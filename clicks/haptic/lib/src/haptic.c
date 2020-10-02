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

#include "haptic.h"

void haptic_cfg_setup ( haptic_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->cs  = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HAPTIC_I2C_ADDRESS;
}

HAPTIC_RETVAL haptic_init ( haptic_t *ctx, haptic_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HAPTIC_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return HAPTIC_OK;
}

void haptic_generic_write ( haptic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void haptic_generic_read ( haptic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void haptic_enable (  haptic_t *ctx )
{   
    digital_out_high( &ctx->cs );
}

void haptic_disable ( haptic_t *ctx )
{   
    digital_out_low( &ctx->cs );
}

void haptic_write_byte (  haptic_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t write_buffer[ 1 ];
    
    write_buffer[ 0 ] = write_data;
    
    haptic_generic_write( ctx, reg_address, write_buffer, 1);
}

uint8_t haptic_read_byte ( haptic_t *ctx, uint8_t reg_address )
{
    uint8_t read_buffer[ 1 ];

    haptic_generic_read( ctx, reg_address, read_buffer, 1 );
    
    return read_buffer[ 0 ];
}

void haptic_set_mode ( haptic_t *ctx, uint8_t sel_mode )
{
    switch ( sel_mode )
    {
        case 0:
        {
            haptic_write_byte( ctx, HAPTIC_REG_MODE, HAPTIC_MODE_INTTRIG );
            break;
        }
        case 1:
        {
            haptic_write_byte( ctx, HAPTIC_REG_MODE, HAPTIC_MODE_EXTTRIGEDGE );
            break;
        }
        case 2:
        {
            haptic_write_byte( ctx, HAPTIC_REG_MODE, HAPTIC_MODE_EXTTRIGLVL );
            break;
        }
        case 3:
        {
            haptic_write_byte( ctx, HAPTIC_REG_MODE, HAPTIC_MODE_PWMANALOG );
            break;
        }
        case 4:
        {
            haptic_write_byte( ctx, HAPTIC_REG_MODE, HAPTIC_MODE_AUDIOVIBE );
            break;
        }
        case 5:
        {
            haptic_write_byte( ctx, HAPTIC_REG_MODE, HAPTIC_MODE_REALTIME );
            break;
        }
        case 6:
        {
            haptic_write_byte( ctx, HAPTIC_REG_MODE, HAPTIC_MODE_DIAGNOS );
            break;
        }
        case 7:
        {
            haptic_write_byte( ctx, HAPTIC_REG_MODE, HAPTIC_MODE_AUTOCAL );
            break;
        }
    }
}

void haptic_soft_reset ( haptic_t *ctx )
{
    haptic_write_byte( ctx, HAPTIC_REG_MODE, 0x80 );
}

uint8_t haptic_get_status ( haptic_t *ctx )
{
    uint8_t temp;
    
    temp = haptic_read_byte( ctx, HAPTIC_REG_STATUS );
    
    return temp;
}

void haptic_set_rtp_input ( haptic_t *ctx, uint8_t input )
{
    haptic_write_byte( ctx, HAPTIC_REG_RTPIN, input );
}

void haptic_set_state_hi ( haptic_t *ctx )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_LIBRARY );
    
    read_temp |= ( 1 << 7 );
    
    haptic_write_byte( ctx, HAPTIC_REG_LIBRARY, read_temp );
}

uint8_t haptic_set_library ( haptic_t *ctx, uint8_t library )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_LIBRARY );

    read_temp &= 0xF8;

    switch ( library )
    {
        case 0:
        {
            read_temp &= 0xF8;
            break;
        }
        case 1:
        {
            read_temp |= 0x01;
            break;
        }
        case 2:
        {
            read_temp |= 0x02;
            break;
        }
        case 3:
        {
            read_temp |= 0x03;
            break;
        }
        case 4:
        {
            read_temp |= 0x04;
            break;
        }
        case 5:
        {
            read_temp |= 0x05;
            break;
        }
        case 6:
        {
            read_temp |= 0x06;
            break;
        }
    }

    haptic_write_byte( ctx, HAPTIC_REG_LIBRARY, read_temp );
    
    return 1;
}

void haptic_start_motor ( haptic_t *ctx )
{
    haptic_write_byte( ctx, HAPTIC_REG_GO, 0x01 );
}

void haptic_set_overdrive_offset ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_OVERDRIVE, temp_data );
}

void haptic_set_sustain_offset_positive ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_SUSTAINPOS, temp_data );
}

void haptic_set_sustain_offset_negative ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_SUSTAINNEG, temp_data );
}

void haptic_set_brake_time_offset ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_BREAK, temp_data );
}

void haptic_set_audio_minimum_input ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_AUDIOMININ, temp_data );
}

void haptic_set_audio_maximum_input ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_AUDIOMAXIN, temp_data );
}

void haptic_set_audio_minimum_output ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_AUDIOMINOUT, temp_data );
}

void haptic_set_audio_maximum_output ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_AUDIOMAXOUT, temp_data );
}

void haptic_set_rated_voltage ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_RATEDV, temp_data );
}

void haptic_set_overdrive_clamp_voltage ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_CLAMPV, temp_data );
}

