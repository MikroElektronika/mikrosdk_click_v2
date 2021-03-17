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
 * @file analogmux2.h
 * @brief This file contains API for Analog MUX 2 Click Driver.
 */

#ifndef ANALOGMUX2_H
#define ANALOGMUX2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup analogmux2 Analog MUX 2 Click Driver
 * @brief API for configuring and manipulating Analog MUX 2 Click driver.
 * @{
 */

/**
 * @defgroup analogmux2_reg Analog MUX 2 Registers List
 * @brief List of registers of Analog MUX 2 Click driver.
 */

/**
 * @defgroup analogmux2_set Analog MUX 2 Registers Settings
 * @brief Settings for registers of Analog MUX 2 Click driver.
 */

/**
 * @addtogroup analogmux2_set
 * @{
 */

/**
 * @brief Analog MUX 2 set channel setting.
 * @details Specified set channel setting 
 * for description of Analog MUX 2 Click driver.
 */
#define ANALOGMUX2_SET_CHANNEL_0      0x00
#define ANALOGMUX2_SET_CHANNEL_1      0x01
#define ANALOGMUX2_SET_CHANNEL_2      0x02
#define ANALOGMUX2_SET_CHANNEL_3      0x03
#define ANALOGMUX2_SET_CHANNEL_4      0x04
#define ANALOGMUX2_SET_CHANNEL_5      0x05
#define ANALOGMUX2_SET_CHANNEL_6      0x06
#define ANALOGMUX2_SET_CHANNEL_7      0x07
#define ANALOGMUX2_SET_NO_CHANNEL     0xFF

/**
 * @brief Analog MUX 2 channel value setting.
 * @details Specified channel value setting 
 * for description of Analog MUX 2 Click driver.
 */
#define ANALOGMUX2_VAL_CHANNEL_OFF    0x00
#define ANALOGMUX2_VAL_CHANNEL_0      0x01
#define ANALOGMUX2_VAL_CHANNEL_1      0x02
#define ANALOGMUX2_VAL_CHANNEL_2      0x04
#define ANALOGMUX2_VAL_CHANNEL_3      0x08
#define ANALOGMUX2_VAL_CHANNEL_4      0x10
#define ANALOGMUX2_VAL_CHANNEL_5      0x20
#define ANALOGMUX2_VAL_CHANNEL_6      0x40
#define ANALOGMUX2_VAL_CHANNEL_7      0x80

/**
 * @brief Analog MUX 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Analog MUX 2 Click driver.
 */
#define ANALOGMUX2_SET_DEV_ADDR_0      0x4C
#define ANALOGMUX2_SET_DEV_ADDR_1      0x4D
#define ANALOGMUX2_SET_DEV_ADDR_2      0x4E
#define ANALOGMUX2_SET_DEV_ADDR_3      0x4F

/*! @} */ // analogmux2_set

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief Analog MUX 2 error status.
 * @details Specified error status 
 * for description of Analog MUX 2 Click driver.
 */
#define ANALOGMUX2_SUCCESS            0
#define ANALOGMUX2_ERROR             -1


/*! @} */ // status


/**
 * @defgroup analogmux2_map Analog MUX 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Analog MUX 2 Click driver.
 */

/**
 * @addtogroup analogmux2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Analog MUX 2 Click to the selected MikroBUS.
 */
#define ANALOGMUX2_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // analogmux2_map
/*! @} */ // analogmux2

/**
 * @brief Analog MUX 2 Click context object.
 * @details Context object definition of Analog MUX 2 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  rst;     /**< Power-up of the device. */

    // Modules

    analog_in_t  adc;

    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} analogmux2_t;

/**
 * @brief Analog MUX 2 Click configuration object.
 * @details Configuration object definition of Analog MUX 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  an;         /**< Analog pin. */
    pin_name_t  rst;        /**< Power-up of the device. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */
    
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} analogmux2_cfg_t;

