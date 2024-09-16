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
 * @file proximity21.c
 * @brief Proximity 21 Click Driver.
 */

#include "proximity21.h"

/**
 * @brief This buffer contains the VL53L4ED default configuration, 
 * refer to VL53L4ED ultra lite driver (ULD) API for more information.
 */
static const uint8_t proximity21_default_cfg_buf[ ] = 
{
    0x00, /* 0x2d : set bit 2 and 5 to 1 for fast plus mode (1MHz I2C), else don't touch */
    0x01, /* 0x2e : bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
    0x01, /* 0x2f : bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
    0x11, /* 0x30 : set bit 4 to 0 for active high interrupt and 1 for active low 
                    (bits 3:0 must be 0x1) */
    0x02, /* 0x31 : bit 1 = interrupt depending on the polarity */
    0x00, /* 0x32 : not user-modifiable */
    0x02, /* 0x33 : not user-modifiable */
    0x08, /* 0x34 : not user-modifiable */
    0x00, /* 0x35 : not user-modifiable */
    0x08, /* 0x36 : not user-modifiable */
    0x10, /* 0x37 : not user-modifiable */
    0x01, /* 0x38 : not user-modifiable */
    0x01, /* 0x39 : not user-modifiable */
    0x00, /* 0x3a : not user-modifiable */
    0x00, /* 0x3b : not user-modifiable */
    0x00, /* 0x3c : not user-modifiable */
    0x00, /* 0x3d : not user-modifiable */
    0xff, /* 0x3e : not user-modifiable */
    0x00, /* 0x3f : not user-modifiable */
    0x0F, /* 0x40 : not user-modifiable */
    0x00, /* 0x41 : not user-modifiable */
    0x00, /* 0x42 : not user-modifiable */
    0x00, /* 0x43 : not user-modifiable */
    0x00, /* 0x44 : not user-modifiable */
    0x00, /* 0x45 : not user-modifiable */
    0x20, /* 0x46 : interrupt configuration 0->level low detection, 1-> level high,
                    2-> Out of window, 3->In window, 0x20-> New sample ready, TBC */
    0x0b, /* 0x47 : not user-modifiable */
    0x00, /* 0x48 : not user-modifiable */
    0x00, /* 0x49 : not user-modifiable */
    0x02, /* 0x4a : not user-modifiable */
    0x14, /* 0x4b : not user-modifiable */
    0x21, /* 0x4c : not user-modifiable */
    0x00, /* 0x4d : not user-modifiable */
    0x00, /* 0x4e : not user-modifiable */
    0x05, /* 0x4f : not user-modifiable */
    0x00, /* 0x50 : not user-modifiable */
    0x00, /* 0x51 : not user-modifiable */
    0x00, /* 0x52 : not user-modifiable */
    0x00, /* 0x53 : not user-modifiable */
    0xc8, /* 0x54 : not user-modifiable */
    0x00, /* 0x55 : not user-modifiable */
    0x00, /* 0x56 : not user-modifiable */
    0x38, /* 0x57 : not user-modifiable */
    0xff, /* 0x58 : not user-modifiable */
    0x01, /* 0x59 : not user-modifiable */
    0x00, /* 0x5a : not user-modifiable */
    0x08, /* 0x5b : not user-modifiable */
    0x00, /* 0x5c : not user-modifiable */
    0x00, /* 0x5d : not user-modifiable */
    0x01, /* 0x5e : not user-modifiable */
    0xcc, /* 0x5f : not user-modifiable */
    0x07, /* 0x60 : not user-modifiable */
    0x01, /* 0x61 : not user-modifiable */
    0xf1, /* 0x62 : not user-modifiable */
    0x05, /* 0x63 : not user-modifiable */
    0x00, /* 0x64 : Sigma threshold MSB (mm in 14.2 format for MSB+LSB), default value 90 mm */
    0xa0, /* 0x65 : Sigma threshold LSB */
    0x00, /* 0x66 : Min count Rate MSB (MCPS in 9.7 format for MSB+LSB) */
    0x80, /* 0x67 : Min count Rate LSB */
    0x08, /* 0x68 : not user-modifiable */
    0x38, /* 0x69 : not user-modifiable */
    0x00, /* 0x6a : not user-modifiable */
    0x00, /* 0x6b : not user-modifiable */
    0x00, /* 0x6c : Intermeasurement period MSB, 32 bits register */
    0x00, /* 0x6d : Intermeasurement period */
    0x0f, /* 0x6e : Intermeasurement period */
    0x89, /* 0x6f : Intermeasurement period LSB */
    0x00, /* 0x70 : not user-modifiable */
    0x00, /* 0x71 : not user-modifiable */
    0x00, /* 0x72 : distance threshold high MSB (in mm, MSB+LSB) */
    0x00, /* 0x73 : distance threshold high LSB */
    0x00, /* 0x74 : distance threshold low MSB (in mm, MSB+LSB) */
    0x00, /* 0x75 : distance threshold low LSB */
    0x00, /* 0x76 : not user-modifiable */
    0x01, /* 0x77 : not user-modifiable */
    0x07, /* 0x78 : not user-modifiable */
    0x05, /* 0x79 : not user-modifiable */
    0x06, /* 0x7a : not user-modifiable */
    0x06, /* 0x7b : not user-modifiable */
    0x00, /* 0x7c : not user-modifiable */
    0x00, /* 0x7d : not user-modifiable */
    0x02, /* 0x7e : not user-modifiable */
    0xc7, /* 0x7f : not user-modifiable */
    0xff, /* 0x80 : not user-modifiable */
    0x9B, /* 0x81 : not user-modifiable */
    0x00, /* 0x82 : not user-modifiable */
    0x00, /* 0x83 : not user-modifiable */
    0x00, /* 0x84 : not user-modifiable */
    0x01, /* 0x85 : not user-modifiable */
    0x00, /* 0x86 : clear interrupt */
    0x00  /* 0x87 : start/stop ranging */
};

