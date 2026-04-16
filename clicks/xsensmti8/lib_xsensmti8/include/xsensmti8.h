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
 * @file xsensmti8.h
 * @brief This file contains API for XSENS MTi-8 Click Driver.
 */

#ifndef XSENSMTI8_H
#define XSENSMTI8_H

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
 * @addtogroup xsensmti8 XSENS MTi-8 Click Driver
 * @brief API for configuring and manipulating XSENS MTi-8 Click driver.
 * @{
 */

/**
 * @defgroup xsensmti8_cmd XSENS MTi-8 Device Settings
 * @brief Settings for registers of XSENS MTi-8 Click driver.
 */

/**
 * @addtogroup xsensmti8_cmd
 * @{
 */

/**
 * @briefXSENS MTi-8 preamble and bus identifier.
 * @details Specified preamble and bus identifier of XSENS MTi-8 Click driver.
 */
#define XSENSMTI8_PREAMBLE                      0xFA
#define XSENSMTI8_BID                           0xFF

/**
 * @brief XSENS MTi-8 message identifiers.
 * @details Specified setting for message identifiers of XSENS MTi-8 Click driver.
 */
#define XSENSMTI8_MID_WAKE_UP                   0x3E
#define XSENSMTI8_MID_WAKE_UP_ACK               0x3F
#define XSENSMTI8_MID_GO_TO_CONFIG              0x30
#define XSENSMTI8_MID_GO_TO_CONFIG_ACK          0x31
#define XSENSMTI8_MID_GO_TO_MEASUREMENT         0x10
#define XSENSMTI8_MID_GO_TO_MEASUREMENT_ACK     0x11
#define XSENSMTI8_MID_RESET                     0x40
#define XSENSMTI8_MID_RESET_ACK                 0x41
#define XSENSMTI8_MID_DEVICE_ID                 0x00
#define XSENSMTI8_MID_DEVICE_ID_ACK             0x01
#define XSENSMTI8_MID_PRODUCT_CODE              0x1C
#define XSENSMTI8_MID_PRODUCT_CODE_ACK          0x1D
#define XSENSMTI8_MID_HARDWARE_VERSION          0x1E
#define XSENSMTI8_MID_HARDWARE_VERSION_ACK      0x1F
#define XSENSMTI8_MID_FW_REV                    0x12
#define XSENSMTI8_MID_FW_REV_ACK                0x13
#define XSENSMTI8_MID_SELFTEST                  0x24
#define XSENSMTI8_MID_SELFTEST_ACK              0x25
#define XSENSMTI8_MID_ERROR                     0x42
#define XSENSMTI8_MID_WARNING                   0x43
#define XSENSMTI8_MID_BAUDRATE                  0x18
#define XSENSMTI8_MID_BAUDRATE_ACK              0x19
#define XSENSMTI8_MID_OPTION_FLAGS              0x48
#define XSENSMTI8_MID_OPTION_FLAGS_ACK          0x49
#define XSENSMTI8_MID_LOCATION_ID               0x84
#define XSENSMTI8_MID_LOCATION_ID_ACK           0x85
#define XSENSMTI8_MID_RESTORE_FACTORY_DEF       0x0E
#define XSENSMTI8_MID_RESTORE_FACTORY_DEF_ACK   0x0F
#define XSENSMTI8_MID_SYNC_SETTINGS             0x2C
#define XSENSMTI8_MID_SYNC_SETTINGS_ACK         0x2D
#define XSENSMTI8_MID_CONFIGURATION             0x0C
#define XSENSMTI8_MID_CONFIGURATION_ACK         0x0D
#define XSENSMTI8_MID_OUTPUT_CONFIGURATION      0xC0
#define XSENSMTI8_MID_OUTPUT_CONFIGURATION_ACK  0xC1
#define XSENSMTI8_MID_ALIGNMENT_ROTATION        0xEC
#define XSENSMTI8_MID_ALIGNMENT_ROTATION_ACK    0xED
#define XSENSMTI8_MID_DATA                      0x34
#define XSENSMTI8_MID_MT_DATA_2                 0x36
#define XSENSMTI8_MID_LAT_LON_ALT               0x6E
#define XSENSMTI8_MID_LAT_LON_ALT_ACK           0x6F
#define XSENSMTI8_MID_AVAILABLE_FILT_PROF       0x62
#define XSENSMTI8_MID_AVAILABLE_FILT_PROF_ACK   0x63
#define XSENSMTI8_MID_FILT_PROF                 0x64
#define XSENSMTI8_MID_FILT_PROF_ACK             0x65
#define XSENSMTI8_MID_GNSS_PLATFORM             0x76
#define XSENSMTI8_MID_GNSS_PLATFORM_ACK         0x77
#define XSENSMTI8_MID_GNSS_LEVER_ARM            0x68
#define XSENSMTI8_MID_GNSS_LEVER_ARM_ACK        0x69
#define XSENSMTI8_MID_GNSS_RX_SETTINGS          0xAC
#define XSENSMTI8_MID_GNSS_RX_SETTINGS_ACK      0xAD
#define XSENSMTI8_MID_RESET_ORIENTATION         0xA4
#define XSENSMTI8_MID_RESET_ORIENTATION_ACK     0xA5
#define XSENSMTI8_MID_NO_ROTATION               0x22
#define XSENSMTI8_MID_NO_ROTATION_ACK           0x23
#define XSENSMTI8_MID_UTC_TIME                  0x60
#define XSENSMTI8_MID_UTC_TIME_ACK              0x61
#define XSENSMTI8_MID_ADJUST_UTC_TIME           0xA8
#define XSENSMTI8_MID_ADJUST_UTC_TIME_ACK       0xA9
#define XSENSMTI8_MID_ICC_COMMAND               0x74
#define XSENSMTI8_MID_ICC_COMMAND_ACK           0x75
#define XSENSMTI8_MID_FORWARD_GNSS_DATA         0xE2
#define XSENSMTI8_MID_FORWARD_GNSS_DATA_ACK     0xE3

/**
 * @brief XSENS MTi-8 XDI packet identifiers.
 * @details Specified setting for XDI packet identifiers of XSENS MTi-8 Click driver.
 */
#define XSENSMTI8_XDI_TEMPERATURE               0x0810
#define XSENSMTI8_XDI_UTC_TIME                  0x1010
#define XSENSMTI8_XDI_PACKET_COUNTER            0x1020
#define XSENSMTI8_XDI_SAMPLE_TIME_FINE          0x1060
#define XSENSMTI8_XDI_SAMPLE_TIME_COURSE        0x1070
#define XSENSMTI8_XDI_QUARTERNION               0x2010
#define XSENSMTI8_XDI_ROTATION_MATRIX           0x2020
#define XSENSMTI8_XDI_EULER_ANGLES              0x2030
#define XSENSMTI8_XDI_BARO_PRESSURE             0x3010
#define XSENSMTI8_XDI_DELTA_V                   0x4010
#define XSENSMTI8_XDI_ACCELERATION              0x4020
#define XSENSMTI8_XDI_FREE_ACCELERATION         0x4030
#define XSENSMTI8_XDI_ACCELERATION_HR           0x4040
#define XSENSMTI8_XDI_ALTITUDE_ELLIPSOID        0x5020
#define XSENSMTI8_XDI_POSITION_ECEF             0x5030
#define XSENSMTI8_XDI_LAT_LON                   0x5040
#define XSENSMTI8_XDI_GNSS_PVT_DATA             0x7010
#define XSENSMTI8_XDI_GNSS_SAT_INFO             0x7020
#define XSENSMTI8_XDI_GNSS_PVT_PULSE            0x7030
#define XSENSMTI8_XDI_RATE_OF_TURN              0x8020
#define XSENSMTI8_XDI_DELTA_Q                   0x8030
#define XSENSMTI8_XDI_RATE_OF_TURN_HR           0x8040
#define XSENSMTI8_XDI_RAW_ACC_GYR_MAG_TEMP      0xA010
#define XSENSMTI8_XDI_RAW_GYRO_TEMP             0xA020
#define XSENSMTI8_XDI_MAGNETIC_FIELD            0xC020
#define XSENSMTI8_XDI_VELOCITY_XYZ              0xD010
#define XSENSMTI8_XDI_STATUS_BYTE               0xE010
#define XSENSMTI8_XDI_STATUS_WORD               0xE020
#define XSENSMTI8_XDI_DEVICE_ID                 0xE080
#define XSENSMTI8_XDI_LOCATION_ID               0xE090
#define XSENSMTI8_XDI_FREQUENCY_1HZ             ( 1u )
#define XSENSMTI8_XDI_FREQUENCY_2HZ             ( 2u )
#define XSENSMTI8_XDI_FREQUENCY_3HZ             ( 3u )
#define XSENSMTI8_XDI_FREQUENCY_5HZ             ( 5u )
#define XSENSMTI8_XDI_FREQUENCY_10HZ            ( 10u )
#define XSENSMTI8_XDI_FREQUENCY_25HZ            ( 25u )
#define XSENSMTI8_XDI_FREQUENCY_50HZ            ( 50u )
#define XSENSMTI8_XDI_FREQUENCY_100HZ           ( 100u )

/**
 * @brief XSENS MTi-8 MID warning codes.
 * @details Specified setting for MID warning codes of XSENS MTi-8 Click driver.
 */
#define XSENSMTI8_WARNING_REFUSED               0x00000191ul
#define XSENSMTI8_WARNING_TIMEOUT               0x00000192ul
#define XSENSMTI8_WARNING_FAILED                0x00000193ul
#define XSENSMTI8_WARNING_LOST                  0x00000195ul
#define XSENSMTI8_WARNING_INCOMPLETE            0x00000197ul

/**
 * @brief XSENS MTi-8 response timeout settings.
 * @details Specified response timeout settings of XSENS MTi-8 Click driver.
 */
#define XSENSMTI8_RSP_TIMEOUT_1S                1000
#define XSENSMTI8_RSP_NUM_TRIES                 3

/**
 * @brief XSENS MTi-8 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define XSENSMTI8_TX_DRV_BUFFER_SIZE            256
#define XSENSMTI8_RX_DRV_BUFFER_SIZE            256
#define XSENSMTI8_DATA_BUFFER_SIZE              254

/*! @} */ // xsensmti8_cmd

/**
 * @defgroup xsensmti8_map XSENS MTi-8 MikroBUS Map
 * @brief MikroBUS pin mapping of XSENS MTi-8 Click driver.
 */

/**
 * @addtogroup xsensmti8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of XSENS MTi-8 Click to the selected MikroBUS.
 */
#define XSENSMTI8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // xsensmti8_map
/*! @} */ // xsensmti8

/**
 * @brief XSENS MTi-8 Click message structure object.
 * @details Message structure object definition of XSENS MTi-8 Click driver.
 */
typedef struct
{
    uint8_t msg_id;                                     /**< Message ID. */
    uint8_t data_buf[ XSENSMTI8_DATA_BUFFER_SIZE ];     /**< Data buffer. */
    uint16_t data_len;                                  /**< Data length. */
    
} xsensmti8_msg_t;

/**
 * @brief XSENS MTi-8 Click context object.
 * @details Context object definition of XSENS MTi-8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< Clear to send pin. */

    // Input pins
    digital_in_t rts;               /**< Ready to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ XSENSMTI8_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ XSENSMTI8_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    xsensmti8_msg_t cmd_msg;         /**< Xbus command message. */
    xsensmti8_msg_t rsp_msg;         /**< Xbus response message. */

} xsensmti8_t;

