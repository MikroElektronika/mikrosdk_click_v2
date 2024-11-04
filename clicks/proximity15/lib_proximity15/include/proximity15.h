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
 * @file proximity15.h
 * @brief This file contains API for Proximity 15 Click Driver.
 */

#ifndef PROXIMITY15_H
#define PROXIMITY15_H

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
 * @addtogroup proximity15 Proximity 15 Click Driver
 * @brief API for configuring and manipulating Proximity 15 Click driver.
 * @{
 */

/**
 * @defgroup proximity15_reg Proximity 15 Registers List
 * @brief List of registers of Proximity 15 Click driver.
 */

/**
 * @addtogroup proximity15_reg
 * @{
 */

/**
 * @brief Proximity 15 Reference registers.
 * @details Specified reference registers of Proximity 15 Click driver.
 */
#define PROXIMITY15_REG_SOFT_RESET              0x0000
#define PROXIMITY15_REG_PAD_I2C_HV_CFG          0x002D
#define PROXIMITY15_REG_CFG_TIMEOUT_MACROP      0x004B
#define PROXIMITY15_REG_CFG_TIMEOUT_MACROP_A_HI 0x005E
#define PROXIMITY15_REG_CFG_VCSEL_PERIOD_A      0x0060
#define PROXIMITY15_REG_CFG_TIMEOUT_MACROP_B_HI 0x0061
#define PROXIMITY15_REG_CFG_VCSEL_PERIOD_B      0x0063
#define PROXIMITY15_REG_CFG_VALID_PHASE_HIGH    0x0069
#define PROXIMITY15_REG_SYSTEM_INT_MEAS_PERIOD  0x006C
#define PROXIMITY15_REG_SD_CFG_WOI_SD0          0x0078
#define PROXIMITY15_REG_SD_CFG_INIT_PHASE_SD0   0x007A
#define PROXIMITY15_REG_SYSTEM_INTERRUPT_CLEAR  0x0086
#define PROXIMITY15_REG_SYSTEM_MODE_START       0x0087
#define PROXIMITY15_REG_RES_FINAL_RANGE_MM_SD0  0x0096
#define PROXIMITY15_REG_RES_OSC_CALIB_VAL       0x00DE
#define PROXIMITY15_REG_MODEL_ID                0x010F
#define PROXIMITY15_REG_MODULE_TYPE             0x0110

/*! @} */ // proximity15_reg

/**
 * @defgroup proximity15_set Proximity 15 Registers Settings
 * @brief Settings for registers of Proximity 15 Click driver.
 */

/**
 * @addtogroup proximity15_set
 * @{
 */

/**
 * @brief Proximity 15 Reference registers values.
 * @details Specified values for reference registers of Proximity 15 Click driver.
 */
#define PROXIMITY15_MODEL_ID                    0xEA
#define PROXIMITY15_MODULE_TYPE                 0xCC

/**
 * @brief Proximity 15 registers settings.
 * @details Specified values for registers setting of Proximity 15 Click driver.
 */
#define PROXIMITY15_SOFT_RESET_ENTER            0x00
#define PROXIMITY15_SOFT_RESET_EXIT             0x01
#define PROXIMITY15_START_RANGING               0x40
#define PROXIMITY15_STOP_RANGING                0x00
#define PROXIMITY15_CLEAR_INTERRUPT             0x01
#define PROXIMITY15_MEASURE_PERIOD_CONST        1.075
#define PROXIMITY15_TIMEOUT_MACROP_SHORT        0x14
#define PROXIMITY15_TIMEOUT_MACROP_LONG         0x0A
#define PROXIMITY15_DISTANCE_MODE_SHORT         0x01
#define PROXIMITY15_DISTANCE_MODE_LONG          0x02

/**
 * @brief Proximity 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 15 Click driver.
 */
#define PROXIMITY15_SET_DEV_ADDR                0x29

/*! @} */ // proximity15_set

/**
 * @defgroup proximity15_map Proximity 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 15 Click driver.
 */

/**
 * @addtogroup proximity15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 15 Click to the selected MikroBUS.
 */
#define PROXIMITY15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.xsh = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity15_map
/*! @} */ // proximity15

/**
 * @brief Proximity 15 Click context object.
 * @details Context object definition of Proximity 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  xsh;         /**< XSHUT pin. */

    // Input pins
    digital_in_t   int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t   i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} proximity15_t;

/**
 * @brief Proximity 15 Click configuration object.
 * @details Configuration object definition of Proximity 15 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  xsh;            /**< XSHUT pin. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} proximity15_cfg_t;

/**
 * @brief Proximity 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY15_OK = 0,
    PROXIMITY15_ERROR = -1

} proximity15_return_value_t;

/**
 * @brief Proximity 15 Click timing budget values.
 * @details Predefined enum values for timing budget.
 * @note 15MS is valid in short distance mode only.
 */
