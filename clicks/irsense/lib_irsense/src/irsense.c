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

#include "irsense.h"

void irsense_cfg_setup ( irsense_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pdn   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = IRSENSE_I2C_ADDRESS_0;
}

IRSENSE_RETVAL irsense_init ( irsense_t *ctx, irsense_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return IRSENSE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->pdn, cfg->pdn );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return IRSENSE_OK;

}

void irsense_generic_write ( irsense_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void irsense_generic_read ( irsense_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void irsense_write_byte ( irsense_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = write_data;

    irsense_generic_write( ctx, reg_address, w_buffer, 1 );
}

uint8_t irsense_read_byte ( irsense_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 1 ];

    irsense_generic_read( ctx, reg_address, r_buffer, 1 );

    return r_buffer[ 0 ];
}

uint16_t irsense_read_data ( irsense_t *ctx, uint8_t reg_address_low )
{

    uint8_t r_buffer_low;
    uint8_t r_buffer_high;
    uint16_t result;

    r_buffer_low = irsense_read_byte( ctx, reg_address_low );
    r_buffer_high = irsense_read_byte( ctx, reg_address_low + 1 );

    result = r_buffer_high;
    result <<= 8;
    result |= r_buffer_low;
    
    return result;
}

void irsense_power_on ( irsense_t *ctx )
{
    digital_out_high( &ctx->pdn );
}

void irsense_power_off ( irsense_t *ctx )
{
    digital_out_low( &ctx->pdn );
}

uint8_t irsense_get_company_code ( irsense_t *ctx )
{
     uint8_t company_code;
     
     company_code = irsense_read_byte( ctx, IRSENSE_REG_WIA1 );
     
     return company_code;
}

uint8_t irsense_get_device_id ( irsense_t *ctx )
{
     uint8_t device_id;

     device_id = irsense_read_byte( ctx, IRSENSE_REG_WIA2 );

     return device_id;
}

uint8_t irsense_read_interrupt_status ( irsense_t *ctx )
{
    uint8_t int_status;

    int_status = irsense_read_byte( ctx, IRSENSE_REG_INTST );

    return int_status;
}

uint8_t irsense_get_status ( irsense_t *ctx )
{
    uint8_t status_val;

    status_val = irsense_read_byte( ctx, IRSENSE_REG_ST1 );

    return status_val;
}

void irsense_set_configuration ( irsense_t *ctx, uint8_t register_value )
{
     irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, register_value );
}

void irsense_set_mode ( irsense_t *ctx, uint8_t mode )
{
    uint8_t current_settings;
  
    mode &= 0x07;

    current_settings = irsense_read_byte( ctx, IRSENSE_REG_ECNTL1 );

    current_settings &= 0xF8;
    current_settings |= mode;
    
    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, current_settings );
}

void irsense_set_cutoff_frequency ( irsense_t *ctx, uint8_t frequency )
{
    uint8_t current_settings;
    frequency &= 0x38;
  
    if ( frequency > 0x28 )
    {
        frequency = 0x00;
    }
    
    current_settings = irsense_read_byte( ctx,IRSENSE_REG_ECNTL1 );

    current_settings &= 0xC7;
    current_settings |= frequency;
  
    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, current_settings );
}

uint8_t irsense_check_available ( irsense_t *ctx )
{
    uint8_t temp;
    
    temp = irsense_read_byte( ctx, IRSENSE_REG_ST1 );
    
    temp &= 0x01;
    
    return temp;
}

uint8_t irsense_check_overrun ( irsense_t *ctx )
{
    uint8_t temp;

    temp = irsense_read_byte( ctx, IRSENSE_REG_ST1 );
    
    temp >>= 1;
    temp &= 0x01;

    return temp;
}

void irsense_soft_reset ( irsense_t *ctx )
{
    irsense_write_byte( ctx, IRSENSE_REG_CNTL2, IRSENSE_CNTL2_SOFT_RESET );
}

void irsense_refresh ( irsense_t *ctx )
{
    uint8_t dummy;

    dummy = irsense_read_byte( ctx, IRSENSE_REG_ST2 );
}

