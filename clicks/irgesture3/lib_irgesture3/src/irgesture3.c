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
 * @file irgesture3.c
 * @brief IR Gesture 3 Click Driver.
 */

#include "irgesture3.h"

void irgesture3_cfg_setup ( irgesture3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->io1 = HAL_PIN_NC;
    cfg->io0 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = IRGESTURE3_DEVICE_ADDRESS;
}

err_t irgesture3_init ( irgesture3_t *ctx, irgesture3_cfg_t *cfg ) 
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

    digital_in_init( &ctx->io1, cfg->io1 );
    digital_in_init( &ctx->io0, cfg->io0 );

    return I2C_MASTER_SUCCESS;
}

err_t irgesture3_default_cfg ( irgesture3_t *ctx ) 
{
    err_t error_flag = IRGESTURE3_OK;
    if ( IRGESTURE3_ERROR == irgesture3_check_communication ( ctx ) )
    {
        return IRGESTURE3_ERROR;
    }
    error_flag |= irgesture3_sw_reset ( ctx );
    Delay_100ms ( );
    
    // Enable state machine clock
    uint16_t reg_data = 0;
    error_flag |= irgesture3_read_register ( ctx, IRGESTURE3_REG_SAMPLE_CLK, &reg_data );
    reg_data |= IRGESTURE3_SAMPLE_CLK_CLK32K_EN_MASK;
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_SAMPLE_CLK, reg_data );
    
    error_flag |= irgesture3_set_mode ( ctx, IRGESTURE3_MODE_PROGRAM );
    
    // Enable slot A interrupt
    error_flag |= irgesture3_read_register ( ctx, IRGESTURE3_REG_INT_MASK, &reg_data );
    reg_data &= ~IRGESTURE3_INT_MASK_SLOTA_INT_MASK;
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_INT_MASK, reg_data );

    // Set GPIO0 to Active LOW interrupt
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_GPIO_DRV, IRGESTURE3_GPIO_DRV_GPIO0_ENA_MASK | 
                                                                            IRGESTURE3_GPIO_DRV_GPIO0_POL_MASK );
    
    // Enable slot A
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_SLOT_EN, IRGESTURE3_SLOT_EN_SLOTA_EN_MASK );
    
    error_flag |= irgesture3_clear_status ( ctx );
    
    // Map timeslot A to PD1-4 channels
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_PD_LED_SELECT, 
                                              IRGESTURE3_PD_LED_SELECT_SLOTA_PD_1_2_3_4 | 
                                              IRGESTURE3_PD_LED_SELECT_SLOTA_LED_1 );
    
    // Disable averaging
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_NUM_AVG, IRGESTURE3_NUM_AVG_SLOTA_1 );
    
    // Set slot A chop mode to inverted, non-inverted, non-inverted, inverted
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_INT_SEQ_A, 
                                              IRGESTURE3_INT_SEQ_A_INTEG_ORDER_A_1001 );
    
    // Set LED 1 power
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_ILED1_COARSE, 
                                              IRGESTURE3_ILED1_COARSE_SCALE_100_PCT | 
                                              IRGESTURE3_ILED1_COARSE_SLEW_3  | 
                                              IRGESTURE3_ILED1_COARSE_COARSE_6 );
    
    // Set slot A to 4 LED pulses with 15us period
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_SLOTA_NUMPULSES, 
                                              IRGESTURE3_SLOTA_NUMPULSES_PULSES_4 | 
                                              IRGESTURE3_SLOTA_NUMPULSES_PERIOD_15_US );
    
    // Set slot A integrator window, offset 23.5us, width 4us
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_SLOTA_AFE_WINDOW, 
                                              IRGESTURE3_SLOTA_AFE_WINDOW_WIDTH_4_US |
                                              IRGESTURE3_SLOTA_AFE_WINDOW_OFFSET_23_5_US );
    
    // Set math for chop mode to inverted, non-inverted, non-inverted, inverted
    error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_MATH, 
                                              IRGESTURE3_MATH_FLT_MATH34_A_ADD_1_SUB_2 | 
                                              IRGESTURE3_MATH_FLT_MATH12_A_SUB_1_ADD_2 );
    
    error_flag |= irgesture3_set_adc_fsample ( ctx, IRGESTURE3_FSAMPLE_500_HZ );
    
    error_flag |= irgesture3_set_mode ( ctx, IRGESTURE3_MODE_NORMAL );
    
    error_flag |= irgesture3_wait_data_ready ( ctx );
    
    uint16_t offset = 0;
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        error_flag |= irgesture3_read_register ( ctx, IRGESTURE3_REG_SLOTA_CH1_OFFSET + cnt, &offset );
        error_flag |= irgesture3_read_register ( ctx, IRGESTURE3_REG_SLOTA_PD1_16BIT + cnt, &reg_data );
        error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_SLOTA_CH1_OFFSET + cnt, offset + reg_data );
    }
    
    return error_flag;
}

