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

#include "g2c3g.h"
#include "string.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OPERATOR_CMD                "AT+NWCR"
#define BROKER_CMD                  "AT+BRCR"
#define DATA_CMD                    "AT+DSET"

#define G2C3G_BUF_FIRST_CMD         "=\""
#define G2C3G_BUF_MID_CMD           "\",\""
#define G2C3G_BUF_END_CMD           "\""

#define G2C3G_RSP_CMD_ACT           "+ACT"
#define G2C3G_RSP_CMD_ACT_LEN        4

// ACTUATOR SWITCH PARSER
#define G2C3G_RSP_STATE_TRUE        "true"
#define G2C3G_RSP_STATE_TRUE_LEN    4
#define G2C3G_RSP_STATE_FALSE       "false"
#define G2C3G_RSP_STATE_FALSE_LEN   5

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void g2c3g_cfg_setup ( g2c3g_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    cfg->rst = HAL_PIN_NC;
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

G2C3G_RETVAL g2c3g_init ( g2c3g_t *ctx, g2c3g_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );

    // Input pins

    digital_in_init( &ctx->gp0, cfg->gp0 );
    digital_in_init( &ctx->gp1, cfg->gp1 );
    digital_in_init( &ctx->rts, cfg->rts );
    
    g2c3g_module_reset( ctx );
    
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

    return G2C3G_OK;
}

void g2c3g_module_reset( g2c3g_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

uint8_t g2c3g_led_net( g2c3g_t *ctx )
{
    return digital_in_read( &ctx->gp1 );
}

uint8_t g2c3g_led_conn( g2c3g_t *ctx )
{
    return digital_in_read( &ctx->gp0 );
}

void g2c3g_generic_write( g2c3g_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t g2c3g_generic_read( g2c3g_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void g2c3g_send_command( g2c3g_t *ctx, char *command )
{
    char tmp_buf[ 100 ];
    uint8_t len;
    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    strcat( tmp_buf, "\r" );

    g2c3g_generic_write( ctx, tmp_buf, strlen( tmp_buf ) );
}

void g2c3g_send_operator_cfg( g2c3g_t *ctx, char *op_apn, char *op_username, char *op_password )
{
    char tmp_buf[ 100 ];
    memset( &tmp_buf[ 0 ], 0, 100 );

    strcat( &tmp_buf[ 0 ], OPERATOR_CMD );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_FIRST_CMD );
    strcat( &tmp_buf[ 0 ], &op_apn[ 0 ] );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_MID_CMD );
    strcat( &tmp_buf[ 0 ], &op_username[ 0 ] );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_MID_CMD );
    strcat( &tmp_buf[ 0 ], &op_password[ 0 ] );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_END_CMD );
    strcat( &tmp_buf[ 0 ], "\r" );

    g2c3g_generic_write( ctx, &tmp_buf[ 0 ], strlen(tmp_buf));
}

void g2c3g_send_broker_cfg( g2c3g_t *ctx, char *brc_key, char *brc_password )
{
    
    uint8_t tmp_buf[ 100 ];
    memset( &tmp_buf[ 0 ], 0, 100 );

    strcat( &tmp_buf[ 0 ], BROKER_CMD );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_FIRST_CMD );
    strcat( &tmp_buf[ 0 ], &brc_key[ 0 ] );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_MID_CMD );
    strcat( &tmp_buf[ 0 ], &brc_password[ 0 ] );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_END_CMD );
    strcat( &tmp_buf[ 0 ], "\r" );

    g2c3g_generic_write( ctx, &tmp_buf[ 0 ], strlen(tmp_buf));
}

void g2c3g_send_data_ref( g2c3g_t *ctx, char *reference_buf, char *data_buf )
{
    
    uint8_t tmp_buf[ 100 ];
    memset( &tmp_buf[ 0 ], 0, 100 );

    strcat( &tmp_buf[ 0 ], DATA_CMD );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_FIRST_CMD );
    strcat( &tmp_buf[ 0 ], &reference_buf[ 0 ] );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_MID_CMD );
    strcat( &tmp_buf[ 0 ], &data_buf[ 0 ] );
    strcat( &tmp_buf[ 0 ], G2C3G_BUF_END_CMD );
    strcat( &tmp_buf[ 0 ], "\r" );

    g2c3g_generic_write( ctx, &tmp_buf[ 0 ], strlen(tmp_buf));
}

