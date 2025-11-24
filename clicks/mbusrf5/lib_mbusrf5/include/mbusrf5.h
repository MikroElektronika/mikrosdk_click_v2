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
 * @file mbusrf5.h
 * @brief This file contains API for M-BUS RF 5 Click Driver.
 */

#ifndef MBUSRF5_H
#define MBUSRF5_H

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
 * @addtogroup mbusrf5 M-BUS RF 5 Click Driver
 * @brief API for configuring and manipulating M-BUS RF 5 Click driver.
 * @{
 */

/**
 * @defgroup mbusrf5_cmd M-BUS RF 5 Device Settings
 * @brief Settings of M-BUS RF 5 Click driver.
 */

/**
 * @addtogroup mbusrf5_cmd
 * @{
 */

/**
 * @brief M-BUS RF 5 start byte.
 * @details Specified start byte of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_START_BYTE                              0x02

/**
 * @brief M-BUS RF 5 commands type settings.
 * @details Specified commands type settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_CMD_TYPE_REQ                            0x00
#define MBUSRF5_CMD_TYPE_CNF                            0x40
#define MBUSRF5_CMD_TYPE_IND                            0x80
#define MBUSRF5_CMD_TYPE_MASK                           0xC0

/**
 * @brief M-BUS RF 5 commands request settings.
 * @details Specified commands request settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_CMD_REQ_DATAEX                          0x01
#define MBUSRF5_CMD_REQ_DATARX_START                    0x02
#define MBUSRF5_CMD_REQ_DATARX_STOP                     0x03
#define MBUSRF5_CMD_REQ_SET                             0x04
#define MBUSRF5_CMD_REQ_GET                             0x05
#define MBUSRF5_CMD_REQ_RESET                           0x06
#define MBUSRF5_CMD_REQ_STANDBY                         0x07
#define MBUSRF5_CMD_REQ_SHUTDOWN                        0x08
#define MBUSRF5_CMD_REQ_FACTORYRESET                    0x10
#define MBUSRF5_CMD_REQ_SETRAM                          0x12
#define MBUSRF5_CMD_REQ_GETRAM                          0x13

/**
 * @brief M-BUS RF 5 commands confirmation settings.
 * @details Specified commands confirmation settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_CMD_CNF_DATAEX                          0x41
#define MBUSRF5_CMD_CNF_DATARX_START                    0x42
#define MBUSRF5_CMD_CNF_DATARX_STOP                     0x43
#define MBUSRF5_CMD_CNF_SET                             0x44
#define MBUSRF5_CMD_CNF_GET                             0x45
#define MBUSRF5_CMD_CNF_SETRAM                          0x52
#define MBUSRF5_CMD_CNF_GETRAM                          0x53

/**
 * @brief M-BUS RF 5 commands indication settings.
 * @details Specified commands indication settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_CMD_IND_DATAEX                          0x81
#define MBUSRF5_CMD_IND_RESET                           0x86
#define MBUSRF5_CMD_IND_STANDBY                         0x87

/**
 * @brief M-BUS RF 5 user settings option list.
 * @details Specified user settings option list of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_OPT_STATUS                              0x01
#define MBUSRF5_OPT_WMBUS_RX_MODE                       0x03
#define MBUSRF5_OPT_WMBUS_TX_MODE                       0x04
#define MBUSRF5_OPT_WMBUS_FRAME_FORMAT                  0x05
#define MBUSRF5_OPT_WMBUS_DATA                          0x06
#define MBUSRF5_OPT_WMBUS_ROLE                          0x07
#define MBUSRF5_OPT_PARAMETER                           0x09
#define MBUSRF5_OPT_UART_BAUDRATE                       0x0A
#define MBUSRF5_OPT_TX_POWER                            0x0B
#define MBUSRF5_OPT_CFG_FLAGS                           0x0C
#define MBUSRF5_OPT_RSSI                                0x0D
#define MBUSRF5_OPT_TIMESTAMP                           0x0E
#define MBUSRF5_OPT_FW_VERSION                          0x81
#define MBUSRF5_OPT_PRODUCT_NAME                        0x82

/**
 * @brief M-BUS RF 5 STATUS settings.
 * @details Specified STATUS settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_STATUS_OK                               0x00
#define MBUSRF5_STATUS_NOK                              0x01
#define MBUSRF5_STATUS_INV_CONFIG                       0x02
#define MBUSRF5_STATUS_NOT_SUPP_BY_MODULE               0x03
#define MBUSRF5_STATUS_INV_OPT                          0x04
#define MBUSRF5_STATUS_OPT_NOT_SUPP                     0x05
#define MBUSRF5_STATUS_NOT_SUPP_BY_ROLE                 0x06

/**
 * @brief M-BUS RF 5 WMBUS_RX_MODE settings.
 * @details Specified WMBUS_RX_MODE settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_WMBUS_RX_MODE_S                         0x00
#define MBUSRF5_WMBUS_RX_MODE_T                         0x02
#define MBUSRF5_WMBUS_RX_MODE_C_T                       0x03
#define MBUSRF5_WMBUS_RX_MODE_C                         0x05

/**
 * @brief M-BUS RF 5 WMBUS_TX_MODE settings.
 * @details Specified WMBUS_TX_MODE settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_WMBUS_TX_MODE_S                         0x00
#define MBUSRF5_WMBUS_TX_MODE_T                         0x01
#define MBUSRF5_WMBUS_TX_MODE_C                         0x04

/**
 * @brief M-BUS RF 5 WMBUS_FRAME_FORMAT settings.
 * @details Specified WMBUS_FRAME_FORMAT settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_WMBUS_FRAME_FORMAT_A                    0x01
#define MBUSRF5_WMBUS_FRAME_FORMAT_B                    0x02

/**
 * @brief M-BUS RF 5 WMBUS_ROLE settings.
 * @details Specified WMBUS_ROLE settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_WMBUS_ROLE_METER                        0x01
#define MBUSRF5_WMBUS_ROLE_GATEWAY                      0x02

/**
 * @brief M-BUS RF 5 UART_BAUDRATE settings.
 * @details Specified UART_BAUDRATE settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_UART_BAUDRATE_9600                      0x00
#define MBUSRF5_UART_BAUDRATE_115200                    0x01
#define MBUSRF5_UART_BAUDRATE_230400                    0x02
#define MBUSRF5_UART_BAUDRATE_460800                    0x03
#define MBUSRF5_UART_BAUDRATE_921600                    0x04

/**
 * @brief M-BUS RF 5 TX_POWER settings.
 * @details Specified TX_POWER settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_TX_POWER_MIN                            0x00
#define MBUSRF5_TX_POWER_1                              0x01
#define MBUSRF5_TX_POWER_2                              0x02
#define MBUSRF5_TX_POWER_3                              0x03
#define MBUSRF5_TX_POWER_4                              0x04
#define MBUSRF5_TX_POWER_5                              0x05
#define MBUSRF5_TX_POWER_6                              0x06
#define MBUSRF5_TX_POWER_7                              0x07
#define MBUSRF5_TX_POWER_8                              0x08
#define MBUSRF5_TX_POWER_9                              0x09
#define MBUSRF5_TX_POWER_A                              0x0A
#define MBUSRF5_TX_POWER_B                              0x0B
#define MBUSRF5_TX_POWER_C                              0x0C
#define MBUSRF5_TX_POWER_D                              0x0D
#define MBUSRF5_TX_POWER_MAX                            0x0E

/**
 * @brief M-BUS RF 5 CFG_FLAGS settings.
 * @details Specified CFG_FLAGS settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_CFG_FLAGS_RSSI_AND_TIMESTAMP_DISABLED   0x00
#define MBUSRF5_CFG_FLAGS_RSSI_ENABLED                  0x01
#define MBUSRF5_CFG_FLAGS_TIMESTAMP_ENABLED             0x02
#define MBUSRF5_CFG_FLAGS_RSSI_AND_TIMESTAMP_ENABLED    0x03

/**
 * @brief M-BUS RF 5 response timeout settings.
 * @details Specified response timeout settings of M-BUS RF 5 Click driver.
 */
#define MBUSRF5_RSP_TIMEOUT_1000MS                      1000
#define MBUSRF5_WAIT_TIME_1S                            1
#define MBUSRF5_WAIT_TIME_3S                            3

/**
 * @brief M-BUS RF 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define MBUSRF5_TX_DRV_BUFFER_SIZE                      300
#define MBUSRF5_RX_DRV_BUFFER_SIZE                      300
#define MBUSRF5_PAYLOAD_BUFFER_SIZE                     256

/*! @} */ // mbusrf5_cmd

/**
 * @defgroup mbusrf5_map M-BUS RF 5 MikroBUS Map
 * @brief MikroBUS pin mapping of M-BUS RF 5 Click driver.
 */

/**
 * @addtogroup mbusrf5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of M-BUS RF 5 Click to the selected MikroBUS.
 */
#define MBUSRF5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.busy = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // mbusrf5_map
/*! @} */ // mbusrf5

/**
 * @brief M-BUS RF 5 Click command packet structure object.
 * @details Command packet structure object definition of M-BUS RF 5 Click driver.
 */
typedef struct
{
    uint8_t cmd;                                    /**< Command code. */
    uint8_t payload[ MBUSRF5_PAYLOAD_BUFFER_SIZE ]; /**< Payload buffer. */
    uint16_t payload_len;                           /**< Payload length. */
    
} mbusrf5_packet_t;

/**
 * @brief M-BUS RF 5 Click context object.
 * @details Context object definition of M-BUS RF 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t wup;              /**< Wake-up pin (falling-edge). */

    // Input pins
    digital_in_t busy;              /**< Busy module pin (active high). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ MBUSRF5_RX_DRV_BUFFER_SIZE ];   /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ MBUSRF5_TX_DRV_BUFFER_SIZE ];   /**< TX Buffer size. */

    mbusrf5_packet_t cmd_pkt;       /**< Command packet structure. */
    mbusrf5_packet_t evt_pkt;       /**< Confirmation/Indication event packet structure. */

} mbusrf5_t;

