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
 * @file spiisolator2.h
 * @brief This file contains API for SPI Isolator 2 Click Driver.
 */

#ifndef SPIISOLATOR2_H
#define SPIISOLATOR2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup spiisolator2 SPI Isolator 2 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 2 Click driver.
 * @{
 */

/**
 * @defgroup spiisolator2_reg SPI Isolator 2 Registers List
 * @brief List of registers of SPI Isolator 2 Click driver.
 */

/**
 * @defgroup spiisolator2_set SPI Isolator 2 Registers Settings
 * @brief Settings for registers of SPI Isolator 2 Click driver.
 */

/**
 * @addtogroup spiisolator2_set
 * @{
 */

/**
 * @brief SPI Isolator 2 description setting.
 * @details Specified setting for description of SPI Isolator 2 Click driver.
 */
#define SPIISOLATOR2_EEPROM5_CMD_WREN                       0x06
#define SPIISOLATOR2_EEPROM5_CMD_WRDI                       0x04
#define SPIISOLATOR2_EEPROM5_CMD_RDSR                       0x05
#define SPIISOLATOR2_EEPROM5_CMD_WRSR                       0x01
#define SPIISOLATOR2_EEPROM5_CMD_READ                       0x03
#define SPIISOLATOR2_EEPROM5_CMD_WRITE                      0x02
#define SPIISOLATOR2_EEPROM5_CMD_READ_ID                    0x83
#define SPIISOLATOR2_EEPROM5_CMD_WRITE_ID                   0x82
#define SPIISOLATOR2_EEPROM5_CMD_READ_LOCK_STATUS           0x83
#define SPIISOLATOR2_EEPROM5_CMD_LOCK_ID                    0x82
                                                 
#define SPIISOLATOR2_OUT_DISABLE                            0x00
#define SPIISOLATOR2_OUT_ENABLE                             0x01

#define SPIISOLATOR2_DUMMY                                  0x00
                           
/*! @} */ // spiisolator2_set

/**
 * @defgroup spiisolator2_map SPI Isolator 2 MikroBUS Map
 * @brief MikroBUS pin mapping of SPI Isolator 2 Click driver.
 */

/**
 * @addtogroup spiisolator2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SPI Isolator 2 Click to the selected MikroBUS.
 */
#define SPIISOLATOR2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \

/*! @} */ // spiisolator2_map
/*! @} */ // spiisolator2

/**
 * @brief SPI Isolator 2 Click context object.
 * @details Context object definition of SPI Isolator 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en1;                              /**< Enable 1 pin. */

    // Modules
    spi_master_t  spi;                              /**< SPI driver object. */

    pin_name_t  chip_select;                        /**< Chip select pin descriptor (used for SPI driver). */

} spiisolator2_t;

/**
 * @brief SPI Isolator 2 Click configuration object.
 * @details Configuration object definition of SPI Isolator 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                 /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  en1;                                /**< Enable 1 pin. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} spiisolator2_cfg_t;

/**
 * @brief SPI Isolator 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   SPIISOLATOR2_OK = 0,
   SPIISOLATOR2_ERROR = -1

} spiisolator2_return_value_t;

/*!
 * @addtogroup spiisolator2 SPI Isolator 2 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 2 Click driver.
 * @{
 */

/**
 * @brief SPI Isolator 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spiisolator2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spiisolator2_cfg_setup ( spiisolator2_cfg_t *cfg );

/**
 * @brief SPI Isolator 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spiisolator2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator2_init ( spiisolator2_t *ctx, spiisolator2_cfg_t *cfg );

/**
 * @brief SPI Isolator 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator2_generic_write ( spiisolator2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief SPI Isolator 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator2_generic_read ( spiisolator2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief SPI Isolator 2 output enable function.
 * @details The function enable or disable output ( isolation ) of the ISO7741DWR High-Speed, 
 * Robust-EMC Reinforced and Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] en_out : Enable/disable pin.
 * @return Nothing.
 * @note None.
 */
