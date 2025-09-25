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
 * @file environment6.c
 * @brief Environment 6 Click Driver.
 */

#include "environment6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Environment 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment6_i2c_write ( environment6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Environment 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment6_i2c_read ( environment6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Environment 6 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment6_spi_write ( environment6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Environment 6 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment6_spi_read ( environment6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Environment 6 set mem page function.
 * @details This function sets the SPI memory page active depending on register address input.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment6_set_mem_page ( environment6_t *ctx, uint8_t reg );

/**
 * @brief Environment 6 get calib data function.
 * @details This function reads the calibration coefficients data.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment6_get_calib_data ( environment6_t *ctx );

/**
 * @brief Calculate temperature from ADC value.
 * @details This function calculates the compensated temperature value based on ADC data.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] temp_adc : Raw ADC temperature value.
 * @return Calculated temperature in degrees Celsius.
 * @note None.
 */
static float environment6_calc_temp ( environment6_t *ctx, uint32_t temp_adc );

/**
 * @brief Calculate pressure from ADC value.
 * @details This function calculates the compensated pressure value based on ADC data.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] pres_adc : Raw ADC pressure value.
 * @param[in] comp_temp : Compensated temperature value.
 * @return Calculated pressure in hPa.
 * @note None.
 */
static float environment6_calc_pres ( environment6_t *ctx, uint32_t pres_adc, float comp_temp );

/**
 * @brief Calculate humidity from ADC value.
 * @details This function calculates the compensated humidity value based on ADC data.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] hum_adc : Raw ADC humidity value.
 * @param[in] comp_temp : Compensated temperature value.
 * @return Calculated relative humidity in %RH.
 * @note None.
 */
static float environment6_calc_hum ( environment6_t *ctx, uint16_t hum_adc, float comp_temp );

/**
 * @brief Calculate gas resistance.
 * @details This function calculates the gas resistance value from the ADC reading.
 * @param[in] gas_res_adc : Raw ADC gas resistance value.
 * @param[in] gas_range : Gas range setting.
 * @return Calculated gas resistance in ohms.
 * @note None.
 */
static float environment6_calc_gas_res ( uint16_t gas_res_adc, uint8_t gas_range );

/**
 * @brief Calculate heater resistance.
 * @details This function calculates the resistance value needed for the gas sensor heater.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] temp : Desired heater temperature.
 * @return Calculated heater resistance value.
 * @note None.
 */
static uint8_t environment6_calc_res_heat ( environment6_t *ctx, uint16_t temp );

/**
 * @brief Calculate gas wait time.
 * @details This function calculates the required wait time for gas sensor measurement.
 * @param[in] dur : Desired wait duration.
 * @return Encoded gas wait time.
 * @note None.
 */
static uint8_t environment6_calc_gas_wait ( uint16_t dur );

void environment6_cfg_setup ( environment6_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ENVIRONMENT6_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ENVIRONMENT6_DRV_SEL_I2C;
}

void environment6_drv_interface_sel ( environment6_cfg_t *cfg, environment6_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t environment6_init ( environment6_t *ctx, environment6_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ENVIRONMENT6_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = environment6_i2c_read;
        ctx->write_f = environment6_i2c_write;
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

        ctx->read_f  = environment6_spi_read;
        ctx->write_f = environment6_spi_write;
    }

    return ENVIRONMENT6_OK;
}

err_t environment6_default_cfg ( environment6_t *ctx ) 
{
    err_t error_flag = ENVIRONMENT6_OK;
    environment6_sen_conf_t sen_conf;
    environment6_gas_conf_t gas_conf;
    if ( ENVIRONMENT6_ERROR == environment6_check_comm ( ctx ) )
    {
        return ENVIRONMENT6_ERROR;
    }
    error_flag |= environment6_soft_reset ( ctx );
    error_flag |= environment6_get_calib_data ( ctx );

    sen_conf.filter = ENVIRONMENT6_FILTER_OFF;
    sen_conf.odr = ENVIRONMENT6_ODR_NONE;
    sen_conf.os_hum = ENVIRONMENT6_OS_16X;
    sen_conf.os_pres = ENVIRONMENT6_OS_16X;
    sen_conf.os_temp = ENVIRONMENT6_OS_16X;
    error_flag |= environment6_set_sensor_conf ( ctx, &sen_conf );

    gas_conf.enable = 1;
    gas_conf.heater_temp = 300;
    gas_conf.heater_dur = 100;
    error_flag |= environment6_set_gas_conf ( ctx, &gas_conf );

    return error_flag;
}

