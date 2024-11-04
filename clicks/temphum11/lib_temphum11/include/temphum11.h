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
 * \brief This file contains API for Temp Hum 11 Click driver.
 *
 * \addtogroup temphum11 Temp Hum 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM11_H
#define TEMPHUM11_H

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
#define TEMPHUM11_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM11_RETVAL  uint8_t

#define TEMPHUM11_OK           0x00
#define TEMPHUM11_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define TEMPHUM11_REG_TEMPERATURE               0x00
#define TEMPHUM11_REG_HUMIDITY                  0x01
#define TEMPHUM11_REG_CONFIGURATION             0x02
#define TEMPHUM11_REG_SERIAL_ID_0               0xFB
#define TEMPHUM11_REG_SERIAL_ID_1               0xFC
#define TEMPHUM11_REG_SERIAL_ID_2               0xFD
#define TEMPHUM11_REG_MANUFACTURER_ID           0xFE
#define TEMPHUM11_REG_DEVICE_ID                 0xFF
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define TEMPHUM11_NORMAL_OPERATION              0x0000
#define TEMPHUM11_SOFTWARE_RESET                0x8000
#define TEMPHUM11_HEATER_DISABLED               0x0000
#define TEMPHUM11_HEATER_ENABLED                0x2000
#define TEMPHUM11_TEMP_HUM_ACQUIRED             0x0000
#define TEMPHUM11_TEMP_FIRST                    0x1000
#define TEMPHUM11_BAT_VOLT_BIGGER_THAN_2p8      0x0000
#define TEMPHUM11_BAT_VOLT_SMALLER_THAN_2p8     0x0800
#define TEMPHUM11_TEMP_RESOLUTION_14bit         0x0000
#define TEMPHUM11_TEMP_RESOLUTION_11bit         0x0400
#define TEMPHUM11_HUM_RESOLUTION_14bit          0x0000
#define TEMPHUM11_HUM_RESOLUTION_11bit          0x0100
#define TEMPHUM11_HUM_RESOLUTION_8bit           0x0200
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define TEMPHUM11_DEVICE_SLAVE_ADDR             0x40
/** \} */

/**
 * \defgroup  return_value  Return Value
 * \{
 */
#define TEMPHUM11_DEVICE_ID                     0x1050
#define TEMPHUM11_MANUFACTURER_ID               0x5449
/** \} */

/**
 * \defgroup temperature_data Temperature data in ..
 * \{
 */
#define TEMPHUM11_TEMP_IN_CELSIUS               0x00
#define TEMPHUM11_TEMP_IN_KELVIN                0x01
#define TEMPHUM11_TEMP_IN_FAHRENHEIT            0x02
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

} temphum11_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // Static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} temphum11_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void temphum11_cfg_setup ( temphum11_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param temphum11 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
TEMPHUM11_RETVAL temphum11_init ( temphum11_t *ctx, temphum11_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TempHum11 Click.
 */
void temphum11_default_cfg ( temphum11_t *ctx );

/**
 * @brief Function for writing configuration device for measurement.
 *
 * @param ctx          Click object.
 * @param config       Data to be written.
 *
 * @description This function writes configuration device for measurement.
 */
void temphum11_write_config ( temphum11_t *ctx, uint16_t config );

/**
 * @brief Functions for reading data from registers
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * 
 * @returns 16-bit data that is reads from the register.
 *
 * @description This function reads data from the desired register.
 */
uint16_t temphum11_read_data ( temphum11_t *ctx, uint8_t reg );

/**
 * @brief Functions for reading Temperature data
 *
 * @param ctx          Click object.
 * @param temp_in      Macro for determinating temperature unit ... (FAHRENHEIT, KELVIN, CELSIUS)
 * 
 * @returns temperature data
 * 
 * @description This function reads temperature data in desired unit.
 */
float temphum11_get_temperature ( temphum11_t *ctx, uint8_t temp_in );

/**
 * @brief Functions for reading Relative Huminidy data
 *
 * @param ctx          Click object.
 * 
 * @returns Relative Huminidy data in [%RH]
 * 
 * description This function reads relative huminidy data
 */
float temphum11_get_humidity ( temphum11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM11_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
