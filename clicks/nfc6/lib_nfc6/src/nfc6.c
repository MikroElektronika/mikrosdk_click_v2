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
 * @file nfc6.c
 * @brief NFC 6 Click Driver.
 */

#include "nfc6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void nfc6_cfg_setup ( nfc6_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->irq_in = HAL_PIN_NC;
    cfg->irq_out = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t nfc6_init ( nfc6_t *ctx, nfc6_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->irq_in, cfg->irq_in );

    digital_in_init( &ctx->irq_out, cfg->irq_out );

    return SPI_MASTER_SUCCESS;
}

err_t nfc6_default_cfg ( nfc6_t *ctx ) 
{
    err_t error_flag = NFC6_OK;
    nfc6_pulse_irq_in ( ctx );
    nfc6_reset_device ( ctx );
    if ( NFC6_ERROR == nfc6_check_command_echo ( ctx ) )
    {
        return NFC6_ERROR;
    }
    error_flag |= nfc6_calibrate_device ( ctx );
    return error_flag;
}

err_t nfc6_send_command ( nfc6_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    uint8_t control_byte = NFC6_CONTROL_SEND_COMMAND;
    if ( ( NULL == data_in ) && ( len > 0 ) )
    {
        return NFC6_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &control_byte, 1 );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    if ( NFC6_CMD_ECHO != cmd )
    {
        error_flag |= spi_master_write( &ctx->spi, &len, 1 );
        if ( len )
        {
            error_flag |= spi_master_write( &ctx->spi, data_in, len );
        }
    }
    spi_master_deselect_device( ctx->chip_select );
    Delay_10us ( );
    return error_flag;
}

err_t nfc6_read_data ( nfc6_t *ctx, uint8_t *data_out, uint16_t buffer_size, uint16_t *rx_len )
{
    uint8_t control_byte = NFC6_CONTROL_READ_DATA;
    uint16_t long_len = 0;
    uint8_t short_len = 0;
    uint8_t resp_code = 0;
    err_t error_flag = NFC6_OK;
    if ( NFC6_ERROR == nfc6_poll_ready_irq ( ctx ) )
    {
        return NFC6_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, &control_byte, 1, &resp_code, 1 );
    // No need to read more bytes if response code is a command echo
    if ( ( NFC6_OK == error_flag ) && ( NFC6_RSP_ECHO == resp_code ) )
    {
        error_flag = NFC6_RSP_ECHO;
    }
    else if ( NFC6_OK == error_flag )
    {
        error_flag |= spi_master_read( &ctx->spi, &short_len, 1 );
        long_len = short_len;
        // Check if response is in a long length format
        if ( NFC6_RSP_FIXED_BYTES == ( resp_code & NFC6_RSP_FIXED_BYTES_MASK ) )
        {
            long_len |= ( ( uint16_t ) ( resp_code & NFC6_RSP_LONG_FRAME_MASK ) << 3 );
            resp_code &= ( ~NFC6_RSP_LONG_FRAME_MASK );
        }
        // Read response data if there's no errors in response code
        if ( ( NFC6_OK == error_flag ) && ( long_len ) &&
             ( ( NFC6_RSP_FIXED_BYTES == resp_code ) || ( NFC6_RSP_OK == resp_code ) ) )
        {
            if ( long_len > NFC6_RSP_MAX_DATA_LEN )
            {
                long_len = NFC6_RSP_MAX_DATA_LEN;
            }
            // Output the number of data bytes that were available for read
            if ( NULL != rx_len )
            {
                *rx_len = long_len;
            }
            if ( NULL != data_out )
            {
                if ( long_len > buffer_size )
                {
                    // Read the buffer size number of bytes to data output buffer
                    error_flag |= spi_master_read( &ctx->spi, data_out, buffer_size );
                    // Dummy read the rest of available bytes to clear RX interrupt
                    while ( long_len > buffer_size )
                    {
                        error_flag |= spi_master_read( &ctx->spi, &resp_code, 1 );
                        long_len--;
                    }
                }
                else
                {
                    // Read all available data bytes to data output buffer
                    error_flag |= spi_master_read( &ctx->spi, data_out, long_len ); 
                }
            }
            else
            {
                // Dummy read the available bytes to clear RX interrupt
                while ( long_len )
                {
                    error_flag |= spi_master_read( &ctx->spi, &resp_code, 1 );
                    long_len--;
                }
            }
        }
        // There's an error flag in a response code
        else if ( NFC6_OK == error_flag ) 
        {
            error_flag = resp_code;
        }
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t nfc6_poll_ready ( nfc6_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t control_byte = NFC6_CONTROL_POLL_READY;
    uint8_t flag = DUMMY;
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, control_byte );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &control_byte, 1, &flag, 1 );
    while ( NFC6_CONTROL_POLL_READY_FLAG != ( flag & NFC6_CONTROL_POLL_READY_FLAG ) )
    {
        error_flag |= spi_master_read( &ctx->spi, &flag, 1 );
        Delay_1ms ( );
        if ( ++timeout_cnt > NFC6_RSP_READY_TIMEOUT_MS )
        {
            error_flag = NFC6_ERROR;
            break;
        }
    }
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t nfc6_poll_ready_irq ( nfc6_t *ctx )
{
    err_t error_flag = NFC6_OK;
    uint32_t timeout_cnt = 0;
    while ( nfc6_get_irq_out_pin ( ctx ) )
    {
        if ( ++timeout_cnt > ( NFC6_RSP_READY_TIMEOUT_MS * 20 ) )
        {
            error_flag = NFC6_ERROR;
            break;
        }
        Delay_50us ( );
    }
    return error_flag;
}

err_t nfc6_reset_device ( nfc6_t *ctx )
{
    uint8_t control_byte = NFC6_CONTROL_RESET_DEVICE;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &control_byte, 1 );
    Delay_1ms ( );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    nfc6_pulse_irq_in ( ctx );
    return error_flag;
}

