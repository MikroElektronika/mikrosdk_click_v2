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
 * @file brushless27.c
 * @brief Brushless 27 Click Driver.
 */

#include "brushless27.h"

void brushless27_cfg_setup ( brushless27_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sen = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = BRUSHLESS27_DEVICE_ADDRESS_A1A0_00;
}

err_t brushless27_init ( brushless27_t *ctx, brushless27_cfg_t *cfg ) 
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

    digital_in_init( &ctx->sen, cfg->sen );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t brushless27_default_cfg ( brushless27_t *ctx ) 
{
    err_t error_flag = BRUSHLESS27_OK;
    
    brushless27_reset_port_exp( ctx );
    
    error_flag |= brushless27_write_reg( ctx, BRUSHLESS27_REG_CONFIG, BRUSHLESS27_FLT_PIN );

    return error_flag;
}

err_t brushless27_generic_write ( brushless27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t brushless27_generic_read ( brushless27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t brushless27_get_sen_pin ( brushless27_t *ctx )
{
    return digital_in_read( &ctx->sen );
}

uint8_t brushless27_get_int_pin ( brushless27_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void brushless27_reset_port_exp ( brushless27_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

err_t brushless27_get_flt_pin ( brushless27_t *ctx )
{
    uint8_t tmp_data = 0;
    err_t error_flag = BRUSHLESS27_OK;
    
    error_flag = brushless27_read_reg ( ctx, BRUSHLESS27_REG_INPUT_PORT, &tmp_data );
    if ( tmp_data & BRUSHLESS27_FLT_PIN )
    {
        error_flag = BRUSHLESS27_ERROR;
    }
    
    return error_flag;
}

err_t brushless27_write_reg ( brushless27_t *ctx, uint8_t reg, uint8_t data_in )
{
    return brushless27_generic_write( ctx, reg, &data_in, 1 );
}

err_t brushless27_read_reg ( brushless27_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return brushless27_generic_read( ctx, reg, data_out, 1 );
}

err_t brushless27_set_pins ( brushless27_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in, data_out;
    err_t error_flag = brushless27_read_reg( ctx, BRUSHLESS27_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        error_flag |= brushless27_write_reg( ctx, BRUSHLESS27_REG_OUTPUT_PORT, data_in );
    }
    return error_flag;
}

err_t brushless27_set_trap_com_state ( brushless27_t *ctx, uint8_t state )
{
    uint8_t set_mask, clr_mask;
    switch ( state )
    {
        case BRUSHLESS27_TR_COM_STATE_COAST:
        {
            set_mask = BRUSHLESS27_NONE_PIN; 
            clr_mask = BRUSHLESS27_UH_PIN | BRUSHLESS27_VH_PIN | BRUSHLESS27_WH_PIN; 
            break;
        }
        
        case BRUSHLESS27_TR_COM_STATE_1:
        {
            set_mask = BRUSHLESS27_VH_PIN | BRUSHLESS27_VL_PIN | BRUSHLESS27_WH_PIN; 
            clr_mask = BRUSHLESS27_UH_PIN | BRUSHLESS27_WL_PIN; 
            break;
        }
        
        case BRUSHLESS27_TR_COM_STATE_2:
        {
            set_mask = BRUSHLESS27_UH_PIN | BRUSHLESS27_UL_PIN | BRUSHLESS27_WH_PIN;
            clr_mask = BRUSHLESS27_VH_PIN | BRUSHLESS27_WL_PIN;
            break;
        }
        
        case BRUSHLESS27_TR_COM_STATE_3:
        {
            set_mask = BRUSHLESS27_UH_PIN | BRUSHLESS27_UL_PIN | BRUSHLESS27_VH_PIN;
            clr_mask = BRUSHLESS27_VL_PIN | BRUSHLESS27_WH_PIN; 
            break;
        }
        
        case BRUSHLESS27_TR_COM_STATE_4:
        {
            set_mask = BRUSHLESS27_VH_PIN | BRUSHLESS27_WH_PIN | BRUSHLESS27_WL_PIN;
            clr_mask = BRUSHLESS27_UH_PIN | BRUSHLESS27_VL_PIN;
            break;
        }
        
        case BRUSHLESS27_TR_COM_STATE_5:
        {
            set_mask = BRUSHLESS27_UH_PIN | BRUSHLESS27_WH_PIN | BRUSHLESS27_WL_PIN;
            clr_mask = BRUSHLESS27_UL_PIN | BRUSHLESS27_VH_PIN;
            break;
        }

        case BRUSHLESS27_TR_COM_STATE_6:
        {
            set_mask = BRUSHLESS27_UH_PIN | BRUSHLESS27_VH_PIN | BRUSHLESS27_VL_PIN;
            clr_mask = BRUSHLESS27_UL_PIN | BRUSHLESS27_WH_PIN;
            break;
        }
        
        case BRUSHLESS27_TR_COM_STATE_BRAKE:
        {
            set_mask = BRUSHLESS27_UL_PIN | BRUSHLESS27_VL_PIN | BRUSHLESS27_WL_PIN;
            clr_mask = BRUSHLESS27_UH_PIN | BRUSHLESS27_VH_PIN | BRUSHLESS27_WH_PIN;
            break;
        }
        
        default:
        {
            return BRUSHLESS27_ERROR;
        }
    }
    
    return brushless27_set_pins ( ctx, set_mask, clr_mask );
}

err_t brushless27_toggle_pin ( brushless27_t *ctx, uint8_t pin_mask, uint8_t speed )
{
    err_t error_flag = BRUSHLESS27_OK;
    for ( uint16_t cnt = 0; cnt < BRUSHLESS27_NUM_PIN_TOGGLE; cnt++ )
    {
        int16_t speed_cnt = BRUSHLESS27_SPEED_MAX;
        
        error_flag |= brushless27_set_pins ( ctx, pin_mask, BRUSHLESS27_NONE_PIN );
        error_flag |= brushless27_set_pins ( ctx, BRUSHLESS27_NONE_PIN, pin_mask );
        
        while ( speed_cnt-- >= speed )
        {
            Delay_10us ( );
        }
    }
    return error_flag;
}

err_t brushless27_perform_com_seq ( brushless27_t *ctx, uint8_t dir, uint8_t speed )
{
    err_t error_flag = BRUSHLESS27_OK;
    if ( ( speed > BRUSHLESS27_SPEED_MAX ) || ( ( BRUSHLESS27_DIR_CW != dir ) && ( BRUSHLESS27_DIR_CCW != dir ) ) )
    {
        return BRUSHLESS27_ERROR;
    }
    
    if ( BRUSHLESS27_DIR_CW == dir )
    {
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_6 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_VL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_1 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_VL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_2 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_UL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_3 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_UL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_4 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_WL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_5 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_WL_PIN, speed );
    }
    else
    {        
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_3 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_UL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_2 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_UL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_1 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_VL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_6 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_VL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_5 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_WL_PIN, speed );
        error_flag |= brushless27_set_trap_com_state ( ctx, BRUSHLESS27_TR_COM_STATE_4 );
        error_flag |= brushless27_toggle_pin ( ctx, BRUSHLESS27_WL_PIN, speed );
    }
    
    return error_flag;
}

err_t brushless27_drive_motor ( brushless27_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms )
{
    err_t error_flag = BRUSHLESS27_OK;
    float aprox_sequence_time = BRUSHLESS27_COM_SEQ_DURATION_FOR_SPEED_MAX + 
                                ( BRUSHLESS27_SPEED_MAX - speed ) * BRUSHLESS27_COM_SEQ_DURATION_SPEED_STEP;
    int32_t num_seq = ( int32_t ) ( time_ms / aprox_sequence_time + BRUSHLESS27_ROUND_TO_NEAREAST_INT );
    do 
    {
        error_flag |= brushless27_perform_com_seq ( ctx, dir, speed );
    } 
    while ( ( --num_seq > 0 ) && ( BRUSHLESS27_OK == error_flag ) );
    return error_flag;
}



// ------------------------------------------------------------------------- END
