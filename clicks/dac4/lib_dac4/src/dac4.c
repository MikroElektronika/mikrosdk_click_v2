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

#include "dac4.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dac4_cfg_setup ( dac4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->lda = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = DAC4_DEVICE_ADDRESS;
}

err_t dac4_init ( dac4_t *ctx, dac4_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    // Output pins 
    digital_out_init( &ctx->lda, cfg->lda );

    // Input pins
    digital_in_init( &ctx->rdy, cfg->rdy );

    return DAC4_OK;
}

void dac4_generic_write ( dac4_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, data_buf, len );  
}

void dac4_generic_read ( dac4_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_read( &ctx->i2c, data_buf, len );  
}

uint8_t dac4_int_get ( dac4_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

void dac4_pwm_set ( dac4_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->lda, pin_state );
}

uint8_t dac4_general_call_reset ( dac4_t *ctx )
{
    uint8_t aux_buf[ 2 ];

    aux_buf[ 0 ] = 0x00;
    aux_buf[ 1 ] = 0x06;
    
    dac4_generic_write( ctx, aux_buf, 2 );
    
    return 0;
}

uint8_t dac4_general_call_wake_up ( dac4_t *ctx )
{
    uint8_t aux_buf[ 2 ];

    aux_buf[ 0 ] = 0x00;
    aux_buf[ 1 ] = 0x09;
    
    dac4_generic_write( ctx, aux_buf, 2 );

    return 0;
}

uint8_t dac4_general_call_software_update ( dac4_t *ctx )
{
    uint8_t aux_buf[ 2 ];

    aux_buf[ 0 ] = 0x00;
    aux_buf[ 1 ] = 0x08;
    
    dac4_generic_write( ctx, aux_buf, 2 );

    return 0;
}

uint8_t dac4_fast_write ( dac4_t *ctx, dac4_channel_t *channels )
{
    uint8_t aux_buf[ 8 ];
    uint8_t i;
    
    if ( channels->channel_a.channel_select > 3 ) 
    {
        return 1;
    }
    if ( channels->channel_b.channel_select > 3 ) 
    {
        return 1;
    }
    if ( channels->channel_c.channel_select > 3 ) 
    {
        return 1;
    }
    if ( channels->channel_d.channel_select > 3 ) 
    {
        return 1;
    }

    if ( channels->channel_a.udac_bit > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_b.udac_bit > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_c.udac_bit > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_d.udac_bit > 1 ) 
    {
        return 1;
    }
    
    if ( channels->channel_a.voltage_reference > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_b.voltage_reference > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_c.voltage_reference > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_d.voltage_reference > 1 ) 
    {
        return 1;
    }
    
    if ( channels->channel_a.power_mode > 3 ) 
    {
        return 1;
    }
    if ( channels->channel_b.power_mode > 3 ) 
    {
        return 1;
    }
    if ( channels->channel_c.power_mode > 3 ) 
    {
        return 1;
    }
    if ( channels->channel_d.power_mode > 3 ) 
    {
        return 1;
    }
    
    if ( channels->channel_a.gain_value > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_b.gain_value > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_c.gain_value > 1 ) 
    {
        return 1;
    }
    if ( channels->channel_d.gain_value > 1 ) 
    {
        return 1;
    }

    if ( channels->channel_a.dac_input_data > 4095 ) 
    {
        return 1;
    }
    if ( channels->channel_b.dac_input_data > 4095 ) 
    {
        return 1;
    }
    if ( channels->channel_c.dac_input_data > 4095 ) 
    {
        return 1;
    }
    if ( channels->channel_d.dac_input_data > 4095 ) 
    {
        return 1;
    }
     
    for ( i = 0; i < 8; i ++ )
    {
        aux_buf[ i ] = 0;
    }
    
    channels->channel_a.power_mode <<= 4;
    channels->channel_b.power_mode <<= 4;
    channels->channel_c.power_mode <<= 4;
    channels->channel_d.power_mode <<= 4;
    
    aux_buf[ 0 ] |= ( uint8_t ) ( channels->channel_a.dac_input_data >> 8 );
    aux_buf[ 0 ] |= ( uint8_t ) ( channels->channel_a.power_mode );
    aux_buf[ 1 ] |= ( uint8_t ) ( channels->channel_a.dac_input_data >> 0 );
    aux_buf[ 2 ] |= ( uint8_t ) ( channels->channel_b.dac_input_data >> 8 );
    aux_buf[ 2 ] |= ( uint8_t ) ( channels->channel_b.power_mode );
    aux_buf[ 3 ] |= ( uint8_t ) ( channels->channel_b.dac_input_data >> 0 );
    aux_buf[ 4 ] |= ( uint8_t ) ( channels->channel_c.dac_input_data >> 8 );
    aux_buf[ 4 ] |= ( uint8_t ) ( channels->channel_c.power_mode );
    aux_buf[ 5 ] |= ( uint8_t ) ( channels->channel_c.dac_input_data >> 0 );
    aux_buf[ 6 ] |= ( uint8_t ) ( channels->channel_d.dac_input_data >> 8 );
    aux_buf[ 6 ] |= ( uint8_t ) ( channels->channel_d.power_mode );
    aux_buf[ 7 ] |= ( uint8_t ) ( channels->channel_d.dac_input_data >> 0 );
    
    dac4_generic_write( ctx, aux_buf, 8 );
    
    return 0;
}

