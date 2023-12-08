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
 * \brief This file contains API for RMS to DC Click driver.
 *
 * \addtogroup rmstodc RMS to DC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RMSTODC_H
#define RMSTODC_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define RMSTODC_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RMSTODC_RETVAL  uint8_t

#define RMSTODC_OK           0x00
#define RMSTODC_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_addr  Device Addr
 * \{
 */
#define ADC_RESOLUTION                     4096
#define RMS2DC_DEVICE_ADDR                 0x4D
/** \} */

/**
 * \defgroup device   Device
 * \{
 */
#define RMS2DC_DEVICE_EN                   0x00
#define RMS2DC_DEVICE_DIS                  0x01
/** \} */

/**
 * \defgroup voltage  Voltage
 * \{
 */
#define RMS2DC_VCC_3V3           3300
#define RMS2DC_VCC_5V            5000
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

    digital_out_t en;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} rmstodc_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t en;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} rmstodc_cfg_t;

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
void rmstodc_cfg_setup ( rmstodc_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RMSTODC_RETVAL rmstodc_init ( rmstodc_t *ctx, rmstodc_cfg_t *cfg );

/**
 * @brief ADC Read function.
 *
 * @returns Result of AD conversion
 *
 * Function returns a 12bit result of AD conversion.
 */
uint16_t rms2dc_read_adc ( rmstodc_t *ctx );

/**
 * @brief Get Output Voltage function.
 *
 * @param vcc_sel  VCC value selection [mV]
 *
 * @returns Output voltage value
 *
 * Function returns the output voltage value calculated to mV, depending on the power voltage selection.
 */
uint16_t rms2dc_vout_adc ( rmstodc_t *ctx, uint16_t vcc_sel );

/**
 * @brief Enable function
 *
 * @param state  0 - ON, 1 - OFF
 *
 * Function turns ON/OFF the device.
 */
void rms2dc_enable ( rmstodc_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _RMSTODC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
