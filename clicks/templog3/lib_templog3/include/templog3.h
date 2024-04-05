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
 * \brief This file contains API for Temp Log 3 Click driver.
 *
 * \addtogroup templog3 Temp Log 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPLOG3_H
#define TEMPLOG3_H

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
#define TEMPLOG3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPLOG3_RETVAL  uint8_t

#define TEMPLOG3_OK           0x00
#define TEMPLOG3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address  Device address
 * \{
 */
#define TEMPLOG3_SLAVE_ADDR_A0_H                     0x19
#define TEMPLOG3_SLAVE_ADDR_A0_L                     0x18
/** \} */

/**
 * \defgroup register  Register
 * \{
 */
#define TEMPLOG3_CAPABILITY_REG                      0x00
#define TEMPLOG3_CONFIG_REG                          0x01
#define TEMPLOG3_TEMP_UPPER_REG                      0x02
#define TEMPLOG3_TEMP_LOWER_REG                      0x03
#define TEMPLOG3_TEMP_CRITICAL_REG                   0x04
#define TEMPLOG3_TEMP_AMBIENT_REG                    0x05
#define TEMPLOG3_MANUFACT_ID_REG                     0x06
#define TEMPLOG3_DEVICE_ID_REG                       0x07
#define TEMPLOG3_RESOLUTION_REG                      0x08
/** \} */

/**
 * \defgroup status_mask  Status mask
 * \{
 */
#define TEMPLOG3_EVENT_SHDN_STATUS_MASK              0x80
#define TEMPLOG3_I2C_TIMEOUT_STATUS_MASK             0x40
#define TEMPLOG3_HIGH_VOLT_INPUT_STATUS_MASK         0x20
#define TEMPLOG3_RESOLUTION_STATUS_MASK              0x18
#define TEMPLOG3_MEAS_RANGE_STATUS_MASK              0x04
#define TEMPLOG3_ACCURACY_STATUS_MASK                0x02
#define TEMPLOG3_ALARM_STATUS_MASK                   0x01
/** \} */

/**
 * \defgroup settings_for_the_config_register  Settings for the config register
 * \{
 */
#define TEMPLOG3_TLIMIT_HYST_0_DEG                  0x0000
#define TEMPLOG3_TLIMIT_HYST_ONE_HALF_DEG           0x0200
#define TEMPLOG3_TLIMIT_HYST_3_DEG                  0x0400
#define TEMPLOG3_TLIMIT_HYST_6_DEG                  0x0600
#define TEMPLOG3_CONT_CONV_MODE                     0x0000
#define TEMPLOG3_SHUTDOWN_MODE                      0x0100
#define TEMPLOG3_TCRIT_LOCKED                       0x0080
#define TEMPLOG3_TUPPER_TLOWER_LOCKED               0x0040
#define TEMPLOG3_INT_CLEAR                          0x0020
#define TEMPLOG3_EVENT_OUTPUT_STATUS_MASK           0x0010
#define TEMPLOG3_EVENT_OUTPUT_EN                    0x0008
#define TEMPLOG3_EVENT_ALL_TLIMIT                   0x0000
#define TEMPLOG3_EVENT_TCRIT_ONLY                   0x0004
#define TEMPLOG3_EVENT_POL_ACT_LOW                  0x0000
#define TEMPLOG3_EVENT_POL_ACT_HIGH                 0x0002
#define TEMPLOG3_EVENT_COMPARATOR_MODE              0x0000
#define TEMPLOG3_EVENT_INTERRUPT_MODE               0x0001
/** \} */

/**
 * \defgroup limit_and_function_response  Limit and function response
 * \{
 */
#define TEMPLOG3_TCRIT_DETECT                        0x80
#define TEMPLOG3_TUPPER_DETECT                       0x40
#define TEMPLOG3_TLOWER_DETECT                       0x20
#define TEMPLOG3_NBYTES_ERROR                        0x04
#define TEMPLOG3_TEMP_RANGE_ERROR                    0x03
#define TEMPLOG3_ADDR_ERROR                          0x02
#define TEMPLOG3_ALARMING                            0x01
#define TEMPLOG3_OK                                  0x00
/** \} */

/**
 * \defgroup resolution  Resolution 
 * \{
 */
#define TEMPLOG3_12BIT_RESOLUTION                    0x03
#define TEMPLOG3_11BIT_RESOLUTION                    0x02
#define TEMPLOG3_10BIT_RESOLUTION                    0x01
#define TEMPLOG3_9BIT_RESOLUTION                     0x00
/** \} */

/**
 * \defgroup eeprom_writing  Eeprom writing
 * \{
 */
#define TEMPLOG3_EEPROM_WRITE                        0x00
#define TEMPLOG3_SW_WRITE_PROTECT                    0x01
#define TEMPLOG3_CLEAR_WRITE_PROTECT                 0x02
/** \} */

/**
 * \defgroup max_eeprom_size  Max eeprom size 
 * \{
 */
#define TEMPLOG3_EEPROM_SIZE                          256
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
    uint8_t slave_eeprom;

    uint8_t resolution;
    uint8_t n_bytes;

} templog3_t;

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
    uint8_t i2c_eeprom;

    uint8_t dev_resolution;
    uint8_t dev_n_bytes;

} templog3_cfg_t;

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
void templog3_cfg_setup ( templog3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPLOG3_RETVAL templog3_init ( templog3_t *ctx, templog3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @note 
 * <pre>
 *      Set: TEMPLOG3_CONFIG_REG
 *            - TEMPLOG3_TLIMIT_HYST_0_DEG | 
 *            - TEMPLOG3_CONT_CONV_MODE | 
 *            - TEMPLOG3_EVENT_OUTPUT_EN | 
 *            - TEMPLOG3_EVENT_TCRIT_ONLY | 
 *            - TEMPLOG3_EVENT_POL_ACT_HIGH | 
 *            - TEMPLOG3_EVENT_COMPARATOR_MODE
 *    Set: TEMPLOG3_RESOLUTION_REG
 *            - TEMPLOG3_11BIT_RESOLUTION
 *    Set: TEMPLOG3_TEMP_CRITICAL_REG
 *            - 26.5
 *    Set: TEMPLOG3_TEMP_UPPER_REG
 *            - 30
 *    Set: TEMPLOG3_TEMP_LOWER_REG
 *            - -5
 * </pre>
 * 
 * @description This function executes default configuration for TempLog3 click.
 */
void templog3_default_cfg ( templog3_t *ctx );

/**
 * @brief Generic Write function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address where data be written
 * @param data_in   16bit data to be written
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function writes a 16bit data to the desired register.
 */
uint8_t templog3_write_reg ( templog3_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Generic Read function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address which from data be read
 * @param data_out  Memory where 16bit data be placed
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function reads a 16bit data from the desired register.
 */
uint8_t templog3_read_reg ( templog3_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Set Address Pointer function
 *
 * @param ctx       Click object.
 * @param reg_addr  Address on which the internal address pointer be set
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function sets the internal address pointer on the desired register address.
 */
uint8_t templog3_set_addr_ptr ( templog3_t *ctx, uint8_t reg_addr );

/**
 * @brief Repeated Read function
 *
 * @param ctx       Click object.
 * @param data_out  Memory where 16bit data be placed
 *
 * @description Function reads a 16bit data from the register on which the internal address pointer was last set.
 */
void templog3_repeated_read ( templog3_t *ctx, uint16_t *data_out );

/**
 * @brief Get Temperature function
 *
 * @param ctx       Click object.
 * @param temp_sel  Address of the desired temperature register
 * @param temp_out  Returns a temperature value calculated to the Celsius degrees
 *
 * @returns 0 - OK, 2 - Wrong address
 *
 * @description Function gets a temperature value from the desired temperature register calculated to the Celsius degrees.
 */
uint8_t templog3_get_temp ( templog3_t *ctx, uint8_t temp_sel, float *temp_out );

/**
 * @brief Set Temperature function
 *
 * @param ctx       Click object.
 * @param temp_sel  Address of the desired temperature register
 * @param temp_in   Temperature value to be written calculated to the Celsius degrees
 *
 * @returns 0 - OK, 2 - Wrong address, 3 - Temperature value is out of range
 *
 * @description Function sets a desired temperature register on the desired value calculated to the Celsius degrees.
 */
uint8_t templog3_set_temp ( templog3_t *ctx, uint8_t temp_sel, float temp_in );

/**
 * @brief Alarm-Event Check function
 *
 * @param ctx          Click object.
 * 
 * @returns 0 - OK, 1 - Alarming, when alarm (event) pin polarity is set to active high
 *
 * @description Function checks the alarm (event) pin state.
 */
uint8_t templog3_check_alarm ( templog3_t *ctx );

/**
 * @brief Conversion Time function
 *
 * @param ctx          Click object.
 * 
 * @description Function ensures that the minimum conversion time is met.
 */
void templog3_wait_conv_done ( templog3_t *ctx );

/**
 * @brief EEPROM Single Write function
 *
 * @param ctx          Click object.
 * @param reg_addr     Memory address where one byte data be written
 * @param data_in      Data byte to be written
 * @param eeprom_mode  0 - EEPROM Write, 1 - SW Write Protection, 2 - Clear Write Protection
 *
 * @description Function writes a one byte data to the EEPROM including/excluding a write protection.
 */
void templog3_eeprom_byte_write ( templog3_t *ctx, uint8_t reg_addr, uint8_t data_in, uint8_t eeprom_mode );

/**
 * @brief EEPROM Page Write function
 *
 * @param ctx          Click object.
 * @param reg_addr     Memory start address which from a writing cycle be started
 * @param data_in      Data to be written, 16 bytes of data
 *
 * @description Function writes a 16 bytes of data to the selected EEPROM page.
 */
void templog3_eeprom_page_write ( templog3_t *ctx, uint8_t reg_addr, uint8_t *data_in );

/**
 * @brief EEPROM Current Address Read function
 *
 * @param ctx              Click object.
 * @param current_address  Returns the address of the last word accessed internally incremented by 1
 *
 * @description Function returns the address of the last word accessed internally incremented by 1.
 */
void templog3_eeprom_curr_addr_read ( templog3_t *ctx, uint8_t *current_address );

/**
 * @brief EEPROM Single Read function
 *
 * @param ctx       Click object.
 * @param reg_addr  Memory address which from data byte be read
 * @param data_out  Memory where data byte be placed
 *
 * @description Function reads a one byte data from the EEPROM.
 */
void templog3_eeprom_byte_read ( templog3_t *ctx, uint8_t reg_addr, uint8_t *data_out );

/**
 * @brief EEPROM Sequential Read function
 *
 * @param ctx          Click object.
 * @param reg_addr     Memory start address which from a reading cycle be started
 * @param data_out     Memory where data be placed
 * @param num_bytes    Number of bytes to be read
 *
 * @returns 0 - OK, 4 - Number of bytes is out of range
 *
 * @description Function reads a desired number of bytes from the EEPROM.
 * @note Sum of the memory address and number of bytes must not be higher than 256.
 */
uint8_t templog3_eeprom_sequential_read ( templog3_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint16_t num_bytes );


#ifdef __cplusplus
}
#endif
#endif  // _TEMPLOG3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
