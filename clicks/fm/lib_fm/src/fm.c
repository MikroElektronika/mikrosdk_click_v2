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

#include "fm.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void fm_mode_select ( fm_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fm_cfg_setup ( fm_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->gp2   = HAL_PIN_NC;
    cfg->rst   = HAL_PIN_NC;
    cfg->sen   = HAL_PIN_NC;
    cfg->gp1   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = DEFAULT_SLAVE_ADDRESS;
}

FM_RETVAL fm_init ( fm_t *ctx, fm_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return FM_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->sen, cfg->sen );

    // Input pins

    digital_in_init( &ctx->gp2, cfg->gp2 );
    digital_in_init( &ctx->gp1, cfg->gp1 );
     
    return FM_OK;
}

void fm_default_cfg ( fm_t *ctx )
{
    fm_power_up( ctx );
    
    fm_basic_settings( ctx );

    fm_set_volume( ctx, 10 );

    fm_set_snr_threshold( ctx, 0x7 );

    fm_set_seek_threshold( ctx, 0x19 );

    fm_set_seek_impulse_detection_threshold( ctx, 0xF ); 
}

void fm_generic_write ( fm_t *ctx, uint16_t *reg_buf )
{
    uint8_t aux_buf[ 32 ];
    uint8_t i;
    uint8_t j;
    
    j = 0;
    
    for ( i = 0; i < 16; i++ )
    {
        aux_buf[ j ] = reg_buf[ i ] >> 8;
        j += 1;
        aux_buf[ j ] = reg_buf[ i ];
        j += 1;
    }
      
    i2c_master_write( &ctx->i2c, aux_buf, 32 );   
}

void fm_generic_read ( fm_t *ctx, uint16_t *reg_buf )
{
    uint8_t aux_buf_1[ 32 ];
    uint8_t aux_buf_2[ 32 ];
    uint8_t i;
    uint8_t j;
    
    i2c_master_read( &ctx->i2c, aux_buf_1, 32 );   

    for ( i = 0; i < 16; i++ )
    {
        aux_buf_2[ i + 16 ] = aux_buf_1[ i ];
    }
    for ( i = 0; i < 16; i++ )
    {
        aux_buf_2[ i ] = aux_buf_1[ i + 16 ];
    }
    
    j = 0;
    
    for ( i = 0; i < 16; i ++ )
    {
        reg_buf[ i ] = aux_buf_2[ j ];
        reg_buf[ i ] <<= 8;
        j += 1;
        reg_buf[ i ] |= aux_buf_2[ j ];
        j += 1;
    }
}

void fm_set_bits ( uint16_t *register_buffer, uint16_t register_address, uint16_t bits_mask, uint16_t bits_value )
{
    register_buffer[ register_address ] &= bits_mask;
    register_buffer[ register_address ] |= bits_value;
}

