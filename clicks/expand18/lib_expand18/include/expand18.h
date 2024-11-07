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
 * @file expand18.h
 * @brief This file contains API for Expand 18 Click Driver.
 */

#ifndef EXPAND18_H
#define EXPAND18_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup expand18 Expand 18 Click Driver
 * @brief API for configuring and manipulating Expand 18 Click driver.
 * @{
 */

/**
 * @defgroup expand18_reg Expand 18 Registers List
 * @brief List of registers of Expand 18 Click driver.
 */

/**
 * @addtogroup expand18_reg
 * @{
 */

/**
 * @brief Expand 18 register list.
 * @details Specified register list of Expand 18 Click driver.
 */
#define EXPAND18_REG_INPUT_P0                   0x00
#define EXPAND18_REG_INPUT_P1                   0x01
#define EXPAND18_REG_OUTPUT_P0                  0x02
#define EXPAND18_REG_OUTPUT_P1                  0x03
#define EXPAND18_REG_POLARITY_INV_P0            0x04
#define EXPAND18_REG_POLARITY_INV_P1            0x05
#define EXPAND18_REG_CONFIG_P0                  0x06
#define EXPAND18_REG_CONFIG_P1                  0x07
#define EXPAND18_REG_OUTPUT_DRIVE_P0A           0x40
#define EXPAND18_REG_OUTPUT_DRIVE_P0B           0x41
#define EXPAND18_REG_OUTPUT_DRIVE_P1A           0x42
#define EXPAND18_REG_OUTPUT_DRIVE_P1B           0x43
#define EXPAND18_REG_INPUT_LATCH_P0             0x44
#define EXPAND18_REG_INPUT_LATCH_P1             0x45
#define EXPAND18_REG_PULL_ENABLE_P0             0x46
#define EXPAND18_REG_PULL_ENABLE_P1             0x47
#define EXPAND18_REG_PULL_SELECTION_P0          0x48
#define EXPAND18_REG_PULL_SELECTION_P1          0x49
#define EXPAND18_REG_INT_MASK_P0                0x4A
#define EXPAND18_REG_INT_MASK_P1                0x4B
#define EXPAND18_REG_INT_STATUS_P0              0x4C
#define EXPAND18_REG_INT_STATUS_P1              0x4D
#define EXPAND18_REG_OUTPUT_PORT_CONFIG         0x4F
#define EXPAND18_REG_INT_EDGE_P0A               0x50
#define EXPAND18_REG_INT_EDGE_P0B               0x51
#define EXPAND18_REG_INT_EDGE_P1A               0x52
#define EXPAND18_REG_INT_EDGE_P1B               0x53
#define EXPAND18_REG_INT_CLEAR_P0               0x54
#define EXPAND18_REG_INT_CLEAR_P1               0x55
#define EXPAND18_REG_INPUT_STATUS_P0            0x56
#define EXPAND18_REG_INPUT_STATUS_P1            0x57
#define EXPAND18_REG_PIN_OUTPUT_P0_CONFIG       0x58
#define EXPAND18_REG_PIN_OUTPUT_P1_CONFIG       0x59
#define EXPAND18_REG_SWITCH_DEBOUNCE_EN_0       0x5A
#define EXPAND18_REG_SWITCH_DEBOUNCE_EN_1       0x5B
#define EXPAND18_REG_SWITCH_DEBOUNCE_CNT        0x5C

/*! @} */ // expand18_reg

/**
 * @defgroup expand18_set Expand 18 Registers Settings
 * @brief Settings for registers of Expand 18 Click driver.
 */

/**
 * @addtogroup expand18_set
 * @{
 */

/**
 * @brief Expand 18 pin mask values.
 * @details Specified pin mask values of Expand 18 Click driver.
 */
#define EXPAND18_NO_PIN_MASK                    0x00
#define EXPAND18_PIN_0_MASK                     0x01
#define EXPAND18_PIN_1_MASK                     0x02
#define EXPAND18_PIN_2_MASK                     0x04
#define EXPAND18_PIN_3_MASK                     0x08
#define EXPAND18_PIN_4_MASK                     0x10
#define EXPAND18_PIN_5_MASK                     0x20
#define EXPAND18_PIN_6_MASK                     0x40
#define EXPAND18_PIN_7_MASK                     0x80
#define EXPAND18_ALL_PINS_MASK                  0xFF

/**
 * @brief Expand 18 port values.
 * @details Specified port values of Expand 18 Click driver.
 */
#define EXPAND18_PORT_0                         0x00
#define EXPAND18_PORT_1                         0x01

/**
 * @brief Expand 18 pin direction values.
 * @details Specified pin direction values of Expand 18 Click driver.
 */
#define EXPAND18_OUTPUT_DIRECTION               0x00
#define EXPAND18_INPUT_DIRECTION                0x01

/**
 * @brief Expand 18 pin logic level values.
 * @details Specified pin logic level values of Expand 18 Click driver.
 */
#define EXPAND18_PIN_LOW_LEVEL                  0x00
#define EXPAND18_PIN_HIGH_LEVEL                 0x01

/**
 * @brief Expand 18 auto increment bit mask.
 * @details Specified bit mask for auto increment of Expand 18 Click driver.
 */
#define EXPAND18_AUTO_INCREMENT_BIT             0x80

/**
 * @brief Expand 18 device ID value.
 * @details Device ID value 24bit (manufacturer 12 MSB, part identification 9bits, revision 3 LSB) of Expand 18 Click driver.
 */
#define EXPAND18_DEVICE_ID                      0x000830

/**
 * @brief Expand 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 18 Click driver.
 */
#define EXPAND18_DEVICE_ADDRESS_0               0x40
#define EXPAND18_DEVICE_ADDRESS_1               0x42
#define EXPAND18_ADDRESS_READ_BIT               0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b expand18_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define EXPAND18_SET_DATA_SAMPLE_EDGE           SET_SPI_DATA_SAMPLE_EDGE
#define EXPAND18_SET_DATA_SAMPLE_MIDDLE         SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // expand18_set

/**
 * @defgroup expand18_map Expand 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 18 Click driver.
 */

/**
 * @addtogroup expand18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 18 Click to the selected MikroBUS.
 */
#define EXPAND18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand18_map
/*! @} */ // expand18

/**
 * @brief Expand 18 Click context object.
 * @details Context object definition of Expand 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t slave_address;      /**< Device slave address (used for SPI driver). */

} expand18_t;