err_t nfc6_check_command_echo ( nfc6_t *ctx )
{
    err_t error_flag = nfc6_send_command( ctx, NFC6_CMD_ECHO, NULL, NULL );
    if ( NFC6_RSP_ECHO != nfc6_read_data ( ctx, NULL, NULL, NULL ) )
    {
        error_flag |= NFC6_ERROR;
    }
    return error_flag;
}

void nfc6_pulse_irq_in ( nfc6_t *ctx )
{
    digital_out_high( &ctx->irq_in );
    Delay_1ms ( );
    digital_out_low( &ctx->irq_in );
    Delay_1ms ( );
    digital_out_high( &ctx->irq_in );
    Delay_10ms ( );
    Delay_10ms ( );
}

void nfc6_set_irq_in_pin ( nfc6_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->irq_in, state );
}

uint8_t nfc6_get_irq_out_pin ( nfc6_t *ctx )
{
    return digital_in_read ( &ctx->irq_out );
}

err_t nfc6_calibrate_device ( nfc6_t *ctx )
{
    err_t error_flag = NFC6_OK;
    uint8_t step_cnt = 0;
    uint8_t data_buf[ NFC6_IDLE_CMD_LENGTH ] = { 0 };
    uint8_t resp_buf[ NFC6_IDLE_RSP_LENGTH ] = { 0 };
    data_buf[ 0 ] = NFC6_IDLE_CMD_WU_SOURCE;
    data_buf[ 1 ] = NFC6_IDLE_CMD_ENTER_CTRL_L;
    data_buf[ 2 ] = NFC6_IDLE_CMD_ENTER_CTRL_H;
    data_buf[ 3 ] = NFC6_IDLE_CMD_WU_CTRL_L;
    data_buf[ 4 ] = NFC6_IDLE_CMD_WU_CTRL_H;
    data_buf[ 5 ] = NFC6_IDLE_CMD_LEAVE_CTRL_L;
    data_buf[ 6 ] = NFC6_IDLE_CMD_LEAVE_CTRL_H;
    data_buf[ 7 ] = NFC6_IDLE_CMD_WU_PERIOD;
    data_buf[ 8 ] = NFC6_IDLE_CMD_OSC_START;
    data_buf[ 9 ] = NFC6_IDLE_CMD_DAC_START;
    data_buf[ 10 ] = NFC6_IDLE_CMD_DAC_DATA_L;
    data_buf[ 11 ] = NFC6_IDLE_CMD_DAC_DATA_H;
    data_buf[ 12 ] = NFC6_IDLE_CMD_SWINGS_CNT;
    data_buf[ 13 ] = NFC6_IDLE_CMD_MAX_SLEEP;
    
    // Check that wake up detection is tag detect (0x02) when DAC Data H is min DAC value 0x00
    data_buf[ 11 ] = NFC6_IDLE_CMD_DAC_DATA_H_MIN;
    error_flag |= nfc6_send_command( ctx, NFC6_CMD_IDLE, data_buf, NFC6_IDLE_CMD_LENGTH );
    error_flag |= nfc6_read_data ( ctx, resp_buf, sizeof ( resp_buf ), NULL );
    if ( NFC6_IDLE_RSP_TAG_DETECT != resp_buf[ 0 ] )
    {
        error_flag |= NFC6_ERROR;
    }
    
    if ( NFC6_OK == error_flag )
    {
        // Check that wake up detection is timeout (0x01) when DAC Data H is max DAC value 0xFC
        data_buf[ 11 ] = NFC6_IDLE_CMD_DAC_DATA_H_MAX;
        error_flag |= nfc6_send_command( ctx, NFC6_CMD_IDLE, data_buf, NFC6_IDLE_CMD_LENGTH );
        error_flag |= nfc6_read_data ( ctx, resp_buf, sizeof ( resp_buf ), NULL );
        if ( NFC6_IDLE_RSP_TIMEOUT != resp_buf[ 0 ] )
        {
            error_flag |= NFC6_ERROR;
        }
    }
    
    if ( NFC6_OK == error_flag )
    {
        for ( step_cnt = 0; step_cnt < 6; step_cnt++ )
        {
            if ( NFC6_IDLE_RSP_TIMEOUT == resp_buf[ 0 ] )
            {
                data_buf[ 11 ] -= ( NFC6_IDLE_CALIB_START >> step_cnt );
            }
            else if ( NFC6_IDLE_RSP_TAG_DETECT == resp_buf[ 0 ] )
            {
                data_buf[ 11 ] += ( NFC6_IDLE_CALIB_START >> step_cnt );
            }
            else
            {
                error_flag |= NFC6_ERROR;
                break;
            }
            error_flag |= nfc6_send_command( ctx, NFC6_CMD_IDLE, data_buf, NFC6_IDLE_CMD_LENGTH );
            error_flag |= nfc6_read_data ( ctx, resp_buf, sizeof ( resp_buf ), NULL );
        }
        ctx->cal_dac_data_h = data_buf[ 11 ];
    }
    
    return error_flag;
}

