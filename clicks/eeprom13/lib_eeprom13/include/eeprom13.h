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
 * @file eeprom13.h
 * @brief This file contains API for EEPROM 13 Click Driver.
 */

#ifndef EEPROM13_H
#define EEPROM13_H

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
 * @addtogroup eeprom13 EEPROM 13 Click Driver
 * @brief API for configuring and manipulating EEPROM 13 Click driver.
 * @{
 */

/**
 * @defgroup eeprom13_reg EEPROM 13 Registers List
 * @brief List of registers of EEPROM 13 Click driver.
 */

/**
 * @addtogroup eeprom13_reg
 * @{
 */

/**
 * @brief EEPROM 13 description register.
 * @details Specified register for description of EEPROM 13 Click driver.
 */
#define EEPROM13_REG_DEV_TYPE_IDENTIFIER       0xE000u
#define EEPROM13_REG_CFG_DEVICE_ADDRESS        0xC000u
#define EEPROM13_REG_SW_WRITE_PROTECTION       0xA000u
#define EEPROM13_REG_IDENTIFICATION_PAGE       0x0000u
#define EEPROM13_REG_IDENTIFICATION_PAGE_LOCK  0x6000u


/*! @} */ // eeprom13_reg

/**
 * @defgroup eeprom13_set EEPROM 13 Registers Settings
 * @brief Settings for registers of EEPROM 13 Click driver.
 */

/**
 * @addtogroup eeprom13_set
 * @{
 */

/**
 * @brief EEPROM 13 mamory data values.
 * @details Specified mamory data values of EEPROM 13 Click driver.
 */
#define EEPROM13_MEMORY_ADDRESS_MIN            0x00000000ul
#define EEPROM13_MEMORY_ADDRESS_MAX            0x0001FFFFul
#define EEPROM13_MEMORY_ADDRESS_16_BIT_MASK    0x00010000ul
#define EEPROM13_MEMORY_ADDRESS_16_BIT         0x01
#define EEPROM13_PAGE_SIZE                     256
#define EEPROM13_PAGE_MAX                      512

/**
 * @brief EEPROM 13 configurable device address register data values.
 * @details CDA register data values of EEPROM 13 Click driver.
 */
#define EEPROM13_CDA_DAL_BIT_MASK              0x01
#define EEPROM13_CDA_CEA_BIT_MASK              0x03

/**
 * @brief EEPROM 13 software write protection register data values.
 * @details SWP register data values of EEPROM 13 Click driver.
 */
#define EEPROM13_SWP_WPL_MODIFIED              0x00
#define EEPROM13_SWP_WPL_FROZEN                0x01
#define EEPROM13_SWP_WPL_BIT_MASK              0x01
#define EEPROM13_SWP_BP_UPPER_QUARTE           0x00
#define EEPROM13_SWP_BP_UPPER_HALF             0x01
#define EEPROM13_SWP_BP_UPPER_THREE_QUARTE     0x02
#define EEPROM13_SWP_BP_WHOLE_MEM              0x03
#define EEPROM13_SWP_BP_BIT_MASK               0x06
#define EEPROM13_SWP_WPA_WRITE_ENABLE          0x00
#define EEPROM13_SWP_WPA_BLOCK_WRITE           0x01
#define EEPROM13_SWP_WPA_BIT_MASK              0x08

/**
 * @brief EEPROM 13 default chip enable address.
 * @details Default chip enable address of EEPROM 13 Click driver.
 */
#define EEPROM13_DEFAULT_CHIP_ENABLE_ADDRESS   0x00

/**
 * @brief EEPROM 13 device address setting.
 * @details Specified setting for device slave address selection of
 * EEPROM 13 Click driver.
 */
#define EEPROM13_DEVICE_ADDRESS_MEMORY         0x50
#define EEPROM13_DEVICE_ADDRESS_PAGE           0x58

/*! @} */ // eeprom13_set

/**
 * @defgroup eeprom13_map EEPROM 13 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 13 Click driver.
 */

/**
 * @addtogroup eeprom13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 13 Click to the selected MikroBUS.
 */
#define EEPROM13_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wc  = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // eeprom13_map
/*! @} */ // eeprom13

/**
 * @brief EEPROM 13 Click context object.
 * @details Context object definition of EEPROM 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wc;    /**< Write control pin. */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
    uint8_t chip_en_addr;     /* Chip enable address */

} eeprom13_t;

/**
 * @brief EEPROM 13 Click configuration object.
 * @details Configuration object definition of EEPROM 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t wc;     /**< Write control pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} eeprom13_cfg_t;

/**
 * @brief EEPROM 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM13_OK = 0,
    EEPROM13_ERROR = -1

} eeprom13_return_value_t;

/*!
 * @addtogroup eeprom13 EEPROM 13 Click Driver
 * @brief API for configuring and manipulating EEPROM 13 Click driver.
 * @{
 */

