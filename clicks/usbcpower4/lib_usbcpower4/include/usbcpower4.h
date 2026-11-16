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
 * @file usbcpower4.h
 * @brief This file contains API for USB-C Power 4 Click Driver.
 */

#ifndef USBCPOWER4_H
#define USBCPOWER4_H

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
 * @addtogroup usbcpower4 USB-C Power 4 Click Driver
 * @brief API for configuring and manipulating USB-C Power 4 Click driver.
 * @{
 */

/**
 * @defgroup usbcpower4_reg USB-C Power 4 Registers List
 * @brief List of registers of USB-C Power 4 Click driver.
 */

/**
 * @addtogroup usbcpower4_reg
 * @{
 */

/**
 * @brief USB-C Power 4 TPS26750A register map.
 * @details Register offsets available through the TPS26750A I2C Unique Address
 * Interface.
 */
#define USBCPOWER4_REG_MODE                       0x03
#define USBCPOWER4_REG_CUSTOMER_USE               0x06
#define USBCPOWER4_REG_CMD1                       0x08
#define USBCPOWER4_REG_DATA1                      0x09
#define USBCPOWER4_REG_VERSION                    0x0F
#define USBCPOWER4_REG_INT_EVENT1                 0x14
#define USBCPOWER4_REG_INT_MASK1                  0x16
#define USBCPOWER4_REG_INT_CLEAR1                 0x18
#define USBCPOWER4_REG_STATUS                     0x1A
#define USBCPOWER4_REG_POWER_PATH_STATUS          0x26
#define USBCPOWER4_REG_GLOBAL_SYSTEM_CONFIG       0x27
#define USBCPOWER4_REG_PORT_CONFIG                0x28
#define USBCPOWER4_REG_PORT_CONTROL               0x29
#define USBCPOWER4_REG_BOOT_FLAGS                 0x2D
#define USBCPOWER4_REG_RX_SOURCE_CAPS             0x30
#define USBCPOWER4_REG_RX_SINK_CAPS               0x31
#define USBCPOWER4_REG_TX_SOURCE_CAPS             0x32
#define USBCPOWER4_REG_TX_SINK_CAPS               0x33
#define USBCPOWER4_REG_ACTIVE_PDO                 0x34
#define USBCPOWER4_REG_ACTIVE_RDO                 0x35
#define USBCPOWER4_REG_AUTO_NEGOTIATE_SINK        0x37
#define USBCPOWER4_REG_POWER_STATUS               0x3F
#define USBCPOWER4_REG_PD_STATUS                  0x40
#define USBCPOWER4_REG_PD3_CONFIG                 0x42
#define USBCPOWER4_REG_RX_IDENTITY                0x48
#define USBCPOWER4_REG_IO_CONFIG                  0x5C
#define USBCPOWER4_REG_TYPE_C_STATE               0x69
#define USBCPOWER4_REG_ADC_RESULTS                0x6A
#define USBCPOWER4_REG_SLEEP_CONTROL              0x70
#define USBCPOWER4_REG_GPIO_STATUS                0x72
#define USBCPOWER4_REG_TX_MANUFACTURER_INFO       0x73
#define USBCPOWER4_REG_TX_SOURCE_CAPS_EXT         0x77
#define USBCPOWER4_REG_TX_SOURCE_INFO             0x78
#define USBCPOWER4_REG_TX_PPS_STATUS              0x7A
#define USBCPOWER4_REG_TX_BATTERY_STATUS          0x7B
#define USBCPOWER4_REG_TX_BATTERY_CAPS            0x7D
#define USBCPOWER4_REG_TX_SINK_CAPS_EXT           0x7E
#define USBCPOWER4_REG_RX_MIDB                    0xA4

/*! @} */ // usbcpower4_reg

/**
 * @defgroup usbcpower4_set USB-C Power 4 Registers Settings
 * @brief Settings for registers of USB-C Power 4 Click driver.
 */

/**
 * @addtogroup usbcpower4_set
 * @{
 */

/**
 * @brief USB-C Power 4 I2C settings.
 * @details The board ADCIN1 and ADCIN2 straps select I2C address index 4,
 * corresponding to the 7-bit target address 0x23.
 */
#define USBCPOWER4_DEVICE_ADDRESS                 0x23
#define USBCPOWER4_MAX_REG_SIZE                   64
#define USBCPOWER4_UAI_HEADER_SIZE                2
#define USBCPOWER4_UAI_COUNT_SIZE                 1

/**
 * @brief USB-C Power 4 register data sizes.
 * @details Expected TPS26750A payload lengths, excluding the UAI byte-count
 * field returned before each register payload.
 */
#define USBCPOWER4_MODE_SIZE                      4
#define USBCPOWER4_STATUS_SIZE                    5
#define USBCPOWER4_PORT_CONTROL_SIZE              4
#define USBCPOWER4_POWER_STATUS_SIZE              2
#define USBCPOWER4_PD_STATUS_SIZE                 4
#define USBCPOWER4_ACTIVE_PDO_SIZE                6
#define USBCPOWER4_ADC_RESULTS_SIZE               13
#define USBCPOWER4_TASK_SIZE                      4
#define USBCPOWER4_PBMS_DATA_SIZE                 6

/**
 * @brief USB-C Power 4 MODE register values.
 * @details Four ASCII bytes identify application, boot, or patch operation.
 */
#define USBCPOWER4_MODE_APP_0                     'A'
#define USBCPOWER4_MODE_APP_1                     'P'
#define USBCPOWER4_MODE_APP_2                     'P'
#define USBCPOWER4_MODE_APP_3                     ' '
#define USBCPOWER4_MODE_PTCH_0                    'P'
#define USBCPOWER4_MODE_PTCH_1                    'T'
#define USBCPOWER4_MODE_PTCH_2                    'C'
#define USBCPOWER4_MODE_PTCH_3                    'H'

/**
 * @brief USB-C Power 4 application loading settings.
 * @details Parameters used to load a TI Low Region application image through
 * the TPS26750A patch-burst interface.
 */
#define USBCPOWER4_PATCH_TARGET_ADDRESS           0x30
#define USBCPOWER4_PATCH_BURST_SIZE               64
#define USBCPOWER4_PATCH_TIMEOUT                  0x32
#define USBCPOWER4_TASK_RETRY_COUNT               5000
#define USBCPOWER4_APP_RETRY_COUNT                1000
#define USBCPOWER4_TASK_SUCCESS                   0x00

/**
 * @brief USB-C Power 4 board pin states.
 * @details EPR controls the TPD4S480 EPR adapter. The interrupt output is
 * active low.
 */
#define USBCPOWER4_EPR_MODE_DISABLED              0
#define USBCPOWER4_EPR_MODE_ENABLED               1
#define USBCPOWER4_INT_ASSERTED                   0
#define USBCPOWER4_INT_DEASSERTED                 1

/**
 * @brief USB-C Power 4 STATUS register fields.
 * @details Masks and shifts used to decode connection, role, orientation, and
 * VBUS state from the five-byte STATUS register.
 */
#define USBCPOWER4_STATUS_PLUG_MASK               0x01
#define USBCPOWER4_STATUS_CONN_MASK               0x0E
#define USBCPOWER4_STATUS_CONN_SHIFT              1
#define USBCPOWER4_STATUS_ORIENTATION_MASK        0x10
#define USBCPOWER4_STATUS_ORIENTATION_SHIFT       4
#define USBCPOWER4_STATUS_POWER_ROLE_MASK         0x20
#define USBCPOWER4_STATUS_POWER_ROLE_SHIFT        5
#define USBCPOWER4_STATUS_DATA_ROLE_MASK          0x40
#define USBCPOWER4_STATUS_DATA_ROLE_SHIFT         6
#define USBCPOWER4_STATUS_VBUS_INDEX              2
#define USBCPOWER4_STATUS_VBUS_MASK               0x30
#define USBCPOWER4_STATUS_VBUS_SHIFT              4

/**
 * @brief USB-C Power 4 PORT_CONTROL register settings.
 * @details Byte position and bit mask for the Enable Current Monitor field.
 * Enabling this field keeps the controller active and measures current flowing
 * through the internal PP5V source path.
 */
#define USBCPOWER4_PORT_CURRENT_INDEX             2
#define USBCPOWER4_PORT_CURRENT_MASK              0x10
#define USBCPOWER4_CURRENT_MONITOR_DISABLED       0
#define USBCPOWER4_CURRENT_MONITOR_ENABLED        1

/**
 * @brief USB-C Power 4 POWER_STATUS and PD_STATUS fields.
 * @details Masks and shifts used to decode power connection, advertised
 * Type-C current, port type, and detected CC pull-up.
 */
#define USBCPOWER4_POWER_CONNECTION_MASK          0x01
#define USBCPOWER4_TYPEC_CURRENT_MASK             0x0C
#define USBCPOWER4_TYPEC_CURRENT_SHIFT            2
#define USBCPOWER4_PD_CC_PULLUP_MASK              0x0C
#define USBCPOWER4_PD_CC_PULLUP_SHIFT             2
#define USBCPOWER4_PD_PORT_TYPE_MASK              0x30
#define USBCPOWER4_PD_PORT_TYPE_SHIFT             4

/**
 * @brief USB-C Power 4 connection states.
 * @details Decoded STATUS register connection values.
 */
#define USBCPOWER4_NOT_CONNECTED                  0
#define USBCPOWER4_PORT_DISABLED                  1
#define USBCPOWER4_AUDIO_CONNECTED                2
#define USBCPOWER4_DEBUG_CONNECTED                3
#define USBCPOWER4_RA_ONLY                        4
#define USBCPOWER4_CONNECTED_NO_RA                6
#define USBCPOWER4_CONNECTED_WITH_RA              7

/**
 * @brief USB-C Power 4 power and data roles.
 * @details Current TPS26750A USB Type-C and USB data roles.
 */
#define USBCPOWER4_POWER_ROLE_SINK                0
#define USBCPOWER4_POWER_ROLE_SOURCE              1
#define USBCPOWER4_DATA_ROLE_UFP                  0
#define USBCPOWER4_DATA_ROLE_DFP                  1
#define USBCPOWER4_ORIENTATION_CC1                0
#define USBCPOWER4_ORIENTATION_CC2                1

/**
 * @brief USB-C Power 4 VBUS states.
 * @details Decoded STATUS register VBUS voltage range.
 */
#define USBCPOWER4_VBUS_SAFE_0V                   0
#define USBCPOWER4_VBUS_SAFE_5V                   1
#define USBCPOWER4_VBUS_EXPECTED                  2
#define USBCPOWER4_VBUS_OUT_OF_RANGE              3

/**
 * @brief USB-C Power 4 advertised Type-C current.
 * @details Current level detected from CC or superseded by an explicit USB PD
 * contract.
 */
#define USBCPOWER4_TYPEC_CURRENT_DEFAULT          0
#define USBCPOWER4_TYPEC_CURRENT_1_5A             1
#define USBCPOWER4_TYPEC_CURRENT_3_0A             2
#define USBCPOWER4_TYPEC_CURRENT_PD               3

/**
 * @brief USB-C Power 4 PDO supply types.
 * @details Supply type encoded in bits 31:30 of a USB Power Data Object.
 */
#define USBCPOWER4_PDO_TYPE_FIXED                 0
#define USBCPOWER4_PDO_TYPE_BATTERY               1
#define USBCPOWER4_PDO_TYPE_VARIABLE              2
#define USBCPOWER4_PDO_TYPE_AUGMENTED             3
#define USBCPOWER4_APDO_TYPE_PPS                  0

/**
 * @brief USB-C Power 4 PDO field definitions.
 * @details Masks, shifts, and units used to decode fixed, battery, variable,
 * and PPS APDO capabilities.
 */
#define USBCPOWER4_PDO_TYPE_MASK                  0xC0000000UL
#define USBCPOWER4_PDO_TYPE_SHIFT                 30
#define USBCPOWER4_APDO_TYPE_MASK                 0x30000000UL
#define USBCPOWER4_APDO_TYPE_SHIFT                28
#define USBCPOWER4_PDO_MAX_VOLTAGE_MASK           0x3FF00000UL
#define USBCPOWER4_PDO_MAX_VOLTAGE_SHIFT          20
#define USBCPOWER4_PDO_MIN_VOLTAGE_MASK           0x000FFC00UL
#define USBCPOWER4_PDO_MIN_VOLTAGE_SHIFT          10
#define USBCPOWER4_FIXED_VOLTAGE_MASK             0x000FFC00UL
#define USBCPOWER4_FIXED_VOLTAGE_SHIFT            10
#define USBCPOWER4_PDO_CURRENT_MASK               0x000003FFUL
#define USBCPOWER4_PDO_POWER_MASK                 0x000003FFUL
#define USBCPOWER4_PPS_MAX_VOLTAGE_MASK           0x01FE0000UL
#define USBCPOWER4_PPS_MAX_VOLTAGE_SHIFT          17
#define USBCPOWER4_PPS_MIN_VOLTAGE_MASK           0x0000FF00UL
#define USBCPOWER4_PPS_MIN_VOLTAGE_SHIFT          8
#define USBCPOWER4_PPS_CURRENT_MASK               0x0000007FUL
#define USBCPOWER4_PDO_VOLTAGE_STEP_MV            50
#define USBCPOWER4_PDO_CURRENT_STEP_MA            10
#define USBCPOWER4_PDO_POWER_STEP_MW              250
#define USBCPOWER4_PPS_VOLTAGE_STEP_MV            100
#define USBCPOWER4_PPS_CURRENT_STEP_MA            50

/**
 * @brief USB-C Power 4 ADC result positions and scales.
 * @details Byte positions and integer conversion factors for the TPS26750A ADC
 * Results register. VBUS current uses a 16.5 mA per LSB scale represented as
 * an integer numerator and divider.
 */
#define USBCPOWER4_ADC_ADCIN1_INDEX               0
#define USBCPOWER4_ADC_ADCIN2_INDEX               1
#define USBCPOWER4_ADC_LDO3V3_INDEX               2
#define USBCPOWER4_ADC_VBUS_INDEX                 3
#define USBCPOWER4_ADC_IVBUS_MEAN_INDEX           5
#define USBCPOWER4_ADC_IVBUS_PEAK_INDEX           11
#define USBCPOWER4_ADC_GPIO_LSB_MV                14
#define USBCPOWER4_ADC_VBUS_LSB_MV                98
#define USBCPOWER4_ADC_CURRENT_SCALE              165
#define USBCPOWER4_ADC_CURRENT_DIVIDER            10

/*! @} */ // usbcpower4_set

/**
 * @defgroup usbcpower4_map USB-C Power 4 MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Power 4 Click driver.
 */

/**
 * @addtogroup usbcpower4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Power 4 Click to the selected MikroBUS.
 */
#define USBCPOWER4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.epr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcpower4_map
/*! @} */ // usbcpower4

/**
 * @brief USB-C Power 4 Click context object.
 * @details Context object definition of USB-C Power 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t epr;          /**< TPD4S480 EPR mode control pin. */

    // Input pins
    digital_in_t int_pin;       /**< TPS26750A active-low interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} usbcpower4_t;

/**
 * @brief USB-C Power 4 Click configuration object.
 * @details Configuration object definition of USB-C Power 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t epr;             /**< TPD4S480 EPR mode control pin. */
    pin_name_t int_pin;         /**< TPS26750A active-low interrupt pin. */

    // Static variables
    uint32_t i2c_speed;         /**< I2C serial speed. */
    uint8_t  i2c_address;       /**< I2C slave address. */

} usbcpower4_cfg_t;

