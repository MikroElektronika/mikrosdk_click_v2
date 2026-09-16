/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file brushless29.c
 * @brief Brushless 29 Click Driver.
 */

#include "brushless29.h"

/**
 * @brief Brushless 29 serial frame settings.
 * @details Specified dummy data, frame sizes, and data positions used by the
 * TC78B043 serial interface.
 */
#define DUMMY                       0x00
#define STATUS_FRAME_SIZE           2
#define REGISTER_FRAME_SIZE         4
#define STATUS_DATA_INDEX           1
#define REGISTER_DATA_MSB_INDEX     2
#define REGISTER_DATA_LSB_INDEX     3
#define READY_TIMEOUT_COUNT         100
#define USER_ID_TEST_MASK           0xFFFF
#define DEFAULT_CFG_REG_COUNT       6

void brushless29_cfg_setup ( brushless29_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->fg_pin = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->vsp = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BRUSHLESS29_DEVICE_ADDRESS_0;

    cfg->dev_pwm_freq = BRUSHLESS29_VSP_PWM_FREQ;
    cfg->speed_mode = BRUSHLESS29_SPEED_MODE;
}

err_t brushless29_init ( brushless29_t *ctx, brushless29_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->vsp;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->fg_pin, cfg->fg_pin );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    ctx->speed_mode = cfg->speed_mode;
    ctx->pwm_active = 0;

    return BRUSHLESS29_OK;
}

err_t brushless29_default_cfg ( brushless29_t *ctx ) 
{
    err_t error_flag = BRUSHLESS29_OK;
    uint8_t cfg_reg[ DEFAULT_CFG_REG_COUNT ] =
    {
        BRUSHLESS29_REG_START_STOP_DUTY,
        BRUSHLESS29_REG_PWM_MAX_DUTY,
        BRUSHLESS29_REG_START_OUT_DUTY,
        BRUSHLESS29_REG_DUTY_SLOPE,
        BRUSHLESS29_REG_DUTY_CHANGE,
        BRUSHLESS29_REG_SPEED_CTRL
    };
    uint16_t cfg_data[ DEFAULT_CFG_REG_COUNT ] =
    {
        BRUSHLESS29_CFG_START_STOP_DUTY,
        BRUSHLESS29_CFG_PWM_MAX_DUTY,
        BRUSHLESS29_CFG_START_OUT_DUTY,
        BRUSHLESS29_CFG_DUTY_SLOPE,
        BRUSHLESS29_CFG_DUTY_CHANGE,
        BRUSHLESS29_CFG_SPEED_CTRL
    };
    uint8_t cfg_cnt = 0;
    uint8_t speed_mode = ctx->speed_mode;
    uint16_t reg_check = 0;
    
    // Configure port expander and gpio pins default state
    brushless29_reset_exp ( ctx );
    error_flag |= brushless29_write_exp_reg ( ctx, BRUSHLESS29_EXP_REG_CONFIG, 
                                              BRUSHLESS29_EXP_DEFAULT_CONFIG );
    error_flag |= brushless29_disable_output ( ctx );
    error_flag |= brushless29_set_direction ( ctx, BRUSHLESS29_DIR_CW );
    error_flag |= brushless29_set_res_pin ( ctx, BRUSHLESS29_PIN_STATE_HIGH );
    error_flag |= brushless29_set_sel_pin ( ctx, BRUSHLESS29_PIN_STATE_HIGH );
    error_flag |= brushless29_set_duty_cycle ( ctx, BRUSHLESS29_VSP_DUTY_MIN );
    Delay_100ms ( );

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_check_com( ctx );
    }

    // Configure and read back the volatile motor-control register profile.
    while ( ( BRUSHLESS29_OK == error_flag ) &&
            ( cfg_cnt < DEFAULT_CFG_REG_COUNT ) )
    {
        error_flag = brushless29_write_reg( ctx, cfg_reg[ cfg_cnt ], cfg_data[ cfg_cnt ] );

        if ( BRUSHLESS29_OK == error_flag )
        {
            error_flag = brushless29_read_reg( ctx, cfg_reg[ cfg_cnt ], &reg_check );
        }

        if ( ( BRUSHLESS29_OK == error_flag ) &&
             ( cfg_data[ cfg_cnt ] != reg_check ) )
        {
            error_flag = BRUSHLESS29_ERROR;
        }

        cfg_cnt++;
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_set_speed( ctx, BRUSHLESS29_SPEED_MIN );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        // PWM mode exits serial mode so VSP, RES, and FG regain pin control.
        error_flag = brushless29_set_speed_mode( ctx, speed_mode );
    }

    return error_flag;
}

