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
 * @file rtd4.c
 * @brief RTD 4 Click Driver.
 */

#include "rtd4.h"

/**
 * @brief RTD 4 receive buffer flush function.
 * @details This function clears any pending byte from the UART RX ring buffer
 * before a command that returns deterministic response data is sent.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void rtd4_flush_rx ( rtd4_t *ctx );

/**
 * @brief RTD 4 byte stream reading function.
 * @details This function waits until the requested number of UART bytes is
 * received or until the timeout expires.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @param[in] timeout_ms : Timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtd4_read_bytes ( rtd4_t *ctx, uint8_t *data_out, uint8_t len, uint16_t timeout_ms );

/**
 * @brief RTD 4 DRDY wait function.
 * @details This function polls the ADS122U04 DRDY register flag until a new
 * conversion result is ready.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[in] timeout_ms : Timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtd4_wait_drdy ( rtd4_t *ctx, uint16_t timeout_ms );

/**
 * @brief RTD 4 register verification function.
 * @details This function reads one ADS122U04 configuration register and checks
 * if its content matches the expected default value.
 * @param[in] ctx : Click context object.
 * See #rtd4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] expected : Expected register value.
 * @param[in] mask : Register bits included in the comparison.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Config register 2 contains a live DRDY bit, so that bit is masked
 * during the default configuration readback.
 */
static err_t rtd4_check_reg ( rtd4_t *ctx, uint8_t reg, uint8_t expected, uint8_t mask );

void rtd4_cfg_setup ( rtd4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t rtd4_init ( rtd4_t *ctx, rtd4_cfg_t *cfg ) 
{
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

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );

    return UART_SUCCESS;
}

err_t rtd4_default_cfg ( rtd4_t *ctx ) 
{
    err_t error_flag = RTD4_OK;

    rtd4_hw_reset( ctx );

    rtd4_send_cmd( ctx, RTD4_CMD_RESET );
    Delay_1ms( );
    Delay_1ms( );

    // Register values are matched to the RTD 4 3-wire PT100 input network.
    rtd4_write_reg( ctx, RTD4_REG_CONFIG_0, RTD4_CFG0_RTD_3WIRE );
    rtd4_write_reg( ctx, RTD4_REG_CONFIG_1, RTD4_CFG1_RTD_3WIRE );
    rtd4_write_reg( ctx, RTD4_REG_CONFIG_2, RTD4_CFG2_RTD_3WIRE );
    rtd4_write_reg( ctx, RTD4_REG_CONFIG_3, RTD4_CFG3_RTD_3WIRE );
    rtd4_write_reg( ctx, RTD4_REG_CONFIG_4, RTD4_CFG4_RTD_3WIRE );

    // Register 2 bit 7 is the live DRDY flag and is masked during readback.
    error_flag |= rtd4_check_reg( ctx, RTD4_REG_CONFIG_0, RTD4_CFG0_RTD_3WIRE, RTD4_REG_MASK_ALL_BITS );
    error_flag |= rtd4_check_reg( ctx, RTD4_REG_CONFIG_1, RTD4_CFG1_RTD_3WIRE, RTD4_REG_MASK_ALL_BITS );
    error_flag |= rtd4_check_reg( ctx, RTD4_REG_CONFIG_2, RTD4_CFG2_RTD_3WIRE, RTD4_REG2_CFG_MASK );
    error_flag |= rtd4_check_reg( ctx, RTD4_REG_CONFIG_3, RTD4_CFG3_RTD_3WIRE, RTD4_REG_MASK_ALL_BITS );
    error_flag |= rtd4_check_reg( ctx, RTD4_REG_CONFIG_4, RTD4_CFG4_RTD_3WIRE, RTD4_REG_MASK_ALL_BITS );

    if ( RTD4_OK == error_flag )
    {
        rtd4_send_cmd( ctx, RTD4_CMD_START_SYNC );
    }

    return error_flag;
}

err_t rtd4_generic_write ( rtd4_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
} 

err_t rtd4_generic_read ( rtd4_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void rtd4_hw_reset ( rtd4_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_1ms( );
    Delay_1ms( );
}

uint8_t rtd4_get_drdy ( rtd4_t *ctx )
{
    uint8_t reg_data = 0;
    uint8_t drdy_state = RTD4_DATA_NOT_READY;

    if ( RTD4_OK == rtd4_read_reg( ctx, RTD4_REG_CONFIG_2, &reg_data ) )
    {
        drdy_state = ( reg_data >> RTD4_REG2_DRDY_SHIFT ) & RTD4_REG2_DRDY_STATE_MASK;
    }

    return drdy_state;
}

void rtd4_send_cmd ( rtd4_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ RTD4_CMD_FRAME_SIZE ] = { 0 };

    tx_buf[ RTD4_FRAME_SYNC_BYTE ] = RTD4_SYNC_WORD;
    tx_buf[ RTD4_FRAME_CMD_BYTE ] = cmd;

    rtd4_generic_write( ctx, tx_buf, RTD4_CMD_FRAME_SIZE );
    Delay_1ms( );
}

void rtd4_write_reg ( rtd4_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ RTD4_CMD_WREG_FRAME_SIZE ] = { 0 };

    tx_buf[ RTD4_FRAME_SYNC_BYTE ] = RTD4_SYNC_WORD;
    tx_buf[ RTD4_FRAME_CMD_BYTE ] = RTD4_CMD_WREG | ( ( reg & RTD4_CMD_REG_ADDR_MASK ) << RTD4_CMD_REG_ADDR_SHIFT );
    tx_buf[ RTD4_FRAME_DATA_BYTE ] = data_in;

    rtd4_generic_write( ctx, tx_buf, RTD4_CMD_WREG_FRAME_SIZE );
    Delay_1ms( );
    Delay_1ms( );
}

