/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright ( c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files ( the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 */

#include "c13dof.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// Macro to combine two 8 bit data's to form a 16 bit data 
#define BME680_CONCAT_BYTES(msb, lsb)        ( ( ( uint16_t )msb << 8) | ( uint16_t )lsb)

// Macro to SET and GET BITS of a register
#define BME680_SET_BITS( reg_data, bitname, data) \
                ( ( reg_data & ~(bitname##_MSK ) ) | \
                ( (data << bitname##_POS) & bitname##_MSK ) )


// Macro variant to handle the bitname position if it is zero
#define BME680_SET_BITS_POS_0( reg_data, bitname, data) \
                                ( ( reg_data & ~(bitname##_MSK ) ) | \
                                (data & bitname##_MSK ) )

// ----------------------------------------------------------------- CONSTANTS
static const float lookup_k1_range[16] =
{
    0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -0.8,
    0.0, 0.0, -0.2, -0.5, 0.0, -1.0, 0.0, 0.0
};
static const float lookup_k2_range[16] =
{
    0.0, 0.0, 0.0, 0.0, 0.1, 0.7, 0.0, -0.8,
    -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

static const int8_t device_amb_temp = 25;


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static int8_t user_read_data( c13dof_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );

static int8_t user_write_data( c13dof_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );

static int8_t bme680_get_regs( c13dof_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );

static int8_t bme680_set_regs( c13dof_t *ctx, uint8_t *reg_addr, uint8_t *reg_data, uint8_t len );

static int8_t bme680_set_sensor_settings( c13dof_t *ctx, uint16_t desired_settings ) ;

static int8_t bme680_set_sensor_mode( c13dof_t *ctx );

static int8_t bme680_set_gas_config( c13dof_t *ctx );

static int16_t bme680_calc_temperature( c13dof_t *ctx, uint32_t temp_adc );

static uint32_t bme680_calc_humidity( c13dof_t *ctx, uint16_t hum_adc );

static uint8_t bme680_calc_heater_res( c13dof_t *ctx, uint16_t temp );

static float bme680_calc_pressure( c13dof_t *ctx, uint32_t pres_adc );

static float bme680_calc_gas_resistance( c13dof_t *ctx, uint16_t gas_res_adc, uint8_t gas_range );

static uint8_t bme680_calc_heater_dur( c13dof_t *ctx, uint16_t dur );

static int8_t bme680_read_field_data( c13dof_t *ctx, T_C13DOF_BME680_FIELD_DATA *d_data );

static int8_t bme680_set_mem_page( c13dof_t *ctx, uint8_t reg_addr);

static int8_t bme680_boundary_check( c13dof_t *ctx, uint8_t *value, uint8_t min, uint8_t max);

static void reset_delay ( void );

static void transfer_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c13dof_cfg_setup ( c13dof_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->bme680_slave_address = C13DOF_BME680_DEVICE_SLAVE_ADDR_0;
    cfg->bmm150_slave_address = C13DOF_BMM150_DEVICE_SLAVE_ADDR;
    cfg->bmi088Gyro_slave_address = C13DOF_BMI088_GYRO_SLAVE_ADDR;
    cfg->bmi088Accel_slave_address = C13DOF_BMI088_ACCEL_SLAVE_ADDR;
}

C13DOF_RETVAL c13dof_init ( c13dof_t *ctx, c13dof_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->bme680_slave_address = cfg->bme680_slave_address;
    ctx->bmm150_slave_address = cfg->bmm150_slave_address;
    ctx->bmi088Gyro_slave_address = cfg->bmi088Gyro_slave_address;
    ctx->bmi088Accel_slave_address = cfg->bmi088Accel_slave_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_SUCCESS )
    {
        return C13DOF_INIT_ERROR;
    }

    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return C13DOF_OK;
}

void c13dof_default_cfg ( c13dof_t *ctx )
{
    c13dof_bme680_soft_reset( ctx );
    c13dof_bme680_get_calibration_data( ctx );
    
    c13dof_bmm150_power_on_reset( ctx );
    c13dof_bmm150_write_byte( ctx, C13DOF_BMM150_DATAREADY_ACTIVE_HIGH, C13DOF_BMM150_INTERR_AND_CHANNEL_EN_REG );
    
    c13dof_bmi088_soft_reset_accel( ctx );
    c13dof_bmi088_set_accel_mode( ctx,  1 );
    c13dof_bmi088_enable_accel( ctx);
    
    ctx->tph_sett.os_hum = C13DOF_BME680_OS_2X;
    ctx->tph_sett.os_pres = C13DOF_BME680_OS_4X;
    ctx->tph_sett.os_temp = C13DOF_BME680_OS_8X;
    ctx->tph_sett.filter = C13DOF_BME680_FILTER_SIZE_3;

    ctx->gas_sett.run_gas = C13DOF_BME680_ENABLE_GAS_MEAS;

    ctx->gas_sett.heatr_temp = 320;
    ctx->gas_sett.heatr_dur = 150;

    ctx->device_power_mode = C13DOF_BME680_FORCED_MODE;

    bme680_set_sensor_settings( ctx,  C13DOF_BME680_OST_SEL |
                               C13DOF_BME680_OSP_SEL |
                               C13DOF_BME680_OSH_SEL |
                               C13DOF_BME680_FILTER_SEL |
                               C13DOF_BME680_GAS_SENSOR_SEL );
    bme680_set_sensor_mode( ctx );
    
    c13dof_bme680_get_temperature( ctx ); // dummy read
}

void c13dof_bme680_write_byte ( c13dof_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 1 ] = write_data;

    i2c_master_set_slave_address( &ctx->i2c, ctx->bme680_slave_address );
    i2c_master_write( &ctx->i2c, w_buffer, 2 ); 
}

uint8_t c13dof_bme680_read_byte ( c13dof_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 1 ];

    i2c_master_set_slave_address( &ctx->i2c, ctx->bme680_slave_address );

    i2c_master_write_then_read( &ctx->i2c, &reg_address, 1, r_buffer, 1 );

    return r_buffer[ 0 ];
}

C13DOF_BME680_RETVAL_T c13dof_bme680_check_id ( c13dof_t *ctx )
{
    uint8_t temp_id;

    temp_id = c13dof_bme680_read_byte( ctx, C13DOF_BME680_CHIP_ID_ADDR );

    if ( temp_id != 0x61 )
    {
        return C13DOF_BME680_ERROR;
    }

    return C13DOF_BME680_OK;
}


uint8_t c13dof_bme680_get_device_id ( c13dof_t *ctx )
{
    uint8_t device_id;

    c13dof_bme680_write_byte( ctx, 0x73, 0x00 );

    device_id = c13dof_bme680_read_byte( ctx, C13DOF_BME680_CHIP_ID_ADDR );

    return device_id;
}


void c13dof_bme680_soft_reset ( c13dof_t *ctx )
{
    uint8_t reg_addr;
    uint8_t soft_rst_cmd;
    uint8_t reg;

    reg_addr = C13DOF_BME680_SOFT_RESET_ADDR;
    soft_rst_cmd = C13DOF_BME680_SOFT_RESET_CMD;

    bme680_set_regs( ctx, &reg_addr, &soft_rst_cmd, 1 );
    Delay_10ms();
}

void c13dof_bme680_get_calibration_data ( c13dof_t *ctx )
{
    uint8_t coeff_array[ C13DOF_BME680_COEFF_SIZE ] = { 0 };
    uint8_t temp_var = 0;

    bme680_get_regs( ctx, C13DOF_BME680_COEFF_ADDR1, coeff_array,  C13DOF_BME680_COEFF_ADDR1_LEN );
    bme680_get_regs( ctx, C13DOF_BME680_COEFF_ADDR2, &coeff_array[ C13DOF_BME680_COEFF_ADDR1_LEN ], C13DOF_BME680_COEFF_ADDR2_LEN );

    ctx->calib.par_t1 = ( uint16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_T1_MSB_REG ], coeff_array[ C13DOF_BME680_T1_LSB_REG ] ) );
    ctx->calib.par_t2 = ( int16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_T2_MSB_REG ], coeff_array[ C13DOF_BME680_T2_LSB_REG ] ) );
    ctx->calib.par_t3 = ( int8_t ) ( coeff_array[ C13DOF_BME680_T3_REG ]);

    ctx->calib.par_p1 = ( uint16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_P1_MSB_REG ], coeff_array[ C13DOF_BME680_P1_LSB_REG ] ) );
    ctx->calib.par_p2 = ( int16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_P2_MSB_REG ], coeff_array[ C13DOF_BME680_P2_LSB_REG ] ) );
    ctx->calib.par_p3 = ( int8_t ) coeff_array[ C13DOF_BME680_P3_REG ];
    ctx->calib.par_p4 = ( int16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_P4_MSB_REG ], coeff_array[ C13DOF_BME680_P4_LSB_REG ] ) );
    ctx->calib.par_p5 = ( int16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_P5_MSB_REG ], coeff_array[ C13DOF_BME680_P5_LSB_REG ] ) );
    ctx->calib.par_p6 = ( int8_t ) ( coeff_array[ C13DOF_BME680_P6_REG ]);
    ctx->calib.par_p7 = ( int8_t ) ( coeff_array[ C13DOF_BME680_P7_REG ]);
    ctx->calib.par_p8 = ( int16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_P8_MSB_REG ], coeff_array[ C13DOF_BME680_P8_LSB_REG ] ) );
    ctx->calib.par_p9 = ( int16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_P9_MSB_REG ], coeff_array[ C13DOF_BME680_P9_LSB_REG ] ) );
    ctx->calib.par_p10 = ( uint8_t ) ( coeff_array[ C13DOF_BME680_P10_REG ]);

    ctx->calib.par_h1 = ( uint16_t ) ( ( ( uint16_t ) coeff_array[ C13DOF_BME680_H1_MSB_REG ] << C13DOF_BME680_HUM_REG_SHIFT_VAL)
       | ( coeff_array[ C13DOF_BME680_H1_LSB_REG ] & C13DOF_BME680_BIT_H1_DATA_MSK ) );
    ctx->calib.par_h2 = ( uint16_t ) ( ( ( uint16_t ) coeff_array[ C13DOF_BME680_H2_MSB_REG ] << C13DOF_BME680_HUM_REG_SHIFT_VAL)
       | ( ( coeff_array[ C13DOF_BME680_H2_LSB_REG ]) >> C13DOF_BME680_HUM_REG_SHIFT_VAL ) );
    ctx->calib.par_h3 = ( int8_t ) coeff_array[ C13DOF_BME680_H3_REG ];
    ctx->calib.par_h4 = ( int8_t ) coeff_array[ C13DOF_BME680_H4_REG ];
    ctx->calib.par_h5 = ( int8_t ) coeff_array[ C13DOF_BME680_H5_REG ];
    ctx->calib.par_h6 = ( uint8_t ) coeff_array[ C13DOF_BME680_H6_REG ];
    ctx->calib.par_h7 = ( int8_t ) coeff_array[ C13DOF_BME680_H7_REG ];

    ctx->calib.par_gh1 = ( int8_t ) coeff_array[ C13DOF_BME680_GH1_REG ];
    ctx->calib.par_gh2 = ( int16_t ) ( BME680_CONCAT_BYTES( coeff_array[ C13DOF_BME680_GH2_MSB_REG ], coeff_array[ C13DOF_BME680_GH2_LSB_REG ] ) );
    ctx->calib.par_gh3 = ( int8_t ) coeff_array[ C13DOF_BME680_GH3_REG ];

    bme680_get_regs( ctx, C13DOF_BME680_ADDR_RES_HEAT_RANGE_ADDR, &temp_var, 1 );
    ctx->calib.res_heat_range = ( ( temp_var & C13DOF_BME680_RHRANGE_MSK) / 16 );

    bme680_get_regs( ctx, C13DOF_BME680_ADDR_RES_HEAT_VAL_ADDR, &temp_var, 1 );
    ctx->calib.res_heat_val = ( int8_t ) temp_var;

    bme680_get_regs( ctx, C13DOF_BME680_ADDR_RANGE_SW_ERR_ADDR, &temp_var, 1 );
    ctx->calib.range_sw_err = ( ( int8_t ) temp_var & ( int8_t ) C13DOF_BME680_RSERROR_MSK ) / 16;
}


