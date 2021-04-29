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
 * @file bletiny.c
 * @brief BLE TINY Click Driver.
 */

#include "bletiny.h"
#include "conversions.h"
#include "generic_pointer.h"

/**
 * @brief Helping strings.
 * @details Strings used for driver use.
 */
#define COMMA ","
#define HEX "0x"

/**
 * @brief Driver @b rx_buf size.
 * @details Specified size of driver receiver buffer.
 */
#define RX_BUF_LEN 100

/**
 * @brief Driver @b rx_buf and its @b rx_buf_cnt.
 * @details Driver receiver buffer and its counter.
 */
static char rx_buf[ RX_BUF_LEN ] = { 0 };
static uint8_t rx_buf_cnt = 0;

/**
 * @brief Response check.
 * @details This function waits and checks for response and returns the status of response.
 * 
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t bletiny_rsp_check ( bletiny_t *ctx );

/**
 * @brief Convert Byte to hex string.
 * @details Convert Byte to hex string using conversions function and trims unwanted characters.
 */
static void bletiny_convert_to_hex ( uint8_t byte, char *out_buf );

/**
 * @brief Convert Byte to dec string.
 * @details Convert Byte to dec string using conversions function and trims unwanted characters.
 */
static void bletiny_convert_to_str ( uint8_t byte, char *out_buf );

void bletiny_cfg_setup ( bletiny_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t bletiny_init ( bletiny_t *ctx, bletiny_cfg_t *cfg ) 
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

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );

    return UART_SUCCESS;
}

err_t bletiny_default_cfg ( bletiny_t *ctx ) 
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_1sec( );
    return BLETINY_OK;
}

