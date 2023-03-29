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
 * @file rfid.c
 * @brief RFID Click Driver.
 */

#include "rfid.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void rfid_cfg_setup ( rfid_cfg_t *cfg ) 
{
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->rx_pin  = HAL_PIN_NC;
    cfg->tx_pin  = HAL_PIN_NC;
    cfg->ssi_1   = HAL_PIN_NC;
    cfg->ssi_0   = HAL_PIN_NC;
    cfg->irq_in  = HAL_PIN_NC;
    cfg->irq_out = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t rfid_init ( rfid_t *ctx, rfid_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;
    uart_config_t uart_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
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
    
    digital_out_init( &ctx->ssi_1, cfg->ssi_1 );
    digital_out_init( &ctx->ssi_0, cfg->ssi_0 );
    digital_out_init( &ctx->irq_in, cfg->irq_in );
    
    digital_in_init( &ctx->irq_out, cfg->irq_out );

    return SPI_MASTER_SUCCESS;
}

err_t rfid_default_cfg ( rfid_t *ctx ) 
{
    // Click default configuration.
    err_t error_flag = rfid_calibration( ctx );
    error_flag |= rfid_set_index_mod_and_gain( ctx );
    error_flag |= rfid_auto_detect_filter( ctx );
    error_flag |= rfid_select_rfid_protocol( ctx, RFID_ISO_14443A );
    
    return error_flag;
}

err_t rfid_send_command ( rfid_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    if ( RFID_SPI == ctx->com_interface )
    {
        uint8_t tx_buf[ 257 ];
        tx_buf[ 0 ] = RFID_SEND_CMD_CRTL;
        tx_buf[ 1 ] = cmd;
        tx_buf[ 2 ] = len;
        for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
        {
            tx_buf[ cnt + 3 ] = data_in[ cnt ];
        }

        spi_master_select_device( ctx->chip_select );
        err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 3 );
        spi_master_deselect_device( ctx->chip_select );

        return error_flag;
    }
    else if ( RFID_UART == ctx->com_interface )
    {
        // clear uart buffer
        {
            uint8_t tmp[ 100 ];
            uart_read( &ctx->uart, tmp, 100 );
        }
        
        uart_write( &ctx->uart, &cmd, 1 );
        Delay_1ms( );
        if ( len > 0 )
        {
            uart_write( &ctx->uart, &len, 1 );
            Delay_1ms( );
            for ( uint8_t cnt = 0; cnt < len; cnt++ )
            {
                uart_write( &ctx->uart, &data_in[ cnt ], 1 );
                Delay_1ms( );
            }
        }
        Delay_10ms( );
        return RFID_OK;
    }
}

err_t rfid_read_data ( rfid_t *ctx, uint8_t *data_out ) 
{
    if ( RFID_SPI == ctx->com_interface )
    {
        while ( rfid_data_ready ( ctx ) != RFID_DATA_READY )
        {
            Delay_1ms( );
        }
        uint8_t tmp = RFID_READ_CTRL;
        spi_master_select_device( ctx->chip_select );
        err_t error_flag = spi_master_write_then_read( &ctx->spi, &tmp, 1, data_out, 2 );
        if ( data_out [ 1 ] > 0 )
        {
            error_flag |= spi_master_read( &ctx->spi, &data_out[ 2 ], data_out[ 1 ] );
        }
        spi_master_deselect_device( ctx->chip_select );

        return error_flag;
    }
    else if ( RFID_UART == ctx->com_interface )
    {
        int32_t rx_size = uart_read( &ctx->uart, ctx->rx_data, 2 );
        if ( rx_size == 2 )
        {
            if ( ctx->rx_data[ 1 ] > 0 )
            {
                rx_size = uart_read( &ctx->uart, &ctx->rx_data[ 2 ], ctx->rx_data[ 1 ] );
                if ( rx_size > 0 )
                {
                    return RFID_OK;
                }
                else
                {
                    return RFID_ERROR;
                }
            }
            else
            {
                return RFID_OK;
            }
        }
        else if ( rx_size > 0 )
        {
            return RFID_OK;
        }
        else
        {
            return RFID_ERROR;
        }
    }

    return RFID_ERROR;
}

