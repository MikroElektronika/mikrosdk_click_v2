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
 * @file neomesh868mhz.h
 * @brief This file contains API for NeoMesh 868MHz Click Driver.
 */

#ifndef NEOMESH868MHZ_H
#define NEOMESH868MHZ_H

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
 * @addtogroup neomesh868mhz NeoMesh 868MHz Click Driver
 * @brief API for configuring and manipulating NeoMesh 868MHz Click driver.
 * @{
 */

/**
 * @defgroup neomesh868mhz_cmd NeoMesh 868MHz Device Settings
 * @brief Settings for registers of NeoMesh 868MHz Click driver.
 */

/**
 * @addtogroup neomesh868mhz_cmd
 * @{
 */

/**
 * @brief NeoMesh 868MHz AAPI control commands.
 * @details Specified setting for AAPI control commands of NeoMesh 868MHz Click driver.
 */
#define NEOMESH868MHZ_CMD_NACK_SEND                 0x02
#define NEOMESH868MHZ_CMD_ACK_SEND                  0x03
#define NEOMESH868MHZ_CMD_NODE_STATUS               0x07
#define NEOMESH868MHZ_CMD_NODE_INFO                 0x08
#define NEOMESH868MHZ_CMD_NEIGHBOUR_LIST            0x09
#define NEOMESH868MHZ_CMD_NETWORK_COMMAND           0x0A
#define NEOMESH868MHZ_CMD_SAPI_TO_AAPI              0x0B
#define NEOMESH868MHZ_CMD_ROUTE_INFO                0x0C
#define NEOMESH868MHZ_CMD_WES_COMMAND               0x10
#define NEOMESH868MHZ_CMD_WES_SETUP_RSP             0x11
#define NEOMESH868MHZ_CMD_GET_SW_VERSION            0x14
#define NEOMESH868MHZ_CMD_ALT_MODE                  0x20

/**
 * @brief NeoMesh 868MHz application data response.
 * @details Specified setting for application data response of NeoMesh 868MHz Click driver.
 */
#define NEOMESH868MHZ_RSP_ACK                       0x50
#define NEOMESH868MHZ_RSP_NACK                      0x51
#define NEOMESH868MHZ_RSP_ACK_HOST                  0x52
#define NEOMESH868MHZ_RSP_ACK_HOST_HAPA             0x53
#define NEOMESH868MHZ_RSP_NACK_HOST                 0x54
#define NEOMESH868MHZ_RSP_NACK_HOST_HAPA            0x55
#define NEOMESH868MHZ_RSP_NACK_SEND                 0x56
#define NEOMESH868MHZ_RSP_NACK_DROP                 0x57
#define NEOMESH868MHZ_RSP_NODE_INFO                 0x58
#define NEOMESH868MHZ_RSP_NEIGHBOUR_LIST            0x59
#define NEOMESH868MHZ_RSP_NETWORK_COMMAND           0x5A
#define NEOMESH868MHZ_RSP_ROUTE_INFO                0x5C
#define NEOMESH868MHZ_RSP_WES_STATUS                0x60
#define NEOMESH868MHZ_RSP_WES_SETUP                 0x61
#define NEOMESH868MHZ_RSP_GET_SW_VERSION            0x64
#define NEOMESH868MHZ_RSP_ALT_MODE                  0x70

/**
 * @brief NeoMesh 868MHz SAPI control commands.
 * @details Specified setting for SAPI control commands of NeoMesh 868MHz Click driver.
 */
#define NEOMESH868MHZ_SAPI_CMD_LOGIN                0x0103u
#define NEOMESH868MHZ_SAPI_CMD_RESET_LIST_ITERATOR  0x0104u
#define NEOMESH868MHZ_SAPI_CMD_GET_LIST             0x0105u
#define NEOMESH868MHZ_SAPI_CMD_GET_SETTING_FLASH    0x0106u
#define NEOMESH868MHZ_SAPI_CMD_GET_SETTING_RAM      0x0107u
#define NEOMESH868MHZ_SAPI_CMD_COMMIT_SETTINGS      0x0108u
#define NEOMESH868MHZ_SAPI_CMD_DISCARD_SETTINGS     0x0109u
#define NEOMESH868MHZ_SAPI_CMD_SET_SETTING          0x010Au
#define NEOMESH868MHZ_SAPI_CMD_START_PROTOCOL_STACK 0x0112u
#define NEOMESH868MHZ_SAPI_CMD_START_BOOTLOADER     0x0113u
#define NEOMESH868MHZ_SAPI_HEADER                   0x3E
#define NEOMESH868MHZ_SAPI_TRAIL                    0x21

/**
 * @brief NeoMesh 868MHz system data response.
 * @details Specified setting for system data response of NeoMesh 868MHz Click driver.
 */
#define NEOMESH868MHZ_SAPI_RSP_OK                   0x0380u
#define NEOMESH868MHZ_SAPI_RSP_ERROR                0x0381u
#define NEOMESH868MHZ_SAPI_RSP_BOOTLOADER_START     0x0382u
#define NEOMESH868MHZ_SAPI_RSP_PROTOCOL_STACK_START 0x0383u
#define NEOMESH868MHZ_SAPI_RSP_PROTOCOL_STACK_ERROR 0x0384u
#define NEOMESH868MHZ_SAPI_RSP_RESET                0x0385u
#define NEOMESH868MHZ_SAPI_RSP_SETTINGS_LIST_OUTPUT 0x0185u
#define NEOMESH868MHZ_SAPI_RSP_SETTINGS_VALUE       0x0186u

/**
 * @brief NeoMesh 868MHz login password settings.
 * @details Specified setting for login password of NeoMesh 868MHz Click driver.
 */
#define NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_0         0x4C
#define NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_1         0x76
#define NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_2         0x6C
#define NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_3         0x31
#define NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_4         0x30

/**
 * @brief NeoMesh 868MHz SAPI settings ID.
 * @details Specified setting for SAPI settings ID of NeoMesh 868MHz Click driver.
 */
#define NEOMESH868MHZ_SAPI_SETTINGS_ID_NODE_ID      0x0A

/**
 * @brief NeoMesh 868MHz CTS/WUP timeout wait.
 * @details Specified setting for CTS/WUP timeout wait of NeoMesh 868MHz Click driver.
 */
#define NEOMESH868MHZ_TIMEOUT_MS                    20000ul

/**
 * @brief NeoMesh 868MHz payload length.
 * @details Specified setting for payload length of NeoMesh 868MHz Click driver.
 */
#define NEOMESH868MHZ_MAX_PAYLOAD_LEN               255

/**
 * @brief NeoMesh 868MHz driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NEOMESH868MHZ_TX_DRV_BUFFER_SIZE            300u
#define NEOMESH868MHZ_RX_DRV_BUFFER_SIZE            300u

/*! @} */ // neomesh868mhz_cmd

/**
 * @defgroup neomesh868mhz_map NeoMesh 868MHz MikroBUS Map
 * @brief MikroBUS pin mapping of NeoMesh 868MHz Click driver.
 */

/**
 * @addtogroup neomesh868mhz_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NeoMesh 868MHz Click to the selected MikroBUS.
 */
#define NEOMESH868MHZ_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.app = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wes = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // neomesh868mhz_map
/*! @} */ // neomesh868mhz

/**
 * @brief NeoMesh 868MHz Click context object.
 * @details Context object definition of NeoMesh 868MHz Click driver.
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
    uint8_t uart_rx_buffer[ NEOMESH868MHZ_RX_DRV_BUFFER_SIZE ]; /**< Buffer size. */
    uint8_t uart_tx_buffer[ NEOMESH868MHZ_TX_DRV_BUFFER_SIZE ]; /**< Buffer size. */

} neomesh868mhz_t;

