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
 * @file magicrfid.c
 * @brief Magic RFID Click Driver.
 */

#include "magicrfid.h"

/**
 * @brief Magic RFID Click CRC-CCITT table.
 * @details CRC-CCITT 16-bit table for calculating CRC of Magic RFID Click driver.
 */
static uint16_t crctable[] =
{
    0x0000,
    0x1021,
    0x2042,
    0x3063,
    0x4084,
    0x50A5,
    0x60C6,
    0x70E7,
    0x8108,
    0x9129,
    0xA14A,
    0xB16B,
    0xC18C,
    0xD1AD,
    0xE1CE,
    0xF1EF,
};

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Magic RFID device delay function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[in] time_ms : Duration of the delay.
 */
void dev_delay_com ( uint16_t time_ms );

/**
 * @brief Magic RFID device reset delay function.
 * @details Reset delay of  300 milliseconds.
 */
void dev_reset_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void magicrfid_cfg_setup ( magicrfid_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t magicrfid_init ( magicrfid_t *ctx, magicrfid_cfg_t *cfg ) 
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

    // Output pins
    digital_out_init( &ctx->en, cfg->en );
    
    return UART_SUCCESS;
}

void magicrfid_default_cfg ( magicrfid_t *ctx ) 
{        
    magicrfid_device_reset( ctx );
    dev_delay_com( MAGICRFID_LONG_DELAY_TIME );
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_VERSION, 0, 0 );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_GET_POWER_MODE, 0, 0 );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_GET_READER_OPTIONAL_PARAMS, 0, 0 );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_set_baud_rate( ctx, 115200 );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_set_region( ctx, MAGICRFID_REGION_OPEN );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_set_read_power( ctx, 500 );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_set_write_power( ctx, 500 );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_set_antenna_port( ctx );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_set_tag_protocol( ctx, MAGICRFID_TAG_PROTOCOL_GEN2 );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_set_reader_configuration ( ctx, 0x0C, 0x00 );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    magicrfid_start_reading( ctx );
    dev_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
}

