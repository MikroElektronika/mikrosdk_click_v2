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
 * @file eeprom15.h
 * @brief This file contains API for EEPROM 15 Click Driver.
 */

#ifndef EEPROM15_H
#define EEPROM15_H

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
 * @addtogroup eeprom15 EEPROM 15 Click Driver
 * @brief API for configuring and manipulating EEPROM 15 Click driver.
 * @{
 */

/**
 * @defgroup eeprom15_reg EEPROM 15 Registers List
 * @brief List of registers of EEPROM 15 Click driver.
 */

/**
 * @addtogroup eeprom15_reg
 * @{
 */

/**
 * @brief EEPROM 15 device address setting.
 * @details Specified setting for device address (registers) of EEPROM 15 Click driver.
 */
#define EEPROM15_REG_RW_EE_MEMORY           0x50
#define EEPROM15_REG_RW_WP_BLOCK_0          0x31
#define EEPROM15_REG_RW_WP_BLOCK_1          0x34
#define EEPROM15_REG_RW_WP_BLOCK_2          0x35
#define EEPROM15_REG_RW_WP_BLOCK_3          0x30
#define EEPROM15_REG_CLEAR_ALL_WP           0x33
#define EEPROM15_REG_SET_PAGE_ADDR_0        0x36
#define EEPROM15_REG_SET_PAGE_ADDR_1        0x37
#define EEPROM15_REG_READ_PAGE_ADDR         0x36

/*! @} */ // eeprom15_reg

/**
 * @defgroup eeprom15_set EEPROM 15 Registers Settings
 * @brief Settings for registers of EEPROM 15 Click driver.
 */

/**
 * @addtogroup eeprom15_set
 * @{
 */

/**
 * @brief EEPROM 15 memory size setting.
 * @details Specified setting for memory size of EEPROM 15 Click driver.
 */
#define EEPROM15_MEM_PAGE_BITMASK           0xF0
#define EEPROM15_MEM_PAGE_SIZE              16
#define EEPROM15_MEM_BANK_SIZE              256

/**
 * @brief EEPROM 15 bank selection setting.
 * @details Specified setting for bank selection of EEPROM 15 Click driver.
 */
#define EEPROM15_BANK_SEL_0                 0x00
#define EEPROM15_BANK_SEL_1                 0x01

/**
 * @brief EEPROM 15 wp block selection setting.
 * @details Specified setting for wp block selection of EEPROM 15 Click driver.
 */
#define EEPROM15_WP_BLOCK_SEL_0             0x00
#define EEPROM15_WP_BLOCK_SEL_1             0x01
#define EEPROM15_WP_BLOCK_SEL_2             0x02
#define EEPROM15_WP_BLOCK_SEL_3             0x03

/**
 * @brief EEPROM 15 device address setting via onboard A2-A1-A0 pins.
 * @details Specified setting for device slave address selection of
 * EEPROM 15 Click driver.
 */
#define EEPROM15_ADDRESS_A2A1A0_000         0x00
#define EEPROM15_ADDRESS_A2A1A0_001         0x01
#define EEPROM15_ADDRESS_A2A1A0_010         0x02
#define EEPROM15_ADDRESS_A2A1A0_011         0x03
#define EEPROM15_ADDRESS_A2A1A0_100         0x04
#define EEPROM15_ADDRESS_A2A1A0_101         0x05
#define EEPROM15_ADDRESS_A2A1A0_110         0x06
#define EEPROM15_ADDRESS_A2A1A0_111         0x07

/*! @} */ // eeprom15_set

/**
 * @defgroup eeprom15_map EEPROM 15 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 15 Click driver.
 */

/**
 * @addtogroup eeprom15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 15 Click to the selected MikroBUS.
 */
#define EEPROM15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // eeprom15_map
/*! @} */ // eeprom15

/**
 * @brief EEPROM 15 Click context object.
 * @details Context object definition of EEPROM 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;           /**< Write protect pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} eeprom15_t;

/**
 * @brief EEPROM 15 Click configuration object.
 * @details Configuration object definition of EEPROM 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t wp;              /**< Write protect pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} eeprom15_cfg_t;

/**
 * @brief EEPROM 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM15_OK = 0,
    EEPROM15_ERROR = -1

} eeprom15_return_value_t;

/*!
 * @addtogroup eeprom15 EEPROM 15 Click Driver
 * @brief API for configuring and manipulating EEPROM 15 Click driver.
 * @{
 */

/**
 * @brief EEPROM 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom15_cfg_setup ( eeprom15_cfg_t *cfg );

/**
 * @brief EEPROM 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #eeprom15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom15_init ( eeprom15_t *ctx, eeprom15_cfg_t *cfg );

/**
 * @brief EEPROM 15 Write Memory function.
 * @details This function writes data to the EEPROM memory starting from the specified address.
 * @param[in] ctx : Click context object.
 * See #eeprom15_t object definition for detailed explanation.
 * @param[in] address : Start address in EEPROM memory.
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write (up to 16).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t eeprom15_write_memory ( eeprom15_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 15 Read Memory function.
 * @details This function reads data from the EEPROM memory starting from the specified address.
 * @param[in] ctx : Click context object.
 * See #eeprom15_t object definition for detailed explanation.
 * @param[in] address : Start address in EEPROM memory.
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read (up to 256).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t eeprom15_read_memory ( eeprom15_t *ctx, uint8_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief EEPROM 15 Set Write Protection Pin function.
 * @details This function sets the state of the write protection (WP) pin.
 * @param[in] ctx : Click context object.
 * See #eeprom15_t object definition for detailed explanation.
 * @param[in] state : Pin state (0 - LOW, 1 - HIGH).
 * @note Write Protection pin is active high.
 */
void eeprom15_set_wp_pin ( eeprom15_t *ctx, uint8_t state );

/**
 * @brief EEPROM 15 Select Memory Bank function.
 * @details This function selects the active memory bank in the EEPROM.
 * @param[in] ctx : Click context object.
 * See #eeprom15_t object definition for detailed explanation.
 * @param[in] bank_sel : Memory bank selection (0 or 1).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t eeprom15_select_bank ( eeprom15_t *ctx, uint8_t bank_sel );

/**
 * @brief EEPROM 15 Set Write Protection Block function.
 * @details This function enables write protection for a specific memory block.
 * @param[in] ctx : Click context object.
 * See #eeprom15_t object definition for detailed explanation.
 * @param[in] block_num : Write protection block selection (0-3).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note A0 pin must be tied to Vhv (Very High Voltage: 7V to 10V).
 */
err_t eeprom15_set_wp_block ( eeprom15_t *ctx, uint8_t block_num );

/**
 * @brief EEPROM 15 Clear Write Protection function.
 * @details This function clears all write protection settings in the EEPROM.
 * @param[in] ctx : Click context object.
 * See #eeprom15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note A0 pin must be tied to Vhv (Very High Voltage: 7V to 10V).
 */
err_t eeprom15_clear_wp ( eeprom15_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EEPROM15_H

/*! @} */ // eeprom15

// ------------------------------------------------------------------------ END
