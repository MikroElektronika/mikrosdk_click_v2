/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "weather.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define WEATHER_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static err_t weather_i2c_write ( weather_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
static err_t weather_i2c_read ( weather_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
static err_t weather_spi_write ( weather_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
static err_t weather_spi_read ( weather_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

static float compensate_temperature ( weather_t *ctx, uint32_t temp_raw_data );
static float compensate_humidity ( weather_t *ctx, uint32_t hum_raw_data );
static float compensate_pressure ( weather_t *ctx, uint32_t press_raw_data );

// Read measurements function
static err_t read_raw_data ( weather_t *ctx, weather_raw_data_t *raw_data );
// Read factory calibration parameters
static err_t read_calibration_params ( weather_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void weather_cfg_setup ( weather_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = WEATHER_I2C_ADDRESS_0;
    cfg->sel = WEATHER_MASTER_I2C;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t weather_init ( weather_t *ctx, weather_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( WEATHER_MASTER_I2C == ctx->master_sel )
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

        ctx->read_f = weather_i2c_read;
        ctx->write_f = weather_i2c_write;
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

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, WEATHER_DUMMY ) ) 
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

        ctx->read_f = weather_spi_read;
        ctx->write_f = weather_spi_write;
    }

    return WEATHER_OK;
}

err_t weather_default_cfg ( weather_t *ctx )
{
    err_t error_flag = WEATHER_OK;
    uint8_t device_id = 0;
    error_flag |= weather_get_device_id ( ctx, &device_id );
    if ( WEATHER_DEF_CHIP_ID != device_id )
    {
        return WEATHER_ERROR;
    }

    error_flag |= read_calibration_params ( ctx );
    
    weather_measurement_cfg_t measure_cfg;
    
    // Click default configuration
    measure_cfg.os_hum         = WEATHER_HUM_OS_1X;
    measure_cfg.os_temp        = WEATHER_MCTRL_TEMP_OS_2X;
    measure_cfg.os_press       = WEATHER_MCTRL_PRESS_OS_16X;
    measure_cfg.mode           = WEATHER_MCTRL_MODE_NORMAL;
    measure_cfg.filter         = WEATHER_CFG_FILTER_16;
    measure_cfg.standby_time   = WEATHER_CFG_STANDBY_TIME_500ms;
    
    error_flag |= weather_measurement_cfg ( ctx, &measure_cfg );
    
    Delay_1sec ( );
    
    return error_flag;
}

err_t weather_generic_write ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_buf, len );
}

err_t weather_generic_read ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_buf, len );
}

err_t weather_get_device_id ( weather_t *ctx, uint8_t *device_id )
{
    return weather_generic_read( ctx, WEATHER_REG_CHIP_ID, device_id, 1 );
}

err_t weather_software_reset ( weather_t *ctx )
{
    uint8_t tx_data = WEATHER_SOFT_RESET;
    return weather_generic_write ( ctx, WEATHER_REG_RESET, &tx_data, 1 );
}

err_t weather_get_ambient_data( weather_t *ctx, weather_data_t *weather_data )
{
    err_t error_flag = WEATHER_OK;
    weather_raw_data_t raw_data;

    error_flag |= read_raw_data ( ctx, &raw_data );

    weather_data->temperature = compensate_temperature( ctx, raw_data.temperature );
    weather_data->humidity    = compensate_humidity( ctx, raw_data.humidity );
    weather_data->pressure    = compensate_pressure( ctx, raw_data.pressure );
    return error_flag;
}

