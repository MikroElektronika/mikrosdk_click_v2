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
 * \brief This file contains API for DAC 3 Click driver.
 *
 * \addtogroup dac3 DAC 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DAC3_H
#define DAC3_H

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
#define DAC3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DAC3_RETVAL  uint8_t

#define DAC3_OK           0x00
#define DAC3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup configuration Configuration 
 * \{
 */
#define DAC3_RESET                0x06
#define DAC3_WAKE_UP              0x09
#define DAC3_VOLATILE_MEM         0x40
#define DAC3_VOLATILE_ALL_MEM     0x60
#define DAC3_VOLATILE_CONF        0x80
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief VRL configuration enumeration.
 */
typedef enum
{
    /*! Vdd pin voltage */
    VDD = 0,
    /*! Vref pin voltage unbuffered */
    VREF_UNBUFFERED = 2,
    /*! Vref pin voltage internally buffered */
    VREF_BUFFERED = 3,

} dac3_vrl_t;

/**
 * @brief Power configuration enumeration.
 */
typedef enum
{
    /*! Normal operation */
    NORMAL,
    /*! 1 kO resistor to ground */
    PD_1,
    /*! 125 kO resistor to ground */
    PD_100,
    /*! 640 kO resistor to ground */
    PD_500

} dac3_pd_t;

/**
 * @brief Gain configuration enumeration.
 */
typedef enum
{
    /*! Gain of 1, with either Vdd or Vref pin used as reference voltage */
    GAIN_1x,
    /*! Gain of 2, only when Vref pin is used as reference voltage */
    GAIN_2x

} dac3_gain_t;

/**
 * @brief DAC configuration object.
 */
typedef struct
{
    dac3_vrl_t vrl;
    dac3_pd_t power;
    dac3_gain_t gain;

} dac3_conf_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{   
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    dac3_conf_t dac_cfg;
    uint8_t slave_address;

} dac3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    dac3_conf_t dac_cfg;
    uint32_t i2c_speed;
    uint8_t i2c_address;

} dac3_cfg_t;

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
void dac3_cfg_setup ( dac3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param dac3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DAC3_RETVAL dac3_init ( dac3_t *ctx, dac3_cfg_t *cfg );

/**
 * @brief Set output voltage function.
 *
 * @param ctx      Click object.
 * @param output   Output voltage.
 *
 * @description This function sets the output voltage on the click module terminal.
 */
void dac3_set_out_voltage ( dac3_t *ctx, uint16_t output );

/**
 * @brief Send command function.
 *
 * @param ctx      Click object.
 * @param cmd      SPI command.
 *
 * @description This function sends a command to the click module using SPI communication.
 */
void dac3_send_command ( dac3_t *ctx, uint8_t cmd );

/**
 * @brief Send command function.
 *
 * @param ctx      Click object.
 * @param cmd      SPI command.
 *
 * @description This function configures the click module.
 * @note In order to use this function properly you need to initialize the dac_cfg object in ctx.
 */
void dac3_write_all_mem ( dac3_t *ctx, uint16_t value );

#ifdef __cplusplus
}
#endif
#endif  // _DAC3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
