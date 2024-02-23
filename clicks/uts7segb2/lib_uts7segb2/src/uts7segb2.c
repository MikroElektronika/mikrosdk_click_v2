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
 * @file uts7segb2.c
 * @brief UT-S 7-SEG B 2 Click Driver.
 */

#include "uts7segb2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief UT-S 7-SEG B 2 ASCII characters table.
 * @details This repository contains integer literals 
 * for displaying ASCII characters on 7 segment LED displays.
 */
const uint8_t uts7segb2_ascii_table[ 95 ] = 
{
//-------------------
//   Hex    Symbol    
//-------------------
    0x00, /* (space) */
    0x86, /* ! */
    0x22, /* " */
    0x7E, /* # */
    0x6D, /* $ */
    0xD2, /* % */
    0x46, /* & */
    0x20, /* ' */
    0x29, /* ( */
    0x0B, /* ) */
    0x21, /* * */
    0x70, /* + */
    0x10, /* , */
    0x40, /* - */
    0x80, /* . */
    0x52, /* / */
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
    0x09, /* : */
    0x0D, /* ; */
    0x61, /* < */
    0x48, /* = */
    0x43, /* > */
    0xD3, /* ? */
    0x5F, /* @ */
    0x77, /* A */
    0x7C, /* B */
    0x39, /* C */
    0x5E, /* D */
    0x79, /* E */
    0x71, /* F */
    0x3D, /* G */
    0x76, /* H */
    0x30, /* I */
    0x1E, /* J */
    0x75, /* K */
    0x38, /* L */
    0x15, /* M */
    0x37, /* N */
    0x3F, /* O */
    0x73, /* P */
    0x6B, /* Q */
    0x33, /* R */
    0x6D, /* S */
    0x78, /* T */
    0x3E, /* U */
    0x3E, /* V */
    0x2A, /* W */
    0x76, /* X */
    0x6E, /* Y */
    0x5B, /* Z */
    0x39, /* [ */
    0x64, /* \ */
    0x0F, /* ] */
    0x23, /* ^ */
    0x08, /* _ */
    0x02, /* ` */
    0x5F, /* a */
    0x7C, /* b */
    0x58, /* c */
    0x5E, /* d */
    0x7B, /* e */
    0x71, /* f */
    0x6F, /* g */
    0x74, /* h */
    0x10, /* i */
    0x0C, /* j */
    0x75, /* k */
    0x30, /* l */
    0x14, /* m */
    0x54, /* n */
    0x5C, /* o */
    0x73, /* p */
    0x67, /* q */
    0x50, /* r */
    0x6D, /* s */
    0x78, /* t */
    0x1C, /* u */
    0x1C, /* v */
    0x14, /* w */
    0x76, /* x */
    0x6E, /* y */
    0x5B, /* z */
    0x46, /* { */
    0x30, /* | */
    0x70, /* } */
    0x01, /* ~ */
};

/**
 * @brief UT-S 7-SEG B 2 hexadecimal numeric matrix data.
 * @details This repository contains hexadecimal numeric matrix data array.
 */
static const uint8_t uts7segb2_hex_num_matrix[ 16 ] =
{
//-------------------
//   Hex   Symbol    
//-------------------
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
    0x77, /* A */
    0x7C, /* B */
    0x39, /* C */
    0x5E, /* D */
    0x79, /* E */
    0x71  /* F */
};

/**
 * @brief UT-S 7-SEG B 2 get character function.
 * @details This function returns the position 
 * from the ASCII table of the desired character.
 */
static uint8_t dev_get_character ( uint8_t character );

void uts7segb2_cfg_setup ( uts7segb2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->cs2  = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t uts7segb2_init ( uts7segb2_t *ctx, uts7segb2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->cs2, cfg->cs2 );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return SPI_MASTER_SUCCESS;
}

err_t uts7segb2_default_cfg ( uts7segb2_t *ctx ) 
{
    uts7segb2_set_outputs_on( ctx );
    
    err_t err_flag = uts7segb2_set_led_output( ctx, UTS7SEGB2_SEG_TOP, 
                                                    UTS7SEGB2_SEG_ALL, 
                                                    UTS7SEGB2_BRIGHTNESS_MIN );
    err_flag |= uts7segb2_set_led_output( ctx, UTS7SEGB2_SEG_BOTTOM, 
                                               UTS7SEGB2_SEG_ALL, 
                                               UTS7SEGB2_BRIGHTNESS_MIN );
    return err_flag;
}

