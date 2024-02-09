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
 * @file silentstep4.c
 * @brief Silent Step 4 Click Driver.
 */

#include "silentstep4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY               0x00
#define SPI_WRITE_BIT       0x80

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void silentstep4_speed_delay ( uint8_t speed_macro );

void silentstep4_cfg_setup ( silentstep4_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SILENTSTEP4_DEVICE_ADDRESS_A1A0_11;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t silentstep4_init ( silentstep4_t *ctx, silentstep4_cfg_t *cfg ) 
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

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->step, cfg->step );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SILENTSTEP4_OK;
}

err_t silentstep4_default_cfg ( silentstep4_t *ctx ) 
{
    err_t error_flag = SILENTSTEP4_OK;
    silentstep4_reset_pca ( ctx );
    // Configure EN and SLEEP pins as OUTPUT, others as INPUT
    error_flag |= silentstep4_pca_write_reg ( ctx, SILENTSTEP4_PCA9538A_REG_CONFIG, 
                                              SILENTSTEP4_PCA9538A_DEFAULT_CONFIG );
    error_flag |= silentstep4_enable_device ( ctx );
    silentstep4_set_direction ( ctx, SILENTSTEP4_DIR_CW );
    error_flag |= silentstep4_set_sleep_pin ( ctx, SILENTSTEP4_PIN_STATE_HIGH );
    Delay_100ms ( );
    if ( ( SILENTSTEP4_OK != error_flag ) ||
         ( SILENTSTEP4_OK != silentstep4_check_com ( ctx ) ) )
    {
        return SILENTSTEP4_ERROR;
    }
    error_flag |= silentstep4_set_toff ( ctx, SILENTSTEP4_TOFF_DEFAULT );
    Delay_10ms ( );
    error_flag |= silentstep4_set_run_current ( ctx, SILENTSTEP4_IRUN_DEFAULT );
    Delay_10ms ( );
    error_flag |= silentstep4_set_step_res ( ctx, SILENTSTEP4_MRES_FULLSTEP );
    Delay_10ms ( );
    return error_flag;
}

