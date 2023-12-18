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

#include "flash2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define FLASH2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void flash2_command( flash2_t *ctx, uint8_t command );
void flash2_write( flash2_t *ctx, uint8_t *buffer, uint16_t count );
uint8_t flash2_read_byte( flash2_t *ctx );
void flash2_read( flash2_t *ctx, uint8_t *buffer, uint16_t count );
void flash2_write_address( flash2_t *ctx, uint32_t address );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void flash2_cfg_setup ( flash2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->hld = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000;
}

FLASH2_RETVAL flash2_init ( flash2_t *ctx, flash2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = FLASH2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return FLASH2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, FLASH2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->hld, cfg->hld );
    digital_out_init( &ctx->wp, cfg->wp );
    
    digital_out_low( &ctx->wp );
    digital_out_high ( &ctx->hld );     

    return FLASH2_OK;
}

void flash2_generic_transfer ( flash2_t *ctx, uint8_t *wr_buf, 
                               uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select ); 
}

uint8_t flash2_busy( flash2_t *ctx )
{
    uint8_t temp;

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RDSR );
    temp = flash2_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= FLASH2_STATUS_BUSY;
    return temp;
}

uint8_t flash2_get_status_reg( flash2_t *ctx )
{
    uint8_t temp;

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RDSR );
    temp = flash2_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  

    return temp;
}


uint8_t flash2_erase_status( flash2_t *ctx )
{
    uint8_t temp;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RDSR );
    temp = flash2_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= FLASH2_STATUS_WSE;

    return temp;
}

uint8_t flash2_write_status( flash2_t *ctx )
{
    uint8_t temp;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RDSR );
    temp = flash2_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= FLASH2_STATUS_WEL;

    return temp;
}

uint8_t flash2_program_status( flash2_t *ctx )
{
    uint8_t temp;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RDSR );
    temp = flash2_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= FLASH2_STATUS_WSP;

    return temp;
}

uint8_t flash2_protect_status( flash2_t *ctx )
{
    uint8_t temp;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RDSR );
    temp = flash2_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= FLASH2_STATUS_WPLD;

    return temp;
}

void flash2_lock_security_id( flash2_t *ctx )
{
    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_LSID );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t flash2_security_status( flash2_t *ctx )
{
    uint8_t temp;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RDSR );
    temp = flash2_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= FLASH2_STATUS_SEC;

    return temp;
}

void flash2_write_protect_enable( flash2_t *ctx )
{
    digital_out_high( &ctx->wp );
}

void flash2_write_protect_disable( flash2_t *ctx )
{
    digital_out_low( &ctx->wp );
}

void flash2_hold_enable( flash2_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    digital_out_high( &ctx->hld );
}

void flash2_hold_disable( flash2_t *ctx )
{
    digital_out_low( &ctx->hld );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_write_suspend( flash2_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_WRSU );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_write_resume( flash2_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_WRRE );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_spi_get_security_id( flash2_t *ctx, uint8_t *buffer, uint32_t data_count)
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RSID );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  

    return;
}

void flash2_sqi_get_security_id( flash2_t *ctx, uint8_t *buffer, uint32_t data_count)
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RSID );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_set_security_id( flash2_t *ctx, uint8_t *buffer, uint32_t data_count )
{
    uint8_t addressL = 0;
    uint8_t addressH = 7;

    while ( flash2_busy( ctx ) );
    
    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_PSID );
    flash2_write( ctx, &addressL, 1);
    flash2_write( ctx, &addressH, 1);
    flash2_write( ctx, buffer, data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_write_disable( flash2_t *ctx )
{
    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_WRDI );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_spi_get_bpr( flash2_t *ctx, uint8_t *buffer, uint32_t data_count )
{
    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RBPR );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_sqi_get_bpr( flash2_t *ctx, uint8_t *buffer, uint32_t data_count  )
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RBPR );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_set_bpr( flash2_t *ctx, uint8_t *buffer )
{
    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_WBPR );
    flash2_write( ctx, buffer, 18 );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_lockBpr( flash2_t *ctx )
{
    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_LBPR );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_nonvolatile_write_lock( flash2_t *ctx, uint8_t *buffer)
{
    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_NVWLDR );
    flash2_write( ctx, buffer, 18 );
    spi_master_deselect_device( ctx->chip_select );  
}


