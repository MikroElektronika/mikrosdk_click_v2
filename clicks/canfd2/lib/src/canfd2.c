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

#include "canfd2.h"
#include "string.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define CANFD2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void canfd2_cfg_setup ( canfd2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;

    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

CANFD2_RETVAL canfd2_init ( canfd2_t *ctx, canfd2_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    spi_master_config_t spi_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = CANFD2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return CANFD2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, CANFD2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return CANFD2_OK;
}

void canfd2_generic_write ( canfd2_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t canfd2_generic_read ( canfd2_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void canfd2_generic_transfer ( canfd2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1us( );    
}

uint8_t  canfd2_read_data ( canfd2_t *ctx, uint8_t reg_addr )
{
    uint8_t write_tmp;
    uint8_t read_data;

    write_tmp = reg_addr & CANFD2_READ_CMD_MASK;

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_write( &ctx->spi, &write_tmp, 1 );
    spi_master_read( &ctx->spi, &read_data, 1 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1us( );
    
    return read_data;
}

void canfd2_write_data ( canfd2_t *ctx, uint8_t reg_addr, uint8_t write_data )
{
    uint8_t write_tmp;

    write_tmp = reg_addr | CANFD2_WRITE_CMD;

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_write( &ctx->spi, &write_tmp, 1 );
    spi_master_write( &ctx->spi, &write_data, 1 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1us( );
}

void canfd2_set_mode ( canfd2_t *ctx, uint8_t op_mode )
{
    switch ( op_mode )
    {
        case CANFD2_OP_MODE_SLEEP:
        {
            canfd2_write_data( ctx, CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_SLEEP );
            break;
        }
        case CANFD2_OP_MODE_STANDBY:
        {
            canfd2_write_data( ctx, CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_STANDBY );
            break;
        }
        case CANFD2_OP_MODE_RECEIVE_ONLY:
        {
            canfd2_write_data( ctx, CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_REC_ONLY );
            break;
        }
        case CANFD2_OP_MODE_NORMAL:
        {
            canfd2_write_data( ctx, CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_NORMAL_OP );
            break;
        }
        default:
        {
            canfd2_write_data( ctx, CANFD2_REG_MODE_CTRL, CANFD2_CTRL_MODE_NORMAL_OP );
            break;
        }
    }
    
    canfd2_write_data( ctx, CANFD2_REG_SWK_CTRL_1, CANFD2_SWK_CTRL_1_CFG_VAL );
    canfd2_write_data( ctx, CANFD2_REG_SWK_CTRL_2, CANFD2_SWK_CTRL_2_SWK_EN |
                                                   CANFD2_SWK_CTRL_2_BR_1M );
}

uint8_t canfd2_get_mode ( canfd2_t *ctx )
{
    uint8_t rx_buf;
    uint8_t o_mode;
    
    rx_buf = canfd2_read_data( ctx, CANFD2_REG_MODE_CTRL ) & 0x0F;
    
    switch ( rx_buf )
    {
        case CANFD2_CTRL_MODE_SLEEP:
        {
            o_mode = CANFD2_OP_MODE_SLEEP;
            break;
        }
        case CANFD2_CTRL_MODE_STANDBY:
        {
            o_mode = CANFD2_OP_MODE_STANDBY;
            break;
        }
        case CANFD2_CTRL_MODE_REC_ONLY:
        {
            o_mode = CANFD2_OP_MODE_RECEIVE_ONLY;
            break;
        }
        case CANFD2_CTRL_MODE_NORMAL_OP:
        {
            o_mode = CANFD2_OP_MODE_NORMAL;
            break;
        }
        default:
        {
            o_mode = CANFD2_OP_MODE_UNKNOWN;
            break;
        }
    }
    
    return o_mode;
}

// ------------------------------------------------------------------------- END

