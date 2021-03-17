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

#include "c4dotmatrixr.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c4dotmatrixr_cfg_setup ( c4dotmatrixr_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x20;
}

C4DOTMATRIXR_RETVAL c4dotmatrixr_init ( c4dotmatrixr_t *ctx, c4dotmatrixr_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return C4DOTMATRIXR_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return C4DOTMATRIXR_OK;

}

void c4dotmatrixr_default_cfg ( c4dotmatrixr_t *ctx )
{
    uint8_t buffer[ 3 ];

    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->pwm );
    Delay_100ms( );

   // start with IODIRA and write 2 bytes

    buffer[ 0 ] = 0x00;            // PORTA as output
    buffer[ 1 ] = 0x00;            // PORTB as output
    
    c4dotmatrixr_generic_write( ctx, C4DOT_IODIRA, buffer, 2 );
}

void c4dotmatrixr_generic_write ( c4dotmatrixr_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void c4dotmatrixr_generic_read ( c4dotmatrixr_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void c4dot_write_char ( c4dotmatrixr_t *ctx, uint8_t char_num, uint8_t char_value )
{
    uint8_t buffer[ 1 ];

    // Return if charNum or charValue are invalid.

    if ( ( char_num > 3 ) || char_value > 127 )
        return;

    buffer[ 0 ] = char_num;

    c4dotmatrixr_generic_write( ctx, C4DOT_OLATA, buffer, 1 );

    Delay_1us( );

    // enable write

    digital_out_low( &ctx->cs );           
    Delay_1us( );
    
    buffer[ 0 ] = char_value;
    
    c4dotmatrixr_generic_write( ctx, C4DOT_OLATB, buffer, 1 );
    Delay_1us( );

    // disable write

    digital_out_high( &ctx->cs );          
    Delay_1us( );
}

void c4dot_write_char0 ( c4dotmatrixr_t *ctx, uint8_t char_value )
{
    c4dot_write_char( ctx, 0, char_value );
}

void c4dot_write_char1 ( c4dotmatrixr_t *ctx, uint8_t char_value )
{
    c4dot_write_char( ctx, 1, char_value );
}

void c4dot_write_char2 ( c4dotmatrixr_t *ctx, uint8_t char_value )
{
    c4dot_write_char( ctx, 2, char_value );
}

void c4dot_write_char3 ( c4dotmatrixr_t *ctx, uint8_t char_value)
{
    c4dot_write_char( ctx, 3, char_value );
}

void c4dot_write_text ( c4dotmatrixr_t *ctx, uint8_t *text_to_write )
{
    uint16_t text_length;
    uint8_t index;

    text_length = strlen( text_to_write );

    // Clip text length so it fits on four characters.

    if ( text_length > 4 )
        text_length = 4;

    // Write the characters of the given text.

    for ( index = 0; index < ( uint8_t )text_length; index++ )
        c4dot_write_char( ctx, 3 - index, text_to_write[ index ] );
    
    // Fill the remaining characters with whitespace.

    while ( index < 4 )
        c4dot_write_char( ctx, index++, ' ' );
}

void c4dot_write_int ( c4dotmatrixr_t *ctx, int16_t int_to_write, uint8_t int_base )
{
    uint8_t digit_to_write;
    uint8_t index;

    // 0 - positive; 1 - negative

    uint8_t sign; 


     // start at the rightmost position
    index = 0;

    sign = 0;

    // Is the number zero?

    if ( int_to_write == 0 )
    {
        c4dot_write_char3( ctx,' ');
        c4dot_write_char2( ctx, ' ');
        c4dot_write_char1( ctx, ' ');
        c4dot_write_char0( ctx, '0');

        return;
    }

    // Is the number negative?

    if ( int_to_write < 0 )
    {
        sign = 1;
        int_to_write = -int_to_write;
    }

    while ( int_to_write > 0 )
    {
        // Get the next digit to write.

        digit_to_write = int_to_write % int_base;
        if (digit_to_write > 9)
            digit_to_write += -10 + 'A';
        else
            digit_to_write += '0';
        int_to_write /= int_base;

        c4dot_write_char( ctx, index++, digit_to_write );

        // Break if there's no more space to write the digits.

        if ( index == 4 )
            break;
    }

    // Is there space left?

    if ( index < 4 )
    {
        // Fill the first space with either '-' or ' '.

        if (sign == 1)
            c4dot_write_char( ctx, index++, '-');
        else
            c4dot_write_char( ctx, index++,' ');
            
        // Fill the remaining spaces.

        while ( index < 4 )
            c4dot_write_char( ctx, index++, ' ' );
    }
}

void c4dot_write_int_bin ( c4dotmatrixr_t *ctx, int16_t int_to_write )
{
    c4dot_write_int( ctx, int_to_write, 2 );
}

void c4dot_write_int_oct ( c4dotmatrixr_t *ctx, int16_t int_to_write )
{
    c4dot_write_int( ctx, int_to_write, 8);
}

void c4dot_write_int_dec ( c4dotmatrixr_t *ctx, int16_t int_to_write)
{
    c4dot_write_int( ctx, int_to_write, 10 );
}

void c4dot_write_int_hex ( c4dotmatrixr_t *ctx, int16_t int_to_write )
{
    c4dot_write_int( ctx, int_to_write, 16 );
}

void c4dot_clear_display ( c4dotmatrixr_t *ctx )
{
    
    digital_out_low( &ctx->rst );
    Delay_1ms( );       // hold CLR low for 1 ms
    digital_out_high( &ctx->rst );

}

// ------------------------------------------------------------------------- END

