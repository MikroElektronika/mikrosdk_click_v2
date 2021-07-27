/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright ( c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 */

#include "magneto8.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void magneto8_cfg_setup ( magneto8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = MAGNETO8_SLAVE_ADDR;
}

MAGNETO8_RETVAL magneto8_init ( magneto8_t *ctx, magneto8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MAGNETO8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->cs, cfg->cs );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return MAGNETO8_OK;
}

void magneto8_default_cfg ( magneto8_t *ctx )
{
    uint16_t cfg_data;

    cfg_data = MAGNETO8_CFG_MODE_NOM | 
               MAGNETO8_CFG_HYST_OFF | 
               MAGNETO8_CFG_SF_2x | 
               MAGNETO8_CFG_FTH_SLOW |
               MAGNETO8_CFG_WD_ON;
    magneto8_generic_write( ctx, MAGNETO8_REG_CONF_C1, ( uint8_t )( cfg_data >> 8 ) );
    magneto8_generic_write( ctx, MAGNETO8_REG_CONF_C2, ( uint8_t )( cfg_data ) );
    magneto8_generic_write( ctx, MAGNETO8_REG_ABN, MAGNETO8_ABN_64 );
}

void magneto8_generic_write ( magneto8_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data; 

    i2c_master_write( &ctx->i2c, tx_buf, 2 );  
}

uint8_t magneto8_generic_read ( magneto8_t *ctx, uint8_t reg )
{
    uint8_t rx_data;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, &rx_data, 1 );
    
    return rx_data;
}

uint16_t magneto8_get_raw_angle ( magneto8_t *ctx )
{
    uint16_t raw_data;

    raw_data = magneto8_generic_read( ctx, MAGNETO8_REG_RAW_ANGLE_MSB );
    raw_data <<= 8;
    raw_data |= magneto8_generic_read( ctx, MAGNETO8_REG_RAW_ANGLE_LSB );
    raw_data &= 0x0FFF;
    
    return raw_data;
}

uint16_t magneto8_get_angle_data ( magneto8_t *ctx )
{
    uint16_t angle;

    angle = magneto8_generic_read( ctx, MAGNETO8_REG_ANGLE_MSB );
    angle <<= 8;
    angle |= magneto8_generic_read( ctx, MAGNETO8_REG_ANGLE_LSB );
    angle &= 0x0FFF;
    
    return angle;
}

uint8_t magneto8_get_status ( magneto8_t *ctx )
{
    return magneto8_generic_read( ctx, MAGNETO8_REG_STATUS );
}

uint16_t magneto8_get_magnitude ( magneto8_t *ctx )
{
    uint16_t magnitude;

    magnitude = magneto8_generic_read( ctx, MAGNETO8_REG_MAGNITUDE_MSB );
    magnitude <<= 8;
    magnitude |= magneto8_generic_read( ctx, MAGNETO8_REG_MAGNITUDE_LSB );
    magnitude &= 0x0FFF;
    
    return magnitude;
}

uint8_t magneto8_get_agc ( magneto8_t *ctx )
{
    return magneto8_generic_read( ctx, MAGNETO8_REG_AGC );
}

uint8_t magneto8_get_zmco ( magneto8_t *ctx )
{
    return magneto8_generic_read( ctx, MAGNETO8_REG_ZMCO );
}

uint8_t magneto8_a_pin_state ( magneto8_t *ctx )
{
   return digital_in_read( &ctx->rst );
}

uint8_t magneto8_b_pin_state ( magneto8_t *ctx )
{
   return digital_in_read( &ctx->cs );
}

uint8_t magneto8_psh_pin_state ( magneto8_t *ctx )
{
   return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

