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
 * @file environment3.c
 * @brief Environment 3 Click Driver.
 */

#include "environment3.h"

// ------------------------------------------------------------- PRIVATE MACROS 
/**
 * @brief Ambient temp data.
 * @details Definition of ambient temp data.
 */
#define DEVICE_AMB_TEMP                                   25

/**
 * @brief Combine two 8 bit macro.
 * @details Macro to combine two 8 bit data's to form a 16 bit data.
 */
#define BYTES_TO_WORD( msb, lsb )                         ( ( ( uint16_t ) msb << 8 ) | ( uint16_t ) lsb )

/**
 * @brief Set reg bits macro.
 * @details Macro to set a desired bits of the reg_data variable.
 */
#define SET_REG_BITS( reg_data, bit_name, in_data )       ( ( reg_data & ~( bit_name##_MASK ) ) | \
                                                          ( ( in_data << bit_name##_POS ) & bit_name##_MASK ) )

/**
 * @brief Get reg bits macro.
 * @details Macro to get a desired bits of the reg_data variable.
 */
#define GET_REG_BITS( reg_data, bit_name )                ( ( reg_data & bit_name##_MASK ) >> bit_name##_POS )

/**
 * @brief Set reg low bits macro.
 * @details Macro to set a desired bits starting from LSB of the reg_data variable.
 */
#define SET_REG_BITS_LOW( reg_data, bit_name, in_data )   ( ( reg_data & ~( bit_name##_MASK ) ) | \
                                                          ( in_data & bit_name##_MASK ) )

/**
 * @brief Get reg low bits macro.
 * @details Macro to get a desired bits starting from LSB of the reg_data variable.
 */
#define GET_REG_BITS_LOW( reg_data, bit_name )            ( reg_data & ( bit_name##_MASK ) )

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                             0x00


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Environment 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment3_i2c_write ( environment3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Environment 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment3_i2c_read ( environment3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Environment 3 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment3_spi_write ( environment3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Environment 3 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t environment3_spi_read ( environment3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Environment 3 get data function.
 * @details This function the pressure, temperature, humidity and gas data
 * from the sensor, compensates the data and store it in the Click object f_data structure.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  2 - No new data.
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t environment3_get_data ( environment3_t *ctx );

/**
 * @brief Environment 3 set gas config function.
 * @details This function sets gas heater temperature and wait duration data.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] conf : Gas setting object.
 * See environment3_gas_settings_t gas setting object definition for detailed explanation.
 * @return @li @c  1 - Wrong operating mode.
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Communication fail.
 *         @li @c -3 - Invalid length.
 * @note None.
 */
static int8_t environment3_set_gas_config ( environment3_t *ctx, environment3_gas_settings_t *conf );

/**
 * @brief Environment 3 set SPI memory page function.
 * @details This function sets SPI memory page depending on the register address value.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Communication fail.
 * @note None.
 */
static int8_t environment3_set_mem_page ( environment3_t *ctx, uint8_t reg );

/**
 * @brief Environment 3 get SPI memory page function.
 * @details This function gets the currently set SPI memory page and stores it in 
 * the Click object structure, device_mem_page variable.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Communication fail.
 * @note None.
 */
static int8_t environment3_get_mem_page( environment3_t *ctx );

/**
 * @brief Environment 3 calculate heater resistance function.
 * @details This function calculates heater resistance from heater temperature.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] temp : Heater temperature.
 * @return Resistance value.
 * @note None.
 */
static uint8_t environment3_calc_heater_res ( environment3_t *ctx, uint16_t temp );

/**
 * @brief Environment 3 calculate gas wait function.
 * @details This function calculates gas wait value from heater duration.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] dur : Heater duration.
 * @return Gas wait value.
 * @note None.
 */
static uint8_t environment3_calc_gas_wait ( environment3_t *ctx, uint16_t dur );

/**
 * @brief Environment 3 boundary check function.
 * @details This function limits the value to min or max if it is out of range.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] value : Value.
 * @param[in] min : Minimal value of range.
 * @param[in] max : Maximal value of range.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t environment3_boundary_check ( environment3_t *ctx, uint8_t *value, uint8_t min, uint8_t max );

/**
 * @brief Environment 3 calculate temperature function.
 * @details This function calculates temperature value from raw temperature ADC value.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] temp_adc : Raw temperature ADC value.
 * @return Temparature value in Celsius.
 * @note None.
 */
static float environment3_calc_temperature ( environment3_t *ctx, uint32_t temp_adc );

/**
 * @brief Environment 3 calculate humidity function.
 * @details This function calculates humidity value from raw humidity ADC value.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] hum_adc : Raw humidity ADC value.
 * @return Humidity value in Percent.
 * @note None.
 */
static float environment3_calc_humidity ( environment3_t *ctx, uint16_t hum_adc );

/**
 * @brief Environment 3 calculate pressure function.
 * @details This function calculates pressure value from raw pressure ADC value.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] pres_adc : Raw pressure ADC value.
 * @return Pressure value in Pascals.
 * @note None.
 */
static float environment3_calc_pressure ( environment3_t *ctx, uint32_t pres_adc );

/**
 * @brief Environment 3 calculate gas resistance high function.
 * @details This function calculates gas resistance high value from raw gas resistance ADC value and gas range.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] gas_res_adc : Raw gas resistance ADC value.
 * @param[in] gas_range : Gas range value.
 * @return Gas resistance high value.
 * @note None.
 */
static float environment3_calc_gas_resistance_high ( environment3_t *ctx, uint16_t gas_res_adc, uint8_t gas_range );

/**
 * @brief Environment 3 calculate gas resistance low function.
 * @details This function calculates gas resistance low value from raw gas resistance ADC value and gas range.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] gas_res_adc : Raw gas resistance ADC value.
 * @param[in] gas_range : Gas range value.
 * @return Gas resistance low value.
 * @note None.
 */
static float environment3_calc_gas_resistance_low ( environment3_t *ctx, uint16_t gas_res_adc, uint8_t gas_range );

/**
 * @brief Environment 3 read field data function.
 * @details This function reads all data from field 0.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] f_data : Field data structure.
 * See environment3_field_data_t object definition for detailed explanation.
 * @return @li @c  2 - No new data.
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t environment3_read_field_data ( environment3_t *ctx, environment3_field_data_t *f_data );

/**
 * @brief Environment 3 get calibration data function.
 * @details This function reads all the calibration coefficients and stores it in 
 * the Click object calib structure.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void environment3_get_calibration_data ( environment3_t *ctx );

/**
 * @brief Environment 3 read variant ID function.
 * @details This function reads variant ID information register status and stores it in
 * the Click object, device_variant_id variable.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static int8_t environment3_read_variant_id ( environment3_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void environment3_cfg_setup ( environment3_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ENVIRONMENT3_DEVICE_SLAVE_ADDR_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ENVIRONMENT3_DRV_SEL_I2C;
}

void environment3_drv_interface_selection ( environment3_cfg_t *cfg, environment3_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t environment3_init ( environment3_t *ctx, environment3_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ctx->drv_sel == ENVIRONMENT3_DRV_SEL_I2C ) 
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

        ctx->read_f  = environment3_i2c_read;
        ctx->write_f = environment3_i2c_write;
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

        ctx->read_f  = environment3_spi_read;
        ctx->write_f = environment3_spi_write;
    }

    return ENVIRONMENT3_OK;
}

err_t environment3_default_cfg ( environment3_t *ctx ) 
{
    // Click default configuration.
    environment3_soft_reset( ctx );
    
    if ( ENVIRONMENT3_OK != environment3_check_id( ctx ) )
    {
        return ENVIRONMENT3_ERROR;
    }
    
    if ( ENVIRONMENT3_OK != environment3_read_variant_id( ctx ) )
    {
        return ENVIRONMENT3_ERROR;
    }
    
    environment3_get_calibration_data( ctx );
    Delay_1sec( );
    
    ctx->tph_sett.os_hum = ENVIRONMENT3_OS_16X;
    ctx->tph_sett.os_pres = ENVIRONMENT3_OS_1X;
    ctx->tph_sett.os_temp = ENVIRONMENT3_OS_2X;
    ctx->tph_sett.filter = ENVIRONMENT3_FILTER_OFF;
    ctx->tph_sett.odr = ENVIRONMENT3_ODR_NONE;
    
    if ( ENVIRONMENT3_OK != environment3_set_sensor_conf ( ctx, &ctx->tph_sett ) )
    {
        return ENVIRONMENT3_ERROR;
    }
    
    ctx->gas_sett.enable = ENVIRONMENT3_DISABLE;
    ctx->gas_sett.heater_temp = 350;
    ctx->gas_sett.heater_dur = 1000;
    
    if ( ENVIRONMENT3_OK != environment3_set_heater_conf ( ctx, &ctx->gas_sett ) )
    {
        return ENVIRONMENT3_ERROR;
    }
    
    return ENVIRONMENT3_OK;
}

err_t environment3_generic_write ( environment3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t environment3_generic_read ( environment3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t environment3_write_byte ( environment3_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 ); 
}

uint8_t environment3_read_byte ( environment3_t *ctx, uint8_t reg )
{
    uint8_t read_buffer;

    ctx->read_f( ctx, reg, &read_buffer, 1 );

    return read_buffer;
}

int8_t environment3_check_id ( environment3_t *ctx )
{
    if ( ENVIRONMENT3_CHIP_ID != environment3_read_byte( ctx, ENVIRONMENT3_REG_CHIP_ID ) )
    {
        return ENVIRONMENT3_ERROR;
    }

    return ENVIRONMENT3_OK;
}

uint8_t environment3_get_device_id ( environment3_t *ctx )
{
    return environment3_read_byte( ctx, ENVIRONMENT3_REG_CHIP_ID );
}

int8_t environment3_soft_reset ( environment3_t *ctx )
{
    uint8_t reg_addr;
    uint8_t soft_rst_cmd;
    int8_t error_check = 0;

    reg_addr = ENVIRONMENT3_REG_RESET;
    soft_rst_cmd = ENVIRONMENT3_SOFT_RESET;

    if ( ENVIRONMENT3_DRV_SEL_SPI == ctx->drv_sel )
    {
        error_check = environment3_get_mem_page( ctx );
    }

    error_check |= environment3_set_regs( ctx, &reg_addr, &soft_rst_cmd, 1 );
    Delay_10ms();

    if ( ENVIRONMENT3_DRV_SEL_SPI == ctx->drv_sel )
    {
        error_check |= environment3_get_mem_page( ctx );
    }
    return error_check;
}

int8_t environment3_get_all_data ( environment3_t *ctx, float *temp, float *hum, float *pres, uint32_t *gas )
{
    int8_t error_check = environment3_get_data ( ctx );
    
    if ( ENVIRONMENT3_OK != error_check )
    {
        return error_check;
    }
    
    *temp = ctx->f_data.temperature;
    
    *hum = ctx->f_data.humidity;
    
    *pres = ctx->f_data.pressure / 100.0;
    
    if( ctx->f_data.status & ENVIRONMENT3_GASM_VALID_MASK )
    {
        *gas = ( uint32_t ) ctx->f_data.gas_resistance;
    }
    
    return ENVIRONMENT3_OK;
}

float environment3_get_temperature ( environment3_t *ctx )
{
    int8_t error_check = environment3_get_data ( ctx );
    
    if ( ENVIRONMENT3_OK != error_check )
    {
        return ( float ) error_check;
    }
    else
    {
        return ctx->f_data.temperature;
    }
}

float environment3_get_humidity ( environment3_t *ctx )
{
    int8_t error_check = environment3_get_data ( ctx );
    
    if ( ENVIRONMENT3_OK != error_check )
    {
        return ( float ) error_check;
    }
    else
    {
        return ctx->f_data.humidity;
    }
}

float environment3_get_pressure ( environment3_t *ctx )
{
    int8_t error_check = environment3_get_data ( ctx );
    
    if ( ENVIRONMENT3_OK != error_check )
    {
        return ( float ) error_check;
    }
    else
    {
        return ctx->f_data.pressure / 100.0;
    }
}

float environment3_get_gas_resistance ( environment3_t *ctx )
{
    int8_t error_check = environment3_get_data ( ctx );
    
    if ( ENVIRONMENT3_OK != error_check )
    {
        return ( float ) error_check;
    }
    else
    {
        return ctx->f_data.gas_resistance;
    }
}


int8_t environment3_get_regs ( environment3_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len )
{
    if ( ENVIRONMENT3_DRV_SEL_SPI == ctx->drv_sel )
    {
        if ( ENVIRONMENT3_OK != environment3_set_mem_page( ctx, reg ) )
        {
            return ENVIRONMENT3_ERROR;
        }
    }
    if ( ENVIRONMENT3_OK != environment3_generic_read( ctx, reg, data_out, len ) )
    {
        return ENVIRONMENT3_E_COM_FAIL;
    }

    return ENVIRONMENT3_OK;
}

int8_t environment3_set_regs ( environment3_t *ctx, uint8_t *reg, uint8_t *data_in, uint8_t len )
{
    int8_t error_check = 0;

    uint8_t tmp_buff[ ENVIRONMENT3_LEN_INTERLEAVE_BUFF ] = { 0 };

    if ( ( len > 0 ) && ( len <= ENVIRONMENT3_LEN_INTERLEAVE_BUFF / 2 ) )
    {

        for ( uint16_t index = 0; index < len; index++ )
        {
            if ( ENVIRONMENT3_DRV_SEL_SPI == ctx->drv_sel )
            {
                error_check |= environment3_set_mem_page( ctx, reg[ index ] );
                tmp_buff[ ( 2 * index ) ] = reg[ index ] & ENVIRONMENT3_SPI_WRITE_MASK;
            }
            else
            {
                tmp_buff[ ( 2 * index ) ] = reg[ index ];
            }
            tmp_buff[ ( 2 * index ) + 1 ] = data_in[ index ];
        }

        if ( ENVIRONMENT3_OK == error_check )
        {
            if ( ENVIRONMENT3_OK != environment3_generic_write( ctx, tmp_buff[ 0 ], &tmp_buff[ 1 ], ( 2 * len ) - 1 ) )
            {
                return ENVIRONMENT3_E_COM_FAIL;
            }
        }
    }
    else
    {
        return ENVIRONMENT3_E_INVALID_LENGTH;
    }

    return error_check;
}

int8_t environment3_enable_heater ( environment3_t *ctx, uint8_t state )
{
    ctx->gas_sett.enable = state;
    
    return environment3_set_heater_conf ( ctx, &ctx->gas_sett );
}

int8_t environment3_set_heater_conf ( environment3_t *ctx, environment3_gas_settings_t *conf )
{
    int8_t error_check = 0;
    uint8_t nb_conv = 0;
    uint8_t hctrl, run_gas = 0;
    uint8_t ctrl_gas_data[ 2 ];
    uint8_t ctrl_gas_addr[ 2 ] = { ENVIRONMENT3_REG_CTRL_GAS_0, ENVIRONMENT3_REG_CTRL_GAS_1 };
    
    if ( conf )
    {
        ctx->gas_sett.enable = conf->enable;
        ctx->gas_sett.heater_temp = conf->heater_temp;
        ctx->gas_sett.heater_dur = conf->heater_dur;
        error_check = environment3_set_operating_mode( ctx, ENVIRONMENT3_MODE_SLEEP );
        if ( ENVIRONMENT3_OK == error_check )
        {
            error_check = environment3_set_gas_config( ctx, conf );
        }

        if ( ENVIRONMENT3_OK == error_check )
        {
            error_check = environment3_get_regs( ctx, ENVIRONMENT3_REG_CTRL_GAS_0, ctrl_gas_data, 2 );
            if ( ENVIRONMENT3_OK == error_check )
            {
                if ( ENVIRONMENT3_ENABLE == conf->enable )
                {
                    hctrl = ENVIRONMENT3_ENABLE_HEATER;
                    if ( ENVIRONMENT3_VARIANT_GAS_HIGH == ctx->device_variant_id )
                    {
                        run_gas = ENVIRONMENT3_ENABLE_GAS_MEAS_H;
                    }
                    else
                    {
                        run_gas = ENVIRONMENT3_ENABLE_GAS_MEAS_L;
                    }
                }
                else
                {
                    hctrl = ENVIRONMENT3_DISABLE_HEATER;
                    run_gas = ENVIRONMENT3_DISABLE_GAS_MEAS;
                }

                ctrl_gas_data[ 0 ] = SET_REG_BITS( ctrl_gas_data[ 0 ], ENVIRONMENT3_HCTRL, hctrl );
                ctrl_gas_data[ 1 ] = SET_REG_BITS_LOW( ctrl_gas_data[ 1 ], ENVIRONMENT3_NBCONV, nb_conv );
                ctrl_gas_data[ 1 ] = SET_REG_BITS( ctrl_gas_data[ 1 ], ENVIRONMENT3_RUN_GAS, run_gas );
                error_check = environment3_set_regs( ctx, ctrl_gas_addr, ctrl_gas_data, 2 );
            }
        }
    }
    else
    {
        error_check = ENVIRONMENT3_E_NULL_PTR;
    }

    return error_check;
}

int8_t environment3_set_sensor_conf ( environment3_t *ctx, environment3_tph_settings_t *conf )
{
    int8_t error_check = 0;
    uint8_t odr20 = 0, odr3 = 1;
    int8_t current_op_mode;
    uint8_t reg_array[ ENVIRONMENT3_LEN_CONFIG ] = 
    { 
        ENVIRONMENT3_REG_CTRL_GAS_1, ENVIRONMENT3_REG_CTRL_HUM, ENVIRONMENT3_REG_STATUS, 
        ENVIRONMENT3_REG_CTRL_MEAS, ENVIRONMENT3_REG_CONFIG 
    };
    
    if ( conf )
    {
        ctx->tph_sett.os_hum = conf->os_hum;
        ctx->tph_sett.os_temp = conf->os_temp;
        ctx->tph_sett.os_pres = conf->os_pres;
        ctx->tph_sett.filter = conf->filter;
        ctx->tph_sett.odr = conf->odr;
    }
    else
    {
        return ENVIRONMENT3_ERROR;
    }
    
    uint8_t data_array[ ENVIRONMENT3_LEN_CONFIG ] = { 0 };
    
    current_op_mode = environment3_get_operating_mode ( ctx );
    if ( ENVIRONMENT3_ERROR == current_op_mode )
    {
        return ENVIRONMENT3_ERROR;
    }
    
    error_check = environment3_set_operating_mode( ctx, ENVIRONMENT3_MODE_SLEEP );

    if ( ENVIRONMENT3_OK == error_check )
    {
        error_check = environment3_get_regs ( ctx, reg_array[ 0 ], data_array, ENVIRONMENT3_LEN_CONFIG );
        
        if ( ENVIRONMENT3_OK == error_check )
        {
            error_check = environment3_boundary_check( ctx, &conf->filter, 
                                                            ENVIRONMENT3_FILTER_OFF, 
                                                            ENVIRONMENT3_FILTER_SIZE_127 );
        }
        if ( ENVIRONMENT3_OK == error_check )
        {
            error_check = environment3_boundary_check( ctx, &conf->os_temp, 
                                                            ENVIRONMENT3_OS_NONE, 
                                                            ENVIRONMENT3_OS_16X );
        }
        if ( ENVIRONMENT3_OK == error_check )
        {
            error_check = environment3_boundary_check( ctx, &conf->os_pres, 
                                                            ENVIRONMENT3_OS_NONE, 
                                                            ENVIRONMENT3_OS_16X );
        }
        if ( ENVIRONMENT3_OK == error_check )
        {
            error_check = environment3_boundary_check( ctx, &conf->os_hum, 
                                                            ENVIRONMENT3_OS_NONE, 
                                                            ENVIRONMENT3_OS_16X );
        }
        if ( ENVIRONMENT3_OK == error_check )
        {
            error_check = environment3_boundary_check( ctx, &conf->odr, 
                                                            ENVIRONMENT3_ODR_0_59_MS, 
                                                            ENVIRONMENT3_ODR_NONE );
        }
        if ( ENVIRONMENT3_OK == error_check )
        {
            data_array[ 4 ] = SET_REG_BITS( data_array[ 4 ], ENVIRONMENT3_FILTER, conf->filter );
            data_array[ 3 ] = SET_REG_BITS( data_array[ 3 ], ENVIRONMENT3_OST, conf->os_temp );
            data_array[ 3 ] = SET_REG_BITS( data_array[ 3 ], ENVIRONMENT3_OSP, conf->os_pres );
            data_array[ 1 ] = SET_REG_BITS_LOW( data_array[ 1 ], ENVIRONMENT3_OSH, conf->os_hum );
            if ( ENVIRONMENT3_ODR_NONE != conf->odr )
            {
                odr20 = conf->odr;
                odr3 = 0;
            }

            data_array[ 4 ] = SET_REG_BITS(data_array[ 4 ], ENVIRONMENT3_ODR20, odr20 );
            data_array[ 0 ] = SET_REG_BITS(data_array[ 0 ], ENVIRONMENT3_ODR3, odr3 );
        }
    }
    
    if ( ENVIRONMENT3_OK == error_check )
    {
        error_check = environment3_set_regs ( ctx, reg_array, data_array, ENVIRONMENT3_LEN_CONFIG );
    }
    
    if ( ( ENVIRONMENT3_MODE_SLEEP != current_op_mode ) && ( ENVIRONMENT3_OK == error_check ) )
    {
        error_check = environment3_set_operating_mode( ctx, current_op_mode );
    }
    return error_check;
}

int8_t environment3_set_operating_mode ( environment3_t *ctx, uint8_t op_mode )
{
    int8_t error_check = 0;
    uint8_t tmp_pow_mode;
    uint8_t pow_mode = 0;
    uint8_t reg_addr = ENVIRONMENT3_REG_CTRL_MEAS;

    do
    {
        error_check = environment3_get_regs( ctx, ENVIRONMENT3_REG_CTRL_MEAS, &tmp_pow_mode, 1 );
        if ( ENVIRONMENT3_OK == error_check )
        {
            pow_mode = GET_REG_BITS_LOW( tmp_pow_mode, ENVIRONMENT3_MODE );
            if ( ENVIRONMENT3_MODE_SLEEP != pow_mode )
            {
                tmp_pow_mode = SET_REG_BITS_LOW( tmp_pow_mode, ENVIRONMENT3_MODE, ENVIRONMENT3_DISABLE );
                error_check = environment3_set_regs( ctx, &reg_addr, &tmp_pow_mode, 1 );
                Delay_10ms();
            }
        }
    } while ( ( ENVIRONMENT3_MODE_SLEEP != pow_mode ) && ( ENVIRONMENT3_OK == error_check ) );

    if ( ( ENVIRONMENT3_MODE_SLEEP != op_mode ) && ( ENVIRONMENT3_OK == error_check ) )
    {
        tmp_pow_mode = SET_REG_BITS_LOW( tmp_pow_mode, ENVIRONMENT3_MODE, op_mode );
        error_check = environment3_set_regs( ctx, &reg_addr, &tmp_pow_mode, 1 );
    }

    return error_check;
}

int8_t environment3_get_operating_mode ( environment3_t *ctx )
{
    uint8_t mode = 0;

    if ( ENVIRONMENT3_OK != environment3_get_regs( ctx, ENVIRONMENT3_REG_CTRL_MEAS, &mode, 1 ) )
    {
        return ENVIRONMENT3_ERROR;
    }

    return mode & ENVIRONMENT3_MODE_MASK;
}

// ------------------------------------------------------------------------- PRIVATE FUNCTIONS

static err_t environment3_i2c_write ( environment3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t environment3_i2c_read ( environment3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t environment3_spi_write ( environment3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg & ENVIRONMENT3_SPI_WRITE_MASK;
    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t environment3_spi_read ( environment3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t tx_data;
    
    tx_data = reg | ENVIRONMENT3_SPI_READ_MASK;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &tx_data, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static int8_t environment3_get_data ( environment3_t *ctx )
{
    int8_t error_check = 0;
    
    error_check = environment3_set_operating_mode( ctx, ENVIRONMENT3_MODE_FORCED );
    
    if ( ENVIRONMENT3_OK != error_check )
    {
        return error_check;
    }
    
    if ( ENVIRONMENT3_ENABLE == ctx->gas_sett.enable )
    {
        for ( uint16_t cnt = 0; cnt < ctx->gas_sett.heater_dur; cnt++ )
        {
            Delay_1ms( );
        }
    }

    Delay_1ms( );
    error_check = environment3_read_field_data( ctx, &ctx->f_data );
    
    return error_check;
}

static int8_t environment3_set_gas_config ( environment3_t *ctx, environment3_gas_settings_t *conf )
{
    uint8_t reg_addr[ 2 ] = { 0 };
    uint8_t reg_data[ 2 ] = { 0 };

    if ( ENVIRONMENT3_MODE_SLEEP == environment3_get_operating_mode( ctx ) )
    {
        reg_addr[ 0 ] = ENVIRONMENT3_REG_RES_HEAT_0;
        reg_data[ 0 ] = environment3_calc_heater_res( ctx, conf->heater_temp );
        reg_addr[ 1 ] = ENVIRONMENT3_REG_GAS_WAIT_0;
        reg_data[ 1 ] = environment3_calc_gas_wait( ctx, conf->heater_dur );
    }
    else
    {
        return ENVIRONMENT3_W_DEFINE_OP_MODE;
    }
    return environment3_set_regs( ctx, reg_addr, reg_data, 2 );
}

static int8_t environment3_set_mem_page ( environment3_t *ctx, uint8_t reg )
{
    uint8_t tmp_data;
    uint8_t mem_page;

    if ( reg > 0x7F )
    {
        mem_page = ENVIRONMENT3_MEM_PAGE_1;
    }
    else
    {
        mem_page = ENVIRONMENT3_MEM_PAGE_0;
    }
    
    if ( mem_page != ctx->device_mem_page )
    {
        ctx->device_mem_page = mem_page;

        if ( ENVIRONMENT3_OK != environment3_generic_read( ctx, ENVIRONMENT3_REG_MEM_PAGE, &tmp_data, 1 ) )
        {
            return ENVIRONMENT3_E_COM_FAIL;
        }
        
        tmp_data = SET_REG_BITS_LOW( tmp_data, ENVIRONMENT3_MEM_PAGE, ctx->device_mem_page );

        if ( ENVIRONMENT3_OK != environment3_generic_write( ctx, ENVIRONMENT3_REG_MEM_PAGE, &tmp_data, 1 ) )
        {
            return ENVIRONMENT3_E_COM_FAIL;
        }
    }

    return ENVIRONMENT3_OK;
}

static int8_t environment3_get_mem_page( environment3_t *ctx )
{
    uint8_t tmp_data;

    if ( ENVIRONMENT3_OK != environment3_generic_read( ctx, ENVIRONMENT3_REG_MEM_PAGE, &tmp_data, 1 ) )
    {
        return ENVIRONMENT3_E_COM_FAIL;
    }
    
    ctx->device_mem_page = tmp_data & ENVIRONMENT3_MEM_PAGE_MASK;
    
    return ENVIRONMENT3_OK;
}

static uint8_t environment3_calc_heater_res ( environment3_t *ctx, uint16_t temp )
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    int32_t var5;
    int32_t heater_res_x100;
    uint8_t heater_res;

    if ( temp > 400 )
    {
        temp = 400;
    }

    var1 = ( ( ( int32_t ) DEVICE_AMB_TEMP * ctx->calib.par_gh3 ) / 1000 ) * 256;
    var2 = ( ctx->calib.par_gh1 + 784 ) * ( ( ( ( ( ctx->calib.par_gh2 + 154009 ) * 
                                                    temp * 5 ) / 100 ) + 3276800 ) / 10 );
    var3 = var1 + ( var2 / 2 );
    var4 = ( var3 / ( ctx->calib.res_heat_range + 4 ) );
    var5 = ( 131 * ctx->calib.res_heat_val ) + 65536;

    heater_res_x100 = ( int32_t ) ( ( ( var4 / var5 ) - 250 ) * 34 );
    heater_res = ( uint8_t ) ( ( heater_res_x100 + 50 ) / 100 );

    return heater_res;
}

static uint8_t environment3_calc_gas_wait ( environment3_t *ctx, uint16_t dur )
{
    uint8_t factor = 0;
    uint8_t durval;

    if ( dur >= 0xFC0 )
    {
        durval = 0xFF;
    }
    else
    {
        while ( dur > 0x3F )
        {
            dur = dur / 4;
            factor += 1;
        }
        durval = ( uint8_t ) ( dur + ( factor * 64 ) );
    }

    return durval;
}

static int8_t environment3_boundary_check ( environment3_t *ctx, uint8_t *value, uint8_t min, uint8_t max )
{
    if ( 0 != value )
    {
        if ( *value < min )
        {
            *value = min;
        }
        if ( *value > max )
        {
            *value = max;
        }
    }
    else
    {
        return ENVIRONMENT3_E_NULL_PTR;
    }

    return ENVIRONMENT3_OK;
}

static float environment3_calc_temperature ( environment3_t *ctx, uint32_t temp_adc )
{
    float var1;
    float var2;
    float calc_temp;

    var1 = ( ( ( ( float ) temp_adc / 16384.0 ) - ( ( float ) ctx->calib.par_t1 / 1024.0 ) ) *
                 ( ( float ) ctx->calib.par_t2 ) );
    
    var2 = ( ( ( ( ( float ) temp_adc / 131072.0 ) - ( ( float ) ctx->calib.par_t1 / 8192.0 ) ) *
               ( ( ( float ) temp_adc / 131072.0 ) - ( ( float ) ctx->calib.par_t1 / 8192.0 ) ) ) * 
                 ( ( float ) ctx->calib.par_t3 * 16.0 ) );
    ctx->calib.t_fine = var1 + var2;
    calc_temp = ctx->calib.t_fine / 5120.0;

    return calc_temp;
}

static float environment3_calc_humidity ( environment3_t *ctx, uint16_t hum_adc )
{
    float var1;
    float var2;
    float var3;
    float var4;
    float temp_scaled;
    float calc_hum;

    temp_scaled = ctx->calib.t_fine / 5120.0;
    var1 = ( float ) hum_adc - ( ( ( float ) ctx->calib.par_h1 * 16.0 ) + 
                               ( ( ( float ) ctx->calib.par_h3 / 2.0 ) * temp_scaled ) );
    var2 = var1 * ( ( float ) ( ( ( float ) ctx->calib.par_h2 / 262144.0 ) * 
                              ( 1.0 + ( ( ( float ) ctx->calib.par_h4 / 16384.0 ) * temp_scaled ) + 
                              ( ( ( float ) ctx->calib.par_h5 / 1048576.0 ) * temp_scaled * temp_scaled ) ) ) );
    var3 = ( float ) ctx->calib.par_h6 / 16384.0;
    var4 = ( float ) ctx->calib.par_h7 / 2097152.0;
    calc_hum = var2 + ( ( var3 + ( var4 * temp_scaled ) ) * var2 * var2 );

    if ( calc_hum > 100.0 )
    {
        calc_hum = 100.0;
    }
    else if ( calc_hum < 0.0 )
    {
        calc_hum = 0.0;
    }
    return calc_hum;
}

static float environment3_calc_pressure ( environment3_t *ctx, uint32_t pres_adc )
{
    float var1 = 0;
    float var2 = 0;
    float var3 = 0;
    float calc_pres = 0;

    var1 = ( float ) ( ctx->calib.t_fine ) / 2.0;
    var1 -= 64000.0;

    var2 = ( float ) ( ctx->calib.par_p6 ) / 131072.0;
    var2 *= var1 * var1;
    var2 += ( var1 * ( ( float ) ctx->calib.par_p5 ) * 2.0 );
    var2 = ( var2 / 4.0 ) + ( ( ( float ) ctx->calib.par_p4 ) * 65536.0 );

    var1 = ( ( ( ( ( float ) ctx->calib.par_p3 * var1 * var1 ) / 16384.0 ) + 
               ( ( float ) ctx->calib.par_p2 * var1 ) ) / 524288.0 );
    var1 = ( ( 1.0  + ( var1 / 32768.0 ) ) * ( ( float ) ctx->calib.par_p1 ) );
    calc_pres = ( 1048576.0 - ( ( float ) pres_adc ) );

    if ( 0 != ( int16_t ) var1 )
    {
        calc_pres = ( ( ( calc_pres - ( var2 / 4096.0 ) ) * 6250.0 ) / var1 );
        var1 = ( ( ( float ) ctx->calib.par_p9 ) * calc_pres * calc_pres ) / 2147483648.0;
        var2 = calc_pres * ( ( ( float ) ctx->calib.par_p8 ) / 32768.0 );
        var3 = ( calc_pres / 256.0 ) * ( calc_pres / 256.0 ) * 
               ( calc_pres / 256.0 ) * ( ctx->calib.par_p10 / 131072.0 );
        calc_pres = calc_pres + ( var1 + var2 + var3 + ( ( float ) ctx->calib.par_p7 * 128.0 ) ) / 16.0;
    }
    else
    {
        calc_pres = 0;
    }

    return calc_pres;
}

static float environment3_calc_gas_resistance_high ( environment3_t *ctx, uint16_t gas_res_adc, uint8_t gas_range )
{
    float calc_gas_res;
    uint32_t var1 = 262144ul >> gas_range;
    int32_t var2 = ( int32_t ) gas_res_adc - 512;

    var2 *= 3;
    var2 += 4096;

    calc_gas_res = 1000000.0 * ( float ) var1 / ( float ) var2;
    
    return calc_gas_res;
}

static float environment3_calc_gas_resistance_low ( environment3_t *ctx, uint16_t gas_res_adc, uint8_t gas_range )
{
    float calc_gas_res;
    float var1 = 0;
    float var2 = 0;
    float var3 = 0;
    const float lookup_k1_range[ 16 ] =
    {
        0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -0.8,
        0.0, 0.0, -0.2, -0.5, 0.0, -1.0, 0.0, 0.0
    };
    const float lookup_k2_range[ 16 ] =
    {
        0.0, 0.0, 0.0, 0.0, 0.1, 0.7, 0.0, -0.8,
        -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    };

    var1 = 5.0 * ctx->calib.range_sw_err;
    var1 += 1340.0;

    var2 = lookup_k1_range[ gas_range ] / 100.0;
    var2 += 1.0;
    var2 *= var1;

    var3 = lookup_k2_range[ gas_range ] / 100.0;
    var3 += 1.0;

    calc_gas_res = 1.0 / ( float )( var3 * 0.000000125 * ( float ) ( 1 << gas_range ) * 
                  ( ( ( ( ( float ) gas_res_adc ) - 512.0 ) / var2 ) + 1.0 ) );

    return calc_gas_res;
}

static int8_t environment3_read_field_data ( environment3_t *ctx, environment3_field_data_t *f_data )
{
    uint8_t buff[ ENVIRONMENT3_LEN_FIELD ] = { 0 };
    uint8_t gas_range_l, gas_range_h;
    uint32_t adc_temp;
    uint32_t adc_pres;
    uint16_t adc_hum;
    uint16_t adc_gas_res_low, adc_gas_res_high;
    uint8_t tries = 5;
    
    if ( 0 == f_data )
    {
        return ENVIRONMENT3_E_NULL_PTR;
    }
    
    do
    {
        if ( ENVIRONMENT3_OK == environment3_get_regs( ctx, ENVIRONMENT3_REG_MEAS_STATUS_FIELD_0, 
                                                            buff, 
                                                            ENVIRONMENT3_LEN_FIELD ) )
        {
            f_data->status = buff[ 0 ] & ENVIRONMENT3_NEW_DATA_MASK;
            f_data->gas_index = buff[ 0 ] & ENVIRONMENT3_GAS_INDEX_MASK;
            f_data->meas_index = buff[ 1 ];

            adc_pres = ( uint32_t ) ( ( ( uint32_t ) buff[ 2 ] * 4096 ) | 
                                      ( ( uint32_t ) buff[ 3 ] * 16 ) | 
                                      ( ( uint32_t ) buff[ 4 ] / 16 ) );
            adc_temp = ( uint32_t ) ( ( ( uint32_t ) buff[ 5 ] * 4096 ) | 
                                      ( ( uint32_t ) buff[ 6 ] * 16 ) | 
                                      ( ( uint32_t ) buff[ 7 ] / 16 ) );
            adc_hum = ( uint16_t ) ( ( ( uint32_t ) buff[ 8 ] * 256 ) | ( uint32_t ) buff[ 9 ] );
            adc_gas_res_low = ( uint16_t ) ( ( uint32_t ) buff[ 13 ] * 4 | ( ( ( uint32_t ) buff[ 14 ] ) / 64 ) );
            adc_gas_res_high = ( uint16_t ) ( ( uint32_t ) buff[ 15 ] * 4 | ( ( ( uint32_t ) buff[ 16 ] ) / 64 ) );
            gas_range_l = buff[ 14 ] & ENVIRONMENT3_GAS_RANGE_MASK;
            gas_range_h = buff[ 16 ] & ENVIRONMENT3_GAS_RANGE_MASK;
            
            if ( ENVIRONMENT3_VARIANT_GAS_HIGH == ctx->device_variant_id )
            {
                f_data->status |= buff[ 16 ] & ENVIRONMENT3_GASM_VALID_MASK;
                f_data->status |= buff[ 16 ] & ENVIRONMENT3_HEAT_STAB_MASK;
            }
            else
            {
                f_data->status |= buff[ 14 ] & ENVIRONMENT3_GASM_VALID_MASK;
                f_data->status |= buff[ 14 ] & ENVIRONMENT3_HEAT_STAB_MASK;
            }
            
            if ( f_data->status & ENVIRONMENT3_NEW_DATA_MASK )
            {
                environment3_get_regs( ctx, ENVIRONMENT3_REG_RES_HEAT_0 + f_data->gas_index, 
                                            &f_data->res_heat, 1 );
                environment3_get_regs( ctx, ENVIRONMENT3_REG_IDAC_HEAT_0 + f_data->gas_index, 
                                            &f_data->idac, 1 );
                environment3_get_regs( ctx, ENVIRONMENT3_REG_GAS_WAIT_0 + f_data->gas_index, 
                                            &f_data->gas_wait, 1 );
                f_data->temperature = environment3_calc_temperature( ctx, adc_temp );
                f_data->pressure = environment3_calc_pressure( ctx, adc_pres );
                f_data->humidity = environment3_calc_humidity( ctx, adc_hum );
                
                if ( ENVIRONMENT3_VARIANT_GAS_HIGH == ctx->device_variant_id )
                {
                    f_data->gas_resistance = environment3_calc_gas_resistance_high( ctx, adc_gas_res_high, gas_range_h );
                }
                else
                {
                    f_data->gas_resistance = environment3_calc_gas_resistance_low( ctx, adc_gas_res_low, gas_range_l );
                }
                break;
            }
        }
        
        Delay_10ms();
        tries--;
    } while ( tries );

    if ( !tries )
    {
        return ENVIRONMENT3_W_NO_NEW_DATA;
    }
    
    return ENVIRONMENT3_OK;
}

static void environment3_get_calibration_data ( environment3_t *ctx )
{
    uint8_t coeff_array[ ENVIRONMENT3_LEN_COEFF_ALL ] = { 0 };
    uint8_t temp_var = 0;

    environment3_get_regs( ctx, ENVIRONMENT3_REG_COEFF_1, coeff_array,  ENVIRONMENT3_LEN_COEFF_1 );
    environment3_get_regs( ctx, ENVIRONMENT3_REG_COEFF_2, &coeff_array[ ENVIRONMENT3_LEN_COEFF_1 ], 
                                                          ENVIRONMENT3_LEN_COEFF_2 );
    environment3_get_regs( ctx, ENVIRONMENT3_REG_COEFF_3, &coeff_array[ ENVIRONMENT3_LEN_COEFF_1 + ENVIRONMENT3_LEN_COEFF_2 ], 
                                                          ENVIRONMENT3_LEN_COEFF_3 );

    /* Temperature related coefficients */
    ctx->calib.par_t1 = ( uint16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_T1_MSB ], 
                                                    coeff_array[ ENVIRONMENT3_IDX_T1_LSB ] );
    ctx->calib.par_t2 = ( int16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_T2_MSB ], 
                                                   coeff_array[ ENVIRONMENT3_IDX_T2_LSB ] );
    ctx->calib.par_t3 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_T3 ];

    /* Pressure related coefficients */
    ctx->calib.par_p1 = ( uint16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_P1_MSB ], 
                                                    coeff_array[ ENVIRONMENT3_IDX_P1_LSB ] );
    ctx->calib.par_p2 = ( int16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_P2_MSB ],
                                                   coeff_array[ ENVIRONMENT3_IDX_P2_LSB ] );
    ctx->calib.par_p3 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_P3 ];
    ctx->calib.par_p4 = ( int16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_P4_MSB ],
                                                   coeff_array[ ENVIRONMENT3_IDX_P4_LSB ] );
    ctx->calib.par_p5 = ( int16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_P5_MSB ],
                                                   coeff_array[ ENVIRONMENT3_IDX_P5_LSB ] );
    ctx->calib.par_p6 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_P6 ];
    ctx->calib.par_p7 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_P7 ];
    ctx->calib.par_p8 = ( int16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_P8_MSB ],
                                                   coeff_array[ ENVIRONMENT3_IDX_P8_LSB ] );
    ctx->calib.par_p9 = ( int16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_P9_MSB ],
                                                   coeff_array[ ENVIRONMENT3_IDX_P9_LSB ] );
    ctx->calib.par_p10 = ( uint8_t ) coeff_array[ ENVIRONMENT3_IDX_P10 ];

    /* Humidity related coefficients */
    ctx->calib.par_h1 = ( uint16_t ) ( ( uint16_t ) coeff_array[ ENVIRONMENT3_IDX_H1_MSB ] << 
                                                    ENVIRONMENT3_HUM_REG_SHIFT_VAL_MASK ) |
                                                  ( coeff_array[ ENVIRONMENT3_IDX_H1_LSB ] & 
                                                    ENVIRONMENT3_BIT_H1_DATA_MASK );
    ctx->calib.par_h2 = ( uint16_t ) ( ( uint16_t ) coeff_array[ ENVIRONMENT3_IDX_H2_MSB ] << 
                                                    ENVIRONMENT3_HUM_REG_SHIFT_VAL_MASK ) |
                                                  ( coeff_array[ENVIRONMENT3_IDX_H2_LSB] >> 
                                                    ENVIRONMENT3_HUM_REG_SHIFT_VAL_MASK );
    ctx->calib.par_h3 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_H3 ];
    ctx->calib.par_h4 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_H4 ];
    ctx->calib.par_h5 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_H5 ];
    ctx->calib.par_h6 = ( uint8_t ) coeff_array[ ENVIRONMENT3_IDX_H6 ];
    ctx->calib.par_h7 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_H7 ];

    /* Gas heater related coefficients */
    ctx->calib.par_gh1 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_GH1 ];
    ctx->calib.par_gh2 = ( int16_t ) BYTES_TO_WORD( coeff_array[ ENVIRONMENT3_IDX_GH2_MSB ],
                                                    coeff_array[ENVIRONMENT3_IDX_GH2_LSB] );
    ctx->calib.par_gh3 = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_GH3 ];

    /* Other coefficients */
    ctx->calib.res_heat_range = ( coeff_array[ ENVIRONMENT3_IDX_RES_HEAT_RANGE ] & ENVIRONMENT3_RHRANGE_MASK ) / 16;
    ctx->calib.res_heat_val = ( int8_t ) coeff_array[ ENVIRONMENT3_IDX_RES_HEAT_VAL ];
    ctx->calib.range_sw_err = ( ( int8_t ) ( coeff_array[ ENVIRONMENT3_IDX_RANGE_SW_ERR ] & 
                                             ENVIRONMENT3_RSERROR_MASK ) ) / 16;
}

static int8_t environment3_read_variant_id ( environment3_t *ctx )
{
    uint8_t reg_data = 0;

    /* Read variant ID information register */
    if ( ENVIRONMENT3_OK == environment3_get_regs( ctx, ENVIRONMENT3_REG_VARIANT_ID, &reg_data, 1 ) )
    {
        ctx->device_variant_id = reg_data;
        return ENVIRONMENT3_OK;
    }
    return ENVIRONMENT3_ERROR;
}

// ------------------------------------------------------------------------ END
