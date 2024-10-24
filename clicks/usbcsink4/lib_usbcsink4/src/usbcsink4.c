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
 * @file usbcsink4.c
 * @brief USB-C Sink 4 Click Driver.
 */

#include "usbcsink4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY          0x00

void usbcsink4_cfg_setup ( usbcsink4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->flt     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCSINK4_DEVICE_ADDRESS;
}

err_t usbcsink4_init ( usbcsink4_t *ctx, usbcsink4_cfg_t *cfg ) 
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

    digital_in_init( &ctx->flt, cfg->flt );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t usbcsink4_default_cfg ( usbcsink4_t *ctx ) 
{
    err_t err_flag = USBCSINK4_OK;
    Delay_100ms( );
    uint16_t silicon_id = DUMMY;
    err_flag |= usbcsink4_get_silicon_id( ctx , &silicon_id );
    if ( USBCSINK4_SILICON_ID_BCR_LITE == silicon_id )
    {
        uint8_t data_buf[ 4 ] = { USBCSINK4_OVP_CONFIG_SIG_DISABLE, USBCSINK4_OVP_CONFIG_THOLD_DEFAULT, 
                                  USBCSINK4_OVP_CONFIG_DBNC_DEFAULT, DUMMY };
        err_flag |= usbcsink4_generic_write( ctx, USBCSINK4_REG_OVP_CONFIG, data_buf, 4 );
        Delay_100ms( );

        data_buf[ 0 ] = USBCSINK4_CHARGING_MODE_ENABLE;
        err_flag |= usbcsink4_generic_write( ctx, USBCSINK4_REG_CHARGING_MODE_DISABLE, data_buf, 1 );
        Delay_100ms( );
    }
    else
    {
        err_flag = USBCSINK4_ERROR;
    }
    return err_flag;
}

err_t usbcsink4_generic_write ( usbcsink4_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) reg;
    data_buf[ 1 ] = ( uint8_t ) ( reg >> 8 );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 2 );
}

err_t usbcsink4_generic_read ( usbcsink4_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) reg;
    data_buf[ 1 ] = ( uint8_t ) ( reg >> 8 );
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, len );
}

err_t usbcsink4_get_silicon_id ( usbcsink4_t *ctx, uint16_t *silicon_id ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = usbcsink4_generic_read( ctx, USBCSINK4_REG_SILICON_ID, data_buf, 2 );
    *silicon_id = data_buf[ 1 ];
    *silicon_id <<= 8;
    *silicon_id |= data_buf[ 0 ];
    return err_flag;
}

err_t usbcsink4_get_type_c_status ( usbcsink4_t *ctx, usbcsink4_type_c_status_t *type_c_status ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = usbcsink4_generic_read( ctx, USBCSINK4_REG_TYPE_C_STATUS, data_buf, 4 );
    type_c_status->port_par_cxn =   data_buf[ 0 ]        & USBCSINK4_TYPE_C_ST_PORT_BITMAKS;
    type_c_status->cc_pol       = ( data_buf[ 0 ] >> 1 ) & USBCSINK4_TYPE_C_ST_CC_BITMAKS;
    type_c_status->att_dev_type = ( data_buf[ 0 ] >> 2 ) & USBCSINK4_TYPE_C_ST_ATT_BITMAKS;
    type_c_status->curr_lvl     = ( data_buf[ 0 ] >> 6 ) & USBCSINK4_TYPE_C_ST_CURR_BITMAKS;
    return err_flag;
}

err_t usbcsink4_get_bus_voltage ( usbcsink4_t *ctx, float *vbus_v ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = usbcsink4_generic_read( ctx, USBCSINK4_REG_BUS_VOLTAGE, &data_buf, 1 );
    *vbus_v = ( float ) data_buf;
    *vbus_v *= USBCSINK4_VOLTAGE_SENS;
    return err_flag;
}

err_t usbcsink4_get_bus_current ( usbcsink4_t *ctx, float *vbus_c ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = usbcsink4_generic_read( ctx, USBCSINK4_REG_BUS_CURRENT, &data_buf, 1 );
    *vbus_c = ( float ) data_buf;
    *vbus_c *= USBCSINK4_CURRENT_SENS;
    return err_flag;
}

