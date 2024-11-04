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
 * \brief This file contains API for FAN 4 Click driver.
 *
 * \addtogroup fan4 FAN 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FAN4_H
#define FAN4_H

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
#define FAN4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FAN4_RETVAL  uint8_t

#define FAN4_OK           0x00
#define FAN4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define FAN4_SLAVE_ADDRESS  0x74
/** \} */

/**
 * \defgroup boost_start Boost start
 * \{
 */
#define FAN4_BOOST_START_TIMER_DIS   0x00
#define FAN4_BOOST_START_TIMER_EN    0x01
/** \} */

/**
 * \defgroup fan_mask Fan mask
 * \{
 */
#define FAN4_VOLT_RANGE_CHECK_MASK   0x01
#define FAN4_BS_TIMER_CHECK_MASK     0x02
#define FAN4_THERM_SHTDWN_CHECK_MASK 0x40
#define FAN4_OVERCURR_CHECK_MASK     0x80
#define FAN4_CHECK_OK                0x00
/** \} */

/**
 * \defgroup fan_range Fan range
 * \{
 */
#define FAN4_DAC_LSB                 78
#define FAN4_MIN_VOLT_SCALE          0
#define FAN4_MAX_VOLT_SCALE          4922
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

} fan4_t;

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

} fan4_cfg_t;

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
void fan4_cfg_setup ( fan4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
FAN4_RETVAL fan4_init ( fan4_t *ctx, fan4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Fan4 Click.
 */
void fan4_default_cfg ( fan4_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param cmd          Command.
 */
void fan4_generic_write ( fan4_t *ctx, uint8_t cmd);

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param data_out     Output data buf
 */
void fan4_generic_read ( fan4_t *ctx, uint8_t *data_out );

/**
 * @brief Set output voltage.
 *
 * @param ctx                 Click object.
 * @param output_volt         Output voltage
 * @param boost_start_timer   boost timer
 */
FAN4_RETVAL fan4_set_output ( fan4_t *ctx, uint16_t output_volt, uint8_t boost_start_timer );

/**
 * @brief Check diagnostic.
 *
 * @param ctx                 Click object.
 * @return Diagnostic return value
 */
uint8_t fan4_check_diagnostic ( fan4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _FAN4_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
