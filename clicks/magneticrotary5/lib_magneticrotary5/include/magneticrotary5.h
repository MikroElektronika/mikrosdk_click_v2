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
 * @file magneticrotary5.h
 * @brief This file contains API for Magnetic Rotary 5 Click Driver.
 */

#ifndef MAGNETICROTARY5_H
#define MAGNETICROTARY5_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup magneticrotary5 Magnetic Rotary 5 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 5 Click driver.
 * @{
 */

/**
 * @defgroup magneticrotary5_reg Magnetic Rotary 5 Registers List
 * @brief List of registers of Magnetic Rotary 5 Click driver.
 */

/**
 * @addtogroup magneticrotary5_reg
 * @{
 */

/**
 * @brief Magnetic Rotary 5 command list.
 * @details Specified command list of Magnetic Rotary 5 Click driver.
 */
#define MAGNETICROTARY5_CMD_WRITE_CONFIG            0x17
#define MAGNETICROTARY5_CMD_SET_MT_COUNTER          0x14
#define MAGNETICROTARY5_CMD_EN_PROG                 0x10
#define MAGNETICROTARY5_CMD_RD_MT_COUNTER           0x04
#define MAGNETICROTARY5_CMD_RD_ANGLE                0x00
#define MAGNETICROTARY5_CMD_WRITE_OTP               0x1F
#define MAGNETICROTARY5_CMD_PROG_OTP                0x19
#define MAGNETICROTARY5_CMD_READ_OTP                0x0F
#define MAGNETICROTARY5_CMD_READ_ANA                0x09

/*! @} */ // magneticrotary5_reg

/**
 * @defgroup magneticrotary5_set Magnetic Rotary 5 Registers Settings
 * @brief Settings for registers of Magnetic Rotary 5 Click driver.
 */

/**
 * @addtogroup magneticrotary5_set
 * @{
 */

/**
 * @brief Magnetic Rotary 5 bit mask and range setting.
 * @details Specified setting for bit mask and range of Magnetic Rotary 5 Click driver.
 */
#define MAGNETICROTARY5_MASK_AGC_BITS               0x3F
#define MAGNETICROTARY5_MASK_ANGLE_MSB              0x01
#define MAGNETICROTARY5_MASK_MT_CNT_MSB             0x01FE
#define MAGNETICROTARY5_MASK_MT_CNT_LSB             0x01
#define MAGNETICROTARY5_MASK_5_LSB                  0x1F
#define MAGNETICROTARY5_MASK_3_LSB                  0x07
#define MAGNETICROTARY5_MAX_DATA_LEN                8
#define MAGNETICROTARY5_MIN_DATA_LEN                1
#define MAGNETICROTARY5_MAX_MT_CNT                  255
#define MAGNETICROTARY5_MIN_MT_CNT                  (-256)
#define MAGNETICROTARY5_DEFAULT_MT_CNT              0

/**
 * @brief Magnetic Rotary 5 ADC setting.
 * @details Specified settings for ADC of Magnetic Rotary 5 Click driver.
 */
#define MAGNETICROTARY5_VREF_3V3                    3.3
#define MAGNETICROTARY5_VREF_5V                     5.0

/*! @} */ // magneticrotary5_set

/**
 * @defgroup magneticrotary5_map Magnetic Rotary 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Magnetic Rotary 5 Click driver.
 */

/**
 * @addtogroup magneticrotary5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magnetic Rotary 5 Click to the selected MikroBUS.
 */
#define MAGNETICROTARY5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.dio   = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.ddclk = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an    = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // magneticrotary5_map
/*! @} */ // magneticrotary5

/**
 * @brief Magnetic Rotary 5 Click context object.
 * @details Context object definition of Magnetic Rotary 5 Click driver.
 */
typedef struct
{
    digital_out_t ddclk;            /**< Clock input for serial interface. */
    digital_out_t cs;               /**< Chip select input for 3-wire mode. */
    pin_name_t    dio;              /**< Data I/O pin for serial interface. */
    
    analog_in_t   adc;              /**< ADC module object. */
    
} magneticrotary5_t;

/**
 * @brief Magnetic Rotary 5 Click configuration object.
 * @details Configuration object definition of Magnetic Rotary 5 Click driver.
 */
typedef struct
{
    pin_name_t ddclk;               /**< Clock input for serial interface. */
    pin_name_t cs;                  /**< Chip select input for 3-wire mode. */
    pin_name_t dio;                 /**< Data I/O pin for serial interface. */
    pin_name_t an;                  /**< Analog input pin. */

    analog_in_resolution_t resolution;      /**< ADC resolution. */
    float                  vref;            /**< ADC reference voltage. */

} magneticrotary5_cfg_t;

/**
 * @brief Magnetic Rotary 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETICROTARY5_OK = 0,
    MAGNETICROTARY5_ERROR = -1

} magneticrotary5_return_value_t;

/*!
 * @addtogroup magneticrotary5 Magnetic Rotary 5 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 5 Click driver.
 * @{
 */

/**
 * @brief Magnetic Rotary 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneticrotary5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneticrotary5_cfg_setup ( magneticrotary5_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneticrotary5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary5_init ( magneticrotary5_t *ctx, magneticrotary5_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 5 default configuration function.
 * @details This function executes a default configuration of Magnetic Rotary 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magneticrotary5_default_cfg ( magneticrotary5_t *ctx );

/**
 * @brief Magnetic Rotary 5 write cmd function.
 * @details This function writes a desired number of data bytes to the selected command
 * by using SSI serial interface bit banging.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte (5-bits).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary5_write_cmd ( magneticrotary5_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Magnetic Rotary 5 read cmd function.
 * @details This function reads a desired number of data bytes from the selected command
 * by using SSI serial interface bit banging.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte (5-bits).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary5_read_cmd ( magneticrotary5_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Magnetic Rotary 5 read angle function.
 * @details This function reads the magnetic angle and automatic gain control (AGC)
 * values measured by the sensor.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[out] agc : Automatic gain control (AGC) value [0,63].
 * @param[out] angle : Magnetic angle in degrees [0,360].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary5_read_angle ( magneticrotary5_t *ctx, uint8_t *agc, uint16_t *angle );

/**
 * @brief Magnetic Rotary 5 read multi turn counter function.
 * @details This function reads the multi turn counter value. With each zero transition in any direction,
 * the output of a special counter is incremented or decremented.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[out] mt_cnt : Multi turn counter value [-256,255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary5_read_mt_cnt ( magneticrotary5_t *ctx, int16_t *mt_cnt );

/**
 * @brief Magnetic Rotary 5 set multi turn counter function.
 * @details This function sets the multi turn counter value. The initial value after reset is 0 LSB.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[in] mt_cnt : Multi turn counter value [-256,255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary5_set_mt_cnt ( magneticrotary5_t *ctx, int16_t mt_cnt );

/**
 * @brief Magnetic Rotary 5 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary5_read_raw_adc ( magneticrotary5_t *ctx, uint16_t *raw_adc );

/**
 * @brief Magnetic Rotary 5 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t magneticrotary5_read_voltage ( magneticrotary5_t *ctx, float *voltage );

/**
 * @brief Magnetic Rotary 5 set vref function.
 * @details This function sets the voltage reference for Magnetic Rotary 5 click driver.
 * @param[in] ctx : Click context object.
 * See #magneticrotary5_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b magneticrotary5_init is 3.3V.
 */
err_t magneticrotary5_set_vref ( magneticrotary5_t *ctx, float vref );

#ifdef __cplusplus
}
#endif
#endif // MAGNETICROTARY5_H

/*! @} */ // magneticrotary5

// ------------------------------------------------------------------------ END
