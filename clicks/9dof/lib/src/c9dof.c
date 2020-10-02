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

#include "c9dof.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C9DOF_COMM_MODE_ACCEL_GYRO        0
#define C9DOF_COMM_MODE_MAG               1
#define C9DOF_ACCEL_GYRO_POWER_MODE_OFF   0
#define C9DOF_ACCEL_GYRO_POWER_MODE_ON    1

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Get axis function.
 *
 * @param ctx          Click object.
 * @param w_mode       Write mode
 * <pre>
 * 0 ( C9DOF_COMM_MODE_ACCEL_GYRO ) : Communication with Accel and Gyro sensor.
 * </pre>
 * <pre>
 * 1 ( C9DOF_COMM_MODE_MAG )        : Communication with Magnetic sensor.
 * </pre> 
 * @param adr_reg_low  LSB data register address.
 */
static int16_t dev_get_axis ( c9dof_t *ctx, uint8_t w_mode, uint8_t adr_reg_lsb );

/**
 * @brief Communication 10 ms delay function.
 */
static void dev_communication_delay ( void );

/**
 * @brief Configuration 10 ms delay function.
 */
static void dev_set_config_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c9dof_cfg_setup ( c9dof_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address_ag = C9DOF_SLAVE_ADDRESS_ACCEL_GYRO_0;
    cfg->i2c_address_m = C9DOF_SLAVE_ADDRESS_MAG_0;
}

C9DOF_RETVAL c9dof_init ( c9dof_t *ctx, c9dof_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed   = cfg->i2c_speed;
    i2c_cfg.scl     = cfg->scl;
    i2c_cfg.sda     = cfg->sda;

    ctx->slave_address_ag = cfg->i2c_address_ag;
    ctx->slave_address_m = cfg->i2c_address_m;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return C9DOF_INIT_ERROR;
    }

    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C9DOF_OK;
}

void c9dof_default_cfg ( c9dof_t *ctx )
{
    // Click default configuration
    
    uint8_t tmp;
    
    // Enable accel and gyro sensors
    
    c9dof_set_power_mode( ctx, C9DOF_ACCEL_GYRO_POWER_MODE_ON );
    dev_set_config_delay( );
    
    // Accel & Gyro
    
    tmp = C9DOF_CTRL_REG4_CONFIG; 
    c9dof_generic_write_accel_gyro( ctx, C9DOF_REG_CTRL_REG4, &tmp, 1 );
    dev_set_config_delay( );
    
    tmp = C9DOF_CTRL_REG1_G_CONFIG; 
    c9dof_generic_write_accel_gyro( ctx, C9DOF_REG_CTRL_REG1_G, &tmp, 1 );
    dev_set_config_delay( );
    
    tmp = C9DOF_CTRL_REG5_XL_CONFIG; 
    c9dof_generic_write_accel_gyro( ctx, C9DOF_REG_CTRL_REG5_XL, &tmp, 1 );
    dev_set_config_delay( );
    
    tmp = C9DOF_CTRL_REG6_XL_CONFIG; 
    c9dof_generic_write_accel_gyro( ctx, C9DOF_REG_CTRL_REG6_XL, &tmp, 1 );
    dev_set_config_delay( );
    
    tmp = C9DOF_CTRL_REG8_CONFIG;
    c9dof_generic_write_accel_gyro( ctx, C9DOF_REG_CTRL_REG8, &tmp, 1 );
    dev_set_config_delay( );
    
    // Magnetometar
    
    tmp = C9DOF_CTRL_REG1_M_CONFIG;
    c9dof_generic_write_mag( ctx, C9DOF_REG_CTRL_REG1_M, &tmp, 1 );
    dev_set_config_delay( );
    
    tmp = C9DOF_CTRL_REG2_M_CONFIG;
    c9dof_generic_write_mag( ctx, C9DOF_REG_CTRL_REG2_M, &tmp, 1 );
    dev_set_config_delay( );
    
    tmp = C9DOF_CTRL_REG3_M_CONFIG;
    c9dof_generic_write_mag( ctx, C9DOF_REG_CTRL_REG3_M, &tmp, 1 );
    dev_set_config_delay( );
    
    tmp = C9DOF_CTRL_REG4_M_CONFIG;
    c9dof_generic_write_mag( ctx, C9DOF_REG_CTRL_REG4_M,  &tmp, 1 );
    dev_set_config_delay( );
    
    tmp = C9DOF_CTRL_REG5_M_CONFIG;
    c9dof_generic_write_mag( ctx, C9DOF_REG_CTRL_REG5_M,  &tmp, 1 );
    dev_set_config_delay( );
}

