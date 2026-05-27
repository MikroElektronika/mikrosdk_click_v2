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
 * @file st67w.h
 * @brief This file contains API for ST67W Click Driver.
 */

#ifndef ST67W_H
#define ST67W_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup st67w ST67W Click Driver
 * @brief API for configuring and manipulating ST67W Click driver.
 * @{
 */

/**
 * @defgroup st67w_cmd ST67W Device Settings
 * @brief Settings for registers of ST67W Click driver.
 */

/**
 * @addtogroup st67w_cmd
 * @{
 */

/**
 * @brief ST67W control commands.
 * @details Specified setting for control commands of ST67W Click driver.
 */
#define ST67W_CMD_AT                            "AT"
#define ST67W_CMD_GET_VERSION                   "AT+GMR"
#define ST67W_CMD_FACTORY_RESET                 "AT+RESTORE"
#define ST67W_CMD_SET_WIFI_MODE                 "AT+CWMODE"
#define ST67W_CMD_CONNECT_TO_AP                 "AT+CWJAP"
#define ST67W_CMD_SET_MULTIPLE_CONNECTION_MODE  "AT+CIPMUX"
#define ST67W_CMD_SET_SOCKET_RECEIVING_MODE     "AT+CIPRECVMODE"
#define ST67W_CMD_ESTABLISH_TCP_UDP_CONNECTION  "AT+CIPSTART"
#define ST67W_CMD_SEND_DATA_VIA_CONNECTION      "AT+CIPSEND"
#define ST67W_CMD_RECEIVE_DATA_VIA_CONNECTION   "AT+CIPRECVDATA"
#define ST67W_CMD_CLOSE_TCP_UDP_CONNECTION      "AT+CIPCLOSE"
#define ST67W_CMD_BLE_INIT                      "AT+BLEINIT"
#define ST67W_CMD_BLE_ADDRESS                   "AT+BLEADDR"
#define ST67W_CMD_BLE_NAME                      "AT+BLENAME"
#define ST67W_CMD_BLE_CONNECT                   "AT+BLECONN"
#define ST67W_CMD_BLE_DISCONNECT                "AT+BLEDISCONN"
#define ST67W_CMD_BLE_SET_ADVERTISING_DATA      "AT+BLEADVDATA"
#define ST67W_CMD_BLE_START_ADVERTISING         "AT+BLEADVSTART"
#define ST67W_CMD_BLE_GATTS_SERVICE_CREATE      "AT+BLEGATTSSRVCRE"
#define ST67W_CMD_BLE_GATTS_CHAR_CREATE         "AT+BLEGATTSCHARCRE"
#define ST67W_CMD_BLE_GATTS_NOTIFY              "AT+BLEGATTSNTFY"

/**
 * @brief ST67W device response for AT commands.
 * @details Device response after commands.
 */
#define ST67W_RSP_OK                            "OK\r\n"
#define ST67W_RSP_ERROR                         "ERROR\r\n"
#define ST67W_RSP_SEND_OK                       "SEND OK\r\n"
#define ST67W_RSP_SEND_FAIL                     "SEND FAIL\r\n"

/**
 * @brief ST67W device response time for AT commands.
 * @details Device response time after commands.
 */
#define ST67W_MAX_RSP_TIME_DEFAULT              5000ul
#define ST67W_MAX_RSP_TIME_READY                10000ul
#define ST67W_MAX_RSP_TIME_FACTORY_RESET        90000ul
#define ST67W_MAX_RSP_TIME_TCP_CONNECT          30000ul
#define ST67W_MAX_RSP_TIME_WIFI_CONNECT         30000ul
#define ST67W_MAX_RSP_TIME_BLE_CONNECT          180000ul

/**
 * @brief ST67W SPI frame header settings.
 * @details Device SPI frame header settings.
 */
#define ST67W_SPI_SYNC_0                        0xAA
#define ST67W_SPI_SYNC_1                        0x55
#define ST67W_SPI_FRAME_BYTE                    0x00
#define ST67W_SPI_TYPE_BYTE                     0x00
#define ST67W_SPI_RESERVED_BYTE                 0x00
#define ST67W_SPI_PADDING_BYTE                  0x88

/**
 * @brief ST67W device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define ST67W_URC_READY                         "ready"
#define ST67W_URC_RECEIVED_DATA                 "+IPD"
#define ST67W_URC_WIFI_CONNECTED                "+CW:GOTIP"
#define ST67W_URC_BLE_CONNECTED                 "+BLE:CONNECTED:"
#define ST67W_URC_BLE_DISCONNECTED              "+BLE:DISCONNECTED:"

/**
 * @brief ST67W device SPI ready timeout settings.
 * @details Device SPI ready timeout settings.
 */
#define ST67W_SPI_READY_TIMEOUT_MS              5000

/**
 * @brief ST67W device maximum data buffer size settings.
 * @details Device maximum data buffer size settings.
 */
#define ST67W_DATA_BUFFER_SIZE                  256

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b st67w_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ST67W_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define ST67W_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // st67w_set

/**
 * @defgroup st67w_map ST67W MikroBUS Map
 * @brief MikroBUS pin mapping of ST67W Click driver.
 */

/**
 * @addtogroup st67w_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ST67W Click to the selected MikroBUS.
 */
#define ST67W_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.boot = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // st67w_map
/*! @} */ // st67w

/**
 * @brief ST67W Click context object.
 * @details Context object definition of ST67W Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t boot;         /**< Boot mode pin (high - UART mode (FW update), low - FLASH mode (SPI AT)). */
    digital_out_t en;           /**< Chip enable pin (active high). */

    // Input pins
    digital_in_t rdy;           /**< SPI ready interrupt (active high). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t cmd_buffer[ ST67W_DATA_BUFFER_SIZE ];   /**< Command buffer. */

} st67w_t;

