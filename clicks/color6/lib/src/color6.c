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

#include "color6.h"

// ------------------------------------------------------------------ CONSTANTS

static const uint8_t channel_time[15] =
{
    COLOR6_CREG1_TIME_1ms,
    COLOR6_CREG1_TIME_2ms,
    COLOR6_CREG1_TIME_4ms,
    COLOR6_CREG1_TIME_8ms,
    COLOR6_CREG1_TIME_16ms,
    COLOR6_CREG1_TIME_32ms,
    COLOR6_CREG1_TIME_64ms,
    COLOR6_CREG1_TIME_128ms,
    COLOR6_CREG1_TIME_256ms,
    COLOR6_CREG1_TIME_512ms,
    COLOR6_CREG1_TIME_1024ms,
    COLOR6_CREG1_TIME_2048ms,
    COLOR6_CREG1_TIME_4096ms,
    COLOR6_CREG1_TIME_8192ms,
    COLOR6_CREG1_TIME_16384ms
};

static const uint32_t number_of_clock[15] =
{
    COLOR6_NUMBER_OF_CLK_TIME_1ms,
    COLOR6_NUMBER_OF_CLK_TIME_2ms,
    COLOR6_NUMBER_OF_CLK_TIME_4ms,
    COLOR6_NUMBER_OF_CLK_TIME_8ms,
    COLOR6_NUMBER_OF_CLK_TIME_16ms,
    COLOR6_NUMBER_OF_CLK_TIME_32ms,
    COLOR6_NUMBER_OF_CLK_TIME_64ms,
    COLOR6_NUMBER_OF_CLK_TIME_128ms,
    COLOR6_NUMBER_OF_CLK_TIME_256ms,
    COLOR6_NUMBER_OF_CLK_TIME_512ms,
    COLOR6_NUMBER_OF_CLK_TIME_1024ms,
    COLOR6_NUMBER_OF_CLK_TIME_2048ms,
    COLOR6_NUMBER_OF_CLK_TIME_4096ms,
    COLOR6_NUMBER_OF_CLK_TIME_8192ms,
    COLOR6_NUMBER_OF_CLK_TIME_16384ms
};

static const uint8_t channel_gain[12] =
{
    COLOR6_CREG1_GAIN_XYZ_2048,
    COLOR6_CREG1_GAIN_XYZ_1024,
    COLOR6_CREG1_GAIN_XYZ_512,
    COLOR6_CREG1_GAIN_XYZ_256,
    COLOR6_CREG1_GAIN_XYZ_128,
    COLOR6_CREG1_GAIN_XYZ_64,
    COLOR6_CREG1_GAIN_XYZ_32,
    COLOR6_CREG1_GAIN_XYZ_16,
    COLOR6_CREG1_GAIN_XYZ_8,
    COLOR6_CREG1_GAIN_XYZ_4,
    COLOR6_CREG1_GAIN_XYZ_2,
    COLOR6_CREG1_GAIN_XYZ_1
};

static const float x_channel_fsr[12] =
{
    COLOR6_X_FSR_OF_GAIN_2048,
    COLOR6_X_FSR_OF_GAIN_1024,
    COLOR6_X_FSR_OF_GAIN_512,
    COLOR6_X_FSR_OF_GAIN_256,
    COLOR6_X_FSR_OF_GAIN_128,
    COLOR6_X_FSR_OF_GAIN_64,
    COLOR6_X_FSR_OF_GAIN_32,
    COLOR6_X_FSR_OF_GAIN_16,
    COLOR6_X_FSR_OF_GAIN_8,
    COLOR6_X_FSR_OF_GAIN_4,
    COLOR6_X_FSR_OF_GAIN_2,
    COLOR6_X_FSR_OF_GAIN_1
};
static const float y_channel_fsr[12] =
{
    COLOR6_Y_FSR_OF_GAIN_2048,
    COLOR6_Y_FSR_OF_GAIN_1024,
    COLOR6_Y_FSR_OF_GAIN_512,
    COLOR6_Y_FSR_OF_GAIN_256,
    COLOR6_Y_FSR_OF_GAIN_128,
    COLOR6_Y_FSR_OF_GAIN_64,
    COLOR6_Y_FSR_OF_GAIN_32,
    COLOR6_Y_FSR_OF_GAIN_16,
    COLOR6_Y_FSR_OF_GAIN_8,
    COLOR6_Y_FSR_OF_GAIN_4,
    COLOR6_Y_FSR_OF_GAIN_2,
    COLOR6_Y_FSR_OF_GAIN_1
};

