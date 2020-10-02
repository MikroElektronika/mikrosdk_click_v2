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
 * \brief This file contains API for VCP monitor Click driver.
 *
 * \addtogroup vcpmonitor VCP monitor Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VCPMONITOR_H
#define VCPMONITOR_H

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
#define VCPMONITOR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VCPMONITOR_RETVAL  uint8_t

#define VCPMONITOR_OK                               0x00
#define VCPMONITOR_INIT_ERROR                       0xFF
/** \} */

/**
 * \defgroup reg Registers
 * \{
 */
#define VCPMONITOR_REG_CONFIGURATION                0x00
#define VCPMONITOR_REG_CURRENT_DATA                 0x01
#define VCPMONITOR_REG_BUS_VOLTAGE_DATA             0x02
#define VCPMONITOR_REG_POWER_DATA                   0x03
#define VCPMONITOR_REG_MASK_ENABLE                  0x06
#define VCPMONITOR_REG_ALERT_LIMIT                  0x07
#define VCPMONITOR_REG_MANUFACTURE_ID               0xFE
#define VCPMONITOR_REG_DIE_ID                       0xFF
/** \} */

/**
 * \defgroup slv_addr Slave address
 * \{
 */
#define VCPMONITOR_SLAVE_ADDR_GND_GND               0x40
#define VCPMONITOR_SLAVE_ADDR_GND_VS                0x41
#define VCPMONITOR_SLAVE_ADDR_GND_SDA               0x42
#define VCPMONITOR_SLAVE_ADDR_GND_SCL               0x43
#define VCPMONITOR_SLAVE_ADDR_VS_GND                0x44
#define VCPMONITOR_SLAVE_ADDR_VS_VS                 0x45
#define VCPMONITOR_SLAVE_ADDR_VS_SDA                0x46
#define VCPMONITOR_SLAVE_ADDR_VS_SCL                0x47
#define VCPMONITOR_SLAVE_ADDR_SDA_GND               0x48
#define VCPMONITOR_SLAVE_ADDR_SDA_VS                0x49
#define VCPMONITOR_SLAVE_ADDR_SDA_SDA               0x4A
#define VCPMONITOR_SLAVE_ADDR_SDA_SCL               0x4B
#define VCPMONITOR_SLAVE_ADDR_SCL_GND               0x4C
#define VCPMONITOR_SLAVE_ADDR_SCL_VS                0x4D
#define VCPMONITOR_SLAVE_ADDR_SCL_SDA               0x4E
#define VCPMONITOR_SLAVE_ADDR_SCL_SCL               0x4F
/** \} */

/**
 * \defgroup  regr_val Register default values
 * \{
 */
#define VCPMONITOR_DEF_MANUFACTURE_ID               0x5449
#define VCPMONITOR_DEF_DIE_ID                               0x2270
#define VCPMONITOR_DEF_CONFIGURATION                0x6127
/** \} */


/**
 * \defgroup  cfg_reg Configuration register
 * \{
 */
#define VCPMONITOR_CFG_RESET_ON                     0x8000
#define VCPMONITOR_CFG_RESET_OFF                    0x0000
#define VCPMONITOR_CFG_NUM_OF_AVG_1                 0x0000
#define VCPMONITOR_CFG_NUM_OF_AVG_4                 0x0200
#define VCPMONITOR_CFG_NUM_OF_AVG_16                0x0400
#define VCPMONITOR_CFG_NUM_OF_AVG_64                0x0600
#define VCPMONITOR_CFG_NUM_OF_AVG_128               0x0800
#define VCPMONITOR_CFG_NUM_OF_AVG_256               0x0A00
#define VCPMONITOR_CFG_NUM_OF_AVG_512               0x0C00
#define VCPMONITOR_CFG_NUM_OF_AVG_1024              0x0E00
#define VCPMONITOR_CFG_VBUSCT_140us                 0x0000
#define VCPMONITOR_CFG_VBUSCT_204us                 0x0040
#define VCPMONITOR_CFG_VBUSCT_332us                 0x0080
#define VCPMONITOR_CFG_VBUSCT_588us                 0x00C0
#define VCPMONITOR_CFG_VBUSCT_1p1ms                 0x0100
#define VCPMONITOR_CFG_VBUSCT_2p116ms               0x0140
#define VCPMONITOR_CFG_VBUSCT_4p156ms               0x0180
#define VCPMONITOR_CFG_VBUSCT_8p244ms               0x01C0
#define VCPMONITOR_CFG_ISHCT_140us                  0x0000
#define VCPMONITOR_CFG_ISHCT_204us                  0x0008
#define VCPMONITOR_CFG_ISHCT_332us                  0x0010
#define VCPMONITOR_CFG_ISHCT_588us                  0x0018
#define VCPMONITOR_CFG_ISHCT_1p1ms                  0x0020
#define VCPMONITOR_CFG_ISHCT_2p116ms                0x0028
#define VCPMONITOR_CFG_ISHCT_4p156ms                0x0030
#define VCPMONITOR_CFG_ISHCT_8p244ms                0x0038
#define VCPMONITOR_CFG_MODE_POWER_DOWN              0x0000
#define VCPMONITOR_CFG_MODE_CURRENT_TRIG            0x0001
#define VCPMONITOR_CFG_MODE_VOLTAGE_TRIG            0x0002
#define VCPMONITOR_CFG_MODE_CURR_VOLT_TRIG          0x0003
#define VCPMONITOR_CFG_MODE_CURRENT_CONT            0x0005
#define VCPMONITOR_CFG_MODE_VOLTAGE_CONT            0x0006
#define VCPMONITOR_CFG_MODE_CURR_VOLT_CONT          0x0007
/** \} */

