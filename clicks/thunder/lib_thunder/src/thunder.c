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
 * \file
 *
 */

#include "thunder.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define THUNDER_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thunder_cfg_setup ( thunder_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins
    cfg->irq = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t thunder_init ( thunder_t *ctx, thunder_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, THUNDER_DUMMY ) ) 
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

    // Input pins
    digital_in_init( &ctx->irq, cfg->irq );

    return THUNDER_OK;
}

void thunder_default_cfg ( thunder_t *ctx )
{
    THUNDER_SET_DATA_SAMPLE_EDGE;
    
    thunder_send_command( ctx, THUNDER_RESET_COMM );
    
    thunder_write_reg( ctx, THUNDER_REG_INTERR_PIN_CONFIG, THUNDER_NO_DISPLAY_ON_IRQ_PIN | 
                                                           THUNDER_DEFAULT_TUNE_CAP );
    Delay_10ms ( );
    thunder_write_reg( ctx, THUNDER_REG_CONFIG_0, THUNDER_OUTDOOR | 
                                                  THUNDER_NORMAL_MODE );
    thunder_send_command( ctx, THUNDER_CALIB_RCO_COMM );
    
    thunder_write_reg( ctx, THUNDER_REG_CONFIG_1, THUNDER_DEFAULT_NOISE_FLOOR_LVL | 
                                                  THUNDER_DEFAULT_WDG_THRESHOLD );
    thunder_write_reg( ctx, THUNDER_REG_CONFIG_2, THUNDER_CLEAR_STAT | 
                                                  THUNDER_1_LIGHTNING | 
                                                  THUNDER_DEFAULT_SREJ );
    thunder_write_reg( ctx, THUNDER_REG_CONFIG_3_INTERR, THUNDER_DIV_RATIO_16 | 
                                                         THUNDER_UNMASK_DISTURBER );
    Delay_100ms ( );
    thunder_check_int ( ctx );
    Delay_100ms ( );
}

err_t thunder_generic_write ( thunder_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t thunder_generic_read ( thunder_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t reg_addr = reg | 0x40;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_addr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t thunder_write_reg ( thunder_t *ctx, uint8_t reg, uint8_t data_in )
{
    return thunder_generic_write ( ctx, reg, &data_in, 1 );
}

err_t thunder_read_reg ( thunder_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return thunder_generic_read ( ctx, reg, data_out, 1 );
}

void thunder_send_command ( thunder_t *ctx, uint8_t command )
{
    if ( command == 0 )
    {
        thunder_write_reg( ctx, THUNDER_REG_RESET, 0x96 );
    }
    else
    {
        thunder_write_reg( ctx, THUNDER_REG_CALIB, 0x96 );
    }
    
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
}

uint8_t thunder_check_int ( thunder_t *ctx )
{
    uint8_t interr_check = 0;
    
    if ( digital_in_read( &ctx->irq ) )
    {
        thunder_read_reg( ctx, THUNDER_REG_CONFIG_3_INTERR, &interr_check );
        interr_check &= 0x0F;
    }
    
    return interr_check;
}

void thunder_get_storm_info ( thunder_t *ctx, uint32_t *energy_out, uint8_t *distance_out )
{
    uint32_t temp = 0;
    uint8_t tmp[ 4 ] = { 0 };

    thunder_generic_read ( ctx, THUNDER_REG_ENERGY_LIGHTNING_LSBYTE, tmp, 4 );
    
    temp = tmp[ 2 ] & 0x1F;
    temp <<= 8;
    temp |= tmp[ 1 ];
    temp <<= 8;
    temp |= tmp[ 0 ];
    *energy_out = temp;
    
    *distance_out = tmp[ 3 ] & 0x3F;
}

uint8_t thunder_check_irq_pin ( thunder_t *ctx )
{
    return digital_in_read( &ctx->irq );
}

// ------------------------------------------------------------------------- END

