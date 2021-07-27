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

#include "fingerprint3.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Check sum function.
 *
 * @param pkg_id      Package Identifier.
 * @param pkg_content Package Content.
 * @param pkg_len     Package Length.
 * 
 * @returns Sum
 *
 * @description This function returns the arithmetic sum of package identifier, 
 *              package length and all package content.
 */
static uint16_t fingerprint3_chk_sum ( uint8_t pkg_id, uint8_t *pkg_content, uint16_t pkg_len );

/**
 * @brief Read response function.
 *
 * @param ctx  Click object.
 * @returns 0 - OK, other - ERROR
 *
 * @description This function reads response and stores it in the click object structure.
 */
static uint8_t fingerprint3_read_response ( fingerprint3_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fingerprint3_cfg_setup ( fingerprint3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

FINGERPRINT3_RETVAL fingerprint3_init ( fingerprint3_t *ctx, fingerprint3_cfg_t *cfg )
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

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );
    
    return FINGERPRINT3_OK;
}

uint8_t fingerprint3_set_config ( fingerprint3_t *ctx, uint32_t addr, uint32_t pass )
{
    ctx->address = addr;
    ctx->password = pass;
    
    uint8_t error_flag = fingerprint3_verify_password ( ctx, ctx->password );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    
    error_flag = fingerprint3_read_product_info ( ctx );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    
    error_flag = fingerprint3_read_system_parameter( ctx );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    
    return FINGERPRINT3_CONF_CMD_OK;
}

