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

#include "c10dof.h"

// ------------------------------------------------------------- PRIVATE MACROS 

static int8_t oversampling;
static uint8_t slave_address_BNO055;
static int16_t ac1_param;
static int16_t ac2_param;
static int16_t ac3_param;
static uint16_t ac4_param;
static uint16_t ac5_param;
static uint16_t ac6_param;
static int16_t b1_param;
static int16_t b2_param;
static int16_t mb_param;
static int16_t mc_param;
static int16_t md_param;
static uint32_t adc_T;
static uint32_t adc_P;
static uint32_t adc_H;
static uint32_t t_fine;
static uint16_t dig_t1;
static int16_t dig_t2;
static int16_t dig_t3;
static uint8_t dig_h1;
static int16_t dig_h2;
static uint8_t dig_h3;
static int16_t dig_h4;
static int16_t dig_h5;
static int8_t dig_h6;
static uint16_t dig_p1;
static int16_t dig_p2;
static int16_t dig_p3;
static int16_t dig_p4;
static int16_t dig_p5;
static int16_t dig_p6;
static int16_t dig_p7;
static int16_t dig_p8;
static int16_t dig_p9;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static int32_t compensate_t ( void );

static uint32_t compensate_h ( void );

static uint32_t compensate_p ( void );

static void hw_medium_delay ( void );

static void hw_small_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c10dof_cfg_setup ( c10dof_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x00;
}

C10DOF_RETVAL c10dof_init ( c10dof_t *ctx, c10dof_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    oversampling = 0;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return C10DOF_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C10DOF_OK;

}

void c10dof_default_cfg ( c10dof_t *ctx ) 
{
    c10dof_hw_reset( ctx );
    Delay_1sec( );
    c10dof_default_configuration_BMP180( ctx );
    hw_medium_delay( );
    c10dof_default_configuration_BNO055 ( ctx );
}

void c10dof_write_byte ( c10dof_t *ctx, uint8_t reg, uint8_t data_in, uint8_t slave_addr )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ]= reg;
    tx_buf[ 1 ]= data_in;

    ctx->slave_address = slave_addr;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_write( &ctx->i2c, tx_buf, 2 ); 
    hw_small_delay( );
}

uint8_t c10dof_read_byte ( c10dof_t *ctx, uint8_t reg, uint8_t slave_addr )
{
    uint8_t rx_buf[ 1 ];

    ctx->slave_address = slave_addr;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, 1 );

    return rx_buf[ 0 ];
}

uint16_t c10dof_read_data ( c10dof_t *ctx, uint8_t msb_reg, uint8_t slave_addr )
{
    uint8_t msb_data;
    uint8_t lsb_data;
    uint16_t result;

    msb_data = c10dof_read_byte( ctx, msb_reg, slave_addr );
    hw_small_delay( );
    lsb_data = c10dof_read_byte( ctx, msb_reg + 1, slave_addr );

    result = msb_data;
    result <<= 8;
    result |= lsb_data;

    return result;
}

void c10dof_hw_reset ( c10dof_t *ctx )
{
    digital_out_low( &ctx->rst );
    hw_medium_delay( );
    digital_out_high( &ctx->rst );
    hw_medium_delay( );
}

uint8_t c10dof_bmp180_chip_ID ( c10dof_t *ctx )
{
    uint8_t id_value;

    id_value = c10dof_read_byte( ctx, C10DOF_BMP180_CHIP_ID_REG, C10DOF_BMP180_ADDRESS );

    return id_value;
}

uint8_t c10dof_bno055_chip_ID ( c10dof_t *ctx )
{
    uint8_t id_value;

    id_value = c10dof_read_byte( ctx, C10DOF_BNO055_ID, C10DOF_BNO055_ADDRESS_A );

    return id_value;
}

uint8_t c10dof_get_accel_ID ( c10dof_t *ctx )
{
    uint8_t id_value;

    id_value = c10dof_read_byte( ctx, C10DOF_BNO055_ACCEL_REV_ID_ADDR, C10DOF_BNO055_ADDRESS_A );

    return id_value;
}

uint8_t c10dof_get_mag_ID ( c10dof_t *ctx )
{
    uint8_t id_value;

    id_value = c10dof_read_byte( ctx, C10DOF_BNO055_MAG_REV_ID_ADDR, C10DOF_BNO055_ADDRESS_A );

    return id_value;
}

