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

#include "pwm2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0
#define PWM2_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static pwm_channel_t pwm2_click_channels[ 48 ];
static uint8_t frame_buffer[ 72 ];
static uint8_t command_buffer[ 8 ] = { 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70 };
static uint8_t initialized = 0;


void pwm2_cfg_setup ( pwm2_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
	cfg->dev_pwm_freq = 5000;
}

PWM2_RETVAL pwm2_init ( pwm2_t *ctx, pwm2_cfg_t *cfg )
{   
    spi_master_config_t spi_cfg;
    pwm_config_t pwm_cfg;
    
    spi_master_configure_default( &spi_cfg );
    pwm_configure_default( &pwm_cfg );

    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = PWM2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return PWM2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, PWM2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    return PWM2_OK;
}

void pwm2_generic_transfer ( pwm2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );      
}

static void pwm2_spi_write ( pwm2_t *ctx,uint8_t *data_buf, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );    
}

void pwm2_set_duty_cycle ( pwm2_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void pwm2_pwm_stop ( pwm2_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void pwm2_pwm_start ( pwm2_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

void pwm2_toggle_phase_shift ( pwm2_t *ctx )
{
    //command 0110_xxx
    send_pulse( ctx );

    spi_master_write( &ctx->spi, &command_buffer[ 6 ], 1 );

    send_async_update_frame( ctx );
}

uint8_t pwm2_set_channel ( pwm2_t *ctx, uint8_t n_channel, uint16_t width, uint8_t correction )
{
    if ( n_channel < 1 | n_channel > 48 )
    {
        return 1;
    }
    n_channel = 49 - n_channel; //the channels are stored MOST SIGNIFICANT channel first
    pwm2_click_channels[ n_channel-1 ].width = width;
    pwm2_click_channels[ n_channel-1 ].correction = correction;
    
    if ( initialized )
    {
        send_async_update_frame( ctx );
        send_output_enable_frame( ctx );
        Delay_1ms();
    }
    return 0;
}

void pwm2_inits ( pwm2_t *ctx )
{
    send_reset_pulse( ctx );
    set_parameters( ctx );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void send_reset_pulse ( pwm2_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_deselect_device( ctx->chip_select );
    Delay_50us( ) ;
    Delay_22us( );
    spi_master_select_device( ctx->chip_select );
}

static void send_pulse ( pwm2_t *ctx )
{
    spi_master_deselect_device( ctx->chip_select );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    spi_master_select_device( ctx->chip_select );

}

static void send_frame_buffer ( pwm2_t *ctx )
{
    uint8_t i = 0;
   
    for(i = 0; i < 72; i++){

    spi_master_write( &ctx->spi, &frame_buffer[ i ], 1 );

    }
}

static void send_async_update_frame ( pwm2_t *ctx )
{
    //command 0001_xxxx
    uint8_t frame_counter = 0;
    uint8_t i = 0;
    uint16_t lsbs = 0;
    uint16_t msbs = 0;
  
    for( i = 0; i < 48; i++ )
    {
        if( ( frame_counter != 0 ) && ( ( frame_counter % 3 ) != 0 ) )
        {
             lsbs |= ( pwm2_click_channels[ i ].width & 0x0F00 ) >> 8;
             frame_buffer[ frame_counter ] = lsbs;
             frame_counter++;
             lsbs = 0;
             msbs = pwm2_click_channels[ i ].width & 0x00FF;
             frame_buffer[ frame_counter ] = msbs;
             frame_counter++;
        }
        else
        {
             msbs = pwm2_click_channels[ i ].width & 0x0FF0;
             frame_buffer[ frame_counter ] = msbs >> 4;
             frame_counter++;
             lsbs = ( pwm2_click_channels[ i ].width & 0x000F ) << 4;
        }
    }
    send_pulse( ctx );
    send_frame_buffer( ctx );

    spi_master_write( &ctx->spi, &command_buffer[ 1 ], 1 );

}

static void send_correction_frame ( pwm2_t *ctx )
{
    //command 0010_xxxx
    uint8_t frame_counter = 0;
    uint8_t i = 0;
    uint8_t send = 0;
    for(i = 0; i < 48; i++)
    {
        if( ( frame_counter != 0) && ( ( frame_counter % 3 ) != 0))
        {
            send = pwm2_click_channels[ i ].correction & 0x3C;
            frame_buffer[ frame_counter ] = ( send >> 2 ) | 0xF0; //setting all the remaining bits to 1
            frame_counter++;
            send = pwm2_click_channels[ i ].correction & 0x03;
            frame_buffer[ frame_counter ] = ( send << 6 ) | 0x3F;
            frame_counter++;
        }
        else
        {
            send = pwm2_click_channels[ i ].correction & 0x3F;
            frame_buffer[ frame_counter ] = ( send << 2 ) | 0x03;
            frame_counter++;
        }
    }
    send_pulse( ctx );
    send_frame_buffer( ctx );

    spi_master_write( &ctx->spi, &command_buffer[ 2 ], 1 );
}

static void send_output_enable_frame ( pwm2_t *ctx )
{
    //command 0011_xxxx
    send_pulse( ctx );

    spi_master_write( &ctx->spi, &command_buffer[ 3 ], 1 );
}

static void send_correction_toggle_frame ( pwm2_t *ctx )
{
    send_pulse( ctx );

    spi_master_write( &ctx->spi, &command_buffer[ 7 ], 1 );
}

static void set_parameters ( pwm2_t *ctx )
{
    send_correction_frame( ctx );
    send_async_update_frame( ctx );
    send_output_enable_frame( ctx );
    send_correction_toggle_frame( ctx );
    send_async_update_frame( ctx );
    send_output_enable_frame( ctx );
    initialized = 1;
}
// ------------------------------------------------------------------------- END

