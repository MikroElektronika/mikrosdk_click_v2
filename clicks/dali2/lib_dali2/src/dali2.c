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
 * @file dali2.c
 * @brief DALI 2 Click Driver.
 */

#include "dali2.h"

/** Bus-idle polling uses 50 us steps; allow 10 ms of idle within a 100 ms window. */
#define DALI2_IDLE_TICKS                        200
#define DALI2_BUSY_TIMEOUT_TICKS                2000

/** Receive polling uses 10 us steps, including margin for GPIO and optocoupler delays. */
#define DALI2_RESPONSE_TIMEOUT_TICKS            1200
#define DALI2_START_MIN_TICKS                   25
#define DALI2_START_MAX_TICKS                   60
#define DALI2_EDGE_MIN_TICKS                    5
#define DALI2_EDGE_MAX_TICKS                    45
#define DALI2_STOP_TICKS                        170

/**
 * @brief DALI 2 wait idle function.
 * @details This function waits for a powered, idle bus before starting a forward frame.
 * It restarts the idle count on bus activity and bounds the overall wait.
 * @param[in] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @return @li @c DALI2_OK - Bus is idle and ready,
 *         @li @c DALI2_ERROR_BUSY - Bus is busy or bus power is missing.
 * See #dali2_return_value_t definition for detailed explanation.
 * @note None.
 */
static err_t dali2_wait_idle ( dali2_t *ctx );

/**
 * @brief DALI 2 delay half bit function.
 * @details This function combines fixed delay primitives for approximately 416.7 us,
 * excluding call overhead.
 * @return None.
 * @note None.
 */
static void dali2_delay_half_bit ( void );

/**
 * @brief DALI 2 send bit function.
 * @details This function transmits one Manchester-encoded bit through the inverted TX interface.
 * @param[in] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @param[in] bit_value : Logical bit value, 0 or 1.
 * @return None.
 * @note None.
 */
static void dali2_send_bit ( dali2_t *ctx, uint8_t bit_value );

/**
 * @brief DALI 2 encode address function.
 * @details This function encodes the destination without setting the command selector bit.
 * @param[in] address : Short or group address; ignored for broadcast.
 * @param[in] address_type : Destination addressing mode.
 * @param[out] encoded_address : Encoded address byte; unchanged if validation fails.
 * @return @li @c DALI2_OK - Address encoded,
 *         @li @c DALI2_ERROR - Unsupported type or out-of-range address.
 * See #dali2_return_value_t definition for detailed explanation.
 * @note None.
 */
static err_t dali2_encode_address ( uint8_t address, uint8_t address_type, uint8_t *encoded_address );

void dali2_cfg_setup ( dali2_cfg_t *cfg ) 
{
    cfg->tx_pin = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
}

err_t dali2_init ( dali2_t *ctx, dali2_cfg_t *cfg ) 
{
    err_t error_flag = DALI2_ERROR;

    if ( DIGITAL_OUT_SUCCESS == digital_out_init( &ctx->tx_pin, cfg->tx_pin ) )
    {
        // Release the bus before configuring the receive input.
        digital_out_write( &ctx->tx_pin, DALI2_PIN_IDLE );
        if ( DIGITAL_IN_SUCCESS == digital_in_init( &ctx->rx_pin, cfg->rx_pin ) )
        {
            error_flag = DALI2_OK;
        }
    }

    return error_flag;
}

err_t dali2_default_cfg ( dali2_t *ctx ) 
{
    digital_out_write( &ctx->tx_pin, DALI2_PIN_IDLE );
    return dali2_wait_idle( ctx );
}

err_t dali2_generic_write ( dali2_t *ctx, uint8_t address, uint8_t data_in )
{
    err_t error_flag = dali2_wait_idle( ctx );
    uint16_t frame = ( ( uint16_t ) address << 8 ) | data_in;
    uint8_t bit_index;

    if ( DALI2_OK == error_flag )
    {
        // A logical one starts the frame, followed by address and data, MSB first.
        dali2_send_bit( ctx, 1 );
        for ( bit_index = 0; bit_index < 16; bit_index++ )
        {
            dali2_send_bit( ctx, ( uint8_t ) ( frame >> 15 ) );
            frame <<= 1;
        }

        // Stop bits are an idle bus, not Manchester-encoded zero bits.
        digital_out_write( &ctx->tx_pin, DALI2_PIN_IDLE );
        for ( bit_index = 0; bit_index < 4; bit_index++ )
        {
            dali2_delay_half_bit( );
        }
    }

    return error_flag;
}

