/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file wifi10_wpa.c
 * @brief WPA2 passphrase derivation for WiFi 10 Click.
 * @details Uses FIPS 180-4 SHA-1 and RFC 8018 PBKDF2 with the parameters specified by IEEE 802.11.
 */

#include "wifi10.h"
#include "wifi10_protocol.h"
#include "wifi10_wpa.h"
#include <string.h>

/**
 * @brief WPA2 derivation settings.
 * @details SHA-1 block and digest sizes, HMAC pads, and PBKDF2 iteration count.
 */
#define WIFI10_SHA1_BLOCK_SIZE          64u
#define WIFI10_SHA1_BLOCK_WORDS         16u
#define WIFI10_SHA1_WORD_MASK           ( WIFI10_SHA1_BLOCK_WORDS - 1u )
#define WIFI10_SHA1_STATE_WORDS         5u
#define WIFI10_SHA1_DIGEST_SIZE         20u
#define WIFI10_SHA1_ROUNDS              80u
#define WIFI10_SHA1_PAD_BYTE            0x80u
#define WIFI10_HMAC_INNER_PAD           0x36u
#define WIFI10_HMAC_OUTER_PAD           0x5Cu
#define WIFI10_PBKDF2_INDEX_SIZE        4u
#define WIFI10_PBKDF2_ITERATIONS        4096u

/**
 * @brief WiFi 10 WPA2 derivation workspace.
 * @details Reuses the SHA-1 block and schedule across HMAC iterations.
 */
typedef struct
{
    uint32_t words[ WIFI10_SHA1_BLOCK_WORDS ];
    uint32_t inner[ WIFI10_SHA1_STATE_WORDS ];
    uint32_t outer[ WIFI10_SHA1_STATE_WORDS ];
    uint32_t state[ WIFI10_SHA1_STATE_WORDS ];
    uint8_t block[ WIFI10_SHA1_BLOCK_SIZE ];
    uint8_t salt[ WIFI10_SSID_MAX_LENGTH + WIFI10_PBKDF2_INDEX_SIZE ];
    uint8_t digest[ WIFI10_SHA1_DIGEST_SIZE ];

} wifi10_wpa_work_t;

/**
 * @brief SHA-1 word rotation.
 * @param[in] value : Word to rotate.
 * @param[in] count : Number of bits to rotate left, from 1 to 31.
 * @return Rotated word.
 */
static uint32_t wifi10_sha1_rotate ( uint32_t value, uint8_t count );

/**
 * @brief SHA-1 block compression.
 * @param[in,out] work : Workspace containing the current 64-byte block and schedule storage.
 * @param[in,out] state : Five SHA-1 state words updated with the block.
 * @return Nothing.
 */
static void wifi10_sha1_transform ( wifi10_wpa_work_t *work, uint32_t *state );

/**
 * @brief SHA-1 digest after an HMAC pad.
 * @details Processes one final block after the already hashed 64-byte pad.
 * @param[in,out] work : Block, state, and digest storage.
 * @param[in] initial : SHA-1 state after hashing the pad.
 * @param[in] message : Remaining bytes. May be the previous digest.
 * @param[in] length : Remaining message length, up to 55 bytes.
 * @return Nothing.
 */
static void wifi10_sha1_finish ( wifi10_wpa_work_t *work, uint32_t *initial, uint8_t *message, uint8_t length );

/**
 * @brief WPA2 HMAC-SHA1 function.
 * @details Uses the saved inner and outer pad states to produce the next PBKDF2 digest.
 * @param[in,out] work : Precomputed pad states and digest storage.
 * @param[in] message : Input bytes, possibly the previous digest.
 * @param[in] length : Number of input bytes.
 * @return Nothing.
 */
static void wifi10_hmac_sha1 ( wifi10_wpa_work_t *work, uint8_t *message, uint8_t length );

void wifi10_derive_pmk ( char *ssid, uint8_t ssid_length, char *password, uint8_t password_length, uint8_t *pmk )
{
    wifi10_wpa_work_t work;
    uint8_t salt_length = ssid_length + WIFI10_PBKDF2_INDEX_SIZE;
    uint8_t copy_length;
    volatile uint8_t *workspace_bytes = ( volatile uint8_t * ) &work;

    work.inner[ 0 ] = 0x67452301ul;
    work.inner[ 1 ] = 0xEFCDAB89ul;
    work.inner[ 2 ] = 0x98BADCFEul;
    work.inner[ 3 ] = 0x10325476ul;
    work.inner[ 4 ] = 0xC3D2E1F0ul;
    memcpy( work.outer, work.inner, sizeof( work.inner ) );

    // Valid WPA2 passphrases fit in one SHA-1 block, so the HMAC key needs only zero padding.
    memset( work.block, WIFI10_HMAC_INNER_PAD, sizeof( work.block ) );
    for ( uint8_t index = 0; index < password_length; index++ )
    {
        work.block[ index ] ^= ( uint8_t ) password[ index ];
    }
    wifi10_sha1_transform( &work, work.inner );
    for ( uint8_t index = 0; index < WIFI10_SHA1_BLOCK_SIZE; index++ )
    {
        work.block[ index ] ^= WIFI10_HMAC_INNER_PAD ^ WIFI10_HMAC_OUTER_PAD;
    }
    wifi10_sha1_transform( &work, work.outer );

    memset( work.salt, 0, sizeof( work.salt ) );
    memcpy( work.salt, ssid, ssid_length );
    for ( uint8_t offset = 0; offset < WIFI10_PMK_LENGTH; offset += WIFI10_SHA1_DIGEST_SIZE )
    {
        // The block number is a big-endian 32-bit integer. A 32-byte key uses block numbers 1 and 2.
        work.salt[ salt_length - 1u ] = offset / WIFI10_SHA1_DIGEST_SIZE + 1u;
        copy_length = WIFI10_PMK_LENGTH - offset;
        if ( copy_length > WIFI10_SHA1_DIGEST_SIZE )
        {
            copy_length = WIFI10_SHA1_DIGEST_SIZE;
        }

        wifi10_hmac_sha1( &work, work.salt, salt_length );
        memcpy( pmk + offset, work.digest, copy_length );
        for ( uint16_t iteration = 1u; iteration < WIFI10_PBKDF2_ITERATIONS; iteration++ )
        {
            wifi10_hmac_sha1( &work, work.digest, WIFI10_SHA1_DIGEST_SIZE );
            for ( uint8_t index = 0; index < copy_length; index++ )
            {
                pmk[ offset + index ] ^= work.digest[ index ];
            }
        }
    }

    for ( uint16_t index = 0; index < sizeof( work ); index++ )
    {
        workspace_bytes[ index ] = 0;
    }
}

