/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "presence.h"
#include "math.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void presence_cfg_setup ( presence_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PRESENCE_DEVICE_GEN_CALL_ADDRESS;
}

err_t presence_init ( presence_t *ctx, presence_cfg_t *cfg )
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

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PRESENCE_OK;
}

err_t presence_default_cfg ( presence_t *ctx ) 
{
    err_t error_flag = PRESENCE_OK;
    
    // General call address
    presence_general_call_addr( ctx );
    Delay_1sec( );

    // EEPROM
    if ( PRESENCE_ERROR == presence_eeprom_process( ctx ) )
    {
        return PRESENCE_ERROR;
    }
    Delay_1sec( );
    Delay_1sec( );
    uint8_t wr_data = PRESENCE_INT_MASK1_TP_OT | PRESENCE_INT_MASK1_MOTION | PRESENCE_INT_MASK1_PRESENCE;
    presence_generic_write( ctx, PRESENCE_REG_INTERRUPT_MASK_1, &wr_data, 1 );
    
    wr_data = ( PRESENCE_LOW_PASS_TIME_8S << 4 ) | PRESENCE_LOW_PASS_TIME_1S;
    presence_generic_write( ctx, PRESENCE_REG_LOW_PASS_TIME_1, &wr_data, 1 );
    
    wr_data = PRESENCE_INT_MASK2_SRC_LP1_LP2 | PRESENCE_INT_MASK2_CYCLE_TIME_140MS;
    presence_generic_write( ctx, PRESENCE_REG_INTERRUPT_MASK_2, &wr_data, 1 );
    
    // Set presence, motion, and over-temperature thresholds
    wr_data = 0x80;
    presence_generic_write( ctx, PRESENCE_REG_TP_PRESENCE_THR, &wr_data, 1 );
    wr_data = 0x60;
    presence_generic_write( ctx, PRESENCE_REG_TP_MOTION_THR, &wr_data, 1 );
    wr_data = 0x83;
    presence_generic_write( ctx, PRESENCE_REG_TP_OT_THR_1, &wr_data, 1 );
    wr_data = 0x00;
    presence_generic_write( ctx, PRESENCE_REG_TP_OT_THR_2, &wr_data, 1 );
    wr_data = PRESENCE_INT_MASK2_TPOT_DIR | PRESENCE_INT_MASK2_SRC_LP1_LP2 | PRESENCE_INT_MASK2_CYCLE_TIME_140MS;
    presence_generic_write( ctx, PRESENCE_REG_INTERRUPT_MASK_2, &wr_data, 1 );
    Delay_1sec( );
    // Clear interrupt status
    presence_generic_read( ctx, PRESENCE_REG_INTERRUPT_STATUS, &wr_data, 1 );
    Delay_1sec( );

    return error_flag;
}

