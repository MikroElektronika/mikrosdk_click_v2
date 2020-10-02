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

#include "irsense3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static int16_t read_data_u16 ( irsense3_t *ctx, uint8_t reg );
static uint8_t done_measurement( irsense3_t *ctx );
static void reset_measurement( irsense3_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void irsense3_cfg_setup ( irsense3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x60;
}

IRSENSE3_RETVAL irsense3_init ( irsense3_t *ctx, irsense3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return IRSENSE3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return IRSENSE3_OK;
}

void irsense3_default_cfg ( irsense3_t *ctx )
{
    uint8_t tmp;

    // Click default configuration

    tmp = IRSENSE3_CTRL2_NO_SYNC;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_2, &tmp, 1 );

    tmp = IRSENSE3_CTRL3_LOW_NOISE_DISABLE | IRSENSE3_CTRL3_ODR_10Hz |
          IRSENSE3_CTRL3_TEMP_FILTER_0p445Hz | IRSENSE3_CTRL3_IR_FILTER_0p9Hz;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_3, &tmp, 1 );

    tmp = IRSENSE3_CTRL4_TOPT_NOISE_DISABLE | IRSENSE3_CTRL4_TOPT_THR_DISABLE;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_4, &tmp, 1 );

    tmp = 0x80;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_5, &tmp, 1 );

    tmp = 0xFF;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_6, &tmp, 1 );

    tmp = IRSENSE3_CTRL7_HUMAN_DETECT_NORMAL | IRSENSE3_CTRL7_HUMAN_DETECT_TIME_0sec;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_7, &tmp, 1 );

    tmp = 0x81;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_8, &tmp, 1 );

    tmp = 0x2C;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_9, &tmp, 1 );

    tmp = 0x81;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_10, &tmp, 1 );


    tmp = IRSENSE3_CTRL11_HBDEN_ON | IRSENSE3_CTRL11_DO_NOT_STOP_UPDATING_SB |
          IRSENSE3_CTRL11_STREAMING_BUFFER_ON | IRSENSE3_CTRL11_INT_HUMAN_ENABLE |
          IRSENSE3_CTRL11_INT_DRDY_ENABLE;

    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_11, &tmp, 1 );

    tmp = IRSENSE3_CTRL12_CONTINUOUS_MODE;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_12, &tmp, 1 );
}

void irsense3_generic_write ( irsense3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void irsense3_generic_read ( irsense3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t irsense3_get_interrupt_state ( irsense3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

float irsense3_get_temperature_data ( irsense3_t *ctx )
{
    int16_t temp_out;
    float temperature;

    temp_out = read_data_u16( ctx, IRSENSE3_REG_TEMP_LSB );

    temperature = ( temp_out * 0.0019837) + 25.0;

    done_measurement( ctx );

    return temperature;
}

float irsense3_get_ir_sensor_data ( irsense3_t *ctx )
{
    int16_t ir_out;
    float ir_data;

    ir_out = read_data_u16( ctx, IRSENSE3_REG_IR_LSB );

    ir_data = (float)( ir_out * 0.4578 );

    done_measurement( ctx );

    return ir_data;
}

uint8_t irsense3_human_approach_detect ( irsense3_t *ctx )
{
    uint8_t status;

    irsense3_generic_read( ctx, IRSENSE3_REG_STATUS_3, &status, 1 );

    if ( ( status & 0x10 ) != 0x00 )
    {
        reset_measurement( ctx );

        return IRSENSE3_PRESENCE_IS_DETECTED;
    }
    return IRSENSE3_PRESENCE_IS_NOT_DETECTED;
}

void irsense3_software_reset( irsense3_t *ctx )
{
    uint8_t tmp;

    tmp = IRSENSE3_CTRL1_SOFTWARE_RESET;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_1, &tmp, 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t done_measurement( irsense3_t *ctx )
{
    uint8_t status;

    irsense3_generic_read( ctx, IRSENSE3_REG_STATUS_2, &status, 2 );

    return status;
}

static void reset_measurement( irsense3_t *ctx )
{
    uint8_t tmp;

    tmp = IRSENSE3_CTRL12_STANDBY_MODE;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_12, &tmp, 1 );

    Delay_100ms();
    Delay_100ms();
    Delay_100ms();

    tmp = IRSENSE3_CTRL12_CONTINUOUS_MODE;
    irsense3_generic_write( ctx, IRSENSE3_REG_CTRL_12, &tmp, 1 );

    Delay_100ms();
}

static int16_t read_data_u16 ( irsense3_t *ctx, uint8_t reg )
{
    uint8_t rx_buf[ 2 ];
    uint16_t rx_data;

    irsense3_generic_read( ctx, reg, rx_buf, 2 );

    rx_data = rx_buf[ 1 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 0 ];

    return rx_data;
}
// ------------------------------------------------------------------------- END

