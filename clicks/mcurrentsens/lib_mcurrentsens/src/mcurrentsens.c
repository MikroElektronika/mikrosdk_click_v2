/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file mcurrentsens.c
 * @brief mCurrent Sens Click Driver.
 */

#include "mcurrentsens.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief mCurrent Sens sign extend 24-bit value function.
 * @details This function converts a 24-bit unsigned value to signed 32-bit format.
 * @param[in] value_in : 24-bit raw value.
 * @return Signed 32-bit value.
 * @note None.
 */
static int32_t mcurrentsens_sign_ext_24 ( uint32_t value_in );

/**
 * @brief mCurrent Sens clamp signed 24-bit value function.
 * @details This function limits a signed value to 24-bit range.
 * @param[in] value_in : Input value.
 * @return Clamped 24-bit signed value.
 * @note None.
 */
static int32_t mcurrentsens_clamp_s24 ( int32_t value_in );

/**
 * @brief mCurrent Sens clamp unsigned 24-bit value function.
 * @details This function limits an unsigned value to 24-bit range.
 * @param[in] value_in : Input value.
 * @return Clamped 24-bit unsigned value.
 * @note None.
 */
static uint32_t mcurrentsens_clamp_u24 ( uint32_t value_in );

void mcurrentsens_cfg_setup ( mcurrentsens_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->clk  = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = MCURRENTSENS_DEVICE_ADDRESS;
}

err_t mcurrentsens_init ( mcurrentsens_t *ctx, mcurrentsens_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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

    digital_in_init( &ctx->irq, cfg->irq );
    digital_in_init( &ctx->clk, cfg->clk );

    return MCURRENTSENS_OK;
}

err_t mcurrentsens_default_cfg ( mcurrentsens_t *ctx ) 
{
    err_t error_flag = MCURRENTSENS_OK;
    
    if ( MCURRENTSENS_OK != mcurrentsens_check_com ( ctx ) )
    {
        return MCURRENTSENS_ERROR;
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_LOCK, MCURRENTSENS_LOCK_UNLOCK );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_write_reg24( ctx, MCURRENTSENS_REG_OFFSETCAL, MCURRENTSENS_OFFSETCAL_DEFAULT );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_write_reg24( ctx, MCURRENTSENS_REG_GAINCAL, MCURRENTSENS_GAINCAL_DEFAULT );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_CONFIG0, MCURRENTSENS_CONFIG0_VREF_SEL_INT | 
                                                                            MCURRENTSENS_CONFIG0_PARTIAL_SHUTDOWN_DIS | 
                                                                            MCURRENTSENS_CONFIG0_CLK_SEL_INT_NO_OUT | 
                                                                            MCURRENTSENS_CONFIG0_CS_SEL_NONE | 
                                                                            MCURRENTSENS_CONFIG0_ADC_MODE_CONVERSION );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_CONFIG1, MCURRENTSENS_CONFIG1_PRE_DIV_1 | 
                                                                            MCURRENTSENS_CONFIG1_OSR_98304 );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_CONFIG2, MCURRENTSENS_CONFIG2_BOOST_X1 | 
                                                                            MCURRENTSENS_CONFIG2_GAIN_X1 | 
                                                                            MCURRENTSENS_CONFIG2_AZ_MUX_DIS | 
                                                                            MCURRENTSENS_CONFIG2_AZ_REF_DIS | 
                                                                            MCURRENTSENS_CONFIG2_RESERVED );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_CONFIG3, MCURRENTSENS_CONFIG3_CONV_MODE_ONE_SHOT_STBY | 
                                                                            MCURRENTSENS_CONFIG3_DATA_FORMAT_24BIT | 
                                                                            MCURRENTSENS_CONFIG3_CRC_FORMAT_16BIT | 
                                                                            MCURRENTSENS_CONFIG3_EN_CRCCOM_DIS | 
                                                                            MCURRENTSENS_CONFIG3_EN_OFFCAL_DIS | 
                                                                            MCURRENTSENS_CONFIG3_EN_GAINCAL_DIS );
    }

    return error_flag;
}

err_t mcurrentsens_write_reg ( mcurrentsens_t *ctx, uint8_t reg, uint8_t data_in )
{
    return mcurrentsens_write_regs ( ctx, reg, &data_in, 1 );
}

