/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
 * @file ble9.c
 * @brief This file contains API definitions for BLE 9 Click driver.
 */

#include "ble9.h"

// ------------------------------------------------ PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Generic BLE9 click error check function.
 * Reads @b read_n_elements number of elements, places them in
 * @b ret_val_check array if any value is needed( handle for example ),
 * and checks @b check_var_num element for return value.
 *
 * @param ctx BLE9 click object.
 * @param read_n_elements Number of elements to read.
 * @param check_char_num Ordinal number of element to check.
 * @param ret_val_check Array address.
 * @return true
 * @return false
 *
 * @warning Take into consideration that different functionalities
 * have different return values and different number of bytes.
 */
static uint8_t ble9_generic_err_check ( ble9_t *ctx, uint8_t read_n_elements,
                                        uint8_t check_char_num, uint8_t *ret_val_check );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ble9_cfg_setup ( ble9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Module settings
    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t ble9_init ( ble9_t *ctx, ble9_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    return BLE9_OK;
}

err_t ble9_sys_hello ( ble9_t *ctx ) 
{
    uint8_t tmp_array[ 6 ] = { 0 };
    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_HELLO_ID );
    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_sys_get_version ( ble9_t *ctx ) 
{
    uint8_t tmp_array[ 22 ] = { 0 };

    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_GET_VERSION_ID );
    Delay_10ms ( );
    if ( 22 == uart_read ( &ctx->uart, tmp_array, 22 ) ) 
    {
        ctx->ble9_version.version_major = ( ( uint16_t ) tmp_array[ 5 ] << 8 ) | tmp_array[ 6 ];
        ctx->ble9_version.version_minor = ( ( uint16_t ) tmp_array[ 7 ] << 8 ) | tmp_array[ 8 ];
        ctx->ble9_version.version_patch = ( ( uint16_t ) tmp_array[ 9 ] << 8 ) | tmp_array[ 10 ];
        ctx->ble9_version.version_build = ( ( uint16_t ) tmp_array[ 11 ] << 8 ) | tmp_array[ 12 ];
        ctx->ble9_version.version_bootloader = ( ( uint32_t ) tmp_array[ 14 ] << 24 ) | ( ( uint32_t ) tmp_array[ 15 ] << 16 ) | 
                                               ( ( uint16_t ) tmp_array[ 16 ] << 8 ) | tmp_array[ 17 ];
        ctx->ble9_version.version_hash = ( ( uint32_t ) tmp_array[ 18 ] << 24 ) | ( ( uint32_t ) tmp_array[ 19 ] << 16 ) | 
                                         ( ( uint16_t ) tmp_array[ 20 ] << 8 ) | tmp_array[ 21 ];;
        return BLE9_OK;
    } 
    else 
    {
        return BLE9_ERROR;
    }
}

void ble9_sys_set_id_addr ( ble9_t *ctx, uint8_t *address, uint8_t type ) 
{
    uint8_t ble9_settings[ 7 ] = { 0 };
    uint8_t counter = 0;
    for ( counter = 0; counter < 6; counter++ ) 
    {
        ble9_settings[ counter ] = address[ counter ];
    }
    ble9_settings[ counter ] = type;

    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_SET_IDENTITY_ADDRESS_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );
}

err_t ble9_sys_get_id_address ( ble9_t *ctx, uint8_t *data_buf, uint8_t type ) 
{
    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_GET_IDENTITY_ADDRESS_ID );
    ble9_generic_write ( ctx, &type, 1 );
    Delay_1ms ( );
    if ( 13 == uart_read ( &ctx->uart, data_buf, 13 ) ) 
    {
        return BLE9_OK;
    } 
    else 
    {
        return BLE9_ERROR;
    }
}

void ble9_sys_reset ( ble9_t *ctx, ble9_dfu_reset_mode_t reset_mode ) 
{
    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_RESET_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ( uint8_t * ) &reset_mode, 1 );
}

err_t ble9_sys_halt ( ble9_t *ctx, uint8_t halt ) 
{
    uint8_t tmp_array[ 6 ] = { 0 };
    if ( halt > BLE9_SYSTEM_HALT )
    {
        return BLE9_ERROR;
    }
    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_HALT_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, &halt, 1 );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

