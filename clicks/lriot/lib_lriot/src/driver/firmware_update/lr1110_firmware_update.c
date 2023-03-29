/*!
 * \file      lr1110_firmware_update.c
 *
 * \brief     LR1110 firmware update implementation
 *
 * Revised BSD License
 * Copyright Semtech Corporation 2020. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include "lriot.h"
#include "common/lr1110_bootloader.h"
#include "transceiver/lr1110_system.h"
#include "modem/lr1110_modem_lorawan.h"
#include "firmware_update/lr1110_firmware_update.h"

err_t lr1110_update_firmware( lriot_t *ctx, uint32_t fw_expected, const uint32_t* buffer, uint32_t length )
{
    lr1110_bootloader_version_t version_bootloader = { 0 };
    
    digital_out_init ( ( digital_out_t * ) &ctx->bsy, ctx->bsy_pin_name );
    digital_out_low ( ( digital_out_t * ) &ctx->bsy );
    lr1110_hal_reset( ctx );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    digital_in_init ( &ctx->bsy, ctx->bsy_pin_name );
    while ( lriot_get_busy_pin( ctx ) );
    Delay_100ms( );
    
    lr1110_bootloader_get_version( ctx, &version_bootloader );
    if ( 0xDF == version_bootloader.type )
    {
        lr1110_bootloader_erase_flash( ctx );
        
        lr1110_bootloader_pin_t      pin      = { 0x00 };
        lr1110_bootloader_chip_eui_t chip_eui = { 0x00 };
        lr1110_bootloader_join_eui_t join_eui = { 0x00 };
        
        lr1110_bootloader_read_pin( ctx, pin );
        lr1110_bootloader_read_chip_eui( ctx, chip_eui );
        lr1110_bootloader_read_join_eui( ctx, join_eui );
        
        lr1110_bootloader_write_flash_encrypted_full( ctx, 0, buffer, length );
        
        lr1110_bootloader_reboot( ctx, false );
        
    #if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
        lr1110_system_version_t version_trx = { 0x00 };
        lr1110_system_uid_t     uid         = { 0x00 };

        lr1110_system_get_version( ctx, &version_trx );

        lr1110_system_read_uid( ctx, uid );

        if( version_trx.fw == fw_expected )
        {
            return LRIOT_OK;
        }
    #else
        lr1110_modem_version_t version_modem = { 0 };
        Delay_1sec ( );
        Delay_1sec ( );
        lr1110_modem_get_version( ctx, &version_modem );
        uint32_t fw_version = ( ( uint32_t )( version_modem.functionality ) << 24 ) + version_modem.firmware;
        if ( fw_version == fw_expected )
        {
            return LRIOT_OK;
        }
    #endif
    }
    return LRIOT_ERROR;
}

/* --- EOF ------------------------------------------------------------------ */
