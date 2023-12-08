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
 * @file touchpad5.h
 * @brief This file contains API for Touchpad 5 Click Driver.
 */

#ifndef TOUCHPAD5_H
#define TOUCHPAD5_H

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
 * @addtogroup touchpad5 Touchpad 5 Click Driver
 * @brief API for configuring and manipulating Touchpad 5 Click driver.
 * @{
 */

/**
 * @defgroup touchpad5_cmd TouchPad 5 Registers List
 * @brief List of registers of TouchPad 5 Click driver.
 */

/**
 * @addtogroup touchpad5_cmd
 * @{
 */

/**
 * @brief TouchPad 5 description register.
 * @details Specified register for description of TouchPad 5 Click driver.
 */
#define TOUCHPAD5_CMD_VERSION_INFO              0x00 
#define TOUCHPAD5_CMD_XY_DATA                   0x01 
#define TOUCHPAD5_CMD_PROXIMITY_STATUS          0x02 
#define TOUCHPAD5_CMD_TOUCH_STATUS              0x03 
#define TOUCHPAD5_CMD_COUNT_VALUES              0x04 
#define TOUCHPAD5_CMD_LONG_TERM_AVERAGES        0x05 
#define TOUCHPAD5_CMD_ATI_COMPENSATION          0x06 
#define TOUCHPAD5_CMD_PORT_CONTROL              0x07 
#define TOUCHPAD5_CMD_SNAP_STATUS               0x08 
#define TOUCHPAD5_CMD_CONTROL_SETTINGS          0x10 
#define TOUCHPAD5_CMD_THRESHOLD_SETTINGS        0x11 
#define TOUCHPAD5_CMD_ATI_SETTINGS              0x12 
#define TOUCHPAD5_CMD_FILTER_SETTINGS           0x13 
#define TOUCHPAD5_CMD_TIMING_SETTINGS           0x14 
#define TOUCHPAD5_CMD_CHANNEL_SETUP             0x15 
#define TOUCHPAD5_CMD_HARDWARE_CONFIG_SETTINGS  0x16 
#define TOUCHPAD5_CMD_ACTIVE_CHANNELS           0x17 
#define TOUCHPAD5_CMD_DEBOUNCE_SETTINGS         0x18 
#define TOUCHPAD5_CMD_PM_PROXIMITY_STATUS       0x20 
#define TOUCHPAD5_CMD_PM_COUNT_VALUES           0x21 
#define TOUCHPAD5_CMD_PM_LONG_TERM_AVERAGES     0x22 
#define TOUCHPAD5_CMD_PM_ATI_COMPENSATION       0x23 
#define TOUCHPAD5_CMD_PM_ATI_SETTINGS           0x24 
#define TOUCHPAD5_CMD_BOOTLOADER                0xFF

/*! @} */ // touchpad5_cmd

/**
 * @defgroup touchpad5_set TouchPad 5 Registers Settings
 * @brief Settings for registers of TouchPad 5 Click driver.
 */

/**
 * @addtogroup touchpad5_set
 * @{
 */

/**
 * @brief TouchPad 5 device address setting.
 * @details Specified setting for device slave address selection of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_SET_DEV_ADDR                  0x74

/**
 * @brief TouchPad 5 description setting.
 * @details Specified setting for description of TouchPad 5 Click driver.
 */


/**
 * @brief TouchPad 5 XY Info Byte bit definitions.
 * @details Specified setting for XY Info Byte bits of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_SHOW_RESET                    0x80
#define TOUCHPAD5_MODE_INDICATOR                0x40
#define TOUCHPAD5_NOISE_STATUS                  0x20
#define TOUCHPAD5_LP_STATUS                     0x10
#define TOUCHPAD5_SNAP_OUTPUT                   0x08
#define TOUCHPAD5_NO_OF_FINGERS                 0x07

/**
 * @brief TouchPad 5 Control Settings 0 and 1 definitions.
 * @details Specified setting for Control Settings of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_ACK_RESET                     0x80
#define TOUCHPAD5_AUTO_MODES                    0x40
#define TOUCHPAD5_SINGLE_XY                     0x20
#define TOUCHPAD5_PM_RESEED                     0x10
#define TOUCHPAD5_MODE_SELECT                   0x08
#define TOUCHPAD5_AUTO_ATI                      0x04
#define TOUCHPAD5_TRACKPAD_RESEED               0x02
#define TOUCHPAD5_EVENT_MODE                    0x01
#define TOUCHPAD5_DIS_PROX_EVENT                0x80
#define TOUCHPAD5_DIS_TOUCH_EVENT               0x40
#define TOUCHPAD5_DIS_SNAP_EVENT                0x20
#define TOUCHPAD5_DIS_PMPROX_EVENT              0x10
#define TOUCHPAD5_REVERSE_EN                    0x08
#define TOUCHPAD5_SLEEP_EN                      0x04
#define TOUCHPAD5_LOW_POWER                     0x02
#define TOUCHPAD5_SNAP_EN                       0x01

/**
 * @brief TouchPad 5 Control Filter Settings definitions.
 * @details Specified setting for Control Settings of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_DIS_NM_FILTER                 0x10
#define TOUCHPAD5_DIS_PM_FILTER                 0x08
#define TOUCHPAD5_SELECT_TOUCH_FILTER           0x04
#define TOUCHPAD5_DIS_HOVER_FILTER              0x02
#define TOUCHPAD5_DIS_TOUCH_FILTER              0x01

/**
 * @brief TouchPad 5 PM Setup definitions.
 * @details Specified setting for Control Settings of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_CHARGE_TYPE_SELF_CHARG        0x80
#define TOUCHPAD5_CHARGE_MUTUAL_SELF_CHARG      0x00
#define TOUCHPAD5_RX_GROUP_RXB                  0x40
#define TOUCHPAD5_RX_GROUP_RXA                  0x00
#define TOUCHPAD5_SUM_OF_TP_RX                  0x10
#define TOUCHPAD5_SUM_OF_TP_TX                  0x00
#define TOUCHPAD5_RX_SELECT                     0x0F
#define TOUCHPAD5_TX_HIGH_DFLT                  0x1F
#define TOUCHPAD5_TX_LOW_DFLT                   0xFF

/**
 * @brief TouchPad 5 Hardware Settings definitions.
 * @details Specified setting for Hardware Settings of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_ND_ENABLE                     0x20
#define TOUCHPAD5_RX_FLOAT                      0x04
#define TOUCHPAD5_CK_FREQ_2                     0x40
#define TOUCHPAD5_CK_FREQ_1                     0x20
#define TOUCHPAD5_CK_FREQ_0                     0x10
#define TOUCHPAD5_ANA_DEAD_TIME                 0x02
#define TOUCHPAD5_INCR_PHASE                    0x01
#define TOUCHPAD5_STAB_TIME_1                   0x80
#define TOUCHPAD5_STAB_TIME_0                   0x40
#define TOUCHPAD5_OPAMP_BIAS_1                  0x20
#define TOUCHPAD5_OPAMP_BIAS_0                  0x10
#define TOUCHPAD5_VTRIP_3                       0x08
#define TOUCHPAD5_VTRIP_2                       0x04
#define TOUCHPAD5_VTRIP_1                       0x02
#define TOUCHPAD5_VTRIP_0                       0x01
#define TOUCHPAD5_UPLEN_2                       0x40
#define TOUCHPAD5_UPLEN_1                       0x20
#define TOUCHPAD5_UPLEN_0                       0x10
#define TOUCHPAD5_PASSLEN_2                     0x04
#define TOUCHPAD5_PASSLEN_1                     0x02
#define TOUCHPAD5_PASSLEN_0                     0x01

/**
 * @brief TouchPad 5 XY Config definitions.
 * @details Specified setting for XY Config of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_PALM_REJECT                   0x08
#define TOUCHPAD5_SWITCH_XY_AXIS                0x04
#define TOUCHPAD5_FLIP_Y                        0x02
#define TOUCHPAD5_FLIP_X                        0x01

/**
 * @brief TouchPad 5 System Config definitions.
 * @details Specified setting for System Config of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_PROX_EVENT                    0x80
#define TOUCHPAD5_TOUCH_EVENT                   0x40
#define TOUCHPAD5_SNAP_EVENT                    0x20
#define TOUCHPAD5_ALP_PROX_EVENT                0x10
#define TOUCHPAD5_REATI_EVENT                   0x08
#define TOUCHPAD5_TP_EVENT                      0x04
#define TOUCHPAD5_GESTURE_EVENT                 0x02
#define TOUCHPAD5_EVENT_MODE                    0x01
#define TOUCHPAD5_ALP_COUNT_FILTER              0x08
#define TOUCHPAD5_IIR_SELECT                    0x04
#define TOUCHPAD5_MAV_FILTER                    0x02
#define TOUCHPAD5_IIR_FILTER                    0x01 

/**
 * @brief TouchPad 5 ALP Channel Setup definitions.
 * @details Specified setting for ALP Channel Setup of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_CHARGE_TYPE                   0x80
#define TOUCHPAD5_RX_GROUP                      0x40
#define TOUCHPAD5_PROX_REV                      0x20
#define TOUCHPAD5_ALP_ENABLE                    0x10 

/**
 * @brief TouchPad 5 Rx To Tx definitions.
 * @details Specified setting for Rx To Tx of
 * TouchPad 5 Click driver.
 */
#define TOUCHPAD5_RX7_TX2                       0x80
#define TOUCHPAD5_RX6_TX3                       0x40
#define TOUCHPAD5_RX5_TX4                       0x20
#define TOUCHPAD5_RX4_TX5                       0x10
#define TOUCHPAD5_RX3_TX6                       0x08
#define TOUCHPAD5_RX2_TX7                       0x04
#define TOUCHPAD5_RX1_TX8                       0x02
#define TOUCHPAD5_RX0_TX9                       0x01 


/*! @} */ // touchpad5_set

/**
 * @defgroup sel_status TouchPad 5 Proximity and Touch Status data.
 * @brief Settings for Proximity and Touch Status of TouchPad 5 Click driver.
 */

/**
 * @addtogroup sel_status
 * @{
 */

/**
 * @brief TouchPad 5 status selection.
 * @details Specified status selection of TouchPad 5 Click driver.
 */
#define TOUCHPAD5_PROXIMITY_STATUS              0x02
#define TOUCHPAD5_TOUCH_STATUS                  0x01
#define TOUCHPAD5_SNAP_STATUS                   0x05


/*! @} */ // sel_status

/**
 * @addtogroup id_tag
 * @{
 */

/**
 * @brief TouchPad 5 ID tag selection.
 * @details Specified ID tag of TouchPad 5 Click driver.
 */
#define TOUCHPAD5_ID_TAG_TOUCH_1                0x01
#define TOUCHPAD5_ID_TAG_TOUCH_2                0x02
#define TOUCHPAD5_ID_TAG_TOUCH_3                0x03
#define TOUCHPAD5_ID_TAG_TOUCH_4                0x04
#define TOUCHPAD5_ID_TAG_TOUCH_5                0x05
#define TOUCHPAD5_ID_TAG_HOVER_1                0x81
#define TOUCHPAD5_ID_TAG_HOVER_2                0x82
#define TOUCHPAD5_ID_TAG_HOVER_3                0x83
#define TOUCHPAD5_ID_TAG_HOVER_4                0x84
#define TOUCHPAD5_ID_TAG_HOVER_5                0x85

/*! @} */ // id_tag


/**
 * @defgroup touchpad5_map Touchpad 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Touchpad 5 Click driver.
 */

/**
 * @addtogroup touchpad5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Touchpad 5 Click to the selected MikroBUS.
 */
#define TOUCHPAD5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.nrst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // touchpad5_map

/**
 * @addtogroup product_num
 * @{
 */

/**
 * @brief TouchPad 2 Product Number selection.
 * @details Specified Product Number of TouchPad 2 Click driver.
 */
#define TOUCHPAD5_IQS550_PRODUCT_NUMBER         40


/*! @} */ // product_num
/*! @} */ // touchpad5

/**
 * @brief Touchpad 5 Click context object.
 * @details Context object definition of Touchpad 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  nrst;           /**< Active low reset pin. */

    // Input pins
    digital_in_t  int_pin;         /**< Interrupt RDY pin. */

    // Modules
    i2c_master_t i2c;              /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;         /**< Device slave address (used for I2C driver). */

} touchpad5_t;

