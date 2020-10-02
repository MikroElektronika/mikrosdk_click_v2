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

#include "heartrate.h"
#include <string.h>


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static int drv_abs ( int i );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void heartrate_cfg_setup ( heartrate_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x57;
}

HEARTRATE_RETVAL heartrate_init ( heartrate_t *ctx, heartrate_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HEARTRATE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return HEARTRATE_OK;
}

void heartrate_default_cfg ( heartrate_t *ctx )
{
    uint8_t cfg[ 1 ] = { 0 };
    uint8_t cfg_reset[ 1 ] = { 0 };

    heartrate_generic_read( ctx, HEARTRATE_MODE_CONFIG, 1, cfg_reset );
    
    cfg_reset[ 0 ].B6 = 1;
    
    heartrate_generic_write( ctx, HEARTRATE_MODE_CONFIG, 1, cfg_reset );
    // wait for the RESET bit to clear itself

    for ( ; ; )
    {
        heartrate_generic_read( ctx, HEARTRATE_MODE_CONFIG, 1, cfg_reset );
        if ( cfg_reset[0].B6 == 0 ) 
        {
            break;
        }
    }

    // read old and set new mode
    heartrate_generic_read( ctx, HEARTRATE_MODE_CONFIG, 1, cfg );
    cfg[ 0 ] = ( cfg[ 0 ] & ~0x07 ) | HEARTRATE_HR_ONLY | HEARTRATE_SPO2_EN | HEARTRATE_TEMP_EN;

    heartrate_generic_write( ctx, HEARTRATE_MODE_CONFIG, 1, cfg );
    heartrate_generic_read( ctx, HEARTRATE_SPO2_CONFIG, 1, cfg );   // read SpO2 configuration
    cfg[ 0 ] |= ( 1 << 6 );                                         // enable High Resolution SpO2
    cfg[ 0 ] |= HEARTRATE_SAMPLES_50;                               // set samples per second
    cfg[ 0 ] |= HEARTRATE_PULSE_WIDTH_1600;                         // set 16-bit ADC resolution
    heartrate_generic_write( ctx, HEARTRATE_SPO2_CONFIG, 1, cfg );  // send new SpO2 configuration

    cfg[ 0 ] = 0x00;
    cfg[ 0 ] |= HEARTRATE_IR_CURRENT_500;                           // set IR LED current to be 50 mA
    cfg[ 0 ] |= HEARTRATE_RED_CURRENT_240;                          // set RED LED current to be 24 mA
    heartrate_generic_write( ctx, HEARTRATE_LED_CONFIG, 1, cfg );   // send new LED current control config

    // interrupt settings
    heartrate_generic_read( ctx, HEARTRATE_INT_ENABLE, 1, cfg );
    cfg[ 0 ] |= HEARTRATE_ENA_HR_RDY;
    cfg[ 0 ] |= HEARTRATE_ENA_SO2_RDY;
    cfg[ 0 ] |= HEARTRATE_ENA_TEP_RDY;

    // send new interrupt settings
    heartrate_generic_write( ctx, HEARTRATE_INT_ENABLE, 1, cfg );
}