/**
 * @brief USB-C Power 4 connection status object.
 * @details Decoded USB-C attachment, role, orientation, VBUS, and advertised
 * current information.
 */
typedef struct
{
    uint8_t plug_present;       /**< USB-C plug presence flag. */
    uint8_t connection_state;   /**< Decoded Type-C connection state. */
    uint8_t orientation;        /**< Active CC1 or CC2 orientation. */
    uint8_t power_role;         /**< Active sink or source power role. */
    uint8_t data_role;          /**< Active UFP or DFP data role. */
    uint8_t vbus_state;         /**< Decoded VBUS voltage range. */
    uint8_t power_connection;   /**< Valid Type-C power connection flag. */
    uint8_t typec_current;      /**< Advertised Type-C current level. */
    uint8_t cc_pullup;          /**< Detected partner CC pull-up level. */
    uint8_t port_type;          /**< Active TPS26750A Type-C port type. */

} usbcpower4_status_t;

/**
 * @brief USB-C Power 4 active PDO object.
 * @details Decoded active USB PD Power Data Object. Fields not applicable to a
 * selected supply type remain zero.
 */
typedef struct
{
    uint8_t  valid;             /**< Active PDO validity state. */
    uint8_t  supply_type;       /**< PDO supply type. */
    uint8_t  apdo_type;         /**< Augmented PDO subtype. */
    uint16_t voltage_mv;        /**< Fixed supply voltage in millivolts. */
    uint16_t min_voltage_mv;    /**< Minimum supply voltage in millivolts. */
    uint16_t max_voltage_mv;    /**< Maximum supply voltage in millivolts. */
    uint16_t current_ma;        /**< PDO current capability in milliamperes. */
    uint32_t power_mw;          /**< PDO power capability in milliwatts. */
    uint32_t raw_pdo;           /**< Unmodified active PDO value. */

} usbcpower4_contract_t;

