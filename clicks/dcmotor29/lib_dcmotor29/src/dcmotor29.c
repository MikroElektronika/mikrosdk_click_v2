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
 * @file dcmotor29.c
 * @brief DC Motor 29 Click Driver.
 */

#include "dcmotor29.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dcmotor29_cfg_setup ( dcmotor29_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->ip   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DCMOTOR29_DEVICE_ADDRESS_A1A0_00;
}

err_t dcmotor29_init ( dcmotor29_t *ctx, dcmotor29_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->in1, cfg->in1 );

    digital_in_init( &ctx->ip, cfg->ip );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->in1 );

    return SPI_MASTER_SUCCESS;
}

err_t dcmotor29_default_cfg ( dcmotor29_t *ctx ) 
{
    err_t error_flag = DCMOTOR29_OK;
    
    dcmotor29_set_rst_pin( ctx, DCMOTOR29_PIN_STATE_HIGH );
    
    error_flag |= dcmotor29_port_expander_write( ctx, DCMOTOR29_REG_CONFIG, DCMOTOR29_FLT_PIN );
    error_flag |= dcmotor29_set_pins( ctx, DCMOTOR29_IN2_PIN, DCMOTOR29_NONE_PIN );
    error_flag |= dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_ON );
    error_flag |= dcmotor29_register_write( ctx, DCMOTOR29_REG_COMMAND, DCMOTOR29_CLR_FLT_CMD );
    error_flag |= dcmotor29_register_write( ctx, DCMOTOR29_REG_CONFIG3, DCMOTOR29_TOF_30_US | DCMOTOR29_S_MODE_INDEPENDENT );
    error_flag |= dcmotor29_register_write( ctx, DCMOTOR29_REG_COMMAND, DCMOTOR29_SPI_IN_UNLOCK_CMD );
    error_flag |= dcmotor29_register_write( ctx, DCMOTOR29_REG_SPI_IN, DCMOTOR29_S_EN_NONE );

    return error_flag;
}

err_t dcmotor29_generic_write ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dcmotor29_generic_read ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void dcmotor29_set_in1_pin ( dcmotor29_t *ctx, uint8_t pin_state )
{
    if ( DCMOTOR29_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->in1 );
    }
    else
    {
        digital_out_low( &ctx->in1 );
    }
}

void dcmotor29_set_rst_pin ( dcmotor29_t *ctx, uint8_t pin_state )
{
    if ( DCMOTOR29_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

uint8_t dcmotor29_get_ip_pin ( dcmotor29_t *ctx )
{
    return digital_in_read( &ctx->ip );
}

uint8_t dcmotor29_get_int_pin ( dcmotor29_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t dcmotor29_register_write ( dcmotor29_t *ctx, uint8_t reg, uint8_t data_in )
{
   return dcmotor29_generic_write( ctx, reg, &data_in, 1 );
}

err_t dcmotor29_register_read ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t reg_val = reg | DCMOTOR29_READ_REG_MASK;
    
    return dcmotor29_generic_read( ctx, reg_val, data_out, 1 );
}

err_t dcmotor29_port_expander_write ( dcmotor29_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t dcmotor29_port_expander_read ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t dcmotor29_set_pins ( dcmotor29_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in, data_out;
    err_t error_flag = dcmotor29_port_expander_read( ctx, DCMOTOR29_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        error_flag |= dcmotor29_port_expander_write( ctx, DCMOTOR29_REG_OUTPUT_PORT, data_in );
    }
    return error_flag;
}

err_t dcmotor29_drvoff_state ( dcmotor29_t *ctx, uint8_t drvoff_state )
{
    uint8_t set_mask = 0;
    uint8_t clr_mask = 0;
    
    if ( DCMOTOR29_DRVOFF_ON == drvoff_state )
    {
        set_mask = DCMOTOR29_DOF_PIN;
    }
    else
    {
        clr_mask = DCMOTOR29_DOF_PIN;
    }
    
    return dcmotor29_set_pins( ctx, set_mask, clr_mask );
}

err_t dcmotor29_drive_motor ( dcmotor29_t *ctx, uint8_t state )
{
    err_t error_flag = DCMOTOR29_OK;
    
    switch ( state )
    {
        case ( DCMOTOR29_DRIVE_MOTOR_CW ):
        {
            dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_ON );
            dcmotor29_set_in1_pin( ctx, DCMOTOR29_PIN_STATE_LOW );
            error_flag |= dcmotor29_set_pins( ctx, DCMOTOR29_IN2_PIN, DCMOTOR29_NONE_PIN );
            dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_OFF );
            break;
        }
        
        case ( DCMOTOR29_DRIVE_MOTOR_CCW ):
        {
            dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_ON );
            dcmotor29_set_in1_pin( ctx, DCMOTOR29_PIN_STATE_HIGH );
            error_flag |= dcmotor29_set_pins( ctx, DCMOTOR29_NONE_PIN, DCMOTOR29_IN2_PIN );
            dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_OFF );
            break;
        }
        
        case ( DCMOTOR29_DRIVE_MOTOR_BRAKE ):
        {
            dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_ON );
            dcmotor29_set_in1_pin( ctx, DCMOTOR29_PIN_STATE_HIGH );
            error_flag |= dcmotor29_set_pins( ctx, DCMOTOR29_IN2_PIN, DCMOTOR29_NONE_PIN );
            dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_OFF );
            break;
        }
        
        case ( DCMOTOR29_DRIVE_MOTOR_COASTING ):
        {
            dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_ON );
            dcmotor29_set_in1_pin( ctx, DCMOTOR29_PIN_STATE_LOW );
            error_flag |= dcmotor29_set_pins( ctx, DCMOTOR29_NONE_PIN, DCMOTOR29_IN2_PIN );
            dcmotor29_drvoff_state( ctx, DCMOTOR29_DRVOFF_OFF );
            break;
        }
        
        default:
        {
            error_flag = DCMOTOR29_ERROR;
            break;
        }
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