uint8_t rfid_data_ready ( rfid_t *ctx ) 
{
    if ( RFID_SPI == ctx->com_interface )
    {
        uint8_t tmp;
        if ( spi_master_set_default_write_data( &ctx->spi, RFID_POLL_CTRL ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }
        
        spi_master_select_device( ctx->chip_select );
        spi_master_read( &ctx->spi, &tmp, 1 );
        spi_master_deselect_device( ctx->chip_select );

        if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }
        
        if ( tmp & RFID_DATA_READY )
        {
            return RFID_DATA_READY;
        }
    }

    return RFID_DATA_NOT_READY;
}

err_t rfid_reset ( rfid_t *ctx ) 
{
    if ( RFID_SPI == ctx->com_interface )
    {
        uint8_t tmp = RFID_RESET_CTRL;

        spi_master_select_device( ctx->chip_select );
        err_t error_flag = spi_master_write( &ctx->spi, &tmp, 1 );
        spi_master_deselect_device( ctx->chip_select );
        
        return error_flag;
    }

    return RFID_ERROR;
}

err_t rfid_check_echo ( rfid_t *ctx ) 
{
    if ( RFID_SPI == ctx->com_interface )
    {
        uint8_t tmp[ 2 ] = { 0 };
        spi_master_select_device( ctx->chip_select );
        tmp[ 0 ] = RFID_SEND_CMD_CRTL;
        tmp[ 1 ] = RFID_ECHO;
        spi_master_write( &ctx->spi, tmp, 2 );
        spi_master_deselect_device( ctx->chip_select );
        
        while ( rfid_data_ready ( ctx ) != RFID_DATA_READY )
        {
            Delay_1ms( );
        }
        
        spi_master_select_device( ctx->chip_select );
        tmp[ 0 ] = RFID_READ_CTRL;
        spi_master_write( &ctx->spi, tmp, 1 );
        spi_master_read( &ctx->spi, tmp, 1 );
        spi_master_deselect_device( ctx->chip_select );
        
        if ( tmp[ 0 ] == RFID_ECHO )
        {
            return RFID_OK;
        }

        return RFID_ERROR;
    }
    else if ( RFID_UART == ctx->com_interface )
    {
        uint8_t tmp = RFID_ECHO;
        uart_write( &ctx->uart, &tmp, 1 );
        Delay_100ms( );
        int32_t rx_size = uart_read( &ctx->uart, &tmp, 1 );
        if ( rx_size > 0 && tmp == RFID_ECHO )
        {
            return RFID_OK;
        }
        else
        {
            return RFID_ERROR;
        }
    }

    return RFID_ERROR;
}

err_t rfid_select_communication_interface ( rfid_t* ctx, uint8_t com_interface )
{
    if ( RFID_UART == com_interface )
    {
        ctx->com_interface = com_interface;
        digital_out_low( &ctx->ssi_1 );
        digital_out_low( &ctx->ssi_0 );
    }
    else if ( RFID_SPI == com_interface )
    {
        ctx->com_interface = com_interface;
        digital_out_low( &ctx->ssi_1 );
        digital_out_high( &ctx->ssi_0 );
        Delay_1ms();
        
        digital_out_high( &ctx->irq_in );
        Delay_1ms();
        digital_out_low( &ctx->irq_in );
        Delay_1ms( );
        digital_out_high( &ctx->irq_in );
        Delay_1ms( );
    }
    Delay_1sec( );
    
    if ( rfid_check_echo ( ctx ) != RFID_OK )
    {
        return RFID_ERROR;
    }
    
    return RFID_OK;
}

