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
 * @file fingerprint5.h
 * @brief This file contains API for Fingerprint 5 Click Driver.
 */

#ifndef FINGERPRINT5_H
#define FINGERPRINT5_H

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
 * @addtogroup fingerprint5 Fingerprint 5 Click Driver
 * @brief API for configuring and manipulating Fingerprint 5 Click driver.
 * @{
 */

/**
 * @defgroup fingerprint5_cmd Fingerprint 5 Device Settings
 * @brief Settings for registers of Fingerprint 5 Click driver.
 */

/**
 * @addtogroup fingerprint5_cmd
 * @{
 */

/**
 * @brief Fingerprint 5 command IDs list.
 * @details Specified setting for command IDs list of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_CMD_STATUS                             0x0040
#define FINGERPRINT5_CMD_VERSION                            0x0041
#define FINGERPRINT5_CMD_BIST                               0x0044
#define FINGERPRINT5_CMD_CAPTURE                            0x0050
#define FINGERPRINT5_CMD_ABORT                              0x0052
#define FINGERPRINT5_CMD_IMAGE_DATA                         0x0053
#define FINGERPRINT5_CMD_ENROLL                             0x0054
#define FINGERPRINT5_CMD_IDENTIFY                           0x0055
#define FINGERPRINT5_CMD_LIST_TEMPLATES                     0x0060
#define FINGERPRINT5_CMD_DELETE_TEMPLATE                    0x0061
#define FINGERPRINT5_CMD_GET_SYSTEM_CONFIG                  0x006A
#define FINGERPRINT5_CMD_SET_SYSTEM_CONFIG                  0x006B
#define FINGERPRINT5_CMD_RESET                              0x0072
#define FINGERPRINT5_CMD_SET_DBG_LOG_LEVEL                  0x00B0
#define FINGERPRINT5_CMD_DATA_GET                           0x0101
#define FINGERPRINT5_CMD_NAVIGATION                         0x0200
#define FINGERPRINT5_CMD_GPIO_CONTROL                       0x0300

/**
 * @brief Fingerprint 5 frame settings.
 * @details Specified setting for frame type of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_FRAME_PROTOCOL_VERSION                 0x0004
#define FINGERPRINT5_FRAME_TYPE_REQUEST                     0x11
#define FINGERPRINT5_FRAME_TYPE_RESPONSE                    0x12
#define FINGERPRINT5_FRAME_TYPE_EVENT                       0x13
#define FINGERPRINT5_FRAME_FLAG_HOST                        0x0010
#define FINGERPRINT5_FRAME_FLAG_FW_BL                       0x0020
#define FINGERPRINT5_FRAME_FLAG_FW_APP                      0x0040
#define FINGERPRINT5_FRAME_CMD_MAX_DATA_SIZE                244
#define FINGERPRINT5_FRAME_MAX_SIZE                         256

/**
 * @brief Fingerprint 5 buffers settings.
 * @details Specified setting for buffers of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_MAX_VERSION_SIZE                       100
#define FINGERPRINT5_MAX_NUM_TEMPLATES                      12

/**
 * @brief Fingerprint 5 event settings.
 * @details Specified setting for event of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_EVENT_NONE                             0
#define FINGERPRINT5_EVENT_IDLE                             1
#define FINGERPRINT5_EVENT_ARMED                            2
#define FINGERPRINT5_EVENT_FINGER_DETECT                    3
#define FINGERPRINT5_EVENT_FINGER_LOST                      4
#define FINGERPRINT5_EVENT_IMAGE_READY                      5
#define FINGERPRINT5_EVENT_CMD_FAILED                       6

/**
 * @brief Fingerprint 5 stete settings.
 * @details Specified setting for stete of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_STATE_APP_FW_READY                     0x0001
#define FINGERPRINT5_STATE_CAPTURE                          0x0004
#define FINGERPRINT5_STATE_IMAGE_AVAILABLE                  0x0010
#define FINGERPRINT5_STATE_DATA_TRANSFER                    0x0040
#define FINGERPRINT5_STATE_FINGER_DOWN                      0x0080
#define FINGERPRINT5_STATE_SYS_ERROR                        0x0400
#define FINGERPRINT5_STATE_ENROLL                           0x1000
#define FINGERPRINT5_STATE_IDENTIFY                         0x2000
#define FINGERPRINT5_STATE_NAVIGATION                       0x4000

/**
 * @brief Fingerprint 5 template ID type settings.
 * @details Specified setting for template ID type of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_TEMPLATE_ID_TYPE_NONE                  0x1012
#define FINGERPRINT5_TEMPLATE_ID_TYPE_ALL                   0x2023
#define FINGERPRINT5_TEMPLATE_ID_TYPE_SPECIFIED             0x3034
#define FINGERPRINT5_TEMPLATE_ID_TYPE_NEW                   0x4045

/**
 * @brief Fingerprint 5 enroll feedback settings.
 * @details Specified setting for enroll feedback of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_ENROLL_FEEDBACK_DONE                   1
#define FINGERPRINT5_ENROLL_FEEDBACK_PROGRESS               2
#define FINGERPRINT5_ENROLL_FEEDBACK_REJECT_LOW_QUALITY     3
#define FINGERPRINT5_ENROLL_FEEDBACK_REJECT_LOW_COVERAGE    4
#define FINGERPRINT5_ENROLL_FEEDBACK_REJECT_LOW_MOBILITY    5
#define FINGERPRINT5_ENROLL_FEEDBACK_REJECT_OTHER           6
#define FINGERPRINT5_ENROLL_FEEDBACK_PROGRESS_IMMOBILE      7

/**
 * @brief Fingerprint 5 identify match settings.
 * @details Specified setting for identify match of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_IDENTIFY_RESULT_MATCH                  0x61EC
#define FINGERPRINT5_IDENTIFY_RESULT_NO_MATCH               0xBAAD

/**
 * @brief Fingerprint 5 navigation orientation settings.
 * @details Specified setting for navigation orientation of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_NAV_ORIENTATION_0                      0
#define FINGERPRINT5_NAV_ORIENTATION_90                     1
#define FINGERPRINT5_NAV_ORIENTATION_180                    2
#define FINGERPRINT5_NAV_ORIENTATION_270                    3

/**
 * @brief Fingerprint 5 GPIO control settings.
 * @details Specified setting for GPIO control of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_GPIO_SUB_CMD_GET                       0
#define FINGERPRINT5_GPIO_SUB_CMD_SET                       1
#define FINGERPRINT5_GPIO_MODE_NOT_USED                     0
#define FINGERPRINT5_GPIO_MODE_OUTPUT_PP                    1
#define FINGERPRINT5_GPIO_MODE_OUTPUT_OD                    2
#define FINGERPRINT5_GPIO_MODE_INPUT_PULL_NONE              3
#define FINGERPRINT5_GPIO_MODE_INPUT_PULL_UP                4
#define FINGERPRINT5_GPIO_MODE_INPUT_PULL_DOWN              5
#define FINGERPRINT5_GPIO_STATE_RESET                       0
#define FINGERPRINT5_GPIO_STATE_SET                         1

/**
 * @brief Fingerprint 5 system config settings.
 * @details Specified setting for system config of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_SYS_CFG_VERSION                        1
#define FINGERPRINT5_SYS_CFG_FLAG_STATUS_EVT_BOOT           0x00000001
#define FINGERPRINT5_SYS_CFG_FLAG_UART_IN_STOP_MODE         0x00000010
#define FINGERPRINT5_SYS_CFG_FLAG_UART_IRQ_TX               0x00000020
#define FINGERPRINT5_SYS_CFG_UART_BAUDRATE_9600             1
#define FINGERPRINT5_SYS_CFG_UART_BAUDRATE_19200            2
#define FINGERPRINT5_SYS_CFG_UART_BAUDRATE_57600            3
#define FINGERPRINT5_SYS_CFG_UART_BAUDRATE_115200           4
#define FINGERPRINT5_SYS_CFG_UART_BAUDRATE_921600           5
#define FINGERPRINT5_SYS_CFG_TYPE_DEFAULT                   0
#define FINGERPRINT5_SYS_CFG_TYPE_CUSTOM                    1

/**
 * @brief Fingerprint 5 timeout setting.
 * @details Specified setting for timeout of Fingerprint 5 Click driver.
 */
#define FINGERPRINT5_RX_TIMEOUT_MS                          3000

/**
 * @brief Fingerprint 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define FINGERPRINT5_TX_DRV_BUFFER_SIZE                     256
#define FINGERPRINT5_RX_DRV_BUFFER_SIZE                     256

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b fingerprint5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FINGERPRINT5_SET_DATA_SAMPLE_EDGE                   SET_SPI_DATA_SAMPLE_EDGE
#define FINGERPRINT5_SET_DATA_SAMPLE_MIDDLE                 SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // fingerprint5_cmd

/**
 * @defgroup fingerprint5_map Fingerprint 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Fingerprint 5 Click driver.
 */

/**
 * @addtogroup fingerprint5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Fingerprint 5 Click to the selected MikroBUS.
 */
#define FINGERPRINT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // fingerprint5_map
/*! @} */ // fingerprint5

/**
 * @brief Fingerprint 5 Click driver selector.
 * @details Selects target driver interface of Fingerprint 5 Click driver.
 */
typedef enum
{
    FINGERPRINT5_DRV_SEL_UART,      /**< UART driver descriptor. */
    FINGERPRINT5_DRV_SEL_SPI        /**< SPI driver descriptor. */

} fingerprint5_drv_t;

/**
 * @brief Fingerprint 5 Click command header object.
 * @details Command header object definition of Fingerprint 5 Click driver.
 */
typedef struct 
{
    uint16_t cmd_id;                /** Command ID. */
    uint8_t payload[ FINGERPRINT5_FRAME_CMD_MAX_DATA_SIZE ]; /** Command data payload. */
    uint16_t payload_len;           /** Size of command payload. */

} fingerprint5_cmd_t;

/**
 * @brief Fingerprint 5 Click status object.
 * @details Status object definition of Fingerprint 5 Click driver.
 */
typedef struct 
{
    uint16_t evt;                   /** Event code. */
    uint16_t state;                 /** The current state code. */
    uint16_t app_fail;              /** Additional details of failure. */

} fingerprint5_status_t;

/**
 * @brief Fingerprint 5 Click version object.
 * @details Version object definition of Fingerprint 5 Click driver.
 */
typedef struct 
{
    uint32_t unique_id[ 3 ];        /** 96 bits of unique ID. */
    uint8_t fw_id;                  /** FW ID code. */
    uint8_t fw_fuse_lvl;            /** Fuse level. */
    uint16_t ver_str_len;           /** Version string length. */
    uint8_t ver_str[ FINGERPRINT5_MAX_VERSION_SIZE ];   /** Version string. */

} fingerprint5_version_t;

/**
 * @brief Fingerprint 5 Click list templates object.
 * @details List templates object definition of Fingerprint 5 Click driver.
 */
typedef struct 
{
    uint16_t num_templates;         /** Number of enrolled templates. */
    uint16_t template_ids[ FINGERPRINT5_MAX_NUM_TEMPLATES ]; /** List of enrolled template IDs. */

} fingerprint5_list_templates_t;

/**
 * @brief Fingerprint 5 Click enroll status object.
 * @details Enroll status object definition of Fingerprint 5 Click driver.
 */
typedef struct 
{
    uint16_t id;                    /** Template ID of the ongoing enrollment. */
    uint8_t feedback;               /** Enroll feedback code. */
    uint8_t samples_remaining;      /** Counter with the remaining touches for the current enrollment. */

} fingerprint5_enroll_t;

/**
 * @brief Fingerprint 5 Click identify status object.
 * @details Identify status object definition of Fingerprint 5 Click driver.
 */
typedef struct 
{
    uint16_t match;                 /** Match result. */
    uint16_t type;                  /** Type of Specifier. */
    uint16_t id;                    /** Template ID. */
    uint16_t tag;                   /** Operation tag. The tag that was entered via the request. */

} fingerprint5_identify_t;

/**
 * @brief Fingerprint 5 Click system config object.
 * @details System config object definition of Fingerprint 5 Click driver.
 */
typedef struct 
{
    uint16_t version;               /** Config Version. */
    uint16_t finger_scan_int_ms;    /** Nominal sleep time between finger present queries [ms], Range [0, 1020]. */
    uint32_t sys_flags;             /** Combination of SYS_CFG_FLAG. */
    uint8_t uart_irq_delay_ms;      /** Delay between the IRQ pin is set and UART TX is started. */
    uint8_t uart_baudrate;          /** One of SYS_CFG_UART_BAUDRATE */
    uint8_t idfy_max_cons_fails;    /** Max number of failed Identify before lockout. */
    uint8_t idfy_lockout_time_s;    /** Identify lockout time, after too many fails. */
    uint16_t idle_time_ms;          /** Idle time after last command, before entering stop mode [ms]. */

} fingerprint5_sys_config_t;

/**
 * @brief Fingerprint 5 Click context object.
 * @details Context object definition of Fingerprint 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< System reset pin (active low). */

    // Input pins
    digital_in_t irq;               /**< Interrupt request pin (active high). */

    // Modules
    uart_t uart;                    /**< UART driver object. */
    spi_master_t spi;               /**< SPI driver object. */
    
    uint8_t uart_rx_buffer[ FINGERPRINT5_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer. */
    uint8_t uart_tx_buffer[ FINGERPRINT5_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    fingerprint5_drv_t drv_sel;     /**< Master driver interface selector. */

    fingerprint5_cmd_t cmd;         /**< Request/Response/Event command header object. */
    uint8_t frame[ FINGERPRINT5_FRAME_MAX_SIZE ];   /**< Frame Buffer. */

} fingerprint5_t;

/**
 * @brief Fingerprint 5 Click configuration object.
 * @details Configuration object definition of Fingerprint 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< System reset pin (active low). */
    pin_name_t irq;                 /**< Interrupt request pin (active high). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    fingerprint5_drv_t drv_sel;     /**< Master driver interface selector. */

} fingerprint5_cfg_t;

/**
 * @brief Fingerprint 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FINGERPRINT5_OK = 0,
    FINGERPRINT5_ERROR = -1,
    FINGERPRINT5_ERROR_TIMEOUT = -2

} fingerprint5_return_value_t;

/*!
 * @addtogroup fingerprint5 Fingerprint 5 Click Driver
 * @brief API for configuring and manipulating Fingerprint 5 Click driver.
 * @{
 */

/**
 * @brief Fingerprint 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #fingerprint5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void fingerprint5_cfg_setup ( fingerprint5_cfg_t *cfg );

/**
 * @brief Fingerprint 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #fingerprint5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fingerprint5_init ( fingerprint5_t *ctx, fingerprint5_cfg_t *cfg );

/**
 * @brief Fingerprint 5 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #fingerprint5_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #fingerprint5_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void fingerprint5_drv_interface_sel ( fingerprint5_cfg_t *cfg, fingerprint5_drv_t drv_sel );

/**
 * @brief Fingerprint 5 write data function.
 * @details This function writes a desired number of data bytes to the selected interface.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_generic_write ( fingerprint5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Fingerprint 5 read data function.
 * @details This function reads a desired number of data bytes from the selected interface.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout error.
 * @note None.
 */
err_t fingerprint5_generic_read ( fingerprint5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Fingerprint 5 set RST pin function.
 * @details This function sets the RST (reset) pin logic state.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[in] state : Pin state (0 or 1).
 * @return None.
 * @note None.
 */
void fingerprint5_set_rst_pin ( fingerprint5_t *ctx, uint8_t state );

/**
 * @brief Fingerprint 5 hardware reset function.
 * @details This function performs a hardware reset by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void fingerprint5_reset_device ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 get IRQ pin function.
 * @details This function returns the state of the IRQ (interrupt) pin.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t fingerprint5_get_irq_pin ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 send command function.
 * @details This function sends a prepared command frame to the device.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_send_cmd ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 read command function.
 * @details This function reads a response or event frame from the device.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout error.
 * @note None.
 */
err_t fingerprint5_read_cmd ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 get status function.
 * @details This function sends the status request command to the device.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_get_status ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 get version function.
 * @details This function sends the firmware version request command to the device.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_get_version ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 enroll finger function.
 * @details This function sends the enroll command for fingerprint registration.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_enroll_finger ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 identify finger function.
 * @details This function sends the identify command to compare the input fingerprint with existing templates.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_identify_finger ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 request abort function.
 * @details This function sends the abort command to stop the current fingerprint operation.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_request_abort ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 list templates function.
 * @details This function sends the list templates command to retrieve all stored fingerprint templates.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_list_templates ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 delete templates function.
 * @details This function sends the delete command to remove all stored fingerprint templates.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_delete_templates ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 request reset function.
 * @details This function sends the reset command to restart the fingerprint sensor firmware.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_request_reset ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 start navigation function.
 * @details This function starts the navigation feature based on the specified screen orientation.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[in] orientation : Navigation screen orientation [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid parameter).
 * @note None.
 */
err_t fingerprint5_start_navigation ( fingerprint5_t *ctx, uint8_t orientation );

/**
 * @brief Fingerprint 5 run BIST function.
 * @details This function sends the built-in self-test command to initiate internal diagnostics.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_run_bist ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 set GPIO function.
 * @details This function sends the GPIO set command to configure a GPIO pin state and mode.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[in] pin : GPIO pin number.
 * @param[in] mode : GPIO mode.
 * @param[in] state : GPIO logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid parameter).
 * @note None.
 */
err_t fingerprint5_set_gpio ( fingerprint5_t *ctx, uint8_t pin, uint8_t mode, uint8_t state );

/**
 * @brief Fingerprint 5 get GPIO function.
 * @details This function sends the GPIO get command to read the state of a GPIO pin.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[in] pin : GPIO pin number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t fingerprint5_get_gpio ( fingerprint5_t *ctx, uint8_t pin );

/**
 * @brief Fingerprint 5 set system config function.
 * @details This function sends the set system configuration command with the specified configuration values.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[in] config : System configuration parameters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (null pointer or communication error).
 * @note None.
 */
err_t fingerprint5_set_config ( fingerprint5_t *ctx, fingerprint5_sys_config_t *config );

/**
 * @brief Fingerprint 5 get system config function.
 * @details This function sends the get system configuration command for the specified configuration type.
 * @param[in] ctx : Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @param[in] type : System configuration type.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid parameter).
 * @note None.
 */
err_t fingerprint5_get_config ( fingerprint5_t *ctx, uint8_t type );

#ifdef __cplusplus
}
#endif
#endif // FINGERPRINT5_H

/*! @} */ // fingerprint5

// ------------------------------------------------------------------------ END
