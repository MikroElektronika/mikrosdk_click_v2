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
 * \brief This file contains API for ADC 3 Click driver.
 *
 * \addtogroup adc3 ADC 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADC3_H
#define ADC3_H

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
#define ADC3_MAP_MIKROBUS( cfg, mikrobus )        \
  cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADC3_RETVAL  uint8_t

#define ADC3_OK                           0x00
#define ADC3_INIT_ERROR                   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define ADC3_I2C_SLAVE_ADDR               0x68
/** \} */

/**
 * \defgroup cfg_reg Configuration register
 * \{
 */
#define ADC3_CFG_REG                      0x00
/** \} */

/**
 * \defgroup pga_gain PGA Gain Selection
 */
#define ADC3_PGA_GAIN_X1                  0x00
#define ADC3_PGA_GAIN_X2                  0x01
#define ADC3_PGA_GAIN_X4                  0x02
#define ADC3_PGA_GAIN_X8                  0x03
/** \} */

/**
 * \defgroup sample_rate Sample Rate Selection
 */
#define ADC3_SAMPLE_RATE_12               0x00
#define ADC3_SAMPLE_RATE_14               0x04
#define ADC3_SAMPLE_RATE_16               0x08
/** \} */

/**
 * \defgroup conv_mode Conversion Mode Bit
 */
#define ADC3_CONV_ONE_SHOT                0x00
#define ADC3_CONV_CONTINOUS               0x10
/** \} */

/**
 * \defgroup select_channel Channel Selection
 */
#define ADC3_SELECT_CHANNEL_1             0x00
#define ADC3_SELECT_CHANNEL_2             0x20
#define ADC3_SELECT_CHANNEL_3             0x40
#define ADC3_SELECT_CHANNEL_4             0x60
/** \} */

/**
 * \defgroup data Data
 */
#define ADC3_DATA_START_VALUE              0
#define ADC3_DATA_RESOL_RATE_12            0x0F
#define ADC3_DATA_RESULT_RATE_12           0x07FF
#define ADC3_DATA_RESOL_RATE_14            0x3F
#define ADC3_DATA_RESULT_RATE_14           0x1FFF
#define ADC3_DATA_RESOL_RATE_16            0xFF
#define ADC3_DATA_RESULT_RATE_16           0x7FFF

/** \} */

/**
 * \defgroup rdy Ready Bit Mode
 */
#define ADC3_RDY_SET                      0x80
#define ADC3_RDY_CLEAR                    0x00
/** \} */

/**
 * \defgroup general_call General Call addresses
 */
#define ADC3_GENERAL_CALL_RESET           0x06
#define ADC3_GENERAL_CALL_LATCH           0x04
#define ADC3_GENERAL_CALL_CONVERSION      0x08
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

} adc3_t;

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

} adc3_cfg_t;

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
 * @param cfg          Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void adc3_cfg_setup ( adc3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx         Click object.
 * @param cfg          Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
ADC3_RETVAL adc3_init ( adc3_t *ctx, adc3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx          Click object.
 *
 * @description This function executes default configuration for Adc3 Click.
 */
void adc3_default_cfg ( adc3_t *ctx );

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
void adc3_generic_write ( adc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void adc3_generic_read ( adc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief General call reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to initiate general call reset.
 * @note The device will abort current conversion and perform internal reset and latch the logic status of external address selection pins.
 */
void adc3_reset ( adc3_t *ctx );

/**
 * @brief General call latch function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to initiate general call latch.
 * @note The device will latch the logic status of the external address selection pins, but will not perform a reset.
 */
void adc3_latch ( adc3_t *ctx );

/**
 * @brief General call conversion function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to initiate general call conversion.
 * @note When the device receives this command, the configuration will be set to the One-Shot Conversion mode 
 *       and a single conversion will be performed. The PGA and data rate settings are unchanged with this general call.
 */
void adc3_conversion ( adc3_t *ctx );

/**
 * @brief ADC3 read measurement function.
 *
 * @param ctx          Click object.
 * @param channel      8-bit data representing channel, conversion mode, conversion rate, and PGA gain values.
 * @param resolution   8-bit data representing conversion rate.
 * @param gain         8-bit data representing PGA gain.
 * 
 * @return result      16-bit value read from output register
 *
 * @description This function is used to read digitaly converted data from any of the 4 channels.
 * @note Function converts data correctly, and then uses default settings from datasheet for further operation.
 */
int16_t adc3_read_measurement ( adc3_t *ctx, uint8_t channel, uint8_t resolution, uint8_t gain );

/**
 * @brief Read voltage function.
 *
 * @param ctx          Click object.
 * @param channel      8-bit data representing channel, conversion mode, conversion rate, and PGA gain values.
 * @param resolution   8-bit data representing conversion rate.
 * @param gain         8-bit data representing PGA gain.
 * 
 * @return result      16-bit value read from output register
 *
 * @description This function is used to read ADC value and calculate voltage.
 * @note Function converts data correctly, and then uses default settings from datasheet for further operation.
 */
float adc3_read_voltage ( adc3_t *ctx, uint8_t channel, uint8_t resolution, uint8_t gain );

#ifdef __cplusplus
}
#endif
#endif  // _ADC3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
