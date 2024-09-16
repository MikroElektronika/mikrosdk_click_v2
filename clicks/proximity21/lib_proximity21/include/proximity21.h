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
 * @file proximity21.h
 * @brief This file contains API for Proximity 21 Click Driver.
 */

#ifndef PROXIMITY21_H
#define PROXIMITY21_H

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
 * @addtogroup proximity21 Proximity 21 Click Driver
 * @brief API for configuring and manipulating Proximity 21 Click driver.
 * @{
 */

/**
 * @defgroup proximity21_reg Proximity 21 Registers List
 * @brief List of registers of Proximity 21 Click driver.
 */

/**
 * @addtogroup proximity21_reg
 * @{
 */

/**
 * @brief Proximity 21 register list.
 * @details Specified register list of Proximity 21 Click driver.
 */
#define PROXIMITY21_REG_I2C_SLAVE_ADDRESS                       0x0001
#define PROXIMITY21_REG_VHV_CONFIG_TIMEOUT                      0x0008
#define PROXIMITY21_REG_XTALK_PLANE_OFFSET_KCPS                 0x0016
#define PROXIMITY21_REG_XTALK_X_PLANE_GRADIENT_KCPS             0x0018
#define PROXIMITY21_REG_XTALK_Y_PLANE_GRADIENT_KCPS             0x001A
#define PROXIMITY21_REG_RANGE_OFFSET_MM                         0x001E
#define PROXIMITY21_REG_INNER_OFFSET_MM                         0x0020
#define PROXIMITY21_REG_OUTER_OFFSET_MM                         0x0022
#define PROXIMITY21_REG_GPIO_HV_MUX_CTRL                        0x0030
#define PROXIMITY21_REG_GPIO_TIO_HV_STATUS                      0x0031
#define PROXIMITY21_REG_SYSTEM_INTERRUPT                        0x0046
#define PROXIMITY21_REG_RANGE_CONFIG_A                          0x005E
#define PROXIMITY21_REG_RANGE_CONFIG_B                          0x0061
#define PROXIMITY21_REG_RANGE_CONFIG_SIGMA_THRESH               0x0064
#define PROXIMITY21_REG_MIN_COUNT_RATE_RTN_LIMIT_MCPS           0x0066
#define PROXIMITY21_REG_INTERMEASUREMENT_MS                     0x006C
#define PROXIMITY21_REG_THRESH_HIGH                             0x0072
#define PROXIMITY21_REG_THRESH_LOW                              0x0074
#define PROXIMITY21_REG_SYSTEM_INTERRUPT_CLEAR                  0x0086
#define PROXIMITY21_REG_SYSTEM_START                            0x0087
#define PROXIMITY21_REG_RESULT_RANGE_STATUS                     0x0089
#define PROXIMITY21_REG_RESULT_SPAD_NB                          0x008C
#define PROXIMITY21_REG_RESULT_SIGNAL_RATE                      0x008E
#define PROXIMITY21_REG_RESULT_AMBIENT_RATE                     0x0090
#define PROXIMITY21_REG_RESULT_SIGMA                            0x0092
#define PROXIMITY21_REG_RESULT_DISTANCE                         0x0096
#define PROXIMITY21_REG_RESULT_OSC_CALIBRATE_VAL                0x00DE
#define PROXIMITY21_REG_FIRMWARE_SYSTEM_STATUS                  0x00E5
#define PROXIMITY21_REG_MODEL_ID                                0x010F

/*! @} */ // proximity21_reg

/**
 * @defgroup proximity21_set Proximity 21 Registers Settings
 * @brief Settings for registers of Proximity 21 Click driver.
 */

/**
 * @addtogroup proximity21_set
 * @{
 */

/**
 * @brief Proximity 21 range status setting.
 * @details Specified setting for range status of Proximity 21 Click driver.
 */
#define PROXIMITY21_RANGE_STATUS_VALID                          0
#define PROXIMITY21_RANGE_STATUS_SIGMA_HIGH                     1
#define PROXIMITY21_RANGE_STATUS_SIGMA_LOW                      2
#define PROXIMITY21_RANGE_STATUS_DISTANCE_LOW                   3
#define PROXIMITY21_RANGE_STATUS_PHASE_LIMIT                    4
#define PROXIMITY21_RANGE_STATUS_HW_FAIL                        5
#define PROXIMITY21_RANGE_STATUS_WRAP_CHECK                     6
#define PROXIMITY21_RANGE_STATUS_PHASE_NO_MATCH                 7
#define PROXIMITY21_RANGE_STATUS_PROCESSING_FAIL                8
#define PROXIMITY21_RANGE_STATUS_CROSSTALK_FAIL                 9
#define PROXIMITY21_RANGE_STATUS_INTERRUPT_ERROR                10
#define PROXIMITY21_RANGE_STATUS_MERGED_TARGET                  11
#define PROXIMITY21_RANGE_STATUS_SIGNAL_TOO_LOW                 12
#define PROXIMITY21_RANGE_STATUS_ERROR                          255

/**
 * @brief Proximity 21 device ID setting.
 * @details Specified setting for device ID of Proximity 21 Click driver.
 */
#define PROXIMITY21_DEVICE_ID                                   0xECAA


/**
 * @brief Proximity 21 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 21 Click driver.
 */
#define PROXIMITY21_DEVICE_ADDRESS                              0x29

/*! @} */ // proximity21_set

/**
 * @defgroup proximity21_map Proximity 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 21 Click driver.
 */

/**
 * @addtogroup proximity21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 21 Click to the selected MikroBUS.
 */
#define PROXIMITY21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.xshut = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gpio1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity21_map
/*! @} */ // proximity21

/**
 * @brief Proximity 21 Click results data object.
 * @details Results data object definition of Proximity 21 Click driver.
 */
typedef struct
{
    /**< Status of measurements. If the status is equal to 0, the data are valid. */
    uint8_t range_status;
    /**< Measured distance in millimeters. */
    uint16_t distance_mm;
    /**< Ambient noise in kcps. */
    uint16_t ambient_rate_kcps;
    /**< Ambient noise in kcps/SPAD. */
    uint16_t ambient_per_spad_kcps;
    /**< Measured signal of the target in kcps. */
    uint16_t signal_rate_kcps;
    /**< Measured signal of the target in kcps/SPAD. */
    uint16_t signal_per_spad_kcps;
    /**< Number of SPADs enabled. */
    uint16_t number_of_spad;
    /**< Estimated measurements std deviation in mm. */
    uint16_t sigma_mm;

} proximity21_data_t;

/**
 * @brief Proximity 21 Click context object.
 * @details Context object definition of Proximity 21 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t xshut;    /**< Xshutdown pin (active low). */

    // Input pins
    digital_in_t gpio1;     /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} proximity21_t;

