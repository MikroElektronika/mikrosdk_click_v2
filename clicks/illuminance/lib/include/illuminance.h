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
 * \brief This file contains API for Illuminance Click driver.
 *
 * \addtogroup illuminance Illuminance Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ILLUMINANCE_H
#define ILLUMINANCE_H

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
#define ILLUMINANCE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define  ILLUMINANCE_RETVAL  uint8_t

#define  ILLUMINANCE_OK                                            0x00
#define  ILLUMINANCE_INIT_ERROR                                    0xFF
/** \} */

/**
 * \defgroup i2c_address I2C Address
 * \{
 */
#define  ILLUMINANCE_TSL2561_I2C_ADDR_LOW                          0x29
#define  ILLUMINANCE_TSL2561_I2C_ADDR_FLOAT                        0x39
#define  ILLUMINANCE_TSL2561_I2C_ADDR_HIGH                         0x49
/** \} */

/**
 * \defgroup register_addr Register Address
 * \{
 */
#define  ILLUMINANCE_TSL2561_REGISTER_CONTROL                      0x00
#define  ILLUMINANCE_TSL2561_REGISTER_TIMING                       0x01
#define  ILLUMINANCE_TSL2561_REGISTER_THRESHHOLDL_LOW              0x02
#define  ILLUMINANCE_TSL2561_REGISTER_THRESHHOLDL_HIGH             0x03
#define  ILLUMINANCE_TSL2561_REGISTER_THRESHHOLDH_LOW              0x04
#define  ILLUMINANCE_TSL2561_REGISTER_THRESHHOLDH_HIGH             0x05
#define  ILLUMINANCE_TSL2561_REGISTER_INTERRUPT                    0x06
#define  ILLUMINANCE_TSL2561_REGISTER_CRC                          0x08
#define  ILLUMINANCE_TSL2561_REGISTER_ID                           0x0A
#define  ILLUMINANCE_TSL2561_REGISTER_CHAN0_LOW                    0x0C
#define  ILLUMINANCE_TSL2561_REGISTER_CHAN0_HIGH                   0x0D
#define  ILLUMINANCE_TSL2561_REGISTER_CHAN1_LOW                    0x0E
#define  ILLUMINANCE_TSL2561_REGISTER_CHAN1_HIGH                   0x0F
/** \} */

/**
 * \defgroup config_bits Configuration Bits
 * \{
 */
#define  ILLUMINANCE_TSL2561_INTEGRATIONTIME_13MS                  0x00
#define  ILLUMINANCE_TSL2561_INTEGRATIONTIME_101MS                 0x01
#define  ILLUMINANCE_TSL2561_INTEGRATIONTIME_402MS                 0x02
#define  ILLUMINANCE_TSL2561_GAIN_0X                               0x00
#define  ILLUMINANCE_TSL2561_GAIN_16X                              0x10
#define  ILLUMINANCE_TSL2561_COMMAND_BIT                           0x80
#define  ILLUMINANCE_TSL2561_CLEAR_BIT                             0x40
#define  ILLUMINANCE_TSL2561_WORD_BIT                              0x20
#define  ILLUMINANCE_TSL2561_BLOCK_BIT                             0x10
#define  ILLUMINANCE_TSL2561_CONTROL_POWERON                       0x03
#define  ILLUMINANCE_TSL2561_CONTROL_POWEROFF                      0x00
#define  ILLUMINANCE_TSL2561_CHSCALE_TINT0                         0x7517
#define  ILLUMINANCE_TSL2561_CHSCALE_TINT1                         0x0FE7
#define  ILLUMINANCE_TSL2561_LUX_SCALE                             14
#define  ILLUMINANCE_TSL2561_RATIO_SCALE                           9
#define  ILLUMINANCE_TSL2561_CH_SCALE                              10
/** \} */

/**
 * \defgroup t_fn_and_cl_package_coeff T, FN and CL package coefficients
 * \{
 */
