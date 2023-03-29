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
 * @file alphanumr.c
 * @brief AlphaNum R Click Driver.
 */

#include "alphanumr.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// ------------------------------------------------------------------ CONSTANTS

static const uint16_t alphanumericr_character_table[ 52 ] =
{
 // 14segment bit order
 // (dp)(h) (i) (m) (k) (g2)(g1)(j)(i)(f)(e)(d)(c)(b)(a)
 // (14)(13)(12)(11)(10)(9) (8) (7)(6)(5)(4)(3)(2)(1)(0)
 // CHARACTERS
 //----------------------------------------------------
 // Hex        Symbol            Binary
 //----------------------------------------------------
    0x0300,    // '-'            0b0000001100000000
    0x4000,    // '.'            0b0100000000000000
    0x0880,    // '/'            0b0000100010000000
    0x003F,    // '0'            0b0000000000111111
    0x0006,    // '1'            0b0000000000000110
    0x031B,    // '2'            0b0000001100011011
    0x030F,    // '3'            0b0000001100001111
    0x0326,    // '4'            0b0000001100100110
    0x032D,    // '5'            0b0000001100101101
    0x033D,    // '6'            0b0000001100111101
    0x0007,    // '7'            0b0000000000000111
    0x033F,    // '8'            0b0000001100111111
    0x032F,    // '9'            0b0000001100101111
    0x1040,    // ':'            0b0001000001000000
    0x0840,    // ';'            0b0000100001000000
    0x0480,    // '<'            0b0000010010000000
    0x0776,    // '='            0b0000001100001000
    0x2800,    // '>'            0b0010100000000000
    0x1223,    // '?'            0b0001001000100011
    0x027B,    // '@'            0b0000001001111011
    0x0337,    // 'A'            0b0000001100110111
    0x124F,    // 'B'            0b0001001001001111
    0x0039,    // 'C'            0b0000001100111001
    0x104F,    // 'D'            0b0001000001001111
    0x0339,    // 'E'            0b0000001100111001
    0x0331,    // 'F'            0b0000001100110001
    0x023D,    // 'G'            0b0000001000111101
    0x0336,    // 'H'            0b0000001100110110
    0x1040,    // 'I'            0b0001000001000000
    0x001E,    // 'J'            0b0000000000011110
    0x05B0,    // 'K'            0b0000010110110000
    0x0038,    // 'L'            0b0000000000111000
    0x20B6,    // 'M'            0b0010000010110110
    0x2436,    // 'N'            0b0010010000110110
    0x003F,    // 'O'            0b0000000000111111
    0x0333,    // 'P'            0b0000001100110011
    0x443F,    // 'Q'            0b0100010000111111
    0x0733,    // 'R'            0b0000011100110011
    0x032D,    // 'S'            0b0000001100101101
    0x1063,    // 'T'            0b0001000001100011
    0x003E,    // 'U'            0b0000000000111110
    0x08B0,    // 'V'            0b0000100010110000
    0x0C36,    // 'W'            0b0000110000110110
    0x2C80,    // 'X'            0b0010110010000000
    0x3080,    // 'Y'            0b0011000010000000
    0x0889,    // 'Z'            0b0000100010001001
    0x0039,    // '['            0b0000000000111001
    0x2400,    // '\'            0b0000100010000000
    0x000F,    // ']'            0b0000000000001111
    0x0081,    // '^'            0b0000000010000001
    0x0008,    // '_'            0b0000000000001000
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t dev_get_character ( uint8_t character );
static uint16_t dev_get_number ( uint8_t number );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void alphanumr_cfg_setup ( alphanumr_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->le2 = HAL_PIN_NC;
    cfg->ns1 = HAL_PIN_NC;
    cfg->ns = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t alphanumr_init ( alphanumr_t *ctx, alphanumr_cfg_t *cfg ) {
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

    digital_out_init( &ctx->le2, cfg->le2 );
    digital_out_init( &ctx->ns1, cfg->ns1 );
    digital_out_init( &ctx->ns, cfg->ns );

    return SPI_MASTER_SUCCESS;
}

void alphanumr_display_write ( alphanumr_t *ctx, uint16_t left_char, uint16_t right_char ) {
    uint16_t counter;
    uint8_t tmp_buf[ 4 ];

    for ( counter = 0; counter < ctx->display_speed; counter++ ) {
        
        tmp_buf[ 0 ] = right_char >> 8;
        tmp_buf[ 1 ] = right_char & 0xFF;
        tmp_buf[ 2 ] = left_char >> 8;
        tmp_buf[ 3 ] = left_char & 0xFF;
        
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tmp_buf, 4 );
        spi_master_deselect_device( ctx->chip_select ); 

        // PWM pin

        alphanumr_set_pwm_low( ctx );
        Delay_10ms( );
        alphanumr_set_pwm_high( ctx );

        // Reset pin

        alphanumr_set_rst_low( ctx );
        alphanumr_set_rst_high( ctx );

        // Interrupt pin

        alphanumr_set_int_low( ctx );
        Delay_10ms( );
        alphanumr_set_int_high( ctx );

        // Chip select + PWM

        spi_master_select_device( ctx->chip_select );
        spi_master_deselect_device( ctx->chip_select ); 
        alphanumr_set_pwm_low( ctx );
        alphanumr_set_pwm_high( ctx );
    }
}

void alphanumr_set_display_interval ( alphanumr_t *ctx, uint16_t delay_char_display ) {
    ctx->display_speed =  delay_char_display / 20;
}

void alphanumr_write_character ( alphanumr_t *ctx, uint8_t left_char, uint8_t right_char ) {
    alphanumr_display_write( ctx, dev_get_character( left_char ),
    dev_get_character( right_char ) );
}

void alphanumr_write_number ( alphanumr_t *ctx, uint8_t left_char, uint8_t right_char ) {
    alphanumr_display_write( ctx, dev_get_number( left_char ),
    dev_get_number( right_char ) );
}

void alphanumr_set_rst_high ( alphanumr_t *ctx ) {
    digital_out_high( &ctx->le2 );
}

void alphanumr_set_rst_low ( alphanumr_t *ctx ) {
    digital_out_low( &ctx->le2 );
}

void alphanumr_set_pwm_high ( alphanumr_t *ctx ) {
    digital_out_high( &ctx->ns1 );
}

void alphanumr_set_pwm_low ( alphanumr_t *ctx ) {
    digital_out_low( &ctx->ns1 );
}

void alphanumr_set_int_high ( alphanumr_t *ctx ) {
    digital_out_high( &ctx->ns );
}

void alphanumr_set_int_low ( alphanumr_t *ctx ) {
    digital_out_low( &ctx->ns );
}



// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t dev_get_character ( uint8_t character ) {
    if ( ( character >= '-' ) && ( character <= '_' ) ) {
        return alphanumericr_character_table[ character - '-' ];
    } else {
        return -1;
    }
}

static uint16_t dev_get_number ( uint8_t number )
{
    if ( ( number >= 0 ) && ( number <= 9 ) ) {
        return alphanumericr_character_table[ number + 3 ];
    } else {
        return -1;
    }
}

// ------------------------------------------------------------------------- END
