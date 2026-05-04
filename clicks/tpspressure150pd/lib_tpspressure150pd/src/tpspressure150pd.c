/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file tpspressure150pd.c
 * @brief TPS Pressure 150PD Click Driver.
 */

#include "tpspressure150pd.h"

void tpspressure150pd_cfg_setup ( tpspressure150pd_cfg_t *cfg ) 
{
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->sdo = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TPSPRESSURE150PD_DEVICE_ADDRESS;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->vref        = TPSPRESSURE150PD_VREF_3V3;
}

err_t tpspressure150pd_init ( tpspressure150pd_t *ctx, tpspressure150pd_cfg_t *cfg ) 
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

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->sdo, cfg->sdo );
    Delay_100ms ( );

    return TPSPRESSURE150PD_OK;
}

err_t tpspressure150pd_default_cfg ( tpspressure150pd_t *ctx ) 
{
    err_t error_flag = TPSPRESSURE150PD_OK;
    tpspressure150pd_enable_device ( ctx );
    Delay_100ms ( );
    if ( TPSPRESSURE150PD_OK != tpspressure150pd_check_com ( ctx ) )
    {
        return TPSPRESSURE150PD_ERROR;
    }
    return error_flag;
}

err_t tpspressure150pd_wr_cmd ( tpspressure150pd_t *ctx, uint8_t cmd )
{
    err_t error_flag = TPSPRESSURE150PD_OK;
    switch ( cmd )
    {
        case TPSPRESSURE150PD_CMD_RESET:
        case TPSPRESSURE150PD_CMD_REFRESH:
        case TPSPRESSURE150PD_CMD_START_AUTOMATIC_MODE:
        case TPSPRESSURE150PD_CMD_STOP_AUTOMATIC_MODE:
        case TPSPRESSURE150PD_CMD_CONVERSION:
        {
            break;
        }
        default:
        {
            error_flag = TPSPRESSURE150PD_ERROR;
            break;
        }
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = tpspressure150pd_wait_ready ( ctx );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = i2c_master_write( &ctx->i2c, &cmd, 1 );
    }
    return error_flag;
}

err_t tpspressure150pd_wr_cmd_data ( tpspressure150pd_t *ctx, uint8_t cmd, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t error_flag = TPSPRESSURE150PD_OK;
    switch ( cmd )
    {
        case TPSPRESSURE150PD_CMD_WRITE_OPERATING_MODE:
        case TPSPRESSURE150PD_CMD_WRITE_CONFIG_PRES_4:
        case TPSPRESSURE150PD_CMD_WRITE_CONFIG_TEMP1_4:
        case TPSPRESSURE150PD_CMD_WRITE_INTERRUPT_MASK:
        case TPSPRESSURE150PD_CMD_WRITE_INTERRUPT_REG:
        case TPSPRESSURE150PD_CMD_WRITE_LIMITS:
        {
            break;
        }
        default:
        {
            error_flag = TPSPRESSURE150PD_ERROR;
            break;
        }
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = tpspressure150pd_wait_ready ( ctx );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        data_buf[ 0 ] = cmd;
        data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
        error_flag = i2c_master_write( &ctx->i2c, data_buf, 3 );
    }
    return error_flag;
}

err_t tpspressure150pd_rd_cmd_data ( tpspressure150pd_t *ctx, uint8_t cmd, uint16_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 8 ] = { 0 };
    err_t error_flag = TPSPRESSURE150PD_OK;
    switch ( cmd )
    {
        case TPSPRESSURE150PD_CMD_READ_SENSOR_ID:
        case TPSPRESSURE150PD_CMD_READ_OPERATING_MODE:
        case TPSPRESSURE150PD_CMD_READ_CONFIG_PRES_4:
        case TPSPRESSURE150PD_CMD_READ_CONFIG_TEMP1_4:
        case TPSPRESSURE150PD_CMD_READ_ADC_P:
        case TPSPRESSURE150PD_CMD_READ_ADC_T1:
        case TPSPRESSURE150PD_CMD_READ_ADC_T1_P:
        case TPSPRESSURE150PD_CMD_READ_INTERRUPT_MASK:
        case TPSPRESSURE150PD_CMD_READ_INTERRUPT_REG:
        case TPSPRESSURE150PD_CMD_READ_LIMITS:
        {
            break;
        }
        default:
        {
            error_flag = TPSPRESSURE150PD_ERROR;
            break;
        }
    }
    if ( ( len < 1 ) || ( len > 4 ) || ( NULL == data_out ) )
    {
        error_flag = TPSPRESSURE150PD_ERROR;
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = tpspressure150pd_wait_ready ( ctx );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = i2c_master_write_then_read ( &ctx->i2c, &cmd, 1, data_buf, len * 2 );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        for ( uint8_t cnt = 0; cnt < len; cnt++ )
        {
            data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 2 ] << 8 ) | data_buf[ cnt * 2 + 1 ];
        }
    }
    return error_flag;
}