err_t magicrfid_generic_write ( magicrfid_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t magicrfid_generic_read ( magicrfid_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void magicrfid_device_reset ( magicrfid_t *ctx ) 
{
    digital_out_low( &ctx->en );
    dev_reset_delay( );
    digital_out_high( &ctx->en );
}

void magicrfid_send_command ( magicrfid_t *ctx, uint8_t opcode, uint8_t *data_in, uint8_t size )
{
    uint8_t tx_data[ DRV_BUFFER_SIZE ];
    uint16_t crc;
    
    tx_data[ 0 ] = MAGICRFID_UNIVERSAL_HEADER; 
    tx_data[ 1 ] = size;
    tx_data[ 2 ] = opcode;
    
    if ( size > 0 ) 
    {
        for ( uint8_t n_cnt = 0; n_cnt < size; n_cnt++ )
        {
            tx_data[ 3 + n_cnt ] = data_in[ n_cnt ];
        }
    }
    
    
    crc = magicrfid_calculate_crc( &tx_data[ 1 ], size + 2 );
    
    tx_data[ size + 3 ] = crc >> 8;
    tx_data[ size + 4 ] = crc & 0xFF;
    
    uart_write( &ctx->uart, tx_data, size + 5 );
}


int8_t magicrfid_get_tag_rssi ( magicrfid_data_t *data_obj ) 
{
    return ( data_obj->drv_rsp_buff[ 12 ] - 256 );
}

void magicrfid_process ( magicrfid_t *ctx, magicrfid_data_t *data_obj ) 
{
    uint8_t rsp_data;
    uint8_t buf_size;
    
    buf_size = magicrfid_generic_read( ctx, &rsp_data, 1 );
    if ( buf_size > 0) 
    {
        buf_size = magicrfid_generic_read( ctx, &rsp_data, 1 );
        if( data_obj->drv_new_data ==  0 ) 
        {
            if ( data_obj->drv_start_package == 1) 
            { 
                data_obj->drv_rsp_buff[ data_obj->drv_buff_cnt++ ] = rsp_data;
            } 
            else 
            {
                if ( ( data_obj->drv_rsp_flag == 0 ) && ( rsp_data == 0xFF ) ) 
                { 
                    data_obj->drv_rsp_flag = 1;
                    data_obj->drv_rsp_buff[ data_obj->drv_buff_cnt++ ] = rsp_data;
                }
                else if ( ( data_obj->drv_rsp_flag == 1 ) && ( rsp_data == 0x21 ) ) 
                { 
                    data_obj->drv_rsp_flag = 2;
                    data_obj->drv_rsp_buff[ data_obj->drv_buff_cnt++ ] = rsp_data;
                }
                else if ( ( data_obj->drv_rsp_flag == 2 ) && ( rsp_data == 0x22 ) ) 
                { 
                    data_obj->drv_start_package = 1; 
                    data_obj->drv_rsp_buff[ data_obj->drv_buff_cnt++ ] = rsp_data;
                }
            }
            
            if ( data_obj->drv_buff_cnt > 47 ) 
            {
                data_obj->drv_new_data = 1;
            }
        }
    }
}

uint8_t magicrfid_get_data_status ( magicrfid_data_t *data_obj ) 
{
    return data_obj->drv_new_data;
}

void magicrfid_reset_data ( magicrfid_data_t *data_obj ) 
{
    data_obj->drv_new_data = 0;
    data_obj->drv_start_package = 0;
    data_obj->drv_rsp_flag = 0;
    data_obj->drv_buff_cnt = 0;
}

void magicrfid_tag_parser ( magicrfid_data_t *data_obj ) 
{
    uint8_t cnt;
    
    for ( cnt = 31; cnt < 43; cnt++ )
    {
       data_obj->tag_buf[ cnt - 31 ] = data_obj->drv_rsp_buff[ cnt ];
    }
    data_obj->tag_rssi = magicrfid_get_tag_rssi( data_obj );
}

void magicrfid_write_data ( magicrfid_t *ctx, uint8_t bank, uint32_t address, uint8_t *data_in, 
                            uint8_t len, uint16_t timeout )
{
    uint8_t tx_data[ DRV_BUFFER_SIZE ];
    tx_data[ 0 ] = ( timeout >> 8 ) & 0xFF;
    tx_data[ 1 ] = timeout & 0xFF;
    tx_data[ 2 ] = 0x00;
    
    for ( uint8_t n_cnt = 0; n_cnt < sizeof( address ); n_cnt++ )
    {
        tx_data[ 3 + n_cnt ] = address >> ( 8 * ( 3 - n_cnt )) & 0xFF;
    }
    tx_data[ 7 ] = bank;
    
    for ( uint8_t n_cnt = 0; n_cnt < len; n_cnt++ )
    {
        tx_data[ 8 + n_cnt ] = data_in[ n_cnt ];
    }
    
    uart_write( &ctx->uart, tx_data, sizeof( tx_data ) );
}

void magicrfid_read_data ( magicrfid_t *ctx, uint8_t bank, uint32_t address, uint8_t *data_out, 
                           uint8_t tx_len, uint8_t *rx_len, uint16_t time_out )
{
    uint8_t tx_data[ 8 ];
    uint8_t rx_data[ DRV_BUFFER_SIZE ];
    uint16_t status;
    uint8_t lenght;
    uint8_t response_lenght;
    
    lenght = tx_len;
    
    tx_data[ 0 ] = time_out >> 8 & 0xFF;
    tx_data[ 1 ] = time_out & 0xFF;
    
    tx_data[ 2 ] = bank;
    
    for ( uint8_t n_cnt = 0; n_cnt < 4; n_cnt++ )
    {
        tx_data[ 3 + n_cnt ] = address >> ( 8 * ( 3 - n_cnt ) ) & 0xFF;
    }
    
    tx_data[ 7 ] = ( lenght / 2 );
    
    if ( bank == 0x03 )
    {
        tx_data[ 7 ] = 0x00;
    }
    
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_READ_TAG_DATA, tx_data, 8 );
    
    magicrfid_generic_read( ctx, rx_data, DRV_BUFFER_SIZE );
    
    if ( rx_data[ 0 ] == 0x00 )
    {
        status = ( rx_data[ 3 ] << 8 ) | rx_data[ 4 ];
        
        if ( status == 0x0000 )
        {
            response_lenght = rx_data[ 1 ];
            
            if ( response_lenght < lenght ) 
            {
                *rx_len = response_lenght;
                for ( uint8_t n_cnt = 0; n_cnt < response_lenght; n_cnt++ )
                {
                    data_out[ n_cnt ] = rx_data[ 5 + n_cnt ];
                }
            }
        }
    }
    
}

uint16_t magicrfid_calculate_crc ( uint8_t *data_val, uint8_t len )
{
    uint16_t crc = 0xFFFF;
    
    for ( uint8_t n_cnt = 0; n_cnt < len; n_cnt++ )
    {
        crc = ( ( crc << 4 ) | ( data_val[ n_cnt ] >> 4 ) ) ^ crctable[ crc >> 12 ];
        crc = ( ( crc << 4 ) | ( data_val[ n_cnt ] & 0x0F ) ) ^ crctable[ crc >> 12 ];
    }
    
    return crc;
}

void magicrfid_set_tag_protocol ( magicrfid_t *ctx, uint8_t protocol )
{
    uint8_t tx_data[ 2 ];
    tx_data[ 0 ] = 0;
    tx_data[ 1 ] = protocol;
    
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_SET_TAG_PROTOCOL, tx_data, 2 );
}

