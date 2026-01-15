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
 * @file pir4.h
 * @brief This file contains API for PIR 4 Click Driver.
 */

#ifndef PIR4_H
#define PIR4_H

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
 * @addtogroup pir4 PIR 4 Click Driver
 * @brief API for configuring and manipulating PIR 4 Click driver.
 * @{
 */

/**
 * @defgroup pir4_reg PIR 4 Registers List
 * @brief List of registers of PIR 4 Click driver.
 */

/**
 * @addtogroup pir4_reg
 * @{
 */

/**
 * @brief PIR 4 register list.
 * @details Specified register list of PIR 4 Click driver.
 */
#define PIR4_REG_OP                             0x00
#define PIR4_REG_DATA_BUFL                      0x02
#define PIR4_REG_DATA_BUFH                      0x03
#define PIR4_REG_STATUS                         0x04
#define PIR4_REG_OVERCOUNT                      0x05
#define PIR4_REG_ODR                            0x06
#define PIR4_REG_PASS_FILTER                    0x07
#define PIR4_REG_INTSEL                         0x09
#define PIR4_REG_THRESHCOUNT                    0x0A
#define PIR4_REG_THRESH_HR                      0x0B
#define PIR4_REG_THRESH_LR                      0x0C
#define PIR4_REG_TIMER_LR                       0x0D
#define PIR4_REG_TIMER_HR                       0x0E

/*! @} */ // pir4_reg

/**
 * @defgroup pir4_set PIR 4 Registers Settings
 * @brief Settings for registers of PIR 4 Click driver.
 */

/**
 * @addtogroup pir4_set
 * @{
 */

/**
 * @brief PIR 4 OP state setting.
 * @details Specified setting for OP state of PIR 4 Click driver.
 */
#define PIR4_OP_STATE_ACTIVE                    0
#define PIR4_OP_STATE_SLEEP                     1

/**
 * @brief PIR 4 ODR setting.
 * @details Specified setting for ODR of PIR 4 Click driver.
 */
#define PIR4_ODR_50_HZ                          0
#define PIR4_ODR_100_HZ                         1
#define PIR4_ODR_DEFAULT                        PIR4_ODR_100_HZ

/**
 * @brief PIR 4 pass filter setting.
 * @details Specified setting for pass filter of PIR 4 Click driver.
 */
#define PIR4_LPF_10_HZ                          0
#define PIR4_LPF_7_HZ                           1
#define PIR4_LPF_DEFAULT                        PIR4_LPF_10_HZ
#define PIR4_HPF_0_3_HZ                         0
#define PIR4_HPF_0_5_HZ                         1
#define PIR4_HPF_DEFAULT                        PIR4_HPF_0_3_HZ

/**
 * @brief PIR 4 interrupt selection setting.
 * @details Specified setting for interrupt selection of PIR 4 Click driver.
 */
#define PIR4_INT_SEL_CONTINUOUS_OUT             0
#define PIR4_INT_SEL_TIMER                      1
#define PIR4_INT_SEL_AND_THRESHOLD_LH           2
#define PIR4_INT_SEL_OR_THRESHOLD_LH            3
#define PIR4_INT_SEL_DEFAULT                    PIR4_INT_SEL_TIMER

/**
 * @brief PIR 4 status setting.
 * @details Specified setting for status of PIR 4 Click driver.
 */
#define PIR4_STATUS_CONTINUOUS_OUT              0x01
#define PIR4_STATUS_TIMER                       0x02
#define PIR4_STATUS_AND_THRESHOLD_LH            0x04
#define PIR4_STATUS_OR_THRESHOLD_LH             0x08
#define PIR4_STATUS_ALL                         0x0F

/**
 * @brief PIR 4 threshold setting.
 * @details Specified setting for threshold of PIR 4 Click driver.
 */
#define PIR4_THRESHOLD_COUNT_DIS                0
#define PIR4_THRESHOLD_COUNT_1_TIME             1
#define PIR4_THRESHOLD_COUNT_2_TIMES            2
#define PIR4_THRESHOLD_COUNT_3_TIMES            3
#define PIR4_THRESHOLD_COUNT_4_TIMES            4
#define PIR4_THRESHOLD_COUNT_5_TIMES            5
#define PIR4_THRESHOLD_COUNT_6_TIMES            6
#define PIR4_THRESHOLD_COUNT_7_TIMES            7
#define PIR4_THRESHOLD_COUNT_DEFAULT            PIR4_THRESHOLD_COUNT_1_TIME
#define PIR4_THRESHOLD_HIGH_MIN                 0
#define PIR4_THRESHOLD_HIGH_MAX                 32640
#define PIR4_THRESHOLD_HIGH_DEFAULT             6144
#define PIR4_THRESHOLD_LOW_MAX                  0
#define PIR4_THRESHOLD_LOW_MIN               ( -32640 )
#define PIR4_THRESHOLD_LOW_DEFAULT           ( -6144 )
#define PIR4_THRESHOLD_RES                      128

/**
 * @brief PIR 4 window time setting.
 * @details Specified setting for window time of PIR 4 Click driver.
 * @note 1 step means 0.02s for 50Hz odr, and 0.01s for 100Hz odr.
 */
#define PIR4_WINDOW_TIME_MIN                    0
#define PIR4_WINDOW_TIME_DEFAULT                50
#define PIR4_WINDOW_TIME_MAX                    1023

/**
 * @brief PIR 4 device address setting.
 * @details Specified setting for device slave address selection of
 * PIR 4 Click driver.
 */
#define PIR4_DEVICE_ADDRESS_0                   0x48
#define PIR4_DEVICE_ADDRESS_1                   0x49

/*! @} */ // pir4_set

/**
 * @defgroup pir4_map PIR 4 MikroBUS Map
 * @brief MikroBUS pin mapping of PIR 4 Click driver.
 */

/**
 * @addtogroup pir4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PIR 4 Click to the selected MikroBUS.
 */
#define PIR4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pir4_map
/*! @} */ // pir4

/**
 * @brief PIR 4 Click context object.
 * @details Context object definition of PIR 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable device pin (active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} pir4_t;

/**
 * @brief PIR 4 Click configuration object.
 * @details Configuration object definition of PIR 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable device pin (active high). */
    pin_name_t int_pin;         /**< Interrupt pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} pir4_cfg_t;

/**
 * @brief PIR 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PIR4_OK = 0,
    PIR4_ERROR = -1

} pir4_return_value_t;

/*!
 * @addtogroup pir4 PIR 4 Click Driver
 * @brief API for configuring and manipulating PIR 4 Click driver.
 * @{
 */

/**
 * @brief PIR 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pir4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pir4_cfg_setup ( pir4_cfg_t *cfg );

/**
 * @brief PIR 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pir4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_init ( pir4_t *ctx, pir4_cfg_t *cfg );

/**
 * @brief PIR 4 default configuration function.
 * @details This function executes a default configuration of PIR 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pir4_default_cfg ( pir4_t *ctx );

/**
 * @brief PIR 4 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register address.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_write_regs ( pir4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief PIR 4 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register address.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_read_regs ( pir4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief PIR 4 write register function.
 * @details This function writes a single data byte to the selected
 * register address.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_write_reg ( pir4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PIR 4 read register function.
 * @details This function reads a single data byte from the selected
 * register address.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_read_reg ( pir4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PIR 4 enable device function.
 * @details This function enables the device by setting the EN pin to a
 * logic high state.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pir4_enable_device ( pir4_t *ctx );

/**
 * @brief PIR 4 disable device function.
 * @details This function disables the device by setting the EN pin to a
 * logic low state.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pir4_disable_device ( pir4_t *ctx );

/**
 * @brief PIR 4 get INT pin state function.
 * @details This function returns the logical state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @return INT pin logic state (0 or 1).
 * @note None.
 */
uint8_t pir4_get_int_pin ( pir4_t *ctx );

/**
 * @brief PIR 4 set operating state function.
 * @details This function sets the device operating state register.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] op_state : Operating state value.
 * Use predefined PIR4_OP_STATE_ macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_set_operating_state ( pir4_t *ctx, uint8_t op_state );

/**
 * @brief PIR 4 set output data rate function.
 * @details This function sets the output data rate (ODR) for the internal
 * sampling of the PIR signal.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] odr : Output data rate setting.
 * Use predefined PIR4_ODR_ macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_set_odr ( pir4_t *ctx, uint8_t odr );

/**
 * @brief PIR 4 set pass filter configuration function.
 * @details This function sets the low-pass and high-pass filter configuration
 * used for PIR signal processing.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] lpf : Low-pass filter selection.
 * @param[in] hpf : High-pass filter selection.
 * Use predefined PIR4_LPF_ and PIR4_HPF_ macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_set_pass_filter ( pir4_t *ctx, uint8_t lpf, uint8_t hpf );

/**
 * @brief PIR 4 set interrupt source function.
 * @details This function configures the interrupt source used to assert
 * the INT pin (timer, AND/OR threshold logic).
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] int_sel : Interrupt source selection.
 * Use predefined PIR4_INT_SEL_ macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_set_interrupt ( pir4_t *ctx, uint8_t int_sel );

/**
 * @brief PIR 4 set threshold function.
 * @details This function configures the number of events and the upper and
 * lower threshold values used by the internal threshold logic.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] count : Threshold count setting.
 * @param[in] thr_high : Upper threshold value (in raw units).
 * @param[in] thr_low : Lower threshold value (in raw units).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_set_threshold ( pir4_t *ctx, uint8_t count, int16_t thr_high, int16_t thr_low );

/**
 * @brief PIR 4 set timer window function.
 * @details This function sets the timer window duration used for internal
 * event counting in timer-based detection modes.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] window_time : Timer window time value.
 * Use units and limits defined by PIR4_WINDOW_TIME_ macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_set_timer ( pir4_t *ctx, uint16_t window_time );

/**
 * @brief PIR 4 read overcount values function.
 * @details This function reads the overcount register and extracts the
 * upper and lower overcount values.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[out] oc_up : Pointer to store upper overcount value (can be NULL).
 * @param[out] oc_lo : Pointer to store lower overcount value (can be NULL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_read_overcount ( pir4_t *ctx, uint8_t *oc_up, uint8_t *oc_lo );

/**
 * @brief PIR 4 read status function.
 * @details This function reads the status register and returns the status
 * flags masked to the lower nibble.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[out] status : Pointer to store status flags (can be NULL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_read_status ( pir4_t *ctx, uint8_t *status );

/**
 * @brief PIR 4 clear status function.
 * @details This function clears status bits by writing back the selected
 * flags to the status register.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[in] status : Status bits to clear (lower nibble is used).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_clear_status ( pir4_t *ctx, uint8_t status );

/**
 * @brief PIR 4 read continuous output function.
 * @details This function reads a continuous output sample when the corresponding
 * status flag and INT pin indicate that new data is available. After reading,
 * the status flags are cleared.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to store raw continuous output data
 * (can be NULL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_read_continuous_out ( pir4_t *ctx, int16_t *data_out );

/**
 * @brief PIR 4 read output overcount function.
 * @details This function reads the overcount and status information when the
 * INT pin is asserted and the detection conditions are met. After reading,
 * the status flags are cleared.
 * @param[in] ctx : Click context object.
 * See #pir4_t object definition for detailed explanation.
 * @param[out] oc_up : Pointer to store upper overcount value (can be NULL).
 * @param[out] oc_lo : Pointer to store lower overcount value (can be NULL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir4_read_out ( pir4_t *ctx, uint8_t *oc_up, uint8_t *oc_lo );

#ifdef __cplusplus
}
#endif
#endif // PIR4_H

/*! @} */ // pir4

// ------------------------------------------------------------------------ END
