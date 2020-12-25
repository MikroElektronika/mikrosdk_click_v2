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
 * \brief This file contains API for Proximity 2 Click driver.
 *
 * \addtogroup proximity2 Proximity 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY2_H
#define PROXIMITY2_H

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
#define PROXIMITY2_MAP_MIKROBUS( cfg, mikrobus )     \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );     \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );     \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY2_RETVAL  uint8_t

#define PROXIMITY2_OK           0x00
#define PROXIMITY2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address I2C Slave address
 * \{
 */
#define PROXIMITY2_I2C_SLAVE_ADDR                                       0x4A
/** \} */

/**
 * \defgroup reg Register map
 * \{
 */
#define PROXIMITY2_REG_INTER_STAT                                       0x00
#define PROXIMITY2_REG_MAIN_CONFIG                                      0x01
#define PROXIMITY2_REG_RECEIVE_CONFIG                                   0x02
#define PROXIMITY2_REG_TRANSMIT_CONFIG                                  0x03
#define PROXIMITY2_REG_ALS_HI_BY                                        0x04
#define PROXIMITY2_REG_ALS_LO_BY                                        0x05
#define PROXIMITY2_REG_PROX                                             0x16
#define PROXIMITY2_REG_ALS_UPTRSH_H                                     0x06
#define PROXIMITY2_REG_ALS_UPTRSH_L                                     0x07
#define PROXIMITY2_REG_ALS_LOTRSH_H                                     0x08
#define PROXIMITY2_REG_ALS_LOTRSH_L                                     0x09
#define PROXIMITY2_REG_TRSH_PERS_TIM                                    0x0A
#define PROXIMITY2_REG_PROX_TRSH_IND                                    0x0B
#define PROXIMITY2_REG_PROX_TRSH                                        0x0C
#define PROXIMITY2_REG_GREEN_GAIN                                       0x0F
#define PROXIMITY2_REG_IR_GAIN                                          0x10
/** \} */

/**
 * \defgroup confg Configuration value
 * \{
 */
#define PROXIMITY2_RECE_CONFIG_ALSPGA_0_03125                           0x00
#define PROXIMITY2_RECE_CONFIG_ALSPGA_0_125                             0x01
#define PROXIMITY2_RECE_CONFIG_ALSPGA_0_5                               0x02
#define PROXIMITY2_RECE_CONFIG_ALSPGA_4                                 0x03
#define PROXIMITY2_RECE_CONFIG_DEFAULT                                  0xF1
#define PROXIMITY2_MAIN_CONFIG_STDWN                                    0x00
#define PROXIMITY2_MAIN_CONFIG_DEFAULT                                  0x13
#define PROXIMITY2_MAIN_CONFIG_ALS_G_IR                                 0x04
#define PROXIMITY2_MAIN_CONFIG_ALS_G                                    0x08
#define PROXIMITY2_MAIN_CONFIG_ALS_IR                                   0x0C
#define PROXIMITY2_MAIN_CONFIG_ALS_PROX                                 0x10
#define PROXIMITY2_MAIN_CONFIG_PROX_ONLY                                0x14
#define PROXIMITY2_RECE_CONFIG_ALSTIM_14                                0x00
#define PROXIMITY2_RECE_CONFIG_ALSTIM_12                                0x01
#define PROXIMITY2_RECE_CONFIG_ALSTIM_10                                0x02
#define PROXIMITY2_RECE_CONFIG_ALSTIM_8                                 0x03
/** \} */

/**
 * \defgroup led_drv Transmit cofiguration values 
 * \{
 */
#define PROXIMITY2_LED_DRV_DISABLE                                      0x00
#define PROXIMITY2_LED_DRV_CURRENT_10_MA                                0x01
#define PROXIMITY2_LED_DRV_CURRENT_20_MA                                0x02
#define PROXIMITY2_LED_DRV_CURRENT_30_MA                                0x03
#define PROXIMITY2_LED_DRV_CURRENT_40_MA                                0x04
#define PROXIMITY2_LED_DRV_CURRENT_50_MA                                0x05
#define PROXIMITY2_LED_DRV_CURRENT_60_MA                                0x06
#define PROXIMITY2_LED_DRV_CURRENT_70_MA                                0x07
#define PROXIMITY2_LED_DRV_CURRENT_80_MA                                0x0C
#define PROXIMITY2_LED_DRV_CURRENT_90_MA                                0x0D
#define PROXIMITY2_LED_DRV_CURRENT_100_MA                               0x0E
#define PROXIMITY2_LED_DRV_CURRENT_110_MA                               0x0F
/** \} */

/**
 * \defgroup int_trg No. Of consecutive triggers before interrupt
 * \{
 */
#define PROXIMITY2_INTERRUPT_TRIGGERS_1                                 0x00
#define PROXIMITY2_INTERRUPT_TRIGGERS_2                                 0x01
#define PROXIMITY2_INTERRUPT_TRIGGERS_4                                 0x02
#define PROXIMITY2_INTERRUPT_TRIGGERS_16                                0x03
/** \} */

/**
 * \defgroup init_val Initial value
 * \{
 */
#define PROXIMITY2_PROXI_AVG_VAL                                        0x7F
#define PROXIMITY2_PROXI_MAX_VAL                                        0xFF
#define PROXIMITY2_PROXI_SENSITIVITY                                    5
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} proximity2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} proximity2_cfg_t;

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
void proximity2_cfg_setup ( proximity2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PROXIMITY2_RETVAL proximity2_init ( proximity2_t *ctx, proximity2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Proximity2 click.
 * @note
 *    Click default configuration:
 * -------------------------------------------------
 * <pre>
 *    reg    : PROXIMITY2_REG_MAIN_CONFIG
 * -------------------------------------------------
 *    tx_buf : PROXIMITY2_MAIN_CONFIG_DEFAULT
 * </pre>
 * <pre>
 *    reg    : PROXIMITY2_REG_RECEIVE_CONFIG
 * -------------------------------------------------
 *    tx_buf : PROXIMITY2_RECE_CONFIG_DEFAULT
 * </pre>
 * <pre>
 *    reg    : PROXIMITY2_REG_TRANSMIT_CONFIG
 * -------------------------------------------------
 *    tx_buf : PROXIMITY2_LED_DRV_CURRENT_110_MA
 * </pre>
 */
void proximity2_default_cfg ( proximity2_t *ctx );

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
void proximity2_generic_write ( proximity2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void proximity2_generic_read ( proximity2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read PROX Data Register function.
 * 
 * @param ctx          Click object.
 * 
 * @return result      8-bit value that represents measurement made by sensor 
 *
 * @description This function is used to read prox data register in order 
 * to get data on distance from sensor to an object.
 */
uint8_t proximity2_read_prox ( proximity2_t *ctx );

/**
 * @brief Read ALS Data Registers function.
 * 
 * @param ctx          Click object.
 * 
 * @return result      combined values from ADC High Byte and ADC Low Byte registers 
 *
 * @description This function is used to read both ADC High Byte 
 * and ADC Low Byte registers.
 * @note The result is always right justified in the two registers 
 * and the unused high bits are zero.
 */
uint16_t proximity2_read_als ( proximity2_t *ctx );

/**
 * @brief Get int pin status.
 * 
 * @param ctx          Click object.
 * 
 * @return status     [ 0 = Active / 1 = Inactive ]
 *
 * @description This function is used to read interrupt pin status.
 */
uint8_t proximity2_get_int_pin_status ( proximity2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
