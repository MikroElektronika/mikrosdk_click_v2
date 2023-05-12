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
 * @file dcmotor26.c
 * @brief DC Motor 26 Click Driver.
 */

#include "dcmotor26.h"

/**
 * @brief Dummy data and SPI read write bit.
 * @details Definition of dummy data and SPI read write bit.
 */
#define DCMOTOR26_DUMMY                 0x00
#define DCMOTOR26_SPI_READ_WRITE_BIT    0x80
#define DCMOTOR26_ERROR_FLAG_BIT        0x80

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x1D (x4 + x3 + x2 + 1)
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final result
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t dcmotor26_calculate_crc ( uint8_t *data_buf, uint8_t len );

void dcmotor26_cfg_setup ( dcmotor26_cfg_t *cfg ) 
{
    cfg->sda  = HAL_PIN_NC;
    cfg->scl  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->cm   = HAL_PIN_NC;
    cfg->slp  = HAL_PIN_NC;
    cfg->clk  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DCMOTOR26_DEVICE_ADDRESS_A1A0_00;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = DCMOTOR26_VREF_3V3;
}

err_t dcmotor26_init ( dcmotor26_t *ctx, dcmotor26_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DCMOTOR26_DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
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
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->cm;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->slp, cfg->slp );
    digital_out_init( &ctx->clk, cfg->clk );
    digital_out_low ( &ctx->slp );
    digital_out_low ( &ctx->clk );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return DCMOTOR26_OK;
}

err_t dcmotor26_default_cfg ( dcmotor26_t *ctx ) 
{
    err_t error_flag = DCMOTOR26_OK;
    DCMOTOR26_SET_DATA_SAMPLE_EDGE;
    dcmotor26_wake_up_device ( ctx );
    Delay_100ms ( );
    // Configure EN1, EN2, and CM_SEL pins as OUTPUT, DIAG1, DIAG2, and SLP pins as INPUT
    error_flag |= dcmotor26_pca9538a_write_register ( ctx, DCMOTOR26_REG_CONFIG, DCMOTOR26_DEFAULT_CONFIG );
    error_flag |= dcmotor26_set_en1_pin ( ctx, DCMOTOR26_PIN_HIGH_LEVEL );
    error_flag |= dcmotor26_set_en2_pin ( ctx, DCMOTOR26_PIN_HIGH_LEVEL );
    error_flag |= dcmotor26_set_cm_sel_pin ( ctx, DCMOTOR26_PIN_LOW_LEVEL );
    // Disable SPI disruption
    error_flag |= dcmotor26_write_register ( ctx, DCMOTOR26_REG_CONFIG1, DCMOTOR26_CONFIG12_SPI_DISR_DISABLE | 
                                                                         DCMOTOR26_CONFIG12_OPMODE_DISR_CONTINUE );
    // Set channel config
    error_flag |= dcmotor26_set_ch1_operation_mode ( ctx, DCMOTOR26_MODE_OUTPUT_OFF );
    error_flag |= dcmotor26_set_ch1_drive_frequency ( ctx, DCMOTOR26_CONFIG56_DRV_FREQ_MAX );
    error_flag |= dcmotor26_set_ch1_duty_period ( ctx, 0u );
    error_flag |= dcmotor26_set_ch2_operation_mode ( ctx, DCMOTOR26_MODE_OUTPUT_OFF );
    error_flag |= dcmotor26_set_ch2_drive_frequency ( ctx, DCMOTOR26_CONFIG56_DRV_FREQ_MAX );
    error_flag |= dcmotor26_set_ch2_duty_period ( ctx, 0u );
    // Clear status registers
    error_flag |= dcmotor26_write_register ( ctx, DCMOTOR26_REG_STATUS1, 0ul );
    error_flag |= dcmotor26_write_register ( ctx, DCMOTOR26_REG_STATUS2, 0ul );
    error_flag |= dcmotor26_write_register ( ctx, DCMOTOR26_REG_STATUS3, 0ul );
    return error_flag;
}

