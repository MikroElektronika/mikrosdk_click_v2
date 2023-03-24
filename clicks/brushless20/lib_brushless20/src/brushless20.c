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
 * @file brushless20.c
 * @brief Brushless 20 Click Driver.
 */

#include "brushless20.h"

void brushless20_cfg_setup ( brushless20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->slp = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = BRUSHLESS20_DEVICE_ADDRESS_A1A0_00;
}

err_t brushless20_init ( brushless20_t *ctx, brushless20_cfg_t *cfg ) 
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
    digital_out_init( &ctx->slp, cfg->slp );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t brushless20_default_cfg ( brushless20_t *ctx ) 
{
    brushless20_reset_port_expander ( ctx );
    brushless20_exit_sleep_mode ( ctx );
    // Configure FAULT pin as INPUT, others as OUTPUT
    return brushless20_write_register ( ctx, BRUSHLESS20_REG_CONFIG, BRUSHLESS20_DEFAULT_CONFIG );
}

err_t brushless20_write_register ( brushless20_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t brushless20_read_register ( brushless20_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t brushless20_set_pins ( brushless20_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in, data_out;
    err_t error_flag = brushless20_read_register ( ctx, BRUSHLESS20_REG_OUTPUT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        error_flag |= brushless20_write_register ( ctx, BRUSHLESS20_REG_OUTPUT, data_in );
    }
    return error_flag;
}

err_t brushless20_get_fault_pin ( brushless20_t *ctx )
{
    uint8_t data_out;
    if ( BRUSHLESS20_OK == brushless20_read_register ( ctx, BRUSHLESS20_REG_INPUT, &data_out ) )
    {
        return ( err_t ) ( ( data_out & BRUSHLESS20_FLT_PIN ) >> 7 );
    }
    return BRUSHLESS20_ERROR;
}

void brushless20_reset_port_expander ( brushless20_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void brushless20_set_rst_pin ( brushless20_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void brushless20_enter_sleep_mode ( brushless20_t *ctx )
{
    digital_out_low ( &ctx->slp );
}

void brushless20_exit_sleep_mode ( brushless20_t *ctx )
{
    digital_out_high ( &ctx->slp );
}

uint8_t brushless20_get_int_pin ( brushless20_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t brushless20_set_trapezoidal_com_state ( brushless20_t *ctx, uint8_t state )
{
    uint8_t set_mask, clr_mask;
    switch ( state )
    {
        case BRUSHLESS20_TR_COM_STATE_COAST:
        {
            set_mask = BRUSHLESS20_NONE_PIN; 
            clr_mask = BRUSHLESS20_EN1_PIN | BRUSHLESS20_EN2_PIN | BRUSHLESS20_EN3_PIN;
            break;
        }
        case BRUSHLESS20_TR_COM_STATE_1:
        {
            set_mask = BRUSHLESS20_EN2_PIN | BRUSHLESS20_IN2_PIN | BRUSHLESS20_EN3_PIN;
            clr_mask = BRUSHLESS20_EN1_PIN | BRUSHLESS20_IN3_PIN;
            break;
        }
        case BRUSHLESS20_TR_COM_STATE_2:
        {
            set_mask = BRUSHLESS20_EN1_PIN | BRUSHLESS20_IN1_PIN | BRUSHLESS20_EN3_PIN;
            clr_mask = BRUSHLESS20_EN2_PIN | BRUSHLESS20_IN3_PIN;
            break;
        }
        case BRUSHLESS20_TR_COM_STATE_3:
        {
            set_mask = BRUSHLESS20_EN1_PIN | BRUSHLESS20_IN1_PIN | BRUSHLESS20_EN2_PIN;
            clr_mask = BRUSHLESS20_IN2_PIN | BRUSHLESS20_EN3_PIN;
            break;
        }
        case BRUSHLESS20_TR_COM_STATE_4:
        {
            set_mask = BRUSHLESS20_EN2_PIN | BRUSHLESS20_EN3_PIN | BRUSHLESS20_IN3_PIN;
            clr_mask = BRUSHLESS20_EN1_PIN | BRUSHLESS20_IN2_PIN;
            break;
        }
        case BRUSHLESS20_TR_COM_STATE_5:
        {
            set_mask = BRUSHLESS20_EN1_PIN | BRUSHLESS20_EN3_PIN | BRUSHLESS20_IN3_PIN;
            clr_mask = BRUSHLESS20_IN1_PIN | BRUSHLESS20_EN2_PIN;
            break;
        }
        case BRUSHLESS20_TR_COM_STATE_6:
        {
            set_mask = BRUSHLESS20_EN1_PIN | BRUSHLESS20_EN2_PIN | BRUSHLESS20_IN2_PIN;
            clr_mask = BRUSHLESS20_IN1_PIN | BRUSHLESS20_EN3_PIN;
            break;
        }
        case BRUSHLESS20_TR_COM_STATE_BRAKE:
        {
            set_mask = BRUSHLESS20_EN1_PIN | BRUSHLESS20_EN2_PIN | BRUSHLESS20_EN3_PIN;
            clr_mask = BRUSHLESS20_IN1_PIN | BRUSHLESS20_IN2_PIN | BRUSHLESS20_IN3_PIN;
            break;
        }
        default:
        {
            return BRUSHLESS20_ERROR;
        }
    }
    return brushless20_set_pins ( ctx, set_mask, clr_mask );
}

err_t brushless20_toggle_pin ( brushless20_t *ctx, uint8_t pin_mask, uint8_t speed )
{
    err_t error_flag = BRUSHLESS20_OK;
    for ( uint16_t cnt = 0; cnt < BRUSHLESS20_NUM_PIN_TOGGLE; cnt++ )
    {
        int16_t speed_cnt = BRUSHLESS20_SPEED_MAX;
        error_flag |= brushless20_set_pins ( ctx, pin_mask, BRUSHLESS20_NONE_PIN );
        error_flag |= brushless20_set_pins ( ctx, BRUSHLESS20_NONE_PIN, pin_mask );
        while ( speed_cnt-- >= speed )
        {
            Delay_50us ( );
            Delay_50us ( );
        }
    }
    return error_flag;
}

err_t brushless20_perform_com_sequence ( brushless20_t *ctx, uint8_t dir, uint8_t speed )
{
    err_t error_flag = BRUSHLESS20_OK;
    if ( ( speed > BRUSHLESS20_SPEED_MAX ) || 
         ( ( BRUSHLESS20_DIR_CW != dir ) && ( BRUSHLESS20_DIR_CCW != dir ) ) )
    {
        return BRUSHLESS20_ERROR;
    }
    if ( BRUSHLESS20_DIR_CW == dir )
    {
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_6 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN2_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_1 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN2_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_2 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN1_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_3 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN1_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_4 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN3_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_5 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN3_PIN, speed );
    }
    else
    {
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_3 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN1_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_2 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN1_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_1 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN2_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_6 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN2_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_5 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN3_PIN, speed );
        error_flag |= brushless20_set_trapezoidal_com_state ( ctx, BRUSHLESS20_TR_COM_STATE_4 );
        error_flag |= brushless20_toggle_pin ( ctx, BRUSHLESS20_IN3_PIN, speed );
    }
    return error_flag;
}

err_t brushless20_drive_motor ( brushless20_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms )
{
    err_t error_flag = BRUSHLESS20_OK;
    float aprox_sequence_time = BRUSHLESS20_COM_SEQ_DURATION_FOR_SPEED_MAX + 
                                ( BRUSHLESS20_SPEED_MAX - speed ) * BRUSHLESS20_COM_SEQ_DURATION_SPEED_STEP;
    int32_t num_seq = ( int32_t ) ( time_ms / aprox_sequence_time + BRUSHLESS20_ROUND_TO_NEAREAST_INT );
    do 
    {
        error_flag |= brushless20_perform_com_sequence ( ctx, dir, speed );
    } 
    while ( ( --num_seq > 0 ) && ( BRUSHLESS20_OK == error_flag ) );
    return error_flag;
}

// ------------------------------------------------------------------------- END
