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

#include "thermo5.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo5_cfg_setup ( thermo5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO5_I2C_ADDRESS;
}

THERMO5_RETVAL thermo5_init ( thermo5_t *ctx, thermo5_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return THERMO5_OK;
}

void thermo5_generic_write ( thermo5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermo5_generic_read ( thermo5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void thermo5_write_byte ( thermo5_t *ctx, uint8_t wr_addr, uint8_t wr_data )
{
    thermo5_generic_write( ctx, wr_addr, &wr_data, 1 );
}

uint8_t thermo5_read_byte ( thermo5_t *ctx, uint8_t rd_addr )
{
    uint8_t r_buffer[ 1 ];

    thermo5_generic_read( ctx, rd_addr, r_buffer, 1 );

    return r_buffer[ 0 ];
}

uint16_t thermo5_read_data ( thermo5_t *ctx, uint16_t reg_addr )
{
    uint8_t reg_addr_high;
    uint8_t reg_addr_low;
    uint16_t result;

    reg_addr_low = ( uint8_t ) reg_addr;
    reg_addr_high = ( uint8_t ) ( reg_addr >> 8 );

    result = thermo5_read_byte( ctx, reg_addr_high );
    result <<= 8;
    result |= thermo5_read_byte( ctx, reg_addr_low );

    return result;
}

float thermo5_read_inter_temp ( thermo5_t *ctx )
{
    uint16_t inter_temp;
    uint8_t high_byte;
    uint8_t low_byte;
    float output;
    output = 0.0;

    high_byte = thermo5_read_byte( ctx, THERMO5_INTER_DIO_DATA_HI_BYTE );
    low_byte = thermo5_read_byte( ctx, THERMO5_INTER_DIO_DATA_LO_BYTE );

    inter_temp = high_byte;
    inter_temp <<= 8;
    inter_temp |= low_byte;
    inter_temp >>= 5;
    output = ( float )inter_temp;
    output *= 0.125;

    return output;
}

float thermo5_read_extern_1_temp ( thermo5_t *ctx )
{
    uint16_t extern_1_temp;
    uint8_t high_byte;
    uint8_t low_byte;
    float output;
    output = 0.0;

    high_byte = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_1_DATA_HI_BYTE );
    low_byte = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_1_DATA_LO_BYTE );

    extern_1_temp = high_byte;
    extern_1_temp <<= 8;
    extern_1_temp |= low_byte;
    extern_1_temp >>= 5;
    output = ( float )extern_1_temp;
    output *= 0.125;

    return output;
}

float thermo5_read_extern_2_temp ( thermo5_t *ctx )
{
    uint16_t extern_2_temp;
    uint8_t high_byte;
    uint8_t low_byte;
    float output;
    output = 0.0;

    high_byte = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_2_DATA_HI_BYTE );
    low_byte = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_2_DATA_LO_BYTE );

    extern_2_temp = high_byte;
    extern_2_temp <<= 8;
    extern_2_temp |= low_byte;
    extern_2_temp >>= 5;
    output = ( float )extern_2_temp;
    output *= 0.125;

    return output;
}

float thermo5_read_extern_3_temp ( thermo5_t *ctx )
{
    uint16_t extern_3_temp;
    uint8_t high_byte;
    uint8_t low_byte;
    float output;
    output = 0.0;

    high_byte = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_3_HI_BYTE );
    low_byte = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_3_LO_BYTE );

    extern_3_temp = high_byte;
    extern_3_temp <<= 8;
    extern_3_temp |= low_byte;
    extern_3_temp >>= 5;
    output = ( float )extern_3_temp;
    output *= 0.125;

    return output;
}

uint8_t thermo5_read_product_id ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_PRODUCT_ID );

    return result;
}

uint8_t thermo5_read_manufacturer_id ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_MANUFACTURER_ID );

    return result;
}

uint8_t thermo5_read_revision_register ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_REVISION );

    return result;
}

uint8_t thermo5_get_interrupt_state ( thermo5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t thermo5_read_stat_reg ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_STAT );

    if ( result == 0 )
    {
        return 0;
    }
    if ( result == 2 )
    {
        return 1;
    }
    if ( result == 4 )
    {
        return 2;
    }
    if ( result == 8 )
    {
        return 3;
    }
    if ( result == 10 )
    {
        return 4;
    }
    if ( result == 80 )
    {
        return 5;
    }
}

uint8_t thermo5_read_therm_limit_stat ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_THERM_LIM_STAT );
    result &= 0x0F;

    return result;
}

uint8_t thermo5_read_exter_diode_fault ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_FAULT );
    result >>= 1;
    result &= 0x03;

    return result;
}

uint8_t thermo5_read_low_limit_stat ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_LO_LIM_STAT );
    result &= 0x0F;

    return result;
}

uint8_t thermo5_read_high_limit_stat ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_HI_LIM_STAT );
    result &= 0x0F;

    return result;
}

void thermo5_write_config ( thermo5_t *ctx, uint8_t wr_data )
{
    thermo5_write_byte( ctx, THERMO5_CONFIG, wr_data );
}

uint8_t thermo5_read_config ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_CONFIG );

    return result;
}

void thermo5_set_convers_rate ( thermo5_t *ctx, uint8_t convers_rate )
{
    thermo5_write_byte( ctx, THERMO5_CONVERS_RATE, convers_rate );
}

uint8_t thermo5_read_convers_rate ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_CONVERS_RATE );

    return result;
}

void thermo5_set_filter_rate ( thermo5_t *ctx, uint8_t filter_decode_rate )
{
    thermo5_write_byte( ctx, THERMO5_FILTER_CONTROL, filter_decode_rate );
}

uint8_t thermo5_read_filter_rate ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_FILTER_CONTROL );

    return result;
}

void thermo5_set_diode_1_beta_config ( thermo5_t *ctx, uint8_t enable )
{
    enable <<= 3;
    thermo5_write_byte( ctx, THERMO5_EXTER_DIO_1_BETA_CONFIG, enable );
}

uint8_t thermo5_read_diode_1_beta_config ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_1_BETA_CONFIG );
    result >>= 1;
    result &= 0x03;

    return result;
}

void thermo5_set_diode_2_beta_config ( thermo5_t *ctx, uint8_t enable )
{
    enable <<= 3;
    thermo5_write_byte( ctx, THERMO5_EXTER_DIO_2_BETA_CONFIG, enable );
}

uint8_t thermo5_read_diode_2_beta_config ( thermo5_t *ctx )
{
    uint8_t result;

    result = thermo5_read_byte( ctx, THERMO5_EXTER_DIO_2_BETA_CONFIG );
    result >>= 1;
    result &= 0x03;

    return result;
}

// ------------------------------------------------------------------------- END

