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
 * @file reram2.h
 * @brief This file contains API for ReRAM 2 Click Driver.
 */

#ifndef RERAM2_H
#define RERAM2_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup reram2 ReRAM 2 Click Driver
 * @brief API for configuring and manipulating ReRAM 2 Click driver.
 * @{
 */

/**
 * @defgroup reram2_reg ReRAM 2 Command List
 * @brief List of commands of ReRAM 2 Click driver.
 */

/**
 * @addtogroup reram2_cmd
 * @{
 */

/**
 * @brief ReRAM 2 description commands.
 * @details Specified commands for description of ReRAM 2 Click driver.
 */
#define RERAM2_CMD_WREN              0x06
#define RERAM2_CMD_WRDI              0x04
#define RERAM2_CMD_RDSR              0x05
#define RERAM2_CMD_WRSR              0x01
#define RERAM2_CMD_READ              0x03
#define RERAM2_CMD_WRITE             0x02
#define RERAM2_CMD_RDID              0x9F
#define RERAM2_CMD_RDUID             0x83
#define RERAM2_CMD_SLEEP             0xB9
#define RERAM2_CMD_PWDN              0xE2

/*! @} */ // reram2_cmd

/**
 * @defgroup reram2_set ReRAM 2 Registers Settings
 * @brief Settings for registers of ReRAM 2 Click driver.
 */

/**
 * @addtogroup reram2_set
 * @{
 */

/**
 * @brief ReRAM 2 Device ID values.
 * @details Specified Device ID values for description of ReRAM 2 Click driver.
 */
#define RERAM2_DEVICE_ID             0x047FAA03
#define RERAM2_MANUFACTURER_ID       0x04
#define RERAM2_CONTINUATION_CODE     0x7F
#define RERAM2_PRODUCT_ID            0xAA03

/**
 * @brief ReRAM 2 Hold pin state.
 * @details Specified Hold pin state for description of ReRAM 2 Click driver.
 */
#define RERAM2_HOLD_ENABLE                                      0x00
#define RERAM2_HOLD_DISABLE                                     0x01

/**
 * @brief ReRAM 2 Write protect pin state.
 * @details Specified Write protect pin state for description of ReRAM 2 Click driver.
 */
#define RERAM2_WP_ENABLE                                        0x00
#define RERAM2_WP_DISABLE                                       0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b reram2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define RERAM2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define RERAM2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // reram2_set

/**
 * @defgroup reram2_map ReRAM 2 MikroBUS Map
 * @brief MikroBUS pin mapping of ReRAM 2 Click driver.
 */

/**
 * @addtogroup reram2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ReRAM 2 Click to the selected MikroBUS.
 */
#define RERAM2_MAP_MIKROBUS( cfg, mikrobus )        \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.ho = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // reram2_map
/*! @} */ // reram2

/**
 * @brief ReRAM 2 Click context object.
 * @details Context object definition of ReRAM 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  ho;         /**< Description. */
    digital_out_t  wp;         /**< Description. */

    // Modules
    spi_master_t  spi;         /**< SPI driver object. */

    pin_name_t  chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} reram2_t;

/**
 * @brief ReRAM 2 Click configuration object.
 * @details Configuration object definition of ReRAM 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  ho;      /**< Description. */
    pin_name_t  wp;      /**< Description. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} reram2_cfg_t;

/**
 * @brief ReRAM 2 Click status object.
 * @details Status object definition of ReRAM 2 Click driver.
 */
typedef struct
{
    uint8_t  write_protect;
    uint8_t  block_protect;
    uint8_t  write_enable_latch;
    uint8_t  write_in_progress;

} reram2_status_t;

/**
 * @brief ReRAM 2 Click status object.
 * @details Status object definition of ReRAM 2 Click driver.
 */
typedef struct
{
    uint8_t   manufacturer_id;
    uint8_t   continuation_code;
    uint16_t  product_id;
    uint8_t   lot_id[ 5 ];
    uint8_t   wafer_id;
    uint16_t  chip_id;

} reram2_dev_id_t;

