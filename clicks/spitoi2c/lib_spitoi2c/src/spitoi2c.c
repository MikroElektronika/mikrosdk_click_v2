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
 * @file spitoi2c.c
 * @brief SPI to I2C Click Driver.
 */

#include "spitoi2c.h"

/**
 * @brief SPI to I2C spi select function.
 * @details This function selects the SPI device by clearing the CS pin.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void spitoi2c_spi_select ( spitoi2c_t *ctx );

/**
 * @brief SPI to I2C spi deselect function.
 * @details This function deselects the SPI device by setting the CS pin.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void spitoi2c_spi_deselect ( spitoi2c_t *ctx );

/**
 * @brief SPI to I2C spi write function.
 * @details This function writes a desired number of data bytes to SPI SPI interface using bit-banging.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return None.
 * @note None.
 */
static void spitoi2c_spi_write ( spitoi2c_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief SPI to I2C spi read function.
 * @details This function reads a desired number of data bytes from SPI interface using bit-banging.
 * @param[in] ctx : Click context object.
 * See #spitoi2c_t object definition for detailed explanation.
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of bytes to be read.
 * @return None.
 * @note None.
 */
static void spitoi2c_spi_read ( spitoi2c_t *ctx, uint8_t *data_out, uint8_t len );

void spitoi2c_cfg_setup ( spitoi2c_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t spitoi2c_init ( spitoi2c_t *ctx, spitoi2c_cfg_t *cfg ) 
{
    err_t error_flag = SPITOI2C_OK;

    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->sck, cfg->sck );
    error_flag |= digital_out_init( &ctx->mosi, cfg->mosi );
    error_flag |= digital_out_init( &ctx->cs, cfg->cs );

    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->cs );
    digital_out_low ( &ctx->sck );
    digital_out_low ( &ctx->mosi );
    Delay_10ms ( );

    digital_out_low ( &ctx->rst );
    digital_out_high ( &ctx->cs );
    digital_out_high ( &ctx->sck );
    digital_out_high ( &ctx->mosi );
    Delay_10ms ( );

    error_flag |= digital_in_init( &ctx->miso, cfg->miso );
    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    return error_flag;
}

err_t spitoi2c_default_cfg ( spitoi2c_t *ctx ) 
{
    err_t error_flag = SPITOI2C_OK;
    spitoi2c_disable_device ( ctx );
    Delay_100ms ( );
    spitoi2c_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= spitoi2c_gpio_config ( ctx, SPITOI2C_PIN_DIR_OUTPUT_PP, SPITOI2C_PIN_0_MASK |
                                                                          SPITOI2C_PIN_1_MASK | 
                                                                          SPITOI2C_PIN_2_MASK );
    error_flag |= spitoi2c_gpio_config ( ctx, SPITOI2C_PIN_DIR_INPUT, SPITOI2C_PIN_3_MASK ); // gpio 4 is input only
    error_flag |= spitoi2c_gpio_write ( ctx, SPITOI2C_NO_PIN_MASK );
    error_flag |= spitoi2c_write_register ( ctx, SPITOI2C_REG_I2C_CLOCK, SPITOI2C_I2C_CLOCK_99_KHZ );
    error_flag |= spitoi2c_write_register ( ctx, SPITOI2C_REG_I2C_ADR, SPITOI2C_I2C_ADDR_127 );
    error_flag |= spitoi2c_write_register ( ctx, SPITOI2C_REG_I2C_TO, SPITOI2C_I2C_TO_DISABLE );
    Delay_1sec ( );
    Delay_1sec ( );
    return error_flag;
}

err_t spitoi2c_gpio_write ( spitoi2c_t *ctx, uint8_t gpio_data )
{
    return spitoi2c_write_register ( ctx, SPITOI2C_REG_IO_STATE, gpio_data & SPITOI2C_ALL_OUT_PINS_MASK );
}