void flash2_global_block_unlock( flash2_t *ctx )
{
    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_ULBPR );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_read_generic( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count )
{
    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_READ );
    flash2_write_address( ctx, address );
    flash2_read( ctx, &buffer[0], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_highspeedRread( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count )
{
    while ( flash2_busy( ctx ) )
    
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_HS_READ );
    flash2_write_address( ctx, address );
    flash2_write( ctx, buffer, data_count );
    spi_master_deselect_device( ctx->chip_select );  
}
void flash2_quadWrite( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count )
{
    uint8_t i;
    uint8_t repeat;
    uint8_t repeat_over;
    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_SPI_QUAD );
    
    if( data_count <= FLASH2_FLASH_PAGE_SIZE )
    {


        flash2_write_address( ctx, address );
        flash2_write( ctx, buffer, data_count );

    }
    else
    {
        repeat = data_count / FLASH2_FLASH_PAGE_SIZE;
        repeat_over = data_count % FLASH2_FLASH_PAGE_SIZE;

        for ( i = 0; i < repeat; i++ )
        {


            flash2_write_address( ctx, address + ( i * FLASH2_FLASH_PAGE_SIZE ) );
            flash2_write(ctx,  buffer + ( i * FLASH2_FLASH_PAGE_SIZE ),
                                        FLASH2_FLASH_PAGE_SIZE );
        }
        if ( repeat_over )
        {

            flash2_write_address( ctx, address +
                                           ( repeat * FLASH2_FLASH_PAGE_SIZE ) );
            flash2_write( ctx, buffer + ( repeat * FLASH2_FLASH_PAGE_SIZE ),
                                        repeat_over );
        }
    }
    spi_master_deselect_device( ctx->chip_select );  

}

void flash2_write_generic( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                        uint32_t data_count )
{
    uint8_t i;
    uint8_t repeat;
    uint8_t repeat_over;
    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_PP );
    
    if( data_count <= FLASH2_FLASH_PAGE_SIZE )
    {

        flash2_write_address( ctx, address );
        flash2_write( ctx, buffer, data_count );

    }
    else
    {
        repeat = data_count / FLASH2_FLASH_PAGE_SIZE;
        repeat_over = data_count % FLASH2_FLASH_PAGE_SIZE;

        for ( i = 0; i < repeat; i++ )
        {

            flash2_write_address( ctx, address + ( i * FLASH2_FLASH_PAGE_SIZE ) );
            flash2_write( ctx, buffer + ( i * FLASH2_FLASH_PAGE_SIZE ),
                                        FLASH2_FLASH_PAGE_SIZE );
        }
        if ( repeat_over )
        {


            flash2_write_address( ctx, address +
                                           ( repeat * FLASH2_FLASH_PAGE_SIZE ) );
            flash2_write( ctx, buffer + ( repeat * FLASH2_FLASH_PAGE_SIZE ),
                                        repeat_over );
        }
    }
    spi_master_deselect_device( ctx->chip_select );  
    

}

void flash2_quad_enable( flash2_t *ctx )
{
    flash2_command( ctx, FLASH2_INSTR_EQIO );
}

