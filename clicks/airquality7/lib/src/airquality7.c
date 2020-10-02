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

#include "airquality7.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void
airquality7_communication_delay( void );

static uint8_t 
airquality7_get_crc( uint8_t *data_in, uint8_t data_size );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void airquality7_cfg_setup ( airquality7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AIRQUALITY7_DEV_ADDR;
}

AIRQUALITY7_RETVAL airquality7_init ( airquality7_t *ctx, airquality7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AIRQUALITY7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return AIRQUALITY7_OK;
}

void airquality7_generic_write ( airquality7_t *ctx, uint8_t *data_buf )
{  
    i2c_master_write( &ctx->i2c, data_buf, 6 );   
}

void airquality7_generic_read ( airquality7_t *ctx, uint8_t *data_buf )
{
    uint8_t tmp;
    
    airquality7_communication_delay( );
    
    i2c_master_read( &ctx->i2c, data_buf, 7 );
}

void
airquality7_set_ppmco2( airquality7_t *ctx, uint8_t *ppmco2_value )
{
    uint8_t tmp_data[ 6 ] = { AIRQUALITY7_DUMMY };
    uint8_t cnt;
    
    tmp_data[ 0 ] = AIRQUALITY7_CMD_SET_PPMCO2;
    
    for ( cnt = 1; cnt <= 4; cnt++  )
    {
        tmp_data[ cnt ] = *ppmco2_value;
        ppmco2_value++;
    }
    
    tmp_data[ 5 ] = airquality7_get_crc( tmp_data, 5 );
    
    airquality7_generic_write( ctx, tmp_data );
}

airquality7_err_t
airquality7_get_status( airquality7_t *ctx, uint16_t *tvoc_ppb, uint16_t *co2_ppm, 
                        uint32_t *res_val_ohm, uint8_t *err_byte )
{
    uint8_t tmp_data[ 7 ] = { AIRQUALITY7_DUMMY };
    uint8_t crc_calc = AIRQUALITY7_DUMMY;
    
    tmp_data[ 0 ] = AIRQUALITY7_CMD_GET_STATUS;
    tmp_data[ 5 ] = airquality7_get_crc( tmp_data, 5 );
    
    airquality7_generic_write( ctx, tmp_data );
    airquality7_generic_read( ctx, tmp_data );
    
    crc_calc = airquality7_get_crc( tmp_data, 6 );
    
    if ( crc_calc != tmp_data[ 6 ] )
    {
        return AIRQUALITY7_ERR_CRC;
    }
    
    if ( tvoc_ppb != AIRQUALITY7_NULL )
    {
        float res = AIRQUALITY7_DUMMY;
        
        res = tmp_data[ 0 ] - 13;
        res *= 1000;
        res /= 229;
        
        *tvoc_ppb = (uint16_t)res;
    }
    
    if ( co2_ppm != AIRQUALITY7_NULL )
    {
        float res = AIRQUALITY7_DUMMY;
    
        res = tmp_data[ 1 ] - 13;
        res *= 1600;
        res /= 229;
        res += 400;
    
        *co2_ppm = (uint16_t)res;
    }
    
    if ( res_val_ohm != AIRQUALITY7_NULL )
    {
        uint32_t res = AIRQUALITY7_DUMMY;
    
        res = (uint32_t)( tmp_data[ 2 ] * 65536 );
        res += (uint16_t)( tmp_data[ 3 ] * 256 );
        res += tmp_data[ 4 ];
        res *= 10;
    
        *res_val_ohm = res;
    }
    
    if ( err_byte != AIRQUALITY7_NULL )
    {
        *err_byte = tmp_data[ 5 ];
    }
    
    return AIRQUALITY7_ERR_OK;
}

airquality7_err_t
airquality7_get_revision( airquality7_t *ctx, uint8_t *year, uint8_t *month, uint8_t *day, 
                          uint8_t *ascii_code )
{
    uint8_t tmp_data[ 7 ] = { AIRQUALITY7_DUMMY };
    uint8_t crc_calc = AIRQUALITY7_DUMMY;

    tmp_data[ 0 ] = AIRQUALITY7_CMD_GET_REVISION;
    tmp_data[ 5 ] = airquality7_get_crc( tmp_data, 5 );

    airquality7_generic_write( ctx, tmp_data );
    airquality7_generic_read( ctx, tmp_data );

    crc_calc = airquality7_get_crc( tmp_data, 6 );

    if ( crc_calc != tmp_data[ 6 ] )
    {
        return AIRQUALITY7_ERR_CRC;
    }
    
    if ( year != AIRQUALITY7_NULL )
    {
        *year = tmp_data[ 0 ];
    }
    
    if ( month != AIRQUALITY7_NULL )
    {
        *month = tmp_data[ 1 ];
    }
    
    if ( day != AIRQUALITY7_NULL )
    {
        *day = tmp_data[ 2 ];
    }
    
    if ( ascii_code != AIRQUALITY7_NULL )
    {
        *ascii_code = tmp_data[ 3 ];
    }
    
    return AIRQUALITY7_ERR_OK;
}

airquality7_err_t
airquality7_get_r0_calib( airquality7_t *ctx, uint16_t *r0_kohm )
{
    uint8_t tmp_data[ 7 ] = { AIRQUALITY7_DUMMY };
    uint8_t crc_calc = AIRQUALITY7_DUMMY;

    tmp_data[ 0 ] = AIRQUALITY7_CMD_GET_R0;
    tmp_data[ 5 ] = airquality7_get_crc( tmp_data, 5 );

    airquality7_generic_write( ctx, tmp_data );
    airquality7_generic_read( ctx, tmp_data );

    crc_calc = airquality7_get_crc( tmp_data, 6 );

    if ( crc_calc != tmp_data[ 6 ] )
    {
        return AIRQUALITY7_ERR_CRC;
    }

    if ( r0_kohm != AIRQUALITY7_NULL )
    {
        *r0_kohm = tmp_data[ 1 ];
        *r0_kohm <<= 8;
        *r0_kohm |= tmp_data[ 0 ];
    }

    return AIRQUALITY7_ERR_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void
airquality7_communication_delay( void )
{
    Delay_100ms( );
}

static uint8_t 
airquality7_get_crc( uint8_t *data_in, uint8_t data_size )
{
    uint8_t crc = 0x00;
    uint8_t cnt = 0x00;
    uint16_t sum = 0x0000;
 
    for ( cnt = 0; cnt < data_size; cnt++ )
    {
        sum += *data_in;
        data_in++;
    }
    
    crc = sum;
    crc += ( sum / 0x0100 );
    crc = 0xFF - crc;

    return crc;
}

// ------------------------------------------------------------------------- END

