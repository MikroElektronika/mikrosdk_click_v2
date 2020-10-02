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


#include "vcpmonitor.h"
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void vcpmonitor_cfg_setup ( vcpmonitor_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = VCPMONITOR_SLAVE_ADDR_GND_GND;
}

VCPMONITOR_RETVAL vcpmonitor_init ( vcpmonitor_t *ctx, vcpmonitor_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return VCPMONITOR_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    

    return VCPMONITOR_OK;
}

void vcpmonitor_default_cfg ( vcpmonitor_t *ctx )
{
       vcpmonitor_write_data (ctx, VCPMONITOR_REG_CONFIGURATION, 
                            VCPMONITOR_CFG_RESET_OFF | 
                            VCPMONITOR_CFG_NUM_OF_AVG_1 |
                            VCPMONITOR_CFG_VBUSCT_1p1ms |
                            VCPMONITOR_CFG_ISHCT_1p1ms |
                            VCPMONITOR_CFG_MODE_CURR_VOLT_CONT );
                            
     vcpmonitor_write_data( ctx, VCPMONITOR_REG_MASK_ENABLE, 
                            VCPMONITOR_MASK_OCL_DISABLE | 
                            VCPMONITOR_MASK_UCL_DISABLE |
                            VCPMONITOR_MASK_BOL_DISABLE | 
                            VCPMONITOR_MASK_BUL_DISABLE |
                            VCPMONITOR_MASK_POL_DISABLE | 
                            VCPMONITOR_MASK_CNVR_ENABLE |
                            VCPMONITOR_MASK_AFF_DISABLE | 
                            VCPMONITOR_MASK_CVRF_ENABLE |
                            VCPMONITOR_MASK_OVF_DISABLE | 
                            VCPMONITOR_MASK_APOL_DISABLE |
                            VCPMONITOR_MASK_LEN_DISABLE );

}

void vcpmonitor_generic_write ( vcpmonitor_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void vcpmonitor_generic_read ( vcpmonitor_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void vcpmonitor_write_data ( vcpmonitor_t *ctx, uint8_t reg, uint16_t tx_data )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = ( tx_data >> 8 ) & 0x00FF;
    tx_buf[ 1 ] = tx_data & 0x00FF;
    
    vcpmonitor_generic_read ( ctx, reg , tx_buf, 2 );
}

uint16_t vcpmonitor_read_data ( vcpmonitor_t *ctx, uint8_t reg_addr )
{
    uint16_t rx_data;
    uint8_t raw_data_n [ 2 ] ;
  
    vcpmonitor_generic_read ( ctx, reg_addr , raw_data_n, 2 );
    
    rx_data = raw_data_n[ 0 ];
    rx_data <<= 8;
    rx_data |= raw_data_n[ 1 ];
    
    return rx_data;
}

uint8_t vcpmonitor_get_interrupt_state( vcpmonitor_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

float vcpmonitor_get_current ( vcpmonitor_t *ctx )
{
    int16_t raw_data;
    float current_val;
    
    raw_data = vcpmonitor_read_data( ctx, VCPMONITOR_REG_CURRENT_DATA );
    current_val = ( float )( raw_data * CURRENT_CONSTANT );
    
    return current_val;
}
float vcpmonitor_get_voltage ( vcpmonitor_t *ctx )
{
    uint16_t raw_data;
    float voltage_val;

    raw_data = vcpmonitor_read_data( ctx, VCPMONITOR_REG_BUS_VOLTAGE_DATA );
    voltage_val = ( float )( raw_data * VOLTAGE_CONSTANT );

    return voltage_val;
}

float vcpmonitor_get_power ( vcpmonitor_t *ctx )
{
    uint16_t raw_data;
    float power_val;

    raw_data = vcpmonitor_read_data( ctx, VCPMONITOR_REG_POWER_DATA );
    power_val = ( float )( raw_data * POWER_CONSTANT );

    return power_val;
}

uint8_t vcpmonitor_get_id_value ( vcpmonitor_t *ctx, uint16_t *manufacture_id, uint16_t* did_id )
{
    uint8_t error = 0;
    uint16_t raw_data;
    
    raw_data = vcpmonitor_read_data( ctx, VCPMONITOR_REG_MANUFACTURE_ID );
    if ( raw_data != VCPMONITOR_DEF_MANUFACTURE_ID )
    {
        error += 1;
    }
    *manufacture_id = raw_data;
    
    raw_data = vcpmonitor_read_data( ctx, VCPMONITOR_REG_DIE_ID );
    if ( raw_data != VCPMONITOR_DEF_DIE_ID )
    {
        error += 2;
    }
    *did_id = raw_data;
    
    return error;
}

// ------------------------------------------------------------------------- END

