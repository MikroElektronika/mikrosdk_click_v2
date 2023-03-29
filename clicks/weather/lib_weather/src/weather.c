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

// -------------------------------------------------------------- PRIVATE TYPES

typedef struct
{
    // Temperature digital value
    uint16_t temp_1;
    int16_t  temp_2;
    int16_t  temp_3;
    // Humidity digital value
    uint8_t  hum_1;
    int16_t  hum_2;
    uint8_t  hum_3;
    int16_t  hum_4;
    int16_t  hum_5;
    int8_t   hum_6;
    // Pressure digital value
    uint16_t press_1;
    int16_t  press_2;
    int16_t  press_3;
    int16_t  press_4;
    int16_t  press_5;
    int16_t  press_6;
    int16_t  press_7;
    int16_t  press_8;
    int16_t  press_9;

    uint32_t t_fine;

} weather_digital_data_t;

typedef struct
{
    uint32_t temperature;
    uint32_t pressure;
    uint32_t humidity;

} weather_raw_data_t;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void weather_i2c_write ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void weather_i2c_read ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void weather_spi_write ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void weather_spi_read ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static float compensate_temperature ( uint32_t temp_raw_data, weather_digital_data_t *dig_data );
static float compensate_humidity ( uint32_t hum_raw_data, weather_digital_data_t *dig_data  );
static float compensate_pressure ( uint32_t press_raw_data, weather_digital_data_t *dig_data );

// Read measurements function
static void read_raw_data ( weather_t *ctx, weather_raw_data_t *raw_data );
// Read factory calibration parameters
static void read_calibration_params ( weather_t *ctx, weather_digital_data_t *dig_data );

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

WEATHER_RETVAL weather_init ( weather_t *ctx, weather_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set

    ctx->master_sel = cfg->sel;

if ( ctx->master_sel == WEATHER_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return WEATHER_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = weather_i2c_read;
        ctx->write_f = weather_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        spi_cfg.default_write_data = WEATHER_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  WEATHER_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, WEATHER_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f = weather_spi_read;
        ctx->write_f = weather_spi_write;
    }

    return WEATHER_OK;
}

void weather_default_cfg ( weather_t *ctx )
{
    weather_measurement_cfg_t measure_cfg;

    // Click default configuration

    measure_cfg.os_hum         = WEATHER_HUM_OS_1X;
    measure_cfg.os_temp        = WEATHER_MCTRL_TEMP_OS_2X;
    measure_cfg.os_press       = WEATHER_MCTRL_PRESS_OS_16X;
    measure_cfg.mode           = WEATHER_MCTRL_MODE_NORMAL;
    measure_cfg.filter         = WEATHER_CFG_FILTER_16;
    measure_cfg.standby_time   = WEATHER_CFG_STANDBY_TIME_10ms;

    weather_measurement_cfg ( ctx, &measure_cfg );
}

void weather_generic_write ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len );
}

void weather_generic_read ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t weather_get_device_id ( weather_t *ctx )
{
    uint8_t rx_data;

    weather_generic_read( ctx, WEATHER_REG_CHIP_ID, &rx_data, 1 );
    return rx_data;
}

void weather_software_reset ( weather_t *ctx )
{
    uint8_t tx_data;

    tx_data = WEATHER_SOFT_RESET;
    weather_generic_write ( ctx, WEATHER_REG_RESET, &tx_data, 1);
}

void weather_get_ambient_data( weather_t *ctx, weather_data_t *weather_data )
{
    weather_raw_data_t raw_data;
    weather_digital_data_t dig_data;

    read_raw_data ( ctx, &raw_data );
    read_calibration_params ( ctx, &dig_data );

    weather_data->temperature = compensate_temperature( raw_data.temperature, &dig_data );
    weather_data->humidity    = compensate_humidity( raw_data.humidity, &dig_data );
    weather_data->pressure    = compensate_pressure( raw_data.pressure, &dig_data );
}

void weather_measurement_cfg ( weather_t *ctx, weather_measurement_cfg_t *cfg )
{
    uint8_t tmp;

    tmp = cfg->os_hum;
    weather_generic_write ( ctx, WEATHER_REG_CTRL_HUMIDITY, &tmp, 1);

    tmp = cfg->os_press;
    tmp |= cfg->os_temp;
    tmp |= cfg->mode;
    weather_generic_write ( ctx, WEATHER_REG_CTRL_MEASUREMENT, &tmp, 1);

    tmp = cfg->standby_time;
    tmp |= cfg->filter;
    weather_generic_write ( ctx, WEATHER_REG_CONFIG, &tmp, 1);
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void weather_i2c_write ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 ); 
}

