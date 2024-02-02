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
 * @file barometer13.c
 * @brief Barometer 13 Click Driver.
 */

#include "barometer13.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80
#define SPI_WRITE_MASK    0x7F

/**
 * @brief Barometer 13 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer13_i2c_write ( barometer13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 13 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer13_i2c_read ( barometer13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 13 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer13_spi_write ( barometer13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 13 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer13_spi_read ( barometer13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void barometer13_cfg_setup ( barometer13_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER13_DEVICE_ADDRESS_1;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = BAROMETER13_DRV_SEL_I2C;
}

void barometer13_drv_interface_sel ( barometer13_cfg_t *cfg, barometer13_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t barometer13_init ( barometer13_t *ctx, barometer13_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( BAROMETER13_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = barometer13_i2c_read;
        ctx->write_f = barometer13_i2c_write;
    } 
    else 
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

        ctx->read_f  = barometer13_spi_read;
        ctx->write_f = barometer13_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return BAROMETER13_OK;
}

err_t barometer13_default_cfg ( barometer13_t *ctx ) 
{
    uint8_t chip_id = DUMMY, rev_id = DUMMY;
    err_t err_flag = barometer13_get_device_id( ctx, &chip_id, &rev_id );
   
    if ( BAROMETER13_CHIP_ID == chip_id )
    {
        err_flag |= barometer13_set_pwr_mode( ctx, BAROMETER13_PWR_MODE_STANDBY );
        Delay_10ms( );
        
        err_flag |= barometer13_press_enable( ctx );
        Delay_10ms( );
        
        err_flag |= barometer13_set_osr( ctx, BAROMETER13_OSR_P_1X, 
                                              BAROMETER13_OSR_T_1X );
        Delay_10ms( );
        
        err_flag |= barometer13_set_shdw_sel( ctx, BAROMETER13_SHDW_SEL_IIR_T, 
                                                   BAROMETER13_SHDW_SEL_IIR_P );
        Delay_10ms( );
        
        err_flag |= barometer13_set_lpf_band_flt( ctx, BAROMETER13_SET_IIR_P_FLT_COEF_1, 
                                                       BAROMETER13_SET_IIR_T_FLT_COEF_1 );
        Delay_10ms( );
        
        err_flag |= barometer13_set_int_cfg( ctx, BAROMETER13_INT_ENABLE, BAROMETER13_INT_PUSH_PULL, 
                                                  BAROMETER13_INT_ACTIVE_HIGH, BAROMETER13_INT_PULSED );
        Delay_10ms( );
        
        err_flag |= barometer13_set_drdy_data( ctx, BAROMETER13_DRDY_DATA_EN );
        Delay_10ms( );
        
        err_flag |= barometer13_set_odr( ctx, BAROMETER13_ODR_1_HZ );
        Delay_10ms( );
        
        err_flag |= barometer13_set_pwr_mode( ctx, BAROMETER13_PWR_MODE_NORMAL );
        Delay_10ms( );
    }
    else
    {
        err_flag = BAROMETER13_ERROR;
    }
    return err_flag;
}

err_t barometer13_generic_write ( barometer13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t barometer13_generic_read ( barometer13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t barometer13_reg_write ( barometer13_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t barometer13_reg_read ( barometer13_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t barometer13_get_device_id ( barometer13_t *ctx, uint8_t *chip_id, uint8_t *rev_id )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = barometer13_generic_read( ctx, BAROMETER13_REG_CHIP_ID, data_buf, 2 );
    *chip_id = data_buf[ 0 ];
    *rev_id = data_buf[ 1 ];
    return err_flag;
}

err_t barometer13_set_int_cfg ( barometer13_t *ctx, uint8_t int_en, uint8_t int_od, 
                                                    uint8_t int_pol, uint8_t int_mode )
{
    uint8_t data_buf = DUMMY;
    int_en &= BAROMETER13_INT_ENABLE;
    int_od &= BAROMETER13_INT_OPEN_DRAIN;
    int_pol &= BAROMETER13_INT_ACTIVE_HIGH;
    int_mode &= BAROMETER13_INT_LATCHED;
    err_t err_flag = barometer13_reg_read( ctx, BAROMETER13_REG_INT_CONFIG, &data_buf );
    data_buf &= ~( BAROMETER13_INT_ENABLE | BAROMETER13_INT_OPEN_DRAIN | 
                   BAROMETER13_INT_ACTIVE_HIGH | BAROMETER13_INT_LATCHED );
    data_buf |= int_en;
    data_buf |= int_od;
    data_buf |= int_pol;
    data_buf |= int_mode;
    err_flag |= barometer13_reg_write( ctx, BAROMETER13_REG_INT_CONFIG, data_buf );
    return err_flag;
}

err_t barometer13_set_drdy_data ( barometer13_t *ctx, uint8_t en_drdy_data )
{
    uint8_t data_buf = DUMMY;
    en_drdy_data &= BAROMETER13_DRDY_DATA_EN;
    err_t err_flag = barometer13_reg_read( ctx, BAROMETER13_REG_INT_SOURCE, &data_buf );
    data_buf &= ~BAROMETER13_DRDY_DATA_EN;
    data_buf |= en_drdy_data;
    err_flag |= barometer13_reg_write( ctx, BAROMETER13_REG_INT_SOURCE, data_buf );
    return err_flag;
}

err_t barometer13_get_int_status ( barometer13_t *ctx, uint8_t *int_status )
{
    return barometer13_reg_read( ctx, BAROMETER13_REG_INT_STATUS, int_status );
}

err_t barometer13_set_shdw_sel ( barometer13_t *ctx, uint8_t shdw_sel_iir_p, uint8_t shdw_sel_iir_t )
{
    uint8_t data_buf = DUMMY;
    shdw_sel_iir_p &= BAROMETER13_SHDW_SEL_IIR_P;
    shdw_sel_iir_t &= BAROMETER13_SHDW_SEL_IIR_T;
    err_t err_flag = barometer13_reg_read( ctx, BAROMETER13_REG_DSP_CONFIG, &data_buf );
    data_buf &= ~( BAROMETER13_SHDW_SEL_IIR_P | BAROMETER13_SHDW_SEL_IIR_T );
    data_buf |= shdw_sel_iir_p;
    data_buf |= shdw_sel_iir_t;
    err_flag |= barometer13_reg_write( ctx, BAROMETER13_REG_DSP_CONFIG, data_buf );
    return err_flag;
}

err_t barometer13_set_lpf_band_flt ( barometer13_t *ctx, uint8_t set_iir_p, uint8_t set_iir_t )
{
    uint8_t data_buf = DUMMY;
    set_iir_p &= BAROMETER13_SET_IIR_P_FLT_COEF_127;
    set_iir_t &= BAROMETER13_SET_IIR_T_FLT_COEF_127;
    err_t err_flag = barometer13_reg_read( ctx, BAROMETER13_REG_DSP_IIR, &data_buf );
    data_buf &= ~( BAROMETER13_SET_IIR_P_FLT_COEF_127 | BAROMETER13_SET_IIR_T_FLT_COEF_127 );
    data_buf |= set_iir_p;
    data_buf |= set_iir_t;
    err_flag |= barometer13_reg_write( ctx, BAROMETER13_REG_DSP_IIR, data_buf );
    return err_flag;
}

err_t barometer13_set_osr ( barometer13_t *ctx, uint8_t osr_p, uint8_t osr_t )
{
    uint8_t data_buf = DUMMY;
    osr_p &= BAROMETER13_OSR_P_128X;
    osr_t &= BAROMETER13_OSR_T_128X;
    err_t err_flag = barometer13_reg_read( ctx, BAROMETER13_REG_OSR_CONFIG, &data_buf );
    data_buf &= ~( BAROMETER13_OSR_P_128X | BAROMETER13_OSR_T_128X );
    data_buf |= osr_p;
    data_buf |= osr_t;
    err_flag |= barometer13_reg_write( ctx, BAROMETER13_REG_OSR_CONFIG, data_buf );
    return err_flag;
}

err_t barometer13_press_enable ( barometer13_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = barometer13_reg_read( ctx, BAROMETER13_REG_OSR_CONFIG, &data_buf );
    data_buf |= BAROMETER13_PRESS_EN;
    err_flag |= barometer13_reg_write( ctx, BAROMETER13_REG_OSR_CONFIG, data_buf );
    return err_flag;
}

err_t barometer13_set_odr ( barometer13_t *ctx, uint8_t odr )
{
    uint8_t data_buf = DUMMY;
    odr &= BAROMETER13_ODR_0_125_HZ;
    err_t err_flag = barometer13_reg_read( ctx, BAROMETER13_REG_ODR_CONFIG, &data_buf );
    data_buf &= ~BAROMETER13_ODR_0_125_HZ;
    data_buf |= odr;
    err_flag |= barometer13_reg_write( ctx, BAROMETER13_REG_ODR_CONFIG, data_buf );
    return err_flag;
}

err_t barometer13_set_pwr_mode ( barometer13_t *ctx, uint8_t pwr_mode )
{
    uint8_t data_buf = DUMMY;
    pwr_mode &= BAROMETER13_PWR_MODE_NON_STOP;
    err_t err_flag = barometer13_reg_read( ctx, BAROMETER13_REG_ODR_CONFIG, &data_buf );
    data_buf &= ~BAROMETER13_PWR_MODE_NON_STOP;
    data_buf |= pwr_mode;
    err_flag |= barometer13_reg_write( ctx, BAROMETER13_REG_ODR_CONFIG, data_buf );
    return err_flag;
}

err_t barometer13_get_raw_data ( barometer13_t *ctx, int32_t *press_data, int32_t *temp_data )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t err_flag = barometer13_generic_read( ctx, BAROMETER13_REG_TEMP_DATA_XLSB, data_buf, 6 );
    *press_data = data_buf[ 5 ];
    *press_data <<= 8;
    *press_data |= data_buf[ 4 ];
    *press_data <<= 8;
    *press_data |= data_buf[ 3 ];
    *press_data <<= 8;
    *press_data >>= 8;
    *temp_data = data_buf[ 2 ];
    *temp_data <<= 8;
    *temp_data |= data_buf[ 1 ];
    *temp_data <<= 8;
    *temp_data |= data_buf[ 0 ];
    *temp_data <<= 8;
    *temp_data >>= 8;
    return err_flag;
}

err_t barometer13_get_measurement ( barometer13_t *ctx, float *pressure, float *temperature )
{
    int32_t press_data = DUMMY, temp_data = DUMMY;
    err_t err_flag = barometer13_get_raw_data( ctx, &press_data, &temp_data );
    *pressure = ( float ) press_data;
    *pressure /= BAROMETER13_PRESS_DATA_RES;
    *pressure /= BAROMETER13_PA_TO_MBAR;
    *temperature = ( float ) temp_data;
    *temperature /= BAROMETER13_TEMP_DATA_RES;
    return err_flag;
}

err_t barometer13_get_pressure ( barometer13_t *ctx, float *pressure )
{
    int32_t press_data = DUMMY, temp_data = DUMMY;
    err_t err_flag = barometer13_get_raw_data( ctx, &press_data, &temp_data );
    *pressure = ( float ) press_data;
    *pressure /= BAROMETER13_PRESS_DATA_RES;
    *pressure *= BAROMETER13_PA_TO_MBAR;
    return err_flag;
}

uint8_t barometer13_get_interrupt ( barometer13_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

static err_t barometer13_i2c_write ( barometer13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t barometer13_i2c_read ( barometer13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t barometer13_spi_write ( barometer13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = BAROMETER13_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t n_cnt = reg;
    spi_master_select_device( ctx->chip_select );
    do
    {
        data_buf[ 0 ] = n_cnt & SPI_WRITE_MASK;
        data_buf[ 1 ] = data_in[ n_cnt - reg ];
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
        n_cnt++;
    }
    while ( ( n_cnt - reg ) < len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t barometer13_spi_read ( barometer13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

// ------------------------------------------------------------------------ END
