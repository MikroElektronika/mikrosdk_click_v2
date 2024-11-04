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
 * \brief This file contains API for Color Click driver.
 *
 * \addtogroup color Color Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR_H
#define COLOR_H

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
#define COLOR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rd = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.gr = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.bl = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR_RETVAL  uint8_t

#define COLOR_OK                              0x00
#define COLOR_INIT_ERROR                      0xFF
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define COLOR_SLAVE_ADDRESS                   0x29
/** \} */


/**
 * \defgroup register Register
 * \{
 */
#define  COLOR_REG_ENABLE                      0x00
#define  COLOR_REG_RGBC_TIME                   0x01
#define  COLOR_REG_WAIT_TIME                   0x02
#define  COLOR_REG_AILTL                       0x03
#define  COLOR_REG_AILTH                       0x04
#define  COLOR_REG_AIHTL                       0x05
#define  COLOR_REG_AIHTH                       0x06
#define  COLOR_REG_PERS                        0x0C
#define  COLOR_REG_CONFIGURATION               0x0D
#define  COLOR_REG_CONTROL                     0x0F
#define  COLOR_REG_DEVICE_ID                   0x12
#define  COLOR_REG_DEVICE_STATUS               0x13
#define  COLOR_REG_CLEAR_DATA_LOW              0x14
#define  COLOR_REG_CLEAR_DATA_HIGH             0x15
#define  COLOR_REG_RED_DATA_LOW                0x16
#define  COLOR_REG_RED_DATA_HIGH               0x17
#define  COLOR_REG_GREEN_DATA_LOW              0x18
#define  COLOR_REG_GREEN_DATA_HIGH             0x19
#define  COLOR_REG_BLUE_DATA_LOW               0x1A
#define  COLOR_REG_BLUE_DATA_HIGH              0x1B
/** \} */

/**
 * \defgroup comm_register Command Register
 * \{
 */
#define  COLOR_CMD_SELECT                      0x80
#define  COLOR_CMD_REPEATED_BYTE_PROTOCOL      0x00
#define  COLOR_CMD_AUTO_INCREMENT_PROTOCOL     0x20
/** \} */

/**
 * \defgroup enable_register ENABLE Register
 * \{
 */
#define  COLOR_ENABLE_RGBC_INTERRUPT           0x10
#define  COLOR_ENABLE_WAIT                     0x08
#define  COLOR_ENABLE_RGBC                     0x02
#define  COLOR_POWER_ON                        0x01
/** \} */

/**
 * \defgroup rgbc_timing_reg RGBC Timing Register
 * \{
 */
#define  COLOR_RGBC_TIME_2_4ms                 0xFF
#define  COLOR_RGBC_TIME_24ms                  0xF6
#define  COLOR_RGBC_TIME_101ms                 0xD5
#define  COLOR_RGBC_TIME_154ms                 0xC0
#define  COLOR_RGBC_TIME_700ms                 0x00
/** \} */

/**
 * \defgroup wait_time_register Wait Time Register
 * \{
 */
#define  COLOR_WAIT_TIME_W0_2_4ms              0xFF
#define  COLOR_WAIT_TIME_W0_204ms              0xAB
#define  COLOR_WAIT_TIME_W0_614ms              0xFF
#define  COLOR_WAIT_TIME_W1_0_029sec           0xFF
#define  COLOR_WAIT_TIME_W1_2_45sec            0xAB
#define  COLOR_WAIT_TIME_W1_7_4sec             0xFF
/** \} */

/**
 * \defgroup persistence_reg Persistence Register
 * \{
 */
#define  COLOR_PERS_EVERY_RGBC                 0x00
#define  COLOR_PERS_CLEAR_CH_1                 0x01
#define  COLOR_PERS_CLEAR_CH_2                 0x02
#define  COLOR_PERS_CLEAR_CH_3                 0x03
#define  COLOR_PERS_CLEAR_CH_5                 0x04
#define  COLOR_PERS_CLEAR_CH_10                0x05
#define  COLOR_PERS_CLEAR_CH_15                0x06
#define  COLOR_PERS_CLEAR_CH_20                0x07
#define  COLOR_PERS_CLEAR_CH_25                0x08
#define  COLOR_PERS_CLEAR_CH_30                0x09
#define  COLOR_PERS_CLEAR_CH_35                0x0A
#define  COLOR_PERS_CLEAR_CH_40                0x0B
#define  COLOR_PERS_CLEAR_CH_45                0x0C
#define  COLOR_PERS_CLEAR_CH_50                0x0D
#define  COLOR_PERS_CLEAR_CH_55                0x0E
#define  COLOR_PERS_CLEAR_CH_60                0x0F
/** \} */

/**
 * \defgroup configuration_reg Configuration Register
 * \{
 */
#define  COLOR_CFG_WAIT_LONG                  0x01
/** \} */

/**
 * \defgroup control_register Control Register
 * \{
 */
