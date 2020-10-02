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

#include "leddriver8.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define LEDDRIVER8_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void communication_delay( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void leddriver8_cfg_setup ( leddriver8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

LEDDRIVER8_RETVAL leddriver8_init ( leddriver8_t *ctx, leddriver8_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = LEDDRIVER8_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return LEDDRIVER8_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, LEDDRIVER8_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return LEDDRIVER8_OK;
}

void leddriver8_generic_transfer 
( 
    leddriver8_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

void leddriver8_write_data ( leddriver8_t *ctx, uint8_t reg, uint8_t data_byte )
{
    uint8_t txbuf[ 2 ];

    txbuf[ 0 ] = ( reg << 1 );
    txbuf[ 1 ] = data_byte;

    leddriver8_generic_transfer( ctx, txbuf, 2, 0, 0 );
    communication_delay( );
}

uint8_t leddriver8_read_data ( leddriver8_t *ctx, uint8_t reg )
{
    uint8_t txdata;
    uint8_t rxdata;

    txdata = ( reg << 1 ) | 0x01;

    leddriver8_generic_transfer( ctx, &txdata, 1, &rxdata, 1 );
    communication_delay( );
    
    return rxdata;
}

void leddriver8_output_enable_pin ( leddriver8_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void leddriver8_reset( leddriver8_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    
    leddriver8_set_output_gain( ctx, LEDDRIVER8_OUTPUT_GAIN_ALL_LED, 
                                LEDDRIVER8_FULL_OUTPUT_CURRENT_GAIN );
}

void leddriver8_set_brightness ( leddriver8_t *ctx, uint8_t num_led, uint8_t value )
{
    if ( num_led == LEDDRIVER8_BRIGHTNESS_ALL_LED )
    {
        leddriver8_write_data ( ctx, LEDDRIVER8_REG_PWM_ALL, value );
    }
    else
    {
        leddriver8_write_data( ctx, LEDDRIVER8_REG_BRIGHTNESS_LED_0 + num_led, value );
    }
}

void leddriver8_set_output_gain ( leddriver8_t *ctx, uint8_t num_led, uint8_t value )
{
    if ( num_led == LEDDRIVER8_OUTPUT_GAIN_ALL_LED )
    {
        leddriver8_write_data( ctx, LEDDRIVER8_REG_IREF_ALL, value );
    }
    else
    {
        leddriver8_write_data( ctx, LEDDRIVER8_REG_IREF_0 + num_led, value );
    }
}

void leddriver8_set_mode_register( leddriver8_t *ctx, uint8_t mode_1, uint8_t mode_2 )
{
    leddriver8_write_data( ctx, LEDDRIVER8_REG_MODE_1, mode_1 );
    leddriver8_write_data( ctx, LEDDRIVER8_REG_MODE_2, mode_2 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void communication_delay( void )
{
    Delay_10us( );
}

// ------------------------------------------------------------------------- END

