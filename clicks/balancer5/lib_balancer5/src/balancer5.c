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

#include "balancer5.h"


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void balancer5_cfg_setup ( balancer5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pg   = HAL_PIN_NC;
    cfg->pss = HAL_PIN_NC;
    cfg->cd   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = BALANCER5_SLAVE_ADDRESS;
}

BALANCER5_RETVAL balancer5_init ( balancer5_t *ctx, balancer5_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return BALANCER5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->cd, cfg->cd );

    // Input pins

    digital_in_init( &ctx->pg, cfg->pg );
    digital_in_init( &ctx->pss, cfg->pss );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return BALANCER5_OK;

}

void balancer5_default_cfg ( balancer5_t *ctx )
{   
    balancer5_write_data( ctx, BALANCER5_REG_ADC_CTRL, BALANCER5_ADC_CTRL_ENABLE |
                               BALANCER5_ADC_CTRL_CONT_CONV |
                               BALANCER5_ADC_CTRL_15BIT_RES );
}

void balancer5_generic_write ( balancer5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void balancer5_generic_read ( balancer5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t balancer5_read_data ( balancer5_t *ctx, uint8_t reg_addr )
{
    uint8_t temp_data;

    balancer5_generic_read(ctx, reg_addr, &temp_data, 1);

    return temp_data;
}

void balancer5_write_data ( balancer5_t *ctx, uint8_t reg_addr, uint8_t write_data )
{
    uint8_t write_buf;

    write_buf = write_data;

    balancer5_generic_write(ctx, reg_addr, &write_buf, 1);
}

void balancer5_charge ( balancer5_t *ctx, uint8_t state )
{
    digital_out_write(&ctx->cd, state);
}

uint8_t balancer5_get_int_status ( balancer5_t *ctx )
{
    uint8_t temp_pin;

    temp_pin = digital_in_read(&ctx->int_pin);
    return temp_pin;
}

uint8_t balancer5_get_power_good_status ( balancer5_t *ctx )
{
    uint8_t temp_pin;

    temp_pin = digital_in_read(&ctx->pg);
    return temp_pin;
}

uint8_t balancer5_get_power_source_status ( balancer5_t *ctx )
{
    uint8_t temp_pin;

    temp_pin = digital_in_read(&ctx->pss);
    return temp_pin;
}

uint8_t balancer5_check_id ( balancer5_t *ctx )
{
    uint8_t temp_id;

    temp_id = balancer5_read_data( ctx, BALANCER5_REG_PART_INFO );

    if ( temp_id == BALANCER5_DEVICE_ID )
    {
        return BALANCER5_SUCCESSFUL;
    }
    
    return BALANCER5_ERROR_ID;
}

// ------------------------------------------------------------------------- END

