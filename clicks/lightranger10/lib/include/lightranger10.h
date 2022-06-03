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
 * @file lightranger10.h
 * @brief This file contains API for LightRanger 10 Click Driver.
 */

#ifndef LIGHTRANGER10_H
#define LIGHTRANGER10_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup lightranger10 LightRanger 10 Click Driver
 * @brief API for configuring and manipulating LightRanger 10 Click driver.
 * @{
 */

/**
 * @defgroup lightranger10_reg LightRanger 10 Registers List
 * @brief List of registers of LightRanger 10 Click driver.
 */

/**
 * @addtogroup lightranger10_reg
 * @{
 */

/**
 * @brief LightRanger 10 register list.
 * @details Specified register list of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_REG_SOFT_RESET                    0x0000
#define LIGHTRANGER10_REG_ALGO_PTP_RANGE_OFFSET_MM      0x001E
#define LIGHTRANGER10_REG_MM_CFG_INNER_OFFSET_MM        0x0020
#define LIGHTRANGER10_REG_MM_CFG_OUTER_OFFSET_MM        0x0022
#define LIGHTRANGER10_REG_RANGE_CFG_VCSEL_PERIOD_A      0x0060
#define LIGHTRANGER10_REG_RANGE_CFG_VCSEL_PERIOD_B      0x0063
#define LIGHTRANGER10_REG_RANGE_CFG_VALID_PHASE_HIGH    0x0069
#define LIGHTRANGER10_REG_SD_CFG_WOI_SD0                0x0078
#define LIGHTRANGER10_REG_SD_CFG_WOI_SD1                0x0079
#define LIGHTRANGER10_REG_SD_CFG_INIT_PHASE_SD0         0x007A
#define LIGHTRANGER10_REG_SD_CFG_INIT_PHASE_SD1         0x007B
#define LIGHTRANGER10_REG_SYSTEM_INT_MEAS_PERIOD        0x006C
#define LIGHTRANGER10_REG_SYSTEM_INTERRUPT_CLEAR        0x0086
#define LIGHTRANGER10_REG_SYSTEM_MODE_START             0x0087
#define LIGHTRANGER10_REG_RESULT_RANGE_MM_SD0           0x0096
#define LIGHTRANGER10_REG_RESULT_OSC_CALIBRATE_VAL      0x00DE
#define LIGHTRANGER10_REG_MODEL_ID                      0x010F
#define LIGHTRANGER10_REG_MODEL_TYPE                    0x0110

/*! @} */ // lightranger10_reg

/**
 * @defgroup lightranger10_set LightRanger 10 Registers Settings
 * @brief Settings for registers of LightRanger 10 Click driver.
 */

/**
 * @addtogroup lightranger10_set
 * @{
 */

/**
 * @brief LightRanger 10 soft reset settings.
 * @details Specified soft reset settings of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_SOFT_RESET_SET                    0x00
#define LIGHTRANGER10_SOFT_RESET_CLEAR                  0x01

/**
 * @brief LightRanger 10 interrupt clear settings.
 * @details Specified interrupt clear settings of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_INTERRUPT_CLEAR                   0x01

/**
 * @brief LightRanger 10 ranging enable values.
 * @details Specified ranging enable values of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_RANGING_ENABLE                    0x40
#define LIGHTRANGER10_RANGING_DISABLE                   0x00

/**
 * @brief LightRanger 10 distance mode values.
 * @details Specified distance mode values of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_DISTANCE_MODE_MEDIUM              0x00
#define LIGHTRANGER10_DISTANCE_MODE_LONG                0x01

/**
 * @brief LightRanger 10 distance config values.
 * @details Specified distance config values of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_DISTANCE_MEDIUM_RANGE_PERIOD_A    0x0B
#define LIGHTRANGER10_DISTANCE_MEDIUM_RANGE_PERIOD_B    0x09
#define LIGHTRANGER10_DISTANCE_MEDIUM_RANGE_VAL_PH_H    0x78
#define LIGHTRANGER10_DISTANCE_MEDIUM_SD_WOI_SD0        0x0B
#define LIGHTRANGER10_DISTANCE_MEDIUM_SD_WOI_SD1        0x09
#define LIGHTRANGER10_DISTANCE_MEDIUM_SD_IN_PH_SD0      0x0A
#define LIGHTRANGER10_DISTANCE_MEDIUM_SD_IN_PH_SD1      0x0A
#define LIGHTRANGER10_DISTANCE_LONG_RANGE_PERIOD_A      0x0F
#define LIGHTRANGER10_DISTANCE_LONG_RANGE_PERIOD_B      0x0D
#define LIGHTRANGER10_DISTANCE_LONG_RANGE_VAL_PH_H      0xB8
#define LIGHTRANGER10_DISTANCE_LONG_SD_WOI_SD0          0x0F
#define LIGHTRANGER10_DISTANCE_LONG_SD_WOI_SD1          0x0D
#define LIGHTRANGER10_DISTANCE_LONG_SD_IN_PH_SD0        0x0E
#define LIGHTRANGER10_DISTANCE_LONG_SD_IN_PH_SD1        0x0E

/**
 * @brief LightRanger 10 distance offset calculation settings.
 * @details Specified distance offset calculation settings of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_ALGO_PTP_RANGE_OFFSET_MM_MULT     4
#define LIGHTRANGER10_ALGO_PTP_RANGE_OFFSET_MM_RESET    0
#define LIGHTRANGER10_MM_CFG_INNER_OFFSET_MM_RESET      0
#define LIGHTRANGER10_MM_CFG_OUTER_OFFSET_MM_RESET      0
#define LIGHTRANGER10_CALIBRATE_DISTANCE_AVERAGE_NUM    20

/**
 * @brief LightRanger 10 intermeasurement period settings.
 * @details Specified intermeasurement period settings of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_DEFAULT_IM_PERIOD_MS              200
#define LIGHTRANGER10_OSC_CALIB_IM_PERIOD_OFFSET        4

/**
 * @brief LightRanger 10 model ID and type values.
 * @details Specified model ID and type values of LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_MODEL_ID                          0xEB
#define LIGHTRANGER10_MODEL_TYPE                        0xAA

/**
 * @brief LightRanger 10 device address setting.
 * @details Specified setting for device slave address selection of
 * LightRanger 10 Click driver.
 */
#define LIGHTRANGER10_DEVICE_ADDRESS                    0x29

/*! @} */ // lightranger10_set

/**
 * @defgroup lightranger10_map LightRanger 10 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 10 Click driver.
 */

/**
 * @addtogroup lightranger10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 10 Click to the selected MikroBUS.
 */
#define LIGHTRANGER10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightranger10_map
/*! @} */ // lightranger10

/**
 * @brief LightRanger 10 Click context object.
 * @details Context object definition of LightRanger 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin, active high. */

    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin, active low. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} lightranger10_t;

