/*!
 * @file      lr1110_bootloader.c
 *
 * @brief     Bootloader driver implementation for LR1110
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2021. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include "common/lr1110_bootloader.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

#define LR1110_FLASH_DATA_MAX_LENGTH_UINT32 ( 64 )
#define LR1110_FLASH_DATA_MAX_LENGTH_UINT8 ( LR1110_FLASH_DATA_MAX_LENGTH_UINT32 * 4 )

#define LR1110_BL_CMD_NO_PARAM_LENGTH ( 2 )
#define LR1110_BL_GET_STATUS_CMD_LENGTH ( 2 + 4 )
#define LR1110_BL_VERSION_CMD_LENGTH LR1110_BL_CMD_NO_PARAM_LENGTH
#define LR1110_BL_ERASE_FLASH_CMD_LENGTH LR1110_BL_CMD_NO_PARAM_LENGTH
#define LR1110_BL_WRITE_FLASH_ENCRYPTED_CMD_LENGTH ( LR1110_BL_CMD_NO_PARAM_LENGTH + 4 )
#define LR1110_BL_REBOOT_CMD_LENGTH ( LR1110_BL_CMD_NO_PARAM_LENGTH + 1 )
#define LR1110_BL_GET_PIN_CMD_LENGTH ( LR1110_BL_CMD_NO_PARAM_LENGTH )
#define LR1110_BL_READ_CHIP_EUI_CMD_LENGTH ( LR1110_BL_CMD_NO_PARAM_LENGTH )
#define LR1110_BL_READ_JOIN_EUI_CMD_LENGTH ( LR1110_BL_CMD_NO_PARAM_LENGTH )

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*!
 * @brief Operating codes for bootloader-related operations
 */
enum
{
    LR1110_BL_GET_STATUS_OC            = 0x0100,
    LR1110_BL_GET_VERSION_OC           = 0x0101,
    LR1110_BL_ERASE_FLASH_OC           = 0x8000,
    LR1110_BL_WRITE_FLASH_ENCRYPTED_OC = 0x8003,
    LR1110_BL_REBOOT_OC                = 0x8005,
    LR1110_BL_GET_PIN_OC               = 0x800B,
    LR1110_BL_READ_CHIP_EUI_OC         = 0x800C,
    LR1110_BL_READ_JOIN_EUI_OC         = 0x800D
};

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/*!
 * @brief Returns the minimum of the operand given as parameter and the maximum allowed block size
 *
 * @param [in] operand Size to compare
 *
 * @returns Minimum between operand and @ref LR1110_FLASH_DATA_MAX_LENGTH_UINT32
 */
static uint8_t lr1110_bootloader_get_min_from_operand_and_max_block_size( uint32_t operand );

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

err_t lr1110_bootloader_get_status( lriot_t *ctx, lr1110_bootloader_stat1_t* stat1, lr1110_bootloader_stat2_t* stat2,
                                    lr1110_bootloader_irq_mask_t* irq_status )
{
    uint8_t data_[LR1110_BL_GET_STATUS_CMD_LENGTH];

    err_t status = lr1110_hal_direct_read( ctx, data_, LR1110_BL_GET_STATUS_CMD_LENGTH );

    if( status == LRIOT_OK )
    {
        stat1->is_interrupt_active = ( ( data_[0] & 0x01 ) != 0 ) ? true : false;
        stat1->command_status      = ( data_[0] >> 1 );

        stat2->is_running_from_flash = ( ( data_[1] & 0x01 ) != 0 ) ? true : false;
        stat2->chip_mode             = ( ( data_[1] & 0x0F ) >> 1 );
        stat2->reset_status          = ( ( data_[1] & 0xF0 ) >> 4 );

        *irq_status =
            ( ( lr1110_bootloader_irq_mask_t ) data_[2] << 24 ) + ( ( lr1110_bootloader_irq_mask_t ) data_[3] << 16 ) +
            ( ( lr1110_bootloader_irq_mask_t ) data_[4] << 8 ) + ( ( lr1110_bootloader_irq_mask_t ) data_[5] << 0 );
    }

    return status;
}

