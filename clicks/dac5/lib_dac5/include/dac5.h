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
 * \brief This file contains API for DAC 5 Click driver.
 *
 * \addtogroup dac5 DAC 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DAC5_H
#define DAC5_H

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
#define DAC5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.lda = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DAC5_RETVAL  uint8_t

#define DAC5_OK                           0x00
#define DAC5_INIT_ERROR                   0xFF
#define DAC5_ERROR                        0
#define DAC5_SUCCESS                      1
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define DAC5_SLAVE_ADDRESS_BROADCAST      0x47
#define DAC5_SLAVE_ADDRESS_GND            0x48
#define DAC5_SLAVE_ADDRESS_VCC            0x49
#define DAC5_SLAVE_ADDRESS_SDA            0x4A
#define DAC5_SLAVE_ADDRESS_SCL            0x4B
/** \} */

/**
 * \defgroup vref Vref
 * \{
 */
#define DAC5_VREF_3300MV            3300
#define DAC5_VREF_5000MV            5000
#define DAC5_VREF_2048MV            2048
#define DAC5_VREF_1024MV            1024
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define DAC5_REG_CONFIG                   0x01
#define DAC5_REG_STATUS_TRIGGER           0x02
#define DAC5_REG_BRDCAST                  0x03
#define DAC5_REG_DAC_A_DATA               0x08
#define DAC5_REG_DAC_B_DATA               0x09
#define DAC5_REG_DAC_C_DATA               0x0A
#define DAC5_REG_DAC_D_DATA               0x0B
#define DAC5_REG_DAC_E_DATA               0x0C
#define DAC5_REG_DAC_F_DATA               0x0D
#define DAC5_REG_DAC_G_DATA               0x0E
#define DAC5_REG_DAC_H_DATA               0x0F
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define DAC5_CONFIG_DEFAULT               0x00FF
#define DAC5_CONFIG_GLOBAL_ENABLED        0x0000
#define DAC5_CONFIG_GLOBAL_DISABLED       0x0100
#define DAC5_CONFIG_A_ENABLED             0x0000
#define DAC5_CONFIG_A_DISABLED            0x0001
#define DAC5_CONFIG_B_ENABLED             0x0000
#define DAC5_CONFIG_B_DISABLED            0x0002
#define DAC5_CONFIG_C_ENABLED             0x0000
#define DAC5_CONFIG_C_DISABLED            0x0004
#define DAC5_CONFIG_D_ENABLED             0x0000
#define DAC5_CONFIG_D_DISABLED            0x0008
#define DAC5_CONFIG_E_ENABLED             0x0000
#define DAC5_CONFIG_E_DISABLED            0x0010
#define DAC5_CONFIG_F_ENABLED             0x0000
#define DAC5_CONFIG_F_DISABLED            0x0020
#define DAC5_CONFIG_G_ENABLED             0x0000
#define DAC5_CONFIG_G_DISABLED            0x0040
#define DAC5_CONFIG_H_ENABLED             0x0000
#define DAC5_CONFIG_H_DISABLED            0x0080
/** \} */

/**
 * \defgroup default_value Defalult value
 * \{
 */
#define DAC5_DEVICE_ID                    0x0300
#define DAC5_SOFTWARE_RESET               0x000A
/** \} */

/**
 * \defgroup data_limiter Data limiter
 * \{
 */
#define DAC5_MIN_DATA                     0x0000
#define DAC5_MAX_DATA                     0x0FFF
/** \} */

/**
 * \defgroup data_validation Data validation
 * \{
 */
#define DAC5_ERROR                        0
#define DAC5_SUCCESS                      1
/** \} */

/**
 * \defgroup working_mode Working mode
 * \{
 */
#define DAC5_SYNCHRONOUS                  1
#define DAC5_ASYNCHRONOUS                 0
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

    digital_out_t rst;
    digital_out_t lda;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    uint16_t vref;

} dac5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t lda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} dac5_cfg_t;

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
void dac5_cfg_setup ( dac5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
DAC5_RETVAL dac5_init ( dac5_t *ctx, dac5_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 *
 * @description This function writes data to the desired register.
 */
void dac5_generic_write ( dac5_t *ctx, uint8_t reg, uint16_t data_buf );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * 
 * @return Output read data
 *
 * @description This function reads data from the desired register.
 */
uint16_t dac5_generic_read ( dac5_t *ctx, uint8_t reg );

/**
 * @brief Function for configurating Click
 *
 * @param   ctx             Click object.
 * @param   config_data     Configuration data
 * 
 * @description This function sends configures device
 */
void dac5_config ( dac5_t *ctx, uint16_t config_data );

/**
 * @brief Function for reading device id
 * 
 * @param   ctx  Click object.
 * 
 * @return  DAC5_DEVICE_ID if successful.
 * 
 * @description This function gets device id
 */
uint16_t dac5_get_device_id ( dac5_t *ctx );

/**
 * @brief Function for software reset
 * 
 * @param   ctx  Click object.
 * 
 * @description This function resets device
 */
void dac5_software_reset ( dac5_t *ctx );

/**
 * @brief Function for clearing sent data
 * 
 * @param   ctx  Click object.
 * 
 * @description This functions clears output V
 */
void dac5_clear ( dac5_t *ctx );

/**
 * @brief Function for setting LDAC pin status
 *
 * @param   ctx         Click object.
 * @param   status      Should send either DAC5_SYNCHRONOUS or DAC5_ASYNCHRONOUS
 * 
 * @return either DAC5_ERROR or DAC5_SUCCESS.
 * 
 * @description This function sets state of ldac pin
 */
uint8_t dac5_set_ldac_pin ( dac5_t *ctx, uint8_t status );

/**
 * @brief Function for sending data to one output
 *
 * @param   ctx  Click object.
 * @param   data_reg    Registar of sending target
 * @param   data_buf   Data to be sent
 * 
 * @note data_buf have minimum (DAC5_MIN_DATA) and maximum (DAC5_MAX_DATA) value
 * 
 * @return either DAC5_ERROR or DAC5_SUCCESS.
 * 
 * @description This function sends data for changing V on output
 */
uint8_t dac5_send_data ( dac5_t *ctx, uint8_t data_reg, uint16_t data_buf );

#ifdef __cplusplus
}
#endif
#endif  // _DAC5_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