err_t nfc6_select_protocol ( nfc6_t *ctx, uint8_t protocol )
{
    err_t error_flag = NFC6_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    switch ( protocol )
    {
        case NFC6_PROTOCOL_FIELD_OFF: 
        {
            data_buf[ 0 ] = NFC6_PROTOCOL_FIELD_OFF;
            error_flag |= nfc6_send_command ( ctx, NFC6_CMD_PROTOCOL_SELECT, data_buf, 1 );
            error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
            break;
        }
        case NFC6_PROTOCOL_ISO_15693: 
        {
            data_buf[ 0 ] = NFC6_PROTOCOL_ISO_15693;
            data_buf[ 1 ] = 0x01; // H 100 S mode
            error_flag |= nfc6_send_command ( ctx, NFC6_CMD_PROTOCOL_SELECT, data_buf, 2 );
            error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
            break;
        }
        case NFC6_PROTOCOL_ISO_14443A: 
        {
            data_buf[ 0 ] = NFC6_PROTOCOL_ISO_14443A;
            data_buf[ 1 ] = 0x00; // 106 Kbps transmission and reception rates
            error_flag |= nfc6_send_command ( ctx, NFC6_CMD_PROTOCOL_SELECT, data_buf, 2 );
            error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
            break;
        }
        case NFC6_PROTOCOL_ISO_14443B: 
        {
            data_buf[ 0 ] = NFC6_PROTOCOL_ISO_14443B;
            data_buf[ 1 ] = 0x01; // 106 Kbps transmission and reception rates with CRC appended
            error_flag |= nfc6_send_command ( ctx, NFC6_CMD_PROTOCOL_SELECT, data_buf, 2 );
            error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
            break;
        }
        case NFC6_PROTOCOL_FELICA: 
        {
            data_buf[ 0 ] = NFC6_PROTOCOL_FELICA;
            data_buf[ 1 ] = 0x51; // 212 Kbps transmission and reception rates with CRC appended
            error_flag |= nfc6_send_command ( ctx, NFC6_CMD_PROTOCOL_SELECT, data_buf, 2 );
            error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
            break;
        }
        default:
        {
            error_flag = NFC6_ERROR;
            break;
        }
    }
    return error_flag;
}

