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
 * @file oledb.c
 * @brief OLED B Click Driver.
 */

#include <stddef.h>
#include "oledb.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OLEDB_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief SPI Master Write function.
 * @details This function executes data writing by using SPI driver.
 * @param[in] obj  Click object.
 * @param[in] data_in  Data to be sent.
 * @param[in] data_mode  0x3C - Command,
 *                       0x3D - Data.
 *
 * @returns 0x00 - Ok,
 *          0xFE - Invalid data mode.
 */
static err_t dev_oledb_spi_master_write( oledb_t *obj, oledb_data_t data_in, oledb_data_mode_t data_mode );

/**
 * @brief I2C Master Write function.
 * @details This function executes data writing by using I2C driver.
 * @param[in] obj  Click object.
 * @param[in] data_in  Data to be sent.
 * @param[in] data_mode  0x3C - Command,
 *                       0x3D - Data.
 *
 * @returns 0x00 - Ok,
 *          0xFE - Invalid data mode.
 */
static err_t dev_oledb_i2c_master_write( oledb_t *obj, oledb_data_t data_in, oledb_data_mode_t data_mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void oledb_cfg_setup( oledb_cfg_t *cfg ) {
    cfg->rst = HAL_PIN_NC;
    cfg->dc  = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->sdi = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x00;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->sel = OLEDB_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t oledb_init( oledb_t *ctx, oledb_cfg_t *cfg ) {
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == OLEDB_MASTER_I2C ) {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
            return OLEDB_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->send = dev_oledb_i2c_master_write;
    } else if ( ctx->master_sel == OLEDB_MASTER_SPI ) {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->sdi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
            return  OLEDB_INIT_ERROR;
        }
        
        spi_master_deselect_device( ctx->chip_select );
        spi_master_set_default_write_data( &ctx->spi, OLEDB_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );

        ctx->send = dev_oledb_spi_master_write;
    } else {
        ctx->send = NULL;

        return OLEDB_INVALID_DRIVER_SELECTOR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dc, cfg->dc );

    digital_out_high( &ctx->rst );

    return OLEDB_OK;
}

err_t oledb_send( oledb_t *ctx, oledb_data_t tx_data, oledb_data_mode_t data_mode ) {
    return ctx->send( ctx, tx_data, data_mode );
}

void oledb_default_cfg( oledb_t *ctx ) {
    oledb_send( ctx, OLEDB_DISPLAYOFF, OLEDB_COMMAND );            //  0xAE Set OLED Display Off
    oledb_send( ctx, OLEDB_SETDISPLAYCLOCKDIV, OLEDB_COMMAND );    //  0xD5 Set Display Clock Divide Ratio/Oscillator Frequency
    oledb_send( ctx, 0x80, OLEDB_COMMAND );
    oledb_send( ctx, OLEDB_SETMULTIPLEX, OLEDB_COMMAND );          //  0xA8 Set Multiplex Ratio
    oledb_send( ctx, 0x27, OLEDB_COMMAND );
    oledb_send( ctx, OLEDB_SETDISPLAYOFFSET, OLEDB_COMMAND );      //  0xD3 Set Display Offset
    oledb_send( ctx, 0x00, OLEDB_COMMAND );
    oledb_send( ctx, OLEDB_SETSTARTLINE, OLEDB_COMMAND );          //  0x40 Set Display Start Line
    oledb_send( ctx, OLEDB_CHARGEPUMP, OLEDB_COMMAND );            //  0x8D Set Charge Pump
    oledb_send( ctx, 0x14, OLEDB_COMMAND );                        //  0x14 Enable Charge Pump
    oledb_send( ctx, OLEDB_COMSCANDEC, OLEDB_COMMAND );            //  0xC8 Set COM Output Scan Direction
    oledb_send( ctx, OLEDB_SETCOMPINS, OLEDB_COMMAND );            //  0xDA Set COM Pins Hardware Configuration
    oledb_send( ctx, 0x12, OLEDB_COMMAND );
    oledb_send( ctx, OLEDB_SETCONTRAST, OLEDB_COMMAND );           //  0x81 Set Contrast Control
    oledb_send( ctx, 0xAF, OLEDB_COMMAND );
    oledb_send( ctx, OLEDB_SETPRECHARGE, OLEDB_COMMAND );          //  0xD9 Set Pre-Charge Period
    oledb_send( ctx, 0x25, OLEDB_COMMAND );
    oledb_send( ctx, OLEDB_SETVCOMDETECT, OLEDB_COMMAND );         //  0xDB Set VCOMH Deselect Level
    oledb_send( ctx, 0x20,  OLEDB_COMMAND );
    oledb_send( ctx, OLEDB_DISPLAYALLON_RESUME, OLEDB_COMMAND );   //  0xA4 Set Entire Display On/Off
    oledb_send( ctx, OLEDB_NORMALDISPLAY, OLEDB_COMMAND );         //  0xA6 Set Normal/Inverse Display
    oledb_send( ctx, OLEDB_DISPLAYON, OLEDB_COMMAND );             //  0xAF Set OLED Display On
}

