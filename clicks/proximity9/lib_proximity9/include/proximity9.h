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
 * \brief This file contains API for Proximity 9 Click driver.
 *
 * \addtogroup proximity9 Proximity 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY9_H
#define PROXIMITY9_H

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
#define PROXIMITY9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY9_RETVAL  uint8_t

#define PROXIMITY9_OK           0x00
#define PROXIMITY9_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define PROXIMITY9_DEV_ADDR                       0x60
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define PROXIMITY9_ALS_CONF_REG                   0x00
#define PROXIMITY9_ALS_THRSHD_H_REG               0x01
#define PROXIMITY9_ALS_THRSHD_L_REG               0x02
#define PROXIMITY9_PS_CONF_REG                    0x03
#define PROXIMITY9_PS_MS_REG                      0x04
#define PROXIMITY9_PS_CANC_REG                    0x05
#define PROXIMITY9_PS_THRSHD_L_REG                0x06
#define PROXIMITY9_PS_THRSHD_H_REG                0x07
#define PROXIMITY9_PS_DATA_REG                    0x08
#define PROXIMITY9_ALS_DATA_REG                   0x09
#define PROXIMITY9_WHITE_DATA_REG                 0x0A
#define PROXIMITY9_INT_FLAG_REG                   0x0B
#define PROXIMITY9_DEV_ID_REG                     0x0C
/** \} */

/**
 * \defgroup als_configuration ALS configuration
 * \{
 */
#define PROXIMITY9_ALS_IT_80_MS                   0x00
#define PROXIMITY9_ALS_IT_160_MS                  0x40
#define PROXIMITY9_ALS_IT_320_MS                  0x80
#define PROXIMITY9_ALS_IT_640_MS                  0xC0
#define PROXIMITY9_ALS_PERS_1                     0x00
#define PROXIMITY9_ALS_PERS_2                     0x04
#define PROXIMITY9_ALS_PERS_4                     0x08
#define PROXIMITY9_ALS_PERS_8                     0x0C
#define PROXIMITY9_ALS_INT_EN                     0x02
#define PROXIMITY9_ALS_SHUTDOWN                   0x01
/** \} */

/**
 * \defgroup proximity_configuration Proximity configuration
 * \{
 */
#define PROXIMITY9_PS_IR_ON_1_OFF_40              0x00
#define PROXIMITY9_PS_IR_ON_1_OFF_80              0x40
#define PROXIMITY9_PS_IR_ON_1_OFF_160             0x80
#define PROXIMITY9_PS_IR_ON_1_OFF_320             0xC0
#define PROXIMITY9_PS_PERS_1                      0x00
#define PROXIMITY9_PS_PERS_2                      0x10
#define PROXIMITY9_PS_PERS_3                      0x20
#define PROXIMITY9_PS_PERS_4                      0x30
#define PROXIMITY9_PS_IT_1T                       0x00
#define PROXIMITY9_PS_IT_1T5                      0x02
#define PROXIMITY9_PS_IT_2T                       0x04
#define PROXIMITY9_PS_IT_2T5                      0x06
#define PROXIMITY9_PS_IT_3T                       0x08
#define PROXIMITY9_PS_IT_3T5                      0x0A
#define PROXIMITY9_PS_IT_4T                       0x0C
#define PROXIMITY9_PS_IT_8T                       0x0E
#define PROXIMITY9_PS_SHUTDOWN                    0x01
 
#define PROXIMITY9_PS_OUTPUT_12BIT               0x0000
#define PROXIMITY9_PS_OUTPUT_16BIT               0x0800
#define PROXIMITY9_PS_INT_TRIGGER_CLOSE          0x0100
#define PROXIMITY9_PS_INT_TRIGGER_AWAY           0x0200
#define PROXIMITY9_PS_INT_TRIGGER_BOTH           0x0300
/** \} */

/**
 * \defgroup mode_selection Mode selection
 * \{
 */
#define PROXIMITY9_PS_SMART_PERS_EN                0x10
#define PROXIMITY9_PS_ACT_FORCE_EN                 0x08
#define PROXIMITY9_PS_TRIG_ONE_CYCLE               0x04

