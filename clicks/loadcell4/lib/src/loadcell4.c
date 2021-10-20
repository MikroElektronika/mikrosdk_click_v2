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
 * @file loadcell4.c
 * @brief Load Cell 4 Click Driver.
 */

#include "loadcell4.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Hardware reset function.
 * @details The function performs hardware reset with delay of 40 ms.
 */
static void dev_hw_reset ( loadcell4_t *ctx );

/**
 * @brief Measurement delay function.
 * @details The function performs the measurement delay of 1 ms.
 */
static void dev_measure_delay ( void );

/**
 * @brief Power ON/OFF delay function.
 * @details The function performs the power ON/OFF delay of 1 ms.
 */
static void dev_pwr_delay ( void );

/**
 * @brief Reset delay function.
 * @details The function performs the reset delay of 10 ms.
 */
static void dev_reset_delay ( void );

/**
 * @brief Generic write data function.
 * @param[in] cmd_byte : 8-bit command byte.
 * @param[in] write_word : 16-bit write data.
 */
static void dev_i2c_write ( loadcell4_t *ctx, uint8_t cmd_byte, uint16_t write_word );

/**
 * @brief Generic read data function.
 * @param[out] read_buf : Pointer to the memory location where data be stored.
 */
static void dev_i2c_read ( loadcell4_t *ctx, uint8_t *read_buf );

/**
 * @brief Read eeprom data function.
 * @param[in] cmd_byte : 8-bit command byte.
 * @param[out] read_word : Pointer to the memory location where data be stored.
 */
static uint8_t dev_i2c_read_eeprom ( loadcell4_t *ctx, uint8_t cmd_data, uint16_t *read_word );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void loadcell4_cfg_setup ( loadcell4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LOADCELL4_SET_DEV_ADDR;
}

err_t loadcell4_init ( loadcell4_t *ctx, loadcell4_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    digital_out_init( &ctx->en, cfg->en );

    return I2C_MASTER_SUCCESS;
}

err_t loadcell4_default_cfg ( loadcell4_t *ctx ) {
    digital_out_high( &ctx->en );
    return LOADCELL4_OK;
}

