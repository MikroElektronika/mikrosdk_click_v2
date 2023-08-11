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
 * @file usbcsink2.c
 * @brief USB-C Sink 2 Click Driver.
 */

#include "usbcsink2.h"

/**
 * @brief Dummy and timeout data.
 * @details Definition of dummy and timeout data.
 */
#define DUMMY                 0x00
#define USBCSINK2_TIMEOUT     1000u

void usbcsink2_cfg_setup ( usbcsink2_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCSINK2_SET_DEV_ADDR;
    cfg->vref        = USBCSINK2_VREF_3V3;
}

err_t usbcsink2_init ( usbcsink2_t *ctx, usbcsink2_cfg_t *cfg ) 
{
    ctx->vref = cfg->vref;

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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return USBCSINK2_OK;
}

err_t usbcsink2_default_cfg ( usbcsink2_t *ctx ) 
{   
    err_t err_flag = usbcsink2_reset( ctx );
    Delay_1sec( );
    
    err_flag |= usbcsink2_get_pdo_num( ctx, &ctx->number_of_valid_pdo );
    Delay_1ms( );
    
    err_flag |= usbcsink2_read_pdo( ctx, &ctx->pdo_data[ 0 ] );
    Delay_1ms( );
    
    return err_flag;
}

err_t usbcsink2_generic_write ( usbcsink2_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = cmd;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t usbcsink2_generic_read ( usbcsink2_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, len );
}

err_t usbcsink2_read_raw_adc ( usbcsink2_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t usbcsink2_read_voltage ( usbcsink2_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t usbcsink2_set_vref ( usbcsink2_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t usbcsink2_read_pdo ( usbcsink2_t *ctx, uint8_t *pdo ) 
{
    return usbcsink2_generic_read( ctx, USBCSINK2_CMD_SRCPDO, pdo, USBCSINK2_SRCPDO_LENGTH );
}

err_t usbcsink2_get_pdo_num ( usbcsink2_t *ctx, uint8_t *pdo_num ) 
{
    return usbcsink2_generic_read( ctx, USBCSINK2_CMD_PDONUM, pdo_num, 1 );
}

err_t usbcsink2_read_status ( usbcsink2_t *ctx, uint8_t *status ) 
{
    return usbcsink2_generic_read( ctx, USBCSINK2_CMD_STATUS, status, 1 );
}

err_t usbcsink2_wait_rdo_req_success ( usbcsink2_t *ctx ) 
{
    err_t err_flag = USBCSINK2_OK;
    uint8_t status = DUMMY;
    uint16_t time_out = DUMMY;
    do 
    {
        err_flag |= usbcsink2_read_status( ctx, &status );
        time_out++;
        Delay_10ms( );
    }
    while ( ( USBCSINK2_RDO_REQ_SUCCESS != status ) || ( USBCSINK2_TIMEOUT < time_out ) );
    
    if ( USBCSINK2_TIMEOUT < time_out )
    {
        err_flag = USBCSINK2_ERROR;
    }
    return err_flag;
}

err_t usbcsink2_get_pdo_voltage ( usbcsink2_t *ctx, float *voltage_mv ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = usbcsink2_generic_read( ctx, USBCSINK2_CMD_VOLTAGE, &data_buf, 1 );
    *voltage_mv = ( float ) data_buf;
    *voltage_mv *= USBCSINK2_SENS_VTG_MV;
    return err_flag;
}

err_t usbcsink2_get_pdo_current ( usbcsink2_t *ctx, float *current_ma ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = usbcsink2_generic_read( ctx, USBCSINK2_CMD_CURRENT, &data_buf, 1 );
    *current_ma = ( float ) data_buf;
    *current_ma *= USBCSINK2_SENS_CURRENT_MA;
    return err_flag;
}

err_t usbcsink2_get_temperature ( usbcsink2_t *ctx, uint8_t *temperature ) 
{
    return usbcsink2_generic_read( ctx, USBCSINK2_CMD_TEMP, temperature, 1 );
}

err_t usbcsink2_write_rdo ( usbcsink2_t *ctx, uint8_t *rdo ) 
{
    return usbcsink2_generic_write( ctx, USBCSINK2_CMD_RDO, rdo, USBCSINK2_RDO_LENGTH );
}

err_t usbcsink2_reset ( usbcsink2_t *ctx ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    return usbcsink2_generic_read( ctx, USBCSINK2_CMD_RDO, data_buf, 4 );
}

uint8_t usbcsink2_get_interrupt ( usbcsink2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
