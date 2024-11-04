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
 * @file neomesh2.h
 * @brief This file contains API for NeoMesh 2 Click Driver.
 */

#ifndef NEOMESH2_H
#define NEOMESH2_H

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
 * @addtogroup neomesh2 NeoMesh 2 Click Driver
 * @brief API for configuring and manipulating NeoMesh 2 Click driver.
 * @{
 */

/**
 * @defgroup neomesh2_cmd NeoMesh 2 Device Settings
 * @brief Settings for registers of NeoMesh 2 Click driver.
 */

/**
 * @addtogroup neomesh2_cmd
 * @{
 */

/**
 * @brief NeoMesh 2 AAPI control commands.
 * @details Specified setting for AAPI control commands of NeoMesh 2 Click driver.
 */
#define NEOMESH2_CMD_NACK_SEND                  0x02
#define NEOMESH2_CMD_ACK_SEND                   0x03
#define NEOMESH2_CMD_NODE_STATUS                0x07
#define NEOMESH2_CMD_NODE_INFO                  0x08
#define NEOMESH2_CMD_NEIGHBOUR_LIST             0x09
#define NEOMESH2_CMD_NETWORK_COMMAND            0x0A
#define NEOMESH2_CMD_SAPI_TO_AAPI               0x0B
#define NEOMESH2_CMD_ROUTE_INFO                 0x0C
#define NEOMESH2_CMD_WES_COMMAND                0x10
#define NEOMESH2_CMD_WES_SETUP_RSP              0x11
#define NEOMESH2_CMD_GET_SW_VERSION             0x14
#define NEOMESH2_CMD_ALT_MODE                   0x20

/**
 * @brief NeoMesh 2 application data response.
 * @details Specified setting for application data response of NeoMesh 2 Click driver.
 */
#define NEOMESH2_RSP_ACK                        0x50
#define NEOMESH2_RSP_NACK                       0x51
#define NEOMESH2_RSP_ACK_HOST                   0x52
#define NEOMESH2_RSP_ACK_HOST_HAPA              0x53
#define NEOMESH2_RSP_NACK_HOST                  0x54
#define NEOMESH2_RSP_NACK_HOST_HAPA             0x55
#define NEOMESH2_RSP_NACK_SEND                  0x56
#define NEOMESH2_RSP_NACK_DROP                  0x57
#define NEOMESH2_RSP_NODE_INFO                  0x58
#define NEOMESH2_RSP_NEIGHBOUR_LIST             0x59
#define NEOMESH2_RSP_NETWORK_COMMAND            0x5A
#define NEOMESH2_RSP_ROUTE_INFO                 0x5C
#define NEOMESH2_RSP_WES_STATUS                 0x60
#define NEOMESH2_RSP_WES_SETUP                  0x61
#define NEOMESH2_RSP_GET_SW_VERSION             0x64
#define NEOMESH2_RSP_ALT_MODE                   0x70

/**
 * @brief NeoMesh 2 SAPI control commands.
 * @details Specified setting for SAPI control commands of NeoMesh 2 Click driver.
 */
#define NEOMESH2_SAPI_CMD_LOGIN                 0x0103u
#define NEOMESH2_SAPI_CMD_RESET_LIST_ITERATOR   0x0104u
#define NEOMESH2_SAPI_CMD_GET_LIST              0x0105u
#define NEOMESH2_SAPI_CMD_GET_SETTING_FLASH     0x0106u
#define NEOMESH2_SAPI_CMD_GET_SETTING_RAM       0x0107u
#define NEOMESH2_SAPI_CMD_COMMIT_SETTINGS       0x0108u
#define NEOMESH2_SAPI_CMD_DISCARD_SETTINGS      0x0109u
#define NEOMESH2_SAPI_CMD_SET_SETTING           0x010Au
#define NEOMESH2_SAPI_CMD_START_PROTOCOL_STACK  0x0112u
#define NEOMESH2_SAPI_CMD_START_BOOTLOADER      0x0113u
#define NEOMESH2_SAPI_HEADER                    0x3E
#define NEOMESH2_SAPI_TRAIL                     0x21

/**
 * @brief NeoMesh 2 system data response.
 * @details Specified setting for system data response of NeoMesh 2 Click driver.
 */
#define NEOMESH2_SAPI_RSP_OK                    0x0380u
#define NEOMESH2_SAPI_RSP_ERROR                 0x0381u
#define NEOMESH2_SAPI_RSP_BOOTLOADER_START      0x0382u
#define NEOMESH2_SAPI_RSP_PROTOCOL_STACK_START  0x0383u
#define NEOMESH2_SAPI_RSP_PROTOCOL_STACK_ERROR  0x0384u
#define NEOMESH2_SAPI_RSP_RESET                 0x0385u
#define NEOMESH2_SAPI_RSP_SETTINGS_LIST_OUTPUT  0x0185u
#define NEOMESH2_SAPI_RSP_SETTINGS_VALUE        0x0186u

/**
 * @brief NeoMesh 2 login password settings.
 * @details Specified setting for login password of NeoMesh 2 Click driver.
 */
#define NEOMESH2_SAPI_LOGIN_PASSWORD_0          0x4C
#define NEOMESH2_SAPI_LOGIN_PASSWORD_1          0x76
#define NEOMESH2_SAPI_LOGIN_PASSWORD_2          0x6C
#define NEOMESH2_SAPI_LOGIN_PASSWORD_3          0x31
#define NEOMESH2_SAPI_LOGIN_PASSWORD_4          0x30

/**
 * @brief NeoMesh 2 SAPI settings ID.
 * @details Specified setting for SAPI settings ID of NeoMesh 2 Click driver.
 */
#define NEOMESH2_SAPI_SETTINGS_ID_NODE_ID       0x0A

/**
 * @brief NeoMesh 2 CTS/WUP timeout wait.
 * @details Specified setting for CTS/WUP timeout wait of NeoMesh 2 Click driver.
 */
#define NEOMESH2_TIMEOUT_MS                     20000ul

/**
 * @brief NeoMesh 2 payload length.
 * @details Specified setting for payload length of NeoMesh 2 Click driver.
 */
#define NEOMESH2_MAX_PAYLOAD_LEN                255

/**
 * @brief NeoMesh 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NEOMESH2_TX_DRV_BUFFER_SIZE             300u
#define NEOMESH2_RX_DRV_BUFFER_SIZE             300u

/*! @} */ // neomesh2_cmd

/**
 * @defgroup neomesh2_map NeoMesh 2 MikroBUS Map
 * @brief MikroBUS pin mapping of NeoMesh 2 Click driver.
 */

/**
 * @addtogroup neomesh2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NeoMesh 2 Click to the selected MikroBUS.
 */
#define NEOMESH2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.app = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wes = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // neomesh2_map
/*! @} */ // neomesh2

/**
 * @brief NeoMesh 2 Click context object.
 * @details Context object definition of NeoMesh 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;  /**< Reset pin. */
    digital_out_t wes;  /**< Enable WES Client pin. */

    // Input pins
    digital_in_t app;   /**< APP pin, indicates activity of the embedded generic application (Active low). */
    digital_in_t cts;   /**< CTS pin, module ready to accept commands. */
    digital_in_t wup;   /**< WUP pin, indicates activity state of module (Active low). */

    // Modules
    uart_t uart;        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NEOMESH2_RX_DRV_BUFFER_SIZE ]; /**< Buffer size. */
    uint8_t uart_tx_buffer[ NEOMESH2_TX_DRV_BUFFER_SIZE ]; /**< Buffer size. */

} neomesh2_t;

