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
 * \brief This file contains API for Color 6 Click driver.
 *
 * \addtogroup color6 Color 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR6_H
#define COLOR6_H

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
#define COLOR6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR6_RETVAL  uint8_t

#define COLOR6_OK           0x00
#define COLOR6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define COLOR6_REG_OPERATIONAL_STATE          0x00
#define COLOR6_REG_API_GENERATION             0x02
#define COLOR6_REG_CONFIGURATION_REGISTER_1   0x06
#define COLOR6_REG_CONFIGURATION_REGISTER_2   0x07
#define COLOR6_REG_CONFIGURATION_REGISTER_3   0x08
#define COLOR6_REG_BREAK_TIME                 0x09
#define COLOR6_REG_EDGE_COUNT_VALUE           0x0A
#define COLOR6_REG_OPTIONS_REGISTER           0x0B
/** \} */

/**
 * \defgroup operational_state_registe Operational State Registe
 * \{
 */
#define COLOR6_OSR_STOP_MEASUREMENT           0x00
#define COLOR6_OSR_START_MEASUREMENT          0x80
#define COLOR6_OSR_POWER_DOWN_SWITCHED_OFF    0x00
#define COLOR6_OSR_POWER_DOWN_SWITCHED_ON     0x40
#define COLOR6_OSR_SOFTWARE_RESET             0x08
#define COLOR6_OSR_DOS_CONFIGURATION          0x02
#define COLOR6_OSR_DOS_MEASUREMENT            0x03
/** \} */

/**
 * \defgroup api_generation_register API Generation Register
 * \{
 */
#define COLOR6_AGEN_DEVICE_ID                 0x01
#define COLOR6_AGEN_MUTATION_NUMBER           0x02
/** \} */

/**
 * \defgroup configuration_register Configuration Register
 * \{
 */
#define COLOR6_CREG1_GAIN_XYZ_2048            0x00
#define COLOR6_CREG1_GAIN_XYZ_1024            0x10
#define COLOR6_CREG1_GAIN_XYZ_512             0x20
#define COLOR6_CREG1_GAIN_XYZ_256             0x30
#define COLOR6_CREG1_GAIN_XYZ_128             0x40
#define COLOR6_CREG1_GAIN_XYZ_64              0x50
#define COLOR6_CREG1_GAIN_XYZ_32              0x60
#define COLOR6_CREG1_GAIN_XYZ_16              0x70
#define COLOR6_CREG1_GAIN_XYZ_8               0x80
#define COLOR6_CREG1_GAIN_XYZ_4               0x90
#define COLOR6_CREG1_GAIN_XYZ_2               0xA0
#define COLOR6_CREG1_GAIN_XYZ_1               0xB0
/** \} */

/**
 * \defgroup time Time
 * \{
 */
#define COLOR6_CREG1_TIME_1ms                 0x00
#define COLOR6_CREG1_TIME_2ms                 0x01
#define COLOR6_CREG1_TIME_4ms                 0x02
#define COLOR6_CREG1_TIME_8ms                 0x03
#define COLOR6_CREG1_TIME_16ms                0x04
#define COLOR6_CREG1_TIME_32ms                0x05
#define COLOR6_CREG1_TIME_64ms                0x06
#define COLOR6_CREG1_TIME_128ms               0x07
#define COLOR6_CREG1_TIME_256ms               0x08
#define COLOR6_CREG1_TIME_512ms               0x09
#define COLOR6_CREG1_TIME_1024ms              0x0A
#define COLOR6_CREG1_TIME_2048ms              0x0B
#define COLOR6_CREG1_TIME_4096ms              0x0C
#define COLOR6_CREG1_TIME_8192ms              0x0D
#define COLOR6_CREG1_TIME_16384ms             0x0E
/** \} */

/**
 * \defgroup configuration_register_creg2 Configuration Register CREG2
 * \{
 */
#define COLOR6_CREG2_EN_TM_DISABLE                       0x00
#define COLOR6_CREG2_EN_TM_ENABLE                        0x40
#define COLOR6_CREG2_DIGITAL_DIVIDER_DISABLE             0x00
#define COLOR6_CREG2_DIGITAL_DIVIDER_ENABLE              0x08
#define COLOR6_CREG2_DIVIDER_2                           0x00
#define COLOR6_CREG2_DIVIDER_4                           0x01
#define COLOR6_CREG2_DIVIDER_8                           0x02
#define COLOR6_CREG2_DIVIDER_16                          0x03
#define COLOR6_CREG2_DIVIDER_32                          0x04
#define COLOR6_CREG2_DIVIDER_64                          0x05
#define COLOR6_CREG2_DIVIDER_128                         0x06
#define COLOR6_CREG2_DIVIDER_256                         0x07
/** \} */

