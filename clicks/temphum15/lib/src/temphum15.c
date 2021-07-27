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
 * @file temphum15.c
 * @brief Temp&Hum 15 Click Driver.
 */

#include "temphum15.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define DEV_TEMPHUM15_RESOLUTION_MAX                                      65535
#define DEV_TEMPHUM15_MULTIPLIER_COEF_TEMP                                175
#define DEV_TEMPHUM15_ADDITION_COEF_TEMP                                  45
#define DEV_TEMPHUM15_MULTIPLIER_COEF_HUM                                 125
#define DEV_TEMPHUM15_ADDITION_COEF_HUM                                   6
#define DEV_TEMPHUM15_HUM_MAX_VALUE                                       100
#define DEV_TEMPHUM15_HUM_MIN_VALUE                                       0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void delay_low_repeatability ( void );

static void delay_med_repeatability ( void );

static void delay_high_repeatability ( void );

static void ( *delay_ptr_arr[ 3 ] )( void ) = {
    delay_high_repeatability,
    delay_med_repeatability,
    delay_low_repeatability
};

static void delay_soft_reset ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum15_cfg_setup ( temphum15_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM15_SET_DEV_ADDR;
}

err_t temphum15_init ( temphum15_t *ctx, temphum15_cfg_t *cfg ) {
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

err_t temphum15_default_cfg ( temphum15_t *ctx ) {
    // Click default configuration.
    return temphum15_soft_reset ( ctx );
}

err_t temphum15_generic_write ( temphum15_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t temphum15_generic_read ( temphum15_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t temphum15_get_temp_and_hum ( temphum15_t *ctx, uint8_t precision_mode, float *temp_val, float *hum_val ) {
    err_t status;
    uint16_t rx_word;
    uint8_t rx_buf[ 6 ];
    uint8_t cmd;
    uint8_t delay_sel;
    
    status = TEMPHUM15_SUCCESS;
    delay_sel = 0;
    
    switch ( precision_mode ) {
        case TEMPHUM15_MODE_MEDIUM_PRECISION: {
            cmd = TEMPHUM15_CMD_MEASURE_MEDIUM_PRECISION;
            delay_sel++;
            break;
        }
        case TEMPHUM15_MODE_LOW_PRECISION: {
            cmd = TEMPHUM15_CMD_MEASURE_LOW_PRECISION;
            delay_sel += 2;
            break;
        }
        default: {
            cmd = TEMPHUM15_CMD_MEASURE_HIGH_PRECISION;
        }
    }
    
    status |= i2c_master_write( &ctx->i2c, &cmd, 1 );
    
    if ( status != TEMPHUM15_SUCCESS ) {
        return status;
    }
    
    ( *delay_ptr_arr[ delay_sel ] )( );
    
    status |= i2c_master_read( &ctx->i2c, rx_buf, 6 );
    
    rx_word = rx_buf[ 0 ];
    rx_word <<= 8;
    rx_word |= rx_buf[ 1 ];
    
    *temp_val = ( float )rx_word / DEV_TEMPHUM15_RESOLUTION_MAX;
    *temp_val *= DEV_TEMPHUM15_MULTIPLIER_COEF_TEMP;
    *temp_val -= DEV_TEMPHUM15_ADDITION_COEF_TEMP;
    
    rx_word = rx_buf[ 3 ];
    rx_word <<= 8;
    rx_word |= rx_buf[ 4 ];
    
    *hum_val = ( float )rx_word / DEV_TEMPHUM15_RESOLUTION_MAX;
    *hum_val *= DEV_TEMPHUM15_MULTIPLIER_COEF_HUM;
    *hum_val -= DEV_TEMPHUM15_ADDITION_COEF_HUM;
    
    if ( *hum_val > DEV_TEMPHUM15_HUM_MAX_VALUE ) {
        *hum_val = DEV_TEMPHUM15_HUM_MAX_VALUE;
    }
    if ( *hum_val < DEV_TEMPHUM15_HUM_MIN_VALUE ) {
        *hum_val = DEV_TEMPHUM15_HUM_MIN_VALUE;
    }

    return status;
}

err_t temphum15_soft_reset ( temphum15_t *ctx ) {
    err_t status;
    uint8_t cmd;
    
    status = TEMPHUM15_SUCCESS;
    cmd = TEMPHUM15_CMD_SOFT_RESET;
    
    status |= i2c_master_write( &ctx->i2c, &cmd, 1 );
    
    if ( status != TEMPHUM15_SUCCESS ) {
        return status;
    }
    
    delay_soft_reset( );
    
    return status;
}

err_t temphum15_read_serial ( temphum15_t *ctx, uint32_t *serial_number ) {
    err_t status;
    uint8_t rx_buf[ 6 ];
    uint8_t cmd;
    
    status = TEMPHUM15_SUCCESS;
    cmd = TEMPHUM15_CMD_READ_SERIAL;
    
    status |= i2c_master_write( &ctx->i2c, &cmd, 1 );
    
    if ( status != TEMPHUM15_SUCCESS ) {
        return status;
    }
    
    delay_soft_reset( );
    
    status |= i2c_master_read( &ctx->i2c, rx_buf, 6 );
    
    *serial_number = rx_buf[ 0 ];
    *serial_number <<= 8;
    *serial_number |= rx_buf[ 1 ];
    *serial_number <<= 8;
    *serial_number |= rx_buf[ 3 ];
    *serial_number <<= 8;
    *serial_number |= rx_buf[ 4 ];
    
    return status;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void delay_low_repeatability ( void ) {
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
}

static void delay_med_repeatability ( void ) {
    Delay_5ms( );
    Delay_1ms( );
}

static void delay_high_repeatability ( void ) {
    Delay_10ms( );
}

static void delay_soft_reset ( void ) {
    Delay_1ms( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
