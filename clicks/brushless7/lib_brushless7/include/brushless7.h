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
 * \brief This file contains API for Brushless7 Click driver.
 *
 * \addtogroup brushless7 Brushless7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BRUSHLESS7_H
#define BRUSHLESS7_H

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
#include "drv_pwm.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BRUSHLESS7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.cmo  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.sby  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BRUSHLESS7_RETVAL  uint8_t

#define BRUSHLESS7_OK           0x00
#define BRUSHLESS7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr  Slave addr
 * \{
 */
#define  BRUSHLESS7_SLAVE_ADDR_ID2_LOW_ID1_LOW     0x29
#define  BRUSHLESS7_SLAVE_ADDR_ID2_LOW_ID1_HIGH    0x29
#define  BRUSHLESS7_SLAVE_ADDR_ID2_HIGH_ID1_LOW    0x2D
#define  BRUSHLESS7_SLAVE_ADDR_ID2_HIGH_ID1_HIGH   0x32
/** \} */
 
/**
 * \defgroup registers  Registers
 * \{
 */
#define  BRUSHLESS7_REG_0                 0
#define  BRUSHLESS7_REG_1                 1
#define  BRUSHLESS7_REG_2                 2
#define  BRUSHLESS7_REG_3                 3
#define  BRUSHLESS7_REG_4                 4
#define  BRUSHLESS7_REG_5                 5
#define  BRUSHLESS7_REG_6                 6
#define  BRUSHLESS7_REG_7                 7
#define  BRUSHLESS7_REG_8                 8
#define  BRUSHLESS7_REG_9                 9
#define  BRUSHLESS7_REG_10                10
#define  BRUSHLESS7_REG_11                11
#define  BRUSHLESS7_REG_12                12
#define  BRUSHLESS7_REG_13                13
#define  BRUSHLESS7_REG_14                14
#define  BRUSHLESS7_REG_15                15
#define  BRUSHLESS7_REG_16                16
#define  BRUSHLESS7_REG_17                17
#define  BRUSHLESS7_REG_18                18
#define  BRUSHLESS7_REG_19                19
#define  BRUSHLESS7_REG_20                20
#define  BRUSHLESS7_REG_21                21
#define  BRUSHLESS7_REG_22                22
#define  BRUSHLESS7_REG_23                23
#define  BRUSHLESS7_REG_24                24
#define  BRUSHLESS7_REG_25                25
#define  BRUSHLESS7_REG_26                26
#define  BRUSHLESS7_REG_27                27
#define  BRUSHLESS7_REG_28                28
#define  BRUSHLESS7_REG_29                29
#define  BRUSHLESS7_REG_30                30
#define  BRUSHLESS7_REG_86                86
#define  BRUSHLESS7_REG_87                87
/** \} */
 
/**
 * \defgroup error_code_dev Error Code dev
 * \{
 */
#define  BRUSHLESS7_DEV_ERROR             0xFF
#define  BRUSHLESS7_DEV_OK                0x00
/** \} */
 
/**
 * \defgroup max_speed  Max speed
 * \{
 */
#define  BRUSHLESS7_MAX_SPEED_4096        0x00
#define  BRUSHLESS7_MAX_SPEED_8192        0x02
#define  BRUSHLESS7_MAX_SPEED_16384       0x04
#define  BRUSHLESS7_MAX_SPEED_32768       0x06
/** \} */
 
/**
 * \defgroup ctrl_type  Ctrl type
 * \{
 */
#define  BRUSHLESS7_CTRL_TYPE_RPM         0xAA
#define  BRUSHLESS7_CTRL_TYPE_DUTY        0xBB
#define  BRUSHLESS7_CTRL_TYPE_STOP        0xCC
/** \} */
 
/**
 * \defgroup dir  Dir
 * \{
 */
#define  BRUSHLESS7_DIR_CW                0xDD
#define  BRUSHLESS7_DIR_CCW               0xEE
/** \} */

/**
 * \defgroup zero  Zero
 * \{
 */
#define BRUSHLESS7_ZERO                                0
/** \} */
 
/**
 * \defgroup start_duty  Start duty
 * \{
 */
#define BRUSHLESS7_START_DUTY_MAX                      49.8
#define BRUSHLESS7_START_DUTY_AMP                      512
/** \} */
 
/**
 * \defgroup stop_duty  Stop duty
 * \{
 */
#define BRUSHLESS7_STOP_DUTY_MAX                       49.6
#define BRUSHLESS7_STOP_DUTY_AMP                       256
#define BRUSHLESS7_STOP_DUTY_MASK                      0x80
/** \} */
 
/**
 * \defgroup change_duty  Change duty
 * \{
 */
#define BRUSHLESS7_CHANGE_DUTY_MIN                     0.4
#define BRUSHLESS7_CHANGE_DUTY_MAX                     99.6
#define BRUSHLESS7_CHANGE_DUTY_AMP                     256
/** \} */
 
/**
 * \defgroup max_duty  Max duty
 * \{
 */
#define BRUSHLESS7_MAX_DUTY_MIN                        50.2
#define BRUSHLESS7_MAX_DUTY_MAX                        100.0
#define BRUSHLESS7_MAX_DUTY_AMP                        512
#define BRUSHLESS7_MAX_DUTY_DEC                        257
/** \} */
 
/**
 * \defgroup start_rpm  Start rpm
 * \{
 */
#define BRUSHLESS7_START_RPM_MAX                       4095
#define BRUSHLESS7_START_RPM_SHIFT                     4
#define BRUSHLESS7_START_RPM_MASK                      0x0F
/** \} */
 
/**
 * \defgroup max_rpm  Max rpm
 * \{
 */
#define BRUSHLESS7_MAX_SPEED_RMP_MASK                  0xF9
/** \} */
 
/**
 * \defgroup precentage_div  Precentage div
 * \{
 */
#define BRUSHLESS7_PRECENTAGE_DIV                      100
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define BRUSHLESS7_DEF_FREQ                            5000
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

    digital_out_t dir;
    digital_out_t sby;

    // Input pins 

    digital_in_t cmo;
    digital_in_t int_pin;
    
    // Modules 

    pwm_t pwm;
    i2c_master_t i2c;

    // ctx variable 

    uint32_t  pwm_freq;
    uint8_t slave_address;

} brushless7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t cmo;
    pin_name_t dir;
    pin_name_t sby;
    pin_name_t int_pin;

    // static variable 

    uint32_t dev_pwm_freq;
    uint32_t i2c_speed;
    uint8_t i2c_address;

} brushless7_cfg_t;

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
void brushless7_cfg_setup ( brushless7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
BRUSHLESS7_RETVAL brushless7_init ( brushless7_t *ctx, brushless7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Brushless7 Click.
 */
void brushless7_default_cfg ( brushless7_t *ctx );

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
void brushless7_generic_write ( brushless7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void brushless7_generic_read ( brushless7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic function for setting SBY pin state
 *
 * @param ctx            Click object.
 * @param state          state of the pin
 */
void brushless7_set_sby_pin_state ( brushless7_t *ctx, uint8_t state );

/**
 * @brief Generic function for toggling DIR pin state
 *
 * @param ctx            Click object.
 */
void brushless7_toggle_dir_pin_state ( brushless7_t *ctx );

/**
 * @brief Generic function for getting INT pin state
 *
 * @param ctx Click object.
 * 
 * @return   State of the pin
 */
uint8_t brushless7_get_int_pin_state ( brushless7_t *ctx );

/**
 * @brief Function for setting start duty of device
 *
 * @param ctx            Click object.
 * @param duty_ptc       duty in percentage
 *
 * @return   One of two dev status.
 * 
 * @note duty_ptc should be in range 0% to 49.8%
 */
uint8_t brushless7_start_duty ( brushless7_t *ctx, float duty_ptc );

/**
 * @brief Function for setting stop duty of device
 *
 * @param ctx            Click object.
 * @param duty_ptc       duty in percentage
 *
 * @return   One of two dev status.
 * 
 * @note duty_ptc should be in range 0% to 49.6%
 */
uint8_t brushless7_stop_duty ( brushless7_t *ctx, float duty_ptc );

/**
 * @brief Function for changeing duty of device
 *
 * @param ctx            Click object.
 * @param duty_ptc       duty in percentage
 *
 * @return   One of two dev status.
 * 
 * @note duty_ptc should be in range 0.4% to 99.6%
 */
uint8_t brushless7_change_duty ( brushless7_t *ctx, float duty_ptc );

/**
 * @brief Function for setting max duty of device
 *
 * @param ctx            Click object.
 * @param duty_ptc       duty in percentage
 *
 * @return   One of two dev status.
 * 
 * @note duty_ptc should be in range 50.2% to 100%
 */
uint8_t brushless7_max_duty ( brushless7_t *ctx, float duty_ptc );

/**
 * @brief Function for setting start rpm parameter of device
 *
 * @param ctx            Click object.
 * @param rpm_val        value
 *
 * @return   One of two dev status.
 * 
 * @note value should be in range 0 to 4095
 */
uint8_t brushless7_start_rpm ( brushless7_t *ctx, uint16_t rpm_val );

/**
 * @brief Function for setting max rpm parameter of device
 *
 * @param ctx            Click object.
 * @param max_speed_rpm  library macro
 *
 * @return   One of two dev status.
 */
uint8_t brushless7_max_speed_rpm ( brushless7_t *ctx, uint8_t max_speed_rpm );

/**
 * @brief Function for setting rotation direction
 *
 * @param ctx            Click object.
 * @param direction_rot  library macro
 *
 * @return   One of two dev status.
 */
uint8_t brushless7_rotating_direction ( brushless7_t *ctx, uint8_t direction_rot );

/**
 * @brief Function for setting type of device control
 *
 * @param ctx            Click object.
 * @param ctrl_type      library macro
 *
 * @return   One of two dev status.
 */
uint8_t brushless7_control_mode_set ( brushless7_t *ctx, uint8_t ctrl_type );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void brushless7_set_duty_cycle ( brushless7_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void brushless7_pwm_stop ( brushless7_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void brushless7_pwm_start ( brushless7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BRUSHLESS7_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
