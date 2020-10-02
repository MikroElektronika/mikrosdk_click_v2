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
 * \brief This file contains API for Thermostat 3 Click driver.
 *
 * \addtogroup thermostat3 Thermostat 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

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

#define THERMOSTAT3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rly = MIKROBUS( mikrobus, MIKROBUS_PWM)
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMOSTAT_RETVAL  uint8_t

#define THERMOSTAT_OK           0x00
#define THERMOSTAT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup relay_pos Relay position
 * \{
 */
#define THERMOSTAT3_RELAY_ON     0x01
#define THERMOSTAT3_RELAY_OFF    0x00
/** \} */

/**
 * \defgroup temp_unit Temperature Unit
 * \{
 */
#define THERMOSTAT3_TEMP_IN_CELSIUS       0x00
#define THERMOSTAT3_TEMP_IN_FAHRENHEIT    0x02
#define THERMOSTAT3_TEMP_IN_KELVIN        0x01
/** \} */

/**
 * \defgroup fault Fault
 * \{
 */
#define THERMOSTAT3_FAULT_ACTIVE_FLAG    0x08
#define THERMOSTAT3_FAULT_SCV_FLAG       0x04
#define THERMOSTAT3_FAULT_SCG_FLAG       0x02
#define THERMOSTAT3_FAULT_OC_FLAG        0x01
#define THERMOSTAT3_FAULT_ALL_FLAG       0x00
/** \} */

/**
 * \defgroup null Empty Buffer
 * \{
 */
#define NULL                             0x00
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

    digital_out_t rly;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    uint8_t relay_flag;
    uint8_t fault_flag;
    uint8_t f_error;
    uint8_t fault_status;

} thermostat3_t;

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

    pin_name_t rly;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    float internal_temp_cfg;
    float thermocouple_temp_cfg;
    uint8_t fault_value_cfg;

} thermostat3_cfg_t;

typedef struct
{
    float internal_temp;
    float thermocouple_temp;
    uint8_t fault_value;

} temp_vals_t;


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
void thermostat3_cfg_setup ( thermostat3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thermostat3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMOSTAT_RETVAL thermostat3_init ( thermostat3_t *ctx, thermostat3_cfg_t *cfg );

void thermostat3_generic_read ( thermostat3_t *ctx, uint8_t *read_buff );

/**
 * @brief Thermostat Process Read data
 *
 * @param ctx        Click object.
 * @param tmp        Temperature click object
 * 
 * @description This function must be constantly called in the task. 
 * The function continuously reads data from the SPI lines and parses the read data.
 */
void thermostat3_process ( thermostat3_t *ctx, temp_vals_t *tmp );

/**
 * @brief Junction (Internal) Temperature
 *
 * @param temp_in    Temperature in (CELSIUS, KELVIN or FAHRENHEIT)
 * @param ctx        Click object.
 * 
 * @return Temperature data
 *
 * @description This function returns 12-Bit Internal Temperature Data
 */
float thermostat3_get_internal_temperature ( temp_vals_t *tmp, uint8_t temp_in );

/**
 * @brief Thermocouple Temperature (K probe)
 *
 * @param temp_in      Temperature in (CELSIUS, KELVIN or FAHRENHEIT)
 * @param ctx          Click object.
 * 
 * @return Fault Error status (1 - ERROR, 0 - OK) or 4-bit data (all Error status)
 * 
 * @description This function returns 14-Bit Thermocouple Temperature Data
 */
float thermostat3_get_thermocouple_temperature ( temp_vals_t *tmp, uint8_t temp_in );

/**
 * @brief Fault data value
 *
 * @param err   Fault error (ACTIVE FAULT, SCV, SCG, OC or all-Error)
 * @param ctx          Click object.
 * 
 * @return Fault Error status (1 - ERROR, 0 - OK) or 4-bit data (all Error status)
 * 
 * @description This function returns Fault data Value.
 */
uint8_t thermostat3_get_fault_data ( temp_vals_t *tmp, uint8_t err );

/**
 * @brief Relay Control
 *
 * @param relay_pos    Relay (ON or OFF state)
 * @param ctx          Click object.
 * 
 * @description This function enables control of the relay.
 */
void thermostat3_relay_control ( thermostat3_t *ctx, uint8_t relay_pos );

#ifdef __cplusplus
}
#endif
#endif  // _THERMOSTAT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
