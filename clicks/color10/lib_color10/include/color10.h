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
 * \brief This file contains API for Color 10 Click driver.
 *
 * \addtogroup color10 Color 10 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR10_H
#define COLOR10_H

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
#define COLOR10_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR10_RETVAL  uint8_t

#define COLOR10_OK           0x00
#define COLOR10_INIT_ERROR   0xFF
/** \} */

#define       COLOR10_SLAVE_ADDR                              0x10

#define       COLOR10_CMD_REG_CFG                             0x00
#define       COLOR10_CMD_REG_C                               0x04
#define       COLOR10_CMD_REG_R                               0x05
#define       COLOR10_CMD_REG_G                               0x06
#define       COLOR10_CMD_REG_B                               0x07
#define       COLOR10_CMD_REG_IR                              0x08
#define       COLOR10_CMD_REG_ID                              0x0C

#define       COLOR10_DEVICE_ID                               0x28

#define       COLOR10_COLOR_ORANGE                            0x11
#define       COLOR10_COLOR_RED                               0x22
#define       COLOR10_COLOR_PINK                              0x33
#define       COLOR10_COLOR_PURPLE                            0x44
#define       COLOR10_COLOR_BLUE                              0x55
#define       COLOR10_COLOR_CYAN                              0x66
#define       COLOR10_COLOR_GREEN                             0x77
#define       COLOR10_COLOR_YELLOW                            0x88
#define       COLOR10_COLOR_OTHER                             0x99

#define       COLOR10_CFG_HIGH_DYNAMIC_RANGE_1_3            0x0040
#define       COLOR10_CFG_HIGH_DYNAMIC_RANGE_1              0x0000
#define       COLOR10_CFG_INTEGRATION_TIME_SETT_50_MS       0x0000
#define       COLOR10_CFG_INTEGRATION_TIME_SETT_100_MS      0x0010
#define       COLOR10_CFG_INTEGRATION_TIME_SETT_200_MS      0x0020
#define       COLOR10_CFG_INTEGRATION_TIME_SETT_400_MS      0x0030
#define       COLOR10_CFG_AUTO_MODE                         0x0000
#define       COLOR10_CFG_FORCE_MODE                        0x0008
#define       COLOR10_CFG_TRIGGER_NO                        0x0000
#define       COLOR10_CFG_TRIGGER_ONE_TIME                  0x0004
#define       COLOR10_CFG_POWER_ON                          0x0000
#define       COLOR10_CFG_SHUT_DOWN                         0x8001
#define       COLOR10_CFG_POWER_ON_G_C_IR                   0x4000
#define       COLOR10_CFG_GAIN_1_X1                         0x0000
#define       COLOR10_CFG_GAIN_1_X2                         0x1000
#define       COLOR10_CFG_GAIN_1_X4                         0x2000
#define       COLOR10_CFG_GAIN_2_X1_2                       0x0C00
#define       COLOR10_CFG_GAIN_2_X1                         0x0000
#define       COLOR10_CFG_GAIN_2_X2                         0x0400
#define       COLOR10_CFG_GAIN_2_X4                         0x0800

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

} color10_t;

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

} color10_cfg_t;

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
void color10_cfg_setup ( color10_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COLOR10_RETVAL color10_init ( color10_t *ctx, color10_cfg_t *cfg );

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
void color10_generic_write ( color10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param cmd_addr     Command address.
 *
 * @returns            Data read from given address.
 * 
 * @description This function reads data from the desired register.
 */
uint16_t color10_generic_read ( color10_t *ctx, uint8_t cmd_addr );

/**
 * @brief Configuration function
 *
 * @param ctx          Click object.
 * @param cfg_data     Configuration data.
 * 
 * @description        This function configures the click according to the config data.
 */
void color10_config ( color10_t *ctx, uint16_t cfg_data );

/**
 * @brief ID retrieval function
 * 
 * @param ctx          Click object.
 * 
 * @returns            ID
 * 
 * @description        This function returns the ID.
 */
uint8_t color10_get_id ( color10_t *ctx );

/**
 * @brief Color ratio function
 * 
 * @param ctx           Click object.
 * @param color_cmd_reg Color command register.
 * 
 * @returns            Color ratio
 * 
 * @description        This function reads the color ratio from given register.
 */
float color10_read_color_ratio ( color10_t *ctx, uint8_t color_cmd_reg );

/**
 * @brief Color value function
 * 
 * @param ctx           Click object.
 * 
 * @returns             Color value.
 * 
 * @description        This function calculates the color value.
 */
float color10_get_color_value ( color10_t *ctx );

/**
 * @brief Color retrieval function
 * 
 * @param color_value          Color value
 * 
 * @returns                    Color ID macro
 * 
 * @description        This function identifies the color using the color value.
 */
uint8_t color10_get_color ( float color_value );


#ifdef __cplusplus
}
#endif
#endif  // _COLOR10_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