int16_t irsense_get_ir1 ( irsense_t *ctx )
{
    uint16_t r_buffer;
    int16_t result;
    
    r_buffer = irsense_read_data( ctx, IRSENSE_REG_IR1_LOW );
    
    if ( r_buffer > 32767 )
    {
        result = r_buffer - 65535;
    }
    else
    {
        result = r_buffer;
    }
    
    return result;
}

int16_t irsense_get_ir2 ( irsense_t *ctx )
{
    uint16_t r_buffer;
    int16_t result;

    r_buffer = irsense_read_data( ctx, IRSENSE_REG_IR2_LOW );

    if ( r_buffer > 32767 )
    {
        result = r_buffer - 65535;
    }
    else
    {
        result = r_buffer;
    }

    return result;
}

int16_t irsense_get_ir3 ( irsense_t *ctx )
{
    uint16_t r_buffer;
    int16_t result;

    r_buffer = irsense_read_data( ctx, IRSENSE_REG_IR3_LOW );

    if ( r_buffer > 32767 )
    {
        result = r_buffer - 65535;
    }
    else
    {
        result = r_buffer;
    }

    return result;
}

int16_t irsense_get_ir4 ( irsense_t *ctx )
{
    uint16_t r_buffer;
    int16_t result;

    r_buffer = irsense_read_data( ctx, IRSENSE_REG_IR4_LOW );

    if ( r_buffer > 32767 )
    {
        result = r_buffer - 65535;
    }
    else
    {
        result = r_buffer;
    }

    return result;
}

void irsense_get_ir_sense ( irsense_t *ctx, irsense_ir_data_t *ir_data )
{
    ir_data->bottom_area = irsense_get_ir1( ctx );
    
    ir_data->left_area = irsense_get_ir2( ctx );
    
    ir_data->right_area = irsense_get_ir3( ctx );
    
    ir_data->top_area = irsense_get_ir4( ctx );
}

float irsense_get_temperature ( irsense_t *ctx )
{
    uint16_t r_temp;
    float temperature;
  
    r_temp = irsense_read_data( ctx, IRSENSE_REG_TMP_LOW );
  
    r_temp >>= 6;

    if ( r_temp > 511 )
    {
        temperature = ( ( float ) r_temp ) - 1023.0;
    }
    else
    {
        temperature = ( float ) r_temp;
    }

    temperature *= 0.125;
    temperature += 26.75;

    return temperature;
}

float irsense_get_temperature_f ( irsense_t *ctx )
{
    float temperature;
    
    temperature = irsense_get_temperature_f( ctx );
    
    temperature *= 1.8;
    temperature += 32.0;
    
    return temperature;
}

void irsense_set_threshold_ir2_ir4 ( irsense_t *ctx, uint8_t value )
{
    uint8_t k_high;
    uint8_t b_low;

    k_high = value >> 5;
    k_high &= 0x7F;
    b_low = value << 3;
    b_low &= 0xF8;

    irsense_write_byte( ctx, IRSENSE_REG_ETH24H_LOW, b_low );
    irsense_write_byte( ctx, IRSENSE_REG_ETH24H_HIGH, k_high );
}

uint16_t irsense_get_threshold_ir2_ir4 ( irsense_t *ctx )
{
    uint16_t current_settings;

    current_settings = irsense_read_data( ctx, IRSENSE_REG_ETH24H_LOW );

    return current_settings;
}

void irsense_set_threshold_eeprom_ir2_ir4 ( irsense_t *ctx, uint8_t value )
{
    uint8_t h_high;
    uint8_t v_low;
    uint8_t current_mode;
    uint8_t temp;

    h_high = value >> 6;
    v_low = value;
    v_low &= 0x3F;
    h_high &= 0x3F;
    v_low |= 0xC0;
    h_high |= 0xC0;

    current_mode = irsense_read_byte( ctx, IRSENSE_REG_ECNTL1 );
    temp = IRSENSE_ENABLE_EEPROM_MODE;
    temp |= ( current_mode & IRSENSE_ENABLE_SETTINGS_EEPROM_MODE );

    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, temp);

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_EKEY, IRSENSE_EEPROM_MAP_VAL_EKEY );

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_ETH24H_LOW, v_low );
    Delay_10ms( );
    Delay_10ms( );

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_EKEY, IRSENSE_EEPROM_MAP_VAL_EKEY );

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_ETH24H_HIGH, h_high );
    Delay_10ms( );
    Delay_10ms( );
    
    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, current_mode );
}

