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

#include "pwrmeter.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void calc_crc ( uint8_t *datagram, uint8_t datagram_length );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pwrmeter_cfg_setup ( pwrmeter_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en   = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

PWRMETER_RETVAL pwrmeter_init ( pwrmeter_t *ctx, pwrmeter_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

   
    return PWRMETER_OK;
}

void pwrmeter_generic_write ( pwrmeter_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t pwrmeter_generic_read ( pwrmeter_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

PWRMETER_RETVAL pwrmeter_read_reg_bytes ( pwrmeter_t *ctx, uint16_t reg_addr, uint8_t n_bytes, uint8_t *data_out )
{
    uint8_t temp_buff[ 35 ];
    uint8_t cnt;
    
    if ( reg_addr > 0x00E1 )
    {
        return PWRMETER_ADDRESS_FAIL;
    }
    if ( n_bytes > 32 )
    {
        return PWRMETER_NBYTES_FAIL;
    }
    
    temp_buff[ 0 ] = PWRMETER_HEADER_BYTE;
    temp_buff[ 1 ] = 0x08;                               // Number of bytes in Frame 
    temp_buff[ 2 ] = PWRMETER_SET_ADDR_POINTER_COMM;
    temp_buff[ 3 ] = reg_addr >> 8;
    temp_buff[ 4 ] = reg_addr;
    temp_buff[ 5 ] = PWRMETER_REG_READ_COMM;
    temp_buff[ 6 ] = n_bytes;
    calc_crc( temp_buff, 8 );
    
    pwrmeter_generic_write( ctx, temp_buff, 8 );
    
    Delay_100ms( );
    pwrmeter_generic_read( ctx, temp_buff, n_bytes + 3 );
    if ( temp_buff[ 0 ] != PWRMETER_SUCCESSFUL )
    {
        return temp_buff[ 0 ];
    }

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        data_out[ cnt ] = temp_buff[ cnt + 2 ];
    }
    
    return temp_buff[ 0 ];
}

PWRMETER_RETVAL pwrmeter_read_reg_word ( pwrmeter_t *ctx, uint16_t register_addr, uint16_t *data_out )
{
    uint8_t buff_out[ 2 ];
    uint8_t check_ret_val;
    uint16_t ret_val;
    
    check_ret_val = pwrmeter_read_reg_bytes( ctx, register_addr, 2, buff_out );
    
    if ( check_ret_val != PWRMETER_SUCCESSFUL )
    {
        return check_ret_val;
    }
    
    ret_val = buff_out[ 1 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 0 ];
    *data_out = ret_val;
    
    return check_ret_val;
}

PWRMETER_RETVAL pwrmeter_read_reg_dword ( pwrmeter_t *ctx, uint16_t register_addr, uint32_t *data_out )
{
    uint8_t buff_out[ 4 ];
    uint8_t check_ret_val;
    uint32_t ret_val;
    
    check_ret_val = pwrmeter_read_reg_bytes( ctx, register_addr, 4, buff_out );
    
    if ( check_ret_val != PWRMETER_SUCCESSFUL )
    {
        return check_ret_val;
    }
    
    ret_val = buff_out[ 3 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 2 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 1 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 0 ];
    *data_out = ret_val;
    
    return check_ret_val;
}

PWRMETER_RETVAL pwrmeter_read_reg_signed ( pwrmeter_t *ctx, uint16_t register_addr, uint8_t data_mode, int32_t *data_out )
{
    uint8_t num_bytes;
    uint8_t buff_out[ 4 ] = { 0 };
    uint8_t check_ret_val;
    int32_t ret_val;
    
    if ( data_mode == PWRMETER_16BIT_DATA )
    {
        num_bytes = 2;
    }
    else
    {
        num_bytes = 4;
    }
    
    check_ret_val = pwrmeter_read_reg_bytes( ctx, register_addr, num_bytes, buff_out );
    
    if ( check_ret_val != PWRMETER_SUCCESSFUL )
    {
        return check_ret_val;
    }
    
    ret_val = buff_out[ 3 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 2 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 1 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 0 ];
    
    if ( data_mode == PWRMETER_16BIT_DATA )
    {
        if ( ret_val & 0x00008000 )
        {
            ret_val |= 0xFFFF0000;
        }
        else
        {
            ret_val &= 0x0000FFFF;
        }
    }
    
    *data_out = ret_val;
    
    return check_ret_val;
}

PWRMETER_RETVAL pwrmeter_write_reg_bytes ( pwrmeter_t *ctx, uint16_t reg_addr, uint8_t n_bytes, uint8_t *data_in )
{
    uint8_t temp_buff[ 12 ];
    uint8_t cnt;
    
    if ( reg_addr > 0x00E1 )
    {
        return PWRMETER_ADDRESS_FAIL;
    }
    if ( n_bytes > 4 )
    {
        return PWRMETER_NBYTES_FAIL;
    }
    pwrmeter_generic_read( ctx, temp_buff, 1 );
    
    temp_buff[ 0 ] = PWRMETER_HEADER_BYTE;
    temp_buff[ 1 ] = n_bytes + 8;                     // Number of bytes in Frame 
    temp_buff[ 2 ] = PWRMETER_SET_ADDR_POINTER_COMM;
    temp_buff[ 3 ] = reg_addr >> 8;
    temp_buff[ 4 ] = reg_addr;
    temp_buff[ 5 ] = PWRMETER_REG_WRITE_COMM;
    temp_buff[ 6 ] = n_bytes;
    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        temp_buff[ cnt + 7 ] = data_in[ cnt ];
    }
    calc_crc( temp_buff, n_bytes + 8 );

    pwrmeter_generic_write( ctx, temp_buff, n_bytes + 8 );
    
    Delay_100ms( );
    pwrmeter_generic_read( ctx, temp_buff, 1 );
    
    return temp_buff[ 0 ];
}