/**
 * @brief Touchpad 5 Click configuration object.
 * @details Configuration object definition of Touchpad 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;               /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;               /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  nrst;              /**< Reset pin. */
    pin_name_t  int_pin;           /**< Interrupt pin. */

    uint32_t  i2c_speed;           /**< I2C serial speed. */
    uint8_t   i2c_address;         /**< I2C slave address. */

} touchpad5_cfg_t;

/**
 * @brief TouchPad 5 device version information object.
 * @details Device version information object definition of TouchPad 5 Click driver.
 */
typedef struct
{
    uint16_t  product_num;         /**< Product Number. */
    uint16_t  project_num;         /**< Project Number. */
    float version;                 /**< Major Release / Minor Release. */
    uint16_t hw_id;                /**< Hardware ID. */
    uint16_t hw_revision;          /**< Hardware Revision. */
} touchpad5_ver_info_t;

/**
 * @brief TouchPad 5 XY data object.
 * @details XY data object definition of TouchPad 5 Click driver.
 */
typedef struct
{
    uint8_t   xy_info;             /**< Status bytes, and indicates the total number of active co-ordinates. */
    uint8_t   no_of_fingers;       /**< Number of touches + hovers. */
    uint8_t   id_tag;              /**< Identify a specific co-ordinate. */
    uint16_t  x_pos;               /**< X Position. */
    uint16_t  y_pos;               /**< Y Position. */
    uint16_t  touch_strength;      /**< Touch Strength – indicates the „hardness‟ of this touch. */

} touchpad5_touch_t;