err_t mcurrentsens_read_reg ( mcurrentsens_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return mcurrentsens_read_regs ( ctx, reg, data_out, 1 );
}

err_t mcurrentsens_write_regs ( mcurrentsens_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t cmd = 0;
    uint8_t status = 0;

    /* Command byte is transferred separately in order to capture the status byte. */
    cmd = MCURRENTSENS_CMD_DEV_ADDR |
          ( reg << MCURRENTSENS_CMD_REG_ADDR_SHIFT ) |
          MCURRENTSENS_CMD_TYPE_INC_WRITE;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, cmd );
    error_flag = spi_master_read( &ctx->spi, &status, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    if ( ( len > 0 ) && ( NULL != data_in ) )
    {
        error_flag |= spi_master_write( &ctx->spi, data_in, len );
    }
    spi_master_deselect_device( ctx->chip_select );
    if ( ( MCURRENTSENS_CMD_DEV_ADDR != ( ( status << 2 ) & MCURRENTSENS_CMD_DEV_ADDR_MASK ) ) ||
         ( ( status >> 4 ) & 0x01 ) == ( ( status >> 3 ) & 0x01 ) )
    {
        // Device address acknowledge bits mismatched
        error_flag = MCURRENTSENS_ERROR;
    }

    return error_flag;
}

err_t mcurrentsens_read_regs ( mcurrentsens_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t cmd = 0;
    uint8_t status = 0;

    /* Command byte is transferred separately in order to capture the status byte. */
    cmd = MCURRENTSENS_CMD_DEV_ADDR |
          ( reg << MCURRENTSENS_CMD_REG_ADDR_SHIFT ) |
          MCURRENTSENS_CMD_TYPE_INC_READ;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, cmd );
    error_flag = spi_master_read( &ctx->spi, &status, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    if ( ( len > 0 ) && ( NULL != data_out ) )
    {
        error_flag |= spi_master_read( &ctx->spi, data_out, len );
    }
    spi_master_deselect_device( ctx->chip_select );
    if ( ( MCURRENTSENS_CMD_DEV_ADDR != ( ( status << 2 ) & MCURRENTSENS_CMD_DEV_ADDR_MASK ) ) ||
         ( ( status >> 4 ) & 0x01 ) == ( ( status >> 3 ) & 0x01 ) )
    {
        // Device address acknowledge bits mismatched
        error_flag = MCURRENTSENS_ERROR;
    }

    return error_flag;
}

err_t mcurrentsens_write_reg16 ( mcurrentsens_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );

    return mcurrentsens_write_regs ( ctx, reg, data_buf, 2 );
}

err_t mcurrentsens_read_reg16 ( mcurrentsens_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t data_buf[ 2 ] = { 0 };

    error_flag = mcurrentsens_read_regs ( ctx, reg, data_buf, 2 );

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) |
                    ( ( uint16_t ) data_buf[ 1 ] );
    }

    return error_flag;
}

err_t mcurrentsens_write_reg24 ( mcurrentsens_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );

    return mcurrentsens_write_regs ( ctx, reg, data_buf, 3 );
}

err_t mcurrentsens_read_reg24 ( mcurrentsens_t *ctx, uint8_t reg, uint32_t *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t data_buf[ 3 ] = { 0 };

    error_flag = mcurrentsens_read_regs ( ctx, reg, data_buf, 3 );

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = ( ( uint32_t ) data_buf[ 0 ] << 16 ) |
                    ( ( uint32_t ) data_buf[ 1 ] << 8 ) |
                    ( ( uint32_t ) data_buf[ 2 ] );
    }

    return error_flag;
}

err_t mcurrentsens_send_fast_cmd ( mcurrentsens_t *ctx, uint8_t cmd )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t status = 0;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, cmd );
    error_flag = spi_master_read( &ctx->spi, &status, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( MCURRENTSENS_CMD_DEV_ADDR != ( ( status << 2 ) & MCURRENTSENS_CMD_DEV_ADDR_MASK ) ) ||
         ( ( status >> 4 ) & 0x01 ) == ( ( status >> 3 ) & 0x01 ) )
    {
        // Device address acknowledge bits mismatched
        error_flag = MCURRENTSENS_ERROR;
    }

    return error_flag;
}

