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
 * @file btaudio2.c
 * @brief BT Audio 2 Click Driver.
 */

#include "btaudio2.h"

void btaudio2_cfg_setup ( btaudio2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ean = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->sc1 = HAL_PIN_NC;
    cfg->mfb = HAL_PIN_NC;
    cfg->sc2 = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t btaudio2_init ( btaudio2_t *ctx, btaudio2_cfg_t *cfg ) 
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
    digital_out_init( &ctx->ean, cfg->ean );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->sc1, cfg->sc1 );
    digital_out_init( &ctx->mfb, cfg->mfb );
    digital_out_init( &ctx->sc2, cfg->sc2 );

    return UART_SUCCESS;
}

err_t btaudio2_default_cfg ( btaudio2_t *ctx ) 
{
    err_t error_flag = BTAUDIO2_OK;
    
    btaudio2_set_mode ( ctx, BTAUDIO2_MODE_FLASH_APPLICATION );
    btaudio2_set_mfb_pin ( ctx, 0 );
    btaudio2_reset_device ( ctx );

    error_flag |= btaudio2_power_on_device ( ctx );
    error_flag |= btaudio2_reset_to_default ( ctx );
    btaudio2_clear_events ( ctx );
    
    return error_flag;
}

err_t btaudio2_generic_write ( btaudio2_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t btaudio2_generic_read ( btaudio2_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void btaudio2_set_mfb_pin ( btaudio2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->mfb, state );
}

void btaudio2_set_rst_pin ( btaudio2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void btaudio2_set_mode ( btaudio2_t *ctx, uint8_t mode )
{
    switch ( mode )
    {
        case BTAUDIO2_MODE_FLASH_APPLICATION:
        {
            digital_out_high ( &ctx->sc1 );
            digital_out_low ( &ctx->ean );
            digital_out_high ( &ctx->sc2 );
            break;
        }
        case BTAUDIO2_MODE_ROM_APPLICATION:
        {
            digital_out_high ( &ctx->sc1 );
            digital_out_high ( &ctx->ean );
            digital_out_high ( &ctx->sc2 );
            break;
        }
        case BTAUDIO2_MODE_FLASH_IBDK:
        {
            digital_out_low ( &ctx->sc1 );
            digital_out_low ( &ctx->ean );
            digital_out_high ( &ctx->sc2 );
            break;
        }
        case BTAUDIO2_MODE_ROM_IBDK:
        {
            digital_out_low ( &ctx->sc1 );
            digital_out_high ( &ctx->ean );
            digital_out_high ( &ctx->sc2 );
            break;
        }
        case BTAUDIO2_MODE_BOOT:
        {
            digital_out_low ( &ctx->sc1 );
            digital_out_high ( &ctx->ean );
            digital_out_low ( &ctx->sc2 );
            break;
        }
        default:
        {
            break;
        }
    }
}

void btaudio2_reset_device ( btaudio2_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    digital_out_high ( &ctx->rst );
    btaudio2_clear_events ( ctx );
}

void btaudio2_send_cmd ( btaudio2_t *ctx )
{
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint16_t cnt = 0;
    uint8_t package_len = ctx->cmd_packet.param_len + 1;
    cmd_buf[ 0 ] = BTAUDIO2_START_HEADER;
    cmd_buf[ 1 ] = ( uint8_t ) ( ( package_len >> 8 ) & 0xFF );
    cmd_buf[ 2 ] = ( uint8_t ) ( package_len & 0xFF );
    cmd_buf[ 3 ] = ctx->cmd_packet.opcode;
    Delay_10ms( );
    btaudio2_generic_write ( ctx, cmd_buf, 4 );
    uint8_t checksum = cmd_buf[ 1 ] + cmd_buf[ 2 ] + cmd_buf[ 3 ];
    if ( ctx->cmd_packet.param_len ) 
    {
        btaudio2_generic_write ( ctx, ctx->cmd_packet.param_buf, ctx->cmd_packet.param_len );
        for ( cnt = 0; cnt < ctx->cmd_packet.param_len; cnt++ )
        {
            checksum += ctx->cmd_packet.param_buf[ cnt ];
        }
    }    
    checksum = ~checksum + 1;
    btaudio2_generic_write ( ctx, &checksum, 1 );
    Delay_10ms( );
}

err_t btaudio2_send_cmd_with_ack ( btaudio2_t *ctx )
{
    btaudio2_send_cmd ( ctx );
    if ( BTAUDIO2_ERROR == btaudio2_read_event ( ctx ) )
    {
        btaudio2_send_cmd ( ctx );
        if ( BTAUDIO2_ERROR == btaudio2_read_event ( ctx ) )
        {
            return BTAUDIO2_ERROR;
        }
    }
    if ( ( BTAUDIO2_EVT_CMD_ACK == ctx->event_packet.opcode ) && 
         ( ctx->cmd_packet.opcode == ctx->event_packet.param_buf[ 0 ] ) && 
         ( 2 == ctx->event_packet.param_len ) )
    {
        return ctx->event_packet.param_buf[ 1 ];
    }
    return BTAUDIO2_ERROR;
}

err_t btaudio2_read_event ( btaudio2_t *ctx )
{
    uint16_t timeout = 500;
    uint8_t evt_buf[ 4 ] = { 0 };
    uint8_t checksum_read = 0;
    uint8_t checksum = 0;
    uint16_t cnt = 0;
    while ( BTAUDIO2_START_HEADER != evt_buf[ 0 ] )
    {
        btaudio2_generic_read( ctx, evt_buf, 1 );
        Delay_1ms( );
        timeout--;
        if ( 0 == timeout )
        {
            return BTAUDIO2_ERROR;
        }
    }
    Delay_10ms( );
    if ( 3 == btaudio2_generic_read( ctx, &evt_buf[ 1 ], 3 ) )
    {
        ctx->event_packet.param_len = ( uint16_t ) ( ( ( uint16_t ) evt_buf[ 1 ] << 8 ) | evt_buf[ 2 ] ) - 1;
        ctx->event_packet.opcode = evt_buf[ 3 ];
        for ( cnt = 0; cnt < ctx->event_packet.param_len; cnt++ )
        {
            Delay_1ms( );
        }
        if ( ctx->event_packet.param_len == 
             btaudio2_generic_read( ctx, ctx->event_packet.param_buf, ctx->event_packet.param_len ) )
        {
            if ( 1 == btaudio2_generic_read( ctx, &checksum_read, 1 ) )
            {
                checksum = evt_buf[ 1 ] + evt_buf[ 2 ] + evt_buf[ 3 ];
                for ( cnt = 0; cnt < ctx->event_packet.param_len; cnt++ )
                {
                    checksum += ctx->event_packet.param_buf[ cnt ];
                }
                checksum = ~checksum + 1;
                if ( checksum == checksum_read )
                {
                    if ( BTAUDIO2_EVT_CMD_ACK != ctx->event_packet.opcode )
                    {
                        ctx->cmd_packet.opcode = BTAUDIO2_CMD_EVENT_ACK;
                        ctx->cmd_packet.param_buf[ 0 ] = ctx->event_packet.opcode;
                        ctx->cmd_packet.param_len = 1;
                        btaudio2_send_cmd ( ctx );
                    }
                    return BTAUDIO2_OK;
                }
            }
        }
    }
    return BTAUDIO2_ERROR;
}

err_t btaudio2_wait_for_event ( btaudio2_t *ctx, uint8_t opcode )
{
    for ( uint8_t cnt = 0; cnt < 50; cnt++ )
    {
        btaudio2_read_event ( ctx );
        if ( ctx->event_packet.opcode == opcode )
        {
            return BTAUDIO2_OK;
        }
    } 
    return BTAUDIO2_ERROR;
}

void btaudio2_clear_events ( btaudio2_t *ctx )
{
    while ( BTAUDIO2_OK == btaudio2_read_event ( ctx ) );
    ctx->event_packet.opcode = 0;
    memset ( ctx->event_packet.param_buf, 0, BTAUDIO2_PARAM_BUFFER_SIZE );
    ctx->event_packet.param_len = 0;
}

err_t btaudio2_send_mmi_action ( btaudio2_t *ctx, uint8_t database_index, uint8_t action )
{
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_MMI_ACTION;
    ctx->cmd_packet.param_buf[ 0 ] = database_index;
    ctx->cmd_packet.param_buf[ 1 ] = action;
    ctx->cmd_packet.param_len = 2;
    return btaudio2_send_cmd_with_ack ( ctx );
}

err_t btaudio2_power_on_device ( btaudio2_t *ctx )
{
    btaudio2_clear_events ( ctx );
    err_t error_flag = btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_POWER_ON_BUTTON_PRESS );
    Delay_100ms ( );
    error_flag |= btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_POWER_ON_BUTTON_RELEASE );
    do
    {
        error_flag |= btaudio2_wait_for_event ( ctx, BTAUDIO2_EVT_BTM_STATE );
    } 
    while ( ( BTAUDIO2_BTM_STATE_POWER_ON != ctx->event_packet.param_buf[ 0 ] ) && 
            ( BTAUDIO2_OK == error_flag ) );
    return error_flag;
}