err_t presence_generic_write ( presence_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

err_t presence_generic_read ( presence_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t presence_get_int_state ( presence_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void presence_general_call_addr ( presence_t *ctx )
{
    uint8_t wr_data = 0x04; // command to reload address from eeprom
    i2c_master_write( &ctx->i2c, &wr_data, 1 );  

    ctx->slave_address = PRESENCE_DEVICE_SLAVE_ADDRESS;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
}

err_t presence_eeprom_process ( presence_t *ctx )
{
    uint8_t ee_protocol = 0;
    uint8_t raw_data[ 2 ] = { 0 };
    uint16_t crc_sum = 0;
    uint8_t crc = 0;
    uint8_t wr_data = 0;

    // EEPROM ENABLE
    wr_data = 0x80;
    presence_generic_write( ctx, PRESENCE_REG_EEPROM_CTRL, &wr_data, 1 );
    
    presence_generic_read( ctx, PRESENCE_EEPROM_PROTOCOL, &ee_protocol, 1 );
    
    presence_generic_read( ctx, PRESENCE_EEPROM_PTAT25_1, raw_data, 2 );
    ctx->eeprom_data.ptat25_data = raw_data[ 0 ];
    ctx->eeprom_data.ptat25_data <<= 8;
    ctx->eeprom_data.ptat25_data |= raw_data[ 1 ];

    presence_generic_read( ctx, PRESENCE_EEPROM_M_1, raw_data, 2 );
    ctx->eeprom_data.m_data = raw_data[ 0 ];
    ctx->eeprom_data.m_data <<= 8;
    ctx->eeprom_data.m_data |= raw_data[ 1 ];
    ctx->eeprom_data.m_data /= 100;

    presence_generic_read( ctx, PRESENCE_EEPROM_U0_1, raw_data, 2 );
    ctx->eeprom_data.u0_data = raw_data[ 0 ];
    ctx->eeprom_data.u0_data <<= 8;
    ctx->eeprom_data.u0_data |= raw_data[ 1 ];
    ctx->eeprom_data.u0_data += 32768;

    presence_generic_read( ctx, PRESENCE_EEPROM_TOBJ, raw_data, 1 );
    ctx->eeprom_data.tobj_data = raw_data[ 0 ];

    presence_generic_read( ctx, PRESENCE_EEPROM_UOUT_1, raw_data, 2 );
    ctx->eeprom_data.uout_data = raw_data[ 0 ];
    ctx->eeprom_data.uout_data <<= 8;
    ctx->eeprom_data.uout_data |= raw_data[ 1 ];
    ctx->eeprom_data.uout_data *= 2;

    presence_generic_read( ctx, PRESENCE_EEPROM_CHECKSUM_1, raw_data, 2 );
    ctx->eeprom_data.checksum_data = raw_data[ 0 ];
    ctx->eeprom_data.checksum_data <<= 8;
    ctx->eeprom_data.checksum_data |= raw_data[ 1 ];

    for ( uint8_t cnt = 35; cnt < 64; cnt++ )
    {
        presence_generic_read( ctx, cnt, &crc, 1 );
        crc_sum += crc;
    }
    crc_sum = crc_sum + ee_protocol;
    
    // Disable EEPROM
    wr_data = 0x00;
    presence_generic_write( ctx, PRESENCE_REG_EEPROM_CTRL, &wr_data, 1 );
    
    if ( ctx->eeprom_data.checksum_data != crc_sum )
    {
        return PRESENCE_ERROR;
    }
    return PRESENCE_OK;
}

float presence_get_calib_constants( presence_t *ctx )
{
    float calib = 0;
    
    calib = ( float ) ctx->eeprom_data.uout_data - ( float ) ctx->eeprom_data.u0_data;
    calib /= pow ( ctx->eeprom_data.tobj_data + 273.15, 3.8 ) - pow( 25.0 + 273.15, 3.8 );
    
    return calib;
}

err_t presence_ambient_temperature( presence_t *ctx, float *temperature )
{
    uint16_t raw_t_amb = 0;
    uint8_t reg_data[ 2 ] = { 0 };
    float t_amb = 0;
    
    err_t error_flag = presence_generic_read( ctx, PRESENCE_REG_TP_AMBIENT_MSB, reg_data, 2 );
    raw_t_amb = reg_data[ 0 ] & 0x7F;
    raw_t_amb <<= 8;
    raw_t_amb |= reg_data[ 1 ];

    t_amb = ( float ) raw_t_amb - ( float ) ctx->eeprom_data.ptat25_data;
    t_amb *= 1.0 / ( float ) ctx->eeprom_data.m_data;
    t_amb += 25.0;
    *temperature = t_amb;

    return error_flag;
}

err_t presence_object_temperature( presence_t *ctx, float *temperature )
{
    uint8_t reg_data[ 3 ] = { 0 };
    uint32_t raw_t_obj = 0;
    float calib = 0;
    float temp0 = 0;
    float temp1 = 0;
    float t_amb = 0;
    float t_obj = 0;
    err_t error_flag = PRESENCE_OK;
    
    calib = presence_get_calib_constants( ctx );
    error_flag |= presence_ambient_temperature( ctx, &t_amb );
    
    error_flag |= presence_generic_read( ctx, PRESENCE_REG_TP_OBJECT_MSB, reg_data, 3 );
    raw_t_obj = reg_data[ 0 ];
    raw_t_obj <<= 8;
    raw_t_obj |= reg_data[ 1 ];
    raw_t_obj <<= 1;
    raw_t_obj |= ( reg_data[ 2 ] & 0x80 ) >> 7;
    
    calib = ( float ) ctx->eeprom_data.uout_data - ( float ) ctx->eeprom_data.u0_data;
    calib /= pow( ctx->eeprom_data.tobj_data + 273.15, 3.8 ) - pow( t_amb + 273.15, 3.8 );

    temp0 = pow( t_amb + 273.15, 3.8 );
    temp1 = ( float ) raw_t_obj - ( float ) ctx->eeprom_data.u0_data;
    temp1 /= calib;
    t_obj = pow( ( temp0 + temp1 ), 0.2631578947 );
    t_obj -= 273.15;
    *temperature = t_obj;

    return error_flag;
}

// ------------------------------------------------------------------------- END

