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
 * @file volume2.h
 * @brief This file contains API for Volume 2 Click Driver.
 */

#ifndef VOLUME2_H
#define VOLUME2_H

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
 * @addtogroup volume2 Volume 2 Click Driver
 * @brief API for configuring and manipulating Volume 2 Click driver.
 * @{
 */

/**
 * @defgroup volume2_reg Volume 2 Registers List
 * @brief List of registers of Volume 2 Click driver.
 */

/**
 * @addtogroup volume2_reg
 * @{
 */

/**
 * @brief Volume 2 gain register.
 * @details Gain register for both channels of Volume 2 Click driver.
 */
#define VOLUME2_REG_VOLUME_1A_2A                                0x00

/**
 * @brief Volume 2 zero and atten Ch1 register.
 * @details Zero cross detection and attenuation for Ch1 of Volume 2 Click driver.
 */
#define VOLUME2_REG_VOLUME_1B_ZERO1                             0x01

/**
 * @brief Volume 2 zero and atten Ch2 register.
 * @details Zero cross detection and attenuation for Ch2 of Volume 2 Click driver.
 */
#define VOLUME2_REG_VOLUME_2B_ZERO2                             0x02

/*! @} */ // volume2_reg

/**
 * @defgroup volume2_set Volume 2 Registers Settings
 * @brief Settings for registers of Volume 2 Click driver.
 */

/**
 * @addtogroup volume2_set
 * @{
 */

/**
 * @brief Volume 2 gain 0dB option setting.
 * @details This option should be assigned to gain_chX of volume2_vol_data_t structure.
 */
#define VOLUME2_GAIN_OPT_0_DB                                   0x00

/**
 * @brief Volume 2 gain 3dB option setting.
 * @details This option should be assigned to gain_chX of volume2_vol_data_t structure.
 */
#define VOLUME2_GAIN_OPT_3_DB                                   0x01

/**
 * @brief Volume 2 gain 6dB option setting.
 * @details This option should be assigned to gain_chX of volume2_vol_data_t structure.
 */
#define VOLUME2_GAIN_OPT_6_DB                                   0x02

/**
 * @brief Volume 2 gain 9dB option setting.
 * @details This option should be assigned to gain_chX of volume2_vol_data_t structure.
 */
#define VOLUME2_GAIN_OPT_9_DB                                   0x03

/**
 * @brief Volume 2 zero cross detection disable setting.
 * @details This option should be assigned to zero_cross_det_chX of volume2_vol_data_t structure.
 */
#define VOLUME2_ZERO_CROSS_DET_OPT_OFF                          0x00

/**
 * @brief Volume 2 zero cross detection enable setting.
 * @details This option should be assigned to zero_cross_det_chX of volume2_vol_data_t structure.
 */
#define VOLUME2_ZERO_CROSS_DET_OPT_ON                           0x01

/**
 * @brief Volume 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Volume 2 Click driver.
 */
#define VOLUME2_SET_DEV_ADDR  0x44

/*! @} */ // volume2_set

/**
 * @defgroup mte_state Volume 2 option List
 * @brief List of mute options of Volume 2 Click driver.
 */

/**
 * @addtogroup mte_state
 * @{
 */

/**
 * @brief Volume 2 mute option on.
 * @details This setting enables mute option of Volume 2 Click driver.
 */
#define VOLUME2_DEVICE_MUTE_ON                                  0x00

/**
 * @brief Volume 2 mute option off.
 * @details This setting disables mute option of Volume 2 Click driver.
 */
#define VOLUME2_DEVICE_MUTE_OFF                                 0x01

/*! @} */ // mte_state

/**
 * @defgroup volume2_map Volume 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Volume 2 Click driver.
 */

/**
 * @addtogroup volume2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Volume 2 Click to the selected MikroBUS.
 */
#define VOLUME2_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.mte = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // volume2_map
/*! @} */ // volume2

/**
 * @brief Volume 2 Click context object.
 * @details Context object definition of Volume 2 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  mte;                              /**< Digital output pin for hardware mute. */

    // Modules

    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} volume2_t;

/**
 * @brief Volume 2 Click configuration object.
 * @details Configuration object definition of Volume 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  mte;                                 /**< Digital output pin for hardware mute. */

    uint32_t  i2c_speed;                             /**< I2C serial speed. */
    uint8_t   i2c_address;                           /**< I2C slave address. */

} volume2_cfg_t;

/**
 * @brief Volume 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VOLUME2_OK = 0,
    VOLUME2_ERROR = -1

} volume2_return_value_t;

/**
 * @brief Volume 2 Vol data structure.
 * @details Complete vol data structure for Volume 2 Click driver.
 */
typedef struct
{
    uint8_t gain_ch1;                                /**< Set gain on Ch1, choose one of the predefined options. */
    uint8_t gain_ch2;                                /**< Set gain on Ch2, choose one of the predefined options. */
    uint8_t attenuation_ch1;                         /**< Set attenation on Ch1, possible value ranges from 0 to 95. */
    uint8_t attenuation_ch2;                         /**< Set attenation on Ch2, possible value ranges from 0 to 95. */
    uint8_t zero_cross_det_ch1;                      /**< Zero cross detection set on Ch1, choose one of the predefined options. */
    uint8_t zero_cross_det_ch2;                      /**< Zero cross detection set on Ch2, choose one of the predefined options. */
    
} volume2_vol_data_t;

/*!
 * @addtogroup volume2 Volume 2 Click Driver
 * @brief API for configuring and manipulating Volume 2 Click driver.
 * @{
 */

/**
 * @brief Volume 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #volume2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void volume2_cfg_setup ( volume2_cfg_t *cfg );

/**
 * @brief Volume 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #volume2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #volume2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t volume2_init ( volume2_t *ctx, volume2_cfg_t *cfg );

/**
 * @brief Volume 2 default configuration function.
 * @details This function executes a default configuration of Volume 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #volume2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t volume2_default_cfg ( volume2_t *ctx );

/**
 * @brief Volume 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #volume2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t volume2_generic_write ( volume2_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Volume 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #volume2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t volume2_generic_read ( volume2_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Volume 2 device mute function.
 * @details This function is used to set mute on or off by controlling the mte pin.
 * @param[in] ctx : Click context object.
 * See #volume2_t object definition for detailed explanation.
 * @param[in] mte_state : Device mute state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t volume2_device_mute ( volume2_t *ctx, uint8_t mte_state );

/**
 * @brief Volume 2 update volume data function.
 * @details This function updates the volume by using direct defined structure options.
 * When adjusting the structure data, it is mandatory to call this function so the
 * changes can take place.
 * @param[in] ctx : Click context object.
 * See #volume2_t object definition for detailed explanation.
 * @param[in] update_data : Volume data structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t volume2_update_vol_data ( volume2_t *ctx, volume2_vol_data_t update_data );

#ifdef __cplusplus
}
#endif
#endif // VOLUME2_H

/*! @} */ // volume2

// ------------------------------------------------------------------------ END
