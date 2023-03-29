/*!
 * @file      lr1110_modem_system.c
 *
 * @brief     System driver implementation for LR1110 modem
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
#include "modem/lr1110_modem_system.h"
#include "modem/lr1110_modem_hal.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

/*!
 * @brief Command buffer length for command Write Regmem32
 */
#define LR1110_MODEM_SYSTEM_WRITE_REGMEM32_CMD_LEN ( 2 + 4 )

/*!
 * @brief Command buffer length for command Read Regmem32
 */
#define LR1110_MODEM_SYSTEM_READ_REGMEM32_CMD_LEN ( 2 + 4 + 1 )

/*!
 * @brief Command buffer length for command System calibrate
 */
#define LR1110_MODEM_SYSTEM_CALIBRATE_CMD_LEN ( 2 + 1 )

/*!
 * @brief Command buffer length for command Set regulator mode
 */
#define LR1110_MODEM_SYSTEM_SET_REGMODE_CMD_LENGTH ( 2 + 1 )

/*!
 * @brief Command buffer length for command Set DIO as RF switch
 */
#define LR1110_MODEM_SYSTEM_SET_DIO_AS_RF_SWITCH_CMD_LENGTH ( 2 + 8 )

/*!
 * @brief Command buffer length for command Configuration LFCLK
 */
#define LR1110_MODEM_SYSTEM_CONFIG_LFCLK_CMD_LENGTH ( 2 + 1 )

/*!
 * @brief Command buffer length for command Set TCXO mode
 */
#define LR1110_MODEM_SYSTEM_SET_TCXO_MODE_CMD_LENGTH ( 2 + 4 )

/*!
 * @brief Command buffer length for command Reboot
 */
#define LR1110_MODEM_SYSTEM_REBOOT_CMD_LENGTH ( 2 + 1 )

/*!
 * @brief Size of data buffer for Write regmem32
 */
#define LR1110_MODEM_SYSTEM_REGMEM_BUFFER_SIZE_MAX ( 256 )

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*!
 * @brief Operation code for system commands
 */
enum
{
    LR1110_MODEM_SYSTEM_WRITE_REG_MEM_32_CMD     = 0x05,
    LR1110_MODEM_SYSTEM_READ_REG_MEM_32_CMD      = 0x06,
    LR1110_MODEM_SYSTEM_CALIBRATE_CMD            = 0x0F,
    LR1110_MODEM_SYSTEM_SET_REG_MODE_CMD         = 0x10,
    LR1110_MODEM_SYSTEM_SET_DIO_AS_RF_SWITCH_CMD = 0x12,
    LR1110_MODEM_SYSTEM_CONFIG_LF_CLOCK_CMD      = 0x16,
    LR1110_MODEM_SYSTEM_SET_TCXO_MODE_CMD        = 0x17,
    LR1110_MODEM_SYSTEM_REBOOT_CMD               = 0x18,
};

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

err_t lr1110_modem_system_write_regmem32( lriot_t *ctx, uint32_t address, uint32_t* buffer, uint8_t length )
{
    uint8_t cbuffer[LR1110_MODEM_SYSTEM_WRITE_REGMEM32_CMD_LEN];
    uint8_t cdata[LR1110_MODEM_SYSTEM_REGMEM_BUFFER_SIZE_MAX] = { 0 };

    cbuffer[0] = LR1110_MODEM_GROUP_ID_SYSTEM;
    cbuffer[1] = LR1110_MODEM_SYSTEM_WRITE_REG_MEM_32_CMD;

    cbuffer[2] = ( uint8_t )( address >> 24 );
    cbuffer[3] = ( uint8_t )( address >> 16 );
    cbuffer[4] = ( uint8_t )( address >> 8 );
    cbuffer[5] = ( uint8_t )( address >> 0 );

    for( uint16_t index = 0; index < length; index++ )
    {
        uint8_t* cdata_local = &cdata[index * sizeof( uint32_t )];

        cdata_local[0] = ( uint8_t )( buffer[index] >> 24 );
        cdata_local[1] = ( uint8_t )( buffer[index] >> 16 );
        cdata_local[2] = ( uint8_t )( buffer[index] >> 8 );
        cdata_local[3] = ( uint8_t )( buffer[index] >> 0 );
    }

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_SYSTEM_WRITE_REGMEM32_CMD_LEN, 
                                   cdata, length * sizeof( uint32_t ) );
}

