/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Ammonia Click driver.
 *
 * \addtogroup ammonia Ammonia Click Driver
 * \{
 */
// ----------------------------------------------------------------------------

#ifndef AMMONIA_H
#define AMMONIA_H

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

#include "drv_analog_in.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define AMMONIA_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMMONIA_OK            0
#define AMMONIA_INIT_ERROR  (-1)
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click AD conversion type selectors.
 */
typedef enum
{
    AMMONIA_ADC_SEL_AN,
    AMMONIA_ADC_SEL_SPI

} ammonia_adc_sel_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins objects

    analog_in_t an;
    digital_in_t miso;

    // Module object

    spi_master_t spi;
    pin_name_t chip_select;

    // ADC selection

    ammonia_adc_sel_t adc_sel;

} ammonia_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins

    pin_name_t an;

    // SPI settings

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    // ADC settings

    analog_in_resolution_t resolution;
    float vref;

    // ADC selection

    ammonia_adc_sel_t adc_sel;

} ammonia_cfg_t;

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 *       Be sure that the ADC selection is properly selected.
 */
void ammonia_cfg_setup ( ammonia_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals used for this Click.
 * @note The ADC selection should be set before call this function.
 */
err_t ammonia_init ( ammonia_t *ctx, ammonia_cfg_t *cfg );

/**
 * @brief Measurement Voltage Read function.
 *
 * @param ctx  Click object.
 * @param data_out  Output voltage value [V].
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads the level of the output measurement voltage.
 */
err_t ammonia_read_signal_voltage ( ammonia_t *ctx, float *data_out );

/**
 * @brief Measurement Read function.
 *
 * @param ctx  Click object.
 * @param data_out  Output measurement level [ppm].
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads the level of the measurement signal voltage and calculates
 * this value to ppm in the range from 5 to 200 ppm.
 */
err_t ammonia_read_measurement ( ammonia_t *ctx, uint16_t *data_out );

#ifdef __cplusplus
}
#endif
#endif  // AMMONIA_H

/** \} */ // End public_function group
/** \} */ // End Click Driver group

// ------------------------------------------------------------------------ END
