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
 * @file haptic6.c
 * @brief Haptic 6 Click Driver.
 */

#include "haptic6.h"

/**
 * @brief IQS397 haptic ready timeout.
 * @details Haptic I2C ready timeout in milliseconds.
 */
#define HAPTIC6_RDY_TIMEOUT_MS  250

/**
 * @brief Haptic 6 RDY wait function.
 * @details This function waits until the IQS397 RDY pin becomes active low or
 * until the driver timeout expires. A short pre-delay allows the IQS397 to
 * update the RDY pin after a previous I2C transfer or haptic trigger command.
 * @param[in] ctx : Click context object.
 * See #haptic6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t haptic6_wait_rdy ( haptic6_t *ctx );

void haptic6_cfg_setup ( haptic6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HAPTIC6_DEVICE_ADDRESS;
}

err_t haptic6_init ( haptic6_t *ctx, haptic6_cfg_t *cfg ) 
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

    digital_in_init( &ctx->rdy, cfg->rdy );

    return I2C_MASTER_SUCCESS;
}

err_t haptic6_default_cfg ( haptic6_t *ctx ) 
{
    err_t error_flag = HAPTIC6_OK;

    if ( HAPTIC6_OK != haptic6_soft_reset( ctx ) )
    {
        return HAPTIC6_ERROR;
    }
    error_flag |= haptic6_ack_reset( ctx );
    error_flag |= haptic6_write_reg( ctx, HAPTIC6_REG_POWER_SETTINGS,
                                      HAPTIC6_POWER_TERM_STOP | HAPTIC6_POWER_IF_STREAMING |
                                      HAPTIC6_POWER_MODE_NORMAL );
    error_flag |= haptic6_write_reg( ctx, HAPTIC6_REG_EVENT_MASKS, HAPTIC6_EVENT_ALL );
    error_flag |= haptic6_write_reg_word( ctx, HAPTIC6_REG_I2C_TIMEOUT, HAPTIC6_DEF_I2C_TIMEOUT );
    error_flag |= haptic6_write_reg_word( ctx, HAPTIC6_REG_HBRIDGE_SETUP, HAPTIC6_DEF_HBRIDGE_SETUP );
    error_flag |= haptic6_write_reg_word( ctx, HAPTIC6_REG_PWM_FREQUENCY, HAPTIC6_DEF_PWM_FREQ );
    error_flag |= haptic6_write_reg_word( ctx, HAPTIC6_REG_LRA_FREQUENCY, HAPTIC6_DEF_LRA_FREQ );
    error_flag |= haptic6_write_reg( ctx, HAPTIC6_REG_AR_SETTINGS, HAPTIC6_DEF_AR_SETTINGS );
    error_flag |= haptic6_write_reg( ctx, HAPTIC6_REG_DRIVE_SETTINGS, HAPTIC6_DEF_DRIVE_SETTINGS );
    error_flag |= haptic6_write_reg_word( ctx, HAPTIC6_REG_HAPTIC_CONTROL, HAPTIC6_HAPTIC_ENABLE );

    return error_flag;
}

err_t haptic6_write_reg ( haptic6_t *ctx, uint16_t reg, uint8_t data_in ) 
{
    return haptic6_write_regs( ctx, reg, &data_in, 1 );
}

err_t haptic6_write_regs ( haptic6_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t )( reg & 0xFF );
    data_buf[ 1 ] = ( uint8_t )( ( reg >> 8 ) & 0xFF );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }

    if ( HAPTIC6_OK != haptic6_wait_rdy( ctx ) )
    {
        return HAPTIC6_ERROR;
    }

    return i2c_master_write( &ctx->i2c, data_buf, len + 2 );
}

err_t haptic6_write_reg_word ( haptic6_t *ctx, uint16_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t )( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t )( ( data_in >> 8 ) & 0xFF );
    return haptic6_write_regs( ctx, reg, data_buf, 2 );
}

err_t haptic6_read_reg ( haptic6_t *ctx, uint16_t reg, uint8_t *data_out ) 
{
    return haptic6_read_regs( ctx, reg, data_out, 1 );
}

err_t haptic6_read_regs ( haptic6_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t )( reg & 0xFF );
    data_buf[ 1 ] = ( uint8_t )( ( reg >> 8 ) & 0xFF );
    if ( HAPTIC6_OK != haptic6_wait_rdy( ctx ) )
    {
        return HAPTIC6_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, len );
}

err_t haptic6_read_reg_word ( haptic6_t *ctx, uint16_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = haptic6_read_regs( ctx, reg, data_buf, 2 );
    if ( ( HAPTIC6_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

uint8_t haptic6_get_rdy_pin ( haptic6_t *ctx )
{
    return !!digital_in_read( &ctx->rdy );
}

err_t haptic6_trigger ( haptic6_t *ctx )
{
    return haptic6_write_reg( ctx, HAPTIC6_REG_SYS_COMMANDS, HAPTIC6_SYS_CMD_TRIGGER );
}

err_t haptic6_cancel ( haptic6_t *ctx )
{
    return haptic6_write_reg_word( ctx, HAPTIC6_REG_HAPTIC_CONTROL,
                                   HAPTIC6_HAPTIC_ENABLE | HAPTIC6_HAPTIC_CANCEL );
}

err_t haptic6_ack_reset ( haptic6_t *ctx )
{
    return haptic6_write_reg( ctx, HAPTIC6_REG_SYS_COMMANDS, HAPTIC6_SYS_CMD_ACK_RESET );
}

err_t haptic6_soft_reset ( haptic6_t *ctx )
{
    return haptic6_write_reg( ctx, HAPTIC6_REG_SYS_COMMANDS, HAPTIC6_SYS_CMD_SOFT_RESET );
}

static err_t haptic6_wait_rdy ( haptic6_t *ctx )
{
    uint16_t timeout_cnt = 0;

    /* Allow RDY to settle before sampling it after back-to-back commands. */
    Delay_50us( );

    for ( timeout_cnt = 0; timeout_cnt < HAPTIC6_RDY_TIMEOUT_MS; timeout_cnt++ )
    {
        if ( 0 == haptic6_get_rdy_pin( ctx ) )
        {
            return HAPTIC6_OK;
        }

        Delay_1ms( );
    }

    return HAPTIC6_ERROR;
}

// ------------------------------------------------------------------------- END