err_t environment6_write_regs ( environment6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t environment6_read_regs ( environment6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t environment6_write_reg ( environment6_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t environment6_read_reg ( environment6_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t environment6_soft_reset ( environment6_t *ctx )
{
    err_t error_flag = ENVIRONMENT6_OK;
    error_flag |= environment6_write_reg ( ctx, ENVIRONMENT6_REG_RESET, ENVIRONMENT6_SOFT_RESET );
    Delay_10ms ( );
    return error_flag;
}

err_t environment6_check_comm ( environment6_t *ctx )
{
    uint8_t chip_id = 0;
    if ( ENVIRONMENT6_OK == environment6_read_reg ( ctx, ENVIRONMENT6_REG_CHIP_ID, &chip_id ) )
    {
        if ( ENVIRONMENT6_CHIP_ID == chip_id )
        {
            return ENVIRONMENT6_OK;
        }
    }
    return ENVIRONMENT6_ERROR;
}

err_t environment6_set_op_mode ( environment6_t *ctx, uint8_t op_mode )
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t ctrl_meas = ~ENVIRONMENT6_MODE_SLEEP;
    uint8_t data_buf[ ENVIRONMENT6_LEN_CONFIG ] = { 0 };
    if ( op_mode > ENVIRONMENT6_MODE_FORCED )
    {
        error_flag |= ENVIRONMENT6_ERROR;
    }
    while ( ( ENVIRONMENT6_MODE_SLEEP != ( ctrl_meas & ENVIRONMENT6_MODE_MASK ) ) && ( ENVIRONMENT6_OK == error_flag ) )
    {
        error_flag |= environment6_read_reg ( ctx, ENVIRONMENT6_REG_CTRL_MEAS, &ctrl_meas );
        if ( ( ENVIRONMENT6_OK == error_flag ) && ( ENVIRONMENT6_MODE_SLEEP != ( ctrl_meas & ENVIRONMENT6_MODE_MASK ) ) )
        {
            error_flag |= environment6_write_reg ( ctx, ENVIRONMENT6_REG_CTRL_MEAS, ( ctrl_meas & ( ~ENVIRONMENT6_MODE_MASK ) ) );
            Delay_10ms ( );
        }
    }
    if ( ( ENVIRONMENT6_MODE_SLEEP != op_mode ) && ( ENVIRONMENT6_OK == error_flag ) )
    {
        ctrl_meas = ( ctrl_meas & ( ~ENVIRONMENT6_MODE_MASK ) ) | ( op_mode & ENVIRONMENT6_MODE_MASK );
        error_flag |= environment6_write_reg ( ctx, ENVIRONMENT6_REG_CTRL_MEAS, ctrl_meas );
    }
    return error_flag;
}

err_t environment6_get_op_mode ( environment6_t *ctx, uint8_t *op_mode )
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t ctrl_meas = 0;
    error_flag |= environment6_read_reg ( ctx, ENVIRONMENT6_REG_CTRL_MEAS, &ctrl_meas );
    if ( ( ENVIRONMENT6_OK == error_flag ) && ( NULL != op_mode ) )
    {
        *op_mode = ctrl_meas & ENVIRONMENT6_MODE_MASK;
    }
    return error_flag;
}

err_t environment6_set_sensor_conf ( environment6_t *ctx, environment6_sen_conf_t *conf )
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t data_buf[ ENVIRONMENT6_LEN_CONFIG ] = { 0 };
    uint8_t op_mode = 0;
    uint8_t odr20 = 0;
    uint8_t odr3 = 1;
    if ( ( NULL == conf ) && 
         ( conf->filter > ENVIRONMENT6_FILTER_SIZE_127 ) && 
         ( conf->os_temp > ENVIRONMENT6_OS_16X ) && 
         ( conf->os_pres > ENVIRONMENT6_OS_16X ) && 
         ( conf->os_hum > ENVIRONMENT6_OS_16X ) && 
         ( conf->odr > ENVIRONMENT6_ODR_NONE ) )
    {
        error_flag |= ENVIRONMENT6_ERROR;
    }
    
    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_get_op_mode ( ctx, &op_mode );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_set_op_mode ( ctx, ENVIRONMENT6_MODE_SLEEP );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_read_regs ( ctx, ENVIRONMENT6_REG_CTRL_GAS_1, data_buf, ENVIRONMENT6_LEN_CONFIG );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        if ( ENVIRONMENT6_ODR_NONE != conf->odr )
        {
            odr20 = conf->odr;
            odr3 = 0;
        }
        data_buf[ 0 ] = ( data_buf[ 0 ] & 0x7F ) | ( odr3 << 7 );
        data_buf[ 1 ] = ( data_buf[ 1 ] & 0xF8 ) | conf->os_hum;
        data_buf[ 3 ] = ( data_buf[ 3 ] & 0x03 ) | ( conf->os_temp << 5 ) | ( conf->os_pres << 2 );
        data_buf[ 4 ] = ( data_buf[ 4 ] & 0x03 ) | ( odr20 << 5 ) | ( conf->filter << 2 );
        error_flag |= environment6_write_regs ( ctx, ENVIRONMENT6_REG_CTRL_GAS_1, data_buf, ENVIRONMENT6_LEN_CONFIG );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        ctx->sen_conf.filter = conf->filter; 
        ctx->sen_conf.os_temp = conf->os_temp; 
        ctx->sen_conf.os_pres = conf->os_pres; 
        ctx->sen_conf.os_hum = conf->os_hum; 
        ctx->sen_conf.odr = conf->odr; 
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_set_op_mode ( ctx, op_mode );
    }
    return error_flag;
}

