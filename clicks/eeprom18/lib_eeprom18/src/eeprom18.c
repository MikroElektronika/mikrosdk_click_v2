/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file eeprom18.c
 * @brief EEPROM 18 Click Driver.
 */

#include "eeprom18.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief EEPROM 18 wait ready function.
 * @details This function waits for the device to become ready for a new command
 * by polling the status register WIP bit.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t eeprom18_wait_ready ( eeprom18_t *ctx );

void eeprom18_cfg_setup ( eeprom18_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wp   = HAL_PIN_NC;
    cfg->hld  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t eeprom18_init ( eeprom18_t *ctx, eeprom18_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_init( &ctx->hld, cfg->hld );
    
    digital_out_high( &ctx->wp );
    digital_out_high( &ctx->hld );

    return SPI_MASTER_SUCCESS;
}

err_t eeprom18_write_memory ( eeprom18_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len ) 
{
    /* Write memory frame: CS_low | WRITE opcode(02h) | XXXX XXXA16 | A15:A8 | A7:A0 | data bytes | CS_high
     *
     * A16...A8 -> Page number
     * A7...A0  -> Byte number in a page */                                                                                         
    err_t error_flag = EEPROM18_OK;
    uint8_t cmd_buf[ 4 ] = { 0 };

    if ( NULL == data_in )
    {
        return EEPROM18_ERROR;
    }
    
    /* Verify that the start address is within bounds and that the write does not cross a page boundary. */
    if ( ( address >= EEPROM18_MEMORY_SIZE ) || ( ( ( address & EEPROM18_PAGE_OFFSET_MASK ) + len ) > EEPROM18_PAGE_SIZE ) )
    {
        return EEPROM18_ERROR;
    }
    
    /* A write enable must precede every memory, status, or identification page write */
    error_flag |= eeprom18_write_enable( ctx );
    
    /* Write opcode */
    cmd_buf[ 0 ] = EEPROM18_CMD_WRITE;

    /* Extract the 17bit address */
    cmd_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0x01 );
    cmd_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    cmd_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, cmd_buf, 4 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    
    /* Wait for the internal write cycle to finish before any other write/read instruction can be called */
    error_flag |= eeprom18_wait_ready( ctx );

    return error_flag;
}

err_t eeprom18_read_memory ( eeprom18_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len ) 
{
    /* Read memory frame: CS_low | read opcode(03h) | XXXX XXXA16 | A15:A8 | A7:A0 | data bytes | CS_high
     *
     * A16...A8 -> Page number
     * A7...A0  -> Byte number in a page */ 
                                                                                                  
    err_t error_flag = EEPROM18_OK;
    uint8_t cmd_buf[ 4 ] = { 0 };

    if ( NULL == data_out )
    {
        return EEPROM18_ERROR;
    }
    
    /* Verify that the read range does not exceed the memory bounds.*/
    if ( ( address + len ) > EEPROM18_MEMORY_SIZE ) 
    {
        return EEPROM18_ERROR;
    }
    
    /* Read opcode */
    cmd_buf[ 0 ] = EEPROM18_CMD_READ;

    /* Extract the 17bit address */
    cmd_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0x01 );
    cmd_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    cmd_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, cmd_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
        
    return error_flag;
}

