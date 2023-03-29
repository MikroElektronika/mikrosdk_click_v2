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
 * @file nfc3.c
 * @brief NFC 3 Click Driver.
 */

#include "nfc3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0xFF

void nfc3_cfg_setup ( nfc3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->aux  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->bsy  = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t nfc3_init ( nfc3_t *ctx, nfc3_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->aux, cfg->aux );
    digital_in_init( &ctx->bsy, cfg->bsy );
    digital_in_init( &ctx->irq, cfg->irq );

    return SPI_MASTER_SUCCESS;
}

err_t nfc3_generic_write ( nfc3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ];
    uint16_t cnt;
    uint16_t timeout = 5000;
    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }
    cnt = 0;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    while ( !nfc3_get_bsy( ctx ) )
    {
        Delay_10us( );
        if ( cnt++ > timeout )
        {
            return NFC3_ERROR;
        }
    }
    cnt = 0;
    spi_master_deselect_device( ctx->chip_select );
    while ( nfc3_get_bsy( ctx ) )
    {
        Delay_10us( );
        if ( cnt++ > timeout )
        {
            return NFC3_ERROR;
        }
    }
    cnt = 0;
    return error_flag;
}

err_t nfc3_generic_transfer ( nfc3_t *ctx, uint8_t *data_in, uint8_t tx_len, uint8_t *data_out, uint8_t rx_len ) 
{
    err_t error_flag;
    uint16_t cnt;
    uint16_t timeout = 5000;
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write( &ctx->spi, data_in, tx_len );
    while ( !nfc3_get_bsy( ctx ) )
    {
        Delay_10us( );
        if ( cnt++ > timeout )
        {
            return NFC3_ERROR;
        }
    }
    cnt = 0;
    spi_master_deselect_device( ctx->chip_select );
    while ( nfc3_get_bsy( ctx ) )
    {
        Delay_10us( );
        if ( cnt++ > timeout )
        {
            return NFC3_ERROR;
        }
    }
    cnt = 0;
    
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_read( &ctx->spi, data_out, rx_len );
    while ( !nfc3_get_bsy( ctx ) )
    {
        Delay_10us( );
        if ( cnt++ > timeout )
        {
            return NFC3_ERROR;
        }
    }
    cnt = 0;
    spi_master_deselect_device( ctx->chip_select );
    while ( nfc3_get_bsy( ctx ) )
    {
        Delay_10us( );
        if ( cnt++ > timeout )
        {
            return NFC3_ERROR;
        }
    }
    cnt = 0;
    return error_flag;
}

err_t nfc3_write_eeprom ( nfc3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag;
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;
    if ( ( uint16_t )( len + reg ) > 0xFF )
    {
        error_flag = NFC3_ERROR;
        return error_flag;
    }
    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }
    error_flag = nfc3_generic_write( ctx, NFC3_CMD_WRITE_EEPROM, tx_buf, len );
    return error_flag;
}

err_t nfc3_read_eeprom ( nfc3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag;
    uint8_t tx_buf[ 3 ];
    if ( ( uint16_t )( len + reg ) > 0xFF )
    {
        error_flag = NFC3_ERROR;
        return error_flag;
    }
    tx_buf[ 0 ] = NFC3_CMD_READ_EEPROM;
    tx_buf[ 1 ] = reg;
    tx_buf[ 2 ] = len;
    error_flag = nfc3_generic_transfer ( ctx, tx_buf, 3, data_out, len );
    return error_flag;
}

err_t nfc3_write_reg ( nfc3_t *ctx, uint8_t reg, uint32_t data_in ) 
{
    err_t error_flag;
    uint8_t tx_buf[ 5 ];
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    tx_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    tx_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    error_flag = nfc3_generic_write( ctx, NFC3_CMD_WRITE_REGISTER, tx_buf, 5 );
    return error_flag;
}

err_t nfc3_write_reg_with_and_mask ( nfc3_t *ctx, uint8_t reg, uint32_t data_in ) 
{
    err_t error_flag;
    uint8_t tx_buf[ 5 ];
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    tx_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    tx_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    error_flag = nfc3_generic_write( ctx, NFC3_CMD_WRITE_REGISTER_AND_MASK, tx_buf, 5 );
    return error_flag;
}

