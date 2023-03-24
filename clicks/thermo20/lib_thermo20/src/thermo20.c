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
 * @file thermo20.c
 * @brief Thermo 20 Click Driver.
 */

#include "thermo20.h"

#define THERMO20_CALC_16_BIT_DIVIDER    65535.0
#define THERMO20_CALC_TEMP_MULTI_FACT   165.000
#define THERMO20_CALC_TEMP_SUB_FACT     40.0000

void thermo20_cfg_setup ( thermo20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO20_SET_DEV_ADDR;
}

err_t thermo20_init ( thermo20_t *ctx, thermo20_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_timeout( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t thermo20_default_cfg ( thermo20_t *ctx ) 
{
    thermo20_soft_reset( ctx );
    Delay_100ms( );
    return THERMO20_OK;
}

err_t thermo20_generic_write ( thermo20_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t thermo20_generic_read ( thermo20_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t thermo20_set_cmd ( thermo20_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 1 ];
    uint8_t status;
    
    status = THERMO20_OK;
    
    if ( ( cmd == THERMO20_CMD_RESET ) ||
         ( cmd == THERMO20_CMD_READ_SERIAL_NUMBER ) ||
         ( cmd == THERMO20_CMD_CONVERSION ) ||
         ( cmd == THERMO20_CMD_READ_ADC ) )
    {
        tx_buf[ 0 ] = cmd;
        
        i2c_master_write( &ctx->i2c, tx_buf, 1 );
    }
    else
    {
        status = THERMO20_ERROR;
    }
    
    return status;
}

void thermo20_soft_reset ( thermo20_t *ctx )
{
    thermo20_set_cmd( ctx, THERMO20_CMD_RESET );
}

void thermo20_start_conversion ( thermo20_t *ctx )
{
    thermo20_set_cmd( ctx, THERMO20_CMD_CONVERSION );
    Delay_10ms();
    Delay_10ms();
}

uint16_t thermo20_read_adc ( thermo20_t *ctx )
{
    uint8_t rx_buf[ 3 ];
    uint16_t res_adc;
    
    thermo20_generic_read( ctx, THERMO20_CMD_READ_ADC, rx_buf, 3 );
    
    res_adc = rx_buf[ 0 ];
    res_adc <<= 8;
    res_adc |= rx_buf[ 1 ];
    
    return res_adc;
}

float thermo20_get_temperature ( thermo20_t *ctx )
{
    uint16_t tmp;
    float temperature;

    tmp = thermo20_read_adc( ctx );

    temperature = ( float ) tmp;
    temperature /= THERMO20_CALC_16_BIT_DIVIDER;
    temperature *= THERMO20_CALC_TEMP_MULTI_FACT;
    temperature -= THERMO20_CALC_TEMP_SUB_FACT;

    return temperature;
}

uint32_t thermo20_get_serial_number ( thermo20_t *ctx )
{
    uint8_t rx_buf[ 4 ];
    uint32_t ser_numb;
    
    thermo20_generic_read( ctx, THERMO20_CMD_READ_SERIAL_NUMBER, rx_buf, 4 );

    ser_numb = rx_buf[ 0 ];
    ser_numb <<= 8;
    ser_numb |= rx_buf[ 1 ];
    ser_numb <<= 8;
    ser_numb |= rx_buf[ 2 ];

    return ser_numb;
}

// ------------------------------------------------------------------------- END
