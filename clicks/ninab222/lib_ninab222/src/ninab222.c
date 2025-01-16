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
 * @file ninab222.c
 * @brief NINA-B222 Click Driver.
 */

#include "ninab222.h"

void ninab222_cfg_setup ( ninab222_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sry = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->io5 = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t ninab222_init ( ninab222_t *ctx, ninab222_cfg_t *cfg ) 
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
    digital_out_init( &ctx->sry, cfg->sry );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->io5, cfg->io5 );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    return UART_SUCCESS;
}

err_t ninab222_generic_write ( ninab222_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ninab222_generic_read ( ninab222_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void ninab222_hw_reset ( ninab222_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

err_t ninab222_write_cmd ( ninab222_t *ctx, uint8_t *command )
{
    ninab222_clear_to_send( ctx, NINAB222_PIN_STATE_HIGH );
    err_t err_flag = ninab222_generic_write( ctx, NINAB222_CMD_AT, 
                                                  strlen( NINAB222_CMD_AT ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_PLUS, 
                                             strlen( NINAB222_PREFIX_SYMBOL_PLUS ) );
    err_flag |= ninab222_generic_write( ctx, command, strlen( command ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_END, 
                                             strlen( NINAB222_PREFIX_SYMBOL_END ) );
    ninab222_clear_to_send( ctx, NINAB222_PIN_STATE_LOW );
    return err_flag;
}

err_t ninab222_write_sys_cmd ( ninab222_t *ctx, uint8_t *command )
{
    ninab222_clear_to_send( ctx, NINAB222_PIN_STATE_HIGH );
    err_t err_flag = ninab222_generic_write( ctx, NINAB222_CMD_AT, 
                                                  strlen( NINAB222_CMD_AT ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_AND, 
                                             strlen( NINAB222_PREFIX_SYMBOL_AND ) );
    err_flag |= ninab222_generic_write( ctx, command, strlen( command ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_END, 
                                             strlen( NINAB222_PREFIX_SYMBOL_END ) );
    ninab222_clear_to_send( ctx, NINAB222_PIN_STATE_LOW );
    return err_flag;
}

err_t ninab222_write_cmd_param ( ninab222_t *ctx, uint8_t *command, uint8_t *param )
{
    ninab222_clear_to_send( ctx, NINAB222_PIN_STATE_HIGH );
    err_t err_flag = ninab222_generic_write( ctx, NINAB222_CMD_AT, 
                                                  strlen( NINAB222_CMD_AT ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_PLUS, 
                                             strlen( NINAB222_PREFIX_SYMBOL_PLUS ) );
    err_flag |= ninab222_generic_write( ctx, command, strlen( command ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_SET_VAL, 
                                             strlen( NINAB222_PREFIX_SYMBOL_SET_VAL ) );
    err_flag |= ninab222_generic_write( ctx, param, strlen( param ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_END, 
                                             strlen( NINAB222_PREFIX_SYMBOL_END ) );
    ninab222_clear_to_send( ctx, NINAB222_PIN_STATE_LOW );
    return err_flag;
}

err_t ninab222_inquire_cmd ( ninab222_t *ctx, uint8_t *command ) 
{
    ninab222_clear_to_send( ctx, NINAB222_PIN_STATE_HIGH );
    err_t err_flag = ninab222_generic_write( ctx, NINAB222_CMD_AT, strlen( NINAB222_CMD_AT ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_PLUS, 
                                             strlen( NINAB222_PREFIX_SYMBOL_PLUS ) );
    err_flag |= ninab222_generic_write( ctx, command, strlen( command ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_QUERY, 
                                             strlen( NINAB222_PREFIX_SYMBOL_QUERY ) );
    err_flag |= ninab222_generic_write( ctx, NINAB222_PREFIX_SYMBOL_END, 
                                             strlen( NINAB222_PREFIX_SYMBOL_END ) );
    ninab222_clear_to_send( ctx, NINAB222_PIN_STATE_LOW );
    return err_flag;
}

err_t ninab222_rst_def_cfg ( ninab222_t *ctx )
{
    err_t err_flag = ninab222_write_cmd( ctx, NINAB222_CMD_UFACTORY );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_write_cmd( ctx, NINAB222_CMD_CPWROFF );
    return err_flag;
}

err_t ninab222_reboot_dce ( ninab222_t *ctx )
{
    err_t err_flag = ninab222_write_sys_cmd( ctx, NINAB222_CMD_ATW );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_write_cmd( ctx, NINAB222_CMD_CPWROFF );
    return err_flag;
}

err_t ninab222_set_bt_intf ( ninab222_t *ctx )
{
    return ninab222_write_cmd_param( ctx, NINAB222_CMD_UMLA, NINAB222_PREFIX_SYMBOL_ONE );
}

err_t ninab222_set_start_mode ( ninab222_t *ctx, uint8_t start_mode )
{
    err_t err_flag = NINAB222_ERROR;
    if ( NINAB222_MODE_PPP >= start_mode )
    {
        start_mode += NINAB222_ASCII_TABLE_START_NUM;
        err_flag = ninab222_write_cmd_param( ctx, NINAB222_CMD_UMSM, &start_mode );
    }   
    return err_flag;
}

err_t ninab222_get_start_mode ( ninab222_t *ctx )
{
    return ninab222_inquire_cmd( ctx, NINAB222_CMD_UMSM );
}

err_t ninab222_set_enter_mode ( ninab222_t *ctx, uint8_t enter_mode )
{
    err_t err_flag = NINAB222_ERROR;
    if ( NINAB222_MODE_PPP >= enter_mode )
    {
        uint8_t data_buf[ 7 ] = { 0 };
        enter_mode += NINAB222_ASCII_TABLE_START_NUM;
        uint8_t tmp_buf[ 2 ] = { enter_mode, 0 };
        strcpy( data_buf, NINAB222_CMD_ATO );
        strcat( data_buf, tmp_buf );
        strcat( data_buf, NINAB222_PREFIX_SYMBOL_END );
        strcat( data_buf, NINAB222_PREFIX_SYMBOL_END );
        err_flag = ninab222_generic_write( ctx, data_buf, 6 );     
    }
    return err_flag;
}

err_t ninab222_set_echo ( ninab222_t *ctx, uint8_t echo_en )
{
    err_t err_flag = NINAB222_ERROR;
    if ( NINAB222_ECHO_ON >= echo_en )
    {
        uint8_t data_buf[ 7 ] = { 0 };
        echo_en += NINAB222_ASCII_TABLE_START_NUM;
        uint8_t tmp_buf[ 2 ] = { echo_en, 0 };
        strcpy( data_buf, NINAB222_CMD_ATE );
        strcat( data_buf, tmp_buf );
        strcat( data_buf, NINAB222_PREFIX_SYMBOL_END );
        strcat( data_buf, NINAB222_PREFIX_SYMBOL_END );
        err_flag = ninab222_generic_write( ctx, data_buf, 6 );
    }
    return err_flag;
}

err_t ninab222_set_device_name ( ninab222_t *ctx, uint8_t *device_name )
{
    uint8_t data_buf[ NINAB222_TX_DRV_BUFFER_SIZE ] = { 0 };
    strcpy( data_buf, NINAB222_PREFIX_SYMBOL_QUOTE );
    strcat( data_buf, device_name );
    strcat( data_buf, NINAB222_PREFIX_SYMBOL_QUOTE );
    return ninab222_write_cmd_param( ctx, NINAB222_CMD_UBTLN, data_buf ); 
}

err_t ninab222_get_device_name ( ninab222_t *ctx )
{
    return ninab222_inquire_cmd( ctx, NINAB222_CMD_UBTLN );
}

err_t ninab222_set_le_role ( ninab222_t *ctx, uint8_t le_role )
{
    err_t err_flag = NINAB222_ERROR;
    if ( NINAB222_LR_ROLE_SIMULTANEOUS >= le_role )
    {
        uint8_t data_buf[ 1 ] = { le_role + NINAB222_ASCII_TABLE_START_NUM };
        err_flag = ninab222_write_cmd_param( ctx, NINAB222_CMD_UBTLE, data_buf );
    }
    return err_flag;
}

err_t ninab222_get_le_role ( ninab222_t *ctx )
{
    return ninab222_inquire_cmd( ctx, NINAB222_CMD_UBTLE );
}

err_t ninab222_get_peers_list ( ninab222_t *ctx )
{
    return ninab222_inquire_cmd( ctx, NINAB222_CMD_UDLP );
}

err_t ninab222_set_default_cfg ( ninab222_t *ctx )
{
    uint8_t data_buf[ 5 ] = { 0 };
    strcpy( data_buf, NINAB222_CMD_ATZ );
    strcat( data_buf, NINAB222_PREFIX_SYMBOL_END );
    err_t err_flag = ninab222_generic_write( ctx, data_buf, 5 );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_write_cmd( ctx, NINAB222_CMD_CPWROFF );
    return err_flag;
}

err_t ninab222_set_pairing_mode ( ninab222_t *ctx, uint8_t p_mode )
{
    err_t err_flag = NINAB222_ERROR;
    if ( NINAB222_GAP_MODE_PAIRING >= p_mode )
    {
        uint8_t data_buf[ 1 ] = { p_mode + NINAB222_ASCII_TABLE_START_NUM };
        err_flag = ninab222_write_cmd_param( ctx, NINAB222_CMD_UBTPM, data_buf );
    }
    return err_flag;
}

err_t ninab222_set_connectability ( ninab222_t *ctx, uint8_t c_mode )
{
    err_t err_flag = NINAB222_ERROR;
    if ( ( NINAB222_GAP_MODE_NON_CONN == c_mode ) || ( NINAB222_GAP_MODE_CONN == c_mode ) )
    {
        uint8_t data_buf[ 1 ] = { c_mode + NINAB222_ASCII_TABLE_START_NUM };
        err_flag = ninab222_write_cmd_param( ctx, NINAB222_CMD_UBTCM, data_buf );
    }
    return err_flag;
}

err_t ninab222_get_connectability ( ninab222_t *ctx )
{
    return ninab222_inquire_cmd( ctx, NINAB222_CMD_UBTCM );
}

err_t ninab222_set_discoverability ( ninab222_t *ctx, uint8_t d_mode )
{
    err_t err_flag = NINAB222_ERROR;
    if ( ( NINAB222_GAP_MODE_GEN_DISC >= d_mode ) && ( NINAB222_GAP_MODE_NON_DIS <= d_mode ) )
    {
        uint8_t data_buf[ 1 ] = { d_mode + NINAB222_ASCII_TABLE_START_NUM };
        err_flag = ninab222_write_cmd_param( ctx, NINAB222_CMD_UBTDM, data_buf );
    }
    return err_flag;
}

err_t ninab222_get_discoverability ( ninab222_t *ctx )
{
    return ninab222_inquire_cmd( ctx, NINAB222_CMD_UBTDM );
}

err_t ninab222_get_info ( ninab222_t *ctx )
{
    err_t err_flag = ninab222_write_cmd( ctx, NINAB222_CMD_GMI );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_write_cmd( ctx, NINAB222_CMD_GMM );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_write_cmd( ctx, NINAB222_CMD_GMR );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_write_cmd( ctx, NINAB222_CMD_GSN );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_inquire_cmd( ctx, NINAB222_CMD_UMRS );
    return err_flag;
}

err_t ninab222_remote_peer ( ninab222_t *ctx, uint8_t *domain )
{
    uint8_t data_buf[ NINAB222_TX_DRV_BUFFER_SIZE ] = { 0 };
    err_t err_flag = ninab222_set_le_role( ctx, NINAB222_LR_ROLE_CENTRAL );
    Delay_10ms( );
    Delay_10ms( ); 
    strcpy( data_buf, NINAB222_PREFIX_SYMBOL_ZERO );
    strcat( data_buf, NINAB222_PREFIX_SYMBOL_SEPARATOR );
    strcat( data_buf, NINAB222_PREFIX_SYMBOL_SPS );
    strcat( data_buf, domain );
    strcat( data_buf, NINAB222_PREFIX_SYMBOL_SEPARATOR );
    strcat( data_buf, NINAB222_PREFIX_SYMBOL_TWO );
    strcat( data_buf, NINAB222_PREFIX_SYMBOL_QUOTE );
    err_flag |= ninab222_write_cmd_param( ctx, NINAB222_CMD_UDDRP, data_buf );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_set_start_mode( ctx, NINAB222_MODE_DATA );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_reboot_dce( ctx );
    return err_flag;
}

err_t ninab222_periph_pairing_cfg ( ninab222_t *ctx )
{
    err_t err_flag = ninab222_set_le_role( ctx, NINAB222_LR_ROLE_PERIPHERAL );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_set_start_mode( ctx, NINAB222_MODE_DATA );
    Delay_10ms( );
    Delay_10ms( );
    err_flag |= ninab222_reboot_dce( ctx );
    return err_flag;
}

void ninab222_clear_to_send ( ninab222_t *ctx, uint8_t cts )
{
    digital_out_write( &ctx->cs, cts );
}

uint8_t ninab222_request_to_send ( ninab222_t *ctx )
{
    return digital_in_read( &ctx->rts );
}

void ninab222_set_sry_pin ( ninab222_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->sry, state );
}

void ninab222_set_io5_pin ( ninab222_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->io5, state );
}


// ------------------------------------------------------------------------- END