void heartrate_generic_write ( heartrate_t *ctx, uint8_t reg, uint16_t len, uint8_t *data_buf )
{
    uint8_t i;
    uint8_t tx_buf[ 64 ];
    uint8_t *ptr = data_buf;
    
    tx_buf[ 0 ] = reg;
    
    memcpy( &tx_buf[ 1 ], data_buf, len );

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void heartrate_generic_read ( heartrate_t *ctx, uint8_t reg, uint16_t len, uint8_t *data_buf )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t heartrate_get_revision_id ( heartrate_t *ctx )
{
    uint8_t read_data;
    heartrate_generic_read( ctx, HEARTRATE_REVISION_ID, 1, &read_data );
    return read_data;
}

// get part ID
uint8_t heartrate_get_part_id ( heartrate_t *ctx )
{
    uint8_t read_data;
    heartrate_generic_read( ctx, HEARTRATE_PART_ID, 1, &read_data );
    return read_data;
}

// get config
uint8_t heartrate_get_config ( heartrate_t *ctx )
{
    uint8_t read_data;
    heartrate_generic_read( ctx, HEARTRATE_MODE_CONFIG, 1, &read_data );
    return read_data;
}

// get status
uint8_t heartrate_get_status ( heartrate_t *ctx )
{
    uint8_t read_data;
    heartrate_generic_read( ctx, HEARTRATE_INT_STATUS, 1, &read_data );
    return read_data;
}

// send configuration
void heartrate_set_config ( heartrate_t *ctx, uint8_t cfg )
{
    heartrate_generic_write( ctx, HEARTRATE_MODE_CONFIG, 1, &cfg );
}

// set interrupts
void heartrate_set_interrupt ( heartrate_t *ctx, uint8_t intrpts )
{
    heartrate_generic_write( ctx, HEARTRATE_MODE_CONFIG, 1, &intrpts );
}

// read data from the sensor
uint8_t heartrate_read_ir_red ( heartrate_t *ctx, uint16_t *ir_buff, uint16_t *red_buff )
{
    uint8_t i, sample_num = 0;
    uint8_t wr_ptr = 0, rd_ptr = 0, ov_ptr, ptr, samples[ 4 ];

    heartrate_generic_read( ctx, HEARTRATE_FIFO_WRITE_PTR, 1, &wr_ptr );
    heartrate_generic_read( ctx, HEARTRATE_FIFO_READ_PTR, 1, &rd_ptr );

    sample_num = drv_abs( 16 + wr_ptr - rd_ptr ) % 16;

    if ( sample_num >= 1 )
    {
        for ( i = 0; i < sample_num; ++i )
        {
            // read data
            heartrate_generic_read( ctx, HEARTRATE_FIFO_DATA_REG, 4, samples );
            ( ( uint8_t * )ir_buff   )[ 0 ]  = samples[ 1 ];
            ( ( uint8_t * )ir_buff++ )[ 1 ]  = samples[ 0 ];

            ( ( uint8_t * )red_buff   )[ 0 ]  = samples[ 3 ];
            ( ( uint8_t * )red_buff++ )[ 1 ]  = samples[ 2 ];
        }
    }
    return sample_num;
}

// read calibration temperature from the sensor
void heartrate_read_temp ( heartrate_t *ctx, uint16_t *temp_value )
{
    uint8_t temp_int, temp_frac;

    // read temperature - int part

    heartrate_generic_read( ctx, HEARTRATE_TEMP_INTEGER, 1, &temp_int );   
    
    // read temperature - frac part

    heartrate_generic_read( ctx, HEARTRATE_TEMP_FRACTION, 1, &temp_frac ); 

    ( ( uint8_t * )temp_value )[ 1 ]  = temp_int;
    ( ( uint8_t * )temp_value )[ 0 ]  = temp_frac;
}

uint8_t heartrate_data_ready ( heartrate_t *ctx )
{
   uint8_t status;
   
   status = ( digital_in_read( &ctx->int_pin ) == 0 ) && ( ( heartrate_get_status( ctx ) & 0x20 ) != 0 );
  
   return status;
}

void hr_shut_down ( heartrate_t *ctx, bool enable )
{
  uint8_t temp;
  heartrate_generic_read( ctx, HEARTRATE_MODE_CONFIG, 1, &temp );

  if ( enable == true )
  {
    temp |= ( 1 << 7 );
  }
  else
  {
    temp &= ~( 1 << 7 );
  }

  heartrate_generic_write( ctx, HEARTRATE_MODE_CONFIG, 1, &temp );
}

void hr_reset ( heartrate_t *ctx )
{
  uint8_t temp;
  heartrate_generic_read( ctx, HEARTRATE_MODE_CONFIG, 1, &temp );

  temp |= ( 1 << 6 );
  heartrate_generic_write( ctx, HEARTRATE_MODE_CONFIG, 1, &temp );
}

void hr_temp_enable ( heartrate_t *ctx, bool enable )
{
  uint8_t temp;
  heartrate_generic_read( ctx, HEARTRATE_MODE_CONFIG, 1, &temp );

  if ( enable == true )
  {
    temp |= ( 1 << 3 );
  }
  else
  {
    temp &= ~( 1 << 3 );
  }

  heartrate_generic_write( ctx, HEARTRATE_MODE_CONFIG,1, &temp );
}

int8_t hr_set_mode ( heartrate_t *ctx, uint8_t mode )
{
  uint8_t temp;

  if ( mode > 7 )
  {
    return -1;
  }
  heartrate_generic_read( ctx, HEARTRATE_MODE_CONFIG, 1, &temp );

  temp |= mode;
  heartrate_generic_write( ctx, HEARTRATE_MODE_CONFIG, 1, &temp );
  return 0;
}

void hr_spo2_high_res_enable ( heartrate_t *ctx, bool enable )
{
  uint8_t temp;
  heartrate_generic_read( ctx, HEARTRATE_SPO2_CONFIG, 1, &temp );

  if ( enable == true )
  {
    temp |= ( 1 << 6 );
  }
  else
  {
    temp &= ~( 1 << 6 );
  }
  heartrate_generic_write( ctx, HEARTRATE_SPO2_CONFIG, 1, &temp );
}

uint8_t hr_spo2_set_sample_rate ( heartrate_t *ctx, uint8_t sample_rate )
{
  uint8_t temp;
  if ( sample_rate > 7 )
  {
    return -1;
  }
  heartrate_generic_read( ctx, HEARTRATE_SPO2_CONFIG, 1, &temp );
  temp |= ( sample_rate << 2 );

  heartrate_generic_write( ctx,  HEARTRATE_SPO2_CONFIG, 1, &temp );
  return 0;
}

uint8_t hr_set_led_pulse_width ( heartrate_t *ctx, uint8_t value )
{
  uint8_t temp;
  if ( value > 3 ) 
  {
    return -1;
  }
  heartrate_generic_read( ctx, HEARTRATE_SPO2_CONFIG, 1, &temp );

  temp |= value;
  heartrate_generic_write( ctx, HEARTRATE_SPO2_CONFIG, 1, &temp );
  return 0;
}

uint8_t hr_set_red_current_level ( heartrate_t *ctx, uint8_t level )
{
  uint8_t temp;
  if ( level > 15 ) 
  {
    return -1;
  }
  heartrate_generic_read( ctx, HEARTRATE_LED_CONFIG, 1, &temp );

  temp |= ( level << 4 );
  heartrate_generic_write( ctx, HEARTRATE_LED_CONFIG, 1, &temp );
  return 0;
}

uint8_t hr_set_ir_current_level ( heartrate_t *ctx, uint8_t level )
{
  uint8_t temp;
  if ( level > 15 ) 
  {
    return -1;
  }
  heartrate_generic_read( ctx, HEARTRATE_LED_CONFIG, 1, &temp );

  temp |= level;
  heartrate_generic_write( ctx, HEARTRATE_LED_CONFIG, 1, &temp );
  return 0;
}

// INTERRUPTS

void hr_fifo_almost_full_int_enable ( heartrate_t *ctx, bool enable )
{
  uint8_t temp;
  heartrate_generic_read( ctx, HEARTRATE_INT_ENABLE, 1, &temp );
  if ( enable == true )
  {
    temp |= ( 1 << 7 );
  }
  else
  {
    temp &= ~( 1 << 7 );
  }
   
  heartrate_generic_write( ctx, HEARTRATE_INT_ENABLE, 1 , &temp );
}

void hr_temp_ready_int_enable ( heartrate_t *ctx, bool enable )
{
  uint8_t temp;
  heartrate_generic_read( ctx, HEARTRATE_INT_ENABLE, 1, &temp );
  if ( enable == true )
  {
    temp |= ( 1 << 6 );
  }
  else
  {
    temp &= ~( 1 << 6 );
  }

  heartrate_generic_write( ctx, HEARTRATE_INT_ENABLE, 1, &temp );
}

void hr_heartrate_data_ready_int_enable ( heartrate_t *ctx, bool enable )
{
  uint8_t temp;
  heartrate_generic_read( ctx, HEARTRATE_INT_ENABLE, 1, &temp );
  if ( enable == true )
  {
    temp |= ( 1 << 5 );
  }
  else
  {
    temp &= ~( 1 << 5 );
  }

  heartrate_generic_write( ctx, HEARTRATE_INT_ENABLE, 1, &temp );
}

void hr_heartrate_spo2_data_ready_int_enable ( heartrate_t *ctx, bool enable )
{
  uint8_t temp;
  heartrate_generic_read( ctx, HEARTRATE_INT_ENABLE, 1, &temp );
  if ( enable == true )
  {
    temp |= ( 1 << 4 );
  }
  else
  {
    temp &= ~( 1 << 4 );
  }

  heartrate_generic_write( ctx, HEARTRATE_INT_ENABLE, 1, &temp );
}

uint8_t hr_read_diodes ( heartrate_t *ctx, uint16_t* ir_buff, uint16_t* red_buff )
{
    uint8_t i, sample_num = 0;
    uint8_t wr_ptr = 0, rd_ptr = 0, samples[ 4 ];

    heartrate_generic_read( ctx, HEARTRATE_FIFO_WRITE_PTR, 1, &wr_ptr );
    heartrate_generic_read( ctx, HEARTRATE_FIFO_READ_PTR, 1, &rd_ptr );

    sample_num = drv_abs( 16 + wr_ptr - rd_ptr ) % 16;

    if ( sample_num >= 1 )
    {
        for ( i = 0; i < sample_num; ++i )
        {
            // read data
            heartrate_generic_read( ctx, HEARTRATE_FIFO_DATA_REG, 4, samples );

            *( ir_buff ) =  ( uint16_t )samples[ 1 ];
            *( ir_buff++ ) |= ( uint16_t )samples[ 0 ] << 8;
            *( red_buff ) = ( uint16_t )samples[ 3 ];
            *( red_buff++ ) |=  ( uint16_t ) samples[ 2 ] << 8;
        }
    }
    return sample_num;
}

uint8_t hr_get_status ( heartrate_t *ctx )
{
    uint8_t read_data;
    heartrate_generic_read( ctx, HEARTRATE_INT_STATUS, 1, &read_data );
    return read_data;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static int drv_abs ( int i )
{	 
    return i < 0 ? -i : i;
}

// ------------------------------------------------------------------------- END

