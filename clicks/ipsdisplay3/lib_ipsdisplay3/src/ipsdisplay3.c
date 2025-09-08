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
 * @file ipsdisplay3.c
 * @brief IPS Display 3 Click Driver.
 */

#include "ipsdisplay3.h"
#include "ipsdisplay3_resources.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void ipsdisplay3_cfg_setup ( ipsdisplay3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->dc   = HAL_PIN_NC;
    cfg->bck  = HAL_PIN_NC;

    cfg->spi_speed = 5000000;
    cfg->spi_mode  = SPI_MASTER_MODE_0;
}

err_t ipsdisplay3_init ( ipsdisplay3_t *ctx, ipsdisplay3_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

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

    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dc, cfg->dc );
    digital_out_init( &ctx->bck, cfg->bck );
    digital_out_high ( &ctx->cs );

    return SPI_MASTER_SUCCESS;
}

err_t ipsdisplay3_default_cfg ( ipsdisplay3_t *ctx ) 
{
    err_t error_flag = IPSDISPLAY3_OK;
    uint8_t data_buf[ 14 ] = { 0 };

    ipsdisplay3_enter_data_mode( ctx );
    ipsdisplay3_reset_device ( ctx );
    
    error_flag |= ipsdisplay3_write_cmd ( ctx, IPSDISPLAY3_CMD_IREGEN1 );
    error_flag |= ipsdisplay3_write_cmd ( ctx, IPSDISPLAY3_CMD_IREGEN2 );
    
    data_buf[ 0 ] = IPSDISPLAY3_B0_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_B0, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_B1_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_B1, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_B2_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_B2, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_B3_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_B3, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_B7_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_B7, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_B6_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_B6, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_CPRRGB565_EPF_DEFAULT | IPSDISPLAY3_CPRRGB565_RESERVED;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_CPRRGB565, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_AB_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_AB, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_COLMOD_CTRL_16BIT_PIXEL;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_COLMOD, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_INVCTRL_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_INVCTRL, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_FRS_RTN1_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_FRS, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_B8_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_B8, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_VREGCTL_AD_DEFAULT_4637_MV;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_VREGCTL, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_VGHSET_D2A_13V | IPSDISPLAY3_VGHSET_RESERVED;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_VGHSET, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_VGLSET_D2A_MIN_13V | IPSDISPLAY3_VGLSET_RESERVED;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_VGLSET, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_VGHVGLCLK_VGH_CLK_DIV_12 | IPSDISPLAY3_VGHVGLCLK_VGL_CLK_DIV_12;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_VGHVGLCLK, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_C6_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_C6, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_C7_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_C7, data_buf, 1 );

    data_buf[ 0 ] = IPSDISPLAY3_SETGAMMA0_0_VR2N_DEFAULT;
    data_buf[ 1 ] = IPSDISPLAY3_SETGAMMA0_1_VR20N_DEFAULT;
    data_buf[ 2 ] = IPSDISPLAY3_SETGAMMA0_2_VR36N_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA0_2_VR27N_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA0_2_RESERVED;
    data_buf[ 3 ] = IPSDISPLAY3_SETGAMMA0_3_VR43N_DEFAULT;
    data_buf[ 4 ] = IPSDISPLAY3_SETGAMMA0_4_VR50N_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA0_4_VR13N_DEFAULT;
    data_buf[ 5 ] = IPSDISPLAY3_SETGAMMA0_5_VR61N_DEFAULT;
    data_buf[ 6 ] = IPSDISPLAY3_SETGAMMA0_6_VR62N_DEFAULT;
    data_buf[ 7 ] = IPSDISPLAY3_SETGAMMA0_7_J0N_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA0_7_J1N_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA0_7_VR0N_DEFAULT;
    data_buf[ 8 ] = IPSDISPLAY3_SETGAMMA0_8_VR1N_DEFAULT;
    data_buf[ 9 ] = IPSDISPLAY3_SETGAMMA0_9_VR4N_DEFAULT;
    data_buf[ 10 ] = IPSDISPLAY3_SETGAMMA0_10_VR6N_DEFAULT;
    data_buf[ 11 ] = IPSDISPLAY3_SETGAMMA0_11_VR57N_DEFAULT;
    data_buf[ 12 ] = IPSDISPLAY3_SETGAMMA0_12_VR59N_DEFAULT;
    data_buf[ 13 ] = IPSDISPLAY3_SETGAMMA0_13_VR63N_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_SETGAMMA0, data_buf, 14 );

    data_buf[ 0 ] = IPSDISPLAY3_SETGAMMA1_0_VR2P_DEFAULT;
    data_buf[ 1 ] = IPSDISPLAY3_SETGAMMA1_1_VR20P_DEFAULT;
    data_buf[ 2 ] = IPSDISPLAY3_SETGAMMA1_2_VR36P_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA1_2_VR27P_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA1_2_RESERVED;
    data_buf[ 3 ] = IPSDISPLAY3_SETGAMMA1_3_VR43P_DEFAULT;
    data_buf[ 4 ] = IPSDISPLAY3_SETGAMMA1_4_VR50P_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA1_4_VR13P_DEFAULT;
    data_buf[ 5 ] = IPSDISPLAY3_SETGAMMA1_5_VR61P_DEFAULT;
    data_buf[ 6 ] = IPSDISPLAY3_SETGAMMA1_6_VR62P_DEFAULT;
    data_buf[ 7 ] = IPSDISPLAY3_SETGAMMA1_7_J0P_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA1_7_J1P_DEFAULT | 
                    IPSDISPLAY3_SETGAMMA1_7_VR0P_DEFAULT;
    data_buf[ 8 ] = IPSDISPLAY3_SETGAMMA1_8_VR1P_DEFAULT;
    data_buf[ 9 ] = IPSDISPLAY3_SETGAMMA1_9_VR4P_DEFAULT;
    data_buf[ 10 ] = IPSDISPLAY3_SETGAMMA1_10_VR6P_DEFAULT;
    data_buf[ 11 ] = IPSDISPLAY3_SETGAMMA1_11_VR57P_DEFAULT;
    data_buf[ 12 ] = IPSDISPLAY3_SETGAMMA1_12_VR59P_DEFAULT;
    data_buf[ 13 ] = IPSDISPLAY3_SETGAMMA1_13_VR63P_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_SETGAMMA1, data_buf, 14 );

    data_buf[ 0 ] = IPSDISPLAY3_MADCTL_DEFAULT;
    error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_MADCTL, data_buf, 1 );

    error_flag |= ipsdisplay3_write_cmd ( ctx, IPSDISPLAY3_CMD_SLPOUT );
    Delay_100ms ( );
    Delay_10ms ( );
    Delay_10ms ( );

    error_flag |= ipsdisplay3_set_rotation ( ctx, IPSDISPLAY3_ROTATION_VERTICAL_0 );
    ipsdisplay3_set_font ( ctx, IPSDISPLAY3_FONT_8X16 );
    
    error_flag |= ipsdisplay3_write_cmd ( ctx, IPSDISPLAY3_CMD_INVOFF );

    error_flag |= ipsdisplay3_fill_screen ( ctx, IPSDISPLAY3_COLOR_BLACK );
    error_flag |= ipsdisplay3_write_cmd ( ctx, IPSDISPLAY3_CMD_DISPON );
    Delay_100ms ( );
    ipsdisplay3_enable_backlight ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t ipsdisplay3_write_cmd ( ipsdisplay3_t *ctx, uint8_t cmd )
{
    err_t error_flag = IPSDISPLAY3_OK;
    digital_out_low ( &ctx->cs );
    ipsdisplay3_enter_cmd_mode( ctx );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    digital_out_high ( &ctx->cs );
    return error_flag;
}

