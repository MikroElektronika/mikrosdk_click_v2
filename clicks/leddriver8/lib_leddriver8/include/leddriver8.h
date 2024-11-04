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
 * \brief This file contains API for LED Driver 8 Click driver.
 *
 * \addtogroup leddriver8 LED Driver 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LEDDRIVER8_H
#define LEDDRIVER8_H

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

#define LEDDRIVER8_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */
 
/**
 * \defgroup error_code Error Code
 * \{
 */
#define LEDDRIVER8_RETVAL  uint8_t

#define LEDDRIVER8_OK           0x00
#define LEDDRIVER8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers  Registers
 * \{
 */
#define LEDDRIVER8_REG_MODE_1             0x00
#define LEDDRIVER8_REG_MODE_2             0x01
#define LEDDRIVER8_REG_OUT_ERROR_FLAG_0   0x02
#define LEDDRIVER8_REG_OUT_ERROR_FLAG_1   0x03
#define LEDDRIVER8_REG_OUT_ERROR_FLAG_2   0x04
#define LEDDRIVER8_REG_OUT_ERROR_FLAG_3   0x05
#define LEDDRIVER8_REG_OUT_ERROR_FLAG_4   0x06
#define LEDDRIVER8_REG_OUT_ERROR_FLAG_5   0x07
#define LEDDRIVER8_REG_LED_OUTPUT_0       0x08
#define LEDDRIVER8_REG_LED_OUTPUT_1       0x09
#define LEDDRIVER8_REG_LED_OUTPUT_2       0x0A
#define LEDDRIVER8_REG_LED_OUTPUT_3       0x0B
#define LEDDRIVER8_REG_LED_OUTPUT_4       0x0C
#define LEDDRIVER8_REG_LED_OUTPUT_5       0x0D
#define LEDDRIVER8_REG_GRP_PWM            0x0E
#define LEDDRIVER8_REG_GRP_FREQ           0x0F
#define LEDDRIVER8_REG_BRIGHTNESS_LED_0   0x10
#define LEDDRIVER8_REG_BRIGHTNESS_LED_1   0x11
#define LEDDRIVER8_REG_BRIGHTNESS_LED_2   0x12
#define LEDDRIVER8_REG_BRIGHTNESS_LED_3   0x13
#define LEDDRIVER8_REG_BRIGHTNESS_LED_4   0x14
#define LEDDRIVER8_REG_BRIGHTNESS_LED_5   0x15
#define LEDDRIVER8_REG_BRIGHTNESS_LED_6   0x16
#define LEDDRIVER8_REG_BRIGHTNESS_LED_7   0x17
#define LEDDRIVER8_REG_BRIGHTNESS_LED_8   0x18
#define LEDDRIVER8_REG_BRIGHTNESS_LED_9   0x19
#define LEDDRIVER8_REG_BRIGHTNESS_LED_10  0x1A
#define LEDDRIVER8_REG_BRIGHTNESS_LED_11  0x1B
#define LEDDRIVER8_REG_BRIGHTNESS_LED_12  0x1C
#define LEDDRIVER8_REG_BRIGHTNESS_LED_13  0x1D
#define LEDDRIVER8_REG_BRIGHTNESS_LED_14  0x1E
#define LEDDRIVER8_REG_BRIGHTNESS_LED_15  0x1F
#define LEDDRIVER8_REG_BRIGHTNESS_LED_16  0x20
#define LEDDRIVER8_REG_BRIGHTNESS_LED_17  0x21
#define LEDDRIVER8_REG_BRIGHTNESS_LED_18  0x22
#define LEDDRIVER8_REG_BRIGHTNESS_LED_19  0x23
#define LEDDRIVER8_REG_BRIGHTNESS_LED_20  0x24
#define LEDDRIVER8_REG_BRIGHTNESS_LED_21  0x25
#define LEDDRIVER8_REG_BRIGHTNESS_LED_22  0x26
#define LEDDRIVER8_REG_BRIGHTNESS_LED_23  0x27
#define LEDDRIVER8_REG_IREF_0             0x28
#define LEDDRIVER8_REG_IREF_1             0x29
#define LEDDRIVER8_REG_IREF_2             0x2A
#define LEDDRIVER8_REG_IREF_3             0x2B
#define LEDDRIVER8_REG_IREF_4             0x2C
#define LEDDRIVER8_REG_IREF_5             0x2D
#define LEDDRIVER8_REG_IREF_6             0x2E
#define LEDDRIVER8_REG_IREF_7             0x2F
#define LEDDRIVER8_REG_IREF_8             0x30
#define LEDDRIVER8_REG_IREF_9             0x31
#define LEDDRIVER8_REG_IREF_10            0x32
#define LEDDRIVER8_REG_IREF_11            0x33
#define LEDDRIVER8_REG_IREF_12            0x34
#define LEDDRIVER8_REG_IREF_13            0x35
#define LEDDRIVER8_REG_IREF_14            0x36
#define LEDDRIVER8_REG_IREF_15            0x37
#define LEDDRIVER8_REG_IREF_16            0x38
#define LEDDRIVER8_REG_IREF_17            0x39
#define LEDDRIVER8_REG_IREF_18            0x3A
#define LEDDRIVER8_REG_IREF_19            0x3B
#define LEDDRIVER8_REG_IREF_20            0x3C
#define LEDDRIVER8_REG_IREF_21            0x3D
#define LEDDRIVER8_REG_IREF_22            0x3E
#define LEDDRIVER8_REG_IREF_23            0x3F
#define LEDDRIVER8_REG_RAMP_RATE_GRP0     0x40
#define LEDDRIVER8_REG_STEP_TIME_GRP0     0x41
#define LEDDRIVER8_REG_HOLD_CNTL_GRP0     0x42
#define LEDDRIVER8_REG_IREF_GRP0          0x43
#define LEDDRIVER8_REG_RAMP_RATE_GRP1     0x44
#define LEDDRIVER8_REG_STEP_TIME_GRP1     0x45
#define LEDDRIVER8_REG_HOLD_CNTL_GRP1     0x46
#define LEDDRIVER8_REG_IREF_GRP1          0x47
#define LEDDRIVER8_REG_RAMP_RATE_GRP2     0x48
#define LEDDRIVER8_REG_STEP_TIME_GRP2     0x49
#define LEDDRIVER8_REG_HOLD_CNTL_GRP2     0x4A
#define LEDDRIVER8_REG_IREF_GRP2          0x4B
#define LEDDRIVER8_REG_RAMP_RATE_GRP3     0x4C
#define LEDDRIVER8_REG_STEP_TIME_GRP3     0x4D
#define LEDDRIVER8_REG_HOLD_CNTL_GRP3     0x4E
#define LEDDRIVER8_REG_IREF_GRP3          0x4F
#define LEDDRIVER8_REG_RAMP_RATE_GRP4     0x50
#define LEDDRIVER8_REG_STEP_TIME_GRP4     0x51
#define LEDDRIVER8_REG_HOLD_CNTL_GRP4     0x52
#define LEDDRIVER8_REG_IREF_GRP4          0x53
#define LEDDRIVER8_REG_RAMP_RATE_GRP5     0x54
#define LEDDRIVER8_REG_STEP_TIME_GRP5     0x55
#define LEDDRIVER8_REG_HOLD_CNTL_GRP5     0x56
#define LEDDRIVER8_REG_IREF_GRP5          0x57
#define LEDDRIVER8_REG_GRAD_MODE_SEL0     0x58
#define LEDDRIVER8_REG_GRAD_MODE_SEL1     0x59
#define LEDDRIVER8_REG_GRAD_MODE_SEL2     0x5A
#define LEDDRIVER8_REG_GRAD_GRP_SEL0      0x5B
#define LEDDRIVER8_REG_GRAD_GRP_SEL1      0x5C
#define LEDDRIVER8_REG_GRAD_GRP_SEL2      0x5D
#define LEDDRIVER8_REG_GRAD_GRP_SEL3      0x5E
#define LEDDRIVER8_REG_GRAD_GRP_SEL4      0x5F
#define LEDDRIVER8_REG_GRAD_GRP_SEL5      0x60
#define LEDDRIVER8_REG_GRAD_GRP_SEL6      0x61
#define LEDDRIVER8_REG_GRAD_GRP_SEL7      0x62
#define LEDDRIVER8_REG_GRAD_GRP_SEL8      0x63
#define LEDDRIVER8_REG_GRAD_GRP_SEL9      0x64
#define LEDDRIVER8_REG_GRAD_GRP_SEL10     0x65
#define LEDDRIVER8_REG_GRAD_GRP_SEL11     0x66
#define LEDDRIVER8_REG_GRAD_CTRL_0        0x67
#define LEDDRIVER8_REG_GRAD_CTRL_1        0x68
#define LEDDRIVER8_REG_OFFSET             0x69
#define LEDDRIVER8_REG_PWM_ALL            0x6A
#define LEDDRIVER8_REG_IREF_ALL           0x6B
/** \} */

/**
 * \defgroup mode_1  Mode 1
 * \{
 */
#define LEDDRIVER8_MODE1_NORMAL_MODE   0x00
#define LEDDRIVER8_MODE1_SLEEP_MODE    0x10
/** \} */
 
/**
 * \defgroup mode_2  Mode 2
 * \{
 */
#define LEDDRIVER8_MODE2_DMBLNK_DIMMING        0x00
#define LEDDRIVER8_MODE2_DMBLNK_BLINKING       0x20
#define LEDDRIVER8_MODE2_CLRERR_NO             0x00
#define LEDDRIVER8_MODE2_CLRERR_ALL            0x10
#define LEDDRIVER8_MODE2_AUTO_SWITCH_OFF_DIS   0x08
#define LEDDRIVER8_MODE2_EXP_ENABLE            0x04
#define LEDDRIVER8_MODE2_EXP_DISABLE           0x00
/** \} */
 
/**
 * \defgroup led_output  Led output
 * \{
 */
#define LEDDRIVER8_LED_DRIVER_0_23         0x00
#define LEDDRIVER8_LED_DRIVER_FULL         0x01
#define LEDDRIVER8_LED_DRIVER_PWMX         0x02
#define LEDDRIVER8_LED_DRIVER_GRPPWM       0x03

#define LEDDRIVER8_BRIGHTNESS_ALL_LED        0x30
#define LEDDRIVER8_OUTPUT_GAIN_ALL_LED       0x40
#define LEDDRIVER8_FULL_OUTPUT_CURRENT_GAIN  0xFF

#define LEDDRIVER8_ENABLE_LED_OUTPUTS    0x00
#define LEDDRIVER8_DISABLE_LED_OUTPUTS   0x01

#define LEDDRIVER8_MAX_BRIGHTNESS        0xFF
#define LEDDRIVER8_MIN_BRIGHTNESS        0x00
/** \} */
 
/**
 * \defgroup leds  leds
 * \{
 */
#define LEDDRIVER8_LED_0                 0x00
#define LEDDRIVER8_LED_1                 0x01
#define LEDDRIVER8_LED_2                 0x02
#define LEDDRIVER8_LED_3                 0x03
#define LEDDRIVER8_LED_4                 0x04
#define LEDDRIVER8_LED_5                 0x05
#define LEDDRIVER8_LED_6                 0x06
#define LEDDRIVER8_LED_7                 0x07
#define LEDDRIVER8_LED_8                 0x08
#define LEDDRIVER8_LED_9                 0x09
#define LEDDRIVER8_LED_10                0x0A
#define LEDDRIVER8_LED_11                0x0B
#define LEDDRIVER8_LED_12                0x0C
#define LEDDRIVER8_LED_13                0x0D
#define LEDDRIVER8_LED_14                0x0E
#define LEDDRIVER8_LED_15                0x0F
#define LEDDRIVER8_LED_16                0x10
#define LEDDRIVER8_LED_17                0x11
#define LEDDRIVER8_LED_18                0x12
#define LEDDRIVER8_LED_19                0x13
#define LEDDRIVER8_LED_20                0x14
#define LEDDRIVER8_LED_21                0x15
#define LEDDRIVER8_LED_22                0x16
#define LEDDRIVER8_LED_23                0x17
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
    digital_out_t cs;
    // Output pins 

    digital_out_t rst;
    digital_out_t pwm;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} leddriver8_t;

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

    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t pwm;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} leddriver8_cfg_t;

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
void leddriver8_cfg_setup ( leddriver8_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param leddriver8 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
LEDDRIVER8_RETVAL leddriver8_init ( leddriver8_t *ctx, leddriver8_cfg_t *cfg );

/**
 * @brief Functions for write one byte in the register
 *
 * @param ctx          Click object.
 * @param reg    Data register in which data will be written
 * @param data_byte  Data byte
 */
void leddriver8_write_data ( leddriver8_t *ctx, uint8_t reg, uint8_t data_byte );

/**
 * @brief Functions for read byte from register
 *
 * @param ctx          Click object.
 * @param reg   Register of the data will be read
 * @retval one-byte data read from the register
 */
uint8_t leddriver8_read_data ( leddriver8_t *ctx, uint8_t reg );

/**
 * @brief Functions for enable led output
 *
 * @param ctx          Click object.
 * @param state 0 - OUTPUT ENABLE // 1 - OUTPUT DISABLE
 */
void leddriver8_output_enable_pin( leddriver8_t *ctx, uint8_t state );

/**
 * @brief Device reset function
 * 
 * @param ctx          Click object.
 * 
 */
void leddriver8_reset( leddriver8_t *ctx );

/**
 * @brief Function for set Brightness
 *
 * @param ctx          Click object.
 * @param num_led       LEDs
 * @param value         PWM ( state )
 *
 * @note:
 *    User can choose to set all LEDs( LEDDRIVER8_BRIGHTNESS_ALL_LED ) or
 *    set one LED ( LEDDRIVER8_LED_0 to LEDDRIVER8_LED_23 ) to change brightness
 */
void leddriver8_set_brightness ( leddriver8_t *ctx, uint8_t num_led, uint8_t value );

/**
 * @brief Function for set output gain
 *
 * @param ctx          Click object.
 * @param num_led     LEDs
 * @param value       Gain value (current limit)
 *
 * @note:
      User can choose to set all LEDs( LEDDRIVER8_OUTPUT_GAIN_ALL_LED ) or
 *    set one LED ( LEDDRIVER8_LED_0 to LEDDRIVER8_LED_23 ) to change current limit
 */
void leddriver8_set_output_gain ( leddriver8_t *ctx, uint8_t num_led, uint8_t value );

/**
 * @brief Function for set mode registers
 *
 * @param ctx          Click object.
 * @param mode_1  Mode 1 settings
 * @param mode_2  Mode 2 settings
 */
void leddriver8_set_mode_register( leddriver8_t *ctx, uint8_t mode_1, uint8_t mode_2 );

#ifdef __cplusplus
}
#endif
#endif  // _LEDDRIVER8_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