err_t dali2_read_response ( dali2_t *ctx, uint8_t *data_out )
{
    err_t error_flag = DALI2_OK;
    uint16_t elapsed = 0;
    uint8_t received = 0;
    uint8_t first_half;
    uint8_t bit_index;

    if ( !data_out )
    {
        error_flag = DALI2_ERROR;
    }
    else
    {
        // A backward frame starts with RX high because the optocoupler inverts the bus.
        while ( ( DALI2_PIN_IDLE == digital_in_read( &ctx->rx_pin ) ) &&
                ( elapsed < DALI2_RESPONSE_TIMEOUT_TICKS ) )
        {
            Delay_10us( );
            elapsed++;
        }
        if ( elapsed == DALI2_RESPONSE_TIMEOUT_TICKS )
        {
            error_flag = DALI2_ERROR_TIMEOUT;
        }
    }

    if ( DALI2_OK == error_flag )
    {
        // Validate the first half of the start bit and synchronize to its falling edge.
        elapsed = 0;
        while ( ( DALI2_PIN_ACTIVE == digital_in_read( &ctx->rx_pin ) ) &&
                ( elapsed < DALI2_START_MAX_TICKS ) )
        {
            Delay_10us( );
            elapsed++;
        }
        if ( ( elapsed < DALI2_START_MIN_TICKS ) || ( elapsed == DALI2_START_MAX_TICKS ) )
        {
            error_flag = DALI2_ERROR_FRAME;
        }
    }

    for ( bit_index = 0; ( bit_index < 8 ) && ( DALI2_OK == error_flag ); bit_index++ )
    {
        // Skip the optional boundary edge, then observe the next mandatory mid-bit edge.
        // Repeating this synchronization prevents sender clock error accumulating over eight bits.
        Delay_500us( );
        Delay_50us( );
        Delay_50us( );
        first_half = digital_in_read( &ctx->rx_pin );
        elapsed = 0;
        while ( ( first_half == digital_in_read( &ctx->rx_pin ) ) && ( elapsed < DALI2_EDGE_MAX_TICKS ) )
        {
            Delay_10us( );
            elapsed++;
        }
        if ( ( elapsed < DALI2_EDGE_MIN_TICKS ) || ( elapsed == DALI2_EDGE_MAX_TICKS ) )
        {
            error_flag = DALI2_ERROR_FRAME;
        }
        else
        {
            // RX high-to-low represents one; low-to-high represents zero.
            received = ( received << 1 ) | first_half;
        }
    }

    if ( DALI2_OK == error_flag )
    {
        // Move beyond the final data half-bit, then require two complete idle stop bits.
        Delay_500us( );
        Delay_50us( );
        Delay_50us( );
        for ( elapsed = 0; ( elapsed < DALI2_STOP_TICKS ) && ( DALI2_OK == error_flag ); elapsed++ )
        {
            if ( DALI2_PIN_IDLE != digital_in_read( &ctx->rx_pin ) )
            {
                error_flag = DALI2_ERROR_FRAME;
            }
            Delay_10us( );
        }
        if ( DALI2_OK == error_flag )
        {
            *data_out = received;
        }
    }

    return error_flag;
}

err_t dali2_send_command ( dali2_t *ctx, uint8_t address, uint8_t address_type, uint8_t command )
{
    uint8_t encoded_address;
    err_t error_flag = dali2_encode_address( address, address_type, &encoded_address );

    if ( DALI2_OK == error_flag )
    {
        error_flag = dali2_generic_write( ctx, encoded_address | DALI2_ADDRESS_COMMAND_MASK, command );
    }

    return error_flag;
}

err_t dali2_set_level ( dali2_t *ctx, uint8_t address, uint8_t address_type, uint8_t level )
{
    uint8_t encoded_address;
    err_t error_flag = dali2_encode_address( address, address_type, &encoded_address );

    if ( DALI2_OK == error_flag )
    {
        error_flag = dali2_generic_write( ctx, encoded_address, level );
    }

    return error_flag;
}

err_t dali2_query ( dali2_t *ctx, uint8_t address, uint8_t command, uint8_t *response )
{
    err_t error_flag = DALI2_ERROR;

    if ( response && ( command >= DALI2_CMD_QUERY_STATUS ) )
    {
        error_flag = dali2_send_command( ctx, address, DALI2_ADDRESS_SHORT, command );
        if ( DALI2_OK == error_flag )
        {
            // Do not log or insert a settling delay here: the gear replies within a short window.
            error_flag = dali2_read_response( ctx, response );
        }
    }

    return error_flag;
}

static err_t dali2_wait_idle ( dali2_t *ctx )
{
    uint16_t elapsed;
    uint16_t idle_count = 0;
    err_t error_flag = DALI2_ERROR_BUSY;

    // A fresh idle interval also keeps consecutive forward frames sufficiently separated.
    for ( elapsed = 0; ( elapsed < DALI2_BUSY_TIMEOUT_TICKS ) && ( idle_count < DALI2_IDLE_TICKS ); elapsed++ )
    {
        if ( DALI2_PIN_IDLE == digital_in_read( &ctx->rx_pin ) )
        {
            idle_count++;
        }
        else
        {
            idle_count = 0;
        }
        Delay_50us( );
    }
    if ( idle_count == DALI2_IDLE_TICKS )
    {
        error_flag = DALI2_OK;
    }

    return error_flag;
}

static void dali2_delay_half_bit ( void )
{
    Delay_410us( );
    Delay_6us( );
}

static void dali2_send_bit ( dali2_t *ctx, uint8_t bit_value )
{
    digital_out_write( &ctx->tx_pin, bit_value );
    dali2_delay_half_bit( );
    digital_out_write( &ctx->tx_pin, bit_value ^ 1 );
    dali2_delay_half_bit( );
}

static err_t dali2_encode_address ( uint8_t address, uint8_t address_type, uint8_t *encoded_address )
{
    err_t error_flag = DALI2_OK;

    switch ( address_type )
    {
        case DALI2_ADDRESS_SHORT:
        {
            if ( address <= DALI2_SHORT_ADDRESS_MAX )
            {
                *encoded_address = address << 1;
            }
            else
            {
                error_flag = DALI2_ERROR;
            }
            break;
        }
        case DALI2_ADDRESS_GROUP:
        {
            if ( address <= DALI2_GROUP_ADDRESS_MAX )
            {
                *encoded_address = DALI2_ADDRESS_GROUP_MASK | ( address << 1 );
            }
            else
            {
                error_flag = DALI2_ERROR;
            }
            break;
        }
        case DALI2_ADDRESS_BROADCAST:
        {
            *encoded_address = DALI2_ADDRESS_BROADCAST_MASK;
            break;
        }
        default:
        {
            error_flag = DALI2_ERROR;
            break;
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