uint8_t fm_set_seek_threshold ( fm_t *ctx, uint16_t seek_threshold )
{
    uint16_t reg_buffer[ 16 ];

    if ( seek_threshold < 128 )
    {
        fm_generic_read( ctx, reg_buffer );

        reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ] &= 0x00FF;
        seek_threshold <<= 8;
        reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ] |= seek_threshold;

        fm_generic_write( ctx, reg_buffer );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t fm_set_volume ( fm_t *ctx, uint8_t volume_level )
{
    uint16_t reg_buffer[ 16 ];

    if ( volume_level < 16 )
    {
        fm_generic_read( ctx, reg_buffer );

        reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ] &= 0xFFF0;
        reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ] |= volume_level;

        fm_generic_write( ctx, reg_buffer );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t fm_set_snr_threshold ( fm_t *ctx, uint8_t snr_threshold )
{
    uint16_t reg_buffer[ 16 ];

    if ( snr_threshold < 8 )
    {
        fm_generic_read( ctx, reg_buffer );

        reg_buffer[ FM_SYSTEM_CONFIGURATION_3 ] &= 0xFF0F;
        snr_threshold <<= 4;
        reg_buffer[ FM_SYSTEM_CONFIGURATION_3 ] |= snr_threshold;

        fm_generic_write( ctx, reg_buffer );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t fm_set_seek_impulse_detection_threshold ( fm_t *ctx, uint8_t impulse_detection_threshold )
{
    uint16_t reg_buffer[ 16 ];

    if ( impulse_detection_threshold < 16 )
    {
        fm_generic_read( ctx, reg_buffer );

        reg_buffer[ FM_SYSTEM_CONFIGURATION_3 ] &= 0xFFF0;
        reg_buffer[ FM_SYSTEM_CONFIGURATION_3 ] |= impulse_detection_threshold;

        fm_generic_write( ctx, reg_buffer );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t fm_get_errors_block_a ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint16_t aux_variable;
    
    uint8_t n_errors;

    fm_generic_read( ctx, reg_buffer );

    aux_variable = reg_buffer[ FM_STATUS_RSSI ];

    aux_variable &= 0x0600;
    aux_variable >>= 9;
    aux_variable &= 0x0003;

    n_errors = aux_variable;

    return n_errors;
}

uint8_t fm_get_received_signal_strength_indicator ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint16_t aux_variable;

    uint8_t rssi_value;

    fm_generic_read( ctx, reg_buffer );

    aux_variable = reg_buffer[ FM_STATUS_RSSI ];

    aux_variable &= 0x00FF;

    rssi_value = aux_variable;

    return rssi_value;
}

uint8_t fm_get_errors_block_b ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint16_t aux_variable;

    uint8_t n_errors;

    fm_generic_read( ctx, reg_buffer );

    aux_variable = reg_buffer[ FM_READ_CHANNEL ];

    aux_variable &= 0xC000;
    aux_variable >>= 14;
    aux_variable &= 0x0003;

    n_errors = aux_variable;

    return n_errors;
}

uint8_t fm_get_errors_block_c ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint16_t aux_variable;

    uint8_t n_errors;

    fm_generic_read( ctx, reg_buffer );

    aux_variable = reg_buffer[ FM_READ_CHANNEL ];

    aux_variable &= 0x3000;
    aux_variable >>= 12;
    aux_variable &= 0x0003;

    n_errors = aux_variable;

    return n_errors;
}

uint8_t fm_get_errors_block_d ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint16_t aux_variable;

    uint8_t n_errors;

    fm_generic_read( ctx, reg_buffer );

    aux_variable = reg_buffer[ FM_READ_CHANNEL ];

    aux_variable &= 0x0C00;
    aux_variable >>= 10;
    aux_variable &= 0x0003;

    n_errors = aux_variable;

    return n_errors;
}

float fm_get_channel_frequency ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint16_t channel;
    uint16_t b;
    uint16_t s;
    float channel_frequency;
    float space;
    float band;

    fm_generic_read( ctx, reg_buffer );

    b = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    b &= 0x00C0;
    b >>= 6;
    b &= 0x0003;

    s = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    s &= 0x0030;
    s >>= 4;
    s &= 0x0003;

    if ( b == 0 )
    {
        band = 87.5;
    }
    else if ( b == 1 )
    {
        band = 76.0;
    }
    else if ( b == 2 )
    {
        band = 76.0;
    }

    if ( s == 0 )
    {
        space = 0.2;
    }
    else if ( s == 1 )
    {
        space = 0.1;
    }
    else if ( s == 2 )
    {
        space = 0.05;
    }

    channel = reg_buffer[ FM_READ_CHANNEL ];

    channel &= 0x03FF;
    
    channel_frequency  = channel * space;
    channel_frequency += band;
    
    return channel_frequency;
}

void fm_power_up ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    
    fm_mode_select( ctx );

    Delay_100ms( );    // wait for device to settle 
    
    fm_generic_read( ctx, reg_buffer );
    
    fm_set_bits( reg_buffer,  FM_TEST_1,  FM_AUDIO_HIGH_Z_MASK,       FM_AUDIO_HIGH_Z_DISABLE );
    fm_set_bits( reg_buffer,  FM_TEST_1,  FM_CRYSTAL_OSCYLATOR_MASK,  FM_CRYSTAL_OSCYLATOR_ENABLE );
    
    fm_generic_write( ctx, reg_buffer );
    
    Delay_1sec( );     // waiting for crystal oscylator to settle -- minimum 500 ms 
    
    fm_generic_read( ctx, reg_buffer );
    
    fm_set_bits( reg_buffer,  FM_POWER_CONFIGURATION,  FM_POWERUP_ENABLE_MASK,   FM_POWERUP_ENABLE_HIGH );
    fm_set_bits( reg_buffer,  FM_POWER_CONFIGURATION,  FM_POWERUP_DISABLE_MASK,  FM_POWERUP_DISABLE_LOW );
    fm_set_bits( reg_buffer,  FM_POWER_CONFIGURATION,  FM_MUTE_MASK,             FM_MUTE_DISABLE );

    fm_generic_write( ctx, reg_buffer );
    
    Delay_100ms( );    // waiting for device to powerup 
}