err_t spitoi2c_gpio_read ( spitoi2c_t *ctx, uint8_t *gpio_data )
{
    if ( NULL == gpio_data )
    {
        return SPITOI2C_ERROR;
    }
    return spitoi2c_read_register ( ctx, SPITOI2C_REG_IO_STATE, gpio_data );
}

err_t spitoi2c_gpio_config ( spitoi2c_t *ctx, uint8_t direction, uint8_t pin_mask )
{
    if ( ( direction > SPITOI2C_PIN_DIR_MASK ) || ( pin_mask >= SPITOI2C_PIN_4_MASK ) )
    {
        return SPITOI2C_ERROR;
    }
    err_t error_flag = SPITOI2C_OK;
    uint8_t io_cfg = 0;
    error_flag |= spitoi2c_read_register ( ctx, SPITOI2C_REG_IO_CONFIG, &io_cfg );
    if ( SPITOI2C_OK == error_flag )
    {
        for ( uint8_t pin = 0; pin < 4; pin++ )
        {
            if ( pin_mask & ( SPITOI2C_PIN_0_MASK << pin ) )
            {
                io_cfg &= ~( SPITOI2C_PIN_DIR_MASK << ( pin * 2 ) );
                io_cfg |= ( direction << ( pin * 2 ) );
            }
        }
        error_flag |= spitoi2c_write_register ( ctx, SPITOI2C_REG_IO_CONFIG, io_cfg );
    }
    return error_flag;
}

err_t spitoi2c_read_i2c_status ( spitoi2c_t *ctx, uint8_t *i2c_stat )
{
    if ( NULL == i2c_stat )
    {
        return SPITOI2C_ERROR;
    }
    return spitoi2c_read_register ( ctx, SPITOI2C_REG_I2C_STAT, i2c_stat );
}

err_t spitoi2c_i2c_write ( spitoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len )
{
    if ( NULL == data_in )
    {
        return SPITOI2C_ERROR;
    }
    uint16_t timeout_cnt = 0;
    uint8_t data_buf[ 3 ] = { SPITOI2C_CMD_WRITE, len, ( slave_addr << 1 ) };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 3 );
    spitoi2c_spi_write ( ctx, data_in, len );
    spitoi2c_spi_deselect ( ctx );
    while ( spitoi2c_get_int_pin ( ctx ) )
    {
        if ( ++timeout_cnt > SPITOI2C_TIMEOUT_MS )
        {
            return SPITOI2C_ERROR;
        }
        Delay_1ms ( );
    }
    Delay_1ms ( );
    spitoi2c_read_i2c_status ( ctx, data_buf );
    if ( SPITOI2C_I2C_STATUS_SUCCESS != data_buf[ 0 ] )
    {
        return data_buf[ 0 ];
    }
    return SPITOI2C_OK;
}

err_t spitoi2c_i2c_read ( spitoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_out, uint8_t len )
{
    if ( NULL == data_out )
    {
        return SPITOI2C_ERROR;
    }
    uint16_t timeout_cnt = 0;
    uint8_t data_buf[ 3 ] = { SPITOI2C_CMD_READ, len, ( ( slave_addr << 1 ) | SPITOI2C_I2C_READ_BIT ) };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 3 );
    spitoi2c_spi_deselect ( ctx );
    while ( spitoi2c_get_int_pin ( ctx ) )
    {
        if ( ++timeout_cnt > SPITOI2C_TIMEOUT_MS )
        {
            return SPITOI2C_ERROR;
        }
        Delay_1ms ( );
    }
    Delay_1ms ( );
    spitoi2c_read_i2c_status ( ctx, data_buf );
    if ( SPITOI2C_I2C_STATUS_SUCCESS != data_buf[ 0 ] )
    {
        return data_buf[ 0 ];
    }
    spitoi2c_read_buffer ( ctx, data_out, len );
    return SPITOI2C_OK;
}

