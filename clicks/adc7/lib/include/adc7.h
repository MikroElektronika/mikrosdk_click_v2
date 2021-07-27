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
 * \brief This file contains API for ADC 7 Click driver.
 *
 * \addtogroup adc7 ADC 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADC7_H
#define ADC7_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define ADC7_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.drl = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.pre = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.mck = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.bsy = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADC7_RETVAL  uint8_t

#define ADC7_OK           0x00
#define ADC7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup filter_registers Filt registers
 * \{
 */
#define ADC7_SINC1_FILT             0x01
#define ADC7_SINC2_FILT             0x02
#define ADC7_SINC3_FILT             0x03
#define ADC7_SINC4_FILT             0x04
#define ADC7_SSINC_FILT             0x05
#define ADC7_FLAT_PASSBAND_FILT     0x06
#define ADC7_AVERAGING_FILT         0x07
 /** \} */

/**
* \defgroup downsample_registers Downsample registers
* \{
*/
#define ADC7_DOWNSAMPL_FACT_4       0x02
#define ADC7_DOWNSAMPL_FACT_8       0x03
#define ADC7_DOWNSAMPL_FACT_16      0x04
#define ADC7_DOWNSAMPL_FACT_32      0x05
#define ADC7_DOWNSAMPL_FACT_64      0x06
#define ADC7_DOWNSAMPL_FACT_128     0x07
#define ADC7_DOWNSAMPL_FACT_256     0x08
#define ADC7_DOWNSAMPL_FACT_512     0x09
#define ADC7_DOWNSAMPL_FACT_1024    0x0A
#define ADC7_DOWNSAMPL_FACT_2048    0x0B
#define ADC7_DOWNSAMPL_FACT_4096    0x0C
#define ADC7_DOWNSAMPL_FACT_8192    0x0D
#define ADC7_DOWNSAMPL_FACT_16384   0x0E
/** \} */

/**
 * \defgroup gain_registers Gain Registers
 * \{
 */
#define ADC7_GAIN_EXPAN_EN          0x01
#define ADC7_GAIN_COMPR_EN          0x02
#define ADC7_GAIN_DISABLE           0x00
/** \} */

/**
* \defgroup various_macros Various Macros
* \{
*/
#define ADC7_DATA_NOT_READY         0x01
#define ADC7_DATA_IS_READY          0x00
#define ADC7_DEVICE_IS_BUSY         0x01
#define ADC7_DEVICE_NOT_BUSY        0x00
#define ADC7_WRONG_GAIN_CONFIG      0x02
#define ADC7_WRONG_DOWNSAMPL_FACT   0x03
#define ADC7_WRONG_FILT_TYPE        0x04
/** \} */

/**
* \defgroup state_values State values
* \{
*/
#define ADC7_HIGH_STATE             0x01
#define ADC7_LOW_STATE              0x00
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
    digital_out_t cs;

    // Output pins 

    digital_out_t pre;
    digital_out_t mck;

    // Input pins 

    digital_in_t drl;
    digital_in_t bsy;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    uint16_t num_sampl;
    float volt_ref;
    float value_lsb;


} adc7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t drl;
    pin_name_t pre;
    pin_name_t mck;
    pin_name_t bsy;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    uint16_t dev_num_sampl;
    float dev_volt_ref;
    float dev_value_lsb;

} adc7_cfg_t;

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
void adc7_cfg_setup ( adc7_cfg_t *cfg );

/**
 * @brief Default Configuration Initialization function.
 *
 * @param ctx  Click object. 
 *
 * @description This function initializes default click configuration.
 */
void adc7_default_cfg ( adc7_t *ctx );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg  Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ADC7_RETVAL adc7_init ( adc7_t *ctx, adc7_cfg_t *cfg );

/**
 * @brief Configuration set function.
 *
 * @param ctx             Click object.
 * @param gain_config      Gain Configuration.
 * @param down_samp_factor Down Sampling Factor.
 * @param filter_type      Filter Type.
 *
 * @returns Is device busy or not.
 *
 * @description Function performs the device configuration by sending 
 * configuration data to configure the next conversion cycle.
 */
uint8_t adc7_set_config ( adc7_t* ctx, uint8_t gain_config,
                          uint8_t down_samp_factor, uint8_t filter_type );

/**
 * @brief Data Ready Check Function
 *
 * @param ctx             Click object.
 *
 * @returns 0 - Data is ready, 1 - Data is not ready.
 *
 * @description Function checks if data is ready for reading.
 */
uint8_t adc7_check_data_ready ( adc7_t* ctx );

/**
 * @brief Busy Check Function
 *
 * @param ctx             Click object.
 *
 * @returns 0 - Device is not busy, 1 - Device is busy.
 *
 * @description Function checks if device is busy.
 */
uint8_t adc7_check_busy ( adc7_t* ctx );

/**
 * @brief Set Clock
 *
 * @param ctx             Click object.
 * @param state            0 - low state, 1 - high state.
 *
 *
 * @description Function sets clock (MCK) pin to desired state.
 */
void adc7_set_clock ( adc7_t* ctx, uint8_t state );

/**
 * @brief Preset Mode
 *
 * @param ctx             Click object.
 * @param state            0 - Normal Mode, 1 - Preset Mode.
 *
 *
 * @description Function puts the device to Preset or to Normal Mode.
 */
void adc7_preset_mode ( adc7_t* ctx, uint8_t state );

/**
 * @brief Read Bytes Function
 *
 * @param ctx             Click object.
 * @param n_bytes         Number of bytes to be read.
 * @param data_out        Memory where data bytes be stored.
 *
 * @returns Is data ready or not.
 *
 * @description Function reads the desired number of data bytes. (32-bit 
 * converted data from ADC + configuration byte/bytes).
 */
uint8_t adc7_read_bytes ( adc7_t* ctx, uint8_t n_bytes, uint8_t* data_out );

/**
 * @brief Start Conversion Function
 *
 * @param ctx             Click object.
 *
 *
 * @description Function generates clock signal on MCK pin and on that way 
 * starts and performs the desired number of conversion cycles,
 * determined by Down Sampling Factor number.
 */
void adc7_start_conv_cycle ( adc7_t* ctx );

/**
 * @brief Start Conversion Function
 *
 * @param ctx             Click object.
 * @param voltage         Memory where converted voltage value is stored.
 *
 * @returns Is data ready or not.
 *
 * @description Function reads 32bit converted voltage value from AD converter
 * and calculates this value to mV.
 */
uint8_t adc7_read_results ( adc7_t* ctx, float* voltage );


#ifdef __cplusplus
}
#endif
#endif  // _ADC7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
