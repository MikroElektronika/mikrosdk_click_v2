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

#include "semperflash2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define SEMPERFLASH2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void drv_communication_delay( );

static void drv_memory_communication_delay( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void semperflash2_cfg_setup ( semperflash2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->io2 = HAL_PIN_NC;
    cfg->io3 = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

SEMPERFLASH2_RETVAL semperflash2_init ( semperflash2_t *ctx, semperflash2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = SEMPERFLASH2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return SEMPERFLASH2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, SEMPERFLASH2_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->io2, cfg->io2 );
    digital_out_init( &ctx->io3, cfg->io3 );

    spi_master_deselect_device( ctx->chip_select );  
    digital_out_high( &ctx->io3 );
    digital_out_high( &ctx->io2 );
    digital_out_high( &ctx->rst );

    return SEMPERFLASH2_OK;
}

void semperflash2_default_cfg ( semperflash2_t *ctx )
{
    semperflash2_config_t cfg_data;

    semperflash2_send_cmd( ctx, SEMPERFLASH2_WRITE_ENABLE_VOLATILE );

    cfg_data.status_reg1 = SEMPERFLASH2_STATUS_REG_1_PROGRAM_ERASE_REG_WRITE_ENABLE;
    cfg_data.cfg1        = SEMPERFLASH2_CFG_1_DEFAULT;
    cfg_data.cfg2        = SEMPERFLASH2_CFG_2_DEFAULT;
    cfg_data.cfg3        = SEMPERFLASH2_CFG_3_DEFAULT;
    cfg_data.cfg4        = SEMPERFLASH2_CFG_4_DEFAULT;

    semperflash2_write_config( ctx, &cfg_data );
}

void semperflash2_send_cmd ( semperflash2_t *ctx, uint8_t cmd )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1us();
    spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );  
    drv_communication_delay( );
}

void semperflash2_transfer_data 
(   
    semperflash2_t *ctx, 
    uint8_t *write_buf,
    uint16_t wbuf_size,
    uint8_t *read_buf,
    uint16_t rbuf_size
)   
{
    spi_master_select_device( ctx->chip_select );
    Delay_1us();
    spi_master_write_then_read( &ctx->spi, write_buf, wbuf_size, read_buf, rbuf_size );
    spi_master_deselect_device( ctx->chip_select );   
    drv_communication_delay( );
}

void semperflash2_generic_write 
(   
    semperflash2_t *ctx, 
    uint8_t *write_buf,
    uint16_t buf_size
)  
{
    spi_master_select_device( ctx->chip_select );
    Delay_1us();
    spi_master_write( &ctx->spi, write_buf, buf_size );
    spi_master_deselect_device( ctx->chip_select );   
    drv_communication_delay( );
}

void semperflash2_write_config ( semperflash2_t *ctx, semperflash2_config_t *cfg_data )
{
    uint8_t cfg_buf[ 6 ];

    cfg_buf[ 0 ] = SEMPERFLASH2_WRITE_REG;
    cfg_buf[ 1 ] = cfg_data->status_reg1;
    cfg_buf[ 2 ] = cfg_data->cfg1;
    cfg_buf[ 3 ] = cfg_data->cfg2;
    cfg_buf[ 4 ] = cfg_data->cfg3;
    cfg_buf[ 5 ] = cfg_data->cfg4;

    semperflash2_generic_write( ctx, cfg_buf, 6 );
    drv_communication_delay( );
}

