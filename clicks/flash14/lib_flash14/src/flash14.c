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
 * @file flash14.c
 * @brief Flash 14 Click Driver.
 */

#include "flash14.h"

/**
 * @brief Flash 14 spi select function.
 * @details This function selects the SPI device by clearing the CS pin.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void flash14_spi_select ( flash14_t *ctx );

/**
 * @brief Flash 14 spi deselect function.
 * @details This function deselects the SPI device by setting the CS pin.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void flash14_spi_deselect ( flash14_t *ctx );

/**
 * @brief Flash 14 spi write function.
 * @details This function writes a desired number of data bytes to SPI interface using bit-banging.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return None.
 * @note None.
 */
static void flash14_spi_write ( flash14_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 14 spi read function.
 * @details This function reads a desired number of data bytes from SPI interface using bit-banging.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of bytes to be read.
 * @return None.
 * @note None.
 */
static void flash14_spi_read ( flash14_t *ctx, uint8_t *data_out, uint8_t len );

void flash14_cfg_setup ( flash14_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wp   = HAL_PIN_NC;
    cfg->hold = HAL_PIN_NC;
}

err_t flash14_init ( flash14_t *ctx, flash14_cfg_t *cfg ) 
{
    err_t error_flag = FLASH14_OK;
    
    error_flag |= digital_out_init( &ctx->sck, cfg->sck );
    error_flag |= digital_out_init( &ctx->mosi, cfg->mosi );
    error_flag |= digital_out_init( &ctx->cs, cfg->cs );
    error_flag |= digital_out_init( &ctx->wp, cfg->wp );
    error_flag |= digital_out_init( &ctx->hold, cfg->hold );

    error_flag |= digital_in_init( &ctx->miso, cfg->miso );
    Delay_100ms ( );

    digital_out_high ( &ctx->cs );
    digital_out_low ( &ctx->sck );
    digital_out_low ( &ctx->mosi );
    digital_out_high ( &ctx->wp );
    digital_out_high ( &ctx->hold );
    Delay_100ms ( );

    return error_flag;
}

void flash14_write_cmd ( flash14_t *ctx, uint8_t cmd )
{
    flash14_spi_select ( ctx );
    flash14_spi_write ( ctx, &cmd, 1 );
    flash14_spi_deselect ( ctx );
    Delay_10ms ( );
}

err_t flash14_write_cmd_data ( flash14_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = FLASH14_OK;
    if ( ( NULL == data_in ) || ( len > 8 ) )
    {
        return FLASH14_ERROR;
    }
    flash14_spi_select ( ctx );
    flash14_spi_write ( ctx, &cmd, 1 );
    flash14_spi_write ( ctx, data_in, len );
    flash14_spi_deselect ( ctx );
    Delay_10ms ( );
    return error_flag;
}

err_t flash14_read_cmd_data ( flash14_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = FLASH14_OK;
    if ( ( NULL == data_out ) || ( len > 8 ) )
    {
        return FLASH14_ERROR;
    }
    flash14_spi_select ( ctx );
    flash14_spi_write ( ctx, &cmd, 1 );
    flash14_spi_read ( ctx, data_out, len );
    flash14_spi_deselect ( ctx );
    Delay_10ms ( );
    return error_flag;
}

err_t flash14_write_cmd_address_data ( flash14_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_in, uint32_t len )
{
    err_t error_flag = FLASH14_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    if ( ( NULL == data_in ) || ( ( address + len - 1 ) > FLASH14_MAX_ADDRESS ) )
    {
        return FLASH14_ERROR;
    }
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 24 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( address & 0xFF );
    flash14_spi_select ( ctx );
    flash14_spi_write ( ctx, data_buf, 5 );
    flash14_spi_write ( ctx, data_in, len );
    flash14_spi_deselect ( ctx );
    Delay_10ms ( );
    return error_flag;
}

err_t flash14_read_cmd_address_data ( flash14_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_out, uint32_t len )
{
    err_t error_flag = FLASH14_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    if ( ( NULL == data_out ) || ( ( address + len - 1 ) > FLASH14_MAX_ADDRESS ) )
    {
        return FLASH14_ERROR;
    }
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 24 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( address & 0xFF );
    flash14_spi_select ( ctx );
    flash14_spi_write ( ctx, data_buf, 5 );
    flash14_spi_read ( ctx, data_out, len );
    flash14_spi_deselect ( ctx );
    Delay_10ms ( );
    return error_flag;
}

err_t flash14_memory_write ( flash14_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len )
{
    err_t error_flag = FLASH14_OK;
    if ( len > FLASH14_PAGE_SIZE )
    {
        return FLASH14_ERROR;
    }
    error_flag |= flash14_write_enable ( ctx );
    error_flag |= flash14_write_cmd_address_data ( ctx, FLASH14_CMD_4B_PAGE_PROGRAM, address, data_in, len );
    error_flag |= flash14_write_protect ( ctx );
    return error_flag;
}

err_t flash14_memory_read ( flash14_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len )
{
    return flash14_read_cmd_address_data ( ctx, FLASH14_CMD_4B_READ_DATA, address, data_out, len );
}

err_t flash14_erase_memory ( flash14_t *ctx, uint8_t erase_cmd, uint32_t address )
{
    err_t error_flag = FLASH14_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t status = 0;
    if ( ( address > FLASH14_MAX_ADDRESS ) || 
         ( ( FLASH14_CMD_4B_SECTOR_ERASE_4KB != erase_cmd ) && 
           ( FLASH14_CMD_4B_BLOCK_ERASE_32KB != erase_cmd ) && 
           ( FLASH14_CMD_4B_BLOCK_ERASE_64KB != erase_cmd ) && 
           ( FLASH14_CMD_CHIP_ERASE != erase_cmd ) ) )
    {
        return FLASH14_ERROR;
    }
    if ( FLASH14_CMD_CHIP_ERASE == erase_cmd )
    {
        error_flag |= flash14_write_enable ( ctx );
        flash14_write_cmd ( ctx, erase_cmd );
    }
    else
    { 
        data_buf[ 0 ] = ( uint8_t ) ( ( address >> 24 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
        error_flag |= flash14_write_enable ( ctx );
        error_flag |= flash14_write_cmd_data ( ctx, erase_cmd, data_buf, 4 );
    }
    do 
    {
        Delay_100ms ( );
        error_flag |= flash14_read_cmd_data ( ctx, FLASH14_CMD_READ_STATUS, &status, 1 );
    }
    while ( ( FLASH14_OK == error_flag ) && ( FLASH14_STATUS_WIP == ( status & FLASH14_STATUS_WIP ) ) );
    
    error_flag |= flash14_write_protect ( ctx );
    return error_flag;
}

err_t flash14_check_communication ( flash14_t *ctx )
{
    uint8_t device_id[ 5 ] = { 0 };
    if ( FLASH14_OK == flash14_read_cmd_data( ctx, FLASH14_CMD_MANUFACTURER_DEVICE_ID, device_id, 5 ) )
    {
        if ( ( FLASH14_MANUFACTURER_ID == device_id[ 3 ] ) && 
             ( FLASH14_DEVICE_ID == device_id[ 4 ] ) )
        {
            flash14_write_cmd ( ctx, FLASH14_CMD_ENTER_4B_MODE );
            return FLASH14_OK;
        }
    }
    return FLASH14_ERROR;
}

err_t flash14_write_protect ( flash14_t *ctx )
{
    err_t error_flag = FLASH14_OK;
    uint8_t status = 0;
    digital_out_low ( &ctx->wp );
    flash14_write_cmd ( ctx, FLASH14_CMD_WRITE_DISABLE );
    error_flag |= flash14_read_cmd_data ( ctx, FLASH14_CMD_READ_STATUS, &status, 1 );
    if ( ( FLASH14_OK == error_flag ) && ( FLASH14_STATUS_WEL != ( status & FLASH14_STATUS_WEL ) ) )
    {
        return FLASH14_OK;
    }
    return FLASH14_ERROR;
}

err_t flash14_write_enable ( flash14_t *ctx )
{
    err_t error_flag = FLASH14_OK;
    uint8_t status = 0;
    digital_out_high ( &ctx->wp );
    flash14_write_cmd ( ctx, FLASH14_CMD_WRITE_ENABLE );
    error_flag |= flash14_read_cmd_data ( ctx, FLASH14_CMD_READ_STATUS, &status, 1 );
    if ( ( FLASH14_OK == error_flag ) && ( FLASH14_STATUS_WEL == ( status & FLASH14_STATUS_WEL ) ) )
    {
        return FLASH14_OK;
    }
    return FLASH14_ERROR;
}

void flash14_soft_reset ( flash14_t *ctx )
{
    flash14_write_cmd ( ctx, FLASH14_CMD_ENABLE_RESET );
    flash14_write_cmd ( ctx, FLASH14_CMD_RESET_DEVICE );
}

void flash14_set_wp_pin ( flash14_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

void flash14_set_hold_pin ( flash14_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->hold, state );
}

static void flash14_spi_select ( flash14_t *ctx )
{
    Delay_10us ( );
    digital_out_low ( &ctx->cs );
    Delay_10us ( );
}

static void flash14_spi_deselect ( flash14_t *ctx )
{
    Delay_10us ( );
    digital_out_high ( &ctx->cs );
    Delay_10us ( );
}

static void flash14_spi_write ( flash14_t *ctx, uint8_t *data_in, uint8_t len )
{
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( data_in[ byte_cnt ] & ( 0x80 >> bit_cnt ) )
            {
                digital_out_high ( &ctx->mosi );
            }
            else
            {
                digital_out_low ( &ctx->mosi );
            }
            digital_out_high ( &ctx->sck );
            Delay_1us ( );
            digital_out_low ( &ctx->sck );
            Delay_1us ( );
        }
        digital_out_low ( &ctx->mosi );
        Delay_1us ( );
    }
}

static void flash14_spi_read ( flash14_t *ctx, uint8_t *data_out, uint8_t len )
{
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        data_out[ byte_cnt ] = 0;
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            digital_out_high ( &ctx->sck );
            Delay_1us ( );
            
            data_out[ byte_cnt ] |= ( ( !!digital_in_read ( &ctx->miso ) ) << ( 7 - bit_cnt ) );

            digital_out_low ( &ctx->sck );
            Delay_1us ( );
        }
        Delay_1us ( );
    }
}

// ------------------------------------------------------------------------- END
