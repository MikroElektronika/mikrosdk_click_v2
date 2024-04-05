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
 * \brief This file contains API for Voltmeter Click driver.
 *
 * \addtogroup voltmeter Voltmeter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VOLTMETER_H
#define VOLTMETER_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define VOLTMETER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VOLTMETER_OK                       0
#define VOLTMETER_ERROR                   -1
/** \} */

/**
 * \defgroup settings Settings
 * \{
 */
#define VOLTMETER_DATA_RESOLUTION           0x0FFF
#define VOLTMETER_VREF_ISOLATED_GND         17.05f
#define VOLTMETER_VREF_SHARED_GND           8.525f
#define VOLTMETER_NUM_ADC_CONVERSIONS       100
#define VOLTMETER_DATA_OFFSET               15
#define VOLTMETER_GND_ISO                   1
#define VOLTMETER_GND_SHARED                0
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
    // Input pins 
    digital_in_t an;
    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;
    
} voltmeter_t;

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

    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;
    
} voltmeter_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void voltmeter_cfg_setup ( voltmeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param voltmeter Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t voltmeter_init ( voltmeter_t *ctx, voltmeter_cfg_t *cfg );

/**
 * @brief Read raw ADC value function.
 *
 * @param ctx          Click object.
 *
 * @details This function reads raw ADC value.
 */
int16_t voltmeter_read_raw_data ( voltmeter_t *ctx );

/**
 * @brief Voltage calculation function.
 *
 * @param ctx          Click object.
 * @param raw_adc      Raw ADC value.
 * @param iso_gnd      1 - Isolated GND (+-17.05V), 0 - Shared GND (+-8.525V).
 *
 * @details This function converts the raw ADC value to proportional voltage level.
 */
float voltmeter_calculate_voltage ( voltmeter_t *ctx, int16_t raw_adc, uint8_t iso_gnd );
 
#ifdef __cplusplus
}
#endif
#endif  // _VOLTMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