err_t brushless29_write_reg ( brushless29_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t tx_buf[ REGISTER_FRAME_SIZE ] = { 0 };
    uint8_t rx_buf[ REGISTER_FRAME_SIZE ] = { 0 };
    err_t error_flag = BRUSHLESS29_OK;

    tx_buf[ 0 ] = BRUSHLESS29_CMD_REG_WRITE;
    tx_buf[ 1 ] = reg;
    tx_buf[ REGISTER_DATA_MSB_INDEX ] = ( uint8_t ) ( data_in >> 8 );
    tx_buf[ REGISTER_DATA_LSB_INDEX ] = ( uint8_t ) data_in;

    error_flag = brushless29_wait_ready( ctx );

    if ( BRUSHLESS29_OK == error_flag )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_transfer( &ctx->spi, tx_buf, rx_buf, REGISTER_FRAME_SIZE );
        spi_master_deselect_device( ctx->chip_select );
        Delay_1ms( );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_wait_ready( ctx );
    }

    return error_flag;
}

err_t brushless29_read_reg ( brushless29_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t tx_buf[ REGISTER_FRAME_SIZE ] = { 0 };
    uint8_t rx_buf[ REGISTER_FRAME_SIZE ] = { 0 };
    err_t error_flag = BRUSHLESS29_OK;

    tx_buf[ 0 ] = BRUSHLESS29_CMD_REG_READ;
    tx_buf[ 1 ] = reg;
    error_flag = brushless29_wait_ready( ctx );

    if ( BRUSHLESS29_OK == error_flag )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_transfer( &ctx->spi, tx_buf, rx_buf, REGISTER_FRAME_SIZE );
        spi_master_deselect_device( ctx->chip_select );
        Delay_1ms( );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) rx_buf[ REGISTER_DATA_MSB_INDEX ] << 8 ) |
                                   rx_buf[ REGISTER_DATA_LSB_INDEX ];
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_wait_ready( ctx );
    }

    return error_flag;
}

err_t brushless29_write_exp_reg ( brushless29_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t brushless29_read_exp_reg ( brushless29_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t brushless29_check_com ( brushless29_t *ctx )
{
    uint8_t restore_flag = 0;
    uint16_t user_id = 0;
    uint16_t test_id = 0;
    uint16_t reg_check = 0;
    err_t error_flag = BRUSHLESS29_OK;
    err_t restore_error = BRUSHLESS29_OK;

    error_flag = brushless29_set_serial_mode( ctx, BRUSHLESS29_SR_SERIAL_MODE );

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_wait_ready( ctx );
    }

    // Verify normal register access without changing the stored NVM contents.
    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_read_reg( ctx, BRUSHLESS29_REG_USER_ID, &user_id );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        test_id = user_id ^ USER_ID_TEST_MASK;
        restore_flag = 1;
        error_flag = brushless29_write_reg( ctx, BRUSHLESS29_REG_USER_ID, test_id );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_read_reg( ctx, BRUSHLESS29_REG_USER_ID, &reg_check );

        if ( ( BRUSHLESS29_OK == error_flag ) && ( test_id != reg_check ) )
        {
            error_flag = BRUSHLESS29_ERROR;
        }
    }

    // Always restore USERID after attempting the reversible register test.
    if ( 0 != restore_flag )
    {
        restore_error = brushless29_write_reg( ctx, BRUSHLESS29_REG_USER_ID, user_id );

        if ( BRUSHLESS29_OK == restore_error )
        {
            restore_error = brushless29_read_reg( ctx, BRUSHLESS29_REG_USER_ID, &reg_check );

            if ( ( BRUSHLESS29_OK == restore_error ) &&
                 ( user_id != reg_check ) )
            {
                restore_error = BRUSHLESS29_ERROR;
            }
        }

        if ( BRUSHLESS29_ERROR == restore_error )
        {
            error_flag = BRUSHLESS29_ERROR;
        }
    }

    return error_flag;
}

