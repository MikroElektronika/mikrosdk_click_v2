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
 * @file hbridge12.c
 * @brief H-Bridge 12 Click Driver.
 */

#include "hbridge12.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void hbridge12_cfg_setup ( hbridge12_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->slp = HAL_PIN_NC;
    cfg->stb = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
}

err_t hbridge12_init ( hbridge12_t *ctx, hbridge12_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->slp, cfg->slp );
    digital_out_init( &ctx->stb, cfg->stb );

    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->slp );
    digital_out_low( &ctx->stb );

    return SPI_MASTER_SUCCESS;
}

err_t hbridge12_default_cfg ( hbridge12_t *ctx ) 
{
    err_t error_flag = HBRIDGE12_OK;
    
    ctx->ab_config_data.addr = HBRIDGE12_ADDR_AB;
    ctx->cd_config_data.addr = HBRIDGE12_ADDR_CD;
    
    hbridge12_set_rst( ctx, HBRIDGE12_PIN_STATE_HIGH );
    hbridge12_set_slp( ctx, HBRIDGE12_PIN_STATE_HIGH );
    
    hbridge12_set_current_scale( ctx, HBRIDGE12_AB_BRIDGE_SEL, HBRIDGE12_CURRENT_SCALE_100_PER, 
                                 HBRIDGE12_CURRENT_SCALE_100_PER );
    hbridge12_set_current_scale( ctx, HBRIDGE12_CD_BRIDGE_SEL, HBRIDGE12_CURRENT_SCALE_100_PER, 
                                 HBRIDGE12_CURRENT_SCALE_100_PER );
    
    hbridge12_set_decay ( ctx, HBRIDGE12_AB_BRIDGE_SEL, 0, 0 );
    hbridge12_set_decay ( ctx, HBRIDGE12_CD_BRIDGE_SEL, 0, 0 );
    
    error_flag = hbridge12_freewheeling_on( ctx, HBRIDGE12_AB_BRIDGE_SEL );
    
    return error_flag;
}

void hbridge12_set_rst ( hbridge12_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE12_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void hbridge12_set_slp ( hbridge12_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE12_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->slp );
    }
    else
    {
        digital_out_low( &ctx->slp );
    }
}

void hbridge12_set_strobe ( hbridge12_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE12_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->stb );
    }
    else
    {
        digital_out_low( &ctx->stb );
    }
}

void hbridge12_generate_strobe ( hbridge12_t *ctx )
{
    digital_out_high( &ctx->stb );
    Delay_1ms( );
    digital_out_low( &ctx->stb );
}

void hbridge12_get_settings ( hbridge12_t *ctx, uint8_t channel_sel, hbridge12_config_t *config_data )
{
    if ( HBRIDGE12_AB_BRIDGE_SEL == channel_sel )
    {
        config_data->addr = ctx->ab_config_data.addr;
        config_data->ch1_cur_scale = ctx->ab_config_data.ch1_cur_scale;
        config_data->ch1_decay = ctx->ab_config_data.ch1_decay;
        config_data->ch1_en = ctx->ab_config_data.ch1_en;
        config_data->ch1_phase = ctx->ab_config_data.ch1_phase;
        config_data->ch2_cur_scale = ctx->ab_config_data.ch2_cur_scale;
        config_data->ch2_decay = ctx->ab_config_data.ch2_decay;
        config_data->ch2_en = ctx->ab_config_data.ch2_en;
        config_data->ch2_phase = ctx->ab_config_data.ch2_phase;
    }
    else
    {
        config_data->addr = ctx->cd_config_data.addr;
        config_data->ch1_cur_scale = ctx->cd_config_data.ch1_cur_scale;
        config_data->ch1_decay = ctx->cd_config_data.ch1_decay;
        config_data->ch1_en = ctx->cd_config_data.ch1_en;
        config_data->ch1_phase = ctx->cd_config_data.ch1_phase;
        config_data->ch2_cur_scale = ctx->cd_config_data.ch2_cur_scale;
        config_data->ch2_decay = ctx->cd_config_data.ch2_decay;
        config_data->ch2_en = ctx->cd_config_data.ch2_en;
        config_data->ch2_phase = ctx->cd_config_data.ch2_phase;
    }
}