/**
 * @brief M-BUS RF 5 Click configuration object.
 * @details Configuration object definition of M-BUS RF 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t wup;                 /**< Wake-up pin (falling-edge). */
    pin_name_t busy;                /**< Busy module pin (active high). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} mbusrf5_cfg_t;

/**
 * @brief M-BUS RF 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MBUSRF5_OK = 0,
    MBUSRF5_ERROR = -1

} mbusrf5_return_value_t;

/*!
 * @addtogroup mbusrf5 M-BUS RF 5 Click Driver
 * @brief API for configuring and manipulating M-BUS RF 5 Click driver.
 * @{
 */

/**
 * @brief M-BUS RF 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mbusrf5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mbusrf5_cfg_setup ( mbusrf5_cfg_t *cfg );

/**
 * @brief M-BUS RF 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mbusrf5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf5_init ( mbusrf5_t *ctx, mbusrf5_cfg_t *cfg );

/**
 * @brief M-BUS RF 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf5_generic_write ( mbusrf5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief M-BUS RF 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf5_generic_read ( mbusrf5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief M-BUS RF 5 set WUP pin function.
 * @details This function sets the wake-up (WUP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mbusrf5_set_wup_pin ( mbusrf5_t *ctx, uint8_t state );

/**
 * @brief M-BUS RF 5 set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mbusrf5_set_rst_pin ( mbusrf5_t *ctx, uint8_t state );

/**
 * @brief M-BUS RF 5 get BUSY pin function.
 * @details This function returns the module busy pin logic state.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mbusrf5_get_busy_pin ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mbusrf5_reset_device ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 send command function.
 * @details This function sends a desired command packet from the Click context object.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return @li @c  0 - Packet is sent,
 *         @li @c -1 - Timeout error.
 * @note None.
 */
