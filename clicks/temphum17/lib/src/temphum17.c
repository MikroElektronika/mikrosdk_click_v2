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
 * @file temphum17.c
 * @brief Temp&Hum 17 Click Driver.
 */

#include "temphum17.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define TEMPHUM17_WAKE_UP                                                0x00
#define TEMPHUM17_BIT_MASK_SIGN_8_BIT                                  0x007F
#define TEMPHUM17_BIT_MASK_SIGN_10_BIT                                 0x01FF
#define TEMPHUM17_BIT_MASK_SIGN_12_BIT                                 0x07FF
#define TEMPHUM17_BIT_MASK_SIGN_14_BIT                                 0x1FFF

#define TEMPHUM17_MULTIPLIER_COEF_TEMP                                    165
#define TEMPHUM17_ADDITION_COEF_TEMP                                       40
#define TEMPHUM17_MULTIPLIER_COEF_HUM                                     100

#define TEMPHUM17_BIT_MASK_8_BIT                                       0x00FF
#define TEMPHUM17_BIT_MASK_10_BIT                                      0x03FF
#define TEMPHUM17_BIT_MASK_12_BIT                                      0x0FFF
#define TEMPHUM17_BIT_MASK_14_BIT                                      0x3FFF

#define TEMPHUM17_BIT_MASK_STATUS                                        0x03
#define TEMPHUM17_BIT_MASK_RESOLUTION                                    0xF3

#define TEMPHUM17_NON_VOLATILE_MEMORY_STATUS_SUCCESS                     0x81

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Delay for 8-bit data resolution function.
 * @details This function performs a delay of the 1.20 milliseconds.
 * @return Nothing.
 * @note None.
 *
 * @endcode
 */
static void delay_resolution_8_bits ( void );

/**
 * @brief Delay for 10-bit data resolution function.
 * @details This function performs a delay of the 2.72 milliseconds.
 * @return Nothing.
 * @note None.
 *
 * @endcode
 */
static void delay_resolution_10_bits ( void );

/**
 * @brief Delay for 12-bit data resolution function.
 * @details This function performs a delay of the 9.10 milliseconds.
 * @return Nothing.
 * @note None.
 *
 * @endcode
 */
static void delay_resolution_12_bits ( void );

/**
 * @brief Delay for 14-bit data resolution function.
 * @details This function performs a delay of the 33.90 milliseconds.
 * @return Nothing.
 * @note None.
 *
 * @endcode
 */
static void delay_resolution_14_bits ( void );

/**
 * @brief The load data delay function.
 * @details This function performs a delay of the 220 microseconds.
 * @return Nothing.
 * @note None.
 *
 * @endcode
 */
static void delay_load_data ( void );

/**
 * @brief The configuration delay function.
 * @details This function performs a delay of the 14 milliseconds.
 * @return Nothing.
 * @note None.
 *
 * @endcode
 */
static void delay_cfg ( void ) ;

/**
 * @brief The delay selection function.
 * @details This function performs a delay depending on the selected data resolution:
 *         @li @c 14-bit resolution it is 33.90 milliseconds,
 *         @li @c 12-bit resolution it is 9.10 milliseconds,
 *         @li @c 10-bit resolution it is 2.72 milliseconds, 
 *         @li @c  8-bit resolution it is 1.20 milliseconds.  
 * @return Nothing.
 * @note None.
 *
 * @endcode
 */
static void ( *delay_ptr[ 4 ] )( void ) = {
    delay_resolution_8_bits,
    delay_resolution_10_bits,
    delay_resolution_12_bits,
    delay_resolution_14_bits
};

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum17_cfg_setup ( temphum17_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM17_SET_DEV_ADDR;
}

