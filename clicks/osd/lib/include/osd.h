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
 * \brief This file contains API for OSD Click driver.
 *
 * \addtogroup osd OSD Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OSD_H
#define OSD_H

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

#define OSD_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OSD_RETVAL  uint8_t

#define OSD_OK           0x00
#define OSD_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup reg_addr Register Addresses
 * \{
 */
#define OSD_VM0_REG                                 0x00
#define OSD_VM1_REG                                 0x01
#define OSD_HOS_REG                                 0x02
#define OSD_VOS_REG                                 0x03
#define OSD_DMM_REG                                 0x04
#define OSD_DMAH_REG                                0x05
#define OSD_DMAL_REG                                0x06
#define OSD_DMDI_REG                                0x07
#define OSD_CMM_REG                                 0x08
#define OSD_CMAH_REG                                0x09
#define OSD_RB0_REG                                 0x10
#define OSD_CMAL_REG                                0x0A
#define OSD_CMDI_REG                                0x0B
#define OSD_OSDM_REG                                0x0C
#define OSD_OSDBL_REG                               0x6C
#define OSD_STAT_REG                                0xA0
#define OSD_DMDO_REG                                0xB0
#define OSD_CMDO_REG                                0xC0
/** \} */

/**
 * \defgroup command Commands
 * \{
 */
#define OSD_WRITE_CMD            0x7F
#define OSD_READ_CMD             0x80

#define OSD_CLEAR_DISPLAY        0x04
#define OSD_CLEAR_DISPLAY_VERT   0x06
#define OSD_END_STRING           0xFF
#define OSD_WRITE_NVR            0xA0

#define OSD_WHITE_LEVEL_80       0x03
#define OSD_WHITE_LEVEL_90       0x02
#define OSD_WHITE_LEVEL_100      0x01
#define OSD_WHITE_LEVEL_120      0x00

#define OSD_MAX_FONT_ROM         0xFF
#define OSD_STATUS_REG_NVR_BUSY  0x20
#define OSD_NVM_RAM_SIZE         0x36
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
    digital_out_t cs;

    // Input pins 

    digital_in_t an;
    digital_in_t pwm;
    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} osd_t;

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

    pin_name_t an;
    pin_name_t rst;
    pin_name_t pwm;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} osd_cfg_t;

/**
 * @brief Structure for osd_write_chars() call
 */
