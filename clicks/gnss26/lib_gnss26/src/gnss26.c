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
 * @file gnss26.c
 * @brief GNSS 26 Click Driver.
 */

#include "gnss26.h"
#include "generic_pointer.h"

/**
 * @brief GNSS 26 I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss26_i2c_write ( gnss26_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 26 I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c >0 - Success - number of bytes read,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss26_i2c_read ( gnss26_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 26 UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss26_uart_write ( gnss26_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 26 UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss26_uart_read ( gnss26_t *ctx, uint8_t *data_out, uint16_t len );

void gnss26_cfg_setup ( gnss26_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->pps = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GNSS26_I2C_SLAVE_ADDRESS_CR_OR_CW;
    
    cfg->drv_sel = GNSS26_DRV_SEL_I2C;
}

void gnss26_drv_interface_sel ( gnss26_cfg_t *cfg, gnss26_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t gnss26_init ( gnss26_t *ctx, gnss26_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low( &ctx->rst );

    // Input pins
    digital_in_init( &ctx->pps, cfg->pps );
    Delay_100ms ( );

    digital_out_high( &ctx->rst );
    Delay_1sec ( );

    if ( GNSS26_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = gnss26_i2c_read;
        ctx->write_f = gnss26_i2c_write;
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

        ctx->read_f  = gnss26_uart_read;
        ctx->write_f = gnss26_uart_write;
    }

    return GNSS26_OK;
}

err_t gnss26_generic_write ( gnss26_t *ctx, uint8_t *data_in, uint16_t len )
{
    return ctx->write_f( ctx, data_in, len );
}

err_t gnss26_generic_read ( gnss26_t *ctx, uint8_t *data_out, uint16_t len )
{
    return ctx->read_f( ctx, data_out, len );
}

uint8_t gnss26_get_pps_pin ( gnss26_t *ctx )
{
    return digital_in_read ( &ctx->pps );
}

void gnss26_set_rst_pin ( gnss26_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void gnss26_reset_device ( gnss26_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

err_t gnss26_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data )
{
    if ( gga_element > GNSS26_GGA_ELEMENT_SIZE )
    {
        return GNSS26_ERROR;
    }
    uint8_t * __generic_ptr start_ptr = strstr( rsp_buf, GNSS26_RSP_GGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr, ( char * ) GNSS26_RSP_END ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS26_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS26_ERROR;
                }
            }
            uint8_t * __generic_ptr end_ptr = strstr( start_ptr, GNSS26_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS26_OK;
            }
        }
    }
    return GNSS26_ERROR;
}

static err_t gnss26_i2c_write ( gnss26_t *ctx, uint8_t *data_in, uint16_t len )
{
    uint8_t error_cnt = 0;
    uint32_t rx_len = 0;
    uint8_t data_buf[ GNSS26_I2C_SLAVE_CMD_LEN ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( GNSS26_I2C_SLAVE_RX_LEN_REG_OFFSET & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( GNSS26_I2C_SLAVE_RX_LEN_REG_OFFSET >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( GNSS26_I2C_SLAVE_CR_CMD & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( GNSS26_I2C_SLAVE_CR_CMD >> 8 ) & 0xFF );
    data_buf[ 4 ] = GNSS26_I2C_SLAVE_RX_LEN;
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS26_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS26_OK == i2c_master_write( &ctx->i2c, data_buf, GNSS26_I2C_SLAVE_CMD_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS26_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS26_ERROR;
        }
    }
    
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS26_I2C_SLAVE_ADDRESS_R );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS26_OK == i2c_master_read( &ctx->i2c, data_buf, GNSS26_I2C_SLAVE_RX_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS26_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS26_ERROR;
        }
    }
    rx_len = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
             ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    if ( len > rx_len )
    {
        return GNSS26_ERROR;
    }
    
    data_buf[ 0 ] = ( uint8_t ) ( GNSS26_I2C_SLAVE_RX_BUF_REG_OFFSET & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( GNSS26_I2C_SLAVE_RX_BUF_REG_OFFSET >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( GNSS26_I2C_SLAVE_CW_CMD & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( GNSS26_I2C_SLAVE_CW_CMD >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( len & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( len >> 8 ) & 0xFF );
    data_buf[ 6 ] = 0;
    data_buf[ 7 ] = 0;
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS26_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS26_OK == i2c_master_write( &ctx->i2c, data_buf, GNSS26_I2C_SLAVE_CMD_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS26_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS26_ERROR;
        }
    }
    
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS26_I2C_SLAVE_ADDRESS_W );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS26_OK == i2c_master_write( &ctx->i2c, data_in, len ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS26_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS26_ERROR;
        }
    }
    return len;
}

static err_t gnss26_i2c_read ( gnss26_t *ctx, uint8_t *data_out, uint16_t len )
{
    uint8_t error_cnt = 0;
    uint32_t rx_len = 0;
    uint8_t data_buf[ GNSS26_I2C_SLAVE_CMD_LEN ] = { 0 };
    
    data_buf[ 0 ] = ( uint8_t ) ( GNSS26_I2C_SLAVE_TX_LEN_REG_OFFSET & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( GNSS26_I2C_SLAVE_TX_LEN_REG_OFFSET >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( GNSS26_I2C_SLAVE_CR_CMD & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( GNSS26_I2C_SLAVE_CR_CMD >> 8 ) & 0xFF );
    data_buf[ 4 ] = GNSS26_I2C_SLAVE_RX_LEN;
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS26_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS26_OK == i2c_master_write( &ctx->i2c, data_buf, GNSS26_I2C_SLAVE_CMD_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS26_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS26_ERROR;
        }
    }
    
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS26_I2C_SLAVE_ADDRESS_R );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS26_OK == i2c_master_read( &ctx->i2c, data_buf, GNSS26_I2C_SLAVE_RX_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS26_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS26_ERROR;
        }
    }
    rx_len = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
             ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    if ( 0 == rx_len )
    {
        return GNSS26_OK;
    }
    if ( rx_len > len )
    {
        rx_len = len;
    }
    
    data_buf[ 0 ] = ( uint8_t ) ( GNSS26_I2C_SLAVE_TX_BUF_REG_OFFSET & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( GNSS26_I2C_SLAVE_TX_BUF_REG_OFFSET >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( GNSS26_I2C_SLAVE_CR_CMD & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( GNSS26_I2C_SLAVE_CR_CMD >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( rx_len & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( rx_len >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( rx_len >> 16 ) & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( ( rx_len >> 24 ) & 0xFF );
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS26_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS26_OK == i2c_master_write( &ctx->i2c, data_buf, GNSS26_I2C_SLAVE_CMD_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS26_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS26_ERROR;
        }
    }
    
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS26_I2C_SLAVE_ADDRESS_R );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS26_OK == i2c_master_read( &ctx->i2c, data_out, rx_len ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS26_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS26_ERROR;
        }
    }
    return rx_len;
}

static err_t gnss26_uart_write ( gnss26_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t gnss26_uart_read ( gnss26_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

// ------------------------------------------------------------------------- END
