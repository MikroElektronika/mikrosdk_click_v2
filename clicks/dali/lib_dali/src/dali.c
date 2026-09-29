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
 * @file dali.c
 * @brief DALI Click Driver.
 */

#include "dali.h"

/** Bus-idle polling uses 50 us steps; allow 10 ms of idle within a 100 ms window. */
#define DALI_IDLE_TICKS                         200
#define DALI_BUSY_TIMEOUT_TICKS                 2000

/** Receive polling uses 10 us steps, including margin for GPIO and optocoupler delays. */
#define DALI_RESPONSE_TIMEOUT_TICKS             1200
#define DALI_START_MIN_TICKS                    25
#define DALI_START_MAX_TICKS                    60
#define DALI_EDGE_MIN_TICKS                     5
#define DALI_EDGE_MAX_TICKS                     45
#define DALI_STOP_TICKS                         170

/**
 * @brief DALI wait idle function.
 * @details This function waits for an idle receive input before starting a forward frame.
 * It restarts the idle count on bus activity and bounds the overall wait.
 * @param[in] ctx : Click context object.
 * See #dali_t object definition for detailed explanation.
 * @return @li @c DALI_OK - Bus is idle and ready,
 *         @li @c DALI_ERROR_BUSY - Receive input did not remain idle.
 * See #dali_return_value_t definition for detailed explanation.
 * @note None.
 */
static err_t dali_wait_idle ( dali_t *ctx );

/**
 * @brief DALI delay half bit function.
 * @details This function combines fixed delay primitives for approximately 416.7 us,
 * excluding call overhead.
 * @return None.
 * @note None.
 */
static void dali_delay_half_bit ( void );

/**
 * @brief DALI send bit function.
 * @details This function transmits one Manchester-encoded bit through the active-low TX interface.
 * @param[in] ctx : Click context object.
 * See #dali_t object definition for detailed explanation.
 * @param[in] bit_value : Logical bit value, 0 or 1.
 * @return None.
 * @note None.
 */
static void dali_send_bit ( dali_t *ctx, uint8_t bit_value );

/**
 * @brief DALI encode address function.
 * @details This function encodes the destination without setting the command selector bit.
 * @param[in] address : Short or group address; ignored for broadcast.
 * @param[in] address_type : Destination addressing mode.
 * @param[out] encoded_address : Encoded address byte; unchanged if validation fails.
 * @return @li @c DALI_OK - Address encoded,
 *         @li @c DALI_ERROR - Unsupported type or out-of-range address.
 * See #dali_return_value_t definition for detailed explanation.
 * @note None.
 */
static err_t dali_encode_address ( uint8_t address, uint8_t address_type, uint8_t *encoded_address );

/**
 * @brief DALI read receive pin function.
 * @details This function reads only the receive input selected during initialization.
 * @param[in] ctx : Click context object.
 * See #dali_t object definition for detailed explanation.
 * @return @li @c DALI_PIN_IDLE - Receive input is high,
 *         @li @c DALI_PIN_ACTIVE - Receive input is low.
 * @note The INT/ICP jumper must match ctx->rx_sel. An idle level does not confirm bus power.
 */
static uint8_t dali_read_rx ( dali_t *ctx );

void dali_cfg_setup ( dali_cfg_t *cfg ) 
{
    cfg->tx_pin = HAL_PIN_NC;
    cfg->phy = HAL_PIN_NC;
    cfg->icp_rx = HAL_PIN_NC;
    cfg->int_rx = HAL_PIN_NC;
    cfg->rx_sel = DALI_RX_INT;
}

err_t dali_init ( dali_t *ctx, dali_cfg_t *cfg ) 
{
    err_t error_flag = DALI_ERROR;

    if ( ( DALI_RX_INT == cfg->rx_sel ) || ( DALI_RX_ICP == cfg->rx_sel ) )
    {
        if ( DIGITAL_OUT_SUCCESS == digital_out_init( &ctx->tx_pin, cfg->tx_pin ) )
        {
            // TX high turns the transmit optocoupler off and releases the bus.
            digital_out_write( &ctx->tx_pin, DALI_PIN_IDLE );
            ctx->rx_sel = cfg->rx_sel;
            if ( DALI_RX_INT == ctx->rx_sel )
            {
                error_flag = digital_in_init( &ctx->int_rx, cfg->int_rx );
            }
            else
            {
                error_flag = digital_in_init( &ctx->icp_rx, cfg->icp_rx );
            }
            if ( DIGITAL_IN_SUCCESS == error_flag )
            {
                error_flag = digital_in_init( &ctx->phy, cfg->phy );
            }

            // Map GPIO-specific errors to the Click driver's return values.
            if ( DIGITAL_IN_SUCCESS == error_flag )
            {
                error_flag = DALI_OK;
            }
            else
            {
                error_flag = DALI_ERROR;
            }
        }
    }

    return error_flag;
}

