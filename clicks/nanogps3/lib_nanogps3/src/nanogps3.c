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
 * @file nanogps3.c
 * @brief Nano GPS 3 Click Driver.
 */

#include "nanogps3.h"
#include "generic_pointer.h"

/**
 * @brief Nano GPS 3 I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nanogps3_i2c_write ( nanogps3_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief Nano GPS 3 I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nanogps3_i2c_read ( nanogps3_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief Nano GPS 3 UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nanogps3_uart_write ( nanogps3_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief Nano GPS 3 UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nanogps3_uart_read ( nanogps3_t *ctx, uint8_t *data_out, uint8_t len );

void nanogps3_cfg_setup ( nanogps3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // UART communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rts   = HAL_PIN_NC;
    cfg->wup   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->fon = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NANOGPS3_DEVICE_ADDRESS;
    
    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
    
    cfg->drv_sel = NANOGPS3_DRV_SEL_UART;
}

void nanogps3_drv_interface_selection ( nanogps3_cfg_t *cfg, nanogps3_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t nanogps3_init ( nanogps3_t *ctx, nanogps3_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    
    if ( NANOGPS3_DRV_SEL_I2C == ctx->drv_sel )
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
        
        ctx->read_f  = nanogps3_i2c_read;
        ctx->write_f = nanogps3_i2c_write;
    }
    else
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
        
        ctx->read_f  = nanogps3_uart_read;
        ctx->write_f = nanogps3_uart_write;
        
        digital_out_init( &ctx->rts, cfg->rts );
        digital_in_init( &ctx->cts, cfg->cts );
    }
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->fon, cfg->fon );

    digital_in_init( &ctx->wup, cfg->wup );

    return I2C_MASTER_SUCCESS;
}

void nanogps3_default_cfg ( nanogps3_t *ctx ) 
{
    nanogps3_request_to_send( ctx, NANOGPS3_PIN_STATE_LOW );
    do
    {
        nanogps3_set_reset_state( ctx, NANOGPS3_PIN_STATE_LOW );
        nanogps3_set_force_on_state( ctx, NANOGPS3_PIN_STATE_LOW );
        Delay_1sec( );
        nanogps3_set_reset_state( ctx, NANOGPS3_PIN_STATE_HIGH );
        nanogps3_set_force_on_state( ctx, NANOGPS3_PIN_STATE_HIGH );
        Delay_1sec( );
        Delay_1sec( );
        Delay_1sec( );
    }
    while ( NANOGPS3_PIN_STATE_HIGH != nanogps3_get_wup_pin( ctx ) );
}

err_t nanogps3_generic_write ( nanogps3_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, data_in, len );
}

err_t nanogps3_generic_read ( nanogps3_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, data_out, len );
}

void nanogps3_request_to_send ( nanogps3_t *ctx, uint8_t rts )
{
    digital_out_write( &ctx->rts, rts );
}

uint8_t nanogps3_clear_to_send ( nanogps3_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

void nanogps3_set_reset_state ( nanogps3_t *ctx, uint8_t rst_state )
{
    digital_out_write( &ctx->rst, rst_state );
}

void nanogps3_set_force_on_state ( nanogps3_t *ctx, uint8_t pwr_state )
{
    digital_out_write( &ctx->fon, pwr_state );
}

uint8_t nanogps3_get_wup_pin ( nanogps3_t *ctx )
{
    return digital_in_read( &ctx->wup );
}

err_t nanogps3_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data )
{
    if ( gngga_element > NANOGPS3_NMEA_GNGGA_NUM_ELEMENT )
    {
        return NANOGPS3_ERROR;
    }
    char * __generic_ptr start_ptr = strstr( rsp_buf, NANOGPS3_RSP_GNGGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr + 1, NANOGPS3_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gngga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, NANOGPS3_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return NANOGPS3_ERROR;
                }
            }
            char * __generic_ptr end_ptr = strstr( start_ptr, NANOGPS3_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return NANOGPS3_OK;
            }
        }
    }
    return NANOGPS3_ERROR;
}

static err_t nanogps3_uart_write ( nanogps3_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t nanogps3_uart_read ( nanogps3_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

static err_t nanogps3_i2c_write ( nanogps3_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

static err_t nanogps3_i2c_read ( nanogps3_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

// ------------------------------------------------------------------------- END
