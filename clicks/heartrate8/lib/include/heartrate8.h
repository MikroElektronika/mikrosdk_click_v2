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
 * \brief This file contains API for Heart Rate 8 Click driver.
 *
 * \addtogroup heartrate8 Heart Rate 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HEARTRATE8_H
#define HEARTRATE8_H

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
#define HEARTRATE8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HEARTRATE8_RETVAL  uint8_t

#define HEARTRATE8_OK           0x00
#define HEARTRATE8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address Device address
 * \{
 */
#define HEARTRATE8_SLAVE_ADDR                         0x5B
/** \} */

/**
 * \defgroup register_address Register addresses
 * \{
 */
#define HEARTRATE8_MANUFACT_ID_REG                    0x0F
#define HEARTRATE8_PART_ID_REG                        0x10
#define HEARTRATE8_RESET_REG                          0x40
#define HEARTRATE8_MEAS_CTRL1_REG                     0x41
#define HEARTRATE8_MEAS_CTRL2_REG                     0x42
#define HEARTRATE8_MEAS_CTRL3_REG                     0x43
#define HEARTRATE8_MEAS_CTRL4_LSB_REG                 0x44
#define HEARTRATE8_MEAS_CTRL4_MSB_REG                 0x45
#define HEARTRATE8_MEAS_CTRL5_REG                     0x46
#define HEARTRATE8_MEAS_START_REG                     0x47
#define HEARTRATE8_MEAS_SYNC_REG                      0x48
#define HEARTRATE8_FIFO_LEV_REG                       0x4B
#define HEARTRATE8_FIFO_DATA0_LSB_REG                 0x4C
#define HEARTRATE8_FIFO_DATA0_MSB_REG                 0x4D
#define HEARTRATE8_FIFO_DATA1_LSB_REG                 0x4E
#define HEARTRATE8_FIFO_DATA1_MSB_REG                 0x4F
#define HEARTRATE8_IRDATA_LEDOFF_LSB_REG              0x50
#define HEARTRATE8_IRDATA_LEDOFF_MSB_REG              0x51
#define HEARTRATE8_IRDATA_LEDON_LSB_REG               0x52
#define HEARTRATE8_IRDATA_LEDON_MSB_REG               0x53
#define HEARTRATE8_GDATA_LEDOFF_LSB_REG               0x54
#define HEARTRATE8_GDATA_LEDOFF_MSB_REG               0x55
#define HEARTRATE8_GDATA_LEDON_LSB_REG                0x56
#define HEARTRATE8_GDATA_LEDON_MSB_REG                0x57
#define HEARTRATE8_INT_CLEAR_REG                      0x58
/** \} */

/**
 * \defgroup register_settings Register settings and commands
 * \{
 */
#define HEARTRATE8_RESET_CMD                          0x80
#define HEARTRATE8_OSC_ACTIVE                         0x80
#define HEARTRATE8_GREEN_MEAS_MODE                    0x00
#define HEARTRATE8_IR_MEAS_MODE                       0x10
#define HEARTRATE8_32HZ_MEAS_MODE                     0x00
#define HEARTRATE8_128HZ_MEAS_MODE                    0x01
#define HEARTRATE8_64HZ_MEAS_MODE                     0x02
#define HEARTRATE8_256HZ_MEAS_MODE                    0x03
#define HEARTRATE8_1024HZ_MEAS_MODE                   0x05
#define HEARTRATE8_NON_SYNC_MEAS_MODE                 0x06
#define HEARTRATE8_SINGLE_MEAS_MODE                   0x07
#define HEARTRATE8_LEDS_PULSED                        0x00
#define HEARTRATE8_LED1_ON                            0x40
#define HEARTRATE8_LED2_ON                            0x80
#define HEARTRATE8_LEDS_ON                            0xC0
#define HEARTRATE8_LED3_OFF                           0x00
#define HEARTRATE8_LED3_ON                            0x80
#define HEARTRATE8_STOP_EMISSION                      0x00
#define HEARTRATE8_LED_CURR_1MA                       0x01
#define HEARTRATE8_LED_CURR_2MA                       0x02
#define HEARTRATE8_LED_CURR_5MA                       0x05
#define HEARTRATE8_LED_CURR_10MA                      0x0A
#define HEARTRATE8_LED_CURR_15MA                      0x0F
#define HEARTRATE8_LED_CURR_20MA                      0x14
#define HEARTRATE8_LED_CURR_25MA                      0x19
#define HEARTRATE8_LED_CURR_30MA                      0x1E
#define HEARTRATE8_LED_CURR_35MA                      0x23
#define HEARTRATE8_LED_CURR_40MA                      0x28
#define HEARTRATE8_LED_CURR_45MA                      0x2D
#define HEARTRATE8_LED_CURR_50MA                      0x32
#define HEARTRATE8_LED_CURR_55MA                      0x37
#define HEARTRATE8_LED_CURR_60MA                      0x3C
#define HEARTRATE8_LED_CURR_63MA                      0x3F
#define HEARTRATE8_INT_DISABLE                        0x00
#define HEARTRATE8_INT_WATER_MARK_FIFO                0x01
#define HEARTRATE8_INT_IR_THRESH                      0x02
#define HEARTRATE8_INT_MEAS_COMPLET                   0x03
#define HEARTRATE8_MEAS_START_CMD                     0x01
#define HEARTRATE8_MEAS_SYNC_CMD                      0x01
/** \} */

/**
 * \defgroup data_select Data selection for Get function
 * \{
 */
#define HEARTRATE8_FIFO_DATA_GET                      0x00
#define HEARTRATE8_IR_DATA_GET                        0x01
#define HEARTRATE8_GREEN_DATA_GET                     0x02
/** \} */

/**
 * \defgroup ret_val Function returned values
 * \{
 */
#define HEARTRATE8_OK                                 0x00
#define HEARTRATE8_WRONG_ADDR                         0x01
#define HEARTRATE8_NBYTES_RANGE_ERROR                 0x02
#define HEARTRATE8_DATA_SEL_ERROR                     0x03
#define HEARTRATE8_INT_ACTIVE                         0x00
#define HEARTRATE8_INT_INACTIVE                       0x01
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

} heartrate8_t;

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

} heartrate8_cfg_t;

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
void heartrate8_cfg_setup ( heartrate8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HEARTRATE8_RETVAL heartrate8_init ( heartrate8_t *ctx, heartrate8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for HeartRate8 click.
 */
void heartrate8_default_cfg ( heartrate8_t *ctx );

/**
 * @brief Generic Single Byte Write function
 *
 * @param ctx  Click object.
 * @param reg_addr  Address where data be written
 * @param data_in  Data to be written
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * @description Function writes one byte to the register.
 */
uint8_t heartrate8_write_single_byte ( heartrate8_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Generic Bytes Write function
 *
 * @param ctx  Click object.
 * @param start_addr  Address from which data writing be started
 * @param data_in  Memory which from data be written
 * @param n_bytes  Number of bytes to be written
 *
 * @returns 0 - OK, 1 - Wrong address, 2 - Number of bytes is out of range
 *
 * @description Function writes the desired number of bytes to the registers.
 */
uint8_t heartrate8_write_bytes ( heartrate8_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief Generic Read function
 *
 * @param ctx  Click object.
 * @param start_addr  Address from which data reading be started
 * @param data_out  Memory where read data be stored
 * @param n_bytes  Number of bytes to be read
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * @description Function reads the desired number of bytes from the registers.
 */
uint8_t heartrate8_read_bytes ( heartrate8_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Measurement Start function
 *
 * @param ctx  Click object.
 * @description Function starts one measurement cycle.
 */
void heartrate8_start_measure ( heartrate8_t *ctx );

/**
 * @brief Reset function
 *
 * @param ctx  Click object.
 * @description Function performs the device reset.
 * @note The device reset must be performed when configurations are changed.
 */
void heartrate8_reset ( heartrate8_t *ctx );

/**
 * @brief Measurement Synchronization function
 *
 * @param ctx  Click object.
 * @description Function performs the measurement synchronization.
 * @note In Synchronized Measurement Mode adjust LED emitting frequency and output data rate by synchronizing 
 *       with MEAS_SYNC received interval. After receiving MEAS_SYNC, the measurements for a set number of times are performed.
 */
void heartrate8_meas_sync ( heartrate8_t *ctx );

/**
 * @brief Interrupt Clear function
 *
 * @param ctx  Click object.
 * @returns Byte from the INT_CLEAR register.
 *
 * @description Function clears interrupt flag on the INT pin.
 */
uint8_t heartrate8_int_clear ( heartrate8_t *ctx );

/**
 * @brief Interrupt Check function
 *
 * @param ctx  Click object.
 * @returns 0 - Interrupt is occured, 1 - Interrupt is not occured
 *
 * @description Function checks INT pin, is interrupt occured or not.
 */
uint8_t heartrate8_check_int ( heartrate8_t *ctx );

/**
 * @brief Data Get function
 *
 * @param ctx  Click object.
 * @param data_select  Determines which data registers be read (0 - FIFO, 1 - IR, 2 - GREEN Data)
 * @param led_out_on  Memory where LED ON Data be stored
 * @param led_out_off  Memory where LED OFF Data be stored
 *
 * @returns 0 - OK, 3 - Wrong data selection
 *
 * @description Function gets the selected data from the determined LED Data registers.
 */
uint8_t heartrate8_get_data ( heartrate8_t *ctx, uint8_t data_select, uint16_t *led_out_on, uint16_t *led_out_off );

#ifdef __cplusplus
}
#endif
#endif  // _HEARTRATE8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
