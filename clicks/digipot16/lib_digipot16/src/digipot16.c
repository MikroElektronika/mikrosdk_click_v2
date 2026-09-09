/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file digipot16.c
 * @brief DIGI POT 16 Click Driver.
 */

#include "digipot16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void digipot16_cfg_setup ( digipot16_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t digipot16_init ( digipot16_t *ctx, digipot16_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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
    
    /* RST is active on LOW-to-HIGH transition */
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_high ( &ctx->rst );

    digital_in_init( &ctx->rdy, cfg->rdy );

    return SPI_MASTER_SUCCESS;
}

err_t digipot16_default_cfg ( digipot16_t *ctx ) 
{
    err_t error_flag = DIGIPOT16_OK;

    DIGIPOT16_SET_DATA_SAMPLE_EDGE;
    
    /* Hardware reset:
     *    wiper -> midscale(512)
     *    write protect -> ON */
    digipot16_hw_reset ( ctx );
    Delay_100ms( );
    
    /* Unlock writing to RDAC register(wiper position) -> Command 4 with [D2:D1] = 01b */
    error_flag |= digipot16_send_command ( ctx, DIGIPOT16_CMD_WRITE_CTRL |
                                                DIGIPOT16_CTRL_WRITE_ENABLE );

    return error_flag;
}

void digipot16_hw_reset ( digipot16_t *ctx )
{
    /* RST is active on LOW-to-HIGH transition */
    digital_out_low ( &ctx->rst );

    /* tRESET min = 20ns - minimum reset pulse width */
    Delay_1ms( );

    digital_out_high ( &ctx->rst );

    /* tPOWER-UP max = 2ms - power-on time to half scale */
    Delay_10ms( );
}

err_t digipot16_send_command ( digipot16_t *ctx, uint16_t cmd_word )
{  
    /* Each command is a 16-bit word:
     *    bits[15:14] - Always 0 bits
     *    bits[13:10] - control bits
     *    bits[9:0]   - data bits */
    uint8_t tx_buf[ 2 ] = { 0 };
    err_t error_flag = DIGIPOT16_OK;

    /* Split 16-bit word into two bytes, MSB first. */
    tx_buf[ 0 ] = ( uint8_t ) ( ( cmd_word >> 8 ) & DIGIPOT16_BYTE_MASK );
    tx_buf[ 1 ] = ( uint8_t ) ( cmd_word & DIGIPOT16_BYTE_MASK );

    spi_master_select_device ( ctx->chip_select );
    error_flag |= spi_master_write ( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device ( ctx->chip_select );

    return error_flag;
}

err_t digipot16_send_command_read ( digipot16_t *ctx, uint16_t *data_out )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    err_t error_flag = DIGIPOT16_OK;

    if ( NULL == data_out )
    {
        return DIGIPOT16_ERROR;
    }
 
    /* NOP command = [0, 0, 0, 0, 0, 0, X9...X0] */
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_select_device ( ctx->chip_select );
    error_flag |= spi_master_read ( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device ( ctx->chip_select );

    *data_out = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] ) & DIGIPOT16_WIPER_MASK;

    return error_flag;
}

err_t digipot16_wait_ready ( digipot16_t *ctx )
{
    uint32_t timeout = DIGIPOT16_RDY_TIMEOUT_MS;

    while ( !digital_in_read ( &ctx->rdy ) )
    {
        if ( !timeout-- )
        {
            return DIGIPOT16_ERROR;
        }
        Delay_1ms( );
    }
    return DIGIPOT16_OK;
}

err_t digipot16_soft_reset ( digipot16_t *ctx )
{
    /* Command 3: resets wiper to midscale (512) and restores default control register(write protect ON) */
    return digipot16_send_command ( ctx, DIGIPOT16_CMD_SOFT_RESET );
}

err_t digipot16_set_wiper ( digipot16_t *ctx, uint16_t wiper )
{
    /* Clamp wiper to valid 10-bit range(1024-position resolution). */
    wiper &= DIGIPOT16_WIPER_MASK;

    /* Command 1: write wiper position -> Word = [0, 0, 0, 0, 0, 1, D9...D0] */
    return digipot16_send_command ( ctx, DIGIPOT16_CMD_WRITE_RDAC | wiper );
}

err_t digipot16_get_wiper ( digipot16_t *ctx, uint16_t *wiper )
{
    uint16_t received_data = 0;
    err_t error_flag = DIGIPOT16_OK;

    if ( NULL == wiper )
    {
        return DIGIPOT16_ERROR;
    }

    /* Command 2: request RDAC readback -> Word = [0, 0, 0, 0, 1, 0, X9...X0] */
    error_flag |= digipot16_send_command ( ctx, DIGIPOT16_CMD_READ_RDAC );

    /* Wait for RDY -> signals data is ready to be output on the bus. */
    error_flag |= digipot16_wait_ready ( ctx );

    if ( DIGIPOT16_OK != error_flag )
    {
        return error_flag;
    }

    /* Send NOP command(Command 0 - clocks out wiper data on SDO on the same cycle) and read the response */
    error_flag |= digipot16_send_command_read ( ctx, &received_data );

    *wiper = received_data & DIGIPOT16_WIPER_MASK;

    return error_flag;
}

err_t digipot16_get_resistance ( digipot16_t *ctx, uint32_t *rwb_ohm, uint32_t *rwa_ohm )
{
    uint16_t wiper = 0;
    err_t error_flag = DIGIPOT16_OK;

    if ( ( NULL == rwb_ohm ) || ( NULL == rwa_ohm ) )
    {
        return DIGIPOT16_ERROR;
    }
    
    /* Get the current wiper position */
    error_flag |= digipot16_get_wiper ( ctx, &wiper );

    if ( DIGIPOT16_OK != error_flag )
    {
        return error_flag;
    }

    /* RWB = ( D / 1024 ) * RAB + RW */
    *rwb_ohm = ( ( uint32_t ) wiper * DIGIPOT16_RAB_OHM ) / DIGIPOT16_RESIS_1024_CONST + DIGIPOT16_RW_OHM;

    /* RWA = ( ( 1024 - D ) / 1024 ) * RAB  + RW */
    *rwa_ohm = ( ( uint32_t ) ( DIGIPOT16_RESIS_1024_CONST - wiper ) * DIGIPOT16_RAB_OHM ) / DIGIPOT16_RESIS_1024_CONST + DIGIPOT16_RW_OHM;

    return error_flag;
}

uint8_t digipot16_get_rdy_pin ( digipot16_t *ctx )
{
    return digital_in_read ( &ctx->rdy );
}

// ------------------------------------------------------------------------- END