err_t temphum17_init ( temphum17_t *ctx, temphum17_cfg_t *cfg ) {
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

err_t temphum17_default_cfg ( temphum17_t *ctx ) {
    err_t err_flag = temphum17_wake_up( ctx );
    return err_flag;
}

err_t temphum17_generic_write ( temphum17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t temphum17_generic_read ( temphum17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t temphum17_wake_up ( temphum17_t *ctx ) {
    uint8_t data_buf;
    data_buf = TEMPHUM17_WAKE_UP;
    
    err_t err_flag = i2c_master_write( &ctx->i2c, &data_buf, 1 );
    
    return err_flag;
}

err_t temphum17_get_raw_data ( temphum17_t *ctx, uint8_t resolution, int16_t *temp, uint16_t *hum, uint8_t *status ) {
    uint8_t tx_buf;
    uint8_t rx_buf[ 4 ];
    uint16_t tmp;
    uint8_t resolution_delay;
    uint16_t res_bit_mask;
    uint16_t signed_check;
    
    if ( resolution > TEMPHUM17_RESOLUTION_14_BITS ) {
        return TEMPHUM17_ERROR;     
    } else {
        resolution_delay = resolution;    
    }
    
    switch ( resolution ) {
        case TEMPHUM17_RESOLUTION_10_BITS: {
            res_bit_mask = TEMPHUM17_BIT_MASK_10_BIT;
            signed_check = TEMPHUM17_BIT_MASK_SIGN_10_BIT;
            break;
        }
        case TEMPHUM17_RESOLUTION_12_BITS: {
            res_bit_mask = TEMPHUM17_BIT_MASK_12_BIT;
            signed_check = TEMPHUM17_BIT_MASK_SIGN_12_BIT;
            break;
        }
        case TEMPHUM17_RESOLUTION_14_BITS: {
            res_bit_mask = TEMPHUM17_BIT_MASK_14_BIT;
            signed_check = TEMPHUM17_BIT_MASK_SIGN_14_BIT;
            break;
        }
        default: {
            res_bit_mask = TEMPHUM17_BIT_MASK_8_BIT;
            signed_check = TEMPHUM17_BIT_MASK_SIGN_8_BIT;
        }
    }
    
    tx_buf = TEMPHUM17_WAKE_UP;
    i2c_master_write( &ctx->i2c, &tx_buf, 1 );
    ( *delay_ptr[ resolution_delay ] )( );
    err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 4 );
    
    *status = ( rx_buf[ 0 ] >> 6 );
    *status &= TEMPHUM17_BIT_MASK_STATUS;
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp &= res_bit_mask;
    
    *hum = tmp;
        
    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 3 ];
    tmp >>= 2;
    tmp &= res_bit_mask;
     
    if ( tmp > signed_check ) {
        *temp = ++signed_check; 
        *temp -= tmp;
    } else {
        *temp = tmp;   
    }
    
    return err_flag; 
}

err_t temphum17_get_temp_hum ( temphum17_t *ctx, uint8_t resolution, float *temperature, float *humidity ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 4 ];
    uint16_t tmp;
    uint8_t resolution_delay;
    uint8_t status;
    uint16_t res_bit_mask;
    uint16_t hum;
    int16_t temp;
    
    switch ( resolution ) {
        case TEMPHUM17_RESOLUTION_10_BITS: {
            res_bit_mask = TEMPHUM17_BIT_MASK_10_BIT;
            break;
        }
        case TEMPHUM17_RESOLUTION_12_BITS: {
            res_bit_mask = TEMPHUM17_BIT_MASK_12_BIT;
            break;
        }
        case TEMPHUM17_RESOLUTION_14_BITS: {
            res_bit_mask = TEMPHUM17_BIT_MASK_14_BIT;
            break;
        }
        default: {
            res_bit_mask = TEMPHUM17_BIT_MASK_8_BIT;
        }
    }
    
    err_t err_flag = temphum17_get_raw_data( ctx, resolution, &temp, &hum, &status );
    
    *humidity = ( float ) hum;
    *humidity /= ( float ) TEMPHUM17_BIT_MASK_14_BIT;
    *humidity *= TEMPHUM17_MULTIPLIER_COEF_HUM;
    
    *temperature = ( float ) temp;
    *temperature /= ( float )  TEMPHUM17_BIT_MASK_14_BIT;
    *temperature *= TEMPHUM17_MULTIPLIER_COEF_TEMP;
    *temperature -= TEMPHUM17_ADDITION_COEF_TEMP;
    
    err_flag |= status;
    
    return err_flag; 
}

err_t temphum17_enter_programming_mode ( temphum17_t *ctx ) {
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = TEMPHUM17_CMD_ENTER_PROGRAMMING_MODE;
    tx_buf[ 1 ] = TEMPHUM17_CMD_DUMMY;
    tx_buf[ 2 ] = TEMPHUM17_CMD_DUMMY;
    err_t err_flag = i2c_master_write( &ctx->i2c, tx_buf, 3 );
    
    return err_flag;
}

err_t temphum17_enter_measurements_mode ( temphum17_t *ctx ) {
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = TEMPHUM17_CMD_ENTER_MEASUREMENTS_MODE;
    tx_buf[ 1 ] = TEMPHUM17_CMD_DUMMY;
    tx_buf[ 2 ] = TEMPHUM17_CMD_DUMMY;
    err_t err_flag = i2c_master_write( &ctx->i2c, tx_buf, 3 );
    
    return err_flag;
}

