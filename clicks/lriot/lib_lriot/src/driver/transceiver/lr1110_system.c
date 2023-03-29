/*!
 * @file      lr1110_system.c
 *
 * @brief     System driver implementation for LR1110
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

#include <stdlib.h>

#include "transceiver/lr1110_system.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

#define LR1110_SYSTEM_GET_IRQ_STATUS_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_GET_VERSION_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_GET_ERRORS_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_CLEAR_ERRORS_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_CALIBRATE_CMD_LENGTH ( 2 + 1 )
#define LR1110_SYSTEM_SET_REGMODE_CMD_LENGTH ( 2 + 1 )
#define LR1110_SYSTEM_CALIBRATE_IMAGE_CMD_LENGTH ( 2 + 2 )
#define LR1110_SYSTEM_SET_DIO_AS_RF_SWITCH_CMD_LENGTH ( 2 + 8 )
#define LR1110_SYSTEM_SET_DIO_IRQ_PARAMS_CMD_LENGTH ( 2 + 8 )
#define LR1110_SYSTEM_CLEAR_IRQ_CMD_LENGTH ( 2 + 4 )
#define LR1110_SYSTEM_CFG_LFCLK_CMD_LENGTH ( 2 + 1 )
#define LR1110_SYSTEM_SET_TCXO_MODE_CMD_LENGTH ( 2 + 4 )
#define LR1110_SYSTEM_REBOOT_CMD_LENGTH ( 2 + 1 )
#define LR1110_SYSTEM_GET_VBAT_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_GET_TEMP_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_SET_SLEEP_CMD_LENGTH ( 2 + 5 )
#define LR1110_SYSTEM_SET_STANDBY_CMD_LENGTH ( 2 + 1 )
#define LR1110_SYSTEM_SET_FS_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_ERASE_INFOPAGE_CMD_LENGTH ( 2 + 1 )
#define LR1110_SYSTEM_WRITE_INFOPAGE_CMD_LENGTH ( 2 + 3 )
#define LR1110_SYSTEM_READ_INFOPAGE_CMD_LENGTH ( 2 + 4 )
#define LR1110_SYSTEM_READ_UID_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_READ_JOIN_EUI_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_READ_PIN_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_READ_PIN_CUSTOM_EUI_CMD_LENGTH ( LR1110_SYSTEM_READ_PIN_CMD_LENGTH + 17 )
#define LR1110_SYSTEM_GET_RANDOM_CMD_LENGTH ( 2 )
#define LR1110_SYSTEM_ENABLE_SPI_CRC_CMD_LENGTH ( 3 )
#define LR1110_SYSTEM_DRIVE_DIO_IN_SLEEP_MODE_CMD_LENGTH ( 3 )

#define LR1110_SYSTEM_GET_STATUS_DIRECT_READ_LENGTH ( 6 )

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*!
 * @brief Operating codes for system-related operations
 */
