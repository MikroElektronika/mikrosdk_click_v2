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
 * @file stepper10.h
 * @brief This file contains API for Stepper 10 Click Driver.
 */

#ifndef STEPPER10_H
#define STEPPER10_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup stepper10 Stepper 10 Click Driver
 * @brief API for configuring and manipulating Stepper 10 Click driver.
 * @{
 */

/**
 * @defgroup stepper10_reg Stepper 10 Registers List
 * @brief List of registers of Stepper 10 Click driver.
 */

/**
 * @addtogroup stepper10_reg
 * @{
 */

/**
 * @brief Stepper 10 TCA9534A registers.
 * @details Specified TCA9534A registers of Stepper 10 Click driver.
 */
#define STEPPER10_TCA9534A_REG_INPUT                0x00
#define STEPPER10_TCA9534A_REG_OUTPUT               0x01
#define STEPPER10_TCA9534A_REG_POLARITY             0x02
#define STEPPER10_TCA9534A_REG_CONFIG               0x03

/*! @} */ // stepper10_reg

/**
 * @defgroup stepper10_set Stepper 10 Registers Settings
 * @brief Settings for registers of Stepper 10 Click driver.
 */

/**
 * @addtogroup stepper10_set
 * @{
 */

/**
 * @brief Stepper 10 TCA9534A pin mask.
 * @details Specified TCA9534A pin mask of Stepper 10 Click driver.
 */
#define STEPPER10_PIN0_MS0                          0x01
#define STEPPER10_PIN0_MS1                          0x02
#define STEPPER10_PIN0_MS2                          0x04
#define STEPPER10_PIN0_MS_MASK                      0x07
#define STEPPER10_PIN0_SLEEP                        0x08
#define STEPPER10_PIN0_MDT0                         0x10
#define STEPPER10_PIN0_MDT1                         0x20
#define STEPPER10_PIN0_MDT_MASK                     0x30
#define STEPPER10_PIN0_AGC                          0x40
#define STEPPER10_PIN0_IF_SEL                       0x80
#define STEPPER10_PIN1_TORQUE0                      0x01
#define STEPPER10_PIN1_TORQUE1                      0x02
#define STEPPER10_PIN1_TORQUE2                      0x04
#define STEPPER10_PIN1_TORQUE_MASK                  0x07
#define STEPPER10_PIN1_CLIM0                        0x08
#define STEPPER10_PIN1_EDG_SEL                      0x10
#define STEPPER10_PIN1_MO                           0x20
#define STEPPER10_PIN1_LO0                          0x40
#define STEPPER10_PIN1_LO1                          0x80
#define STEPPER10_PIN1_LO_MASK                      0xC0

/**
 * @brief Stepper 10 TCA9534A pin direction config.
 * @details Specified TCA9534A pin direction config of Stepper 10 Click driver.
 */
#define STEPPER10_TCA9534A_0_DEFAULT_CONFIG         0x00
#define STEPPER10_TCA9534A_1_DEFAULT_CONFIG         0xE0

/**
 * @brief Stepper 10 direction setting.
 * @details Specified setting for direction of Stepper 10 Click driver.
 */
#define STEPPER10_DIR_CW                            0
#define STEPPER10_DIR_CCW                           1

/**
 * @brief Stepper 10 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 10 Click driver.
 */
#define STEPPER10_PIN_STATE_LOW                     0
#define STEPPER10_PIN_STATE_HIGH                    1

/**
 * @brief Stepper 10 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER10_SPEED_VERY_SLOW                   0
#define STEPPER10_SPEED_SLOW                        1
#define STEPPER10_SPEED_MEDIUM                      2
#define STEPPER10_SPEED_FAST                        3
#define STEPPER10_SPEED_VERY_FAST                   4

/**
 * @brief Stepper 10 step resolution setting.
 * @details Specified setting for step resolution of Stepper 10 Click driver.
 */
#define STEPPER10_MODE_FULL_STEP                    0
#define STEPPER10_MODE_HALF_STEP                    1
#define STEPPER10_MODE_QUARTER_STEP                 2
#define STEPPER10_MODE_1_OVER_8                     3
#define STEPPER10_MODE_1_OVER_16                    4
#define STEPPER10_MODE_1_OVER_32                    5
#define STEPPER10_MODE_1_OVER_64                    6
#define STEPPER10_MODE_1_OVER_128                   7

/**
 * @brief Stepper 10 mixed decay setting.
 * @details Specified setting for mixed decay of Stepper 10 Click driver.
 */
#define STEPPER10_MIXED_DECAY_FAST_37_5             0
#define STEPPER10_MIXED_DECAY_FAST_50               1
#define STEPPER10_MIXED_DECAY_FAST_ONLY             2
#define STEPPER10_MIXED_DECAY_ADMD                  3

/**
 * @brief Stepper 10 torque setting.
 * @details Specified setting for torque of Stepper 10 Click driver.
 */
#define STEPPER10_TORQUE_100                        0
#define STEPPER10_TORQUE_85                         1
#define STEPPER10_TORQUE_70                         2
#define STEPPER10_TORQUE_60                         3
#define STEPPER10_TORQUE_50                         4
#define STEPPER10_TORQUE_40                         5
#define STEPPER10_TORQUE_25                         6
#define STEPPER10_TORQUE_10                         7

/**
 * @brief Stepper 10 LO error detect flag setting.
 * @details Specified setting for LO error detect flag of Stepper 10 Click driver.
 */
#define STEPPER10_LO_THERMAL_SHUTDOWN               0
#define STEPPER10_LO_MOTOR_LOAD_OPEN                1
#define STEPPER10_LO_OVER_CURRENT                   2
#define STEPPER10_LO_NORMAL                         3

/**
 * @brief Stepper 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 10 Click driver.
 */
#define STEPPER10_DEVICE0_ADDRESS_A2A1_00           0x38
#define STEPPER10_DEVICE0_ADDRESS_A2A1_01           0x3A
#define STEPPER10_DEVICE0_ADDRESS_A2A1_10           0x3C
#define STEPPER10_DEVICE0_ADDRESS_A2A1_11           0x3E
#define STEPPER10_DEVICE1_ADDRESS_A2A1_00           0x39
#define STEPPER10_DEVICE1_ADDRESS_A2A1_01           0x3B
#define STEPPER10_DEVICE1_ADDRESS_A2A1_10           0x3D
#define STEPPER10_DEVICE1_ADDRESS_A2A1_11           0x3F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b stepper10_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define STEPPER10_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define STEPPER10_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // stepper10_set

/**
 * @defgroup stepper10_map Stepper 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 10 Click driver.
 */

/**
 * @addtogroup stepper10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 10 Click to the selected MikroBUS.
 */
#define STEPPER10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper10_map
/*! @} */ // stepper10

/**
 * @brief Stepper 10 Click context object.
 * @details Context object definition of Stepper 10 Click driver.
 */
typedef struct stepper10_s
{
    digital_out_t dir;              /**< Direction control pin. */
    digital_out_t rst;              /**< Electric angle reset pin. */
    digital_out_t step;             /**< Step signal pin. */
    digital_out_t en;               /**< Enable output pin. */

    digital_in_t int_pin;           /**< TCA9534A interrupt pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} stepper10_t;

/**
 * @brief Stepper 10 Click configuration object.
 * @details Configuration object definition of Stepper 10 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t en;                  /**< Enable output pin. */
    pin_name_t dir;                 /**< Direction control pin. */
    pin_name_t rst;                 /**< Electric angle reset pin. */
    pin_name_t step;                /**< Step signal pin. */
    pin_name_t int_pin;             /**< TCA9534A interrupt pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t   spi_speed;           /**< SPI serial speed. */
    spi_master_mode_t spi_mode;     /**< SPI master mode. */

} stepper10_cfg_t;

/**
 * @brief Stepper 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER10_OK = 0,
    STEPPER10_ERROR = -1

} stepper10_return_value_t;

/*!
 * @addtogroup stepper10 Stepper 10 Click Driver
 * @brief API for configuring and manipulating Stepper 10 Click driver.
 * @{
 */

/**
 * @brief Stepper 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper10_cfg_setup ( stepper10_cfg_t *cfg );

/**
 * @brief Stepper 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_init ( stepper10_t *ctx, stepper10_cfg_t *cfg );

/**
 * @brief Stepper 10 default configuration function.
 * @details This function executes a default configuration of Stepper 10
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper10_default_cfg ( stepper10_t *ctx );

/**
 * @brief Stepper 10 write spi bank0 function.
 * @details This function writes a 32-bit command to BANK0 by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] data_in : 32-bit SPI data command, D0-D31, where D0 is a MSB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The stepper10_select_spi command needs to be called before this function call.
 */
err_t stepper10_write_spi_bank0 ( stepper10_t *ctx, uint32_t data_in );

/**
 * @brief Stepper 10 write spi bank1 function.
 * @details This function writes a 32-bit command to BANK1 by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] data_in : 32-bit SPI data command, D0-D31, where D0 is a MSB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The stepper10_select_spi command needs to be called before this function call.
 */
err_t stepper10_write_spi_bank1 ( stepper10_t *ctx, uint32_t data_in );

/**
 * @brief Stepper 10 tca write reg function.
 * @details This function writes a desired data byte to the selected TCA9534A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_tca_write_reg ( stepper10_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 10 tca read reg function.
 * @details This function reads data from the selected TCA9534A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_tca_read_reg ( stepper10_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 10 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution:
 *                   @li @c 0 - Full step resolution (2-phase excitation),
 *                   @li @c 1 - 1/2 step resolution (1-2-phase excitation),
 *                   @li @c 2 - 1/4 step resolution (W1-2-phase excitation),
 *                   @li @c 3 - 1/8 step resolution (2W1-2-phase excitation),
 *                   @li @c 4 - 1/16 step resolution (4W1-2-phase excitation),
 *                   @li @c 5 - 1/32 step resolution (8W1-2-phase excitation),
 *                   @li @c 6 - 1/64 step resolution (16W1-2-phase excitation),
 *                   @li @c 7 - 1/128 step resolution (32W1-2-phase excitation).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_step_mode ( stepper10_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 10 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution:
 *                   @li @c 0 - Full step resolution (2-phase excitation),
 *                   @li @c 1 - 1/2 step resolution (1-2-phase excitation),
 *                   @li @c 2 - 1/4 step resolution (W1-2-phase excitation),
 *                   @li @c 3 - 1/8 step resolution (2W1-2-phase excitation),
 *                   @li @c 4 - 1/16 step resolution (4W1-2-phase excitation),
 *                   @li @c 5 - 1/32 step resolution (8W1-2-phase excitation),
 *                   @li @c 6 - 1/64 step resolution (16W1-2-phase excitation),
 *                   @li @c 7 - 1/128 step resolution (32W1-2-phase excitation).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_set_step_mode ( stepper10_t *ctx, uint8_t mode );

/**
 * @brief Stepper 10 get sleep pin function.
 * @details This function reads the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_sleep_pin ( stepper10_t *ctx, uint8_t *state );

/**
 * @brief Stepper 10 set sleep pin function.
 * @details This function sets the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_set_sleep_pin ( stepper10_t *ctx, uint8_t state );

/**
 * @brief Stepper 10 get mixed decay function.
 * @details This function reads the mixed decay settings.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] mode : Mixed decay mode:
 *                   @li @c 0 - Fast Decay: 37.5% (Fast Decay = OSCM × 6),
 *                   @li @c 1 - Fast Decay: 50% (Fast Decay = OSCM × 8),
 *                   @li @c 2 - Fast Decay only,
 *                   @li @c 3 - ADMD.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_mixed_decay ( stepper10_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 10 set mixed decay function.
 * @details This function sets the mixed decay settings.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] mode : Mixed decay mode:
 *                   @li @c 0 - Fast Decay: 37.5% (Fast Decay = OSCM × 6),
 *                   @li @c 1 - Fast Decay: 50% (Fast Decay = OSCM × 8),
 *                   @li @c 2 - Fast Decay only,
 *                   @li @c 3 - ADMD.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_set_mixed_decay ( stepper10_t *ctx, uint8_t mode );

/**
 * @brief Stepper 10 get agc pin function.
 * @details This function reads the agc pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_agc_pin ( stepper10_t *ctx, uint8_t *state );

/**
 * @brief Stepper 10 set agc pin function.
 * @details This function sets the agc pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_set_agc_pin ( stepper10_t *ctx, uint8_t state );

/**
 * @brief Stepper 10 select GPIO function.
 * @details This function selects GPIO communication by setting the IF_SEL pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_select_gpio ( stepper10_t *ctx );

/**
 * @brief Stepper 10 select SPI function.
 * @details This function selects SPI communication by setting the IF_SEL pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_select_spi ( stepper10_t *ctx );

/**
 * @brief Stepper 10 get torque function.
 * @details This function reads the torque mode settings.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] mode : Torque settings:
 *                   @li @c 0 - 100%,
 *                   @li @c 1 - 85%,
 *                   @li @c 2 - 70%,
 *                   @li @c 3 - 60%,
 *                   @li @c 4 - 50%,
 *                   @li @c 5 - 40%,
 *                   @li @c 6 - 25%,
 *                   @li @c 7 - 10%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_torque ( stepper10_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 10 set torque function.
 * @details This function sets the torque mode settings.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] mode : Torque settings:
 *                   @li @c 0 - 100%,
 *                   @li @c 1 - 85%,
 *                   @li @c 2 - 70%,
 *                   @li @c 3 - 60%,
 *                   @li @c 4 - 50%,
 *                   @li @c 5 - 40%,
 *                   @li @c 6 - 25%,
 *                   @li @c 7 - 10%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_set_torque ( stepper10_t *ctx, uint8_t mode );

/**
 * @brief Stepper 10 get clim0 pin function.
 * @details This function reads the CLIM0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_clim0_pin ( stepper10_t *ctx, uint8_t *state );

/**
 * @brief Stepper 10 set clim0 pin function.
 * @details This function sets the CLIM0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_set_clim0_pin ( stepper10_t *ctx, uint8_t state );

/**
 * @brief Stepper 10 get edg_sel pin function.
 * @details This function reads the EDG_SEL pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_edg_sel_pin ( stepper10_t *ctx, uint8_t *state );

/**
 * @brief Stepper 10 set edg_sel pin function.
 * @details This function sets the EDG_SEL pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_set_edg_sel_pin ( stepper10_t *ctx, uint8_t state );

/**
 * @brief Stepper 10 get mo pin function.
 * @details This function reads the MO pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_mo_pin ( stepper10_t *ctx, uint8_t *state );

/**
 * @brief Stepper 10 get LO function.
 * @details This function reads the LO error detect flag state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[out] state : LO error detect flag:
 *                     @li @c 0 - Detected thermal shutdown (TSD),
 *                     @li @c 1 - Detected motor load open (OPD),
 *                     @li @c 2 - Detected over current (ISD),
 *                     @li @c 3 - Normal status (Normal operation).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_get_lo_state ( stepper10_t *ctx, uint8_t *state );

/**
 * @brief Stepper 10 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper10_enable_device ( stepper10_t *ctx );

/**
 * @brief Stepper 10 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper10_disable_device ( stepper10_t *ctx );

/**
 * @brief Stepper 10 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper10_get_int_pin ( stepper10_t *ctx );

/**
 * @brief Stepper 10 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper10_set_direction ( stepper10_t *ctx, uint8_t dir );

/**
 * @brief Stepper 10 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper10_set_rst_pin ( stepper10_t *ctx, uint8_t state );

/**
 * @brief Stepper 10 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper10_reset_device ( stepper10_t *ctx );

/**
 * @brief Stepper 10 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper10_set_step_pin ( stepper10_t *ctx, uint8_t state );

/**
 * @brief Stepper 10 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper10_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper10_drive_motor ( stepper10_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER10_H

/*! @} */ // stepper10

// ------------------------------------------------------------------------ END
