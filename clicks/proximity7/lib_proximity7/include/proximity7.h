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
 * \brief This file contains API for PROXIMITY 7 Click driver.
 *
 * \addtogroup proximity7 PROXIMITY 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY7_H
#define PROXIMITY7_H

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
#define PROXIMITY7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY7_RETVAL  uint8_t

#define PROXIMITY7_OK           0x00
#define PROXIMITY7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address Device address
 * \{
 */
#define PROXIMITY7_DEVICE_ADDRESS  0x39
/** \} */

/**
 * \defgroup transaction_type Transaction type
 * \{
 */ 
#define PROXIMITY7_REPEATED_BYTE                          0x80
#define PROXIMITY7_AUTO_INCREMENT                         0xA0
#define PROXIMITY7_RESERVED                               0xC0
#define PROXIMITY7_SPECIAL_FUNCTION                       0xE0
/** \} */

/**
 * \defgroup special_function Special function
 * \{
 */
#define PROXIMITY7_NO_ACTION                              0x00
#define PROXIMITY7_PROXIMITY_INT_PIN_CLEAR                0x05
#define PROXIMITY7_ALS_INT_PIN_CLEAR                      0x06
#define PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR        0x07
/** \} */

/**
 * \defgroup register_addresses Register addresses
 * \{
 */
#define PROXIMITY7_ENABLE                                 0x00
#define PROXIMITY7_ALS_ADC_TIME                           0x01
#define PROXIMITY7_PROXIMITY_ADC_TIME                     0x02
#define PROXIMITY7_WAIT_TIME                              0x03
#define PROXIMITY7_LOW_ALS_INT_PIN_THRESHOLD_LOW          0x04
#define PROXIMITY7_LOW_ALS_INT_PIN_THRESHOLD_HIGH         0x05
#define PROXIMITY7_HIGH_ALS_INT_PIN_THRESHOLD_LOW         0x06
#define PROXIMITY7_HIGH_ALS_INT_PIN_THRESHOLD_HIGH        0x07
#define PROXIMITY7_LOW_PROXIMITY_INT_PIN_THRESHOLD_LOW    0x08
#define PROXIMITY7_LOW_PROXIMITY_INT_PIN_THRESHOLD_HIGH   0x09
#define PROXIMITY7_HIGH_PROXIMITY_INT_PIN_THRESHOLD_LOW   0x0A
#define PROXIMITY7_HIGH_PROXIMITY_INT_PIN_THRESHOLD_HIGH  0x0B
#define PROXIMITY7_INT_PIN_PERSISTANCE_FILTERS            0x0C
#define PROXIMITY7_CONFIGURATION                          0x0D
#define PROXIMITY7_PROXIMITY_PULSE_COUNT                  0x0E
#define PROXIMITY7_GAIN_CONTROL                           0x0F
#define PROXIMITY7_ID                                     0x12
#define PROXIMITY7_STATUS                                 0x13
#define PROXIMITY7_CH0_ADC_DATA_LOW                       0x14
#define PROXIMITY7_CH0_ADC_DATA_HIGH                      0x15
#define PROXIMITY7_CH1_ADC_DATA_LOW                       0x16
#define PROXIMITY7_CH1_ADC_DATA_HIGH                      0x17
#define PROXIMITY7_PROXIMITY_ADC_DATA_LOW                 0x18
#define PROXIMITY7_PROXIMITY_ADC_DATA_HIGH                0x19
#define PROXIMITY7_PROXIMITY_OFFSET                       0x1E
/** \} */

/**
 * \defgroup enable_register Enable register
 * \{
 */
#define PROXIMITY7_SLEEP_AFTER_INT_PIN                    0x40
#define PROXIMITY7_PROXIMITY_INT_PIN_MASK                 0x20
#define PROXIMITY7_ALS_INT_PIN_MASK                       0x10
#define PROXIMITY7_WAIT_ENA                               0x08
#define PROXIMITY7_PROXIMITY_ENA                          0x04
#define PROXIMITY7_ALS_ENA                                0x02
#define PROXIMITY7_POWER_ON                               0x01
/** \} */

/**
 * \defgroup persistence_filter Persistence filter
 * \{
 */
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_EVERY  0x00
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_1      0x10
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_2      0x20
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_3      0x30
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_4      0x40
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_5      0x50
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_6      0x60
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_7      0x70
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_8      0x80
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_9      0x90
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_10     0xA0
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_11     0xB0
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_12     0xC0
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_13     0xD0
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_14     0xE0
#define PROXIMITY7_PPERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_15     0xF0

#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_EVERY  0x00
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_1      0x01
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_2      0x02
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_3      0x03
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_5      0x04
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_10     0x05
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_15     0x06
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_20     0x07
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_25     0x08
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_30     0x09
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_35     0x0A
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_40     0x0B
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_45     0x0C
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_50     0x0D
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_55     0x0E
#define PROXIMITY7_APERS_CONSECUTIVE_VALUES_OUT_OF_RANGE_60     0x0F
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define PROXIMITY7_ALS_GAIN_LEVEL         0x04
#define PROXIMITY7_WAIT_LONG              0x02
#define PROXIMITY7_PROXIMITY_DRIVE_LEVEL  0x01
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY7_LED_DRIVE_100mA        0x00
#define PROXIMITY7_LED_DRIVE_50mA         0x40
#define PROXIMITY7_LED_DRIVE_25mA         0x80
#define PROXIMITY7_LED_DRIVE_12p5mA       0xC0
#define PROXIMITY7_PROXIMITY_DIODE_CH1    0x20
#define PROXIMITY7_PROXIMITY_GAIN_1x      0x00
#define PROXIMITY7_PROXIMITY_GAIN_2x      0x04
#define PROXIMITY7_PROXIMITY_GAIN_4x      0x08
#define PROXIMITY7_PROXIMITY_GAIN_8x      0x0C
#define PROXIMITY7_ALS_GAIN_1x            0x00
#define PROXIMITY7_ALS_GAIN_8x            0x01
#define PROXIMITY7_ALS_GAIN_16x           0x02
#define PROXIMITY7_ALS_GAIN_120x          0x03
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define PROXIMITY7_PROXIMITY_SATURATION_MASK      0x40
#define PROXIMITY7_PROXIMITY_INT_PINERRUPT_MASK   0x20
#define PROXIMITY7_ALS_INT_PINERRUPT_MASK         0x10
#define PROXIMITY7_PROXIMITY_VALID_MASK           0x02
#define PROXIMITY7_ALS_VALID_MASK                 0x01
/** \} */

/**
 * \defgroup offset_sign Offset sign
 * \{
 */
#define PROXIMITY7_NEGATIVE  0x00
#define PROXIMITY7_POSITIVE  0x80
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

    float glass_attenuation;
    float const_b;
    float const_c;
    float const_d;
    float device_factor;

} proximity7_t;

