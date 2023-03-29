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

#include "environment.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ENVIRONMENT_DUMMY  0
#define DEVICE_AMB_TEMP    25

// ------------------------------------------------------------------ CONSTANTS
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
// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void environment_i2c_write ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void environment_i2c_read ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void environment_spi_write ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void environment_spi_read ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static int8_t user_read_data ( environment_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );

static int8_t user_write_data ( environment_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );

static int8_t bme680_get_regs ( environment_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

static int8_t bme680_set_regs ( environment_t *ctx, uint8_t *reg_addr, uint8_t *reg_data, uint8_t len );

static int8_t bme680_set_sensor_settings ( environment_t *ctx, uint16_t desired_settings );

static int8_t bme680_set_sensor_mode ( environment_t *ctx );

static int8_t bme680_set_gas_config ( environment_t *ctx );

static int16_t bme680_calc_temperature ( environment_t *ctx, uint32_t temp_adc );

static uint32_t bme680_calc_humidity ( environment_t *ctx, uint16_t hum_adc );

static uint8_t bme680_calc_heater_res ( environment_t *ctx, uint16_t temp );

static float bme680_calc_pressure ( environment_t *ctx, uint32_t pres_adc );

static float bme680_calc_gas_resistance ( environment_t *ctx, uint16_t gas_res_adc, uint8_t gas_range );

static uint8_t bme680_calc_heater_dur ( environment_t *ctx, uint16_t dur );

static int8_t bme680_read_field_data ( environment_t *ctx, T_ENVIRONMENT_BME680_FIELD_DATA *d_data );

static int8_t bme680_set_mem_page ( environment_t *ctx, uint8_t reg_addr);

static int8_t bme680_boundary_check ( environment_t *ctx, uint8_t *value, uint8_t min, uint8_t max );

static void hw_reset_delay( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void environment_cfg_setup ( environment_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ENVIRONMENT_DEVICE_SLAVE_ADDR_1;
    cfg->sel = ENVIRONMENT_MASTER_I2C;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ENVIRONMENT_RETVAL environment_init ( environment_t *ctx, environment_cfg_t *cfg )
{
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ENVIRONMENT_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ENVIRONMENT_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = environment_i2c_read;
        ctx->write_f = environment_i2c_write;
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
        
        spi_cfg.default_write_data = ENVIRONMENT_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  ENVIRONMENT_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ENVIRONMENT_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f = environment_spi_read;
        ctx->write_f = environment_spi_write;
    }

    return ENVIRONMENT_OK;
}

void environment_default_cfg ( environment_t *ctx )
{

    environment_soft_reset( ctx );
    environment_get_calibration_data( ctx );
    
    
    ctx->tph_sett.os_hum = ENVIRONMENT_OS_2X;
    ctx->tph_sett.os_pres = ENVIRONMENT_OS_4X;
    ctx->tph_sett.os_temp = ENVIRONMENT_OS_8X;
    ctx->tph_sett.filter = ENVIRONMENT_FILTER_SIZE_3;

    ctx->gas_sett.run_gas = ENVIRONMENT_ENABLE_GAS_MEAS;

    ctx->gas_sett.heatr_temp = 320;
    ctx->gas_sett.heatr_dur = 150;

    ctx->device_power_mode = ENVIRONMENT_FORCED_MODE;
    environment_default_config( ctx );
    hw_reset_delay( );
}

void environment_generic_write ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void environment_generic_read ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void environment_write_byte ( environment_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    ctx->write_f( ctx, reg_address, &write_data, 2 ); 
}

uint8_t environment_read_byte ( environment_t *ctx, uint8_t reg_address )
{
    uint8_t read_buffer[ 1 ];

    ctx->read_f( ctx, reg_address, read_buffer, 1 );

    return read_buffer[ 0 ];
}

uint8_t environment_check_id ( environment_t *ctx )
{
    uint8_t temp_id;

    if ( ctx->master_sel == ENVIRONMENT_MASTER_SPI  )
    {
        environment_write_byte( ctx, 0x76, 0x00 ); 
    }

    temp_id =  environment_read_byte( ctx, 0xD0 );

    if ( temp_id != 0x61 )
    {
        return 0;
    }

    return 1;
}

uint8_t environment_get_device_id ( environment_t *ctx )
{
    uint8_t device_id;

    if ( ctx->master_sel == ENVIRONMENT_MASTER_SPI )
    {
        environment_write_byte( ctx, 0x73, 0x00 );
    }

    device_id =  environment_read_byte( ctx, 0xD0 );

    return device_id;
}

void environment_soft_reset ( environment_t *ctx )
{
    uint8_t reg_addr;
    uint8_t soft_rst_cmd;
    uint8_t reg;

    reg_addr = ENVIRONMENT_SOFT_RESET_ADDR;
    soft_rst_cmd = ENVIRONMENT_SOFT_RESET_CMD;

    if ( ctx->master_sel == ENVIRONMENT_MASTER_SPI )
    {
        user_read_data( ctx, ENVIRONMENT_MEM_PAGE_ADDR | ENVIRONMENT_SPI_RD_MSK, &reg, 1 );
        ctx->device_mem_page = reg & ENVIRONMENT_MEM_PAGE_MSK;
    }

    bme680_set_regs( ctx, &reg_addr, &soft_rst_cmd, 1 );
    Delay_10ms();

    if ( ctx->master_sel == ENVIRONMENT_MASTER_SPI )
    {
        user_read_data( ctx, ENVIRONMENT_MEM_PAGE_ADDR | ENVIRONMENT_SPI_RD_MSK, &reg, 1 );
        ctx->device_mem_page = reg & ENVIRONMENT_MEM_PAGE_MSK;
    }
}

void environment_get_calibration_data ( environment_t *ctx )
{
    uint8_t coeff_array[ ENVIRONMENT_COEFF_SIZE ] = { 0 };
    uint8_t temp_var = 0;

    bme680_get_regs( ctx, ENVIRONMENT_COEFF_ADDR1, coeff_array,  ENVIRONMENT_COEFF_ADDR1_LEN );
    bme680_get_regs( ctx, ENVIRONMENT_COEFF_ADDR2, &coeff_array[ ENVIRONMENT_COEFF_ADDR1_LEN ], ENVIRONMENT_COEFF_ADDR2_LEN );

    ctx->calib.par_t1 = (uint16_t) (BME680_CONCAT_BYTES(coeff_array[ ENVIRONMENT_T1_MSB_REG ], coeff_array[ ENVIRONMENT_T1_LSB_REG ]));
    ctx->calib.par_t2 = (int16_t) (BME680_CONCAT_BYTES(coeff_array[ ENVIRONMENT_T2_MSB_REG ], coeff_array[ ENVIRONMENT_T2_LSB_REG ]));
    ctx->calib.par_t3 = (int8_t) (coeff_array[ ENVIRONMENT_T3_REG ]);

    ctx->calib.par_p1 = (uint16_t) (BME680_CONCAT_BYTES(coeff_array[ ENVIRONMENT_P1_MSB_REG ],coeff_array[ ENVIRONMENT_P1_LSB_REG ]));
    ctx->calib.par_p2 = (int16_t) (BME680_CONCAT_BYTES(coeff_array[ ENVIRONMENT_P2_MSB_REG ],coeff_array[ ENVIRONMENT_P2_LSB_REG ]));
    ctx->calib.par_p3 = (int8_t) coeff_array[ ENVIRONMENT_P3_REG ];
    ctx->calib.par_p4 = (int16_t) (BME680_CONCAT_BYTES(coeff_array[ ENVIRONMENT_P4_MSB_REG ],coeff_array[ ENVIRONMENT_P4_LSB_REG ]));
    ctx->calib.par_p5 = (int16_t) (BME680_CONCAT_BYTES(coeff_array[ ENVIRONMENT_P5_MSB_REG ],coeff_array[ ENVIRONMENT_P5_LSB_REG ]));
    ctx->calib.par_p6 = (int8_t) (coeff_array[ ENVIRONMENT_P6_REG ]);
    ctx->calib.par_p7 = (int8_t) (coeff_array[ ENVIRONMENT_P7_REG ]);
    ctx->calib.par_p8 = (int16_t) (BME680_CONCAT_BYTES(coeff_array[ ENVIRONMENT_P8_MSB_REG ],coeff_array[ ENVIRONMENT_P8_LSB_REG ]));
    ctx->calib.par_p9 = (int16_t) (BME680_CONCAT_BYTES(coeff_array[ ENVIRONMENT_P9_MSB_REG ],coeff_array[ ENVIRONMENT_P9_LSB_REG ]));
    ctx->calib.par_p10 = (uint8_t) (coeff_array[ ENVIRONMENT_P10_REG ]);

    ctx->calib.par_h1 = (uint16_t) (((uint16_t) coeff_array[ENVIRONMENT_H1_MSB_REG] << ENVIRONMENT_HUM_REG_SHIFT_VAL)
       | (coeff_array[ENVIRONMENT_H1_LSB_REG] & ENVIRONMENT_BIT_H1_DATA_MSK));
    ctx->calib.par_h2 = (uint16_t) (((uint16_t) coeff_array[ENVIRONMENT_H2_MSB_REG] << ENVIRONMENT_HUM_REG_SHIFT_VAL)
       | ((coeff_array[ENVIRONMENT_H2_LSB_REG]) >> ENVIRONMENT_HUM_REG_SHIFT_VAL));
    ctx->calib.par_h3 = (int8_t) coeff_array[ENVIRONMENT_H3_REG];
    ctx->calib.par_h4 = (int8_t) coeff_array[ENVIRONMENT_H4_REG];
    ctx->calib.par_h5 = (int8_t) coeff_array[ENVIRONMENT_H5_REG];
    ctx->calib.par_h6 = (uint8_t) coeff_array[ENVIRONMENT_H6_REG];
    ctx->calib.par_h7 = (int8_t) coeff_array[ENVIRONMENT_H7_REG];

    ctx->calib.par_gh1 = (int8_t) coeff_array[ENVIRONMENT_GH1_REG];
    ctx->calib.par_gh2 = (int16_t) (BME680_CONCAT_BYTES(coeff_array[ENVIRONMENT_GH2_MSB_REG],coeff_array[ENVIRONMENT_GH2_LSB_REG]));
    ctx->calib.par_gh3 = (int8_t) coeff_array[ENVIRONMENT_GH3_REG];

    bme680_get_regs( ctx, ENVIRONMENT_ADDR_RES_HEAT_RANGE_ADDR, &temp_var, 1);
    ctx->calib.res_heat_range = ((temp_var & ENVIRONMENT_RHRANGE_MSK) / 16);

    bme680_get_regs( ctx, ENVIRONMENT_ADDR_RES_HEAT_VAL_ADDR, &temp_var, 1);
    ctx->calib.res_heat_val = (int8_t) temp_var;

    bme680_get_regs( ctx, ENVIRONMENT_ADDR_RANGE_SW_ERR_ADDR, &temp_var, 1);
    ctx->calib.range_sw_err = ((int8_t) temp_var & (int8_t) ENVIRONMENT_RSERROR_MSK) / 16;
}

void environment_default_config ( environment_t *ctx )
{

    bme680_set_sensor_settings( ctx, ENVIRONMENT_OST_SEL | 
                               ENVIRONMENT_OSP_SEL |
                               ENVIRONMENT_OSH_SEL | 
                               ENVIRONMENT_FILTER_SEL | 
                               ENVIRONMENT_GAS_SENSOR_SEL );
    bme680_set_sensor_mode( ctx );
}

float environment_get_ambient_data ( environment_t *ctx, uint8_t data_in )
{
    bme680_read_field_data( ctx, &ctx->d_data );

    if ( ctx->device_power_mode == ENVIRONMENT_FORCED_MODE )
    {
        bme680_set_sensor_mode( ctx );
    }

    if ( data_in == ENVIRONMENT_DATA_TEMPERATURE )
    {
        return (float)ctx->d_data.temperature / 100.0;
    }
    else if ( data_in == ENVIRONMENT_DATA_PRESSURE )
    {
        return (float)ctx->d_data.pressure / 100.0;
    }
    else if ( data_in == ENVIRONMENT_DATA_HUMIDITY )
    {
        return (float)ctx->d_data.humidity / 1000.0;
    }
    else
    {
        return 1;
    }
}

float environment_get_temperature ( environment_t *ctx )
{
    float temperature;

    temperature = environment_get_ambient_data( ctx, ENVIRONMENT_DATA_TEMPERATURE );

    return temperature;
}

float environment_get_humidity ( environment_t *ctx )
{
    float humidity;

    humidity = environment_get_ambient_data( ctx, ENVIRONMENT_DATA_HUMIDITY );

    return humidity;
}

float environment_get_pressure ( environment_t *ctx )
{
    float pressure;

    pressure = environment_get_ambient_data( ctx, ENVIRONMENT_DATA_PRESSURE );

    return pressure;
}

uint32_t environment_get_gas_resistance ( environment_t *ctx )
{
    uint32_t gas_resistance;

    bme680_read_field_data( ctx, &ctx->d_data );

    if( ctx->d_data.status & ENVIRONMENT_GASM_VALID_MSK )
    {
        gas_resistance = ctx->d_data.gas_resistance;
    }

    if ( ctx->device_power_mode == ENVIRONMENT_FORCED_MODE )
    {
        bme680_set_sensor_mode( ctx );
    }

    return gas_resistance;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void environment_i2c_write ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void environment_i2c_read ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void environment_spi_write ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );    
}

static void environment_spi_read ( environment_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );  

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt ];
    }
}

