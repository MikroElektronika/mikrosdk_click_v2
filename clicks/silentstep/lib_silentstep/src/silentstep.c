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
 * @file silentstep.c
 * @brief Silent Step Click Driver.
 */

#include "silentstep.h"

/**
 * @brief Dummy and SPI write bit data.
 * @details Definition of dummy and SPI write bit data.
 */
#define DUMMY                       0x00
#define SILENTSTEP_SPI_WRITE_BIT    0x80

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void silentstep_speed_delay ( uint8_t speed_macro );

void silentstep_cfg_setup ( silentstep_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->spm  = HAL_PIN_NC;
    cfg->sdm  = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t silentstep_init ( silentstep_t *ctx, silentstep_cfg_t *cfg ) 
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

    digital_out_init( &ctx->spm, cfg->spm );
    digital_out_init( &ctx->sdm, cfg->sdm );
    digital_out_init( &ctx->step, cfg->step );
    digital_out_init( &ctx->dir, cfg->dir );

    return SPI_MASTER_SUCCESS;
}

err_t silentstep_default_cfg ( silentstep_t *ctx ) 
{
    err_t error_flag = SILENTSTEP_OK;
    silentstep_set_sdm_pin ( ctx, SILENTSTEP_PIN_STATE_HIGH );
    silentstep_set_spm_pin ( ctx, SILENTSTEP_PIN_STATE_HIGH );
    silentstep_set_direction ( ctx, SILENTSTEP_DIR_CW );
    Delay_100ms ( );
    if ( SILENTSTEP_OK != silentstep_check_com ( ctx ) )
    {
        return SILENTSTEP_ERROR;
    }
    error_flag |= silentstep_set_toff ( ctx, SILENTSTEP_TOFF_DRIVER_DISABLE );
    Delay_10ms ( );
    error_flag |= silentstep_set_run_current ( ctx, SILENTSTEP_IRUN_DEFAULT );
    Delay_10ms ( );
    error_flag |= silentstep_set_step_res ( ctx, SILENTSTEP_MRES_FULLSTEP );
    Delay_10ms ( );
    return error_flag;
}

err_t silentstep_write_reg ( silentstep_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = reg | SILENTSTEP_SPI_WRITE_BIT;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t silentstep_read_reg ( silentstep_t *ctx, uint8_t reg, uint32_t *data_out )
{
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = reg & ( ~SILENTSTEP_SPI_WRITE_BIT );
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

err_t silentstep_check_com ( silentstep_t *ctx )
{
    uint32_t reg_data = 0;
    if ( SILENTSTEP_OK == silentstep_read_reg ( ctx, SILENTSTEP_REG_IOIN, &reg_data ) )
    {
        if ( SILENTSTEP_IOIN_VERSION_DEFAULT == ( reg_data & SILENTSTEP_IOIN_VERSION_MASK ) )
        {
            return SILENTSTEP_OK;
        }
    }
    return SILENTSTEP_ERROR;
}

void silentstep_set_direction ( silentstep_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void silentstep_switch_direction ( silentstep_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void silentstep_set_spm_pin ( silentstep_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->spm, state );
}

void silentstep_set_sdm_pin ( silentstep_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sdm, state );
}

void silentstep_set_step_pin ( silentstep_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

err_t silentstep_set_toff ( silentstep_t *ctx, uint8_t toff )
{
    uint32_t reg_data = 0;
    if ( toff > SILENTSTEP_TOFF_MAX )
    {
        return SILENTSTEP_ERROR;
    }
    if ( SILENTSTEP_ERROR == silentstep_read_reg ( ctx, SILENTSTEP_REG_CHOPCONF, &reg_data ) )
    {
        return SILENTSTEP_ERROR;
    }
    if ( ( ( uint32_t ) toff << SILENTSTEP_TOFF_SHIFT ) == ( reg_data & SILENTSTEP_TOFF_MASK ) )
    {
        return SILENTSTEP_OK;
    }
    reg_data &= ~SILENTSTEP_TOFF_MASK;
    reg_data |= ( ( uint32_t ) toff << SILENTSTEP_TOFF_SHIFT );
    return silentstep_write_reg ( ctx, SILENTSTEP_REG_CHOPCONF, reg_data );
}

err_t silentstep_set_step_res ( silentstep_t *ctx, uint8_t mres )
{
    uint32_t reg_data = 0;
    if ( mres > SILENTSTEP_MRES_FULLSTEP )
    {
        return SILENTSTEP_ERROR;
    }
    if ( SILENTSTEP_ERROR == silentstep_read_reg ( ctx, SILENTSTEP_REG_CHOPCONF, &reg_data ) )
    {
        return SILENTSTEP_ERROR;
    }
    if ( ( ( uint32_t ) mres << SILENTSTEP_MRES_SHIFT ) == ( reg_data & SILENTSTEP_MRES_MASK ) )
    {
        return SILENTSTEP_OK;
    }
    reg_data &= ~SILENTSTEP_MRES_MASK;
    reg_data |= ( ( uint32_t ) mres << SILENTSTEP_MRES_SHIFT );
    return silentstep_write_reg ( ctx, SILENTSTEP_REG_CHOPCONF, reg_data );
}

err_t silentstep_set_run_current ( silentstep_t *ctx, uint8_t irun )
{
    uint32_t reg_data = 0;
    if ( irun > SILENTSTEP_IRUN_MAX )
    {
        return SILENTSTEP_ERROR;
    }
    if ( SILENTSTEP_ERROR == silentstep_read_reg ( ctx, SILENTSTEP_REG_IHOLD_IRUN, &reg_data ) )
    {
        return SILENTSTEP_ERROR;
    }
    if ( ( ( uint32_t ) irun << SILENTSTEP_IRUN_SHIFT ) == ( reg_data & SILENTSTEP_IRUN_MASK ) )
    {
        return SILENTSTEP_OK;
    }
    reg_data &= ~SILENTSTEP_IRUN_MASK;
    reg_data |= ( ( uint32_t ) irun << SILENTSTEP_IRUN_SHIFT );
    return silentstep_write_reg ( ctx, SILENTSTEP_REG_IHOLD_IRUN, reg_data );
}

void silentstep_drive_motor ( silentstep_t *ctx, uint32_t steps, uint8_t speed )
{
    silentstep_set_toff ( ctx, SILENTSTEP_TOFF_DEFAULT );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        silentstep_set_step_pin ( ctx, SILENTSTEP_PIN_STATE_HIGH );
        silentstep_speed_delay ( speed );
        silentstep_set_step_pin ( ctx, SILENTSTEP_PIN_STATE_LOW );
        silentstep_speed_delay ( speed );
    }
    silentstep_set_toff ( ctx, SILENTSTEP_TOFF_DRIVER_DISABLE );
}

static void silentstep_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case SILENTSTEP_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case SILENTSTEP_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case SILENTSTEP_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case SILENTSTEP_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case SILENTSTEP_SPEED_VERY_FAST:
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

// ------------------------------------------------------------------------- END
