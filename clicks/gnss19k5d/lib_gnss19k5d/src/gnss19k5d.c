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
 * @file gnss19k5d.c
 * @brief GNSS 19 K5-D Click Driver.
 */

#include "gnss19k5d.h"
#include "generic_pointer.h"

/**
 * @brief GNSS 19 K5-D I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss19k5d_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss19k5d_i2c_write ( gnss19k5d_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 19 K5-D I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss19k5d_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c >0 - Success - number of bytes read,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss19k5d_i2c_read ( gnss19k5d_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 19 K5-D UART writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss19k5d_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss19k5d_uart_write ( gnss19k5d_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 19 K5-D UART reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss19k5d_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss19k5d_uart_read ( gnss19k5d_t *ctx, uint8_t *data_out, uint16_t len );

void gnss19k5d_cfg_setup ( gnss19k5d_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->out_pin = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->son = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GNSS19K5D_I2C_SLAVE_ADDRESS_CR_OR_CW;
    
    cfg->drv_sel = GNSS19K5D_DRV_SEL_UART;
}

void gnss19k5d_drv_interface_sel ( gnss19k5d_cfg_t *cfg, gnss19k5d_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t gnss19k5d_init ( gnss19k5d_t *ctx, gnss19k5d_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->cts );

    // Input pins
    digital_in_init( &ctx->out_pin, cfg->out_pin );
    digital_in_init( &ctx->son, cfg->son );
    digital_in_init( &ctx->rts, cfg->rts );
    Delay_100ms ( );

    digital_out_high( &ctx->rst );
    Delay_1sec ( );

    if ( GNSS19K5D_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = gnss19k5d_i2c_read;
        ctx->write_f = gnss19k5d_i2c_write;
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

        ctx->read_f  = gnss19k5d_uart_read;
        ctx->write_f = gnss19k5d_uart_write;
    }

    return GNSS19K5D_OK;
}

err_t gnss19k5d_generic_write ( gnss19k5d_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return ctx->write_f( ctx, data_in, len );
}

err_t gnss19k5d_generic_read ( gnss19k5d_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return ctx->read_f( ctx, data_out, len );
}

uint8_t gnss19k5d_get_son_pin ( gnss19k5d_t *ctx )
{
    return !!digital_in_read ( &ctx->son );
}

uint8_t gnss19k5d_get_out_pin ( gnss19k5d_t *ctx )
{
    return !!digital_in_read ( &ctx->out_pin );
}

uint8_t gnss19k5d_get_rts_pin ( gnss19k5d_t *ctx )
{
    return !!digital_in_read ( &ctx->rts );
}

void gnss19k5d_set_cts_pin ( gnss19k5d_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

void gnss19k5d_set_rst_pin ( gnss19k5d_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void gnss19k5d_reset_device ( gnss19k5d_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

err_t gnss19k5d_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data )
{
    if ( gga_element > GNSS19K5D_GGA_ELEMENT_SIZE )
    {
        return GNSS19K5D_ERROR;
    }
    uint8_t * __generic_ptr start_ptr = strstr( rsp_buf, GNSS19K5D_RSP_GGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr, ( char * ) GNSS19K5D_RSP_END ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS19K5D_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS19K5D_ERROR;
                }
            }
            uint8_t * __generic_ptr end_ptr = strstr( start_ptr, GNSS19K5D_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS19K5D_OK;
            }
        }
    }
    return GNSS19K5D_ERROR;
}

static err_t gnss19k5d_i2c_write ( gnss19k5d_t *ctx, uint8_t *data_in, uint16_t len )
{
    uint8_t error_cnt = 0;
    uint32_t rx_len = 0;
    uint8_t data_buf[ GNSS19K5D_I2C_SLAVE_CMD_LEN ] = { 0 };
    data_buf[ 0 ] = 0;
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        // Check slave alive
        if ( GNSS19K5D_OK == i2c_master_write( &ctx->i2c, data_buf, 1 ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }

    data_buf[ 0 ] = ( uint8_t ) ( GNSS19K5D_I2C_SLAVE_RX_LEN_REG_OFFSET & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( GNSS19K5D_I2C_SLAVE_RX_LEN_REG_OFFSET >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( GNSS19K5D_I2C_SLAVE_CR_CMD & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( GNSS19K5D_I2C_SLAVE_CR_CMD >> 8 ) & 0xFF );
    data_buf[ 4 ] = GNSS19K5D_I2C_SLAVE_RX_LEN;
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS19K5D_OK == i2c_master_write( &ctx->i2c, data_buf, GNSS19K5D_I2C_SLAVE_CMD_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_R );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS19K5D_OK == i2c_master_read( &ctx->i2c, data_buf, GNSS19K5D_I2C_SLAVE_RX_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    rx_len = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
             ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    if ( len > rx_len )
    {
        return GNSS19K5D_ERROR;
    }
    
    data_buf[ 0 ] = ( uint8_t ) ( GNSS19K5D_I2C_SLAVE_RX_BUF_REG_OFFSET & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( GNSS19K5D_I2C_SLAVE_RX_BUF_REG_OFFSET >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( GNSS19K5D_I2C_SLAVE_CW_CMD & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( GNSS19K5D_I2C_SLAVE_CW_CMD >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( len & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( len >> 8 ) & 0xFF );
    data_buf[ 6 ] = 0;
    data_buf[ 7 ] = 0;
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS19K5D_OK == i2c_master_write( &ctx->i2c, data_buf, GNSS19K5D_I2C_SLAVE_CMD_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_W );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS19K5D_OK == i2c_master_write( &ctx->i2c, data_in, len ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    return len;
}

static err_t gnss19k5d_i2c_read ( gnss19k5d_t *ctx, uint8_t *data_out, uint16_t len )
{
    uint8_t error_cnt = 0;
    uint32_t rx_len = 0;
    uint8_t data_buf[ GNSS19K5D_I2C_SLAVE_CMD_LEN ] = { 0 };
    data_buf[ 0 ] = 0;
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        // Check slave alive
        if ( GNSS19K5D_OK == i2c_master_write( &ctx->i2c, data_buf, 1 ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    
    data_buf[ 0 ] = ( uint8_t ) ( GNSS19K5D_I2C_SLAVE_TX_LEN_REG_OFFSET & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( GNSS19K5D_I2C_SLAVE_TX_LEN_REG_OFFSET >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( GNSS19K5D_I2C_SLAVE_CR_CMD & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( GNSS19K5D_I2C_SLAVE_CR_CMD >> 8 ) & 0xFF );
    data_buf[ 4 ] = GNSS19K5D_I2C_SLAVE_RX_LEN;
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS19K5D_OK == i2c_master_write( &ctx->i2c, data_buf, GNSS19K5D_I2C_SLAVE_CMD_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_R );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS19K5D_OK == i2c_master_read( &ctx->i2c, data_buf, GNSS19K5D_I2C_SLAVE_RX_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    rx_len = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
             ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    if ( 0 == rx_len )
    {
        return GNSS19K5D_OK;
    }
    if ( rx_len > len )
    {
        rx_len = len;
    }
    
    data_buf[ 0 ] = ( uint8_t ) ( GNSS19K5D_I2C_SLAVE_TX_BUF_REG_OFFSET & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( GNSS19K5D_I2C_SLAVE_TX_BUF_REG_OFFSET >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( GNSS19K5D_I2C_SLAVE_CR_CMD & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( GNSS19K5D_I2C_SLAVE_CR_CMD >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( rx_len & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( rx_len >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( rx_len >> 16 ) & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( ( rx_len >> 24 ) & 0xFF );
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_CR_OR_CW );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS19K5D_OK == i2c_master_write( &ctx->i2c, data_buf, GNSS19K5D_I2C_SLAVE_CMD_LEN ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    
    error_cnt = 0;
    i2c_master_set_slave_address( &ctx->i2c, GNSS19K5D_I2C_SLAVE_ADDRESS_R );
    for ( ; ; )
    {
        Delay_10ms ( );
        Delay_10ms ( );
        if ( GNSS19K5D_OK == i2c_master_read( &ctx->i2c, data_out, rx_len ) )
        {
            break;
        }
        if ( ++error_cnt > GNSS19K5D_I2C_SLAVE_MAX_ERRORS )
        {
            return GNSS19K5D_ERROR;
        }
    }
    return rx_len;
}

static err_t gnss19k5d_uart_write ( gnss19k5d_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

static err_t gnss19k5d_uart_read ( gnss19k5d_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

// ------------------------------------------------------------------------- END
