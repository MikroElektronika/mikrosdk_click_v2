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

#include "pressure2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PRESSURE2_DUMMY 0


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static double pow( double x, uint8_t y );
static uint8_t crcMS5803( pressure2_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure2_cfg_setup ( pressure2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

PRESSURE2_RETVAL pressure2_init ( pressure2_t *ctx, pressure2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = PRESSURE2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return PRESSURE2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, PRESSURE2_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    return PRESSURE2_OK;
}

PRESSURE2_RETVAL pressure2_default_cfg ( pressure2_t *ctx )
{
    uint8_t p_crc, n_crc;
    uint8_t i;
    
    ctx->pressure       = 0;
    ctx->temperature    = 0;
    ctx->delta_temp     = 0;
    ctx->sensor_offset  = 0;
    ctx->sensitivity    = 0;

    pressure2_reset( ctx );
    Delay_100ms();

    for ( i = 0; i < 8; i++ )
    {
        ctx->sensor_coefficients[ i ] = pressure2_read_coefficient( ctx, i );
    }

    p_crc = ctx->sensor_coefficients[ 7 ];
    n_crc = crcMS5803( ctx );

    if ( p_crc != n_crc )
    {
        return PRESSURE2_FALSE;
    }
    else
    {
        return PRESSURE2_TRUE;
    }
}

void pressure2_generic_transfer 
( 
    pressure2_t *ctx, 
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

void pressure2_reset ( pressure2_t *ctx )
{
    pressure2_write_bytes( ctx, PRESSURE2_CMD_RESET );
    Delay_100ms( );
}

void pressure2_read_data ( pressure2_t *ctx, uint8_t cmd, uint8_t *buffer, uint8_t n_bytes )
{
    pressure2_generic_transfer( ctx, &cmd, 1, buffer, n_bytes + 1 );
}

void pressure2_write_bytes ( pressure2_t *ctx, uint8_t cmd )
{   
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

uint16_t pressure2_read_coefficient ( pressure2_t *ctx, uint8_t index )
{
    uint16_t result = 0;
    uint8_t result_first[ 3 ];

    pressure2_read_data( ctx, PRESSURE2_CMD_PROM_RD + ( index * 2 ), result_first, 2 );
    result = ( (uint16_t)result_first[ 1 ] ) << 8;
    result |= result_first[ 2 ];

    return result;
}

uint32_t pressure2_send_cmdadc ( pressure2_t *ctx, uint8_t cmd )
{
    uint32_t result = 0;
    uint8_t adc_read[ 4 ];

    pressure2_write_bytes( ctx, PRESSURE2_CMD_ADC_CONV + cmd ); // Send conversion command
    Delay_1ms( );

    switch ( cmd & 0x0F )
    {
        case PRESSURE2_CMD_ADC_256 :
        { 
            Delay_500us();
            Delay_80us();
            Delay_80us();
            Delay_80us();
            Delay_80us();
            Delay_80us();
        break;
        }
        case PRESSURE2_CMD_ADC_512 :
        { 
            Delay_1ms();
            Delay_1ms();
            Delay_1ms();
        break;
        }
        case PRESSURE2_CMD_ADC_1024 :
        {
            Delay_1ms();
            Delay_1ms();
            Delay_1ms();
            Delay_1ms();
        break;
        }
        case PRESSURE2_CMD_ADC_2048 : 
        {
            Delay_8ms();
        break;
        }
        case PRESSURE2_CMD_ADC_4096 :
        {
            Delay_10ms();
            Delay_1ms();
            Delay_1ms();
            Delay_1ms();
            Delay_1ms();
        break;
        }
        default :
        {
        break;
        }
    }

    pressure2_read_data( ctx, PRESSURE2_CMD_ADC_READ, adc_read, 3 );
    result = ( (uint32_t) adc_read[1] << 16 );
    result |= ( (uint16_t) adc_read[2] << 8 );
    result |= adc_read[3];

    return result;
}

void pressure2_read_sensor ( pressure2_t *ctx, float *press, float *temp )
{
    
    ctx->pressure = pressure2_send_cmdadc( ctx, PRESSURE2_CMD_ADC_D1 + PRESSURE2_CMD_ADC_2048 );
    ctx->temperature = pressure2_send_cmdadc( ctx, PRESSURE2_CMD_ADC_D2 + PRESSURE2_CMD_ADC_2048 );

    ctx->delta_temp  = ctx->sensor_coefficients[ 5 ];
    ctx->delta_temp *= pow( 2, 8 );
    ctx->delta_temp  = ctx->temperature - ctx->delta_temp;

    ctx->sensor_offset  = ((float)ctx->delta_temp) / pow( 2, 7 ); 
    ctx->sensor_offset *= ((float)ctx->sensor_coefficients[ 4 ]) / pow( 2, 7 );
    ctx->sensor_offset += ((float)ctx->sensor_coefficients[ 2 ]) * pow( 2, 16 );

    ctx->sensitivity  = ((float)ctx->delta_temp) / pow( 2, 8 );
    ctx->sensitivity *= ((float)ctx->sensor_coefficients[ 3 ]) / pow( 2, 8 );
    ctx->sensitivity += ((float)ctx->sensor_coefficients[ 1 ]) * pow( 2, 15 );

    *press  = ((float)ctx->pressure ) / pow( 2, 15 );
    *press *= ((float)ctx->sensitivity ) / pow( 2, 21 );
    *press -= ((float)ctx->sensor_offset ) / pow( 2, 15 );
    *press /=10;
    
    *temp = ( 2000 + ( ( ctx->delta_temp / pow( 2, 13 ) ) * ( ctx->sensor_coefficients[6] / pow( 2, 10 ) ) )  ) / 100;
    
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static double pow ( double x, uint8_t y )
{
    double res = 1; // Initialize result

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
        {
            res = res * x;
        }

        // n must be even now
        y = y >> 1; // y = y/2
        x = x * x; // Change x to x^2
    }

    return res;
}

static uint8_t crcMS5803 ( pressure2_t *ctx )
{
    uint16_t cnt;                  // Simple counter
    uint16_t n_rem;                // Crc reminder
    uint16_t crc_read;             // Original value of the crc
    uint8_t  n_bit;

    n_rem = 0x00;
    crc_read = ctx->sensor_coefficients[ 7 ];       // Save read CRC
    ctx->sensor_coefficients[ 7 ] = ( 0xFF00 & ( ctx->sensor_coefficients[ 7 ] ) );   // CRC byte is replaced by 0
  
    for ( cnt = 0; cnt < 16; cnt++ )        // Operation is performed on bytes
    {
        // choose LSB or MSB
        if ( cnt % 2 == 1 )
        {
            n_rem ^= ( uint8_t ) ( ( ctx->sensor_coefficients[ cnt >> 1 ] ) & 0x00FF );
        }
        else
        {
            n_rem ^= ( uint8_t ) ( ctx->sensor_coefficients[ cnt >> 1 ] >> 8 );
        }

        for ( n_bit = 8; n_bit > 0; n_bit-- )
        {
            if ( n_rem & ( 0x8000 ) )
            {
                n_rem = ( n_rem << 1 ) ^ 0x3000;
            }
            else
            {
                n_rem = ( n_rem << 1 );
            }
        }
    }

    n_rem = ( 0x000F & ( n_rem >> 12 ) );    // Final 4-bit reminder is CRC code
    ctx->sensor_coefficients[ 7 ] = crc_read;        // Restore the crc_read to its original place

    return ( n_rem ^ 0x00 );                 // The calculated CRC should match what the device initally returned.
}
// ------------------------------------------------------------------------- END