/*!
 * @addtogroup analogmux2 Analog MUX 2 Click Driver
 * @brief API for configuring and manipulating Analog MUX 2 Click driver.
 * @{
 */

/**
 * @brief Analog MUX 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #analogmux2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void analogmux2_cfg_setup ( analogmux2_cfg_t *cfg );

/**
 * @brief Analog MUX 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #analogmux2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t analogmux2_init ( analogmux2_t *ctx, analogmux2_cfg_t *cfg );

/**
 * @brief Analog MUX 2 default configuration function.
 * @details This function executes a default configuration of Analog MUX 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
void analogmux2_default_cfg ( analogmux2_t *ctx );

/**
 * @brief Analog MUX 2 reset the device function.
 * @details This function executes a hardware reset of
 * Analog MUX 2 click board.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void analogmux2_hw_reset ( analogmux2_t *ctx );

/**
 * @brief Analog MUX 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t analogmux2_generic_write ( analogmux2_t *ctx, uint8_t tx_data );

/**
 * @brief Analog MUX 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t analogmux2_generic_read ( analogmux2_t *ctx );

/**
 * @brief Analog MUX 2 set channel function.
 * @details This function sets the active channel by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param[in] mux_ch : 
 *         @li @c 0x00 ( ANALOGMUX2_SET_CHANNEL_0 ) - Set active channel 0,
 *         @li @c 0x01 ( ANALOGMUX2_SET_CHANNEL_1 ) - Set active channel 1,
 *         @li @c 0x02 ( ANALOGMUX2_SET_CHANNEL_2 ) - Set active channel 2,
 *         @li @c 0x03 ( ANALOGMUX2_SET_CHANNEL_3 ) - Set active channel 3,
 *         @li @c 0x04 ( ANALOGMUX2_SET_CHANNEL_4 ) - Set active channel 4,
 *         @li @c 0x05 ( ANALOGMUX2_SET_CHANNEL_5 ) - Set active channel 5,
 *         @li @c 0x06 ( ANALOGMUX2_SET_CHANNEL_6 ) - Set active channel 6,
 *         @li @c 0x07 ( ANALOGMUX2_SET_CHANNEL_7 ) - Set active channel 7,
 *         @li @c 0xFF ( ANALOGMUX2_SET_NO_CHANNEL )- Disable all channels.
 *         
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t analogmux2_set_channel ( analogmux2_t *ctx, uint8_t mux_ch );

/**
 * @brief Analog MUX 2 get channel function.
 * @details This function get the active channel by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.        
 *         
 * @return @li @c 0x00 ( ANALOGMUX2_SET_CHANNEL_0 ) - Active channel 0,
 *         @li @c 0x01 ( ANALOGMUX2_SET_CHANNEL_1 ) - Active channel 1,
 *         @li @c 0x02 ( ANALOGMUX2_SET_CHANNEL_2 ) - Active channel 2,
 *         @li @c 0x03 ( ANALOGMUX2_SET_CHANNEL_3 ) - Active channel 3,
 *         @li @c 0x04 ( ANALOGMUX2_SET_CHANNEL_4 ) - Active channel 4,
 *         @li @c 0x05 ( ANALOGMUX2_SET_CHANNEL_5 ) - Active channel 5,
 *         @li @c 0x06 ( ANALOGMUX2_SET_CHANNEL_6 ) - Active channel 6,
 *         @li @c 0x07 ( ANALOGMUX2_SET_CHANNEL_7 ) - Active channel 7,
 *         @li @c 0xFF ( ANALOGMUX2_SET_NO_CHANNEL )- Disable all channels.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t analogmux2_get_channel ( analogmux2_t *ctx );

/**
 * @brief Analog MUX 2 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t analogmux2_read_an_pin_value ( analogmux2_t *ctx, uint16_t *data_out );

/**
 * @brief Analog MUX 2 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #analogmux2_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t analogmux2_read_an_pin_voltage ( analogmux2_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // ANALOGMUX2_H

/*! @} */ // analogmux2

// ------------------------------------------------------------------------ END