err_t dcmotor26_write_register ( dcmotor26_t *ctx, uint8_t reg, uint32_t data_in )
{
    err_t error_flag = DCMOTOR26_OK;
    uint8_t write_buf[ 5 ] = { 0 };
    uint8_t read_buf[ 5 ] = { 0 };
    write_buf[ 0 ] = reg | DCMOTOR26_SPI_READ_WRITE_BIT;
    write_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    write_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    write_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    write_buf[ 4 ] = dcmotor26_calculate_crc ( write_buf, 4 );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, write_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms ( );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, read_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    write_buf[ 0 ] &= ( ~DCMOTOR26_SPI_READ_WRITE_BIT );
    if ( ( DCMOTOR26_ERROR == error_flag ) ||
         ( read_buf[ 0 ] & DCMOTOR26_ERROR_FLAG_BIT ) || 
         ( memcmp( write_buf, read_buf, 4 ) ) || 
         ( read_buf[ 4 ] != dcmotor26_calculate_crc ( read_buf, 4 ) ) )
    {
        return DCMOTOR26_ERROR;
    }
    return DCMOTOR26_OK;
}

err_t dcmotor26_read_register ( dcmotor26_t *ctx, uint8_t reg, uint32_t *data_out )
{
    err_t error_flag = DCMOTOR26_OK;
    uint8_t write_buf[ 5 ] = { 0 };
    uint8_t read_buf[ 5 ] = { 0 };
    write_buf[ 0 ] = reg & ( ~DCMOTOR26_SPI_READ_WRITE_BIT );
    write_buf[ 1 ] = DCMOTOR26_DUMMY;
    write_buf[ 2 ] = DCMOTOR26_DUMMY;
    write_buf[ 3 ] = DCMOTOR26_DUMMY;
    write_buf[ 4 ] = dcmotor26_calculate_crc ( write_buf, 4 );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, write_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms ( );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, read_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( DCMOTOR26_ERROR == error_flag ) ||
         ( write_buf[ 0 ] != read_buf[ 0 ] ) || 
         ( read_buf[ 4 ] != dcmotor26_calculate_crc ( read_buf, 4 ) ) )
    {
        return DCMOTOR26_ERROR;
    }
    *data_out = ( ( uint32_t ) read_buf[ 1 ] << 16 ) | ( ( uint16_t ) read_buf[ 2 ] << 8 ) | read_buf[ 3 ];
    return DCMOTOR26_OK;
}

