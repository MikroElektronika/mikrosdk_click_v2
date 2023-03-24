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

#include "airquality2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void airquality2_cfg_setup ( airquality2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AIRQUALITY2_I2C_ADDRESS;
}

AIRQUALITY2_RETVAL airquality2_init ( airquality2_t *ctx, airquality2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    
    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl      = cfg->scl;
    i2c_cfg.sda      = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AIRQUALITY2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return AIRQUALITY2_OK;
}

void airquality2_generic_read ( airquality2_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_read( &ctx->i2c, data_buf, len );
}

uint8_t airquality2_get_all_data ( airquality2_t *ctx, uint16_t *value_co2, uint16_t *value_tvoc, int32_t *resistance )
{
    uint8_t buffer[ 9 ];
    uint16_t resulet_co2;
    uint16_t resulet_tvoc;
    int32_t resulet_resistance;
    uint8_t status;

    airquality2_generic_read( ctx, buffer, AIRQUALITY2_READ_ALL );

    resulet_co2 = buffer[ AIRQUALITY2_CO2_PREDICTION_MSB_OFFSET ];
    resulet_co2 <<= 8;
    resulet_co2 |= buffer[ AIRQUALITY2_CO2_PREDICTION_LSB_OFFSET ];
    
    status = buffer[ AIRQUALITY2_STATUS_OFFSET ];

    resulet_resistance = buffer[ AIRQUALITY2_RESISTANCE_MSB_OFFSET ];
    resulet_resistance <<= 8;
    resulet_resistance |= buffer[ AIRQUALITY2_RESISTANCE_MID_OFFSET ];
    resulet_resistance <<= 8;
    resulet_resistance |= buffer[ AIRQUALITY2_RESISTANCE_LSB_OFFSET ];
    
    resulet_tvoc = buffer[ AIRQUALITY2_TVOC_PREDICTION_MSB_OFFSET ];
    resulet_tvoc <<= 8;
    resulet_tvoc |=  buffer[ AIRQUALITY2_TVOC_PREDICTION_LSB_OFFSET ];

    *value_co2 = resulet_co2;
    *value_tvoc = resulet_tvoc;
    *resistance = resulet_resistance;

    return status;
}

// ------------------------------------------------------------------------- END

