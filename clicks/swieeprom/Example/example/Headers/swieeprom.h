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

#ifndef SWI_EEPROM_
#define SWI_EEPROM_

#include "stdint.h"


/*!
 * @addtogroup swieeprom SWI EEPROM Click Driver
 * @brief API for configuring and manipulating SWI EEPROM Click driver.
 * @{
 */

/**
 * @brief SWI EEPROM Click ID value.
 * @details ID value for SWI EEPROM Click driver.
 */
#define SWIEEPROM_ID                        0x00D200

/**
 * @brief SWI EEPROM Click operation codes.
 * @details Operation codes for communication with SWI EEPROM Click driver.
 */
typedef enum
{
    SWIEEPROM_OP_CODE_EEPROM                = 0xA0,
    SWIEEPROM_OP_CODE_SECURITY              = 0xB0,
    SWIEEPROM_OP_CODE_LOCK                  = 0x20,
    SWIEEPROM_OP_CODE_ROM                   = 0x70,
    SWIEEPROM_OP_CODE_FREEZE_ROM            = 0x10,
    SWIEEPROM_OP_CODE_ID                    = 0xC0,
    SWIEEPROM_OP_CODE_STDN_SPEED            = 0xD0,
    SWIEEPROM_OP_CODE_HIGH_SPEED            = 0xE0
}swieeprom_op_code_t;

/**
 * @brief SWI EEPROM Click return values.
 * @details Return values of SWI EEPROM Click driver functions.
 */
typedef enum
{
    SWIEEPROM_RET_VAL_OK                    = 0,
    SWIEEPROM_RET_VAL_ERROR                 = -1,
    SWIEEPROM_RET_VAL_ERROR_NO_DEVICE_FOUND = -2,
    SWIEEPROM_RET_VAL_ERROR_SLAVE_ADDRESS   = -3,

    SWIEEPROM_RET_VAL_ERROR_OP_CODE         = -4,
    SWIEEPROM_RET_VAL_ERROR_ADR             = -5,
    SWIEEPROM_RET_VAL_ERROR_DATA            = -6,
    SWIEEPROM_RET_VAL_ERROR_ID              = -7
}swieeprom_return_value_t;

/**
 * @brief SWI EEPROM Click context object.
 * @details Context object definition of SWI EEPROM Click driver.
 */
typedef struct
{
    // Slave address
    uint8_t slave_address;

} swieeprom_t;

/**
 * @brief SWI EEPROM initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #${NAME_LOWERCASE}_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - No device found.
 *         @li @c -3 - Slave address missing. 
 */
swieeprom_return_value_t swieeprom_init ( swieeprom_t *ctx );

/**
 * @brief SWI EEPROM check device ID.
 * @details This function reads device ID and checks if it's correct.
 * @param[in] ctx : Click context object.
 * See #${NAME_LOWERCASE}_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -4 - OP CODE Error.
 *         @li @c -7 - ID Error. 
 */
swieeprom_return_value_t swieeprom_read_id ( swieeprom_t *ctx );

/**
 * @brief SWI EEPROM write byte to memory.
 * @details This function writes one byte of data to specific memory address.
 * @param[in] ctx : Click context object.
 * See #${NAME_LOWERCASE}_t object definition for detailed explanation.
 * @param[in] mem_adr : Address that will be written to.
 * @param[in] mem_data : Data that will be written.
 * @return @li @c  0 - Success,
 *         @li @c -4 - OP CODE Error.
 *         @li @c -5 - Memory address Error. 
 *         @li @c -6 - Data Error. 
 */
swieeprom_return_value_t swieeprom_write_to_memory ( swieeprom_t *ctx, uint8_t mem_adr, uint8_t mem_data );

/**
 * @brief SWI EEPROM read byte from memory.
 * @details This function reads one byte of data from specific memory address.
 * @param[in] ctx : Click context object.
 * See #${NAME_LOWERCASE}_t object definition for detailed explanation.
 * @param[in] mem_adr : Address that will be read from.
 * @param[out] mem_data : Data that will be read.
 * @return @li @c  0 - Success,
 *         @li @c -4 - OP CODE Error.
 *         @li @c -5 - Memory address Error. 
 */
swieeprom_return_value_t swieeprom_read_from_memory ( swieeprom_t *ctx, uint8_t mem_adr, uint8_t *mem_data );

/**
 * @brief SWI EEPROM write data to memory.
 * @details This function writes @b buf_len bytes of data starting from specific memory address.
 * @param[in] ctx : Click context object.
 * See #${NAME_LOWERCASE}_t object definition for detailed explanation.
 * @param[in] start_mem_adr : Address that write will start with.
 * @param[in] tx_buf : Data that will be written.
 * @param[in] buf_len : Data length.
 * @return @li @c  0 - Success,
 *         @li @c -4 - OP CODE Error.
 *         @li @c -5 - Memory address Error. 
 *         @li @c -6 - Data Error. 
 */
swieeprom_return_value_t swieeprom_write_data_to_memory ( swieeprom_t *ctx, uint8_t start_mem_adr, uint8_t *tx_buf, uint16_t buf_len );

/**
 * @brief SWI EEPROM read data from memory.
 * @details This function reads @b buf_len bytes of data starting from specific memory address.
 * @param[in] ctx : Click context object.
 * See #${NAME_LOWERCASE}_t object definition for detailed explanation.
 * @param[in] start_mem_adr : Address that read will start with.
 * @param[out] rx_buf : Data that will be read.
 * @param[in] buf_len : Data length.
 * @return @li @c  0 - Success,
 *         @li @c -4 - OP CODE Error.
 *         @li @c -5 - Memory address Error. 
 */
swieeprom_return_value_t swieeprom_read_data_from_memory ( swieeprom_t *ctx, uint8_t start_mem_adr, uint8_t *rx_buf, uint16_t buf_len );

/**
 * @brief SWI EEPROM clears data from memory.
 * @details This function clears @b buf_len bytes of data starting from specific memory address.
 * @param[in] ctx : Click context object.
 * See #${NAME_LOWERCASE}_t object definition for detailed explanation.
 * @param[in] start_mem_adr : Address that write will start with.
 * @param[in] buf_len : Data length.
 * @return @li @c  0 - Success,
 *         @li @c -4 - OP CODE Error.
 *         @li @c -5 - Memory address Error. 
 *         @li @c -6 - Data Error. 
 */
swieeprom_return_value_t swieeprom_clear_data_from_memory ( swieeprom_t *ctx, uint8_t start_mem_adr, uint16_t buf_len );

#endif

/*! @} */ // swieeprom

// ------------------------------------------------------------------------ END
