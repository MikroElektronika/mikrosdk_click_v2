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
 * \brief This file contains API for Barometer Click driver.
 *
 * \addtogroup barometer Barometer Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BAROMETER_H
#define BAROMETER_H

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

#define BAROMETER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define BAROMETER_MASTER_I2C 0
#define BAROMETER_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BAROMETER_RETVAL  uint8_t

#define BAROMETER_OK           0x00
#define BAROMETER_INIT_ERROR   0xFF
/** \} */

/**
 *  \defgroup barometer_address  Barometer Address
 * \{
 */
 #define BAROMETER_I2C_ADDRESS_0                     0x5C
 /** \} */
 
 /**
  *  \defgroup barometer_address_1  Barometer Address 1
  * \{
  */
 #define BAROMETER_I2C_ADDRESS_1                      0x5D
 /** \} */
 
 /**
  *  \defgroup barometer_ref  Barometer Ref 
  * \{
  */
 #define BAROMETER_REF_P_XL                           0x08
 #define BAROMETER_REF_P_L                            0x09
 #define BAROMETER_REF_P_H                            0x0A
 /** \} */
 
 /**
  *  \defgroup Barometer_who  Barometer Who
  * \{
  */
 #define BAROMETER_WHO_AM_I                           0x0F
 /** \} */
 
 /**
  *  \defgroup barometer_data  Barometer Data
  * \{
  */
 #define BAROMETER_RES_CONF                           0x10
 #define BAROMETER_CTRL_REG1                          0x20
 #define BAROMETER_CTRL_REG2                          0x21
 #define BAROMETER_CTRL_REG3                          0x22
 #define BAROMETER_CTRL_REG4                          0x23
 #define BAROMETER_INTERRUPT_CFG                      0x24
 #define BAROMETER_INT_SOURCE                         0x25
 #define BAROMETER_STATUS_REG                         0x27
 #define BAROMETER_PRESS_OUT_XL                       0x28
 #define BAROMETER_PRESS_OUT_L                        0x29
 #define BAROMETER_PRESS_OUT_H                        0x2A
 #define BAROMETER_TEMP_OUT_L                         0x2B
 #define BAROMETER_TEMP_OUT_H                         0x2C
 #define BAROMETER_FIFO_CTRL                          0x2E
 #define BAROMETER_FIFO_STATUS                        0x2F
 #define BAROMETER_THS_P_L                            0x30
 #define BAROMETER_THS_P_H                            0x31
 #define BAROMETER_RPDS_L                             0x39
 #define BAROMETER_RPDS_H                             0x3A
 #define BAROMETER_DEVICE_ID                          0xBD
 /** \} */
 
 /**
  *  \defgroup  default  Default
  * \{
  */
 #define BAROMETER_DEFAULT_CONFIG                     0xB0
 #define BAROMETER_CONFIG_ACTIVE_MODE                 0x80
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
typedef uint8_t  barometer_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *barometer_master_io_t )( struct barometer_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct barometer_s
{
    digital_out_t cs;

    // Input pins 

    digital_in_t rdy;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
   barometer_master_io_t  write_f;
   barometer_master_io_t  read_f;
   barometer_select_t master_sel;

} barometer_t;

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
    
    // Additional gpio pins 

    pin_name_t rdy;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

    barometer_select_t sel;

} barometer_cfg_t;

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
void barometer_cfg_setup ( barometer_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param barometer Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BAROMETER_RETVAL barometer_init ( barometer_t *ctx, barometer_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @note
 *<pre>
 *       set: BAROMETER_CTRL_REG1
 *              - BAROMETER_DEFAULT_CONFIG
 *</pre>
 * @description This function executes default configuration for Barometer click.
 */
void barometer_default_cfg ( barometer_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void barometer_generic_write ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void barometer_generic_read ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read 8-bit data function
 *
 * @param ctx             Click object.
 * @param address         Register address
 *
 * @return
 * 8-bit data from addressed register from the LPS25HB
 *
 * Function read 8-bit data from register address 
 * of the LPS25HB sensor.
 */
uint8_t barometer_read_data( barometer_t *ctx, uint8_t address );

/**
 * @brief Sets the module active function
 *
 * @param ctx          Click object.
 * Function set active mode
 * by writing configuration register from the LPS25HB sensor.
 */
void barometer_set_active( barometer_t *ctx );

/**
 * @brief Read temperature in degrees Celsius function
 *
 * @param ctx          Click object.
 * @return
 * float temperature data degrees Celsius [ �C ]
 *
 * Function read and calculate temperature
 * in degrees Celsius from the LPS25HB sensor.
 */
float barometer_get_temperature_c ( barometer_t *ctx );

/**
 * @brief Read temperature in degrees of Fahrenheit function
 *
 * @param ctx          Click object.
 * @return
 * float temperature data degrees Fahrenheit [ �F ]
 *
 * Function read and calculate temperature
 * in degrees Fahrenheit from the LPS25HB sensor.
 */
float barometer_get_temperature_f( barometer_t *ctx );

/**
 * @brief Read pressure in milibars function
 *
 * @param ctx          Click object.
 * @return
 * float pressure data in milibars [ mbar ]
 *
 * Function read and calculate pressure
 * in milibars from the LPS25HB sensor.
 */
float barometer_get_pressure( barometer_t *ctx );

/**
 * @brief Check sensor id - Who Am I function
 *
 * @param ctx          Click object.
 * @return
 * 8-bit id data from Who Am I register
 *
 * Function read sensor id ( Who Am I register )
 * from the LPS25HB sensor.
 */
uint8_t barometer_check_id ( barometer_t *ctx );

/**
 * @brief Check sensor status function
 *
 * @param ctx          Click object.
 * @return
 * 8-bit id data from status register
 *
 * Function read sensor status ( status register )
 * from the LPS25HB sensor.
 */
uint8_t barometer_check_status ( barometer_t *ctx );

/**
 * @brief State of interrupt pin function
 *
 * @param ctx          Click object.
 * @return State of INT pin - 0 or 1
 *
 * Function checks is interrupt occurred and returns the state of the INT pin.
 * INT pin can be configured to show are data registers updated with the new values or not.
 */
uint8_t barometer_check_interrupt ( barometer_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BAROMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
