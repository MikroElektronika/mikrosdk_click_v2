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
 * @file ipsdisplay.c
 * @brief IPS Display Click Driver.
 */

#include "ipsdisplay.h"
#include "ipsdisplay_resources.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void ipsdisplay_cfg_setup ( ipsdisplay_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->dc   = HAL_PIN_NC;

    cfg->spi_speed   = 5000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
}

err_t ipsdisplay_init ( ipsdisplay_t *ctx, ipsdisplay_cfg_t *cfg ) 
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
    digital_out_high ( &ctx->cs );

    return SPI_MASTER_SUCCESS;
}

err_t ipsdisplay_default_cfg ( ipsdisplay_t *ctx ) 
{
    err_t error_flag = IPSDISPLAY_OK;
    uint8_t data_buf[ 14 ] = { 0 };

    ipsdisplay_enter_data_mode( ctx );
    ipsdisplay_reset_device ( ctx );

    error_flag |= ipsdisplay_set_rotation ( ctx, IPSDISPLAY_ROTATION_VERTICAL_0 );
    ipsdisplay_set_font ( ctx, IPSDISPLAY_FONT_8X16 );

    data_buf[ 0 ] = IPSDISPLAY_COLMOD_CTRL_16BIT_PIXEL;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_COLMOD, data_buf, 1 );
    
    data_buf[ 0 ] = IPSDISPLAY_PORCTRL_0_BPA_DEFAULT;
    data_buf[ 1 ] = IPSDISPLAY_PORCTRL_1_FPA_DEFAULT;
    data_buf[ 2 ] = IPSDISPLAY_PORCTRL_2_PSEN_DISABLE;
    data_buf[ 3 ] = IPSDISPLAY_PORCTRL_3_BPB_DEFAULT | IPSDISPLAY_PORCTRL_3_FPB_DEFAULT;
    data_buf[ 4 ] = IPSDISPLAY_PORCTRL_4_BPC_DEFAULT | IPSDISPLAY_PORCTRL_4_FPC_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_PORCTRL, data_buf, 5 );
    
    data_buf[ 0 ] = IPSDISPLAY_GCTRL_VGHS_DEFAULT | IPSDISPLAY_GCTRL_VGLS_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_GCTRL, data_buf, 1 );
    
    data_buf[ 0 ] = IPSDISPLAY_VCOMS_VCOM_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_VCOMS, data_buf, 1 );
    
    data_buf[ 0 ] = IPSDISPLAY_LCMCTRL_XBGR | IPSDISPLAY_LCMCTRL_XMX | IPSDISPLAY_LCMCTRL_XMH;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_LCMCTRL, data_buf, 1 );
    
    data_buf[ 0 ] = IPSDISPLAY_VDVVRHEN_CMDEN_ENABLE;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_VDVVRHEN, data_buf, 1 );
    
    data_buf[ 0 ] = IPSDISPLAY_VRHS_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_VRHS, data_buf, 1 );
    
    data_buf[ 0 ] = IPSDISPLAY_VDVSET_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_VDVSET, data_buf, 1 );
    
    data_buf[ 0 ] = IPSDISPLAY_FRCTR2_NLA_DEFAULT | IPSDISPLAY_FRCTR2_RTNA_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_FRCTR2, data_buf, 1 );
    
    data_buf[ 0 ] = IPSDISPLAY_PWCTRL1_0_DEFAULT;
    data_buf[ 1 ] = IPSDISPLAY_PWCTRL1_1_AVDD_DEFAULT | IPSDISPLAY_PWCTRL1_1_AVCL_DEFAULT | 
                    IPSDISPLAY_PWCTRL1_1_VDS_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_PWCTRL1, data_buf, 2 );
    
    data_buf[ 0 ] = IPSDISPLAY_PVGAMCTRL_0_V63P_DEFAULT | IPSDISPLAY_PVGAMCTRL_0_V0P_DEFAULT;
    data_buf[ 1 ] = IPSDISPLAY_PVGAMCTRL_1_V1P_DEFAULT;
    data_buf[ 2 ] = IPSDISPLAY_PVGAMCTRL_2_V2P_DEFAULT;
    data_buf[ 3 ] = IPSDISPLAY_PVGAMCTRL_3_V4P_DEFAULT;
    data_buf[ 4 ] = IPSDISPLAY_PVGAMCTRL_4_V6P_DEFAULT;
    data_buf[ 5 ] = IPSDISPLAY_PVGAMCTRL_5_J0P_DEFAULT | IPSDISPLAY_PVGAMCTRL_5_J13P_DEFAULT;
    data_buf[ 6 ] = IPSDISPLAY_PVGAMCTRL_6_V20P_DEFAULT;
    data_buf[ 7 ] = IPSDISPLAY_PVGAMCTRL_7_V36P_DEFAULT | IPSDISPLAY_PVGAMCTRL_7_V27P_DEFAULT;
    data_buf[ 8 ] = IPSDISPLAY_PVGAMCTRL_8_V43P_DEFAULT;
    data_buf[ 9 ] = IPSDISPLAY_PVGAMCTRL_9_J1P_DEFAULT | IPSDISPLAY_PVGAMCTRL_9_V50P_DEFAULT;
    data_buf[ 10 ] = IPSDISPLAY_PVGAMCTRL_10_V57P_DEFAULT;
    data_buf[ 11 ] = IPSDISPLAY_PVGAMCTRL_11_V59P_DEFAULT;
    data_buf[ 12 ] = IPSDISPLAY_PVGAMCTRL_12_V61P_DEFAULT;
    data_buf[ 13 ] = IPSDISPLAY_PVGAMCTRL_13_V62P_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_PVGAMCTRL, data_buf, 14 );
    
    data_buf[ 0 ] = IPSDISPLAY_NVGAMCTRL_0_V63N_DEFAULT | IPSDISPLAY_NVGAMCTRL_0_V0N_DEFAULT;
    data_buf[ 1 ] = IPSDISPLAY_NVGAMCTRL_1_V1N_DEFAULT;
    data_buf[ 2 ] = IPSDISPLAY_NVGAMCTRL_2_V2N_DEFAULT;
    data_buf[ 3 ] = IPSDISPLAY_NVGAMCTRL_3_V4N_DEFAULT;
    data_buf[ 4 ] = IPSDISPLAY_NVGAMCTRL_4_V6N_DEFAULT;
    data_buf[ 5 ] = IPSDISPLAY_NVGAMCTRL_5_J0N_DEFAULT | IPSDISPLAY_NVGAMCTRL_5_J13N_DEFAULT;
    data_buf[ 6 ] = IPSDISPLAY_NVGAMCTRL_6_V20N_DEFAULT;
    data_buf[ 7 ] = IPSDISPLAY_NVGAMCTRL_7_V36N_DEFAULT | IPSDISPLAY_NVGAMCTRL_7_V27N_DEFAULT;
    data_buf[ 8 ] = IPSDISPLAY_NVGAMCTRL_8_V43N_DEFAULT;
    data_buf[ 9 ] = IPSDISPLAY_NVGAMCTRL_9_J1N_DEFAULT | IPSDISPLAY_NVGAMCTRL_9_V50N_DEFAULT;
    data_buf[ 10 ] = IPSDISPLAY_NVGAMCTRL_10_V57N_DEFAULT;
    data_buf[ 11 ] = IPSDISPLAY_NVGAMCTRL_11_V59N_DEFAULT;
    data_buf[ 12 ] = IPSDISPLAY_NVGAMCTRL_12_V61N_DEFAULT;
    data_buf[ 13 ] = IPSDISPLAY_NVGAMCTRL_13_V62N_DEFAULT;
    error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_NVGAMCTRL, data_buf, 14 );
    
    error_flag |= ipsdisplay_write_cmd ( ctx, IPSDISPLAY_CMD_INVON );
    
    error_flag |= ipsdisplay_write_cmd ( ctx, IPSDISPLAY_CMD_SLPOUT );
    Delay_100ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    error_flag |= ipsdisplay_fill_screen ( ctx, IPSDISPLAY_COLOR_BLACK );
    error_flag |= ipsdisplay_write_cmd ( ctx, IPSDISPLAY_CMD_DISPON );
    Delay_100ms ( );
    return error_flag;
}