err_t spitoi2c_i2c_read_after_write ( spitoi2c_t *ctx, uint8_t slave_addr, 
                                      uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len )
{
    if ( ( NULL == data_in ) || ( NULL == data_out ) )
    {
        return SPITOI2C_ERROR;
    }
    uint16_t timeout_cnt = 0;
    uint8_t data_buf[ 4 ] = { SPITOI2C_CMD_READ_AFTER_WRITE, in_len, out_len, ( slave_addr << 1 ) };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 4 );
    spitoi2c_spi_write ( ctx, data_in, in_len );
    data_buf[ 3 ] |= SPITOI2C_I2C_READ_BIT;
    spitoi2c_spi_write ( ctx, &data_buf[ 3 ], 1 );
    spitoi2c_spi_deselect ( ctx );
    while ( spitoi2c_get_int_pin ( ctx ) )
    {
        if ( ++timeout_cnt > SPITOI2C_TIMEOUT_MS )
        {
            return SPITOI2C_ERROR;
        }
        Delay_1ms ( );
    }
    Delay_1ms ( );
    spitoi2c_read_i2c_status ( ctx, data_buf );
    if ( SPITOI2C_I2C_STATUS_SUCCESS != data_buf[ 0 ] )
    {
        return data_buf[ 0 ];
    }
    spitoi2c_read_buffer ( ctx, data_out, out_len );
    return SPITOI2C_OK;
}

err_t spitoi2c_i2c_write_after_write ( spitoi2c_t *ctx, uint8_t slave_addr, 
                                       uint8_t *data_in1, uint8_t in1_len, uint8_t *data_in2, uint8_t in2_len )
{
    if ( ( NULL == data_in1 ) || ( NULL == data_in2 ) )
    {
        return SPITOI2C_ERROR;
    }
    uint16_t timeout_cnt = 0;
    uint8_t data_buf[ 4 ] = { SPITOI2C_CMD_WRITE_AFTER_WRITE, in1_len, in2_len, ( slave_addr << 1 ) };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 4 );
    spitoi2c_spi_write ( ctx, data_in1, in1_len );
    spitoi2c_spi_write ( ctx, &data_buf[ 3 ], 1 );
    spitoi2c_spi_write ( ctx, data_in2, in2_len );
    spitoi2c_spi_deselect ( ctx );
    while ( spitoi2c_get_int_pin ( ctx ) )
    {
        if ( ++timeout_cnt > SPITOI2C_TIMEOUT_MS )
        {
            return SPITOI2C_ERROR;
        }
        Delay_1ms ( );
    }
    Delay_1ms ( );
    spitoi2c_read_i2c_status ( ctx, data_buf );
    if ( SPITOI2C_I2C_STATUS_SUCCESS != data_buf[ 0 ] )
    {
        return data_buf[ 0 ];
    }
    return SPITOI2C_OK;
}

void spitoi2c_read_buffer ( spitoi2c_t *ctx, uint8_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 1 ] = { SPITOI2C_CMD_READ_BUFFER };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 1 );
    spitoi2c_spi_read ( ctx, data_out, len );
    spitoi2c_spi_deselect ( ctx );
}

err_t spitoi2c_set_spi_config ( spitoi2c_t *ctx, uint8_t spi_cfg )
{
    if ( ( SPITOI2C_SPI_CONFIG_LSB_FIRST != spi_cfg ) && ( SPITOI2C_SPI_CONFIG_MSB_FIRST != spi_cfg ) )
    {
        return SPITOI2C_ERROR;
    }
    uint8_t data_buf[ 2 ] = { SPITOI2C_CMD_SPI_CONFIG, spi_cfg };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 2 );
    spitoi2c_spi_deselect ( ctx );
    return SPITOI2C_OK;
}