float c13dof_bme680_get_ambient_data ( c13dof_t *ctx, uint8_t data_in )
{
    bme680_read_field_data( ctx, &ctx->d_data );

    if ( ctx->device_power_mode == C13DOF_BME680_FORCED_MODE )
    {
        bme680_set_sensor_mode( ctx );
    }

    if ( data_in == C13DOF_BME680_DATA_TEMPERATURE )
    {
        return ( float )ctx->d_data.temperature / 100.0;
    }
    else if ( data_in == C13DOF_BME680_DATA_PRESSURE )
    {
        return ( float )ctx->d_data.pressure / 100.0;
    }
    else if ( data_in == C13DOF_BME680_DATA_HUMIDITY )
    {
        return ( float )ctx->d_data.humidity / 1000.0;
    }
    else
    {
        return 1;
    }
}

float c13dof_bme680_get_temperature ( c13dof_t *ctx )
{
    float temperature;

    temperature = c13dof_bme680_get_ambient_data( ctx, C13DOF_BME680_DATA_TEMPERATURE );

    return temperature;
}

float c13dof_bme680_get_humidity ( c13dof_t *ctx )
{
    float humidity;

    humidity = c13dof_bme680_get_ambient_data( ctx, C13DOF_BME680_DATA_HUMIDITY );

    return humidity;
}

