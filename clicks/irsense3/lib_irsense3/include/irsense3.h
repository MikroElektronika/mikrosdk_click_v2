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
 * \brief This file contains API for IR Sense 3 Click driver.
 *
 * \addtogroup irsense3 IR Sense 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRSENSE3_H
#define IRSENSE3_H

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
#define IRSENSE3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRSENSE3_RETVAL  uint8_t

#define IRSENSE3_OK           0x00
#define IRSENSE3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define IRSENSE3_REG_COMPANY_CODE  0x00
#define IRSENSE3_REG_DEVICE_ID     0x01
#define IRSENSE3_REG_INFO_1        0x02
#define IRSENSE3_REG_INFO_2        0x03
#define IRSENSE3_REG_STATUS_1      0x04
#define IRSENSE3_REG_IR_LSB        0x05
#define IRSENSE3_REG_IR_MSB        0x06
#define IRSENSE3_REG_TEMP_LSB      0x07
#define IRSENSE3_REG_TEMP_MSB      0x08
#define IRSENSE3_REG_STATUS_2      0x09
#define IRSENSE3_REG_STATUS_3      0x0A
#define IRSENSE3_REG_STATUS_4      0x1F
#define IRSENSE3_REG_CTRL_1        0x20
#define IRSENSE3_REG_CTRL_2        0x21
#define IRSENSE3_REG_CTRL_3        0x22
#define IRSENSE3_REG_CTRL_4        0x23
#define IRSENSE3_REG_CTRL_5        0x24
#define IRSENSE3_REG_CTRL_6        0x25
#define IRSENSE3_REG_CTRL_7        0x26
#define IRSENSE3_REG_CTRL_8        0x27
#define IRSENSE3_REG_CTRL_9        0x28
#define IRSENSE3_REG_CTRL_10       0x29
#define IRSENSE3_REG_CTRL_11       0x2A
#define IRSENSE3_REG_CTRL_12       0x2B
/** \} */

/**
 * \defgroup return_info Return info
 * \{
 */
#define IRSENSE3_DEVICE_ID     0x15
#define IRSENSE3_COMPANY_CODE  0x48
/** \} */

/**
 * \defgroup ctrl1 Control 1 Register
 * \{
 */
#define IRSENSE3_CTRL1_NORMAL_STATE    0xFE
#define IRSENSE3_CTRL1_SOFTWARE_RESET  0xFF
/** \} */

/**
 * \defgroup ctrl2 Control 2 Register
 * \{
 */
#define IRSENSE3_CTRL2_NO_SYNC      0xFC
#define IRSENSE3_CTRL2_MASTER_SYNC  0xFD
#define IRSENSE3_CTRL2_SLAVE_SYNC   0xFE
/** \} */

/**
 * \defgroup ctrl3 Control 3 Register
 * \{
 */
#define IRSENSE3_CTRL3_LOW_NOISE_DISABLE    0x80
#define IRSENSE3_CTRL3_LOW_NOISE_ENABLE     0xC0
#define IRSENSE3_CTRL3_ODR_1Hz              0x80
#define IRSENSE3_CTRL3_ODR_2Hz              0x90
#define IRSENSE3_CTRL3_ODR_10Hz             0xA0
#define IRSENSE3_CTRL3_ODR_50Hz             0xB0
#define IRSENSE3_CTRL3_NO_TEMP_FILTER       0x80
#define IRSENSE3_CTRL3_TEMP_FILTER_0p9Hz    0x84
#define IRSENSE3_CTRL3_TEMP_FILTER_0p445Hz  0x88
#define IRSENSE3_CTRL3_NO_IR_FILTER         0x80
#define IRSENSE3_CTRL3_IR_FILTER_0p9Hz      0x81
#define IRSENSE3_CTRL3_IR_FILTER_0p445Hz    0x82
/** \} */

/**
 * \defgroup ctrl4 Control 4 Register
 * \{
 */
