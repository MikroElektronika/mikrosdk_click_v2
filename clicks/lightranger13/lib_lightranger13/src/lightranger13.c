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
 * @file lightranger13.c
 * @brief LightRanger 13 Click Driver.
 */

#include "lightranger13.h"

void lightranger13_cfg_setup ( lightranger13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHTRANGER13_DEVICE_ADDRESS;
}

err_t lightranger13_init ( lightranger13_t *ctx, lightranger13_cfg_t *cfg ) 
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
    digital_out_low ( &ctx->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t lightranger13_default_cfg ( lightranger13_t *ctx ) 
{
    err_t error_flag = LIGHTRANGER13_OK;
    if ( LIGHTRANGER13_OK != lightranger13_power_up ( ctx ) )
    {
        return LIGHTRANGER13_ERROR;
    }
    error_flag |= lightranger13_read_info ( ctx );

    // Enable results interrupt
    error_flag |= lightranger13_write_reg ( ctx, LIGHTRANGER13_REG_INT_ENAB, LIGHTRANGER13_INTERRUPT_RESULT );

    // Default factory calibration setting
    ctx->factory_calib[ 0 ] = LIGHTRANGER13_FACTORY_CALIB_0; // The factory data ID. Must be 0x02, or the state data will be discarded
    ctx->factory_calib[ 1 ] = LIGHTRANGER13_FACTORY_CALIB_1; // Reserved
    ctx->factory_calib[ 2 ] = LIGHTRANGER13_FACTORY_CALIB_2; // Reserved
    ctx->factory_calib[ 3 ] = LIGHTRANGER13_FACTORY_CALIB_3; // The first crosstalk bin position as UQ6.6 (lower 8 bits)
    ctx->factory_calib[ 4 ] = LIGHTRANGER13_FACTORY_CALIB_4; // The first crosstalk bin position as UQ6.6 (upper 4 bits)
    ctx->factory_calib[ 5 ] = LIGHTRANGER13_FACTORY_CALIB_5; // The crosstalk bin position delta to bin pos 0 as Q2.6
    ctx->factory_calib[ 6 ] = LIGHTRANGER13_FACTORY_CALIB_6; // The crosstalk bin position delta to bin pos 0 as Q2.6
    ctx->factory_calib[ 7 ] = LIGHTRANGER13_FACTORY_CALIB_7; // The crosstalk bin position delta to bin pos 0 as Q2.6
    ctx->factory_calib[ 8 ] = LIGHTRANGER13_FACTORY_CALIB_8; // The crosstalk bin position delta to bin pos 0 as Q2.6 (upper 8 bits)
    ctx->factory_calib[ 9 ] = LIGHTRANGER13_FACTORY_CALIB_9; // The crosstalk bin position delta to bin pos 0 as Q2.6
    ctx->factory_calib[ 10 ] = LIGHTRANGER13_FACTORY_CALIB_10; // The crosstalk bin position delta to bin pos 0 as Q2.6
    ctx->factory_calib[ 11 ] = LIGHTRANGER13_FACTORY_CALIB_11; // The crosstalk bin position delta to bin pos 0 as Q2.6
    ctx->factory_calib[ 12 ] = LIGHTRANGER13_FACTORY_CALIB_12; // The crosstalk bin position delta to bin pos 0 as Q2.6 (upper 3 bits)
    ctx->factory_calib[ 13 ] = LIGHTRANGER13_FACTORY_CALIB_13; // The optical system offset
    
    // Default state data setting
    ctx->state_data[ 0 ] = LIGHTRANGER13_STATE_DATA_0; // The state data ID. Must be 0x02, or the state data will be discarded
    ctx->state_data[ 1 ] = LIGHTRANGER13_STATE_DATA_1; // The last selected breakdown voltage value
    ctx->state_data[ 2 ] = LIGHTRANGER13_STATE_DATA_2; // The average optical reference bin position in bins (UQ7.9)
    ctx->state_data[ 3 ] = LIGHTRANGER13_STATE_DATA_3; // The average optical reference bin position in bins (UQ7.9)
    ctx->state_data[ 4 ] = LIGHTRANGER13_STATE_DATA_4; // The last BDV calibration temperature in degree C
    ctx->state_data[ 5 ] = LIGHTRANGER13_STATE_DATA_5; // The temperature at which the measurement needs to run with 20MHz due to a weak VCSEL driver
    ctx->state_data[ 6 ] = LIGHTRANGER13_STATE_DATA_6; // The TDC bin width electrical calibration value in Q9.
    ctx->state_data[ 7 ] = LIGHTRANGER13_STATE_DATA_7; // The TDC bin width electrical calibration value in Q9.
    ctx->state_data[ 8 ] = LIGHTRANGER13_STATE_DATA_8; // The TDC bin width electrical calibration value in Q9.
    ctx->state_data[ 9 ] = LIGHTRANGER13_STATE_DATA_9; // The TDC bin width electrical calibration value in Q9.
    ctx->state_data[ 10 ] = LIGHTRANGER13_STATE_DATA_10; // The TDC bin width electrical calibration value in Q9.

    // Default measurement config setting
    ctx->meas_cfg.ss_spad_chg_pump = LIGHTRANGER13_MEAS_CFG_SS_SPAD_CHG_PUMP;
    ctx->meas_cfg.ss_vcsel_chg_pump = LIGHTRANGER13_MEAS_CFG_SS_VCSEL_CHG_PUMP;
    ctx->meas_cfg.calib_state = LIGHTRANGER13_MEAS_CFG_CALIB_STATE;
    ctx->meas_cfg.algo = LIGHTRANGER13_MEAS_CFG_ALGO;
    ctx->meas_cfg.gpio_ctrl = LIGHTRANGER13_MEAS_CFG_GPIO_CTRL;
    ctx->meas_cfg.dax_delay_100us = LIGHTRANGER13_MEAS_CFG_DAX_DELAY_100US;
    ctx->meas_cfg.snr = LIGHTRANGER13_MEAS_CFG_SNR;
    ctx->meas_cfg.rep_period_ms = LIGHTRANGER13_MEAS_CFG_REP_PERIOD_MS;
    ctx->meas_cfg.k_iters = LIGHTRANGER13_MEAS_CFG_K_ITERS;

    return error_flag;
}

err_t lightranger13_write_regs ( lightranger13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t lightranger13_read_regs ( lightranger13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t lightranger13_write_reg ( lightranger13_t *ctx, uint8_t reg, uint8_t data_in )
{
    return lightranger13_write_regs ( ctx, reg, &data_in, 1 );
}

err_t lightranger13_read_reg ( lightranger13_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return lightranger13_read_regs ( ctx, reg, data_out, 1 );
}

err_t lightranger13_send_cmd ( lightranger13_t *ctx, uint8_t cmd, uint8_t *payload, 
                               uint8_t payload_len, uint16_t timeout_ms )
{
    err_t error_flag = LIGHTRANGER13_OK;
    uint8_t data_buf[ 11 ] = { 0 };
    uint16_t timeout_cnt = 0;
    if ( ( payload_len > 10 ) || 
         ( ( payload_len > 0 ) && ( NULL == payload ) ) )
    {
        return LIGHTRANGER13_ERROR;
    }
    if ( payload_len > 0 )
    {
        memcpy( data_buf, payload, payload_len );
    }
    data_buf[ payload_len ] = cmd;
    error_flag |= lightranger13_write_regs ( ctx, LIGHTRANGER13_REG_APP0_CMD - payload_len, data_buf, payload_len + 1 );
    error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APP0_CMD, data_buf, 2 );
    while ( ( LIGHTRANGER13_OK == error_flag ) && 
            ( ( LIGHTRANGER13_STATUS_IDLE != data_buf[ 0 ] ) || ( cmd != data_buf[ 1 ] ) ) )
    {
        Delay_1ms ( );
        if ( ( ++timeout_cnt > timeout_ms ) && ( LIGHTRANGER13_TIMEOUT_INFINITE != timeout_ms ) )
        {
            error_flag |= LIGHTRANGER13_ERROR;
        }
        else
        {
            error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APP0_CMD, data_buf, 2 );
        }
    }
    return error_flag;
}

err_t lightranger13_wait_reg_state ( lightranger13_t *ctx, uint8_t reg, uint8_t mask, 
                                     uint8_t state, uint16_t timeout_ms )
{
    err_t error_flag = LIGHTRANGER13_OK;
    uint8_t reg_data = 0;
    uint16_t timeout_cnt = 0;
    error_flag |= lightranger13_read_reg ( ctx, reg, &reg_data );
    while ( ( LIGHTRANGER13_OK == error_flag ) && 
            ( state != ( reg_data & mask ) ) )
    {
        Delay_1ms ( );
        if ( ( ++timeout_cnt > timeout_ms ) && ( LIGHTRANGER13_TIMEOUT_INFINITE != timeout_ms ) )
        {
            error_flag |= LIGHTRANGER13_ERROR;
        }
        else
        {
            error_flag |= lightranger13_read_reg ( ctx, reg, &reg_data );
        }
    }
    return error_flag;
}

void lightranger13_enable_device ( lightranger13_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void lightranger13_disable_device ( lightranger13_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t lightranger13_get_int_pin ( lightranger13_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t lightranger13_power_up ( lightranger13_t *ctx )
{
    err_t error_flag = LIGHTRANGER13_OK;
    uint8_t timeout_cnt = 0;
    uint8_t reg_data = 0;
    // Pull the enable line high
    lightranger13_enable_device ( ctx );
    // Wait for at least 1.6ms (bootloader startup time)
    Delay_1ms ( );
    Delay_1ms ( );
    // Wait for the bootloader sleep
    error_flag |= lightranger13_wait_reg_state ( ctx, LIGHTRANGER13_REG_ENABLE, LIGHTRANGER13_MASK_ALL, 
                                                 LIGHTRANGER13_ENABLE_STANDBY, LIGHTRANGER13_TIMEOUT_1MS );
    if ( LIGHTRANGER13_OK == error_flag )
    {
        // Set PON bit
        reg_data = LIGHTRANGER13_ENABLE_PON;
        error_flag |= lightranger13_write_reg ( ctx, LIGHTRANGER13_REG_ENABLE, reg_data );
    }

    if ( LIGHTRANGER13_OK == error_flag )
    {
        // Wait for the bootloader ready
        error_flag |= lightranger13_wait_reg_state ( ctx, LIGHTRANGER13_REG_ENABLE, LIGHTRANGER13_MASK_ALL, 
                                                    ( LIGHTRANGER13_ENABLE_CPU_READY | LIGHTRANGER13_ENABLE_PON ), 
                                                    LIGHTRANGER13_TIMEOUT_2MS );
    }

    if ( LIGHTRANGER13_OK == error_flag )
    {
        // Request the ROM application firmware (App0) start
        reg_data = LIGHTRANGER13_APPID_APP0;
        error_flag |= lightranger13_write_reg ( ctx, LIGHTRANGER13_REG_APPREQID, reg_data );
    }

    if ( LIGHTRANGER13_OK == error_flag )
    {
        // Wait for the application
        error_flag |= lightranger13_wait_reg_state ( ctx, LIGHTRANGER13_REG_APPID, LIGHTRANGER13_MASK_ALL, 
                                                     LIGHTRANGER13_APPID_APP0, LIGHTRANGER13_TIMEOUT_1MS );
    }
    return error_flag;
}

err_t lightranger13_read_info ( lightranger13_t *ctx )
{
    err_t error_flag = LIGHTRANGER13_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t timeout_cnt = 0;
    error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_ID, ctx->info.chip_ver, 2 );
    error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APPID, ctx->info.app_ver, 2 );
    if ( ( LIGHTRANGER13_OK == error_flag ) && ( LIGHTRANGER13_APPID_APP0 == ctx->info.app_ver[ 0 ] ) )
    {
        error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APP0_APPREV_MINOR, &ctx->info.app_ver[ 2 ], 2 );
        error_flag |= lightranger13_send_cmd ( ctx, LIGHTRANGER13_CMD_READ_SERIAL_NUMBER, NULL, 0, LIGHTRANGER13_TIMEOUT_1MS );
        if ( LIGHTRANGER13_OK == error_flag )
        {
            // Check if serial number is in register contents
            error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APP0_REGISTER_CONTENTS, data_buf, 1 );
            if ( ( LIGHTRANGER13_OK == error_flag ) && ( LIGHTRANGER13_CMD_READ_SERIAL_NUMBER == data_buf[ 0 ] ) )
            {
                // Read serial number
                error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APP0_ODR_STATE_DATA_0, data_buf, 4 );
                ctx->info.serial_num = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                                       ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
            }
            else
            {
                error_flag = LIGHTRANGER13_ERROR;
            }
        }
    }
    return error_flag;
}

