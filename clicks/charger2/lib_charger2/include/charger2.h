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
 * \brief This file contains API for Charger 2 Click driver.
 *
 * \addtogroup charger2 Charger 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CHARGER2_H
#define CHARGER2_H

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
#define CHARGER2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CHARGER2_RETVAL  uint8_t

#define CHARGER2_OK           0x00
#define CHARGER2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup r_shunt R Shunt
 * \{
 */
#define  R_SHUNT                          0.05
/** \} */

/**
 * \defgroup reg Reg
 * \{
 */
#define CHARGER2_REG_MODE                 0x00
#define CHARGER2_REG_CONTROL              0x01
#define CHARGER2_REG_CHARGE_LOW           0x02
#define CHARGER2_REG_CHARGE_HIGH          0x03
#define CHARGER2_REG_COUNTER_LOW          0x04
#define CHARGER2_REG_COUNTER_HIGH         0x05
#define CHARGER2_REG_CURRENT_LOW          0x06
#define CHARGER2_REG_CURRENT_HIGH         0x07
#define CHARGER2_REG_VOLTAGE_LOW          0x08
#define CHARGER2_REG_VOLTAGE_HIGH         0x09
#define CHARGER2_REG_TEMPERATURE_LOW      0x0A
#define CHARGER2_REG_TEMPERATURE_HIGH     0x0B
#define CHARGER2_REG_ID0                  0x18
#define CHARGER2_REG_ID1                  0x19
#define CHARGER2_REG_ID2                  0x1A
#define CHARGER2_REG_ID3                  0x1B
#define CHARGER2_REG_ID4                  0x1C
#define CHARGER2_REG_ID5                  0x1D
#define CHARGER2_REG_ID6                  0x1E
#define CHARGER2_REG_ID7                  0x1F
#define CHARGER2_REG_RAM0                 0x20
#define CHARGER2_REG_RAM1                 0x21
#define CHARGER2_REG_RAM2                 0x22
#define CHARGER2_REG_RAM3                 0x23
#define CHARGER2_REG_RAM4                 0x24
#define CHARGER2_REG_RAM5                 0x25
#define CHARGER2_REG_RAM6                 0x26
#define CHARGER2_REG_RAM7                 0x27
#define CHARGER2_REG_RAM8                 0x28
#define CHARGER2_REG_RAM9                 0x29
#define CHARGER2_REG_RAM10                0x2A
#define CHARGER2_REG_RAM11                0x2B
#define CHARGER2_REG_RAM12                0x2C
#define CHARGER2_REG_RAM13                0x2D
#define CHARGER2_REG_RAM14                0x2E
#define CHARGER2_REG_RAM15                0x2F
#define CHARGER2_REG_RAM16                0x30
#define CHARGER2_REG_RAM17                0x31
#define CHARGER2_REG_RAM18                0x32
#define CHARGER2_REG_RAM19                0x33
#define CHARGER2_REG_RAM20                0x34
#define CHARGER2_REG_RAM21                0x35
#define CHARGER2_REG_RAM22                0x36
#define CHARGER2_REG_RAM23                0x37
#define CHARGER2_REG_RAM24                0x38
#define CHARGER2_REG_RAM25                0x39
#define CHARGER2_REG_RAM26                0x3A
#define CHARGER2_REG_RAM27                0x3B
#define CHARGER2_REG_RAM28                0x3C
#define CHARGER2_REG_RAM29                0x3D
#define CHARGER2_REG_RAM30                0x3E
#define CHARGER2_REG_RAM31                0x3F
/** \} */

/**
 * \defgroup resolution Resolution
 * \{
 */
#define CHARGER2_AUTO_DETECT              0x00
#define CHARGER2_EXTERNAL_CLOCK           0x01
#define CHARGER2_14_BITS_RESOLUTION       0x00
#define CHARGER2_13_BITS_RESOLUTION       0x02
#define CHARGER2_12_BITS_RESOLUTION       0x04
#define CHARGER2_CALIBRATE_ADC            0x08
#define CHARGER2_STANDBY_MODE             0x00
#define CHARGER2_OPERATING_MODE           0x10
/** \} */

/**
 * \defgroup resolution Resolution
 * \{
 */
#define CHARGER2_IO0_OUTPUT_LOW                     0x00
#define CHARGER2_IO0_OUTPUT_OPEN                    0x01
#define CHARGER2_RESET_CHARGE_ACCUM_AND_COUNTER     0x02
#define CHARGER2_RELEASE_SOFT_RESET                 0x00
#define CHARGER2_ASSERT_SOFT_RESET                  0x10
/** \} */

/**
 * \defgroup resolution Resolution
 * \{
 */
#define CHARGER2_RESET_COUNTER_MODE                 0x00
#define CHARGER2_SOFT_RESET_MODE                    0x01
#define CHARGER2_CURRENT_CYCLE_CHECK                0x00
#define CHARGER2_VOLTAGE_TEMP_CYCLE_CHECK           0x01
#define CHARGER2_GAS_GAUGE_CHARGE_DATA              0x00
#define CHARGER2_CONV_NUMBER                        0x01
#define CHARGER2_SHUNT_VOLTAGE                      0x02
#define CHARGER2_BATTERY_VOLTAGE                    0x03
#define CHARGER2_TEMPERATURE                        0x04
#define CHARGER2_BATTERY_CURRENT                    0x05
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

    uint8_t unit_mode;

} charger2_t;

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

} charger2_cfg_t;

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
void charger2_cfg_setup ( charger2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param charger2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CHARGER2_RETVAL charger2_init ( charger2_t *ctx, charger2_cfg_t *cfg );

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
void charger2_generic_write ( charger2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void charger2_generic_read ( charger2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write reg function.
 *
 * @param ctx                 Click object.
 * @param register_address    Address where data be written.
 * @param transfer_data       Data to be written.
 *
 * @description This function writes one byte data to the register.
 */
uint8_t charger2_write_reg ( charger2_t *ctx, uint8_t register_address, uint8_t transfer_data );

/**
 * @brief Read reg function.
 *
 * @param ctx                 Click object.
 * @param register_address    Address which from data be read.
 * @param value_out           Buffer where data be stored.
 * @param n_bytes             Number of bytes to be read.
 *
 * @description This function reads the desired number of data bytes.
 */
uint8_t charger2_read_reg ( charger2_t *ctx, uint8_t register_address, uint8_t *value_out, uint8_t n_bytes );

/**
 * @brief Data Read function.
 *
 * @param ctx          Click object.
 * @param data_mode    Determines the data to be read.
 * @param data_out     Buffer where data be stored.
 *
 * @description This function reads the desired data from data registers and converts this data to the appropriate unit.
 */
uint8_t charger2_read_data ( charger2_t *ctx, uint8_t data_mode, uint32_t *data_out );

/**
 * @brief Reset function.
 *
 * @param ctx          Click object.
 * @param reset_mode   Determines which reset be performed, for counter and accumulator (0), or software reset (1).
 *
 * @description This function performs the counter and accumulator reset or the software reset.
 */
uint8_t charger2_reset ( charger2_t *ctx, uint8_t reset_mode );

/**
 * @brief Conversion Cycle Check function.
 *
 * @param ctx           Click object.
 * @param conv_mode     Determines which conversion cycle be checked, for current (0), or for voltage and temperature (1).
 *
 * @description This function checks is conversion cycle for battery current, or for battery voltage and temperature, finished,
 * and if is not, waits until one of this conversions be finished.
 */
uint8_t charger2_check_conv_cycle( charger2_t *ctx, uint8_t conv_mode );

#ifdef __cplusplus
}
#endif
#endif  // _CHARGER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