/**
 * @brief LightRanger 10 Click configuration object.
 * @details Configuration object definition of LightRanger 10 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;             /**< Enable pin, active high. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} lightranger10_cfg_t;

/**
 * @brief LightRanger 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHTRANGER10_OK = 0,
    LIGHTRANGER10_ERROR = -1

} lightranger10_return_value_t;

/*!
 * @addtogroup lightranger10 LightRanger 10 Click Driver
 * @brief API for configuring and manipulating LightRanger 10 Click driver.
 * @{
 */

/**
 * @brief LightRanger 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightranger10_cfg_setup ( lightranger10_cfg_t *cfg );

/**
 * @brief LightRanger 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_init ( lightranger10_t *ctx, lightranger10_cfg_t *cfg );

/**
 * @brief LightRanger 10 default configuration function.
 * @details This function executes a default configuration of LightRanger 10
 * click board.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lightranger10_default_cfg ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_generic_write ( lightranger10_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LightRanger 10 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_generic_read ( lightranger10_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LightRanger 10 write byte function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_write_byte ( lightranger10_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief LightRanger 10 read byte function.
 * @details This function reads data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_read_byte ( lightranger10_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief LightRanger 10 write word function.
 * @details This function writes a data word (two bytes) 
 * starting from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_write_word ( lightranger10_t *ctx, uint16_t reg, uint16_t data_in );

/**
 * @brief LightRanger 10 read word function.
 * @details This function reads data word (two bytes) 
 * starting from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_read_word ( lightranger10_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief LightRanger 10 write dword function.
 * @details This function writes a double word of data (four bytes) 
 * starting from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_write_dword ( lightranger10_t *ctx, uint16_t reg, uint32_t data_in );

/**
 * @brief LightRanger 10 read dword function.
 * @details This function reads double word of data (four bytes) 
 * starting from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_read_dword ( lightranger10_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief LightRanger 10 check communication function.
 * @details This function checks the communication by reading and verifying the model ID and type.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_check_communication ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lightranger10_get_int_pin ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 enable device function.
 * @details This function enables the device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger10_enable_device ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 disable device function.
 * @details This function disables the device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger10_disable_device ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 reset device function.
 * @details This function resets the device by toggling the EN pin.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger10_reset_device ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 soft reset function.
 * @details This function performs the software reset through the soft reset register.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_soft_reset ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 clear interrupts function.
 * @details This function clears the interrupts.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_clear_interrupts ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 set inter measurement period ms function.
 * @details This function sets the inter-measurement period in milliseconds.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] period_ms : Inter-measurement period in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_set_inter_measurement_period_ms ( lightranger10_t *ctx, uint32_t period_ms );

/**
 * @brief LightRanger 10 set distance offset function.
 * @details This function sets distance offset in millimeters.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] offset_mm : Distance offset in millimeters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_set_distance_offset ( lightranger10_t *ctx, int16_t offset_mm );

/**
 * @brief LightRanger 10 calibrate distance function.
 * @details This function calibrates the distance offset to the selected target distance.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] target_distance_mm : Target distance in millimeters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_calibrate_distance ( lightranger10_t *ctx, uint16_t target_distance_mm );

/**
 * @brief LightRanger 10 set distance mode function.
 * @details This function sets the distance mode to medium or long distance.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[in] distance_mode : @li @c 0 - MEDIUM,
 *                            @li @c 1 - LONG.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_set_distance_mode ( lightranger10_t *ctx, uint8_t distance_mode );

/**
 * @brief LightRanger 10 start measurement function.
 * @details This function starts the measurement by enabling ranging.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_start_measurement ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 stop measurement function.
 * @details This function stops the measurement by disabling ranging.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_stop_measurement ( lightranger10_t *ctx );

/**
 * @brief LightRanger 10 get distance function.
 * @details This function reads the target object distance in millimeters.
 * @param[in] ctx : Click context object.
 * See #lightranger10_t object definition for detailed explanation.
 * @param[out] distance_mm : Distance in millimeters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger10_get_distance ( lightranger10_t *ctx, uint16_t *distance_mm );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER10_H

/*! @} */ // lightranger10

// ------------------------------------------------------------------------ END
