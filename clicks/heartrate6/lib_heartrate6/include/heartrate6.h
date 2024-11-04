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
 * \brief This file contains API for Heart rate 6 Click driver.
 *
 * \addtogroup heartrate6 Heart rate 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HEARTRATE6_H
#define HEARTRATE6_H

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
#define HEARTRATE6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HEARTRATE6_RETVAL  uint8_t

#define HEARTRATE6_OK           0x00
#define HEARTRATE6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address Device address
 * \{
 */
#define HEARTRATE6_SLAVE_ADDR               0x5B
/** \} */

/**
 * \defgroup reg_address Register addresses
 * \{
 */
#define HEARTRATE6_MANUFACT_ID_REG1         0x0F
#define HEARTRATE6_MANUFACT_ID_REG2         0x92
#define HEARTRATE6_PART_ID_REG              0x10
#define HEARTRATE6_RESET_REG                0x40
#define HEARTRATE6_MEAS_CTRL1_REG           0x41
#define HEARTRATE6_MEAS_CTRL2_REG           0x42
#define HEARTRATE6_MEAS_START_REG           0x43
#define HEARTRATE6_DATA_LEDOFF_LSB_REG      0x54
#define HEARTRATE6_DATA_LEDOFF_MSB_REG      0x55
#define HEARTRATE6_DATA_LEDON_LSB_REG       0x56
#define HEARTRATE6_DATA_LEDON_MSB_REG       0x57
/** \} */

/**
 * \defgroup reg_settings Register settings
 * \{
 */
#define HEARTRATE6_RESET_CMD                0x80
#define HEARTRATE6_OSC_ACTIVE               0x80
#define HEARTRATE6_LED_FREQ_128HZ           0x00
#define HEARTRATE6_LED_FREQ_64HZ            0x04
#define HEARTRATE6_DATAREAD_FREQ_64HZ       0x01
#define HEARTRATE6_DATAREAD_FREQ_32HZ       0x02
#define HEARTRATE6_LEDS_PULSED              0x00
#define HEARTRATE6_LED1_CONST_LED2_PULSED   0x40
#define HEARTRATE6_LED1_PULSED_LED2_CONST   0x80
#define HEARTRATE6_LEDS_CONST               0xC0
#define HEARTRATE6_LED_TIME_300MICROSEC     0x00
#define HEARTRATE6_LED_TIME_600MICROSEC     0x20
#define HEARTRATE6_LED_CURR_0MA             0x00
#define HEARTRATE6_LED_CURR_1MA             0x08
#define HEARTRATE6_LED_CURR_2MA             0x09
#define HEARTRATE6_LED_CURR_3MA             0x0A
#define HEARTRATE6_LED_CURR_6MA             0x0B
#define HEARTRATE6_LED_CURR_10MA            0x0C
#define HEARTRATE6_LED_CURR_20MA            0x0D
#define HEARTRATE6_LED_CURR_30MA            0x0E
#define HEARTRATE6_LED_CURR_60MA            0x0F
#define HEARTRATE6_START_MEAS               0x01
/** \} */

/**
 * \defgroup ret_val Return values
 * \{
 */
#define HEARTRATE6_OK                       0x00
#define HEARTRATE6_WRONG_ADDR               0x01
#define HEARTRATE6_NBYTES_RANGE_ERROR       0x02
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

    float res;
    uint8_t wait_time;

} heartrate6_t;

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

} heartrate6_cfg_t;

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
void heartrate6_cfg_setup ( heartrate6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
HEARTRATE6_RETVAL heartrate6_init ( heartrate6_t *ctx, heartrate6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for HeartRate6 Click.
 */
void heartrate6_default_cfg ( heartrate6_t *ctx );

/**
 * @brief Single Byte Write function
 *
 * @param ctx  Click object.
 * @param reg_addr  Address where byte be written
 * @param data_in  Byte to be written
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * @description Function writes one byte to the register.
 */
uint8_t heartrate6_write_single_byte ( heartrate6_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Bytes Write function
 *
 * @param ctx  Click object.
 * @param start_addr  Start address where data be written
 * @param data_in  Memory which from data be written to registers
 * @param n_bytes  Number of bytes to be written
 *
 * @returns 0 - OK, 1 - Wrong address, 2 - Number of bytes is out of range
 *
 * @description Function writes the desired number of bytes to the registers.
 */
uint8_t heartrate6_write_bytes ( heartrate6_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief Generic Read function
 *
 * @param ctx  Click object.
 * @param start_addr  Start address which from data be read
 * @param data_out  Memory where data be stored
 * @param n_nytes  Number of bytes to be read
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * @description Function reads the desired number of bytes from the registers.
 */
uint8_t heartrate6_read_bytes( heartrate6_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Measurement Start function
 *
 * @param ctx  Click object.
 * @description Function starts measurement cycle.
 */
void heartrate6_start_measure ( heartrate6_t *ctx );

/**
 * @brief Reset function
 *
 * @param ctx  Click object.
 * @description Function performs the SW Reset.
 * @note When SW Reset is performed, the measurement cycle is stopped and configuration registers can be updated.
 */
void heartrate6_reset ( heartrate6_t *ctx );

/**
 * @brief Frequency Set function
 *
 * @param ctx  Click object.
 * @param freq_data  Settings for frequency control register
 *
 * @description Function sets the data reading frequency and the LED pulse frequency.
 * @note Data reading frequency directly determines the measurement time.
 */
void heartrate6_set_freq ( heartrate6_t *ctx, uint8_t freq_data );

/**
 * @brief Data Get function
 *
 * @param ctx  Click object.
 * @param led_off_data  Memory where LED OFF Data be stored
 * @param led_on_data  Memory where LED ON Data be stored
 *
 * @description Function reads the LED Data as 16bit unsigned value.
 */
void heartrate6_get_data ( heartrate6_t *ctx, uint16_t *led_off_data, uint16_t *led_on_data );

/**
 * @brief Wait measurement function
 *
 * @param ctx  Click object.
 *
 * @description Function delays program for a time specified in Click object wait_time field.
 */
void heartrate6_wait_measure( heartrate6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HEARTRATE6_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
