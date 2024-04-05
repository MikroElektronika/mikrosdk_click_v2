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
 * \brief This file contains API for STSPIN233 Click driver.
 *
 * \addtogroup stspin233 STSPIN233 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef STSPIN233_H
#define STSPIN233_H

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
#include "drv_uart.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */  


/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define STSPIN233_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define STSPIN233_RETVAL  uint8_t

#define STSPIN233_OK           0x00
#define STSPIN233_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup command  Command
 * \{
 */
#define STSPIN233_CMD_START_MOTOR  "STARTM"
#define STSPIN233_CMD_STOP_MOTOR   "STOPMT"
#define STSPIN233_CMD_DIR_MOTOR    "DIRECT"
#define STSPIN233_CMD_SET_SPEED    "SETSPD"
#define STSPIN233_CMD_GET_SPEED    "GETSPD"
#define STSPIN233_CMD_STATUS       "STATUS"
#define STSPIN233_CMD_HELP         "HELP"
#define STSPIN233_CMD_SET_PWM      "INIREF"
#define STSPIN233_CMD_COM_DELAY    "COMDEL"
#define STSPIN233_CMD_MOTOR_POLE   "POLESP"
#define STSPIN233_CMD_KP_PRM       "KP-PRM"
#define STSPIN233_CMD_KI_PRM       "KI-PRM"
/** \} */
 
/**
 * \defgroup dir  Dir
 * \{
 */
#define STSPIN233_CW_DIR   "1"
#define STSPIN233_CCW_DIR  "0"
/** \} */
 
/**
 * \defgroup pwm_duty_cycle  PWM Duty Cycle
 * \{
 */
#define STSPIN233_START_PWM_DUTY_10p    "409"
#define STSPIN233_START_PWM_DUTY_20p    "819"
#define STSPIN233_START_PWM_DUTY_DEF    "819"
#define STSPIN233_START_PWM_DUTY_30p    "1229"
#define STSPIN233_START_PWM_DUTY_40p    "1638"
#define STSPIN233_START_PWM_DUTY_50p    "2048"
#define STSPIN233_START_PWM_DUTY_60p    "2458"
#define STSPIN233_START_PWM_DUTY_70p    "2867"
#define STSPIN233_START_PWM_DUTY_80p    "3277"
#define STSPIN233_START_PWM_DUTY_90p    "3687"
#define STSPIN233_START_PWM_DUTY_100p   "4095"
/** \} */
 
/**
 * \defgroup communication_delay  Communication delay
 * \{
 */
#define STSPIN233_COMM_DELAY_7ms  "7"
#define STSPIN233_COMM_DELAY_DEF  "7"
/** \} */
 
/**
 * \defgroup motor_pole  Motor pole
 * \{
 */
#define  STSPIN233_M_POLE_2     "2"
#define  STSPIN233_M_POLE_3     "3"
#define  STSPIN233_M_POLE_4     "4"
#define  STSPIN233_M_POLE_5     "5"
#define  STSPIN233_M_POLE_6     "6"
#define  STSPIN233_M_POLE_DEF   "6"
#define  STSPIN233_M_POLE_7     "7"
#define  STSPIN233_M_POLE_8     "8"
/** \} */
 
/**
 * \defgroup def_value  Def value
 * \{
 */
#define  STSPIN233_KP_PRM_DEF  "500"
#define  STSPIN233_KI_PRM_DEF  "250"
/** \} */
 
/**
 * \defgroup motor_speed  Motor speed
 * \{
 */
#define  STSPIN233_SPEED_1000RPM   "1000"
#define  STSPIN233_SPEED_DEF       "1000"
#define  STSPIN233_SPEED_900RPM     "900"
#define  STSPIN233_SPEED_1100RPM   "1100"
#define  STSPIN233_SPEED_1200RPM   "1200"
#define  STSPIN233_SPEED_1300RPM   "1300"
#define  STSPIN233_SPEED_1400RPM   "1400"
#define  STSPIN233_SPEED_1500RPM   "1500"
#define  STSPIN233_SPEED_1600RPM   "1600"
#define  STSPIN233_SPEED_1700RPM   "1700"
#define  STSPIN233_SPEED_1800RPM   "1800"
#define  STSPIN233_SPEED_1900RPM   "1900"
#define  STSPIN233_SPEED_2000RPM   "2000"
#define  STSPIN233_SPEED_2100RPM   "2100"
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} stspin233_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits. 

} stspin233_cfg_t;

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
void stspin233_cfg_setup ( stspin233_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param stspin233 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
STSPIN233_RETVAL stspin233_init ( stspin233_t *ctx, stspin233_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for STSPIN233 click.
 */
void stspin233_default_cfg ( stspin233_t *ctx );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void stspin233_generic_write ( stspin233_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t stspin233_generic_read ( stspin233_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Module wake-up (procedure)
 *
 * @param ctx          Click object.
 */
void stspin233_wakeup ( stspin233_t *ctx );

/**
 * @brief Send single command
 *
 * @param ctx          Click object.
 * @param tx_buf       Command buffer
 *
 * @Description This function sends one command buffer.
 * <pre>
 *     example: Start motor command.
 *              Command: STARTM
 * </pre>
 */
void stspin233_send_single_cmd ( stspin233_t *ctx, uint8_t *tx_buf );

/**
 * @brief Send double command
 *
 * @param ctx        Click object.
 * @param cmd_buf    Command buffer
 * @param arg_buf    Argument buffer
 *
 * @Description This function sends two command buffer.
 * <pre>
 *     example: Engine direction set command.
 *              Command: DIRECT
 *              Argument: 0 [CW] or 1 [CCW]
 * </pre>
 */
void stspin233_send_double_cmd ( stspin233_t *ctx, uint8_t *cmd_buf, uint8_t *arg_buf );

/**
 * @brief Set RST pin state
 *
 * @param ctx          Click object.
 * @param state        RST pin state
 */
void stspin233_set_reset_state ( stspin233_t *ctx, uint8_t state );

/**
 * @brief Get INT pin state
 *
 * @param ctx          Click object.
 *
 * @return INT pin state
 */
uint8_t stspin233_get_int_state ( stspin233_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _STSPIN233_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