/**
 * @brief TouchPad 5 Channel Setup object.
 * @details Channel Setup object definition of TouchPad 5 Click driver.
 */
typedef struct
{
    uint8_t   total_rx;            /**< Total amount of Rx channels used. */
    uint8_t   total_tx;            /**< Total amount of Tx channels used. */
    uint8_t   track_pad_rx;        /**< Total amount of Rx channels used for XY trackpad purposes. */
    uint8_t   track_pad_tx;        /**< Total amount of Tx channels used for XY trackpad purposes. */
    uint8_t   pm_setup;            /**< ProxMode settings, and Rx configuration. */
    uint16_t  tx_config;           /**< ProxMode Tx configuration high byte. */

} touchpad5_channel_setup_t;

/**
 * @brief TouchPad 5 Threshold Settings object.
 * @details Threshold Settings object definition of TouchPad 5 Click driver.
 */
typedef struct
{
    uint8_t   prox_thresh;         /**< Delta value used for proximity threshold (applied to trackpad channels). */
    uint8_t   touch_thresh_mult;   /**< Touch treshold multiplier (applied to trackpad channels). */
    uint8_t   touch_thresh_shift;  /**< Touch threshold shifter (applied to trackpad channels). */
    uint8_t   pm_prox_thresh;      /**< Delta value used for proximity threshold of ProxMode channels. */
    uint8_t   snap_thresh_high;    /**< Higher byte of delta value below LTA. */
    uint8_t   snap_thresh_low;     /**< Lower byte of delta value below LTA. */
    uint8_t   prox_thresh2;        /**< Delta value used for proximity threshold (applied to non-trackpad channels). */
    uint8_t   touch_thresh_mult2;  /**< Touch treshold multiplier (applied to non-trackpad channels). */
    uint8_t   touch_thresh_shift2; /**< Touch threshold shifter (applied to non-trackpad channels). */

} touchpad5_threshold_settings_t;