err_t silentstep4_write_reg ( silentstep4_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = reg | SPI_WRITE_BIT;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t silentstep4_read_reg ( silentstep4_t *ctx, uint8_t reg, uint32_t *data_out )
{
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = reg & ( ~SPI_WRITE_BIT );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write  ( &ctx->spi, data_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read ( &ctx->spi, data_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = ( ( uint32_t ) data_buf[ 1 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    return error_flag;
}

err_t silentstep4_pca_write_reg ( silentstep4_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t silentstep4_pca_read_reg ( silentstep4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t silentstep4_check_com ( silentstep4_t *ctx )
{
    uint32_t reg_data = 0;
    if ( SILENTSTEP4_OK == silentstep4_read_reg ( ctx, SILENTSTEP4_REG_IOIN, &reg_data ) )
    {
        if ( SILENTSTEP4_IOIN_VERSION_DEFAULT == ( reg_data & SILENTSTEP4_IOIN_VERSION_MASK ) )
        {
            return SILENTSTEP4_OK;
        }
    }
    return SILENTSTEP4_ERROR;
}

err_t silentstep4_get_en_pin ( silentstep4_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP4_ERROR == silentstep4_pca_read_reg ( ctx, SILENTSTEP4_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    *state = reg_data & SILENTSTEP4_PIN_EN;
    return SILENTSTEP4_OK;
}

err_t silentstep4_set_en_pin ( silentstep4_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > SILENTSTEP4_PIN_STATE_HIGH )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( SILENTSTEP4_ERROR == silentstep4_pca_read_reg ( ctx, SILENTSTEP4_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( state == ( reg_data & SILENTSTEP4_PIN_EN ) )
    {
        return SILENTSTEP4_OK;
    }
    reg_data &= ~SILENTSTEP4_PIN_EN;
    reg_data |= state;
    return silentstep4_pca_write_reg ( ctx, SILENTSTEP4_PCA9538A_REG_OUTPUT, reg_data );
}

err_t silentstep4_get_sleep_pin ( silentstep4_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP4_ERROR == silentstep4_pca_read_reg ( ctx, SILENTSTEP4_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    *state = ( reg_data & SILENTSTEP4_PIN_SLEEP ) >> 1;
    return SILENTSTEP4_OK;
}

err_t silentstep4_set_sleep_pin ( silentstep4_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > SILENTSTEP4_PIN_STATE_HIGH )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( SILENTSTEP4_ERROR == silentstep4_pca_read_reg ( ctx, SILENTSTEP4_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( ( state << 1 ) == ( reg_data & SILENTSTEP4_PIN_SLEEP ) )
    {
        return SILENTSTEP4_OK;
    }
    reg_data &= ~SILENTSTEP4_PIN_SLEEP;
    reg_data |= ( state << 1 );
    return silentstep4_pca_write_reg ( ctx, SILENTSTEP4_PCA9538A_REG_OUTPUT, reg_data );
}

err_t silentstep4_get_diag0_pin ( silentstep4_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP4_ERROR == silentstep4_pca_read_reg ( ctx, SILENTSTEP4_PCA9538A_REG_INPUT, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    *state = ( reg_data & SILENTSTEP4_PIN_DIAG0 ) >> 2;
    return SILENTSTEP4_OK;
}

err_t silentstep4_get_diag1_pin ( silentstep4_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP4_ERROR == silentstep4_pca_read_reg ( ctx, SILENTSTEP4_PCA9538A_REG_INPUT, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    *state = ( reg_data & SILENTSTEP4_PIN_DIAG1 ) >> 3;
    return SILENTSTEP4_OK;
}

err_t silentstep4_get_ov_pin ( silentstep4_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP4_ERROR == silentstep4_pca_read_reg ( ctx, SILENTSTEP4_PCA9538A_REG_INPUT, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    *state = ( reg_data & SILENTSTEP4_PIN_OV ) >> 4;
    return SILENTSTEP4_OK;
}

err_t silentstep4_enable_device ( silentstep4_t *ctx )
{
    return silentstep4_set_en_pin ( ctx, SILENTSTEP4_PIN_STATE_LOW );
}

err_t silentstep4_disable_device ( silentstep4_t *ctx )
{
    return silentstep4_set_en_pin ( ctx, SILENTSTEP4_PIN_STATE_HIGH );
}

void silentstep4_set_direction ( silentstep4_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void silentstep4_switch_direction ( silentstep4_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void silentstep4_reset_pca ( silentstep4_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void silentstep4_set_rst_pin ( silentstep4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t silentstep4_get_int_pin ( silentstep4_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void silentstep4_set_step_pin ( silentstep4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

err_t silentstep4_set_toff ( silentstep4_t *ctx, uint8_t toff )
{
    uint32_t reg_data = 0;
    if ( toff > SILENTSTEP4_TOFF_MAX )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( SILENTSTEP4_ERROR == silentstep4_read_reg ( ctx, SILENTSTEP4_REG_CHOPCONF, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( ( ( uint32_t ) toff << SILENTSTEP4_TOFF_SHIFT ) == ( reg_data & SILENTSTEP4_TOFF_MASK ) )
    {
        return SILENTSTEP4_OK;
    }
    reg_data &= ~SILENTSTEP4_TOFF_MASK;
    reg_data |= ( ( uint32_t ) toff << SILENTSTEP4_TOFF_SHIFT );
    return silentstep4_write_reg ( ctx, SILENTSTEP4_REG_CHOPCONF, reg_data );
}

err_t silentstep4_set_step_res ( silentstep4_t *ctx, uint8_t mres )
{
    uint32_t reg_data = 0;
    if ( mres > SILENTSTEP4_MRES_FULLSTEP )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( SILENTSTEP4_ERROR == silentstep4_read_reg ( ctx, SILENTSTEP4_REG_CHOPCONF, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( ( ( uint32_t ) mres << SILENTSTEP4_MRES_SHIFT ) == ( reg_data & SILENTSTEP4_MRES_MASK ) )
    {
        return SILENTSTEP4_OK;
    }
    reg_data &= ~SILENTSTEP4_MRES_MASK;
    reg_data |= ( ( uint32_t ) mres << SILENTSTEP4_MRES_SHIFT );
    return silentstep4_write_reg ( ctx, SILENTSTEP4_REG_CHOPCONF, reg_data );
}

err_t silentstep4_set_run_current ( silentstep4_t *ctx, uint8_t irun )
{
    uint32_t reg_data = 0;
    if ( irun > SILENTSTEP4_IRUN_MAX )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( SILENTSTEP4_ERROR == silentstep4_read_reg ( ctx, SILENTSTEP4_REG_IHOLD_IRUN, &reg_data ) )
    {
        return SILENTSTEP4_ERROR;
    }
    if ( ( ( uint32_t ) irun << SILENTSTEP4_IRUN_SHIFT ) == ( reg_data & SILENTSTEP4_IRUN_MASK ) )
    {
        return SILENTSTEP4_OK;
    }
    reg_data &= ~SILENTSTEP4_IRUN_MASK;
    reg_data |= ( ( uint32_t ) irun << SILENTSTEP4_IRUN_SHIFT );
    return silentstep4_write_reg ( ctx, SILENTSTEP4_REG_IHOLD_IRUN, reg_data );
}

void silentstep4_drive_motor ( silentstep4_t *ctx, uint32_t steps, uint8_t speed )
{
    silentstep4_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        silentstep4_set_step_pin ( ctx, SILENTSTEP4_PIN_STATE_HIGH );
        silentstep4_speed_delay ( speed );
        silentstep4_set_step_pin ( ctx, SILENTSTEP4_PIN_STATE_LOW );
        silentstep4_speed_delay ( speed );
    }
    silentstep4_disable_device ( ctx );
}

static void silentstep4_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case SILENTSTEP4_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case SILENTSTEP4_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case SILENTSTEP4_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case SILENTSTEP4_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case SILENTSTEP4_SPEED_VERY_FAST:
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
