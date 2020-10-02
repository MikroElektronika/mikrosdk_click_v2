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
 * \brief This file contains API for NO 2 Click driver.
 *
 * \addtogroup no2 NO 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NO2_H
#define NO2_H

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
#define NO2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NO2_RETVAL  uint8_t

#define NO2_OK                              0x00
#define NO2_INIT_ERROR                      0xFF
/** \} */

/**
 * \defgroup registers  Registers
 * \{
 */
#define NO2_STATUS_REG                      0x00
#define NO2_LOCK_REG                        0x01
#define NO2_TIACN_REG                       0x10
#define NO2_REFCN_REG                       0x11
#define NO2_MODECN_REG                      0x12
/** \} */

/**
 * \defgroup write_read_mode  Write read mode
 * \{
 */ 
#define NO2_WRITE_MODE                      0x00
#define NO2_READ_ONLY_MODE                  0x01
/** \} */

/**
 * \defgroup res  Res
 * \{
 */ 
#define NO2_EXT_TIA_RES                     0x00
#define NO2_2750_OHM_TIA_RES                0x04
#define NO2_3500_OHM_TIA_RES                0x08
#define NO2_7K_OHM_TIA_RES                  0x0C
#define NO2_14K_OHM_TIA_RES                 0x10
#define NO2_35K_OHM_TIA_RES                 0x14
#define NO2_120K_OHM_TIA_RES                0x18
#define NO2_350K_OHM_TIA_RES                0x1C
#define NO2_10_OHM_LOAD_RES                 0x00
#define NO2_33_OHM_LOAD_RES                 0x01
#define NO2_50_OHM_LOAD_RES                 0x02
#define NO2_100_OHM_LOAD_RES                0x03
/** \} */

/**
 * \defgroup values Values
 * \{
 */
#define NO2_VREF_INT                        0x00
#define NO2_VREF_EXT                        0x80
#define NO2_20_PERCENTS_INT_ZERO            0x00
#define NO2_50_PERCENTS_INT_ZERO            0x20
#define NO2_67_PERCENTS_INT_ZERO            0x40
#define NO2_INT_ZERO_BYPASSED               0x60
#define NO2_BIAS_POL_NEGATIVE               0x00
#define NO2_BIAS_POL_POSITIVE               0x10
#define NO2_0_PERCENTS_BIAS                 0x00
#define NO2_1_PERCENT_BIAS                  0x01
#define NO2_2_PERCENTS_BIAS                 0x02
#define NO2_4_PERCENTS_BIAS                 0x03
#define NO2_6_PERCENTS_BIAS                 0x04
#define NO2_8_PERCENTS_BIAS                 0x05
#define NO2_10_PERCENTS_BIAS                0x06
#define NO2_12_PERCENTS_BIAS                0x07
#define NO2_14_PERCENTS_BIAS                0x08
#define NO2_16_PERCENTS_BIAS                0x09
#define NO2_18_PERCENTS_BIAS                0x0A
#define NO2_20_PERCENTS_BIAS                0x0B
#define NO2_22_PERCENTS_BIAS                0x0C
#define NO2_24_PERCENTS_BIAS                0x0D
/** \} */

/**
 * \defgroup mode  Mode
 * \{
 */
#define NO2_FET_DIS                         0x00
#define NO2_FET_EN                          0x80
#define NO2_DEEP_SLEEP_MODE                 0x00
#define NO2_2_LEAD_MODE                     0x01
#define NO2_STANDBY_MODE                    0x02
#define NO2_3_LEAD_MODE                     0x03
#define NO2_TEMP_MODE_TIA_OFF               0x06
#define NO2_TEMP_MODE_TIA_ON                0x07
/** \} */

/**
 * \defgroup state_device  State device
 * \{
 */
#define NO2_DEVICE_EN                       0x00
#define NO2_DEVICE_DIS                      0x01
/** \} */

/**
 * \defgroup device_address  Device address
 * \{
 */
#define ADC_DEVICE_ADDR                      0x4D
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

} no2_t;

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

} no2_cfg_t;

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
void no2_cfg_setup ( no2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NO2_RETVAL no2_init ( no2_t *ctx, no2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * 
 * @note
 * <pre>
 *      Set: NO2_MODECN_REG
 *              - NO2_DEEP_SLEEP_MODE
 *      Set: NO2_LOCK_REG
 *              - NO2_WRITE_MODE
 *      Set: NO2_TIACN_REG
 *              - NO2_EXT_TIA_RES | 
 *              - NO2_100_OHM_LOAD_RES
 *      Set: NO2_REFCN_REG
 *              - NO2_VREF_INT | 
 *              - NO2_50_PERCENTS_INT_ZERO |
 *              - NO2_BIAS_POL_NEGATIVE | 
 *              - NO2_0_PERCENTS_BIAS      
 * </pre>
 *
 * @description This function executes default configuration for No2 click.
 */
void no2_default_cfg ( no2_t *ctx );

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
void no2_generic_write ( no2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void no2_generic_read ( no2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function writes one byte to the register.
 *
 * @param ctx          Click object.
 * @param reg          Address where data be written
 * @param dev_data     Data to be written
 */
void no2_write_byte ( no2_t *ctx, uint8_t reg, uint8_t dev_data );

/**
 * @brief Function reads one byte from the register.
 *
 * @param ctx              Click object.
 * @param reg              Address which from data be read
 *
 * @description data that is read from the registry
 */
uint8_t no2_read_byte ( no2_t *ctx, uint8_t reg );

/**
 * @brief Device Enable function
 * 
 * @param ctx          Click object.
 * @param state        Value of pin RST
 * 
 */
void no2_enable ( no2_t *ctx, uint8_t state );

/**
 * @brief Function for read ADC sensor data
 *
 * @param ctx          Click object.
 * 
 * @description 12bit ADC value   
 */
uint16_t no2_read_adc ( no2_t *ctx );

/**
 * @brief Get NO2 Data function
 *
 * @param ctx          Click object.
 * 
 * @description NO2 data in ppm.
 */
float no2_get_no_2_ppm ( no2_t *ctx );

/**
 * @brief Function waits until I2C is ready for the next command.
 * 
 * @param ctx          Click object.
 */
void no2_wait_ready ( no2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _NO2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