typedef struct
{
    float glass_attenuation;
    float const_b;
    float const_c;
    float const_d;
    float device_factor;
} proximity7_const_t;

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

    proximity7_const_t dev_const;

} proximity7_cfg_t;


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
void proximity7_cfg_setup ( proximity7_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
uint8_t proximity7_init ( proximity7_t *ctx, proximity7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Proximity7 Click.
 */
void proximity7_default_cfg ( proximity7_t *ctx );

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
void proximity7_generic_write ( proximity7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void proximity7_generic_read ( proximity7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

 /**
 * @brief Setting ALS int_pinegration time.
 *
 * @param ctx                    Click object.
 * @param int_pinegration_time_      Int_pinegration time.
 * @param addr_reg
 *
 * @description This function sets ALS int_pinegration time.
 */
 uint8_t proximity7_set_als_integration_time( proximity7_t *ctx, float integration_time );

 /**
 * @brief Setting proximity int_pinegration time.
 *
 * @param ctx                     Click object.
 * @param int_pinegration_time_       Int_pinegration time. 
 *
 * @description This function sets priximity int_pinegration time.
 */
 uint8_t proximity7_set_proximity_integration_time( proximity7_t *ctx, float integration_time );

 /**
 * @brief Setting wait time.
 * 
 * @param ctx                      Click object.
 * @param wait_time_               Wait time.
 *
 * @description This function sets wait time.
 */
 uint8_t proximity7_set_wait_time( proximity7_t *ctx, float wait_time );

 /**
 * @brief Setting low ALS Ch0 threshold value.
 *
 * @param ctx                       Click object.
 * @param low_als_ch0_threshold_    Low ALS Ch0.
 *
 * @description This function sets low ALS Ch0 threshold value.
 */
 void proximity7_set_low_alsCh0_threshold( proximity7_t *ctx, uint16_t low_als_ch0_threshold );

/**
 * @brief Setting high ALS Ch0 threshold value.
 *
 * @param ctx                        Click object.
 * @param high_als_ch0_threshold_    High ALS Ch0.
 *
 * @description This function sets high ALS Ch0 threshold value.
 */
 void proximity7_set_high_alsCh0_threshold( proximity7_t *ctx, uint16_t high_als_ch0_threshold );

 /**
 * @brief Setting low proximity threshold.
 *
 * @param ctx                        Click object.
 * @param low_proximity_threshold_   Low proximity.
 *
 * @description This function sets low proximity threshold.
 */
 void proximity7_set_low_proximity_threshold( proximity7_t *ctx, uint16_t low_proximity_threshold );

 /**
 * @brief Setting high proximity threshold.
 *
 * @param ctx                         Click object.
 * @param high_proximity_threshold_   High proximity.
 *
 * @description This function sets high proximity threshold.
 */
 void proximity7_set_high_proximity_threshold( proximity7_t *ctx, uint16_t high_proximity_threshold );

 /**
 * @brief Setting int_pinerrupt persistance.
 *
 * @param ctx                         Click object.
 * @param als_int_pin_persistence         ALS int_pinerrupt.
 *
 * @description This function sets int_pinerrupt persistance for ALS and Proximity measurements.
 */
 void proximity7_set_int_persistance( proximity7_t *ctx, uint16_t proximity_int_persistence, uint16_t als_int_persistence );

 /**
 * @brief Setting proximity pulse count.
 *
 * @param ctx                         Click object.
 * @param proximity_pulse_count_      Proximity pulse count.
 *
 * @description This function sets proximity pulse count.
 */
 void proximity7_set_proximity_pulse_count( proximity7_t *ctx, uint8_t proximity_pulse_count );

 /**
 * @brief Getting channel  measurement data.
 *
 * @param ctx          Click object.
 *
 * @description This function gets data from channel 0 measurement.
 */
 uint16_t proximity7_get_als_data_ch0( proximity7_t *ctx );

 /**
 * @brief Getting channel 1 measurement data.
 *
 * @param ctx          Click object.
 *
 * @description This function gets data from channel 1 measurement.
 */
 uint16_t proximity7_get_als_data_ch1( proximity7_t *ctx );

 /**
 * @brief Getting proximity measurement data.
 * 
 * @param ctx          Click object.
 *
 * @description This function gets data from proximity measurement.
 */
 uint16_t proximity7_get_proximity_data( proximity7_t *ctx );

 /**
 * @brief Setting proximity offset.
 * 
 * @param ctx                            Click object.
 * @param proximity_offset_sign          Offset sign.
 * @param proximity_offset_magnitude_    Offset magnitude.
 *
 * @description This function returns 0 if offset value is in range.
                This function returns 1 if offset value is not in range 
 */
 uint8_t proximity7_set_proximity_offset( proximity7_t *ctx, uint8_t proximity_offset_sign, uint8_t proximity_offset_magnitude );

 /**
 * @brief Calculating LUX level.
 * 
 * @param ctx          Click object.
 *
 * @description This function calculates LUX level based on Ch0 and Ch1 data.
 */
 float proximity7_get_lux_level( proximity7_t *ctx );

 /**
 * @brief Checking INT_pin pin status.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function returns 0 if INT_pin pin is LOW.
 *               This function returns 1 if INT_pin pin is HIGH.
 */
 uint8_t proximity7_get_int_pin( proximity7_t *ctx );
          
 /**
 * @brief Generic read function.
 * 
 * @param ctx                   Click object.
 * @param set_const_data        Constant data.         
 *
 * @description This function reads data from the desired register.
 */
void proximity7_set_constants( proximity7_t *ctx, proximity7_const_t *set_const_data );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY7_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
