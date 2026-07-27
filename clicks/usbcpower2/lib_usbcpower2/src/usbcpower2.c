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
 * @file usbcpower2.c
 * @brief USB-C Power 2 Click Driver.
 */

#include "usbcpower2.h"

void usbcpower2_cfg_setup ( usbcpower2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->id_pin = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCPOWER2_DEVICE_ADDRESS;
}

err_t usbcpower2_init ( usbcpower2_t *ctx, usbcpower2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->id_pin, cfg->id_pin );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t usbcpower2_default_cfg ( usbcpower2_t *ctx ) 
{
    err_t error_flag = USBCPOWER2_OK;
    if ( USBCPOWER2_OK != usbcpower2_check_com ( ctx ) )
    {
        return USBCPOWER2_ERROR;
    }
    // Reset system digital block
    error_flag |= usbcpower2_write_reg ( ctx, USBCPOWER2_REG_RESET, USBCPOWER2_RESET_SYSTEM );
    Delay_100ms ( );
    // Rp Selection - 80uA default, Mode Selection - Dual Role (DRP), Interrupt Mask for detached/attached - not masked
    error_flag |= usbcpower2_write_reg ( ctx, USBCPOWER2_REG_CONTROL, USBCPOWER2_CONTROL_RP_SEL_80UA | 
                                                                      USBCPOWER2_CONTROL_MODE_SEL_DUAL_ROLE_DRP | 
                                                                      USBCPOWER2_CONTROL_INT_MASK_DIS );
    // Mask all other interrupts
    error_flag |= usbcpower2_write_reg ( ctx, USBCPOWER2_REG_INTERRUPT_MASK, USBCPOWER2_INTERRUPT_MASK_CC1_CC2_CHANGE_EN | 
                                                                             USBCPOWER2_INTERRUPT_MASK_ROLE_CHANGE_EN | 
                                                                             USBCPOWER2_INTERRUPT_MASK_ORIENTATION_EN | 
                                                                             USBCPOWER2_INTERRUPT_MASK_DEBUG_EN | 
                                                                             USBCPOWER2_INTERRUPT_MASK_AUDIO_EN );
    // Enable CON_DET output on pin 5
    error_flag |= usbcpower2_write_reg ( ctx, USBCPOWER2_REG_CON_DET_CONFIG, USBCPOWER2_CON_DET_CONFIG_EN );
    return error_flag;
}

err_t usbcpower2_write_reg ( usbcpower2_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( USBCPOWER2_REG_CONTROL != reg ) &&
         ( USBCPOWER2_REG_CON_DET_CONFIG != reg ) &&
         ( USBCPOWER2_REG_RESET != reg ) &&
         ( USBCPOWER2_REG_INTERRUPT_MASK != reg ) )
    {
        return USBCPOWER2_ERROR;
    }
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t usbcpower2_read_reg ( usbcpower2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( ( USBCPOWER2_REG_VENDOR_ID != reg ) &&
         ( USBCPOWER2_REG_CONTROL != reg ) &&
         ( USBCPOWER2_REG_INTERRUPT_STATUS != reg ) &&
         ( USBCPOWER2_REG_CC_STATUS != reg ) &&
         ( USBCPOWER2_REG_CON_DET_CONFIG != reg ) &&
         ( USBCPOWER2_REG_VCONN_STATUS != reg ) &&
         ( USBCPOWER2_REG_RESET != reg ) &&
         ( USBCPOWER2_REG_INTERRUPT_MASK != reg ) &&
         ( USBCPOWER2_REG_INTERRUPT_REG_STATUS != reg ) )
    {
        return USBCPOWER2_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

uint8_t usbcpower2_get_id_pin ( usbcpower2_t *ctx )
{
    return !!digital_in_read ( &ctx->id_pin );
}

uint8_t usbcpower2_get_int_pin ( usbcpower2_t *ctx )
{
    return !!digital_in_read ( &ctx->int_pin );
}

err_t usbcpower2_check_com ( usbcpower2_t *ctx )
{
    uint8_t vendor_id = 0;
    if ( USBCPOWER2_OK == usbcpower2_read_reg ( ctx, USBCPOWER2_REG_VENDOR_ID, &vendor_id ) )
    {
        if ( USBCPOWER2_VENDOR_ID_VENDOR_ID == ( vendor_id & USBCPOWER2_VENDOR_ID_VENDOR_ID_MASK ) )
        {
            return USBCPOWER2_OK;
        }
    }
    return USBCPOWER2_ERROR;
}

// ------------------------------------------------------------------------- END
