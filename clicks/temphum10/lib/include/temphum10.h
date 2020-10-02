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
 * \brief This file contains API for Temp&Hum 10 Click driver.
 *
 * \addtogroup temphum10 Temp&Hum 10 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM10_H
#define TEMPHUM10_H

#include "drv_digital_out.h"
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
#define TEMPHUM10_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ) 

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM10_RETVAL  uint8_t

#define TEMPHUM10_OK           0x00
#define TEMPHUM10_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define TEMPHUM10_REG_DEVICE_RESET        0x00
#define TEMPHUM10_REG_AVERAGE_MODE        0x01
#define TEMPHUM10_REG_ERROR_FLAG          0x03
#define TEMPHUM10_REG_HUMIDITY_LSB        0x04
#define TEMPHUM10_REG_HUMIDITY_MSB        0x05
#define TEMPHUM10_REG_TEMPERATURE_LSB     0x06
#define TEMPHUM10_REG_TEMPERATURE_MSB     0x07
#define TEMPHUM10_REG_CAPACITY_LSB        0x0A
#define TEMPHUM10_REG_CAPACITY_MSB        0x0B
#define TEMPHUM10_REG_CAPACITY_CTRL       0x2C
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define TEMPHUM10_MODE_SLEEP     0x00
#define TEMPHUM10_MODE_STANDBY   0x01
/** \} */

/**
 * \defgroup reset Reset
 * \{
 */
#define TEMPHUM10_RST_NORMAL_OPERATION  0x00
#define TEMPHUM10_RST_ACTIVE_RESET      0x01
/** \} */

/**
 * \defgroup average_mode  Average mode
 * \{
 */
#define TEMPHUM10_AM_NO_AVERAGING_PROCESS              0x00
#define TEMPHUM10_AM_TIMES_AVERAGE_MODE_2              0x08
#define TEMPHUM10_AM_TIMES_AVERAGE_MODE_4              0x10
#define TEMPHUM10_AM_TIMES_AVERAGE_MODE_8              0x20
#define TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_8         0x00
#define TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_16        0x04
#define TEMPHUM10_AM_MANUAL_MODE_DETECTION_OP_STOP     0x00
#define TEMPHUM10_AM_MANUAL_MODE_DETECTION_OP_START    0x01
/** \} */

/**
 * \defgroup error Error
 * \{
 */
#define TEMPHUM10_ERR_NO_ERROR             0x00
#define TEMPHUM10_ERR_ERROR_FLAG_RESET     0x01
/** \} */

/**
 * \defgroup capacity_control  apaciti control
 * \{
 */
#define TEMPHUM10_CAP_OUTSIDE_CAPACITY_CUTTING     0x00
#define TEMPHUM10_CAP_OUTSIDE_CAPACITY_CONNECTION  0x10
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
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} temphum10_t;

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

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} temphum10_cfg_t;

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
void temphum10_cfg_setup ( temphum10_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM10_RETVAL temphum10_init ( temphum10_t *ctx, temphum10_cfg_t *cfg );

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
void temphum10_generic_write ( temphum10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void temphum10_generic_read ( temphum10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for read Relative Huminidy data
 *
 * @param ctx          Click object.
 * 
 * @return Relative Huminidy data in [%RH]
 */
float temphum10_get_humidity ( temphum10_t *ctx );

/**
 * @brief Functions for read Temperature data
 *
 * @param ctx          Click object.
 * 
 * @return Temperature data in [C]
 */
float temphum10_get_temperature ( temphum10_t *ctx );

/**
 * @brief Functions for sets Device mode
 *
 * @param ctx        Click object. 
 * @param mode       Device mode ( TEMPHUM10_MODE_SLEEP or TEMPHUM10_MODE_STANDBY )
 */
void temphum10_set_device_mode ( temphum10_t *ctx, uint8_t mode );

/**
 * @brief Functions for repeat measurement
 *
 * @param ctx        Click object. 
 * @param average    Sets average times(2, 4, 8 times or no average) and temperature (_TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_8 or _TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_16)
 */
void temphum10_repeat_measurement ( temphum10_t *ctx, uint8_t average );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM10_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
