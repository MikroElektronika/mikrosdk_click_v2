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
 * \brief This file contains API for PIR Click driver.
 *
 * \addtogroup pir PIR Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PIR_H
#define PIR_H

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
#define PIR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PIR_RETVAL  uint8_t

#define PIR_OK           0x00
#define PIR_INIT_ERROR   0xFF
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

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} pir_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t an;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} pir_cfg_t;

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
void pir_cfg_setup ( pir_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PIR_RETVAL pir_init ( pir_t *ctx, pir_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void pir_generic_write ( pir_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void pir_generic_read ( pir_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Reading 12bit ADC value.
 *
 * @param ctx   Click object.
 *
 * This function reads single ADC conversion data
 */
uint16_t pir_get_adc ( pir_t *ctx );

/**
 * @brief Reading register.
 *
 * @param ctx   Click object.
 *
 * This function reads register
 */
uint16_t pir_reg_read ( pir_t *ctx );

/**
 * @brief Reading ADC data in mili Volts
 *
 * @param ctx   Click object.
 * @param ref_voltage reference voltage in miliVolts (3300 or 5000 miliVolts).
 *
 * This function reads 12bit ADC data and convets it to miliVolts
 */
float pir_get_mili_volt ( pir_t *ctx, uint16_t ref_voltage );

/**
 * @brief Scaling ADC results
 *
 * @param ctx       Click object.
 * @param in_val    ADC conversion raw data   
 * @param out_min   lower limit of output data
 * @param out_max   upper limit of output data
 *
 * This function scales ADC conversion data (inVal) to desired range (from outMin to outMax) and returns scaled data (outVal)
 */
float pir_scale_results ( pir_t *ctx, uint16_t in_val, uint16_t out_min, uint16_t out_max );

#ifdef __cplusplus
}
#endif
#endif  // _PIR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