static void weather_i2c_read ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void weather_spi_write ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len );
    spi_master_deselect_device( ctx->chip_select );
}

static void weather_spi_read ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len );
    spi_master_deselect_device( ctx->chip_select );  

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt ];
    }
}

static float compensate_temperature ( uint32_t temp_raw_data, weather_digital_data_t *dig_data )
{
    int32_t temp1;
    int32_t temp2;
    int32_t val_temp;
    float out_data;

    temp1 = ( ( ( ( temp_raw_data >> 3 ) - ( ( int32_t )dig_data->temp_1 << 1 ) ) ) * ( ( int32_t )dig_data->temp_2 ) ) >> 11;
    temp2 = ( ( ( ( ( temp_raw_data >> 4 ) - ( ( int32_t )dig_data->temp_1 ) ) * ( ( temp_raw_data >> 4 ) -
            ( ( int32_t )dig_data->temp_1 ) ) ) >> 12 ) * ( ( int32_t )dig_data->temp_3 ) ) >> 14;
    dig_data->t_fine = temp1 + temp2;
    val_temp = ( dig_data->t_fine * 5 + 128 ) >> 8;

    out_data = val_temp / 100.0;
    return out_data;
}

static float compensate_humidity ( uint32_t hum_raw_data, weather_digital_data_t *dig_data  )
{
    int32_t val_hum;
    float out_data;

    val_hum = ( dig_data->t_fine - ( ( int32_t )76800 ) );

    val_hum = ( ( ( ( ( hum_raw_data << 14 ) - ( ( ( int32_t )dig_data->hum_4 ) << 20 ) - ( ( ( int32_t )dig_data->hum_5 ) * val_hum ) ) +
             ( ( int32_t )16384 ) ) >> 15 ) * ( ( ( ( ( ( ( val_hum * ( ( int32_t )dig_data->hum_6 ) ) >> 10 ) *
             ( ( ( val_hum * ( ( int32_t )dig_data->hum_3 ) ) >> 11 ) + ( ( int32_t )32768 ) ) ) >> 10) +
             ( ( int32_t )2097152 ) ) * ( ( int32_t )dig_data->hum_2 ) + 8192 ) >> 14 ) );

    val_hum = ( val_hum - ( ( ( ( ( val_hum >> 15 ) * ( val_hum >> 15 ) ) >> 7 ) * ( ( int32_t )dig_data->hum_1 ) ) >> 4 ) );
    val_hum = ( val_hum < 0 ? 0 : val_hum );
    val_hum = ( val_hum > 419430400 ? 419430400 : val_hum );

    out_data = ( val_hum >> 12 ) / 1024.0;
    return out_data;
}

static float compensate_pressure ( uint32_t press_raw_data, weather_digital_data_t *dig_data )
{
    int32_t press1;
    int32_t  press2;
    uint32_t val_pres;
    float out_data;

    press1 = ( ( (int32_t)dig_data->t_fine ) >> 1 ) - ( int32_t )64000;
    press2 = ( ( ( press1 >> 2 ) * ( press1 >> 2 ) ) >> 11 ) * ( ( int32_t )dig_data->press_6 );
    press2 = press2 + ( ( press1 * ( ( int32_t )dig_data->press_5 ) ) << 1 );
    press2 = ( press2 >> 2 ) + ( ( ( int32_t )dig_data->press_4 ) << 16 );
    press1 = ( ( ( dig_data->press_3 * ( ( ( press1 >> 2 ) * ( press1 >> 2 ) ) >> 13 ) ) >> 3 ) + ( ( ( ( int32_t )dig_data->press_2 ) * press1 ) >> 1 ) ) >> 18;
    press1 =((((32768+press1))*((int32_t)dig_data->press_1))>>15);

    if ( press1 == 0 )
    {
        return 0;
    }

    val_pres = ( ( ( uint32_t )( ( ( int32_t )1048576 ) - press_raw_data ) - ( press2 >> 12 ) ) ) * 3125;

    if ( val_pres < 0x80000000 )
    {
        val_pres = ( val_pres << 1 ) / ( ( uint32_t )press1 );
    }
    else
    {
        val_pres = ( val_pres / ( uint32_t )press1 ) * 2;
    }

    press1 = ( ( ( int32_t )dig_data->press_9 ) * ( ( int32_t )( ( ( val_pres >> 3 ) * ( val_pres >> 3 ) ) >> 13 ) ) ) >> 12;
    press2 = ( ( ( int32_t )( val_pres >> 2 ) ) * ( ( int32_t )dig_data->press_8 ) ) >> 13;
    val_pres = ( uint32_t )( ( int32_t )val_pres + ( ( press1 + press2 + dig_data->press_7 ) >> 4 ) );

    out_data = val_pres / 100.0;
    return out_data;
}

