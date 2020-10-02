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

#include "hbridge3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR    0
#define HBRIDGE3_DUMMY     0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hbridge3_cfg_setup ( hbridge3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->sdo = HAL_PIN_NC;
    cfg->sdi = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dir = HAL_PIN_NC;
    cfg->dis = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;

	cfg->dev_pwm_freq 	  = 5000;

    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

HBRIDGE3_RETVAL hbridge3_init ( hbridge3_t *ctx, hbridge3_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    spi_master_config_t spi_cfg;
    
    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->sdo;
    spi_cfg.mosi      = cfg->sdi;
    spi_cfg.default_write_data = HBRIDGE3_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return HBRIDGE3_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, HBRIDGE3_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );  

    // Output pins 

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->dis, cfg->dis );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm_pin, cfg->pwm );

    digital_out_write( &ctx->dir, 1 );
    digital_out_write( &ctx->dis, 0 );
    digital_out_write( &ctx->cs, 1 );
    Delay_10ms( );

    return HBRIDGE3_OK;
}

void hbridge3_set_duty_cycle ( hbridge3_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void hbridge3_pwm_stop ( hbridge3_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void hbridge3_pwm_start ( hbridge3_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

void hbridge3_dir_set ( hbridge3_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->dir, pin_state );
}

void hbridge3_dis_set ( hbridge3_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->dis, pin_state );
}

void hbridge3_cs_set ( hbridge3_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->cs, pin_state );
}

void hbridge3_pwm_set ( hbridge3_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->pwm_pin, pin_state );
}

void hbridge3_generic_transfer ( hbridge3_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );     
}

uint8_t hbridge3_spi ( hbridge3_t *ctx, uint8_t spi_command )
{
    uint8_t aux_in[ 1 ];
    uint8_t aux_out[ 1 ];

    aux_in[ 0 ] = spi_command;

    Delay_10ms( );
    hbridge3_generic_transfer( ctx, aux_in, 1, aux_out, 1 );

    aux_in[ 0 ] = 0x00;
    aux_out[ 0 ] = 0x00;
    
    Delay_10ms( );
    hbridge3_generic_transfer( ctx, aux_in, 1, aux_out, 1 );

    return aux_out[ 0 ];
}

// ------------------------------------------------------------------------- END