uint8_t c10dof_get_gyro_ID ( c10dof_t *ctx )
{
    uint8_t id_value;

    id_value = c10dof_read_byte( ctx, C10DOF_BNO055_GYRO_REV_ID_ADDR, C10DOF_BNO055_ADDRESS_A );

    return id_value;
}


uint16_t c10dof_get_soft_ID ( c10dof_t *ctx )
{
    uint16_t result;
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = c10dof_read_byte( ctx, C10DOF_BNO055_SW_REV_ID_MSB_ADDR, C10DOF_BNO055_ADDRESS_A );
    hw_small_delay( );
    tx_buf[ 1 ] = c10dof_read_byte( ctx, C10DOF_BNO055_SW_REV_ID_LSB_ADDR, C10DOF_BNO055_ADDRESS_A );

    result = tx_buf[ 0 ];
    result <<= 8;
    result |= tx_buf[ 1 ];

    return result;
}

uint8_t c10dof_get_page_ID ( c10dof_t *ctx )
{
    uint8_t id_value;

    id_value = c10dof_read_byte( ctx, C10DOF_BNO055_PAGE_ID_ADDR, C10DOF_BNO055_ADDRESS_A );

    return id_value;
}

void c10dof_default_configuration_BMP180 ( c10dof_t *ctx )
{
    c10dof_write_byte( ctx, C10DOF_BMP180_REG_CONF_ADDR, 0x00, C10DOF_BMP180_ADDRESS );
    hw_small_delay( );

    c10dof_write_byte( ctx, C10DOF_BMP180_PWR_MODE_ADDR, 0x00, C10DOF_BMP180_ADDRESS );
    hw_small_delay( );

    c10dof_write_byte( ctx, C10DOF_BMP180_OPR_MODE_ADDR, 0x0C, C10DOF_BMP180_ADDRESS );
}

void c10dof_default_configuration_BNO055 ( c10dof_t *ctx )
{
    c10dof_write_byte( ctx, C10DOF_BNO055_OPR_MODE_ADDR, 0x00, C10DOF_BNO055_ADDRESS_A );
    hw_medium_delay( );

    c10dof_write_byte( ctx, C10DOF_BNO055_PAGE_ID_ADDR, 0x01, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_ACCEL_DATA_X_LSB_ADDR, 0x0D, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_ACCEL_DATA_Y_LSB_ADDR, 0x18, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_ACCEL_DATA_Y_MSB_ADDR, 0x00, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_ACCEL_DATA_X_MSB_ADDR, 0x06, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_PAGE_ID_ADDR, 0x00, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_UNIT_SEL_ADDR, 0x01, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_TEMP_SOURCE_ADDR, 0x01, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_PWR_MODE_ADDR, 0x00, C10DOF_BNO055_ADDRESS_A );

    c10dof_write_byte( ctx, C10DOF_BNO055_OPR_MODE_ADDR, 0x0C, C10DOF_BNO055_ADDRESS_A );
}

void c10dof_set_config_mode ( c10dof_t *ctx, uint8_t config_mode )
{
    config_mode %= 9;
    
    oversampling = config_mode;
    
    c10dof_write_byte( ctx, C10DOF_BNO055_OPR_MODE_ADDR, config_mode, C10DOF_BNO055_ADDRESS_A );
}

void c10dof_select_page ( c10dof_t *ctx, uint8_t page_number )
{
    page_number &= 0x01;

    c10dof_write_byte( ctx, C10DOF_BNO055_PAGE_ID_ADDR, page_number, C10DOF_BNO055_ADDRESS_A );
}

void c10dof_config_accel ( c10dof_t *ctx, uint8_t acc_cnfg )
{
    c10dof_write_byte( ctx, C10DOF_BNO055_ACCEL_DATA_X_LSB_ADDR, acc_cnfg, C10DOF_BNO055_ADDRESS_A );
}

void c10dof_config_gyro ( c10dof_t *ctx, uint8_t gyro_cnfg )
{
    c10dof_write_byte( ctx, C10DOF_BNO055_ACCEL_DATA_Y_LSB_ADDR, gyro_cnfg, C10DOF_BNO055_ADDRESS_A );
}

void c10dof_config_mag ( c10dof_t *ctx, uint8_t mag_cnfg )
{
    c10dof_write_byte( ctx, C10DOF_BNO055_ACCEL_DATA_Y_LSB_ADDR, mag_cnfg, C10DOF_BNO055_ADDRESS_A );
}

