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
 * \brief This file contains API for Magneto 5 Click driver.
 *
 * \addtogroup magneto5 Magneto 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MAGNETO5_H
#define MAGNETO5_H

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
#define MAGNETO5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MAGNETO5_RETVAL  uint8_t

#define MAGNETO5_OK           0x00
#define MAGNETO5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_map   Register Map
 * \{
 */
#define MAGNETO5_REG_X_OUT_LOW           0x00
#define MAGNETO5_REG_X_OUT_HIGH          0x01
#define MAGNETO5_REG_Y_OUT_LOW           0x02
#define MAGNETO5_REG_Y_OUT_HIGH          0x03
#define MAGNETO5_REG_Z_OUT_LOW           0x04
#define MAGNETO5_REG_Z_OUT_HIGH          0x05
#define MAGNETO5_REG_STATUS              0x06
#define MAGNETO5_REG_INTERNAL_CONTROL_0  0x07
#define MAGNETO5_REG_INTERNAL_CONTROL_1  0x08
#define MAGNETO5_REG_PRODUCT_ID          0x20
/** \} */

/**
 * \defgroup check_status    Check Status
 * \{
 */
#define MAGNETO_STATUS_MEASUREMENT_DONE  0x01
#define MAGNETO_STATUS_PUMP_ON           0x02
#define MAGNETO_STATUS_READ_DONE         0x04
#define MAGNETO_STATUS_SELFTEST_OK       0x08
#define MAGNETO5_ERROR                   0x00
#define MAGNETO5_PRODUCT_ID              0x06
/** \} */

/**
 * \defgroup axis    Axis
 * \{
 */
#define MAGNETO5_AXIS_X                  0x00
#define MAGNETO5_AXIS_Y                  0x02
#define MAGNETO5_AXIS_Z                  0x04
/** \} */

/**
 * \defgroup config_register_0    Config Register 0
 * \{
 */
#define MAGNETO5_CR0_RESET               0x40
#define MAGNETO5_CR0_SET                 0x20
#define MAGNETO5_CR0_REFILL_CAP          0x80
#define MAGNETO5_CR0_NO_BOOST            0x10
#define MAGNETO5_CR0_MEASUREMENT_MODE_0  0x00
#define MAGNETO5_CR0_MEASUREMENT_MODE_1  0x04
#define MAGNETO5_CR0_MEASUREMENT_MODE_2  0x08
#define MAGNETO5_CR0_MEASUREMENT_MODE_3  0x0C
#define MAGNETO5_CR0_CONTINUOUS_MODE     0x02
#define MAGNETO5_CR0_TAKE_MEASUREMENT    0x01
/** \} */

/**
 * \defgroup config_register_1    Config Register 1
 * \{
 */
#define MAGNETO5_CR1_SOFT_RESET          0x80
#define MAGNETO5_CR1_TEMP_TEST           0x40
#define MAGNETO5_CR1_SELFTEST_XYZ        0x20
#define MAGNETO5_CR1_FACTORY_USE_X       0x10
#define MAGNETO5_CR1_FACTORY_USE_Y       0x08
#define MAGNETO5_CR1_FACTORY_USE_Z       0x04
#define MAGNETO5_CH0_16bits_8ms          0x00
#define MAGNETO5_CH1_16bits_4ms          0x01
#define MAGNETO5_CH2_14bits_2ms          0x02
#define MAGNETO5_CH3_12bits_1ms          0x03
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

    float max_resolution;
    uint8_t data_flag;

} magneto5_t;

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

} magneto5_cfg_t;

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
void magneto5_cfg_setup ( magneto5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param magneto5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MAGNETO5_RETVAL magneto5_init ( magneto5_t *ctx, magneto5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Magneto5 click.
 */
void magneto5_default_cfg ( magneto5_t *ctx );

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
void magneto5_generic_write ( magneto5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void magneto5_generic_read ( magneto5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions reads status register.
 *
 * 
 * @param ctx          Click object.
 *
 * @description The function is used to check if the chip is ready to read data and measurment data.
 */
uint8_t magneto5_set_status_reg ( magneto5_t *ctx );

/**
 * @brief Functions reads product ID from register.
 *
 * 
 * @param ctx          Click object.
 *
 * @description The function gets product id.
 */
uint8_t magneto5_get_product_id ( magneto5_t *ctx );

/**
 * @brief Functions reads axis data.
 *
 * 
 * @param ctx                Click object.
 * @param axis_buffer        Buffer in which axis data will be written.
 * @param max_resolution     Maximum resolution axis value.
 *
 * @description This function gets axis data.
 */
void magneto5_get_axis_data ( magneto5_t *ctx, int16_t *axis_buffer, uint8_t max_resolution );

/**
 * @brief Functions reads axis data value.
 *
 * 
 * @param ctx                Click object.
 * @param axis               Axis which be read.
 * @param max_resolution     Maximum resolution axis value.
 *
 * @description This function float axis value.
 */
float magneto5_get_axis_value ( magneto5_t *ctx, uint8_t axis, uint8_t max_resolution );

/**
 * @brief Functions sets configuration register 0.
 *
 * 
 * @param ctx                Click object.
 * @param config_data        Data which be set.
 *
 * @description Options for set:
      Take measurement,
      Continuous Measurement Mode,
      Frequency in continuous measurement mode (1.5Hz, 13Hz, 25Hz or 50 Hz),
      No Boost ( disable the charge pump )
      SET / RESET
      Refill Cap.
 */
void magneto5_config_register_0 ( magneto5_t *ctx, uint8_t config_data );

/**
 * @brief Functions sets configuration register 1.
 *
 * 
 * @param ctx                Click object.
 * @param config_data        Data which be set.
 *
 * @description Options for set:
      X/Y/Z channel measurements,
      Self Test,
      Temperature test,
      Soft reset.
 */
void magneto5_config_register_1 ( magneto5_t *ctx, uint8_t config_data );

/**
 * @brief Functions for reset data.
 *
 * 
 * @param ctx                Click object.
 *
 * @description This function is reset.
 */
void magneto5_reset (  magneto5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MAGNETO5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
