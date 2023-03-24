/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file ambient15.c
 * @brief Ambient 15 Click Driver.
 */

#include "ambient15.h"

void ambient15_cfg_setup ( ambient15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT15_SET_DEV_ADDR_GND;
}

err_t ambient15_init ( ambient15_t *ctx, ambient15_cfg_t *cfg ) 
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

err_t ambient15_default_cfg ( ambient15_t *ctx ) 
{
    err_t error_flag = AMBIENT15_OK;

    if ( AMBIENT15_ERROR == ambient15_check_communication ( ctx ) )
    {
        return AMBIENT15_ERROR;
    }
    // enable adc, enable power
    error_flag |= ambient15_write_register ( ctx, AMBIENT15_REG_CONTROL, AMBIENT15_CONTROL_POWER_ON | 
                                                                         AMBIENT15_CONTROL_ADC_ENABLE );
    // set default atime - 200ms
    error_flag |= ambient15_set_atime ( ctx, AMBIENT15_DEFAULT_ATIME );
    
    // set gain to 16x
    error_flag |= ambient15_set_gain ( ctx, AMBIENT15_GAIN_16X );
    
    // enable interrupts
    error_flag |= ambient15_write_register ( ctx, AMBIENT15_REG_INTERRUPT, AMBIENT15_ENABLE_INTERRUPT );
    
    return error_flag;
}

err_t ambient15_generic_write ( ambient15_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 32 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t ambient15_generic_read ( ambient15_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t ambient15_write_register ( ambient15_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg | AMBIENT15_CMD_BIT;
    data_buf[ 1 ] = data_in;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t ambient15_read_register ( ambient15_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    reg |= AMBIENT15_CMD_BIT;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

uint8_t ambient15_get_int_pin ( ambient15_t *ctx ) 
{
    return digital_in_read ( &ctx->int_pin );
}

err_t ambient15_check_communication ( ambient15_t *ctx )
{
    uint8_t id_partno = 0;
    uint8_t id2 = 0;
    err_t error_flag = ambient15_read_register ( ctx, AMBIENT15_REG_ID, &id_partno );
    error_flag |= ambient15_read_register ( ctx, AMBIENT15_REG_ID2, &id2 );
    if ( ( AMBIENT15_OK == error_flag ) && 
         ( AMBIENT15_ID_PARTNO == ( id_partno & 0xF0 ) ) && 
         ( AMBIENT15_ID2 & id2 ) )
    {
        return AMBIENT15_OK;
    }
    return AMBIENT15_ERROR;
}

err_t ambient15_set_atime ( ambient15_t *ctx, float atime_ms )
{
    uint8_t atime = 0;
    if ( atime_ms >= AMBIENT15_ATIME_MAX ) 
    {
        atime = 1;
        ctx->atime_ms = AMBIENT15_ATIME_MAX;
    }
    else if ( atime_ms <= AMBIENT15_ATIME_MIN )
    {
        atime = 0xFF;
        ctx->atime_ms = AMBIENT15_ATIME_MIN;
    }
    else
    {
        atime = 0xFF - ( uint8_t ) ( atime_ms / AMBIENT15_ATIME_STEP );
        ctx->atime_ms = atime_ms;
    }
    return ambient15_write_register( ctx, AMBIENT15_REG_TIMING, atime );
}

err_t ambient15_set_gain ( ambient15_t *ctx, uint8_t gain )
{
    switch ( gain )
    {
        case AMBIENT15_GAIN_1X:
        {
            ctx->gain = 1;
            break;
        }
        case AMBIENT15_GAIN_8X:
        {
            ctx->gain = 8;
            break;
        }
        case AMBIENT15_GAIN_16X:
        {
            ctx->gain = 16;
            break;
        }
        case AMBIENT15_GAIN_111X:
        {
            ctx->gain = 111;
            break;
        }
        default:
        {
            return AMBIENT15_ERROR;
        }
    }
    return ambient15_write_register( ctx, AMBIENT15_REG_ANALOG, gain );
}

err_t ambient15_read_raw_data ( ambient15_t *ctx, uint16_t *ch_0, uint16_t *ch_1 ) 
{
    uint8_t rx_data = 0;
    err_t error_flag = ambient15_read_register( ctx, AMBIENT15_REG_CONTROL, &rx_data );
    if ( ( rx_data & AMBIENT15_CONTROL_ADC_VALID ) && 
         ( rx_data & AMBIENT15_CONTROL_ADC_INTR ) && 
         ( AMBIENT15_OK == error_flag ) )
    {
        error_flag |= ambient15_read_register( ctx, AMBIENT15_REG_DATA0_LOW, &rx_data );
        *ch_0 = rx_data;
        error_flag |= ambient15_read_register( ctx, AMBIENT15_REG_DATA0_HIGH, &rx_data );
        *ch_0 |= ( ( uint16_t ) rx_data << 8 );
        
        error_flag |= ambient15_read_register( ctx, AMBIENT15_REG_DATA1_LOW, &rx_data );
        *ch_1 = rx_data;
        error_flag |= ambient15_read_register( ctx, AMBIENT15_REG_DATA1_HIGH, &rx_data );
        *ch_1 |= ( ( uint16_t ) rx_data << 8 );
        
        // clear interrupts
        ambient15_generic_write ( ctx, AMBIENT15_CMD_BIT | 
                                       AMBIENT15_TRANSACTION_SPEC_FUNC | 
                                       AMBIENT15_SPEC_FUNC_INT_CLEAR, 0, 0 );
        return error_flag;
    }
    return AMBIENT15_ERROR;
}

err_t ambient15_measure_light_level ( ambient15_t *ctx, uint16_t *lux ) 
{
    uint16_t ch0, ch1;
    err_t error_flag = ambient15_read_raw_data ( ctx, &ch0, &ch1 );
    
    if ( AMBIENT15_OK == error_flag )
    {
        int16_t lux1 = ( int16_t ) ( ( AMBIENT15_CH0_COFF0 * ch0 - AMBIENT15_CH1_COFF0 * ch1 ) / 
                                   ( ctx->atime_ms * ctx->gain ) );
        int16_t lux2 = ( int16_t ) ( ( AMBIENT15_CH0_COFF1 * ch0 - AMBIENT15_CH1_COFF1 * ch1 ) / 
                                   ( ctx->atime_ms * ctx->gain ) );
        if ( ( lux1 < 0 ) && ( lux2 < 0 ) )
        {
            return AMBIENT15_ERROR;
        }
        *lux = ( lux1 >= lux2 ) ? lux1 : lux2;
        return AMBIENT15_OK;
    }
    
    return AMBIENT15_ERROR;
}

// ------------------------------------------------------------------------- END
