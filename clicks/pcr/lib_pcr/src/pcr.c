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
 * @file pcr.c
 * @brief PCR Click Driver.
 */

#include "pcr.h"

void pcr_cfg_setup ( pcr_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PCR_DEVICE_ADDRESS;
}

err_t pcr_init ( pcr_t *ctx, pcr_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wup, cfg->wup );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );

    return I2C_MASTER_SUCCESS;
}

err_t pcr_default_cfg ( pcr_t *ctx ) 
{
    err_t error_flag = PCR_OK;
    pcr_hw_reset( ctx );

    error_flag |= pcr_write_reg( ctx, PCR_REG_COMMAND, PCR_RESET_MODULE_CMD );
    err_t busy_flag;
    do
    {
        busy_flag = pcr_check_if_busy( ctx );
        Delay_100ms( );
    }
    while ( PCR_BUSY == busy_flag );

    error_flag |= pcr_write_reg( ctx, PCR_REG_START, PCR_MIN_DISTANCE );
    Delay_100ms( );
    error_flag |= pcr_write_reg( ctx, PCR_REG_END, PCR_MAX_DISTANCE );
    Delay_100ms( );
    error_flag |= pcr_write_reg( ctx, PCR_REG_COMMAND, PCR_APPLY_CFG_AND_CALIB_CMD );
    Delay_100ms( );
    
    do
    {
        busy_flag = pcr_check_if_busy( ctx );
        Delay_100ms( );
    }
    while ( PCR_BUSY == busy_flag );
    while ( PCR_PIN_STATE_HIGH == pcr_get_int_pin( ctx ) );
    Delay_100ms( );

    error_flag |= pcr_check_if_ok( ctx );
    Delay_100ms( );

    return error_flag;
}

err_t pcr_generic_write ( pcr_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t pcr_generic_read ( pcr_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void pcr_set_wup_pin ( pcr_t *ctx, uint8_t pin_state )
{
    if ( PCR_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->wup );
    }
    else
    {
        digital_out_low( &ctx->wup );
    }
}

void pcr_set_rst_pin ( pcr_t *ctx, uint8_t pin_state )
{
    if ( PCR_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

uint8_t pcr_get_int_pin ( pcr_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void pcr_hw_reset ( pcr_t *ctx )
{
    pcr_set_rst_pin( ctx, PCR_PIN_STATE_LOW );
    Delay_100ms( );
    pcr_set_rst_pin( ctx, PCR_PIN_STATE_HIGH );
    Delay_100ms( );
}

err_t pcr_write_reg ( pcr_t *ctx, uint16_t reg, uint32_t data_in )
{
    err_t error_flag = PCR_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg >> 8 ); 
    data_buf[ 1 ] = ( uint8_t ) reg; 
    data_buf[ 2 ] = ( uint8_t ) ( data_in >> 24 ); 
    data_buf[ 3 ] = ( uint8_t ) ( data_in >> 16 ); 
    data_buf[ 4 ] = ( uint8_t ) ( data_in >> 8 ); 
    data_buf[ 5 ] = ( uint8_t ) data_in; 

    pcr_set_wup_pin( ctx, PCR_PIN_STATE_HIGH );
    while ( PCR_PIN_STATE_HIGH != pcr_get_int_pin( ctx ) );
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, 6 );
    while ( PCR_PIN_STATE_HIGH != pcr_get_int_pin( ctx ) );
    pcr_set_wup_pin( ctx, PCR_PIN_STATE_LOW );

    return error_flag;
}

err_t pcr_read_reg ( pcr_t *ctx, uint16_t reg, uint32_t *data_out )
{
    err_t error_flag = PCR_OK;
    uint8_t tx_data_buf[ 2 ] = { 0 };
    uint8_t rx_data_buf[ 4 ] = { 0 };
    uint32_t tmp_data = 0;

    tx_data_buf[ 0 ] = ( uint8_t ) ( reg >> 8 );
    tx_data_buf[ 1 ] = ( uint8_t ) reg;

    pcr_set_wup_pin( ctx, PCR_PIN_STATE_HIGH );
    while ( PCR_PIN_STATE_HIGH != pcr_get_int_pin( ctx ) );
    error_flag |= i2c_master_write( &ctx->i2c, tx_data_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, rx_data_buf, 4 );
    while ( PCR_PIN_STATE_HIGH != pcr_get_int_pin( ctx ) );
    pcr_set_wup_pin( ctx, PCR_PIN_STATE_LOW );

    tmp_data = rx_data_buf[ 0 ];
    tmp_data <<= 8;
    tmp_data |= rx_data_buf[ 1 ];
    tmp_data <<= 8;
    tmp_data |= rx_data_buf[ 2 ];
    tmp_data <<= 8;
    tmp_data |= rx_data_buf[ 3 ];

    *data_out = tmp_data;

    return error_flag;
}

err_t pcr_get_status ( pcr_t *ctx, uint32_t *status )
{
    return pcr_read_reg( ctx, PCR_REG_DETECTOR_STATUS, status );
}

err_t pcr_check_if_busy ( pcr_t *ctx )
{
    uint32_t tmp_data = 0;

    pcr_get_status( ctx, &tmp_data );
    if ( tmp_data & PCR_STATUS_BUSY )
    {
        return PCR_BUSY;
    }
    else
    {
        return PCR_OK;
    }

}

err_t pcr_check_if_ok ( pcr_t *ctx )
{
    err_t error_flag = PCR_OK;
    uint32_t status_data = 0;
    uint32_t tmp_data = 0;

    status_data = PCR_STATUS_RSS_REG_OK | 
                  PCR_STATUS_CFG_CREATE_OK |
                  PCR_STATUS_SENSOR_CREATE_OK |
                  PCR_STATUS_DETECTOR_CREATE_OK |
                  PCR_STATUS_DETECTOR_BUFFER_OK |
                  PCR_STATUS_SENSOR_BUFFER_OK |
                  PCR_STATUS_CALIB_BUFFER_OK |
                  PCR_STATUS_CFG_APPLY_OK |
                  PCR_STATUS_SENSOR_CALIB_OK |
                  PCR_STATUS_DETECTOR_CALIB_OK;

    if ( PCR_OK == pcr_get_status( ctx, &tmp_data ) )
    {
        if ( status_data != tmp_data )
        { 
            return PCR_ERROR;
        }
        else
        {
            return PCR_OK;
        }
    }

    return PCR_ERROR;
}

err_t pcr_get_distance ( pcr_t *ctx, uint32_t *distance_data )
{
    err_t error_flag = PCR_OK;
    uint32_t tmp_data = 0;

    error_flag |= pcr_write_reg( ctx, PCR_REG_COMMAND, PCR_MEASURE_DISTANCE_CMD );

    err_t busy_flag;
    do
    {
        busy_flag = pcr_check_if_busy( ctx );
        Delay_100ms( );
    }
    while ( PCR_OK != busy_flag );

    error_flag |= pcr_read_reg( ctx, PCR_REG_PEAK0_DISTANCE, &tmp_data );

    if ( PCR_OK == error_flag )
    {
        *distance_data = tmp_data;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
