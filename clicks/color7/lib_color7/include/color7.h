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
 * \brief This file contains API for Color 7 Click driver.
 *
 * \addtogroup color7 Color 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR7_H
#define COLOR7_H

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
#define COLOR7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR7_RETVAL  uint8_t

#define COLOR7_OK           0x00
#define COLOR7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers 
 * \{
 */
#define COLOR7_REG_ENABLE           0x00
#define COLOR7_REG_RGBC_TIME        0x01
#define COLOR7_REG_WAIT_TIME        0x02
#define COLOR7_REG_AILTL            0x03
#define COLOR7_REG_AILTH            0x04
#define COLOR7_REG_AIHTL            0x05
#define COLOR7_REG_AIHTH            0x06
#define COLOR7_REG_PERS             0x0C
#define COLOR7_REG_CONFIGURATION    0x0D
#define COLOR7_REG_CONTROL          0x0F
#define COLOR7_REG_DEVICE_ID        0x12
#define COLOR7_REG_DEVICE_STATUS    0x13
#define COLOR7_REG_CLEAR_DATA_LOW   0x14
#define COLOR7_REG_CLEAR_DATA_HIGH  0x15
#define COLOR7_REG_RED_DATA_LOW     0x16
#define COLOR7_REG_RED_DATA_HIGH    0x17
#define COLOR7_REG_GREEN_DATA_LOW   0x18
#define COLOR7_REG_GREEN_DATA_HIGH  0x19
#define COLOR7_REG_BLUE_DATA_LOW    0x1A
#define COLOR7_REG_BLUE_DATA_HIGH   0x1B
/** \} */

/**
 * \defgroup command_register Command Register
 * \{
 */
#define COLOR7_CMD_SELECT  0x80
#define COLOR7_CMD_REPEATED_BYTE_PROTOCOL  0x00
#define COLOR7_CMD_AUTO_INCREMENT_PROTOCOL  0x20
/** \} */

/**
 * \defgroup enable_register Enable Register
 * \{
 */
#define COLOR7_ENABLE_RGBC_INTERRUPT  0x10
#define COLOR7_ENABLE_WAIT            0x08
#define COLOR7_ENABLE_RGBC            0x02
#define COLOR7_POWER_ON               0x01
/** \} */

/**
 * \defgroup rgbc_timing_register RGBC Timing Register
 * \{
 */
#define COLOR7_RGBC_TIME_2_4ms  0xFF
#define COLOR7_RGBC_TIME_24ms   0xF6
#define COLOR7_RGBC_TIME_101ms  0xD5
#define COLOR7_RGBC_TIME_154ms  0xC0
#define COLOR7_RGBC_TIME_700ms  0x00
/** \} */

/**
 * \defgroup wait_time_register Wait Time Register
 * \{
 */
#define COLOR7_WAIT_TIME_W0_2_4ms     0xFF
#define COLOR7_WAIT_TIME_W0_204ms     0xAB
#define COLOR7_WAIT_TIME_W0_614ms     0xFF
#define COLOR7_WAIT_TIME_W1_0_029sec  0xFF
#define COLOR7_WAIT_TIME_W1_2_45sec   0xAB
#define COLOR7_WAIT_TIME_W1_7_4sec    0xFF
/** \} */

/**
 * \defgroup persistence_register Persistence Register
 * \{
 */
#define COLOR7_PERS_EVERY_RGBC   0x00
#define COLOR7_PERS_CLEAR_CH_1   0x01
#define COLOR7_PERS_CLEAR_CH_2   0x02
#define COLOR7_PERS_CLEAR_CH_3   0x03
#define COLOR7_PERS_CLEAR_CH_5   0x04
#define COLOR7_PERS_CLEAR_CH_10  0x05
#define COLOR7_PERS_CLEAR_CH_15  0x06
#define COLOR7_PERS_CLEAR_CH_20  0x07
#define COLOR7_PERS_CLEAR_CH_25  0x08
#define COLOR7_PERS_CLEAR_CH_30  0x09
#define COLOR7_PERS_CLEAR_CH_35  0x0A
#define COLOR7_PERS_CLEAR_CH_40  0x0B
#define COLOR7_PERS_CLEAR_CH_45  0x0C
#define COLOR7_PERS_CLEAR_CH_50  0x0D
#define COLOR7_PERS_CLEAR_CH_55  0x0E
#define COLOR7_PERS_CLEAR_CH_60  0x0F
/** \} */

/**
 * \defgroup config_register Configuration Register
 * \{
 */
#define COLOR7_CFG_WAIT_LONG  0x01
/** \} */

/**
 * \defgroup control_register Control Register
 * \{
 */
#define COLOR7_CTRL_GAIN_x1   0x00
#define COLOR7_CTRL_GAIN_x4   0x01
#define COLOR7_CTRL_GAIN_x16  0x02
#define COLOR7_CTRL_GAIN_x60  0x03
/** \} */

/**
 * \defgroup color_register Color Register
 * \{
 */
#define COLOR7_COLOR_DATA_CLEAR  0x14
#define COLOR7_COLOR_DATA_RED    0x16
#define COLOR7_COLOR_DATA_GREEN  0x18
#define COLOR7_COLOR_DATA_BLUE   0x1A
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

} color7_t;

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

} color7_cfg_t;

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
void color7_cfg_setup ( color7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param color7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COLOR7_RETVAL color7_init ( color7_t *ctx, color7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Color7 click.
 *
 * @note The default click set contains:
 * <pre>
 *    -  Register enable
 *         ** COLOR7_ENABLE_RGBC_INTERRUPT
 *         ** COLOR7_ENABLE_WAIT
 *         ** COLOR7_ENABLE_RGBC
 *         ** COLOR7_POWER_ON
 *    - Register ctrl
 *         ** COLOR7_CTRL_GAIN_x16
 *    - RGBC time
 *         ** COLOR7_RGBC_TIME_700ms
 * </pre>
 */
void color7_default_cfg ( color7_t *ctx );

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
void color7_generic_write ( color7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void color7_generic_read ( color7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for read color ratio
 *
 * @param ctx      Click object.
 * @param color    Color register which be read
 * @retval color ratio data
 *
 * Use this function when reading one color ratio
 */
float color7_read_color_ratio ( color7_t *ctx, uint8_t color );

/**
 * @brief Functions for read color value
 *
 * @param ctx      Click object.
 * @retval Color value in HSL
 *
 * @note This functions reas 3 color filters and Clear Filters and converts the resulting color from RGBC to HSL. The color range is between 0.0650 and 1.0000.
 */
float color7_get_color_value ( color7_t *ctx );

/**
 * @brief Functions for detect colors
 *
 * @retval Color flag
 *
 * @note
 * <pre>
 *    Detect color
 *       PINK color   - from 0.920  to 0.974
 *       PURPLE color - from 0.6201 to 0.919
 *       BLUE color   - from 0.521  to 0.620
 *       CYAN color   - from 0.430  to 0.520
 *       GREEN color  - from 0.300  to 0.429
 *       YELLOW color - from 0.019  to 0.200
 *       RED color    - from 0.0005 to 0.018
 * </pre>
 */
uint8_t color7_get_color( color7_t *ctx );

/**
 * @brief Get interrut pin state
 *
 * @retval INT pin state
 */
uint8_t color7_get_interrupt_state ( color7_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _COLOR7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