err_t lr1110_bootloader_clear_reset_status_info( lriot_t *ctx )
{
    uint8_t cbuffer[LR1110_BL_CMD_NO_PARAM_LENGTH] = {
        ( uint8_t )( LR1110_BL_GET_STATUS_OC >> 8 ),
        ( uint8_t )( LR1110_BL_GET_STATUS_OC >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_BL_CMD_NO_PARAM_LENGTH, 0, 0 );
}

err_t lr1110_bootloader_get_version( lriot_t *ctx, lr1110_bootloader_version_t* version )
{
    uint8_t cbuffer[LR1110_BL_VERSION_CMD_LENGTH] = {
        ( uint8_t )( LR1110_BL_GET_VERSION_OC >> 8 ),
        ( uint8_t )( LR1110_BL_GET_VERSION_OC >> 0 )
    };
    uint8_t rbuffer[LR1110_BL_VERSION_LENGTH] = { 0x00 };

    err_t status = lr1110_hal_read( ctx, cbuffer, LR1110_BL_VERSION_CMD_LENGTH,
                                    rbuffer, LR1110_BL_VERSION_LENGTH );

    if( status == LRIOT_OK )
    {
        version->hw   = rbuffer[0];
        version->type = rbuffer[1];
        version->fw   = ( ( uint16_t ) rbuffer[2] << 8 ) + ( uint16_t ) rbuffer[3];
    }

    return status;
}

err_t lr1110_bootloader_erase_flash( lriot_t *ctx )
{
    uint8_t cbuffer[LR1110_BL_ERASE_FLASH_CMD_LENGTH] = {
        ( uint8_t )( LR1110_BL_ERASE_FLASH_OC >> 8 ),
        ( uint8_t )( LR1110_BL_ERASE_FLASH_OC >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_BL_ERASE_FLASH_CMD_LENGTH, 0, 0 );
}

err_t lr1110_bootloader_write_flash_encrypted( lriot_t *ctx, uint32_t offset,
                                               const uint32_t* buffer, uint8_t length )
{
    uint8_t cbuffer[LR1110_BL_WRITE_FLASH_ENCRYPTED_CMD_LENGTH] = {
        ( uint8_t )( LR1110_BL_WRITE_FLASH_ENCRYPTED_OC >> 8 ),
        ( uint8_t )( LR1110_BL_WRITE_FLASH_ENCRYPTED_OC >> 0 ),
        ( uint8_t )( offset >> 24 ),
        ( uint8_t )( offset >> 16 ),
        ( uint8_t )( offset >> 8 ),
        ( uint8_t )( offset >> 0 )
    };

    uint8_t cdata[256] = { 0 };
    for( uint8_t index = 0; index < length; index++ )
    {
        uint8_t* cdata_local = &cdata[index * sizeof( uint32_t )];

        cdata_local[0] = ( uint8_t )( buffer[index] >> 24 );
        cdata_local[1] = ( uint8_t )( buffer[index] >> 16 );
        cdata_local[2] = ( uint8_t )( buffer[index] >> 8 );
        cdata_local[3] = ( uint8_t )( buffer[index] >> 0 );
    }

    return lr1110_hal_write( ctx, cbuffer, LR1110_BL_WRITE_FLASH_ENCRYPTED_CMD_LENGTH, cdata,
                             length * sizeof( uint32_t ) );
}

err_t lr1110_bootloader_write_flash_encrypted_full( lriot_t *ctx, uint32_t offset,
                                                    const uint32_t* buffer, uint32_t length )
{
    uint32_t remaining_length = length;
    uint32_t local_offset     = offset;
    uint32_t loop             = 0;

    while( remaining_length != 0 )
    {
        err_t status = lr1110_bootloader_write_flash_encrypted(
            ctx, local_offset, buffer + loop * LR1110_FLASH_DATA_MAX_LENGTH_UINT32,
            lr1110_bootloader_get_min_from_operand_and_max_block_size( remaining_length ) );

        if( status != LRIOT_OK )
        {
            return status;
        }

        local_offset += LR1110_FLASH_DATA_MAX_LENGTH_UINT8;
        remaining_length = ( remaining_length < LR1110_FLASH_DATA_MAX_LENGTH_UINT32 )
                               ? 0
                               : ( remaining_length - LR1110_FLASH_DATA_MAX_LENGTH_UINT32 );

        loop++;
    }

    return LRIOT_OK;
}

err_t lr1110_bootloader_reboot( lriot_t *ctx, bool stay_in_bootloader )
{
    uint8_t cbuffer[LR1110_BL_REBOOT_CMD_LENGTH] = {
        ( uint8_t )( LR1110_BL_REBOOT_OC >> 8 ),
        ( uint8_t )( LR1110_BL_REBOOT_OC >> 0 ),
        ( ( stay_in_bootloader == true ) ? 0x03 : 0x00 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_BL_REBOOT_CMD_LENGTH, 0, 0 );
}

err_t lr1110_bootloader_read_pin( lriot_t *ctx, lr1110_bootloader_pin_t pin )
{
    uint8_t cbuffer[LR1110_BL_GET_PIN_CMD_LENGTH] = {
        ( uint8_t )( LR1110_BL_GET_PIN_OC >> 8 ),
        ( uint8_t )( LR1110_BL_GET_PIN_OC >> 0 )
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_BL_GET_PIN_CMD_LENGTH, pin, LR1110_BL_PIN_LENGTH );
}

err_t lr1110_bootloader_read_chip_eui( lriot_t *ctx, lr1110_bootloader_chip_eui_t chip_eui )
{
    uint8_t cbuffer[LR1110_BL_READ_CHIP_EUI_CMD_LENGTH] = {
        ( uint8_t )( LR1110_BL_READ_CHIP_EUI_OC >> 8 ),
        ( uint8_t )( LR1110_BL_READ_CHIP_EUI_OC >> 0 )
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_BL_READ_CHIP_EUI_CMD_LENGTH, chip_eui,
                            LR1110_BL_CHIP_EUI_LENGTH );
}

err_t lr1110_bootloader_read_join_eui( lriot_t *ctx, lr1110_bootloader_join_eui_t join_eui )
{
    uint8_t cbuffer[LR1110_BL_READ_JOIN_EUI_CMD_LENGTH] = {
        ( uint8_t )( LR1110_BL_READ_JOIN_EUI_OC >> 8 ),
        ( uint8_t )( LR1110_BL_READ_JOIN_EUI_OC >> 0 )
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_BL_READ_JOIN_EUI_CMD_LENGTH, join_eui,
                            LR1110_BL_JOIN_EUI_LENGTH );
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

static uint8_t lr1110_bootloader_get_min_from_operand_and_max_block_size( uint32_t operand )
{
    if( operand > LR1110_FLASH_DATA_MAX_LENGTH_UINT32 )
    {
        return LR1110_FLASH_DATA_MAX_LENGTH_UINT32;
    }
    else
    {
        return ( uint8_t ) operand;
    }
}

/* --- EOF ------------------------------------------------------------------ */
