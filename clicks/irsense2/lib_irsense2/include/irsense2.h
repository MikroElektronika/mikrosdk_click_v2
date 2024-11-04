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
 * \brief This file contains API for IR Sense 2 Click driver.
 *
 * \addtogroup irsense2 IR Sense 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRSENSE2_H
#define IRSENSE2_H

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
#define IRSENSE2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRSENSE2_RETVAL  uint8_t

#define IRSENSE2_OK           0x00
#define IRSENSE2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup reg_addr Register Addresses
 * \{
 */
#define IRS
#define COMPANY_CODE_WIA1                    0x00
#define DEVICE_ID_WIA2                       0x01
#define INFO_1                               0x02
#define INFO_2                               0x03
#define STATUS_1_ST1                         0x04
#define STATUS_2_ST2                         0x0A
#define INTCAUSE                             0x05
#define IR_SENSOR_LSB                        0x06
#define IR_SENSOR_MSB                        0x07
#define TMP_SENSOR_LSB                       0x08
#define TMP_SENSOR_MSB                       0x09
#define THIRH_IR_THRESHOLD_LVL_LSB           0x0B 
#define THIRH_IR_THRESHOLD_LVL_MSB           0x0C
#define THIRL_IR_THRESHOLD_LVL_LSB           0x0D
#define THIRL_IR_THRESHOLD_LVL_MSB           0x0E
#define THTMPH_TEMP_SENS_THRESHOLD_LV_LSB    0x0F
#define THTMPH_TEMP_SENS_THRESHOLD_LV_MSB    0x10
#define THTMPL_TEMP_SENS_THRESHOLD_LV_LSB    0x11 
#define THTMPL_TEMP_SENS_THRESHOLD_LV_MSB    0x12
#define INTEN_INTERRUPT_FACTOR_SETTING       0x13
#define CNTL1_CUT_OFF_FREQ_SETTING           0x14
#define CNTL2_OPERATING_MODE_SETTING         0x15
#define CNTL3_SOFT_RESET                     0x16
/** \} */

/**
 * \defgroup rst_mask Reset masks
 * \{
 */
#define ST1_RST                              0xFE
#define INTCAUSE_RST                         0xE0
#define IR_RST                               0x00
#define TMP_RST                              0x00
#define ST2_RST                              0xFE
#define THIRH_THIRL_THTMPH_THTMPL_RST        0x00
#define INTEN_RST                            0xE0
#define CNTL1_RST                            0xE0
#define CNTL2_RST                            0xFC
#define CNTL3_RST                            0xFE
/** \} */

/**
 * \defgroup mode Modes
 * \{
 */
#define INTEN_MODE_MASK_DATARDY_INT_VALID    0xE1       
#define CNTL1_IR__MODE_MASK_NO_FILTER        0xE0
#define CNTL1_IR__MODE_MASK_FC_2_5HZ         0xE8
#define CNTL1_IR_MODE_MASK_FC_0_9HZ          0xF0
#define CNTL1_IR_MODE_MASK_FC_0_45HZ         0xF8
#define CNTL1_TMP_MODE_MASK_NO_FILTER        0xE0
#define CNTL1_TMP_MODE_MASK_FC_2_5HZ         0xE1
#define CNTL1_TMP_MODE_MASK_FC_0_9HZ         0xE2                      
#define CNTL1_TMP_MODE_MASK_FC_0_45HZ        0xE3 
#define CNTL1_TMP_MODE_MASK_FC_0_22HZ        0xE4
#define CNTL2_STANDBY_MODE                   0xFC
#define CNTL2_CONTINUOUS_MODE                0xFD
#define CNTL2_SINGLE_SHOT_MODE               0xFE
#define CNTL3_RESET_MODE                     0xFF
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

    uint8_t data_flag;
    float prev_ir_data;
    float prev_ir_data2;

} irsense2_t;

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
    uint8_t data_flag_cfg;
    int8_t prev_ir_data_cfg;
    int8_t prev_ir_data_cfg2;

} irsense2_cfg_t;

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
void irsense2_cfg_setup ( irsense2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param irsense2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
IRSENSE2_RETVAL irsense2_init ( irsense2_t *ctx, irsense2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for IrSense2 Click.
 */
void irsense2_default_cfg ( irsense2_t *ctx );

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
void irsense2_generic_write ( irsense2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void irsense2_generic_read ( irsense2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Data function.
 *
 * 
 * @param ctx          Click object.
 * @param ir_data      16bit Data read and adjusted from the IR sensor.
 * @param temp_data    16bit Data read and adjusted from the temperature sensor.
 *
 * @description This function reads data from IR and Temeprature sensors and adjusts them with apropriate values.
 */
void irsense2_data_read ( irsense2_t *ctx, float *ir_data, float *temp_data );

/**
 * @brief IR Data read function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @retval 16bit value from IR sensor's register.
 *
 * @description This function reads and returns 16bit value from the IR senor.
 */
int16_t irsense2_get_ir_data ( irsense2_t *ctx );

/**
 * @brief Temperatire Data read function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @retval 16bit value from Temperature sensor's register.
 *
 * @description This function reads and returns 16bit value from the Temperature senor.
 */
int16_t irsense2_get_temperature_data ( irsense2_t *ctx );

/**
 * @brief Interrupt factor function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function reads from interrupt factor information register.
 */
void irsense2_get_int ( irsense2_t *ctx );

/**
 * @brief Human detection function.
 *
 * 
 * @param ctx          Click object.
 * @param ir_data      Currently read IR sensor data
 *
 * @description This function calculates differences in read IR sensor data and
 * determines if there was a presence that tireggered a change.
 */
uint8_t irsense_human_detected ( irsense2_t *ctx, float ir_data );

/**
 * @brief Int_pin state function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function gets int_pin state.
 */
void irsense2_get_int_pin( irsense2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _IRSENSE2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
