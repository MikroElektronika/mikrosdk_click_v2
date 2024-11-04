/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file pressure.c
 *
 */

#include "pressure.h"


// ------------------------------------------------------------- PRIVATE MACROS

#define PRESSURE_DUMMY  0

//  Pressure Click slave address.
#define PRESSURE_I2C_ADDR_0  0x5C
#define PRESSURE_I2C_ADDR_1  0x5D

//  Pressure Click commands.
#define PRESSURE_SPI_READ_CMD  0x80
#define PRESSURE_SPI_AUTO_INC  0x40
#define PRESSURE_I2C_AUTO_INC  0x80

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief I2C Master Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 * @param n_data  Number of bytes to be written.
 *
 * @description This function writes the desired number of data bytes starting
 * from the selected register by using I2C driver.
 * @note I2C START and STOP sequences are included in this function.
 */
static void
pressure_i2c_master_write( pressure_t *ctx, uint8_t reg_addr,
                           uint8_t *data_in, uint8_t n_data );

/**
 * @brief I2C Master Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_out  Output data.
 * @param n_data  Number of bytes to be read.
 *
 * @description This function reads the desired number of data bytes starting
 * from the selected register by using I2C driver.
 * @note I2C START and STOP sequences are included in this function.
 */
static void
pressure_i2c_master_read( pressure_t *ctx, uint8_t reg_addr,
                          uint8_t *data_out, uint8_t n_data );

/**
 * @brief SPI Master Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 * @param n_data  Number of bytes to be written.
 *
 * @description This function writes the desired number of data bytes starting
 * from the selected register by using SPI driver.
 * @note Chip Select control is included in this function.
 */
static void
pressure_spi_master_write( pressure_t *ctx, uint8_t reg_addr,
                           uint8_t *data_in, uint8_t n_data );

/**
 * @brief SPI Master Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_out  Output data.
 * @param n_data  Number of bytes to be read.
 *
 * @description This function reads the desired number of data bytes starting
 * from the selected register by using SPI driver.
 * @note Chip Select control is included in this function.
 */
static void
pressure_spi_master_read( pressure_t *ctx, uint8_t reg_addr,
                          uint8_t *data_out, uint8_t n_data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
pressure_cfg_setup( pressure_cfg_t *cfg )
{
    cfg->cs      = HAL_PIN_NC;
    cfg->sck     = HAL_PIN_NC;
    cfg->sdo     = HAL_PIN_NC;
    cfg->sdi     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
    cfg->scl     = HAL_PIN_NC;
    cfg->sda     = HAL_PIN_NC;

    cfg->i2c_addr  = true;
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;

    cfg->spi_speed = 100000;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_mode  = SPI_MASTER_MODE_0;

    cfg->drv_sel   = PRESSURE_DRV_SEL_I2C;
}

pressure_err_t
pressure_init( pressure_t *ctx, pressure_cfg_t *cfg )
{

    if ( cfg->drv_sel == PRESSURE_DRV_SEL_I2C )
    {
        i2c_master_config_t i2c_cfg;

        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed   = cfg->i2c_speed;
        i2c_cfg.scl     = cfg->scl;
        i2c_cfg.sda     = cfg->sda;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return PRESSURE_ERR_INIT_DRV;
        }

        if ( cfg->i2c_addr )
        {
            ctx->slave_addr = PRESSURE_I2C_ADDR_1;
        }
        else
        {
            ctx->slave_addr = PRESSURE_I2C_ADDR_0;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_addr );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->write = pressure_i2c_master_write;
        ctx->read  = pressure_i2c_master_read;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->sdo;
        spi_cfg.mosi   = cfg->sdi;
        spi_cfg.default_write_data = PRESSURE_DUMMY;

        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return PRESSURE_ERR_INIT_DRV;
        }

        spi_master_set_default_write_data( &ctx->spi, PRESSURE_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->write = pressure_spi_master_write;
        ctx->read  = pressure_spi_master_read;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PRESSURE_OK;
}

void
pressure_default_cfg( pressure_t *ctx )
{
    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG1,
                                   PRESSURE_SET_PWR_UP_DEV |
                                   (PRESSURE_ODR_P25HZ_T25HZ << 4) |
                                   PRESSURE_SET_BLOCK_DATA_UPDATE |
                                   PRESSURE_SET_PWR_UP_INT );
    pressure_generic_single_write( ctx, PRESSURE_REG_RES_CFG,
                                   (PRESSURE_SET_RES_AVG_128 << 4) |
                                   PRESSURE_SET_RES_AVG_256 );
    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG3,
                                   PRESSURE_SET_INT_DATA_RDY );
}

