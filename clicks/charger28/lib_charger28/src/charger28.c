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
 * @file charger28.c
 * @brief Charger 28 Click Driver.
 */

#include "charger28.h"

void charger28_cfg_setup ( charger28_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pg = HAL_PIN_NC;
    cfg->cen = HAL_PIN_NC;
    cfg->sts = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER28_DEVICE_ADDRESS;
}

err_t charger28_init ( charger28_t *ctx, charger28_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;
    
    digital_out_init( &ctx->cen, cfg->cen );
    digital_out_high( &ctx->cen );

    digital_in_init( &ctx->pg, cfg->pg );
    digital_in_init( &ctx->sts, cfg->sts );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

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

    return I2C_MASTER_SUCCESS;
}

err_t charger28_default_cfg ( charger28_t *ctx ) 
{
    err_t error_flag = CHARGER28_OK;
    // Disable charging and check communication
    charger28_disable_charging ( ctx );
    Delay_100ms ( );
    if ( CHARGER28_OK != charger28_check_communication ( ctx ) )
    {
        return CHARGER28_ERROR;
    }
    // Reset registers to default values
    error_flag |= charger28_write_reg_byte ( ctx, CHARGER28_REG_CHARGER_CONTROL_2, 
                                             CHARGER28_CHARGER_CONTROL_2_REG_RST_SET );
    Delay_1sec ( );
    // Disable TS pin
    error_flag |= charger28_write_reg_byte ( ctx, CHARGER28_REG_NTC_CONTROL_0, 
                                             CHARGER28_NTC_CONTROL_0_TS_IGNORE_SET |
                                             CHARGER28_NTC_CONTROL_0_CHG_RATE_1C | 
                                             CHARGER28_NTC_CONTROL_0_TS_TH_OTG_HOT_60C | 
                                             CHARGER28_NTC_CONTROL_0_TS_TH_OTG_COLD_MIN_20C | 
                                             CHARGER28_NTC_CONTROL_0_TS_TH1_0C | 
                                             CHARGER28_NTC_CONTROL_0_TS_TH6_60C );
    // Disable watchdog reset
    error_flag |= charger28_write_reg_byte ( ctx, CHARGER28_REG_CHARGER_CONTROL_1, 
                                             CHARGER28_CHARGER_CONTROL_1_EN_AUTO_IBAT_DSCHG_EN | 
                                             CHARGER28_CHARGER_CONTROL_1_FORCE_IBAT_DSCHG_DIS | 
                                             CHARGER28_CHARGER_CONTROL_1_EN_CHG_EN | 
                                             CHARGER28_CHARGER_CONTROL_1_EN_HIZ_DIS | 
                                             CHARGER28_CHARGER_CONTROL_1_FORCE_PMID_DSCHG_DIS | 
                                             CHARGER28_CHARGER_CONTROL_1_WD_RST_CLEAR | 
                                             CHARGER28_CHARGER_CONTROL_1_WATCHDOG_DISABLE );
    // Enable ADC, set resolution, and enable averaging
    error_flag |= charger28_write_reg_byte ( ctx, CHARGER28_REG_ADC_CONTROL, 
                                             CHARGER28_ADC_CONTROL_EN_ADC_EN | 
                                             CHARGER28_ADC_CONTROL_ADC_RATE_CONTINUOUS | 
                                             CHARGER28_ADC_CONTROL_ADC_SAMPLE_11BIT | 
                                             CHARGER28_ADC_CONTROL_ADC_AVG_EN | 
                                             CHARGER28_ADC_CONTROL_ADC_AVG_INIT_NEW_CONV | 
                                             CHARGER28_ADC_CONTROL_DIS_ADCIN_ADC_EN );
    // Enable charging
    charger28_enable_charging ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t charger28_write_reg_bytes ( charger28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t charger28_read_reg_bytes ( charger28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t charger28_write_reg_byte ( charger28_t *ctx, uint8_t reg, uint8_t data_in )
{
    return charger28_write_reg_bytes( ctx, reg, &data_in, 1 );
}

err_t charger28_read_reg_byte ( charger28_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return charger28_read_reg_bytes( ctx, reg, data_out, 1 );
}

err_t charger28_write_reg_word ( charger28_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return charger28_write_reg_bytes( ctx, reg, data_buf, 2 );
}

err_t charger28_read_reg_word ( charger28_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = charger28_read_reg_bytes( ctx, reg, data_buf, 2 );
    if ( CHARGER28_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

err_t charger28_check_communication ( charger28_t *ctx )
{
    uint8_t part_info = 0;
    if ( CHARGER28_OK == charger28_read_reg_byte ( ctx, CHARGER28_REG_PART_INFORMATION, &part_info ) )
    {
        if ( CHARGER28_PART_NUMBER == ( CHARGER28_PART_NUMBER_MASK & part_info ) )
        {
            return CHARGER28_OK;
        }
    }
    return CHARGER28_ERROR;
}

void charger28_enable_charging ( charger28_t *ctx )
{
    digital_out_low ( &ctx->cen );
}

void charger28_disable_charging ( charger28_t *ctx )
{
    digital_out_high ( &ctx->cen );
}

uint8_t charger28_get_pg_pin ( charger28_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

uint8_t charger28_get_sts_pin ( charger28_t *ctx )
{
    return digital_in_read ( &ctx->sts );
}

uint8_t charger28_get_int_pin ( charger28_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t charger28_get_ibus ( charger28_t *ctx, float *ibus )
{
    uint16_t reg_data = 0;
    int16_t ibus_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_IBUS_ADC, &reg_data );
    if ( CHARGER28_OK == error_flag )
    {
        ibus_adc = reg_data;
        *ibus = ( ibus_adc >> 1 ) * CHARGER28_LSB_ADC_IBUS;
    }
    return error_flag;
}

err_t charger28_get_ibat ( charger28_t *ctx, int16_t *ibat )
{
    uint16_t reg_data = 0;
    int16_t ibat_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_IBAT_ADC, &reg_data );
    if ( CHARGER28_OK == error_flag )
    {
        ibat_adc = reg_data;
        *ibat = ( ibat_adc >> 3 ) * CHARGER28_LSB_ADC_IBAT;
    }
    return error_flag;
}

err_t charger28_get_vbus ( charger28_t *ctx, uint16_t *vbus )
{
    uint16_t vbus_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_VBUS_ADC, &vbus_adc );
    if ( CHARGER28_OK == error_flag )
    {
        *vbus = ( vbus_adc >> 2 ) * CHARGER28_LSB_ADC_VBUS;
    }
    return error_flag;
}

err_t charger28_get_vpmid ( charger28_t *ctx, uint16_t *vpmid )
{
    uint16_t vpmid_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_VPMID_ADC, &vpmid_adc );
    if ( CHARGER28_OK == error_flag )
    {
        *vpmid = ( vpmid_adc >> 2 ) * CHARGER28_LSB_ADC_VPMID;
    }
    return error_flag;
}

err_t charger28_get_vbat ( charger28_t *ctx, float *vbat )
{
    uint16_t vbat_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_VBAT_ADC, &vbat_adc );
    if ( CHARGER28_OK == error_flag )
    {
        *vbat = ( vbat_adc >> 1 ) * CHARGER28_LSB_ADC_VBAT;
    }
    return error_flag;
}

err_t charger28_get_vsys ( charger28_t *ctx, float *vsys )
{
    uint16_t vsys_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_VSYS_ADC, &vsys_adc );
    if ( CHARGER28_OK == error_flag )
    {
        *vsys = ( vsys_adc >> 1 ) * CHARGER28_LSB_ADC_VSYS;
    }
    return error_flag;
}

err_t charger28_get_ts ( charger28_t *ctx, float *ts )
{
    uint16_t ts_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_TS_ADC, &ts_adc );
    if ( CHARGER28_OK == error_flag )
    {
        *ts = ts_adc * CHARGER28_LSB_ADC_TS;
    }
    return error_flag;
}

err_t charger28_get_tdie ( charger28_t *ctx, float *tdie )
{
    uint16_t reg_data = 0;
    int16_t tdie_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_TDIE_ADC, &reg_data );
    if ( CHARGER28_OK == error_flag )
    {
        tdie_adc = ( reg_data << 4 );
        *tdie = ( tdie_adc >> 4 ) * CHARGER28_LSB_ADC_TDIE;
    }
    return error_flag;
}

err_t charger28_get_adcin ( charger28_t *ctx, float *adcin )
{
    uint16_t adcin_adc = 0;
    err_t error_flag = charger28_read_reg_word ( ctx, CHARGER28_REG_ADCIN_ADC, &adcin_adc );
    if ( CHARGER28_OK == error_flag )
    {
        *adcin = adcin_adc * CHARGER28_LSB_ADC_ADCIN;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