err_t brushless29_get_res_pin ( brushless29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    *state = ( reg_data & BRUSHLESS29_EXP_PIN_RES ) >> 0;
    return BRUSHLESS29_OK;
}

err_t brushless29_set_res_pin ( brushless29_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > BRUSHLESS29_PIN_STATE_HIGH )
    {
        return BRUSHLESS29_ERROR;
    }
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    if ( ( state << 0 ) == ( reg_data & BRUSHLESS29_EXP_PIN_RES ) )
    {
        return BRUSHLESS29_OK;
    }
    reg_data &= ~BRUSHLESS29_EXP_PIN_RES;
    reg_data |= ( state << 0 );
    return brushless29_write_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, reg_data );
}

err_t brushless29_get_sel_pin ( brushless29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    *state = ( reg_data & BRUSHLESS29_EXP_PIN_SEL ) >> 1;
    return BRUSHLESS29_OK;
}

err_t brushless29_set_sel_pin ( brushless29_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > BRUSHLESS29_PIN_STATE_HIGH )
    {
        return BRUSHLESS29_ERROR;
    }
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    if ( ( state << 1 ) == ( reg_data & BRUSHLESS29_EXP_PIN_SEL ) )
    {
        return BRUSHLESS29_OK;
    }
    reg_data &= ~BRUSHLESS29_EXP_PIN_SEL;
    reg_data |= ( state << 1 );
    return brushless29_write_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, reg_data );
}

err_t brushless29_get_fault_pin ( brushless29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_INPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    *state = ( reg_data & BRUSHLESS29_EXP_PIN_FAULT ) >> 2;
    return BRUSHLESS29_OK;
}

err_t brushless29_get_dir_pin ( brushless29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    *state = ( reg_data & BRUSHLESS29_EXP_PIN_DIR ) >> 3;
    return BRUSHLESS29_OK;
}

err_t brushless29_set_dir_pin ( brushless29_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > BRUSHLESS29_PIN_STATE_HIGH )
    {
        return BRUSHLESS29_ERROR;
    }
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    if ( ( state << 3 ) == ( reg_data & BRUSHLESS29_EXP_PIN_DIR ) )
    {
        return BRUSHLESS29_OK;
    }
    reg_data &= ~BRUSHLESS29_EXP_PIN_DIR;
    reg_data |= ( state << 3 );
    return brushless29_write_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, reg_data );
}

err_t brushless29_get_pg_pin ( brushless29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_INPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    *state = ( reg_data & BRUSHLESS29_EXP_PIN_PG ) >> 6;
    return BRUSHLESS29_OK;
}

err_t brushless29_get_en_pin ( brushless29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    *state = ( reg_data & BRUSHLESS29_EXP_PIN_EN ) >> 7;
    return BRUSHLESS29_OK;
}

err_t brushless29_set_en_pin ( brushless29_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > BRUSHLESS29_PIN_STATE_HIGH )
    {
        return BRUSHLESS29_ERROR;
    }
    if ( BRUSHLESS29_ERROR == brushless29_read_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, &reg_data ) )
    {
        return BRUSHLESS29_ERROR;
    }
    if ( ( state << 7 ) == ( reg_data & BRUSHLESS29_EXP_PIN_EN ) )
    {
        return BRUSHLESS29_OK;
    }
    reg_data &= ~BRUSHLESS29_EXP_PIN_EN;
    reg_data |= ( state << 7 );
    return brushless29_write_exp_reg ( ctx, BRUSHLESS29_EXP_REG_OUTPUT, reg_data );
}

err_t brushless29_enable_output ( brushless29_t *ctx )
{
    return brushless29_set_en_pin ( ctx, BRUSHLESS29_PIN_STATE_HIGH );
}