err_t uts7segb2_top_seg_write ( uts7segb2_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t uts7segb2_top_seg_read ( uts7segb2_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t uts7segb2_bottom_seg_write ( uts7segb2_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    digital_out_low( &ctx->cs2 );
    err_t err_flag = spi_master_write( &ctx->spi, data_in, len );
    digital_out_high( &ctx->cs2 );
    return err_flag;
}

err_t uts7segb2_bottom_seg_read ( uts7segb2_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    digital_out_low( &ctx->cs2 );
    err_t err_flag = spi_master_read( &ctx->spi, data_out, len );
    digital_out_high( &ctx->cs2 );
    return err_flag;
}

void uts7segb2_set_outputs_on ( uts7segb2_t *ctx ) 
{
    digital_out_low( &ctx->pwm );
}

void uts7segb2_set_outputs_off ( uts7segb2_t *ctx ) 
{
    digital_out_high( &ctx->pwm );
}

err_t uts7segb2_set_seg_pos ( uts7segb2_t *ctx, uts7segb2_seg_sel_t seg_sel, 
                              uint8_t seg_num, uint16_t brightness ) 
{
    err_t err_flag = UTS7SEGB2_ERROR;
    uint8_t data_buf[ 36 ] = { 0 };
    uint8_t dummy_buf[ 36 ] = { 0 };
    if ( ( UTS7SEGB2_SEG_NUM_POS > seg_num ) && ( UTS7SEGB2_BRIGHTNESS_MAX >= brightness ) )
    {
        if ( seg_num % 2 )
        {
            seg_num /= 2;
            seg_num *= 3;
            data_buf[ 35 - seg_num ] = ( uint8_t ) brightness;
            data_buf[ 34 - seg_num ] = ( uint8_t ) ( brightness >> 8 );
        }
        else
        {
            seg_num--;
            seg_num /= 2;
            seg_num *= 3;
            data_buf[ 34 - seg_num ] = ( uint8_t ) ( ( brightness >> 4 ) & UTS7SEGB2_NIBBLE_HIGH );
            data_buf[ 33 - seg_num ] = ( uint8_t ) brightness;
        }
        
        if ( UTS7SEGB2_SEG_TOP == seg_sel )
        {
            err_flag = uts7segb2_top_seg_write( ctx, data_buf, 36 );
            err_flag = uts7segb2_bottom_seg_write( ctx, dummy_buf, 36 );
        }
        else
        {
            err_flag = uts7segb2_top_seg_write( ctx, dummy_buf, 36 );
            err_flag = uts7segb2_bottom_seg_write( ctx, data_buf, 36 );
        }
    }
    return err_flag;
}

err_t uts7segb2_set_led_output ( uts7segb2_t *ctx, uts7segb2_seg_sel_t seg_sel, 
                                 uint32_t seg_bit_mask, uint16_t brightness ) 
{
    err_t err_flag = UTS7SEGB2_ERROR;
    uint8_t data_buf[ 36 ] = { 0 };
    uint8_t seg_pos = UTS7SEGB2_SEG_NUM_START;
    if ( UTS7SEGB2_BRIGHTNESS_MAX >= brightness )
    {
        for ( uint8_t n_cnt = 0; n_cnt < 36; n_cnt += 3 )
        {
            if ( seg_bit_mask & ( UTS7SEGB2_SEG_DIS36_SEG7 >> seg_pos ) )
            {
                data_buf[ n_cnt ] |= ( uint8_t ) ( ( brightness >> 4 ) & UTS7SEGB2_BYTE_LOW );
                data_buf[ n_cnt + 1 ] |= ( uint8_t ) ( ( brightness & UTS7SEGB2_NIBBLE_LOW ) << 4 );
                data_buf[ n_cnt + 2 ] |= DUMMY;
            } 
            if ( seg_bit_mask & ( UTS7SEGB2_SEG_DIS36_SEG6 >> seg_pos ) )
            {
                data_buf[ n_cnt ] |= DUMMY;
                data_buf[ n_cnt + 1 ] |= ( uint8_t ) ( ( brightness >> 8 ) & UTS7SEGB2_NIBBLE_LOW );
                data_buf[ n_cnt + 2 ] |= ( uint8_t ) brightness;
            }
            seg_pos += 2;
        }
        
        if ( UTS7SEGB2_SEG_TOP == seg_sel )
        {
            err_flag = uts7segb2_top_seg_write( ctx, data_buf, 36 );
        }
        else
        {
            err_flag = uts7segb2_bottom_seg_write( ctx, data_buf, 36 );
        }
    }
    return err_flag;
}

err_t uts7segb2_display_character ( uts7segb2_t *ctx, uts7segb2_character_cfg_t ascii_char ) 
{
    err_t err_flag = UTS7SEGB2_ERROR;
    if ( UTS7SEGB2_BRIGHTNESS_MAX >= ascii_char.brightness )
    {
        uint32_t tmp_buf = DUMMY;
        tmp_buf = ( uint32_t ) dev_get_character( ascii_char.char_top_right );
        tmp_buf <<= 8;
        tmp_buf |= ( uint32_t ) dev_get_character( ascii_char.char_top_mid );
        tmp_buf <<= 8;
        tmp_buf |= ( uint32_t ) dev_get_character( ascii_char.char_top_left );
        err_flag = uts7segb2_set_led_output( ctx, UTS7SEGB2_SEG_TOP, tmp_buf, ascii_char.brightness );
        
        tmp_buf = ( uint32_t ) dev_get_character( ascii_char.char_bottom_left );
        tmp_buf <<= 8;
        tmp_buf |= ( uint32_t ) dev_get_character( ascii_char.char_bottom_mid );
        tmp_buf <<= 8;
        tmp_buf |= ( uint32_t ) dev_get_character( ascii_char.char_bottom_right );
        err_flag |= uts7segb2_set_led_output( ctx, UTS7SEGB2_SEG_BOTTOM, tmp_buf, ascii_char.brightness );
    }
    return err_flag;
}

err_t uts7segb2_display_number ( uts7segb2_t *ctx, uts7segb2_number_cfg_t number ) 
{
    err_t err_flag = UTS7SEGB2_ERROR;
    uint32_t tmp_buf = DUMMY;
    if ( ( number.brightness_top <= UTS7SEGB2_BRIGHTNESS_MAX ) && 
         ( number.brightness_bottom <= UTS7SEGB2_BRIGHTNESS_MAX ) && 
         ( number.num_top < number.base * number.base * number.base ) && 
         ( number.num_bottom < number.base * number.base * number.base ) )
    {
        tmp_buf = uts7segb2_hex_num_matrix[ number.num_top % number.base ];
        tmp_buf |= ( number.dot_bit_mask & 0x01 ) << 7;
        tmp_buf <<= 8;
        tmp_buf |= uts7segb2_hex_num_matrix[ ( number.num_top / number.base ) % number.base ];
        tmp_buf |= ( number.dot_bit_mask & 0x02 ) << 6;
        tmp_buf <<= 8;
        tmp_buf |= uts7segb2_hex_num_matrix[ number.num_top / ( number.base * number.base ) ];
        tmp_buf |= ( number.dot_bit_mask & 0x04 ) << 5;
        err_flag = uts7segb2_set_led_output( ctx, UTS7SEGB2_SEG_TOP, tmp_buf, number.brightness_top );
        
        tmp_buf = uts7segb2_hex_num_matrix[ number.num_bottom / ( number.base * number.base ) ];
        tmp_buf |= ( number.dot_bit_mask & 0x08 ) << 4;
        tmp_buf <<= 8;
        tmp_buf |= uts7segb2_hex_num_matrix[ ( number.num_bottom / number.base ) % number.base ];
        tmp_buf |= ( number.dot_bit_mask & 0x10 ) << 3;
        tmp_buf <<= 8;
        tmp_buf |= uts7segb2_hex_num_matrix[ number.num_bottom % number.base ];
        tmp_buf |= ( number.dot_bit_mask & 0x20 ) << 2;
        err_flag = uts7segb2_set_led_output( ctx, UTS7SEGB2_SEG_BOTTOM, tmp_buf, number.brightness_bottom );
    }
    return err_flag;
}

static uint8_t dev_get_character ( uint8_t character ) 
{
    if ( ( ' ' <= character ) && ( '~' >= character ) ) 
    {
        return uts7segb2_ascii_table[ character - ' ' ];
    } 
    else 
    {
        return UTS7SEGB2_ERROR;
    }
}

// ------------------------------------------------------------------------- END