float c13dof_bme680_get_pressure ( c13dof_t *ctx )
{
    float pressure;

    pressure = c13dof_bme680_get_ambient_data( ctx, C13DOF_BME680_DATA_PRESSURE );

    return pressure;
}

uint32_t c13dof_bme680_get_gas_resistance ( c13dof_t *ctx )
{
    uint32_t gas_resistance;

    bme680_read_field_data( ctx, &ctx->d_data );

    if ( ctx->d_data.status & C13DOF_BME680_GASM_VALID_MSK )
    {
        gas_resistance = ctx->d_data.gas_resistance;
    }

    if ( ctx->device_power_mode == C13DOF_BME680_FORCED_MODE )
    {
        bme680_set_sensor_mode( ctx );
    }

    return gas_resistance;
}

C13DOF_BMM150_RETVAL_T c13dof_bmm150_write_byte ( c13dof_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];

    if ( ( reg_address < 0x40 ) || ( reg_address > 0x52 ) )
    {
        return C13DOF_BMM150_ADDR_ERR;
    }

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 1 ] = write_data;

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmm150_slave_address );
    i2c_master_write( &ctx->i2c, w_buffer, 2 );   

    return C13DOF_BMM150_OK;
}

uint8_t c13dof_bmm150_read_byte ( c13dof_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 1 ];

    r_buffer[ 0 ] = reg_address;
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->bmm150_slave_address );
    i2c_master_write_then_read( &ctx->i2c, &reg_address, 1, r_buffer, 1 );

    return r_buffer[ 0 ];
}
 
C13DOF_BMM150_RETVAL_T c13dof_bmm150_read_bytes ( c13dof_t *ctx, uint8_t *data_out, uint8_t reg_address, uint8_t n_bytes )
{
    uint8_t w_buffer[ 20 ];

    if ( ( reg_address < 0x40 ) || ( reg_address > 0x52 ) )
    {
        return C13DOF_BMM150_ADDR_ERR;
    }
    if ( n_bytes > 19 )
    {
        return C13DOF_BMM150_NBYTES_ERR;
    }

    w_buffer[ 0 ] = reg_address;

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmm150_slave_address );
    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, data_out, n_bytes );
    
    return C13DOF_BMM150_OK;
}

C13DOF_BMM150_RETVAL_T c13dof_bmm150_check_ready ( c13dof_t *ctx )
{
    uint8_t tmp;

    c13dof_bmm150_read_bytes( ctx, &tmp, C13DOF_BMM150_RHALL_LSB_REG, 1 );

    tmp &= C13DOF_BMM150_DATA_READY;

    return tmp;
}
 
void c13dof_bmm150_read_geo_mag_data ( c13dof_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z, uint16_t *res_hall )
{
    uint8_t r_buffer[ 8 ];
    uint16_t temp;

    c13dof_bmm150_read_bytes( ctx, r_buffer, C13DOF_BMM150_DATAX_LSB_REG, 8 );

    temp = r_buffer[ 1 ];
    temp <<= 5;
    temp |= r_buffer[ 0 ] >> 3;
    
    *mag_x = temp;
    if ( *mag_x & 0x1000 )
    {
        *mag_x |= 0xE000;
    }

    temp = r_buffer[ 3 ];
    temp <<= 5;
    temp |= r_buffer[ 2 ] >> 3;
    
    *mag_y = temp;
    if ( *mag_y & 0x1000 )
    {
        *mag_y |= 0xE000;
    }

    temp = r_buffer[ 5 ];
    temp <<= 7;
    temp |= r_buffer[ 4 ] >> 1;
    
    *mag_z = temp;
    if ( *mag_z & 0x4000 )
    {
        *mag_z |= 0x8000;
    }

    temp = r_buffer[ 7 ];
    temp <<= 6;
    temp |= r_buffer[ 6 ] >> 2;
    *res_hall = temp;
}


void c13dof_bmm150_soft_reset ( c13dof_t *ctx )
{
    c13dof_bmm150_write_byte( ctx, C13DOF_BMM150_POWER_AND_RESET_CON_REG, C13DOF_BMM150_SOFT_RESET_EN | C13DOF_BMM150_SLEEP_MODE );
    c13dof_bmm150_write_byte( ctx, C13DOF_BMM150_DATARATE_AND_OPMODE_CON_REG, C13DOF_BMM150_NORMAL_OPMODE_DR_10HZ );
}

void c13dof_bmm150_power_on_reset ( c13dof_t *ctx )
{
    c13dof_bmm150_write_byte( ctx, C13DOF_BMM150_POWER_AND_RESET_CON_REG, C13DOF_BMM150_SUSPEND_MODE_SPI4_EN );
    c13dof_bmm150_write_byte( ctx, C13DOF_BMM150_POWER_AND_RESET_CON_REG, C13DOF_BMM150_SLEEP_MODE );
    reset_delay ( );
    c13dof_bmm150_write_byte( ctx, C13DOF_BMM150_DATARATE_AND_OPMODE_CON_REG, C13DOF_BMM150_NORMAL_OPMODE_DR_10HZ );
}

void c13dof_bmi088_gyro_write_byte ( c13dof_t *ctx,  uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ]= reg_address;
    w_buffer[ 1 ]= write_data;

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmi088Gyro_slave_address );
    i2c_master_write( &ctx->i2c, w_buffer, 2 );
}

