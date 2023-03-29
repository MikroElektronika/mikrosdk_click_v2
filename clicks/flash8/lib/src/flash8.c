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
 * @file flash8.c
 * @brief Flash 8 Click Driver.
 */

#include "flash8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                             0x00

/**
 * @brief Column Address 13-bit data mask.
 * @details Definition of Column Address 13-bit data mask.
 */
#define FLASH8_COLUMN_ADDR_13_BIT_MASK    0x1FFF

/**
 * @brief Row Address 18-bit data mask.
 * @details Definition of Row Address 18-bit data mask.
 */
#define FLASH8_ROW_ADDR_18_BIT_MASK      0x0003FFFF

void flash8_cfg_setup ( flash8_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;
    cfg->hld = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t flash8_init ( flash8_t *ctx, flash8_cfg_t *cfg ) {
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

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_init( &ctx->hld, cfg->hld );

    return SPI_MASTER_SUCCESS;
}

err_t flash8_default_cfg ( flash8_t *ctx ) {
    flash8_write_protect_disable( ctx );
    flash8_hold_disable( ctx );
    
    return FLASH8_OK;
}

err_t flash8_generic_write ( flash8_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = cmd;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t flash8_generic_read ( flash8_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) {

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t flash8_hold_enable ( flash8_t *ctx ) {
    digital_out_low( &ctx->hld );
    
    return FLASH8_OK;
}

err_t flash8_hold_disable ( flash8_t *ctx ) {
    digital_out_high( &ctx->hld );
    
    return FLASH8_OK;
}

err_t flash8_write_protect_enable ( flash8_t *ctx ) {
    digital_out_low( &ctx->wp );
    
    return FLASH8_OK;
}

err_t flash8_write_protect_disable ( flash8_t *ctx ) {
    digital_out_high( &ctx->wp );
    
    return FLASH8_OK;
}

err_t flash8_read_cell_array ( flash8_t *ctx, uint32_t row_address, uint16_t column_address, uint8_t *feature_status_out ) {
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 4 ];
    
    row_address &= FLASH8_ROW_ADDR_18_BIT_MASK;
    column_address &= FLASH8_COLUMN_ADDR_13_BIT_MASK;

    tx_buf[ 0 ] = FLASH8_CMD_READ_CELL_ARRAY;
    tx_buf[ 1 ] = ( uint8_t ) ( row_address >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( row_address >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) row_address;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    tx_buf[ 0 ] = FLASH8_CMD_GET_FEATURE;
    tx_buf[ 1 ] = FLASH8_FEATURE_C0;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, tx_buf, 2, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    *feature_status_out = rx_buf[ 0 ];
    
    tx_buf[ 0 ] = FLASH8_CMD_READ_BUFFER;
    tx_buf[ 1 ] = ( uint8_t ) ( column_address >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) column_address;
    tx_buf[ 3 ] = DUMMY;

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 4, rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t flash8_read_buffer ( flash8_t *ctx, uint16_t column_address, uint8_t *read_data ) {
    uint8_t rx_buf[ 6 ];
    uint8_t tx_buf[ 4 ];
    
    column_address &= FLASH8_COLUMN_ADDR_13_BIT_MASK;

    tx_buf[ 0 ] = FLASH8_CMD_READ_BUFFER;
    tx_buf[ 1 ] = ( uint8_t ) ( column_address >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) column_address;
    tx_buf[ 3 ] = DUMMY;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 4, rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    *read_data = rx_buf[ 0 ];

    return error_flag;
}

err_t flash8_program_load ( flash8_t *ctx, uint16_t column_address, uint8_t *data_in, uint16_t len ) {
   uint8_t tx_buf[ 2048 ];
    
    column_address &= FLASH8_COLUMN_ADDR_13_BIT_MASK;

    tx_buf[ 0 ] = FLASH8_CMD_PROGRAM_LOAD;
    tx_buf[ 1 ] = ( uint8_t ) ( column_address >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) column_address;
    for ( uint16_t cnt = 3; cnt < len + 3; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t flash8_program_execute ( flash8_t *ctx, uint32_t row_address ) {
    uint8_t tx_buf[ 4 ];
    
    row_address &= FLASH8_ROW_ADDR_18_BIT_MASK;

    tx_buf[ 0 ] = FLASH8_CMD_PROGRAM_EXECUTE;
    tx_buf[ 1 ] = ( uint8_t ) ( row_address >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( row_address >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) row_address;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t flash8_program_load_random ( flash8_t *ctx, uint16_t column_address, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 2048 ];
    
    column_address &= FLASH8_COLUMN_ADDR_13_BIT_MASK;

    tx_buf[ 0 ] = FLASH8_CMD_PROGRAM_LOAD_RANDOM_DATA;
    tx_buf[ 1 ] = ( uint8_t ) ( column_address >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) column_address;
    for ( uint16_t cnt = 3; cnt < len + 3; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t flash8_block_erase ( flash8_t *ctx, uint32_t row_address, uint8_t *feature_status_out ) {
    uint8_t tx_buf[ 4 ];
    
    row_address &= FLASH8_ROW_ADDR_18_BIT_MASK;
    
    flash8_write_enable( ctx );

    tx_buf[ 0 ] = FLASH8_CMD_BLOCK_ERASE;
    tx_buf[ 1 ] = ( uint8_t ) ( row_address >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( row_address >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) row_address;
    

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    flash8_get_feature( ctx, FLASH8_FEATURE_C0, feature_status_out );
    
    return error_flag;
}

err_t flash8_sw_reset ( flash8_t *ctx, uint8_t *feature_status_out ) {
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = FLASH8_CMD_RESET;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    flash8_get_feature( ctx, FLASH8_FEATURE_C0, feature_status_out );
    
    return error_flag;
}

err_t flash8_write_enable ( flash8_t *ctx ) {
    uint8_t write_enable;

    write_enable = FLASH8_CMD_WRITE_ENABLE;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &write_enable, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t flash8_write_disable ( flash8_t *ctx ) {
    uint8_t write_enable;

    write_enable = FLASH8_CMD_WRITE_DISABLE;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &write_enable, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t flash8_set_feature ( flash8_t *ctx, uint8_t feature_addr, uint8_t feature_data ) {
    uint8_t tx_buf[ 3 ];
    tx_buf[ 0 ] = FLASH8_CMD_SET_FEATURE;
    tx_buf[ 1 ] = feature_addr;
    tx_buf[ 2 ] = feature_data;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t flash8_set_config_feature ( flash8_t *ctx, feature_cfg_t feature_data ) {
    uint8_t tx_data;
   
    tx_data  = ( feature_data.brwd & 0x01 ) << 7;
    tx_data |= ( feature_data.bl   & 0x07 ) << 3;
    
    err_t error_flag = flash8_set_feature(  ctx, FLASH8_FEATURE_A0, tx_data );
    
    tx_data  = ( feature_data.idr_e  & 0x01 ) << 6;
    tx_data |= ( feature_data.ecc_e  & 0x01 ) << 4;
    tx_data |= ( feature_data.prt_e  & 0x01 ) << 2;
    tx_data |= ( feature_data.hse    & 0x01 ) << 1;
    tx_data |=   feature_data.hold_d & 0x01;
    
    error_flag |= flash8_set_feature(  ctx, FLASH8_FEATURE_B0, tx_data );
    
    tx_data  = ( feature_data.eccs  & 0x03 ) << 4;
    tx_data |= ( feature_data.prg_f & 0x01 ) << 3;
    tx_data |= ( feature_data.ers_f & 0x01 ) << 2;
    tx_data |= ( feature_data.wel   & 0x01 ) << 1;
    tx_data |=   feature_data.oip   & 0x01;
    
    error_flag |= flash8_set_feature(  ctx, FLASH8_FEATURE_C0, tx_data );
    
    if ( feature_data.wel == 1 ) {
        error_flag |= flash8_write_enable( ctx );
    } else {
        error_flag |= flash8_write_disable( ctx );    
    }

    return error_flag;
}

err_t flash8_get_feature ( flash8_t *ctx, uint8_t feature_addr, uint8_t *feature_status_out ) {
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = FLASH8_CMD_GET_FEATURE;
    tx_buf[ 1 ] = feature_addr;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    *feature_status_out = rx_buf[ 0 ];

    return error_flag;
}

err_t flash8_get_config_feature ( flash8_t *ctx, feature_cfg_t *feature_data ) {
    uint8_t rx_data;
    
    err_t error_flag = flash8_get_feature( ctx, FLASH8_FEATURE_A0, &rx_data );
    
    feature_data->brwd = ( rx_data >> 7 ) & 0x01;
    feature_data->bl   = ( rx_data >> 3 ) & 0x07;
    
    error_flag |= flash8_get_feature( ctx, FLASH8_FEATURE_B0, &rx_data );
    
    feature_data->idr_e  = ( rx_data >> 6 ) & 0x01;
    feature_data->ecc_e  = ( rx_data >> 4 ) & 0x01;
    feature_data->prt_e  = ( rx_data >> 2 ) & 0x01;
    feature_data->hse    = ( rx_data >> 1 ) & 0x01;
    feature_data->hold_d =   rx_data & 0x01;
    
    error_flag |= flash8_get_feature( ctx, FLASH8_FEATURE_C0, &rx_data );
    
    feature_data->eccs  = ( rx_data >> 4 ) & 0x03;
    feature_data->prg_f = ( rx_data >> 3 ) & 0x01;
    feature_data->ers_f = ( rx_data >> 2 ) & 0x01;
    feature_data->wel   = ( rx_data >> 1 ) & 0x01;
    feature_data->oip   =   rx_data & 0x01;

    return error_flag;
}

err_t flash8_protected_area_all_unlocked ( flash8_t *ctx ) {   
    return flash8_set_feature( ctx, FLASH8_FEATURE_A0, FLASH8_SET_BL_ALL_UNLOCKED );
}

err_t flash8_protect_execute ( flash8_t *ctx, uint32_t row_address, uint8_t *feature_status_out ) {
    uint8_t tx_buf[ 4 ];
    
    row_address &= FLASH8_ROW_ADDR_18_BIT_MASK;

    tx_buf[ 0 ] = FLASH8_CMD_PROTECT_EXECUTE;
    tx_buf[ 1 ] = ( uint8_t ) ( row_address >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( row_address >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) row_address;
    

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    flash8_get_feature( ctx, FLASH8_FEATURE_C0, feature_status_out );
    
    return error_flag;
}

err_t flash8_read_id ( flash8_t *ctx, uint8_t *manufacture_id, uint8_t *device_id, uint8_t *organization_id ) {
    uint8_t rx_buf[ 3 ];
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = FLASH8_CMD_READ_ID;
    tx_buf[ 1 ] = DUMMY;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    *manufacture_id = rx_buf[ 0 ];
    *device_id= rx_buf[ 1 ];
    *organization_id = rx_buf[ 2 ];

    return error_flag;
}

err_t flash8_write_memory ( flash8_t *ctx, uint32_t row_address, uint16_t column_address, uint8_t *data_in, uint16_t len, uint8_t *feature_status_out ) {
    uint8_t tx_buf[ 2048 ];
    
    row_address &= FLASH8_ROW_ADDR_18_BIT_MASK;
    column_address &= FLASH8_COLUMN_ADDR_13_BIT_MASK;
    
    err_t error_flag = flash8_write_enable( ctx );
    
    tx_buf[ 0 ] = FLASH8_CMD_PROGRAM_LOAD;
    tx_buf[ 1 ] = ( uint8_t ) ( column_address >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) column_address;
    for ( uint16_t cnt = 0; cnt < len; cnt++ ) {
        tx_buf[ cnt + 3 ] = data_in[ cnt ];
    }
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, len + 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    error_flag |= flash8_program_execute ( ctx, row_address );
    
    error_flag |= flash8_get_feature( ctx, FLASH8_FEATURE_C0, feature_status_out );
    
    return error_flag;
}

err_t flash8_read_memory ( flash8_t *ctx, uint32_t row_address, uint16_t column_address, uint8_t *data_out, uint16_t len, uint8_t *feature_status_out ) {
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 4 ];
    
    row_address &= FLASH8_ROW_ADDR_18_BIT_MASK;
    column_address &= FLASH8_COLUMN_ADDR_13_BIT_MASK;

    tx_buf[ 0 ] = FLASH8_CMD_READ_CELL_ARRAY;
    tx_buf[ 1 ] = ( uint8_t ) ( row_address >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( row_address >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) row_address;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    tx_buf[ 0 ] = FLASH8_CMD_GET_FEATURE;
    tx_buf[ 1 ] = FLASH8_FEATURE_C0;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, tx_buf, 2, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    *feature_status_out =rx_buf[ 0 ];
    
    tx_buf[ 0 ] = FLASH8_CMD_READ_BUFFER;
    tx_buf[ 1 ] = ( uint8_t ) ( column_address >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) column_address;
    tx_buf[ 3 ] = DUMMY;

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}


// ------------------------------------------------------------------------- END
