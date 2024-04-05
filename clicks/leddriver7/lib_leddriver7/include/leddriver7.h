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
 * \brief This file contains API for LED Driver 7 Click driver.
 *
 * \addtogroup leddriver7 LED Driver 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LEDDRIVER7_H
#define LEDDRIVER7_H

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
#define LEDDRIVER7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LEDDRIVER7_RETVAL  uint8_t

#define LEDDRIVER7_OK           0x00
#define LEDDRIVER7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define LEDDRIVER7_SLAVE_ADR_GND               0x2C
#define LEDDRIVER7_SLAVE_ADR_VCC               0x2D
/** \} */

/**
 * \defgroup time_mode  Time mode
 * \{
 */
#define LEDDRIVER7_ONE_TIME_PRG                0x80
#define LEDDRIVER7_NORM_OP_MODE                0x00
/** \} */

 /**
 * \defgroup status  Status
 * \{
 */
#define LEDDRIVER7_OTP_RDY_PRG                 0x00
#define LEDDRIVER7_OTP_TEST_FUSE_NOT_BLOWN     0x40
#define LEDDRIVER7_OTP_FATAL_ERR               0x80
#define LEDDRIVER7_OTP_SUCCESSFULL             0xC0
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

} leddriver7_t;

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

} leddriver7_cfg_t;

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
void leddriver7_cfg_setup ( leddriver7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param leddriver7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LEDDRIVER7_RETVAL leddriver7_init ( leddriver7_t *ctx, leddriver7_cfg_t *cfg );

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
void leddriver7_generic_write ( leddriver7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void leddriver7_generic_read ( leddriver7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif  // _LEDDRIVER7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
