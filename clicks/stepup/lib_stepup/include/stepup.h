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
 * \brief This file contains API for Step Up Click driver.
 *
 * \addtogroup stepup Step Up Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef STEPUP_H
#define STEPUP_H

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

#define STEPUP_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.mod = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define STEPUP_RETVAL  uint8_t

#define STEPUP_OK           0x00
#define STEPUP_INIT_ERROR   0xFF
#define STEPUP_ERROR        (-1)
/** \} */

/**
 * \defgroup stepup_config    Step up configuration
 * \{
 */
#define STEPUP_CFG_VREF_BUFFERED         1
#define STEPUP_CFG_VREF_UNBUFFERED       0

#define STEPUP_CFG_GAIN_1X               1
#define STEPUP_CFG_GAIN_2X               0

#define STEPUP_CFG_POWER_OUT_ON          1
#define STEPUP_CFG_POWER_OUT_OFF         0
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
/**
 * @brief Click DAC configuration structure definition.
 */
typedef struct
{
    uint8_t buf;
    uint8_t ga;
    uint8_t shdn;

} stepup_dac_cfg_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t mod;
    digital_out_t en;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    stepup_dac_cfg_t dac_config;

} stepup_t;

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

    pin_name_t mod;
    pin_name_t en;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    stepup_dac_cfg_t dac_config;

} stepup_cfg_t;

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
void stepup_cfg_setup ( stepup_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param stepup Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
STEPUP_RETVAL stepup_init ( stepup_t *ctx, stepup_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 * @param out_value     Output value (range : 0 to 4095)
 *
 * @description This function executes default configuration for Step Up click.
 */
void stepup_default_cfg ( stepup_t *ctx );


/**
 * @brief Mod Pin set function.
 *
 * @param ctx          Click object.
 * @param pin_state    MOD pin state (0 for LOW and 1 for HIGH)
 * 
 * @description This function sets the MOD pin state
 */
void stepup_mod_set ( stepup_t *ctx, uint8_t pin_state );

/**
 * @brief En Pin set function.
 *
 * @param ctx          Click object.
 * @param pin_state    EN pin state (0 for LOW and 1 for HIGH)
 * 
 * @description This function sets the EN pin state
 */
void stepup_en_set ( stepup_t *ctx, uint8_t pin_state );

/**
 * @brief DAC Setup function.
 *
 * @param ctx  Click object.
 * @param cfg  DAC configuration structure.
 *
 * @description This function performs the setup of the DAC converter of the Step up click.
 */
void stepup_dac_setup ( stepup_t *ctx, stepup_dac_cfg_t *cfg );

/**
 * @brief DAC Write function.
 *
 * @param ctx  Click object.
 * @param dac_val  DAC writing value [12-bit].
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function sets the DAC converter to the selected value and allows the output
 * voltage changing.
 */
err_t stepup_dac_write ( stepup_t *ctx, uint16_t dac_val );

/**
 * @brief Set DAC precetage up
 *
 * @param ctx  Click object.
 * @param percentage  Percentage boost ( 0 - 100% )
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function sets the DAC percentage boost.
 */
err_t stepup_set_percentage ( stepup_t *ctx, float percentage );

#ifdef __cplusplus
}
#endif
#endif  // _STEPUP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