void fm_basic_settings ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];

    fm_generic_read( ctx, reg_buffer );

    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_SOFTMUTE_MASK,          FM_SOFTMUTE_DISABLE );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_MUTE_MASK,              FM_MUTE_DISABLE );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_STEREO_MASK,            FM_STEREO );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_RDS_MODE_MASK,          FM_RDS_MODE_STANDARD );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_SEEK_MODE_MASK,         FM_SEEK_MODE_WRAP );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_SEEK_DIRECTION_MASK,    FM_SEEK_DIRECTION_UP );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_SEEK_MASK,              FM_SEEK_DISABLE );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_POWERUP_DISABLE_MASK,   FM_POWERUP_DISABLE_LOW );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_POWERUP_ENABLE_MASK,    FM_POWERUP_ENABLE_HIGH );
    
    fm_set_bits( reg_buffer,   FM_CHANNEL,   FM_TUNE_MASK,   FM_TUNE_DISABLE );

    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_RDS_INTERRUPT_MASK,                FM_RDS_INTERRUPT_DISABLE );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_SEEK_TUNE_COMPLETE_INTERRUPT_MASK, FM_SEEK_TUNE_COMPLETE_INTERRUPT_ENABLE );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_RDS_MASK,                          FM_RDS_DISABLE );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_DE_EMPHASIS_MASK,                  FM_DE_EMPHASIS_EUROPE_AUSTRALIA_JAPAN );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_AGC_MASK,                          FM_AGC_ENABLE );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_STEREO_MONO_BLEND_LEVEL_MASK,      FM_STEREO_MONO_BLEND_LEVEL_31_49_RSSI );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_GPIO3_MASK,                        FM_GPIO3_HIGH_IMPENDANCE );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_GPIO2_MASK,                        FM_GPIO2_STC_RDS_INTERRUPT );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_GPIO1_MASK,                        FM_GPIO1_HIGH_IMPEDANCE );

    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_2,   FM_BAND_MASK,                         FM_BAND_USA_EUROPE_87P5_108_MHZ );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_2,   FM_CHANNEL_SPACING_MASK,              FM_CHANNEL_SPACING_EUROPE_JAPAN_100_KHZ );
    
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_3,   FM_SOFTMUTE_ATTACK_RECOVER_RATE_MASK, FM_SOFTMUTE_ATTACK_RECOVER_RATE_FASTEST );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_3,   FM_SOFTMUTE_ATTENUATION_MASK,         FM_SOFTMUTE_ATTENUATION_16_DB );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_3,   FM_EXTENDED_VOLUME_RANGE_MASK,        FM_EXTENDED_VOLUME_RANGE_DISABLED );

    fm_generic_write( ctx, reg_buffer );
}

void fm_power_down ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];

    fm_generic_read( ctx, reg_buffer );

    fm_set_bits( reg_buffer,   FM_TEST_1,   FM_AUDIO_HIGH_Z_MASK,   FM_AUDIO_HIGH_Z_ENABLE );
    
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_RDS_MASK,     FM_RDS_DISABLE );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_GPIO1_MASK,   FM_GPIO1_LOW );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_GPIO2_MASK,   FM_GPIO2_LOW );
    fm_set_bits( reg_buffer,   FM_SYSTEM_CONFIGURATION_1,   FM_GPIO3_MASK,   FM_GPIO3_LOW );
    
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_POWERUP_ENABLE_MASK,    FM_POWERUP_ENABLE_LOW );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_POWERUP_DISABLE_MASK,   FM_POWERUP_DISABLE_HIGH );
    fm_set_bits( reg_buffer,   FM_POWER_CONFIGURATION,   FM_MUTE_MASK,              FM_MUTE_ENABLE );

    fm_generic_write( ctx, reg_buffer );

    Delay_1sec( );    // powerdown time
}

uint16_t fm_get_channel ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint16_t channel;
    
    fm_generic_read( ctx, reg_buffer );

    channel = reg_buffer[ FM_READ_CHANNEL ];

    channel &= 0x03FF;
    
    return channel;
}

