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
 * @file skywire.c
 * @brief Skywire Click Driver.
 */

#include "skywire.h"

/**
 * @brief Skywire send command buffer function.
 * @details This function appends the command line termination character to the 
 * command buffer and sends it to the Click module.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
static void skywire_send_cmd_buffer ( skywire_t *ctx );

void skywire_cfg_setup ( skywire_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en    = HAL_PIN_NC;
    cfg->rst   = HAL_PIN_NC;
    cfg->rts   = HAL_PIN_NC;
    cfg->cts   = HAL_PIN_NC;
    cfg->ad1_j = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t skywire_init ( skywire_t *ctx, skywire_cfg_t *cfg ) 
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
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );
    digital_in_init( &ctx->ad1_j, cfg->ad1_j );

    /* Release the modem ON_OFF and RESET lines and set host to ready to receive data */
    digital_out_low( &ctx->en );
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->rts );

    /* Dummy read to enable RX interrupt */
    uint8_t dummy_read = 0;
    uart_read( &ctx->uart, &dummy_read, 1 );
    Delay_100ms( );

    return UART_SUCCESS;
}

err_t skywire_generic_write ( skywire_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t skywire_generic_read ( skywire_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void skywire_set_en_pin ( skywire_t *ctx, uint8_t state )
{
    if ( SKYWIRE_PIN_STATE_HIGH == state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

void skywire_set_rst_pin ( skywire_t *ctx, uint8_t state )
{
    if ( SKYWIRE_PIN_STATE_HIGH == state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void skywire_set_rts_pin ( skywire_t *ctx, uint8_t state )
{
    if ( SKYWIRE_PIN_STATE_HIGH == state )
    {
        digital_out_high( &ctx->rts );
    }
    else
    {
        digital_out_low( &ctx->rts );
    }
}

uint8_t skywire_get_cts ( skywire_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

void skywire_power_on ( skywire_t *ctx )
{
    /*
     * ON_OFF line must be held low for at least 5 seconds and then released
     * to start the modem ( NL-SW-HSPA datasheet, page 10, 3.1 ).
     * EN high pulls ON_OFF low through Q1.
     */
    skywire_set_en_pin( ctx, SKYWIRE_PIN_STATE_HIGH );
    for ( uint8_t cnt = 0; cnt < 5; cnt++ )
    {
        Delay_1sec( );
    }
    Delay_100ms( );
    skywire_set_en_pin( ctx, SKYWIRE_PIN_STATE_LOW );
}

void skywire_hw_shutdown ( skywire_t *ctx )
{
    /* 
     * RESET_nIN line must be held low for 200 ms and then 
     * released ( NL-SW-HSPA datasheet, page 6, pin 5 ). 
     * RST high pulls the RESET_nIN line low through Q2.
     */
    skywire_set_rst_pin( ctx, SKYWIRE_PIN_STATE_HIGH );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    skywire_set_rst_pin( ctx, SKYWIRE_PIN_STATE_LOW );
}

void skywire_cmd_run ( skywire_t *ctx, uint8_t *cmd )
{
    strcpy( ctx->cmd_buffer, cmd );
    skywire_send_cmd_buffer( ctx );
}

void skywire_cmd_set ( skywire_t *ctx, uint8_t *cmd, uint8_t *value )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };

    /* Command line format: AT<cmd>=<value><CR> */
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, value );

    skywire_send_cmd_buffer( ctx );
}

void skywire_cmd_get ( skywire_t *ctx, uint8_t *cmd )
{
    uint8_t check_char[ 2 ] = { '?', 0 };

    /* Command line format: AT<cmd>?<CR> */
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, check_char );

    skywire_send_cmd_buffer( ctx );
}

void skywire_set_sim_apn ( skywire_t *ctx, uint8_t *sim_apn )
{
    uint8_t apn_param[ SKYWIRE_APN_PARAM_BUFFER_SIZE ] = { 0 };

    /* PDP context definition format: AT+CGDCONT=<cid>,"IP","<APN>" */
    strcpy( apn_param, SKYWIRE_PDP_CONTEXT_ID );
    strcat( apn_param, ",\"IP\",\"" );
    strcat( apn_param, sim_apn );
    strcat( apn_param, "\"" );

    skywire_cmd_set( ctx, SKYWIRE_CMD_DEFINE_PDP_CONTEXT, apn_param );
}

void skywire_send_sms_text ( skywire_t *ctx, uint8_t *phone_number, uint8_t *sms_text )
{
    uint8_t sms_param[ SKYWIRE_SMS_PARAM_BUFFER_SIZE ] = { 0 };
    uint8_t sms_ctrl = SKYWIRE_SMS_CTRL_Z;

    /* Text mode command format: AT+CMGS="<da>"<CR>, the modem answers with the "> " prompt */
    strcpy( sms_param, "\"" );
    strcat( sms_param, phone_number );
    strcat( sms_param, "\"" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_SEND_SMS, sms_param );

    /* Wait for the prompt before the message text is sent */
    Delay_1sec( );

    /* The message text is terminated with Ctrl-Z, which sends the message */
    skywire_generic_write( ctx, sms_text, strlen( sms_text ) );
    skywire_generic_write( ctx, &sms_ctrl, 1 );
    Delay_1sec( );
}

static void skywire_send_cmd_buffer ( skywire_t *ctx )
{
    uint8_t cr_char[ 2 ] = { '\r', 0 };

    strcat( ctx->cmd_buffer, cr_char );
    skywire_generic_write( ctx, ctx->cmd_buffer, strlen( ctx->cmd_buffer ) );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
