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
 * @file ph.c
 * @brief pH Click Driver.
 */

#include "ph.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Makes 100 ms delay in order to facilitate the communication.
 */
static void dev_com_delay ();

/**
 * @brief pH str cut chr function.
 * @details This function removes all selected characters from string str,
 * and returns it to the same str without those characters.
 * @param str Address of string.
 * @param chr Character to cut.
 */
static void ph_str_cut_chr ( uint8_t *str, uint8_t chr );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void ph_cfg_setup ( ph_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t ph_init ( ph_t *ctx, ph_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    return UART_SUCCESS;
}

err_t ph_generic_write ( ph_t *ctx, uint8_t *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t ph_generic_read ( ph_t *ctx, uint8_t *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void ph_uart_write ( ph_t *ctx, uint8_t input )
{
    uart_write( &ctx->uart, &input, 1 );
}

void ph_uart_read_until ( ph_t *ctx, char *p_rx_data, char *delim )
{
    char rx_data[ 40 ];
    uint16_t n_cnt = 0;

    for ( ; ; )
    {
        ph_generic_read( ctx, rx_data, 40 );
        
        if ( strrchr( rx_data, 13 ) )
        {
            ph_str_cut_chr( rx_data, 13 );
            if ( strstr( rx_data, delim ) == 0 )
            {
                p_rx_data = rx_data;
                break;
            } 
            else if ( strstr( rx_data, PH_RSP_CODE_ERROR ) == 0 )
            {
                p_rx_data = rx_data;
                break;
            }
        }
        
    }
}

void ph_send_cmd ( ph_t *ctx, char *p_cmd )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;

    n_len = strlen( p_cmd );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        uart_write( &ctx->uart, &p_cmd[ n_cnt ], 1 );
    }
    uart_write( &ctx->uart, PH_CMD_END_COMMAND, 1 );
}

void ph_send_cmd_resp ( ph_t *ctx, char *p_cmd, char *p_resp )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;

    n_len = strlen( p_cmd );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        uart_write( &ctx->uart, &p_cmd[ n_cnt ], 1 );
    }
    uart_write( &ctx->uart, PH_CMD_END_COMMAND, 1 );

    ph_uart_read_until( ctx, p_resp, PH_RSP_CODE_ALL_GOOD );
}

void ph_send_cmd_w_num ( ph_t *ctx, char *p_cmd, char *flt_val, char *p_resp )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;
    char flt_str[ 5 ]= { 0 };

    n_len = strlen( p_cmd );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        uart_write( &ctx->uart, &p_cmd[ n_cnt ], 1 );
    }
    
    n_len = strlen( flt_val );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        uart_write( &ctx->uart, &flt_val[ n_cnt ], 1 );
    }

    uart_write( &ctx->uart, PH_CMD_END_COMMAND, 1 );

    ph_uart_read_until( ctx, p_resp, PH_RSP_CODE_ALL_GOOD );
}

void ph_get_cmd_resp ( ph_t *ctx, char *p_cmd, char *p_resp )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;
    char temp = '?';

    n_len = strlen( p_cmd );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        uart_write( &ctx->uart, &p_cmd[ n_cnt ], 1 );
    }
    uart_write( &ctx->uart, &temp, 1 );
    uart_write( &ctx->uart, PH_CMD_END_COMMAND, 1 );

    ph_uart_read_until( ctx, p_resp, PH_RSP_CODE_ALL_GOOD );
}

void ph_switch_led ( ph_t *ctx, uint8_t state, char *p_resp )
{
    char tx_buf[ 3 ];

    tx_buf[ 0 ] = 'l';
    tx_buf[ 1 ] = ',';
    tx_buf[ 2 ] = state + 48;
    
    ph_send_cmd_resp( ctx, tx_buf, p_resp );
}

void ph_chk_led_state ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_CHK_LED, p_resp );
}

void ph_find_dev ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_DEV_FIND, p_resp );
}

