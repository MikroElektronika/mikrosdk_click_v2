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
 * @file bluetooth2.c
 * @brief Bluetooth2 Click Driver.
 */

#include "bluetooth2.h"
#include "conversions.h"

void bluetooth2_cfg_setup ( bluetooth2_cfg_t *cfg ) 
{
    cfg->tx_pin = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->cts    = HAL_PIN_NC;
    cfg->aio    = HAL_PIN_NC;
    cfg->rst    = HAL_PIN_NC;
    cfg->io7    = HAL_PIN_NC;
    cfg->rts    = HAL_PIN_NC;
    
    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = 3.3;
}

err_t bluetooth2_init ( bluetooth2_t *ctx, bluetooth2_cfg_t *cfg ) 
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->aio;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }

    if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }

    if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }
    
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

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );
    
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->io7, cfg->io7 );

    digital_in_init( &ctx->rts, cfg->rts );

    return BLUETOOTH2_OK;
}

void bluetooth2_default_cfg ( bluetooth2_t *ctx ) 
{
    bluetooth2_set_cts_pin ( ctx, 0 );
    bluetooth2_set_io7_pin ( ctx, 0 );
    bluetooth2_hw_reset ( ctx );
}

err_t bluetooth2_generic_write ( bluetooth2_t *ctx, char *data_buf, uint16_t len )
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t bluetooth2_generic_read ( bluetooth2_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

err_t bluetooth2_read_an_pin_value ( bluetooth2_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t bluetooth2_read_an_pin_voltage ( bluetooth2_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void bluetooth2_set_cts_pin ( bluetooth2_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->cts, state );
}

void bluetooth2_set_rst_pin ( bluetooth2_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rst, state );
}

void bluetooth2_set_io7_pin ( bluetooth2_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->io7, state );
}

uint8_t bluetooth2_get_rts_pin ( bluetooth2_t *ctx ) 
{
    return digital_in_read ( &ctx->rts );
}

err_t bluetooth2_write_command ( bluetooth2_t *ctx, char *data_buf )
{
    uint8_t carriage_return = '\r';
    
    err_t error_flag = uart_write( &ctx->uart, data_buf, strlen( data_buf ) );
    error_flag |= uart_write( &ctx->uart, &carriage_return, 1 );
    
    return error_flag;
}

void bluetooth2_hw_reset ( bluetooth2_t *ctx )
{
    bluetooth2_set_rst_pin( ctx, 0 );
    Delay_100ms( );
    bluetooth2_set_rst_pin( ctx, 1 );
    Delay_1sec( );
}

err_t bluetooth2_toggle_mode ( bluetooth2_t *ctx )
{
    Delay_1sec( );
    err_t error_flag = bluetooth2_generic_write ( ctx, BLUETOOTH2_ESCAPE_SEQUENCE, 3 );
    Delay_1sec( );
    return error_flag;
}

err_t bluetooth2_factory_reset ( bluetooth2_t *ctx )
{
    err_t error_flag = bluetooth2_write_command ( ctx, BLUETOOTH2_FACTORY_RESET );
    Delay_1sec( );
    return error_flag;
}

err_t bluetooth2_sw_reset ( bluetooth2_t *ctx )
{
    err_t error_flag = bluetooth2_write_command ( ctx, BLUETOOTH2_SW_RESET );
    Delay_100ms( );
    return error_flag;
}

err_t bluetooth2_remove_pairings ( bluetooth2_t *ctx )
{
    return bluetooth2_write_command ( ctx, BLUETOOTH2_REMOVE_PAIRINGS );
}

err_t bluetooth2_list_pairings ( bluetooth2_t *ctx )
{
    return bluetooth2_write_command ( ctx, BLUETOOTH2_LIST_PAIRINGS );
}

err_t bluetooth2_set_device_name ( bluetooth2_t *ctx, char *dev_name )
{
    if ( strlen( dev_name ) > 140 || strlen( dev_name ) < 1 )
    {
        return BLUETOOTH2_ERROR;
    }
    
    err_t error_flag = bluetooth2_generic_write ( ctx, BLUETOOTH2_SET_DEVICE_NAME, 
                                                       strlen( BLUETOOTH2_SET_DEVICE_NAME ) );
    error_flag |= bluetooth2_write_command ( ctx, dev_name );
    return error_flag;
}

err_t bluetooth2_find_other_devices ( bluetooth2_t *ctx, uint8_t timeout )
{
    if ( timeout > 48 || timeout < 1 )
    {
        return BLUETOOTH2_ERROR;
    }
    
    err_t error_flag = bluetooth2_generic_write ( ctx, BLUETOOTH2_FIND_OTHER_DEVICES, 
                                                       strlen( BLUETOOTH2_FIND_OTHER_DEVICES ) );
    uint8_t tmp_str[ 5 ] = { 0 };
    uint8_to_str( timeout, tmp_str );
    l_trim( tmp_str );
    error_flag |= bluetooth2_write_command ( ctx, tmp_str );
    return error_flag;
}

err_t bluetooth2_pair ( bluetooth2_t *ctx, uint8_t *dev_addr )
{
    if ( strlen( dev_addr ) != strlen( BLUETOOTH2_DEV_ADDRESS_FORMAT ) )
    {
        return BLUETOOTH2_ERROR;
    }
    
    err_t error_flag = bluetooth2_generic_write ( ctx, BLUETOOTH2_PAIR, 
                                                       strlen( BLUETOOTH2_PAIR ) );
    error_flag |= bluetooth2_write_command ( ctx, dev_addr );
    return error_flag;
}

err_t bluetooth2_enable_ok_response ( bluetooth2_t *ctx )
{
    err_t error_flag = bluetooth2_generic_write ( ctx, BLUETOOTH2_SET_CONTROL_CONFIG, 
                                                       strlen( BLUETOOTH2_SET_CONTROL_CONFIG ) );
    error_flag |= bluetooth2_write_command ( ctx, BLUETOOTH2_ENABLE_OK_WITH_DEFAULT_VALUES );
    return error_flag;
}

// ------------------------------------------------------------------------ END
