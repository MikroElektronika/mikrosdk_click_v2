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
 * @file sqiflash.c
 * @brief SQI FLASH Click Driver.
 */

#include "sqiflash.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief SQI FLASH command write.
 * @details This function writes a command.
 */
void sqiflash_command( sqiflash_t *ctx, uint8_t command );

/**
 * @brief SQI FLASH write.
 * @details This function writes a desired number of data bytes.
 */
void sqiflash_write( sqiflash_t *ctx, uint8_t *buffer, uint16_t count );

/**
 * @brief SQI FLASH read byte.
 * @details This function reads a byte.
 */
uint8_t sqiflash_read_byte( sqiflash_t *ctx );

/**
 * @brief SQI FLASH read.
 * @details This function reads a desired number of data bytes.
 */
void sqiflash_read( sqiflash_t *ctx, uint8_t *buffer, uint16_t count );

/**
 * @brief SQI FLASH write address.
 * @details This function writes to address.
 */
void sqiflash_write_address( sqiflash_t *ctx, uint32_t address );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void sqiflash_cfg_setup ( sqiflash_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->sq3 = HAL_PIN_NC;
    cfg->sq2 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t sqiflash_init ( sqiflash_t *ctx, sqiflash_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->sq3, cfg->sq3 );
    digital_out_init( &ctx->sq2, cfg->sq2 );
    
    digital_out_high( &ctx->sq3 );
    digital_out_low( &ctx->sq2 );

    return SPI_MASTER_SUCCESS;
}

err_t sqiflash_generic_write ( sqiflash_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t sqiflash_generic_read ( sqiflash_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void sqiflash_generic_transfer ( sqiflash_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, 
                                 uint16_t rd_len  ) {
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select ); 
}

uint8_t sqiflash_busy ( sqiflash_t *ctx ) {
    uint8_t temp;

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RDSR );
    temp = sqiflash_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= SQIFLASH_STATUS_BUSY;
    
    return temp;
}

uint8_t sqiflash_get_status_reg ( sqiflash_t *ctx ) {
    uint8_t temp;

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RDSR );
    temp = sqiflash_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  

    return temp;
}


uint8_t sqiflash_erase_status ( sqiflash_t *ctx ) {
    uint8_t temp;

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RDSR );
    temp = sqiflash_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= SQIFLASH_STATUS_WSE;

    return temp;
}

uint8_t sqiflash_write_status ( sqiflash_t *ctx ) {
    uint8_t temp;

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RDSR );
    temp = sqiflash_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= SQIFLASH_STATUS_WEL;

    return temp;
}

uint8_t sqiflash_program_status ( sqiflash_t *ctx ) {
    uint8_t temp;

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RDSR );
    temp = sqiflash_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= SQIFLASH_STATUS_WSP;

    return temp;
}

uint8_t sqiflash_protect_status ( sqiflash_t *ctx ) {
    uint8_t temp;

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RDSR );
    temp = sqiflash_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= SQIFLASH_STATUS_WPLD;

    return temp;
}

void sqiflash_lock_security_id ( sqiflash_t *ctx ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_LSID );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t sqiflash_security_status ( sqiflash_t *ctx ) {
    uint8_t temp;

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RDSR );
    temp = sqiflash_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  
    temp &= SQIFLASH_STATUS_SEC;

    return temp;
}

void sqiflash_write_protect_enable ( sqiflash_t *ctx ) {
    digital_out_high( &ctx->sq2 );
}

void sqiflash_write_protect_disable ( sqiflash_t *ctx ) {
    digital_out_low( &ctx->sq2 );
}

void sqiflash_hold_enable ( sqiflash_t *ctx ) {
    spi_master_select_device( ctx->chip_select );
    digital_out_high( &ctx->sq3 );
}

void sqiflash_hold_disable ( sqiflash_t *ctx ) {
    digital_out_low( &ctx->sq3 );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_write_suspend ( sqiflash_t *ctx ) {
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_WRSU );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_write_resume ( sqiflash_t *ctx ) {
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_WRRE );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_spi_get_security_id ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RSID );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  

    return;
}

void sqiflash_sqi_get_security_id ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RSID );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_set_security_id ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count ) {
    uint8_t addressL = 0;
    uint8_t addressH = 7;

    while ( sqiflash_busy( ctx ) );
    
    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_PSID );
    sqiflash_write( ctx, &addressL, 1);
    sqiflash_write( ctx, &addressH, 1);
    sqiflash_write( ctx, buffer, data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_write_disable ( sqiflash_t *ctx ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_WRDI );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_spi_get_bpr ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RBPR );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_sqi_get_bpr ( sqiflash_t *ctx, uint8_t *buffer, uint32_t data_count  ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RBPR );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_set_bpr ( sqiflash_t *ctx, uint8_t *buffer ) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_WBPR );
    sqiflash_write( ctx, buffer, 18 );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_lock_bpr ( sqiflash_t *ctx ) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_LBPR );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_nonvolatile_write_lock ( sqiflash_t *ctx, uint8_t *buffer) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_NVWLDR );
    sqiflash_write( ctx, buffer, 18 );
    spi_master_deselect_device( ctx->chip_select );  
}


