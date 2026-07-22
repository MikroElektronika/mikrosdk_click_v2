/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file gnssmax4.c
 * @brief GNSS MAX 4 Click Driver.
 */

#include "gnssmax4.h"
#include "generic_pointer.h"

/**
 * @brief GNSS MAX 4 I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnssmax4_i2c_write ( gnssmax4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS MAX 4 I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c >0 - Success - number of bytes read,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnssmax4_i2c_read ( gnssmax4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS MAX 4 UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnssmax4_uart_write ( gnssmax4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS MAX 4 UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnssmax4_uart_read ( gnssmax4_t *ctx, uint8_t *data_out, uint16_t len );

void gnssmax4_cfg_setup ( gnssmax4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->exi = HAL_PIN_NC;
    cfg->pps = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GNSSMAX4_DEVICE_ADDRESS;
    
    cfg->drv_sel = GNSSMAX4_DRV_SEL_I2C;
}

void gnssmax4_drv_interface_sel ( gnssmax4_cfg_t *cfg, gnssmax4_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t gnssmax4_init ( gnssmax4_t *ctx, gnssmax4_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( GNSSMAX4_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = gnssmax4_i2c_read;
        ctx->write_f = gnssmax4_i2c_write;
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

        ctx->read_f  = gnssmax4_uart_read;
        ctx->write_f = gnssmax4_uart_write;
    }

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->exi, cfg->exi );
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->exi );

    // Input pins
    digital_in_init( &ctx->pps, cfg->pps );

    Delay_100ms( );

    return GNSSMAX4_OK;
}

err_t gnssmax4_generic_write ( gnssmax4_t *ctx, uint8_t *data_in, uint16_t len )
{
    return ctx->write_f( ctx, data_in, len );
}

err_t gnssmax4_generic_read ( gnssmax4_t *ctx, uint8_t *data_out, uint16_t len )
{
    return ctx->read_f( ctx, data_out, len );
}

uint8_t gnssmax4_get_pps_pin ( gnssmax4_t *ctx )
{
    return digital_in_read( &ctx->pps );
}

void gnssmax4_set_exi_pin ( gnssmax4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->exi, state );
}

void gnssmax4_set_rst_pin ( gnssmax4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void gnssmax4_reset_device ( gnssmax4_t *ctx )
{   
    /* RST pin has to be low for at least 1 ms to trigger a reset */
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

err_t gnssmax4_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data )
{
    if ( gga_element > GNSSMAX4_GGA_ELEMENT_SIZE )
    {
        return GNSSMAX4_ERROR;
    }

    /* check if the received message is GGA NMEA message */
    uint8_t * __generic_ptr start_ptr = strstr( rsp_buf, GNSSMAX4_RSP_GGA );

    if ( start_ptr )
    {
        /* Check if the whole message is received */
        if ( strstr( start_ptr, ( char * ) GNSSMAX4_RSP_END ) )
        {
            /* count the number of ',' until the targeted element */
            for ( uint8_t element_cnt = 0; element_cnt < gga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSSMAX4_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    /* message shorter than expected */
                    return GNSSMAX4_ERROR;
                }
            }

            /* Start_prt now points to the wanted element.
             * Next ',' will mark the end of the targeted element. */
            uint8_t * __generic_ptr end_ptr = strstr( start_ptr, GNSSMAX4_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSSMAX4_OK;
            }
        }
    }

    return GNSSMAX4_ERROR;
}

static err_t gnssmax4_i2c_write ( gnssmax4_t *ctx, uint8_t *data_in, uint16_t len )
{
    /* A minimum of 2 bytes must be sent otherwise the device will
     * treat it as an address pointer.*/
    return i2c_master_write( &ctx->i2c, data_in, len );
}

static err_t gnssmax4_i2c_read ( gnssmax4_t *ctx, uint8_t *data_out, uint16_t len )
{   
    /* The initial value of the address pointer at startup is 0xFF(where data stream begins)
     * therefore no register address needs to be passed by as an argument */
    if ( GNSSMAX4_OK == i2c_master_read( &ctx->i2c, data_out, len ) )
    {
        return len;
    }
    else
    {
        return GNSSMAX4_ERROR;
    }
}

static err_t gnssmax4_uart_write ( gnssmax4_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t gnssmax4_uart_read ( gnssmax4_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

// ------------------------------------------------------------------------- END