/**
 * @brief USB-C Power 4 ADC result object.
 * @details Converted TPS26750A ADC measurements. The ADC Results register is
 * intended by TI for development and diagnostic use.
 */
typedef struct
{
    uint16_t adcin1_mv;         /**< ADCIN1 voltage in millivolts. */
    uint16_t adcin2_mv;         /**< ADCIN2 voltage in millivolts. */
    uint16_t ldo_3v3_mv;        /**< LDO_3V3 voltage in millivolts. */
    uint16_t vbus_mv;           /**< VBUS voltage in millivolts. */
    uint16_t vbus_mean_ma;      /**< Mean PP5V source-path current in milliamperes. */
    uint16_t vbus_peak_ma;      /**< Peak PP5V source-path current in milliamperes. */

} usbcpower4_adc_t;

/**
 * @brief USB-C Power 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBCPOWER4_OK = 0,
    USBCPOWER4_ERROR = -1

} usbcpower4_return_value_t;

/*!
 * @addtogroup usbcpower4 USB-C Power 4 Click Driver
 * @brief API for configuring and manipulating USB-C Power 4 Click driver.
 * @{
 */

/**
 * @brief USB-C Power 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcpower4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcpower4_cfg_setup ( usbcpower4_cfg_t *cfg );

/**
 * @brief USB-C Power 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcpower4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower4_init ( usbcpower4_t *ctx, usbcpower4_cfg_t *cfg );

/**
 * @brief USB-C Power 4 default configuration function.
 * @details This function verifies communication with the TPS26750A and places
 * the TPD4S480 port protector in standard power range mode.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The TPS26750A I2C address and initial behavior are selected by the
 * board ADCIN straps.
 */