err_t tpspressure150pd_wr_cmd_a ( tpspressure150pd_t *ctx, uint8_t cmd, uint8_t addr )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = TPSPRESSURE150PD_OK;
    if ( ( TPSPRESSURE150PD_CMD_ERASE_NVM != cmd ) || 
         ( addr > TPSPRESSURE150PD_REG_NVM_END ) )
    {
        error_flag = TPSPRESSURE150PD_ERROR;
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = tpspressure150pd_wait_ready ( ctx );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        data_buf[ 0 ] = cmd;
        data_buf[ 1 ] = addr;
        error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    }
    return error_flag;
}

err_t tpspressure150pd_wr_cmd_a_data ( tpspressure150pd_t *ctx, uint8_t cmd, uint8_t addr, uint16_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = TPSPRESSURE150PD_OK;
    if ( ( ( TPSPRESSURE150PD_CMD_WRITE_NVM != cmd ) || 
           ( addr > TPSPRESSURE150PD_REG_NVM_END ) ) && 
         ( ( TPSPRESSURE150PD_CMD_WRITE_REG != cmd ) || 
           ( addr < TPSPRESSURE150PD_REG_PRES_4 ) || 
           ( addr > TPSPRESSURE150PD_REG_CRC_USER_MEM ) ) )
    {
        error_flag = TPSPRESSURE150PD_ERROR;
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = tpspressure150pd_wait_ready ( ctx );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        data_buf[ 0 ] = cmd;
        data_buf[ 1 ] = addr;
        data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
        error_flag = i2c_master_write( &ctx->i2c, data_buf, 4 );
    }
    return error_flag;
}

err_t tpspressure150pd_rd_cmd_a_data ( tpspressure150pd_t *ctx, uint8_t cmd, uint8_t addr, uint16_t *data_out )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = TPSPRESSURE150PD_OK;
    if ( ( ( TPSPRESSURE150PD_CMD_READ_NVM != cmd ) || 
           ( addr > TPSPRESSURE150PD_REG_NVM_END ) ) && 
         ( ( TPSPRESSURE150PD_CMD_READ_REG != cmd ) || 
           ( addr < TPSPRESSURE150PD_REG_PRES_4 ) || 
           ( addr > TPSPRESSURE150PD_REG_CRC_USER_MEM ) ) )
    {
        error_flag = TPSPRESSURE150PD_ERROR;
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = tpspressure150pd_wait_ready ( ctx );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        data_buf[ 0 ] = cmd;
        data_buf[ 1 ] = addr;
        error_flag = i2c_master_write_then_read ( &ctx->i2c, &data_buf[ 0 ], 2, &data_buf[ 2 ], 2 );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    }
    return error_flag;
}

