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
 * @file airmotion.c
 * @brief Air Motion Click Driver.
 */

#include "airmotion.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Air Motion I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airmotion_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airmotion_i2c_write ( airmotion_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Motion I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airmotion_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airmotion_i2c_read ( airmotion_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Air Motion SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #airmotion_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airmotion_spi_write ( airmotion_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Motion SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #airmotion_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airmotion_spi_read ( airmotion_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Dev software reset delay function.
 * @details This function is used to ensure that software reset is performed correctly.
 * @return Nothing.
 * @note None.
 */
void dev_sw_reset_delay ( void );

/**
 * @brief Dev format data function.
 * @details This function is used to convert two bytes of data into a 16-bit value.
 * @param[in] data_in : Input data.
 * @return 16-bit value.
 * @note None.
 */
uint16_t dev_format_data ( uint8_t *data_in );

void airmotion_cfg_setup ( airmotion_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AIRMOTION_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = AIRMOTION_DRV_SEL_I2C;
}

void airmotion_drv_interface_selection ( airmotion_cfg_t *cfg, airmotion_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t airmotion_init ( airmotion_t *ctx, airmotion_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( AIRMOTION_DRV_SEL_I2C == ctx->drv_sel ) 
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
        ctx->slew_rate = AIRMOTION_SLEW_RATE_18nS;
        ctx->read_f  = airmotion_i2c_read;
        ctx->write_f = airmotion_i2c_write;
    } 
    else 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;
        ctx->spi_mode = cfg->spi_mode;

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
        ctx->slew_rate = AIRMOTION_SLEW_RATE_6nS;
        ctx->read_f  = airmotion_spi_read;
        ctx->write_f = airmotion_spi_write;
    }

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return AIRMOTION_OK;
}

err_t airmotion_default_cfg ( airmotion_t *ctx ) 
{
    err_t error_flag = AIRMOTION_OK;
    uint8_t temp_data;
   
    error_flag |= airmotion_configure_digital_interface( ctx, ctx->slew_rate );
    error_flag |= airmotion_sw_reset( ctx );
    error_flag |= airmotion_configure_digital_interface( ctx, ctx->slew_rate );

    // Disabling FIFO, we are reading data from registers.
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_FIFO_CONFIG, &temp_data, 1 );
    temp_data |= AIRMOTION_FIFO_BYPASS;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_FIFO_CONFIG, &temp_data, 1 );
    
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_FIFO_CONFIG1, &temp_data, 1 );
    temp_data &= ~( AIRMOTION_FIFO_RESUME_PARTIAL_RD | AIRMOTION_FIFO_WM_GT_TH | AIRMOTION_FIFO_TEMP_EN | 
                    AIRMOTION_FIFO_TEMP_EN | AIRMOTION_FIFO_GYRO_EN | AIRMOTION_FIFO_ACCEL_EN );
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_FIFO_CONFIG1, &temp_data, 1 );
    
    // Setting GYRO configuration.
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_GYRO_CONFIG0, &temp_data, 1 );
    temp_data &= ~AIRMOTION_GYRO_FS_SEL_MASK;
    temp_data |= AIRMOTION_GYRO_FS_SEL_2000DPS | AIRMOTION_GYRO_ODR_500Hz;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_GYRO_CONFIG0, &temp_data, 1 );
    
    // Setting ACCEL configuration.
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_ACCEL_CONFIG0, &temp_data, 1 );
    temp_data &= ~AIRMOTION_ACCEL_FS_SEL_MASK;
    temp_data |= AIRMOTION_ACCEL_FS_SEL_4G | AIRMOTION_ACCEL_ODR_500Hz_LP_LN;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_ACCEL_CONFIG0, &temp_data, 1 );
    
    // Enableing Timestamp data so it can be read.
    temp_data = AIRMOTION_TMST_TO_REGS_EN | AIRMOTION_TMST_RES | AIRMOTION_TMST_DELTA_EN | AIRMOTION_TMST_EN;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_TMST_CONFIG, &temp_data, 1 );
    
    // Setting INT1 and INT2 settings, in this case INT1 is used as Data ready flag, and INT2 is Reset done flag.  
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_CONFIG, &temp_data, 1 );
    temp_data |= ( AIRMOTION_INT_INT1_MODE_LATCHED | AIRMOTION_INT_INT1_PUSH_PULL | AIRMOTION_INT_INT1_ACTIVE_HIGH | 
                   AIRMOTION_INT_INT2_MODE_LATCHED | AIRMOTION_INT_INT2_PUSH_PULL | AIRMOTION_INT_INT2_ACTIVE_HIGH );
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_CONFIG, &temp_data, 1 );
    
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_CONFIG1, &temp_data, 1 );
    temp_data |= AIRMOTION_INT_ASYNC_RESET_DISABLE;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_CONFIG1, &temp_data, 1 );
    
    temp_data = AIRMOTION_INT_UI_DRDY_INT1_EN;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_SOURCE0, &temp_data, 1 );
    
    temp_data = AIRMOTION_INT_RESET_DONE_INT2_EN;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_SOURCE3, &temp_data, 1 );
    
    // Turnning on GYRO and ACCEL and setting them into Low Noise mode.
    temp_data = AIRMOTION_PWR_GYRO_LN_MODE | AIRMOTION_PWR_ACCEL_LN_MODE;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_PWR_MGMT0, &temp_data, 1 );
    
    return error_flag;
}