err_t btaudio2_power_off_device ( btaudio2_t *ctx )
{
    btaudio2_clear_events ( ctx );
    err_t error_flag = btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_POWER_OFF_BUTTON_PRESS );
    Delay_100ms ( );
    error_flag |= btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_POWER_OFF_BUTTON_RELEASE );
    do
    {
        error_flag |= btaudio2_wait_for_event ( ctx, BTAUDIO2_EVT_BTM_STATE );
    } 
    while ( ( BTAUDIO2_BTM_STATE_POWER_OFF != ctx->event_packet.param_buf[ 0 ] ) && 
            ( BTAUDIO2_OK == error_flag ) );
    return error_flag;
}

err_t btaudio2_enter_pairing_mode ( btaudio2_t *ctx )
{
    btaudio2_clear_events ( ctx );
    err_t error_flag = btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_ENTER_PAIRING_MODE );
    do
    {
        error_flag |= btaudio2_wait_for_event ( ctx, BTAUDIO2_EVT_BTM_STATE );
    } 
    while ( ( BTAUDIO2_BTM_STATE_PAIRING_STATE != ctx->event_packet.param_buf[ 0 ] ) && 
            ( BTAUDIO2_OK == error_flag ) );
    return error_flag;
}

err_t btaudio2_reset_to_default ( btaudio2_t *ctx )
{
    btaudio2_clear_events ( ctx );
    err_t error_flag = btaudio2_send_mmi_action ( ctx, 0, BTAUDIO2_MMI_RESET_EEPROM_SETTING );
    btaudio2_wait_for_event ( ctx, BTAUDIO2_EVT_RESET_TO_DEFAULT );
    return error_flag;
}

