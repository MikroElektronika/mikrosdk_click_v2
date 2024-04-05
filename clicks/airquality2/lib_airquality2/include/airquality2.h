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
 * \brief This file contains API for Air quality 2 Click driver.
 *
 * \addtogroup airquality2 Air quality 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AIRQUALITY2_H
#define AIRQUALITY2_H

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
#define AIRQUALITY2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AIRQUALITY2_RETVAL  uint8_t

#define AIRQUALITY2_OK                                             0x00
#define AIRQUALITY2_INIT_ERROR                                     0xFF
/** \} */

/**
 * \defgroup i2c_register_address I2C Register Address
 * \{
 */
#define AIRQUALITY2_I2C_ADDRESS                                    0x5A
#define AIRQUALITY2_START_READING                                  0xB5
/** \} */

/**
 * \defgroup type Type
 * \{
 */
#define AIRQUALITY2_TYPE_C                                         0x00
#define AIRQUALITY2_TYPE_P                                         0x01
#define AIRQUALITY2_MEASUREMENT_INTERVAL_TYPE_C                    1000
#define AIRQUALITY2_MEASUREMENT_INTERVAL_TYPE_P                    11000
/** \} */

/**
 * \defgroup bytes_to_read Bytes To Read
 * \{
 */
#define AIRQUALITY2_READ_CO2_AND_STATUS                            3
#define AIRQUALITY2_READ_ALL                                       9
/** \} */

/**
 * \defgroup status_codes Status Codes
 * \{
 */
#define AIRQUALITY2_STATUS_OK                                      0x00
#define AIRQUALITY2_STATUS_RUNIN                                   0x10
#define AIRQUALITY2_STATUS_BUSY                                    0x01
#define AIRQUALITY2_STATUS_ERROR                                   0x80
/** \} */

/**
 * \defgroup inofficial_status Inofficial Status
 * \{
 */
#define AIRQUALITY2_STATUS_NOT_UPDATED_AT_ALL                      0xf0
#define AIRQUALITY2_STATUS_UPDATING                                0xf1
#define AIRQUALITY2_STATUS_I2C_REQ_FAILED                          0xf2
/** \} */

/**
 * \defgroup memory_addressing Memory Addressing
 * \{
 */
#define AIRQUALITY2_CO2_PREDICTION_MSB_OFFSET                      0x00
#define AIRQUALITY2_CO2_PREDICTION_LSB_OFFSET                      0x01
#define AIRQUALITY2_STATUS_OFFSET                                  0x02
#define AIRQUALITY2_RESISTANCE_NULL_BYTE                           0x03
#define AIRQUALITY2_RESISTANCE_MSB_OFFSET                          0x04
#define AIRQUALITY2_RESISTANCE_MID_OFFSET                          0x05
#define AIRQUALITY2_RESISTANCE_LSB_OFFSET                          0x06
#define AIRQUALITY2_TVOC_PREDICTION_MSB_OFFSET                     0x07
#define AIRQUALITY2_TVOC_PREDICTION_LSB_OFFSET                     0x08
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

} airquality2_t;

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

} airquality2_cfg_t;

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
void airquality2_cfg_setup ( airquality2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AIRQUALITY2_RETVAL airquality2_init ( airquality2_t *ctx, airquality2_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data.
 */
void airquality2_generic_read ( airquality2_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read all data info function.
 *
 * @param ctx              Click object.
 * @param value_co2        Pointer to 16-bit Prediction Value CO2.
 * @param value_tvoc       Pointer to 16-bit Prediction Value TVOC.
 * @param resistance       Pointer to 16-bit ( signed ) Resistance Value.
 *
 * @description Reads all data information about the indoor air quality.
 */
uint8_t airquality2_get_all_data ( airquality2_t *ctx, uint16_t *value_co2, uint16_t *value_tvoc, int32_t *resistance );

#ifdef __cplusplus
}
#endif
#endif  // _AIRQUALITY2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
