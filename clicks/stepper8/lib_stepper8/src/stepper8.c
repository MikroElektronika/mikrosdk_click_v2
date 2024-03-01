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
 * @file stepper8.c
 * @brief Stepper 8 Click Driver.
 */

#include "stepper8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper8_speed_delay ( uint8_t speed_macro );

void stepper8_cfg_setup ( stepper8_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->md1  = HAL_PIN_NC;
    cfg->md3  = HAL_PIN_NC;
    cfg->md0  = HAL_PIN_NC;
    cfg->md2  = HAL_PIN_NC;
    cfg->err  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER8_DEVICE_ADDRESS_A1A0_00;

    cfg->spi_speed   = 5000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
}

err_t stepper8_init ( stepper8_t *ctx, stepper8_cfg_t *cfg ) 
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

    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

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

    digital_out_init( &ctx->md0, cfg->md0 );
    digital_out_init( &ctx->md1, cfg->md1 );
    digital_out_init( &ctx->md2, cfg->md2 );
    digital_out_init( &ctx->md3, cfg->md3 );

    digital_in_init( &ctx->err, cfg->err );

    digital_out_low ( &ctx->md0 );
    digital_out_low ( &ctx->md1 );
    digital_out_low ( &ctx->md2 );
    digital_out_low ( &ctx->md3 );

    return STEPPER8_OK;
}

err_t stepper8_default_cfg ( stepper8_t *ctx ) 
{
    err_t error_flag = STEPPER8_OK;
    error_flag |= stepper8_pca_write_reg ( ctx, STEPPER8_PCA9538A_REG_CONFIG, 
                                                STEPPER8_PCA9538A_DEFAULT_CONFIG );
    stepper8_set_direction ( ctx, STEPPER8_DIR_CW );
    error_flag |= stepper8_select_gpio ( ctx );
    error_flag |= stepper8_disable_standby ( ctx );
    error_flag |= stepper8_disable_device ( ctx );
    error_flag |= stepper8_set_step_mode ( ctx, STEPPER8_MODE_FULL_STEP );
    Delay_100ms ( );
    return error_flag;
}

err_t stepper8_write_spi ( stepper8_t *ctx, uint32_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    digital_out_low ( &ctx->md1 );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    digital_out_high ( &ctx->md1 );
    return error_flag;
}

err_t stepper8_pca_write_reg ( stepper8_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper8_pca_read_reg ( stepper8_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t stepper8_enable_standby ( stepper8_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER8_ERROR == stepper8_pca_read_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER8_ERROR;
    }
    if ( STEPPER8_PIN_STBY != ( reg_data & STEPPER8_PIN_STBY ) )
    {
        return STEPPER8_OK;
    }
    reg_data &= ~STEPPER8_PIN_STBY;
    return stepper8_pca_write_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper8_disable_standby ( stepper8_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER8_ERROR == stepper8_pca_read_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER8_ERROR;
    }
    if ( STEPPER8_PIN_STBY == ( reg_data & STEPPER8_PIN_STBY ) )
    {
        return STEPPER8_OK;
    }
    reg_data |= STEPPER8_PIN_STBY;
    return stepper8_pca_write_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper8_select_gpio ( stepper8_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER8_ERROR == stepper8_pca_read_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER8_ERROR;
    }
    if ( STEPPER8_PIN_SELECT != ( reg_data & STEPPER8_PIN_SELECT ) )
    {
        return STEPPER8_OK;
    }
    reg_data &= ~STEPPER8_PIN_SELECT;
    return stepper8_pca_write_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper8_select_spi ( stepper8_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER8_ERROR == stepper8_pca_read_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER8_ERROR;
    }
    if ( STEPPER8_PIN_SELECT == ( reg_data & STEPPER8_PIN_SELECT ) )
    {
        return STEPPER8_OK;
    }
    reg_data |= STEPPER8_PIN_SELECT;
    return stepper8_pca_write_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper8_disable_device ( stepper8_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER8_ERROR == stepper8_pca_read_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER8_ERROR;
    }
    if ( STEPPER8_PIN_EN != ( reg_data & STEPPER8_PIN_EN ) )
    {
        return STEPPER8_OK;
    }
    reg_data &= ~STEPPER8_PIN_EN;
    return stepper8_pca_write_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper8_enable_device ( stepper8_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER8_ERROR == stepper8_pca_read_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER8_ERROR;
    }
    if ( STEPPER8_PIN_EN == ( reg_data & STEPPER8_PIN_EN ) )
    {
        return STEPPER8_OK;
    }
    reg_data |= STEPPER8_PIN_EN;
    return stepper8_pca_write_reg ( ctx, STEPPER8_PCA9538A_REG_OUTPUT, reg_data );
}

void stepper8_set_md0_pin ( stepper8_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->md0, state );
}

