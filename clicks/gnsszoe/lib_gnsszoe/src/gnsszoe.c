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
 * @file gnsszoe.c
 * @brief GNSS ZOE Click Driver.
 */

#include "gnsszoe.h"
#include "generic_pointer.h"

/**
 * @brief GNSS ZOE I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnsszoe_i2c_write ( gnsszoe_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS ZOE I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnsszoe_i2c_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS ZOE SPI writing function.
 * @details This function writes a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnsszoe_spi_write ( gnsszoe_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS ZOE SPI reading function.
 * @details This function reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnsszoe_spi_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS ZOE UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnsszoe_uart_write ( gnsszoe_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS ZOE UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnsszoe_uart_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len );

void gnsszoe_cfg_setup ( gnsszoe_cfg_t *cfg ) 
{
    cfg->scl     = HAL_PIN_NC;
    cfg->sda     = HAL_PIN_NC;
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->rx_pin  = HAL_PIN_NC;
    cfg->tx_pin  = HAL_PIN_NC;
    cfg->exi     = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GNSSZOE_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;

    cfg->drv_sel = GNSSZOE_DRV_SEL_SPI;
}

void gnsszoe_drv_interface_selection ( gnsszoe_cfg_t *cfg, gnsszoe_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t gnsszoe_init ( gnsszoe_t *ctx, gnsszoe_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( GNSSZOE_DRV_SEL_UART == ctx->drv_sel ) 
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
        
        ctx->read_f  = gnsszoe_uart_read;
        ctx->write_f = gnsszoe_uart_write;
    } 
    else if ( GNSSZOE_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = gnsszoe_i2c_read;
        ctx->write_f = gnsszoe_i2c_write;
    } 
    else 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, GNSSZOE_DUMMY ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        ctx->read_f  = gnsszoe_spi_read;
        ctx->write_f = gnsszoe_spi_write;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->exi, cfg->exi );
    
    digital_out_high ( &ctx->rst );

    return GNSSZOE_OK;
}

err_t gnsszoe_generic_write ( gnsszoe_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, data_in, len );
}

err_t gnsszoe_generic_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, data_out, len );
}

void gnsszoe_set_rst_pin ( gnsszoe_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t gnsszoe_get_exi_pin ( gnsszoe_t *ctx )
{
    return digital_in_read ( &ctx->exi );
}

void gnsszoe_reset_device ( gnsszoe_t *ctx )
{
    gnsszoe_set_rst_pin ( ctx, 0 );
    Delay_1sec ( );
    gnsszoe_set_rst_pin ( ctx, 1 );
    Delay_1sec ( );
}

err_t gnsszoe_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data )
{    
    if ( gngga_element > GNSSZOE_GNGGA_ELEMENT_SIZE )
    {
        return GNSSZOE_ERROR;
    }
    char * __generic_ptr start_ptr = strstr( rsp_buf, GNSSZOE_RSP_GNGGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr + 1, GNSSZOE_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gngga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSSZOE_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSSZOE_ERROR;
                }
            }
            char * __generic_ptr end_ptr = strstr( start_ptr, GNSSZOE_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSSZOE_OK;
            }
        }
    }
    return GNSSZOE_ERROR;
}

static err_t gnsszoe_i2c_write ( gnsszoe_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

static err_t gnsszoe_i2c_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

static err_t gnsszoe_spi_write ( gnsszoe_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t gnsszoe_spi_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t gnsszoe_uart_write ( gnsszoe_t *ctx, uint8_t *data_in, uint8_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t gnsszoe_uart_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

// ------------------------------------------------------------------------ END
