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

#include "irgesture.h"


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t compare_data ( uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3 );
static uint8_t get_mode ( irgesture_t *ctx );
static void set_mode ( irgesture_t *ctx, uint8_t mode, uint8_t enable );
static uint8_t process_gesture_data ( gesture_data_t *gesture_data );
static uint8_t decode_gesture ( gesture_data_t *gesture_data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void irgesture_cfg_setup ( irgesture_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = IRGESTURE_I2C_ADDR;
}

IRGESTURE_RETVAL irgesture_init ( irgesture_t *ctx, irgesture_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return IRGESTURE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );


    return IRGESTURE_OK;
}

void irgesture_default_cfg ( irgesture_t *ctx )
{
    uint8_t val;
    uint8_t drive;

    irgesture_write_data( ctx, IRGESTURE_ATIME, DEFAULT_ATIME );

    irgesture_write_data( ctx, IRGESTURE_WTIME, DEFAULT_WTIME );

    irgesture_write_data( ctx, IRGESTURE_PPULSE, DEFAULT_PROX_PPULSE );

    irgesture_write_data( ctx, IRGESTURE_POFFSET_UR, DEFAULT_POFFSET_UR );

    irgesture_write_data( ctx, IRGESTURE_POFFSET_DL, DEFAULT_POFFSET_DL );

    irgesture_write_data( ctx, IRGESTURE_CONFIG1, DEFAULT_CONFIG1 );

    irgesture_write_data( ctx, IRGESTURE_CONFIG1, DEFAULT_CONFIG1 );

    val = irgesture_read_data( ctx, IRGESTURE_CONTROL );
    drive = 0x00;
    drive &= 0x03;
    drive = drive << 6;
    val &= 0x3F;
    val |= drive;

    irgesture_write_data( ctx, IRGESTURE_CONTROL, val );

    val = irgesture_read_data( ctx, IRGESTURE_CONTROL );
    drive = 0x02;
    drive &= 0x03;
    drive = drive << 2;
    val &= 0xF3;
    val |= drive;

    irgesture_write_data( ctx, IRGESTURE_CONTROL, val );

    val = irgesture_read_data( ctx, IRGESTURE_CONTROL );
    drive = 0x01;
    drive &= 0x03;
    val &= 0xFC;
    val |= drive;

    irgesture_write_data( ctx, IRGESTURE_CONTROL, val );

    irgesture_write_data( ctx, IRGESTURE_PILT, 0x00 );

    irgesture_write_data( ctx, IRGESTURE_PIHT, 0x32 );

    irgesture_write_data( ctx, IRGESTURE_AILTL, 0xFF );

    irgesture_write_data( ctx, IRGESTURE_AILTH, 0x00 );

    irgesture_write_data( ctx, IRGESTURE_AIHTL, 0xFF );

    irgesture_write_data( ctx, IRGESTURE_AILTH, 0x00 );

    irgesture_write_data( ctx, IRGESTURE_PERS, 0x11 );

    irgesture_write_data( ctx, IRGESTURE_CONFIG2, 0x01 );

    irgesture_write_data( ctx, IRGESTURE_CONFIG3, 0x00 );

    irgesture_write_data( ctx, IRGESTURE_GPENTH, 0x28 );

    irgesture_write_data( ctx, IRGESTURE_GEXTH, 0x1E );

    irgesture_write_data( ctx, IRGESTURE_GCONF1,  0x40 );

    irgesture_write_data( ctx, IRGESTURE_GCONF1,  0x40 );

    val = irgesture_read_data( ctx, IRGESTURE_GCONF2 );
    val &= 0x9F;
    val |= 0x40;
    irgesture_write_data( ctx, IRGESTURE_GCONF2, val );

    val = irgesture_read_data( ctx, IRGESTURE_GCONF2 );
    val &= 0xE7;
    val |= 0x08;
    irgesture_write_data( ctx, IRGESTURE_GCONF2, val );

    val = irgesture_read_data( ctx, IRGESTURE_GCONF2 );
    val &= 0xF8;
    val |= 0x01;
    irgesture_write_data( ctx, IRGESTURE_GCONF2, val );

    irgesture_write_data( ctx, IRGESTURE_GOFFSET_U,  0x00 );

    irgesture_write_data( ctx, IRGESTURE_GOFFSET_D,  0x00 );

    irgesture_write_data( ctx, IRGESTURE_GOFFSET_L,  0x00 );

    irgesture_write_data( ctx, IRGESTURE_GOFFSET_R,  0x00 );

    irgesture_write_data( ctx, IRGESTURE_GPULSE,  0xC9 );

    irgesture_write_data( ctx, IRGESTURE_GCONF3,  0x00 );

    val = irgesture_read_data( ctx, IRGESTURE_GCONF4 );
    val &= 0xFD;
    val |= 0x02;
    irgesture_write_data( ctx, IRGESTURE_GCONF2, val );
    
    irgesture_enable_gesture_sensor( ctx );
}

