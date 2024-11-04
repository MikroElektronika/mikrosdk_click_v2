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
 * @file swieeprom.h
 * @brief This file contains API for SWI EEPROM Click Driver.
 */

#ifndef SWIEEPROM_H
#define SWIEEPROM_H

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

/*!
 * @addtogroup swieeprom SWI EEPROM Click Driver
 * @brief API for configuring and manipulating SWI EEPROM Click driver.
 * @{
 */

/**
 * @defgroup swieeprom_set SWI EEPROM Registers Settings
 * @brief Settings for registers of SWI EEPROM Click driver.
 */
#define SWIEEPROM_OP_CODE_EEPROM        0xA0
#define SWIEEPROM_OP_CODE_SECURITY      0xB0
#define SWIEEPROM_OP_CODE_LOCK          0x20
#define SWIEEPROM_OP_CODE_ROM           0x70
#define SWIEEPROM_OP_CODE_FREEZE_ROM    0x10
#define SWIEEPROM_OP_CODE_ID            0xC0
#define SWIEEPROM_OP_CODE_STDN_SPEED    0xD0
#define SWIEEPROM_OP_CODE_HIGH_SPEED    0xE0

/**
 * @addtogroup swieeprom_set
 * @{
 */

/**
 * @brief SWI EEPROM device ID setting.
 * @details Specified setting for device ID of SWI EEPROM Click driver.
 */
#define SWIEEPROM_DEVICE_ID             0x00D200

/*! @} */ // swieeprom_set
/*! @} */ // swieeprom


/**
 * @brief Function pointers for gpio settings.
 * @details Function pointers for gpio settings of SWI EEPROM Click driver.
 */
typedef err_t ( *drv_reset_t ) ( void );
typedef void ( *drv_set_t ) ( void );
typedef uint8_t ( *drv_get_t ) ( void );

/**
 * @brief SWI EEPROM Click context object.
 * @details Context object definition of SWI EEPROM Click driver.
 */
typedef struct
{
    uint8_t slave_address;      /**< Device slave address. */
    
    drv_reset_t swi_reset;      /**< Function pointer to SWI reset function definition. */
    drv_set_t swi_start_stop;   /**< Function pointer to SWI start/stop function definition. */
    drv_set_t swi_logic_0;      /**< Function pointer to SWI logic 0 function definition. */
    drv_set_t swi_logic_1;      /**< Function pointer to SWI logic 1 function definition. */
    drv_get_t swi_logic_read;   /**< Function pointer to SWI logic read function definition. */

} swieeprom_t;

/**
 * @brief SWI EEPROM Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SWIEEPROM_OK = 0,
    SWIEEPROM_ERROR = -1

} swieeprom_return_value_t;

/*!
 * @addtogroup swieeprom SWI EEPROM Click Driver
 * @brief API for configuring and manipulating SWI EEPROM Click driver.
 * @{
 */

/**
 * @brief SWI EEPROM initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t swieeprom_init ( swieeprom_t *ctx );

/**
 * @brief SWI EEPROM check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t swieeprom_check_communication ( swieeprom_t *ctx );

/**
 * @brief SWI EEPROM memory write function.
 * @details This function writes data to the specified memory address.
 * @param[in] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @param[in] start_addr : Address byte [0-127].
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t swieeprom_mem_write ( swieeprom_t *ctx, uint8_t start_addr, uint8_t data_in );

/**
 * @brief SWI EEPROM memory write page function.
 * @details This function writes data to the specified memory address page.
 * @param[in] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @param[in] start_addr : Address byte [0-127].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes (up to 8 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t swieeprom_mem_write_page ( swieeprom_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief SWI EEPROM memory read function.
 * @details This function reads data from the specified memory address.
 * @param[in] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @param[in] start_addr : Address byte [0-127].
 * @param[out] data_out : Read data.
 * @param[in] len : Number of data bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t swieeprom_mem_read ( swieeprom_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief SWI EEPROM memory clear function.
 * @details This function clears the whole memory to zero.
 * @param[in] ctx : Click context object.
 * See #swieeprom_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t swieeprom_mem_clear ( swieeprom_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SWIEEPROM_H

/*! @} */ // swieeprom

// ------------------------------------------------------------------------ END