err_t airmotion_generic_write ( airmotion_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t airmotion_generic_read ( airmotion_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

static err_t airmotion_i2c_write ( airmotion_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t airmotion_i2c_read ( airmotion_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t airmotion_spi_write ( airmotion_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t airmotion_spi_read ( airmotion_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t airmotion_set_reg_bank( airmotion_t *ctx, uint8_t bank )
{
    return airmotion_generic_write( ctx, AIRMOTION_REG_BANK_SEL, &bank, 1 );
}

err_t airmotion_reg_write ( airmotion_t *ctx, uint8_t reg_bank, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = AIRMOTION_OK;
    
    error_flag |= airmotion_set_reg_bank( ctx, reg_bank );
    error_flag |= airmotion_generic_write( ctx, reg, data_in, len );

    return error_flag;
}

err_t airmotion_reg_read ( airmotion_t *ctx, uint8_t reg_bank, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = AIRMOTION_OK;
    
    error_flag |= airmotion_set_reg_bank( ctx, reg_bank );
    error_flag |= airmotion_generic_read( ctx, reg, data_out, len );
    
    return error_flag;
}

err_t airmotion_configure_digital_interface ( airmotion_t *ctx, uint8_t slew_rate )
{
    err_t error_flag = AIRMOTION_OK;
    
    if ( AIRMOTION_DRV_SEL_I2C == ctx->drv_sel )
    {
        uint8_t slew_rate_i2c;
        slew_rate_i2c = slew_rate << 3;
        
        error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_DRIVE_CONFIG, &slew_rate_i2c, 1 );
    }
    else
    {
        uint8_t spi_mode;
        if ( ( SPI_MASTER_MODE_0 == ctx->spi_mode ) || ( SPI_MASTER_MODE_3 == ctx->spi_mode ) )
        {
            spi_mode = AIRMOTION_SPI_MODE0_MODE3 << 4;
            error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_DEVICE_CONFIG, &spi_mode, 1 );
        }
        else
        {
            spi_mode = AIRMOTION_SPI_MODE1_MODE2 << 4;
            error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_DEVICE_CONFIG, &spi_mode, 1 );
        }
        
        error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_DRIVE_CONFIG, &slew_rate, 1 );
        spi_mode = AIRMOTION_SPI_4WIRE;
        error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INTF_CONFIG4, &spi_mode, 1 );
    }
    
    return error_flag;
}

uint8_t airmotion_get_int1_state ( airmotion_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t airmotion_get_int2_state ( airmotion_t *ctx )
{
    return digital_in_read( &ctx->an );
}


err_t airmotion_sw_reset( airmotion_t *ctx )
{
    err_t error_flag = AIRMOTION_OK;
    uint8_t temp_data;
    temp_data = AIRMOTION_ENABLE_SW_RESET;
    
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_DEVICE_CONFIG, &temp_data, 1 );
    dev_sw_reset_delay( );
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_STATUS, &temp_data, 1 );
    
    while ( 0 == ( temp_data & AIRMOTION_RESET_DONE_INT_FLAG ) )
    {
        error_flag = AIRMOTION_RESET_ERROR;
    }
    
    return error_flag;
}

err_t airmotion_read_temperature ( airmotion_t *ctx, float *temperature_data )
{
    err_t error_flag = AIRMOTION_OK;
    int16_t temperature;
    uint8_t read_data[ 2 ];
    
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_TEMP_DATA1, read_data, 2 );
    temperature = read_data[ 0 ];
    temperature <<= 8;
    temperature |= read_data[ 1 ];
    *temperature_data = ( ( ( float ) temperature ) / 132.48 ) + 25;
    
    return error_flag;
}

err_t airmotion_read_timestamp ( airmotion_t *ctx, uint32_t *tmst_data )
{
    err_t error_flag = AIRMOTION_OK;
    uint32_t time;
    uint8_t read_data[ 3 ];
    
    read_data[ 0 ] = AIRMOTION_TMST_STROBE;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_SIGNAL_PATH_RESET, read_data, 1 );
    
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK1_SEL, AIRMOTION_TMSTVAL0, read_data, 3 );
    
    time = read_data[ 2 ];
    time <<= 8;
    time |= read_data[ 1 ];
    time <<= 8;
    time |= read_data[ 0 ];
    
    *tmst_data = time;
    
    return error_flag;
}

