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
 * @file ultrasonic2.c
 * @brief Ultrasonic 2 Click Driver.
 */

#include "ultrasonic2.h"

/**
 * @brief Ultrasonic 2 UART protocol settings.
 * @details Settings for the synchronization byte, diagnostic field and device CRC status.
 * @note Diagnostic bits 7 and 6 must be 0 and 1. A clear diagnostic byte is 0x40.
 */
#define ULTRASONIC2_SYNC                 0x55u
#define ULTRASONIC2_DIAG_MASK            0xC0u
#define ULTRASONIC2_DIAG_OK              0x40u
#define ULTRASONIC2_STATUS_CRC_MASK      0x07u

/**
 * @brief Ultrasonic 2 threshold map size.
 * @details Combined number of bytes in the preset 1 and preset 2 threshold maps.
 */
#define ULTRASONIC2_THRESHOLD_BYTES      32u

/**
 * @brief Ultrasonic 2 UART response settings.
 * @details Base timeout and additional time per reply byte, in milliseconds.
 * The reply overhead consists of the diagnostic byte and checksum.
 */
#define ULTRASONIC2_RESPONSE_TIMEOUT     50u
#define ULTRASONIC2_RESPONSE_BYTE_MS     5u
#define ULTRASONIC2_REPLY_OVERHEAD       2u

/**
 * @brief Ultrasonic 2 object detection settings.
 * @details Settings for echo capture mode, the requested object count and the
 * echo time value returned when no object is detected.
 */
#define ULTRASONIC2_DATA_DUMP_ENABLE     0x80u
#define ULTRASONIC2_DATA_DUMP_DISABLE    0x00u
#define ULTRASONIC2_ONE_OBJECT           1u
#define ULTRASONIC2_NO_ECHO_TIME         0xFFFFu

/**
 * @brief Ultrasonic 2 distance conversion settings.
 * @details Speed of sound in metres per second and one-way timing compensation in microseconds.
 */
#define ULTRASONIC2_SOUND_M_PER_S        343ul
#define ULTRASONIC2_ONE_WAY_OFFSET_US    50u

/**
 * @brief Ultrasonic 2 gain map size.
 * @details Number of bytes in the time-varying gain map from TVGAIN0 through TVGAIN6.
 */
#define ULTRASONIC2_TVG_BYTES            7u

/**
 * @brief Ultrasonic 2 register verification masks.
 * @details Masks used to compare writable gain, current-limit and threshold-offset bits during readback.
 * Reserved bits are excluded from the comparisons.
 */
#define ULTRASONIC2_TVG6_MASK            0xFDu
#define ULTRASONIC2_CURR_LIM_P1_MASK     0xBFu
#define ULTRASONIC2_THR_OFFSET_MASK      0x0Fu

/**
 * @brief Ultrasonic 2 checksum calculation function.
 * @details This function calculates the inverted byte sum with end-around carry
 * for the supplied UART command and payload bytes.
 * @param[in] bytes : Bytes included in the checksum.
 * @param[in] len : Number of bytes in the checksum.
 * @return Calculated 8-bit checksum.
 * @note The synchronization byte is excluded from the checksum calculation.
 */
static uint8_t ultrasonic2_checksum ( uint8_t *bytes, uint8_t len );

/**
 * @brief Ultrasonic 2 command writing function.
 * @details This function sends a UART command to device address 0 with the required
 * framing and byte spacing. It clears stale input and enables reception before transmission.
 * @param[in] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @param[in] cmd : Command byte for UART address 0.
 * @param[in] payload : Command payload, or a null pointer when len is zero.
 * @param[in] len : Payload length, up to #ULTRASONIC2_THRESHOLD_BYTES.
 * @return @li @c  0 - Command sent,
 *         @li @c -1 - UART error.
 * See #err_t definition for detailed explanation.
 * @note Only commands with a payload include a checksum. An incomplete transmission
 * is followed by an idle interval to reset the device frame parser.
 */
static err_t ultrasonic2_send_command ( ultrasonic2_t *ctx, uint8_t cmd, uint8_t *payload, uint8_t len );

