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
 * @file ambient17.c
 * @brief Ambient 17 Click Driver.
 */

#include "ambient17.h"

void ambient17_cfg_setup ( ambient17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT17_DEVICE_ADDRESS;
}

err_t ambient17_init ( ambient17_t *ctx, ambient17_cfg_t *cfg ) 
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

err_t ambient17_default_cfg ( ambient17_t *ctx ) 
{
    err_t error_flag = AMBIENT17_OK;
    if ( AMBIENT17_ERROR == ambient17_check_communication ( ctx ) )
    {
        return AMBIENT17_ERROR;
    }
    error_flag |= ambient17_write_register ( ctx, AMBIENT17_REG_ENABLE, AMBIENT17_ENABLE_ALS_INT | 
                                                                        AMBIENT17_ENABLE_ALS | 
                                                                        AMBIENT17_ENABLE_OSC );
    error_flag |= ambient17_set_atime ( ctx, AMBIENT17_DEFAULT_ATIME );
    error_flag |= ambient17_set_again ( ctx, AMBIENT17_AGAIN_8X );
    Delay_100ms ( );
    return error_flag;
}

err_t ambient17_generic_write ( ambient17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 17 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ cnt + 1 ] = tx_buf[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t ambient17_generic_read ( ambient17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t ambient17_write_register ( ambient17_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return ambient17_generic_write( ctx, reg | AMBIENT17_CMD_BIT, &data_in, 1 );
}

err_t ambient17_read_register ( ambient17_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return ambient17_generic_read( ctx, reg | AMBIENT17_CMD_BIT, data_out, 1 );
}

err_t ambient17_check_communication ( ambient17_t *ctx )
{
    uint8_t dev_id = 0;
    if ( AMBIENT17_OK == ambient17_read_register ( ctx, AMBIENT17_REG_ID, &dev_id ) ) 
    {
        if ( AMBIENT17_DEVICE_ID == dev_id )
        {
            return AMBIENT17_OK;
        }
    }
    return AMBIENT17_ERROR;
}

uint8_t ambient17_get_int_pin ( ambient17_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t ambient17_clear_interrupts ( ambient17_t *ctx )
{
    return ambient17_generic_write ( ctx, AMBIENT17_CMD_BIT | 
                                          AMBIENT17_TYPE_SPEC_FUNC | 
                                          AMBIENT17_SPEC_FUNC_INT_CLEAR, 0, 0 );
}

err_t ambient17_set_atime ( ambient17_t *ctx, float atime_ms )
{
    uint8_t atime = 0;
    if ( atime_ms >= AMBIENT17_ATIME_MAX ) 
    {
        atime = 1;
        ctx->atime_ms = AMBIENT17_ATIME_MAX;
    }
    else if ( atime_ms <= AMBIENT17_ATIME_MIN )
    {
        atime = 0xFF;
        ctx->atime_ms = AMBIENT17_ATIME_MIN;
    }
    else
    {
        atime = 0xFF - ( uint8_t ) ( atime_ms / AMBIENT17_ATIME_STEP );
        ctx->atime_ms = atime_ms;
    }
    ctx->cpl = ( ctx->atime_ms * ctx->again ) / ( AMBIENT17_GA_VALUE * AMBIENT17_GA_MULTIPLIER );
    return ambient17_write_register( ctx, AMBIENT17_REG_ATIME, atime );
}

err_t ambient17_set_wtime ( ambient17_t *ctx, float wtime_ms )
{
    uint8_t wtime = 0;
    if ( wtime_ms >= AMBIENT17_WTIME_MAX ) 
    {
        wtime = 1;
    }
    else if ( wtime_ms <= AMBIENT17_WTIME_MIN )
    {
        wtime = 0xFF;
    }
    else
    {
        wtime = 0xFF - ( uint8_t ) ( wtime_ms / AMBIENT17_WTIME_STEP );
    }
    return ambient17_write_register( ctx, AMBIENT17_REG_WTIME, wtime );
}

err_t ambient17_set_again ( ambient17_t *ctx, uint8_t again )
{
    switch ( again )
    {
        case AMBIENT17_AGAIN_1X:
        {
            ctx->again = 1;
            break;
        }
        case AMBIENT17_AGAIN_8X:
        {
            ctx->again = 8;
            break;
        }
        case AMBIENT17_AGAIN_16X:
        {
            ctx->again = 16;
            break;
        }
        case AMBIENT17_AGAIN_120X:
        {
            ctx->again = 120;
            break;
        }
        default:
        {
            return AMBIENT17_ERROR;
        }
    }
    ctx->cpl = ( ctx->atime_ms * ctx->again ) / ( AMBIENT17_GA_VALUE * AMBIENT17_GA_MULTIPLIER );
    return ambient17_write_register( ctx, AMBIENT17_REG_CONTROL, again );
}

err_t ambient17_read_raw_data ( ambient17_t *ctx, uint16_t *ch_0, uint16_t *ch_1 )
{
    uint8_t rx_data = 0;
    err_t error_flag = ambient17_read_register( ctx, AMBIENT17_REG_STATUS, &rx_data );
    if ( ( rx_data & AMBIENT17_STATUS_AINT ) && 
         ( rx_data & AMBIENT17_STATUS_AVALID ) && 
         ( AMBIENT17_OK == error_flag ) )
    {
        error_flag |= ambient17_read_register( ctx, AMBIENT17_REG_C0DATA, &rx_data );
        *ch_0 = rx_data;
        error_flag |= ambient17_read_register( ctx, AMBIENT17_REG_C0DATAH, &rx_data );
        *ch_0 |= ( ( uint16_t ) rx_data << 8 );
        
        error_flag |= ambient17_read_register( ctx, AMBIENT17_REG_C1DATA, &rx_data );
        *ch_1 = rx_data;
        error_flag |= ambient17_read_register( ctx, AMBIENT17_REG_C1DATAH, &rx_data );
        *ch_1 |= ( ( uint16_t ) rx_data << 8 );
        
        error_flag |= ambient17_clear_interrupts ( ctx );
        return error_flag;
    }
    return AMBIENT17_ERROR;
}

err_t ambient17_measure_light_level ( ambient17_t *ctx, uint16_t *lux )
{
    uint16_t ch0, ch1;
    err_t error_flag = ambient17_read_raw_data ( ctx, &ch0, &ch1 );
    
    if ( AMBIENT17_OK == error_flag )
    {
        int16_t lux1 = ( int16_t ) ( ( AMBIENT17_CH0_COFF0 * ch0 - AMBIENT17_CH1_COFF0 * ch1 ) / ctx->cpl );
        int16_t lux2 = ( int16_t ) ( ( AMBIENT17_CH0_COFF1 * ch0 - AMBIENT17_CH1_COFF1 * ch1 ) / ctx->cpl );
        if ( ( lux1 < 0 ) && ( lux2 < 0 ) )
        {
            return AMBIENT17_ERROR;
        }
        *lux = ( lux1 >= lux2 ) ? lux1 : lux2;
        return AMBIENT17_OK;
    }
    
    return AMBIENT17_ERROR;
}

// ------------------------------------------------------------------------- END
