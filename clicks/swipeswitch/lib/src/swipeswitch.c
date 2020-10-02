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

#include "swipeswitch.h"


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void acknowledge_reset ( swipeswitch_t *ctx );
static void auto_tune ( swipeswitch_t *ctx ); 

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void swipeswitch_cfg_setup ( swipeswitch_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = SWIPESWITCH_DEVICE_SLAVE_ADDRESS;
}

SWIPESWITCH_RETVAL swipeswitch_init ( swipeswitch_t *ctx, swipeswitch_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SWIPESWITCH_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );

    return SWIPESWITCH_OK;
}

void swipeswitch_default_cfg ( swipeswitch_t *ctx )
{
    uint8_t resp;

    resp = swipeswitch_wait_for_ready( ctx);
    if ( resp )
    {
        acknowledge_reset( ctx );
        swipeswitch_set_report_rate_lp( ctx, 8 );
        swipeswitch_set_np_segment_rate( ctx, 6 );
        auto_tune( ctx );
    }
    swipeswitch_disable_halt_timeout( ctx );
    swipeswitch_disable_events( ctx, SWIPESWITCH_EVENTS_ALL );

    swipeswitch_set_touch_sensitivity( ctx, 48 );
    swipeswitch_set_prox_sensitivity( ctx, 2 );
    swipeswitch_set_tap_timer_limit( ctx, 50 );
    swipeswitch_set_tap_threshold( ctx, 35 );
    swipeswitch_set_swipe_timer_limit( ctx, 150 );
    swipeswitch_set_swipe_threshold( ctx, 50 );
    swipeswitch_set_event_mask( ctx, SWIPESWITCH_EVENT_SWIPE | 
                                     SWIPESWITCH_EVENT_TAP | 
                                     SWIPESWITCH_EVENT_TP );
    swipeswitch_go_to_event_mode( ctx ); 
}

void swipeswitch_generic_write ( swipeswitch_t *ctx, uint8_t reg, uint8_t len, uint8_t *data_buf )
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

void swipeswitch_generic_read ( swipeswitch_t *ctx, uint8_t reg, uint8_t len, uint8_t *data_buf )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}


uint8_t swipeswitch_wait_for_ready ( swipeswitch_t *ctx )
{
    uint16_t not_ready_count = 0 ;

    while ( digital_in_read( &ctx->rdy ) != 0 )
    {
        not_ready_count++;
        Delay_50us( );
        Delay_50us( );

        if ( ( not_ready_count % 1000 ) == 0 )
        {
            return 1;
        }
    }
    return 0;
}

void swipeswitch_disable_halt_timeout ( swipeswitch_t *ctx )
{
    uint8_t halt_time = 255;

    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_TIMEOUT_PERIODS, 1, &halt_time );
}

void swipeswitch_disable_events ( swipeswitch_t *ctx, uint8_t event )
{
    uint8_t transfer_bytes[ 1 ];

    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_EVENT_MASK, 1, transfer_bytes );
    transfer_bytes[ 0 ] |= event;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_EVENT_MASK, 1, transfer_bytes );
}

void swipeswitch_enable_events ( swipeswitch_t *ctx, uint8_t event )
{
    uint8_t transfer_bytes[ 1 ];

    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_EVENT_MASK, 1, transfer_bytes );
    transfer_bytes[ 0 ] &= ~( event );
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_EVENT_MASK, 1, transfer_bytes );
}

void swipeswitch_go_to_event_mode ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 2 ];

    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_PROXSETTINGS_01, 2, transfer_bytes );
    transfer_bytes[ 1 ] |=  SWIPESWITCH_EVENT_MODE;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_PROXSETTINGS_01, 2, transfer_bytes );
}

void swipeswitch_go_to_stream_mode ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 2 ];

    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_PROXSETTINGS_01, 2, transfer_bytes );
    transfer_bytes[ 1 ] &= ~( SWIPESWITCH_EVENT_MODE );
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_PROXSETTINGS_01, 2, transfer_bytes );
}

uint8_t swipeswitch_read_system_flags ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 1 ];
        
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_SYS_FLAGS, 1, transfer_bytes );
    return transfer_bytes[ 0 ];
}