/**
 * @brief XSENS MTi-8 Click configuration object.
 * @details Configuration object definition of XSENS MTi-8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< Clear to send pin. */
    pin_name_t rts;                 /**< Ready to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} xsensmti8_cfg_t;

/**
 * @brief XSENS MTi-8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    XSENSMTI8_OK = 0,
    XSENSMTI8_ERROR = -1

} xsensmti8_return_value_t;

/*!
 * @addtogroup xsensmti8 XSENS MTi-8 Click Driver
 * @brief API for configuring and manipulating XSENS MTi-8 Click driver.
 * @{
 */

/**
 * @brief XSENS MTi-8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #xsensmti8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void xsensmti8_cfg_setup ( xsensmti8_cfg_t *cfg );

/**
 * @brief XSENS MTi-8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #xsensmti8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xsensmti8_init ( xsensmti8_t *ctx, xsensmti8_cfg_t *cfg );

/**
 * @brief XSENS MTi-8 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xsensmti8_generic_write ( xsensmti8_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief XSENS MTi-8 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xsensmti8_generic_read ( xsensmti8_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief XSENS MTi-8 set RST pin state function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xsensmti8_set_rst_pin ( xsensmti8_t *ctx, uint8_t state );

/**
 * @brief XSENS MTi-8 set CTS pin state function.
 * @details This function sets the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xsensmti8_set_cts_pin ( xsensmti8_t *ctx, uint8_t state );

/**
 * @brief XSENS MTi-8 get RTS pin state function.
 * @details This function reads the logic state of the RTS pin.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xsensmti8_get_rts_pin ( xsensmti8_t *ctx );

/**
 * @brief XSENS MTi-8 reset device function.
 * @details This function performs a hardware reset of the XSENS MTi-8 Click board.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xsensmti8_reset_device ( xsensmti8_t *ctx );

/**
 * @brief XSENS MTi-8 clear buffers function.
 * @details This function clears the UART buffers and internal message structures.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xsensmti8_clear_buffers ( xsensmti8_t *ctx );

/**
 * @brief XSENS MTi-8 send message function.
 * @details This function sends a desired command message from the Click context object.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t xsensmti8_send_message ( xsensmti8_t *ctx );

/**
 * @brief XSENS MTi-8 read message function.
 * @details This function reads response message from the ring buffer and stores it in
 * the Click context object.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t xsensmti8_read_message ( xsensmti8_t *ctx );

/**
 * @brief XSENS MTi-8 wait for specific message function.
 * @details This function waits and checks for a specific message ID in the received response.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @param[in] msg_id : Expected message ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t xsensmti8_wait_message ( xsensmti8_t *ctx, uint8_t msg_id );

#ifdef __cplusplus
}
#endif
#endif // XSENSMTI8_H

/*! @} */ // xsensmti8

// ------------------------------------------------------------------------ END
