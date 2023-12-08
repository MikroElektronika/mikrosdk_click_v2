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
 * @file excelonultra.h
 * @brief This file contains API for Excelon-Ultra Click Driver.
 */

#ifndef EXCELONULTRA_H
#define EXCELONULTRA_H

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

/*!
 * @addtogroup excelonultra Excelon-Ultra Click Driver
 * @brief API for configuring and manipulating Excelon-Ultra Click driver.
 * @{
 */

/**
 * @defgroup excelonultra_cmd Excelon-Ultra Command List
 * @brief List of commands of Excelon-Ultra Click driver.
 */

/**
 * @addtogroup excelonultra_cmd
 * @{
 */

/**
 * @brief Excelon-Ultra Write Enable Control commands.
 * @details Specified commands for write enable of Excelon-Ultra Click driver.
 */
#define EXCELONULTRA_CMD_WREN       0x06/*< Write Enable*/
#define EXCELONULTRA_CMD_WRDI       0x04/*< Write Disable*/

/**
 * @brief Excelon-Ultra Register Access commands.
 * @details Specified commands for register access of Excelon-Ultra Click driver.
 */
#define EXCELONULTRA_CMD_WRSR       0x01/*< Write Status Register 1*/
#define EXCELONULTRA_CMD_RDSR1      0x05/*< Read Status Register 1*/
#define EXCELONULTRA_CMD_RDSR2      0x07/*< Read Status Register 2*/
#define EXCELONULTRA_CMD_RDCR1      0x32/*< Read Status Configuration Register 1*/
#define EXCELONULTRA_CMD_RDCR2      0x3F/*< Read Status Configuration Register 2*/
#define EXCELONULTRA_CMD_RDCR4      0x45/*< Read Status Configuration Register 4*/
#define EXCELONULTRA_CMD_RDCR5      0x5E/*< Read Status Configuration Register 5*/
#define EXCELONULTRA_CMD_WRAR       0x71/*< Write Any Register*/
#define EXCELONULTRA_CMD_RDAR       0x65/*< Rrite Any Register*/

/**
 * @brief Excelon-Ultra Memory control commands.
 * @details Specified commands for memory control of Excelon-Ultra Click driver.
 */
#define EXCELONULTRA_CMD_READ       0x03/*< Memory Read*/
#define EXCELONULTRA_CMD_FAST_READ  0x0B/*< Memory Fast Read*/
#define EXCELONULTRA_CMD_WRITE      0x02/*< Memory Write*/
#define EXCELONULTRA_CMD_FAST_WRITE 0xDA/*< Memory Fast Write*/
#define EXCELONULTRA_CMD_SSWR       0x42/*< Special Sector Write*/
#define EXCELONULTRA_CMD_SSRD       0x4B/*< Special Sector Read*/

/**
 * @brief Excelon-Ultra ECC and CRC commands.
 * @details Specified commands for  Error Correction Code and 
 * Cyclic Redundancy Check of Excelon-Ultra Click driver.
 */
#define EXCELONULTRA_CMD_CLECC      0x1B/*< Clear ECC Register*/
#define EXCELONULTRA_CMD_ECCRD      0x19/*< ECC Status Read*/
#define EXCELONULTRA_CMD_CRCC       0x5B/*< CRC Calculation*/
#define EXCELONULTRA_CMD_EPCS       0x75/*< CRC Suspend*/
#define EXCELONULTRA_CMD_EPCR       0x7A/*< CRC Resume*/

/**
 * @brief Excelon-Ultra Identication commands.
 * @details Specified commands for identication of Excelon-Ultra Click driver.
 */
#define EXCELONULTRA_CMD_RUID       0x4C/*< Read Unique ID*/
#define EXCELONULTRA_CMD_RDID       0x9F/*< Read Device ID*/
#define EXCELONULTRA_CMD_WRSN       0xC2/*< Write Serial Number*/
#define EXCELONULTRA_CMD_RDSN       0xC3/*< Read Serial Number*/

/**
 * @brief Excelon-Ultra Power and reset commands.
 * @details Specified commands for power and reset of Excelon-Ultra Click driver.
 */
#define EXCELONULTRA_CMD_DPD        0xB9/*< Deep Power Down*/
#define EXCELONULTRA_CMD_HBN        0xBA/*< Hibernate Mode*/
#define EXCELONULTRA_CMD_RSTEN      0x66/*< Reset Enable*/
#define EXCELONULTRA_CMD_RST        0x99/*< Software Reset*/


/*! @} */ // excelonultra_cmd

/**
 * @defgroup excelonultra_set Excelon-Ultra Registers Settings
 * @brief Settings for registers of Excelon-Ultra Click driver.
 */

/**
 * @addtogroup excelonultra_set
 * @{
 */

/**
 * @brief Excelon-Ultra description setting.
 * @details Specified setting for description of Excelon-Ultra Click driver.
 */
#define EXCELONULTRA_MAX_MEMORY_ADDRESS 0x1FFFFF

/*! @} */ // excelonultra_set

/**
 * @defgroup excelonultra_map Excelon-Ultra MikroBUS Map
 * @brief MikroBUS pin mapping of Excelon-Ultra Click driver.
 */

/**
 * @addtogroup excelonultra_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Excelon-Ultra Click to the selected MikroBUS.
 */