static int8_t user_read_data ( environment_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
{
    environment_generic_read ( ctx, reg_addr, reg_data, len );

    return 0;
}

static int8_t user_write_data ( environment_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
{
    environment_generic_write ( ctx, reg_addr, reg_data, len );

    return 0;
}

static int8_t bme680_get_regs ( environment_t *ctx, uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
{
    int8_t rslt = 0;
    int8_t com_rslt;

    if ( ctx->master_sel == ENVIRONMENT_MASTER_SPI )
    {
        rslt = bme680_set_mem_page( ctx, reg_addr );
        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            reg_addr = reg_addr | ENVIRONMENT_SPI_RD_MSK;
        }
    }
    com_rslt = user_read_data( ctx, reg_addr, reg_data, len );
    if ( com_rslt != 0 )
    {
        rslt = ENVIRONMENT_E_COM_FAIL;
    }

    return rslt;
}

static int8_t bme680_set_regs ( environment_t *ctx, uint8_t *reg_addr, uint8_t *reg_data, uint8_t len )
{
    int8_t rslt = 0;
    int8_t com_rslt;

    uint8_t tmp_buff[ENVIRONMENT_TMP_BUFFER_LENGTH] = { 0 };
    uint16_t index;

    if ( ( len > 0 ) && ( len < ENVIRONMENT_TMP_BUFFER_LENGTH / 2 ) )
    {

        for ( index = 0; index < len; index++ )
        {
            if ( ctx->master_sel == ENVIRONMENT_MASTER_SPI )
            {
                rslt = bme680_set_mem_page( ctx, reg_addr[ index ] );
                tmp_buff[ ( 2 * index ) ] = reg_addr[ index ] & ENVIRONMENT_SPI_WR_MSK;
            }
            else
            {
                tmp_buff[ ( 2 * index ) ] = reg_addr[ index ];
            }
            tmp_buff[ ( 2 * index ) + 1 ] = reg_data[ index ];
        }

        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            com_rslt = user_write_data( ctx, tmp_buff[ 0 ], &tmp_buff[ 1 ], ( 2 * len ) - 1 );
            if ( com_rslt != 0 )
            {
                rslt = ENVIRONMENT_E_COM_FAIL;
            }
        }
    }
    else
    {
        rslt = ENVIRONMENT_E_INVALID_LENGTH;
    }

    return rslt;
}

static int8_t bme680_set_sensor_settings ( environment_t *ctx, uint16_t desired_settings )
{
    int8_t rslt = 0;
    uint8_t reg_addr;
    uint8_t d_data = 0;
    uint8_t count = 0;
    uint8_t reg_array[ENVIRONMENT_REG_BUFFER_LENGTH] = { 0 };
    uint8_t data_array[ENVIRONMENT_REG_BUFFER_LENGTH] = { 0 };
    uint8_t intended_power_mode = ctx->device_power_mode;

    if ( desired_settings & ENVIRONMENT_GAS_MEAS_SEL )
    {
        rslt = bme680_set_gas_config( ctx );
    }
    
    ctx->device_power_mode = ENVIRONMENT_SLEEP_MODE;
    
    if ( rslt == ENVIRONMENT_DEVICE_OK )
    {
        rslt = bme680_set_sensor_mode( ctx );
    }

    if ( desired_settings & ENVIRONMENT_FILTER_SEL )
    {
        rslt = bme680_boundary_check( ctx, &ctx->tph_sett.filter, ENVIRONMENT_FILTER_SIZE_0, ENVIRONMENT_FILTER_SIZE_127 );
        reg_addr = ENVIRONMENT_CONF_ODR_FILT_ADDR;

        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1);
        }
        if ( desired_settings & ENVIRONMENT_FILTER_SEL )
        {
            d_data = BME680_SET_BITS( d_data, ENVIRONMENT_FILTER, ctx->tph_sett.filter );
        }
        reg_array[count] = reg_addr;
        data_array[count] = d_data;
        count++;
    }

    if ( desired_settings & ENVIRONMENT_HCNTRL_SEL )
    {
        rslt = bme680_boundary_check( ctx, &ctx->gas_sett.heatr_ctrl, ENVIRONMENT_ENABLE_HEATER,
                ENVIRONMENT_DISABLE_HEATER );
        reg_addr = ENVIRONMENT_CONF_HEAT_CTRL_ADDR;

        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
                rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1 );
        }
        d_data = BME680_SET_BITS_POS_0( d_data, ENVIRONMENT_HCTRL, ctx->gas_sett.heatr_ctrl );

        reg_array[count] = reg_addr;
        data_array[count] = d_data;
        count++;
    }

    if ( desired_settings & ( ENVIRONMENT_OST_SEL | ENVIRONMENT_OSP_SEL ) )
    {
        rslt = bme680_boundary_check( ctx,  &ctx->tph_sett.os_temp, ENVIRONMENT_OS_NONE, ENVIRONMENT_OS_16X );
        reg_addr = ENVIRONMENT_CONF_T_P_MODE_ADDR;

        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1);
        }
        if ( desired_settings & ENVIRONMENT_OST_SEL )
        {
            d_data = BME680_SET_BITS(d_data, ENVIRONMENT_OST, ctx->tph_sett.os_temp);
        }
        if ( desired_settings & ENVIRONMENT_OSP_SEL )
        {
            d_data = BME680_SET_BITS(d_data, ENVIRONMENT_OSP, ctx->tph_sett.os_pres);
        }
        reg_array[ count ] = reg_addr;
        data_array[ count ] = d_data;
        count++;
    }

    if ( desired_settings & ENVIRONMENT_OSH_SEL )
    {
        rslt = bme680_boundary_check( ctx, &ctx->tph_sett.os_hum, ENVIRONMENT_OS_NONE, ENVIRONMENT_OS_16X );
        reg_addr = ENVIRONMENT_CONF_OS_H_ADDR;

        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1 );
        }
        d_data = BME680_SET_BITS_POS_0( d_data, ENVIRONMENT_OSH, ctx->tph_sett.os_hum );

        reg_array[ count ] = reg_addr;
        data_array[ count ] = d_data;
        count++;
    }

    if ( desired_settings & ( ENVIRONMENT_RUN_GAS_SEL | ENVIRONMENT_NBCONV_SEL ) )
    {
        rslt = bme680_boundary_check( ctx, &ctx->gas_sett.run_gas, ENVIRONMENT_RUN_GAS_DISABLE, ENVIRONMENT_RUN_GAS_ENABLE );
        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            rslt = bme680_boundary_check( ctx, &ctx->gas_sett.nb_conv, ENVIRONMENT_NBCONV_MIN, ENVIRONMENT_NBCONV_MAX );
        }

        reg_addr = ENVIRONMENT_CONF_ODR_RUN_GAS_NBC_ADDR;

        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            rslt = bme680_get_regs( ctx, reg_addr, &d_data, 1 );
        }
        if ( desired_settings & ENVIRONMENT_RUN_GAS_SEL )
        {
            d_data = BME680_SET_BITS( d_data, ENVIRONMENT_RUN_GAS, ctx->gas_sett.run_gas );
        }
        if ( desired_settings & ENVIRONMENT_NBCONV_SEL )
        {
            d_data = BME680_SET_BITS_POS_0( d_data, ENVIRONMENT_NBCONV, ctx->gas_sett.nb_conv );
        }
        reg_array[ count ] = reg_addr;
        data_array[ count ] = d_data;
        count++;
    }

    if ( rslt == ENVIRONMENT_DEVICE_OK )
    {
        rslt = bme680_set_regs( ctx, reg_array, data_array, count );
    }

    ctx->device_power_mode = intended_power_mode;

    return rslt;
}

