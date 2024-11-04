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
 * @file expand3.h
 * @brief This file contains API for Expand 3 Click Driver.
 */

#ifndef EXPAND3_H
#define EXPAND3_H

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
#include "drv_one_wire.h"

/*!
 * @addtogroup expand3 Expand 3 Click Driver
 * @brief API for configuring and manipulating Expand 3 Click driver.
 * @{
 */

/**
 * @defgroup expand3_cmd Expand 3 Commands List
 * @brief List of commands of Expand 3 Click driver.
 */

/**
 * @addtogroup expand3_cmd
 * @{
 */

/**
 * @brief Expand 3 commands list.
 * @details Specified commands list of Expand 3 Click driver.
 */
#define EXPAND3_CMD_READ_PIO_REGISTERS      0xF0
#define EXPAND3_CMD_CHANNEL_ACCESS_READ     0xF5
#define EXPAND3_CMD_CHANNEL_ACCESS_WRITE    0x5A
#define EXPAND3_CMD_WRITE_CONDITIONAL       0xCC
#define EXPAND3_CMD_RESET_ACTIVITY_LATCHES  0xC3

/**
 * @brief Expand 3 registers list.
 * @details Specified registers list of Expand 3 Click driver.
 */
#define EXPAND3_REG_PIO_LOGIC               0x0088
#define EXPAND3_REG_PIO_OUT_LATCH           0x0089
#define EXPAND3_REG_PIO_ACTIVITY_LATCH      0x008A
#define EXPAND3_REG_CHANNEL_MASK            0x008B
#define EXPAND3_REG_CHANNEL_POLARITY        0x008C
#define EXPAND3_REG_CONTROL                 0x008D

/*! @} */ // expand3_cmd

/**
 * @defgroup expand3_set Expand 3 Settings
 * @brief Settings of Expand 3 Click driver.
 */

/**
 * @addtogroup expand3_set
 * @{
 */

/**
 * @brief Expand 3 Control/Status/Mask/Polarity register setting.
 * @details Specified Control/Status/Mask/Polarity register setting of Expand 3 Click driver.
 */
#define EXPAND3_STATUS_VCCP                 0x80
#define EXPAND3_CONTROL_PORL                0x08
#define EXPAND3_CONTROL_ROS                 0x04
#define EXPAND3_CONTROL_CT                  0x02
#define EXPAND3_CONTROL_PLS                 0x01
#define EXPAND3_CONTROL_DEFAULT             0x00
#define EXPAND3_MASK_DEFAULT                0x00
#define EXPAND3_POLARITY_DEFAULT            0x00

/**
 * @brief Expand 3 confirmation byte.
 * @details Specified confirmation byte of Expand 3 Click driver.
 */
#define EXPAND3_CONFIRMATION_BYTE           0xAA

/**
 * @brief Expand 3 pin mask setting.
 * @details Specified pin mask setting of Expand 3 Click driver.
 */
#define EXPAND3_PIN_0                       0x01
#define EXPAND3_PIN_1                       0x02
#define EXPAND3_PIN_2                       0x04
#define EXPAND3_PIN_3                       0x08
#define EXPAND3_PIN_4                       0x10
#define EXPAND3_PIN_5                       0x20
#define EXPAND3_PIN_6                       0x40
#define EXPAND3_PIN_7                       0x80

/**
 * @brief Expand 3 family code value.
 * @details Specified family code value of Expand 3 Click driver.
 */
#define EXPAND3_FAMILY_CODE                 0x29

/**
 * @brief Expand 3 address selection macros.
 * @details Specified address selection macros of Expand 3 Click driver.
 */
#define EXPAND3_ADDRESS_0                   0x00
#define EXPAND3_ADDRESS_ALL                 0xFF

/*! @} */ // expand3_set

/**
 * @defgroup expand3_map Expand 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 3 Click driver.
 */

/**
 * @addtogroup expand3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 3 Click to the selected MikroBUS.
 */
#define EXPAND3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ow0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ow1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // expand3_map
/*! @} */ // expand3

/**
 * @brief Expand 3 Click gpio selector.
 * @details Selects gpio pin of Expand 3 Click driver.
 */
typedef enum
{
    EXPAND3_GPIO_OW0,                   /**< GPIO OW0 pin. */
    EXPAND3_GPIO_OW1                    /**< GPIO OW1 pin. */

} expand3_gpio_sel_t;

