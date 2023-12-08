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
 * \brief This file contains API for Surface temp 2 Click driver.
 *
 * \addtogroup surfacetemp2 Surface temp 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SURFACETEMP2_H
#define SURFACETEMP2_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define SURFACETEMP2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SURFACETEMP2_RETVAL  uint8_t

#define SURFACETEMP2_OK           0x00
#define SURFACETEMP2_INIT_ERROR   0xFF
/** \} */
 
/**
 * \defgroup slave_address  Slave address
 * \{
 */
#define SURFACETEMP2_I2C_DEV_ADR_0_0      0x48
#define SURFACETEMP2_I2C_DEV_ADR_0_1      0x49
#define SURFACETEMP2_I2C_DEV_ADR_1_0      0x4A
#define SURFACETEMP2_I2C_DEV_ADR_1_1      0x4B
/** \} */
 
/**
 * \defgroup reg_map  Reg map
 * \{
 */
#define SURFACETEMP2_REG_TEMP_MSB         0x00
#define SURFACETEMP2_REG_TEMP_LSB         0x01
#define SURFACETEMP2_REG_STAT             0x02
#define SURFACETEMP2_REG_CFG              0x03
#define SURFACETEMP2_REG_T_HIGH_SETP_MSB  0x04
#define SURFACETEMP2_REG_T_HIGH_SETP_LSB  0x05
#define SURFACETEMP2_REG_T_LOW_SETP_MSB   0x06
#define SURFACETEMP2_REG_T_LOW_SETP_LSB   0x07
#define SURFACETEMP2_REG_T_CRIT_SETP_MSB  0x08
#define SURFACETEMP2_REG_T_CRIT_SETP_LSB  0x09
#define SURFACETEMP2_REG_T_HYST_SETP      0x0A
#define SURFACETEMP2_REG_ID               0x0B
#define SURFACETEMP2_REG_SOFT_RESET       0x2F
/** \} */
 
/**
 * \defgroup stat_reg_mask  Stat reg mask
 * \{
 */
#define SURFACETEMP2_STAT_T_LOW_MSK       0x10
#define SURFACETEMP2_STAT_T_HIGH_MSK      0x20
#define SURFACETEMP2_STAT_T_CRIT_MSK      0x40
#define SURFACETEMP2_STAT_RDY_MSK         0x80
/** \} */
 
/**
 * \defgroup conf_reg  Conf reg
 * \{
 */
#define SURFACETEMP2_CFG_FLT_Q_1          0x00
#define SURFACETEMP2_CFG_FLT_Q_2          0x01
#define SURFACETEMP2_CFG_FLT_Q_3          0x02
#define SURFACETEMP2_CFG_FLT_Q_4          0x03
#define SURFACETEMP2_CFG_CT_POL_ACT_H     0x04
#define SURFACETEMP2_CFG_CT_POL_ACT_L     0x00
#define SURFACETEMP2_CFG_INT_POL_ACT_H    0x08
#define SURFACETEMP2_CFG_INT_POL_ACT_L    0x00
#define SURFACETEMP2_CFG_INT_MODE         0x00
#define SURFACETEMP2_CFG_CT_MODE          0x10
#define SURFACETEMP2_CFG_OP_MODE_CONT     0x00
#define SURFACETEMP2_CFG_OP_MODE_ONE_SHT  0x20
#define SURFACETEMP2_CFG_OP_MODE_SPS      0x40
#define SURFACETEMP2_CFG_OP_MODE_SHDN     0x60
#define SURFACETEMP2_CFG_RES_13           0x00
#define SURFACETEMP2_CFG_RES_16           0x80
/** \} */
 
/**
 * \defgroup temp_resolution  Temp resolution
 * \{
 */
#define SURFACETEMP2_RES_13_BIT             0.0625
#define SURFACETEMP2_RES_16_BIT             0.0078125
/** \} */
 
