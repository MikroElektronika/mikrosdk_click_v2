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
 * @file vcpmonitor5.c
 * @brief VCP Monitor 5 Click Driver.
 */

#include "vcpmonitor5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void vcpmonitor5_cfg_setup ( vcpmonitor5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VCPMONITOR5_DEVICE_ADDRESS_GND;
}

err_t vcpmonitor5_init ( vcpmonitor5_t *ctx, vcpmonitor5_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alr, cfg->alr );

    return I2C_MASTER_SUCCESS;
}

err_t vcpmonitor5_default_cfg ( vcpmonitor5_t *ctx ) 
{
    uint16_t device_id = DUMMY;
    err_t err_flag = vcpmonitor5_get_device_id( ctx, &device_id );
    if ( VCPMONITOR5_MANUFACTURER_ID == device_id )
    {
        err_flag |= vcpmonitor5_sw_reset( ctx );
        Delay_100ms( );
    
        err_flag |= vcpmonitor5_set_op_mode( ctx, VCPMONITOR5_ADC_CFG_MODE_CNT_ALL );
        Delay_100ms( );

        err_flag |= vcpmonitor5_set_diag_flg_alr( ctx, VCPMONITOR5_ALR_DIAG_TRANSPARENT | 
                                                       VCPMONITOR5_ALR_DIAG_CNVR_DIS | 
                                                       VCPMONITOR5_ALR_DIAG_SLWALR_NAVG |
                                                       VCPMONITOR5_ALR_DIAG_APOL_NORMAL );
        Delay_100ms( );
    }
    else
    {
        err_flag = VCPMONITOR5_ERROR;
    }
    return err_flag;
}

err_t vcpmonitor5_generic_write ( vcpmonitor5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t vcpmonitor5_generic_read ( vcpmonitor5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t vcpmonitor5_reg_write ( vcpmonitor5_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 1 ] = ( uint8_t )   data_in;
    return vcpmonitor5_generic_write( ctx, reg, data_buf, 2 );
}

err_t vcpmonitor5_reg_read ( vcpmonitor5_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = vcpmonitor5_generic_read( ctx, reg, data_buf, 2 );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    return err_flag;
}

err_t vcpmonitor5_sw_reset ( vcpmonitor5_t *ctx ) 
{
    return vcpmonitor5_reg_write( ctx, VCPMONITOR5_REG_CONFIG, VCPMONITOR5_CFG_RST );
}

err_t vcpmonitor5_set_conv_dly ( vcpmonitor5_t *ctx, uint16_t dly_ms ) 
{
    err_t err_flag = VCPMONITOR5_ERROR;
    if ( dly_ms <= VCPMONITOR5_CFG_CONVDLY )
    {
        dly_ms /= 2;
        dly_ms <<= 6;
        err_flag = vcpmonitor5_reg_write( ctx, VCPMONITOR5_REG_CONFIG, dly_ms );
    }
    return err_flag;
}

err_t vcpmonitor5_set_op_mode ( vcpmonitor5_t *ctx, uint8_t op_mode ) 
{
    err_t err_flag = VCPMONITOR5_ERROR;
    if ( op_mode <= VCPMONITOR5_ADC_CFG_MODE_CNT_ALL )
    {
        uint16_t data_buf = DUMMY;
        err_flag = vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_ADC_CONFIG, &data_buf );
        data_buf &= VCPMONITOR5_ADC_CFG_MODE_BITMASK;
        data_buf |= ( uint16_t ) op_mode << 12;
        err_flag |= vcpmonitor5_reg_write( ctx, VCPMONITOR5_REG_ADC_CONFIG, data_buf );
    }
    return err_flag;
}

err_t vcpmonitor5_set_conv_time ( vcpmonitor5_t *ctx, uint8_t vbusct, uint8_t vsenct, uint8_t tct ) 
{
    err_t err_flag = VCPMONITOR5_ERROR;
    if ( ( vbusct | vsenct | tct ) <= VCPMONITOR5_ADC_CFG_VBSTA )
    {
        uint16_t data_buf = DUMMY;
        err_flag = vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_ADC_CONFIG, &data_buf );
        data_buf &= VCPMONITOR5_ADC_CFG_VBSTA_BITMASK; 
        data_buf |= ( uint16_t ) vbusct << 9;
        data_buf |= ( uint16_t ) vsenct << 6;
        data_buf |= ( uint16_t ) tct << 3;
        err_flag |= vcpmonitor5_reg_write( ctx, VCPMONITOR5_REG_ADC_CONFIG, data_buf );
    }
    return err_flag;
}

err_t vcpmonitor5_set_adc_avg ( vcpmonitor5_t *ctx, uint8_t avg ) 
{
    err_t err_flag = VCPMONITOR5_ERROR;
    if ( avg <= VCPMONITOR5_ADC_CFG_AVG )
    {
        uint16_t data_buf = DUMMY;
        err_flag = vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_ADC_CONFIG, &data_buf );
        data_buf &= VCPMONITOR5_ADC_CFG_AVG_BITMASK;
        data_buf |= ( uint16_t ) avg;
        err_flag |= vcpmonitor5_reg_write( ctx, VCPMONITOR5_REG_ADC_CONFIG, data_buf );
    }
    return err_flag;
}