pressure_err_t
pressure_generic_single_write( pressure_t *ctx, uint8_t reg_addr,
                               uint8_t data_in )
{
    uint8_t data_;

    if (( reg_addr < 0x8 ) ||
        (( reg_addr > 0xA ) && ( reg_addr < 0xF )) ||
        (( reg_addr > 0x10 ) && ( reg_addr < 0x20 )) ||
        (( reg_addr > 0x2C ) && ( reg_addr != 0x30 )))
    {
        return PRESSURE_ERR_ADDR;
    }

    data_ = data_in;

    ctx->write( ctx, reg_addr, &data_, PRESSURE_DATA_NUMBER_MIN );

    return PRESSURE_OK;
}

pressure_err_t
pressure_generic_multiple_write( pressure_t *ctx, uint8_t reg_addr,
                                 uint8_t *data_in, uint8_t n_data )
{
    if (( reg_addr < 0x8 ) ||
        (( reg_addr > 0xA ) && ( reg_addr < 0xF )) ||
        (( reg_addr > 0x10 ) && ( reg_addr < 0x20 )) ||
        (( reg_addr > 0x2C ) && ( reg_addr != 0x30 )))
    {
        return PRESSURE_ERR_ADDR;
    }

    if (( n_data < PRESSURE_DATA_NUMBER_MIN ) ||
        ( n_data > PRESSURE_DATA_NUMBER_MAX ))
    {
        return PRESSURE_ERR_NDATA;
    }

    ctx->write( ctx, reg_addr, data_in, n_data );

    return PRESSURE_OK;
}

pressure_err_t
pressure_generic_multiple_read( pressure_t *ctx, uint8_t reg_addr,
                                uint8_t *data_out, uint8_t n_data )
{
    if (( reg_addr < 0x8 ) ||
        (( reg_addr > 0xA ) && ( reg_addr < 0xF )) ||
        (( reg_addr > 0x10 ) && ( reg_addr < 0x20 )) ||
        (( reg_addr > 0x2C ) && ( reg_addr != 0x30 )))
    {
        return PRESSURE_ERR_ADDR;
    }

    if (( n_data < PRESSURE_DATA_NUMBER_MIN ) ||
        ( n_data > PRESSURE_DATA_NUMBER_MAX ))
    {
        return PRESSURE_ERR_NDATA;
    }

    ctx->read( ctx, reg_addr, data_out, n_data );

    return PRESSURE_OK;
}

uint8_t
pressure_read_id( pressure_t *ctx )
{
    uint8_t read_data;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_DEVICE_ID, &read_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    return read_data;
}

void
pressure_set_odr( pressure_t *ctx, pressure_odr_t odr )
{
    uint8_t tmp_data;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG1, &tmp_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    tmp_data &= 0x8F;
    tmp_data |= odr << 4;

    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG1, tmp_data );
}

void
pressure_pwr_ctrl( pressure_t *ctx, pressure_pwr_ctrl_t state )
{
    uint8_t tmp_data;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG1, &tmp_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    tmp_data &= 0x7F;
    tmp_data |= state << 7;

    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG1, tmp_data );
}

void
pressure_pwr_ctrl_interrupt( pressure_t *ctx, pressure_pwr_ctrl_t state )
{
    uint8_t tmp_data;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG1, &tmp_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    tmp_data &= 0xF7;
    tmp_data |= state << 3;

    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG1, tmp_data );
}

void
pressure_block_data_update( pressure_t *ctx, pressure_pwr_ctrl_t state )
{
    uint8_t tmp_data;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG1, &tmp_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    tmp_data &= 0xFB;
    tmp_data |= state << 2;

    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG1, tmp_data );
}

void
pressure_pwr_ctrl_delta_pressure( pressure_t *ctx, pressure_pwr_ctrl_t state )
{
    uint8_t tmp_data;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG1, &tmp_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    tmp_data &= 0xFD;
    tmp_data |= state << 1;

    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG1, tmp_data );
}

void
pressure_reboot_memory( pressure_t *ctx )
{
    uint8_t tmp_data;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG2, &tmp_data,
                                    PRESSURE_DATA_NUMBER_MIN );
    tmp_data |= PRESSURE_SET_REBOOT_MEM_CONTENT;
    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG2, tmp_data );
    Delay_1sec();

    pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG2, &tmp_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    while (tmp_data & PRESSURE_SET_REBOOT_MEM_CONTENT)
    {
        pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG2, &tmp_data,
                                        PRESSURE_DATA_NUMBER_MIN );
    }
}

