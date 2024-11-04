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
 * @file mux9.h
 * @brief This file contains API for MUX 9 Click Driver.
 */

#ifndef MUX9_H
#define MUX9_H

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
 * @addtogroup mux9 MUX 9 Click Driver
 * @brief API for configuring and manipulating MUX 9 Click driver.
 * @{
 */

/**
 * @defgroup mux9_set MUX 9 Registers Settings
 * @brief Settings for registers of MUX 9 Click driver.
 */

/**
 * @addtogroup mux9_set
 * @{
 */

/**
 * @brief mux9_set MUX 9 channel selection flags.
 * @details Specified channel selection of MUX 9 Click driver.
 */
#define MUX9_SELECT_CH_1        1
#define MUX9_SELECT_CH_2        2
#define MUX9_SELECT_CH_3        3
#define MUX9_SELECT_CH_4        4
#define MUX9_SELECT_CH_5        5
#define MUX9_SELECT_CH_6        6
#define MUX9_SELECT_CH_7        7
#define MUX9_SELECT_CH_8        8

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b mux9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MUX9_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define MUX9_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // mux9_set

/**
 * @defgroup mux9_map MUX 9 MikroBUS Map
 * @brief MikroBUS pin mapping of MUX 9 Click driver.
 */

/**
 * @addtogroup mux9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MUX 9 Click to the selected MikroBUS.
 */
#define MUX9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // mux9_map
/*! @} */ // mux9

/**
 * @brief MUX 9 Click context object.
 * @details Context object definition of MUX 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;           /**< Reset pin. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} mux9_t;

/**
 * @brief MUX 9 Click configuration object.
 * @details Configuration object definition of MUX 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} mux9_cfg_t;

/**
 * @brief MUX 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MUX9_OK = 0,
    MUX9_ERROR = -1

} mux9_return_value_t;

/*!
 * @addtogroup mux9 MUX 9 Click Driver
 * @brief API for configuring and manipulating MUX 9 Click driver.
 * @{
 */

/**
 * @brief MUX 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mux9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mux9_cfg_setup ( mux9_cfg_t *cfg );

/**
 * @brief MUX 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mux9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mux9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux9_init ( mux9_t *ctx, mux9_cfg_t *cfg );

/**
 * @brief MUX 9 reset function.
 * @details This function executes the reset 
 * of the  ADG1438B Serially Controlled, ±15 V/+12 V/±5 V, 
 * 8-Channel/4-Channel, iCMOS Multiplexers/Matrix Switches
 * on the MUX 9 Click board™.
 * @param[in] ctx : Click context object.
 * See #mux9_t object definition for detailed explanation.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void mux9_reset ( mux9_t *ctx );

/**
 * @brief MUX 9 enable function.
 * @details This function turns on all switches
 * of the ADG1438B Serially Controlled, ±15 V/+12 V/±5 V, 
 * 8-Channel/4-Channel, iCMOS Multiplexers/Matrix Switches
 * on the MUX 9 Click board™.
 * @param[in] ctx : Click context object.
 * See #mux9_t object definition for detailed explanation.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void mux9_enable ( mux9_t *ctx );

/**
 * @brief MUX 9 disable function.
 * @details This function turns off all switches
 * of the ADG1438B Serially Controlled, ±15 V/+12 V/±5 V, 
 * 8-Channel/4-Channel, iCMOS Multiplexers/Matrix Switches
 * on the MUX 9 Click board™.
 * @param[in] ctx : Click context object.
 * See #mux9_t object definition for detailed explanation.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void mux9_disable ( mux9_t *ctx );

/**
 * @brief MUX 9 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mux9_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux9_generic_write ( mux9_t *ctx, uint8_t data_in );

/**
 * @brief MUX 9 active channel function.
 * @details This function enable is the selected channel
 * of the ADG1438B Serially Controlled, ±15 V/+12 V/±5 V, 
 * 8-Channel/4-Channel, iCMOS Multiplexers/Matrix Switches
 * on the MUX 9 Click board™.
 * @param[in] ctx : Click context object.
 * See #mux9_t object definition for detailed explanation.
 * @param[in] sel_ch : Selection of the desired channel [1-8].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux9_active_channel ( mux9_t *ctx, uint8_t sel_ch );

#ifdef __cplusplus
}
#endif
#endif // MUX9_H

/*! @} */ // mux9

// ------------------------------------------------------------------------ END
