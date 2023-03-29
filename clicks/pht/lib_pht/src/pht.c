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
 * @file pht.c
 * @brief PHT Click Driver.
 */

#include "pht.h"

static uint32_t prom_coeff[ 6 ];
static uint8_t ratio_temp;
static uint8_t ratio_press;

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Send I2C address change delay function
 * @details The function performs the address change delay of 1 ms.
 */
static void dev_addr_change_delay( void );

/**
 * @brief Send hold delay function
 * @details The function performs the hold delay of 20 ms.
 */
static void dev_hold_delay( void );

/**
 * @brief Send Command Delay function
 * @details The function performs the send command delay of 10 ms.
 */
static void dev_send_cmd_delay ( void );

/**
 * @brief Command Send function
 * @details The function performs the desired command 
 * by determined communication.
 * @param[out] cfg : Click configuration structure.
 * See #pht_cfg_t object definition for detailed explanation.
 * @param[in] cmd_byte : Command which be performed
 */
static void dev_send_cmd ( pht_t *ctx, uint8_t cmd_byte );

/**
 * @brief Send Command With Device Response function
 * @details The function performs the desired command 
 * by determined communication and reads response from the device.
 * @param[in] cfg : Click configuration structure.
 * See #pht_cfg_t object definition for detailed explanation.
 * @param[in] num_bytes : Number of bytes which be read
 * @param[in] tx_data : Buffer where data (device response) be stored
 * @param[in] cmd_byte : Command which be performed
 */
static void dev_send_cmd_resp ( pht_t *ctx, uint8_t cmd_byte, uint8_t num_bytes, uint32_t *tx_data );

/**
 * @brief Conversion Command Make function
 * @details The function makes the conversion command byte for desired ratio.
 * @param[out] cmd_temp : Stores the conversion command for desired temperature ratio
 * @param[out] cmd_press : Stores the conversion command for desired pressure ratio
 */
static void dev_make_conv_cmd ( uint8_t *cmd_temp, uint8_t *cmd_press );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void pht_cfg_setup ( pht_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PHT_I2C_SLAVE_ADDR_P_AND_T;
}