static int8_t bme680_set_sensor_mode ( environment_t *ctx )
{
    int8_t rslt = 0;
    uint8_t tmp_pow_mode;
    uint8_t pow_mode = 0;
    uint8_t reg_addr = ENVIRONMENT_CONF_T_P_MODE_ADDR;

    do
    {
        rslt = bme680_get_regs( ctx, ENVIRONMENT_CONF_T_P_MODE_ADDR, &tmp_pow_mode, 1 );
        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            pow_mode = ( tmp_pow_mode & ENVIRONMENT_MODE_MSK );

            if ( pow_mode != ENVIRONMENT_SLEEP_MODE )
            {
                tmp_pow_mode = tmp_pow_mode & ( ~ENVIRONMENT_MODE_MSK );
                rslt = bme680_set_regs( ctx, &reg_addr, &tmp_pow_mode, 1 );
                Delay_10ms();
            }
        }
    } while ( pow_mode != ENVIRONMENT_SLEEP_MODE );

    if ( ctx->device_power_mode != ENVIRONMENT_SLEEP_MODE )
    {
        tmp_pow_mode = ( tmp_pow_mode & ~ENVIRONMENT_MODE_MSK ) | ( ctx->device_power_mode & ENVIRONMENT_MODE_MSK );
        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
             rslt = bme680_set_regs( ctx, &reg_addr, &tmp_pow_mode, 1 );
        }
    }

    return rslt;
}