err_t nfc3_write_reg_with_or_mask ( nfc3_t *ctx, uint8_t reg, uint32_t data_in ) 
{
    err_t error_flag;
    uint8_t tx_buf[ 5 ];
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    tx_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    tx_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    error_flag = nfc3_generic_write( ctx, NFC3_CMD_WRITE_REGISTER_OR_MASK, tx_buf, 5 );
    return error_flag;
}

err_t nfc3_read_reg ( nfc3_t *ctx, uint8_t reg, uint32_t *data_out ) 
{
    err_t error_flag;
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 4 ];
    tx_buf[ 0 ] = NFC3_CMD_READ_REGISTER;
    tx_buf[ 1 ] = reg;
    error_flag = nfc3_generic_transfer ( ctx, tx_buf, 2, rx_buf, 4 );
    *data_out = rx_buf[ 3 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 2 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 0 ];
    return error_flag;
}

err_t nfc3_send_data ( nfc3_t *ctx, uint8_t *data_in, uint16_t len, uint8_t valid_bits ) 
{
    err_t error_flag;
    if ( len > 260 ) 
    {
        error_flag = NFC3_ERROR; // send data with more than 260 bytes is not supported
        return error_flag;
    }
    uint8_t tx_buf[ 261 ];
    tx_buf[ 0 ] = valid_bits; // number of valid bits of last byte are transmitted (0 = all bits are transmitted)
    for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
    {
        tx_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    // Idle/StopCom Command
    error_flag = nfc3_write_reg_with_and_mask ( ctx, NFC3_REG_SYSTEM_CONFIG, 0xFFFFFFF8 ); 
    // Transceive Command
    error_flag |= nfc3_write_reg_with_or_mask ( ctx, NFC3_REG_SYSTEM_CONFIG, 0x00000003 ); 
    
    nfc3_transceive_stat_t state = nfc3_get_transceive_state ( ctx );
    if ( NFC3_TS_WAIT_TRANSMIT != state ) 
    {
        error_flag = NFC3_ERROR; // Transceiver not in state WAIT_TRANSMIT
        return error_flag;
    }
    error_flag |= nfc3_generic_write ( ctx, NFC3_CMD_SEND_DATA, tx_buf, len + 1 );
    return error_flag;
}

err_t nfc3_read_data ( nfc3_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag;
    if ( len > 508 ) 
    {
        error_flag = NFC3_ERROR; // Reading more than 508 bytes is not supported
        return error_flag;
    }
    uint8_t cmd[ 2 ] = { NFC3_CMD_READ_DATA, 0x00 };
    error_flag = nfc3_generic_transfer ( ctx, cmd, 2, data_out, len );
    return error_flag;
}

err_t nfc3_load_rf_config ( nfc3_t *ctx, uint8_t tx_conf, uint8_t rx_conf ) 
{
    err_t error_flag;
    uint8_t cmd[ 2 ] = { tx_conf, rx_conf };
    error_flag = nfc3_generic_write( ctx, NFC3_CMD_LOAD_RF_CONFIG, cmd, 2 );
    return error_flag;
}

err_t nfc3_read_firmware_version ( nfc3_t *ctx, uint16_t *data_out ) 
{
    err_t error_flag;
    uint8_t rx_buf[ 2 ];
    error_flag = nfc3_read_eeprom ( ctx, NFC3_EEPROM_FIRMWARE_VERSION, rx_buf, 2 );
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    return error_flag;
}

err_t nfc3_read_product_version ( nfc3_t *ctx, uint16_t *data_out ) 
{
    err_t error_flag;
    uint8_t rx_buf[ 2 ];
    error_flag = nfc3_read_eeprom ( ctx, NFC3_EEPROM_PRODUCT_VERSION, rx_buf, 2 );
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    return error_flag;
}

err_t nfc3_read_eeprom_version ( nfc3_t *ctx, uint16_t *data_out ) 
{
    err_t error_flag;
    uint8_t rx_buf[ 2 ];
    error_flag = nfc3_read_eeprom ( ctx, NFC3_EEPROM_EEPROM_VERSION, rx_buf, 2 );
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    return error_flag;
}

void nfc3_reset ( nfc3_t *ctx ) 
{
    uint32_t irq_status;
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    do
    {
        nfc3_read_reg ( ctx, NFC3_REG_IRQ_STATUS, &irq_status );
    }
    while ( ( irq_status & NFC3_IDLE_IRQ_STAT ) == 0 ); // wait for system to start up
    nfc3_write_reg ( ctx, NFC3_REG_IRQ_CLEAR, 0xFFFFFFFF ); // Clear all flags
}

void nfc3_set_rst ( nfc3_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rst, state );
}

