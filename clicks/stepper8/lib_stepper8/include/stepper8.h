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
 * @file stepper8.h
 * @brief This file contains API for Stepper 8 Click Driver.
 */

#ifndef STEPPER8_H
#define STEPPER8_H

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
 * @addtogroup stepper8 Stepper 8 Click Driver
 * @brief API for configuring and manipulating Stepper 8 Click driver.
 * @{
 */

/**
 * @defgroup stepper8_reg Stepper 8 Registers List
 * @brief List of registers of Stepper 8 Click driver.
 */

/**
 * @addtogroup stepper8_reg
 * @{
 */

/**
 * @brief Stepper 8 PCA9538A registers.
 * @details Specified PCA9538A registers of Stepper 8 Click driver.
 */
#define STEPPER8_PCA9538A_REG_INPUT             0x00
#define STEPPER8_PCA9538A_REG_OUTPUT            0x01
#define STEPPER8_PCA9538A_REG_POLARITY          0x02
#define STEPPER8_PCA9538A_REG_CONFIG            0x03

/*! @} */ // stepper8_reg

/**
 * @defgroup stepper8_set Stepper 8 Registers Settings
 * @brief Settings for registers of Stepper 8 Click driver.
 */

/**
 * @addtogroup stepper8_set
 * @{
 */

/**
 * @brief Stepper 8 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Stepper 8 Click driver.
 */
#define STEPPER8_PIN_STBY                       0x01
#define STEPPER8_PIN_SELECT                     0x02
#define STEPPER8_PIN_EN                         0x04

/**
 * @brief Stepper 8 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Stepper 8 Click driver.
 */
#define STEPPER8_PCA9538A_DEFAULT_CONFIG        0xF8

/**
 * @brief Stepper 8 direction setting.
 * @details Specified setting for direction of Stepper 8 Click driver.
 */
#define STEPPER8_DIR_CW                         0
#define STEPPER8_DIR_CCW                        1

/**
 * @brief Stepper 8 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 8 Click driver.
 */
#define STEPPER8_PIN_STATE_LOW                  0
#define STEPPER8_PIN_STATE_HIGH                 1

/**
 * @brief Stepper 8 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER8_SPEED_VERY_SLOW                0
#define STEPPER8_SPEED_SLOW                     1
#define STEPPER8_SPEED_MEDIUM                   2
#define STEPPER8_SPEED_FAST                     3
#define STEPPER8_SPEED_VERY_FAST                4

/**
 * @brief Stepper 8 step resolution setting.
 * @details Specified setting for step resolution of Stepper 8 Click driver.
 */
#define STEPPER8_MODE_FULL_STEP                 0
#define STEPPER8_MODE_HALF_STEP                 1
#define STEPPER8_MODE_QUARTER_STEP              2
#define STEPPER8_MODE_1_OVER_8                  3
#define STEPPER8_MODE_1_OVER_16                 4
#define STEPPER8_MODE_1_OVER_32                 5
#define STEPPER8_MODE_1_OVER_64                 6
#define STEPPER8_MODE_1_OVER_128                7

/**
 * @brief Stepper 8 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 8 Click driver.
 */
#define STEPPER8_DEVICE_ADDRESS_A1A0_00         0x70
#define STEPPER8_DEVICE_ADDRESS_A1A0_01         0x71
#define STEPPER8_DEVICE_ADDRESS_A1A0_10         0x72
#define STEPPER8_DEVICE_ADDRESS_A1A0_11         0x73

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b stepper8_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define STEPPER8_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define STEPPER8_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // stepper8_set

/**
 * @defgroup stepper8_map Stepper 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 8 Click driver.
 */

/**
 * @addtogroup stepper8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 8 Click to the selected MikroBUS.
 */
#define STEPPER8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.md1  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.md3  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.md0  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.md2  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.err  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper8_map
/*! @} */ // stepper8

/**
 * @brief Stepper 8 Click context object.
 * @details Context object definition of Stepper 8 Click driver.
 */
typedef struct stepper8_s
{
    digital_out_t md0;          /**< MODE0/UP-DW pin. */
    digital_out_t md1;          /**< MODE1/SET_EN/LATCH pin. */
    digital_out_t md2;          /**< MODE2/CLK pin. */
    digital_out_t md3;          /**< MODE3/CW-CCW pin. */

    digital_in_t err;           /**< ERR pin. */

    i2c_master_t i2c;           /**< I2C driver object. */
    spi_master_t spi;           /**< SPI driver object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t dir;                /**< Direction mode. */

} stepper8_t;

/**
 * @brief Stepper 8 Click configuration object.
 * @details Configuration object definition of Stepper 8 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t md0;             /**< MODE0/UP-DW pin. */
    pin_name_t md1;             /**< MODE1/SET_EN/LATCH pin. */
    pin_name_t md2;             /**< MODE2/CLK pin. */
    pin_name_t md3;             /**< MODE3/CW-CCW pin. */
    pin_name_t err;             /**< ERR pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t            spi_speed;  /**< SPI serial speed. */
    spi_master_mode_t   spi_mode;   /**< SPI master mode. */

} stepper8_cfg_t;