err_t dali_default_cfg ( dali_t *ctx ) 
{
    digital_out_write( &ctx->tx_pin, DALI_PIN_IDLE );
    return dali_wait_idle( ctx );
}

err_t dali_generic_write ( dali_t *ctx, uint8_t address, uint8_t data_in )
{
    err_t error_flag = dali_wait_idle( ctx );
    uint16_t frame = ( ( uint16_t ) address << 8 ) | data_in;
    uint8_t bit_index;

    if ( DALI_OK == error_flag )
    {
        // A logical one starts the frame, followed by address and data, MSB first.
        dali_send_bit( ctx, 1 );
        for ( bit_index = 0; bit_index < 16; bit_index++ )
        {
            dali_send_bit( ctx, ( uint8_t ) ( frame >> 15 ) );
            frame <<= 1;
        }

        // Stop bits are an idle bus, not Manchester-encoded zero bits.
        digital_out_write( &ctx->tx_pin, DALI_PIN_IDLE );
        for ( bit_index = 0; bit_index < 4; bit_index++ )
        {
            dali_delay_half_bit( );
        }
    }

    return error_flag;
}

err_t dali_read_response ( dali_t *ctx, uint8_t *data_out )
{
    err_t error_flag = DALI_OK;
    uint16_t elapsed = 0;
    uint8_t received = 0;
    uint8_t first_half;
    uint8_t bit_index;

    if ( !data_out )
    {
        error_flag = DALI_ERROR;
    }
    else
    {
        // A backward frame starts with RX low; the idle input is high.
        while ( ( DALI_PIN_IDLE == dali_read_rx( ctx ) ) &&
                ( elapsed < DALI_RESPONSE_TIMEOUT_TICKS ) )
        {
            Delay_10us( );
            elapsed++;
        }
        if ( elapsed == DALI_RESPONSE_TIMEOUT_TICKS )
        {
            error_flag = DALI_ERROR_TIMEOUT;
        }
    }

    if ( DALI_OK == error_flag )
    {
        // Validate the first half of the start bit and synchronize to its rising edge.
        elapsed = 0;
        while ( ( DALI_PIN_ACTIVE == dali_read_rx( ctx ) ) &&
                ( elapsed < DALI_START_MAX_TICKS ) )
        {
            Delay_10us( );
            elapsed++;
        }
        if ( ( elapsed < DALI_START_MIN_TICKS ) || ( elapsed == DALI_START_MAX_TICKS ) )
        {
            error_flag = DALI_ERROR_FRAME;
        }
    }

    for ( bit_index = 0; ( bit_index < 8 ) && ( DALI_OK == error_flag ); bit_index++ )
    {
        // Skip the optional boundary edge, then observe the next mandatory mid-bit edge.
        // Repeating this synchronization prevents sender clock error accumulating over eight bits.
        Delay_500us( );
        Delay_50us( );
        Delay_50us( );
        first_half = dali_read_rx( ctx );
        elapsed = 0;
        while ( ( first_half == dali_read_rx( ctx ) ) && ( elapsed < DALI_EDGE_MAX_TICKS ) )
        {
            Delay_10us( );
            elapsed++;
        }
        if ( ( elapsed < DALI_EDGE_MIN_TICKS ) || ( elapsed == DALI_EDGE_MAX_TICKS ) )
        {
            error_flag = DALI_ERROR_FRAME;
        }
        else
        {
            // RX low-to-high represents one; high-to-low represents zero.
            received = ( received << 1 ) | ( first_half ^ 1 );
        }
    }

    if ( DALI_OK == error_flag )
    {
        // Move beyond the final data half-bit, then require two complete idle stop bits.
        Delay_500us( );
        Delay_50us( );
        Delay_50us( );
        for ( elapsed = 0; ( elapsed < DALI_STOP_TICKS ) && ( DALI_OK == error_flag ); elapsed++ )
        {
            if ( DALI_PIN_IDLE != dali_read_rx( ctx ) )
            {
                error_flag = DALI_ERROR_FRAME;
            }
            Delay_10us( );
        }
        if ( DALI_OK == error_flag )
        {
            *data_out = received;
        }
    }

    return error_flag;
}