void c9dof_set_power_mode ( c9dof_t *ctx, uint8_t pwr_mode )
{
    if ( pwr_mode == C9DOF_ACCEL_GYRO_POWER_MODE_OFF )
    {
        digital_out_low( &ctx->en );
    }
    else if ( pwr_mode == C9DOF_ACCEL_GYRO_POWER_MODE_ON )
    {
        digital_out_high( &ctx->en );
    }
}

void c9dof_generic_write_accel_gyro ( c9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_ag );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );      
}

void c9dof_generic_read_accel_gyro ( c9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_ag );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void c9dof_generic_write_mag ( c9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_m );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );  
}

void c9dof_generic_read_mag ( c9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_m );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void c9dof_read_accel ( c9dof_t *ctx, c9dof_accel_data_t *accel_data )
{   
    accel_data->x = dev_get_axis( ctx, C9DOF_COMM_MODE_ACCEL_GYRO, C9DOF_REG_OUT_X_L_XL );
    accel_data->y = dev_get_axis( ctx, C9DOF_COMM_MODE_ACCEL_GYRO, C9DOF_REG_OUT_Y_L_XL );
    accel_data->z = dev_get_axis( ctx, C9DOF_COMM_MODE_ACCEL_GYRO, C9DOF_REG_OUT_Z_L_XL );
}

void c9dof_read_gyro ( c9dof_t *ctx, c9dof_gyro_data_t *gyro_data )
{
    gyro_data->x = dev_get_axis( ctx, C9DOF_COMM_MODE_ACCEL_GYRO, C9DOF_REG_OUT_X_L_G );
    gyro_data->y = dev_get_axis( ctx, C9DOF_COMM_MODE_ACCEL_GYRO, C9DOF_REG_OUT_Y_L_G );
    gyro_data->z = dev_get_axis( ctx, C9DOF_COMM_MODE_ACCEL_GYRO, C9DOF_REG_OUT_Z_L_G );
}

void c9dof_read_mag ( c9dof_t *ctx, c9dof_mag_data_t *mag_data )
{
    mag_data->x = dev_get_axis( ctx, C9DOF_COMM_MODE_MAG, C9DOF_REG_OUT_X_L_M );
    mag_data->y = dev_get_axis( ctx, C9DOF_COMM_MODE_MAG, C9DOF_REG_OUT_Y_L_M );
    mag_data->z = dev_get_axis( ctx, C9DOF_COMM_MODE_MAG, C9DOF_REG_OUT_Z_L_M );
}

uint8_t c9dof_get_interrupt ( c9dof_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static int16_t dev_get_axis ( c9dof_t *ctx, uint8_t r_mode, uint8_t adr_reg_lsb )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];
    
    if ( r_mode == C9DOF_COMM_MODE_ACCEL_GYRO )
    {
        c9dof_generic_read_accel_gyro ( ctx, adr_reg_lsb, &rx_buf, 2 );
    }
    else if ( r_mode == C9DOF_COMM_MODE_MAG )
    {
        c9dof_generic_read_mag ( ctx, adr_reg_lsb, &rx_buf, 2 );    
    }

    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];

    return result;
}

static void dev_communication_delay ( void )
{
    Delay_10ms( );
}

static void dev_set_config_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