#define EXCELONULTRA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // excelonultra_map
/*! @} */ // excelonultra

/**
 * @brief Excelon-Ultra Click context object.
 * @details Context object definition of Excelon-Ultra Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset. */
    digital_out_t  wp;          /**< Write protect. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    //Static variables
    uint8_t unique_id[ 8 ];     /**< 8 bytes of unique ID. */
    uint16_t manufacturer_id;   /**< Manufacturer ID. */
    uint16_t product_id;        /**< Product ID. */
    uint8_t density_id;         /**< Density ID. */
    uint8_t die_rev;            /**< Die Revision. */

} excelonultra_t;

/**
 * @brief Excelon-Ultra Click configuration object.
 * @details Configuration object definition of Excelon-Ultra Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;            /**< Reset. */
    pin_name_t  wp;             /**< Write protect. */

    // Communication variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} excelonultra_cfg_t;

/**
 * @brief Excelon-Ultra Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   EXCELONULTRA_OK = 0,
   EXCELONULTRA_ERROR = -1

} excelonultra_return_value_t;

/*!
 * @addtogroup excelonultra Excelon-Ultra Click Driver
 * @brief API for configuring and manipulating Excelon-Ultra Click driver.
 * @{
 */

/**
 * @brief Excelon-Ultra configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #excelonultra_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void excelonultra_cfg_setup ( excelonultra_cfg_t *cfg );

/**
 * @brief Excelon-Ultra initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #excelonultra_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t excelonultra_init ( excelonultra_t *ctx, excelonultra_cfg_t *cfg );

/**
 * @brief Excelon-Ultra default configuration function.
 * @details This function executes a default configuration of Excelon-Ultra
 * click board.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t excelonultra_default_cfg ( excelonultra_t *ctx );

/**
 * @brief Send command.
 * @details This function writes a byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] cmd : Byte to send.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_send_cmd ( excelonultra_t *ctx, uint8_t cmd ) ;

/**
 * @brief Write-Read function.
 * @details This function writes selected number of bytes and then 
 * reads selected number of bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] data_in : Input write data.
 * @param[in] len_in : Number of bytes to be write.
 * @param[out] data_out : Output read data.
 * @param[in] len_out : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_generic_transfer 
( excelonultra_t *ctx, uint8_t *data_in, uint32_t len_in, uint8_t *data_out, uint32_t len_out ) ;

/**
 * @brief Excelon-Ultra data writing function.
 * @details This function writes a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_generic_write ( excelonultra_t *ctx, uint8_t *data_in, uint32_t len_in );

/**
 * @brief Get device IDs.
 * @details This function reads Device ID and Unique ID and places data in context object.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_get_device_identification ( excelonultra_t *ctx );

/**
 * @brief Write byte of data to specified memory address.
 * @details This function writes a byte of data to selected memory address.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] mem_adr : Memory address to write data to.
 * @param[in] mem_data : Byte to write to memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_write_byte_to_memory ( excelonultra_t *ctx, uint32_t mem_adr, uint8_t mem_data );

/**
 * @brief Write data starting from specified memory address.
 * @details This function writes a data starting from selected memory address.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] mem_adr : Memory address to start writeing data to.
 * @param[in] mem_data : Data to write.
 * @param[in] mem_data_len : Number of bytes to write starting from selected memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_write_data_to_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint8_t *mem_data, uint32_t mem_data_len );

/**
 * @brief Read byte of data from specified memory address.
 * @details This function read a byte of data from selected memory address.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] mem_adr : Memory address to read data from.
 * @param[out] mem_data : Read byte of data from memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_read_byte_from_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint8_t *mem_data );

/**
 * @brief Read data starting from specified memory address.
 * @details This function reads a data starting from selected memory address.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] mem_adr : Memory address to start reading data from.
 * @param[out] mem_data : Read data.
 * @param[in] mem_data_len : Number of bytes to read starting from selected memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_read_data_from_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint8_t *mem_data, uint32_t mem_data_len );

/**
 * @brief Clear byte of data from specified memory address.
 * @details This function clears a byte of data to selected memory address.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] mem_adr : Memory address to clear data from.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_clear_byte_from_memory ( excelonultra_t *ctx, uint32_t mem_adr );

/**
 * @brief Clears data starting from specified memory address.
 * @details This function clears a data starting from selected memory address.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] mem_adr : Memory address to start clearing data from.
 * @param[in] mem_data_len : Number of bytes to clear starting from selected memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t excelonultra_clear_data_from_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint32_t mem_data_len );

/**
 * @brief Set reset pin state.
 * @details This function sets reset pin to selected state.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] state : Pin state to set.
 * @return Nothing
 */
void excelonultra_set_rst_pin ( excelonultra_t *ctx, uint8_t state );

/**
 * @brief Set write protect pin state.
 * @details This function sets write protect pin to selected state.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @param[in] state : Pin state to set.
 * @return Nothing
 */
void excelonultra_set_wp_pin ( excelonultra_t *ctx, uint8_t state );

/**
 * @brief Reset device.
 * @details This function resets device by toggling rst pin.
 * @param[in] ctx : Click context object.
 * See #excelonultra_t object definition for detailed explanation.
 * @return Nothing
 */
void excelonultra_hw_reset ( excelonultra_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EXCELONULTRA_H

/*! @} */ // excelonultra

// ------------------------------------------------------------------------ END
