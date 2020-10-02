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
 * \brief This file contains API for Weather Click driver.
 *
 * \addtogroup weather Weather Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WEATHER_H
#define WEATHER_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define WEATHER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define WEATHER_MASTER_I2C 0
#define WEATHER_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define WEATHER_RETVAL  uint8_t

#define WEATHER_OK           0x00
#define WEATHER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_variables Default variables
 * \{
 */
#define WEATHER_DEF_CHIP_ID 0x60
#define WEATHER_SOFT_RESET 0xB6
/** \} */

/**
 * \defgroup i2c_slave_address Slave address
 * \{
 */
#define WEATHER_I2C_ADDRESS_0 0x76
#define WEATHER_I2C_ADDRESS_1 0x77
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define WEATHER_REG_CHIP_ID          0xD0
#define WEATHER_REG_RESET            0xE0
#define WEATHER_REG_STATUS           0xF3
#define WEATHER_REG_CTRL_MEASUREMENT 0xF4
#define WEATHER_REG_CTRL_HUMIDITY    0xF2
#define WEATHER_REG_CONFIG           0xF5
#define WEATHER_REG_RAW_DATA         0xF7
#define WEATHER_REG_PRESSURE_MSB     0xF7
#define WEATHER_REG_PRESSURE_LSB     0xF8
#define WEATHER_REG_PRESSURE_XLSB    0xF9
#define WEATHER_REG_TEMPERATURE_MSB  0xFA
#define WEATHER_REG_TEMPERATURE_LSB  0xFB
#define WEATHER_REG_TEMPERATURE_XLSB 0xFC
#define WEATHER_REG_HUMIDITY_MSB     0xFD
#define WEATHER_REG_HUMIDITY_LSB     0xFE
/** \} */

/**
 * \defgroup calibration_parameters Calibration parameters
 * \{
 */
#define WEATHER_REG_CALIB_TEMPERATURE 0x88
#define WEATHER_REG_CALIB_TEMP_1_LSB  0x88
#define WEATHER_REG_CALIB_TEMP_1_MSB  0x89
#define WEATHER_REG_CALIB_TEMP_2_LSB  0x8A
#define WEATHER_REG_CALIB_TEMP_2_MSB  0x8B
#define WEATHER_REG_CALIB_TEMP_3_LSB  0x8C
#define WEATHER_REG_CALIB_TEMP_3_MSB  0x8D

#define WEATHER_REG_CALIB_PRESSURE    0x8E
#define WEATHER_REG_CALIB_PRESS_1_LSB 0x8E
#define WEATHER_REG_CALIB_PRESS_1_MSB 0x8F
#define WEATHER_REG_CALIB_PRESS_2_LSB 0x90
#define WEATHER_REG_CALIB_PRESS_2_MSB 0x91
#define WEATHER_REG_CALIB_PRESS_3_LSB 0x92
#define WEATHER_REG_CALIB_PRESS_3_MSB 0x93
#define WEATHER_REG_CALIB_PRESS_4_LSB 0x94
#define WEATHER_REG_CALIB_PRESS_4_MSB 0x95
#define WEATHER_REG_CALIB_PRESS_5_LSB 0x96
#define WEATHER_REG_CALIB_PRESS_5_MSB 0x97
#define WEATHER_REG_CALIB_PRESS_6_LSB 0x98
#define WEATHER_REG_CALIB_PRESS_6_MSB 0x99
#define WEATHER_REG_CALIB_PRESS_7_LSB 0x9A
#define WEATHER_REG_CALIB_PRESS_7_MSB 0x9B
#define WEATHER_REG_CALIB_PRESS_8_LSB 0x9C
#define WEATHER_REG_CALIB_PRESS_8_MSB 0x9D
#define WEATHER_REG_CALIB_PRESS_9_LSB 0x9E
#define WEATHER_REG_CALIB_PRESS_9_MSB 0x9F

#define WEATHER_REG_CALIB_HUMIDITY  0xA1
#define WEATHER_REG_CALIB_HUM_1     0xA1
#define WEATHER_REG_CALIB_HUM_2_LSB 0xE1
#define WEATHER_REG_CALIB_HUM_2_MSB 0xE2
#define WEATHER_REG_CALIB_HUM_3     0xE3
#define WEATHER_REG_CALIB_HUM_4_MSB 0xE4
#define WEATHER_REG_CALIB_HUM_4_LSB 0xE5
#define WEATHER_REG_CALIB_HUM_5_MSB 0xE6
#define WEATHER_REG_CALIB_HUM_6     0xE7
/** \} */

/**
 * \defgroup ctrl_humidity CRTL humidity register
 * \{
 */
#define WEATHER_HUM_OS_SKIPPED 0x00
#define WEATHER_HUM_OS_1X      0x01
#define WEATHER_HUM_OS_2X      0x02
#define WEATHER_HUM_OS_4X      0x03
#define WEATHER_HUM_OS_8X      0x04
#define WEATHER_HUM_OS_16X     0x05
/** \} */

/**
 * \defgroup status Status register
 * \{
 */
#define WEATHER_STATUS_MEASURING 0x08
#define WEATHER_STATUS_IM_UPDATE 0x01
/** \} */

/**
 * \defgroup ctrl_measurement CRTL measurement register
 * \{
 */
#define WEATHER_MCTRL_PRESS_OS_SKIPPED 0x00;
#define WEATHER_MCTRL_PRESS_OS_1X      ( 0x01<<2 )
#define WEATHER_MCTRL_PRESS_OS_2X      ( 0x02<<2 )
#define WEATHER_MCTRL_PRESS_OS_4X      ( 0x03<<2 )
#define WEATHER_MCTRL_PRESS_OS_8X      ( 0x04<<2 )
#define WEATHER_MCTRL_PRESS_OS_16X     ( 0x05<<2 )
#define WEATHER_MCTRL_TEMP_OS_SKIPPED  0x00
#define WEATHER_MCTRL_TEMP_OS_1X       ( 0x01<<5 )
#define WEATHER_MCTRL_TEMP_OS_2X       ( 0x02<<5 )
#define WEATHER_MCTRL_TEMP_OS_4X       ( 0x03<<5 )
#define WEATHER_MCTRL_TEMP_OS_8X       ( 0x04<<5 )
#define WEATHER_MCTRL_TEMP_OS_16X      ( 0x05<<5 )
#define WEATHER_MCTRL_MODE_SLEEP       0x00
#define WEATHER_MCTRL_MODE_FORCED      0x01
#define WEATHER_MCTRL_MODE_NORMAL      0x03
/** \} */

/**
 * \defgroup config Config register
 * \{
 */
#define WEATHER_CFG_STANDBY_TIME_0p5ms  0x00
#define WEATHER_CFG_STANDBY_TIME_62p5ms ( 0x01<<5 )
#define WEATHER_CFG_STANDBY_TIME_125ms  ( 0x02<<5 )
#define WEATHER_CFG_STANDBY_TIME_250ms  ( 0x03<<5 )
#define WEATHER_CFG_STANDBY_TIME_500ms  ( 0x04<<5 )
#define WEATHER_CFG_STANDBY_TIME_1000ms ( 0x05<<5 )
#define WEATHER_CFG_STANDBY_TIME_10ms   ( 0x06<<5 )
#define WEATHER_CFG_STANDBY_TIME_20ms   ( 0x07<<5 )
#define WEATHER_CFG_FILTER_OFF          0x00
#define WEATHER_CFG_FILTER_2            ( 0x01<<2 )
#define WEATHER_CFG_FILTER_4            ( 0x02<<2 )
#define WEATHER_CFG_FILTER_8            ( 0x03<<2 )
#define WEATHER_CFG_FILTER_16           ( 0x04<<2 )
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  weather_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *weather_master_io_t )( struct weather_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct weather_s
{
    digital_out_t cs;

    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
   weather_master_io_t  write_f;
   weather_master_io_t  read_f;
   weather_select_t master_sel;

} weather_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
   // Communication gpio pins 

   pin_name_t scl;
   pin_name_t sda;
   pin_name_t miso;
   pin_name_t mosi;
   pin_name_t sck;
   pin_name_t cs;

   // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   weather_select_t sel;

} weather_cfg_t;