static int8_t bme680_set_gas_config ( environment_t *ctx )
{
    int8_t rslt = 0;
    uint8_t reg_addr[ 2 ] = { 0 };
    uint8_t reg_data[ 2 ] = { 0 };

    if ( ctx->device_power_mode == ENVIRONMENT_FORCED_MODE )
    {
        reg_addr[ 0 ] = ENVIRONMENT_RES_HEAT0_ADDR;
        reg_data[ 0 ] = bme680_calc_heater_res( ctx, ctx->gas_sett.heatr_temp );
        reg_addr[ 1 ] = ENVIRONMENT_GAS_WAIT0_ADDR;
        reg_data[ 1 ] = bme680_calc_heater_dur( ctx, ctx->gas_sett.heatr_dur );
        ctx->gas_sett.nb_conv = 0;
    }
    else
    {
        rslt = ENVIRONMENT_W_DEFINE_PWR_MODE;
    }
    if ( rslt == ENVIRONMENT_DEVICE_OK )
    {
        rslt = bme680_set_regs( ctx, reg_addr, reg_data, 2 );
    }

    return rslt;
}

static int16_t bme680_calc_temperature ( environment_t *ctx, uint32_t temp_adc )
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t calc_temp;

    var1 = ((int32_t) temp_adc >> 3) - ((int32_t) ctx->calib.par_t1 << 1);
    var2 = (var1 * (int32_t) ctx->calib.par_t2) >> 11;
    var3 = ((var1 >> 1) * (var1 >> 1)) >> 12;
    var3 = ((var3) * ((int32_t) ctx->calib.par_t3 << 4)) >> 14;
    ctx->calib.t_fine = (int32_t) (var2 + var3);
    calc_temp = (int16_t) (((ctx->calib.t_fine * 5) + 128) >> 8);

    return calc_temp;
}

