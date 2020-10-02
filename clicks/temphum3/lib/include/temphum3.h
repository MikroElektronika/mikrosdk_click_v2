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
 * \brief This file contains API for TempHum 3 Click driver.
 *
 * \addtogroup temphum3 TempHum 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM3_H
#define TEMPHUM3_H

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
#define TEMPHUM3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM3_RETVAL  uint8_t

#define TEMPHUM3_OK           0x00
#define TEMPHUM3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode Running modes
 * \{
 */
#define TEMPHUM3_MODE_ACTIVE    0x01 
#define TEMPHUM3_MODE_SLEEP     0x00 
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define TEMPHUM3_REG_TEMPERATURE           0x00 
#define TEMPHUM3_REG_HUMIDITY              0x02 
#define TEMPHUM3_REG_INTERRUPT_DRDY        0x04 
#define TEMPHUM3_REG_TEMPERATURE_MAX       0x05 
#define TEMPHUM3_REG_HUMIDITY_MAX          0x06 
#define TEMPHUM3_REG_INTERRUPT_MASK        0x07 
#define TEMPHUM3_REG_TEMP_OFFSET_ADJUST    0x08 
#define TEMPHUM3_REG_HUM_OFFSET_ADJUST     0x09 
#define TEMPHUM3_REG_TEMP_THRESHOLD_HIGH   0x0A 
#define TEMPHUM3_REG_HUM_THRESHOLD_HIGH    0x0C 
#define TEMPHUM3_REG_TEMP_THRESHOLD_LOW    0x0B 
#define TEMPHUM3_REG_HUM_THRESHOLD_LOW     0x0D 
#define TEMPHUM3_REG_RST_DRDY_INT_CONF     0x0E 
#define TEMPHUM3_REG_MEASUREMENT_CONF      0x0F 
#define TEMPHUM3_REG_MANUFACTURER_ID       0xFC 
#define TEMPHUM3_REG_DEVICE_ID             0xFE 
/** \} */

/**
 * \defgroup status_registers Status registers
 * \{
 */
#define TEMPHUM3_STATUS_DRDY        0x80 
#define TEMPHUM3_STATUS_TEMP_HIGH   0x40 
#define TEMPHUM3_STATUS_TEMP_LOW    0x20 
#define TEMPHUM3_STATUS_HUM_HIGH    0x10 
#define TEMPHUM3_STATUS_HUM_LOW     0x08 
/** \} */

/**
 * \defgroup mask_registers Mask registers
 * \{
 */
#define TEMPHUM3_MASK_DRDY         0x80 
#define TEMPHUM3_MASK_TEMP_HIGH    0x40 
#define TEMPHUM3_MASK_TEMP_LOW     0x20 
#define TEMPHUM3_MASK_HUM_HIGH     0x10 
#define TEMPHUM3_MASK_HUM_LOW      0x08 
/** \} */


/**
 * \defgroup configuration_modes Configuration modes
 * \{
 */
#define TEMPHUM3_CONF_NORMAL_MODE   0x00 << 7
#define TEMPHUM3_CONF_SOFT_RESET    0x01 << 7
/** \} */

/**
 * \defgroup output_data_range Output data range 
 * \{
 */
#define TEMPHUM3_CONF_ODR_NO_REPEATED      0x00 << 4
#define TEMPHUM3_CONF_ODR_REPEATED_2MIN    0x01 << 4
#define TEMPHUM3_CONF_ODR_REPEATED_1MIN    0x02 << 4
#define TEMPHUM3_CONF_ODR_REPEATED_10SEC   0x03 << 4
#define TEMPHUM3_CONF_ODR_REPEATED_5SEC    0x04 << 4
#define TEMPHUM3_CONF_ODR_REPEATED_1SEC    0x05 << 4
#define TEMPHUM3_CONF_ODR_REPEATED_500MS   0x06 << 4
#define TEMPHUM3_CONF_ODR_REPEATED_200MS   0x07 << 4
#define TEMPHUM3_CONF_HEATER_OFF           0x00 << 3
#define TEMPHUM3_CONF_HEATER_ON            0x01 << 3
#define TEMPHUM3_CONF_INT_DRDY_HIGH_Z      0x00 << 2
#define TEMPHUM3_CONF_INT_DRDY_ENABLE      0x01 << 2
#define TEMPHUM3_CONF_INT_POL_LOW          0x00 << 1
#define TEMPHUM3_CONF_INT_POL_HIGH         0x01 << 1
#define TEMPHUM3_CONF_INT_MODE_SENSITIVE   0x00
#define TEMPHUM3_CONF_INT_MODE_COMPARATOR  0x01
/** \} */

/**
 * \defgroup measurement_config Measurement config 
 * \{
 */
#define TEMPHUM3_MCONF_TEMP_RES_14BIT   0x00 << 6
#define TEMPHUM3_MCONF_TEMP_RES_11BIT   0x01 << 6
#define TEMPHUM3_MCONF_TEMP_RES_9BIT    0x02 << 6
#define TEMPHUM3_MCONF_HUM_RES_14BIT    0x00 << 5
#define TEMPHUM3_MCONF_HUM_RES_11BIT    0x01 << 5
#define TEMPHUM3_MCONF_HUM_RES_9BIT     0x02 << 5
#define TEMPHUM3_MCONF_HUM_TEMP         0x00 << 1
#define TEMPHUM3_MCONF_TEMP_ONLY        0x01 << 1
#define TEMPHUM3_MCONF_HUM_ONLY         0x02 << 1
#define TEMPHUM3_MCONF_MEAS_START       0x01
#define TEMPHUM3_MCONF_MEAS_NO_ACTION   0x00
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

    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} temphum3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t cs;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} temphum3_cfg_t;

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
void temphum3_cfg_setup ( temphum3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM3_RETVAL temphum3_init ( temphum3_t *ctx, temphum3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TempHum3 click.
 */
void temphum3_default_cfg ( temphum3_t *ctx );

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
void temphum3_generic_write ( temphum3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void temphum3_generic_read ( temphum3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set measurement mode function
 *
 * @param ctx          Click object.
 * @param value        Register address value
 *
 * @description This function sets measurement mode
 */
void temphum3_set_mode ( temphum3_t *ctx, uint8_t value );

/**
 * @brief Set configuration function
 *
 * @param ctx          Click object.
 * @param value        Register address value
 *
 * @description This function configures the measurement values
 */
void temphum3_set_configuration ( temphum3_t *ctx, uint8_t value );

/**
 * @brief Set measurement function
 *
 * @param ctx          Click object.
 *
 * @description This function returns temperature value
 */
void temphum3_set_measurement ( temphum3_t *ctx, uint8_t value );

/**
 * @brief Get temperature function
 *
 * @param ctx          Click object.
 *
 * @description This function returns temperature value
 */
float temphum3_get_temperature ( temphum3_t *ctx );

/**
 * @brief Get humidity function
 * 
 * @param ctx          Click object.
 *
 * @description This function returns humidity value
 */
float temphum3_get_humidity ( temphum3_t *ctx );

/**
 * @brief Get ID function
 * 
 * @param ctx          Click object.
 *
 * @description This function returns ID of the module
 */
uint16_t temphum3_get_id ( temphum3_t *ctx );

/**
 * @brief Get manufacturer's ID function
 * 
 * @param ctx          Click object.
 *
 * @description This function returns manufacturer's ID value
 */
uint16_t temphum3_get_manufacturer_id ( temphum3_t *ctx );

/**
 * @brief Get interrupt status function
 * 
 * @param ctx          Click object.
 *
 * @description This function returns status of an interrupt
 */
uint8_t temphum3_get_status_interrupt ( temphum3_t *ctx, uint8_t mask );

/**
 * @brief Get interrupt mask function
 * 
 * @param ctx          Click object.
 * @param mask         Interrupt mask
 * 
 * @description This function returns interrupt mask value
 */
uint8_t temphum3_get_interrupt_mask ( temphum3_t *ctx, uint8_t mask );

/**
 * @brief Set offset function
 * 
 * @param ctx          Click object.
 * @param reg          Registry value
 * @param value        Buffer value
 *
 * @description This function sets value of a offset
 */
void temphum3_set_offset ( temphum3_t *ctx, uint8_t reg, uint8_t value );

/**
 * @brief Set high temperature function
 * 
 * @param ctx          Click object.
 * @param temp_data    Temperature data value
 *
 * @description This function sets the high temperature value
 */
void temphum3_set_high_temp ( temphum3_t *ctx, uint8_t temp_data );

/**
 * @brief Set low temperature function
 * 
 * @param ctx          Click object.
 * @param temp_data    Temperature data value
 * 
 * @description This function sets the low temperature value
 */
void temphum3_set_low_temp ( temphum3_t *ctx, uint8_t temp_data);

/**
 * @brief Set high humidity function
 * 
 * @param ctx          Click object.
 * @param hum_data     Humidity data value
 * 
 * @description This function sets the high humidity value
 */
void temphum3_set_high_hum( temphum3_t *ctx, uint8_t hum_data);

/**
 * @brief Set low humidity function
 * 
 * @param ctx          Click object.
 * @param hum_data     Humidity data value
 * 
 * @description This function sets high humidity value
 */
void temphum3_set_low_hum( temphum3_t *ctx, uint8_t hum_data);

/**
 * @brief Get maximum humidity function
 * 
 * @param ctx          Click object.
 * 
 * @description This function gets the maximum humidity value
 */
float temphum3_get_max_hum ( temphum3_t *ctx );

/**
 * @brief Get maximum temperature function
 * 
 * @param ctx          Click object.
 * 
 * @description This function gets the maximum temperature value
 */
float temphum3_get_max_temp ( temphum3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