#define PROXIMITY9_WHITE_CH_DIS                  0x8000
#define PROXIMITY9_PS_NORMAL_OP_MODE             0x0000
#define PROXIMITY9_PS_DET_LOGIC_MODE             0x4000
#define PROXIMITY9_LED_I_50_MA                   0x0000
#define PROXIMITY9_LED_I_75_MA                   0x0100
#define PROXIMITY9_LED_I_100_MA                  0x0200
#define PROXIMITY9_LED_I_120_MA                  0x0300
#define PROXIMITY9_LED_I_140_MA                  0x0400
#define PROXIMITY9_LED_I_160_MA                  0x0500
#define PROXIMITY9_LED_I_180_MA                  0x0600
#define PROXIMITY9_LED_I_200_MA                  0x0700
/** \} */

/**
 * \defgroup interrupt_flags Interrupt flags
 * \{
 */
#define PROXIMITY9_PS_ENTER_PROT_MODE_FLAG         0x40
#define PROXIMITY9_ALS_IF_L_FLAG                   0x20
#define PROXIMITY9_ALS_IF_H_FLAG                   0x10
#define PROXIMITY9_PS_IF_CLOSE_FLAG                0x02
#define PROXIMITY9_PS_IF_AWAY_FLAG                 0x01
#define PROXIMITY9_INT_CLEARED                     0x00
/** \} */

/**
 * \defgroup returned_value  Returned values
 * \{
 */
#define PROXIMITY9_INVALID_ADDR                    0x01
#define PROXIMITY9_OK                              0x00
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

    float als_sens;

} proximity9_t;

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

} proximity9_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void proximity9_cfg_setup ( proximity9_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
PROXIMITY9_RETVAL proximity9_init ( proximity9_t *ctx, proximity9_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * 
 * @note 
 * <pre>
 * PROXIMITY9_ALS_CONF_REG:
 *      set: PROXIMITY9_ALS_IT_320_MS;
 * PROXIMITY9_PS_CONF_REG:
 *      set: PROXIMITY9_PS_OUTPUT_16BIT | 
 *           PROXIMITY9_PS_INT_TRIGGER_BOTH | 
 *           PROXIMITY9_PS_IR_ON_1_OFF_80 | 
 *           PROXIMITY9_PS_IT_8T;
 * PROXIMITY9_PS_MS_REG:
 *      set: PROXIMITY9_PS_NORMAL_OP_MODE | 
 *           PROXIMITY9_LED_I_160_MA;
 * PROXIMITY9_PS_THRSHD_L_REG:
 *      set: 30;
 * PROXIMITY9_PS_THRSHD_H_REG:
 *      set: 2000;
 * </pre>
 *
 * @description This function executes default configuration for Proximity9 Click.
 */
void proximity9_default_cfg ( proximity9_t *ctx );

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
void proximity9_generic_write ( proximity9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void proximity9_generic_read ( proximity9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic Read function
 *
 * @param ctx          Click object.
 * @param reg_addr     Address which from data be read
 * @param data_out     Memory location where data be stored
 *
 * @returns 0 - OK, 1 - Invalid register address
 *
 * @description This function reads a 16bit data from the desired register.
 */
PROXIMITY9_RETVAL proximity9_read_register ( proximity9_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Generic Write function
 *
 * @param ctx          Click object.
 * @param reg_addr     Address where data be written
 * @param data_in      Data to be written
 *
 * @returns 0 - OK, 1 - Invalid register address
 *
 * @description This function writes a 16bit data to the desired register.
 */
PROXIMITY9_RETVAL proximity9_write_register ( proximity9_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief INT Pin Check function
 *
 * @param ctx          Click object.
 * 
 * @returns 0 or 1
 *
 * @description This function returns the state of the INT pin.
 */
uint8_t proximity9_check_int_pin ( proximity9_t *ctx );

/**
 * @brief INT Flag Check function
 *
 * @param ctx          Click object.
 * @param bit_mask     Selects the flags to be checked
 *
 * @returns Flags status
 *
 * @description This function allows user to check a desired interrupt flags.
 */
uint8_t proximity9_check_int_flag ( proximity9_t *ctx, uint8_t bit_mask );

/**
 * @brief ALS Get function
 *
 * @param ctx          Click object.
 * 
 * @returns The real ALS value in lux unit
 *
 * @description This function allows user to get the ALS value calculated to lux.
 */
float proximity9_get_als_lux ( proximity9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY9_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
