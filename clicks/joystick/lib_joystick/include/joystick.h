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
 * \brief This file contains API for Joystick Click driver.
 *
 * \addtogroup joystick Joystick Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef JOYSTCIK_H
#define JOYSTCIK_H

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
 * \defgroup Device I2C Address
 * \{
 */
#define JOYSTICK_I2C_ADDRESS_0                                     0x40
#define JOYSTICK_I2C_ADDRESS_1                                     0x41

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup Register Map
 * \{
 */
#define JOYSTICK_ID_CODE                                           0x0C
#define JOYSTICK_ID_VERSION                                        0x0D
#define JOYSTICK_SIL_REV                                           0x0E
#define JOYSTICK_CONTROL1                                          0x0F
#define JOYSTICK_CONTROL2                                          0x2E
#define JOYSTICK_X                                                 0x10
#define JOYSTICK_Y_RES_INT                                         0x11
#define JOYSTICK_XP                                                0x12
#define JOYSTICK_XN                                                0x13
#define JOYSTICK_YP                                                0x14
#define JOYSTICK_YN                                                0x15
#define JOYSTICK_AGC                                               0x2A
#define JOYSTICK_M_CTRL                                            0x2B
#define JOYSTICK_J_CTRL                                            0x2C
#define JOYSTICK_T_CTRL                                            0x2D
/** \} */

/**
 * \defgroup Write Command
 * \{
 */
#define JOYSTICK_CONTROL2_TEST_CMD                                 0x84
#define JOYSTICK_AGC_MAX_SENSITIVITY_CMD                           0x3F
#define JOYSTICK_T_CTRL_SCALING_90_8_CMD                           0x0A
#define JOYSTICK_T_CTRL_SCALING_100_CMD                            0x09
#define JOYSTICK_CONTROL1_RESET_CMD                                0x88
#define JOYSTICK_INVERT_SPINING_CMD                                0x86
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define JOYSTCIK_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );\
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );\
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );\
  cfg.tst = MIKROBUS( mikrobus, MIKROBUS_CS );
  
/** \} */
/**
 * \defgroup error_code Error Code
 * \{
 */
