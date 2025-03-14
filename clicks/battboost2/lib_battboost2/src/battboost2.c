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
 * @file battboost2.c
 * @brief BATT Boost 2 Click Driver.
 */

#include "battboost2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                  0x00

void battboost2_cfg_setup ( battboost2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->on  = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BATTBOOST2_DEVICE_ADDRESS_0;
}

err_t battboost2_init ( battboost2_t *ctx, battboost2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->on, cfg->on );

    digital_in_init( &ctx->rdy, cfg->rdy );

    return I2C_MASTER_SUCCESS;
}

err_t battboost2_default_cfg ( battboost2_t *ctx ) 
{
    err_t err_flag = BATTBOOST2_OK;
    Delay_100ms( );

    battboost2_set_on_pin_state( ctx, BATTBOOST2_CONDITION_STOP );
    Delay_100ms( );

    err_flag |= battboost2_set_vmin( ctx, BATTBOOST2_SET2_VMIN_2_4V );
    Delay_10ms( );

    err_flag |= battboost2_vdh_vbt_mode( ctx );
    Delay_10ms( );

    err_flag |= battboost2_set_ich( ctx, BATTBOOST2_ICH_16_MA );
    Delay_10ms( );

    err_flag |= battboost2_set_vew( ctx, BATTBOOST2_SET3_VEW_2_6V, 
                                        BATTBOOST2_SET3_EEW_ENABLE );
    Delay_10ms( );

    err_flag |= battboost2_set_vcapmax( ctx, BATTBOOST2_SET4_VCAPMAX_9_9V );
    Delay_10ms( );

    err_flag |= battboost2_set_opt_marg( ctx, BATTBOOST2_SET5_OPT_MARG_EXTRA_SAFE );
    Delay_10ms( );

    err_flag |= battboost2_set_prof( ctx, 1 );
    Delay_10ms( );

    err_flag |= battboost2_set_vset( ctx, BATTBOOST2_SET1_VSET_1_8V );
    Delay_10ms( );

    err_flag |= battboost2_set_op_mode( ctx, BATTBOOST2_OP_MODE_CHARGE );
    Delay_10ms( );

    while ( BATTBOOST2_STATUS_READY != battboost2_get_ready( ctx ) );

    err_flag |= battboost2_set_op_mode( ctx, BATTBOOST2_OP_MODE_ACTIVE );
    Delay_10ms( );

    battboost2_set_on_pin_state( ctx, BATTBOOST2_CONDITION_START );
    Delay_10ms( );

    return err_flag;
}

err_t battboost2_generic_write ( battboost2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t battboost2_generic_read ( battboost2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t battboost2_get_status ( battboost2_t *ctx, uint8_t *status ) 
{
    return battboost2_generic_read( ctx, BATTBOOST2_REG_STATUS, status, 1 );
}

err_t battboost2_get_chenergy ( battboost2_t *ctx, uint32_t *chenergy ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_CHENERGY_3, data_buf, 4 );
    *chenergy = data_buf[ 0 ];
    *chenergy <<= 8;
    *chenergy |= data_buf[ 1 ];
    *chenergy <<= 8;
    *chenergy |= data_buf[ 2 ];
    *chenergy <<= 8;
    *chenergy |= data_buf[ 3 ];
    return err_flag;
}

err_t battboost2_get_vcap ( battboost2_t *ctx, float *vcap ) 
{
    uint8_t data_buf = DUMMY;
    float vcap_vtg_table[ 32 ] = { 1.40, 1.51, 1.80, 2.19, 
                                   2.40, 2.60, 2.79, 3.01, 
                                   3.20, 3.41, 3.61, 3.99, 
                                   4.39, 4.80, 5.21, 5.59, 
                                   5.91, 6.02, 6.40, 6.55, 
                                   6.80, 7.14, 7.23, 7.68, 
                                   8.19, 8.65, 9.10, 9.53, 
                                   9.91, 10.33, 10.69, 11.07 };
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_VCAP, &data_buf, 1 );
    data_buf &= BATTBOOST2_VCAP_BIT_MASK;
    *vcap = vcap_vtg_table[ data_buf ];
    return err_flag;
}

err_t battboost2_get_vchend ( battboost2_t *ctx, uint8_t *vchend ) 
{
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_VCHEND, vchend, 1 );
    *vchend &= BATTBOOST2_VCHEND_BIT_MASK;
    return err_flag;
}

