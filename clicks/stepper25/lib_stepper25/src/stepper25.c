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
 * @file stepper25.c
 * @brief Stepper 25 Click Driver.
 */

#include "stepper25.h"

/**
 * @brief Dummy and spi read bit macros.
 * @details Definition of dummy and spi read bit macros.
 */
#define DUMMY                       0x00
#define STEPPER25_SPI_READ_BIT      0x40

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return None.
 */
static void stepper25_speed_delay ( stepper25_t *ctx, uint8_t speed_macro );

void stepper25_cfg_setup ( stepper25_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dir   = HAL_PIN_NC;
    cfg->sleep = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t stepper25_init ( stepper25_t *ctx, stepper25_cfg_t *cfg ) 
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

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->sleep, cfg->sleep );
    digital_out_init( &ctx->step, cfg->step );

    digital_in_init( &ctx->fault, cfg->fault );

    return SPI_MASTER_SUCCESS;
}

err_t stepper25_default_cfg ( stepper25_t *ctx ) 
{
    err_t error_flag = STEPPER25_OK;

    STEPPER25_SET_DATA_SAMPLE_EDGE;
    
    stepper25_enable_device ( ctx );
    Delay_100ms ( );
    
    stepper25_set_direction ( ctx, STEPPER25_DIR_CW );

    // Limit the run current to 25 percents. 
    error_flag |= stepper25_write_reg ( ctx, STEPPER25_REG_CTRL11, STEPPER25_CTRL11_TRQ_DAC_25_PCT );
        
    error_flag |= stepper25_set_step_mode ( ctx, STEPPER25_STEP_MODE_HALF );

    error_flag |= stepper25_clear_fault ( ctx );

    return error_flag;
}

err_t stepper25_write_reg ( stepper25_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = STEPPER25_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( reg > STEPPER25_REG_SS_CTRL5 ) && ( STEPPER25_REG_CTRL14 != reg ) )
    {
        return STEPPER25_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, reg );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, data_in );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( STEPPER25_OK == error_flag )
    {
        ctx->status = ( data_buf[ 0 ] & 0x3F );
    }
    return error_flag;
}

err_t stepper25_read_reg ( stepper25_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = STEPPER25_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( reg > STEPPER25_REG_SS_CTRL5 ) && ( STEPPER25_REG_CTRL14 != reg ) )
    {
        return STEPPER25_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, reg | STEPPER25_SPI_READ_BIT );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( STEPPER25_OK == error_flag )
    {
        ctx->status = ( data_buf[ 0 ] & 0x3F );
        if ( NULL != data_out )
        {
            *data_out = data_buf[ 1 ];
        }
    }
    return error_flag;
}

void stepper25_enable_device ( stepper25_t *ctx )
{
    digital_out_high ( &ctx->sleep );
}

void stepper25_disable_device ( stepper25_t *ctx )
{
    digital_out_low ( &ctx->sleep );
}

void stepper25_set_direction ( stepper25_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper25_switch_direction ( stepper25_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

uint8_t stepper25_get_fault_pin ( stepper25_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

void stepper25_set_step_pin ( stepper25_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

err_t stepper25_clear_fault ( stepper25_t *ctx )
{
    err_t error_flag = STEPPER25_OK;
    uint8_t reg_data = 0;
    error_flag |= stepper25_read_reg ( ctx, STEPPER25_REG_CTRL3, &reg_data );
    reg_data &= ( ~STEPPER25_CTRL3_CLR_FLT_MASK );
    reg_data |= STEPPER25_CTRL3_CLR_FLT_HIGH;
    error_flag |= stepper25_write_reg ( ctx, STEPPER25_REG_CTRL3, reg_data );
    return error_flag;
}

err_t stepper25_enable_output ( stepper25_t *ctx )
{
    err_t error_flag = STEPPER25_OK;
    uint8_t reg_data = 0;
    error_flag |= stepper25_read_reg ( ctx, STEPPER25_REG_CTRL1, &reg_data );
    reg_data &= ( ~STEPPER25_CTRL1_EN_OUT_MASK );
    reg_data |= STEPPER25_CTRL1_EN_OUT_ENABLED;
    error_flag |= stepper25_write_reg ( ctx, STEPPER25_REG_CTRL1, reg_data );
    return error_flag;
}

err_t stepper25_disable_output ( stepper25_t *ctx )
{
    err_t error_flag = STEPPER25_OK;
    uint8_t reg_data = 0;
    error_flag |= stepper25_read_reg ( ctx, STEPPER25_REG_CTRL1, &reg_data );
    reg_data &= ( ~STEPPER25_CTRL1_EN_OUT_MASK );
    reg_data |= STEPPER25_CTRL1_EN_OUT_DISABLED;
    error_flag |= stepper25_write_reg ( ctx, STEPPER25_REG_CTRL1, reg_data );
    return error_flag;
}

err_t stepper25_set_step_mode ( stepper25_t *ctx, uint8_t step_mode )
{
    err_t error_flag = STEPPER25_OK;
    uint8_t reg_data = 0;
    if ( step_mode > STEPPER25_STEP_MODE_1_OVER_256 )
    {
        return STEPPER25_ERROR;
    }
    error_flag |= stepper25_read_reg ( ctx, STEPPER25_REG_CTRL2, &reg_data );
    reg_data &= ( ~STEPPER25_CTRL2_MICROSTEP_MODE_MASK );
    reg_data |= step_mode;
    error_flag |= stepper25_write_reg ( ctx, STEPPER25_REG_CTRL2, reg_data );
    if ( STEPPER25_OK == error_flag )
    {
        ctx->step_mode = step_mode;
    }
    return error_flag;
}

err_t stepper25_drive_motor ( stepper25_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = STEPPER25_OK;
    error_flag |= stepper25_enable_output ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper25_set_step_pin ( ctx, STEPPER25_PIN_HIGH_LEVEL );
        stepper25_speed_delay ( ctx, speed );
        stepper25_set_step_pin ( ctx, STEPPER25_PIN_LOW_LEVEL );
        stepper25_speed_delay ( ctx, speed );
    }
    error_flag |= stepper25_disable_output ( ctx );
    return error_flag;
}

static void stepper25_speed_delay ( stepper25_t *ctx, uint8_t speed_macro )
{
    uint32_t num_delay_10us = 5000;
    uint16_t step_divider = 1;
    if ( ctx->step_mode <= STEPPER25_STEP_MODE_FULL_71 )
    {
        step_divider = 1;
    }
    else if ( ctx->step_mode <= STEPPER25_STEP_MODE_HALF )
    {
        step_divider = 2;
    }
    else
    {
        step_divider = 4 << ( ctx->step_mode - STEPPER25_STEP_MODE_QUARTER );
    }
    num_delay_10us /= step_divider;
    num_delay_10us /= ( 1 << speed_macro );
    while ( num_delay_10us-- )
    {
        Delay_10us ( );
    }
}

// ------------------------------------------------------------------------- END