void c13dof_bmi088_gyro_write_bytes ( c13dof_t *ctx, uint8_t reg_address, uint8_t *write_data, uint8_t n_bytes )
{
    uint16_t cnt;
    uint8_t w_buffer[ 255 ];

    w_buffer[ 0 ] = reg_address;

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        w_buffer[ cnt + 1 ] = write_data[ cnt ];
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmi088Gyro_slave_address );
    i2c_master_write( &ctx->i2c, w_buffer, n_bytes + 1 );
}

uint8_t c13dof_bmi088_gyro_read_byte ( c13dof_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 1 ];

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmi088Gyro_slave_address );
    i2c_master_write_then_read( &ctx->i2c, &reg_address, 1, r_buffer, 1 );

    return r_buffer[ 0 ];
}

C13DOF_BMI088_RETVAL_T c13dof_bmi088_gyro_read_bytes ( c13dof_t *ctx, uint8_t *data_out, uint8_t reg_address, uint8_t n_bytes )
{
    uint8_t w_buffer[ 20 ];

    w_buffer[ 0 ] = reg_address;

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmi088Gyro_slave_address );
    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, data_out, n_bytes );

    return C13DOF_BMI088_OK;
}

uint8_t c13dof_bmi088_get_gyro_id ( c13dof_t *ctx )
{
    uint8_t gyro_id;

    gyro_id = c13dof_bmi088_accel_read_byte( ctx, C13DOF_BMI088_GYRO_CHIP_ID_REG );

    return gyro_id;
}
 
C13DOF_BMI088_RETVAL_T c13dof_bmi088_set_gyro_range ( c13dof_t *ctx, uint8_t gyro_range )
{
    if ( gyro_range > 4 )
    {
        return C13DOF_BMI088_ERROR;
    }

    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_GYRO_RANGE_REG, gyro_range );
    
    return C13DOF_BMI088_OK;
}

C13DOF_BMI088_RETVAL_T c13dof_bmi088_set_gyro_bandwidth( c13dof_t *ctx, uint8_t gyro_bandwidth )
{
    if ( gyro_bandwidth > 7 )
    {
        return C13DOF_BMI088_ERROR;
    }

    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_GYRO_BANDWIDTH_REG, gyro_bandwidth );

    return C13DOF_BMI088_OK;
}

void c13dof_bmi088_soft_reset_giro ( c13dof_t *ctx )
{
    c13dof_bmi088_gyro_write_byte( ctx, C13DOF_BMI088_GYRO_SOFTRESET_REG, 0xB6 );
}

int16_t c13dof_bmi088_get_gyro_axis ( c13dof_t *ctx, uint8_t adr_reg_LSB, uint8_t adr_reg_MSB )
{
    uint16_t result;
    uint8_t temp[ 2 ];

    temp[ 0 ] = c13dof_bmi088_gyro_read_byte( ctx, adr_reg_MSB );
    temp[ 1 ] = c13dof_bmi088_gyro_read_byte( ctx,  adr_reg_LSB );

    result = temp[ 0 ];
    result <<= 8;
    result |= temp[ 1 ];

    return result;
}

void c13dof_bmi088_read_gyro ( c13dof_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z )
{
    *gyro_x = c13dof_bmi088_get_gyro_axis( ctx, C13DOF_BMI088_GYRO_X_LSB_REG, C13DOF_BMI088_GYRO_X_MSB_REG );
    *gyro_y = c13dof_bmi088_get_gyro_axis( ctx, C13DOF_BMI088_GYRO_Y_LSB_REG, C13DOF_BMI088_GYRO_Y_MSB_REG );
    *gyro_z = c13dof_bmi088_get_gyro_axis( ctx, C13DOF_BMI088_GYRO_Z_LSB_REG, C13DOF_BMI088_GYRO_Z_MSB_REG );
}

void c13dof_bmi088_accel_write_byte ( c13dof_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ]= reg_address;
    w_buffer[ 1 ]= write_data;

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmi088Accel_slave_address );
    i2c_master_write( &ctx->i2c, w_buffer, 2 );
}

void c13dof_bmi088_accel_write_bytes ( c13dof_t *ctx, uint8_t reg_address, uint8_t *write_data, uint8_t n_bytes )
{
    uint16_t cnt;
    uint8_t w_buffer[ 255 ];

    w_buffer[ 0 ] = reg_address;

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        w_buffer[ cnt + 1 ] = write_data[ cnt ];
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmi088Accel_slave_address );
    i2c_master_write( &ctx->i2c, w_buffer, n_bytes + 1 );
}

uint8_t c13dof_bmi088_accel_read_byte ( c13dof_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 1 ];

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmi088Accel_slave_address );
    i2c_master_write_then_read( &ctx->i2c, &reg_address, 1, r_buffer,  1 );

    return r_buffer[ 0 ];
}
 
C13DOF_BMI088_RETVAL_T c13dof_bmi088_accel_read_bytes ( c13dof_t *ctx, uint8_t *data_out, uint8_t reg_address, uint8_t n_bytes )
{
    uint8_t w_buffer[ 20 ];

    w_buffer[ 0 ] = reg_address;

    i2c_master_set_slave_address( &ctx->i2c, ctx->bmi088Accel_slave_address );
    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, data_out, n_bytes );

    return C13DOF_BMI088_OK;
}

uint8_t c13dof_bmi088_get_accel_id( c13dof_t *ctx )
{
    uint8_t accel_id;
    
    accel_id = c13dof_bmi088_accel_read_byte( ctx, C13DOF_BMI088_ACCEL_CHIP_ID_REG );

    return accel_id;
}

uint8_t c13dof_bmi088_get_accel_error ( c13dof_t *ctx )
{
    uint8_t accel_error;

    accel_error = c13dof_bmi088_accel_read_byte( ctx, C13DOF_BMI088_ACCEL_ERR_REG );

    return accel_error;
}

uint8_t c13dof_bmi088_check_accel_data_ready ( c13dof_t *ctx )
{
    uint8_t ready_check;

    ready_check = c13dof_bmi088_accel_read_byte( ctx, C13DOF_BMI088_ACCEL_STATUS_REG );
    
    ready_check >>= 7;

    return ready_check;
}

void c13dof_bmi088_set_accel_config ( c13dof_t *ctx, uint8_t accel_config )
{
    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_CONF_REG, accel_config );
}

