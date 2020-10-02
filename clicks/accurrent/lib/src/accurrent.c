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

#include "accurrent.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCURRENT_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accurrent_cfg_setup ( accurrent_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

ACCURRENT_RETVAL accurrent_init ( accurrent_t *ctx, accurrent_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ACCURRENT_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ACCURRENT_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ACCURRENT_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    digital_in_init( &ctx->an, cfg->an );
    spi_master_deselect_device( ctx->chip_select );  

    return ACCURRENT_OK;
}

void accurrent_generic_transfer ( accurrent_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

float accurrent_get_ma ( accurrent_t *ctx )
{
    // Local variables
    uint8_t i;
    uint8_t buffer[ 10 ];
    uint8_t read_lsb;
    uint8_t read_msb;
    uint8_t msb_mask;
    uint16_t max_val;
    uint16_t tmp;
    float avg;
    uint16_t sum;

    // Initialize variables
    msb_mask = 0x00;
    tmp = 0;
    avg = 0;
    sum = 0;
    max_val = 0;

    // Setting appropriate MSB mask
    if ( ACCURRENT_ADC_CONVERSION_SIZE == ACCURRENT_ADC_12_BIT )
    {
        msb_mask = ACCURRENT_ADC_12_BIT_MSB_MASK;
        max_val = 4095;
    }
    else if ( ACCURRENT_ADC_CONVERSION_SIZE == ACCURRENT_ADC_10_BIT )
    {
        msb_mask = ACCURRENT_ADC_10_BIT_MSB_MASK;
        max_val = 1024;
    }
    else if ( ACCURRENT_ADC_CONVERSION_SIZE == ACCURRENT_ADC_8_BIT )
        {
        msb_mask = ACCURRENT_ADC_8_BIT_MSB_MASK;
        max_val = 255;
        }
    else return 0.0;
        
    // SPI reading
    for( i = 0; i < ACCURRENT_ADC_ITERATION_SIZE; i++ )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_read( &ctx->spi, buffer, 2 );
        spi_master_deselect_device( ctx->chip_select );
        
        // Reading most significant and least significant bytes
        read_msb = buffer[ 0 ] & msb_mask;
        read_lsb = buffer[ 1 ];
        
        // Forming ADC_CONVERSION_SIZE
        tmp = ( ( read_msb & msb_mask ) << 8 );
        tmp =  tmp | read_lsb;
        
        sum = sum + tmp;                            // Sum of the ADC readings
    }
    
    // Average ADC value based on sum of the ADC readings
    avg = ( float ) ( sum / ACCURRENT_ADC_ITERATION_SIZE );
    avg = ( avg / max_val ) * 8.25 * 1000;

    return avg;                                   // Returns the average ADC value
}

float accurrent_get_a ( accurrent_t *ctx )
{
    // Local variables
    uint8_t i;
    uint8_t buffer[ 10 ];
    uint8_t read_lsb;
    uint8_t read_msb;
    uint8_t msb_mask;
    uint16_t max_val;
    uint16_t tmp;
    float avg;
    uint16_t sum;

    // Initialize variables
    msb_mask = 0x00;
    tmp = 0;
    avg = 0;
    sum = 0;
    max_val = 0;

    // Setting appropriate MSB mask
    if ( ACCURRENT_ADC_CONVERSION_SIZE == ACCURRENT_ADC_12_BIT )
    {
        msb_mask = ACCURRENT_ADC_12_BIT_MSB_MASK;
        max_val = 4095;
    }
    else if ( ACCURRENT_ADC_CONVERSION_SIZE == ACCURRENT_ADC_10_BIT )
    {
        msb_mask = ACCURRENT_ADC_10_BIT_MSB_MASK;
        max_val = 1024;
    }
    else if ( ACCURRENT_ADC_CONVERSION_SIZE == ACCURRENT_ADC_8_BIT )
        {
        msb_mask = ACCURRENT_ADC_8_BIT_MSB_MASK;
        max_val = 255;
        }
    else return 0.0;
        
    // SPI reading
    for( i = 0; i < ACCURRENT_ADC_ITERATION_SIZE; i++ )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_read( &ctx->spi, buffer, 2 );
        spi_master_deselect_device( ctx->chip_select );
        
        // Reading most significant and least significant bytes
        read_msb = buffer[ 0 ] & msb_mask;
        read_lsb = buffer[ 1 ];
        
        // Forming ADC_CONVERSION_SIZE
        tmp = ( ( read_msb & msb_mask ) << 8 );
        tmp =  tmp | read_lsb;
        
        sum = sum + tmp;                            // Sum of the ADC readings
    }
    
    // Average ADC value based on sum of the ADC readings
    avg = ( float ) (sum / ACCURRENT_ADC_ITERATION_SIZE );
    avg = ( avg / max_val ) * 8.25;

    return avg;                                   // Returns the average ADC value
}
// ------------------------------------------------------------------------- END