void fm_tune_channel ( fm_t *ctx, uint16_t channel )
{
    uint16_t reg_buffer[ 16 ];
    
    fm_generic_read( ctx, reg_buffer );

    channel &= 0x03FF;

    reg_buffer[ FM_CHANNEL ] &= 0x0000;
    reg_buffer[ FM_CHANNEL ] |= channel;
    
    fm_set_bits( reg_buffer, FM_CHANNEL, FM_TUNE_MASK, FM_TUNE_ENABLE );
    
    fm_generic_write( ctx, reg_buffer );
}

uint8_t fm_tune ( fm_t *ctx, float channel_frequency )
{
    uint16_t channel_limit_up;
    uint16_t reg_buffer[ 16 ];
    uint16_t channel;
    uint16_t b;
    uint16_t s;
    float band_limit_down;
    float band_limit_up;
    float space;
    float aux;

    fm_generic_read( ctx, reg_buffer );

    b = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    b &= 0x00C0;
    b >>= 6;
    b &= 0x0003;

    s = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    s &= 0x0030;
    s >>= 4;
    s &= 0x0003;

    if ( b == 0 )
    {
        band_limit_down = 87.5;
        band_limit_up = 108;
    }
    else if ( b == 1 )
    {
        band_limit_down = 76.0;
        band_limit_up = 108;
    }
    else if ( b == 2 )
    {
        band_limit_down = 76.0;
        band_limit_up = 90;
    }

    if ( s == 0 )
    {
        space = 0.2;
    }
    else if ( s == 1 )
    {
        space = 0.1;
    }
    else if ( s == 2 )
    {
        space = 0.05;
    }

    aux  = channel_frequency - band_limit_down;
    aux /= space;

    channel = ( uint16_t )( aux );
    
    aux  = band_limit_up - band_limit_down;
    aux /= space;
    
    channel_limit_up = ( uint16_t )( aux );

    if ( channel < channel_limit_up && channel > 0)
    {
        reg_buffer[ FM_CHANNEL ] &= 0x0000;
        reg_buffer[ FM_CHANNEL ] |= channel;

        fm_set_bits( reg_buffer, FM_CHANNEL, FM_TUNE_MASK, FM_TUNE_ENABLE );

        fm_generic_write( ctx, reg_buffer );

        return 0;
    }
    else
    {
        return 1;
    }
}

void fm_end_tune ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    
    fm_generic_read( ctx, reg_buffer );
    
    fm_set_bits( reg_buffer, FM_CHANNEL, FM_TUNE_MASK, FM_TUNE_DISABLE );
    
    fm_generic_write( ctx, reg_buffer );
}

void fm_seek ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    
    fm_generic_read( ctx, reg_buffer );
    
    fm_set_bits( reg_buffer, FM_POWER_CONFIGURATION, FM_SEEK_MASK, FM_SEEK_ENABLE );
    
    fm_generic_write( ctx, reg_buffer );
}

void fm_end_seek ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];

    fm_generic_read( ctx, reg_buffer );

    fm_set_bits( reg_buffer, FM_POWER_CONFIGURATION, FM_SEEK_MASK, FM_SEEK_DISABLE );

    fm_generic_write( ctx, reg_buffer );
}

uint8_t fm_volume_up ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint8_t volume_level;
    
    fm_generic_read( ctx, reg_buffer );
    
    volume_level  = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    volume_level &= 0x000F;
    
    if ( volume_level < 15 )
    {
        volume_level += 1;
        
        reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ] &= 0xFFF0;
        reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ] |= volume_level;

        fm_generic_write( ctx, reg_buffer );
        
        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t fm_volume_down ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    uint8_t volume_level;

    fm_generic_read( ctx, reg_buffer );

    volume_level  = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    volume_level &= 0x000F;

    if ( volume_level > 0 )
    {
        volume_level -= 1;

        reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ] &= 0xFFF0;
        reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ] |= volume_level;

        fm_generic_write( ctx, reg_buffer );

        return 0;
    }
    else
    {
        return 1;
    }
}

void fm_mute_enable ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];
    
    fm_generic_read( ctx, reg_buffer );
    
    fm_set_bits( reg_buffer, FM_POWER_CONFIGURATION, FM_MUTE_MASK, FM_MUTE_ENABLE );
    
    fm_generic_write( ctx, reg_buffer );
}

