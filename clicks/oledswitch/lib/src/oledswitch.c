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

#include "oledswitch.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OLEDSWITCH_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void oledswitch_cfg_setup ( oledswitch_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->cd = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

OLEDSWITCH_RETVAL oledswitch_init ( oledswitch_t *ctx, oledswitch_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = OLEDSWITCH_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return OLEDSWITCH_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, OLEDSWITCH_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cd, cfg->cd );

    spi_master_deselect_device( ctx->chip_select );   

    return OLEDSWITCH_OK;
}

void oledswitch_default_cfg ( oledswitch_t *ctx, uint8_t buffer_size )
{
    uint8_t row_range[ 2 ] = { 0 };
    uint8_t column_range[ 2 ] = { 0 };

    ctx->contrast.a = 0x0F;
    ctx->contrast.b = 0x0E;
    ctx->contrast.c = 0x1B;

    if ( buffer_size == OLEDSWITCH_BUFFER_SIZE_SMALL )
    {
        ctx->coordinate.column_start = 0x10;
        ctx->coordinate.column_end = 0x4F;
        ctx->coordinate.row_start = 0x00;
        ctx->coordinate.row_end = 0x2F;

        row_range[ 0 ] = 0x00;
        row_range[ 1 ] = 0x2F;
        column_range[ 0 ] = 0x10;
        column_range[ 1 ] = 0x4F;
    }
    else if ( buffer_size == OLEDSWITCH_BUFFER_SIZE_BIG )
    {
        ctx->coordinate.column_start = 0x00;
        ctx->coordinate.column_end = 0x5F;
        ctx->coordinate.row_start = 0x00;
        ctx->coordinate.row_end = 0x3F;

        row_range[ 0 ] = 0x00;
        row_range[ 1 ] = 0x3F;
        column_range[ 0 ] = 0x00;
        column_range[ 1 ] = 0x5F;
    }

    ctx->scroll.column_horizontal_shift = 0x01;
    ctx->scroll.row_horizontal_shift = 0x40;
    ctx->scroll.row_vertical_shift = 0x05;
    ctx->scroll.row_offset = 0x00;
    ctx->scroll.interval = 0x00;

    oledswitch_software_reset( ctx );
    
    oledswitch_set_contrast( ctx );
    oledswitch_set_master_current( ctx );
    oledswitch_set_remap_color_depth( ctx );
    oledswitch_set_display_start_line( ctx );
    oledswitch_set_display_offset( ctx );
    oledswitch_set_normal_display( ctx );
    oledswitch_set_multiplex_ratio( ctx );
    oledswitch_set_dim_mode( ctx );
    oledswitch_enable_linear_gray_scale( ctx );
    oledswitch_display_normal_mode( ctx );

    oledswitch_set_master_config( ctx );
    oledswitch_set_power_save_mode( ctx );
    oledswitch_set_phase_period_adjustment( ctx );
    oledswitch_display_clock_divider_oscillator_frequency( ctx );
    oledswitch_pre_charge_level( ctx );
    oledswitch_set_vcomh( ctx );
    
    oledswitch_set_row_range( ctx, row_range[ 0 ], row_range[ 1 ] );
    oledswitch_set_column_range( ctx, column_range[ 0 ], column_range[ 1 ] );
    oledswitch_clear_window( ctx );

    oledswitch_deactivate_scrolling( ctx );
    oledswitch_demo_scrolling_setup( ctx );

    Delay_1sec( );
}

void oledswitch_draw_image ( oledswitch_t *ctx, uint8_t *image_buf, uint16_t image_size )
{
    uint16_t cnt;

    oledswitch_digital_write_pwm( ctx, 1 );

    spi_master_select_device( ctx->chip_select );
    Delay_10ms( );

    for ( cnt = 0; cnt < image_size; cnt++ )
    {
        spi_master_write( &ctx->spi, &image_buf[ cnt ], 1 );
        Delay_100us(  ); 
    }

    spi_master_deselect_device( ctx->chip_select );
}


void oledswitch_demo_scrolling_setup ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 6 ];

    write_buf[ 0 ] = OLEDSWITCH_SCROLLING_SETUP;
    write_buf[ 1 ] = ctx->scroll.column_horizontal_shift;
    write_buf[ 2 ] = ctx->scroll.row_horizontal_shift;
    write_buf[ 3 ] = ctx->scroll.row_vertical_shift;
    write_buf[ 4 ] = ctx->scroll.row_offset;
    write_buf[ 5 ] = ctx->scroll.interval;

    oledswitch_reg_write( ctx, write_buf, 6 ); 
}

void oledswitch_deactivate_scrolling ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_DEACTIVATE_SCROLLING;
    write_buf[ 1 ] = 0x00;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_clear_window ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 5 ];

    write_buf[ 0 ] = OLEDSWITCH_CLEAR_WINDOW;
    write_buf[ 1 ] = ctx->coordinate.column_start;
    write_buf[ 2 ] = ctx->coordinate.row_start;
    write_buf[ 3 ] = ctx->coordinate.column_end;
    write_buf[ 4 ] = ctx->coordinate.row_end;    

    oledswitch_reg_write( ctx, write_buf, 5 );
}

