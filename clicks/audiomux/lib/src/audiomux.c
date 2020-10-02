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

#include "audiomux.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void audiomux_cfg_setup ( audiomux_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AUDIOMUX_DEVICE_ADDR;
}

AUDIOMUX_RETVAL audiomux_init ( audiomux_t *ctx, audiomux_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AUDIOMUX_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return AUDIOMUX_OK;

}

void audiomux_default_cfg ( audiomux_t *ctx )
{

    audiomux_select_input( ctx, AUDIOMUX_IN1_EN, AUDIOMUX_MUTE_INPUT_OFF,
                                AUDIOMUX_MIC_GAIN_14DB, AUDIOMUX_MIC_OFF );
    audiomux_set_input_gain( ctx, AUDIOMUX_IN_GAIN_2DB );
    audiomux_write_single_byte( ctx, AUDIOMUX_SURROUND_ADDR,
                                     AUDIOMUX_MIX_0 );
    audiomux_set_volume( ctx, AUDIOMUX_VOL1_6DB_NEG, AUDIOMUX_VOL2_0DB,
                              AUDIOMUX_VOLUME_LEFT_ADDR );
    audiomux_set_volume( ctx, AUDIOMUX_VOL1_6DB_NEG, AUDIOMUX_VOL2_0DB,
                              AUDIOMUX_VOLUME_RIGHT_ADDR );
    audiomux_set_treble_bass( ctx, AUDIOMUX_TRE_BASS_4DB_NEG,
                                   AUDIOMUX_TRE_BASS_14DB );
    audiomux_write_single_byte( ctx, AUDIOMUX_BASS_ALC_ADDR,
                                     AUDIOMUX_MODE2_ADAPTIVE );
    audiomux_mute_ouput( ctx, AUDIOMUX_MUTE_OUTPUT_OFF );
}

void audiomux_generic_write ( audiomux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void audiomux_generic_read ( audiomux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

T_AUDIOMUX_RETVAL audiomux_write_single_byte ( audiomux_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t data_to_write[ 1 ];

    if (reg_addr > AUDIOMUX_BASS_ALC_ADDR)
    {
        return AUDIOMUX_ADDR_ERR;
    }

    *data_to_write = data_in;
    audiomux_generic_write( ctx, reg_addr, data_to_write, 1 );

    return AUDIOMUX_OK;
}

T_AUDIOMUX_RETVAL audiomux_write_bytes ( audiomux_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes )
{
    uint8_t reg_addr;

    if (start_addr > AUDIOMUX_BASS_ALC_ADDR)
    {
        return AUDIOMUX_ADDR_ERR;
    }

    if (n_bytes > (0x08 - start_addr))
    {
        return AUDIOMUX_NBYTES_ERR;
    }

    reg_addr = start_addr | AUDIOMUX_AUTO_INCR;
    audiomux_generic_write( ctx, reg_addr, data_in, n_bytes );

    return AUDIOMUX_OK;
}

T_AUDIOMUX_RETVAL audiomux_read_single_byte ( audiomux_t *ctx, uint8_t reg_addr, uint8_t *data_out )
{

    if (reg_addr > AUDIOMUX_BASS_ALC_ADDR)
    {
        return AUDIOMUX_ADDR_ERR;
    }

    audiomux_generic_read( ctx, reg_addr, data_out, 1 );

    return AUDIOMUX_OK;
}

T_AUDIOMUX_RETVAL audiomux_read_bytes ( audiomux_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t reg_addr;

    if ( start_addr > AUDIOMUX_BASS_ALC_ADDR )
    {
        return AUDIOMUX_ADDR_ERR;
    }
    
    if ( n_bytes > (0x08 - start_addr) )
    {
        return AUDIOMUX_NBYTES_ERR;
    }

    reg_addr = start_addr | AUDIOMUX_AUTO_INCR;
    audiomux_generic_read( ctx, reg_addr, data_out, n_bytes);
    
    return AUDIOMUX_OK;
}

T_AUDIOMUX_RETVAL audiomux_select_input ( audiomux_t *ctx, uint8_t input_sel, uint8_t mute_in,
                                          uint8_t mic_gain, uint8_t mic_state )
{
    uint8_t byte_in;

    if ( input_sel > 0x03 )
    {
        return AUDIOMUX_IN_SEL_ERR;
    }
    
    if ( mic_gain > 0x03 )
    {
        return AUDIOMUX_GAIN_ERR;
    }
    
    if ( (mic_state > 0x01) || (mute_in > 0x01) )
    {
        return AUDIOMUX_STATE_ERR;
    }

    byte_in = mic_state << 5;
    byte_in |= mic_gain << 3;
    byte_in |= mute_in << 2;
    byte_in |= input_sel;

    audiomux_write_single_byte( ctx, AUDIOMUX_INPUT_SEL_ADDR, byte_in );

    return AUDIOMUX_OK;
}

T_AUDIOMUX_RETVAL audiomux_set_input_gain ( audiomux_t *ctx, uint8_t input_gain )
{
    uint8_t byte_in;

    if (input_gain > 0x07)
    {
        return AUDIOMUX_GAIN_ERR;
    }

    byte_in = input_gain;

    audiomux_write_single_byte( ctx, AUDIOMUX_INPUT_GAIN_ADDR, byte_in );

    return AUDIOMUX_OK;
}

T_AUDIOMUX_RETVAL audiomux_set_volume ( audiomux_t *ctx, uint8_t volume1, uint8_t volume2,
                                        uint8_t side_sel )
{
    uint8_t byte_in;
    uint8_t side_addr;

    if ( ( volume1 > 0x3F ) || ( volume2 > 0x03 ) )
    {
        return AUDIOMUX_VOL_ERR;
    }
    
    if ( ( side_sel != AUDIOMUX_VOLUME_LEFT_ADDR ) && ( side_sel != AUDIOMUX_VOLUME_RIGHT_ADDR ) )
    {
        return AUDIOMUX_ADDR_ERR;
    }

    byte_in = volume2 << 6;
    byte_in |= volume1;
    side_addr = side_sel;

    audiomux_write_single_byte( ctx, side_addr, byte_in );

    return AUDIOMUX_OK;
}

T_AUDIOMUX_RETVAL audiomux_set_treble_bass ( audiomux_t *ctx, uint8_t treble, uint8_t bass )
{
    uint8_t byte_in;

    if ((treble > 0x0F) || (bass > 0x0F))
    {
        return AUDIOMUX_TRE_BASS_ERR;
    }

    byte_in = bass << 4;
    byte_in |= treble;

    audiomux_write_single_byte( ctx, AUDIOMUX_TREBLE_BASS_ADDR, byte_in );

    return AUDIOMUX_OK;
}

T_AUDIOMUX_RETVAL audiomux_mute_ouput ( audiomux_t *ctx, uint8_t state )
{
    uint8_t byte_in;

    if (state > 0x01)
    {
        return AUDIOMUX_STATE_ERR;
    }

    byte_in = state;

    audiomux_write_single_byte( ctx, AUDIOMUX_OUTPUT_ADDR, byte_in );

    return AUDIOMUX_OK;
}

// ------------------------------------------------------------------------- END