err_t btaudio2_set_device_name ( btaudio2_t *ctx, uint8_t *device_name )
{
    uint8_t device_name_size = strlen( device_name );
    if ( device_name_size >= 32 )
    {
        return BTAUDIO2_ERROR;
    }
    btaudio2_clear_events ( ctx );
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_CHANGE_DEVICE_NAME;
    memcpy ( ctx->cmd_packet.param_buf, device_name, device_name_size );
    ctx->cmd_packet.param_len = device_name_size;
    err_t error_flag = btaudio2_send_cmd_with_ack ( ctx );

    ctx->cmd_packet.opcode = BTAUDIO2_CMD_CONFIGURE_VENDOR_PARAM;
    ctx->cmd_packet.param_buf[ 0 ] = 0x00;
    ctx->cmd_packet.param_buf[ 1 ] = 0x00;
    ctx->cmd_packet.param_buf[ 2 ] = device_name_size;
    memcpy ( &ctx->cmd_packet.param_buf[ 3 ], device_name, device_name_size );
    ctx->cmd_packet.param_len = device_name_size + 3;
    btaudio2_send_cmd_with_ack ( ctx );
    return error_flag;
}

err_t btaudio2_music_control ( btaudio2_t *ctx, btaudio2_music_control_t action )
{
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_MUSIC_CONTROL;
    ctx->cmd_packet.param_buf[ 0 ] = 0x00;
    ctx->cmd_packet.param_buf[ 1 ] = action;
    ctx->cmd_packet.param_len = 2;
    return btaudio2_send_cmd_with_ack ( ctx );
}

