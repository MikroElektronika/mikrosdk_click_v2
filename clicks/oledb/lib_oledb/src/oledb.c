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

#include "oledb.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OLEDB_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief SPI Master Write function.
 * @details This function executes data writing by using SPI driver.
 * @param[in] obj  Click object.
 * @param[in] data_in  Data to be sent.
 * @param[in] data_len  Number of data bytes.
 * @returns Nothing.
 */
static void dev_oledb_spi_master_write( oledb_t *obj, oledb_data_t *data_in, uint8_t data_len );

/**
 * @brief I2C Master Write function.
 * @details This function executes data writing by using I2C driver.
 * @param[in] obj  Click object.
 * @param[in] data_in  Data to be sent.
 * @param[in] data_len  Number of data bytes.
 * @returns Nothing.
 */
static void dev_oledb_i2c_master_write( oledb_t *obj, oledb_data_t *data_in, uint8_t data_len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void oledb_cfg_setup( oledb_cfg_t *cfg ) 
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
    cfg->i2c_address = OLEDB_COMMAND;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->sel = OLEDB_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t oledb_init( oledb_t *ctx, oledb_cfg_t *cfg ) 
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( OLEDB_MASTER_I2C == ctx->master_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return OLEDB_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->send = dev_oledb_i2c_master_write;
    } 
    else if ( OLEDB_MASTER_SPI == ctx->master_sel ) 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->sdi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
        {
            return OLEDB_INIT_ERROR;
        }
        
        spi_master_deselect_device( ctx->chip_select );
        spi_master_set_default_write_data( &ctx->spi, OLEDB_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );

        ctx->send = dev_oledb_spi_master_write;
    } 
    else 
    {
        ctx->send = NULL;
        return OLEDB_INVALID_DRIVER_SELECTOR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dc, cfg->dc );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );

    return OLEDB_OK;
}

void oledb_send_cmd( oledb_t *ctx, oledb_data_t tx_cmd )
{
    uint8_t tx_buffer[ 2 ];
    digital_out_low( &ctx->dc );
    tx_buffer[ 0 ] = 0x80;
    tx_buffer[ 1 ] = tx_cmd;
    if ( OLEDB_MASTER_I2C == ctx->master_sel )
    {
        i2c_master_set_slave_address( &ctx->i2c, OLEDB_COMMAND );
    }
    ctx->send( ctx, tx_buffer, 2 );
}

void oledb_send_data( oledb_t *ctx, oledb_data_t *tx_data, uint8_t data_len )
{
    uint8_t tx_buffer[ 256 ];
    digital_out_high( &ctx->dc );
    tx_buffer[ 0 ] = 0x40;
    memcpy ( &tx_buffer[ 1 ], tx_data, data_len );
    if ( OLEDB_MASTER_I2C == ctx->master_sel )
    {
        i2c_master_set_slave_address( &ctx->i2c, OLEDB_DATA );
    }
    ctx->send( ctx, tx_buffer, data_len + 1 );
}

void oledb_default_cfg( oledb_t *ctx ) 
{
    oledb_send_cmd( ctx, OLEDB_DISPLAYOFF );            //  0xAE Set OLED Display Off
    oledb_send_cmd( ctx, OLEDB_SETDISPLAYCLOCKDIV );    //  0xD5 Set Display Clock Divide Ratio/Oscillator Frequency
    oledb_send_cmd( ctx, 0x80 );
    oledb_send_cmd( ctx, OLEDB_SETMULTIPLEX );          //  0xA8 Set Multiplex Ratio
    oledb_send_cmd( ctx, OLEDB_DISPLAY_HEIGHT - 1 );
    oledb_send_cmd( ctx, OLEDB_SETDISPLAYOFFSET );      //  0xD3 Set Display Offset
    oledb_send_cmd( ctx, 0x00 );
    oledb_send_cmd( ctx, OLEDB_SETSTARTLINE );          //  0x40 Set Display Start Line
    oledb_send_cmd( ctx, OLEDB_CHARGEPUMP );            //  0x8D Set Charge Pump
    oledb_send_cmd( ctx, 0x14 );                        //  0x14 Enable Charge Pump
    oledb_send_cmd( ctx, OLEDB_COMSCANDEC );            //  0xC8 Set COM Output Scan Direction
    oledb_send_cmd( ctx, OLEDB_SETCOMPINS );            //  0xDA Set COM Pins Hardware Configuration
    oledb_send_cmd( ctx, 0x12 );
    oledb_send_cmd( ctx, OLEDB_SETCONTRAST );           //  0x81 Set Contrast Control
    oledb_send_cmd( ctx, 0xAF );
    oledb_send_cmd( ctx, OLEDB_SETPRECHARGE );          //  0xD9 Set Pre-Charge Period
    oledb_send_cmd( ctx, 0x25 );
    oledb_send_cmd( ctx, OLEDB_SETVCOMDETECT );         //  0xDB Set VCOMH Deselect Level
    oledb_send_cmd( ctx, 0x20 );
    oledb_send_cmd( ctx, OLEDB_DISPLAYALLON_RESUME );   //  0xA4 Set Entire Display On/Off
    oledb_send_cmd( ctx, OLEDB_NORMALDISPLAY );         //  0xA6 Set Normal/Inverse Display
    oledb_send_cmd( ctx, OLEDB_DISPLAYON );             //  0xAF Set OLED Display On
}