PWRMETER_RETVAL pwrmeter_write_reg_word ( pwrmeter_t *ctx, uint16_t register_addr, uint16_t data_in )
{
    uint8_t buff_in[ 2 ];
    uint8_t check_ret_val;
    
    buff_in[ 0 ] = data_in;
    buff_in[ 1 ] = data_in >> 8;
    
    check_ret_val = pwrmeter_write_reg_bytes( ctx, register_addr, 2, buff_in );
    
    return check_ret_val;
}

PWRMETER_RETVAL pwrmeter_write_reg_dword ( pwrmeter_t *ctx, uint16_t register_addr, uint32_t data_in )
{
    uint8_t buff_in[ 4 ];
    uint8_t check_ret_val;
    
    buff_in[ 0 ] = data_in;
    buff_in[ 1 ] = data_in >> 8;
    buff_in[ 2 ] = data_in >> 16;
    buff_in[ 3 ] = data_in >> 24;
    
    check_ret_val = pwrmeter_write_reg_bytes( ctx, register_addr, 4, buff_in );
    
    return check_ret_val;
}

PWRMETER_RETVAL pwrmeter_write_reg_signed ( pwrmeter_t *ctx, uint16_t register_addr, uint8_t data_mode, int32_t data_in )
{
    uint8_t buff_in[ 4 ];
    uint8_t num_bytes;
    uint8_t check_ret_val;
    
    if ( data_mode == PWRMETER_16BIT_DATA )
    {
        num_bytes = 2;
    }
    else
    {
        num_bytes = 4;
    }
    
    buff_in[ 0 ] = data_in;
    buff_in[ 1 ] = data_in >> 8;
    buff_in[ 2 ] = data_in >> 16;
    buff_in[ 3 ] = data_in >> 24;
    
    check_ret_val = pwrmeter_write_reg_bytes( ctx, register_addr, num_bytes, buff_in );
    
    return check_ret_val;
}

PWRMETER_RETVAL pwrmeter_send_command ( pwrmeter_t *ctx, uint8_t command_byte )
{
    uint8_t temp_buff[ 4 ];
    uint8_t cnt;
    
    temp_buff[ 0 ] = PWRMETER_HEADER_BYTE;
    temp_buff[ 1 ] = 0x04;                      // Number of bytes in Frame
    temp_buff[ 2 ] = command_byte;
    calc_crc( temp_buff, 4 );
    
    pwrmeter_generic_write( ctx, temp_buff, 4 );
    
    Delay_100ms( );
    pwrmeter_generic_read( ctx, temp_buff, 1 );
    
    return temp_buff[ 0 ];
}

