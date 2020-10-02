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
 * \brief This file contains API for Air quality 4 Click driver.
 *
 * \addtogroup airquality4 Air quality 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AIRQUALITY4_H
#define AIRQUALITY4_H

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
#define AIRQUALITY4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AIRQUALITY4_RETVAL  uint8_t

#define AIRQUALITY4_OK           0x00
#define AIRQUALITY4_INIT_ERROR   0xFF
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

} airquality4_t;

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

} airquality4_cfg_t;

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
void airquality4_cfg_setup ( airquality4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AIRQUALITY4_RETVAL airquality4_init ( airquality4_t *ctx, airquality4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for AirQuality4 click.
 */
void airquality4_default_cfg ( airquality4_t *ctx );

/**
 * @brief Get ID function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buffer to be written in.
 *
 * @description Function writes 48-bit ID data to buffer determined by pointer in parametar of function.
 */
void air_quality4_get_id ( airquality4_t *ctx, uint8_t *data_buf);

/**
 * @brief Initialization function.
 *
 * @param ctx          Click object.
 *
 * @description Function initializes click and starts measurement.
 */
void air_quality4_dev_init ( airquality4_t *ctx );

/**
 * @brief Quality measurment function.
 *
 * @param ctx          Click object.
 * @param read_air     Data buffer to be written in.
 *
 * @description Function writes 6 bytes CO2 data (2 bytes) and TVOC data (2 bytes) with CRC data for each other
 * to buffer determined by pointer in parametar of function.
 */
void air_quality4_measure_quality ( airquality4_t *ctx, uint8_t *read_air );

/**
 * @brief Read CO2 and TVOC function.
 *
 * @param ctx          Click object.
 * @param value     Data buffer to be written in.
 *
 * @description Function writes 2 bytes CO2 data and 2 bytes TVOC data without CRC data to buffer determined 
 * by pointer in parametar of functi
 */
void air_quality4_get_co2_and_tvoc ( airquality4_t *ctx, uint16_t *value);

/**
 * @brief Signal measurment function.
 *
 * @param ctx          Click object.
 * @param read_air     Data buffer to be written in.
 *
 * @description Function writes 6 bytes H2 data (2 bytes) and EthOH - Ethanol data (2 bytes) with CRC data for each other
 * to buffer determined by pointer in parametar of function.
 */
void air_quality4_measure_signal ( airquality4_t *ctx, uint8_t *read_air);

/**
 * @brief Read H2 and EthOH function.
 *
 * @param ctx          Click object.
 * @param value     Data buffer to be written in.
 *
 * @description Function writes 2 bytes H2 data and 2 bytes EthOH data without CRC data to buffer determined 
 * by pointer in parametar of function.
 */
void air_quality4_get_h2_and_ethon ( airquality4_t *ctx, uint16_t *value );

/**
 * @brief Get Baseline function.
 *
 * @param ctx          Click object.
 * @param read_air     Data buffer to be written in.
 *
 * @description Function writes 6 bytes baseline data for the two air quality signals and CRC data for each other
 * to buffer determined by pointer in parametar of function.
 * This data should be stored on an external memory.
 */
void air_quality4_get_baseline ( airquality4_t *ctx,  uint16_t *read_air);

/**
 * @brief Set Baseline function.
 *
 * @param ctx          Click object.
 *
 * @description Function writes 6 bytes baseline data on I2C bus for the two air quality signals and CRC data for each other.
 */
void air_quality4_set_baseline ( airquality4_t *ctx );

/**
 * @brief Software reset function
 *
 * @param ctx          Click object.
 *
 * @description Function calls general reset witch resets all states on the chip and initializes chip again.
 * Function will not reset external memory state.
 */
void air_quality4_soft_reset ( airquality4_t *ctx );

/**
 * @brief Get version function.
 *
 * @param ctx          Click object.
 * @param version    Data buffer to be written in.
 *
 * @description Function writes chip version data to buffer determined by pointer in parametar of function.
 */
void air_quality4_get_version ( airquality4_t *ctx, uint8_t *version );

/**
 * @brief Measure test function.
 *
 * @param ctx          Click object.
 * @param version    Data buffer to be written in.
 *
 * @description Function writes measurement test data to buffer determined by pointer in parametar of function.
 */
void air_quality4_get_version ( airquality4_t *ctx, uint8_t *version );

#ifdef __cplusplus
}
#endif
#endif  // _AIRQUALITY4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