/**
 * @brief ReRAM 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RERAM2_OK = 0,
    RERAM2_ERROR = -1

} reram2_return_value_t;

/*!
 * @addtogroup reram2 ReRAM 2 Click Driver
 * @brief API for configuring and manipulating ReRAM 2 Click driver.
 * @{
 */

/**
 * @brief ReRAM 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #reram2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void reram2_cfg_setup ( reram2_cfg_t *cfg );

/**
 * @brief ReRAM 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #reram2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_init ( reram2_t *ctx, reram2_cfg_t *cfg );

/**
 * @brief ReRAM 2 default configuration function.
 * @details This function executes a default configuration of ReRAM 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t reram2_default_cfg ( reram2_t *ctx );

/**
 * @brief ReRAM 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_generic_write ( reram2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ReRAM 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_generic_read ( reram2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ReRAM 2 set hold function.
 * @details This function set hold by setting the HO pin state
 * of the MB85AS8MT Resistive Random Access Memory 
 * on the ReRAM 2 board™.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[in] en_hold : 
 *         @li @c 0 ( RERAM2_HOLD_ENABLE ) - Enable hold and pause the serial communication,
 *         @li @c 1 ( RERAM2_HOLD_DISABLE )- Disable hold and resume the serial communication.
 * @return @li @c  0 - Success,
 *
 * @note None.
 */
err_t reram2_set_hold ( reram2_t *ctx, uint8_t en_hold );

/**
 * @brief ReRAM 2 write protection function.
 * @details This function set write protection by setting the WP pin state
 * of the MB85AS8MT Resistive Random Access Memory 
 * on the ReRAM 2 board™.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[in] en_wp : 
 *         @li @c 0 ( RERAM2_WP_ENABLE ) - Store operations,
 *         @li @c 1 ( RERAM2_WP_DISABLE )- Resume the serial communication.
 * @return @li @c  0 - Success,
 *
 * @note None.
 */
err_t reram2_set_write_protect ( reram2_t *ctx, uint8_t en_wp );

/**
 * @brief ReRAM 2 wake up function.
 * @details This function performs device wake-up
 * of the MB85AS8MT Resistive Random Access Memory 
 * on the ReRAM 2 board™.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *
 * @note None.
 */
err_t reram2_wake_up ( reram2_t *ctx );

/**
 * @brief ReRAM 2 set command function.
 * @details This function writes a desired command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_send_command ( reram2_t *ctx, uint8_t cmd );

/**
 * @brief ReRAM 2 get status function.
 * @details This function reads a status register
 * of the MB85AS8MT Resistive Random Access Memory 
 * on the ReRAM 2 board™.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[out] status : Click Status object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_get_status ( reram2_t *ctx, reram2_status_t *status );

/**
 * @brief ReRAM 2 read device ID function.
 * @details This function reads a device ID
 * of the MB85AS8MT Resistive Random Access Memory 
 * on the ReRAM 2 board™.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[out] dev_id : Click Device ID object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_read_device_id ( reram2_t *ctx, reram2_dev_id_t *dev_id );

/**
 * @brief ReRAM 2 check device ID function.
 * @details This function check a device ID
 * of the MB85AS8MT Resistive Random Access Memory 
 * on the ReRAM 2 board™.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @return @li @c  0 - OK,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_check_device_id ( reram2_t *ctx );

/**
 * @brief ReRAM 2 write memory function.
 * @details This function burst write memory a desired number address
 * of data bytes starting from the selected memory address
 * of the MB85AS8MT Resistive Random Access Memory 
 * on the ReRAM 2 board™.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_write_memory ( reram2_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint16_t len );

/**
 * @brief ReRAM 2 read memory function.
 * @details This function burst reads memory a desired number address
 * of data bytes starting from the selected memory address
 * of the MB85AS8MT Resistive Random Access Memory 
 * on the ReRAM 2 board™.
 * @param[in] ctx : Click context object.
 * See #reram2_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t reram2_read_memory ( reram2_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // RERAM2_H

/*! @} */ // reram2

// ------------------------------------------------------------------------ END
