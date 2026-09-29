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
 * @file texttospeech.c
 * @brief TextToSpeech Click Driver.
 */

#include "texttospeech.h"
#include "firmware/text_to_speech_img.h"

/**
 * @brief TextToSpeech protocol and audio configuration.
 * @details These macros define ISC frame and padding sizes, boot-loader and main-firmware payload limits,
 * firmware and receive-processing chunk sizes, the 11.025 kHz sample-rate code, and the audio gain offset.
 */
#define TEXTTOSPEECH_START_BYTE                 0xAA
#define TEXTTOSPEECH_PADDING_BYTE               0x00
#define TEXTTOSPEECH_HEADER_SIZE                4
#define TEXTTOSPEECH_PADDING_SIZE               16
#define TEXTTOSPEECH_BOOT_RUN_PADDING           8
#define TEXTTOSPEECH_BOOT_PAYLOAD_MAX           2044
#define TEXTTOSPEECH_MAIN_PAYLOAD_MAX           2112
#define TEXTTOSPEECH_BOOT_CHUNK_SIZE            256
#define TEXTTOSPEECH_PROCESS_SIZE               64
#define TEXTTOSPEECH_SAMPLE_RATE_11KHZ          1
#define TEXTTOSPEECH_GAIN_OFFSET                49

/**
 * @brief TextToSpeech transfer byte function.
 * @details This function exchanges one SPI byte and passes the received byte to the ISC parser.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] data_in : Byte to transmit.
 * @return Driver communication or parser status.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note CS must already be asserted.
 */
static err_t texttospeech_transfer_byte ( texttospeech_t *ctx, uint8_t data_in );

/**
 * @brief TextToSpeech parse byte function.
 * @details This function assembles a bounded ISC frame and tracks the clocks needed to flush it.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] data_in : Received SPI byte.
 * @return Nothing.
 * @note A new frame can begin during padding; start bytes are recognized whenever no frame is active.
 */
static void texttospeech_parse_byte ( texttospeech_t *ctx, uint8_t data_in );

/**
 * @brief TextToSpeech handle message function.
 * @details This function separates asynchronous indications from the pending command response.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @return Nothing.
 * @note An unsolicited second response or malformed indication latches a protocol error.
 */
static void texttospeech_handle_message ( texttospeech_t *ctx );

/**
 * @brief TextToSpeech send parts function.
 * @details This function streams a prefix and payload within one ISC frame without a large transmit buffer.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] message_id : ISC message identifier.
 * @param[in] prefix : Optional leading payload bytes.
 * @param[in] prefix_len : Number of leading bytes.
 * @param[in] data_in : Remaining payload bytes.
 * @param[in] len : Remaining payload length.
 * @return Driver transmission status.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note Boot-run and standby-exit requests have special padding requirements.
 */
static err_t texttospeech_send_parts ( texttospeech_t *ctx, uint16_t message_id, uint8_t *prefix,
                                       uint8_t prefix_len, uint8_t *data_in, uint16_t len );

/**
 * @brief TextToSpeech request function.
 * @details This function sends a request and checks its two-byte status response.
 * @param[in] ctx : Click context object.
 * See #texttospeech_t object definition for detailed explanation.
 * @param[in] message_id : Request whose response identifier is message_id + 1.
 * @param[in] data_in : Request payload, or NULL for an empty payload.
 * @param[in] len : Request payload length.
 * @return Driver or device status.
 * See #texttospeech_return_value_t definition for detailed explanation.
 * @note Boot-load and boot-run succeed with status 1; other requests succeed with status 0.
 */
static err_t texttospeech_request ( texttospeech_t *ctx, uint16_t message_id, uint8_t *data_in, uint16_t len );

/**
 * @brief TextToSpeech get word function.
 * @details This function decodes a two-byte little-endian value.
 * @param[in] data_in : Buffer containing at least two bytes.
 * @return Decoded 16-bit value.
 * @note None.
 */
static uint16_t texttospeech_get_word ( uint8_t *data_in );