err_t vcpmonitor5_get_bus_voltage ( vcpmonitor5_t *ctx, float *voltage ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_VBUS, &data_buf );
    *voltage = ( float ) data_buf;
    *voltage *= VCPMONITOR5_CONV_FACT_VBUS;
    *voltage /= VCPMONITOR5_UN_CONV_1K;
    return err_flag;
}

err_t vcpmonitor5_get_temperature ( vcpmonitor5_t *ctx, float *temperature ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_DIETEMP, &data_buf );
    *temperature = ( float ) ( ( int16_t ) ( data_buf >> 4 ) );
    *temperature *= VCPMONITOR5_CONV_FACT_DIETEMP;
    *temperature /= VCPMONITOR5_UN_CONV_1K;
    return err_flag;
}

err_t vcpmonitor5_get_current ( vcpmonitor5_t *ctx, float *current ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_CURRENT, &data_buf );
    *current = ( float ) ( ( int16_t ) data_buf );
    *current *= VCPMONITOR5_CONV_FACT_CURRENT;
    *current /= VCPMONITOR5_UN_CONV_1K;
    return err_flag;
}

err_t vcpmonitor5_get_power ( vcpmonitor5_t *ctx, float *power ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    uint32_t pwr_data = DUMMY;
    err_t err_flag = vcpmonitor5_generic_read( ctx, VCPMONITOR5_REG_POWER, data_buf, 3 );
    pwr_data = data_buf[ 0 ];
    pwr_data <<= 8;
    pwr_data |= data_buf[ 1 ];
    pwr_data <<= 8;
    pwr_data |= data_buf[ 2 ];
    *power = ( float ) ( pwr_data );
    *power *= VCPMONITOR5_CONV_FACT_POWER;
    *power /= VCPMONITOR5_UN_CONV_1M;
    return err_flag;
}

err_t vcpmonitor5_get_energy ( vcpmonitor5_t *ctx, float *energy ) 
{
    uint8_t data_buf[ 5 ] = { 0 };
    err_t err_flag = vcpmonitor5_generic_read( ctx, VCPMONITOR5_REG_ENERGY, data_buf, 5 );
    *energy = ( float ) ( data_buf[ 0 ] );
    for ( uint8_t n_cnt = 1; n_cnt < 5; n_cnt++ )
    {
        *energy *= VCPMONITOR5_CALC_EN_CHRG_RES;
        *energy += ( float ) ( data_buf[ n_cnt ] );
    }
    *energy *= VCPMONITOR5_CONV_FACT_ENERGY;
    *energy /= VCPMONITOR5_UN_CONV_1M;
    *energy /= VCPMONITOR5_CALC_EN_CHRG;
    return err_flag;
}

err_t vcpmonitor5_get_charge ( vcpmonitor5_t *ctx, float *charge ) 
{
    uint8_t data_buf[ 5 ] = { 0 };
    err_t err_flag = vcpmonitor5_generic_read( ctx, VCPMONITOR5_REG_CHARGE, data_buf, 5 );
    *charge = ( float ) ( data_buf[ 0 ] );
    for ( uint8_t n_cnt = 1; n_cnt < 5; n_cnt++ )
    {
        *charge *= VCPMONITOR5_CALC_EN_CHRG_RES;
        *charge += ( float ) ( data_buf[ n_cnt ] );
    }
    *charge *= VCPMONITOR5_CONV_FACT_CHARGE;
    *charge /= VCPMONITOR5_UN_CONV_1M;
    *charge /= VCPMONITOR5_CALC_EN_CHRG;
    return err_flag;
}

err_t vcpmonitor5_set_diag_flg_alr ( vcpmonitor5_t *ctx, uint16_t diag_flg_alr ) 
{
    diag_flg_alr &= VCPMONITOR5_ALR_DIAG_W_BITMASK; 
    return vcpmonitor5_reg_write( ctx, VCPMONITOR5_REG_ALERT_DIAG, diag_flg_alr );
}

err_t vcpmonitor5_get_indc_flg ( vcpmonitor5_t *ctx, uint16_t *indc_flg ) 
{
    err_t err_flag = vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_ALERT_DIAG, indc_flg );
    *indc_flg &= VCPMONITOR5_ALR_DIAG_R_BITMASK;
    return err_flag;
}

err_t vcpmonitor5_wait_conv_cmpl ( vcpmonitor5_t *ctx ) 
{
    uint16_t data_buf = VCPMONITOR5_ALR_DIAG_MEMSTAT;
    err_t err_flag = VCPMONITOR5_OK;

    while( VCPMONITOR5_ALR_DIAG_MEMSTAT != data_buf )
    {
        err_flag = vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_ALERT_DIAG, &data_buf );
        data_buf &= VCPMONITOR5_ALR_DIAG_CNVRF;
        Delay_1ms( );
    }

    return err_flag;
}

err_t vcpmonitor5_get_device_id ( vcpmonitor5_t *ctx, uint16_t *man_id ) 
{
    return vcpmonitor5_reg_read( ctx, VCPMONITOR5_REG_MANUFACTURER_ID, man_id );
}

uint8_t vcpmonitor5_get_alarm ( vcpmonitor5_t *ctx ) 
{
    return digital_in_read( &ctx->alr );
}


// ------------------------------------------------------------------------- END
