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
 * @file flash7.c
 * @brief Flash 7 Click Driver.
 */

#include "flash7.h"

void flash7_cfg_setup ( flash7_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->io2 = HAL_PIN_NC;
    cfg->io3 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t flash7_init ( flash7_t *ctx, flash7_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, FLASH7_DUMMY ) == SPI_MASTER_ERROR ) {
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

    digital_out_init( &ctx->io2, cfg->io2 );
    digital_out_init( &ctx->io3, cfg->io3 );

    return SPI_MASTER_SUCCESS;
}

err_t flash7_default_cfg ( flash7_t *ctx ) {
    digital_out_high( &ctx->io2 );
    digital_out_high( &ctx->io3 );
    return FLASH7_OK;
}

err_t flash7_generic_write ( flash7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
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

err_t flash7_generic_read ( flash7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}


void flash7_write_protect ( flash7_t *ctx, uint8_t en_write_protect ) {
    if ( en_write_protect == FLASH7_WRITE_PROTECT_ENABLE ) {
        digital_out_low( &ctx->io2 );
    } else {
        digital_out_high( &ctx->io2 );
    }
}

void flash7_hold ( flash7_t *ctx, uint8_t en_hold ) {
    if ( en_hold == FLASH7_HOLD_ENABLE ) {
        digital_out_low( &ctx->io3 );
    } else {
        digital_out_high( &ctx->io3 );
    }
}

void flash7_send_command ( flash7_t *ctx, uint8_t cmd ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = cmd;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void flash7_write_enable ( flash7_t *ctx ) {
    flash7_send_command( ctx,FLASH7_CMD_WREN );
}

void flash7_write_disable ( flash7_t *ctx ) {
    flash7_send_command( ctx, FLASH7_CMD_WRDI );
}

void flash7_chip_erase ( flash7_t *ctx ) {
    flash7_write_enable( ctx );
    Delay_1ms( );
    flash7_send_command( ctx, FLASH7_CMD_CE );
    Delay_1ms( );
}

uint8_t flash7_read_status_register ( flash7_t *ctx, uint8_t status_byte ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];
    
    if ( status_byte == 0 ) {
        tx_buf[ 0 ] = FLASH7_CMD_RDSR_LSB;
    } else {
        tx_buf[ 0 ] = FLASH7_CMD_RDSR_MSB;
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return rx_buf[ 0 ];
}

void flash7_write_status_register ( flash7_t *ctx, uint16_t status_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = FLASH7_CMD_WRSR;
    tx_buf[ 1 ] = ( uint8_t ) status_data;
    tx_buf[ 2 ] = ( uint8_t ) ( status_data >> 8 );

    flash7_write_enable( ctx );
    Delay_1ms( );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t flash7_page_program ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_tx_data, uint16_t n_bytes ) {
    uint8_t tx_buf[ 256 ];
    uint16_t n_cnt;
    uint8_t status;

    status = FLASH7_OK;

    if ( n_bytes < 256 ) {
        tx_buf[ 0 ] = FLASH7_CMD_WRITE;
        tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) mem_addr;

        for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ ) {
            tx_buf[ n_cnt + 4 ] = p_tx_data[ n_cnt ];
        }

        flash7_write_enable( ctx );
        Delay_1ms( );

        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tx_buf, n_bytes + 4 );
        spi_master_deselect_device( ctx->chip_select );
    } else {
        status = FLASH7_ERROR;
    }
    return status;
}


void flash7_read_memory ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_rx_data, uint16_t n_bytes ) {
    uint8_t tx_buf[ 5 ];

    mem_addr &= FLASH7_MEMORY_ADDR_END;

    tx_buf[ 0 ] = FLASH7_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) mem_addr;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 4, p_rx_data, n_bytes );
    spi_master_deselect_device( ctx->chip_select );
}