/**
 * @brief TextToSpeech get double word function.
 * @details This function decodes a four-byte little-endian value.
 * @param[in] data_in : Buffer containing at least four bytes.
 * @return Decoded 32-bit value.
 * @note None.
 */
static uint32_t texttospeech_get_dword ( uint8_t *data_in );

void texttospeech_cfg_setup ( texttospeech_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->mute = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->drdy = HAL_PIN_NC;

    cfg->spi_speed   = TEXTTOSPEECH_SPI_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t texttospeech_init ( texttospeech_t *ctx, texttospeech_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) )
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, TEXTTOSPEECH_PADDING_BYTE ) )
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) )
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) )
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->mute, cfg->mute );
    digital_out_high( &ctx->mute );

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low( &ctx->rst );

    digital_in_init( &ctx->drdy, cfg->drdy );

    return SPI_MASTER_SUCCESS;
}

void texttospeech_reset ( texttospeech_t *ctx )
{
    texttospeech_set_mute( ctx, TEXTTOSPEECH_MUTE_ENABLE );
    spi_master_deselect_device( ctx->chip_select );
    digital_out_low( &ctx->rst );

    ctx->response_id = 0;
    ctx->device_status = 0;
    ctx->response_len = 0;
    ctx->response_ready = 0;
    ctx->request_pending = 0;
    ctx->rx_active = 0;
    ctx->rx_index = 0;
    ctx->rx_length = 0;
    ctx->rx_padding = 0;
    ctx->speech_ready = 1;
    ctx->speech_finished = 1;
    ctx->rx_error = TEXTTOSPEECH_OK;

    Delay_10ms( );
    digital_out_high( &ctx->rst );

    // Epson requires at least 120 ms without SPI clocks after releasing reset.
    Delay_100ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

err_t texttospeech_default_cfg ( texttospeech_t *ctx ) 
{
    texttospeech_version_t version;
    uint8_t boot_data[ TEXTTOSPEECH_BOOT_CHUNK_SIZE ];
    // Fixed ISC payloads for host registration and power-manager configuration.
    uint8_t registration[ 8 ] = { 1, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t power_config[ 4 ] = { 1, 0, 1, 0 };
    uint32_t offset = 0;
    uint16_t count;
    uint16_t index;
    err_t error_flag;

    texttospeech_reset( ctx );
    error_flag = texttospeech_get_version( ctx, &version );

    // Keep the image in program memory and acknowledge every uploaded block.
    while ( ( offset < sizeof( TTS_INIT_DATA ) ) && ( TEXTTOSPEECH_OK == error_flag ) )
    {
        count = TEXTTOSPEECH_BOOT_CHUNK_SIZE;
        if ( ( sizeof( TTS_INIT_DATA ) - offset ) < count )
        {
            count = sizeof( TTS_INIT_DATA ) - offset;
        }
        for ( index = 0; index < count; index++ )
        {
            boot_data[ index ] = TTS_INIT_DATA[ offset + index ];
        }
        error_flag = texttospeech_request( ctx, TEXTTOSPEECH_ISC_BOOT_LOAD_REQ, boot_data, count );
        offset += count;
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        error_flag = texttospeech_request( ctx, TEXTTOSPEECH_ISC_BOOT_RUN_REQ, NULL, 0 );
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        // No SPI clocks during the transition from the boot loader to the main firmware.
        Delay_100ms( );
        Delay_10ms( );
        Delay_10ms( );
        Delay_10ms( );
        Delay_10ms( );
        Delay_10ms( );
        error_flag = texttospeech_request( ctx, TEXTTOSPEECH_ISC_TEST_REQ, registration, sizeof( registration ) );
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        error_flag = texttospeech_get_version( ctx, &version );
        if ( ( TEXTTOSPEECH_OK == error_flag ) && !( version.features & TEXTTOSPEECH_FEATURE_TTS ) )
        {
            error_flag = TEXTTOSPEECH_ERROR_DEVICE;
        }
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        error_flag = texttospeech_request( ctx, TEXTTOSPEECH_ISC_PMAN_CONFIG_REQ, power_config, sizeof( power_config ) );
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        error_flag = texttospeech_set_volume( ctx, TEXTTOSPEECH_VOLUME_DEFAULT );
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        error_flag = texttospeech_set_config( ctx, TEXTTOSPEECH_VOICE_PAUL, TEXTTOSPEECH_LANGUAGE_US_ENGLISH,
                                              TEXTTOSPEECH_RATE_DEFAULT, TEXTTOSPEECH_PARSER_DECTALK );
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        texttospeech_set_mute( ctx, TEXTTOSPEECH_MUTE_DISABLE );
    }

    return error_flag;
}

err_t texttospeech_write_message ( texttospeech_t *ctx, uint16_t message_id, uint8_t *data_in, uint16_t len )
{
    return texttospeech_send_parts( ctx, message_id, NULL, 0, data_in, len );
}

err_t texttospeech_read_response ( texttospeech_t *ctx, uint16_t response_id, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = TEXTTOSPEECH_OK;
    uint16_t elapsed = 0;
    uint8_t complete = 0;

    if ( ( len > sizeof( ctx->response ) ) || ( len && !data_out ) || !ctx->request_pending )
    {
        error_flag = TEXTTOSPEECH_ERROR;
    }
    while ( ( TEXTTOSPEECH_OK == error_flag ) && !complete )
    {
        error_flag = texttospeech_process( ctx );
        complete = ctx->response_ready && !ctx->rx_active && !ctx->rx_padding && !digital_in_read( &ctx->drdy );
        if ( ( TEXTTOSPEECH_OK == error_flag ) && !complete )
        {
            if ( elapsed >= TEXTTOSPEECH_RESPONSE_TIMEOUT_MS )
            {
                // A late response must not be mistaken for the next command's reply.
                ctx->rx_error = TEXTTOSPEECH_ERROR_TIMEOUT;
                error_flag = ctx->rx_error;
            }
            else
            {
                Delay_1ms( );
                elapsed++;
            }
        }
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        if ( ( response_id != ctx->response_id ) || ( len != ctx->response_len ) )
        {
            ctx->rx_error = TEXTTOSPEECH_ERROR_PROTOCOL;
            error_flag = ctx->rx_error;
        }
        else
        {
            if ( len )
            {
                memcpy( data_out, ctx->response, len );
            }
            ctx->response_ready = 0;
            ctx->request_pending = 0;
        }
    }

    return error_flag;
}

err_t texttospeech_process ( texttospeech_t *ctx )
{
    uint8_t index = 0;
    err_t error_flag = ctx->rx_error;

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    while ( ( index < TEXTTOSPEECH_PROCESS_SIZE ) && ( TEXTTOSPEECH_OK == error_flag ) &&
            ( ctx->rx_active || ctx->rx_padding || digital_in_read( &ctx->drdy ) ) )
    {
        error_flag = texttospeech_transfer_byte( ctx, TEXTTOSPEECH_PADDING_BYTE );
        index++;
    }
    spi_master_deselect_device( ctx->chip_select );
    Delay_1us( );

    return error_flag;
}

err_t texttospeech_get_version ( texttospeech_t *ctx, texttospeech_version_t *version )
{
    uint8_t response[ 16 ];
    err_t error_flag = TEXTTOSPEECH_ERROR;

    if ( version )
    {
        error_flag = texttospeech_write_message( ctx, TEXTTOSPEECH_ISC_VERSION_REQ, NULL, 0 );
        if ( TEXTTOSPEECH_OK == error_flag )
        {
            error_flag = texttospeech_read_response( ctx, TEXTTOSPEECH_ISC_VERSION_RESP, response, sizeof( response ) );
        }
        if ( TEXTTOSPEECH_OK == error_flag )
        {
            version->hardware_major = response[ 0 ];
            version->hardware_minor = response[ 1 ];
            version->firmware_major = response[ 2 ];
            version->firmware_minor = response[ 3 ];
            version->features = texttospeech_get_dword( &response[ 4 ] );
            version->languages = texttospeech_get_dword( &response[ 8 ] );
            version->firmware_patch = response[ 12 ];
        }
    }

    return error_flag;
}

err_t texttospeech_set_config ( texttospeech_t *ctx, uint8_t voice, uint8_t language, uint16_t rate, uint8_t parser )
{
    uint8_t config[ 8 ] = { TEXTTOSPEECH_SAMPLE_RATE_11KHZ, 0, 0, 0, 0, 0, 0, 0 };
    err_t error_flag = TEXTTOSPEECH_ERROR;

    if ( ( ( TEXTTOSPEECH_VOICE_PAUL == voice ) || ( TEXTTOSPEECH_VOICE_HARRY == voice ) ||
           ( TEXTTOSPEECH_VOICE_DENNIS == voice ) || ( TEXTTOSPEECH_VOICE_WENDY == voice ) ) &&
         ( ( TEXTTOSPEECH_LANGUAGE_US_ENGLISH == language ) || ( TEXTTOSPEECH_LANGUAGE_CASTILIAN_SPANISH == language ) ||
           ( TEXTTOSPEECH_LANGUAGE_LATIN_SPANISH == language ) ) &&
         ( rate >= TEXTTOSPEECH_RATE_MIN ) && ( rate <= TEXTTOSPEECH_RATE_MAX ) && ( parser <= TEXTTOSPEECH_PARSER_EPSON ) )
    {
        config[ 1 ] = voice;
        config[ 2 ] = parser;
        config[ 3 ] = language;
        config[ 4 ] = ( uint8_t ) rate;
        config[ 5 ] = ( uint8_t ) ( rate >> 8 );
        error_flag = texttospeech_request( ctx, TEXTTOSPEECH_ISC_TTS_CONFIG_REQ, config, sizeof( config ) );
    }

    return error_flag;
}

err_t texttospeech_set_volume ( texttospeech_t *ctx, int8_t gain_db )
{
    uint8_t config[ 8 ] = { 0, 0, 0, TEXTTOSPEECH_SAMPLE_RATE_11KHZ, 0, 0, 0, 0 };
    err_t error_flag = TEXTTOSPEECH_ERROR;

    if ( ( gain_db >= TEXTTOSPEECH_VOLUME_MIN ) && ( gain_db <= TEXTTOSPEECH_VOLUME_MAX ) )
    {
        // The audio configuration uses 1 for -48 dB, 49 for 0 dB, and 67 for +18 dB.
        config[ 1 ] = ( uint8_t ) ( gain_db + TEXTTOSPEECH_GAIN_OFFSET );
        error_flag = texttospeech_request( ctx, TEXTTOSPEECH_ISC_AUDIO_CONFIG_REQ, config, sizeof( config ) );
    }

    return error_flag;
}

err_t texttospeech_speak ( texttospeech_t *ctx, char *text )
{
    uint16_t len = 0;
    uint8_t flush = 0;
    uint8_t response[ 2 ];
    err_t error_flag = TEXTTOSPEECH_ERROR;

    if ( text )
    {
        while ( ( len <= TEXTTOSPEECH_TEXT_MAX_LEN ) && text[ len ] )
        {
            len++;
        }
        if ( len && ( len <= TEXTTOSPEECH_TEXT_MAX_LEN ) )
        {
            error_flag = texttospeech_process( ctx );
            if ( ( TEXTTOSPEECH_OK == error_flag ) && ( !ctx->speech_ready || !ctx->speech_finished ) )
            {
                error_flag = TEXTTOSPEECH_ERROR_BUSY;
            }
            if ( TEXTTOSPEECH_OK == error_flag )
            {
                error_flag = texttospeech_send_parts( ctx, TEXTTOSPEECH_ISC_TTS_SPEAK_REQ, &flush, 1,
                                                      ( uint8_t * ) text, len + 1 );
                if ( TEXTTOSPEECH_OK == error_flag )
                {
                    error_flag = texttospeech_read_response( ctx, TEXTTOSPEECH_ISC_TTS_SPEAK_RESP,
                                                             response, sizeof( response ) );
                }
                if ( TEXTTOSPEECH_OK == error_flag )
                {
                    ctx->device_status = texttospeech_get_word( response );
                    if ( ctx->device_status )
                    {
                        ctx->speech_ready = 1;
                        ctx->speech_finished = 1;
                        error_flag = TEXTTOSPEECH_ERROR_DEVICE;
                    }
                }
            }
        }
    }

    return error_flag;
}

err_t texttospeech_wait_complete ( texttospeech_t *ctx, uint32_t timeout_ms )
{
    err_t error_flag = TEXTTOSPEECH_OK;
    uint32_t elapsed = 0;
    uint8_t complete = 0;

    while ( ( TEXTTOSPEECH_OK == error_flag ) && !complete )
    {
        error_flag = texttospeech_process( ctx );
        complete = ctx->speech_finished && ctx->speech_ready && !ctx->rx_active && !ctx->rx_padding &&
                   !digital_in_read( &ctx->drdy );
        if ( ( TEXTTOSPEECH_OK == error_flag ) && !complete )
        {
            if ( elapsed >= timeout_ms )
            {
                error_flag = TEXTTOSPEECH_ERROR_TIMEOUT;
            }
            else
            {
                Delay_1ms( );
                elapsed++;
            }
        }
    }

    return error_flag;
}

err_t texttospeech_set_pause ( texttospeech_t *ctx, uint8_t enable )
{
    uint8_t payload[ 2 ] = { 0, 0 };
    err_t error_flag = TEXTTOSPEECH_ERROR;

    if ( enable <= TEXTTOSPEECH_PAUSE_ENABLE )
    {
        payload[ 0 ] = enable;
        error_flag = texttospeech_request( ctx, TEXTTOSPEECH_ISC_TTS_PAUSE_REQ, payload, sizeof( payload ) );
    }

    return error_flag;
}

err_t texttospeech_stop ( texttospeech_t *ctx )
{
    uint8_t payload[ 2 ] = { 0, 0 };
    err_t error_flag = texttospeech_request( ctx, TEXTTOSPEECH_ISC_TTS_STOP_REQ, payload, sizeof( payload ) );

    if ( TEXTTOSPEECH_OK == error_flag )
    {
        ctx->speech_ready = 1;
        ctx->speech_finished = 1;
    }

    return error_flag;
}

void texttospeech_set_mute ( texttospeech_t *ctx, uint8_t enable )
{
    digital_out_write( &ctx->mute, enable ? TEXTTOSPEECH_MUTE_ENABLE : TEXTTOSPEECH_MUTE_DISABLE );
}

static err_t texttospeech_transfer_byte ( texttospeech_t *ctx, uint8_t data_in )
{
    uint8_t data_out;
    err_t error_flag = spi_master_transfer( &ctx->spi, &data_in, &data_out, 1 );

    if ( SPI_MASTER_SUCCESS == error_flag )
    {
        texttospeech_parse_byte( ctx, data_out );
    }
    else
    {
        ctx->rx_error = TEXTTOSPEECH_ERROR;
    }

    return ctx->rx_error;
}

static void texttospeech_parse_byte ( texttospeech_t *ctx, uint8_t data_in )
{
    if ( ctx->rx_padding )
    {
        ctx->rx_padding--;
    }
    if ( !ctx->rx_active )
    {
        if ( TEXTTOSPEECH_START_BYTE == data_in )
        {
            ctx->rx_active = 1;
            ctx->rx_index = 0;
            ctx->rx_length = 0;
        }
    }
    else
    {
        ctx->rx_buffer[ ctx->rx_index++ ] = data_in;
        if ( 2 == ctx->rx_index )
        {
            ctx->rx_length = texttospeech_get_word( ctx->rx_buffer );
            if ( ( ctx->rx_length < TEXTTOSPEECH_HEADER_SIZE ) || ( ctx->rx_length > sizeof( ctx->rx_buffer ) ) )
            {
                ctx->rx_error = TEXTTOSPEECH_ERROR_PROTOCOL;
                ctx->rx_active = 0;
            }
        }
        if ( ctx->rx_active && ( ctx->rx_index == ctx->rx_length ) )
        {
            ctx->rx_active = 0;
            ctx->rx_padding = TEXTTOSPEECH_PADDING_SIZE;
            if ( TEXTTOSPEECH_ISC_BOOT_RUN_RESP == texttospeech_get_word( &ctx->rx_buffer[ 2 ] ) )
            {
                ctx->rx_padding = TEXTTOSPEECH_BOOT_RUN_PADDING;
            }
            texttospeech_handle_message( ctx );
        }
    }
}

static void texttospeech_handle_message ( texttospeech_t *ctx )
{
    uint16_t message_id = texttospeech_get_word( &ctx->rx_buffer[ 2 ] );
    uint8_t len = ctx->rx_length - TEXTTOSPEECH_HEADER_SIZE;

    switch ( message_id )
    {
        case TEXTTOSPEECH_ISC_TTS_READY_IND:
        case TEXTTOSPEECH_ISC_TTS_FINISHED_IND:
        case TEXTTOSPEECH_ISC_SPCODEC_READY_IND:
        case TEXTTOSPEECH_ISC_SPCODEC_FINISHED_IND:
        {
            if ( len )
            {
                ctx->rx_error = TEXTTOSPEECH_ERROR_PROTOCOL;
            }
            else if ( TEXTTOSPEECH_ISC_TTS_READY_IND == message_id )
            {
                ctx->speech_ready = 1;
            }
            else if ( TEXTTOSPEECH_ISC_TTS_FINISHED_IND == message_id )
            {
                ctx->speech_finished = 1;
            }
            break;
        }
        case TEXTTOSPEECH_ISC_ERROR_IND:
        {
            if ( 2 == len )
            {
                ctx->device_status = texttospeech_get_word( &ctx->rx_buffer[ 4 ] );
                ctx->rx_error = TEXTTOSPEECH_ERROR_DEVICE;
            }
            else
            {
                ctx->rx_error = TEXTTOSPEECH_ERROR_PROTOCOL;
            }
            break;
        }
        case TEXTTOSPEECH_ISC_MSG_BLOCKED_RESP:
        {
            if ( 4 == len )
            {
                ctx->device_status = texttospeech_get_word( &ctx->rx_buffer[ 6 ] );
                ctx->rx_error = TEXTTOSPEECH_ERROR_DEVICE;
            }
            else
            {
                ctx->rx_error = TEXTTOSPEECH_ERROR_PROTOCOL;
            }
            break;
        }
        default:
        {
            if ( ctx->response_ready || !ctx->request_pending )
            {
                ctx->rx_error = TEXTTOSPEECH_ERROR_PROTOCOL;
            }
            else
            {
                ctx->response_id = message_id;
                ctx->response_len = len;
                memcpy( ctx->response, &ctx->rx_buffer[ TEXTTOSPEECH_HEADER_SIZE ], len );
                ctx->response_ready = 1;
            }
            break;
        }
    }
}

static err_t texttospeech_send_parts ( texttospeech_t *ctx, uint16_t message_id, uint8_t *prefix,
                                       uint8_t prefix_len, uint8_t *data_in, uint16_t len )
{
    uint8_t header[ 5 ];
    uint8_t padding = TEXTTOSPEECH_PADDING_SIZE;
    uint16_t index;
    uint16_t frame_len;
    uint16_t payload_max = TEXTTOSPEECH_MAIN_PAYLOAD_MAX;
    err_t error_flag = TEXTTOSPEECH_OK;

    if ( TEXTTOSPEECH_ISC_BOOT_LOAD_REQ == message_id )
    {
        payload_max = TEXTTOSPEECH_BOOT_PAYLOAD_MAX;
    }
    if ( ( len && !data_in ) || ( prefix_len && !prefix ) || ( ( uint32_t ) len + prefix_len > payload_max ) )
    {
        error_flag = TEXTTOSPEECH_ERROR;
    }
    else if ( ctx->request_pending )
    {
        error_flag = TEXTTOSPEECH_ERROR_BUSY;
    }
    else
    {
        error_flag = texttospeech_process( ctx );
        if ( ( TEXTTOSPEECH_OK == error_flag ) &&
             ( ctx->rx_active || ctx->rx_padding || digital_in_read( &ctx->drdy ) ) )
        {
            error_flag = TEXTTOSPEECH_ERROR_BUSY;
        }
    }

    if ( TEXTTOSPEECH_OK == error_flag )
    {
        // The ISC length counts its four-byte header and payload, not the start byte.
        frame_len = TEXTTOSPEECH_HEADER_SIZE + prefix_len + len;
        header[ 0 ] = TEXTTOSPEECH_START_BYTE;
        header[ 1 ] = ( uint8_t ) frame_len;
        header[ 2 ] = ( uint8_t ) ( frame_len >> 8 );
        header[ 3 ] = ( uint8_t ) message_id;
        header[ 4 ] = ( uint8_t ) ( message_id >> 8 );
        ctx->request_pending = 1;
        ctx->response_ready = 0;
        ctx->device_status = 0;
        if ( TEXTTOSPEECH_ISC_TTS_SPEAK_REQ == message_id )
        {
            // READY can arrive before SPEAK_RESP, even while the request is still being sent.
            ctx->speech_ready = 0;
            ctx->speech_finished = 0;
        }

        if ( TEXTTOSPEECH_ISC_BOOT_RUN_REQ == message_id )
        {
            padding = TEXTTOSPEECH_BOOT_RUN_PADDING;
        }
        else if ( TEXTTOSPEECH_ISC_PMAN_STANDBY_EXIT_IND == message_id )
        {
            padding = 0;
        }

        spi_master_select_device( ctx->chip_select );
        Delay_1us( );
        for ( index = 0; ( index < sizeof( header ) ) && ( TEXTTOSPEECH_OK == error_flag ); index++ )
        {
            error_flag = texttospeech_transfer_byte( ctx, header[ index ] );
        }
        for ( index = 0; ( index < prefix_len ) && ( TEXTTOSPEECH_OK == error_flag ); index++ )
        {
            error_flag = texttospeech_transfer_byte( ctx, prefix[ index ] );
        }
        for ( index = 0; ( index < len ) && ( TEXTTOSPEECH_OK == error_flag ); index++ )
        {
            error_flag = texttospeech_transfer_byte( ctx, data_in[ index ] );
        }
        for ( index = 0; ( index < padding ) && ( TEXTTOSPEECH_OK == error_flag ); index++ )
        {
            error_flag = texttospeech_transfer_byte( ctx, TEXTTOSPEECH_PADDING_BYTE );
        }
        spi_master_deselect_device( ctx->chip_select );
        Delay_1us( );
    }

    return error_flag;
}

static err_t texttospeech_request ( texttospeech_t *ctx, uint16_t message_id, uint8_t *data_in, uint16_t len )
{
    uint8_t response[ 2 ];
    uint16_t expected_status = 0;
    err_t error_flag = texttospeech_write_message( ctx, message_id, data_in, len );

    if ( TEXTTOSPEECH_OK == error_flag )
    {
        error_flag = texttospeech_read_response( ctx, message_id + 1, response, sizeof( response ) );
    }
    if ( TEXTTOSPEECH_OK == error_flag )
    {
        if ( ( TEXTTOSPEECH_ISC_BOOT_LOAD_REQ == message_id ) || ( TEXTTOSPEECH_ISC_BOOT_RUN_REQ == message_id ) )
        {
            expected_status = 1;
        }
        ctx->device_status = texttospeech_get_word( response );
        if ( ctx->device_status != expected_status )
        {
            error_flag = TEXTTOSPEECH_ERROR_DEVICE;
        }
    }

    return error_flag;
}

static uint16_t texttospeech_get_word ( uint8_t *data_in )
{
    return ( uint16_t ) data_in[ 0 ] | ( ( uint16_t ) data_in[ 1 ] << 8 );
}

static uint32_t texttospeech_get_dword ( uint8_t *data_in )
{
    return ( uint32_t ) data_in[ 0 ] | ( ( uint32_t ) data_in[ 1 ] << 8 ) |
           ( ( uint32_t ) data_in[ 2 ] << 16 ) | ( ( uint32_t ) data_in[ 3 ] << 24 );
}

// ------------------------------------------------------------------------- END