uint8_t swipeswitch_read_events ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 2 ];
  
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_SYS_FLAGS, 2, transfer_bytes );
    return transfer_bytes[ 1 ];
}

uint8_t swipeswitch_read_gestures ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 1 ];

    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_TP_FLAGS, 1, transfer_bytes );
    return transfer_bytes[ 0 ];
}

uint8_t swipeswitch_read_trackpad_flags ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 1 ];
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_TP_FLAGS, 1, transfer_bytes );
    return transfer_bytes[ 0 ];
}

uint8_t swipeswitch_read_prox_byte ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 1 ];
   
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_CHANNEL_BYTES, 1, transfer_bytes );
    return transfer_bytes[ 0 ];
}

uint8_t swipeswitch_read_touch_byte ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 2 ];
  
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_CHANNEL_BYTES, 2, transfer_bytes );
    return transfer_bytes[ 1 ];
}

uint8_t swipeswitch_read_x_coordinate ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 1 ];
  
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_COORDINATES, 1, transfer_bytes );
    return transfer_bytes[ 0 ];
}

uint8_t swipeswitch_read_y_coordinate ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 2 ];
  
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_COORDINATES, 2, transfer_bytes );
    return transfer_bytes[ 1 ];
}

void swipeswitch_set_touch_sensitivity ( swipeswitch_t *ctx, uint8_t sensitivity )
{
    uint8_t transfer_bytes[ 8 ];
    int i;
  
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_THRESHOLDS_CH0, 1, transfer_bytes );
  
    for ( i=1; i<8; i++)
    {
        transfer_bytes[ i ] = sensitivity;
    }
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_THRESHOLDS_CH0, 8, transfer_bytes );
}


void swipeswitch_set_prox_sensitivity ( swipeswitch_t *ctx, uint8_t sensitivity )
{
    uint8_t transfer_bytes[ 1 ];
  
    transfer_bytes[ 0 ] = sensitivity;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_THRESHOLDS_CH0, 1, transfer_bytes );
}

void swipeswitch_set_event_mask ( swipeswitch_t *ctx, uint8_t event_mask )
{
    uint8_t transfer_bytes[ 1 ];
  
    transfer_bytes[ 0 ] = event_mask;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_EVENT_MASK, 1, transfer_bytes );
}

void swipeswitch_enable_channel ( swipeswitch_t *ctx, uint8_t channel )
{
   uint8_t transfer_bytes[ 2 ]; 
  
   swipeswitch_generic_read( ctx, SWIPESWITCH_REG_CHANNEL_SETTINGS, 2, transfer_bytes );
   transfer_bytes[ 1 ] |= ( 1 << channel );
   swipeswitch_generic_write( ctx, SWIPESWITCH_REG_CHANNEL_SETTINGS, 2, transfer_bytes );
}

void swipeswitch_disable_channel ( swipeswitch_t *ctx, uint8_t channel )
{
   uint8_t transfer_bytes[ 2 ]; 
 
   swipeswitch_generic_read( ctx, SWIPESWITCH_REG_CHANNEL_SETTINGS, 2, transfer_bytes );
   transfer_bytes[ 1 ] &= ~( 1 << channel );
   swipeswitch_generic_write( ctx, SWIPESWITCH_REG_CHANNEL_SETTINGS, 2, transfer_bytes );
}

uint16_t swipeswitch_read_channel ( swipeswitch_t *ctx, uint8_t read_data, uint8_t channel )
{
    uint8_t transfer_bytes[ 2 ];
    uint8_t read_address = read_data;
    uint8_t counts_low      = 0;
    uint8_t counts_high     = 0;
    uint16_t counts_return  = 0;


    read_address += channel;
    swipeswitch_generic_read( ctx, read_address, 2, transfer_bytes );
 
    counts_low = transfer_bytes[ 0 ];
    counts_high = transfer_bytes[ 1 ];
    counts_return = ( uint16_t )( counts_low );
    counts_return |= ( uint16_t )( counts_high << 8 );
 
    return counts_return;
}

