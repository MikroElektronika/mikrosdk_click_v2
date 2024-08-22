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
 * @file pmic.c
 * @brief PMIC Click Driver.
 */

#include "pmic.h"

void pmic_cfg_setup ( pmic_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PMIC_DEVICE_ADDRESS;
}

err_t pmic_init ( pmic_t *ctx, pmic_cfg_t *cfg ) 
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

err_t pmic_default_cfg ( pmic_t *ctx ) 
{
    err_t error_flag = PMIC_OK;

    // Disable and clear all interrupts.
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_INTENEVENTSADCCLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_EVENTSADCCLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_INTENEVENTSBCHARGER0CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_EVENTSBCHARGER0CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_INTENEVENTSBCHARGER1CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_EVENTSBCHARGER1CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_INTENEVENTSBCHARGER2CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_EVENTSBCHARGER2CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_INTENEVENTSSHPHLDCLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_EVENTSSHPHLDCLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_INTENEVENTSVBUSIN0CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_EVENTSVBUSIN0CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_INTENEVENTSVBUSIN1CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_EVENTSVBUSIN1CLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_INTENEVENTSGPIOCLR, PMIC_EVENTS_ALL_FLAGS );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_MAIN_EVENTSGPIOCLR, PMIC_EVENTS_ALL_FLAGS );
    
    // Set GPIO 4 as GPO Interrupt.
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_GPIOS_GPIOMODE_4, PMIC_GPIO_MODE_GPOIRQ );
    
    // Set GPIO 0 as GPO Reset.
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_GPIOS_GPIOMODE_0, PMIC_GPIO_MODE_GPORESET );
    
	// Disable NTC module to work with two-wire batteries.
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_BCHARGER_BCHGDISABLESET, PMIC_BCHGDISABLESET_IGNORENTC );

	// Disable charger before changing charge current.
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_BCHARGER_BCHGENABLECLR, PMIC_BCHGENABLECLR_DISABLECHG );
    
    // Enable VBAT auto measure every 1 second in single measurement mode
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_ADC_ADCCONFIG, PMIC_ADCCONFIG_AUTOENABLE );

    // Set charging current.
    error_flag |= pmic_set_charging_current ( ctx, PMIC_CHARGING_CURRENT_DEFAULT );
    
    // Set battery termination voltage to 4.2V.
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_BCHARGER_BCHGVTERM, PMIC_BCHGVTERMNORM_4V20 );
    
	// Enable charger for events handling.
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_BCHARGER_BCHGENABLESET, PMIC_BCHGENABLESET_ENABLECHG );
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_BCHARGER_BCHGDISABLECLR, PMIC_BCHGDISABLECLR_ENABLERCHG );

    return error_flag;
}

err_t pmic_reg_write ( pmic_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 2 );
}

err_t pmic_reg_read ( pmic_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, data_out, len );
    return error_flag;
}

err_t pmic_reg_write_byte ( pmic_t *ctx, uint16_t reg, uint8_t data_in )
{
    return pmic_reg_write( ctx, reg, &data_in, 1 );
}

err_t pmic_reg_read_byte ( pmic_t *ctx, uint16_t reg, uint8_t *data_out )
{
    return pmic_reg_read( ctx, reg, data_out, 1 );
}

