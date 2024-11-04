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
 * \brief This file contains API for Knob Click driver.
 *
 * \addtogroup knob Knob Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef KNOB_H
#define KNOB_H

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
#define KNOB_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.ena = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.enb = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.oe = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.sw = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define KNOB_RETVAL  uint8_t

#define KNOB_OK           0x00
#define KNOB_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define KNOB_REG_MODE_1                           0x00
#define KNOB_REG_MODE_2                           0x01
#define KNOB_REG_LED_OUTPUT_STATE_0               0x02
#define KNOB_REG_LED_OUTPUT_STATE_1               0x03
#define KNOB_REG_LED_OUTPUT_STATE_2               0x04
#define KNOB_REG_LED_OUTPUT_STATE_3               0x05
#define KNOB_REG_LED_OUTPUT_STATE_4               0x06
#define KNOB_REG_LED_OUTPUT_STATE_5               0x07
#define KNOB_REG_GROUP_DUTY_CYCLE_CONTROL         0x08
#define KNOB_REG_GROUP_FREQUENCY                  0x09
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_0         0x0A
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_1         0x0B
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_2         0x0C
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_3         0x0D
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_4         0x0E
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_5         0x0F
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_6         0x10
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_7         0x11
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_8         0x12
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_9         0x13
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_10        0x14
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_11        0x15
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_12        0x16
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_13        0x17
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_14        0x18
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_15        0x19
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_16        0x1A
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_17        0x1B
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_18        0x1C
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_19        0x1D
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_20        0x1E
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_21        0x1F
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_22        0x20
#define KNOB_REG_BRIGHTNESS_CONTROL_LED_23        0x21
#define KNOB_REG_OUTPUT_GAIN_CONTROL_0            0x22
#define KNOB_REG_OUTPUT_GAIN_CONTROL_1            0x23
#define KNOB_REG_OUTPUT_GAIN_CONTROL_2            0x24
#define KNOB_REG_OUTPUT_GAIN_CONTROL_3            0x25
#define KNOB_REG_OUTPUT_GAIN_CONTROL_4            0x26
#define KNOB_REG_OUTPUT_GAIN_CONTROL_5            0x27
#define KNOB_REG_OUTPUT_GAIN_CONTROL_6            0x28
#define KNOB_REG_OUTPUT_GAIN_CONTROL_7            0x29
#define KNOB_REG_OUTPUT_GAIN_CONTROL_8            0x2A
#define KNOB_REG_OUTPUT_GAIN_CONTROL_9            0x2B
#define KNOB_REG_OUTPUT_GAIN_CONTROL_10           0x2C
#define KNOB_REG_OUTPUT_GAIN_CONTROL_11           0x2D
#define KNOB_REG_OUTPUT_GAIN_CONTROL_12           0x2E
#define KNOB_REG_OUTPUT_GAIN_CONTROL_13           0x2F
#define KNOB_REG_OUTPUT_GAIN_CONTROL_14           0x30
#define KNOB_REG_OUTPUT_GAIN_CONTROL_15           0x31
#define KNOB_REG_OUTPUT_GAIN_CONTROL_16           0x32
#define KNOB_REG_OUTPUT_GAIN_CONTROL_17           0x33
#define KNOB_REG_OUTPUT_GAIN_CONTROL_18           0x34
#define KNOB_REG_OUTPUT_GAIN_CONTROL_19           0x35
#define KNOB_REG_OUTPUT_GAIN_CONTROL_20           0x36
#define KNOB_REG_OUTPUT_GAIN_CONTROL_21           0x37
#define KNOB_REG_OUTPUT_GAIN_CONTROL_22           0x38
#define KNOB_REG_OUTPUT_GAIN_CONTROL_23           0x39
#define KNOB_REG_OFFSET                           0x3A
#define KNOB_REG_I2C_BUS_SUBADDRESS_1             0x3B
#define KNOB_REG_I2C_BUS_SUBADDRESS_2             0x3C
#define KNOB_REG_I2C_BUS_SUBADDRESS_3             0x3D
#define KNOB_REG_ALL_CALL_I2C_BUS_ADDRESS         0x3E
#define KNOB_REG_BRIGHTNESS_CONTROL_FOR_ALL_LED   0x3F
#define KNOB_REG_GAIN_CONTROL_FOR_ALL_LED         0x40
#define KNOB_REG_OUTPUT_ERROR_FLAG_0              0x41
#define KNOB_REG_OUTPUT_ERROR_FLAG_1              0x42
#define KNOB_REG_OUTPUT_ERROR_FLAG_2              0x43
#define KNOB_REG_OUTPUT_ERROR_FLAG_3              0x44
#define KNOB_REG_OUTPUT_ERROR_FLAG_4              0x45
#define KNOB_REG_OUTPUT_ERROR_FLAG_5              0x46
/** \} */

/**
 * \defgroup mode_register_1 Mode register 1
 * \{
 */
#define KNOB_M1_AUTO_INCREMENT_BIT_1_TO_0      0x00
#define KNOB_M1_AUTO_INCREMENT_BIT_1_TO_1      0x40
#define KNOB_M1_AUTO_INCREMENT_BIT_0_TO_0      0x00
#define KNOB_M1_AUTO_INCREMENT_BIT_0_TO_1      0x20
#define KNOB_M1_SET_NORMAL_MODE                0x00
#define KNOB_M1_SET_LOW_POWER_MODE             0x10
#define KNOB_M1_USES_I2C_BUS_SUBADDRESS_1      0x08
#define KNOB_M1_USES_I2C_BUS_SUBADDRESS_2      0x04
#define KNOB_M1_USES_I2C_BUS_SUBADDRESS_3      0x02
#define KNOB_M1_USES_ALL_CALL_I2C_BUS_ADDRESS  0x01
/** \} */

