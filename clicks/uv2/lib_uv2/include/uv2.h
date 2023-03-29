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
 * \brief This file contains API for UV 2  Click driver.
 *
 * \addtogroup uv2 UV 2  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UV2_H
#define UV2_H

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
#define UV2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UV2_RETVAL  uint8_t

#define UV2_OK           0x00
#define UV2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup id Id
 * \{
 */
#define UV2_I2C_ADDRESS                                            0x10
#define UV2_DEV_ID                                                 0x26
/** \} */

/**
 * \defgroup reg reg
 * \{
 */
#define UV2_REG_CONF                                               0x00
#define UV2_REG_UVA                                                0x07
#define UV2_REG_UVB                                                0x09
#define UV2_REG_UVCOMP1                                            0x0A
#define UV2_REG_UVCOMP2                                            0x0B
#define UV2_REG_DEVID                                              0x0C
/** \} */

/**
 * \defgroup conf_it Conf It
 * \{
 */
#define UV2_CONF_IT_50MS                                           0x00
#define UV2_CONF_IT_100MS                                          0x10
#define UV2_CONF_IT_200MS                                          0x20
#define UV2_CONF_IT_400MS                                          0x30
#define UV2_CONF_IT_800MS                                          0x40
#define UV2_CONF_IT_MASK                                           0x8F
/** \} */

/**
 * \defgroup conf_hd Conf Hd
 * \{
 */
#define UV2_CONF_HD_NORM                                           0x00
#define UV2_CONF_HD_HIGH                                           0x08
/** \} */

/**
 * \defgroup conf_trig Conf Trig
 * \{
 */
#define UV2_CONF_MODE_TRIG                                         0x00
#define UV2_CONF_ONE_TRIG                                          0x04
/** \} */

/**
 * \defgroup conf_af Conf Af
 * \{
 */
#define UV2_CONF_AF_OFF                                            0x00
#define UV2_CONF_AF_ON                                             0x02
/** \} */

/**
 * \defgroup conf_sd Conf Sd
 * \{
 */
#define UV2_CONF_SD_PWR_ON                                         0x00
#define UV2_CONF_SD_PWR_OFF                                        0x01
/** \} */

/**
 * \defgroup uvi_coeff Uvi Coeff
 * \{
 */
#define UV2_UVI_UVA_VIS_COEFF                                      3.33
#define UV2_UVI_UVA_IR_COEFF                                       2.50
#define UV2_UVI_UVB_VIS_COEFF                                      3.66
#define UV2_UVI_UVB_IR_COEFF                                       2.75
/** \} */

/**
 * \defgroup uvi_response Uvi Response
 * \{
 */
#define UV2_UVI_UVA_RESPONSE                                       0.00110
#define UV2_UVI_UVB_RESPONSE                                       0.00125
/** \} */

/**
 * \defgroup write_msb_bits Write Msb Bits
 * \{
 */
#define UV2_WRITE_MSB_BITS                                         0x00
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

} uv2_t;

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

} uv2_cfg_t;

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
void uv2_cfg_setup ( uv2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UV2_RETVAL uv2_init ( uv2_t *ctx, uv2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for UV2 click.
 */
void uv2_default_cfg ( uv2_t *ctx );

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
void uv2_generic_write ( uv2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void uv2_generic_read ( uv2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write 16-bit data function.
 *
 * @param ctx           Click object.
 * @param reg_address   8-bit register address.
 * @param write_data    16-bit data to write to given address.
 *
 * @description This function write 16-bit data to given 8-bit register address
 * of VEML6075 sesnor on UV 2 Click.
 */
void uv2_write_data ( uv2_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Read 16-bit data from 8-bit address function.
 *
 * @param ctx           Click object.
 * @param reg_address   8-bit register address.
 *
 * @description This function read 16-bit data from given 8-bit register address
 * of VEML6075 sesnor on UV 2 Click.
 */
uint16_t uv2_read_data ( uv2_t *ctx, uint8_t reg_address );

/**
 * @brief Set configuration function.
 *
 * @param ctx           Click object.
 * @param config_value  8-bit configuration value.
 *
 * @description This function set configuration by write configuration value
 * to config register of VEML6075 sesnor on UV 2 Click.
 */
void uv2_set_config ( uv2_t *ctx, uint8_t config_value );

/**
 * @brief Set integration time function.
 *
 * @param ctx           Click object.
 * @param intg_time     8-bit configuration value.
 *
 * @description This function set configuration by write configuration value
 * to config register of VEML6075 sesnor on UV 2 Click.
 */
void uv2_set_integration_time ( uv2_t *ctx, uint16_t intg_time );

/**
 * @brief Set normal dynamic function.
 *
 * @param ctx           Click object.
 *
 * @description This function set normal dynamic by set HD bit low
 * to config register of VEML6075 sesnor on UV 2 Click.
 */
void uv2_set_normal_dynamic ( uv2_t *ctx );

/**
 * @brief Set high dynamic function.
 *
 * @param ctx           Click object.
 *
 * @description This function set high dynamic by set HD bit high
 * to config register of VEML6075 sesnor on UV 2 Click.
 */
void uv2_set_high_dynamic ( uv2_t *ctx );

/**
 * @brief Set trigger one measurement function.
 *
 * @param ctx           Click object.
 *
 * @description This function trigger one measurement by set UV_TRIG bit high
 * to config register of VEML6075 sesnor on UV 2 Click.
 */
void uv2_set_trigger_measurement ( uv2_t *ctx );

/**
 * @brief Set active force mode function.
 *
 * @param ctx           Click object.
 * @param force_mode    Trigger mode.
 *
 * @description This function set active force mode by write force mode UV_AF bit
 * to config register of VEML6075 sesnor on UV 2 Click.
 */
void uv2_set_active_force_mode ( uv2_t *ctx, uint8_t force_mode );

/**
 * @brief Set power ON function.
 *
 * @param ctx           Click object.
 *
 * @description This function set power ON by set SD bit low
 * to config register of VEML6075 sesnor on UV 2 Click.
 */
void uv2_set_power_on ( uv2_t *ctx );

/**
 * @brief Set power OFF function.
 *
 * @param ctx           Click object.
 *
 * @description This function set power OFF by set SD bit high
 * to config register of VEML6075 sesnor on UV 2 Click.
 */
void uv2_set_power_off ( uv2_t *ctx );

/**
 * @brief Check sensor ID function.
 *
 * @param ctx           Click object.
 *
 * @description This function check sensor ID of VEML6075 sesnor on UV 2 Click.
 */
uint8_t uv2_check_id ( uv2_t *ctx );

/**
 * @brief Get UVA data function.
 *
 * @param ctx           Click object.
 *
 * @description This function get UVA data by read UVA register value 
 * of VEML6075 sesnor on UV 2 Click.
 */
uint16_t uv2_get_uva ( uv2_t *ctx );

/**
 * @brief Get UVB data function.
 *
 * @param ctx           Click object.
 *
 * @description This function get UVB data by read UVB register value
 * of VEML6075 sesnor on UV 2 Click.
 */
uint16_t uv2_get_uvb ( uv2_t *ctx );

/**
 * @brief Get UV index function.
 *
 * @param ctx           Click object.
 *
 * @description This function get UV index by calculating data from UVA and UVB register 
 * of VEML6075 sesnor on UV 2 Click.
 */
float uv2_get_uv_index ( uv2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _UV2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