/**
 * @brief Weather data structure definition.
 */
typedef struct
{
    float temperature;
    float pressure;
    float humidity;

} weather_data_t;

/**
 * @brief Measurement configuration structure definition.
 */
typedef struct
{
    // CTRL register
    uint8_t os_temp;
    uint8_t os_press;
    uint8_t os_hum;
    uint8_t mode;

    // CFG register
    uint8_t standby_time;
    uint8_t filter;

} weather_measurement_cfg_t;

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
void weather_cfg_setup ( weather_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param weather Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
WEATHER_RETVAL weather_init ( weather_t *ctx, weather_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Weather click.
 *
 * @note Default configuration of the chip contains the settings :
 *         - oversampling huidity -  WEATHER_HUM_OS_1X;
 *         - oversampling temperature - WEATHER_MCTRL_TEMP_OS_2X
 *         - oversampling pressure - WEATHER_MCTRL_PRESS_OS_16X
 *         - mode - WEATHER_MCTRL_MODE_NORMAL
 *         - filter - WEATHER_CFG_FILTER_16
 *         - standby_time - WEATHER_CFG_STANDBY_TIME_10ms
 *
 */
void weather_default_cfg ( weather_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void weather_generic_write ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void weather_generic_read ( weather_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Device ID
 *
 * @param ctx      Click object.
 * @return (8 bit) Device ID - 0x60 - default
 *
 * @description You can use this function as a check on click communication with your MCU.
 */
uint8_t weather_get_device_id ( weather_t *ctx );

/**
 * @brief Software reset function
 *
 * @param ctx      Click object.
 */
void weather_software_reset ( weather_t *ctx );

/**
 * @brief Weather data
 *
 * @param ctx      Click object.
 * @param *weather_data  Structure that contains info about weather data
 *
 * @description Use this function to read the temperature, pressure and humidity data
 */
void weather_get_ambient_data( weather_t *ctx, weather_data_t *weather_data );

/**
 * @brief Measurement config
 *
 * @param ctx      Click object.
 * @param cfg      Structure that contains info about new measurement data for settings
 *
 * @description Use this function to set up new settings
 */
void weather_measurement_cfg ( weather_t *ctx, weather_measurement_cfg_t *cfg );


#ifdef __cplusplus
}
#endif
#endif  // _WEATHER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
