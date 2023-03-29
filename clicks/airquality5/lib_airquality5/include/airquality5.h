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
 * \brief This file contains API for Air quality 5 Click driver.
 *
 * \addtogroup airquality5 Air quality 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AIRQUALITY5_H
#define AIRQUALITY5_H

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
#define AIRQUALITY5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AIRQUALITY5_RETVAL  uint8_t

#define AIRQUALITY5_OK           0x00
#define AIRQUALITY5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup chanel_data  Chanel Data
 * \{
 */
#define AIRQ5_DATA_CHANNEL_NO2    0x4000
#define AIRQ5_DATA_CHANNEL_NH3    0x5000
#define AIRQ5_DATA_CHANNEL_CO     0x6000
/** \} */

/**
 * \defgroup register   Register
 * \{
 */
#define AIRQ5_REG_POINTER_CONVERT         0x00
#define AIRQ5_REG_POINTER_CONFIG          0x01
#define AIRQ5_REG_POINTER_LOW_THRESH      0x02
#define AIRQ5_REG_POINTER_HIGH_THRESH     0x03
/** \} */

/**
 * \defgroup configuration_os   Configuration OS
 * \{
 */
#define AIRQ5_CONFIG_OS_SINGLE        0x8000
#define AIRQ5_CONFIG_OS_BUSY          0x0000
#define AIRQ5_CONFIG_OS_NOTBUSY       0x8000
/** \} */

/**
 * \defgroup configuration_pga   Configuration PGA
 * \{
 */
#define AIRQ5_CONFIG_PGA_6_144V       0x0000
#define AIRQ5_CONFIG_PGA_4_096V       0x0200
#define AIRQ5_CONFIG_PGA_2_048V       0x0400
#define AIRQ5_CONFIG_PGA_1_024V       0x0600
#define AIRQ5_CONFIG_PGA_0_512V       0x0800
#define AIRQ5_CONFIG_PGA_0_256V       0x0A00
/** \} */

/**
 * \defgroup configuration_mode   Configuration MODE
 * \{
 */
#define AIRQ5_CONFIG_CONTINUOUS_MODE  0x0000
#define AIRQ5_CONFIG_SINGLE_MODE      0x0100
/** \} */

/**
 * \defgroup configuration_dr   Configuration DR
 * \{
 */
#define AIRQ5_CONFIG_DATA_RATE_128SPS    0x0000
#define AIRQ5_CONFIG_DATA_RATE_250SPS    0x0020
#define AIRQ5_CONFIG_DATA_RATE_490SPS    0x0040
#define AIRQ5_CONFIG_DATA_RATE_920SPS    0x0060
#define AIRQ5_CONFIG_DATA_RATE_1600SPS   0x0080
#define AIRQ5_CONFIG_DATA_RATE_2400SPS   0x00A0
#define AIRQ5_CONFIG_DATA_RATE_3300SPS   0x00C0
/** \} */

/**
 * \defgroup configuration_cmode   Configuration CMODE
 * \{
 */
#define AIRQ5_CONFIG_COMP_MODE_TRADITIONAL  0x0000
#define AIRQ5_CONFIG_COMP_MODE_WINDOW       0x0010
/** \} */

/**
 * \defgroup configuration_cpol   Configuration CPOL
 * \{
 */
#define AIRQ5_CONFIG_COMP_POL_ACTIVE_LOW    0x0000
#define AIRQ5_CONFIG_COMP_POL_ACTIVE_HIGH   0x0008
/** \} */

/**
 * \defgroup configuration_clat   Configuration CLAT
 * \{
 */
#define AIRQ5_CONFIG_COMP_LAT_NOT_LATCH    0x0000
#define AIRQ5_CONFIG_COMP_LAT_LATCH        0x0004
/** \} */

/**
 * \defgroup configuration_cque   Configuration CQUE
 * \{
 */
#define AIRQ5_CONFIG_COMP_QUE_1CONV   0x0000
#define AIRQ5_CONFIG_COMP_QUE_2CONV   0x0001
#define AIRQ5_CONFIG_COMP_QUE_4CONV   0x0002
#define AIRQ5_CONFIG_COMP_QUE_0CONV   0x0003
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
    uint16_t data_config;

} airquality5_t;

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

} airquality5_cfg_t;

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
void airquality5_cfg_setup ( airquality5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AIRQUALITY5_RETVAL airquality5_init ( airquality5_t *ctx, airquality5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Airquality5 click.
 */
void airquality5_default_cfg ( airquality5_t *ctx );

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
void airquality5_generic_write ( airquality5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void airquality5_generic_read ( airquality5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for write data in register.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register in which the data will be written.
 * @param data_buf     Output data buf.
 * @param data_b       Data which be written in the register.
 *
 * @description This function when you need to written data into the register.
 */
void airq5_write_data ( airquality5_t *ctx, uint8_t reg, uint16_t data_b );

/**
 * @brief Functions for read data from register.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register from which will be read.
 *
 * @description This function when you need to reads data from the register.
 */
uint16_t airq5_read_data ( airquality5_t *ctx, uint8_t reg );

/**
 * @brief Functions for configuration.
 *
 * 
 * @param ctx             Click object.
 * @param config          Register from which will be read.
 *
 * @description This functions sets configuration.
 */
void airq5_set_configuration ( airquality5_t *ctx, uint16_t config );

/**
 * @brief Functions for read sensor data.
 *
 * 
 * @param ctx                   Click object.
 * @param channel_data          Data which be reads.
 *
 * @description This functions for read sensor data.
 */
uint16_t airq5_read_sensor_data( airquality5_t *ctx, uint16_t channel_data );

/**
 * @brief Functions for reads interrupt pin.
 *
 * 
 * @param ctx                   Click object.
 *
 * @description This functions for reads interrupt pin.
 */
uint8_t airq5_get_interrupt ( airquality5_t *ctx );
#ifdef __cplusplus
}
#endif
#endif  // _AIRQUALITY5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
