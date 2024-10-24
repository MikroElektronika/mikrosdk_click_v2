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
 * @file calypso.c
 * @brief Calypso Click Driver.
 */

#include "calypso.h"

void calypso_cfg_setup ( calypso_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rm0 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_NONE;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
    cfg->i2c_speed     = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address   = CALYPSO_DEVICE_ADDRESS;
}

err_t calypso_init ( calypso_t *ctx, calypso_cfg_t *cfg ) 
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

    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->wup, cfg->wup );

    // Input pins
    digital_in_init( &ctx->rm0, cfg->rm0 );
    digital_in_init( &ctx->rts, cfg->rts );

    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->cts );
    digital_out_high( &ctx->wup );

    return UART_SUCCESS;
}

err_t calypso_default_cfg ( calypso_t *ctx ) 
{
    err_t error_flag = CALYPSO_OK;

    error_flag |= calypso_port_expander_write( ctx, CALYPSO_REG_CONFIGURATION, CALYPSO_PIN_RM2_MASK );
    error_flag |= calypso_set_app_mode( ctx, CALYPSO_APP_MODE_AT_COMMAND );
    
    return error_flag;
}

err_t calypso_generic_write ( calypso_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t calypso_generic_read ( calypso_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t calypso_port_expander_write ( calypso_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t calypso_port_expander_read ( calypso_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t calypso_set_pins ( calypso_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in = 0; 
    uint8_t data_out = 0;
    err_t error_flag = calypso_port_expander_read( ctx, CALYPSO_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        error_flag |= calypso_port_expander_write( ctx, CALYPSO_REG_OUTPUT_PORT, data_in );
    }
    return error_flag;
}

err_t calypso_set_app_mode ( calypso_t *ctx, uint8_t mode_sel )
{
    err_t error_flag = CALYPSO_OK;

    switch ( mode_sel )
    {
        case CALYPSO_APP_MODE_AT_COMMAND:
        {
            error_flag |= calypso_set_pins( ctx, CALYPSO_PIN_NONE_MASK, CALYPSO_PIN_AP0_MASK | CALYPSO_PIN_AP1_MASK | CALYPSO_PIN_BOOT_MASK );
            break;
        }
        
        case CALYPSO_APP_MODE_OTA:
        {
            error_flag |= calypso_set_pins( ctx, CALYPSO_PIN_AP1_MASK, CALYPSO_PIN_AP0_MASK | CALYPSO_PIN_BOOT_MASK );
            break;
        }
        
        case CALYPSO_APP_MODE_PROVISIONIG:
        {
            error_flag |= calypso_set_pins( ctx, CALYPSO_PIN_AP0_MASK, CALYPSO_PIN_AP1_MASK | CALYPSO_PIN_BOOT_MASK );
            break;
        }
        
        case CALYPSO_APP_MODE_TRANSPARENT:
        {
            error_flag |= calypso_set_pins( ctx, CALYPSO_PIN_AP0_MASK | CALYPSO_PIN_AP1_MASK, CALYPSO_PIN_BOOT_MASK );
            break;
        }
        
        default:
        {
            error_flag |= CALYPSO_ERROR;
            break;
        }
    }

    return error_flag;
}

void calypso_set_rst_pin ( calypso_t *ctx, uint8_t pin_state )
{
    if ( CALYPSO_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void calypso_set_cts_pin ( calypso_t *ctx, uint8_t pin_state )
{
    if ( CALYPSO_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->cts );
    }
    else
    {
        digital_out_low( &ctx->cts );
    }
}

void calypso_set_wup_pin ( calypso_t *ctx, uint8_t pin_state )
{
    if ( CALYPSO_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->wup );
    }
    else
    {
        digital_out_low( &ctx->wup );
    }
}

uint8_t calypso_get_rts_pin ( calypso_t *ctx )
{
    return digital_in_read( &ctx->rts );
}

uint8_t calypso_get_rm0_pin ( calypso_t *ctx )
{
    return digital_in_read( &ctx->rm0 );
}

void calypso_hw_reset ( calypso_t *ctx )
{
    calypso_set_rst_pin ( ctx, CALYPSO_PIN_STATE_LOW );
    Delay_100ms( );
    calypso_set_rst_pin ( ctx, CALYPSO_PIN_STATE_HIGH );
    Delay_100ms( );
}

void calypso_send_cmd ( calypso_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t cmd_end[ 2 ] = { '\r', '\n' };
    while ( *at_cmd_buf != 0 )
    {
        uart_write( &ctx->uart, at_cmd_buf, 1 );
        at_cmd_buf++;
    }
    uart_write( &ctx->uart, cmd_end, 2 );
    Delay_100ms(  );
}

void calypso_send_cmd_with_par ( calypso_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t final_cmd[ CALYPSO_TX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    calypso_send_cmd( ctx, final_cmd );
}

void calypso_send_cmd_check ( calypso_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ CALYPSO_TX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    calypso_send_cmd( ctx, final_cmd );
}

// ------------------------------------------------------------------------- END