uint8_t nfc3_get_irq ( nfc3_t *ctx ) 
{
    return digital_in_read( &ctx->irq );
}

uint8_t nfc3_get_bsy ( nfc3_t *ctx ) 
{
    return digital_in_read( &ctx->bsy );
}

uint8_t nfc3_get_aux ( nfc3_t *ctx ) 
{
    return digital_in_read( &ctx->aux );
}

nfc3_transceive_stat_t nfc3_get_transceive_state ( nfc3_t *ctx ) 
{
    uint32_t rf_status;
    nfc3_read_reg ( ctx, NFC3_REG_RF_STATUS, &rf_status );
    if ( !rf_status ) 
    {
        return NFC3_TS_IDLE;
    }
    switch ( ( rf_status >> 24 ) & 0x07 )
    {
        case 0: return NFC3_TS_IDLE;
        case 1: return NFC3_TS_WAIT_TRANSMIT;
        case 2: return NFC3_TS_TRANSMITTING;
        case 3: return NFC3_TS_WAIT_RECEIVE;
        case 4: return NFC3_TS_WAIT_FOR_DATA;
        case 5: return NFC3_TS_RECEIVING;
        case 6: return NFC3_TS_LOOPBACK;
        case 7: return NFC3_TS_RESERVED;
    }
}

uint16_t nfc3_rx_num_bytes_received ( nfc3_t *ctx ) 
{
    uint32_t rx_status;
    uint16_t len = 0;
    nfc3_read_reg ( ctx, NFC3_REG_RX_STATUS, &rx_status );
    // Lower 9 bits has length
    len = ( uint16_t )( rx_status & 0x01FF );
    return len;
}