/**
 * @brief NeoMesh 868MHz Click configuration object.
 * @details Configuration object definition of NeoMesh 868MHz Click driver.
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

} neomesh868mhz_cfg_t;

/**
 * @brief NeoMesh 868MHz Click data frame object.
 * @details AAPI data frame object definition of NeoMesh 868MHz Click driver.
 */
typedef struct
{
    uint8_t cmd;                                        /**< Command byte. */
    uint8_t len;                                        /**< Payload length. */
    uint8_t payload[ NEOMESH868MHZ_MAX_PAYLOAD_LEN ];   /**< Payload bytes. */

} neomesh868mhz_aapi_frame_t;

/**
 * @brief NeoMesh 868MHz Click data frame object.
 * @details SAPI data frame object definition of NeoMesh 868MHz Click driver.
 */
typedef struct
{
    uint16_t cmd;                                       /**< Command word. */
    uint8_t len;                                        /**< Payload length. */
    uint8_t payload[ NEOMESH868MHZ_MAX_PAYLOAD_LEN ];   /**< Payload bytes. */

} neomesh868mhz_sapi_frame_t;

/**
 * @brief NeoMesh 868MHz Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NEOMESH868MHZ_OK = 0,
    NEOMESH868MHZ_ERROR = -1,
    NEOMESH868MHZ_TIMEOUT = -2

} neomesh868mhz_return_value_t;

/*!
 * @addtogroup neomesh868mhz NeoMesh 868MHz Click Driver
 * @brief API for configuring and manipulating NeoMesh 868MHz Click driver.
 * @{
 */