void irsense_set_threshold_ir1_ir3 ( irsense_t *ctx, uint8_t value )
{
    uint8_t k_high;
    uint8_t b_low;

    k_high = value >> 5;
    k_high &= 0x7F;
    b_low = value << 3;
    b_low &= 0xF8;

    irsense_write_byte( ctx, IRSENSE_REG_ETH13H_LOW, b_low );
    irsense_write_byte( ctx, IRSENSE_REG_ETH13H_HIGH, k_high );
}

uint16_t irsense_get_threshold_ir1_ir3 ( irsense_t *ctx )
{
    uint16_t current_settings;

    current_settings = irsense_read_data( ctx, IRSENSE_REG_ETH13H_LOW );

    return current_settings;
}

void irsense_set_threshold_eeprom_ir1_ir3( irsense_t *ctx, uint8_t value )
{
    uint8_t h_high;
    uint8_t v_low;
    uint8_t current_mode;
    uint8_t temp;

    h_high = value >> 6;
    v_low = value;
    v_low &= 0x3F;
    h_high &= 0x3F;
    v_low |= 0xC0;
    h_high |= 0xC0;

    current_mode = irsense_read_byte( ctx, IRSENSE_REG_ECNTL1 );
    temp = IRSENSE_ENABLE_EEPROM_MODE;
    temp |= ( current_mode & IRSENSE_ENABLE_SETTINGS_EEPROM_MODE );

    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, temp);

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_EKEY, IRSENSE_EEPROM_MAP_VAL_EKEY );

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_ETH13H_LOW, v_low );
    Delay_10ms( );
    Delay_10ms( );

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_EKEY, IRSENSE_EEPROM_MAP_VAL_EKEY );

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_ETH13H_HIGH, h_high );
    Delay_10ms( );
    Delay_10ms( );
    
    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, current_mode );
}

void irsense_read_threshold ( irsense_t *ctx, irsense_reg_t *reg )
{
    reg->eth24h = irsense_read_data( ctx, IRSENSE_REG_ETH24H_LOW );
    
    reg->eth24l = irsense_read_data( ctx, IRSENSE_REG_ETH24L_LOW );
    
    reg->eth13h = irsense_read_data( ctx, IRSENSE_REG_ETH13H_LOW );
    
    reg->eth13l = irsense_read_data( ctx, IRSENSE_REG_ETH13L_LOW );
}

void irsense_read_threshold_eeprom ( irsense_t *ctx, irsense_eeprom_t *eeprom )
{
    uint8_t current_mode;
    uint8_t temp;
    
    current_mode = irsense_read_byte( ctx, IRSENSE_REG_ECNTL1 );
    temp = IRSENSE_ENABLE_EEPROM_MODE;
    temp |= ( current_mode & IRSENSE_ENABLE_SETTINGS_EEPROM_MODE );
    

    irsense_write_byte(  ctx, IRSENSE_REG_ECNTL1, temp );
    
    eeprom->eeth24h = irsense_read_data( ctx, IRSENSE_EEPROM_MAP_ETH24H_LOW );
    
    eeprom->eeth24l = irsense_read_data( ctx, IRSENSE_EEPROM_MAP_ETH24L_LOW );
    
    eeprom->eeth13h = irsense_read_data( ctx, IRSENSE_EEPROM_MAP_ETH13H_LOW );
    
    eeprom->eeth13l = irsense_read_data( ctx, IRSENSE_EEPROM_MAP_ETH13L_LOW );

    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, current_mode );
}


void irsense_set_hysteresis_ir2_ir4 ( irsense_t *ctx, uint8_t value )
{
    value &= 0x1F;
    value |= 0xE0;

    irsense_write_byte( ctx, IRSENSE_REG_EHYS24, value );
}

