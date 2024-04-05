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
 * \brief This file contains API for Thermo 8 Click driver.
 *
 * \addtogroup thermo8 Thermo 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO8_H
#define THERMO8_H

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
#define THERMO8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.ale = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO8_RETVAL  uint8_t

#define THERMO8_OK           0x00
#define THERMO8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup address Address
 * \{
 */
#define THERMO8_ADDR0                            0x18
#define THERMO8_ADDR1                           (0x18 | 0x01)
#define THERMO8_ADDR2                           (0x18 | 0x02)
#define THERMO8_ADDR3                           (0x18 | 0x03)
#define THERMO8_ADDR4                           (0x18 | 0x04)
#define THERMO8_ADDR5                           (0x18 | 0x05)
#define THERMO8_ADDR6                           (0x18 | 0x06)
#define THERMO8_ADDR7                           (0x18 | 0x07)
/** \} */

/**
 * \defgroup config Config
 * \{
 */
#define THERMO8_CONFIG                           0x01
#define THERMO8_TUPPER                           0x02
#define THERMO8_TLOWER                           0x03
#define THERMO8_TCRIT                            0x04
#define THERMO8_TUPPER_REACHED                   0x03
#define THERMO8_TLOWER_REACHED                   0x0C
#define THERMO8_TCRIT_REACHED                    0x30
#define THERMO8_TCRIT_ONLY_ALERT                 1
#define THERMO8_ALERT_ON_ALL                     0
#define THERMO8_THYS_0C                          0x00
#define THERMO8_THYS_1C5                         0x01
#define THERMO8_THYS_3C                          0x02
#define THERMO8_THYS_6C                          0x03
/** \} */

/**
 * \defgroup id Id
 * \{
 */
#define THERMO8_TA                               0x05
#define THERMO8_MANID                            0x06
#define THERMO8_DEVID                            0x07
/** \} */

/**
 * \defgroup resolution Resolution
 * \{
 */
#define THERMO8_RESOLUTION_REG                   0x08
#define THERMO8_R05C_30MS                        0x00
#define THERMO8_R025C_65MS                       0x01
#define THERMO8_R0125C_130MS                     0x02
#define THERMO8_R00625C_250MS                    0x03
/** \} */

/** \} )*/ // End group macro 
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

    digital_in_t ale;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    uint16_t limit_status;

} thermo8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t ale;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermo8_cfg_t;

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
void thermo8_cfg_setup ( thermo8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO8_RETVAL thermo8_init ( thermo8_t *ctx, thermo8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Thermo8 click.
 */
void thermo8_default_cfg ( thermo8_t *ctx );

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
void thermo8_generic_write ( thermo8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void thermo8_generic_read ( thermo8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for returning the state of the alert pin.
 *
 * @param ctx          Click object.
 *
 * @description This function returning the state of the alert pin.
 */
uint8_t thermo8_ale_get ( thermo8_t *ctx );

/**
 * @brief Function for writing to 16 bit registers.
 *
 * @param ctx          Click object.
 * @param r_addr       Register address.
 * @param r_data       Data to be written.
 *
 * @description This function for writing to 16 bit registers.
 */
void thermo8_write_reg ( thermo8_t *ctx, uint8_t r_addr, uint16_t r_data );

/**
 * @brief Function for reading from 16 bit registers.
 *
 * @param ctx          Click object.
 * @param r_addr       Register address.
 *
 * @description This function for reading from 16 bit registers.
 */
uint16_t thermo8_read_reg ( thermo8_t *ctx, uint8_t r_addr );

/**
 * @brief Function for single byte writes.
 *
 * @param ctx          Click object.
 * @param r_addr       Register address.
 * @param r_data       Data to be written.
 *
 * @description This function for single byte writes.
 */
void thermo8_write_reg_8 ( thermo8_t *ctx, uint8_t r_addr, uint8_t r_data);

/**
 * @brief Function for single byte read's.
 *
 * @param ctx          Click object.
 * @param r_addr       Register address.
 *
 * @description This function for single byte read's.
 */
uint8_t thermo8_read_reg_8 ( thermo8_t *ctx, uint8_t r_addr );

/**
 * @brief Function will return the temperature value in �C.
 *
 * @param ctx          Click object.
 *
 * @description This function returns the temperature value in �C.
 */
float thermo8_get_temperature ( thermo8_t *ctx );

/**
 * @brief Function will set the conversion resoult temperature step depending on the passed constant.
 *
 * @param ctx          Click object.
 * @param r_cfg       Register address.
 *
 * @description This function sets the conversion resoult temperature step depending on the passed constant.
 */
void thermo8_set_resolution ( thermo8_t *ctx, uint8_t r_cfg );

/**
 * @brief Function will return the device ID.
 *
 * @param ctx          Click object.
 *
 * @description This function returns the device ID.
 */
uint16_t thermo8_get_dev_id ( thermo8_t *ctx );

/**
 * @brief Function will return the manufacturer ID.
 *
 * @param ctx          Click object.
 *
 * @description This function returns the manufacturer ID.
 */
uint16_t thermo8_get_man_id ( thermo8_t *ctx );

/**
 * @brief Function will place Thermo 8 to the low power mode.
 *
 * @param ctx          Click object.
 *
 * @description This function place Thermo 8 to the low power mode.
 * To read the data from the sensor you will need to call the thermo8_wakeup() function.
 */
void thermo8_sleep ( thermo8_t *ctx );

/**
 * @brief Function for waking up the click board from the sleep mode.
 *
 * @param ctx          Click object.
 *
 * @description This function waking up the click board from the sleep mode.
 */
void thermo8_wake_up ( thermo8_t *ctx );

/**
 * @brief Function for setting the temperature alarm levels for the lower, upper and critical alert levels.
 *
 * @param ctx               Click object.
 * @param limit_reg_addr    Limit register address constant.
 * @param limit             The temperature value that you want to limit the alert to.
 *
 * @description This function setting the temperature alarm levels for the lower, upper and critical alert levels.
 */
void thermo8_limit_set ( thermo8_t *ctx, uint8_t limit_reg_addr, float limit );

/**
 * @brief Function will return all alert states.
 *
 * @param ctx          Click object.
 *
 * @description This function will return all alert states. The alert can be tested with the predefined constants.
 */
uint8_t thermo8_get_alert_stat ( thermo8_t *ctx );

/**
 * @brief Function for setting the Tupper and Tlower hysterezis level as well as the alert mode.
 *
 * @param ctx           Click object.
 * @param thys          Hysterezis level.
 * @param alert_cfg     Set the alert trigger.
 *
 * @description This functionsetting the Tupper and Tlower hysterezis level as well as the alert mode.
 */
void thermo8_alert_enable ( thermo8_t *ctx, uint8_t thys, uint8_t alert_cfg );

/**
 * @brief Function for locking the critical temperature setting register.
 *
 * @param ctx          Click object.
 *
 * @description This function locking the critical temperature setting register.
 * By default at powerup the register is unlocked.
 */
void thermo8_tcrit_lock ( thermo8_t *ctx );

/**
 * @brief Function for unlocking the critical temperature setting register.
 *
 * @param ctx          Click object.
 *
 * @description This function unlocking the critical temperature setting register.
 */
void thermo8_tcrit_unlock ( thermo8_t *ctx );

/**
 * @brief Function for locking the Tupper and Tlower registers.
 *
 * @param ctx          Click object.
 *
 * @description locking the Tupper and Tlower registers.
 * By default at powerup the registers are unlocked.
 */
void thermo8_win_lock ( thermo8_t *ctx );

/**
 * @brief Function for unlocking the Tupper and Tlower registers.
 *
 * @param ctx          Click object.
 *
 * @description This function unlocking the Tupper and Tlower registers.
 */
void thermo8_win_unlock ( thermo8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
