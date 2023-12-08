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
 * \brief This file contains API for 3D Hall 2 Click driver.
 *
 * \addtogroup c3dhall2 3D Hall 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C3DHALL2_H
#define C3DHALL2_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define C3DHALL2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * @brief 3D Hall 2 device address setting.
 * @details Specified setting for device slave address selection of
 * 3D Hall 2 Click driver.
 */
#define   C3DHALL2_DEVICE_ADDRESS               0x5E

/**
 * \defgroup mode_1_settings Mode 1 settings
 * \{
 */
#define   C3DHALL2_M1_I2C_SLAVE_ADDRESS_0       0x00
#define   C3DHALL2_M1_I2C_SLAVE_ADDRESS_1       0x20
#define   C3DHALL2_M1_I2C_SLAVE_ADDRESS_2       0x40
#define   C3DHALL2_M1_I2C_SLAVE_ADDRESS_3       0x60
#define   C3DHALL2_M1_INTERRUPT_ENABLE          0x04
#define   C3DHALL2_M1_INTERRUPT_DISABLE         0x00
#define   C3DHALL2_M1_FAST_MODE_ENABLE          0x02
#define   C3DHALL2_M1_FAST_MODE_DISABLE         0x00
#define   C3DHALL2_M1_LOW_POWER_MODE_ENABLE     0x01
#define   C3DHALL2_M1_LOW_POWER_MODE_DISABLE    0x00
/** \} */

/**
 * \defgroup mode_2_settings Mode 2 settings
 * \{
 */
#define   C3DHALL2_M2_TEMPERATURE_ENABLE       0x00
#define   C3DHALL2_M2_TEMPERATURE_DISABLE      0x80
#define   C3DHALL2_M2_LOW_POWER_PERIOD_100MS   0x00
#define   C3DHALL2_M2_LOW_POWER_PERIOD_12MS    0x40
#define   C3DHALL2_M2_PARITY_TEST_ENABLE       0x00
#define   C3DHALL2_M2_PARITY_TEST_DISABLE      0x20
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

} c3dhall2_t;

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

} c3dhall2_cfg_t;

/**
 * @brief 3D Hall 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL2_OK = 0,
    C3DHALL2_ERROR = -1

} c3dhall2_return_value_t;

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
void c3dhall2_cfg_setup ( c3dhall2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t c3dhall2_init ( c3dhall2_t *ctx, c3dhall2_cfg_t *cfg );

/**
 * @brief Default configuration initialization function.
 *
 * @param ctx Click object.
 *
 * @description This function initializes default configuration.
 * @note This function sets values to required registers.
 */
err_t c3dhall2_default_cfg( c3dhall2_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to register.
 */
err_t c3dhall2_write_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from register.
 */
err_t c3dhall2_read_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Functions for getting Hall axis data and Temperature data
 *
 * @param ctx         Click object.
 * @param axis_data   Hall axis data in mT - (axisData[0] - X axis, axisData[1] - Y axis, axisData[2] - Z axis)
 * @param temp_data   Temperature data in C 
 * 
 * @description This function gets temperature and axis data.
 */
err_t c3dhall2_get_axis_temp_data ( c3dhall2_t *ctx, float *axis_data, float *temp_data );

/**
 * @brief Functions for settings chip for measurement
 *
 * @param ctx         Click object
 * @param settings1   Mode 1 register settings
 * @param settings2   Mode 2 register settings 
 * 
 * @description This function configures the chip for measurement.
 * @note  Options - modes :
 *  * <pre>
 * Options for settings:
 *  Mode 1 :
 *    Slave address (0,1, 2 or 3)
 *		Interrupt (Enable or Disable)
 *		Fast mode (Enable or Disable)
 *		Low power mode (Enable or Disable)
 *	Mode 2 :
 *	    Temperature (Enable or Disable)
 *		Low power period (100ms or 12ms)
 *		Parity test (Enable or Disable)
 *</pre>
 */
err_t c3dhall2_configuration ( c3dhall2_t *ctx, uint8_t settings1, uint8_t settings2 );


#ifdef __cplusplus
}
#endif
#endif  // _C3DHALL2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
