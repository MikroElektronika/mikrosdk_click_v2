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
 * @file ultrasonic2.h
 * @brief This file contains API for Ultrasonic 2 Click Driver.
 */

#ifndef ULTRASONIC2_H
#define ULTRASONIC2_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup ultrasonic2 Ultrasonic 2 Click Driver
 * @brief API for configuring and manipulating Ultrasonic 2 Click driver.
 * @{
 */

/**
 * @defgroup ultrasonic2_cmd Ultrasonic 2 Device Settings
 * @brief Settings of Ultrasonic 2 Click driver.
 */

/**
 * @addtogroup ultrasonic2_cmd
 * @{
 */

/**
 * @brief Ultrasonic 2 UART commands.
 * @details PGA460 command bytes for the factory UART address (0).
 */
#define ULTRASONIC2_CMD_BURST_P1            0x00u
#define ULTRASONIC2_CMD_RESULT              0x05u
#define ULTRASONIC2_CMD_REG_READ            0x09u
#define ULTRASONIC2_CMD_REG_WRITE           0x0Au
#define ULTRASONIC2_CMD_TVG_WRITE           0x0Eu
#define ULTRASONIC2_CMD_THR_WRITE           0x10u

/**
 * @brief Ultrasonic 2 configuration registers.
 * @details PGA460 gain, burst, receiver, threshold and status registers at UART address 0.
 * DEV_STAT1 supply and thermal flags are cleared when the register is read.
 */
#define ULTRASONIC2_REG_TVGAIN0             0x14u
#define ULTRASONIC2_REG_TVGAIN6             0x1Au
#define ULTRASONIC2_REG_INIT_GAIN           0x1Bu
#define ULTRASONIC2_REG_FREQUENCY           0x1Cu
#define ULTRASONIC2_REG_DEADTIME            0x1Du
#define ULTRASONIC2_REG_PULSE_P1            0x1Eu
#define ULTRASONIC2_REG_CURR_LIM_P1         0x20u
#define ULTRASONIC2_REG_CURR_LIM_P2         0x21u
#define ULTRASONIC2_REG_REC_LENGTH          0x22u
#define ULTRASONIC2_REG_FREQ_DIAG           0x23u
#define ULTRASONIC2_REG_SAT_FDIAG_TH        0x24u
#define ULTRASONIC2_REG_DECPL_TEMP          0x26u
#define ULTRASONIC2_REG_DSP_SCALE           0x27u
#define ULTRASONIC2_REG_P1_GAIN_CTRL        0x29u
#define ULTRASONIC2_REG_EE_CNTRL            0x40u
#define ULTRASONIC2_REG_DEV_STAT0           0x4Cu
#define ULTRASONIC2_REG_DEV_STAT1           0x4Du
#define ULTRASONIC2_REG_P1_THR_0            0x5Fu
#define ULTRASONIC2_REG_P1_THR_15           0x6Eu
#define ULTRASONIC2_REG_P2_THR_15           0x7Eu

/**
 * @brief Ultrasonic 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ULTRASONIC2_TX_DRV_BUFFER_SIZE      100
#define ULTRASONIC2_RX_DRV_BUFFER_SIZE      100

/**
 * @brief Ultrasonic 2 measurement reply size.
 * @details Number of bytes in a single-object measurement reply, including the
 * diagnostic byte, echo time, width, peak amplitude and checksum.
 */
#define ULTRASONIC2_ECHO_REPLY_SIZE         6u

/*! @} */ // ultrasonic2_cmd

/**
 * @defgroup ultrasonic2_map Ultrasonic 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Ultrasonic 2 Click driver.
 */

/**
 * @addtogroup ultrasonic2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ultrasonic 2 Click to the selected MikroBUS.
 */
#define ULTRASONIC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.test = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // ultrasonic2_map
/*! @} */ // ultrasonic2

/**
 * @brief Ultrasonic 2 Click context object.
 * @details Owns the UART ring buffers and the boost-enable and TEST pin handles.
 * Allocate one context for each Click board and keep it alive while the UART is open.
 */
typedef struct
{
    // Output pins
    digital_out_t en;               /**< Active-high boost converter enable. */

    // Input pins
    digital_in_t test;              /**< PGA460 TEST pin, left as a host input. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ ULTRASONIC2_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ ULTRASONIC2_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} ultrasonic2_t;

/**
 * @brief Ultrasonic 2 Click configuration object.
 * @details Configuration object definition of Ultrasonic 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t test;                /**< TEST pin on AN. */
    pin_name_t en;                  /**< Boost converter enable on CS. */

    // Static variable
    uint32_t         baud_rate;     /**< UART baud rate, 2400 to 115200 bps. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} ultrasonic2_cfg_t;

/**
 * @brief Ultrasonic 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ULTRASONIC2_OK = 0,
    ULTRASONIC2_ERROR = -1,
    ULTRASONIC2_NO_OBJECT = -2,
    ULTRASONIC2_DEVICE_ERROR = -3

} ultrasonic2_return_value_t;

/**
 * @brief Ultrasonic 2 echo measurement.
 * @details First echo crossing the configured preset 1 threshold after a burst.
 * All fields are assigned only after the complete reply passes validation.
 */
typedef struct
{
    uint16_t time_us;               /**< Raw echo time after the burst, in microseconds. */
    uint16_t distance_mm;           /**< One-way distance in mm at 343 m/s with a 50 us timing offset. */
    uint8_t width;                  /**< Echo width in 4 us units, 0xFF at the end of the record. */
    uint8_t amplitude;              /**< Peak amplitude at the DSP output, 0 to 255. */

} ultrasonic2_measurement_t;

/*!
 * @addtogroup ultrasonic2 Ultrasonic 2 Click Driver
 * @brief API for configuring and manipulating Ultrasonic 2 Click driver.
 * @{
 */

/**
 * @brief Ultrasonic 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ultrasonic2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All pins start unconnected. Apply #ULTRASONIC2_MAP_MIKROBUS before #ultrasonic2_init.
 * The default UART format is 19200 bps, 8N1. Commands include the idle time required between bytes.
 */
void ultrasonic2_cfg_setup ( ultrasonic2_cfg_t *cfg );

/**
 * @brief Ultrasonic 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ultrasonic2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Connect an external pull-up resistor from mikroBUS RX (PGA460 TXD) to a logic rail
 * compatible with the host UART input. PGA460 TXD is high impedance between replies.
 * TEST remains a host input. The boost converter is disabled until #ultrasonic2_default_cfg is called.
 */
err_t ultrasonic2_init ( ultrasonic2_t *ctx, ultrasonic2_cfg_t *cfg );

/**
 * @brief Ultrasonic 2 default configuration function.
 * @details This function executes a default configuration of Ultrasonic 2 Click board. 
 * It enables the boost converter, waits for power-up and writes the burst, receiver gain and threshold maps.
 * Verifies the programmed values and device memory CRC status before reporting success.
 * @param[in] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Communication error,
 *         @li @c -3 - Device diagnostic or configuration error.
 * See #err_t definition for detailed explanation.
 * @note Call after each power-up. The ranging profile uses 16 pulses at 40 kHz,
 * preset 1 current-limit code 63 and a 65.536 ms record interval. Settings are volatile.
 * The initial status reply clears previously latched UART diagnostics before configuration.
 * Receiver gain starts at 46.5 dB, holds until 1.4 ms, and reaches 62.5 dB at 2.8 ms for the rest of the record.
 * Preset 1 threshold points 1 and 2 are 152. Points 3 through 12 are 80, starting at 3.6 ms.
 * Long-range digital gain is x2 from threshold 9. The device compensates the threshold at this transition.
 */
err_t ultrasonic2_default_cfg ( ultrasonic2_t *ctx );

/**
 * @brief Ultrasonic 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Number of bytes written,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note Raw writes do not add PGA460 framing or inter-byte delays.
 * Use #ultrasonic2_write_register for register access with framing and checksum.
 */
err_t ultrasonic2_generic_write ( ultrasonic2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Ultrasonic 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note Reads bytes already received by the UART driver. Blocking follows cfg.uart_blocking.
 * Register and measurement functions handle their complete replies internally.
 */
err_t ultrasonic2_generic_read ( ultrasonic2_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Ultrasonic 2 register writing function.
 * @details This function writes a PGA460 register by using a checksummed UART command.
 * @param[in] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] value : Register value.
 * @return @li @c  0 - Command sent,
 *         @li @c -1 - UART error.
 * See #err_t definition for detailed explanation.
 * @note The device does not acknowledge this command. Read back a register to verify it.
 */
err_t ultrasonic2_write_register ( ultrasonic2_t *ctx, uint8_t reg, uint8_t value );

/**
 * @brief Ultrasonic 2 register reading function.
 * @details This function reads a PGA460 register and checks the diagnostic byte and response checksum.
 * @param[in] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] value : Register value on success.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid output pointer, communication or checksum error,
 *         @li @c -3 - Device diagnostic error.
 * See #err_t definition for detailed explanation.
 * @note The output value is written only on success. A read clears latched UART diagnostics.
 * Reading a clear-on-read register such as DEV_STAT1 also acknowledges its stored flags.
 */
err_t ultrasonic2_read_register ( ultrasonic2_t *ctx, uint8_t reg, uint8_t *value );

/**
 * @brief Ultrasonic 2 single-object measurement function.
 * @details This function sends a preset 1 burst, waits for the record interval and reads the first echo.
 * The distance calculation halves the raw echo time and subtracts a 50 us one-way offset.
 * The driver uses zero for negative corrected times and converts at 343 m/s, rounding to the nearest millimetre.
 * @param[in] ctx : Click context object.
 * See #ultrasonic2_t object definition for detailed explanation.
 * @param[out] measurement : Echo timing, distance, width and amplitude on success.
 * See #ultrasonic2_measurement_t object definition for detailed explanation.
 * @return @li @c  0 - Echo detected,
 *         @li @c -1 - Invalid output pointer, communication or checksum error,
 *         @li @c -2 - No object detected,
 *         @li @c -3 - Device diagnostic error or object detection disabled.
 * See #err_t definition for detailed explanation.
 * @note Run #ultrasonic2_default_cfg after each power-up before taking measurements.
 * This call waits 100 ms for capture completion, including when UART transfers are nonblocking.
 * The output structure is left untouched on error or when no object is detected.
 * Keep the burst, gain, threshold and timing compensation settings together when tuning a different transducer.
 */
err_t ultrasonic2_get_measurement ( ultrasonic2_t *ctx, ultrasonic2_measurement_t *measurement );

#ifdef __cplusplus
}
#endif
#endif // ULTRASONIC2_H

/*! @} */ // ultrasonic2

// ------------------------------------------------------------------------ END
