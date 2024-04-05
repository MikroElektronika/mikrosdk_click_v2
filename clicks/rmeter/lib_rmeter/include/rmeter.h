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
 * \brief This file contains API for R Meter Click driver.
 *
 * \addtogroup rmeter R Meter Click Driver
 * \{
 */

#ifndef RMETER_H
#define RMETER_H

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
#include "drv_analog_in.h"
#include "drv_spi_master.h"

/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define RMETER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ) ; \
   cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )  ; \
   cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN )  ; \
   cfg.s3   = MIKROBUS( mikrobus, MIKROBUS_RST ) ; \
   cfg.s2   = MIKROBUS( mikrobus, MIKROBUS_INT ) ; \
   cfg.s1   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RMETER_OK            0
#define RMETER_INIT_ERROR  (-1)
/** \} */

/** \} */ // End group macro

/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click callback handler definition.
 */
typedef void ( *rmeter_callback_t )( char* );

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Auto scale control pins objects.

    digital_out_t s3;
    digital_out_t s2;
    digital_out_t s1;

    // Analog input pin object.

    analog_in_t an;

    // Communication module object.

    spi_master_t spi;

    pin_name_t chip_select;

    // R Meter calculation operands.

    float ifb;      /*!< Current of feedback [Ifb]]. */

    // Callback handler.

    rmeter_callback_t callback;

} rmeter_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication pins descriptors.

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional pins descriptors.

    pin_name_t an;
    pin_name_t s3;
    pin_name_t s2;
    pin_name_t s1;

    // Module configuration settings.

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    // ADC settings.

    analog_in_resolution_t adc_resolution;  /*!< ADC resolution. */
    float adc_vref;                         /*!< ADC voltage reference value [V - recommended]. */

} rmeter_cfg_t;

/** \} */ // End types group

/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void rmeter_cfg_setup ( rmeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t rmeter_init ( rmeter_t *ctx, rmeter_cfg_t *cfg );

/**
 * @brief Callback Handler Setup function.
 *
 * @param ctx  Click object.
 * @param handler  Callback handler which will be set.
 *
 * @description This function sets a callback handler for message logging.
 */
void rmeter_set_callback_handler ( rmeter_t *ctx, rmeter_callback_t handler );

/**
 * @brief Range Setup Up To 1k9 Ohms function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the scale range up to 1k9 ohms for better sensitivity of small resistance.
 */
void rmeter_set_range_up_to_1k9_ohms ( rmeter_t *ctx );

/**
 * @brief Range Setup Up To 17k Ohms function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the scale range up to 17k ohms for better sensitivity of resistance in that range.
 */
void rmeter_set_range_up_to_17k_ohms ( rmeter_t *ctx );

/**
 * @brief Range Setup Up To 1M9 Ohms function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the scale range up to 1M9 ohms for large range of resistance.
 */
void rmeter_set_range_up_to_1M9_ohms ( rmeter_t *ctx );

/**
 * @brief Measurement Reading function.
 *
 * @param ctx  Click object.
 * @param data_out  12-bit measurement results.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads the converted measurement results.
 */
err_t rmeter_read_measurement ( rmeter_t *ctx, uint16_t *data_out );

/**
 * @brief Resistance Calculation function.
 *
 * @param ctx  Click object.
 * @param data_out  Floating value of calculated resistance [ohm].
 * @param data_in  12-bit measurement data.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function performs the all necessary calculations to get the target resistance value
 * depending on the measured data.
 * @note Before execution of this function need to set measurement range by calling functions for range setting
 * or auto scalling function.
 */
err_t rmeter_calculate_resistance ( rmeter_t *ctx, float *data_out, uint16_t data_in );

/**
 * @brief Auto Scale Range Execution function.
 *
 * @param ctx  Click object.
 * @return 12-bit measured data results.
 *
 * @description This function is able to recognize and set the necessary range of measurement of the target
 * resistance.
 */
uint16_t rmeter_auto_scale_range_execution ( rmeter_t *ctx );

/**
 * @brief AN Pin Reading function.
 *
 * @param ctx  Click object.
 * @param data_out  Analog pin converted value.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads the analog input pin (AN) value depending on the selected ADC resolution.
 */
err_t rmeter_read_an ( rmeter_t *ctx, uint16_t *data_out );

/**
 * @brief AN Voltage Level Reading function.
 *
 * @param ctx  Click object.
 * @param data_out  Analog pin voltage level [V].
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads the analog input pin (AN) voltage level depending on the selected ADC resolution
 * and ADC reference voltage.
 */
err_t rmeter_read_an_voltage ( rmeter_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif  // RMETER_H

/** \} */ // End public_function group
/** \} */ // End click Driver group

// ------------------------------------------------------------------------ END