void stepper8_set_md1_pin ( stepper8_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->md1, state );
}

void stepper8_set_md2_pin ( stepper8_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->md2, state );
}

void stepper8_set_md3_pin ( stepper8_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->md3, state );
}

uint8_t stepper8_get_err_pin ( stepper8_t *ctx )
{
    return digital_in_read ( &ctx->err );
}

void stepper8_set_direction ( stepper8_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->md3, dir );
    ctx->dir = dir;
}

void stepper8_switch_direction ( stepper8_t *ctx )
{
    digital_out_toggle ( &ctx->md3 );
    ctx->dir = !ctx->dir;
}

void stepper8_set_step_pin ( stepper8_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->md2, state );
}

err_t stepper8_set_step_mode ( stepper8_t *ctx, uint8_t mode )
{
    err_t error_flag = STEPPER8_OK;
    error_flag |= stepper8_enable_standby ( ctx );
    error_flag |= stepper8_disable_device ( ctx );
    digital_out_high ( &ctx->md3 );
    switch ( mode )
    {
        case STEPPER8_MODE_FULL_STEP:
        {
            digital_out_low ( &ctx->md2 );
            digital_out_low ( &ctx->md1 );
            digital_out_low ( &ctx->md0 );
            break;
        }
        case STEPPER8_MODE_HALF_STEP:
        {
            digital_out_low ( &ctx->md2 );
            digital_out_low ( &ctx->md1 );
            digital_out_high ( &ctx->md0 );
            break;
        }
        case STEPPER8_MODE_QUARTER_STEP:
        {
            digital_out_low ( &ctx->md2 );
            digital_out_high ( &ctx->md1 );
            digital_out_low ( &ctx->md0 );
            break;
        }
        case STEPPER8_MODE_1_OVER_8:
        {
            digital_out_low ( &ctx->md2 );
            digital_out_high ( &ctx->md1 );
            digital_out_high ( &ctx->md0 );
            break;
        }
        case STEPPER8_MODE_1_OVER_16:
        {
            digital_out_high ( &ctx->md2 );
            digital_out_low ( &ctx->md1 );
            digital_out_low ( &ctx->md0 );
            break;
        }
        case STEPPER8_MODE_1_OVER_32:
        {
            digital_out_high ( &ctx->md2 );
            digital_out_low ( &ctx->md1 );
            digital_out_high ( &ctx->md0 );
            break;
        }
        case STEPPER8_MODE_1_OVER_64:
        {
            digital_out_high ( &ctx->md2 );
            digital_out_high ( &ctx->md1 );
            digital_out_low ( &ctx->md0 );
            break;
        }
        case STEPPER8_MODE_1_OVER_128:
        {
            digital_out_high ( &ctx->md2 );
            digital_out_high ( &ctx->md1 );
            digital_out_high ( &ctx->md0 );
            break;
        }
        default:
        {
            digital_out_low ( &ctx->md2 );
            digital_out_low ( &ctx->md1 );
            digital_out_low ( &ctx->md0 );
            error_flag = STEPPER8_ERROR;
            break;
        }
    }
    Delay_1ms ( );
    error_flag |= stepper8_disable_standby ( ctx );
    error_flag |= stepper8_enable_device ( ctx );
    stepper8_set_direction ( ctx, ctx->dir );
    return error_flag;
}

err_t stepper8_drive_motor ( stepper8_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = STEPPER8_OK;
    error_flag |= stepper8_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper8_set_step_pin ( ctx, STEPPER8_PIN_STATE_HIGH );
        stepper8_speed_delay ( speed );
        stepper8_set_step_pin ( ctx, STEPPER8_PIN_STATE_LOW );
        stepper8_speed_delay ( speed );
    }
    error_flag |= stepper8_disable_device ( ctx );
    return error_flag;
}

static void stepper8_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER8_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER8_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER8_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER8_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER8_SPEED_VERY_FAST:
        {
            Delay_1ms( );
            break;
        }
        default:
        {
            Delay_5ms( );
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
