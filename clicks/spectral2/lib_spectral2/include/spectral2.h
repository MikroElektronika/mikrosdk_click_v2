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
 * \brief This file contains API for Spectral 2 Click driver.
 *
 * \addtogroup spectral2 Spectral 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SPECTRAL2_H
#define SPECTRAL2_H

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
#define SPECTRAL2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SPECTRAL2_RETVAL  uint8_t

#define SPECTRAL2_OK           0x00
#define SPECTRAL2_INIT_ERROR   0xFF
/** \} */


/**
 * \defgroup setup_config Setup Configuration
 * \{
 */
#define SPECTRAL2_SOFT_RESET          0x01 << 6
#define SPECTRAL2_NORMAL_OPERATION    0x00 << 6
#define SPECTRAL2_INT_ENABLE          0x01 << 5
#define SPECTRAL2_INT_DISABLE         0x00 << 5
#define SPECTRAL2_GAIN_1X             0x00 << 4
#define SPECTRAL2_GAIN_3_7X           0x01 << 4
#define SPECTRAL2_GAIN_16X            0x02 << 4
#define SPECTRAL2_GAIN_64X            0x03 << 4
#define SPECTRAL2_MODE_0              0x00 << 2
#define SPECTRAL2_MODE_1              0x01 << 2
#define SPECTRAL2_MODE_2              0x02 << 2
#define SPECTRAL2_MODE_3              0x03 << 2
/** \} */


/**
 * \defgroup led_ctrl Led Control
 * \{
 */
#define SPECTRAL2_LED_DRV_CURRENT_12_5mA    0x00 << 4
#define SPECTRAL2_LED_DRV_CURRENT_25mA      0x01 << 4
#define SPECTRAL2_LED_DRV_CURRENT_50mA      0x02 << 4
#define SPECTRAL2_LED_DRV_CURRENT_100mA     0x03 << 4
#define SPECTRAL2_LED_DRV_ENABLE            0x01 << 2
#define SPECTRAL2_LED_DRV_DISABLE           0x00 << 2
#define SPECTRAL2_LED_IND_CURRENT_1mA       0x00 << 1
#define SPECTRAL2_LED_IND_CURRENT_2mA       0x01 << 1
#define SPECTRAL2_LED_IND_CURRENT_4mA       0x02 << 1
#define SPECTRAL2_LED_IND_CURRENT_8mA       0x03 << 1
#define SPECTRAL2_LED_IND_ENABLE            0x01
#define SPECTRAL2_LED_IND_DISABLE           0x00
/** \} */

/**
 * \defgroup sensr_calibrated_data Sensor Calibrated Data
 * \{
 */
#define SPECTRAL2_CALIBRATED_DATA_V      0x14
#define SPECTRAL2_CALIBRATED_DATA_B      0x18
#define SPECTRAL2_CALIBRATED_DATA_G      0x1C
#define SPECTRAL2_CALIBRATED_DATA_Y      0x20
#define SPECTRAL2_CALIBRATED_DATA_O      0x24
#define SPECTRAL2_CALIBRATED_DATA_R      0x28
/** \} */

// Sensor Data
/**
 * \defgroup sensr_data Sensor Data
 * \{
 */
#define SPECTRAL2_DATA_V       0x08
#define SPECTRAL2_DATA_B       0x0A
#define SPECTRAL2_DATA_G       0x0C
#define SPECTRAL2_DATA_Y       0x0E
#define SPECTRAL2_DATA_O       0x10
#define SPECTRAL2_DATA_R       0x12
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

    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;

    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} spectral2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} spectral2_cfg_t;

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
void spectral2_cfg_setup ( spectral2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SPECTRAL2_RETVAL spectral2_init ( spectral2_t *ctx, spectral2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Spectral2 click.
 */

/**
 * @brief Function for configuration measurements
 *
 * @param ctx  Click object.
 *
 * Options for Configuration:
 * <pre>
     Soft Reset ( 0 - automatically after the reset / 1 - soft reset )
     Enable interrupt pin output ( 1 - Enable / 0 - Disable )
     Sensor Channel Gain Setting ( 1x, 3.7x, 16x or  64x)
     Data Conversion Type:
      <pre>
        Mode 0 -  reads V, B, G and Y data
        Mode 1 -  reads G, Y, O and R data
        Mode 2 -  reads all data
        Mode 3 -  reads V, B, G, Y, O and R in One-Shot mode
      </pre>
   </pre>
 */
void spectral2_default_cfg ( spectral2_t *ctx );

/**
 * @brief Generic write function
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void spectral2_generic_write ( spectral2_t *ctx, uint8_t reg, uint8_t data_buf );

/**
 * @brief Generic read function
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @return             Read data value.
 *
 * @description This function reads data from the desired register.
 */
uint8_t spectral2_generic_read ( spectral2_t *ctx, uint8_t reg );

/**
 * @brief Reset function
 *
 * @param ctx          Click object.
 *
 * @description This function resets the chip.
 */
void spectral2_reset ( spectral2_t *ctx );

/**
 * @brief Integration time function
 *
 * @param ctx          Click object.
 * @param cur_time     Data that will be written in the integration time register.
 *
 * @description Function for calculating integration time.
 *
 * @note Integration time = <value> * 2.8ms (default 0xFF)
 */
void spectral2_set_integration_time ( spectral2_t *ctx, uint8_t cur_time );

/**
 * @brief Read temperature function
 *
 * @param ctx          Click object.
 *
 * @return Device temperature data byte in (deg C).
 *
 * @description Function for reading device temperature.
 */
uint8_t spectral2_get_temperature ( spectral2_t *ctx );

/**
 * @brief Led ctrl and setting function
 *
 * @param ctx          Click object.
 * @param led_data     Data that will be written in the LED control register.
 *
 * @description Function for led control and settings led.
 *
 * @note Options:
 * <pre>
     LED_DRV current limit ( 12.5mA, 25mA, 50mA or 100mA )
     Enable LED_DRV ( 1 - Enable / 0 - Disable )
     LED_IND current limit ( 1mA, 2mA, 4mA or 8mA )
     Enable LED_IND ( 1 - Enable / 0 - Disable )
  </pre>
 */
void spectral2_led_control ( spectral2_t *ctx, uint8_t led_data );

/**
 * @brief Read data function
 *
 * @param ctx          Click object.
 * @param dataReg      Value from which the filter will be read.
 *
 * @return 16 bit signed data that is read from the register.
 *
 * @description Function for reading the measured data.
 */
int16_t spectral2_get_data ( spectral2_t *ctx, uint8_t data_reg );

/**
 * @brief Reads calibrated data function
 *
 * @param ctx          Click object.
 * @param dataReg      Value from which the filter will be read.
 *
 * @return Floating point data that is read from the register.
 *
 * @description Function reads the calibrated data.
 */
int32_t spectral2_get_calibrated_data ( spectral2_t *ctx, uint8_t data_reg );

#ifdef __cplusplus
}
#endif
#endif  // SPECTRAL2_H

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------ END
