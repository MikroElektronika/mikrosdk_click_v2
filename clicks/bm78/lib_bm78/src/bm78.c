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
 * @file bm78.c
 * @brief BM78 Click Driver.
 */

#include "bm78.h"
#include "bm78_config.h"


void bm78_cfg_setup ( bm78_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->st1 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->st2 = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t bm78_init ( bm78_t *ctx, bm78_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );

    // Input pins
    digital_in_init( &ctx->st1, cfg->st1 );
    digital_in_init( &ctx->st2, cfg->st2 );
    digital_in_init( &ctx->rts, cfg->rts );

    bm78_set_rst_pin( ctx, BM78_PIN_STATE_HIGH );

    return UART_SUCCESS;
}

void bm78_set_rst_pin ( bm78_t *ctx, uint8_t pin_state )
{
    if ( BM78_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void bm78_set_cts_pin ( bm78_t *ctx, uint8_t pin_state )
{
    if ( BM78_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->cts );
    }
    else
    {
        digital_out_low( &ctx->cts );
    }
}

uint8_t bm78_get_st1_pin ( bm78_t *ctx )
{
    return digital_in_read( &ctx->st1 );
}

uint8_t bm78_get_st2_pin ( bm78_t *ctx )
{
    return digital_in_read( &ctx->st2 );
}

uint8_t bm78_get_rts_pin ( bm78_t *ctx )
{
    return digital_in_read( &ctx->rts );
}

void bm78_hw_reset( bm78_t *ctx )
{
    bm78_set_rst_pin( ctx, BM78_PIN_STATE_LOW );
    Delay_100ms();
    bm78_set_rst_pin( ctx, BM78_PIN_STATE_HIGH );
    Delay_100ms();
    Delay_100ms();
}

err_t bm78_generic_write ( bm78_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t bm78_generic_read ( bm78_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t bm78_eeprom_send_cmd ( bm78_t *ctx, uint16_t ofc, uint8_t *param, uint8_t len )
{
    err_t error_flag = BM78_OK;
    uint8_t data_buf[ 50 ] = { 0 };
    data_buf[ 0 ] = BM78_HCI_COMMAND_PACKET;
    data_buf[ 1 ] = ( uint8_t ) ( ofc >> 8 );
    data_buf[ 2 ] = ( uint8_t ) ofc;
    data_buf[ 3 ] = len;
    if ( len > 0 )
    {
        for ( uint8_t n_cnt = 0; n_cnt < len; n_cnt++ )
        {
            data_buf[ 4 + n_cnt ] = param[ n_cnt ];
        }
    }
 
    error_flag |= bm78_generic_write( ctx, data_buf, len + 4 );

    return error_flag;
}

err_t bm78_eeprom_get_event ( bm78_t *ctx, uint8_t *event_type, uint8_t *len, uint8_t *data_rx )
{
    err_t error_flag = BM78_ERROR;
    uint8_t rx_buf[ 50 ] = { 0 };
    
    int32_t rx_size = bm78_generic_read( ctx, rx_buf, 50 );    

    if ( rx_size > 0 )
    {
        *event_type = rx_buf[ 1 ];
        *len = rx_buf[ 2 ];
        for ( uint8_t n_cnt = 0; n_cnt < rx_buf[ 2 ]; n_cnt++ )
        {
            data_rx[ n_cnt ] = rx_buf[ 3 + n_cnt ];
        }
        error_flag = rx_size; 
    }

    return error_flag;
} 

err_t bm78_reset_cmd ( bm78_t *ctx )
{
    err_t error_flag = BM78_OK;
    uint8_t data_buf[ 40 ] = { 0 };
    uint8_t ev_type = 0;
    uint8_t resp_len = 0;
    
    error_flag |= bm78_eeprom_send_cmd( ctx,  BM78_OPCODE_RESET_CMD, data_buf, 0 );
    Delay_100ms();
    error_flag |= bm78_eeprom_get_event( ctx, &ev_type, &resp_len, data_buf );
    if ( BM78_HCI_COMMAND_COMPLETE == ev_type )
    {
        if ( BM78_HCI_COMMAND_PACKET != data_buf[ 0 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) ( BM78_OPCODE_RESET_CMD >> 8 ) != data_buf[ 1 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) BM78_OPCODE_RESET_CMD != data_buf[ 2 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( BM78_HCI_COMMAND_IND_SUCCESS != data_buf[ 3 ] )
        {
            error_flag = BM78_ERROR;
        }
    }
    else
    {
        error_flag = BM78_ERROR;
    }

    return error_flag;
}

err_t bm78_eeprom_write_number ( bm78_t *ctx )
{
    err_t error_flag = BM78_OK;
    uint8_t data_buf[ 40 ] = { 0 };
    uint8_t ev_type = 0;
    uint8_t resp_len = 0;
    
    data_buf[ 0 ] = BM78_PAGE_WRITE_NUMBER; 

    error_flag |= bm78_eeprom_send_cmd( ctx, BM78_HCI_EEPROM_WR_PG_NUM_CMD, data_buf, 1 );
    Delay_100ms();
    error_flag |= bm78_eeprom_get_event( ctx, &ev_type, &resp_len, data_buf );

    if ( BM78_HCI_COMMAND_COMPLETE == ev_type )
    {
        if ( BM78_HCI_COMMAND_PACKET != data_buf[ 0 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) ( BM78_HCI_EEPROM_WR_PG_NUM_CMD >> 8 ) != data_buf[ 1 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) BM78_HCI_EEPROM_WR_PG_NUM_CMD != data_buf[ 2 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( BM78_HCI_COMMAND_IND_SUCCESS != data_buf[ 3 ] )
        {
            error_flag = BM78_ERROR;
        }
    }
    else
    {
        error_flag = BM78_ERROR;
    }

    return error_flag;
}

err_t bm78_eeprom_write ( bm78_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = BM78_OK;
    uint8_t data_buf[ 40 ] = { 0 };
    uint8_t ev_type = 0;
    uint8_t resp_len = 0;
    
    data_buf[ 0 ] = ( uint8_t ) ( address >> 8 ); 
    data_buf[ 1 ] = ( uint8_t ) address; 
    data_buf[ 2 ] = len;
    for ( uint8_t n_cnt = 0; n_cnt < len; n_cnt++ )
    {
        data_buf[ n_cnt + 3 ] = data_in[ n_cnt ];
    } 

    error_flag |= bm78_eeprom_send_cmd( ctx, BM78_HCI_EEPROM_WRITE_CMD, data_buf, len + 3 );
    Delay_100ms();
    error_flag |= bm78_eeprom_get_event( ctx, &ev_type, &resp_len, data_buf );

    if ( BM78_HCI_COMMAND_COMPLETE == ev_type )
    {
        if ( BM78_HCI_COMMAND_PACKET != data_buf[ 0 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) ( BM78_HCI_EEPROM_WRITE_CMD >> 8 ) != data_buf[ 1 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) BM78_HCI_EEPROM_WRITE_CMD != data_buf[ 2 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( BM78_HCI_COMMAND_IND_SUCCESS != data_buf[ 3 ] )
        {
            error_flag = BM78_ERROR;
        }
    }
    else
    {
        error_flag = BM78_ERROR;
    }

    return error_flag;
}

err_t bm78_eeprom_read ( bm78_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = BM78_OK;
    uint8_t data_buf[ 40 ] = { 0 };
    uint8_t ev_type = 0;
    uint8_t resp_len = 0;
    
    data_buf[ 0 ] = ( uint8_t ) ( address >> 8 ); 
    data_buf[ 1 ] = ( uint8_t ) address; 
    data_buf[ 2 ] = len;
 

    error_flag |= bm78_eeprom_send_cmd( ctx, BM78_HCI_EEPROM_READ_CMD, data_buf, 3 );
    Delay_100ms();
    error_flag |= bm78_eeprom_get_event( ctx, &ev_type, &resp_len, data_buf );

    if ( BM78_HCI_COMMAND_COMPLETE == ev_type )
    {
        if ( BM78_HCI_COMMAND_PACKET != data_buf[ 0 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) ( BM78_HCI_EEPROM_READ_CMD >> 8 ) != data_buf[ 1 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) BM78_HCI_EEPROM_READ_CMD != data_buf[ 2 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( BM78_HCI_COMMAND_IND_SUCCESS != data_buf[ 3 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) ( address >> 8 ) != data_buf[ 4 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( ( uint8_t ) address != data_buf[ 5 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( len != data_buf[ 6 ] )
        {
            error_flag = BM78_ERROR;
        }
        if ( BM78_ERROR != error_flag )
        {
            for ( uint8_t n_cnt = 0; n_cnt < data_buf[ 6 ]; n_cnt++ )
            {
                data_out[ n_cnt ] = data_buf[ n_cnt + 7 ];
            }
        }
    }
    else
    {
        error_flag = BM78_ERROR;
    }

    return error_flag;
}

err_t bm78_flash_eeprom ( bm78_t *ctx )
{
    err_t error_flag = BM78_OK;
 
    // Using reset to enable EEPROM operation.
    error_flag |= bm78_reset_cmd( ctx );
    
    // Using bm78_eeprom_write_number to specify the size of the EEPROM write operation.
    error_flag |= bm78_eeprom_write_number( ctx );

    uint8_t data_cmd_buff[ 50 ] = { 0 };
    uint8_t data_read_buff[ 50 ] = { 0 };
    uint8_t eeprom_flashed = 0;
    uint16_t start_address = 0;
    uint16_t data_index_cnt = 0;

    while ( 0 == eeprom_flashed )
    {
        uint16_t data_cnt = 0;

        if ( BM78_END_BYTE == bm78_eeprom_cfg[ data_index_cnt ] )
        {
            eeprom_flashed = 1;
            break;
        }
        else if (  0 == ( bm78_eeprom_cfg[ data_index_cnt ] & BM78_SKIP_BYTE ) )
        {
            start_address = data_index_cnt;
            while ( ( BM78_SKIP_BYTE != ( bm78_eeprom_cfg[ data_index_cnt ] & BM78_SKIP_BYTE ) ) && ( 32 >= data_cnt ) )
            {
                if ( BM78_END_BYTE == bm78_eeprom_cfg[ data_index_cnt ] )
                {
                    eeprom_flashed = 1;
                    break;
                }
                data_cmd_buff[ data_cnt ] = ( uint8_t ) ( bm78_eeprom_cfg[ data_index_cnt ] & 0x00FF ) ;
                data_cnt++;
                data_index_cnt++;
            }

            error_flag |= bm78_eeprom_write( ctx, start_address, data_cmd_buff, data_cnt );
            error_flag |= bm78_eeprom_read( ctx, start_address, data_read_buff, data_cnt );
            for ( uint8_t n_cnt = 0; n_cnt < data_cnt; n_cnt++ )
            {
                if ( data_cmd_buff[ n_cnt ] != data_read_buff[ n_cnt ] )
                {
                    return BM78_ERROR;
                }
            }

        }
        else
        {
            data_index_cnt++;
        }

    }

    return error_flag;
}






// ------------------------------------------------------------------------- END
