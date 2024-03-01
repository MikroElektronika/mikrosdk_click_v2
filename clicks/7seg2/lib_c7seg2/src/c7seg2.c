/****************************************************************************
** Copyright (C) 2023 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file c7seg2.c
 * @brief 7-SEG 2 Click Driver.
 */

#include "c7seg2.h"

/**
 * @brief 7-SEG 2 digits and segments consts.
 * @details Specified bits setting for digits and segments selection of 7-SEG 2 Click driver.
 */
static const uint16_t digits[ C7SEG2_DIGITS_NUMBER ] = 
{ 0x03C9, 0x0009, 0x0383, 0x018B, 0x004B, 0x01CA, 0x03CA, 0x0109, 0x03CB, 0x014B };
static const uint16_t segments[ C7SEG2_SEGMENTS_NUMBER ] = { 0x0004, 0x0020, 0x0400 };

void c7seg2_cfg_setup ( c7seg2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = C7SEG2_DEVICE_ADDRESS;
}

err_t c7seg2_init ( c7seg2_t *ctx, c7seg2_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t c7seg2_sw_reset ( c7seg2_t *ctx )
{
    return c7seg2_write_reg( ctx, C7SEG2_REG_DEVICE_EN, C7SEG2_SW_RESET );
}

err_t c7seg2_default_cfg ( c7seg2_t *ctx ) 
{
    err_t error_flag = C7SEG2_OK;
    
    error_flag |= c7seg2_sw_reset( ctx );
    error_flag |= c7seg2_write_reg( ctx, C7SEG2_REG_DEVICE_EN, C7SEG2_ENABLE );
    
    error_flag |= c7seg2_set_segments_current ( ctx, C7SEG2_CURRENT_DEFAULT );

    return error_flag;
}

err_t c7seg2_generic_write ( c7seg2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t c7seg2_generic_read ( c7seg2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t c7seg2_get_int_pin ( c7seg2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t c7seg2_write_reg ( c7seg2_t *ctx, uint8_t reg, uint8_t data_in )
{
    return c7seg2_generic_write( ctx, reg, &data_in, 1 );
}

err_t c7seg2_read_reg ( c7seg2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return c7seg2_generic_read( ctx, reg, data_out, 1 );
}

err_t c7seg2_set_segments_current ( c7seg2_t *ctx, float current_val )
{
    uint8_t current_data = current_val * C7SEG2_CURRENT_STEP_TO_HEX;
    err_t error_flag = C7SEG2_OK;
    
    for ( uint8_t current_reg = C7SEG2_REG_CUR_LED_CS0; current_reg <= C7SEG2_REG_CUR_LED_CS11; current_reg++ )
    {
        error_flag |= c7seg2_write_reg( ctx, current_reg, current_data );
    }
        
    return error_flag;
}

err_t c7seg2_write_segment ( c7seg2_t *ctx, uint8_t segment, uint8_t digit, uint8_t dpt ) 
{
    uint16_t output = digits[ digit % C7SEG2_DIGITS_NUMBER ] | segments[ segment % C7SEG2_SEGMENTS_NUMBER ];
    if ( dpt )
    {
        output |= C7SEG2_DP_PIN_MASK;
    }
    uint8_t output_data[ 2 ] = { ( uint8_t ) ( output & 0xFF ), ( uint8_t ) ( ( output >> 8 ) & 0xFF ) };

    return c7seg2_generic_write( ctx, C7SEG2_REG_CH_EN_LOW, output_data, sizeof ( output_data ) );
}

err_t c7seg2_disable_segments ( c7seg2_t *ctx ) 
{
    uint16_t output = C7SEG2_SEGMENTS_DISABLED;
    uint8_t output_data[ 2 ] = { ( uint8_t ) ( output & 0xFF ), ( uint8_t ) ( ( output >> 8 ) & 0xFF ) };
    
    return c7seg2_generic_write( ctx, C7SEG2_REG_CH_EN_LOW, output_data, sizeof ( output_data ) );
}

err_t c7seg2_write_number ( c7seg2_t *ctx, uint16_t number, uint8_t dpt ) 
{
    err_t error_flag = C7SEG2_OK;
    
    uint8_t num_arr[ 3 ] = { 0 };
    uint16_t num = ( number >= C7SEG2_MAX_NUMBER ) ? C7SEG2_MAX_NUMBER : number;
    
    num_arr[ 2 ] = ( num / 100 ) % 10;
    num_arr[ 1 ] = ( num / 10 ) % 10;
    num_arr[ 0 ] = num % 10;
    
    for ( uint8_t seg = C7SEG2_SEGMENT_0; seg < C7SEG2_SEGMENTS_NUMBER; seg++ )
    {
        error_flag |= c7seg2_write_segment( ctx, seg, num_arr[ seg ], ( dpt & C7SEG2_DP_MASK ) == ( seg + 1 ) );
        for ( uint16_t del = 0; del < C7SEG2_REFRESH_RATE_DELAY; del++ )
        {
            Delay_50us( );
        }
    }
    error_flag |= c7seg2_disable_segments( ctx );
    return error_flag;
}

// ------------------------------------------------------------------------- END
