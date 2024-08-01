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
 * @file gnss18.c
 * @brief GNSS 18 Click Driver.
 */

#include "gnss18.h"
#include "generic_pointer.h"
#include "string.h"

/**
 * @brief GNSS 18 I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss18_i2c_write ( gnss18_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 18 I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss18_i2c_read ( gnss18_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS 18 UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss18_uart_write ( gnss18_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 18 UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss18_uart_read ( gnss18_t *ctx, uint8_t *data_out, uint8_t len );

void gnss18_cfg_setup ( gnss18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl    = HAL_PIN_NC;
    cfg->sda    = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GNSS18_DEVICE_ADDRESS;
    
    cfg->drv_sel = GNSS18_DRV_SEL_I2C;
}

void gnss18_drv_interface_selection ( gnss18_cfg_t *cfg, gnss18_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t gnss18_init ( gnss18_t *ctx, gnss18_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( GNSS18_DRV_SEL_UART == ctx->drv_sel ) 
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
        
        ctx->read_f  = gnss18_uart_read;
        ctx->write_f = gnss18_uart_write;
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

        ctx->read_f  = gnss18_i2c_read;
        ctx->write_f = gnss18_i2c_write;
    } 

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    gnss18_reset_device(ctx);

    return GNSS18_OK;
}

err_t gnss18_generic_write ( gnss18_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, data_in, len );
}

err_t gnss18_generic_read ( gnss18_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, data_out, len );
}

void gnss18_set_rst_pin ( gnss18_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t gnss18_get_int_pin ( gnss18_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void gnss18_reset_device ( gnss18_t *ctx )
{
    gnss18_set_rst_pin ( ctx, 0 );
    Delay_1sec ( );
    gnss18_set_rst_pin ( ctx, 1 );
    Delay_1sec ( );
}

err_t gnss18_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data )
{    
    if ( gpgga_element > GNSS18_GPGGA_ELEMENT_SIZE )
    {
        return GNSS18_ERROR;
    }
    uint8_t * __generic_ptr start_ptr = strstr( rsp_buf, GNSS18_RSP_GPGGA );
    if ( start_ptr )
    {
        if ( !strstr( start_ptr, GNSS18_RSP_END_SEQ ) )
        {
            return GNSS18_ERROR;
        }
        if ( strstr( start_ptr + 1, GNSS18_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gpgga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS18_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS18_ERROR;
                }
            }
            uint8_t * __generic_ptr end_ptr = strstr( start_ptr, GNSS18_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS18_OK;
            }
        }
    }
    return GNSS18_ERROR;
}

static err_t gnss18_i2c_write ( gnss18_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

static err_t gnss18_i2c_read ( gnss18_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

static err_t gnss18_uart_write ( gnss18_t *ctx, uint8_t *data_in, uint8_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t gnss18_uart_read ( gnss18_t *ctx, uint8_t *data_out, uint8_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

// ------------------------------------------------------------------------- END