err_t nfc6_read_mifare_tag_uid ( nfc6_t *ctx, uint8_t *tag_uid, uint8_t *tag_uid_len )
{
    err_t error_flag = NFC6_OK;
    uint8_t data_buf[ NFC6_TAG_UID_RSP_MAX_DATA_LEN ] = { 0 };
    uint8_t resp_buf[ NFC6_TAG_UID_RSP_MAX_DATA_LEN ] = { 0 };
    uint16_t resp_len = 0;
    uint8_t cnt = 0;
    
    do
    {
        // Select protocol
        error_flag = nfc6_select_protocol ( ctx, NFC6_PROTOCOL_ISO_14443A );
        Delay_100ms ( );
    } 
    while ( NFC6_OK != error_flag );
    
    // Send REQA
    data_buf[ 0 ] = NFC6_MIFARE_REQA;
    data_buf[ 1 ] = NFC6_MIFARE_REQA_LEN;
    error_flag |= nfc6_send_command ( ctx, NFC6_CMD_SEND_RECV, data_buf, 2 );
    error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
    
    // Send anti-collision CL1
    data_buf[ 0 ] = NFC6_MIFARE_CL1;
    data_buf[ 1 ] = NFC6_MIFARE_ANTICOLLISION;
    data_buf[ 2 ] = NFC6_MIFARE_ANTICOLLISION_LEN;
    error_flag |= nfc6_send_command ( ctx, NFC6_CMD_SEND_RECV, data_buf, 3 );
    error_flag |= nfc6_read_data ( ctx, resp_buf, sizeof ( resp_buf ), &resp_len );
    if ( ( NFC6_OK == error_flag ) && ( resp_len < NFC6_TAG_UID_RSP_MAX_DATA_LEN ) )
    {
        // Check if a 7-byte UID is detected
        if ( NFC6_MIFARE_CASCADE_TAG == resp_buf[ 0 ] )
        {
            for ( cnt = 0; ( cnt < resp_len - 5 ); cnt++ )
            {
                tag_uid[ cnt ] = resp_buf[ cnt + 1 ];
                data_buf[ cnt + 3 ] = tag_uid[ cnt ];
            }
            // Select CL1
            data_buf[ 0 ] = NFC6_MIFARE_CL1;
            data_buf[ 1 ] = NFC6_MIFARE_SELECT;
            data_buf[ 2 ] = NFC6_MIFARE_CASCADE_TAG;
            data_buf[ cnt + 3 ] = resp_buf[ cnt + 1 ];
            data_buf[ cnt + 4 ] = resp_buf[ cnt + 2 ];
            error_flag |= nfc6_send_command ( ctx, NFC6_CMD_SEND_RECV, data_buf, resp_len );
            error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
            
            // Send anti-collision CL2
            data_buf[ 0 ] = NFC6_MIFARE_CL2;
            data_buf[ 1 ] = NFC6_MIFARE_ANTICOLLISION;
            data_buf[ 2 ] = NFC6_MIFARE_ANTICOLLISION_LEN;
            error_flag |= nfc6_send_command ( ctx, NFC6_CMD_SEND_RECV, data_buf, 3 );
            error_flag |= nfc6_read_data ( ctx, resp_buf, sizeof ( resp_buf ), &resp_len );
            if ( ( NFC6_OK == error_flag ) && ( resp_len < NFC6_TAG_UID_RSP_MAX_DATA_LEN ) )
            {
                for ( ; cnt < resp_len - 1; cnt++ )
                {
                    tag_uid[ cnt ] = resp_buf[ cnt - 3 ];
                    data_buf[ cnt - 1 ] = tag_uid[ cnt ];
                }
                
                // Select CL2
                data_buf[ 0 ] = NFC6_MIFARE_CL2;
                data_buf[ 1 ] = NFC6_MIFARE_SELECT;
                data_buf[ cnt - 1 ] = resp_buf[ cnt - 3 ];
                data_buf[ cnt ] = resp_buf[ cnt - 2 ];
                error_flag |= nfc6_send_command ( ctx, NFC6_CMD_SEND_RECV, data_buf, resp_len );
                error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
            }
        }
        else
        {
            for ( cnt = 0; cnt < resp_len - 4; cnt++ )
            {
                tag_uid[ cnt ] = resp_buf[ cnt ];
                data_buf[ cnt + 2 ] = tag_uid[ cnt ];
            }
            // Select CL1
            data_buf[ 0 ] = NFC6_MIFARE_CL1;
            data_buf[ 1 ] = NFC6_MIFARE_SELECT;
            data_buf[ cnt + 2 ] = resp_buf[ cnt ];
            data_buf[ cnt + 3 ] = resp_buf[ cnt + 1 ];
            error_flag |= nfc6_send_command ( ctx, NFC6_CMD_SEND_RECV, data_buf, resp_len );
            error_flag |= nfc6_read_data ( ctx, NULL, NULL, NULL );
        }
        *tag_uid_len = cnt;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