err_t btaudio2_make_call ( btaudio2_t *ctx, uint8_t database_index, uint8_t *phone_number )
{
    if ( strlen ( phone_number ) > 19 )
    {
        return BTAUDIO2_ERROR;
    }
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_MAKE_CALL;
    ctx->cmd_packet.param_buf[ 0 ] = database_index;
    memcpy ( &ctx->cmd_packet.param_buf[ 1 ], phone_number, strlen ( phone_number ) );
    ctx->cmd_packet.param_len = strlen ( phone_number ) + 1;
    return btaudio2_send_cmd_with_ack ( ctx );
}

err_t btaudio2_volume_up ( btaudio2_t *ctx, uint8_t database_index, uint8_t mask )
{
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_SET_OVERALL_GAIN;
    ctx->cmd_packet.param_buf[ 0 ] = database_index;
    ctx->cmd_packet.param_buf[ 1 ] = mask;
    ctx->cmd_packet.param_buf[ 2 ] = 0x01;
    ctx->cmd_packet.param_buf[ 3 ] = 0x00;
    ctx->cmd_packet.param_buf[ 4 ] = 0x00;
    ctx->cmd_packet.param_buf[ 5 ] = 0x00;
    ctx->cmd_packet.param_len = 6;
    return btaudio2_send_cmd_with_ack ( ctx );
}

err_t btaudio2_volume_down ( btaudio2_t *ctx, uint8_t database_index, uint8_t mask )
{
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_SET_OVERALL_GAIN;
    ctx->cmd_packet.param_buf[ 0 ] = database_index;
    ctx->cmd_packet.param_buf[ 1 ] = mask;
    ctx->cmd_packet.param_buf[ 2 ] = 0x02;
    ctx->cmd_packet.param_buf[ 3 ] = 0x00;
    ctx->cmd_packet.param_buf[ 4 ] = 0x00;
    ctx->cmd_packet.param_buf[ 5 ] = 0x00;
    ctx->cmd_packet.param_len = 6;
    return btaudio2_send_cmd_with_ack ( ctx );
}

err_t btaudio2_enable_advertising ( btaudio2_t *ctx )
{
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_LE_SIGNALING;
    ctx->cmd_packet.param_buf[ 0 ] = 0x01;
    ctx->cmd_packet.param_buf[ 1 ] = 0x01;
    ctx->cmd_packet.param_len = 2;
    return btaudio2_send_cmd_with_ack ( ctx );
}

err_t btaudio2_disable_advertising ( btaudio2_t *ctx )
{
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_LE_SIGNALING;
    ctx->cmd_packet.param_buf[ 0 ] = 0x01;
    ctx->cmd_packet.param_buf[ 1 ] = 0x00;
    ctx->cmd_packet.param_len = 2;
    return btaudio2_send_cmd_with_ack ( ctx );
}

err_t btaudio2_set_eq_mode ( btaudio2_t *ctx, btaudio2_eq_mode_t eq_mode )
{
    ctx->cmd_packet.opcode = BTAUDIO2_CMD_EQ_MODE_SETTING;
    ctx->cmd_packet.param_buf[ 0 ] = eq_mode;
    ctx->cmd_packet.param_buf[ 1 ] = 0x00;
    return btaudio2_send_cmd_with_ack ( ctx );
}

// ------------------------------------------------------------------------- END
