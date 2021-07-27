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
 * @file lightranger5.c
 * @brief LightRanger 5 Click Driver.
 */

#include "lightranger5.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Reset delay.
 * @details Reset delay for 100 milliseconds.
 */
static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lightranger5_cfg_setup ( lightranger5_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->en   = HAL_PIN_NC;
    cfg->io0 = HAL_PIN_NC;
    cfg->io1 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHTRANGER5_SET_DEV_ADDR;
}

err_t lightranger5_init ( lightranger5_t *ctx, lightranger5_cfg_t *cfg ) {
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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->io0, cfg->io0 );
    digital_out_init( &ctx->io1, cfg->io1 );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t lightranger5_default_cfg ( lightranger5_t *ctx ) {
    // Click default configuration.
    
    lightranger5_enable_device( ctx );
    dev_reset_delay( );
    
    lightranger5_set_pin_state_io0( ctx, 1 );
    dev_reset_delay( );
    
    return LIGHTRANGER5_OK;
}

err_t lightranger5_generic_write ( lightranger5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t lightranger5_generic_read ( lightranger5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t lightranger5_enable_device ( lightranger5_t *ctx ) {
    digital_out_high( &ctx->en );
    
    return LIGHTRANGER5_OK;
}

err_t lightranger5_disable_device ( lightranger5_t *ctx ) {
    digital_out_low( &ctx->en );
    
    return LIGHTRANGER5_OK;
}

err_t lightranger5_set_pin_state_io0 ( lightranger5_t *ctx, uint8_t io0_state ) {
    digital_out_write( &ctx->io0, io0_state );
    
    return LIGHTRANGER5_OK;
}

err_t lightranger5_set_pin_state_io1 ( lightranger5_t *ctx, uint8_t io1_state ) {
    digital_out_write( &ctx->io1, io1_state );
    
    return LIGHTRANGER5_OK;
}

err_t lightranger5_device_reset ( lightranger5_t *ctx ) {
    uint8_t data_buf[ 2 ];
    uint8_t read_reg;

    lightranger5_generic_read( ctx, LIGHTRANGER5_REG_ENABLE, &read_reg, 1 );
    read_reg &= ~( LIGHTRANGER5_ENABLE_RESET );
    read_reg |= LIGHTRANGER5_ENABLE_RESET;
    
    data_buf[ 0 ] = LIGHTRANGER5_REG_ENABLE;
    data_buf[ 1 ] = read_reg;
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    dev_reset_delay( );
    
    return error_flag;
}

err_t lightranger5_load_app ( lightranger5_t *ctx ) {
    uint8_t data_buf[ 2 ];

    data_buf[ 0 ] = LIGHTRANGER5_REG_APPREQID;
    data_buf[ 1 ] = LIGHTRANGER5_APPID_MEASUREMENT;
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    dev_reset_delay( );
    
    return error_flag;
}

err_t lightranger5_start_calib_cmd ( lightranger5_t *ctx ) {
    uint8_t data_buf[ 2 ];

    data_buf[ 0 ] = LIGHTRANGER5_REG_COMMAND;
    data_buf[ 1 ] = LIGHTRANGER5_CMD_FACTORY_CALIB;
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    
    return error_flag;
}

err_t lightranger5_check_factory_calibration ( lightranger5_t *ctx ) {
    uint8_t reg_tmp;
    
    lightranger5_generic_read( ctx, LIGHTRANGER5_REG_DEVICE_ID, &reg_tmp, 1 );
    if ( reg_tmp != LIGHTRANGER5_EXPECTED_ID ) {
        return LIGHTRANGER5_ERROR;
    }
    
    lightranger5_device_reset( ctx );
    lightranger5_generic_read( ctx, LIGHTRANGER5_REG_ENABLE, &reg_tmp, 1 );
    if ( !( reg_tmp & LIGHTRANGER5_BIT_CPU_RDY ) ) {
        return LIGHTRANGER5_ERROR;
    }
    
    lightranger5_load_app( ctx );
    lightranger5_generic_read( ctx, LIGHTRANGER5_REG_APPID, &reg_tmp, 1 );
    if ( reg_tmp != LIGHTRANGER5_APPID_MEASUREMENT ) {
        return LIGHTRANGER5_ERROR;
    }
    
    lightranger5_start_calib_cmd( ctx );
}

err_t lightranger5_get_status ( lightranger5_t *ctx, uint8_t *status ) {
    err_t error_flag = lightranger5_generic_read( ctx, LIGHTRANGER5_REG_STATUS, status, 1 );
    
    return error_flag;
}

err_t lightranger5_set_command ( lightranger5_t *ctx, uint8_t cmd ) {
    err_t error_flag = lightranger5_generic_write( ctx, LIGHTRANGER5_REG_STATUS, &cmd, 1 );
    
    return error_flag;
}

err_t lightranger5_set_factory_calib_data ( lightranger5_t *ctx, uint8_t *factory_calib_data ) {
    err_t error_flag = lightranger5_generic_write( ctx, LIGHTRANGER5_REG_FACTORY_CALIB_0, factory_calib_data, 14 );
    
    return error_flag;
}

err_t lightranger5_get_factory_calib_data ( lightranger5_t *ctx, uint8_t *factory_calib_data ) {
    err_t error_flag = lightranger5_generic_read( ctx, LIGHTRANGER5_REG_FACTORY_CALIB_0, factory_calib_data, 14 );
    
    return error_flag;
}

err_t lightranger5_set_algorithm_state_data ( lightranger5_t *ctx, uint8_t *alg_state_data ) {
    err_t error_flag = lightranger5_generic_write( ctx, LIGHTRANGER5_REG_STATE_DATA_WR_0, alg_state_data, 11 );
    
    return error_flag;
}

err_t lightranger5_set_command_data ( lightranger5_t *ctx, uint8_t *cmd_data ) {
    err_t error_flag = lightranger5_generic_write( ctx, LIGHTRANGER5_REG_CMD_DATA7, cmd_data, 9 );
    
    return error_flag;
}

err_t lightranger5_check_previous_command ( lightranger5_t *ctx, uint8_t *previous_cmd ) {   
    err_t error_flag = lightranger5_generic_write( ctx, LIGHTRANGER5_REG_PREVIOUS, previous_cmd, 1 );
    
    return error_flag;
}

err_t lightranger5_get_currently_run_app ( lightranger5_t *ctx, uint8_t *appid_data ) {
    err_t error_flag = lightranger5_generic_read( ctx, LIGHTRANGER5_REG_APPID, appid_data, 1 );
    
    return error_flag;
}

lightranger5_return_data_ready_t lightranger5_check_data_ready ( lightranger5_t *ctx ) {
    uint8_t rx_buf;
    
    lightranger5_generic_read( ctx, LIGHTRANGER5_REG_REGISTER_CONTENTS, &rx_buf, 1 );
    
    if ( rx_buf == LIGHTRANGER5_CMD_RESULT ) {
        return LIGHTRANGER5_DATA_IS_READY;    
    } else {
        return LIGHTRANGER5_DATA_NOT_READY;    
    }
}

uint16_t lightranger5_measure_distance ( lightranger5_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint16_t result;
    
    lightranger5_generic_read( ctx, LIGHTRANGER5_REG_DISTANCE_PEAK_0, rx_buf, 2 );
    
    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];
    
    return result;
}

uint8_t lightranger5_check_int ( lightranger5_t *ctx ) {   
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
