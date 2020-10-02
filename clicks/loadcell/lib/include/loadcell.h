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
 * \brief This file contains API for Load cell Click driver.
 *
 * \addtogroup loadcell Load cell Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LOADCELL_H
#define LOADCELL_H

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
#define LOADCELL_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.rte= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.clk= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LOADCELL_RETVAL  uint8_t

#define LOADCELL_OK           0x00
#define LOADCELL_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup ch_gate Channel gate
 * \{
 */
#define LOADCELL_CHANN_A_GATE_128_NEXT                   0
#define LOADCELL_CHANN_B_GATE_32_NEXT                    1
#define LOADCELL_CHANN_A_GATE_64_NEXT                    2
/** \} */

/**
 * \defgroup int_osc Internal oscilator
 * \{
 */
#define LOADCELL_10HZ_INTERNAL_OSC                       0
#define LOADCELL_80HZ_INTERNAL_OSC                       1
/** \} */

/**
 * \defgroup pwr_st Power state
 * \{
 */
#define LOADCELL_POWER_UP                                0
#define LOADCELL_POWER_DOWN                              1
/** \} */

/**
 * \defgroup result Result state
 * \{
 */
#define LOADCELL_GET_RESULT_ERROR                        0
#define LOADCELL_GET_RESULT_OK                           1
/** \} */

/**
 * \defgroup weight_val Weight value
 * \{
 */
#define LOADCELL_WEIGHT_100G                            100
#define LOADCELL_WEIGHT_500G                            500
#define LOADCELL_WEIGHT_1000G                           1000
#define LOADCELL_WEIGHT_5000G                           5000
#define LOADCELL_WEIGHT_10000G                          10000
/** \} */

/**
 * \defgroup coeff Calculation coefficient
 * \{
 */
#define LOADCELL_DEFAULT_WEIGHT_SCALE_COEFFICIENT        0.088495575221
/** \} */

/**
 * \defgroup data_stat Data status
 * \{
 */
#define LOADCELL_DATA_NO_DATA                            0
#define LOADCELL_DATA_OK                                 1
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

    digital_out_t rte;
    digital_out_t clk;

    // Input pins 

    digital_in_t int_pin;

} loadcell_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t rte;
    pin_name_t clk;
    pin_name_t int_pin;

} loadcell_cfg_t;

/**
 * @brief Load cell data structure definition.
 */
typedef struct
{
    float tare;
    uint8_t tare_ok;
    float weight_coeff_100g;
    uint8_t weight_data_100g_ok;
    float weight_coeff_500g;
    uint8_t weight_data_500g_ok;
    float weight_coeff_1000g;
    uint8_t weight_data_1000g_ok;
    float weight_coeff_5000g;
    uint8_t weight_data_5000g_ok;
    float weight_coeff_10000g;
    uint8_t weight_data_10000g_ok;
}
loadcell_data_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group
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
void loadcell_cfg_setup ( loadcell_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LOADCELL_RETVAL loadcell_init ( loadcell_t *ctx, loadcell_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Load cell click.
 */
void loadcell_default_cfg ( loadcell_t *ctx );

/**
 * @brief Check status of pin DO (do_pin).
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description When the data output pin (DO) goes to a LOW logic level, the host microcontroller (MCU) can start generating clock pulses on the SCK pin. 
 */
uint8_t loadcell_check_out ( loadcell_t *ctx );

/**
 * @brief Read results of function.
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function read result for this click.
 */
uint8_t loadcell_read_results ( loadcell_t *ctx, uint8_t input_sel, uint32_t *data_out );

/**
 * @brief Set rate function.
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description A HIGH logic level on this pin will set the output data rate at 80 samples per second (SPS), while the LOW logic level will set the data rate to 10 SPS. .
 */
void loadcell_set_rate ( loadcell_t *ctx, uint8_t rate_sel );

/**
 * @brief Reset clock function.
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function reset serial data clock.
 */
void loadcell_reset ( loadcell_t *ctx );

/**
 * @brief Set clock mode function.
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function set clock mode.
 */
void loadcell_set_mode ( loadcell_t *ctx, uint8_t pwr_mode );

/**
 * @brief Function of messure and read results.
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function read results of messure.
 */
void loadcell_tare ( loadcell_t *ctx, uint8_t input_sel, loadcell_data_t *cell_data );

/**
 * @brief Calibration function.
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function do calibration.
 */
uint8_t loadcell_calibration ( loadcell_t *ctx, uint8_t input_sel, uint16_t cal_val, loadcell_data_t *cell_data );

/**
 * @brief Get weight function.
 * @param loadcell Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function messure weight.
 */
float loadcell_get_weight ( loadcell_t *ctx, uint8_t input_sel, loadcell_data_t *cell_data );


#ifdef __cplusplus
}
#endif
#endif  // _LOADCELL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
