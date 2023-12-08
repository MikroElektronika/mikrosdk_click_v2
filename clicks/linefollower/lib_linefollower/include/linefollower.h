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
 * \brief This file contains API for Line Follower Click driver.
 *
 * \addtogroup linefollower Line Follower Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define LINEFOLLOWER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.u2= MIKROBUS( mikrobus, MIKROBUS_AN );       \
  cfg.u1= MIKROBUS( mikrobus, MIKROBUS_RST );      \
  cfg.u5= MIKROBUS( mikrobus, MIKROBUS_PWM );      \
  cfg.u4= MIKROBUS( mikrobus, MIKROBUS_RX );       \
  cfg.u3= MIKROBUS( mikrobus, MIKROBUS_TX );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LINEFOLLOWER_RETVAL  uint8_t

#define LINEFOLLOWER_OK           0x00
#define LINEFOLLOWER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup dir_data Direction value
 * \{
 */
#define LINEFOLLOWER_DATA_DIR_START       0x00
#define LINEFOLLOWER_DATA_DIR_1           0x01
#define LINEFOLLOWER_DATA_DIR_2           0x02
#define LINEFOLLOWER_DATA_DIR_3           0x03
#define LINEFOLLOWER_DATA_DIR_4           0x04
#define LINEFOLLOWER_DATA_DIR_6           0x06
#define LINEFOLLOWER_DATA_DIR_7           0x07
#define LINEFOLLOWER_DATA_DIR_8           0x08
#define LINEFOLLOWER_DATA_DIR_12          0x0C
#define LINEFOLLOWER_DATA_DIR_16          0x10
#define LINEFOLLOWER_DATA_DIR_24          0x18
#define LINEFOLLOWER_DATA_DIR_28          0x1C
#define LINEFOLLOWER_DATA_DIR_31          0x1F
/** \} */

/**
 * \defgroup dir_b_m Direction bit mask
 * \{
 */
#define LINEFOLLOWER_BIT_0                 0x01
#define LINEFOLLOWER_BIT_1                 0x02
#define LINEFOLLOWER_BIT_2                 0x04
#define LINEFOLLOWER_BIT_3                 0x08
#define LINEFOLLOWER_BIT_4                 0x10
/** \} */

/**
 * \defgroup dir_pos Direction
 * \{
 */
#define LINEFOLLOWER_DIR_STRAIGHT         0x00
#define LINEFOLLOWER_DIR_LEFT             0x01
#define LINEFOLLOWER_DIR_RIGHT            0x02
#define LINEFOLLOWER_DIR_SHARP_LEFT       0x03
#define LINEFOLLOWER_DIR_SHARP_RIGHT      0x04
#define LINEFOLLOWER_DIR_TRACKING_LOST    0x05
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

    digital_in_t u1;
    digital_in_t u2;
    digital_in_t u3;
    digital_in_t u4;
    digital_in_t u5;

} linefollower_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t u1;
    pin_name_t u2;
    pin_name_t u3;
    pin_name_t u4;
    pin_name_t u5;

} linefollower_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */
typedef struct
{
    uint8_t u1;
    uint8_t u2;
    uint8_t u3;
    uint8_t u4;
    uint8_t u5;

} linefollower_direction_t;

/** \} */ // End variable group
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
void linefollower_cfg_setup ( linefollower_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param linefollower Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LINEFOLLOWER_RETVAL linefollower_init ( linefollower_t *ctx, linefollower_cfg_t *cfg );

/**
 * @brief Get status of U1 pin function
 *
 * @param ctx  Click object.
 * 
 * @return Detect line black-white color::
 * - 0 : no black;
 * - 1 : black;
 *
 * This function get state of the RST pin
 * U1: QRE1113 Minature Reective Object Sensor.
 */
uint8_t linefollower_get_u1 ( linefollower_t *ctx );

/**
 * @brief Get status of U2 pin function
 *
 * @param ctx  Click object.
 * 
 * @return Detect line black-white color:
 * - 0 : no black;
 * - 1 : black;
 *
 * This function get state of the RST pin
 * U2: QRE1113 Minature Reective Object Sensor.
 */
uint8_t linefollower_get_u2 ( linefollower_t *ctx );

/**
 * @brief Get status of U3 pin function
 *
 * @param ctx  Click object.
 * 
 * @return Detect line black-white color:
 * - 0 : no black;
 * - 1 : black;
 *
 * This function get state of the RST pin
 * U3: QRE1113 Minature Reective Object Sensor.
 */
uint8_t linefollower_get_u3 ( linefollower_t *ctx );

/**
 * @brief Get status of U4 pin function
 *
 * @param ctx  Click object.
 * 
 * @return Detect line black-white color:
 * - 0 : no black;
 * - 1 : black;
 *
 * This function get state of the RST pin
 * U4: QRE1113 Minature Reective Object Sensor.
 */
uint8_t linefollower_get_u4 ( linefollower_t *ctx );

/**
 * @brief Get status of U5 pin function
 *
 * @param ctx  Click object.
 * 
 * @return Detect line black-white color:
 * - 0 : no black;
 * - 1 : black;
 *
 * This function get state of the RST pin
 * U5: QRE1113 Minature Reective Object Sensor.
 */
uint8_t linefollower_get_u5 ( linefollower_t *ctx );

/**
 * @brief Get status of all pin function
 *
 * @param ctx  Click object.
 * 
 * @param  data_track Data track structure
 *
 * This function get status of all pin
 * of the QRE1113 Minature Reective Object Sensor.
 */
void linefollower_data_track ( linefollower_t *ctx, linefollower_direction_t *data_track );

/**
 * @brief Get direction data function
 *
 * @param ctx  Click object.
 * 
 * @return direction
 * <pre>
 * - 0 [ LINEFOLLOWER_DIR_STRAIGHT ] : Straight movement;
 * </pre>
 * <pre>
 * - 1 [ LINEFOLLOWER_DIR_LEFT ] : Left movement;
 * </pre>
 * <pre>
 * - 2 [ LINEFOLLOWER_DIR_RIGHT ] : Right movement;
 * </pre>
 * <pre>
 * - 3 [ LINEFOLLOWER_DIR_SHARP_LEFT ] : Sharp left movement;
 * </pre>
 * <pre>
 * - 4 [ LINEFOLLOWER_DIR_SHARP_RIGHT ] : Sharp right movement;
 * </pre>
 * <pre>
 * - 5 [ LINEFOLLOWER_DIR_TRACKING_LOST ] : Tracking lost;
 * </pre>
 *
 * This function direction movement data
 * of the QRE1113 Minature Reective Object Sensor.
 */
uint8_t linefollower_get_direction ( linefollower_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _LINEFOLLOWER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
