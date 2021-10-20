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
 * @file proximity15.c
 * @brief Proximity 15 Click Driver.
 */

#include "proximity15.h"

/**
 * @brief Proximity 15 Click default configuration.
 * @details Default configuration values for registers 0x2D to 0x87.
 */
uint8_t proximity15_default_config[ ] = 
{
    0x00, /* 0x2D : Set bit 2 and 5 to 1 for fast plus mode (1MHz I2C), else don't touch */
    0x00, /* 0x2E : Bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
    0x00, /* 0x2F : Bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
    0x01, /* 0x30 : Set bit 4 to 0 for active high interrupt and 1 for active low (bits 3:0 must be 0x01) */
    0x02, /* 0x31 : Bit 1 = interrupt depending on the polarity */
    0x00, /* 0x32 : Not user-modificable */
    0x02, /* 0x33 : Not user-modificable */
    0x08, /* 0x34 : Not user-modificable */
    0x00, /* 0x35 : Not user-modificable */
    0x08, /* 0x36 : Not user-modificable */
    0x10, /* 0x37 : Not user-modificable */
    0x01, /* 0x38 : Not user-modificable */
    0x01, /* 0x39 : Not user-modificable */
    0x00, /* 0x3A : Not user-modificable */
    0x00, /* 0x3B : Not user-modificable */
    0x00, /* 0x3C : Not user-modificable */
    0x00, /* 0x3D : Not user-modificable */
    0xFF, /* 0x3E : Not user-modificable */
    0x00, /* 0x3F : Not user-modificable */
    0x0F, /* 0x40 : Not user-modificable */
    0x00, /* 0x41 : Not user-modificable */
    0x00, /* 0x42 : Not user-modificable */
    0x00, /* 0x43 : Not user-modificable */
    0x00, /* 0x44 : Not user-modificable */
    0x00, /* 0x45 : Not user-modificable */
    0x20, /* 0x46 : Interrupt configuration: 0x20-> New sample ready */
    0x0B, /* 0x47 : Not user-modificable */
    0x00, /* 0x48 : Not user-modificable */
    0x00, /* 0x49 : Not user-modificable */
    0x02, /* 0x4A : Not user-modificable */
    0x0A, /* 0x4B : Not user-modificable */
    0x21, /* 0x4C : Not user-modificable */
    0x00, /* 0x4D : Not user-modificable */
    0x00, /* 0x4E : Not user-modificable */
    0x05, /* 0x4F : Not user-modificable */
    0x00, /* 0x50 : Not user-modificable */
    0x00, /* 0x51 : Not user-modificable */
    0x00, /* 0x52 : Not user-modificable */
    0x00, /* 0x53 : Not user-modificable */
    0xC8, /* 0x54 : Not user-modificable */
    0x00, /* 0x55 : Not user-modificable */
    0x00, /* 0x56 : Not user-modificable */
    0x38, /* 0x57 : Not user-modificable */
    0xFF, /* 0x58 : Not user-modificable */
    0x01, /* 0x59 : Not user-modificable */
    0x00, /* 0x5A : Not user-modificable */
    0x08, /* 0x5B : Not user-modificable */
    0x00, /* 0x5C : Not user-modificable */
    0x00, /* 0x5D : Not user-modificable */
    0x00, /* 0x5E : Timeout MACROP A HI MSB, default 50ms, use proximity15_set_timeout_budget( ) */
    0xAD, /* 0x5F : Timeout MACROP A HI LSB */
    0x0F, /* 0x60 : Not user-modificable */
    0x00, /* 0x61 : Timeout MACROP B HI MSB, default 50ms, use proximity15_set_timeout_budget( ) */
    0xC6, /* 0x62 : Timeout MACROP B HI LSB */
    0x0D, /* 0x63 : Not user-modificable */
    0x01, /* 0x64 : Sigma threshold MSB (mm in 14.2 format for MSB+LSB), default value 90 mm */
    0x68, /* 0x65 : Sigma threshold LSB */
    0x00, /* 0x66 : Min count Rate MSB (MCPS in 9.7 format for MSB+LSB) */
    0x80, /* 0x67 : Min count Rate LSB */
    0x08, /* 0x68 : Not user-modificable */
    0xB8, /* 0x69 : Not user-modificable */
    0x00, /* 0x6A : Not user-modificable */
    0x00, /* 0x6B : Not user-modificable */
    0x00, /* 0x6C : Intermeasurement period MSB, default 100ms, use proximity15_set_inter_measurement_period( ) */
    0x00, /* 0x6D : Intermeasurement period */
    0x0F, /* 0x6E : Intermeasurement period */
    0x77, /* 0x6F : Intermeasurement period LSB */
    0x00, /* 0x70 : Not user-modificable */
    0x00, /* 0x71 : Not user-modificable */
    0x00, /* 0x72 : Distance threshold high MSB (in mm, MSB+LSB) */
    0x00, /* 0x73 : Distance threshold high LSB */
    0x00, /* 0x74 : Distance threshold low MSB ( in mm, MSB+LSB) */
    0x00, /* 0x75 : Distance threshold low LSB */
    0x00, /* 0x76 : Not user-modificable */
    0x01, /* 0x77 : Not user-modificable */
    0x0F, /* 0x78 : Not user-modificable */
    0x0D, /* 0x79 : Not user-modificable */
    0x0E, /* 0x7A : Not user-modificable */
    0x0E, /* 0x7B : Not user-modificable */
    0x00, /* 0x7C : Not user-modificable */
    0x00, /* 0x7D : Not user-modificable */
    0x02, /* 0x7E : Not user-modificable */
    0xC7, /* 0x7F : ROI center */
    0xFF, /* 0x80 : XY ROI (X=Width, Y=Height) */
    0x9B, /* 0x81 : Not user-modificable */
    0x00, /* 0x82 : Not user-modificable */
    0x00, /* 0x83 : Not user-modificable */
    0x00, /* 0x84 : Not user-modificable */
    0x01, /* 0x85 : Not user-modificable */
    0x00, /* 0x86 : clear interrupt, use proximity15_clear_interrupt( ) */
    0x00  /* 0x87 : start ranging, use proximity15_start_ranging() or proximity15_stop_ranging() */
};

