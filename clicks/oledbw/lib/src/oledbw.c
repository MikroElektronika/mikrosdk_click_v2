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
 * \file oledbw.c
 *
 */

#include <stddef.h>
#include "oledbw.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OLEDBW_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief SPI Master Write function.
 *
 * @param obj  Click object.
 * @param data_in  Data to be sent.
 * @param data_mode  0x3C - Command,
 *                   0x3D - Data.
 *
 * @returns 0x00 - Ok,
 *          0xFE - Invalid data mode.
 *
 * @description This function executes data writing by using SPI driver.
 */
static OLEDBW_RETVAL
oledbw_spi_master_write( oledbw_t *obj, oledbw_data_t data_in,
                         oledbw_data_mode_t data_mode );

/**
 * @brief I2C Master Write function.
 *
 * @param obj  Click object.
 * @param data_in  Data to be sent.
 * @param data_mode  0x3C - Command,
 *                   0x3D - Data.
 *
 * @returns 0x00 - Ok,
 *          0xFE - Invalid data mode.
 *
 * @description This function executes data writing by using I2C driver.
 */
static OLEDBW_RETVAL
oledbw_i2c_master_write( oledbw_t *obj, oledbw_data_t data_in,
                         oledbw_data_mode_t data_mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
oledbw_cfg_setup( oledbw_cfg_t *cfg )
{
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
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_mode = SPI_MASTER_MODE_0;

    cfg->sel = OLEDBW_MASTER_SPI;
}

OLEDBW_RETVAL
oledbw_init( oledbw_t *ctx, oledbw_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == OLEDBW_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return OLEDBW_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->send = oledbw_i2c_master_write;
    }
    else if ( ctx->master_sel == OLEDBW_MASTER_SPI )
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->sdi;
        
        spi_cfg.default_write_data = ${NAME_UPPERCASE}_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  OLEDBW_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, OLEDBW_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->send = oledbw_spi_master_write;
    }
    else
    {
        ctx->send = NULL;

        return OLEDBW_INVALID_DRIVER_SELECTOR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dc, cfg->dc );

    digital_out_high( &ctx->rst );

    return OLEDBW_OK;
}

OLEDBW_RETVAL
oledbw_send( oledbw_t *ctx, oledbw_data_t tx_data,
             oledbw_data_mode_t data_mode )
{
    return ctx->send( ctx, tx_data, data_mode );
}

void
oledbw_default_cfg( oledbw_t *ctx )
{
    oledbw_send( ctx, OLEDBW_DISPLAYOFF,          OLEDBW_COMMAND );   //  0xAE Set OLED Display Off
    oledbw_send( ctx, OLEDBW_SETDISPLAYCLOCKDIV,  OLEDBW_COMMAND );   //  0xD5 Set Display Clock Divide Ratio/Oscillator Frequency
    oledbw_send( ctx, 0x80,                       OLEDBW_COMMAND );
    oledbw_send( ctx, OLEDBW_SETMULTIPLEX,        OLEDBW_COMMAND );   //  0xA8 Set Multiplex Ratio
    oledbw_send( ctx, 0x27,                       OLEDBW_COMMAND );
    oledbw_send( ctx, OLEDBW_SETDISPLAYOFFSET,    OLEDBW_COMMAND );   //  0xD3 Set Display Offset
    oledbw_send( ctx, 0x00,                       OLEDBW_COMMAND );
    oledbw_send( ctx, OLEDBW_SETSTARTLINE,        OLEDBW_COMMAND );   //  0x40 Set Display Start Line
    oledbw_send( ctx, OLEDBW_CHARGEPUMP,          OLEDBW_COMMAND );   //  0x8D Set Charge Pump
    oledbw_send( ctx, 0x14,                       OLEDBW_COMMAND );   //  0x14 Enable Charge Pump
    oledbw_send( ctx, OLEDBW_COMSCANDEC,          OLEDBW_COMMAND );   //  0xC8 Set COM Output Scan Direction
    oledbw_send( ctx, OLEDBW_SETCOMPINS,          OLEDBW_COMMAND );   //  0xDA Set COM Pins Hardware Configuration
    oledbw_send( ctx, 0x12,                       OLEDBW_COMMAND );
    oledbw_send( ctx, OLEDBW_SETCONTRAST,         OLEDBW_COMMAND );   //  0x81 Set Contrast Control
    oledbw_send( ctx, 0xAF,                       OLEDBW_COMMAND );
    oledbw_send( ctx, OLEDBW_SETPRECHARGE,        OLEDBW_COMMAND );   //  0xD9 Set Pre-Charge Period
    oledbw_send( ctx, 0x25,                       OLEDBW_COMMAND );
    oledbw_send( ctx, OLEDBW_SETVCOMDETECT,       OLEDBW_COMMAND );   //  0xDB Set VCOMH Deselect Level
    oledbw_send( ctx, 0x20,                       OLEDBW_COMMAND );
    oledbw_send( ctx, OLEDBW_DISPLAYALLON_RESUME, OLEDBW_COMMAND );   //  0xA4 Set Entire Display On/Off
    oledbw_send( ctx, OLEDBW_NORMALDISPLAY,       OLEDBW_COMMAND );   //  0xA6 Set Normal/Inverse Display
    oledbw_send( ctx, OLEDBW_DISPLAYON,           OLEDBW_COMMAND );   //  0xAF Set OLED Display On
}