err_t mcurrentsens_check_com ( mcurrentsens_t *ctx )
{
    uint16_t res_16 = 0;
    // RESERVED_16 register looks like a classic device ID register
    if ( MCURRENTSENS_OK == mcurrentsens_read_reg16( ctx, MCURRENTSENS_REG_RESERVED_16, &res_16 ) )
    {
        if ( MCURRENTSENS_RESERVED_16_DEFAULT == res_16 )
        {
            return MCURRENTSENS_OK;
        }
    }
    return MCURRENTSENS_ERROR;
}

err_t mcurrentsens_set_mux ( mcurrentsens_t *ctx, uint8_t vin_p, uint8_t vin_n )
{
    uint8_t data_in = ( vin_p << MCURRENTSENS_MUX_VIN_P_SHIFT ) |
                      ( vin_n << MCURRENTSENS_MUX_VIN_N_SHIFT );

    return mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_MUX, data_in );
}

err_t mcurrentsens_set_gain ( mcurrentsens_t *ctx, uint8_t gain )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t config2 = 0;

    error_flag = mcurrentsens_read_reg( ctx, MCURRENTSENS_REG_CONFIG2, &config2 );

    if ( MCURRENTSENS_OK == error_flag )
    {
        config2 &= ( ~MCURRENTSENS_CONFIG2_GAIN_MASK );
        config2 |= ( gain & MCURRENTSENS_CONFIG2_GAIN_MASK );
        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_CONFIG2, config2 );
    }

    return error_flag;
}

err_t mcurrentsens_set_osr ( mcurrentsens_t *ctx, uint8_t osr )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t config1 = 0;

    error_flag = mcurrentsens_read_reg( ctx, MCURRENTSENS_REG_CONFIG1, &config1 );

    if ( MCURRENTSENS_OK == error_flag )
    {
        config1 &= ( ~MCURRENTSENS_CONFIG1_OSR_MASK );
        config1 |= ( osr & MCURRENTSENS_CONFIG1_OSR_MASK );
        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_CONFIG1, config1 );
    }

    return error_flag;
}

err_t mcurrentsens_set_mode ( mcurrentsens_t *ctx, uint8_t mode )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t config0 = 0;

    error_flag = mcurrentsens_read_reg( ctx, MCURRENTSENS_REG_CONFIG0, &config0 );

    if ( MCURRENTSENS_OK == error_flag )
    {
        config0 &= ( ~MCURRENTSENS_CONFIG0_ADC_MODE_MASK );
        config0 |= ( mode & MCURRENTSENS_CONFIG0_ADC_MODE_MASK );
        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_CONFIG0, config0 );
    }

    return error_flag;
}

err_t mcurrentsens_get_irq ( mcurrentsens_t *ctx, uint8_t *data_out )
{
    return mcurrentsens_read_reg( ctx, MCURRENTSENS_REG_IRQ, data_out );
}

err_t mcurrentsens_set_offset_cal ( mcurrentsens_t *ctx, int32_t data_in )
{
    return mcurrentsens_write_reg24( ctx, MCURRENTSENS_REG_OFFSETCAL, ( uint32_t ) data_in );
}

err_t mcurrentsens_get_offset_cal ( mcurrentsens_t *ctx, int32_t *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint32_t offset_cal = 0;

    error_flag = mcurrentsens_read_reg24( ctx, MCURRENTSENS_REG_OFFSETCAL, &offset_cal );

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = mcurrentsens_sign_ext_24 ( offset_cal );
    }

    return error_flag;
}

err_t mcurrentsens_set_gain_cal ( mcurrentsens_t *ctx, uint32_t data_in )
{
    return mcurrentsens_write_reg24( ctx, MCURRENTSENS_REG_GAINCAL, data_in );
}

err_t mcurrentsens_get_gain_cal ( mcurrentsens_t *ctx, uint32_t *data_out )
{
    return mcurrentsens_read_reg24( ctx, MCURRENTSENS_REG_GAINCAL, data_out );
}

