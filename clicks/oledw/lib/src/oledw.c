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
 * @file oledw.c
 * @brief OLED W Click Driver.
 */

#include <stddef.h>
#include "oledw.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OLEDW_DUMMY 0

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
static err_t dev_oledw_spi_master_write( oledw_t *obj, oledw_data_t data_in, oledw_data_mode_t data_mode );

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
static err_t dev_oledw_i2c_master_write( oledw_t *obj, oledw_data_t data_in, oledw_data_mode_t data_mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void oledw_cfg_setup( oledw_cfg_t *cfg ) {
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
    cfg->sel = OLEDW_MASTER_SPI;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t oledw_init( oledw_t *ctx, oledw_cfg_t *cfg ) {
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == OLEDW_MASTER_I2C ) {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
            return OLEDW_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->send = dev_oledw_i2c_master_write;
    } else if ( ctx->master_sel == OLEDW_MASTER_SPI ) {
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
            return  OLEDW_INIT_ERROR;
        }
        
        spi_master_deselect_device( ctx->chip_select );
        spi_master_set_default_write_data( &ctx->spi, OLEDW_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );

        ctx->send = dev_oledw_spi_master_write;
    } else {
        ctx->send = NULL;

        return OLEDW_INVALID_DRIVER_SELECTOR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dc, cfg->dc );

    digital_out_high( &ctx->rst );

    return OLEDW_OK;
}

err_t oledw_send( oledw_t *ctx, oledw_data_t tx_data, oledw_data_mode_t data_mode ) {
    return ctx->send( ctx, tx_data, data_mode );
}

void oledw_default_cfg( oledw_t *ctx ) {
    oledw_send( ctx, OLEDW_DISPLAYOFF, OLEDW_COMMAND );            //  0xAE Set OLED Display Off
    oledw_send( ctx, OLEDW_SETDISPLAYCLOCKDIV, OLEDW_COMMAND );    //  0xD5 Set Display Clock Divide Ratio/Oscillator Frequency
    oledw_send( ctx, 0x80, OLEDW_COMMAND );
    oledw_send( ctx, OLEDW_SETMULTIPLEX, OLEDW_COMMAND );          //  0xA8 Set Multiplex Ratio
    oledw_send( ctx, 0x27, OLEDW_COMMAND );
    oledw_send( ctx, OLEDW_SETDISPLAYOFFSET, OLEDW_COMMAND );      //  0xD3 Set Display Offset
    oledw_send( ctx, 0x00, OLEDW_COMMAND );
    oledw_send( ctx, OLEDW_SETSTARTLINE, OLEDW_COMMAND );          //  0x40 Set Display Start Line
    oledw_send( ctx, OLEDW_CHARGEPUMP, OLEDW_COMMAND );            //  0x8D Set Charge Pump
    oledw_send( ctx, 0x14, OLEDW_COMMAND );                        //  0x14 Enable Charge Pump
    oledw_send( ctx, OLEDW_COMSCANDEC, OLEDW_COMMAND );            //  0xC8 Set COM Output Scan Direction
    oledw_send( ctx, OLEDW_SETCOMPINS, OLEDW_COMMAND );            //  0xDA Set COM Pins Hardware Configuration
    oledw_send( ctx, 0x12, OLEDW_COMMAND );
    oledw_send( ctx, OLEDW_SETCONTRAST, OLEDW_COMMAND );           //  0x81 Set Contrast Control
    oledw_send( ctx, 0xAF, OLEDW_COMMAND );
    oledw_send( ctx, OLEDW_SETPRECHARGE, OLEDW_COMMAND );          //  0xD9 Set Pre-Charge Period
    oledw_send( ctx, 0x25, OLEDW_COMMAND );
    oledw_send( ctx, OLEDW_SETVCOMDETECT, OLEDW_COMMAND );         //  0xDB Set VCOMH Deselect Level
    oledw_send( ctx, 0x20,  OLEDW_COMMAND );
    oledw_send( ctx, OLEDW_DISPLAYALLON_RESUME, OLEDW_COMMAND );   //  0xA4 Set Entire Display On/Off
    oledw_send( ctx, OLEDW_NORMALDISPLAY, OLEDW_COMMAND );         //  0xA6 Set Normal/Inverse Display
    oledw_send( ctx, OLEDW_DISPLAYON, OLEDW_COMMAND );             //  0xAF Set OLED Display On
}

void oledw_set_page( oledw_t *ctx, oledw_data_t page_addr ) {
    oledw_send( ctx, page_addr | 0xB0, OLEDW_COMMAND );
}

void oledw_set_column( oledw_t *ctx, oledw_data_t col_addr ) {
    oledw_send( ctx, (col_addr >> 4) | 0x10, OLEDW_COMMAND );
    oledw_send( ctx, col_addr & 0x0F,        OLEDW_COMMAND );
}

void oledw_display_picture( oledw_t *ctx, oledw_resources_t *pic ) {
    uint8_t i;
    uint8_t j;

    for (i = 0x00; i < 0x05; i++) {
        oledw_set_page( ctx, i );
        oledw_send( ctx, 0x10, OLEDW_COMMAND );
        oledw_send( ctx, 0x40, OLEDW_COMMAND );

        for (j = 0x00; j < 0x60; j++) {
            oledw_send( ctx, pic[ i * 0x60 + j ], OLEDW_DATA );
        }
    }
}

void oledw_set_contrast( oledw_t *ctx, oledw_data_t value ) {
    oledw_send( ctx, OLEDW_SETCONTRAST, OLEDW_COMMAND );    //  0x81 Set Contrast Control
    oledw_send( ctx, value,              OLEDW_COMMAND );   //  Contrast Step 0 to 255
}

