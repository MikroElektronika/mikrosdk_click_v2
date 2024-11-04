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
 * \brief This file contains API for Temp-Hum 9 Click driver.
 *
 * \addtogroup temphum9 Temp-Hum 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM9_H
#define TEMPHUM9_H

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
#define TEMPHUM9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )
  
/** \} */

/**
 * \defgroup temphum_result TempHum result values
 * \{
 */
#define TEMPHUM9_OK                     0
#define TEMPHUM9_ERROR                 -1
/** \} */

/**
 * \defgroup slave_address slave address
 * \{
 */
#define TEMPHUM9_DEVICE_ADDRESS         0x70
/** \} */


/**
 * \defgroup measurement_modes Measurement modes
 * \{
 */
#define TEMPHUM9_NORMAL_MODE            0x00
#define TEMPHUM9_LOW_POWER_MODE         0x01
/** \} */

/**
 * \defgroup data_address Data
 * \{
 */

#define TEMPHUM9_SINGLE_DATA            0x03
#define TEMPHUM9_DUAL_DATA              0x06
/** \} */

/**
 * \defgroup commands_address commands
 * \{
 */
#define TEMPHUM9_SLEEP                  0xB098
#define TEMPHUM9_WAKEUP                 0x3517
#define TEMPHUM9_SOFT_RESET             0x805D
#define TEMPHUM9_GENERAL_CALL_RESET     0x0006
#define TEMPHUM9_READ_ID                0xEFC8
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

} temphum9_t;

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

} temphum9_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void temphum9_cfg_setup ( temphum9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t temphum9_init ( temphum9_t *ctx, temphum9_cfg_t *cfg );

/**
 * @brief Readinig register content
 * 
 * @param ctx                Click object.
 * @param address            Address of a register to read (command)
 * @param num_data           single for one 16-bit register or dual for two 16-bit registers
 * @param data_out           read data is stored into this array
 *
 * @details This function reads one or two 16-bit registers
 */
void temphum9_read_register ( temphum9_t *ctx, uint16_t address, uint8_t num_data, uint16_t *data_out );

/**
 * @brief  Issuing a command
 * 
 * @param ctx                Click object.
 * @param command            command to be sent to device
 *
 * @details This function issues (sends) command to device
 */
void temphum9_send_command ( temphum9_t *ctx, uint16_t command );

/**
 * @brief  Calculating temperature
 * 
 * @param ctx                Click object.
 * @param data_mode          mode to be used for measurement (normal or low power mode)
 *
 * @details This function performs temperature measurement and calculates temperature
 */
float temphum9_get_temperature ( temphum9_t *ctx, uint8_t data_mode );

/**
 * @brief  Calculating relative humidity
 * 
 * @param ctx                Click object.
 * @param data_mode          mode to be used for measurement (normal or low power mode)
 *
 * @details This function performs relative humidity measurement and calculates relative humidity
 */
float temphum9_get_humidity ( temphum9_t *ctx, uint8_t data_mode );

/**
 * @brief  Calculating temperature and relative humidity
 * 
 * @param ctx                Click object.
 * @param data_mode          mode to be used for measurement (normal or low power mode)
 * @param temp               temperature measurement data
 * @param hum                relative humidity measurement data
 * @details This function performs temperature and relative humidity measurement and calculates temperature and relative humidity
 */
void temhum9_get_data ( temphum9_t *ctx, uint8_t data_mode, float *temp, float *hum );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM9_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