err_t mcurrentsens_en_dig_cal ( mcurrentsens_t *ctx, uint8_t en_offset, uint8_t en_gain )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t config3 = 0;

    error_flag = mcurrentsens_read_reg( ctx, MCURRENTSENS_REG_CONFIG3, &config3 );

    if ( MCURRENTSENS_OK == error_flag )
    {
        config3 &= ~( MCURRENTSENS_CONFIG3_EN_OFFCAL_MASK | MCURRENTSENS_CONFIG3_EN_GAINCAL_MASK );

        if ( en_offset )
        {
            config3 |= MCURRENTSENS_CONFIG3_EN_OFFCAL_EN;
        }

        if ( en_gain )
        {
            config3 |= MCURRENTSENS_CONFIG3_EN_GAINCAL_EN;
        }

        error_flag = mcurrentsens_write_reg( ctx, MCURRENTSENS_REG_CONFIG3, config3 );
    }

    return error_flag;
}

err_t mcurrentsens_apply_calib ( mcurrentsens_t *ctx, mcurrentsens_calib_t cal )
{
    err_t error_flag = MCURRENTSENS_OK;

    error_flag = mcurrentsens_set_offset_cal( ctx, cal.offset_cal );

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_set_gain_cal( ctx, cal.gain_cal );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_en_dig_cal( ctx, MCURRENTSENS_CONFIG3_EN_OFFCAL_EN, 
                                                   MCURRENTSENS_CONFIG3_EN_GAINCAL_EN );
    }

    return error_flag;
}

err_t mcurrentsens_wait_data_ready ( mcurrentsens_t *ctx )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t irq_data = 0;
    uint16_t timeout_cnt = 0;

    while ( MCURRENTSENS_OK == error_flag )
    {
        Delay_1ms ( );
        if ( !mcurrentsens_get_irq_pin( ctx ) )
        {
            error_flag = mcurrentsens_get_irq( ctx, &irq_data );
            if ( MCURRENTSENS_OK == error_flag )
            {
                if ( irq_data & MCURRENTSENS_IRQ_DR_STATUS )
                {
                    break;
                }
            }
        }
        if ( ++timeout_cnt > MCURRENTSENS_DATA_READY_TIMEOUT_MS )
        {
            error_flag = MCURRENTSENS_ERROR;
        }
    }

    return error_flag;
}

err_t mcurrentsens_read_adc ( mcurrentsens_t *ctx, int32_t *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;
    uint32_t adc_data = 0;

    /* Start one-shot conversion using fast command. */
    error_flag = mcurrentsens_send_fast_cmd( ctx, MCURRENTSENS_FAST_CMD_CONV_START );
        
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_wait_data_ready ( ctx );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_read_reg24( ctx, MCURRENTSENS_REG_ADCDATA, &adc_data );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = mcurrentsens_sign_ext_24 ( adc_data );
    }

    return error_flag;
}

err_t mcurrentsens_read_adc_avg ( mcurrentsens_t *ctx, uint8_t sample_count, int32_t *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;
    int32_t sample_data = 0;
    int32_t sum_data = 0;
    uint16_t cnt = 0;

    while ( ( MCURRENTSENS_OK == error_flag ) && ( cnt < ( sample_count + 1 ) ) )
    {
        if ( MCURRENTSENS_OK == error_flag )
        {
            error_flag = mcurrentsens_read_adc( ctx, &sample_data );
        }

        /* The first sample is discarded to remove a stale conversion result. */
        if ( ( MCURRENTSENS_OK == error_flag ) && ( cnt > 0 ) )
        {
            sum_data += sample_data;
        }

        cnt++;
    }

    *data_out = ( int32_t ) ( sum_data / sample_count );

    return error_flag;
}

err_t mcurrentsens_read_voltage_avg ( mcurrentsens_t *ctx, uint8_t sample_count, float *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;
    int32_t adc_avg = 0;

    error_flag = mcurrentsens_read_adc_avg ( ctx, sample_count, &adc_avg );
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = mcurrentsens_adc_to_mv( adc_avg, MCURRENTSENS_GAIN_ADC );
    }

    return error_flag;
}