C13DOF_BMI088_RETVAL_T c13dof_bmi088_set_accel_range ( c13dof_t *ctx, uint8_t accel_range )
{
    if ( accel_range > 3 )
    {
        return C13DOF_BMI088_ERROR;
    }
    
    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_RANGE_REG, accel_range );
    
    return C13DOF_BMI088_OK;
}

void c13dof_bmi088_soft_reset_accel ( c13dof_t *ctx )
{
    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_SOFTRESET_REG, 0xB6 );
    reset_delay();
}

void c13dof_bmi088_set_accel_mode ( c13dof_t *ctx, uint8_t active_mode )
{
    if ( active_mode )
    {
        c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_PWR_CONF_REG, 0x00 );
    }
    else
    {
        c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_PWR_CONF_REG, 0x03 );
    }
    
}

C13DOF_BMI088_RETVAL_T c13dof_bmi088_enable_accel ( c13dof_t *ctx )
{
    uint8_t tmp;

    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_PWR_CTRL_REG, 0x04 );

    tmp = c13dof_bmi088_accel_read_byte( ctx, C13DOF_BMI088_ACCEL_PWR_CTRL_REG );

    if ( tmp = 0x04 )
    {
        return C13DOF_BMI088_OK;
    }
    else
    {
       return C13DOF_BMI088_ERROR;
    }
}


C13DOF_BMI088_RETVAL_T c13dof_bmi088_disable_accel ( c13dof_t *ctx )
{
    uint8_t tmp;

    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_PWR_CTRL_REG, 0x00 );

    tmp = c13dof_bmi088_accel_read_byte( ctx, C13DOF_BMI088_ACCEL_PWR_CTRL_REG );

    if ( tmp = 0x00 )
    {
        return C13DOF_BMI088_OK;
    }
    else
    {
       return C13DOF_BMI088_ERROR;
    }
}

int16_t c13dof_bmi088_get_accel_axis ( c13dof_t *ctx, uint8_t adr_reg_LSB, uint8_t adr_reg_MSB )
{
    uint16_t result;
    uint8_t temp[ 2 ];

    temp[ 0 ] = c13dof_bmi088_accel_read_byte( ctx, adr_reg_MSB );
    temp[ 1 ] = c13dof_bmi088_accel_read_byte( ctx, adr_reg_LSB );

    result = temp[ 0 ];
    result <<= 8;
    result |= temp[ 1 ];

    return result;
}

void c13dof_bmi088_read_accel ( c13dof_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z )
{
    *accel_x = c13dof_bmi088_get_accel_axis( ctx, C13DOF_BMI088_ACCEL_X_LSB_REG, C13DOF_BMI088_ACCEL_X_MSB_REG );
    *accel_y = c13dof_bmi088_get_accel_axis( ctx, C13DOF_BMI088_ACCEL_Y_LSB_REG, C13DOF_BMI088_ACCEL_Y_MSB_REG );
    *accel_z = c13dof_bmi088_get_accel_axis( ctx, C13DOF_BMI088_ACCEL_Y_LSB_REG, C13DOF_BMI088_ACCEL_Z_MSB_REG );
}

void c13dof_bmi088_default_config ( c13dof_t *ctx )
{
    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_CONF_REG, 0xA8 );
    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_RANGE_REG, 0x03 );
    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_INT1_IO_CONF_REG, 0x09 );
    c13dof_bmi088_accel_write_byte( ctx, C13DOF_BMI088_ACCEL_INT1_INT2_MAP_DATA_REG, 0x02 );

    c13dof_bmi088_set_gyro_range( ctx, 0x01 );
    c13dof_bmi088_set_gyro_bandwidth( ctx, 0x05 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static int8_t user_read_data ( c13dof_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf [ 0 ] = reg_addr;
    ctx->bme680_slave_address = C13DOF_BME680_DEVICE_SLAVE_ADDR_0;

    i2c_master_set_slave_address( &ctx->i2c, ctx->bme680_slave_address );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, reg_data, len );

    return 0;
}

static int8_t user_write_data ( c13dof_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
{
    int16_t i;
    uint8_t tx_buf[ 100 ];
    
    ctx->bme680_slave_address = C13DOF_BME680_DEVICE_SLAVE_ADDR_0;

    tx_buf[ 0 ] = reg_addr;

    for ( i = 0; i < len; i++ )
    {
        tx_buf[ i+1 ] = reg_data[ i ];
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->bme680_slave_address );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );

    return 0;
}
static int8_t bme680_get_regs ( c13dof_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
{
    int8_t rslt = 0;
    int8_t com_rslt;

    com_rslt = user_read_data( ctx, reg_addr, reg_data, len );

    if ( com_rslt != 0)
    {
        rslt = C13DOF_BME680_E_COM_FAIL;
    }

    return rslt;
}

static int8_t bme680_set_regs ( c13dof_t *ctx, uint8_t *reg_addr, uint8_t *reg_data, uint8_t len )
{
    int8_t rslt = 0;
    int8_t com_rslt;

    uint8_t tmp_buff[ C13DOF_BME680_TMP_BUFFER_LENGTH ] = { 0 };
    uint16_t index;

    if ( ( len > 0 ) && ( len < C13DOF_BME680_TMP_BUFFER_LENGTH / 2 ) )
    {

        for ( index = 0; index < len; index++ )
        {
            tmp_buff[ ( 2 * index ) ] = reg_addr[ index ];

            tmp_buff[ ( 2 * index ) + 1 ] = reg_data[ index ];
        }

        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
            com_rslt = user_write_data( ctx, tmp_buff[ 0 ], &tmp_buff[ 1 ], ( 2 * len ) - 1 );
            if ( com_rslt != 0 )
            {
                rslt = C13DOF_BME680_E_COM_FAIL;
            }
        }
    }
    else
    {
        rslt = C13DOF_BME680_E_INVALID_LENGTH;
    }

    return rslt;
}