/**
 * \defgroup device_id_value  Device id value
 * \{
 */
#define SURFACETEMP2_DEV_ID_VAL           0xCB
/** \} */
 
/**
 * \defgroup device_check_status  Device check status
 * \{
 */
#define SURFACETEMP2_DEV_OK               0x00
#define SURFACETEMP2_DEV_NOK              0x01
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

    digital_in_t pwm;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} surfacetemp2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t pwm;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} surfacetemp2_cfg_t;

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
void surfacetemp2_cfg_setup ( surfacetemp2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param surfacetemp2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SURFACETEMP2_RETVAL surfacetemp2_init ( surfacetemp2_t *ctx, surfacetemp2_cfg_t *cfg );

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
void surfacetemp2_generic_write ( surfacetemp2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void surfacetemp2_generic_read ( surfacetemp2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Software Reset function
 *
 * @param ctx          Click object.
 * 
 * Function is used to issue soft reset command.
 * @note Function holds small 100 ms delay.
**/
void surfacetemp2_soft_reset ( surfacetemp2_t *ctx );

/**
 * @brief Setup function
 *
 * @param ctx          Click object.
 * @param setup  8-bit input data that define device settings
 *
 * @returns 0 If setup si successful
 * @returns 1 If an error has occured.

 *
 * Function is used to apply the desired settings.
 * @note Function holds "Software Reset" function and reads device ID.
**/
uint8_t surfacetemp2_setup ( surfacetemp2_t *ctx, uint8_t setup );

/**
 * @brief Set Hysteresis function
 *
 * @param ctx          Click object.
 * @param hys_val user defined value that represents hysteresis
 *
 * Function is used to set hysteresis.
 * @note Hysteresis value should range from 0 to 15;
**/
void surfacetemp2_set_hys_val ( surfacetemp2_t *ctx, uint8_t hys_val );

/**
 * @brief Get Temperature function
 *
 * @param ctx          Click object.
 * 
 * @returns Temperature value in degree Celsius.
 *
 * Function is used to read and calculate temperatre value.
 * @note Function checks the resolution by rading Configuration register.
**/
float surfacetemp2_get_temperature ( surfacetemp2_t *ctx );

/**
 * @brief Set Over Temperature Threshold function
 *
 * @param ctx          Click object.
 * @param trsh  over temperature threshold limit
 *
 * Function is used to set over temperature threshold limit.
**/
void surfacetemp2_set_high_trsh ( surfacetemp2_t *ctx, float trsh );

/**
 * @brief Set Under Temperature Threshold function
 *
 * @param ctx          Click object.
 * @param trsh  under temperature threshold limit
 *
 * Function is used to set under temperature threshold limit.
**/
void surfacetemp2_set_low_trsh ( surfacetemp2_t *ctx, float trsh );

/**
 * @brief Set Critical Temperature Threshold function
 *
 * @param ctx          Click object.
 * @param trsh  critical temperature threshold limit
 *
 * Function is used to set critical temperature threshold limit.
**/
void surfacetemp2_set_crit_trsh ( surfacetemp2_t *ctx, float trsh );

/**
 * @brief Get INT pin state function
 *
 * @param ctx          Click object.
 * 
 * @returns 0 if INT pin is LOW
 * @returns 1 if INT pin is HIGH
 *
 * Function is used to get the INT pin state.
 * @note Use of the INT pin is defined in Configuration register.
**/
uint8_t surfacetemp2_get_int_pin ( surfacetemp2_t *ctx );

/**
 * @brief Get CT pin state function
 *
 * @param ctx          Click object.
 * 
 * @returns 0 if INT pin is LOW
 * @returns 1 if INT pin is HIGH
 *
 * Function is used to get the CT pin state.
 * @note Use of the CT pin is defined in Configuration register.
**/
uint8_t surfacetemp2_get_ct_pin ( surfacetemp2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SURFACETEMP2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