static uint32_t bme680_calc_humidity ( environment_t *ctx, uint16_t hum_adc )
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    int32_t var5;
    int32_t var6;
    int32_t temp_scaled;
    int32_t calc_hum;

    temp_scaled = (((int32_t) ctx->calib.t_fine * 5) + 128) >> 8;
    var1 = (int32_t) (hum_adc - ((int32_t) ((int32_t) ctx->calib.par_h1 * 16))) - (((temp_scaled * (int32_t) ctx->calib.par_h3) / ((int32_t) 100)) >> 1);
    var2 = ((int32_t) ctx->calib.par_h2
            * (((temp_scaled * (int32_t) ctx->calib.par_h4) / ((int32_t) 100))
                    + (((temp_scaled * ((temp_scaled * (int32_t) ctx->calib.par_h5) / ((int32_t) 100))) >> 6)
                            / ((int32_t) 100)) + (int32_t) (1 << 14))) >> 10;
    var3 = var1 * var2;
    var4 = (int32_t) ctx->calib.par_h6 << 7;
    var4 = ((var4) + ((temp_scaled * (int32_t) ctx->calib.par_h7) / ((int32_t) 100))) >> 4;
    var5 = ((var3 >> 14) * (var3 >> 14)) >> 10;
    var6 = (var4 * var5) >> 1;
    calc_hum = (((var3 + var6) >> 10) * ((int32_t) 1000)) >> 12;

    if (calc_hum > 100000)
    {
        calc_hum = 100000;
    }
    else if (calc_hum < 0)
    {
        calc_hum = 0;
    }
    return (uint32_t) calc_hum;
}

