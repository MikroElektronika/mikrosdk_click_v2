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
 * @file irthermo4.c
 * @brief IR Thermo 4 Click Driver.
 */

#include "irthermo4.h"
#include "math.h"

/**
 * @brief IR Thermo 4 calculate checksum function.
 * @details This function calculates the checksum word of the input array.
 * @param[in] data_in : Data buffer to calculate the checksum from.
 * @param[in] len : Number of bytes in the data buffer.
 * @return Calculated checksum word.
 * @note None.
 */
static uint16_t irthermo4_calculate_checksum ( uint8_t *data_in, uint8_t len );

void irthermo4_cfg_setup ( irthermo4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = IRTHERMO4_DEVICE_ADDRESS_GND;
}

err_t irthermo4_init ( irthermo4_t *ctx, irthermo4_cfg_t *cfg ) 
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

err_t irthermo4_default_cfg ( irthermo4_t *ctx ) 
{
    err_t error_flag = IRTHERMO4_OK;
    if ( IRTHERMO4_OK != irthermo4_refresh_address ( ctx ) )
    {
        return IRTHERMO4_ERROR;
    }
    error_flag |= irthermo4_read_eeprom ( ctx );
    return error_flag;
}

err_t irthermo4_write_regs ( irthermo4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    if ( ( reg < IRTHERMO4_REG_S_LP1_LP2 ) || 
         ( ( reg + len ) > ( IRTHERMO4_REG_EEPROM_CONTROL + 1 ) ) || 
         ( NULL == data_in ) )
    {
        return IRTHERMO4_ERROR;
    }
    uint8_t data_buf[ 13 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t irthermo4_read_regs ( irthermo4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( reg < IRTHERMO4_REG_TP_OBJECT ) || 
         ( ( reg + len ) > ( IRTHERMO4_REG_SLAVE_ADDRESS + 1 ) ) || 
         ( NULL == data_out ) )
    {
        return IRTHERMO4_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t irthermo4_write_reg ( irthermo4_t *ctx, uint8_t reg, uint8_t data_in )
{
    return irthermo4_write_regs( ctx, reg, &data_in, 1 );
}

err_t irthermo4_read_reg ( irthermo4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return irthermo4_read_regs( ctx, reg, data_out, 1 );
}

err_t irthermo4_refresh_address ( irthermo4_t *ctx )
{
    err_t error_flag = IRTHERMO4_OK;
    uint8_t cmd = IRTHERMO4_CMD_RELOAD;
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, IRTHERMO4_DEVICE_ADDRESS_GEN_CALL );
    error_flag |= i2c_master_write( &ctx->i2c, &cmd, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    Delay_1ms ( );
    return error_flag;
}

err_t irthermo4_read_eeprom ( irthermo4_t *ctx )
{
    err_t error_flag = IRTHERMO4_OK;
    uint8_t data_buf[ 32 ] = { 0 };
    uint16_t checksum = 0;
    float temp0 = 0;
    error_flag |= irthermo4_write_reg( ctx, IRTHERMO4_REG_EEPROM_CONTROL, IRTHERMO4_EEPROM_READ_ENABLE );
    Delay_1ms ( );
    error_flag |= irthermo4_read_regs( ctx, IRTHERMO4_REG_EEPROM_CONTENT, data_buf, 32 );
    checksum = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    if ( ( IRTHERMO4_OK == error_flag ) && 
         ( checksum == ( irthermo4_calculate_checksum ( &data_buf[ 3 ], 29 ) + data_buf[ 0 ] ) ) )
    {
        ctx->eeprom.protocol = data_buf[ 0 ];
        ctx->eeprom.lookup = data_buf[ 9 ];
        ctx->eeprom.ptat25 = ( ( uint16_t ) data_buf[ 10 ] << 8 ) | data_buf[ 11 ];
        ctx->eeprom.m_val = ( float ) ( ( ( uint16_t ) data_buf[ 12 ] << 8 ) | data_buf[ 13 ] ) / IRTHERMO4_DIGITS_K_TO_M;
        ctx->eeprom.u0_val = ( uint32_t ) ( ( ( uint16_t ) data_buf[ 14 ] << 8 ) | data_buf[ 15 ] ) + IRTHERMO4_TP_OFFSET_TO_U0;
        ctx->eeprom.uout1 = ( uint32_t ) ( ( ( uint16_t ) data_buf[ 16 ] << 8 ) | data_buf[ 17 ] ) * IRTHERMO4_TP_OUT_TO_UOUT;
        ctx->eeprom.tobj1 = data_buf[ 18 ];
        ctx->eeprom.slave_add = data_buf[ 31 ];
        ctx->eeprom.k_val = ( ( float ) ctx->eeprom.uout1 - ctx->eeprom.u0_val );
        if ( 0 != ctx->eeprom.k_val )
        {
            if ( 0 != ctx->eeprom.tobj1 )
            {
                temp0 = pow ( ( float ) ctx->eeprom.tobj1, IRTHERMO4_FUNCTION_EXPONENT );
            }
            temp0 -= pow ( IRTHERMO4_ROOM_TEMPERATURE, IRTHERMO4_FUNCTION_EXPONENT );
            if ( 0 != temp0 )
            {
                ctx->eeprom.k_val /= temp0;
            }
        }
    }
    error_flag |= irthermo4_write_reg( ctx, IRTHERMO4_REG_EEPROM_CONTROL, IRTHERMO4_EEPROM_READ_DISABLE );
    Delay_1ms ( );
    return error_flag;
}

uint8_t irthermo4_get_int_pin ( irthermo4_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t irthermo4_read_ambient_temp ( irthermo4_t *ctx, float *t_amb )
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t tp_ambient = 0;
    float temp0 = 0;
    err_t error_flag = irthermo4_read_regs( ctx, IRTHERMO4_REG_TP_AMBIENT, data_buf, 2 );
    if ( ( IRTHERMO4_OK == error_flag ) && ( NULL != t_amb ) )
    {
        tp_ambient = ( ( uint16_t ) ( data_buf[ 0 ] & 0x7F ) << 8 ) | data_buf[ 1 ];
        if ( 0 != ctx->eeprom.m_val )
        {
            temp0 = 1 / ctx->eeprom.m_val;
        }
        *t_amb = IRTHERMO4_ROOM_TEMPERATURE + ( ( float ) tp_ambient - ctx->eeprom.ptat25 ) * temp0;
    }
    return error_flag;
}

err_t irthermo4_read_object_temp ( irthermo4_t *ctx, float *t_obj, float t_amb )
{
    uint8_t data_buf[ 3 ] = { 0 };
    uint32_t tp_object = 0;
    float temp0 = 0;
    err_t error_flag = irthermo4_read_regs( ctx, IRTHERMO4_REG_TP_OBJECT, data_buf, 3 );
    if ( ( IRTHERMO4_OK == error_flag ) && ( NULL != t_obj ) )
    {
        tp_object = ( ( uint32_t ) data_buf[ 0 ] << 9 ) | ( ( uint16_t ) data_buf[ 1 ] << 1 ) | ( data_buf[ 2 ] >> 7 );
        if ( 0 != ctx->eeprom.k_val )
        {
            temp0 = ( ( float ) tp_object - ctx->eeprom.u0_val );
            temp0 /= ctx->eeprom.k_val;
            temp0 += pow ( t_amb, IRTHERMO4_FUNCTION_EXPONENT );
        }
        if ( temp0 > 0 )
        {
            *t_obj = pow ( temp0, ( float ) 1 / IRTHERMO4_FUNCTION_EXPONENT );
        }
        else
        {
            *t_obj = 0;
        }
    }
    return error_flag;
}

static uint16_t irthermo4_calculate_checksum ( uint8_t *data_in, uint8_t len )
{
    uint16_t checksum = 0;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        checksum += data_in[ cnt ];
    }
    return checksum;
}

// ------------------------------------------------------------------------- END