void fingerprint3_set_rst_pin ( fingerprint3_t *ctx, uint8_t rst_pin )
{
    if ( rst_pin == 1 )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void fingerprint3_generic_write ( fingerprint3_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t fingerprint3_generic_read ( fingerprint3_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t fingerprint3_send_package ( fingerprint3_t *ctx, uint8_t pkg_id, uint8_t *pkg_content, uint16_t pkg_len )
{
    uint8_t tmp_buf[ FINGERPRINT3_ERR_PACKAGE_LEN ];
    uint16_t checksum;
    
    // Clear RX buffer
    fingerprint3_generic_read ( ctx, tmp_buf, FINGERPRINT3_ERR_PACKAGE_LEN );
    
    // Header
    tmp_buf[ 0 ] = FINGERPRINT3_HEADER_MSB;
    tmp_buf[ 1 ] = FINGERPRINT3_HEADER_LSB;
    uart_write( &ctx->uart, tmp_buf, 2 );
    
    // Address
    tmp_buf[ 0 ] = ( uint8_t ) ( ( ctx->address >> 24 ) & 0xFF );
    tmp_buf[ 1 ] = ( uint8_t ) ( ( ctx->address >> 16 ) & 0xFF );
    tmp_buf[ 2 ] = ( uint8_t ) ( ( ctx->address >> 8 ) & 0xFF );
    tmp_buf[ 3 ] = ( uint8_t ) ( ctx->address & 0xFF );
    uart_write( &ctx->uart, tmp_buf, 4 );
    
    // Package Identifier
    uart_write( &ctx->uart, &pkg_id, 1 );
    
    // Package Length
    pkg_len += 2;
    tmp_buf[ 0 ] = ( uint8_t ) ( ( pkg_len >> 8 ) & 0xFF );
    tmp_buf[ 1 ] = ( uint8_t ) ( pkg_len & 0xFF );
    uart_write( &ctx->uart, tmp_buf, 2 );
    
    // Package Content
    if ( pkg_len > 2 )
    {
        uart_write( &ctx->uart, pkg_content, pkg_len - 2 );  
    }  
    
    // Checksum
    checksum = fingerprint3_chk_sum( pkg_id, pkg_content, pkg_len );
    tmp_buf[ 0 ] = ( uint8_t ) ( ( checksum >> 8 ) & 0xFF );
    tmp_buf[ 1 ] = ( uint8_t ) ( checksum & 0xFF );
    uart_write( &ctx->uart, tmp_buf, 2 );
    
    return fingerprint3_read_response( ctx );
}

uint8_t fingerprint3_finger_indicator ( fingerprint3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t fingerprint3_aura_control ( fingerprint3_t *ctx, uint8_t control, uint8_t speed,
                                                         uint8_t color, uint8_t times )
{
    uint8_t tmp_buf[ 5 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_AURA_CONTROL;
    tmp_buf[ 1 ] = control;
    tmp_buf[ 2 ] = speed;
    tmp_buf[ 3 ] = color;
    tmp_buf[ 4 ] = times;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 5 );
}

uint8_t fingerprint3_verify_password ( fingerprint3_t *ctx, uint32_t pass )
{
    uint8_t tmp_buf[ 5 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_VERIFY_PASSWORD;
    tmp_buf[ 1 ] = ( uint8_t ) ( ( pass >> 24 ) & 0xFF );
    tmp_buf[ 2 ] = ( uint8_t ) ( ( pass >> 16 ) & 0xFF );
    tmp_buf[ 3 ] = ( uint8_t ) ( ( pass >> 8 ) & 0xFF );
    tmp_buf[ 4 ] = ( uint8_t ) ( pass & 0xFF );
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 5 );
}

uint8_t fingerprint3_read_product_info ( fingerprint3_t *ctx )
{
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_READ_PRODUCT_INFO;
    uint8_t error_flag = fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    
    memcpy( ctx->product_info.module_type, &ctx->rsp.pkg_content[ 1 ], 16 );
    memcpy( ctx->product_info.module_batch_number, &ctx->rsp.pkg_content[ 17 ], 4 );
    memcpy( ctx->product_info.module_serial_number, &ctx->rsp.pkg_content[ 21 ], 8 );
    memcpy( ctx->product_info.hardware_version, &ctx->rsp.pkg_content[ 29 ], 2 );
    memcpy( ctx->product_info.sensor_type, &ctx->rsp.pkg_content[ 31 ], 8 );
    
    ctx->product_info.sensor_width = ctx->rsp.pkg_content[ 39 ];
    ctx->product_info.sensor_width <<= 8;
    ctx->product_info.sensor_width |= ctx->rsp.pkg_content[ 40 ];
    
    ctx->product_info.sensor_height = ctx->rsp.pkg_content[ 41 ];
    ctx->product_info.sensor_height <<= 8;
    ctx->product_info.sensor_height |= ctx->rsp.pkg_content[ 42 ];
    
    ctx->product_info.template_size = ctx->rsp.pkg_content[ 43 ];
    ctx->product_info.template_size <<= 8;
    ctx->product_info.template_size |= ctx->rsp.pkg_content[ 44 ];
    
    ctx->product_info.database_size = ctx->rsp.pkg_content[ 45 ];
    ctx->product_info.database_size <<= 8;
    ctx->product_info.database_size |= ctx->rsp.pkg_content[ 46 ];
    
    return FINGERPRINT3_CONF_CMD_OK;
}

uint8_t fingerprint3_read_system_parameter ( fingerprint3_t *ctx )
{
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_READ_SYS_PARAM;
    uint8_t error_flag = fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    
    ctx->system_parameters.status_register = ctx->rsp.pkg_content[ 1 ];
    ctx->system_parameters.status_register <<= 8;
    ctx->system_parameters.status_register |= ctx->rsp.pkg_content[ 2 ];
    
    ctx->system_parameters.system_identifier_code = ctx->rsp.pkg_content[ 3 ];
    ctx->system_parameters.system_identifier_code <<= 8;
    ctx->system_parameters.system_identifier_code |= ctx->rsp.pkg_content[ 4 ];
    
    ctx->system_parameters.finger_library_size = ctx->rsp.pkg_content[ 5 ];
    ctx->system_parameters.finger_library_size <<= 8;
    ctx->system_parameters.finger_library_size |= ctx->rsp.pkg_content[ 6 ];
    
    ctx->system_parameters.security_level = ctx->rsp.pkg_content[ 7 ];
    ctx->system_parameters.security_level <<= 8;
    ctx->system_parameters.security_level |= ctx->rsp.pkg_content[ 8 ];
    
    ctx->system_parameters.device_address = ctx->rsp.pkg_content[ 9 ];
    ctx->system_parameters.device_address <<= 8;
    ctx->system_parameters.device_address |= ctx->rsp.pkg_content[ 10 ];
    ctx->system_parameters.device_address <<= 8;
    ctx->system_parameters.device_address |= ctx->rsp.pkg_content[ 11 ];
    ctx->system_parameters.device_address <<= 8;
    ctx->system_parameters.device_address |= ctx->rsp.pkg_content[ 12 ];
    
    ctx->system_parameters.data_package_size = ctx->rsp.pkg_content[ 13 ];
    ctx->system_parameters.data_package_size <<= 8;
    ctx->system_parameters.data_package_size |= ctx->rsp.pkg_content[ 14 ];
    
    ctx->system_parameters.baudrate = ctx->rsp.pkg_content[ 15 ];
    ctx->system_parameters.baudrate <<= 8;
    ctx->system_parameters.baudrate |= ctx->rsp.pkg_content[ 16 ];
    ctx->system_parameters.baudrate *= 9600;
    
    return FINGERPRINT3_CONF_CMD_OK;
}

uint8_t fingerprint3_set_security_level ( fingerprint3_t *ctx, uint8_t lvl )
{
    uint8_t tmp_buf[ 3 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_SET_SYS_PARAM;
    tmp_buf[ 1 ] = 5;
    tmp_buf[ 2 ] = lvl;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 3 );
}

uint8_t fingerprint3_hand_shake ( fingerprint3_t *ctx )
{
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_HAND_SHAKE;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
}

uint8_t fingerprint3_check_sensor ( fingerprint3_t *ctx )
{
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_CHECK_SENSOR;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
}

uint8_t fingerprint3_soft_reset ( fingerprint3_t *ctx )
{
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_SOFT_RESET;
    uint8_t error_flag = fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    
    uint16_t timeout = 0; 
    
    // Checks if the sensor is ready
    for ( ; ; )
    {
        if ( uart_read( &ctx->uart, &tmp, 1 ) > 0 )
        {
            if ( tmp == 0x55 )
            {
                return FINGERPRINT3_OK;
            }
        }
        else
        {
            if ( timeout++ > FINGERPRINT3_TIMEOUT )
            {
                return FINGERPRINT3_ERR_TIMEOUT;
            }
            Delay_10ms( );
        }
    }    
}

uint8_t fingerprint3_read_index_table ( fingerprint3_t *ctx, uint8_t *table, uint8_t page )
{    
    uint8_t tmp_buf[ 2 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_READ_INDEX_TEMPLATE;
    tmp_buf[ 1 ] = page;
    uint8_t error_flag = fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 2 );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    memcpy ( table, &ctx->rsp.pkg_content[ 1 ], 32 );
    
    return FINGERPRINT3_OK;
}

uint8_t fingerprint3_take_image ( fingerprint3_t *ctx )
{
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_GET_IMAGE;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
}

uint8_t fingerprint3_extract_features ( fingerprint3_t *ctx, uint8_t char_buffer )
{
    uint8_t tmp_buf[ 2 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_IMAGE_2_TZ;
    tmp_buf[ 1 ] = char_buffer;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 2 );
}

uint8_t fingerprint3_create_template ( fingerprint3_t *ctx )
{
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_REG_MODEL;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
}

uint8_t fingerprint3_store_template ( fingerprint3_t *ctx, uint8_t char_buffer, uint16_t location )
{
    uint8_t tmp_buf[ 4 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_STORE;
    tmp_buf[ 1 ] = char_buffer;
    tmp_buf[ 2 ] = ( uint8_t ) ( ( location >> 8 ) & 0xFF );
    tmp_buf[ 3 ] = ( uint8_t ) ( location & 0xFF );
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 4 );
}

uint8_t fingerprint3_delete_template ( fingerprint3_t *ctx, uint16_t location )
{
    uint8_t tmp_buf[ 5 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_DELETE_CHAR;
    tmp_buf[ 1 ] = ( uint8_t ) ( ( location >> 8 ) & 0xFF );
    tmp_buf[ 2 ] = ( uint8_t ) ( location & 0xFF );
    tmp_buf[ 3 ] = 0x00;
    tmp_buf[ 4 ] = 0x01;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 5 );
}

uint8_t fingerprint3_empty_library ( fingerprint3_t *ctx )
{
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_EMPTY;
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
}

uint8_t fingerprint3_load_template ( fingerprint3_t *ctx, uint8_t char_buffer, uint16_t location )
{
    uint8_t tmp_buf[ 4 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_LOAD_CHAR;
    tmp_buf[ 1 ] = char_buffer;
    tmp_buf[ 2 ] = ( uint8_t ) ( ( location >> 8 ) & 0xFF );
    tmp_buf[ 3 ] = ( uint8_t ) ( location & 0xFF );
    return fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 4 );
}

uint8_t fingerprint3_match_finger ( fingerprint3_t *ctx, uint16_t *score )
{    
    uint8_t tmp;
    
    tmp = FINGERPRINT3_CMD_MATCH;
    uint8_t error_flag = fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, &tmp, 1 );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    
    *score = ctx->rsp.pkg_content[ 1 ];
    *score <<= 8;
    *score |= ctx->rsp.pkg_content[ 2 ];
    
    return FINGERPRINT3_OK;
}

uint8_t fingerprint3_search_finger ( fingerprint3_t *ctx, uint8_t char_buffer, uint16_t *location, uint16_t *score )
{    
    uint16_t start_page = 0;
    uint16_t page_count = ctx->system_parameters.finger_library_size;
    uint8_t tmp_buf[ 6 ];
    
    tmp_buf[ 0 ] = FINGERPRINT3_CMD_SEARCH;
    tmp_buf[ 1 ] = char_buffer;
    tmp_buf[ 2 ] = ( uint8_t ) ( ( start_page >> 8 ) & 0xFF );
    tmp_buf[ 3 ] = ( uint8_t ) ( start_page & 0xFF );
    tmp_buf[ 4 ] = ( uint8_t ) ( ( page_count >> 8 ) & 0xFF );
    tmp_buf[ 5 ] = ( uint8_t ) ( page_count & 0xFF );
    
    uint8_t error_flag = fingerprint3_send_package ( ctx, FINGERPRINT3_COMMAND_PACKET, tmp_buf, 6 );
    
    if ( error_flag != FINGERPRINT3_CONF_CMD_OK )
    {
        return error_flag;
    }
    
    *location = ctx->rsp.pkg_content[ 1 ];
    *location <<= 8;
    *location |= ctx->rsp.pkg_content[ 2 ];
    
    *score = ctx->rsp.pkg_content[ 3 ];
    *score <<= 8;
    *score |= ctx->rsp.pkg_content[ 4 ];
    
    return FINGERPRINT3_OK;
}

// ---------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static uint8_t fingerprint3_read_response ( fingerprint3_t *ctx )
{
    uint8_t tmp = 0;
    uint16_t timeout = 0; 
    
    // Check header
    for ( ; ; )
    {
        if ( uart_read( &ctx->uart, &tmp, 1 ) > 0 )
        {
            if ( tmp == FINGERPRINT3_HEADER_MSB )
            {
                ctx->rsp.header = tmp;
                ctx->rsp.header <<= 8;
                Delay_1ms( );
                uart_read( &ctx->uart, &tmp, 1 );
                if ( tmp == FINGERPRINT3_HEADER_LSB )
                {   
                    ctx->rsp.header |= tmp;
                    break;
                }
                else
                {
                    return FINGERPRINT3_ERR_HEADER;
                }
            }
        }
        else
        {
            if ( timeout++ > FINGERPRINT3_TIMEOUT )
            {
                return FINGERPRINT3_ERR_TIMEOUT;
            }
            Delay_10ms( );
        }
    }   
    Delay_10ms( ); 
    Delay_10ms( ); 
    
    // Read address
    uart_read( &ctx->uart, &tmp, 1 );
    ctx->rsp.addr = tmp;
    ctx->rsp.addr <<= 8;
    uart_read( &ctx->uart, &tmp, 1 );
    ctx->rsp.addr |= tmp;
    ctx->rsp.addr <<= 8;
    uart_read( &ctx->uart, &tmp, 1 );
    ctx->rsp.addr |= tmp;
    ctx->rsp.addr <<= 8;
    uart_read( &ctx->uart, &tmp, 1 );
    ctx->rsp.addr |= tmp;
    
    // Package Identifier 
    uart_read( &ctx->uart, &ctx->rsp.pkg_id, 1 );
    
    // Package Length 
    uart_read( &ctx->uart, &tmp, 1 );
    ctx->rsp.pkg_len = tmp;
    ctx->rsp.pkg_len <<= 8;
    uart_read( &ctx->uart, &tmp, 1 );
    ctx->rsp.pkg_len |= tmp;
    
    if ( ctx->rsp.pkg_len > FINGERPRINT3_MAX_PACKAGE_LENGTH || ctx->rsp.pkg_len < 2 )
    {
        return FINGERPRINT3_ERR_PACKAGE_LEN;
    }

    // Package Content
    if ( ctx->rsp.pkg_len > 2 )
    {
        uart_read( &ctx->uart, ctx->rsp.pkg_content, ctx->rsp.pkg_len - 2 );
    } 
    
    // Checksum 
    uart_read( &ctx->uart, &tmp, 1 );
    ctx->rsp.checksum = tmp;
    ctx->rsp.checksum <<= 8;
    uart_read( &ctx->uart, &tmp, 1 );
    ctx->rsp.checksum |= tmp;

    if ( ctx->rsp.checksum == fingerprint3_chk_sum( ctx->rsp.pkg_id, ctx->rsp.pkg_content, ctx->rsp.pkg_len ) )
    {
        return ctx->rsp.pkg_content[ 0 ];
    }
    else
    {
        return FINGERPRINT3_ERR_CHKSUM;
    }
}

static uint16_t fingerprint3_chk_sum ( uint8_t pkg_id, uint8_t *pkg_content, uint16_t pkg_len )
{
    uint16_t res;

    res = pkg_id;
    res += pkg_len;

    for ( uint8_t cnt = 0; cnt < pkg_len - 2; cnt++ )
    {
        res += pkg_content[ cnt ];
    }

    return res;
}

// ------------------------------------------------------------------------- END