uint8_t pmic_get_int_pin ( pmic_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t pmic_wait_for_event ( pmic_t *ctx, uint16_t evt_set_reg, uint8_t bit_mask )
{
    err_t error_flag = PMIC_OK;
    uint32_t timeout_cnt = 0;
    uint8_t reg_data = 0;
    while ( PMIC_OK == error_flag )
    {
        error_flag |= pmic_reg_read_byte ( ctx, evt_set_reg, &reg_data );
        if ( bit_mask == ( reg_data & bit_mask ) )
        {
            error_flag |= pmic_reg_write_byte ( ctx, evt_set_reg + 1, bit_mask );
            break;
        }
        if ( timeout_cnt++ > PMIC_WAIT_EVENT_TIMEOUT_MS )
        {
            error_flag = PMIC_ERROR;
        }
        Delay_1ms ( );
    }
    return error_flag;
}

err_t pmic_get_vbat ( pmic_t *ctx, uint16_t *vbat )
{
    err_t error_flag = PMIC_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_adc = 0;
    if ( PMIC_OK != pmic_wait_for_event ( ctx, PMIC_REG_MAIN_EVENTSADCSET, PMIC_EVENTADCVBATRDY ) )
    {
        return PMIC_ERROR;
    }
    error_flag |= pmic_reg_read_byte ( ctx, PMIC_REG_ADC_ADCVBATRESULTMSB, &data_buf[ 0 ] );
    error_flag |= pmic_reg_read_byte ( ctx, PMIC_REG_ADC_ADCGP0RESULTLSBS, &data_buf[ 1 ] );
    if ( ( PMIC_OK == error_flag ) && ( NULL != vbat ) )
    {
        raw_adc = ( ( uint16_t ) data_buf[ 0 ] << 2 ) | ( data_buf[ 1 ] & 0x03 );
        *vbat = ( uint16_t ) ( ( float ) raw_adc * PMIC_VBAT_FULL_SCALE_MILLIVOLTS / PMIC_VBAT_DATA_RESOLUTION );
    }
    return error_flag;
}

err_t pmic_get_vbus ( pmic_t *ctx, uint16_t *vbus )
{
    err_t error_flag = PMIC_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_adc = 0;
    // Trigger VBUS measurement
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_ADC_TASKVBUS7MEASURE, PMIC_TRIGGER_MEASUREMENT );
    if ( PMIC_OK != pmic_wait_for_event ( ctx, PMIC_REG_MAIN_EVENTSADCSET, PMIC_EVENTADCVBUS7V0RDY ) )
    {
        return PMIC_ERROR;
    }
    error_flag |= pmic_reg_read_byte ( ctx, PMIC_REG_ADC_ADCVBAT3RESULTMSB, &data_buf[ 0 ] );
    error_flag |= pmic_reg_read_byte ( ctx, PMIC_REG_ADC_ADCGP1RESULTLSBS, &data_buf[ 1 ] );
    if ( ( PMIC_OK == error_flag ) && ( NULL != vbus ) )
    {
        raw_adc = ( ( uint16_t ) data_buf[ 0 ] << 2 ) | ( ( data_buf[ 1 ] >> 6 ) & 0x03 );
        *vbus = ( uint16_t ) ( ( float ) raw_adc * PMIC_VBUS_FULL_SCALE_MILLIVOLTS / PMIC_VBUS_DATA_RESOLUTION );
    }
    return error_flag;
}

err_t pmic_get_vsys ( pmic_t *ctx, uint16_t *vsys )
{
    err_t error_flag = PMIC_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_adc = 0;
    // Trigger VSYS measurement
    error_flag |= pmic_reg_write_byte ( ctx, PMIC_REG_ADC_TASKVSYSMEASURE, PMIC_TRIGGER_MEASUREMENT );
    if ( PMIC_OK != pmic_wait_for_event ( ctx, PMIC_REG_MAIN_EVENTSADCSET, PMIC_EVENTADCVSYSRDY ) )
    {
        return PMIC_ERROR;
    }
    error_flag |= pmic_reg_read_byte ( ctx, PMIC_REG_ADC_ADCVSYSRESULTMSB, &data_buf[ 0 ] );
    error_flag |= pmic_reg_read_byte ( ctx, PMIC_REG_ADC_ADCGP0RESULTLSBS, &data_buf[ 1 ] );
    if ( ( PMIC_OK == error_flag ) && ( NULL != vsys ) )
    {
        raw_adc = ( ( uint16_t ) data_buf[ 0 ] << 2 ) | ( ( data_buf[ 1 ] >> 6 ) & 0x03 );
        *vsys = ( uint16_t ) ( ( float ) raw_adc * PMIC_VSYS_FULL_SCALE_MILLIVOLTS / PMIC_VSYS_DATA_RESOLUTION );
    }
    return error_flag;
}

err_t pmic_set_charging_current ( pmic_t *ctx, uint16_t current )
{
    if ( ( current < PMIC_CHARGING_CURRENT_MIN ) || ( current > PMIC_CHARGING_CURRENT_MAX ) )
    {
        return PMIC_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_data = current / 2;
    data_buf[ 0 ] = ( uint8_t ) ( raw_data >> 1 );
    data_buf[ 1 ] = ( uint8_t ) ( raw_data & 1 );
    return pmic_reg_write ( ctx, PMIC_REG_BCHARGER_BCHGISETMSB, data_buf, 2 );
}

// ------------------------------------------------------------------------- END
