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
 * @file alphanumg2.c
 * @brief AlphaNum G 2 Click Driver.
 */

#include "alphanumg2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief AlphaNum G 2 ASCII characters table.
 * @details This repository contains integer literals 
 * for displaying ASCII characters on 16 segment LED displays.
 */
const uint16_t alphanumg2_ascii_table[ 95 ] = 
{
//-----------------------
//   Hex     Symbol    
//-----------------------
    0x0000, /* (space) */
    0x001C, /* ! */
    0x0204, /* " */
    0xAA3C, /* # */
    0xAABB, /* $ */
    0xEE99, /* % */
    0x9371, /* & */
    0x0200, /* ' */
    0x1400, /* ( */
    0x4100, /* ) */
    0xFF00, /* * */
    0xAA00, /* + */
    0x4000, /* , */
    0x8800, /* - */
    0x1000, /* . */
    0x4400, /* / */
    0x44FF, /* 0 */
    0x040C, /* 1 */
    0x4837, /* 2 */
    0x1433, /* 3 */
    0x889D, /* 4 */
    0x90B3, /* 5 */
    0x90F3, /* 6 */
    0x2403, /* 7 */
    0x88FF, /* 8 */
    0x093F, /* 9 */
    0x2200, /* : */
    0x4200, /* ; */
    0x9400, /* < */
    0x8830, /* = */
    0x4900, /* > */
    0x2807, /* ? */
    0x0AF7, /* @ */
    0x88CF, /* A */
    0x2A3F, /* B */
    0x00F3, /* C */
    0x223F, /* D */
    0x80F3, /* E */
    0x80C3, /* F */
    0x08FB, /* G */
    0x88CC, /* H */
    0x2233, /* I */
    0x007C, /* J */
    0x94C0, /* K */
    0x00F0, /* L */
    0x05CC, /* M */
    0x11CC, /* N */
    0x00FF, /* O */
    0x88C7, /* P */
    0x10FF, /* Q */
    0x98C7, /* R */
    0x88BB, /* S */
    0x2203, /* T */
    0x00FC, /* U */
    0x44C0, /* V */
    0x50CC, /* W */
    0x5500, /* X */
    0x88BC, /* Y */
    0x4433, /* Z */
    0x2212, /* [ */
    0x1100, /* \ */
    0x2221, /* ] */
    0x5000, /* ^ */
    0x0030, /* _ */
    0x0100, /* ` */
    0xA070, /* a */
    0xA0E0, /* b */
    0x8060, /* c */
    0x281C, /* d */
    0xC060, /* e */
    0xAA02, /* f */
    0xA2A1, /* g */
    0xA0C0, /* h */
    0x2000, /* i */
    0x2260, /* j */
    0x3600, /* k */
    0x00C0, /* l */
    0xA848, /* m */
    0xA040, /* n */
    0xA060, /* o */
    0x82C1, /* p */
    0xA281, /* q */
    0x8040, /* r */
    0xA0A1, /* s */
    0x80E0, /* t */
    0x2060, /* u */
    0x4040, /* v */
    0x5048, /* w */
    0x5500, /* x */
    0x0A1C, /* y */
    0xC020, /* z */
    0xA212, /* { */
    0x2200, /* | */
    0x2A21, /* } */
    0xCC00, /* ~ */
};

/**
 * @brief AlphaNum G 2 get character function.
 * @details This function returns the position 
 * from the ASCII table of the desired character.
 */
static uint16_t dev_get_character ( uint8_t character );

