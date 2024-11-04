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
 * \brief This file contains API for Qi Receiver Click driver.
 *
 * \addtogroup qireceiver Qi Receiver Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef QIRECEIVER_H
#define QIRECEIVER_H

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
#define QIRECEIVER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.teop = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.stat = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.end = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define QIRECEIVER_RETVAL  uint8_t

#define QIRECEIVER_OK           0x00
#define QIRECEIVER_INIT_ERROR   0xFF
/** \} */
/** \} */ // End group macro 
// -------------------------------------------------------------- PRIVATE MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup i2c_device_address I2C device address
 * \{
 */
#define QIRECEIVER_I2C_ADDR                                   0x25
/** \} */


/**
 * \defgroup vrect_registers VRECT Registers
 * \{
 */
#define  QIRECEIVER_VRECT_REG0                                0x40
#define  QIRECEIVER_VRECT_REG1                                0x41
/** \} */


/**
 * \defgroup iout_registers IOUT Registers
 * \{
 */
#define QIRECEIVER_IOUT_REG2                                  0x42
#define  QIRECEIVER_IOUT_REG3                                 0x43
/** \} */

/**
 * \defgroup frequency_registers Frequency Registers 
 * \{
 */
#define QIRECEIVER_FREQ_REG4                                  0x44
#define QIRECEIVER_FREQ_REG5                                  0x45
/** \} */


/**
 * \defgroup miscellaneous_functions_registers Miscellaneous Functions Registers
 * \{
 */
#define QIRECEIVER_REG7                                       0x47
#define QIRECEIVER_REG8                                       0x48
/** \} */


/**
 * \defgroup unique_ic_identifier_per_wpc_specification Unique IC identifier per WPC specification 
 * \{
 */
#define QIRECEIVER_WPC_ID_B0                                  0x54
#define QIRECEIVER_WPC_ID_B1                                  0x55
#define QIRECEIVER_WPC_ID_B2                                  0x56
#define QIRECEIVER_WPC_ID_B3                                  0x57
#define QIRECEIVER_WPC_ID_B4                                  0x58
#define QIRECEIVER_WPC_ID_B5                                  0x59
#define QIRECEIVER_WPC_ID_B6                                  0x5A
/** \} */


/**
 * \defgroup read_write_physical_fod_registers Read-Write physical FOD registers
 * \{
 */
#define QIRECEIVER_FOD9                                       0x49
#define QIRECEIVER_FOD10                                      0x4A
#define QIRECEIVER_FOD11                                      0x4B
#define QIRECEIVER_FOD12                                      0x4C
#define QIRECEIVER_FOD13                                      0x4D
#define QIRECEIVER_FOD14                                      0x4E
#define QIRECEIVER_FOD15                                      0x4F
#define QIRECEIVER_FOD16                                      0x50
#define QIRECEIVER_FOD17                                      0x51
#define QIRECEIVER_FOD18                                      0x52
#define QIRECEIVER_FOD19                                      0x53
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

    digital_out_t teop;
    digital_out_t en;
    digital_out_t end;

    // Input pins 

    digital_in_t stat;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} qireceiver_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t teop;
    pin_name_t en;
    pin_name_t stat;
    pin_name_t end;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} qireceiver_cfg_t;

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
void qireceiver_cfg_setup ( qireceiver_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
QIRECEIVER_RETVAL qireceiver_init ( qireceiver_t *ctx, qireceiver_cfg_t *cfg );

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
void qireceiver_generic_write ( qireceiver_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads data from the desired register.
 */
void qireceiver_generic_read ( qireceiver_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read Voltage function
 *
 * @param ctx Click object.
 *
 * @returns result float value of a current voltage
 *
 * @description Function is used to measure current voltage in volt.
**/
float qireceiver_read_voltage ( qireceiver_t *ctx );

/**
 * @brief Read Current function
 *
 * @param ctx Click object.
 *
 * @returns result float value of a current amperage
 *
 * @description Function is used to measure current amperage in mA.
**/
float qireceiver_read_current ( qireceiver_t *ctx );

/**
 * @brief Read Frequency function
 *
 * @param ctx Click object.
 *
 * @returns result float value of a current frequency
 *
 * @description Function is used to measure current frequency in hertz.
**/
float qireceiver_read_freq ( qireceiver_t *ctx );

/**
 * @brief Device enable function
 *
 * @param ctx Click object.
 * 
 * Function is used to enable the device.
**/
void qireceiver_dev_enable ( qireceiver_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _QIRECEIVER_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