/**
 * @brief NeoMesh 2 Click configuration object.
 * @details Configuration object definition of NeoMesh 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;  /**< RX pin. */
    pin_name_t tx_pin;  /**< TX pin. */

    // Additional gpio pins
    pin_name_t app;     /**< APP pin, indicates activity of the embedded generic application (Active low). */
    pin_name_t rst;     /**< Reset pin. */
    pin_name_t wes;     /**< Enable WES Client pin. */
    pin_name_t cts;     /**< CTS pin, module ready to accept commands. */
    pin_name_t wup;     /**< WUP pin, indicates activity state of module (Active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} neomesh2_cfg_t;

/**
 * @brief NeoMesh 2 Click data frame object.
 * @details AAPI data frame object definition of NeoMesh 2 Click driver.
 */
typedef struct
{
    uint8_t cmd;                                        /**< Command byte. */
    uint8_t len;                                        /**< Payload length. */
    uint8_t payload[ NEOMESH2_MAX_PAYLOAD_LEN ];   /**< Payload bytes. */

} neomesh2_aapi_frame_t;

/**
 * @brief NeoMesh 2 Click data frame object.
 * @details SAPI data frame object definition of NeoMesh 2 Click driver.
 */
typedef struct
{
    uint16_t cmd;                                       /**< Command word. */
    uint8_t len;                                        /**< Payload length. */
    uint8_t payload[ NEOMESH2_MAX_PAYLOAD_LEN ];   /**< Payload bytes. */

} neomesh2_sapi_frame_t;

