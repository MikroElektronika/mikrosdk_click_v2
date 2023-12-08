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
 * \brief This file contains API for Air Quality 7 Click driver.
 *
 * \addtogroup airquality7 Air Quality 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AIRQUALITY7_H
#define AIRQUALITY7_H

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
#define AIRQUALITY7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AIRQUALITY7_RETVAL  uint8_t
#define airquality7_err_t   uint8_t

#define AIRQUALITY7_OK           0x00
#define AIRQUALITY7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup command  Command
 * \{
 */
#define AIRQUALITY7_CMD_SET_PPMCO2    0x08
#define AIRQUALITY7_CMD_GET_STATUS    0x0C
#define AIRQUALITY7_CMD_GET_REVISION  0x0D
#define AIRQUALITY7_CMD_GET_R0        0x10
/** \} */

/**
 * \defgroup slave_addr  Slave addr
 * \{
 */
#define AIRQUALITY7_DEV_ADDR  0x70
/** \} */

/**
 * \defgroup error  Error
 * \{
 */
#define AIRQUALITY7_ERR_OK    0x00
#define AIRQUALITY7_ERR_CRC   0x01
/** \} */

/**
 * \defgroup dummy  Dummy 
 * \{
 */
#define AIRQUALITY7_NULL      0x00
#define AIRQUALITY7_DUMMY     0x00
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} airquality7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} airquality7_cfg_t;

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
void airquality7_cfg_setup ( airquality7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param airquality7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AIRQUALITY7_RETVAL airquality7_init ( airquality7_t *ctx, airquality7_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buf to be written.
 *
 * @description This function writes data to the desired register.
 */
void airquality7_generic_write ( airquality7_t *ctx, uint8_t *data_buf );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param data_buf     Output data buf
 *
 * @description This function reads data from the desired register.
 */
void airquality7_generic_read ( airquality7_t *ctx, uint8_t *data_buf );

/**
 * @brief Set CO2 [ppm] function.
 *
 * @param ctx           Click object.
 * @param ppmco2_value  4 bytes of CO2 data to be written in ppm.
 *
 * @description This function is used to send the ppmCO2 value given by an 
 * external analyzer to the Air quality 7 click in order to recalibrate its 
 * outputs.
 */
void airquality7_set_ppmco2( airquality7_t *ctx, uint8_t *ppmco2_value );

/**
 * @brief Get Status function.
 *
 * @param ctx          Click object.
 * @param tvoc_ppb     tVOC output data in ppb.
 * @param co2_ppm      CO2 output data in ppm.
 * @param res_val_ohm  Resistor value output data in Ohms.
 * @param err_byte     Error status output data.
 *
 * @returns 0 - Ok,
 *          1 - CRC error.
 *
 * @description This function is used to read the Air quality 7 click status 
 * coded on tVOC data byte [0 - 1000 ppb], CO2 data byte [400 - 2000 ppm], 
 * resistor value data 3 bytes [Ohm], error status byte and CRC byte.
 */
airquality7_err_t airquality7_get_status( airquality7_t *ctx, uint16_t *tvoc_ppb, 
                                                              uint16_t *co2_ppm, 
                                                              uint32_t *res_val_ohm, 
                                                              uint8_t *err_byte );

/**
 * @brief Get Revision function.
 *
 * @param ctx          Click object.
 * @param year         Revision year output data.
 * @param month        Revision month output data.
 * @param day          Revision day output data.
 * @param ascii_code   Revision ASCII code output data.
 *
 * @returns 0 - Ok,
 *          1 - CRC error.
 *
 * @description This function will return the revision code of the module coded
 * on year data byte, month data byte, day data byte, ASCII code data byte
 * for a charter and CRC byte.
 */
airquality7_err_t airquality7_get_revision( airquality7_t *ctx, uint8_t *year, 
                                                                uint8_t *month, 
                                                                uint8_t *day, 
                                                                uint8_t *ascii_code );

/**
 * @brief Get R0 Calibration function.
 *
 * @param ctx          Click object.
 * @param r0_kohm      R0 calibration output data in kOhms.
 *
 * @returns 0 - Ok,
 *          1 - CRC error.
 *
 * @description This function is used to read the R0 (calibration) value in
 * [kOhms] coded on 2 data bytes and CRC byte.
 */
airquality7_err_t airquality7_get_r0_calib( airquality7_t *ctx, uint16_t *r0_kohm );

#ifdef __cplusplus
}
#endif
#endif  // _AIRQUALITY7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