void irgesture_write_data ( irgesture_t *ctx, uint8_t reg_addr, uint8_t write_data )
{
    uint8_t buffer[2];

    buffer[ 0 ] = reg_addr;
    buffer[ 1 ] = write_data;
    
    i2c_master_write( &ctx->i2c, buffer, 2 );   
}

uint8_t irgesture_read_data ( irgesture_t *ctx, uint8_t reg_addr )
{
    uint8_t read_reg[ 1 ];

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, read_reg, 1 );

    return read_reg[ 0 ];
}

uint8_t irgesture_get_interrupt ( irgesture_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

gesture_dir_t irgesture_gesture_read_gesture ( irgesture_t *ctx )
{
    gesture_data_t gesture_data;
    uint8_t fifo_count;
    uint8_t fifo_data[ 132 ];
    uint8_t fifo_addr[ 1 ];
    uint16_t i;
    uint8_t len;
    
    fifo_count = 0;
    fifo_addr[ 0 ] = IRGESTURE_GFIFO_U;

    if ( !irgesture_available( ctx ) || !( get_mode( ctx ) & 0x41 ) )
    {
        return DIR_NONE;
    }

    while ( 1 )
    {
        Delay_100ms();

        if ( irgesture_available( ctx ) )
        {
            fifo_count = irgesture_read_data( ctx, IRGESTURE_GFLVL );

            if ( fifo_count > 0 )
            {
                i2c_master_write_then_read( &ctx->i2c, &fifo_addr, 1, fifo_data, fifo_count * 4 );


                for ( i = 0; i < fifo_count; i += 4 )
                {
                    gesture_data.u_data[ gesture_data.index ] = fifo_data[ i ];
                    gesture_data.d_data[ gesture_data.index ] = fifo_data[ i + 1 ];
                    gesture_data.l_data[ gesture_data.index ] = fifo_data[ i + 2 ];
                    gesture_data.r_data[ gesture_data.index ] = fifo_data[ i + 3 ];
                    gesture_data.index++;
                    gesture_data.total_gestures++;
                }

                if ( !process_gesture_data( &gesture_data ) )
                {
                    if ( !decode_gesture( &gesture_data ) )
                    {

                    }
                }

                gesture_data.index = 0;
                gesture_data.total_gestures = 0;
            }
        } 
        else 
        {
            Delay_100ms();
            decode_gesture( &gesture_data );

            return gesture_data.motion;
        }
    }
}

void irgesture_set_gesture_mode ( irgesture_t *ctx )
{
    uint8_t val;

    val = irgesture_read_data( ctx, IRGESTURE_GCONF4 );

    val &= ~( 1 << 0 );

    val |= ( 1 << 0 );

    irgesture_write_data( ctx, IRGESTURE_GCONF4, val );
}

void irgesture_enable_power ( irgesture_t *ctx )
{
    set_mode( ctx, 0x00, 1 );
}

void irgesture_disable_power ( irgesture_t *ctx )
{
    set_mode( ctx, 0x00, 0 );
}

void irgesture_set_ambient_light_gain ( irgesture_t *ctx, uint8_t gain_val )
{
    uint8_t val;
    
    val = 0;

    val = irgesture_read_data( ctx, IRGESTURE_CONTROL );

    val &= ~( 1 << 0 ) | ( 1 << 1 );
    gain_val |= val;

    irgesture_write_data( ctx, IRGESTURE_CONTROL, gain_val );
}

uint8_t irgesture_get_ambient_light_gain ( irgesture_t *ctx )
{
    uint8_t val;

    val = 0;

    val = irgesture_read_data( ctx, IRGESTURE_CONTROL );

    val &= 0x03;

    return val;
}

void irgesture_enable_light_sensor ( irgesture_t *ctx )
{
    irgesture_set_ambient_light_gain( ctx, DEFAULT_AGAIN );

    irgesture_enable_power( ctx );
    
    set_mode( ctx, 0x01, 1 );
}

void irgesture_disable_light_sensor ( irgesture_t *ctx )
{
    irgesture_enable_power( ctx );

    set_mode( ctx, 0x01, 0 );
}

uint16_t irgesture_read_ambient_light ( irgesture_t *ctx )
{
    uint8_t buffer[ 2 ];
    uint16_t result;

    buffer[ 0 ] = irgesture_read_data( ctx, IRGESTURE_CDATAH );
    buffer[ 1 ] = irgesture_read_data( ctx, IRGESTURE_CDATAL );
    
    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

uint16_t irgesture_read_red_light ( irgesture_t *ctx )
{
    uint8_t buffer[ 2 ];
    uint16_t result;

    buffer[ 0 ] = irgesture_read_data( ctx, IRGESTURE_RDATAH );
    buffer[ 1 ] = irgesture_read_data( ctx, IRGESTURE_RDATAL );
    
    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

uint16_t irgesture_read_green_light ( irgesture_t *ctx )
{
    uint8_t buffer[ 2 ];
    uint16_t result;

    buffer[ 0 ] = irgesture_read_data( ctx, IRGESTURE_GDATAH );
    buffer[ 1 ] = irgesture_read_data( ctx, IRGESTURE_GDATAL );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

uint16_t irgesture_read_blue_light ( irgesture_t *ctx )
{
    uint8_t buffer[ 2 ];
    uint16_t result;

    buffer[ 0 ] = irgesture_read_data( ctx, IRGESTURE_BDATAH );
    buffer[ 1 ] = irgesture_read_data( ctx, IRGESTURE_BDATAL );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

void irgesture_set_led_boost ( irgesture_t *ctx, uint8_t boost )
{
    uint8_t val;

    val = 0;

    val = irgesture_read_data( ctx, IRGESTURE_CONFIG2 );

    val &= ~( 1 << 4 ) | ( 1 << 5 );
    
    boost = ( boost << 4 ) | val;

    irgesture_write_data( ctx, IRGESTURE_CONFIG2, boost );
}

uint8_t irgesture_get_led_boost ( irgesture_t *ctx )
{
    uint8_t val;

    val = irgesture_read_data( ctx, IRGESTURE_CONFIG2 );

    val = ( val >> 4 ) & 0x03;

    return val;
}

uint8_t irgesture_available ( irgesture_t *ctx )
{
    uint8_t val;

    val = 0;

    val = irgesture_read_data( ctx, IRGESTURE_GSTATUS );

    val &= IRGESTURE_GVALID;

    return ( val == 1 ) ? 1 : 0;
}

void irgesture_set_gesture_gain ( irgesture_t *ctx, uint8_t gain_val )
{
    uint8_t val;

    val = 0;

    val = irgesture_read_data( ctx, IRGESTURE_GCONF2 );

    val &= ~( 1 << 5 ) | ( 1 << 6 );

    gain_val = ( gain_val << 5 ) | val;

    irgesture_write_data( ctx, IRGESTURE_GCONF2, gain_val );
}

uint8_t irgesture_getesture_gain ( irgesture_t *ctx )
{
    uint8_t val;

    val = 0;

    val = irgesture_read_data( ctx, IRGESTURE_GCONF2 );

    val = ( val >> 5 ) & 0x03;

    return val;
}

void irgesture_enable_gesture_sensor ( irgesture_t *ctx )
{
    uint8_t temp;
    uint8_t val;
    
    temp = 0xFF;
    val = 0;
    
    irgesture_write_data( ctx, IRGESTURE_WTIME, 0xFF );
    
    temp = DEFAULT_GESTURE_PPULSE;
    
    irgesture_write_data( ctx, IRGESTURE_PPULSE, 0xFF );

    val = irgesture_read_data( ctx, IRGESTURE_GCONF4 );

    val &= ~( 1 << 1 );

    val |= ( 1 << 1 );

    irgesture_write_data( ctx, IRGESTURE_GCONF4, val );

    irgesture_set_gesture_mode( ctx );
    
    irgesture_enable_power( ctx );
    
    set_mode( ctx, 0x03, 1 );
    set_mode( ctx, 0x02, 1 );
    set_mode( ctx, 0x06, 1 );
}

void irgesture_disable_gesture_sensor ( irgesture_t *ctx )
{
    uint8_t val;
    
    val = 0;
    
    val = irgesture_read_data( ctx, IRGESTURE_GCONF4 );

    val &= ~( 1 << 0 );

    irgesture_write_data( ctx, IRGESTURE_GCONF4, val );
    
    set_mode( ctx, 0x06, 0 );
}

uint8_t irgesture_detect_gesture ( irgesture_t *ctx )
{
    uint8_t data_right;
    uint8_t data_left;
    uint8_t data_up;
    uint8_t data_down;
    uint8_t result;
    
    data_right = irgesture_read_data( ctx, IRGESTURE_GFIFO_R );
    data_left  = irgesture_read_data( ctx, IRGESTURE_GFIFO_L );
    data_up    = irgesture_read_data( ctx, IRGESTURE_GFIFO_U );
    data_down  = irgesture_read_data( ctx, IRGESTURE_GFIFO_D );
    
    result = compare_data( data_right, data_left, data_up, data_down );
    
    return result;
}

void irgesture_set_proximity_gain ( irgesture_t *ctx, uint8_t gain_val )
{
    uint8_t val;
    
    val = 0;

    val = irgesture_read_data( ctx, IRGESTURE_CONTROL );

    val &= ~( 1 << 2 ) | ( 1 << 3 );
    gain_val = ( gain_val << 2 ) | val;

    irgesture_write_data( ctx, IRGESTURE_CONTROL, gain_val );
}

uint8_t irgesture_get_proximity_gain ( irgesture_t *ctx )
{
    uint8_t result;

    result = 0;

    result = irgesture_read_data( ctx, IRGESTURE_CONTROL );

    result = ( result >> 2 ) & 0x03;

    return result;
}

void irgesture_enable_proximity_sensor ( irgesture_t *ctx )
{
    irgesture_set_proximity_gain( ctx, DEFAULT_PGAIN );

    irgesture_enable_power( ctx );
    
    set_mode( ctx, 0x02, 1 );
}

void irgesture_disable_proximity_sensor ( irgesture_t *ctx )
{
    irgesture_enable_power( ctx );

    set_mode( ctx, 0x02, 0 );
}

uint8_t irgesture_get_proxy_photo_mask ( irgesture_t *ctx )
{
    uint8_t result;

    result = 0;

    result = irgesture_read_data( ctx, IRGESTURE_CONFIG3 );

    result &= 0x0f;

    return result;
}

void irgesture_set_proxy_photo_mask ( irgesture_t *ctx, uint8_t mask )
{
    uint8_t val;

    val = 0;

    val = irgesture_read_data( ctx, IRGESTURE_CONFIG3 );

    val &= ~( 1 << 0 ) | ( 1 << 1 )| ( 1 << 2 )| ( 1 << 3 );
    mask |= val;

    irgesture_write_data( ctx, IRGESTURE_CONFIG3, mask );
}

uint8_t irgesture_read_proximity_data ( irgesture_t *ctx )
{
    uint8_t result;

    result = 0;

    result = irgesture_read_data( ctx, IRGESTURE_PDATA );

    return result;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t compare_data ( uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3 )
{
    uint8_t max_data;
    uint16_t sum_data;
    uint8_t result;
    uint8_t cnt;
    uint8_t temp[ 4 ];
    temp[ 0 ] = value0;
    temp[ 1 ] = value1;
    temp[ 2 ] = value2;
    temp[ 3 ] = value3;
    
    max_data = value0;
    sum_data = 0;
    result = 1;
    
    for ( cnt = 0; cnt < 4; cnt++ )
    {
        if ( max_data < temp [ cnt ] )
        {
            max_data = temp[ cnt ];
            result = cnt + 1;
        }
        
        sum_data += temp[ cnt ];
    }

    if ( sum_data > 1000 )
    {
        result = 5;
    }
    if ( max_data < 16 )
    {
        result = 0;
    } 

    return result;
}

static uint8_t get_mode ( irgesture_t *ctx )
{
    uint8_t enable_value;

    enable_value = irgesture_read_data( ctx, IRGESTURE_ENABLE );

    return enable_value;
}

static void set_mode ( irgesture_t *ctx, uint8_t mode, uint8_t enable )
{
    uint8_t reg_val = get_mode( ctx );

    if ( reg_val == IRGESTURE_INIT_ERROR )
    {
        return;
    }
    if ( mode == 0x07 )
    {
        reg_val = 0x00;
        if ( enable )
        {
            reg_val = 0x7F;
        }
    } 
    else 
    {
        reg_val &= ~( 1 << mode );

        if( enable )
            reg_val |= ( 1 << mode );
    }

    irgesture_write_data( ctx, IRGESTURE_ENABLE, reg_val );
}

static uint8_t process_gesture_data ( gesture_data_t *gesture_data )
{
    uint8_t u_first = 0;
    uint8_t d_first = 0;
    uint8_t l_first = 0;
    uint8_t r_first = 0;
    uint8_t u_last = 0;
    uint8_t d_last = 0;
    uint8_t l_last = 0;
    uint8_t r_last = 0;
    uint16_t ud_ratio_first;
    uint16_t lr_ratio_first;
    uint16_t ud_ratio_last;
    uint16_t lr_ratio_last;
    uint16_t ud_delta;
    uint16_t lr_delta;
    uint16_t i;

    if ( gesture_data->total_gestures <= 4 )
    {
        return -1;
    }

    if ( ( gesture_data->total_gestures <= 32 ) && ( gesture_data->total_gestures > 0 ) )
    {
        for ( i = 0; i < gesture_data->total_gestures; i++ )
        {
            if ( ( gesture_data->u_data[ i ] > 10 ) && ( gesture_data->d_data[i] > 10 ) && ( gesture_data->l_data[ i ] > 10 ) && ( gesture_data->r_data[ i ] > 10 ) )
            {
                u_first = gesture_data->u_data[ i ];
                d_first = gesture_data->d_data[ i ];
                l_first = gesture_data->l_data[ i ];
                r_first = gesture_data->r_data[ i ];
                break;
            }
        }

        if ( ( u_first == 0 ) || 
             ( d_first == 0 ) ||
             ( l_first == 0 ) || 
             ( r_first == 0 ) )
        {
            return -1;
        } 

        for ( i = gesture_data->total_gestures - 1; i >= 0; i-- )
        {
            if( ( gesture_data->u_data[ i ] > 10 ) && ( gesture_data->d_data[ i ] > 10 ) && ( gesture_data->l_data[ i ] > 10 ) && ( gesture_data->r_data[ i ] > 10 ) )
            {
                u_last = gesture_data->u_data[ i ];
                d_last = gesture_data->d_data[ i ];
                l_last = gesture_data->l_data[ i ];
                r_last = gesture_data->r_data[ i ];
                break;
            }
        }
    }

    ud_ratio_first = ( ( u_first - d_first ) * 100 ) / ( u_first + d_first );
    lr_ratio_first = ( ( l_first - r_first ) * 100 ) / ( l_first + r_first );
    ud_ratio_last = ( ( u_last - d_last ) * 100 ) / ( u_last + d_last );
    lr_ratio_last = ( ( l_last - r_last ) * 100 ) / ( l_last + r_last );

    ud_delta = ud_ratio_last - ud_ratio_first;
    lr_delta = lr_ratio_last - lr_ratio_first;

    gesture_data->ud_delta += ud_delta;
    gesture_data->lr_delta += lr_delta;

    if ( gesture_data->ud_delta >= 50 )
    {
        gesture_data->ud_count = 1;
    }
    else if ( gesture_data->ud_delta <= -50 )
    {
        gesture_data->ud_count = -1;
    }
    else
    {
        gesture_data->ud_count = 0;
    }

    if ( gesture_data->lr_delta >= 50 )
    {
        gesture_data->lr_count = 1;
    }
    else if ( gesture_data->lr_delta <= -50 )
    {
        gesture_data->lr_count = -1;
    }
    else
    {
        gesture_data->lr_count = 0;
    }

    if ( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 0 ) )
    {
        if ( ( ud_delta  < 20 ) && ( lr_delta < 20 ) )
        {
            if ( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
            {
                gesture_data->near_count++;
            }
            else if ( ( ud_delta != 0 ) || ( lr_delta != 0 ) )
            {
                gesture_data->far_count++;
            }

            if ( ( gesture_data->near_count >= 10 ) && ( gesture_data->far_count >= 2 ) )
            {
                if ( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
                {
                    gesture_data->state = NEAR_STATE;
                }
                else if ( ( ud_delta != 0 ) && ( lr_delta != 0 ) )
                {
                    gesture_data->state = FAR_STATE;
                }
                
                return 0;
            }
        }
    } 
    else 
    {
        if ( (  ud_delta < 20 ) && ( lr_delta < 20 ) )
        {
            if ( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
            {
                gesture_data->near_count++;
            }
            if ( gesture_data->near_count >= 10 )
            {
                gesture_data->ud_count = 0;
                gesture_data->lr_count = 0;
                gesture_data->ud_delta = 0;
                gesture_data->lr_delta = 0;
            }
        }
    }
    return -1;
}


static uint8_t decode_gesture ( gesture_data_t *gesture_data )
{
    if ( gesture_data->state == NEAR_STATE )
    {
        gesture_data->motion = DIR_NEAR;
        return 0;
    } 
    else if ( gesture_data->state == FAR_STATE )
    {
         gesture_data->motion = DIR_FAR;
         return 0;
    }

    if ( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 0 ) )
    {
        gesture_data->motion = DIR_UP;
    }
    else if ( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 0) )
    {
        gesture_data->motion = DIR_DOWN;
    }
    else if ( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 1) )
    {
        gesture_data->motion = DIR_RIGHT;
    }
    else if ( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == -1) )
    {
        gesture_data->motion = DIR_LEFT;
    }
    else if ( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 1) )
    {
        if ( gesture_data->ud_delta > gesture_data->lr_delta )
        {
            gesture_data->motion = DIR_UP;
        }
        else
        {
            gesture_data->motion = DIR_RIGHT;
        }
    }
    else if ( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == -1) )
    {
        if ( gesture_data->ud_delta > gesture_data->lr_delta )
        {
            gesture_data->motion = DIR_DOWN;
        }
        else
        {
            gesture_data->motion = DIR_LEFT;
        }
    }
    else if ( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == -1) )
    {
        if ( gesture_data->ud_delta > gesture_data->lr_delta )
        {
             gesture_data->motion = DIR_UP;
        }
        else
        {
            gesture_data->motion = DIR_LEFT;
        }
    }
    else if ( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 1) )
    {
        if ( gesture_data->ud_delta > gesture_data->lr_delta )
        {
            gesture_data->motion = DIR_DOWN;
        }
        else
        {
            gesture_data->motion = DIR_RIGHT;
        }
    }
    else
    {
        return -1;
    }

    return 0;
}

// ------------------------------------------------------------------------- END

