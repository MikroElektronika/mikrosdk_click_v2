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
 * \file reram.c
 *
 */

#include <string.h>
#include "reram.h"


// ------------------------------------------------------------- PRIVATE MACROS

#define RERAM_DUMMY      0x0

#define RERAM_CMD_RDSR   0x5
#define RERAM_CMD_WRSR   0x1
#define RERAM_CMD_READ   0x3
#define RERAM_CMD_WRITE  0x2
#define RERAM_CMD_RDID   0x9F

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief SPI Master Transfer function.
 *
 * @param obj  SPI object.
 * @param block  SPI transfer block.
 *
 * @description This function startup SPI driver and executes data transfer
 * operation.
 */
static void reram_generic_transfer 
( 
    reram_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
reram_cfg_setup( reram_cfg_t *cfg )
{
    cfg->cs  = HAL_PIN_NC;
    cfg->ho  = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->sdi = HAL_PIN_NC;
    cfg->sdo = HAL_PIN_NC;
    cfg->wp  = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

reram_err_t
reram_init( reram_t *ctx, reram_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->sdo;
    spi_cfg.mosi      = cfg->sdi;
    spi_cfg.default_write_data = RERAM_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    spi_master_set_default_write_data( &ctx->spi, RERAM_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    digital_out_init( &ctx->ho, cfg->ho );
    digital_out_init( &ctx->wp, cfg->wp );

    digital_out_high( &ctx->ho );
    digital_out_high( &ctx->wp );

    return RERAM_OK;
}

void
reram_default_cfg( reram_t *ctx )
{
    reram_send_cmd( ctx, RERAM_CMD_WREN );
    reram_write_status( ctx, RERAM_WP_STAT_EN );
}

reram_err_t
reram_send_cmd( reram_t *ctx, uint8_t cmd_code )
{
    uint8_t cmd_;

    if (( cmd_code != RERAM_CMD_WREN ) &&
        ( cmd_code != RERAM_CMD_WRDI ) &&
        ( cmd_code != RERAM_CMD_SLEEP ))
    {
        return RERAM_ERR_CMD;
    }

    cmd_ = cmd_code;

    reram_generic_transfer ( ctx, &cmd_, 1, 0, 0 );

    return RERAM_OK;
}

uint8_t
reram_read_status( reram_t *ctx )
{
    uint8_t data_input;
    uint8_t data_output[ 2 ];

    data_input = RERAM_CMD_RDSR;
    memset( data_output, RERAM_DUMMY, sizeof( data_output ) );

    reram_generic_transfer ( ctx, &data_input, 1, data_output, 2 );

    return data_output[ 1 ];
}

void
reram_write_status( reram_t *ctx, uint8_t data_in )
{
    uint8_t data_input[ 2 ];

    data_input[ 0 ] = RERAM_CMD_WRSR;
    data_input[ 1 ] = data_in;

    reram_generic_transfer ( ctx, data_input, 3, 0, 0 );
}

reram_err_t
reram_read_memory( reram_t *ctx, uint32_t mem_addr,
                   uint8_t *data_out, uint16_t n_bytes )
{
    uint8_t data_input[ 4 ];
    uint8_t data_output[ 260 ];
    uint16_t cnt;

    if (mem_addr > RERAM_MEM_ADDR_END)
    {
        return RERAM_ERR_MEM_ADDR;
    }
    if (( n_bytes < RERAM_TRANSFER_BYTES_MIN ) ||
        ( n_bytes > RERAM_TRANSFER_BYTES_MAX ))
    {
        return RERAM_ERR_NBYTES;
    }

    data_input[ 0 ] = RERAM_CMD_READ;
    data_input[ 1 ] = mem_addr >> 16;
    data_input[ 2 ] = mem_addr >> 8;
    data_input[ 3 ] = mem_addr;
    memset( data_output, RERAM_DUMMY, sizeof( data_output ) );

    reram_generic_transfer ( ctx, data_input, 4, data_output, n_bytes + 4 );

    for (cnt = 4; cnt < n_bytes + 4; cnt++)
    {
        *data_out = data_output[ cnt ];
        data_out++;
    }

    return RERAM_OK;
}

reram_err_t
reram_write_memory( reram_t *ctx, uint32_t mem_addr,
                    uint8_t *data_in, uint16_t n_bytes )
{
    uint8_t data_input[ 260 ];
    uint16_t cnt;

    if (mem_addr > RERAM_MEM_ADDR_END)
    {
        return RERAM_ERR_MEM_ADDR;
    }
    if (( n_bytes < RERAM_TRANSFER_BYTES_MIN ) ||
        ( n_bytes > RERAM_TRANSFER_BYTES_MAX ))
    {
        return RERAM_ERR_NBYTES;
    }

    memset( data_input, RERAM_DUMMY, sizeof( data_input ) );
    data_input[ 0 ] = RERAM_CMD_WRITE;
    data_input[ 1 ] = mem_addr >> 16;
    data_input[ 2 ] = mem_addr >> 8;
    data_input[ 3 ] = mem_addr;

    for (cnt = 4; cnt < n_bytes + 4; cnt++)
    {
        data_input[ cnt ] = *data_in;
        data_in++;
    }

    reram_generic_transfer ( ctx, data_input, n_bytes + 4, 0, 0 );

    return RERAM_OK;
}

uint32_t
reram_read_id( reram_t *ctx )
{
    uint8_t data_input;
    uint8_t data_output[ 5 ];
    uint32_t ret_val;

    data_input = RERAM_CMD_RDID;
    memset( data_output, RERAM_DUMMY, sizeof( data_output ) );

    reram_generic_transfer ( ctx, &data_input, 1, data_output, 5 );

    ret_val = data_output[ 1 ];
    ret_val <<= 8;
    ret_val |= data_output[ 2 ];
    ret_val <<= 8;
    ret_val |= data_output[ 3 ];
    ret_val <<= 8;
    ret_val |= data_output[ 4 ];

    return ret_val;
}

void
reram_set_hold_pin( reram_t *ctx, reram_pin_state_t state )
{
    digital_out_write( &ctx->ho, state );
}

void
reram_set_write_protect_pin( reram_t *ctx, reram_pin_state_t state )
{
    digital_out_write( &ctx->wp, state );
}

void
reram_wake_up( reram_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    Delay_10ms();
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_10ms();
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void reram_generic_transfer 
( 
    reram_t *ctx, 
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

// ------------------------------------------------------------------------ END