uint8_t dac4_multi_write ( dac4_t *ctx, dac4_channel_setting_t *channel_buffer, uint8_t n_channels )
{
    uint8_t aux_buf[ 12 ];
    uint8_t aux_count;
    uint8_t i;
    uint8_t j;
    
    if ( n_channels > 4 ) 
    {
        return 1;
    }
    
    for ( i = 0; i < 12; i ++ )
    {
        aux_buf[ i ] = 0;
    }
    
    aux_count = 0;
    
    for ( i = 0; i < n_channels; i ++ )
    {
        if ( channel_buffer[ i ].channel_select > 3 )    
        {
            return 1;
        }
        if ( channel_buffer[ i ].udac_bit > 1 )          
        {
            return 1;
        }
        if ( channel_buffer[ i ].voltage_reference > 1 ) 
        {
            return 1;
        }
        if ( channel_buffer[ i ].power_mode > 3 )        
        {
            return 1;
        }
        if ( channel_buffer[ i ].gain_value > 1 )        
        {
            return 1;
        }
        if ( channel_buffer[ i ].dac_input_data > 4095 ) 
        {
            return 1;
        }
    }
    
    for ( i = 0; i < n_channels; i ++ )
    {
        channel_buffer[ i ].channel_select <<= 1;
        channel_buffer[ i ].udac_bit <<= 0;
        channel_buffer[ i ].voltage_reference <<= 7;
        channel_buffer[ i ].power_mode <<= 5;
        channel_buffer[ i ].gain_value <<= 4;
        channel_buffer[ i ].dac_input_data <<= 0;
    }
    
    j = 0;
    
    for ( i = 0; i < n_channels; i ++ )
    {
        aux_buf[ j ] |= 0x40;
        aux_buf[ j ] |= channel_buffer[ i ].channel_select;
        aux_buf[ j ] |= channel_buffer[ i ].udac_bit;
        j++;
        aux_buf[ j ] |= channel_buffer[ i ].voltage_reference;
        aux_buf[ j ] |= channel_buffer[ i ].power_mode;
        aux_buf[ j ] |= channel_buffer[ i ].gain_value;
        aux_buf[ j ] |= ( uint8_t ) ( channel_buffer[ i ].dac_input_data >> 8 );
        j++;
        aux_buf[ j ] |= ( uint8_t ) ( channel_buffer[ i ].dac_input_data >> 0 );
        j++;
    }
    
    aux_count = n_channels * 3;
    
    dac4_generic_write( ctx, aux_buf, aux_count );

    return 0;
}