err_t environment6_set_gas_conf ( environment6_t *ctx, environment6_gas_conf_t *conf )
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t op_mode = 0;
    uint8_t hctrl = 1;
    uint8_t run_gas = 0;
    if ( NULL == conf )
    {
        error_flag |= ENVIRONMENT6_ERROR;
    }
    
    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_get_op_mode ( ctx, &op_mode );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_set_op_mode ( ctx, ENVIRONMENT6_MODE_SLEEP );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_write_reg ( ctx, ENVIRONMENT6_REG_RES_HEAT_0, 
                                               environment6_calc_res_heat ( ctx, conf->heater_temp ) );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_write_reg ( ctx, ENVIRONMENT6_REG_GAS_WAIT_0, 
                                               environment6_calc_gas_wait ( conf->heater_dur ) );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_read_regs ( ctx, ENVIRONMENT6_REG_CTRL_GAS_0, data_buf, 2 );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        if ( conf->enable )
        {
            hctrl = 0;
            run_gas = 1;
        }
        data_buf[ 0 ] = ( data_buf[ 0 ] & 0xF7 ) | ( hctrl << 3 ) ;
        data_buf[ 1 ] = ( data_buf[ 1 ] & 0xC0 ) | ( run_gas << 5 );
        error_flag |= environment6_write_regs ( ctx, ENVIRONMENT6_REG_CTRL_GAS_0, data_buf, 2 );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        ctx->gas_conf.enable = conf->enable; 
        ctx->gas_conf.heater_temp = conf->heater_temp; 
        ctx->gas_conf.heater_dur = conf->heater_dur; 
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_set_op_mode ( ctx, op_mode );
    }

    return error_flag;
}

