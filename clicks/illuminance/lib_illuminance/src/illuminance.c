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
 * @file illuminance.c
 * @brief Illuminance Click Driver.
 */

#include "illuminance.h"

void illuminance_cfg_setup ( illuminance_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ILLUMINANCE_SET_DEV_ADDR_VCC;
}

err_t illuminance_init ( illuminance_t *ctx, illuminance_cfg_t *cfg ) 
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

err_t illuminance_default_cfg ( illuminance_t *ctx ) 
{
    err_t error_flag = ILLUMINANCE_OK;

    if ( ILLUMINANCE_ERROR == illuminance_check_communication ( ctx ) )
    {
        return ILLUMINANCE_ERROR;
    }
    // enable adc, enable power
    error_flag |= illuminance_write_register ( ctx, ILLUMINANCE_REG_CONTROL, ILLUMINANCE_CONTROL_POWER_ON | 
                                                                             ILLUMINANCE_CONTROL_ADC_ENABLE );
    // set default atime - 200ms
    error_flag |= illuminance_set_atime ( ctx, ILLUMINANCE_DEFAULT_ATIME );
    
    // set gain to 16x
    error_flag |= illuminance_set_gain ( ctx, ILLUMINANCE_GAIN_16X );
    
    // enable interrupts
    error_flag |= illuminance_write_register ( ctx, ILLUMINANCE_REG_INTERRUPT, ILLUMINANCE_ENABLE_INTERRUPT );
    
    return error_flag;
}

err_t illuminance_generic_write ( illuminance_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 32 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t illuminance_generic_read ( illuminance_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t illuminance_write_register ( illuminance_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg | ILLUMINANCE_CMD_BIT;
    data_buf[ 1 ] = data_in;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t illuminance_read_register ( illuminance_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    reg |= ILLUMINANCE_CMD_BIT;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

uint8_t illuminance_get_int_pin ( illuminance_t *ctx ) 
{
    return digital_in_read ( &ctx->int_pin );
}

err_t illuminance_check_communication ( illuminance_t *ctx )
{
    uint8_t id_partno = 0;
    uint8_t id2 = 0;
    err_t error_flag = illuminance_read_register ( ctx, ILLUMINANCE_REG_ID, &id_partno );
    error_flag |= illuminance_read_register ( ctx, ILLUMINANCE_REG_ID2, &id2 );
    if ( ( ILLUMINANCE_OK == error_flag ) && 
         ( ILLUMINANCE_ID_PARTNO == ( id_partno & 0xF0 ) ) && 
         ( ILLUMINANCE_ID2 & id2 ) )
    {
        return ILLUMINANCE_OK;
    }
    return ILLUMINANCE_ERROR;
}

err_t illuminance_set_atime ( illuminance_t *ctx, float atime_ms )
{
    uint8_t atime = 0;
    if ( atime_ms >= ILLUMINANCE_ATIME_MAX ) 
    {
        atime = 1;
        ctx->atime_ms = ILLUMINANCE_ATIME_MAX;
    }
    else if ( atime_ms <= ILLUMINANCE_ATIME_MIN )
    {
        atime = 0xFF;
        ctx->atime_ms = ILLUMINANCE_ATIME_MIN;
    }
    else
    {
        atime = 0xFF - ( uint8_t ) ( atime_ms / ILLUMINANCE_ATIME_STEP );
        ctx->atime_ms = atime_ms;
    }
    return illuminance_write_register( ctx, ILLUMINANCE_REG_TIMING, atime );
}

err_t illuminance_set_gain ( illuminance_t *ctx, uint8_t gain )
{
    switch ( gain )
    {
        case ILLUMINANCE_GAIN_1X:
        {
            ctx->gain = 1;
            break;
        }
        case ILLUMINANCE_GAIN_8X:
        {
            ctx->gain = 8;
            break;
        }
        case ILLUMINANCE_GAIN_16X:
        {
            ctx->gain = 16;
            break;
        }
        case ILLUMINANCE_GAIN_111X:
        {
            ctx->gain = 111;
            break;
        }
        default:
        {
            return ILLUMINANCE_ERROR;
        }
    }
    return illuminance_write_register( ctx, ILLUMINANCE_REG_ANALOG, gain );
}

err_t illuminance_read_raw_data ( illuminance_t *ctx, uint16_t *ch_0, uint16_t *ch_1 ) 
{
    uint8_t rx_data = 0;
    err_t error_flag = illuminance_read_register( ctx, ILLUMINANCE_REG_CONTROL, &rx_data );
    if ( ( rx_data & ILLUMINANCE_CONTROL_ADC_VALID ) && 
         ( rx_data & ILLUMINANCE_CONTROL_ADC_INTR ) && 
         ( ILLUMINANCE_OK == error_flag ) )
    {
        error_flag |= illuminance_read_register( ctx, ILLUMINANCE_REG_DATA0_LOW, &rx_data );
        *ch_0 = rx_data;
        error_flag |= illuminance_read_register( ctx, ILLUMINANCE_REG_DATA0_HIGH, &rx_data );
        *ch_0 |= ( ( uint16_t ) rx_data << 8 );
        
        error_flag |= illuminance_read_register( ctx, ILLUMINANCE_REG_DATA1_LOW, &rx_data );
        *ch_1 = rx_data;
        error_flag |= illuminance_read_register( ctx, ILLUMINANCE_REG_DATA1_HIGH, &rx_data );
        *ch_1 |= ( ( uint16_t ) rx_data << 8 );
        
        // clear interrupts
        illuminance_generic_write ( ctx, ILLUMINANCE_CMD_BIT | 
                                         ILLUMINANCE_TRANSACTION_SPEC_FUNC | 
                                         ILLUMINANCE_SPEC_FUNC_INT_CLEAR, 0, 0 );
        return error_flag;
    }
    return ILLUMINANCE_ERROR;
}

// ------------------------------------------------------------------------- END