uint8_t dac4_sequential_write ( dac4_t *ctx, uint8_t starting_channel, dac4_channel_setting_t *channel_buffer )
{
    uint8_t aux_buf[ 9 ];
    uint8_t aux_count;
    uint8_t i;
    uint8_t j;

    if ( starting_channel > 3 ) 
    {
        return 1;
    }

    for ( i = 0; i < 9; i ++ )
    {
        aux_buf[ i ] = 0;
    }

    aux_count = 4;
    aux_count -= starting_channel;

    for ( i = 0; i < aux_count; i ++ )
    {
        if ( channel_buffer[ i ].channel_select > 3 )    
        {
            return 1;
        }
        if ( channel_buffer[ i ].udac_bit > 1 )          
        {
            return 1;
        }
        if ( channel_buffer[ i ].voltage_reference > 1 ) 
        {
            return 1;
        }
        if ( channel_buffer[ i ].power_mode > 3 )        
        {
            return 1;
        }
        if ( channel_buffer[ i ].gain_value > 1 )        
        {
            return 1;
        }
        if ( channel_buffer[ i ].dac_input_data > 4095 ) 
        {
            return 1;
        }
    }

    for ( i = 0; i < aux_count; i ++ )
    {
        channel_buffer[ i ].channel_select <<= 1;
        channel_buffer[ i ].udac_bit <<= 0;
        channel_buffer[ i ].voltage_reference <<= 7;
        channel_buffer[ i ].power_mode <<= 5;
        channel_buffer[ i ].gain_value <<= 4;
        channel_buffer[ i ].dac_input_data <<= 0;
    }

    i = 0;
    j = 0;
    
    starting_channel <<= 1;
    
    aux_buf[ j ] |= 0x50;
    aux_buf[ j ] |= starting_channel;
    aux_buf[ j ] |= channel_buffer[ i ].udac_bit;

    j++;

    for ( i = 0; i < aux_count; i ++ )
    {
        aux_buf[ j ] |= channel_buffer[ i ].voltage_reference;
        aux_buf[ j ] |= channel_buffer[ i ].power_mode;
        aux_buf[ j ] |= channel_buffer[ i ].gain_value;
        aux_buf[ j ] |= ( uint8_t ) ( channel_buffer[ i ].dac_input_data >> 8 );
        j++;
        aux_buf[ j ] |= ( uint8_t ) ( channel_buffer[ i ].dac_input_data >> 0 );
        j++;
    }

    aux_count *= 2;
    aux_count += 1;

    dac4_generic_write( ctx, aux_buf, aux_count );

    return 0;
}

uint8_t dac4_single_write ( dac4_t *ctx, dac4_channel_setting_t *channel_x )
{
    uint8_t aux_buf[ 3 ];
    uint8_t i;

    if ( channel_x[ 0 ].channel_select > 3 )    
    
    {
        return 1;
    }
    if ( channel_x[ 0 ].udac_bit > 1 )          
    
    {
        return 1;
    }
    if ( channel_x[ 0 ].voltage_reference > 1 ) 
    
    {
        return 1;
    }
    if ( channel_x[ 0 ].power_mode > 3 )        
    
    {
        return 1;
    }
    if ( channel_x[ 0 ].gain_value > 1 )        
    
    {
        return 1;
    }
    if ( channel_x[ 0 ].dac_input_data > 4095 ) 
    
    {
        return 1;
    }
    
    for ( i = 0; i < 3; i ++ )
    {
        aux_buf[ i ] = 0;
    }

    channel_x[ 0 ].channel_select <<= 1;
    channel_x[ 0 ].udac_bit <<= 0;
    channel_x[ 0 ].voltage_reference <<= 7;
    channel_x[ 0 ].power_mode <<= 5;
    channel_x[ 0 ].gain_value <<= 4;
    channel_x[ 0 ].dac_input_data <<= 0;

    aux_buf[ 0 ] |= ( uint8_t ) ( 0x58 );
    
    aux_buf[ 0 ] |= ( uint8_t ) ( channel_x[ 0 ].channel_select );
    aux_buf[ 0 ] |= ( uint8_t ) ( channel_x[ 0 ].udac_bit );
    aux_buf[ 1 ] |= ( uint8_t ) ( channel_x[ 0 ].voltage_reference );
    aux_buf[ 1 ] |= ( uint8_t ) ( channel_x[ 0 ].power_mode );
    aux_buf[ 1 ] |= ( uint8_t ) ( channel_x[ 0 ].gain_value );
    aux_buf[ 1 ] |= ( uint8_t ) ( channel_x[ 0 ].dac_input_data >> 8 );
    aux_buf[ 2 ] |= ( uint8_t ) ( channel_x[ 0 ].dac_input_data >> 0 );

    dac4_generic_write( ctx, aux_buf, 3 );

    return 0;
}

