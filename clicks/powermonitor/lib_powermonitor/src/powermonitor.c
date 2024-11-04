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
 * @file powermonitor.c
 * @brief Power Monitor Click Driver.
 */

#include "powermonitor.h"

/**
 * @brief Power Monitor get ADC range function.
 * @details This function gets shunt full scale range selection across IN+ and IN- 
 * of Power Monitor Click board.
 * @param[in] ctx : Click context object.
 * See #powermonitor_t object definition for detailed explanation.
 * @return @li @c 0 - Shunt full scale range ±163.84 mV,
 *         @li @c 1 - Shunt full scale range ± 40.96 mV.
 *
 * @note None.
 *
 * @endcode
 */
static uint8_t powermonitor_get_adcrange ( powermonitor_t *ctx );

/**
 * @brief Power Monitor configuration delay function.
 * @details This function executes a gonfiguratio delay of the 10 milliseconds 
 * of Power Monitor Click board.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
static void config_delay ( void );

void powermonitor_cfg_setup ( powermonitor_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = POWERMONITOR_SET_DEV_ADDR_SDA_SDA;
}

err_t powermonitor_init ( powermonitor_t *ctx, powermonitor_cfg_t *cfg ) 
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

err_t powermonitor_default_cfg ( powermonitor_t *ctx ) 
{
    powermonitor_dev_cfg_t cfg_data;
    cfg_data.rstacc   = POWERMONITOR_RSTACC_NORMAL_OPERATION;
    cfg_data.convdly  = POWERMONITOR_CONVDLY_0_s;
    cfg_data.tempcomp = POWERMONITOR_TEMPCOMP_DISABLED;
    cfg_data.adcrange = POWERMONITOR_ADCRANGE_163_84_mV;
    err_t err_flag = powermonitor_set_configuration( ctx, cfg_data );
    config_delay( );
    
    powermonitor_adc_cfg_t adc_cfg;
    adc_cfg.mode   = POWERMONITOR_MODE_CONTINUOUS_SHOT_TEMP_SHUNT_BUS_VTG;
    adc_cfg.vbusct = POWERMONITOR_VBUSCT_CONVERSION_TIME_1052_nS;
    adc_cfg.vshct  = POWERMONITOR_VSHCT_CONVERSION_TIME_1052_nS;
    adc_cfg.vtct   = POWERMONITOR_VTCT_CONVERSION_TIME_1052_nS;
    adc_cfg.avg    = POWERMONITOR_AVG_AVERAGING_COUNT_1;
    err_flag |= powermonitor_set_adc_config( ctx, adc_cfg );
    config_delay( );
    
    powermonitor_set_bus_overvoltage_threshold( ctx, 4.5 );
    config_delay( );
    
    powermonitor_set_bus_undervoltage_threshold( ctx, 2.5 );
    config_delay( );
    
    powermonitor_set_shunt_overvoltage_threshold( ctx, 0.01 );
    config_delay( );
    
    powermonitor_set_shunt_undervoltage_threshold( ctx, 0.05 );
    config_delay( );
    
    return err_flag;
}

err_t powermonitor_generic_write ( powermonitor_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t powermonitor_generic_read ( powermonitor_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t powermonitor_soft_reset ( powermonitor_t *ctx ) 
{
    uint8_t tmp;
    err_t err_flag = powermonitor_generic_read( ctx, POWERMONITOR_REG_CONFIG, &tmp, 1 );
    
    tmp |= POWERMONITOR_RST_RESET_BIT;
    err_flag |= powermonitor_generic_write( ctx, POWERMONITOR_REG_CONFIG, &tmp, 1 );
    
    return err_flag;
}

err_t powermonitor_set_configuration ( powermonitor_t *ctx, powermonitor_dev_cfg_t cfg_data )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ]  = ( cfg_data.rstacc   & 0x01 ) << 6;
    tx_buf[ 0 ] |= ( cfg_data.convdly  & 0xFC ) >> 2;
    tx_buf[ 1 ]  = ( cfg_data.convdly  & 0x03 ) << 6;
    tx_buf[ 1 ] |= ( cfg_data.tempcomp & 0x01 ) << 5;
    tx_buf[ 1 ] |= ( cfg_data.adcrange & 0x01 ) << 4;
    
    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_CONFIG, tx_buf, 2 );
    
    return err_flag;
}

err_t powermonitor_get_configuration ( powermonitor_t *ctx, powermonitor_dev_cfg_t *cfg_data )
{
    uint8_t rx_buf[ 2 ];
    
    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_CONFIG, rx_buf, 2 );
    
    cfg_data->rstacc   = ( rx_buf[ 0 ] >> 6 ) & 0x01;
    cfg_data->convdly  = ( ( rx_buf[ 0 ] & 0x3F ) << 2 ) | ( ( rx_buf[ 1 ] & 0xC0 ) >> 6 );
    cfg_data->tempcomp = ( rx_buf[ 1 ] >> 5 ) & 0x01;
    cfg_data->adcrange = ( rx_buf[ 1 ] >> 4 ) & 0x01; 
    
    return err_flag;
}

err_t powermonitor_set_adc_config ( powermonitor_t *ctx, powermonitor_adc_cfg_t adc_cfg )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ]  = ( adc_cfg.mode    & 0x0F ) << 4;
    tx_buf[ 0 ] |= ( adc_cfg.vbusct  & 0x07 ) << 1;
    tx_buf[ 0 ] |= ( adc_cfg.vshct   & 0x04 ) >> 2;
    tx_buf[ 1 ]  = ( adc_cfg.vshct   & 0x03 ) << 6;
    tx_buf[ 1 ] |= ( adc_cfg.vtct    & 0x07 ) << 3;
    tx_buf[ 1 ] |= ( adc_cfg.avg     & 0x07 );
    
    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_ADCCONFIG, tx_buf, 2 );
    
    return err_flag;
}

err_t powermonitor_get_adc_configu ( powermonitor_t *ctx, powermonitor_adc_cfg_t *adc_cfg )
{
    uint8_t rx_buf[ 2 ];
    
    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_ADCCONFIG, rx_buf, 2 );
    
    adc_cfg->mode   = ( rx_buf[ 0 ] >> 4 ) & 0x0F;
    adc_cfg->vbusct = ( rx_buf[ 0 ] >> 2 ) & 0x0F;
    adc_cfg->vshct  = ( ( rx_buf[ 0 ] & 0x80 ) >> 5 ) | ( ( rx_buf[ 1 ] & 0xC0 ) >> 6 );
    adc_cfg->vtct   = ( rx_buf[ 1 ] >> 5 ) & 0x01;
    adc_cfg->avg    = ( rx_buf[ 1 ] >> 4 ) & 0x01; 
    
    return err_flag;
}

err_t powermonitor_set_bus_overvoltage_threshold ( powermonitor_t *ctx, float bovl )
{
    uint8_t tx_buf[ 2 ];
    uint16_t tmp;
    
    tmp = ( uint16_t ) ( bovl / 3.125 );
    
    tx_buf[ 0 ] = ( uint8_t ) ( tmp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   tmp;
    
    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_BOVL, tx_buf, 2 );
    
    return err_flag;
}

err_t powermonitor_set_bus_undervoltage_threshold ( powermonitor_t *ctx, float buvl )
{
    uint8_t tx_buf[ 2 ];
    uint16_t tmp;
    
    tmp = ( uint16_t ) ( buvl / 3.125 );
    
    tx_buf[ 0 ] = ( uint8_t ) ( tmp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   tmp;
    
    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_BUVL, tx_buf, 2 );
    
    return err_flag;
}

err_t powermonitor_set_shunt_overvoltage_threshold ( powermonitor_t *ctx, float sovl )
{
    uint8_t tx_buf[ 2 ];
    uint16_t tmp;
    float shunt_conv_factor;
    
    if ( powermonitor_get_adcrange( ctx ) == POWERMONITOR_ADCRANGE_163_84_mV ) 
    {
        shunt_conv_factor = 0.00000125;    
    } else 
    {
        shunt_conv_factor = 0.0000005;    
    }
    
    if ( sovl >= 0 )
    {
        tmp = ( sovl * ctx->shunt ) / shunt_conv_factor;
    }
    else 
    {
        float value_temp;
        value_temp = sovl * ( -1 );
        tmp = ( value_temp * ctx->shunt ) / shunt_conv_factor;
        tmp = ~tmp;
        ++tmp;
    }
    
    tx_buf[ 0 ] = ( uint8_t ) ( tmp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   tmp;
    
    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_SOVL, tx_buf, 2 );
    
    return err_flag;
}

err_t powermonitor_set_shunt_undervoltage_threshold ( powermonitor_t *ctx, float suvl )
{
    uint8_t tx_buf[ 2 ];
    uint16_t tmp;
    float shunt_conv_factor;
    
    if ( suvl >= 0 )
    {
        tmp = ( suvl * ctx->shunt ) / shunt_conv_factor;
    }
    else
    {
        float value_temp;
        value_temp = suvl * ( -1 );
        tmp = ( value_temp * ctx->shunt ) / shunt_conv_factor;
        tmp = ~tmp;
        tmp += 1;
    }
    
    tx_buf[ 0 ] = ( uint8_t ) ( tmp >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   tmp;
    
    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_SUVL, tx_buf, 2 );
    
    return err_flag;
}

err_t powermonitor_get_vshunt ( powermonitor_t *ctx, float *vshunt )
{
    uint8_t rx_buf[ 3 ];
    uint32_t tmp;
    
    err_t err_flag = powermonitor_generic_read( ctx, POWERMONITOR_REG_VSHUNT, rx_buf, 3 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    tmp >>= 4;
    
    *vshunt = ( float ) tmp;
    
    if ( tmp > 0x0007FFFF )
    {
        *vshunt -= 524288.0;
    } 
    
    if ( powermonitor_get_adcrange( ctx ) == POWERMONITOR_ADCRANGE_163_84_mV ) 
    {
        *vshunt *= 312.5;    
    } else 
    {
        *vshunt *= 78.125;    
    }
    
    *vshunt /= 1000000; 

    return err_flag;
}

err_t powermonitor_get_vbus ( powermonitor_t *ctx, float *vbus )
{
    uint8_t rx_buf[ 3 ];
    uint32_t tmp;
    
    err_t err_flag = powermonitor_generic_read( ctx, POWERMONITOR_REG_VBUS, rx_buf, 3 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    tmp >>= 4;
    
    *vbus = ( float ) tmp;
    *vbus *=  0.1953;
    
    return err_flag;
}

err_t powermonitor_get_temperature ( powermonitor_t *ctx, float *temperature )
{
    uint8_t rx_buf[ 2 ];
    int16_t tmp;
    
    err_t err_flag = powermonitor_generic_read( ctx, POWERMONITOR_REG_DIETEMP, rx_buf, 2 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    
    *temperature = ( float ) tmp;
    *temperature *= 0.0078125;
    
    return err_flag;
}

err_t powermonitor_get_current ( powermonitor_t *ctx, float *current )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 3 ];
    uint32_t tmp;
    float current_lsb;
    float temp;
    uint16_t shunt_cal;
    
    if ( powermonitor_get_adcrange( ctx ) == POWERMONITOR_ADCRANGE_163_84_mV ) 
    {
        temp = 0.16384;
    } else 
    {
        temp = 0.04096;  
    }
    
    current_lsb = (temp / ctx->shunt) / 524288;
    
    shunt_cal = ( uint16_t ) ( 13107.2e6 * current_lsb * ctx->shunt );
    
    tx_buf[ 0 ] = ( uint8_t ) ( shunt_cal >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   shunt_cal;

    err_t err_flag = powermonitor_generic_write( ctx, POWERMONITOR_REG_SHUNT_CAL, tx_buf, 2 );
    config_delay( );
    
    err_flag |= powermonitor_generic_read( ctx, POWERMONITOR_REG_CURRENT, rx_buf, 3 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    tmp >>= 4;
    
    *current = ( float ) tmp;
    *current *= current_lsb;
    *current *= 1000;
    
    return err_flag;
}

err_t powermonitor_get_power ( powermonitor_t *ctx, float *power )
{
    uint8_t rx_buf[ 5 ];
    uint32_t tmp;
    float current_lsb;
    float temp;
    
    if ( powermonitor_get_adcrange( ctx ) == POWERMONITOR_ADCRANGE_163_84_mV ) 
    {
        temp = 0.16384;
    } else 
    {
        temp = 0.04096;  
    }
    
    current_lsb = ( temp / ctx->shunt) / 524288;
    
    err_t err_flag = powermonitor_generic_read( ctx, POWERMONITOR_REG_POWER, rx_buf, 5 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    
    *power = ( float ) tmp;
    *power *= current_lsb;
    *power *= 3.2;

    return err_flag;
}

err_t powermonitor_get_energy_data ( powermonitor_t *ctx, uint8_t *energy_data )
{
    err_t err_flag = powermonitor_generic_read( ctx, POWERMONITOR_REG_ENERGY, energy_data, 5 );
    
    return err_flag;
}

err_t powermonitor_get_energy ( powermonitor_t *ctx, float *energy )
{
    float power;
    
    err_t err_flag = powermonitor_get_power ( ctx, &power );
    
    *energy = power;
    *energy *= 16;
    
    return err_flag;
}

err_t powermonitor_get_id ( powermonitor_t *ctx, uint8_t *manufacturer_id, uint16_t *die_id, uint8_t *rev_id )
{
    uint8_t rx_buf[ 2 ];
    
    err_t err_flag = powermonitor_generic_read( ctx, POWERMONITOR_REG_MANUFACTURER_ID, manufacturer_id, 2 );
    
    err_flag |= powermonitor_generic_read( ctx, POWERMONITOR_REG_DEVICE_ID, rx_buf, 2 );
    
    *die_id = rx_buf[ 0 ];
    *die_id <<= 8;
    *die_id |= rx_buf[ 1 ];
    *die_id >>= 4;
    
    *rev_id = rx_buf[ 1 ] & 0x0F;
    
    return err_flag;
}

err_t powermonitor_get_alert ( powermonitor_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

static uint8_t powermonitor_get_adcrange ( powermonitor_t *ctx )
{
    uint8_t rx_buf[ 2 ];
   
    err_t err_flag = powermonitor_generic_read( ctx, POWERMONITOR_REG_CONFIG, rx_buf, 1 );
    
    rx_buf[ 0 ] &= 0x10;
    rx_buf[ 0 ] >>= 4;
    
    return rx_buf[ 0 ];
}

static void config_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
