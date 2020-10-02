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
 * \file
 *
 */

#include "rfid.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define RFID_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void rfid_spi_write ( rfid_t *ctx , uint8_t *data_buf , uint8_t len );
static void rfid_spi_read ( rfid_t *ctx , uint8_t *data_buf, uint8_t len );
static uint8_t binarySearch( uint8_t* arr[] , uint8_t l , uint8_t r , uint8_t x );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rfid_cfg_setup ( rfid_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

RFID_RETVAL rfid_init ( rfid_t *ctx, rfid_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = RFID_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return RFID_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, RFID_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->an , cfg->an );
    digital_out_init( &ctx->rst , cfg->rst );
    digital_out_init( &ctx->pwm , cfg->pwm );
    digital_out_init( &ctx->int_pin , cfg->int_pin );
   
    return RFID_OK;

}

void rfid_generic_transfer 
( 
    rfid_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t rfid_com_select( rfid_t* ctx , uint8_t com )
{
    if ( RFID_UART == com )
    {
        digital_out_low( &ctx->an );
        digital_out_low( &ctx->rst );
        digital_out_low( &ctx->pwm );
        digital_out_low( &ctx->int_pin );
        
        return 1;
    }
    else if ( RFID_SPI == com )
    {
        digital_out_low( &ctx->an );
        digital_out_low( &ctx->rst );
        digital_out_low( &ctx->pwm );
        digital_out_low( &ctx->int_pin );
        
        digital_out_high( &ctx->rst );
        digital_out_high( &ctx->pwm );
        Delay_1ms();
        digital_out_low( &ctx->pwm );
        Delay_1ms( );
        digital_out_high( &ctx->pwm );
        Delay_1ms( );
        
        return 1;
    }
        
    return 0;
}

uint8_t rfid_write( rfid_t* ctx , uint8_t cmd , uint8_t len , uint8_t* w_data )
{
    uint8_t w_buf[ RFID_MAX_DATA_LEN ] = { 0 };
    
    if( len & 0x00 )
        return 0;
    
    w_buf[ 0 ] = RFID_SEND_CMD_CRTL;
    w_buf[ 1 ] = cmd;
    w_buf[ 2 ] = len;
    if( NULL != w_data )
        memcpy( w_buf + 3 , w_data , len );
    
    rfid_spi_write ( ctx , w_buf , len + 3 );

    return 1;
}

uint8_t rfid_poll( rfid_t* ctx )
{
    uint8_t r_buf = 0;
    uint8_t w_data = RFID_POLL_CTRL;
    uint8_t i = 0;
    
    for( i = 0 ; (i < 250) && !( r_buf >> 3 ) ; i++ )
    {
        rfid_generic_transfer ( ctx , &w_data , 1 , &r_buf, 1 );
    }
    
    if ( 250 <= i )
        return 0;
    
    return 1;
}

void rfid_read( rfid_t* ctx , uint8_t* r_buf , uint8_t len)
{
    uint8_t w_data = RFID_READ_CTRL;
    
    if( RFID_MAX_DATA_LEN < len )
        return;
    
    rfid_generic_transfer ( ctx , &w_data , 1 , r_buf, len );
}

void rfid_read_idn( rfid_t* ctx , uint8_t* r_buf )
{
    uint8_t check = 0;
    
    rfid_write( ctx , RFID_IDN , 0 , NULL );
    check = rfid_poll( ctx );
    if( check )
        rfid_read( ctx , r_buf , 17 );
    
    Delay_ms( 500 );
}

void rfid_protocol_select( rfid_t* ctx , uint8_t* r_buf , uint8_t protocol )
{
    uint8_t w_data[ 2 ] = { 0 };
    uint8_t check = 0;
    
    w_data[ 0 ] = protocol;
    
    rfid_write( ctx , RFID_PROT_SELECT , 2 , w_data);
    check = rfid_poll( ctx );
    if( check )
        rfid_read( ctx , r_buf , 17 );
    
    Delay_ms( 500 );
}

uint8_t rfid_echo( rfid_t* ctx , uint8_t* r_buf)
{
    uint8_t check = 0;
    
    rfid_write( ctx , 0x55 , 0x00 , 0x00 );
    check = rfid_poll( ctx );
    if( check )
        rfid_read( ctx , r_buf , 0x0F );
    
    return ( 0x55 == *r_buf );
}

void rfid_index_mod( rfid_t* ctx , uint8_t* r_buf  )
{
    uint8_t w_buf[ 10 ] = { 0 };
    uint8_t check = 0;
    
    w_buf[0] = 0x09;
    w_buf[1] = 0x04;
    w_buf[2] = 0x68;
    w_buf[3] = 0x01;
    w_buf[4] = 0x01;
    w_buf[5] = 0x50;
    
    rfid_write( ctx , RFID_WR_WAKEUP_REG , 0x06 , w_buf );
    check = rfid_poll( ctx );
    if( check )
        rfid_read( ctx , r_buf , 17 );

    Delay_ms( 500 );
}

void rfid_auto_det( rfid_t* ctx , uint8_t* r_buf  )
{
    uint8_t w_buf[ 10 ] = { 0 };
    uint8_t check = 0;
    
    w_buf[0] = 0x09;
    w_buf[1] = 0x04;
    w_buf[2] = 0x0A;
    w_buf[3] = 0x01;
    w_buf[4] = 0x02;
    w_buf[5] = 0xA1;
    
    rfid_write( ctx , RFID_WR_WAKEUP_REG , 0x06 , w_buf );
    check = rfid_poll( ctx );
    if( check )
        rfid_read( ctx , r_buf , 17 );

    Delay_ms( 500 );
}

void rfid_read_nfc_tag( rfid_t* ctx , uint8_t* r_buf )
{
    uint8_t w_buf[ 10 ] = { 0 };
    uint8_t check = 0;
    
    w_buf[ 0 ] = 0x26;
    w_buf[ 1 ] = 0x07;
    
    rfid_write( ctx , RFID_SEND_RECV , 0x02 , w_buf );
    check = rfid_poll( ctx );
    if( check )
        rfid_read( ctx , r_buf , 17 );
    
    memset( w_buf , 0 , 10 );
    check = 0;
    
    w_buf[ 0 ] = 0x93;
    w_buf[ 1 ] = 0x20;
    w_buf[ 2 ] = 0x08;
    
    rfid_write( ctx , RFID_SEND_RECV , 0x03 , w_buf );
    check = rfid_poll( ctx );
    if( check )
        rfid_read( ctx , r_buf , 17 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void rfid_spi_write ( rfid_t *ctx , uint8_t *data_buf , uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_buf , len );
    spi_master_deselect_device( ctx->chip_select );    
}

static void rfid_spi_read ( rfid_t *ctx , uint8_t *data_buf, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi , data_buf , len );
    spi_master_deselect_device( ctx->chip_select ); 
}

// ------------------------------------------------------------------------- END

