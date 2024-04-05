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
 * \brief This file contains API for OLED Switch Click driver.
 *
 * \addtogroup oledswitch OLED Switch Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OLEDSWITCH_H
#define OLEDSWITCH_H

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

#define OLEDSWITCH_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.cd    = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OLEDSWITCH_RETVAL  uint8_t

#define OLEDSWITCH_OK           0x00
#define OLEDSWITCH_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup initialization_commands Initialization Commands
 * \{
 */
#define OLEDSWITCH_15_CONTRAST_FOR_COLOR_A_1                         0x81
#define OLEDSWITCH_15_CONTRAST_FOR_COLOR_A_2                         0x19
#define OLEDSWITCH_15_CONTRAST_FOR_COLOR_B_1                         0x82
#define OLEDSWITCH_15_CONTRAST_FOR_COLOR_B_2                         0x14      
#define OLEDSWITCH_15_CONTRAST_FOR_COLOR_C_1                         0x83
#define OLEDSWITCH_15_CONTRAST_FOR_COLOR_C_2                         0x24

#define OLEDSWITCH_30_CONTRAST_FOR_COLOR_A_1                         0x81
#define OLEDSWITCH_30_CONTRAST_FOR_COLOR_A_2                         0x15
#define OLEDSWITCH_30_CONTRAST_FOR_COLOR_B_1                         0x82
#define OLEDSWITCH_30_CONTRAST_FOR_COLOR_B_2                         0x1A      
#define OLEDSWITCH_30_CONTRAST_FOR_COLOR_C_1                         0x83
#define OLEDSWITCH_30_CONTRAST_FOR_COLOR_C_2                         0x17
                    
#define OLEDSWITCH_MASTER_CURRENT_CONTROL_1                          0x87
#define OLEDSWITCH_MASTER_CURRENT_CONTROL_2                          0x0F

#define OLEDSWITCH_REMAP_AND_COLOR_DEPTH_SETTING_1                    0xA0
#define OLEDSWITCH_REMAP_AND_COLOR_DEPTH_SETTING_2                    0x70
             
#define OLEDSWITCH_SET_DISPLAY_START_LINE_1                           0xA1
#define OLEDSWITCH_SET_DISPLAY_START_LINE_2                           0x00
                     
#define OLEDSWITCH_SET_DISPLAY_OFFSET_1                               0xA2
#define OLEDSWITCH_SET_DISPLAY_OFFSET_2                               0x10
                         
#define OLEDSWITCH_NORMAL_DISPLAY                                     0xA4
                             
#define OLEDSWITCH_MULTIPLEX_RATIO_1                                  0xA8
#define OLEDSWITCH_MULTIPLEX_RATIO_2                                  0x2F
    
#define OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_1                 0xAB
#define OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_2                 0x00
#define OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_3                 0x12
#define OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_4                 0x0C
#define OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_5                 0x14
#define OLEDSWITCH_DIM_MODE_SETTING_FOR_COLOR_A_B_C_6                 0x12
              
#define OLEDSWITCH_MASTER_CONFIGURATION_1                             0xAD
#define OLEDSWITCH_MASTER_CONFIGURATION_2                             0x8E
                          
#define OLEDSWITCH_POWER_SAVE_MODE_1                                  0xB0
#define OLEDSWITCH_POWER_SAVE_MODE_2                                  0x0B
    
#define OLEDSWITCH_PHASE_1_AND_2_PERIOD_ADJUSTMENT_1                  0xB1
#define OLEDSWITCH_PHASE_1_AND_2_PERIOD_ADJUSTMENT_2                  0x44
    
#define OLEDSWITCH_DISPLAY_CLOCK_DIVIDER_OSCILLATOR_FREQUENCY_1       0xB3
#define OLEDSWITCH_DISPLAY_CLOCK_DIVIDER_OSCILLATOR_FREQUENCY_2       0xA0
    
#define OLEDSWITCH_ENABLE_LINEAR_GRAY_SCALE                           0xB9
                        
#define OLEDSWITCH_PRE_CHARGE_LEVEL_1                                 0xBB
#define OLEDSWITCH_PRE_CHARGE_LEVEL_2                                 0x12
                              
#define OLEDSWITCH_15_SET_VCOMH_1                                     0xBE
#define OLEDSWITCH_15_SET_VCOMH_2                                     0x28

#define OLEDSWITCH_30_SET_VCOMH_1                                     0xBE
#define OLEDSWITCH_30_SET_VCOMH_2                                     0x3E
                       
#define OLEDSWITCH_DISPLAY_ON_IN_NORMAL_MODE                          0xAF
/** \} */

/**
 * \defgroup configuration_variables Configuration Variables
 * \{
 */
#define OLEDSWITCH_BUFFER_SIZE_BIG        0x00
#define OLEDSWITCH_BUFFER_SIZE_SMALL      0x01 
 
#define OLEDSWITCH_FILL_ENABLE_DISABLE    0x26 
 
#define OLEDSWITCH_ROW_RANGE              0x75 
 
#define OLEDSWITCH_COLUMN_RANGE           0x15
 
#define OLEDSWITCH_CLEAR_WINDOW           0x25

#define OLEDSWITCH_DEACTIVATE_SCROLLING   0x2E

#define OLEDSWITCH_ACTIVATE_SCROLLING     0x2F

#define OLEDSWITCH_SCROLLING_SETUP        0x27

#define OLEDSWITCH_IMG_SIZE_NORMAL        6144
#define OLEDSWITCH_IMG_SIZE_BIG           12288
/** \} */

/**
 * \defgroup initialization_commands_15000 Initialization Commands 15000
 * \{
 */

/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Scroll structure.
 */
typedef struct 
{
    uint8_t column_horizontal_shift;
    uint8_t row_horizontal_shift;
    uint8_t row_vertical_shift;
    uint8_t row_offset;
    uint8_t interval;

} oledswitch_scroll_t;

/**
 * @brief Coordinate structure.
 */
typedef struct
{
    uint8_t column_start;
    uint8_t column_end;
    uint8_t row_start;
    uint8_t row_end;

} oledswitch_coordinate_t;

/**
 * @brief Color structure.
 */
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

} oledswitch_color_t;