/**
 * @brief Ultrasonic 2 response reading function.
 * @details This function receives a complete UART reply and validates its diagnostic
 * byte and checksum. The payload excludes the diagnostic byte and checksum.
 * @param[in] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @param[out] payload : Buffer with room for len reply bytes.
 * @param[in] len : Expected payload length.
 * @return @li @c  0 - Valid reply,
 *         @li @c -1 - Timeout, UART error or invalid frame,
 *         @li @c -3 - Valid frame containing a device diagnostic.
 * See #err_t definition for detailed explanation.
 * @note A single timeout bounds reception of the entire reply. The caller uses
 * the payload only after this function returns success.
 */
static err_t ultrasonic2_read_response ( ultrasonic2_t *ctx, uint8_t *payload, uint8_t len );

void ultrasonic2_cfg_setup ( ultrasonic2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->test = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->baud_rate     = 19200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t ultrasonic2_init ( ultrasonic2_t *ctx, ultrasonic2_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;
    err_t status;

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

    status = uart_open( &ctx->uart, &uart_cfg );
    if ( UART_ERROR != status )
    {
        uart_set_baud( &ctx->uart, cfg->baud_rate );
        uart_set_parity( &ctx->uart, cfg->parity_bit );
        uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
        uart_set_data_bits( &ctx->uart, cfg->data_bit );

        uart_set_blocking( &ctx->uart, cfg->uart_blocking );

        // Output pins
        digital_out_init( &ctx->en, cfg->en );
        digital_out_low( &ctx->en );

        // Leave TEST as a host input so the MCU does not drive the PGA460 test or logic-level selection pin.
        digital_in_init( &ctx->test, cfg->test );

        status = UART_SUCCESS;
    }
    return status;
}

err_t ultrasonic2_default_cfg ( ultrasonic2_t *ctx ) 
{
    // Ranging profile, in register order from TVGAIN0 through P2_GAIN_CTRL.
    static uint8_t profile[] =
    {
        // TVGAIN0-2 pack T0-T5. Hold 46.5 dB to 1.4 ms and finish the gain ramp at 2.8 ms.
        0x88u, 0xEEu, 0xEFu,
        // TVGAIN3-6 pack G1-G5. All five points use 62.5 dB in the selected AFE range.
        0x82u, 0x08u, 0x20u, 0x80u,
        0x40u, // INIT_GAIN sets 46.5 dB initial gain and 4 kHz band-pass bandwidth.
        0x32u, // FREQUENCY selects 30 kHz + 50 * 200 Hz = 40 kHz.
        0x80u, // DEADTIME selects 64 us threshold deglitch and zero driver dead time.
        0x10u, // PULSE_P1 selects 16 burst pulses.
        0x1Fu, // PULSE_P2 selects 31 pulses and UART address 0.
        0x7Fu, // CURR_LIM_P1 enables current limiting with preset 1 current-limit code 63.
        0x40u, // CURR_LIM_P2 selects 2 kHz low-pass cutoff and preset 2 current-limit code 0.
        0xF9u, // REC_LENGTH selects 65.536 ms for preset 1 and 40.960 ms for preset 2.
        0x1Bu, // FREQ_DIAG captures three periods starting 1.1 ms after the burst.
        0x2Cu, // SAT_FDIAG_TH sets diagnostic thresholds and disables preset 1 nonlinear scaling.
        0x7Cu, // FVOLT_DEC sets voltage diagnostics and disables preset 2 nonlinear scaling.
        0x8Fu, // DECPL_TEMP selects the 46-78 dB AFE range and a 65.536 ms decouple time.
        0x00u, // DSP_SCALE selects zero noise offset and the first nonlinear scaling start point.
        0x00u, // TEMP_TRIM applies zero temperature gain and offset correction.
        0x08u, // P1_GAIN_CTRL selects x1 short-range and x2 long-range digital gain.
        0x18u  // P2_GAIN_CTRL selects x1 short-range and x8 long-range digital gain.
    };
    static uint8_t thresholds[ ULTRASONIC2_THRESHOLD_BYTES ] =
    {
        // Preset 1 time points. Point 1 is absolute and the following times are increments.
        0x77u, 0x77u, 0x77u, 0x77u, 0x78u, 0x88u,
        // Levels 1-8 are packed 5-bit codes with 8-count resolution. Levels 1-2 are 152, then 80.
        0x9Cu, 0xD4u, 0xA5u, 0x29u, 0x4Au,
        // Levels 9-12 are full bytes. The final byte selects zero short-range threshold offset.
        0x50u, 0x50u, 0x50u, 0x50u, 0x00u,
        // Preset 2 time points, packed levels 1-8, full levels 9-12 and offset.
        0x88u, 0x88u, 0x88u, 0x88u, 0x88u, 0x88u,
        0x84u, 0x21u, 0x08u, 0x42u, 0x10u,
        0x80u, 0x80u, 0x80u, 0x80u, 0x00u
    };
    uint8_t reg;
    uint8_t reg_value;
    uint8_t mask;
    err_t status;

    // CS enables the boost converter. Allow VPWR and the PGA460 to settle before accessing registers.
    digital_out_high( &ctx->en );
    Delay_100ms( );

    // A reply acknowledges latched UART errors from power-up before configuration begins.
    status = ultrasonic2_read_register( ctx, ULTRASONIC2_REG_DEV_STAT0, &reg_value );
    if ( ULTRASONIC2_DEVICE_ERROR == status )
    {
        status = ULTRASONIC2_OK;
    }
    // Threshold RAM is undefined at power-up. Load both maps before checking device CRC status.
    if ( ULTRASONIC2_OK == status )
    {
        status = ultrasonic2_send_command( ctx, ULTRASONIC2_CMD_THR_WRITE, thresholds, sizeof( thresholds ) );
    }
    if ( ULTRASONIC2_OK == status )
    {
        status = ultrasonic2_send_command( ctx, ULTRASONIC2_CMD_TVG_WRITE, profile, ULTRASONIC2_TVG_BYTES );
    }
    // The seven gain-map bytes use a bulk command. The remaining registers are consecutive single writes.
    for ( uint8_t index = ULTRASONIC2_TVG_BYTES; ( ULTRASONIC2_OK == status ) && ( index < sizeof( profile ) ); index++ )
    {
        reg = ( uint8_t ) ( ULTRASONIC2_REG_TVGAIN0 + index );
        status = ultrasonic2_write_register( ctx, reg, profile[ index ] );
    }
    if ( ULTRASONIC2_OK == status )
    {
        // Object detection and echo RAM capture are mutually exclusive in the PGA460.
        status = ultrasonic2_write_register( ctx, ULTRASONIC2_REG_EE_CNTRL, ULTRASONIC2_DATA_DUMP_DISABLE );
    }
    if ( ULTRASONIC2_OK == status )
    {
        status = ultrasonic2_read_register( ctx, ULTRASONIC2_REG_DEV_STAT0, &reg_value );
        if ( ( ULTRASONIC2_OK == status ) && ( reg_value & ULTRASONIC2_STATUS_CRC_MASK ) )
        {
            status = ULTRASONIC2_DEVICE_ERROR;
        }
    }

    // Verify the unacknowledged writes, ignoring reserved bits on readback.
    for ( uint8_t index = 0; ( ULTRASONIC2_OK == status ) && ( index < sizeof( profile ) ); index++ )
    {
        reg = ( uint8_t ) ( ULTRASONIC2_REG_TVGAIN0 + index );
        mask = 0xFFu;
        if ( ULTRASONIC2_REG_TVGAIN6 == reg )
        {
            mask = ULTRASONIC2_TVG6_MASK;
        }
        else if ( ULTRASONIC2_REG_CURR_LIM_P1 == reg )
        {
            mask = ULTRASONIC2_CURR_LIM_P1_MASK;
        }
        status = ultrasonic2_read_register( ctx, reg, &reg_value );
        if ( ( ULTRASONIC2_OK == status ) && ( ( reg_value ^ profile[ index ] ) & mask ) )
        {
            status = ULTRASONIC2_DEVICE_ERROR;
        }
    }
    for ( uint8_t index = 0; ( ULTRASONIC2_OK == status ) && ( index < sizeof( thresholds ) ); index++ )
    {
        reg = ( uint8_t ) ( ULTRASONIC2_REG_P1_THR_0 + index );
        mask = 0xFFu;
        if ( ( ULTRASONIC2_REG_P1_THR_15 == reg ) || ( ULTRASONIC2_REG_P2_THR_15 == reg ) )
        {
            mask = ULTRASONIC2_THR_OFFSET_MASK;
        }
        status = ultrasonic2_read_register( ctx, reg, &reg_value );
        if ( ( ULTRASONIC2_OK == status ) && ( ( reg_value ^ thresholds[ index ] ) & mask ) )
        {
            status = ULTRASONIC2_DEVICE_ERROR;
        }
    }
    return status;
}

err_t ultrasonic2_generic_write ( ultrasonic2_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ultrasonic2_generic_read ( ultrasonic2_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t ultrasonic2_write_register ( ultrasonic2_t *ctx, uint8_t reg, uint8_t value )
{
    uint8_t payload[ 2 ];
    payload[ 0 ] = reg;
    payload[ 1 ] = value;
    return ultrasonic2_send_command( ctx, ULTRASONIC2_CMD_REG_WRITE, payload, sizeof( payload ) );
}

err_t ultrasonic2_read_register ( ultrasonic2_t *ctx, uint8_t reg, uint8_t *value )
{
    uint8_t reg_value;
    err_t status = ULTRASONIC2_ERROR;
    if ( value )
    {
        status = ultrasonic2_send_command( ctx, ULTRASONIC2_CMD_REG_READ, &reg, 1 );
        if ( ULTRASONIC2_OK == status )
        {
            status = ultrasonic2_read_response( ctx, &reg_value, 1 );
        }
        if ( ULTRASONIC2_OK == status )
        {
            *value = reg_value;
        }
    }
    return status;
}

err_t ultrasonic2_get_measurement ( ultrasonic2_t *ctx, ultrasonic2_measurement_t *measurement )
{
    uint8_t objects = ULTRASONIC2_ONE_OBJECT;
    uint8_t control;
    uint8_t echo[ ULTRASONIC2_ECHO_REPLY_SIZE - ULTRASONIC2_REPLY_OVERHEAD ];
    uint16_t time_us;
    uint16_t one_way_us;
    err_t status = ULTRASONIC2_ERROR;
    if ( measurement )
    {
        // Reject a disabled threshold comparator instead of returning old measurement registers.
        status = ultrasonic2_read_register( ctx, ULTRASONIC2_REG_EE_CNTRL, &control );
        if ( ( ULTRASONIC2_OK == status ) && ( control & ULTRASONIC2_DATA_DUMP_ENABLE ) )
        {
            status = ULTRASONIC2_DEVICE_ERROR;
        }
    }
    if ( ULTRASONIC2_OK == status )
    {
        status = ultrasonic2_send_command( ctx, ULTRASONIC2_CMD_BURST_P1, &objects, 1 );
    }
    if ( ULTRASONIC2_OK == status )
    {
        // Covers the longest programmable record interval (65.536 ms) plus burst time.
        Delay_100ms( );
        status = ultrasonic2_send_command( ctx, ULTRASONIC2_CMD_RESULT, 0, 0 );
    }
    if ( ULTRASONIC2_OK == status )
    {
        status = ultrasonic2_read_response( ctx, echo, sizeof( echo ) );
    }
    if ( ULTRASONIC2_OK == status )
    {
        // Each result contains a big-endian 16-bit echo time followed by width and peak amplitude.
        time_us = ( ( uint16_t ) echo[ 0 ] << 8 ) | echo[ 1 ];
        if ( ULTRASONIC2_NO_ECHO_TIME == time_us )
        {
            // An undetected object has no valid timing value. Leave the caller's measurement untouched.
            status = ULTRASONIC2_NO_OBJECT;
        }
        else
        {
            // Halve the round-trip time once, then apply the profile's 50 us one-way compensation.
            // Clamp before subtracting to prevent unsigned underflow for very short echo times.
            one_way_us = time_us / 2u;
            if ( one_way_us > ULTRASONIC2_ONE_WAY_OFFSET_US )
            {
                one_way_us -= ULTRASONIC2_ONE_WAY_OFFSET_US;
            }
            else
            {
                one_way_us = 0;
            }
            measurement->time_us = time_us;
            // Multiplication uses 32 bits. Division by 1000 converts m/s * us to mm and rounds to the nearest mm.
            measurement->distance_mm = ( uint16_t ) ( ( ( uint32_t ) one_way_us * ULTRASONIC2_SOUND_M_PER_S +
                                                        500ul ) / 1000ul );
            measurement->width = echo[ 2 ];
            measurement->amplitude = echo[ 3 ];
        }
    }
    return status;
}

static uint8_t ultrasonic2_checksum ( uint8_t *bytes, uint8_t len )
{
    uint16_t sum = 0;
    for ( uint8_t index = 0; index < len; index++ )
    {
        // Fold the carry into the low byte before inverting the completed sum.
        sum += bytes[ index ];
        sum = ( sum & 0xFFu ) + ( sum >> 8 );
    }
    return ( uint8_t ) ~sum;
}

static err_t ultrasonic2_send_command ( ultrasonic2_t *ctx, uint8_t cmd, uint8_t *payload, uint8_t len )
{
    uint8_t frame[ ULTRASONIC2_THRESHOLD_BYTES + 3 ];
    uint8_t size = 2;
    err_t status = ULTRASONIC2_OK;

    for ( uint16_t offset = 0; offset < sizeof( ctx->uart_rx_buffer ); offset += sizeof( frame ) )
    {
        if ( ( err_t ) sizeof( frame ) != ultrasonic2_generic_read( ctx, frame, sizeof( frame ) ) )
        {
            break;
        }
    }

    // A request is sync, command, optional payload and optional checksum. Response-only commands end at command.
    frame[ 0 ] = ULTRASONIC2_SYNC;
    frame[ 1 ] = cmd;
    if ( len > 0 )
    {
        memcpy( &frame[ size ], payload, len );
        size += len;
        frame[ size ] = ultrasonic2_checksum( &frame[ 1 ], size - 1 );
        size++;
    }

    for ( uint8_t index = 0; ( ULTRASONIC2_OK == status ) && ( index < size ); index++ )
    {
        if ( 1 != ultrasonic2_generic_write( ctx, &frame[ index ], 1 ) )
        {
            status = ULTRASONIC2_ERROR;
        }
        // Covers a full character and one idle bit at the minimum supported baud rate.
        Delay_5ms( );
    }
    if ( ULTRASONIC2_OK != status )
    {
        // An incomplete frame is discarded after 15 ms of UART inactivity.
        Delay_10ms( );
        Delay_10ms( );
    }
    return status;
}

static err_t ultrasonic2_read_response ( ultrasonic2_t *ctx, uint8_t *payload, uint8_t len )
{
    uint8_t received = 0;
    uint8_t diagnostic = 0;
    uint8_t value;
    uint8_t reply_len = len + ULTRASONIC2_REPLY_OVERHEAD;
    uint16_t sum = 0;
    // At 2400 baud each UART character needs up to 5 ms. Allow additional response latency.
    uint16_t timeout_limit = ULTRASONIC2_RESPONSE_TIMEOUT + ( uint16_t ) reply_len * ULTRASONIC2_RESPONSE_BYTE_MS;
    err_t status = ULTRASONIC2_ERROR;
    for ( uint16_t timeout = 0; timeout < timeout_limit; timeout++ )
    {
        if ( uart_bytes_available( &ctx->uart ) > 0 )
        {
            if ( 1 != ultrasonic2_generic_read( ctx, &value, 1 ) )
            {
                break;
            }
            // The final byte is the checksum over the diagnostic prefix and payload.
            if ( received == reply_len - 1u )
            {
                if ( ULTRASONIC2_DIAG_OK == ( diagnostic & ULTRASONIC2_DIAG_MASK ) )
                {
                    if ( value == ( uint8_t ) ~sum )
                    {
                        status = ULTRASONIC2_OK;
                        // A valid frame may still report a latched device or communication diagnostic.
                        if ( ULTRASONIC2_DIAG_OK != diagnostic )
                        {
                            status = ULTRASONIC2_DEVICE_ERROR;
                        }
                    }
                }
                break;
            }
            sum += value;
            sum = ( sum & 0xFFu ) + ( sum >> 8 );
            if ( 0 == received )
            {
                diagnostic = value;
            }
            else
            {
                payload[ received - 1u ] = value;
            }
            received++;
        }
        Delay_1ms( );
    }
    return status;
}

// ------------------------------------------------------------------------- END
