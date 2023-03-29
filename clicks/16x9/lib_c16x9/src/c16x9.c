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

#include "c16x9.h"

// ------------------------------------------------------------------ VARIABLES

static const uint16_t demo_matrix[ 127 ][ 9 ] =
{
        { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char
        { 0x0000, 0x0000, 0x0000, 0x3BFC, 0x3BFC, 0x3BFC, 0x0000, 0x0000, 0x0000},  // Code for char !
        { 0x0000, 0x0000, 0x0038, 0x0038, 0x0000, 0x0038, 0x0038, 0x0000, 0x0000},  // Code for char "
        { 0x0000, 0x0720, 0x01E0, 0x0138, 0x0720, 0x01E0, 0x0138, 0x0000, 0x0000},  // Code for char #
        { 0x0000, 0x0000, 0x0270, 0x04C8, 0x0FFC, 0x04C8, 0x0390, 0x0000, 0x0000},  // Code for char $
        { 0x0078, 0x0048, 0x0678, 0x0180, 0x0060, 0x0798, 0x0480, 0x0780, 0x0000},  // Code for char %
        { 0x0300, 0x07B0, 0x04F8, 0x04C8, 0x07B8, 0x0730, 0x0580, 0x0000, 0x0000},  // Code for char &
        { 0x0000, 0x0038, 0x0038, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char '
        { 0x0000, 0x03E0, 0x0FF0, 0x1818, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char (
        { 0x0000, 0x1808, 0x0FF0, 0x03C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char )
        { 0x0000, 0x0050, 0x0038, 0x0050, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char *
        { 0x0000, 0x0020, 0x0020, 0x00F8, 0x0020, 0x0020, 0x0000, 0x0000, 0x0000},  // Code for char +
        { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2C00, 0x1C00, 0x0000, 0x0000},  // Code for char ,
        { 0x0000, 0x0000, 0x0000, 0x0100, 0x0100, 0x0100, 0x0000, 0x0000, 0x0000},  // Code for char -
        { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3000, 0x3000, 0x0000, 0x0000},  // Code for char .
        { 0x0000, 0x0000, 0x0600, 0x01E0, 0x0018, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char /
        { 0x0000, 0x0000, 0x03F0, 0x07F8, 0x0408, 0x07F8, 0x03F0, 0x0000, 0x0000},  // Code for char 0
        { 0x0000, 0x0000, 0x0060, 0x0030, 0x07F8, 0x07F8, 0x0000, 0x0000, 0x0000},  // Code for char 1
        { 0x0000, 0x0000, 0x0610, 0x0718, 0x0588, 0x04F8, 0x0470, 0x0000, 0x0000},  // Code for char 2
        { 0x0000, 0x0000, 0x0210, 0x0618, 0x0448, 0x07F8, 0x03B0, 0x0000, 0x0000},  // Code for char 3
        { 0x0000, 0x0000, 0x0180, 0x0160, 0x0110, 0x07F8, 0x07F8, 0x0100, 0x0000},  // Code for char 4
        { 0x0000, 0x0000, 0x02E0, 0x0678, 0x0458, 0x07C8, 0x0388, 0x0000, 0x0000},  // Code for char 5
        { 0x0000, 0x03F0, 0x07F8, 0x0448, 0x07D8, 0x0390, 0x0000, 0x0000, 0x0000},  // Code for char 6
        { 0x0000, 0x0000, 0x0008, 0x0788, 0x07E8, 0x0078, 0x0018, 0x0000, 0x0000},  // Code for char 7
        { 0x0000, 0x03B0, 0x07F8, 0x0448, 0x07F8, 0x03B0, 0x0000, 0x0000, 0x0000},  // Code for char 8
        { 0x0000, 0x0270, 0x06F8, 0x0488, 0x07F8, 0x03F0, 0x0000, 0x0000, 0x0000},  // Code for char 9
        { 0x0000, 0x0000, 0x0660, 0x0660, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char :
        { 0x0000, 0x0000, 0x0B30, 0x0730, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char ;
        { 0x0000, 0x0000, 0x0180, 0x0180, 0x0240, 0x0240, 0x0420, 0x0000, 0x0000},  // Code for char <
        { 0x0000, 0x0000, 0x0140, 0x0140, 0x0140, 0x0140, 0x0140, 0x0000, 0x0000},  // Code for char =
        { 0x0000, 0x0000, 0x0210, 0x0120, 0x0120, 0x00C0, 0x00C0, 0x0000, 0x0000},  // Code for char >
        { 0x0000, 0x0000, 0x0010, 0x0698, 0x06C8, 0x0078, 0x0030, 0x0000, 0x0000},  // Code for char ?
        { 0x03C0, 0x0C30, 0x0B90, 0x1468, 0x1428, 0x1628, 0x17E8, 0x1468, 0x0A10},  // Code for char @
        { 0x0000, 0x0700, 0x07E0, 0x01F8, 0x0118, 0x01F8, 0x07E0, 0x0700, 0x0000},  // Code for char A
        { 0x0000, 0x03FC, 0x03FC, 0x0224, 0x0224, 0x03FC, 0x01D8, 0x0000, 0x0000},  // Code for char B
        { 0x0000, 0x00F0, 0x01F8, 0x030C, 0x0204, 0x0204, 0x030C, 0x0108, 0x0000},  // Code for char C
        { 0x0000, 0x07F8, 0x07F8, 0x0408, 0x0408, 0x07F8, 0x03F0, 0x0000, 0x0000},  // Code for char D
        { 0x0000, 0x07F8, 0x07F8, 0x0448, 0x0448, 0x0448, 0x0000, 0x0000, 0x0000},  // Code for char E
        { 0x0000, 0x07F8, 0x07F8, 0x0048, 0x0048, 0x0048, 0x0000, 0x0000, 0x0000},  // Code for char F
        { 0x0000, 0x01E0, 0x03F0, 0x0618, 0x0408, 0x0488, 0x0798, 0x0390, 0x0000},  // Code for char G
        { 0x0000, 0x07F8, 0x07F8, 0x0040, 0x0040, 0x07F8, 0x07F8, 0x0000, 0x0000},  // Code for char H
        { 0x0000, 0x0000, 0x07F8, 0x07F8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char I
        { 0x0000, 0x0200, 0x0600, 0x0400, 0x07F8, 0x03F8, 0x0000, 0x0000, 0x0000},  // Code for char J
        { 0x0000, 0x07F8, 0x07F8, 0x00C0, 0x01F0, 0x07B8, 0x0608, 0x0000, 0x0000},  // Code for char K
        { 0x0000, 0x07F8, 0x07F8, 0x0400, 0x0400, 0x0400, 0x0400, 0x0000, 0x0000},  // Code for char L
        { 0x07F8, 0x07F8, 0x0078, 0x03F8, 0x0700, 0x03E0, 0x0078, 0x07F8, 0x07F8},  // Code for char M
        { 0x0000, 0x07F8, 0x07F8, 0x0060, 0x0180, 0x07F8, 0x07F8, 0x0000, 0x0000},  // Code for char N
        { 0x0000, 0x01E0, 0x03F0, 0x0618, 0x0408, 0x0618, 0x03F0, 0x01E0, 0x0000},  // Code for char O
        { 0x0000, 0x07F8, 0x07F8, 0x0088, 0x0088, 0x00F8, 0x0070, 0x0000, 0x0000},  // Code for char P
        { 0x0000, 0x01E0, 0x03F0, 0x0618, 0x0508, 0x0618, 0x07F0, 0x09E0, 0x0000},  // Code for char Q
        { 0x0000, 0x07F8, 0x07F8, 0x0088, 0x0188, 0x03F8, 0x0670, 0x0400, 0x0000},  // Code for char R
        { 0x1380, 0x33C0, 0x2640, 0x2640, 0x3CC0, 0x1C80, 0x0000, 0x0000, 0x0000},  // Code for char S
        { 0x0000, 0x0008, 0x0008, 0x07F8, 0x07F8, 0x0008, 0x0008, 0x0000, 0x0000},  // Code for char T
        { 0x0000, 0x03F8, 0x07F8, 0x0400, 0x0400, 0x07F8, 0x03F8, 0x0000, 0x0000},  // Code for char U
        { 0x0000, 0x0018, 0x01F8, 0x07E0, 0x0600, 0x07E0, 0x01F8, 0x0018, 0x0000},  // Code for char V
        { 0x01F8, 0x07E0, 0x0700, 0x01F0, 0x0038, 0x01F0, 0x0700, 0x07E0, 0x01F8},  // Code for char W
        { 0x0000, 0x0618, 0x0738, 0x01E0, 0x01E0, 0x0738, 0x0618, 0x0000, 0x0000},  // Code for char X
        { 0x0000, 0x0018, 0x0078, 0x07C0, 0x07C0, 0x0078, 0x1800, 0x0000, 0x0000},  // Code for char Y
        { 0x0000, 0x0608, 0x0708, 0x05C8, 0x04E8, 0x0438, 0x0418, 0x0000, 0x0000},  // Code for char Z
        { 0x0000, 0x1FF8, 0x1FF8, 0x1008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char [
        { 0x0000, 0x0018, 0x01E0, 0x0600, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char BackSlash
        { 0x0000, 0x0000, 0x1008, 0x1FF8, 0x1FF8, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char ]
        { 0x0000, 0x0040, 0x0070, 0x0018, 0x0070, 0x0040, 0x0000, 0x0000, 0x0000},  // Code for char ^
        { 0x0000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000},  // Code for char _
        { 0x0000, 0x0008, 0x0018, 0x0010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char `
        { 0x0000, 0x00D0, 0x01E8, 0x0128, 0x01F8, 0x01F0, 0x0000, 0x0000, 0x0000},  // Code for char a
        { 0x0000, 0x07F8, 0x07F8, 0x0420, 0x0420, 0x07E0, 0x03C0, 0x0000, 0x0000},  // Code for char b
        { 0x0000, 0x00F0, 0x01F8, 0x0108, 0x0198, 0x0090, 0x0000, 0x0000, 0x0000},  // Code for char c
        { 0x0000, 0x03C0, 0x07E0, 0x0420, 0x0420, 0x07F8, 0x07F8, 0x0000, 0x0000},  // Code for char d
        { 0x0000, 0x00F0, 0x01F8, 0x0128, 0x0128, 0x01B8, 0x00B0, 0x0000, 0x0000},  // Code for char e
        { 0x0000, 0x07F0, 0x07F8, 0x0028, 0x0008, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char f
        { 0x0000, 0x02F0, 0x05F8, 0x0508, 0x0508, 0x07F8, 0x03F8, 0x0000, 0x0000},  // Code for char g
        { 0x0000, 0x07F8, 0x07F8, 0x0020, 0x0020, 0x07E0, 0x07C0, 0x0000, 0x0000},  // Code for char h
        { 0x0000, 0x07E8, 0x07E8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char i
        { 0x0000, 0x3000, 0x2000, 0x3FD8, 0x1FD8, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char j
        { 0x0000, 0x07F8, 0x07F8, 0x0180, 0x03C0, 0x0760, 0x0420, 0x0000, 0x0000},  // Code for char k
        { 0x0000, 0x07F8, 0x07F8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char l
        { 0x01F8, 0x01F8, 0x0008, 0x0008, 0x01F8, 0x01F8, 0x0008, 0x0008, 0x01F8},  // Code for char m
        { 0x0000, 0x01F8, 0x01F8, 0x0008, 0x0008, 0x01F8, 0x01F0, 0x0000, 0x0000},  // Code for char n
        { 0x0000, 0x00F0, 0x01F8, 0x0108, 0x0108, 0x01F8, 0x00F0, 0x0000, 0x0000},  // Code for char o
        { 0x0000, 0x07F8, 0x07F8, 0x0108, 0x0108, 0x01F8, 0x00F0, 0x0000, 0x0000},  // Code for char p
        { 0x0000, 0x00F0, 0x01F8, 0x0108, 0x0108, 0x07F8, 0x07F8, 0x0000, 0x0000},  // Code for char q
        { 0x0000, 0x01F8, 0x01F8, 0x0008, 0x0008, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char r
        { 0x0000, 0x00B0, 0x01B8, 0x0168, 0x0168, 0x01D8, 0x00D0, 0x0000, 0x0000},  // Code for char s
        { 0x0000, 0x0020, 0x03F0, 0x07F8, 0x0420, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char t
        { 0x0000, 0x00F8, 0x01F8, 0x0100, 0x0100, 0x01F8, 0x01F8, 0x0000, 0x0000},  // Code for char u
        { 0x0000, 0x0078, 0x01F8, 0x0180, 0x01F8, 0x0078, 0x0000, 0x0000, 0x0000},  // Code for char v
        { 0x0038, 0x01F8, 0x01C0, 0x00F0, 0x0038, 0x00F0, 0x01C0, 0x01F8, 0x0038},  // Code for char w
        { 0x0000, 0x0198, 0x01F8, 0x0060, 0x01F8, 0x0198, 0x0000, 0x0000, 0x0000},  // Code for char x
        { 0x0000, 0x0478, 0x07F0, 0x0380, 0x01F0, 0x0078, 0x0008, 0x0000, 0x0000},  // Code for char y
        { 0x0000, 0x0188, 0x01C8, 0x0168, 0x0138, 0x0118, 0x0000, 0x0000, 0x0000},  // Code for char z
        { 0x0000, 0x0FF0, 0x1EF8, 0x1008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char {
        { 0x0000, 0x1FF8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char |
        { 0x0000, 0x1008, 0x1EF8, 0x0FF0, 0x0100, 0x0000, 0x0000, 0x0000, 0x0000},  // Code for char }
        { 0x0000, 0x0010, 0x0008, 0x0008, 0x0010, 0x0008, 0x0000, 0x0000, 0x0000},  // Code for char ~
        { 0x0000, 0x0000, 0x07F8, 0x07F8, 0x07F8, 0x07F8, 0x0000, 0x0000, 0x0000}   // Code for char 
};

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c16x9_cfg_setup ( c16x9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->sdb   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C16X9_SLAVE_ADDRESS;
}

C16X9_RETVAL c16x9_init ( c16x9_t *ctx, c16x9_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
     i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_SUCCESS )
    {
        return C16X9_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->sdb, cfg->sdb );
    digital_out_high( &ctx->sdb );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return C16X9_OK;
}

void c16x9_generic_write ( c16x9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void c16x9_control_all ( c16x9_t *ctx, uint8_t ctrl, uint8_t state )
{
    uint8_t tx_reg;
    uint8_t tx_buf[ 20 ];
    uint8_t cnt;

    // Select register

    if ( ctrl == C16X9_CTRL_LED )
    {
        tx_reg = 0x00;
    }
    else
    {
        tx_reg = 0x12;
    }

    // Buffer storage

    for ( cnt = 0; cnt < 18; cnt++ )
    {
        if ( state == 1 )
        {
            tx_buf[ cnt ] = 0xFF;
        }
        else
        {
            tx_buf[ cnt ] = 0x00;
        }
    }

    c16x9_generic_write( ctx, tx_reg, tx_buf, 18 );
}

void c16x9_fill_screen ( c16x9_t *ctx, uint8_t pwm )
{
    uint8_t cnt;
    uint8_t tx_buf[145];

    for ( cnt = 0; cnt < 145; cnt++ )
    {
        tx_buf[ cnt ] = pwm;
    }

    c16x9_generic_write( ctx, 0x24, tx_buf, 145 );
}

void c16x9_display_refresh ( c16x9_t *ctx )
{
    uint8_t tmp;

    tmp = C16X9_SHUTDOWN_MODE;
    c16x9_generic_write( ctx, C16X9_REG_SHUTDOWN, &tmp, 1 );

    tmp = C16X9_POINT_TO_PAGE_ONE;
    c16x9_generic_write( ctx, C16X9_REG_COMMAND, &tmp, 1 );

    c16x9_control_all( ctx, C16X9_CTRL_LED, 1 );

    c16x9_fill_screen( ctx, 0x00 );

    tmp = C16X9_POINT_TO_PAGE_NINE;
    c16x9_generic_write( ctx, C16X9_REG_COMMAND, &tmp, 1 );

    tmp = C16X9_NORMAL_OPERATION;
    c16x9_generic_write( ctx, C16X9_REG_SHUTDOWN, &tmp, 1 );
}

void c16x9_draw_point ( c16x9_t *ctx, c16x9_point_t *point )
{
    uint8_t tx_reg;
    uint8_t tx_data;

    if ( point->x > 8 || point->y > 15 )
    {
        return;
    }

    tx_reg = 0x24 + point->x * 16 + point->y;
    tx_data = point->pwm;

    c16x9_generic_write( ctx, tx_reg, &tx_data, 1 );
}


void c16x9_display_image ( c16x9_t *ctx, c16x9_image_t *image )
{
    c16x9_point_t point;

    uint8_t cnt;
    uint8_t tmp;
    uint16_t demo_display;
    uint16_t cnt_pos;
    uint16_t demo_pixel;

    for ( cnt_pos = 0; cnt_pos <= 8; cnt_pos++ )
    {
        demo_display = image->buf[ cnt_pos ];

        for ( cnt = 0; cnt < 16; cnt++ )
        {
            demo_pixel = demo_display & ( 0x8000 >> cnt );

            if ( demo_pixel != 0 )
            {
                tmp = C16X9_POINT_TO_PAGE_ONE;
                c16x9_generic_write( ctx, C16X9_REG_COMMAND, &tmp, 1 );

                point.x   = cnt_pos;
                point.y   = cnt;
                point.pwm = image->pwm;
                c16x9_draw_point( ctx, &point );

                tmp = C16X9_POINT_TO_PAGE_NINE;
                c16x9_generic_write( ctx, C16X9_REG_COMMAND, &tmp, 1 );

                tmp = image->frame;
                c16x9_generic_write( ctx, C16X9_REG_PICTURE_DISPLAY, &tmp, 1 );
            }
        }
    }
}

void c16x9_display_byte ( c16x9_t *ctx, c16x9_char_t *data_char )
{
    c16x9_point_t point;

    uint8_t cnt_pos;
    uint8_t cnt;
    uint8_t tmp;
    uint16_t demo_display;
    uint16_t demo_pixel;
    uint8_t demo_byte;

    demo_byte = data_char->character - 32;

    for ( cnt_pos = 0; cnt_pos <= 8; cnt_pos++ )
    {
        demo_display = demo_matrix[ demo_byte ][ cnt_pos ];

        for ( cnt = 0; cnt < 16; cnt++ )
        {
            demo_pixel = demo_display & ( 0x8000 >> cnt );

            if ( demo_pixel != 0 )
            {
                tmp = C16X9_POINT_TO_PAGE_ONE;
                c16x9_generic_write( ctx, C16X9_REG_COMMAND, &tmp, 1 );

                point.x   = cnt_pos;
                point.y   = cnt;
                point.pwm = data_char->pwm;

                c16x9_draw_point( ctx, &point );

                tmp = C16X9_POINT_TO_PAGE_NINE;
                c16x9_generic_write( ctx, C16X9_REG_COMMAND, &tmp, 1 );

                tmp = data_char->frame;
                c16x9_generic_write( ctx, C16X9_REG_PICTURE_DISPLAY, &tmp, 1 );
            }
        }
    }
}

void c16x9_draw_rectangle( c16x9_t *ctx,  c16x9_rectangle_t *rectangle )
{
    uint8_t cnt;
    uint8_t cnt_pwm;
    uint8_t w;
    uint8_t h;

    uint8_t tmp;
    uint8_t tx_reg;
    uint8_t tx_buf[256];

    if ( rectangle->width > 9 )
    {
        w = 9;
    }
    else
    {
        w = rectangle->x + rectangle->width;
    }

    if ( rectangle->height > 16 )
    {
        h = 16;
    }
    else
    {
        h = rectangle->y + rectangle->height;
    }

    tmp = C16X9_POINT_TO_PAGE_ONE;
    c16x9_generic_write( ctx, C16X9_REG_COMMAND, &tmp, 1 );

    for ( cnt = 0; cnt < w; cnt++ )
    {
        tx_reg = 0x24 + ( rectangle->x + cnt ) * 16 + rectangle->y;

        for ( cnt_pwm = 1; cnt_pwm <= h; cnt_pwm++ )
        {
            tx_buf[ cnt_pwm ] = rectangle->pwm;
        }

        c16x9_generic_write( ctx, tx_reg, tx_buf, h );
    }

    tmp = C16X9_POINT_TO_PAGE_NINE;
    c16x9_generic_write( ctx, C16X9_REG_COMMAND, &tmp, 1 );

    tmp = rectangle->frame;
    c16x9_generic_write( ctx, C16X9_REG_PICTURE_DISPLAY, &tmp, 1 );
}

uint8_t c16x9_get_interrupt_state( c16x9_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

