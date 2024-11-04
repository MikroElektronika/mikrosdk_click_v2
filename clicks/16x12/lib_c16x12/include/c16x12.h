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
 * \brief This file contains API for 16x12 Click driver.
 *
 * \addtogroup c16x12 16x12 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C16X12_H
#define C16X12_H

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
#define C16X12_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.sdb = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C16X12_RETVAL uint8_t

#define C16X12_OK           0x00
#define C16X12_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define C16X12G_PSR               0xFD     
#define C16X12G_PSWL              0xFE     
#define C16X12G_IMR               0xF0     
#define C16X12G_ISR               0xF1     
#define C16X12G_PSWL_DISABLE      0x00     
#define C16X12G_PSWL_ENABLE       0xC5     
#define C16X12G_IMR_IAC           0x08     
#define C16X12G_IMR_IAB           0x04     
#define C16X12G_IMR_IS            0x02     
#define C16X12G_IMR_IO            0x01     
#define C16X12G_ISR_ABM3          0x10     
#define C16X12G_ISR_ABM2          0x08     
#define C16X12G_ISR_ABM1          0x04     
#define C16X12G_ISR_SB            0x02     
#define C16X12G_ISR_OB            0x01     
/** \} */

/**
 * \defgroup other_macros  Other Macros
 * \{
 */
#define C16X12G_CR_SYNC_MASTER  0x40
#define C16X12G_CR_SYNC_SLAVE   0x80
#define C16X12G_CR_OSD          0x04
#define C16X12G_CR_BEN          0x02
#define C16X12G_CR_SSD          0x01
#define C16X12G_LEDONOFF        0x0000
#define C16X12G_LEDOPEN         0x0018
#define C16X12G_LEDSHORT        0x0030
#define C16X12G_LEDPWM          0x0100
#define C16X12G_LEDABM          0x0200
#define C16X12G_CR              0x0300 
#define C16X12G_GCC             0x0301 
#define C16X12G_ABM1            0x0302 
#define C16X12G_ABM2            0x0306 
#define C16X12G_ABM3            0x030A 
#define C16X12G_TUR             0x030E 
#define C16X12G_SWPUR           0x030F 
#define C16X12G_CSPDR           0x0310 
#define C16X12G_RESET           0x0311 
/** \} */
 
/**
 * \defgroup 
 * \{
 */
#define C16X12G_CS                  16 
#define C16X12G_SW                  12 
#define C16X12G_GND_ADDR            0x00 
#define C16X12G_SCL_ADDR            0x01 
#define C16X12G_SDA_ADDR            0x02 
#define C16X12G_VCC_ADDR            0x03 
#define C16X12G_ABM_LOOP_TIMES_MAX  0x0FFF 
#define C16X12G_ABM_LOOP_FOREVER    0x0000 
/** \} */
 
/**
 * \defgroup switch  Switch
 * \{
 */
#define C16X12G_LED_STATE_OFF  0x00 
#define C16X12G_LED_STATE_ON   0x01 
/** \} */
 
/**
 * \defgroup  setings Setings
 * \{
 */
#define C16X12G_CONTINUE_SETTINGS  0x00 
#define C16X12G_STOP_SETTINGS      0x01 
/** \} */
 
/**
 * \defgroup status Status
 * \{
 */
#define C16X12G_LED_STATUS_NORMAL   0x00 
#define C16X12G_LED_STATUS_OPEN     0x01 
#define C16X12G_LED_STATUS_SHORT    0x02 
#define C16X12G_LED_STATUS_UNKNOWN  0x03 
/** \} */
 
/**
 * \defgroup resistor Resistor
 * \{
 */
#define C16X12G_RESISTOR_OFF 0x00 
#define C16X12G_RESISTOR_500 0x01 
#define C16X12G_RESISTOR_1K  0x02 
#define C16X12G_RESISTOR_2K  0x03 
#define C16X12G_RESISTOR_4K  0x04 
#define C16X12G_RESISTOR_8K  0x05 
#define C16X12G_RESISTOR_16K 0x06 
#define C16X12G_RESISTOR_32K 0x07 
/** \} */
 
/**
 * \defgroup led_mode Led Mode
 * \{
 */
#define C16X12G_LED_MODE_PWM  0x00 
#define C16X12G_LED_MODE_ABM1 0x01 
#define C16X12G_LED_MODE_ABM2 0x02 
#define C16X12G_LED_MODE_ABM3 0x03 
/** \} */
 
/**
 * \defgroup t1 T1
 * \{
 */
#define C16X12G_ABM_T1_210MS   0x00 
#define C16X12G_ABM_T1_420MS   0x20 
#define C16X12G_ABM_T1_840MS   0x40 
#define C16X12G_ABM_T1_1680MS  0x60 
#define C16X12G_ABM_T1_3360MS  0x80 
#define C16X12G_ABM_T1_6720MS  0xA0 
#define C16X12G_ABM_T1_13440MS 0xC0 
#define C16X12G_ABM_T1_26880MS 0xE0 
/** \} */
 
/**
 * \defgroup t2 T2
 * \{
 */ 
