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
 * \brief This file contains API for Temp Hum 6 Click driver.
 *
 * \addtogroup temphum6 Temp Hum 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM6_H
#define TEMPHUM6_H

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
#define TEMPHUM6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl= MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda= MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM6_RETVAL  uint8_t

#define TEMPHUM6_OK           0x00
#define TEMPHUM6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup chip_constants Chip Constants
 * \{
 */
#define TEMPHUM6_PART_ID                   0x0210
#define TEMPHUM6_DEVICE_SLAVE_ADDRESS      0x43
/** \} */ 

/**
 * \defgroup registers Registers
 * \{
 */           
#define TEMPHUM6_REG_PART_ID               0x00
#define TEMPHUM6_REG_UNIQUE_IDENTIFIER     0x04
#define TEMPHUM6_REG_SYSTEM_CONTROL        0x10
#define TEMPHUM6_REG_SYSTEM_STATUS         0x11
#define TEMPHUM6_REG_SENS_RUN              0x21
#define TEMPHUM6_REG_SENS_START            0x22
#define TEMPHUM6_REG_SENS_STOP             0x23
#define TEMPHUM6_REG_SENS_STATUS           0x24
#define TEMPHUM6_REG_TEMPERATURE           0x30
#define TEMPHUM6_REG_RELATIVE_HUMIDITY     0x33
/** \} */
  
/**
 * \defgroup status Status
 * \{
 */        
#define TEMPHUM6_STATUS_I2C_ERROR      4
#define TEMPHUM6_STATUS_CRC_ERROR      3
#define TEMPHUM6_STATUS_INVALID        2
#define TEMPHUM6_STATUS_OK             1
/** \} */
  
/**
 * \defgroup temperature_data Temperature Data
 * \{
 */            
#define TEMPHUM6_TEMP_IN_FAHRENHEIT    2
#define TEMPHUM6_TEMP_IN_KELVIN        1
#define TEMPHUM6_TEMP_IN_CELSIUS       0
/** \} */

/**
 * \defgroup controls_the_system Controls the System
 * \{
 */            
#define TEMPHUM6_LOW_POWER_DISABLE     0x00
#define TEMPHUM6_LOW_POWER_ENABLE      0x01
/** \} */

/**
 * \defgroup system_status System Status
 * \{
 */          
#define TEMPHUM6_SYSTEM_IS_IN_STANDBY_OR_BOOTING_STATE     0
#define TEMPHUM6_SYSTEM_IS_IN_ACTIVE_STATE                 1
/** \} */

/**
 * \defgroup configure_run_mode_registers Configure Run Modes Registers
 * \{
 */        
#define TEMPHUM6_HUM_RUN_SINGLE_SHOT_MODE     0x00
#define TEMPHUM6_TEMP_RUN_SINGLE_SHOT_MODE    0x00
#define TEMPHUM6_HUM_RUN_CONTINUOUS_MODE      0x02
#define TEMPHUM6_TEMP_RUN_CONTINUOUS_MODE     0x01
/** \} */

/**
 * \defgroup measurement_start Measurement Start
 * \{
 */        
#define TEMPHUM6_HUM_START_MEASUREMENT        0x02
#define TEMPHUM6_TEMP_START_MEASUREMENT       0x01
#define TEMPHUM6_DISABLE_MEASUREMENT          0x00
/** \} */

/**
 * \defgroup stops_continuous_measurement Stops Continuous Measurement
 * \{
 */      
#define TEMPHUM6_HUM_STOP_CONTINUOUS_MEASUREMENT     0x02
#define TEMPHUM6_TEMP_STOP_CONTINUOUS_MEASUREMENT    0x01
#define TEMPHUM6_DISABLE_CONTINUOUS_MEASUREMENT      0x00
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

} temphum6_t;

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

} temphum6_cfg_t;

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
void temphum6_cfg_setup ( temphum6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM6_RETVAL temphum6_init ( temphum6_t *ctx, temphum6_cfg_t *cfg );

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
void temphum6_generic_write ( temphum6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void temphum6_generic_read ( temphum6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for reset device
 * 
 * @param ctx          Click object.
 * 
 * @description This functions resets the device.
 */
void temphum6_reset ( temphum6_t *ctx );

/**
 * @brief Functions for get device PART ID
 *
 * @param ctx          Click object.
 * 
 * @return 16bit device part id
 * 
 * @description This function returns the device part id.
 */
uint16_t temphum6_get_part_id ( temphum6_t *ctx );

/**
 * @brief Functions for RUN measurement
 *
 * @param ctx          Click object.
 *
 * @description The function sets the registers _TEMPHUM6_REG_SENS_RUN and _TEMPHUM6_REG_SENS_START.
 * <pre>
 *    RUN   : ( _TEMPHUM6_HUM_RUN_SINGLE_SHOT_MODE | _TEMPHUM6_TEMP_RUN_SINGLE_SHOT_MODE )
 *    START : ( _TEMPHUM6_HUM_START_MEASUREMENT | _TEMPHUM6_TEMP_START_MEASUREMENT )
 * </pre>
 */
void temphum6_run ( temphum6_t *ctx );

/**
 * @brief Functions for read Temperature data
 *
 * @param ctx          Click object.
 * @param temp_in       Temperature in ... (FAHRENHEIT, KELVIN, CELSIUS)
 * 
 * @return Temperature data
 * 
 * @description This function returns read Temperature data.
 */
float temphum6_read_temperature ( temphum6_t *ctx, uint8_t temp_in );

/**
 * @brief Functions for read Relative Huminidy data
 *
 * @param ctx          Click object.
 * 
 * @return Relative Huminidy data in [%RH]
 * 
 * @description This function returns read relative Humidity data.
 */
float temphum6_read_relative_huminidy( temphum6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
