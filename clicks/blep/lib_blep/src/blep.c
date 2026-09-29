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
 * @file blep.c
 * @brief BLE P Click Driver.
 */

#include "blep.h"
#include "blep_setup.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                               0x00

/** Maximum RDYN handshake and setup response wait, in milliseconds. */
#define BLEP_READY_TIMEOUT_MS               2000

/**
 * @brief BLE P bit reversal function.
 * @details This function converts a BLE P Click byte between MSB-first SPI and LSB-first ACI order.
 * @param[in] value : Byte to reverse.
 * @return Byte with reversed bit order.
 * @note None.
 */
static uint8_t blep_reverse_byte ( uint8_t value );

/**
 * @brief BLE P ACI transfer function.
 * @details This function exchanges a BLE P Click packet using the REQN/RDYN handshake.
 * @param[in] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] packet : Length-prefixed command, or NULL for an event-only transfer.
 * @param[out] evt : Simultaneously received event.
 * See #blep_event_t object definition for detailed explanation.
 * @return BLEP_OK, or a negative transport, length, or timeout error.
 * @note The first received byte is the SPI status, not the event length.
 */
static err_t blep_transfer ( blep_t *ctx, uint8_t *packet, blep_event_t *evt );

/**
 * @brief BLE P event state update function.
 * @details This function validates BLE P Click event lengths and updates the connection and credit state.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] evt : Received event.
 * See #blep_event_t object definition for detailed explanation.
 * @return BLEP_OK, or BLEP_ERROR_RESPONSE for a malformed or hardware error event.
 * @note None.
 */
static err_t blep_update_state ( blep_t *ctx, blep_event_t *evt );

/**
 * @brief BLE P setup response waiting function.
 * @details This function waits for the BLE P Click response to one setup packet.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] expected_status : Expected CONTINUE or COMPLETE status.
 * @return BLEP_OK, or a negative error.
 * @note Consumes setup events; call only while loading the profile before advertising.
 */
static err_t blep_wait_setup_response ( blep_t *ctx, uint8_t expected_status );

void blep_cfg_setup ( blep_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->act  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t blep_init ( blep_t *ctx, blep_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->act, cfg->act );
    digital_in_init( &ctx->rdy, cfg->rdy );

    // Clear protocol state before the application waits for DeviceStarted.
    blep_reset ( ctx );

    return SPI_MASTER_SUCCESS;
}

void blep_reset ( blep_t *ctx )
{
    spi_master_deselect_device( ctx->chip_select );
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );

    ctx->event_head = 0;
    ctx->event_count = 0;
    ctx->device_mode = 0;
    ctx->connected = 0;
    ctx->credits = 0;
    ctx->total_credits = 0;
    memset( ctx->open_pipes, 0, 8 );
}

err_t blep_write_command ( blep_t *ctx, uint8_t command, uint8_t *param_in, uint8_t len )
{
    uint8_t packet[ BLEP_PACKET_SIZE + 1 ];
    blep_event_t evt;
    err_t error_flag = BLEP_ERROR;

    if ( ( len < BLEP_PACKET_SIZE ) && ( ( 0 == len ) || ( NULL != param_in ) ) )
    {
        if ( ctx->event_count >= BLEP_EVENT_QUEUE_SIZE )
        {
            error_flag = BLEP_BUSY;
        }
        else
        {
            packet[ 0 ] = len + 1;
            packet[ 1 ] = command;
            if ( len )
            {
                memcpy( &packet[ 2 ], param_in, len );
            }
            error_flag = blep_transfer( ctx, packet, &evt );
            if ( ( BLEP_OK == error_flag ) && evt.len )
            {
                // Preserve events received during the command write for the next read_event call.
                ctx->events[ ( ctx->event_head + ctx->event_count ) % BLEP_EVENT_QUEUE_SIZE ] = evt;
                ctx->event_count++;
            }
        }
    }
    return error_flag;
}

err_t blep_run_command ( blep_t *ctx, uint8_t command )
{
    return blep_write_command( ctx, command, NULL, 0 );
}

