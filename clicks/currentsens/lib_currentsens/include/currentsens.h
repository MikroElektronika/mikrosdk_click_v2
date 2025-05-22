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
 * @file currentsens.h
 * @brief This file contains API for Current Sens Click Driver.
 */

#ifndef CURRENTSENS_H
#define CURRENTSENS_H

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
#include "drv_analog_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup currentsens Current Sens Click Driver
 * @brief API for configuring and manipulating Current Sens Click driver.
 * @{
 */

/**
 * @defgroup currentsens_set Current Sens Registers Settings
 * @brief Settings for registers of Current Sens Click driver.
 */

/**
 * @addtogroup currentsens_set
 * @{
 */

/**
 * @brief Current Sens default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Current Sens Click driver.
 */
#define CURRENTSENS_NUM_CONVERSIONS             200

/**
 * @brief Current Sens ADC setting.
 * @details Specified settings for ADC of Current Sens Click driver.
 */
#define CURRENTSENS_ADC_RESOLUTION              0x0FFF
#define CURRENTSENS_VREF_2V5                    2.5
#define CURRENTSENS_VREF_3V3                    3.3
#define CURRENTSENS_VREF_5V                     5.0

/**
 * @brief Current Sens timeout setting.
 * @details Specified setting for timeout of Current Sens Click driver.
 */
#define CURRENTSENS_TIMEOUT_MS                  2000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b currentsens_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CURRENTSENS_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define CURRENTSENS_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // currentsens_set

/**
 * @defgroup currentsens_map Current Sens MikroBUS Map
 * @brief MikroBUS pin mapping of Current Sens Click driver.
 */

/**
 * @addtogroup currentsens_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Sens Click to the selected MikroBUS.
 */
#define CURRENTSENS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // currentsens_map
/*! @} */ // currentsens

/**
 * @brief Current Sens Click driver selector.
 * @details Selects target driver interface of Current Sens Click driver.
 */
typedef enum
{
    CURRENTSENS_DRV_SEL_ADC,              /**< ADC driver descriptor. */
    CURRENTSENS_DRV_SEL_SPI               /**< I2C driver descriptor. */

} currentsens_drv_t;

/**
 * @brief Current Sens Click context object.
 * @details Context object definition of Current Sens Click driver.
 */
typedef struct
{
    analog_in_t  adc;                   /**< ADC module object. */
    spi_master_t spi;                   /**< SPI driver object. */

    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    currentsens_drv_t drv_sel;          /**< Master driver interface selector. */
    float        vref;                  /**< ADC reference voltage. */
    float        zero_curr_offset;      /**< Voltage offset for zero current value. */
    float        data_resolution;       /**< Calibrated data resolution. */

} currentsens_t;

/**
 * @brief Current Sens Click configuration object.
 * @details Configuration object definition of Current Sens Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    
    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */
    currentsens_drv_t      drv_sel;     /**< Master driver interface selector. */

} currentsens_cfg_t;

/**
 * @brief Current Sens Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENTSENS_OK = 0,
    CURRENTSENS_ERROR = -1

} currentsens_return_value_t;

/*!
 * @addtogroup currentsens Current Sens Click Driver
 * @brief API for configuring and manipulating Current Sens Click driver.
 * @{
 */

/**
 * @brief Current Sens configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentsens_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentsens_cfg_setup ( currentsens_cfg_t *cfg );

/**
 * @brief Current Sens driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #currentsens_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #currentsens_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void currentsens_drv_interface_sel ( currentsens_cfg_t *cfg, currentsens_drv_t drv_sel );

/**
 * @brief Current Sens initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #currentsens_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentsens_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentsens_init ( currentsens_t *ctx, currentsens_cfg_t *cfg );

/**
 * @brief Current Sens read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #currentsens_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentsens_read_raw_adc ( currentsens_t *ctx, uint16_t *raw_adc );

/**
 * @brief Current Sens read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #currentsens_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t currentsens_read_voltage ( currentsens_t *ctx, float *voltage );

/**
 * @brief Current Sens read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #currentsens_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t currentsens_read_voltage_avg ( currentsens_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Current Sens set vref function.
 * @details This function sets the voltage reference for Current Sens Click driver.
 * @param[in] ctx : Click context object.
 * See #currentsens_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b currentsens_init is 3.3V.
 */
err_t currentsens_set_vref ( currentsens_t *ctx, float vref );

/**
 * @brief Current Sens calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #currentsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no current flows through the sensor.
 */
err_t currentsens_calib_offset ( currentsens_t *ctx );

/**
 * @brief Current Sens calib resolution function.
 * @details This function calibrates the data resolution at the known load current.
 * @param[in] ctx : Click context object.
 * See #currentsens_t object definition for detailed explanation.
 * @param[in] calib_current : The known load current used for calibrating data resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when a known amount of load current flows through the sensor
 * and after calibrating zero current offset using currentsens_calib_offset function.
 */
err_t currentsens_calib_resolution ( currentsens_t *ctx, float calib_current );

/**
 * @brief Current Sens read current function.
 * @details This function reads the input current level [A].
 * @param[in] ctx : Click context object.
 * See #currentsens_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero current offset and data resolution.
 * Refer to currentsens_calib_offset and currentsens_calib_resolution functions.
 */
err_t currentsens_read_current ( currentsens_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // CURRENTSENS_H

/*! @} */ // currentsens

// ------------------------------------------------------------------------ END