err_t usbcpower4_default_cfg ( usbcpower4_t *ctx );

/**
 * @brief USB-C Power 4 write register function.
 * @details This function writes a single byte using the TPS26750A byte-counted
 * Unique Address Interface protocol.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower4_write_reg ( usbcpower4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief USB-C Power 4 write registers function.
 * @details This function writes a byte-counted payload to the selected
 * TPS26750A register.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The maximum supported payload is #USBCPOWER4_MAX_REG_SIZE bytes.
 */
err_t usbcpower4_write_regs ( usbcpower4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief USB-C Power 4 read register function.
 * @details This function reads one byte from a TPS26750A register and validates
 * the returned byte count.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower4_read_reg ( usbcpower4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief USB-C Power 4 read registers function.
 * @details This function reads a TPS26750A byte-counted register payload and
 * copies the requested number of bytes to the output buffer.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The returned byte count may exceed @p len because TPS26750A permits a
 * controller to terminate a register read before the complete payload.
 */
err_t usbcpower4_read_regs ( usbcpower4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief USB-C Power 4 communication check function.
 * @details This function verifies communication by reading the TPS26750A MODE
 * register.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower4_check_communication ( usbcpower4_t *ctx );

/**
 * @brief USB-C Power 4 read mode function.
 * @details This function reads the four ASCII bytes from the TPS26750A MODE
 * register.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[out] mode : Pointer to a four-byte output buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The output is not null terminated.
 */
err_t usbcpower4_read_mode ( usbcpower4_t *ctx, uint8_t *mode );

/**
 * @brief USB-C Power 4 application loading function.
 * @details This function loads a TI Low Region application image through the
 * TPS26750A patch-burst interface and verifies that the controller enters
 * application mode.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[in] app_image : Pointer to the Low Region application image.
 * @param[in] app_size : Application image size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note A controller already operating in APP mode is left unchanged. Any
 * other non-PTCH mode causes the function to return an error.
 */
err_t usbcpower4_load_app ( usbcpower4_t *ctx, const uint8_t *app_image, uint32_t app_size );

/**
 * @brief USB-C Power 4 read status function.
 * @details This function reads and decodes the STATUS, POWER_STATUS, and
 * PD_STATUS registers.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[out] status : Pointer to the decoded status object.
 * See #usbcpower4_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower4_read_status ( usbcpower4_t *ctx, usbcpower4_status_t *status );

/**
 * @brief USB-C Power 4 read active PDO function.
 * @details This function reads and decodes the current explicit USB PD
 * contract PDO.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[out] contract : Pointer to the active PDO object.
 * See #usbcpower4_contract_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note A zero PDO reports a valid read with the @c valid member cleared.
 */
err_t usbcpower4_read_active_pdo ( usbcpower4_t *ctx, usbcpower4_contract_t *contract );

/**
 * @brief USB-C Power 4 read ADC results function.
 * @details This function reads and converts TPS26750A ADC results to integer
 * millivolt and milliampere values.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[out] adc_result : Pointer to the converted ADC result object.
 * See #usbcpower4_adc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note TI specifies the ADC Results register for debug use. PP5V current has
 * a 16.5 mA resolution and is valid only when its monitor is enabled while the
 * port sources 5 V through the internal PP5V path.
 */
err_t usbcpower4_read_adc_results ( usbcpower4_t *ctx, usbcpower4_adc_t *adc_result );

/**
 * @brief USB-C Power 4 current monitor setting function.
 * @details This function performs a read-modify-write of PORT_CONTROL to enable
 * or disable the TPS26750A internal PP5V current monitor without changing the
 * remaining port policy fields.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[in] state : Current monitor state.
 * See #USBCPOWER4_CURRENT_MONITOR_DISABLED and
 * #USBCPOWER4_CURRENT_MONITOR_ENABLED settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The current result does not represent sink current or current supplied
 * through an external high-voltage power path.
 */
err_t usbcpower4_set_current_monitor ( usbcpower4_t *ctx, uint8_t state );

/**
 * @brief USB-C Power 4 EPR mode setting function.
 * @details This function controls the TPD4S480 EPR adapter through the
 * MikroBUS PWM pin.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @param[in] mode : EPR mode state.
 * See #USBCPOWER4_EPR_MODE_DISABLED and #USBCPOWER4_EPR_MODE_ENABLED settings.
 * @return Nothing.
 * @note EPR mode must be coordinated with the active USB PD policy.
 */
void usbcpower4_set_epr_mode ( usbcpower4_t *ctx, uint8_t mode );

/**
 * @brief USB-C Power 4 interrupt pin reading function.
 * @details This function reads the active-low TPS26750A interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #usbcpower4_t object definition for detailed explanation.
 * @return Interrupt pin logic state.
 * @note None.
 */
uint8_t usbcpower4_get_int_pin ( usbcpower4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBCPOWER4_H

/*! @} */ // usbcpower4

// ------------------------------------------------------------------------ END