static uint8_t bme680_calc_heater_res ( environment_t *ctx, uint16_t temp )
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    int32_t var5;
    int32_t heatr_res_x100;
    uint8_t heatr_res;

    if (temp > 400)
    {
        temp = 400;
    }

    var1 = (((int32_t) DEVICE_AMB_TEMP * ctx->calib.par_gh3) / 1000) * 256;
    var2 = (ctx->calib.par_gh1 + 784) * (((((ctx->calib.par_gh2 + 154009) * temp * 5) / 100) + 3276800) / 10);
    var3 = var1 + (var2 / 2);
    var4 = (var3 / (ctx->calib.res_heat_range + 4));
    var5 = (131 * ctx->calib.res_heat_val) + 65536;

    heatr_res_x100 = (int32_t) (((var4 / var5) - 250) * 34);
    heatr_res = (uint8_t) ((heatr_res_x100 + 50) / 100);

    return heatr_res;
}

static float bme680_calc_pressure ( environment_t *ctx, uint32_t pres_adc )
{
    float var1 = 0;
    float var2 = 0;
    float var3 = 0;
    float calc_pres = 0;

    var1 = (float)(ctx->calib.t_fine) / 2.0f;
    var1 -= 64000.0f;

    var2 =(float)(ctx->calib.par_p6) / 131072.0f;
    var2 *= var1 * var1;
    var2 += (var1 * ((float)ctx->calib.par_p5) * 2.0f);
    var2 = (var2 / 4.0f) + (((float)ctx->calib.par_p4) * 65536.0f);

    var1 = (((((float)ctx->calib.par_p3 * var1 * var1) / 16384.0f) + ((float)ctx->calib.par_p2 * var1)) / 524288.0f);
    var1 = ((1.0f + (var1 / 32768.0f)) * ((float)ctx->calib.par_p1));
    calc_pres = (1048576.0f - ((float)pres_adc));

    if ((int)var1 != 0)
    {
        calc_pres = (((calc_pres - (var2 / 4096.0f)) * 6250.0f) / var1);
        var1 = (((float)ctx->calib.par_p9) * calc_pres * calc_pres) / 2147483648.0f;
        var2 = calc_pres * (((float)ctx->calib.par_p8) / 32768.0f);
        var3 = ((calc_pres / 256.0f) * (calc_pres / 256.0f) * (calc_pres / 256.0f) * (ctx->calib.par_p10 / 131072.0f));
        calc_pres = (calc_pres + (var1 + var2 + var3 + ((float)ctx->calib.par_p7 * 128.0f)) / 16.0f);
    }
    else
    {
        calc_pres = 0;
    }

    return calc_pres;
}