err_t environment6_get_data ( environment6_t *ctx, environment6_data_t *data_out )
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t field_buf[ ENVIRONMENT6_LEN_FIELD ] = { 0 };
    uint8_t gas_range = 0;
    uint32_t adc_temp = 0;
    uint32_t adc_pres = 0;
    uint16_t adc_hum = 0;
    uint16_t adc_gas_res = 0;
    uint32_t delay_cnt = 0;
    if ( NULL == data_out )
    {
        error_flag |= ENVIRONMENT6_ERROR;
    }
    
    if ( ENVIRONMENT6_OK == error_flag )
    {
        error_flag |= environment6_set_op_mode ( ctx, ENVIRONMENT6_MODE_FORCED );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        if ( ctx->gas_conf.enable )
        {
            for ( delay_cnt = 0; delay_cnt < ctx->gas_conf.heater_dur; delay_cnt++ )
            {
                Delay_1ms( );
            }
        }
        if ( ctx->sen_conf.os_temp )
        {
            delay_cnt += ( 1ul << ( ctx->sen_conf.os_temp - 1 ) );
        }
        if ( ctx->sen_conf.os_pres )
        {
            delay_cnt += ( 1ul << ( ctx->sen_conf.os_pres - 1 ) );
        }
        if ( ctx->sen_conf.os_hum )
        {
            delay_cnt += ( 1ul << ( ctx->sen_conf.os_hum - 1 ) );
        }
        delay_cnt *= 1963;
        delay_cnt += 1908;
        delay_cnt += 2385;
        delay_cnt /= 1000;
        delay_cnt++;
        while ( delay_cnt > 0 )
        {
            Delay_1ms( );
            delay_cnt--;
        }
        error_flag |= environment6_read_regs ( ctx, ENVIRONMENT6_REG_FIELD_0, field_buf, ENVIRONMENT6_LEN_FIELD );
    }

    if ( ENVIRONMENT6_OK == error_flag )
    {
        data_out->status = field_buf[ 0 ] & 0x80;
        data_out->gas_index = field_buf[ 0 ] & 0x0F;
        data_out->meas_index = field_buf[ 1 ];
        adc_pres = ( ( uint32_t ) field_buf[ 2 ] << 16 ) | ( ( uint16_t ) field_buf[ 3 ] << 8 ) | field_buf[ 4 ];
        adc_temp = ( ( uint32_t ) field_buf[ 5 ] << 16 ) | ( ( uint16_t ) field_buf[ 6 ] << 8 ) | field_buf[ 7 ];
        adc_hum = ( ( uint16_t ) field_buf[ 8 ] << 8 ) | field_buf[ 9 ];
        adc_gas_res = ( ( uint16_t ) field_buf[ 15 ] << 2 ) | ( field_buf[ 16 ] >> 6 );

        gas_range = field_buf[ 16 ] & 0x0F;

        data_out->status |= ( field_buf[ 16 ] & 0x30 );
    }

    if ( ( ENVIRONMENT6_OK == error_flag ) && ( data_out->status & 0x80 ) )
    {
        error_flag |= environment6_read_reg ( ctx, ENVIRONMENT6_REG_RES_HEAT_0 + data_out->gas_index, &data_out->res_heat );
        
        if ( ENVIRONMENT6_OK == error_flag )
        {
            error_flag |= environment6_read_reg ( ctx, ENVIRONMENT6_REG_IDAC_HEAT_0 + data_out->gas_index, &data_out->idac );
        }

        if ( ENVIRONMENT6_OK == error_flag )
        {
            error_flag |= environment6_read_reg ( ctx, ENVIRONMENT6_REG_GAS_WAIT_0 + data_out->gas_index, &data_out->gas_wait );
        }

        if ( ENVIRONMENT6_OK == error_flag )
        {
            data_out->temperature = environment6_calc_temp ( ctx, adc_temp );
            data_out->pressure = environment6_calc_pres ( ctx, adc_pres, data_out->temperature );
            data_out->humidity = environment6_calc_hum ( ctx, adc_hum, data_out->temperature );
            data_out->gas_resistance = environment6_calc_gas_res ( adc_gas_res, gas_range );
        }
    }
    else
    {
        error_flag |= ENVIRONMENT6_ERROR;
    }

    return error_flag;
}

static err_t environment6_i2c_write ( environment6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 512 ] = { 0 };
    for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt * 2 ] = reg + cnt;
        data_buf[ cnt * 2 + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len * 2 );
}

