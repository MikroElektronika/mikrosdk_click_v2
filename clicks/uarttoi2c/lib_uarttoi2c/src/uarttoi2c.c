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
 * @file uarttoi2c.c
 * @brief UART to I2C Click Driver.
 */

#include "uarttoi2c.h"

void uarttoi2c_cfg_setup ( uarttoi2c_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t uarttoi2c_init ( uarttoi2c_t *ctx, uarttoi2c_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );
    
    // perform dummy read in order to enable uart RX interrupt
    uint8_t dummy;
    uarttoi2c_generic_read( ctx, &dummy, 1 );
    return UART_SUCCESS;
}

err_t uarttoi2c_default_cfg ( uarttoi2c_t *ctx ) 
{
    err_t error_flag = UARTTOI2C_OK;
    if ( UARTTOI2C_OK != uarttoi2c_reset_device ( ctx ) )
    {
        return UARTTOI2C_ERROR;
    }
    error_flag |= uarttoi2c_gpio_config ( ctx, UARTTOI2C_PIN_DIR_OUTPUT_PP, UARTTOI2C_PIN_0_MASK | 
                                                                            UARTTOI2C_PIN_1_MASK | 
                                                                            UARTTOI2C_PIN_2_MASK | 
                                                                            UARTTOI2C_PIN_3_MASK );
    error_flag |= uarttoi2c_gpio_config ( ctx, UARTTOI2C_PIN_DIR_INPUT, UARTTOI2C_PIN_4_MASK | 
                                                                        UARTTOI2C_PIN_5_MASK | 
                                                                        UARTTOI2C_PIN_6_MASK | 
                                                                        UARTTOI2C_PIN_7_MASK );
    uarttoi2c_gpio_write ( ctx, UARTTOI2C_NO_PIN_MASK );
    return error_flag;
}