static uint32_t wifi10_sha1_rotate ( uint32_t value, uint8_t count )
{
    return ( value << count ) | ( value >> ( 32u - count ) );
}

static void wifi10_sha1_transform ( wifi10_wpa_work_t *work, uint32_t *state )
{
    uint32_t a = state[ 0 ];
    uint32_t b = state[ 1 ];
    uint32_t c = state[ 2 ];
    uint32_t d = state[ 3 ];
    uint32_t e = state[ 4 ];
    uint32_t mix;
    uint32_t round_constant;
    uint32_t next;
    uint8_t slot;

    for ( uint8_t index = 0; index < WIFI10_SHA1_BLOCK_WORDS; index++ )
    {
        uint8_t offset = 4u * index;
        work->words[ index ] = ( ( uint32_t ) work->block[ offset ] << 24 ) |
                               ( ( uint32_t ) work->block[ offset + 1u ] << 16 ) |
                               ( ( uint32_t ) work->block[ offset + 2u ] << 8 ) |
                               ( uint32_t ) work->block[ offset + 3u ];
    }
    for ( uint8_t round = 0; round < WIFI10_SHA1_ROUNDS; round++ )
    {
        slot = round & WIFI10_SHA1_WORD_MASK;
        if ( round >= WIFI10_SHA1_BLOCK_WORDS )
        {
            work->words[ slot ] = wifi10_sha1_rotate( work->words[ ( round - 3u ) & WIFI10_SHA1_WORD_MASK ] ^
                                                    work->words[ ( round - 8u ) & WIFI10_SHA1_WORD_MASK ] ^
                                                    work->words[ ( round - 14u ) & WIFI10_SHA1_WORD_MASK ] ^
                                                    work->words[ slot ], 1u );
        }
        if ( round < 20u )
        {
            mix = ( b & c ) | ( ~b & d );
            round_constant = 0x5A827999ul;
        }
        else if ( round < 40u )
        {
            mix = b ^ c ^ d;
            round_constant = 0x6ED9EBA1ul;
        }
        else if ( round < 60u )
        {
            mix = ( b & c ) | ( b & d ) | ( c & d );
            round_constant = 0x8F1BBCDCul;
        }
        else
        {
            mix = b ^ c ^ d;
            round_constant = 0xCA62C1D6ul;
        }
        next = wifi10_sha1_rotate( a, 5u ) + mix + e + round_constant + work->words[ slot ];
        e = d;
        d = c;
        c = wifi10_sha1_rotate( b, 30u );
        b = a;
        a = next;
    }
    state[ 0 ] += a;
    state[ 1 ] += b;
    state[ 2 ] += c;
    state[ 3 ] += d;
    state[ 4 ] += e;
}

static void wifi10_sha1_finish ( wifi10_wpa_work_t *work, uint32_t *initial, uint8_t *message, uint8_t length )
{
    uint16_t bit_length = ( WIFI10_SHA1_BLOCK_SIZE + length ) * 8u;

    memset( work->block, 0, sizeof( work->block ) );
    memcpy( work->block, message, length );
    work->block[ length ] = WIFI10_SHA1_PAD_BYTE;
    // The high six bytes of SHA-1's length field are zero for every WPA2 HMAC message.
    work->block[ WIFI10_SHA1_BLOCK_SIZE - 2u ] = ( uint8_t ) ( bit_length >> 8 );
    work->block[ WIFI10_SHA1_BLOCK_SIZE - 1u ] = ( uint8_t ) bit_length;

    memcpy( work->state, initial, sizeof( work->state ) );
    wifi10_sha1_transform( work, work->state );
    for ( uint8_t index = 0; index < WIFI10_SHA1_STATE_WORDS; index++ )
    {
        uint8_t offset = 4u * index;
        uint32_t word = work->state[ index ];
        work->digest[ offset ] = ( uint8_t ) ( word >> 24 );
        work->digest[ offset + 1u ] = ( uint8_t ) ( word >> 16 );
        work->digest[ offset + 2u ] = ( uint8_t ) ( word >> 8 );
        work->digest[ offset + 3u ] = ( uint8_t ) word;
    }
}

static void wifi10_hmac_sha1 ( wifi10_wpa_work_t *work, uint8_t *message, uint8_t length )
{
    wifi10_sha1_finish( work, work->inner, message, length );
    wifi10_sha1_finish( work, work->outer, work->digest, WIFI10_SHA1_DIGEST_SIZE );
}

// ------------------------------------------------------------------------- END