#define  COLOR_CTRL_GAIN_x1                    0x00
#define  COLOR_CTRL_GAIN_x4                    0x01
#define  COLOR_CTRL_GAIN_x16                   0x02
#define  COLOR_CTRL_GAIN_x60                   0x03
/** \} */

/**
 * \defgroup color_register Color Register
 * \{
 */
#define  COLOR_COLOR_DATA_CLEAR                0x14
#define  COLOR_COLOR_DATA_RED                  0x16
#define  COLOR_COLOR_DATA_GREEN                0x18
#define  COLOR_COLOR_DATA_BLUE                 0x1A
/** \} */

/**
 * \defgroup led LED
 * \{
 */
#define  COLOR_LED_RED_ENABLE                  0x01
#define  COLOR_LED_GREEN_ENABLE                0x01
#define  COLOR_LED_BLUE_ENABLE                 0x01
#define  COLOR_LED_RED_DISABLE                 0x00
#define  COLOR_LED_GREEN_DISABLE               0x00
#define  COLOR_LED_BLUE_DISABLE                0x00
/** \} */

/**
 * \defgroup color_flag Color Flag
 * \{
 */
#define  ORANGE_COLOR_FLAG                        1
#define  RED_COLOR_FLAG                           2
#define  PINK_COLOR_FLAG                          3
#define  PURPLE_COLOR_FLAG                        4
#define  BLUE_COLOR_FLAG                          5
#define  CYAN_COLOR_FLAG                          6
#define  GREEN_COLOR_FLAG                         7
#define  YELLOW_COLOR_FLAG                        8
#define  NON_COLOR_FLAG                           0
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

    digital_out_t rd;
    digital_out_t gr;
    digital_out_t bl;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} color_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rd;
    pin_name_t gr;
    pin_name_t bl;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} color_cfg_t;

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
 * @param cfg            Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void color_cfg_setup ( color_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param color          Click object.
 * @param cfg            Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
COLOR_RETVAL color_init ( color_t *ctx, color_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx            Click object.
 *
 * @description This function executes default configuration for Color Click.
 */
void color_default_cfg ( color_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx            Click object.
 * @param reg            Register address.
 * @param data_buf       Data buf to be written.
 * @param len            Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void color_generic_write ( color_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx            Click object.
 * @param reg            Register address.
 * @param data_buf       Output data buf
 * @param len            Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void color_generic_read ( color_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write one byte to register.
 *
 * @param ctx            Click object.
 * @param reg            Register in which the data will be written.
 * @param data_to_write  Data which be written to the register.
 *
 * @description This function writes one byte to register.
 */
void color_write_byte ( color_t *ctx, uint8_t reg, uint8_t data_to_write );

/**
 * @brief Read 16-bit data from register.
 *
 * @param ctx            Click object.
 * @param reg            Register in which the data will be written.
 *
 * @returns Two byte data which is read from the register
 *
 * @description This function reads 2 bytes from register.
 */
uint16_t color_read_data ( color_t *ctx, uint8_t reg );

/**
 * @brief Read color ratio from register.
 *
 * @param ctx            Click object.
 * @param color          Color to get ratio for.
 *
 * @returns              Color ratio.
 *
 * @description This function reads desired color ratio from register.
 */
float color_read_color_ratio ( color_t *ctx, uint8_t color );

/**
 * @brief Functions for read color value.
 *
 * @param ctx            Click object.
 *
 * @returns              Color value in HSL.
 *
 * @description This function reads 3 color filters and clear
 * filters and converts the resulting color from RGBC to HSL.
 * The color range is between 0.0650 and 1.0000.
 */
float color_get_color_value ( color_t *ctx );

/**
 * @brief Detect color.
 *
 * @param color_value    Color value in HSL.
 *
 * @returns               Color flag.
 *
 * @description This function determines which color is read
 * by Click sensor after color_get_color_value() function has
 * been invoked previously.
 *
 * @note
 * <pre>
 * Detect color
 *    ORANGE color - from 0.992  to 0.999
 *    RED color    - from 0.9750 to 0.9919
 *    PINK color   - from 0.920  to 0.9749
 *    PURPLE color - from 0.6201 to 0.919
 *    BLUE color   - from 0.521  to 0.6200
 *    CYAN color   - from 0.4700 to 0.520
 *    GREEN color  - from 0.210  to 0.469
 *    YELLOW color - from 0.0650 to 0.209
 * </pre>
 */
uint8_t color_get_color ( float color_value );

/**
 * @brief Get interrupt pin state.
 *
 * @param ctx            Click object.
 *
 * @returns              int pin state.
 *
 * @description This function reads interrupt pin state.
 */
uint8_t color_get_interrupt ( color_t *ctx );

/**
 * @brief Functions for set Led lights.
 *
 * @param ctx            Click object.
 * @param red            Enable/disable red LED.
 * @param green          Enable/disable green LED.
 * @param blue           Enable/disable blue LED.
 *
 * @description This function enables and disables LEDs.
 */
void color_set_led ( color_t *ctx, uint8_t red, uint8_t green, uint8_t blue );


#ifdef __cplusplus
}
#endif
#endif  // _COLOR_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