static err_t environment6_i2c_read ( environment6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t environment6_spi_write ( environment6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t reg_adr = reg & ( ~SPI_READ_MASK );
    error_flag |= environment6_set_mem_page ( ctx, reg );
    spi_master_select_device( ctx->chip_select );
    for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
    {
        error_flag |= spi_master_write( &ctx->spi, &reg_adr, 1 );
        error_flag |= spi_master_write( &ctx->spi, &data_in[ cnt ], 1 );
        reg_adr++;
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t environment6_spi_read ( environment6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t reg_adr = reg | SPI_READ_MASK;
    error_flag |= environment6_set_mem_page ( ctx, reg );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t environment6_set_mem_page ( environment6_t *ctx, uint8_t reg )
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t mem_page = ENVIRONMENT6_MEM_PAGE_0;
    uint8_t reg_adr = 0;
    uint8_t status = 0;
    if ( reg & ENVIRONMENT6_MEM_PAGE_1_REG_MASK )
    {
        mem_page = ENVIRONMENT6_MEM_PAGE_1;
    }

    if ( mem_page != ctx->spi_mem_page )
    {
        reg_adr = ENVIRONMENT6_REG_STATUS | SPI_READ_MASK;
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write_then_read( &ctx->spi, &reg_adr, 1, &status, 1 );
        spi_master_deselect_device( ctx->chip_select );

        status &= ( ~ENVIRONMENT6_MEM_PAGE_MASK );
        status |= ( mem_page & ENVIRONMENT6_MEM_PAGE_MASK );
        reg_adr = ENVIRONMENT6_REG_STATUS & ( ~SPI_READ_MASK );
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, &reg_adr, 1 );
        error_flag |= spi_master_write( &ctx->spi, &status, 1 );
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

static err_t environment6_get_calib_data ( environment6_t *ctx )
{
    err_t error_flag = ENVIRONMENT6_OK;
    uint8_t coeff_buf[ ENVIRONMENT6_LEN_COEFF_ALL ] = { 0 };

    error_flag |= environment6_read_regs ( ctx, ENVIRONMENT6_REG_COEFF_1, coeff_buf, ENVIRONMENT6_LEN_COEFF_1 );
    error_flag |= environment6_read_regs ( ctx, 
                                           ENVIRONMENT6_REG_COEFF_2, 
                                           &coeff_buf[ ENVIRONMENT6_LEN_COEFF_1 ], 
                                           ENVIRONMENT6_LEN_COEFF_2 );
    error_flag |= environment6_read_regs ( ctx, 
                                           ENVIRONMENT6_REG_COEFF_3, 
                                           &coeff_buf[ ENVIRONMENT6_LEN_COEFF_1 + ENVIRONMENT6_LEN_COEFF_2 ], 
                                           ENVIRONMENT6_LEN_COEFF_3 );

    if ( ENVIRONMENT6_OK == error_flag )
    {
        /* Temperature related coefficients */
        ctx->calib.par_t1 = ( ( uint16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_DO_C_MSB ] << 8 ) | 
                                           coeff_buf[ ENVIRONMENT6_COEFF_IDX_DO_C_LSB ];
        ctx->calib.par_t2 = ( ( uint16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_DTK1_C_MSB ] << 8 ) | 
                                           coeff_buf[ ENVIRONMENT6_COEFF_IDX_DTK1_C_LSB ];
        ctx->calib.par_t3 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_DTK2_C ];

        /* Pressure related coefficients */
        ctx->calib.par_p5 = ( int16_t ) ( ( ( uint16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_S_C_MSB ] << 8 ) | 
                                                         coeff_buf[ ENVIRONMENT6_COEFF_IDX_S_C_LSB ] );
        ctx->calib.par_p6 = ( int16_t ) ( ( ( uint16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK1S_C_MSB ] << 8 ) | 
                                                         coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK1S_C_LSB ] );
        ctx->calib.par_p7 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK2S_C ];
        ctx->calib.par_p8 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK3S_C ];

        ctx->calib.par_p1 = ( int16_t ) ( ( ( uint16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_O_C_MSB ] << 8 ) | 
                                                         coeff_buf[ ENVIRONMENT6_COEFF_IDX_O_C_LSB ] );
        ctx->calib.par_p2 = ( int16_t ) ( ( ( uint16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK10_C_MSB ] << 8 ) | 
                                                         coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK10_C_LSB ] );
        ctx->calib.par_p3 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK20_C ];
        ctx->calib.par_p4 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK30_C ];

        ctx->calib.par_p9 = ( int16_t ) ( ( ( uint16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_NLS_C_MSB ] << 8 ) | 
                                                         coeff_buf[ ENVIRONMENT6_COEFF_IDX_NLS_C_LSB ] );
        ctx->calib.par_p10 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TKNLS_C ];
        ctx->calib.par_p11 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_NLS3_C ];

        /* Humidity related coefficients */
        ctx->calib.par_h5 = ( int16_t ) ( ( ( int16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_S_H_MSB ] << 4 ) | 
                                                      ( coeff_buf[ ENVIRONMENT6_COEFF_IDX_S_H_LSB ] >> 4 ) );
        ctx->calib.par_h1 = ( int16_t ) ( ( ( int16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_O_H_MSB ] << 4 ) | 
                                                      ( coeff_buf[ ENVIRONMENT6_COEFF_IDX_O_H_LSB ] & 0x0F ) );
        ctx->calib.par_h2 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TK10H_C ];
        ctx->calib.par_h4 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_PAR_H4 ];
        ctx->calib.par_h3 = ( uint8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_PAR_H3 ];
        ctx->calib.par_h6 = ( uint8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_HLIN2_C ];

        /* Gas heater related coefficients */
        ctx->calib.par_g1 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_RO_C ];
        ctx->calib.par_g2 = ( int16_t ) ( ( ( uint16_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_TKR_C_MSB ] << 8 ) | 
                                                         coeff_buf[ ENVIRONMENT6_COEFF_IDX_TKR_C_LSB ] );
        ctx->calib.par_g3 = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_T_AMB_COMP ];

        /* Other coefficients */
        ctx->calib.res_heat_range = ( ( coeff_buf[ ENVIRONMENT6_COEFF_IDX_RES_HEAT_RANGE ] & 0x30 ) >> 4 );
        ctx->calib.res_heat_val = ( int8_t ) coeff_buf[ ENVIRONMENT6_COEFF_IDX_RES_HEAT_VAL ];
        ctx->calib.range_sw_err = ( ( int8_t ) ( coeff_buf[ ENVIRONMENT6_COEFF_IDX_RANGE_SW_ERR ] & 0xF0 ) ) / 16;
    }
    return error_flag;
}

