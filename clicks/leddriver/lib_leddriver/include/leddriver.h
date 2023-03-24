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
 * \brief This file contains API for LED DRIVER Click driver.
 *
 * \addtogroup leddriver LED DRIVER Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
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
#define LEDDRIVER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LEDDRIVER_RETVAL  uint8_t

#define LEDDRIVER_OK           0x00
#define LEDDRIVER_INIT_ERROR   0xFF
#define LEDDRIVER_FREQ_ERROR   0xFE
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define LEDDRIVER_DEF_FREQ     10000
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
    pwm_t pwm;

    uint32_t pwm_freq;

} leddriver_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    pin_name_t pwm;

    uint32_t dev_pwm_freq;

} leddriver_cfg_t;

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
 * @param cfg Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void leddriver_cfg_setup ( leddriver_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * @return 0x00 - OK, 0xFF - Init error, 0xFE - Wrong frequency.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LEDDRIVER_RETVAL leddriver_init ( leddriver_t *ctx, leddriver_cfg_t *cfg );

/**
 * @brief Get Max PWM Duty Cycle function.
 * @param ctx Click object.
 * @return Maximal PWM Duty Cycle.
 *
 * @description This function returns a maximal pwm duty cycle depending on the selected frequency.
 */
uint16_t leddriver_get_pwm_max_duty ( leddriver_t *ctx );

/**
 * @brief Generic sets PWM duty cycle.
 * @param ctx Click object.
 * @param duty_cycle Duty cycle.
 * @return See #err_t type of data.
 *
 * @description This function sets the PWM duty cycle.
 */
err_t leddriver_set_duty_cycle ( leddriver_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 * @param ctx Click object.
 * @return See #err_t type of data.
 *
 * @description This function stops PWM module.
 */
err_t leddriver_pwm_stop ( leddriver_t *ctx );

/**
 * @brief Start PWM module.
 * @param ctx Click object.
 * @return See #err_t type of data.
 *
 * @description This function starts PWM module.
 */
err_t leddriver_pwm_start ( leddriver_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LEDDRIVER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
