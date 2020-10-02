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

#include "captouch5.h"


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void captouch5_cfg_setup ( captouch5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CAPTOUCH5_I2C_SLAVE_ADDRESS;
}

CAPTOUCH5_RETVAL captouch5_init ( captouch5_t *ctx, captouch5_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CAPTOUCH5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return CAPTOUCH5_OK;

}


void captouch5_config_sensors ( captouch5_t *ctx, uint16_t sens_data )
{
    captouch5_write_two_bytes(ctx, CAPTOUCH5_REG_SENSOR_EN, ( sens_data || 0x05));
    captouch5_write_two_bytes(ctx, CAPTOUCH5_REG_FSS_EN, 0x000F);
}

void captouch5_config_slider ( captouch5_t *ctx, uint8_t slider_data )
{
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER_CFG, 0x02 );
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER1_CFG, slider_data );
 
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER1_THRESHOLD, 200 );
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER1_RESOLUTION, 0x01 );
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER_NT, 84 );
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER_NNT, 84 );
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER_LBR, 50 );
 
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER2_CFG, slider_data );
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER2_THRESHOLD, 200 );
    captouch5_write_byte( ctx, CAPTOUCH5_REG_SLIDER2_RESOLUTION, 0x01 );

    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD6,  200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD7,  200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD8,  200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD9,  200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD10, 200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD11, 200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD12, 200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD13, 200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD14, 200 );
    captouch5_write_two_bytes( ctx, CAPTOUCH5_REG_FINGER_THRESHOLD15, 200 );
}


void captouch5_device_config ( captouch5_t *ctx, T_CAPTOUCH5_DEVICE_CONFIG *device_cfg )
{
    uint8_t cfg_temp;

    device_cfg->cfg0.iirFilter = CAPTOUCH5_CFG0_IIR_FILTER_ENABLED;
    device_cfg->cfg0.medFilter = CAPTOUCH5_CFG0_MED_FILTER_ENABLED;
    device_cfg->cfg1.sysDiagnostic = CAPTOUCH5_CFG1_SYS_DIAGNOSTIC_ENABLED;
    device_cfg->cfg2.proximityAutoReset = CAPTOUCH5_CFG2_PROXIMIYU_AUTO_RESET_DISABLED;
    device_cfg->cfg2.buttonAutoReset = CAPTOUCH5_CFG2_BUTTON_SLIDER_AUTO_RESET_DISABLED;
    device_cfg->cfg2.autoThreshold = CAPTOUCH5_CFG2_AUTOMATIC_THRESHOLD_DISABLED;
    device_cfg->cfg2.emcSolution = CAPTOUCH5_CFG2_EMC_DISABLED;
    device_cfg->cfg2.guardSens = CAPTOUCH5_CFG2_GUARD_SENS_ENABLED;
    device_cfg->cfg2.shieldSens = CAPTOUCH5_CFG2_SHIELD_ENABLED;
    device_cfg->cfg3.powerSupply = CAPTOUCH5_CFG3_POWER_SUPPLY_EXTERNALLY;
    
    cfg_temp = 0x00;

    cfg_temp = device_cfg->cfg0->medFilter;
    cfg_temp <<= 1;
    cfg_temp |= device_cfg->cfg0->iirFilter;
    captouch5_write_byte( ctx, CAPTOUCH5_REG_DEVICE_CFG0, cfg_temp );

    cfg_temp = 0x00;

    cfg_temp = device_cfg->cfg1->sysDiagnostic;
    captouch5_write_byte( ctx, CAPTOUCH5_REG_DEVICE_CFG1, cfg_temp );

    cfg_temp = 0x00;

    cfg_temp = device_cfg->cfg2->proximityAutoReset;
    cfg_temp <<= 6;
    cfg_temp |= device_cfg->cfg2->buttonAutoReset;
    cfg_temp <<= 4;
    cfg_temp |= device_cfg->cfg2->autoThreshold;
    cfg_temp <<= 3;
    cfg_temp |= device_cfg->cfg2->emcSolution;
    cfg_temp <<= 2;
    cfg_temp |= device_cfg->cfg2->guardSens;
    cfg_temp <<= 1;
    cfg_temp |= device_cfg->cfg2->shieldSens;
    captouch5_write_byte( ctx, CAPTOUCH5_REG_DEVICE_CFG2, cfg_temp );

    cfg_temp = 0x00;

    cfg_temp = device_cfg->cfg3->powerSupply;
    captouch5_write_byte( ctx, CAPTOUCH5_REG_DEVICE_CFG3, cfg_temp );
}