#define IRSENSE3_CTRL4_TOPT_THR_DISABLE    0xF8
#define IRSENSE3_CTRL4_TOPT_THR_ENABLE     0xFC
#define IRSENSE3_CTRL4_TOPT_NOISE_DISABLE  0xF8
#define IRSENSE3_CTRL4_TOPT_NOISE_ENABLE   0xFB
/** \} */

/**
 * \defgroup ctrl7 Control 7 Register
 * \{
 */
#define IRSENSE3_CTRL7_HUMAN_DETECT_NORMAL      0xF0
#define IRSENSE3_CTRL7_HUMAN_DETECT_INVERT      0xF8
#define IRSENSE3_CTRL7_HUMAN_DETECT_TIME_0sec   0xF0
#define IRSENSE3_CTRL7_HUMAN_DETECT_TIME_5sec   0xF1
#define IRSENSE3_CTRL7_HUMAN_DETECT_TIME_10sec  0xF2
#define IRSENSE3_CTRL7_HUMAN_DETECT_TIME_30sec  0xF3
#define IRSENSE3_CTRL7_HUMAN_DETECT_TIME_300sec 0xF4
/** \} */

/**
 * \defgroup ctrl11 Control 11 Register
 * \{
 */
#define IRSENSE3_CTRL11_HBDEN_OFF                0xE0
#define IRSENSE3_CTRL11_HBDEN_ON                 0xF0
#define IRSENSE3_CTRL11_DO_NOT_STOP_UPDATING_SB  0xE0
#define IRSENSE3_CTRL11_STOP_UPDATING_SB         0xE8
#define IRSENSE3_CTRL11_STREAMING_BUFFER_OFF     0xE0
#define IRSENSE3_CTRL11_STREAMING_BUFFER_ON      0xE4
#define IRSENSE3_CTRL11_INT_HUMAN_DISABLE        0xE0
#define IRSENSE3_CTRL11_INT_HUMAN_ENABLE         0xE2
#define IRSENSE3_CTRL11_INT_DRDY_DISABLE         0xE0
#define IRSENSE3_CTRL11_INT_DRDY_ENABLE          0xE1
/** \} */

/**
 * \defgroup ctrl12 Control 12 Register
 * \{
 */
#define IRSENSE3_CTRL12_STANDBY_MODE      0xFE
#define IRSENSE3_CTRL12_CONTINUOUS_MODE   0xFF
/** \} */

/**
 * \defgroup human_detect Human detect
 * \{
 */
#define IRSENSE3_PRESENCE_IS_DETECTED 0x01
#define IRSENSE3_PRESENCE_IS_NOT_DETECTED 0x00
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

} irsense3_t;

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

} irsense3_cfg_t;

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
void irsense3_cfg_setup ( irsense3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param irsense3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
IRSENSE3_RETVAL irsense3_init ( irsense3_t *ctx, irsense3_cfg_t *cfg );


/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for IrSense3 Click.
 */
void irsense3_default_cfg ( irsense3_t *ctx );

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
void irsense3_generic_write ( irsense3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void irsense3_generic_read ( irsense3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get Interrupt state
 *
 * @param ctx          Click object.
 *
 * @retval Interrupt state on the INT pin
 */
uint8_t irsense3_get_interrupt_state ( irsense3_t *ctx );

/**
 * @brief Temperature data
 *
 * @param ctx          Click object.
 *
 * @retval Temperature data in [C]
 */
float irsense3_get_temperature_data ( irsense3_t *ctx );

/**
 * @brief Output current of IR sensor
 *
 * @param ctx          Click object.
 *
 * @retval Current of the IR sensor in [pA]
 */
float irsense3_get_ir_sensor_data ( irsense3_t *ctx );

/**
 * @brief Human approach detection
 *
 * @param ctx          Click object.
 *
 * @retval 1 - if presence is detected or 0 - if there isn't presence detected
 */
uint8_t irsense3_human_approach_detect ( irsense3_t *ctx );

/**
 * @brief Software reset
 *
 * @param ctx          Click object.
 */
void irsense3_software_reset( irsense3_t *ctx );

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
void irsense3_generic_write ( irsense3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void irsense3_generic_read ( irsense3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif  // _IRSENSE3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
