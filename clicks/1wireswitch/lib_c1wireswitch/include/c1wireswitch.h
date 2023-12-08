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
 * @file c1wireswitch.h
 * @brief This file contains API for 1-Wire Switch Click Driver.
 */

#ifndef C1WIRESWITCH_H
#define C1WIRESWITCH_H

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
#include "drv_one_wire.h"

/*!
 * @addtogroup c1wireswitch 1-Wire Switch Click Driver
 * @brief API for configuring and manipulating 1-Wire Switch Click driver.
 * @{
 */

/**
 * @defgroup c1wireswitch_cmd 1-Wire Switch Commands List
 * @brief List of commands of 1-Wire Switch Click driver.
 */

/**
 * @addtogroup c1wireswitch_cmd
 * @{
 */

/**
 * @brief 1-Wire Switch commands list.
 * @details Specified commands list of 1-Wire Switch Click driver.
 */
#define C1WIRESWITCH_CMD_WRITE_SCRATCHPAD      0x5A
#define C1WIRESWITCH_CMD_READ_SCRATCHPAD       0xF5

#define C1WIRESWITCH_CMD_WRITE_PIO             0x5A
#define C1WIRESWITCH_CMD_READ_PIO              0xF5

/**
 * @brief 1-Wire Switch PIO state masks.
 * @details Specified PIO state masks of 1-Wire Switch Click driver.
 */
#define C1WIRESWITCH_PIOB_STATE_MASK           0x04
#define C1WIRESWITCH_PIOA_STATE_MASK           0x01
#define C1WIRESWITCH_PIOB_LATCH_STATE_MASK     0x08
#define C1WIRESWITCH_PIOA_LATCH_STATE_MASK     0x02

/**
 * @brief 1-Wire Switch PIO states.
 * @details Specified PIO states of 1-Wire Switch Click driver.
 */
#define C1WIRESWITCH_PIOA_HIGH                 0x01
#define C1WIRESWITCH_PIOA_LOW                  0x00
#define C1WIRESWITCH_PIOB_HIGH                 0x04
#define C1WIRESWITCH_PIOB_LOW                  0x00

#define C1WIRESWITCH_PIOB_ON                   0x02
#define C1WIRESWITCH_PIOB_OFF                  0x00
#define C1WIRESWITCH_PIOA_ON                   0x00
#define C1WIRESWITCH_PIOA_OFF                  0x01

#define C1WIRESWITCH_PIOB_LATCH_LOW            0x00
#define C1WIRESWITCH_PIOB_LATCH_HIGH           0x08
#define C1WIRESWITCH_PIOA_LATCH_LOW            0x00
#define C1WIRESWITCH_PIOA_LATCH_HIGH           0x02

/*! @} */ // c1wireswitch_cmd

/**
 * @defgroup c1wireswitch_set 1-Wire Switch Settings
 * @brief Settings of 1-Wire Switch Click driver.
 */

/**
 * @addtogroup c1wireswitch_set
 * @{
 */

/**
 * @brief 1-Wire Switch family code value.
 * @details Specified family code value of 1-Wire Switch Click driver.
 */
#define C1WIRESWITCH_FAMILY_CODE               0x3A

/**
 * @brief 1-Wire Switch address selection macros.
 * @details Specified address selection macros of 1-Wire Switch Click driver.
 */
#define C1WIRESWITCH_ADDRESS                   0x33
#define C1WIRESWITCH_ADDRESS_ALL               0xFF

/*! @} */ // c1wireswitch_set

/**
 * @defgroup c1wireswitch_map 1-Wire Switch MikroBUS Map
 * @brief MikroBUS pin mapping of 1-Wire Switch Click driver.
 */

/**
 * @addtogroup c1wireswitch_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 1-Wire Switch Click to the selected MikroBUS.
 */
#define C1WIRESWITCH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN ); 

/*! @} */ // c1wireswitch_map
/*! @} */ // c1wireswitch

/**
 * @brief 1-Wire Switch Click gpio selector.
 * @details Selects gpio pin of 1-Wire Switch Click driver.
 */
typedef enum
{
    C1WIRESWITCH_GPIO_0,      /**< GPIO 0 pin. */
    C1WIRESWITCH_GPIO_1       /**< GPIO 1 pin. */

} c1wireswitch_gpio_sel_t;

/**
 * @brief 1-Wire Switch Click context object.
 * @details Context object definition of 1-Wire Switch Click driver.
 */
