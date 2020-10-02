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
 * \brief This file contains API for Oximeter3 Click driver.
 *
 * \addtogroup oximeter3 Oximeter3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OXIMETER3_H
#define OXIMETER3_H

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
#define OXIMETER3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OXIMETER3_RETVAL  uint8_t

#define OXIMETER3_OK           0x00
#define OXIMETER3_INIT_ERROR   0xFF
#define OXIMETER3_ERROR        0xFF
/** \} */
 
/**
 * \defgroup slave_address  Slave Address
 * \{
 */
#define OXIMETER3_SLAVE_ADDRESS                                0x13

/**
 * \defgroup registers  Registers
 * \{
 */
#define OXIMETER3_REG_COMMAND                                  0x80
#define OXIMETER3_REG_PRODUCT_ID                               0x81
#define OXIMETER3_REG_PROX_RATE                                0x82
#define OXIMETER3_REG_LED_CURRENT                              0x83
#define OXIMETER3_REG_ALS_PARAMETER                            0x84
#define OXIMETER3_REG_ALS_RESULT_MSB                           0x85
#define OXIMETER3_REG_ALS_RESULT_LSB                           0x86
#define OXIMETER3_REG_PROX_RESULT_MSB                          0x87
#define OXIMETER3_REG_PROX_RESULT_LSB                          0x88
#define OXIMETER3_REG_INTERRUPT_CTRL                           0x89
#define OXIMETER3_REG_LOW_THRESHOLD_MSB                        0x8A
#define OXIMETER3_REG_LOW_THRESHOLD_LSB                        0x8B
#define OXIMETER3_REG_HIGH_THRESHOLD_MSB                       0x8C
#define OXIMETER3_REG_HIGH_THRESHOLD_LSB                       0x8D
#define OXIMETER3_REG_INTERRUPT_STATUS                         0x8E
#define OXIMETER3_REG_PROX_MODULATOR_TIMING                    0x8F
/** \} */
 
/**
 * \defgroup command  Command
 * \{
 */
#define OXIMETER3_CMD_ALS_SINGLE_MEASUREMENT_ENABLE            0x10
#define OXIMETER3_CMD_ALS_SINGLE_MEASUREMENT_DISABLE           0x00
#define OXIMETER3_CMD_PROX_SINGLE_MEASUREMENT_ENABLE           0x08
#define OXIMETER3_CMD_PROX_SINGLE_MEASUREMENT_DISABLE          0x00
#define OXIMETER3_CMD_ALS_PERIODIC_MEASUREMENT_ENABLE          0x04
#define OXIMETER3_CMD_ALS_PERIODIC_MEASUREMENT_DISABLE         0x00
#define OXIMETER3_CMD_PROX_PERIODIC_MEASUREMENT_ENABLE         0x02
#define OXIMETER3_CMD_PROX_PERIODIC_MEASUREMENT_DISABLE        0x00
#define OXIMETER3_CMD_MEASUREMENT_ENABLE                       0x01
#define OXIMETER3_CMD_MEASUREMENT_DISABLE                      0x00

#define OXIMETER3_CMD_ALS_DATA_READY                           0x20
#define OXIMETER3_CMD_PROX_DATA_READY                          0x40
/** \} */
 
/**
 * \defgroup prox_rate  Prox rate
 * \{
 */
#define OXIMETER3_PROX_RATE_1p95_MPS                           0x00
#define OXIMETER3_PROX_RATE_3p90625_MPS                        0x01
#define OXIMETER3_PROX_RATE_7p8125_MPS                         0x02
#define OXIMETER3_PROX_RATE_16p625_MPS                         0x03
#define OXIMETER3_PROX_RATE_31p25_MPS                          0x04
#define OXIMETER3_PROX_RATE_62p5_MPS                           0x05
#define OXIMETER3_PROX_RATE_125_MPS                            0x06
#define OXIMETER3_PROX_RATE_250_MPS                            0x07
/** \} */
 
/**
 * \defgroup led_curr  Led curr
 * \{
 */
#define OXIMETER3_LED_CURR_MIN                                 1
#define OXIMETER3_LED_CURR_MAX                                 20
/** \} */
 
/**
 * \defgroup als_param  Als Param
 * \{
 */
