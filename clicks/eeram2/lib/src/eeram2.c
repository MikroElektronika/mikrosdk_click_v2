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

#include "eeram2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define EERAM2_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static const uint16_t crc16_ccitt_table[ 256 ] =
{
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t dev_crc16_ccitt ( uint8_t *p_data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void eeram2_cfg_setup ( eeram2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->hld = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

EERAM2_RETVAL eeram2_init ( eeram2_t *ctx, eeram2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = EERAM2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return EERAM2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, EERAM2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->hld, cfg->hld );

    return EERAM2_OK;
}

void eeram2_generic_transfer ( eeram2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

void eeram2_set_on_hold_status ( eeram2_t *ctx, uint8_t en_hold )
{
    if ( en_hold == EERAM2_HOLD_ENABLE )
    {
        digital_out_low( &ctx->hld );
    }
    else
    {
        digital_out_high( &ctx->hld );
    }
}

void eeram2_set_command ( eeram2_t *ctx, uint8_t command )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = command;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 1 );

    spi_master_deselect_device( ctx->chip_select ); 
}

void eeram2_set_write_status ( eeram2_t *ctx, uint8_t en_write )
{
    if ( en_write == EERAM2_WRITE_ENABLE )
    {
        eeram2_set_command( ctx, EERAM2_CMD_WREN );
    }
    else
    {
        eeram2_set_command( ctx, EERAM2_CMD_WRDI );
    }
}

void eeram2_set_status ( eeram2_t *ctx, uint8_t tx_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = EERAM2_CMD_WRSR;
    tx_buf[ 1 ] = tx_data;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 2 );
    
    spi_master_deselect_device( ctx->chip_select ); 
}

uint8_t eeram2_get_status ( eeram2_t *ctx )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = EERAM2_CMD_RDSR;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 1 );
    
    spi_master_read( &ctx->spi, rx_buf, 1 );
    
    spi_master_deselect_device( ctx->chip_select ); 

    return rx_buf[ 0 ];
}

uint8_t eeram2_write_byte ( eeram2_t *ctx, uint32_t reg, uint8_t tx_data )
{
    uint8_t tx_buf[ 5 ];
    uint8_t status;

    status = EERAM2_SUCCESS;

    if ( reg > EERAM2_SRAM_ADDR_LAST )
    {
        status = EERAM2_ERROR;
    }

    tx_buf[ 0 ] = EERAM2_CMD_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( reg >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) reg;
    tx_buf[ 4 ] = tx_data;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 5 );
  
    spi_master_deselect_device( ctx->chip_select ); 

    return status;
}

uint8_t eeram2_read_byte ( eeram2_t *ctx, uint32_t reg )
{
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 1 ];

    reg &= EERAM2_SRAM_ADDR_LAST;

    tx_buf[ 0 ] = EERAM2_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( reg >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) reg;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 4 );

    spi_master_read( &ctx->spi, rx_buf, 1 );
    
    spi_master_deselect_device( ctx->chip_select ); 

    return rx_buf[ 0 ];
}

uint8_t eeram2_write_continuous ( eeram2_t *ctx, uint32_t reg, uint8_t *p_tx_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 256 ];
    uint8_t n_cnt;

    uint8_t status;

    status = EERAM2_SUCCESS;

    if ( reg > EERAM2_SRAM_ADDR_LAST )
    {
        status = EERAM2_ERROR;
    }

    tx_buf[ 0 ] = EERAM2_CMD_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( reg >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) reg;

    for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ )
    {
        tx_buf[ n_cnt + 4 ] = p_tx_data[ n_cnt ];
    }

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, n_bytes );

    spi_master_deselect_device( ctx->chip_select ); 

    return status;
}

uint8_t eeram2_read_continuous ( eeram2_t *ctx, uint32_t reg, uint8_t *p_rx_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 4 ];
    uint8_t n_cnt;

    reg &= EERAM2_SRAM_ADDR_LAST;

    tx_buf[ 0 ] = EERAM2_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( reg >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) reg;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 4 );
    
    spi_master_read( &ctx->spi, p_rx_data, n_bytes );
    
    spi_master_deselect_device( ctx->chip_select ); 

    return EERAM2_SUCCESS;
}

uint8_t eeram2_write_nonvolatile ( eeram2_t *ctx, uint8_t *p_tx_data )
{
    uint8_t tx_buf[ 17 ];
    uint8_t n_cnt;

    tx_buf[ 0 ] = EERAM2_CMD_WRNUR;

    for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
    {
        tx_buf[ n_cnt + 1 ] = p_tx_data[ n_cnt ];
    }

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 16 );
    
    spi_master_deselect_device( ctx->chip_select ); 

    return EERAM2_SUCCESS;
}

uint8_t eeram2_read_nonvolatile ( eeram2_t *ctx, uint8_t *p_rx_data )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = EERAM2_CMD_RDNUR;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 1 );

    spi_master_read( &ctx->spi, p_rx_data, 16 );

    spi_master_deselect_device( ctx->chip_select ); 

    return EERAM2_SUCCESS;
}

uint8_t eeram2_secure_write ( eeram2_t *ctx, uint16_t reg, uint8_t *p_tx_data )
{
    uint8_t tx_buf[ 133 ];
    uint8_t n_cnt;
    uint16_t crc;

    crc = dev_crc16_ccitt( &p_tx_data[ 0 ] );

    tx_buf[ 0 ] = EERAM2_CMD_SECURE_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) reg;

    for ( n_cnt = 0; n_cnt < 128; n_cnt++ )
    {
        tx_buf[ n_cnt + 3 ] = p_tx_data[ n_cnt ];
    }

    tx_buf[ 131 ] = ( uint8_t ) ( crc >> 8 );
    tx_buf[ 132 ] = ( uint8_t ) crc;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 132 );

    spi_master_deselect_device( ctx->chip_select ); 

    return EERAM2_SUCCESS;
}

uint8_t eeram2_secure_read ( eeram2_t *ctx, uint16_t reg, uint8_t *p_rx_data )
{
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 2 ];
    uint16_t crc;
    uint8_t n_cnt;

    reg &= EERAM2_SRAM_ADDR_LAST;

    tx_buf[ 0 ] = EERAM2_CMD_SECURE_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) reg;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, tx_buf, 3 );
    
    spi_master_read( &ctx->spi, p_rx_data, 127 );
        
    spi_master_read( &ctx->spi, rx_buf, 2 );
    
    spi_master_deselect_device( ctx->chip_select ); 

    crc = rx_buf[ 0 ];
    crc <<= 8;
    crc |= rx_buf[ 1 ];

    if ( crc == dev_crc16_ccitt( &p_rx_data[ 0 ] ) )
    {
        return EERAM2_SUCCESS;
    }
    else
    {
        return EERAM2_ERROR;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t dev_crc16_ccitt ( uint8_t *p_data )
{
    uint16_t crc;
    uint8_t len;
    uint8_t tmp;

    crc = 0x0000;

    for ( len = 0; len < 128; len++ )
    {
        tmp = ( uint8_t ) ( crc >> 8 );
        tmp ^= p_data[ len ];
        crc <<= 8;
        crc ^= crc16_ccitt_table[ tmp ];
    }
    return crc;
}

// ------------------------------------------------------------------------- END

