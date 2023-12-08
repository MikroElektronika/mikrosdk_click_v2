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
 * @file eeprom9.h
 * @brief This file contains API for EEPROM 9 Click Driver.
 */

#ifndef EEPROM9_H
#define EEPROM9_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup eeprom9 EEPROM 9 Click Driver
 * @brief API for configuring and manipulating EEPROM 9 Click driver.
 * @{
 */

/**
 * @defgroup eeprom9_set EEPROM 9 Registers Settings
 * @brief Settings for registers of EEPROM 9 Click driver.
 */

/**
 * @addtogroup eeprom9_set
 * @{
 */

/**
 * @brief EEPROM 9 description setting.
 * @details Specified setting for description of EEPROM 9 Click driver.
 */
#define EEPROM9_HOLD_DISABLE                                    0x00
#define EEPROM9_HOLD_ENABLE                                     0x01
#define EEPROM9_WRITE_PROTECT_DISABLE                           0x00
#define EEPROM9_WRITE_PROTECT_ENABLE                            0x01
#define EEPROM9_WRITE_ENABLE                                    0x00
#define EEPROM9_WRITE_DISABLE                                   0x01

/**
 * @brief EEPROM 9 Status register setting.
 * @details Specified status register settinge of EEPROM 9 Click driver.
 */
#define EEPROM9_SRWD_MASK                                       0x80
#define EEPROM9_TB_MASK                                         0x40
#define EEPROM9_BP2_MASK                                        0x10
#define EEPROM9_BP1_MASK                                        0x08
#define EEPROM9_BP0_MASK                                        0x04
#define EEPROM9_WEL_MASK                                        0x02
#define EEPROM9_WIP_MASK                                        0x01

/**
 * @brief EEPROM 9 Manufacturer code.
 * @details Specified Manufacturer code of EEPROM 9 Click driver.
 */
#define EEPROM9_ST_MANUFACTURER_CODE                            0x20

/**
 * @brief EEPROM 9 Memory address.
 * @details Specified memory addresses of EEPROM 9 Click driver.
 */
#define EEPROM9_MEMORY_ADDR_START                               0x00000000ul
#define EEPROM9_MEMORY_ADDR_END                                 0x003FFFFFul

/**
 * @brief EEPROM 9 Commands.
 * @details Specified commands for description of EEPROM 9 Click driver.
 */
#define EEPROM9_CMD_WREN                                        0x06
#define EEPROM9_CMD_WRDI                                        0x04
#define EEPROM9_CMD_RDSR                                        0x05
#define EEPROM9_CMD_WRSR                                        0x01
#define EEPROM9_CMD_READ                                        0x03
#define EEPROM9_CMD_FREAD                                       0x0B
#define EEPROM9_CMD_FDREAD                                      0x3B
#define EEPROM9_CMD_FQREAD                                      0x6B
#define EEPROM9_CMD_PGWR                                        0x02
#define EEPROM9_CMD_PGPR                                        0x0A
#define EEPROM9_CMD_PGER                                        0xDB
#define EEPROM9_CMD_SCER                                        0x20
#define EEPROM9_CMD_BKER                                        0xD8
#define EEPROM9_CMD_CHER                                        0xC7
#define EEPROM9_CMD_RDID                                        0x83
#define EEPROM9_CMD_FRDID                                       0x8B
#define EEPROM9_CMD_WRID                                        0x82
#define EEPROM9_CMD_DPD                                         0xB9
#define EEPROM9_CMD_RDPD                                        0xAB
#define EEPROM9_CMD_JEDPC                                       0x9F
#define EEPROM9_CMD_RDCR                                        0x15
#define EEPROM9_CMD_RDVR                                        0x85
#define EEPROM9_CMD_WRVR                                        0x81
#define EEPROM9_CMD_CLRSF                                       0x50
#define EEPROM9_CMD_RDSFDP                                      0x5A
#define EEPROM9_CMD_RSTEN                                       0x66
#define EEPROM9_CMD_RESET                                       0x99

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b eeprom9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define EEPROM9_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define EEPROM9_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // eeprom9_set

/**
 * @defgroup eeprom9_map EEPROM 9 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 9 Click driver.
 */

/**
 * @addtogroup eeprom9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 9 Click to the selected MikroBUS.
 */
#define EEPROM9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.hld  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // eeprom9_map
/*! @} */ // eeprom9

/**
 * @brief EEPROM 9 Click context object.
 * @details Context object definition of EEPROM 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;               /**< Write protection. */
    digital_out_t hld;              /**< Hold. */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} eeprom9_t;

