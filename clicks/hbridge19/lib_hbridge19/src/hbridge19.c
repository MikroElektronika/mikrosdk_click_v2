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
 * @file hbridge19.c
 * @brief H-Bridge 19 Click Driver.
 */

#include "hbridge19.h"

void hbridge19_cfg_setup ( hbridge19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HBRIDGE19_DEVICE_ADDRESS;
}

err_t hbridge19_init ( hbridge19_t *ctx, hbridge19_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t hbridge19_default_cfg ( hbridge19_t *ctx ) 
{
    err_t error_flag = HBRIDGE19_OK;

    /* Drive 0 to all output pins as a safe output state since POR default is 0xFF */
    error_flag |= hbridge19_write_reg ( ctx, HBRIDGE19_REG_OUTPUT_PORT, HBRIDGE19_OUTPUT_DEFAULT );

    /* Set all port pins as output except pin 5 which is mapped to BD60210FV-E2 FAULT pin */ 
    error_flag |= hbridge19_write_reg ( ctx, HBRIDGE19_REG_CONFIG, HBRIDGE19_CONFIG_DEFAULT );

    /* Both motors stay in high-impedance. */
    error_flag |= hbridge19_enable_device ( ctx );

    return error_flag;
}

err_t hbridge19_write_reg ( hbridge19_t *ctx, uint8_t cmd, uint8_t data_in ) 
{
    /* Write frame: S | addr + W | A | command_byte | A | data_byte | A | P */
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = data_in;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t hbridge19_read_reg ( hbridge19_t *ctx, uint8_t cmd, uint8_t *data_out ) 
{
    /* Read frame: S | addr + W | A | command_byte | A | RS | addr + R | data_byte | NA | P */
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, 1 );
}

err_t hbridge19_enable_device ( hbridge19_t *ctx ) 
{
    uint8_t port_data = 0;

    /* Perform read-modify-write to set PS pin(bit 6) without changing other bits */
    err_t error_flag = hbridge19_read_reg ( ctx, HBRIDGE19_REG_OUTPUT_PORT, &port_data );
    port_data |= HBRIDGE19_PIN_PS;
    error_flag |= hbridge19_write_reg ( ctx, HBRIDGE19_REG_OUTPUT_PORT, port_data );

    Delay_1ms ( );

    return error_flag;
}

err_t hbridge19_disable_device ( hbridge19_t *ctx ) 
{
    uint8_t port_data = 0;

    /* Perform read-modify-write to clear PS pin(bit 6) without changing other bits */
    err_t error_flag = hbridge19_read_reg ( ctx, HBRIDGE19_REG_OUTPUT_PORT, &port_data );
    port_data &= ~HBRIDGE19_PIN_PS;
    error_flag |= hbridge19_write_reg ( ctx, HBRIDGE19_REG_OUTPUT_PORT, port_data );

    return error_flag;
}

err_t hbridge19_set_motor_state ( hbridge19_t *ctx, uint8_t motor, uint8_t state ) 
{
    /* Reject an invalid motor index (0-1) or state (0-3) */
    if ( ( HBRIDGE19_MOTOR_SEL_1 < motor ) || ( HBRIDGE19_MOTOR_STATE_BRAKE < state ) )
    {
        return HBRIDGE19_ERROR;
    }

    uint8_t mask_in_a = 0;
    uint8_t mask_in_b = 0;

    /* Pick the INxA/INxB for the selected motor:
     *     P3 = IN2A -> motor 1
     *     P2 = IN2B -> motor 1
     *     P1 = IN1B -> motor 0
     *     P0 = IN1A -> motor 0 */
    if ( HBRIDGE19_MOTOR_SEL_1 == motor )
    {
        mask_in_a = HBRIDGE19_PIN_IN2A;
        mask_in_b = HBRIDGE19_PIN_IN2B;
    }
    else
    {
        mask_in_a = HBRIDGE19_PIN_IN1A;
        mask_in_b = HBRIDGE19_PIN_IN1B;
    }

    uint8_t motor_mask = ( mask_in_a | mask_in_b );

    /* Decode the state:
     *     bit[1] = INxB
     *     bit[0] = INxA
     *     00 -> HI_Z, 01 -> FORWARD , 10 -> REVERSE, 11 -> BRAKE */
    uint8_t in_a = ( state & 0x01 );
    uint8_t in_b = ( ( state >> 1 ) & 0x01 );

    /* Perform read-modify-write to set INxA/INxB in output register based on selected state */
    uint8_t port_data = 0;
    err_t error_flag = hbridge19_read_reg ( ctx, HBRIDGE19_REG_OUTPUT_PORT, &port_data );
    port_data &= ~motor_mask;

    if ( in_a )
    {
        port_data |= mask_in_a;
    }
    if ( in_b )
    {
        port_data |= mask_in_b;
    }

    error_flag |= hbridge19_write_reg ( ctx, HBRIDGE19_REG_OUTPUT_PORT, port_data );

    return error_flag;
}

uint8_t hbridge19_get_int_pin ( hbridge19_t *ctx ) 
{
    return digital_in_read ( &ctx->int_pin );
}

err_t hbridge19_get_fault ( hbridge19_t *ctx, uint8_t *fault ) 
{
    uint8_t port_data = 0;
    
    /* Read P5 = FAULT pin which signals overcurrent protection or thermal shutdown circuit activation */
    err_t error_flag = hbridge19_read_reg ( ctx, HBRIDGE19_REG_INPUT_PORT, &port_data );
    
    /* FAULT is active low */
    if ( port_data & HBRIDGE19_PIN_FAULT )
    {
        *fault = 0;
    }
    else
    {
        *fault = 1;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