#define  ILLUMINANCE_TSL2561_K1T                                   0x0040
#define  ILLUMINANCE_TSL2561_B1T                                   0x01f2
#define  ILLUMINANCE_TSL2561_M1T                                   0x01be
#define  ILLUMINANCE_TSL2561_K2T                                   0x0080
#define  ILLUMINANCE_TSL2561_B2T                                   0x0214
#define  ILLUMINANCE_TSL2561_M2T                                   0x02d1
#define  ILLUMINANCE_TSL2561_K3T                                   0x00c0
#define  ILLUMINANCE_TSL2561_B3T                                   0x023f
#define  ILLUMINANCE_TSL2561_M3T                                   0x037b
#define  ILLUMINANCE_TSL2561_K4T                                   0x0100
#define  ILLUMINANCE_TSL2561_B4T                                   0x0270
#define  ILLUMINANCE_TSL2561_M4T                                   0x03fe
#define  ILLUMINANCE_TSL2561_K5T                                   0x0138
#define  ILLUMINANCE_TSL2561_B5T                                   0x016f
#define  ILLUMINANCE_TSL2561_M5T                                   0x01fc
#define  ILLUMINANCE_TSL2561_K6T                                   0x019a
#define  ILLUMINANCE_TSL2561_B6T                                   0x00d2
#define  ILLUMINANCE_TSL2561_M6T                                   0x00fb
#define  ILLUMINANCE_TSL2561_K7T                                   0x029a
#define  ILLUMINANCE_TSL2561_B7T                                   0x0018
#define  ILLUMINANCE_TSL2561_M7T                                   0x0012
#define  ILLUMINANCE_TSL2561_K8T                                   0x029a
#define  ILLUMINANCE_TSL2561_B8T                                   0x0000
#define  ILLUMINANCE_TSL2561_M8T                                   0x0000
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

} illuminance_t;

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

} illuminance_cfg_t;

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
void illuminance_cfg_setup ( illuminance_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param illuminance Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ILLUMINANCE_RETVAL illuminance_init ( illuminance_t *ctx, illuminance_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration ( typically power on device and
 * set timing value ) for Illuminance click.
 */
void illuminance_default_cfg ( illuminance_t *ctx );

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
void illuminance_generic_write ( illuminance_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void illuminance_generic_read ( illuminance_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write data function
 *
 * @param ctx             Click object.
 * @param address         Register address.
 * @param write_command   Command to write.
 *
 * @description This function writes byte of data to TSL2561.
 */
void illuminance_write_data( illuminance_t *ctx, uint8_t address, uint8_t write_command );

/**
 * @brief Generic read data function
 *
 * @param ctx             Click object.
 * @param addr            Register address.
 *
 * @returns    8-bit data from addressed register from TSL2561
 *
 * @description This function reads byte of data from register address addr of TSL2561.
 */
uint8_t illuminance_read_data( illuminance_t *ctx, uint8_t addr );


/**
 * @brief Get Visible & Infrared value
 *
 * @param ctx             Click object.
 * @param value_ch0       Pointer to read Visible & Infrared value.
 * @param value_ch1       Pointer to read Infrared value.
 *
 * @description This function gets Visible & Infrared value.
 */
void illuminance_get_result( illuminance_t *ctx, uint16_t *value_ch0, uint16_t *value_ch1 );

/**
 * @brief Calculate lux value
 *
 * @param ctx             Click object.
 * @param value_gain      0x00 - No gain, 0x01 - 16x gain
 * @param value_int       0x00 - 13.7ms, 0x01 - 101ms, 0x02 - 402ms
 * @param channel0        Visible & Infrared data
 * @param channel1        Infrared data
 *
 * @returns               16-bit resulting lux calculation
 *
 * @descruotion This function calculates lux value from the TSL2561 sensor.
 */
uint16_t illuminance_calculate_lux( uint16_t value_gain, uint16_t value_int, uint16_t ch0, uint16_t ch1 );

/**
 * @brief Get interrupt pin status
 *
 * @param ctx            Click object.
 *
 * @returns              Interrupt pin state.
 *
 * @description This functions gets interrupt pin state.
 */
uint8_t illuminance_get_interrupt( illuminance_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _ILLUMINANCE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
