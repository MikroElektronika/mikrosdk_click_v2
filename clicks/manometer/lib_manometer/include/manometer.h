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
 * \brief This file contains API for Manometer Click driver.
 *
 * \addtogroup manometer Manometer Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MANOMETER_H
#define MANOMETER_H

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
#define MANOMETER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MANOMETER_RETVAL  uint8_t

#define MANOMETER_OK           0x00
#define MANOMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup adc_reset_command  Adc Reset Command
 * \{
 */
#define MANOMETER_CMD_RESET         0x1E
/** \} */

/**
 * \defgroup adc_read_command   Adc Read Command
 * \{
 */
#define MANOMETER_CMD_ADC_READ      0x00
/** \} */

/**
 * \defgroup adc_conversion_command   Adc Conversion Commadn
 * \{
 */
#define MANOMETER_CMD_ADC_CONV      0x40
/** \} */

/**
 * \defgroup adc_d1_conversion  Adc D1 Conversion
 * \{
 */
#define MANOMETER_CMD_ADC_D1        0x00
/** \} */

/**
 * \defgroup adc_d2_conversion  Adc D2 Conversion
 * \{
 */
#define MANOMETER_CMD_ADC_D2        0x10
/** \} */

/**
 * \defgroup adc_osr_256  Adc Osr=256
 * \{
 */
#define MANOMETER_CMD_ADC_256       0x00
/** \} */

/**
 * \defgroup adc_osr_512  Adc Osr=512
 * \{
 */
#define MANOMETER_CMD_ADC_512       0x02
/** \} */

/**
 * \defgroup adc_osr_1024  Adc Osr=1024
 * \{
 */
#define MANOMETER_CMD_ADC_1024      0x04
/** \} */

/**
 * \defgroup adc_osr_2056  Adc Osr=2056
 * \{
 */
#define MANOMETER_CMD_ADC_2048      0x06
/** \} */

/**
 * \defgroup adc_osr_4096  Adc Osr=4096
 * \{
 */
#define MANOMETER_CMD_ADC_4096      0x08
/** \} */

/**
 * \defgroup prom_read_command   Prom Read Command
 * \{
 */
#define MANOMETER_CMD_PROM_RD       0xA0
/** \} */

/**
 * \defgroup output_register_address  Output Register Address
 * \{
 */
#define MANOMETER_OUTPUT_ADDRESS    0x38
/** \} */

/**
 * \defgroup i2c_register_address   I2c Register Address
 * \{
 */
#define MANOMETER_I2C_ADDRESS       0x38

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

} manometer_t;

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

} manometer_cfg_t;

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
void manometer_cfg_setup ( manometer_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param manometer Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MANOMETER_RETVAL manometer_init ( manometer_t *ctx, manometer_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Manometer Click.
 */
void manometer_default_cfg ( manometer_t *ctx );

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
void manometer_generic_write ( manometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void manometer_generic_read ( manometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function read 16-bit data and convert to pressure in mbar.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function read pressure value.
 */
float manometer_get_pressure ( manometer_t *ctx );

/**
 * @brief Function read 11-bit data and convert to temperature in degrees Celsius [ �C ].
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function read temperature value.
 */
float manometer_get_temperature ( manometer_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MANOMETER_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
