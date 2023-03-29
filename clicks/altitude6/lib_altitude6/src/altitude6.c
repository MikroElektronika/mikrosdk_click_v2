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
 * @file altitude6.c
 * @brief Altitude 6 Click Driver.
 */

#include "altitude6.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                         0x00

/**
 * @brief SPI read mask data.
 * @details Definition of SPI read mask data.
 */
#define SPI_READ_MASK                                 0x00

/**
 * @brief Altitude, pressure and temperature calculation data.
 * @details Definition of altitude, pressure and temperature calculation data.
 */
#define ALTITUDE6_CONVERT_Pa_TO_mbar                  100
#define ALTITUDE6_TEMP_CONVERT_C_TO_K                 273.15
#define ALTITUDE6_ISA_MODEL_PARAM                       0.1902225603956629
#define ALTITUDE6_CONVERT_NEG                           1
#define ALTITUDE6_STANDARD_TEMPERATURE_LAPSE_RATE       0.0065
#define ALTITUDE6_TEMPERATURE_COEFF                  2000
#define ALTITUDE6_7_BIT_DATA                          128
#define ALTITUDE6_8_BIT_DATA                          256
#define ALTITUDE6_15_BIT_DATA                       32768
#define ALTITUDE6_16_BIT_DATA                       65536
#define ALTITUDE6_21_BIT_DATA                     2097152
#define ALTITUDE6_23_BIT_DATA                     8388608
#define ALTITUDE6_TEMPERATURE_CONV_TO_C               100
#define ALTITUDE6_STANDARD_ATMOSPHERE_mbar           1013.25

