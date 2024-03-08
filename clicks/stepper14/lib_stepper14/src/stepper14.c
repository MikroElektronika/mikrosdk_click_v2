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
 * @file stepper14.c
 * @brief Stepper 14 Click Driver.
 */

#include "stepper14.h"

/**
 * @brief Stepper 14 I/O signal table for full step resolution.
 * @details Specified I/O signal table for full step resolution, set in the following order:
 * IN1, IN2, IN3, and IN4.
 */
static uint8_t stepper14_full_step[ 4 ][ 4 ] = 
{
    { 1, 0, 0, 1 },
    { 1, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 0, 1 },
};

/**
 * @brief Stepper 14 I/O signal table for half step resolution.
 * @details Specified I/O signal table for half step resolution, set in the following order:
 * IN1, IN2, IN3, and IN4.
 */
static uint8_t stepper14_half_step[ 8 ][ 4 ] = 
{
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 1 },
};

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper14_speed_delay ( uint8_t speed_macro );

/**
 * @brief Set pins for one micro step.
 * @details This function sets IN1, IN2, IN3, and IN4 pins for a desired step.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] pins_array : Array of 4 bytes that contains IN1, IN2, IN3, and IN4 pins
 * logic state value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t stepper14_set_pins ( stepper14_t *ctx, uint8_t pins_array[ 4 ] );

void stepper14_cfg_setup ( stepper14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER14_DEVICE_ADDRESS_A1A0_00;
}

err_t stepper14_init ( stepper14_t *ctx, stepper14_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->flt, cfg->flt );

    return I2C_MASTER_SUCCESS;
}

err_t stepper14_default_cfg ( stepper14_t *ctx ) 
{
    err_t error_flag = STEPPER14_OK;
    stepper14_reset_pca ( ctx );
    error_flag |= stepper14_pca_write_reg ( ctx, STEPPER14_PCA9538A_REG_CONFIG, 
                                                 STEPPER14_PCA9538A_DEFAULT_CONFIG );
    stepper14_disable_device ( ctx );
    error_flag |= stepper14_set_in1_pin ( ctx, STEPPER14_PIN_STATE_LOW );
    error_flag |= stepper14_set_in2_pin ( ctx, STEPPER14_PIN_STATE_LOW );
    error_flag |= stepper14_set_in3_pin ( ctx, STEPPER14_PIN_STATE_LOW );
    error_flag |= stepper14_set_in4_pin ( ctx, STEPPER14_PIN_STATE_LOW );
    error_flag |= stepper14_set_trq_pin ( ctx, STEPPER14_PIN_STATE_HIGH );
    error_flag |= stepper14_set_interface_mode ( ctx, STEPPER14_INTERFACE_4_PIN );
    Delay_100ms ( );
    return error_flag;
}

err_t stepper14_pca_write_reg ( stepper14_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper14_pca_read_reg ( stepper14_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void stepper14_set_rst_pin ( stepper14_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void stepper14_reset_pca ( stepper14_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t stepper14_get_fault_pin ( stepper14_t *ctx )
{
    return digital_in_read ( &ctx->flt );
}

void stepper14_enable_device ( stepper14_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper14_disable_device ( stepper14_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t stepper14_set_in1_pin ( stepper14_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER14_PIN_STATE_HIGH )
    {
        return STEPPER14_ERROR;
    }
    if ( STEPPER14_ERROR == stepper14_pca_read_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER14_ERROR;
    }
    if ( state == ( reg_data & STEPPER14_PIN_IN1 ) )
    {
        return STEPPER14_OK;
    }
    reg_data &= ( ~STEPPER14_PIN_IN1 );
    reg_data |= state;
    return stepper14_pca_write_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper14_set_in2_pin ( stepper14_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER14_PIN_STATE_HIGH )
    {
        return STEPPER14_ERROR;
    }
    if ( STEPPER14_ERROR == stepper14_pca_read_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER14_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER14_PIN_IN2 ) >> 1 ) )
    {
        return STEPPER14_OK;
    }
    reg_data &= ( ~STEPPER14_PIN_IN2 );
    reg_data |= ( state << 1 );
    return stepper14_pca_write_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper14_set_in3_pin ( stepper14_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER14_PIN_STATE_HIGH )
    {
        return STEPPER14_ERROR;
    }
    if ( STEPPER14_ERROR == stepper14_pca_read_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER14_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER14_PIN_IN3 ) >> 3 ) )
    {
        return STEPPER14_OK;
    }
    reg_data &= ( ~STEPPER14_PIN_IN3 );
    reg_data |= ( state << 3 );
    return stepper14_pca_write_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper14_set_in4_pin ( stepper14_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER14_PIN_STATE_HIGH )
    {
        return STEPPER14_ERROR;
    }
    if ( STEPPER14_ERROR == stepper14_pca_read_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER14_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER14_PIN_IN4 ) >> 4 ) )
    {
        return STEPPER14_OK;
    }
    reg_data &= ( ~STEPPER14_PIN_IN4 );
    reg_data |= ( state << 4 );
    return stepper14_pca_write_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper14_set_mode_pin ( stepper14_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER14_PIN_STATE_HIGH )
    {
        return STEPPER14_ERROR;
    }
    if ( STEPPER14_ERROR == stepper14_pca_read_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER14_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER14_PIN_MODE ) >> 2 ) )
    {
        return STEPPER14_OK;
    }
    reg_data &= ( ~STEPPER14_PIN_MODE );
    reg_data |= ( state << 2 );
    return stepper14_pca_write_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper14_set_trq_pin ( stepper14_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER14_PIN_STATE_HIGH )
    {
        return STEPPER14_ERROR;
    }
    if ( STEPPER14_ERROR == stepper14_pca_read_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER14_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER14_PIN_TRQ ) >> 5 ) )
    {
        return STEPPER14_OK;
    }
    reg_data &= ( ~STEPPER14_PIN_TRQ );
    reg_data |= ( state << 5 );
    return stepper14_pca_write_reg ( ctx, STEPPER14_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper14_set_interface_mode ( stepper14_t *ctx, uint8_t mode )
{
    err_t error_flag = STEPPER14_OK;
    if ( STEPPER14_INTERFACE_4_PIN == mode )
    {
        ctx->pin_mode = STEPPER14_INTERFACE_4_PIN;
        error_flag |= stepper14_set_mode_pin ( ctx, STEPPER14_PIN_STATE_LOW );
    }
    else
    {
        ctx->pin_mode = STEPPER14_INTERFACE_2_PIN;
        error_flag |= stepper14_set_mode_pin ( ctx, STEPPER14_PIN_STATE_HIGH );
    }
    return error_flag;
}

void stepper14_set_step_mode ( stepper14_t *ctx, uint8_t mode )
{
    if ( STEPPER14_MODE_HALF_STEP == mode )
    {
        ctx->step_mode = STEPPER14_MODE_HALF_STEP;
    }
    else
    {
        ctx->step_mode = STEPPER14_MODE_FULL_STEP;
    }
}

void stepper14_set_direction ( stepper14_t *ctx, uint8_t dir )
{
    if ( STEPPER14_DIR_CCW == dir )
    {
        ctx->direction = STEPPER14_DIR_CCW;
    }
    else
    {
        ctx->direction = STEPPER14_DIR_CW;
    }
}

void stepper14_switch_direction ( stepper14_t *ctx )
{
    if ( STEPPER14_DIR_CCW == ctx->direction )
    {
        ctx->direction = STEPPER14_DIR_CW;
    }
    else
    {
        ctx->direction = STEPPER14_DIR_CCW;
    }
}

err_t stepper14_drive_motor ( stepper14_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = STEPPER14_OK;
    stepper14_enable_device ( ctx );
    for ( uint32_t num_steps = 0; num_steps < steps; num_steps++ )
    {
        if ( ( STEPPER14_PIN_STATE_HIGH == ctx->pin_mode ) && 
             ( STEPPER14_MODE_FULL_STEP == ctx->step_mode ) )
        {
            if ( STEPPER14_DIR_CW == ctx->direction )
            {
                error_flag |= stepper14_set_in1_pin ( ctx, stepper14_full_step[ num_steps % 4 ][ 1 ] );
                error_flag |= stepper14_set_in2_pin ( ctx, stepper14_full_step[ num_steps % 4 ][ 2 ] );
            }
            else
            {
                error_flag |= stepper14_set_in1_pin ( ctx, stepper14_full_step[ 3 - ( num_steps % 4 ) ][ 1 ] );
                error_flag |= stepper14_set_in2_pin ( ctx, stepper14_full_step[ 3 - ( num_steps % 4 ) ][ 2 ] );
            }
        }
        else if ( ( STEPPER14_PIN_STATE_LOW == ctx->pin_mode ) && 
                  ( STEPPER14_MODE_FULL_STEP == ctx->step_mode ) )
        {
            if ( STEPPER14_DIR_CW == ctx->direction )
            {
                error_flag |= stepper14_set_pins ( ctx, stepper14_full_step[ num_steps % 4 ] );
            }
            else
            {
                error_flag |= stepper14_set_pins ( ctx, stepper14_full_step[ 3 - ( num_steps % 4 ) ] );
            }
        }
        else if ( ( STEPPER14_PIN_STATE_LOW == ctx->pin_mode ) && 
                  ( STEPPER14_MODE_HALF_STEP == ctx->step_mode ) )
        {
            if ( STEPPER14_DIR_CW == ctx->direction )
            {
                error_flag |= stepper14_set_pins ( ctx, stepper14_half_step[ num_steps % 8 ] );
            }
            else
            {
                error_flag |= stepper14_set_pins ( ctx, stepper14_half_step[ 7 - ( num_steps % 8 ) ] );
            }
        }
        stepper14_speed_delay ( speed );
    }
    stepper14_disable_device ( ctx );
    return error_flag;
}

static void stepper14_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER14_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER14_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER14_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER14_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER14_SPEED_VERY_FAST:
        {
            Delay_500us( );
            break;
        }
        default:
        {
            Delay_5ms( );
            break;
        }
    }
}

static err_t stepper14_set_pins ( stepper14_t *ctx, uint8_t pins_array[ 4 ] )
{
    err_t error_flag = STEPPER14_OK;
    error_flag |= stepper14_set_in1_pin ( ctx, pins_array[ 0 ] );
    error_flag |= stepper14_set_in2_pin ( ctx, pins_array[ 1 ] );
    error_flag |= stepper14_set_in3_pin ( ctx, pins_array[ 2 ] );
    error_flag |= stepper14_set_in4_pin ( ctx, pins_array[ 3 ] );
    return error_flag;
}

// ------------------------------------------------------------------------- END