PWRMETER_RETVAL pwrmeter_read_page_eeprom ( pwrmeter_t *ctx, uint8_t page_num, uint16_t *data_out )
{
    uint8_t temp_buff[ 19 ];
    uint16_t ret_val;
    uint8_t cnt;
    uint8_t indx;
    
    if ( page_num > 31 )
    {
        return PWRMETER_PAGE_NUM_FAIL;
    }
    
    temp_buff[ 0 ] = PWRMETER_HEADER_BYTE;
    temp_buff[ 1 ] = 0x05;                      // Number of bytes in Frame 
    temp_buff[ 2 ] = PWRMETER_EEPROM_READ_COMM;
    temp_buff[ 3 ] = page_num;
    calc_crc( temp_buff, 5 );
    
    pwrmeter_generic_write( ctx, temp_buff, 5 );
    
    Delay_100ms( );
    pwrmeter_generic_read( ctx, temp_buff, 19 );
    if ( temp_buff[ 0 ] != PWRMETER_SUCCESSFUL )
    {
        return temp_buff[ 0 ];
    }

    cnt = 2;
    indx = 0;
    
    while ( cnt < 18 )
    {
        data_out[ indx ] = temp_buff[ cnt + 1 ];
        data_out[ indx ] <<= 8;
        data_out[ indx ] |= temp_buff[ cnt ];
        
        cnt += 2;
        indx++;
    }
    
    return temp_buff[ 0 ];
}

PWRMETER_RETVAL pwrmeter_write_page_eeprom ( pwrmeter_t *ctx, uint8_t  page_num, uint16_t *data_in )
{
    uint8_t temp_buff[ 21 ];
    uint8_t cnt;
    uint8_t indx;
    
    if (( page_num < 2) || ( page_num > 31 ))
    {
        return PWRMETER_PAGE_NUM_FAIL;
    }
    
    temp_buff[ 0 ] = PWRMETER_HEADER_BYTE;
    temp_buff[ 1 ] = 0x15;                          // Number of bytes in Frame 
    temp_buff[ 2 ] = PWRMETER_EEPROM_WRITE_COMM;
    temp_buff[ 3 ] = page_num;
    cnt = 4;
    for ( indx = 0; indx < 8; indx++ )
    {
        temp_buff[ cnt ] = data_in[ indx ];
        temp_buff[ cnt + 1 ] = data_in[ indx ] >> 8;
        
        cnt += 2;
    }
    calc_crc( temp_buff, 21 );
    
    pwrmeter_generic_write( ctx, temp_buff, 21 );
    
    Delay_100ms( );
    pwrmeter_generic_read( ctx, temp_buff, 1 );
    
    return temp_buff[ 0 ];
}

PWRMETER_RETVAL pwrmeter_get_status ( pwrmeter_t *ctx, uint8_t *status_data )
{
    uint16_t st_data;
    uint8_t check_resp;
    
    check_resp = pwrmeter_read_reg_word ( ctx, PWRMETER_SYS_STATUS_REG, &st_data );
    
    if ( check_resp != PWRMETER_SUCCESSFUL )
    {
        return check_resp;
    }
    
    *status_data  = ( st_data & 0x8000 ) >> 15;
    *status_data |= ( st_data & 0x4000 ) >> 13;
    *status_data |= ( st_data & 0x2000 ) >> 11;
    *status_data |= ( st_data & 0x0020 ) >> 2;
    *status_data |= ( st_data & 0x0010 );
    
    return check_resp;
}

void pwrmeter_enable ( pwrmeter_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

// ---------------------------------------------- PRIVATE FUNCTION DEFINITION 

static void calc_crc ( uint8_t *datagram, uint8_t datagram_length )
{
    uint32_t cs = 0;
    uint8_t *crc = datagram + ( datagram_length - 1 );
    uint32_t tmp = 0;
    uint8_t i;

    for ( i = 0; i < datagram_length - 1; i++ )
    {
        tmp = datagram[ i ];
        cs = cs + tmp;
    }

    cs = ( cs % 256 ) & 0xFF;
    *crc = cs;
}

// ------------------------------------------------------------------------- END