err_t battboost2_set_prof ( battboost2_t *ctx, uint8_t prof ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_PROFILE_MSB, data_buf, 2 );
    data_buf[ 0 ] &= BATTBOOST2_CMD_PROF_BIT_MASK;
    data_buf[ 0 ] |= ( prof >> 4 ) & BATTBOOST2_PROF_MSB_BIT_MASK;
    data_buf[ 1 ] &= BATTBOOST2_CMD_BIT_MASK;
    data_buf[ 1 ] |= ( prof << 4 ) & BATTBOOST2_PROF_BIT_MASK;
    err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_PROFILE_MSB, data_buf, 2 );
    return err_flag;
}

err_t battboost2_get_prof ( battboost2_t *ctx, uint8_t *prof ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_PROFILE_MSB, data_buf, 2 );
    *prof = data_buf[ 0 ] & BATTBOOST2_PROF_MSB_BIT_MASK;
    *prof <<= 4;
    *prof |= ( data_buf[ 1 ] >> 4 ) & BATTBOOST2_CMD_BIT_MASK;
    return err_flag;
}

err_t battboost2_set_op_mode ( battboost2_t *ctx, uint8_t op_mode ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
    Delay_1ms( );
    if ( op_mode == BATTBOOST2_OP_MODE_STANDBY )
    {
        data_buf &= ~BATTBOOST2_OP_MODE_STBY_BIT_MASK;
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
        Delay_10ms( );
    }
    else if ( op_mode == BATTBOOST2_OP_MODE_CHARGE )
    {
        data_buf &= BATTBOOST2_OP_MODE_CHG_BIT_MASK;
        data_buf |= BATTBOOST2_OP_MODE_SET_CHARGE;
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
        Delay_10ms( );
    }
    else if ( op_mode == BATTBOOST2_OP_MODE_ACTIVE )
    {
        data_buf |= BATTBOOST2_OP_MODE_SET_ACT_ACTIVE;
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
        Delay_10ms( );
    }
    else
    {
        err_flag = BATTBOOST2_ERROR;
    }
    return err_flag;
}

err_t battboost2_reset_optimizer ( battboost2_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
    Delay_1ms( );
    data_buf |= BATTBOOST2_CMD_RESET_BIT_MASK;
    err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
    Delay_10ms( );
    data_buf &= ~BATTBOOST2_CMD_RESET_BIT_MASK;
    err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
    return err_flag;
}

err_t battboost2_set_automode ( battboost2_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
    Delay_1ms( );
    data_buf |= BATTBOOST2_CMD_AUTOMODE_ENABLE;
    err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_COMMAND, &data_buf, 1 );
    return err_flag;
}

err_t battboost2_set_vset ( battboost2_t *ctx, float vset ) 
{
    err_t err_flag = BATTBOOST2_OK;
    uint8_t data_buf = DUMMY;
    if ( ( vset < BATTBOOST2_SET1_VSET_1_8V ) || 
         ( vset > BATTBOOST2_SET1_VSET_3_6V ) )
    {
        err_flag = BATTBOOST2_ERROR;
    }
    else
    { 
        err_flag |= battboost2_generic_read( ctx, BATTBOOST2_REG_SET1, &data_buf, 1 );
        data_buf &= BATTBOOST2_SET1_VSET_BIT_MASK;
        if ( vset < BATTBOOST2_SET1_VSET_2_4V )
        {
            vset -= BATTBOOST2_SET1_VSET_1_8V;
            data_buf |= ( uint8_t ) ( vset / 0.2 );
        }
        else
        {
            vset *= 10;
            data_buf |= ( ( ( uint8_t ) vset ) % 24 ) + 3;
        }
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET1, &data_buf, 1 );
    }
    return err_flag;
}

err_t battboost2_set_vfix ( battboost2_t *ctx, battboost2_vfix_t vfix ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = battboost2_get_prof( ctx, &data_buf );
    if ( BATTBOOST2_CMD_PROF_0_FIXED_MODE == data_buf )
    {
        err_flag = BATTBOOST2_ERROR;
    }
    else
    { 
        err_flag |= battboost2_generic_read( ctx, BATTBOOST2_REG_SET1, &data_buf, 1 );
        data_buf &= BATTBOOST2_SET1_VFIX_BIT_MASK;
        data_buf |= vfix;
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET1, &data_buf, 1 );
    }
    return err_flag;
}

