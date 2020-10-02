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

#include "thermo8.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static float b_to_t_conversion ( uint16_t r_data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo8_cfg_setup ( thermo8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ale = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO8_ADDR0;
}

THERMO8_RETVAL thermo8_init ( thermo8_t *ctx, thermo8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->ale, cfg->ale );

    return THERMO8_OK;
}

void thermo8_default_cfg ( thermo8_t *ctx )
{
    thermo8_set_resolution( ctx, THERMO8_R025C_65MS );
    thermo8_limit_set( ctx, THERMO8_TLOWER, 27.0 );
    thermo8_limit_set( ctx, THERMO8_TUPPER, 28.0 );
    thermo8_alert_enable( ctx, THERMO8_THYS_0C, THERMO8_ALERT_ON_ALL ); 
}

void thermo8_generic_write ( thermo8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermo8_generic_read ( thermo8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t thermo8_ale_get ( thermo8_t *ctx )
{
    return digital_in_read( &ctx->ale );
}

void thermo8_write_reg ( thermo8_t *ctx, uint8_t r_addr, uint16_t r_data )
{
   uint8_t r_buf[ 2 ];

   r_buf[ 0 ] = ( uint8_t )( ( r_data >> 8 ) & 0xFF );
   r_buf[ 1 ] = ( uint8_t )( r_data & 0xFF );

   thermo8_generic_write( ctx, r_addr, r_buf, 2 );
}

uint16_t thermo8_read_reg ( thermo8_t *ctx, uint8_t r_addr )
{
  uint8_t r_buf[ 2 ];
  
  thermo8_generic_read( ctx, r_addr, r_buf, 2 );

  return ( (uint16_t)r_buf[ 0 ] << 8 | r_buf[ 1 ] ) ;
}

void thermo8_write_reg_8 ( thermo8_t *ctx, uint8_t r_addr, uint8_t r_data)
{
    thermo8_generic_write( ctx, r_addr, &r_data, 1 );
}

uint8_t thermo8_read_reg_8 ( thermo8_t *ctx, uint8_t r_addr )
{
    uint8_t r_buf;

    thermo8_generic_write( ctx, r_addr, &r_buf, 1 );

    return r_buf;
}

float thermo8_get_temperature ( thermo8_t *ctx )
{
    float t_temp;
    uint16_t t_data;

    t_data = thermo8_read_reg( ctx, THERMO8_TA );
    ctx->limit_status = t_data;
    t_temp = b_to_t_conversion( t_data );
    return t_temp;
}

void thermo8_set_resolution ( thermo8_t *ctx, uint8_t r_cfg )
{
    uint8_t tmp;

    tmp = r_cfg & 0x03;
    thermo8_write_reg_8( ctx, THERMO8_RESOLUTION_REG, r_cfg );
}

uint16_t thermo8_get_dev_id ( thermo8_t *ctx )
{
    return thermo8_read_reg( ctx, THERMO8_DEVID );
}

uint16_t thermo8_get_man_id ( thermo8_t *ctx )
{
    return thermo8_read_reg( ctx, THERMO8_MANID );
}

void thermo8_sleep ( thermo8_t *ctx )
{
    uint16_t tmp;
  
    tmp = thermo8_read_reg( ctx, THERMO8_CONFIG );
    tmp |= 1 << 8;
    
    thermo8_write_reg( ctx, THERMO8_CONFIG, tmp ); 
    Delay_100ms( );
}

void thermo8_wake_up ( thermo8_t *ctx )
{
    uint16_t tmp;

    tmp = thermo8_read_reg( ctx, THERMO8_CONFIG );
    tmp &= ~( 1 << 8 );
    thermo8_write_reg( ctx, THERMO8_CONFIG, tmp );
    Delay_100ms( );                 
}

void thermo8_limit_set ( thermo8_t *ctx, uint8_t limit_reg_addr, float limit )
{
    float c_limit;
    uint16_t x_limit;
    
    c_limit = ( limit * 16.0 );
    x_limit = (uint16_t)c_limit;
    
    if( x_limit & 0x03 )
    {
       x_limit += 1;
    }
    
    thermo8_write_reg( ctx, limit_reg_addr, x_limit );
}

uint8_t thermo8_get_alert_stat ( thermo8_t *ctx )
{
    uint8_t alert_gen = 0;
    
    if( ctx->limit_status & 1 << 13 )
    {
      alert_gen |= THERMO8_TLOWER_REACHED;
    }
    if( ctx->limit_status & 1 << 14 )
    {
      alert_gen |= THERMO8_TUPPER_REACHED;
    }
    if( ctx->limit_status & 1 << 15 )
    {
      alert_gen |= THERMO8_TCRIT_REACHED;
    }
    
    return alert_gen;
}

void thermo8_alert_enable ( thermo8_t *ctx, uint8_t thys, uint8_t alert_cfg )
{
     uint16_t cfg;

     cfg = 0x0001 | 0x0008 | 0x0010 ;
     thys &= 0x03;
     
     if( THERMO8_TCRIT_ONLY_ALERT == alert_cfg )
     {
        cfg |= 0x0004;
     }
     else
     {
       cfg &= ~0x0004;
     }
     cfg |= ( thys << 9 );
     thermo8_write_reg( ctx, THERMO8_CONFIG, cfg );
}

void thermo8_tcrit_lock ( thermo8_t *ctx )
{
     uint16_t tmp;

     tmp = thermo8_read_reg( ctx, THERMO8_CONFIG );
     tmp |= 1 << 7;
     thermo8_write_reg( ctx, THERMO8_CONFIG, tmp );
}

void thermo8_tcrit_unlock ( thermo8_t *ctx )
{
     uint16_t tmp;
     tmp = thermo8_read_reg( ctx, THERMO8_CONFIG );
     tmp &= ~( 1 << 7 );
     thermo8_write_reg( ctx, THERMO8_CONFIG, tmp );
}

void thermo8_win_lock ( thermo8_t *ctx )
{
     uint16_t tmp;
     tmp = thermo8_read_reg( ctx, THERMO8_CONFIG );
     tmp |= 1 << 6;
     thermo8_write_reg( ctx, THERMO8_CONFIG, tmp );
}

void thermo8_win_unlock ( thermo8_t *ctx )
{
     uint16_t tmp;
     tmp = thermo8_read_reg( ctx, THERMO8_CONFIG );
     tmp &= ~( 1 << 6 );
     thermo8_write_reg( ctx, THERMO8_CONFIG, tmp );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float b_to_t_conversion ( uint16_t r_data )
{
    float t;
    uint8_t reg_upper = ( uint8_t )( r_data>>8 );
    uint8_t reg_lower = ( uint8_t )( r_data );
    
    reg_upper &= 0x1F;
    
    if( reg_upper & 0x10 )
    {
      reg_upper &= 0x0F;
      t = 256.0 - ( ( ( float )( reg_upper ) * 16.0 ) + ( ( float )( reg_lower ) / 16.0 ) );
    }
    else
    {
      t = ( ( ( float )( reg_upper ) * 16.0 ) + ( ( float )( reg_lower ) / 16.0 ) );
    }
    
    return t;
}

// ------------------------------------------------------------------------- END

