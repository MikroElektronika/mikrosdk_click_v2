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
 * @file stepper7.h
 * @brief This file contains API for Stepper 7 Click Driver.
 */

#ifndef STEPPER7_H
#define STEPPER7_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup stepper7 Stepper 7 Click Driver
 * @brief API for configuring and manipulating Stepper 7 Click driver.
 * @{
 */

/**
 * @defgroup stepper7_reg Stepper 7 Registers List
 * @brief List of registers of Stepper 7 Click driver.
 */

/**
 * @addtogroup stepper7_reg
 * @{
 */

/**
 * @brief Stepper 7 register list.
 * @details Specified register list of Stepper 7 Click driver.
 */
#define STEPPER7_REG_IODIR                  0x00
#define STEPPER7_REG_IPOL                   0x01
#define STEPPER7_REG_GPINTEN                0x02
#define STEPPER7_REG_DEFVAL                 0x03
#define STEPPER7_REG_INTCON                 0x04
#define STEPPER7_REG_IOCON                  0x05
#define STEPPER7_REG_GPPU                   0x06
#define STEPPER7_REG_INTF                   0x07
#define STEPPER7_REG_INTCAP                 0x08
#define STEPPER7_REG_GPIO                   0x09
#define STEPPER7_REG_OLAT                   0x0A

/*! @} */ // stepper7_reg

/**
 * @defgroup stepper7_set Stepper 7 Registers Settings
 * @brief Settings for registers of Stepper 7 Click driver.
 */

/**
 * @addtogroup stepper7_set
 * @{
 */
 
/**
 * @brief Stepper 7 MCP23S08T pin mask setting.
 * @details Specified setting for pin mask of Stepper 7 Click driver.
 */
#define STEPPER7_PIN_PHASE2                 0x80
#define STEPPER7_PIN_PHASE1                 0x40
#define STEPPER7_PIN_I12                    0x20
#define STEPPER7_PIN_I02                    0x10
#define STEPPER7_PIN_I11                    0x08
#define STEPPER7_PIN_I01                    0x04

/**
 * @brief Stepper 7 MCP23S08T settings.
 * @details Specified MCP23S08T settings of Stepper 7 Click driver.
 */
#define STEPPER7_IODIR_DEFAULT              0x03
#define STEPPER7_IOCON_DEFAULT              0x38
#define STEPPER7_GPIO_CLEAR                 0x00

/**
 * @brief Stepper 7 direction setting.
 * @details Specified setting for direction of Stepper 7 Click driver.
 */
#define STEPPER7_DIR_CW                     0
#define STEPPER7_DIR_CCW                    1

/**
 * @brief Stepper 7 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 7 Click driver.
 */
#define STEPPER7_PIN_LOW_LEVEL              0
#define STEPPER7_PIN_HIGH_LEVEL             1

/**
 * @brief Stepper 7 step resolution setting.
 * @details Specified setting for step resolution of Stepper 7 Click driver.
 */
#define STEPPER7_MODE_FULL_STEP             0
#define STEPPER7_MODE_HALF_STEP             1
#define STEPPER7_MODE_1_OVER_8_STEP         2

/**
 * @brief Stepper 7 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER7_SPEED_VERY_SLOW            0
#define STEPPER7_SPEED_SLOW                 1
#define STEPPER7_SPEED_MEDIUM               2
#define STEPPER7_SPEED_FAST                 3
#define STEPPER7_SPEED_VERY_FAST            4 

/**
 * @brief Stepper 7 SPI setting.
 * @details Specified setting for SPI of Stepper 7 Click driver.
 */
#define STEPPER7_SPI_READ_OPCODE            0x41
#define STEPPER7_SPI_WRITE_OPCODE           0x40

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b stepper7_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define STEPPER7_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define STEPPER7_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // stepper7_set

/**
 * @defgroup stepper7_map Stepper 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 7 Click driver.
 */

/**
 * @addtogroup stepper7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 7 Click to the selected MikroBUS.
 */
#define STEPPER7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // stepper7_map
/*! @} */ // stepper7

/**
 * @brief Stepper 7 Click context object.
 * @details Context object definition of Stepper 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t step_mode;              /**< Step mode setting (0 - full step, 1 - half step, 2 - 1/8th step). */
    uint8_t direction;              /**< Direction setting (0 - cw, 1 - ccw). */

} stepper7_t;

