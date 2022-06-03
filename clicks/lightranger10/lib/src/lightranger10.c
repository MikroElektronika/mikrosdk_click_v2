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
 * @file lightranger10.c
 * @brief LightRanger 10 Click Driver.
 */

#include "lightranger10.h"

void lightranger10_cfg_setup ( lightranger10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHTRANGER10_DEVICE_ADDRESS;
}

err_t lightranger10_init ( lightranger10_t *ctx, lightranger10_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t lightranger10_default_cfg ( lightranger10_t *ctx ) 
{
    err_t error_flag = LIGHTRANGER10_OK;
    lightranger10_reset_device ( ctx );
    if ( LIGHTRANGER10_ERROR == lightranger10_check_communication ( ctx ) )
    {
        return LIGHTRANGER10_ERROR;
    }
    error_flag |= lightranger10_soft_reset ( ctx );
    error_flag |= lightranger10_set_distance_mode ( ctx, LIGHTRANGER10_DISTANCE_MODE_MEDIUM );
    error_flag |= lightranger10_set_inter_measurement_period_ms ( ctx, LIGHTRANGER10_DEFAULT_IM_PERIOD_MS );
    error_flag |= lightranger10_start_measurement ( ctx );
    error_flag |= lightranger10_clear_interrupts ( ctx );
    return error_flag;
}

err_t lightranger10_generic_write ( lightranger10_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    return i2c_master_write ( &ctx->i2c, data_buf, len + 2 );
}

err_t lightranger10_generic_read ( lightranger10_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, len );
}

err_t lightranger10_write_byte ( lightranger10_t *ctx, uint16_t reg, uint8_t data_in )
{
    return lightranger10_generic_write ( ctx, reg, &data_in, 1 );
}

err_t lightranger10_read_byte ( lightranger10_t *ctx, uint16_t reg, uint8_t *data_out )
{
    return lightranger10_generic_read ( ctx, reg, data_out, 1 );
}

err_t lightranger10_write_word ( lightranger10_t *ctx, uint16_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    return lightranger10_generic_write ( ctx, reg, data_buf, 2 );
}

err_t lightranger10_read_word ( lightranger10_t *ctx, uint16_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = lightranger10_generic_read ( ctx, reg, data_buf, 2 );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t lightranger10_write_dword ( lightranger10_t *ctx, uint16_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    return lightranger10_generic_write ( ctx, reg, data_buf, 4 );
}

err_t lightranger10_read_dword ( lightranger10_t *ctx, uint16_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = lightranger10_generic_read ( ctx, reg, data_buf, 4 );
    *data_out = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) | 
                ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    return error_flag;
}

err_t lightranger10_check_communication ( lightranger10_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( LIGHTRANGER10_OK == lightranger10_generic_read ( ctx, LIGHTRANGER10_REG_MODEL_ID, data_buf, 2 ) )
    {
        if ( ( LIGHTRANGER10_MODEL_ID == data_buf[ 0 ] ) &&
             ( LIGHTRANGER10_MODEL_TYPE == data_buf[ 1 ] ) )
        {
            return LIGHTRANGER10_OK;
        }
    }
    return LIGHTRANGER10_ERROR;
}

uint8_t lightranger10_get_int_pin ( lightranger10_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void lightranger10_enable_device ( lightranger10_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

void lightranger10_disable_device ( lightranger10_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
}

void lightranger10_reset_device ( lightranger10_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

err_t lightranger10_soft_reset ( lightranger10_t *ctx )
{
    err_t error_flag = lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SOFT_RESET, LIGHTRANGER10_SOFT_RESET_SET );
    Delay_1ms ( );
    error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SOFT_RESET, LIGHTRANGER10_SOFT_RESET_CLEAR );
    Delay_100ms ( );
    return error_flag;
}

err_t lightranger10_clear_interrupts ( lightranger10_t *ctx )
{
    return lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SYSTEM_INTERRUPT_CLEAR, LIGHTRANGER10_INTERRUPT_CLEAR );
}

err_t lightranger10_set_inter_measurement_period_ms ( lightranger10_t *ctx, uint32_t period_ms )
{
    uint16_t osc_calibrate_val;
    err_t error_flag = lightranger10_read_word ( ctx, LIGHTRANGER10_REG_RESULT_OSC_CALIBRATE_VAL, &osc_calibrate_val );
    error_flag |= lightranger10_write_dword ( ctx, LIGHTRANGER10_REG_SYSTEM_INT_MEAS_PERIOD, 
                                                   period_ms * ( osc_calibrate_val + LIGHTRANGER10_OSC_CALIB_IM_PERIOD_OFFSET ) );
    return error_flag;
}

err_t lightranger10_set_distance_offset ( lightranger10_t *ctx, int16_t offset_mm )
{
    err_t error_flag = LIGHTRANGER10_OK;
    error_flag |= lightranger10_write_word( ctx, LIGHTRANGER10_REG_ALGO_PTP_RANGE_OFFSET_MM, 
                                                 ( offset_mm * LIGHTRANGER10_ALGO_PTP_RANGE_OFFSET_MM_MULT ) );
    error_flag |= lightranger10_write_word( ctx, LIGHTRANGER10_REG_MM_CFG_INNER_OFFSET_MM, 
                                                 LIGHTRANGER10_MM_CFG_INNER_OFFSET_MM_RESET );
    error_flag |= lightranger10_write_word( ctx, LIGHTRANGER10_REG_MM_CFG_OUTER_OFFSET_MM, 
                                                 LIGHTRANGER10_MM_CFG_OUTER_OFFSET_MM_RESET );
    return error_flag;
}