static const float z_channel_fsr[12] =
{
    COLOR6_Z_FSR_OF_GAIN_2048,
    COLOR6_Z_FSR_OF_GAIN_1024,
    COLOR6_Z_FSR_OF_GAIN_512,
    COLOR6_Z_FSR_OF_GAIN_256,
    COLOR6_Z_FSR_OF_GAIN_128,
    COLOR6_Z_FSR_OF_GAIN_64,
    COLOR6_Z_FSR_OF_GAIN_32,
    COLOR6_Z_FSR_OF_GAIN_16,
    COLOR6_Z_FSR_OF_GAIN_8,
    COLOR6_Z_FSR_OF_GAIN_4,
    COLOR6_Z_FSR_OF_GAIN_2,
    COLOR6_Z_FSR_OF_GAIN_1
};

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void color6_cfg_setup ( color6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x74;
}

COLOR6_RETVAL color6_init ( color6_t *ctx, color6_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COLOR6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return COLOR6_OK;

}

void color6_default_cfg ( color6_t *ctx )
{
    color6_write_byte( ctx, COLOR6_REG_CONFIGURATION_REGISTER_1, COLOR6_CREG1_GAIN_XYZ_2 | COLOR6_CREG1_TIME_512ms );
    color6_write_byte( ctx, COLOR6_REG_CONFIGURATION_REGISTER_2, 0x80 | COLOR6_CREG2_EN_TM_ENABLE | COLOR6_CREG2_DIGITAL_DIVIDER_ENABLE | COLOR6_CREG2_DIVIDER_16 );
    color6_write_byte( ctx, COLOR6_REG_CONFIGURATION_REGISTER_3, COLOR6_CREG3_SB_STANDBY_SWITCHED_ON );
    color6_write_byte( ctx, COLOR6_REG_BREAK_TIME, 0x52 );
    color6_write_byte( ctx, COLOR6_REG_EDGE_COUNT_VALUE, 0x01 );
}

void color6_generic_write ( color6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void color6_generic_read ( color6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void color6_write_byte ( color6_t *ctx, uint8_t reg, uint8_t r_data )
{   
    color6_generic_write( ctx, reg , &r_data , 1 );

    if ( reg == COLOR6_REG_CONFIGURATION_REGISTER_1 )
    {
        ctx->set_gain = ( r_data & 0xF0 );
        ctx->set_time = ( r_data & 0x0F );
    }
}

uint8_t color6_read_byte ( color6_t *ctx, uint8_t reg )
{
    uint8_t read_reg[ 1 ] = { 0 };
   
    color6_generic_read( ctx, reg, read_reg, 1 ); 

    return read_reg[ 0 ];
}

uint16_t color6_read_data ( color6_t *ctx, uint8_t reg )
{
    uint8_t read_reg[ 2 ] = { 0 };
    uint16_t read_data = 0;

    color6_generic_read( ctx, reg, read_reg, 2 );

    read_data = read_reg[ 1 ];
    read_data = read_data << 8;
    read_data = read_data | read_reg[ 0 ];
    
    return read_data;
}

float color6_get_temperature ( color6_t *ctx )
{
    uint16_t channel_data;
    float float_data;
    
    channel_data = color6_read_data( ctx, COLOR6_MREG_TEMPERATURE_MEASUREMENT );
    channel_data = channel_data & 0x0FFF;
    float_data = ( channel_data * 0.05 ) - 66.9;
    return float_data;
}

void color6_software_reset ( color6_t *ctx ) 
{
    color6_write_byte( ctx, COLOR6_REG_OPERATIONAL_STATE, 0x4A );
}

void color6_go_to_measurement_mode ( color6_t *ctx )
{
    color6_write_byte( ctx, COLOR6_REG_OPERATIONAL_STATE, 0x83 );
}

float color6_converting_to_ee ( color6_t *ctx, uint8_t channel, uint16_t mres_data )
{
    float data_value;
    uint8_t cnt;
    
    for (cnt = 0; cnt < 12; cnt++)
    {
        if ( channel_gain[ cnt ] == ctx->set_gain)
        {
             if ( channel == COLOR6_MREG_MEASUREMENT_X_CHANNEL )
             {
                 ctx->fsr = x_channel_fsr[ cnt ];
             }
             else if ( channel == COLOR6_MREG_MEASUREMENT_Y_CHANNEL )
             {
                 ctx->fsr = y_channel_fsr[ cnt ];
             }
             else if ( channel == COLOR6_MREG_MEASUREMENT_Z_CHANNEL )
             {
                 ctx->fsr = z_channel_fsr[ cnt ];
             }
        }
        if ( channel_time[ cnt ] == ctx->set_time )
        {
             ctx->num_of_clk = number_of_clock[ cnt ];
        }
    }
    
    data_value = (float)( ctx->fsr / ctx->num_of_clk ) * (float)mres_data;

    return data_value;
}

// ------------------------------------------------------------------------- END

