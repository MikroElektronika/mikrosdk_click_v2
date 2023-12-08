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
 * @file expand8.h
 * @brief This file contains API for Expand 8 Click Driver.
 */

#ifndef EXPAND8_H
#define EXPAND8_H

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
 * @addtogroup expand8 Expand 8 Click Driver
 * @brief API for configuring and manipulating Expand 8 Click driver.
 * @{
 */

/**
 * @defgroup expand8_set Expand 8 Registers Settings
 * @brief Settings for registers of Expand 8 Click driver.
 */

/**
 * @addtogroup expand8_set
 * @{
 */

/**
 * @brief Expand 8 port adresses.
 * @details Specified port adresses of Expand 8 Click driver.
 */
#define EXPAND8_ADDR_OUT_LVL_PORT_P0                               0x00
#define EXPAND8_ADDR_OUT_LVL_PORT_P1                               0x01
#define EXPAND8_ADDR_OUT_LVL_PORT_P2                               0x02
#define EXPAND8_ADDR_OUT_LVL_PORT_P3                               0x03
#define EXPAND8_ADDR_OUT_LVL_PORT_P4                               0x04
#define EXPAND8_ADDR_OUT_LVL_PORT_P5                               0x05
#define EXPAND8_ADDR_OUT_LVL_PORT_P6                               0x06
#define EXPAND8_ADDR_OUT_LVL_PORT_P7                               0x07
#define EXPAND8_ADDR_OUT_LVL_PORT_P8                               0x08
#define EXPAND8_ADDR_OUT_LVL_PORT_P9                               0x09
#define EXPAND8_ADDR_OUT_LVL_PORT_P0_THROUGH_P9                    0x0A
#define EXPAND8_ADDR_OUT_LVL_PORT_P0_THROUGH_P3                    0x0B
#define EXPAND8_ADDR_OUT_LVL_PORT_P4_THROUGH_P7                    0x0C
#define EXPAND8_ADDR_OUT_LVL_PORT_P8_THROUGH_P9                    0x0D
#define EXPAND8_ADDR_OUT_LVL_PORT_P7_THROUGH_P0                    0x0E
#define EXPAND8_ADDR_OUT_LVL_PORT_P9_THROUGH_P8                    0x0F
#define EXPAND8_ADDR_RAM                                           0x13
#define EXPAND8_ADDR_NOP                                           0x20

/**
 * @brief Expand 8 impedance set values.
 * @details Specified impedance set values of Expand 8 Click driver.
 */
#define EXPAND8_SET_LOW_IMPEDANCE                                  0x00
#define EXPAND8_SET_HIGH_IMPEDANCE                                 0xFF

/**
 * @brief Expand 8 commands.
 * @details Specified commands of Expand 8 Click driver.
 */
#define EXPAND8_CMD_WRITE                                          0x00
#define EXPAND8_CMD_READ                                           0x80

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b expand8_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define EXPAND8_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define EXPAND8_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // expand8_set

/**
 * @defgroup expand8_map Expand 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 8 Click driver.
 */

/**
 * @addtogroup expand8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 8 Click to the selected MikroBUS.
 */
#define EXPAND8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // expand8_map
/*! @} */ // expand8

/**
 * @brief Expand 8 Click context object.
 * @details Context object definition of Expand 8 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} expand8_t;

/**
 * @brief Expand 8 Click configuration object.
 * @details Configuration object definition of Expand 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                  /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                  /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                   /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                    /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} expand8_cfg_t;

/**
 * @brief Expand 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   EXPAND8_OK = 0,
   EXPAND8_ERROR = -1

} expand8_return_value_t;

/*!
 * @addtogroup expand8 Expand 8 Click Driver
 * @brief API for configuring and manipulating Expand 8 Click driver.
 * @{
 */

/**
 * @brief Expand 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand8_cfg_setup ( expand8_cfg_t *cfg );

/**
 * @brief Expand 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #expand8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t expand8_init ( expand8_t *ctx, expand8_cfg_t *cfg );

/**
 * @brief Expand 8 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #expand8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t expand8_generic_write ( expand8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Expand 8 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #expand8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t expand8_generic_read ( expand8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );


/**
 * @brief Generic write data function.
 * @details The function write the byte of data
 * to the target 8-bit register address of the MAX7317,
 * 10-Port SPI-Interfaced I/O Expander with
 * Overvoltage and Hot-Insertion Protection on Expand 8 click board.
 * @param[in] ctx : Click context object.
 * See #expand8_t object definition for detailed explanation.
 * @param[in] addr : 7-bit Command Address.
 * @param[in] tx_data : Byte of data to write.
 * @return Nothing.
 */
void expand8_write_data ( expand8_t *ctx, uint8_t addr, uint8_t tx_data );

/**
 * @brief Generic read data function.
 * @details The function read the the byte of data
 * from the target 8-bit register address of the MAX7317,
 * 10-Port SPI-Interfaced I/O Expander with
 * Overvoltage and Hot-Insertion Protection on Expand 8 click boar.
 * @param[in] ctx : Click context object.
 * See #expand8_t object definition for detailed explanation.
 * @param[in] addr : 7-bit Command Address.
 * @return 8-bit read data.
 */
uint8_t expand8_read_data ( expand8_t *ctx, uint8_t addr );

/**
 * @brief Set port function.
 * @details The function set and configur the target port 
 * of the MAX7317, 10-Port SPI-Interfaced I/O Expander with
 * Overvoltage and Hot-Insertion Protection on Expand 8 click board.
 * @param[in] ctx : Click context object.
 * See #expand8_t object definition for detailed explanation.
 * @param sel_port : Selected Port [ 0 : 9 ].
 * @param sel_imped : Selected Impedance.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t expand8_set_port ( expand8_t *ctx, uint8_t sel_port, uint8_t sel_imped );

#ifdef __cplusplus
}
#endif
#endif // EXPAND8_H

/*! @} */ // expand8

// ------------------------------------------------------------------------ END
