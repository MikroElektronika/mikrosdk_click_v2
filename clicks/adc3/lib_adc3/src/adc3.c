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

#include "adc3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

// ADC3 Multiplying Factor

#define ADC3_MULTIP_FACTOR             2.048

// ADC3 Result Calibrating Factor

#define ADC3_RESUL_12_CALIB_FACTOR     2048.0
#define ADC3_RESUL_14_CALIB_FACTOR     8192.0
#define ADC3_RESUL_16_CALIB_FACTOR     32768.0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc3_cfg_setup ( adc3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ADC3_I2C_SLAVE_ADDR;
}

ADC3_RETVAL adc3_init ( adc3_t *ctx, adc3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ADC3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return ADC3_OK;
}

void adc3_default_cfg ( adc3_t *ctx )
{
    // Initiate general reset function
    
    adc3_reset( ctx );
    dev_comm_delay( );
}

void adc3_generic_write ( adc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void adc3_generic_read ( adc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void adc3_reset ( adc3_t *ctx )
{
    uint8_t tx_buf;
    
    tx_buf = ADC3_GENERAL_CALL_RESET;
    
    adc3_generic_write( ctx, ADC3_CFG_REG, &tx_buf, 1 );
}

void adc3_latch ( adc3_t *ctx )
{
    uint8_t tx_buf;
    
    tx_buf = ADC3_GENERAL_CALL_LATCH;
    
    adc3_generic_write( ctx, ADC3_CFG_REG, &tx_buf, 1 );
}

void adc3_conversion ( adc3_t *ctx )
{
    uint8_t tx_buf;
    
    tx_buf = ADC3_GENERAL_CALL_CONVERSION;
    
    adc3_generic_write( ctx, ADC3_CFG_REG, &tx_buf, 1 );
}

int16_t adc3_read_measurement ( adc3_t *ctx, uint8_t channel, uint8_t resolution, uint8_t gain )
{
    uint8_t tmp_data[ 5 ];
    int16_t result;
    
    tmp_data[ 0 ]  = channel;       
    tmp_data[ 0 ] |= ADC3_CONV_CONTINOUS;         
    tmp_data[ 0 ] |= resolution;   
    tmp_data[ 0 ] |= gain;          
    
    dev_comm_delay( );
    i2c_master_write( &ctx->i2c, tmp_data, 1 ); 
    dev_comm_delay( );

    tmp_data[ 0 ]  = ADC3_RDY_SET;
    tmp_data[ 0 ] |= channel;       
    tmp_data[ 0 ] |= ADC3_CONV_CONTINOUS;         
    tmp_data[ 0 ] |= resolution;   
    tmp_data[ 0 ] |= gain;          

    i2c_master_write( &ctx->i2c, tmp_data, 1 ); 
    dev_comm_delay( );

    i2c_master_read( &ctx->i2c, tmp_data, 4 );

    result = ADC3_DATA_START_VALUE;
    if ( resolution == ADC3_SAMPLE_RATE_12 )
    {
        tmp_data[ 0 ] &= ADC3_DATA_RESOL_RATE_12;
        result  |= tmp_data[ 0 ];
        result <<= 8;
        result  |= tmp_data[ 1 ];
        if( result > ADC3_DATA_RESULT_RATE_12 ) {
            result ^= 0xFFF;
            result  = ~result;
        }
    }
    else if ( resolution == ADC3_SAMPLE_RATE_14 )
    {
        tmp_data[ 0 ] &= ADC3_DATA_RESOL_RATE_14;
        result  |= tmp_data[ 0 ];
        result <<= 8;
        result  |= tmp_data[ 1 ];
        if( result > ADC3_DATA_RESULT_RATE_14 ) {
            result ^= 0x3FFF;
            result  = ~result;
        }
    }
    else
    {
        tmp_data[ 0 ] &= ADC3_DATA_RESOL_RATE_16;
        result  |= tmp_data[ 0 ];
        result <<= 8;
        result  |= tmp_data[ 1 ];
        if( result > ADC3_DATA_RESULT_RATE_16 ) {
            result ^= 0xFFFF;
            result  = ~result;
        }
    }

    return result;
}

float adc3_read_voltage ( adc3_t *ctx, uint8_t channel, uint8_t resolution, uint8_t gain )
{
    int16_t tmp_data;
    float result;

    tmp_data = adc3_read_measurement( ctx, channel, resolution, gain );
    
    result = ADC3_DATA_START_VALUE;
    if( resolution == ADC3_SAMPLE_RATE_12 )
    {
        result  = (float)tmp_data;
	    result *= ADC3_MULTIP_FACTOR;
	    result /= ADC3_RESUL_12_CALIB_FACTOR;
    }
    else if( resolution == ADC3_SAMPLE_RATE_14 )
    {
        result  = (float)tmp_data;
        result *= ADC3_MULTIP_FACTOR;
        result /= ADC3_RESUL_14_CALIB_FACTOR;
    }
    else
    {
        result  = (float)tmp_data;
	    result *= ADC3_MULTIP_FACTOR;
	    result /= ADC3_RESUL_16_CALIB_FACTOR;
    }

    return result;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_comm_delay ( void )
{
    Delay_100ms();
}

// ------------------------------------------------------------------------- END

