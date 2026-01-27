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
 * @file hydrogen2.h
 * @brief This file contains API for Hydrogen 2 Click Driver.
 */

#ifndef HYDROGEN2_H
#define HYDROGEN2_H

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
 * @addtogroup hydrogen2 Hydrogen 2 Click Driver
 * @brief API for configuring and manipulating Hydrogen 2 Click driver.
 * @{
 */

/**
 * @defgroup hydrogen2_cmd Hydrogen 2 Commands List
 * @brief List of commands of Hydrogen 2 Click driver.
 */

/**
 * @addtogroup hydrogen2_cmd
 * @{
 */

/**
 * @brief Hydrogen 2 commands list.
 * @details Specified commands list of Hydrogen 2 Click driver.
 */
#define HYDROGEN2_CMD_TRIG_CONC_MEAS            0xA8
#define HYDROGEN2_CMD_TRIG_TEMP_MEAS            0xA9
#define HYDROGEN2_CMD_SET_CONFIG                0xC4
#define HYDROGEN2_CMD_STANDBY                   0xC3
#define HYDROGEN2_CMD_READ_ID                   0xC2

/*! @} */ // hydrogen2_cmd

/**
 * @defgroup hydrogen2_set Hydrogen 2 Registers Settings
 * @brief Settings for registers of Hydrogen 2 Click driver.
 */

/**
 * @addtogroup hydrogen2_set
 * @{
 */

/**
 * @brief Hydrogen 2 set config command setting.
 * @details Specified setting for set config command of Hydrogen 2 Click driver.
 */
#define HYDROGEN2_CFG_1_SPIKE_FILTER_DIS        0x00
#define HYDROGEN2_CFG_1_SPIKE_FILTER_EN         0x08
#define HYDROGEN2_CFG_1_SPIKE_FILTER_MASK       0x08
#define HYDROGEN2_CFG_1_PP2_WAKE_LOW            0x00
#define HYDROGEN2_CFG_1_PP2_WAKE_HIGH           0x04
#define HYDROGEN2_CFG_1_PP2_WAKE_MASK           0x04
#define HYDROGEN2_CFG_1_WAKE_MAP_PP2            0x00
#define HYDROGEN2_CFG_1_WAKE_MAP_PP1            0x02
#define HYDROGEN2_CFG_1_WAKE_MAP_MASK           0x02
#define HYDROGEN2_CFG_1_AUTO_STANDBY_DIS        0x00
#define HYDROGEN2_CFG_1_AUTO_STANDBY_EN         0x01
#define HYDROGEN2_CFG_1_AUTO_STANDBY_MASK       0x01
#define HYDROGEN2_CFG_2_BUSY_MAP_DIS            0x00
#define HYDROGEN2_CFG_2_BUSY_MAP_PP2            0x01
#define HYDROGEN2_CFG_2_BUSY_MAP_PP3            0x02
#define HYDROGEN2_CFG_2_BUSY_MAP_STDBY          0x03
#define HYDROGEN2_CFG_2_BUSY_MAP_MASK           0x03
#define HYDROGEN2_CFG_3_STANDBY_MAP_DIS         0x00
#define HYDROGEN2_CFG_3_STANDBY_MAP_PP2         0x01
#define HYDROGEN2_CFG_3_STANDBY_MAP_PP3         0x02
#define HYDROGEN2_CFG_3_STANDBY_MAP_STDBY       0x03
#define HYDROGEN2_CFG_3_STANDBY_MAP_MASK        0x03

/**
 * @brief Hydrogen 2 concentration measurement setting.
 * @details Specified setting for concentration measurement command of Hydrogen 2 Click driver.
 */
#define HYDROGEN2_CONC_CONFIG_RH_RES_1          0x00
#define HYDROGEN2_CONC_CONFIG_RH_RES_0_25       0x40
#define HYDROGEN2_CONC_CONFIG_RH_RES_0_5        0x80
#define HYDROGEN2_CONC_CONFIG_RH_RES_0_75       0xC0
#define HYDROGEN2_CONC_CONFIG_RH_RES_MASK       0xC0
#define HYDROGEN2_CONC_CONFIG_FIELD_CONT_DIS    0x00
#define HYDROGEN2_CONC_CONFIG_FIELD_CONT_EN     0x20
#define HYDROGEN2_CONC_CONFIG_FIELD_CONT_MASK   0x20
#define HYDROGEN2_CONC_CONFIG_EOL_CONT_DIS      0x00
#define HYDROGEN2_CONC_CONFIG_EOL_CONT_EN       0x10
#define HYDROGEN2_CONC_CONFIG_EOL_CONT_MASK     0x10
#define HYDROGEN2_CONC_CONFIG_MEMS_VREG_NO_BP   0x00
#define HYDROGEN2_CONC_CONFIG_MEMS_VREG_BP      0x08
#define HYDROGEN2_CONC_CONFIG_MEMS_VREG_MASK    0x08
#define HYDROGEN2_CONC_CONFIG_CALIB_SEL_H2      0x00
#define HYDROGEN2_CONC_CONFIG_CALIB_SEL_R32     0x04
#define HYDROGEN2_CONC_CONFIG_CALIB_SEL_MASK    0x04
#define HYDROGEN2_CONC_CONFIG_COMP_SEL_FULL     0x00
#define HYDROGEN2_CONC_CONFIG_COMP_SEL_T        0x01
#define HYDROGEN2_CONC_CONFIG_COMP_SEL_RHT      0x02
#define HYDROGEN2_CONC_CONFIG_COMP_SEL_RAW      0x03
#define HYDROGEN2_CONC_CONFIG_COMP_SEL_MASK     0x03
#define HYDROGEN2_CONC_RH_DEFAULT               50
#define HYDROGEN2_CONC_T_DEFAULT                25
#define HYDROGEN2_CONC_P_DEFAULT                100

/**
 * @brief Hydrogen 2 status setting.
 * @details Specified setting for status command of Hydrogen 2 Click driver.
 */
#define HYDROGEN2_STATUS_OK                     0x00
#define HYDROGEN2_STATUS_ADC_UNDERFLOW          0x01
#define HYDROGEN2_STATUS_ADC_OVERFLOW           0x02
#define HYDROGEN2_STATUS_IN_PARAM_OUT_OF_RANGE  0x04
#define HYDROGEN2_STATUS_MEMS_OR_CONT_FAIL      0x08
#define HYDROGEN2_STATUS_VDD_OUT_OF_RANGE       0x10
#define HYDROGEN2_STATUS_PREV_CMD_FAIL          0x20

/**
 * @brief Hydrogen 2 H2 calculation setting.
 * @details Specified setting for H2 calculation of Hydrogen 2 Click driver.
 */
#define HYDROGEN2_H2_RES                        0.01

/**
 * @brief Hydrogen 2 timeout setting.
 * @details Specified setting for timeout of Hydrogen 2 Click driver.
 */
#define HYDROGEN2_TIMEOUT_MS                    2000

/**
 * @brief Hydrogen 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Hydrogen 2 Click driver.
 */
#define HYDROGEN2_DEVICE_ADDRESS                0x36

/*! @} */ // hydrogen2_set

/**
 * @defgroup hydrogen2_map Hydrogen 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Hydrogen 2 Click driver.
 */

/**
 * @addtogroup hydrogen2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hydrogen 2 Click to the selected MikroBUS.
 */
#define HYDROGEN2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sby = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hydrogen2_map
/*! @} */ // hydrogen2

/**
 * @brief Hydrogen 2 Click device ID object.
 * @details Device ID object definition of Hydrogen 2 Click driver.
 */
typedef struct
{
    uint32_t sensor_id;         /**< 32-bit sensor ID. */
    uint16_t product_code;      /**< 16-bit product code. */ 
    uint16_t fw_rev_num;        /**< 16-bit firmware revision number. */
    uint8_t man_code;           /**< 8-bit manufacturer code. */

} hydrogen2_info_t;

/**
 * @brief Hydrogen 2 Click context object.
 * @details Context object definition of Hydrogen 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t sby;           /**< Device standby or device busy indication (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    hydrogen2_info_t info;      /**< Device info. */

} hydrogen2_t;

