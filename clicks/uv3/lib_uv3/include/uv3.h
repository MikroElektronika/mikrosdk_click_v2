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
 * \brief This file contains API for UV 3 Click driver.
 *
 * \addtogroup uv3 UV 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UV3_H
#define UV3_H

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
#define UV3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.ack  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UV3_RETVAL  uint8_t

#define UV3_OK           0x00
#define UV3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup address macros
 * \{
 */
#define UV3_I2C_ADDR_DEFAULT                                       0x38
#define UV3_ADDR_ARA                                               0x0C
#define UV3_ADDR_CMD                                               0x38
#define UV3_ADDR_DATA_LSB                                          0x38
#define UV3_ADDR_DATA_MSB                                          0x39
/** \} */

/**
 * \defgroup command register macros
 * \{
 */
#define UV3_CMD_DEFAULT                                            0x02
#define UV3_CMD_SD                                                 0x01
#define UV3_CMD_IT_0_5T                                            0x00
#define UV3_CMD_IT_1T                                              0x04
#define UV3_CMD_IT_2T                                              0x08
#define UV3_CMD_IT_4T                                              0x0C
/** \} */

/**
 * \defgroup radiation macros
 * \{
 */
#define UV3_RAD_LOW                                                0x01
#define UV3_RAD_MODERATE                                           0x02
#define UV3_RAD_HIGH                                               0x03
#define UV3_RAD_VERY_HIGH                                          0x04
#define UV3_RAD_EXTREME                                            0x05
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

    digital_in_t ack;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} uv3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t ack;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} uv3_cfg_t;

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
void uv3_cfg_setup ( uv3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UV3_RETVAL uv3_init ( uv3_t *ctx, uv3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Uv3 click.
 */
void uv3_default_cfg ( uv3_t *ctx );

/**
 * @brief Write function.
 *
 * @param ctx          Click object.
 * @param slave_addr   Slave address.
 * @param command      Command to be written.
 *
 * @description Function write the 8-bit of data to the
 * target 8-bit write slave address of VEML6070 sensor on UV 3 Click.
 */
void uv3_write_command ( uv3_t *ctx, uint8_t slave_addr, uint8_t command );

/**
 * @brief Read function.
 *
 * @param ctx          Click object.
 * @param slave_addr   Slave address.
 *  
 * @returns One byte read data.
 * 
 * @description  Function read the 8-bit of data from the
 * target 8-bit reed slave address of VEML6070 sensor on UV 3 Click.
 */
uint8_t uv3_read_byte ( uv3_t *ctx, uint8_t slave_addr );

/**
 * @brief Read ARA to clear interrupt function.
 * 
 * @param ctx          Click object.
 *
 * @description Function read ARA clear interrupt from the
 * target 8-bit ARA slave address of VEML6070 sensor on UV 3 Click.
 */
void uv3_clear_ack ( uv3_t *ctx );

/**
 * @brief Enable sensor function.
 *
 * @param ctx          Click object.
 * 
 * @description Function enable sensor by sets shutdown mode bits as LOW to the
 * target 8-bit CMD slave address of VEML6070 sensor on UV 3 Click.
 */
void uv3_enable_sensor ( uv3_t *ctx );

/**
 * @brief Disable sensor function
 * 
 * @param ctx          Click object.
 *
 * @description Function disable sensor by sets shutdown mode bits as HIGH to the
 * target 8-bit CMD slave address of VEML6070 sensor on UV 3 Click.
 */
void uv3_disable_mode ( uv3_t *ctx );

/**
 * @brief Set integration time function.
 *
 * @param ctx          Click object.
 * @param it_data
 * 
 * @note
 * <pre>
 * Integration time data:
 * - 0x00 : 1/2 T ( 62.5 ms or 125  ms );
 * - 0x04 :  1  T ( 125  ms or 250  ms );
 * - 0x08 :  2  T ( 250  ms or 500  ms );
 * - 0x0C :  4  T ( 500  ms or 1000 ms );
 * </pre>
 * 
 * @description Function set integration time function by write it data to the
 * target 8-bit write slave address of VEML6070 sensor on UV 3 Click.
 */
void uv3_set_integration_time ( uv3_t *ctx, uint8_t int_data );

/**
 * @brief Get UV data measurements function.
 * 
 * @param ctx          Click object.
 *
 * @description Function read UV data measurements from to the two
 * target 8-bit slave address: DATA LSB and DATA HSB of VEML6070 sensor on UV 3 Click.
 */
uint16_t uv3_read_measurements ( uv3_t *ctx );

/**
 * @brief Calculate UV risk level function.
 *
 * @param uv_data      16-bit uv data for calculate.
 *
 * @return risk level.
 * @note
 * <pre>
 * Risk level
 * - 1: Low UV radiation;
 * - 2: Moderate UV radiation;
 * - 3: High UV radiation;
 * - 4: Very High UV radiation;
 * - 5: Extreme UV radiation;
 * </pre>
 * 
 * @description Function calculate UV risk level of VEML6070 sensor on UV 3 Click.
 */
uint8_t uv3_risk_level ( uint16_t uv_data );

/**
 * @brief Get state of interrupt pin function
 *
 * @param ctx          Click object.
 * 
 * @return state of ACK pin : 0 (not active) or 1 (active).
 *
 * @description Function get state of interrupt ( ACK ) pin.
 */
uint8_t uv3_get_interrupt ( uv3_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _UV3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
