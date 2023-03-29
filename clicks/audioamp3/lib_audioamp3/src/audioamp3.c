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

#include "audioamp3.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void audioamp3_cfg_setup ( audioamp3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->stb = HAL_PIN_NC;
    cfg->clp = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AUDIOAMP3_I2C_SLAVE_ADDRESS;
}

AUDIOAMP3_RETVAL audioamp3_init ( audioamp3_t *ctx, audioamp3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AUDIOAMP3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->stb, cfg->stb );

    // Input pins

    digital_in_init( &ctx->clp, cfg->clp );
    digital_in_init( &ctx->flt, cfg->flt );


    return AUDIOAMP3_OK;
}

void audioamp3_generic_write ( audioamp3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void audioamp3_generic_read ( audioamp3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void audioamp3_power_up ( audioamp3_t *ctx )
{
    digital_out_high( &ctx->stb );
}

void audioamp3_hw_reset ( audioamp3_t *ctx )
{
    digital_out_low( &ctx->stb );
    dev_comm_delay( );
    digital_out_high( &ctx->stb );
    dev_comm_delay( );
}

void audioamp3_read_all_diagnostics ( audioamp3_t *ctx, uint8_t *p_all_diagnostics )
{
    audioamp3_generic_read( ctx, AUDIOAMP3_DIAG_LATCHED_FAULT_REG_1, &p_all_diagnostics[ 0 ], 9 );
}

AUDIOAMP3_STATUS_T audioamp3_set_channel_low_to_low ( audioamp3_t *ctx, uint8_t s_channel )
{
    uint8_t temp;
    uint8_t rx_buf[ 1 ];
    uint8_t c_flag;
    
    audioamp3_generic_read( ctx, AUDIOAMP3_EXT_CTRL_REG_6, rx_buf, 1 );
    temp = rx_buf[ 0 ];

    c_flag = AUDIOAMP3_STATUS_ERR;

    if ( s_channel == AUDIOAMP3_MASK_BIT_SEL_CH_1 )
    {
        temp |= AUDIOAMP3_OUT_CTRL_SET_CH_1_L_LOW_STATE;
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_6, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }

    if ( s_channel == AUDIOAMP3_MASK_BIT_SEL_CH_2 )
    {
        temp |= AUDIOAMP3_OUT_CTRL_SET_CH_2_L_LOW_STATE;
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_6, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }

    return c_flag;
}

AUDIOAMP3_STATUS_T audioamp3_set_channel_mute_mode ( audioamp3_t *ctx, uint8_t s_channel )
{
    uint8_t temp;
    uint8_t c_flag;

    c_flag = AUDIOAMP3_STATUS_ERR;
    
    if ( s_channel == AUDIOAMP3_MASK_BIT_SEL_NO_CH )
    {
        temp  = AUDIOAMP3_OUT_CTRL_ALL_CH_HI_Z_MUTE_RST_DIS_DC_EN;
        temp &= AUDIOAMP3_MASK_BIT_MUTE_NO_CH;
        
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_5, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }
    
    if ( s_channel == AUDIOAMP3_MASK_BIT_SEL_CH_1 )
    {
        temp  = AUDIOAMP3_OUT_CTRL_ALL_CH_HI_Z_MUTE_RST_DIS_DC_EN;
        temp &= AUDIOAMP3_MASK_BIT_MUTE_CH_1;
        
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_5, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }
    
    if ( s_channel == AUDIOAMP3_MASK_BIT_SEL_CH_2 )
    {
        temp  = AUDIOAMP3_OUT_CTRL_ALL_CH_HI_Z_MUTE_RST_DIS_DC_EN;
        temp &= AUDIOAMP3_MASK_BIT_MUTE_CH_2;
        
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_5, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }
    
    if ( s_channel == AUDIOAMP3_MASK_BIT_SEL_ALL_CH )
    {
        temp  = AUDIOAMP3_OUT_CTRL_ALL_CH_HI_Z_MUTE_RST_DIS_DC_EN;
        
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_5, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }
    
    return c_flag;
}

AUDIOAMP3_STATUS_T audioamp3_run_channel_diagnostics ( audioamp3_t *ctx, uint8_t rc_channel )
{
    uint8_t temp;
    uint8_t c_flag;

    c_flag = AUDIOAMP3_STATUS_ERR;

    if ( rc_channel == AUDIOAMP3_MASK_BIT_SEL_NO_CH )
    {
        temp = AUDIOAMP3_SET_CLOCK_OUTPUT_DISABLED;
        
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_4, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }

    if ( rc_channel == AUDIOAMP3_MASK_BIT_SEL_CH_1 )
    {
        temp  = AUDIOAMP3_SET_CLOCK_OUTPUT_DISABLED;
        temp |= AUDIOAMP3_LOAD_DIAG_RUN_CH_1;
        
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_4, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }
    
    if ( rc_channel == AUDIOAMP3_MASK_BIT_SEL_CH_2 )
    {
        temp  = AUDIOAMP3_SET_CLOCK_OUTPUT_DISABLED;
        temp |= AUDIOAMP3_LOAD_DIAG_RUN_CH_2;
        
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_4, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }
    
    if ( rc_channel == AUDIOAMP3_MASK_BIT_SEL_ALL_CH )
    {
        temp  = AUDIOAMP3_SET_CLOCK_OUTPUT_DISABLED;
        temp |= AUDIOAMP3_LOAD_DIAG_RUN_CH_1;
        temp |= AUDIOAMP3_LOAD_DIAG_RUN_CH_2;
        temp |= AUDIOAMP3_LOAD_DIAG_RUN_CH_3;
        temp |= AUDIOAMP3_LOAD_DIAG_RUN_CH_4;
        
        audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_4, &temp, 1 );
        c_flag = AUDIOAMP3_STATUS_OK;
    }

    return c_flag;
}

AUDIOAMP3_STATUS_T audioamp3_set_play_mode ( audioamp3_t *ctx )
{
    uint8_t temp;
    uint8_t tx_buf;
    uint8_t rx_buf[ 1 ];
    uint8_t p_flag;

    p_flag = AUDIOAMP3_STATUS_ERR;
    
    tx_buf = AUDIOAMP3_OUT_CTRL_SET_PLAY_MODE;

    audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_5, &tx_buf, 1 );
    audioamp3_generic_read( ctx, AUDIOAMP3_EXT_CTRL_REG_2, rx_buf, 1 );
    
    temp = rx_buf[ 0 ];

    if ( temp == AUDIOAMP3_OUT_CTRL_SET_PLAY_MODE )
    {
        p_flag = AUDIOAMP3_STATUS_OK;
    }

    return p_flag;
}

