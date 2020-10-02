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
 * \brief This file contains API for Buck 2 Click driver.
 *
 * \addtogroup buck2 Buck 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK2_H
#define BUCK2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BUCK2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.voset0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.voset1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.fq= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.pg= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK2_RETVAL  uint8_t

#define BUCK2_OK           0x00
#define BUCK2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup set_mode Buck power mode
 * \{
 */
#define BUCK2_MODE_ACTIVE 0x01
#define BUCK2_MODE_SLEEP  0x00
/** \} */

/**
 * \defgroup set_voltage Set voltage
 * \{
 */
#define BUCK2_VOSET_LOW   0x00
#define BUCK2_VOSET_HIGH  0x01
/** \} */

/**
 * \defgroup set_freq Set frequency
 * \{
 */
#define BUCK2_FREQ_790KHz 0x01
#define BUCK2_FREQ_565KHz 0x00
/** \} */

/**
 * \defgroup output_voltage Output voltage
 * \{
 */
#define BUCK2_SET_VOLTAGE_3300mV 0
#define BUCK2_SET_VOLTAGE_2500mV 1
#define BUCK2_SET_VOLTAGE_1800mV 2
#define BUCK2_SET_VOLTAGE_1500mV 3
/** \} */

/**
 * \defgroup channel VOSET Channel 
 * \{
 */
#define BUCK2_VOSET_CH_0 0
#define BUCK2_VOSET_CH_1 1
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
 
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t voset0;
    digital_out_t voset1;
    digital_out_t en;
    digital_out_t fq;

    // Input pins 

    digital_in_t pg;

} buck2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t voset0;
    pin_name_t voset1;
    pin_name_t en;
    pin_name_t fq;
    pin_name_t pg;

} buck2_cfg_t;

/** \} */ // End types group

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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void buck2_cfg_setup ( buck2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK2_RETVAL buck2_init ( buck2_t *ctx, buck2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Buck 2 click.
 * @note Settings that are included in the default config:
 * <pre>
 ***  Power mode options:
 *  - BUCK2_MODE_ACTIVE
 *** Set voltage 
 *  - BUCK2_SET_VOLTAGE_3300mV
 * </pre>
 */
void buck2_default_cfg ( buck2_t *ctx );

/**
 * @brief Function settings VOSET pin state 
 *
 * @param ctx  Click object.
 * @param channel  Select channel 
 * @param state  VOSET pin state 
 */
void buck2_set_voset ( buck2_t *ctx, uint8_t channel, uint8_t state );

/**
 * @brief Function settings Frequency
 * 
 * @param ctx  Click object.
 * @param freq   Select frequency
 *
 * @note Frequency: 
 * <pre>
 *  - 565kHz - if the pin FQ is set to LOW
 *  - 790kHz - if the pin FQ is set to HIGH
 * </pre>
 */
void busk2_set_frequency ( buck2_t *ctx, uint8_t freq );

/**
 * @brief Function settings chip mode
 *
 * @param ctx  Click object.
 * @param mode  Select power mode
 *
 * @note Set options:
 * <pre>
 *  - BUCK2_MODE_ACTIVE
 *  - BUCK_MODE_SLEEP
 * </pre>
 */
void buck2_set_power_mode ( buck2_t *ctx, uint8_t mode );

/**
 * @brief Function for reset chip
 *
 * @param ctx  Click object.
 */
void back2_device_reset ( buck2_t *ctx );

/**
 * @brief Function reads state PG pin
 *
 * @param ctx  Click object.
 * 
 * @return 
 *  - 0 / Not a good input voltage, 
 *  set the input voltage to a minimum of 4500mV.
 *  - 1 / Power good output voltage
 */
uint8_t buck2_get_power_good ( buck2_t *ctx  );

/**
 * @brief Function settings output voltage
 *
 * @param ctx  Click object.
 * @param voltage  Select output voltage
 *
 * @note Set options:
 * <pre>
 *  - BUCK2_SET_VOLTAGE_3300mV
 *  - BUCK2_SET_VOLTAGE_2500mV
 *  - BUCK2_SET_VOLTAGE_1800mV
 *  - BUCK2_SET_VOLTAGE_1500mV
 * </pre>
 */
void buck2_set_output_voltage ( buck2_t *ctx , uint8_t voltage );

#ifdef __cplusplus
}
#endif
#endif  // _BUCK2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
