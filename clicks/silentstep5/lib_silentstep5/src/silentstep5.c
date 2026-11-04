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
 * @file silentstep5.c
 * @brief Silent Step 5 Click Driver.
 */

#include "silentstep5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_WRITE_BIT     0x80

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting the delay length.
 * @return Nothing.
 */
static void silentstep5_speed_delay ( uint8_t speed_macro );

void silentstep5_cfg_setup ( silentstep5_cfg_t *cfg ) 
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
    cfg->i2c_address = SILENTSTEP5_DEVICE_ADDRESS_A1A0_00;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t silentstep5_init ( silentstep5_t *ctx, silentstep5_cfg_t *cfg ) 
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

    return SILENTSTEP5_OK;
}

err_t silentstep5_default_cfg ( silentstep5_t *ctx ) 
{
    err_t error_flag = SILENTSTEP5_OK;

    // Configure port expander and gpio pins default state
    silentstep5_reset_exp ( ctx );
    error_flag |= silentstep5_write_exp_reg ( ctx, SILENTSTEP5_EXP_REG_CONFIG, 
                                              SILENTSTEP5_EXP_DEFAULT_CONFIG );
    error_flag |= silentstep5_disable_device ( ctx );
    silentstep5_set_direction ( ctx, SILENTSTEP5_DIR_CW );
    error_flag |= silentstep5_set_sleep_pin ( ctx, SILENTSTEP5_PIN_STATE_HIGH );
    Delay_100ms ( );

    // PLL Initialization
    error_flag |= silentstep5_write_reg ( ctx, SILENTSTEP5_REG_PLL, SILENTSTEP5_PLL_CLOCK_DIVIDER_16MHZ | 
                                                                    SILENTSTEP5_PLL_CLK_FSM_ENA | 
                                                                    SILENTSTEP5_PLL_CLK_SYS_SEL | 
                                                                    SILENTSTEP5_PLL_COMMIT );
    Delay_1ms( );
    error_flag |= silentstep5_write_reg ( ctx, SILENTSTEP5_REG_PLL, SILENTSTEP5_PLL_CLK_IS_STUCK | 
                                                                    SILENTSTEP5_PLL_CLK_LOSS |
                                                                    SILENTSTEP5_PLL_CLK_1M0_TMO |
                                                                    SILENTSTEP5_PLL_CLOCK_DIVIDER_16MHZ | 
                                                                    SILENTSTEP5_PLL_CLK_FSM_ENA | 
                                                                    SILENTSTEP5_PLL_CLK_SYS_SEL );
    Delay_10ms ( );

    // Clear status
    error_flag |= silentstep5_write_reg ( ctx, SILENTSTEP5_REG_GSTAT, SILENTSTEP5_GSTAT_CLEAR_ALL );
    Delay_10ms ( );

    // Enable STEP/DIR pin interface function
    error_flag |= silentstep5_enable_step_dir ( ctx );
    Delay_10ms ( );

    // Set TOFF, IRUN current, and step resolution
    error_flag |= silentstep5_set_toff ( ctx, SILENTSTEP5_TOFF_DEFAULT );
    Delay_10ms ( );
    error_flag |= silentstep5_set_run_current ( ctx, SILENTSTEP5_IRUN_DEFAULT );
    Delay_10ms ( );
    error_flag |= silentstep5_set_step_res ( ctx, SILENTSTEP5_MRES_FULLSTEP );
    Delay_10ms ( );
    return error_flag;
}

err_t silentstep5_write_reg ( silentstep5_t *ctx, uint8_t reg, uint32_t data_in )
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

err_t silentstep5_read_reg ( silentstep5_t *ctx, uint8_t reg, uint32_t *data_out )
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

