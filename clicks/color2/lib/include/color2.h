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
 * \brief This file contains API for Color 2 Click driver.
 *
 * \addtogroup color2 Color 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR2_H
#define COLOR2_H

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
#define COLOR2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR2_RETVAL  uint8_t

#define COLOR2_OK           0x00
#define COLOR2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup config_register Config Registers
 * \{
 */ 
#define COLOR2_I2C_ADDR                            0x44
#define COLOR2_DEVICE_ID                           0x00
#define COLOR2_CONFIG_1                            0x01
#define COLOR2_CONFIG_2                            0x02
#define COLOR2_CONFIG_3                            0x03
#define COLOR2_THRESHOLD_LL                        0x04
#define COLOR2_THRESHOLD_LH                        0x05
#define COLOR2_THRESHOLD_HL                        0x06
#define COLOR2_THRESHOLD_HH                        0x07
#define COLOR2_STATUS                              0x08
#define COLOR2_GREEN_L                             0x09
#define COLOR2_GREEN_H                             0x0A
#define COLOR2_RED_L                               0x0B
#define COLOR2_RED_H                               0x0C
#define COLOR2_BLUE_L                              0x0D
#define COLOR2_BLUE_H                              0x0E
#define COLOR2_CFG_DEFAULT                         0x00
#define COLOR2_CFG1_MODE_POWERDOWN                 0x00
#define COLOR2_CFG1_MODE_G                         0x01
#define COLOR2_CFG1_MODE_R                         0x02
#define COLOR2_CFG1_MODE_B                         0x03
#define COLOR2_CFG1_MODE_STANDBY                   0x04
#define COLOR2_CFG1_MODE_RGB                       0x05
#define COLOR2_CFG1_MODE_RG                        0x06
#define COLOR2_CFG1_MODE_GB                        0x07
#define COLOR2_CFG1_375LUX                         0x00
#define COLOR2_CFG1_10KLUX                         0x08
#define COLOR2_CFG1_16BIT                          0x00
#define COLOR2_CFG1_12BIT                          0x10
#define COLOR2_CFG1_ADC_SYNC_NORMAL                0x00
#define COLOR2_CFG1_ADC_SYNC_TO_INT                0x20
#define COLOR2_CFG2_IR_OFFSET_OFF                  0x00
#define COLOR2_CFG2_IR_OFFSET_ON                   0x80
#define COLOR2_CFG2_IR_ADJUST_LOW                  0x00
#define COLOR2_CFG2_IR_ADJUST_MID                  0x20
#define COLOR2_CFG2_IR_ADJUST_HIGH                 0x3F
/** \} */

/**
 * \defgroup interrupt_register Interrupt Registers
 * \{
 */ 
#define COLOR2_CFG3_NO_INT                        0x00
#define COLOR2_CFG3_G_INT                         0x01
#define COLOR2_CFG3_R_INT                         0x02
#define COLOR2_CFG3_B_INT                         0x03
#define COLOR2_CFG3_INT_PRST1                     0x00
#define COLOR2_CFG3_INT_PRST2                     0x04
#define COLOR2_CFG3_INT_PRST4                     0x08
#define COLOR2_CFG3_INT_PRST8                     0x0C
#define COLOR2_CFG3_RGB_CONV_TO_INT_DISABLE       0x00
#define COLOR2_CFG3_RGB_CONV_TO_INT_ENABLE        0x10
/** \} */

/**
 * \defgroup status_flag_masks STATUS FLAG MASKS
 * \{
 */
#define COLOR2_FLAG_INT                           0x01
#define COLOR2_FLAG_CONV_DONE                     0x02
#define COLOR2_FLAG_BROWNOUT                      0x04
#define COLOR2_FLAG_CONV_G                        0x10
#define COLOR2_FLAG_CONV_R                        0x20
#define COLOR2_FLAG_CONV_B                        0x30
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

} color2_t;

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

} color2_cfg_t;

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
void color2_cfg_setup ( color2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param color2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COLOR2_RETVAL color2_init ( color2_t *ctx, color2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Color2 click.
 */
void color2_default_cfg ( color2_t *ctx );

/**
 * @brief Generic write data function
 *
 * @param ctx          Click object.
 * @param address         Register address
 *
 * @param writeCommand    Command to write
 *
 * Function write byte of data to ISL29125
 */
void color2_write_data ( color2_t *ctx, uint8_t address, uint8_t write_command );

/**
 * @brief Generic read data function
 *
 * @param ctx  Click object.
 * @param address         Register address
 *
 * @return    Data from addressed register in ISL29125
 *
 * Function read byte of data from register address of ISL29125
 */
uint8_t color2_read_data ( color2_t *ctx, uint8_t address );
 
/**
 * @brief Reset default register value function
 *
 * @param ctx  Click object.
 * @return    0 if ERROR; 1 if OK
 *
 * Reset default register value function ISL29125
 */
uint8_t color2_reset ( color2_t *ctx );

/**
 * @brief Generic read data function
 *
 * @param ctx  Click object.
 * @param config1         Register address config1
 *
 * @param config2         Register address config2
 *
 * @param config3         Register address config3
 *
 * @return    0 if ERROR; 1 if OK
 *
 * Function read byte of data from register address of ISL29125
 */
uint8_t color2_init_advanced ( color2_t *ctx, uint8_t config1, uint8_t config2, uint8_t config3);

/**
 * @brief Function set upper threshold register
 *
 * @param ctx  Click object.
 * @param upperThreshold         upperThreshold register address
 *
 * Function set upper threshold register of ISL29125
 */
void color2_set_upper_threshold ( color2_t *ctx, uint16_t upper_threshold );

/**
 * @brief Function set lower threshold register
 *
 * @param ctx  Click object.
 * @param lowerThreshold         lowerThreshold register address
 *
 * Function set lower threshold register of ISL29125
 */
void color2_set_lower_hreshold ( color2_t *ctx, uint16_t lower_threshold );

/**
 * @brief Function read upper threshold register
 *
 * @param ctx  Click object.
 * @return    Upper Threshold 16-bit data
 *
 * Function read upper threshold register from ISL29125
 */
uint16_t color2_read_upper_threshold ( color2_t *ctx );

/**
 * @brief Function read lower threshold register
 *
 * @param ctx  Click object.
 * @return    Lower Threshold 16-bit data
 *
 * Function read lower threshold register from ISL29125
 */
uint16_t color2_read_lower_threshold ( color2_t *ctx );

/**
 * @brief Function read red color data
 *
 * @param ctx  Click object.
 * @return    16-bit red color data
 *
 * Function read red color data from ISL29125
 */
float color2_read_red ( color2_t *ctx );

/**
 * @brief Function read green color data
 *
 * @param ctx  Click object.
 * @return    16-bit green color data
 *
 * Function read green color data from ISL29125
 */
float color2_read_green ( color2_t *ctx );

/**
 * @brief Function read blue color data
 *
 * @param ctx  Click object.
 * @return    16-bit blue color data
 *
 * Function read blue color data from ISL29125
 */
float color2_read_blue ( color2_t *ctx );

/**
 * @brief Function read status registe value
 *
 * @param ctx  Click object.
 * @return    16-bit status data
 *
 * Function read status registe value from ISL29125
 */
uint8_t color2_read_status ( color2_t *ctx );

/**
 * @brief Functions for read color value
 *
 * @param ctx  Click object.
 * @retval Color value in HSL
 *
 * This functions reas 3 color filters and Clear Filters and converts the resulting color from RGBC to HSL
   The color range is between 0.0650 and 1.0000.
 */
float color2_get_color_value ( color2_t *ctx );

/**
 * @brief Functions for detect colors
 *
 * @param ctx  Click object.
 * @param color_value  color value in HSL
 *
 * @retval Color flag
 *
 * Detect color
      ORANGE color - from 0.992  to 0.999
      RED color    - from 0.9750 to 0.9919
      PINK color   - from 0.920  to 0.9749
      PURPLE color - from 0.6201 to 0.919
      BLUE color   - from 0.521  to 0.6200
      CYAN color   - from 0.4700 to 0.520
      GREEN color  - from 0.210  to 0.469
      YELLOW color - from 0.0650 to 0.209
 */
uint8_t color2_get_color ( float color_value );

#ifdef __cplusplus
}
#endif
#endif  // _COLOR2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
