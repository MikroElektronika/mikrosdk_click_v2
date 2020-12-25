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
 * \file adc.h
 *
 * \brief This file contains API for ADC Click driver.
 *
 * \addtogroup adc ADC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _ADC_H_
#define _ADC_H_

#include "drv_digital_out.h"
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
#define ADC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK  ); \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS   )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Click error code definition.
 */
#define ADC_RETVAL  uint8_t

#define ADC_OK                  0x00
#define ADC_INIT_ERROR     0xFF

/**
 * @brief Click reference voltage definition.
 */
#define ADC_VREF_3300MV     3300
#define ADC_VREF_4096MV     4096
#define ADC_VREF_5000MV     5000

/**
 * @brief Click channel definition.
 */
#define ADC_CH0_OR_CH01     0x00
#define ADC_CH1_OR_CH10     0x01
#define ADC_CH2_OR_CH23     0x02
#define ADC_CH3_OR_CH32     0x03

/**
 * @brief Click context object definition.
 */
typedef struct
{
    digital_out_t cs;

    //  SPI Module.
    spi_master_t spi;
    pin_name_t chip_select;

    //  Single-Ended Channels Data.
    uint16_t  ch0;
    uint16_t  ch1;
    uint16_t  ch2;
    uint16_t  ch3;

    //  Differential Channels Data.
    uint16_t  ch01;
    uint16_t  ch10;
    uint16_t  ch23;
    uint16_t  ch32;

    //  Reference Voltage.
    uint16_t  vref;

} adc_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication GPIO Pins.
    pin_name_t  miso;
    pin_name_t  mosi;
    pin_name_t  sck;
    pin_name_t  cs;

    //  SPI Configuration Variables.
    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    //  Reference Voltage Selection.
    uint16_t  vref;

} adc_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state.
 *       Reference voltage will be set to 3V3 by default.
 */
void adc_cfg_setup( adc_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0 - Ok,
 *          0xFF - Driver init error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 */
ADC_RETVAL adc_init( adc_t *ctx, adc_cfg_t *cfg );

/**
 * @brief Get Single-Ended Channel function.
 *
 * @param ctx  Click object.
 * @param channel  Single-Ended channel selector.
 *                 (From CH0 to CH3).
 *
 * @returns Voltage level of selected channel [mV].
 *
 * @description This function returns voltage level of selected single-ended
 * channel in millivolts. The voltage value will be placed also in the
 * corresponding field of ctx object.
 */
uint16_t adc_get_single_ended_ch( adc_t *ctx, uint8_t channel );

/**
 * @brief Get Pseudo-Differential Pair function.
 *
 * @param ctx  Click object.
 * @param channel  Differential channels selector.
 *                 (CH01 means that CH0 is IN+, and CH1 is IN-).
 *
 * @returns Voltage level of selected pseudo-differential pair.
 *
 * @description This function returns voltage level of selected
 * pseudo-differential pair in millivolts. The voltage value will be placed
 * also in the corresponding field of ctx object.
 */
uint16_t adc_get_differential_ch( adc_t *ctx, uint8_t channel );

#ifdef __cplusplus
}
#endif
#endif  //  _ADC_H_

/** \} */ //  End public_function group
/// \}    //  End adc group
/*! @} */
// ------------------------------------------------------------------------ END