err_t lr1110_modem_system_read_regmem32( lriot_t *ctx, uint32_t address, uint32_t* buffer, uint8_t length )
{
    uint8_t cbuffer[LR1110_MODEM_SYSTEM_READ_REGMEM32_CMD_LEN];
    err_t rc;

    cbuffer[0] = LR1110_MODEM_GROUP_ID_SYSTEM;
    cbuffer[1] = LR1110_MODEM_SYSTEM_READ_REG_MEM_32_CMD;

    cbuffer[2] = ( uint8_t )( address >> 24 );
    cbuffer[3] = ( uint8_t )( address >> 16 );
    cbuffer[4] = ( uint8_t )( address >> 8 );
    cbuffer[5] = ( uint8_t )( address >> 0 );

    cbuffer[6] = length;

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_SYSTEM_READ_REGMEM32_CMD_LEN, 
                                ( uint8_t* ) buffer, length * sizeof( uint32_t ) );

    for( uint8_t index = 0; index < length; index++ )
    {
        uint8_t* buffer_local = ( uint8_t* ) &buffer[index];

        buffer[index] = ( ( uint32_t ) buffer_local[0] << 24 ) + ( ( uint32_t ) buffer_local[1] << 16 ) +
                        ( ( uint32_t ) buffer_local[2] << 8 ) + ( ( uint32_t ) buffer_local[3] << 0 );
    }

    return rc;
}

err_t lr1110_modem_system_calibrate( lriot_t *ctx, uint8_t calib_param )
{
    uint8_t cbuffer[LR1110_MODEM_SYSTEM_CALIBRATE_CMD_LEN];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_SYSTEM;
    cbuffer[1] = LR1110_MODEM_SYSTEM_CALIBRATE_CMD;

    cbuffer[2] = calib_param;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_SYSTEM_CALIBRATE_CMD_LEN, 0, 0 );
}

err_t lr1110_modem_system_set_reg_mode( lriot_t *ctx, lr1110_modem_system_reg_mode_t reg_mode )
{
    uint8_t cbuffer[LR1110_MODEM_SYSTEM_SET_REGMODE_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_SYSTEM;
    cbuffer[1] = LR1110_MODEM_SYSTEM_SET_REG_MODE_CMD;

    cbuffer[2] = ( uint8_t ) reg_mode;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_SYSTEM_SET_REGMODE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_system_set_dio_as_rf_switch( lriot_t *ctx, lr1110_modem_system_rf_switch_cfg_t* rf_switch_cfg )
{
    uint8_t cbuffer[LR1110_MODEM_SYSTEM_SET_DIO_AS_RF_SWITCH_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_SYSTEM;
    cbuffer[1] = LR1110_MODEM_SYSTEM_SET_DIO_AS_RF_SWITCH_CMD;

    cbuffer[2] = rf_switch_cfg->enable;
    cbuffer[3] = rf_switch_cfg->standby;
    cbuffer[4] = rf_switch_cfg->rx_mode;
    cbuffer[5] = rf_switch_cfg->tx_mode;
    cbuffer[6] = rf_switch_cfg->tx_hp;
    cbuffer[7] = rf_switch_cfg->tx_hf;
    cbuffer[8] = rf_switch_cfg->gnss;
    cbuffer[9] = rf_switch_cfg->wifi;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_SYSTEM_SET_DIO_AS_RF_SWITCH_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_system_cfg_lfclk( lriot_t *ctx, lr1110_modem_system_lfclk_cfg_t lfclock_cfg, bool wait_for_32k_ready )
{
    uint8_t cbuffer[LR1110_MODEM_SYSTEM_CONFIG_LFCLK_CMD_LENGTH];
    uint8_t config = lfclock_cfg | ( wait_for_32k_ready << 2 );

    cbuffer[0] = LR1110_MODEM_GROUP_ID_SYSTEM;
    cbuffer[1] = LR1110_MODEM_SYSTEM_CONFIG_LF_CLOCK_CMD;

    cbuffer[2] = config;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_SYSTEM_CONFIG_LFCLK_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_system_set_tcxo_mode( lriot_t *ctx, lr1110_modem_system_tcxo_supply_voltage_t tune, uint32_t timeout )
{
    uint8_t cbuffer[LR1110_MODEM_SYSTEM_SET_TCXO_MODE_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_SYSTEM;
    cbuffer[1] = LR1110_MODEM_SYSTEM_SET_TCXO_MODE_CMD;

    cbuffer[2] = ( uint8_t ) tune;

    cbuffer[3] = ( uint8_t )( timeout >> 16 );
    cbuffer[4] = ( uint8_t )( timeout >> 8 );
    cbuffer[5] = ( uint8_t )( timeout >> 0 );

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_SYSTEM_SET_TCXO_MODE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_system_reboot( lriot_t *ctx, bool stay_in_bootloader )
{
    uint8_t cbuffer[LR1110_MODEM_SYSTEM_REBOOT_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_SYSTEM;
    cbuffer[1] = LR1110_MODEM_SYSTEM_REBOOT_CMD;

    cbuffer[2] = ( stay_in_bootloader == true ) ? 0x03 : 0x00;

    return lr1110_modem_hal_write_without_rc( ctx, cbuffer, LR1110_MODEM_SYSTEM_REBOOT_CMD_LENGTH, 0, 0 );
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

/* --- EOF ------------------------------------------------------------------ */