/**
 * @brief EEPROM 9 Click configuration object.
 * @details Configuration object definition of EEPROM 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wp;              /**< Write protection. */
    pin_name_t hld;             /**< Hold. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} eeprom9_cfg_t;

/**
 * @brief EEPROM 9 Click identification data.
 * @details Configuration object definition of identification values.
 */
typedef struct
{
    uint8_t manufact_code;      /**< ST manufacturer code field. */
    uint8_t spi_code;           /**< SPI family code field. */
    uint8_t memory_density;     /**< Memory density code field. */
} id_data_t;

/**
 * @brief EEPROM 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM9_OK = 0,
    EEPROM9_ERROR = -1

} eeprom9_return_value_t;

/*!
 * @addtogroup eeprom9 EEPROM 9 Click Driver
 * @brief API for configuring and manipulating EEPROM 9 Click driver.
 * @{
 */

/**
 * @brief EEPROM 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All used pins will be set to an unconnected state.
 */
void eeprom9_cfg_setup ( eeprom9_cfg_t *cfg );

/**
 * @brief EEPROM 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom9_init ( eeprom9_t *ctx, eeprom9_cfg_t *cfg );

/**
 * @brief EEPROM 9 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom9_generic_write ( eeprom9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 9 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom9_generic_read ( eeprom9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 9 set hold pin state function.
 * @details This function sets a hold pin level.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] en_hold : Hold state.
 * @return Nothing.
 * @note None.
 */
void eeprom9_set_hold ( eeprom9_t *ctx, uint8_t en_hold );

/**
 * @brief EEPROM 9 set write protection state function.
 * @details This function sets a hold pin level.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] en_wp : Write protection state.
 * @return Nothing.
 * @note None.
 */
void eeprom9_set_write_protection ( eeprom9_t *ctx, uint8_t en_wp );

/**
 * @brief EEPROM 9 send command function.
 * @details This function writes a command byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] cmd : Command to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom9_send_cmd ( eeprom9_t *ctx, uint8_t cmd );

/**
 * @brief EEPROM 9 enable write function.
 * @details This function writes a command to enable or disable
 * writing into memory by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] en_write : Enable write state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom9_set_write_enable ( eeprom9_t *ctx, uint8_t en_write );

/**
 * @brief EEPROM 9 memory reading function.
 * @details This function reads a desired number of data bytes into memory starting from
 * the selected address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom9_read_memory ( eeprom9_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 9 memory writing function.
 * @details This function writes a desired number of data bytes into memory starting from
 * the selected address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note To use this function memory writing needs to be enabled.
 */
err_t eeprom9_write_memory ( eeprom9_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 9 read status function.
 * @details This function is used to read the status register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[out] status_data : Status register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note To use this function memory writing needs to be enabled.
 */
err_t eeprom5_get_status_reg ( eeprom9_t *ctx, uint8_t *status_data );

/**
 * @brief EEPROM 9 chip memory erase function.
 * @details This function is used to erase the whole content of the memory.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note To use this function memory writing needs to be enabled.
 */
err_t eeprom9_chip_erase ( eeprom9_t *ctx );

/**
 * @brief EEPROM 9 memory block erase function.
 * @details This function is used to erase the memory block specified by the memory address.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] block_addr : Block memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note To use this function memory writing needs to be enabled.
 */
err_t eeprom9_block_erase ( eeprom9_t *ctx, uint32_t block_addr );

/**
 * @brief EEPROM 9 memory sector erase function.
 * @details This function is used to erase the memory sector specified by the memory address.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] sector_addr : Sector memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note To use this function memory writing needs to be enabled.
 */
err_t eeprom9_sector_erase ( eeprom9_t *ctx, uint32_t sector_addr );

/**
 * @brief EEPROM 9 memory page erase function.
 * @details This function is used to erase the memory page specified by the memory address.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[in] page_addr : Page memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note To use this function memory writing needs to be enabled.
 */
err_t eeprom9_page_erase ( eeprom9_t *ctx, uint32_t page_addr );

/**
 * @brief EEPROM 9 read identification function.
 * @details This function reads an identification value by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom9_t object definition for detailed explanation.
 * @param[out] id_data : Id data values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom9_read_identification ( eeprom9_t *ctx, id_data_t *id_data  );

#ifdef __cplusplus
}
#endif
#endif // EEPROM9_H

/*! @} */ // eeprom9

// ------------------------------------------------------------------------ END