/**
 * @brief Hydrogen 2 Click configuration object.
 * @details Configuration object definition of Hydrogen 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t sby;             /**< Device standby or device busy indication (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} hydrogen2_cfg_t;

/**
 * @brief Hydrogen 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HYDROGEN2_OK = 0,
    HYDROGEN2_ERROR = -1

} hydrogen2_return_value_t;

/*!
 * @addtogroup hydrogen2 Hydrogen 2 Click Driver
 * @brief API for configuring and manipulating Hydrogen 2 Click driver.
 * @{
 */

/**
 * @brief Hydrogen 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hydrogen2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hydrogen2_cfg_setup ( hydrogen2_cfg_t *cfg );

/**
 * @brief Hydrogen 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hydrogen2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen2_init ( hydrogen2_t *ctx, hydrogen2_cfg_t *cfg );

/**
 * @brief Hydrogen 2 default configuration function.
 * @details This function executes a default configuration of Hydrogen 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hydrogen2_default_cfg ( hydrogen2_t *ctx );

/**
 * @brief Hydrogen 2 write command function.
 * @details This function writes a command with optional parameter bytes and appends
 * a CRC16-CCITT checksum before sending it over the I2C interface.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be written.
 * @param[in] param_in : Pointer to command parameters to be written (can be NULL).
 * @param[in] param_len : Number of parameter bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen2_write_cmd ( hydrogen2_t *ctx, uint8_t cmd, uint8_t *param_in, uint8_t param_len );

/**
 * @brief Hydrogen 2 read response function.
 * @details This function reads a response frame, validates the CRC16-CCITT checksum,
 * and returns the status byte and optional parameter bytes.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @param[out] status : Pointer to response status byte (can be NULL).
 * @param[out] param_out : Pointer to output parameter buffer (can be NULL).
 * @param[in] param_len : Number of parameter bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen2_read_response ( hydrogen2_t *ctx, uint8_t *status, uint8_t *param_out, uint8_t param_len );

/**
 * @brief Hydrogen 2 get standby pin state function.
 * @details This function reads the logic state of the SBY pin and returns its
 * current value.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @return Logic state of the SBY pin.
 * @note None.
 */
