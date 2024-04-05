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
 * \brief This file contains API for HTU21D Click driver.
 *
 * \addtogroup htu21d HTU21D Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HTU21D_H
#define HTU21D_H

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
#define HTU21D_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HTU21D_RETVAL  uint8_t

#define HTU21D_OK                                         0x00
#define HTU21D_INIT_ERROR                                 0xFF
/** \} */


/**
* \defgroup  htu21d_i2c_address  I2C address
* \{
*/
#define HTU21D_I2C_ADDRESS                                0x40
/** \} */

/**
 * \defgroup htu21d_wrt_usr_reg write user register
 * \{
 */
#define HTU21D_USER_REG_WRITE                             0xE6
/** \} */

 /**
  * \defgroup htu21d_rd_urs_reg read user register
  * \{
  */
#define HTU21D_USER_REG_READ                              0xE7
/** \} */

/**
 * \defgroup htu21d_wrt_htr_reg write heater contro register
 * \{
 */
#define HTU21D_HEATER_REG_WRITE                           0x51
/** \} */

/**
 * \defgroup htu21d_rd_htr_reg read heater register
 * \{
 */
#define HTU21D_HEATER_REG_READ                            0x11
/** \} */

/**
 * \defgroup htu21d_sft_rst soft reset
 * \{
 */
#define HTU21D_SOFT_RESET                                 0xFE
/** \} */

/**
 * \defgroup htu21d_rd_st read first two serial bytes
 * \{
 */
#define HTU21D_SERIAL1_READ1                              0xFA
/** \} */

 /**
  * \defgroup htu21d_rd_st read second two serial bytes
  * \{
  */
#define HTU21D_SERIAL1_READ2                              0x0F
/** \} */

/**
 * \defgroup htu21d_rd_rd read third two serial bytes
 * \{
 */
#define HTU21D_SERIAL2_READ1                              0xFC
/** \} */

/**
 * \defgroup htu21d_rd_th read fourth two serial bytes
 * \{
 */
#define HTU21D_SERIAL2_READ2                              0xC9
/** \} */

/**
 * \defgroup htu21d_id   id SI7013
 * \{
 */
#define HTU21D_SI7013_CHIPID                              0x0D
/** \} */

/**
 * \defgroup htu21d_id   id SI7020
 * \{
 */
#define HTU21D_SI7020_CHIPID                              0x14
/** \} */

/**
 * \defgroup htu21d_id   id SI7021
 * \{
 */
#define HTU21D_SI7021_CHIPID                              0x15
/** \} */

/**
 * \defgroup htu21d_id   id sht21
 * \{
 */
#define HTU21D_CHIPID                                     0x32
/** \} */

 /**
  * \defgroup htu21d_fmw_rd  read firmware revision first
  * \{
  */
#define HTU21D_FIRMWARE_READ1                             0x84
/** \} */

/**
 * \defgroup htu21d_fmw_rd  read firmware revision second
 * \{
 */
#define HTU21D_FIRMWARE_READ2                             0xB8
/** \} */

/**
 * \defgroup htu21d_srn  sensor firmware v1.0
 * \{
 */
#define HTU21D_FIRMWARE_V1                                0xFF
/** \} */

/**
 * \defgroup htu21d_srn_  sensor firmware v2.0
 * \{
 */
#define HTU21D_FIRMWARE_V2                                0x20
/** \} */

/**
 * \defgroup htu21d_frc__temp force read temperature
 * \{
 */
#define HTU21D_FORCE_READ_TEMP                            0xFE
/** \} */

/**
 * \defgroup htu21d_error  communication error is occurred 
 * \{
 */
#define HTU21D_ERROR                                      0xFF
/** \} */

/**
 * \defgroup htu21d_res_temp resolution temperature 14 bit &humidity 12 bit
 * \{
 */
#define HTU21D_RES_RH12_TEMP14                            0x00
/** \} */

/**
 * \defgroup htu21d_res_temp resolution temperature 12 bit &humidity 8 bit
 * \{
 */
#define HTU21D_RES_RH8_TEMP12                             0x01
/** \} */

/**
 * \defgroup htu21d_res_temp resolution temperature 13 bit &humidity 10 bit
 * \{
 */