void
pressure_sw_reset( pressure_t *ctx )
{
    uint8_t tmp_data;

    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG2,
                                   PRESSURE_SET_SW_RESET );
    Delay_100ms();
    Delay_100ms();
    pressure_generic_single_write( ctx, PRESSURE_REG_CTRL_REG2,
                                   PRESSURE_SET_REBOOT_MEM_CONTENT );
    Delay_1sec();

    pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG2, &tmp_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    while (tmp_data & PRESSURE_SET_REBOOT_MEM_CONTENT)
    {
        pressure_generic_multiple_read( ctx, PRESSURE_REG_CTRL_REG2, &tmp_data,
                                        PRESSURE_DATA_NUMBER_MIN );
    }
}

float
pressure_get_pressure( pressure_t *ctx )
{
    uint8_t read_data[ 3 ];
    int32_t tmp_data;
    float press;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_PRESS_OUT_XLB, read_data,
                                    3 );

    tmp_data = read_data[ 2 ];
    tmp_data <<= 8;
    tmp_data |= read_data[ 1 ];
    tmp_data <<= 8;
    tmp_data |= read_data[ 0 ];

    if (tmp_data & 0x800000)
    {
        tmp_data |= 0xFF000000;
    }

    press = tmp_data;
    press /= 4096;

    return press;
}

float
pressure_get_temperature( pressure_t *ctx )
{
    uint8_t read_data[ 2 ];
    int16_t tmp_data;
    float temp;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_TEMP_OUT_LSB, read_data,
                                    2 );

    tmp_data = read_data[ 1 ];
    tmp_data <<= 8;
    tmp_data |= read_data[ 0 ];

    temp = tmp_data;
    temp /= 480;
    temp += 42.5;

    return temp;
}

uint8_t
pressure_get_status( pressure_t *ctx, uint8_t bit_mask )
{
    uint8_t read_data;

    pressure_generic_multiple_read( ctx, PRESSURE_REG_STATUS, &read_data,
                                    PRESSURE_DATA_NUMBER_MIN );

    read_data &= bit_mask;

    return read_data;
}

uint8_t
pressure_get_int_pin( pressure_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void
pressure_i2c_master_write( pressure_t *ctx, uint8_t reg_addr, uint8_t *data_in,
                           uint8_t n_data )
{
    uint8_t tx_data[ 50 ];
    uint8_t cnt;

    tx_data[ 0 ] = reg_addr | PRESSURE_I2C_AUTO_INC;

    for ( cnt = 1; cnt <= n_data; cnt++ )
    {
        tx_data[ cnt ] = *data_in;
        data_in++;
    }

    i2c_master_write( &ctx->i2c, tx_data, n_data + 1 );
}

static void
pressure_i2c_master_read( pressure_t *ctx, uint8_t reg_addr, uint8_t *data_out,
                          uint8_t n_data )
{
    uint8_t tx_data;

    tx_data = reg_addr | PRESSURE_I2C_AUTO_INC;

    i2c_master_write_then_read( &ctx->i2c, &tx_data, 1, data_out, n_data );
}

static void
pressure_spi_master_write( pressure_t *ctx, uint8_t reg_addr, uint8_t *data_in,
                           uint8_t n_data )
{
    uint8_t tx_data[ 50 ];
    uint8_t cnt;

    tx_data[ 0 ] = reg_addr | PRESSURE_SPI_AUTO_INC;

    for ( cnt = 1; cnt <= n_data; cnt++ )
    {
        tx_data[ cnt ] = *data_in;
        data_in++;
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_data, n_data + 1 );
    spi_master_deselect_device( ctx->chip_select );    
}

static void
pressure_spi_master_read( pressure_t *ctx, uint8_t reg_addr, uint8_t *data_out,
                          uint8_t n_data )
{
    uint8_t tx_data;
    uint8_t rx_data[ 50 ];
    uint8_t cnt;

    tx_data = reg_addr | PRESSURE_SPI_READ_CMD | PRESSURE_SPI_AUTO_INC;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &tx_data, 1, rx_data, n_data );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < n_data; cnt++ )
    {
        *data_out = rx_data[ cnt ];
        data_out++;
    }
}

// ------------------------------------------------------------------------ END