#define C16X12G_ABM_T2_0MS     0x00 
#define C16X12G_ABM_T2_210MS   0x02 
#define C16X12G_ABM_T2_420MS   0x04 
#define C16X12G_ABM_T2_840MS   0x06 
#define C16X12G_ABM_T2_1680MS  0x08 
#define C16X12G_ABM_T2_3360MS  0x0A 
#define C16X12G_ABM_T2_6720MS  0x0C 
#define C16X12G_ABM_T2_13440MS 0x0E 
#define C16X12G_ABM_T2_26880MS 0x10 
/** \} */
 
/**
 * \defgroup t3 T3
 * \{
 */
#define C16X12G_ABM_T3_210MS   0x00 
#define C16X12G_ABM_T3_420MS   0x20 
#define C16X12G_ABM_T3_840MS   0x40 
#define C16X12G_ABM_T3_1680MS  0x60 
#define C16X12G_ABM_T3_3360MS  0x80 
#define C16X12G_ABM_T3_6720MS  0xA0 
#define C16X12G_ABM_T3_13440MS 0xC0 
#define C16X12G_ABM_T3_26880MS 0xE0 
/** \} */
 
/**
 * \defgroup t4 T4
 * \{
 */
#define C16X12G_ABM_T4_0MS      0x00 
#define C16X12G_ABM_T4_210MS    0x02 
#define C16X12G_ABM_T4_420MS    0x04 
#define C16X12G_ABM_T4_840MS    0x06 
#define C16X12G_ABM_T4_1680MS   0x08 
#define C16X12G_ABM_T4_3360MS   0x0A 
#define C16X12G_ABM_T4_6720MS   0x0C 
#define C16X12G_ABM_T4_13440MS  0x0E 
#define C16X12G_ABM_T4_26880MS  0x10 
#define C16X12G_ABM_T4_53760MS  0x12 
#define C16X12G_ABM_T4_107520MS 0x14 
/** \} */
 
/**
 * \defgroup amp_loop_begin  Amp Loop Begin
 * \{
 */
#define C16X12G_ABM_LOOP_BEGIN_T1 0x00 
#define C16X12G_ABM_LOOP_BEGIN_T2 0x10 
#define C16X12G_ABM_LOOP_BEGIN_T3 0x20 
#define C16X12G_ABM_LOOP_BEGIN_T4 0x30 
/** \} */
 
/**
 * \defgroup end End
 * \{
 */
#define C16X12G_ABM_LOOP_END_T3 0x00 
#define C16X12G_ABM_LOOP_END_T1 0x40 
/** \} */
 
/**
 * \defgroup number Number
 * \{
 */
#define C16X12G_ABM_NUM_1 0x0302 
#define C16X12G_ABM_NUM_2 0x0306 
#define C16X12G_ABM_NUM_3 0x030A 
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
    digital_out_t sdb;
    
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} c16x12_t;

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
    pin_name_t sdb;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} c16x12_cfg_t;

/**
 * @brief ABM structure definition.
 */