static float bme680_calc_gas_resistance ( environment_t *ctx, uint16_t gas_res_adc, uint8_t gas_range )
{
    float calc_gas_res;
    float var1 = 0;
    float var2 = 0;
    float var3 = 0;

    var1 = 5.0f * ctx->calib.range_sw_err;
    var1 += 1340.0f;

    var2 = lookup_k1_range[gas_range] / 100.0f;
    var2 += 1.0f;
    var2 *= var1;

    var3 = lookup_k2_range[gas_range] / 100.0f;
    var3 += 1.0f ;

    calc_gas_res = 1.0f / (float)(var3 * (0.000000125f) * (float)(1 << gas_range) * (((((float)gas_res_adc) - 512.0f)/var2) + 1.0f));

    return calc_gas_res;
}

static uint8_t bme680_calc_heater_dur ( environment_t *ctx, uint16_t dur )
{
    uint8_t factor = 0;
    uint8_t durval;

    if (dur >= 0xfc0)
    {
        durval = 0xff;
    }
    else
    {
        while (dur > 0x3F)
        {
            dur = dur / 4;
            factor += 1;
        }
        durval = (uint8_t) (dur + (factor * 64));
    }

    return durval;
}

static int8_t bme680_read_field_data ( environment_t *ctx, T_ENVIRONMENT_BME680_FIELD_DATA *d_data )
{
    int8_t rslt = 0;
    uint8_t buff[ENVIRONMENT_FIELD_LENGTH] = { 0 };
    uint8_t gas_range;
    uint32_t adc_temp;
    uint32_t adc_pres;
    uint16_t adc_hum;
    uint16_t adc_gas_res;
    uint8_t tries = 10;

    do
    {
        if (rslt == ENVIRONMENT_DEVICE_OK)
        {
            rslt = bme680_get_regs( ctx, ((uint8_t) (ENVIRONMENT_FIELD0_ADDR)), buff, (uint16_t) ENVIRONMENT_FIELD_LENGTH);

            d_data->status = buff[0] & ENVIRONMENT_NEW_DATA_MSK;
            d_data->gas_index = buff[0] & ENVIRONMENT_GAS_INDEX_MSK;
            d_data->meas_index = buff[1];

            adc_pres = (uint32_t) (((uint32_t) buff[2] * 4096) | ((uint32_t) buff[3] * 16)
                    | ((uint32_t) buff[4] / 16));
            adc_temp = (uint32_t) (((uint32_t) buff[5] * 4096) | ((uint32_t) buff[6] * 16)
                    | ((uint32_t) buff[7] / 16));
            adc_hum = (uint16_t) (((uint32_t) buff[8] * 256) | (uint32_t) buff[9]);
            adc_gas_res = (uint16_t) ((uint32_t) buff[13] * 4 | (((uint32_t) buff[14]) / 64));
            gas_range = buff[14] & ENVIRONMENT_GAS_RANGE_MSK;

            d_data->status |= buff[14] & ENVIRONMENT_GASM_VALID_MSK;
            d_data->status |= buff[14] & ENVIRONMENT_HEAT_STAB_MSK;

            if (d_data->status & ENVIRONMENT_NEW_DATA_MSK)
            {
                d_data->temperature = bme680_calc_temperature( ctx, adc_temp);
                d_data->pressure = bme680_calc_pressure( ctx, adc_pres);
                d_data->humidity = bme680_calc_humidity( ctx, adc_hum);
                d_data->gas_resistance = bme680_calc_gas_resistance( ctx, adc_gas_res, gas_range);
                break;
            }

            Delay_10ms();
        }
        tries--;
    } while ( tries );

    if ( !tries )
    {
        rslt = ENVIRONMENT_W_NO_NEW_DATA;
    }
    return rslt;
}