void alphanumg2_cfg_setup ( alphanumg2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->blk   = HAL_PIN_NC;
    cfg->ca1 = HAL_PIN_NC;
    cfg->ca2 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t alphanumg2_init ( alphanumg2_t *ctx, alphanumg2_cfg_t *cfg ) 
{
    ctx->char_duration = ALPHANUMG2_DEFAULT_DUR_1000_MS;
    
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

    digital_out_init( &ctx->blk, cfg->blk );
    digital_out_init( &ctx->ca1, cfg->ca1 );
    digital_out_init( &ctx->ca2, cfg->ca2 );

    return SPI_MASTER_SUCCESS;
}

err_t alphanumg2_default_cfg ( alphanumg2_t *ctx ) 
{    
    alphanumg2_set_outputs_on( ctx );
    
    alphanumg2_set_seg_left_on( ctx );
    
    alphanumg2_set_seg_right_on( ctx );
    
    alphanumg2_set_char_duration( ctx, ALPHANUMG2_DEFAULT_DUR_1000_MS );

    return alphanumg2_display_character( ctx, ' ', ALPHANUMG2_BRIGHTNESS_MAX, 
                                              ' ', ALPHANUMG2_BRIGHTNESS_MAX );
}

err_t alphanumg2_generic_write ( alphanumg2_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t alphanumg2_generic_read ( alphanumg2_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

void alphanumg2_set_char_duration ( alphanumg2_t *ctx, uint16_t duration_ms ) 
{
    ctx->char_duration =  duration_ms / 16;
}

void alphanumg2_set_outputs_off ( alphanumg2_t *ctx ) 
{
    digital_out_high( &ctx->blk );
}

void alphanumg2_set_outputs_on ( alphanumg2_t *ctx ) 
{
    digital_out_low( &ctx->blk );
}

void alphanumg2_set_seg_left_off ( alphanumg2_t *ctx ) 
{
    digital_out_high( &ctx->ca1 );
}

void alphanumg2_set_seg_left_on ( alphanumg2_t *ctx ) 
{
    digital_out_low( &ctx->ca1 );
}

void alphanumg2_set_seg_right_off ( alphanumg2_t *ctx ) 
{
    digital_out_high( &ctx->ca2 );
}

void alphanumg2_set_seg_right_on ( alphanumg2_t *ctx ) 
{
    digital_out_low( &ctx->ca2 );
}

err_t alphanumg2_set_led_output ( alphanumg2_t *ctx, uint16_t seg_bit_mask, 
                                  alphanumg2_dot_t seg_dot, uint16_t brightness ) 
{
    err_t err_flag = ALPHANUMG2_ERROR;
    uint8_t data_buf[ 36 ] = { 0 };
    uint8_t tmp_pos = DUMMY;
    if ( ALPHANUMG2_SET_DOT == seg_dot )
    {
        data_buf[ 10 ] |= ( uint8_t ) ( brightness & ALPHANUMG2_NIBBLE_LOW );
        data_buf[ 11 ] |= ( uint8_t ) ( brightness >> 4 );
    }
    
    if ( ALPHANUMG2_BRIGHTNESS_MAX >= brightness )
    {
        for ( uint8_t n_cnt = 12; n_cnt < 36; n_cnt += 3 )
        {
            if ( seg_bit_mask & ( ALPHANUMG2_WORD_BIT_POS_15 >> tmp_pos ) )
            {
                data_buf[ n_cnt ] |= ( uint8_t ) ( ( brightness >> 4 ) & ALPHANUMG2_BYTE_LOW );
                data_buf[ n_cnt + 1 ] |= ( uint8_t ) ( ( brightness & ALPHANUMG2_NIBBLE_LOW ) << 4 );
                data_buf[ n_cnt + 2 ] |= DUMMY;
            } 
            if ( seg_bit_mask & ( ALPHANUMG2_WORD_BIT_POS_14 >> tmp_pos ) )
            {
                data_buf[ n_cnt ] |= DUMMY;
                data_buf[ n_cnt + 1 ] |= ( uint8_t ) ( ( brightness >> 8 ) & ALPHANUMG2_NIBBLE_LOW );
                data_buf[ n_cnt + 2 ] |= ( uint8_t ) brightness;
            }
            tmp_pos += 2;
        }
        err_flag = alphanumg2_generic_write( ctx, data_buf, 36 );
    }
    return err_flag;
}

err_t alphanumg2_display_character ( alphanumg2_t *ctx, uint8_t left_char, uint16_t left_brightness,  
                                                        uint8_t right_char, uint16_t right_brightness ) 
{
    err_t err_flag = ALPHANUMG2_OK;
    if ( ( ALPHANUMG2_BRIGHTNESS_MAX < left_brightness ) || 
         ( ALPHANUMG2_BRIGHTNESS_MAX < right_brightness ) )
    {
        err_flag = ALPHANUMG2_ERROR;
    }
    else
    {
        alphanumg2_set_seg_left_off( ctx );
        alphanumg2_set_seg_right_off( ctx );
        for ( uint16_t n_cnt = 0; n_cnt < ctx->char_duration; n_cnt++ ) 
        {
            err_flag |= alphanumg2_set_led_output( ctx, dev_get_character( left_char ), 
                                                        ALPHANUMG2_NO_DOT, 
                                                        left_brightness );
            alphanumg2_set_seg_right_off( ctx );
            alphanumg2_set_seg_left_on( ctx );
            Delay_8ms();
            
            alphanumg2_set_seg_left_off( ctx );
            alphanumg2_set_seg_right_off( ctx );
            
            err_flag |= alphanumg2_set_led_output( ctx, dev_get_character( right_char ), 
                                                        ALPHANUMG2_NO_DOT, 
                                                        right_brightness );
            alphanumg2_set_seg_left_off( ctx );
            alphanumg2_set_seg_right_on( ctx );
            Delay_8ms();
            alphanumg2_set_seg_left_off( ctx );
            alphanumg2_set_seg_right_off( ctx );
        }
    }
    return err_flag;
}

static uint16_t dev_get_character ( uint8_t character ) 
{
    if ( ( ' ' <= character ) && ( '~' >= character ) ) 
    {
        return alphanumg2_ascii_table[ character - ' ' ];
    } 
    else 
    {
        return ALPHANUMG2_ERROR;
    }
}

// ------------------------------------------------------------------------- END