void proximity15_cfg_setup ( proximity15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->xsh   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY15_SET_DEV_ADDR;
}

err_t proximity15_init ( proximity15_t *ctx, proximity15_cfg_t *cfg ) 
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

    digital_out_init( &ctx->xsh, cfg->xsh );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t proximity15_default_cfg ( proximity15_t *ctx ) 
{
    proximity15_enable_sensor ( ctx );
    
    if ( PROXIMITY15_ERROR == proximity15_check_communication ( ctx ) )
    {
        return PROXIMITY15_ERROR;
    }
    
    err_t error_flag = proximity15_software_reset ( ctx );
    
    error_flag |= proximity15_write_registers ( ctx, PROXIMITY15_REG_PAD_I2C_HV_CFG, 
                                                     proximity15_default_config, 
                                                     sizeof ( proximity15_default_config ) );

    error_flag |= proximity15_set_distance_mode ( ctx, PROXIMITY15_DISTANCE_MODE_LONG );
    
    error_flag |= proximity15_set_timing_budget ( ctx, PROXIMITY15_TIMING_BUDGET_50MS );
    
    error_flag |= proximity15_set_inter_measurement_period ( ctx, 100 );
    
    error_flag |= proximity15_start_ranging ( ctx );
    
    while ( !proximity15_get_int_pin ( ctx ) );
    
    error_flag |= proximity15_clear_interrupt ( ctx );
    
    return error_flag;
}

err_t proximity15_write_registers ( proximity15_t *ctx, uint16_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );

    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ cnt + 2 ] = tx_buf[ cnt ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 2 );
}

err_t proximity15_read_registers ( proximity15_t *ctx, uint16_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };
    
    tx_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    tx_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    
    return i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, rx_len );
}

err_t proximity15_write_register ( proximity15_t *ctx, uint16_t reg, uint8_t tx_data ) 
{
    return proximity15_write_registers ( ctx, reg, &tx_data, 1 );
}

err_t proximity15_read_register ( proximity15_t *ctx, uint16_t reg, uint8_t *rx_data ) 
{
    return proximity15_read_registers ( ctx, reg, rx_data, 1 );
}

err_t proximity15_check_communication ( proximity15_t *ctx ) 
{
    uint8_t dev_id[ 2 ] = { 0 };

    if ( PROXIMITY15_OK == proximity15_read_registers ( ctx, PROXIMITY15_REG_MODEL_ID, dev_id, 2 ) )
    {
        if ( ( PROXIMITY15_MODEL_ID == dev_id[ 0 ] ) && 
             ( PROXIMITY15_MODULE_TYPE == dev_id[ 1 ] ) )
        {
            return PROXIMITY15_OK;
        }
    }
    return PROXIMITY15_ERROR;
}

