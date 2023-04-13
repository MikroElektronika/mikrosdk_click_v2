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
 * @file gnss13.c
 * @brief GNSS 13 Click Driver.
 */

#include "gnss13.h"
#include "generic_pointer.h"

/**
 * @brief GNSS 13 i2c write function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c >=0 - Number of data bytes written,
 *         @li @c  -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss13_i2c_write ( gnss13_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 13 i2c read function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c >=0 - Number of data bytes read,
 *         @li @c  -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss13_i2c_read ( gnss13_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS 13 uart write function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Number of data bytes written,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss13_uart_write ( gnss13_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 13 uart read function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss13_uart_read ( gnss13_t *ctx, uint8_t *data_out, uint8_t len );

void gnss13_cfg_setup ( gnss13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl    = HAL_PIN_NC;
    cfg->sda    = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GNSS13_DEVICE_ADDRESS;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
    
    cfg->drv_sel = GNSS13_DRV_SEL_I2C;
}

void gnss13_drv_interface_selection ( gnss13_cfg_t *cfg, gnss13_drv_t drv_sel )
{
    cfg->drv_sel = drv_sel;
}

err_t gnss13_init ( gnss13_t *ctx, gnss13_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( GNSS13_DRV_SEL_UART == ctx->drv_sel )
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

        ctx->read_f  = gnss13_uart_read;
        ctx->write_f = gnss13_uart_write;
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

        ctx->read_f  = gnss13_i2c_read;
        ctx->write_f = gnss13_i2c_write;
    }

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wup, cfg->wup );

    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->wup );
    Delay_1sec ( );

    return UART_SUCCESS;
}

err_t gnss13_generic_write ( gnss13_t *ctx, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f ( ctx, data_in, len );
}

err_t gnss13_generic_read ( gnss13_t *ctx, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f ( ctx, data_out, len );
}

void gnss13_clear_ring_buffers ( gnss13_t *ctx )
{
    if ( GNSS13_DRV_SEL_UART == ctx->drv_sel )
    {
        uart_clear( &ctx->uart );
    }
}

void gnss13_set_rst_pin ( gnss13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void gnss13_set_wup_pin ( gnss13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

err_t gnss13_parse_gngga ( uint8_t *rsp_buf, uint8_t gngga_element, uint8_t *element_data )
{    
    if ( gngga_element > GNSS13_GNGGA_ELEMENT_SIZE )
    {
        return GNSS13_ERROR;
    }
    uint8_t * __generic_ptr start_ptr = strstr( rsp_buf, GNSS13_RSP_GNGGA );
    if ( start_ptr )
    {
        if ( !strstr( start_ptr, GNSS13_RSP_END_SEQ ) )
        {
            return GNSS13_ERROR;
        }
        if ( strstr( start_ptr + 1, GNSS13_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gngga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS13_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS13_ERROR;
                }
            }
            uint8_t * __generic_ptr end_ptr = strstr( start_ptr, GNSS13_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS13_OK;
            }
        }
    }
    return GNSS13_ERROR;
}

static err_t gnss13_i2c_write ( gnss13_t *ctx, uint8_t *data_in, uint8_t len )
{
    if ( GNSS13_OK == i2c_master_write( &ctx->i2c, data_in, len ) )
    {
        return len;
    }
    return GNSS13_ERROR;
}

static err_t gnss13_i2c_read ( gnss13_t *ctx, uint8_t *data_out, uint8_t len )
{
    uint8_t dummy = 0;
    if ( GNSS13_OK == i2c_master_write_then_read( &ctx->i2c, &dummy, 1, data_out, len ) )
    {
        return len;
    }
    return GNSS13_ERROR;
}

static err_t gnss13_uart_write ( gnss13_t *ctx, uint8_t *data_in, uint8_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t gnss13_uart_read ( gnss13_t *ctx, uint8_t *data_out, uint8_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

// ------------------------------------------------------------------------- END