void sqiflash_global_block_unlock ( sqiflash_t *ctx ) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_ULBPR );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_read_generic ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer,
                            uint32_t data_count ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_READ );
    sqiflash_write_address( ctx, address );
    sqiflash_read( ctx, &buffer[0], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_highspeed_r_read( sqiflash_t *ctx, uint32_t address, uint8_t *buffer,
                              uint32_t data_count ) {
    while ( sqiflash_busy( ctx ) )
    
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_HS_READ );
    sqiflash_write_address( ctx, address );
    sqiflash_write( ctx, buffer, data_count );
    spi_master_deselect_device( ctx->chip_select );  
}
void sqiflash_quad_write ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, uint32_t data_count ) {
    uint8_t i;
    uint8_t repeat;
    uint8_t repeat_over;
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_SPI_QUAD );
    
    if( data_count <= SQIFLASH_FLASH_PAGE_SIZE ) {


        sqiflash_write_address( ctx, address );
        sqiflash_write( ctx, buffer, data_count );

    } else {
        repeat = data_count / SQIFLASH_FLASH_PAGE_SIZE;
        repeat_over = data_count % SQIFLASH_FLASH_PAGE_SIZE;

        for ( i = 0; i < repeat; i++ ) {


            sqiflash_write_address( ctx, address + ( i * SQIFLASH_FLASH_PAGE_SIZE ) );
            sqiflash_write(ctx,  buffer + ( i * SQIFLASH_FLASH_PAGE_SIZE ),
                                        SQIFLASH_FLASH_PAGE_SIZE );
        }
        if ( repeat_over ) {

            sqiflash_write_address( ctx, address +
                                           ( repeat * SQIFLASH_FLASH_PAGE_SIZE ) );
            sqiflash_write( ctx, buffer + ( repeat * SQIFLASH_FLASH_PAGE_SIZE ),
                                        repeat_over );
        }
    }
    spi_master_deselect_device( ctx->chip_select );  

}

void sqiflash_write_generic ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer,
                        uint32_t data_count ) {
    uint8_t i;
    uint8_t repeat;
    uint8_t repeat_over;
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_PP );
    
    if( data_count <= SQIFLASH_FLASH_PAGE_SIZE ) {

        sqiflash_write_address( ctx, address );
        sqiflash_write( ctx, buffer, data_count );

    } else {
        repeat = data_count / SQIFLASH_FLASH_PAGE_SIZE;
        repeat_over = data_count % SQIFLASH_FLASH_PAGE_SIZE;

        for ( i = 0; i < repeat; i++ ) {

            sqiflash_write_address( ctx, address + ( i * SQIFLASH_FLASH_PAGE_SIZE ) );
            sqiflash_write( ctx, buffer + ( i * SQIFLASH_FLASH_PAGE_SIZE ),
                                        SQIFLASH_FLASH_PAGE_SIZE );
        }
        if ( repeat_over ) {
            
            sqiflash_write_address( ctx, address +
                                        ( repeat * SQIFLASH_FLASH_PAGE_SIZE ) );
            sqiflash_write( ctx, buffer + ( repeat * SQIFLASH_FLASH_PAGE_SIZE ),
                                 repeat_over );
        }
    }
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_quad_enable ( sqiflash_t *ctx ) {
    sqiflash_command( ctx, SQIFLASH_INSTR_EQIO );
}