err_t dali_send_command ( dali_t *ctx, uint8_t address, uint8_t address_type, uint8_t command )
{
    uint8_t encoded_address;
    err_t error_flag = dali_encode_address( address, address_type, &encoded_address );

    if ( DALI_OK == error_flag )
    {
        error_flag = dali_generic_write( ctx, encoded_address | DALI_ADDRESS_COMMAND_MASK, command );
    }

    return error_flag;
}

err_t dali_set_level ( dali_t *ctx, uint8_t address, uint8_t address_type, uint8_t level )
{
    uint8_t encoded_address;
    err_t error_flag = dali_encode_address( address, address_type, &encoded_address );

    if ( DALI_OK == error_flag )
    {
        error_flag = dali_generic_write( ctx, encoded_address, level );
    }

    return error_flag;
}

err_t dali_query ( dali_t *ctx, uint8_t address, uint8_t command, uint8_t *response )
{
    err_t error_flag = DALI_ERROR;

    if ( response && ( command >= DALI_CMD_QUERY_STATUS ) )
    {
        error_flag = dali_send_command( ctx, address, DALI_ADDRESS_SHORT, command );
        if ( DALI_OK == error_flag )
        {
            // Do not log or insert a settling delay here: the gear replies within a short window.
            error_flag = dali_read_response( ctx, response );
        }
    }

    return error_flag;
}

uint8_t dali_get_phy_state ( dali_t *ctx )
{
    return digital_in_read( &ctx->phy );
}

static err_t dali_wait_idle ( dali_t *ctx )
{
    uint16_t elapsed;
    uint16_t idle_count = 0;
    err_t error_flag = DALI_ERROR_BUSY;

    // A fresh idle interval also keeps consecutive forward frames sufficiently separated.
    for ( elapsed = 0; ( elapsed < DALI_BUSY_TIMEOUT_TICKS ) && ( idle_count < DALI_IDLE_TICKS ); elapsed++ )
    {
        if ( DALI_PIN_IDLE == dali_read_rx( ctx ) )
        {
            idle_count++;
        }
        else
        {
            idle_count = 0;
        }
        Delay_50us( );
    }
    if ( idle_count == DALI_IDLE_TICKS )
    {
        error_flag = DALI_OK;
    }

    return error_flag;
}

static void dali_delay_half_bit ( void )
{
    Delay_410us( );
    Delay_6us( );
}

static void dali_send_bit ( dali_t *ctx, uint8_t bit_value )
{
    digital_out_write( &ctx->tx_pin, bit_value ^ 1 );
    dali_delay_half_bit( );
    digital_out_write( &ctx->tx_pin, bit_value );
    dali_delay_half_bit( );
}

static err_t dali_encode_address ( uint8_t address, uint8_t address_type, uint8_t *encoded_address )
{
    err_t error_flag = DALI_OK;

    switch ( address_type )
    {
        case DALI_ADDRESS_SHORT:
        {
            if ( address <= DALI_SHORT_ADDRESS_MAX )
            {
                *encoded_address = address << 1;
            }
            else
            {
                error_flag = DALI_ERROR;
            }
            break;
        }
        case DALI_ADDRESS_GROUP:
        {
            if ( address <= DALI_GROUP_ADDRESS_MAX )
            {
                *encoded_address = DALI_ADDRESS_GROUP_MASK | ( address << 1 );
            }
            else
            {
                error_flag = DALI_ERROR;
            }
            break;
        }
        case DALI_ADDRESS_BROADCAST:
        {
            *encoded_address = DALI_ADDRESS_BROADCAST_MASK;
            break;
        }
        default:
        {
            error_flag = DALI_ERROR;
            break;
        }
    }

    return error_flag;
}

static uint8_t dali_read_rx ( dali_t *ctx )
{
    uint8_t state;

    if ( DALI_RX_INT == ctx->rx_sel )
    {
        state = digital_in_read( &ctx->int_rx );
    }
    else
    {
        state = digital_in_read( &ctx->icp_rx );
    }

    return state;
}

// ------------------------------------------------------------------------- END