err_t spitoi2c_write_register ( spitoi2c_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( reg > SPITOI2C_REG_I2C_ADR )
    {
        return SPITOI2C_ERROR;
    }
    uint8_t data_buf[ 3 ] = { SPITOI2C_CMD_WRITE_REG, reg, data_in };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 3 );
    spitoi2c_spi_deselect ( ctx );
    return SPITOI2C_OK;
}

err_t spitoi2c_read_register ( spitoi2c_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( reg > SPITOI2C_REG_I2C_ADR )
    {
        return SPITOI2C_ERROR;
    }
    uint8_t data_buf[ 2 ] = { SPITOI2C_CMD_READ_REG, reg };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 2 );
    spitoi2c_spi_read ( ctx, data_out, 1 );
    spitoi2c_spi_deselect ( ctx );
    return SPITOI2C_OK;
}

void spitoi2c_deep_power_down ( spitoi2c_t *ctx )
{
    uint8_t data_buf[ 3 ] = { SPITOI2C_CMD_DEEP_POWER_DOWN, SPITOI2C_DEEP_PDOWN_BYTE_0, SPITOI2C_DEEP_PDOWN_BYTE_1 };
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, data_buf, 3 );
    spitoi2c_spi_deselect ( ctx );
}

void spitoi2c_wake_up ( spitoi2c_t *ctx )
{
    spitoi2c_spi_select ( ctx );
    Delay_100ms ( );
    spitoi2c_spi_deselect ( ctx );
    Delay_1ms ( );
}

err_t spitoi2c_read_version ( spitoi2c_t *ctx, uint8_t *version )
{
    if ( NULL == version )
    {
        return SPITOI2C_ERROR;
    }
    uint16_t timeout_cnt = 0;
    uint8_t cmd = SPITOI2C_CMD_READ_VERSION;
    spitoi2c_spi_select ( ctx );
    spitoi2c_spi_write ( ctx, &cmd, 1 );
    spitoi2c_spi_deselect ( ctx );
    while ( spitoi2c_get_int_pin ( ctx ) )
    {
        if ( ++timeout_cnt > SPITOI2C_TIMEOUT_MS )
        {
            return SPITOI2C_ERROR;
        }
        Delay_1ms ( );
    }
    Delay_1ms ( );
    spitoi2c_read_buffer ( ctx, version, 16 );
    return SPITOI2C_OK;
}

void spitoi2c_enable_device ( spitoi2c_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void spitoi2c_disable_device ( spitoi2c_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

uint8_t spitoi2c_get_int_pin ( spitoi2c_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

static void spitoi2c_spi_select ( spitoi2c_t *ctx )
{
    Delay_10us ( );
    digital_out_low ( &ctx->cs );
    Delay_10us ( );
}

static void spitoi2c_spi_deselect ( spitoi2c_t *ctx )
{
    Delay_10us ( );
    digital_out_high ( &ctx->cs );
    Delay_10us ( );
}

static void spitoi2c_spi_write ( spitoi2c_t *ctx, uint8_t *data_in, uint8_t len )
{
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( data_in[ byte_cnt ] & ( 0x80 >> bit_cnt ) )
            {
                digital_out_high ( &ctx->mosi );
            }
            else
            {
                digital_out_low ( &ctx->mosi );
            }
            digital_out_low ( &ctx->sck );
            Delay_10us ( );
            digital_out_high ( &ctx->sck );
            Delay_10us ( );
        }
        Delay_10us ( );
    }
}

static void spitoi2c_spi_read ( spitoi2c_t *ctx, uint8_t *data_out, uint8_t len )
{
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        data_out[ byte_cnt ] = 0;
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            digital_out_low ( &ctx->sck );
            Delay_10us ( );
            
            data_out[ byte_cnt ] |= ( ( !!digital_in_read ( &ctx->miso ) ) << ( 7 - bit_cnt ) );
            
            digital_out_high ( &ctx->sck );
            Delay_10us ( );
        }
        Delay_10us ( );
    }
}

// ------------------------------------------------------------------------- END