static int8_t bme680_set_sensor_settings ( c13dof_t *ctx, uint16_t desired_settings )
{
    int8_t rslt = 0;
    uint8_t reg_addr;
    uint8_t d_data = 0;
    uint8_t count = 0;
    uint8_t reg_array[ C13DOF_BME680_REG_BUFFER_LENGTH ] = { 0 };
    uint8_t data_array[ C13DOF_BME680_REG_BUFFER_LENGTH ] = { 0 };
    uint8_t intended_power_mode = ctx->device_power_mode;

    if ( desired_settings & C13DOF_BME680_GAS_MEAS_SEL )
    {
        rslt = bme680_set_gas_config( ctx );
    }

    ctx->device_power_mode = C13DOF_BME680_SLEEP_MODE;

    if ( rslt == C13DOF_BME680_DEVICE_OK )
    {
        rslt = bme680_set_sensor_mode( ctx );
    }

    if ( desired_settings & C13DOF_BME680_FILTER_SEL )
    {
        rslt = bme680_boundary_check( ctx, &ctx->tph_sett.filter, C13DOF_BME680_FILTER_SIZE_0, C13DOF_BME680_FILTER_SIZE_127 );
        reg_addr = C13DOF_BME680_CONF_ODR_FILT_ADDR;

        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
            rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1 );
        }
        if ( desired_settings & C13DOF_BME680_FILTER_SEL )
        {
            d_data = BME680_SET_BITS( d_data, C13DOF_BME680_FILTER, ctx-> tph_sett.filter );
        }
        reg_array[ count ] = reg_addr;
        data_array[ count ] = d_data;
        count++;
    }

    if ( desired_settings & C13DOF_BME680_HCNTRL_SEL )
    {
        rslt = bme680_boundary_check( ctx, &ctx->gas_sett.heatr_ctrl, C13DOF_BME680_ENABLE_HEATER,
                C13DOF_BME680_DISABLE_HEATER );
        reg_addr = C13DOF_BME680_CONF_HEAT_CTRL_ADDR;

        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
                rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1 );
        }
        d_data = BME680_SET_BITS_POS_0( d_data, C13DOF_BME680_HCTRL, ctx->gas_sett.heatr_ctrl );

        reg_array[ count ] = reg_addr;
        data_array[ count ] = d_data;
        count++;
    }

    if ( desired_settings & ( C13DOF_BME680_OST_SEL | C13DOF_BME680_OSP_SEL ) )
    {
        rslt = bme680_boundary_check( ctx, &ctx->tph_sett.os_temp, C13DOF_BME680_OS_NONE, C13DOF_BME680_OS_16X );
        reg_addr = C13DOF_BME680_CONF_T_P_MODE_ADDR;

        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
            rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1 );
        }
        if ( desired_settings & C13DOF_BME680_OST_SEL )
        {
            d_data = BME680_SET_BITS( d_data, C13DOF_BME680_OST, ctx->tph_sett.os_temp );
        }
        if ( desired_settings & C13DOF_BME680_OSP_SEL )
        {
            d_data = BME680_SET_BITS( d_data, C13DOF_BME680_OSP, ctx->tph_sett.os_pres );
        }
        reg_array[ count ] = reg_addr;
        data_array[ count ] = d_data;
        count++;
    }

    if ( desired_settings & C13DOF_BME680_OSH_SEL )
    {
        rslt = bme680_boundary_check( ctx,  &ctx->tph_sett.os_hum, C13DOF_BME680_OS_NONE, C13DOF_BME680_OS_16X );
        reg_addr = C13DOF_BME680_CONF_OS_H_ADDR;

        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
            rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1 );
        }
        d_data = BME680_SET_BITS_POS_0( d_data, C13DOF_BME680_OSH, ctx->tph_sett.os_hum );

        reg_array[ count ] = reg_addr;
        data_array[ count ] = d_data;
        count++;
    }

    if ( desired_settings & ( C13DOF_BME680_RUN_GAS_SEL | C13DOF_BME680_NBCONV_SEL ) )
    {
        rslt = bme680_boundary_check( ctx, &ctx->gas_sett.run_gas, C13DOF_BME680_RUN_GAS_DISABLE, C13DOF_BME680_RUN_GAS_ENABLE );
        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
            rslt = bme680_boundary_check( ctx, &ctx->gas_sett.nb_conv, C13DOF_BME680_NBCONV_MIN, C13DOF_BME680_NBCONV_MAX );
        }

        reg_addr = C13DOF_BME680_CONF_ODR_RUN_GAS_NBC_ADDR;

        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
            rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1 );
        }
        if ( desired_settings & C13DOF_BME680_RUN_GAS_SEL )
        {
            d_data = BME680_SET_BITS( d_data, C13DOF_BME680_RUN_GAS, ctx->gas_sett.run_gas );
        }
        if ( desired_settings & C13DOF_BME680_NBCONV_SEL )
        {
            d_data = BME680_SET_BITS_POS_0( d_data, C13DOF_BME680_NBCONV, ctx->gas_sett.nb_conv );
        }
        reg_array[ count ] = reg_addr;
        data_array[ count ] = d_data;
        count++;
    }

    if ( rslt == C13DOF_BME680_DEVICE_OK )
    {
        rslt = bme680_set_regs( ctx, reg_array, data_array, count );
    }

    ctx->device_power_mode = intended_power_mode;

    return rslt;
}

static int8_t bme680_set_sensor_mode ( c13dof_t *ctx )
{
    int8_t rslt = 0;
    uint8_t tmp_pow_mode;
    uint8_t pow_mode = 0;
    uint8_t reg_addr = C13DOF_BME680_CONF_T_P_MODE_ADDR;

    do
    {
        rslt = bme680_get_regs( ctx, C13DOF_BME680_CONF_T_P_MODE_ADDR, &tmp_pow_mode, 1 );
        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
            pow_mode = ( tmp_pow_mode & C13DOF_BME680_MODE_MSK );

            if ( pow_mode != C13DOF_BME680_SLEEP_MODE )
            {
                tmp_pow_mode = tmp_pow_mode & ( ~C13DOF_BME680_MODE_MSK );
                rslt = bme680_set_regs( ctx, &reg_addr, &tmp_pow_mode, 1 );
                Delay_10ms();
            }
        }
    } while ( pow_mode != C13DOF_BME680_SLEEP_MODE );

    if ( ctx->device_power_mode != C13DOF_BME680_SLEEP_MODE )
    {
        tmp_pow_mode = ( tmp_pow_mode & ~C13DOF_BME680_MODE_MSK ) | ( ctx->device_power_mode & C13DOF_BME680_MODE_MSK );
        if ( rslt == C13DOF_BME680_DEVICE_OK )
        {
             rslt = bme680_set_regs( ctx, &reg_addr, &tmp_pow_mode, 1 );
        }
    }

    return rslt;
}