// Read measurements function
static void read_raw_data ( weather_t *ctx, weather_raw_data_t *raw_data )
{
    uint8_t rx_buffer [ 8 ];

    weather_generic_read( ctx, WEATHER_REG_RAW_DATA, rx_buffer, 8);

    raw_data->humidity = rx_buffer [ 7 ];
    raw_data->humidity |= ( uint32_t )rx_buffer[ 6 ] << 8;

    raw_data->temperature  = ( uint32_t )rx_buffer[ 5 ] >> 4;
    raw_data->temperature |= ( uint32_t )rx_buffer[ 4 ] << 4;
    raw_data->temperature |= ( uint32_t )rx_buffer[ 3 ] << 12;

    raw_data->pressure  = ( uint32_t )rx_buffer[ 2 ] >> 4;
    raw_data->pressure |= ( uint32_t )rx_buffer[ 1 ] << 4;
    raw_data->pressure |= ( uint32_t )rx_buffer[ 0 ] << 12;
}


// Read factory calibration parameters
static void read_calibration_params ( weather_t *ctx, weather_digital_data_t *dig_data )
{
    uint8_t rx_buffer [ 18 ];

    weather_generic_read( ctx, WEATHER_REG_CALIB_TEMPERATURE, rx_buffer, 6);
    dig_data->temp_1  = rx_buffer[ 1 ];
    dig_data->temp_1 <<= 8;
    dig_data->temp_1 |= rx_buffer[ 0 ];

    dig_data->temp_2  = rx_buffer[ 3 ];
    dig_data->temp_2 <<= 8;
    dig_data->temp_2 |= rx_buffer[ 2 ];

    dig_data->temp_3  = rx_buffer[ 5 ];
    dig_data->temp_3 <<= 8;
    dig_data->temp_3 |= rx_buffer[ 4 ];


    weather_generic_read( ctx, WEATHER_REG_CALIB_PRESSURE, rx_buffer, 18);
    dig_data->press_1  = rx_buffer[ 1 ];
    dig_data->press_1 <<= 8;
    dig_data->press_1 |= rx_buffer[ 0 ];

    dig_data->press_2  = rx_buffer[ 3 ];
    dig_data->press_2 <<= 8;
    dig_data->press_2 |= rx_buffer[ 2 ];

    dig_data->press_3  = rx_buffer[ 5 ];
    dig_data->press_3 <<= 8;
    dig_data->press_3 |= rx_buffer[ 4 ];

    dig_data->press_4  = rx_buffer[ 7 ];
    dig_data->press_4 <<= 8;
    dig_data->press_4 |= rx_buffer[ 6 ];

    dig_data->press_5  = rx_buffer[ 9 ];
    dig_data->press_5 <<= 8;
    dig_data->press_5 |= rx_buffer[ 8 ];

    dig_data->press_6  = rx_buffer[ 11 ];
    dig_data->press_6 <<= 8;
    dig_data->press_6 |= rx_buffer[ 10 ];

    dig_data->press_7  = rx_buffer[ 13 ];
    dig_data->press_7 <<= 8;
    dig_data->press_7 |= rx_buffer[ 12 ];

    dig_data->press_8  = rx_buffer[ 15 ];
    dig_data->press_8 <<= 8;
    dig_data->press_8 |= rx_buffer[ 14 ];

    dig_data->press_9  = rx_buffer[ 17 ];
    dig_data->press_9 <<= 8;
    dig_data->press_9 |= rx_buffer[ 16 ];


    weather_generic_read( ctx, WEATHER_REG_CALIB_HUMIDITY, rx_buffer, 9);
    dig_data->hum_1  = rx_buffer[ 0 ];
    dig_data->hum_2  = rx_buffer[ 2 ];
    dig_data->hum_2 <<= 8;
    dig_data->hum_2 |= rx_buffer[ 1 ];
    dig_data->hum_3  = rx_buffer[ 3 ];
    dig_data->hum_4  = rx_buffer[ 5 ];
    dig_data->hum_4 <<= 4;
    dig_data->hum_4 |= rx_buffer[ 4 ] & 0x0F;
    dig_data->hum_5  = rx_buffer[ 7 ];
    dig_data->hum_5 <<= 4;
    dig_data->hum_5 |= ( rx_buffer[ 6 ] >> 4 );
    dig_data->hum_6  = rx_buffer[ 8 ];
}
// ------------------------------------------------------------------------- END