err_t airmotion_get_data_from_register ( airmotion_t *ctx, float *temperature_data, 
                                         airmotion_data_t *accel_data, 
                                         airmotion_data_t *gyro_data, uint32_t *tmst_data )
{
    err_t error_flag = AIRMOTION_OK;
    uint16_t temp_data;
    uint8_t read_data[ 12 ];
    uint8_t int_status;
    
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_STATUS, &int_status, 1 );
    if ( AIRMOTION_DATA_RDY_INT_FLAG & int_status )
    {

        error_flag |= airmotion_read_temperature( ctx, temperature_data );

        error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_ACCEL_DATA_X1, read_data, 12 );
        temp_data = dev_format_data( &read_data[ 0 ] );
        accel_data->data_x = temp_data;
        
        temp_data = dev_format_data( &read_data[ 2 ] );
        accel_data->data_y = temp_data;
        
        temp_data = dev_format_data( &read_data[ 4 ] );
        accel_data->data_z = temp_data;
        
        temp_data = dev_format_data( &read_data[ 6 ] );
        gyro_data->data_x = temp_data;
        
        temp_data = dev_format_data( &read_data[ 8 ] );
        gyro_data->data_y = temp_data;
        
        temp_data = dev_format_data( &read_data[ 10 ] );
        gyro_data->data_z = temp_data;
        
        error_flag |= airmotion_read_timestamp( ctx, tmst_data );
    }
    else
    {
        error_flag = AIRMOTION_ERROR;
    }
    
    return error_flag;
}

err_t airmotion_set_basic_tap_detection ( airmotion_t *ctx )
{
    err_t error_flag = AIRMOTION_OK;
    uint8_t temp_data;
    
    error_flag |= airmotion_sw_reset( ctx );
    error_flag |= airmotion_configure_digital_interface( ctx, ctx->slew_rate );
    
    temp_data = ( AIRMOTION_INT_INT1_MODE_LATCHED | AIRMOTION_INT_INT1_PUSH_PULL | AIRMOTION_INT_INT1_ACTIVE_HIGH | 
                   AIRMOTION_INT_INT2_MODE_LATCHED | AIRMOTION_INT_INT2_PUSH_PULL | AIRMOTION_INT_INT2_ACTIVE_HIGH );
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_CONFIG, &temp_data, 1 );
    
    temp_data = AIRMOTION_ACCEL_FS_SEL_16G | AIRMOTION_ACCEL_ODR_500Hz_LP_LN;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_ACCEL_CONFIG0, &temp_data, 1 );
    
    temp_data = AIRMOTION_PWR_ACCEL_LP_MODE;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_PWR_MGMT0, &temp_data, 1 );
    
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_ACCEL_CONFIG1, &temp_data, 1 );
    temp_data |= AIRMOTION_ACCEL_DEC2_M2_ORD_3rd;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_ACCEL_CONFIG1, &temp_data, 1 );
    Delay_10ms();
    
    temp_data = AIRMOTION_TAP_TMAX | AIRMOTION_TAP_TAVG | AIRMOTION_TAP_TMIN;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK4_SEL, AIRMOTION_APEX_CONFIG8, &temp_data, 1 );
    
    temp_data = AIRMOTION_TAP_MIN_JERK_THR | AIRMOTION_TAP_MAX_OEAK_TOL;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK4_SEL, AIRMOTION_APEX_CONFIG7, &temp_data, 1 );
    Delay_10ms();
    
    temp_data = AIRMOTION_INT_SOURCE6_TAP_DET_INT1_EN;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK4_SEL, AIRMOTION_INT_SOURCE6, &temp_data, 1 );
    Delay_100ms();
    
    temp_data = AIRMOTION_TAP_ENABLE;
    error_flag |= airmotion_reg_write( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_APEX_CONFIG0, &temp_data, 1 );
    
    return error_flag;
}

err_t airmotion_get_tap_detection ( airmotion_t *ctx, uint8_t *tap_num, uint8_t *tap_axis, uint8_t *tap_dir )
{
    err_t error_flag = AIRMOTION_OK;
    uint8_t read_data;
    uint16_t temp_data;
    uint8_t int_status;
    
    error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_INT_STATUS3, &int_status, 1 );
    if ( AIRMOTION_TAP_DET_INT_FLAG & int_status )
    {
        error_flag |= airmotion_reg_read( ctx, AIRMOTION_BANK0_SEL, AIRMOTION_APEX_DATA4, &read_data, 1 );
        *tap_num = read_data & AIRMOTION_TAP_NUM_MASK;
        *tap_axis = read_data & AIRMOTION_TAP_AXIS_MASK;
        *tap_dir = read_data & AIRMOTION_TAP_DIR_MASK;
    }
    else
    {
        error_flag = AIRMOTION_ERROR;
    }
    
    return error_flag;
}

// ---------------------- PRIVATE FUNTIONS ----------------------

uint16_t dev_format_data ( uint8_t *data_in )
{
    return ( ( data_in[ 0 ] << 8 ) | data_in[ 1 ] );
}

void dev_sw_reset_delay ( void )
{
    Delay_5500us();
}



// ------------------------------------------------------------------------ END
