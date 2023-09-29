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
 * @file stepdown9.c
 * @brief Step Down 9 Click Driver.
 */

#include "stepdown9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void stepdown9_cfg_setup ( stepdown9_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->pg   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t stepdown9_init ( stepdown9_t *ctx, stepdown9_cfg_t *cfg ) 
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

    digital_in_init( &ctx->pg, cfg->pg );

    return SPI_MASTER_SUCCESS;
}

err_t stepdown9_default_cfg ( stepdown9_t *ctx ) 
{
    err_t error_flag = STEPDOWN9_OK;
    
    stepdown9_set_en_pin( ctx, STEPDOWN9_PIN_STATE_HIGH );
    
    error_flag = stepdown9_set_output( ctx, STEPDOWN9_VOUT_1V6 );

    return error_flag;
}

err_t stepdown9_generic_write ( stepdown9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t stepdown9_generic_read ( stepdown9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void stepdown9_set_en_pin ( stepdown9_t *ctx, uint8_t pin_state )
{
    if ( STEPDOWN9_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

uint8_t stepdown9_get_pg_pin ( stepdown9_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

err_t stepdown9_set_wiper_pos ( stepdown9_t *ctx, uint8_t wiper_pos )
{
    err_t error_flag = STEPDOWN9_OK;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &wiper_pos, 1 );
    spi_master_deselect_device( ctx->chip_select );   
       
    return error_flag;
}

err_t stepdown9_set_resistance ( stepdown9_t *ctx, uint32_t res_ohm )
{
    err_t error_flag = STEPDOWN9_OK;
    if ( ( res_ohm <= ( STEPDOWN9_FULL_SCALE_RES_100_KOHM + STEPDOWN9_RESISTANCE_MIN) ) && 
         ( res_ohm >= STEPDOWN9_RESISTANCE_MIN ) )
    {
        float tmp  = ( res_ohm - STEPDOWN9_RESISTANCE_MIN );
        tmp /= STEPDOWN9_FULL_SCALE_RES_100_KOHM;
        tmp *= STEPDOWN9_WIPER_POS_MAX;
        tmp += STEPDOWN9_ROUND_TO_NEAREST_INT;
        stepdown9_set_wiper_pos( ctx, ( uint8_t ) tmp );
    }
    return error_flag;
}

err_t stepdown9_set_output ( stepdown9_t *ctx, uint8_t voltage )
{
    err_t error_flag = STEPDOWN9_OK;
    
    switch ( voltage )
    {
        case ( STEPDOWN9_VOUT_1V6 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_1V6_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_2V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_2V_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_2V5 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_2V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_3V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_3V_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_3V3 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_3V3_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_3V5 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_3V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_4V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_4V_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_4V5 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_4V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_5V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_5V_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_5V5 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_5V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_6V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_6V_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_6V5 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_6V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_7V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_7V_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_7V5 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_7V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_8V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_8V_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_8V5 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_8V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_9V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_9V_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_9V5 ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_9V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN9_VOUT_10V ):
        {
            error_flag |= stepdown9_set_resistance( ctx, STEPDOWN9_VOUT_10V_RESISTANCE );
            break;
        }
        default:
        {
            error_flag = STEPDOWN9_ERROR;
        }
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