/**
 * @brief Altitude 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t altitude6_i2c_write ( altitude6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Altitude 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t altitude6_i2c_read ( altitude6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Altitude 6 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t altitude6_spi_write ( altitude6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Altitude 6 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #altitude6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t altitude6_spi_read ( altitude6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Altitude 6 ADC conversion delay function.
 * @details This function executes a ADC conversion delay of the 10 milliseconds.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_adc_conversion_delay ( void );

/**
 * @brief Altitude 6 reset delay function.
 * @details This function executes a reset - reload delay of the 3 milliseconds.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_reset_reload_delay ( void );

void altitude6_cfg_setup ( altitude6_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ALTITUDE6_SET_DEV_ADDR_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->sea_level_pressure = ALTITUDE6_STANDARD_ATMOSPHERE_mbar;

    cfg->drv_sel = ALTITUDE6_DRV_SEL_I2C;
}

void altitude6_drv_interface_selection ( altitude6_cfg_t *cfg, altitude6_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t altitude6_init ( altitude6_t *ctx, altitude6_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->sea_lvl_pressure = cfg->sea_level_pressure;

    if ( ALTITUDE6_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = altitude6_i2c_read;
        ctx->write_f = altitude6_i2c_write;
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

        ctx->read_f  = altitude6_spi_read;
        ctx->write_f = altitude6_spi_write;
    }

    return ALTITUDE6_OK;
}

err_t altitude6_default_cfg ( altitude6_t *ctx ) 
{    
    err_t err_flag = altitude6_sw_reset( ctx );
    
    err_flag |= altitude6_get_calibration_data( ctx );
    
    altitude6_set_ratio ( ctx, ALTITUDE6_RATIO_2048, ALTITUDE6_RATIO_2048 );

    return err_flag;
}

err_t altitude6_set_command ( altitude6_t *ctx, uint8_t cmd ) 
{
    return ctx->write_f( ctx, cmd, DUMMY, DUMMY );
}

err_t altitude6_generic_read ( altitude6_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, cmd, data_out, len );
}

err_t altitude6_set_ratio ( altitude6_t *ctx, uint8_t temp_ratio, uint8_t press_ratio )
{
    if ( ( temp_ratio > ALTITUDE6_RATIO_4096 ) || ( press_ratio > ALTITUDE6_RATIO_4096 ) )
    {
        return ALTITUDE6_ERROR;
    }
   
    ctx->ratio_temp = temp_ratio;
    ctx->ratio_press = press_ratio;

    return ALTITUDE6_OK;
}

err_t altitude6_sw_reset ( altitude6_t *ctx )
{
    err_t err_flag = altitude6_set_command( ctx, ALTITUDE6_CMD_RESET );
    dev_reset_reload_delay( );
    
    return err_flag;
}

err_t altitude6_get_calibration_data ( altitude6_t *ctx )
{
    uint8_t tmp_data;
    uint16_t prom_data[ 6 ];
    uint8_t data_out[ 2 ];
    err_t err_flag = ALTITUDE6_OK;

    for ( uint8_t n_cnt = 1; n_cnt < 7; n_cnt++ )
    {
        tmp_data = ALTITUDE6_CMD_PROM_READ_START | ( n_cnt << 1 );
        err_flag |= altitude6_generic_read( ctx, tmp_data, data_out, 2 );
        dev_adc_conversion_delay();
        
        prom_data[ n_cnt - 1 ] = data_out[ 0 ];
        prom_data[ n_cnt - 1 ] <<= 8;
        prom_data[ n_cnt - 1 ] |= data_out[ 1 ];
    } 
    
    ctx->press_sens_c1     = prom_data[ 0 ];
    ctx->press_off_c2      = prom_data[ 1 ];
    ctx->press_tcs_c3      = prom_data[ 2 ];
    ctx->press_tco_c4      = prom_data[ 3 ];
    ctx->press_tref_c5     = prom_data[ 4 ];
    ctx->press_tempsens_c6 = prom_data[ 5 ];

    return err_flag;
}

err_t altitude6_get_raw_data ( altitude6_t *ctx, uint32_t *temp_data, uint32_t *press_data )
{
    uint8_t buff_data[ 3 ];
        
    err_t err_flag = altitude6_set_command( ctx, ALTITUDE6_CMD_CONV_D2_OSR_256 | ctx->ratio_temp );
    dev_adc_conversion_delay( );
    err_flag |= altitude6_generic_read( ctx, ALTITUDE6_CMD_ADC_READ, buff_data, 3 );
    
    *temp_data = buff_data[ 0 ];
    *temp_data <<= 8;
    *temp_data |= buff_data[ 1 ];
    *temp_data <<= 8;
    *temp_data |= buff_data[ 2 ];
    
    err_flag |= altitude6_set_command( ctx, ALTITUDE6_CMD_CONV_D1_OSR_256 | ctx->ratio_press );
    dev_adc_conversion_delay( );
    err_flag |= altitude6_generic_read( ctx, DUMMY, buff_data, 3 );
    
    *press_data = buff_data[ 0 ];
    *press_data <<= 8;
    *press_data |= buff_data[ 1 ];
    *press_data <<= 8;
    *press_data |= buff_data[ 2 ];
    
    return err_flag;
}

err_t altitude6_get_temperature ( altitude6_t *ctx, float *temperature )
{
    uint32_t temp_data;
    uint32_t press_data;
    float dT;
    
    err_t err_flag = altitude6_get_raw_data( ctx, &temp_data, &press_data );
    
    *temperature = ALTITUDE6_TEMPERATURE_COEFF;
    dT = ( float ) temp_data;
    dT -= ( float ) ctx->press_tref_c5 * ALTITUDE6_8_BIT_DATA;
    *temperature += dT * ( float ) ctx->press_tempsens_c6 / ALTITUDE6_23_BIT_DATA;
    *temperature /= ALTITUDE6_TEMPERATURE_CONV_TO_C;
    
    return err_flag;
}

err_t altitude6_get_pressure ( altitude6_t *ctx, float *pressure )
{
    uint32_t temp_data;
    uint32_t press_data;
    float dT;
    float off;
    float sens;
    
    err_t err_flag = altitude6_get_raw_data( ctx, &temp_data, &press_data );
    
    dT = ( float ) temp_data;
    dT -= ( float ) ctx->press_tref_c5 * ALTITUDE6_8_BIT_DATA;
    
    off = ( float )ctx->press_off_c2 * ALTITUDE6_16_BIT_DATA;
    off += ( ( float )ctx->press_tco_c4 * dT ) / ALTITUDE6_7_BIT_DATA;
    
    sens = ( float )ctx->press_sens_c1 * ALTITUDE6_15_BIT_DATA;
    sens += ( ( float )ctx->press_tcs_c3 * dT ) / ALTITUDE6_8_BIT_DATA;
    
    *pressure = ( float ) press_data;
    *pressure *= sens;
    *pressure /= ALTITUDE6_21_BIT_DATA;
    *pressure -= off;
    *pressure /= ALTITUDE6_15_BIT_DATA;
    *pressure /= ALTITUDE6_CONVERT_Pa_TO_mbar;
    
    return err_flag;
}

err_t altitude6_get_data ( altitude6_t *ctx, float *temperature, float *pressure, float *altitude )
{
    float tmp;
    float dT;
    float off;
    float sens;
    
    err_t err_flag = altitude6_get_temperature ( ctx, temperature );
    
    off = ( float )ctx->press_off_c2 * ALTITUDE6_16_BIT_DATA;
    off += ( ( float )ctx->press_tco_c4 * dT ) / ALTITUDE6_7_BIT_DATA;
    
    sens = ( float )ctx->press_sens_c1 * ALTITUDE6_15_BIT_DATA;
    sens += ( ( float )ctx->press_tcs_c3 * dT ) / ALTITUDE6_8_BIT_DATA;
    
    err_flag |= altitude6_get_pressure ( ctx, pressure );
    
    tmp = ctx->sea_lvl_pressure;
    tmp /= *pressure;
    
    *altitude = pow( tmp, ALTITUDE6_ISA_MODEL_PARAM );
    *altitude -= ALTITUDE6_CONVERT_NEG;
    
    tmp = *temperature;
    tmp += ALTITUDE6_TEMP_CONVERT_C_TO_K;
    
    *altitude *= tmp;
    *altitude /= ALTITUDE6_STANDARD_TEMPERATURE_LAPSE_RATE;
    
    return err_flag;
}

static err_t altitude6_i2c_write ( altitude6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t altitude6_i2c_read ( altitude6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t altitude6_spi_write ( altitude6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t altitude6_spi_read ( altitude6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static void dev_adc_conversion_delay ( void ) 
{
    Delay_10ms( );
}

static void dev_reset_reload_delay ( void ) 
{
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
}


// ------------------------------------------------------------------------ END
