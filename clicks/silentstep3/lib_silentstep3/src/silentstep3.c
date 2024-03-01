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
 * @file silentstep3.c
 * @brief Silent Step 3 Click Driver.
 */

#include "silentstep3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void silentstep3_speed_delay ( uint8_t speed_macro );

void silentstep3_cfg_setup ( silentstep3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->sg   = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t silentstep3_init ( silentstep3_t *ctx, silentstep3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->step, cfg->step );
    digital_out_init( &ctx->dir, cfg->dir );

    digital_in_init( &ctx->sg, cfg->sg );

    return SPI_MASTER_SUCCESS;
}

err_t silentstep3_default_cfg ( silentstep3_t *ctx ) 
{
    err_t error_flag = SILENTSTEP3_OK;
    error_flag |= silentstep3_write_register ( ctx, SILENTSTEP3_REG_DRVCONF, 
                                                    SILENTSTEP3_DRVCONF_SDOFF_0 | 
                                                    SILENTSTEP3_DRVCONF_RDSEL_SG_CS_LEVEL, NULL );
    error_flag |= silentstep3_write_register ( ctx, SILENTSTEP3_REG_DRVCTRL, 
                                                    SILENTSTEP3_DRVCTRL_0_MRES_1, NULL );
    error_flag |= silentstep3_write_register ( ctx, SILENTSTEP3_REG_CHOPCONF, 
                                                    SILENTSTEP3_CHOPCONF_TBL_32 | 
                                                    SILENTSTEP3_CHOPCONF_HEND_0 | 
                                                    SILENTSTEP3_CHOPCONF_HSTRT_4 |
                                                    SILENTSTEP3_CHOPCONF_TOFF_4, NULL );
    error_flag |= silentstep3_write_register ( ctx, SILENTSTEP3_REG_SMARTEN, 
                                                    SILENTSTEP3_SMARTEN_SEIMIN_QUARTER_CS | 
                                                    SILENTSTEP3_SMARTEN_SEDN_32 |
                                                    SILENTSTEP3_SMARTEN_SEMAX_2 | 
                                                    SILENTSTEP3_SMARTEN_SEUP_1 |
                                                    SILENTSTEP3_SMARTEN_SEMIN_2, NULL );
    error_flag |= silentstep3_write_register ( ctx, SILENTSTEP3_REG_SGCSCONF, 
                                                    SILENTSTEP3_SGCSCONF_SFILT_FILTERED |
                                                    SILENTSTEP3_SGCSCONF_SGT_0 | 
                                                    SILENTSTEP3_SGCSCONF_CS_2_OF_32, NULL );
    return error_flag;
}

err_t silentstep3_write_register ( silentstep3_t *ctx, uint8_t reg, uint32_t data_in, uint32_t *data_out )
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t error_flag = SILENTSTEP3_OK;
    switch ( reg )
    {
        case SILENTSTEP3_REG_DRVCTRL:
        {
            ctx->drvctrl = data_in;
            break;
        }
        case SILENTSTEP3_REG_CHOPCONF:
        {
            ctx->chopconf = data_in;
            break;
        }
        case SILENTSTEP3_REG_SMARTEN:
        {
            ctx->smarten = data_in;
            break;
        }
        case SILENTSTEP3_REG_SGCSCONF:
        {
            ctx->sgcsconf = data_in;
            break;
        }
        case SILENTSTEP3_REG_DRVCONF:
        {
            ctx->drvconf = data_in;
            break;
        }
        default:
        {
            return SILENTSTEP3_ERROR;
        }
    }
    spi_master_select_device( ctx->chip_select );
    data_buf[ 0 ] = ( uint8_t ) ( ( reg << 1 ) | ( ( data_in >> 16 ) & 0x03 ) );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 1 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 2 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 2 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( SILENTSTEP3_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint32_t ) ( data_buf[ 0 ] & 0x0F ) << 16 ) | 
                    ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

err_t silentstep3_set_step_mode ( silentstep3_t *ctx, uint8_t mode )
{
    err_t error_flag = SILENTSTEP3_OK;
    if ( mode > SILENTSTEP3_MODE_FULL_STEP )
    {
        return SILENTSTEP3_ERROR;
    }
    if ( ctx->drvconf & SILENTSTEP3_DRVCONF_SDOFF_MASK )
    {
        ctx->drvconf &= ( ~SILENTSTEP3_DRVCONF_SDOFF_MASK );
        error_flag |= silentstep3_write_register ( ctx, SILENTSTEP3_REG_DRVCONF, ctx->drvconf, NULL );
    }
    if ( ( ctx->drvctrl & SILENTSTEP3_DRVCTRL_0_MRES_MASK ) == mode )
    {
        return SILENTSTEP3_OK;
    }
    ctx->drvctrl &= ( ~SILENTSTEP3_DRVCTRL_0_MRES_MASK );
    ctx->drvctrl |= mode;
    return silentstep3_write_register ( ctx, SILENTSTEP3_REG_DRVCTRL, ctx->drvctrl, NULL );
}

void silentstep3_enable_device ( silentstep3_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void silentstep3_disable_device ( silentstep3_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void silentstep3_set_direction ( silentstep3_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void silentstep3_switch_direction ( silentstep3_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void silentstep3_set_step_pin ( silentstep3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

uint8_t silentstep3_get_sg_pin ( silentstep3_t *ctx )
{
    return digital_in_read ( &ctx->sg );
}

void silentstep3_drive_motor ( silentstep3_t *ctx, uint32_t steps, uint8_t speed )
{
    silentstep3_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        silentstep3_set_step_pin ( ctx, SILENTSTEP3_PIN_STATE_HIGH );
        silentstep3_speed_delay ( speed );
        silentstep3_set_step_pin ( ctx, SILENTSTEP3_PIN_STATE_LOW );
        silentstep3_speed_delay ( speed );
    }
    silentstep3_disable_device ( ctx );
}

static void silentstep3_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case SILENTSTEP3_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case SILENTSTEP3_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case SILENTSTEP3_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case SILENTSTEP3_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case SILENTSTEP3_SPEED_VERY_FAST:
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