static int8_t bme680_set_gas_config ( c13dof_t *ctx )
{
    int8_t rslt = 0;
    uint8_t reg_addr[ 2 ] = { 0 };
    uint8_t reg_data[ 2 ] = { 0 };

    if ( ctx->device_power_mode == C13DOF_BME680_FORCED_MODE )
    {
        reg_addr[ 0 ] = C13DOF_BME680_RES_HEAT0_ADDR;
        reg_data[ 0 ] = bme680_calc_heater_res( ctx, ctx->gas_sett.heatr_temp );
        reg_addr[ 1 ] = C13DOF_BME680_GAS_WAIT0_ADDR;
        reg_data[ 1 ] = bme680_calc_heater_dur( ctx, ctx->gas_sett.heatr_dur );
        ctx->gas_sett.nb_conv = 0;
    }
    else
    {
        rslt = C13DOF_BME680_W_DEFINE_PWR_MODE;
    }
    if ( rslt == C13DOF_BME680_DEVICE_OK )
    {
        rslt = bme680_set_regs( ctx, reg_addr, reg_data, 2 );
    }

    return rslt;
}

static int16_t bme680_calc_temperature ( c13dof_t *ctx, uint32_t temp_adc )
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t calc_temp;

    var1 = ( ( int32_t )temp_adc >> 3 ) - ( ( int32_t ) ctx->calib.par_t1 << 1 );
    var2 = ( var1 * ( int32_t ) ctx->calib.par_t2 ) >> 11;
    var3 = ( ( var1 >> 1 ) * ( var1 >> 1 ) ) >> 12;
    var3 = ( ( var3 ) * ( ( int32_t ) ctx->calib.par_t3 << 4 ) ) >> 14;
    ctx->calib.t_fine = ( int32_t ) ( var2 + var3 );
    calc_temp = ( int16_t ) ( ( ( ctx->calib.t_fine * 5 ) + 128 ) >> 8 );

    return calc_temp;
}

static uint32_t bme680_calc_humidity ( c13dof_t *ctx, uint16_t hum_adc )
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    int32_t var5;
    int32_t var6;
    int32_t temp_scaled;
    int32_t calc_hum;

    temp_scaled = ( ( ( int32_t ) ctx->calib.t_fine * 5 ) + 128 ) >> 8;
    var1 = ( int32_t ) ( hum_adc - ( ( int32_t ) ( ( int32_t ) ctx->calib.par_h1 * 16 ) ) ) - ( ( ( temp_scaled * ( int32_t ) ctx->calib.par_h3 ) / ( ( int32_t ) 100 ) ) >> 1 );
    var2 = ( ( int32_t ) ctx->calib.par_h2
            * ( ( ( temp_scaled * ( int32_t ) ctx->calib.par_h4 ) / ( ( int32_t ) 100 ) )
                    + ( ( ( temp_scaled * ( ( temp_scaled * ( int32_t ) ctx->calib.par_h5 ) / ( ( int32_t ) 100 ) ) ) >> 6 )
                            / ( ( int32_t ) 100 ) ) + ( int32_t ) ( 1 << 14 ) ) ) >> 10;
    var3 = var1 * var2;
    var4 = ( int32_t ) ctx->calib.par_h6 << 7;
    var4 = ( ( var4 ) + ( ( temp_scaled * ( int32_t ) ctx->calib.par_h7 ) / ( ( int32_t ) 100 ) ) ) >> 4;
    var5 = ( ( var3 >> 14 ) * ( var3 >> 14 ) ) >> 10;
    var6 = ( var4 * var5 ) >> 1;
    calc_hum = ( ( ( var3 + var6 ) >> 10 ) * ( ( int32_t ) 1000 ) ) >> 12;

    if ( calc_hum > 100000 )
    {
        calc_hum = 100000;
    }
    else if ( calc_hum < 0 )
    {
        calc_hum = 0;
    }
    return ( uint32_t ) calc_hum;
}

static uint8_t bme680_calc_heater_res ( c13dof_t *ctx, uint16_t temp )
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    int32_t var5;
    int32_t heatr_res_x100;
    uint8_t heatr_res;

    if ( temp > 400)
    {
        temp = 400;
    }

    var1 = ( ( ( int32_t ) device_amb_temp * ctx->calib.par_gh3 ) / 1000 ) * 256;
    var2 = ( ctx->calib.par_gh1 + 784 ) * ( ( ( ( ( ctx->calib.par_gh2 + 154009 ) * temp * 5 ) / 100 ) + 3276800 ) / 10 );
    var3 = var1 + ( var2 / 2 );
    var4 = ( var3 / ( ctx->calib.res_heat_range + 4 ) );
    var5 = ( 131 * ctx->calib.res_heat_val ) + 65536;

    heatr_res_x100 = ( int32_t ) ( ( ( var4 / var5) - 250 ) * 34 );
    heatr_res = ( uint8_t ) ( ( heatr_res_x100 + 50) / 100 );

    return heatr_res;
}

static float bme680_calc_pressure ( c13dof_t *ctx, uint32_t pres_adc )
{
    float var1 = 0;
    float var2 = 0;
    float var3 = 0;
    float calc_pres = 0;

    var1 = ( float )( ctx->calib.t_fine ) / 2.0f;
    var1 -= 64000.0f;

    var2 =( float )( ctx->calib.par_p6 ) / 131072.0f;
    var2 *= var1 * var1;
    var2 += ( var1 * ( ( float )ctx->calib.par_p5 ) * 2.0f );
    var2 = ( var2 / 4.0f ) + ( ( ( float )ctx->calib.par_p4 ) * 65536.0f );

    var1 = ( ( ( ( ( float )ctx->calib.par_p3 * var1 * var1 ) / 16384.0f) + ( ( float )ctx->calib.par_p2 * var1 ) ) / 524288.0f );
    var1 = ( ( 1.0f + ( var1 / 32768.0f ) ) * ( ( float )ctx->calib.par_p1 ) );
    calc_pres = ( 1048576.0f - ( ( float )pres_adc ) );

    if ( (int)var1 != 0)
    {
        calc_pres = ( ( ( calc_pres - ( var2 / 4096.0f ) ) * 6250.0f ) / var1 );
        var1 = ( ( ( float )ctx->calib.par_p9 ) * calc_pres * calc_pres) / 2147483648.0f;
        var2 = calc_pres * ( ( ( float )ctx->calib.par_p8 ) / 32768.0f );
        var3 = ( ( calc_pres / 256.0f ) * ( calc_pres / 256.0f ) * ( calc_pres / 256.0f ) * ( ctx->calib.par_p10 / 131072.0f ) );
        calc_pres = ( calc_pres + ( var1 + var2 + var3 + ( ( float )ctx->calib.par_p7 * 128.0f ) ) / 16.0f );
    }
    else
    {
        calc_pres = 0;
    }

    return calc_pres;
}