enum
{
    LR1110_SYSTEM_GET_STATUS_OC              = 0x0100,
    LR1110_SYSTEM_GET_VERSION_OC             = 0x0101,
    LR1110_SYSTEM_GET_ERRORS_OC              = 0x010D,
    LR1110_SYSTEM_CLEAR_ERRORS_OC            = 0x010E,
    LR1110_SYSTEM_CALIBRATE_OC               = 0x010F,
    LR1110_SYSTEM_SET_REGMODE_OC             = 0x0110,
    LR1110_SYSTEM_CALIBRATE_IMAGE_OC         = 0x0111,
    LR1110_SYSTEM_SET_DIO_AS_RF_SWITCH_OC    = 0x0112,
    LR1110_SYSTEM_SET_DIOIRQPARAMS_OC        = 0x0113,
    LR1110_SYSTEM_CLEAR_IRQ_OC               = 0x0114,
    LR1110_SYSTEM_CFG_LFCLK_OC               = 0x0116,
    LR1110_SYSTEM_SET_TCXO_MODE_OC           = 0x0117,
    LR1110_SYSTEM_REBOOT_OC                  = 0x0118,
    LR1110_SYSTEM_GET_VBAT_OC                = 0x0119,
    LR1110_SYSTEM_GET_TEMP_OC                = 0x011A,
    LR1110_SYSTEM_SET_SLEEP_OC               = 0x011B,
    LR1110_SYSTEM_SET_STANDBY_OC             = 0x011C,
    LR1110_SYSTEM_SET_FS_OC                  = 0x011D,
    LR1110_SYSTEM_GET_RANDOM_OC              = 0x0120,
    LR1110_SYSTEM_ERASE_INFOPAGE_OC          = 0x0121,
    LR1110_SYSTEM_WRITE_INFOPAGE_OC          = 0x0122,
    LR1110_SYSTEM_READ_INFOPAGE_OC           = 0x0123,
    LR1110_SYSTEM_READ_UID_OC                = 0x0125,
    LR1110_SYSTEM_READ_JOIN_EUI_OC           = 0x0126,
    LR1110_SYSTEM_READ_PIN_OC                = 0x0127,
    LR1110_SYSTEM_ENABLE_SPI_CRC_OC          = 0x0128,
    LR1110_SYSTEM_DRIVE_DIO_IN_SLEEP_MODE_OC = 0x012A
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
 * @brief Fill stat1 structure with data from stat1_byte
 *
 * @param [in]  stat1_byte stat1 byte
 * @param [out] stat1      stat1 structure
 */
static void lr1110_system_convert_stat1_byte_to_enum( uint8_t stat1_byte, lr1110_system_stat1_t* stat1 );

/*!
 * @brief Fill stat2 structure with data from stat2_byte
 *
 * @param [in]  stat2_byte stat2 byte
 * @param [out] stat2      stat2 structure
 */
static void lr1110_system_convert_stat2_byte_to_enum( uint8_t stat2_byte, lr1110_system_stat2_t* stat2 );

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

err_t lr1110_system_get_irq_status( lriot_t *ctx, lr1110_system_irq_mask_t* irq_status )
{
    return lr1110_system_get_status( ctx, 0, 0, irq_status );
}

err_t lr1110_system_reset( lriot_t *ctx )
{
    return lr1110_hal_reset( ctx );
}

err_t lr1110_system_get_status( lriot_t *ctx, lr1110_system_stat1_t* stat1, lr1110_system_stat2_t* stat2, 
                                lr1110_system_irq_mask_t* irq_status )
{
    uint8_t data_buf[LR1110_SYSTEM_GET_STATUS_DIRECT_READ_LENGTH];
    err_t status;

    status = lr1110_hal_direct_read( ctx, data_buf, LR1110_SYSTEM_GET_STATUS_DIRECT_READ_LENGTH );

    if( status == LRIOT_OK )
    {
        lr1110_system_convert_stat1_byte_to_enum( data_buf[0], stat1 );
        lr1110_system_convert_stat2_byte_to_enum( data_buf[1], stat2 );
        if( irq_status != 0 )
        {
            *irq_status = ( ( lr1110_system_irq_mask_t ) data_buf[2] << 24 ) +
                          ( ( lr1110_system_irq_mask_t ) data_buf[3] << 16 ) +
                          ( ( lr1110_system_irq_mask_t ) data_buf[4] << 8 ) + ( ( lr1110_system_irq_mask_t ) data_buf[5] << 0 );
        }
    }

    return status;
}

err_t lr1110_system_clear_reset_status_info( lriot_t *ctx )
{
    uint8_t cbuffer[2] = {
        ( uint8_t )( LR1110_SYSTEM_GET_STATUS_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_GET_STATUS_OC >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, sizeof( cbuffer ), 0, 0 );
}

err_t lr1110_system_get_version( lriot_t *ctx, lr1110_system_version_t* version )
{
    uint8_t cbuffer[LR1110_SYSTEM_GET_VERSION_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_GET_VERSION_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_GET_VERSION_OC >> 0 )
    };
    uint8_t rbuffer[LR1110_SYSTEM_VERSION_LENGTH] = { 0x00 };

    err_t status = lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_GET_VERSION_CMD_LENGTH, 
                                    rbuffer, LR1110_SYSTEM_VERSION_LENGTH );

    if( status == LRIOT_OK )
    {
        version->hw   = rbuffer[0];
        version->type = rbuffer[1];
        version->fw   = ( ( uint16_t ) rbuffer[2] << 8 ) + ( uint16_t ) rbuffer[3];
    }

    return status;
}

