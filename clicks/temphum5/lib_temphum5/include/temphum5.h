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
 * \brief This file contains API for Temp&Hum 5 Click driver.
 *
 * \addtogroup temphum5 Temp&Hum 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM5_H
#define TEMPHUM5_H

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
#define TEMPHUM5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.all = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.alh = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM5_RETVAL  uint8_t

#define TEMPHUM5_OK           0x00
#define TEMPHUM5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define TEMPHUM5_DEVICE_SLAVE_ADDRESS     0x27
/** \} */

/**
 * \defgroup temperature_data_in Temperature data in
 * \{
 */
#define TEMPHUM5_TEMP_DATA_IN_CELSIUS     0x01
#define TEMPHUM5_TEMP_DATA_IN_KELVIN      0x02
#define TEMPHUM5_TEMP_DATA_IN_FAHRENHEIT  0x03
/** \} */


/**
 * \defgroup status Status 
 * \{
 */
#define TEMPHUM5_STATUS_NORMAL_OPERATION  0x00
#define TEMPHUM5_STATUS_STALE_DATA        0x01
#define TEMPHUM5_STATUS_COMMAND_MODE      0x02
/** \} */

/**
 * \defgroup alarm Alarm
 * \{
 */
#define TEMPHUM5_ALARM_OUTPUT_HIGH  0x01
#define TEMPHUM5_ALARM_OUTPUT_LOW   0x02
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

    digital_in_t all;
    digital_in_t alh;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint16_t temperature;
    uint16_t humidity;

} temphum5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t all;
    pin_name_t alh;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

    uint16_t dev_temperature;
    uint16_t dev_humidity;

} temphum5_cfg_t;

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
void temphum5_cfg_setup ( temphum5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param temphum5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM5_RETVAL temphum5_init ( temphum5_t *ctx, temphum5_cfg_t *cfg );

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
void temphum5_generic_write ( temphum5_t *ctx, uint8_t cmd );

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
void temphum5_generic_read ( temphum5_t *ctx, uint8_t *data_out );

/**
 * @brief Functions for start measurement
 *
 * @param ctx          Click object.
 *
 * @return Modul status 
 * @note
 *<pre>
 * Status:
 *   - Normal Operation, Valid Data that has not been fetched since the last measurement cycle.
 *   - Stale Data: Data that has already been fetched since the last measurement cycle, or
 *                 data fetched before the first measurement has been completed.
 *   - Device in Command Mode - Command Mode is used for programming the sensor.
 *</pre>
 */
uint8_t temphum5_start_measurement ( temphum5_t *ctx );

/**
 * @brief Functions for read Temperature data
 * 
 * @param ctx          Click object. 
 * @param temp_in        Temperature in ... (FAHRENHEIT, KELVIN, CELSIUS)
 *
 * @return Temperature data
 *
 */
float temphum5_get_temperature ( temphum5_t *ctx, uint8_t temp_in );

/**
 * @brief Functions for read Relative Huminidy data
 * 
 * @param ctx          Click object.
 * 
 * @return Relative Huminidy data in [%RH]
 *
 */
float temphum5_get_humidity ( temphum5_t *ctx );

/**
 * @brief Functions for get output Alarm 
 * 
 * @param ctx          Click object.
 * @param alarm        Output Alarm (HIGH or LOW)
 *
 * @description The alarm is set by default and it is not possible to change it
 */
uint8_t temphum5_get_alarm ( temphum5_t *ctx, uint8_t alarm );


#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