/**
 * @brief Stepper 7 Click configuration object.
 * @details Configuration object definition of Stepper 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} stepper7_cfg_t;

/**
 * @brief Stepper 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER7_OK = 0,
    STEPPER7_ERROR = -1

} stepper7_return_value_t;

/*!
 * @addtogroup stepper7 Stepper 7 Click Driver
 * @brief API for configuring and manipulating Stepper 7 Click driver.
 * @{
 */

/**
 * @brief Stepper 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper7_cfg_setup ( stepper7_cfg_t *cfg );

/**
 * @brief Stepper 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_init ( stepper7_t *ctx, stepper7_cfg_t *cfg );

/**
 * @brief Stepper 7 default configuration function.
 * @details This function executes a default configuration of Stepper 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper7_default_cfg ( stepper7_t *ctx );

/**
 * @brief Stepper 7 write reg function.
 * @details This function writes data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_write_reg ( stepper7_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 7 read reg function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_read_reg ( stepper7_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 7 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper7_set_rst_pin ( stepper7_t *ctx, uint8_t state );

/**
 * @brief Stepper 7 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper7_reset_device ( stepper7_t *ctx );

/**
 * @brief Stepper 7 set PHASE2 pin function.
 * @details This function sets the PHASE2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_set_phase2_pin ( stepper7_t *ctx, uint8_t state );

/**
 * @brief Stepper 7 set PHASE1 pin function.
 * @details This function sets the PHASE1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_set_phase1_pin ( stepper7_t *ctx, uint8_t state );

/**
 * @brief Stepper 7 set I12 pin function.
 * @details This function sets the I12 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_set_i12_pin ( stepper7_t *ctx, uint8_t state );

/**
 * @brief Stepper 7 set I02 pin function.
 * @details This function sets the I02 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_set_i02_pin ( stepper7_t *ctx, uint8_t state );

/**
 * @brief Stepper 7 set I11 pin function.
 * @details This function sets the I11 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_set_i11_pin ( stepper7_t *ctx, uint8_t state );

/**
 * @brief Stepper 7 set I01 pin function.
 * @details This function sets the I01 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_set_i01_pin ( stepper7_t *ctx, uint8_t state );

/**
 * @brief Stepper 7 enable device function.
 * @details This function enables the device by setting all pins to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_enable_device ( stepper7_t *ctx );

/**
 * @brief Stepper 7 disable device function.
 * @details This function disables the device by setting all pins to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_disable_device ( stepper7_t *ctx );

/**
 * @brief Stepper 7 set step mode function.
 * @details This function sets the step mode resolution settings in @b ctx->step_mode.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 *                   @li @c 0 - Full step,
 *                   @li @c 1 - Half step,
 *                   @li @c 2 - 1/8th step.
 * @return None.
 * @note None.
 */
void stepper7_set_step_mode ( stepper7_t *ctx, uint8_t mode );

/**
 * @brief Stepper 7 set direction function.
 * @details This function sets the motor direction to clockwise or counter-clockwise in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper7_set_direction ( stepper7_t *ctx, uint8_t dir );

/**
 * @brief Stepper 7 switch direction function.
 * @details This function switches the motor direction in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper7_switch_direction ( stepper7_t *ctx );

/**
 * @brief Stepper 7 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper7_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper7_drive_motor ( stepper7_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER7_H

/*! @} */ // stepper7

// ------------------------------------------------------------------------ END
