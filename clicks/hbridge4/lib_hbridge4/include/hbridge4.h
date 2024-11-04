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
 * \brief This file contains API for H-Bridge 4 Click driver.
 *
 * \addtogroup hbridge4 H-Bridge 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HBRIDGE4_H
#define HBRIDGE4_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define HBRIDGE4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in4 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.in3 = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HBRIDGE4_RETVAL  uint8_t

#define HBRIDGE4_OK           0x00
#define HBRIDGE4_INIT_ERROR   0xFF
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

    digital_out_t in1;
    digital_out_t in2;
    digital_out_t en;
    digital_out_t in4;
    digital_out_t in3;

} hbridge4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t in1;
    pin_name_t in2;
    pin_name_t en;
    pin_name_t in4;
    pin_name_t in3;

} hbridge4_cfg_t;

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
void hbridge4_cfg_setup ( hbridge4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param hbridge4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
HBRIDGE4_RETVAL hbridge4_init ( hbridge4_t *ctx, hbridge4_cfg_t *cfg );

/**
 * @brief Enable the device function
 *
 * @param ctx    Click object.
 * @param state  0 - Device disabled / 1 - Device enabled
 *
 * @description Function is used to enable or disable the device.
 */
void hbridge4_enable ( hbridge4_t *ctx, uint8_t state );

/**
 * @brief Set IN1 function
 *
 * @param ctx    Click object.
 * @param state  0 - IN1 pin cleared / 1 - IN1 pin set
 *
 * @description Function is used to set or clear IN1 pin.
 */
void hbridge4_set_in1 ( hbridge4_t *ctx, uint8_t state );

/**
 * @brief Set IN2 function
 *
 * @param ctx    Click object.
 * @param state  0 - IN2 pin cleared / 1 - IN2 pin set
 *
 * @description Function is used to set or clear IN2 pin.
 */
void hbridge4_set_in2 ( hbridge4_t *ctx, uint8_t state );

/**
 * @brief Set IN3 function
 *
 * @param ctx    Click object.
 * @param state  0 - IN3 pin cleared / 1 - IN3 pin set
 *
 * @description Function is used to set or clear IN3 pin.
 */
void hbridge4_set_in3 ( hbridge4_t *ctx, uint8_t state );

/**
 * @brief Set IN4 function
 *
 * @param ctx    Click object.
 * @param state  0 - IN4 pin cleared / 1 - IN4 pin set
 *
 * @description Function is used to set or clear IN4 pin.
 */
void hbridge4_set_in4 ( hbridge4_t *ctx, uint8_t state );

/**
 * @brief Motor A standby function
 *
 * @description Function is used to put motor A into standby.
 */
void hbridge4_motor_a_standby ( hbridge4_t *ctx );

/**
 * @brief Motor A clockwise motion function
 *
 * @param ctx    Click object.
 *
 * @description Function is used to put motor A into clockwise motion.
 */
void hbridge4_motor_acw ( hbridge4_t *ctx );

/**
 * @brief Motor A counter-clockwise motion function
 *
 * @param ctx    Click object.
 *
 * @description Function is used to put motor A into counter-clockwise motion.
 */
void hbridge4_motor_accw ( hbridge4_t *ctx );

/**
 * @brief Motor A Brake function
 *
 * @param ctx    Click object.
 *
 * @description Function is used to brake motor A to a halt.
 */
void hbridge4_motor_a_brake ( hbridge4_t *ctx );

/**
 * @brief Motor B standby function
 *
 * @param ctx    Click object.
 *
 * @description Function is used to put motor B into standby.
 */
void hbridge4_motor_b_standby ( hbridge4_t *ctx );

/**
 * @brief Motor B clockwise motion function
 *
 * @param ctx    Click object.
 *
 * @description Function is used to put motor B into clockwise motion.
 */
void hbridge4_motor_bcw ( hbridge4_t *ctx );

/**
 * @brief Motor B counter-clockwise motion function
 *
 * @param ctx    Click object.
 *
 * @description Function is used to put motor B into counter-clockwise motion.
 */
void hbridge4_motor_bccw ( hbridge4_t *ctx );

/**
 * @brief Motor B Brake function
 *
 * @param ctx    Click object.
 *
 * @description Function is used to brake motor B to a halt.
 */
void hbridge4_motor_b_brake ( hbridge4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HBRIDGE4_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
