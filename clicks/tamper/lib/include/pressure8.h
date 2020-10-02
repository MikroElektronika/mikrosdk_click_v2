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
 * \brief This file contains API for Pressure 8 Click driver.
 *
 * \addtogroup pressure8 Pressure 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE8_H
#define PRESSURE8_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define PRESSURE8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.eoc = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE8_RETVAL  uint8_t

#define PRESSURE8_OK           0x00
#define PRESSURE8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup pressure_data Pressure data format
 * \{
 */
#define PRESSURE8_DATA_IN_mBar  1
#define PRESSURE8_DATA_IN_hPa   2
#define PRESSURE8_DATA_IN_kPa   3
#define PRESSURE8_DATA_IN_Torr  4
#define PRESSURE8_DATA_IN_mmHg  5
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

    digital_out_t rst;

    // Input pins 

    digital_in_t eoc;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    hal_i2c_address_t slave_address;
    uint8_t device_status;

} pressure8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t eoc;

    // static variable 

    hal_i2c_speed_t i2c_speed;
    hal_i2c_address_t i2c_address;

} pressure8_cfg_t;

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
void pressure8_cfg_setup ( pressure8_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param pressure8 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PRESSURE8_RETVAL pressure8_init ( pressure8_t *ctx, pressure8_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void pressure8_generic_read ( pressure8_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for get Pressure data
 *
 * @param ctx Click object.
 * @param press_foramt  Pressure data in ... (mBar, hPa, kPa, mmHg and Torr)
 * 
 * @return Pressure data
 *
 */
float pressure8_get_pressure ( pressure8_t *ctx, uint8_t press_foramt );

/**
 * @brief Functions for hardware device reset
 *
 * @param ctx Click object.
 */
void pressure8_device_reset ( pressure8_t *ctx );

/**
 * @brief Functions for get interrupt pin state
 *
 * @param ctx Click object.
 * 
 * @return Interrupt (EOC) pin state
 */
uint8_t pressure8_get_interrupt_state ( pressure8_t *ctx );

/**
 * @brief Functions for get device status
 *
 * @param ctx Click object.
 * 
 * @return Device satus
 */
uint8_t pressure8_get_device_status ( pressure8_t *ctx );

/**
 * @brief Functions for set PSI range
 *
 * @param psi_min   PSI min range
 * @param psi_max   PSI max range
 * 
 * @note PSI range options:
 * <pre>
 *    - Absolute (0psi to 15psi, 0psi to 25psi(def) and 0psi to 30psi)
 *    - Gage ( 0psi to 1psi, 0psi to 5pis, 0psi to 15psi and 0psi to 30psi)
 * </pre>
 */
void pressure8_set_psi_range ( float psi_min, float psi_max );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