void c10dof_set_sensor_units ( c10dof_t *ctx, uint8_t sensor_units )
{
    c10dof_write_byte( ctx, C10DOF_BNO055_UNIT_SEL_ADDR, sensor_units, C10DOF_BNO055_ADDRESS_A );
}

uint8_t c10dof_get_system_status ( c10dof_t *ctx )
{
    uint8_t error_code;

    error_code = c10dof_read_byte( ctx, C10DOF_BNO055_SYS_STAT_ADDR, C10DOF_BNO055_ADDRESS_A );

    return error_code;
}

uint8_t c10dof_get_system_error ( c10dof_t *ctx )
{
    uint8_t error_code;

    error_code = c10dof_read_byte( ctx, C10DOF_BNO055_SYS_ERR_ADDR, C10DOF_BNO055_ADDRESS_A );

    return error_code;
}

void c10dof_set_mode ( c10dof_t *ctx, uint8_t mode_val )
{
    mode_val &= 0x03;
    
    if ( mode_val < 4 )
    {
        c10dof_write_byte( ctx, C10DOF_BNO055_PWR_MODE_ADDR, mode_val, C10DOF_BNO055_ADDRESS_A );
    }
}

void c10dof_set_normal_mode ( c10dof_t *ctx )
{
    c10dof_write_byte( ctx, C10DOF_BNO055_PWR_MODE_ADDR, 0x00, C10DOF_BNO055_ADDRESS_A );
}

void c10dof_start_temperature_measure ( c10dof_t *ctx )
{
    c10dof_write_byte( ctx, C10DOF_BMP180_CTRL_MEAS_REG, C10DOF_BMP180_T_MEASURE, C10DOF_BMP180_ADDRESS );
}

void c10dof_start_pressure_measure ( c10dof_t *ctx )
{
    c10dof_write_byte( ctx, C10DOF_BMP180_CTRL_MEAS_REG, C10DOF_BMP180_P_MEASURE, C10DOF_BMP180_ADDRESS );
}

int16_t c10dof_read_raw_temperature ( c10dof_t *ctx, uint8_t msb_reg )
{
    uint8_t msb_data;
    uint8_t lsb_data;
    int16_t result;

    msb_data = c10dof_read_byte( ctx, msb_reg, C10DOF_BMP180_ADDRESS );
    hw_small_delay( );
    lsb_data = c10dof_read_byte( ctx, msb_reg + 1, C10DOF_BMP180_ADDRESS );

    result = msb_data;
    result <<= 8;
    result |= lsb_data;

    return result;
}

int32_t c10dof_read_raw_pressure ( c10dof_t *ctx, uint8_t msb_addr )
{
    uint8_t msb_data;
    uint8_t lsb_data;
    uint8_t xlsb_data;
    int32_t result;

    result = 0;

    msb_data = c10dof_read_byte( ctx, msb_addr, C10DOF_BMP180_ADDRESS );
    hw_small_delay( );
    lsb_data = c10dof_read_byte( ctx, msb_addr + 1, C10DOF_BMP180_ADDRESS );
    hw_small_delay( );
    xlsb_data = c10dof_read_byte( ctx, msb_addr + 2, C10DOF_BMP180_ADDRESS );

    result = msb_data;
    result <<= 8;
    result |= lsb_data;
    result <<= 8;
    result |= xlsb_data;

    return result;
}

void c10dof_get_calib_param ( c10dof_t *ctx )
{
    ac1_param = ( int16_t ) c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_AC1_MSB, C10DOF_BMP180_ADDRESS );
    ac2_param = ( int16_t ) c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_AC2_MSB, C10DOF_BMP180_ADDRESS );
    ac3_param = ( int16_t ) c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_AC3_MSB, C10DOF_BMP180_ADDRESS );
    ac4_param = c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_AC4_MSB, C10DOF_BMP180_ADDRESS );
    ac5_param = c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_AC5_MSB, C10DOF_BMP180_ADDRESS );
    ac6_param = c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_AC6_MSB, C10DOF_BMP180_ADDRESS );
    b1_param = ( int16_t ) c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_B1_MSB, C10DOF_BMP180_ADDRESS );
    b2_param = ( int16_t ) c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_B2_MSB, C10DOF_BMP180_ADDRESS );
    mb_param = ( int16_t ) c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_MB_MSB, C10DOF_BMP180_ADDRESS );
    mc_param = ( int16_t ) c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_MC_MSB, C10DOF_BMP180_ADDRESS );
    md_param = ( int16_t ) c10dof_read_data( ctx, C10DOF_BMP180_REG_CALIB_PARAM_MD_MSB, C10DOF_BMP180_ADDRESS );
}