uint8_t hydrogen2_get_sby_pin ( hydrogen2_t *ctx );

/**
 * @brief Hydrogen 2 get concentration function.
 * @details This function triggers a hydrogen concentration measurement using
 * default environmental parameters, reads the response and returns the measured
 * concentration value.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @param[out] conc : Pointer to the measured concentration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen2_get_conc ( hydrogen2_t *ctx, int16_t *conc );

/**
 * @brief Hydrogen 2 get temperature function.
 * @details This function triggers a temperature measurement, reads the response
 * and returns the measured temperature value.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @param[out] temp : Pointer to the measured temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen2_get_temp ( hydrogen2_t *ctx, int8_t *temp );

/**
 * @brief Hydrogen 2 set configuration function.
 * @details This function writes the configuration bytes to the device and checks
 * the response status for successful configuration update.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @param[in] cfg_1 : Configuration byte 1.
 * @param[in] cfg_2 : Configuration byte 2.
 * @param[in] cfg_3 : Configuration byte 3.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen2_set_config ( hydrogen2_t *ctx, uint8_t cfg_1, uint8_t cfg_2, uint8_t cfg_3 );

/**
 * @brief Hydrogen 2 go standby function.
 * @details This function sends the standby command to place the device into
 * standby mode.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen2_go_standby ( hydrogen2_t *ctx );

/**
 * @brief Hydrogen 2 read identification function.
 * @details This function reads the device identification data and stores the
 * parsed information into the info structure inside the context object.
 * @param[in] ctx : Click context object.
 * See #hydrogen2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen2_read_id ( hydrogen2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HYDROGEN2_H

/*! @} */ // hydrogen2

// ------------------------------------------------------------------------ END