err_t rtd4_read_reg ( rtd4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t tx_buf[ RTD4_CMD_FRAME_SIZE ] = { 0 };

    rtd4_flush_rx( ctx );

    tx_buf[ RTD4_FRAME_SYNC_BYTE ] = RTD4_SYNC_WORD;
    tx_buf[ RTD4_FRAME_CMD_BYTE ] = RTD4_CMD_RREG | ( ( reg & RTD4_CMD_REG_ADDR_MASK ) << RTD4_CMD_REG_ADDR_SHIFT );

    rtd4_generic_write( ctx, tx_buf, RTD4_CMD_FRAME_SIZE );

    return rtd4_read_bytes( ctx, data_out, RTD4_REG_READ_SIZE, RTD4_REG_READ_TIMEOUT_MS );
}

err_t rtd4_read_raw ( rtd4_t *ctx, int32_t *adc_data )
{
    err_t error_flag = RTD4_OK;
    uint8_t rx_buf[ RTD4_CMD_RDATA_SIZE ] = { 0 };
    uint32_t raw_data = 0;

    rtd4_send_cmd( ctx, RTD4_CMD_START_SYNC );

    error_flag = rtd4_wait_drdy( ctx, RTD4_CONV_TIMEOUT_MS );

    if ( RTD4_OK == error_flag )
    {
        rtd4_flush_rx( ctx );
        rtd4_send_cmd( ctx, RTD4_CMD_RDATA );
        error_flag = rtd4_read_bytes( ctx, rx_buf, RTD4_CMD_RDATA_SIZE, RTD4_DATA_READ_TIMEOUT_MS );
    }

    if ( RTD4_OK == error_flag )
    {
        // ADS122U04 returns conversion data LSB first, then middle byte and MSB.
        raw_data  = ( uint32_t ) rx_buf[ RTD4_RDATA_MSB_BYTE ] << RTD4_ADC_MSB_SHIFT;
        raw_data |= ( uint32_t ) rx_buf[ RTD4_RDATA_MID_BYTE ] << RTD4_ADC_MID_SHIFT;
        raw_data |= ( uint32_t ) rx_buf[ RTD4_RDATA_LSB_BYTE ];

        if ( raw_data & RTD4_ADC_SIGN_BIT )
        {
            raw_data |= RTD4_ADC_SIGN_EXT;
        }

        *adc_data = ( int32_t ) raw_data;
    }

    return error_flag;
}

err_t rtd4_read_res ( rtd4_t *ctx, float *resistance )
{
    err_t error_flag = RTD4_OK;
    int32_t adc_data = 0;

    error_flag = rtd4_read_raw( ctx, &adc_data );

    if ( RTD4_OK == error_flag )
    {
        /* For the 3-wire ratiometric circuit:
           code / 2^23 = RTD resistance * gain / ( 2 * reference resistor ). */
        *resistance = ( float ) adc_data;
        *resistance /= RTD4_ADC_FULL_SCALE;
        *resistance *= ( RTD4_RTD_REF_FACTOR * RTD4_REF_RESISTOR_OHM );
        *resistance /= RTD4_RTD_GAIN;
    }

    return error_flag;
}

err_t rtd4_read_temp ( rtd4_t *ctx, float *temperature, float *resistance )
{
    err_t error_flag = RTD4_OK;

    error_flag = rtd4_read_res( ctx, resistance );

    if ( RTD4_OK == error_flag )
    {
        *temperature = ( *resistance - RTD4_PT100_R0_OHM ) / RTD4_PT100_ALPHA;
    }

    return error_flag;
}

static void rtd4_flush_rx ( rtd4_t *ctx )
{
    uint8_t dummy = 0;

    // Clear stale UART bytes before register or conversion data reads.
    while ( 0 < rtd4_generic_read( ctx, &dummy, 1 ) );
}

static err_t rtd4_read_bytes ( rtd4_t *ctx, uint8_t *data_out, uint8_t len, uint16_t timeout_ms )
{
    err_t error_flag = RTD4_ERROR;
    uint8_t cnt = 0;
    uint16_t timeout_cnt = timeout_ms;

    while ( timeout_cnt-- )
    {
        if ( 0 < rtd4_generic_read( ctx, &data_out[ cnt ], 1 ) )
        {
            if ( ++cnt == len )
            {
                error_flag = RTD4_OK;
                timeout_cnt = 0;
            }
        }
        else
        {
            Delay_1ms( );
        }
    }

    return error_flag;
}

static err_t rtd4_wait_drdy ( rtd4_t *ctx, uint16_t timeout_ms )
{
    err_t error_flag = RTD4_ERROR;
    uint16_t timeout_cnt = timeout_ms;

    while ( timeout_cnt-- )
    {
        if ( RTD4_DATA_READY == rtd4_get_drdy( ctx ) )
        {
            error_flag = RTD4_OK;
            timeout_cnt = 0;
        }
        else
        {
            Delay_1ms( );
        }
    }

    return error_flag;
}

static err_t rtd4_check_reg ( rtd4_t *ctx, uint8_t reg, uint8_t expected, uint8_t mask )
{
    err_t error_flag = RTD4_OK;
    uint8_t reg_data = 0;

    error_flag = rtd4_read_reg( ctx, reg, &reg_data );

    if ( RTD4_OK == error_flag )
    {
        if ( ( reg_data & mask ) != ( expected & mask ) )
        {
            error_flag = RTD4_ERROR;
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
