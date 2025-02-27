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
 * @file heartrate13.c
 * @brief Heart Rate 13 Click Driver.
 */

#include "heartrate13.h"

void heartrate13_cfg_setup ( heartrate13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->io0 = HAL_PIN_NC;
    cfg->io1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HEARTRATE13_DEVICE_ADDRESS;
}

err_t heartrate13_init ( heartrate13_t *ctx, heartrate13_cfg_t *cfg ) 
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

    digital_in_init( &ctx->io0, cfg->io0 );
    digital_in_init( &ctx->io1, cfg->io1 );

    return I2C_MASTER_SUCCESS;
}

err_t heartrate13_default_cfg ( heartrate13_t *ctx ) 
{
    err_t error_flag = HEARTRATE13_OK;
    uint16_t reg_data = 0;
    uint16_t offset = 0;
    uint8_t cnt = 0;

    if ( HEARTRATE13_ERROR == heartrate13_check_communication ( ctx ) )
    {
        return HEARTRATE13_ERROR;
    }
    error_flag |= heartrate13_sw_reset ( ctx );
    Delay_100ms ( );
    
    // Enable state machine clock
    error_flag |= heartrate13_read_register ( ctx, HEARTRATE13_REG_SAMPLE_CLK, &reg_data );
    reg_data |= HEARTRATE13_SAMPLE_CLK_CLK32K_EN_MASK;
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_SAMPLE_CLK, reg_data );
    
    error_flag |= heartrate13_set_mode ( ctx, HEARTRATE13_MODE_PROGRAM );
    
    // Enable slot A interrupt
    error_flag |= heartrate13_read_register ( ctx, HEARTRATE13_REG_INT_MASK, &reg_data );
    reg_data &= ~HEARTRATE13_INT_MASK_SLOTA_INT_MASK;
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_INT_MASK, reg_data );

    // Set GPIO0 to Active LOW interrupt
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_GPIO_DRV, HEARTRATE13_GPIO_DRV_GPIO0_ENA_MASK | 
                                                                              HEARTRATE13_GPIO_DRV_GPIO0_POL_MASK );
    
    // Enable slot A
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_SLOT_EN, HEARTRATE13_SLOT_EN_SLOTA_EN_MASK );
    
    error_flag |= heartrate13_clear_status ( ctx );
    
    // Map timeslot A to PD1-4 channels
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_PD_LED_SELECT, 
                                               HEARTRATE13_PD_LED_SELECT_SLOTA_PD_1_2_3_4 | 
                                               ( HEARTRATE13_DEFAULT_LED & HEARTRATE13_PD_LED_SELECT_SLOTA_LED_SEL_MASK ) );
    
    // Set averaging to 16 samples
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_NUM_AVG, HEARTRATE13_NUM_AVG_SLOTA_16 );

    // Set LEDs power
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_ILED1_COARSE,  
                                               HEARTRATE13_ILEDX_COARSE_SCALE_100_PCT | 
                                               HEARTRATE13_ILEDX_COARSE_RESERVED | 
                                               HEARTRATE13_ILEDX_COARSE_SLEW_MIN  | 
                                               HEARTRATE13_ILEDX_COARSE_COARSE_MIN );
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_ILED2_COARSE,  
                                               HEARTRATE13_ILEDX_COARSE_SCALE_100_PCT | 
                                               HEARTRATE13_ILEDX_COARSE_RESERVED | 
                                               HEARTRATE13_ILEDX_COARSE_SLEW_MIN  | 
                                               HEARTRATE13_ILEDX_COARSE_COARSE_MIN );
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_ILED3_COARSE,  
                                               HEARTRATE13_ILEDX_COARSE_SCALE_100_PCT | 
                                               HEARTRATE13_ILEDX_COARSE_RESERVED | 
                                               HEARTRATE13_ILEDX_COARSE_SLEW_MIN  | 
                                               HEARTRATE13_ILEDX_COARSE_COARSE_MIN );

    // Set slot A to 8 LED pulses with 15us period
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_SLOTA_NUMPULSES, 
                                               HEARTRATE13_SLOTA_NUMPULSES_PULSES_8 | 
                                               HEARTRATE13_SLOTA_NUMPULSES_PERIOD_15_US );
    
    // Set slot A integrator window, offset 23.5us, width 4us
    error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_SLOTA_AFE_WINDOW, 
                                               HEARTRATE13_SLOTA_AFE_WINDOW_WIDTH_4_US |
                                               HEARTRATE13_SLOTA_AFE_WINDOW_OFFSET_23_5_US );
    
    error_flag |= heartrate13_set_adc_fsample ( ctx, HEARTRATE13_FSAMPLE_1000_HZ );
    
    error_flag |= heartrate13_set_mode ( ctx, HEARTRATE13_MODE_NORMAL );
    
    // Calibrate offset for PD1-PD3
    error_flag |= heartrate13_wait_data_ready ( ctx );
    for ( cnt = 0; cnt < 3; cnt++ )
    {
        error_flag |= heartrate13_read_register ( ctx, HEARTRATE13_REG_SLOTA_CH1_OFFSET + cnt, &offset );
        error_flag |= heartrate13_read_register ( ctx, HEARTRATE13_REG_SLOTA_PD1_16BIT + cnt, &reg_data );
        error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_SLOTA_CH1_OFFSET + cnt, offset + reg_data );
    }
    return error_flag;
}

