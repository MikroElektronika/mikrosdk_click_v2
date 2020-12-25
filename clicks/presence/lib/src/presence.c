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
    cfg->i2c_address = 0x00;
}

PRESENCE_RETVAL presence_init ( presence_t *ctx, presence_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PRESENCE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PRESENCE_OK;

}

void presence_generic_write ( presence_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

void presence_generic_read ( presence_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t presence_get_interrupt_state ( presence_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void presence_general_call_addr ( presence_t *ctx )
{
    uint8_t write_reg;

    write_reg = 0x04;

    i2c_master_write( &ctx->i2c, &write_reg, 1 );  

    ctx->slave_address = PRESENCE_DEVICE_SLAVE_ADDRESS;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
}

uint8_t presence_eeprom_process ( presence_t *ctx )
{
    uint8_t ee_protocol;
    uint8_t raw_data[ 3 ] = { 0 };
    uint8_t cnt;
    uint16_t crc_sum = 0;
    uint8_t crc_pom;
    uint8_t pom_buff;

    // EEPROM ENABLE
    
    pom_buff = 0x80;
    presence_generic_write( ctx, PRESENCE_REG_EEPROM_CTRL, &pom_buff, 1 );
    
    presence_generic_read( ctx, PRESENCE_EEPROM_PROTOCOL, &ee_protocol, 1 );
    
    presence_generic_read( ctx, PRESENCE_EEPROM_PTAT25_1, &raw_data[ 0 ], 2 );
    ctx->eeprom_data.ptat25_data = raw_data[ 0 ];
    ctx->eeprom_data.ptat25_data <<= 8;
    ctx->eeprom_data.ptat25_data |= raw_data[ 1 ];

    presence_generic_read( ctx, PRESENCE_EEPROM_M_1, &raw_data[ 0 ], 2 );
    ctx->eeprom_data.m_data = raw_data[ 0 ];
    ctx->eeprom_data.m_data <<= 8;
    ctx->eeprom_data.m_data |= raw_data[ 1 ];
    ctx->eeprom_data.m_data /= 100;

    presence_generic_read( ctx, PRESENCE_EEPROM_U0_1, &raw_data[ 0 ], 2 );
    ctx->eeprom_data.u0_data = raw_data[ 0 ];
    ctx->eeprom_data.u0_data <<= 8;
    ctx->eeprom_data.u0_data |= raw_data[ 1 ];
    ctx->eeprom_data.u0_data += 32768;

    presence_generic_read( ctx, PRESENCE_EEPROM_TOBJ, &raw_data[ 0 ], 1 );
    ctx->eeprom_data.tobj_data = raw_data[ 0 ];

    presence_generic_read( ctx, PRESENCE_EEPROM_UOUT_1, &raw_data[ 0 ], 2 );
    ctx->eeprom_data.uout_data = raw_data[ 0 ];
    ctx->eeprom_data.uout_data <<= 8;
    ctx->eeprom_data.uout_data |= raw_data[ 1 ];
    ctx->eeprom_data.uout_data *= 2;

    presence_generic_read( ctx, PRESENCE_EEPROM_CHECKSUM_1, &raw_data[ 0 ], 2 );
    ctx->eeprom_data.checksum_data = raw_data[ 0 ];
    ctx->eeprom_data.checksum_data <<= 8;
    ctx->eeprom_data.checksum_data |= raw_data[ 1 ];

    for ( cnt = 35; cnt < 64; cnt++ )
    {
        presence_generic_read( ctx, cnt, &crc_pom, 1 );
        crc_sum += crc_pom;
    }
    crc_sum = crc_sum + ee_protocol;
    
    // Disable EEPROM

    pom_buff = 0x00;
    presence_generic_write( ctx, PRESENCE_REG_EEPROM_CTRL, &pom_buff, 1);
    
    if ( ctx->eeprom_data.checksum_data != crc_sum )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

float presence_get_calib_constants( presence_t *ctx )
{
    float kalib;
    
    kalib = ( float )ctx->eeprom_data.uout_data - ( float )ctx->eeprom_data.u0_data;
    kalib /= pow( ctx->eeprom_data.tobj_data + 273.15, 3.8 ) - pow( 25.0 + 273.15, 3.8 );
    
    return kalib;
}

float presence_ambient_temperature( presence_t *ctx )
{
    uint16_t tpamb;
    uint8_t raw_data[ 2 ];
    float tamb;
    
    presence_generic_read( ctx, PRESENCE_REG_TP_AMBIENT_MSB, &raw_data[ 0 ], 2 );
    tpamb = raw_data[ 0 ] & 0x7F;
    tpamb <<= 8;
    tpamb |= raw_data[ 1 ];

    tamb = ( float )tpamb - ( float )ctx->eeprom_data.ptat25_data;
    tamb *= 1.0 /( float )ctx->eeprom_data.m_data;
    tamb += 25.0;

    return tamb;
}

float presence_object_temperature( presence_t *ctx )
{
    uint8_t raw_data[ 3 ];
    uint32_t tpobj;
    float k;
    float temp0;
    float temp1;
    float tamb;
    float tobj;
    
    k = presence_get_calib_constants( ctx );
    tamb = presence_ambient_temperature( ctx );
    
    presence_generic_read( ctx, PRESENCE_REG_TP_OBJECT_MSB, &raw_data[ 0 ], 3 );
    tpobj = raw_data[ 0 ];
    tpobj <<= 8;
    tpobj |= raw_data[ 1 ];
    tpobj <<= 1;
    tpobj |= ( raw_data[ 2 ] & 0x80 ) >> 7;
    
    k = ( float )ctx->eeprom_data.uout_data - ( float )ctx->eeprom_data.u0_data;
    k /= pow( ctx->eeprom_data.tobj_data + 273.15, 3.8 ) - pow( tamb + 273.15, 3.8 );

    temp0 = pow( tamb + 273.15, 3.8 );
    temp1 = ( float )tpobj - ( float )ctx->eeprom_data.u0_data;
    temp1 /= k;
    tobj = pow( ( temp0 + temp1 ), 0.2631578947 );
    tobj -= 273.15;

    return tobj;
}

// ------------------------------------------------------------------------- END

