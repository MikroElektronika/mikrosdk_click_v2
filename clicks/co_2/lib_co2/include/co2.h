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
 * \brief This file contains API for CO 2 Click driver.
 *
 * \addtogroup co2 CO 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CO2_H
#define CO2_H

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
#define CO2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CO2_RETVAL  uint8_t

#define CO2_OK           0x00
#define CO2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define CO2_STATUS_REG    0x00
#define CO2_LOCK_REG    0x01
#define CO2_TIACN_REG    0x10
#define CO2_REFCN_REG    0x11
#define CO2_MODECN_REG    0x12
/** \} */

/**
 * \defgroup modes Modes
 * \{
 */
#define CO2_WRITE_MODE    0x00
#define CO2_READ_ONLY_MODE    0x01
/** \} */

/**
 * \defgroup resolution Resolution
 * \{
 */
#define CO2_EXT_TIA_RES    0x00
#define CO2_2750_OHM_TIA_RES    0x04
#define CO2_3500_OHM_TIA_RES    0x08
#define CO2_7K_OHM_TIA_RES    0x0C
#define CO2_14K_OHM_TIA_RES    0x10
#define CO2_35K_OHM_TIA_RES    0x14
#define CO2_120K_OHM_TIA_RES    0x18
#define CO2_350K_OHM_TIA_RES    0x1C
#define CO2_10_OHM_LOAD_RES    0x00
#define CO2_33_OHM_LOAD_RES    0x01
#define CO2_50_OHM_LOAD_RES    0x02
#define CO2_100_OHM_LOAD_RES    0x03
/** \} */

/**
 * \defgroup measurement_values Measurement Values
 * \{
 */
#define CO2_VREF_INT    0x00
#define CO2_VREF_EXT    0x80
#define CO2_20_PERCENTS_INT_ZERO    0x00
#define CO2_50_PERCENTS_INT_ZERO    0x20
#define CO2_67_PERCENTS_INT_ZERO    0x40
#define CO2_INT_ZERO_BYPASSED    0x60
#define CO2_BIAS_POL_NEGATIVE    0x00
#define CO2_BIAS_POL_POSITIVE    0x10
#define CO2_0_PERCENTS_BIAS    0x00
#define CO2_1_PERCENT_BIAS    0x01
#define CO2_2_PERCENTS_BIAS    0x02
#define CO2_4_PERCENTS_BIAS    0x03
#define CO2_6_PERCENTS_BIAS    0x04
#define CO2_8_PERCENTS_BIAS    0x05
#define CO2_10_PERCENTS_BIAS    0x06
#define CO2_12_PERCENTS_BIAS    0x07
#define CO2_14_PERCENTS_BIAS    0x08
#define CO2_16_PERCENTS_BIAS    0x09
#define CO2_18_PERCENTS_BIAS    0x0A
#define CO2_20_PERCENTS_BIAS    0x0B
#define CO2_22_PERCENTS_BIAS    0x0C
#define CO2_24_PERCENTS_BIAS    0x0D
/** \} */

/**
 * \defgroup on_off_modes On/Off Modes
 * \{
 */
#define CO2_FET_DIS    0x00
#define CO2_FET_EN    0x80
#define CO2_DEEP_SLEEP_MODE    0x00
#define CO2_2_LEAD_MODE    0x01
#define CO2_STANDBY_MODE    0x02
#define CO2_3_LEAD_MODE    0x03
#define CO2_TEMP_MODE_TIA_OFF    0x06
#define CO2_TEMP_MODE_TIA_ON    0x07
/** \} */

/**
 * \defgroup enable_disable Enable/Disable
 * \{
 */
#define CO2_DEVICE_EN    0x00
#define CO2_DEVICE_DIS    0x01
/** \} */

/**
 * \defgroup adc_addr ADC Address
 * \{
 */
#define ADC_DEVICE_ADDR    0x4D
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

    // Input pins 

    digital_in_t an;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} co2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t rst;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} co2_cfg_t;

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
void co2_cfg_setup ( co2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param co2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CO2_RETVAL co2_init ( co2_t *ctx, co2_cfg_t *cfg );

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
uint8_t co2_generic_write ( co2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
uint8_t co2_generic_read ( co2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 *
 * @description Function waits until I2C is ready for the next command.
 */
void co2_wait_i2c_ready ( co2_t *ctx );

/**
 * @brief Device Enable function
 *
 * @param ctx          Click object.
 * @param state        0 - enable, value different from 0 - disable
 *
 * @description Function puts the device to enabled or to disabled state.
 */
void co2_enable( co2_t *ctx, uint8_t state );

/**
 * @brief Read ADC Data function
 *
 * @param ctx        Click object.
 * @param data_out   Buffer where the converted data be stored
 *
 * @description Function reads the converted data (CO) from the 12-bit AD converter.
 */
void co2_read_adc( co2_t *ctx, uint16_t *data_out );

/**
 * @brief Get CO Data function
 *  
 * @param ctx        Click object.
 * @param co_data   Memory where CO data from the device be stored
 *
 * @description Function reads the CO converted data and calculates this value to the ppm.
 */
void co2_get_co2_ppm( co2_t *ctx, float *co2_data );

#ifdef __cplusplus
}
#endif
#endif  // _CO2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