uint8_t semperflash2_read_memory 
(   
    semperflash2_t *ctx,
    uint32_t addr,
    uint8_t *data_buf,
    uint16_t buf_size
)
{
    uint8_t write_buf[ 256 ] = { 0 };
    uint8_t read_buf[ 256 ] = { 0 };
    uint8_t cnt;

    if ( buf_size > SEMPERFLASH2_MEMORY_BUF_MAX_SIZE )
    {
        return SEMPERFLASH2_SIZE_ERROR;
    }

    write_buf[ 0 ] = SEMPERFLASH2_READ_1;
    write_buf[ 1 ] = addr >> 24;
    write_buf[ 2 ] = addr >> 16;
    write_buf[ 3 ] = addr >> 8;
    write_buf[ 4 ] = addr;

    semperflash2_transfer_data( ctx, write_buf, 5, data_buf, buf_size );
    drv_memory_communication_delay( );

    return SEMPERFLASH2_SUCCESS;
}

uint8_t semperflash2_write_memory 
( 
    semperflash2_t *ctx,
    uint32_t addr,
    uint8_t *data_buf,
    uint16_t buf_size
)
{
    uint8_t write_buf[ 256 ];
    uint8_t cnt;

    if ( buf_size > SEMPERFLASH2_MEMORY_BUF_MAX_SIZE )
    {
        return SEMPERFLASH2_SIZE_ERROR;
    }

    write_buf[ 0 ] = SEMPERFLASH2_PROGRAM_PAGE_1;
    write_buf[ 1 ] = addr >> 24;
    write_buf[ 2 ] = addr >> 16;
    write_buf[ 3 ] = addr >> 8;
    write_buf[ 4 ] = addr;
    
    for ( cnt = 0; cnt < buf_size; cnt++ )
    {
        write_buf[ cnt + 5 ] = data_buf[ cnt ];
    }
    
    semperflash2_generic_write( ctx, write_buf, buf_size + 5 );
    drv_memory_communication_delay( );

    return SEMPERFLASH2_SUCCESS;
}

void semperflash2_erase_memory ( semperflash2_t *ctx, uint32_t addr )
{
    uint8_t erase_buf[ 5 ];

    erase_buf[ 0 ] = SEMPERFLASH2_ERASE_4K_1;
    erase_buf[ 1 ] = addr >> 24;
    erase_buf[ 2 ] = addr >> 16;
    erase_buf[ 3 ] = addr >> 8;
    erase_buf[ 4 ] = addr;

    semperflash2_generic_write( ctx, erase_buf,5 );
    drv_memory_communication_delay( );
}

uint8_t semperflash2_get_device_id ( semperflash2_t *ctx, uint8_t *id_buf )
{
    uint8_t id_buf_write[ 13 ];
    uint8_t cnt;

    id_buf_write[ 0 ] = SEMPERFLASH2_DEVICE_ID;

    semperflash2_transfer_data( ctx, id_buf_write, 5, id_buf, 8 );
    drv_communication_delay( );

    return SEMPERFLASH2_SUCCESS;
}

uint8_t semperflash2_check_manufacturer_id ( semperflash2_t *ctx )
{
    uint8_t id_write[ 2 ];
    uint8_t id_read[ 2 ] = { 0 };

    id_write[ 0 ] = SEMPERFLASH2_MANUFACTURER_DEVICE_ID;

    semperflash2_transfer_data( ctx, id_write, 1, id_read, 1 );
    drv_communication_delay( );
    
    if ( SEMPERFLASH2_MANUFACTURER_DEVICE_ID_VALUE == id_read[ 0 ] )
    {
        return SEMPERFLASH2_SUCCESS;
    }
    else
    {
        return SEMPERFLASH2_ID_ERROR;
    }
}

uint8_t semperflash2_check_status_reg_1 ( semperflash2_t *ctx )
{
    uint8_t cmd[ 2 ] = { 0 };
    uint8_t return_val[ 2 ] = { 0 };

    cmd[ 0 ] = SEMPERFLASH2_READ_STATUS_REG_1;

    semperflash2_transfer_data( ctx, cmd, 1, return_val, 1 );
    drv_communication_delay( );

    return return_val[ 0 ];
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void drv_communication_delay ( )
{
    Delay_10ms( );
}

static void drv_memory_communication_delay ( )
{
    Delay_100ms( );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

