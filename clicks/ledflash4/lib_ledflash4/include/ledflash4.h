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
 * @file ledflash4.h
 * @brief This file contains API for LED Flash 4 Click Driver.
 */

#ifndef LEDFLASH4_H
#define LEDFLASH4_H

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
 * @addtogroup ledflash4 LED Flash 4 Click Driver
 * @brief API for configuring and manipulating LED Flash 4 Click driver.
 * @{
 */

/**
 * @defgroup ledflash4_reg LED Flash 4 Registers List
 * @brief List of registers of LED Flash 4 Click driver.
 */

/**
 * @addtogroup ledflash4_reg
 * @{
 */

/**
 * @brief LED Flash 4 register.
 * @details Specified register of LED Flash 4 Click driver.
 */
#define LEDFLASH4_REG_CHIP_ID               0x00
#define LEDFLASH4_REG_CURRENT_SET_LED1      0x01
#define LEDFLASH4_REG_CURRENT_SET_LED2      0x02
#define LEDFLASH4_REG_LOW_VOLTAGE           0x04
#define LEDFLASH4_REG_FLASH_TIMER           0x05
#define LEDFLASH4_REG_CONTROL               0x06
#define LEDFLASH4_REG_STROBE_SIGNALING      0x07
#define LEDFLASH4_REG_FAULT                 0x08
#define LEDFLASH4_REG_PWM_AND_INDICATOR     0x09
#define LEDFLASH4_REG_MINIMUM_LED_CURRENT   0x0E
#define LEDFLASH4_REG_ACTUAL_LED_CURRENT    0x0F
#define LEDFLASH4_REG_PASSWORD              0x80
#define LEDFLASH4_REG_CURRENT_BOOST         0x81

/*! @} */ // ledflash4_reg

/**
 * @defgroup ledflash4_set LED Flash 4 Registers Settings
 * @brief Settings for registers of LED Flash 4 Click driver.
 */

/**
 * @addtogroup ledflash4_set
 * @{
 */

/**
 * @brief LED Flash 4 device ID setting.
 * @details Specified setting for device ID of LED Flash 4 Click driver.
 */
#define LEDFLASH4_DEVICE_ID                 0xB0
#define LEDFLASH4_DEVICE_ID_MASK            0xF8

/**
 * @brief LED Flash 4 LED current setting.
 * @details Specified setting for LED current of LED Flash 4 Click driver.
 */
#define LEDFLASH4_LED_CURRENT_MIN           0
#define LEDFLASH4_LED_CURRENT_MAX           900
#define LEDFLASH4_LED_CURRENT_DEFAULT       50
#define LEDFLASH4_LED_CURRENT_REG_MASK      0xFF
#define LEDFLASH4_LED_CURRENT_ROUND_INT     0.5f

/**
 * @brief LED Flash 4 low voltage register setting.
 * @details Specified setting for low voltage register of LED Flash 4 Click driver.
 */
#define LEDFLASH4_VIN_LOW_V_RUN_DIS         0x00
#define LEDFLASH4_VIN_LOW_V_RUN_3V          0x01
#define LEDFLASH4_VIN_LOW_V_RUN_3_07V       0x02
#define LEDFLASH4_VIN_LOW_V_RUN_3_14V       0x03
#define LEDFLASH4_VIN_LOW_V_RUN_3_22V       0x04
#define LEDFLASH4_VIN_LOW_V_RUN_3_3V        0x05
#define LEDFLASH4_VIN_LOW_V_RUN_3_38V       0x06
#define LEDFLASH4_VIN_LOW_V_RUN_3_47V       0x07
#define LEDFLASH4_VIN_LOW_V_RUN_MASK        0x07
#define LEDFLASH4_VIN_LOW_V_DIS             0x00
#define LEDFLASH4_VIN_LOW_V_3V              0x08
#define LEDFLASH4_VIN_LOW_V_3_07V           0x10
#define LEDFLASH4_VIN_LOW_V_3_14V           0x18
#define LEDFLASH4_VIN_LOW_V_3_22V           0x20
#define LEDFLASH4_VIN_LOW_V_3_3V            0x28
#define LEDFLASH4_VIN_LOW_V_3_38V           0x30
#define LEDFLASH4_VIN_LOW_V_3_47V           0x38
#define LEDFLASH4_VIN_LOW_V_MASK            0x38
#define LEDFLASH4_VIN_LOW_V_SHUTDOWN_MASK   0x40
#define LEDFLASH4_CONST_V_MODE_MASK         0x80

/**
 * @brief LED Flash 4 flash timer register setting.
 * @details Specified setting for flash timer register of LED Flash 4 Click driver.
 */
#define LEDFLASH4_FLASH_TIMER_36MS          0x23

/**
 * @brief LED Flash 4 control register setting.
 * @details Specified setting for control register of LED Flash 4 Click driver.
 */
#define LEDFLASH4_CONTROL_MODE_SHUTDOWN     0x00
#define LEDFLASH4_CONTROL_MODE_INDICATOR    0x01
#define LEDFLASH4_CONTROL_MODE_ASSIST_LIGHT 0x02
#define LEDFLASH4_CONTROL_MODE_FLASH        0x03
#define LEDFLASH4_CONTROL_MODE_MASK         0x03
#define LEDFLASH4_CONTROL_OUT_OFF           0x00
#define LEDFLASH4_CONTROL_OUT_ON            0x08
#define LEDFLASH4_CONTROL_OUT_MASK          0x08
#define LEDFLASH4_CONTROL_AUTO_STROBE_OFF   0x00
#define LEDFLASH4_CONTROL_AUTO_STROBE_ON    0x10
#define LEDFLASH4_CONTROL_AUTO_STROBE_MASK  0x10
#define LEDFLASH4_CONTROL_STROBE_TYPE_EDGE  0x00
#define LEDFLASH4_CONTROL_STROBE_TYPE_LEVEL 0x40
#define LEDFLASH4_CONTROL_STROBE_TYPE_MASK  0x40
#define LEDFLASH4_CONTROL_STROBE_INPUT_OFF  0x00
#define LEDFLASH4_CONTROL_STROBE_INPUT_ON   0x80
#define LEDFLASH4_CONTROL_STROBE_INPUT_MASK 0x80

/**
 * @brief LED Flash 4 fault register setting.
 * @details Specified setting for fault register of LED Flash 4 Click driver.
 */
#define LEDFLASH4_FAULT_UVLO                0x01
#define LEDFLASH4_FAULT_TIMEOUT             0x10
#define LEDFLASH4_FAULT_OVERTEMP            0x20
#define LEDFLASH4_FAULT_LED_SHORT           0x40
#define LEDFLASH4_FAULT_OVP                 0x80

/**
 * @brief LED Flash 4 pwm and indicator register setting.
 * @details Specified setting for pwm and indicator register of LED Flash 4 Click driver.
 */
#define LEDFLASH4_PWM_INCT_1_OF_16_DC       0x00
#define LEDFLASH4_PWM_INCT_2_OF_16_DC       0x01
#define LEDFLASH4_PWM_INCT_3_OF_16_DC       0x02
#define LEDFLASH4_PWM_INCT_4_OF_16_DC       0x03
#define LEDFLASH4_PWM_INCT_MASK             0x03
#define LEDFLASH4_PWM_FREQ_SWITCH_ON_MASK   0x04
#define LEDFLASH4_PWM_LED_OUT1ABOVE2_MASK   0x08
#define LEDFLASH4_PWM_LED_OUT2ABOVE1_MASK   0x10
#define LEDFLASH4_PWM_LOAD_BALANCE_ON_MASK  0x20

/**
 * @brief LED Flash 4 strobe pin setting.
 * @details Specified setting for strobe pin of LED Flash 4 Click driver.
 */
#define LEDFLASH4_STROBE_PIN_LOW            0
#define LEDFLASH4_STROBE_PIN_HIGH           1

/**
 * @brief LED Flash 4 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Flash 4 Click driver.
 */
#define LEDFLASH4_DEVICE_ADDRESS_0          0x30
#define LEDFLASH4_DEVICE_ADDRESS_1          0x32

/*! @} */ // ledflash4_set

/**
 * @defgroup ledflash4_map LED Flash 4 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Flash 4 Click driver.
 */

/**
 * @addtogroup ledflash4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Flash 4 Click to the selected MikroBUS.
 */
#define LEDFLASH4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // ledflash4_map
/*! @} */ // ledflash4

/**
 * @brief LED Flash 4 Click context object.
 * @details Context object definition of LED Flash 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t stb;          /**< Strobe time control pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} ledflash4_t;

/**
 * @brief LED Flash 4 Click configuration object.
 * @details Configuration object definition of LED Flash 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t stb;             /**< Strobe time control pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ledflash4_cfg_t;

/**
 * @brief LED Flash 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDFLASH4_OK = 0,
    LEDFLASH4_ERROR = -1

} ledflash4_return_value_t;

/*!
 * @addtogroup ledflash4 LED Flash 4 Click Driver
 * @brief API for configuring and manipulating LED Flash 4 Click driver.
 * @{
 */

/**
 * @brief LED Flash 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ledflash4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ledflash4_cfg_setup ( ledflash4_cfg_t *cfg );

/**
 * @brief LED Flash 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ledflash4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash4_init ( ledflash4_t *ctx, ledflash4_cfg_t *cfg );

/**
 * @brief LED Flash 4 default configuration function.
 * @details This function executes a default configuration of LED Flash 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ledflash4_default_cfg ( ledflash4_t *ctx );

/**
 * @brief LED Flash 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash4_generic_write ( ledflash4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LED Flash 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash4_generic_read ( ledflash4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LED Flash 4 write reg function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash4_write_reg ( ledflash4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LED Flash 4 read reg function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash4_read_reg ( ledflash4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LED Flash 4 set STB pin function.
 * @details This function sets the strobe (STB) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ledflash4_set_stb_pin ( ledflash4_t *ctx, uint8_t state );

/**
 * @brief LED Flash 4 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash4_check_communication ( ledflash4_t *ctx );

/**
 * @brief LED Flash 4 set LED1 current function.
 * @details This function sets the LED1 maximum current in mA.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @param[in] led_current : LED current in mA [0-900].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash4_set_led1_current ( ledflash4_t *ctx, uint16_t led_current );

/**
 * @brief LED Flash 4 set LED2 current function.
 * @details This function sets the LED2 maximum current in mA.
 * @param[in] ctx : Click context object.
 * See #ledflash4_t object definition for detailed explanation.
 * @param[in] led_current : LED current in mA [0-900].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash4_set_led2_current ( ledflash4_t *ctx, uint16_t led_current );

#ifdef __cplusplus
}
#endif
#endif // LEDFLASH4_H

/*! @} */ // ledflash4

// ------------------------------------------------------------------------ END
