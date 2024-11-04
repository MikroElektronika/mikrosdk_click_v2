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
 * \brief This file contains API for PWM Click driver.
 *
 * \addtogroup pwm PWM Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PWM_H
#define PWM_H

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
#define PWM_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); 
/** \} */
 
/**
 * \defgroup    PWM_period_time_resolution  CH15 REG ADDRESS
 * \{
 */
#define PWM_MAX_RESOLUTION                                     4096
/** \} */
 
/**
 * \defgroup error_code Error Code
 * \{
 */
#define PWM_RETVAL  uint8_t
#define PWM_OK           0x00
#define PWM_INIT_ERROR   0xFF
/** \} */

/** \} */ // End group macro 
 
 // -------------------------------------------------------------- PRIVATE MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup  output_state output state
 * \{
 */
#define PWM_DISABLE   0x00
#define PWM_ENABLE    0x01
/** \} */

/**
 * \defgroup  mode1_bits MODE1_bits
 * \{
 */
#define PWM_RESTART                                            0x80
#define PWM_EXTCLK                                             0x40
#define PWM_AI                                                 0x20
#define PWM_SLEEP                                              0x10
#define PWM_SUB_1                                              0x08
#define PWM_SUB_2                                              0x04
#define PWM_SUB_3                                              0x02
#define PWM_ALL_CALL                                           0x01
/** \} */
 
/**
 * \defgroup  mode2_bits MODE2_bits
 * \{
 */
#define PWM_INVRT                                              0x10
#define PWM_OCH                                                0x08
#define PWM_OUTDRV                                             0x04
#define PWM_OUTNE1                                             0x02
#define PWM_OUTNE0                                             0x01
/** \} */
 
/**
 * \defgroup  slave_address SLAVE ADDRESS
 * \{
 */
#define PWM_I2C_ADDRESS                                        0x40
/** \} */
 
/**
 * \defgroup  mode1_reg_address MODE1_REG_ADDRESS
 * \{
 */
#define PWM_MODE1_REG                                          0x00
/** \} */
 
/**
 * \defgroup  mode2_reg_address MODE2_REG_ADDRESS
 * \{
 */
#define PWM_MODE2_REG                                          0x01
/** \} */
 
/**
 * \defgroup   pre_scale_reg_address PRE_SCALE REG ADDRESS
 * \{
 */
#define PWM_PRE_SCALE                                          0xFE
/** \} */
 
/**
 * \defgroup   test_reg_address TEST REG ADDRESS
 * \{
 */
#define PWM_TEST                                               0xFF
/** \} */
 
/**
 * \defgroup   ch0_reg_address  CH0 REG ADDRESS
 * \{
 */
#define PWM_CH0_ON_L                                           0x06   
#define PWM_CH0_ON_H                                           0x07   
#define PWM_CH0_OFF_L                                          0x08   
#define PWM_CH0_OFF_H                                          0x09   
/** \} */

/**
 * \defgroup   ch1_reg_address  CH1 REG ADDRESS
 * \{
 */
#define PWM_CH1_ON_L                                           0x0A  
#define PWM_CH1_ON_H                                           0x0B  
#define PWM_CH1_OFF_L                                          0x0C  
#define PWM_CH1_OFF_H                                          0x0D  
/** \} */
 
/**
 * \defgroup   ch2_reg_address  CH2 REG ADDRESS
 * \{
 */
#define PWM_CH2_ON_L                                           0x0E  
#define PWM_CH2_ON_H                                           0x0F  
#define PWM_CH2_OFF_L                                          0x10  
#define PWM_CH2_OFF_H                                          0x11  
/** \} */
 
/**
 * \defgroup   ch3_reg_address  CH3 REG ADDRESS
 * \{
 */
#define PWM_CH3_ON_L                                           0x12   
#define PWM_CH3_ON_H                                           0x13   
#define PWM_CH3_OFF_L                                          0x14   
#define PWM_CH3_OFF_H                                          0x15   
/** \} */
 
/**
 * \defgroup   ch4_reg_address  CH4 REG ADDRESS
 * \{
 */
#define PWM_CH4_ON_L                                           0x16   
#define PWM_CH4_ON_H                                           0x17   
#define PWM_CH4_OFF_L                                          0x18   
#define PWM_CH4_OFF_H                                          0x19   
/** \} */
 
/**
 * \defgroup   ch5_reg_address  CH5 REG ADDRESS
 * \{
 */
#define PWM_CH5_ON_L                                           0x1A  
#define PWM_CH5_ON_H                                           0x1B  
#define PWM_CH5_OFF_L                                          0x1C  
#define PWM_CH5_OFF_H                                          0x1D  
/** \} */
 
/**
 * \defgroup   ch6_reg_address  CH6 REG ADDRESS
 * \{
 */
#define PWM_CH6_ON_L                                           0x1E  
#define PWM_CH6_ON_H                                           0x1F  
#define PWM_CH6_OFF_L                                          0x20  
#define PWM_CH6_OFF_H                                          0x21  
/** \} */
 
/**
 * \defgroup   ch7_reg_address  CH7 REG ADDRESS
 * \{
 */
#define PWM_CH7_ON_L                                           0x22   
#define PWM_CH7_ON_H                                           0x23   
#define PWM_CH7_OFF_L                                          0x24   
#define PWM_CH7_OFF_H                                          0x25   
/** \} */
 
/**
 * \defgroup   ch8_reg_address  CH8 REG ADDRESS
 * \{
 */
#define PWM_CH8_ON_L                                           0x26  
#define PWM_CH8_ON_H                                           0x27  
#define PWM_CH8_OFF_L                                          0x28  
#define PWM_CH8_OFF_H                                          0x29  
/** \} */
 
/**
 * \defgroup   ch9_reg_address  CH9 REG ADDRESS
 * \{
 */
#define PWM_CH9_ON_L                                           0x2A  
#define PWM_CH9_ON_H                                           0x2B  
#define PWM_CH9_OFF_L                                          0x2C  
#define PWM_CH9_OFF_H                                          0x2D  
/** \} */
 
/**
 * \defgroup   ch10_reg_address  CH10 REG ADDRESS
 * \{
 */
#define PWM_CH10_ON_L                                          0x2E  
#define PWM_CH10_ON_H                                          0x2F  
#define PWM_CH10_OFF_L                                         0x30  
#define PWM_CH10_OFF_H                                         0x31  
/** \} */
 
/**
 * \defgroup   ch11_reg_address  CH11 REG ADDRESS
 * \{
 */
#define PWM_CH11_ON_L                                          0x32   
#define PWM_CH11_ON_H                                          0x33   
#define PWM_CH11_OFF_L                                         0x34   
#define PWM_CH11_OFF_H                                         0x35   
/** \} */
 
/**
 * \defgroup   ch12_reg_address  CH12 REG ADDRESS
 * \{
 */
#define PWM_CH12_ON_L                                          0x36 
#define PWM_CH12_ON_H                                          0x37 
#define PWM_CH12_OFF_L                                         0x38 
#define PWM_CH12_OFF_H                                         0x39 
/** \} */
 
/**
 * \defgroup   ch13_reg_address  CH13 REG ADDRESS
 * \{
 */
#define PWM_CH13_ON_L                                          0x3A   
#define PWM_CH13_ON_H                                          0x3B   
#define PWM_CH13_OFF_L                                         0x3C   
#define PWM_CH13_OFF_H                                         0x3D   
/** \} */

/**
 * \defgroup   ch14_reg_address  CH14 REG ADDRESS
 * \{
 */
#define PWM_CH14_ON_L                                          0x3E   
#define PWM_CH14_ON_H                                          0x3F   
#define PWM_CH14_OFF_L                                         0x40   
#define PWM_CH14_OFF_H                                         0x41   
/** \} */

/**
 * \defgroup   ch15_reg_address  CH15 REG ADDRESS
 * \{
 */
#define PWM_CH15_ON_L                                          0x42   
#define PWM_CH15_ON_H                                          0x43   
#define PWM_CH15_OFF_L                                         0x44   
#define PWM_CH15_OFF_H                                         0x45   
/** \} */
 
 /**
 * \defgroup   all_ch_reg_address  CH15 REG ADDRESS
 * \{
 */
#define PWM_ALL_CH_ON_L                                        0xFA   
#define PWM_ALL_CH_ON_H                                        0xFB   
#define PWM_ALL_CH_OFF_L                                       0xFC   
#define PWM_ALL_CH_OFF_H                                       0xFD   
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
    // Output pins 

    digital_out_t rst;
 
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} pwm_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
 
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} pwm_cfg_t;

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
void pwm_cfg_setup ( pwm_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
PWM_RETVAL pwm_init ( pwm_t *ctx, pwm_cfg_t *cfg );

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
void pwm_generic_write ( pwm_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void pwm_generic_read ( pwm_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );


/**
 * @brief Output state set function.
 *
 * @param ctx          Click object.
 * @param en_ou          Click object.
 *
 * @description This function set output state.
 */
void pwm_set_output ( pwm_t *ctx, uint8_t en_ou );

/**
 * @brief Device configuration function.
 *
 * @param ctx          Click object.
 * @param config[0]  if set to :
 *       - '0' :  does not respond to All Call I2C-bus address
 *       - '1' :  responds to All Call I2C-bus address
 * @param config[1]  if set to :
 *       - '0' :  does not respond to I2C-bus subaddress 3
 *       - '1' :  responds to I2C-bus subaddress 3
 * @param config[2]  if set to :
 *       - '0' :  does not respond to I2C-bus subaddress 2
 *       - '1' :  responds to I2C-bus subaddress 2
 * @param config[3]  if set to :
 *       - '0' :  does not respond to I2C-bus subaddress 1
 *       - '1' :  responds to I2C-bus subaddress 1
 * @param config[4]  if set to :
 *       - '0' :  Normal mode
 *       - '1' :  Low power mode, oscillator off
 * @param config[5]  if set to :
 *       - '0' :  Restart disabled
 *       - '1' :  Restart enabled
 *
 * @description This function configuration the device.
 */
void pwm_dev_config ( pwm_t *ctx,  uint8_t *config );

/**
 * @brief Output configuration function.
 *
 * @param ctx          Click object.
 * @param config[0]  if set to :
 *       - '0' :  output drivers not enabled
 *       - '1' :  if out = 1 drivers are enabled
 *       - '2' :  output drivers not enabled( high-impedance )
 * @param config1[1]  if set to :
 *       - '0' :  outputs are configured with an open-drain structure
 *       - '1' :  outputs are configured with a totem pole structure
 * @param config1[2]  if set to :
 *       - '0' :  outputs change on STOP command
 *       - '1' :  outputs change on ACK
 * @param config1[3]  if set to :
 *       - '0' :  output logic state not inverted; value to use when external driver used
 *       - '1' :  output logic state inverted; value to use when no external driver used
 *
 * @description This function configuration output.
 */
void pwm_output_config ( pwm_t *ctx, uint8_t *config1 );

/**
 * @brief Channel state function.
 *
 * @param ctx          Click object.
 * @param chann_id  4-bit value that defines what channel is used
 * @param state  if set to :
 *       - '0' :  output is disabled
 *       - '1' :  output is enabled
 *
 * @description This function is used to set the state of a specific channel.
 */
void pwm_channel_state ( pwm_t *ctx, uint8_t chann_id, uint8_t state );

/**
 * @brief Set channel raw function.
 *
 * @param ctx          Click object.
 * @param chann_id  4-bit value that defines what channel is used
 * @param raw_off_set  12-bit value that defines raw offset
 * @param raw_dc  12-bit value that defines raw DC
 *
 * @description This function is used to specific set channel output with data.
 */
void pwm_set_channel_raw ( pwm_t *ctx, uint8_t chann_id, uint16_t raw_off_set, uint16_t raw_dc );

/**
 * @brief All channels state function.
 *
 * @param ctx          Click object.
 * @param state  if set to :
 *       - '0' :  output is disabled
 *       - '1' :  output is enabled
 *
 * @description This function is used to set the state of all channels.
 */
void pwm_all_chann_state( pwm_t *ctx, uint8_t state );

/**
 * @brief Set pre scale function.
 *
 * @param ctx          Click object.
 * @param pre_scale 8-bit value that defines the frequency
 *
 * @description This function uses prescaler to program the PWM output frequency.
 */
void pwm_set_pre_scale ( pwm_t *ctx, uint8_t pre_scale );

/**
 * @brief Set all channels raw function.
 *
 * @param ctx          Click object.
 * @param raw_dc       12-bit value that defines raw DC
 *
 * @description This function is used to set all channels output with raw data.
 */
void pwm_set_all_raw ( pwm_t *ctx, uint16_t raw_dc );

#ifdef __cplusplus
}
#endif
#endif  // _PWM_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