void ph_cont_read ( ph_t *ctx, uint8_t time, char *p_resp )
{
    char tx_buf[ 4 ] = { '\0', '\0', '\0', '\0' };
    uint8_t n_cnt = 0;
    
    tx_buf[ 0 ] = 'C';
    tx_buf[ 1 ] = ',';
    
    if ( time > 9 )
    {
        tx_buf[ 2 ] = ( ( time / 10 ) + 48 );
        tx_buf[ 3 ] = ( ( time % 10 ) + 48 );
    }
    else 
    {
        tx_buf[ 2 ] = time + 48;
    }
    
    ph_send_cmd_resp( ctx, tx_buf, p_resp );
    dev_com_delay();
    while( strcmp( p_resp, PH_RSP_CODE_ERROR ) == 0 )
    {
        ph_send_cmd_resp( ctx, tx_buf, p_resp );
        dev_com_delay();
    }
}

void ph_chk_cont_read ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_CHK_CONT_READ, p_resp );
}

void ph_perf_calib ( ph_t *ctx, char *point, float flt_val, char *p_resp )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;
    uint8_t tmp = ( uint8_t ) flt_val;
    float flt_v = flt_val;
    char tx_buf[ 5 ] = { '\0', '\0', '\0', '\0', '\0' };
    
    tx_buf[ 0 ] = tmp + 48;
    tx_buf[ 1 ] = '.';
    for ( uint8_t cnt = 2; cnt < 5; cnt++ )
    {
        flt_v = flt_v - tmp;
        flt_v *= 10;
        tmp = (uint8_t) flt_v;
        tx_buf[ cnt ] = tmp + 48;
    }
    
    n_len = strlen( PH_CMD_CALIB_PERF );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        ph_uart_write( ctx, PH_CMD_CALIB_PERF[ n_cnt ] );
    }

    ph_send_cmd_w_num( ctx, point, tx_buf, p_resp );
}

void ph_chk_calib ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_CHK_CALIB, p_resp );
}

void ph_chk_slope ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_RET_SLOPE, p_resp );
}

void ph_get_calib_exp_bytes_num ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_CHK_CALIB_EXP, p_resp );
}

void ph_import_calib ( ph_t *ctx, uint8_t *in_calib, char *p_resp )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;

    n_len = strlen( PH_CMD_CALIB_IMP );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        ph_uart_write( ctx, PH_CMD_CALIB_IMP[ n_cnt ] );
    }
    ph_send_cmd_resp( ctx, in_calib, p_resp );
}

void ph_factory_rst ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_EN_FTY_RST, p_resp );
    dev_com_delay();
    if ( strcmp( p_resp, PH_RSP_CODE_ERROR ) != 0 )
    {
        ph_send_cmd_resp( ctx, PH_CMD_EN_FTY_RST, p_resp );
    }
    ph_uart_read_until( ctx, p_resp, PH_RSP_CODE_ALL_GOOD );
}

void ph_set_temp_comp ( ph_t *ctx, float flt_val, char *p_resp )
{
    uint8_t tmp = flt_val;
    float flt_v;
    char tx_buf[ 4 ];
    
    tx_buf[ 0 ] = ( tmp / 10 ) + 48;
    tx_buf[ 1 ] = ( tmp % 10 ) + 48;
    tx_buf[ 2 ] = '.';
    flt_v = flt_val - tmp;
    tmp = ( uint8_t ) flt_v * 10;
    tx_buf[ 3 ] = tmp + 48;
    
    ph_send_cmd_w_num( ctx, PH_CMD_TEMP_COMP, tx_buf, p_resp );
}

void ph_get_temp_comp ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_CHK_TEMP_COMP, p_resp );
}

void ph_set_name ( ph_t *ctx, char *p_dev_name, char *p_resp )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;

    n_len = strlen( PH_CMD_SET_DEV_NAME );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        ph_uart_write( ctx, PH_CMD_SET_DEV_NAME[ n_cnt ] );
    }
    ph_send_cmd_resp( ctx, p_dev_name, p_resp );
}

