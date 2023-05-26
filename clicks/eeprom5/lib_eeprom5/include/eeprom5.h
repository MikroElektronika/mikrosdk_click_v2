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
 * @file eeprom5.h
 * @brief This file contains API for EEPROM 5 Click Driver.
 */

#ifndef EEPROM5_H
#define EEPROM5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup eeprom5 EEPROM 5 Click Driver
 * @brief API for configuring and manipulating EEPROM 5 Click driver.
 * @{
 */

/**
 * @defgroup eeprom5_set EEPROM 5 Registers Settings
 * @brief Settings for registers of EEPROM 5 Click driver.
 */

/**
 * @addtogroup eeprom5_set
 * @{
 */

/**
 * @brief EEPROM 5 Commands.
 * @details Specified commands for description of EEPROM 5 Click driver.
 */
#define EEPROM5_CMD_WREN                                          0x06
#define EEPROM5_CMD_WRDI                                          0x04
#define EEPROM5_CMD_RDSR                                          0x05
#define EEPROM5_CMD_WRSR                                          0x01
#define EEPROM5_CMD_READ                                          0x03
#define EEPROM5_CMD_WRITE                                         0x02
#define EEPROM5_CMD_READ_ID                                       0x83
#define EEPROM5_CMD_WRITE_ID                                      0x82
#define EEPROM5_CMD_READ_LOCK_STATUS                              0x83
#define EEPROM5_CMD_LOCK_ID                                       0x82

/**
 * @brief EEPROM 5 Memory enable.
 * @details Specified commands for enabling and disabling memory of EEPROM 5 Click driver.
 */
#define EEPROM5_WRITE_MEMORY_DISABLE                              0x00
#define EEPROM5_WRITE_MEMORY_ENABLE                               0x01

/**
 * @brief EEPROM 5 Memory address.
 * @details Specified memory addresses of EEPROM 5 Click driver.
 */
#define EEPROM5_IDENT_PAGE_ADDR_START                           0x0000
#define EEPROM5_IDENT_PAGE_ADDR_END                             0x01FF

/**
 * @brief EEPROM 5 Significant address bit.
 * @details Specified significant address bit of EEPROM 5 Click driver.
 */
#define EEPROM5_SIGNIFICANT_ADDR_BIT_0                            0xFB
#define EEPROM5_SIGNIFICANT_ADDR_BIT_1                            0x04

/**
 * @brief EEPROM 5 Memory address.
 * @details Specified memory addresses of EEPROM 5 Click driver.
 */
#define EEPROM5_MEMORY_ADDR_START                           0x00000000ul
#define EEPROM5_MEMORY_ADDR_END                             0x0007FFFFul

/**
 * @brief EEPROM 5 Hold enable.
 * @details Specified hold enable settings of EEPROM 5 Click driver.
 */
#define EEPROM5_HOLD_DISABLE                                      0x00
#define EEPROM5_HOLD_ENABLE                                       0x01

/**
 * @brief EEPROM 5 Write protect.
 * @details Specified write protect settings of EEPROM 5 Click driver.
 */
#define EEPROM5_WRITE_PROTECT_DISABLE                             0x00
#define EEPROM5_WRITE_PROTECT_ENABLE                              0x01

/**
 * @brief EEPROM 5 Dummy.
 * @details Specified dummy data of EEPROM 5 Click driver.
 */
#define EEPROM5_DUMMY                                             0xFF

/*! @} */ // eeprom5_set

/**
 * @defgroup eeprom5_map EEPROM 5 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 5 Click driver.
 */

/**
 * @addtogroup eeprom5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 5 Click to the selected MikroBUS.
 */
#define EEPROM5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // eeprom5_map
/*! @} */ // eeprom5

/**
 * @brief EEPROM 5 Click context object.
 * @details Context object definition of EEPROM 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  hld;         /**< HOLD Function. */
    digital_out_t  wp;          /**< Write Protect. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} eeprom5_t;

/**
 * @brief EEPROM 5 Click configuration object.
 * @details Configuration object definition of EEPROM 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  hld;            /**< HOLD Function. */
    pin_name_t  wp;             /**< Write Protect. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} eeprom5_cfg_t;

/**
 * @brief EEPROM 5 Click status data object.
 * @details Status data object definition of EEPROM 5 Click driver.
 */
typedef struct
{
    uint8_t write_in_progress;
    uint8_t write_enable_latch;
    uint8_t block_protect;
    uint8_t write_protect;
    
} status_data_t;

/**
 * @brief EEPROM 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   EEPROM5_OK = 0,
   EEPROM5_ERROR = -1

} eeprom5_return_value_t;

/*!
 * @addtogroup eeprom5 EEPROM 5 Click Driver
 * @brief API for configuring and manipulating EEPROM 5 Click driver.
 * @{
 */

/**
 * @brief EEPROM 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom5_cfg_setup ( eeprom5_cfg_t *cfg );

/**
 * @brief EEPROM 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t eeprom5_init ( eeprom5_t *ctx, eeprom5_cfg_t *cfg );

/**
 * @brief EEPROM 5 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void eeprom5_generic_write ( eeprom5_t *ctx, uint32_t addr, uint8_t tx_data );

/**
 * @brief EEPROM 5 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t eeprom5_generic_read ( eeprom5_t *ctx, uint32_t addr );

/**
 * @brief Enable hold operation function.
 * @details The function enable hold operation
 * by sets the states of the HLD ( PWM ) pin
 * depending on the function argument.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param en_hold : Pause or resume any serial communications with the device.
 * 
 * @return Nothing.
 */
void eeprom5_set_hold ( eeprom5_t *ctx, uint8_t en_hold );

/**
 * @brief Enable write protect function.
 * @details The function enables write protect,
 * purpose of this input signal is to freeze the size of the area
 * of memory that is protected against Write instructions.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] en_write_protect : The contents of memory registers will be protected or not.
 * 
 * @return Nothing.
 */
void eeprom5_set_write_protect ( eeprom5_t *ctx, uint8_t en_wr_prot );

/**
 * @brief Send command function.
 * @details The function sends the desired command
 * to the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] cmd : 8-bit commands instruction.
 *
 * @return Nothing.
 */
void eeprom5_send_cmd ( eeprom5_t *ctx, uint8_t cmd );

/**
 * @brief Enable memory write function.
 * @details The function enable write depending on the function argument
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] en_wr_mem : Write enabled or disabled.
 *
 * @return Nothing.
 */
void eeprom5_enable_memory_write ( eeprom5_t *ctx, uint8_t en_wr_mem );

/**
 * @brief Get status function.
 * @details The function read status data
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[out] stat_data : Pointer to the memory location where status data be stored.
 *
 * @return Nothing.
 */
void eeprom5_get_status ( eeprom5_t *ctx, status_data_t *stat_data );

/**
 * @brief Set status function.
 * @details The function write status data
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[out] stat_data : Pointer to the memory location where status data be stored.
 *
 * @return Nothing.
 */
void eeprom5_set_status ( eeprom5_t *ctx, status_data_t stat_data );

/**
 * @brief Read EEPROM memory function.
 * @details The function read a sequential data starting
 * from the targeted 19-bit register address
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] addr : 19-bit memory address.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : Number of bytes to be read.
 *
 * @return Nothing.
 */
void eeprom5_read_memory ( eeprom5_t *ctx, uint32_t addr, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Write EEPROM memory function.
 * @details The function writes a sequential data starting
 * of the targeted 19-bit register address
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] addr : 19-bit memory address.
 * @param[in] p_tx_data : Pointer to the data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 *
 * @return Nothing.
 */
void eeprom5_write_memory ( eeprom5_t *ctx, uint32_t addr, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Read identification page function.
 * @details The function read the identification page
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] addr : 9-bit register address.
 *
 * @return
 * 8-bit read data.
 */
uint8_t eeprom5_read_ident_page ( eeprom5_t *ctx, uint16_t addr );

/**
 * @brief Write dentification page function.
 * @details The function writes the identification page
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] addr : 19-bit register address.
 * @param[in] ident_data : 8-bit data to be written.
 *
 * @return Nothing.
 */
void eeprom5_write_ident_page ( eeprom5_t *ctx, uint16_t addr, uint8_t ident_data );

/**
 * @brief Reads the identification page lock status function.
 * @details The function read the the identification page lock status
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * 
 * @return Identification page lock status data.
 */
uint8_t eeprom5_read_lock_status ( eeprom5_t *ctx );

/**
 * @brief Lock ID function.
 * @details The function lock ID instruction
 * permanently locks the Identification page in read-only mode
 * of the M95M04-DR, 4-Mbit serial SPI bus EEPROM
 * on EEPROM 5 click board.
 * @param[in] ctx : Click context object.
 * See #eeprom5_t object definition for detailed explanation.
 * @param[in] lock_id : 8-bit data to be written.
 *
 * @return Nothing.
 */
void eeprom5_lock_id ( eeprom5_t *ctx, uint8_t lock_id );

#ifdef __cplusplus
}
#endif
#endif // EEPROM5_H

/*! @} */ // eeprom5

// ------------------------------------------------------------------------ END