/**
 * @brief Contrast structure.
 */
typedef struct
{
    uint8_t a;
    uint8_t b;
    uint8_t c;

} oledswitch_contrast_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t cd;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    oledswitch_coordinate_t coordinate;
    oledswitch_contrast_t contrast;
    oledswitch_scroll_t scroll;
    oledswitch_color_t color;

} oledswitch_t;

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
    pin_name_t cd;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} oledswitch_cfg_t;

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
void oledswitch_cfg_setup ( oledswitch_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param oledswitch Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OLEDSWITCH_RETVAL oledswitch_init ( oledswitch_t *ctx, oledswitch_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for OLED Switch click.
 */
void oledswitch_default_cfg ( oledswitch_t *ctx, uint8_t buffer_size );

/**
 * @brief Register write function.
 *
 * @param ctx         Click object.
 * @param write_buf   Pointer to a data array that will be written.
 * @param len         Number of bytes in the data array.
 *
 * @description This function writes to control and configuration registers on the chip.
 */
void oledswitch_reg_write ( oledswitch_t *ctx, uint8_t *write_buf, uint8_t len );

/**
 * @brief Register write function.
 *
 * @param ctx          Click object.
 * @param image_buf    Pointer to a image array that will be displayed.
 * @param image_size   Number of bytes in the image array.
 *
 * @description This function writes image data to the chip, which displays it in real time.
 */
void oledswitch_draw_image ( oledswitch_t *ctx, const uint8_t *image_buf, uint16_t image_size );

/**
 * @brief Set contrast function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes contrast configuration data to the chip.
 */
void oledswitch_set_contrast ( oledswitch_t *ctx );

/**
 * @brief Set master current function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes master current configuration data to the chip.
 */
void oledswitch_set_master_current ( oledswitch_t *ctx );

/**
 * @brief Set remap color depth function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes remap color depth configuration data to the chip.
 */
void oledswitch_set_remap_color_depth ( oledswitch_t *ctx );

/**
 * @brief Set display start line function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes display start line configuration data to the chip.
 */
void oledswitch_set_display_start_line ( oledswitch_t *ctx );

/**
 * @brief Set display offset function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes display offset configuration data to the chip.
 */
void oledswitch_set_display_offset ( oledswitch_t *ctx );

/**
 * @brief Set normal display function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes normal display configuration data to the chip.
 */
void oledswitch_set_normal_display ( oledswitch_t *ctx );

/**
 * @brief Set multiplex ratio function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes multiplex ratio configuration data to the chip.
 */
void oledswitch_set_multiplex_ratio ( oledswitch_t *ctx );

/**
 * @brief Set dim mode function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes dim mode configuration data to the chip.
 */
void oledswitch_set_dim_mode ( oledswitch_t *ctx );

/**
 * @brief Set master config function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes master configuration data to the chip.
 */
void oledswitch_set_master_config ( oledswitch_t *ctx );

/**
 * @brief Set power save mode function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes power save mode configuration data to the chip.
 */
void oledswitch_set_power_save_mode ( oledswitch_t *ctx );

/**
 * @brief Set phase period adjustment function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes phase period adjustment configuration data to the chip.
 */
void oledswitch_set_phase_period_adjustment ( oledswitch_t *ctx );

/**
 * @brief Display clock divider oscillator frequency function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes display clock divider oscillator frequency
 *              configuration data to the chip.
 */
void oledswitch_display_clock_divider_oscillator_frequency ( oledswitch_t *ctx );

/**
 * @brief Enable linear gray scale function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes linear gray scale configuration data to the chip.
 */
void oledswitch_enable_linear_gray_scale ( oledswitch_t *ctx );

/**
 * @brief Set pre-charge level function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes pre-charge level configuration data to the chip.
 */
void oledswitch_pre_charge_level ( oledswitch_t *ctx );

/**
 * @brief Set vcomh function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes vcomh configuration data to the chip.
 */
void oledswitch_set_vcomh ( oledswitch_t *ctx );

/**
 * @brief Display normal mode function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes display mode configuration data to the chip.
 */
void oledswitch_display_normal_mode ( oledswitch_t *ctx );

/**
 * @brief Set row range function.
 *
 * @param ctx     Click object.
 * @param start   Start pixel position value.
 * @param end     End pixel position value.
 *
 * @description This function sets the row range for the display.
 */
void oledswitch_set_row_range ( oledswitch_t *ctx, uint8_t start, uint8_t end );

/**
 * @brief Set column range function.
 *
 * @param ctx     Click object.
 * @param start   Start pixel position value.
 * @param end     End pixel position value.
 *
 * @description This function sets the column range for the display.
 */
void oledswitch_set_column_range ( oledswitch_t *ctx, uint8_t start, uint8_t end );

/**
 * @brief Clear window function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes the clear display command and sends row and column
 *              data to the chip.
 */
void oledswitch_clear_window ( oledswitch_t *ctx );

/**
 * @brief Deactivate scrolling function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes the deactivate scrolling command to the chip.
 */
void oledswitch_deactivate_scrolling ( oledswitch_t *ctx );

/**
 * @brief Activate scrolling function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes the activate scrolling command to the chip.
 */
void oledswitch_activate_scrolling ( oledswitch_t *ctx );

/**
 * @brief Demo scroling setup function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes the scrolling setup configuration to the chip.
 */
void oledswitch_demo_scrolling_setup ( oledswitch_t *ctx );

/**
 * @brief Software reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function does a software reset of the click module.
 */
void oledswitch_software_reset ( oledswitch_t *ctx );

/**
 * @brief Digital write pwm function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the digital output signal for the PWM pin.
 */
void oledswitch_digital_write_pwm ( oledswitch_t *ctx, uint8_t signal );

/**
 * @brief Digital write reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the digital output signal for the RST pin.
 */
void oledswitch_digital_write_rst ( oledswitch_t *ctx, uint8_t signal );

#ifdef __cplusplus
}
#endif
#endif  // _OLEDSWITCH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
