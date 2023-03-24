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
 * @file smartmic.c
 * @brief Smart Mic Click Driver.
 */

#include "smartmic.h"

#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    #include "resources/firmware_uart.h"
#elif ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_I2C )
    #include "resources/firmware_i2c.h"
#else
    #include "resources/firmware_spi.h"
#endif

#if ( SMARTMIC_SYS_CFG_SELECTOR == SMARTMIC_SYS_CFG_6SEC_TO )
    #include "resources/system_config_6sec_to.h"
#elif ( SMARTMIC_SYS_CFG_SELECTOR == SMARTMIC_SYS_CFG_6SEC_TO_UTK )
    #include "resources/system_config_6sec_to_utk.h"
#else
    #include "resources/system_config_6sec_to_vid.h"
#endif
#include "resources/keyword_hello_voice_q2.h"
#include "resources/keyword_switch_the_light.h"
#include "resources/keyword_next_song.h"
#include "resources/keyword_baidu_yixia.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void smartmic_cfg_setup ( smartmic_cfg_t *cfg )
{
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
    
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
#elif ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_I2C )
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTMIC_DEVICE_ADDRESS_0;
#else
    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
#endif
}

err_t smartmic_init ( smartmic_t *ctx, smartmic_cfg_t *cfg )
{
    digital_out_init( &ctx->en, cfg->en );
    smartmic_disable_device ( ctx );
    Delay_100ms ( );
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
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

    smartmic_enable_device ( ctx );
    Delay_100ms ( );
    digital_in_init( &ctx->irq, cfg->miso );
    uint8_t sync_byte = SMARTMIC_SYNC_BYTE;
    uint8_t sync_resp;
    uint8_t dummy_write[ 2 ] = { 0, 0 };
    
    // In order for the chip to recognize the baud rate
    smartmic_write_data ( ctx, dummy_write, 2 );
    Delay_1ms ( );
    smartmic_write_data ( ctx, &sync_byte, 1 );
    while ( smartmic_read_data ( ctx, &sync_resp, 1 ) <= 0 );
    if ( sync_resp != sync_byte )
    {
        return SMARTMIC_ERROR;
    }
#elif ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_I2C )
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    digital_out_t p2_pin, p3_pin;
    digital_out_init ( &p2_pin, cfg->sck );
    digital_out_init ( &p3_pin, cfg->miso );
    switch ( cfg->i2c_address )
    {
        case SMARTMIC_DEVICE_ADDRESS_1:
        {
            digital_out_high ( &p2_pin );
            digital_out_low ( &p3_pin );
            break;
        }
        case SMARTMIC_DEVICE_ADDRESS_2:
        {
            digital_out_low ( &p2_pin );
            digital_out_high ( &p3_pin );
            break;
        }
        case SMARTMIC_DEVICE_ADDRESS_3:
        {
            digital_out_high ( &p2_pin );
            digital_out_high ( &p3_pin );
            break;
        }
        default:
        {
            digital_out_low ( &p2_pin );
            digital_out_low ( &p3_pin );
            break;
        }
    }
    Delay_100ms ( );
    smartmic_enable_device ( ctx );
    Delay_100ms ( );
    digital_in_init( &ctx->irq, cfg->miso );
    uint8_t sync_byte = SMARTMIC_SYNC_BYTE;
    uint8_t sync_resp;
    if ( SMARTMIC_ERROR == smartmic_write_data ( ctx, &sync_byte, 1 ) )
    {
        return SMARTMIC_ERROR;
    }
    Delay_1ms ( );
    if ( SMARTMIC_ERROR == smartmic_read_data ( ctx, &sync_resp, 1 ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( sync_resp != sync_byte )
    {
        return SMARTMIC_ERROR;
    }
#else
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
    
    smartmic_enable_device ( ctx );
    Delay_100ms ( );
    digital_in_init( &ctx->irq, cfg->int_pin );
    uint8_t sync_bytes[ 4 ] = { SMARTMIC_SYNC_BYTE, SMARTMIC_SYNC_BYTE, SMARTMIC_SYNC_BYTE, SMARTMIC_SYNC_BYTE };
    uint8_t sync_resp[ 4 ];
    if ( SMARTMIC_ERROR == smartmic_write_data ( ctx, sync_bytes, 4 ) )
    {
        return SMARTMIC_ERROR;
    }
    Delay_1ms ( );
    if ( SMARTMIC_ERROR == smartmic_read_data ( ctx, sync_resp, 4 ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( memcmp ( sync_bytes, sync_resp, 4 ) )
    {
        return SMARTMIC_ERROR;
    }
#endif
    Delay_10ms ( );
    return SMARTMIC_OK;
}

err_t smartmic_default_cfg ( smartmic_t *ctx )
{
    if ( SMARTMIC_OK != smartmic_download_config ( ctx ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_download_firmware ( ctx ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_download_keyword ( ctx, ( uint16_t * ) keyword_hello_voice_q2, 
                                                         sizeof ( keyword_hello_voice_q2 ) ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_download_keyword ( ctx, ( uint16_t * ) keyword_switch_the_light, 
                                                         sizeof ( keyword_switch_the_light ) ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_download_keyword ( ctx, ( uint16_t * ) keyword_next_song, 
                                                         sizeof ( keyword_next_song ) ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_download_keyword ( ctx, ( uint16_t * ) keyword_baidu_yixia, 
                                                         sizeof ( keyword_baidu_yixia ) ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_voice_make ( ctx ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_send_command ( ctx, SMARTMIC_CMD_SET_POWER_STATE, SMARTMIC_LOW_POWER_MODE_RT6, NULL ) )
    {
        return SMARTMIC_ERROR;
    }
    return SMARTMIC_OK;
}

err_t smartmic_write_data ( smartmic_t *ctx, uint8_t *data_in, uint16_t len )
{
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    uart_clear ( &ctx->uart );
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        uart_write( &ctx->uart, &data_in[ cnt ], 1 );
        Delay_80us ( );
    }
    return SMARTMIC_OK;
#elif ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_I2C )
    return i2c_master_write( &ctx->i2c, data_in, len );
#else
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
#endif
}

err_t smartmic_read_data ( smartmic_t *ctx, uint8_t *data_out, uint16_t len )
{
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    return uart_read( &ctx->uart, data_out, len );
#elif ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_I2C )
    return i2c_master_read( &ctx->i2c, data_out, len );
#else
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
#endif
}

err_t smartmic_send_command ( smartmic_t *ctx, uint16_t cmd, uint16_t data_in, uint16_t *response )
{
    err_t error_flag = SMARTMIC_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    smartmic_write_data ( ctx, data_buf, 4 );
#else
    if ( SMARTMIC_ERROR == smartmic_write_data ( ctx, data_buf, 4 ) )
    {
        return SMARTMIC_ERROR;
    }
#endif
    if ( SMARTMIC_NO_RESPONSE_BIT != ( cmd & SMARTMIC_NO_RESPONSE_BIT ) )
    {
        memset ( data_buf, 0, sizeof ( data_buf ) );
        Delay_5ms ( );
    #if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
        uint8_t cnt = 0;
        while ( cnt < 4 )
        {
            if ( smartmic_read_data ( ctx, &data_buf[ cnt ], 1 ) > 0 )
            {
                cnt++;
            }
        }
    #else
        error_flag = smartmic_read_data ( ctx, data_buf, 4 );
    #endif
        *response = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        if ( ( SMARTMIC_OK == error_flag ) && ( *response == cmd ) )
        {
            *response = ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
        }
        else
        {
            error_flag = SMARTMIC_ERROR;
        }
    }
    return error_flag;
}

err_t smartmic_download_bin ( smartmic_t *ctx, uint8_t *data_in, uint32_t len )
{
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    uint8_t write_data = SMARTMIC_BOOT_BYTE;
    uint8_t read_data;
    smartmic_write_data ( ctx, &write_data, 1 );
    while ( smartmic_read_data ( ctx, &read_data, 1 ) <= 0 );
    if ( read_data != write_data )
    {
        return SMARTMIC_ERROR;
    }
#elif ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_I2C )
    uint8_t write_data = SMARTMIC_BOOT_BYTE;
    uint8_t read_data;
    if ( SMARTMIC_ERROR == smartmic_write_data ( ctx, &write_data, 1 ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( ( SMARTMIC_ERROR == smartmic_read_data ( ctx, &read_data, 1 ) ) ||
         ( read_data != write_data ) )
    {
        return SMARTMIC_ERROR;
    }
#else
    uint8_t write_data[ 4 ] = { DUMMY, DUMMY, DUMMY, SMARTMIC_BOOT_BYTE };
    uint8_t read_data[ 4 ];
    if ( SMARTMIC_ERROR == smartmic_write_data ( ctx, write_data, 4 ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( ( SMARTMIC_ERROR == smartmic_read_data ( ctx, read_data, 4 ) ) || 
         ( read_data[ 3 ] != write_data[ 3 ] ) )
    {
        return SMARTMIC_ERROR;
    }
#endif
    uint32_t cnt = 0;
    while ( cnt < len )
    {
        if ( ( len - cnt ) >= 256 ) 
        {
            if ( SMARTMIC_ERROR == smartmic_write_data ( ctx, &data_in[ cnt ], 256 ) )
            {
                return SMARTMIC_ERROR;
            }
        }
        else
        {
            if ( SMARTMIC_ERROR == smartmic_write_data ( ctx, &data_in[ cnt ], ( len - cnt ) ) )
            {
                return SMARTMIC_ERROR;
            }
        }
        cnt += 256;
    }
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    Delay_1ms( );
    if ( smartmic_read_data ( ctx, &read_data, 1 ) > 0 )
    {
        return read_data;
    }
#endif
    return SMARTMIC_OK;
}

err_t smartmic_download_config ( smartmic_t *ctx )
{
    return smartmic_download_bin ( ctx, ( uint8_t * ) smartmic_system_config, sizeof ( smartmic_system_config ) );
}

err_t smartmic_download_firmware ( smartmic_t *ctx )
{
    err_t error_flag = smartmic_download_bin ( ctx, ( uint8_t * ) smartmic_firmware, sizeof ( smartmic_firmware ) );
    Delay_100ms( );
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_SPI )
    uint8_t dummy_read[ 4 ];
    error_flag |= smartmic_read_data ( ctx, dummy_read, 4 );
#endif
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    if ( SMARTMIC_FIRMWARE_OK == error_flag )
    {
        uint16_t sync_resp;
        if ( SMARTMIC_OK == smartmic_send_command ( ctx, SMARTMIC_CMD_SYNC, DUMMY, &sync_resp ) )
        {
            return sync_resp;
        }
    }
#else
    if ( SMARTMIC_OK == error_flag )
    {
        uint16_t sync_resp;
        if ( SMARTMIC_OK == smartmic_send_command ( ctx, SMARTMIC_CMD_SYNC, DUMMY, &sync_resp ) )
        {
            uint16_t int_resp;
            if ( SMARTMIC_OK == smartmic_send_command ( ctx, SMARTMIC_CMD_SET_EVENT_RESP, 
                                                        SMARTMIC_IA611_INT_RISING_EDGE, &int_resp ) )
            {
                if ( SMARTMIC_IA611_INT_RISING_EDGE == int_resp )
                {
                    return sync_resp;
                }
            }
        }
    }
#endif
    return SMARTMIC_ERROR;
}

err_t smartmic_download_keyword ( smartmic_t *ctx, uint16_t *data_in, uint16_t len )
{
    static uint8_t download_num = 0;
    static uint8_t ref_model = 0;
    // Begin Creating Header info for STX MODE. Generate the length
    uint16_t spacket_g = ( uint16_t ) ( ( len / SMARTMIC_WDB_SIZE_NO_HEADER ) );
    if ( len % SMARTMIC_WDB_SIZE_NO_HEADER )
    {
        spacket_g++;
    }
    // Send Write Data Block command
    uint16_t resp = 0;
    err_t error_flag = smartmic_send_command ( ctx, SMARTMIC_CMD_WRITE_DATA_BLOCK | SMARTMIC_NO_RESPONSE_BIT, len, &resp );
    Delay_500us( );
    
    uint16_t seq_data = 0;
#if ( SMARTMIC_SYS_CFG_SELECTOR == SMARTMIC_SYS_CFG_6SEC_TO_VID ) 
    // No need to add the keyword ID to the Voice ID reference model file.
    if ( ( 1 == download_num ) && ( 0 == ref_model ) )
    {
        seq_data = data_in[ 1 ];
    }
    else
#endif
    {
        // Set the Keyword sequence number in header bit 4-7.
        seq_data = data_in[ 1 ] + ( download_num << 4 ); 
    }
    // Send the OEM Model
    uint16_t block_cnt = 0;
    for ( uint16_t data_idx = 2; data_idx < ( len / 2 ); )
    {
        Delay_500us( );
        // Send Block Header including updated block sequence number
    #if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
        smartmic_write_data ( ctx, ( uint8_t * ) &data_in[ 0 ], 2 );
        smartmic_write_data ( ctx, ( uint8_t * ) &seq_data, 2 );
    #else
        error_flag |= smartmic_write_data ( ctx, ( uint8_t * ) &data_in[ 0 ], 2 );
        error_flag |= smartmic_write_data ( ctx, ( uint8_t * ) &seq_data, 2 );
    #endif

        // Send 512 Bytes block to IA61x
        for ( uint16_t block_idx = 2; block_idx < ( SMARTMIC_WDB_SIZE / 2 ); block_idx++ )
        {
            if ( data_idx < ( len / 2 ) )
            {
            #if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
                smartmic_write_data ( ctx, ( uint8_t * ) &data_in[ data_idx++ ], 2 );
            #else
                error_flag |= smartmic_write_data ( ctx, ( uint8_t * ) &data_in[ data_idx++ ], 2 );
            #endif
            }
            else 
            {
                // Send extra 0x0000 to Pad the data if it's not 512 byte aligned
                uint8_t dummy_write[ 2 ] = { 0, 0 };
            #if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
                smartmic_write_data ( ctx, dummy_write, 2 );
            #else
                error_flag |= smartmic_write_data ( ctx, dummy_write, 2 );
            #endif
                data_idx++;
            }
        }
        // Increment block counter and updated the Sequence header
        block_cnt++;
        // For last block set Sequence number to 0xFF
        if ( block_cnt == spacket_g ) 
        {
            block_cnt = 0xFF;
        }
        seq_data = seq_data | ( block_cnt << 8 );
    }
    
    // Wait for sometime for firmware to respond.
    Delay_5ms ( );
    uint8_t data_buf[ 4 ];
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    uint8_t cnt = 0;
    while ( cnt < 4 )
    {
        if ( smartmic_read_data ( ctx, &data_buf[ cnt ], 1 ) > 0 )
        {
            cnt++;
        }
    }
#else
    error_flag |= smartmic_read_data ( ctx, data_buf, 4 );
#endif
#if ( SMARTMIC_SYS_CFG_SELECTOR == SMARTMIC_SYS_CFG_6SEC_TO_VID ) 
    if ( ( 1 == download_num ) && ( 0 == ref_model ) )
    {
        ref_model = 1;
    }
    else
#endif
    {
        // Increment OEM keyword download sequence number for next keyword
        download_num++;
    }
    if ( ( SMARTMIC_OK == error_flag ) && 
         ( SMARTMIC_CMD_WRITE_DATA_BLOCK == ( ( ( uint8_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) ) &&
         ( DUMMY == data_buf[ 2 ] ) && 
         ( DUMMY == data_buf[ 3 ] ) )
    {
        return SMARTMIC_OK;
    }
    return SMARTMIC_ERROR;
}

err_t smartmic_voice_make ( smartmic_t *ctx )
{
    err_t error_flag = SMARTMIC_OK;
    uint16_t resp = 0;
    // Send Sync command first to make sure that IA61x is awake. Ignore the response.
    smartmic_send_command ( ctx, SMARTMIC_CMD_SYNC, DUMMY, &resp );
    Delay_1ms ( );
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_STOP_ROUTE, DUMMY, &resp );
    if ( DUMMY != resp )
    {
        error_flag--;
    }
    Delay_1ms ( );
    // Set Digital gain to 20db
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_DIG_GAIN, SMARTMIC_DIGITAL_GAIN_20, &resp );
    if ( SMARTMIC_DIGITAL_GAIN_20 != resp )
    {
        error_flag--;
    }
    Delay_1ms ( );
    // Set Sample Rate to 16K
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_SAMPLE_RATE, SMARTMIC_SAMPLE_RATE_16K, &resp );
    if ( SMARTMIC_SAMPLE_RATE_16K != resp )
    {
        error_flag--;
    }
    Delay_1ms ( );
    // Set Frame Size to 16 mS
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_FRAME_SIZE, SMARTMIC_FRAME_SIZE_16MS, &resp );
    if ( SMARTMIC_FRAME_SIZE_16MS != resp )
    {
        error_flag--;
    }
    Delay_1ms ( );
    // Select Route 6
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SELECT_ROUTE, SMARTMIC_ROUTE_6, &resp );
    if ( SMARTMIC_ROUTE_6 != resp )
    {
        error_flag--;
    }
    Delay_1ms ( );
    // Set Algorithm Parameter: Sensitivity to 5 for OEM
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_ALGO_PARAM_ID, SMARTMIC_VQ_CMD_OEM_SENSITIVITY, &resp );
    if ( SMARTMIC_VQ_CMD_OEM_SENSITIVITY == resp )
    {
        error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_ALGO_PARAM, SMARTMIC_OEM_SENSITIVITY_5, &resp );
        if ( SMARTMIC_OEM_SENSITIVITY_5 != resp )
        {
            error_flag--;
        }
    }
    else
    {
        error_flag--;
    }
    Delay_1ms ( );
    // Set Algorithm Parameter: Sensitivity to 0 for UTK
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_ALGO_PARAM_ID, SMARTMIC_VQ_CMD_UTK_SENSITIVITY, &resp );
    if ( SMARTMIC_VQ_CMD_UTK_SENSITIVITY == resp )
    {
        error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_ALGO_PARAM, SMARTMIC_UTK_SENSITIVITY_0, &resp );
        if ( SMARTMIC_UTK_SENSITIVITY_0 != resp )
        {
            error_flag--;
        }
    }
    else
    {
        error_flag--;
    }
    Delay_1ms ( );
    // Set Algorithm Parameter: Sensitivity to 2 for VID
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_ALGO_PARAM_ID, SMARTMIC_VQ_CMD_VID_SENSITIVITY, &resp );
    if ( SMARTMIC_VQ_CMD_VID_SENSITIVITY == resp )
    {
        error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_ALGO_PARAM, SMARTMIC_VID_SENSITIVITY_2, &resp );
        if ( SMARTMIC_VID_SENSITIVITY_2 != resp )
        {
            error_flag--;
        }
    }
    else
    {
        error_flag--;
    }
    Delay_1ms ( );
    // Set Algorithm Parameter: VS Processing Mode to Keyword detection
    error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_ALGO_PARAM_ID, SMARTMIC_VQ_CMD_VS_PROCESSING_MODE, &resp );
    if ( SMARTMIC_VQ_CMD_VS_PROCESSING_MODE == resp )
    {
        error_flag -= smartmic_send_command ( ctx, SMARTMIC_CMD_SET_ALGO_PARAM, SMARTMIC_VS_PROCESSING_MODE_KW, &resp );
        if ( SMARTMIC_VS_PROCESSING_MODE_KW != resp )
        {
            error_flag--;
        }
    }
    else
    {
        error_flag--;
    }
    Delay_1ms ( );
    return error_flag;
}

err_t smartmic_wait_keyword ( smartmic_t *ctx )
{
#if ( SMARTMIC_DRIVER_SELECTOR == SMARTMIC_DRIVER_UART )
    uint8_t event_header;
    for ( ; ; )
    {
        if ( smartmic_read_data ( ctx, &event_header, 1 ) > 0 )
        {
            if ( SMARTMIC_UART_EVENT_HEADER == event_header )
            {
                break;
            }
        }
    }
#else
    while ( smartmic_get_irq_pin ( ctx ) );
#endif
    uint16_t resp = 0;
    // Send Get Event Command to IA61x to check which event has happened!
    if ( SMARTMIC_OK != smartmic_send_command ( ctx, SMARTMIC_CMD_GET_EVENT, DUMMY, &resp ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_voice_make ( ctx ) )
    {
        return SMARTMIC_ERROR;
    }
    if ( SMARTMIC_OK != smartmic_send_command ( ctx, SMARTMIC_CMD_SET_POWER_STATE, SMARTMIC_LOW_POWER_MODE_RT6, NULL ) )
    {
        return SMARTMIC_ERROR;
    }
    return ( err_t )( resp & 0xFF );
}

void smartmic_enable_device ( smartmic_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void smartmic_disable_device ( smartmic_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t smartmic_get_irq_pin ( smartmic_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

// ------------------------------------------------------------------------ END