g2c3g_error_t g2c3g_actuator_sw_parser( char *rsp, char *act_ref, g2c3g_actuator_sw_t *sw_state )
{
    uint8_t err;
    uint8_t tmp_storage[ 10 ];
    uint8_t len;

    // Buffer erase
    memset( tmp_storage, 0, 10 );
    err = G2C3G_PARSER_NO_ERROR;

    // Checking commands
    if ( 0 == strncmp( G2C3G_RSP_CMD_ACT, rsp + 2, G2C3G_RSP_CMD_ACT_LEN ) )
    {
        len = strlen( act_ref );

        // Checking reference
        if ( 0 == strncmp( act_ref, rsp + 9, len ) )
        {
            len = len + 12;
            strcpy( tmp_storage, rsp + len );

            // Checking data
            if ( 0 == strncmp( tmp_storage, G2C3G_RSP_STATE_TRUE, G2C3G_RSP_STATE_TRUE_LEN ) )
            {
                *sw_state = 1;
            }
            else if ( 0 == strncmp( tmp_storage, G2C3G_RSP_STATE_FALSE, G2C3G_RSP_STATE_FALSE_LEN ) )
            {
                *sw_state = 0;
            }
            else
            {
                err |= G2C3G_PARSER_ERROR_DATA;
            }
        }
        else
        {
            err |= G2C3G_PARSER_ERROR_REF;
        }
    }
    else
    {
        err |= G2C3G_PARSER_ERROR_CMD;
    }
    return err;
}

g2c3g_error_t g2c3g_actuator_cnt_parser( char *rsp, char *act_ref, g2c3g_actuator_cnt_t *num_data )
{
    uint8_t err;
    uint8_t tmp_storage[ 10 ];
    uint8_t len;
    uint8_t cnt;
    
    uint8_t num_len = 0;
    uint8_t tmp_data_u8 = 0;

    // Buffer erase
    memset( tmp_storage, 0, 10 );
    err = G2C3G_PARSER_NO_ERROR;
    *num_data = 0;
    
    // Checking commands
    if ( 0 == strncmp( G2C3G_RSP_CMD_ACT, rsp + 2, G2C3G_RSP_CMD_ACT_LEN ) )
    {
        len = strlen( act_ref );
        
        // Checking reference
        if ( 0 == strncmp( act_ref, rsp + 9, len ) )
        {
            len = len + 12;
            strcpy( tmp_storage, rsp + len );
           
            num_len = strlen( tmp_storage );
            
            // Checking data
            if ( num_len != 0 )
            {
                for( cnt = 0; cnt < num_len; cnt++ )
                {
                    if( ( tmp_storage[ cnt ] >= '0' ) && ( tmp_storage[ cnt ] <= '9' ) )
                    {
                        *num_data *= 10;
                        tmp_data_u8 = tmp_storage[ cnt ];
                        *num_data += ( tmp_data_u8 - 48 );
                    }
                }
            }
            else
            {
                err |= G2C3G_PARSER_ERROR_DATA;
            }
        }
        else
        {
            err |= G2C3G_PARSER_ERROR_REF;
        }
    }
    else
    {
        err |= G2C3G_PARSER_ERROR_CMD;
    }
    
    return err;
}

g2c3g_error_t g2c3g_actuator_str_parser( char *rsp, char *act_ref, g2c3g_actuator_str_t *str_data )
{
    uint8_t err;
    uint8_t tmp_storage[ 200 ];
    uint8_t len;
    uint16_t data_len;
    uint16_t str_cnt = 0;
    uint16_t cnt;

    // Buffer erase
    memset( tmp_storage, 0, 10 );
    err = G2C3G_PARSER_NO_ERROR;
    
    // Checking command
    if ( 0 == strncmp( G2C3G_RSP_CMD_ACT, rsp + 2, G2C3G_RSP_CMD_ACT_LEN ) )
    {
        len = strlen( act_ref );

        // Checking reference
        if ( 0 == strncmp( act_ref, rsp + 9, len ) )
        {
            len = len + 12;
            strcpy( tmp_storage, rsp + len );
            
            data_len = strlen( tmp_storage );
            
            // Checking data
            if( data_len != 0 )
            {
                for( cnt = 0; cnt < data_len; cnt++ )
                {
                    if ( tmp_storage[ cnt ] != '"' )
                    {
                        str_data[str_cnt++] = tmp_storage[ cnt ];
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                err |= G2C3G_PARSER_ERROR_DATA;
            }
        }
        else
        {
            err |= G2C3G_PARSER_ERROR_REF;
        }
    }
    else
    {
        err |= G2C3G_PARSER_ERROR_CMD;
    }
    return err;
}

// ------------------------------------------------------------------------- END