err_t proximity15_software_reset ( proximity15_t *ctx )
{
    err_t error_flag = proximity15_write_register ( ctx, PROXIMITY15_REG_SOFT_RESET, PROXIMITY15_SOFT_RESET_ENTER );
    Delay_500us( );
    error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_SOFT_RESET, PROXIMITY15_SOFT_RESET_EXIT );
    Delay_1sec( );
    return error_flag;
}

err_t proximity15_get_distance ( proximity15_t *ctx, uint16_t *distance )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    
    while ( !proximity15_get_int_pin ( ctx ) );
    
    err_t error_flag = proximity15_read_registers ( ctx, PROXIMITY15_REG_RES_FINAL_RANGE_MM_SD0, rx_buf, 2 );
    
    *distance = rx_buf[ 0 ];
    *distance <<= 8;
    *distance |= rx_buf[ 1 ];
    
    error_flag |= proximity15_clear_interrupt( ctx );
    
    return error_flag;
}

void proximity15_enable_sensor ( proximity15_t *ctx )
{
    digital_out_high ( &ctx->xsh );
    Delay_1sec( );
}

void proximity15_disable_sensor ( proximity15_t *ctx )
{
    digital_out_low ( &ctx->xsh );
}

uint8_t proximity15_get_int_pin ( proximity15_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t proximity15_start_ranging ( proximity15_t *ctx )
{
    return proximity15_write_register ( ctx, PROXIMITY15_REG_SYSTEM_MODE_START, PROXIMITY15_START_RANGING );
}

err_t proximity15_stop_ranging ( proximity15_t *ctx )
{
    return proximity15_write_register ( ctx, PROXIMITY15_REG_SYSTEM_MODE_START, PROXIMITY15_STOP_RANGING );
}

err_t proximity15_clear_interrupt ( proximity15_t *ctx )
{
    return proximity15_write_register ( ctx, PROXIMITY15_REG_SYSTEM_INTERRUPT_CLEAR, PROXIMITY15_CLEAR_INTERRUPT );
}

err_t proximity15_set_inter_measurement_period ( proximity15_t *ctx, uint16_t time_ms )
{
    uint32_t meas_period = 0;
    uint8_t tmp_buf[ 4 ] = { 0 };
    
    err_t error_flag = proximity15_read_registers ( ctx, PROXIMITY15_REG_RES_OSC_CALIB_VAL, tmp_buf, 2 );
    meas_period = tmp_buf[ 0 ];
    meas_period <<= 8;
    meas_period |= tmp_buf[ 1 ];
    meas_period &= 0x03FF;
    meas_period *= ( uint32_t ) ( time_ms * PROXIMITY15_MEASURE_PERIOD_CONST ); 
    
    tmp_buf[ 0 ] = ( uint8_t ) ( ( meas_period >> 24 ) & 0xFF );
    tmp_buf[ 1 ] = ( uint8_t ) ( ( meas_period >> 16 ) & 0xFF );
    tmp_buf[ 2 ] = ( uint8_t ) ( ( meas_period >> 8 ) & 0xFF );
    tmp_buf[ 3 ] = ( uint8_t ) ( meas_period & 0xFF );
    
    error_flag |= proximity15_write_registers ( ctx, PROXIMITY15_REG_SYSTEM_INT_MEAS_PERIOD, tmp_buf, 4 );

    return error_flag;
}

err_t proximity15_set_distance_mode ( proximity15_t *ctx, uint8_t mode )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    proximity15_timing_budget_t time;
    
    err_t error_flag = proximity15_get_timing_budget ( ctx, &time );
    
    switch ( mode )
    {
        case PROXIMITY15_DISTANCE_MODE_SHORT:
        {
            error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_CFG_TIMEOUT_MACROP, PROXIMITY15_TIMEOUT_MACROP_SHORT );
            error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_CFG_VCSEL_PERIOD_A, 0x07 );
            error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_CFG_VCSEL_PERIOD_B, 0x05 );
            error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_CFG_VALID_PHASE_HIGH, 0x38 );
            tx_buf[ 0 ] = 0x07;
            tx_buf[ 1 ] = 0x05;
            error_flag |= proximity15_write_registers ( ctx, PROXIMITY15_REG_SD_CFG_WOI_SD0, tx_buf, 2 );
            tx_buf[ 0 ] = 0x06;
            tx_buf[ 1 ] = 0x06;
            error_flag |= proximity15_write_registers ( ctx, PROXIMITY15_REG_SD_CFG_INIT_PHASE_SD0, tx_buf, 2 );
            break;
        }
        case PROXIMITY15_DISTANCE_MODE_LONG:
        {
            error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_CFG_TIMEOUT_MACROP, PROXIMITY15_TIMEOUT_MACROP_LONG );
            error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_CFG_VCSEL_PERIOD_A, 0x0F );
            error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_CFG_VCSEL_PERIOD_B, 0x0D );
            error_flag |= proximity15_write_register ( ctx, PROXIMITY15_REG_CFG_VALID_PHASE_HIGH, 0xB8 );
            tx_buf[ 0 ] = 0x0F;
            tx_buf[ 1 ] = 0x0D;
            error_flag |= proximity15_write_registers ( ctx, PROXIMITY15_REG_SD_CFG_WOI_SD0, tx_buf, 2 );
            tx_buf[ 0 ] = 0x0E;
            tx_buf[ 1 ] = 0x0E;
            error_flag |= proximity15_write_registers ( ctx, PROXIMITY15_REG_SD_CFG_INIT_PHASE_SD0, tx_buf, 2 );
            break;
        }
        default:
        {
            return PROXIMITY15_ERROR;
        }
    }
    error_flag |= proximity15_set_timing_budget ( ctx, time );
    
    return error_flag;
}

