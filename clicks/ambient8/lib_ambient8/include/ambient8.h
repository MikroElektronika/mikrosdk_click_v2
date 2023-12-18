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
 * \brief This file contains API for Ambient 8 Click driver.
 *
 * \addtogroup ambient8 Ambient 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMBIENT8_H
#define AMBIENT8_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define AMBIENT8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT8_RETVAL  uint8_t

#define AMBIENT8_OK           0x00
#define AMBIENT8_INIT_ERROR   0xFF
/** \} */
/**
 * \defgroup device_address Device Address
 * \{
 */
#define AMBIENT8_DEVICE_ADDRESS                0x29
 /** \} */ // End group device_address 

/**
 * \defgroup register_address Register address
 * \{
 */
#define AMBIENT8_ALS_CONTROL                   0x80
#define AMBIENT8_ALS_MEASUREMENT_RATE          0x85
#define AMBIENT8_PART_ID                       0x86
#define AMBIENT8_MANUFACTURER_ID               0x87
#define AMBIENT8_ALS_DATA_CH1_0                0x88
#define AMBIENT8_ALS_DATA_CH1_1                0x89
#define AMBIENT8_ALS_DATA_CH0_0                0x8A
#define AMBIENT8_ALS_DATA_CH0_1                0x8B
#define AMBIENT8_ALS_STATUS                    0x8C
/** \} */ // End group register_address 

/**
 * \defgroup als_control_register Als control register
 * \{
 */
#define AMBIENT8_ALS_GAIN_1X                   0x00
#define AMBIENT8_ALS_GAIN_2X                   0x04
#define AMBIENT8_ALS_GAIN_4X                   0x08
#define AMBIENT8_ALS_GAIN_8X                   0x0C
#define AMBIENT8_ALS_GAIN_48X                  0x18
#define AMBIENT8_ALS_GAIN_96X                  0x1C
#define AMBIENT8_SW_RESET                      0x02
#define AMBIENT8_ALS_MODE_STANDBY              0x00
#define AMBIENT8_ALS_MODE_ACTIVE               0x01
/** \} */ // End group als_control_register 

/**
 * \defgroup als_measurement_rate_register Als measurement rate register
 * \{
 */
#define AMBIENT8_ALS_INTEGRATION_TIME_100ms    0x00
#define AMBIENT8_ALS_INTEGRATION_TIME_50ms     0x08
#define AMBIENT8_ALS_INTEGRATION_TIME_200ms    0x10
#define AMBIENT8_ALS_INTEGRATION_TIME_400ms    0x18
#define AMBIENT8_ALS_INTEGRATION_TIME_150ms    0x20
#define AMBIENT8_ALS_INTEGRATION_TIME_250ms    0x28
#define AMBIENT8_ALS_INTEGRATION_TIME_300ms    0x30
#define AMBIENT8_ALS_INTEGRATION_TIME_350ms    0x38
#define AMBIENT8_ALS_MEASUREMENT_RATE_50       0x00
#define AMBIENT8_ALS_MEASUREMENT_RATE_100      0x01
#define AMBIENT8_ALS_MEASUREMENT_RATE_200      0x02
#define AMBIENT8_ALS_MEASUREMENT_RATE_500      0x03
#define AMBIENT8_ALS_MEASUREMENT_RATE_1000     0x04
#define AMBIENT8_ALS_MEASUREMENT_RATE_2000     0x07
/** \} */ // End group als_measurement_rate_register
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
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} ambient8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} ambient8_cfg_t;

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
 * @description This function initializes click configuration structure to init
 * state.
 * @note All used pins will be set to unconnected state.
 */
void ambient8_cfg_setup ( ambient8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals 
 * used for this click.
 */
AMBIENT8_RETVAL ambient8_init ( ambient8_t *ctx, ambient8_cfg_t *cfg );

/**
 * @brief Writing to device registers.
 *
 * @param ctx          Click object.
 * @param write_buf    Buffer for bytes to be written.
 * @param n_bytes      Number of bytes to be written.
 *
 * @description This function writes bytes to n_bytes - registers in device memory
 */
void ambient8_set_register ( ambient8_t* ctx, uint8_t* write_buf, uint8_t n_bytes );

/**
 * @brief Reading register value(s).
 * 
 * @param ctx          Click object.
 * @param reg_addr     Register address.
 * @param data_buf     Output data buf
 * @param n_bytes      Number of the bytes to be read
 *
 * @description This function reads n_bytes - registers(bytes) from device memory
 */
void ambient8_get_register ( ambient8_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint8_t n_bytes );

/**
 * @brief Setting constants for lux level calculation
 *
 * @param ctx          Click object.
 *
 * @description  This function sets constants (gain and integration time) for
 * lux level calculation.
 */
void ambient8_set_constants ( ambient8_t* ctx );

/**
 * @brief  Reading ALS data
 *
 * @param ctx             Click object.
 * @param als_data_ch1    ALS channel 1 data.
 * @param als_data_ch0    ALS channel 0 data.
 *
 * @returns Error         0 - OK, 1-Error.
 *
 * @description  This function checks for new data by polling ALS status register.
 */
AMBIENT8_RETVAL ambient8_get_als_data ( ambient8_t* ctx, uint16_t* als_data_ch1,
                                        uint16_t* als_data_ch0);

/**
 * @brief  Calculating lux level
 *
 * @param ctx             Click object.
 * @param lux_level       Lux level calculated using window factor , IR factor
 *                        and ALS channel 0 and channel 1 data
 * @param window_factor   Window factor needs to be derived if window
 *                        is being used.
 * @param IR_facotr       IR factor needs to be derived if window is being used.
 *
 * @returns Error         0 - OK, 1-Error.
 *
 * @description   This function reads and data and performs lux level calculation
 * This function returns 0 and stores lux level value into luxLevel_ if new data
 * is ready and if new data is valid.
 */
AMBIENT8_RETVAL ambient8_get_lux_level ( ambient8_t* ctx, float* lux_level,
                                         float window_factor, float IR_factor );

#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
