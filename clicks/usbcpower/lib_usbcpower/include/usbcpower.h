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
 * @file usbcpower.h
 * @brief This file contains API for USB-C Power Click Driver.
 */

#ifndef USBCPOWER_H
#define USBCPOWER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup usbcpower USB-C Power Click Driver
 * @brief API for configuring and manipulating USB-C Power Click driver.
 * @{
 */

/**
 * @defgroup usbcpower_reg USB-C Power Registers List
 * @brief List of registers of USB-C Power Click driver.
 */

/**
 * @addtogroup usbcpower_reg
 * @{
 */

/**
 * @brief USB-C Power description register.
 * @details Specified register for description of USB-C Power Click driver.
 */
#define USBCPOWER_REG_MODE                      0x03
#define USBCPOWER_MODE_REG_SIZE                    5
#define USBCPOWER_REG_TYPE                      0x04
#define USBCPOWER_TYPE_REG_SIZE                    5
#define USBCPOWER_REG_CUSTUSE                   0x06
#define USBCPOWER_CUSTUSE_REG_SIZE                 9
#define USBCPOWER_REG_CMD1                      0x08
#define USBCPOWER_CMD1_REG_SIZE                    5
#define USBCPOWER_REG_DATA                      0x09
#define USBCPOWER_DATA_REG_SIZE                   65
#define USBCPOWER_REG_DEVICE_CAP                0x0D
#define USBCPOWER_DEVICE_CAP_REG_SIZE              5 
#define USBCPOWER_REG_VERSION                   0x0F
#define USBCPOWER_VERSION_REG_SIZE                 5
#define USBCPOWER_REG_INT_EVENT1                0x14
#define USBCPOWER_INT_EVENT1_REG_SIZE             15
#define USBCPOWER_REG_INT_MASK1                 0x16
#define USBCPOWER_INT_MASK1_REG_SIZE              12
#define USBCPOWER_REG_INT_CLEAR1                0x18
#define USBCPOWER_INT_CLEAR1_REG_SIZE             12
#define USBCPOWER_REG_STATUS                    0x1A
#define USBCPOWER_STATUS_REG_SIZE                  6
#define USBCPOWER_REG_POWER_PATH_STATUS         0x26
#define USBCPOWER_POWER_PATH_STATUS_REG_SIZE       6
#define USBCPOWER_REG_PORT_CONTROL              0x29
#define USBCPOWER_PORT_CONTROL_REG_SIZE            5
#define USBCPOWER_REG_BOOT_STATUS               0x2D
#define USBCPOWER_BOOT_STATUS_REG_SIZE             6
#define USBCPOWER_REG_BUILD_DESC                0x2E
#define USBCPOWER_BUILD_DESC_SIZE                 50
#define USBCPOWER_REG_DEVICE_INFO               0x2F
#define USBCPOWER_DEVICE_INFO_REG_SIZE            41
#define USBCPOWER_REG_RX_SOURCE_CAPS            0x30
#define USBCPOWER_RX_SOURCE_CAPS_REG_SIZE         30
#define USBCPOWER_REG_RX_SINK_CAPS              0x31
#define USBCPOWER_RX_SINK_CAPS_REG_SIZE           30
#define USBCPOWER_REG_TX_SOURCE_CAPS            0x32
#define USBCPOWER_TX_SOURCE_CAPS_REG_SIZE         32
#define USBCPOWER_REG_TX_SINK_CAPS              0x33
#define USBCPOWER_TX_SINK_CAPS_REG_SIZE           30
#define USBCPOWER_REG_ACTIVE_CONTRACT_PDO       0x34
#define USBCPOWER_ACTIVE_CONTRACT_PDO_REG_SIZE     7
#define USBCPOWER_REG_ACTIVE_CONTRACT_RDO       0x35
#define USBCPOWER_ACTIVE_CONTRACT_RDO_REG_SIZE     5
#define USBCPOWER_REG_POWER_STATUS              0x3F
#define USBCPOWER_POWER_STATUS_REG_SIZE            3
#define USBCPOWER_REG_PD_STATUS                 0x40
#define USBCPOWER_PD_STATUS_REG_SIZE               5
#define USBCPOWER_REG_TYPEC_STATE               0x69
#define USBCPOWER_TYPEC_STATE_REG_SIZE             5
#define USBCPOWER_REG_GPIO_STATUS               0x72
#define USBCPOWER_GPIO_STATUS_REG_SIZE             9

/*! @} */ // usbcpower_reg

/**
 * @defgroup usbcpower_set USB-C Power Registers Settings
 * @brief Settings for registers of USB-C Power Click driver.
 */

/**
 * @addtogroup usbcpower_set
 * @{
 */

/**
 * @brief USB-C Power description setting.
 * @details Specified setting for description of USB-C Power Click driver.
 */
#define USBCPOWER_CAP_POWER_ROLE_M              0x03
#define USBCPOWER_CAP_USBPD_CAP_M               0x04
#define USBCPOWER_CAP_I2CMLEVEL_VOLT_M          0x80

/**
 * @brief USB-C Power description status value.
 * @details Specified status value for description of USB-C Power Click driver.
 */
#define USBCPOWER_STATUS_PLUG_PRESENT_M         0x01
#define USBCPOWER_STATUS_CONN_STATE_M           0x0E
#define USBCPOWER_STATUS_PLUG_OR_M              0x10
#define USBCPOWER_STATUS_PORT_ROLE_M            0x20
#define USBCPOWER_STATUS_DATA_ROLE_M            0x40
#define USBCPOWER_STATUS_VBUS_STATUS_M          0x30
#define USBCPOWER_STATUS_USB_HOST_PRSNT_M       0xC0
#define USBCPOWER_STATUS_ACT_LEGACY_M           0x03
#define USBCPOWER_STATUS_BIST_M                 0x08

/**
 * @brief USB-C Power description standard task response value.
 * @details Specified tasks response value for description of USB-C Power Click driver.
 */
#define USBCPOWER_RSP_OK                        0x00
#define USBCPOWER_RSP_PBMs                      "PBMs"
#define USBCPOWER_RSP_PTCH                      "PTCH"
#define USBCPOWER_RSP_APP                       "APP "
#define USBCPOWER_RSP_BOOT                      "BOOT"
#define USBCPOWER_RSP_DEVICE_INFO_NAME          "TPS65992"

/**
 * @brief USB-C Power description 4CC tasks command value.
 * @details Specified 4CC tasks command value for description of USB-C Power Click driver.
 */
#define USBCPOWER_CMD_SWSk                      "4SWSk"
#define USBCPOWER_CMD_SWSr                      "4SWSr"
#define USBCPOWER_CMD_SWDF                      "4SWDF"
#define USBCPOWER_CMD_SWUF                      "4SWUF"
#define USBCPOWER_CMD_GSkC                      "4GSkC"
#define USBCPOWER_CMD_GSrC                      "4GSrC"
#define USBCPOWER_CMD_SSrC                      "4SSrC"
#define USBCPOWER_CMD_PTCH                      "4PTCH"
#define USBCPOWER_CMD_GO2P                      "4GO2P"
#define USBCPOWER_CMD_PBMs                      "4PBMs"
#define USBCPOWER_CMD_PBMc                      "4PBMc"
#define USBCPOWER_CMD_PBMe                      "4PBMe"

/**
 * @brief USB-C Power description of device modes value.
 * @details Specified device modes value for description of USB-C Power Click driver.
 */
#define USBCPOWER_MODE_PTCH                     0x00
#define USBCPOWER_MODE_APP                      0x01
#define USBCPOWER_MODE_BOOT                     0x02
#define USBCPOWER_MODE_UNKNOWN                  0x03
#define USBCPOWER_PD_CON_MODE_SOURCE            0x00
#define USBCPOWER_PD_CON_MODE_SINK              0x01
#define USBCPOWER_PD_MODE_SELECTOR              USBCPOWER_PD_CON_MODE_SOURCE

/**
 * @brief USB-C Power description of power status value.
 * @details Specified power status information value for description of USB-C Power Click driver.
 */
#define USBCPOWER_STATUS_NO_CONNECTION          0x00
#define USBCPOWER_STATUS_PORT_DISABLED          0x01
#define USBCPOWER_STATUS_AUDIO_CONNECTION       0x02
#define USBCPOWER_STATUS_DEBUG_CONNECTION       0x03
#define USBCPOWER_STATUS_NO_CONNECTION_Ra       0x04
#define USBCPOWER_STATUS_RESERVED               0x05
#define USBCPOWER_STATUS_CONNECT_NO_Ra          0x06
#define USBCPOWER_PWR_STATUS_USB                0x00
#define USBCPOWER_PWR_STATUS_TYPE_C_1_5A        0x01
#define USBCPOWER_PWR_STATUS_TYPE_C_3_0A        0x02
#define USBCPOWER_PWR_STATUS_CHG_ADV_DISABLE    0x00
#define USBCPOWER_PWR_STATUS_CHG_ADV_PROCESS    0x01
#define USBCPOWER_PWR_STATUS_CHG_ADV_COMPLETE   0x02

/**
 * @brief USB-C Power device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Power Click driver.
 */
#define USBCPOWER_DEVICE_ADDRESS                0x21

/*! @} */ // usbcpower_set

/**
 * @defgroup usbcpower_map USB-C Power MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Power Click driver.
 */

/**
 * @addtogroup usbcpower_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Power Click to the selected MikroBUS.
 */
#define USBCPOWER_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcpower_map
/*! @} */ // usbcpower

/**
 * @brief USB-C Power Click context object.
 * @details Context object definition of USB-C Power Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;    /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} usbcpower_t;

/**
 * @brief USB-C Power Click configuration object.
 * @details Configuration object definition of USB-C Power Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;        /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} usbcpower_cfg_t;

/**
 * @brief USB-C Power Click PBMs configuration object.
 * @details Configuration for initializing the firmware in preparation 
 * for a patch bundle load sequence object definition of USB-C Power Click driver.
 */
typedef struct
{
    uint32_t bundle_size;
    uint8_t eeprom_slave_address;
    uint8_t timeout_value;

} usbcpower_pbms_cfg_t;

/**
 * @brief USB-C Power Click status information object.
 * @details Status information object definition of USB-C Power Click driver.
 */
typedef struct
{
    uint8_t plug_present;
    uint8_t conn_state;
    uint8_t plug_orientation;
    uint8_t port_role;
    uint8_t data_role;
    uint8_t vbus_status;
    uint8_t usb_hos_tpresent;
    uint8_t acting_as_legacy;
    uint8_t bist;

} usbcpower_status_t;

/**
 * @brief USB-C Power Click power path status object.
 * @details Power path status object definition of USB-C Power Click driver.
 */
typedef struct
{
    uint8_t pp_cable1_switch;
    uint8_t pp1_switch;
    uint8_t pp3_switch;
    uint8_t pp1_overcurrent;
    uint8_t pp_cable1_ovc;
    uint8_t power_source;

} usbcpower_pwr_path_status_t;

/**
 * @brief USB-C Power Click boot path status object.
 * @details Boot status object definition of USB-C Power Click driver.
 */
typedef struct
{
    uint8_t patch_header_err;
    uint8_t dead_battery_flag;
    uint8_t i2c_eeprom_present;
    uint8_t patch_downloader;
    uint8_t master_tsd;
    uint8_t patch_cfg_source;
    uint8_t rev_id;

} usbcpower_boot_status_t;

/**
 * @brief USB-C Power Click rx source/sink caps object.
 * @details Rx source/sink caps object definition of USB-C Power Click driver.
 */
typedef struct
{
    uint8_t  num_src_pdos;
    uint32_t source_pdo[ 8 ];
    uint8_t  num_sink_pdos;
    uint32_t sink_pdo[ 8 ];

} usbcpower_rx_caps_t;

/**
 * @brief USB-C Power Click power status object.
 * @details Power status object definition of USB-C Power Click driver.
 */
typedef struct
{
    uint8_t pwr_conn;
    uint8_t src_sink;
    uint8_t type_c_current;
    uint8_t charger_detect;
    uint8_t charger_advertise;

} usbcpower_pwr_status_t;

/**
 * @brief USB-C Power Click PD status object.
 * @details PD status object definition of USB-C Power Click driver.
 */
typedef struct
{
    uint8_t cc_pull_up;
    uint8_t port_type;
    uint8_t pd_role;
    uint8_t soft_rst_dets;
    uint8_t hard_rst_dets;
    uint8_t err_rec_dets;
    uint8_t data_rst_dets;

} usbcpower_pd_status_t;


/**
 * @brief USB-C Power Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBCPOWER_OK = 0,
    USBCPOWER_ERROR = -1

} usbcpower_return_value_t;

/*!
 * @addtogroup usbcpower USB-C Power Click Driver
 * @brief API for configuring and manipulating USB-C Power Click driver.
 * @{
 */

/**
 * @brief USB-C Power configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcpower_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcpower_cfg_setup ( usbcpower_cfg_t *cfg );

/**
 * @brief USB-C Power initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcpower_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_init ( usbcpower_t *ctx, usbcpower_cfg_t *cfg );

/**
 * @brief USB-C Power default configuration function.
 * @details This function executes a default configuration of USB-C Power
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t usbcpower_default_cfg ( usbcpower_t *ctx );

/**
 * @brief USB-C Power I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_generic_write ( usbcpower_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief USB-C Power I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_generic_read ( usbcpower_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief USB-C Power get device mode function.
 * @details This function reads a device information value 
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] device_mode : Device mode string.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_device_mode ( usbcpower_t *ctx, uint8_t *device_mode );

/**
 * @brief USB-C Power get device capabilities function.
 * @details This function reads a device capabilities value
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] device_cap : Device capabilities.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_device_capabilities ( usbcpower_t *ctx, uint8_t *device_cap );

/**
 * @brief USB-C Power device info function.
 * @details This function reads a ASCII string with hardware 
 * and firmware version information of the PD Controller
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] device_info : Device information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_device_info ( usbcpower_t *ctx, uint8_t *device_info );

/**
 * @brief USB-C Power set patch mode function.
 * @details This function set the patch mode,
 * forces PD controller to return to 'PTCH' mode and wait for patch over I2C
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] response : Response code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_set_patch_mode ( usbcpower_t *ctx, uint32_t *response );

/**
 * @brief USB-C Power starts the patch burst mode function.
 * @details This function write sequence for loading a patch bundle 
 * in burst mode to the PD controller from an external host over I2C
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[in] pbms_cfg : The 'PBMs' task configuration object.
 * See usbcpower_pbms_cfg_t definition for detailed explanation.
 * @param[out] response : Response code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The 'PBMs' Task starts the patch loading sequence. 
 * This Task initializes the firmware in preparation 
 * for a patch bundle load sequence and 
 * indicates what the patch bundle will contain.
 */
err_t usbcpower_start_patch_burst_mode ( usbcpower_t *ctx, usbcpower_pbms_cfg_t pbms_cfg, uint32_t *response );

/**
 * @brief USB-C Power complete the patch burst mode function.
 * @details This function ends the patch loading sequence
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] response : Response code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The 'PBMc' Task ends the patch loading sequence. 
 * Send this Task after all patch data has been transferred. 
 * This Task will initiate the CRC check on the binary patch data 
 * that has been transferred, and if the CRC is successful, 
 * the function contained within the patch will be executed.
 */
err_t usbcpower_complete_patch_burst_mode ( usbcpower_t *ctx, uint32_t *response );

/**
 * @brief USB-C Power exit the patch burst mode function.
 * @details This function ends the patch loading sequence
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] response : Response code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The 'PBMe' Task ends the patch loading sequence. 
 * This Task instructs the PD controller to complete 
 * the patch loading process.
 */
err_t usbcpower_exit_patch_burst_mode ( usbcpower_t *ctx, uint32_t *response );

/**
 * @brief USB-C Power gets selected mode function.
 * @details This function reads application operation mode
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] sel_mode :
 *         @li @c 0x00 (USBCPOWER_MODE_PTCH)    - Device in patch mode,
 *         @li @c 0x01 (USBCPOWER_MODE_APP)     - The PD Controller is fully functioning in the application firmware,
 *         @li @c 0x02 (USBCPOWER_MODE_BOOT)    - Device booting in dead battery,
 *         @li @c 0x03 (USBCPOWER_MODE_UNKNOWN) - The PD Controller is functioning in a limited capacity.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_selected_mode ( usbcpower_t *ctx, uint8_t *sel_mode );

/**
 * @brief USB-C Power update patch bundle function.
 * @details This function writes the entire patch-bundle data 
 * in a single I2C transaction
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[in] pbms_cfg : The 'PBMs' task configuration object.
 * See usbcpower_pbms_cfg_t definition for detailed explanation.
 * @param[out] response : Response code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The PD controller increments the pointer 
 * into its patch memory space with each byte received 
 * on the Patch Slave address that was configured 
 * as part of the 'PBMs' 4CC Task.
 */
err_t usbcpower_update_patch_bundle ( usbcpower_t *ctx, usbcpower_pbms_cfg_t pbms_cfg );

/**
 * @brief USB-C Power gets status function.
 * @details This function reads a status information
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] status : Status information object.
 * See usbcpower_status_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_status ( usbcpower_t *ctx, usbcpower_status_t *status );

/**
 * @brief USB-C Power gets power path status function.
 * @details This function reads a power path status
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] pp_status : Power path status object.
 * See usbcpower_pwr_path_status_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_pwr_path_status ( usbcpower_t *ctx, usbcpower_pwr_path_status_t *pp_status );

/**
 * @brief USB-C Power gets boot status function.
 * @details This function reads a boot status
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] boot_status : Boot status object.
 * See usbcpower_boot_status_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_boot_status ( usbcpower_t *ctx, usbcpower_boot_status_t *boot_status );

/**
 * @brief USB-C Power gets RX caps function.
 * @details This function reads a source and sink capabilities
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] rx_caps : Source and sink capabilities object.
 * See usbcpower_rx_caps_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_rx_caps ( usbcpower_t *ctx, usbcpower_rx_caps_t *rx_caps );

/**
 * @brief USB-C Power gets PWR status function.
 * @details This function reads a power of the connection status info
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] pwr_status : Power of the connection status object.
 * See usbcpower_pwr_status_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_pwr_status ( usbcpower_t *ctx, usbcpower_pwr_status_t *pwr_status );

/**
 * @brief USB-C Power gets PD status function.
 * @details This function reads a power status of PD and Type-C state-machine
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @param[out] pd_status : Source and sink capabilities object.
 * See usbcpower_pd_status_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower_get_pd_status ( usbcpower_t *ctx, usbcpower_pd_status_t *pd_status );

/**
 * @brief USB-C Power gets interrupt function.
 * @details This function get states of the Interrupt ( INT ) pin
 * of the TPS25750 USB Type-C® and USB PD Controller with 
 * Integrated Power Switches Optimized for Power Applications
 * on the USB-C Power Click board™.
 * @param[in] ctx : Click context object.
 * See #usbcpower_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t usbcpower_get_int_pin ( usbcpower_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBCPOWER_H

/*! @} */ // usbcpower

// ------------------------------------------------------------------------ END