/**
 * @brief Proximity 21 Click configuration object.
 * @details Configuration object definition of Proximity 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t xshut;       /**< Xshutdown pin (active low). */
    pin_name_t gpio1;       /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} proximity21_cfg_t;

/**
 * @brief Proximity 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY21_OK = 0,
    PROXIMITY21_ERROR = -1

} proximity21_return_value_t;

/*!
 * @addtogroup proximity21 Proximity 21 Click Driver
 * @brief API for configuring and manipulating Proximity 21 Click driver.
 * @{
 */

/**
 * @brief Proximity 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity21_cfg_setup ( proximity21_cfg_t *cfg );

/**
 * @brief Proximity 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_init ( proximity21_t *ctx, proximity21_cfg_t *cfg );

/**
 * @brief Proximity 21 default configuration function.
 * @details This function executes a default configuration of Proximity 21
 * click board.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity21_default_cfg ( proximity21_t *ctx );

/**
 * @brief Proximity 21 reg write bytes function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_reg_write_bytes ( proximity21_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Proximity 21 reg read bytes function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_reg_read_bytes ( proximity21_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Proximity 21 reg write byte function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 8-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_reg_write_byte ( proximity21_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief Proximity 21 reg read byte function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 8-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_reg_read_byte ( proximity21_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief Proximity 21 reg write word function.
 * @details This function writes a data word starting from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_reg_write_word ( proximity21_t *ctx, uint16_t reg, uint16_t data_in );

/**
 * @brief Proximity 21 reg read word function.
 * @details This function reads a data word starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : 16-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_reg_read_word ( proximity21_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief Proximity 21 reg write dword function.
 * @details This function writes a data dword starting from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_reg_write_dword ( proximity21_t *ctx, uint16_t reg, uint32_t data_in );

/**
 * @brief Proximity 21 reg read dword function.
 * @details This function reads a data dword starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : 32-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_reg_read_dword ( proximity21_t *ctx, uint16_t reg, uint32_t *data_out );

/**
 * @brief Proximity 21 disable device function.
 * @details This function disables the device by setting the XSHUT pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity21_disable_device ( proximity21_t *ctx );

/**
 * @brief Proximity 21 enable device function.
 * @details This function enables the device by setting the XSHUT pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity21_enable_device ( proximity21_t *ctx );

/**
 * @brief Proximity 21 get GPIO1 pin function.
 * @details This function returns the GPIO1 (interrupt) pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity21_get_gpio1_pin ( proximity21_t *ctx );

/**
 * @brief Proximity 21 check comm function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_check_comm ( proximity21_t *ctx );

/**
 * @brief Proximity 21 set I2C address function.
 * @details This function sets a new 7-bit I2C address for the click sensor.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] address : 7-bit I2C address to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_set_i2c_address ( proximity21_t *ctx, uint8_t address );

/**
 * @brief Proximity 21 clear interrupt function.
 * @details This function clears the data ready interrupt.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_clear_interrupt ( proximity21_t *ctx );

/**
 * @brief Proximity 21 start ranging function.
 * @details This function starts a continuous ranging session.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_start_ranging ( proximity21_t *ctx );

/**
 * @brief Proximity 21 stop ranging function.
 * @details This function stops the ranging session.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_stop_ranging ( proximity21_t *ctx );

/**
 * @brief Proximity 21 set range timing function.
 * @details This function sets the VCSEL enabled time, and the time between two measurements.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] timing_budget_ms : VCSEL enabled time in milliseconds (10 to 200ms), default 50ms.
 * @param[in] inter_measurement_ms : The time between two measurements in milliseconds. If the value is equal to 0,
 * the time is defined by timing_budget_ms. Otherwise, it must be > timing_budget_ms, default 200ms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_set_range_timing ( proximity21_t *ctx, uint32_t timing_budget_ms, uint32_t inter_measurement_ms );

/**
 * @brief Proximity 21 get result function.
 * @details This function gets the results reported by the sensor.
 * @param[in] ctx : Click context object.
 * See #proximity21_t object definition for detailed explanation.
 * @param[in] results : Click context object.
 * See #proximity21_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity21_get_result ( proximity21_t *ctx, proximity21_data_t *results );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY21_H

/*! @} */ // proximity21

// ------------------------------------------------------------------------ END