void oledb_set_page( oledb_t *ctx, oledb_data_t page_addr ) {
    oledb_send( ctx, page_addr | 0xB0, OLEDB_COMMAND );
}

void oledb_set_column( oledb_t *ctx, oledb_data_t col_addr ) {
    oledb_send( ctx, (col_addr >> 4) | 0x10, OLEDB_COMMAND );
    oledb_send( ctx, col_addr & 0x0F,        OLEDB_COMMAND );
}

void oledb_display_picture( oledb_t *ctx, oledb_resources_t *pic ) {
    uint8_t i;
    uint8_t j;

    for (i = 0x00; i < 0x05; i++) {
        oledb_set_page( ctx, i );
        oledb_send( ctx, 0x10, OLEDB_COMMAND );
        oledb_send( ctx, 0x40, OLEDB_COMMAND );

        for (j = 0x00; j < 0x60; j++) {
            oledb_send( ctx, pic[ i * 0x60 + j ], OLEDB_DATA );
        }
    }
}

void oledb_set_contrast( oledb_t *ctx, oledb_data_t value ) {
    oledb_send( ctx, OLEDB_SETCONTRAST, OLEDB_COMMAND );    //  0x81 Set Contrast Control
    oledb_send( ctx, value,              OLEDB_COMMAND );   //  Contrast Step 0 to 255
}

void oledb_scroll_right( oledb_t *ctx, oledb_data_t start_page_addr, oledb_data_t end_page_addr ) {
    oledb_send( ctx, OLEDB_RIGHT_HORIZONTAL_SCROLL, OLEDB_COMMAND );    //  0x26 Right Horizontal scroll
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                             //  Dummy byte
    oledb_send( ctx, start_page_addr, OLEDB_COMMAND );                  //  Define start page address
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                             //  Set time interval between each scroll
    oledb_send( ctx, end_page_addr, OLEDB_COMMAND );                    //  Define end page address
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                             //  Dummy byte
    oledb_send( ctx, 0xFF, OLEDB_COMMAND );                             //  Dummy byte
    oledb_send( ctx, OLEDB_ACTIVATE_SCROLL, OLEDB_COMMAND );            //  0x2F Activate scroll
}

void oledb_scroll_left( oledb_t *ctx, oledb_data_t start_page_addr, oledb_data_t end_page_addr ) {
    oledb_send( ctx, OLEDB_LEFT_HORIZONTAL_SCROLL, OLEDB_COMMAND );   //  0x27 Left Horizontal scroll
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                           //  Dummy byte
    oledb_send( ctx, start_page_addr, OLEDB_COMMAND );                //  Define start page address
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                           //  Set time interval between each scroll
    oledb_send( ctx, end_page_addr, OLEDB_COMMAND );                  //  Define end page address
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                           //  Dummy byte
    oledb_send( ctx, 0xFF, OLEDB_COMMAND );                           //  Dummy byte
    oledb_send( ctx, OLEDB_ACTIVATE_SCROLL, OLEDB_COMMAND );          //  0x2F Activate scroll
}

