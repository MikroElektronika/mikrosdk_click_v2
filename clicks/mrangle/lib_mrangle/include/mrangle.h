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
 * @file mrangle.h
 * @brief This file contains API for MR Angle Click Driver.
 */

#ifndef MRANGLE_H
#define MRANGLE_H

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
#include "math.h"
    

/*!
 * @addtogroup mrangle MR Angle Click Driver
 * @brief API for configuring and manipulating MR Angle Click driver.
 * @{
 */

/**
 * @defgroup mrangle_map MR Angle MikroBUS Map
 * @brief MikroBUS pin mapping of MR Angle Click driver.
 */

/**
 * @addtogroup mrangle_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MR Angle Click to the selected MikroBUS.
 */
#define MRANGLE_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.tce = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.pdn = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // mrangle_map
/*! @} */ // mrangle

/**
 * @brief MR Angle Click context object.
 * @details Context object definition of MR Angle Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  tce;         /**< Temperature coefficient compensation enable pin. */
    digital_out_t  pdn;         /**< Power-down mode enable pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */
                                
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    float  vref;                /**< Reference Voltage. */

} mrangle_t;

/**
 * @brief MR Angle Click configuration object.
 * @details Configuration object definition of MR Angle Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  tce;            /**< Temperature coefficient compensation enable pin. */
    pin_name_t  pdn;            /**< Power-down mode enable pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */
    
    float  vref;                /**< Reference Voltage. */

} mrangle_cfg_t;

/**
 * @brief MR Angle Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   MRANGLE_OK = 0,
   MRANGLE_ERROR = -1

} mrangle_return_value_t;

/**
 * @brief MR Angle Click powerdown mode value data.
 * @details Predefined enum values for driver powerdown mode values.
 */
typedef enum
{
   POWERDOWN_MODE_DISABLE = 0,
   POWERDOWN_MODE_ENABLE = 1

} mrangle_powerdown_mode_value_t;

/**
 * @brief MR Angle Click output mode value data.
 * @details Predefined enum values for driver output mode values.
 */
typedef enum
{
   OUTPUT_MODE_VOUT_SIN_COS = 0,
   OUTPUT_MODE_VOUT_TEMP = 1

} mrangle_output_mode_value_t;

/*!
 * @addtogroup mrangle MR Angle Click Driver
 * @brief API for configuring and manipulating MR Angle Click driver.
 * @{
 */

/**
 * @brief MR Angle configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mrangle_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mrangle_cfg_setup ( mrangle_cfg_t *cfg );

/**
 * @brief MR Angle initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mrangle_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_init ( mrangle_t *ctx, mrangle_cfg_t *cfg );

/**
 * @brief MR Angle default configuration function.
 * @details This function executes a default configuration of MR Angle
 * Click board™.
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void mrangle_default_cfg ( mrangle_t *ctx );

/**
 * @brief MR Angle powerdown mode function.
 * @details This function powerdown mode switches the device into Power-down mode
 * or Power-up mode of the KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™.
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[in] pd_mode : Enum values for powerdown mode.
 * @return None.
 * @note None.
 */
void mrangle_powerdown_mode ( mrangle_t *ctx, mrangle_powerdown_mode_value_t pd_mode );

/**
 * @brief MR Angle output mode function.
 * @details This function output mode switches to the desired device output mode
 * sine and cosine output mode or temperature output mode of the 
 * KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™.
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[in] output_mode : Enum values for data output mode.
 * @return None.
 * @note None.
 */
void mrangle_output_mode ( mrangle_t *ctx, mrangle_output_mode_value_t output_mode );

/**
 * @brief MR Angle data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_generic_write ( mrangle_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief MR Angle data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_generic_read ( mrangle_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief MR Angle get ADC sine function.
 * @details This function reads a sine ADC value of the 
 * KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™. 
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[out] sin_adc : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_get_adc_sin ( mrangle_t *ctx, uint16_t *sin_adc );

/**
 * @brief MR Angle get sine function.
 * @details This function reads a sine ADC value and 
 * calculate sine output signal amplitude of the 
 * KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™. 
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[out] sin : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_get_sin ( mrangle_t *ctx, float *sin );

/**
 * @brief MR Angle get ADC cosine function.
 * @details This function reads a cosine ADC value of the 
 * KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™. 
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[out] cos_adc : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_get_adc_cos ( mrangle_t *ctx, uint16_t *cos_adc );

/**
 * @brief MR Angle get cosine function.
 * @details This function reads a cosine ADC value and 
 * calculate cosine output signal amplitude of the 
 * KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™. 
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[out] cos : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_get_cos ( mrangle_t *ctx, float *cos );

/**
 * @brief MR Angle get ADC temperature function.
 * @details This function reads a temperature ADC value of the 
 * KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™. 
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[out] temp_adc : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_get_adc_temp ( mrangle_t *ctx, uint16_t *temp_adc );

/**
 * @brief MR Angle get temperature function.
 * @details This function reads a temperature data ( degree Celsius ) of the 
 * KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™. 
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_get_temperature ( mrangle_t *ctx, float *temperature );

/**
 * @brief MR Angle get angle function.
 * @details This function reads a angle data ( degree ) of the 
 * KMZ60 Angle sensor with integrated amplifier on the 
 * MR Angle Click board™. 
 * @param[in] ctx : Click context object.
 * See #mrangle_t object definition for detailed explanation.
 * @param[out] angle : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mrangle_get_angle ( mrangle_t *ctx, float *angle );

#ifdef __cplusplus
}
#endif
#endif // MRANGLE_H

/*! @} */ // mrangle

// ------------------------------------------------------------------------ END