err_t pht_init ( pht_t *ctx, pht_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t pht_generic_write ( pht_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t pht_generic_read ( pht_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void pht_set_command ( pht_t *ctx, uint8_t sensor_type, uint8_t cmd ) {   
    if ( sensor_type == PHT_SENSOR_TYPE_PT ) {
        i2c_master_set_slave_address( &ctx->i2c, PHT_I2C_SLAVE_ADDR_P_AND_T );
        dev_addr_change_delay( );
        
        i2c_master_write( &ctx->i2c, &cmd, 1 );
        
        i2c_master_set_slave_address( &ctx->i2c, PHT_I2C_SLAVE_ADDR_RH );
        dev_addr_change_delay( );
    } else {
        i2c_master_write( &ctx->i2c, &cmd, 1 );
    }
}

void pht_soft_reset ( pht_t *ctx, uint8_t sensor_type ) {
    if ( sensor_type == PHT_SENSOR_TYPE_PT ) {
        pht_set_command( ctx, sensor_type, PHT_PT_CMD_RESET );
    } else {
        pht_set_command( ctx, sensor_type, PHT_RH_CMD_RESET );
    }
}

uint8_t pht_get_prom ( pht_t *ctx, uint8_t sel_data, uint32_t *tx_data ) {
    uint8_t tmp_data;

    if ( sel_data > 7 ) {
        return PHT_ERROR;
    }

    tmp_data = PHT_PT_CMD_PROM_READ_P_T_START | ( sel_data << 1 );
    dev_send_cmd_resp( ctx, tmp_data, 2, tx_data );

    return PHT_OK;
}

uint8_t pht_set_ratio ( pht_t *ctx, uint8_t temp_ratio, uint8_t press_ratio ) {
    if ( temp_ratio > PHT_PT_CMD_RATIO_8192 ) {
        return PHT_ERROR;
    }

    if ( temp_ratio > PHT_PT_CMD_RATIO_8192 ) {
        return PHT_ERROR;
    }

    ratio_temp = temp_ratio;
    ratio_press = press_ratio;

    return PHT_OK;
}

void pht_reset ( pht_t *ctx ) {
    uint8_t cmd_data;
    uint8_t n_cnt;

    cmd_data = PHT_PT_CMD_RESET;

    dev_send_cmd( ctx, cmd_data );

    for ( n_cnt = 1; n_cnt < 7; n_cnt++ ) {
        pht_get_prom( ctx, n_cnt, &prom_coeff[ n_cnt - 1 ] );
    }
}

void pht_write_user_register ( pht_t *ctx, uint8_t tx_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = PHT_RH_CMD_WRITE_USER_REG;
    tx_buf[ 1 ] = tx_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t pht_read_user_register ( pht_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = PHT_RH_CMD_READ_USER_REG;

    i2c_master_write( &ctx->i2c, tx_buf, 1 );
    i2c_master_read( &ctx->i2c, rx_buf, 1 );
    
    return rx_buf[ 0 ];
}

uint8_t pht_measure_rh ( pht_t *ctx, uint16_t *rh_data ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 3 ];
    uint8_t status;
    uint16_t tmp;

    tx_buf[ 0 ] = PHT_RH_MEASURE_RH_NO_HOLD;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 2 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp >>= 2;
    
    *rh_data = tmp;
    
    status = rx_buf[ 1 ] & 0x03;

    return status;
}

void pht_get_temperature_pressure ( pht_t *ctx, float *temperature, float *pressure ) {
    uint32_t buff_data[ 2 ];
    uint8_t temp_cmd;
    uint8_t press_cmd;
    float res_data[ 4 ];
    
    dev_make_conv_cmd( &temp_cmd, &press_cmd );
    dev_send_cmd( ctx, temp_cmd );
    dev_send_cmd_resp( ctx, PHT_PT_CMD_ADC_READ, 3, &buff_data[ 0 ] );
    dev_send_cmd( ctx, press_cmd );
    dev_send_cmd_resp( ctx, PHT_PT_CMD_ADC_READ, 3, &buff_data[ 1 ] );

    res_data[ 0 ] = prom_coeff[ 4 ] * 256.0;
    res_data[ 0 ] = buff_data[ 0 ] - res_data[ 0 ];
    res_data[ 1 ] = res_data[ 0 ] / 8.0;
    res_data[ 1 ] = res_data[ 1 ] * ( prom_coeff[ 5 ] / 1048576.0 );
    res_data[ 1 ] = res_data[ 1 ] + 2000.0;
    res_data[ 1 ] /= 100.0;
    *temperature = res_data[ 1 ];

    res_data[ 2 ] = res_data[ 0 ] / 128.0;
    res_data[ 2 ] = res_data[ 2 ] * ( prom_coeff[ 2 ] / 2097152.0 );
    res_data[ 2 ] = res_data[ 2 ] + ( prom_coeff[ 0 ] / 32.0 );
    res_data[ 3 ] = res_data[ 0 ] / 32.0;
    res_data[ 3 ] = res_data[ 3 ] * ( prom_coeff[ 3 ] / 65536.0 );
    res_data[ 3 ] = res_data[ 3 ] + ( prom_coeff[ 1 ] * 4.0 );
    res_data[ 1 ] = buff_data[ 1 ] / 32768.0;
    res_data[ 1 ] = res_data[ 1 ] * res_data[ 2 ];
    res_data[ 1 ] = res_data[ 1 ] - res_data[ 3 ];
    res_data[ 1 ] /= 100.0;
    *pressure = res_data[ 1 ];
}

void pht_get_relative_humidity ( pht_t *ctx, float *humidity ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 3 ];
    uint16_t rh_val;
    float rh;

    tx_buf[ 0 ] = PHT_RH_MEASURE_RH_HOLD;

    i2c_master_write( &ctx->i2c, tx_buf, 1 );
    dev_hold_delay( );
    i2c_master_read( &ctx->i2c, rx_buf, 2 );
    
    rh_val = rx_buf[ 0 ];
    rh_val <<= 8;
    rh_val |= rx_buf[ 1 ];

    rh = ( float ) rh_val;
    rh *= 12500.0;
    rh /= 65536.0;
    rh -= 600.0;
    rh /= 100.0;

    *humidity = rh;
}


// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_addr_change_delay( void ) {
    Delay_1ms( );
}

static void dev_hold_delay( void ) {
    Delay_10ms( );
    Delay_10ms( );
}

static void dev_send_cmd_delay ( void ) {
    Delay_10ms( );
}

static void dev_send_cmd ( pht_t *ctx, uint8_t cmd_byte ) {
    uint8_t tx_buf[ 1 ];
    
    tx_buf[ 0 ] = cmd_byte;
    
    i2c_master_set_slave_address( &ctx->i2c, PHT_I2C_SLAVE_ADDR_P_AND_T );
    dev_addr_change_delay( );
    
    i2c_master_write( &ctx->i2c, tx_buf, 1 );
    dev_send_cmd_delay( );
    
    i2c_master_set_slave_address( &ctx->i2c, PHT_I2C_SLAVE_ADDR_RH );
    dev_addr_change_delay( );
}

static void dev_send_cmd_resp ( pht_t *ctx, uint8_t cmd_byte, uint8_t n_bytes, uint32_t *tx_data ) {
    uint8_t tmp[ 3 ];
    uint8_t cnt;
    uint32_t pom;
    
    pom = 0;

    tmp[ 0 ] = cmd_byte;

    i2c_master_set_slave_address( &ctx->i2c, PHT_I2C_SLAVE_ADDR_P_AND_T );
    dev_addr_change_delay( );
    
    i2c_master_write( &ctx->i2c, tmp, 1 );
    i2c_master_read( &ctx->i2c, tmp, n_bytes );
    
    i2c_master_set_slave_address( &ctx->i2c, PHT_I2C_SLAVE_ADDR_RH );
    dev_addr_change_delay( );

    for ( cnt = 0; cnt < n_bytes; cnt++ ) {
        pom <<= 8;
        pom |= tmp[ cnt ];
    }
    
    *tx_data = pom;
}

static void dev_make_conv_cmd ( uint8_t *cmd_temp, uint8_t *cmd_press ) {
    uint8_t cmd_byte;
    uint8_t ratio_cnt;
    
    cmd_byte = 0x50;
    ratio_cnt = 0;

    while ( ratio_temp != ratio_cnt ) {
        cmd_byte += 2;
        ratio_cnt++;
    }
    
    *cmd_temp = cmd_byte;

    cmd_byte = 0x40;
    ratio_cnt = 0;
    
    while ( ratio_press != ratio_cnt ) {
        cmd_byte += 2;
        ratio_cnt++;
    }
    
    *cmd_press = cmd_byte;
}

// ------------------------------------------------------------------------- END