void oledb_scroll_diag_right( oledb_t *ctx, oledb_data_t start_page_addr, oledb_data_t end_page_addr ) {
    oledb_send( ctx, OLEDB_SET_VERTICAL_SCROLL_AREA, OLEDB_COMMAND );               //  0xA3 Set Vertical Scroll Area
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                                         //  Set No. of rows in top fixed area
    oledb_send( ctx, OLEDB_LCDHEIGHT, OLEDB_COMMAND );                              //  Set No. of rows in scroll area
    oledb_send( ctx, OLEDB_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL, OLEDB_COMMAND );   //  0x29 Vertical and Right Horizontal Scroll
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                                         //  Dummy byte
    oledb_send( ctx, start_page_addr, OLEDB_COMMAND );                              //  Define start page address
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                                         //  Set time interval between each scroll
    oledb_send( ctx, end_page_addr, OLEDB_COMMAND );                                //  Define end page address
    oledb_send( ctx, 0x01, OLEDB_COMMAND );                                         //  Vertical scrolling offset
    oledb_send( ctx, OLEDB_ACTIVATE_SCROLL, OLEDB_COMMAND );                        //  0x2F Activate scroll
}

void oledb_scroll_diag_left( oledb_t *ctx, oledb_data_t start_page_addr, oledb_data_t end_page_addr ) {
    oledb_send( ctx, OLEDB_SET_VERTICAL_SCROLL_AREA, OLEDB_COMMAND );               //  0xA3 Set Vertical Scroll Area
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                                         //  Set No. of rows in top fixed area
    oledb_send( ctx, OLEDB_LCDHEIGHT, OLEDB_COMMAND );                              //  Set No. of rows in scroll area
    oledb_send( ctx, OLEDB_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL, OLEDB_COMMAND );    //  0x2A Vertical and Left Horizontal Scroll
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                                         //  Dummy byte
    oledb_send( ctx, start_page_addr, OLEDB_COMMAND );                              //  Define start page address
    oledb_send( ctx, 0x00, OLEDB_COMMAND );                                         //  Set time interval between each scroll
    oledb_send( ctx, end_page_addr, OLEDB_COMMAND );                                //  Define end page address
    oledb_send( ctx, 0x01, OLEDB_COMMAND );                                         //  Vertical scrolling offset
    oledb_send( ctx, OLEDB_ACTIVATE_SCROLL, OLEDB_COMMAND );                        //  0x2F Activate scroll
}

void oledb_stop_scroll( oledb_t *ctx ) {
    oledb_send( ctx, 0x2E, OLEDB_COMMAND );   //  0x2E Deactivate scroll
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static err_t dev_oledb_spi_master_write( oledb_t *obj, oledb_data_t data_in, oledb_data_mode_t data_mode ) {
    if (data_mode == OLEDB_COMMAND) {
        digital_out_low( &obj->dc );
    } else if (data_mode == OLEDB_DATA) {
        digital_out_high( &obj->dc );
    } else {
        return OLEDB_INVALID_DATA_MODE;
    }

    spi_master_select_device( obj->chip_select );
    spi_master_write( &obj->spi, &data_in, 1 );
    spi_master_deselect_device( obj->chip_select ); 

    return OLEDB_OK;
}

static err_t dev_oledb_i2c_master_write( oledb_t *obj, oledb_data_t data_in, oledb_data_mode_t data_mode ) {
    uint8_t tx_buffer[ 2 ];

    if (data_mode == OLEDB_COMMAND) {
        digital_out_low( &obj->dc );
        tx_buffer[ 0 ] = 0b0000000;
    } else if (data_mode == OLEDB_DATA) {
        digital_out_high( &obj->dc );
        tx_buffer[ 0 ] = 0b1100000;
    } else {
        return OLEDB_INVALID_DATA_MODE;
    }

    tx_buffer[ 1 ] = data_in;

    i2c_master_set_slave_address( &obj->i2c, data_mode );
    i2c_master_write( &obj->i2c, tx_buffer, 2 );    

    return OLEDB_OK;
}


// ------------------------------------------------------------------------ END
