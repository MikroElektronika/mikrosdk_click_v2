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
 * \brief This file contains API for Temp Log 4 Click driver.
 *
 * \addtogroup templog4 Temp Log 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPLOG4_H
#define TEMPLOG4_H

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
#define TEMPLOG4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPLOG4_RETVAL  uint8_t

#define TEMPLOG4_OK           0x00
#define TEMPLOG4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register   Register
 * \{
 */
#define TEMPLOG4_SLAVE_ADDR_A0_H                   0x19
#define TEMPLOG4_SLAVE_ADDR_A0_L                   0x18
/** \} */

/**
* \defgroup register_1   Register 1
* \{
*/
#define TEMPLOG4_CAPABILITY_REG                    0x00
#define TEMPLOG4_CONFIG_REG                        0x01
#define TEMPLOG4_TEMP_UPPER_REG                    0x02
#define TEMPLOG4_TEMP_LOWER_REG                    0x03
#define TEMPLOG4_TEMP_CRITICAL_REG                 0x04
#define TEMPLOG4_TEMP_AMBIENT_REG                  0x05
#define TEMPLOG4_MANUFACT_ID_REG                   0x06
#define TEMPLOG4_DEVICE_ID_REG                     0x07
#define TEMPLOG4_SMBUS_REG                         0x22
/** \} */

/**
* \defgroup mask  Mask
* \{
*/
#define TEMPLOG4_EVENT_SHDN_STATUS_MASK            0x80
#define TEMPLOG4_BUS_TIMEOUT_STATUS_MASK           0x40
#define TEMPLOG4_HIGH_VOLT_INPUT_STATUS_MASK       0x20
#define TEMPLOG4_RESOLUTION_STATUS_MASK            0x18
#define TEMPLOG4_MEAS_RANGE_STATUS_MASK            0x04
#define TEMPLOG4_ACCURACY_STATUS_MASK              0x02
#define TEMPLOG4_ALARM_STATUS_MASK                 0x01
/** \} */

/**
* \defgroup config   Config
* \{
*/
#define TEMPLOG4_TLIMIT_HYST_0_DEG                0x0000
#define TEMPLOG4_TLIMIT_HYST_ONE_HALF_DEG         0x0200
#define TEMPLOG4_TLIMIT_HYST_3_DEG                0x0400
#define TEMPLOG4_TLIMIT_HYST_6_DEG                0x0600
#define TEMPLOG4_CONT_CONV_MODE                   0x0000
#define TEMPLOG4_SHUTDOWN_MODE                    0x0100
#define TEMPLOG4_TCRIT_LOCKED                     0x0080
#define TEMPLOG4_TUPPER_TLOWER_LOCKED             0x0040
#define TEMPLOG4_INT_CLEAR                        0x0020
#define TEMPLOG4_EVENT_OUTPUT_STATUS_MASK         0x0010
#define TEMPLOG4_EVENT_OUTPUT_EN                  0x0008
#define TEMPLOG4_EVENT_ALL_TLIMIT                 0x0000
#define TEMPLOG4_EVENT_TCRIT_ONLY                 0x0004
#define TEMPLOG4_EVENT_POL_ACT_LOW                0x0000
#define TEMPLOG4_EVENT_POL_ACT_HIGH               0x0002
#define TEMPLOG4_EVENT_COMPARATOR_MODE            0x0000
#define TEMPLOG4_EVENT_INTERRUPT_MODE             0x0001
/** \} */

/**
* \defgroup alters  Alters
* \{
*/
#define TEMPLOG4_TCRIT_DETECT                      0x80
#define TEMPLOG4_TUPPER_DETECT                     0x40
#define TEMPLOG4_TLOWER_DETECT                     0x20
#define TEMPLOG4_NBYTES_ERROR                      0x04
#define TEMPLOG4_TEMP_RANGE_ERROR                  0x03
#define TEMPLOG4_ADDR_ERROR                        0x02
#define TEMPLOG4_ALARMING                          0x01
#define TEMPLOG4_OK                                0x00
/** \} */

/**
* \defgroup enable_disable  Enable Disable
* \{
*/
#define TEMPLOG4_SMBUS_TIMEOUT_DIS                 0x80
#define TEMPLOG4_SMBUS_TIMEOUT_SHTDN_EN            0x20
#define TEMPLOG4_SMBUS_ARA_DIS                     0x01
/** \} */

/**
* \defgroup eeprom_write  Eeprom Write
* \{
*/
#define TEMPLOG4_EEPROM_WRITE                      0x00
#define TEMPLOG4_SW_WRITE_PROTECT                  0x01
#define TEMPLOG4_CLEAR_WRITE_PROTECT               0x02
/** \} */

/**
* \defgroup eeprom_size   Eeprom Size
* \{
*/
#define _TEMPLOG4_EEPROM_SIZE                      256
#define _TEMPLOG4_MANUFACT_ID                      0x1131
#define _TEMPLOG4_DEVICE_ID                        0xA203
#define TEMPLOG4_DUMMY_BYTE                        0x00
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

} templog4_t;

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
    uint8_t i2c_eeprom_address;

} templog4_cfg_t;

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
void templog4_cfg_setup ( templog4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPLOG4_RETVAL templog4_init ( templog4_t *ctx, templog4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TempLog4 click.
 */
void templog4_default_cfg ( templog4_t *ctx );

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
void templog4_generic_write ( templog4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void templog4_generic_read ( templog4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic Write function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param input_data   16bit data to be written
 *
 * @description This function writes a 16bit data to the desired register.
 */
uint8_t templog4_write_reg ( templog4_t *ctx, uint8_t reg, uint16_t input_data );

/**
 * @brief Generic Read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param out_var      Memory where 16bit data be placed.
 *
 * @description This function reads a 16bit data from the desired register.
 */
uint8_t templog4_read_reg ( templog4_t *ctx, uint8_t reg, uint16_t *out_var );

/**
 * @brief Set Address Pointer function.
 * 
 * @param ctx          Click object.
 * @param addr         Address on which the internal address pointer be set.
 *
 * @description This function sets the internal address pointer on the desired register address.
 */
void templog4_set_addr_ptr ( templog4_t *ctx, uint8_t addr );

/**
 * @brief Repeated Read function.
 * 
 * @param ctx          Click object.
 * @param addr         Address on which the internal address pointer be set.
 *
 * @description This function sets the internal address pointer on the desired register address.
 */
void templog4_repeated_read ( templog4_t *ctx, uint16_t *out_var );

/**
 * @brief Get Temperature function.
 * 
 * @param ctx          Click object.
 * @param temp_sel     Address of the desired temperature register.
 * @param temp_out     Returns a temperature value calculated to the Celsius degrees.
 *
 * @description This function gets a temperature value from the desired temperature register calculated to the Celsius degrees.
 */
uint8_t templog4_get_temp ( templog4_t *ctx, uint8_t temp_sel, float *temp_out );

/**
 * @brief Set Temperature function.
 * 
 * @param ctx          Click object.
 * @param temp_sel     Address of the desired temperature register.
 * @param temp_in      Temperature value to be written calculated to the Celsius degrees.
 *
 * @description This function sets a desired temperature register on the desired value calculated to the Celsius degrees.
 */
void templog4_set_temp ( templog4_t *ctx, uint8_t temp_sel, float temp_in );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPLOG4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
