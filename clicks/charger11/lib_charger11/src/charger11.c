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
 * @file charger11.c
 * @brief Charger 11 Click Driver.
 */

#include "charger11.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

void charger11_cfg_setup ( charger11_cfg_t *cfg ) {
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->lr   = HAL_PIN_NC;
    cfg->lg = HAL_PIN_NC;
    cfg->st = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER11_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

}

err_t charger11_init ( charger11_t *ctx, charger11_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;
    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
        return I2C_MASTER_ERROR;
    }
    
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
    
    digital_out_init( &ctx->lr, cfg->lr );
    digital_out_init( &ctx->lg, cfg->lg );

    digital_in_init( &ctx->st, cfg->st );

    digital_out_low( &ctx->lr );
    digital_out_low( &ctx->lg );

    return 0;
}

err_t charger11_i2c_write ( charger11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

err_t charger11_i2c_read ( charger11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t charger11_spi_write ( charger11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
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

err_t charger11_spi_read ( charger11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

uint8_t charger11_get_int( charger11_t *ctx ) {
    return digital_in_read( &ctx->st );
}

void charger11_lr_set( charger11_t *ctx, uint8_t pin_state ) {
    if ( pin_state == CHARGER11_PIN_ENABE ) {
        digital_out_high( &ctx->lr );
    } else {
        digital_out_low( &ctx->lr );
    }
}

void charger11_lg_set( charger11_t *ctx, uint8_t pin_state ) {
    if ( pin_state == CHARGER11_PIN_ENABE ) {
        digital_out_high( &ctx->lg );
    } else {
        digital_out_low( &ctx->lg );
    }
}

void charger11_spi_transfer( charger11_t *ctx, uint8_t *data_in, uint8_t *data_out, 
                             uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) {
        
        spi_master_set_default_write_data( &ctx->spi, data_in[ cnt ] );
        spi_master_read( &ctx->spi, &data_out[ cnt ], 1 );
        spi_master_set_default_write_data( &ctx->spi, DUMMY );
    }
    spi_master_deselect_device( ctx->chip_select );
}

void charger11_spi_set_register( charger11_t *ctx, uint8_t register_address, 
                                 uint16_t register_value ) {
    uint8_t tx_buf[2];

    tx_buf[0] = register_address;
    tx_buf[0] <<= 4;
    tx_buf[0] &= 0xF0;
    tx_buf[0] |= 0x02;
    
    register_value &= 0x03FF;
    
    tx_buf[0] |= (uint8_t)(register_value >> 8);
    
    tx_buf[1] = (uint8_t)(register_value);

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

void charger11_spi_get_register( charger11_t *ctx, uint8_t register_address, 
                                 uint16_t *register_value ) {
    uint8_t tx_buf[2];
    uint8_t rx_buf[2];

    tx_buf[0] = register_address;
    tx_buf[0] <<= 4;
    tx_buf[0] &= 0xF0;
    tx_buf[0] |= 0x0E;

    tx_buf[1] = 0xFF;

    charger11_spi_transfer( ctx, tx_buf, rx_buf, 2 );

    *register_value = 0;
    *register_value = ( uint16_t ) rx_buf[0];
    *register_value <<= 8;
    *register_value |= ( uint16_t ) rx_buf[1];
    
    *register_value &= 0x03FF;
}

void charger11_spi_increment_wiper( charger11_t *ctx ) {
    uint8_t tx_buf[1];

    tx_buf[0] = 0x04;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void charger11_spi_decrement_wiper( charger11_t *ctx ) {
    uint8_t tx_buf[1];

    tx_buf[0] = 0x08;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t charger11_spi_get_wiper_position( charger11_t *ctx ) {
    uint16_t rx_buf;

    charger11_spi_get_register( ctx, 0x00, &rx_buf );

    return (uint8_t) rx_buf;
}

uint16_t charger11_i2c_get_rawData( charger11_t *ctx ) {
    uint8_t rx_buf[2];

    uint16_t aux_value;
    
    rx_buf[0] = 0x00;
    rx_buf[1] = 0x00;

    i2c_master_read( &ctx->i2c, rx_buf, 2 );
    
    aux_value = 0;
    aux_value |= rx_buf[0];
    aux_value <<= 8;
    aux_value |= rx_buf[1];
    
    return aux_value;
}

float charger11_i2c_get_volt( charger11_t *ctx, float reference_voltage ) {
    uint8_t rx_buf[2];

    uint16_t aux_value;
    float aux_voltage;

    rx_buf[0] = 0x00;
    rx_buf[1] = 0x00;

    i2c_master_read( &ctx->i2c, rx_buf, 2 );
    
    aux_value = 0;
    aux_value |= rx_buf[0];
    aux_value <<= 8;
    aux_value |= rx_buf[1];

    aux_voltage = reference_voltage * aux_value;
    aux_voltage /= 4096.0;

    return aux_voltage;
}


// ------------------------------------------------------------------------ END
