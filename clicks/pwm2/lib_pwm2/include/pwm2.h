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
 * \brief This file contains API for PWM 2 Click driver.
 *
 * \addtogroup pwm2 PWM 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PWM2_H
#define PWM2_H

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
#include "drv_pwm.h"
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
#define PWM2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
  cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
  cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
  cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PWM2_RETVAL  uint8_t

#define PWM2_OK           0x00
#define PWM2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define PWM2_DEF_FREQ     20000
/** \} */

/**
 * \defgroup pwm_clock PWM Clock
 * \{
 */
#define PWM2_CLOCK_25_MHZ  25000000
#define PWM2_CLOCK_15_MHZ  15000000
#define PWM2_CLOCK_5_MHZ   5000000
/** \} */

/**
 * \defgroup precent_duty Precent duty
 * \{
 */
#define PWM2_100_PERCENT_DUTY   4095
#define PWM2_75_PERCENT_DUTY    3072
#define PWM2_50_PERCENT_DUTY    2048
#define PWM2_25_PERCENT_DUTY    1024
/** \} */

/**
 * \defgroup correction Correction
 * \{
 */
#define PWM2_NO_CORRECTION  0
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

    digital_out_t  cs;

    // Input pins 

    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;
    pwm_t pwm;

    // ctx variable 

    uint32_t pwm_freq;

} pwm2_t;

typedef struct 
{
    uint16_t width;
    uint8_t correction;
    
} pwm_channel_t;

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
    pin_name_t pwm;
    
    // Additional gpio pins 


    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;
    uint32_t dev_pwm_freq;

} pwm2_cfg_t;

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
void pwm2_cfg_setup ( pwm2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PWM2_RETVAL pwm2_init ( pwm2_t *ctx, pwm2_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void pwm2_set_duty_cycle ( pwm2_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx          Click object.
 *
 * @description This function stops PWM module.
 */
void pwm2_pwm_stop ( pwm2_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx          Click object.
 *
 * @description This function starts PWM module.
 */
void pwm2_pwm_start ( pwm2_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void pwm2_generic_transfer ( pwm2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Reset pulse.
 *
 * @param ctx          Click object.
 *
 * @description This function reset the click.
 */
 static void send_reset_pulse ( pwm2_t *ctx );

/**
 * @brief Set pulse.
 *
 * @param ctx          Click object.
 *
 * @description This function set the click.
 */
static void send_pulse ( pwm2_t *ctx );

/**
 * @brief Send frame buffer.
 *
 * @param ctx          Click object.
 *
 * @description This function send the frame to the buffer.
 */
static void send_frame_buffer ( pwm2_t *ctx );

/**
 * @brief Asynchronous update frame.
 *
 * @param ctx          Click object.
 *
 * @description This function send the asynchronous update frame.
 */
static void send_async_update_frame ( pwm2_t *ctx );

/**
 * @brief Correction frame.
 *
 * @param ctx          Click object.
 *
 * @description This function send the correction frame.
 */
static void send_correction_frame ( pwm2_t *ctx );

/**
 * @brief Enable frame.
 *
 * @param ctx          Click object.
 *
 * @description This function send enable frame to the output.
 */
static void send_output_enable_frame ( pwm2_t *ctx );

/**
 * @brief Toggle frame.
 *
 * @param ctx          Click object.
 *
 * @description This function send correction toggle frame.
 */
static void send_correction_toggle_frame ( pwm2_t *ctx );

/**
 * @brief Set parameters.
 *
 * @param ctx          Click object.
 *
 * @description This function set the all needed click parameters.
 */
static void set_parameters ( pwm2_t *ctx );

/**
 * @brief Toggle phase shift.
 *
 * @param ctx          Click object.
 *
 * @description This function set toggle phase shift.
 */
void pwm2_toggle_phase_shift ( pwm2_t *ctx );

/**
 * @brief Set channel function.
 *
 * @param ctx          Click object.
 * @param n_channel    Channel select.
 * @param width        Channel width.
 * @param correction   Correction.
 *
 * @description This function choose one or more channel of 48.
 */
uint8_t pwm2_set_channel ( pwm2_t *ctx, uint8_t n_channel, uint16_t width, uint8_t correction );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx          Click object.
 *
 * @description This function executes default configuration for PWM 2 Click.
 */
void pwm2_default_cfg ( pwm2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PWM2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