/**
 * \defgroup configuration_register_creg3 Configuration Register CREG3
 * \{
 */
#define COLOR6_CREG3_MMODE_CONT_MODE                     0x00
#define COLOR6_CREG3_MMODE_CMD_MODE                      0x40
#define COLOR6_CREG3_MMODE_SYNS_MODE                     0x80
#define COLOR6_CREG3_MMODE_SIND_MODE                     0xC0
#define COLOR6_CREG3_SB_STANDBY_SWITCHED_OFF             0x00
#define COLOR6_CREG3_SB_STANDBY_SWITCHED_ON              0x10
#define COLOR6_CREG3_READY_PUSH_PULL_OUT                 0x00
#define COLOR6_CREG3_READY_OPEN_DRAIN_OUT                0x08
#define COLOR6_CREG3_INTERNAL_CLOCK_1024MHZ              0x00
#define COLOR6_CREG3_INTERNAL_CLOCK_2048MHZ              0x01
#define COLOR6_CREG3_INTERNAL_CLOCK_4096MHZ              0x02
#define COLOR6_CREG3_INTERNAL_CLOCK_8192MHZ              0x03
/** \} */

/**
 * \defgroup output_result_register_bank Output Result Register Bank
 * \{
 */
#define COLOR6_MREG_STATUS_REGISTER                      0x00
#define COLOR6_MREG_TEMPERATURE_MEASUREMENT              0x01
#define COLOR6_MREG_MEASUREMENT_X_CHANNEL                0x02
#define COLOR6_MREG_MEASUREMENT_Y_CHANNEL                0x03
#define COLOR6_MREG_MEASUREMENT_Z_CHANNEL                0x04
#define COLOR6_MREG_OUT_CONVERSION_LSB                   0x05
#define COLOR6_MREG_OUT_CONVERSION_MSB                   0x06
/** \} */

/**
 * \defgroup status_register Status Register
 * \{
 */
#define COLOR6_STATUS_OUTCONVOF                          0x80
#define COLOR6_STATUS_MRESOF                             0x40
#define COLOR6_STATUS_ADCOF                              0x20
#define COLOR6_STATUS_LDATA                              0x10
#define COLOR6_STATUS_NDATA                              0x08
#define COLOR6_STATUS_NOTREADY                           0x04
#define COLOR6_STATUS_STANDBY                            0x02
#define COLOR6_STATUS_POWER                              0x01
/** \} */

/**
 * \defgroup  full_scale_range_of_detectable_irradiance Full Scale Range of detectable irradiance
 * \{
 */
#define COLOR6_X_FSR_OF_GAIN_2048                       0.866
#define COLOR6_Y_FSR_OF_GAIN_2048                       0.932
#define COLOR6_Z_FSR_OF_GAIN_2048                       0.501
#define COLOR6_X_FSR_OF_GAIN_1024                       1.732
#define COLOR6_Y_FSR_OF_GAIN_1024                       1.865
#define COLOR6_Z_FSR_OF_GAIN_1024                       1.002
#define COLOR6_X_FSR_OF_GAIN_512                        3.463
#define COLOR6_Y_FSR_OF_GAIN_512                        3.730
#define COLOR6_Z_FSR_OF_GAIN_512                        2.003
#define COLOR6_X_FSR_OF_GAIN_256                        6.927
#define COLOR6_Y_FSR_OF_GAIN_256                        7.460
#define COLOR6_Z_FSR_OF_GAIN_256                        4.006
#define COLOR6_X_FSR_OF_GAIN_128                        13.854
#define COLOR6_Y_FSR_OF_GAIN_128                        14.919
#define COLOR6_Z_FSR_OF_GAIN_128                        8.012
#define COLOR6_X_FSR_OF_GAIN_64                         27.707
#define COLOR6_Y_FSR_OF_GAIN_64                         29.838
#define COLOR6_Z_FSR_OF_GAIN_64                         16.024
#define COLOR6_X_FSR_OF_GAIN_32                         55.414
#define COLOR6_Y_FSR_OF_GAIN_32                         59.677
#define COLOR6_Z_FSR_OF_GAIN_32                         32.048
#define COLOR6_X_FSR_OF_GAIN_16                         110.828
#define COLOR6_Y_FSR_OF_GAIN_16                         119.354
#define COLOR6_Z_FSR_OF_GAIN_16                         64.097
#define COLOR6_X_FSR_OF_GAIN_8                          221.657
#define COLOR6_Y_FSR_OF_GAIN_8                          238.707
#define COLOR6_Z_FSR_OF_GAIN_8                          128.194
#define COLOR6_X_FSR_OF_GAIN_4                          443.314
#define COLOR6_Y_FSR_OF_GAIN_4                          477.415
#define COLOR6_Z_FSR_OF_GAIN_4                          256.387
#define COLOR6_X_FSR_OF_GAIN_2                          886.628
#define COLOR6_Y_FSR_OF_GAIN_2                          954.830
#define COLOR6_Z_FSR_OF_GAIN_2                          512.774
#define COLOR6_X_FSR_OF_GAIN_1                          1773.255
#define COLOR6_Y_FSR_OF_GAIN_1                          1909.659
#define COLOR6_Z_FSR_OF_GAIN_1                          1025.548
/** \} */

