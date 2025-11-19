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
 * @file canlinsbc.c
 * @brief CAN-LIN SBC Click Driver.
 */

#include "canlinsbc.h"

/**
 * @brief Dummy data and SPI read bit.
 * @details Definition of dummy data and SPI read bit.
 */
#define CANLINSBC_DUMMY         0x00
#define CANLIBSBC_SPI_READ_BIT  0x01

void canlinsbc_cfg_setup ( canlinsbc_cfg_t *cfg ) 
{
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->txd_lin = HAL_PIN_NC;
    cfg->rxd_lin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t canlinsbc_init ( canlinsbc_t *ctx, canlinsbc_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, CANLINSBC_DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    uart_config_t uart_cfg;

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

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->txd_lin, cfg->txd_lin );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->txd_lin );

    digital_in_init( &ctx->rxd_lin, cfg->rxd_lin );

    return CANLINSBC_OK;
}

err_t canlinsbc_default_cfg ( canlinsbc_t *ctx ) 
{
    err_t error_flag = CANLINSBC_OK;
    
    // Default sample edge for Microchip PIC family devices
    CANLINSBC_SET_DATA_SAMPLE_EDGE;

    canlinsbc_reset_device ( ctx );
    if ( CANLINSBC_ERROR == canlibsbc_check_communication ( ctx ) )
    {
        return CANLINSBC_ERROR;
    }
    // Go to standby mode
    error_flag |= canlinsbc_write_reg ( ctx, CANLINSBC_REG_DMCR, CANLINSBC_DMCR_RSTEN | 
                                                                 CANLINSBC_DMCR_VCCOVSD | 
                                                                 CANLINSBC_DMCR_DOPM_STANDBY_MODE );

    // Clear LH with three consecutive watchdog reset commands
    error_flag |= canlinsbc_write_reg ( ctx, CANLINSBC_REG_WDTRIG, CANLINSBC_WDTRIG_RESET );
    error_flag |= canlinsbc_write_reg ( ctx, CANLINSBC_REG_WDTRIG, CANLINSBC_WDTRIG_RESET );
    error_flag |= canlinsbc_write_reg ( ctx, CANLINSBC_REG_WDTRIG, CANLINSBC_WDTRIG_RESET );

    // Disable watchdog
    error_flag |= canlinsbc_write_reg ( ctx, CANLINSBC_REG_WDCR1, CANLINSBC_WDCR1_WDC_OFF_MODE | 
                                                                  CANLINSBC_WDCR1_WDLW );
    
    // Set CAN transceiver operating mode to normal
    error_flag |= canlinsbc_write_reg ( ctx, CANLINSBC_REG_TRXCR, CANLINSBC_TRXCR_COMP_NORMAL_MODE );

    // Go to normal mode
    error_flag |= canlinsbc_write_reg ( ctx, CANLINSBC_REG_DMCR, CANLINSBC_DMCR_RSTEN | 
                                                                 CANLINSBC_DMCR_VCCOVSD | 
                                                                 CANLINSBC_DMCR_DOPM_NORMAL_MODE );
    return error_flag;
}

err_t canlinsbc_write_reg ( canlinsbc_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t reg_addr = ( reg << 1 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t canlinsbc_read_reg ( canlinsbc_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t reg_addr = ( reg << 1 ) | CANLIBSBC_SPI_READ_BIT;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_addr, 1, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t canlinsbc_generic_write ( canlinsbc_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t canlinsbc_generic_read ( canlinsbc_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void canlinsbc_set_rst_pin ( canlinsbc_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void canlinsbc_set_txd_lin_pin ( canlinsbc_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->txd_lin, state );
}

uint8_t canlinsbc_get_rxd_lin_pin ( canlinsbc_t *ctx )
{
    return digital_in_read ( &ctx->rxd_lin );
}

void canlinsbc_reset_device ( canlinsbc_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

err_t canlibsbc_check_communication ( canlinsbc_t *ctx )
{
    uint8_t device_id = 0;
    if ( CANLINSBC_OK == canlinsbc_read_reg ( ctx, CANLINSBC_REG_DIDR, &device_id ) )
    {
        if ( CANLINSBC_DEVICE_ID == device_id )
        {
            return CANLINSBC_OK;
        }
    }
    return CANLINSBC_ERROR;
}

// ------------------------------------------------------------------------- END