/**
 * @brief EEPROM 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom13_cfg_setup ( eeprom13_cfg_t *cfg );

/**
 * @brief EEPROM 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_init ( eeprom13_t *ctx, eeprom13_cfg_t *cfg );

/**
 * @brief EEPROM 13 hardware write enable function.
 * @details This function disabled hardware write protection of the entire memory 
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[out] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void eeprom13_hw_write_enable ( eeprom13_t *ctx );

/**
 * @brief EEPROM 13 hardware write enable function.
 * @details This function enabled hardware write protection of the entire memory 
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[out] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void eeprom13_hw_write_disable ( eeprom13_t *ctx );

/**
 * @brief EEPROM 13 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_generic_write ( eeprom13_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 13 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_generic_read ( eeprom13_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 13 memory write function.
 * @details This function writes a desired number of data bytes 
 * starting from the selected memory address
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address (0x00000000-0x0001FFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_memory_write ( eeprom13_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 13 memory write function.
 * @details This function reads a desired number of data bytes 
 * starting from the selected memory address
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address (0x00000000-0x0001FFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_memory_read ( eeprom13_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 13 memory page write function.
 * @details This function writes a desired number of data bytes 
 * starting from the selected memory page address
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] page_addr : Start memory page address (0-512).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_memory_page_write ( eeprom13_t *ctx, uint16_t page_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 13 memory page read function.
 * @details his function reads a desired number of data bytes 
 * starting from the selected memory page address
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] page_addr : Start memory page address (0-512).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_memory_page_read ( eeprom13_t *ctx, uint16_t page_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 13 identification page write function.
 * @details his function writes a desired number of data bytes 
 * starting from the selected identification page address
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] id_page_addr : Start identification page address (0-256).
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_id_page_write ( eeprom13_t *ctx, uint16_t id_page_addr, uint8_t *data_in );


/**
 * @brief EEPROM 13 identification page read function.
 * @details This function reads a desired number of data bytes 
 * starting from the selected identification page address
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] id_page_addr : Start identification page address (0-256).
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom13_id_page_read ( eeprom13_t *ctx, uint16_t id_page_addr, uint8_t *data_out );

/**
 * @brief EEPROM 13 configuate device address function.
 * @details This function writes a configurable device address register
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] cda : Configurable device address bits (0x00-0x03).
 * @param[in] dal : Device address lock bit:
 *         @li @c  0 - Configurable device address can be modified,
 *         @li @c  1 - Configurable device address cannot be modified.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Updating the DAL bit from 0 to 1 is an irreversible action: 
 * the C2,C1 and DAL bits cannot be updated any more. If the write control input (WC) is driven high or 
 * if the DAL bit is set to 1, the write configurable device address command is not executed 
 * and the accompanying data byte is not acknowledged.
 */
err_t eeprom13_config_dev_addr ( eeprom13_t *ctx, uint8_t cda, uint8_t dal );

/**
 * @brief EEPROM 13 software write protection function.
 * @details This function software disable/enable write protection of the entire memory 
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] wpa : Write protect activation bit:
 *         @li @c  0 - No write protection,
 *         @li @c  1 - Write protection active.
 * @param[in] dal : Block protection bits:
 *         @li @c  0 - The upper quarter of memory is write-protected,
 *         @li @c  1 - The upper half of memory is write-protected,
 *         @li @c  2 - The upper ¾ of memory is write-protected,
 *         @li @c  3 - The upper whole memory is write-protected.
 * @param[in] wpl : write protection lock bit:
 *         @li @c  0 - Can be modified,
 *         @li @c  1 - Cannot be modified and therefore the write protection register is frozen.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Updating the WPL bit from 0 to 1 is an irreversible action: 
 * the WPA, BP1, BP0 and WPL bits cannot be updated any more.
 *  If the write control input (WC) is driven high or if the WPL bit is set to 1, 
 * the write configurable device address command is not executed 
 * and the accompanying data byte is not acknowledged.
 */
err_t eeprom13_sw_write_protect ( eeprom13_t *ctx, uint8_t wpa, uint8_t bp, uint8_t wpl );

/**
 * @brief EEPROM 13 get lock/unlock status of the identification function.
 * @details This function reads the lock/unlock status of the identification
 * of the M24M01E-FMN6TP, 1-Mbit serial I�C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 13 Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom13_t object definition for detailed explanation.
 * @param[in] lock_status : Lock/unlock status of the identification.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns an acknowledge bit after the data byte 
 * if the identification page is unlocked, otherwise a NoAck bit 
 * if the identification page is locked (lock status).
 */
err_t eeprom13_get_lock_status ( eeprom13_t *ctx, uint8_t *lock_status );

#ifdef __cplusplus
}
#endif
#endif // EEPROM13_H

/*! @} */ // eeprom13

// ------------------------------------------------------------------------ END
