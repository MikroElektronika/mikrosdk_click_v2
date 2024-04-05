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
 * \brief This file contains API for Clock Gen 2 Click driver.
 *
 * \addtogroup clockgen2 Clock Gen 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CLOCKGEN2_H
#define CLOCKGEN2_H

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
#define CLOCKGEN2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pdn = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.oe = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.dtr = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CLOCKGEN2_RETVAL  uint8_t

#define CLOCKGEN2_OK           0x00
#define CLOCKGEN2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup general_registers General Registers
 * \{
 */

// A0 = A1 = A2 = 0
#define CLOCKGEN2_ADDR                      0x58

#define CLOCKGEN2_PRESCALER_REG             0x02
#define CLOCKGEN2_ADDR_CHANGE_REG           0x0D
#define CLOKCGEN2_AUTO_PRESERVE_ENABLE      0
#define CLOCKGEN2_AUTO_PRESERVE_DISABLE     1
#define CLOCKGEN2_WRITE_EE_REG              0x3F
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

    digital_out_t pdn;
    digital_out_t oe;
    digital_out_t dtr;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} clockgen2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t pdn;
    pin_name_t oe;
    pin_name_t dtr;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} clockgen2_cfg_t;

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
void clockgen2_cfg_setup ( clockgen2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param clockgen2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CLOCKGEN2_RETVAL clockgen2_init ( clockgen2_t *ctx, clockgen2_cfg_t *cfg );

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
void clockgen2_generic_write ( clockgen2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void clockgen2_generic_read ( clockgen2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set dtr pin function.
 *
 * @param ctx          Click object.
 * @param state        Pin state value.
 *
 * @description Set the state of the DTR pin.
 */
void clockgen2_set_dtr_pin ( clockgen2_t *ctx, uint8_t state );

/**
 * @brief Set pdn pin function.
 *
 * @param ctx          Click object.
 * @param state        Pin state value.
 *
 * @description Set the state of the PDN pin.
 */
void clockgen2_set_pdn_pin ( clockgen2_t *ctx, uint8_t state );

/**
 * @brief Set oe pin function.
 *
 * @param ctx          Click object.
 * @param state        Pin state value.
 *
 * @description Set the state of the OE pin.
 */
void clockgen2_set_oe_pin ( clockgen2_t *ctx, uint8_t state );

/**
 * @brief Writing 1B function.
 *
 * @param ctx          Click object.
 * @param w_reg        Write address.
 * @param w_data       Data to be written.
 *
 * @description Function for writing data to a specified register.
 */
void clockgen2_write ( clockgen2_t *ctx, uint8_t w_reg, uint8_t w_data );

/**
 * @brief Prescaler set function.
 *
 * @param ctx          Click object.
 * @param val          Write address.
 *
 * @description Function for setting the main clock prescaler.
 * @note Prescaler range is from 0 - 8.
 */
void clockgen2_set_prescaler ( clockgen2_t *ctx, uint8_t val );

/**
 * @brief Prescaler set function.
 *
 * @param ctx          Click object.
 * @param new_addr     New slave address.
 *
 * @description Function configures the clockgen2 slave address at runtime.
 * @note User can chose between 7 differnet addresses.
 * The default unshifted 7bit address is 0x58.
 */
void clockgen2_change_address ( clockgen2_t *ctx, uint8_t new_addr );

/**
 * @brief Settings save function.
 *
 * @param ctx          Click object.
 *
 * @description Function used for saving the settings to the eeprom if the the auto preserve settings is disabled.
 */
void clockgen2_store_config ( clockgen2_t *ctx );

/**
 * @brief Auto setting preservation function.
 *
 * @param ctx          Click object.
 * @param state        Value to comapre with Enable/Disable registers.
 *
 * @description Function used for enabling/disabling auto settings preservation.
 * @note This option needs to be disabled if the eeprom settings are changed very often to minimize the wear of the eeprom memory.
 */
void clockgen2_auto_setting_preserve ( clockgen2_t *ctx, uint8_t state );

/**
 * @brief Settings save function.
 *
 * @param ctx          Click object.
 * @param state        Pin value.
 *
 * @description Function for enabling/disabling of the clock output.
 */
void clockgen2_output_enable ( clockgen2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _CLOCKGEN2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