uint8_t dac4_voltage_reference_set ( dac4_t *ctx, dac4_v_ref_channels_t *vref )
{
    uint8_t temp;
    
    if ( vref->channel_a > 1 ) 
    {
        return 1;
    }
    if ( vref->channel_b > 1 ) 
    {
        return 1;
    }
    if ( vref->channel_c > 1 ) 
    {
        return 1;
    }
    if ( vref->channel_d > 1 ) 
    {
        return 1;
    }

    temp = 0x80;
    
    if ( vref->channel_a == 1 ) 
    {
        temp |= 0x08;
    }
    if ( vref->channel_b == 1 ) 
    {
        temp |= 0x04;
    }
    if ( vref->channel_c == 1 ) 
    {
        temp |= 0x02;
    }
    if ( vref->channel_d == 1 ) 
    {
        temp |= 0x01;
    }
    
    dac4_generic_write( ctx, &temp, 1 );

    return 0;
}

uint8_t dac4_power_mode_set ( dac4_t *ctx, dac4_pm_channels_t *pm  )
{
    uint8_t aux_buf[ 2 ];

    if ( pm->channel_a > 3 ) 
    {
        return 1;
    }
    if ( pm->channel_b > 3 ) 
    {
        return 1;
    }
    if ( pm->channel_c > 3 ) 
    {
        return 1;
    }
    if ( pm->channel_d > 3 ) 
    {
        return 1;
    }

    aux_buf[ 0 ] = 0xA0;
    aux_buf[ 1 ] = 0x00;
    
    switch ( pm->channel_a )
    {
        case DAC4_MODE_NORMAL:
        {
            aux_buf[ 0 ] |= DAC4_MODE_NORMAL << 2;
        break;
        }
        case DAC4_MODE_1kOhm:
        {
            aux_buf[ 0 ] |= DAC4_MODE_1kOhm << 2;
        break;
        }
        case DAC4_MODE_100kOhm:
        {
            aux_buf[ 0 ] |= DAC4_MODE_100kOhm << 2;
        break;
        }
        case DAC4_MODE_500kOhm:
        {
            aux_buf[ 0 ] |= DAC4_MODE_500kOhm << 2;
        break;
        }
        default :
        {
            return 1;
        break;
        }
    }
    
    switch ( pm->channel_b )
    {
        case DAC4_MODE_NORMAL:
        {
            aux_buf[ 0 ] |= DAC4_MODE_NORMAL << 0;
        break;
        }
        case DAC4_MODE_1kOhm:
        {
            aux_buf[ 0 ] |= DAC4_MODE_1kOhm << 0;
        break;
        }
        case DAC4_MODE_100kOhm:
        {
            aux_buf[ 0 ] |= DAC4_MODE_100kOhm << 0;
        break;
        }
        case DAC4_MODE_500kOhm:
        {
            aux_buf[ 0 ] |= DAC4_MODE_500kOhm << 0;
        break;
        }
        default :
        {
            return 1;
        break;
        }
    }
    
    switch ( pm->channel_c ) 
    {
        case DAC4_MODE_NORMAL:
        {
            aux_buf[ 1 ] |= DAC4_MODE_NORMAL << 6;
        break;
        }
        case DAC4_MODE_1kOhm:
        {
            aux_buf[ 1 ] |= DAC4_MODE_1kOhm << 6;
        break;
        }
        case DAC4_MODE_100kOhm:
        {
            aux_buf[ 1 ] |= DAC4_MODE_100kOhm << 6;
        break;
        }
        case DAC4_MODE_500kOhm:
        {
            aux_buf[ 1 ] |= DAC4_MODE_500kOhm << 6;
        break;
        }
        default :
        {
            return 1;
        break;
        }
    }
    
    switch ( pm->channel_d )
    {
        case DAC4_MODE_NORMAL:
        {
            aux_buf[ 1 ] |= DAC4_MODE_NORMAL << 4;
        break;
        }
        case DAC4_MODE_1kOhm:
        {
            aux_buf[ 1 ] |= DAC4_MODE_1kOhm << 4;
        break;
        }
        case DAC4_MODE_100kOhm:
        {
            aux_buf[ 1 ] |= DAC4_MODE_100kOhm << 4;
        break;
        }
        case DAC4_MODE_500kOhm:
        {
            aux_buf[ 1 ] |= DAC4_MODE_500kOhm << 4;
        break;
        }
        default :
        {
            return 1;
        break;
        }
    }

    dac4_generic_write( ctx, aux_buf, 2 );

    return 0;
}