uint8_t nfc3_activate_type_a ( nfc3_t *ctx, uint8_t *data_out, uint8_t kind ) 
{
    uint8_t cmd[ 7 ] = { 0 };
    uint8_t uid_length = 0;
    nfc3_reset ( ctx );
    
    // LOAD_RF_CONFIG, ISO 14443-A, 106 kbps
    if ( nfc3_load_rf_config( ctx, 0x00, 0x80 ) == NFC3_ERROR )
    {
        return 0;
    }

    // RF field ON
    if ( nfc3_generic_write ( ctx, NFC3_CMD_RF_ON, cmd, 1 ) == NFC3_ERROR )
    {
        return 0;
    }
    Delay_100ms( );
    
    // OFF Crypto
    if ( nfc3_write_reg_with_and_mask ( ctx, NFC3_REG_SYSTEM_CONFIG, 0xFFFFFFBF ) == NFC3_ERROR )
    {
        return 0;
    }
    
    // Clear RX and TX CRC
    if ( nfc3_clear_rx_tx_crc ( ctx ) == NFC3_ERROR )
    {
        return 0;
    }
    
    // Send REQA/WUPA, 7 bits in last byte
    cmd[ 0 ] = ( kind == 0 ) ? 0x26 : 0x52;
    if ( nfc3_send_data ( ctx, cmd, 1, 0x07 ) == NFC3_ERROR )
    {
        return 0;
    }
    Delay_10ms( );
    
    // READ 2 bytes ATQA into data_out
    if ( nfc3_read_data ( ctx, data_out, 2 ) == NFC3_ERROR )
    {
        return 0;
    }
    
    // Send Anti collision 1, 8 bits in last byte
    cmd[ 0 ] = 0x93;
    cmd[ 1 ] = 0x20;
    if ( nfc3_send_data ( ctx, cmd, 2, 0x00 ) == NFC3_ERROR )
    {
        return 0;
    }
    Delay_10ms( );
    
    // Read 5 bytes, we will store at offset 2 for later usage
    if ( nfc3_read_data ( ctx, &cmd[ 2 ], 5 ) == NFC3_ERROR )
    {
        return 0;
    }
    
    // Enable RX and TX CRC calculation
    if ( nfc3_enable_rx_tx_crc ( ctx ) == NFC3_ERROR )
    {
        return 0;
    }
    
    // Send Select anti collision 1, the remaining bytes are already in offset 2 onwards
    cmd[ 0 ] = 0x93;
    cmd[ 1 ] = 0x70;
    if ( nfc3_send_data ( ctx, cmd, 7, 0x00 ) == NFC3_ERROR )
    {
        return 0;
    }
    Delay_10ms( );
    
    // Read 1 byte SAK into data_out[2]
    if ( nfc3_read_data ( ctx, &data_out[ 2 ], 1 ) == NFC3_ERROR )
    {
        return 0;
    }
    
    // Check if the tag is 4 Byte UID or 7 byte UID and requires anti collision 2
    // If Bit 3 is 0 it is 4 Byte UID
    if ( ( data_out[ 2 ] & 0x04 ) == 0 ) 
    {
        // Take first 4 bytes of anti collision as UID store at offset 3 onwards. job done
        for ( uint8_t cnt = 0; cnt < 4; cnt++ ) 
        {
            data_out[ cnt + 3 ] = cmd[ cnt + 2 ];
        }
        uid_length = 4;
    }
    else 
    {
        // Take First 3 bytes of UID, Ignore first byte 88(CT)
        if ( cmd[ 2 ] != 0x88 )
        {
            return 0;
        }
        
        for ( uint8_t cnt = 0; cnt < 3; cnt++ ) 
        {
            data_out[ cnt + 3 ] = cmd[ cnt + 3 ];
        }
        
        // Clear RX and TX CRC
        if ( nfc3_clear_rx_tx_crc ( ctx ) == NFC3_ERROR )
        {
            return 0;
        }
        
        // Do anti collision 2
        cmd[ 0 ] = 0x95;
        cmd[ 1 ] = 0x20;
        if ( nfc3_send_data ( ctx, cmd, 2, 0x00 ) == NFC3_ERROR )
        {
            return 0;
        }
        Delay_10ms( );
        
        // Read 5 bytes. we will store at offset 2 for later use
        if ( nfc3_read_data ( ctx, &cmd[ 2 ], 5 ) == NFC3_ERROR )
        {
            return 0;
        }
        
        // first 4 bytes belongs to last 4 UID bytes, we keep it.
        for ( uint8_t cnt = 0; cnt < 4; cnt++ ) 
        {
            data_out[ cnt + 6 ] = cmd[ cnt + 2 ];
        }
        
        // Enable RX and TX CRC calculation
        if ( nfc3_enable_rx_tx_crc ( ctx ) == NFC3_ERROR )
        {
            return 0;
        }
        
        // Send Select anti collision 2 
        cmd[ 0 ] = 0x95;
        cmd[ 1 ] = 0x70;
        if ( nfc3_send_data ( ctx, cmd, 7, 0x00 ) == NFC3_ERROR )
        {
            return 0;
        }
        Delay_10ms( );
        
        // Read 1 byte SAK into data_out[2]
        if ( nfc3_read_data ( ctx, &data_out[ 2 ], 1 ) == NFC3_ERROR )
        {
            return 0;
        }
        uid_length = 7;
    }
    return uid_length;
}

err_t nfc3_mifare_block_read( nfc3_t *ctx, uint8_t *data_out, uint8_t blockno ) 
{
    uint16_t len;
    uint8_t cmd[ 2 ];
    // Send mifare command 30, blockno
    cmd[ 0 ] = 0x30;
    cmd[ 1 ] = blockno;
    
    nfc3_send_data ( ctx, cmd, 2, 0x00 );
    Delay_10ms( );
    
    // Check if we have received any data from the tag
    len = nfc3_rx_num_bytes_received( ctx );
    
    if ( len == 16 ) 
    {
        // READ 16 bytes into data_out
        nfc3_read_data ( ctx, data_out, 16 );
        return NFC3_OK;
    }
    return NFC3_ERROR;
}