void ph_show_name ( ph_t *ctx, char *p_dev_name )
{
    ph_send_cmd_resp( ctx, PH_CMD_GET_DEV_NAME, p_dev_name );
}

void ph_get_dev_info ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_DEV_INFO, p_resp );
}

void ph_check_status ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_READ_STATUS, p_resp );
}

void ph_sleep ( ph_t *ctx )
{
    ph_send_cmd( ctx, PH_CMD_ENTER_SLEEP );
}

void ph_chng_baud_rate ( ph_t *ctx, char *baud_rate, char *p_resp  )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;
    char br_str[ 5 ]= { 0 };

    n_len = strlen( PH_CMD_CNG_BAUD_RATE );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        ph_uart_write( ctx, PH_CMD_CNG_BAUD_RATE[ n_cnt ] );
    }

    ph_send_cmd_resp( ctx, baud_rate, p_resp );
}

void ph_chk_baud_rate ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp ( ctx, PH_CMD_CHK_BAUD_RATE, p_resp );
}

void ph_protocol_lock ( ph_t *ctx, uint8_t state, char *p_resp )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;
    char buf[ 1 ] = { 0 };

    n_len = strlen( PH_CMD_PROTOCOL_LOCK );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        ph_uart_write( ctx, PH_CMD_PROTOCOL_LOCK[ n_cnt ] );
    }
    buf[ 0 ] = state + 48;

    ph_send_cmd_resp( ctx, buf, p_resp );
}

void ph_check_protocol_lock ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp( ctx, PH_CMD_PROTOCOL_CKH, p_resp );
}

void ph_chng_i2c_adr ( ph_t *ctx, uint32_t i2c_adr, char *p_resp )
{
    uint8_t n_cnt = 0;
    uint8_t n_len = 0;
    uint8_t tmp;
    char adr_str[ 3 ]= { 0 };

    n_len = strlen( PH_CMD_CNG_I2C );

    for ( n_cnt = 0; n_cnt < n_len; n_cnt++ )
    {
        ph_uart_write( ctx, PH_CMD_CNG_I2C[ n_cnt ] );
    }
    tmp = i2c_adr;
    if ( i2c_adr > 99 ) {
        adr_str[ 0 ] = ( tmp / 100 ) + 48;
        adr_str[ 1 ] = ( ( tmp / 100 ) / 10 ) + 48;
        adr_str[ 2 ] = ( ( tmp / 100 ) / 10 ) + 48;
    } 
    else if ( i2c_adr < 100 && i2c_adr > 9 )
    {
        adr_str[ 0 ] = ( tmp / 10 ) + 48;
        adr_str[ 1 ] = ( tmp % 10 ) + 48;
        adr_str[ 2 ] = '\r';
    }
    else
    {
        adr_str[ 0 ] = tmp + 48;
        adr_str[ 1 ] = '\r';
        adr_str[ 2 ] = '\r';
    }

    ph_send_cmd_resp( ctx, adr_str, p_resp );
}

void ph_single_read ( ph_t *ctx, char *p_resp )
{
    ph_send_cmd_resp ( ctx, PH_CMD_SET_SNGL_READ, p_resp );
}

uint8_t ph_response ( ph_t *ctx, char *p_resp )
{
    uint8_t len;
    
    len = uart_read( &ctx->uart, p_resp, 40 );
    
    return  len;
}

void ph_clr_log_buf ( char *p_str )
{
    memset( p_str, 0, 40 );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 


static void dev_com_delay ()
{
    Delay_100ms( );
}

static void ph_str_cut_chr ( uint8_t *str, uint8_t chr )
{
    uint16_t cnt_0, cnt_1;
    for ( cnt_0 = 0; cnt_0 < strlen( str ); cnt_0++ )
    {
        if ( str[ cnt_0 ] == chr )
        {
            for ( cnt_1 = cnt_0; cnt_1 < strlen( str ); cnt_1++ )
            {
                str[ cnt_1 ] = str[ cnt_1 + 1 ];
            }
        }
    }
}

// ------------------------------------------------------------------------- END