err_t ipsdisplay_write_cmd ( ipsdisplay_t *ctx, uint8_t cmd )
{
    err_t error_flag = IPSDISPLAY_OK;
    digital_out_low ( &ctx->cs );
    ipsdisplay_enter_cmd_mode( ctx );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    digital_out_high ( &ctx->cs );
    return error_flag;
}

err_t ipsdisplay_write_cmd_par ( ipsdisplay_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = IPSDISPLAY_OK;
    error_flag |= ipsdisplay_write_cmd( ctx, cmd );
    for ( uint8_t cnt = 0; ( cnt < len ) && ( NULL != data_in ); cnt++ )
    {
        digital_out_low ( &ctx->cs );
        ipsdisplay_enter_data_mode( ctx );
        error_flag |= spi_master_write( &ctx->spi, &data_in[ cnt ], 1 );
        digital_out_high ( &ctx->cs );
    }
    return error_flag;
}

err_t ipsdisplay_write_data ( ipsdisplay_t *ctx, uint16_t *data_in, uint16_t len )
{
    err_t error_flag = IPSDISPLAY_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    digital_out_low ( &ctx->cs );
    ipsdisplay_enter_data_mode( ctx );
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( data_in[ cnt ] >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( data_in[ cnt ] & 0xFF );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    }
    digital_out_high ( &ctx->cs );
    return error_flag;
}