/**
 * @brief TouchPad 5 Control Settings object.
 * @details Control Settings object definition of TouchPad 5 Click driver.
 */
typedef struct
{
    uint8_t   ctrl_settings0;      /**< First Control byte address command. */
    uint8_t   ctrl_settings1;      /**< Second Control byte address command. */

} touchpad5_control_settings_t;

/**
 * @brief Touchpad 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TOUCHPAD5_OK = 0,
    TOUCHPAD5_ERROR = -1

} touchpad5_return_value_t;

/*!
 * @addtogroup touchpad5 Touchpad 5 Click Driver
 * @brief API for configuring and manipulating Touchpad 5 Click driver.
 * @{
 */

/**
 * @brief Touchpad 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #touchpad5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void touchpad5_cfg_setup( touchpad5_cfg_t *cfg );

/**
 * @brief Touchpad 5 reset function.
 * @details This function toggles the NRST pin thus resetting the IQS550 device. 
 * @param[out] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void touchpad5_reset( touchpad5_t *ctx );

/**
 * @brief Touchpad 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #touchpad5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_init( touchpad5_t *ctx, touchpad5_cfg_t *cfg );

/**
 * @brief Touchpad 5 default configuration function.
 * @details This function executes a default configuration of Touchpad 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t touchpad5_default_cfg( touchpad5_t *ctx );

/**
 * @brief Touchpad 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_generic_write( touchpad5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Touchpad 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_generic_read( touchpad5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );


/**
 * @brief TouchPad 5 Check Version function.
 * @details This function check  device version information
 * of the IQS550 Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[out] ver_info : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_check_version( touchpad5_t *ctx, touchpad5_ver_info_t *ver_info );

/**
 * @brief TouchPad 5 Check Bootloader Status.
 * @details This function check the bootloader status
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[out] rx_buf : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Output read data returns 0xA5 if the bootloader is present, 0xEE otherwise.
 */