void oledswitch_set_column_range ( oledswitch_t *ctx, uint8_t start, uint8_t end )
{
    uint8_t write_buf[ 3 ];

    write_buf[ 0 ] = OLEDSWITCH_COLUMN_RANGE;
    write_buf[ 1 ] = start;
    write_buf[ 2 ] = end;

    oledswitch_reg_write( ctx, write_buf, 3 );
}

void oledswitch_set_row_range ( oledswitch_t *ctx, uint8_t start, uint8_t end )
{
    uint8_t write_buf[ 3 ];

    write_buf[ 0 ] = OLEDSWITCH_ROW_RANGE;
    write_buf[ 1 ] = start;
    write_buf[ 2 ] = end;

    oledswitch_reg_write( ctx, write_buf, 3 );
}

void oledswitch_display_normal_mode ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 1 ];

    write_buf[ 0 ] = OLEDSWITCH_DISPLAY_ON_IN_NORMAL_MODE;

    oledswitch_reg_write( ctx, &write_buf[ 0 ], 1 );
}

void oledswitch_set_vcomh ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_30_SET_VCOMH_1;
    write_buf[ 1 ] = OLEDSWITCH_30_SET_VCOMH_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_pre_charge_level ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_PRE_CHARGE_LEVEL_1;
    write_buf[ 1 ] = OLEDSWITCH_PRE_CHARGE_LEVEL_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_enable_linear_gray_scale ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 1 ];

    write_buf[ 0 ] = OLEDSWITCH_ENABLE_LINEAR_GRAY_SCALE;

    oledswitch_reg_write( ctx, &write_buf[ 0 ], 1 );
}

void oledswitch_display_clock_divider_oscillator_frequency ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_DISPLAY_CLOCK_DIVIDER_OSCILLATOR_FREQUENCY_1;
    write_buf[ 1 ] = OLEDSWITCH_DISPLAY_CLOCK_DIVIDER_OSCILLATOR_FREQUENCY_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_phase_period_adjustment ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_PHASE_1_AND_2_PERIOD_ADJUSTMENT_1;
    write_buf[ 1 ] = OLEDSWITCH_PHASE_1_AND_2_PERIOD_ADJUSTMENT_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_power_save_mode ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_POWER_SAVE_MODE_1;
    write_buf[ 1 ] = OLEDSWITCH_POWER_SAVE_MODE_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_master_config ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_MASTER_CONFIGURATION_1;
    write_buf[ 1 ] = OLEDSWITCH_MASTER_CONFIGURATION_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_dim_mode ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 6 ] = {

        OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_1,
        OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_2,
        OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_3,
        OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_4,
        OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_5,
        OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_6
    };
    oledswitch_reg_write( ctx, write_buf, 6 );
}

void oledswitch_set_multiplex_ratio ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];
    write_buf[ 0 ] = OLEDSWITCH_MULTIPLEX_RATIO_1;
    write_buf[ 1 ] = OLEDSWITCH_MULTIPLEX_RATIO_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_normal_display ( oledswitch_t *ctx )
{   
    uint8_t write_buf[ 1 ];

    write_buf[ 0 ] = OLEDSWITCH_NORMAL_DISPLAY;

    oledswitch_reg_write( ctx, &write_buf[ 0 ], 1 );
}

void oledswitch_set_display_offset ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_SET_DISPLAY_OFFSET_1;
    write_buf[ 1 ] = OLEDSWITCH_SET_DISPLAY_OFFSET_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_display_start_line ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_SET_DISPLAY_START_LINE_1;
    write_buf[ 1 ] = OLEDSWITCH_SET_DISPLAY_START_LINE_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_remap_color_depth ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_REMAP_AND_COLOR_DEPTH_SETTING_1;
    write_buf[ 1 ] = OLEDSWITCH_REMAP_AND_COLOR_DEPTH_SETTING_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_master_current ( oledswitch_t *ctx ) 
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_MASTER_CURRENT_CONTROL_1;
    write_buf[ 1 ] = OLEDSWITCH_MASTER_CURRENT_CONTROL_2;

    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_set_contrast ( oledswitch_t *ctx )
{
    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = OLEDSWITCH_FILL_ENABLE_DISABLE;
    write_buf[ 1 ] = ctx->contrast.a;
    oledswitch_reg_write( ctx, write_buf, 2 );

    write_buf[ 1 ] = ctx->contrast.b;
    oledswitch_reg_write( ctx, write_buf, 2 );

    write_buf[ 1 ] = ctx->contrast.c;
    oledswitch_reg_write( ctx, write_buf, 2 );
}

void oledswitch_software_reset ( oledswitch_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_5ms( );
    digital_out_high( &ctx->rst );
}

void oledswitch_digital_write_pwm ( oledswitch_t *ctx, uint8_t signal )
{
    digital_out_write( &ctx->cd, signal );
}

void oledswitch_digital_write_rst ( oledswitch_t *ctx, uint8_t signal )
{
    digital_out_write( &ctx->rst, signal );
}

void oledswitch_reg_write ( oledswitch_t *ctx, uint8_t *data_buf, uint8_t len )
{
    uint8_t cnt;

    oledswitch_digital_write_pwm( ctx, 0 );

    spi_master_select_device( ctx->chip_select );
    Delay_10ms( );

    for ( cnt = 0; cnt < len; cnt++ )
    {
        spi_master_write( &ctx->spi, &data_buf[ cnt ], 1 ); 
    }

    spi_master_deselect_device( ctx->chip_select );    
}
// ------------------------------------------------------------------------- END