#define HTU21D_RES_RH10_TEMP13                            0x80
/** \} */

 /**
  * \defgroup htu21d_res_temp resolution temperature 11 bit &humidity 11 bit
  * \{
  */
#define HTU21D_RES_RH11_TEMP11                            0x81
/** \} */

 /**
  * \defgroup htu21d_humd_msr humidity measurement with hold master
  * \{
  */
#define HTU21D_TRIG_HUMD_MEASURE_HOLD                     0xE5
/** \} */

 /**
  * \defgroup htu21d_humd_msr humidity measurement with no hold master
  * \{
  */
#define HTU21D_TRIG_HUMD_MEASURE_NOHOLD                   0xF5
/** \} */

/**
 * \defgroup htu21d_temp_msr  temperature measurement with hold master
 * \{
 */
#define HTU21D_TRIG_TEMP_MEASURE_HOLD                     0xE3
/** \} */

/**
 * \defgroup htu21d_temp_msr  temperature measurement with no hold master
 * \{
 */
#define HTU21D_TRIG_TEMP_MEASURE_NOHOLD                   0xF3
/** \} */

/**
 * \defgroup htu21d_htr_on heater on
 * \{
 */
#define HTU21D_ON                                         0x04
/** \} */

 /**
  * \defgroup htu21d_htr_off heater off
  * \{
  */
#define HTU21D_OFF                                        0xFB
/** \} */

/**
 * \defgroup htu21d_plm_vl polynomial for 16bit value
 * \{
 */
#define HTU21D_CRC8_POLYNOMINAL                           0x1310
/** \} */

/**
 * \defgroup calc_coef Calculation Coefficients
 * \{
 */
#define HTU21D_DATA_FILTER                                0xFFFC
#define HTU21D_DATA_RESOLUTION                            65536.0
#define HTU21D_TEMP_CALC_COEF                             175.72
#define HTU21D_TEMP_STB_COEF                              -46.85
#define HTU21D_HUMI_CALC_COEF                             125.0
#define HTU21D_HUMI_STB_COEF                              6.0
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

} htu21d_t;

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

} htu21d_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


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
void htu21d_cfg_setup ( htu21d_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param htu21d Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HTU21D_RETVAL htu21d_init ( htu21d_t *ctx, htu21d_cfg_t *cfg );

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
void htu21d_generic_write ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void htu21d_generic_read ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read 24-bit data function
 *
 * @param ctx           Click object.
 * @param reg_adr       Register address.
 *
 * @return 24-bit data from addressed register from HTU21D.
 *
 * @description Function read 24-bit data from register address of HTU21D.
 */
uint32_t htu21d_read_data ( htu21d_t *ctx, uint8_t reg_adr );

/**
 * @brief Send command function
 *
 * @param ctx           Click object.
 * @param cmd_byte      Command byte.
 *
 * @description Function sends command to HTU21D.
 * 
 * @note It  takes ~ 15 ms delay to reset.
 */
void htu21d_send_cmd ( htu21d_t *ctx, uint8_t cmd_byte );

/**
 * @brief Data read function.
 *
 * @param ctx           Click object.
 * @param reg           Register address.
 * @param data_buf      Output data buf
 * @param len           Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void htu21d_generic_read ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get temperature value function
 * 
 * @param ctx           Click object.
 * 
 * @return float temperature data degrees Celsius.
 *
 *@description Function read and calculate temperature in degrees Celsius 
 * from the HTU21D sensor.
 */
float htu21d_get_temperature ( htu21d_t *ctx );

/**
 * @brief Get humidity value function
 * 
 * @param ctx           Click object.
 *
 * @return float humidity data percentage.
 *
 * @description Function read and calculate humidity percentage
 * from the HTU21D sensor.
 */
float htu21d_get_humidity( htu21d_t *ctx );

/**
 * @brief Get humidity value function
 * 
 * @param ctx           Click object.
 *
 * @return float humidity data percentage.
 *
 * @description Function read and calculate humidity percentage
 * from the HTU21D sensor.
 */

#ifdef __cplusplus
}
#endif
#endif  // _HTU21D_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