err_t lightranger13_clear_interrupts ( lightranger13_t *ctx )
{
    err_t error_flag = LIGHTRANGER13_OK;
    uint8_t int_status = 0;
    error_flag |= lightranger13_read_reg ( ctx, LIGHTRANGER13_REG_INT_STATUS, &int_status );
    error_flag |= lightranger13_write_reg ( ctx, LIGHTRANGER13_REG_INT_STATUS, int_status );
    return error_flag;
}

err_t lightranger13_factory_calib ( lightranger13_t *ctx )
{
    err_t error_flag = LIGHTRANGER13_OK;
    uint16_t timeout_cnt = 0;
    uint16_t k_iters_save = ctx->meas_cfg.k_iters;
    uint16_t calib_state_save = ctx->meas_cfg.calib_state;
    uint8_t data_buf[ 14 ] = { 0 };
    ctx->meas_cfg.k_iters = LIGHTRANGER13_FACTORY_CALIB_K_ITERS;
    ctx->meas_cfg.calib_state = LIGHTRANGER13_FACTORY_CALIB_STATE;
    error_flag |= lightranger13_clear_interrupts ( ctx );
    data_buf[ 0 ] = ctx->meas_cfg.ss_spad_chg_pump;
    data_buf[ 1 ] = ctx->meas_cfg.ss_vcsel_chg_pump;
    data_buf[ 2 ] = ctx->meas_cfg.calib_state;
    data_buf[ 3 ] = ctx->meas_cfg.algo;
    data_buf[ 4 ] = ctx->meas_cfg.gpio_ctrl;
    data_buf[ 5 ] = ctx->meas_cfg.dax_delay_100us;
    data_buf[ 6 ] = ctx->meas_cfg.snr;
    data_buf[ 7 ] = ctx->meas_cfg.rep_period_ms;
    data_buf[ 8 ] = ( uint8_t ) ( ctx->meas_cfg.k_iters & 0xFF );
    data_buf[ 9 ] = ( uint8_t ) ( ( ctx->meas_cfg.k_iters >> 8 ) & 0xFF );
    error_flag |= lightranger13_send_cmd ( ctx, LIGHTRANGER13_CMD_CUSTOMER_FACTORY_CALIB, data_buf, 10, LIGHTRANGER13_TIMEOUT_5MS );

    while ( lightranger13_get_int_pin ( ctx ) && ( LIGHTRANGER13_OK == error_flag ) )
    {
        if ( ++timeout_cnt > LIGHTRANGER13_TIMEOUT_5S )
        {
            error_flag = LIGHTRANGER13_ERROR;
        }
        Delay_1ms ( );
    }

    if ( LIGHTRANGER13_OK == error_flag )
    {
        error_flag |= lightranger13_clear_interrupts ( ctx );
    }
    if ( LIGHTRANGER13_OK == error_flag )
    {
        error_flag |= lightranger13_wait_reg_state ( ctx, LIGHTRANGER13_REG_APP0_REGISTER_CONTENTS, LIGHTRANGER13_MASK_ALL, 
                                                     LIGHTRANGER13_REGISTER_CONTENTS_CALIBRATION, LIGHTRANGER13_TIMEOUT_150MS );
    }
    if ( LIGHTRANGER13_OK == error_flag )
    {
        error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_0, data_buf, 14 );
    }
    if ( LIGHTRANGER13_OK == error_flag )
    {
        memcpy ( ctx->factory_calib, data_buf, 14 );
    }
    ctx->meas_cfg.k_iters = k_iters_save;
    ctx->meas_cfg.calib_state = calib_state_save;
    return error_flag;
}

