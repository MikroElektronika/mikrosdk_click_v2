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
 * \brief This file contains API for Clock Gen 3 Click driver.
 *
 * \addtogroup clockgen3 Clock Gen 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CLOCKGEN3_H
#define CLOCKGEN3_H

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
#define CLOCKGEN3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CLOCKGEN3_RETVAL  uint8_t

#define CLOCKGEN3_OK           0x00
#define CLOCKGEN3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup oct_value Oct Value  
 * \{
 */
#define CLOCKGEN3_OCT_0  0
#define CLOCKGEN3_OCT_1  1
#define CLOCKGEN3_OCT_2  2
#define CLOCKGEN3_OCT_3  3
#define CLOCKGEN3_OCT_4  4
#define CLOCKGEN3_OCT_5  5
#define CLOCKGEN3_OCT_6  6
#define CLOCKGEN3_OCT_7  7
#define CLOCKGEN3_OCT_8  8
#define CLOCKGEN3_OCT_9  9
#define CLOCKGEN3_OCT_10 10
#define CLOCKGEN3_OCT_11 11
#define CLOCKGEN3_OCT_12 12
#define CLOCKGEN3_OCT_13 13
#define CLOCKGEN3_OCT_14 14
#define CLOCKGEN3_OCT_15 15
/** \} */

/**
 * \defgroup slave_addr  Slave Addr 
 * \{
 */
#define CLOCKGEN3_SLAVE_ADDRESS_GND  0x17
#define CLOCKGEN3_SLAVE_ADDRESS_VCC  0x16
/** \} */

/**
 * \defgroup config_param  Config param
 * \{
 */
#define CLOCKGEN3_CFG_ON_CLK_180     0x00
#define CLOCKGEN3_CFG_OFF_ON         0x01
#define CLOCKGEN3_CFG_ON_OFF         0x02
#define CLOCKGEN3_CFG_POWER_DOWN     0x03
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

    digital_out_t cs;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint8_t dev_slave_addr;
    uint8_t dev_config;


} clockgen3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t cs;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

    uint8_t dev_conf;

} clockgen3_cfg_t;

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
void clockgen3_cfg_setup ( clockgen3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param clockgen3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CLOCKGEN3_RETVAL clockgen3_init ( clockgen3_t *ctx, clockgen3_cfg_t *cfg );

/**
 * @brief Configuration
 *
 * @param ctx          Click object.
 * @param cfg          Configuration
 *
 * @note Options for configuration:
 * <pre>
 *    CLOCKGEN3_CFG_ON_CLK_180,
 *    CLOCKGEN3_CFG_OFF_ON,
 *    CLOCKGEN3_CFG_ON_OFF,
 *    CLOCKGEN3_CFG_POWER_DOWN
 * </pre>
 */
void clockgen3_config ( clockgen3_t *ctx, uint8_t cfg );

/**
 * @brief Sets CS pin state
 *
 * @param ctx          Click object.
 * @param state        CS pin state
 */
void clockgen3_set_cs_pin ( clockgen3_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void clockgen3_generic_write ( clockgen3_t *ctx, uint8_t *data_buf, uint8_t len );

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
void clockgen3_generic_read ( clockgen3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Sets Frequency
 *
 * @param ctx          Click object.
 * @param freq         Frequency in KHz ( 1.039 KHz to 68.03 MHz )
 *
 */
void clockgen3_set_freq ( clockgen3_t *ctx, float freq );

#ifdef __cplusplus
}
#endif
#endif  // _CLOCKGEN3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