err_t blep_read_event ( blep_t *ctx, blep_event_t *evt )
{
    err_t error_flag = BLEP_NO_EVENT;

    memset( evt, 0, sizeof( blep_event_t ) );
    // Return queued events first so command-time events are handled before new SPI data.
    if ( ctx->event_count )
    {
        *evt = ctx->events[ ctx->event_head ];
        ctx->event_head = ( ctx->event_head + 1 ) % BLEP_EVENT_QUEUE_SIZE;
        ctx->event_count--;
        error_flag = BLEP_OK;
    }
    else if ( 0 == blep_get_ready( ctx ) )
    {
        error_flag = blep_transfer( ctx, NULL, evt );
        if ( ( BLEP_OK == error_flag ) && ( 0 == evt->len ) )
        {
            error_flag = BLEP_NO_EVENT;
        }
    }
    if ( BLEP_OK == error_flag )
    {
        error_flag = blep_update_state( ctx, evt );
    }
    return error_flag;
}

err_t blep_uart_cfg ( blep_t *ctx )
{
    uint8_t idx;
    uint8_t status;
    uint16_t elapsed;
    blep_event_t evt;
    err_t error_flag = BLEP_ERROR;

    if ( BLEP_MODE_SETUP == ctx->device_mode )
    {
        error_flag = BLEP_OK;
        for ( idx = 0; ( idx < BLEP_SETUP_MESSAGES ) && ( BLEP_OK == error_flag ); idx++ )
        {
            error_flag = blep_write_command( ctx, BLEP_CMD_SETUP, &blep_setup[ idx ][ 2 ], blep_setup[ idx ][ 0 ] - 1 );
            if ( BLEP_OK == error_flag )
            {
                status = ( idx + 1 == BLEP_SETUP_MESSAGES ) ? BLEP_STATUS_COMPLETE : BLEP_STATUS_CONTINUE;
                error_flag = blep_wait_setup_response( ctx, status );
            }
        }
        for ( elapsed = 0; ( elapsed < BLEP_READY_TIMEOUT_MS ) && ( BLEP_OK == error_flag ) &&
              ( BLEP_MODE_STANDBY != ctx->device_mode ); elapsed++ )
        {
            error_flag = blep_read_event( ctx, &evt );
            if ( BLEP_NO_EVENT == error_flag )
            {
                error_flag = BLEP_OK;
            }
            Delay_1ms( );
        }
        if ( ( BLEP_OK == error_flag ) && ( BLEP_MODE_STANDBY != ctx->device_mode ) )
        {
            error_flag = BLEP_ERROR_TIMEOUT;
        }
    }
    return error_flag;
}

err_t blep_set_local_data ( blep_t *ctx, uint8_t pipe, uint8_t *data_in, uint8_t len )
{
    uint8_t param[ BLEP_UART_DATA_SIZE + 1 ];
    err_t error_flag = BLEP_ERROR;

    if ( ( pipe > 0 ) && ( pipe <= 62 ) && ( len <= BLEP_UART_DATA_SIZE ) &&
         ( ( 0 == len ) || ( NULL != data_in ) ) )
    {
        param[ 0 ] = pipe;
        if ( len )
        {
            memcpy( &param[ 1 ], data_in, len );
        }
        error_flag = blep_write_command( ctx, BLEP_CMD_SET_LOCAL_DATA, param, len + 1 );
    }
    return error_flag;
}

err_t blep_start_advertising ( blep_t *ctx, uint16_t timeout, uint16_t interval )
{
    uint8_t param[ 4 ];
    err_t error_flag = BLEP_ERROR;

    if ( ( timeout <= 16383 ) && ( interval >= 32 ) && ( interval <= 16384 ) )
    {
        param[ 0 ] = ( uint8_t ) timeout;
        param[ 1 ] = ( uint8_t ) ( timeout >> 8 );
        param[ 2 ] = ( uint8_t ) interval;
        param[ 3 ] = ( uint8_t ) ( interval >> 8 );
        error_flag = blep_write_command( ctx, BLEP_CMD_CONNECT, param, 4 );
    }
    return error_flag;
}

err_t blep_disconnect ( blep_t *ctx )
{
    uint8_t reason = BLEP_DISCONNECT_TERMINATE;

    return blep_write_command( ctx, BLEP_CMD_DISCONNECT, &reason, 1 );
}

