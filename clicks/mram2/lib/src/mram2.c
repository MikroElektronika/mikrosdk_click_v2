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

#include "mram2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MRAM2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Sleep Mode Entry Time function
 *
 * Function delays for 3 us allowing the device to enter the sleep mode.
**/
static void dev_sleep_mode_entry_time ( );

/**
 * @brief Sleep Mode Exit Time function
 *
 * Function delays for 400 us allowing the device to wake up frpm sleep mode.
**/
static void dev_sleep_mode_exit_time ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mram2_cfg_setup ( mram2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

MRAM2_RETVAL mram2_init ( mram2_t *ctx, mram2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MRAM2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return MRAM2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MRAM2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->cs );

    return MRAM2_OK;
}

// Read Status Register (RDSR)
uint8_t mram2_rdsr ( mram2_t *ctx )
{
    uint8_t tx_buf;
    uint8_t stat_reg;
    
    tx_buf = MRAM2_CMD_RDSR;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_read( &ctx->spi, &stat_reg, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    return stat_reg;
}

// Write Enable (WREN)
void mram2_wren ( mram2_t *ctx )
{
    uint8_t tx_buf;

    tx_buf = MRAM2_CMD_WREN;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

// Write Disable (WRDI)
void mram2_wrdi ( mram2_t *ctx )
{
    uint8_t tx_buf;

    tx_buf = MRAM2_CMD_WRDI;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

// Write Status Register (WRSR)
void mram2_wrsr ( mram2_t *ctx, uint8_t stat_reg )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = MRAM2_CMD_WRSR;
    tx_buf[ 1 ] = stat_reg;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
}

// Read Data Bytes (READ)
void mram2_read ( mram2_t *ctx, uint32_t mem_adr, uint8_t *rd_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 256 ];
    uint32_t cnt;

    tx_buf[ 0 ] = MRAM2_CMD_READ;
    tx_buf[ 1 ] = (uint8_t)( ( mem_adr >> 16 ) & 0x000000FF );
    tx_buf[ 2 ] = (uint8_t)( ( mem_adr >> 8 ) & 0x000000FF );
    tx_buf[ 3 ] = (uint8_t)( mem_adr & 0x000000FF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_read( &ctx->spi, rx_buf, n_bytes );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        rd_data[ cnt ] = rx_buf [ cnt ];
    }
}

// Fast Read Data Bytes (FREAD)
void mram2_fread ( mram2_t *ctx, uint32_t mem_adr, uint8_t mode, uint8_t *rd_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 5 ];
    uint8_t rx_buf[ 256 ];
    uint32_t cnt;

    tx_buf[ 0 ] = MRAM2_CMD_FREAD;
    tx_buf[ 1 ] = (uint8_t)( ( mem_adr >> 16 ) & 0x000000FF );
    tx_buf[ 2 ] = (uint8_t)( ( mem_adr >> 8 ) & 0x000000FF );
    tx_buf[ 3 ] = (uint8_t)( mem_adr & 0x000000FF );
    tx_buf[ 4 ] = mode;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 5 );
    spi_master_read( &ctx->spi, rx_buf, n_bytes );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        rd_data[ cnt ] = rx_buf [ cnt ];
    }
}

// Write Data Bytes (WRITE)
void mram2_write ( mram2_t *ctx, uint32_t mem_adr, uint8_t *wr_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 256 ];
    uint32_t cnt;

    tx_buf[ 0 ] = MRAM2_CMD_WRITE;
    tx_buf[ 1 ] = (uint8_t)( ( mem_adr >> 16 ) & 0x000000FF );
    tx_buf[ 2 ] = (uint8_t)( ( mem_adr >> 8 ) & 0x000000FF );
    tx_buf[ 3 ] = (uint8_t)( mem_adr & 0x000000FF );

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        tx_buf[ cnt + 4 ] = wr_data[ cnt ];
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, n_bytes + 4 );
    spi_master_deselect_device( ctx->chip_select ); 
}

// Enter Sleep Mode (SLEEP)
void mram2_sleep ( mram2_t *ctx )
{
    uint8_t tx_buf;

    tx_buf = MRAM2_CMD_SLEEP;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    dev_sleep_mode_entry_time( );
}

// Exit Sleep Mode (WAKE)
void mram2_wake_up ( mram2_t *ctx )
{
    uint8_t tx_buf;

    tx_buf = MRAM2_CMD_WAKE;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    dev_sleep_mode_exit_time( );
}

// Tamper Detect (TDET)
uint32_t mram2_tdet ( mram2_t *ctx )
{
    uint32_t result;
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 4 ];

    tx_buf[ 0 ] = MRAM2_CMD_TDET;
    tx_buf[ 1 ] = 0xFF;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_read( &ctx->spi, rx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    result = rx_buf[ 0 ];
    result << 8;
    result |= rx_buf[ 1 ];
    result << 8;
    result |= rx_buf[ 2 ];
    result << 8;
    result |= rx_buf[ 3 ];
    
    return result;
}

// Tamper Detect Exit (TDETX)
void mram2_tdetx ( mram2_t *ctx )
{
    uint8_t tx_buf;

    tx_buf = MRAM2_CMD_TDETX;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

// Read ID (RDID)
void mram2_rdid ( mram2_t *ctx, uint8_t *rd_id )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 7 ];
    uint32_t cnt;

    tx_buf[ 0 ] = MRAM2_CMD_RDID;
    tx_buf[ 1 ] = 0xFF;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_read( &ctx->spi, rx_buf, 5 );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < 5; cnt++ )
    {
        rd_id[ cnt ] = rx_buf [ cnt ];
    }
}

// Write Protect
void mram2_write_protect ( mram2_t *ctx, uint8_t state )
{
    if ( state == MRAM2_WP_ENABLE )
    {
        digital_out_low( &ctx->rst );
    }
    else if ( state == MRAM2_WP_DISABLE )
    {
        digital_out_high( &ctx->rst );
    }
}

// Hold
void mram2_hold ( mram2_t *ctx, uint8_t state )
{
    if ( state == MRAM2_HLD_ENABLE )
    {
        digital_out_low( &ctx->int_pin );
    }
    else if ( state == MRAM2_HLD_DISABLE )
    {
        digital_out_high( &ctx->int_pin );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_sleep_mode_entry_time ( )
{
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
}

static void dev_sleep_mode_exit_time ( )
{
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
}

// ------------------------------------------------------------------------- END

