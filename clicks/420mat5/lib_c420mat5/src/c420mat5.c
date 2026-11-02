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
 * @file c420mat5.c
 * @brief 4-20mA T 5 Click Driver.
 */

#include "c420mat5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void c420mat5_cfg_setup ( c420mat5_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->od   = HAL_PIN_NC;
    cfg->err  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t c420mat5_init ( c420mat5_t *ctx, c420mat5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->od, cfg->od );
    digital_in_init( &ctx->err, cfg->err );

    /* Disable output */
    digital_out_high( &ctx->od );

    return SPI_MASTER_SUCCESS;
}

err_t c420mat5_default_cfg ( c420mat5_t *ctx ) 
{
    err_t error_flag = C420MAT5_OK;
    
    /* Startup delay */
    Delay_100ms( );

    /*
     * Volatile VREF register(0x08):
     *
     *  - bits[1:0] = 00 -> VDD selected as the reference, datasheed(page 55, 5.2)
     *                      recommends the VDD reference mode when VREF pin is tied to VDD
     *                      as per schematic of the Click board.
     */
    error_flag |= c420mat5_write_reg( ctx, C420MAT5_REG_VREF, C420MAT5_VREF_VDD_UNBUFFERED );

    /*
     * Power-down control register(0x09):
     *
     *  - bits[1:0] = 00 -> Normal operation (not powered-down)
     */
    error_flag |= c420mat5_write_reg( ctx, C420MAT5_REG_PWR_DOWN, C420MAT5_PWR_DOWN_NORMAL );

    /* Set the lower current loop limit before the output is enabled */
    error_flag |= c420mat5_set_output_current( ctx, C420MAT5_CURRENT_MIN_MA );

    c420mat5_enable_output( ctx );

    Delay_10ms( );

    return error_flag;
}

err_t c420mat5_write_reg ( c420mat5_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    /* 
     * Write frame : CS_LOW | command_byte | data[15:8] | data[7:0] | CS_HIGH 
     *
     *  - command_byte[7:3] = AD4..AD0 -> Register address
     *  - command_byte[2:1] = C1 C0 -> Command bits (00 - write, 11 - read)
     *  - command_byte[0] = X -> reserved
     */
    uint8_t tx_buf[ C420MAT5_FRAME_LEN ] = { 0 };

    tx_buf[ 0 ] = ( uint8_t ) ( ( reg << C420MAT5_REG_ADDR_SHIFT ) | C420MAT5_CMD_WRITE );
    tx_buf[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) data_in;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, C420MAT5_FRAME_LEN );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t c420mat5_read_reg ( c420mat5_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    /* 
     * Read frame : CS_LOW | command_byte | read_data[15:8] | read_data[7:0] | CS_HIGH 
     *
     *  - command_byte[7:3] = AD4..AD0 -> Register address
     *  - command_byte[2:1] = C1 C0 -> Command bits (00 - write, 11 - read)
     *  - command_byte[0] = X -> reserved
     */
    uint8_t rx_buf[ C420MAT5_DATA_LEN ] = { 0 };
    uint8_t cmd_byte = ( uint8_t ) ( ( reg << C420MAT5_REG_ADDR_SHIFT ) | C420MAT5_CMD_READ );

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd_byte, C420MAT5_CMD_LEN, rx_buf, C420MAT5_DATA_LEN );
    spi_master_deselect_device( ctx->chip_select );

    *data_out = ( uint16_t ) ( ( rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] );

    return error_flag;
}

err_t c420mat5_set_dac_value ( c420mat5_t *ctx, uint16_t dac_value ) 
{
    /* The raw value is limited to the range that keeps the XTR200 inside its 4-20mA limit. */
    if ( ( C420MAT5_DAC_MIN_VALUE > dac_value ) || ( C420MAT5_DAC_MAX_VALUE < dac_value ) )
    {
        return C420MAT5_ERROR;
    }

    err_t error_flag = c420mat5_write_reg( ctx, C420MAT5_REG_DAC0, dac_value );

    return error_flag;
}

err_t c420mat5_set_output_current ( c420mat5_t *ctx, float current_ma ) 
{
    err_t error_flag = C420MAT5_OK;

    /* 4-20mA range guard */
    if ( ( C420MAT5_CURRENT_MIN_MA > current_ma ) || ( C420MAT5_CURRENT_MAX_MA < current_ma ) )
    {
        return C420MAT5_ERROR;
    }

    /*
     * DAC reg_value calculation based on desired output current:
     *
     *  - XTR200 : I_OUT = 10 * V_IN / R_SET (page 17, equation 3)
     *     => V_IN = I_OUT * R_SET / 10.
     * 
     *  - MCP48CMD21 : V_OUT = ( ( V_rl * reg_value ) / ( ladder_resistors ) ) * Gain (page 57, equation 5-2),
     *     - V_rl = VDD = 5V
     *     - ladder_resistors = 4096
     *     - Gain = 1
     *        => For a given voltage : DAC reg_value = ( V_OUT * 4096 )  / 5000mV
     * 
     *  - MCP48CMD21T V_OUT mapped to XTR200DQCR V_IN:
     *     => DAC reg_value = ( V_IN * 4096 ) / 5000mV
     *                      = ( I_OUT[mA] * R_SET / 10 ) * 4096 / 5000mV
     */
    float v_in_mv = ( current_ma * C420MAT5_RSET_OHM ) / C420MAT5_XTR_CURRENT_GAIN;
    uint16_t dac_value = ( uint16_t ) ( ( ( v_in_mv * C420MAT5_DAC_RESOLUTION ) / C420MAT5_VREF_MV ) + C420MAT5_ROUND_OFFSET );

    error_flag |= c420mat5_set_dac_value( ctx, dac_value );

    return error_flag;
}

void c420mat5_enable_output ( c420mat5_t *ctx ) 
{
    digital_out_low( &ctx->od );
}

void c420mat5_disable_output ( c420mat5_t *ctx ) 
{
    digital_out_high( &ctx->od );
}

uint8_t c420mat5_get_err_pin ( c420mat5_t *ctx )
{
    return digital_in_read( &ctx->err );
}

// ------------------------------------------------------------------------- END
