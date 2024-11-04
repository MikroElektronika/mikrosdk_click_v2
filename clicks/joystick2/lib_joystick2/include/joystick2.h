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
 * \brief This file contains API for Joystick 2 Click driver.
 *
 * \addtogroup joystick2 Joystick 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef JOYSTICK2_H
#define JOYSTICK2_H

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
#define JOYSTICK2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define JOYSTICK2_RETVAL  uint8_t

#define JOYSTICK2_OK           0x00
#define JOYSTICK2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Device Slave Address
 * \{
 */
#define JOYSTICK2_DEVICE_SLAVE_ADDR_0_0  0x70
#define JOYSTICK2_DEVICE_SLAVE_ADDR_0_1  0x71
#define JOYSTICK2_DEVICE_SLAVE_ADDR_1_0  0x72
#define JOYSTICK2_DEVICE_SLAVE_ADDR_1_1  0x73
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define JOYSTICK2_CMD_INPUT_PORT          0x00
#define JOYSTICK2_CMD_OUTPUT_PORT         0x01
#define JOYSTICK2_CMD_POLARITY_INVERSION  0x02
#define JOYSTICK2_CMD_CONFIGURATION       0x03
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define JOYSTICK2_CFG_ENABLE_ALL_PORT   0xFF
#define JOYSTICK2_CFG_DISABLE_ALL_PORT  0x00
#define JOYSTICK2_CFG_ENABLE_BUTTON     0x02
#define JOYSTICK2_CFG_ENABLE_LEFT_POS   0x01
#define JOYSTICK2_CFG_ENABLE_RIGHT_POS  0x10
#define JOYSTICK2_CFG_ENABLE_UP_POS     0x08
#define JOYSTICK2_CFG_ENABLE_DOWN_POS   0x04
/** \} */

/**
 * \defgroup position Position
 * \{
 */
#define JOYSTICK2_POSITION_LEFT    0x01
#define JOYSTICK2_POSITION_RIGHT   0x10
#define JOYSTICK2_POSITION_UP      0x08
#define JOYSTICK2_POSITION_DOWN    0x04
#define JOYSTICK2_BUTTON_ACTIVE    0x02
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} joystick2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} joystick2_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void joystick2_cfg_setup ( joystick2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param joystick2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
JOYSTICK2_RETVAL joystick2_init ( joystick2_t *ctx, joystick2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Joystick2 Click.
 * @note Functions and setups that are included in the device's start configuration:
 * <pre>
 *   CONFIGURATION
 * -------------------------------------------
 *   JOYSTICK2_CFG_ENABLE_DOWN_POS
 *   JOYSTICK2_CFG_ENABLE_LEFT_POS
 *   JOYSTICK2_CFG_ENABLE_UP_POS
 *   JOYSTICK2_CFG_ENABLE_RIGHT_POS
 *   JOYSTICK2_CFG_ENABLE_BUTTON
 * </pre>
 */
void joystick2_default_cfg ( joystick2_t *ctx );

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
void joystick2_generic_write ( joystick2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void joystick2_generic_read ( joystick2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for reset module
 *
 * @param ctx          Click object.
 */
void joystick2_reset ( joystick2_t *ctx );

/**
 * @brief Functions for read interrupt state
 *
 * @param ctx          Click object.
 * @retval Interrupt state on the INT pin
 */
uint8_t joystick2_get_interrupt_state ( joystick2_t *ctx );

/**
 * @brief Functions for configuration joystick
 *
 * @param ctx          Click object.
 * @param cfg_data   The configuration data to be set
 *
 * @note Use this functions when you want to enable or disable the joystick position
 */
void joystick2_set_cfg_register ( joystick2_t *ctx, uint8_t cfg_data );

/**
 * @brief Functions for get Joystick position
 *
 * @param ctx          Click object.
 * @retval Joystick position (UP, DOWN, LEFT, RIGHT or BUTTON ACTIVE)
 */
uint8_t joystick2_get_position ( joystick2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _JOYSTICK2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