err_t blep_send_data ( blep_t *ctx, uint8_t pipe, uint8_t *data_in, uint8_t len )
{
    uint8_t param[ BLEP_UART_DATA_SIZE + 1 ];
    err_t error_flag = BLEP_ERROR;

    if ( ( NULL != data_in ) && ( len > 0 ) && ( len <= BLEP_UART_DATA_SIZE ) &&
         ctx->connected && blep_is_pipe_open( ctx, pipe ) )
    {
        error_flag = BLEP_BUSY;
        if ( ctx->credits )
        {
            param[ 0 ] = pipe;
            memcpy( &param[ 1 ], data_in, len );
            error_flag = blep_write_command( ctx, BLEP_CMD_SEND_DATA, param, len + 1 );
            if ( BLEP_OK == error_flag )
            {
                // This credit is replenished later by a DataCredit event.
                ctx->credits--;
            }
        }
    }
    return error_flag;
}

uint8_t blep_is_pipe_open ( blep_t *ctx, uint8_t pipe )
{
    uint8_t open = 0;

    if ( ( pipe > 0 ) && ( pipe <= 62 ) )
    {
        open = ( ctx->open_pipes[ pipe / 8 ] >> ( pipe % 8 ) ) & 1;
    }
    return open;
}

uint8_t blep_get_ready ( blep_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

uint8_t blep_get_activity ( blep_t *ctx )
{
    return digital_in_read( &ctx->act );
}

static uint8_t blep_reverse_byte ( uint8_t value )
{
    value = ( ( value & 0xF0 ) >> 4 ) | ( ( value & 0x0F ) << 4 );
    value = ( ( value & 0xCC ) >> 2 ) | ( ( value & 0x33 ) << 2 );
    value = ( ( value & 0xAA ) >> 1 ) | ( ( value & 0x55 ) << 1 );
    return value;
}

static err_t blep_transfer ( blep_t *ctx, uint8_t *packet, blep_event_t *evt )
{
    uint8_t tx_buf[ BLEP_PACKET_SIZE + 2 ] = { 0 };
    uint8_t rx_buf[ BLEP_PACKET_SIZE + 2 ] = { 0 };
    uint8_t tx_len = 0;
    uint8_t transfer_len;
    uint8_t idx;
    uint16_t elapsed = 0;
    err_t error_flag = BLEP_OK;

    memset( evt, 0, sizeof( blep_event_t ) );
    if ( NULL != packet )
    {
        tx_len = packet[ 0 ];
        for ( idx = 0; idx <= tx_len; idx++ )
        {
            tx_buf[ idx ] = blep_reverse_byte( packet[ idx ] );
        }
    }

    spi_master_select_device( ctx->chip_select );
    while ( blep_get_ready( ctx ) && ( elapsed < BLEP_READY_TIMEOUT_MS ) )
    {
        Delay_1ms( );
        elapsed++;
    }
    if ( blep_get_ready( ctx ) )
    {
        error_flag = BLEP_ERROR_TIMEOUT;
    }
    else if ( SPI_MASTER_SUCCESS != spi_master_transfer( &ctx->spi, tx_buf, rx_buf, 2 ) )
    {
        error_flag = BLEP_ERROR;
    }
    else
    {
        // First phase exchanges length/opcode and receives status/event length; the second transfers payload.
        evt->len = blep_reverse_byte( rx_buf[ 1 ] );
        if ( evt->len > BLEP_PACKET_SIZE )
        {
            evt->len = 0;
            error_flag = BLEP_ERROR_RESPONSE;
        }
        else
        {
            transfer_len = ( tx_len > 0 ) ? tx_len - 1 : 0;
            if ( evt->len > transfer_len )
            {
                transfer_len = evt->len;
            }
            if ( transfer_len && ( SPI_MASTER_SUCCESS !=
                 spi_master_transfer( &ctx->spi, &tx_buf[ 2 ], &rx_buf[ 2 ], transfer_len ) ) )
            {
                error_flag = BLEP_ERROR;
            }
            else if ( evt->len )
            {
                evt->opcode = blep_reverse_byte( rx_buf[ 2 ] );
                for ( idx = 1; idx < evt->len; idx++ )
                {
                    evt->payload[ idx - 1 ] = blep_reverse_byte( rx_buf[ idx + 2 ] );
                }
            }
        }
    }
    spi_master_deselect_device( ctx->chip_select );
    Delay_1us( );
    return error_flag;
}

static err_t blep_update_state ( blep_t *ctx, blep_event_t *evt )
{
    uint8_t min_len = 1;
    err_t error_flag = BLEP_OK;

    switch ( evt->opcode )
    {
        case BLEP_EVT_DEVICE_STARTED:   min_len = 4;  break;
        case BLEP_EVT_COMMAND_RESPONSE: min_len = 3;  break;
        case BLEP_EVT_CONNECTED:        min_len = 15; break;
        case BLEP_EVT_DISCONNECTED:     min_len = 3;  break;
        case BLEP_EVT_PIPE_STATUS:      min_len = 17; break;
        case BLEP_EVT_DATA_CREDIT:      min_len = 2;  break;
        case BLEP_EVT_DATA_RECEIVED:    min_len = 2;  break;
        case BLEP_EVT_PIPE_ERROR:       min_len = 3;  break;
        default: break;
    }
    if ( ( evt->len < min_len ) || ( BLEP_EVT_HW_ERROR == evt->opcode ) )
    {
        error_flag = BLEP_ERROR_RESPONSE;
    }
    else
    {
        switch ( evt->opcode )
        {
            case BLEP_EVT_DEVICE_STARTED:
            {
                ctx->device_mode = evt->payload[ 0 ];
                ctx->total_credits = evt->payload[ 2 ];
                ctx->connected = 0;
                ctx->credits = 0;
                memset( ctx->open_pipes, 0, 8 );
                if ( evt->payload[ 1 ] )
                {
                    error_flag = BLEP_ERROR_RESPONSE;
                }
                break;
            }
            case BLEP_EVT_CONNECTED:
            {
                ctx->connected = 1;
                ctx->credits = ctx->total_credits;
                memset( ctx->open_pipes, 0, 8 );
                break;
            }
            case BLEP_EVT_DISCONNECTED:
            {
                ctx->connected = 0;
                ctx->credits = 0;
                memset( ctx->open_pipes, 0, 8 );
                break;
            }
            case BLEP_EVT_PIPE_STATUS:
            {
                memcpy( ctx->open_pipes, evt->payload, 8 );
                break;
            }
            case BLEP_EVT_DATA_CREDIT:
            {
                if ( ctx->connected )
                {
                    // Reject duplicate or malformed grants that exceed the startup credit count.
                    if ( evt->payload[ 0 ] <= ctx->total_credits - ctx->credits )
                    {
                        ctx->credits += evt->payload[ 0 ];
                    }
                    else
                    {
                        error_flag = BLEP_ERROR_RESPONSE;
                    }
                }
                break;
            }
            case BLEP_EVT_PIPE_ERROR:
            {
                if ( ctx->connected && ( BLEP_STATUS_PEER_ATT_ERROR != evt->payload[ 1 ] ) &&
                     ( ctx->credits < ctx->total_credits ) )
                {
                    ctx->credits++;
                }
                break;
            }
            default: break;
        }
    }
    return error_flag;
}

static err_t blep_wait_setup_response ( blep_t *ctx, uint8_t expected_status )
{
    uint16_t elapsed;
    blep_event_t evt;
    err_t error_flag = BLEP_OK;
    uint8_t received = 0;

    for ( elapsed = 0; ( elapsed < BLEP_READY_TIMEOUT_MS ) && !received && ( BLEP_OK == error_flag ); elapsed++ )
    {
        error_flag = blep_read_event( ctx, &evt );
        if ( BLEP_NO_EVENT == error_flag )
        {
            error_flag = BLEP_OK;
        }
        else if ( ( BLEP_OK == error_flag ) && ( BLEP_EVT_COMMAND_RESPONSE == evt.opcode ) )
        {
            received = 1;
            if ( ( BLEP_CMD_SETUP != evt.payload[ 0 ] ) || ( expected_status != evt.payload[ 1 ] ) )
            {
                error_flag = BLEP_ERROR_RESPONSE;
            }
        }
        Delay_1ms( );
    }
    if ( ( BLEP_OK == error_flag ) && !received )
    {
        error_flag = BLEP_ERROR_TIMEOUT;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