err_t eeprom18_write_enable ( eeprom18_t *ctx ) 
{
    /* WRITE enable frame: CS_low | opcode(06h) | CS_high */
    uint8_t cmd = EEPROM18_CMD_WREN;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t eeprom18_write_disable ( eeprom18_t *ctx ) 
{
    /* Write disable frame: CS_low | opcode(04h) | CS_high */
    uint8_t cmd = EEPROM18_CMD_WRDI;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t eeprom18_read_status ( eeprom18_t *ctx, uint8_t *status ) 
{
    /* Read status register frame: CS_low | Opcode(05h) | D7...D0 | CS_high */
    uint8_t cmd = EEPROM18_CMD_RDSR;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, status, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t eeprom18_write_status ( eeprom18_t *ctx, uint8_t status ) 
{
    /* Write status register frame: CS_low | Opcode(01h) | D7...D0 | CS_high */
    err_t error_flag = EEPROM18_OK;
    uint8_t cmd_buf[ 2 ] = { 0 };
    
    /* A write enable must precede every memory, status, or identification page write */
    error_flag |= eeprom18_write_enable( ctx );

    cmd_buf[ 0 ] = EEPROM18_CMD_WRSR;
    cmd_buf[ 1 ] = status;

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, cmd_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    /* Wait for the internal write cycle to finish before any other write/read instruction can be called */
    error_flag |= eeprom18_wait_ready( ctx );

    return error_flag;
}

err_t eeprom18_write_id_page ( eeprom18_t *ctx, uint8_t offset, uint8_t *data_in, uint16_t len )
{
    /* Write identification page frame: CS_low | Opcode(82h) | 0x00 | XXXX X0XX | A7...A0 | data bytes | CS_high
     *
     * A7...A0 -> Offset within the 256-byte page. */
    err_t error_flag = EEPROM18_OK;
    uint8_t cmd_buf[ 4 ] = { 0 };

    if ( NULL == data_in )
    {
        return EEPROM18_ERROR;
    }

    /* Verify that the write does not cross the identification page boundary. */
    if ( ( ( uint16_t ) offset + len ) > EEPROM18_PAGE_SIZE )
    {
        return EEPROM18_ERROR;
    }

    /* A write enable must precede every memory, status, or identification page write. */
    error_flag |= eeprom18_write_enable( ctx );

    cmd_buf[ 0 ] = EEPROM18_CMD_WRID;
    cmd_buf[ 1 ] = 0x00;
    cmd_buf[ 2 ] = 0x00;
    cmd_buf[ 3 ] = offset;

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, cmd_buf, 4 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    /* Wait for the internal write cycle to finish before any other write/read instruction can be called. */
    error_flag |= eeprom18_wait_ready( ctx );

    return error_flag;
}

err_t eeprom18_read_id_page ( eeprom18_t *ctx, uint8_t offset, uint8_t *data_out, uint16_t len )
{
    /* Read identification page frame: CS_low | Opcode(83h) | 0x00 | XXXX X0XX | A7...A0 | data bytes | CS_high
     *
     * A7...A0 -> Offset within the 256-byte page. */
    err_t error_flag = EEPROM18_OK;
    uint8_t cmd_buf[ 4 ] = { 0 };

    if ( NULL == data_out )
    {
        return EEPROM18_ERROR;
    }

    /* Verify that the read range does not exceed the identification page bounds. */
    if ( ( ( uint16_t ) offset + len ) > EEPROM18_PAGE_SIZE )
    {
        return EEPROM18_ERROR;
    }

    cmd_buf[ 0 ] = EEPROM18_CMD_RDID;
    cmd_buf[ 1 ] = 0x00;
    cmd_buf[ 2 ] = 0x00;
    cmd_buf[ 3 ] = offset;

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, cmd_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t eeprom18_lock_id_page ( eeprom18_t *ctx )
{
    /* Lock identification page frame: CS_low | Opcode(82h) | 0x00 | XXXX X1XX | 0x00 | XXXX XX1X | CS_high */
    err_t error_flag = EEPROM18_OK;
    uint8_t cmd_buf[ 5 ] = { 0 };

    /* A write enable must precede every memory, status, or identification page write. */
    error_flag |= eeprom18_write_enable( ctx );

    cmd_buf[ 0 ] = EEPROM18_CMD_LID;
    cmd_buf[ 1 ] = 0x00;
    cmd_buf[ 2 ] = EEPROM18_ID_PAGE_A10_BIT;
    cmd_buf[ 3 ] = 0x00;
    cmd_buf[ 4 ] = EEPROM18_ID_PAGE_LOCK_BYTE;

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, cmd_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );

    /* Wait for the internal write cycle to finish before any other write/read instruction can be called. */
    error_flag |= eeprom18_wait_ready( ctx );

    return error_flag;
}

err_t eeprom18_read_lock_status ( eeprom18_t *ctx, uint8_t *lock_status )
{
    /* Read lock status frame: CS_low | Opcode(83h) | 0x00 | XXXX X1XX | 0x00 | lock status byte | CS_high */
    uint8_t cmd_buf[ 4 ] = { 0 };

    if ( NULL == lock_status )
    {
        return EEPROM18_ERROR;
    }

    /* RDLS opcode; A10 = 1 selects the lock status read. */
    cmd_buf[ 0 ] = EEPROM18_CMD_RDLS;
    cmd_buf[ 1 ] = 0x00;
    cmd_buf[ 2 ] = EEPROM18_ID_PAGE_A10_BIT;
    cmd_buf[ 3 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, cmd_buf, 4, lock_status, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void eeprom18_set_wp_pin ( eeprom18_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->wp, state );
}

void eeprom18_set_hold_pin ( eeprom18_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->hld, state );
}

static err_t eeprom18_wait_ready ( eeprom18_t *ctx )
{
    err_t error_flag = EEPROM18_OK;
    uint8_t status = 0;
    uint16_t timeout_cnt = EEPROM18_WRITE_TIMEOUT_MS;
    
    /* Poll status register until WIP = 0 -> device ready to decode a new command */
    do
    {
        error_flag |= eeprom18_read_status( ctx, &status );
        Delay_1ms( );
        timeout_cnt--;
    }
    while ( ( status & EEPROM18_STATUS_WIP ) && ( timeout_cnt > 0 ) );

    if ( 0 == timeout_cnt )
    {
        return EEPROM18_ERROR;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
