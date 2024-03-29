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
 * @file stepper19.c
 * @brief Stepper 19 Click Driver.
 */

#include "stepper19.h"


/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Stepper 19 step delay function.
 * @details This function sets the defined delay value.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void stepper19_step_delay ( stepper19_t *ctx );

void stepper19_cfg_setup ( stepper19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->stp = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER19_DEVICE_ADDRESS_0;
}

err_t stepper19_init ( stepper19_t *ctx, stepper19_cfg_t *cfg ) 
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

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->stp, cfg->stp );

    digital_in_init( &ctx->flt, cfg->flt );

    return I2C_MASTER_SUCCESS;
}

err_t stepper19_default_cfg ( stepper19_t *ctx ) 
{
    ctx->step_delay = STEPPER19_STEP_DELAY_DEF_100US;
    ctx->step_dir_mode = STEPPER19_CTRL_STEP_DIR_GPIO;
    ctx->microstep_mode = STEPPER19_FULL_STEP / STEPPER19_MSTEP_MODE_FULL;
    Delay_10ms( );

    err_t err_flag = stepper19_port_exp_write( ctx, STEPPER19_REG_CONFIG, STEPPER19_PORT_EXP_DEFAULT_CFG );
    Delay_10ms( );

    err_flag |= stepper19_set_direction( ctx, STEPPER19_DIR_CLOCKWISE );
    Delay_10ms( );

    err_flag |= stepper19_set_decay_mode( ctx, STEPPER19_DECAY_MODE_DYN );

    
    err_flag |= stepper19_set_toff( ctx, STEPPER19_TOFF_7US );
    
    stepper19_enable_device( ctx );
    Delay_10ms( );

    return err_flag;
}

err_t stepper19_generic_write ( stepper19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t stepper19_generic_read ( stepper19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t stepper19_port_exp_write ( stepper19_t *ctx, uint8_t reg, uint8_t data_in )
{
    return stepper19_generic_write( ctx, reg, &data_in, 1 );
}

err_t stepper19_port_exp_read ( stepper19_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return stepper19_generic_read( ctx, reg, data_out, 1 );
}

err_t stepper19_set_pins ( stepper19_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in = DUMMY;
    uint8_t data_out = DUMMY;
    err_t err_flag = stepper19_port_exp_read( ctx, STEPPER19_REG_OUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        err_flag |= stepper19_port_exp_write( ctx, STEPPER19_REG_OUT_PORT, data_in );
    }
    return err_flag;
}

err_t stepper19_set_microstep_mode ( stepper19_t *ctx, uint8_t ms_mode )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = stepper19_port_exp_read( ctx, STEPPER19_REG_CONFIG, &data_buf );
    data_buf &= ~( STEPPER19_PIN_M0 | STEPPER19_PIN_M1 );
    err_flag |= stepper19_port_exp_write( ctx, STEPPER19_REG_CONFIG, data_buf );
    ctx->microstep_mode = STEPPER19_FULL_STEP / STEPPER19_MSTEP_MODE_1_4;
    switch ( ms_mode )
    {
        case STEPPER19_MSTEP_MODE_FULL:
        {
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_M0, STEPPER19_PIN_STATE_LOW );
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_M1, STEPPER19_PIN_STATE_LOW );
            break;
        }
        case STEPPER19_MSTEP_MODE_HALF:
        {
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_M0, STEPPER19_PIN_STATE_LOW );
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_M1, STEPPER19_PIN_STATE_HIGH );
            break;
        }
        case STEPPER19_MSTEP_MODE_1_4:
        {
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_M0, STEPPER19_PIN_STATE_HIGH );
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_M1, STEPPER19_PIN_STATE_LOW );
            break;
        }
        case STEPPER19_MSTEP_MODE_1_8:
        {
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_M0, STEPPER19_PIN_STATE_HIGH );
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_M1, STEPPER19_PIN_STATE_HIGH );
            break;
        }
        default:
        {
            err_flag = STEPPER19_ERROR;
            break;
        }
    }
    return err_flag;
}

err_t stepper19_set_decay_mode ( stepper19_t *ctx, uint8_t decay_mode )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = stepper19_port_exp_read( ctx, STEPPER19_REG_CONFIG, &data_buf );
    data_buf &= ~( STEPPER19_PIN_DEC0 | STEPPER19_PIN_DEC1 );
    err_flag |= stepper19_port_exp_write( ctx, STEPPER19_REG_CONFIG, data_buf );
    switch ( decay_mode )
    {
        case STEPPER19_DECAY_MODE_DYN:
        {
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_DEC0, STEPPER19_PIN_STATE_LOW );
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_DEC1, STEPPER19_PIN_STATE_LOW );
            break;
        }
        case STEPPER19_DECAY_MODE_XRP:
        {
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_DEC0, STEPPER19_PIN_STATE_LOW );
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_DEC1, STEPPER19_PIN_STATE_HIGH );
            break;
        }
        case STEPPER19_DECAY_MODE_F_30:
        {
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_DEC0, STEPPER19_PIN_STATE_HIGH );
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_DEC1, STEPPER19_PIN_STATE_LOW );
            break;
        }
        case STEPPER19_DECAY_MODE_SLW:
        {
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_DEC0, STEPPER19_PIN_STATE_HIGH );
            err_flag |= stepper19_set_pins( ctx, STEPPER19_PIN_DEC1, STEPPER19_PIN_STATE_HIGH );
            break;
        }
        default:
        {
            err_flag = STEPPER19_ERROR;
            break;
        }
    }
    return err_flag;
}

