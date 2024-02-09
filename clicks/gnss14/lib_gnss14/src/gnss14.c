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
 * @file gnss14.c
 * @brief GNSS 14 Click Driver.
 */

#include "gnss14.h"
#include "generic_pointer.h"

/**
 * @brief GNSS 14 I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss14_i2c_write ( gnss14_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 14 I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss14_i2c_read ( gnss14_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS 14 UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss14_uart_write ( gnss14_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 14 UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss14_uart_read ( gnss14_t *ctx, uint8_t *data_out, uint8_t len );

void gnss14_cfg_setup ( gnss14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl    = HAL_PIN_NC;
    cfg->sda    = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->io6 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->eit = HAL_PIN_NC;
    cfg->tp = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GNSS14_SET_DEV_ADDR;

    cfg->baud_rate     = 38400;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->drv_sel = GNSS14_DRV_SEL_UART;
}

void gnss14_drv_interface_selection ( gnss14_cfg_t *cfg, gnss14_drv_t drv_sel )
{
    cfg->drv_sel = drv_sel;
}

err_t gnss14_init ( gnss14_t *ctx, gnss14_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( GNSS14_DRV_SEL_UART == ctx->drv_sel )
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

        ctx->read_f  = gnss14_uart_read;
        ctx->write_f = gnss14_uart_write;
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

        ctx->read_f  = gnss14_i2c_read;
        ctx->write_f = gnss14_i2c_write;
    }

    // Output pins
    digital_out_init( &ctx->io6, cfg->io6 );
    digital_out_init( &ctx->rst, cfg->rst );
    
    // Input pins
    digital_in_init( &ctx->eit, cfg->eit );
    digital_in_init( &ctx->tp, cfg->tp );

    return UART_SUCCESS;
}

err_t gnss14_generic_write ( gnss14_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return ctx->write_f( ctx, data_in, len );
}

err_t gnss14_generic_read ( gnss14_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return ctx->read_f( ctx, data_out, len );
}

void gnss14_set_io6_pin ( gnss14_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->io6, state );
}

void gnss14_set_rst_pin ( gnss14_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

uint8_t gnss14_get_eit_pin ( gnss14_t *ctx )
{
    return digital_in_read( &ctx->eit );
}

uint8_t gnss14_get_tp_pin ( gnss14_t *ctx )
{
    return digital_in_read( &ctx->tp );
}

void gnss14_reset_device ( gnss14_t *ctx )
{
    gnss14_set_rst_pin( ctx, 0 );
    Delay_1sec( );
    gnss14_set_rst_pin( ctx, 1 );
    Delay_1sec( );
}

err_t gnss14_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data )
{
    if ( gngga_element > GNSS14_GNGGA_ELEMENT_SIZE )
    {
        return GNSS14_ERROR;
    }
    char * __generic_ptr start_ptr = strstr( rsp_buf, GNSS14_RSP_GNGGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr + 1, GNSS14_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gngga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS14_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS14_ERROR;
                }
            }
            char * __generic_ptr end_ptr = strstr( start_ptr, GNSS14_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS14_OK;
            }
        }
    }
    return GNSS14_ERROR;
}

static err_t gnss14_i2c_write ( gnss14_t *ctx, uint8_t *data_in, uint8_t len )
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

static err_t gnss14_i2c_read ( gnss14_t *ctx, uint8_t *data_out, uint8_t len )
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

static err_t gnss14_uart_write ( gnss14_t *ctx, uint8_t *data_in, uint8_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t gnss14_uart_read ( gnss14_t *ctx, uint8_t *data_out, uint8_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

// ------------------------------------------------------------------------- END