/**
 * \defgroup  number_of_clocks Number of clocks
 * \{
 */
#define COLOR6_NUMBER_OF_CLK_TIME_1ms                   1024
#define COLOR6_NUMBER_OF_CLK_TIME_2ms                   2048
#define COLOR6_NUMBER_OF_CLK_TIME_4ms                   4096
#define COLOR6_NUMBER_OF_CLK_TIME_8ms                   8192
#define COLOR6_NUMBER_OF_CLK_TIME_16ms                  16384
#define COLOR6_NUMBER_OF_CLK_TIME_32ms                  32768
#define COLOR6_NUMBER_OF_CLK_TIME_64ms                  65536
#define COLOR6_NUMBER_OF_CLK_TIME_128ms                 131072
#define COLOR6_NUMBER_OF_CLK_TIME_256ms                 262144
#define COLOR6_NUMBER_OF_CLK_TIME_512ms                 524288
#define COLOR6_NUMBER_OF_CLK_TIME_1024ms                1048576
#define COLOR6_NUMBER_OF_CLK_TIME_2048ms                2097152
#define COLOR6_NUMBER_OF_CLK_TIME_4096ms                4194304
#define COLOR6_NUMBER_OF_CLK_TIME_8192ms                8388608
#define COLOR6_NUMBER_OF_CLK_TIME_16384ms               16777216

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

    uint8_t set_gain;
    uint8_t set_time;
    float   fsr;         
    uint32_t num_of_clk;   


} color6_t;

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

} color6_cfg_t;

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
void color6_cfg_setup ( color6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param color6 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COLOR6_RETVAL color6_init ( color6_t *ctx, color6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Color6 click.
 */
void color6_default_cfg ( color6_t *ctx );

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
void color6_generic_write ( color6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void color6_generic_read ( color6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for write one byte in register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param r_data       Register data.
 *
 * @description This function write one byte in register.
 */
void color6_write_byte ( color6_t *ctx, uint8_t reg, uint8_t r_data );

/**
 * @brief Functions for read one byte data from register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads one byte data from register.
 */
uint8_t color6_read_byte ( color6_t *ctx, uint8_t reg );

/**
 * @brief Functions for read data from register.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads data from register.
 */
uint16_t color6_read_data ( color6_t *ctx, uint8_t reg );

/**
 * @brief Functions for read temperature.
 *
 * @param ctx          Click object.
 *
 * @description The measurement result is available as TEMP of the output result registers.
 */
float color6_get_temperature ( color6_t *ctx );

/**
 * @brief Functions for software reset.
 *
 * @param ctx          Click object.
 *
 * @description This function should be called at the start of the program before the configuration of the chip.
 */
void color6_software_reset ( color6_t *ctx ); 

/**
 * @brief Functions for go to measurement mode.
 *
 * @param ctx          Click object.
 *
 * @description This function should be called before the start measurement.
 */
void color6_go_to_measurement_mode ( color6_t *ctx );

/**
 * @brief Functions for go to measurement mode.
 *
 * @param ctx          Click object.
 * @param channel          channel from which the data will be converted.
 * @param mres_data        data read from the channel.
 *
 * @description This function should be called before the start measurement.
 */
float color6_converting_to_ee ( color6_t *ctx, uint8_t channel, uint16_t mres_data );
#ifdef __cplusplus
}
#endif
#endif  // _COLOR6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
