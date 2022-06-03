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
 * @file dcmotor22.c
 * @brief DC Motor 22 Click Driver.
 */

#include "dcmotor22.h"

/** 
 * @brief CRC8-ATM calculation function.
 * @details This function calculates CRC8-ATM with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8 + x2 + x +1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input True
 * @li @c  Reflect output False
 * @li @c  Final NO XOR
 * @param[in] data_buf : Array of bytes to calculate CRC8-ATM from.
 * @param[in] len : Number of bytes to calculate CRC8-ATM from.
 * @return Calculated CRC8-ATM byte.
 * @note None.
 */
static uint8_t dcmotor22_calculate_crc ( uint8_t *data_buf, uint8_t len );

void dcmotor22_cfg_setup ( dcmotor22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->a0 = HAL_PIN_NC;
    cfg->a1 = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DCMOTOR22_ADC_DEVICE_ADDRESS;
}

err_t dcmotor22_init ( dcmotor22_t *ctx, dcmotor22_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );
    
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->i2c_slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->i2c_slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    // Output pins
    digital_out_init( &ctx->a0, cfg->a0 );
    digital_out_init( &ctx->a1, cfg->a1 );
    digital_out_init( &ctx->en, cfg->en );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return UART_SUCCESS;
}

err_t dcmotor22_default_cfg ( dcmotor22_t *ctx ) 
{
    err_t error_flag = DCMOTOR22_OK;
    ctx->pwm_ab = 0;
    dcmotor22_reset_device ( ctx );
    Delay_100ms ( );
    dcmotor22_set_device_address ( ctx, DCMOTOR22_UART_DEVICE_ADDRESS_0 );
    
    error_flag |= dcmotor22_adc_write_setup_byte ( ctx, DCMOTOR22_ADC_SETUP_VREF_INT_REF_NC_ON | 
                                                        DCMOTOR22_ADC_SETUP_CLK_INT | 
                                                        DCMOTOR22_ADC_SETUP_UNIPOLAR | 
                                                        DCMOTOR22_ADC_SETUP_RST_NO_ACTION );
    error_flag |= dcmotor22_adc_write_config_byte ( ctx, DCMOTOR22_ADC_CONFIG_SCAN_CS0 | 
                                                         DCMOTOR22_ADC_CONFIG_CS0_AIN0 | 
                                                         DCMOTOR22_ADC_CONFIG_SINGLE_ENDED );
    Delay_100ms ( );
    error_flag |= dcmotor22_write_register ( ctx, DCMOTOR22_REG_GCONF, DCMOTOR22_GCONF_PWM_DIRECT | 
                                                                       DCMOTOR22_GCONF_EXTCAP_AVAILABLE | 
                                                                       DCMOTOR22_GCONF_PAR_MODE_DUAL_MOTOR );
    Delay_100ms ( );
    error_flag |= dcmotor22_write_register ( ctx, DCMOTOR22_REG_SLAVECONF, DCMOTOR22_SLAVECONF_SENDDELAY_40BIT );
    Delay_100ms ( );
    error_flag |= dcmotor22_write_register ( ctx, DCMOTOR22_REG_CURRENT_LIMIT, DCMOTOR22_CURRENT_LIMIT_IRUN_32_32 | 
                                                                               DCMOTOR22_CURRENT_LIMIT_EN_FREEWHEELING );
    Delay_100ms ( );
    error_flag |= dcmotor22_write_register ( ctx, DCMOTOR22_REG_PWM_AB, DCMOTOR22_PWM_DUTY_0 );
    Delay_100ms ( );
    error_flag |= dcmotor22_write_register ( ctx, DCMOTOR22_REG_CHOPCONF, DCMOTOR22_CHOPCONF_TBL_1 | 
                                                                          DCMOTOR22_CHOPCONF_ENABLEDRV );
    Delay_100ms ( );
    error_flag |= dcmotor22_write_register ( ctx, DCMOTOR22_REG_PWMCONF, DCMOTOR22_PWMCONF_FREEWHEEL_FREEWHEELING | 
                                                                         DCMOTOR22_PWMCONF_PWM_FREQ_2_683 );
    Delay_100ms ( );
    error_flag |= dcmotor22_write_register ( ctx, DCMOTOR22_REG_GSTAT, DCMOTOR22_GSTAT_CLEAR_ALL );
    Delay_100ms ( );
    return error_flag;
}

err_t dcmotor22_write_register ( dcmotor22_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = DCMOTOR22_SYNC_BYTE;
    data_buf[ 1 ] = ctx->uart_device_address;
    data_buf[ 2 ] = reg | DCMOTOR22_READ_WRITE_BIT;
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 7 ] = dcmotor22_calculate_crc ( data_buf, 7 );
    if ( 8 == uart_write ( &ctx->uart, data_buf, 8 ) )
    {
        return DCMOTOR22_OK;
    }
    return DCMOTOR22_ERROR;
}