err_t lightranger10_calibrate_distance ( lightranger10_t *ctx, uint16_t target_distance_mm )
{
    uint32_t avg_distance_mm = 0;
    uint16_t distance_mm;
    int16_t offset_mm;
    err_t error_flag = LIGHTRANGER10_OK;
    error_flag |= lightranger10_set_distance_offset ( ctx, LIGHTRANGER10_ALGO_PTP_RANGE_OFFSET_MM_RESET );
    for ( uint16_t cnt = 0; cnt < LIGHTRANGER10_CALIBRATE_DISTANCE_AVERAGE_NUM; cnt++ )
    {
        while ( lightranger10_get_int_pin ( ctx ) );
        error_flag |= lightranger10_clear_interrupts ( ctx ); 
        error_flag |= lightranger10_get_distance ( ctx, &distance_mm );
        avg_distance_mm += distance_mm;
    }
    avg_distance_mm /= LIGHTRANGER10_CALIBRATE_DISTANCE_AVERAGE_NUM;
    offset_mm = ( int16_t ) target_distance_mm - avg_distance_mm;
    error_flag |= lightranger10_set_distance_offset ( ctx, offset_mm );
    return error_flag;
}

err_t lightranger10_set_distance_mode ( lightranger10_t *ctx, uint8_t distance_mode )
{
    err_t error_flag = LIGHTRANGER10_OK;
    if ( LIGHTRANGER10_DISTANCE_MODE_MEDIUM == distance_mode ) 
    {
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_RANGE_CFG_VCSEL_PERIOD_A, 
                                                      LIGHTRANGER10_DISTANCE_MEDIUM_RANGE_PERIOD_A );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_RANGE_CFG_VCSEL_PERIOD_B, 
                                                      LIGHTRANGER10_DISTANCE_MEDIUM_RANGE_PERIOD_B );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_RANGE_CFG_VALID_PHASE_HIGH, 
                                                      LIGHTRANGER10_DISTANCE_MEDIUM_RANGE_VAL_PH_H );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SD_CFG_WOI_SD0, 
                                                      LIGHTRANGER10_DISTANCE_MEDIUM_SD_WOI_SD0 );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SD_CFG_WOI_SD1, 
                                                      LIGHTRANGER10_DISTANCE_MEDIUM_SD_WOI_SD1 );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SD_CFG_INIT_PHASE_SD0, 
                                                      LIGHTRANGER10_DISTANCE_MEDIUM_SD_IN_PH_SD0 );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SD_CFG_INIT_PHASE_SD1, 
                                                      LIGHTRANGER10_DISTANCE_MEDIUM_SD_IN_PH_SD1 );
    }
    else if ( LIGHTRANGER10_DISTANCE_MODE_LONG == distance_mode ) 
    {
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_RANGE_CFG_VCSEL_PERIOD_A, 
                                                      LIGHTRANGER10_DISTANCE_LONG_RANGE_PERIOD_A );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_RANGE_CFG_VCSEL_PERIOD_B, 
                                                      LIGHTRANGER10_DISTANCE_LONG_RANGE_PERIOD_B );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_RANGE_CFG_VALID_PHASE_HIGH, 
                                                      LIGHTRANGER10_DISTANCE_LONG_RANGE_VAL_PH_H );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SD_CFG_WOI_SD0, 
                                                      LIGHTRANGER10_DISTANCE_LONG_SD_WOI_SD0 );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SD_CFG_WOI_SD1, 
                                                      LIGHTRANGER10_DISTANCE_LONG_SD_WOI_SD1 );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SD_CFG_INIT_PHASE_SD0, 
                                                      LIGHTRANGER10_DISTANCE_LONG_SD_IN_PH_SD0 );
        error_flag |= lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SD_CFG_INIT_PHASE_SD1, 
                                                      LIGHTRANGER10_DISTANCE_LONG_SD_IN_PH_SD1 );
    }
    else
    {
        error_flag = LIGHTRANGER10_ERROR;
    }
    return error_flag;
}

err_t lightranger10_start_measurement ( lightranger10_t *ctx )
{
    return lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SYSTEM_MODE_START, LIGHTRANGER10_RANGING_ENABLE );
}

err_t lightranger10_stop_measurement ( lightranger10_t *ctx )
{
    return lightranger10_write_byte ( ctx, LIGHTRANGER10_REG_SYSTEM_MODE_START, LIGHTRANGER10_RANGING_DISABLE );
}

err_t lightranger10_get_distance ( lightranger10_t *ctx, uint16_t *distance_mm )
{
    return lightranger10_read_word ( ctx, LIGHTRANGER10_REG_RESULT_RANGE_MM_SD0, distance_mm );
}

// ------------------------------------------------------------------------- END