err_t uarttoi2c_generic_write ( uarttoi2c_t *ctx, char *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t uarttoi2c_generic_read ( uarttoi2c_t *ctx, char *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void uarttoi2c_set_rst_pin ( uarttoi2c_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

err_t uarttoi2c_reset_device ( uarttoi2c_t *ctx )
{
    err_t error_flag = UARTTOI2C_OK;
    uint16_t timeout_cnt = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    uart_clear ( &ctx->uart );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    // Read the first byte of power up message
    while ( UARTTOI2C_OK == error_flag )
    {
        if ( ( 1 == uarttoi2c_generic_read( ctx, data_buf, 1 ) ) && 
             ( UARTTOI2C_POWER_UP_BYTE_0 == data_buf[ 0 ] ) )
        {
            Delay_10ms( );
            // Read the second byte of power up message
            if ( ( 1 == uarttoi2c_generic_read( ctx, &data_buf[ 1 ], 1 ) ) && 
                 ( UARTTOI2C_POWER_UP_BYTE_1 == data_buf[ 1 ] ) )
            {
                error_flag = UARTTOI2C_OK;
                break;
            }
        }
        if ( ++timeout_cnt > UARTTOI2C_TIMEOUT_MS )
        {
            error_flag = UARTTOI2C_TIMEOUT_ERROR;
            break;
        }
        Delay_1ms( );
    }
    return error_flag;
}

err_t uarttoi2c_write_register ( uarttoi2c_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( reg > UARTTOI2C_REG_I2C_STAT )
    {
        return UARTTOI2C_ERROR;
    }
    uint8_t tmp_data = UARTTOI2C_CMD_WRITE_REG;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = reg;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = data_in;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = UARTTOI2C_CMD_STOP;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    Delay_10ms( );
    return UARTTOI2C_OK;
}

err_t uarttoi2c_read_register ( uarttoi2c_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( ( NULL == data_out ) || ( reg > UARTTOI2C_REG_I2C_STAT ) )
    {
        return UARTTOI2C_ERROR;
    }
    err_t error_flag = UARTTOI2C_OK;
    uint16_t timeout_cnt = 0;
    uart_clear ( &ctx->uart );
    uint8_t tmp_data = UARTTOI2C_CMD_READ_REG;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = reg;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = UARTTOI2C_CMD_STOP;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    Delay_10ms( );
    
    // Read the first byte of response message
    while ( UARTTOI2C_OK == error_flag )
    {
        if ( ( 1 == uarttoi2c_generic_read( ctx, data_out, 1 ) ) )
        {
            break;
        }
        if ( ++timeout_cnt > UARTTOI2C_TIMEOUT_MS )
        {
            error_flag = UARTTOI2C_TIMEOUT_ERROR;
            break;
        }
        Delay_1ms( );
    }
    return error_flag;
}

void uarttoi2c_gpio_write ( uarttoi2c_t *ctx, uint8_t gpio_data )
{
    uint8_t tmp_data = UARTTOI2C_CMD_WRITE_GPIO;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = gpio_data;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = UARTTOI2C_CMD_STOP;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    Delay_10ms( );
}

err_t uarttoi2c_gpio_read ( uarttoi2c_t *ctx, uint8_t *gpio_data )
{
    if ( NULL == gpio_data )
    {
        return UARTTOI2C_ERROR;
    }
    err_t error_flag = UARTTOI2C_OK;
    uint16_t timeout_cnt = 0;
    uart_clear ( &ctx->uart );
    uint8_t tmp_data = UARTTOI2C_CMD_READ_GPIO;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = UARTTOI2C_CMD_STOP;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    Delay_10ms( );
    
    // Read the first byte of response message
    while ( UARTTOI2C_OK == error_flag )
    {
        if ( ( 1 == uarttoi2c_generic_read( ctx, gpio_data, 1 ) ) )
        {
            break;
        }
        if ( ++timeout_cnt > UARTTOI2C_TIMEOUT_MS )
        {
            error_flag = UARTTOI2C_TIMEOUT_ERROR;
            break;
        }
        Delay_1ms( );
    }
    return error_flag;
}

err_t uarttoi2c_gpio_config ( uarttoi2c_t *ctx, uint8_t direction, uint8_t pin_mask )
{
    if ( direction > UARTTOI2C_PIN_DIR_OUTPUT_OD )
    {
        return UARTTOI2C_ERROR;
    }
    err_t error_flag = UARTTOI2C_OK;
    uint8_t tmp_data;
    error_flag |= uarttoi2c_read_register ( ctx, UARTTOI2C_REG_PORT_CONF_1, &tmp_data );
    if ( UARTTOI2C_OK == error_flag )
    {
        for ( uint8_t pin = 0; pin < 4; pin++ )
        {
            if ( pin_mask & ( UARTTOI2C_PIN_0_MASK << pin ) )
            {
                tmp_data &= ~( UARTTOI2C_PIN_DIR_OUTPUT_MASK << ( pin * 2 ) );
                tmp_data |= ( direction << ( pin * 2 ) );
            }
        }
        error_flag |= uarttoi2c_write_register ( ctx, UARTTOI2C_REG_PORT_CONF_1, tmp_data );
    }
    
    if ( UARTTOI2C_OK == error_flag )
    {
        error_flag |= uarttoi2c_read_register ( ctx, UARTTOI2C_REG_PORT_CONF_2, &tmp_data );
        if ( UARTTOI2C_OK == error_flag )
        {
            for ( uint8_t pin = 0; pin < 4; pin++ )
            {
                if ( pin_mask & ( UARTTOI2C_PIN_4_MASK << pin ) )
                {
                    tmp_data &= ~( UARTTOI2C_PIN_DIR_OUTPUT_MASK << ( pin * 2 ) );
                    tmp_data |= ( direction << ( pin * 2 ) );
                }
            }
            error_flag |= uarttoi2c_write_register ( ctx, UARTTOI2C_REG_PORT_CONF_2, tmp_data );
        }
    }
    return error_flag;
}

err_t uarttoi2c_read_version ( uarttoi2c_t *ctx, uint8_t *version )
{
    err_t error_flag = UARTTOI2C_OK;
    uint16_t timeout_cnt = 0;
    uart_clear ( &ctx->uart );
    uint8_t tmp_data = UARTTOI2C_CMD_READ_VERSION;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = UARTTOI2C_CMD_STOP;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    Delay_10ms( );
    
    // Read the first byte of response message
    while ( UARTTOI2C_OK == error_flag )
    {
        if ( ( 1 == uarttoi2c_generic_read( ctx, &version[ 0 ], 1 ) ) )
        {
            Delay_10ms ( );
            // Read the rest bytes of response message
            if ( 15 != uarttoi2c_generic_read( ctx, &version[ 1 ], 15 ) )
            {
                error_flag = UARTTOI2C_ERROR;
            }
            break;
        }
        if ( ++timeout_cnt > UARTTOI2C_TIMEOUT_MS )
        {
            error_flag = UARTTOI2C_TIMEOUT_ERROR;
            break;
        }
        Delay_1ms( );
    }
    return error_flag;
}

err_t uarttoi2c_i2c_write ( uarttoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len )
{
    if ( NULL == data_in )
    {
        return UARTTOI2C_ERROR;
    }
    uint8_t tmp_data = UARTTOI2C_CMD_START;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = ( slave_addr << 1 );
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = len;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    uarttoi2c_generic_write ( ctx, data_in, len );
    tmp_data = UARTTOI2C_CMD_STOP;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    Delay_10ms( );
    return UARTTOI2C_OK;
}

err_t uarttoi2c_i2c_read ( uarttoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_out, uint8_t len )
{
    if ( ( NULL == data_out ) || ( 0 == len ) )
    {
        return UARTTOI2C_ERROR;
    }
    err_t error_flag = UARTTOI2C_OK;
    uint16_t timeout_cnt = 0;
    uart_clear ( &ctx->uart );
    uint8_t tmp_data = UARTTOI2C_CMD_START;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = ( slave_addr << 1 );
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = len;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = UARTTOI2C_CMD_STOP;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    Delay_10ms( );
    
    // Read the first byte of response message
    while ( UARTTOI2C_OK == error_flag )
    {
        if ( ( 1 == uarttoi2c_generic_read( ctx, &data_out[ 0 ], 1 ) ) )
        {
            Delay_10ms ( );
            // Read the rest bytes of response message
            if ( ( len - 1 ) != uarttoi2c_generic_read( ctx, &data_out[ 1 ], ( len - 1 ) ) )
            {
                error_flag = UARTTOI2C_ERROR;
            }
            break;
        }
        if ( ++timeout_cnt > UARTTOI2C_TIMEOUT_MS )
        {
            error_flag = UARTTOI2C_TIMEOUT_ERROR;
            break;
        }
        Delay_1ms( );
    }
    return error_flag;
}

err_t uarttoi2c_i2c_write_then_read ( uarttoi2c_t *ctx, uint8_t slave_addr, 
                                      uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len )
{
    if ( ( NULL == data_in ) || ( NULL == data_out ) )
    {
        return UARTTOI2C_ERROR;
    }
    err_t error_flag = UARTTOI2C_OK;
    uint16_t timeout_cnt = 0;
    uart_clear ( &ctx->uart );
    uint8_t tmp_data = UARTTOI2C_CMD_START;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = ( slave_addr << 1 );
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = in_len;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    uarttoi2c_generic_write ( ctx, data_in, in_len );
    tmp_data = UARTTOI2C_CMD_START;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = ( slave_addr << 1 ) + 1;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = out_len;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    tmp_data = UARTTOI2C_CMD_STOP;
    uarttoi2c_generic_write ( ctx, &tmp_data, 1 );
    Delay_10ms( );
    
    // Read the first byte of response message
    while ( UARTTOI2C_OK == error_flag )
    {
        if ( ( 1 == uarttoi2c_generic_read( ctx, &data_out[ 0 ], 1 ) ) )
        {
            Delay_10ms ( );
            // Read the rest bytes of response message
            if ( ( out_len - 1 ) != uarttoi2c_generic_read( ctx, &data_out[ 1 ], ( out_len - 1 ) ) )
            {
                error_flag = UARTTOI2C_ERROR;
            }
            break;
        }
        if ( ++timeout_cnt > UARTTOI2C_TIMEOUT_MS )
        {
            error_flag = UARTTOI2C_TIMEOUT_ERROR;
            break;
        }
        Delay_1ms( );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