AUDIOAMP3_STATUS_T audioamp3_set_gain_lvl ( audioamp3_t *ctx, uint8_t gain_lvl )
{
    uint8_t temp;
    uint8_t g_flag;

    g_flag = AUDIOAMP3_STATUS_ERR;

    switch ( gain_lvl )
    {
        case AUDIOAMP3_GAIN_VAL_LVL_1_12dB:
        {
            temp = AUDIOAMP3_SEL_CH_1_GAIN_12dB;
            temp |= AUDIOAMP3_SEL_CH_2_GAIN_12dB;
            g_flag = AUDIOAMP3_STATUS_OK;
            break;
        }
        case AUDIOAMP3_GAIN_VAL_LVL_2_20dB:
        {
            temp = AUDIOAMP3_SEL_CH_1_GAIN_20dB;
            temp |= AUDIOAMP3_SEL_CH_2_GAIN_20dB;
            g_flag = AUDIOAMP3_STATUS_OK;
            break;
        }
        case AUDIOAMP3_GAIN_VAL_LVL_3_26dB:
        {
            temp = AUDIOAMP3_SEL_ALL_CH_GAIN_26dB;
            g_flag = AUDIOAMP3_STATUS_OK;
            break;
        }
        case AUDIOAMP3_GAIN_VAL_LVL_4_32dB:
        {
            temp = AUDIOAMP3_SEL_CH_1_GAIN_32dB;
            temp |= AUDIOAMP3_SEL_CH_2_GAIN_32dB;
            g_flag = AUDIOAMP3_STATUS_OK;
            break;
        }
    }

    audioamp3_generic_write( ctx, AUDIOAMP3_EXT_CTRL_REG_1, &temp, 1 );

    return g_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_comm_delay ( void )
{
    Delay_100ms();
}

// ------------------------------------------------------------------------- END

