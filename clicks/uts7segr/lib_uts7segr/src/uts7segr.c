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
 * @file uts7segr.c
 * @brief UT-S 7-SEG R Click Driver.
 */

#include "uts7segr.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
// -------------------------------------------------------------  PRIVATE MACROS 

#define UTS7SEGR_DUMMY           0x00
#define UTS7SEGR_DOT_POSITION    0x80

// ------------------------------------------------------------------ CONSTANTS

static const uint8_t hex_number_matrix [ 16 ] =
{
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

void uts7segr_cfg_setup ( uts7segr_cfg_t *cfg ) {

    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC; 

    // Additional gpio pins   

    cfg->oe = HAL_PIN_NC;
                               
    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t uts7segr_init ( uts7segr_t *ctx, uts7segr_cfg_t *cfg ) {
    
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed = cfg->spi_speed;
    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;
    spi_cfg.default_write_data = UTS7SEGR_DUMMY;     

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) { 
        return UTS7SEGR_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, UTS7SEGR_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // Output pins 
    
    digital_out_init( &ctx->oe, cfg->oe );
  
    return UTS7SEGR_OK;
}

void uts7segr_default_cfg ( uts7segr_t *ctx ) { 
    // Click default configuration.
    uts7segr_display_state( ctx, UTS7SEGR_DISPLAY_ON );
}

err_t uts7segr_generic_write ( uts7segr_t *ctx, uint8_t *data_in ) {  
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, data_in, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    return err_flag;
}

void uts7segr_display_state ( uts7segr_t *ctx, uint8_t state ) {
    digital_out_write( &ctx->oe, state );
}

err_t uts7segr_display_number ( uts7segr_t *ctx, uint8_t number, uint8_t dot_pos ) {
    uint8_t right_pos;
    uint8_t left_pos;
    uint8_t data_buf[ 2 ];

    number %= 100;

    left_pos = number / 10;
    right_pos = number % 10;

    switch ( dot_pos )
    {
        case UTS7SEGR_NO_DOT: {
            right_pos = hex_number_matrix[ right_pos ];
            left_pos = hex_number_matrix[ left_pos ];
            break;
        }
        case UTS7SEGR_DOT_RIGHT: {
            right_pos = hex_number_matrix[ right_pos ] | UTS7SEGR_DOT_POSITION;
            left_pos = hex_number_matrix[ left_pos ];
            break;
        }
        case UTS7SEGR_DOT_LEFT: {
            right_pos = hex_number_matrix[ right_pos ];
            left_pos = hex_number_matrix[ left_pos ] | UTS7SEGR_DOT_POSITION;
            break;
        }
        case UTS7SEGR_DOT_LEFT_RIGHT: {
            right_pos = hex_number_matrix[ right_pos ] | UTS7SEGR_DOT_POSITION;
            left_pos = hex_number_matrix[ left_pos ] | UTS7SEGR_DOT_POSITION;
            break;
        }
    }

    if ( left_pos == 0) {
        data_buf[ 0 ] = right_pos;
        data_buf[ 1 ] = UTS7SEGR_DUMMY;
    }
    else {
        data_buf[ 0 ] = right_pos;
        data_buf[ 1 ] = left_pos;
    }

    err_t err_flag = uts7segr_generic_write( ctx, data_buf );
    
    return err_flag;
}

// ------------------------------------------------------------------------- END
