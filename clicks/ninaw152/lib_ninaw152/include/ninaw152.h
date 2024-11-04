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
 * @file ninaw152.h
 * @brief This file contains API for NINA-W152 Click Driver.
 */

#ifndef NINAW152_H
#define NINAW152_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup ninaw152 NINA-W152 Click Driver
 * @brief API for configuring and manipulating NINA-W152 Click driver.
 * @{
 */

/**
 * @defgroup ninaw152_cmd NINA-W152 Device Settings
 * @brief Settings for registers of NINA-W152 Click driver.
 */

/**
 * @addtogroup ninaw152_cmd
 * @{
 */

/**
 * @brief NINA-W152 control commands.
 * @details Specified setting for control commands of NINA-W152 Click driver.
 */
#define NINAW152_CMD_AT                         "AT"
#define NINAW152_CMD_GET_MODEL_ID               "AT+GMM"
#define NINAW152_CMD_GET_SW_VERSION             "AT+GMR"
#define NINAW152_CMD_GET_SERIAL_NUM             "AT+GSN"
#define NINAW152_CMD_FACTORY_RESET              "AT+UFACTORY"
#define NINAW152_CMD_REBOOT_DEVICE              "AT+CPWROFF"
#define NINAW152_CMD_NETWORK_HOST_NAME          "AT+UNHN"
#define NINAW152_CMD_BT_LOCAL_NAME              "AT+UBTLN"
#define NINAW152_CMD_WIFI_STATION_CONFIG        "AT+UWSC"
#define NINAW152_CMD_WIFI_STATION_CONFIG_ACTION "AT+UWSCA"
#define NINAW152_CMD_WIFI_STATION_STATUS        "AT+UWSSTAT"
#define NINAW152_CMD_CONNECT_PEER               "AT+UDCP"
#define NINAW152_CMD_WRITE_DATA                 "AT+UDATW"
#define NINAW152_CMD_READ_DATA                  "AT+UDATR"
#define NINAW152_CMD_CLOSE_PEER                 "AT+UDCPC"
#define NINAW152_CMD_ENTER_DATA_MODE            "ATO1"
#define NINAW152_CMD_ENTER_CMD_MODE             "+++"

/**
 * @brief NINA-W152 device response to AT commands.
 * @details Device response to commands.
 */
#define NINAW152_RSP_OK                         "OK"
#define NINAW152_RSP_ERROR                      "ERROR"

/**
 * @brief NINA-W152 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define NINAW152_URC_GREETING                   "+STARTUP"
#define NINAW152_URC_WIFI_LINK_CONNECTED        "+UUWLE:"
#define NINAW152_URC_NETWORK_UP                 "+UUNU:"
#define NINAW152_URC_PEER_CONNECTED             "+UUDPC:"
#define NINAW152_URC_PEER_DISCONNECTED          "+UUDPD:"
#define NINAW152_URC_READ_SOCKET_DATA           "+UUDATA:"

/**
 * @brief NINA-W152 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NINAW152_TX_DRV_BUFFER_SIZE             200
#define NINAW152_RX_DRV_BUFFER_SIZE             600

/**
 * @brief NINA-W152 SPI packet settings.
 * @details Specified settings of SPI packet.
 */
#define NINAW152_SPI_HEADER_0                   0xBA
#define NINAW152_SPI_HEADER_1                   0x15
#define NINAW152_SPI_NORX                       0x80

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ninaw152_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define NINAW152_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define NINAW152_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ninaw152_cmd

/**
 * @defgroup ninaw152_map NINA-W152 MikroBUS Map
 * @brief MikroBUS pin mapping of NINA-W152 Click driver.
 */

/**
 * @addtogroup ninaw152_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NINA-W152 Click to the selected MikroBUS.
 */
#define NINAW152_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sry = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.esc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ninaw152_map
/*! @} */ // ninaw152

/**
 * @brief NINA-W152 Click driver selector.
 * @details Selects target driver interface of NINA-W152 Click driver.
 */
typedef enum
{
    NINAW152_DRV_SEL_UART,  /**< UART driver descriptor. */
    NINAW152_DRV_SEL_SPI    /**< SPI driver descriptor. */

} ninaw152_drv_t;

/**
 * @brief NINA-W152 Click context object.
 * @details Context object definition of NINA-W152 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin (active low). */
    digital_out_t cts;      /**< UART clear to send pin (active low). */
    digital_out_t esc;      /**< UART DSR or escape from data mode pin. */

    // Input pins
    digital_in_t sry;       /**< SPI data ready signal. */
    digital_in_t rts;       /**< UART request to send pin (active low). */

    // Modules
    uart_t uart;            /**< UART driver object. */
    spi_master_t spi;       /**< SPI driver object. */
    
    uint8_t uart_rx_buffer[ NINAW152_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ NINAW152_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    ninaw152_drv_t drv_sel;         /**< Master driver interface selector. */

} ninaw152_t;

/**
 * @brief NINA-W152 Click configuration object.
 * @details Configuration object definition of NINA-W152 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;        /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;        /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;         /**< Clock pin descriptor for SPI driver. */
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t sry;         /**< SPI data ready signal. */
    pin_name_t rst;         /**< Reset pin (active low). */
    pin_name_t cts;         /**< UART clear to send pin (active low). */
    pin_name_t esc;         /**< UART DSR or escape from data mode pin. */
    pin_name_t rts;         /**< UART request to send pin (active low). */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    ninaw152_drv_t drv_sel; /**< Master driver interface selector. */

} ninaw152_cfg_t;

