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
 * @file audioamp11.h
 * @brief This file contains API for AudioAMP 11 Click Driver.
 */

#ifndef AUDIOAMP11_H
#define AUDIOAMP11_H

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
 * @addtogroup audioamp11 AudioAMP 11 Click Driver
 * @brief API for configuring and manipulating AudioAMP 11 Click driver.
 * @{
 */

/**
 * @defgroup audioamp11_reg AudioAMP 11 Registers List
 * @brief List of registers of AudioAMP 11 Click driver.
 */

/**
 * @addtogroup audioamp11_reg
 * @{
 */

/**
 * @brief AudioAMP 11 description register.
 * @details Specified register for description of AudioAMP 11 Click driver.
 */
#define AUDIOAMP11_REG_REGGAIN                  0x04
#define AUDIOAMP11_REG_VOLCTRL                  0x1B

/*! @} */ // audioamp11_reg

/**
 * @defgroup audioamp11_set AudioAMP 11 Registers Settings
 * @brief Settings for registers of AudioAMP 11 Click driver.
 */

/**
 * @addtogroup audioamp11_set
 * @{
 */

/**
 * @brief AudioAMP 11 description setting.
 * @details Specified setting for description of AudioAMP 11 Click driver.
 */
#define AUDIOAMP11_GS_0dB_VOLCTRL_0dB           0x00
#define AUDIOAMP11_GS_0dB_VOLCTRL_m2dB          0x01
#define AUDIOAMP11_GS_0dB_VOLCTRL_m4dB          0x02
#define AUDIOAMP11_GS_0dB_VOLCTRL_m6dB          0x03
#define AUDIOAMP11_GS_0dB_VOLCTRL_m8dB          0x04
#define AUDIOAMP11_GS_0dB_VOLCTRL_m10dB         0x05
#define AUDIOAMP11_GS_0dB_VOLCTRL_m12dB         0x06
#define AUDIOAMP11_GS_0dB_VOLCTRL_m14dB         0x07
#define AUDIOAMP11_GS_0dB_VOLCTRL_m16dB         0x08
#define AUDIOAMP11_GS_0dB_VOLCTRL_m18dB         0x09
#define AUDIOAMP11_GS_0dB_VOLCTRL_m20dB         0x0A
#define AUDIOAMP11_GS_0dB_VOLCTRL_m22dB         0x0B
#define AUDIOAMP11_GS_0dB_VOLCTRL_m24dB         0x0C
#define AUDIOAMP11_GS_0dB_VOLCTRL_m26dB         0x0D
#define AUDIOAMP11_GS_0dB_VOLCTRL_m28dB         0x0E
#define AUDIOAMP11_GS_0dB_VOLCTRL_m30dB         0x0F
#define AUDIOAMP11_GS_0dB_VOLCTRL_m32dB         0x10
#define AUDIOAMP11_GS_0dB_VOLCTRL_m34dB         0x11
#define AUDIOAMP11_GS_0dB_VOLCTRL_m36dB         0x12
#define AUDIOAMP11_GS_0dB_VOLCTRL_m38dB         0x13
#define AUDIOAMP11_GS_0dB_VOLCTRL_m40dB         0x14
#define AUDIOAMP11_GS_0dB_VOLCTRL_m42dB         0x15
#define AUDIOAMP11_GS_0dB_VOLCTRL_m44dB         0x16
#define AUDIOAMP11_GS_0dB_VOLCTRL_m46dB         0x17
#define AUDIOAMP11_GS_0dB_VOLCTRL_m48dB         0x18
#define AUDIOAMP11_GS_0dB_VOLCTRL_m50dB         0x19
#define AUDIOAMP11_GS_0dB_VOLCTRL_m52dB         0x1A
#define AUDIOAMP11_GS_0dB_VOLCTRL_m54dB         0x1B
#define AUDIOAMP11_GS_0dB_VOLCTRL_m56dB         0x1C
#define AUDIOAMP11_GS_0dB_VOLCTRL_m58dB         0x1D
#define AUDIOAMP11_GS_0dB_VOLCTRL_m60dB         0x1E
#define AUDIOAMP11_GS_0dB_VOLCTRL_m62dB         0x1F
#define AUDIOAMP11_GS_6dB_VOLCTRL_6dB           0x00
#define AUDIOAMP11_GS_6dB_VOLCTRL_4_1dB         0x01
#define AUDIOAMP11_GS_6dB_VOLCTRL_2_2dB         0x02
#define AUDIOAMP11_GS_6dB_VOLCTRL_0_4dB         0x03
#define AUDIOAMP11_GS_6dB_VOLCTRL_m1_6dB        0x04
#define AUDIOAMP11_GS_6dB_VOLCTRL_m3_5dB        0x05
#define AUDIOAMP11_GS_6dB_VOLCTRL_m5_6dB        0x06
#define AUDIOAMP11_GS_6dB_VOLCTRL_m7_5dB        0x07
#define AUDIOAMP11_GS_6dB_VOLCTRL_m9_5dB        0x08
#define AUDIOAMP11_GS_6dB_VOLCTRL_m11_4dB       0x09
#define AUDIOAMP11_GS_6dB_VOLCTRL_m13_4dB       0x0A
#define AUDIOAMP11_GS_6dB_VOLCTRL_m15_4dB       0x0B
#define AUDIOAMP11_GS_6dB_VOLCTRL_m17_3dB       0x0C
#define AUDIOAMP11_GS_6dB_VOLCTRL_m19_3dB       0x0D
#define AUDIOAMP11_GS_6dB_VOLCTRL_m21_3dB       0x0E
#define AUDIOAMP11_GS_6dB_VOLCTRL_m23_3dB       0x0F
#define AUDIOAMP11_GS_6dB_VOLCTRL_m25_3dB       0x10
#define AUDIOAMP11_GS_6dB_VOLCTRL_m27_3dB       0x11
#define AUDIOAMP11_GS_6dB_VOLCTRL_m29_1dB       0x12
#define AUDIOAMP11_GS_6dB_VOLCTRL_m30_7dB       0x13
#define AUDIOAMP11_GS_6dB_VOLCTRL_m32_2dB       0x14
#define AUDIOAMP11_GS_6dB_VOLCTRL_m33_7dB       0x15
#define AUDIOAMP11_GS_6dB_VOLCTRL_m35_1dB       0x16
#define AUDIOAMP11_GS_6dB_VOLCTRL_m36_6dB       0x17
#define AUDIOAMP11_GS_6dB_VOLCTRL_m36dB         0x18
#define AUDIOAMP11_GS_6dB_VOLCTRL_m35_2dB       0x19
#define AUDIOAMP11_GS_6dB_VOLCTRL_m34_6dB       0x1A
#define AUDIOAMP11_GS_6dB_VOLCTRL_m33_9dB       0x1B
#define AUDIOAMP11_GS_6dB_VOLCTRL_m33_5dB       0x1D
#define AUDIOAMP11_GS_6dB_VOLCTRL_m33_4dB       0x1E
#define AUDIOAMP11_GS_6dB_VOLCTRL_m62dB         0x1F
#define AUDIOAMP11_GS_12dB_VOLCTRL_12dB         0x00
#define AUDIOAMP11_GS_12dB_VOLCTRL_10_4dB       0x01
#define AUDIOAMP11_GS_12dB_VOLCTRL_8_8dB        0x02
#define AUDIOAMP11_GS_12dB_VOLCTRL_7_1dB        0x03
#define AUDIOAMP11_GS_12dB_VOLCTRL_5_4dB        0x04
#define AUDIOAMP11_GS_12dB_VOLCTRL_3_6dB        0x05
#define AUDIOAMP11_GS_12dB_VOLCTRL_1_7dB        0x06
#define AUDIOAMP11_GS_12dB_VOLCTRL_m0_2dB       0x07
#define AUDIOAMP11_GS_12dB_VOLCTRL_m2dB         0x08
#define AUDIOAMP11_GS_12dB_VOLCTRL_m3_9dB       0x09
#define AUDIOAMP11_GS_12dB_VOLCTRL_m5_8dB       0x0A
#define AUDIOAMP11_GS_12dB_VOLCTRL_m7_8dB       0x0B
#define AUDIOAMP11_GS_12dB_VOLCTRL_m9_7dB       0x0C
#define AUDIOAMP11_GS_12dB_VOLCTRL_m11_7dB      0x0D
#define AUDIOAMP11_GS_12dB_VOLCTRL_m13_6dB      0x0E
#define AUDIOAMP11_GS_12dB_VOLCTRL_m15_6dB      0x0F
#define AUDIOAMP11_GS_12dB_VOLCTRL_m17_6dB      0x10
#define AUDIOAMP11_GS_12dB_VOLCTRL_m19_3dB      0x11
#define AUDIOAMP11_GS_12dB_VOLCTRL_m20_4dB      0x12
#define AUDIOAMP11_GS_12dB_VOLCTRL_m20_5dB      0x13
#define AUDIOAMP11_GS_12dB_VOLCTRL_m20_2dB      0x14
#define AUDIOAMP11_GS_12dB_VOLCTRL_m20dB        0x15
#define AUDIOAMP11_GS_12dB_VOLCTRL_m19_8dB      0x16
#define AUDIOAMP11_GS_12dB_VOLCTRL_m19_7dB      0x17
#define AUDIOAMP11_GS_12dB_VOLCTRL_m19_6dB      0x18
#define AUDIOAMP11_GS_12dB_VOLCTRL_m19_5dB      0x19
#define AUDIOAMP11_GS_12dB_VOLCTRL_m19_4dB      0x1B
#define AUDIOAMP11_GS_18dB_VOLCTRL_18dB         0x00
#define AUDIOAMP11_GS_18dB_VOLCTRL_17dB         0x01
#define AUDIOAMP11_GS_18dB_VOLCTRL_16dB         0x02
#define AUDIOAMP11_GS_18dB_VOLCTRL_15dB         0x03
#define AUDIOAMP11_GS_18dB_VOLCTRL_13_7dB       0x04
#define AUDIOAMP11_GS_18dB_VOLCTRL_12_4dB       0x05
#define AUDIOAMP11_GS_18dB_VOLCTRL_10_9dB       0x06
#define AUDIOAMP11_GS_18dB_VOLCTRL_9_4dB        0x07
#define AUDIOAMP11_GS_18dB_VOLCTRL_7_9dB        0x08
#define AUDIOAMP11_GS_18dB_VOLCTRL_6_2dB        0x09
#define AUDIOAMP11_GS_18dB_VOLCTRL_4_5dB        0x0A
#define AUDIOAMP11_GS_18dB_VOLCTRL_2_7dB        0x0B
#define AUDIOAMP11_GS_18dB_VOLCTRL_0_9dB        0x0C
#define AUDIOAMP11_GS_18dB_VOLCTRL_m0_9dB       0x0D
#define AUDIOAMP11_GS_18dB_VOLCTRL_m2_8dB       0x0E
#define AUDIOAMP11_GS_18dB_VOLCTRL_m4_7dB       0x0F
#define AUDIOAMP11_GS_18dB_VOLCTRL_m6_6dB       0x10
#define AUDIOAMP11_GS_18dB_VOLCTRL_m7_3dB       0x11
#define AUDIOAMP11_GS_18dB_VOLCTRL_m7_1dB       0x14
#define AUDIOAMP11_GS_18dB_VOLCTRL_m7_0dB       0x18
#define AUDIOAMP11_GS_24dB_VOLCTRL_24dB         0x00

#define AUDIOAMP11_VOLUME_LEVEL_31              0x00
#define AUDIOAMP11_VOLUME_LEVEL_30              0x01
#define AUDIOAMP11_VOLUME_LEVEL_29              0x02
#define AUDIOAMP11_VOLUME_LEVEL_28              0x03
#define AUDIOAMP11_VOLUME_LEVEL_27              0x04
#define AUDIOAMP11_VOLUME_LEVEL_26              0x05
#define AUDIOAMP11_VOLUME_LEVEL_25              0x06
#define AUDIOAMP11_VOLUME_LEVEL_24              0x07
#define AUDIOAMP11_VOLUME_LEVEL_23              0x08
#define AUDIOAMP11_VOLUME_LEVEL_22              0x09
#define AUDIOAMP11_VOLUME_LEVEL_21              0x0A
#define AUDIOAMP11_VOLUME_LEVEL_20              0x0B
#define AUDIOAMP11_VOLUME_LEVEL_19              0x0C
#define AUDIOAMP11_VOLUME_LEVEL_18              0x0D
#define AUDIOAMP11_VOLUME_LEVEL_17              0x0E
#define AUDIOAMP11_VOLUME_LEVEL_16              0x0F
#define AUDIOAMP11_VOLUME_LEVEL_15              0x10
#define AUDIOAMP11_VOLUME_LEVEL_14              0x11
#define AUDIOAMP11_VOLUME_LEVEL_13              0x12
#define AUDIOAMP11_VOLUME_LEVEL_12              0x13
#define AUDIOAMP11_VOLUME_LEVEL_11              0x14
#define AUDIOAMP11_VOLUME_LEVEL_10              0x15
#define AUDIOAMP11_VOLUME_LEVEL_9               0x16
#define AUDIOAMP11_VOLUME_LEVEL_8               0x17
#define AUDIOAMP11_VOLUME_LEVEL_7               0x18
#define AUDIOAMP11_VOLUME_LEVEL_6               0x19
#define AUDIOAMP11_VOLUME_LEVEL_5               0x1A
#define AUDIOAMP11_VOLUME_LEVEL_4               0x1B
#define AUDIOAMP11_VOLUME_LEVEL_3               0x1C
#define AUDIOAMP11_VOLUME_LEVEL_2               0x1D
#define AUDIOAMP11_VOLUME_LEVEL_1               0x1E
#define AUDIOAMP11_VOLUME_LEVEL_0               0x1F
#define AUDIOAMP11_VOLUME_MUTE                  0x3F

#define AUDIOAMP11_GAINDEC_0dB                  0x01
#define AUDIOAMP11_GAINDEC_6dB                  0x02
#define AUDIOAMP11_GAINDEC_12dB                 0x04
#define AUDIOAMP11_GAINDEC_18dB                 0x08
#define AUDIOAMP11_GAINDEC_24dB                 0x10

/**
 * @brief AudioAMP 11 device address setting.
 * @details Specified setting for device slave address selection of
 * AudioAMP 11 Click driver.
 */
#define AUDIOAMP11_DEVICE_ADDRESS               0x2A

/*! @} */ // audioamp11_set

/**
 * @addtogroup audioamp11_volume_control
 * @{
 */

/**
 * @brief AudioAMP 11 description volume control.
 * @details Specified volume control for description of AudioAMP 11 Click driver.
 */
#define AUDIOAMP11_CALC_GAIN_CONFIG(GAINDEC)    (GAINDEC==1?0:(GAINDEC==2?6:(GAINDEC==4?12:(GAINDEC==8 ? 18:24))))

#define OUTPUT_VOLUME_0dB   0.0, -2.0, -4.0, -6.0, -8.0, -10.0, -12.0, -14.0, -16.0, -18.0,      \
                           -20.0, -22.0, -24.0, -26.0, -28.0, -30.0, -32.0, -34.0, -36.0, -38.0, \
                           -40.0, -42.0, -44.0, -46.0, -48.0, -50.0, -52.0, -54.0, -56.0, -58.0, -60.0, -62.0

#define OUTPUT_VOLUME_6dB   6.0, 4.1, 2.2, 0.4, -1.6, -3.5, -5.6, -7.5, -29.5, -11.4 ,           \
                           -13.4, -15.4, -17.3, -19.3, -21.3, -23.3, -25.3, -27.3, -29.1, -30.7, \
                           -32.2, -33.7, -35.1, -36.6, -36.0, -35.2, -34.6, -34.2, -33.9, -33.7, -33.5, -33.4

#define OUTPUT_VOLUME_12dB  12.0, 10.4, 8.8, 7.1, 5.4, 3.6, 1.7, -0.2, -2.0, -3.9,            \
                           -5.8, -7.8, -9.7, -11.7, -13.6, -15.6, -17.6, -19.3, -20.4, -20.5, \
                           -20.2, -20.0, -19.8, -19.7, -19.6, -19.5, -19.5, -19.4, -19.4, -19.4, -19.4, -19.3
                           
#define OUTPUT_VOLUME_18dB  19.0, 17.0, 16.0, 15.0, 13.7, 12.4, 10.9, 9.4, 7.9, 6.2,  \
                             4.5, 2.7, 0.9, -0.9, -2.8, -4.7, -6.6, -7.3, -7.3, -7.1, \
                            -7.1, -7.1, -7.1, -7.0, -7.0, -7.0, -7.0, -7.0, -7.0, -7.0, -7.0, -7.0
                            
#define OUTPUT_VOLUME_24dB  24.0

/*! @} */ // audioamp11_volume_control

/**
 * @defgroup audioamp11_map AudioAMP 11 MikroBUS Map
 * @brief MikroBUS pin mapping of AudioAMP 11 Click driver.
 */

/**
 * @addtogroup audioamp11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AudioAMP 11 Click to the selected MikroBUS.
 */
#define AUDIOAMP11_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // audioamp11_map
/*! @} */ // audioamp11

/**
 * @brief AudioAMP 11 Click context object.
 * @details Context object definition of AudioAMP 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;         /**< Chip Enable pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} audioamp11_t;

/**
 * @brief AudioAMP 11 Click configuration object.
 * @details Configuration object definition of AudioAMP 11 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;             /**< Chip Enable pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} audioamp11_cfg_t;

/**
 * @brief AudioAMP 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AUDIOAMP11_OK = 0,
    AUDIOAMP11_ERROR = -1

} audioamp11_return_value_t;


/*!
 * @addtogroup audioamp11 AudioAMP 11 Click Driver
 * @brief API for configuring and manipulating AudioAMP 11 Click driver.
 * @{
 */

/**
 * @brief AudioAMP 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #audioamp11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void audioamp11_cfg_setup ( audioamp11_cfg_t *cfg );

/**
 * @brief AudioAMP 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #audioamp11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp11_init ( audioamp11_t *ctx, audioamp11_cfg_t *cfg );

/**
 * @brief AudioAMP 11 default configuration function.
 * @details This function executes a default configuration of AudioAMP 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t audioamp11_default_cfg ( audioamp11_t *ctx );

/**
 * @brief AudioAMP 11 I2C writing function.
 * @details This function writes a desired byte of data to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp11_generic_write ( audioamp11_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief AudioAMP 11 I2C reading function.
 * @details This function reads a desired byte of data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp11_generic_read ( audioamp11_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief AudioAMP 11 enable device function.
 * @details This function enables the NAU8224, 
 * 3.1W Stereo Filter-Free Class-D Audio Amplifier
 * with 2 wire interface gain control 
 * on the AudioAMP 11 Click board™. 
 * @param[in] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @return Nothing.
 * @note None
 */
void audioamp11_enable_device ( audioamp11_t *ctx );

/**
 * @brief AudioAMP 11 enable device function.
 * @details This function disables the NAU8224, 
 * 3.1W Stereo Filter-Free Class-D Audio Amplifier
 * with 2 wire interface gain control 
 * on the AudioAMP 11 Click board™. 
 * @param[in] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @return Nothing.
 * @note None
 */
void audioamp11_disable_device ( audioamp11_t *ctx );

/**
 * @brief AudioAMP 11 check gain function.
 * @details This function check the configuration of the GAIN pin
 * of the NAU8224, 3.1W Stereo Filter-Free Class-D Audio Amplifier
 * with 2 wire interface gain control on the AudioAMP 11 Click board™. 
 * @param[in] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @param[out] gain : Output gain data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp11_check_gain ( audioamp11_t *ctx, uint8_t *gain );

/**
 * @brief AudioAMP 11 get output volume level function.
 * @details This function reads output volume data  
 * from the NAU8224, 3.1W Stereo Filter-Free Class-D Audio Amplifier
 * with 2 wire interface gain control on the AudioAMP 11 Click board™. 
 * @param[in] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @param[out] volume_data : Output volume data [0x00-0x3F].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp11_get_output_volume_level ( audioamp11_t *ctx, uint8_t *volume_data );

/**
 * @brief AudioAMP 11 set output volume level function.
 * @details This function set output volume level data 
 * from the NAU8224, 3.1W Stereo Filter-Free Class-D Audio Amplifier
 * with 2 wire interface gain control on the AudioAMP 11 Click board™. 
 * @param[in] ctx : Click context object.
 * See #audioamp11_t object definition for detailed explanation.
 * @param[in] volume_data : Output volume data [0x00-0x3F].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp11_set_output_volume_level ( audioamp11_t *ctx, uint8_t volume_data );

#ifdef __cplusplus
}
#endif
#endif // AUDIOAMP11_H

/*! @} */ // audioamp11

// ------------------------------------------------------------------------ END