err_t silentstep5_write_exp_reg ( silentstep5_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t silentstep5_read_exp_reg ( silentstep5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t silentstep5_get_sleep_pin ( silentstep5_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP5_ERROR == silentstep5_read_exp_reg ( ctx, SILENTSTEP5_EXP_REG_OUTPUT, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    *state = ( reg_data & SILENTSTEP5_EXP_PIN_SLEEP ) >> 1;
    return SILENTSTEP5_OK;
}

err_t silentstep5_set_sleep_pin ( silentstep5_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > SILENTSTEP5_PIN_STATE_HIGH )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( SILENTSTEP5_ERROR == silentstep5_read_exp_reg ( ctx, SILENTSTEP5_EXP_REG_OUTPUT, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( ( state << 1 ) == ( reg_data & SILENTSTEP5_EXP_PIN_SLEEP ) )
    {
        return SILENTSTEP5_OK;
    }
    reg_data &= ~SILENTSTEP5_EXP_PIN_SLEEP;
    reg_data |= ( state << 1 );
    return silentstep5_write_exp_reg ( ctx, SILENTSTEP5_EXP_REG_OUTPUT, reg_data );
}

err_t silentstep5_get_diag0_pin ( silentstep5_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP5_ERROR == silentstep5_read_exp_reg ( ctx, SILENTSTEP5_EXP_REG_INPUT, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    *state = ( reg_data & SILENTSTEP5_EXP_PIN_DIAG0 ) >> 3;
    return SILENTSTEP5_OK;
}

err_t silentstep5_get_diag1_pin ( silentstep5_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP5_ERROR == silentstep5_read_exp_reg ( ctx, SILENTSTEP5_EXP_REG_INPUT, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    *state = ( reg_data & SILENTSTEP5_EXP_PIN_DIAG1 ) >> 4;
    return SILENTSTEP5_OK;
}

err_t silentstep5_get_drv_en_pin ( silentstep5_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( SILENTSTEP5_ERROR == silentstep5_read_exp_reg ( ctx, SILENTSTEP5_EXP_REG_OUTPUT, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    *state = ( reg_data & SILENTSTEP5_EXP_PIN_DRV_EN ) >> 7;
    return SILENTSTEP5_OK;
}

err_t silentstep5_set_drv_en_pin ( silentstep5_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > SILENTSTEP5_PIN_STATE_HIGH )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( SILENTSTEP5_ERROR == silentstep5_read_exp_reg ( ctx, SILENTSTEP5_EXP_REG_OUTPUT, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( ( state << 7 ) == ( reg_data & SILENTSTEP5_EXP_PIN_DRV_EN ) )
    {
        return SILENTSTEP5_OK;
    }
    reg_data &= ~SILENTSTEP5_EXP_PIN_DRV_EN;
    reg_data |= ( state << 7 );
    return silentstep5_write_exp_reg ( ctx, SILENTSTEP5_EXP_REG_OUTPUT, reg_data );
}

err_t silentstep5_enable_device ( silentstep5_t *ctx )
{
    return silentstep5_set_drv_en_pin ( ctx, SILENTSTEP5_PIN_STATE_LOW );
}

err_t silentstep5_disable_device ( silentstep5_t *ctx )
{
    return silentstep5_set_drv_en_pin ( ctx, SILENTSTEP5_PIN_STATE_HIGH );
}

void silentstep5_set_direction ( silentstep5_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void silentstep5_switch_direction ( silentstep5_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void silentstep5_reset_exp ( silentstep5_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void silentstep5_set_rst_pin ( silentstep5_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t silentstep5_get_int_pin ( silentstep5_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void silentstep5_set_step_pin ( silentstep5_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

err_t silentstep5_set_toff ( silentstep5_t *ctx, uint8_t toff )
{
    uint32_t reg_data = 0;
    if ( toff > SILENTSTEP5_TOFF_MAX )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( SILENTSTEP5_ERROR == silentstep5_read_reg ( ctx, SILENTSTEP5_REG_CHOPCONF, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( ( ( uint32_t ) toff << SILENTSTEP5_TOFF_SHIFT ) == ( reg_data & SILENTSTEP5_TOFF_MASK ) )
    {
        return SILENTSTEP5_OK;
    }
    reg_data &= ~( SILENTSTEP5_TOFF_MASK );
    reg_data |= ( ( uint32_t ) toff << SILENTSTEP5_TOFF_SHIFT );
    return silentstep5_write_reg ( ctx, SILENTSTEP5_REG_CHOPCONF, reg_data );
}

err_t silentstep5_set_step_res ( silentstep5_t *ctx, uint8_t mres )
{
    uint32_t reg_data = 0;
    if ( mres > SILENTSTEP5_MRES_FULLSTEP )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( SILENTSTEP5_ERROR == silentstep5_read_reg ( ctx, SILENTSTEP5_REG_CHOPCONF, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( ( ( uint32_t ) mres << SILENTSTEP5_MRES_SHIFT ) == ( reg_data & SILENTSTEP5_MRES_MASK ) )
    {
        return SILENTSTEP5_OK;
    }
    reg_data &= ~( SILENTSTEP5_MRES_MASK );
    reg_data |= ( ( uint32_t ) mres << SILENTSTEP5_MRES_SHIFT );
    return silentstep5_write_reg ( ctx, SILENTSTEP5_REG_CHOPCONF, reg_data );
}

err_t silentstep5_set_run_current ( silentstep5_t *ctx, uint8_t irun )
{
    uint32_t reg_data = 0;
    if ( SILENTSTEP5_ERROR == silentstep5_read_reg ( ctx, SILENTSTEP5_REG_IHOLD_IRUN, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( ( ( uint32_t ) irun << SILENTSTEP5_IRUN_SHIFT ) == ( reg_data & SILENTSTEP5_IRUN_MASK ) )
    {
        return SILENTSTEP5_OK;
    }
    reg_data &= ~( SILENTSTEP5_IRUN_MASK );
    reg_data |= ( ( uint32_t ) irun << SILENTSTEP5_IRUN_SHIFT );
    return silentstep5_write_reg ( ctx, SILENTSTEP5_REG_IHOLD_IRUN, reg_data );
}

err_t silentstep5_enable_step_dir ( silentstep5_t *ctx )
{
    uint32_t reg_data = 0;
    if ( SILENTSTEP5_ERROR == silentstep5_read_reg ( ctx, SILENTSTEP5_REG_GCONF, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( SILENTSTEP5_GCONF_STEP_DIR_EXTERNAL == ( reg_data & SILENTSTEP5_GCONF_STEP_DIR_MASK ) )
    {
        return SILENTSTEP5_OK;
    }
    reg_data &= ~( SILENTSTEP5_GCONF_STEP_DIR_MASK );
    reg_data |= SILENTSTEP5_GCONF_STEP_DIR_EXTERNAL;
    return silentstep5_write_reg ( ctx, SILENTSTEP5_REG_GCONF, reg_data );
}

err_t silentstep5_disable_step_dir ( silentstep5_t *ctx )
{
    uint32_t reg_data = 0;
    if ( SILENTSTEP5_ERROR == silentstep5_read_reg ( ctx, SILENTSTEP5_REG_GCONF, &reg_data ) )
    {
        return SILENTSTEP5_ERROR;
    }
    if ( SILENTSTEP5_GCONF_STEP_DIR_INTERNAL == ( reg_data & SILENTSTEP5_GCONF_STEP_DIR_MASK ) )
    {
        return SILENTSTEP5_OK;
    }
    reg_data &= ~( SILENTSTEP5_GCONF_STEP_DIR_MASK );
    reg_data |= SILENTSTEP5_GCONF_STEP_DIR_INTERNAL;
    return silentstep5_write_reg ( ctx, SILENTSTEP5_REG_GCONF, reg_data );
}

void silentstep5_drive_motor ( silentstep5_t *ctx, uint32_t steps, uint8_t speed )
{
    silentstep5_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        silentstep5_set_step_pin ( ctx, SILENTSTEP5_PIN_STATE_HIGH );
        silentstep5_speed_delay ( speed );
        silentstep5_set_step_pin ( ctx, SILENTSTEP5_PIN_STATE_LOW );
        silentstep5_speed_delay ( speed );
    }
    silentstep5_disable_device ( ctx );
}

static void silentstep5_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case SILENTSTEP5_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case SILENTSTEP5_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case SILENTSTEP5_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case SILENTSTEP5_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case SILENTSTEP5_SPEED_VERY_FAST:
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
