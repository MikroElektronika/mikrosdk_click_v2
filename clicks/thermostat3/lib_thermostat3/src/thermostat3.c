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

#include "thermostat3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define THERMOSTAT_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void conversions_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermostat3_cfg_setup ( thermostat3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rly = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->internal_temp_cfg = 0.0;
    cfg->thermocouple_temp_cfg = 0.0;
    cfg->fault_value_cfg = 0;
}

THERMOSTAT_RETVAL thermostat3_init ( thermostat3_t *ctx, thermostat3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = THERMOSTAT_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return THERMOSTAT_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, THERMOSTAT_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rly, cfg->rly );

    spi_master_deselect_device( ctx->chip_select );  

    ctx->relay_flag = 0;
    ctx->fault_flag = 0;
    ctx->f_error = 3;

    return THERMOSTAT_OK;
}

void thermostat3_generic_read ( thermostat3_t *ctx, uint8_t *read_buff )
{
    uint8_t i;

    spi_master_select_device( ctx->chip_select );
    for ( i = 0; i < 4; i++ )
    {
      spi_master_read( &ctx->spi, &read_buff[ i ], 1 );
    }
    spi_master_deselect_device( ctx->chip_select );     
}

void thermostat3_process ( thermostat3_t *ctx, temp_vals_t *tmp )
{
    uint8_t read_data[ 4 ];
    int16_t i_temp;
    int16_t e_temp;
    
    thermostat3_generic_read( ctx, read_data );

    // External Thermocouple Temperature

    e_temp = read_data[ 0 ];
    e_temp <<= 8;
    e_temp |= read_data[ 1 ] & 0xFC;
    
    if ( read_data[ 0 ] > 128 )
    {
        e_temp = ~ e_temp;

        tmp->thermocouple_temp = ( float )( ( e_temp >> 2 ) & 0x03 );
        tmp->thermocouple_temp *= -0.25;
        tmp->thermocouple_temp -= ( float )( e_temp >> 4 );
        tmp->thermocouple_temp += 1.0;
    }
    else
    {
        tmp->thermocouple_temp = ( float )( ( e_temp >> 2 ) & 0x03 );
        tmp->thermocouple_temp *= 0.25;
        tmp->thermocouple_temp += ( float )( e_temp >> 4 );
    }
    
    // Internal Temperature

    i_temp = read_data[ 2 ];
    i_temp <<= 8;
    i_temp |= read_data[ 3 ] & 0xF0;
    
    if ( i_temp > 32768 )
    {
        i_temp = ~ i_temp;

       tmp->internal_temp = ( float )( ( i_temp >> 4 ) & 0x0F );
       tmp->internal_temp *= -0.0625;
       tmp->internal_temp -= ( float )( i_temp >> 8 );
       tmp->internal_temp += 1.0;
    }
    else
    {
       tmp->internal_temp = ( float )( ( i_temp >> 4 ) & 0x0F );
       tmp->internal_temp *= 0.0625;
       tmp->internal_temp += ( float )( i_temp >> 8 );
       tmp->internal_temp -= 1.0;
    }
    
    // Fault [Error] value
    tmp->fault_value = ( read_data[ 1 ] & 0x01 ) << 3;
    tmp->fault_value |= ( read_data[ 3 ] & 0x07 );
    
    conversions_delay( );
}

float thermostat3_get_internal_temperature ( temp_vals_t *tmp, uint8_t temp_in )
{
    if( temp_in == THERMOSTAT3_TEMP_IN_KELVIN )
    {
        tmp->internal_temp = tmp->internal_temp + 273.15;
    }
    else if ( temp_in == THERMOSTAT3_TEMP_IN_FAHRENHEIT )
    {
        tmp->internal_temp = tmp->internal_temp * 1.8 + 32.0;
    }
    
    return tmp->internal_temp;
}

float thermostat3_get_thermocouple_temperature ( temp_vals_t *tmp, uint8_t temp_in )
{
    if ( temp_in == THERMOSTAT3_TEMP_IN_KELVIN)
    {
        tmp->thermocouple_temp = tmp->thermocouple_temp + 273.15;
    }
    else if( temp_in == THERMOSTAT3_TEMP_IN_FAHRENHEIT )
    {
        tmp->thermocouple_temp = tmp->thermocouple_temp * 1.8 + 32.0;
    }
    
    return tmp->thermocouple_temp;
}

uint8_t thermostat3_get_fault_data ( temp_vals_t *tmp, uint8_t err )
{
    if ( err == THERMOSTAT3_FAULT_ALL_FLAG )
    {
        return tmp->fault_value;
    }

    if ( ( tmp->fault_value & err ) != 0 )
    {
        return 1;
    }
    return 0;
}

void thermostat3_relay_control ( thermostat3_t *ctx, uint8_t relay_pos )
{
    if ( relay_pos == THERMOSTAT3_RELAY_ON )
    {
        digital_out_high( &ctx->rly );
    }
    else
    {
        digital_out_low( &ctx->rly );
    }
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void conversions_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

