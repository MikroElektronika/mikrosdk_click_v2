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
 * @file ble10.c
 * @brief BLE 10 Click Driver.
 */

#include "ble10.h"

void ble10_cfg_setup ( ble10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->ain = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->pio3 = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t ble10_init ( ble10_t *ctx, ble10_cfg_t *cfg ) 
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
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->ain;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );

    // Input pins
    digital_in_init( &ctx->pio3, cfg->pio3 );
    digital_in_init( &ctx->rts, cfg->rts );

    return UART_SUCCESS;
}

void ble10_default_cfg ( ble10_t *ctx ) 
{
    ble10_set_cts_pin ( ctx, 0 );
    ble10_hw_reset ( ctx );
}

err_t ble10_generic_write ( ble10_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t ble10_generic_read ( ble10_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t ble10_get_rts_pin ( ble10_t *ctx ) 
{
    return digital_in_read ( &ctx->rts );
}

uint8_t ble10_get_pio3_pin ( ble10_t *ctx ) 
{
    return digital_in_read ( &ctx->pio3 );
}

void ble10_set_cts_pin ( ble10_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->cts, state );
}

void ble10_set_rst_pin ( ble10_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rst, state );
}

void ble10_hw_reset ( ble10_t *ctx )
{
    ble10_set_rst_pin( ctx, 0 );
    Delay_1ms( );
    ble10_set_rst_pin( ctx, 1 );
    Delay_1sec( );
}

err_t ble10_sw_reset ( ble10_t *ctx )
{
    err_t error_flag = ble10_send_cmd ( ctx, BLE10_CMD_ATRST );
    Delay_1sec( );
    return error_flag;
}

err_t ble10_factory_reset ( ble10_t *ctx )
{
    err_t error_flag = ble10_send_cmd ( ctx, BLE10_CMD_ATFRST );
    Delay_1sec( );
    return error_flag;
}

err_t ble10_send_cmd ( ble10_t *ctx, char *at_cmd_buf )
{
    uint8_t carriage_return = '\r';
    
    err_t error_flag = ble10_generic_write( ctx, at_cmd_buf, strlen( at_cmd_buf ) );
    error_flag |= ble10_generic_write( ctx, &carriage_return, 1 );
    
    return error_flag;
}

err_t ble10_send_cmd_with_parameter ( ble10_t *ctx, char *at_cmd_buf, char *param_buf )
{
    uint8_t carriage_return = '\r';
    uint8_t delimiter = ',';
    
    err_t error_flag = ble10_generic_write( ctx, at_cmd_buf, strlen( at_cmd_buf ) );
    error_flag |= ble10_generic_write( ctx, &delimiter, 1 );
    error_flag |= ble10_generic_write( ctx, param_buf, strlen( param_buf ) );
    error_flag |= ble10_generic_write( ctx, &carriage_return, 1 );
    
    return error_flag;
}

err_t ble10_send_cmd_check ( ble10_t *ctx, char *at_cmd_buf )
{
    uint8_t carriage_return = '\r';
    uint8_t check_char = '?';
    
    err_t error_flag = ble10_generic_write( ctx, at_cmd_buf, strlen( at_cmd_buf ) );
    error_flag |= ble10_generic_write( ctx, &check_char, 1 );
    error_flag |= ble10_generic_write( ctx, &carriage_return, 1 );
    
    return error_flag;
}

err_t ble10_remove_pairings ( ble10_t *ctx )
{
    return ble10_send_cmd ( ctx, BLE10_CMD_ATCP );
}

err_t ble10_list_pairings ( ble10_t *ctx )
{
    return ble10_send_cmd_check ( ctx, BLE10_CMD_ATP );
}

err_t ble10_set_device_name ( ble10_t *ctx, char *dev_name )
{
    if ( strlen( dev_name ) > 20 || strlen( dev_name ) < 1 )
    {
        return BLE10_ERROR;
    }
    return ble10_send_cmd_with_parameter ( ctx, BLE10_CMD_ATSN, dev_name );
}

err_t ble10_discover_nearby_devices ( ble10_t *ctx )
{
    return ble10_send_cmd ( ctx, BLE10_CMD_ATDI );
}

err_t ble10_get_temperature ( ble10_t *ctx )
{
    return ble10_send_cmd_check ( ctx, BLE10_CMD_ATT );
}

err_t ble10_read_an_pin_value ( ble10_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t ble10_read_an_pin_voltage ( ble10_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

// ------------------------------------------------------------------------- END
