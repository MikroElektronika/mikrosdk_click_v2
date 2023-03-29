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
 * \brief This file contains API for IR SENSE Click driver.
 *
 * \addtogroup irsense IR SENSE Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRSENSE_H
#define IRSENSE_H

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
#define IRSENSE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pdn = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRSENSE_RETVAL  uint8_t

#define IRSENSE_OK           0x00
#define IRSENSE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address I2C address
 * \{
 */
#define IRSENSE_I2C_ADDRESS_0                                       0x64
#define IRSENSE_I2C_ADDRESS_1                                       0x65
#define IRSENSE_I2C_ADDRESS_2                                       0x66
/** \} */

/**
 * \defgroup register_addresses Register addresses
 * \{
 */
#define IRSENSE_REG_WIA1                                            0x00
#define IRSENSE_REG_WIA2                                            0x01
#define IRSENSE_REG_INFO1                                           0x02
#define IRSENSE_REG_INFO2                                           0x03
#define IRSENSE_REG_INTST                                           0x04
#define IRSENSE_REG_ST1                                             0x05
#define IRSENSE_REG_IR1_LOW                                         0x06
#define IRSENSE_REG_IR1_HIGH                                        0x07
#define IRSENSE_REG_IR2_LOW                                         0x08
#define IRSENSE_REG_IR2_HIGH                                        0x09
#define IRSENSE_REG_IR3_LOW                                         0x0A
#define IRSENSE_REG_IR3_HIGH                                        0x0B
#define IRSENSE_REG_IR4_LOW                                         0x0C
#define IRSENSE_REG_IR4_HIGH                                        0x0D
#define IRSENSE_REG_TMP_LOW                                         0x0E
#define IRSENSE_REG_TMP_HIGH                                        0x0F
#define IRSENSE_REG_ST2                                             0x10
#define IRSENSE_REG_ETH13H_LOW                                      0x11
#define IRSENSE_REG_ETH13H_HIGH                                     0x12
#define IRSENSE_REG_ETH13L_LOW                                      0x13
#define IRSENSE_REG_ETH13L_HIGH                                     0x14
#define IRSENSE_REG_ETH24H_LOW                                      0x15
#define IRSENSE_REG_ETH24H_HIGH                                     0x16
#define IRSENSE_REG_ETH24L_LOW                                      0x17
#define IRSENSE_REG_ETH24L_HIGH                                     0x18
#define IRSENSE_REG_EHYS13                                          0x19
#define IRSENSE_REG_EHYS24                                          0x1A
#define IRSENSE_REG_EINTEN                                          0x1B
#define IRSENSE_REG_ECNTL1                                          0x1C
#define IRSENSE_REG_CNTL2                                           0x1D
/** \} */

/**
 * \defgroup eeprom_register_map EEPROM Register Map
 * \{
 */
#define IRSENSE_EEPROM_MAP_EKEY                                     0x50
#define IRSENSE_EEPROM_MAP_ETH13H_LOW                               0x51
#define IRSENSE_EEPROM_MAP_ETH13H_HIGH                              0x52
#define IRSENSE_EEPROM_MAP_ETH13L_LOW                               0x53
#define IRSENSE_EEPROM_MAP_ETH13L_HIGH                              0x54
#define IRSENSE_EEPROM_MAP_ETH24H_LOW                               0x55
#define IRSENSE_EEPROM_MAP_ETH24H_HIGH                              0x56
#define IRSENSE_EEPROM_MAP_ETH24L_LOW                               0x57
#define IRSENSE_EEPROM_MAP_ETH24L_HIGH                              0x58
#define IRSENSE_EEPROM_MAP_EHYS13                                   0x59
#define IRSENSE_EEPROM_MAP_EHYS24                                   0x5A
#define IRSENSE_EEPROM_MAP_EINTEN                                   0x5B
#define IRSENSE_EEPROM_MAP_ECNTL1                                   0x5C
/** \} */

/**
 * \defgroup ecntl1_bit_map ECNTL1 Bit Map
 * \{
 */
#define IRSENSE_ECNTL1_MODE_STAND_BY                                0x00
#define IRSENSE_ECNTL1_MODE_EEPROM_ACCESS                           0x01
#define IRSENSE_ECNTL1_MODE_SINGLE_SHOT                             0x02
#define IRSENSE_ECNTL1_MODE_BE_PROHIBITED                           0x03
#define IRSENSE_ECNTL1_MODE_CONTINUOUS_0                            0x04
#define IRSENSE_ECNTL1_MODE_CONTINUOUS_1                            0x05
#define IRSENSE_ECNTL1_MODE_CONTINUOUS_2                            0x06
#define IRSENSE_ECNTL1_MODE_CONTINUOUS_3                            0x07
#define IRSENSE_ECNTL1_CUTOFF_FREQUENCY_0_3_Hz                      0x00
#define IRSENSE_ECNTL1_CUTOFF_FREQUENCY_0_6_Hz                      0x08
#define IRSENSE_ECNTL1_CUTOFF_FREQUENCY_1_1_Hz                      0x10
#define IRSENSE_ECNTL1_CUTOFF_FREQUENCY_2_2_Hz                      0x18
#define IRSENSE_ECNTL1_CUTOFF_FREQUENCY_4_4_Hz                      0x20
#define IRSENSE_ECNTL1_CUTOFF_FREQUENCY_8_8_Hz                      0x28
/** \} */

/**
 * \defgroup interrupt_source_setting Interrupt Source setting
 * \{
 */
#define IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE                        0x00
#define IRSENSE_EINTEN_IR13_HIGH_INT_ENABLE                         0x01
#define IRSENSE_EINTEN_IR13_LOW_INT_DISABLE                         0x00
#define IRSENSE_EINTEN_IR13_LOW_INT_ENABLE                          0x01
#define IRSENSE_EINTEN_IR24_HIGH_INT_DISABLE                        0x00
#define IRSENSE_EINTEN_IR24_HIGH_INT_ENABLE                         0x01
#define IRSENSE_EINTEN_IR24_LOW_INT_DISABLE                         0x00
#define IRSENSE_EINTEN_IR24_LOW_INT_ENABLE                          0x01
#define IRSENSE_EINTEN_DRI_INT_DISABLE                              0x00
#define IRSENSE_EINTEN_DRI_INT_ENABLE                               0x01

#define IRSENSE_CNTL2_SOFT_RESET                                    0x01
#define IRSENSE_EEPROM_MAP_VAL_EKEY                                 0xA5
#define IRSENSE_ENABLE_SETTINGS_EEPROM_MODE                         0x38
#define IRSENSE_ENABLE_EEPROM_MODE                                  0xC1
#define IRSENSE_EINTEN_RESET_VALUE                                  0xC0
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

    digital_out_t pdn;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} irsense_t;