static float bme680_calc_gas_resistance ( c13dof_t *ctx, uint16_t gas_res_adc, uint8_t gas_range )
{
    float calc_gas_res;
    float var1 = 0;
    float var2 = 0;
    float var3 = 0;

    var1 = 5.0f * ctx->calib.range_sw_err;
    var1 += 1340.0f;

    var2 = lookup_k1_range[ gas_range ] / 100.0f;
    var2 += 1.0f;
    var2 *= var1;

    var3 = lookup_k2_range[ gas_range ] / 100.0f;
    var3 += 1.0f ;

    calc_gas_res = 1.0f / ( float )( var3 * ( 0.000000125f ) * ( float )( 1 << gas_range ) * ( ( ( ( ( float )gas_res_adc ) - 512.0f )/var2 ) + 1.0f ) );

    return calc_gas_res;
}

static uint8_t bme680_calc_heater_dur ( c13dof_t *ctx, uint16_t dur )
{
    uint8_t factor = 0;
    uint8_t durval;

    if ( dur >= 0xfc0 )
    {
        durval = 0xff;
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

static int8_t bme680_read_field_data ( c13dof_t *ctx, T_C13DOF_BME680_FIELD_DATA *d_data )
{
    int8_t rslt = 0;
    uint8_t buff[ C13DOF_BME680_FIELD_LENGTH ] = { 0 };
    uint8_t gas_range;
    uint32_t adc_temp;
    uint32_t adc_pres;
    uint16_t adc_hum;
    uint16_t adc_gas_res;
    uint8_t tries = 10;

    do
    {
        if ( rslt == C13DOF_BME680_DEVICE_OK)
        {
            rslt = bme680_get_regs( ctx, ( ( uint8_t ) ( C13DOF_BME680_FIELD0_ADDR ) ), buff, ( uint16_t ) C13DOF_BME680_FIELD_LENGTH );

            d_data->status = buff[ 0 ] & C13DOF_BME680_NEW_DATA_MSK;
            d_data->gas_index = buff[ 0 ] & C13DOF_BME680_GAS_INDEX_MSK;
            d_data->meas_index = buff[ 1 ];

            adc_pres = ( uint32_t ) ( ( ( uint32_t ) buff[ 2 ] * 4096 ) | ( ( uint32_t ) buff[ 3 ] * 16 )
                    | ( ( uint32_t ) buff[ 4 ] / 16 ) );
            adc_temp = ( uint32_t ) ( ( ( uint32_t ) buff[ 5 ] * 4096 ) | ( ( uint32_t ) buff[ 6 ] * 16 )
                    | ( ( uint32_t ) buff[ 7 ] / 16 ) );
            adc_hum = ( uint16_t ) ( ( ( uint32_t ) buff[ 8 ] * 256 ) | ( uint32_t ) buff[ 9 ] );
            adc_gas_res = ( uint16_t ) ( ( uint32_t ) buff[ 13 ] * 4 | ( ( ( uint32_t ) buff[ 14 ] ) / 64 ) );
            gas_range = buff[ 14 ] & C13DOF_BME680_GAS_RANGE_MSK;

            d_data->status |= buff[ 14 ] & C13DOF_BME680_GASM_VALID_MSK;
            d_data->status |= buff[ 14 ] & C13DOF_BME680_HEAT_STAB_MSK;

            if ( d_data->status & C13DOF_BME680_NEW_DATA_MSK )
            {
                d_data->temperature = bme680_calc_temperature( ctx, adc_temp );
                d_data->pressure = bme680_calc_pressure( ctx, adc_pres );
                d_data->humidity = bme680_calc_humidity( ctx, adc_hum );
                d_data->gas_resistance = bme680_calc_gas_resistance( ctx, adc_gas_res, gas_range );
                break;
            }

            Delay_10ms();
        }
        tries--;
    } while ( tries );

    if ( !tries )
    {
        rslt = C13DOF_BME680_W_NO_NEW_DATA;
    }
    return rslt;
}

static int8_t bme680_set_mem_page ( c13dof_t *ctx, uint8_t reg_addr )
{
    int8_t rslt = 0;
    int8_t com_rslt;
    uint8_t reg;
    uint8_t mem_page;

    if ( reg_addr > 0x7f )
    {
        mem_page = C13DOF_BME680_MEM_PAGE1;
    }
    else
    {
        mem_page = C13DOF_BME680_MEM_PAGE0;
    }
    if ( mem_page != ctx->device_mem_page )
    {
        ctx->device_mem_page = mem_page;

        com_rslt = user_read_data( ctx, C13DOF_BME680_MEM_PAGE_ADDR | C13DOF_BME680_SPI_RD_MSK, &reg, 1 );
        if ( com_rslt != 0)
        {
            rslt = C13DOF_BME680_E_COM_FAIL;
        }
        if ( rslt == C13DOF_BME680_DEVICE_OK)
        {
            reg = reg & ( ~C13DOF_BME680_MEM_PAGE_MSK );
            reg = reg | ( ctx->device_mem_page & C13DOF_BME680_MEM_PAGE_MSK );

            com_rslt = user_write_data( ctx, C13DOF_BME680_MEM_PAGE_ADDR & C13DOF_BME680_SPI_WR_MSK,&reg, 1 );
            if ( com_rslt != 0 )
            {
                rslt = C13DOF_BME680_E_COM_FAIL;
            }
        }
    }

    return rslt;
}

static int8_t bme680_boundary_check ( c13dof_t *ctx, uint8_t *value, uint8_t min, uint8_t max )
{
    int8_t rslt = C13DOF_BME680_DEVICE_OK;

    if ( value != 0 )
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
        rslt = C13DOF_BME680_E_NULL_PTR;
    }

    return rslt;
}

static void reset_delay ( void ) 
{
    Delay_100ms();
}

static void transfer_delay ( void )
{
    Delay_10ms();
}
// ------------------------------------------------------------------------- END