err_t rfid_calibration ( rfid_t *ctx ) 
{
    uint8_t tx_data[ 20 ];
    
    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = 0xA1;
    tx_data[ 2 ] = 0x00;
    tx_data[ 3 ] = 0xF8;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x18;
    tx_data[ 6 ] = 0x00;
    tx_data[ 7 ] = 0x20;
    tx_data[ 8 ] = 0x60;
    tx_data[ 9 ] = 0x60;
    tx_data[ 10 ] = 0x00;
    tx_data[ 11 ] = 0x00;
    tx_data[ 12 ] = 0x3F;
    tx_data[ 13 ] = 0x01;
    err_t error_flag = rfid_send_command ( ctx, RFID_IDLE, tx_data, 14 );
    Delay_1sec( );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );

    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = 0xA1;
    tx_data[ 2 ] = 0x00;
    tx_data[ 3 ] = 0xF8;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x18;
    tx_data[ 6 ] = 0x00;
    tx_data[ 7 ] = 0x20;
    tx_data[ 8 ] = 0x60;
    tx_data[ 9 ] = 0x60;
    tx_data[ 10 ] = 0x00;
    tx_data[ 11 ] = 0xFC;
    tx_data[ 12 ] = 0x3F;
    tx_data[ 13 ] = 0x01;
    error_flag |= rfid_send_command ( ctx, RFID_IDLE, tx_data, 14 );
    Delay_1sec( );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );

    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = 0xA1;
    tx_data[ 2 ] = 0x00;
    tx_data[ 3 ] = 0xF8;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x18;
    tx_data[ 6 ] = 0x00;
    tx_data[ 7 ] = 0x20;
    tx_data[ 8 ] = 0x60;
    tx_data[ 9 ] = 0x60;
    tx_data[ 10 ] = 0x00;
    tx_data[ 11 ] = 0x7C;
    tx_data[ 12 ] = 0x3F;
    tx_data[ 13 ] = 0x01;
    error_flag |= rfid_send_command ( ctx, RFID_IDLE, tx_data, 14 );
    Delay_1sec( );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );

    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = 0xA1;
    tx_data[ 2 ] = 0x00;
    tx_data[ 3 ] = 0xF8;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x18;
    tx_data[ 6 ] = 0x00;
    tx_data[ 7 ] = 0x20;
    tx_data[ 8 ] = 0x60;
    tx_data[ 9 ] = 0x60;
    tx_data[ 10 ] = 0x00;
    tx_data[ 11 ] = 0x3C;
    tx_data[ 12 ] = 0x3F;
    tx_data[ 13 ] = 0x01;
    error_flag |= rfid_send_command ( ctx, RFID_IDLE, tx_data, 14 );
    Delay_1sec( );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );

    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = 0xA1;
    tx_data[ 2 ] = 0x00;
    tx_data[ 3 ] = 0xF8;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x18;
    tx_data[ 6 ] = 0x00;
    tx_data[ 7 ] = 0x20;
    tx_data[ 8 ] = 0x60;
    tx_data[ 9 ] = 0x60;
    tx_data[ 10 ] = 0x00;
    tx_data[ 11 ] = 0x5C;
    tx_data[ 12 ] = 0x3F;
    tx_data[ 13 ] = 0x01;
    error_flag |= rfid_send_command ( ctx, RFID_IDLE, tx_data, 14 );
    Delay_1sec( );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );

    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = 0xA1;
    tx_data[ 2 ] = 0x00;
    tx_data[ 3 ] = 0xF8;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x18;
    tx_data[ 6 ] = 0x00;
    tx_data[ 7 ] = 0x20;
    tx_data[ 8 ] = 0x60;
    tx_data[ 9 ] = 0x60;
    tx_data[ 10 ] = 0x00;
    tx_data[ 11 ] = 0x6C;
    tx_data[ 12 ] = 0x3F;
    tx_data[ 13 ] = 0x01;
    error_flag |= rfid_send_command ( ctx, RFID_IDLE, tx_data, 14 );
    Delay_1sec( );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );

    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = 0xA1;
    tx_data[ 2 ] = 0x00;
    tx_data[ 3 ] = 0xF8;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x18;
    tx_data[ 6 ] = 0x00;
    tx_data[ 7 ] = 0x20;
    tx_data[ 8 ] = 0x60;
    tx_data[ 9 ] = 0x60;
    tx_data[ 10 ] = 0x00;
    tx_data[ 11 ] = 0x74;
    tx_data[ 12 ] = 0x3F;
    tx_data[ 13 ] = 0x01;
    error_flag |= rfid_send_command ( ctx, RFID_IDLE, tx_data, 14 );
    Delay_1sec( );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );

    tx_data[ 0 ] = 0x03;
    tx_data[ 1 ] = 0xA1;
    tx_data[ 2 ] = 0x00;
    tx_data[ 3 ] = 0xF8;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x18;
    tx_data[ 6 ] = 0x00;
    tx_data[ 7 ] = 0x20;
    tx_data[ 8 ] = 0x60;
    tx_data[ 9 ] = 0x60;
    tx_data[ 10 ] = 0x00;
    tx_data[ 11 ] = 0x70;
    tx_data[ 12 ] = 0x3F;
    tx_data[ 13 ] = 0x01;
    error_flag |= rfid_send_command ( ctx, RFID_IDLE, tx_data, 14 );
    Delay_1sec( );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );
    
    return error_flag;
}

