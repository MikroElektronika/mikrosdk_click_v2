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
 * @file spiisolator8.h
 * @brief This file contains API for SPI Isolator 8 Click Driver.
 */

#ifndef SPIISOLATOR8_H
#define SPIISOLATOR8_H

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
 * @addtogroup spiisolator8 SPI Isolator 8 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 8 Click driver.
 * @{
 */

/**
 * @addtogroup spiisolator8_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b spiisolator8_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SPIISOLATOR8_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define SPIISOLATOR8_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // spiisolator8_set

/**
 * @defgroup spiisolator8_map SPI Isolator 8 MikroBUS Map
 * @brief MikroBUS pin mapping of SPI Isolator 8 Click driver.
 */

/**
 * @addtogroup spiisolator8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SPI Isolator 8 Click to the selected MikroBUS.
 */
#define SPIISOLATOR8_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.enc = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.enp = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // spiisolator8_map
/*! @} */ // spiisolator8

/**
 * @brief SPI Isolator 8 Click context object.
 * @details Context object definition of SPI Isolator 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t enc;    /**< Enable (input) side 1 pin. */
    digital_out_t enp;    /**< Enable (output) side 2 pin. */

    // Input pins
    digital_in_t flt;     /**< Fault pin. */

    // Modules
    spi_master_t spi;     /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} spiisolator8_t;

/**
 * @brief SPI Isolator 8 Click configuration object.
 * @details Configuration object definition of SPI Isolator 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  enc;    /**< Enable (input) side 1 pin. */
    pin_name_t enp;     /**< Enable (output) side 2 pin. */
    pin_name_t flt;     /**< Fault pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} spiisolator8_cfg_t;

/**
 * @brief SPI Isolator 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPIISOLATOR8_OK = 0,
    SPIISOLATOR8_ERROR = -1

} spiisolator8_return_value_t;

/*!
 * @addtogroup spiisolator8 SPI Isolator 8 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 8 Click driver.
 * @{
 */

/**
 * @brief SPI Isolator 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spiisolator8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spiisolator8_cfg_setup ( spiisolator8_cfg_t *cfg );

/**
 * @brief SPI Isolator 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spiisolator8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator8_init ( spiisolator8_t *ctx, spiisolator8_cfg_t *cfg );

/**
 * @brief SPI Isolator 8 default configuration function.
 * @details This function executes a default configuration of SPI Isolator 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void spiisolator8_default_cfg ( spiisolator8_t *ctx );

/**
 * @brief SPI Isolator 8 enable side 1 function.
 * @details This function performs enabling a channel output pins on side 1
 * of the ISOW7741FBDFMR, Quad-Channel Digital Isolator 
 * with Integrated Low-Emissions, Low-Noise DC-DC Converter
 * on the SPI Isolator 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void spiisolator8_enc_enable ( spiisolator8_t *ctx );

/**
 * @brief SPI Isolator 8 disable side 1 function.
 * @details This function performs disabling a channel output pins on side 1
 * of the ISOW7741FBDFMR, Quad-Channel Digital Isolator 
 * with Integrated Low-Emissions, Low-Noise DC-DC Converter
 * on the SPI Isolator 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void spiisolator8_enc_disable ( spiisolator8_t *ctx );

/**
 * @brief SPI Isolator 8 enable side 2 function.
 * @details This function performs enabling a channel output pins on side 2
 * of the ISOW7741FBDFMR, Quad-Channel Digital Isolator 
 * with Integrated Low-Emissions, Low-Noise DC-DC Converter
 * on the SPI Isolator 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void spiisolator8_enp_enable ( spiisolator8_t *ctx );

/**
 * @brief SPI Isolator 8 disable side 2 function.
 * @details This function performs disabling a channel output pins on side 2
 * of the ISOW7741FBDFMR, Quad-Channel Digital Isolator 
 * with Integrated Low-Emissions, Low-Noise DC-DC Converter
 * on the SPI Isolator 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void spiisolator8_enp_disable ( spiisolator8_t *ctx );

/**
 * @brief SPI Isolator 8 get fault function.
 * @details This function get fault state, 
 * alert signal if power converter is not operating properly
 * of the ISOW7741FBDFMR, Quad-Channel Digital Isolator 
 * with Integrated Low-Emissions, Low-Noise DC-DC Converter
 * on the SPI Isolator 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @return @li @c 0 - Power converter is not operating properly,
 *         @li @c 1 - Power converter is operating properly.
 * @note None.
 */
uint8_t spiisolator8_get_fault ( spiisolator8_t *ctx );

/**
 * @brief SPI Isolator 8 data writing function.
 * @details This function writes a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator8_write ( spiisolator8_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief SPI Isolator 8 data reading function.
 * @details This function reads a desired number of data bytes
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator8_read ( spiisolator8_t *ctx, uint8_t *data_out, uint8_t len_out );

/**
 * @brief SPI Isolator 8 write then read function.
 * @details This function writes and then reads a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len_in : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len_out : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator8_write_then_read ( spiisolator8_t *ctx, uint8_t *data_in, uint8_t len_in, 
                                                          uint8_t *data_out, uint8_t len_out );

/**
 * @brief SPI Isolator 8 data transfer function.
 * @details This function writes and reads a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be transferred (write/read).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator8_transfer ( spiisolator8_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // SPIISOLATOR8_H

/*! @} */ // spiisolator8

// ------------------------------------------------------------------------ END
