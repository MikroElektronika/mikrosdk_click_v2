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
 * @file light4.h
 * @brief This file contains API for Light 4 Click Driver.
 */

#ifndef LIGHT4_H
#define LIGHT4_H

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
 * @addtogroup light4 Light 4 Click Driver
 * @brief API for configuring and manipulating Light 4 Click driver.
 * @{
 */

/**
 * @defgroup light4_reg Light 4 Registers List
 * @brief List of registers of Light 4 Click driver.
 */

/**
 * @addtogroup light4_reg
 * @{
 */

/**
 * @brief Light 4 description register.
 * @details Specified register for description of Light 4 Click driver.
 */
#define LIGHT4_REG_UV_CALIB                         0x08
#define LIGHT4_REG_MOD_CHANNEL_CTRL                 0x40
#define LIGHT4_REG_ENABLE                           0x80
#define LIGHT4_REG_MEAS_MODE0                       0x81
#define LIGHT4_REG_MEAS_MODE1                       0x82
#define LIGHT4_REG_SAMPLE_TIME0                     0x83
#define LIGHT4_REG_SAMPLE_TIME1                     0x84
#define LIGHT4_REG_ALS_NR_SAMPLES0                  0x85
#define LIGHT4_REG_ALS_NR_SAMPLES1                  0x86
#define LIGHT4_REG_FD_NR_SAMPLES0                   0x87
#define LIGHT4_REG_FD_NR_SAMPLES1                   0x88
#define LIGHT4_REG_WTIME                            0x89
#define LIGHT4_REG_AILT0                            0x8A
#define LIGHT4_REG_AILT1                            0x8B
#define LIGHT4_REG_AILT2                            0x8C
#define LIGHT4_REG_AIHT0                            0x8D
#define LIGHT4_REG_AIHT1                            0x8B
#define LIGHT4_REG_AIHT2                            0x8F
#define LIGHT4_REG_AUX_ID                           0x90
#define LIGHT4_REG_REV_ID                           0x91
#define LIGHT4_REG_ID                               0x92
#define LIGHT4_REG_STATUS                           0x93
#define LIGHT4_REG_ALS_STATUS                       0x94
#define LIGHT4_REG_ALS_DATA0_LSB                    0x95
#define LIGHT4_REG_ALS_DATA0_MSB                    0x96
#define LIGHT4_REG_ALS_DATA1_LSB                    0x97
#define LIGHT4_REG_ALS_DATA1_MSB                    0x98
#define LIGHT4_REG_ALS_DATA2_LSB                    0x99
#define LIGHT4_REG_ALS_DATA2_MSB                    0x9A
#define LIGHT4_REG_ALS_STATUS2                      0x9B
#define LIGHT4_REG_ALS_STATUS3                      0x9C
#define LIGHT4_REG_STATUS2                          0x9D
#define LIGHT4_REG_STATUS3                          0x9E
#define LIGHT4_REG_STATUS4                          0x9F
#define LIGHT4_REG_STATUS5                          0xA0
#define LIGHT4_REG_CFG0                             0xA1
#define LIGHT4_REG_CFG1                             0xA2
#define LIGHT4_REG_CFG2                             0xA3
#define LIGHT4_REG_CFG3                             0xA4
#define LIGHT4_REG_CFG4                             0xA5
#define LIGHT4_REG_CFG5                             0xA6
#define LIGHT4_REG_CFG6                             0xA7
#define LIGHT4_REG_CFG7                             0xA8
#define LIGHT4_REG_CFG8                             0xA9
#define LIGHT4_REG_CFG9                             0xAA
#define LIGHT4_REG_AGC_NR_SAMPLES_LSB               0xAC
#define LIGHT4_REG_AGC_NR_SAMPLES_MSB               0xAD
#define LIGHT4_REG_TRIGGER_MODE                     0xAE
#define LIGHT4_REG_CONTROL                          0xB1
#define LIGHT4_REG_INTENAB                          0xBA
#define LIGHT4_REG_SIEN                             0xBB
#define LIGHT4_REG_MOD_COMP_CFG1                    0xCE
#define LIGHT4_REG_MEAS_SEQR_FD_0                   0xCF
#define LIGHT4_REG_MEAS_SEQR_ALS_FD_1               0xD0
#define LIGHT4_REG_MEAS_SEQR_APERS_AND_VSYNC_WAIT   0xD1
#define LIGHT4_REG_MEAS_SEQR_RESIDUAL_0             0xD2
#define LIGHT4_REG_MEAS_SEQR_RESIDUAL_1_AND_WAIT    0xD3
#define LIGHT4_REG_MEAS_SEQR_STEP0_MOD_GAINX_L      0xD4
#define LIGHT4_REG_MEAS_SEQR_STEP0_MOD_GAINX_H      0xD5
#define LIGHT4_REG_MEAS_SEQR_STEP1_MOD_GAINX_L      0xD6
#define LIGHT4_REG_MEAS_SEQR_STEP1_MOD_GAINX_H      0xD7
#define LIGHT4_REG_MEAS_SEQR_STEP2_MOD_GAINX_L      0xD8
#define LIGHT4_REG_MEAS_SEQR_STEP2_MOD_GAINX_H      0xD9
#define LIGHT4_REG_MEAS_SEQR_STEP3_MOD_GAINX_L      0xDA
#define LIGHT4_REG_MEAS_SEQR_STEP3_MOD_GAINX_H      0xDB
#define LIGHT4_REG_MEAS_SEQR_STEP0_MOD_PHDX_L       0xDC
#define LIGHT4_REG_MEAS_SEQR_STEP0_MOD_PHDX_H       0xDD
#define LIGHT4_REG_MEAS_SEQR_STEP1_MOD_PHDX_L       0xDE
#define LIGHT4_REG_MEAS_SEQR_STEP1_MOD_PHDX_H       0xDF
#define LIGHT4_REG_MEAS_SEQR_STEP2_MOD_PHDX_L       0xE0
#define LIGHT4_REG_MEAS_SEQR_STEP2_MOD_PHDX_H       0xE1
#define LIGHT4_REG_MEAS_SEQR_STEP3_MOD_PHDX_L       0xE2
#define LIGHT4_REG_MEAS_SEQR_STEP3_MOD_PHDX_H       0xE3
#define LIGHT4_REG_MOD_CALIB_CFG0                   0xE4
#define LIGHT4_REG_MOD_CALIB_CFG2                   0xE6
#define LIGHT4_REG_VSYNC_PERIOD_LSB                 0xF2
#define LIGHT4_REG_VSYNC_PERIOD_MSB                 0xF3
#define LIGHT4_REG_VSYNC_PERIOD_TARGET_LSB          0xF4
#define LIGHT4_REG_VSYNC_PERIOD_TARGET_MSB          0xF5
#define LIGHT4_REG_VSYNC_CONTROL                    0xF6
#define LIGHT4_REG_VSYNC_CFG                        0xF7
#define LIGHT4_REG_VSYNC_GPIO_INT                   0xF8
#define LIGHT4_REG_MOD_FIFO_DATA_CFG0               0xF9
#define LIGHT4_REG_MOD_FIFO_DATA_CFG1               0xFA
#define LIGHT4_REG_MOD_FIFO_DATA_CFG2               0xFB
#define LIGHT4_REG_FIFO_THR                         0xDC
#define LIGHT4_REG_FIFO_STATUS0                     0xFD
#define LIGHT4_REG_FIFO_STATUS1                     0xFE
#define LIGHT4_REG_FIFO_DATA                        0xFF

/*! @} */ // light4_reg

/**
 * @defgroup light4_set Light 4 Registers Settings
 * @brief Settings for registers of Light 4 Click driver.
 */

/**
 * @addtogroup light4_set
 * @{
 */

/**
 * @brief Light 4 description setting.
 * @details Specified setting for description of Light 4 Click driver.
 */
#define LIGHT4_FDEN                                 0x40
#define LIGHT4_AEN                                  0x02
#define LIGHT4_PON                                  0x01

/**
 * @brief Light 4 MOD_CHANNEL_CTRL register setting.
 * @details Specified setting for MOD_CHANNEL_CTRL register of Light 4 Click driver.
 */
#define LIGHT4_MOD2_DISABLE                         0x04
#define LIGHT4_MOD1_DISABLE                         0x02
#define LIGHT4_MOD0_DISABLE                         0x01
#define LIGHT4_MOD_ENABLE_ALL                       0x00

/**
 * @brief Light 4 ENABLE register setting.
 * @details Specified setting for ENABLE register of Light 4 Click driver.
 */
#define LIGHT4_MIEN                                 0x80
#define LIGHT4_AIEN                                 0x04
#define LIGHT4_FIEN                                 0x02
#define LIGHT4_SIEN                                 0x01

/**
 * @brief Light 4 CONTROL register setting.
 * @details Specified setting for CONTROL register of Light 4 Click driver.
 */
#define LIGHT4_SOFT_RESET                           0x08
#define LIGHT4_FIFO_CLR                             0x02
#define LIGHT4_CLEAR_SAI_ACTIVE                     0x01

/**
 * @brief Light 4 ALS_STATUS register setting.
 * @details Specified setting for ALS_STATUS register of Light 4 Click driver.
 */
#define LIGHT4_MEAS_SEQR_STEP_MASK                  0xC0
#define LIGHT4_ALS_DATA0_ANALOG_SATURATION_STATUS   0x20
#define LIGHT4_ALS_DATA1_ANALOG_SATURATION_STATUS   0x10
#define LIGHT4_ALS_DATA2_ANALOG_SATURATION_STATUS   0x08
#define LIGHT4_ALS_DATA0_SCALED_STATUS              0x04
#define LIGHT4_ALS_DATA1_SCALED_STATUS              0x02
#define LIGHT4_ALS_DATA2_SCALED_STATUS              0x01

/**
 * @brief Light 4 Pin state setting.
 * @details Specified setting for Pin state of Light 4 Click driver.
 */
#define LIGHT4_PIN_STATE_HIGH                       0x01
#define LIGHT4_PIN_STATE_LOW                        0x00

/**
 * @brief Light 4 Device ID setting.
 * @details Specified setting for Device ID of Light 4 Click driver.
 */
#define LIGHT4_AUX_ID                               0x06
#define LIGHT4_REV_ID                               0x11
#define LIGHT4_DEVICE_ID                            0x5C

/**
 * @brief Light 4 Channel selection setting.
 * @details Specified setting for channel selection of Light 4 Click driver.
 */
#define LIGHT4_CHANNEL0_SEL                         0x00
#define LIGHT4_CHANNEL1_SEL                         0x01
#define LIGHT4_CHANNEL2_SEL                         0x02

/**
 * @brief Light 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Light 4 Click driver.
 */
#define LIGHT4_DEVICE_ADDRESS                       0x39

/*! @} */ // light4_set

/**
 * @defgroup light4_map Light 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Light 4 Click driver.
 */

/**
 * @addtogroup light4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Light 4 Click to the selected MikroBUS.
 */
#define LIGHT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.snc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // light4_map
/*! @} */ // light4

/**
 * @brief Light 4 Click context object.
 * @details Context object definition of Light 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */
    digital_out_t snc;          /**< Synchronization pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} light4_t;

/**
 * @brief Light 4 Click configuration object.
 * @details Configuration object definition of Light 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin. */
    pin_name_t snc;             /**< Synchronization pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} light4_cfg_t;

/**
 * @brief Light 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHT4_OK = 0,
    LIGHT4_ERROR = -1,
    LIGHT4_ANALOG_SAT = -2

} light4_return_value_t;

/*!
 * @addtogroup light4 Light 4 Click Driver
 * @brief API for configuring and manipulating Light 4 Click driver.
 * @{
 */

/**
 * @brief Light 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #light4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void light4_cfg_setup ( light4_cfg_t *cfg );

/**
 * @brief Light 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #light4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light4_init ( light4_t *ctx, light4_cfg_t *cfg );

/**
 * @brief Light 4 default configuration function.
 * @details This function executes a default configuration of Light 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t light4_default_cfg ( light4_t *ctx );

/**
 * @brief Light 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light4_generic_write ( light4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Light 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light4_generic_read ( light4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Light 4 set EN pin function.
 * @details This function sets the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void light4_set_en_pin ( light4_t *ctx, uint8_t pin_state );

/**
 * @brief Light 4 set SNC pin function.
 * @details This function sets the SNC pin logic state.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void light4_set_snc_pin ( light4_t *ctx, uint8_t pin_state );

/**
 * @brief  Light 4 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t light4_get_int_pin ( light4_t *ctx );

/**
 * @brief Light 4 Register writing function.
 * @details This function writes a byte into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light4_write_reg ( light4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Light 4 Register reading function.
 * @details This function reads a data byte from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light4_read_reg ( light4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Light 4 Software reset function.
 * @details This function is used to perform software reset 
 * of Light 4 Click board.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light4_sw_reset ( light4_t *ctx );

/**
 * @brief Light 4 get channel data function.
 * @details This function is used to read data from selected channel 
 * of Light 4 Click board.
 * @param[in] ctx : Click context object.
 * See #light4_t object definition for detailed explanation.
 * @param[in] channel_sel : Channel selection.
 * @param[out] channel_data : Read channel data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light4_read_channel_data ( light4_t *ctx, uint8_t channel_sel, float *channel_data );

#ifdef __cplusplus
}
#endif
#endif // LIGHT4_H

/*! @} */ // light4

// ------------------------------------------------------------------------ END
