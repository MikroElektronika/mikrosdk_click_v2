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
 * @file ezocarrierorp.c
 * @brief EZO Carrier ORP Click Driver.
 */

#include "ezocarrierorp.h"

void ezocarrierorp_cfg_setup ( ezocarrierorp_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->scl    = HAL_PIN_NC;
    cfg->sda    = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EZOCARRIERORP_DEVICE_ADDRESS;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->drv_sel = EZOCARRIERORP_DRV_SEL_UART;
}

void ezocarrierorp_drv_interface_sel ( ezocarrierorp_cfg_t *cfg, ezocarrierorp_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t ezocarrierorp_init ( ezocarrierorp_t *ctx, ezocarrierorp_cfg_t *cfg ) 
{
    if ( EZOCARRIERORP_DRV_SEL_UART == cfg->drv_sel )
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
        ctx->drv_sel = EZOCARRIERORP_DRV_SEL_UART;
    }
    else
    {
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
        ctx->drv_sel = EZOCARRIERORP_DRV_SEL_I2C;
    }

    return EZOCARRIERORP_OK;
}

err_t ezocarrierorp_generic_write ( ezocarrierorp_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    err_t error_flag = EZOCARRIERORP_OK;
    if ( EZOCARRIERORP_DRV_SEL_UART == ctx->drv_sel )
    {
        
        error_flag |= uart_write( &ctx->uart, data_in, len );
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, data_in, len );
        Delay_100ms( );
        Delay_100ms( );
        Delay_100ms( );
    }
    return error_flag;
}

err_t ezocarrierorp_generic_read ( ezocarrierorp_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    if ( EZOCARRIERORP_DRV_SEL_UART == ctx->drv_sel )
    {
        return uart_read( &ctx->uart, data_out, len );
    }
    else
    {
        return i2c_master_read( &ctx->i2c, data_out, len );
    }
}

void ezocarrierorp_send_cmd ( ezocarrierorp_t *ctx, uint8_t *cmd )
{
    uint8_t final_cmd[ 100 ] = { 0 };

    strcpy( final_cmd, cmd );
    strcat( final_cmd, EZOCARRIERORP_CMD_END_COMMAND );

    ezocarrierorp_generic_write( ctx, final_cmd, strlen( final_cmd ) );
}

void ezocarrierorp_send_cmd_with_par ( ezocarrierorp_t *ctx, uint8_t *cmd, uint8_t *param_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { ',', 0 };
    
    strcpy( final_cmd, cmd );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    ezocarrierorp_send_cmd( ctx, final_cmd );
}

void ezocarrierorp_send_cmd_check ( ezocarrierorp_t *ctx, uint8_t *cmd )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 3 ] = { ',', '?', 0 };
    
    strcpy( final_cmd, cmd );
    strcat( final_cmd, check_char );
    
    ezocarrierorp_send_cmd( ctx, final_cmd );
}

// ------------------------------------------------------------------------- END