err_t proximity15_get_distance_mode ( proximity15_t *ctx, uint8_t *mode )
{
    uint8_t reg_data = 0;
    
    if ( PROXIMITY15_OK == proximity15_read_register ( ctx, PROXIMITY15_REG_CFG_TIMEOUT_MACROP, &reg_data ) )
    {
        if ( PROXIMITY15_TIMEOUT_MACROP_SHORT == reg_data )
        {
            *mode = PROXIMITY15_DISTANCE_MODE_SHORT;
            return PROXIMITY15_OK;
        }
        else if ( PROXIMITY15_TIMEOUT_MACROP_LONG == reg_data )
        {
            *mode = PROXIMITY15_DISTANCE_MODE_LONG;
            return PROXIMITY15_OK;
        }
    }
    return PROXIMITY15_ERROR;
}

err_t proximity15_set_timing_budget ( proximity15_t *ctx, proximity15_timing_budget_t time )
{
    uint8_t a_hi_buf[ 2 ] = { 0 };
    uint8_t b_hi_buf[ 2 ] = { 0 };
    uint8_t distance_mode = 0;
    err_t error_flag = proximity15_get_distance_mode ( ctx, &distance_mode );
    
    if ( PROXIMITY15_ERROR == error_flag )
    {
        return PROXIMITY15_ERROR;
    }
    
    switch ( time )
    {
        case PROXIMITY15_TIMING_BUDGET_15MS:
        {
            if ( PROXIMITY15_DISTANCE_MODE_SHORT == distance_mode )
            {
                a_hi_buf[ 0 ] = 0x00;
                a_hi_buf[ 1 ] = 0x1D;
                b_hi_buf[ 0 ] = 0x00;
                b_hi_buf[ 1 ] = 0x27;
            }
            else
            {
                return PROXIMITY15_ERROR;
            }
            break;
        }
        case PROXIMITY15_TIMING_BUDGET_20MS:
        {
            if ( PROXIMITY15_DISTANCE_MODE_SHORT == distance_mode )
            {
                a_hi_buf[ 0 ] = 0x00;
                a_hi_buf[ 1 ] = 0x51;
                b_hi_buf[ 0 ] = 0x00;
                b_hi_buf[ 1 ] = 0x6E;
            }
            else
            {
                a_hi_buf[ 0 ] = 0x00;
                a_hi_buf[ 1 ] = 0x1E;
                b_hi_buf[ 0 ] = 0x00;
                b_hi_buf[ 1 ] = 0x22;
            }
            break;
        }
        case PROXIMITY15_TIMING_BUDGET_33MS:
        {
            if ( PROXIMITY15_DISTANCE_MODE_SHORT == distance_mode )
            {
                a_hi_buf[ 0 ] = 0x00;
                a_hi_buf[ 1 ] = 0xD6;
                b_hi_buf[ 0 ] = 0x00;
                b_hi_buf[ 1 ] = 0x6E;
            }
            else
            {
                a_hi_buf[ 0 ] = 0x00;
                a_hi_buf[ 1 ] = 0x60;
                b_hi_buf[ 0 ] = 0x00;
                b_hi_buf[ 1 ] = 0x6E;
            }
            break;
        }
        case PROXIMITY15_TIMING_BUDGET_50MS:
        {
            if ( PROXIMITY15_DISTANCE_MODE_SHORT == distance_mode )
            {
                a_hi_buf[ 0 ] = 0x01;
                a_hi_buf[ 1 ] = 0xAE;
                b_hi_buf[ 0 ] = 0x01;
                b_hi_buf[ 1 ] = 0xE8;
            }
            else
            {
                a_hi_buf[ 0 ] = 0x00;
                a_hi_buf[ 1 ] = 0xAD;
                b_hi_buf[ 0 ] = 0x00;
                b_hi_buf[ 1 ] = 0xC6;
            }
            break;
        }
        case PROXIMITY15_TIMING_BUDGET_100MS:
        {
            if ( PROXIMITY15_DISTANCE_MODE_SHORT == distance_mode )
            {
                a_hi_buf[ 0 ] = 0x02;
                a_hi_buf[ 1 ] = 0xE1;
                b_hi_buf[ 0 ] = 0x03;
                b_hi_buf[ 1 ] = 0x88;
            }
            else
            {
                a_hi_buf[ 0 ] = 0x01;
                a_hi_buf[ 1 ] = 0xCC;
                b_hi_buf[ 0 ] = 0x01;
                b_hi_buf[ 1 ] = 0xEA;
            }
            break;
        }
        case PROXIMITY15_TIMING_BUDGET_200MS:
        {
            if ( PROXIMITY15_DISTANCE_MODE_SHORT == distance_mode )
            {
                a_hi_buf[ 0 ] = 0x03;
                a_hi_buf[ 1 ] = 0xE1;
                b_hi_buf[ 0 ] = 0x04;
                b_hi_buf[ 1 ] = 0x96;
            }
            else
            {
                a_hi_buf[ 0 ] = 0x02;
                a_hi_buf[ 1 ] = 0xD9;
                b_hi_buf[ 0 ] = 0x02;
                b_hi_buf[ 1 ] = 0xF8;
            }
            break;
        }
        case PROXIMITY15_TIMING_BUDGET_500MS:
        {
            if ( PROXIMITY15_DISTANCE_MODE_SHORT == distance_mode )
            {
                a_hi_buf[ 0 ] = 0x05;
                a_hi_buf[ 1 ] = 0x91;
                b_hi_buf[ 0 ] = 0x05;
                b_hi_buf[ 1 ] = 0xC1;
            }
            else
            {
                a_hi_buf[ 0 ] = 0x04;
                a_hi_buf[ 1 ] = 0x8F;
                b_hi_buf[ 0 ] = 0x04;
                b_hi_buf[ 1 ] = 0xA4;
            }
            break;
        }
        default:
        {
            return PROXIMITY15_ERROR;
        }
    }
    
    error_flag |= proximity15_write_registers ( ctx, PROXIMITY15_REG_CFG_TIMEOUT_MACROP_A_HI, a_hi_buf, 2 );
    error_flag |= proximity15_write_registers ( ctx, PROXIMITY15_REG_CFG_TIMEOUT_MACROP_B_HI, b_hi_buf, 2 );

    return error_flag;
}

