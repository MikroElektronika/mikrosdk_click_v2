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
 * @file adc10.c
 * @brief ADC 10 Click Driver.
 */

#include "adc10.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Configuration delay.
 * @details Configuration delay for 1 milliseconds.
 */
static void dev_config_delay ( void );

/**
 * @brief Reset delay.
 * @details Reset delay for 10 milliseconds.
 */
static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc10_cfg_setup ( adc10_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t adc10_init ( adc10_t *ctx, adc10_cfg_t *cfg ) {
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

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return UART_SUCCESS;
}

void adc10_default_cfg ( adc10_t *ctx ) {
    // Click default configuration
    
    adc10_settings_t stg_tx_data;

    stg_tx_data.input_mux         = ADC10_REG0_MUX_P0_NS;
    stg_tx_data.gain              = ADC10_REG0_GAIN_1;
    stg_tx_data.pga_bypass        = ADC10_REG0_PGA_DISABLED;

    stg_tx_data.data_rate         = ADC10_REG1_DR_NORMAL_20;
    stg_tx_data.op_mode           = ADC10_REG1_MODE_NORMAL;
    stg_tx_data.conv_mode         = ADC10_REG1_CM_SINGAL_SHOT;
    stg_tx_data.vref              = ADC10_REG1_VREF_INTERNAL_2048;
    stg_tx_data.temp_sensor       = ADC10_REG1_TS_DISABLED;

    stg_tx_data.conv_drdy         = ADC10_REG2_DRDY_NOT_READY;
    stg_tx_data.data_cnt          = ADC10_REG2_DCNT_DISABLED;
    stg_tx_data.data_integ_check  = ADC10_REG2_CRC_DISABLED;
    stg_tx_data.b_current_src     = ADC10_REG2_BCS_CURRENT_SOURCE_OFF;
    stg_tx_data.idac_current      = ADC10_REG2_IDAC_CURRENT_OFF;

    stg_tx_data.idac1_routing     = ADC10_REG3_L1MUX_DISABLED;
    stg_tx_data.idac2_routing     = ADC10_REG3_L2MUX_DISABLED;
    stg_tx_data.adc_data_out_mode = ADC10_REG3_DATA_MODE_MANUAL;
    
    stg_tx_data.gpio2_ctrl        = ADC10_REG4_GPIO2_DIR_OUTPUT;
    stg_tx_data.gpio1_ctrl        = ADC10_REG4_GPIO1_DIR_OUTPUT;
    stg_tx_data.gpio0_ctrl        = ADC10_REG4_GPIO0_DIR_OUTPUT;
    stg_tx_data.gpio2_drdy_ctrl   = ADC10_REG4_GPIO2_SEL_DRDY;
    stg_tx_data.gpio2_io_lvl      = ADC10_REG4_GPIO_LOW;
    stg_tx_data.gpio1_io_lvl      = ADC10_REG4_GPIO_LOW;
    stg_tx_data.gpio0_io_lvl      = ADC10_REG4_GPIO_LOW;

    adc10_set_config( ctx, stg_tx_data );
}

err_t adc10_generic_write ( adc10_t *ctx, char *data_buf, uint16_t len ) {
    return uart_write( &ctx->uart, data_buf, len );
}

err_t adc10_generic_read ( adc10_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

void adc10_hw_reset ( adc10_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

uint8_t adc10_check_drdy ( adc10_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

void adc10_send_command ( adc10_t *ctx, uint8_t cmd ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ADC10_SYNC_WORD;
    tx_buf[ 1 ] = cmd;

    adc10_generic_write( ctx, tx_buf, 2 );
}

void adc10_reset ( adc10_t *ctx ) {
    adc10_send_command( ctx, ADC10_CMD_RESET );
}

void adc10_start_sync ( adc10_t *ctx ) {
    adc10_send_command( ctx, ADC10_CMD_START );
}

void adc10_shutdown ( adc10_t *ctx ) {
    adc10_send_command( ctx, ADC10_CMD_POWERDOWN );
}

void adc10_write_reg ( adc10_t *ctx, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 3 ];

    reg <<= 1;
    reg &= ADC10_REG_BITS;

    tx_buf[ 0 ] = ADC10_SYNC_WORD;
    tx_buf[ 1 ] = ADC10_CMD_WREG;
    tx_buf[ 1 ] |= reg;
    tx_buf[ 2 ] = tx_data;

    adc10_generic_write( ctx, tx_buf, 3 );
}

uint8_t adc10_read_reg ( adc10_t *ctx, uint8_t reg ) {
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 1 ];

    reg <<= 1;
    reg &= ADC10_REG_BITS;

    tx_buf[ 0 ] = ADC10_SYNC_WORD;
    tx_buf[ 1 ] = ADC10_CMD_RREG;
    tx_buf[ 1 ] |= reg;

    adc10_generic_write( ctx, tx_buf, 2 );
    adc10_generic_read( ctx, rx_buf, 1 );

    return rx_buf[ 0 ];
}

int32_t adc10_get_ch_output ( adc10_t *ctx, uint8_t sel_ch ) {
    uint8_t rx_buf[ 3 ];
    uint32_t result;
    int32_t adc_res;
    uint8_t tmp;

    switch ( sel_ch ) {
        case ADC10_ANALOG_INPUT_CH_0: {
            tmp = ADC10_REG0_MUX_P0_NS;
            break;
        }
        case ADC10_ANALOG_INPUT_CH_1: {
            tmp = ADC10_REG0_MUX_P1_NS;
            break;
        }
        case ADC10_ANALOG_INPUT_CH_2: {
            tmp = ADC10_REG0_MUX_P2_NS;
            break;
        }
        case ADC10_ANALOG_INPUT_CH_3: {
            tmp = ADC10_REG0_MUX_P3_NS;
            break;
        }
        default: {
            tmp = ADC10_REG0_MUX_P0_NS;
            break;
        }
    }

    tmp <<= 4;
    tmp |= ADC10_REG0_PGA_DISABLED;

    adc10_write_reg( ctx, ADC10_REG_CONFIG_0, tmp );
    dev_reset_delay( );
    
    while ( adc10_check_drdy( ctx ) == ADC10_NEW_DATA_NOT_READY );

    adc10_send_command( ctx, ADC10_CMD_RDATA );

    while ( adc10_check_drdy( ctx ) == ADC10_NEW_DATA_IS_READY );
    
    adc10_generic_read( ctx, rx_buf, 3 );
    dev_config_delay( );

    result = rx_buf[ 2 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];
    result <<= 8;

    adc_res = ( int32_t ) result;
    adc_res >>= 8;

    return adc_res;
}

float adc10_calc_voltage ( adc10_t *ctx, int32_t adc_data, float vref, uint8_t gain ) {
    float voltage;

    voltage = ( float ) adc_data;
    voltage *= vref;
    voltage /= ( float ) ADC10_ADC_RESOLUTION;
    voltage /= gain;

    return voltage;
}

void adc10_set_config ( adc10_t *ctx, adc10_settings_t stg_data ) {
    uint8_t temp;

    temp  = ( stg_data.input_mux & 0x0F )         << 4;
    temp |= ( stg_data.gain & 0x07 )              << 1;
    temp |= ( stg_data.pga_bypass & 0x01 );

    adc10_write_reg( ctx, ADC10_REG_CONFIG_0, temp );
    dev_config_delay( );

    temp  = ( stg_data.data_rate & 0x03 )         << 6;
    temp |= ( stg_data.op_mode & 0x01 )           << 4;
    temp |= ( stg_data.conv_mode & 0x01 )         << 3;
    temp |= ( stg_data.vref & 0x03 )              << 1;
    temp |= ( stg_data.temp_sensor & 0x01 );

    adc10_write_reg( ctx, ADC10_REG_CONFIG_1, temp );
    dev_config_delay( );

    temp  = ( stg_data.conv_drdy & 0x01 )         << 7;
    temp |= ( stg_data.data_cnt & 0x01 )          << 6;
    temp |= ( stg_data.data_integ_check & 0x03 )  << 4;
    temp |= ( stg_data.b_current_src & 0x01 )     << 2;
    temp |= ( stg_data.idac_current & 0x07 );

    adc10_write_reg( ctx, ADC10_REG_CONFIG_2, temp );
    dev_config_delay( );

    temp  = ( stg_data.idac1_routing & 0x07 )     << 5;
    temp |= ( stg_data.idac2_routing & 0x07 )     << 2;
    temp |= ( stg_data.adc_data_out_mode & 0x01 );

    adc10_write_reg( ctx, ADC10_REG_CONFIG_3, temp );
    dev_config_delay( );

    temp  = ( stg_data.gpio2_ctrl & 0x01 )        << 6;
    temp |= ( stg_data.gpio1_ctrl & 0x01 )        << 5;
    temp |= ( stg_data.gpio0_ctrl & 0x01 )        << 4;
    temp |= ( stg_data.gpio2_drdy_ctrl & 0x01 )   << 3;
    temp |= ( stg_data.gpio2_io_lvl & 0x01 )      << 2;
    temp |= ( stg_data.gpio1_io_lvl & 0x01 )      << 1;
    temp |= ( stg_data.gpio0_io_lvl & 0x01 );

    adc10_write_reg( ctx, ADC10_REG_CONFIG_4, temp );
    dev_config_delay( );
}

void adc10_get_config ( adc10_t *ctx, adc10_settings_t *stg_data ) {
    uint8_t temp;

    temp = adc10_read_reg( ctx, ADC10_REG_CONFIG_0 );

    stg_data->input_mux         = ( temp >> 4 ) & 0x0F;
    stg_data->gain              = ( temp >> 1 ) & 0x07;
    stg_data->pga_bypass        =   temp        & 0x01;

    temp = adc10_read_reg( ctx, ADC10_REG_CONFIG_1 );

    stg_data->data_rate         = ( temp >> 6 ) & 0x03;
    stg_data->op_mode           = ( temp >> 4 ) & 0x01;
    stg_data->conv_mode         = ( temp >> 3 ) & 0x01;
    stg_data->vref              = ( temp >> 1 ) & 0x03;
    stg_data->temp_sensor       =   temp        & 0x01;

    temp = adc10_read_reg( ctx, ADC10_REG_CONFIG_2 );

    stg_data->conv_drdy         = ( temp >> 7 ) & 0x01;
    stg_data->data_cnt          = ( temp >> 6 ) & 0x01;
    stg_data->data_integ_check  = ( temp >> 4 ) & 0x03;
    stg_data->b_current_src     = ( temp >> 2 ) & 0x01;
    stg_data->idac_current      =   temp        & 0x07;

    temp = adc10_read_reg( ctx, ADC10_REG_CONFIG_2 );

    stg_data->idac1_routing     = ( temp >> 5 ) & 0x07;
    stg_data->idac2_routing     = ( temp >> 2 ) & 0x07;
    stg_data->adc_data_out_mode =   temp        & 0x01;

    temp = adc10_read_reg( ctx, ADC10_REG_CONFIG_3 );

    stg_data->gpio2_ctrl        = ( temp >> 6 ) & 0x01;
    stg_data->gpio1_ctrl        = ( temp >> 5 ) & 0x01;
    stg_data->gpio0_ctrl        = ( temp >> 4 ) & 0x01;
    stg_data->gpio2_drdy_ctrl   = ( temp >> 3 ) & 0x01;
    stg_data->gpio2_io_lvl      = ( temp >> 2 ) & 0x01;
    stg_data->gpio1_io_lvl      = ( temp >> 1 ) & 0x01;
    stg_data->gpio0_io_lvl      =   temp        & 0x01;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_config_delay ( void ) {
    Delay_1ms( );   
}

static void dev_reset_delay ( void ) {
    Delay_10ms( );   
}

// ------------------------------------------------------------------------- END