err_t dcmotor26_pca9538a_write_register ( dcmotor26_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t dcmotor26_pca9538a_read_register ( dcmotor26_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void dcmotor26_enter_sleep_mode ( dcmotor26_t *ctx )
{
    digital_out_low ( &ctx->slp );
}

void dcmotor26_wake_up_device ( dcmotor26_t *ctx )
{
    digital_out_high ( &ctx->slp );
}

uint8_t dcmotor26_get_int_pin ( dcmotor26_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void dcmotor26_set_clk_pin ( dcmotor26_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->clk, state );
}

err_t dcmotor26_set_en1_pin ( dcmotor26_t *ctx, uint8_t state )
{
    if ( state > DCMOTOR26_PIN_HIGH_LEVEL )
    {
        return DCMOTOR26_ERROR;
    }
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( state == ( ( reg_data & DCMOTOR26_EN1_PIN ) >> 2 ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_EN1_PIN;
    reg_data |= ( state << 2 );
    return dcmotor26_pca9538a_write_register ( ctx, DCMOTOR26_REG_OUTPUT, reg_data );
}

err_t dcmotor26_get_en1_pin ( dcmotor26_t *ctx, uint8_t *state )
{
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    *state = ( reg_data & DCMOTOR26_EN1_PIN ) >> 2;
    return DCMOTOR26_OK;
}

err_t dcmotor26_set_en2_pin ( dcmotor26_t *ctx, uint8_t state )
{
    if ( state > DCMOTOR26_PIN_HIGH_LEVEL )
    {
        return DCMOTOR26_ERROR;
    }
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( state == ( ( reg_data & DCMOTOR26_EN2_PIN ) >> 3 ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_EN2_PIN;
    reg_data |= ( state << 3 );
    return dcmotor26_pca9538a_write_register ( ctx, DCMOTOR26_REG_OUTPUT, reg_data );
}

err_t dcmotor26_get_en2_pin ( dcmotor26_t *ctx, uint8_t *state )
{
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    *state = ( reg_data & DCMOTOR26_EN2_PIN ) >> 3;
    return DCMOTOR26_OK;
}

err_t dcmotor26_set_cm_sel_pin ( dcmotor26_t *ctx, uint8_t state )
{
    if ( state > DCMOTOR26_PIN_HIGH_LEVEL )
    {
        return DCMOTOR26_ERROR;
    }
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( state == ( ( reg_data & DCMOTOR26_CM_SEL_PIN ) >> 4 ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_CM_SEL_PIN;
    reg_data |= ( state << 4 );
    return dcmotor26_pca9538a_write_register ( ctx, DCMOTOR26_REG_OUTPUT, reg_data );
}

err_t dcmotor26_get_cm_sel_pin ( dcmotor26_t *ctx, uint8_t *state )
{
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    *state = ( reg_data & DCMOTOR26_CM_SEL_PIN ) >> 4;
    return DCMOTOR26_OK;
}

err_t dcmotor26_get_diag1_pin ( dcmotor26_t *ctx, uint8_t *state )
{
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_INPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    *state = reg_data & DCMOTOR26_DIAG1_PIN;
    return DCMOTOR26_OK;
}

err_t dcmotor26_get_diag2_pin ( dcmotor26_t *ctx, uint8_t *state )
{
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_INPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    *state = ( reg_data & DCMOTOR26_DIAG2_PIN ) >> 1;
    return DCMOTOR26_OK;
}

err_t dcmotor26_get_sleep_pin ( dcmotor26_t *ctx, uint8_t *state )
{
    uint8_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_pca9538a_read_register ( ctx, DCMOTOR26_REG_INPUT, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    *state = ( reg_data & DCMOTOR26_SLP_PIN ) >> 5;
    return DCMOTOR26_OK;
}

err_t dcmotor26_read_an_pin_value ( dcmotor26_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t dcmotor26_read_an_pin_voltage ( dcmotor26_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t dcmotor26_get_motor_current ( dcmotor26_t *ctx, float *current )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t conv_cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( conv_cnt < DCMOTOR26_NUM_CONVERSIONS )
    {
        if ( DCMOTOR26_OK == dcmotor26_read_an_pin_voltage( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            conv_cnt++;
        }
        else
        {
            timeout_cnt++;
            if ( timeout_cnt >= DCMOTOR26_NUM_CONVERSIONS )
            {
                return DCMOTOR26_ERROR;
            }
        }
    }
    *current = voltage_sum / DCMOTOR26_NUM_CONVERSIONS / ( DCMOTOR26_RSENSE * DCMOTOR26_VOLTAGE_TO_CURRENT );
    return DCMOTOR26_OK;
}

err_t dcmotor26_set_ch1_operation_mode ( dcmotor26_t *ctx, uint8_t mode )
{
    if ( mode > DCMOTOR26_CONFIG56_MOTOR_OPMODE_MAX )
    {
        return DCMOTOR26_ERROR;
    }
    uint32_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_read_register ( ctx, DCMOTOR26_REG_CONFIG5, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( mode == ( ( reg_data & DCMOTOR26_CONFIG56_MOTOR_OPMODE_MASK ) >> DCMOTOR26_CONFIG56_MOTOR_OPMODE_SHIFT ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_CONFIG56_MOTOR_OPMODE_MASK;
    reg_data |= ( ( uint32_t ) mode << DCMOTOR26_CONFIG56_MOTOR_OPMODE_SHIFT );
    return dcmotor26_write_register ( ctx, DCMOTOR26_REG_CONFIG5, reg_data );
}

err_t dcmotor26_set_ch2_operation_mode ( dcmotor26_t *ctx, uint8_t mode )
{
    if ( mode > DCMOTOR26_CONFIG56_MOTOR_OPMODE_MAX )
    {
        return DCMOTOR26_ERROR;
    }
    uint32_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_read_register ( ctx, DCMOTOR26_REG_CONFIG6, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( mode == ( ( reg_data & DCMOTOR26_CONFIG56_MOTOR_OPMODE_MASK ) >> DCMOTOR26_CONFIG56_MOTOR_OPMODE_SHIFT ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_CONFIG56_MOTOR_OPMODE_MASK;
    reg_data |= ( ( uint32_t ) mode << DCMOTOR26_CONFIG56_MOTOR_OPMODE_SHIFT );
    return dcmotor26_write_register ( ctx, DCMOTOR26_REG_CONFIG6, reg_data );
}

err_t dcmotor26_set_ch1_drive_frequency ( dcmotor26_t *ctx, uint16_t drv_freq )
{
    if ( drv_freq > DCMOTOR26_CONFIG56_DRV_FREQ_MAX )
    {
        return DCMOTOR26_ERROR;
    }
    uint32_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_read_register ( ctx, DCMOTOR26_REG_CONFIG5, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( drv_freq == ( ( reg_data & DCMOTOR26_CONFIG56_DRV_FREQ_MASK ) >> DCMOTOR26_CONFIG56_DRV_FREQ_SHIFT ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_CONFIG56_DRV_FREQ_MASK;
    reg_data |= ( ( uint32_t ) drv_freq << DCMOTOR26_CONFIG56_DRV_FREQ_SHIFT );
    return dcmotor26_write_register ( ctx, DCMOTOR26_REG_CONFIG5, reg_data );
}

err_t dcmotor26_set_ch2_drive_frequency ( dcmotor26_t *ctx, uint16_t drv_freq )
{
    if ( drv_freq > DCMOTOR26_CONFIG56_DRV_FREQ_MAX )
    {
        return DCMOTOR26_ERROR;
    }
    uint32_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_read_register ( ctx, DCMOTOR26_REG_CONFIG6, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( drv_freq == ( ( reg_data & DCMOTOR26_CONFIG56_DRV_FREQ_MASK ) >> DCMOTOR26_CONFIG56_DRV_FREQ_SHIFT ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_CONFIG56_DRV_FREQ_MASK;
    reg_data |= ( ( uint32_t ) drv_freq << DCMOTOR26_CONFIG56_DRV_FREQ_SHIFT );
    return dcmotor26_write_register ( ctx, DCMOTOR26_REG_CONFIG6, reg_data );
}

err_t dcmotor26_set_ch1_duty_period ( dcmotor26_t *ctx, uint16_t duty_period )
{
    if ( duty_period > DCMOTOR26_CONFIG56_DUTY_PERIOD_MAX )
    {
        return DCMOTOR26_ERROR;
    }
    uint32_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_read_register ( ctx, DCMOTOR26_REG_CONFIG5, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( duty_period == ( ( reg_data & DCMOTOR26_CONFIG56_DUTY_PERIOD_MASK ) >> DCMOTOR26_CONFIG56_DUTY_PERIOD_SHIFT ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_CONFIG56_DUTY_PERIOD_MASK;
    reg_data |= ( ( uint32_t ) duty_period << DCMOTOR26_CONFIG56_DUTY_PERIOD_SHIFT );
    return dcmotor26_write_register ( ctx, DCMOTOR26_REG_CONFIG5, reg_data );
}

err_t dcmotor26_set_ch2_duty_period ( dcmotor26_t *ctx, uint16_t duty_period )
{
    if ( duty_period > DCMOTOR26_CONFIG56_DUTY_PERIOD_MAX )
    {
        return DCMOTOR26_ERROR;
    }
    uint32_t reg_data;
    if ( DCMOTOR26_ERROR == dcmotor26_read_register ( ctx, DCMOTOR26_REG_CONFIG6, &reg_data ) )
    {
        return DCMOTOR26_ERROR;
    }
    if ( duty_period == ( ( reg_data & DCMOTOR26_CONFIG56_DUTY_PERIOD_MASK ) >> DCMOTOR26_CONFIG56_DUTY_PERIOD_SHIFT ) )
    {
        return DCMOTOR26_OK;
    }
    reg_data &= ~DCMOTOR26_CONFIG56_DUTY_PERIOD_MASK;
    reg_data |= ( ( uint32_t ) duty_period << DCMOTOR26_CONFIG56_DUTY_PERIOD_SHIFT );
    return dcmotor26_write_register ( ctx, DCMOTOR26_REG_CONFIG6, reg_data );
}

static uint8_t dcmotor26_calculate_crc ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    for ( uint8_t byte_cnt = 0; byte_cnt < len; byte_cnt++ ) 
    {
        crc ^= data_buf[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 )
            {    
                crc = ( uint8_t ) ( ( crc << 1 ) ^ 0x1D );
            }
            else
            {
                crc <<= 1;
            }    
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