err_t touchpad5_check_bl_status( touchpad5_t *ctx, uint8_t* rx_buf );

/**
 * @brief TouchPad 5 check interrupt function.
 * @details This function check the interrupt state, the state of the INT pin 
 * of the IQS550 Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,
 *         @li @c 1 - INT pin state high.
 *
 * @note None.
 */
uint8_t touchpad5_check_interrupt( touchpad5_t *ctx );

/**
 * @brief TouchPad 5 wait ready function.
 * @details This function waits for the communication window to be available
 * of the IQS550 Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void touchpad5_wait_ready( touchpad5_t *ctx );

/**
 * @brief TouchPad 5 channel setup function.
 * @details This function channel setup used for trackpad ( XY information ) purposes, 
 * as well as the total Rx and Tx‟s used can be selected
 * of the IQS550 Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[in] ch_setup : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_channel_setup( touchpad5_t *ctx, touchpad5_channel_setup_t ch_setup );

/**
 * @brief TouchPad 5 threshold setup function.
 * @details This function sets the threshold levels used for touch panel channels and ProxMode 
 * channels of the IQS550 Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[in] thresh_setup : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_threshold_setup( touchpad5_t *ctx, touchpad5_threshold_settings_t thresh_setup );


/**
 * @brief TouchPad 5 control setup function.
 * @details This function sets the control commands of the IQS550 
 * Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[in] ctrl_setup : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_control_setup( touchpad5_t *ctx, touchpad5_control_settings_t ctrl_setup );


/**
 * @brief TouchPad 5 get touch function.
 * @details This function get touch data, XY data consists of the status byte and
 * the following repeated sets of data bytes, relative to the number of multi-touch points used
 * of the IQS550 Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[out] touch_data : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_get_touch( touchpad5_t *ctx, touchpad5_touch_t *touch_data );

/**
 * @brief TouchPad 5 get all data function.
 * @details This function get all data, XY data consists of the status byte and
 * the following repeated sets of data bytes, relative to the number of multi-touch points used
 * of the IQS550 Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The XY data consists of the status byte and the following repeated sets of data bytes,
 * relative to the number of multi-touch points used. 
 * Currently 5 points are implemented, and thus a total of (7x5 + 1) 36 bytes are available 
 * to be read in XY Data Read mode.
 */
err_t touchpad5_get_all_data( touchpad5_t *ctx, uint8_t *rx_data );

/**
 * @brief TouchPad 5 get status function.
 * @details This function get status proximity, touch or snap data
 * of the IQS550 Multiple Channel Projected Capacitive Controller, with Proximity, Touch and Snap
 * on the TouchPad 5 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[in] sel_status : 
 *         @li @c 0x02 ( TOUCHPAD5_PROXIMITY_STATUS ) - Proximity Status,
 *         @li @c 0x01 ( TOUCHPAD5_TOUCH_STATUS )     - Touch Status,
 *         @li @c 0x08 ( TOUCHPAD5_SNAP_STATUS )      - Snap Status.
 * @param[in] num_of_samples : Number of samples needed.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad5_get_status( touchpad5_t *ctx, uint8_t sel_status, uint16_t *rx_data, uint8_t num_of_samples );

#ifdef __cplusplus
}
#endif
#endif // TOUCHPAD5_H

/*! @} */ // touchpad5

// ------------------------------------------------------------------------ END