err_t heartrate13_write_register ( heartrate13_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t heartrate13_read_register ( heartrate13_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t heartrate13_check_communication ( heartrate13_t *ctx )
{
    uint16_t devid = 0;
    if ( HEARTRATE13_OK == heartrate13_read_register ( ctx, HEARTRATE13_REG_DEVID, &devid ) )
    {
        if ( HEARTRATE13_DEVICE_ID == ( devid & HEARTRATE13_DEVICE_ID_MASK ) )
        {
            return HEARTRATE13_OK;
        }
    }
    return HEARTRATE13_ERROR;
}

uint8_t heartrate13_get_io0_pin ( heartrate13_t *ctx )
{
    return digital_in_read ( &ctx->io0 );
}

uint8_t heartrate13_get_io1_pin ( heartrate13_t *ctx )
{
    return digital_in_read ( &ctx->io1 );
}

err_t heartrate13_sw_reset ( heartrate13_t *ctx )
{
    return heartrate13_write_register ( ctx, HEARTRATE13_REG_SW_RESET, HEARTRATE13_SW_RESET );
}

err_t heartrate13_set_mode ( heartrate13_t *ctx, uint8_t mode )
{
    err_t error_flag = heartrate13_write_register ( ctx, HEARTRATE13_REG_MODE, HEARTRATE13_MODE_PROGRAM );
    Delay_1ms ( );
    if ( ( HEARTRATE13_MODE_STANDBY == mode ) || ( HEARTRATE13_MODE_NORMAL == mode ) )
    {
        error_flag |= heartrate13_write_register ( ctx, HEARTRATE13_REG_MODE, ( uint16_t ) mode );
    }
    return error_flag;
}

err_t heartrate13_set_adc_fsample ( heartrate13_t *ctx, uint16_t freq_hz )
{
    uint16_t reg_data = 0;
    if ( freq_hz > HEARTRATE13_FSAMPLE_MAX )
    {
        return HEARTRATE13_ERROR;
    }
    reg_data = HEARTRATE13_INT_OSC / ( freq_hz * 4 );
    return heartrate13_write_register ( ctx, HEARTRATE13_REG_FSAMPLE, reg_data );
}

err_t heartrate13_clear_status ( heartrate13_t *ctx )
{
    return heartrate13_write_register ( ctx, HEARTRATE13_REG_STATUS, HEARTRATE13_STATUS_CLEAR );
}

err_t heartrate13_wait_data_ready ( heartrate13_t *ctx )
{
    uint32_t timeout_cnt = 0;
    while ( heartrate13_get_io0_pin ( ctx ) )
    {
        if ( ++timeout_cnt > HEARTRATE13_TIMEOUT_MS )
        {
            return HEARTRATE13_ERROR;
        }
        Delay_1ms ( );
    }
    return heartrate13_clear_status ( ctx );
}

err_t heartrate13_get_pd_data ( heartrate13_t *ctx, heartrate13_pd_data_t *pd_data )
{
    err_t error_flag = HEARTRATE13_OK;
    error_flag |= heartrate13_wait_data_ready ( ctx );
    error_flag |= heartrate13_read_register ( ctx, HEARTRATE13_REG_SLOTA_PD1_16BIT, &pd_data->pd1 );
    error_flag |= heartrate13_read_register ( ctx, HEARTRATE13_REG_SLOTA_PD2_16BIT, &pd_data->pd2 );
    error_flag |= heartrate13_read_register ( ctx, HEARTRATE13_REG_SLOTA_PD3_16BIT, &pd_data->pd3 );
    return error_flag;
}

// ------------------------------------------------------------------------- END