void ipsdisplay_disable_device ( ipsdisplay_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void ipsdisplay_enable_device ( ipsdisplay_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void ipsdisplay_reset_device ( ipsdisplay_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    Delay_100ms ( );
}

void ipsdisplay_enter_cmd_mode ( ipsdisplay_t *ctx )
{
    digital_out_low ( &ctx->dc );
}

void ipsdisplay_enter_data_mode ( ipsdisplay_t *ctx )
{
    digital_out_high ( &ctx->dc );
}

err_t ipsdisplay_set_rotation ( ipsdisplay_t *ctx, uint8_t rotation )
{
    uint8_t cmd_param = IPSDISPLAY_MADCTL_DEFAULT;
    ctx->rotation = rotation;
    if ( IPSDISPLAY_ROTATION_VERTICAL_180 == rotation )
    {
        cmd_param = IPSDISPLAY_MADCTL_MY | IPSDISPLAY_MADCTL_MX;
    }
    else if ( IPSDISPLAY_ROTATION_HORIZONTAL_0 == rotation )
    {
        cmd_param = IPSDISPLAY_MADCTL_MX | IPSDISPLAY_MADCTL_MV;
    }
    else if ( IPSDISPLAY_ROTATION_HORIZONTAL_180 == rotation )
    {
        cmd_param = IPSDISPLAY_MADCTL_MY | IPSDISPLAY_MADCTL_MV;
    }
    else
    {
        ctx->rotation = IPSDISPLAY_ROTATION_VERTICAL_0;
    }
    return ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_MADCTL, &cmd_param, 1 );
}

void ipsdisplay_set_font ( ipsdisplay_t *ctx, uint8_t font_sel )
{
    switch ( font_sel )
    {
    #ifdef IPSDISPLAY_FONT_6X12
        case IPSDISPLAY_FONT_6X12:
        {
            ctx->font.font_buf = ipsdisplay_font_6x12;
            ctx->font.width = 6;
            ctx->font.height = 12;
            break;
        }
    #endif
    #ifdef IPSDISPLAY_FONT_8X16
        case IPSDISPLAY_FONT_8X16:
        {
            ctx->font.font_buf = ipsdisplay_font_8x16;
            ctx->font.width = 8;
            ctx->font.height = 16;
            break;
        }
    #endif
    #ifdef IPSDISPLAY_FONT_12X24
        case IPSDISPLAY_FONT_12X24:
        {
            ctx->font.font_buf = ipsdisplay_font_12x24;
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

err_t ipsdisplay_set_pos ( ipsdisplay_t *ctx, ipsdisplay_point_t start_pt, ipsdisplay_point_t end_pt )
{
    err_t error_flag = IPSDISPLAY_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t x_offset = 0;
    uint8_t y_offset = 0;
    if ( ( IPSDISPLAY_ROTATION_VERTICAL_0 == ctx->rotation ) || 
         ( IPSDISPLAY_ROTATION_VERTICAL_180 == ctx->rotation ) )
    {
        if ( ( start_pt.x > end_pt.x ) || ( start_pt.y > end_pt.y ) || 
             ( end_pt.x > IPSDISPLAY_POS_WIDTH_MAX ) || ( end_pt.y > IPSDISPLAY_POS_HEIGHT_MAX ) )
        {
            error_flag = IPSDISPLAY_ERROR;
        }
    }
    else
    {
        if ( ( start_pt.x > end_pt.x ) || ( start_pt.y > end_pt.y ) || 
             ( end_pt.x > IPSDISPLAY_POS_HEIGHT_MAX ) || ( end_pt.y > IPSDISPLAY_POS_WIDTH_MAX ) )
        {
            error_flag = IPSDISPLAY_ERROR;
        }
    }
    if ( IPSDISPLAY_OK == error_flag )
    {
        if ( IPSDISPLAY_ROTATION_VERTICAL_0 == ctx->rotation )
        {
            x_offset = IPSDISPLAY_POS_OFFSET_LEFT;
            y_offset = IPSDISPLAY_POS_OFFSET_UP;
        }
        else if ( IPSDISPLAY_ROTATION_VERTICAL_180 == ctx->rotation )
        {
            x_offset = IPSDISPLAY_POS_OFFSET_RIGHT;
            y_offset = IPSDISPLAY_POS_OFFSET_DOWN;
        }
        else if ( IPSDISPLAY_ROTATION_HORIZONTAL_0 == ctx->rotation )
        {
            x_offset = IPSDISPLAY_POS_OFFSET_UP;
            y_offset = IPSDISPLAY_POS_OFFSET_RIGHT;
        }
        else
        {
            x_offset = IPSDISPLAY_POS_OFFSET_DOWN;
            y_offset = IPSDISPLAY_POS_OFFSET_LEFT;
        }
        data_buf[ 0 ] = ( uint8_t ) ( ( ( start_pt.x + x_offset ) >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( start_pt.x + x_offset ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( ( end_pt.x + x_offset ) >> 8 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( ( end_pt.x + x_offset ) & 0xFF );
        error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_CASET, data_buf, 4 );
        data_buf[ 0 ] = ( uint8_t ) ( ( ( start_pt.y + y_offset ) >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( start_pt.y + y_offset ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( ( end_pt.y + y_offset ) >> 8 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( ( end_pt.y + y_offset ) & 0xFF );
        error_flag |= ipsdisplay_write_cmd_par ( ctx, IPSDISPLAY_CMD_RASET, data_buf, 4 );
        error_flag |= ipsdisplay_write_cmd ( ctx, IPSDISPLAY_CMD_RAMWR );
    }
    return error_flag;
}

err_t ipsdisplay_fill_screen ( ipsdisplay_t *ctx, uint16_t color )
{
    err_t error_flag = IPSDISPLAY_OK;
    ipsdisplay_point_t start_pt, end_pt;
    start_pt.x = IPSDISPLAY_POS_HEIGHT_MIN;
    start_pt.y = IPSDISPLAY_POS_WIDTH_MIN;
    end_pt.x = IPSDISPLAY_POS_HEIGHT_MAX;
    end_pt.y = IPSDISPLAY_POS_WIDTH_MAX;
    if ( ( IPSDISPLAY_ROTATION_VERTICAL_0 == ctx->rotation ) || 
         ( IPSDISPLAY_ROTATION_VERTICAL_180 == ctx->rotation ) )
    {
        start_pt.x = IPSDISPLAY_POS_WIDTH_MIN;
        start_pt.y = IPSDISPLAY_POS_HEIGHT_MIN;
        end_pt.x = IPSDISPLAY_POS_WIDTH_MAX;
        end_pt.y = IPSDISPLAY_POS_HEIGHT_MAX;
    }
    error_flag |= ipsdisplay_set_pos ( ctx, start_pt, end_pt );
    for ( uint16_t cnt = 0; cnt < IPSDISPLAY_NUM_PIXELS; cnt++ )
    {
        error_flag |= ipsdisplay_write_data ( ctx, &color, 1 );
    }
    return error_flag;
}

err_t ipsdisplay_write_char ( ipsdisplay_t *ctx, ipsdisplay_point_t start_pt, uint8_t data_in, uint16_t color )
{
    err_t error_flag = IPSDISPLAY_OK;
    ipsdisplay_point_t point;
    uint16_t font_pos = ( data_in - IPSDISPLAY_FONT_ASCII_OFFSET ) * ctx->font.height * ( ( ( ctx->font.width - 1 ) / 8 ) + 1 );
    uint8_t h_cnt = 0;
    uint8_t w_cnt = 0;
    for ( h_cnt = 0; h_cnt < ctx->font.height; h_cnt++ )
    {
        for ( w_cnt = 0; w_cnt < ctx->font.width; w_cnt++ )
        {
            if ( ctx->font.font_buf[ font_pos + ( w_cnt / 8 ) ] & ( IPSDISPLAY_FONT_WIDTH_MSB >> ( w_cnt % 8 ) ) )
            {
                point.x = start_pt.x + w_cnt;
                point.y = start_pt.y + h_cnt;
                error_flag |= ipsdisplay_draw_pixel ( ctx, point, color );
            }
        }
        font_pos = font_pos + ( ( w_cnt - 1 ) / 8 ) + 1;
    }
    return error_flag;
}

err_t ipsdisplay_write_string ( ipsdisplay_t *ctx, ipsdisplay_point_t start_pt, uint8_t *data_in, uint16_t color )
{
    err_t error_flag = IPSDISPLAY_OK;
    ipsdisplay_point_t point;
    point.x = start_pt.x;
    point.y = start_pt.y;
    for ( uint16_t char_cnt = 0; char_cnt < strlen ( ( char * ) data_in ); char_cnt++ )
    {
        if ( ( IPSDISPLAY_ROTATION_VERTICAL_0 == ctx->rotation ) || 
             ( IPSDISPLAY_ROTATION_VERTICAL_180 == ctx->rotation ) )
        {
            if ( point.x > ( IPSDISPLAY_POS_WIDTH_MAX - ctx->font.width ) )
            {
                point.x = IPSDISPLAY_POS_WIDTH_MIN;
                point.y += ctx->font.height;
            }
            if ( point.y > ( IPSDISPLAY_POS_HEIGHT_MAX - ctx->font.height ) )
            {
                point.y = IPSDISPLAY_POS_HEIGHT_MIN;
            }
        }
        else
        {
            if ( point.x > ( IPSDISPLAY_POS_HEIGHT_MAX - ctx->font.width ) )
            {
                point.x = IPSDISPLAY_POS_HEIGHT_MIN;
                point.y += ctx->font.height;
            }
            if ( point.y > ( IPSDISPLAY_POS_WIDTH_MAX - ctx->font.height ) )
            {
                point.y = IPSDISPLAY_POS_WIDTH_MIN;
            }
        }
        error_flag |= ipsdisplay_write_char ( ctx, point, data_in[ char_cnt ], color );
        point.x += ( ctx->font.width + IPSDISPLAY_FONT_TEXT_SPACE );
    }
    return error_flag;
}

err_t ipsdisplay_draw_pixel ( ipsdisplay_t *ctx, ipsdisplay_point_t start_pt, uint16_t color )
{
    err_t error_flag = IPSDISPLAY_OK;
    error_flag |= ipsdisplay_set_pos ( ctx, start_pt, start_pt );
    if ( IPSDISPLAY_OK == error_flag )
    {
        error_flag |= ipsdisplay_write_data ( ctx, &color, 1 );
    }
    return error_flag;
}

err_t ipsdisplay_draw_line ( ipsdisplay_t *ctx, ipsdisplay_point_t start_pt, 
                             ipsdisplay_point_t end_pt, uint16_t color )
{
    err_t error_flag = IPSDISPLAY_OK;
    int16_t x_err = 0;
    int16_t y_err = 0;
    int16_t delta_x = end_pt.x - start_pt.x;
    int16_t delta_y = end_pt.y - start_pt.y;
    int16_t distance = 0;
    int16_t incx = 0;
    int16_t incy = 0;
    ipsdisplay_point_t point;
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
        error_flag |= ipsdisplay_draw_pixel ( ctx, point, color );
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

err_t ipsdisplay_draw_rectangle ( ipsdisplay_t *ctx, ipsdisplay_point_t start_pt, 
                                  ipsdisplay_point_t end_pt, uint16_t color )
{
    err_t error_flag = IPSDISPLAY_OK;
    ipsdisplay_point_t pt1, pt2;
    pt1.x = start_pt.x;
    pt1.y = start_pt.y;
    pt2.x = end_pt.x;
    pt2.y = start_pt.y;
    error_flag |= ipsdisplay_draw_line ( ctx, pt1, pt2, color );
    pt1.x = start_pt.x;
    pt1.y = start_pt.y;
    pt2.x = start_pt.x;
    pt2.y = end_pt.y;
    error_flag |= ipsdisplay_draw_line ( ctx, pt1, pt2, color );
    pt1.x = start_pt.x;
    pt1.y = end_pt.y;
    pt2.x = end_pt.x;
    pt2.y = end_pt.y;
    error_flag |= ipsdisplay_draw_line ( ctx, pt1, pt2, color );
    pt1.x = end_pt.x;
    pt1.y = start_pt.y;
    pt2.x = end_pt.x;
    pt2.y = end_pt.y;
    error_flag |= ipsdisplay_draw_line ( ctx, pt1, pt2, color );
    return error_flag;
}

err_t ipsdisplay_draw_circle ( ipsdisplay_t *ctx, ipsdisplay_point_t center_pt, uint8_t radius, uint16_t color )
{
    err_t error_flag = IPSDISPLAY_OK;
    ipsdisplay_point_t pt0;
    int16_t a_val = 0;
    int16_t b_val = radius;
    while ( a_val <= b_val )
    {
        pt0.x = center_pt.x + a_val;
        pt0.y = center_pt.y + b_val;
        error_flag |= ipsdisplay_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x - a_val;
        pt0.y = center_pt.y + b_val;
        error_flag |= ipsdisplay_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x + a_val;
        pt0.y = center_pt.y - b_val;
        error_flag |= ipsdisplay_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x - a_val;
        pt0.y = center_pt.y - b_val;
        error_flag |= ipsdisplay_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x + b_val;
        pt0.y = center_pt.y + a_val;
        error_flag |= ipsdisplay_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x - b_val;
        pt0.y = center_pt.y + a_val;
        error_flag |= ipsdisplay_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x + b_val;
        pt0.y = center_pt.y - a_val;
        error_flag |= ipsdisplay_draw_pixel ( ctx, pt0, color );
        pt0.x = center_pt.x - b_val;
        pt0.y = center_pt.y - a_val;
        error_flag |= ipsdisplay_draw_pixel ( ctx, pt0, color );
        a_val++;
        if ( ( a_val * a_val + b_val * b_val ) > ( radius * radius ) )
        {
            b_val--;
        }
    }
    return error_flag;
}

err_t ipsdisplay_draw_picture ( ipsdisplay_t *ctx, uint8_t rotation, const uint16_t *image )
{
    err_t error_flag = IPSDISPLAY_OK;
    ipsdisplay_point_t start_pt, end_pt;
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t old_rotation = ctx->rotation;
    error_flag |= ipsdisplay_set_rotation ( ctx, rotation );
    start_pt.x = IPSDISPLAY_POS_HEIGHT_MIN;
    start_pt.y = IPSDISPLAY_POS_WIDTH_MIN;
    end_pt.x = IPSDISPLAY_POS_HEIGHT_MAX;
    end_pt.y = IPSDISPLAY_POS_WIDTH_MAX;
    if ( ( IPSDISPLAY_ROTATION_VERTICAL_0 == ctx->rotation ) || 
         ( IPSDISPLAY_ROTATION_VERTICAL_180 == ctx->rotation ) )
    {
        start_pt.x = IPSDISPLAY_POS_WIDTH_MIN;
        start_pt.y = IPSDISPLAY_POS_HEIGHT_MIN;
        end_pt.x = IPSDISPLAY_POS_WIDTH_MAX;
        end_pt.y = IPSDISPLAY_POS_HEIGHT_MAX;
    }
    error_flag |= ipsdisplay_set_pos ( ctx, start_pt, end_pt );
    digital_out_low ( &ctx->cs );
    ipsdisplay_enter_data_mode( ctx );
    for ( uint16_t cnt = 0; cnt < IPSDISPLAY_NUM_PIXELS; cnt++ )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( image[ cnt ] >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( image[ cnt ] & 0xFF );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    }
    digital_out_high ( &ctx->cs );
    error_flag |= ipsdisplay_set_rotation ( ctx, old_rotation );
    return error_flag;
}

// ------------------------------------------------------------------------- END