err_t dcmotor22_read_register ( dcmotor22_t *ctx, uint8_t reg, uint32_t *data_out )
{
    uint8_t data_buf[ 12 ] = { 0 };
    uint16_t read_to_cnt = 0;
    uint16_t retry_send_to_cnt = 0;
    uint8_t byte_cnt = 0;
    data_buf[ 0 ] = DCMOTOR22_SYNC_BYTE;
    data_buf[ 1 ] = ctx->uart_device_address;
    data_buf[ 2 ] = reg & ( ~DCMOTOR22_READ_WRITE_BIT );
    data_buf[ 3 ] = dcmotor22_calculate_crc ( data_buf, 3 );
    uart_clear ( &ctx->uart );
    uart_write ( &ctx->uart, data_buf, 4 );
    Delay_1ms ( );
    for ( ; ; )
    {
        if ( uart_read ( &ctx->uart, &data_buf[ byte_cnt ], 1 ) > 0 )
        {
            byte_cnt++;
            if ( 12 == byte_cnt )
            {
                if ( ( DCMOTOR22_SYNC_BYTE == data_buf[ 4 ] ) &&
                     ( data_buf[ 11 ] == dcmotor22_calculate_crc ( &data_buf[ 4 ], 7 ) ) )
                {
                    *data_out = ( ( uint32_t ) data_buf[ 7 ] << 24 ) | ( ( uint32_t ) data_buf[ 8 ] << 16 ) | 
                                ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 10 ];
                    return DCMOTOR22_OK;
                }
                byte_cnt = 0;
            }
        }
        else
        {
            if ( ++read_to_cnt > DCMOTOR22_READ_TIMEOUT )
            {
                return DCMOTOR22_ERROR;
            }
            if ( ++retry_send_to_cnt > DCMOTOR22_RETRY_SEND_TIMEOUT )
            {
                retry_send_to_cnt = 0;
                byte_cnt = 0;
                data_buf[ 0 ] = DCMOTOR22_SYNC_BYTE;
                data_buf[ 1 ] = ctx->uart_device_address;
                data_buf[ 2 ] = reg & ( ~DCMOTOR22_READ_WRITE_BIT );
                data_buf[ 3 ] = dcmotor22_calculate_crc ( data_buf, 3 );
                uart_clear ( &ctx->uart );
                uart_write ( &ctx->uart, data_buf, 4 );
            }
            Delay_1ms ( );
        }
    }
}

err_t dcmotor22_adc_write_setup_byte ( dcmotor22_t *ctx, uint8_t setup_byte )
{
    ctx->adc_setup_byte = ( setup_byte & ( ~DCMOTOR22_ADC_REG_BIT_MASK ) ) | DCMOTOR22_ADC_REG_SETUP;
    return i2c_master_write( &ctx->i2c, &ctx->adc_setup_byte, 1 );
}

err_t dcmotor22_adc_write_config_byte ( dcmotor22_t *ctx, uint8_t config_byte )
{
    ctx->adc_config_byte = ( config_byte & ( ~DCMOTOR22_ADC_REG_BIT_MASK ) ) | DCMOTOR22_ADC_REG_CONFIG;
    return i2c_master_write( &ctx->i2c, &ctx->adc_config_byte, 1 );
}

err_t dcmotor22_adc_set_channel ( dcmotor22_t *ctx, uint8_t channel )
{
    if ( channel > DCMOTOR22_ADC_CHANNEL_1 )
    {
        return DCMOTOR22_ERROR;
    }
    ctx->adc_config_byte &= ~DCMOTOR22_ADC_CONFIG_CS0_BIT_MASK;
    if ( DCMOTOR22_ADC_CHANNEL_1 == channel )
    {
        ctx->adc_config_byte |= DCMOTOR22_ADC_CONFIG_CS0_AIN1;
    }
    return dcmotor22_adc_write_config_byte( ctx, ctx->adc_config_byte );
}

err_t dcmotor22_adc_get_voltage ( dcmotor22_t *ctx, float *voltage )
{
    uint8_t rx_buf[ 2 ];
    int16_t raw_adc;
    err_t error_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
    raw_adc = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
    raw_adc &= DCMOTOR22_ADC_RESOLUTION;
    if ( ( DCMOTOR22_ADC_SETUP_BIPOLAR == ( ctx->adc_setup_byte & DCMOTOR22_ADC_SETUP_UNI_BIP_BIT_MASK ) ) && 
         ( DCMOTOR22_ADC_CONFIG_DIFFERENTIAL == ( ctx->adc_config_byte & DCMOTOR22_ADC_CONFIG_SGL_DIF_BIT_MASK ) ) )
    {
        raw_adc = ( int16_t ) ( raw_adc << 4 ) >> 4;
        *voltage = ( ( float ) raw_adc / DCMOTOR22_ADC_RESOLUTION ) * DCMOTOR22_ADC_VREF;
    }
    else
    {
        *voltage = ( ( float ) raw_adc / DCMOTOR22_ADC_RESOLUTION ) * DCMOTOR22_ADC_VREF;
    }
    return error_flag;
}