typedef struct
{
    uint8_t  time_1;
    uint8_t  time_2;
    uint8_t  time_3;
    uint8_t  time_4;
    uint8_t  loop_begin;
    uint8_t  loop_end;
    uint16_t loop_times;

}c16x12_abm_t;

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
void c16x12_cfg_setup ( c16x12_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
C16X12_RETVAL c16x12_init ( c16x12_t *ctx, c16x12_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 16x12 Click.
 */
void c16x12_default_cfg ( c16x12_t *ctx );

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
void c16x12_generic_write ( c16x12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void c16x12_generic_read ( c16x12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for write one byte in register
 *
 * @param ctx          Click object.
 * @param reg          Register in which the data will be written
 * @param c_data       Data which be written in the register
 */
void c16x12g_write_reg ( c16x12_t *ctx, uint8_t reg, uint8_t c_data );

/**
 * @brief Functions for select page
 *
 * @param ctx          Click object.
 * @param page         The page to be set
 */
void c16x12g_select_page ( c16x12_t *ctx, uint8_t page );

/**
 * @brief Functions for write one byte in register with select page
 *
 * @param ctx             Click object. 
 * @param reg_addr        Register in which the data will be written
 * @param reg_value       Data which be written in the register
 *
 * @note reg_addr contains page(MSB) and registar address (LSB) 
 */
void c16x12g_write_page_byte ( c16x12_t *ctx, uint16_t reg_addr, uint8_t reg_value );

/**
 * @brief Functions for write n byte in registers with select page
 *
 * @param ctx            Click object.  
 * @param reg            Start register in which the data will be written
 * @param data_buf       Data which be written in the registers
 * @param n_data         Number of the data which be written in the registers
 *
 * @note reg contains page(MSB) and registar address (LSB) 
 */
void c16x12g_write_page_data ( c16x12_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t n_data );

/**
 * @brief Functions for read byte from register
 *
 * @param ctx            Click object.   
 * @param reg            Register which will be read
 * @retval one byte data which is read from the register
 */
uint8_t c16x12g_read_reg ( c16x12_t *ctx, uint8_t reg );

/**
 * @brief Functions for sets SDB pin state
 *
 * @param ctx             Click object. 
 * @param state           SDB pin state
 */
void c16x12g_set_stand_by ( c16x12_t *ctx, uint8_t state );

/**
 * @brief Functions for device reset
 *
 * @param ctx             Click object.
 */
void c16x12g_device_reset ( c16x12_t *ctx );

/**
 * @brief Functions for reads interrupt state
 *
 * @param ctx             Click object. 
 *
 * @retval Interrupt state on the INT pin
 */
uint8_t c16x12g_get_interrupt ( c16x12_t *ctx );

/**
 * @brief Functions for device configuration 
 *
 * @param ctx             Click object.
 * 
 * @note
    Configuration of the device implies setting all LEDs to the OFF state
	and setting the SDB pin to the ON state
 */
void c16x12g_device_configuration ( c16x12_t *ctx );

/**
 * @brief Functions for sets all LEDs on the state 
 *
 * @param ctx             Click object.
 *
 * @note
       Use this function when it is necessary to set all LEDs to the state OFF or ON state
 */
void c16x12g_set_all_leds ( c16x12_t *ctx, uint8_t state );

/**
 * @brief Functions for sets global current for all leds
 *
 * @param ctx             Click object.
 *
 * @param gcc    Gl    oba current 
 */
void c16x12g_set_global_current_control ( c16x12_t *ctx, uint8_t gcc );

/**
 * @brief Functions for clear display
 *
 * @param ctx             Click object. 
 */
void c16x12g_clear_display ( c16x12_t *ctx );

/**
 * @brief Functions for sets column state
 *
 * @param ctx          Click object. 
 * @param col          Column - from 1 to 12
 * @param state        16 bit data - 1 bit is 1 led
 * @param c_end        A variable that indicates whether after this function the 
                       setting of a new column is continued or the end is set to be set 
					   and everything that has been set so far should be displayed.
					   (_C16X12G_STOP_SETTINGS or _C16X12G_CONTINUE_SETTINGS)
 */
void c16x12g_set_column_state ( c16x12_t *ctx, uint8_t col, uint16_t state, uint8_t c_end );

/**
 * @brief Functions for sets LEDs mode
 *
 * @param ctx             Click object. 
 * @param mode          LEDs mode 
 *
 * Options for sets Led mode:
      _C16X12G_LED_MODE_PWM 
      _C16X12G_LED_MODE_ABM1
      _C16X12G_LED_MODE_ABM2
      _C16X12G_LED_MODE_ABM3
 *
 * @note 
     If PWM led mode is set, it is necessary to call the PWM setting for all LEDs 
*/
void c16x12g_set_leds_mode ( c16x12_t *ctx, uint8_t mode );

/**
 * @brief Functions for sets PWM for all LEDs
 *
 * @param ctx             Click object.
 * @param pwm_value          PWM value 
*/
void c16x12g_set_pmw ( c16x12_t *ctx, uint8_t pwm_value );

/**
 * @brief Functions for sets LEDs state
 *
 * @param ctx             Click object.
 *
 * @param x_pos          X poistion of the LEDs (1 is bottom - 12 is up) 
 * @param y_pos          Y poistion of the LEDs (1 is right - 12 is left)
 * @param state          LEDs state (ON or OFF)
 * @param c_end          A variable that indicates whether after this function the 
                         setting of a new LEDs is continued or the end is set to be set 
					     and everything that has been set so far should be displayed.
					     (_C16X12G_STOP_SETTINGS or _C16X12G_CONTINUE_SETTINGS) 

*/
void c16x12g_set_led ( c16x12_t *ctx, uint8_t x_pos, uint8_t y_pos, uint8_t state, uint8_t c_end );

/**
 * @brief Functions for display one Byte
 *
 * @param ctx             Click object. 
 *
 * @param ch             The character to be displayed
*/
void c16x12g_display_byte ( c16x12_t *ctx, char ch );

/**
 * @brief Functions for display Image 
 *
 * @param ctx             Click object. 
 *
 * @param p_image         Image buffer
*/
void c16x12g_display_image ( c16x12_t *ctx, uint16_t *p_image );

/**
 * @brief Functions for display text with scroll 
 *
 * @param ctx             Click object. 
 *
 * @param p_text          Text buffer
 * @param n_char          Number of the character in the text
 * @param speed           Speed per character in ms
*/
void c16x12g_display_text ( c16x12_t *ctx, char *p_text, uint8_t n_char, uint8_t speed );

/**
 * @brief Functions for ABM configuration
 *
 * @param ctx             Click object. 
 *
 * @param n_abm           Number of the ABM
 * @param config          ABM structure with new configuration
*/
void c16x12g_config_abm ( c16x12_t *ctx, uint16_t n_abm, c16x12_abm_t *config );

/**
 * @brief Functions for start new ABM configuration
 *
 * @param ctx             Click object. 
 *
 * @param ctx             Click object. 
*/
void c16x12g_start_abm ( c16x12_t *ctx );



#ifdef __cplusplus
}
#endif
#endif  // _C16X12_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
