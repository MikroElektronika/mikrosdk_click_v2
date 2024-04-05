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
 * @file heartrate10.h
 * @brief This file contains API for Heart Rate 10 Click Driver.
 */

#ifndef HEARTRATE10_H
#define HEARTRATE10_H

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
 * @addtogroup heartrate10 Heart Rate 10 Click Driver
 * @brief API for configuring and manipulating Heart Rate 10 Click driver.
 * @{
 */

/**
 * @defgroup heartrate10_reg Heart Rate 10 Registers List
 * @brief List of registers of Heart Rate 10 Click driver.
 */

/**
 * @addtogroup heartrate10_reg
 * @{
 */

/**
 * @brief Heart Rate 10 communication register.
 * @details Specified registers for communication with Heart Rate 10 Click.
 */
#define HEARTRATE10_REG_INT_STATUS              0x00
#define HEARTRATE10_REG_INT_ENABLE              0x02
#define HEARTRATE10_REG_FIFO_WR_PTR             0x04
#define HEARTRATE10_REG_FIFO_OVF_CNT            0x05
#define HEARTRATE10_REG_FIFO_RD_PTR             0x06
#define HEARTRATE10_REG_FIFO_DATA               0x07
#define HEARTRATE10_REG_FIFO_CFG                0x08
#define HEARTRATE10_REG_MODE_CFG1               0x09
#define HEARTRATE10_REG_MODE_CFG2               0x0A
#define HEARTRATE10_REG_LED1_PA                 0x0C
#define HEARTRATE10_REG_LED2_PA                 0x0D
#define HEARTRATE10_REG_LED3_PA                 0x0E
#define HEARTRATE10_REG_LED4_PA                 0x0F
#define HEARTRATE10_REG_LED_RANGE               0x11
#define HEARTRATE10_REG_PILOT_PA                0x12
#define HEARTRATE10_REG_LED_SEQ1                0x13
#define HEARTRATE10_REG_LED_SEQ2                0x14
#define HEARTRATE10_REG_DAC1_CROSSTALK_CODE     0x26
#define HEARTRATE10_REG_DAC2_CROSSTALK_CODE     0x27
#define HEARTRATE10_REG_DAC3_CROSSTALK_CODE     0x28
#define HEARTRATE10_REG_DAC4_CROSSTALK_CODE     0x29
#define HEARTRATE10_REG_PROX_INT_THRESHOLD      0x30
#define HEARTRATE10_REG_LED_COMPARATOR_EN       0x31
#define HEARTRATE10_REG_LED_COMPARATOR_STATUS   0x32
#define HEARTRATE10_REG_REV_ID                  0xFE
#define HEARTRATE10_REG_PART_ID                 0xFF

/*! @} */ // heartrate10_reg

/**
 * @defgroup heartrate10_set Heart Rate 10 Registers Settings
 * @brief Settings for registers of Heart Rate 10 Click driver.
 */

/**
 * @addtogroup heartrate10_set
 * @{
 */

/**
 * @brief Heart Rate 10 description setting.
 * @details Specified setting for description of Heart Rate 10 Click driver.
 */
#define HEARTRATE10_PART_ID                     0x2B

/**
 * @brief Heart Rate 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Heart Rate 10 Click driver.
 */
#define HEARTRATE10_SET_DEV_ADDR                0x57

/*! @} */ // heartrate10_set

/**
 * @defgroup heartrate10_map Heart Rate 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Heart Rate 10 Click driver.
 */

/**
 * @addtogroup heartrate10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Heart Rate 10 Click to the selected MikroBUS.
 */
#define HEARTRATE10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // heartrate10_map
/*! @} */ // heartrate10

/**
 * @brief Heart Rate 10 Click context object.
 * @details Context object definition of Heart Rate 10 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;  /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} heartrate10_t;

/**
 * @brief Heart Rate 10 Click configuration object.
 * @details Configuration object definition of Heart Rate 10 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} heartrate10_cfg_t;

/**
 * @brief Heart Rate 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HEARTRATE10_OK = 0,
   HEARTRATE10_ERROR = -1

} heartrate10_return_value_t;

/*!
 * @addtogroup heartrate10 Heart Rate 10 Click Driver
 * @brief API for configuring and manipulating Heart Rate 10 Click driver.
 * @{
 */

/**
 * @brief Heart Rate 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #heartrate10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void heartrate10_cfg_setup ( heartrate10_cfg_t *cfg );

/**
 * @brief Heart Rate 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #heartrate10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t heartrate10_init ( heartrate10_t *ctx, heartrate10_cfg_t *cfg );

/**
 * @brief Heart Rate 10 default configuration function.
 * @details This function executes a default configuration of Heart Rate 10
 * click board.
 * @param[in] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t heartrate10_default_cfg ( heartrate10_t *ctx );

/**
 * @brief Writing function.
 * @details This function writes a data to the selected register.
 * @param[in] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t heartrate10_generic_write ( heartrate10_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Reading function.
 * @details This function reads a data from the selected register.
 * @param[in] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t heartrate10_generic_read ( heartrate10_t *ctx, uint8_t reg, uint8_t *rx_data );

/**
 * @brief Get interrupt pin state.
 * @details Read and return @b int_pin state.
 * @param[in] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @return Pin state
 *
 * See #err_t definition for detailed explanation.
 */
uint8_t heartrate10_get_int_pin ( heartrate10_t *ctx );

/**
 * @brief Reset device.
 * @details Set bit for reseting device and waits untill bit is cleared.
 * @param[in] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @return Nothing.
 */
void heartrate10_reset ( heartrate10_t *ctx );

/**
 * @brief Read fifo register data.
 * @details This function reads a data from the @b HEARTRATE10_REG_FIFO_DATA.
 * @param[in] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Length of data to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t heartrate10_fifo_read ( heartrate10_t *ctx, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Read single sample of FIFO data.
 * @details This function reads a 3 bytes from FIFO data register 
 * and concatenates data into 19bit led data.
 * @param[in] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @return Led data.
 * 
 * @note This function will read sample of data for four led diod it assumes 
 * that there is at least one led enabled and set in sequence register.
 */
uint32_t heartrate10_read_fifo_sample ( heartrate10_t *ctx );

/**
 * @brief Read all led samples.
 * @details This function reads a 12 bytes from FIFO data register 
 * and concatenates data into 4 x 19bit led data.
 * @param[in] ctx : Click context object.
 * See #heartrate10_t object definition for detailed explanation.
 * @param[out] led1 : Led1 output read data.
 * @param[out] led2 : Led2 output read data.
 * @param[out] led3 : Led3 output read data.
 * @param[out] led4 : Led4 output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function will read four samples of data for four led diodes
 * it assumes that there are 4 leds enabled and set in sequence register.
 */
err_t heartrate10_read_complete_fifo_data ( heartrate10_t *ctx, uint32_t *led1, uint32_t *led2, uint32_t *led3, uint32_t *led4 );

#ifdef __cplusplus
}
#endif
#endif // HEARTRATE10_H

/*! @} */ // heartrate10

// ------------------------------------------------------------------------ END
