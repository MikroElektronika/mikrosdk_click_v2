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
 * @file vtohz3.h
 * @brief This file contains API for V to Hz 3 Click Driver.
 */

#ifndef VTOHZ3_H
#define VTOHZ3_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup vtohz3 V to Hz 3 Click Driver
 * @brief API for configuring and manipulating V to Hz 3 Click driver.
 * @{
 */

/**
 * @defgroup vtohz3_set V to Hz 3 Settings
 * @brief Settings for V to Hz 3 Click driver.
 */

/**
 * @addtogroup vtohz3_set
 * @{
 */

/**
 * @brief V to Hz 3 AD7740 input frequency range.
 * @details Specified AD7740 input frequency range of V to Hz 3 Click driver.
 */
#define VTOHZ3_MAXIMAL_IN_FREQUENCY     1000000
#define VTOHZ3_MINIMAL_IN_FREQUENCY     32000
#define VTOHZ3_DEFAULT_IN_FREQUENCY     100000

/**
 * @brief V to Hz 3 voltage reference selection.
 * @details Specified voltage reference selection of V to Hz 3 Click driver.
 */
#define VTOHZ3_VREF_3V3                 3.3
#define VTOHZ3_VREF_5V                  5.0
#define VTOHZ3_VREF_INTERNAL_2V5        2.5

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b vtohz3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define VTOHZ3_SET_DATA_SAMPLE_EDGE     SET_SPI_DATA_SAMPLE_EDGE
#define VTOHZ3_SET_DATA_SAMPLE_MIDDLE   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // vtohz3_set

/**
 * @defgroup vtohz3_map V to Hz 3 MikroBUS Map
 * @brief MikroBUS pin mapping of V to Hz 3 Click driver.
 */

/**
 * @addtogroup vtohz3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of V to Hz 3 Click to the selected MikroBUS.
 */
#define VTOHZ3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.buf  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fout = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // vtohz3_map
/*! @} */ // vtohz3

/**
 * @brief V to Hz 3 Click context object.
 * @details Context object definition of V to Hz 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  buf;               /**< Buffered mode select pin. */

    // Input pins
    digital_in_t   fout;              /**< Generated frequency output. */

    // Modules
    spi_master_t   spi;               /**< SPI driver object. */
    analog_in_t    adc;               /**< ADC module object. */

    pin_name_t     chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    
    uint32_t       clock_in_freq;     /**< Clock input frequency. */

} vtohz3_t;

/**
 * @brief V to Hz 3 Click configuration object.
 * @details Configuration object definition of V to Hz 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  an;                                      /**< Analog pin descriptor. */

    // Additional gpio pins
    pin_name_t  buf;                                     /**< Buffered mode select pin. */
    pin_name_t  fout;                                    /**< Generated frequency output. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */
    
    analog_in_resolution_t             resolution;       /**< ADC resolution. */
    float                              vref;             /**< ADC reference voltage. */

} vtohz3_cfg_t;

/**
 * @brief V to Hz 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VTOHZ3_OK = 0,
    VTOHZ3_ERROR = -1

} vtohz3_return_value_t;

/*!
 * @addtogroup vtohz3 V to Hz 3 Click Driver
 * @brief API for configuring and manipulating V to Hz 3 Click driver.
 * @{
 */

/**
 * @brief V to Hz 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vtohz3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vtohz3_cfg_setup ( vtohz3_cfg_t *cfg );

/**
 * @brief V to Hz 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #vtohz3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vtohz3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vtohz3_init ( vtohz3_t *ctx, vtohz3_cfg_t *cfg );

/**
 * @brief V to Hz 3 set input frequency function.
 * @details This function enables and sets output frequency of the programmable oscillator, 
 * which is the AD7740 input frequency.
 * @param[in] ctx : Click context object.
 * See #vtohz3_t object definition for detailed explanation.
 * @param[in] freq : Frequency in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The frequency is limited by the AD7740 Voltage-to-Frequency Converter to 
 * 32KHz as a minimal and 1MHz as a maximal input frequency.
 */
err_t vtohz3_set_input_frequency ( vtohz3_t *ctx, uint32_t freq );

/**
 * @brief V to Hz 3 disable input frequency function.
 * @details This function disables the output frequency of the programmable oscillator, 
 * which is the AD7740 input frequency.
 * @param[in] ctx : Click context object.
 * See #vtohz3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vtohz3_disable_input_frequency ( vtohz3_t *ctx );

/**
 * @brief V to Hz 3 set buf pin function.
 * @details This function sets the BUF pin state which is a buffered mode select pin.
 * @param[in] ctx : Click context object.
 * See #vtohz3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void vtohz3_set_buf_pin ( vtohz3_t *ctx, uint8_t state );

/**
 * @brief V to Hz 3 get fout pin function.
 * @details This function returns the FOUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #vtohz3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t vtohz3_get_fout_pin ( vtohz3_t *ctx );

/**
 * @brief V to Hz 3 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #vtohz3_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vtohz3_read_an_pin_value ( vtohz3_t *ctx, uint16_t *data_out );

/**
 * @brief V to Hz 3 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #vtohz3_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t vtohz3_read_an_pin_voltage ( vtohz3_t *ctx, float *data_out );

/**
 * @brief V to Hz 3 get frequency function.
 * @details This function converts voltage to the estimated output frequency in Hz.
 * @param[in] ctx : Click context object.
 * See #vtohz3_t object definition for detailed explanation.
 * @param[in] voltage : Voltage from AN pin.
 * @param[in] vref_in : AD7740 voltage reference input (2.5V if not connected).
 * @return Estimated output frequency in Hz.
 * @note None.
 */
uint32_t vtohz3_get_frequency ( vtohz3_t *ctx, float voltage, float vref_in );

#ifdef __cplusplus
}
#endif
#endif // VTOHZ3_H

/*! @} */ // vtohz3

// ------------------------------------------------------------------------ END
