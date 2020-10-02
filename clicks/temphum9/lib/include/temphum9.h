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
 * \brief This file contains API for Temp-Hum 9 Click driver.
 *
 * \addtogroup temphum9 Temp-Hum 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM9_H
#define TEMPHUM9_H

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
#define TEMPHUM9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
  
/** \} */

/**
 * \defgroup temphum_data TempHum data format
 * \{
 */
#define TEMPHUM9_RETVAL  uint8_t

#define TEMPHUM9_OK           0x00
#define TEMPHUM9_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_adresa slave adresa
 * \{
 */
#define  TEMPHUM9_DEVICE_ADDRESS        0x70
/** \} */


/**
 * \defgroup measurement_modes Measurement modes
 * \{
 */
#define  TEMPHUM9_NORMAL_MODE           0x00
#define  TEMPHUM9_LOW_POWER_MODE        0x01
/** \} */

/**
 * \defgroup data_adresa Data
 * \{
 */

#define  TEMPHUM9_SINGLE_DATA           0x03
#define  TEMPHUM9_DUAL_DATA             0x06
/** \} */

/**
 * \defgroup commands_adresa commands
 * \{
 */

#define  TEMPHUM9_SLEEP                0xB098
#define  TEMPHUM9_WAKEUP               0x3517
#define  TEMPHUM9_SOFT_RESET           0x805D
#define  TEMPHUM9_GENERAL_CALL_RESET   0x0006
#define  TEMPHUM9_READ_ID              0xEFC8
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

} temphum9_t;

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

} temphum9_cfg_t;

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
void temphum9_cfg_setup ( temphum9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM9_RETVAL temphum9_init ( temphum9_t *ctx, temphum9_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TempHum9 click.
 */
void temphum9_default_cfg ( temphum9_t *ctx );

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
void temphum9_generic_write ( temphum9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void temphum9_generic_read ( temphum9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Readinig register content
 * 
 * @param ctx                Click object.
 * @param register_address   ddress of a register to read (command)
 * @param n_data             single for one 16-bit register or dual for two 16-bit registers
 * @param register_buffer    read data is stored into this array
 *
 * @description This function reads one or two 16-bit registers
 */
void temphum9_read_register ( temphum9_t *ctx, uint16_t register_address, uint8_t n_data_, uint16_t *register_buffer );

/**
 * @brief  Issuing a command
 * 
 * @param ctx                Click object.
 * @param command            command to be sent to device
 *
 * @description This function issues (sends) command to device
 */
void temphum9_send_command ( temphum9_t *ctx, uint16_t command );

/**
 * @brief  Calculating temperature
 * 
 * @param ctx                Click object.
 * @param data            mode to be used for measurement (normal or low power mode)
 *
 * @description This function performs temperature measurement and calculates temperature
 */
float temphum9_get_temperature ( temphum9_t *ctx, uint8_t data_mode );

/**
 * @brief  Calculating relative humidity
 * 
 * @param ctx                Click object.
 * @param data            mode to be used for measurement (normal or low power mode)
 *
 * @description This function performs relative humidity measurement and calculates relative humidity
 */
float temphum9_get_relative_humidity ( temphum9_t *ctx, uint8_t data_mode );

/**
 * @brief  Calculating temperature and relative humidity
 * 
 * @param ctx                Click object.
 * @param data               mode to be used for measurement (normal or low power mode)
 * @param measurement_data   measurend data is stored into this array
 * @description This function performs temperature and relative humidity measurement and calculates temperature and relative humidity
 */
void temhum9_get_temperature_and_humidity ( temphum9_t *ctx,  uint8_t data_mode , float *measurement_data );


#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
