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
 * @file brushless26.c
 * @brief Brushless 26 Click Driver.
 */

#include "brushless26.h"

void brushless26_cfg_setup ( brushless26_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = BRUSHLESS26_DEVICE_ADDRESS_A1A0_00;
}

err_t brushless26_init ( brushless26_t *ctx, brushless26_cfg_t *cfg ) 
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
    
    ctx->mode = BRUSHLESS26_MODE_6X_PWM;
    
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->flt, cfg->flt );
    
    digital_out_high( &ctx->rst );

    return I2C_MASTER_SUCCESS;
}

err_t brushless26_default_cfg ( brushless26_t *ctx ) 
{
    err_t error_flag = BRUSHLESS26_OK;
    
    brushless26_reset_port_exp( ctx );
    
    error_flag |= brushless26_write_reg( ctx, BRUSHLESS26_REG_CONFIG, BRUSHLESS26_NONE_PIN );
    
    error_flag |= brushless26_set_pins( ctx, BRUSHLESS26_SLP_PIN, BRUSHLESS26_NONE_PIN );

    return error_flag;
}

err_t brushless26_generic_write ( brushless26_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t brushless26_generic_read ( brushless26_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void brushless26_set_rst_pin ( brushless26_t *ctx, uint8_t pin_state )
{
    if ( BRUSHLESS26_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void brushless26_reset_port_exp ( brushless26_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms ( );
    digital_out_high( &ctx->rst );
    Delay_100ms ( );
}

uint8_t brushless26_get_flt_pin ( brushless26_t *ctx )
{
    return digital_in_read ( &ctx->flt );
}

err_t brushless26_write_reg ( brushless26_t *ctx, uint8_t reg, uint8_t data_in )
{
    return brushless26_generic_write( ctx, reg, &data_in, 1 );
}

err_t brushless26_read_reg ( brushless26_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return brushless26_generic_read( ctx, reg, data_out, 1 );
}

err_t brushless26_set_pins ( brushless26_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in, data_out;
    err_t error_flag = brushless26_read_reg( ctx, BRUSHLESS26_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        error_flag |= brushless26_write_reg( ctx, BRUSHLESS26_REG_OUTPUT_PORT, data_in );
    }
    return error_flag;
}

err_t brushless26_set_trap_com_state ( brushless26_t *ctx, uint8_t state )
{
    uint8_t set_mask, clr_mask;
    switch ( state )
    {
        case BRUSHLESS26_TR_COM_STATE_COAST:
        {
            if ( BRUSHLESS26_MODE_6X_PWM == ctx->mode )
            {
                set_mask = BRUSHLESS26_NONE_PIN; 
                clr_mask = BRUSHLESS26_ALL_OUTPUT_PIN; 
            }
            else
            {
                set_mask = BRUSHLESS26_NONE_PIN; 
                clr_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_SLP_PIN; 
            }
            break;
        }
        
        case BRUSHLESS26_TR_COM_STATE_1:
        {
            if ( BRUSHLESS26_MODE_6X_PWM == ctx->mode )
            {
                set_mask = BRUSHLESS26_INHB_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_SLP_PIN; 
                clr_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_INHC_PIN;
            }
            else
            {
                set_mask = BRUSHLESS26_INLB_PIN | BRUSHLESS26_INHB_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_SLP_PIN; 
                clr_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHC_PIN; 
            }
            break;
        }
        
        case BRUSHLESS26_TR_COM_STATE_2:
        {
            if ( BRUSHLESS26_MODE_6X_PWM == ctx->mode )
            {
                set_mask = BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_INHB_PIN | BRUSHLESS26_INHC_PIN;
            }
            else
            {
                set_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INLB_PIN | BRUSHLESS26_INHC_PIN;
            }
            break;
        }
        
        case BRUSHLESS26_TR_COM_STATE_3:
        {
            if ( BRUSHLESS26_MODE_6X_PWM == ctx->mode )
            {
                set_mask = BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHB_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_INHC_PIN;
            }
            else
            {
                set_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INHB_PIN | BRUSHLESS26_INLC_PIN; 
            }
            break;
        }
        
        case BRUSHLESS26_TR_COM_STATE_4:
        {
            if ( BRUSHLESS26_MODE_6X_PWM == ctx->mode )
            {
                set_mask = BRUSHLESS26_INLB_PIN | BRUSHLESS26_INHC_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHA_PIN | BRUSHLESS26_INHB_PIN | BRUSHLESS26_INLC_PIN;
            }
            else
            {
                set_mask = BRUSHLESS26_INLB_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_INHC_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHB_PIN;
            }
            break;
        }
        
        case BRUSHLESS26_TR_COM_STATE_5:
        {
            if ( BRUSHLESS26_MODE_6X_PWM == ctx->mode )
            {
                set_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHC_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_INHB_PIN;
            }
            else
            {
                set_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_INHC_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLB_PIN;
            }
            break;
        }

        case BRUSHLESS26_TR_COM_STATE_6:
        {
            if ( BRUSHLESS26_MODE_6X_PWM == ctx->mode )
            {
                set_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INHB_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_INLC_PIN | BRUSHLESS26_INHC_PIN;
            }
            else
            {
                set_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_INHB_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INHA_PIN | BRUSHLESS26_INLC_PIN;
            }
            break;
        }
        
        case BRUSHLESS26_TR_COM_STATE_BRAKE:
        {
            if ( BRUSHLESS26_MODE_6X_PWM == ctx->mode )
            {
                set_mask = BRUSHLESS26_INHA_PIN | BRUSHLESS26_INHB_PIN | BRUSHLESS26_INHC_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INLC_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_INLA_PIN; 
            }
            else
            {
                set_mask = BRUSHLESS26_INHA_PIN | BRUSHLESS26_INHB_PIN | BRUSHLESS26_INHC_PIN | BRUSHLESS26_SLP_PIN;
                clr_mask = BRUSHLESS26_INLA_PIN | BRUSHLESS26_INLB_PIN | BRUSHLESS26_INLC_PIN;
            }
            break;
        }
        
        default:
        {
            return BRUSHLESS26_ERROR;
        }
    }
    
    return brushless26_set_pins ( ctx, set_mask, clr_mask );
}

err_t brushless26_toggle_pin ( brushless26_t *ctx, uint8_t pin_mask, uint8_t speed )
{
    err_t error_flag = BRUSHLESS26_OK;
    for ( uint16_t cnt = 0; cnt < BRUSHLESS26_NUM_PIN_TOGGLE; cnt++ )
    {
        int16_t speed_cnt = 100;
        
        error_flag |= brushless26_set_pins ( ctx, pin_mask, BRUSHLESS26_NONE_PIN );
        error_flag |= brushless26_set_pins ( ctx, BRUSHLESS26_NONE_PIN, pin_mask );
        
        while ( speed_cnt-- >= speed )
        {
            Delay_10us ( );
        }
    }
    return error_flag;
}

err_t brushless26_perform_com_seq ( brushless26_t *ctx, uint8_t dir, uint8_t speed )
{
    err_t error_flag = BRUSHLESS26_OK;
    if ( ( speed > 100 ) || ( ( BRUSHLESS26_DIR_CW != dir ) && ( BRUSHLESS26_DIR_CCW != dir ) ) )
    {
        return BRUSHLESS26_ERROR;
    }
    
    if ( BRUSHLESS26_DIR_CW == dir )
    {
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_6 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHB_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_1 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHB_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_2 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHA_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_3 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHA_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_4 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHC_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_5 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHC_PIN, speed );
    }
    else
    {        
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_3 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHA_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_2 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHA_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_1 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHB_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_6 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHB_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_5 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHC_PIN, speed );
        error_flag |= brushless26_set_trap_com_state ( ctx, BRUSHLESS26_TR_COM_STATE_4 );
        error_flag |= brushless26_toggle_pin ( ctx, BRUSHLESS26_INHC_PIN, speed );
    }
    
    return error_flag;
}

err_t brushless26_drive_motor ( brushless26_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms )
{
    err_t error_flag = BRUSHLESS26_OK;
    float aprox_sequence_time = BRUSHLESS26_COM_SEQ_DURATION_FOR_SPEED_MAX + 
                                ( BRUSHLESS26_SPEED_MAX - speed ) * BRUSHLESS26_COM_SEQ_DURATION_SPEED_STEP;
    int32_t num_seq = ( int32_t ) ( time_ms / aprox_sequence_time + BRUSHLESS26_ROUND_TO_NEAREAST_INT );
    do 
    {
        error_flag |= brushless26_perform_com_seq ( ctx, dir, speed );
    } 
    while ( ( --num_seq > 0 ) && ( BRUSHLESS26_OK == error_flag ) );
    return error_flag;
}

// ------------------------------------------------------------------------- END