err_t rfid_get_device_id ( rfid_t *ctx, uint8_t *device_id ) 
{
    err_t error_flag = rfid_send_command ( ctx, RFID_IDN, NULL, 0 );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );
    for ( uint8_t cnt = 0; cnt < ctx->rx_data[ 1 ]; cnt++ )
    {
        device_id[ cnt ] = ctx->rx_data[ cnt + 2 ];
    }
    
    return error_flag;
}

err_t rfid_select_rfid_protocol ( rfid_t *ctx, uint8_t rfid_protocol ) 
{
    err_t error_flag;
    
    switch ( rfid_protocol )
    {
        case RFID_ISO_14443A: 
        {
            uint8_t tx_data[ 2 ] = { 0 };
            tx_data[ 0 ] = RFID_ISO_14443A;
            tx_data[ 1 ] = 0x00;
            error_flag = rfid_send_command ( ctx, RFID_PROT_SELECT, tx_data, 2 );
            error_flag |= rfid_read_data ( ctx, ctx->rx_data );
            error_flag |= ctx->rx_data[ 0 ] | ctx->rx_data[ 1 ];
            break;
        }
        case RFID_ISO_18092NFC: 
        {
            uint8_t tx_data[ 2 ] = { 0 };
            tx_data[ 0 ] = RFID_ISO_18092NFC;
            tx_data[ 1 ] = 0x51;
            error_flag = rfid_send_command ( ctx, RFID_PROT_SELECT, tx_data, 2 );
            error_flag |= rfid_read_data ( ctx, ctx->rx_data );
            error_flag |= ctx->rx_data[ 0 ] | ctx->rx_data[ 1 ];
            break;
        }
        default:
        {
            uint8_t tx_data[ 2 ] = { 0 };
            tx_data[ 0 ] = RFID_ISO_14443A;
            tx_data[ 1 ] = 0x00;
            error_flag = rfid_send_command ( ctx, RFID_PROT_SELECT, tx_data, 2 );
            error_flag |= rfid_read_data ( ctx, ctx->rx_data );
            error_flag |= ctx->rx_data[ 0 ] | ctx->rx_data[ 1 ];
            break;
        }
    }

    return error_flag;
}

err_t rfid_set_index_mod_and_gain ( rfid_t *ctx ) 
{
    uint8_t tx_data[ 6 ];
    
    tx_data[ 0 ] = 0x09;
    tx_data[ 1 ] = 0x04;
    tx_data[ 2 ] = 0x68;
    tx_data[ 3 ] = 0x01;
    tx_data[ 4 ] = 0x01;
    tx_data[ 5 ] = 0x50;
    err_t error_flag = rfid_send_command ( ctx, RFID_WR_WAKEUP_REG, tx_data, 6 );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );
    
    return error_flag;
}

err_t rfid_auto_detect_filter ( rfid_t *ctx ) 
{
    uint8_t tx_data[ 6 ];
    
    tx_data[ 0 ] = 0x09;
    tx_data[ 1 ] = 0x04;
    tx_data[ 2 ] = 0x0A;
    tx_data[ 3 ] = 0x01;
    tx_data[ 4 ] = 0x02;
    tx_data[ 5 ] = 0xA1;
    err_t error_flag = rfid_send_command ( ctx, RFID_WR_WAKEUP_REG, tx_data, 6 );
    error_flag |= rfid_read_data ( ctx, ctx->rx_data );
    
    return error_flag;
}