void proximity21_cfg_setup ( proximity21_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->xshut = HAL_PIN_NC;
    cfg->gpio1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY21_DEVICE_ADDRESS;
}

err_t proximity21_init ( proximity21_t *ctx, proximity21_cfg_t *cfg ) 
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

    digital_out_init( &ctx->xshut, cfg->xshut );

    digital_in_init( &ctx->gpio1, cfg->gpio1 );

    return I2C_MASTER_SUCCESS;
}

err_t proximity21_default_cfg ( proximity21_t *ctx ) 
{
    err_t error_flag = PROXIMITY21_OK;
    uint8_t tmp_data = 0;
    uint16_t timeout_cnt = 0;
    proximity21_disable_device ( ctx );
    Delay_100ms ( );
    proximity21_enable_device ( ctx );
    Delay_100ms ( );
    if ( PROXIMITY21_ERROR == proximity21_check_comm ( ctx ) )
    {
        return PROXIMITY21_ERROR;
    }
    // Wait for sensor boot indication
    while ( 0x03 != tmp_data ) 
    {
        error_flag |= proximity21_reg_read_byte ( ctx, PROXIMITY21_REG_FIRMWARE_SYSTEM_STATUS, &tmp_data );
        if ( ( ++timeout_cnt > 1000 ) || ( PROXIMITY21_ERROR == error_flag ) )
        {
            return PROXIMITY21_ERROR;
        }
        Delay_1ms ( );
    }

    // Load default configuration
    for ( uint8_t addr = 0x2D; addr <= 0x87; addr++ )
    {
        error_flag |= proximity21_reg_write_byte ( ctx, addr, proximity21_default_cfg_buf[ addr - 0x2D ] );
    }
    // Start VHV
    error_flag |= proximity21_reg_write_byte ( ctx, PROXIMITY21_REG_SYSTEM_START, 0x40 );

    // Wait data ready
    timeout_cnt = 0;
    while ( proximity21_get_gpio1_pin ( ctx ) ) 
    {
        if ( ++timeout_cnt > 1000 )
        {
            return PROXIMITY21_ERROR;
        }
        Delay_1ms ( );
    }
    error_flag |= proximity21_clear_interrupt ( ctx );
    error_flag |= proximity21_stop_ranging ( ctx );
    error_flag |= proximity21_reg_write_byte ( ctx, PROXIMITY21_REG_VHV_CONFIG_TIMEOUT, 0x09 );
    error_flag |= proximity21_reg_write_byte ( ctx, 0x000B, 0x00 );
    error_flag |= proximity21_reg_write_word ( ctx, 0x0024, 0x0500 );
    
    error_flag |= proximity21_set_range_timing ( ctx, 50, 200 );
    error_flag |= proximity21_start_ranging ( ctx );
    return error_flag;
}