err_t proximity15_get_timing_budget ( proximity15_t *ctx, proximity15_timing_budget_t *time )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint16_t a_hi_data = 0;
    err_t error_flag = proximity15_read_registers ( ctx, PROXIMITY15_REG_CFG_TIMEOUT_MACROP_A_HI, rx_buf, 2 );
    a_hi_data = rx_buf[ 0 ];
    a_hi_data <<= 8;
    a_hi_data |= rx_buf[ 1 ];

    switch ( a_hi_data )
    {
        case 0x001D: 
        {
            *time = PROXIMITY15_TIMING_BUDGET_15MS;
            break;
        }
        case 0x0051:
        case 0x001E:
        {
            *time = PROXIMITY15_TIMING_BUDGET_20MS;
            break;
        }
        case 0x00D6:
        case 0x0060:
        {
            *time = PROXIMITY15_TIMING_BUDGET_33MS;
            break;
        }
        case 0x01AE:
        case 0x00AD:
        {
            *time = PROXIMITY15_TIMING_BUDGET_50MS;
            break;
        }
        case 0x02E1:
        case 0x01CC:
        {
            *time = PROXIMITY15_TIMING_BUDGET_100MS;
            break;
        }
        case 0x03E1:
        case 0x02D9:
        {
            *time = PROXIMITY15_TIMING_BUDGET_200MS;
            break;
        }
        case 0x0591:
        case 0x048F:
        {
            *time = PROXIMITY15_TIMING_BUDGET_500MS;
            break;
        }
        default:
        {
            return PROXIMITY15_ERROR;
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