err_t bletiny_generic_write ( bletiny_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t bletiny_generic_read ( bletiny_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void bletiny_send_cmd ( bletiny_t *ctx, char *cmd )
{
    char lf = 13;
    
    uart_write( &ctx->uart, cmd, strlen( cmd ) );
    uart_write( &ctx->uart, &lf, 1 );
    Delay_100ms();
}



void bletiny_spi_config ( bletiny_t *ctx, uint8_t speed, uint8_t mode )
{
    #define CS_CFG      "AT+IOCFG=8,20"
    #define SCK_CFG     "AT+IOCFG=7,19"
    #define MISO_CFG    "AT+IOCFG=11,22"
    #define MOSI_CFG    "AT+IOCFG=9,21"
    char fix_cfg[] = "8";
    char cfg_cmd[ 20 ] = "AT+SPICFG=";
    char help[ 10 ] = { 0 };
    
    bletiny_convert_to_str( speed, help );
    strcat( cfg_cmd, help);
    strcat( cfg_cmd, COMMA);
    bletiny_convert_to_str( mode, help );
    strcat( cfg_cmd, help);
    strcat( cfg_cmd, COMMA);
    strcat( cfg_cmd, fix_cfg);
    
    do
    {
        bletiny_send_cmd( ctx, CS_CFG );
    }while ( BLETINY_OK != bletiny_rsp_check( ctx ) );
    
    do
    {
        bletiny_send_cmd( ctx, SCK_CFG );
    }while ( BLETINY_OK != bletiny_rsp_check( ctx ) );
    
    do
    {
        bletiny_send_cmd( ctx, MISO_CFG );
    }while ( BLETINY_OK != bletiny_rsp_check( ctx ) );
    
    do
    {
        bletiny_send_cmd( ctx, MOSI_CFG );
    }while ( BLETINY_OK != bletiny_rsp_check( ctx ) );
    
    do
    {
        bletiny_send_cmd( ctx, cfg_cmd );
    }while ( BLETINY_OK != bletiny_rsp_check( ctx ) );
    
}

err_t bletiny_spi_write ( bletiny_t *ctx, char *data_buf, uint8_t len )
{
    char data_out[ 140 ] = "AT+SPIWR=0x";
    static uint8_t buf[ 64 ] = { 0 };
    char help[ 10 ] = { 0 };
    
    memcpy( buf, data_buf, len );
    
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        bletiny_convert_to_hex( buf[ cnt ], help );
        strcat( data_out, help );
    }
    bletiny_send_cmd( ctx, data_out );
    
    if ( BLETINY_OK == bletiny_rsp_check( ctx ) )
    {
        return BLETINY_OK;
    }
    else
    {
        return BLETINY_ERROR;
    }
}

err_t bletiny_spi_read ( bletiny_t *ctx, char *data_buf, uint8_t len )
{
    char data_out[ 140 ] = "AT+SPIRD=";
    char buf[ 10 ] = { 0 };
    bletiny_convert_to_str( len, buf );
    strcat( data_out, buf );
    bletiny_send_cmd( ctx, data_out );

    if ( BLETINY_OK == bletiny_rsp_check( ctx ) )
    {
        char* __generic start_rsp = strstr( rx_buf, data_out );
        char* __generic end_rsp = strstr( rx_buf, BLETINY_RSP_OK );
        if ( start_rsp )
        {
            start_rsp += strlen( data_out );
        }
        else
        {
            start_rsp = data_out;
        }
        
        start_rsp += 3;
        char hex[ 3 ] = { 0 };
        
        #define HEX "0x"
        start_rsp = strstr( start_rsp, HEX );
        
        for ( uint8_t cnt = 0; cnt < len; cnt++ )
        {
            start_rsp += 2;
            memcpy( hex, start_rsp, 2 );
            data_buf[ cnt ] = hex_to_uint8( hex );
        }
        return BLETINY_OK;
    }
    else
    {
        return BLETINY_ERROR;
    }
}

err_t bletiny_spi_write_then_read ( bletiny_t *ctx, uint8_t *data_write, uint8_t write_len, char *data_read, uint8_t read_len )
{
    #define DUMMY "00"
    char data_out[ 140 ] = "AT+SPITR=0x";
    uint8_t cnt = 0;
    for ( cnt = 0; cnt < write_len; cnt++ )
    {
        char buf[ 10 ] = { 0 };
        bletiny_convert_to_hex( data_write[ cnt ], buf );
        strcat( data_out, buf );
    }
    for ( cnt = 0; cnt < read_len; cnt++ )
    {
        strcat( data_out, DUMMY );
    }
    
    bletiny_send_cmd( ctx, data_out );
    if ( BLETINY_OK == bletiny_rsp_check( ctx ) )
    {
        char* __generic start_rsp = strstr( rx_buf, data_out );
        char* __generic end_rsp = strstr( rx_buf, BLETINY_RSP_OK );
        if ( start_rsp )
        {
            start_rsp += strlen( data_out );
        }
        else
        {
            start_rsp = data_out;
        }
        
        char hex[ 3 ] = { 0 };
        
        
        start_rsp = strstr( start_rsp, HEX );
        start_rsp += ( 2 + ( 2 * write_len ) );
        for ( cnt = 0; cnt < read_len; cnt++ )
        {
            memcpy( hex, start_rsp, 2 );
            data_read[ cnt ] = hex_to_uint8( hex );
            start_rsp += 2;
        }
        return BLETINY_OK;
    }
    else
    {
        return BLETINY_ERROR;
    }
}

void bletiny_i2c_config ( bletiny_t *ctx, uint8_t speed, uint8_t reg_len )
{
    #define SCL_CFG "AT+IOCFG=11,7"
    #define SDA_CFG "AT+IOCFG=9,8"
    char fix_cfg[] = "7";
    char cfg_cmd[ 20 ] = "AT+I2CCFG=";
    char help[ 10 ] = { 0 };
    
    strcat( cfg_cmd, fix_cfg);
    strcat( cfg_cmd, COMMA);
    bletiny_convert_to_str( speed, help );
    strcat( cfg_cmd, help);
    strcat( cfg_cmd, COMMA);
    bletiny_convert_to_str( reg_len, help );
    strcat( cfg_cmd, help);
    
    do
    {
        bletiny_send_cmd( ctx, SCL_CFG );
    }while ( BLETINY_OK != bletiny_rsp_check( ctx ) );
    
    do
    {
        bletiny_send_cmd( ctx, SDA_CFG );
    }while ( BLETINY_OK != bletiny_rsp_check( ctx ) );
    
    do
    {
        bletiny_send_cmd( ctx, cfg_cmd );
    }while ( BLETINY_OK != bletiny_rsp_check( ctx ) );
}

err_t bletiny_i2c_write ( bletiny_t *ctx, uint8_t slave_address, uint16_t reg, uint8_t reg_data )
{
    char data_out[ 140 ] = "AT+I2CWRITE=0x";
    char buf[ 10 ] = { 0 };
    
    bletiny_convert_to_hex( slave_address, buf );
    strcat( data_out, buf );
    strcat( data_out, COMMA );
    bletiny_convert_to_str( reg, buf );
    strcat( data_out, buf );
    strcat( data_out, COMMA );
    bletiny_convert_to_str( reg_data, buf );
    strcat( data_out, buf );
    
    bletiny_send_cmd( ctx, data_out );
    
    if ( BLETINY_OK == bletiny_rsp_check( ctx ) )
    {
        return BLETINY_OK;
    }
    else
    {
        return BLETINY_ERROR;
    }
}

err_t bletiny_i2c_read ( bletiny_t *ctx,  uint8_t slave_address, uint16_t reg, uint8_t *data_buf, uint8_t len )
{
    char data_out[ 140 ] = "AT+I2CREAD=0x";
    char buf[ 10 ] = { 0 };
    bletiny_convert_to_hex( slave_address, buf );
    strcat( data_out, buf );
    strcat( data_out, COMMA );
    bletiny_convert_to_str( reg, buf );
    strcat( data_out, buf );
    strcat( data_out, COMMA );
    bletiny_convert_to_str( len, buf );
    strcat( data_out, buf );
    bletiny_send_cmd( ctx, data_out );
    if ( BLETINY_OK == bletiny_rsp_check( ctx ) )
    {
        char* __generic start_rsp = strstr( rx_buf, data_out );
        char* __generic end_rsp = strstr( rx_buf, BLETINY_RSP_OK );
        if ( start_rsp )
        {
            start_rsp += strlen( data_out );
        }
        else
        {
            start_rsp = data_out;
        }
        
        char hex[ 3 ] = { 0 };
        
        for ( uint8_t cnt = 0; cnt < len; cnt++ )
        {
            start_rsp = strstr( start_rsp, HEX );
            if ( start_rsp )
            {
                start_rsp += 2;
                memcpy( hex, start_rsp, 2 );
                data_buf[ cnt ] = hex_to_uint8( hex );
            }
            else
            {
                return BLETINY_ERROR;
            }
        }
        return BLETINY_OK;
    }
    else
    {
        return BLETINY_ERROR;
    }
}

static err_t bletiny_rsp_check ( bletiny_t *ctx )
{
    char dev_buf[ 30 ] = { 0 };
    uint16_t timeout = 1000;
    
    memset( rx_buf, 0 , RX_BUF_LEN );
    rx_buf_cnt = 0;
    
    while ( ( 0 == strstr( rx_buf, BLETINY_RSP_OK ) ) && ( 0 ==strstr( rx_buf, BLETINY_RSP_ERROR ) ) )
    {
        err_t read_val = bletiny_generic_read( ctx, dev_buf, 30 );
        if ( read_val > 0 )
        {
            for ( int32_t cnt = 0; cnt < read_val; cnt++ )
            {
                rx_buf[ rx_buf_cnt ] = dev_buf[ cnt ];
                rx_buf_cnt++;
            }
        }
        
        timeout--;
        if ( !timeout )
        {
            return BLETINY_ERROR_TIMEOUT;
        }
    }
    
    if ( strstr( rx_buf, BLETINY_RSP_OK ) )
    {
        return BLETINY_OK;
    }
    else
    {
        return BLETINY_ERROR;
    }
}

static void bletiny_convert_to_hex ( uint8_t byte, char *out_buf )
{
    uint8_to_hex( byte, out_buf );
    r_trim(out_buf);
    l_trim(out_buf);
}

static void bletiny_convert_to_str ( uint8_t byte, char *out_buf )
{
    uint8_to_str( byte, out_buf );
    r_trim(out_buf);
    l_trim(out_buf);
}

// ------------------------------------------------------------------------- END
