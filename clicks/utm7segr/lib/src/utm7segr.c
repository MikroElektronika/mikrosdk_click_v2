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
 * @file utm7segr.c
 * @brief UT-M 7-SEG R Click Driver.
 */

#include "utm7segr.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define UTM7SEG_DUMMY            0

/**
 * @brief No number data.
 * @details Definition of no number data.
 */
#define UTM7SEG_NO_NUMB           0

/**
 * @brief Dot position.
 * @details Definition of dot position.
 */
#define UTM7SEGR_DOT_POSITION 0x80

static const uint8_t hex_number_matrix [ 16 ] = {
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F,  // 9
    0x77,  // A
    0x7C,  // B
    0x39,  // C
    0x5E,  // D
    0x79,  // E
    0x71   // F
};

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void utm7segr_cfg_setup ( utm7segr_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    
    cfg->oe = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t utm7segr_init ( utm7segr_t *ctx, utm7segr_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, UTM7SEG_DUMMY ) == SPI_MASTER_ERROR ) {
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

    // Output pins.

    digital_out_init( &ctx->oe, cfg->oe );
   
    return SPI_MASTER_SUCCESS;
}

void utm7segr_default_cfg ( utm7segr_t *ctx ) {
    // Click default configuration.
    utm7segr_display_state( ctx, UTM7SEGR_DISPLAY_ON );
}

err_t utm7segr_generic_write ( utm7segr_t *ctx, uint8_t *data_in ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void utm7segr_display_state ( utm7segr_t *ctx, uint8_t state ) {
    digital_out_write( &ctx->oe, state );
}

err_t utm7segr_display_number ( utm7segr_t *ctx, uint8_t number, uint8_t dot_pos ) {
    uint8_t right_pos;
    uint8_t left_pos;
    uint8_t data_buf[ 2 ];

    number %= 100;

    left_pos = number / 10;
    right_pos = number % 10;

    switch ( dot_pos ) {
        case UTM7SEGR_NO_DOT: {
            right_pos = hex_number_matrix[ right_pos ];
            left_pos = hex_number_matrix[ left_pos ];
            break;
        }
        case UTM7SEGR_DOT_RIGHT: {
            right_pos = hex_number_matrix[ right_pos ] | UTM7SEGR_DOT_POSITION;
            left_pos = hex_number_matrix[ left_pos ];
            break;
        }
        case UTM7SEGR_DOT_LEFT: {
            right_pos = hex_number_matrix[ right_pos ];
            left_pos = hex_number_matrix[ left_pos ] | UTM7SEGR_DOT_POSITION;
            break;
        }
        case UTM7SEGR_DOT_LEFT_RIGHT: {
            right_pos = hex_number_matrix[ right_pos ] | UTM7SEGR_DOT_POSITION;
            left_pos = hex_number_matrix[ left_pos ] | UTM7SEGR_DOT_POSITION;
            break;
        }
    }

    if ( left_pos == UTM7SEG_NO_NUMB ) {
        data_buf[ 0 ] = right_pos;
        data_buf[ 1 ] = UTM7SEG_DUMMY;
    } else {
        data_buf[ 0 ] = right_pos;
        data_buf[ 1 ] = left_pos;
    }

    err_t error_flag = utm7segr_generic_write( ctx, data_buf );
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
