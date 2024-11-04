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
 * @file isoadc3.h
 * @brief This file contains API for ISO ADC 3 Click Driver.
 */

#ifndef ISOADC3_H
#define ISOADC3_H

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
 * @addtogroup isoadc3 ISO ADC 3 Click Driver
 * @brief API for configuring and manipulating ISO ADC 3 Click driver.
 * @{
 */

/**
 * @defgroup isoadc3_set ISO ADC 3 Registers Settings
 * @brief Settings for registers of ISO ADC 3 Click driver.
 */

/**
 * @addtogroup isoadc3_set
 * @{
 */

/**
 * @brief ISO ADC 3 description setting.
 * @details Specified setting for description of ISO ADC 3 Click driver.
 */
#define ISOADC3_RESOLUTION                  4096
#define ISOADC3_OFFSET                      1287
#define ISOADC3_ADC_NUM_OF_MEASURE          100.0
#define ISOADC3_12_BIT_DATA                 0x0FFF
#define ISOADC3_GAIN                        4

/**
 * @brief ISO ADC 3 Vref.
 * @details Specified setting for Vref of ISO ADC 3 Click driver,
 * depending on VCC SEL ( 3.3V or 5V ).
 */
#define ISOADC3_VREF_3V3                    3336
#define ISOADC3_VREF_5V                     5070

/**
 * @brief ISO ADC 3 device address setting.
 * @details Specified setting for device slave address selection of
 * ISO ADC 3 Click driver.
 */
#define ISOADC3_SET_DEV_ADDR                0x4D

/*! @} */ // isoadc3_set

/**
 * @defgroup isoadc3_map ISO ADC 3 MikroBUS Map
 * @brief MikroBUS pin mapping of ISO ADC 3 Click driver.
 */

/**
 * @addtogroup isoadc3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISO ADC 3 Click to the selected MikroBUS.
 */
#define ISOADC3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // isoadc3_map
/*! @} */ // isoadc3

/**
 * @brief ISO ADC 3 Click context object.
 * @details Context object definition of ISO ADC 3 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} isoadc3_t;

/**
 * @brief ISO ADC 3 Click configuration object.
 * @details Configuration object definition of ISO ADC 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} isoadc3_cfg_t;

/**
 * @brief ISO ADC 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ISOADC3_OK = 0,
   ISOADC3_ERROR = -1

} isoadc3_return_value_t;

/*!
 * @addtogroup isoadc3 ISO ADC 3 Click Driver
 * @brief API for configuring and manipulating ISO ADC 3 Click driver.
 * @{
 */

/**
 * @brief ISO ADC 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #isoadc3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void isoadc3_cfg_setup ( isoadc3_cfg_t *cfg );

/**
 * @brief ISO ADC 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #isoadc3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #isoadc3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc3_init ( isoadc3_t *ctx, isoadc3_cfg_t *cfg );

/**
 * @brief ISO ADC 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc3_generic_write ( isoadc3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief ISO ADC 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 *
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc3_generic_read ( isoadc3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Read ADC function.
 * @details Function is used to read raw ADC data from MCP3221.
 * @param[in] ctx : Click context object.
 * See #isoadc3_t object definition for detailed explanation.
 * @returns Result 16-bit value that represents ADC value from output register
**/
uint16_t isoadc3_read_adc ( isoadc3_t *ctx );

/**
 * @brief Read ADC voltage function.
 * @details Function is used to read raw voltage data from MCP3221.
 * @param[in] ctx : Click context object.
 * See #isoadc3_t object definition for detailed explanation.
 * @param[in] v_ref : 16-bit value representing power supply voltage.
 * @returns Result 12-bit value that represents voltage in millivolts.
**/
uint16_t isoadc3_get_adc_voltage ( isoadc3_t *ctx, uint16_t v_ref );

/**
 * @brief Read voltage function.
 * @details Function is used to calculate voltage of the connected battery.
 * @param[in] ctx : Click context object.
 * See #isoadc3_t object definition for detailed explanation.
 * @param[in] v_ref : 16-bit value representing power supply voltage.
 * @returns Result 12-bit value that represents voltage in millivolts.
**/
uint16_t isoadc3_read_voltage ( isoadc3_t *ctx, uint16_t v_ref );

#ifdef __cplusplus
}
#endif
#endif // ISOADC3_H

/*! @} */ // isoadc3

// ------------------------------------------------------------------------ END
