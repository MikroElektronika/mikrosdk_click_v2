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

static uint8_t pressure2_calculate_crc( pressure2_t *ctx );

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

err_t pressure2_init ( pressure2_t *ctx, pressure2_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, PRESSURE2_DUMMY ) ) 
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

    return PRESSURE2_OK;
}

err_t pressure2_default_cfg ( pressure2_t *ctx )
{
    ctx->pressure      = 0;
    ctx->temperature   = 0;
    ctx->delta_temp    = 0;
    ctx->sensor_offset = 0;
    ctx->sensitivity   = 0;

    pressure2_reset( ctx );
    Delay_100ms( );

    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        ctx->sensor_coefficients[ cnt ] = pressure2_read_coefficient( ctx, cnt );
    }

    if ( ctx->sensor_coefficients[ 7 ] != pressure2_calculate_crc( ctx ) )
    {
        return PRESSURE2_ERROR;
    }
    return PRESSURE2_OK;
}

void pressure2_reset ( pressure2_t *ctx )
{
    pressure2_write_bytes( ctx, PRESSURE2_CMD_RESET );
    Delay_100ms( );
}

void pressure2_read_data ( pressure2_t *ctx, uint8_t cmd, uint8_t *buffer, uint8_t n_bytes )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &cmd, 1, buffer, n_bytes );
    spi_master_deselect_device( ctx->chip_select );   
}

void pressure2_write_bytes ( pressure2_t *ctx, uint8_t cmd )
{   
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

uint16_t pressure2_read_coefficient ( pressure2_t *ctx, uint8_t index )
{
    uint8_t result_first[ 2 ] = { 0 };

    pressure2_read_data( ctx, PRESSURE2_CMD_PROM_RD + ( index * 2 ), result_first, 2 );

    return ( ( ( uint16_t ) result_first[ 0 ] ) << 8 ) | result_first[ 1 ];
}

uint32_t pressure2_send_cmd_adc ( pressure2_t *ctx, uint8_t cmd )
{
    uint8_t adc_read[ 3 ] = { 0 };

    pressure2_write_bytes( ctx, PRESSURE2_CMD_ADC_CONV + cmd ); // Send conversion command
    Delay_1ms( );

    switch ( cmd & 0x0F )
    {
        case PRESSURE2_CMD_ADC_256 :
        { 
            Delay_500us( );
            Delay_80us( );
            Delay_80us( );
            Delay_80us( );
            Delay_80us( );
            Delay_80us( );
            break;
        }
        case PRESSURE2_CMD_ADC_512 :
        { 
            Delay_1ms( );
            Delay_1ms( );
            Delay_1ms( );
            break;
        }
        case PRESSURE2_CMD_ADC_1024 :
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_1ms( );
            Delay_1ms( );
            break;
        }
        case PRESSURE2_CMD_ADC_2048 : 
        {
            Delay_8ms( );
            break;
        }
        case PRESSURE2_CMD_ADC_4096 :
        {
            Delay_10ms( );
            Delay_1ms( );
            Delay_1ms( );
            Delay_1ms( );
            Delay_1ms( );
            break;
        }
        default :
        {
            break;
        }
    }

    pressure2_read_data( ctx, PRESSURE2_CMD_ADC_READ, adc_read, 3 );

    return ( ( uint32_t ) adc_read[ 0 ] << 16 ) | ( ( uint16_t ) adc_read[ 1 ] << 8 ) | adc_read[ 2 ];
}

void pressure2_read_sensor ( pressure2_t *ctx, float *press, float *temp )
{
    ctx->pressure = pressure2_send_cmd_adc( ctx, PRESSURE2_CMD_ADC_D1 + PRESSURE2_CMD_ADC_2048 );
    ctx->temperature = pressure2_send_cmd_adc( ctx, PRESSURE2_CMD_ADC_D2 + PRESSURE2_CMD_ADC_2048 );

    ctx->delta_temp  = ctx->sensor_coefficients[ 5 ];
    ctx->delta_temp *= pow( 2, 8 );
    ctx->delta_temp  = ctx->temperature - ctx->delta_temp;

    ctx->sensor_offset  = ( ( float ) ctx->delta_temp ) / pow( 2, 7 ); 
    ctx->sensor_offset *= ( ( float ) ctx->sensor_coefficients[ 4 ] ) / pow( 2, 7 );
    ctx->sensor_offset += ( ( float ) ctx->sensor_coefficients[ 2 ] ) * pow( 2, 16 );

    ctx->sensitivity  = ( ( float ) ctx->delta_temp ) / pow( 2, 8 );
    ctx->sensitivity *= ( ( float ) ctx->sensor_coefficients[ 3 ] ) / pow( 2, 8 );
    ctx->sensitivity += ( ( float ) ctx->sensor_coefficients[ 1 ] ) * pow( 2, 15 );

    *press  = ( ( float ) ctx->pressure ) / pow( 2, 15 );
    *press *= ( ( float ) ctx->sensitivity ) / pow( 2, 21 );
    *press -= ( ( float ) ctx->sensor_offset ) / pow( 2, 15 );
    *press /= 10;
    
    *temp = ( 2000 + ( ( ctx->delta_temp / pow( 2, 13 ) ) * 
            ( ctx->sensor_coefficients[ 6 ] / pow( 2, 10 ) ) )  ) / 100;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t pressure2_calculate_crc ( pressure2_t *ctx )
{
    uint16_t n_rem = 0;            // Crc reminder
    uint16_t crc_read = 0;         // Original value of the crc
    uint8_t cnt = 0;               // Simple counter
    uint8_t n_bit = 0;

    n_rem = 0x00;
    crc_read = ctx->sensor_coefficients[ 7 ];   // Save read CRC
    ctx->sensor_coefficients[ 7 ] = ( 0xFF00 & ( ctx->sensor_coefficients[ 7 ] ) ); // CRC byte is replaced by 0
  
    for ( cnt = 0; cnt < 16; cnt++ )  // Operation is performed on bytes
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

    n_rem = ( 0x000F & ( n_rem >> 12 ) );       // Final 4-bit reminder is CRC code
    ctx->sensor_coefficients[ 7 ] = crc_read;   // Restore the crc_read to its original place

    return ( n_rem ^ 0x00 );                    // The calculated CRC should match what the device initally returned.
}
// ------------------------------------------------------------------------- END