uint8_t haptic_set_audio_peak_time ( haptic_t *ctx, uint8_t temp_data )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_AUDIOCTRL );
    
    switch ( temp_data )
    {
        case 0:
        {
            read_temp &= ~1;
            haptic_write_byte( ctx, HAPTIC_REG_AUDIOCTRL, read_temp );
            break;
        }
        case 1:
        {
            read_temp |= ( 1 << 2 );
            haptic_write_byte( ctx, HAPTIC_REG_AUDIOCTRL, read_temp );
            break;
        }
        case 2:
        {
            read_temp |= ( 1 << 3 );
            haptic_write_byte( ctx, HAPTIC_REG_AUDIOCTRL, read_temp );
            break;
        }
        case 3:
        {
            read_temp |= ( 1 << 3 );
            read_temp |= ( 1 << 2 );
            haptic_write_byte( ctx, HAPTIC_REG_AUDIOCTRL, read_temp );
            break;
        }
        default:
        {
            return -1;
        }
    }
    return 0;
}

uint8_t haptic_set_audio_low_pass_filter ( haptic_t *ctx, uint8_t temp_data )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_AUDIOCTRL );

    switch ( temp_data )
    {
        case 0:
        {
            read_temp &= ~1;
            haptic_write_byte( ctx, HAPTIC_REG_AUDIOCTRL, read_temp );
            break;
        }
        case 1:
        {
            read_temp |= 1;
            haptic_write_byte( ctx, HAPTIC_REG_AUDIOCTRL, read_temp );
            break;
        }
        case 2:
        {
            read_temp |= ( 1 << 1 );
            haptic_write_byte( ctx, HAPTIC_REG_AUDIOCTRL, read_temp );
            break;
        }
        case 3:
        {
            read_temp |= ( 1 << 1 );
            read_temp |= ( 1 << 2 );
            haptic_write_byte( ctx, HAPTIC_REG_AUDIOCTRL, read_temp );
            break;
        }
        default:
        {
            return -1;
        }
    }
    return 0;
}

uint8_t haptic_get_calibration_result_comp ( haptic_t *ctx )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_AUTOCALCOMP );
    
    return read_temp;
}

uint8_t haptic_get_calibration_result_emf ( haptic_t *ctx )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte (ctx,  HAPTIC_REG_AUTOCALEMF );
    
    return read_temp;
}

uint8_t haptic_get_supply_voltage_value ( haptic_t *ctx )
{
    uint8_t temp_read;
    
    temp_read = haptic_read_byte( ctx, HAPTIC_REG_VBAT );
    
    return temp_read;
}

uint8_t haptic_get_lra_resonance_period ( haptic_t *ctx )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_LRARESON );
    
    return read_temp;
}

void haptic_set_to_erm_mode ( haptic_t *ctx )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_FEEDBACK );
    
    read_temp &= ~( 1 << 7 );
    
    haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
}

void haptic_set_to_lra_mode ( haptic_t *ctx )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_FEEDBACK );
    
    read_temp |= ( 1 << 7 );
    
    haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
}

uint8_t haptic_setBrakeFactor( haptic_t *ctx, uint8_t brake_factor )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_FEEDBACK );

    switch ( brake_factor )
    {
        case 1:
        {
            read_temp &= ~( 1 << 4 );
            read_temp &= ~( 1 << 5 );
            read_temp &= ~( 1 << 6 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 2:
        {
            read_temp |= ( 1 << 4 );
            read_temp &= ~( 1 << 5 );
            read_temp &= ~( 1 << 6 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 3:
        {
            read_temp &= ~( 1 << 4 );
            read_temp |=  ( 1 << 5 );
            read_temp &= ~( 1 << 6 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 4:
        {
            read_temp |= ( 1 << 4 );
            read_temp |= ( 1 << 5 );
            read_temp &= ~( 1 << 6 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 6:
        {
            read_temp &= ~( 1 << 4 );
            read_temp &= ~( 1 << 5 );
            read_temp |= ( 1 << 6 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 8:
        {
            read_temp |= ( 1 << 4 );
            read_temp &= ~( 1 << 5 );
            read_temp |= ( 1 << 6 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 16:
        {
            read_temp &= ~( 1 << 4 );
            read_temp |= ( 1 << 5 );
            read_temp |= ( 1 << 6 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        default:
        {
            return 0;
        }
    }
    
    return 1;
}

uint8_t haptic_set_loop_gain ( haptic_t *ctx, uint8_t gain )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_FEEDBACK );

    switch ( gain )
    {
        case 0:
        {
            read_temp &= ~( 1 << 2 );
            read_temp &= ~( 1 << 2 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 1:
        {
            read_temp |= ( 1 << 2 );
            read_temp &= ~( 1 << 2 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 2:
        {
            read_temp &= ~( 1 << 2 );
            read_temp |=  ( 1 << 2 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        case 3:
        {
            read_temp |= ( 1 << 2 );
            read_temp |= ( 1 << 2 );
            haptic_write_byte( ctx, HAPTIC_REG_FEEDBACK, read_temp );
            break;
        }
        default:
        {
            return 0;
        }
    }
    
    return 1;
}

void haptic_set_input_to_analog ( haptic_t *ctx )
{
    haptic_write_byte( ctx, HAPTIC_REG_CONTROL3, 0x02 );
}

void haptic_set_input_to_pwm ( haptic_t *ctx )
{
    uint8_t read_temp;
    
    read_temp = haptic_read_byte( ctx, HAPTIC_REG_CONTROL3 );
    
    read_temp &= ~ ( 1 << 1 );
    
    haptic_write_byte( ctx, HAPTIC_REG_CONTROL3, read_temp );
}

void haptic_set_sequence ( haptic_t *ctx, uint8_t temp_data )
{
    haptic_write_byte( ctx, HAPTIC_REG_WAVESEQ1, temp_data );
}

void haptic_enable_ac_coulping ( haptic_t *ctx )
{
    haptic_write_byte( ctx, HAPTIC_REG_CONTROL1, 0xB3 );
}
// ------------------------------------------------------------------------- END