void flash7_fast_read_memory ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_rx_data, uint16_t n_bytes ) {
    uint8_t tx_buf[ 5 ];
    uint16_t cnt;

    mem_addr &= FLASH7_MEMORY_ADDR_END;

    tx_buf[ 0 ] = FLASH7_CMD_FREAD;
    tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) mem_addr;
    tx_buf[ 4 ] = FLASH7_DUMMY;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 5, p_rx_data, n_bytes );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t flash7_sector_erase ( flash7_t *ctx, uint16_t mem_sector ) {
    uint8_t tx_buf[ 5 ];
    uint8_t status;
    uint32_t mem_addr;
    
    status = FLASH7_OK;
    
    mem_addr = 1;

    if ( mem_sector > 0 ) {
        mem_sector -= 1;
        mem_addr += ( uint32_t )mem_sector * FLASH7_MEM_SECTOR_LEN;

        tx_buf[ 0 ] = FLASH7_CMD_SE;
        tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) mem_addr;

        flash7_write_enable( ctx );
        Delay_1ms( );

        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tx_buf, 4 );
        spi_master_deselect_device( ctx->chip_select );
    } else {
        status = FLASH7_ERROR;
    }
    
    return status;
}

uint8_t flash7_block_erase ( flash7_t *ctx, uint8_t mem_block, uint8_t mem_block_len ) {
    uint8_t tx_buf[ 5 ];
    uint8_t status;
    uint32_t mem_addr;
    uint32_t mem_sel;
    
    if ( mem_block_len == FLASH7_CMD_BE_32KB ) {
        mem_sel = FLASH7_MEMORY_BLOCK_SIZE;
    } else {
        mem_sel = FLASH7_MEMORY_BLOCK_SIZE << 1;
    }
    
    status = FLASH7_OK;
    
    mem_addr = 1;

    if ( ( mem_block > 0 ) && ( mem_block_len == FLASH7_CMD_BE_32KB || mem_block_len == FLASH7_CMD_BE_64KB ) ) {
        mem_block -= 1;
        mem_addr += ( uint32_t )mem_block * mem_sel;

        tx_buf[ 0 ] = mem_block_len;
        tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) mem_addr;

        flash7_write_enable( ctx );
        Delay_1ms( );

        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tx_buf, 4 );
        spi_master_deselect_device( ctx->chip_select );
    } else {
        status = FLASH7_ERROR;
    }

    return status;
}

void flash7_go_to_sleep ( flash7_t *ctx ) {
    flash7_send_command( ctx, FLASH7_CMD_SLEEP );
}

uint8_t flash7_wake_up ( flash7_t *ctx ) {
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 1 ];
    uint8_t dev_id;

    tx_buf[ 0 ] = FLASH7_CMD_WAKE;
    tx_buf[ 1 ] = FLASH7_DUMMY;
    tx_buf[ 2 ] = FLASH7_DUMMY;
    tx_buf[ 3 ] = FLASH7_DUMMY;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 4, rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );

    dev_id = rx_buf[ 0 ];

    return dev_id;
}

void flash7_read_id ( flash7_t *ctx, uint8_t *manufacturer_id, uint8_t *device_id ) {
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf[ 2 ];

    tx_buf[ 0 ] = FLASH7_CMD_REMS;
    tx_buf[ 1 ] = FLASH7_DUMMY;
    tx_buf[ 2 ] = FLASH7_DUMMY;
    tx_buf[ 3 ] = FLASH7_DUMMY;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 4, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    *manufacturer_id = rx_buf[ 0 ];
    *device_id = rx_buf[ 1 ];
}

void flash7_get_identification ( flash7_t *ctx, uint8_t *manufacturer_id, uint8_t *memory_type_id, uint8_t *capacity_id ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 3 ];

    tx_buf[ 0 ] = FLASH7_CMD_RDID;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    *manufacturer_id = rx_buf[ 0 ];
    *memory_type_id = rx_buf[ 1 ];
    *capacity_id = rx_buf[ 2 ];
}

void flash7_sw_reset ( flash7_t *ctx ) {
    flash7_send_command( ctx, FLASH7_CMD_ENRES );
    Delay_1ms( );
    flash7_send_command( ctx, FLASH7_CMD_RES );
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