err_t usbcsink4_get_event_status ( usbcsink4_t *ctx, usbcsink4_event_status_t *event_status ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = usbcsink4_generic_read( ctx, USBCSINK4_REG_EVENT_STATUS, data_buf, 4 );
    event_status->dev_att        =   data_buf[ 0 ]        & 0x01;
    event_status->dev_disc       = ( data_buf[ 0 ] >> 1 ) & 0x01;
    event_status->pd_cn_comp     = ( data_buf[ 0 ] >> 2 ) & 0x01;
    event_status->pwr_role       = ( data_buf[ 0 ] >> 3 ) & 0x01;
    event_status->data_role      = ( data_buf[ 0 ] >> 4 ) & 0x01;
    event_status->vconn          = ( data_buf[ 0 ] >> 5 ) & 0x01;
    event_status->hw_rst_rec     = ( data_buf[ 0 ] >> 6 ) & 0x01;
    event_status->hw_rst_sent    = ( data_buf[ 0 ] >> 7 ) & 0x01;
    event_status->soft_rst_sent  =   data_buf[ 1 ]        & 0x01;
    event_status->cable_rst_sent = ( data_buf[ 1 ] >> 1 ) & 0x01;
    event_status->err_rcvy       = ( data_buf[ 1 ] >> 2 ) & 0x01;
    event_status->vbus_err       = ( data_buf[ 3 ] >> 5 ) & 0x01;
    event_status->vbus_vtg_ovr   = ( data_buf[ 3 ] >> 6 ) & 0x01;
    event_status->vbus_curr_ovr  = ( data_buf[ 3 ] >> 7 ) & 0x01;

    data_buf[ 0 ] = USBCSINK4_CHG_MODE_STATUS_CLEAR;
    data_buf[ 1 ] = USBCSINK4_CHG_MODE_STATUS_CLEAR;
    data_buf[ 2 ] = USBCSINK4_CHG_MODE_STATUS_CLEAR;
    data_buf[ 3 ] = USBCSINK4_CHG_MODE_STATUS_CLEAR;
    err_flag |= usbcsink4_generic_write( ctx, USBCSINK4_REG_EVENT_STATUS, data_buf, 4 );
    return err_flag;
}

err_t usbcsink4_get_chrg_mode ( usbcsink4_t *ctx, uint8_t *chrg_mode ) 
{
    return usbcsink4_generic_read( ctx, USBCSINK4_REG_CHARGING_MODE_STATUS, chrg_mode, 1 );
}

err_t usbcsink4_reset_device ( usbcsink4_t *ctx ) 
{
    uint8_t data_buf[ 2 ] = { USBCSINK4_SIG_RESET, USBCSINK4_RESET_DEVICE };
    return usbcsink4_generic_write( ctx, USBCSINK4_REG_RESET, data_buf, 2 );
}

err_t usbcsink4_reset_i2c ( usbcsink4_t *ctx ) 
{
    uint8_t data_buf[ 2 ] = { USBCSINK4_SIG_RESET, USBCSINK4_RESET_I2C };
    return usbcsink4_generic_write( ctx, USBCSINK4_REG_RESET, data_buf, 2 );
}

err_t usbcsink4_get_response ( usbcsink4_t *ctx, uint8_t *rsp_code ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t interrupt = 0;
    err_t err_flag = usbcsink4_generic_read( ctx, USBCSINK4_REG_INTERRUPT, &interrupt, 1 );
    if ( USBCSINK4_INTERRUPT_RESPONSE_DEV == interrupt )
    {
        err_flag |= usbcsink4_generic_read( ctx, USBCSINK4_REG_DEV_RESPONSE, data_buf, 2 );
    }
    else if ( USBCSINK4_INTERRUPT_RESPONSE_PD == interrupt )
    {
        err_flag |= usbcsink4_generic_read( ctx, USBCSINK4_REG_PD_RESPONSE, data_buf, 4 );
    }
    *rsp_code = data_buf[ 0 ];
    return err_flag;
}

uint8_t usbcsink4_get_interrupt ( usbcsink4_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t usbcsink4_get_fault_condition ( usbcsink4_t *ctx ) 
{
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END