err_t weather_measurement_cfg ( weather_t *ctx, weather_measurement_cfg_t *cfg )
{
    err_t error_flag = WEATHER_OK;
    uint8_t tmp = cfg->os_hum;
    error_flag |= weather_generic_write ( ctx, WEATHER_REG_CTRL_HUMIDITY, &tmp, 1 );

    tmp = cfg->os_press;
    tmp |= cfg->os_temp;
    tmp |= cfg->mode;
    error_flag |= weather_generic_write ( ctx, WEATHER_REG_CTRL_MEASUREMENT, &tmp, 1 );

    tmp = cfg->standby_time;
    tmp |= cfg->filter;
    error_flag |= weather_generic_write ( ctx, WEATHER_REG_CONFIG, &tmp, 1 );
    return error_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static err_t weather_i2c_write ( weather_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t weather_i2c_read ( weather_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t weather_spi_write ( weather_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t reg_adr = reg & 0x7F;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_adr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t weather_spi_read ( weather_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t reg_adr = reg | 0x80;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static float compensate_temperature ( weather_t *ctx, uint32_t temp_raw_data )
{
    int32_t temp1 = 0;
    int32_t temp2 = 0;
    int32_t val_temp = 0;
    float out_data = 0;

    temp1 = ( ( ( temp_raw_data >> 3 ) - ( ( int32_t ) ctx->calib_params.temp_1 << 1 ) ) * 
              ( ( int32_t ) ctx->calib_params.temp_2 ) ) >> 11;
    temp2 = ( ( ( ( ( temp_raw_data >> 4 ) - ( ( int32_t ) ctx->calib_params.temp_1 ) ) * 
                  ( ( temp_raw_data >> 4 ) - ( ( int32_t ) ctx->calib_params.temp_1 ) ) ) >> 12 ) * 
              ( ( int32_t ) ctx->calib_params.temp_3 ) ) >> 14;
    ctx->calib_params.t_fine = temp1 + temp2;
    val_temp = ( ctx->calib_params.t_fine * 5 + 128 ) >> 8;

    out_data = val_temp / 100.0;
    return out_data;
}

static float compensate_humidity ( weather_t *ctx, uint32_t hum_raw_data )
{
    float val_hum = 0;

    val_hum = ( ( float ) ctx->calib_params.t_fine - 76800.0 );

    val_hum = ( hum_raw_data - ( ( ( float ) ctx->calib_params.hum_4 ) * 64.0 + 
                                 ( ( float ) ctx->calib_params.hum_5 ) / 16384.0 * val_hum ) ) * 
              ( ( ( float ) ctx->calib_params.hum_2 ) / 65536.0 * 
                ( 1.0 + ( ( float ) ctx->calib_params.hum_6 ) / 67108864.0 * val_hum * 
                        ( 1.0 + ( ( float ) ctx->calib_params.hum_3 ) / 67108864.0 * val_hum ) ) );
    val_hum = val_hum * ( 1.0 - ( ( float ) ctx->calib_params.hum_1 ) * val_hum / 524288.0 );

    if ( val_hum > 100.0 )
    {
        val_hum = 100.0;
    }
    else if ( val_hum < 0.0 )
    {
        val_hum = 0.0;
    }
    return val_hum;
}

static float compensate_pressure ( weather_t *ctx, uint32_t press_raw_data )
{
    int32_t press1 = 0;
    int32_t  press2 = 0;
    uint32_t val_pres = 0;
    float out_data = 0;

    press1 = ( ( ( int32_t ) ctx->calib_params.t_fine ) >> 1 ) - ( int32_t ) 64000;
    press2 = ( ( ( press1 >> 2 ) * ( press1 >> 2 ) ) >> 11 ) * ( ( int32_t ) ctx->calib_params.press_6 );
    press2 = press2 + ( ( press1 * ( ( int32_t ) ctx->calib_params.press_5 ) ) << 1 );
    press2 = ( press2 >> 2 ) + ( ( ( int32_t ) ctx->calib_params.press_4 ) << 16 );
    press1 = ( ( ( ctx->calib_params.press_3 * ( ( ( press1 >> 2 ) * ( press1 >> 2 ) ) >> 13 ) ) >> 3 ) + 
               ( ( ( ( int32_t ) ctx->calib_params.press_2 ) * press1 ) >> 1 ) ) >> 18;
    press1 = ( ( ( ( 32768 + press1 ) ) * ( ( int32_t ) ctx->calib_params.press_1 ) ) >> 15 );

    if ( press1 == 0 )
    {
        return 0;
    }

    val_pres = ( ( ( uint32_t ) ( ( ( int32_t ) 1048576 ) - press_raw_data ) - ( press2 >> 12 ) ) ) * 3125;

    if ( val_pres < 0x80000000ul )
    {
        val_pres = ( val_pres << 1 ) / ( ( uint32_t ) press1 );
    }
    else
    {
        val_pres = ( val_pres / ( uint32_t ) press1 ) * 2;
    }

    press1 = ( ( ( int32_t ) ctx->calib_params.press_9 ) * ( ( int32_t ) ( ( ( val_pres >> 3 ) * ( val_pres >> 3 ) ) >> 13 ) ) ) >> 12;
    press2 = ( ( ( int32_t ) ( val_pres >> 2 ) ) * ( ( int32_t ) ctx->calib_params.press_8 ) ) >> 13;
    val_pres = ( uint32_t )( ( int32_t ) val_pres + ( ( press1 + press2 + ctx->calib_params.press_7 ) >> 4 ) );

    out_data = val_pres / 100.0;
    return out_data;
}

// Read measurements function
static err_t read_raw_data ( weather_t *ctx, weather_raw_data_t *raw_data )
{
    err_t error_flag = WEATHER_OK;
    uint8_t rx_buffer[ 8 ] = { 0 };

    error_flag |= weather_generic_read( ctx, WEATHER_REG_RAW_DATA, rx_buffer, 8 );

    raw_data->humidity = rx_buffer[ 7 ];
    raw_data->humidity |= ( ( uint32_t ) rx_buffer[ 6 ] << 8 );

    raw_data->temperature  = ( ( uint32_t ) rx_buffer[ 5 ] >> 4 );
    raw_data->temperature |= ( ( uint32_t ) rx_buffer[ 4 ] << 4 );
    raw_data->temperature |= ( ( uint32_t ) rx_buffer[ 3 ] << 12 );

    raw_data->pressure  = ( ( uint32_t ) rx_buffer[ 2 ] >> 4 );
    raw_data->pressure |= ( ( uint32_t ) rx_buffer[ 1 ] << 4 );
    raw_data->pressure |= ( ( uint32_t ) rx_buffer[ 0 ] << 12 );
    return error_flag;
}

// Read factory calibration parameters
static err_t read_calibration_params ( weather_t *ctx )
{
    err_t error_flag = WEATHER_OK;
    uint8_t rx_buffer[ 26 ] = { 0 };

    error_flag |= weather_generic_read( ctx, WEATHER_REG_CALIB_TEMPERATURE, rx_buffer, 26 );
    ctx->calib_params.temp_1  = rx_buffer[ 1 ];
    ctx->calib_params.temp_1 <<= 8;
    ctx->calib_params.temp_1 |= rx_buffer[ 0 ];

    ctx->calib_params.temp_2  = rx_buffer[ 3 ];
    ctx->calib_params.temp_2 <<= 8;
    ctx->calib_params.temp_2 |= rx_buffer[ 2 ];

    ctx->calib_params.temp_3  = rx_buffer[ 5 ];
    ctx->calib_params.temp_3 <<= 8;
    ctx->calib_params.temp_3 |= rx_buffer[ 4 ];

    ctx->calib_params.press_1  = rx_buffer[ 7 ];
    ctx->calib_params.press_1 <<= 8;
    ctx->calib_params.press_1 |= rx_buffer[ 6 ];

    ctx->calib_params.press_2  = rx_buffer[ 9 ];
    ctx->calib_params.press_2 <<= 8;
    ctx->calib_params.press_2 |= rx_buffer[ 8 ];

    ctx->calib_params.press_3  = rx_buffer[ 11 ];
    ctx->calib_params.press_3 <<= 8;
    ctx->calib_params.press_3 |= rx_buffer[ 10 ];

    ctx->calib_params.press_4  = rx_buffer[ 13 ];
    ctx->calib_params.press_4 <<= 8;
    ctx->calib_params.press_4 |= rx_buffer[ 12 ];

    ctx->calib_params.press_5  = rx_buffer[ 15 ];
    ctx->calib_params.press_5 <<= 8;
    ctx->calib_params.press_5 |= rx_buffer[ 14 ];

    ctx->calib_params.press_6  = rx_buffer[ 17 ];
    ctx->calib_params.press_6 <<= 8;
    ctx->calib_params.press_6 |= rx_buffer[ 16 ];

    ctx->calib_params.press_7  = rx_buffer[ 19 ];
    ctx->calib_params.press_7 <<= 8;
    ctx->calib_params.press_7 |= rx_buffer[ 18 ];

    ctx->calib_params.press_8  = rx_buffer[ 21 ];
    ctx->calib_params.press_8 <<= 8;
    ctx->calib_params.press_8 |= rx_buffer[ 20 ];

    ctx->calib_params.press_9  = rx_buffer[ 23 ];
    ctx->calib_params.press_9 <<= 8;
    ctx->calib_params.press_9 |= rx_buffer[ 22 ];
    
    ctx->calib_params.hum_1  = rx_buffer[ 25 ];

    error_flag |= weather_generic_read( ctx, WEATHER_REG_CALIB_HUM_2_LSB, rx_buffer, 7 );
    ctx->calib_params.hum_2  = rx_buffer[ 1 ];
    ctx->calib_params.hum_2 <<= 8;
    ctx->calib_params.hum_2 |= rx_buffer[ 0 ];
    ctx->calib_params.hum_3  = rx_buffer[ 2 ];
    ctx->calib_params.hum_4  = rx_buffer[ 3 ];
    ctx->calib_params.hum_4 <<= 4;
    ctx->calib_params.hum_4 |= rx_buffer[ 4 ] & 0x0F;
    ctx->calib_params.hum_5  = rx_buffer[ 5 ];
    ctx->calib_params.hum_5 <<= 4;
    ctx->calib_params.hum_5 |= ( rx_buffer[ 4 ] >> 4 );
    ctx->calib_params.hum_6  = rx_buffer[ 6 ];
    return error_flag;
}
// ------------------------------------------------------------------------- END

