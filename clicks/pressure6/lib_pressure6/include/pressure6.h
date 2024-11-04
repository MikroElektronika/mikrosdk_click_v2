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
 * \brief This file contains API for Pressure 6 Click driver.
 *
 * \addtogroup pressure6 Pressure 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE6_H
#define PRESSURE6_H

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
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define PRESSURE6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.dri = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */
/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE6_RETVAL  uint8_t

#define PRESSURE6_OK           0x00
#define PRESSURE6_INIT_ERROR   0xFF
/** \} */
/**
 * \defgroup macros Mode control
 * \{
 */
#define PRESSURE6_MC_AVE_NUM_SINGLE                  0x00
#define PRESSURE6_MC_AVE_NUM_2_TIMES                 0x20
#define PRESSURE6_MC_AVE_NUM_4_TIMES                 0x40
#define PRESSURE6_MC_AVE_NUM_8_TIMES                 0x60
#define PRESSURE6_MC_AVE_NUM_16_TIMES                0x80
#define PRESSURE6_MC_AVE_NUM_32_TIMES                0xA0
#define PRESSURE6_MC_AVE_NUM_64_TIMES                0xC0
#define PRESSURE6_MC_AVE_NUM_PROHIBITED              0xE0
#define PRESSURE6_MC_DATA_READY_ENABLED              0x10
#define PRESSURE6_MC_DATA_READY_DISABLED             0x00
#define PRESSURE6_MC_FULL_DATA_ENABLED               0x08
#define PRESSURE6_MC_FULL_DATA_DISABLED              0x00
#define PRESSURE6_MC_WATER_MARK_ENABLED              0x04
#define PRESSURE6_MC_WATER_MARK_DISABLED             0x00
#define PRESSURE6_MC_MODE_STAND_BY                   0x00
#define PRESSURE6_MC_MODE_ONE_SHOT                   0x01
#define PRESSURE6_MC_MODE_CONTINUOUS                 0x02
#define PRESSURE6_REG_MODE_CONTROL                   0x14
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

    digital_in_t dri;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} pressure6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t dri;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} pressure6_cfg_t;

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
void pressure6_cfg_setup ( pressure6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
PRESSURE6_RETVAL pressure6_init ( pressure6_t *ctx, pressure6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pressure6 Click.
 * @note 
 * <pre>
 * Powers on the module
 * Sets the default configuration registers values.
 * </pre>
 */
void pressure6_default_cfg ( pressure6_t *ctx );

/**
 * @brief Byte write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_in      Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void pressure6_write_byte( pressure6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Byte read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @returns            Data from the register.
 *
 * @description This function reads data from the desired register.
 */
uint8_t pressure6_read_byte( pressure6_t *ctx, uint8_t reg);

/**
 * @brief Pressure value.
 * 
 * @param ctx          Click object.
 *
 * @returns            Pressure value.
 *
 * @description This function finds pressure value.
 */
uint16_t pressure6_get_pressure( pressure6_t *ctx );

/**
 * @brief Temperature value.
 * 
 * @param ctx          Click object.
 *
 * @returns            Temperature value.
 *
 * @description This function finds temperature value.
 */
uint8_t pressure6_get_temperature( pressure6_t *ctx );

/**
 * @brief Interupt.
 * 
 * @param ctx          Click object.
 *
 * @returns            Pin state.
 *
 * @description This function interupts the program.
 */
uint8_t pressure6_get_interrupt( pressure6_t *ctx );

/**
 * @brief Status.
 * 
 * @param ctx          Click object.
 *
 * @returns            Status.
 *
 * @description This function finds status of the register.
 */
uint8_t pressure6_get_status( pressure6_t *ctx);

/**
 * @brief Power ON
 * 
 * @param ctx          Click object.
 *
 * @description This function turns on the power.
 */
void pressure6_power_on( pressure6_t *ctx );

/**
 * @brief Power OFF
 * 
 * @param ctx          Click object.
 *
 * @description This function turns off the power.
 */
void pressure6_power_off( pressure6_t *ctx);

/**
 * @brief Waits for new data.
 * 
 * @param ctx          Click object.
 *
 * @description This function delays the time of getting new data.
 */
void pressure6_waiting_for_new_data( pressure6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE6_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
