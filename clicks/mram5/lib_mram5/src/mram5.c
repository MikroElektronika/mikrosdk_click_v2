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
 * @file mram5.c
 * @brief MRAM 5 Click Driver.
 */

#include "mram5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief MRAM 5 check address function.
 * @details This function checks whether the selected memory address range fits
 * inside the addressable memory.
 * @param[in] mem_addr : Start memory address.
 * @param[in] len : Number of bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mram5_check_address ( uint32_t mem_addr, uint32_t len );

void mram5_cfg_setup ( mram5_cfg_t *cfg ) 
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

err_t mram5_init ( mram5_t *ctx, mram5_cfg_t *cfg ) 
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

    Delay_1ms( );

    return SPI_MASTER_SUCCESS;
}

err_t mram5_default_cfg ( mram5_t *ctx ) 
{
    err_t error_flag = MRAM5_OK;
    
    /* 
     * The Exit Sleep Mode (WAKE) command turns on internal MRAM 
     * power regulators to allow normal operation.  
     */
    error_flag |= mram5_wake_up( ctx );

    return error_flag;
}

err_t mram5_set_command ( mram5_t *ctx, uint8_t cmd )
{
    /*
     * WREN, WRDI, SLEEP and WAKE instructions consist of one command byte 
     * and nothing else.
     */
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t mram5_generic_write ( mram5_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    /* Frame : cs_low | command_byte | data0 ..... dataN | cs_high */
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t mram5_generic_read ( mram5_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    /* Frame : cs_low | command_byte | dummy0 ..... dummyN | cs_high */
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t mram5_write_cmd_addr_data ( mram5_t *ctx, uint8_t cmd, uint32_t mem_addr, uint8_t *data_in, uint32_t len )
{
    /* Frame : cs_low | command_byte | addr_byte1 | addr_byte2 | addr_byte3 | data0 ..... dataN | cs_high */ 
    uint8_t data_buf[ MRAM5_ADDRESS_FRAME_SIZE ] = { 0 };

    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( mem_addr >> MRAM5_ADDRESS_BYTE_HIGH_SHIFT );
    data_buf[ 2 ] = ( uint8_t ) ( mem_addr >> MRAM5_ADDRESS_BYTE_MID_SHIFT );
    data_buf[ 3 ] = ( uint8_t ) mem_addr;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, MRAM5_ADDRESS_FRAME_SIZE );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t mram5_read_cmd_addr_data ( mram5_t *ctx, uint8_t cmd, uint32_t mem_addr, uint8_t *data_out, uint32_t len )
{
    /* Frame : cs_low | command_byte | addr_byte1 | addr_byte2 | addr_byte3 | dummy ..... dummyN | cs_high */ 
    uint8_t data_buf[ MRAM5_ADDRESS_FRAME_SIZE ] = { 0 };

    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( mem_addr >> MRAM5_ADDRESS_BYTE_HIGH_SHIFT );
    data_buf[ 2 ] = ( uint8_t ) ( mem_addr >> MRAM5_ADDRESS_BYTE_MID_SHIFT );
    data_buf[ 3 ] = ( uint8_t ) mem_addr;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_buf, MRAM5_ADDRESS_FRAME_SIZE, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t mram5_memory_write ( mram5_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len )
{
    err_t error_flag = MRAM5_OK;

    /* Address range guard */
    if ( MRAM5_ERROR == mram5_check_address( mem_addr, len ) )
    {
        return MRAM5_ERROR;
    }

    error_flag |= mram5_write_enable( ctx );
    error_flag |= mram5_write_cmd_addr_data( ctx, MRAM5_CMD_WRITE, mem_addr, data_in, len );

    return error_flag;
}

err_t mram5_memory_read ( mram5_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len )
{
    err_t error_flag = MRAM5_OK;
    
    /* Address range guard */
    if ( MRAM5_ERROR == mram5_check_address( mem_addr, len ) )
    {
        return MRAM5_ERROR;
    }

    error_flag |= mram5_read_cmd_addr_data( ctx, MRAM5_CMD_READ, mem_addr, data_out, len );

    return error_flag;
}

err_t mram5_write_enable ( mram5_t *ctx )
{
    uint8_t status = DUMMY;
    err_t error_flag = MRAM5_OK;

    /*
     * The Write Enable(WREN) command sets the Write Enable Latch(WEL) bit in the status register(bit 1). 
     * Write Enable Latch must be set prior to writing either bit in the status register or the memory. 
     */
    error_flag |= mram5_set_command( ctx, MRAM5_CMD_WREN );

    /* Check if writing has been enabled */
    error_flag |= mram5_get_status( ctx, &status );
    if ( !( status & MRAM5_STATUS_WEL_BIT_MASK ) )
    {
        error_flag = MRAM5_ERROR;
    }

    return error_flag;
}

err_t mram5_write_disable ( mram5_t *ctx )
{
    uint8_t status = DUMMY;
    err_t error_flag = MRAM5_OK;

    /*
     * The Write Disable (WRDI) command resets the Write Enable Latch (WEL) bit in the status register (bit 1) to 0.
     * This prevents writes to status register or memory.  
     */
    error_flag |= mram5_set_command( ctx, MRAM5_CMD_WRDI );

    /* Check if writing has been disabled */
    error_flag |= mram5_get_status( ctx, &status );
    if ( status & MRAM5_STATUS_WEL_BIT_MASK )
    {
        error_flag = MRAM5_ERROR;
    }

    return error_flag;
}

err_t mram5_get_status ( mram5_t *ctx, uint8_t *status )
{
    return mram5_generic_read( ctx, MRAM5_CMD_RDSR, status, 1 );
}

err_t mram5_set_status ( mram5_t *ctx, uint8_t status )
{
    err_t error_flag = MRAM5_OK;

    error_flag |= mram5_write_enable( ctx );
    error_flag |= mram5_generic_write( ctx, MRAM5_CMD_WRSR, &status, 1 );

    return error_flag;
}

err_t mram5_enter_sleep ( mram5_t *ctx )
{
    /*
     * The Enter Sleep Mode (SLEEP) command turns off all MRAM power regulators in order
     * to reduce the overall chip standby power.
     */
    return mram5_set_command( ctx, MRAM5_CMD_SLEEP );
}

err_t mram5_wake_up ( mram5_t *ctx )
{
    err_t error_flag = MRAM5_OK;

    /* The Exit Sleep Mode (WAKE) command turns on internal MRAM power regulators to allow normal operation. */
    error_flag |= mram5_set_command( ctx, MRAM5_CMD_WAKE );
    Delay_1ms( );

    return error_flag;
}

void mram5_set_wp ( mram5_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wp, state );
}
 
void mram5_set_hld ( mram5_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->hld, state );
}

static err_t mram5_check_address ( uint32_t mem_addr, uint32_t len )
{
    if ( 0 == len )
    {
        return MRAM5_ERROR;
    }

    if ( MRAM5_MEMORY_ADDRESS_MAX < mem_addr )
{
    return MRAM5_ERROR;
}

    if ( MRAM5_MEMORY_ADDRESS_MAX < ( mem_addr + len - 1 ) )
    {
        return MRAM5_ERROR;
    }

    return MRAM5_OK;
}

// ------------------------------------------------------------------------- END
