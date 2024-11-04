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
 * \brief This file contains API for Wheatstone Click driver.
 *
 * \addtogroup wheatstone Wheatstone Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WHEATSTONE_H
#define WHEATSTONE_H

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
#include "drv_analog_in.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define WHEATSTONE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an    = MIKROBUS( mikrobus, MIKROBUS_AN )
 

/**
 * \defgroup error_code Error Code
 * \{
 */
#define WHEATSTONE_OK                   0
#define WHEATSTONE_ERROR               -1
/** \} */

/**
 * \defgroup potenciometer  Potenciometer
 * \{
 */
#define WHEATSTONE_POT_RESOLUTION       256
#define WHEATSTONE_POT_MAX              255
#define WHEATSTONE_POT_MIN              0
/** \} */

/**
 * \defgroup settings  Voltage and gain settings
 * \{
 */
#define WHEATSTONE_MAX_POT_KOHM         100
#define WHEATSTONE_R8_KOHM              1
#define WHEATSTONE_GAIN_R1_KOHM         1
#define WHEATSTONE_VCC_5V               5.0f
#define WHEATSTONE_VCC_3V3              3.3f
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
    // Modules 
    spi_master_t spi;
    analog_in_t adc;
    pin_name_t chip_select;

    // Approximate gain output level related to the potentiometer settings
    float gain;
    
} wheatstone_t;

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
    pin_name_t an;

    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;
    
    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef 

} wheatstone_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void wheatstone_cfg_setup ( wheatstone_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t wheatstone_init ( wheatstone_t *ctx, wheatstone_cfg_t *cfg );

/**
 * @brief Set potentiometer ( 0 - 100k )
 *
 * @param ctx           Click object.
 * @param pot_value     Value ( 0x00 - 0xFF )
 *
 * @details This function set 8-bit wiper positions data via SPI on the TPL0501 chip register.
 */
void wheatstone_set_potentiometer ( wheatstone_t *ctx, uint8_t pot_value );

/**
 * @brief Wheatstone read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #wheatstone_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wheatstone_read_an_pin_value ( wheatstone_t *ctx, uint16_t *data_out );

/**
 * @brief Wheatstone read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #wheatstone_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t wheatstone_read_an_pin_voltage ( wheatstone_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif  // _WHEATSTONE_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
