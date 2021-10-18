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
 * @file eeprom7.c
 * @brief EEPROM 7 Click Driver.
 */

#include "eeprom7.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void eeprom7_cfg_setup ( eeprom7_cfg_t *cfg ) {
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

err_t eeprom7_init ( eeprom7_t *ctx, eeprom7_cfg_t *cfg ) {
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

    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_init( &ctx->hld, cfg->hld );
    
    return SPI_MASTER_SUCCESS;
}

err_t eeprom7_default_cfg ( eeprom7_t *ctx ) {
    eeprom7_enable_write_protect(ctx,  1 );
    eeprom7_send_cmd( ctx, EEPROM7_OPCODE_STATUS_WREN );
    eeprom7_set_status( ctx, 0x00 );
    eeprom7_enable_hold_operation( ctx, 1 );
    return EEPROM7_OK;
}

err_t eeprom7_generic_write ( eeprom7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
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

err_t eeprom7_generic_read ( eeprom7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t eeprom7_generic_write_then_read ( eeprom7_t *ctx, uint8_t *data_in, uint8_t len_in, uint8_t *data_out, uint8_t len_out ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_in, len_in, data_out, len_out );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void eeprom7_enable_write_protect ( eeprom7_t *ctx, uint8_t en_write_protect ) {
    digital_out_write( &ctx->wp, en_write_protect );
}

void eeprom7_enable_hold_operation ( eeprom7_t *ctx, uint8_t en_hold ) {
    digital_out_write( &ctx->hld, en_hold );
}

void eeprom7_enable_write ( eeprom7_t *ctx, uint8_t en_write ) {
    uint8_t tx_data;
    
    if ( en_write == EEPROM7_SEC_WRITE_ENABLE ) {
        tx_data = EEPROM7_OPCODE_STATUS_WREN;
    } else {
        tx_data = EEPROM7_OPCODE_STATUS_WRDI;
    }
    
    eeprom7_generic_write( ctx, tx_data, NULL, 0 );
}

uint16_t eeprom7_read_status ( eeprom7_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint16_t status;
    
    eeprom7_generic_read( ctx, EEPROM7_OPCODE_STATUS_RDSR, rx_buf, 2 );
    
    status = rx_buf[ 0 ];
    status <<= 8;
    status |= rx_buf[ 1 ];
    
    return status;
}

uint8_t eeprom7_is_device_ready ( eeprom7_t *ctx ) {
    uint16_t status;
    uint8_t is_ready;
    
    status = eeprom7_read_status( ctx );
    
    is_ready = ( ( uint8_t ) status ) & 0x01;
    
    return is_ready;
}

err_t eeprom7_send_cmd ( eeprom7_t *ctx, uint8_t cmd ) {
    uint8_t rx_buf[ 2 ] = { 0 };
    
    if ( cmd == EEPROM7_OPCODE_STATUS_WRBP ) {        
        eeprom7_generic_read( ctx, cmd, rx_buf, 1 );

        return rx_buf[ 0 ];
    } else {        
        eeprom7_generic_write( ctx, cmd, NULL, 0 );

        return EEPROM7_STATUS_SUCCESS;
    }
}

void eeprom7_sw_reset ( eeprom7_t *ctx ) {
    eeprom7_send_cmd( ctx, EEPROM7_OPCODE_SW_RESET_SRST );
}

void eeprom7_set_status ( eeprom7_t *ctx, uint8_t status ) {    
    eeprom7_generic_write( ctx, EEPROM7_OPCODE_STATUS_WRSR, &status, 1 );
}

uint8_t eeprom7_get_status ( eeprom7_t *ctx ) {
    uint8_t rx_buf[ 1 ];

    eeprom7_generic_read( ctx, EEPROM7_OPCODE_STATUS_RDSR, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void eeprom7_write_memory ( eeprom7_t *ctx, uint32_t addr, uint8_t *p_tx_data, uint8_t n_bytes ) {
    uint8_t tx_buf[ 256 ];
    uint8_t n_cnt;

    tx_buf[ 0 ] = ( uint8_t ) addr >> 16;
    tx_buf[ 1 ] = ( uint8_t ) addr >> 8;
    tx_buf[ 2 ] = ( uint8_t ) addr;
    
    for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ ) {
        tx_buf[ n_cnt + 3 ] = p_tx_data[ n_cnt ];
    }
    
    eeprom7_generic_write( ctx, EEPROM7_OPCODE_EEPROM_SECURITY_WRITE, tx_buf, n_bytes + 3 );
}

void eeprom7_read_memory ( eeprom7_t *ctx, uint32_t addr, uint8_t *p_rx_data, uint8_t n_bytes) {
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = EEPROM7_OPCODE_EEPROM_SECURITY_READ;
    tx_buf[ 1 ] = ( uint8_t ) addr >> 16;
    tx_buf[ 2 ] = ( uint8_t ) addr >> 8;
    tx_buf[ 3 ] = ( uint8_t ) addr;
    
    eeprom7_generic_write_then_read( ctx, tx_buf, 4, p_rx_data, n_bytes );
}

err_t eeprom7_check_status ( eeprom7_t *ctx, uint8_t check_bit ) {
    uint8_t status_state;
    uint8_t ret_val;
    
    ret_val = 0;

    status_state = eeprom7_get_status( ctx );

    ret_val = status_state & check_bit;

    if ( ( ret_val == 0x01 ) || ( ret_val == 0x02 ) || ( ret_val == 0x08 ) ) {
        return EEPROM7_STATUS_SUCCESS;
    } else {
        return EEPROM7_STATUS_ERROR;
    }
}

// ------------------------------------------------------------------------- END
