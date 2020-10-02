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

#include "boostinv.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BOOSTINV_VOLTAGE_POSITIVE_MIN            3200
#define BOOSTINV_VOLTAGE_POSITIVE_MAX            12750
#define BOOSTINV_VOLTAGE_NEGATIVE_MIN           -14000
#define BOOSTINV_VOLTAGE_NEGATIVE_MAX           -1200
#define BOOSTINV_VOLTAGE_NEGATIVE_ABS_MIN        13950
#define BOOSTINV_VOLTAGE_NEGATIVE_ABS_MAX        1200
#define BOOSTINV_VOLTAGE_CALC_DEV_FACT           50

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Its 200 ms delay until the EN ( RST ) 
 * changes the pin state from low to high.
 */
void boostinv_enable_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void boostinv_cfg_setup ( boostinv_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = BOOSTINV_I2C_SLAVE_ADDRESS_VCC;
}

BOOSTINV_RETVAL boostinv_init ( boostinv_t *ctx, boostinv_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return BOOSTINV_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    return BOOSTINV_OK;

}

void boostinv_default_cfg ( boostinv_t *ctx )
{
    // Click default configuration 
    
    boostinv_enable( ctx );
    
	boostinv_generic_write( ctx, BOOSTINV_REG_CONFIG, 
                                      BOOSTINV_CFG_PUSEQ_VOUTP_RAMP_1ST );
    boostinv_generic_write( ctx, BOOSTINV_REG_COMMAND, 
                                      BOOSTINV_CMD_REGISTER_SELECT_POS_VOUT |
                                      BOOSTINV_CMD_REGISTER_SELECT_NEG_VOUT |
                                      BOOSTINV_CMD_REGISTER_SELECT_CONFIG );
}

void boostinv_generic_write ( boostinv_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;
    
    i2c_master_write( &ctx->i2c, tx_buf, 2 ); 
}

uint8_t boostinv_generic_read ( boostinv_t *ctx, uint8_t reg )
{
    uint8_t rx_buf[ 1 ];

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, 1 );
    
    return rx_buf[ 0 ];
}

void boostinv_enable ( boostinv_t *ctx )
{
    digital_out_low( &ctx->en );
    boostinv_enable_delay( );
    digital_out_high( &ctx->en );
    boostinv_enable_delay( );
}

void boostinv_set_positive_voltage ( boostinv_t *ctx, uint16_t voltage )
{
    uint16_t v_p_val;
    uint16_t v_out_val;
    
    if ( voltage < BOOSTINV_VOLTAGE_POSITIVE_MIN )
    {
        v_out_val = BOOSTINV_VOLTAGE_POSITIVE_MIN;
    }
    else if ( voltage > BOOSTINV_VOLTAGE_POSITIVE_MAX )
    {
        v_out_val = BOOSTINV_VOLTAGE_POSITIVE_MAX;
    }
    else
    {
        v_out_val = voltage;
    }
    
    v_p_val = v_out_val - BOOSTINV_VOLTAGE_POSITIVE_MIN;
    v_p_val /= BOOSTINV_VOLTAGE_CALC_DEV_FACT;
    
    boostinv_generic_write( ctx, BOOSTINV_REG_POSITIVE_VOUT, v_p_val );
}

void boostinv_set_negative_voltage ( boostinv_t *ctx, int16_t voltage )
{
    uint16_t v_n_val;
    int16_t v_out_val;
    
    if ( voltage > BOOSTINV_VOLTAGE_NEGATIVE_MAX )
    {
        v_out_val = BOOSTINV_VOLTAGE_NEGATIVE_ABS_MAX;
    }
    else if ( voltage < BOOSTINV_VOLTAGE_NEGATIVE_MIN )
    {
        v_out_val = BOOSTINV_VOLTAGE_NEGATIVE_ABS_MIN;
    }
    else
    {
        v_out_val = - voltage;
    }
    
    v_n_val = v_out_val - BOOSTINV_VOLTAGE_NEGATIVE_ABS_MAX;
    v_n_val /= BOOSTINV_VOLTAGE_CALC_DEV_FACT;
    
    boostinv_generic_write( ctx, BOOSTINV_REG_NEGATIVE_VOUT, v_n_val );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void boostinv_enable_delay ( void )
{
    Delay_100ms( );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

