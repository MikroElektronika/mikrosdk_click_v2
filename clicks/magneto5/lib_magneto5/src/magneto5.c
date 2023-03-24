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

#include "magneto5.h"
/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static void measure_resolution ( magneto5_t *ctx, uint8_t set_data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void magneto5_cfg_setup ( magneto5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x30;
}

MAGNETO5_RETVAL magneto5_init ( magneto5_t *ctx, magneto5_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MAGNETO5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
//     i2c_master_set_timeout( &ctx->i2c, 0 );

    return MAGNETO5_OK;

}

// void magneto5_generic_write ( magneto5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
// {
//     uint8_t tx_buf[ 256 ];
//     uint8_t cnt;
//     
//     tx_buf[ 0 ] = reg;
//     
//     for ( cnt = 1; cnt <= len; cnt++ )
//     {
//         tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
//     }
//     
//     i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
// }
// 
// void magneto5_generic_read ( magneto5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
// {
//     i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
// }

uint8_t magneto5_set_status_reg ( magneto5_t *ctx )
{
    uint8_t write_reg[ 1 ];
    uint8_t read_reg[ 1 ];

    write_reg[ 0 ] = MAGNETO5_REG_STATUS;
    
    i2c_master_write_then_read( &ctx->i2c, write_reg, 1, read_reg, 1 );

    return read_reg[ 0 ];
}

uint8_t magneto5_get_product_id ( magneto5_t *ctx )
{    
    uint8_t write_reg[ 1 ];
    uint8_t read_reg[ 1 ];
    uint8_t status_read;
    
    write_reg[ 0 ] = MAGNETO5_REG_PRODUCT_ID;
    status_read = magneto5_set_status_reg( ctx );
    
    if (status_read & MAGNETO_STATUS_READ_DONE)
    {
        i2c_master_write_then_read( &ctx->i2c, write_reg, 1, read_reg, 1 );
        
        if (read_reg[ 0 ] != MAGNETO5_PRODUCT_ID)
        {
            return MAGNETO5_ERROR;
        }
        else
        {
            return  read_reg[ 0 ];
        }
    }
    Delay_10ms();
}

void magneto5_get_axis_data ( magneto5_t *ctx, int16_t *axis_buffer, uint8_t max_resolution )
{ 
    uint8_t write_reg[ 1 ];
    uint8_t read_reg[ 6 ];
    uint8_t read_status;
    uint16_t temp_data;

    write_reg[ 0 ] = 0x00;

    magneto5_config_register_0( ctx, MAGNETO5_CR0_TAKE_MEASUREMENT | MAGNETO5_CR0_REFILL_CAP );

    read_status = magneto5_set_status_reg( ctx );
    magneto5_config_register_0( ctx, max_resolution );
    measure_resolution( ctx, max_resolution );

    if (read_status & ( MAGNETO_STATUS_MEASUREMENT_DONE | MAGNETO_STATUS_READ_DONE ))
    {        
        i2c_master_write_then_read( &ctx->i2c, write_reg, 1, read_reg, 6 );

        axis_buffer[0] = read_reg[1];
        axis_buffer[0] <<= 8;
        axis_buffer[0] |= read_reg[0];
        
        axis_buffer[1] = read_reg[3];
        axis_buffer[1] = axis_buffer[1] << 8;
        axis_buffer[1] = axis_buffer[1] | read_reg[2];
        
        axis_buffer[2] = read_reg[5];
        axis_buffer[2] = axis_buffer[2] << 8;
        axis_buffer[2] = axis_buffer[2] | read_reg[4];
        
        axis_buffer[0] = axis_buffer[0] >> ctx->data_flag;
        axis_buffer[1] = axis_buffer[1] >> ctx->data_flag;
        axis_buffer[2] = axis_buffer[2] >> ctx->data_flag;
        magneto5_reset( ctx );
    }
}

float magneto5_get_axis_value ( magneto5_t *ctx, uint8_t axis, uint8_t max_resolution )
{
    int16_t axis_data[ 3 ];
    float axis_value;
    
    magneto5_get_axis_data( ctx, &axis_data[ 0 ], max_resolution );
    
    if ( axis == MAGNETO5_AXIS_X)
    {
        axis_value = ( float )axis_data[ 0 ] / ctx->max_resolution;
    }
    else if ( axis == MAGNETO5_AXIS_Y)
    {
        axis_value = ( float )axis_data[ 1 ] / ctx->max_resolution;
    }
    else if ( axis == MAGNETO5_AXIS_Z)
    {
        axis_value = ( float )axis_data[ 2 ] / ctx->max_resolution;
    }
    
    return axis_value;
}

void magneto5_config_register_0 ( magneto5_t *ctx, uint8_t config_data )
{    
    uint8_t write_reg[ 2 ];

    write_reg[ 0 ] = MAGNETO5_REG_INTERNAL_CONTROL_0;
    write_reg[ 1 ] = config_data;
    
    i2c_master_write( &ctx->i2c, write_reg, 2 );
    Delay_100ms();
}

void magneto5_config_register_1 ( magneto5_t *ctx, uint8_t config_data )
{    
    uint8_t write_reg[ 2 ];

    write_reg[ 0 ] = MAGNETO5_REG_INTERNAL_CONTROL_1;
    write_reg[ 1 ] = config_data;
    
    i2c_master_write( &ctx->i2c, write_reg, 2 );  
    Delay_100ms();
}

void magneto5_reset (  magneto5_t *ctx )
{
    uint8_t write_reg[ 2 ];

    write_reg[ 0 ] = MAGNETO5_REG_INTERNAL_CONTROL_0;
    write_reg[ 1 ] = MAGNETO5_CR0_RESET;
    
    i2c_master_write( &ctx->i2c, write_reg, 2 );  
}

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static void measure_resolution ( magneto5_t *ctx, uint8_t set_data )
{   
    if (set_data == MAGNETO5_CH0_16bits_8ms)
    {
        ctx->max_resolution = 2048.0;
        ctx->data_flag = 0;
    }
    else if (set_data == MAGNETO5_CH1_16bits_4ms)
    {
        ctx->max_resolution = 2048.0;
        ctx->data_flag = 0;
    }
    else if (set_data == MAGNETO5_CH2_14bits_2ms)
    {
        ctx->max_resolution = 512.0;
        ctx->data_flag = 2;
    }
    else if (set_data == MAGNETO5_CH3_12bits_1ms)
    {
        ctx->max_resolution = 128.0;
        ctx->data_flag = 4;
    }
}

// ------------------------------------------------------------------------- END