void oledw_scroll_right( oledw_t *ctx, oledw_data_t start_page_addr, oledw_data_t end_page_addr ) {
    oledw_send( ctx, OLEDW_RIGHT_HORIZONTAL_SCROLL, OLEDW_COMMAND );    //  0x26 Right Horizontal scroll
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                             //  Dummy byte
    oledw_send( ctx, start_page_addr, OLEDW_COMMAND );                  //  Define start page address
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                             //  Set time interval between each scroll
    oledw_send( ctx, end_page_addr, OLEDW_COMMAND );                    //  Define end page address
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                             //  Dummy byte
    oledw_send( ctx, 0xFF, OLEDW_COMMAND );                             //  Dummy byte
    oledw_send( ctx, OLEDW_ACTIVATE_SCROLL, OLEDW_COMMAND );            //  0x2F Activate scroll
}

void oledw_scroll_left( oledw_t *ctx, oledw_data_t start_page_addr, oledw_data_t end_page_addr ) {
    oledw_send( ctx, OLEDW_LEFT_HORIZONTAL_SCROLL, OLEDW_COMMAND );   //  0x27 Left Horizontal scroll
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                           //  Dummy byte
    oledw_send( ctx, start_page_addr, OLEDW_COMMAND );                //  Define start page address
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                           //  Set time interval between each scroll
    oledw_send( ctx, end_page_addr, OLEDW_COMMAND );                  //  Define end page address
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                           //  Dummy byte
    oledw_send( ctx, 0xFF, OLEDW_COMMAND );                           //  Dummy byte
    oledw_send( ctx, OLEDW_ACTIVATE_SCROLL, OLEDW_COMMAND );          //  0x2F Activate scroll
}

void oledw_scroll_diag_right( oledw_t *ctx, oledw_data_t start_page_addr, oledw_data_t end_page_addr ) {
    oledw_send( ctx, OLEDW_SET_VERTICAL_SCROLL_AREA, OLEDW_COMMAND );               //  0xA3 Set Vertical Scroll Area
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                                         //  Set No. of rows in top fixed area
    oledw_send( ctx, OLEDW_LCDHEIGHT, OLEDW_COMMAND );                              //  Set No. of rows in scroll area
    oledw_send( ctx, OLEDW_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL, OLEDW_COMMAND );   //  0x29 Vertical and Right Horizontal Scroll
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                                         //  Dummy byte
    oledw_send( ctx, start_page_addr, OLEDW_COMMAND );                              //  Define start page address
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                                         //  Set time interval between each scroll
    oledw_send( ctx, end_page_addr, OLEDW_COMMAND );                                //  Define end page address
    oledw_send( ctx, 0x01, OLEDW_COMMAND );                                         //  Vertical scrolling offset
    oledw_send( ctx, OLEDW_ACTIVATE_SCROLL, OLEDW_COMMAND );                        //  0x2F Activate scroll
}

void oledw_scroll_diag_left( oledw_t *ctx, oledw_data_t start_page_addr, oledw_data_t end_page_addr ) {
    oledw_send( ctx, OLEDW_SET_VERTICAL_SCROLL_AREA, OLEDW_COMMAND );               //  0xA3 Set Vertical Scroll Area
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                                         //  Set No. of rows in top fixed area
    oledw_send( ctx, OLEDW_LCDHEIGHT, OLEDW_COMMAND );                              //  Set No. of rows in scroll area
    oledw_send( ctx, OLEDW_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL, OLEDW_COMMAND );    //  0x2A Vertical and Left Horizontal Scroll
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                                         //  Dummy byte
    oledw_send( ctx, start_page_addr, OLEDW_COMMAND );                              //  Define start page address
    oledw_send( ctx, 0x00, OLEDW_COMMAND );                                         //  Set time interval between each scroll
    oledw_send( ctx, end_page_addr, OLEDW_COMMAND );                                //  Define end page address
    oledw_send( ctx, 0x01, OLEDW_COMMAND );                                         //  Vertical scrolling offset
    oledw_send( ctx, OLEDW_ACTIVATE_SCROLL, OLEDW_COMMAND );                        //  0x2F Activate scroll
}

void oledw_stop_scroll( oledw_t *ctx ) {
    oledw_send( ctx, 0x2E, OLEDW_COMMAND );   //  0x2E Deactivate scroll
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static err_t dev_oledw_spi_master_write( oledw_t *obj, oledw_data_t data_in, oledw_data_mode_t data_mode ) {
    if (data_mode == OLEDW_COMMAND) {
        digital_out_low( &obj->dc );
    } else if (data_mode == OLEDW_DATA) {
        digital_out_high( &obj->dc );
    } else {
        return OLEDW_INVALID_DATA_MODE;
    }

    spi_master_select_device( obj->chip_select );
    spi_master_write( &obj->spi, &data_in, 1 );
    spi_master_deselect_device( obj->chip_select ); 

    return OLEDW_OK;
}

static err_t dev_oledw_i2c_master_write( oledw_t *obj, oledw_data_t data_in, oledw_data_mode_t data_mode ) {
    uint8_t tx_buffer[ 2 ];

    if (data_mode == OLEDW_COMMAND) {
        digital_out_low( &obj->dc );
        tx_buffer[ 0 ] = 0b0000000;
    } else if (data_mode == OLEDW_DATA) {
        digital_out_high( &obj->dc );
        tx_buffer[ 0 ] = 0b1100000;
    } else {
        return OLEDW_INVALID_DATA_MODE;
    }

    tx_buffer[ 1 ] = data_in;

    i2c_master_set_slave_address( &obj->i2c, data_mode );
    i2c_master_write( &obj->i2c, tx_buffer, 2 );    

    return OLEDW_OK;
}


// ------------------------------------------------------------------------ END