/**
 * @brief NeoMesh 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NEOMESH2_OK = 0,
    NEOMESH2_ERROR = -1,
    NEOMESH2_TIMEOUT = -2

} neomesh2_return_value_t;

/*!
 * @addtogroup neomesh2 NeoMesh 2 Click Driver
 * @brief API for configuring and manipulating NeoMesh 2 Click driver.
 * @{
 */

/**
 * @brief NeoMesh 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #neomesh2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void neomesh2_cfg_setup ( neomesh2_cfg_t *cfg );

/**
 * @brief NeoMesh 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #neomesh2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh2_init ( neomesh2_t *ctx, neomesh2_cfg_t *cfg );

/**
 * @brief NeoMesh 2 send aapi frame function.
 * @details This function sends a desired AAPI frame by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @param[in] frame : AAPI frame structure to be sent.
 * See #neomesh2_aapi_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh2_send_aapi_frame ( neomesh2_t *ctx, neomesh2_aapi_frame_t *frame );

/**
 * @brief NeoMesh 2 read aapi frame function.
 * @details This function reads an AAPI frame by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @param[out] frame : AAPI frame structure read.
 * See #neomesh2_aapi_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error, frame is not read correctly,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh2_read_aapi_frame ( neomesh2_t *ctx, neomesh2_aapi_frame_t *frame );

/**
 * @brief NeoMesh 2 send sapi frame function.
 * @details This function sends a desired SAPI frame by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @param[in] frame : SAPI frame structure to be sent.
 * See #neomesh2_sapi_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh2_send_sapi_frame ( neomesh2_t *ctx, neomesh2_sapi_frame_t *frame );

/**
 * @brief NeoMesh 2 read sapi frame function.
 * @details This function reads an SAPI frame by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @param[out] frame : SAPI frame structure read.
 * See #neomesh2_sapi_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error, frame is not read correctly,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh2_read_sapi_frame ( neomesh2_t *ctx, neomesh2_sapi_frame_t *frame );

/**
 * @brief NeoMesh 2 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void neomesh2_set_rst_pin ( neomesh2_t *ctx, uint8_t state );

/**
 * @brief NeoMesh 2 set wes pin function.
 * @details This function sets the WES pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void neomesh2_set_wes_pin ( neomesh2_t *ctx, uint8_t state );

/**
 * @brief NeoMesh 2 get app pin function.
 * @details This function returns the APP pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t neomesh2_get_app_pin ( neomesh2_t *ctx );

/**
 * @brief NeoMesh 2 get cts pin function.
 * @details This function returns the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t neomesh2_get_cts_pin ( neomesh2_t *ctx );

/**
 * @brief NeoMesh 2 get wup pin function.
 * @details This function returns the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t neomesh2_get_wup_pin ( neomesh2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NEOMESH2_H

/*! @} */ // neomesh2

// ------------------------------------------------------------------------ END