err_t tpspressure150pd_read_raw_adc ( tpspressure150pd_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t tpspressure150pd_read_voltage ( tpspressure150pd_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t tpspressure150pd_set_vref ( tpspressure150pd_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void tpspressure150pd_enable_device ( tpspressure150pd_t *ctx )
{
    digital_out_high ( ctx );
}

void tpspressure150pd_disable_device ( tpspressure150pd_t *ctx )
{
    digital_out_low ( ctx );
}

uint8_t tpspressure150pd_get_sdo_pin ( tpspressure150pd_t *ctx )
{
    return !!digital_in_read ( &ctx->sdo );
}

err_t tpspressure150pd_wait_ready ( tpspressure150pd_t *ctx )
{
    uint32_t timeout_cnt = 0;
    while ( !tpspressure150pd_get_sdo_pin ( ctx ) )
    {
        if ( timeout_cnt++ > TPSPRESSURE150PD_TIMEOUT_MS )
        {
            return TPSPRESSURE150PD_ERROR;
        }
        Delay_1ms ( );
    }
    return TPSPRESSURE150PD_OK;
}

err_t tpspressure150pd_read_sensor_id ( tpspressure150pd_t *ctx, uint32_t *part_num, uint16_t *serial_num, uint16_t *wafer_num )
{
    uint16_t sensor_id[ 4 ] = { 0 };
    err_t error_flag = TPSPRESSURE150PD_OK;
    error_flag = tpspressure150pd_rd_cmd_data ( ctx, TPSPRESSURE150PD_CMD_READ_SENSOR_ID, sensor_id, 4 );
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        if ( NULL != part_num )
        {
            *part_num = ( ( uint32_t ) sensor_id[ 0 ] << 16 ) | sensor_id[ 1 ];
        }
        if ( NULL != serial_num )
        {
            *serial_num = sensor_id[ 2 ];
        }
        if ( NULL != wafer_num )
        {
            *wafer_num = sensor_id[ 3 ];
        }
    }
    return error_flag;
}

err_t tpspressure150pd_check_com ( tpspressure150pd_t *ctx )
{
    uint32_t part_num = 0;
    if ( TPSPRESSURE150PD_OK == tpspressure150pd_read_sensor_id ( ctx, &part_num, NULL, NULL ) )
    {
        if ( TPSPRESSURE150PD_PART_NUMBER == part_num )
        {
            return TPSPRESSURE150PD_OK;
        }
    }
    return TPSPRESSURE150PD_ERROR;
}

err_t tpspressure150pd_read_raw_data ( tpspressure150pd_t *ctx, uint32_t *press, uint32_t *temp )
{
    err_t error_flag = TPSPRESSURE150PD_OK;
    uint16_t adc_data[ 3 ] = { 0 };
    error_flag = tpspressure150pd_wr_cmd ( ctx, TPSPRESSURE150PD_CMD_CONVERSION );
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        error_flag = tpspressure150pd_rd_cmd_data ( ctx, TPSPRESSURE150PD_CMD_READ_ADC_T1_P, adc_data, 3 );
    }
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        if ( NULL != press )
        {
            *temp = ( ( ( uint32_t ) adc_data[ 0 ] << 8 ) | ( adc_data[ 1 ] >> 8 ) ) & TPSPRESSURE150PD_DATA_RESOLUTION;
        }
        if ( NULL != temp )
        {
            *press = ( ( ( uint32_t ) ( adc_data[ 1 ] & 0x00FF ) << 16 ) | adc_data[ 2 ] ) & TPSPRESSURE150PD_DATA_RESOLUTION;
        }
    }
    return error_flag;
}

err_t tpspressure150pd_read_data ( tpspressure150pd_t *ctx, float *press, float *temp )
{
    err_t error_flag = TPSPRESSURE150PD_OK;
    uint32_t press_raw = 0;
    uint32_t temp_raw = 0;
    error_flag = tpspressure150pd_read_raw_data ( ctx, &press_raw, &temp_raw );
    if ( TPSPRESSURE150PD_OK == error_flag )
    {
        if ( NULL != press )
        {
            *press = TPSPRESSURE150PD_PRESSURE_MIN + ( ( press_raw - TPSPRESSURE150PD_DATA_MIN ) / 
                                                       ( TPSPRESSURE150PD_DATA_MAX - TPSPRESSURE150PD_DATA_MIN ) ) * 
                                                     ( TPSPRESSURE150PD_PRESSURE_MAX - TPSPRESSURE150PD_PRESSURE_MIN );
            if ( *press > TPSPRESSURE150PD_PRESSURE_MAX )
            {
                *press = TPSPRESSURE150PD_PRESSURE_MAX;
            }
            else if ( *press < TPSPRESSURE150PD_PRESSURE_MIN )
            {
                *press = TPSPRESSURE150PD_PRESSURE_MIN;
            }
        }
        if ( NULL != temp )
        {
            *temp = TPSPRESSURE150PD_TEMPERATURE_MIN + ( ( temp_raw - TPSPRESSURE150PD_DATA_MIN ) / 
                                                         ( TPSPRESSURE150PD_DATA_MAX - TPSPRESSURE150PD_DATA_MIN ) ) * 
                                                       ( TPSPRESSURE150PD_TEMPERATURE_MAX - TPSPRESSURE150PD_TEMPERATURE_MIN );
            if ( *temp > TPSPRESSURE150PD_TEMPERATURE_MAX )
            {
                *temp = TPSPRESSURE150PD_TEMPERATURE_MAX;
            }
            else if ( *temp < TPSPRESSURE150PD_TEMPERATURE_MIN )
            {
                *temp = TPSPRESSURE150PD_TEMPERATURE_MIN;
            }
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