err_t lr1110_system_get_errors( lriot_t *ctx, lr1110_system_errors_t* errors )
{
    uint8_t cbuffer[LR1110_SYSTEM_GET_ERRORS_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_GET_ERRORS_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_GET_ERRORS_OC >> 0 )
    };
    uint8_t rbuffer[sizeof( errors )] = { 0x00 };

    err_t status = lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_GET_ERRORS_CMD_LENGTH, 
                                    rbuffer, sizeof( *errors ) );

    if( status == LRIOT_OK )
    {
        *errors = ( ( uint16_t ) rbuffer[0] << 8 ) + ( uint16_t ) rbuffer[1];
    }

    return status;
}

err_t lr1110_system_clear_errors( lriot_t *ctx )
{
    uint8_t cbuffer[LR1110_SYSTEM_CLEAR_ERRORS_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_CLEAR_ERRORS_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_CLEAR_ERRORS_OC >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_CLEAR_ERRORS_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_calibrate( lriot_t *ctx, uint8_t calib_param )
{
    uint8_t cbuffer[LR1110_SYSTEM_CALIBRATE_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_CALIBRATE_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_CALIBRATE_OC >> 0 ),
        calib_param
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_CALIBRATE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_set_reg_mode( lriot_t *ctx, lr1110_system_reg_mode_t reg_mode )
{
    uint8_t cbuffer[LR1110_SYSTEM_SET_REGMODE_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_SET_REGMODE_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_SET_REGMODE_OC >> 0 ),
        ( uint8_t ) reg_mode
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_SET_REGMODE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_calibrate_image( lriot_t *ctx, uint8_t freq1, uint8_t freq2 )
{
    uint8_t cbuffer[LR1110_SYSTEM_CALIBRATE_IMAGE_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_CALIBRATE_IMAGE_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_CALIBRATE_IMAGE_OC >> 0 ),
        freq1,
        freq2
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_CALIBRATE_IMAGE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_calibrate_image_in_mhz( lriot_t *ctx, uint16_t freq1_in_mhz, uint16_t freq2_in_mhz )
{
    // Perform a floor() to get a value for freq1 corresponding to a frequency lower than or equal to freq1_in_mhz
    uint8_t freq1 = freq1_in_mhz / LR1110_SYSTEM_IMAGE_CALIBRATION_STEP_IN_MHZ;

    // Perform a ceil() to get a value for freq2 corresponding to a frequency higher than or equal to freq2_in_mhz
    uint8_t freq2 = ( freq2_in_mhz + LR1110_SYSTEM_IMAGE_CALIBRATION_STEP_IN_MHZ - 1 ) / LR1110_SYSTEM_IMAGE_CALIBRATION_STEP_IN_MHZ;

    return lr1110_system_calibrate_image( ctx, freq1, freq2 );
}

err_t lr1110_system_set_dio_as_rf_switch( lriot_t *ctx, lr1110_system_rfswitch_cfg_t* rf_switch_cfg )
{
    uint8_t cbuffer[LR1110_SYSTEM_SET_DIO_AS_RF_SWITCH_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_SET_DIO_AS_RF_SWITCH_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_SET_DIO_AS_RF_SWITCH_OC >> 0 ),
        rf_switch_cfg->enable,
        rf_switch_cfg->standby,
        rf_switch_cfg->rx_mode,
        rf_switch_cfg->tx_mode,
        rf_switch_cfg->tx_hp,
        rf_switch_cfg->tx_hf,
        rf_switch_cfg->gnss,
        rf_switch_cfg->wifi
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_SET_DIO_AS_RF_SWITCH_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_set_dio_irq_params( lriot_t *ctx, uint32_t irqs_to_enable_dio1, uint32_t irqs_to_enable_dio2 )
{
    uint8_t cbuffer[LR1110_SYSTEM_SET_DIO_IRQ_PARAMS_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_SET_DIOIRQPARAMS_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_SET_DIOIRQPARAMS_OC >> 0 ),
        ( uint8_t )( irqs_to_enable_dio1 >> 24 ),
        ( uint8_t )( irqs_to_enable_dio1 >> 16 ),
        ( uint8_t )( irqs_to_enable_dio1 >> 8 ),
        ( uint8_t )( irqs_to_enable_dio1 >> 0 ),
        ( uint8_t )( irqs_to_enable_dio2 >> 24 ),
        ( uint8_t )( irqs_to_enable_dio2 >> 16 ),
        ( uint8_t )( irqs_to_enable_dio2 >> 8 ),
        ( uint8_t )( irqs_to_enable_dio2 >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_SET_DIO_IRQ_PARAMS_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_clear_irq_status( lriot_t *ctx, lr1110_system_irq_mask_t irqs_to_clear )
{
    uint8_t cbuffer[LR1110_SYSTEM_CLEAR_IRQ_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_CLEAR_IRQ_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_CLEAR_IRQ_OC >> 0 ),
        ( uint8_t )( irqs_to_clear >> 24 ),
        ( uint8_t )( irqs_to_clear >> 16 ),
        ( uint8_t )( irqs_to_clear >> 8 ),
        ( uint8_t )( irqs_to_clear >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_CLEAR_IRQ_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_get_and_clear_irq_status( lriot_t *ctx, lr1110_system_irq_mask_t* irq )
{
    lr1110_system_irq_mask_t lr1110_irq_mask = LR1110_SYSTEM_IRQ_NONE;

    err_t status = lr1110_system_get_irq_status( ctx, &lr1110_irq_mask );

    if( ( status == LRIOT_OK ) && ( lr1110_irq_mask != 0 ) )
    {
        status = lr1110_system_clear_irq_status( ctx, lr1110_irq_mask );
    }
    if( ( status == LRIOT_OK ) && ( irq != 0 ) )
    {
        *irq = lr1110_irq_mask;
    }

    return status;
}

err_t lr1110_system_cfg_lfclk( lriot_t *ctx, lr1110_system_lfclk_cfg_t lfclock_cfg, bool wait_for_32k_ready )
{
    uint8_t cbuffer[LR1110_SYSTEM_CFG_LFCLK_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_CFG_LFCLK_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_CFG_LFCLK_OC >> 0 ),
        ( uint8_t )( lfclock_cfg | ( wait_for_32k_ready << 2 ) )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_CFG_LFCLK_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_set_tcxo_mode( lriot_t *ctx, lr1110_system_tcxo_supply_voltage_t tune, uint32_t timeout )
{
    uint8_t cbuffer[LR1110_SYSTEM_SET_TCXO_MODE_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_SET_TCXO_MODE_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_SET_TCXO_MODE_OC >> 0 ),
        ( uint8_t ) tune,
        ( uint8_t )( timeout >> 16 ),
        ( uint8_t )( timeout >> 8 ),
        ( uint8_t )( timeout >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_SET_TCXO_MODE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_reboot( lriot_t *ctx, bool stay_in_bootloader )
{
    uint8_t cbuffer[LR1110_SYSTEM_REBOOT_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_REBOOT_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_REBOOT_OC >> 0 ),
        ( ( stay_in_bootloader == true ) ? 0x03 : 0x00 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_REBOOT_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_get_vbat( lriot_t *ctx, uint8_t* vbat )
{
    uint8_t cbuffer[LR1110_SYSTEM_GET_VBAT_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_GET_VBAT_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_GET_VBAT_OC >> 0 )
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_GET_VBAT_CMD_LENGTH, vbat, sizeof( *vbat ) );
}

err_t lr1110_system_get_temp( lriot_t *ctx, uint16_t* temp )
{
    uint8_t cbuffer[LR1110_SYSTEM_GET_TEMP_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_GET_TEMP_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_GET_TEMP_OC >> 0 )
    };
    uint8_t rbuffer[sizeof( uint16_t )] = { 0x00 };

    err_t status = lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_GET_TEMP_CMD_LENGTH, rbuffer, sizeof( uint16_t ) );

    if( status == LRIOT_OK )
    {
        *temp = ( ( uint16_t ) rbuffer[0] << 8 ) + ( uint16_t ) rbuffer[1];
    }

    return status;
}

err_t lr1110_system_set_sleep( lriot_t *ctx, lr1110_system_sleep_cfg_t sleep_cfg, uint32_t sleep_time )
{
    uint8_t cbuffer[LR1110_SYSTEM_SET_SLEEP_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_SET_SLEEP_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_SET_SLEEP_OC >> 0 ),
        ( sleep_cfg.is_rtc_timeout << 1 ) + sleep_cfg.is_warm_start,
        ( uint8_t )( sleep_time >> 24 ),
        ( uint8_t )( sleep_time >> 16 ),
        ( uint8_t )( sleep_time >> 8 ),
        ( uint8_t )( sleep_time >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_SET_SLEEP_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_set_standby( lriot_t *ctx, lr1110_system_standby_cfg_t standby_cfg )
{
    uint8_t cbuffer[LR1110_SYSTEM_SET_STANDBY_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_SET_STANDBY_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_SET_STANDBY_OC >> 0 ),
        ( uint8_t ) standby_cfg
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_SET_STANDBY_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_wakeup( lriot_t *ctx )
{
    return lr1110_hal_wakeup( ctx );
}

err_t lr1110_system_set_fs( lriot_t *ctx )
{
    uint8_t cbuffer[LR1110_SYSTEM_SET_FS_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_SET_FS_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_SET_FS_OC >> 0 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_SET_FS_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_erase_infopage( lriot_t *ctx, lr1110_system_infopage_id_t infopage_id )
{
    uint8_t cbuffer[LR1110_SYSTEM_ERASE_INFOPAGE_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_ERASE_INFOPAGE_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_ERASE_INFOPAGE_OC >> 0 ),
        ( uint8_t ) infopage_id
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_ERASE_INFOPAGE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_write_infopage( lriot_t *ctx, lr1110_system_infopage_id_t infopage_id,
                                    uint16_t address, uint32_t* data_buf, uint8_t length )
{
    uint8_t cbuffer[LR1110_SYSTEM_WRITE_INFOPAGE_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_WRITE_INFOPAGE_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_WRITE_INFOPAGE_OC >> 0 ),
        ( uint8_t ) infopage_id,
        ( uint8_t )( address >> 8 ),
        ( uint8_t )( address >> 0 )
    };
    uint8_t cdata[256];

    for( uint16_t index = 0; index < length; index++ )
    {
        uint8_t* cdata_local = &cdata[index * sizeof( uint32_t )];

        cdata_local[0] = ( uint8_t )( data_buf[index] >> 24 );
        cdata_local[1] = ( uint8_t )( data_buf[index] >> 16 );
        cdata_local[2] = ( uint8_t )( data_buf[index] >> 8 );
        cdata_local[3] = ( uint8_t )( data_buf[index] >> 0 );
    }

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_WRITE_INFOPAGE_CMD_LENGTH, cdata, 
                             length * sizeof( uint32_t ) );
}

err_t lr1110_system_read_infopage( lriot_t *ctx, lr1110_system_infopage_id_t infopage_id,
                                   uint16_t address, uint32_t* data_buf, uint8_t length )
{
    uint8_t cbuffer[LR1110_SYSTEM_READ_INFOPAGE_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_READ_INFOPAGE_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_READ_INFOPAGE_OC >> 0 ),
        ( uint8_t ) infopage_id,
        ( uint8_t )( address >> 8 ),
        ( uint8_t )( address >> 0 ),
        length
    };

    err_t status = lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_READ_INFOPAGE_CMD_LENGTH, 
                                    ( uint8_t* ) data_buf, length * sizeof( *data_buf ) );

    if( status == LRIOT_OK )
    {
        for( uint8_t index = 0; index < length; index++ )
        {
            uint8_t* buffer_local = ( uint8_t* ) &data_buf[index];

            data_buf[index] = ( ( uint32_t ) buffer_local[0] << 24 ) + ( ( uint32_t ) buffer_local[1] << 16 ) +
                              ( ( uint32_t ) buffer_local[2] << 8 ) + ( ( uint32_t ) buffer_local[3] << 0 );
        }
    }

    return status;
}

err_t lr1110_system_read_uid( lriot_t *ctx, lr1110_system_uid_t unique_identifier )
{
    uint8_t cbuffer[LR1110_SYSTEM_READ_UID_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_READ_UID_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_READ_UID_OC >> 0 )
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_READ_UID_CMD_LENGTH, 
                            unique_identifier, LR1110_SYSTEM_UID_LENGTH );
}

err_t lr1110_system_read_join_eui( lriot_t *ctx, lr1110_system_join_eui_t join_eui )
{
    uint8_t cbuffer[LR1110_SYSTEM_READ_JOIN_EUI_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_READ_JOIN_EUI_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_READ_JOIN_EUI_OC >> 0 )
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_READ_JOIN_EUI_CMD_LENGTH, 
                            join_eui, LR1110_SYSTEM_JOIN_EUI_LENGTH );
}

err_t lr1110_system_read_pin( lriot_t *ctx, lr1110_system_pin_t pin )
{
    uint8_t cbuffer[LR1110_SYSTEM_READ_PIN_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_READ_PIN_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_READ_PIN_OC >> 0 )
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_READ_PIN_CMD_LENGTH, pin, LR1110_SYSTEM_PIN_LENGTH );
}

err_t lr1110_system_read_pin_custom_eui( lriot_t *ctx, lr1110_system_uid_t device_eui, 
                                         lr1110_system_join_eui_t join_eui, uint8_t rfu, lr1110_system_pin_t pin )
{
    uint8_t cbuffer[LR1110_SYSTEM_READ_PIN_CUSTOM_EUI_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_READ_PIN_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_READ_PIN_OC >> 0 ),
        device_eui[0],
        device_eui[1],
        device_eui[2],
        device_eui[3],
        device_eui[4],
        device_eui[5],
        device_eui[6],
        device_eui[7],
        join_eui[0],
        join_eui[1],
        join_eui[2],
        join_eui[3],
        join_eui[4],
        join_eui[5],
        join_eui[6],
        join_eui[7],
        rfu
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_READ_PIN_CUSTOM_EUI_CMD_LENGTH, pin, LR1110_SYSTEM_PIN_LENGTH );
}

err_t lr1110_system_get_random_number( lriot_t *ctx, uint32_t* random_number )
{
    uint8_t cbuffer[LR1110_SYSTEM_GET_RANDOM_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_GET_RANDOM_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_GET_RANDOM_OC >> 0 )
    };

    return lr1110_hal_read( ctx, cbuffer, LR1110_SYSTEM_GET_RANDOM_CMD_LENGTH,
                            ( uint8_t* ) random_number, sizeof( uint32_t ) );
}

err_t lr1110_system_enable_spi_crc( lriot_t *ctx, bool enable_crc )
{
    uint8_t cbuffer[LR1110_SYSTEM_ENABLE_SPI_CRC_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_ENABLE_SPI_CRC_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_ENABLE_SPI_CRC_OC >> 0 ),
        ( ( enable_crc == true ) ? 0x01 : 0x00 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_ENABLE_SPI_CRC_CMD_LENGTH, 0, 0 );
}

err_t lr1110_system_drive_dio_in_sleep_mode( lriot_t *ctx, bool enable_drive )
{
    uint8_t cbuffer[LR1110_SYSTEM_DRIVE_DIO_IN_SLEEP_MODE_CMD_LENGTH] = {
        ( uint8_t )( LR1110_SYSTEM_DRIVE_DIO_IN_SLEEP_MODE_OC >> 8 ),
        ( uint8_t )( LR1110_SYSTEM_DRIVE_DIO_IN_SLEEP_MODE_OC >> 0 ),
        ( ( enable_drive == true ) ? 0x01 : 0x00 )
    };

    return lr1110_hal_write( ctx, cbuffer, LR1110_SYSTEM_DRIVE_DIO_IN_SLEEP_MODE_CMD_LENGTH, 0, 0 );
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

static void lr1110_system_convert_stat1_byte_to_enum( uint8_t stat1_byte, lr1110_system_stat1_t* stat1 )
{
    if( stat1 != 0 )
    {
        stat1->is_interrupt_active = ( ( stat1_byte & 0x01 ) != 0 ) ? true : false;
        stat1->command_status      = ( stat1_byte >> 1 );
    }
}

static void lr1110_system_convert_stat2_byte_to_enum( uint8_t stat2_byte, lr1110_system_stat2_t* stat2 )
{
    if( stat2 != 0 )
    {
        stat2->is_running_from_flash = ( ( stat2_byte & 0x01 ) != 0 ) ? true : false;
        stat2->chip_mode             = ( ( stat2_byte & 0x0F ) >> 1 );
        stat2->reset_status          = ( ( stat2_byte & 0xF0 ) >> 4 );
    }
}

/* --- EOF ------------------------------------------------------------------ */