void magicrfid_set_region ( magicrfid_t *ctx, uint8_t region )
{
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_SET_REGION, &region, 1 );
}

void magicrfid_set_antenna_port ( magicrfid_t *ctx )
{
    uint8_t tx_data[ 2 ] = { 0x01, 0x01 };
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_SET_ANTENNA_PORT, tx_data, 2 );
}

void magicrfid_set_antenna_search_list ( magicrfid_t *ctx )
{
    uint8_t tx_data[ 3 ] = { 0x02, 0x01, 0x01 };
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_SET_ANTENNA_PORT, tx_data, 3 );
}

void magicrfid_set_baud_rate ( magicrfid_t *ctx, uint32_t baud_rate )
{
    uint8_t tx_data[ 4 ];
    for ( uint8_t n_cnt = 0; n_cnt < 4; n_cnt++ )
    {
        tx_data[ n_cnt ] = ( uint8_t ) baud_rate >> ( 8 * ( 3 - n_cnt ) );
    }
    
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_SET_BAUD_RATE, tx_data, 4 );
}

void magicrfid_set_read_power ( magicrfid_t *ctx, uint16_t power_setting )
{
    uint8_t tx_data[ 2 ];
    uint16_t power_val;
    power_val = power_setting;
    
    if ( power_val > 2700 )
    {
        power_val = 2700;
    }
    
    tx_data[ 0 ] = ( uint8_t ) power_val >> 8;
    tx_data[ 1 ] = ( uint8_t ) power_val & 0xFF;
    
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_SET_READ_TX_POWER, tx_data, 2 );
}

void magicrfid_set_write_power ( magicrfid_t *ctx, uint16_t power_setting )
{
    uint8_t tx_data[ 2 ];
    uint16_t power_val;
    power_val = power_setting;
    
    if ( power_val > 2700 )
    {
        power_val = 2700;
    }
    
    tx_data[ 0 ] = ( uint8_t ) power_val >> 8;
    tx_data[ 1 ] = ( uint8_t ) power_val & 0xFF;
    
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_SET_WRITE_TX_POWER, tx_data, 2 );
}

void magicrfid_set_reader_configuration ( magicrfid_t *ctx, uint8_t option1, uint8_t option2 )
{
    uint8_t tx_data[ 3 ];
    
    tx_data[ 0 ] = 1;
    tx_data[ 1 ] = option1;
    tx_data[ 2 ] = option2;
    
    magicrfid_send_command( ctx, MAGICRFID_OPCODE_SET_READER_OPTIONAL_PARAMS, tx_data, 3 );
}

void magicrfid_start_reading ( magicrfid_t *ctx )
{
    uint8_t tx_data[] = { 0x00, 0x00, 0x01, 0x22, 0x00, 0x00, 0x05, 0x07, 0x22, 0x10, 0x00, 0x1B, 
                          0x03, 0xE8, 0x01, 0xFF };

    magicrfid_send_command( ctx, MAGICRFID_OPCODE_MULTI_PROTOCOL_TAG_OP, tx_data, 16 );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

void dev_delay_com ( uint16_t time_ms ) 
{
    for ( uint16_t cnt = 0; cnt < time_ms; cnt++ ) 
    {
        Delay_1ms( );
    }
}

void dev_reset_delay( void ) 
{
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
