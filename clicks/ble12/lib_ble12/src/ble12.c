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
 * @file ble12.c
 * @brief BLE 12 Click Driver.
 */

#include "ble12.h"

#define TERMINATED_CHAR      0x0D
#define LINEFEED_CHAR        0x0A

/**
 * @brief BLE 12 start-up configuration delay function.
 * @details This function executes a start-up configuration delay 
 * of the 1 milliseconds of BLE 12 Click board™.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_startup_cfg_delay ( void );

/**
 * @brief BLE 12 device configuration delay function.
 * @details This function executes a device configuration delay 
 * of the 100 milliseconds of BLE 12 Click board™.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_cfg_delay ( void );

void ble12_cfg_setup ( ble12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->wkp   = HAL_PIN_NC;
    cfg->cmd = HAL_PIN_NC;
    cfg->req = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t ble12_init ( ble12_t *ctx, ble12_cfg_t *cfg ) 
{
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wkp, cfg->wkp );
    digital_out_init( &ctx->cmd, cfg->cmd );
    
    digital_in_init( &ctx->req, cfg->req );
    
    digital_out_high( &ctx->rst );
    dev_startup_cfg_delay( );

    digital_out_high( &ctx->cmd );
    dev_startup_cfg_delay( );
    
    digital_out_low( &ctx->wkp );
    dev_startup_cfg_delay( );

    digital_out_high( &ctx->wkp );
    dev_startup_cfg_delay( );
    
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

    return UART_SUCCESS;
}

err_t ble12_default_cfg ( ble12_t *ctx ) 
{   
    err_t err_flag = ble12_wake_up_device( ctx );
    dev_cfg_delay( );
    
    err_flag |= ble12_reset( ctx );
    dev_cfg_delay( );
    
    err_flag |= ble12_init_led( ctx );
    dev_cfg_delay( );

    return err_flag;
}

err_t ble12_generic_write ( ble12_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t ble12_generic_read ( ble12_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

err_t ble12_wake_up_device ( ble12_t *ctx ) 
{
    digital_out_high( &ctx->rst );
    dev_startup_cfg_delay( );
    
    digital_out_high( &ctx->cmd );
    dev_startup_cfg_delay( );
    
    digital_out_low( &ctx->wkp );
    dev_startup_cfg_delay( );
    
    digital_out_high( &ctx->wkp );
    dev_startup_cfg_delay( );
    
    return BLE12_OK;
}

err_t ble12_send_cmd ( ble12_t *ctx, char *cmd ) 
{
    char tmp_buf[ 100 ];
    uint8_t len;
    err_t err_flag;

    memset( tmp_buf, 0, 100 );
    len = strlen( cmd );

    strncpy( tmp_buf, cmd, len );
    tmp_buf[ len ] = TERMINATED_CHAR;
    tmp_buf[ len + 1 ] = LINEFEED_CHAR;
    
    for ( uint8_t cnt = 0; cnt < len + 2; cnt ++ ) 
    {
        err_flag |= ble12_generic_write( ctx, &tmp_buf[ cnt ], 1 );
    }
    
    return err_flag;
}

err_t ble12_send_data ( ble12_t *ctx, char *tx_data ) 
{
    char tmp_buf[ 100 ];
    uint8_t len;
    err_t err_flag;

    memset( tmp_buf, 0, 100 );
    len = strlen( tx_data );

    for ( uint8_t cnt = 0; cnt < len; cnt ++ ) 
    {
        err_flag |= ble12_generic_write( ctx, &tmp_buf[ cnt ], 1 );
    }
    
    return err_flag;
}

err_t ble12_init_led ( ble12_t *ctx ) 
{
    ble12_send_cmd( ctx, BLE12_CMD_INIT_LED1 );
    dev_cfg_delay( );
    
    ble12_send_cmd( ctx, BLE12_CMD_INIT_LED2 );
    dev_cfg_delay( );
    
    return BLE12_OK;
}

err_t ble12_set_led_state ( ble12_t *ctx, uint8_t led, uint8_t state ) 
{  
    err_t err_flag = ble12_generic_write( ctx, BLE12_CMD_SET_GPIO, 7 );
    
    if ( led == BLE12_LED_YELLOW )
    {
        err_flag |= ble12_generic_write( ctx, BLE12_SELECT_LED_YELLOW, 4 );    
    }
    else if ( led == BLE12_LED_RED )
    {
         err_flag |= ble12_generic_write( ctx, BLE12_SELECT_LED_RED, 4 );     
    }
    else
    {
        return BLE12_ERROR;    
    }
    
    if ( state == BLE12_LED_ON )
    {
        err_flag |= ble12_send_cmd( ctx, BLE12_SET_LED_STATE_ON );        
    }
    else if ( state == BLE12_LED_OFF )
    {
        err_flag |= ble12_send_cmd( ctx, BLE12_SET_LED_STATE_OFF );            
    }
    else
    {
        return BLE12_ERROR;    
    }
    
    return BLE12_OK;
}

err_t ble12_reset ( ble12_t *ctx ) 
{   
    err_t err_flag = ble12_send_cmd( ctx, BLE12_CMD_SW_RESET );
    
    return err_flag;
}

err_t ble12_get_version ( ble12_t *ctx ) 
{
    err_t err_flag = ble12_send_cmd( ctx, BLE12_CMD_GET_VERSION );
    
    return err_flag;
}

err_t ble12_set_device_name ( ble12_t *ctx, uint8_t *device_name ) 
{   
    err_t err_flag = ble12_generic_write( ctx, BLE12_CMD_SET_NAME, 8 );
    err_flag |= ble12_send_cmd( ctx, device_name );
    
    return err_flag;
}

err_t ble12_save_config ( ble12_t *ctx ) 
{         
    return ble12_send_cmd( ctx, BLE12_CMD_SET_SAVE );;
}

err_t ble12_set_adv_interval ( ble12_t *ctx, uint8_t *adv_interval ) 
{     
    err_t err_flag = ble12_generic_write( ctx, BLE12_CMD_SET_ADINTERVAL, 14 );
    err_flag |= ble12_send_cmd( ctx, adv_interval );    
    
    return err_flag;
}

err_t ble12_disconnect ( ble12_t *ctx  ) 
{     
    return ble12_send_cmd( ctx, BLE12_CMD_SET_DISCON );
}

err_t ble12_set_default ( ble12_t *ctx ) 
{   
    err_t err_flag = ble12_send_cmd( ctx, BLE12_CMD_SET_DEFAULT );
    
    return err_flag;
}

err_t ble12_set_op_mode ( ble12_t *ctx, uint8_t op_mode ) 
{
    if ( op_mode == BLE12_OP_MODE_CMD )
    {
        digital_out_high( &ctx->cmd );
    }
    else if ( op_mode == BLE12_OP_MODE_DATA )
    {
        digital_out_low( &ctx->cmd );
    }
    else
    {
        return BLE12_ERROR;    
    }

    return BLE12_ERROR;
}

err_t ble12_event_startup ( ble12_t *ctx ) 
{
    err_t err_flag = BLE12_OK;
    
    for ( uint8_t cnt = 0; cnt < 10; cnt++ )
    {
        err_flag |= ble12_set_led_state( ctx, BLE12_LED_YELLOW, BLE12_LED_ON );
        dev_cfg_delay( );
        err_flag |= ble12_set_led_state( ctx, BLE12_LED_RED, BLE12_LED_ON );
        dev_cfg_delay( );
        err_flag |= ble12_set_led_state( ctx, BLE12_LED_YELLOW, BLE12_LED_OFF );
        dev_cfg_delay( );
        err_flag |= ble12_set_led_state( ctx, BLE12_LED_RED, BLE12_LED_OFF );
        dev_cfg_delay( );
    }
    
    return err_flag;
}

static void dev_startup_cfg_delay ( void ) 
{
    Delay_1ms( );
}

static void dev_cfg_delay ( void ) 
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
