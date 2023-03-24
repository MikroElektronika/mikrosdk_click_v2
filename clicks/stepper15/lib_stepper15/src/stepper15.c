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
 * @file stepper15.c
 * @brief Stepper 15 Click Driver.
 */

#include "stepper15.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                   0x00

/**
 * @brief SPI read bit mask.
 * @details Definition of SPI read bit mask.
 */
#define SPI_READ_BIT_MASK                       0x40

/**
 * @brief Fault condition bit mask.
 * @details Definition of fault condition data.
 */
#define STEPPER15_FAULT_CONDITION_BIT_MASK      0x01

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Step delay.
 * @details Reset step for 1 milliseconds.
 */
static void dev_step_delay ( void );

/**
 * @brief Reset delay.
 * @details Reset delay for 100 milliseconds.
 */
static void dev_reset_delay ( void );

/**
 * @brief Configuration delay.
 * @details Configuration delay for 10 milliseconds.
 */
static void dev_config_delay ( void );

/**
 * @brief Stepper 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t stepper15_i2c_write ( stepper15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Stepper 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t stepper15_i2c_read ( stepper15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Stepper 15 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t stepper15_spi_write ( stepper15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Stepper 15 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t stepper15_spi_read ( stepper15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void stepper15_cfg_setup ( stepper15_cfg_t *cfg ) {
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER15_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = STEPPER15_DRV_SEL_SPI;
}

void stepper15_drv_interface_selection ( stepper15_cfg_t *cfg, stepper15_drv_t drv_sel ) {
    cfg->drv_sel = drv_sel;
}

    err_t stepper15_init ( stepper15_t *ctx, stepper15_cfg_t *cfg ) {
    ctx->drv_sel = cfg->drv_sel;

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

    ctx->read_f  = stepper15_i2c_read;
    ctx->write_f = stepper15_i2c_write;
    
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    ctx->read_f  = stepper15_spi_read;
    ctx->write_f = stepper15_spi_write;

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwm, cfg->pwm );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return 0;
}

err_t stepper15_default_cfg ( stepper15_t *ctx ) {
    err_t error_flag;
    uint8_t tmp;

    stepper15_reset( ctx );
    dev_config_delay( );
    
    tmp = STEPPER15_SET_CONFIG_DEFAULT; 
    error_flag = stepper15_i2c_write( ctx, STEPPER15_REG_CONFIGURATION, &tmp, 1 );
    dev_config_delay( );
    
    tmp = STEPPER15_SET_DIRECTION_CW;
    tmp |= STEPPER15_SET_WORK_MODE_ENABLE_DEVICE;
    tmp |= STEPPER15_SET_OUT_MODE_DEVICE_OUTPUTS_ENABLE;
    error_flag |= stepper15_i2c_write( ctx, STEPPER15_REG_OUTPUT_PORT, &tmp, 1 );
    dev_config_delay( );
    
    stepper15_set_torque_dac( ctx, STEPPER15_SET_CTRL1_TRQ_62_5 );
    dev_config_delay( );
    
    tmp  = STEPPER15_SET_CTRL2_OUTPUT_ENABLE;
    tmp |= STEPPER15_SET_CTRL2_TOFF_16_us;
    tmp |= STEPPER15_SET_CTRL2_SMART_TUNE_RIPPLE_CTRL;
    stepper15_generic_write( ctx, STEPPER15_REG_CTRL_2, &tmp, 1 );
    dev_config_delay( );
    
    tmp  = STEPPER15_SET_SPI_DIR_INPUT_PIN;
    tmp |= STEPPER15_SET_SPI_STEP_INPUT_PIN;
    tmp |= STEPPER15_SET_CTRL3_SET_MICROSTEP_MODE_FULL_STEP;
    stepper15_generic_write( ctx, STEPPER15_REG_CTRL_3, &tmp, 1 );
    dev_config_delay( );
    
    tmp = STEPPER15_SET_CTRL4_UNLOCK_ALL_REG;
    stepper15_generic_write( ctx, STEPPER15_REG_CTRL_4, &tmp, 1 );
    dev_config_delay( );
    
    tmp = STEPPER15_SET_CTRL5_REPORTED_ON_FAULT;
    stepper15_generic_write( ctx, STEPPER15_REG_CTRL_5, &tmp, 1 );
    dev_config_delay( );
    
    stepper15_set_counts( ctx, 200 );
    dev_config_delay( );
    
    return error_flag;
}

err_t stepper15_generic_write ( stepper15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    return ctx->write_f( ctx, reg, data_in, len );
}

void stepper15_reset ( stepper15_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
    dev_reset_delay( );
}

void stepper15_motor_stop ( stepper15_t *ctx ) {
    digital_out_high( &ctx->pwm );
}

uint8_t stepper15_get_interrupt ( stepper15_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

err_t stepper15_make_one_step ( stepper15_t *ctx, uint8_t step_speed ) {
    err_t error_flag;
    
    if ( ( step_speed > 100 ) || ( step_speed < 1 ) ) {
        error_flag = STEPPER15_ERROR;    
    } else {
        error_flag = STEPPER15_OK ;
        digital_out_high( &ctx->pwm );
        dev_step_delay( );
        
        for ( uint8_t n_cnt = 100; n_cnt > step_speed; n_cnt-- ) {
            dev_step_delay( );
        }
    
        digital_out_low( &ctx->pwm );
        dev_step_delay( );
        
        for ( uint8_t n_cnt = 100; n_cnt > step_speed; n_cnt-- ) {
            dev_step_delay( );
        }
    }
    
    return error_flag;
}

err_t stepper15_set_direction ( stepper15_t *ctx, uint8_t direction ) {
    err_t error_flag= STEPPER15_OK;
    uint8_t data_buf[ 1 ];
    
    error_flag |= stepper15_i2c_read( ctx, STEPPER15_REG_OUTPUT_PORT, data_buf, 1 );
    
    data_buf[ 0 ] &= STEPPER15_SET_DIRECTION_BIT_MASK;
    
    if ( direction == STEPPER15_DIRECTION_COUNTERCLOCKWISE ) {
        data_buf[ 0 ] |= STEPPER15_SET_DIRECTION_CCW;    
    } else if ( direction == STEPPER15_DIRECTION_CLOCKWISE ) {
        data_buf[ 0 ] |= STEPPER15_SET_DIRECTION_CW;    
    } else {
        error_flag = STEPPER15_ERROR;    
    }
    
    error_flag |= stepper15_i2c_write( ctx, STEPPER15_REG_OUTPUT_PORT, data_buf, 1 );
    
    return error_flag;
}

err_t stepper15_set_work_mode ( stepper15_t *ctx, uint8_t work_mode ) {
    err_t error_flag= STEPPER15_OK;
    uint8_t data_buf[ 1 ];
    
    error_flag |= stepper15_i2c_read( ctx, STEPPER15_REG_OUTPUT_PORT, data_buf, 1 );
    
    data_buf[ 0 ] &= STEPPER15_SET_WORK_MODE_BIT_MASK;
    
    if ( work_mode == STEPPER15_WORK_MODE_SLEEP ) {
        data_buf[ 0 ] |= STEPPER15_SET_WORK_MODE_SLEEP;  
    } else if ( work_mode == STEPPER15_WORK_MODE_ENABLE_DEVICE ) {
        data_buf[ 0 ] |= STEPPER15_SET_WORK_MODE_ENABLE_DEVICE;  
    } else {
        error_flag = STEPPER15_ERROR;     
    }
    
    error_flag |= stepper15_i2c_write( ctx, STEPPER15_REG_OUTPUT_PORT, data_buf, 1 );
    
    return error_flag;
}

err_t stepper15_set_output_mode ( stepper15_t *ctx, uint8_t output_mode ) {
    err_t error_flag= STEPPER15_OK;
    uint8_t data_buf[ 1 ];
    
    error_flag |= stepper15_i2c_read( ctx, STEPPER15_REG_OUTPUT_PORT, data_buf, 1 );
    
    data_buf[ 0 ] &= STEPPER15_SET_OUT_MODE_BIT_MASK;
    
    if ( output_mode == STEPPER15_OUTPUT_MODE_OUTPUTS_DISABLE ) {
        data_buf[ 0 ] |= STEPPER15_SET_OUT_MODE_DEVICE_OUTPUTS_DISABLE;  
    } else if ( output_mode == STEPPER15_OUTPUT_MODE_OUTPUTS_ENABLE ) {
        data_buf[ 0 ] |= STEPPER15_SET_OUT_MODE_DEVICE_OUTPUTS_ENABLE;
    } else {
        error_flag = STEPPER15_ERROR;     
    }
    
    error_flag |= stepper15_i2c_write( ctx, STEPPER15_REG_OUTPUT_PORT, data_buf, 1 );
    
    return error_flag;
}

err_t stepper15_set_torque_dac ( stepper15_t *ctx, uint8_t trq_data ) {
    err_t error_flag= STEPPER15_OK;
    
    trq_data &= STEPPER15_CTRL1_TRQ_DAC_MASK;
    error_flag |= stepper15_generic_write( ctx, STEPPER15_REG_CTRL_1, &trq_data, 1 );
    
    return error_flag;
}

err_t stepper15_set_counts ( stepper15_t *ctx, uint8_t counts ) {
    err_t error_flag= STEPPER15_OK;
    
    error_flag |= stepper15_generic_write( ctx, STEPPER15_REG_CTRL_6, &counts, 1 );
    
    return error_flag;
}

uint8_t stepper15_get_fault_condition ( stepper15_t *ctx ) {
    uint8_t fault_condition;
    
    stepper15_i2c_read( ctx, STEPPER15_REG_INPUT_PORT, &fault_condition, 1 );
    
    fault_condition >>= 3;
    fault_condition &= STEPPER15_FAULT_CONDITION_BIT_MASK;
    
    return fault_condition;
}

err_t stepper15_step_by_angle ( stepper15_t *ctx, uint8_t step_speed, float angle, uint16_t step_360 ) {
    err_t error_flag = STEPPER15_OK;
    float step_angle;
    uint16_t make_step;
    
    step_angle = 360;
    step_angle /= step_360;
    
    make_step = ( uint16_t ) ( angle / step_angle );
    
    for ( uint16_t n_cnt = 0; n_cnt < make_step; n_cnt++ ) {
        error_flag |= stepper15_make_one_step ( ctx, step_speed );
        dev_step_delay( );
    }
    
    return error_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_100ms( );
}

static void dev_config_delay ( void ) {
    Delay_10ms( );
}

static void dev_step_delay ( void ) {
    Delay_1ms( );
}

static err_t stepper15_i2c_write ( stepper15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t stepper15_i2c_read ( stepper15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t stepper15_spi_write ( stepper15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t stepper15_spi_read ( stepper15_t *ctx, uint8_t reg, uint8_t *data_out ) {
    uint8_t tx_data;
    err_t error_flag;
    
    tx_data = reg;
    tx_data <<= 1;
    tx_data |= SPI_READ_BIT_MASK; 
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, tx_data );
    spi_master_read( &ctx->spi, data_out, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}


// ------------------------------------------------------------------------ END
