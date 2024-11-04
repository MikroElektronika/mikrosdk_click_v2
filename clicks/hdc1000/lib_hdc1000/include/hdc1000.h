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
 * \brief This file contains API for HDC1000 Click driver.
 *
 * \addtogroup hdc1000 HDC1000 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HDC1000_H
#define HDC1000_H

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
#define HDC1000_MAP_MIKROBUS( cfg, mikrobus )    \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HDC1000_RETVAL  uint8_t

#define HDC1000_OK                   0x00
#define HDC1000_INIT_ERROR           0xFF

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define HDC1000_SLAVE_ADDRESS        0x40
/** \} */

/**
 * \defgroup reg Register address
 * \{
 */
#define HDC1000_REG_TEMP             0x00
#define HDC1000_REG_HUMI             0x01
#define HDC1000_REG_CONFIG           0x02
#define HDC1000_REG_SERID_1          0xFB
#define HDC1000_REG_SERID_2          0xFC
#define HDC1000_REG_SERID_3          0xFD
#define HDC1000_REG_MFID             0xFE
#define HDC1000_REG_DEVID            0xFF
/** \} */

/**
 * \defgroup config_val Configuration value
 * \{
 */
#define HDC1000_RST                  0x80
#define HDC1000_HEAT_ON              0x20
#define HDC1000_HEAT_OFF             0x00
#define HDC1000_BOTH_TEMP_HUMI       0x10
#define HDC1000_SINGLE_MEASUR        0x00
#define HDC1000_TEMP_HUMI_14BIT      0x00
#define HDC1000_TEMP_11BIT           0x04
#define HDC1000_HUMI_11BIT           0x01
#define HDC1000_HUMI_8BIT            0x02
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

    digital_in_t rdy;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} hdc1000_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rdy;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} hdc1000_cfg_t;

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
void hdc1000_cfg_setup ( hdc1000_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
HDC1000_RETVAL hdc1000_init ( hdc1000_t *ctx, hdc1000_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for HDC1000 Click.
 * @note
 *      Click default configuration:
 * Sets both temperature and humidity 
 * like values with 14bit resolution.
 * --------------------------------------
 * <pre>
 *     HDC1000_CONFIG
 * --------------------------------------
 *     HDC1000_BOTH_TEMP_HUMI 
 *   | HDC1000_TEMP_HUMI_14BIT
 * </pre>
 */
void hdc1000_default_cfg ( hdc1000_t *ctx );

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
void hdc1000_generic_write ( hdc1000_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void hdc1000_generic_read ( hdc1000_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get temperature value.
 *
 * @param ctx          Click object.
 * 
 * @return
 * Temperature data.
 *
 * @description This function gets temperature data from the HDC1000 sensor.
 */
float hdc1000_get_temperature_data( hdc1000_t *ctx );

/**
 * @brief Get humidity value.
 *
 * @param ctx          Click object.
 * 
 * @return
 * Humidity data.
 *
 * @description This function gets humidity data from the HDC1000 sensor.
 */
float hdc1000_get_humidity_data( hdc1000_t *ctx );

/**
 * @brief Get interrupt state.
 *
 * @param ctx          Click object.
 *
 * @return
 * Interrupt state:
 * <pre>
 *    0 : Not active.
 * </pre>
 * <pre>
 *    1 : Active.
 * </pre>
 * 
 * @description This function gets states of the 
 * RDY ( INT ) pin of the HDC1000 sensor.
 */
uint8_t hdc1000_get_interrupt ( hdc1000_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HDC1000_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