err_t brushless29_disable_output ( brushless29_t *ctx )
{
    return brushless29_set_en_pin ( ctx, BRUSHLESS29_PIN_STATE_LOW );
}

err_t brushless29_set_direction ( brushless29_t *ctx, uint8_t dir )
{
    return brushless29_set_dir_pin ( ctx, dir );
}

err_t brushless29_switch_direction ( brushless29_t *ctx )
{
    err_t error_flag = BRUSHLESS29_OK;
    uint8_t state = 0;
    error_flag = brushless29_get_dir_pin ( ctx, &state );
    if ( BRUSHLESS29_OK == error_flag )
    {
        state ^= BRUSHLESS29_PIN_STATE_HIGH;
        error_flag = brushless29_set_dir_pin ( ctx, state );
    }
    return error_flag;
}

void brushless29_reset_exp ( brushless29_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void brushless29_set_rst_pin ( brushless29_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t brushless29_get_int_pin ( brushless29_t *ctx )
{
    return !!digital_in_read ( &ctx->int_pin );
}

err_t brushless29_set_duty_cycle ( brushless29_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless29_pwm_start ( brushless29_t *ctx )
{
    err_t error_flag = BRUSHLESS29_OK;

    error_flag = brushless29_set_sel_pin( ctx, BRUSHLESS29_PIN_STATE_HIGH );

    if ( BRUSHLESS29_OK == error_flag )
    {
        spi_master_deselect_device( ctx->chip_select );
        error_flag = brushless29_set_serial_mode( ctx, BRUSHLESS29_SR_NORMAL_MODE );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = pwm_start( &ctx->pwm );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        ctx->pwm_active = 1;
    }

    return error_flag;
}

err_t brushless29_pwm_stop ( brushless29_t *ctx )
{
    err_t error_flag = pwm_stop( &ctx->pwm );

    if ( BRUSHLESS29_OK == error_flag )
    {
        ctx->pwm_active = 0;
    }

    return error_flag;
}

err_t brushless29_read_status ( brushless29_t *ctx, uint8_t *status )
{
    uint8_t tx_buf[ STATUS_FRAME_SIZE ] = { BRUSHLESS29_CMD_SR_READ, DUMMY };
    uint8_t rx_buf[ STATUS_FRAME_SIZE ] = { 0 };
    err_t error_flag = BRUSHLESS29_OK;

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_transfer( &ctx->spi, tx_buf, rx_buf, STATUS_FRAME_SIZE );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms( );

    if ( BRUSHLESS29_OK == error_flag )
    {
        *status = rx_buf[ STATUS_DATA_INDEX ];
    }

    return error_flag;
}

err_t brushless29_set_serial_mode ( brushless29_t *ctx, uint8_t mode )
{
    uint8_t tx_buf[ STATUS_FRAME_SIZE ] =
    {
        BRUSHLESS29_CMD_SR_WRITE,
        DUMMY
    };
    uint8_t rx_buf[ STATUS_FRAME_SIZE ] = { 0 };
    uint8_t status = 0;
    err_t error_flag = BRUSHLESS29_OK;

    if ( ( BRUSHLESS29_SR_NORMAL_MODE != mode ) &&
         ( BRUSHLESS29_SR_SERIAL_MODE != mode ) )
    {
        error_flag = BRUSHLESS29_ERROR;
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_read_status( ctx, &status );
    }

    if ( ( BRUSHLESS29_OK == error_flag ) &&
         ( status & ( uint8_t ) ~BRUSHLESS29_SR_VALID_MASK ) )
    {
        error_flag = BRUSHLESS29_ERROR;
    }

    if ( ( BRUSHLESS29_OK == error_flag ) &&
         ( mode != ( status & BRUSHLESS29_SR_ENB_MASK ) ) )
    {
        tx_buf[ STATUS_DATA_INDEX ] = mode;
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_transfer( &ctx->spi, tx_buf, rx_buf, STATUS_FRAME_SIZE );
        spi_master_deselect_device( ctx->chip_select );
        Delay_1ms( );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_read_status( ctx, &status );
    }

    if ( ( BRUSHLESS29_OK == error_flag ) &&
         ( mode != ( status & BRUSHLESS29_SR_ENB_MASK ) ) )
    {
        error_flag = BRUSHLESS29_ERROR;
    }

    return error_flag;
}

err_t brushless29_wait_ready ( brushless29_t *ctx )
{
    uint8_t status = 0;
    uint8_t ready_flag = 0;
    uint16_t timeout_cnt = 0;
    err_t error_flag = BRUSHLESS29_OK;

    while ( ( READY_TIMEOUT_COUNT > timeout_cnt ) &&
            ( 0 == ready_flag ) &&
            ( BRUSHLESS29_OK == error_flag ) )
    {
        error_flag = brushless29_read_status( ctx, &status );

        if ( BRUSHLESS29_OK == error_flag )
        {
            if ( ( status & ( uint8_t ) ~BRUSHLESS29_SR_VALID_MASK ) ||
                 ( 0 == ( status & BRUSHLESS29_SR_ENB_MASK ) ) )
            {
                error_flag = BRUSHLESS29_ERROR;
            }
            else if ( 0 == ( status & BRUSHLESS29_SR_BUSY_MASK ) )
            {
                ready_flag = 1;
            }
            else
            {
                Delay_1ms( );
                timeout_cnt++;
            }
        }
    }

    if ( 0 == ready_flag )
    {
        error_flag = BRUSHLESS29_ERROR;
    }

    return error_flag;
}

err_t brushless29_set_speed ( brushless29_t *ctx, uint16_t speed )
{
    err_t error_flag = BRUSHLESS29_OK;
    uint8_t tx_buf[ REGISTER_FRAME_SIZE ] = { 0 };
    uint8_t rx_buf[ REGISTER_FRAME_SIZE ] = { 0 };
    uint16_t reg_data = 0;

    if ( speed > BRUSHLESS29_SPEED_MAX )
    {
        speed = BRUSHLESS29_SPEED_MAX;
    }

    reg_data = ( uint16_t ) ( speed << BRUSHLESS29_SPEED_SHIFT );
    reg_data &= BRUSHLESS29_SPEED_MASK;

    tx_buf[ 0 ] = BRUSHLESS29_CMD_REG_WRITE;
    tx_buf[ 1 ] = BRUSHLESS29_REG_SPEED_COMMAND;
    tx_buf[ REGISTER_DATA_MSB_INDEX ] = ( uint8_t ) ( reg_data >> 8 );
    tx_buf[ REGISTER_DATA_LSB_INDEX ] = ( uint8_t ) reg_data;

    // Serial mode remains enabled, so register 13 accepts a continued write.
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_transfer( &ctx->spi, tx_buf, rx_buf, REGISTER_FRAME_SIZE );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms( );
    return error_flag;
}

err_t brushless29_set_speed_mode ( brushless29_t *ctx, uint8_t mode )
{
    uint16_t reg_mode = BRUSHLESS29_TRQ_SEL_SPI;
    uint16_t reg_data = 0;
    uint16_t reg_check = 0;
    err_t error_flag = BRUSHLESS29_OK;

    if ( ( BRUSHLESS29_SPEED_MODE_PWM != mode ) && ( BRUSHLESS29_SPEED_MODE_SPI != mode ) )
    {
        error_flag = BRUSHLESS29_ERROR;
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_set_duty_cycle( ctx, BRUSHLESS29_VSP_DUTY_MIN );
    }

    if ( ( BRUSHLESS29_OK == error_flag ) && ctx->pwm_active )
    {
        error_flag = brushless29_pwm_stop( ctx );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_set_serial_mode( ctx, BRUSHLESS29_SR_SERIAL_MODE );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_set_speed( ctx, BRUSHLESS29_SPEED_MIN );
    }

    if ( BRUSHLESS29_SPEED_MODE_PWM == mode )
    {
        reg_mode = BRUSHLESS29_TRQ_SEL_PWM_LOW;
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_read_reg( ctx, BRUSHLESS29_REG_SPEED_CTRL, &reg_data );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        reg_data &= ( uint16_t ) ~BRUSHLESS29_TRQ_SEL_MASK;
        reg_data |= reg_mode;
        error_flag = brushless29_write_reg( ctx, BRUSHLESS29_REG_SPEED_CTRL, reg_data );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_read_reg( ctx, BRUSHLESS29_REG_SPEED_CTRL, &reg_check );
    }

    if ( ( BRUSHLESS29_OK == error_flag ) && ( reg_data != reg_check ) )
    {
        error_flag = BRUSHLESS29_ERROR;
    }

    if ( ( BRUSHLESS29_OK == error_flag ) && ( BRUSHLESS29_SPEED_MODE_PWM == mode ) )
    {
        // Restore VSP, RES, and FG to their motor-control functions.
        error_flag = brushless29_set_serial_mode( ctx, BRUSHLESS29_SR_NORMAL_MODE );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        ctx->speed_mode = mode;
    }

    return error_flag;
}

err_t brushless29_run_motor ( brushless29_t *ctx, uint8_t direction, uint16_t speed )
{
    float duty_cycle = BRUSHLESS29_VSP_DUTY_MIN;
    err_t error_flag = BRUSHLESS29_OK;

    if ( speed > BRUSHLESS29_SPEED_MAX )
    {
        speed = BRUSHLESS29_SPEED_MAX;
    }

    error_flag = brushless29_set_direction( ctx, direction );

    if ( BRUSHLESS29_OK == error_flag )
    {
        if ( BRUSHLESS29_SPEED_MODE_PWM == ctx->speed_mode )
        {
            duty_cycle = ( float ) speed / ( float ) BRUSHLESS29_SPEED_MAX;
            error_flag = brushless29_set_duty_cycle( ctx, duty_cycle );

            if ( ( BRUSHLESS29_OK == error_flag ) &&
                 ( BRUSHLESS29_SPEED_MIN == speed ) &&
                 ( 0 != ctx->pwm_active ) )
            {
                error_flag = brushless29_pwm_stop( ctx );
            }
            else if ( ( BRUSHLESS29_OK == error_flag ) &&
                      ( BRUSHLESS29_SPEED_MIN != speed ) &&
                      ( 0 == ctx->pwm_active ) )
            {
                // Start the PWM channel only after a nonzero duty is loaded.
                error_flag = brushless29_pwm_start( ctx );
            }
        }
        else
        {
            error_flag = brushless29_set_speed( ctx, speed );
        }
    }

    // Enable the gate driver while the controller outputs are held inactive.
    if ( BRUSHLESS29_OK == error_flag )
    {
        error_flag = brushless29_enable_output( ctx );
    }

    if ( BRUSHLESS29_OK == error_flag )
    {
        Delay_1ms( );
        error_flag = brushless29_set_res_pin( ctx, BRUSHLESS29_PIN_STATE_LOW );
    }

    if ( BRUSHLESS29_OK != error_flag )
    {
        brushless29_set_duty_cycle( ctx, BRUSHLESS29_VSP_DUTY_MIN );
        brushless29_set_res_pin( ctx, BRUSHLESS29_PIN_STATE_HIGH );
        brushless29_disable_output( ctx );

        if ( ctx->pwm_active )
        {
            brushless29_pwm_stop( ctx );
        }
    }

    return error_flag;
}

err_t brushless29_stop_motor ( brushless29_t *ctx )
{
    err_t error_flag = BRUSHLESS29_OK;

    // Attempt every shutdown step even if an earlier hardware access fails.
    error_flag |= brushless29_set_duty_cycle( ctx, BRUSHLESS29_VSP_DUTY_MIN );
    error_flag |= brushless29_set_res_pin( ctx, BRUSHLESS29_PIN_STATE_HIGH );

    if ( BRUSHLESS29_SPEED_MODE_SPI == ctx->speed_mode )
    {
        error_flag |= brushless29_set_speed( ctx, BRUSHLESS29_SPEED_MIN );
    }

    error_flag |= brushless29_disable_output( ctx );

    if ( ctx->pwm_active )
    {
        error_flag |= brushless29_pwm_stop( ctx );
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