err_t irgesture3_write_register ( irgesture3_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t irgesture3_read_register ( irgesture3_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t irgesture3_check_communication ( irgesture3_t *ctx )
{
    uint16_t devid = 0;
    if ( IRGESTURE3_OK == irgesture3_read_register ( ctx, IRGESTURE3_REG_DEVID, &devid ) )
    {
        if ( IRGESTURE3_DEVICE_ID == ( devid & IRGESTURE3_DEVICE_ID_MASK ) )
        {
            return IRGESTURE3_OK;
        }
    }
    return IRGESTURE3_ERROR;
}

uint8_t irgesture3_get_io0_pin ( irgesture3_t *ctx )
{
    return digital_in_read ( &ctx->io0 );
}

uint8_t irgesture3_get_io1_pin ( irgesture3_t *ctx )
{
    return digital_in_read ( &ctx->io1 );
}

err_t irgesture3_sw_reset ( irgesture3_t *ctx )
{
    return irgesture3_write_register ( ctx, IRGESTURE3_REG_SW_RESET, IRGESTURE3_SW_RESET );
}

err_t irgesture3_set_mode ( irgesture3_t *ctx, uint8_t mode )
{
    err_t error_flag = irgesture3_write_register ( ctx, IRGESTURE3_REG_MODE, IRGESTURE3_MODE_PROGRAM );
    Delay_1ms ( );
    if ( ( IRGESTURE3_MODE_STANDBY == mode ) || ( IRGESTURE3_MODE_NORMAL == mode ) )
    {
        error_flag |= irgesture3_write_register ( ctx, IRGESTURE3_REG_MODE, ( uint16_t ) mode );
    }
    return error_flag;
}

err_t irgesture3_set_adc_fsample ( irgesture3_t *ctx, uint16_t freq_hz )
{
    uint16_t reg_data = 0;
    if ( freq_hz > IRGESTURE3_FSAMPLE_MAX )
    {
        return IRGESTURE3_ERROR;
    }
    reg_data = IRGESTURE3_INT_OSC / ( freq_hz * 4 );
    return irgesture3_write_register ( ctx, IRGESTURE3_REG_FSAMPLE, reg_data );
}

err_t irgesture3_clear_status ( irgesture3_t *ctx )
{
    return irgesture3_write_register ( ctx, IRGESTURE3_REG_STATUS, IRGESTURE3_STATUS_CLEAR );
}

err_t irgesture3_wait_data_ready ( irgesture3_t *ctx )
{
    uint32_t timeout_cnt = 0;
    while ( irgesture3_get_io0_pin ( ctx ) )
    {
        if ( ++timeout_cnt > IRGESTURE3_TIMEOUT_MS )
        {
            return IRGESTURE3_ERROR;
        }
        Delay_1ms ( );
    }
    return irgesture3_clear_status ( ctx );
}

err_t irgesture3_get_pd_data ( irgesture3_t *ctx, irgesture3_pd_data_t *pd_data )
{
    err_t error_flag = IRGESTURE3_OK;
    error_flag |= irgesture3_wait_data_ready ( ctx );
    error_flag |= irgesture3_read_register ( ctx, IRGESTURE3_REG_SLOTA_PD1_16BIT, &pd_data->x_right );
    error_flag |= irgesture3_read_register ( ctx, IRGESTURE3_REG_SLOTA_PD2_16BIT, &pd_data->x_left );
    error_flag |= irgesture3_read_register ( ctx, IRGESTURE3_REG_SLOTA_PD3_16BIT, &pd_data->y_bottom );
    error_flag |= irgesture3_read_register ( ctx, IRGESTURE3_REG_SLOTA_PD4_16BIT, &pd_data->y_top );
    return error_flag;
}

err_t irgesture3_get_gesture ( irgesture3_t *ctx, uint8_t *gesture )
{
    err_t error_flag = IRGESTURE3_OK;
    irgesture3_pd_data_t pd_data;
    uint32_t light = 0;
    float start_x = 0;
    float start_y = 0;
    float end_x = 0;
    float end_y = 0;
    float slope = 0;
    float distance = 0;
    uint16_t num_samples = 0;
    
    // Wait for start coordinates
    while ( ( IRGESTURE3_OK == error_flag ) && ( light < IRGESTURE3_LIGHT_THRESHOLD ) )
    {
        error_flag |= irgesture3_get_pd_data ( ctx, &pd_data );
        light = ( uint32_t ) pd_data.x_left + pd_data.x_right + pd_data.y_top + pd_data.y_bottom;
        if ( ++num_samples > IRGESTURE3_MAX_NUM_SAMPLES )
        {
            error_flag = IRGESTURE3_ERROR;
        }
    }
    if ( IRGESTURE3_OK == error_flag )
    {
        if ( ( ( float ) pd_data.x_left + pd_data.x_right ) )
        {
            start_x = ( ( float ) pd_data.x_left - pd_data.x_right ) / 
                      ( ( float ) pd_data.x_left + pd_data.x_right );
        }
        if ( ( ( float ) pd_data.y_top + pd_data.y_bottom ) )
        {
            start_y = ( ( float ) pd_data.y_top - pd_data.y_bottom ) / 
                      ( ( float ) pd_data.y_top + pd_data.y_bottom );
        }
        num_samples = 1;
    }
    
    // Wait for end coordinates
    while ( ( IRGESTURE3_OK == error_flag ) && ( light > IRGESTURE3_LIGHT_THRESHOLD ) )
    {
        error_flag |= irgesture3_get_pd_data ( ctx, &pd_data );
        light = ( uint32_t ) pd_data.x_left + pd_data.x_right + pd_data.y_top + pd_data.y_bottom;
        if ( ++num_samples > IRGESTURE3_MAX_NUM_SAMPLES )
        {
            break;
        }
    }
    if ( num_samples < IRGESTURE3_MIN_NUM_SAMPLES )
    {
        error_flag = IRGESTURE3_ERROR;
    }
    
    // Calculate gesture
    if ( IRGESTURE3_OK == error_flag )
    {
        if ( ( ( float ) pd_data.x_left + pd_data.x_right ) )
        {
            end_x = ( ( float ) pd_data.x_left - pd_data.x_right ) / 
                    ( ( float ) pd_data.x_left + pd_data.x_right );
        }
        if ( ( ( float ) pd_data.y_top + pd_data.y_bottom ) )
        {
            end_y = ( ( float ) pd_data.y_top - pd_data.y_bottom ) / 
                    ( ( float ) pd_data.y_top + pd_data.y_bottom );
        }
        slope = ( start_y - end_y ) / ( start_x - end_x + pow( 10, -6 ) );
        distance = sqrt ( pow ( start_x - end_x, 2 ) + pow( start_y - end_y, 2 ) );
        if ( slope < 0 )
        {
            slope *= -1;
        }
        if ( distance < IRGESTURE3_DISTANCE_THRESHOLD )
        {
            *gesture = IRGESTURE3_GESTURE_CLICK;
        }
        else if ( ( slope > 1 ) && ( start_y > end_y ) )
        {
            *gesture = IRGESTURE3_GESTURE_SWIPE_RIGHT;
        }
        else if ( ( slope > 1 ) && ( start_y <= end_y ) )
        {
            *gesture = IRGESTURE3_GESTURE_SWIPE_LEFT;
        }
        else if ( ( slope < 1 ) && ( start_x > end_x ) )
        {
            *gesture = IRGESTURE3_GESTURE_SWIPE_DOWN;
        }
        else if ( ( slope < 1 ) && ( start_x <= end_x ) )
        {
            *gesture = IRGESTURE3_GESTURE_SWIPE_UP;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
