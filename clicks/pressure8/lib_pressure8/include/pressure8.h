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
  cfg.eoc = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE8_OK                0
#define PRESSURE8_ERROR            -1
/** \} */

/**
 * \defgroup pressure_data Pressure data format
 * \{
 */
#define PRESSURE8_DATA_IN_MBAR      1
#define PRESSURE8_DATA_IN_HPA       2
#define PRESSURE8_DATA_IN_KPA       3
#define PRESSURE8_DATA_IN_TORR      4
#define PRESSURE8_DATA_IN_MMHG      5
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
    uint8_t slave_address;
    uint8_t device_status;
    float press_max;
    float press_min;

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
    uint32_t i2c_speed;
    uint8_t i2c_address;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void pressure8_cfg_setup ( pressure8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t pressure8_init ( pressure8_t *ctx, pressure8_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @details This function reads data from the desired register.
 */
void pressure8_generic_read ( pressure8_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for get Pressure data
 *
 * @param ctx Click object.
 * @param press_format  Pressure data in ... (mBar, hPa, kPa, mmHg and Torr)
 * 
 * @return Pressure data
 *
 * @details This function get pressure data.
 */
float pressure8_get_pressure ( pressure8_t *ctx, uint8_t press_format );

/**
 * @brief Functions for hardware device reset
 *
 * @param ctx Click object.
 *
 * @details This function resets hardware device.
 */
void pressure8_device_reset ( pressure8_t *ctx );

/**
 * @brief Functions for get interrupt pin state
 *
 * @param ctx Click object.
 * 
 * @return Interrupt (EOC) pin state
 *
 * @details This function gets interrupt state. 
 */
uint8_t pressure8_get_eoc_state ( pressure8_t *ctx );

/**
 * @brief Functions for get device status
 *
 * @param ctx Click object.
 * 
 * @return Device status
 *
 * @details This function gets device status. 
 */
uint8_t pressure8_get_device_status ( pressure8_t *ctx );

/**
 * @brief Functions for set PSI range
 *
 * @param ctx Click object.
 * @param psi_min   PSI min range
 * @param psi_max   PSI max range
 * 
 * @note PSI range options:
 * <pre>
 *    - Absolute (0psi to 15psi, 0psi to 25psi(def) and 0psi to 30psi)
 *    - Gage ( 0psi to 1psi, 0psi to 5pis, 0psi to 15psi and 0psi to 30psi)
 * </pre>
 *
 * @details This function set PSI range.
 */
void pressure8_set_psi_range ( pressure8_t *ctx, float psi_min, float psi_max );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE8_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
