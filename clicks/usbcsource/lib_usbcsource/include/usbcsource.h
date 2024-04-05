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
 * @file usbcsource.h
 * @brief This file contains API for USB-C Source Click Driver.
 */

#ifndef USBCSOURCE_H
#define USBCSOURCE_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup usbcsource USB-C Source Click Driver
 * @brief API for configuring and manipulating USB-C Source Click driver.
 * @{
 */

/**
 * @defgroup usbcsource_reg USB-C Source Registers List
 * @brief List of registers of USB-C Source Click driver.
 */

/**
 * @addtogroup usbcsource_reg
 * @{
 */

/**
 * @brief USB-C Source description register.
 * @details Specified register for description of USB-C Source Click driver.
 */
#define USBCSOURCE_REG_ALERT_STATUS_REG                             0x0B
#define USBCSOURCE_REG_ALERT_STATUS_MASK_CTRL                       0x0C
#define USBCSOURCE_REG_CC_CONNECTION_STATUS_TRANS                   0x0D
#define USBCSOURCE_REG_CC_CONNECTION_STATUS_1                       0x0E
#define USBCSOURCE_REG_MONITORING_STATUS_TRANS                      0x0F
#define USBCSOURCE_REG_MONITORING_STATUS                            0x10
#define USBCSOURCE_REG_CC_CONNECTION_STATUS_2                       0x11
#define USBCSOURCE_REG_HW_FAULT_STATUS_TRANS                        0x12
#define USBCSOURCE_REG_HW_FAULT_STATUS                              0x13
#define USBCSOURCE_REG_CC_CAPABILITY_CTRL                           0x18
#define USBCSOURCE_REG_RESET_CTRL                                   0x23
#define USBCSOURCE_REG_VBUS_DISCHARGE_TIME_CTRL                     0x25
#define USBCSOURCE_REG_VBUS_DISCHARGE_STATUS                        0x26
#define USBCSOURCE_REG_VBUS_ENABLE_STATUS                           0x27
#define USBCSOURCE_REG_VBUS_MONITORING_CTRL                         0x2E

#define USBCSOURCE_REG_SRC_PDO1                                     0x71
#define USBCSOURCE_REG_SRC_PDO2                                     0x75
#define USBCSOURCE_REG_SRC_PDO3                                     0x79
#define USBCSOURCE_REG_SRC_PDO4                                     0x7D
#define USBCSOURCE_REG_SRC_PDO5                                     0x81

/*! @} */ // usbcsource_reg

/**
 * @defgroup usbcsource_set USB-C Source Registers Settings
 * @brief Settings for registers of USB-C Source Click driver.
 */

/**
 * @addtogroup usbcsource_set
 * @{
 */

/**
 * @brief USB-C Source description setting.
 * @details Specified setting for description of USB-C Source Click driver.
 */

/**
 * @brief USB-C PDO select setting.
 * @details Specified PDO select setting of USB-C Source Click driver.
 */
#define USBCSOURCE_SEL_PDO1                                         0x01
#define USBCSOURCE_SEL_PDO2                                         0x02
#define USBCSOURCE_SEL_PDO3                                         0x03
#define USBCSOURCE_SEL_PDO4                                         0x04
#define USBCSOURCE_SEL_PDO5                                         0x05

/**
 * @brief USB-C PDO NVM voltage configuration.
 * @details Specified PDO NVM voltage configuration setting of USB-C Source Click driver.
 */
#define USBCSOURCE_PDO_NVM_VOLT_CFG_9_V                             0x00
#define USBCSOURCE_PDO_NVM_VOLT_CFG_15_V                            0x01
#define USBCSOURCE_PDO_NVM_VOLT_CFG_FLEX_V1                         0x02
#define USBCSOURCE_PDO_NVM_VOLT_CFG_FLEX_V2                         0x03

/**
 * @brief USB-C PDO NVM current configuration.
 * @details Specified PDO NVM current configuration setting of USB-C Source Click driver.
 */
#define USBCSOURCE_PDO_NVM_CUR_FLEX_I                               0x00
#define USBCSOURCE_PDO_NVM_CUR_1_50_A                               0x01
#define USBCSOURCE_PDO_NVM_CUR_1_75_A                               0x02
#define USBCSOURCE_PDO_NVM_CUR_2_00_A                               0x03
#define USBCSOURCE_PDO_NVM_CUR_2_25_A                               0x04
#define USBCSOURCE_PDO_NVM_CUR_2_50_A                               0x05
#define USBCSOURCE_PDO_NVM_CUR_2_75_A                               0x06
#define USBCSOURCE_PDO_NVM_CUR_3_00_A                               0x07
#define USBCSOURCE_PDO_NVM_CUR_3_25_A                               0x08
#define USBCSOURCE_PDO_NVM_CUR_3_50_A                               0x09
#define USBCSOURCE_PDO_NVM_CUR_3_75_A                               0x0A
#define USBCSOURCE_PDO_NVM_CUR_4_00_A                               0x0B
#define USBCSOURCE_PDO_NVM_CUR_4_25_A                               0x0C
#define USBCSOURCE_PDO_NVM_CUR_4_50_A                               0x0D
#define USBCSOURCE_PDO_NVM_CUR_4_75_A                               0x0E
#define USBCSOURCE_PDO_NVM_CUR_5_00_A                               0x0F

/**
 * @brief USB-C software reset.
 * @details Specified software reset setting of USB-C Source Click driver.
 */
#define USBCSOURCE_RESET_DIS                                        0x00
#define USBCSOURCE_RESET_EN                                         0x01

/**
 * @brief USB-C alert state.
 * @details Specified alert state setting of USB-C Source Click driver.
 */
#define USBCSOURCE_ALERT_STAT_HARD_RESET_AL                         0x80
#define USBCSOURCE_ALERT_STAT_PORT_STAT_AL                          0x40
#define USBCSOURCE_ALERT_STAT_TYPEC_MON_AL                          0x20
#define USBCSOURCE_ALERT_STAT_CC_HW_FAULT_AL                        0x10
#define USBCSOURCE_ALERT_STAT_DPM_STAT_AL                           0x08
#define USBCSOURCE_ALERT_STAT_PE_STAT_AL                            0x04
#define USBCSOURCE_ALERT_STAT_PRT_STAT_AL                           0x02
#define USBCSOURCE_ALERT_STAT_PHY_STAT_AL                           0x01

/**
 * @brief USB-C attached device.
 * @details Specified attached device setting of USB-C Source Click driver.
 */
#define USBCSOURCE_ATTACHED_DEVICE_NONE_ATT                         0x00
#define USBCSOURCE_ATTACHED_DEVICE_SNK_ATT                          0x01
#define USBCSOURCE_ATTACHED_DEVICE_SRC_ATT                          0x02
#define USBCSOURCE_ATTACHED_DEVICE_DBG_ATT                          0x03
#define USBCSOURCE_ATTACHED_DEVICE_AUD_ATT                          0x04
#define USBCSOURCE_ATTACHED_DEVICE_POW_ACC_ATT                      0x05

/**
 * @brief USB-C low power standby.
 * @details Specified low power standby setting of USB-C Source Click driver.
 */
#define USBCSOURCE_LOW_POWER_STANDBY_OFF                            0x00
#define USBCSOURCE_LOW_POWER_STANDBY_ON                             0x01

/**
 * @brief USB-C power mode.
 * @details Specified power mode setting of USB-C Source Click driver.
 */
#define USBCSOURCE_POWER_MODE_SNK                                   0x00
#define USBCSOURCE_POWER_MODE_SRC                                   0x01

/**
 * @brief USB-C data mode.
 * @details Specified data mode setting of USB-C Source Click driver.
 */
#define USBCSOURCE_DATA_MODE_UFP                                    0x00
#define USBCSOURCE_DATA_MODE_DFP                                    0x01

/**
 * @brief USB-C connection attach.
 * @details Specified connection attach setting of USB-C Source Click driver.
 */
#define USBCSOURCE_CONN_UNATTACHED                                  0x00
#define USBCSOURCE_CONN_ATTACHED                                    0x01

/**
 * @brief USB-C VBUS settings.
 * @details Specified VBUS setting of USB-C Source Click driver.
 */
#define USBCSOURCE_VBUS_READY_DISCONNECTED                          0x00
#define USBCSOURCE_VBUS_READY_CONNECTED                             0x01

#define USBCSOURCE_VBUS_VSAFE0V_0_8V_HIGHER                         0x00
#define USBCSOURCE_VBUS_VSAFE0V_0_8V_LOWER                          0x01

#define USBCSOURCE_VBUS_VALID_3_9V_LOWER                            0x00
#define USBCSOURCE_VBUS_VALID_3_9V_HIGHER                           0x01

/**
 * @brief USB-C status.
 * @details Specified status setting of USB-C Source Click driver.
 */
#define USBCSOURCE_STATUS_ERROR                                     0x00
#define USBCSOURCE_STATUS_SUCCESS                                   0x01

/**
 * @brief USB-C Source device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Source Click driver.
 */
#define USBCSOURCE_I2C_SLAVE_ADR_GND                                 0x28
#define USBCSOURCE_I2C_SLAVE_ADR_VCC                                 0x29

/*! @} */ // usbcsource_set

/**
 * @defgroup usbcsource_map USB-C Source MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Source Click driver.
 */

/**
 * @addtogroup usbcsource_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Source Click to the selected MikroBUS.
 */
#define USBCSOURCE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcsource_map
/*! @} */ // usbcsource

/**
 * @brief USB-C Source Click context object.
 * @details Context object definition of USB-C Source Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset. */

    // Input pins
    digital_in_t  int_pin;      /**< Interrupt. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} usbcsource_t;

/**
 * @brief USB-C Source Click configuration object.
 * @details Configuration object definition of USB-C Source Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;            /**< Reset. */
    pin_name_t  int_pin;        /**< Interrupt. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} usbcsource_cfg_t;

/**
 * @brief USB-C Source Click alert status object.
 * @details Alert status object definition of USB-C Source Click driver.
 */
typedef struct
{
    uint8_t hard_reset_al;
    uint8_t port_status_al;
    uint8_t typec_monitoring_status_al;
    uint8_t cc_hw_fault_status_al;
    uint8_t prt_status_al;
    uint8_t phy_status_al;
} alert_status_t;

/**
 * @brief USB-C Source Click port status object.
 * @details Port status object definition of USB-C Source Click driver.
 */
typedef struct
{
    uint8_t attached_device;
    uint8_t low_power_standby;
    uint8_t power_mode;
    uint8_t data_mode;
    uint8_t vconn_mode;
    uint8_t attach;
} port_status_t;

/**
 * @brief USB-C Source Click monitor status object.
 * @details Monitor status object definition of USB-C Source Click driver.
 */
typedef struct
{
    uint8_t pd_typec_hand_check;
    uint8_t vbus_ready;
    uint8_t vbus_vsafe0v;
    uint8_t vbus_valid;
    uint8_t vconn_valid;
} monitor_status_t;

/**
 * @brief USB-C Source Click connection status object.
 * @details Connection status object definition of USB-C Source Click driver.
 */
typedef struct
{
    uint8_t cc_reverse;
    uint8_t snk_power_level;
    uint8_t typec_fsm_state;
} connection_status_t;

/**
 * @brief USB-C Source Click fault status object.
 * @details Fault status object definition of USB-C Source Click driver.
 */
typedef struct
{
    uint8_t th_145_status;
    uint8_t vpu_ovp_fault_trans;
    uint8_t vpu_valid_trans;
    uint8_t vconn_sw_rvp_fault_trans;
    uint8_t vconn_sw_ocp_fault_trans;
    uint8_t vconn_sw_ovp_fault_trans;
    uint8_t vpu_ovp_fault;
    uint8_t vpu_valid;
    uint8_t vconn_sw_rvp_fault_cc1;
    uint8_t vconn_sw_rvp_fault_cc2;
    uint8_t vconn_sw_ocp_fault_cc1;
    uint8_t vconn_sw_ocp_fault_cc2;
    uint8_t vconn_sw_ovp_fault_cc1;
    uint8_t vconn_sw_ovp_fault_cc2;
} fault_status_t;

/**
 * @brief USB-C Source Click PDO config object.
 * @details PDO config object definition of USB-C Source Click driver.
 */
typedef struct
{
    uint8_t pdo_number;
    uint8_t fixed_supply;
    uint8_t dual_role_power;
    uint8_t usb_suspend_support;
    uint8_t unconstr_power;
    uint8_t usb_commun_capable;
    uint8_t dual_role_data;
    uint8_t unch_exd_mesg_support;
    uint8_t peak_current;
    float vtg_data;
    float curr_data;
} pdo_config_t;

/**
 * @brief USB-C Source Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   USBCSOURCE_OK = 0,
   USBCSOURCE_ERROR = -1

} usbcsource_return_value_t;

/*!
 * @addtogroup usbcsource USB-C Source Click Driver
 * @brief API for configuring and manipulating USB-C Source Click driver.
 * @{
 */

/**
 * @brief USB-C Source configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcsource_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcsource_cfg_setup ( usbcsource_cfg_t *cfg );

/**
 * @brief USB-C Source initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcsource_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t usbcsource_init ( usbcsource_t *ctx, usbcsource_cfg_t *cfg );

/**
 * @brief USB-C Source I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t usbcsource_generic_write ( usbcsource_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief USB-C Source I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t usbcsource_generic_read ( usbcsource_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Generic write function.
 * @details The function write the byte of data
 * to the target 8-bit register address of the STUSB4700, 
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : Byte of data to write.
 * @return Nothing.
**/
void usbcsource_write_byte ( usbcsource_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Generic read function.
 * @details The function read the the byte of data
 * from the target 8-bit register address of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @return 8-bit read data.
**/
uint8_t usbcsource_read_byte ( usbcsource_t *ctx, uint8_t reg );

/**
 * @brief HW reset function.
 * @details The function hardware reset,
 * reset the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[out] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @return Nothing.
**/
void usbcsource_hw_reset ( usbcsource_t *ctx );

/**
 * @brief Get INT pin state function.
 * @details The function get INT pin state
 * reset the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[out] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @return State of the INT pin.
**/
uint8_t usbcsource_int_pin_state ( usbcsource_t *ctx );

/**
 * @brief Get alert status function.
 * @details The function get alert status
 * by read the byte of data from a register USBCSOURCE_REG_ALERT_STATUS_REG
 * of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[out] alert_status_data : Pointer to the memory location where data be stored.
 * @return Nothing.
**/
void usbcsource_get_alert_status ( usbcsource_t *ctx, alert_status_t *alert_status_data );

/**
 * @brief Set alert status function.
 * @details The function set alert status
 * by write the byte of data to a register USBCSOURCE_REG_ALERT_STATUS_REG
 * of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[out] alert_status_data : Structure where data be stored.
 * @return Nothing.
**/
void usbcsource_set_alert_status ( usbcsource_t *ctx, alert_status_t alert_status_data );

/**
 * @brief Check attach trans function.
 * @details The function check attach transition
 * of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @return @li @c 0 - Transition not detected in Attached state.
 *         @li @c 1 - Transition detected in Attached state.
**/
uint8_t usbcsource_check_attach_trans ( usbcsource_t *ctx );

/**
 * @brief Get port status function.
 * @details The function get port status
 * by read the byte of data from a register 
 * USBCSOURCE_REG_CC_CONNECTION_STATUS_1 of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[out] port_status_data : Pointer to the memory location where data be stored.
 * @return Nothing.
**/
void usbcsource_get_port_status ( usbcsource_t *ctx, port_status_t *port_status_data );

/**
 * @brief Get monitoring status function.
 * @details The function get monitoring status
 * by read the byte of data from a registers
 * USBCSOURCE_REG_MONITORING_STATUS_TRANS and USBCSOURCE_REG_MONITORING_STATUS
 * of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[out] port_monitoring_data : Pointer to the memory location where data be stored.
 * @return Nothing.
**/
void usbcsource_get_monitoring_status ( usbcsource_t *ctx, monitor_status_t *monitor_status_data );

/**
 * @brief Get connection status function.
 * @details The function get connection status
 * by read the byte of data from a register 
 * USBCSOURCE_REG_CC_CONNECTION_STATUS_2 of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[out] port_connection_data : Pointer to the memory location where data be stored.
 * @return Nothing.
**/
void usbcsource_get_connection_status ( usbcsource_t *ctx, connection_status_t *conn_data );

/**
 * @brief Get fault status function.
 * @details The function get fault status
 * by read the byte of data from a registers
 * USBCSOURCE_REG_HW_FAULT_STATUS_TRANS and USBCSOURCE_REG_HW_FAULT_STATUS
 * of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[out] port_fault_data : Pointer to the memory location where data be stored.
 * @return Nothing.
**/
void usbcsource_get_fault_status ( usbcsource_t *ctx, fault_status_t *fault_data );

/**
 * @brief SW reset function.
 * @details The function software reset,
 * reset the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @return Nothing.
**/
void usbcsource_sw_reset ( usbcsource_t *ctx );

/**
 * @brief Set PDO configuration function.
 * @details The function set the configuration of the desired PDO
 * of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[out] pdo_cfg_data : Structure where data be stored.
 * @return Nothing.
**/
uint8_t usbcsource_set_pdo_config ( usbcsource_t *ctx, pdo_config_t pdo_cfg_data );

/**
 * @brief Get PDO configuration function.
 * @details The function get the configuration of the desired PDO
 * of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @param[in] pdo_numb : Number of the source PDOs[ 1 - 5 ].
 * @param[out] pdo_cfg_data Pointer to the memory location where data be stored.
 * @return Status.
**/
uint8_t usbcsource_get_pdo_config ( usbcsource_t *ctx, uint8_t pdo_numb, pdo_config_t *pdo_cfg_data );

/**
 * @brief Default configuration function.
 * @details The function set the default configuration
 * of the STUSB4700,
 * Standalone autonomous USB PD controller with short-to-VBUS protections
 * on USB-C Source Click board.
 * @param[in] ctx : Click context object.
 * See #usbcsource_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note Default configuration:
 * - PDO1 : Voltage  5V, Current 3A.
 * - PDO2 : Voltage  9V, Current 3A.
 * - PDO3 : Voltage 12V, Current 3A.
 * - PDO4 : Voltage 15V, Current 3A.
 * - PDO5 : Voltage 20V, Current 2.25A.
**/
void usbcsource_default_config ( usbcsource_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBCSOURCE_H

/*! @} */ // usbcsource

// ------------------------------------------------------------------------ END
