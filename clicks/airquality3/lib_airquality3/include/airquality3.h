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
 * \brief This file contains API for Air quality 3 Click driver.
 *
 * \addtogroup airquality3 Air quality 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AIRQUALITY3_H
#define AIRQUALITY3_H

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
#define AIRQUALITY3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.wke = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AIRQUALITY3_RETVAL  uint8_t

#define AIRQUALITY3_OK           0x00
#define AIRQUALITY3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define AIRQUALITY3_REG_ID               0x20
#define AIRQUALITY3_REG_ERROR_ID         0xE0
#define AIRQUALITY3_REG_STATUS           0x00
#define AIRQUALITY3_REG_HW_VERSION       0x21
#define AIRQUALITY3_REG_FW_BOOT_VERSION  0x23
#define AIRQUALITY3_REG_FW_APP_VERSION   0x24
#define AIRQUALITY3_REG_SW_RESET         0xFF
#define AIRQUALITY3_REG_ALG_DATA         0x02
#define AIRQUALITY3_REG_RAW_DATA         0x03
#define AIRQUALITY3_REG_ENV_DATA         0x05
#define AIRQUALITY3_REG_NTC              0x06
#define AIRQUALITY3_REG_MEAS_MODE        0x01
#define AIRQUALITY3_REG_BASELINE         0x11
/** \} */

/**
 * \defgroup meas_mode Measurement mode
 * \{
 */
#define AIRQUALITY3_DRIVE_MODE_0  ( 0x00 << 4 )
#define AIRQUALITY3_DRIVE_MODE_1  ( 0x01 << 4 )
#define AIRQUALITY3_DRIVE_MODE_2  ( 0x02 << 4 )
#define AIRQUALITY3_DRIVE_MODE_3  ( 0x03 << 4 )
#define AIRQUALITY3_DRIVE_MODE_4  ( 0x04 << 4 )
#define AIRQUALITY3_INT_DATARDY_0 ( 0x00 << 3 )
#define AIRQUALITY3_INT_DATARDY_1 ( 0x01 << 3 )
#define AIRQUALITY3_INT_THRESH_0  ( 0x00 << 2 )
#define AIRQUALITY3_INT_THRESH_1  ( 0x01 << 2 )
/** \} */

/**
 * \defgroup app_data APP data
 * \{
 */
#define AIRQUALITY3_APP_START   0xF4
#define AIRQUALITY3_APP_VERIFY  0xF3
#define AIRQUALITY3_APP_DATA    0xF2
#define AIRQUALITY3_APP_ERASE   0xF1
/** \} */

/**
 * \defgroup device_slave Device Slave Address
 * \{
 */
#define AIRQUALITY3_DEVICE_SLAVE_ADDRESS 0x5A
/** \} */

/**
 * \defgroup power_state Power state
 * \{
 */
#define AIRQUALITY3_POWER_STATE_ON 0
#define AIRQUALITY3_POWER_STATE_OFF 1
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
    digital_out_t wke;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} airquality3_t;

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
    pin_name_t wke;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} airquality3_cfg_t;

/**
 * @brief Info structure definition.
 */
typedef struct
{
    uint8_t device_id;
    uint8_t hw_ver;
    uint8_t fw_boot_ver;
    uint8_t fw_app_ver;

}airguality3_info_t;

/**
 * @brief Air data structure definition.
 */
