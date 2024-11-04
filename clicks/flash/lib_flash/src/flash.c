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
 * \file flash.c
 *
 */

#include <string.h>
#include "flash.h"


// ------------------------------------------------------------- PRIVATE MACROS

//  FLASH Commands.
#define FLASH_CMD_RDID   0x9F
#define FLASH_CMD_READ   0x3
#define FLASH_CMD_WRITE  0x2
#define FLASH_CMD_WREN   0x6
#define FLASH_CMD_WDIS   0x4
#define FLASH_CMD_RDSR   0x5
#define FLASH_CMD_WRSR   0x1
#define FLASH_CMD_ERASE  0xC7
#define FLASH_CMD_BER    0xD8
#define FLASH_CMD_HBER   0x52
#define FLASH_CMD_SER    0x20
#define FLASH_CMD_RSTEN  0x66
#define FLASH_CMD_RST    0x99

#define FLASH_DUMMY  0x0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Generic Transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer function, for sending and receiving data
 * packages.
 */
static void flash_spi_master_transfer( flash_t *ctx,
                           uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic Command Send function.
 *
 * @param ctx      Click object.
 * @param command  Command to be sent.
 *
 * @description Generic function for sending commands to Flash Click.
 */
static void flash_send_cmd( flash_t *ctx, uint8_t command );

/**
 * @brief Generic Memory Erase function.
 *
 * @param ctx        Click object.
 * @param erase_cmd  Command which selects the part of the memory content to be
 *                   erased.
 * @param mem_addr   Memory address.
 *
 * @returns 0x0 - Ok,
 *          0xFE - Invalid memory address.
 *
 * @description Generic function to select the part of the memory content which
 * will be erased.
 */
static flash_err_t flash_erase( flash_t *ctx, uint8_t erase_cmd, uint32_t mem_addr );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void flash_cfg_setup( flash_cfg_t *cfg )
{
    cfg->sdo = HAL_PIN_NC;
    cfg->sdi = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->hld = HAL_PIN_NC;
    cfg->wp  = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

flash_err_t flash_init( flash_t *ctx, flash_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->sdo;
    spi_cfg.mosi      = cfg->sdi;
    spi_cfg.default_write_data = FLASH_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

     if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return FLASH_ERR_INIT_DRV;
    }

    spi_master_set_default_write_data( &ctx->spi, FLASH_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    digital_out_init( &ctx->hld, cfg->hld );
    digital_out_init( &ctx->wp, cfg->wp );

    return FLASH_OK;
}

void flash_default_cfg( flash_t *ctx )
{
    flash_set_hold_pin( ctx, FLASH_PIN_STATE_HIGH );
    flash_set_write_protect_pin( ctx, FLASH_PIN_STATE_HIGH );
    flash_write_status( ctx, FLASH_STATUS_SET_OTP_LOCK );
}

void flash_reset( flash_t *ctx )
{
    flash_send_cmd( ctx, FLASH_CMD_RSTEN );
    Delay_10ms( );
    flash_send_cmd( ctx, FLASH_CMD_RST );
    Delay_1sec( );
}

void flash_write_enable( flash_t *ctx )
{
    flash_send_cmd( ctx, FLASH_CMD_WREN );
}

void flash_write_disable( flash_t *ctx )
{
    flash_send_cmd( ctx, FLASH_CMD_WDIS );
}

void flash_write_status( flash_t *ctx, uint8_t data_tx )
{
    uint8_t data_in[ 2 ];

    flash_write_enable( ctx );
    Delay_10ms( );

    data_in[ 0 ] = FLASH_CMD_WRSR;
    data_in[ 1 ] = data_tx & 0xFC;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_in, 2 );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t flash_read_status( flash_t *ctx )
{
    uint8_t data_in;
    uint8_t data_out[ 1 ];

    data_in = FLASH_CMD_RDSR;
    memset( data_out, FLASH_DUMMY, sizeof( data_out ) );

    flash_spi_master_transfer( ctx, &data_in, 1, data_out, 1 );

    return data_out[ 0 ];
}

void flash_read_id( flash_t *ctx, uint8_t *manufact_id, uint16_t *dev_id )
{
    uint8_t data_in;
    uint8_t data_out[ 3 ];

    data_in = FLASH_CMD_RDID;
    memset( data_out, FLASH_DUMMY, sizeof( data_out ) );

    flash_spi_master_transfer( ctx, &data_in, 1, data_out, 3 );

    *manufact_id = data_out[ 0 ];
    *dev_id      = data_out[ 1 ];
    *dev_id    <<= 8;
    *dev_id     |= data_out[ 2 ];
}

flash_err_t flash_write_byte( flash_t *ctx, uint32_t mem_addr, uint8_t data_tx )
{
    uint8_t data_in[ 5 ];

    if ( mem_addr > FLASH_MEM_ADDR_LAST_PAGE_END )
    {
        return FLASH_ERR_MEM_ADDR;
    }

    flash_write_enable( ctx );
    Delay_10ms( );

    data_in[ 0 ] = FLASH_CMD_WRITE;
    data_in[ 1 ] = mem_addr >> 16;
    data_in[ 2 ] = mem_addr >> 8;
    data_in[ 3 ] = mem_addr;
    data_in[ 4 ] = data_tx;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_in, 5 );
    spi_master_deselect_device( ctx->chip_select );  

    return FLASH_OK;
}

flash_err_t flash_read_byte( flash_t *ctx, uint32_t mem_addr, uint8_t *data_rx )
{
    uint8_t data_in[ 4 ];
    uint8_t data_out[ 1 ];

    if ( mem_addr > FLASH_MEM_ADDR_LAST_PAGE_END )
    {
        return FLASH_ERR_MEM_ADDR;
    }

    data_in[ 0 ] = FLASH_CMD_READ;
    data_in[ 1 ] = mem_addr >> 16;
    data_in[ 2 ] = mem_addr >> 8;
    data_in[ 3 ] = mem_addr;
    memset( data_out, FLASH_DUMMY, sizeof( data_out ) );

    flash_spi_master_transfer( ctx, data_in, 4, data_out, 1 );

    *data_rx = data_out[ 0 ];

    return FLASH_OK;
}

flash_err_t flash_write_page( flash_t *ctx, uint32_t mem_addr, uint8_t *data_tx,
                  uint16_t n_data )
{
    uint8_t data_in[ 260 ];
    uint16_t cnt;

    if ( mem_addr > FLASH_MEM_ADDR_LAST_PAGE_END )
    {
        return FLASH_ERR_MEM_ADDR;
    }

    if ( ( n_data < FLASH_NDATA_TRANSFER_MIN ) ||
         ( n_data > FLASH_NDATA_TRANSFER_MAX ) )
    {
        return FLASH_ERR_NDATA;
    }

    flash_write_enable( ctx );
    Delay_10ms( );

    data_in[ 0 ] = FLASH_CMD_WRITE;
    data_in[ 1 ] = mem_addr >> 16;
    data_in[ 2 ] = mem_addr >> 8;
    data_in[ 3 ] = mem_addr;

    for ( cnt = 0; cnt < n_data; cnt++ )
    {
        data_in[ cnt + 4 ] = *data_tx;
        data_tx++;
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_in, n_data + 4 );
    spi_master_deselect_device( ctx->chip_select );  

    return FLASH_OK;
}

flash_err_t flash_read_page( flash_t *ctx, uint32_t mem_addr, uint8_t *data_rx,
                 uint16_t n_data )
{
    uint8_t data_in[ 4 ];
    uint8_t data_out[ 260 ];

    if ( mem_addr > FLASH_MEM_ADDR_LAST_PAGE_END )
    {
        return FLASH_ERR_MEM_ADDR;
    }

    if ( ( n_data < FLASH_NDATA_TRANSFER_MIN ) ||
         ( n_data > FLASH_NDATA_TRANSFER_MAX ) )
    {
        return FLASH_ERR_NDATA;
    }

    data_in[ 0 ] = FLASH_CMD_READ;
    data_in[ 1 ] = mem_addr >> 16;
    data_in[ 2 ] = mem_addr >> 8;
    data_in[ 3 ] = mem_addr;
    memset( data_out, FLASH_DUMMY, sizeof( data_out ) );

    flash_spi_master_transfer( ctx, data_in, 4, data_rx, n_data );

    return FLASH_OK;
}

void flash_erase_chip( flash_t *ctx )
{
    flash_write_enable( ctx );
    Delay_10ms( );
    flash_send_cmd( ctx, FLASH_CMD_ERASE );
}

flash_err_t flash_erase_block( flash_t *ctx, uint32_t mem_addr )
{
    return flash_erase( ctx, FLASH_CMD_BER, mem_addr );
}

flash_err_t flash_erase_half_block( flash_t *ctx, uint32_t mem_addr )
{
    return flash_erase( ctx, FLASH_CMD_HBER, mem_addr );
}

flash_err_t flash_erase_sector( flash_t *ctx, uint32_t mem_addr )
{
    return flash_erase( ctx, FLASH_CMD_SER, mem_addr );
}

void flash_set_write_protect_pin( flash_t *ctx, flash_pin_state_t state )
{
    digital_out_write( &ctx->wp, state );
}

void flash_set_hold_pin( flash_t *ctx, flash_pin_state_t state )
{
    digital_out_write( &ctx->hld, state );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void flash_spi_master_transfer( flash_t *ctx,
                           uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

static void flash_send_cmd( flash_t *ctx, uint8_t command )
{
    uint8_t data_in;

    data_in = command;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

static flash_err_t flash_erase( flash_t *ctx, uint8_t erase_cmd, uint32_t mem_addr )
{
    uint8_t data_in[ 4 ];

    if ( mem_addr > FLASH_MEM_ADDR_LAST_PAGE_END )
    {
        return FLASH_ERR_MEM_ADDR;
    }

    flash_write_enable( ctx );
    Delay_10ms( );

    data_in[ 0 ] = erase_cmd;
    data_in[ 1 ] = mem_addr >> 16;
    data_in[ 2 ] = mem_addr >> 8;
    data_in[ 3 ] = mem_addr;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_in, 4 );
    spi_master_deselect_device( ctx->chip_select );  

    return FLASH_OK;
}

// ------------------------------------------------------------------------ END
