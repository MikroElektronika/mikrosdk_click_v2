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
 * @file stepper13.c
 * @brief Stepper 13 Click Driver.
 */

#include "stepper13.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper13_speed_delay ( uint8_t speed_macro );

void stepper13_cfg_setup ( stepper13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER13_DEVICE_ADDRESS_A1A0_00;
}

err_t stepper13_init ( stepper13_t *ctx, stepper13_cfg_t *cfg ) 
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
    digital_out_init( &ctx->step, cfg->step );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t stepper13_default_cfg ( stepper13_t *ctx ) 
{
    err_t error_flag = STEPPER13_OK;
    stepper13_reset_pca ( ctx );
    // Configure FAULT pin as INPUT, others as OUTPUT
    error_flag |= stepper13_pca_write_reg ( ctx, STEPPER13_PCA9538A_REG_CONFIG, 
                                                 STEPPER13_PCA9538A_DEFAULT_CONFIG );
    error_flag |= stepper13_disable_device ( ctx );
    error_flag |= stepper13_disable_sleep ( ctx );
    error_flag |= stepper13_set_direction ( ctx, STEPPER13_DIR_CW );
    error_flag |= stepper13_set_step_mode ( ctx, STEPPER13_MODE_FULL_STEP );
    Delay_100ms ( );
    return error_flag;
}

err_t stepper13_pca_write_reg ( stepper13_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper13_pca_read_reg ( stepper13_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t stepper13_get_fault_pin ( stepper13_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_INPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    *state = ( reg_data & STEPPER13_PIN_FAULT ) >> 2;
    return STEPPER13_OK;
}

err_t stepper13_enable_device ( stepper13_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    if ( STEPPER13_PIN_ENABLE != ( reg_data & STEPPER13_PIN_ENABLE ) )
    {
        return STEPPER13_OK;
    }
    reg_data &= ( ~STEPPER13_PIN_ENABLE );
    return stepper13_pca_write_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper13_disable_device ( stepper13_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    if ( STEPPER13_PIN_ENABLE == ( reg_data & STEPPER13_PIN_ENABLE ) )
    {
        return STEPPER13_OK;
    }
    reg_data |= STEPPER13_PIN_ENABLE;
    return stepper13_pca_write_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper13_enable_sleep ( stepper13_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    if ( STEPPER13_PIN_SLEEP != ( reg_data & STEPPER13_PIN_SLEEP ) )
    {
        return STEPPER13_OK;
    }
    reg_data &= ( ~STEPPER13_PIN_SLEEP );
    return stepper13_pca_write_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper13_disable_sleep ( stepper13_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    if ( STEPPER13_PIN_SLEEP == ( reg_data & STEPPER13_PIN_SLEEP ) )
    {
        return STEPPER13_OK;
    }
    reg_data |= STEPPER13_PIN_SLEEP;
    return stepper13_pca_write_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper13_set_direction ( stepper13_t *ctx, uint8_t dir )
{
    uint8_t reg_data = 0;
    if ( dir > STEPPER13_DIR_CCW )
    {
        return STEPPER13_ERROR;
    }
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    if ( dir == ( ( reg_data & STEPPER13_PIN_DIR ) >> 3 ) )
    {
        return STEPPER13_OK;
    }
    reg_data &= ( ~STEPPER13_PIN_DIR );
    reg_data |= ( dir << 3 );
    return stepper13_pca_write_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper13_switch_direction ( stepper13_t *ctx )
{
    uint8_t reg_data = 0;
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    reg_data ^= STEPPER13_PIN_DIR;
    return stepper13_pca_write_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, reg_data );
}

void stepper13_set_rst_pin ( stepper13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void stepper13_reset_pca ( stepper13_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t stepper13_get_int_pin ( stepper13_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void stepper13_set_step_pin ( stepper13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

err_t stepper13_get_step_mode ( stepper13_t *ctx, uint8_t *mode )
{
    uint8_t reg_data = 0;
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    *mode = ( reg_data & STEPPER13_PIN_MS_MASK );
    return STEPPER13_OK;
}

err_t stepper13_set_step_mode ( stepper13_t *ctx, uint8_t mode )
{
    uint8_t reg_data = 0;
    if ( mode > STEPPER13_MODE_1_OVER_8 )
    {
        return STEPPER13_ERROR;
    }
    if ( STEPPER13_ERROR == stepper13_pca_read_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER13_ERROR;
    }
    if ( mode == ( reg_data & STEPPER13_PIN_MS_MASK ) )
    {
        return STEPPER13_OK;
    }
    reg_data &= ~STEPPER13_PIN_MS_MASK;
    reg_data |= mode;
    return stepper13_pca_write_reg ( ctx, STEPPER13_PCA9538A_REG_OUTPUT, reg_data );
}

err_t stepper13_drive_motor ( stepper13_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = STEPPER13_OK;
    error_flag |= stepper13_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper13_set_step_pin ( ctx, STEPPER13_PIN_STATE_HIGH );
        stepper13_speed_delay ( speed );
        stepper13_set_step_pin ( ctx, STEPPER13_PIN_STATE_LOW );
        stepper13_speed_delay ( speed );
    }
    error_flag |= stepper13_disable_device ( ctx );
    return error_flag;
}

static void stepper13_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER13_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER13_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER13_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER13_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER13_SPEED_VERY_FAST:
        {
            Delay_1ms( );
            break;
        }
        default:
        {
            Delay_5ms( );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