err_t rfid_get_tag_uid ( rfid_t *ctx, uint8_t rfid_protocol, uint8_t *tag_uid ) 
{
    err_t error_flag = RFID_ERROR;
    
    switch ( rfid_protocol )
    {
        case RFID_ISO_14443A: 
        {
            while ( rfid_select_rfid_protocol ( ctx, rfid_protocol ) != RFID_OK )
            {
                Delay_100ms( );
            }
            uint8_t tx_data[ 20 ] = { 0 };
            tx_data[ 0 ] = 0x26;
            tx_data[ 1 ] = 0x07;
            error_flag = rfid_send_command ( ctx, RFID_SEND_RECV, tx_data, 2 );
            error_flag |= rfid_read_data ( ctx, ctx->rx_data );
            tx_data[ 0 ] = 0x93;
            tx_data[ 1 ] = 0x20;
            tx_data[ 2 ] = 0x08;
            error_flag |= rfid_send_command ( ctx, RFID_SEND_RECV, tx_data, 3 ); // Anti-collision CL1
            error_flag |= rfid_read_data ( ctx, ctx->rx_data );
            if ( ctx->rx_data[ 0 ] == 0x80 )
            {
                uint8_t cnt = 0;
                if ( ctx->rx_data[ 2 ] == 0x88 ) // check for CT byte
                {
                    for ( cnt = 0; cnt < ctx->rx_data[ 1 ] - 5; cnt++ )
                    {
                        tag_uid[ cnt ] = ctx->rx_data[ cnt + 3 ];
                        tx_data[ cnt + 3 ] = tag_uid[ cnt ];
                    }
                    tx_data[ 0 ] = 0x93;
                    tx_data[ 1 ] = 0x70;
                    tx_data[ 2 ] = 0x88;
                    tx_data[ cnt + 3 ] = ctx->rx_data[ cnt + 3 ];
                    tx_data[ cnt + 4 ] = 0x28;
                    error_flag |= rfid_send_command ( ctx, RFID_SEND_RECV, tx_data, ctx->rx_data[ 1 ] ); // Select CL1
                    error_flag |= rfid_read_data ( ctx, ctx->rx_data );
                    tx_data[ 0 ] = 0x95;
                    tx_data[ 1 ] = 0x20;
                    tx_data[ 2 ] = 0x08;
                    error_flag |= rfid_send_command ( ctx, RFID_SEND_RECV, tx_data, 3 ); // Anti-collision CL2
                    error_flag |= rfid_read_data ( ctx, ctx->rx_data );
                    
                    for ( ; cnt < ctx->rx_data[ 1 ] - 1; cnt++ )
                    {
                        tag_uid[ cnt ] = ctx->rx_data[ cnt - 1 ];
                        tx_data[ cnt - 1 ] = tag_uid[ cnt ];
                    }
                    tx_data[ 0 ] = 0x95;
                    tx_data[ 1 ] = 0x70;
                    tx_data[ cnt - 1 ] = ctx->rx_data[ cnt - 1 ];
                    tx_data[ cnt ] = 0x28;
                    error_flag |= rfid_send_command ( ctx, RFID_SEND_RECV, tx_data, ctx->rx_data[ 1 ] ); // Select CL2
                    error_flag |= rfid_read_data ( ctx, ctx->rx_data );
                }
                else
                {
                    for ( cnt = 0; cnt < ctx->rx_data[ 1 ] - 4; cnt++ )
                    {
                        tag_uid[ cnt ] = ctx->rx_data[ cnt + 2 ];
                        tx_data[ cnt + 2 ] = tag_uid[ cnt ];
                    }
                    
                    tx_data[ 0 ] = 0x93;
                    tx_data[ 1 ] = 0x70;
                    tx_data[ cnt + 2 ] = ctx->rx_data[ cnt + 2 ];
                    tx_data[ cnt + 3 ] = 0x28;
                    error_flag |= rfid_send_command ( ctx, RFID_SEND_RECV, tx_data, ctx->rx_data[ 1 ] ); // Select CL1
                    error_flag |= rfid_read_data ( ctx, ctx->rx_data );
                }
                
                return cnt;
            }
            break;
        }
        case RFID_ISO_18092NFC: 
        {
            while ( rfid_select_rfid_protocol ( ctx, rfid_protocol ) != RFID_OK )
            {
                Delay_100ms( );
            }
            uint8_t tx_data[ 5 ] = { 0 };
            tx_data[ 0 ] = 0x00;
            tx_data[ 1 ] = 0xFF;
            tx_data[ 2 ] = 0xFF;
            tx_data[ 3 ] = 0x00;
            tx_data[ 4 ] = 0x00;
            error_flag = rfid_send_command ( ctx, RFID_SEND_RECV, tx_data, 2 );
            error_flag |= rfid_read_data ( ctx, ctx->rx_data );
            if ( ctx->rx_data[ 0 ] == 0x80 )
            {
                uint8_t cnt;
                for ( cnt = 0; cnt < ctx->rx_data[ 1 ]; cnt++ )
                {
                    tag_uid[ cnt ] = ctx->rx_data[ cnt + 2 ];
                }
                return cnt;
            }
            break;
        }
        default:
        {
            break;
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