err_t proximity21_reg_write_bytes ( proximity21_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len )
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

err_t proximity21_reg_read_bytes ( proximity21_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, data_out, len );
    return error_flag;
}

err_t proximity21_reg_write_byte ( proximity21_t *ctx, uint16_t reg, uint8_t data_in )
{
    return proximity21_reg_write_bytes ( ctx, reg, &data_in, 1 );
}

err_t proximity21_reg_read_byte ( proximity21_t *ctx, uint16_t reg, uint8_t *data_out )
{
    return proximity21_reg_read_bytes ( ctx, reg, data_out, 1 );
}

err_t proximity21_reg_write_word ( proximity21_t *ctx, uint16_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    return proximity21_reg_write_bytes ( ctx, reg, data_buf, 2 );
}

err_t proximity21_reg_read_word ( proximity21_t *ctx, uint16_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = proximity21_reg_read_bytes ( ctx, reg, data_buf, 2 );
    if ( ( PROXIMITY21_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t proximity21_reg_write_dword ( proximity21_t *ctx, uint16_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    return proximity21_reg_write_bytes ( ctx, reg, data_buf, 4 );
}

err_t proximity21_reg_read_dword ( proximity21_t *ctx, uint16_t reg, uint32_t *data_out )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = proximity21_reg_read_bytes ( ctx, reg, data_buf, 4 );
    if ( ( PROXIMITY21_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) | 
                    ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    }
    return error_flag;
}

void proximity21_disable_device ( proximity21_t *ctx )
{
    digital_out_low ( &ctx->xshut );
}

void proximity21_enable_device ( proximity21_t *ctx )
{
    digital_out_high ( &ctx->xshut );
}

uint8_t proximity21_get_gpio1_pin ( proximity21_t *ctx )
{
    return digital_in_read ( &ctx->gpio1 );
}

err_t proximity21_check_comm ( proximity21_t *ctx )
{
    uint16_t device_id = 0;
    if ( PROXIMITY21_OK == proximity21_reg_read_word ( ctx, PROXIMITY21_REG_MODEL_ID, &device_id ) )
    {
        if ( PROXIMITY21_DEVICE_ID == device_id )
        {
            return PROXIMITY21_OK;
        }
    }
    return PROXIMITY21_ERROR;
}

err_t proximity21_set_i2c_address ( proximity21_t *ctx, uint8_t address )
{
    if ( PROXIMITY21_OK == proximity21_reg_write_byte ( ctx, PROXIMITY21_REG_I2C_SLAVE_ADDRESS, address ) )
    {
        ctx->slave_address = address;
        return i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return PROXIMITY21_ERROR;
}

err_t proximity21_clear_interrupt ( proximity21_t *ctx )
{
    return proximity21_reg_write_byte ( ctx, PROXIMITY21_REG_SYSTEM_INTERRUPT_CLEAR, 0x01 );
}

err_t proximity21_start_ranging ( proximity21_t *ctx )
{
    uint32_t tmp_data = 0;
    err_t error_flag = proximity21_reg_read_dword ( ctx, PROXIMITY21_REG_INTERMEASUREMENT_MS, &tmp_data );
    if ( 0 == tmp_data ) 
    {
        // Sensor runs in continuous mode
        error_flag |= proximity21_reg_write_byte ( ctx, PROXIMITY21_REG_SYSTEM_START, 0x21 );
    }
    else 
    {
        // Sensor runs in autonomous mode
        error_flag |= proximity21_reg_write_byte ( ctx, PROXIMITY21_REG_SYSTEM_START, 0x40 );
    }
    return error_flag;
}

err_t proximity21_stop_ranging ( proximity21_t *ctx )
{
    return proximity21_reg_write_byte ( ctx, PROXIMITY21_REG_SYSTEM_START, 0x00 );
}

err_t proximity21_set_range_timing ( proximity21_t *ctx, uint32_t timing_budget_ms, uint32_t inter_measurement_ms )
{
    uint16_t clock_pll = 0, osc_frequency = 0, ms_byte = 0;
    uint32_t macro_period_us = 0, timing_budget_us = 0, ls_byte = 0, tmp_data = 0;
    float inter_measurement_factor = 1.055f;
    err_t error_flag = proximity21_reg_read_word ( ctx, 0x0006, &osc_frequency );
    if ( osc_frequency )
    {
        timing_budget_us = timing_budget_ms * 1000;
        macro_period_us = ( uint32_t ) ( 2304 * ( 0x40000000ul / osc_frequency ) ) >> 6;
    }
    else
    {
        return PROXIMITY21_ERROR;
    }
    // Timing budget check validity
    if ( ( timing_budget_ms < 10 ) || ( timing_budget_ms > 200 ) || ( PROXIMITY21_OK != error_flag ) )
    {
        return PROXIMITY21_ERROR;
    }
    else if ( !inter_measurement_ms )
    {
        // Sensor runs in continuous mode
        error_flag |= proximity21_reg_write_dword ( ctx, PROXIMITY21_REG_INTERMEASUREMENT_MS, 0 );
        timing_budget_us -= 2500;
    }
    else if ( inter_measurement_ms > timing_budget_ms )
    {
        error_flag |= proximity21_reg_read_word ( ctx, PROXIMITY21_REG_RESULT_OSC_CALIBRATE_VAL, &clock_pll );
        clock_pll &= 0x03FF;
        inter_measurement_factor = inter_measurement_factor * inter_measurement_ms * clock_pll;
        error_flag |= proximity21_reg_write_dword ( ctx, PROXIMITY21_REG_INTERMEASUREMENT_MS, ( uint32_t ) inter_measurement_factor );
        timing_budget_us -= 4300;
        timing_budget_us /= 2;
    }
    else
    {
        return PROXIMITY21_ERROR;
    }

    if ( PROXIMITY21_OK == error_flag )
    {
        ms_byte = 0;
        timing_budget_us <<= 12;
        tmp_data = macro_period_us * 16;
        ls_byte = ( ( timing_budget_us + ( tmp_data >> 7 ) ) / ( tmp_data >> 6 ) ) - 1;
        while ( ( ls_byte & 0xFFFFFF00ul ) > 0 )
        {
            ls_byte >>= 1;
            ms_byte++;
        }
        ms_byte = ( ( uint16_t ) ms_byte << 8 ) | ( ls_byte & 0xFF );
        error_flag |= proximity21_reg_write_word ( ctx, PROXIMITY21_REG_RANGE_CONFIG_A, ms_byte );

        ms_byte = 0;
        tmp_data = macro_period_us * 12;
        ls_byte = ( ( timing_budget_us + ( tmp_data >> 7 ) ) / ( tmp_data >> 6 ) ) - 1;
        while ( ( ls_byte & 0xFFFFFF00ul ) > 0 )
        {
            ls_byte >>= 1;
            ms_byte++;
        }
        ms_byte = ( ( uint16_t ) ms_byte << 8 ) | ( ls_byte & 0xFF );
        error_flag |= proximity21_reg_write_word ( ctx, PROXIMITY21_REG_RANGE_CONFIG_B, ms_byte );
    }
    return error_flag;
}

err_t proximity21_get_result ( proximity21_t *ctx, proximity21_data_t *results )
{
    uint16_t temp_16 = 0;
    uint8_t temp_8 = 0;
    uint8_t status_rtn[ 24 ] = 
    { 
        PROXIMITY21_RANGE_STATUS_ERROR, PROXIMITY21_RANGE_STATUS_ERROR, PROXIMITY21_RANGE_STATUS_ERROR, 
        PROXIMITY21_RANGE_STATUS_HW_FAIL, PROXIMITY21_RANGE_STATUS_SIGMA_LOW, PROXIMITY21_RANGE_STATUS_PHASE_LIMIT, 
        PROXIMITY21_RANGE_STATUS_SIGMA_HIGH, PROXIMITY21_RANGE_STATUS_PHASE_NO_MATCH, PROXIMITY21_RANGE_STATUS_DISTANCE_LOW, 
        PROXIMITY21_RANGE_STATUS_VALID, PROXIMITY21_RANGE_STATUS_ERROR, PROXIMITY21_RANGE_STATUS_ERROR, 
        PROXIMITY21_RANGE_STATUS_CROSSTALK_FAIL, PROXIMITY21_RANGE_STATUS_ERROR, PROXIMITY21_RANGE_STATUS_ERROR,
        PROXIMITY21_RANGE_STATUS_ERROR, PROXIMITY21_RANGE_STATUS_ERROR, PROXIMITY21_RANGE_STATUS_ERROR, 
        PROXIMITY21_RANGE_STATUS_INTERRUPT_ERROR, PROXIMITY21_RANGE_STATUS_WRAP_CHECK, PROXIMITY21_RANGE_STATUS_ERROR,
        PROXIMITY21_RANGE_STATUS_ERROR, PROXIMITY21_RANGE_STATUS_MERGED_TARGET, PROXIMITY21_RANGE_STATUS_SIGNAL_TOO_LOW 
    };
    err_t error_flag = proximity21_reg_read_byte ( ctx, PROXIMITY21_REG_RESULT_RANGE_STATUS, &temp_8 );
    temp_8 &= 0x1F;
    if ( temp_8 < 24 )
    {
        temp_8 = status_rtn[ temp_8 ];
    }
    results->range_status = temp_8;
    if ( PROXIMITY21_RANGE_STATUS_VALID != results->range_status )
    {
        results->number_of_spad = 0;
        results->signal_rate_kcps = 0;
        results->ambient_rate_kcps = 0;
        results->sigma_mm = 0;
        results->distance_mm = 0;
        results->signal_per_spad_kcps = 0;
        results->ambient_per_spad_kcps = 0;
    }
    else
    {
        error_flag |= proximity21_reg_read_word ( ctx, PROXIMITY21_REG_RESULT_SPAD_NB, &temp_16 );
        results->number_of_spad = temp_16 / 256;

        error_flag |= proximity21_reg_read_word ( ctx, PROXIMITY21_REG_RESULT_SIGNAL_RATE, &temp_16 );
        results->signal_rate_kcps = temp_16 * 8;

        error_flag |= proximity21_reg_read_word ( ctx, PROXIMITY21_REG_RESULT_AMBIENT_RATE, &temp_16 );
        results->ambient_rate_kcps = temp_16 * 8;

        error_flag |= proximity21_reg_read_word ( ctx, PROXIMITY21_REG_RESULT_SIGMA, &temp_16 );
        results->sigma_mm = temp_16 / 4;

        error_flag |= proximity21_reg_read_word ( ctx, PROXIMITY21_REG_RESULT_DISTANCE, &temp_16 );
        results->distance_mm = temp_16;

        if ( results->number_of_spad )
        {
            results->signal_per_spad_kcps = results->signal_rate_kcps / results->number_of_spad;
        }
        if ( results->number_of_spad )
        {
            results->ambient_per_spad_kcps = results->ambient_rate_kcps / results->number_of_spad;
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