void ble9_sys_set_tx_power ( ble9_t *ctx, int16_t min_power, int16_t max_power ) 
{
    uint8_t data_buf[ 4 ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( min_power & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( min_power >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( max_power & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( max_power >> 8 ) & 0xFF );
    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_SET_TX_POWER_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, data_buf, 4 );
}

err_t ble9_sys_data_buf_write ( ble9_t *ctx, uint16_t data_len, uint8_t *wr_data ) 
{
    uint8_t tmp_dat = ( uint8_t ) ( ( ( 1 + data_len ) & 0xFF ) << 8 ) + ( ( ( 1 + data_len ) & 0x700 ) >> 8 );
    uint8_t ble9_settings[ 5 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = tmp_dat;
    for ( uint8_t counter = 1; counter <= tmp_dat; counter++ ) 
    {
        ble9_settings[ counter ] = ( uint8_t ) ( ( data_len & ( 0xFF << ( ( counter - 1 ) * 8 ) ) ) >> 
                                                 ( ( counter - 1 ) * 8 ) );
    }

    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_DATA_BUFFER_WRITE_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, tmp_dat + 1 );

    ble9_generic_write( ctx, wr_data, data_len );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_sys_data_buf_clear ( ble9_t *ctx ) 
{
    uint8_t tmp_array[ 6 ] = { 0 };
    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_DATA_BUFFER_CLEAR_ID );
    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_sys_set_soft_timer ( ble9_t  *ctx, ble9_timer_t *ble9_timer ) 
{
    uint8_t ble9_settings[ 6 ] = { 0 };
    uint8_t counter = 0;
    uint8_t tmp_array[ 6 ] = { 0 };

    for ( counter = 0; counter < 3; counter++ ) 
    {
        ble9_settings[ counter ] = ( uint8_t ) ( ( ble9_timer->ble9_timer_time & ( 0xFF << ( counter * 8 ) ) ) >> 
                                                 ( counter * 8 ) );
    }
    // Timer can have a maximum value of 2147483647, which corresponds to about 18.2 hours.
    ble9_settings[ counter++ ] = BLE9_CMD_NULL;  
    ble9_settings[ counter++ ] = ble9_timer->ble9_timer_handle;
    ble9_settings[ counter ]   = ble9_timer->ble9_timer_single_shot;

    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_SET_SOFT_TIMER_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_sys_set_lazy_soft_timer ( ble9_t *ctx, ble9_timer_t *ble9_timer ) 
{
    uint8_t ble9_settings[ 10 ] = { 0 };
    uint8_t counter = 0;
    uint8_t tmp_array[ 6 ] = { 0 };

    for ( counter = 0; counter < 4; counter++ ) 
    {
        ble9_settings[ counter ] = ( uint8_t ) ( ( ble9_timer->ble9_timer_time & ( 0xFF << ( counter * 8 ) ) ) >> 
                                                 ( counter * 8 ) );
        ble9_settings[ counter + 4 ] = ( uint8_t ) ( ( ble9_timer->ble9_timer_slack & ( 0xFF << ( counter * 8 ) ) ) >> 
                                                     ( counter * 8 ) );
    }
    // Timer can have a maximum value of 2147483647, which corresponds to about 18.2 hours.
    ble9_settings[ 3 ] = BLE9_CMD_NULL; 
    ble9_settings[ 8 ] = ble9_timer->ble9_timer_handle;
    ble9_settings[ 9 ] = ble9_timer->ble9_timer_single_shot;

    ble9_send_command ( ctx, BLE9_CMD_SYSTEM_SET_LAZY_SOFT_TIMER_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_gap_set_privacy_mode ( ble9_t *ctx, uint8_t privacy, uint8_t interval_in_minutes ) 
{
    uint8_t ble9_settings[ 2 ] = { privacy, interval_in_minutes };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_send_command ( ctx, BLE9_CMD_GAP_SET_PRIVACY_MODE_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_gap_en_wlist ( ble9_t *ctx, uint8_t enable ) 
{
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_send_command ( ctx, BLE9_CMD_GAP_ENABLE_WHITELISTING_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ( uint8_t * ) &enable, 1 );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_create_id ( ble9_t *ctx ) 
{
    uint8_t status = BLE9_OK;
    uint8_t tmp_array[ 7 ] = { 0 };

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_CREATE_ID );
    status = ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 6, tmp_array );

    /* Map new handle. */
    ctx->ble9_adv_handle = tmp_array[ 5 ];

    return status;
}

err_t ble9_adv_delete_id ( ble9_t *ctx ) 
{
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_DELETE_SET_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, &ctx->ble9_adv_handle, 1 );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_set_timing ( ble9_t *ctx, uint16_t interval_min, uint16_t interval_max, 
                            uint16_t duration, uint8_t maxevents ) 
{
    uint8_t ble9_settings[ 12 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ]  = ctx->ble9_adv_handle;
    ble9_settings[ 1 ]  = interval_min & 0xFF;
    ble9_settings[ 2 ]  = ( interval_min & 0xFF00 ) >> 8;
    ble9_settings[ 5 ]  = interval_max & 0xFF;
    ble9_settings[ 6 ]  = ( interval_max & 0xFF00 ) >> 8;
    ble9_settings[ 9 ]  = duration & 0xFF;
    ble9_settings[ 10 ] = ( duration & 0xFF00 ) >> 8;
    ble9_settings[ 11 ] = maxevents;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_SET_TIMING_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_set_phy ( ble9_t *ctx, ble9_phy_type_t primary_phy, ble9_phy_type_t secondary_phy ) 
{
    uint8_t ble9_settings[ 3 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = primary_phy;
    ble9_settings[ 2 ] = secondary_phy;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_SET_PHY_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_set_channel_map ( ble9_t *ctx, ble9_channel_t channel_map ) 
{
    uint8_t ble9_settings[ 2 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = channel_map;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_SET_CHANNEL_MAP_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_set_tx_power ( ble9_t *ctx, int16_t power, int16_t *set_power ) 
{
    uint8_t ble9_settings[ 3 ] = { 0 };
    uint8_t status = BLE9_OK;
    uint8_t tmp_array[ 8 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = power & 0xFF;
    ble9_settings[ 2 ] = ( power & 0xFF00 ) >> 8;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_SET_TX_POWER_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    status = ble9_generic_err_check( ctx, sizeof ( tmp_array ), 5, tmp_array );
    *set_power = tmp_array[ 6 ];

    return status;
}

err_t ble9_adv_set_report_scan_req ( ble9_t *ctx, uint8_t report_scan_req ) 
{
    uint8_t ble9_settings[ 2 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = report_scan_req;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_SET_REPORT_SCAN_REQUEST_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_set_configuration ( ble9_t *ctx, uint8_t configurations ) 
{
    uint8_t ble9_settings[ 2 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = configurations;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_SET_CONFIGURATION_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_clear_configuration ( ble9_t *ctx, uint8_t configurations ) 
{
    uint8_t ble9_settings[ 2 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = configurations;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_CLEAR_CONFIGURATION_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_set_data ( ble9_t *ctx, ble9_package_type_t packet_type, 
                          uint16_t adv_data_len, uint8_t *adv_data ) 
{
    uint8_t ble9_settings[ 7 ] = { 0 };
    uint8_t dat_num = 0;
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = packet_type;
    for ( uint8_t counter = 5; counter > 1; counter-- ) 
    {
        if ( adv_data_len & ( 0xFF << ( counter - 1) ) ) 
        {
            ble9_settings[ counter + 1 ] = ( packet_type & ( 0xFF << ( counter - 1 ) ) ) >> ( counter - 1 );
            dat_num++;
        }
    }
    ble9_settings[ 2 ] = dat_num;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_SET_DATA_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, 3 + dat_num );
    Delay_1ms ( );

    ble9_generic_write ( ctx, adv_data, adv_data_len );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_set_long_data ( ble9_t *ctx, ble9_package_type_t packet_type ) 
{
    uint8_t ble9_settings[ 2 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = packet_type;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_SET_LONG_DATA_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_start ( ble9_t *ctx, ble9_adv_mode_discoverable_t discover, 
                       ble9_adv_mode_connectable_t connect ) 
{
    uint8_t ble9_settings[ 3 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = discover;
    ble9_settings[ 2 ] = connect;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_START_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_stop ( ble9_t *ctx ) 
{
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_STOP_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, &ctx->ble9_adv_handle, 1 );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_start_per_adv ( ble9_t *ctx, uint16_t interval_min, uint16_t interval_max, uint8_t flags ) 
{
    uint8_t ble9_settings[ 6 ] = { 0 };
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_settings[ 0 ] = ctx->ble9_adv_handle;
    ble9_settings[ 1 ] = ( interval_min & 0xFF00 ) >> 8;
    ble9_settings[ 2 ] = ( interval_min & 0x00FF );
    ble9_settings[ 3 ] = ( interval_max & 0xFF00 ) >> 8;
    ble9_settings[ 4 ] = ( interval_max & 0x00FF );
    ble9_settings[ 5 ] = flags;

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_START_PERIODIC_ADVERTISING_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, ble9_settings, sizeof ( ble9_settings ) );

    return ble9_generic_err_check ( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

err_t ble9_adv_stop_per_adv ( ble9_t *ctx ) 
{
    uint8_t tmp_array[ 6 ] = { 0 };

    ble9_send_command ( ctx, BLE9_CMD_ADVERTISER_STOP_PERIODIC_ADVERTISING_ID );
    Delay_1ms ( );
    ble9_generic_write ( ctx, &ctx->ble9_adv_handle, 1 );

    return ble9_generic_err_check( ctx, sizeof ( tmp_array ), 4, tmp_array );
}

// -----------------------------------------------------------------------------
// GENERIC FUNCTIONS
// -----------------------------------------------------------------------------

void ble9_generic_write ( ble9_t *ctx, uint8_t *data_buf, uint16_t len ) 
{
    uart_write ( &ctx->uart, data_buf, len );
}

int32_t ble9_generic_read ( ble9_t *ctx, uint8_t *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void ble9_send_command ( ble9_t *ctx, uint32_t command ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( command & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( command >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( command >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( command >> 24 ) & 0xFF );
    ble9_generic_write( ctx, data_buf, 4 );
}

// -----------------------------------------------------------------------------
// STATIC FUNCTIONS
// -----------------------------------------------------------------------------

static uint8_t ble9_generic_err_check ( ble9_t *ctx, uint8_t read_n_elements,
                                        uint8_t check_char_num, uint8_t *ret_val_check ) 
{
    uint8_t temp_array[ 22 ] = { 0 };
    uart_read ( &ctx->uart, temp_array, read_n_elements );

    if ( BLE9_OK == temp_array[ check_char_num ] ) 
    {
        memcpy ( ret_val_check, temp_array, read_n_elements );
        return BLE9_OK;
    } 
    else 
    {
        return BLE9_ERROR;
    }
}

// ------------------------------------------------------------------------- END