/**
 * \defgroup  mask_reg Mask Enable register
 * \{
 */
// Mask Enable register
#define VCPMONITOR_MASK_OCL_DISABLE                 0x0000
#define VCPMONITOR_MASK_UCL_ENABLE                  0x4000
#define VCPMONITOR_MASK_UCL_DISABLE                 0x0000
#define VCPMONITOR_MASK_BOL_ENABLE                  0x2000
#define VCPMONITOR_MASK_BOL_DISABLE                 0x0000
#define VCPMONITOR_MASK_BUL_ENABLE                  0x1000
#define VCPMONITOR_MASK_OCL_ENABLE                  0x8000
#define VCPMONITOR_MASK_BUL_DISABLE                 0x0000
#define VCPMONITOR_MASK_POL_ENABLE                  0x0800
#define VCPMONITOR_MASK_POL_DISABLE                 0x0000
#define VCPMONITOR_MASK_CNVR_ENABLE                0x0400
#define VCPMONITOR_MASK_CNVR_DISABLE             0x0000
#define VCPMONITOR_MASK_AFF_ENABLE                 0x0010
#define VCPMONITOR_MASK_AFF_DISABLE                0x0000
#define VCPMONITOR_MASK_CVRF_ENABLE               0x0008
#define VCPMONITOR_MASK_CVRF_DISABLE              0x0000
#define VCPMONITOR_MASK_OVF_ENABLE                 0x0004
#define VCPMONITOR_MASK_OVF_DISABLE                0x0000
#define VCPMONITOR_MASK_APOL_ENABLE                0x0002
#define VCPMONITOR_MASK_APOL_DISABLE               0x0000
#define VCPMONITOR_MASK_LEN_ENABLE                  0x0001
#define VCPMONITOR_MASK_LEN_DISABLE                 0x0000
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

} vcpmonitor_t;

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

} vcpmonitor_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
  #define CURRENT_CONSTANT 1.25
  #define VOLTAGE_CONSTANT 1.25
  #define POWER_CONSTANT   10
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */
  static uint8_t dev_slave_addr;


/** \} */ // End variable group
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
void vcpmonitor_cfg_setup ( vcpmonitor_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
VCPMONITOR_RETVAL vcpmonitor_init ( vcpmonitor_t *ctx, vcpmonitor_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for VCPmonitor click.
 */
void vcpmonitor_default_cfg ( vcpmonitor_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx           Click object.
 * @param reg           Register address.
 * @param data_buf  Data buf to be written.
 * @param len           Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void vcpmonitor_generic_write ( vcpmonitor_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx             Click object.
 * @param reg             Register address.
 * @param data_buf        Output data buf
 * @param len             Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void vcpmonitor_generic_read ( vcpmonitor_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief                 Writes data to register
 *
 * @param ctx             Click object.
 * @param reg             Register address
 * @param tx_data         Data to be write in the register
 *
 * @description This function writes data to register.
 */
void vcpmonitor_write_data ( vcpmonitor_t *ctx, uint8_t reg, uint16_t tx_data );

/**
 * @brief               Reads data from register
 *
 * @param ctx             Click object. 
 * @param reg             Register address
 * @return                16-bit data read from the register
 *
 * @description This function reads data from register.
 */
uint16_t vcpmonitor_read_data ( vcpmonitor_t *ctx, uint8_t reg_addr  );

/**
 * @brief Gets Interrupt pin state
 *
 * @param ctx             Click object.
 * 
 * @return Interrupt pin state
 *
 * @description This function gets Interrupt pin state.
 */
uint8_t vcpmonitor_get_interrupt_state( vcpmonitor_t *ctx );

/**
 * @brief     Reads current data in mA
 *
 * @param ctx             Click object.
 *
 * @return   Current data in mA
 *
 * @description This function reads current data in mA.
 */
float vcpmonitor_get_current ( vcpmonitor_t *ctx );

/**
 * @brief     Reads voltage data in mV
 *
 * @param ctx             Click object.
 * 
 * @return  Voltage data in mV
 *
 * @description This function reads voltage data in mV.
 */
float vcpmonitor_get_voltage ( vcpmonitor_t *ctx );

/**
 * @brief    Reads power data in mW
 *
 * @param ctx             Click object.

 * @return  Power data in mW
 *
 * @description This function reads power data in mW.
 */
float vcpmonitor_get_power ( vcpmonitor_t *ctx );

/**
 * @brief Gets Manufacture ID and Device ID
 *
 * @param ctx             Click object. 
 * @param manufacture_id  Manufacture ID data
 * @param did_id          Device ID data
 *
 * @return Communication errors
 *
 * @description This function gets Manufacture ID and Device ID
 */
uint8_t vcpmonitor_get_id_value ( vcpmonitor_t *ctx, uint16_t *manufacture_id, uint16_t* did_id );


#ifdef __cplusplus
}
#endif
#endif  // _VCPMONITOR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
