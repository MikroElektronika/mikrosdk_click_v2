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
 * @file buck16.h
 * @brief This file contains API for Buck 16 Click Driver.
 */

#ifndef BUCK16_H
#define BUCK16_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup buck16 Buck 16 Click Driver
 * @brief API for configuring and manipulating Buck 16 Click driver.
 * @{
 */

/**
 * @defgroup buck16_reg Buck 16 Registers List
 * @brief List of registers of Buck 16 Click driver.
 */

/**
 * @addtogroup buck16_reg
 * @{
 */

/**
 * @brief Buck 16 commands.
 * @details Specified commands for control of Buck 16 Click driver.
 */
#define BUCK16_CMD_VOLATILE_WIPER_0     0x00
#define BUCK16_CMD_NV_WIPER_0           0x20
#define BUCK16_CMD_VOLATILE_TCON        0x40
#define BUCK16_CMD_DATA_EEPROM_1        0x60
#define BUCK16_CMD_DATA_EEPROM_2        0x70
#define BUCK16_CMD_DATA_EEPROM_3        0x80
#define BUCK16_CMD_DATA_EEPROM_4        0x90
#define BUCK16_CMD_DATA_EEPROM_5        0xA0
#define BUCK16_CMD_DATA_EEPROM_6        0xB0
#define BUCK16_CMD_DATA_EEPROM_7        0xC0
#define BUCK16_CMD_DATA_EEPROM_8        0xD0
#define BUCK16_CMD_DATA_EEPROM_9        0xE0
#define BUCK16_CMD_DATA_EEPROM_10       0xF0

/**
 * @brief Buck 16 commands bits.
 * @details Specified commands bits for control of Buck 16 Click driver.
 */
#define BUCK16_WRITE                    0x00
#define BUCK16_INCREMENT                0x04
#define BUCK16_DECREMENT                0x08

/*! @} */ // buck16_reg

/**
 * @defgroup buck16_set Buck 16 Registers Settings
 * @brief Settings for registers of Buck 16 Click driver.
 */

/**
 * @addtogroup buck16_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b buck16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BUCK16_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define BUCK16_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // buck16_set

/**
 * @defgroup buck16_map Buck 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 16 Click driver.
 */

/**
 * @addtogroup buck16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 16 Click to the selected MikroBUS.
 */
#define BUCK16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); 

/*! @} */ // buck16_map
/*! @} */ // buck16

/**
 * @brief Buck 16 Click context object.
 * @details Context object definition of Buck 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Output enable. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} buck16_t;

/**
 * @brief Buck 16 Click configuration object.
 * @details Configuration object definition of Buck 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;    /**< Output enable. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} buck16_cfg_t;

/**
 * @brief Buck 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BUCK16_OK = 0,
   BUCK16_ERROR = -1

} buck16_return_value_t;

/*!
 * @addtogroup buck16 Buck 16 Click Driver
 * @brief API for configuring and manipulating Buck 16 Click driver.
 * @{
 */

/**
 * @brief Buck 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck16_cfg_setup ( buck16_cfg_t *cfg );

/**
 * @brief Buck 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buck16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buck16_init ( buck16_t *ctx, buck16_cfg_t *cfg );

/**
 * @brief Data writing function.
 * @details This function writes a data to the selected command.
 * @param[in] ctx : Click context object.
 * See #buck16_t object definition for detailed explanation.
 * @param[in] cmd : Command to send.
 * @param[in] cmd_bits : Configuration command bits.
 * @param[in] tx_data : Command data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buck16_generic_write ( buck16_t *ctx, uint8_t cmd, uint8_t cmd_bits, uint16_t tx_data );

/**
 * @brief Enable/Disable voltage output.
 * @details This function sets pin that enables or disables voltage output.
 * @param[in] ctx : Click context object.
 * See #buck16_t object definition for detailed explanation.
 * @param[in] enable : Pin state to set.
 * @return Nothing.
 */
void buck16_enable_output ( buck16_t *ctx, uint8_t enable );

/**
 * @brief Set potentiometer resistivity.
 * @details This function sets potentiometer value.
 * @param[in] ctx : Click context object.
 * See #buck16_t object definition for detailed explanation.
 * @param[in] rwb : Resistivity to set with potentiometer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buck16_set_potentiometer ( buck16_t *ctx, uint16_t rwb );

/**
 * @brief Set output voltage.
 * @details This function sets voltage value on output.
 * @param[in] ctx : Click context object.
 * See #buck16_t object definition for detailed explanation.
 * @param[in] vout : Output voltage to set in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Output voltage depends of VCC. 
 * Vout value is in range 800-5500.
 */
err_t buck16_set_output ( buck16_t *ctx, uint16_t vout );


#ifdef __cplusplus
}
#endif
#endif // BUCK16_H

/*! @} */ // buck16

// ------------------------------------------------------------------------ END