void irsense_set_hysteresis_eeprom_ir2_ir4 ( irsense_t *ctx, uint8_t value )
{
    uint8_t current_mode;
    uint8_t temp;
    
    value &= 0x1F;
    value |= 0xE0;
    
    current_mode = irsense_read_byte( ctx, IRSENSE_REG_ECNTL1 );
    temp = IRSENSE_ENABLE_EEPROM_MODE;
    temp |= ( current_mode & IRSENSE_ENABLE_SETTINGS_EEPROM_MODE );
    
    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, temp );
    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_EKEY, IRSENSE_EEPROM_MAP_VAL_EKEY );

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_EHYS24, value );
    Delay_10ms( );
    Delay_10ms( );
    
    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, current_mode );
}

void irsense_set_hysteresis_ir1_ir3 ( irsense_t *ctx, uint8_t value )
{
    value &= 0x1F;
    value |= 0xE0;

    irsense_write_byte( ctx, IRSENSE_REG_EHYS13, value );
}

void irsense_set_hysteresis_eeprom_ir1_ir3 (irsense_t *ctx, uint8_t value )
{
    uint8_t current_mode;
    uint8_t temp;

    value &= 0x1F;
    value |= 0xE0;

    current_mode = irsense_read_byte( ctx, IRSENSE_REG_ECNTL1 );
    temp = IRSENSE_ENABLE_EEPROM_MODE;
    temp |= ( current_mode & IRSENSE_ENABLE_SETTINGS_EEPROM_MODE );

    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, temp );
    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_EKEY, IRSENSE_EEPROM_MAP_VAL_EKEY );

    irsense_write_byte( ctx, IRSENSE_EEPROM_MAP_EHYS13, value );
    Delay_10ms( );
    Delay_10ms( );

    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, current_mode );
}

void irsense_read_hysteresis ( irsense_t *ctx, uint8_t *ehys24, uint8_t *ehys13 )
{
    *ehys24 = irsense_read_byte( ctx, IRSENSE_EEPROM_MAP_EHYS24 );
    
    *ehys24 = irsense_read_byte( ctx, IRSENSE_EEPROM_MAP_EHYS13 );
}

void irsense_read_hysteresis_eeprom ( irsense_t *ctx, uint8_t *eehys24, uint8_t *eehys13 )
{
    uint8_t current_settings;
    uint8_t temp;

    current_settings = irsense_read_byte( ctx, IRSENSE_REG_ECNTL1 );
    temp = IRSENSE_ENABLE_EEPROM_MODE;
    temp |= ( current_settings & IRSENSE_ENABLE_SETTINGS_EEPROM_MODE );

    irsense_write_byte(  ctx, IRSENSE_REG_ECNTL1, temp );

    *eehys24 = irsense_read_byte( ctx, IRSENSE_EEPROM_MAP_EHYS24 );

    *eehys13 = irsense_read_byte( ctx, IRSENSE_EEPROM_MAP_EHYS13 );

    irsense_write_byte( ctx, IRSENSE_REG_ECNTL1, current_settings );
}

void irsense_set_interrupts_reg ( irsense_t *ctx, irsense_eint_t *eint )
{
    uint8_t temp;
    
    temp = IRSENSE_EINTEN_RESET_VALUE;
    temp |= ( ( eint->ir13h << 4 ) | ( eint->ir13l << 3 ) | ( eint->ir24h << 2 ) | ( eint->ir24l << 1 ) | eint->dr );
    
    irsense_write_byte( ctx, IRSENSE_REG_EINTEN, temp );
}

void irsense_enable_data_ready_interrupt ( irsense_t *ctx )  
{
    irsense_write_byte( ctx, IRSENSE_REG_EINTEN,  IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE
                                                | IRSENSE_EINTEN_IR13_LOW_INT_DISABLE
                                                | IRSENSE_EINTEN_IR24_HIGH_INT_DISABLE
                                                | IRSENSE_EINTEN_IR24_LOW_INT_DISABLE
                                                | IRSENSE_EINTEN_DRI_INT_ENABLE );
}

uint8_t irsense_check_int_states ( irsense_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}
// ------------------------------------------------------------------------- END