err_t temphum17_set_relative_humidity_resolution ( temphum17_t *ctx, uint8_t resolution ) {
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 3 ];
    
    if ( ( resolution > TEMPHUM17_RESOLUTION_14_BITS ) || ( resolution < TEMPHUM17_RESOLUTION_8_BITS ) ) {
        return TEMPHUM17_ERROR;     
    } 
    
    tx_buf[ 0 ] = TEMPHUM17_REG_HUMIDITY_SENSOR_RESOLUTION_READ;
    tx_buf[ 1 ] = TEMPHUM17_CMD_DUMMY;
    tx_buf[ 2 ] = TEMPHUM17_CMD_DUMMY;
    err_t err_flag = i2c_master_write( &ctx->i2c, tx_buf, 3 );
    delay_load_data( );
    
    err_flag |= i2c_master_read( &ctx->i2c, rx_buf, 3 );
    delay_load_data( );
    
    if ( rx_buf[ 0 ] != TEMPHUM17_NON_VOLATILE_MEMORY_STATUS_SUCCESS ) {
        return TEMPHUM17_ERROR;     
    }
    
    tx_buf[ 0 ] = TEMPHUM17_REG_HUMIDITY_SENSOR_RESOLUTION_WRITE;
    tx_buf[ 1 ] = rx_buf[ 1 ];
    tx_buf[ 1 ] &= TEMPHUM17_BIT_MASK_RESOLUTION;
    tx_buf[ 1 ] |= ( resolution << 2 );
    tx_buf[ 2 ] = rx_buf[ 2 ];
    err_flag |= i2c_master_write( &ctx->i2c, tx_buf, 3 );
    delay_cfg( );
    
    return err_flag;
}

err_t temphum17_set_temperature_resolution ( temphum17_t *ctx, uint8_t resolution ) {
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 3 ];
    
    if ( ( resolution > TEMPHUM17_RESOLUTION_14_BITS ) || ( resolution < TEMPHUM17_RESOLUTION_8_BITS ) ) {
        return TEMPHUM17_ERROR;     
    } 
    
    tx_buf[ 0 ] = TEMPHUM17_REG_TEMPERATURE_SENSOR_RESOLUTION_READ;
    tx_buf[ 1 ] = TEMPHUM17_CMD_DUMMY;
    tx_buf[ 2 ] = TEMPHUM17_CMD_DUMMY;
    err_t err_flag = i2c_master_write( &ctx->i2c, tx_buf, 3 );
    delay_load_data( );
    
    err_flag |= i2c_master_read( &ctx->i2c, rx_buf, 3 );
    delay_load_data( );
    
    if ( rx_buf[ 0 ] != TEMPHUM17_NON_VOLATILE_MEMORY_STATUS_SUCCESS ) {
        return TEMPHUM17_ERROR;     
    }
    
    tx_buf[ 0 ] = TEMPHUM17_REG_TEMPERATURE_SENSOR_RESOLUTION_WRITE;
    tx_buf[ 1 ] = rx_buf[ 1 ];
    tx_buf[ 1 ] &= TEMPHUM17_BIT_MASK_RESOLUTION;
    tx_buf[ 1 ] |= ( resolution << 2 );
    tx_buf[ 2 ] = rx_buf[ 2 ];
    err_flag |= i2c_master_write( &ctx->i2c, tx_buf, 3 );
    delay_cfg( );
    
    return err_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void delay_resolution_8_bits ( void ) {
    Delay_1ms( );
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
}

static void delay_resolution_10_bits ( void ) {
    Delay_1ms( );
    Delay_1ms( );
    Delay_500us( );
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
    Delay_10us( );
    Delay_10us( );
}

static void delay_resolution_12_bits ( void ) {
    for ( uint8_t n_cnt = 0; n_cnt < 9; n_cnt++ ) {
        Delay_1ms( );
    }
    
    Delay_50us( );
    Delay_50us( );
}

static void delay_resolution_14_bits ( void ) {
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_500us( );
    for ( uint8_t n_cnt = 0; n_cnt < 8; n_cnt++ ) {
        Delay_50us( );
    }
}

static void delay_load_data ( void ) {
    Delay_50us( );
    Delay_50us( );
    Delay_10us( );
    Delay_10us( );
}

static void delay_cfg ( void ) {
    Delay_10ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
