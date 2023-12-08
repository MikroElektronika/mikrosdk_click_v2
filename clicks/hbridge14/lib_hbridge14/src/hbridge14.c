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
 * @file hbridge14.c
 * @brief H-Bridge 14 Click Driver.
 */

#include "hbridge14.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x40

void hbridge14_cfg_setup ( hbridge14_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->in2  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->in1  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HBRIDGE14_DEVICE_ADDRESS_A1A0_00;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t hbridge14_init ( hbridge14_t *ctx, hbridge14_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->in1, cfg->in1 );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t hbridge14_default_cfg ( hbridge14_t *ctx ) 
{
    err_t error_flag = HBRIDGE14_OK;
    
    hbridge14_set_rst_pin( ctx, HBRIDGE14_PIN_STATE_HIGH );
    
    error_flag |= hbridge14_port_expander_write( ctx, HBRIDGE14_REG_CONFIG, HBRIDGE14_FLT_PIN );
    error_flag |= hbridge14_set_pins( ctx, HBRIDGE14_SLP_PIN, HBRIDGE14_DIS_PIN );
    error_flag |= hbridge14_disable_state( ctx, HBRIDGE14_DIS_OFF );
    error_flag |= hbridge14_sleep_state( ctx, HBRIDGE14_SLEEP_OFF );
    error_flag |= hbridge14_register_write ( ctx, HBRIDGE14_REG_IC3_CTRL, HBRIDGE14_CLR_FLT );

    return error_flag;
}

err_t hbridge14_generic_write ( hbridge14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t hbridge14_generic_read ( hbridge14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void hbridge14_set_in1_pin ( hbridge14_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE14_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->in1 );
    }
    else
    {
        digital_out_low( &ctx->in1 );
    }
}

void hbridge14_set_in2_pin ( hbridge14_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE14_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->in2 );
    }
    else
    {
        digital_out_low( &ctx->in2 );
    }
}

void hbridge14_set_rst_pin ( hbridge14_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE14_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

uint8_t hbridge14_get_int_pin ( hbridge14_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t hbridge14_register_write ( hbridge14_t *ctx, uint8_t reg, uint8_t data_in )
{
   return hbridge14_generic_write( ctx, reg, &data_in, 1 );
}

err_t hbridge14_register_read ( hbridge14_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t reg_val = reg | SPI_READ_MASK;
    
    return hbridge14_generic_read( ctx, reg_val, data_out, 1 );
}

err_t hbridge14_port_expander_write ( hbridge14_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t hbridge14_port_expander_read ( hbridge14_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t hbridge14_set_pins ( hbridge14_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in, data_out;
    err_t error_flag = hbridge14_port_expander_read( ctx, HBRIDGE14_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        error_flag |= hbridge14_port_expander_write( ctx, HBRIDGE14_REG_OUTPUT_PORT, data_in );
    }
    return error_flag;
}

err_t hbridge14_disable_state ( hbridge14_t *ctx, uint8_t dis_state )
{
    uint8_t set_mask = 0;
    uint8_t clr_mask = 0;
    
    if ( HBRIDGE14_DIS_ON == dis_state )
    {
        set_mask = HBRIDGE14_DIS_PIN;
    }
    else
    {
        clr_mask = HBRIDGE14_DIS_PIN;
    }
    
    return hbridge14_set_pins( ctx, set_mask, clr_mask );
}

err_t hbridge14_sleep_state ( hbridge14_t *ctx, uint8_t sleep_state )
{
    uint8_t set_mask = 0;
    uint8_t clr_mask = 0;
    
    if ( HBRIDGE14_SLEEP_ON == sleep_state )
    {
        clr_mask = HBRIDGE14_SLP_PIN;
    }
    else
    {
        set_mask = HBRIDGE14_SLP_PIN;
    }
    
    return hbridge14_set_pins( ctx, set_mask, clr_mask );
}

err_t hbridge14_drive_motor ( hbridge14_t *ctx, uint8_t state )
{
    err_t error_flag = HBRIDGE14_OK;
    
    switch ( state )
    {
        case ( HBRIDGE14_DRIVE_MOTOR_CW ):
        {
            hbridge14_disable_state( ctx, HBRIDGE14_DIS_ON );
            hbridge14_set_in1_pin( ctx, HBRIDGE14_PIN_STATE_LOW );
            hbridge14_set_in2_pin( ctx, HBRIDGE14_PIN_STATE_HIGH );
            hbridge14_disable_state( ctx, HBRIDGE14_DIS_OFF );
            break;
        }
        
        case ( HBRIDGE14_DRIVE_MOTOR_CCW ):
        {
            hbridge14_disable_state( ctx, HBRIDGE14_DIS_ON );
            hbridge14_set_in1_pin( ctx, HBRIDGE14_PIN_STATE_HIGH );
            hbridge14_set_in2_pin( ctx, HBRIDGE14_PIN_STATE_LOW );
            hbridge14_disable_state( ctx, HBRIDGE14_DIS_OFF );
            break;
        }
        
        case ( HBRIDGE14_DRIVE_MOTOR_BRAKE ):
        {
            hbridge14_disable_state( ctx, HBRIDGE14_DIS_ON );
            hbridge14_set_in1_pin( ctx, HBRIDGE14_PIN_STATE_HIGH );
            hbridge14_set_in2_pin( ctx, HBRIDGE14_PIN_STATE_HIGH );
            hbridge14_disable_state( ctx, HBRIDGE14_DIS_OFF );
            break;
        }
        
        case ( HBRIDGE14_DRIVE_MOTOR_COASTING ):
        {
            hbridge14_disable_state( ctx, HBRIDGE14_DIS_ON );
            hbridge14_set_in1_pin( ctx, HBRIDGE14_PIN_STATE_LOW );
            hbridge14_set_in2_pin( ctx, HBRIDGE14_PIN_STATE_LOW );
            hbridge14_disable_state( ctx, HBRIDGE14_DIS_OFF );
            break;
        }
        
        default:
        {
            error_flag = HBRIDGE14_ERROR;
            break;
        }
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------ END