typedef struct
{
    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t address;                    /**< Device address selection. */

} c1wireswitch_t;

/**
 * @brief 1-Wire Switch Click configuration object.
 * @details Configuration object definition of 1-Wire Switch Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;                     /**< GPIO 0 pin. */
    pin_name_t gp1;                     /**< GPIO 1 pin. */
    
    c1wireswitch_gpio_sel_t gpio_sel;      /**< GPIO selection. */

} c1wireswitch_cfg_t;

/**
 * @brief 1-Wire Switch Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C1WIRESWITCH_OK = 0,
    C1WIRESWITCH_ERROR = -1

} c1wireswitch_return_value_t;

/*!
 * @addtogroup c1wireswitch 1-Wire Switch Click Driver
 * @brief API for configuring and manipulating 1-Wire Switch Click driver.
 * @{
 */

/**
 * @brief 1-Wire Switch configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c1wireswitch_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c1wireswitch_cfg_setup ( c1wireswitch_cfg_t *cfg );

/**
 * @brief 1-Wire Switch driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c1wireswitch_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #c1wireswitch_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c1wireswitch_gpio_selection ( c1wireswitch_cfg_t *cfg, c1wireswitch_gpio_sel_t gpio_sel );

/**
 * @brief 1-Wire Switch initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c1wireswitch_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_init ( c1wireswitch_t *ctx, c1wireswitch_cfg_t *cfg );

/**
 * @brief 1-Wire Switch default configuration function.
 * @details This function executes a default configuration of 1-Wire Switch
 * click board.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c1wireswitch_default_cfg ( c1wireswitch_t *ctx );

/**
 * @brief 1-Wire Switch check communication function.
 * @details This function checks the communication by reading the ROM address 
 * as well as verifying family code and Maxim CRC 8.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_check_communication ( c1wireswitch_t *ctx );

/**
 * @brief 1-Wire Switch select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the @b ctx->address.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_select_device ( c1wireswitch_t *ctx );

/**
 * @brief 1-Wire Switch read scratchpad function.
 * @details This function reads a desired number of scratchpad bytes using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @param[out] scratchpad : Output read scratchpad.
 * @param[in] scratchpad_len : Scratchpad length in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_read_scratchpad ( c1wireswitch_t *ctx, uint8_t *scratchpad, uint8_t scratchpad_len );

/**
 * @brief 1-Wire Switch write scratchpad function.
 * @details This function writes a desired number of scratchpad bytes using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @param[in] scratchpad : Scratchpad to be written.
 * @param[in] scratchpad_len : Scratchpad length in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_write_scratchpad ( c1wireswitch_t *ctx, uint8_t *scratchpad, uint8_t scratchpad_len );

/**
 * @brief 1-Wire Switch write programmable I/O state function.
 * @details This function writes a programmable I/O state using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @param[in] state : State to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_write_pio ( c1wireswitch_t *ctx, uint8_t state );

/**
 * @brief 1-Wire Switch read programmable I/O state function.
 * @details This function reads a programmable I/O state using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @param[out] state : State of the I/O.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_read_pio ( c1wireswitch_t *ctx, uint8_t *state );

/**
 * @brief 1-Wire Switch write specific programmable I/O state function.
 * @details This function writes a specific programmable I/O state using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @param[in] pio_a : State of the PIO A to be written.
 * @param[in] pio_b : State of the PIO B to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_set_pio_state ( c1wireswitch_t *ctx, uint8_t pio_a, uint8_t pio_b );

/**
 * @brief 1-Wire Switch read specific programmable I/O state function.
 * @details This function reads a specific programmable I/O state using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @param[out] pio_a : State of the I/O A.
 * @param[out] pio_b : State of the I/O B.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_get_pio_state ( c1wireswitch_t *ctx, uint8_t *pio_a, uint8_t *pio_b );

/**
 * @brief 1-Wire Switch read programmable I/O latch state function.
 * @details This function reads a programmable I/O latch state using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #c1wireswitch_t object definition for detailed explanation.
 * @param[out] pio_a_latch : State of the latch A.
 * @param[out] pio_b_latch : State of the latch B.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wireswitch_get_pio_latch_state ( c1wireswitch_t *ctx, uint8_t *pio_a_latch, uint8_t *pio_b_latch );

#ifdef __cplusplus
}
#endif
#endif // C1WIRESWITCH_H

/*! @} */ // c1wireswitch

// ------------------------------------------------------------------------ END
