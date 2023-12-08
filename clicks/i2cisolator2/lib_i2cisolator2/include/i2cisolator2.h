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
 * \brief This file contains API for I2C Isolator 2 Click driver.
 *
 * \addtogroup i2cisolator2 I2C Isolator 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef I2CISOLATOR2_H
#define I2CISOLATOR2_H

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
#define I2CISOLATOR2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pdis = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define I2CISOLATOR2_OK             0
#define I2CISOLATOR2_ERROR         -1
/** \} */

/**
 * \defgroup power_enable Power enable
 * \{
 */
#define I2CISOLATOR2_POWER_ENABLE   0
#define I2CISOLATOR2_POWER_DISABLE  1

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
    digital_out_t pdis;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} i2cisolator2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t pdis;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} i2cisolator2_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void i2cisolator2_cfg_setup ( i2cisolator2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t i2cisolator2_init ( i2cisolator2_t *ctx, i2cisolator2_cfg_t *cfg );

/**
 * @brief This function sets PDIS pin state.
 *
 * @param ctx    Click object.
 * @param state  PDIS pin state.
 *
 * @details This function sets the state of PDIS pin.
 */
void i2cisolator2_enable_power ( i2cisolator2_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_in      Data buf to be written.
 * @param len          Number of bytes in data buf.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *
 * @details This function writes a desired data to I2C bus.
 */
err_t i2cisolator2_write ( i2cisolator2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param data_out     Output data buf
 * @param len          Number of bytes to be read
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *
 * @details This function reads a desired number of data bytes from I2C bus.
 */
err_t i2cisolator2_read ( i2cisolator2_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Generic write then read function.
 *
 * @param ctx          Click object.
 * @param data_in      Data buf to be written.
 * @param in_len       Number of bytes in data in buffer.
 * @param data_out     Output data buf
 * @param out_len      Number of bytes in data out buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *
 * @details This function writes a desired number of data bytes to I2C bus and then
 * reads a desired number of data bytes from I2C bus.
 */
err_t i2cisolator2_write_then_read ( i2cisolator2_t *ctx, uint8_t *data_in, uint16_t in_len, 
                                     uint8_t *data_out, uint16_t out_len );

/**
 * @brief Set slave address function.
 *
 * @param ctx          Click object.
 * @param slave_addr   Slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *
 * @details This function sets the slave address.
 */
err_t i2cisolator2_set_slave_address ( i2cisolator2_t *ctx, uint8_t slave_addr );

#ifdef __cplusplus
}
#endif
#endif  // _I2CISOLATOR2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
