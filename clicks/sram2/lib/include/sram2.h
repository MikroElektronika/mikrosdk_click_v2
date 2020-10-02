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
 * \brief This file contains API for SRAM 2 Click driver.
 *
 * \addtogroup sram2 SRAM 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SRAM2_H
#define SRAM2_H

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
#define SRAM2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SRAM2_RETVAL  uint8_t

#define SRAM2_OK           0x00
#define SRAM2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup write_protect  Write Protect
 * \{
 */
#define SRAM2_WR_ENABLE    0x01
#define SRAM2_WR_DISABLE   0x00
/** \} */

/**
 * \defgroup slave_address  Slave address
 * \{
 */
#define SRAM2_SLAVE_ADDR_0_0  0x51
#define SRAM2_SLAVE_ADDR_0_1  0x53
#define SRAM2_SLAVE_ADDR_1_0  0x55
#define SRAM2_SLAVE_ADDR_1_1  0x57
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

    digital_out_t wp;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} sram2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t wp;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} sram2_cfg_t;

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
void sram2_cfg_setup ( sram2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SRAM2_RETVAL sram2_init ( sram2_t *ctx, sram2_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param wr_data      Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void sram2_generic_write ( sram2_t *ctx, uint16_t reg, uint8_t wr_data );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param rx_data      Output data 
 *
 * @description This function reads data from the desired register.
 */
void sram2_generic_read ( sram2_t *ctx, uint16_t reg, uint8_t *rx_data );

/**
 * @brief Set PWM pin for write protection.
 *
 * @param ctx          Click object.
 * @param state        State of ( PWM ) pin.
 *
 * @description This function set pwm pin on 1 or 0.
 */
void sram2_write_protect( sram2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _SRAM2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