typedef enum
{
    PROXIMITY15_TIMING_BUDGET_15MS = 0,
    PROXIMITY15_TIMING_BUDGET_20MS,
    PROXIMITY15_TIMING_BUDGET_33MS,
    PROXIMITY15_TIMING_BUDGET_50MS,
    PROXIMITY15_TIMING_BUDGET_100MS,
    PROXIMITY15_TIMING_BUDGET_200MS,
    PROXIMITY15_TIMING_BUDGET_500MS

} proximity15_timing_budget_t;

/*!
 * @addtogroup proximity15 Proximity 15 Click Driver
 * @brief API for configuring and manipulating Proximity 15 Click driver.
 * @{
 */

/**
 * @brief Proximity 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity15_cfg_setup ( proximity15_cfg_t *cfg );

/**
 * @brief Proximity 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_init ( proximity15_t *ctx, proximity15_cfg_t *cfg );

/**
 * @brief Proximity 15 default configuration function.
 * @details This function executes a default configuration of Proximity 15
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity15_default_cfg ( proximity15_t *ctx );

/**
 * @brief Proximity 15 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_write_registers ( proximity15_t *ctx, uint16_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Proximity 15 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_read_registers ( proximity15_t *ctx, uint16_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Proximity 15 write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_write_register ( proximity15_t *ctx, uint16_t reg, uint8_t tx_data );

/**
 * @brief Proximity 15 read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_read_register ( proximity15_t *ctx, uint16_t reg, uint8_t *rx_data );

/**
 * @brief Proximity 15 check communication function.
 * @details This function checks the communication by reading and verifying the model ID and 
 * module type registers.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_check_communication ( proximity15_t *ctx );

/**
 * @brief Proximity 15 software reset function.
 * @details This function performs the device software reset.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_software_reset ( proximity15_t *ctx );

/**
 * @brief Proximity 15 get distance function.
 * @details This function waits for the data ready, then reads the distance measured by the sensor 
 * in milimeters and clears interrupts.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[out] distance : Object distance in milimeters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_get_distance ( proximity15_t *ctx, uint16_t *distance );

/**
 * @brief Proximity 15 enable sensor function.
 * @details This function enables the sensor by setting XSH pin to HIGH logic level.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity15_enable_sensor ( proximity15_t *ctx );

/**
 * @brief Proximity 15 disable sensor function.
 * @details This function disables the sensor by setting XSH pin to LOW logic level.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proximity15_disable_sensor ( proximity15_t *ctx );

/**
 * @brief Proximity 15 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t proximity15_get_int_pin ( proximity15_t *ctx );

/**
 * @brief Proximity 15 start ranging function.
 * @details This function starts the ranging distance operation.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The ranging operation is continuous. The clear interrupt has to be done after each get data 
 * to allow the interrupt to raise when the next data is ready.
 */
err_t proximity15_start_ranging ( proximity15_t *ctx );

/**
 * @brief Proximity 15 stop ranging function.
 * @details This function stops the ranging distance operation.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_stop_ranging ( proximity15_t *ctx );

/**
 * @brief Proximity 15 clear interrupt function.
 * @details This function clears the interrupt.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Call this function after a ranging data reading to arm the interrupt for the next data ready event.
 */
err_t proximity15_clear_interrupt ( proximity15_t *ctx );

/**
 * @brief Proximity 15 set inter measurement period function.
 * @details This function programs the inter measurement period in miliseconds.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[in] time_ms : Inter measurement period in miliseconds ( Default: 100ms ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Inter measurement period must be >= timing budget value. By default the timing budget is set to 50ms.
 */
err_t proximity15_set_inter_measurement_period ( proximity15_t *ctx, uint16_t time_ms );

/**
 * @brief Proximity 15 set distance mode function.
 * @details This function programs the distance mode.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[in] mode : @li @c  1 - Short mode,
 *                   @li @c  2 - Long mode ( Default ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Short mode can range up to 2 meters, while long mode ranges up to 6 meters when
 * the timing budget and inter measurement are set to more than 200ms.
 */
err_t proximity15_set_distance_mode ( proximity15_t *ctx, uint8_t mode );

/**
 * @brief Proximity 15 get distance mode function.
 * @details This function returns the current distance mode.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[out] mode : @li @c  1 - Short mode,
 *                    @li @c  2 - Long mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_get_distance_mode ( proximity15_t *ctx, uint8_t *mode );

/**
 * @brief Proximity 15 set timing budget function.
 * @details This function programs the timing budget in miliseconds.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[in] time : Time value (enum 0-6).
 * See proximity15_timing_budget_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_set_timing_budget ( proximity15_t *ctx, proximity15_timing_budget_t time );

/**
 * @brief Proximity 15 get timing budget function.
 * @details This function returns the current timing budget in miliseconds.
 * @param[in] ctx : Click context object.
 * See #proximity15_t object definition for detailed explanation.
 * @param[out] time : Time value (enum 0-6).
 * See proximity15_timing_budget_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity15_get_timing_budget ( proximity15_t *ctx, proximity15_timing_budget_t *time );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY15_H

/*! @} */ // proximity15

// ------------------------------------------------------------------------ END
