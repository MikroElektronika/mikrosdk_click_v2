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

#include "airquality3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void airquality3_cfg_setup ( airquality3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->wke   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AIRQUALITY3_DEVICE_SLAVE_ADDRESS;
}

AIRQUALITY3_RETVAL airquality3_init ( airquality3_t *ctx, airquality3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl      = cfg->scl;
    i2c_cfg.sda      = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AIRQUALITY3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wke, cfg->wke );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return AIRQUALITY3_OK;
}

void airquality3_default_cfg ( airquality3_t *ctx )
{
    airquality3_set_measurement_mode( ctx, AIRQUALITY3_DRIVE_MODE_4 | AIRQUALITY3_INT_DATARDY_1 );
}

void airquality3_generic_write ( airquality3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void airquality3_generic_read ( airquality3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t airquality3_get_starus ( airquality3_t *ctx )
{
    uint8_t rx_data;

    airquality3_generic_read( ctx, AIRQUALITY3_REG_STATUS, &rx_data, 1 );
    Delay_100ms( );

    return rx_data;
}

void airquality3_get_device_info ( airquality3_t *ctx, airguality3_info_t *info )
{
    uint8_t tmp;

    airquality3_generic_read( ctx, AIRQUALITY3_REG_ID, &tmp, 1 ); // 0x81
    info->device_id = tmp;

    airquality3_generic_read( ctx, AIRQUALITY3_REG_HW_VERSION, &tmp, 1 ); // 0x1X
    info->hw_ver = tmp;

    airquality3_generic_read( ctx, AIRQUALITY3_REG_FW_BOOT_VERSION, &tmp, 1 );
    info->fw_boot_ver = tmp;

    airquality3_generic_read( ctx, AIRQUALITY3_REG_FW_APP_VERSION, &tmp, 1 );
    info->fw_app_ver = tmp;
}


void airquality3_software_reset ( airquality3_t *ctx, uint32_t reset )    // 0x11,0xE5,0x72,0x8A
{
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = reset;
    tx_buf[ 1 ] = reset >> 8;
    tx_buf[ 2 ] = reset >> 16;
    tx_buf[ 3 ] = reset >> 24;

    airquality3_generic_write( ctx, AIRQUALITY3_REG_SW_RESET, tx_buf, 4 );
}

uint8_t airquality3_get_co2_and_tvoc ( airquality3_t *ctx, airquality3_air_data_t *air_data )
{
    uint8_t rx_buf[ 8 ];
    uint8_t drdy_f;

    drdy_f = airquality3_get_starus( ctx );

    if ( ( drdy_f & 0x08 ) != 0 )
    {
        airquality3_generic_read( ctx, AIRQUALITY3_REG_ALG_DATA, rx_buf, 8 );

        air_data->co2 = rx_buf[ 0 ];   // CO2
        air_data->co2 <<= 8;
        air_data->co2 |= rx_buf[ 1 ];

        air_data->tvoc = rx_buf[ 2 ];  // TVOC
        air_data->tvoc <<= 8;
        air_data->tvoc |= rx_buf[ 3 ];

        air_data->m_status = rx_buf[ 4 ];  // status reg

        air_data->raw_data = rx_buf[ 6 ];  // RAW DATA
        air_data->raw_data <<= 8;
        air_data->raw_data |= rx_buf[ 7 ];

        return rx_buf[ 5 ];  // error ID
    }
    return 0;
}

void airquality3_get_raw_data ( airquality3_t *ctx, uint16_t *raw_data )
{
    uint8_t rx_buf[ 2 ];

    airquality3_generic_read( ctx, AIRQUALITY3_REG_RAW_DATA, rx_buf, 2 );

    raw_data[ 0 ] &= 0xFC;
    raw_data[ 1 ] = rx_buf[ 0 ] & 0x03;
    raw_data[ 1 ] <<= 8;
    raw_data[ 1 ] |= rx_buf[ 1 ];
}

void airquality3_set_environment_data ( airquality3_t *ctx, uint32_t env_data )    // 0x11,0xE5,0x72,0x8A
{
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = env_data;
    tx_buf[ 1 ] = env_data >> 8;
    tx_buf[ 2 ] = env_data >> 16;
    tx_buf[ 3 ] = env_data >> 24;

    airquality3_generic_write( ctx, AIRQUALITY3_REG_ENV_DATA, tx_buf, 4 );
}

void airquality3_get_ntc_data ( airquality3_t *ctx, uint8_t *data_buf )
{
    airquality3_generic_read( ctx, AIRQUALITY3_REG_NTC, data_buf, 4 );
}

void airquality3_set_measurement_mode ( airquality3_t *ctx, uint8_t mode )
{
    airquality3_generic_write( ctx, AIRQUALITY3_REG_MEAS_MODE, &mode, 1 );
}

void airquality3_set_baseline ( airquality3_t *ctx, uint16_t baseline )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = baseline >> 8;
    tx_buf[ 1 ] = baseline;

    airquality3_generic_write( ctx, AIRQUALITY3_REG_BASELINE, tx_buf, 2 );
}

void airquality3_app_function ( airquality3_t *ctx, uint8_t app_task )
{
    airquality3_generic_write( ctx, app_task, 0, 0 );
}

void airquality3_set_power( airquality3_t *ctx, uint16_t pwr_state )
{
   digital_out_write( &ctx->wke, pwr_state );
}

void airquality3_hardware_reset( airquality3_t *ctx )
{
   digital_out_low( &ctx->rst );
   Delay_1sec( );
   Delay_1sec( );
   digital_out_high( &ctx->rst );
   Delay_100ms( );
   Delay_100ms( );
}

uint8_t airquality3_get_interrupt_state( airquality3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