void
oledbw_set_page( oledbw_t *ctx, oledbw_data_t page_addr )
{
    oledbw_send( ctx, page_addr | 0xB0, OLEDBW_COMMAND );
}

void
oledbw_set_column( oledbw_t *ctx, oledbw_data_t col_addr )
{
    oledbw_send( ctx, (col_addr >> 4) | 0x10, OLEDBW_COMMAND );
    oledbw_send( ctx, col_addr & 0x0F,        OLEDBW_COMMAND );
}

void
oledbw_display_picture( oledbw_t *ctx, oledbw_resources_t *pic )
{
    uint8_t i;
    uint8_t j;

    for (i = 0x00; i < 0x05; i++)
    {
        oledbw_set_page( ctx, i );
        oledbw_send( ctx, 0x10, OLEDBW_COMMAND );
        oledbw_send( ctx, 0x40, OLEDBW_COMMAND );

        for (j = 0x00; j < 0x60; j++)
        {
            oledbw_send( ctx, pic[ i * 0x60 + j ], OLEDBW_DATA );
        }
    }
}

void
oledbw_set_contrast( oledbw_t *ctx, oledbw_data_t value )
{
    oledbw_send( ctx, OLEDBW_SETCONTRAST, OLEDBW_COMMAND );   //  0x81 Set Contrast Control
    oledbw_send( ctx, value,              OLEDBW_COMMAND );   //  Contrast Step 0 to 255
}

void
oledbw_scroll_right( oledbw_t *ctx, oledbw_data_t start_page_addr,
                     oledbw_data_t end_page_addr )
{
    oledbw_send( ctx, OLEDBW_RIGHT_HORIZONTAL_SCROLL, OLEDBW_COMMAND );   //  0x26 Right Horizontal scroll
    oledbw_send( ctx, 0x00,                           OLEDBW_COMMAND );   //  Dummy byte
    oledbw_send( ctx, start_page_addr,                OLEDBW_COMMAND );   //  Define start page address
    oledbw_send( ctx, 0x00,                           OLEDBW_COMMAND );   //  Set time interval between each scroll
    oledbw_send( ctx, end_page_addr,                  OLEDBW_COMMAND );   //  Define end page address
    oledbw_send( ctx, 0x00,                           OLEDBW_COMMAND );   //  Dummy byte
    oledbw_send( ctx, 0xFF,                           OLEDBW_COMMAND );   //  Dummy byte
    oledbw_send( ctx, OLEDBW_ACTIVATE_SCROLL,         OLEDBW_COMMAND );   //  0x2F Activate scroll
}

void
oledbw_scroll_left( oledbw_t *ctx, oledbw_data_t start_page_addr,
                    oledbw_data_t end_page_addr )
{
    oledbw_send( ctx, OLEDBW_LEFT_HORIZONTAL_SCROLL, OLEDBW_COMMAND );   //  0x27 Left Horizontal scroll
    oledbw_send( ctx, 0x00,                          OLEDBW_COMMAND );   //  Dummy byte
    oledbw_send( ctx, start_page_addr,               OLEDBW_COMMAND );   //  Define start page address
    oledbw_send( ctx, 0x00,                          OLEDBW_COMMAND );   //  Set time interval between each scroll
    oledbw_send( ctx, end_page_addr,                 OLEDBW_COMMAND );   //  Define end page address
    oledbw_send( ctx, 0x00,                          OLEDBW_COMMAND );   //  Dummy byte
    oledbw_send( ctx, 0xFF,                          OLEDBW_COMMAND );   //  Dummy byte
    oledbw_send( ctx, OLEDBW_ACTIVATE_SCROLL,        OLEDBW_COMMAND );   //  0x2F Activate scroll
}

