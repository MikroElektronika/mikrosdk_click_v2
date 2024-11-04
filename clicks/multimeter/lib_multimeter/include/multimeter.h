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
 * \brief This file contains API for Multimeter Click driver.
 *
 * \addtogroup multimeter Multimeter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MULTIMETER_H
#define MULTIMETER_H

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

#define MULTIMETER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.a     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.b     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.c     = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MULTIMETER_RETVAL  uint8_t

#define MULTIMETER_OK           0x00
#define MULTIMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup channels Channels
 * \{
 */
#define MULTIMETER_I_CHANNEL   0x00
#define MULTIMETER_U_CHANNEL   0x01
#define MULTIMETER_R_CHANNEL   0x02
#define MULTIMETER_C_CHANNEL   0x03
/** \} */

/**
 * \defgroup channels Channels
 * \{
 */
#define MULTIMETER_MAX_VOLTAGE   4095.0
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Calibration structure.
 */
typedef struct
{
    float capacitance_cal;
    float voltage_cal;
    float current_cal;
    uint8_t scan_range;

} calibration_t;

/**
 * @brief Calibration configuration structure.
 */
typedef struct 
{
    float capa_cal_cfg;
    float volt_cal_cfg;
    float curr_cal_cfg;
    uint8_t scan_range_cfg;

} calibration_cfg_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t a;
    digital_out_t b;
    digital_out_t c;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    calibration_t calibration;
    pin_name_t chip_select;

} multimeter_t;

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

    pin_name_t a;
    pin_name_t b;
    pin_name_t c;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;
    calibration_cfg_t calibration_cfg;

} multimeter_cfg_t;

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
void multimeter_cfg_setup ( multimeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param multimeter Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MULTIMETER_RETVAL multimeter_init ( multimeter_t *ctx, multimeter_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Multimeter Click.
 */
void multimeter_default_cfg ( multimeter_t *ctx );

/**
 * @brief Read capacitance function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads and returns capacitance data.
 */
float multimeter_read_capacitance ( multimeter_t *ctx );

/**
 * @brief Read voltage function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads and returns voltage data.
 */
float multimeter_read_voltage ( multimeter_t *ctx );

/**
 * @brief Read current function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads and returns current data.
 */
float multimeter_read_current ( multimeter_t *ctx );

/**
 * @brief Read resistance function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads and returns resistance data.
 */
float multimeter_read_resistance ( multimeter_t *ctx );

/**
 * @brief Get resistance range function.
 *
 * @param ctx       Click object.
 * @param range     Scan range variable.
 *
 * @description This function calculates the resistance scan range with the help of the
 *              set_resistance_range(...) function and returns the scan range value.
 */
uint16_t multimeter_get_resistance_range ( multimeter_t *ctx, uint8_t range );

/**
 * @brief Set resistance range function.
 *
 * @param ctx       Click object.
 * @param range     Scan range variable.
 *
 * @description This function configures the scan range by activating pins that control
 *              which of the MOSFET gates will open.
 */
void multimeter_set_resistance_range ( multimeter_t *ctx, uint8_t range );

#ifdef __cplusplus
}
#endif
#endif  // _MULTIMETER_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
