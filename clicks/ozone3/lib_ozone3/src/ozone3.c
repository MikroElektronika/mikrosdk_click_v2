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
 * @file ozone3.c
 * @brief Ozone 3 Click Driver.
 */

#include "ozone3.h"

#define OZONE3_ADC_RESOLUTION                    4095
#define OZONE3_MPPM_TO_PPM                       1000
#define OZONE3_I2C_BUSY_BIT_MASK                 0x01

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Enable delay.
 * @details Enable delay for 10 microseconds.
 */
static void dev_enable_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ozone3_cfg_setup ( ozone3_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->an   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = OZONE3_SET_DEV_ADDR;
}

err_t ozone3_init ( ozone3_t *ctx, ozone3_cfg_t *cfg ) {
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

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->an, cfg->an );

    return I2C_MASTER_SUCCESS;
}

err_t ozone3_default_cfg ( ozone3_t *ctx ) {
    // Click default configuration.
   
    ozone3_write_byte( ctx, OZONE3_REG_MODECN, OZONE3_DEEP_SLEEP_MODE );
   
    ozone3_write_byte( ctx, OZONE3_REG_LOCK, OZONE3_WRITE_MODE );
    
    ozone3_write_byte( ctx, OZONE3_REG_TIACN,  OZONE3_RES_TIA_EXT | 
                                               OZONE3_RES_LOAD_100_Ohm );
    
    ozone3_write_byte( ctx, OZONE3_REG_REFCN, OZONE3_VREF_INT | 
                                              OZONE3_PERCENTS_INT_ZERO_50 | 
                                              OZONE3_BIAS_POL_NEGATIVE | 
                                              OZONE3_PERCENTS_BIAS_0 );

    return OZONE3_OK;
}

err_t ozone3_generic_write ( ozone3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t ozone3_generic_read ( ozone3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t ozone3_enable ( ozone3_t *ctx, uint8_t state ) {
    dev_enable_delay( );
    digital_out_write( &ctx->rst, state );
    
    return OZONE3_OK; 
}

err_t ozone3_write_byte ( ozone3_t *ctx, uint8_t reg, uint8_t dev_data ) {   
    ozone3_enable( ctx, OZONE3_DEVICE_ENABLE );
    err_t error_flag = ozone3_generic_write( ctx, reg, &dev_data, 1 );
    ozone3_enable( ctx, OZONE3_DEVICE_DISABLE );
    
    return error_flag;
}

uint8_t ozone3_read_byte ( ozone3_t *ctx, uint8_t reg ) {
    uint8_t read_reg;
    
    ozone3_enable( ctx, OZONE3_DEVICE_ENABLE );
    ozone3_generic_read( ctx, reg, &read_reg, 1 );
    ozone3_enable( ctx, OZONE3_DEVICE_DISABLE );
    
    return read_reg;
}

uint16_t ozone3_read_adc ( ozone3_t *ctx ) {
    uint8_t read_data[ 2 ];
    uint16_t adc_data;
    
    i2c_master_set_slave_address( &ctx->i2c, OZONE3_ADC_DEVICE_ADDR );
    i2c_master_read( &ctx->i2c, read_data, 2 );   
    
    adc_data = read_data[ 0 ];
    adc_data <<= 8;
    adc_data |= read_data[ 1 ];
    adc_data &= OZONE3_ADC_RESOLUTION;
        
    return adc_data;
}

float ozone3_get_o3_ppm ( ozone3_t *ctx ) {
    uint16_t adc_data;
    float temp;
    
    adc_data = ozone3_read_adc( ctx );
    
    temp = ( float ) adc_data;
    temp /= OZONE3_ADC_RESOLUTION;
    temp *= OZONE3_MPPM_TO_PPM;

    return temp;
}

void ozone3_wait_ready ( ozone3_t *ctx ) {
    uint8_t i2c_busy;

    i2c_busy = ozone3_read_byte( ctx, OZONE3_REG_STATUS );
    
    while ( !( i2c_busy & OZONE3_I2C_BUSY_BIT_MASK ) ) {
        i2c_busy = ozone3_read_byte( ctx, OZONE3_REG_STATUS );
    }
}

// ---------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_enable_delay ( void ) {
    Delay_10us( );    
}

// ------------------------------------------------------------------------- END
