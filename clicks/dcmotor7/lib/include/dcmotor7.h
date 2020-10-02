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
 * \brief This file contains API for DC MOTOR 7 Click driver.
 *
 * \addtogroup dcmotor7 DC MOTOR 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR7_H
#define DCMOTOR7_H

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
#define DCMOTOR7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pwma = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pwmb = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR7_RETVAL  uint8_t

#define DCMOTOR7_OK           0x00
#define DCMOTOR7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup command  Command
 * \{
 */
#define DCMOTOR7_CMD_INPUT_PORT           0x00 // def xxxx xxxx
#define DCMOTOR7_CMD_OUTPUT_PORT          0x01 // def 1111 1111
#define DCMOTOR7_CMD_POLARITY_INVERSION   0x02 // def 0000 0000
#define DCMOTOR7_CMD_CONFIGURATION        0x03 // def 1111 1111
/** \} */
 
/**
 * \defgroup port  Port
 * \{
 */
#define DCMOTOR7_PORT_0   0x01
#define DCMOTOR7_PORT_1   0x02
#define DCMOTOR7_PORT_2   0x04
#define DCMOTOR7_PORT_3   0x08
#define DCMOTOR7_PORT_4   0x10
#define DCMOTOR7_PORT_5   0x20
#define DCMOTOR7_PORT_6   0x40
#define DCMOTOR7_PORT_7   0x80
/** \} */
 
/**
 * \defgroup tblk_noise_rejection_time   TBLK noise rejection time
 * \{
 */
#define DCMOTOR7_TBLK_FOSCM_X4_CLK    0x00
#define DCMOTOR7_TBLK_FOSCM_X6_CLK    0x01
/** \} */
 
/**
 * \defgroup h-bridge_operation_mode   H-bridge operation mode
 * \{
 */
#define DCMOTOR7_HBMODE_SMALL_MODE   0x00
#define DCMOTOR7_HBMODE_LARGE_MODE   0x01
/** \} */
 
/**
 * \defgroup motor  Motor
 * \{
 */
#define DCMOTOR7_MOTOR_A  0x01
#define DCMOTOR7_MOTOR_B  0x02
/** \} */
 
/**
 * \defgroup slave_address  Slave Address
 * \{
 */
#define DCMOTOR7_SLAVE_ADDRESS_0_0   0x70
#define DCMOTOR7_SLAVE_ADDRESS_0_1   0x71
#define DCMOTOR7_SLAVE_ADDRESS_1_0   0x72
#define DCMOTOR7_SLAVE_ADDRESS_1_1   0x73
/** \} */
 
/**
 * \defgroup configuration  Configuration
 * \{
 */
#define DCMOTOR7_ENABLE_ALL_OUTPUT_PORT    0x00
#define DCMOTOR7_DISABLE_ALL_OUTPUT_PORT   0xFF
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

    digital_out_t pwma;
    digital_out_t pwmb;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} dcmotor7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t pwma;
    pin_name_t pwmb;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} dcmotor7_cfg_t;

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
void dcmotor7_cfg_setup ( dcmotor7_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR7_RETVAL dcmotor7_init ( dcmotor7_t *ctx, dcmotor7_cfg_t *cfg );

/**
 * @brief Default Confuguration.
 *
 * @param ctx    Click object.
 * @note
 * <pre>
 *  Set: DCMOTOR7_CMD_CONFIGURATION
          - DCMOTOR7_ENABLE_ALL_OUTPUT_PORT
    Set: DCMOTOR7_PORT_0
          - DCMOTOR7_TBLK_FOSCM_X6_CLK
    Set: DCMOTOR7_PORT_5
          - DCMOTOR7_HBMODE_SMALL_MODE
 * </pre>
 * 
 * @description This function is default configuration for this click.
 */
void dcmotor7_default_cfg ( dcmotor7_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param tmp     Data buf to be written
 *
 * @description This function writes data to the desired register.
 */
void dcmotor7_generic_write ( dcmotor7_t *ctx, uint8_t reg, uint8_t tmp );

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
void dcmotor7_generic_read ( dcmotor7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for set port
 *
 * @param ctx     Click object.
 * @param port    Port to be set up
 * @param value   Value to which the selected port is being set
 */
void dcmotor7_set_port ( dcmotor7_t *ctx, uint8_t port, uint8_t value );

/**
 * @brief Functions for set Motor
 *
 * @param ctx     Click object.
 * @param motor   Motor (A or B)
 * @param in1     Motor Ach or Bch IN1 signal
 * @param in2     Motor Ach or Bch IN2 signal
 */
void dcmotor7_set_motor ( dcmotor7_t *ctx, uint8_t motor, uint8_t in1, uint8_t in2 );

/**
 * @brief Functions for set Motor Ach and Bch Digital tBLK
 *
 * @param ctx    Click object.
 * @param tbblk   TBLK noise rejection time (Digital tBLK = fOSCM � 4 clk or fOSCM � 6 clk)
 */
void dcmotor7_set_tblkab ( dcmotor7_t *ctx, uint8_t tblk );

/**
 * @brief Functions for set H-Bridge operation mode
 *
 * @param ctx    Click object.
 * @param mode   Mode (Small mode or Large mode)
 */
void dcmotor7_set_hb_mode ( dcmotor7_t *ctx, uint8_t mode );

/**
 * @brief Motor stop function
 *
 * @param ctx     Click object.
 * @param motor   Motor (A or B)
 */
void dcmotor7_motor_stop ( dcmotor7_t *ctx, uint8_t motor );

/**
 * @brief Function for setting the motor in stand mode
 *
 * @param ctx     Click object.
 * @param motor   Motor (A or B)
 */
void dcmotor7_go_to_stand_by_mode ( dcmotor7_t *ctx, uint8_t motor );

/**
 * @brief Function for set PWM value for motor A
 *
 * @param ctx     Click object.
 * @param state   PWM state
 */
void dcmotor7_set_pwm_motor_a ( dcmotor7_t *ctx, uint8_t state );

/**
 * @brief Function for set PWM value for motor B
 *
 * @param ctx     Click object.v
 * @param state   PWM state
 */
void dcmotor7_set_pwm_motor_b ( dcmotor7_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