/**
 * @brief IR data structure definition.
 */
typedef struct
{
    int16_t bottom_area;
    int16_t left_area;
    int16_t right_area;
    int16_t top_area;

} irsense_ir_data_t;

/**
 * @brief Enable interrupt structure definition.
 */
typedef struct
{
    uint8_t ir13h;
    uint8_t ir13l;
    uint8_t ir24h;
    uint8_t ir24l;
    uint8_t dr;
} irsense_eint_t;

/**
 * @brief Register address structure definition.
 */
 typedef struct
{
    uint16_t eth24h;
    uint16_t eth24l;
    uint16_t eth13h;
    uint16_t eth13l;
} irsense_reg_t;

/**
 * @brief EEPROM map structure definition.
 */
 typedef struct
{   
    uint16_t eeth24h;
    uint16_t eeth24l;
    uint16_t eeth13h;
    uint16_t eeth13l;
} irsense_eeprom_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t pdn;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} irsense_cfg_t;

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
void irsense_cfg_setup ( irsense_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param irsense Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRSENSE_RETVAL irsense_init ( irsense_t *ctx, irsense_cfg_t *cfg );

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
void irsense_generic_write ( irsense_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void irsense_generic_read ( irsense_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write the byte of data function.
 *
 * 
 * @param ctx          Click object.
 * @param reg_address  Register address.
 * @param write_data   Byte of data to write.
 *
 * @description Function write the 8-bit data to the
 * target 8-bit register address of AK9750 sensor on IR Sense click board.
 */
 void irsense_write_byte ( irsense_t *ctx, uint8_t reg_address, uint8_t write_data );

 /**
 * @brief Generic read the byte of data function.
 *
 * 
 * @param ctx          Click object.
 * @param reg_address  Register address.
 *
 * @description Function read the 8-bit data from the
 * target 8-bit register address of AK9750 sensor on IR Sense click board.
 */
 uint8_t irsense_read_byte ( irsense_t *ctx, uint8_t reg_address );

 /**
 * @brief Generic read 16-bit of data function.
 *
 * 
 * @param ctx             Click object.
 * @param reg_address_low Low register address.
 *
 * @description Function read the 16-bit data from the
 * two target 8-bit register address of AK9750 sensor on IR Sense click board.
 */
 uint16_t irsense_read_data ( irsense_t *ctx, uint8_t reg_address_low );

 /**
 * @brief Enable the sensor function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description  Function enable the sensor by set state of CS pin
 * of AK9750 sensor on IR Sense click board.
 */
void irsense_power_on ( irsense_t *ctx );

 /**
 * @brief Disable the sensor function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function disable the sensor by clear state of CS pin
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_power_off ( irsense_t *ctx );

 /**
 * @brief Get company code function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function get company code by read 8-bit data from the
 * target _IRSENSE_REG_WIA1 register address of AK9750 sensor on IR Sense click board.
 */
 uint8_t irsense_get_company_code ( irsense_t *ctx );

 /**
 * @brief Get device ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function get device ID by read 8-bit data from the
 * target IRSENSE_REG_WIA2 register address of AK9750 sensor on IR Sense click board.
 */
 uint8_t irsense_get_device_id ( irsense_t *ctx );

 /**
 * @brief Get interrupts activate or inactivate corresponding status value function.
 *
 * 
 * @param ctx          Click object.
 *
 * @return
 * 8-bit interrupts status value:
 * - [ bit7 : bit5 ] Reserved;
 * - [ bit4 ] The differential signals of two IR sensors (IR1 - IR3 )  are equal to or above the upper threshold levels :
 *    - 0 : The differential signals ( IR1 � IR3 ) are below the upper threshold levels.
 *    - 1 : The differential signals ( IR1 � IR3 ) are below the upper threshold levels.
 * - [ bit3 ] The differential signals of two IR sensors ( IR1 - IR3 ) are equal to or below the lower threshold levels :
 *    - 0 : The differential signals ( IR1 - IR3 ) are above the lower threshold levels.
 *    - 1 : The differential signals ( IR1 - IR3 ) are equal to or below the lower threshold levels.
 * - [ bit2 ] The differential signals of two IR sensors (IR2 - IR4 )  are equal to or above the upper threshold levels :
 *    - 0 : The differential signals ( IR2 � IR4 ) are below the upper threshold levels.
 *    - 1 : The differential signals ( IR2 � IR4 ) are below the upper threshold levels.
 * - [ bit1 ] The differential signals of two IR sensors ( IR2 - IR4 ) are equal to or below the lower threshold levels :
 *    - 0 : The differential signals ( IR2 - IR4 ) are above the lower threshold levels.
 *    - 1 : The differential signals ( IR2 - IR4 ) are equal to or below the lower threshold levels.
 * - [ bit0 ] Data Ready :
 *    - 0 : Normal state.
 *    - 1 : Data Ready.
 *
 *
 * @description Function get interrupts activate or inactivate corresponding status by read 8-bit data from the
 * target _IRSENSE_REG_INTST register address of AK9750 sensor on IR Sense click board.
 */
 uint8_t irsense_read_interrupt_status ( irsense_t *ctx );

 /**
 * @brief Get status value function.
 *
 * @param ctx          Click object.
 * 
 * @return
 * 8-bit status value:
 * - [ bit7 : bit2 ] Reserved;
 * - [ bit1 ]  Data Overrun :
 *    - 0 : Normal State.
 *    - 1 : Data Overrun.
 * - [ bit0 ] Data Ready :
 *    - 0 : Normal State.
 *    - 1 : Data Ready.
 *
 * @description Function get status value by read 8-bit data from the
 * target IRSENSE_REG_ST1 register address of AK9750 sensor on IR Sense click board.
 */
 uint8_t irsense_get_status ( irsense_t *ctx );

 /**
 * @brief Set configuration function.
 *
 * @param ctx          Click object.
 * @param registerValue
 * 8-bit interrupts status value:
 * - [ bit7 ] Reserved;
 * - [ bit6 ] Setting :
 *    - 0 :  Normal Mode.
 *    - 1 :  EEPROM Access Mode.
 * - [ bit5 : bit3 ] Digital Filter Cutoff Frequency (Fc) setting :
 *    - 0 : Frequency  0.3 Hz.
 *    - 1 : Frequency  0.6 Hz.
 *    - 2 : Frequency  1.1 Hz.
 *    - 3 : Frequency  2.2 Hz.
 *    - 4 : Frequency  4.4 Hz.
 *    - 5 : Frequency  8.8 Hz.
 *    - 6 : Be prohibited.
 *    - 7 : Be prohibited.
 * - [ bit2 : bit0 ] Mode setting :
 *    - 0 : Stand-by Mode.
 *    - 1 : EEPROM Access Mode.
 *    - 2 : Shingle Shot Mode.
 *    - 3 : Be prohibited.
 *    - 4 : Continuous Mode 0.
 *    - 5 : Continuous Mode 1.
 *    - 6 : Continuous Mode 2.
 *    - 7 : Continuous Mode 3.
 *
 * @description  Function set configuration by write 8-bit registerValue to the
 * target IRSENSE_REG_ECNTL1 register address of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_configuration ( irsense_t *ctx, uint8_t register_value );

 /**
 * @brief Set the mode function.
 *
 * @param ctx          Click object.
 * @param mode
 * 8-bit mode value [ bit2 : bit0 ] :
 *    - 0x00 : Stand-by Mode.
 *    - 0x01 : EEPROM Access Mode.
 *    - 0x02 : Shingle Shot Mode.
 *    - 0x03 : Be prohibited.
 *    - 0x04 : Continuous Mode 0.
 *    - 0x05 : Continuous Mode 1.
 *    - 0x06 : Continuous Mode 2.
 *    - 0x07 : Continuous Mode 3.
 *
 * @description Function set the mode by write 8-bit mode to the
 * target IRSENSE_REG_ECNTL1 register address of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_mode ( irsense_t *ctx, uint8_t mode );

 /**
 * @brief Set the cutoff frequency function.
 *
 * @param ctx          Click object. 
 * @param frequency
 * 8-bit mode value [ bit5 : bit3 ] :
 *    - 0x00 : Frequency  0.3 Hz.
 *    - 0x08 : Frequency  0.6 Hze.
 *    - 0x10 : Frequency  1.1 Hz.
 *    - 0x18 : Frequency  2.2 Hz.
 *    - 0x20 : Frequency  4.4 Hz.
 *    - 0x28 : Frequency  8.8 Hz.
 *    - 0x30 : Be prohibited.
 *    - 0x38 : Be prohibited.
 *
 * @description Function set the cutoff frequency by write 8-bit mode to the
 * target _IRSENSE_REG_ECNTL1 register address of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_cutoff_frequency ( irsense_t *ctx, uint8_t frequency );

 /**
 * @brief Checks to see if DRDY flag is set in the status register function.
 *
 * 
 * @param ctx          Click object.
 *
 * @return
 * Data Ready:
 *    - 0 : Normal State.
 *    - 1 : Data Ready.
 *
 * @description Function checks to see if DRDY flag is set in the status register by read DRDY bit from the
 * target IRSENSE_REG_ST1 register address of AK9750 sensor on IR Sense click board.
 */
 uint8_t irsense_check_available ( irsense_t *ctx );

 /**
 * @brief Checks to see if data overrun flag is set in the status register function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @return
 * Data Overrun:
 *    - 0 : Normal State.
 *    - 1 : Data Overrun.
 *
 *
 * @description Function checks to see if overrun flag is set in the status register by read overrun bit from the
 * target IRSENSE_REG_ST1 register address of AK9750 sensor on IR Sense click board.
 */
 uint8_t irsense_check_overrun ( irsense_t *ctx );

 /**
 * @brief Soft reset function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function soft reset by sets Soft Reset bit ( write 0x01 ) to the
 * target IRSENSE_REG_CNTL2 register address of AK9750 sensor on IR Sense click board.
 */
 void irsense_soft_reset ( irsense_t *ctx );

 /**
 * @brief Refresh by read dummy data function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function refresh by read dummy data by read data from the
 * target IRSENSE_REG_ST2 register address of AK9750 sensor on IR Sense click board.
 */
 void irsense_refresh ( irsense_t *ctx );

 /**
 * @brief Get value of sensor channel 1 function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @return
 * 16- bit signed channel 1 value
 *
 * @description Function get value of sensor channel 1 by read value from the
 * two target IRSENSE_REG_IR1_LOW and IRSENSE_REG_IR1_HIGH
 * register address of AK9750 sensor on IR Sense click board.
 */
 int16_t irsense_get_ir1 ( irsense_t *ctx );

 /**
 * @brief Get value of sensor channel 2 function.
 *
 * 
 * @param ctx          Click object.
 *
 * @return
 * 16- bit signed channel 2 value
 *
 * @description Function get value of sensor channel 2 by read value from the
 * two target IRSENSE_REG_IR2_LOW and IRSENSE_REG_IR2_HIGH
 * register address of AK9750 sensor on IR Sense click board.
 */
 int16_t irsense_get_ir2 ( irsense_t *ctx );

 /**
 * @brief Get value of sensor channel 3 function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @return
 * 16- bit signed channel 3 value
 *
 * @description Function get value of sensor channel 3 by read value from the
 * two target IRSENSE_REG_IR3_LOW and IRSENSE_REG_IR3_HIGH
 * register address of AK9750 sensor on IR Sense click board.
 */
 int16_t irsense_get_ir3 ( irsense_t *ctx );

 /**
 * @brief Get value of sensor channel 4 function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @return
 * 16- bit signed channel 4 value
 *
 * @description Function get value of sensor channel 4 by read value from the
 * two target IRSENSE_REG_IR4_LOW and IRSENSE_REG_IR4_HIGH
 * register address of AK9750 sensor on IR Sense click board.
 */
 int16_t irsense_get_ir4 ( irsense_t *ctx );

 /**
 * @brief Get value of sensor all channels function.
 *
 * 
 * @param ctx          Click object.
 * @param ir_data      IR data (1,2,3,4).
 *
 * @description Function get value of sensor all channels by read values from the
 * target IRSENSE_REG_IR1_LOW, IRSENSE_REG_IR1_HIGH,
 * IRSENSE_REG_IR1_LOW, IRSENSE_REG_IR1_HIGH,
 * IRSENSE_REG_IR2_LOW, IRSENSE_REG_IR2_HIGH,
 * IRSENSE_REG_IR3_LOW, IRSENSE_REG_IR3_HIGH,
 * IRSENSE_REG_IR4_LOW and IRSENSE_REG_IR4_HIGH
 * register address of AK9750 sensor on IR Sense click board.
 */
 void irsense_get_ir_sense ( irsense_t *ctx, irsense_ir_data_t *ir_data );

 /**
 * @brief Get the temperature in degrees Celsius function.
 *
 * 
 * @param ctx          Click object.
 *
 * @return
 * float temperature value in degrees Celsius [ �C ]
 *
 * @description Function get the temperature float value by read the measurement data from the
 * two target IRSENSE_REG_TMP_LOW and IRSENSE_REG_TMP_HIGH
 * register address of AK9750 sensor on IR Sense click board
 * calculate temperature value to degree Celsius [ �C ].
 */
 float irsense_get_temperature ( irsense_t *ctx );

 /**
 * @brief Get the temperature in Fahrenheit degrees function.
 *
 * 
 * @param ctx          Click object.
 *
 * @return
 * float temperature value in Fahrenheit degrees [ �F ]
 *
 * @description  Function get the temperature float value by read the measurement data from the
 * two target IRSENSE_REG_TMP_LOW and IRSENSE_REG_TMP_HIGH
 * register address of AK9750 sensor on IR Sense click board
 * calculate temperature value to Fahrenheit degrees [ �F ].
 */
 float irsense_get_temperature_f ( irsense_t *ctx );

 /**
 * @brief Set high or low threshold for channel 2 and channel 4 ( Ir2-Ir4 ) function.
 *
 * 
 * @param ctx          Click object.
 * @param value        8-bit threshold value for channel 2 and channel 4.
 *
 * @description Function set high or low threshold level setting for channel 2 and channel 4 ( Ir2-Ir4 )
 * by write 8-bit value to the two target IRSENSE_REG_ETH24H_LOW and IRSENSE_REG_ETH24H_HIGH
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_threshold_ir2_ir4 ( irsense_t *ctx, uint8_t value );

 /**
 * @brief Get threshold value for channel 2 and channel 4 ( Ir2-Ir4 ) function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @return
 * 16-bit threshold value for channel 2 and channel 4
 *
 *
 * @description Function get threshold level setting value for channel 2 and channel 4 ( Ir2-Ir4 )
 * by read 16-bit value to the two target IRSENSE_REG_ETH24H_LOW and IRSENSE_REG_ETH24H_HIGH
 * of AK9750 sensor on IR Sense click board.
 */
 uint16_t irsense_get_threshold_ir2_ir4 ( irsense_t *ctx );

 /**
 * @brief Set high or low EEPROM threshold for channel 2 and channel 4 ( Ir2-Ir4 ) function.
 *
 * 
 * @param ctx          Click object.
 * @param value        8-bit threshold value for channel 2 and channel 4.
 *
 * @description Function set high or low EEPROM threshold level setting for channel 2 and channel 4 ( Ir2-Ir4 )
 * by write 8-bit value to the two target _IRSENSE_REG_ETH24H_LOW and _IRSENSE_REG_ETH24H_HIGH
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_threshold_eeprom_ir2_ir4 ( irsense_t *ctx, uint8_t value );

 /**
 * @brief Set high or low threshold for channel 1 and channel 3 ( Ir1-Ir3 ) function.
 *
 * 
 * @param ctx          Click object.
 * @param value        8-bit threshold value for channel 1 and channel 3.
 *
 * @description Function set high or low threshold level setting for channel 1 and channel 3 ( Ir1-Ir3 )
 * by write 8-bit value to the two target _IRSENSE_REG_ETH13H_LOW and _IRSENSE_REG_ETH13H_HIGH
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_threshold_ir1_ir3 ( irsense_t *ctx, uint8_t value );

 /**
 * @brief Get threshold value for channel 1 and channel 3 ( Ir1-Ir3 ) function.
 *
 * 
 * @param ctx          Click object.
 *
 * @return
 * 16-bit threshold value for channel 1 and channel 3
 *
 * @description Function get threshold level setting value for channel 1 and channel 3 ( Ir1-Ir3 )
 * by read 16-bit value to the two target _IRSENSE_REG_ETH13H_LOW and _IRSENSE_REG_ETH13H_HIGH
 * of AK9750 sensor on IR Sense click board.
 */
 uint16_t irsense_get_threshold_ir1_ir3 ( irsense_t *ctx );

 /**
 * @brief Set high or low EEPROM threshold for channel 1 and channel 3 ( Ir1-Ir3 ) function.
 *
 * 
 * @param ctx          Click object.
 * @param value        8-bit threshold value for channel 1 and channel 3.
 *
 * @description Function set high or low EEPROM threshold level setting for channel 1 and channel 3 ( Ir1-Ir3 )
 * by write 8-bit value to the two target _IRSENSE_REG_ETH13H_LOW and _IRSENSE_REG_ETH13H_HIGH
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_threshold_eeprom_ir1_ir3( irsense_t *ctx, uint8_t value );

 /**
 * @brief Get threshold value for all channels function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description Function get threshold level setting value for all channels
 * by read all threshold level setting value from all target registers
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_read_threshold ( irsense_t *ctx, irsense_reg_t *reg );

 /**
 * @brief Get threshold EEPROM value for all channels function.
 *
 * 
 * @param ctx          Click object.
 * @param eeth24h      pointer to 16-bit (  High Ir2-Ir4 ) EEPROM value.
 * @param eeth24l      pointer to 16-bit ( Low Ir2-Ir4 ) EEPROM value.
 * @param eeth13h      pointer to 16-bit ( High Ir1-Ir3 ) EEPROM value.
 * @param eeth13l      pointer to 16-bit ( Low Ir1-Ir3 ) EEPROM value.
 *
 *
 * @description Function get threshold EEPROM level setting value for all channels
 * by read all threshold EEPROM level setting value from all target registers
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_read_threshold_eeprom ( irsense_t *ctx, irsense_eeprom_t *eeprom );

 /**
 * @brief Set hysteresis setting of threshold level for channel 2 and channel 4 ( Ir2-Ir4 ) function.
 *
 * 
 * @param ctx          Click object.
 * @param value        8-bit hysteresis setting of threshold level value for channel 2 and channel 4.
 *
 * @description Function set hysteresis setting of threshold level value for channel 2 and channel 4 ( Ir2-Ir4 )
 * by write 8-bit hysteresis value to the target IRSENSE_REG_EHYS24
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_hysteresis_ir2_ir4 ( irsense_t *ctx, uint8_t value );

 /**
 * @brief Set hysteresis EEPROM setting of threshold level for channel 2 and channel 4 ( Ir2-Ir4 ) function.
 *
 * 
 * @param ctx          Click object.
 * @param value        8-bit hysteresis setting of threshold level value for channel 2 and channel 4.
 *
 * @description Function set hysteresis EEPROM setting of threshold level value for channel 2 and channel 4 ( Ir2-Ir4 )
 * by write 8-bit hysteresis EEPROM value to the target IRSENSE_EEPROM_MAP_EHYS24
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_hysteresis_eeprom_ir2_ir4 ( irsense_t *ctx, uint8_t value );

 /**
 * @brief Set hysteresis setting of threshold level for channel 1 and channel 3 ( Ir1-Ir3 ) function.
 *
 * 
 * @param ctx          Click object.
 * @param value        8-bit hysteresis setting of threshold level value for channel 1 and channel 3.
 *
 * @description Function set hysteresis setting of threshold level value for channel 1 and channel 3 ( Ir1-Ir3 )
 * by write 8-bit hysteresis value to the target IRSENSE_REG_EHYS13
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_hysteresis_ir1_ir3 ( irsense_t *ctx, uint8_t value );

 /**
 * @brief Set hysteresis EEPROM setting of threshold level for channel 1 and channel 3 ( Ir1-Ir3 ) function.
 *
 * 
 * @param ctx          Click object.
 * @param value        8-bit hysteresis setting of threshold level value for channel 1 and channel 3.        Number of the bytes to be read
 *
 * @description Function set hysteresis EEPROM setting of threshold level value for channel 1 and channel 3 ( Ir1-Ir3 )
 * by write 8-bit hysteresis EEPROM value to the target IRSENSE_EEPROM_MAP_EHYS13
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_hysteresis_eeprom_ir1_ir3 (irsense_t *ctx, uint8_t value );

  /**
 * @brief Get Hysteresis value for all channes function.
 *
 * 
 * @param ctx          Click object.
 * @param ehys24       pointer to 8-bit ( Ir2-Ir4 ) hysteresis setting of threshold level value.
 * @param ehys13       pointer to 8-bit ( Ir1-Ir3 ) hysteresis setting of threshold level value.
 *
 * @description  Function get hysteresis setting of threshold level value for all channels
 * by read all hysteresis setting of threshold level value from all target registers
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_read_hysteresis ( irsense_t *ctx, uint8_t *ehys24, uint8_t *ehys13 );

 /**
 * @brief Get Hysteresis EEPROM value for all channes function.
 *
 * 
 * @param ctx          Click object.
 * @param eehys24      pointer to 8-bit ( Ir2-Ir4 ) hysteresis EEPROM setting of threshold level value.
 * @param eehys13      pointer to 8-bit ( Ir1-Ir3 ) hysteresis EEPROM setting of threshold level value.
 *
 * @description Function get hysteresis EEPROM setting of threshold level value for all channels
 * by read all hysteresis EEPROM setting of threshold level value from all target registers
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_read_hysteresis_eeprom ( irsense_t *ctx, uint8_t *eehys24, uint8_t *eehys13 );

  /**
 * @brief Sets interrupts activate or inactivate corresponding function.
 *
 * 
 * @param ctx          Click object.
 * @param eint         Enable interrupt.
 *
 * @description Function sets interrupts activate or inactivate corresponding
 * by write interrupts activate value to the target IRSENSE_REG_EINTEN
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_set_interrupts_reg ( irsense_t *ctx, irsense_eint_t *eint );

/**
 * @brief Sets interrupts source settings function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function sets interrupts activate or inactivate corresponding
 * by write activate data ready interrupt setting bit to the target IRSENSE_REG_EINTEN
 * of AK9750 sensor on IR Sense click board.
 */
 void irsense_enable_data_ready_interrupt ( irsense_t *ctx );  

 /**
 * @brief Check state of INT pin function.
 *
 * 
 * @param ctx          Click object.
 *
 * @return
 * state of INT pin :
 *    - 0 : Interrupt Disable.
 *    - 1 : Interrupt Enable.
 *
 * @description Function check state of INT pin
 * of AK9750 sensor on IR Sense click board.
 */
 uint8_t irsense_check_int_states ( irsense_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _IRSENSE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