err_t dcmotor22_get_motor_current ( dcmotor22_t *ctx, uint8_t motor_sel, float *current )
{
    if ( DCMOTOR22_MOTOR_A == motor_sel )
    {
        if ( DCMOTOR22_ERROR == dcmotor22_adc_set_channel ( ctx, DCMOTOR22_ADC_CHANNEL_1 ) )
        {
            return DCMOTOR22_ERROR;
        }
    }
    else if ( DCMOTOR22_MOTOR_B == motor_sel )
    {
        if ( DCMOTOR22_ERROR == dcmotor22_adc_set_channel ( ctx, DCMOTOR22_ADC_CHANNEL_0 ) )
        {
            return DCMOTOR22_ERROR;
        }
    }
    else
    {
        return DCMOTOR22_ERROR;
    }
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t conv_cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( conv_cnt < DCMOTOR22_NUM_CONVERSIONS )
    {
        if ( DCMOTOR22_OK == dcmotor22_adc_get_voltage( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            conv_cnt++;
        }
        else
        {
            timeout_cnt++;
            if ( timeout_cnt >= DCMOTOR22_NUM_CONVERSIONS )
            {
                return DCMOTOR22_ERROR;
            }
        }
    }
    *current = voltage_sum / DCMOTOR22_NUM_CONVERSIONS / DCMOTOR22_RSENSE;
    return DCMOTOR22_OK;
}

err_t dcmotor22_set_motor_pwm ( dcmotor22_t *ctx, uint8_t motor_sel, int16_t pwm_duty )
{
    if ( ( pwm_duty > DCMOTOR22_MAX_PWM ) || ( pwm_duty < DCMOTOR22_MIN_PWM ) || ( motor_sel > DCMOTOR22_MOTOR_B ) )
    {
        return DCMOTOR22_ERROR;
    }
    pwm_duty &= DCMOTOR22_PWM_RES;
    if ( DCMOTOR22_MOTOR_A == motor_sel )
    {
        ctx->pwm_ab &= ( ~( ( uint32_t ) DCMOTOR22_PWM_RES ) );
        ctx->pwm_ab |= pwm_duty;
    }
    else
    {
        ctx->pwm_ab &= ( ~( ( uint32_t ) DCMOTOR22_PWM_RES << 16 ) );
        ctx->pwm_ab |= ( ( uint32_t ) pwm_duty << 16 );
    }
    return dcmotor22_write_register ( ctx, DCMOTOR22_REG_PWM_AB, ctx->pwm_ab );
}

void dcmotor22_enable_device ( dcmotor22_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void dcmotor22_disable_device ( dcmotor22_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void dcmotor22_reset_device ( dcmotor22_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
    digital_out_high ( &ctx->en );
}

void dcmotor22_set_device_address ( dcmotor22_t *ctx, uint8_t addr )
{
    switch ( addr & DCMOTOR22_UART_DEVICE_ADDRESS_MASK )
    {
        case DCMOTOR22_UART_DEVICE_ADDRESS_0:
        {
            digital_out_low ( &ctx->a0 );
            digital_out_low ( &ctx->a1 );
            ctx->uart_device_address = DCMOTOR22_UART_DEVICE_ADDRESS_0;
            break;
        }
        case DCMOTOR22_UART_DEVICE_ADDRESS_1:
        {
            digital_out_high ( &ctx->a0 );
            digital_out_low ( &ctx->a1 );
            ctx->uart_device_address = DCMOTOR22_UART_DEVICE_ADDRESS_1;
            break;
        }
        case DCMOTOR22_UART_DEVICE_ADDRESS_2:
        {
            digital_out_low ( &ctx->a0 );
            digital_out_high ( &ctx->a1 );
            ctx->uart_device_address = DCMOTOR22_UART_DEVICE_ADDRESS_2;
            break;
        }
        case DCMOTOR22_UART_DEVICE_ADDRESS_3:
        {
            digital_out_high ( &ctx->a0 );
            digital_out_high ( &ctx->a1 );
            ctx->uart_device_address = DCMOTOR22_UART_DEVICE_ADDRESS_3;
            break;
        }
    }
}

uint8_t dcmotor22_get_int_pin ( dcmotor22_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

static uint8_t dcmotor22_calculate_crc ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    for ( uint8_t cnt_byte = 0; cnt_byte < len; cnt_byte++ ) 
    {
        uint8_t curr_byte = data_buf[ cnt_byte ];
        for ( uint8_t cnt_bit = 0; cnt_bit < 8; cnt_bit++ ) 
        {
            if ( ( crc >> 7 ) ^ ( curr_byte & 0x01 ) )
            {    
                crc = ( uint8_t )( ( crc << 1 ) ^ 0x07 );
            }
            else
            {
                 crc <<= 1;
            }
            curr_byte >>= 1;
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