typedef struct 
{

uint8_t n_byte;    // number of bytes
uint8_t flags;     // flags: 1 <==> blink; 2 <==> invert 
uint8_t line_pos;  // line position value
uint8_t row_pos;   // row position value

} osd_write_chars_t;

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
void osd_cfg_setup ( osd_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param osd Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OSD_RETVAL osd_init  ( osd_t *ctx, osd_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for OSD click.
 */
void osd_default_cfg  ( osd_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void osd_generic_transfer 
( 
    osd_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Write the byte of data
 *
 * @param ctx                        Click object.
 * @param reg_address                8-bit register address
 * @param write_data                 Byte of data to write
 *
 * @description This function writes the byte of data to the
 * targeted 8-bit register address of MAX7456 single-channel
 * monochrome OSD with integrated EEPROM memory on OSD 
 * click board.
 */
void osd_write_byte  ( osd_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Read the byte of data function
 *
 * @param ctx                        Click object.
 * @param reg_address                8-bit register address
 *
 * @returns  8-bit read data
 *
 * @description This function rides 8-bit of data from the
 * targeted 8-bit register address.
 */
uint8_t osd_read_byte ( osd_t *ctx, uint8_t reg_address );

/**
 * @brief Hardware reset function
 *
 * @param ctx                        Click object.
 * @description This function Hardware reset - resets the MAX7456
 * single-channel monochrome OSD with integrated EEPROM memor
 * by cleared to '0' RST state pin, wait for 10 ms,
 * set to '1' RST state pin and wait for another 10 ms.
 *
 * @note
 * <pre>
 * Delay is 20 ms.
 * </pre>
 */
void osd_hw_reset ( osd_t *ctx );

/**
 * @brief Enable OSD function
 *
 * @param ctx                        Click object.
 *
 * @description This function enables OSD by set to '1' [ bit 3 ]
 * states to the targeted OSD_VM0_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 */
void osd_enable ( osd_t *ctx );

/**
 * @brief Disable OSD function
 *
 * @param ctx                        Click object.
 *
 * @description This function disables OSD by clear to '0' [ bit 3 ]
 * states to the targeted OSD_VM0_REG register address.
 */
void osd_disable ( osd_t *ctx );

/**
 * @brief Write character by position function
 *
 * @param ctx                        Click object.
 * @param line_pos                   8-bit value of line position
 * @param row_pos                    8-bit value of row position
 * @param symbol                     8-bit value of character
 *
 * @description This function writes character by position to the
 * targeted register address of MAX7456 single-channel monochrome
 * OSD with integrated EEPROM memory on OSD click board.
 */
void osd_write_character ( osd_t *ctx, uint8_t line_pos, uint8_t row_pos, uint8_t symbol );

/**
 * @brief Write custom character function
 *
 * @param ctx                        Click object.
 * @param chr_address                8-bit character register address
 * @param custom_char                8-bit value of character
 *
 * @description This function writes custom character by
 * position to the targeted register address of MAX7456 single-channel
 * monochrome OSD with integrated EEPROM memory on OSD click board.
 */
void osd_insert_custom_char ( osd_t *ctx, uint8_t chr_address, uint8_t custom_char );

/**
 * @brief Clears the character places function
 *
 * @param ctx                        Click object.
 * @param start_line_pos             initial line position value
 * @param start_row_pos              initial row position value
 * @param end_line_pos               last line position value
 * @param end_row_pos                last row position value
 *
 * @description The function clears the character by position to the
 * targeted register address of MAX7456 single-channel monochrome
 * OSD with integrated EEPROM memory on OSD click board.
 */
void osd_clears_char_places ( osd_t *ctx, uint8_t start_x, uint8_t start_y, uint8_t end_x,
                             uint8_t end_y );

/**
 * @brief Set NTSC video standard function
 *
 * @param ctx                        Click object.
 *
 * @description This function sets NTSC video standard by clear
 * to '0' [ bit 6 ] states to the targeted OSD_VM0_REG register
 * address of MAX7456 single-channel monochrome OSD with integrated
 * EEPROM memory on OSD click board.
 */                             
void osd_set_ntsc ( osd_t *ctx );

/**
 * @brief Set PAL video standard function
 *
 * @param ctx                        Click object.
 *
 * @description This function sets PAL video standard by set to '1'
 * [ bit 6 ] states to the targeted OSD_VM0_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 */
void osd_set_pal ( osd_t *ctx );


/**
 * @brief Set video sync mode function
 *
 * @param ctx                        Click object.
 * @param sync_mode                  Sync Mode to be set.
 *
 * @description This function sets the video sync mode: autosync, external
 * or internal by write sync_mode value to the targeted OSD_VM0_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 * @note
 * <pre>
 * sync mode values:
 * - 0 : Autosync select (external sync when LOS = 0 and internal sync when LOS = 1);
 * - 1 : External;
 * - 2 : Internal;
 * </pre>
 */
void osd_set_video_sync_mode ( osd_t *ctx, uint8_t sync_mode );

/**
 * @brief Enable display of OSD image function
 *
 * @param ctx                       Click object.
 *
 * @description This function enables display of OSD image by set to '1' [ bit 3 ] states to the
 * targeted _OSD_VM0_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 */
void osd_enable_display_image ( osd_t *ctx );

/**
 * @brief Disable display of OSD image function
 *
 * @param ctx                       Click object.
 *
 * @description This function disables display of OSD image by clear to '0'
 * [ bit 3 ] states to the targeted OSD_VM0_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 */
void osd_disable_display_image ( osd_t *ctx );

/**
 * @brief Enable vertical synchronization of on-screen data function
 *
 * @param ctx                       Click object.
 * @param vsync                     vsync options
 *
 * @description This function enables vertical synchronization of on-screen
 * data by write vsync value to the targeted OSD_VM0_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 *
 * @note
 * <pre>
 * vsync values:
 * - 0 : Enable on-screen display immediately;
 * - 1 : Enable on-screen display at the next VSYNC;
 * </pre>
 */
void osd_vertical_sync_screen ( osd_t *ctx, uint8_t vsync );

/**
 * @brief Software reset function
 *
 * @param ctx                       Click object.
 *
 * @description This function performs software reset OSD click by set
 * to '1' [ bit 1 ] states to the to the targeted OSD_VM0_REG register
 * address of MAX7456 single-channel monochrome OSD with integrated
 * EEPROM memory.
 *
 * @note
 * <pre>
 * This bit is automatically cleared to '0' by hardware.
 * Delay is 1 ms.
 * </pre>
 */
void osd_soft_reset ( osd_t *ctx );

/**
 * @brief Enable video buffer
 *
 * @param ctx                       Click object.
 *
 * @description This function enables video buffer by clear to '0'
 * [ bit 0 ] states to the targeted OSD_VM0_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 */
void osd_enable_video_buffer ( osd_t *ctx );

/**
 * @brief Disable video buffer
 *
 * @param ctx                       Click object.
 *
 * @description This function disables video buffer by set to '1'
 * [ bit 0 ] states to the targeted OSD_VM0_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 */
void osd_disable_video_buffer ( osd_t *ctx );

/**
 * @brief Set background mode
 *
 * @param ctx                       Click object.
 * @param b_mode
 *
 * @description This function sets background mode.
 *
 * @note
 * <pre>
 * In internal sync mode, the background mode bit is set to '1'.
 * b_mode values:
 * - 0 : Sets the state of each character background;
 * - 1 : Sets all displayed background pixels to gray;
 * </pre>
 */
void osd_set_background_mode ( osd_t *ctx, uint8_t b_mode );

/**
 * @brief Set background brightness function
 *
 * @param ctx                       Click object.
 * @param brightness
 *
 * @description This function sets background brightness.
 * @note
 * <pre>
 * Background Mode Brightness:
 * - 0 : 0%;
 * - 1 : 7%;
 * - 2 : 14%;
 * - 3 : 21%;
 * - 4 : 28%;
 * - 5 : 35%;
 * - 6 : 42%;
 * - 7 : 49%;
 * </pre>
 */
void osd_set_background_brightness ( osd_t *ctx, uint8_t brightness );

/**
 * @brief Set blinking time
 *
 * @param ctx                       Click object.
 * @param blinking_time             Blinking time to be set
 *
 * @description This function sets blinking time of the click.
 *
 * @note
 * <pre>
 * Blinking Time:
 * - 0 : 2 fields ( 33 ms in NTSC mode, 40 ms in PAL mode );
 * - 1 : 4 fields ( 67 ms in NTSC mode, 80 ms in PAL mode );
 * - 2 : 6 fields ( 100 ms in NTSC mode, 120 ms in PAL mode );
 * - 3 : 8 fields ( 133 ms in NTSC mode, 160 ms in PAL mode );
 * </pre>
 */
void osd_set_blinking_time ( osd_t *ctx, uint8_t blinking_time );

/**
 * @brief Set blinking duty cycle function
 *
 * @param ctx                       Click object.
 * @param blink_duty_cycle
 *
 * @description This function sets blinking duty cycle by write
 * blink_duty_cycle value to the targeted OSD_VM1_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 * @note
 * <pre>
 * Blinking Duty Cycle ( On : Off ):
 * - 0 : Blinking Time : Blinking Time;
 * - 1 : Blinking Time : ( 2 x Blinking Time );
 * - 2 : Blinking Time : ( 3 x Blinking Time );
 * - 3 : ( 3 x Blinking Time ) : Blinking Time;
 * </pre>
 */
void osd_set_blinking_duty_cycle ( osd_t *ctx, uint8_t blink_duty_cycle );

/**
 * @brief Set horizontal offset function
 *
 * @param ctx                       Click object.
 * @param h_offset                  Horisontal possition offset
 *
 * @description This function sets horizontal offset.
 *
 * @note
 * <pre>
 * Horizontal Position Offset:
 * -  0 : Farthest left ( -32 pixels );
 * - .
 * - .
 * - .
 * - 32 : No horizontal offset;
 * - .
 * - .
 * - .
 * - 63 :  Farthest right ( +31 pixels );
 * </pre>
 */
void osd_set_horizontal_offset ( osd_t *ctx, uint8_t h_offset );

/**
 * @brief Set vertical offset function
 *
 * @param ctx                       Click object.
 * @param v_offset                  Vertical possition offset
 *
 * @description This function sets horizontal offset
 *
 * @note
 * <pre>
 * Vertical Position Offset:
 * -  0 : Farthest up ( +16 pixels );
 * - .
 * - .
 * - .
 * - 16 : No vertical offset;
 * - .
 * - .
 * - .
 * - 31 : Farthest down ( -15 pixels );
 * </pre>
 */
void osd_set_vertical_offset ( osd_t *ctx, uint8_t v_offset );

/**
 * @brief Set operation mode function
 *
 * @param ctx                       Click object.
 * @param op_mode                   Operation mode to be set.
 *
 * @description This function sets operation mode.
 *
 * @note
 * <pre>
 * Operation Mode Selection:
 * - 0 : 16-bit operation mode;
 *     - The 16-bit operation mode increases the speed at which the display memory can be updated;
 * - 1 : 8-bit operation mode:
 *     - The 8-bit operation mode provides maximum flexibility when writing characters to the display memory;
 * </pre>
 */
void osd_set_operation_mode ( osd_t *ctx, uint8_t op_mode );

/**
 * @brief Set local background control function
 *
 * @param ctx                       Click object
 * @param lb_mode                   Local background control to be set
 *
 * @description This function sets local background control.
 *
 * @note
 * <pre>
 * Local Background Control:
 * - 0 : Sets the background pixels of the character to the video input (VIN) when in external sync mode;
 * - 1 : Sets the background pixels of the character to the background mode brightness level defined status ( external or internal sync mode );
 * </pre>
 */
void osd_set_local_background_control ( osd_t *ctx, uint8_t lb_mode );

/**
 * @brief Set blinking ON function
 *
 * @param ctx                       Click object
 *
 * @description This function set blinking ON  by set to '1' [ bit 4 ] states to the
 * targeted OSD_DMM_REG register address of MAX7456 single-channel monochrome OSD
 * with integrated EEPROM memory on OSD click board.
 */
void osd_blinking_on ( osd_t *ctx );

/**
 * @brief Set blinking OFF function
 *
 * @param ctx                       Click object
 *
 * @description This function sets blinking OFF by clear to '0' [ bit 4 ]
 * states to the targeted OSD_DMM_REG register address of MAX7456
 * single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 */
void osd_blinking_off ( osd_t *ctx );

/**
 * @brief Invert color of pixels on display function
 *
 * @param ctx                       Click object
 *
 * @description This function inverts color of pixels on display.
 */
void osd_invert_pixels_display ( osd_t *ctx );

/**
 * @brief Normal color of pixels on display function
 *
 * @param ctx                       Click object
 *
 * @description This function normal color of pixels on display.
 */
void osd_normal_pixels_display ( osd_t *ctx );

/**
 * @brief Clear display memory
 *
 * @param ctx                       Click object
 *
 * @description This function clears display memory.
 *
 * @note
 * <pre>
 * This bit is automatically cleared after the operation is completed.
 * This operation is automatically performed:
 * - 1) On power-up;
 * - 2) Immediately following the rising edge of RESET;
 * - 3) Immediately following the rising edge of CS;
 * Delay is 1 ms.
 * </pre>
 */
void osd_clear_display_memory ( osd_t *ctx );

/**
 * @brief Write character function
 *
 * @param ctx                      Click object
 * @param symbol_buff              Pointer to the memory location of symbolBuff
 * @param write_ctx                Write context structure for this function
 *
 * @description This function writes array of character by position
 * to the targeted register address of MAX7456 single-channel
 * monochrome OSD with integrated EEPROM memory on OSD click board.
 *
 * @note
 * <pre>
 * write_ctx->flags values:
 * 1 : blink;
 * 2 : invert;
 * </pre>
 */
void osd_write_chars ( osd_t *ctx, uint8_t *symbol_buff, osd_write_chars_t *write_ctx );

/**
 * @brief Write NVM character function
 *
 * @param ctx                      Click object
 * @param v_chars                  8-bit character value
 * @param v_index                  8-bit index value
 *
 * @description This function writes NVM character to the targeted
 * register address of MAX7456 single-channel monochrome OSD with
 * integrated EEPROM memory on OSD click board.
 */
void osd_write_nvm_character ( osd_t *ctx, uint8_t v_chars, uint16_t v_index );

/**
 * @brief Set the white background of the character function
 *
 * @param ctx                       Click object.
 *
 * @description This function sets the white background of the character
 */
void osd_set_character_color_white ( osd_t *ctx );

/**
 * @brief Set the black background of the character function
 *
 * @param ctx                       Click object.
 *
 * @description This function sets the black background of the character
 */
void osd_set_character_color_black ( osd_t *ctx );

/**
 * @brief Set blinking ON function
 *
 * @param ctx                       Click object.
 *
 * @description This function sets blinking ON by set to '1' [ bit 6 ]
 * states to the targeted OSD_DMDI_REG register address of
 * MAX7456 single-channel monochrome OSD with integrated EEPROM memory
 * on OSD click board.
 */
void osd_character_blinking_on ( osd_t *ctx );

/**
 * @brief Set blinking OFF function
 *
 * @param ctx                       Click object.
 *
 * @description This function sets blinking OFF.
 */
void osd_character_blinking_off ( osd_t *ctx );

/**
 * @brief Invert color of character pixels on display
 *
 * @param ctx                       Click object.
 *
 * @description This function sets invert color of character pixels on display.
 */
void osd_invert_pixels_character ( osd_t *ctx );

/**
 * @brief Normal color of character pixels on display
 *
 * @param ctx                       Click object.
 *
 * @description This function sets normal color of character pixels on display.
 */
void osd_normal_pixels_character ( osd_t *ctx );

/**
 * @brief Set sharpness function
 *
 * @param ctx                       Click object.
 * @param s_data                    Data to be written to OSD_OSDM_REG register 
 *
 * @description This function sets sharpness by write s_data value
 * to the targeted OSD_OSDM_REG register address of MAX7456
 * single-channel monochrome OSD with integrated EEPROM memory on 
 * OSD click board.
 *
 * @note
 * <pre>
 * OSD Rise and Fall Time : OSD Insertion Mux Switching Time
 * - 0 :  20 ns and  30 ns;
 * - 1 :  30 ns and  35 ns;
 * - 2 :  35 ns and  50 ns;
 * - 3 :  60 ns and  75 ns;
 * - 4 :  80 ns and 100 ns;
 * - 5 : 110 ns and 120 ns;
 * </pre>
 */
void osd_set_sharpness ( osd_t *ctx, uint8_t s_data );

/**
 * @brief Enable automatic OSD black function
 *
 * @param ctx                       Click object.
 *
 * @description This function enables automatic OSD black.
 */
void osd_enable_auto_black ( osd_t *ctx );

/**
 * @brief Disable automatic OSD black function
 *
 * @param ctx                       Click object.
 *
 * @description This function disables automatic OSD black by set
 * to '1' [ bit 4 ] states to the targeted OSD_OSDBL_REG register
 * address of MAX7456 single-channel monochrome OSD with integrated
 * EEPROM memory on OSD click board.
 */
void osd_disable_auto_black ( osd_t *ctx );

/**
 * @brief Get status data function
 *
 * @param ctx                       Click object.
 *
 * @returns Status data
 *
 * @description This function gets status data by read from the
 * targeted OSD_STAT_REG register address of MAX7456 single-channel
 * monochrome OSD with integrated EEPROM memory on OSD click board.
 * @note
 * <pre>
 * Status data:
 * - [ bit 7 ] : Don't Care;
 * - [ bit 6 ] : Reset Mode:
 *             - 0 : Clear when power-up reset mode is complete;
 *             - 1 : Set when in power-up reset mode;
 * - [ bit 5 ] : Character Memory Status:
 *             - 0 : Available to be written to or read from;
 *             - 1 : Unavailable to be written to or read from;
 * - [ bit 4 ] : VSYNC Output Level:
 *             - 0 : Active during vertical sync time;
 *             - 1 : Inactive otherwise;
 * - [ bit 3 ] : HSYNC Output Level:
 *             - 0 : Active during horizontal sync time;
 *             - 1 : Inactive otherwise;
 * - [ bit 2 ] : Loss-of-Sync ( LOS ):
 *             - 0 : Sync Active. Asserted after 32 consecutive input video lines;
 *             - 1 : No Sync. Asserted after 32 consecutive missing input video lines;
 * - [ bit 1 ] : NTSC:
 *            - 0 : NTSC signal is not detected at VIN;
 *             - 1 : NTSC signal is detected at VIN;
 * - [ bit 0 ] : PAL:
 *             - 0 : PAL signal is not detected at VIN;
 *             - 1 : PAL signal is detected at VIN;
 * </pre>
 */
uint8_t osd_get_status ( osd_t *ctx );

/**
 * @brief Get display memory data out function
 *
 * @param ctx                       Click object.
 *
 * @returns Status data
 *
 * @description This function gets display memory data out by read from the
 * targeted OSD_DMDO_REG register address of MAX7456 single-channel
 * monochrome OSD with integrated EEPROM memory on OSD click board.
 * @note
 * <pre>
 * status data:
 * - [ bit 7 ] : Local Background Control:
 *             - 0 : Sets the background pixels of the character to the video input
 *                  (VIN) when in external sync mode;
 *             - 1 : Sets the background pixels of the character to the background
 *                   mode brightness level defined ( external or internal sync mode );
 * - [ bit 6 ] : Blink:
 *             - 0 : Blinking off;
 *             - 1 : Blinking on;
 * - [ bit 5 ] : Invert:
 *             - 0 : Normal ( white pixels display white, black pixels display black );
 *             - 1 : Invert ( white pixels display black, black pixels display white );
 * - [ bit 4:0 ] : Don't Care;
 * </pre>
 */
uint8_t osd_get_display_data_out ( osd_t *ctx );

/**
 * @brief Get character memory data out function
 *
 * @param ctx                       Click object.
 *
 * @returns Status data
 *
 * @description This function gets character memory data out by read from the
 * targeted OSD_CMDO_REG register address of MAX7456 single-channel 
 * monochrome OSD with integrated EEPROM memory on OSD click board.
 *
 * @note
 * <pre>
 * Status data:
 * - [ bit 7:6 ] : Leftmost pixel. 00 = Black, 10 = White, 01 or 11 = Transparent;
 * - [ bit 5:4 ] : Left center pixel. 00 = Black, 10 = White, 01 or 11 = Transparent;
 * - [ bit 3:2 ] : Right center pixel. 00 = Black, 10 = White, 01 or 11 = Transparent:
 * - [ bit 1:0 ] : Rightmost pixel. 00 = Black, 10 = White, 01 or 11 = Transparent;
 * </pre>
 */
uint8_t osd_get_character_data_out ( osd_t *ctx );

/**
 * @brief Get loss of sync status function
 *
 * @param ctx                       Click object.
 *
 * @returns LOS state
 *
 * @description This function gets loss of sync status
 * by return status of AN pin of OSD Click board.
 *
 * @note
 * <pre>
 * LOS state values:
 * - 0 : not active
 * - 1 : active
 * </pre>
 */
uint8_t osd_get_los ( osd_t *ctx );

/**
 * @brief Get vertical sync status function
 *
 * @param ctx                       Click object.
 *
 * @returns VSYNC state
 *
 * @description This function gets vertical sync status
 * by return status of INT pin of OSD Click board.
 *
 * @note
 * <pre>
 * VSYNC state values:
 * - 0 : not active
 * - 1 : active
 * </pre>
 */
uint8_t osd_get_vsync ( osd_t *ctx );

/**
 * @brief Get horizontal sync status function
 *
 * @param ctx                       Click object.
 *
 * @returns HSYNC state
 *
 * @description This function gets horizontal sync status
 * by return status of PWM pin of OSD Click board.
 * 
 * @note
 * <pre>
 * HSYNC state values:
 * - 0 : not active
 * - 1 : active
 * </pre>
 */
uint8_t osd_get_hsync ( osd_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _OSD_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