/**
 * @brief Expand 18 Click configuration object.
 * @details Configuration object definition of Expand 18 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    uint8_t spi_address;        /**< SPI slave address. */

} expand18_cfg_t;

/**
 * @brief Expand 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND18_OK = 0,
    EXPAND18_ERROR = -1

} expand18_return_value_t;

/*!
 * @addtogroup expand18 Expand 18 Click Driver
 * @brief API for configuring and manipulating Expand 18 Click driver.
 * @{
 */

/**
 * @brief Expand 18 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand18_cfg_setup ( expand18_cfg_t *cfg );

/**
 * @brief Expand 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_init ( expand18_t *ctx, expand18_cfg_t *cfg );

/**
 * @brief Expand 18 default configuration function.
 * @details This function executes a default configuration of Expand 18
 * Click board.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand18_default_cfg ( expand18_t *ctx );

/**
 * @brief Expand 18 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] reg : Start register address, with EXPAND18_AUTO_INCREMENT_BIT set for reg auto increment.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_generic_write ( expand18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Expand 18 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] reg : Start register address, with EXPAND18_AUTO_INCREMENT_BIT set for reg auto increment.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_generic_read ( expand18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Expand 18 write register function.
 * @details This function writes a data byte to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_write_register ( expand18_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Expand 18 read register function.
 * @details This function reads a data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_read_register ( expand18_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Expand 18 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void expand18_set_rst_pin ( expand18_t *ctx, uint8_t state );

/**
 * @brief Expand 18 reset device function.
 * @details This function resets the device by toggling the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void expand18_reset_device ( expand18_t *ctx );

/**
 * @brief Expand 18 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t expand18_get_int_pin ( expand18_t *ctx );

/**
 * @brief Expand 18 set pin direction function.
 * @details This function sets the direction of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 * @param[in] pin_mask : Pin mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_set_pin_direction ( expand18_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask );

/**
 * @brief Expand 18 set all pins direction function.
 * @details This function sets the direction of all pins.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_set_all_pins_direction ( expand18_t *ctx, uint8_t direction );

/**
 * @brief Expand 18 set all pins value function.
 * @details This function sets the value of all output pins.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_set_all_pins_value ( expand18_t *ctx, uint8_t set_mask );

/**
 * @brief Expand 18 set pin value function.
 * @details This function sets the value of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_set_pin_value ( expand18_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 18 read port value function.
 * @details This function reads the value of the selected port input pins.
 * @param[in] ctx : Click context object.
 * See #expand18_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 * @param[out] data_out : Port value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand18_read_port_value ( expand18_t *ctx, uint8_t port, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // EXPAND18_H

/*! @} */ // expand18

// ------------------------------------------------------------------------ END
