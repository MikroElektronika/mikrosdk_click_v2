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
 * @file battmon5.h
 * @brief This file contains API for BATT-MON 5 Click Driver.
 */

#ifndef BATTMON5_H
#define BATTMON5_H

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
 * @addtogroup battmon5 BATT-MON 5 Click Driver
 * @brief API for configuring and manipulating BATT-MON 5 Click driver.
 * @{
 */

/**
 * @defgroup battmon5_reg BATT-MON 5 Registers List
 * @brief List of registers of BATT-MON 5 Click driver.
 */

/**
 * @addtogroup battmon5_reg
 * @{
 */

/**
 * @brief BATT-MON 5 register map.
 * @details Specified register map of BATT-MON 5 Click driver.
 */
#define BATTMON5_REG_BEFORE_RSOC        0x04
#define BATTMON5_REG_TSENSE_THERM_B     0x06
#define BATTMON5_REG_INITIAL_RSOC       0x07
#define BATTMON5_REG_CELL_TEMP          0x08
#define BATTMON5_REG_CELL_V             0x09
#define BATTMON5_REG_CURRENT_DIR        0x0A
#define BATTMON5_REG_APA                0x0B
#define BATTMON5_REG_APT                0x0C
#define BATTMON5_REG_RSOC               0x0D
#define BATTMON5_REG_ITE                0x0F
#define BATTMON5_REG_IC_VERSION         0x11
#define BATTMON5_REG_CHANGE_PARAM       0x12
#define BATTMON5_REG_ALARM_LOW_RSOC     0x13
#define BATTMON5_REG_ALARM_LOW_CELL_V   0x14
#define BATTMON5_REG_IC_POWER_MODE      0x15
#define BATTMON5_REG_STATUS             0x16
#define BATTMON5_REG_BATT_STATUS        0x19
#define BATTMON5_REG_NUM_PARAM          0x1A
#define BATTMON5_REG_TERM_CURRENT       0x1C
#define BATTMON5_REG_EMPTY_CELL_V       0x1D
#define BATTMON5_REG_ITE_OFFSET         0x1E

/*! @} */ // battmon5_reg

/**
 * @defgroup battmon5_set BATT-MON 5 Registers Settings
 * @brief Settings for registers of BATT-MON 5 Click driver.
 */

/**
 * @addtogroup battmon5_set
 * @{
 */

/**
 * @brief BATT-MON 5 APA register setting.
 * @details Specified setting for APA register of BATT-MON 5 Click driver.
 */
#define BATTMON5_APA_50MAH              0x1313
#define BATTMON5_APA_100MAH             0x1515
#define BATTMON5_APA_200MAH             0x1818
#define BATTMON5_APA_500MAH             0x2121
#define BATTMON5_APA_1000MAH            0x2D2D
#define BATTMON5_APA_2000MAH            0x3A3A
#define BATTMON5_APA_3000MAH            0x3F3F
#define BATTMON5_APA_4000MAH            0x4242
#define BATTMON5_APA_5000MAH            0x4444
#define BATTMON5_APA_6000MAH            0x4545

/**
 * @brief BATT-MON 5 CHANGE_PARAM register setting.
 * @details Specified setting for CHANGE_PARAM register of BATT-MON 5 Click driver.
 */
#define BATTMON5_CHANGE_PARAM_3_7_V     0x0000
#define BATTMON5_CHANGE_PARAM_PANASONIC 0x0001
#define BATTMON5_CHANGE_PARAM_SAMSUNG   0x0002
#define BATTMON5_CHANGE_PARAM_3_8_V     0x0003
#define BATTMON5_CHANGE_PARAM_3_85_V    0x0004

/**
 * @brief BATT-MON 5 IC_POWER_MODE register setting.
 * @details Specified setting for IC_POWER_MODE register of BATT-MON 5 Click driver.
 */
#define BATTMON5_IC_POWER_MODE_NORMAL   0x0001
#define BATTMON5_IC_POWER_MODE_SLEEP    0x0002

/**
 * @brief BATT-MON 5 BATT_STATUS register setting.
 * @details Specified setting for BATT_STATUS register of BATT-MON 5 Click driver.
 */
#define BATTMON5_BATT_STATUS_CLEAR      0x0000
#define BATTMON5_BATT_STATUS_LOW_CELL_V 0x0800
#define BATTMON5_BATT_STATUS_LOW_RSOC   0x0200
#define BATTMON5_BATT_STATUS_INIT       0x0080

/**
 * @brief BATT-MON 5 device address setting.
 * @details Specified setting for device slave address selection of
 * BATT-MON 5 Click driver.
 */
#define BATTMON5_DEVICE_ADDRESS         0x0B

/*! @} */ // battmon5_set

/**
 * @defgroup battmon5_map BATT-MON 5 MikroBUS Map
 * @brief MikroBUS pin mapping of BATT-MON 5 Click driver.
 */

/**
 * @addtogroup battmon5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BATT-MON 5 Click to the selected MikroBUS.
 */
#define BATTMON5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alarm = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // battmon5_map
/*! @} */ // battmon5

/**
 * @brief BATT-MON 5 Click context object.
 * @details Context object definition of BATT-MON 5 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alarm;         /**< Alarm pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} battmon5_t;

/**
 * @brief BATT-MON 5 Click configuration object.
 * @details Configuration object definition of BATT-MON 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alarm;           /**< Alarm pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} battmon5_cfg_t;

/**
 * @brief BATT-MON 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BATTMON5_OK = 0,
    BATTMON5_ERROR = -1

} battmon5_return_value_t;

/*!
 * @addtogroup battmon5 BATT-MON 5 Click Driver
 * @brief API for configuring and manipulating BATT-MON 5 Click driver.
 * @{
 */

/**
 * @brief BATT-MON 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #battmon5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void battmon5_cfg_setup ( battmon5_cfg_t *cfg );

/**
 * @brief BATT-MON 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #battmon5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #battmon5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon5_init ( battmon5_t *ctx, battmon5_cfg_t *cfg );

/**
 * @brief BATT-MON 5 default configuration function.
 * @details This function executes a default configuration of BATT-MON 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #battmon5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t battmon5_default_cfg ( battmon5_t *ctx );

/**
 * @brief BATT-MON 5 write reg function.
 * @details This function writes a data word starting to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon5_write_reg ( battmon5_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief BATT-MON 5 read reg function.
 * @details This function reads a data word from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon5_read_reg ( battmon5_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief BATT-MON 5 get alarm pin function.
 * @details This function returns the ALARM pin logic state.
 * @param[in] ctx : Click context object.
 * See #battmon5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t battmon5_get_alarm_pin ( battmon5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BATTMON5_H

/*! @} */ // battmon5

// ------------------------------------------------------------------------ END