err_t battboost2_set_vmin ( battboost2_t *ctx, float vmin ) 
{
    err_t err_flag = BATTBOOST2_OK;
    uint8_t data_buf = DUMMY;
    if ( ( vmin < BATTBOOST2_SET2_VMIN_2_4V ) || ( vmin > BATTBOOST2_SET2_VMIN_3_2V ) )
    {
        err_flag = BATTBOOST2_ERROR;
    }
    else
    { 
        err_flag |= battboost2_generic_read( ctx, BATTBOOST2_REG_SET2, &data_buf, 1 );
        data_buf &= BATTBOOST2_SET2_VMIN_BIT_MASK;
        vmin -= BATTBOOST2_SET2_VMIN_2_4V;
        data_buf |= ( uint8_t ) ( vmin / 0.2 );
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET2, &data_buf, 1 );
    }
    return err_flag;
}

err_t battboost2_set_ich ( battboost2_t *ctx, battboost2_ich_t ich ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_SET2, &data_buf, 1 );
    data_buf &= BATTBOOST2_SET2_ICH_BIT_MASK;
    data_buf |= ich << 5;
    err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET2, &data_buf, 1 );
    return err_flag;
}

err_t battboost2_high_impedance_mode ( battboost2_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_SET2, &data_buf, 1 );
    data_buf |= BATTBOOST2_SET2_SET_VDH_VBT;
    err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET2, &data_buf, 1 );
    return err_flag;
}

err_t battboost2_vdh_vbt_mode ( battboost2_t *ctx ) 
{
    uint8_t data_buf = 0;
    err_t err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_SET2, &data_buf, 1 );
    data_buf &= ~BATTBOOST2_SET2_SET_VDH_VBT;
    err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET2, &data_buf, 1 );
    return err_flag;
}

err_t battboost2_set_vew ( battboost2_t *ctx, uint8_t vew, uint8_t eew ) 
{
    err_t err_flag = BATTBOOST2_OK;
    uint8_t data_buf = DUMMY;
    if ( ( vew > BATTBOOST2_SET3_VEW_4_8V ) || ( eew > BATTBOOST2_SET3_EEW_ENABLE ) )
    {
        err_flag = BATTBOOST2_ERROR;
    }
    else
    {
        err_flag = battboost2_generic_read( ctx, BATTBOOST2_REG_SET3, &data_buf, 1 );
        data_buf &= BATTBOOST2_SET3_VEW_BIT_MASK;
        data_buf |= eew << 4;
        data_buf |= vew;
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET3, &data_buf, 1 );
    }
    return err_flag;
}

err_t battboost2_set_vcapmax ( battboost2_t *ctx, uint8_t vcapmax ) 
{
    err_t err_flag = BATTBOOST2_OK;
    uint8_t data_buf = DUMMY;
    if ( vcapmax > BATTBOOST2_SET4_VCAPMAX_11_0V )
    {
        err_flag = BATTBOOST2_ERROR;
    }
    else
    { 
        err_flag |= battboost2_generic_read( ctx, BATTBOOST2_REG_SET4, &data_buf, 1 );
        data_buf &= BATTBOOST2_SET4_VCAPMAX_BIT_MASK;
        data_buf |= vcapmax << 4;
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET4, &data_buf, 1 );
    }
    return err_flag;
}

err_t battboost2_set_opt_marg ( battboost2_t *ctx, uint8_t opt_marg ) 
{
    err_t err_flag = BATTBOOST2_OK;
    if ( opt_marg > BATTBOOST2_SET5_OPT_MARG_EXTRA_SAFE )
    {
        err_flag = BATTBOOST2_ERROR;
    }
    else
    {
        err_flag |= battboost2_generic_write( ctx, BATTBOOST2_REG_SET5, &opt_marg, 1 );
    }
    return err_flag;
}

void battboost2_set_on_pin_state ( battboost2_t *ctx, uint8_t start ) 
{
    digital_out_write( &ctx->on, start );
}

uint8_t battboost2_get_ready ( battboost2_t *ctx ) 
{
    return digital_in_read( &ctx->rdy );
}

// ------------------------------------------------------------------------- END
