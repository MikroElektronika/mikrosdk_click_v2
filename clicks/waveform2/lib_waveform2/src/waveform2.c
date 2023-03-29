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
 * @file waveform2.c
 * @brief Waveform 2 Click Driver.
 */

#include "waveform2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

// --------------------------------------------------------- PRIVATE FUNCTIONS 

/**
 * @brief Dev delay function.
 * @details 10 ms delay function.
 */
void dev_delay( void );

/**
 * @brief Dev double command function.
 * @details Function used for sending two commands at the same time.
 */
void waveform2_double_cmd ( waveform2_t *ctx, uint16_t cmd1, uint16_t cmd2 );

// --------------------------------------------------------- PUBLIC FUNCTIONS

void waveform2_cfg_setup ( waveform2_cfg_t *cfg ) {
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = WAVEFORM2_DEVICE_SLAVE_ADDR_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t waveform2_init ( waveform2_t *ctx, waveform2_cfg_t *cfg ) {
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );
 
    ctx->mode_output = OUTPUT_TRIANGLE;
    
    return 0;
}

err_t waveform2_default_cfg ( waveform2_t *ctx ) {
    digital_out_low( &ctx->rst );
    waveform2_mclk_enable( ctx );
    return WAVEFORM2_OK;
}

err_t waveform2_i2c_write ( waveform2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

err_t waveform2_i2c_read ( waveform2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t waveform2_spi_write ( waveform2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
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

err_t waveform2_spi_read ( waveform2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

uint8_t waveform2_eeprom_read_byte ( waveform2_t *ctx, uint16_t addr ) {
    uint8_t tx_buf[ 2 ];
    uint8_t rx_data;
    
    tx_buf[ 0 ] = ( uint8_t )( addr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) addr;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, &rx_data, 1 );
    
    return rx_data;
}

uint16_t waveform2_eeprom_read_word ( waveform2_t *ctx, uint16_t addr ) {
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint16_t rx_data;

    tx_buf[ 0 ] = ( uint8_t )( addr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) addr;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 2 );

    rx_data = rx_buf[ 0 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 1 ];

    return rx_data;
}

uint32_t waveform2_eeprom_read_long ( waveform2_t *ctx, uint16_t addr ) {
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 4 ];
    uint32_t rx_data;

    tx_buf[ 0 ] = ( uint8_t )( addr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) addr;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 4 );

    rx_data = rx_buf[ 0 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 1 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 2 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 3 ];

    return rx_data;
}

void waveform2_eeprom_read_string ( waveform2_t *ctx, uint16_t addr, uint8_t *data_buf, uint16_t len ) {
    uint16_t cnt;
    
    for ( cnt = 0; cnt < len; cnt++ ) {
        data_buf[ cnt ] = waveform2_eeprom_read_byte( ctx, addr + cnt );
        dev_delay( );
    }
}

void waveform2_eeprom_write_byte ( waveform2_t *ctx, uint16_t addr, uint8_t tx_data ) {
    uint8_t tx_buf[ 3 ];

    tx_buf[ 0 ] = ( uint8_t )( addr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) addr;
    tx_buf[ 2 ] = tx_data;
    
    i2c_master_write( &ctx->i2c, tx_buf, 3 );
}

void waveform2_eeprom_write_word ( waveform2_t *ctx, uint16_t addr, uint16_t tx_data ) {
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = ( uint8_t )( addr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) addr;
    tx_buf[ 2 ] = ( uint8_t )( tx_data >> 8 );
    tx_buf[ 3 ] = ( uint8_t )( tx_data );
}

void waveform2_eeprom_write_long ( waveform2_t *ctx, uint16_t addr, uint32_t tx_data ) {
    uint8_t tx_buf[ 6 ];

    tx_buf[ 0 ] = ( uint8_t )( addr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) addr;
    tx_buf[ 2 ] = ( uint8_t )( tx_data >> 24 );
    tx_buf[ 3 ] = ( uint8_t )( tx_data >> 16 );
    tx_buf[ 4 ] = ( uint8_t )( tx_data >> 8 );
    tx_buf[ 5 ] = ( uint8_t )( tx_data );

    i2c_master_write( &ctx->i2c, tx_buf, 6 );
}

void waveform2_eeprom_write_string ( waveform2_t *ctx, uint16_t addr, uint8_t *data_buf, uint16_t len  ) {
    uint16_t cnt;
    
    for ( cnt = 0; cnt < len; cnt++ ) {
        waveform2_eeprom_write_byte( ctx, addr + cnt, data_buf[ cnt ] );
        dev_delay( );
    }
}

void waveform2_mclk_enable ( waveform2_t *ctx ) {
    digital_out_high( &ctx->en );
}

void waveform2_mclk_disable ( waveform2_t *ctx ) {
    digital_out_low( &ctx->en );
}

void waveform2_hw_reset ( waveform2_t *ctx ) {
    digital_out_high( &ctx->rst );
    dev_delay( );
    digital_out_low( &ctx->rst );
    dev_delay( );
}

void waveform2_set_freq ( waveform2_t *ctx, uint32_t freq ) {
    uint16_t freq0_14bits;
    uint16_t freq1_14bits;

    freq1_14bits = (uint16_t)( freq & 0x7FFF );
    freq0_14bits = (uint16_t)( freq >> 14 ) & 0x7FFF;

    waveform2_double_cmd( ctx, 0x0000, freq1_14bits | 0x8000 );
    waveform2_double_cmd( ctx, 0x1000, freq0_14bits | 0x4000 );
    
    if ( ctx->mode_output == OUTPUT_TRIANGLE ) {
        waveform2_triangle_output( ctx );
    } else {
        waveform2_sine_output( ctx );
    }
}

void waveform2_configuration ( waveform2_t *ctx, uint16_t cfg ) {
    uint8_t tx_data[ 2 ];
    
    tx_data[ 0 ] = ( uint8_t )( cfg >> 8 );
    tx_data[ 1 ] = ( uint8_t )( cfg );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_data, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

void waveform2_sine_output ( waveform2_t *ctx ) {
    waveform2_configuration( ctx, 0 );
    ctx->mode_output = OUTPUT_SINUSOID;
}

void waveform2_triangle_output ( waveform2_t *ctx ) {
    waveform2_configuration( ctx, WAVEFORM2_CFG_MODE_MSK | WAVEFORM2_CFG_B28_MSK );
    ctx->mode_output = OUTPUT_TRIANGLE;
}

void waveform2_output_off ( waveform2_t *ctx ) {
    waveform2_configuration( ctx, WAVEFORM2_CFG_SLEEP1_MSK | WAVEFORM2_CFG_SLEEP12_MSK );
    ctx->mode_output = OUTPUT_SINUSOID;
}

// --------------------------------------------------------- PRIVATE FUNCTIONS 

void dev_delay( void ) { 
    Delay_10ms( );
}

void waveform2_double_cmd ( waveform2_t *ctx, uint16_t cmd1, uint16_t cmd2 ) {
    uint8_t tx_buf_cmd[ 4 ];

    tx_buf_cmd[ 0 ] = ( uint8_t )( cmd1 >> 8 );
    tx_buf_cmd[ 1 ] = ( uint8_t )( cmd1 );
    tx_buf_cmd[ 2 ] = ( uint8_t )( cmd2 >> 8 );
    tx_buf_cmd[ 3 ] = ( uint8_t )( cmd2 );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf_cmd[0], 2 );
    spi_master_write( &ctx->spi, &tx_buf_cmd[2], 2 );
    spi_master_deselect_device( ctx->chip_select );
}

// ------------------------------------------------------------------------ END
