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

#include "dcmotor7.h"

// ---------------------------------------------------------- PRIVATE VARIABLES

static uint8_t port_data = 0xFF;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dcmotor7_cfg_setup ( dcmotor7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pwma = HAL_PIN_NC;
    cfg->pwmb = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = DCMOTOR7_SLAVE_ADDRESS_1_1;
}

DCMOTOR7_RETVAL dcmotor7_init ( dcmotor7_t *ctx, dcmotor7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return DCMOTOR7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->pwma, cfg->pwma );
    digital_out_init( &ctx->pwmb, cfg->pwmb );

    return DCMOTOR7_OK;
}

void dcmotor7_default_cfg ( dcmotor7_t *ctx )
{
    dcmotor7_generic_write( ctx, DCMOTOR7_CMD_CONFIGURATION, DCMOTOR7_ENABLE_ALL_OUTPUT_PORT );
    dcmotor7_set_tblkab( ctx, DCMOTOR7_TBLK_FOSCM_X6_CLK );
    dcmotor7_set_hb_mode( ctx, DCMOTOR7_HBMODE_SMALL_MODE );
}

void dcmotor7_generic_write ( dcmotor7_t *ctx, uint8_t reg, uint8_t tmp )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tmp;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );    
}

void dcmotor7_generic_read ( dcmotor7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void dcmotor7_set_port ( dcmotor7_t *ctx, uint8_t port, uint8_t value )
{
    if ( value == 1 )
    {
        port_data = port_data | port;
    }
    else
    {
       port_data = port_data & ( ~port );
    }
    
    dcmotor7_generic_write( ctx, DCMOTOR7_CMD_OUTPUT_PORT, port_data );
}

void dcmotor7_set_motor ( dcmotor7_t *ctx, uint8_t motor, uint8_t in1, uint8_t in2 )
{
    if ( motor == DCMOTOR7_MOTOR_A )
    {
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_4, in1 );
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_3, in2 );
        digital_out_high( &ctx->pwma );
    }
    else
    {
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_2, in1 );
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_1, in2 );
        digital_out_high( &ctx->pwmb );
    }
}

void dcmotor7_set_tblkab ( dcmotor7_t *ctx, uint8_t tblk )
{
    dcmotor7_set_port( ctx, DCMOTOR7_PORT_0, tblk );
}

void dcmotor7_set_hb_mode ( dcmotor7_t *ctx, uint8_t mode )
{
    dcmotor7_set_port( ctx, DCMOTOR7_PORT_5, mode );
}

void dcmotor7_motor_stop ( dcmotor7_t *ctx, uint8_t motor )
{
    if ( motor == DCMOTOR7_MOTOR_A )
    {
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_4, 0 );
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_3, 0 );
        digital_out_high( &ctx->pwma );
    }
    else
    {
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_2, 0 );
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_1, 0 );
        digital_out_high( &ctx->pwmb );
    }
}

void dcmotor7_go_to_stand_by_mode ( dcmotor7_t *ctx, uint8_t motor )
{
    if ( motor == DCMOTOR7_MOTOR_A )
    {
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_4, 0 );
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_3, 0 );
        digital_out_low( &ctx->pwma );
    }
    else
    {
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_2, 0 );
        dcmotor7_set_port( ctx, DCMOTOR7_PORT_1, 0 );
        digital_out_low( &ctx->pwmb );
    }
}

void dcmotor7_set_pwm_motor_a ( dcmotor7_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->pwma, state );
}

void dcmotor7_set_pwm_motor_b ( dcmotor7_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->pwmb, state );
}

// ------------------------------------------------------------------------- END