void c10dof_get_measurements( c10dof_t *ctx, float *temperature, float *pressure )
{
    int16_t temp_data;
    uint32_t pressure_data;
    int32_t x1;
    int32_t x2;
    int32_t x3;
    int32_t b3;
    int32_t b5;
    uint32_t b4;
    int32_t b6;
    uint32_t b7;
    int32_t press;

    temp_data = 0;
    pressure_data = 0;

    c10dof_get_calib_param( ctx );
    hw_small_delay( );

    c10dof_start_temperature_measure( ctx );
    hw_small_delay( );

    temp_data = c10dof_read_data( ctx, C10DOF_BMP180_ADC_OUT_MSB_REG, C10DOF_BMP180_ADDRESS );
    hw_small_delay( );

    c10dof_start_pressure_measure( ctx );
    hw_small_delay( );

    pressure_data = c10dof_read_raw_pressure( ctx, C10DOF_BMP180_ADC_OUT_MSB_REG );
    pressure_data >>= 8 - oversampling;

    x1 = ( temp_data - ( ( int32_t  ) ac6_param ) ) * ( ( int32_t ) ac5_param ) >> 15;
    x2 = ( ( ( int32_t ) mc_param ) << 11 ) / ( x1 + ( ( int32_t ) md_param ) );
    b5 = x1 + x2;
    *temperature = ( ( ( float ) b5 + 8.0 ) / 16.0 );

    *temperature /= 10.0;

    b6 = b5 - 4000;
    x1 = ( ( ( int32_t) b2_param ) * ( (b6 * b6) >> 12 ) ) >> 11;
    x2 = ( ( ( int32_t ) ac2_param ) * b6 ) >> 11;
    x3 = x1 + x2;
    b3 = ( ( ( ( ( ( int32_t ) ac1_param ) * 4 ) + x3 ) << oversampling ) + 2 ) / 4;

    x1 = ( ( ( int32_t ) ac3_param ) * b6 ) >> 13;
    x2 = ( ( (int32_t ) b1_param ) * ( ( b6 * b6 ) >> 12 ) ) >> 16;
    x3 = ( ( x1 + x2 ) + 2 ) >> 2;
    b4 = ( ( ( uint32_t ) ac4_param ) * ( uint32_t )( x3 + 32768 ) ) >> 15;
    b7 = ( ( ( uint32_t ) pressure_data ) - b3 ) * ( uint32_t )( 50000UL >> oversampling );

    if ( b7 < 0x80000000 )
    {
        press = ( b7 * 2 ) / b4;
    }
    else
    {
        press = ( b7 / b4 ) * 2;
    }

    x1 = ( press >> 8 ) * ( press >> 8 );
    x1 = ( x1 * 3038 ) >> 16;
    x2 = ( -7357 * press ) >> 16;

    press = press + ( ( x1 + x2 + 3791 ) >> 4 );

    *pressure = ( float ) press;
    *pressure /= 100.0;
}

float c10dof_get_temperature ( c10dof_t *ctx )
{
    int16_t temp_data;
    int32_t x1;
    int32_t x2;
    int32_t b5;
    float temperature;

    temp_data = 0;

    c10dof_get_calib_param ( ctx );
    hw_small_delay( );

    c10dof_start_temperature_measure ( ctx );
    hw_small_delay( );
    temp_data = c10dof_read_data( ctx, C10DOF_BMP180_ADC_OUT_MSB_REG, C10DOF_BMP180_ADDRESS );

    x1 = ( temp_data - ( ( int32_t  ) ac6_param ) ) * ( ( int32_t ) ac5_param ) >> 15;
    x2 = ( ( ( int32_t ) mc_param ) << 11 ) / ( x1 + ( ( int32_t ) md_param ) );
    b5 = x1+ x2;
    temperature = ( ( ( float ) b5 + 8.0 ) / 16.0 );
    temperature /= 10.0;

    return temperature;
}

