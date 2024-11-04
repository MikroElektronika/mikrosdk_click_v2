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
 * @file eeprom6.h
 * @brief This file contains API for EEPROM 6 Click Driver.
 */

#ifndef EEPROM6_H
#define EEPROM6_H

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
 * @addtogroup eeprom6 EEPROM 6 Click Driver
 * @brief API for configuring and manipulating EEPROM 6 Click driver.
 * @{
 */

/**
 * @defgroup eeprom6_cmd EEPROM 6 Commands List
 * @brief List of commands of EEPROM 6 Click driver.
 */

/**
 * @addtogroup eeprom6_cmd
 * @{
 */

/**
 * @brief EEPROM 6 commands list.
 * @details Specified commands list of EEPROM 6 Click driver.
 */
#define EEPROM6_CMD_WRITE_SCRATCHPAD      0x0F
#define EEPROM6_CMD_READ_SCRATCHPAD       0xAA
#define EEPROM6_CMD_COPY_SCRATCHPAD       0x55
#define EEPROM6_CMD_READ_MEMORY           0xF0  
#define EEPROM6_CMD_EXTENDED_READ_MEMORY  0xA5

/*! @} */ // eeprom6_cmd

/**
 * @defgroup eeprom6_set EEPROM 6 Settings
 * @brief Settings of EEPROM 6 Click driver.
 */

/**
 * @addtogroup eeprom6_set
 * @{
 */

/**
 * @brief EEPROM 6 family code value.
 * @details Specified family code value of EEPROM 6 Click driver.
 */
#define EEPROM6_FAMILY_CODE               0x43

/**
 * @brief EEPROM 6 address selection macros.
 * @details Specified address selection macros of EEPROM 6 Click driver.
 */
#define EEPROM6_ADDRESS_0                 0x00
#define EEPROM6_ADDRESS_1                 0x01
#define EEPROM6_ADDRESS_ALL               0xFF

/*! @} */ // eeprom6_set

/**
 * @defgroup eeprom6_map EEPROM 6 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 6 Click driver.
 */

/**
 * @addtogroup eeprom6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 6 Click to the selected MikroBUS.
 */
#define EEPROM6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN ); 

/*! @} */ // eeprom6_map
/*! @} */ // eeprom6

/**
 * @brief EEPROM 6 Click gpio selector.
 * @details Selects gpio pin of EEPROM 6 Click driver.
 */
typedef enum
{
    EEPROM6_GPIO_0,      /**< GPIO 0 pin. */
    EEPROM6_GPIO_1       /**< GPIO 1 pin. */

} eeprom6_gpio_sel_t;

/**
 * @brief EEPROM 6 Click context object.
 * @details Context object definition of EEPROM 6 Click driver.
 */
typedef struct
{
    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t address;                    /**< Device address selection. */

} eeprom6_t;

/**
 * @brief EEPROM 6 Click configuration object.
 * @details Configuration object definition of EEPROM 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;                     /**< GPIO 0 pin. */
    pin_name_t gp1;                     /**< GPIO 1 pin. */

    eeprom6_gpio_sel_t gpio_sel;        /**< GPIO selection. */

} eeprom6_cfg_t;

/**
 * @brief EEPROM 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM6_OK = 0,
    EEPROM6_ERROR = -1

} eeprom6_return_value_t;

/*!
 * @addtogroup eeprom6 EEPROM 6 Click Driver
 * @brief API for configuring and manipulating EEPROM 6 Click driver.
 * @{
 */

/**
 * @brief EEPROM 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom6_cfg_setup ( eeprom6_cfg_t *cfg );

/**
 * @brief EEPROM 6 driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom6_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #eeprom6_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void eeprom6_gpio_selection ( eeprom6_cfg_t *cfg, eeprom6_gpio_sel_t gpio_sel );

/**
 * @brief EEPROM 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #eeprom6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom6_init ( eeprom6_t *ctx, eeprom6_cfg_t *cfg );

/**
 * @brief EEPROM 6 default configuration function.
 * @details This function executes a default configuration of EEPROM 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t eeprom6_default_cfg ( eeprom6_t *ctx );

/**
 * @brief EEPROM 6 check communication function.
 * @details This function checks the communication by reading the ROM address twice and comparing
 * the two results, as well as verifying the family code byte.
 * @param[in] ctx : Click context object.
 * See #eeprom6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom6_check_communication ( eeprom6_t *ctx );

/**
 * @brief EEPROM 6 select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the @b ctx->address.
 * @param[in] ctx : Click context object.
 * See #eeprom6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom6_select_device ( eeprom6_t *ctx );

/**
 * @brief EEPROM 6 read scratchpad function.
 * @details This function reads a desired number of scratchpad bytes using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #eeprom6_t object definition for detailed explanation.
 * @param[out] scratchpad : Output read scratchpad.
 * @param[in] scratchpad_len : Scratchpad length in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom6_read_scratchpad ( eeprom6_t *ctx, uint8_t *scratchpad, uint8_t scratchpad_len );

/**
 * @brief EEPROM 6 write scratchpad function.
 * @details This function writes a desired number of scratchpad bytes using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #eeprom6_t object definition for detailed explanation.
 * @param[in] scratchpad : Scratchpad to be written.
 * @param[in] scratchpad_len : Scratchpad length in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom6_write_scratchpad ( eeprom6_t *ctx, uint8_t *scratchpad, uint8_t scratchpad_len );

/**
 * @brief EEPROM 6 read memory function.
 * @details This function reads a sequential data starting from the targeted 16-bit register address of 
 * the DS28EC20.
 * @param[in] ctx : Click context object.
 * See #eeprom6_t object definition for detailed explanation.
 * @param[in] reg_adr : 16-bit memory address. 
 * @param[in] data_in : Pointer to the memory location where data to be stored.
 * @param[in] n_len : Number of bytes to be written. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom6_read_mem ( eeprom6_t *ctx, uint16_t reg_adr, uint8_t *data_in, uint16_t n_len );

/**
 * @brief EEPROM 6 write memory function.
 * @details This function writes a sequential data starting of the targeted 16-bit register address of the DS28EC20.
 * @param[in] ctx : Click context object.
 * See #eeprom6_t object definition for detailed explanation.
 * @param[in] reg_adr : Target address to which data is copied from the scratchpad.
 * @param[in] data_in : Pointer to the data to be written. 
 * @param[in] n_len : Number of bytes to be written. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom6_write_mem ( eeprom6_t *ctx, uint16_t reg_adr, uint8_t *data_in, uint16_t n_len );

#ifdef __cplusplus
}
#endif
#endif // EEPROM6_H

/*! @} */ // eeprom6

// ------------------------------------------------------------------------ END