/**
 * \defgroup mode_register_2 Mode register 2
 * \{
 */
#define KNOB_M2_GROUP_CONTROL_DIMMING   0x00
#define KNOB_M2_GROUP_CONTROL_BLINKING  0x20
#define KNOB_M2_CHANGE_ON_STOP_CMD  0x00
#define KNOB_M2_CHANGE_ON_ACK       0x10
/** \} */

/**
 * \defgroup ctrl_all_led CTRL all LED's
 * \{
 */
#define KNOB_BRIGHTNESS_ALL_LED    0x30
#define KNOB_OUTPUT_GAIN_ALL_LED   0x40
/** \} */

/**
 * \defgroup led_state LED state
 * \{
 */
#define KNOB_LED_ON   0xFF
#define KNOB_LED_OFF  0x00
/** \} */

/**
 * \defgroup sleve_address Slave Address
 * \{
 */
#define KNOB_DEF_SLAVE_ADDRESS  0x70
/** \} */

/**
 * \defgroup full_out_gain Output gain
 * \{
 */
#define KNOB_FULL_OUTPUT_CURRENT_GAIN  0xFF
/** \} */

/**
 * \defgroup led_output_en LED output enable
 * \{
 */
#define KNOB_ENABLE_LED_OUTPUTS  0x00
#define KNOB_DISABLE_LED_OUTPUTS  0x01
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
    digital_out_t oe;

    // Input pins 

    digital_in_t ena;
    digital_in_t enb;
    digital_in_t sw;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    int32_t encoder_position;
    uint8_t state_old_rotate;
    uint8_t state_new_rotate;
    uint8_t start_status;

} knob_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t ena;
    pin_name_t rst;
    pin_name_t enb;
    pin_name_t oe;
    pin_name_t sw;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} knob_cfg_t;

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
void knob_cfg_setup ( knob_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param knob Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
KNOB_RETVAL knob_init ( knob_t *ctx, knob_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Knob Click.
 *
 * @note The default Click set contains:
 *<pre>
 *    -  Led output enable
 *         ** KNOB_ENABLE_LED_OUTPUTS
 *    - Output gain
 *         ** KNOB_OUTPUT_GAIN_ALL_LED
 *         ** KNOB_FULL_OUTPUT_CURRENT_GAIN
 *    - Encoder start position
 *         ** Sets on the 1
 *</pre>
 */
void knob_default_cfg ( knob_t *ctx );

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
void knob_generic_write ( knob_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void knob_generic_read ( knob_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for reset device
 *
 * @param ctx          Click object.
 */
void knob_reset ( knob_t *ctx );

/**
 * @brief Functions for enable Led Output
 *
 * @param ctx          Click object.
 * @param state        Enable or disable leds
 */
void knob_led_output_enable ( knob_t *ctx, uint8_t state);

/**
 * @brief Functions for get ENA pin state
 *
 * @param ctx          Click object.
 * @return ENA (AN) pin state
 */
uint8_t knob_get_ena_state( knob_t *ctx );

/**
 * @brief Functions for get ENB pin state
 *
 * @param ctx          Click object.
 * @return ENB (CS) pin state
 */
uint8_t knob_get_enb_state ( knob_t *ctx );

/**
 * @brief Functions for get SW pin(switch button) state
 *
 * @param ctx          Click object.
 * @return Switch (INT) pin state
 */
uint8_t knob_get_sw_button_state( knob_t *ctx );

/**
 * @brief Functions for set new start encoder position
 *
 * @param ctx          Click object.
 * @param position     Start encoder position
 */
void knob_set_encoder_start_position ( knob_t *ctx, int32_t position );

/**
 * @brief Functions for set led state(PWM on the LED)
 *
 * @param ctx       Click object.
 * @param led       LEDs
 * @param value     PWM (state)
 */
void knob_set_led_state ( knob_t *ctx, uint8_t led, uint8_t state );

/**
 * @brief Functions for set Brightness
 *
 * @param ctx       Click object.
 * @param led       LEDs
 * @param value     PWM(state)
 *
 * @note For Led you can choose to set all LEDs(_KNOBG_BRIGHTNESS_ALL_LED) or
     set one LED( BRIGHTNESS_CONTROL_LED_0 to BRIGHTNESS_CONTROL_LED_23 ) to the desired state
 */
void knob_set_brightness ( knob_t *ctx, uint8_t led, uint8_t value );

/**
 * @brief Functions for set output GAIN
 *
 * @param ctx       Click object.
 * @param led       LEDs
 * @param value     PWM(state)
 *
 * @note For Led you can choose to set all LEDs( OUTPUT_GAIN_ALL_LED ) or
     set one LED( OUTPUT_GAIN_CONTROL_0 to OUTPUT_GAIN_CONTROL_1 ) to the desired state
 */
void knob_set_output_gain ( knob_t *ctx, uint8_t led, uint8_t value );

/**
 * @brief Functions for get Encoder position
 *
 * @param ctx         Click object.
 * @param position    Encoder position (counter)
 * @param dir         Encoder direction
 */
void knob_get_encoder_position ( knob_t *ctx, int32_t *position, uint8_t *dir );

#ifdef __cplusplus
}
#endif
#endif  // _KNOB_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
