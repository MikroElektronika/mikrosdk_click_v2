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

#include "current3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void current3_cfg_setup ( current3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->trm = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CURRENT3_I2C_SLAVE_ADDR;
}

CURRENT3_RETVAL current3_init ( current3_t *ctx, current3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CURRENT3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->trm, cfg->trm );
    digital_in_init( &ctx->alr, cfg->alr );

    return CURRENT3_OK;
}

void current3_default_cfg ( current3_t *ctx, current3_sense_cfg_data_t sense_cfg_data )
{
    sense_cfg_data.cs_queue     = CURRENT3_NUM_OF_CONS_OUT_LIMIT_MEASUR_1;
    sense_cfg_data.cs_samp_avg  = CURRENT3_CURRENT_SENSE_AVG_1X;
    sense_cfg_data.cs_samp_time = CURRENT3_CS_SAMP_TIME_82ms;
    sense_cfg_data.cs_rng       = CURRENT3_SENSOR_RANGE_10_mV;

    current3_set_sense_sampling_config( ctx, sense_cfg_data );
    Delay_100ms( );
}

void current3_generic_write ( current3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void current3_generic_read ( current3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

float current3_get_temperature ( current3_t *ctx, uint8_t temp_sel )
{
    uint8_t buf[ 2 ];
    int16_t tmp;
    float temperature;

    if ( temp_sel == CURRENT3_TEMP_INTERNAL_DIODE )
    {
        current3_generic_read( ctx, CURRENT3_REG_INT_DIODE_HIGH_BYTE, buf, 2 );
    }
    else
    {
        current3_generic_read( ctx, CURRENT3_REG_EXT_DIODE_1_HIGH_BYTE, buf, 2 );
    }

    buf[ 1 ] >>= 5;

    tmp = ( int16_t ) buf[ 0 ];

    temperature = ( float ) tmp;

    if ( tmp < 0 )
    {
        temperature -= ( ( float ) buf[ 1 ] ) * CURRENT3_TEMPERATURE_CALC_FACT;
    }
    else
    {
        temperature += ( ( float ) buf[ 1 ] ) * CURRENT3_TEMPERATURE_CALC_FACT;
    }

    return temperature;
}

void current3_get_status ( current3_t *ctx, current3_status_data_t *status_cfg )
{
    uint8_t status_data;

    current3_generic_read( ctx, CURRENT3_REG_STATUS, &status_data, 1 );

    status_cfg->busy_data  = ( status_data >> 7 ) & 0x01;
    status_cfg->peak_data  = ( status_data >> 6 ) & 0x01;
    status_cfg->high_data  = ( status_data >> 4 ) & 0x01;
    status_cfg->low_data   = ( status_data >> 3 ) & 0x01;
    status_cfg->fault_data = ( status_data >> 2 ) & 0x01;
    status_cfg->crit_data  = ( status_data >> 1 ) & 0x01;
}

void current3_set_configuration ( current3_t *ctx,  current3_cfg_data_t cfg_data )
{
    uint8_t d_cfg;

    d_cfg  = cfg_data.mask_all   << 7;
    d_cfg |= cfg_data.tmeas_stop << 6;
    d_cfg |= cfg_data.alert_comp << 5;
    d_cfg |= cfg_data.dis_rec1   << 4;
    d_cfg |= cfg_data.imeas_stop << 2;
    d_cfg |= cfg_data.davg_dis   << 1;

    current3_generic_write( ctx, CURRENT3_REG_CFG, &d_cfg, 1 );
}

void current3_get_configuration ( current3_t *ctx,  current3_cfg_data_t *cfg_data )
{
    uint8_t d_cfg;

    current3_generic_read( ctx, CURRENT3_REG_CFG, &d_cfg, 1 );

    cfg_data->mask_all   = ( d_cfg >> 7 ) & 0x01;
    cfg_data->tmeas_stop = ( d_cfg >> 6 ) & 0x01;
    cfg_data->alert_comp = ( d_cfg >> 5 ) & 0x01;
    cfg_data->dis_rec1   = ( d_cfg >> 4 ) & 0x01;
    cfg_data->imeas_stop = ( d_cfg >> 2 ) & 0x01;
    cfg_data->davg_dis   = ( d_cfg >> 1 ) & 0x01;
}

void current3_set_voltage_sampling_config ( current3_t *ctx, current3_voltage_cfg_data_t vtg_cfg_data )
{
    uint8_t vtg_cfg;
    
    vtg_cfg  = vtg_cfg_data.pk_alert_therm << 7;
    vtg_cfg |= vtg_cfg_data.v_queue        << 2;
    vtg_cfg |= vtg_cfg_data.v_avg;

    current3_generic_write( ctx, CURRENT3_REG_VOLTAGE_SAMPLING_CFG, &vtg_cfg, 1 );
}

void current3_get_voltage_sampling_config ( current3_t *ctx, current3_voltage_cfg_data_t *vtg_cfg_data )
{
    uint8_t vtg_cfg;

    current3_generic_read( ctx, CURRENT3_REG_VOLTAGE_SAMPLING_CFG, &vtg_cfg, 1 );

    vtg_cfg_data->pk_alert_therm = ( vtg_cfg >> 7 ) & 0x01;
    vtg_cfg_data->v_queue        = ( vtg_cfg >> 2 ) & 0x03;
    vtg_cfg_data->v_avg          =   vtg_cfg        & 0x03;
}

void current3_set_sense_sampling_config ( current3_t *ctx, current3_sense_cfg_data_t sense_cfg_data )
{
    uint8_t sen_cfg;
    
    sen_cfg  = sense_cfg_data.cs_queue     << 6;
    sen_cfg |= sense_cfg_data.cs_samp_avg  << 4;
    sen_cfg |= sense_cfg_data.cs_samp_time << 2;
    sen_cfg |= sense_cfg_data.cs_rng;
    
    current3_generic_write( ctx, CURRENT3_REG_CURRENT_SENSE_SAMPLING_CFG, &sen_cfg, 1 );
}

void current3_get_sense_sampling_config ( current3_t *ctx, current3_sense_cfg_data_t *sense_cfg_data )
{
    uint8_t sen_cfg;
    
    current3_generic_read( ctx, CURRENT3_REG_CURRENT_SENSE_SAMPLING_CFG, &sen_cfg, 1 );
    
    sense_cfg_data->cs_queue     = ( sen_cfg >> 6 ) & 0x03;
    sense_cfg_data->cs_samp_avg  = ( sen_cfg >> 4 ) & 0x03;
    sense_cfg_data->cs_samp_time = ( sen_cfg >> 2 ) & 0x03;
    sense_cfg_data->cs_rng       =   sen_cfg        & 0x03;
}

int16_t current3_get_sense_voltage ( current3_t *ctx )
{
    uint8_t buf[ 2 ];
    uint16_t tmp;
    int16_t sense_voltage;

    current3_generic_read( ctx, CURRENT3_REG_SENSE_VOLTAGE_HIGH_BYTE, buf, 2 );

    tmp = buf[ 0 ];
    tmp <<= 8;
    tmp |= buf[ 1 ];

    sense_voltage = ( int16_t ) tmp;
    sense_voltage >>= 4;

    return sense_voltage;
}

float current3_get_source_voltage ( current3_t *ctx )
{
    uint8_t buf[ 2 ];
    uint16_t tmp;
    float source_voltage;

    current3_generic_read( ctx, CURRENT3_REG_SOURCE_VOLTAGE_HIGH_BYTE, buf, 2 );

    tmp = buf[ 0 ];
    tmp <<= 8;
    tmp |= buf[ 1 ];
    tmp >>= 5;

    source_voltage = ( float ) tmp;
    source_voltage *= CURRENT3_SOURCE_VOLTAGE_CALC_FACT;

    return source_voltage;
}

float current3_get_current ( current3_t *ctx )
{
    uint8_t buf;
    int16_t sense_scale;
    float fsc;
    float current;

    current3_generic_read( ctx, CURRENT3_REG_CURRENT_SENSE_SAMPLING_CFG, &buf, 1 );
    
    buf &= CURRENT3_SENSOR_RANGE_BIT_MASK;
    
    switch ( buf )
    {
        case CURRENT3_SENSOR_RANGE_10_mV:
        {
            fsc = CURRENT3_SENSOR_RANGE_VALUE_10_mV;
            break;
        }
        case CURRENT3_SENSOR_RANGE_20_mV:
        {
            fsc = CURRENT3_SENSOR_RANGE_VALUE_20_mV;
            break;
        }
        case CURRENT3_SENSOR_RANGE_40_mV:
        {
            fsc = CURRENT3_SENSOR_RANGE_VALUE_40_mV;
            break;
        }
        case CURRENT3_SENSOR_RANGE_80_mV:
        {
            fsc = CURRENT3_SENSOR_RANGE_VALUE_80_mV;
            break;
        }
    }
    
    fsc /= CURRENT3_DEFAULT_RSENSE;
    
    sense_scale = current3_get_sense_voltage( ctx );

    current = ( float ) sense_scale;
    current /= ( float ) CURRENT3_FULL_SCALE_SENSE_VOLTAGE;
    current *= fsc;
    current *= ( float ) CURRENT3_CON_FCT_mV_TO_V;

    return current;
}

uint8_t current3_check_therm ( current3_t *ctx )
{
    return digital_in_read( &ctx->trm );
}

uint8_t current3_check_alert ( current3_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

// ------------------------------------------------------------------------- END