/**
 * @brief Expand 3 Click context object.
 * @details Context object definition of Expand 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Reset pin (active low). */

    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t address;                    /**< Device address selection. */

} expand3_t;

/**
 * @brief Expand 3 Click configuration object.
 * @details Configuration object definition of Expand 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t ow0;                     /**< GPIO OW0 pin. */
    pin_name_t ow1;                     /**< GPIO OW1 pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin (active low). */

    expand3_gpio_sel_t gpio_sel;        /**< GPIO selection. */

} expand3_cfg_t;

/**
 * @brief Expand 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND3_OK = 0,
    EXPAND3_ERROR = -1

} expand3_return_value_t;

/*!
 * @addtogroup expand3 Expand 3 Click Driver
 * @brief API for configuring and manipulating Expand 3 Click driver.
 * @{
 */

/**
 * @brief Expand 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand3_cfg_setup ( expand3_cfg_t *cfg );

/**
 * @brief Expand 3 driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #expand3_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #expand3_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void expand3_gpio_selection ( expand3_cfg_t *cfg, expand3_gpio_sel_t gpio_sel );

/**
 * @brief Expand 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_init ( expand3_t *ctx, expand3_cfg_t *cfg );

/**
 * @brief Expand 3 default configuration function.
 * @details This function executes a default configuration of Expand 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand3_default_cfg ( expand3_t *ctx );

/**
 * @brief Expand 3 check communication function.
 * @details This function checks the communication by reading the ROM address 
 * as well as verifying family code and CRC 8.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_check_communication ( expand3_t *ctx );

/**
 * @brief Expand 3 select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the @b ctx->address.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_select_device ( expand3_t *ctx );

/**
 * @brief Expand 3 read register function.
 * @details This function reads data from the selected register by using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_read_register ( expand3_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief Expand 3 write register function.
 * @details This function writes data to the selected register by using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_write_register ( expand3_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief Expand 3 read state function.
 * @details This function reads the status of all eight PIO channels.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[out] state : PIO state read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_read_state ( expand3_t *ctx, uint8_t *state );

/**
 * @brief Expand 3 write state function.
 * @details This function writes data to the PIO output-latch state register which controls
 * the open-drain output transistors of the PIO channels.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[in] state : PIO state to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_write_state ( expand3_t *ctx, uint8_t state );

/**
 * @brief Expand 3 reset activity function.
 * @details This function resets an activity latch that is set whenever there is
 * a state transition at a PIO pin.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_reset_activity ( expand3_t *ctx );

/**
 * @brief Expand 3 write mask function.
 * @details This function writes a conditional search channel selection mask which controls
 * wheather a PIO channel qualifies for participation in the conditional search command.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[in] mask : Mask byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_write_mask ( expand3_t *ctx, uint8_t mask );

/**
 * @brief Expand 3 write polarity function.
 * @details This function writes a conditional search channel polarity selection which
 * specifies the polarity of each selected PIO channel for the device to respond to
 * the conditional search command.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[in] polarity : Polarity byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_write_polarity ( expand3_t *ctx, uint8_t polarity );

/**
 * @brief Expand 3 write control function.
 * @details This function writes a control register which determines the function of
 * the RSTZ pin and further configures the device for conditional search.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[in] control : Control byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_write_control ( expand3_t *ctx, uint8_t control );

/**
 * @brief Expand 3 read control function.
 * @details This function reads a control or status register settings.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[out] control : Control or status byte read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_read_control ( expand3_t *ctx, uint8_t *control );

/**
 * @brief Expand 3 read current state function.
 * @details This function reads the current logic state of the PIO pins.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[out] curr_state : PIO state read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_read_current_state ( expand3_t *ctx, uint8_t *curr_state );

/**
 * @brief Expand 3 read last state function.
 * @details This function reads the latest data written to the PIO using
 * the expand3_write_state function.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[out] last_state : Latest data written to the PIO.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_read_last_state ( expand3_t *ctx, uint8_t *last_state );

/**
 * @brief Expand 3 read activity function.
 * @details This function reads the current state of the PIO activity latches.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[out] activity : PIO activity latches state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand3_read_activity ( expand3_t *ctx, uint8_t *activity );

/**
 * @brief Expand 3 set rst pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void expand3_set_rst_pin ( expand3_t *ctx, uint8_t state );

/**
 * @brief Expand 3 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #expand3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void expand3_reset_device ( expand3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EXPAND3_H

/*! @} */ // expand3

// ------------------------------------------------------------------------ END
