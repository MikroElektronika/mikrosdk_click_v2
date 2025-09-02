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
 * @file eeprom17.h
 * @brief This file contains API for EEPROM 17 Click Driver.
 */

#ifndef EEPROM17_H
#define EEPROM17_H

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
 * @addtogroup eeprom17 EEPROM 17 Click Driver
 * @brief API for configuring and manipulating EEPROM 17 Click driver.
 * @{
 */

/**
 * @defgroup eeprom17_set EEPROM 17 Settings
 * @brief Settings of EEPROM 17 Click driver.
 */

/**
 * @addtogroup eeprom17_set
 * @{
 */

/**
 * @brief EEPROM 17 memory size setting.
 * @details Specified setting for memory size of EEPROM 17 Click driver.
 */
#define EEPROM17_MEM_PAGE_BITMASK           0xF0
#define EEPROM17_MEM_PAGE_SIZE              16
#define EEPROM17_MEM_BANK_SIZE              256

/**
 * @brief EEPROM 17 bank selection setting.
 * @details Specified setting for bank selection of EEPROM 17 Click driver.
 */
#define EEPROM17_BANK_SEL_0                 0x00
#define EEPROM17_BANK_SEL_1                 0x01

/**
 * @brief EEPROM 17 device address setting.
 * @details Specified setting for device slave address selection of
 * EEPROM 17 Click driver.
 */
#define EEPROM17_DEVICE_ADDRESS_0           0x50
#define EEPROM17_DEVICE_ADDRESS_1           0x52

/*! @} */ // eeprom17_set

/**
 * @defgroup eeprom17_map EEPROM 17 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 17 Click driver.
 */

/**
 * @addtogroup eeprom17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 17 Click to the selected MikroBUS.
 */
#define EEPROM17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wc = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // eeprom17_map
/*! @} */ // eeprom17

/**
 * @brief EEPROM 17 Click context object.
 * @details Context object definition of EEPROM 17 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wc;           /**< Write control/disable pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} eeprom17_t;

/**
 * @brief EEPROM 17 Click configuration object.
 * @details Configuration object definition of EEPROM 17 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t wc;              /**< Write control/disable pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} eeprom17_cfg_t;

/**
 * @brief EEPROM 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM17_OK = 0,
    EEPROM17_ERROR = -1

} eeprom17_return_value_t;

/*!
 * @addtogroup eeprom17 EEPROM 17 Click Driver
 * @brief API for configuring and manipulating EEPROM 17 Click driver.
 * @{
 */

/**
 * @brief EEPROM 17 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom17_cfg_setup ( eeprom17_cfg_t *cfg );

/**
 * @brief EEPROM 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #eeprom17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom17_init ( eeprom17_t *ctx, eeprom17_cfg_t *cfg );

/**
 * @brief EEPROM 17 Write Memory function.
 * @details This function writes data to the EEPROM memory starting from the specified address.
 * @param[in] ctx : Click context object.
 * See #eeprom17_t object definition for detailed explanation.
 * @param[in] address : Start address in EEPROM memory.
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write (up to 16).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t eeprom17_write_memory ( eeprom17_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 17 Read Memory function.
 * @details This function reads data from the EEPROM memory starting from the specified address.
 * @param[in] ctx : Click context object.
 * See #eeprom17_t object definition for detailed explanation.
 * @param[in] address : Start address in EEPROM memory.
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read (up to 256).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t eeprom17_read_memory ( eeprom17_t *ctx, uint8_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief EEPROM 17 Set Write Control Pin function.
 * @details This function sets the state of the write control (WC) pin.
 * @param[in] ctx : Click context object.
 * See #eeprom17_t object definition for detailed explanation.
 * @param[in] state : Pin state (0 - LOW, 1 - HIGH).
 * @note Write Control/Disable pin is active high.
 */
void eeprom17_set_wc_pin ( eeprom17_t *ctx, uint8_t state );

/**
 * @brief EEPROM 17 Select Memory Bank function.
 * @details This function selects the active memory bank in the EEPROM.
 * @param[in] ctx : Click context object.
 * See #eeprom17_t object definition for detailed explanation.
 * @param[in] bank_sel : Memory bank selection (0 or 1).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t eeprom17_select_bank ( eeprom17_t *ctx, uint8_t bank_sel );

#ifdef __cplusplus
}
#endif
#endif // EEPROM17_H

/*! @} */ // eeprom17

// ------------------------------------------------------------------------ END