err_t lightranger13_set_threshold ( lightranger13_t *ctx, uint16_t t_low, uint16_t t_high, uint8_t persistance )
{
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = persistance;
    data_buf[ 1 ] = ( uint8_t ) ( t_low & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( t_low >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( t_high & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( t_high >> 8 ) & 0xFF );
    return lightranger13_send_cmd ( ctx, LIGHTRANGER13_CMD_WRITE_ADD_CFG, data_buf, 5, LIGHTRANGER13_TIMEOUT_150MS );
}

err_t lightranger13_start_measurement ( lightranger13_t *ctx )
{
    err_t error_flag = LIGHTRANGER13_OK;
    uint8_t data_buf[ 25 ] = { 0 };
    uint8_t cfg_len = 0;
    if ( ctx->meas_cfg.calib_state & ( LIGHTRANGER13_MEAS_CFG_7_FACTORY_CAL_MASK | LIGHTRANGER13_MEAS_CFG_7_ALG_STATE_MASK ) )
    {
        memcpy ( &data_buf[ 0 ], ctx->factory_calib, 14 );
        cfg_len = 14;
    }
    if ( ctx->meas_cfg.calib_state & LIGHTRANGER13_MEAS_CFG_7_ALG_STATE_MASK )
    {
        memcpy ( &data_buf[ 14 ], ctx->state_data, 11 );
        cfg_len = 25;
    }
    if ( cfg_len > 0 )
    {
        error_flag |= lightranger13_write_regs ( ctx, LIGHTRANGER13_REG_APP0_CAD_FACTORY_CALIB_0, data_buf, 25 );
    }
    data_buf[ 0 ] = ctx->meas_cfg.ss_spad_chg_pump;
    data_buf[ 1 ] = ctx->meas_cfg.ss_vcsel_chg_pump;
    data_buf[ 2 ] = ctx->meas_cfg.calib_state;
    data_buf[ 3 ] = ctx->meas_cfg.algo;
    data_buf[ 4 ] = ctx->meas_cfg.gpio_ctrl;
    data_buf[ 5 ] = ctx->meas_cfg.dax_delay_100us;
    data_buf[ 6 ] = ctx->meas_cfg.snr;
    data_buf[ 7 ] = ctx->meas_cfg.rep_period_ms;
    data_buf[ 8 ] = ( uint8_t ) ( ctx->meas_cfg.k_iters & 0xFF );
    data_buf[ 9 ] = ( uint8_t ) ( ( ctx->meas_cfg.k_iters >> 8 ) & 0xFF );
    error_flag |= lightranger13_send_cmd ( ctx, LIGHTRANGER13_CMD_START_MEASUREMENT, data_buf, 10, LIGHTRANGER13_TIMEOUT_5MS );
    return error_flag;
}

err_t lightranger13_stop_measurement ( lightranger13_t *ctx )
{
    return lightranger13_send_cmd ( ctx, LIGHTRANGER13_CMD_STOP_COMMAND, NULL, 0, LIGHTRANGER13_TIMEOUT_150MS );
}

err_t lightranger13_read_result ( lightranger13_t *ctx, lightranger13_meas_result_t *result )
{
    err_t error_flag = LIGHTRANGER13_OK;
    uint8_t data_buf[ 30 ] = { 0 };
    error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APP0_STATUS, data_buf, 2 );
    if ( ( LIGHTRANGER13_STATUS_IDLE != data_buf[ 0 ] ) || ( LIGHTRANGER13_REGISTER_CONTENTS_MEASUREMENT != data_buf[ 1 ] ) )
    {
        error_flag |= LIGHTRANGER13_ERROR;
    }
    if ( LIGHTRANGER13_OK == error_flag )
    {
        error_flag |= lightranger13_read_regs ( ctx, LIGHTRANGER13_REG_APP0_ODR_RESULT_NUMBER, data_buf, 30 );
    }
    if ( LIGHTRANGER13_OK == error_flag )
    {
        result->result_num = data_buf[ 0 ];
        result->result_info = data_buf[ 1 ];
        result->dist_peak = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        result->sys_clock = ( ( uint32_t ) data_buf[ 7 ] << 24 ) | ( ( uint32_t ) data_buf[ 6 ] << 16 ) | 
                            ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
        memcpy ( result->state_data, &data_buf[ 8 ], 11 );
        result->temperature = data_buf[ 19 ];
        result->ref_hits = ( ( uint32_t ) data_buf[ 23 ] << 24 ) | ( ( uint32_t ) data_buf[ 22 ] << 16 ) | 
                           ( ( uint16_t ) data_buf[ 21 ] << 8 ) | data_buf[ 20 ];
        result->object_hits = ( ( uint32_t ) data_buf[ 27 ] << 24 ) | ( ( uint32_t ) data_buf[ 26 ] << 16 ) | 
                              ( ( uint16_t ) data_buf[ 25 ] << 8 ) | data_buf[ 24 ];
        result->xtalk = ( ( uint16_t ) data_buf[ 29 ] << 8 ) | data_buf[ 28 ];
        memcpy ( ctx->state_data, result->state_data, 11 );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