typedef struct
{
    uint16_t co2;
    uint16_t tvoc;
    uint16_t raw_data;
    uint8_t m_status;

}airquality3_air_data_t;

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
void airquality3_cfg_setup ( airquality3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AIRQUALITY3_RETVAL airquality3_init ( airquality3_t *ctx, airquality3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for AirQuality3 click.
 *
 * @note The default configuration is set:
 * <pre>
 *    -  Set measurement mode : AIRQUALITY3_DRIVE_MODE_4 | AIRQUALITY3_INT_DATARDY_1
 * </pre>
 */
void airquality3_default_cfg ( airquality3_t *ctx );

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
void airquality3_generic_write ( airquality3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void airquality3_generic_read ( airquality3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Reads status
 *
 * @param ctx          Click object.
 * @return  (8-bit) Status data
 */
uint8_t airquality3_get_starus ( airquality3_t *ctx );

/**
 * @brief Get device info
 *
 * @param ctx          Click object.
 * @param info  Structure ( Device ID, HW ver, FW boot ver, FW app ver.. )
 *
 */
void airquality3_get_device_info ( airquality3_t *ctx, airguality3_info_t *info );

/**
 * @brief Software reset
 *
 * @param ctx          Click object.
 * @param reset    4 bytes for reset chip
 *
 * @note
 * <pre>
 *     If the correct is 4 bytes (0x11 0xE5 0x72 0x8A) are written
 *     to this register in a single sequence the device will reset
 *     and return to BOOT mode.
 * </pre>
 */
void airquality3_software_reset ( airquality3_t *ctx, uint32_t reset );    // 0x11,0xE5,0x72,0x8A

/**
 * @brief Get CO2 and TVOC data
 *
 * @param ctx          Click object.
 * @param air_data    Structure for air quality data storage
 *
 * @note
 * <pre>
 *    This function returns a lot of data.
 *    The first data is the CO2 value,
 *    following the TVOC value, and the status register for CO2 and TVOC and RAW_DATA value.
 * </pre>
 * @return Error ID value.
 */
uint8_t airquality3_get_co2_and_tvoc ( airquality3_t *ctx, airquality3_air_data_t *air_data );


/**
 * @brief Function reads raw ADC data values for resistance and current source used.
 *
 * @param ctx          Click object.
 * @param raw_data    pointer to the buffer when data will be storaged
 */
void airquality3_get_raw_data ( airquality3_t *ctx, uint16_t *raw_data );

/**
 * @brief Temperature and humidity data settings
 *
 * @param ctx          Click object.
 * @param _data    4 bytes data for settings temperature and huminidy
 *
 * @note
 * <pre>
 *     The internal algorithm uses these values (or default values if
 *     not set by the application) to compensate for changes in
 *     relative humidity and ambient temperature.
 * </pre>
 */
void airquality3_set_environment_data ( airquality3_t *ctx, uint32_t env_data );    // 0x11,0xE5,0x72,0x8A

/**
 * @brief Get NTC value
 *
 * @param ctx          Click object.
 * @param data_buf    pointer to the buffer when data will be storaged
 *
 * @note
 * <pre>
 *     Four bytes read only a register that contains voltage across
 *     resistor (RREF) and voltage across the NTC resistor
 *     which determines the ambient temperature.
 * </pre>
 */
void airquality3_get_ntc_data ( airquality3_t *ctx, uint8_t *data_buf );

/**
 * @brief Function for settings sensor drive mode and interrupts.
 *
 * @param ctx          Click object.
 * @param mode    data to be written into the meas register
 *
 * @note set mode options:
 * <pre>
 * - mode:
 *   Mode 0 - Idle ( Measurements are disabled in this mode )
 *   Mode 1 - Constant power mode, IAQ measurement every second
 *   Mode 2 - Pulse heating mode IAQ measurement every 10 seconds
 *   Mode 3 - Low power pulse heating mode IAQ measurement every 60 seconds
 *   Mode 4 - Constant power mode, sensor measurement every 250ms
 * - set interrupts:
 *   0: Interrupt generation is disabled
 *   1: The nINT signal is asserted (driven low) when a new sample is ready in multiData register.
 * - set thresholds:
 *   0: Interrupt mode (if enabled) operates normally
 *   1: Interrupt mode (if enabled) only asserts the nINT signal (driven low) if the new
 *      ALG_RESULT_DATA crosses one of the thresholds set in the THRESHOLDS register
 *      by more than the hysteresis value (also in the THRESHOLDS register).
 *</pre>
 */
void airquality3_set_measurement_mode ( airquality3_t *ctx, uint8_t mode );

/**
 * @brief Function for settings baseline value
 *
 * @param ctx          Click object.
 * @param baseline   2 bytes data to be written into the baseline register
 *
 * @note
 * <pre>
 *    This function is used to correct the measurement,
 *    and set the baseline value that the algorithm uses to measure the CO2 and TVOC values.
 * </pre>
 */
void airquality3_set_baseline ( airquality3_t *ctx, uint16_t baseline );

/**
 * @brief function to start APP task
 *
 * @param ctx          Click object.
 * @param app_task   1 bytes data to be written in register
 *
 * @note Task options:
 * <pre>
 *   App start - Application start. This command must be executed at the start.
 *   App verify - Starts the process of the bootloader checking though
 *   the application to make sure a full image is valid.
 * </pre>
 */
void airquality3_app_function ( airquality3_t *ctx, uint8_t app_task );

/**
 * @brief Function for power ON/OFF chip
 *
 * @param ctx          Click object.
 * @param prw_state Power state (ON or OFF state)
 */
void airquality3_set_power( airquality3_t *ctx, uint16_t pwr_state );

/**
 * @brief Hardware reset
 *
 * @param ctx          Click object.
 */
void airquality3_hardware_reset( airquality3_t *ctx );

/**
 * @brief Get interrupt state
 *
 * @param ctx          Click object.
 * @return Interrupt state on the INT pin (DRDY)
 */
uint8_t airquality3_get_interrupt_state( airquality3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AIRQUALITY3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