static float environment6_calc_temp ( environment6_t *ctx, uint32_t temp_adc )
{
    int32_t do1 = 0;
    int32_t cf_val = 0;
    float dtk1 = 0;
    float dtk2 = 0;
    float temp1 = 0;
    float temp2 = 0;
    float calc_temp = 0;

    do1 = ( int32_t ) ctx->calib.par_t1 << 8;
    dtk1 = ctx->calib.par_t2 / 1073741824.0;
    dtk2 = ctx->calib.par_t3 / 281474976710656.0;

    cf_val = temp_adc - do1;
    temp1 = ( float ) cf_val * dtk1;
    temp2 = ( float ) cf_val * cf_val * dtk2;

    calc_temp = temp1 + temp2;

    return calc_temp;
}

static float environment6_calc_pres ( environment6_t *ctx, uint32_t pres_adc, float comp_temp )
{
    uint32_t o_val = 0;
    float tk10 = 0;
    float tk20 = 0;
    float tk30 = 0;
    float s_val = 0;
    float tk1s = 0;
    float tk2s = 0;
    float tk3s = 0;
    float nls = 0;
    float tknls = 0;
    float nls3 = 0;
    float calc_pres = 0;
    float tmp1 = 0;
    float tmp2 = 0;
    float tmp3 = 0;
    float tmp4 = 0;

    o_val = ( uint32_t ) ctx->calib.par_p1 * 8;
    tk10 = ctx->calib.par_p2 / 64.0;
    tk20 = ctx->calib.par_p3 / 256.0;
    tk30 = ctx->calib.par_p4 / 32768.0;

    s_val = ( ( float ) ctx->calib.par_p5 - 16384.0 ) / 1048576.0;
    tk1s = ( ( float ) ctx->calib.par_p6 - 16384.0 ) / 536870912.0;
    tk2s = ( float ) ctx->calib.par_p7 / 4294967296.0;
    tk3s = ( float ) ctx->calib.par_p8 / 137438953472.0;

    nls = ( float ) ctx->calib.par_p9 / 281474976710656.0;
    tknls = ( float ) ctx->calib.par_p10 / 281474976710656.0;

    nls3 = ( float ) ctx->calib.par_p11 / 34359738368.0 / 1073741824.0;

    tmp1 = ( float ) o_val + ( tk10 * comp_temp ) + ( tk20 * comp_temp * comp_temp ) +
                             ( tk30 * comp_temp * comp_temp * comp_temp );

    tmp2 = ( float ) pres_adc * ( ( float ) s_val + ( tk1s * comp_temp ) + 
                                                    ( tk2s * comp_temp * comp_temp ) +
                                                    ( tk3s * comp_temp * comp_temp * comp_temp ) );

    tmp3 = ( float ) pres_adc * ( float ) pres_adc * ( nls + ( tknls * comp_temp ) );
    tmp4 = ( float ) pres_adc * ( float ) pres_adc * ( float ) pres_adc * nls3;

    calc_pres = tmp1 + tmp2 + tmp3 + tmp4;

    return ( float ) calc_pres / 100.0;
}

