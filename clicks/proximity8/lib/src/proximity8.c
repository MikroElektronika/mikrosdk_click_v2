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

#include "proximity8.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity8_cfg_setup ( proximity8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY8_DEVICE_SLAVE_ADDRESS;
}

PROXIMITY8_RETVAL proximity8_init ( proximity8_t *ctx, proximity8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY8_OK;
}

void proximity8_default_cfg ( proximity8_t *ctx )
{
    uint16_t w_temp;

    w_temp = PROXIMITY8_CFG12_PS_IT_8T | PROXIMITY8_CFG12_MPS_1 | 
                                        PROXIMITY8_CFG12_ITB_50us | 
                                        PROXIMITY8_CFG12_PERIOD_64ms | 
                                        PROXIMITY8_CFG12_INT_ENABLE | 
                                        PROXIMITY8_CFG12_SMART_PERS_ENABLE | 
                                        PROXIMITY8_CFG12_SD_POWER_ON;
    proximity8_generic_write( ctx, PROXIMITY8_REG_PS_CONFIG_12, &w_temp, 1 );
    
    w_temp = PROXIMITY8_CFG34_ON_SUNLIGHT_CANCEL | PROXIMITY8_CFG34_SC_CUR_X1 | 
                                                PROXIMITY8_CFG34_PS_OUTPUT_12bit | 
                                                PROXIMITY8_CFG34_VCSEL_I_20mA | 
                                                PROXIMITY8_CFG34_AF_MODE_AUTO | 
                                                PROXIMITY8_CFG34_FOR_TRIG_ONE_TIME;
    proximity8_generic_write( ctx, PROXIMITY8_REG_PS_CONFIG_34, &w_temp, 1 );
    
    w_temp = 0x0100;
    proximity8_generic_write( ctx, PROXIMITY8_REG_PS_CONFIG_5, &w_temp, 1 );
}

void proximity8_generic_write ( proximity8_t *ctx, uint8_t reg, uint16_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    uint8_t cnt2;
    
    cnt2 = 1;
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt2 ] = data_buf[ cnt ] >> 8; 
        tx_buf[ cnt2 + 1 ] = data_buf[ cnt ];

        cnt2 += 2;
    }  

    i2c_master_write( &ctx->i2c, tx_buf, len * 2 + 1 );   
}

void proximity8_generic_read ( proximity8_t *ctx, uint8_t reg, uint16_t *read_data )
{
    uint8_t tx_buf[ 1 ];
    uint8_t read_reg[ 2 ];

    tx_buf [ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, read_reg, 2 );

    *read_data = read_reg[ 1 ];
    *read_data <<= 8;
    *read_data |= read_reg[ 0 ];

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, read_reg, 2 );
}

uint8_t proximity8_get_interrupt_state ( proximity8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