err_t loadcell4_generic_write ( loadcell4_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t loadcell4_generic_read ( loadcell4_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void loadcell4_read_raw ( loadcell4_t *ctx, uint32_t *rx_data ) {
    uint8_t rx_buf[ 4 ];
    uint32_t tmp;

    dev_i2c_read( ctx, rx_buf );

    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 3 ];
    
    *rx_data = tmp;
}

uint8_t loadcell4_read_data ( loadcell4_t *ctx, uint16_t *bridge_data, int16_t *temperature_data ) {
    uint32_t raw_data;
    uint8_t status_data;
    uint16_t temp_data;

    loadcell4_read_raw( ctx, &raw_data );

    status_data = raw_data >> 30;
    status_data &= LOADCELL4_STATUS_BIT_MASK;

    temp_data = raw_data >> 16;
    temp_data &= LOADCELL4_BRIDGE_RES;
    *bridge_data = temp_data;

    temp_data = raw_data;
    temp_data >>= 5;
    *temperature_data = temp_data;

    return status_data;
}

uint16_t loadcell4_read_bridge_data ( loadcell4_t *ctx ) {
    uint32_t raw_data;
    uint8_t status_data;
    uint16_t bridge_data;

    status_data = LOADCELL4_STATUS_ERROR;

    while ( status_data != LOADCELL4_STATUS_NORMAL ) {
        loadcell4_read_raw( ctx, &raw_data );
        dev_measure_delay( );

        status_data = raw_data >> 30;
        status_data &= LOADCELL4_STATUS_BIT_MASK;

        bridge_data = raw_data >> 16;
        bridge_data &= LOADCELL4_BRIDGE_RES;
    }

    return bridge_data;
}

void loadcell4_start_cmd_mode ( loadcell4_t *ctx ) {
    dev_i2c_write( ctx, LOADCELL4_CMD_MODE_START, LOADCELL4_DUMMY );
}

void loadcell4_end_cmd_mode ( loadcell4_t *ctx ) {
    dev_i2c_write( ctx, LOADCELL4_CMD_MODE_STOP, LOADCELL4_DUMMY );
}

void loadcell4_power_dev ( loadcell4_t *ctx, uint8_t power_state ) {
    if ( power_state == LOADCELL4_PWR_OFF ) {
        digital_out_low( &ctx->en );
    } else {
        digital_out_high( &ctx->en );
    }

    dev_pwr_delay( );
}

void loadcell4_write_eeprom ( loadcell4_t *ctx, uint8_t cmd_byte, uint16_t data_word ) {
    uint8_t eeprom_word = cmd_byte;
    eeprom_word |= LOADCELL4_EEPROM_WRITE_CMD;
    dev_i2c_write( ctx, eeprom_word, data_word );
}

uint16_t loadcell4_read_eeprom ( loadcell4_t *ctx, uint8_t cmd_byte ) {
    uint8_t status_data = 0;
    uint16_t data_word;

    while ( status_data != LOADCELL4_EEPROM_STATUS_READ_READY ) {
        status_data = dev_i2c_read_eeprom( ctx, cmd_byte, &data_word );
        dev_measure_delay( );
    }

    return data_word;
}

uint8_t loadcell4_get_int ( loadcell4_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

void loadcell4_tare ( loadcell4_t *ctx, loadcell4_data_t *cell_data ) {
    uint16_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;

    for ( n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        dev_hw_reset( ctx );
        
        while ( loadcell4_get_int( ctx ) != 1 );
        
        results = loadcell4_read_bridge_data( ctx );

        dev_measure_delay( );
    }

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 100; n_cnt++ ) {
        dev_hw_reset( ctx );
        results = loadcell4_read_bridge_data( ctx );
        sum_val += results;
        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= LOADCELL4_NUMB_OF_SUM_AVG_100;

    cell_data->tare = average_val;
    cell_data->tare_ok = LOADCELL4_DATA_OK;
    cell_data->weight_data_100g_ok = LOADCELL4_DATA_NO_DATA;
    cell_data->weight_data_500g_ok = LOADCELL4_DATA_NO_DATA;
    cell_data->weight_data_1000g_ok = LOADCELL4_DATA_NO_DATA;
    cell_data->weight_data_5000g_ok = LOADCELL4_DATA_NO_DATA;
    cell_data->weight_data_10000g_ok = LOADCELL4_DATA_NO_DATA;
}

err_t loadcell4_calibration ( loadcell4_t *ctx, uint16_t cal_val, loadcell4_data_t *cell_data ) {
    uint16_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    uint8_t status;

    status = LOADCELL4_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 100; n_cnt++ ) {
        dev_hw_reset( ctx );
        
        while ( loadcell4_get_int( ctx ) != 1 );
        
        results = loadcell4_read_bridge_data( ctx );

        sum_val += results;

        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= LOADCELL4_NUMB_OF_SUM_AVG_100;

    weight_val = average_val - tare_val;

    switch ( cal_val ) {
        case LOADCELL4_WEIGHT_100G: {
            cell_data->weight_coeff_100g = ( float )LOADCELL4_WEIGHT_100G / weight_val;
            cell_data->weight_data_100g_ok = LOADCELL4_DATA_OK;
            break;
        }
        case LOADCELL4_WEIGHT_500G: {
            cell_data->weight_coeff_500g = ( float )LOADCELL4_WEIGHT_500G / weight_val;
            cell_data->weight_data_500g_ok = LOADCELL4_DATA_OK;
            break;
        }
        case LOADCELL4_WEIGHT_1000G: {
            cell_data->weight_coeff_1000g = ( float )LOADCELL4_WEIGHT_1000G / weight_val;
            cell_data->weight_data_1000g_ok = LOADCELL4_DATA_OK;
            break;
        }
        case LOADCELL4_WEIGHT_5000G: {
            cell_data->weight_coeff_5000g = ( float )LOADCELL4_WEIGHT_5000G / weight_val;
            cell_data->weight_data_5000g_ok = LOADCELL4_DATA_OK;
            break;
        }
        case LOADCELL4_WEIGHT_10000G: {
            cell_data->weight_coeff_10000g = ( float )LOADCELL4_WEIGHT_10000G / weight_val;
            cell_data->weight_data_10000g_ok = LOADCELL4_DATA_OK;
            break;
        }
        default : {
            status = LOADCELL4_ERROR;
            cell_data->weight_data_100g_ok = LOADCELL4_DATA_NO_DATA;
            cell_data->weight_data_500g_ok = LOADCELL4_DATA_NO_DATA;
            cell_data->weight_data_1000g_ok = LOADCELL4_DATA_NO_DATA;
            cell_data->weight_data_5000g_ok = LOADCELL4_DATA_NO_DATA;
            cell_data->weight_data_10000g_ok = LOADCELL4_DATA_NO_DATA;
            break;
        }
    }

    return status;
}

float loadcell4_get_weight ( loadcell4_t *ctx, loadcell4_data_t *cell_data ) {
    uint16_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    uint8_t status;

    status = LOADCELL4_GET_RESULT_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 100; n_cnt++ ) {
        dev_hw_reset( ctx );
        
        while ( loadcell4_get_int( ctx ) != 1 );
        
        results = loadcell4_read_bridge_data( ctx );

        sum_val += results;

        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= LOADCELL4_NUMB_OF_SUM_AVG_100;

    weight_val = average_val - tare_val;

    if ( cell_data->weight_data_100g_ok == LOADCELL4_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_100g;
        dev_pwr_delay( );
    } else if ( cell_data->weight_data_500g_ok == LOADCELL4_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_500g;
        dev_pwr_delay( );
    } else if ( cell_data->weight_data_1000g_ok == LOADCELL4_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_1000g;
        dev_pwr_delay( );
    } else if ( cell_data->weight_data_5000g_ok == LOADCELL4_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_5000g;
        dev_pwr_delay( );
    } else if ( cell_data->weight_data_10000g_ok == LOADCELL4_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_10000g;
        dev_pwr_delay( );
    }

    if ( weight_val < 0 ) {
        weight_val = LOADCELL4_WEIGHT_ZERO;
    }

    return weight_val;
}


// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_hw_reset ( loadcell4_t *ctx ) {
    digital_out_low( &ctx->en );
    dev_reset_delay( );
    digital_out_high( &ctx->en );
    dev_reset_delay( );
}

static void dev_measure_delay ( void ) {
    Delay_10us( );
}

static void dev_pwr_delay ( void ) {
    Delay_1ms( );
}

static void dev_reset_delay ( void ) {
    Delay_10ms( );
    Delay_10ms( );
}

static void dev_i2c_write ( loadcell4_t *ctx, uint8_t cmd_byte, uint16_t write_word ) {
    uint8_t write_buf[ 3 ];

    write_buf[ 0 ] = cmd_byte;
    write_buf[ 1 ] = write_word >> 8;
    write_buf[ 2 ] = write_word;

    i2c_master_write( &ctx->i2c, write_buf, 3 );

    while ( !loadcell4_get_int( ctx ) );
}

static void dev_i2c_read ( loadcell4_t *ctx, uint8_t *read_buf ) {
    i2c_master_read( &ctx->i2c, read_buf, 4 );
}

static uint8_t dev_i2c_read_eeprom ( loadcell4_t *ctx, uint8_t cmd_data, uint16_t *read_word ) {
    uint8_t read_buf[ 3 ] = { 0, 0, 0 };
    uint16_t temp_data;

    read_buf[ 0 ] = cmd_data;

    i2c_master_write( &ctx->i2c, read_buf, 3 );
    i2c_master_read( &ctx->i2c, read_buf, 3 );

    temp_data = read_buf[ 1 ];
    temp_data <<= 8;
    temp_data |= read_buf[ 2 ];

    *read_word = temp_data;

    return read_buf[ 0 ];
}

// ------------------------------------------------------------------------- END
