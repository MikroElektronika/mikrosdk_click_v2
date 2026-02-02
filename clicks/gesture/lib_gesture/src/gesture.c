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
 * @file gesture.c
 * @brief Gesture Click Driver.
 */

#include "gesture.h"

void gesture_cfg_setup ( gesture_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->osc_en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GESTURE_DEVICE_ADDRESS;
}

err_t gesture_init ( gesture_t *ctx, gesture_cfg_t *cfg ) 
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

    digital_out_init( &ctx->osc_en, cfg->osc_en );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t gesture_default_cfg ( gesture_t *ctx ) 
{
    err_t error_flag = GESTURE_OK;
    gesture_spi_osc_disable ( ctx );
    Delay_100ms ( );
    if ( GESTURE_OK != gesture_check_communication ( ctx ) )
    {
        Delay_100ms ( );
        if ( GESTURE_OK != gesture_check_communication ( ctx ) )
        {
            return GESTURE_ERROR;
        }
    }

    // Recommended initial settings for gesture mode from datasheet
    error_flag |= gesture_bank_sel ( ctx, GESTURE_BANK_SELECT_0 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_CURSOR_CLAMP_LEFT, 0x07 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_CURSOR_CLAMP_RIGHT, 0x17 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_CURSOR_CLAMP_UP, 0x06 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_INT2_EN, GESTURE_INT2_WAVE );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_AE_LED_OFF_UB, 0x2D );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_AE_LED_OFF_LB, 0x0F );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_AE_EXPOSURE_UB_L, 0x3C );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_AE_EXPOSURE_UB_H, 0x00 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_AE_EXPOSURE_LB_L, 0x1E );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_AE_GAIN_UB, 0x20 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_MANUAL, 0x10 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_5E, 0x10 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_60, 0x27 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_GPIO_01, 0x42 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_GPIO_23, 0x44 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_INT, 0x04 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_CURSOR_OBJECT_SIZE_TH, 0x01 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_NO_MOTION_COUNT_THD, 0x06 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_Z_DIR_THD, 0x0A );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_Z_DIR_XY_THD, 0x0C );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_Z_DIR_ANGLE_THD, 0x05 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_ROTATE_XY_THD, 0x14 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_FILTER, 0x3F );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_FILTER_IMAGE, 0x19 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_Y_TO_Z_SUM, 0x19 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_Y_TO_Z_FACTOR, 0x0B );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_FILTER_LEN, 0x03 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_WAVE_THD, 0x64 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B0_ABORT_COUNT_THD, 0x21 );
    error_flag |= gesture_bank_sel ( ctx, GESTURE_BANK_SELECT_1 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_CMD_H_START, 0x0F );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_CMD_V_START, 0x10 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_CMD_HV, 0x02 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_LENS_SHADING_COMP_EN_H, 0x01 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_OFFSET_Y, 0x39 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_LSC, 0x7F );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_LSFT, 0x08 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_3E, 0xFF );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_5E, 0x3D );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_IDLE_TIME_L, 0x96 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_IDLE_TIME_SLEEP_1_L, 0x97 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_IDLE_TIME_SLEEP_2_L, 0xCD );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_IDLE_TIME_SLEEP_2_H, 0x01 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_OBJECT_TIME_2_L, 0x2C );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_OBJECT_TIME_2_H, 0x01 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_TG_EN_H, 0x01 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_AUTO_SLEEP_MODE, 0x35 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_WAKE_UP_SIG_SEL, 0x00 );
    error_flag |= gesture_write_reg ( ctx, GESTURE_REG_B1_SRAM_READ_EN_H, 0x01 );
    error_flag |= gesture_bank_sel ( ctx, GESTURE_BANK_SELECT_0 );

    return error_flag;
}

err_t gesture_write_regs ( gesture_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t gesture_read_regs ( gesture_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t gesture_write_reg ( gesture_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return gesture_write_regs( ctx, reg, &data_in, 1 );
}

err_t gesture_read_reg ( gesture_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return gesture_read_regs( ctx, reg, data_out, 1 );
}

void gesture_spi_osc_enable ( gesture_t *ctx )
{
    digital_out_high ( &ctx->osc_en );
}

void gesture_spi_osc_disable ( gesture_t *ctx )
{
    digital_out_low ( &ctx->osc_en );
}

uint8_t gesture_get_int_pin ( gesture_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t gesture_check_communication ( gesture_t *ctx )
{
    uint8_t part_id[ 2 ] = { 0 };
    if ( GESTURE_OK == gesture_read_regs ( ctx, GESTURE_REG_B0_PART_ID_L, part_id, 2 ) )
    {
        if ( ( GESTURE_PART_ID_L == part_id[ 0 ] ) && ( GESTURE_PART_ID_H == part_id[ 1 ] ) )
        {
            return GESTURE_OK;
        }
    }
    return GESTURE_ERROR;
}

err_t gesture_bank_sel ( gesture_t *ctx, uint8_t bank_sel )
{
    if ( bank_sel > GESTURE_BANK_SELECT_1 )
    {
        return GESTURE_ERROR;
    }
    return gesture_write_reg ( ctx, GESTURE_REG_BANK_SELECT, bank_sel );
}

err_t gesture_get_detected_gesture ( gesture_t *ctx, uint8_t *gesture, uint32_t timeout )
{
    uint8_t int_flag[ 2 ] = { 0 };
    uint32_t timeout_cnt = 0;
    while ( gesture_get_int_pin ( ctx ) )
    {
        if ( ( ++timeout_cnt > timeout ) && ( GESTURE_TIMEOUT_INFINITE != timeout ) )
        {
            return GESTURE_ERROR_TIMEOUT;
        }
        Delay_1ms ( );
    }
    
    if ( GESTURE_OK != gesture_read_regs ( ctx, GESTURE_REG_B0_INT1_FLAG, int_flag, 2 ) )
    {
        return GESTURE_ERROR;
    }

    if ( int_flag[ 0 ] & GESTURE_INT1_UP )
    {
        *gesture = GESTURE_UP;
    }
    else if ( int_flag[ 0 ] & GESTURE_INT1_DOWN )
    {
        *gesture = GESTURE_DOWN;
    }
    else if ( int_flag[ 0 ] & GESTURE_INT1_LEFT )
    {
        *gesture = GESTURE_LEFT;
    }
    else if ( int_flag[ 0 ] & GESTURE_INT1_RIGHT )
    {
        *gesture = GESTURE_RIGHT;
    }
    else if ( int_flag[ 0 ] & GESTURE_INT1_FORWARD )
    {
        *gesture = GESTURE_FORWARD;
    }
    else if ( int_flag[ 0 ] & GESTURE_INT1_BACKWARD )
    {
        *gesture = GESTURE_BACKWARD;
    }
    else if ( int_flag[ 0 ] & GESTURE_INT1_CLOCKWISE )
    {
        *gesture = GESTURE_CLOCKWISE;
    }
    else if ( int_flag[ 0 ] & GESTURE_INT1_COUNTER_CLOCKWISE )
    {
        *gesture = GESTURE_COUNTER_CLOCKWISE;
    }
    else if ( int_flag[ 1 ] & GESTURE_INT2_WAVE )
    {
        *gesture = GESTURE_WAVE;
    }
    else
    {
        *gesture = GESTURE_UNKNOWN;
    }
    return GESTURE_OK;
}

// ------------------------------------------------------------------------- END