float c10dof_get_pressure ( c10dof_t *ctx )
{
    int16_t temp_data;
    uint32_t pressure_data;
    int32_t x1;
    int32_t x2;
    int32_t x3;
    int32_t b3;
    int32_t b5;
    uint32_t b4;
    int32_t b6;
    uint32_t b7;
    int32_t press;
    float pressure;

    temp_data = 0;
    pressure_data = 0;

    c10dof_get_calib_param ( ctx );
    hw_small_delay( );

    c10dof_start_temperature_measure ( ctx );
    hw_small_delay( );

    temp_data = c10dof_read_data ( ctx, C10DOF_BMP180_ADC_OUT_MSB_REG, C10DOF_BMP180_ADDRESS );
    hw_small_delay( );

    c10dof_start_pressure_measure ( ctx );
    hw_small_delay( );

    pressure_data = c10dof_read_raw_pressure ( ctx, C10DOF_BMP180_ADC_OUT_MSB_REG );
    pressure_data >>= 8 - oversampling;

    x1 = ( temp_data - ( ( int32_t  ) ac6_param ) ) * ( ( int32_t ) ac5_param ) >> 15;
    x2 = ( ( ( int32_t ) mc_param ) << 11 ) / ( x1 + ( ( int32_t ) md_param ) );
    b5 = x1 + x2;

    b6 = b5 - 4000;
    x1 = ( ( ( int32_t) b2_param ) * ( (b6 * b6) >> 12 ) ) >> 11;
    x2 = ( ( ( int32_t ) ac2_param ) * b6 ) >> 11;
    x3 = x1 + x2;
    b3 = ( ( ( ( ( ( int32_t ) ac1_param ) * 4 ) + x3 ) << oversampling ) + 2 ) / 4;

    x1 = ( ( ( int32_t ) ac3_param ) * b6 ) >> 13;
    x2 = ( ( (int32_t ) b1_param ) * ( ( b6 * b6 ) >> 12 ) ) >> 16;
    x3 = ( ( x1 + x2 ) + 2 ) >> 2;
    b4 = ( ( ( uint32_t ) ac4_param ) * ( uint32_t )( x3 + 32768 ) ) >> 15;
    b7 = ( ( ( uint32_t ) pressure_data ) - b3 ) * ( uint32_t )( 50000UL >> oversampling );

    if ( b7 < 0x80000000 )
    {
        press = ( b7 * 2 ) / b4;
    }
    else
    {
        press = ( b7 / b4 ) * 2;
    }

    x1 = ( press >> 8 ) * ( press >> 8 );
    x1 = ( x1 * 3038 ) >> 16;
    x2 = ( -7357 * press ) >> 16;

    press = press + ( ( x1 + x2 + 3791 ) >> 4 );

    pressure = ( float ) press;
    pressure /= 100.0;
    
    return pressure;
}

int16_t c10dof_get_axis ( c10dof_t *ctx, uint8_t addr_reg_low )
{
    int16_t result;
    uint16_t temp;
    uint8_t buffer[ 2 ];

    buffer[ 0 ] = c10dof_read_byte( ctx, addr_reg_low + 1, C10DOF_BNO055_ADDRESS_A );
    Delay_10us();
    buffer[ 1 ] = c10dof_read_byte( ctx, addr_reg_low, C10DOF_BNO055_ADDRESS_A );

    temp = buffer[ 0 ];
    temp <<= 8;
    temp |= buffer[ 1 ];

    result = ( int16_t ) temp;

    return result;
}

void c10dof_read_accel ( c10dof_t *ctx, int16_t *accelX, int16_t *accelY, int16_t *accelZ )
{
    *accelX = c10dof_get_axis( ctx, C10DOF_BNO055_ACCEL_DATA_X_LSB_ADDR );
    *accelY = c10dof_get_axis( ctx, C10DOF_BNO055_ACCEL_DATA_Y_LSB_ADDR );
    *accelZ = c10dof_get_axis( ctx, C10DOF_BNO055_ACCEL_DATA_Z_LSB_ADDR );
}

void c10dof_read_mag ( c10dof_t *ctx, int16_t *magX, int16_t *magY, int16_t *magZ )
{
    *magX = c10dof_get_axis( ctx, C10DOF_BNO055_MAG_DATA_X_LSB_ADDR );
    *magY = c10dof_get_axis( ctx, C10DOF_BNO055_MAG_DATA_Y_LSB_ADDR );
    *magZ = c10dof_get_axis( ctx, C10DOF_BNO055_MAG_DATA_Z_LSB_ADDR );
}