void oledb_set_page( oledb_t *ctx, oledb_data_t page_addr ) 
{
    oledb_send_cmd( ctx, OLEDB_PAGEADDR );
    oledb_send_cmd( ctx, page_addr );
    oledb_send_cmd( ctx, OLEDB_DISPLAY_ROWS - 1 );
}

void oledb_set_column( oledb_t *ctx, oledb_data_t col_addr ) 
{
    oledb_send_cmd( ctx, OLEDB_COLUMNADDR );
    oledb_send_cmd( ctx, col_addr );
    oledb_send_cmd( ctx, OLEDB_SSD1306_WIDTH - 1 );
}

void oledb_display_picture( oledb_t *ctx, oledb_resources_t *pic ) 
{
    uint8_t data_buf[ 8 ] = { 0 };
    uint8_t page_num = 0;
    uint8_t seg_num = 0;
    oledb_send_cmd( ctx, OLEDB_DISPLAYOFF );
    for ( page_num = 0; page_num < OLEDB_DISPLAY_ROWS; page_num++ ) 
    {
        oledb_set_column ( ctx, 0 );
        oledb_set_page ( ctx, page_num );
        for ( seg_num = 0; seg_num < OLEDB_DISPLAY_WIDTH; seg_num += 8 )
        {
            memcpy ( data_buf, &pic[ page_num * OLEDB_DISPLAY_WIDTH + seg_num ], 8 );
            oledb_send_data( ctx, data_buf, 8 );
        }
    }
    oledb_send_cmd( ctx, OLEDB_DISPLAYON );
}

void oledb_clear_display( oledb_t *ctx )
{
    uint8_t data_buf[ 8 ] = { 0 };
    uint8_t page_num = 0;
    uint8_t seg_num = 0;
    oledb_send_cmd( ctx, OLEDB_DISPLAYOFF );
    for ( page_num = 0; page_num < OLEDB_DISPLAY_ROWS; page_num++ ) 
    {
        oledb_set_column ( ctx, 0 );
        oledb_set_page ( ctx, page_num );
        for ( seg_num = 0; seg_num < OLEDB_SSD1306_WIDTH; seg_num += 8 )
        {
            oledb_send_data( ctx, data_buf, 8 );
        }
    }
    oledb_send_cmd( ctx, OLEDB_DISPLAYON );
}

void oledb_write_char( oledb_t *ctx, uint8_t font, uint8_t row, uint8_t position, uint8_t data_in )
{
    if ( ( font > OLEDB_FONT_6X8 ) || ( row > ( OLEDB_DISPLAY_ROWS - 1 ) ) )
    {
        return;
    }
    uint8_t char_buf[ 6 ] = { 0 };
    uint8_t char_width = 0;
    if ( ( data_in < 32 ) || ( data_in > 127 ) ) 
    {
        data_in = ' ';
    }
    if ( OLEDB_FONT_5X7 == font )
    {
        char_width = 5;
        memcpy ( char_buf, &oledb_font_5x7[ ( data_in - 32 ) * char_width ], char_width );
    }
    else if ( OLEDB_FONT_6X8 == font )
    {
        char_width = 6;
        memcpy ( char_buf, &oledb_font_6x8[ ( data_in - 32 ) * char_width ], char_width );
    }
    if ( position > ( ( ( OLEDB_SSD1306_WIDTH + 1 ) / char_width ) - 1 ) )
    {
        return;
    }
    
    oledb_set_column ( ctx, OLEDB_DISPLAY_WIDTH - char_width - position * char_width );
    oledb_set_page ( ctx, row );
    oledb_send_data( ctx, char_buf, char_width );
}

void oledb_write_string( oledb_t *ctx, uint8_t font, uint8_t row, uint8_t position, uint8_t *data_in )
{
    uint8_t data_len = strlen ( data_in );
    uint8_t data_cnt = 0;
    for ( data_cnt = 0; data_cnt < data_len; data_cnt++ )
    {
        oledb_write_char( ctx, font, row, position + data_len - 1 - data_cnt, data_in[ data_len - 1 - data_cnt ] );
    }
}

void oledb_set_contrast( oledb_t *ctx, oledb_data_t value ) 
{
    oledb_send_cmd( ctx, OLEDB_SETCONTRAST );    //  0x81 Set Contrast Control
    oledb_send_cmd( ctx, value );                //  Contrast Step 0 to 255
}

