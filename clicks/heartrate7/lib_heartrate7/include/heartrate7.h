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
 * @file heartrate7.h
 * @brief This file contains API for Heart Rate 7 Click Driver.
 */

#ifndef HEARTRATE7_H
#define HEARTRATE7_H

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
 * @addtogroup heartrate7 Heart Rate 7 Click Driver
 * @brief API for configuring and manipulating Heart Rate 7 Click driver.
 * @{
 */

/**
 * @defgroup heartrate7_reg Heart Rate 7 Registers List
 * @brief List of registers of Heart Rate 7 Click driver.
 */

/**
 * @addtogroup heartrate7_reg
 * @{
 */

/**
 * @brief Heart Rate 7 description register.
 * @details Specified register for description of Heart Rate 7 Click driver.
 */

/**
 * @brief Heart Rate 7 Timing control registers.
 * @details Specified register for description of timing control of Heart Rate 7 Click driver.
 */
#define HEARTRATE7_REG0H                       0x00
#define HEARTRATE7_REG1H                       0x01
#define HEARTRATE7_REG2H                       0x02
#define HEARTRATE7_REG3H                       0x03
#define HEARTRATE7_REG4H                       0x04
#define HEARTRATE7_REG5H                       0x05
#define HEARTRATE7_REG6H                       0x06
#define HEARTRATE7_REG7H                       0x07
#define HEARTRATE7_REG8H                       0x08
#define HEARTRATE7_REG9H                       0x09
#define HEARTRATE7_REGAH                       0x0A
#define HEARTRATE7_REGBH                       0x0B
#define HEARTRATE7_REGCH                       0x0C
#define HEARTRATE7_REGDH                       0x0D
#define HEARTRATE7_REGEH                       0x0E
#define HEARTRATE7_REGFH                       0x0F
#define HEARTRATE7_REG10H                      0x10
#define HEARTRATE7_REG11H                      0x11
#define HEARTRATE7_REG12H                      0x12
#define HEARTRATE7_REG13H                      0x13
#define HEARTRATE7_REG14H                      0x14
#define HEARTRATE7_REG15H                      0x15
#define HEARTRATE7_REG16H                      0x16
#define HEARTRATE7_REG17H                      0x17
#define HEARTRATE7_REG18H                      0x18
#define HEARTRATE7_REG19H                      0x19
#define HEARTRATE7_REG1AH                      0x1A
#define HEARTRATE7_REG1BH                      0x1B
#define HEARTRATE7_REG1CH                      0x1C
#define HEARTRATE7_REG1DH                      0x1D
#define HEARTRATE7_REG1EH                      0x1E
#define HEARTRATE7_REG20H                      0x20
#define HEARTRATE7_REG21H                      0x21
#define HEARTRATE7_REG22H                      0x22
#define HEARTRATE7_REG23H                      0x23
#define HEARTRATE7_REG29H                      0x29
#define HEARTRATE7_REG2AH                      0x2A
#define HEARTRATE7_REG2BH                      0x2B
#define HEARTRATE7_REG2CH                      0x2C
#define HEARTRATE7_REG2DH                      0x2D
#define HEARTRATE7_REG2EH                      0x2E
#define HEARTRATE7_REG2FH                      0x2F
#define HEARTRATE7_REG31H                      0x31

/**
 * @brief Heart Rate 7 timing controls for dynamic power-down registers.
 * @details Specified register for description of timing controls for dynamic power-down
 * of Heart Rate 7 Click driver.
 */
#define HEARTRATE7_REG32H                      0x32
#define HEARTRATE7_REG33H                      0x33
#define HEARTRATE7_REG34H                      0x34
#define HEARTRATE7_REG35H                      0x35

/**
 * @brief Heart Rate 7 Timing controls for driving the third LED registers.
 * @details Specified register for description of Timing controls for driving the 
 * third LED of Heart Rate 7 Click driver.
 */
#define HEARTRATE7_REG36H                      0x36
#define HEARTRATE7_REG37H                      0x37
#define HEARTRATE7_REG39H                      0x39
#define HEARTRATE7_REG3AH                      0x3A
#define HEARTRATE7_REG3DH                      0x3D
#define HEARTRATE7_REG3FH                      0x3F
#define HEARTRATE7_REG40H                      0x40

/*! @} */ // heartrate7_reg

/**
 * @defgroup heartrate7_set Heart Rate 7 Registers Settings
 * @brief Settings for registers of Heart Rate 7 Click driver.
 */

/**
 * @addtogroup heartrate7_set
 * @{
 */

/**
 * @brief Heart Rate 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Heart Rate 7 Click driver.
 */
#define HEARTRATE7_SET_DEV_ADDR  0x58

/*! @} */ // heartrate7_set

/**
 * @defgroup heartrate7_map Heart Rate 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Heart Rate 7 Click driver.
 */

/**
 * @addtogroup heartrate7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Heart Rate 7 Click to the selected MikroBUS.
 */
#define HEARTRATE7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // heartrate7_map
/*! @} */ // heartrate7

/**
 * @brief Heart Rate 7 Click context object.
 * @details Context object definition of Heart Rate 7 Click driver.
 */
typedef struct
{
    // Output pins
   digital_out_t  rst;          /**< Reset/Power-down. */

    // Input pins
    digital_in_t  int_pin;      /**< ADC_RDY/Interrupt. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} heartrate7_t;

/**
 * @brief Heart Rate 7 Click configuration object.
 * @details Configuration object definition of Heart Rate 7 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;            /**< Reset/Power-down. */
    pin_name_t  int_pin;        /**< ADC_RDY/Interrupt. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} heartrate7_cfg_t;

/**
 * @brief Heart Rate 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HEARTRATE7_OK = 0,
    HEARTRATE7_ERROR = -1

} heartrate7_return_value_t;

/*!
 * @addtogroup heartrate7 Heart Rate 7 Click Driver
 * @brief API for configuring and manipulating Heart Rate 7 Click driver.
 * @{
 */

/**
 * @brief Heart Rate 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #heartrate7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void heartrate7_cfg_setup ( heartrate7_cfg_t *cfg );

/**
 * @brief Heart Rate 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #heartrate7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t heartrate7_init ( heartrate7_t *ctx, heartrate7_cfg_t *cfg );

/**
 * @brief Heart Rate 7 default configuration function.
 * @details This function executes a default configuration of Heart Rate 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t heartrate7_default_cfg ( heartrate7_t *ctx );

/**
 * @brief Heart Rate 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t heartrate7_generic_write ( heartrate7_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Heart Rate 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t heartrate7_generic_read ( heartrate7_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Heart Rate 7 register writing function.
 * @details This function writes a 24-bit data into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @param[in] reg_addr : Start register address.
 * @param[in] write_data : Data to be written.
 * @return Nothing.
 */
void heartrate7_write_reg( heartrate7_t *ctx, uint8_t reg_addr, uint32_t write_data ); 

/**
 * @brief Heart Rate 7 register reading function.
 * @details This function reads a 24-bit data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @param[in] reg_addr : Start register address.
 * @return 24-bit read data.
 */
uint32_t heartrate7_read_reg( heartrate7_t *ctx, uint8_t reg_addr ); 

/**
 * @brief Heart Rate 7 hardware reset function.
 * @details This function is used to perform hardware reset.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return Nothing.
 */
void heartrate7_hw_reset( heartrate7_t *ctx ); 

/**
 * @brief Heart Rate 7 software reset function.
 * @details This function is used to perform software reset.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return Nothing.
 */
void heartrate7_sw_reset( heartrate7_t *ctx );

/**
 * @brief Heart Rate 7 get LED2 data function.
 * @details This function is used to read conversion data from the LED2.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate7_get_led2_val( heartrate7_t *ctx  );

/**
 * @brief Heart Rate 7 get ALED2 data function.
 * @details This function is used to read conversion data from the ALED2.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate7_get_aled2_val_led3v_al( heartrate7_t *ctx );

/**
 * @brief Heart Rate 7 get LED1 data function.
 * @details This function is used to read conversion data from the LED1.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate7_get_led1_val( heartrate7_t *ctx );

/**
 * @brief Heart Rate 7 get ALED1 data function.
 * @details This function is used to read conversion data from the ALED1.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate7_get_aled1_val( heartrate7_t *ctx );

/**
 * @brief Heart Rate 7 get LED2_ALED2 data function.
 * @details This function is used to read conversion data from the LED2_ALED2.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate7_get_led2_aled2_val( heartrate7_t *ctx ); 

/**
 * @brief Heart Rate 7 get LED1_ALED1 data function.
 * @details This function is used to read conversion data from the LED1_ALED1.
 * @param[in] ctx : Click context object.
 * See #heartrate7_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate7_get_led1_aled1_val( heartrate7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HEARTRATE7_H

/*! @} */ // heartrate7

// ------------------------------------------------------------------------ END
