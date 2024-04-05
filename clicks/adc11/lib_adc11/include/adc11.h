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
 * @file adc11.h
 * @brief This file contains API for ADC 11 Click Driver.
 */

#ifndef ADC11_H
#define ADC11_H

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

/*!
 * @addtogroup adc11 ADC 11 Click Driver
 * @brief API for configuring and manipulating ADC 11 Click driver.
 * @{
 */


/**
 * @defgroup adc11_map ADC 11 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 11 Click driver.
 */

/**
 * @addtogroup adc11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 11 Click to the selected MikroBUS.
 */
#define ADC11_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // adc11_map
/*! @} */ // adc11

/**
 * @brief ADC 11 Click context object.
 * @details Context object definition of ADC 11 Click driver.
 */
typedef struct
{
    // Modules

    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} adc11_t;

/**
 * @brief ADC 11 Click configuration object.
 * @details Configuration object definition of ADC 11 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} adc11_cfg_t;

/**
 * @brief ADC 11 Click calibration object.
 * @details Calibration object definition of ADC 11 Click driver.
 */
typedef struct
{
    uint16_t zero_adc_val;
    
} adc11_calibration_data_t;

/**
 * @brief ADC 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC11_OK = 0,
    ADC11_ERROR = -1

} adc11_return_value_t;

/*!
 * @addtogroup adc11 ADC 11 Click Driver
 * @brief API for configuring and manipulating ADC 11 Click driver.
 * @{
 */

/**
 * @brief ADC 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc11_cfg_setup ( adc11_cfg_t *cfg );

/**
 * @brief ADC 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc11_init ( adc11_t *ctx, adc11_cfg_t *cfg );

/**
 * @brief ADC 11 data reading function.
 * @details This function reads a 16-bit ADC data from 
 * the LTC1864 µPower, 16-Bit, 250ksps 1- and 2-Channel ADCs in MSOP 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc11_t object definition for detailed explanation.
 * @param[out] adc_data : Output read ADC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc11_generic_read ( adc11_t *ctx, uint16_t *adc_data );

/**
 * @brief ADC 11 set calibration function.
 * @details This function sets the calibration value into the calibration data structure of
 * the LTC1864 µPower, 16-Bit, 250ksps 1- and 2-Channel ADCs in MSOP 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc11_t object definition for detailed explanation.
 * @param[out] adc_val : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The function samples ADC 100 times in short intervals of 1 millisecond,
 * which makes the total delay in function approximately 100 millisecond.
 */
err_t adc11_set_calibration ( adc11_t *ctx, adc11_calibration_data_t *adc_val );

/**
 * @brief ADC 11 get voltage function.
 * @details This function read ADC value and calculate voltage ( V ) of
 * the LTC1864 µPower, 16-Bit, 250ksps 1- and 2-Channel ADCs in MSOP 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc11_t object definition for detailed explanation.
 * @param[out] voltage : voltage data ( V ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The function samples ADC 100 times in short intervals of 1 millisecond,
 * which makes the total delay in function approximately 100 millisecond.
 */
err_t adc11_get_voltage ( adc11_t *ctx, adc11_calibration_data_t *adc_val, float *voltage );


#ifdef __cplusplus
}
#endif
#endif // ADC11_H

/*! @} */ // adc11

// ------------------------------------------------------------------------ END
