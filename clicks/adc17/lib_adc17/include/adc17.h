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
 * @file adc17.h
 * @brief This file contains API for ADC 17 Click Driver.
 */

#ifndef ADC17_H
#define ADC17_H

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
 * @addtogroup adc17 ADC 17 Click Driver
 * @brief API for configuring and manipulating ADC 17 Click driver.
 * @{
 */

/**
 * @defgroup adc17_set ADC 17 Registers Settings
 * @brief Settings for registers of ADC 17 Click driver.
 */

/**
 * @addtogroup adc17_set
 * @{
 */

/**
 * @brief ADC 17 setup byte values.
 * @details Specified setup byte values of ADC 17 Click driver.
 */
#define ADC17_REG_SETUP                     0x80
#define ADC17_SETUP_VREF_VDD_REF_NC_OFF     0x00
#define ADC17_SETUP_VREF_EXT_REF_IN_OFF     0x20
#define ADC17_SETUP_VREF_INT_REF_NC_OFF     0x40
#define ADC17_SETUP_VREF_INT_REF_NC_ON      0x50
#define ADC17_SETUP_VREF_INT_REF_OUT_OFF    0x60
#define ADC17_SETUP_VREF_INT_REF_OUT_ON     0x70
#define ADC17_SETUP_CLK_INT                 0x00
#define ADC17_SETUP_CLK_EXT                 0x08
#define ADC17_SETUP_UNIPOLAR                0x00
#define ADC17_SETUP_BIPOLAR                 0x04
#define ADC17_SETUP_RST_RESET               0x00
#define ADC17_SETUP_RST_NO_ACTION           0x02

/**
 * @brief ADC 17 config byte values.
 * @details Specified config byte values of ADC 17 Click driver.
 */
#define ADC17_REG_CONFIG                    0x00
#define ADC17_CONFIG_SCAN_AIN0_TO_CS0       0x00
#define ADC17_CONFIG_SCAN_CS0_8_TIMES       0x20
#define ADC17_CONFIG_SCAN_CS0               0x60
#define ADC17_CONFIG_CS0_AIN0               0x00
#define ADC17_CONFIG_CS0_AIN1               0x02
#define ADC17_CONFIG_DIFFERENTIAL           0x00
#define ADC17_CONFIG_SINGLE_ENDED           0x01

/**
 * @brief ADC 17 register bit mask.
 * @details Specified register bit of ADC 17 Click driver.
 */
#define ADC17_REG_BIT_MASK                  0x80
#define ADC17_SETUP_VREF_BIT_MASK           0x70
#define ADC17_SETUP_CLK_BIT_MASK            0x08
#define ADC17_SETUP_UNI_BIP_BIT_MASK        0x04
#define ADC17_SETUP_RST_BIT_MASK            0x02
#define ADC17_CONFIG_SCAN_BIT_MASK          0x60
#define ADC17_CONFIG_CS0_BIT_MASK           0x02
#define ADC17_CONFIG_SGL_DIF_BIT_MASK       0x01

/**
 * @brief ADC 17 channel selection values.
 * @details Specified channel selection values of ADC 17 Click driver.
 */
#define ADC17_CHANNEL_0                     0
#define ADC17_CHANNEL_1                     1

/**
 * @brief ADC 17 calculation values.
 * @details Specified calculation values of ADC 17 Click driver.
 */
#define ADC17_RESOLUTION                    0x0FFF
#define ADC17_VREF                          2.048

/**
 * @brief ADC 17 device address setting.
 * @details Specified setting for device slave address selection of
 * ADC 17 Click driver.
 */
#define ADC17_SET_DEV_ADDR                  0x36

/*! @} */ // adc17_set

/**
 * @defgroup adc17_map ADC 17 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 17 Click driver.
 */

/**
 * @addtogroup adc17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 17 Click to the selected MikroBUS.
 */
#define ADC17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // adc17_map
/*! @} */ // adc17

/**
 * @brief ADC 17 Click context object.
 * @details Context object definition of ADC 17 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t setup_byte;         /**< Setup byte last programmed value. */
    uint8_t config_byte;        /**< Config byte last programmed value. */
    
} adc17_t;

/**
 * @brief ADC 17 Click configuration object.
 * @details Configuration object definition of ADC 17 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} adc17_cfg_t;

/**
 * @brief ADC 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC17_OK = 0,
    ADC17_ERROR = -1

} adc17_return_value_t;

/*!
 * @addtogroup adc17 ADC 17 Click Driver
 * @brief API for configuring and manipulating ADC 17 Click driver.
 * @{
 */

/**
 * @brief ADC 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc17_cfg_setup ( adc17_cfg_t *cfg );

/**
 * @brief ADC 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc17_init ( adc17_t *ctx, adc17_cfg_t *cfg );

/**
 * @brief ADC 17 default configuration function.
 * @details This function executes a default configuration of ADC 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #adc17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc17_default_cfg ( adc17_t *ctx );

/**
 * @brief ADC 17 write setup byte function.
 * @details This function writes a setup byte to the ADC chip by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc17_t object definition for detailed explanation.
 * @param[in] setup_byte : Setup byte to be written ( the value will be stored in @b ctx->setup_byte ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc17_write_setup_byte ( adc17_t *ctx, uint8_t setup_byte );

/**
 * @brief ADC 17 write config byte function.
 * @details This function writes a config byte to the ADC chip by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc17_t object definition for detailed explanation.
 * @param[in] config_byte : Config byte to be written ( the value will be stored in @b ctx->config_byte ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc17_write_config_byte ( adc17_t *ctx, uint8_t config_byte );

/**
 * @brief ADC 17 set channel function.
 * @details This function sets the selected channel active by modifying the config byte.
 * @param[in] ctx : Click context object.
 * See #adc17_t object definition for detailed explanation.
 * @param[in] channel : Channel number (0-1).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc17_set_channel ( adc17_t *ctx, uint8_t channel );

/**
 * @brief ADC 17 get voltage function.
 * @details This function reads the voltage from the previously selected channel 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc17_t object definition for detailed explanation.
 * @param[out] voltage : Voltage value [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc17_get_voltage ( adc17_t *ctx, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // ADC17_H

/*! @} */ // adc17

// ------------------------------------------------------------------------ END