err_t mcurrentsens_read_ch1_current ( mcurrentsens_t *ctx, float *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;

    if ( ctx->calibrated )
    {
        error_flag = mcurrentsens_apply_calib ( ctx, ctx->ch1_curr_cal );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_set_mux ( ctx, MCURRENTSENS_MUX_CH1_CURRENT_P, MCURRENTSENS_MUX_CH1_CURRENT_N );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_read_voltage_avg ( ctx, MCURRENTSENS_SAMPLE_COUNT, data_out );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = *data_out / MCURRENTSENS_CH1_CURRENT_COEFF;
    }

    return error_flag;
}

err_t mcurrentsens_read_ch1_voltage ( mcurrentsens_t *ctx, float *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;

    if ( ctx->calibrated )
    {
        error_flag = mcurrentsens_apply_calib ( ctx, ctx->ch1_volt_cal );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_set_mux( ctx, MCURRENTSENS_MUX_CH1_VOLTAGE_P, MCURRENTSENS_MUX_CH1_VOLTAGE_N );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_read_voltage_avg ( ctx, MCURRENTSENS_SAMPLE_COUNT, data_out );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = *data_out / MCURRENTSENS_CH1_VOLTAGE_COEFF;
    }

    return error_flag;
}

err_t mcurrentsens_read_ch2_current ( mcurrentsens_t *ctx, float *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;

    if ( ctx->calibrated )
    {
        error_flag = mcurrentsens_apply_calib ( ctx, ctx->ch2_curr_cal );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_set_mux( ctx, MCURRENTSENS_MUX_CH2_CURRENT_P, MCURRENTSENS_MUX_CH2_CURRENT_N );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_read_voltage_avg ( ctx, MCURRENTSENS_SAMPLE_COUNT, data_out );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = *data_out / MCURRENTSENS_CH2_CURRENT_COEFF;
    }

    return error_flag;
}

err_t mcurrentsens_read_ch2_voltage ( mcurrentsens_t *ctx, float *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;

    if ( ctx->calibrated )
    {
        error_flag = mcurrentsens_apply_calib ( ctx, ctx->ch2_volt_cal );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_set_mux( ctx, MCURRENTSENS_MUX_CH2_VOLTAGE_P, MCURRENTSENS_MUX_CH2_VOLTAGE_N );
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_read_voltage_avg ( ctx, MCURRENTSENS_SAMPLE_COUNT, data_out );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = *data_out / MCURRENTSENS_CH2_VOLTAGE_COEFF;
    }

    return error_flag;
}

err_t mcurrentsens_read_temperature ( mcurrentsens_t *ctx, float *data_out )
{
    err_t error_flag = MCURRENTSENS_OK;

    error_flag = mcurrentsens_set_mux( ctx, MCURRENTSENS_MUX_TEMP_P, MCURRENTSENS_MUX_TEMP_M );
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = mcurrentsens_read_voltage_avg ( ctx, MCURRENTSENS_SAMPLE_COUNT, data_out );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        *data_out = ( *data_out - MCURRENTSENS_TEMPERATURE_OFFSET ) / MCURRENTSENS_TEMPERATURE_COEFF;
    }

    return error_flag;
}

float mcurrentsens_adc_to_mv ( int32_t adc_code, float gain_adc )
{
    return ( ( ( float ) adc_code * MCURRENTSENS_VREF_INTERNAL ) /
             ( MCURRENTSENS_ADC_FS_CODE * gain_adc ) ) * MCURRENTSENS_V_TO_MV;
}

void mcurrentsens_calculate_calib ( mcurrentsens_calib_t *calib, float offset_coeff,
                                    float target_1, float measured_1,
                                    float target_2, float measured_2 )
{
    float gain = 0;
    float offset = 0;

    /* Linear fit equivalent to polyfit(measured_values, target_values, 1). */
    gain = ( target_2 - target_1 ) / ( measured_2 - measured_1 );

    /* Convert calibration offset to ADC domain before writing OFFSETCAL. */
    offset = ( target_1 - ( gain * measured_1 ) ) * offset_coeff / MCURRENTSENS_V_TO_MV;

    offset = ( MCURRENTSENS_ADC_FS_CODE * MCURRENTSENS_GAIN_ADC * offset ) / MCURRENTSENS_VREF_INTERNAL;
    calib->offset_cal = mcurrentsens_clamp_s24( ( int32_t ) offset );
    gain = MCURRENTSENS_ADC_FS_CODE * gain;
    calib->gain_cal = mcurrentsens_clamp_u24( ( uint32_t ) gain );
}