void spiisolator2_output_enable( spiisolator2_t *ctx, uint8_t en_out );

/**
 * @brief SPI Isolator 2 send command function.
 * @details The function sends the desired command to the ISO7741DWR High-Speed, Robust-EMC Reinforced
 * and Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] cmd : 8-bit commands instruction.
 * @return Nothing.
 * @note None.
 */
void spiisolator2_set_cmd ( spiisolator2_t *ctx, uint8_t cmd );

/**
 * @brief SPI Isolator 2 write the byte of data function.
 * @details The function writes the byte of data to the targeted 8-bit
 * register address of the ISO7741DWR High-Speed, Robust-EMC Reinforced
 * and Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : 8-bit data to be written.
 * @return Nothing.
 * @note None.
 */
void spiisolator2_write_byte ( spiisolator2_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief SPI Isolator 2 read the byte of data function.
 * @details The function read a the byte of data from the targeted 8-bit
 * register address of the ISO7741DWR High-Speed, Robust-EMC Reinforced
 * and Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @return 8-bit read data.
 * @note None.
 */
uint8_t spiisolator2_read_byte ( spiisolator2_t *ctx, uint8_t reg );

/**
 * @brief SPI Isolator 2 burst write function.
 * @details The function writes sequential data starting to the targeted 8-bit register address
 * of the ISO7741DWR High-Speed, Robust-EMC Reinforced and Basic Quad-Channel Digital Isolators 
 * on SPI Isolator 2 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] p_tx_data : 8-bit data to be written.
 * @param[in] n_bytes : number of bytes to be written.
 * @return Nothing.
 * @note None.
 */
void spiisolator2_burst_write ( spiisolator2_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief SPI Isolator 2 burst read function.
 * @details The function read sequential data starting from the targeted 8-bit register address
 * of the ISO7741DWR High-Speed, Robust-EMC Reinforced and Basic Quad-Channel Digital Isolators
 * on SPI Isolator 2 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] p_rx_data : 8-bit data to be written.
 * @param[in] n_bytes : number of bytes to be written.
 * @return Nothing.
 * @note None.
 */
void spiisolator2_burst_read ( spiisolator2_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief SPI Isolator 2 multi write function.
 * @details The function writes sequential data starting of the targeted (selected) 8-bit, 16-bit, 
 * 24-bit, or 32-bit register address of the ISO7741DWR High-Speed, Robust-EMC Reinforced
 * and Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] addr : 8-bit register address.
 * @param[in] addr_n_bytes : The number of bytes of the registry address.
 * @param[in] p_tx_data : 8-bit data to be written.
 * @param[in] tx_data_n_bytes : Pointer to the data to be written.
 * @return Nothing.
 * @note None.
 */
void spiisolator2_multi_write ( spiisolator2_t *ctx, uint32_t addr, uint8_t addr_n_bytes, 
                                uint8_t *p_tx_data, uint8_t tx_data_n_bytes );

/**
 * @brief SPI Isolator 2 multi read function.
 * @details The function read sequential data starting from the targeted (selected) 8-bit, 16-bit, 
 * 24-bit, or 32-bit register address of the ISO7741DWR High-Speed, Robust-EMC Reinforced
 * and Basic Quad-Channel Digital Isolators on SPI Isolator 2 click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator2_t object definition for detailed explanation.
 * @param[in] addr : 8-bit register address.
 * @param[in] addr_n_bytes : The number of bytes of the registry address.
 * @param[in] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] tx_data_n_bytes : Number of bytes to be read.
 * @return Nothing.
 * @note None.
 */
void spiisolator2_multi_read ( spiisolator2_t *ctx, uint32_t addr, uint8_t addr_n_bytes, 
                               uint8_t *p_rx_data, uint8_t tx_data_n_bytes );

#ifdef __cplusplus
}
#endif
#endif // SPIISOLATOR2_H

/*! @} */ // spiisolator2

// ------------------------------------------------------------------------ END
