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
 * @file sram3.c
 * @brief SRAM 3 Click Driver.
 */

#include "sram3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief SRAM 3 check protect range function.
 * @details Function for check protect range.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[out] protect_range : Part of memory to be protected.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note None.
 */
static uint8_t check_protect_range( sram3_t *ctx, uint8_t protect_range );

/**
 * @brief SRAM 3 writing data function.
 * @details Function for writing data memory.
 * @param[in] ctx : Click context object.
 * See #sram3_t object definition for detailed explanation.
 * @param[in] buf : Buffer to be written to.
 * @param[in] size : Size of data.
 * @return crc : Result data.
 *
 * @note None.
 */
static uint16_t crc16_calc( sram3_t *ctx, uint8_t *buf, uint8_t size );

void sram3_cfg_setup ( sram3_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->hold = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t sram3_init ( sram3_t *ctx, sram3_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {        
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {        
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {        
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->hold, cfg->hold );
    return SPI_MASTER_SUCCESS;
}

err_t sram3_generic_write ( sram3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t sram3_generic_read ( sram3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void sram3_enable_write( sram3_t *ctx ) {
    uint8_t enwr_opcode = SRAM3_OPCODE_WREN;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &enwr_opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void sram3_disable_write( sram3_t *ctx ) {   
    uint8_t diwr_opcode = SRAM3_OPCODE_WRDI;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &diwr_opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t sram3_read_status( sram3_t *ctx ) {    
    uint8_t rdsr_opcode = SRAM3_OPCODE_RDSR;
    uint8_t status;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &rdsr_opcode, 1, &status, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return status;
}

void sram3_write_status( sram3_t *ctx, uint8_t status ) {
    uint8_t wrsr_buf[ 2 ];

    wrsr_buf[ 0 ] = SRAM3_OPCODE_WRSR;
    wrsr_buf[ 1 ] = status;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &wrsr_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

void sram3_protect_memory( sram3_t *ctx, uint8_t protect_range ) {
    uint8_t old_status;

    if ( check_protect_range( ctx, protect_range ) == 0 ) {        
        return;
    }

    old_status = sram3_read_status( ctx );
    old_status &= 0x73;
    protect_range |= old_status;
    sram3_write_status( ctx, protect_range );
}

void sram3_enable_pdis( sram3_t *ctx ) {    
    uint8_t old_status = sram3_read_status( ctx );
    
    old_status |= 0x40;
    sram3_write_status( ctx, old_status );
}

void sram3_disable_pdis( sram3_t *ctx ) {   
    uint8_t old_status = sram3_read_status( ctx );
    
    old_status &= 0x1F;
    sram3_write_status( ctx, old_status );
}

void sram3_recall( sram3_t *ctx ) {
    uint8_t rec_opcode = SRAM3_OPCODE_RECALL;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &rec_opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void sram3_store( sram3_t *ctx ) {    
    uint8_t str_opcode = SRAM3_OPCODE_STORE;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &str_opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void sram3_hibernate_start( sram3_t *ctx ) {    
    uint8_t hib_opcode = SRAM3_OPCODE_HIBERNATE;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &hib_opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void sram3_hibernate_stop( sram3_t *ctx ) {        
    spi_master_select_device( ctx->chip_select );
    Delay_100ms( ); 
    Delay_100ms( );
    spi_master_deselect_device( ctx->chip_select );
}

void sram3_hold( sram3_t *ctx ) {    
    digital_out_low( &ctx->hold );
}

void sram3_release_hold( sram3_t *ctx ) {    
    digital_out_high( &ctx->hold );
}

void sram3_read_serial( sram3_t *ctx, uint8_t *buf ) {
    uint8_t rdsnr_opcode = SRAM3_OPCODE_RDSNR;
    uint8_t len = SRAM3_SERIAL_LEN;
    
    spi_master_select_device( ctx->chip_select );    
    spi_master_write_then_read( &ctx->spi, &rdsnr_opcode, 1, buf, len );
    spi_master_deselect_device( ctx->chip_select );
}

void sram3_write_serial( sram3_t *ctx, uint8_t *buf ) {
    uint8_t wrsnr_buf[ 17 ] = { 0 }, cnt; 
    
    for( cnt = 0; cnt < SRAM3_SERIAL_LEN; cnt++ ) {
        wrsnr_buf[ cnt + 1 ] = buf[ cnt ];
    }

    wrsnr_buf[ 0 ] = SRAM3_OPCODE_WRSNR;
    uint8_t len = SRAM3_SERIAL_LEN;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &wrsnr_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void sram3_read( sram3_t *ctx, uint32_t mem_adr, uint8_t *read_buf, uint8_t buf_size ) {   
    uint8_t tx_buff[ 4 ] = { 0 };
    uint16_t cnt = 0;
    
    tx_buff[ 0 ] = SRAM3_OPCODE_READ;
    tx_buff[ 1 ] = mem_adr >> 16;
    tx_buff[ 2 ] = mem_adr >> 8;
    tx_buff[ 3 ] = mem_adr;

    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buff, 4 );
    spi_master_read( &ctx->spi, read_buf,  buf_size + 2 );
    spi_master_deselect_device( ctx->chip_select );    
}

err_t sram3_secure_read( sram3_t *ctx, uint32_t mem_adr, uint8_t *read_buf, uint8_t buf_size ) {
    static const ADDRESS_BYTES = 3;
    static const uint8_t extra_info = 4;
    err_t err_flag;
    
    uint8_t tx_buff[ 4 ] = { 0 };
    uint16_t cnt;
    uint8_t crc_extra_bytes = 0;
    uint16_t crc_sent = 0;
    uint16_t crc_received = 0;
    uint8_t crc_ok = 0;
    
    tx_buff[ 0 ] = SRAM3_OPCODE_SECURE_READ;
    tx_buff[ 1 ] = mem_adr >> 16;
    tx_buff[ 2 ] = mem_adr >> 8;
    tx_buff[ 3 ] = mem_adr;
    
    spi_master_select_device( ctx->chip_select );
    err_flag = spi_master_write( &ctx->spi, tx_buff,  4 );
    err_flag |= spi_master_read( &ctx->spi, read_buf,  buf_size + 1 );
    spi_master_deselect_device( ctx->chip_select );  
 
    return err_flag;
}

void sram3_write( sram3_t *ctx, uint32_t mem_adr, uint8_t *write_buf, uint8_t buf_size ) {   
    uint8_t tx_buf[ 260 ] = { 0 };
    uint16_t cnt = 0;
    
    tx_buf[ 0 ] = SRAM3_OPCODE_WRITE;
    tx_buf[ 1 ] = mem_adr >> 16;
    tx_buf[ 2 ] = mem_adr >> 8;
    tx_buf[ 3 ] = mem_adr;

    for( cnt = 0 ; cnt < buf_size; cnt++ ) {        
        tx_buf[ cnt + 4 ] = write_buf[ cnt ];
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, buf_size + 4 );
    spi_master_deselect_device( ctx->chip_select );
}

err_t sram3_secure_write( sram3_t *ctx, uint32_t mem_adr, uint8_t *write_buf, uint8_t buf_size ) {    
    uint8_t tx_buf[ 260 ] = { 0 };
    uint16_t cnt = 0;
    err_t err_flag;
    
    tx_buf[ 0 ] = SRAM3_OPCODE_SECURE_WRITE;
    tx_buf[ 1 ] = mem_adr >> 16;
    tx_buf[ 2 ] = mem_adr >> 8;
    tx_buf[ 3 ] = mem_adr;

    for( cnt = 0 ; cnt < buf_size; cnt++ ) {
        tx_buf[ cnt + 4 ] = write_buf[ cnt ];
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, buf_size + 4 );
    spi_master_deselect_device( ctx->chip_select );    
        return err_flag;
}

static uint8_t check_protect_range( sram3_t *ctx, uint8_t protect_range ) {   
    switch( protect_range ) {        
        case SRAM3_PROT_NONE:
        case SRAM3_PROT_QUART:
        case SRAM3_PROT_HALF:
        case SRAM3_PROT_ALL:
            return 1;
        default:
            return 0;
    }
}

static uint16_t crc16_calc( sram3_t *ctx, uint8_t *buf, uint8_t size ) {    
    static const uint16_t polynomial = 0x1021;               // x^16+x^12+x^5+1
    uint8_t i = 0, j = 0;
    uint16_t crc = 0xffff;
    
    // *** address_H has 1 address bit only. Calculate separate! *****
    crc = crc ^ ( buf[0] << 15 );
    for ( j = 0; j < 1; j++){                                // 1 bit only 
        if (( crc & 0x8000 ) == 0x8000 ) {                   // if x^16 = 1
            crc = ( crc << 1 ) ^ polynomial;
        }
        else {
            crc = ( crc << 1 );
        }
    }
    
    // calculate remaining bytes
    for ( i = 1; i < size; i++ ) {
        crc = crc ^ ( buf[ i ] << 8 );
        for ( j = 0; j < 8; j++ ) {                          // 8 bits/byte
            if (( crc & 0x8000 ) == 0x8000 ) {               // if x^16 = 1
                crc = ( crc << 1 ) ^ polynomial;
            }
            else {
                crc = ( crc << 1 );
            }
            crc = crc & 0xffff;                              // trim shouldn't be needed
        }
    }
    return crc;
}
// ------------------------------------------------------------------------- END
