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
 * \brief This file contains API for Opto Encoder 3 Click driver.
 *
 * \addtogroup optoencoder3 Opto Encoder 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OPTOENCODER3_H
#define OPTOENCODER3_H

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
#define OPTOENCODER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.o1= MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.o2= MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.o4= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.o3= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error code
 * \{
 */
#define OPTOENCODER3_RETVAL  uint8_t

#define OPTOENCODER3_OK           0x00
#define OPTOENCODER3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup encoder_state Encoder state
 * \{
 */
#define OPTOENCODER3_ENABLE             0
#define OPTOENCODER3_DISABLE            1
/** \} */

/**
 * \defgroup pin_state Pin state
 * \{
 */
#define OPTOENCODER3_PIN_ACTIVE         0
#define OPTOENCODER3_PIN_NOT_ACTIVE     1
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

    digital_out_t en;

    // Input pins 

    digital_in_t o1;
    digital_in_t o2;
    digital_in_t o4;
    digital_in_t o3;

    uint8_t dev_cnt;
    int8_t  dev_swipe_cnt;
    uint8_t dev_swiping_dir;
    uint8_t dev_stage;

} optoencoder3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t o1;
    pin_name_t o2;
    pin_name_t en;
    pin_name_t o4;
    pin_name_t o3;

} optoencoder3_cfg_t;

/**
 * @brief Click pins state.
 */
typedef struct
{
  uint8_t pin_o1;
  uint8_t pin_o2;
  uint8_t pin_o3;
  uint8_t pin_o4;
  
}optoencoder3_pins_t;

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
void optoencoder3_cfg_setup ( optoencoder3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param optoencoder3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OPTOENCODER3_RETVAL optoencoder3_init ( optoencoder3_t *ctx, optoencoder3_cfg_t *cfg );

/**
 * @brief Sets state of click
 *
 * @param ctx  Click object.
 * 
 * @param active   State to be set
 */
void optoencoder3_enabler ( optoencoder3_t *ctx, uint8_t active );

/**
 * @brief Functions for reading state of pin o1
 *
 * @param ctx  Click object.
 * 
 * @return 8-bit data that is read from the pin.
 */
uint8_t optoencoder3_read_pin_o1 ( optoencoder3_t *ctx );

/**
 * @brief Functions for reading state of pin o2
 *
 * @param ctx  Click object.
 * 
 * @return 8-bit data that is read from the pin.
 */
uint8_t optoencoder3_read_pin_o2 ( optoencoder3_t *ctx );

/**
 * @brief Functions for reading state of pin o3
 *
 * @param ctx  Click object.
 * 
 * @return 8-bit data that is read from the pin.
 */
uint8_t optoencoder3_read_pin_o3 ( optoencoder3_t *ctx );

/**
 * @brief Functions for reading state of pin o4
 *
 * @param ctx  Click object.
 * 
 * @return 8-bit data that is read from the pin.
 */
uint8_t optoencoder3_read_pin_o4 ( optoencoder3_t *ctx );

/**
 * @brief Functions for reading number of swipes
 *
 * @param ctx  Click object.
 * 
 * @return 8-bit data of swipe number.
 */
uint8_t optoencoder3_cnt ( optoencoder3_t *ctx );

/**
 * @brief Functions for reading number of swipe directions
 *
 * @param ctx  Click object.
 * 
 * @note: 
 * <pre>
 *     This function adds 1 to counter if it detects swipe from one direction or deducts 1
 *     if it detects swipe from other direction
 * </pre>
 * @return 8-bit data of counter number.
 */
int8_t optoencoder3_dir_cnt ( optoencoder3_t *ctx );

/**
 * @brief Functions for reseting counters
 * 
 * @param ctx  Click object.
 */
void optoencoder3_reset_counters ( optoencoder3_t *ctx );

/**
 * @brief Sets state of all pins
 * 
 * @param ctx  Click object.
 *
 * @param *pins   Pointer on struct of all pins that is being set
 */
void optoencoder3_read_all_pins ( optoencoder3_t *ctx, optoencoder3_pins_t *pins );


#ifdef __cplusplus
}
#endif
#endif  // _OPTOENCODER3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