void captouch5_default_cfg ( captouch5_t *ctx, T_CAPTOUCH5_DEVICE_CONFIG *device_cfg )
{
    captouch5_config_sensors( ctx, CAPTOUCH5_BUTTON_SENS_ENABLED );
    captouch5_config_slider( ctx, CAPTOUCH5_SLIDER_SENS_0p4 );
    captouch5_device_config( ctx, device_cfg );
}

void captouch5_generic_write ( captouch5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void captouch5_generic_read ( captouch5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}


uint16_t captouch5_read_two_bytes ( captouch5_t *ctx, uint8_t reg_addr )
 {
    uint8_t buf[ 2 ];
    uint16_t two_bytes;

    captouch5_generic_read(ctx, reg_addr, buf, 2);

    two_bytes = buf[ 1 ];
    two_bytes <<= 8;
    two_bytes |= buf[ 0 ];

    return two_bytes;
 }


void captouch5_write_two_bytes ( captouch5_t *ctx, uint8_t reg_addr, uint16_t data_buf )
 {
    uint8_t buf[ 2 ];
    
    buf[ 0 ] = data_buf >> 8;
    buf[ 1 ] = data_buf;

    captouch5_generic_write( ctx, reg_addr, buf, 2);
 }

uint8_t captouch5_read_byte ( captouch5_t *ctx, uint8_t reg_addr )
 {
    uint8_t byte;

    captouch5_generic_read(ctx, reg_addr, &byte, 1);

    return byte;
 
 }

void captouch5_write_byte ( captouch5_t *ctx, uint8_t reg_addr, uint8_t data_buf )
 {
    captouch5_generic_write(ctx, reg_addr, &data_buf, 1);
 }

uint8_t captouch5_process ( captouch5_t *ctx )
 {
    return captouch5_read_byte( ctx, CAPTOUCH5_REG_CTRL_CMD_STATUS );
 }

uint16_t captouch5_get_device_id ( captouch5_t *ctx )
{
    return captouch5_read_two_bytes( ctx, CAPTOUCH5_REG_DEVICE_ID );
}

uint8_t captouch5_get_family_id ( captouch5_t *ctx )
{
    return captouch5_read_byte( ctx, CAPTOUCH5_REG_FAMILY_ID );
}

void captouch5_read_button_status ( captouch5_t *ctx, T_CAPTOUCH5_BUTTONS *buttons )
{
    uint16_t temp;

    temp = captouch5_read_two_bytes( ctx, CAPTOUCH5_REG_BUTTON_STAT );

    buttons->button1 = ( temp >> 3 ) & 0x01;
    buttons->button2 = temp  & 0x01;
    buttons->button3 = ( temp >> 2 ) & 0x01;
    buttons->button4 = ( temp >> 1 ) & 0x01;
}

uint16_t captouch5_read_slider_position ( captouch5_t *ctx )
{
    uint16_t slider;

    slider = captouch5_read_byte( ctx, CAPTOUCH5_REG_SLIDER2_POSITION );
    slider <<= 8;
    slider |= captouch5_read_byte( ctx, CAPTOUCH5_REG_SLIDER1_POSITION );

    return slider;
}

void captouch5_software_reset ( captouch5_t *ctx )
{
    captouch5_write_byte( ctx, CAPTOUCH5_REG_CTRL_CMD, 255 );
}

// ------------------------------------------------------------------------- END

