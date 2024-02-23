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
 * @file gnss15.c
 * @brief GNSS 15 Click Driver.
 */

#include "gnss15.h"
#include "generic_pointer.h"

/**
 * @brief GNSS 15 I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss15_i2c_write ( gnss15_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 15 I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss15_i2c_read ( gnss15_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS 15 UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss15_uart_write ( gnss15_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 15 UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss15_uart_read ( gnss15_t *ctx, uint8_t *data_out, uint8_t len );

void gnss15_cfg_setup ( gnss15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->scl    = HAL_PIN_NC;
    cfg->sda    = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GNSS15_DEVICE_ADDRESS;
    
    cfg->drv_sel = GNSS15_DRV_SEL_UART;
}

void gnss15_drv_interface_selection ( gnss15_cfg_t *cfg, gnss15_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t gnss15_init ( gnss15_t *ctx, gnss15_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wup, cfg->wup );

    // Input pins
    digital_in_init( &ctx->irq, cfg->irq );
    
    digital_out_high ( &ctx->rst );
    digital_out_high ( &ctx->wup );
    Delay_1sec ( );

    if ( GNSS15_DRV_SEL_UART == ctx->drv_sel ) 
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

        ctx->read_f  = gnss15_uart_read;
        ctx->write_f = gnss15_uart_write;
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

        ctx->read_f  = gnss15_i2c_read;
        ctx->write_f = gnss15_i2c_write;
    }

    return UART_SUCCESS;
}

err_t gnss15_generic_write ( gnss15_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return ctx->write_f( ctx, data_in, len );
}

err_t gnss15_generic_read ( gnss15_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return ctx->read_f( ctx, data_out, len );
}

void gnss15_set_rst_pin ( gnss15_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void gnss15_set_wup_pin ( gnss15_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wup, state );
}

uint8_t gnss15_get_interrupt ( gnss15_t *ctx )
{
    return digital_in_read( &ctx->irq );
}

void gnss15_reset_device ( gnss15_t *ctx )
{
    gnss15_set_rst_pin( ctx, 0 );
    Delay_1sec( );
    gnss15_set_rst_pin( ctx, 1 );
    Delay_1sec( );
}

err_t gnss15_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data )
{    
    if ( gpgga_element > GNSS15_GPGGA_ELEMENT_SIZE )
    {
        return GNSS15_ERROR;
    }
    uint8_t * __generic_ptr start_ptr = strstr( rsp_buf, GNSS15_RSP_GPGGA );
    if ( start_ptr )
    {
        if ( !strstr( start_ptr, GNSS15_RSP_END_SEQ ) )
        {
            return GNSS15_ERROR;
        }
        if ( strstr( start_ptr + 1, GNSS15_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gpgga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS15_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS15_ERROR;
                }
            }
            uint8_t * __generic_ptr end_ptr = strstr( start_ptr, GNSS15_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS15_OK;
            }
        }
    }
    return GNSS15_ERROR;
}

static err_t gnss15_i2c_write ( gnss15_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

static err_t gnss15_i2c_read ( gnss15_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

static err_t gnss15_uart_write ( gnss15_t *ctx, uint8_t *data_in, uint8_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t gnss15_uart_read ( gnss15_t *ctx, uint8_t *data_out, uint8_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

// ------------------------------------------------------------------------- END
