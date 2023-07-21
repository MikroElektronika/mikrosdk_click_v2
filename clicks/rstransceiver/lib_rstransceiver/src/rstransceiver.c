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
 * @file rstransceiver.c
 * @brief RS Transceiver Click Driver.
 */

#include "rstransceiver.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY    0x00

/**
 * @brief RS Transceiver I2C writing function.
 * @details This function writes a desired data byte 
 * to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rstransceiver_i2c_write ( rstransceiver_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RS Transceiver I2C reading function.
 * @details This function reads a data byte
 * from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rstransceiver_i2c_read ( rstransceiver_t *ctx, uint8_t reg, uint8_t *data_out );

void rstransceiver_cfg_setup ( rstransceiver_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // UART communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->slw = HAL_PIN_NC;
    cfg->cst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RSTRANSCEIVER_DEVICE_ADDRESS;
    
    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t rstransceiver_init ( rstransceiver_t *ctx, rstransceiver_cfg_t *cfg ) 
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
    Delay_10ms( );
    
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->slw, cfg->slw );

    digital_in_init( &ctx->cst, cfg->cst );

    return I2C_MASTER_SUCCESS;
}

err_t rstransceiver_default_cfg ( rstransceiver_t *ctx ) 
{
    // Enable the device for operation
    rstransceiver_device_enable( ctx );
    Delay_100ms( );
    
    // Enables 250 kbps slew limiting
    rstransceiver_set_slew( ctx, RSTRANSCEIVER_SLEW_ENABLE );
    Delay_10ms( );
    
    // Sets the output direction of all pins
    err_t err_flag = rstransceiver_i2c_write( ctx, RSTRANSCEIVER_REG_CONFIG, RSTRANSCEIVER_OUTPUT_DIRECTION );
    Delay_10ms( );
    
    // All the internal pull-up resistors are disabled
    err_flag |= rstransceiver_i2c_write( ctx, RSTRANSCEIVER_REG_SPECIAL_FUNC, RSTRANSCEIVER_SPECIAL_FUNC_PU_DISABLED );
    Delay_10ms( );
    
    // Mode Selection: Loopback
    err_flag |= rstransceiver_set_op_mode( ctx, RSTRANSCEIVER_OP_MODE_LOOPBACK );
    Delay_10ms( );
    
    // Direction: RX (T1) enable
    err_flag |= rstransceiver_set_dir1( ctx, RSTRANSCEIVER_DIR_T1_EN );
    Delay_10ms( );
    
    // Enables RS485/RS422 receiver termination
    err_flag |= rstransceiver_term_enable( ctx );
    Delay_10ms( );

    return err_flag;
}

void rstransceiver_device_enable ( rstransceiver_t *ctx ) 
{
    digital_out_high( &ctx->rst );
}

void rstransceiver_device_disable ( rstransceiver_t *ctx ) 
{
    digital_out_low( &ctx->rst );
}

void rstransceiver_set_slew ( rstransceiver_t *ctx, uint8_t slew ) 
{
    digital_out_write( &ctx->slw, slew );
}

void rstransceiver_set_rts ( rstransceiver_t *ctx, uint8_t rts ) 
{
    digital_out_write( &ctx->cs, rts );
}

uint8_t rstransceiver_get_cts ( rstransceiver_t *ctx ) 
{
    return digital_in_read( &ctx->cst );
}

err_t rstransceiver_set_op_mode ( rstransceiver_t *ctx, uint8_t op_mode )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = rstransceiver_i2c_read( ctx, RSTRANSCEIVER_REG_OUTPUT_PORT, &data_buf );
    data_buf &= RSTRANSCEIVER_OP_MODE_PIN_BIT_MASK;
    Delay_1ms( );
    switch ( op_mode )
    {
        case RSTRANSCEIVER_OP_MODE_LOOPBACK: 
        {
            data_buf |= RSTRANSCEIVER_NO_PIN_BIT_MASK;
            break;
        }
        case RSTRANSCEIVER_OP_MODE_RS232: 
        {
            data_buf |= RSTRANSCEIVER_PIN_1_BIT_MASK;
            break;
        }
        case RSTRANSCEIVER_OP_MODE_HALF_DUPLEX: 
        {
            data_buf |= RSTRANSCEIVER_PIN_2_BIT_MASK;
            break;
        }
        case RSTRANSCEIVER_OP_MODE_FULL_DUPLEX: 
        {
            data_buf |= RSTRANSCEIVER_PIN_1_BIT_MASK | 
                        RSTRANSCEIVER_PIN_2_BIT_MASK;
            break;
        }
        default: 
        {
            data_buf |= RSTRANSCEIVER_NO_PIN_BIT_MASK;
            break;
        }
    }
    err_flag |= rstransceiver_i2c_write( ctx, RSTRANSCEIVER_REG_OUTPUT_PORT, data_buf );
    return err_flag;
}

err_t rstransceiver_mode_loopback ( rstransceiver_t *ctx )
{
    return rstransceiver_set_op_mode( ctx, RSTRANSCEIVER_OP_MODE_LOOPBACK );
}

err_t rstransceiver_mode_rs232 ( rstransceiver_t *ctx, uint8_t slew )
{
    rstransceiver_set_slew( ctx, slew );
    return rstransceiver_set_op_mode( ctx, RSTRANSCEIVER_OP_MODE_RS232 );
}

err_t rstransceiver_mode_half_duplex ( rstransceiver_t *ctx, uint8_t slew, uint8_t dir1, uint8_t term )
{
    rstransceiver_set_slew( ctx, slew );
    err_t err_flag = rstransceiver_set_dir1( ctx, dir1 );
    if ( RSTRANSCEIVER_TERM_DISABLE == term )
    {
        err_flag |= rstransceiver_term_disable( ctx );
    }
    else
    {
        err_flag |= rstransceiver_term_enable( ctx );
    }
    
    err_flag |= rstransceiver_set_op_mode( ctx, RSTRANSCEIVER_OP_MODE_HALF_DUPLEX );
    return err_flag;
}

err_t rstransceiver_mode_full_duplex ( rstransceiver_t *ctx, uint8_t slew, uint8_t dir1, uint8_t term )
{
    rstransceiver_set_slew( ctx, slew );
    err_t err_flag = rstransceiver_set_dir1( ctx, dir1 );
    if ( RSTRANSCEIVER_TERM_DISABLE == term )
    {
        err_flag |= rstransceiver_term_disable( ctx );
    }
    else
    {
        err_flag |= rstransceiver_term_enable( ctx );
    }
    err_flag |= rstransceiver_set_op_mode( ctx, RSTRANSCEIVER_OP_MODE_FULL_DUPLEX );
    return err_flag;
}

err_t rstransceiver_set_dir1 ( rstransceiver_t *ctx, uint8_t dir1 )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = rstransceiver_i2c_read( ctx, RSTRANSCEIVER_REG_OUTPUT_PORT, &data_buf );
    data_buf &= RSTRANSCEIVER_DIR_PIN_BIT_MASK;
    data_buf |= dir1;
    err_flag |= rstransceiver_i2c_write( ctx, RSTRANSCEIVER_REG_OUTPUT_PORT, data_buf );
    return err_flag;
}

err_t rstransceiver_term_enable ( rstransceiver_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = rstransceiver_i2c_read( ctx, RSTRANSCEIVER_REG_OUTPUT_PORT, &data_buf );
    data_buf |= RSTRANSCEIVER_TERM_EN_PIN_BIT_MASK;
    err_flag |= rstransceiver_i2c_write( ctx, RSTRANSCEIVER_REG_OUTPUT_PORT, data_buf );
    return err_flag;
}

err_t rstransceiver_term_disable ( rstransceiver_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = rstransceiver_i2c_read( ctx, RSTRANSCEIVER_REG_OUTPUT_PORT, &data_buf );
    data_buf &= RSTRANSCEIVER_TERM_DIS_PIN_BIT_MASK;
    err_flag |= rstransceiver_i2c_write( ctx, RSTRANSCEIVER_REG_OUTPUT_PORT, data_buf );
    return err_flag;
}

err_t rstransceiver_generic_write ( rstransceiver_t *ctx, char *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t rstransceiver_generic_read ( rstransceiver_t *ctx, char *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

static err_t rstransceiver_i2c_write ( rstransceiver_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

static err_t rstransceiver_i2c_read ( rstransceiver_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

// ------------------------------------------------------------------------- END