void swipeswitch_set_tap_timer_limit ( swipeswitch_t *ctx, uint8_t time_limit )
{
    uint8_t transfer_bytes[ 1 ];
  
    transfer_bytes[ 0 ] = time_limit;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_TAP_SETTINGS, 1, transfer_bytes );
}

void swipeswitch_set_tap_threshold ( swipeswitch_t *ctx, uint8_t threshold )
{
    uint8_t transfer_bytes[ 2 ];

    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_TAP_SETTINGS, 1, transfer_bytes );
    transfer_bytes[ 1 ] = threshold;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_TAP_SETTINGS, 2, transfer_bytes );
}

void swipeswitch_set_swipe_timer_limit ( swipeswitch_t *ctx, uint8_t time_limit )
{
    uint8_t transfer_bytes[ 1 ];

    transfer_bytes[ 0 ] = time_limit;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_SWIPE_SETTINGS, 1, transfer_bytes );
}

void swipeswitch_set_swipe_threshold ( swipeswitch_t *ctx, uint8_t threshold )
{
    uint8_t transfer_bytes[ 2 ];
  
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_SWIPE_SETTINGS, 1, transfer_bytes );
    transfer_bytes[ 1 ] = threshold;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_SWIPE_SETTINGS, 2, transfer_bytes );
}

void swipeswitch_set_report_rate_nm ( swipeswitch_t *ctx, uint8_t report_rate )
{
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_REPORT_RATES, 1, &report_rate );
}

void swipeswitch_set_report_rate_lp ( swipeswitch_t *ctx, uint8_t report_rate )
{
    uint8_t transfer_bytes[ 2 ];

    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_REPORT_RATES, 1, transfer_bytes );
    transfer_bytes[ 1 ] = report_rate;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_REPORT_RATES, 2, transfer_bytes );
}

void swipeswitch_set_np_segment_rate ( swipeswitch_t *ctx, uint8_t segment_rate )
{
    uint8_t transfer_bytes[ 1 ];

    if ( segment_rate > 7 )
    {
        segment_rate = 7;
    }
    swipeswitch_generic_read ( ctx, SWIPESWITCH_REG_PROXSETTINGS_23, 1, transfer_bytes );
    transfer_bytes[ 0 ] &= 0xF8;
    transfer_bytes[ 0 ] |= segment_rate;
    swipeswitch_generic_write ( ctx, SWIPESWITCH_REG_PROXSETTINGS_23, 1, transfer_bytes );
}

void swipeswitch_set_zoom_timeout ( swipeswitch_t *ctx, uint8_t timeout_period )
{
    uint8_t transfer_bytes[ 2 ];

    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_EVENT_MASK, 1, transfer_bytes );
    transfer_bytes[ 1 ] = timeout_period;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_EVENT_MASK, 2, transfer_bytes );
}

void swipeswitch_set_halt_timeout ( swipeswitch_t *ctx, uint8_t halt_time )
{
    if ( halt_time > 127 )
    {
        halt_time = 254;
    }
    else if ( halt_time < 1 )
    {
        halt_time = 1;
    }
    else
    {
        halt_time += halt_time;
    }
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_TIMEOUT_PERIODS, 1, &halt_time );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void acknowledge_reset ( swipeswitch_t *ctx )
{
    uint8_t transfer_bytes[ 2 ];
        
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_PROXSETTINGS_23, 2, transfer_bytes );
    transfer_bytes[ 1 ] |= SWIPESWITCH_ACK_RESET;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_PROXSETTINGS_23, 2, transfer_bytes );
}

static void auto_tune ( swipeswitch_t *ctx ) 
{
    uint8_t transfer_byte[ 1 ];
  
    swipeswitch_generic_read( ctx, SWIPESWITCH_REG_PROXSETTINGS_01, 1, transfer_byte );
    transfer_byte[ 0 ] |= SWIPESWITCH_REDO_ATI;
    swipeswitch_generic_write( ctx, SWIPESWITCH_REG_PROXSETTINGS_01, 1, transfer_byte );
}

// ------------------------------------------------------------------------- END