#define JOYSTCIK_RETVAL  uint8_t
#define JOYSTCIK_OK           0x00
#define JOYSTCIK_INIT_ERROR   0xFF
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
    digital_in_t tst;

    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} joystick_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t tst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} joystick_cfg_t;

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
void joystick_cfg_setup ( joystick_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param joystick Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
JOYSTCIK_RETVAL joystick_init ( joystick_t *ctx, joystick_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Joystick Click.
 */
void joystick_default_cfg ( joystick_t *ctx );

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
void joystick_generic_write ( joystick_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void joystick_generic_read ( joystick_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set default configuration function
 *
 * @param ctx          Click object.
 *
 * @description Function set default configuration,
 * set required Test bits of Control Register 2,
 * set maximum sensitivity,
 * set scaling Factor to 90.8% and
 * reset read value by writing configuration 1 register.
 */
void joystick_set_default_configuration ( joystick_t *ctx );

/**
 * @brief Check sensor ID code function
 *
 * @param ctx          Click object.
 *
 * @return sensor ID code
 * <pre>
 * - 1 : OK
 * - 0 : ERROR
 * </pre>
 *
 * @description Function read and return sensor ID code
 * from ID Code register.
 */
uint8_t joystick_check_id_code ( joystick_t *ctx );

/**
 * @brief Check sensor ID version function
 *
 * @param ctx          Click object.
 *
 * @return sensor ID version
 * <pre>
 * - 1 : OK
 * - 0 : ERROR
 * </pre>
 *
 * @description Function read and return sensor ID version
 * from ID Version register.
 */
uint8_t joystick_check_id_version ( joystick_t *ctx );

/**
 * @brief Set Low Power Mode function
 *
 * @param ctx  Click object.
 * @param timings  timings by setting the low power timebase
 *
 * @description Function set default configuration,
 * The measurements are triggered with an internal low power oscillator the user can select between 8 different timings by
 * setting the low power timebase.
 * <pre>
 * - 0 :  20 ms;
 * - 1 :  40 ms;
 * - 2 :  80 ms;
 * - 3 : 100 ms;
 * - 4 : 140 ms;
 * - 5 : 200 ms;
 * - 6 : 260 ms;
 * - 7 : 320 ms;
 * </pre>
 */
void joystick_set_low_power_mode ( joystick_t *ctx, uint8_t timings );

/**
 * @brief Set scaling factor function
 *
 * @param ctx          Click object.
 *
 * @param[in] scalingFactor                  scaling factor
 *
 * @description Function set scaling factor value of the XY coordinates
 * to fit to the 8-bit X and Y_res_int register (full dynamic range);
 * 
 * <pre>
 * - 31 :  31.3 %;
 * - 30 :  32.2 %;
 * - 29 :  33.4 %;
 * - 28 :  34.6 %;
 * - 27 :  35.7 %;
 * - 26 :  37.1 %;
 * - 25 :  38.5 %;
 * - 24 :  40.0 %;
 * - 23 :  41.6 %;
 * - 22 :  43.6 %;
 * - 21 :  45.5 %;
 * - 20 :  47.7 %;
 * - 19 :  50.0 %;
 * - 18 :  52.5 %;
 * - 17 :  55.5 %;
 * - 16 :  58.8 %;
 * - 15 :  62.5 %;
 * - 14 :  66.6 %;
 * - 13 :  71.5 %;
 * - 12 :  77.0 %;
 * - 11 :  83.4 %;
 * - 10 :  90.8 %;
 * -  9 : 100.0 %;
 * -  8 : 111.1 %;
 * -  7 : 125.0 %;
 * -  6 : 142.8 %;
 * -  5 : 166.6 %;
 * -  4 : 200.0 %;
 * -  3 : 250.0 %;
 * -  2 : 333.4 %;
 * -  1 : 500.0 %;
 * </pre>
 */
void joystick_set_scaling_factor ( joystick_t *ctx, uint8_t scaling_factor );

/**
 * @brief Set interrupt disabled function
 *
 * @param ctx          Click object.
 *
 * @brief Set interrupt disabled function
 *
 * @description Function set interrupt output is disabled.
 */
void joystick_disabled_interrupt( joystick_t *ctx );

/**
 * @brief Set interrupt enabled function
 *
 * @param ctx          Click object.
 *
 * @description Function set interrupt output is enabled.
 */
void joystick_enabled_interrupt( joystick_t *ctx );

/**
 * @brief Invert the channel voltage function
 *
 * @param ctx          Click object.
 *
 * @description Function set invert the channel voltage,
 * set to invert the magnet polarity.
 */
void joystick_invert_spinning( joystick_t *ctx );

/**
 * @brief Get joystick position function
 *
 * @param ctx          Click object.
 *
 * @return 8-bit data of position
 * <pre>
 * - 0 : Start           Position;
 * - 1 : Top             Position;
 * - 2 : Top-Right       Position;
 * - 3 : Right           Position;
 * - 4 : Bottom-Right    Position;
 * - 5 : Bottom          Position;
 * - 6 : Bottom-Left     Position;
 * - 7 : Left            Position;
 * - 8 : Top-Left        Position;
 * </pre>

 * @description Function get position of miniature joystick module ( N50P105 ),
 * return position state value from 0 to 8 that calculeted
 * by the value read from the register of the AS5013 Hall IC.
 */
uint8_t joystick_get_position( joystick_t *ctx );

/**
 * @brief Get state of interrupt pin function
 *
 * @param ctx          Click object.
 *
 * @return
 * state of INT pin:
 * <pre>
 * - 0 : active low;
 * - 1 : open drain;
 * </pre>
 *
 * @description Function read state of interrupt ( INT ) pin,
 * and return 0 or 1.
 */
uint8_t joystick_get_interrupt ( joystick_t *ctx );

/**
 * @brief Get state of Joystick button function
 *
 * @param ctx          Click object.
 *
 * @return
 * state of CS pin:
 * <pre>
 * - 0 : not active;
 * - 1 : active;
 * </pre>
 *
 * @description Function read state of Joystick button ( CS ) pin,
 * and return 0 or 1.
 */
uint8_t joystick_press_button( joystick_t *ctx );

/**
 * @brief General soft reset function
 *
 * @param ctx          Click object.
 *
 * @description Function soft reset register of the AS5013 Hall IC.
 * All the internal registers are loaded with their reset value.
 * The Control Register 1 is loaded as well with
 * the value 0xF0, then the Soft_rst bit goes back to 0 (Normal mode) once the internal reset sequence is finished.
 */
void joystick_soft_reset( joystick_t *ctx );

/**
 * @brief General hardware reset function
 *
 * @param ctx          Click object.
 *
 * @description Function hardware reset register of the AS5013 Hall IC,
 * by set RST pin high.
 */
void joystick_hardware_reset( joystick_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _JOYSTCIK_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
