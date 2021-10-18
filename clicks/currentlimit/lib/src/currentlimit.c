/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file currentlimit.c
 * @brief Current Limit Click Driver.
 */

#include "currentlimit.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Turn-On Time function
 * @details Function is a 200 us delay that gives time to the device 
 * in order for it to turn on properly.
**/
static void dev_turn_on_time ( void );

/**
 * @brief Turn-Off Time function
 * @details Function is a 22 us delay that gives time to the device
 * in order for it to turn off properly.
**/
static void dev_turn_off_time ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void currentlimit_cfg_setup ( currentlimit_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t currentlimit_init ( currentlimit_t *ctx, currentlimit_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->en, cfg->en );

    return SPI_MASTER_SUCCESS;
}

err_t currentlimit_generic_write ( currentlimit_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t currentlimit_generic_read ( currentlimit_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void currentlimit_dev_enable ( currentlimit_t *ctx, uint8_t state ) {
    if ( state == CURRENTLIMIT_ENABLE ) {
        digital_out_low( &ctx->en );
        dev_turn_on_time( );
    } else if ( state == CURRENTLIMIT_DISABLE ) {
        digital_out_high( &ctx->en );
        dev_turn_off_time( );
    }
}

void currentlimit_set_limit ( currentlimit_t *ctx, uint8_t lim_val ) {
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &lim_val, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
}

void currentlimit_set_limit_calc ( currentlimit_t *ctx, float lim_val ) {
    float r_val;
    uint8_t r_code;
    
    if ( lim_val > CURRENTLIMIT_I_MAX ) {
        lim_val = CURRENTLIMIT_I_MAX;
    }
    
    r_val = ( CURRENTLIMIT_CALC_COEF / lim_val );
    r_val -= CURRENTLIMIT_R_BASE;
    r_code = 255 - (uint8_t)( r_val / CURRENTLIMIT_LSB_VAL );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &r_code, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_turn_on_time ( void ) {
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
}

static void dev_turn_off_time ( void ) {
    Delay_22us( );
}

// ------------------------------------------------------------------------- END