/**
 * @brief ST67W Click configuration object.
 * @details Configuration object definition of ST67W Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t boot;            /**< Boot mode pin (high - UART mode (FW update), low - FLASH mode (SPI AT)). */
    pin_name_t en;              /**< Chip enable pin (active high). */
    pin_name_t rdy;             /**< SPI ready interrupt (active high). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} st67w_cfg_t;

/**
 * @brief ST67W Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ST67W_OK = 0,
    ST67W_ERROR = -1,
    ST67W_ERROR_TIMEOUT = -2,
    ST67W_ERROR_CMD = -3

} st67w_return_value_t;

/*!
 * @addtogroup st67w ST67W Click Driver
 * @brief API for configuring and manipulating ST67W Click driver.
 * @{
 */

/**
 * @brief ST67W configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #st67w_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void st67w_cfg_setup ( st67w_cfg_t *cfg );

/**
 * @brief ST67W initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #st67w_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t st67w_init ( st67w_t *ctx, st67w_cfg_t *cfg );

/**
 * @brief ST67W data writing function.
 * @details This function writes a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t st67w_generic_write ( st67w_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ST67W data reading function.
 * @details This function reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t st67w_generic_read ( st67w_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ST67W set boot pin function.
 * @details This function sets the BOOT pin logic state.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void st67w_set_boot_pin ( st67w_t *ctx, uint8_t state );

/**
 * @brief ST67W enable device function.
 * @details This function enables the device by setting the EN pin to high state.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void st67w_enable_device ( st67w_t *ctx );

/**
 * @brief ST67W disable device function.
 * @details This function disables the device by clearing the EN pin to low state.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void st67w_disable_device ( st67w_t *ctx );

/**
 * @brief ST67W reset device function.
 * @details This function resets the device by toggling the EN pin state.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void st67w_reset_device ( st67w_t *ctx );

/**
 * @brief ST67W get rdy pin function.
 * @details This function returns the SPI ready (RDY) pin logic state.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t st67w_get_rdy_pin ( st67w_t *ctx );

/**
 * @brief ST67W cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void st67w_cmd_run ( st67w_t *ctx, uint8_t *cmd );

/**
 * @brief ST67W cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void st67w_cmd_set ( st67w_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief ST67W cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void st67w_cmd_get ( st67w_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // ST67W_H

/*! @} */ // st67w

// ------------------------------------------------------------------------ END
