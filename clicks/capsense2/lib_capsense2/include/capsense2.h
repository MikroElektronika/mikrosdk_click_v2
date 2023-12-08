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
 * @file capsense2.h
 * @brief This file contains API for CapSense 2 Click Driver.
 */

#ifndef CAPSENSE2_H
#define CAPSENSE2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup capsense2 CapSense 2 Click Driver
 * @brief API for configuring and manipulating CapSense 2 Click driver.
 * @{
 */

/**
 * @defgroup capsense2_reg CapSense 2 Registers List
 * @brief List of registers of CapSense 2 Click driver.
 */

/**
 * @addtogroup capsense2_reg
 * @{
 */

/**
 * @brief CapSense 2 Register List.
 * @details Specified Register List of CapSense 2 Click driver.
 */
#define CAPSENSE2_REG_MAIN_STATUS_CONTROL               0x00
#define CAPSENSE2_REG_BUTTON_STATUS_1                   0x03
#define CAPSENSE2_REG_BUTTON_STATUS_2                   0x04
#define CAPSENSE2_REG_BUILD_REVISION                    0x05
#define CAPSENSE2_REG_SLIDER_POSITION_DATA              0x06
#define CAPSENSE2_REG_VENDOR_ID                         0x08
#define CAPSENSE2_REG_VOLUMETRIC_STEP                   0x09
#define CAPSENSE2_REG_NOISE_STATUS_1                    0x0A
#define CAPSENSE2_REG_NOISE_STATUS_2                    0x0B
#define CAPSENSE2_REG_LID_CLOSURE_STATUS_1              0x0C
#define CAPSENSE2_REG_LID_CLOSURE_STATUS_2              0x0D
#define CAPSENSE2_REG_GPIO_STATUS                       0x0E
#define CAPSENSE2_REG_GROUP_STATUS                      0x0F
#define CAPSENSE2_REG_SENSOR_1_DELTA_COUNT              0x10
#define CAPSENSE2_REG_SENSOR_2_DELTA_COUNT              0x11
#define CAPSENSE2_REG_SENSOR_3_DELTA_COUNT              0x12
#define CAPSENSE2_REG_SENSOR_4_DELTA_COUNT              0x13
#define CAPSENSE2_REG_SENSOR_5_DELTA_COUNT              0x14
#define CAPSENSE2_REG_SENSOR_6_DELTA_COUNT              0x15
#define CAPSENSE2_REG_SENSOR_7_DELTA_COUNT              0x16
#define CAPSENSE2_REG_SENSOR_8_DELTA_COUNT              0x17
#define CAPSENSE2_REG_SENSOR_9_DELTA_COUNT              0x18
#define CAPSENSE2_REG_SENSOR_10_DELTA_COUNT             0x19
#define CAPSENSE2_REG_SENSOR_11_DELTA_COUNT             0x1A
#define CAPSENSE2_REG_SENSOR_12_DELTA_COUNT             0x1B
#define CAPSENSE2_REG_SENSOR_13_DELTA_COUNT             0x1C
#define CAPSENSE2_REG_SENSOR_14_DELTA_COUNT             0x1D
#define CAPSENSE2_REG_QUEUE_CONTROL                     0x1E
#define CAPSENSE2_REG_DATA_SENSITIVITY                  0x1F
#define CAPSENSE2_REG_CONFIGURATION                     0x20
#define CAPSENSE2_REG_SENSOR_ENABLE                     0x21
#define CAPSENSE2_REG_BUTTON_CONFIGURATION              0x22
#define CAPSENSE2_REG_GROUP_CONFIGURATION_1             0x23
#define CAPSENSE2_REG_GROUP_CONFIGURATION_2             0x24
#define CAPSENSE2_REG_CALIBRATION_ENABLE                0x25
#define CAPSENSE2_REG_CALIBRATION_ACTIVATE              0x26
#define CAPSENSE2_REG_INTERRUPT_ENABLE_1                0x27
#define CAPSENSE2_REG_INTERRUPT_ENABLE_2                0x28
#define CAPSENSE2_REG_SLEEP_CHANNEL_CONTROL             0x29
#define CAPSENSE2_REG_MULTIPLE_PRESS_CONFIGURATION      0x2A
#define CAPSENSE2_REG_LID_CLOSURE_CONFIGURATION         0x2B
#define CAPSENSE2_REG_LID_CLOSURE_QUEUE_CONTROL         0x2C
#define CAPSENSE2_REG_LID_CLOSURE_PATTERN_1             0x2D
#define CAPSENSE2_REG_LID_CLOSURE_PATTERN_2             0x2E
#define CAPSENSE2_REG_RECALIBRATION_CONFIGURATION       0x2F
#define CAPSENSE2_REG_SENSOR_1_THRESHOLD                0x30
#define CAPSENSE2_REG_SENSOR_2_THRESHOLD                0x31
#define CAPSENSE2_REG_SENSOR_3_THRESHOLD                0x32
#define CAPSENSE2_REG_SENSOR_4_THRESHOLD                0x33
#define CAPSENSE2_REG_SENSOR_5_THRESHOLD                0x34
#define CAPSENSE2_REG_SENSOR_6_THRESHOLD                0x35
#define CAPSENSE2_REG_SENSOR_7_THRESHOLD                0x36
#define CAPSENSE2_REG_GROUP_THRESHOLD                   0x37
#define CAPSENSE2_REG_BUTTON_NOISE_THRESHOLD_1          0x38
#define CAPSENSE2_REG_BUTTON_NOISE_THRESHOLD_2          0x39
#define CAPSENSE2_REG_LID_CLOSURE_THRESHOLD_1           0x3A
#define CAPSENSE2_REG_LID_CLOSURE_THRESHOLD_2           0x3B
#define CAPSENSE2_REG_LID_CLOSURE_THRESHOLD_3           0x3C
#define CAPSENSE2_REG_LID_CLOSURE_THRESHOLD_4           0x3D
#define CAPSENSE2_REG_SLIDER_VELOCITY_CONFIGURATION     0x3E
#define CAPSENSE2_REG_DIGITAL_RECALIBRATION             0x3F
#define CAPSENSE2_REG_CONFIGURATION_2                   0x40
#define CAPSENSE2_REG_GROUPED_CHANNEL_SENSOR_ENABLE     0x41
#define CAPSENSE2_REG_PROXIMITY_CONTROL                 0x42
#define CAPSENSE2_REG_GROUPED_SENSOR_CALIB_ACTIVATE     0x46
#define CAPSENSE2_REG_SAMPLING_CHANNEL_SELECT           0x4E
#define CAPSENSE2_REG_SAMPLING_CONFIGURATION            0x4F
#define CAPSENSE2_REG_SENSOR_1_BASE_COUNT               0x50
#define CAPSENSE2_REG_SENSOR_2_BASE_COUNT               0x51
#define CAPSENSE2_REG_SENSOR_3_BASE_COUNT               0x52
#define CAPSENSE2_REG_SENSOR_4_BASE_COUNT               0x53
#define CAPSENSE2_REG_SENSOR_5_BASE_COUNT               0x54
#define CAPSENSE2_REG_SENSOR_6_BASE_COUNT               0x55
#define CAPSENSE2_REG_SENSOR_7_BASE_COUNT               0x56
#define CAPSENSE2_REG_SENSOR_8_BASE_COUNT               0x57
#define CAPSENSE2_REG_SENSOR_9_BASE_COUNT               0x58
#define CAPSENSE2_REG_SENSOR_10_BASE_COUNT              0x59
#define CAPSENSE2_REG_SENSOR_11_BASE_COUNT              0x5A
#define CAPSENSE2_REG_SENSOR_12_BASE_COUNT              0x5B
#define CAPSENSE2_REG_SENSOR_13_BASE_COUNT              0x5C
#define CAPSENSE2_REG_SENSOR_14_BASE_COUNT              0x5D
#define CAPSENSE2_REG_LED_STATUS_1                      0x60
#define CAPSENSE2_REG_LED_STATUS_2                      0x61
#define CAPSENSE2_REG_LED_DIRECTION                     0x70
#define CAPSENSE2_REG_LED_OUTPUT_TYPE                   0x71
#define CAPSENSE2_REG_GPIO_INPUT                        0x72
#define CAPSENSE2_REG_LED_OUTPUT_CONTROL_1              0x73
#define CAPSENSE2_REG_LED_OUTPUT_CONTROL_2              0x74
#define CAPSENSE2_REG_LED_POLARITY_1                    0x75
#define CAPSENSE2_REG_LED_POLARITY_2                    0x76
#define CAPSENSE2_REG_LINKED_LED_TRANSITION_CONTROL_1   0x77
#define CAPSENSE2_REG_LINKED_LED_TRANSITION_CONTROL_2   0x78
#define CAPSENSE2_REG_LED_MIRROR_CONTROL_1              0x79
#define CAPSENSE2_REG_LED_MIRROR_CONTROL_2              0x7A
#define CAPSENSE2_REG_SENSOR_LED_LINKING                0x80
#define CAPSENSE2_REG_LED_BEHAVIOR_1                    0x81
#define CAPSENSE2_REG_LED_BEHAVIOR_2                    0x82
#define CAPSENSE2_REG_LED_BEHAVIOR_3                    0x83
#define CAPSENSE2_REG_LED_PULSE_1_PERIOD                0x84
#define CAPSENSE2_REG_LED_PULSE_2_PERIOD                0x85
#define CAPSENSE2_REG_LED_BREATHE_PERIOD                0x86
#define CAPSENSE2_REG_LED_CONFIGURATION                 0x88
#define CAPSENSE2_REG_LED_PULSE_1_DUTY_CYCLE            0x90
#define CAPSENSE2_REG_LED_PULSE_2_DUTY_CYCLE            0x91
#define CAPSENSE2_REG_LED_BREATHE_DUTY_CYCLE            0x92
#define CAPSENSE2_REG_LED_DIRECT_DUTY_CYCLE             0x93
#define CAPSENSE2_REG_LED_DIRECT_RAMP_RATES             0x94
#define CAPSENSE2_REG_LED_OFF_DELAY                     0x95
#define CAPSENSE2_REG_SENSOR_1_CALIBRATION              0xB1
#define CAPSENSE2_REG_SENSOR_2_CALIBRATION              0xB2
#define CAPSENSE2_REG_SENSOR_3_CALIBRATION              0xB3
#define CAPSENSE2_REG_SENSOR_4_CALIBRATION              0xB4
#define CAPSENSE2_REG_SENSOR_5_CALIBRATION              0xB5
#define CAPSENSE2_REG_SENSOR_6_CALIBRATION              0xB6
#define CAPSENSE2_REG_SENSOR_7_CALIBRATION              0xB7
#define CAPSENSE2_REG_SENSOR_8_CALIBRATION              0xB8
#define CAPSENSE2_REG_SENSOR_9_CALIBRATION              0xB9
#define CAPSENSE2_REG_SENSOR_10_CALIBRATION             0xBA
#define CAPSENSE2_REG_SENSOR_11_CALIBRATION             0xBB
#define CAPSENSE2_REG_SENSOR_12_CALIBRATION             0xBC
#define CAPSENSE2_REG_SENSOR_13_CALIBRATION             0xBD
#define CAPSENSE2_REG_SENSOR_14_CALIBRATION             0xBE
#define CAPSENSE2_REG_PRODUCT_ID                        0xFD
#define CAPSENSE2_REG_MANUFACTURER_ID                   0xFE
#define CAPSENSE2_REG_REVISION                          0xFF

/*! @} */ // capsense2_reg

/**
 * @defgroup capsense2_set CapSense 2 Registers Settings
 * @brief Settings for registers of CapSense 2 Click driver.
 */

/**
 * @addtogroup capsense2_set
 * @{
 */

/**
 * @brief CapSense 2 main status control register values.
 * @details Specified main status control register values of CapSense 2 Click driver.
 */
#define CAPSENSE2_MAIN_STATUS_CONTROL_DEACT             0x40
#define CAPSENSE2_MAIN_STATUS_CONTROL_SLEEP             0x20
#define CAPSENSE2_MAIN_STATUS_CONTROL_DSLEEP            0x10
#define CAPSENSE2_MAIN_STATUS_CONTROL_PWR_LED           0x02
#define CAPSENSE2_MAIN_STATUS_CONTROL_INT               0x01

/**
 * @brief CapSense 2 button status 1 register values.
 * @details Specified main status control register values of CapSense 2 Click driver.
 */
#define CAPSENSE2_BUTTON_STATUS_1_UP_SLIDER             0x80
#define CAPSENSE2_BUTTON_STATUS_1_DOWN_SLIDER           0x40
#define CAPSENSE2_BUTTON_STATUS_1_BUTTON_2              0x02
#define CAPSENSE2_BUTTON_STATUS_1_BUTTON_1              0x01

/**
 * @brief CapSense 2 multiple press configuration register values.
 * @details Specified multiple press configuration register values of CapSense 2 Click driver.
 */
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_ENABLE          0x80
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_BUTTONS_1       0x00
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_BUTTONS_2       0x04
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_BUTTONS_3       0x08
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_BUTTONS_4       0x0C
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_GROUP_2         0x00
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_GROUP_3         0x01
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_GROUP_4         0x02
#define CAPSENSE2_MULTIPLE_PRESS_CONFIG_GROUP_1         0x03

/**
 * @brief CapSense 2 configuration register values.
 * @details Specified configuration register values of CapSense 2 Click driver.
 */
#define CAPSENSE2_CONFIGURATION_TIMEOUT                 0x80
#define CAPSENSE2_CONFIGURATION_POS_VOL                 0x40
#define CAPSENSE2_CONFIGURATION_BLK_DIG_NOISE           0x20
#define CAPSENSE2_CONFIGURATION_BLK_ANA_NOISE           0x10
#define CAPSENSE2_CONFIGURATION_MAX_DUR_EN_B            0x08
#define CAPSENSE2_CONFIGURATION_RPT_EN_B                0x04
#define CAPSENSE2_CONFIGURATION_MAX_DUR_EN_G            0x02
#define CAPSENSE2_CONFIGURATION_RPT_EN_G                0x01

/**
 * @brief CapSense 2 slider velocity configuration register values.
 * @details Specified slider velocity configuration register values of CapSense 2 Click driver.
 */
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_EXTRA_INT_EN   0x80
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_0      0x00
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_1      0x10
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_2      0x20
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_3      0x30
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_4      0x40
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_5      0x50
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_6      0x60
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_7      0x70
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_SLIDE_TIME_350 0x00
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_SLIDE_TIME_560 0x04
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_SLIDE_TIME_770 0x08
#define CAPSENSE2_SLIDER_VELOCITY_CONFIG_SLIDE_TIME_980 0x0C

/**
 * @brief CapSense 2 led direction register values.
 * @details Specified led direction register values of CapSense 2 Click driver.
 */
#define CAPSENSE2_LED_DIRECTION_OUTPUT_LED1             0x01
#define CAPSENSE2_LED_DIRECTION_OUTPUT_LED2             0x02
#define CAPSENSE2_LED_DIRECTION_OUTPUT_LED3             0x04
#define CAPSENSE2_LED_DIRECTION_OUTPUT_LED4             0x08
#define CAPSENSE2_LED_DIRECTION_OUTPUT_LED5             0x10
#define CAPSENSE2_LED_DIRECTION_OUTPUT_LED6             0x20
#define CAPSENSE2_LED_DIRECTION_OUTPUT_LED7             0x40
#define CAPSENSE2_LED_DIRECTION_OUTPUT_LED8             0x80

/**
 * @brief CapSense 2 sensor led linking register values.
 * @details Specified sensor led linking register values of CapSense 2 Click driver.
 */
#define CAPSENSE2_SENSOR_LED_LINKING_CS1_LED1           0x01
#define CAPSENSE2_SENSOR_LED_LINKING_CS2_LED2           0x02
#define CAPSENSE2_SENSOR_LED_LINKING_CS3_LED3           0x04
#define CAPSENSE2_SENSOR_LED_LINKING_CS4_LED4           0x08
#define CAPSENSE2_SENSOR_LED_LINKING_CS5_LED5           0x10
#define CAPSENSE2_SENSOR_LED_LINKING_CS6_LED6           0x20
#define CAPSENSE2_SENSOR_LED_LINKING_CS7_LED7           0x40
#define CAPSENSE2_SENSOR_LED_LINKING_UP_DOWN_LINK       0x80

/**
 * @brief CapSense 2 ID values.
 * @details Specified ID values of CapSense 2 Click driver.
 */
#define CAPSENSE2_VENDOR_ID                             0x5D
#define CAPSENSE2_MANUFACTURER_ID                       0x5D
#define CAPSENSE2_PRODUCT_ID                            0x3A

/**
 * @brief CapSense 2 device address setting.
 * @details Specified setting for device slave address selection of
 * CapSense 2 Click driver.
 */
#define CAPSENSE2_SET_DEV_ADDR                          0x28

/*! @} */ // capsense2_set

/**
 * @defgroup capsense2_map CapSense 2 MikroBUS Map
 * @brief MikroBUS pin mapping of CapSense 2 Click driver.
 */

/**
 * @addtogroup capsense2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CapSense 2 Click to the selected MikroBUS.
 */
#define CAPSENSE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // capsense2_map
/*! @} */ // capsense2

/**
 * @brief CapSense 2 Click context object.
 * @details Context object definition of CapSense 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset pin. */

    // Input pins
    digital_in_t   alt;         /**< Alert pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} capsense2_t;

/**
 * @brief CapSense 2 Click configuration object.
 * @details Configuration object definition of CapSense 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;            /**< Reset pin. */
    pin_name_t  alt;            /**< Alert pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} capsense2_cfg_t;

/**
 * @brief CapSense 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CAPSENSE2_OK = 0,
    CAPSENSE2_ERROR = -1

} capsense2_return_value_t;

/*!
 * @addtogroup capsense2 CapSense 2 Click Driver
 * @brief API for configuring and manipulating CapSense 2 Click driver.
 * @{
 */

/**
 * @brief CapSense 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #capsense2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void capsense2_cfg_setup ( capsense2_cfg_t *cfg );

/**
 * @brief CapSense 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #capsense2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t capsense2_init ( capsense2_t *ctx, capsense2_cfg_t *cfg );

/**
 * @brief CapSense 2 default configuration function.
 * @details This function executes a default configuration of CapSense 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t capsense2_default_cfg ( capsense2_t *ctx );

/**
 * @brief CapSense 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t capsense2_generic_write ( capsense2_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief CapSense 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t capsense2_generic_read ( capsense2_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief CapSense 2 write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t capsense2_write_register ( capsense2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief CapSense 2 read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t capsense2_read_register ( capsense2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief CapSense 2 set reset pin function.
 * @details This function sets the RST pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void capsense2_set_reset_pin ( capsense2_t *ctx, uint8_t state );

/**
 * @brief CapSense 2 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t capsense2_get_alert_pin ( capsense2_t *ctx );

/**
 * @brief CapSense 2 reset device function.
 * @details This function performs the device reset by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void capsense2_reset_device ( capsense2_t *ctx );

/**
 * @brief CapSense 2 check communication function.
 * @details This function checks the communication by reading and verifying the chip identification numbers.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t capsense2_check_communication ( capsense2_t *ctx );

/**
 * @brief CapSense 2 clear interrupt function.
 * @details This function clears the INT bit of the main status register if the interrupt pin is asserted.
 * @param[in] ctx : Click context object.
 * See #capsense2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t capsense2_clear_interrupt ( capsense2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CAPSENSE2_H

/*! @} */ // capsense2

// ------------------------------------------------------------------------ END
