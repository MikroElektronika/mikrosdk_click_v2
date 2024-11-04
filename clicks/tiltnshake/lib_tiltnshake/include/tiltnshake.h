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
 * \brief This file contains API for TILT-n-SHAKE Click driver.
 *
 * \addtogroup tiltnshake TILT-n-SHAKE Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TILTNSHAKE_H
#define TILTNSHAKE_H

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
#define TILTNSHAKE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TILTNSHAKE_OK               0
#define TILTNSHAKE_ERROR           -1
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define TILTNSHAKE_MMA8491Q_I2C     0x55
/** \} */

/**
 * \defgroup must_be_1  Must be 1
 * \{
 */
#define TILTNSHAKE_STATUS_REG       0x00
#define TILTNSHAKE_DATA_READY       0x0F
/** \} */

/**
 * \defgroup MSB_and_LSB_axis_bits MSB and LSB axis bits
 * \{
 */
#define TILTNSHAKE_OUT_X_MSB_REG    0x01
#define TILTNSHAKE_OUT_X_LSB_REG    0x02
#define TILTNSHAKE_OUT_Y_MSB_REG    0x03
#define TILTNSHAKE_OUT_Y_LSB_REG    0x04
#define TILTNSHAKE_OUT_Z_MSB        0x05
#define TILTNSHAKE_OUT_Z_LSB        0x06
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
    digital_out_t en;

    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} tiltnshake_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t en;
    pin_name_t int_pin;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} tiltnshake_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void tiltnshake_cfg_setup ( tiltnshake_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t tiltnshake_init ( tiltnshake_t *ctx, tiltnshake_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @details This function writes data to the desired register.
 */
void tiltnshake_generic_write ( tiltnshake_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @details This function reads data from the desired register.
 */
void tiltnshake_generic_read ( tiltnshake_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for enabling chip
 * 
 * @param ctx          Click object.
 *
 * @details Enables chip
 */
void tiltnshake_enable ( tiltnshake_t *ctx );

/**
 * @brief Function for disabling chip
 * 
 * @param ctx          Click object.
 *
 * @details Disables chip
 */
void tiltnshake_disable ( tiltnshake_t *ctx );

/**
 * @brief Function for read status and axis
 * 
 * @param ctx          Click object.
 * @param status       Status register value
 * @param out_x        Axis x
 * @param out_y        Axis y
 * @param out_z        Axis z       
 *
 * @details Reads status register and then reads axis X Y Z like 14 bit data and places them in addresses
 */
void tiltnshake_read_status_and_axis ( tiltnshake_t *ctx, uint8_t *status, 
                                       float *out_x, float *out_y, float *out_z );

#ifdef __cplusplus
}
#endif
#endif  // _TILTNSHAKE_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