/**
 * @brief NINA-W152 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NINAW152_OK = 0,
    NINAW152_ERROR = -1,
    NINAW152_ERROR_TIMEOUT = -2,
    NINAW152_ERROR_CMD = -3,
    NINAW152_ERROR_UNKNOWN = -4

} ninaw152_return_value_t;

/*!
 * @addtogroup ninaw152 NINA-W152 Click Driver
 * @brief API for configuring and manipulating NINA-W152 Click driver.
 * @{
 */

/**
 * @brief NINA-W152 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ninaw152_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ninaw152_cfg_setup ( ninaw152_cfg_t *cfg );

/**
 * @brief NINA-W152 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ninaw152_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninaw152_init ( ninaw152_t *ctx, ninaw152_cfg_t *cfg );

/**
 * @brief NINA-W152 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ninaw152_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ninaw152_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ninaw152_drv_interface_sel ( ninaw152_cfg_t *cfg, ninaw152_drv_t drv_sel );

/**
 * @brief NINA-W152 data writing function.
 * @details This function writes a desired number of data bytes by using UART or SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninaw152_generic_write ( ninaw152_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NINA-W152 data reading function.
 * @details This function reads a desired number of data bytes by using UART or SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninaw152_generic_read ( ninaw152_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NINA-W152 set rst pin function.
 * @details This function sets the reset (RST) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ninaw152_set_rst_pin ( ninaw152_t *ctx, uint8_t state );

/**
 * @brief NINA-W152 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ninaw152_reset_device ( ninaw152_t *ctx );

/**
 * @brief NINA-W152 set cts pin function.
 * @details This function sets the UART clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ninaw152_set_cts_pin ( ninaw152_t *ctx, uint8_t state );

/**
 * @brief NINA-W152 set esc pin function.
 * @details This function sets the UART DSR or escape from data mode (ESC) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ninaw152_set_esc_pin ( ninaw152_t *ctx, uint8_t state );

/**
 * @brief NINA-W152 get rts pin function.
 * @details This function returns the UART request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ninaw152_get_rts_pin ( ninaw152_t *ctx );

/**
 * @brief NINA-W152 get sry pin function.
 * @details This function returns the SPI data ready signal (SRY) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ninaw152_get_sry_pin ( ninaw152_t *ctx );

/**
 * @brief NINA-W152 send command function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ninaw152_send_cmd ( ninaw152_t *ctx, uint8_t *cmd );

/**
 * @brief NINA-W152 send command with parameter function.
 * @details This function sends a command with specified parameter to the Click module.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return None.
 * @note None.
 */
void ninaw152_send_cmd_with_par ( ninaw152_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief NINA-W152 send command check function.
 * @details This function sends a desired command with appended checkmark.
 * @param[in] ctx : Click context object.
 * See #ninaw152_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return None.
 * @note None.
 */
void ninaw152_send_cmd_check ( ninaw152_t *ctx, uint8_t *at_cmd_buf );

#ifdef __cplusplus
}
#endif
#endif // NINAW152_H

/*! @} */ // ninaw152

// ------------------------------------------------------------------------ END