#define OXIMETER3_ALS_PARAM_CONT_CONVERSION_ENABLE             0x80
#define OXIMETER3_ALS_PARAM_CONT_CONVERSION_DISABLE            0x00
#define OXIMETER3_ALS_PARAM_AUTO_OFSEN_ENABLE                  0x08
#define OXIMETER3_ALS_PARAM_AUTO_OFSEN_DISABLE                 0x00
#define OXIMETER3_ALS_PARAM_1_SAMPEL_PER_S                     0x00
#define OXIMETER3_ALS_PARAM_2_SAMPEL_PER_S                     0x10
#define OXIMETER3_ALS_PARAM_3_SAMPEL_PER_S                     0x20
#define OXIMETER3_ALS_PARAM_4_SAMPEL_PER_S                     0x30
#define OXIMETER3_ALS_PARAM_5_SAMPEL_PER_S                     0x40
#define OXIMETER3_ALS_PARAM_6_SAMPEL_PER_S                     0x50
#define OXIMETER3_ALS_PARAM_8_SAMPEL_PER_S                     0x60
#define OXIMETER3_ALS_PARAM_10_SAMPEL_PER_S                    0x70
/** \} */
 
/**
 * \defgroup int_ctrl  Int ctrl
 * \{
 */
#define OXIMETER3_INT_CTRL_1_CNT                               0x00
#define OXIMETER3_INT_CTRL_2_CNT                               0x20
#define OXIMETER3_INT_CTRL_4_CNT                               0x40
#define OXIMETER3_INT_CTRL_8_CNT                               0x60
#define OXIMETER3_INT_CTRL_16_CNT                              0x80
#define OXIMETER3_INT_CTRL_32_CNT                              0xA0
#define OXIMETER3_INT_CTRL_64_CNT                              0xC0
#define OXIMETER3_INT_CTRL_128_CNT                             0xE0
#define OXIMETER3_INT_CTRL_INT_ON_PROX_RDY                     0x08
#define OXIMETER3_INT_CTRL_INT_ON_ALS_RDY                      0x04
#define OXIMETER3_INT_CTRL_INT_ON_THRESHOLD                    0x02
#define OXIMETER3_INT_CTRL_INT_ON_THRESHOLD_PROX               0x00
#define OXIMETER3_INT_CTRL_INT_ON_THRESHOLD_ALS                0x01
/** \} */
 
/**
 * \defgroup int_status Int status
 * \{
 */
#define OXIMETER3_INT_STATUS_PROX                              0x08
#define OXIMETER3_INT_STATUS_ALS                               0x04
#define OXIMETER3_INT_STATUS_LOW_THRESHOLD                     0x02
#define OXIMETER3_INT_STATUS_HIGH_THRESHOLD                    0x01
/** \} */
 
/**
 * \defgroup prox_timing  Prox timing
 * \{
 */
#define OXIMETER3_PROX_TIMING_FREQ_390p625_KHZ                 0x00
#define OXIMETER3_PROX_TIMING_FREQ_781p25_KHZ                  0x01
#define OXIMETER3_PROX_TIMING_FREQ_1p5625_MHZ                  0x10
#define OXIMETER3_PROX_TIMING_FREQ_3p125_MHZ                   0x11
/** \} */
 
/**
 * \defgroup id_val  ID Val
 * \{
 */
#define OXIMETER3_ID_VAL                                       0x21
/** \} */
 
/**
 * \defgroup als_prox_rate  Als prox rate
 * \{
 */
#define OXIMETER3_ALS                                          0x11
#define OXIMETER3_PROX                                         0x22
#define OXIMETER3_HEART_RATE                                   0x33
/** \} */
 
/**
 * \defgroup shift_value  Shift value
 * \{
 */
#define SHIFT_VALUE                                            8
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
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} oximeter3_t;

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

} oximeter3_cfg_t;

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
void oximeter3_cfg_setup ( oximeter3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param oximeter3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OXIMETER3_RETVAL oximeter3_init ( oximeter3_t *ctx, oximeter3_cfg_t *cfg );

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
void oximeter3_generic_write ( oximeter3_t *ctx, uint8_t reg, uint8_t data_buf );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads data from the desired register.
 */
uint8_t oximeter3_generic_read ( oximeter3_t *ctx, uint8_t reg );

/**
 * @brief Gets state of the int pin
 * 
 * @param ctx          Click object.
 * 
 * @return State of the pin
 */
uint8_t oximeter3_get_int_status ( oximeter3_t *ctx );

/**
 * @brief Generic function for reading als and proximity values
 * 
 * @param ctx                Click object.
 * @param type_macro         OXIMETER3_HEART_RATE or 
 *                           OXIMETER3_ALS or 
 *                           OXIMETER3_PROX
 * 
 * @return Read data or OXIMETER3_ERROR if wrong macro is written
 */
uint16_t oximeter3_read_value ( oximeter3_t *ctx, uint8_t type_macro );

#ifdef __cplusplus
}
#endif
#endif  // _OXIMETER3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