void flash2_quad_out_read( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                            uint32_t data_count)
{

    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->wp );
    digital_out_low( &ctx->hld );
    flash2_command( ctx, FLASH2_INSTR_SQOR );
    flash2_write_address( ctx, address );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_quad_io_read( flash2_t *ctx, uint32_t address, uint8_t mode, uint8_t *buffer, uint32_t data_count)
{

    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->wp );
    digital_out_low( &ctx->hld );
    flash2_command( ctx, FLASH2_INSTR_SQIOR );
    flash2_write_address( ctx, address );
    flash2_write( ctx, &mode, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[0], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_quad_reset( flash2_t *ctx )
{

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RSTQIO );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_set_burst( flash2_t *ctx, uint8_t length )
{
    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_SB );
    flash2_write( ctx, &length, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_read_sqi_burst_wrap( flash2_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count )
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RBSQI );
    flash2_write_address( ctx, address );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_read_spi_burst_wrap( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                              uint32_t data_count )
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RBSPI );
    flash2_write_address( ctx, address );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_read_dual_output( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                                uint32_t data_count )
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_SDOR );
    flash2_write_address( ctx, address );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_read_dual_io ( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                          uint32_t data_count )
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_SDIOR );
    flash2_write_address( ctx, address );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_sector_erase( flash2_t *ctx, uint32_t address )
{
    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_SE );
    flash2_write_address( ctx, address );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_block_erase( flash2_t *ctx, uint32_t address )
{
    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_BE );
    flash2_write_address( ctx, address );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_chip_erase( flash2_t *ctx )
{

    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_CE );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_get_sfdp_params( flash2_t *ctx, uint32_t address, uint8_t *buffer,
                         uint32_t data_count )
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_SFDP );
    flash2_write_address( ctx, address );
    flash2_write( ctx, &dummy_byte, 1 );
    flash2_read( ctx, &buffer[0], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t flash2_quad_device_manufac( flash2_t *ctx )
{
    uint8_t partial_info[ 3 ];

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_QUAD_JID );
    flash2_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 0 ];
} 

uint8_t flash2_quad_device_type( flash2_t *ctx )
{
    uint8_t partial_info[ 3 ];

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_QUAD_JID );
    flash2_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 1 ];
}

uint8_t flash2_quad_device_id( flash2_t *ctx  )
{
    uint8_t partial_info[ 3 ];

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_QUAD_JID );
    flash2_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 2 ];
}

uint8_t flash2_device_manufac( flash2_t *ctx )
{
    uint8_t partial_info[ 3 ];

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_JEDECID );
    flash2_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 0 ];
}

uint8_t flash2_device_type( flash2_t *ctx )
{
    uint8_t partial_info[ 3 ];

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_JEDECID );
    flash2_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 1 ];
}

uint8_t flash2_device_id( flash2_t *ctx )
{
    uint8_t partial_info[ 3 ];

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_JEDECID );
    flash2_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 2 ];
}

void flash2_reset( flash2_t *ctx )
{
    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RSTEN );
    spi_master_deselect_device( ctx->chip_select );  
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RST );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash2_write_status_reg( flash2_t *ctx, uint8_t s_reg )
{
    uint8_t dummy_byte = 0x00;

    while ( flash2_busy( ctx ) );

    flash2_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_WRSR );
    flash2_write( ctx, &dummy_byte, 1);
    flash2_write( ctx, &s_reg, 1);
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t flash2_get_config_reg( flash2_t *ctx )
{
    uint8_t temp;

    while ( flash2_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_RDCR );
    flash2_read( ctx, &temp, 1);
    spi_master_deselect_device( ctx->chip_select );  

    return temp;
}

void flash2_write_enable( flash2_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    flash2_command( ctx, FLASH2_INSTR_WREN );
    spi_master_deselect_device( ctx->chip_select );  
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void flash2_command( flash2_t *ctx, uint8_t command )
{
    uint8_t tx_buf[ 1 ];
    tx_buf[ 0 ] = command;
    spi_master_write( &ctx->spi, &tx_buf[ 0 ], 1 );
}

void flash2_write( flash2_t *ctx, uint8_t *buffer, uint16_t count )
{
    spi_master_write( &ctx->spi, buffer, count );
}

uint8_t flash2_read_byte( flash2_t *ctx )
{
    uint8_t ret_val;

    spi_master_read( &ctx->spi, &ret_val, 1 );

    return ret_val;
}

void flash2_read( flash2_t *ctx, uint8_t *buffer, uint16_t count )
{
    spi_master_read( &ctx->spi, buffer, count );
}

void flash2_write_address( flash2_t *ctx, uint32_t addr )
{
    uint8_t temp[ 3 ];
    temp[ 0 ] = ( uint8_t ) ( addr >> 16 );
    temp[ 1 ] = ( uint8_t ) ( ( addr & 0x00FF00 ) >> 8);
    temp[ 2 ] = ( uint8_t ) ( addr & 0x0000FF );

    flash2_write( ctx, temp, 3 );
}



// ------------------------------------------------------------------------- END

