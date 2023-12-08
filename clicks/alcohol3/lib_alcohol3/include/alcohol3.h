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
 * \brief This file contains API for Alcohol 3 Click driver.
 *
 * \addtogroup alcohol3 Alcohol 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ALCOHOL3_H
#define ALCOHOL3_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
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
#define ALCOHOL3_MAP_MIKROBUS( cfg, mikrobus )   \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ALCOHOL3_RETVAL  uint8_t

#define ALCOHOL3_OK                      0x00
#define ALCOHOL3_INIT_ERROR              0xFF
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ALCOHOL3_DEVICE_SLAVE_ADDRESS    0x4D
/** \} */

/**
 * \defgroup measure_param Measurement parameters
 * \{
 */
#define ALCOHOL3_PARAM_CO_OUT_MIN        1 
#define ALCOHOL3_PARAM_CO_OUT_MAX        1000
#define ALCOHOL3_PARAM_SUPPLY_IN_MIN     0
#define ALCOHOL3_PARAM_SUPPLY_IN_MAX     4096
 /** \} */

/**
 * \defgroup conversion Conversion parameters
 * \{
 */

// ppm to mg/L

#define ALCOHOL3_CONV_MGL_PARAM_A        1.82
#define ALCOHOL3_CONV_MGL_PARAM_B        0.91
#define ALCOHOL3_CONV_MGL_PARAM_C        0.18
#define ALCOHOL3_CONV_MGL_PARAM_D        0.09

#define ALCOHOL3_CONV_AIR_PPM_PARAM_A    1000
#define ALCOHOL3_CONV_AIR_PPM_PARAM_B    500
#define ALCOHOL3_CONV_AIR_PPM_PARAM_C    100
#define ALCOHOL3_CONV_AIR_PPM_PARAM_D    50
 /** \} */

/**
 * \defgroup const Constants
 * \{
 */

 // CO [ ppm ]

#define ALCOHOL3_CO_PPM_0                0
#define ALCOHOL3_CO_PPM_10               10
#define ALCOHOL3_CO_PPM_50               50
#define ALCOHOL3_CO_PPM_100              100
#define ALCOHOL3_CO_PPM_500              500

// Equivalent C2H5OH

#define ALCOHOL3_EQU_TO_PPM_0            0
#define ALCOHOL3_EQU_TO_PPM_10           1
#define ALCOHOL3_EQU_TO_PPM_50           6
#define ALCOHOL3_EQU_TO_PPM_100          18
#define ALCOHOL3_EQU_TO_PPM_500          274
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

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} alcohol3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} alcohol3_cfg_t;

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
void alcohol3_cfg_setup ( alcohol3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ALCOHOL3_RETVAL alcohol3_init ( alcohol3_t *ctx, alcohol3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Alcohol3 click.
 */
void alcohol3_default_cfg ( alcohol3_t *ctx );

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
void alcohol3_generic_write ( alcohol3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void alcohol3_generic_read ( alcohol3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for read ADC data.
 *
 * @param ctx          Click object.
 *
 * @description This function reads 12bit ADC value.
 */
uint16_t alcohol3_get_adc_data ( alcohol3_t *ctx );

/**
 * @brief Function for read CO (Carbon monoxide) data in ppm.
 *
 * @param ctx          Click object.
 *
 * @description This function reads CO (Carbon monoxide) data in ppm (1 ppm - 1000 ppm).
 */
uint16_t alcohol3_get_co_in_ppm ( alcohol3_t *ctx );

/**
 * @brief Function for read CO (Carbon monoxide) data in mg/L.
 *
 * @param ctx          Click object.
 *
 * @description This function reads CO (Carbon monoxide) data in mg/L.
 */
float alcohol3_get_co_in_mgl ( alcohol3_t *ctx );

/**
 * @brief Function for read Ethanol (C2H5OH) data in ppm.
 *
 * @param ctx          Click object.
 *
 * @description This function reads Ethanol (C2H5OH) data in ppm (1 ppm - 500 ppm).
 */
uint16_t alcohol3_ethanol_in_ppm ( alcohol3_t *ctx );

/**
 * @brief Function for read percentage of alcohol in the blood (BAC).
 *
 * @param ctx          Click object.
 *
 * @description This function reads percentage of alcohol in the blood (BAC).
 */
float alcohol3_get_percentage_bac ( alcohol3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ALCOHOL3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