void c10dof_read_gyro ( c10dof_t *ctx, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ )
{
    *gyroX = c10dof_get_axis( ctx, C10DOF_BNO055_GYRO_DATA_X_LSB_ADDR );
    *gyroY = c10dof_get_axis( ctx, C10DOF_BNO055_GYRO_DATA_Y_LSB_ADDR );
    *gyroZ = c10dof_get_axis( ctx, C10DOF_BNO055_GYRO_DATA_Z_LSB_ADDR );
}

uint8_t c10dof_check_interrupt ( c10dof_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static int32_t compensate_t ( void )
{
    int32_t temp1;
    int32_t temp2;
    int32_t val_t;

    temp1 = ( ( ( ( adc_T >> 3 ) -( ( int32_t )dig_t1 << 1 ) ) ) * ( ( int32_t )dig_t2 ) ) >> 11;
    temp2 = ( ( ( ( ( adc_T >> 4 ) - ( ( int32_t )dig_t1 ) ) * ( ( adc_T >> 4 ) - ( ( int32_t )dig_t1 ) ) ) >> 12 ) * ( ( int32_t )dig_t3 ) ) >> 14;
    t_fine = temp1 + temp2;
    val_t = ( t_fine * 5 + 128 ) >> 8;

    return val_t;
}

static uint32_t compensate_h ( void )
{
    int32_t val_hum;

    val_hum = ( t_fine - ( ( int32_t )76800 ) );

    val_hum = ( ( ( ( ( adc_H << 14 ) - ( ( ( int32_t )dig_h4 ) << 20 ) - ( ( ( int32_t )dig_h5 ) * val_hum ) ) +
             ( ( int32_t )16384 ) ) >> 15 ) * ( ( ( ( ( ( ( val_hum * ( ( int32_t )dig_h6 ) ) >> 10 ) *
             ( ( ( val_hum * ( ( int32_t )dig_h3 ) ) >> 11 ) + ( ( int32_t )32768 ) ) ) >> 10) +
             ( ( int32_t )2097152 ) ) * ( ( int32_t )dig_h2 ) + 8192 ) >> 14 ) );

    val_hum = ( val_hum - ( ( ( ( ( val_hum >> 15 ) * ( val_hum >> 15 ) ) >> 7 ) * ( ( int32_t )dig_h1 ) ) >> 4 ) );
    val_hum = ( val_hum < 0 ? 0 : val_hum );
    val_hum = ( val_hum > 419430400 ? 419430400 : val_hum );

    return ( uint32_t )( val_hum >> 12 );
}

static uint32_t compensate_p ( void )
{
    int32_t press1;
    int32_t  press2;
    uint32_t val_p;

    press1 = ( ( (int32_t)t_fine ) >> 1 ) - ( int32_t )64000;
    press2 = ( ( ( press1 >> 2 ) * ( press1 >> 2 ) ) >> 11 ) * ( ( int32_t )dig_p6 );
    press2 = press2 + ( ( press1 * ( ( int32_t )dig_p5 ) ) << 1 );
    press2 = ( press2 >> 2 ) + ( ( ( int32_t )dig_p4 ) << 16 );
    press1 = ( ( ( dig_p3 * ( ( ( press1 >> 2 ) * ( press1 >> 2 ) ) >> 13 ) ) >> 3 ) + ( ( ( ( int32_t )dig_p2 ) * press1 ) >> 1 ) ) >> 18;
    press1 =((((32768+press1))*((int32_t)dig_p1))>>15);

    if ( press1 == 0 )
    {
        return 0;
    }

    val_p = ( ( ( uint32_t )( ( ( int32_t )1048576 ) - adc_P ) - ( press2 >> 12 ) ) ) * 3125;

    if ( val_p < 0x80000000 )
    {
        val_p = ( val_p << 1 ) / ( ( uint32_t )press1 );
    }
    else
    {
        val_p = ( val_p / ( uint32_t )press1 ) * 2;
    }

    press1 = ( ( ( int32_t )dig_p9 ) * ( ( int32_t )( ( ( val_p >> 3 ) * ( val_p >> 3 ) ) >> 13 ) ) ) >> 12;
    press2 = ( ( ( int32_t )( val_p >> 2 ) ) * ( ( int32_t )dig_p8 ) ) >> 13;
    val_p = ( uint32_t )( ( int32_t )val_p + ( ( press1 + press2 + dig_p7 ) >> 4 ) );

    return val_p;
}


static void hw_small_delay ( void )
{
    Delay_10ms( );
}

static void hw_medium_delay ( void )
{
    Delay_100ms( );
}
// ------------------------------------------------------------------------- END