uint8_t dac4_gain_set ( dac4_t *ctx, dac4_gain_channels_t *gain )
{
    uint8_t temp;

    if ( gain->channel_a > 1 ) 
    {
        return 1;
    }
    if ( gain->channel_b > 1 ) 
    {
        return 1;
    }
    if ( gain->channel_c > 1 ) 
    {
        return 1;
    }
    if ( gain->channel_d > 1 ) 
    {
        return 1;
    }

    temp = 0xC0;

    if ( gain->channel_a == 1 ) 
    {
        temp |= 0x08;
    }
    if ( gain->channel_b == 1 ) 
    {
        temp |= 0x04;
    }
    if ( gain->channel_c == 1 ) 
    {
        temp |= 0x02;
    }
    if ( gain->channel_d == 1 ) 
    {
        temp |= 0x01;
    }

    dac4_generic_write( ctx, &temp, 1 );

    return 0;
}

uint8_t dac4_data_report( dac4_t *ctx, dac4_channel_setting_t *channel_buffer )
{
    uint8_t out_buf[ 24 ];
    uint8_t i;
    uint8_t j;
    
    for ( i = 0; i < 24; i ++ ) 
    {
        out_buf[ i ] = 0;
    }
    
    for ( i = 0; i < 8; i ++ )
    {
        channel_buffer[ i ].rdy_bit = 0;
        channel_buffer[ i ].por_bit = 0;
        channel_buffer[ i ].channel_select = 0;
        channel_buffer[ i ].udac_bit = 0;
        channel_buffer[ i ].voltage_reference = 0;
        channel_buffer[ i ].power_mode = 0;
        channel_buffer[ i ].gain_value = 0;
        channel_buffer[ i ].dac_input_data = 0;
    }
    
    dac4_generic_read( ctx, out_buf, 24 );
    
    j = 0;
    
    for ( i = 0; i < 8; i ++ )
    {
        channel_buffer[ i ].rdy_bit = out_buf[ j ];
        channel_buffer[ i ].rdy_bit >>= 7;
        channel_buffer[ i ].rdy_bit &= 0x01;

        channel_buffer[ i ].por_bit = out_buf[ j ];
        channel_buffer[ i ].por_bit >>= 6;
        channel_buffer[ i ].por_bit &= 0x01;

        channel_buffer[ i ].channel_select = out_buf[ j ];
        channel_buffer[ i ].channel_select >>= 4;
        channel_buffer[ i ].channel_select &= 0x03;
        
        j++;

        channel_buffer[ i ].voltage_reference = out_buf[ j ];
        channel_buffer[ i ].voltage_reference >>= 7;
        channel_buffer[ i ].voltage_reference &= 0x01;

        channel_buffer[ i ].power_mode = out_buf[ j ];
        channel_buffer[ i ].power_mode >>= 5;
        channel_buffer[ i ].power_mode &= 0x03;

        channel_buffer[ i ].gain_value = out_buf[ j ];
        channel_buffer[ i ].gain_value >>= 4;
        channel_buffer[ i ].gain_value &= 0x01;

        channel_buffer[ i ].dac_input_data = out_buf[ j ];
        channel_buffer[ i ].dac_input_data &= 0x0F;
        channel_buffer[ i ].dac_input_data <<= 8;
        
        j++;

        channel_buffer[ i ].dac_input_data |= out_buf[ j ];
        
        j++;
    }
    
    return 0;
}

// ------------------------------------------------------------------------- END