uint8_t nfc3_mifare_block_write_16( nfc3_t *ctx, uint8_t *data_in, uint8_t blockno ) 
{
    uint8_t cmd[ 2 ];
    // Clear RX CRC
    nfc3_write_reg_with_and_mask ( ctx, NFC3_REG_CRC_RX_CONFIG, 0xFFFFFFFE );

    // Mifare write part 1
    cmd[ 0 ] = 0xA0;
    cmd[ 1 ] = blockno;
    nfc3_send_data ( ctx, cmd, 2, 0x00 );
    Delay_10ms( );
    nfc3_read_data ( ctx, cmd, 1 );

    // Mifare write part 2
    nfc3_send_data ( ctx, data_in, 16, 0x00 );
    Delay_10ms( );

    // Read ACK/NAK
    nfc3_read_data ( ctx, cmd, 1 );

    // Enable RX CRC calculation
    nfc3_write_reg_with_or_mask ( ctx, NFC3_REG_CRC_RX_CONFIG, 0x01 );
    
    return cmd[ 0 ];
}

err_t nfc3_mifare_halt( nfc3_t *ctx ) 
{
    uint8_t cmd[ 2 ];
    
    // MIFARE Halt
    cmd[ 0 ] = 0x50;
    cmd[ 1 ] = 0x00;
    
    return nfc3_send_data ( ctx, cmd, 2, 0x00 );
}

uint8_t nfc3_read_card_uid ( nfc3_t *ctx, uint8_t *data_out ) 
{  
    uint8_t response[ 10 ];
    uint8_t uid_length;
    
    for ( uint8_t cnt = 0; cnt < 10; cnt++ ) 
    {
        response[ cnt ] = 0;
    }
    
    uid_length = nfc3_activate_type_a( ctx, response, 1 );
    
    if ( ( response[ 0 ] == 0xFF ) && ( response[ 1 ] == 0xFF ) )
    {
        return 0;
    }
    
    // check for valid uid
    if ( ( response[ 3 ] == 0x00 ) && ( response[ 4 ] == 0x00 ) && ( response[ 5 ] == 0x00 ) && ( response[ 6 ] == 0x00 ) )
    {
        return 0;
    }    
    if ( ( response[ 3 ] == 0xFF ) && ( response[ 4 ] == 0xFF ) && ( response[ 5 ] == 0xFF ) && ( response[ 6 ] == 0xFF ) )
    {
        return 0;
    }
    
    for ( uint8_t cnt = 0; cnt < 7; cnt++ ) 
    {
        data_out[ cnt ] = response[ cnt + 3 ];
    }
    
    nfc3_mifare_halt( ctx );
    return uid_length;  
}

err_t nfc3_clear_rx_tx_crc ( nfc3_t *ctx ) 
{
    // Clear RX CRC
    if ( nfc3_write_reg_with_and_mask ( ctx, NFC3_REG_CRC_RX_CONFIG, 0xFFFFFFFE ) == NFC3_ERROR )
    {
        return NFC3_ERROR;
    }
    // Clear TX CRC
    if ( nfc3_write_reg_with_and_mask ( ctx, NFC3_REG_CRC_TX_CONFIG, 0xFFFFFFFE ) == NFC3_ERROR )
    {
        return NFC3_ERROR;
    }
    return NFC3_OK;
}

err_t nfc3_enable_rx_tx_crc ( nfc3_t *ctx ) 
{
    // Enable RX CRC calculation
    if ( nfc3_write_reg_with_or_mask ( ctx, NFC3_REG_CRC_RX_CONFIG, 0x01 ) == NFC3_ERROR )
    {
        return NFC3_ERROR;
    }
    
    // Enable TX CRC calculation
    if ( nfc3_write_reg_with_or_mask ( ctx, NFC3_REG_CRC_TX_CONFIG, 0x01 ) == NFC3_ERROR )
    {
        return NFC3_ERROR;
    }
    return NFC3_OK;
}


// ------------------------------------------------------------------------- END
