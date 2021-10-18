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
 * @file gainamp.h
 * @brief This file contains API for GainAMP Click Driver.
 */

#ifndef GAINAMP_H
#define GAINAMP_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_analog_in.h"    

/*!
 * @addtogroup gainamp GainAMP Click Driver
 * @brief API for configuring and manipulating GainAMP Click driver.
 * @{
 */

/**
 * @defgroup gainamp_set GainAMP Registers Settings
 * @brief Settings for registers of GainAMP Click driver.
 */

/**
 * @addtogroup gainamp_set
 * @{
 */

/**
 * @brief GainAMP description setting.
 * @details Specified setting for description of GainAMP Click driver.
 */
#define GAINAMP_CHANNEL_A_x0         0x00
#define GAINAMP_CHANNEL_A_x1         0x01
#define GAINAMP_CHANNEL_A_x2         0x02
#define GAINAMP_CHANNEL_A_x5         0x03
#define GAINAMP_CHANNEL_A_x10        0x04
#define GAINAMP_CHANNEL_A_x20        0x05
#define GAINAMP_CHANNEL_A_x50        0x06
#define GAINAMP_CHANNEL_A_x100       0x07
#define GAINAMP_CHANNEL_A_SHUTDOWN   0x08

#define GAINAMP_CHANNEL_B_x0         0x00
#define GAINAMP_CHANNEL_B_x1         0x10
#define GAINAMP_CHANNEL_B_x2         0x20
#define GAINAMP_CHANNEL_B_x5         0x30
#define GAINAMP_CHANNEL_B_x10        0x40
#define GAINAMP_CHANNEL_B_x20        0x50
#define GAINAMP_CHANNEL_B_x50        0x60
#define GAINAMP_CHANNEL_B_x100       0x70
#define GAINAMP_CHANNEL_B_SHUTDOWN   0x80

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gainamp_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GAINAMP_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define GAINAMP_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gainamp_set

/**
 * @defgroup gainamp_map GainAMP MikroBUS Map
 * @brief MikroBUS pin mapping of GainAMP Click driver.
 */

/**
 * @addtogroup gainamp_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GainAMP Click to the selected MikroBUS.
 */
#define GAINAMP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // gainamp_map
/*! @} */ // gainamp

/**
 * @brief GainAMP Click context object.
 * @details Context object definition of GainAMP Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;     /**< Description. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */
    analog_in_t  adc;       /**< ADC module object. */

} gainamp_t;

/**
 * @brief GainAMP Click configuration object.
 * @details Configuration object definition of GainAMP Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;        /**< Description. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */
    
    pin_name_t  an;     /**< Analog pin descriptor. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} gainamp_cfg_t;

/**
 * @brief GainAMP Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   GAINAMP_OK = 0,
   GAINAMP_ERROR = -1

} gainamp_return_value_t;

/*!
 * @addtogroup gainamp GainAMP Click Driver
 * @brief API for configuring and manipulating GainAMP Click driver.
 * @{
 */

/**
 * @brief GainAMP configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gainamp_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gainamp_cfg_setup ( gainamp_cfg_t *cfg );

/**
 * @brief GainAMP initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gainamp_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gainamp_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp_init ( gainamp_t *ctx, gainamp_cfg_t *cfg );

/**
 * @brief GainAMP data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gainamp_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp_generic_write ( gainamp_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief GainAMP data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gainamp_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gainamp_generic_read ( gainamp_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief GainAMP read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #gainamp_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t gainamp_read_an_pin_value ( gainamp_t *ctx, uint16_t *data_out );

/**
 * @brief GainAMP read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #gainamp_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t gainamp_read_an_pin_voltage ( gainamp_t *ctx, float *data_out );

/**
 * @brief Function for reset chip of the GainAMP Click. 
 * @details This function performs hardware reset.
 * @param[in] ctx : Click context object.
 * See #gainamp_t object definition for detailed explanation.
 * @return Nothing.
 */
void gainamp_reset ( gainamp_t *ctx );

/**
 * @brief Function for sets gain of the GainAMP Click.
 * @details This function sets gain of the GainAMP Click.
 * @param[in] ctx : Click context object.
 * See #gainamp_t object definition for detailed explanation.
 * @param[in] gain : Gain that will be set.
 * @return Nothing.
 */
void gainamp_set_gain ( gainamp_t *ctx, uint8_t gain );

#ifdef __cplusplus
}
#endif
#endif // GAINAMP_H

/*! @} */ // gainamp

// ------------------------------------------------------------------------ END
