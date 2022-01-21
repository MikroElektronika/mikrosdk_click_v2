/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file btaudio3.c
 * @brief BT Audio 3 Click Driver.
 */

#include "btaudio3.h"

void btaudio3_cfg_setup ( btaudio3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sm  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->mfb = HAL_PIN_NC;
    cfg->mod = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t btaudio3_init ( btaudio3_t *ctx, btaudio3_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->sm, cfg->sm );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->mfb, cfg->mfb );
    digital_out_init( &ctx->mod, cfg->mod );

    return UART_SUCCESS;
}

err_t btaudio3_default_cfg ( btaudio3_t *ctx ) 
{
    err_t error_flag = BTAUDIO3_OK;
    
    btaudio3_set_application_mode ( ctx );
    btaudio3_set_mfb_pin ( ctx, 1 );
    btaudio3_soft_unmute_output ( ctx );
    btaudio3_reset_device ( ctx );

    error_flag |= btaudio3_power_on_device ( ctx );
    error_flag |= btaudio3_reset_to_default ( ctx );
    error_flag |= btaudio3_enter_pairing_mode ( ctx );
    btaudio3_clear_events ( ctx );
    
    return error_flag;
}

err_t btaudio3_generic_write ( btaudio3_t *ctx, uint8_t *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t btaudio3_generic_read ( btaudio3_t *ctx, uint8_t *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void btaudio3_set_mfb_pin ( btaudio3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->mfb, state );
}

void btaudio3_set_rst_pin ( btaudio3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void btaudio3_set_application_mode ( btaudio3_t *ctx )
{
    digital_out_high ( &ctx->mod );
}

void btaudio3_set_test_mode ( btaudio3_t *ctx )
{
    digital_out_low ( &ctx->mod );
}

void btaudio3_reset_device ( btaudio3_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    digital_out_high ( &ctx->rst );
    btaudio3_clear_events ( ctx );
}

void btaudio3_soft_mute_output ( btaudio3_t *ctx )
{
    digital_out_high ( &ctx->sm );
}

void btaudio3_soft_unmute_output ( btaudio3_t *ctx )
{
    digital_out_low ( &ctx->sm );
}

void btaudio3_send_command ( btaudio3_t *ctx )
{
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t package_len = ctx->command_packet.param_len + 1;
    cmd_buf[ 0 ] = BTAUDIO3_START_HEADER;
    cmd_buf[ 1 ] = ( uint8_t ) ( ( package_len >> 8 ) & 0xFF );
    cmd_buf[ 2 ] = ( uint8_t ) ( package_len & 0xFF );
    cmd_buf[ 3 ] = ctx->command_packet.opcode;
    
    Delay_10ms( );
    btaudio3_generic_write ( ctx, cmd_buf, 4 );
    uint8_t checksum = cmd_buf[ 1 ] + cmd_buf[ 2 ] + cmd_buf[ 3 ];
    if ( ctx->command_packet.param_len ) 
    {
        btaudio3_generic_write ( ctx, ctx->command_packet.param_buf, ctx->command_packet.param_len );
        for ( uint16_t cnt = 0; cnt < ctx->command_packet.param_len; cnt++ )
        {
            checksum += ctx->command_packet.param_buf[ cnt ];
        }
    }    
    checksum = ~checksum + 1;
    btaudio3_generic_write ( ctx, &checksum, 1 );
    Delay_10ms( );
}

err_t btaudio3_send_command_with_ack_check ( btaudio3_t *ctx )
{
    btaudio3_send_command ( ctx );
    if ( BTAUDIO3_ERROR == btaudio3_read_event ( ctx ) )
    {
        btaudio3_send_command ( ctx );
        if ( BTAUDIO3_ERROR == btaudio3_read_event ( ctx ) )
        {
            return BTAUDIO3_ERROR;
        }
    }
    if ( ( BTAUDIO3_EVT_CMD_ACK == ctx->event_packet.opcode ) && 
         ( ctx->command_packet.opcode == ctx->event_packet.param_buf[ 0 ] ) && 
         ( 2 == ctx->event_packet.param_len ) )
    {
        return ctx->event_packet.param_buf[ 1 ];
    }
    return BTAUDIO3_ERROR;
}

err_t btaudio3_read_event ( btaudio3_t *ctx )
{
    uint8_t timeout = 200;
    uint8_t evt_buf[ 4 ] = { 0 };
    while ( BTAUDIO3_START_HEADER != evt_buf[ 0 ] )
    {
        btaudio3_generic_read( ctx, evt_buf, 1 );
        Delay_1ms( );
        timeout--;
        if ( 0 == timeout )
        {
            return BTAUDIO3_ERROR;
        }
    }
    Delay_10ms( );
    if ( 3 == btaudio3_generic_read( ctx, &evt_buf[ 1 ], 3 ) )
    {
        ctx->event_packet.param_len = ( uint16_t ) ( ( ( uint16_t ) evt_buf[ 1 ] << 8 ) | evt_buf[ 2 ] ) - 1;
        ctx->event_packet.opcode = evt_buf[ 3 ];
        for ( uint16_t cnt = 0; cnt < ctx->event_packet.param_len; cnt++ )
        {
            Delay_1ms( );
        }
        if ( ctx->event_packet.param_len == 
             btaudio3_generic_read( ctx, ctx->event_packet.param_buf, ctx->event_packet.param_len ) )
        {
            uint8_t checksum_read = 0;
            if ( 1 == btaudio3_generic_read( ctx, &checksum_read, 1 ) )
            {
                uint8_t checksum = evt_buf[ 1 ] + evt_buf[ 2 ] + evt_buf[ 3 ];
                for ( uint16_t cnt = 0; cnt < ctx->event_packet.param_len; cnt++ )
                {
                    checksum += ctx->event_packet.param_buf[ cnt ];
                }
                checksum = ~checksum + 1;
                if ( checksum == checksum_read )
                {
                    if ( BTAUDIO3_EVT_CMD_ACK != ctx->event_packet.opcode )
                    {
                        ctx->command_packet.opcode = BTAUDIO3_CMD_EVENT_ACK;
                        ctx->command_packet.param_buf[ 0 ] = ctx->event_packet.opcode;
                        ctx->command_packet.param_len = 1;
                        btaudio3_send_command ( ctx );
                    }
                    return BTAUDIO3_OK;
                }
            }
        }
    }
    return BTAUDIO3_ERROR;
}

void btaudio3_wait_for_event ( btaudio3_t *ctx, uint8_t opcode )
{
    do 
    {
        btaudio3_read_event ( ctx );
    } while ( ctx->event_packet.opcode != opcode );
}

void btaudio3_clear_events ( btaudio3_t *ctx )
{
    while ( BTAUDIO3_OK == btaudio3_read_event ( ctx ) );
    ctx->event_packet.opcode = 0;
    memset ( ctx->event_packet.param_buf, 0, 256 );
    ctx->event_packet.param_len = 0;
}

err_t btaudio3_send_mmi_action ( btaudio3_t *ctx, uint8_t database_index, uint8_t action )
{
    ctx->command_packet.opcode = BTAUDIO3_CMD_MMI_ACTION;
    ctx->command_packet.param_buf[ 0 ] = database_index;
    ctx->command_packet.param_buf[ 1 ] = action;
    ctx->command_packet.param_len = 2;
    return btaudio3_send_command_with_ack_check ( ctx );
}

err_t btaudio3_power_on_device ( btaudio3_t *ctx )
{
    btaudio3_clear_events ( ctx );
    err_t error_flag = btaudio3_send_mmi_action ( ctx, 0, BTAUDIO3_MMI_POWER_ON_BUTTON_PRESS );
    error_flag |= btaudio3_send_mmi_action ( ctx, 0, BTAUDIO3_MMI_POWER_ON_BUTTON_RELEASE );
    do
    {
        btaudio3_wait_for_event ( ctx, BTAUDIO3_EVT_BTM_STATE );
    } while ( BTAUDIO3_BTM_STATE_POWER_ON != ctx->event_packet.param_buf[ 0 ] );
    return error_flag;
}

err_t btaudio3_power_off_device ( btaudio3_t *ctx )
{
    btaudio3_clear_events ( ctx );
    err_t error_flag = btaudio3_send_mmi_action ( ctx, 0, BTAUDIO3_MMI_POWER_OFF_BUTTON_PRESS );
    error_flag |= btaudio3_send_mmi_action ( ctx, 0, BTAUDIO3_MMI_POWER_OFF_BUTTON_RELEASE );
    do
    {
        btaudio3_wait_for_event ( ctx, BTAUDIO3_EVT_BTM_STATE );
    } while ( BTAUDIO3_BTM_STATE_POWER_OFF != ctx->event_packet.param_buf[ 0 ] );
    return error_flag;
}

err_t btaudio3_enter_pairing_mode ( btaudio3_t *ctx )
{
    btaudio3_clear_events ( ctx );
    err_t error_flag = btaudio3_send_mmi_action ( ctx, 0, BTAUDIO3_MMI_ENTER_PAIRING_MODE );
    do
    {
        btaudio3_wait_for_event ( ctx, BTAUDIO3_EVT_BTM_STATE );
    } while ( BTAUDIO3_BTM_STATE_PAIRING_STATE != ctx->event_packet.param_buf[ 0 ] );
    return error_flag;
}

err_t btaudio3_reset_to_default ( btaudio3_t *ctx )
{
    btaudio3_clear_events ( ctx );
    err_t error_flag = btaudio3_send_mmi_action ( ctx, 0, BTAUDIO3_MMI_RESET_EEPROM_SETTING );
    btaudio3_wait_for_event ( ctx, BTAUDIO3_EVT_RESET_TO_DEFAULT );
    return error_flag;
}

err_t btaudio3_set_device_name ( btaudio3_t *ctx, uint8_t *device_name )
{
    uint8_t device_name_size = strlen( device_name );
    if ( device_name_size >= 32 )
    {
        return BTAUDIO3_ERROR;
    }
    btaudio3_clear_events ( ctx );
    ctx->command_packet.opcode = BTAUDIO3_CMD_CHANGE_DEVICE_NAME;
    memcpy ( ctx->command_packet.param_buf, device_name, device_name_size );
    ctx->command_packet.param_len = device_name_size;
    err_t error_flag = btaudio3_send_command_with_ack_check ( ctx );
    
    ctx->command_packet.opcode = BTAUDIO3_CMD_CONFIGURE_VENDOR_PARAM;
    ctx->command_packet.param_buf[ 0 ] = 0x00;
    ctx->command_packet.param_buf[ 1 ] = 0x00;
    ctx->command_packet.param_buf[ 2 ] = device_name_size;
    memcpy ( &ctx->command_packet.param_buf[ 3 ], device_name, device_name_size );
    ctx->command_packet.param_len = device_name_size + 3;
    error_flag |= btaudio3_send_command_with_ack_check ( ctx );
    return error_flag;
}

err_t btaudio3_music_control ( btaudio3_t *ctx, btaudio3_music_control_t action )
{
    ctx->command_packet.opcode = BTAUDIO3_CMD_MUSIC_CONTROL;
    ctx->command_packet.param_buf[ 0 ] = 0x00;
    ctx->command_packet.param_buf[ 1 ] = action;
    ctx->command_packet.param_len = 2;
    return btaudio3_send_command_with_ack_check ( ctx );
}

err_t btaudio3_make_call ( btaudio3_t *ctx, uint8_t database_index, uint8_t *phone_number )
{
    if ( strlen ( phone_number ) > 19 )
    {
        return BTAUDIO3_ERROR;
    }
    ctx->command_packet.opcode = BTAUDIO3_CMD_MAKE_CALL;
    ctx->command_packet.param_buf[ 0 ] = database_index;
    memcpy ( &ctx->command_packet.param_buf[ 1 ], phone_number, strlen ( phone_number ) );
    ctx->command_packet.param_len = strlen ( phone_number ) + 1;
    return btaudio3_send_command_with_ack_check ( ctx );
}

err_t btaudio3_volume_up ( btaudio3_t *ctx, uint8_t database_index, uint8_t mask )
{
    ctx->command_packet.opcode = BTAUDIO3_CMD_SET_OVERALL_GAIN;
    ctx->command_packet.param_buf[ 0 ] = database_index;
    ctx->command_packet.param_buf[ 1 ] = mask;
    ctx->command_packet.param_buf[ 2 ] = 0x01;
    ctx->command_packet.param_buf[ 3 ] = 0x00;
    ctx->command_packet.param_buf[ 4 ] = 0x00;
    ctx->command_packet.param_buf[ 5 ] = 0x00;
    ctx->command_packet.param_len = 6;
    return btaudio3_send_command_with_ack_check ( ctx );
}

err_t btaudio3_volume_down ( btaudio3_t *ctx, uint8_t database_index, uint8_t mask )
{
    ctx->command_packet.opcode = BTAUDIO3_CMD_SET_OVERALL_GAIN;
    ctx->command_packet.param_buf[ 0 ] = database_index;
    ctx->command_packet.param_buf[ 1 ] = mask;
    ctx->command_packet.param_buf[ 2 ] = 0x02;
    ctx->command_packet.param_buf[ 3 ] = 0x00;
    ctx->command_packet.param_buf[ 4 ] = 0x00;
    ctx->command_packet.param_buf[ 5 ] = 0x00;
    ctx->command_packet.param_len = 6;
    return btaudio3_send_command_with_ack_check ( ctx );
}

err_t btaudio3_enable_advertising ( btaudio3_t *ctx )
{
    ctx->command_packet.opcode = BTAUDIO3_CMD_LE_SIGNALING;
    ctx->command_packet.param_buf[ 0 ] = 0x01;
    ctx->command_packet.param_buf[ 1 ] = 0x01;
    ctx->command_packet.param_len = 2;
    return btaudio3_send_command_with_ack_check ( ctx );
}

err_t btaudio3_disable_advertising ( btaudio3_t *ctx )
{
    ctx->command_packet.opcode = BTAUDIO3_CMD_LE_SIGNALING;
    ctx->command_packet.param_buf[ 0 ] = 0x01;
    ctx->command_packet.param_buf[ 1 ] = 0x00;
    ctx->command_packet.param_len = 2;
    return btaudio3_send_command_with_ack_check ( ctx );
}

err_t btaudio3_set_eq_mode ( btaudio3_t *ctx, btaudio3_eq_mode_t eq_mode )
{
    ctx->command_packet.opcode = BTAUDIO3_CMD_EQ_MODE_SETTING;
    ctx->command_packet.param_buf[ 0 ] = eq_mode;
    ctx->command_packet.param_buf[ 1 ] = 0x00;
    return btaudio3_send_command_with_ack_check ( ctx );
}

// ------------------------------------------------------------------------- END