void
oledbw_scroll_diag_right( oledbw_t *ctx, oledbw_data_t start_page_addr,
                          oledbw_data_t end_page_addr )
{
    oledbw_send( ctx, OLEDBW_SET_VERTICAL_SCROLL_AREA,             OLEDBW_COMMAND );   //  0xA3 Set Vertical Scroll Area
    oledbw_send( ctx, 0x00,                                        OLEDBW_COMMAND );   //  Set No. of rows in top fixed area
    oledbw_send( ctx, OLEDBW_LCDHEIGHT,                            OLEDBW_COMMAND );   //  Set No. of rows in scroll area
    oledbw_send( ctx, OLEDBW_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL, OLEDBW_COMMAND );   //  0x29 Vertical and Right Horizontal Scroll
    oledbw_send( ctx, 0x00,                                        OLEDBW_COMMAND );   //  Dummy byte
    oledbw_send( ctx, start_page_addr,                             OLEDBW_COMMAND );   //  Define start page address
    oledbw_send( ctx, 0x00,                                        OLEDBW_COMMAND );   //  Set time interval between each scroll
    oledbw_send( ctx, end_page_addr,                               OLEDBW_COMMAND );   //  Define end page address
    oledbw_send( ctx, 0x01,                                        OLEDBW_COMMAND );   //  Vertical scrolling offset
    oledbw_send( ctx, OLEDBW_ACTIVATE_SCROLL,                      OLEDBW_COMMAND );   //  0x2F Activate scroll
}

void
oledbw_scroll_diag_left( oledbw_t *ctx, oledbw_data_t start_page_addr,
                         oledbw_data_t end_page_addr )
{
    oledbw_send( ctx, OLEDBW_SET_VERTICAL_SCROLL_AREA,            OLEDBW_COMMAND );   //  0xA3 Set Vertical Scroll Area
    oledbw_send( ctx, 0x00,                                       OLEDBW_COMMAND );   //  Set No. of rows in top fixed area
    oledbw_send( ctx, OLEDBW_LCDHEIGHT,                           OLEDBW_COMMAND );   //  Set No. of rows in scroll area
    oledbw_send( ctx, OLEDBW_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL, OLEDBW_COMMAND );   //  0x2A Vertical and Left Horizontal Scroll
    oledbw_send( ctx, 0x00,                                       OLEDBW_COMMAND );   //  Dummy byte
    oledbw_send( ctx, start_page_addr,                            OLEDBW_COMMAND );   //  Define start page address
    oledbw_send( ctx, 0x00,                                       OLEDBW_COMMAND );   //  Set time interval between each scroll
    oledbw_send( ctx, end_page_addr,                              OLEDBW_COMMAND );   //  Define end page address
    oledbw_send( ctx, 0x01,                                       OLEDBW_COMMAND );   //  Vertical scrolling offset
    oledbw_send( ctx, OLEDBW_ACTIVATE_SCROLL,                     OLEDBW_COMMAND );   //  0x2F Activate scroll
}

void
oledbw_stop_scroll( oledbw_t *ctx )
{
    oledbw_send( ctx, 0x2E, OLEDBW_COMMAND );   //  0x2E Deactivate scroll
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static OLEDBW_RETVAL
oledbw_spi_master_write( oledbw_t *obj, oledbw_data_t data_in,
                         oledbw_data_mode_t data_mode )
{
    if (data_mode == OLEDBW_COMMAND)
    {
        digital_out_low( &obj->dc );
    }
    else if (data_mode == OLEDBW_DATA)
    {
        digital_out_high( &obj->dc );
    }
    else
    {
        return OLEDBW_INVALID_DATA_MODE;
    }

    spi_master_select_device( obj->chip_select );
    spi_master_write( &obj->spi, &data_in, 1 );
    spi_master_deselect_device( obj->chip_select ); 

    return OLEDBW_OK;
}

static OLEDBW_RETVAL
oledbw_i2c_master_write( oledbw_t *obj, oledbw_data_t data_in,
                         oledbw_data_mode_t data_mode )
{
    uint8_t tx_buffer[ 2 ];

    if (data_mode == OLEDBW_COMMAND)
    {
        digital_out_low( &obj->dc );
        tx_buffer[ 0 ] = 0b0000000;
    }
    else if (data_mode == OLEDBW_DATA)
    {
        digital_out_high( &obj->dc );
        tx_buffer[ 0 ] = 0b1100000;
    }
    else
    {
        return OLEDBW_INVALID_DATA_MODE;
    }

    tx_buffer[ 1 ] = data_in;

    i2c_master_set_slave_address( &obj->i2c, data_mode );
    i2c_master_write( &obj->i2c, tx_buffer, 2 );    

    return OLEDBW_OK;
}

// ------------------------------------------------------------------------ END