err_t ipsdisplay3_write_cmd_par ( ipsdisplay3_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = IPSDISPLAY3_OK;
    error_flag |= ipsdisplay3_write_cmd( ctx, cmd );
    for ( uint8_t cnt = 0; ( cnt < len ) && ( NULL != data_in ); cnt++ )
    {
        digital_out_low ( &ctx->cs );
        ipsdisplay3_enter_data_mode( ctx );
        error_flag |= spi_master_write( &ctx->spi, &data_in[ cnt ], 1 );
        digital_out_high ( &ctx->cs );
    }
    return error_flag;
}

err_t ipsdisplay3_write_data ( ipsdisplay3_t *ctx, uint16_t *data_in, uint16_t len )
{
    err_t error_flag = IPSDISPLAY3_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    digital_out_low ( &ctx->cs );
    ipsdisplay3_enter_data_mode( ctx );
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( data_in[ cnt ] >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( data_in[ cnt ] & 0xFF );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    }
    digital_out_high ( &ctx->cs );
    return error_flag;
}

void ipsdisplay3_disable_device ( ipsdisplay3_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void ipsdisplay3_enable_device ( ipsdisplay3_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void ipsdisplay3_reset_device ( ipsdisplay3_t *ctx )
{
    Delay_10ms ( );
    digital_out_low ( &ctx->rst );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
}

void ipsdisplay3_disable_backlight ( ipsdisplay3_t *ctx )
{
    digital_out_low ( &ctx->bck );
}

void ipsdisplay3_enable_backlight ( ipsdisplay3_t *ctx )
{
    digital_out_high ( &ctx->bck );
}

void ipsdisplay3_enter_cmd_mode ( ipsdisplay3_t *ctx )
{
    digital_out_low ( &ctx->dc );
}

void ipsdisplay3_enter_data_mode ( ipsdisplay3_t *ctx )
{
    digital_out_high ( &ctx->dc );
}

err_t ipsdisplay3_set_rotation ( ipsdisplay3_t *ctx, uint8_t rotation )
{
    uint8_t cmd_param = IPSDISPLAY3_MADCTL_DEFAULT;
    ctx->rotation = rotation;
    if ( IPSDISPLAY3_ROTATION_VERTICAL_180 == rotation )
    {
        cmd_param = IPSDISPLAY3_MADCTL_MY | IPSDISPLAY3_MADCTL_MX;
        ctx->center.x = ( IPSDISPLAY3_POS_WIDTH_MAX / 2 + 1 ) - IPSDISPLAY3_POS_OFFSET_LEFT;
        ctx->center.y = ( IPSDISPLAY3_POS_WIDTH_MAX / 2 + 1 ) - IPSDISPLAY3_POS_OFFSET_UP;
    }
    else if ( IPSDISPLAY3_ROTATION_HORIZONTAL_0 == rotation )
    {
        cmd_param = IPSDISPLAY3_MADCTL_MX | IPSDISPLAY3_MADCTL_MV;
        ctx->center.x = ( IPSDISPLAY3_POS_WIDTH_MAX / 2 + 1 ) - IPSDISPLAY3_POS_OFFSET_DOWN;
        ctx->center.y = ( IPSDISPLAY3_POS_WIDTH_MAX / 2 + 1 ) - IPSDISPLAY3_POS_OFFSET_LEFT;
    }
    else if ( IPSDISPLAY3_ROTATION_HORIZONTAL_180 == rotation )
    {
        cmd_param = IPSDISPLAY3_MADCTL_MY | IPSDISPLAY3_MADCTL_MV;
        ctx->center.x = ( IPSDISPLAY3_POS_WIDTH_MAX / 2 + 1 ) - IPSDISPLAY3_POS_OFFSET_UP;
        ctx->center.y = ( IPSDISPLAY3_POS_WIDTH_MAX / 2 + 1 ) - IPSDISPLAY3_POS_OFFSET_RIGHT;
    }
    else
    {
        ctx->rotation = IPSDISPLAY3_ROTATION_VERTICAL_0;
        ctx->center.x = ( IPSDISPLAY3_POS_WIDTH_MAX / 2 + 1 ) - IPSDISPLAY3_POS_OFFSET_RIGHT;
        ctx->center.y = ( IPSDISPLAY3_POS_WIDTH_MAX / 2 + 1 ) - IPSDISPLAY3_POS_OFFSET_DOWN;
    }
    return ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_MADCTL, &cmd_param, 1 );
}

void ipsdisplay3_set_font ( ipsdisplay3_t *ctx, uint8_t font_sel )
{
    switch ( font_sel )
    {
    #ifdef IPSDISPLAY3_FONT_6X12
        case IPSDISPLAY3_FONT_6X12:
        {
            ctx->font.font_buf = ipsdisplay3_font_6x12;
            ctx->font.width = 6;
            ctx->font.height = 12;
            break;
        }
    #endif
    #ifdef IPSDISPLAY3_FONT_8X16
        case IPSDISPLAY3_FONT_8X16:
        {
            ctx->font.font_buf = ipsdisplay3_font_8x16;
            ctx->font.width = 8;
            ctx->font.height = 16;
            break;
        }
    #endif
    #ifdef IPSDISPLAY3_FONT_12X24
        case IPSDISPLAY3_FONT_12X24:
        {
            ctx->font.font_buf = ipsdisplay3_font_12x24;
            ctx->font.width = 12;
            ctx->font.height = 24;
            break;
        }
    #endif
        default:
        {
            break;
        }
    }
}

err_t ipsdisplay3_set_pos ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, ipsdisplay3_point_t end_pt )
{
    err_t error_flag = IPSDISPLAY3_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t x_offset = 0;
    uint8_t y_offset = 0;
    if ( ( IPSDISPLAY3_ROTATION_VERTICAL_0 == ctx->rotation ) || 
         ( IPSDISPLAY3_ROTATION_VERTICAL_180 == ctx->rotation ) )
    {
        if ( ( start_pt.x > end_pt.x ) || ( start_pt.y > end_pt.y ) || 
             ( end_pt.x > IPSDISPLAY3_POS_WIDTH_MAX ) || ( end_pt.y > IPSDISPLAY3_POS_HEIGHT_MAX ) )
        {
            error_flag = IPSDISPLAY3_ERROR;
        }
    }
    else
    {
        if ( ( start_pt.x > end_pt.x ) || ( start_pt.y > end_pt.y ) || 
             ( end_pt.x > IPSDISPLAY3_POS_HEIGHT_MAX ) || ( end_pt.y > IPSDISPLAY3_POS_WIDTH_MAX ) )
        {
            error_flag = IPSDISPLAY3_ERROR;
        }
    }
    if ( IPSDISPLAY3_OK == error_flag )
    {
        if ( IPSDISPLAY3_ROTATION_VERTICAL_0 == ctx->rotation )
        {
            x_offset = IPSDISPLAY3_POS_OFFSET_LEFT;
            y_offset = IPSDISPLAY3_POS_OFFSET_UP;
        }
        else if ( IPSDISPLAY3_ROTATION_VERTICAL_180 == ctx->rotation )
        {
            x_offset = IPSDISPLAY3_POS_OFFSET_RIGHT;
            y_offset = IPSDISPLAY3_POS_OFFSET_DOWN;
        }
        else if ( IPSDISPLAY3_ROTATION_HORIZONTAL_0 == ctx->rotation )
        {
            x_offset = IPSDISPLAY3_POS_OFFSET_UP;
            y_offset = IPSDISPLAY3_POS_OFFSET_RIGHT;
        }
        else
        {
            x_offset = IPSDISPLAY3_POS_OFFSET_DOWN;
            y_offset = IPSDISPLAY3_POS_OFFSET_LEFT;
        }
        data_buf[ 0 ] = ( uint8_t ) ( ( ( start_pt.x + x_offset ) >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( start_pt.x + x_offset ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( ( end_pt.x + x_offset ) >> 8 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( ( end_pt.x + x_offset ) & 0xFF );
        error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_CASET, data_buf, 4 );
        data_buf[ 0 ] = ( uint8_t ) ( ( ( start_pt.y + y_offset ) >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( start_pt.y + y_offset ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( ( end_pt.y + y_offset ) >> 8 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( ( end_pt.y + y_offset ) & 0xFF );
        error_flag |= ipsdisplay3_write_cmd_par ( ctx, IPSDISPLAY3_CMD_RASET, data_buf, 4 );
        error_flag |= ipsdisplay3_write_cmd ( ctx, IPSDISPLAY3_CMD_RAMWR );
    }
    return error_flag;
}

err_t ipsdisplay3_fill_screen ( ipsdisplay3_t *ctx, uint16_t color )
{
    err_t error_flag = IPSDISPLAY3_OK;
    ipsdisplay3_point_t start_pt, end_pt;
    start_pt.x = IPSDISPLAY3_POS_HEIGHT_MIN;
    start_pt.y = IPSDISPLAY3_POS_WIDTH_MIN;
    end_pt.x = IPSDISPLAY3_POS_HEIGHT_MAX;
    end_pt.y = IPSDISPLAY3_POS_WIDTH_MAX;
    if ( ( IPSDISPLAY3_ROTATION_VERTICAL_0 == ctx->rotation ) || 
         ( IPSDISPLAY3_ROTATION_VERTICAL_180 == ctx->rotation ) )
    {
        start_pt.x = IPSDISPLAY3_POS_WIDTH_MIN;
        start_pt.y = IPSDISPLAY3_POS_HEIGHT_MIN;
        end_pt.x = IPSDISPLAY3_POS_WIDTH_MAX;
        end_pt.y = IPSDISPLAY3_POS_HEIGHT_MAX;
    }
    error_flag |= ipsdisplay3_set_pos ( ctx, start_pt, end_pt );
    for ( uint16_t cnt = 0; cnt < IPSDISPLAY3_NUM_PIXELS; cnt++ )
    {
        error_flag |= ipsdisplay3_write_data ( ctx, &color, 1 );
    }
    return error_flag;
}

err_t ipsdisplay3_write_char ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, uint8_t data_in, uint16_t color )
{
    err_t error_flag = IPSDISPLAY3_OK;
    ipsdisplay3_point_t point;
    uint16_t font_pos = ( data_in - IPSDISPLAY3_FONT_ASCII_OFFSET ) * ctx->font.height * ( ( ( ctx->font.width - 1 ) / 8 ) + 1 );
    uint8_t h_cnt = 0;
    uint8_t w_cnt = 0;
    for ( h_cnt = 0; h_cnt < ctx->font.height; h_cnt++ )
    {
        for ( w_cnt = 0; w_cnt < ctx->font.width; w_cnt++ )
        {
            if ( ctx->font.font_buf[ font_pos + ( w_cnt / 8 ) ] & ( IPSDISPLAY3_FONT_WIDTH_MSB >> ( w_cnt % 8 ) ) )
            {
                point.x = start_pt.x + w_cnt;
                point.y = start_pt.y + h_cnt;
                error_flag |= ipsdisplay3_draw_pixel ( ctx, point, color );
            }
        }
        font_pos = font_pos + ( ( w_cnt - 1 ) / 8 ) + 1;
    }
    return error_flag;
}

err_t ipsdisplay3_write_string ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, uint8_t *data_in, uint16_t color )
{
    err_t error_flag = IPSDISPLAY3_OK;
    ipsdisplay3_point_t point;
    point.x = start_pt.x;
    point.y = start_pt.y;
    for ( uint16_t char_cnt = 0; char_cnt < strlen ( ( char * ) data_in ); char_cnt++ )
    {
        if ( ( IPSDISPLAY3_ROTATION_VERTICAL_0 == ctx->rotation ) || 
             ( IPSDISPLAY3_ROTATION_VERTICAL_180 == ctx->rotation ) )
        {
            if ( point.x > ( IPSDISPLAY3_POS_WIDTH_MAX - ctx->font.width ) )
            {
                point.x = IPSDISPLAY3_POS_WIDTH_MIN;
                point.y += ctx->font.height;
            }
            if ( point.y > ( IPSDISPLAY3_POS_HEIGHT_MAX - ctx->font.height ) )
            {
                point.y = IPSDISPLAY3_POS_HEIGHT_MIN;
            }
        }
        else
        {
            if ( point.x > ( IPSDISPLAY3_POS_HEIGHT_MAX - ctx->font.width ) )
            {
                point.x = IPSDISPLAY3_POS_HEIGHT_MIN;
                point.y += ctx->font.height;
            }
            if ( point.y > ( IPSDISPLAY3_POS_WIDTH_MAX - ctx->font.height ) )
            {
                point.y = IPSDISPLAY3_POS_WIDTH_MIN;
            }
        }
        error_flag |= ipsdisplay3_write_char ( ctx, point, data_in[ char_cnt ], color );
        point.x += ( ctx->font.width + IPSDISPLAY3_FONT_TEXT_SPACE );
    }
    return error_flag;
}

err_t ipsdisplay3_draw_pixel ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, uint16_t color )
{
    err_t error_flag = IPSDISPLAY3_OK;
    error_flag |= ipsdisplay3_set_pos ( ctx, start_pt, start_pt );
    if ( IPSDISPLAY3_OK == error_flag )
    {
        error_flag |= ipsdisplay3_write_data ( ctx, &color, 1 );
    }
    return error_flag;
}

err_t ipsdisplay3_draw_line ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, 
                              ipsdisplay3_point_t end_pt, uint16_t color )
{
    err_t error_flag = IPSDISPLAY3_OK;
    int16_t x_err = 0;
    int16_t y_err = 0;
    int16_t delta_x = end_pt.x - start_pt.x;
    int16_t delta_y = end_pt.y - start_pt.y;
    int16_t distance = 0;
    int16_t incx = 0;
    int16_t incy = 0;
    ipsdisplay3_point_t point;
    point.x = start_pt.x;
    point.y = start_pt.y;

    if ( delta_x > 0 ) 
    {
        incx = 1;
    } 
    else if ( delta_x < 0 )
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if ( delta_y > 0 )
    {
        incy = 1;
    }
    else if ( delta_y < 0 )
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if ( delta_x > delta_y )
    {
        distance = delta_x;
    }
    else 
    {
        distance = delta_y;
    }
    
    for ( uint16_t p_cnt = 0; p_cnt <= distance; p_cnt++ )
    {
        error_flag |= ipsdisplay3_draw_pixel ( ctx, point, color );
        x_err += delta_x;
        y_err += delta_y;
        if ( x_err > distance )
        {
            x_err -= distance;
            point.x += incx;
        }
        if ( y_err > distance )
        {
            y_err -= distance;
            point.y += incy;
        }
    }
    return error_flag;
}

err_t ipsdisplay3_draw_rectangle ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, 
                                   ipsdisplay3_point_t end_pt, uint16_t color )
{
    err_t error_flag = IPSDISPLAY3_OK;
    ipsdisplay3_point_t pt1, pt2;
    pt1.x = start_pt.x;
    pt1.y = start_pt.y;
    pt2.x = end_pt.x;
    pt2.y = start_pt.y;
    error_flag |= ipsdisplay3_draw_line ( ctx, pt1, pt2, color );
    pt1.x = start_pt.x;
    pt1.y = start_pt.y;
    pt2.x = start_pt.x;
    pt2.y = end_pt.y;
    error_flag |= ipsdisplay3_draw_line ( ctx, pt1, pt2, color );
    pt1.x = start_pt.x;
    pt1.y = end_pt.y;
    pt2.x = end_pt.x;
    pt2.y = end_pt.y;
    error_flag |= ipsdisplay3_draw_line ( ctx, pt1, pt2, color );
    pt1.x = end_pt.x;
    pt1.y = start_pt.y;
    pt2.x = end_pt.x;
    pt2.y = end_pt.y;
    error_flag |= ipsdisplay3_draw_line ( ctx, pt1, pt2, color );
    return error_flag;
}

err_t ipsdisplay3_draw_circle ( ipsdisplay3_t *ctx, ipsdisplay3_point_t center_pt, uint8_t radius, uint16_t color )
{
    err_t error_flag = IPSDISPLAY3_OK;
    ipsdisplay3_point_t pt0;
    int16_t a_val = 0;
    int16_t b_val = radius;
    while ( a_val <= b_val )
    {
        pt0.x = center_pt.x + a_val;
        pt0.y = center_pt.y + b_val;
        error_flag |= ipsdisplay3_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x - a_val;
        pt0.y = center_pt.y + b_val;
        error_flag |= ipsdisplay3_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x + a_val;
        pt0.y = center_pt.y - b_val;
        error_flag |= ipsdisplay3_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x - a_val;
        pt0.y = center_pt.y - b_val;
        error_flag |= ipsdisplay3_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x + b_val;
        pt0.y = center_pt.y + a_val;
        error_flag |= ipsdisplay3_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x - b_val;
        pt0.y = center_pt.y + a_val;
        error_flag |= ipsdisplay3_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x + b_val;
        pt0.y = center_pt.y - a_val;
        error_flag |= ipsdisplay3_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x - b_val;
        pt0.y = center_pt.y - a_val;
        error_flag |= ipsdisplay3_draw_pixel ( ctx, pt0, color );
        a_val++;
        if ( ( a_val * a_val + b_val * b_val ) > ( radius * radius ) )
        {
            b_val--;
        }
    }
    return error_flag;
}

err_t ipsdisplay3_draw_picture ( ipsdisplay3_t *ctx, uint8_t rotation, const uint16_t *image )
{
    err_t error_flag = IPSDISPLAY3_OK;
    ipsdisplay3_point_t start_pt, end_pt;
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t old_rotation = ctx->rotation;
    error_flag |= ipsdisplay3_set_rotation ( ctx, rotation );
    start_pt.x = IPSDISPLAY3_POS_HEIGHT_MIN;
    start_pt.y = IPSDISPLAY3_POS_WIDTH_MIN;
    end_pt.x = IPSDISPLAY3_POS_HEIGHT_MAX;
    end_pt.y = IPSDISPLAY3_POS_WIDTH_MAX;
    if ( ( IPSDISPLAY3_ROTATION_VERTICAL_0 == ctx->rotation ) || 
         ( IPSDISPLAY3_ROTATION_VERTICAL_180 == ctx->rotation ) )
    {
        start_pt.x = IPSDISPLAY3_POS_WIDTH_MIN;
        start_pt.y = IPSDISPLAY3_POS_HEIGHT_MIN;
        end_pt.x = IPSDISPLAY3_POS_WIDTH_MAX;
        end_pt.y = IPSDISPLAY3_POS_HEIGHT_MAX;
    }
    error_flag |= ipsdisplay3_set_pos ( ctx, start_pt, end_pt );
    digital_out_low ( &ctx->cs );
    ipsdisplay3_enter_data_mode( ctx );
    for ( uint16_t cnt = 0; cnt < IPSDISPLAY3_NUM_PIXELS; cnt++ )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( image[ cnt ] >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( image[ cnt ] & 0xFF );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    }
    digital_out_high ( &ctx->cs );
    error_flag |= ipsdisplay3_set_rotation ( ctx, old_rotation );
    return error_flag;
}

// ------------------------------------------------------------------------- END
