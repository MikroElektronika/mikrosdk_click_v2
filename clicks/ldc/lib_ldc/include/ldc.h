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
 * @file ldc.h
 * @brief This file contains API for LDC Click Driver.
 */

#ifndef LDC_H
#define LDC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ldc LDC Click Driver
 * @brief API for configuring and manipulating LDC Click driver.
 * @{
 */

/**
 * @defgroup ldc_reg LDC Registers List
 * @brief List of registers of LDC Click driver.
 */

/**
 * @addtogroup ldc_reg
 * @{
 */

/**
 * @brief LDC description register.
 * @details Specified register for description of LDC Click driver.
 */
#define LDC_REG_DATA_CH0            0x00
#define LDC_REG_DATA_CH1            0x02
#define LDC_REG_RCOUNT_CH0          0x08
#define LDC_REG_RCOUNT_CH1          0x09
#define LDC_REG_OFFSET_CH0          0x0C
#define LDC_REG_OFFSET_CH1          0x0D
#define LDC_REG_SETTLECOUNT_CH0     0x10
#define LDC_REG_SETTLECOUNT_CH1     0x11
#define LDC_REG_CLOCK_DIVIDERS_CH0  0x14
#define LDC_REG_CLOCK_DIVIDERS_CH1  0x15
#define LDC_REG_STATUS              0x18
#define LDC_REG_ERROR_CONFIG        0x19
#define LDC_REG_CONFIG              0x1A
#define LDC_REG_MUX_CONFIG          0x1B
#define LDC_REG_RESET_DEV           0x1C
#define LDC_REG_DRIVE_CURRENT_CH0   0x1E
#define LDC_REG_DRIVE_CURRENT_CH1   0x1F
#define LDC_REG_MANUFACTURER_ID     0x7E
#define LDC_REG_DEVICE_ID           0x7F

/*! @} */ // ldc_reg

/**
 * @defgroup ldc_set LDC Registers Settings
 * @brief Settings for registers of LDC Click driver.
 */

/**
 * @addtogroup ldc_set
 * @{
 */

/**
 * @brief LDC identification data.
 * @details Specified ID's for LDC Click driver.
 */
#define LDC_MANUFACTURER_ID         0x5449
#define LDC_DEVICE_ID               0x3054 

/**
 * @brief LDC identification data.
 * @details Specified ID's for LDC Click driver.
 */
#define LDC_INTERNAL_FREQUENCY      43.4/*<MHz*/
#define LDC_FREQUENCY_RESOLUTION    4096
#define LDC_SENSOR_CAPACITANCE      0.00022/*<uF*/

/**
 * @brief Gain configuration.
 * @details Specified gain values configuration of LDC Click driver.
 */
#define LDC_GAIN_1                  0x0000
#define LDC_GAIN_4                  0x0200
#define LDC_GAIN_8                  0x0400
#define LDC_GAIN_16                 0x0600

/**
 * @brief Error status data from data register.
 * @details Specified error status data from data register of LDC Click driver.
 */
#define LDC_OVER_RANGE              0x8
#define LDC_UNDER_RANGE             0x4
#define LDC_WATCHDOG                0x3

/**
 * @brief Status register.
 * @details Specified status register of LDC Click driver.
 */
#define LDC_STATUS_DRDY             0x0040

/**
 * @brief LDC device address setting.
 * @details Specified setting for device slave address selection of
 * LDC Click driver.
 */
#define LDC_SET_DEV_ADDR            0x2B 

/*! @} */ // ldc_set

/**
 * @defgroup ldc_map LDC MikroBUS Map
 * @brief MikroBUS pin mapping of LDC Click driver.
 */

/**
 * @addtogroup ldc_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LDC Click to the selected MikroBUS.
 */
#define LDC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ldc_map
/*! @} */ // ldc

/**
 * @brief LDC Click context object.
 * @details Context object definition of LDC Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  sd;      /**< Shut down. */

    // Input pins
    digital_in_t  int_pin;  /**< Interrupt. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} ldc_t;

/**
 * @brief LDC Click configuration object.
 * @details Configuration object definition of LDC Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  sd;         /**< Shut down. */
    pin_name_t  int_pin;    /**< Interrput. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} ldc_cfg_t;

/**
 * @brief LDC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LDC_OK = 0,
   LDC_ERROR = -1,
   LDC_ERROR_UNDER_RANGE = -2,
   LDC_ERROR_OVER_RANGE = -3,
   LDC_ERROR_WATCHDOG = -4

} ldc_return_value_t;

/*!
 * @addtogroup ldc LDC Click Driver
 * @brief API for configuring and manipulating LDC Click driver.
 * @{
 */

/**
 * @brief LDC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ldc_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ldc_cfg_setup ( ldc_cfg_t *cfg );

/**
 * @brief LDC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ldc_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ldc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ldc_init ( ldc_t *ctx, ldc_cfg_t *cfg );

/**
 * @brief LDC default configuration function.
 * @details This function executes a default configuration of LDC
 * click board.
 * @param[in] ctx : Click context object.
 * See #ldc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ldc_default_cfg ( ldc_t *ctx );

/**
 * @brief LDC I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ldc_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ldc_generic_write ( ldc_t *ctx, uint8_t reg, uint16_t tx_data );

/**
 * @brief LDC I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ldc_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ldc_generic_read ( ldc_t *ctx, uint8_t reg, uint16_t *rx_data );

/**
 * @brief Get interrupt pin status.
 * @details This function reads @b int_pin status.
 * @param[in] ctx : Click context object.
 * See #ldc_t object definition for detailed explanation.
 * @return Interrupt pin status.
 */
uint8_t ldc_get_interrupt ( ldc_t *ctx );

/**
 * @brief Set shut down pin status.
 * @details This function sets @b sd pin status.
 * @param[in] ctx : Click context object.
 * See #ldc_t object definition for detailed explanation.
 * @param[in] state : Pin state to set.
 * @return Nothing.
 */
void ldc_set_shut_down ( ldc_t *ctx, uint8_t state );

/**
 * @brief Get frequency value calulated for specific channel.
 * @details This function reads a data from data channel and 
 * calculates frequency relative to selected divider.
 * @param[in] ctx : Click context object.
 * See #ldc_t object definition for detailed explanation.
 * @param[in] channel : Channel data register to read from.
 * @param[in] divider : Divider set for selected channel.
 * @param[out] frequency : Calculated frequency in MHz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Under-range,
 *         @li @c -3 - Over-range,
 *         @li @c -4 - Watchdog.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ldc_get_frequency ( ldc_t *ctx, uint8_t channel, uint16_t divider, float *frequency );

/**
 * @brief Calculate inductance relative to frequency.
 * @details This function calculates inductance relative to forwarded frequency.
 * @param[in] ctx : Click context object.
 * See #ldc_t object definition for detailed explanation.
 * @param[in] frequency : Current sensor frequency.
 * @return Calculated inductance data in uH unit.
 */
float ldc_calculate_inductance ( float frequency );


#ifdef __cplusplus
}
#endif
#endif // LDC_H

/*! @} */ // ldc

// ------------------------------------------------------------------------ END