/**
 * @brief NeoMesh 868MHz configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #neomesh868mhz_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void neomesh868mhz_cfg_setup ( neomesh868mhz_cfg_t *cfg );

/**
 * @brief NeoMesh 868MHz initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #neomesh868mhz_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh868mhz_init ( neomesh868mhz_t *ctx, neomesh868mhz_cfg_t *cfg );

/**
 * @brief NeoMesh 868MHz send aapi frame function.
 * @details This function sends a desired AAPI frame by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @param[in] frame : AAPI frame structure to be sent.
 * See #neomesh868mhz_aapi_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh868mhz_send_aapi_frame ( neomesh868mhz_t *ctx, neomesh868mhz_aapi_frame_t *frame );

/**
 * @brief NeoMesh 868MHz read aapi frame function.
 * @details This function reads an AAPI frame by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @param[out] frame : AAPI frame structure read.
 * See #neomesh868mhz_aapi_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error, frame is not read correctly,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh868mhz_read_aapi_frame ( neomesh868mhz_t *ctx, neomesh868mhz_aapi_frame_t *frame );

/**
 * @brief NeoMesh 868MHz send sapi frame function.
 * @details This function sends a desired SAPI frame by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @param[in] frame : SAPI frame structure to be sent.
 * See #neomesh868mhz_sapi_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh868mhz_send_sapi_frame ( neomesh868mhz_t *ctx, neomesh868mhz_sapi_frame_t *frame );

/**
 * @brief NeoMesh 868MHz read sapi frame function.
 * @details This function reads an SAPI frame by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @param[out] frame : SAPI frame structure read.
 * See #neomesh868mhz_sapi_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error, frame is not read correctly,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t neomesh868mhz_read_sapi_frame ( neomesh868mhz_t *ctx, neomesh868mhz_sapi_frame_t *frame );

/**
 * @brief NeoMesh 868MHz set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void neomesh868mhz_set_rst_pin ( neomesh868mhz_t *ctx, uint8_t state );

/**
 * @brief NeoMesh 868MHz set wes pin function.
 * @details This function sets the WES pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void neomesh868mhz_set_wes_pin ( neomesh868mhz_t *ctx, uint8_t state );

/**
 * @brief NeoMesh 868MHz get app pin function.
 * @details This function returns the APP pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t neomesh868mhz_get_app_pin ( neomesh868mhz_t *ctx );

/**
 * @brief NeoMesh 868MHz get cts pin function.
 * @details This function returns the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t neomesh868mhz_get_cts_pin ( neomesh868mhz_t *ctx );

/**
 * @brief NeoMesh 868MHz get wup pin function.
 * @details This function returns the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #neomesh868mhz_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t neomesh868mhz_get_wup_pin ( neomesh868mhz_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NEOMESH868MHZ_H

/*! @} */ // neomesh868mhz

// ------------------------------------------------------------------------ END