err_t mcurrentsens_write_memory ( mcurrentsens_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t data_buf[ MCURRENTSENS_EEPROM_PAGE_SIZE + 1 ] = { 0 };
    if ( ( ( address + len - 1 ) > MCURRENTSENS_EEPROM_ADDR_END ) ||
         ( len > MCURRENTSENS_EEPROM_PAGE_SIZE ) ||
         ( NULL == data_in ) )
    {
        error_flag = MCURRENTSENS_ERROR;
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        data_buf[ 0 ] = address;
        memcpy ( &data_buf[ 1 ], data_in, len );
        error_flag = i2c_master_write( &ctx->i2c, data_buf, len + 1 );
    }
    return error_flag;
}

err_t mcurrentsens_read_memory ( mcurrentsens_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = MCURRENTSENS_OK;
    if ( ( ( address + len - 1 ) > MCURRENTSENS_EEPROM_ADDR_END ) ||
         ( len > MCURRENTSENS_EEPROM_PAGE_SIZE ) ||
         ( NULL == data_out ) )
    {
        error_flag = MCURRENTSENS_ERROR;
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        error_flag = i2c_master_write_then_read( &ctx->i2c, &address, 1, data_out, len );
    }
    return error_flag;
}

err_t mcurrentsens_store_calib ( mcurrentsens_t *ctx ) 
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t page[ MCURRENTSENS_EEPROM_PAGE_SIZE ] = { 0 };

    page[ 0 ] = ( uint8_t ) ( ( ctx->ch1_curr_cal.offset_cal >> 24 ) & 0xFF );
    page[ 1 ] = ( uint8_t ) ( ( ctx->ch1_curr_cal.offset_cal >> 16 ) & 0xFF );
    page[ 2 ] = ( uint8_t ) ( ( ctx->ch1_curr_cal.offset_cal >> 8 ) & 0xFF );
    page[ 3 ] = ( uint8_t ) ( ( ctx->ch1_curr_cal.offset_cal >> 0 ) & 0xFF );
    page[ 4 ] = ( uint8_t ) ( ( ctx->ch1_curr_cal.gain_cal >> 24 ) & 0xFF );
    page[ 5 ] = ( uint8_t ) ( ( ctx->ch1_curr_cal.gain_cal >> 16 ) & 0xFF );
    page[ 6 ] = ( uint8_t ) ( ( ctx->ch1_curr_cal.gain_cal >> 8 ) & 0xFF );
    page[ 7 ] = ( uint8_t ) ( ( ctx->ch1_curr_cal.gain_cal >> 0 ) & 0xFF );
    page[ 8 ] = ( uint8_t ) ( ( ctx->ch1_volt_cal.offset_cal >> 24 ) & 0xFF );
    page[ 9 ] = ( uint8_t ) ( ( ctx->ch1_volt_cal.offset_cal >> 16 ) & 0xFF );
    page[ 10 ] = ( uint8_t ) ( ( ctx->ch1_volt_cal.offset_cal >> 8 ) & 0xFF );
    page[ 11 ] = ( uint8_t ) ( ( ctx->ch1_volt_cal.offset_cal >> 0 ) & 0xFF );
    page[ 12 ] = ( uint8_t ) ( ( ctx->ch1_volt_cal.gain_cal >> 24 ) & 0xFF );
    page[ 13 ] = ( uint8_t ) ( ( ctx->ch1_volt_cal.gain_cal >> 16 ) & 0xFF );
    page[ 14 ] = ( uint8_t ) ( ( ctx->ch1_volt_cal.gain_cal >> 8 ) & 0xFF );
    page[ 15 ] = ( uint8_t ) ( ( ctx->ch1_volt_cal.gain_cal >> 0 ) & 0xFF );
    error_flag = mcurrentsens_write_memory ( ctx, MCURRENTSENS_EEPROM_ADDR_START, page, MCURRENTSENS_EEPROM_PAGE_SIZE );
    Delay_10ms ( );

    if ( MCURRENTSENS_OK == error_flag )
    {
        page[ 0 ] = ( uint8_t ) ( ( ctx->ch2_curr_cal.offset_cal >> 24 ) & 0xFF );
        page[ 1 ] = ( uint8_t ) ( ( ctx->ch2_curr_cal.offset_cal >> 16 ) & 0xFF );
        page[ 2 ] = ( uint8_t ) ( ( ctx->ch2_curr_cal.offset_cal >> 8 ) & 0xFF );
        page[ 3 ] = ( uint8_t ) ( ( ctx->ch2_curr_cal.offset_cal >> 0 ) & 0xFF );
        page[ 4 ] = ( uint8_t ) ( ( ctx->ch2_curr_cal.gain_cal >> 24 ) & 0xFF );
        page[ 5 ] = ( uint8_t ) ( ( ctx->ch2_curr_cal.gain_cal >> 16 ) & 0xFF );
        page[ 6 ] = ( uint8_t ) ( ( ctx->ch2_curr_cal.gain_cal >> 8 ) & 0xFF );
        page[ 7 ] = ( uint8_t ) ( ( ctx->ch2_curr_cal.gain_cal >> 0 ) & 0xFF );
        page[ 8 ] = ( uint8_t ) ( ( ctx->ch2_volt_cal.offset_cal >> 24 ) & 0xFF );
        page[ 9 ] = ( uint8_t ) ( ( ctx->ch2_volt_cal.offset_cal >> 16 ) & 0xFF );
        page[ 10 ] = ( uint8_t ) ( ( ctx->ch2_volt_cal.offset_cal >> 8 ) & 0xFF );
        page[ 11 ] = ( uint8_t ) ( ( ctx->ch2_volt_cal.offset_cal >> 0 ) & 0xFF );
        page[ 12 ] = ( uint8_t ) ( ( ctx->ch2_volt_cal.gain_cal >> 24 ) & 0xFF );
        page[ 13 ] = ( uint8_t ) ( ( ctx->ch2_volt_cal.gain_cal >> 16 ) & 0xFF );
        page[ 14 ] = ( uint8_t ) ( ( ctx->ch2_volt_cal.gain_cal >> 8 ) & 0xFF );
        page[ 15 ] = ( uint8_t ) ( ( ctx->ch2_volt_cal.gain_cal >> 0 ) & 0xFF );
        error_flag = mcurrentsens_write_memory ( ctx, ( MCURRENTSENS_EEPROM_ADDR_START + MCURRENTSENS_EEPROM_PAGE_SIZE ), 
                                                 page, MCURRENTSENS_EEPROM_PAGE_SIZE );
        Delay_10ms ( );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        ctx->calibrated = true;
    }
    
    return error_flag;
}

