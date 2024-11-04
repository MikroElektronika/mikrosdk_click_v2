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
 * \brief This file contains API for Color 8 Click driver.
 *
 * \addtogroup color8 Color 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR8_H
#define COLOR8_H

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
#define COLOR8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR8_RETVAL  uint8_t

#define COLOR8_OK           0x00
#define COLOR8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define COLOR8_REG_SYSTEM_CONTROL               0x40
#define COLOR8_REG_MODE_CONTROL_1               0x41
#define COLOR8_REG_MODE_CONTROL_2               0x42
#define COLOR8_REG_RED_DATA                     0x50
#define COLOR8_REG_RED_DATA_LSB                 0x50
#define COLOR8_REG_RED_DATA_MSB                 0x51
#define COLOR8_REG_GREEN_DATA                   0x52
#define COLOR8_REG_GREEN_DATA_LSB               0x52
#define COLOR8_REG_GREEN_DATA_MSB               0x53
#define COLOR8_REG_BLUE_DATA                    0x54
#define COLOR8_REG_BLUE_DATA_LSB                0x54
#define COLOR8_REG_BLUE_DATA_MSB                0x55
#define COLOR8_REG_IR_DATA                      0x58
#define COLOR8_REG_IR_DATA_LSB                  0x58
#define COLOR8_REG_IR_DATA_MSB                  0x59
#define COLOR8_REG_GREEN_DATA_2                 0x5A
#define COLOR8_REG_GREEN_DATA_2_LSB             0x5A
#define COLOR8_REG_GREEN_DATA_2_MSB             0x5B
#define COLOR8_REG_INTERRUPT                    0x60
#define COLOR8_REG_PERSISTENCE                  0x61
#define COLOR8_REG_THRESHOLD_HIGH_LSB           0x62
#define COLOR8_REG_THRESHOLD_HIGH_MSB           0x63
#define COLOR8_REG_THRESHOLD_LOW_LSB            0x64
#define COLOR8_REG_THRESHOLD_LOW_MSB            0x65
#define COLOR8_REG_MANUFACTURER_ID              0x92
/** \} */

/**
 * \defgroup system_control System Control
 * \{
 */
#define COLOR8_SS_SW_RESET_IS_NOT_DONE          0x00
#define COLOR8_SS_SW_RESET_IS_DONE              0x80
#define COLOR8_SS_INT_PIN_IS_NOT_ACTIVE         0x00
#define COLOR8_SS_INT_PIN_IS_ACTIVE             0x40
/** \} */

/**
 * \defgroup mode_control_1 Mode Control 1
 * \{
 */
#define COLOR8_MC1_IR_DATA_GAIN_X1              0x20
#define COLOR8_MC1_IR_DATA_GAIN_X32             0x60
#define COLOR8_MC1_RGB_DATA_GAIN_X1             0x08
#define COLOR8_MC1_RGB_DATA_GAIN_X32            0x18
#define COLOR8_MC1_MEASURE_MODE_120ms           0x02
#define COLOR8_MC1_MEASURE_MODE_240ms           0x03
#define COLOR8_MC1_MEASURE_MODE_35ms            0x05
/** \} */

/**
 * \defgroup mode_control_2 Mode Control 2
 * \{
 */
#define COLOR8_MC2_MEASUREMENT_IS_ACTIVE        0x10
#define COLOR8_MC2_MEASUREMENT_IS_INACTIVE      0x00
/** \} */

/**
 * \defgroup interrupt Interrupt
 * \{
 */
#define COLOR8_INT_INTERRUPT_SIGNAL_IS_ACTIVE   0x80
#define COLOR8_INT_RED_CHANNEL                  0x00
#define COLOR8_INT_GREEN_CHANNEL                0x02
#define COLOR8_INT_BLUE_CHANNEL                 0x04
#define COLOR8_INT_PIN_DISABLE                  0x00
#define COLOR8_INT_PIN_ENABLE                   0x01
/** \} */

/**
 * \defgroup persistence Persistence
 * \{
 */
#define COLOR8_PERSISTENCE_INT_SETTINGS_0       0x00
#define COLOR8_PERSISTENCE_INT_SETTINGS_1       0x01
#define COLOR8_PERSISTENCE_INT_SETTINGS_2       0x02
#define COLOR8_PERSISTENCE_INT_SETTINGS_3       0x03
/** \} */

/**
 * \defgroup default Default
 * \{
 */
#define COLOR8_DEF_MANUFACTURER_ID              0xE0
#define COLOR8_DEF_PART_ID                      0x0D
#define COLOR8_DEF_SLAVE_ADDRESS_0              0x38
#define COLOR8_DEF_SLAVE_ADDRESS_1              0x39
/** \} */

/**
 * \defgroup color_flag Color Flag
 * \{
 */
#define ORANGE_COLOR_FLAG                       1
#define RED_COLOR_FLAG                          2
#define PINK_COLOR_FLAG                         3
#define PURPLE_COLOR_FLAG                       4
#define BLUE_COLOR_FLAG                         5
#define CYAN_COLOR_FLAG                         6
#define GREEN_COLOR_FLAG                        7
#define YELLOW_COLOR_FLAG                       8
#define NON_COLOR_FLAG                          0
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} color8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} color8_cfg_t;

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
void color8_cfg_setup ( color8_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param color8 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
COLOR8_RETVAL color8_init ( color8_t *ctx, color8_cfg_t *cfg );

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
void color8_generic_write ( color8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void color8_generic_read ( color8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for write one byte in register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param w_data       Data which be written in the register.
 *
 * @description This function writes one byte in register.
 */
void color8_write_byte ( color8_t *ctx, uint8_t reg, uint8_t w_data );

/**
 * @brief Functions for read one byte data from register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads one byte data from register.
 */
uint8_t color8_read_byte ( color8_t *ctx, uint8_t reg );

/**
 * @brief Functions get interrupt.
 *
 * @param ctx          Click object.
 *
 * @description This function gets interrupt.
 */
uint8_t color8_get_interrupt ( color8_t *ctx );

/**
 * @brief Functions for read data from register.
 *
 * @param ctx          Click object.
 * @param reg_data     Register in which the data will be written.
 *
 * @description This function reads data from register.
 */
uint16_t color8_read_data ( color8_t *ctx, uint8_t reg_data );

/**
 * @brief Functions for read color value.
 *
 * @param ctx          Click object.
 *
 * @description This functions reads 3 color filters and Clear Filters and converts the resulting color from RGB to HSL.
 *              The color range is between 0.00 and 1.0000.
 */
float color8_get_color_value ( color8_t *ctx );

/**
 * @brief Functions for detect colors.
 *
 * @param ctx          Click object.
 * @param color_value  Color value in HSL.
 *
 * @description This function detect colors.
 *       PINK color   - from 0.920  to 0.974
 *       PURPLE color - from 0.6201 to 0.919
 *       BLUE color   - from 0.521  to 0.620
 *       CYAN color   - from 0.430  to 0.520
 *       GREEN color  - from 0.300  to 0.429
 *       YELLOW color - from 0.019  to 0.200
 *       RED color    - from 0.0005 to 0.018
 */
uint8_t color8_get_color ( color8_t *ctx, float color_value );


#ifdef __cplusplus
}
#endif
#endif  // _COLOR8_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