void hbridge12_set_settings ( hbridge12_t *ctx, uint8_t channel_sel, hbridge12_config_t config_data )
{
    if ( HBRIDGE12_AB_BRIDGE_SEL == channel_sel )
    {
        ctx->ab_config_data.addr = config_data.addr;
        ctx->ab_config_data.ch1_cur_scale = config_data.ch1_cur_scale;
        ctx->ab_config_data.ch1_decay = config_data.ch1_decay;
        ctx->ab_config_data.ch1_en = config_data.ch1_en;
        ctx->ab_config_data.ch1_phase = config_data.ch1_phase;
        ctx->ab_config_data.ch2_cur_scale = config_data.ch2_cur_scale;
        ctx->ab_config_data.ch2_decay = config_data.ch2_decay;
        ctx->ab_config_data.ch2_en = config_data.ch2_en;
        ctx->ab_config_data.ch2_phase = config_data.ch2_phase;
    }
    else
    {
        ctx->cd_config_data.addr = config_data.addr;
        ctx->cd_config_data.ch1_cur_scale = config_data.ch1_cur_scale;
        ctx->cd_config_data.ch1_decay = config_data.ch1_decay;
        ctx->cd_config_data.ch1_en = config_data.ch1_en;
        ctx->cd_config_data.ch1_phase = config_data.ch1_phase;
        ctx->cd_config_data.ch2_cur_scale = config_data.ch2_cur_scale;
        ctx->cd_config_data.ch2_decay = config_data.ch2_decay;
        ctx->cd_config_data.ch2_en = config_data.ch2_en;
        ctx->cd_config_data.ch2_phase = config_data.ch2_phase;
    }
}

err_t hbridge12_write_config ( hbridge12_t *ctx, hbridge12_config_t config_data )
{
    uint8_t tx_data[ 2 ] = { 0 };
    
    tx_data[ 0 ] = config_data.ch2_phase | ( config_data.ch2_en << 1 ) 
                | ( config_data.ch1_decay << 2 ) | ( config_data.ch1_cur_scale << 3 ) 
                | ( config_data.ch1_phase << 6 ) | ( config_data.ch1_en << 7 );
    tx_data[ 1 ] = ( config_data.addr << 3 ) | ( config_data.ch2_decay << 4 ) 
                | ( config_data.ch2_cur_scale << 5 );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_data, 2 );
    spi_master_deselect_device( ctx->chip_select );
    hbridge12_generate_strobe( ctx );
    
    return error_flag;
}

void hbridge12_set_current_scale ( hbridge12_t *ctx, uint8_t channel_sel, uint8_t out1_curr_scale, 
                                   uint8_t out2_curr_scale )
{
    if ( HBRIDGE12_AB_BRIDGE_SEL == channel_sel )
    {
        ctx->ab_config_data.ch1_cur_scale = out1_curr_scale;
        ctx->ab_config_data.ch2_cur_scale = out2_curr_scale;
    }
    else
    {
        ctx->cd_config_data.ch1_cur_scale = out1_curr_scale;
        ctx->cd_config_data.ch2_cur_scale = out2_curr_scale;
    }
}

void hbridge12_set_decay ( hbridge12_t *ctx, uint8_t channel_sel, uint8_t out1_decay, 
                                   uint8_t out2_decay )
{
    if ( HBRIDGE12_AB_BRIDGE_SEL == channel_sel )
    {
        ctx->ab_config_data.ch1_decay = out1_decay;
        ctx->ab_config_data.ch2_decay = out2_decay;
    }
    else
    {
        ctx->cd_config_data.ch1_decay = out1_decay;
        ctx->cd_config_data.ch2_decay = out2_decay;
    }
}

