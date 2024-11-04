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
 * \brief This file contains API for Cap Wheel 2 Click driver.
 *
 * \addtogroup capwheel2 Cap Wheel 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPWHEEL2_H
#define CAPWHEEL2_H

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
#define CAPWHEEL2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPWHEEL2_RETVAL  uint8_t

#define CAPWHEEL2_OK           0x00
#define CAPWHEEL2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup I2C default slave address 
 * \{
 */
#define CAPWHEEL2_DEVICE_ADDRESS             0x44
/** \} */

/**
 * \defgroup Cap Wheel 2 ( IQS263 ) registers 
 * \{
 */
#define CAPWHEEL2_DEVICE_INFO                0x00
#define CAPWHEEL2_SYS_FLAGS                  0x01
#define CAPWHEEL2_COORDINATES                0x02
#define CAPWHEEL2_TOUCH_BYTES                0x03
#define CAPWHEEL2_COUNTS                     0x04
#define CAPWHEEL2_LTA                        0x05
#define CAPWHEEL2_DELTAS                     0x06
#define CAPWHEEL2_MULTIPLIERS                0x07
#define CAPWHEEL2_COMPENSATION               0x08
#define CAPWHEEL2_PROX_SETTINGS              0x09
#define CAPWHEEL2_THRESHOLDS                 0x0A
#define CAPWHEEL2_TIMINGS_AND_TARGETS        0x0B
#define CAPWHEEL2_GESTURE_TIMERS             0x0C
#define CAPWHEEL2_ACTIVE_CHANNELS            0x0D
/** \} */

/**
 * \defgroup Gesture masks
 * \{
 */
#define CAPWHEEL2_TAP_MASK                   0x20
#define CAPWHEEL2_TOUCH_MASK                 0x02
#define CAPWHEEL2_PROX_MASK                  0x01
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

    digital_in_t rdy;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} capwheel2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rdy;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} capwheel2_cfg_t;

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
void capwheel2_cfg_setup ( capwheel2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param capwheel2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
CAPWHEEL2_RETVAL capwheel2_init ( capwheel2_t *ctx, capwheel2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @returns    Data buffer setted to default values.
 *
 * @description This function executes default configuration for CapWheel2 Click.
 */
uint8_t capwheel2_default_cfg ( capwheel2_t *ctx );

/**
 * @brief Write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void capwheel2_i2c_write_no_wait ( capwheel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void capwheel2_i2c_read_no_wait ( capwheel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Getingg state of INT pin.
 *
 * @param ctx  Click object.
 * @returns    1 for HIGH pin state, or 0 for LOW pin state.
 *
 * @description This function gets state of INT pin.
 */
uint8_t capwheel2_int_get ( capwheel2_t *ctx );

/**
 * @brief Waiting for RDY (INT) pin.
 *
 * @param ctx  Click object.
 * @returns    0 if RDY pin went from HIGH to LOW state, or 1 if it did not go from HIGH to LOW state within 4,294,967,295(2^32 - 1) iterations.
 *
 * @description This function waits for RDY pin to transition from HIGH to LOW state.
 */
uint8_t capwheel2_wait_for_rdy ( capwheel2_t *ctx );

/**
 * @brief Read wait function.
 *
 * 
 * @param ctx                       Click object.
 * @param register_address          Register address.
 * @param read_buffer               Buffer to store register byte(s).
 * @param len                       Number of the bytes to be read.
 * @returns                         0 if no error occured during setup, or 1 if error occured.
 *
 * @description This function reads data from the desired register.
 */
uint8_t capwheel2_i2c_read_wait ( capwheel2_t *ctx, uint8_t register_address, uint8_t * read_buffer, uint8_t n_bytes );

/**
 * @brief Write wait function.
 *
 * @param ctx                       Click object.
 * @param register_address          Register address.
 * @param register_values           Buffer to store register value(s).
 * @param len                       Number of the bytes in data buf.
 * @returns                         0 if no error occured during setup, or 1 if error occured.
 *
 * @description This function sets register content.
 * @note This function waits for RDY pin to go from HIGH to LOW in order to get register contents
 */
uint8_t capwheel2_i2c_write_wait ( capwheel2_t *ctx, uint8_t register_address, uint8_t * register_values, uint8_t n_bytes );


#ifdef __cplusplus
}
#endif
#endif  // _CAPWHEEL2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