/**
 * @brief Stepper 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER8_OK = 0,
    STEPPER8_ERROR = -1

} stepper8_return_value_t;

/*!
 * @addtogroup stepper8 Stepper 8 Click Driver
 * @brief API for configuring and manipulating Stepper 8 Click driver.
 * @{
 */

/**
 * @brief Stepper 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper8_cfg_setup ( stepper8_cfg_t *cfg );

/**
 * @brief Stepper 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_init ( stepper8_t *ctx, stepper8_cfg_t *cfg );

/**
 * @brief Stepper 8 default configuration function.
 * @details This function executes a default configuration of Stepper 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper8_default_cfg ( stepper8_t *ctx );

/**
 * @brief Stepper 8 write spi function.
 * @details This function writes a 32-bit command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] data_in : 32-bit SPI data command, D0-D31, where D0 is a MSB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The stepper8_select_spi command needs to be called before this function call.
 */
err_t stepper8_write_spi ( stepper8_t *ctx, uint32_t data_in );

/**
 * @brief Stepper 8 pca write reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_pca_write_reg ( stepper8_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 8 pca read reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_pca_read_reg ( stepper8_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 8 enable standby function.
 * @details This function enables the standby by setting the STBY pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_enable_standby ( stepper8_t *ctx );

/**
 * @brief Stepper 8 disable standby function.
 * @details This function disables the standby by setting the STBY pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_disable_standby ( stepper8_t *ctx );

/**
 * @brief Stepper 8 select GPIO function.
 * @details This function selects GPIO communication by setting the SELECT pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_select_gpio ( stepper8_t *ctx );

/**
 * @brief Stepper 8 select SPI function.
 * @details This function selects SPI communication by setting the SELECT pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_select_spi ( stepper8_t *ctx );

/**
 * @brief Stepper 8 disable device function.
 * @details This function disables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_disable_device ( stepper8_t *ctx );

/**
 * @brief Stepper 8 enable device function.
 * @details This function enables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper8_enable_device ( stepper8_t *ctx );

/**
 * @brief Stepper 8 set MD0 pin function.
 * @details This function sets the MD0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper8_set_md0_pin ( stepper8_t *ctx, uint8_t state );

/**
 * @brief Stepper 8 set MD1 pin function.
 * @details This function sets the MD1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper8_set_md1_pin ( stepper8_t *ctx, uint8_t state );

/**
 * @brief Stepper 8 set MD2 pin function.
 * @details This function sets the MD2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper8_set_md2_pin ( stepper8_t *ctx, uint8_t state );

/**
 * @brief Stepper 8 set MD3 pin function.
 * @details This function sets the MD3 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper8_set_md3_pin ( stepper8_t *ctx, uint8_t state );

/**
 * @brief Stepper 8 get ERR pin function.
 * @details This function returns the ERR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper8_get_err_pin ( stepper8_t *ctx );

/**
 * @brief Stepper 8 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper8_set_direction ( stepper8_t *ctx, uint8_t dir );

/**
 * @brief Stepper 8 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper8_set_rst_pin ( stepper8_t *ctx, uint8_t state );

/**
 * @brief Stepper 8 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper8_set_step_pin ( stepper8_t *ctx, uint8_t state );

/**
 * @brief Stepper 8 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
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
err_t stepper8_set_step_mode ( stepper8_t *ctx, uint8_t mode );

/**
 * @brief Stepper 8 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper8_t object definition for detailed explanation.
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
err_t stepper8_drive_motor ( stepper8_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER8_H

/*! @} */ // stepper8

// ------------------------------------------------------------------------ END