void sqiflash_quad_out_read ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer,
                            uint32_t data_count) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->sq2 );
    digital_out_low( &ctx->sq3 );
    sqiflash_command( ctx, SQIFLASH_INSTR_SQOR );
    sqiflash_write_address( ctx, address );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_quad_io_read ( sqiflash_t *ctx, uint32_t address, uint8_t mode, uint8_t *buffer, 
                            uint32_t data_count) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->sq2 );
    digital_out_low( &ctx->sq3 );
    sqiflash_command( ctx, SQIFLASH_INSTR_SQIOR );
    sqiflash_write_address( ctx, address );
    sqiflash_write( ctx, &mode, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[0], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_quad_reset ( sqiflash_t *ctx ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RSTQIO );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_set_burst ( sqiflash_t *ctx, uint8_t length ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_SB );
    sqiflash_write( ctx, &length, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_read_sqi_burst_wrap ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, 
                                   uint32_t data_count ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RBSQI );
    sqiflash_write_address( ctx, address );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_read_spi_burst_wrap ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer,
                              uint32_t data_count ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RBSPI );
    sqiflash_write_address( ctx, address );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_read_dual_output ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer,
                                uint32_t data_count ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_SDOR );
    sqiflash_write_address( ctx, address );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_read_dual_io ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer,
                          uint32_t data_count ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_SDIOR );
    sqiflash_write_address( ctx, address );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[ 0 ], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_sector_erase ( sqiflash_t *ctx, uint32_t address ) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_SE );
    sqiflash_write_address( ctx, address );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_block_erase ( sqiflash_t *ctx, uint32_t address ) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_BE );
    sqiflash_write_address( ctx, address );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_chip_erase ( sqiflash_t *ctx ) {

    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_CE );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_get_sfdp_params ( sqiflash_t *ctx, uint32_t address, uint8_t *buffer, 
                               uint32_t data_count ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_SFDP );
    sqiflash_write_address( ctx, address );
    sqiflash_write( ctx, DUMMY, 1 );
    sqiflash_read( ctx, &buffer[0], data_count );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t sqiflash_quad_device_manufac ( sqiflash_t *ctx ) {
    uint8_t partial_info[ 3 ];

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_QUAD_JID );
    sqiflash_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 0 ];
} 

uint8_t sqiflash_quad_device_type ( sqiflash_t *ctx ) {
    uint8_t partial_info[ 3 ];

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_QUAD_JID );
    sqiflash_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 1 ];
}

uint8_t sqiflash_quad_device_id ( sqiflash_t *ctx  ) {
    uint8_t partial_info[ 3 ];

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_QUAD_JID );
    sqiflash_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 2 ];
}

uint8_t sqiflash_device_manufac ( sqiflash_t *ctx ) {
    uint8_t partial_info[ 3 ];

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_JEDECID );
    sqiflash_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 0 ];
}

uint8_t sqiflash_device_type ( sqiflash_t *ctx ) {
    uint8_t partial_info[ 3 ];

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_JEDECID );
    sqiflash_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 1 ];
}

uint8_t sqiflash_device_id ( sqiflash_t *ctx ) {
    uint8_t partial_info[ 3 ];

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_JEDECID );
    sqiflash_read( ctx, &partial_info[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );  

    return partial_info[ 2 ];
}

void sqiflash_reset ( sqiflash_t *ctx ) {
    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RSTEN );
    spi_master_deselect_device( ctx->chip_select );  
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RST );
    spi_master_deselect_device( ctx->chip_select );  
}

void sqiflash_write_status_reg ( sqiflash_t *ctx, uint8_t s_reg ) {
    while ( sqiflash_busy( ctx ) );

    sqiflash_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_WRSR );
    sqiflash_write( ctx, DUMMY, 1);
    sqiflash_write( ctx, &s_reg, 1);
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t sqiflash_get_config_reg ( sqiflash_t *ctx ) {
    uint8_t temp;

    while ( sqiflash_busy( ctx ) );

    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_RDCR );
    sqiflash_read( ctx, &temp, 1);
    spi_master_deselect_device( ctx->chip_select );  

    return temp;
}

void sqiflash_write_enable ( sqiflash_t *ctx ) {
    spi_master_select_device( ctx->chip_select );
    sqiflash_command( ctx, SQIFLASH_INSTR_WREN );
    spi_master_deselect_device( ctx->chip_select );  
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void sqiflash_command( sqiflash_t *ctx, uint8_t command ) {
    uint8_t tx_buf[ 1 ];
    tx_buf[ 0 ] = command;
    spi_master_write( &ctx->spi, &tx_buf[ 0 ], 1 );
}

void sqiflash_write( sqiflash_t *ctx, uint8_t *buffer, uint16_t count ) {
    spi_master_write( &ctx->spi, buffer, count );
}

uint8_t sqiflash_read_byte( sqiflash_t *ctx ) {
    uint8_t ret_val;

    spi_master_read( &ctx->spi, &ret_val, 1 );

    return ret_val;
}

void sqiflash_read( sqiflash_t *ctx, uint8_t *buffer, uint16_t count ) {
    spi_master_read( &ctx->spi, buffer, count );
}

void sqiflash_write_address( sqiflash_t *ctx, uint32_t addr ) {
    uint8_t temp[ 3 ];
    temp[ 0 ] = ( uint8_t ) ( addr >> 16 );
    temp[ 1 ] = ( uint8_t ) ( ( addr & 0x00FF00 ) >> 8);
    temp[ 2 ] = ( uint8_t ) ( addr & 0x0000FF );

    sqiflash_write( ctx, temp, 3 );
}


// ------------------------------------------------------------------------- END
