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

#include "accel12.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void go_to_standby_mode ( accel12_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel12_cfg_setup ( accel12_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x4C;
}

ACCEL12_RETVAL accel12_init ( accel12_t *ctx, accel12_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ACCEL12_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ACCEL12_OK;
}

void accel12_default_cfg ( accel12_t *ctx )
{
    uint8_t temp;
    
    // Accel configuration 
    
    temp = ACCEL12_OUTCFG_RESOLUTION_14_bit | 
           ACCEL12_OUTCFG_RANGE_2g;
    accel12_configuration( ctx, ACCEL12_REG_OUTPUT_CONFIG, temp );

    temp = ACCEL12_SRTFR_RATE_256Hz | 
           ACCEL12_SRTFR_TAP_LATCH_DISABLE;
    accel12_configuration( ctx, ACCEL12_REG_SAMPLE_RATE_AND_TAP, temp );
    
    // TAP configuration 
    
    temp = ACCEL12_EINT_TAP_XP_ENABLE | 
           ACCEL12_EINT_TAP_YP_ENABLE | 
           ACCEL12_EINT_TAP_ZP_ENABLE |
           ACCEL12_EINT_TAP_XN_ENABLE | 
           ACCEL12_EINT_TAP_YN_ENABLE | 
           ACCEL12_EINT_TAP_ZN_ENABLE |
           ACCEL12_EINT_ACQ_INT_ENABLE;
    accel12_configuration( ctx, ACCEL12_REG_INTERRUPT_ENABLE, temp );

    temp = ACCEL12_TAPEN_TAP_X_POS_ENABLE | 
           ACCEL12_TAPEN_TAP_Y_POS_ENABLE | 
           ACCEL12_TAPEN_TAP_Z_POS_ENABLE |
           ACCEL12_TAPEN_TAP_X_NEG_ENABLE | 
           ACCEL12_TAPEN_TAP_Y_NEG_ENABLE | 
           ACCEL12_TAPEN_TAP_Z_NEG_ENABLE |
           ACCEL12_TAPEN_TAP_THRESHOLD | 
           ACCEL12_TAPEN_ALL_TAP_DISABLE;                                                     
    accel12_configuration( ctx, ACCEL12_REG_TAP_CONTROL, temp );
    
    accel12_configuration( ctx, ACCEL12_REG_TAP_X_DURATION, 0x7F );
    accel12_configuration( ctx, ACCEL12_REG_TAP_Y_DURATION, 0x7F );
    accel12_configuration( ctx, ACCEL12_REG_TAP_Z_DURATION, 0x7F );
 
    // Go to wake-up mode 
    
    temp = ACCEL12_MODE_WAKE_STATE | 
           ACCEL12_MODE_I2C_WDT_POS_DISABLE |
           ACCEL12_MODE_I2C_WDT_NEG_DISABLE | 
           ACCEL12_MODE_IPP_PUSH_PULL | 
           ACCEL12_MODE_IAH_ACTIVE_HIGH;
    accel12_generic_write( ctx, ACCEL12_REG_MODE_CONTROL, &temp, 1 );
}

void accel12_generic_write ( accel12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void accel12_generic_read ( accel12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void accel12_configuration ( accel12_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t mode;
    accel12_generic_read( ctx, ACCEL12_REG_DEVICE_STATUS, &mode, 1 );
    mode = mode & 0x01;
    
    if ( mode == 0x01 )
    {
       go_to_standby_mode( ctx );
    }
    
    // Delay for go to stand by mode 
    Delay_1ms( );
    
    accel12_generic_write( ctx, reg, &data_in, 1 );
}

int16_t accel12_get_one_axis ( accel12_t *ctx, uint8_t axis )
{
    int16_t axis_data;
    uint8_t read_reg[ 2 ];
    
    accel12_generic_read( ctx, axis, read_reg, 2 );
    
    axis_data = read_reg[ 1 ];
    axis_data <<= 8;
    axis_data |= read_reg[ 0 ];
    
    return axis_data;
}

void accel12_get_axis_data ( accel12_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis)
{
    *x_axis = accel12_get_one_axis( ctx, ACCEL12_REG_X_AXIS_LSB );
    *y_axis = accel12_get_one_axis( ctx, ACCEL12_REG_Y_AXIS_LSB );
    *z_axis = accel12_get_one_axis( ctx, ACCEL12_REG_Z_AXIS_LSB );
}

uint8_t accel12_get_tap_detection ( accel12_t *ctx )
{
    uint8_t tap;

    accel12_generic_read( ctx, ACCEL12_REG_GENERAL_STATUS, &tap, 1 );
    tap = tap & 0x3F;
    
    if ( tap == 0 )
    {
        return 0;
    }
    
    if ( ( tap & ACCEL12_GS_TAP_X_POSITIVE ) == ACCEL12_GS_TAP_X_POSITIVE )
    {
        return 1;
    }
    else if ( ( tap & ACCEL12_GS_TAP_X_NEGATIVE ) == ACCEL12_GS_TAP_X_NEGATIVE )
    {
        return 4;
    }

    if ( ( tap & ACCEL12_GS_TAP_Y_POSITIVE ) == ACCEL12_GS_TAP_Y_POSITIVE )
    {
        return 2;
    }
    else if ( ( tap & ACCEL12_GS_TAP_Y_NEGATIVE ) == ACCEL12_GS_TAP_Y_NEGATIVE )
    {
        return 5;
    }

    if ( ( tap & ACCEL12_GS_TAP_Z_POSITIVE ) == ACCEL12_GS_TAP_Z_POSITIVE )
    {
        return 3;
    }
    else if ( ( tap & ACCEL12_GS_TAP_Z_NEGATIVE ) == ACCEL12_GS_TAP_Z_NEGATIVE )
    {
        return 6;
    }
    
    return 0;
}

uint8_t accel12_get_interrupt_state ( accel12_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void go_to_standby_mode ( accel12_t *ctx )
{
    uint8_t tmp;
    tmp = ACCEL12_MODE_STANDBY_STATE |
          ACCEL12_MODE_I2C_WDT_NEG_DISABLE | ACCEL12_MODE_I2C_WDT_POS_DISABLE |
          ACCEL12_MODE_IPP_PUSH_PULL | ACCEL12_MODE_IAH_ACTIVE_HIGH;
    accel12_generic_write( ctx, ACCEL12_REG_MODE_CONTROL, &tmp, 1 );
}

// ------------------------------------------------------------------------- END