static float environment6_calc_hum ( environment6_t *ctx, uint16_t hum_adc, float comp_temp )
{
    float oh_val = 0;
    float tk10h = 0;
    float sh_val = 0;
    float tk1sh = 0;
    float tk2sh = 0;
    float hlin2 = 0;
    float hoff = 0;
    float hsens = 0;
    float temp_comp = 0;
    float calc_hum = 0;
    float temp_var_1 = 0;

    temp_comp = ( comp_temp * 5120.0 ) - 76800.0;

    oh_val = ( float ) ctx->calib.par_h1 * 64.0;
    sh_val = ( float ) ctx->calib.par_h5 / 65536.0;
    tk10h = ( float ) ctx->calib.par_h2 / 16384.0;
    tk1sh = ( float ) ctx->calib.par_h4 / 67108864.0;
    tk2sh = ( float ) ctx->calib.par_h3 / 67108864.0;
    hlin2 = ( float ) ctx->calib.par_h6 / 524288.0;

    hoff = ( float ) hum_adc - ( oh_val + tk10h * temp_comp );
    hsens = hoff * sh_val * ( 1 + ( tk1sh * temp_comp ) + ( tk1sh * tk2sh * temp_comp * temp_comp ) );
    temp_var_1 = hsens * ( 1 - hlin2 * hsens );
    calc_hum = temp_var_1;

    return ( float ) calc_hum;
}

static float environment6_calc_gas_res ( uint16_t gas_res_adc, uint8_t gas_range )
{
    float calc_gas_res = 0;

    uint32_t var1 = ( 262144ul ) >> gas_range;
    int32_t var2 = ( int32_t ) gas_res_adc - 512;

    var2 *= 3;
    var2 = 4096 + var2;

    calc_gas_res = 1000000.0 * ( float ) var1 / ( float ) var2;

    return calc_gas_res;
}

static uint8_t environment6_calc_res_heat ( environment6_t *ctx, uint16_t temp )
{
    float var1 = 0;
    float var2 = 0;
    float var3 = 0;
    float var4 = 0;
    float var5 = 0;
    uint8_t res_heat = 0;

    if ( temp > 400 )
    {
        temp = 400;
    }

    var1 = ctx->calib.par_g1 / 16.0 + 49.0;
    var2 = ( ctx->calib.par_g2 / 32768.0 ) * 0.0005 + 0.00235;
    var3 = ctx->calib.par_g3 / 1024.0;
    var4 = var1 * 1.0 + var2 * temp;
    var5 = var4 + var3 * 25;
    res_heat = ( uint8_t ) ( 3.4 * ( var5 * ( 4.0 / ( 4 + ctx->calib.res_heat_range ) ) *
                                            ( 1.0 / ( 1 + ctx->calib.res_heat_val * 0.002 ) ) ) - 25 );
    return res_heat;
}

static uint8_t environment6_calc_gas_wait ( uint16_t dur )
{
    uint8_t factor = 0;

    if ( dur >= 0x0FC0 )
    {
        return 0xFF;
    }

    while ( dur > 0x3F )
    {
        dur = dur / 4;
        factor += 1;
    }

    return ( uint8_t ) ( dur + ( factor * 64 ) );
}

// ------------------------------------------------------------------------ END
