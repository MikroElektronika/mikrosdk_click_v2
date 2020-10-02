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

#include "pressure6.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PRESSURE6_REG_MANUFACTURER_ID                0x0F
#define PRESSURE6_REG_PART_ID                        0x10
#define PRESSURE6_REG_POWER_DOWN                     0x12
#define PRESSURE6_REG_RESET                          0x13
#define PRESSURE6_REG_IIR_FIFO_CONTROL               0x15
#define PRESSURE6_REG_FIFO_DATA                      0x18
#define PRESSURE6_REG_STATUS                         0x19
#define PRESSURE6_REG_PRESSURE_DATA                  0x1A
#define PRESSURE6_REG_PRESSURE_DATA_OUT_MSB          0x1A
#define PRESSURE6_REG_PRESSURE_DATA_OUT_LSB          0x1B
#define PRESSURE6_REG_PRESSURE_DATA_OUT_XL           0x1C
#define PRESSURE6_REG_TEMP_DATA                      0x1D
#define PRESSURE6_REG_TEMP_DATA_OUT_MSB              0x1D
#define PRESSURE6_REG_TEMP_DATA_OUT_LSB              0x1E
#define PRESSURE6_DEF_SLAVE_ADDRESS                  0x5D
#define PRESSURE6_DEF_MANUFACTURER_ID                0xE0
#define PRESSURE6_DEF_PART_ID                        0x33
#define PRESSURE6_DEVICE_POWER_DOWN                  0x00
#define PRESSURE6_DEVICE_ACTIVE                      0x01
#define PRESSURE6_MEASURE_CTRL_BLOCK_IS_RESET        0x00
#define PRESSURE6_MEASURE_CTRL_BLOCK_IS_ACTIVE       0x01
#define PRESSURE6_FIFO_EN_MODE_BYPASS                0x00
#define PRESSURE6_FIFO_EN_MODE_ENABLED               0x80
#define PRESSURE6_WATER_MARK_LEVEL_24                0x00
#define PRESSURE6_WATER_MARK_LEVEL_28                0x40
#define PRESSURE6_IIR_MODE_IIR_OFF                   0x00
#define PRESSURE6_IIR_MODE_IIR_ON_WEAK               0x01
#define PRESSURE6_IIR_MODE_IIR_ON_MIDDLE             0x02
#define PRESSURE6_IIR_MODE_IIR_ON_STRONG             0x03

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure6_cfg_setup ( pressure6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dri = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x5D;
}

PRESSURE6_RETVAL pressure6_init ( pressure6_t *ctx, pressure6_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PRESSURE6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->dri, cfg->dri );
    
    return PRESSURE6_OK;
}

void pressure6_default_cfg ( pressure6_t *ctx )
{
    pressure6_power_on( ctx );
    pressure6_write_byte( ctx, PRESSURE6_REG_MODE_CONTROL,
                               PRESSURE6_MC_AVE_NUM_SINGLE |
                               PRESSURE6_MC_DATA_READY_ENABLED |
                               PRESSURE6_MC_FULL_DATA_ENABLED |
                               PRESSURE6_MC_WATER_MARK_ENABLED |
                               PRESSURE6_MC_MODE_CONTINUOUS );
}


void pressure6_write_byte ( pressure6_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = data_in;   

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t pressure6_read_byte ( pressure6_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 1 ];

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, tx_buf, 1 );

    return tx_buf[ 0 ];
}

uint16_t pressure6_get_pressure ( pressure6_t *ctx )
{
    uint32_t pressure_counts = 0;
    uint32_t pressure_value = 0;

    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 3 ];

    tx_buf[ 0 ] = PRESSURE6_REG_PRESSURE_DATA;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 3 );

    pressure_counts = tx_buf[ 0 ];
    pressure_counts = pressure_counts << 8;
    pressure_counts |= tx_buf[ 1 ];
    pressure_counts = pressure_counts << 8;
    pressure_counts |= tx_buf[ 2 ];
    pressure_counts >>= 2;

    pressure_value = pressure_counts / 2048;

    return pressure_value;
}

uint8_t pressure6_get_temperature ( pressure6_t *ctx )
{
    uint16_t temp_counts;
    uint8_t temp_value;

    temp_counts = pressure6_read_byte( ctx, PRESSURE6_REG_TEMP_DATA );
    temp_counts <<= 8;
    temp_counts |= pressure6_read_byte( ctx, PRESSURE6_REG_TEMP_DATA_OUT_LSB );

    temp_value = temp_counts / 32;

    return temp_value;
}

uint8_t pressure6_get_interrupt ( pressure6_t *ctx )
{
    return digital_in_read( &ctx->dri );
}

uint8_t pressure6_get_status ( pressure6_t *ctx)
{
    uint8_t status;

    status = pressure6_read_byte( ctx, PRESSURE6_REG_STATUS );
    return status;
}

void pressure6_power_on ( pressure6_t *ctx )
{
    pressure6_write_byte( ctx, PRESSURE6_REG_POWER_DOWN, PRESSURE6_DEVICE_ACTIVE );
    pressure6_write_byte( ctx, PRESSURE6_REG_RESET, PRESSURE6_MEASURE_CTRL_BLOCK_IS_ACTIVE );
    pressure6_write_byte( ctx, PRESSURE6_REG_MODE_CONTROL, PRESSURE6_MC_MODE_STAND_BY );
}

void pressure6_power_off ( pressure6_t *ctx )
{
    pressure6_write_byte( ctx, PRESSURE6_REG_RESET, PRESSURE6_MEASURE_CTRL_BLOCK_IS_RESET );
    pressure6_write_byte( ctx, PRESSURE6_REG_POWER_DOWN, PRESSURE6_DEVICE_POWER_DOWN );
}

void pressure6_waiting_for_new_data ( pressure6_t *ctx )
{
    uint8_t status;
    uint16_t cnt = 0;

    do
    {
        cnt++;

        if ( cnt > 1000 )
        {
            return;
        }
        
        status = pressure6_get_status( ctx );
        
        Delay_10ms();

    }
    while( ( status & 0x01 ) == 0 );
}

// ------------------------------------------------------------------------- END