static int8_t bme680_set_mem_page ( environment_t *ctx, uint8_t reg_addr)
{
    int8_t rslt = 0;
    int8_t com_rslt;
    uint8_t reg;
    uint8_t mem_page;

    if ( reg_addr > 0x7f )
    {
        mem_page = ENVIRONMENT_MEM_PAGE1;
    }
    else
    {
        mem_page = ENVIRONMENT_MEM_PAGE0;
    }
    if ( mem_page != ctx->device_mem_page )
    {
        ctx->device_mem_page = mem_page;

        com_rslt = user_read_data( ctx, ENVIRONMENT_MEM_PAGE_ADDR | ENVIRONMENT_SPI_RD_MSK, &reg, 1);
        if ( com_rslt != 0 )
        {
            rslt = ENVIRONMENT_E_COM_FAIL;
        }
        if ( rslt == ENVIRONMENT_DEVICE_OK )
        {
            reg = reg & (~ENVIRONMENT_MEM_PAGE_MSK);
            reg = reg | (ctx->device_mem_page & ENVIRONMENT_MEM_PAGE_MSK);

            com_rslt = user_write_data( ctx, ENVIRONMENT_MEM_PAGE_ADDR & ENVIRONMENT_SPI_WR_MSK,&reg, 1);
            if ( com_rslt != 0 )
            {
                rslt = ENVIRONMENT_E_COM_FAIL;
            }
        }
    }

    return rslt;
}

static int8_t bme680_boundary_check ( environment_t *ctx, uint8_t *value, uint8_t min, uint8_t max)
{
    int8_t rslt = ENVIRONMENT_DEVICE_OK;

    if (value != 0)
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
        rslt = ENVIRONMENT_E_NULL_PTR;
    }

    return rslt;
}

static void hw_reset_delay ( void ) 
{
    Delay_1sec( );
}
// ------------------------------------------------------------------------- END

