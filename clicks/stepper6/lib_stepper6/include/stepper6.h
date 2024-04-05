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
 * @file stepper6.h
 * @brief This file contains API for Stepper 6 Click Driver.
 */

#ifndef STEPPER6_H
#define STEPPER6_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup stepper6 Stepper 6 Click Driver
 * @brief API for configuring and manipulating Stepper 6 Click driver.
 * @{
 */

/**
 * @defgroup stepper6_reg Stepper 6 Registers List
 * @brief List of registers of Stepper 6 Click driver.
 */

/**
 * @addtogroup stepper6_reg
 * @{
 */

/**
 * @brief Stepper 6 PCA9538A registers.
 * @details Specified PCA9538A registers of Stepper 6 Click driver.
 */
#define STEPPER6_PCA9538A_REG_INPUT             0x00
#define STEPPER6_PCA9538A_REG_OUTPUT            0x01
#define STEPPER6_PCA9538A_REG_POLARITY          0x02
#define STEPPER6_PCA9538A_REG_CONFIG            0x03

/*! @} */ // stepper6_reg

/**
 * @defgroup stepper6_set Stepper 6 Registers Settings
 * @brief Settings for registers of Stepper 6 Click driver.
 */

/**
 * @addtogroup stepper6_set
 * @{
 */

/**
 * @brief Stepper 6 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Stepper 6 Click driver.
 */
#define STEPPER6_PIN_TRQ                        0x01
#define STEPPER6_PIN_M1                         0x02
#define STEPPER6_PIN_M0                         0x04
#define STEPPER6_PIN_SLEEP                      0x08
#define STEPPER6_PIN_FAULT                      0x10

/**
 * @brief Stepper 6 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Stepper 6 Click driver.
 */
#define STEPPER6_PCA9538A_DEFAULT_CONFIG        0xF0

/**
 * @brief Stepper 6 direction setting.
 * @details Specified setting for direction of Stepper 6 Click driver.
 */
#define STEPPER6_DIR_CW                         0
#define STEPPER6_DIR_CCW                        1

/**
 * @brief Stepper 6 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 6 Click driver.
 */
#define STEPPER6_PIN_STATE_LOW                  0
#define STEPPER6_PIN_STATE_HIGH                 1
#define STEPPER6_PIN_STATE_OPEN                 2

/**
 * @brief Stepper 6 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER6_SPEED_VERY_SLOW                0
#define STEPPER6_SPEED_SLOW                     1
#define STEPPER6_SPEED_MEDIUM                   2
#define STEPPER6_SPEED_FAST                     3
#define STEPPER6_SPEED_VERY_FAST                4

/**
 * @brief Stepper 6 step resolution setting.
 * @details Specified setting for step resolution of Stepper 6 Click driver.
 */
#define STEPPER6_MODE_FULL_STEP                 0
#define STEPPER6_MODE_1_OVER_16                 1
#define STEPPER6_MODE_HALF_STEP                 2
#define STEPPER6_MODE_QUARTER_STEP              3
#define STEPPER6_MODE_1_OVER_8                  4
#define STEPPER6_MODE_HALF_NON_CIRC_STEP        5

/**
 * @brief Stepper 6 DAC default setting.
 * @details Specified DAC default setting of Stepper 6 Click driver.
 */
#define STEPPER6_DAC_DEFAULT_CONFIG             0x7FFFu

/**
 * @brief Stepper 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 6 Click driver.
 */
#define STEPPER6_DEVICE_ADDRESS_A1A0_00         0x70
#define STEPPER6_DEVICE_ADDRESS_A1A0_01         0x71
#define STEPPER6_DEVICE_ADDRESS_A1A0_10         0x72
#define STEPPER6_DEVICE_ADDRESS_A1A0_11         0x73

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b stepper6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define STEPPER6_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define STEPPER6_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // stepper6_set

/**
 * @defgroup stepper6_map Stepper 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 6 Click driver.
 */

/**
 * @addtogroup stepper6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 6 Click to the selected MikroBUS.
 */
#define STEPPER6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dir  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper6_map
/*! @} */ // stepper6

/**
 * @brief Stepper 6 Click context object.
 * @details Context object definition of Stepper 6 Click driver.
 */
typedef struct stepper6_s
{
    digital_out_t step;         /**< Step signal pin. */
    digital_out_t en;           /**< Enable driver pin. */
    digital_out_t dir;          /**< Direction control pin. */
    digital_out_t rst;          /**< PCA9538A reset pin. */

    i2c_master_t i2c;           /**< I2C driver object. */
    spi_master_t spi;           /**< SPI driver object. */

    uint8_t      slave_address; /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} stepper6_t;

/**
 * @brief Stepper 6 Click configuration object.
 * @details Configuration object definition of Stepper 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t en;              /**< Enable driver pin. */
    pin_name_t dir;             /**< Direction control pin. */
    pin_name_t rst;             /**< PCA9538A reset pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} stepper6_cfg_t;

/**
 * @brief Stepper 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER6_OK = 0,
    STEPPER6_ERROR = -1

} stepper6_return_value_t;

/*!
 * @addtogroup stepper6 Stepper 6 Click Driver
 * @brief API for configuring and manipulating Stepper 6 Click driver.
 * @{
 */

/**
 * @brief Stepper 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper6_cfg_setup ( stepper6_cfg_t *cfg );

/**
 * @brief Stepper 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_init ( stepper6_t *ctx, stepper6_cfg_t *cfg );

/**
 * @brief Stepper 6 default configuration function.
 * @details This function executes a default configuration of Stepper 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper6_default_cfg ( stepper6_t *ctx );

/**
 * @brief Stepper 6 set dac function.
 * @details This function writes a 16-bit command to DAC register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] dac_cmd : 16-bit DAC command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note DAC command is in format: B15 (!A/B -> default !A, i.e. 0), B14 (BUF -> VREF buffered - 1, not buffered - 0),
 * B13 (GA -> Output gain 1x - 1, 2x - 0), B12 (SHDN -> 1 enable, 0 disable), B11-B0 (DAC data).
 */
err_t stepper6_set_dac ( stepper6_t *ctx, uint16_t dac_cmd );

/**
 * @brief Stepper 6 pca write reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_pca_write_reg ( stepper6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 6 pca read reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_pca_read_reg ( stepper6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 6 get trq pin function.
 * @details This function reads the TRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state,
 *                     @li @c 2 - Open state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_get_trq_pin ( stepper6_t *ctx, uint8_t *state );

/**
 * @brief Stepper 6 set trq pin function.
 * @details This function sets the TRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state,
 *                    @li @c 2 - Open state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_set_trq_pin ( stepper6_t *ctx, uint8_t state );

/**
 * @brief Stepper 6 get M1 pin function.
 * @details This function reads the M1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_get_m1_pin ( stepper6_t *ctx, uint8_t *state );

/**
 * @brief Stepper 6 set M1 pin function.
 * @details This function sets the M1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_set_m1_pin ( stepper6_t *ctx, uint8_t state );

/**
 * @brief Stepper 6 get M0 pin function.
 * @details This function reads the M0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state,
 *                     @li @c 2 - Open state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_get_m0_pin ( stepper6_t *ctx, uint8_t *state );

/**
 * @brief Stepper 6 set M0 pin function.
 * @details This function sets the M0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state,
 *                    @li @c 2 - Open state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_set_m0_pin ( stepper6_t *ctx, uint8_t state );

/**
 * @brief Stepper 6 get sleep pin function.
 * @details This function reads the SLEEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_get_sleep_pin ( stepper6_t *ctx, uint8_t *state );

/**
 * @brief Stepper 6 set sleep pin function.
 * @details This function sets the SLEEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_set_sleep_pin ( stepper6_t *ctx, uint8_t state );

/**
 * @brief Stepper 6 get fault pin function.
 * @details This function reads the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_get_fault_pin ( stepper6_t *ctx, uint8_t *state );

/**
 * @brief Stepper 6 enable device function.
 * @details This function enables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper6_enable_device ( stepper6_t *ctx );

/**
 * @brief Stepper 6 disable device function.
 * @details This function disables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper6_disable_device ( stepper6_t *ctx );

/**
 * @brief Stepper 6 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper6_set_direction ( stepper6_t *ctx, uint8_t dir );

/**
 * @brief Stepper 6 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper6_switch_direction ( stepper6_t *ctx );

/**
 * @brief Stepper 6 reset device function.
 * @details This function resets the PCA9538A device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper6_reset_pca ( stepper6_t *ctx );

/**
 * @brief Stepper 6 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper6_set_rst_pin ( stepper6_t *ctx, uint8_t state );

/**
 * @brief Stepper 6 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper6_set_step_pin ( stepper6_t *ctx, uint8_t state );

/**
 * @brief Stepper 6 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution:
 *                    @li @c 0 - Full step (2-phase excitation) with 71% current,
 *                    @li @c 1 - 1/16 step,
 *                    @li @c 2 - 1/2 step,
 *                    @li @c 3 - 1/4 step,
 *                    @li @c 4 - 1/8 step,
 *                    @li @c 5 - Non-circular 1/2 step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_get_step_mode ( stepper6_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 6 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution:
 *                   @li @c 0 - Full step (2-phase excitation) with 71% current,
 *                   @li @c 1 - 1/16 step,
 *                   @li @c 2 - 1/2 step,
 *                   @li @c 3 - 1/4 step,
 *                   @li @c 4 - 1/8 step,
 *                   @li @c 5 - Non-circular 1/2 step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper6_set_step_mode ( stepper6_t *ctx, uint8_t mode );

/**
 * @brief Stepper 6 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper6_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return None.
 * @note None.
 */
void stepper6_drive_motor ( stepper6_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER6_H

/*! @} */ // stepper6

// ------------------------------------------------------------------------ END