err_t stepper19_set_toff ( stepper19_t *ctx, uint8_t toff )
{
    err_t err_flag = STEPPER19_ERROR;
    if ( toff <= STEPPER19_TOFF_16US )
    {
        err_flag = stepper19_set_pins( ctx, STEPPER19_PIN_TOFF, toff );
    }
    return err_flag;
}

void stepper19_enable_device ( stepper19_t *ctx )
{
    digital_out_high( &ctx->en );
}

void stepper19_disable_device ( stepper19_t *ctx )
{
    digital_out_low( &ctx->en );
}

err_t stepper19_set_direction ( stepper19_t *ctx, uint8_t dir )
{
    err_t err_flag = STEPPER19_OK;
    if ( STEPPER19_CTRL_STEP_DIR_GPIO == ctx->step_dir_mode )
    {
        digital_out_write( &ctx->dir, dir );
    }
    else 
    {
        err_flag = stepper19_set_pins( ctx, STEPPER19_PIN_DIR, dir );
    }
    return err_flag;
}

err_t stepper19_set_step ( stepper19_t *ctx, uint8_t step )
{
    err_t err_flag = STEPPER19_OK;
    if ( STEPPER19_CTRL_STEP_DIR_GPIO == ctx->step_dir_mode )
    {
        digital_out_write( &ctx->stp, step );
    }
    else 
    {
        err_flag = stepper19_set_pins( ctx, STEPPER19_PIN_STP, step );
    }
    return err_flag;
}

err_t stepper19_make_one_step ( stepper19_t *ctx, uint8_t step_speed ) 
{
    err_t err_flag = STEPPER19_OK;

    if ( ( STEPPER19_STEP_SPEED_MAX < step_speed ) || 
         ( STEPPER19_STEP_SPEED_MIN > step_speed ) ) 
    {
        err_flag = STEPPER19_ERROR;    
    } 
    else 
    {
        stepper19_enable_device( ctx );
        err_flag |= stepper19_set_step( ctx, STEPPER19_PIN_STATE_HIGH );
        stepper19_step_delay( ctx );
        
        for ( uint8_t n_cnt = STEPPER19_STEP_SPEED_MAX; n_cnt > step_speed / STEPPER19_STEP_DELAY_DEF_100US; n_cnt-- ) 
        {
            stepper19_step_delay( ctx );
        }
    
        err_flag |= stepper19_set_step( ctx, STEPPER19_PIN_STATE_LOW );
        stepper19_step_delay( ctx );
        
        for ( uint8_t n_cnt = STEPPER19_STEP_SPEED_MAX; n_cnt > step_speed / STEPPER19_STEP_DELAY_DEF_100US; n_cnt-- ) 
        {
            stepper19_step_delay( ctx );
        }
        stepper19_disable_device( ctx );
    }
    return err_flag;
}

err_t stepper19_rotate_by_angle ( stepper19_t *ctx, uint8_t step_speed, float angle, uint16_t res_360 ) 
{
    err_t err_flag = STEPPER19_OK;
    float step_angle = DUMMY;
    uint16_t make_step = DUMMY;

    step_angle = STEPPER19_ANGLE_360_DEGREES;
    step_angle /= ( float ) res_360;
    step_angle *= ctx->microstep_mode;
    make_step = ( uint16_t ) ( angle / step_angle );
    
    for ( uint16_t n_cnt = 0; n_cnt < make_step; n_cnt++ ) 
    {
        err_flag |= stepper19_make_one_step ( ctx, step_speed );
    }
    return err_flag;
}

err_t stepper19_rotate_by_step ( stepper19_t *ctx, uint8_t step_speed, uint16_t steps )
{
    err_t err_flag = STEPPER19_OK;
    for ( uint16_t step_cnt = 0; step_cnt < steps; step_cnt++ )
    {
        err_flag |= stepper19_make_one_step( ctx, step_speed );
    }
    return err_flag;
}

uint8_t stepper19_fault_indication ( stepper19_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

static void stepper19_step_delay ( stepper19_t *ctx ) 
{
    for ( uint32_t n_cnt = 0; n_cnt < ctx->step_delay; n_cnt++ )
    {
        Delay_50us( );
    }
}

// ------------------------------------------------------------------------- END