err_t mbusrf5_send_cmd ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 read event function.
 * @details This function reads an event packet from the ring buffer and stores it in
 * the Click context object. It waits up to 1 second for a packet, and if there's no packet
 * received it returns an error.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf5_read_event ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 wait for event function.
 * @details This function waits for the desired event packet to arrive and stores it
 * in the Click context object.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] cmd : Expected packet command byte.
 * @param[in] max_time_s : Maximum wait time in seconds.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mbusrf5_wait_for_event ( mbusrf5_t *ctx, uint8_t cmd, uint8_t max_time_s );

/**
 * @brief M-BUS RF 5 clear buffers function.
 * @details This function clears the ring buffers and the event packet object.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void mbusrf5_clear_buffers ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 set user settings function.
 * @details This function writes data to a desired user settings option in RAM.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] option : User settings option.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mbusrf5_set_user_setting_ram ( mbusrf5_t *ctx, uint8_t option, uint8_t data_in );

/**
 * @brief M-BUS RF 5 get user settings function.
 * @details This function reads data from the desired user settings option in RAM and stores it
 * in the Click context event packet object.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] option : User settings option.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mbusrf5_get_user_setting_ram ( mbusrf5_t *ctx, uint8_t option );

/**
 * @brief M-BUS RF 5 set user settings function.
 * @details This function writes data to a desired user settings option in FLASH.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] option : User settings option.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mbusrf5_set_user_setting_flash ( mbusrf5_t *ctx, uint8_t option, uint8_t data_in );

/**
 * @brief M-BUS RF 5 get user settings function.
 * @details This function reads data from the desired user settings option in FLASH and stores it
 * in the Click context event packet object.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @param[in] option : User settings option.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t mbusrf5_get_user_setting_flash ( mbusrf5_t *ctx, uint8_t option );

#ifdef __cplusplus
}
#endif
#endif // MBUSRF5_H

/*! @} */ // mbusrf5

// ------------------------------------------------------------------------ END