err_t hbridge12_turn_clockwise ( hbridge12_t *ctx, uint8_t channel_sel )
{
    err_t error_flag = HBRIDGE12_OK;
    
    if ( HBRIDGE12_AB_BRIDGE_SEL == channel_sel )
    {
        ctx->ab_config_data.ch1_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->ab_config_data.ch1_phase = HBRIDGE12_PHASE_OUT1_H_OUT2_L;
        ctx->ab_config_data.ch2_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->ab_config_data.ch2_phase = HBRIDGE12_PHASE_OUT1_L_OUT2_H;
        error_flag = hbridge12_write_config( ctx, ctx->ab_config_data );
    }
    else
    {
        ctx->cd_config_data.ch1_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->cd_config_data.ch1_phase = HBRIDGE12_PHASE_OUT1_H_OUT2_L;
        ctx->cd_config_data.ch2_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->cd_config_data.ch2_phase = HBRIDGE12_PHASE_OUT1_L_OUT2_H;
        error_flag = hbridge12_write_config( ctx, ctx->cd_config_data );
    }
    
    return error_flag;
}

err_t hbridge12_turn_counterclockwise ( hbridge12_t *ctx, uint8_t channel_sel )
{
    err_t error_flag = HBRIDGE12_OK;
    
    if ( HBRIDGE12_AB_BRIDGE_SEL == channel_sel )
    {
        ctx->ab_config_data.ch1_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->ab_config_data.ch1_phase = HBRIDGE12_PHASE_OUT1_L_OUT2_H;
        ctx->ab_config_data.ch2_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->ab_config_data.ch2_phase = HBRIDGE12_PHASE_OUT1_H_OUT2_L;
        error_flag = hbridge12_write_config( ctx, ctx->ab_config_data );
    }
    else
    {
        ctx->cd_config_data.ch1_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->cd_config_data.ch1_phase = HBRIDGE12_PHASE_OUT1_L_OUT2_H;
        ctx->cd_config_data.ch2_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->cd_config_data.ch2_phase = HBRIDGE12_PHASE_OUT1_H_OUT2_L;
        error_flag = hbridge12_write_config( ctx, ctx->cd_config_data );
    }

    return error_flag;
}

err_t hbridge12_turn_brake_on ( hbridge12_t *ctx, uint8_t channel_sel )
{
    err_t error_flag = HBRIDGE12_OK;
    
    if ( HBRIDGE12_AB_BRIDGE_SEL == channel_sel )
    {
        ctx->ab_config_data.ch1_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->ab_config_data.ch1_phase = HBRIDGE12_PHASE_OUT1_H_OUT2_L;
        ctx->ab_config_data.ch2_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->ab_config_data.ch2_phase = HBRIDGE12_PHASE_OUT1_H_OUT2_L;
        error_flag = hbridge12_write_config( ctx, ctx->ab_config_data );
    }
    else
    {
        ctx->cd_config_data.ch1_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->cd_config_data.ch1_phase = HBRIDGE12_PHASE_OUT1_H_OUT2_L;
        ctx->cd_config_data.ch2_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->cd_config_data.ch2_phase = HBRIDGE12_PHASE_OUT1_H_OUT2_L;
        error_flag = hbridge12_write_config( ctx, ctx->cd_config_data );
    }

    return error_flag;
}

err_t hbridge12_freewheeling_on ( hbridge12_t *ctx, uint8_t channel_sel )
{
    err_t error_flag = HBRIDGE12_OK;
    
    if ( HBRIDGE12_AB_BRIDGE_SEL == channel_sel )
    {
        ctx->ab_config_data.ch1_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->ab_config_data.ch1_phase = HBRIDGE12_PHASE_OUT1_L_OUT2_H;
        ctx->ab_config_data.ch2_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->ab_config_data.ch2_phase = HBRIDGE12_PHASE_OUT1_L_OUT2_H;
        error_flag = hbridge12_write_config( ctx, ctx->ab_config_data );
    }
    else
    {
        ctx->cd_config_data.ch1_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->cd_config_data.ch1_phase = HBRIDGE12_PHASE_OUT1_L_OUT2_H;
        ctx->cd_config_data.ch2_en = HBRIDGE12_ENABLE_BRIDGE_OUTPUT;
        ctx->cd_config_data.ch2_phase = HBRIDGE12_PHASE_OUT1_L_OUT2_H;
        error_flag = hbridge12_write_config( ctx, ctx->cd_config_data );
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
