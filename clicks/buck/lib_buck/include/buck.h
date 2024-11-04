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
 * \brief This file contains API for BUCK Click driver.
 *
 * \addtogroup buck BUCK Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK_H
#define BUCK_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BUCK_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.a0= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.a1= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.pg= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK_RETVAL  uint8_t

#define BUCK_OK           0x00
#define BUCK_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_mode Device mode (Enable / Disable)
 * \{
 */
#define BUCK_DEVICE_DISABLE  0
#define BUCK_DEVICE_ENABLE   1
/** \} */

/**
 * \defgroup  frequency  Select frequency
 * \{
 */
#define BUCK_FREQ_400KHz   0x00
#define BUCK_FREQ_1200KHz  0x01
#define BUCK_FREQ_800KHz   0x02
#define BUCK_FREQ_1600KHz  0x03
/** \} */

/**
 * \defgroup  multiplexer_pin  Multiplexer pin select
 * \{
 */
#define BUCK_SET_MULTIPLEXER_A0 0
#define BUCK_SET_MULTIPLEXER_A1 1
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

    digital_out_t a0;
    digital_out_t en;
    digital_out_t a1;

    // Input pins 

    digital_in_t pg;

} buck_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t a0;
    pin_name_t en;
    pin_name_t a1;
    pin_name_t pg;

} buck_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void buck_cfg_setup ( buck_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
BUCK_RETVAL buck_init ( buck_t *ctx, buck_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for BUCK Click.
 * 
 * @note Default module configuration:
 * <pre>
 * - Set frequency ( BUCK_FREQ_400KHz )
 * - Set powermode ( BUCK_DEVICE_ENABLE )
 * </pre>
 */
void buck_default_cfg ( buck_t *ctx );

/**
 * @brief Device reset chip function
 *
 * @param ctx  Click object.
 *
 * @note Function soft reset LT3976 chip
 * by set state of CS pin from low to high.
 */
void buck_device_reset ( buck_t *ctx );

/**
 * @brief Select buck mode (Disable / Enable)
 *
 * @param ctx  Click object.
 * @param mode  Buck mode (Enable / Disable)
 */
void buck_set_mode ( buck_t *ctx, uint8_t mode );

/**
 * @brief Get state internal comparator function
 *
 * @param ctx  Click object.
 * 
 * @return
 * <pre>
 * - 1 : power good output voltage;
 * - 0 : not a good input voltage, set the input voltage to a minimum of 4500mV;
 * </pre>
 * 
 * @note Function get state internal comparator
 * by read state of INT pin on Buck Click.
 */
uint8_t buck_get_power_good ( buck_t *ctx );

/**
 * @brief Set multiplexer (A0 or A1) state 
 *
 * @param ctx  Click object.
 * @param mode  Buck mode (Enable / Disable)
 */
void buck_set_multiplexer_state ( buck_t *ctx, uint8_t mux, uint8_t state );

/**
 * @brief Setting the switching frequency function
 *
 * @param frequency
 * <pre>         
 * 8-bit frequency value:
 * - 0 : frequency  400 kHz, resistor  130k
 * - 1 : frequency 1200 kHz, resistor 32.4k
 * - 2 : frequency  800 kHz, resistor 54.9k
 * - 3 : frequency 1600 kHz, resistor 21.5k
 * </pre>
 * 
 * @note Function setting the switching frequency
 * to the LT3976 chip on Buck Click.
 */
void buck_switch_frequency ( buck_t *ctx, uint8_t frequency );


#ifdef __cplusplus
}
#endif
#endif  // _BUCK_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