void fm_mute_disable ( fm_t *ctx )
{
    uint16_t reg_buffer[ 16 ];

    fm_generic_read( ctx, reg_buffer );

    fm_set_bits( reg_buffer, FM_POWER_CONFIGURATION, FM_MUTE_MASK, FM_MUTE_DISABLE );

    fm_generic_write( ctx, reg_buffer );
}

uint8_t fm_fine_tune_up ( fm_t *ctx )
{
    uint16_t channel_limit_up;
    uint16_t current_channel;
    uint16_t reg_buffer[ 16 ];
    uint16_t increment;
    uint16_t channel;
    uint16_t b;
    uint16_t s;
    float band_limit_down;
    float band_limit_up;
    float space;
    float aux;

    fm_generic_read( ctx, reg_buffer );

    b = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    b &= 0x00C0;
    b >>= 6;
    b &= 0x0003;

    s = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    s &= 0x0030;
    s >>= 4;
    s &= 0x0003;
    
    current_channel  = reg_buffer[ FM_READ_CHANNEL ];
    current_channel &= 0x03FF;

    if ( b == 0 )
    {
        band_limit_down = 87.5;
        band_limit_up = 108;
    }
    else if ( b == 1 )
    {
        band_limit_down = 76.0;
        band_limit_up = 108;
    }
    else if ( b == 2 )
    {
        band_limit_down = 76.0;
        band_limit_up = 90;
    }

    if ( s == 0 )
    {
        space = 0.2;
        increment = 1;
    }
    else if ( s == 1 )
    {
        space = 0.1;
        increment = 1;
    }
    else if ( s == 2 )
    {
        space = 0.05;
        increment = 2;
    }
    
    channel = current_channel + increment;

    aux  = band_limit_up - band_limit_down;
    aux /= space;

    channel_limit_up = ( uint16_t )( aux );

    if ( channel < channel_limit_up && channel > 0 )
    {
        reg_buffer[ FM_CHANNEL ] &= 0x0000;
        reg_buffer[ FM_CHANNEL ] |= channel;

        fm_set_bits( reg_buffer, FM_CHANNEL, FM_TUNE_MASK, FM_TUNE_ENABLE );

        fm_generic_write( ctx, reg_buffer );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t fm_fine_tune_down ( fm_t *ctx )
{
    uint16_t current_channel;
    uint16_t channel_limit_up;
    uint16_t reg_buffer[ 16 ];
    uint16_t increment;
    uint16_t channel;
    uint16_t b;
    uint16_t s;
    float band_limit_down;
    float band_limit_up;
    float space;
    float aux;

    fm_generic_read( ctx, reg_buffer );

    b = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    b &= 0x00C0;
    b >>= 6;
    b &= 0x0003;

    s = reg_buffer[ FM_SYSTEM_CONFIGURATION_2 ];
    s &= 0x0030;
    s >>= 4;
    s &= 0x0003;

    current_channel  = reg_buffer[ FM_READ_CHANNEL ];
    current_channel &= 0x03FF;

    if ( b == 0 )
    {
        band_limit_down = 87.5;
        band_limit_up = 108;
    }
    else if ( b == 1 )
    {
        band_limit_down = 76.0;
        band_limit_up = 108;
    }
    else if ( b == 2 )
    {
        band_limit_down = 76.0;
        band_limit_up = 90;
    }

    if ( s == 0 )
    {
        space = 0.2;
        increment = 1;
    }
    else if ( s == 1 )
    {
        space = 0.1;
        increment = 1;
    }
    else if ( s == 2 )
    {
        space = 0.05;
        increment = 2;
    }

    channel = current_channel - increment;

    aux  = band_limit_up - band_limit_down;
    aux /= space;

    channel_limit_up = ( uint16_t )( aux );

    if ( channel < channel_limit_up && channel > 0 )
    {
        reg_buffer[ FM_CHANNEL ] &= 0x0000;
        reg_buffer[ FM_CHANNEL ] |= channel;

        fm_set_bits( reg_buffer, FM_CHANNEL, FM_TUNE_MASK, FM_TUNE_ENABLE );

        fm_generic_write( ctx, reg_buffer );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t fm_get_int_pin ( fm_t *ctx )
{
    return digital_in_read( &ctx->gp1 );
}

uint8_t fm_get_an_pin ( fm_t *ctx )
{
    return digital_in_read( &ctx->gp2 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void fm_mode_select ( fm_t *ctx )
{
    digital_out_low( &ctx->rst );
    digital_out_high( &ctx->sen );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
}

// ------------------------------------------------------------------------- END

