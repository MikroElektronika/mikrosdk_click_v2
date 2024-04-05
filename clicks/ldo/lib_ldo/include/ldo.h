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
 * @file ldo.h
 * @brief This file contains API for LDO Click Driver.
 */

#ifndef LDO_H
#define LDO_H

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
 * @addtogroup ldo LDO Click Driver
 * @brief API for configuring and manipulating LDO Click driver.
 * @{
 */

/**
 * @defgroup ldo_reg LDO Registers List
 * @brief List of registers of LDO Click driver.
 */

/**
 * @addtogroup ldo_reg
 * @{
 */

/**
 * @brief LDO register list.
 * @details Specified register list of LDO Click driver.
 */
#define LDO_REG_INPUT_PORT              0x00
#define LDO_REG_OUTPUT_PORT             0x01
#define LDO_REG_POLARITY_INV            0x02
#define LDO_REG_CONFIG                  0x03

/*! @} */ // ldo_reg

/**
 * @defgroup ldo_set LDO Registers Settings
 * @brief Settings for registers of LDO Click driver.
 */

/**
 * @addtogroup ldo_set
 * @{
 */

/**
 * @brief LDO pin mask values.
 * @details Specified pin mask values of LDO Click driver.
 */
#define LDO_PIN_NONE                    0x00
#define LDO_PIN_1600_mV                 0x01
#define LDO_PIN_800_mV                  0x02
#define LDO_PIN_400_mV                  0x04
#define LDO_PIN_200_mV                  0x08
#define LDO_PIN_100_mV                  0x10
#define LDO_PIN_50_mV                   0x20
#define LDO_PIN_ALL                     0x3F

/**
 * @brief LDO pin logic level setting.
 * @details Specified setting for pin logic level of LDO Click driver.
 */
#define LDO_PIN_LOW                     0
#define LDO_PIN_OPEN                    1

/**
 * @brief LDO VOUT settings.
 * @details Specified VOUT settings of LDO Click driver.
 */
#define LDO_VOUT_MIN                    800
#define LDO_VOUT_STEP                   50
#define LDO_VOUT_MAX                    3950

/**
 * @brief LDO device address setting.
 * @details Specified setting for device slave address selection of LDO Click driver.
 */
#define LDO_DEVICE_ADDRESS_0            0x38
#define LDO_DEVICE_ADDRESS_1            0x39
#define LDO_DEVICE_ADDRESS_2            0x3A
#define LDO_DEVICE_ADDRESS_3            0x3B
#define LDO_DEVICE_ADDRESS_4            0x3C
#define LDO_DEVICE_ADDRESS_5            0x3D
#define LDO_DEVICE_ADDRESS_6            0x3E
#define LDO_DEVICE_ADDRESS_7            0x3F

/*! @} */ // ldo_set

/**
 * @defgroup ldo_map LDO MikroBUS Map
 * @brief MikroBUS pin mapping of LDO Click driver.
 */

/**
 * @addtogroup ldo_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LDO Click to the selected MikroBUS.
 */
#define LDO_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); 

/*! @} */ // ldo_map
/*! @} */ // ldo

/**
 * @brief LDO Click context object.
 * @details Context object definition of LDO Click driver.
 */
typedef struct
{    
    // Output pins
    digital_out_t en;           /**< Enable pin (Active high). */
    
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} ldo_t;

/**
 * @brief LDO Click configuration object.
 * @details Configuration object definition of LDO Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t en;              /**< Enable pin (Active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ldo_cfg_t;

/**
 * @brief LDO Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LDO_OK = 0,
    LDO_ERROR = -1

} ldo_return_value_t;

/*!
 * @addtogroup ldo LDO Click Driver
 * @brief API for configuring and manipulating LDO Click driver.
 * @{
 */

/**
 * @brief LDO configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ldo_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ldo_cfg_setup ( ldo_cfg_t *cfg );

/**
 * @brief LDO initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ldo_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ldo_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldo_init ( ldo_t *ctx, ldo_cfg_t *cfg );

/**
 * @brief LDO default configuration function.
 * @details This function executes a default configuration of LDO
 * click board.
 * @param[in] ctx : Click context object.
 * See #ldo_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ldo_default_cfg ( ldo_t *ctx );

/**
 * @brief LDO write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ldo_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldo_write_register ( ldo_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LDO read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ldo_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldo_read_register ( ldo_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LDO set pin state function.
 * @details This function sets the state of the selected pins. Others remain unchanged.
 * @param[in] ctx : Click context object.
 * See #ldo_t object definition for detailed explanation.
 * @param[in] pin_mask : Bit-mask of pins to configure.
 * @param[in] state : State of pins (0-LOW, 1-OPEN).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldo_set_pin_state ( ldo_t *ctx, uint8_t pin_mask, uint8_t state );

/**
 * @brief LDO set vout function.
 * @details This function sets the voltage output.
 * @param[in] ctx : Click context object.
 * See #ldo_t object definition for detailed explanation.
 * @param[in] vout : Voltage output in a range of 800 to 3950 mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldo_set_vout ( ldo_t *ctx, uint16_t vout );

/**
 * @brief LDO enable device function.
 * @details This function enables the device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #ldo_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ldo_enable_device ( ldo_t *ctx );

/**
 * @brief LDO disable device function.
 * @details This function disables the device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #ldo_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ldo_disable_device ( ldo_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LDO_H

/*! @} */ // ldo

// ------------------------------------------------------------------------ END