void oledb_scroll_right( oledb_t *ctx, oledb_data_t start_page_addr, oledb_data_t end_page_addr ) 
{
    oledb_send_cmd( ctx, OLEDB_RIGHT_HORIZONTAL_SCROLL );    //  0x26 Right Horizontal scroll
    oledb_send_cmd( ctx, 0x00 );                             //  Dummy byte
    oledb_send_cmd( ctx, start_page_addr );                  //  Define start page address
    oledb_send_cmd( ctx, 0x00 );                             //  Set time interval between each scroll
    oledb_send_cmd( ctx, end_page_addr );                    //  Define end page address
    oledb_send_cmd( ctx, 0x00 );                             //  Dummy byte
    oledb_send_cmd( ctx, 0xFF );                             //  Dummy byte
    oledb_send_cmd( ctx, OLEDB_ACTIVATE_SCROLL );            //  0x2F Activate scroll
}

void oledb_scroll_left( oledb_t *ctx, oledb_data_t start_page_addr, oledb_data_t end_page_addr ) 
{
    oledb_send_cmd( ctx, OLEDB_LEFT_HORIZONTAL_SCROLL );   //  0x27 Left Horizontal scroll
    oledb_send_cmd( ctx, 0x00 );                           //  Dummy byte
    oledb_send_cmd( ctx, start_page_addr );                //  Define start page address
    oledb_send_cmd( ctx, 0x00 );                           //  Set time interval between each scroll
    oledb_send_cmd( ctx, end_page_addr );                  //  Define end page address
    oledb_send_cmd( ctx, 0x00 );                           //  Dummy byte
    oledb_send_cmd( ctx, 0xFF );                           //  Dummy byte
    oledb_send_cmd( ctx, OLEDB_ACTIVATE_SCROLL );          //  0x2F Activate scroll
}

void oledb_scroll_diag_right( oledb_t *ctx, oledb_data_t start_page_addr, oledb_data_t end_page_addr ) 
{
    oledb_send_cmd( ctx, OLEDB_SET_VERTICAL_SCROLL_AREA );               //  0xA3 Set Vertical Scroll Area
    oledb_send_cmd( ctx, 0x00 );                                         //  Set No. of rows in top fixed area
    oledb_send_cmd( ctx, OLEDB_DISPLAY_HEIGHT );                         //  Set No. of rows in scroll area
    oledb_send_cmd( ctx, OLEDB_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL );   //  0x29 Vertical and Right Horizontal Scroll
    oledb_send_cmd( ctx, 0x00 );                                         //  Dummy byte
    oledb_send_cmd( ctx, start_page_addr );                              //  Define start page address
    oledb_send_cmd( ctx, 0x00 );                                         //  Set time interval between each scroll
    oledb_send_cmd( ctx, end_page_addr );                                //  Define end page address
    oledb_send_cmd( ctx, 0x01 );                                         //  Vertical scrolling offset
    oledb_send_cmd( ctx, OLEDB_ACTIVATE_SCROLL );                        //  0x2F Activate scroll
}

void oledb_scroll_diag_left( oledb_t *ctx, oledb_data_t start_page_addr, oledb_data_t end_page_addr ) 
{
    oledb_send_cmd( ctx, OLEDB_SET_VERTICAL_SCROLL_AREA );               //  0xA3 Set Vertical Scroll Area
    oledb_send_cmd( ctx, 0x00 );                                         //  Set No. of rows in top fixed area
    oledb_send_cmd( ctx, OLEDB_DISPLAY_HEIGHT );                         //  Set No. of rows in scroll area
    oledb_send_cmd( ctx, OLEDB_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL );    //  0x2A Vertical and Left Horizontal Scroll
    oledb_send_cmd( ctx, 0x00 );                                         //  Dummy byte
    oledb_send_cmd( ctx, start_page_addr );                              //  Define start page address
    oledb_send_cmd( ctx, 0x00 );                                         //  Set time interval between each scroll
    oledb_send_cmd( ctx, end_page_addr );                                //  Define end page address
    oledb_send_cmd( ctx, 0x01 );                                         //  Vertical scrolling offset
    oledb_send_cmd( ctx, OLEDB_ACTIVATE_SCROLL );                        //  0x2F Activate scroll
}

void oledb_stop_scroll( oledb_t *ctx ) 
{
    oledb_send_cmd( ctx, 0x2E);   //  0x2E Deactivate scroll
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_oledb_spi_master_write( oledb_t *obj, oledb_data_t *data_in, uint8_t data_len ) 
{
    spi_master_select_device( obj->chip_select );
    spi_master_write( &obj->spi, &data_in[ 1 ], data_len - 1 );
    spi_master_deselect_device( obj->chip_select ); 
}

static void dev_oledb_i2c_master_write( oledb_t *obj, oledb_data_t *data_in, uint8_t data_len ) 
{
    i2c_master_write( &obj->i2c, data_in, data_len );    
}

// ------------------------------------------------------------------------ END