err_t mcurrentsens_fetch_calib ( mcurrentsens_t *ctx ) 
{
    err_t error_flag = MCURRENTSENS_OK;
    uint8_t page[ MCURRENTSENS_EEPROM_PAGE_SIZE ] = { 0 };
    uint8_t blank_page[ MCURRENTSENS_EEPROM_PAGE_SIZE ] = { 0 };

    memset ( blank_page, 0xFF, MCURRENTSENS_EEPROM_PAGE_SIZE );
    Delay_10ms ( );
    error_flag = mcurrentsens_read_memory ( ctx, MCURRENTSENS_EEPROM_ADDR_START, page, MCURRENTSENS_EEPROM_PAGE_SIZE );

    if ( MCURRENTSENS_OK == error_flag )
    {
        if ( !memcmp ( page, blank_page, MCURRENTSENS_EEPROM_PAGE_SIZE ) )
        {
            error_flag = MCURRENTSENS_ERROR;
        }
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        ctx->ch1_curr_cal.offset_cal = ( int32_t ) ( ( ( uint32_t ) page[ 0 ] << 24 ) | 
                                                     ( ( uint32_t ) page[ 1 ] << 16 ) | 
                                                     ( ( uint16_t ) page[ 2 ] << 8 ) | 
                                                                    page[ 3 ] );
        ctx->ch1_curr_cal.gain_cal = ( ( ( uint32_t ) page[ 4 ] << 24 ) | 
                                       ( ( uint32_t ) page[ 5 ] << 16 ) | 
                                       ( ( uint16_t ) page[ 6 ] << 8 ) | 
                                                      page[ 7 ] );
        ctx->ch1_volt_cal.offset_cal = ( int32_t ) ( ( ( uint32_t ) page[ 8 ] << 24 ) | 
                                                     ( ( uint32_t ) page[ 9 ] << 16 ) | 
                                                     ( ( uint16_t ) page[ 10 ] << 8 ) | 
                                                                    page[ 11 ] );
        ctx->ch1_volt_cal.gain_cal = ( ( ( uint32_t ) page[ 12 ] << 24 ) | 
                                       ( ( uint32_t ) page[ 13 ] << 16 ) | 
                                       ( ( uint16_t ) page[ 14 ] << 8 ) | 
                                                      page[ 15 ] );
        Delay_10ms ( );
        error_flag = mcurrentsens_read_memory ( ctx, ( MCURRENTSENS_EEPROM_ADDR_START + MCURRENTSENS_EEPROM_PAGE_SIZE ), 
                                                page, MCURRENTSENS_EEPROM_PAGE_SIZE );
    }

    if ( MCURRENTSENS_OK == error_flag )
    {
        if ( !memcmp ( page, blank_page, MCURRENTSENS_EEPROM_PAGE_SIZE ) )
        {
            error_flag = MCURRENTSENS_ERROR;
        }
    }
    
    if ( MCURRENTSENS_OK == error_flag )
    {
        ctx->ch2_curr_cal.offset_cal = ( int32_t ) ( ( ( uint32_t ) page[ 0 ] << 24 ) | 
                                                     ( ( uint32_t ) page[ 1 ] << 16 ) | 
                                                     ( ( uint16_t ) page[ 2 ] << 8 ) | 
                                                                    page[ 3 ] );
        ctx->ch2_curr_cal.gain_cal = ( ( ( uint32_t ) page[ 4 ] << 24 ) | 
                                       ( ( uint32_t ) page[ 5 ] << 16 ) | 
                                       ( ( uint16_t ) page[ 6 ] << 8 ) | 
                                                      page[ 7 ] );
        ctx->ch2_volt_cal.offset_cal = ( int32_t ) ( ( ( uint32_t ) page[ 8 ] << 24 ) | 
                                                     ( ( uint32_t ) page[ 9 ] << 16 ) | 
                                                     ( ( uint16_t ) page[ 10 ] << 8 ) | 
                                                                    page[ 11 ] );
        ctx->ch2_volt_cal.gain_cal = ( ( ( uint32_t ) page[ 12 ] << 24 ) | 
                                       ( ( uint32_t ) page[ 13 ] << 16 ) | 
                                       ( ( uint16_t ) page[ 14 ] << 8 ) | 
                                                      page[ 15 ] );
        ctx->calibrated = true;
    }
    else
    {
        ctx->calibrated = false;
    }
    return error_flag;
}

uint8_t mcurrentsens_get_irq_pin ( mcurrentsens_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

uint8_t mcurrentsens_get_clk_pin ( mcurrentsens_t *ctx )
{
    return digital_in_read ( &ctx->clk );
}

static int32_t mcurrentsens_sign_ext_24 ( uint32_t value_in )
{
    int32_t value_out = ( int32_t )( value_in & 0xFFFFFFl );

    if ( 0 != ( value_out & 0x800000l ) )
    {
        value_out |= 0xFF000000l;
    }

    return value_out;
}

static int32_t mcurrentsens_clamp_s24 ( int32_t value_in )
{
    int32_t value_out = value_in;

    if ( value_out > 0x7FFFFFl )
    {
        value_out = 0x7FFFFFl;
    }

    if ( value_out < ( -0x800000l ) )
    {
        value_out = -0x800000l;
    }

    return value_out;
}

static uint32_t mcurrentsens_clamp_u24 ( uint32_t value_in )
{
    uint32_t value_out = value_in;

    if ( value_out > 0xFFFFFFul )
    {
        value_out = 0xFFFFFFul;
    }

    return value_out;
}

// ------------------------------------------------------------------------- END
