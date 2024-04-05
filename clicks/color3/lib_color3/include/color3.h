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
 * \brief This file contains API for Color 3 Click driver.
 *
 * \addtogroup color3 Color 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR3_H
#define COLOR3_H

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
#define COLOR3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR3_OK                                   0
#define COLOR3_ERROR                               -1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR3_COMMAND_TYPE_SPECIAL                 ( 3 << 5 )
#define COLOR3_COMMAND_TYPE_AUTOINC                 ( 1 << 5 )
#define COLOR3_COMMAND_SELECT                       ( 1 << 7 )
/** \} */

/**
 * \defgroup I2C_slave_address I2C slave address
 * \{
 */
#define COLOR3_I2C_SLAVE_ADDR                       0x29
/** \} */

/**
 * \defgroup register_addresses Register addresses
 * \{
 */
#define COLOR3_ENABLE                               0x00
#define COLOR3_ATIME                                0x01
#define COLOR3_PTIME                                0x02
#define COLOR3_WTIME                                0x03
#define COLOR3_AILTL                                0x04
#define COLOR3_AILTH                                0x05
#define COLOR3_AIHTL                                0x06
#define COLOR3_AIHTH                                0x07
#define COLOR3_PILTL                                0x08
#define COLOR3_PILTH                                0x09
#define COLOR3_PIHTL                                0x0A
#define COLOR3_PIHTH                                0x0B
#define COLOR3_PERS                                 0x0C
#define COLOR3_CONFIG                               0x0D
#define COLOR3_PPCOUNT                              0x0E
#define COLOR3_CONTROL                              0x0F
#define COLOR3_ID                                   0x12
#define COLOR3_STATUS                               0x13
#define COLOR3_CDATA                                0x14
#define COLOR3_CDATAH                               0x15
#define COLOR3_RDATA                                0x16
#define COLOR3_RDATAH                               0x17
#define COLOR3_GDATA                                0x18
#define COLOR3_GDATAH                               0x19
#define COLOR3_BDATA                                0x1A
#define COLOR3_BDATAH                               0x1B
#define COLOR3_PDATA                                0x1C
#define COLOR3_PDATAH                               0x1D
/** \} */

/**
 * \defgroup enable_register_values Enable register values
 * \{
 */
#define COLOR3_ENABLE_REG_DEFAULT                   0x00
#define COLOR3_ENABLE_REG_PON                       0x01
#define COLOR3_ENABLE_REG_AEN                       0x02
#define COLOR3_ENABLE_REG_PEN                       0x04
#define COLOR3_ENABLE_REG_WEN                       0x08
#define COLOR3_ENABLE_REG_AIEN                      0x10
#define COLOR3_ENABLE_REG_PIEN                      0x20
/** \} */

/**
 * \defgroup RGBC_timing_register_values RGBC Timing register values
 * \{
 */
#define COLOR3_RGBC_TIMING_1_CYC                    0xFF
#define COLOR3_RGBC_TIMING_4_CYC                    0xFC
#define COLOR3_RGBC_TIMING_10_CYC                   0xF6
#define COLOR3_RGBC_TIMING_42_CYC                   0xD6
#define COLOR3_RGBC_TIMING_64_CYC                   0xAD
#define COLOR3_RGBC_TIMING_256_CYC                  0x00
/** \} */

/**
 * \defgroup proximity_pulse_counter_values Proximity pulse counter values
 * \{
 */
#define COLOR3_PROXY_PULSE_1                        0xFF
#define COLOR3_PROXY_PULSE_10                       0xF6
#define COLOR3_PROXY_PULSE_42                       0xD6
#define COLOR3_PROXY_PULSE_64                       0xAD
#define COLOR3_PROXY_PULSE_256                      0x00
/** \} */

/**
 * \defgroup proximity_timing_register_values Proximity Timing register values
 * \{
 */
#define COLOR3_WAIT_TIME_REG_1_CYC                  0xFF
#define COLOR3_WAIT_TIME_REG_42_CYC                 0xD8
#define COLOR3_WAIT_TIME_REG_64_CYC                 0xAD
#define COLOR3_WAIT_TIME_REG_256_CYC                0x00
/** \} */

/**
 * \defgroup threshold_values Threshold values
 * \{
 */
#define COLOR3_LOW_THRESHOLD_VALUE                  0x0130
#define COLOR3_HIGH_THRESHOLD_VALUE                 0x0170
/** \} */

/**
 * \defgroup persistence_filtering_values Persistence filtering values
 * \{
 */
#define COLOR3_EVERY_CYC_INTER                      0x00
#define COLOR3_1_OR_INTER                           0x01
#define COLOR3_2_OR_INTER                           0x02
#define COLOR3_3_OR_INTER                           0x03
#define COLOR3_5_OR_INTER                           0x04
#define COLOR3_10_OR_INTER                          0x05
#define COLOR3_15_OR_INTER                          0x06
#define COLOR3_20_OR_INTER                          0x07
#define COLOR3_25_OR_INTER                          0x08
#define COLOR3_30_OR_INTER                          0x09
#define COLOR3_35_OR_INTER                          0x0A
#define COLOR3_40_OR_INTER                          0x0B
#define COLOR3_45_OR_INTER                          0x0C
#define COLOR3_50_OR_INTER                          0x0D
#define COLOR3_55_OR_INTER                          0x0E
#define COLOR3_60_OR_INTER                          0x0F
/** \} */

/**
 * \defgroup long_wait_value Long wait value
 * \{
 */
#define COLOR3_LONG_WAIT                            0x02
/** \} */

/**
 * \defgroup RGBC_gain_control RGBC Gain Control
 * \{
 */
#define COLOR3_A_GAIN_1                             0x00
#define COLOR3_A_GAIN_4                             0x01
#define COLOR3_A_GAIN_16                            0x02
#define COLOR3_A_GAIN_60                            0x03
/** \} */

/**
 * \defgroup proximity_diode _select Proximity Diode Select
 * \{
 */
#define COLOR3_CLEAR_DIODE                          0x10
#define COLOR3_IR_DIODE                             0x20
#define COLOR3_BOTH_DIODE                           0x30
/** \} */

/**
 * \defgroup LED_drive_strength LED Drive Strength
 * \{
 */
#define COLOR3_LED_STR_100                          0x00
#define COLOR3_LED_STR_50                           0x40
#define COLOR3_LED_STR_25                           0x80
#define COLOR3_LED_STR_12_5                         0xC0
/** \} */

/**
 * @brief Color 3 color flags.
 * @details Specified color flags of Color 3 Click driver.
 */
#define COLOR3_UNKNOWN_COLOR                        0
#define COLOR3_RED_COLOR                            1
#define COLOR3_YELLOW_COLOR                         2
#define COLOR3_GREEN_COLOR                          3
#define COLOR3_CYAN_COLOR                           4
#define COLOR3_BLUE_COLOR                           5
#define COLOR3_MAGENTA_COLOR                        6
#define COLOR3_WHITE_COLOR                          7
#define COLOR3_BLACK_COLOR                          8

/**
 * @brief Color 3 color from HSL thresholds.
 * @details Specified color from HSL thresholds of Color 3 Click driver.
 */
#define COLOR3_WHITE_COLOR_LIGHTNESS                97
#define COLOR3_BLACK_COLOR_LIGHTNESS                3
#define COLOR3_YELLOW_COLOR_HUE_ANGLE               30
#define COLOR3_GREEN_COLOR_HUE_ANGLE                90
#define COLOR3_CYAN_COLOR_HUE_ANGLE                 150
#define COLOR3_BLUE_COLOR_HUE_ANGLE                 210
#define COLOR3_MAGENTA_COLOR_HUE_ANGLE              270
#define COLOR3_RED_COLOR_HUE_ANGLE                  330

/**
 * @brief Color 3 RGB to HSL calculation values.
 * @details Specified RGB to HSL calculation values of Color 3 Click driver.
 */
#define COLOR3_HSL_HUE_RESOLUTION                   360
#define COLOR3_HSL_SATURATION_RESOLUTION            100
#define COLOR3_HSL_LIGHTNESS_RESOLUTION             100

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
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} color3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t int_pin;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} color3_cfg_t;

/**
 * @brief Color 3 RGBC channels data object.
 * @details RGBC channels data object of Color 3 Click driver.
 */
typedef struct
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t clear;

} color3_channels_t;

/**
 * @brief Color 3 HSL color data object.
 * @details HSL color data object of Color 3 Click driver.
 */
typedef struct
{
    float hue;
    float saturation;
    float lightness;

} color3_hsl_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void color3_cfg_setup ( color3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param color3 Click object.
 * @param cfg Click configuration structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t color3_init ( color3_t *ctx, color3_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_in      Data buf to be written.
 * @param len          Number of the bytes in data buf.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function writes data to the desired register.
 */
err_t color3_generic_write ( color3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Generic read function.
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_out     Output data buf
 * @param len          Number of the bytes to be read
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function reads data from the desired register.
 */
err_t color3_generic_read ( color3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Generic read function.
 * @param ctx          Normal write byte function.
 * @param wrAddr       8-bit register address.
 * @param wrData       8-bit data to be written into register.
 *
 * @details  Function writes 2 bytes of data, with normal settings.
 */
void color3_normal_wr_byte ( color3_t *ctx, uint8_t wr_addr, uint8_t wr_data );

/**
* @brief Special write byte function.
* 
* @param ctx          Click object.
* @param wrAddr       8-bit register address.
* @param wrData       8-bit data to be written into register.
*
* @details Function writes 2 bytes of data, with special settings.
*/
void color3_special_wr_byte ( color3_t *ctx, uint8_t wr_addr, uint8_t wr_data );

/**
* @brief Read byte function.
*
* @param ctx          Click object.
* @param rd_addr      8-bit register address.
*
* @details Function reads single byte of data from specified register.
*/
uint8_t color3_read_byte ( color3_t *ctx, uint8_t rd_addr );

/**
* @brief Normal write data function.
*
* @param ctx          Click object.
* @param wr_addr      8-bit register address.
* @param wr_ata       16-bit data to be written into registers.
*
* @details Function writes 2 bytes of data, with normal settings.
*/
void color3_normal_wr_data ( color3_t *ctx, uint8_t wr_addr, uint16_t wr_data );

/**
* @brief Special write function.
*
* @param ctx          Click object.
* @param wr_addr      8-bit register address.
* @param wr_data      16-bit data to be written into registers.
*
* @details Function writes 2 bytes of data, with special settings.
*/
void color3_special_wr_data ( color3_t *ctx, uint8_t wr_addr, uint16_t wr_data );

/**
* @brief Read data function.
* 
* @param ctx          Click object.
* @param rd_addr      8-bit register address.
*
* @details Function reads 2 bytes of data from specified registers.
*/
uint16_t color3_read_data ( color3_t *ctx, uint8_t rd_addr );

/**
* @brief Write Enable Register function.
*
* @param ctx          Click object.
* @param wr_data      8-bit data to be written into enable register.
*
* @details Function is used to write into enable register.
*/
void color3_write_enable_reg ( color3_t *ctx, uint8_t wr_data );

/**
* @brief Read Enable Register function.
*
* @param ctx          Click object.
*
* @details Function is used to read from enable register.
*/
uint8_t color3_read_enable_reg ( color3_t *ctx );

/**
* @brief Write RGBC Timing Register function.
*
* @param ctx          Click object.
* @param wr_data      8-bit data to be written into RGBC timing register.
*
* @details Function is used to write into RGBC timing register.
*/
void color3_write_rgbc_timing_reg ( color3_t *ctx , uint8_t wr_data );

/**
* @brief Read RGBC Timing Register function.
* 
* @param ctx          Click object.
* @param reg          Register address.
* @param data_buf     Output data buf
* @param len          Number of the bytes to be read
*
* @details Function is used to read from RGBC timing register..
*/
uint8_t color3_read_rgbc_timing_reg ( color3_t *ctx ); 

/**
* @brief Write Proximity Timing Register function.
*
* @param ctx          Click object.
* @param wr_data  8-bit data to be written into proximity timing register.
*
* @details Function is used to write into proximity timing register.
*/
void color3_write_prox_timing_reg ( color3_t *ctx );

/**
* @brief Read Proximity Timing Register function.
*
* @param ctx          Click object.
* @param reg          Register address.
* @param data_buf     Output data buf
* @param len          Number of the bytes to be read
*
* @details Function is used to read from proximity timing register.
*/
uint8_t color3_read_prox_timing_reg ( color3_t *ctx );

/**
* @brief Write Wait Time Register function.
* 
* @param ctx          Click object.
* @param wr_data      8-bit data to be written into wait time register.
*
* @details Function is used to write into wait time register.
*/
void color3_write_wait_time_reg ( color3_t *ctx, uint8_t wr_data );

/**
* @brief Read Wait Time Register function.
* 
* @param ctx          Click object.
*
* @details Function is used to read from wait time register.
*/
uint8_t color3_read_wait_time_reg ( color3_t *ctx );

/**
* @brief RGBC interrupt threshold low value function.
*
* @param ctx          Click object.
* @param wr_data      16-bit data to be written into RGBC interrupt threshold low value registers.
*
* @details Function is used to set RGBC interrupt threshold low value.
*/
void color3_set_inter_trsh_lo( color3_t *ctx, uint16_t wr_data );

/**
* @brief RGBC interrupt threshold high value function.
* 
* @param ctx          Click object.
* @param wr_data      16-bit data to be written into RGBC interrupt threshold high value registers.
*
* @details Function is used to set RGBC interrupt threshold high value.
*/
void color3_set_inter_trsh_hi ( color3_t *ctx, uint16_t wr_data );

/**
* @brief Proximity interrupt threshold low value function.
*
* @param ctx          Click object.
* @param wr_data      16-bit data to be written into proximity interrupt threshold low value registers.
*
* @details Function is used to set proximity interrupt threshold low value.
*/
void color3_set_prox_inter_trsh_lo ( color3_t *ctx, uint16_t wr_data );

/**
* @brief Proximity interrupt threshold high value function.
*
* @param ctx          Click object.
* @param wr_data      16-bit data to be written into proximity interrupt threshold high value registers.
*
* @details Function is used to set proximity interrupt threshold high value.
*/
void color3_set_prox_inter_trsh_hi ( color3_t *ctx, uint16_t wr_data );

/**
* @brief Set Interrupt persistence persistence function.
*
* @param ctx          Click object.
* @param int_pers     8-bit data to be written into wait time register.
*
* @details Function is used to control the filtering interrupt capabilities of the device.
*/
void color3_set_int_pers ( color3_t *ctx, uint8_t int_pers );

/**
* @brief Read Interrupt persistence function.
* 
* @param ctx          Click object.
*
* @details Function is used to check RGBC interrupt persistence settings.
*/
uint8_t color3_read_int_pers ( color3_t *ctx );

/**
* @brief Set Proximity interrupt persistence function.
* 
* @param ctx          Click object.
* @param int_pers  8-bit data that represents proximity interrupt persistence.
*
* @details Function is used to control the filtering interrupt capabilities of the device.
*/
void color3_set_prox_int_pers ( color3_t *ctx, uint8_t int_pers );

/**
* @brief Read Proximity interrupt persistence function.
*
* @param ctx          Click object.
*
* @details Function is used to check proximity interrupt persistence settings.
*/
uint8_t color3_read_prox_int_pers ( color3_t *ctx );

/**
* @brief Set long wait function.
*
* @param ctx          Click object.
* @param lon_wait     8-bit data that is written into configuration register.
*
* @details Function is used to enable or disable long wait by writing into configuration register.
*/
void color3_set_long_wait ( color3_t *ctx, uint8_t lon_wait );

/**
* @brief Read long wait function.
* 
* @param ctx          Click object.
*
* @details Function is used to check if the long wait is enabled or disabled.
*/
uint8_t color3_read_long_wait ( color3_t *ctx );

/**
* @brief Write Proximity Pulse Count function.
* 
* @param ctx          Click object.
* @param pulse_cnt    8-bit data that is written into proximity pulse count register.
*
* @details Function sets the number of proximity pulses that will be transmitted.
*/
void color3_write_pulse_cnt ( color3_t *ctx, uint8_t pulse_cnt );

/**
* @brief Read Proximity Pulse Count function.
*
* @param ctx          Click object.
*
* @details Function is used to check set number of proximity pulses that will be transmitted.
*/
uint8_t color3_read_pulse_cnt ( color3_t *ctx );

/**
* @brief Write RGBC Gain Value function.
*
* @param ctx          Click object.
* @param gain     8-bit data that is written into control register.
*
* @details Function is used to set RGBC Gain Value.
*/
void color3_write_rgbc_gain ( color3_t *ctx, uint8_t gain );

/**
* @brief Read RGBC Gain Value function.
* 
* @param ctx          Click object.
*
* @details Function is used to check RGBC Gain Value.
*/
uint8_t color3_read_rgbc_gain ( color3_t *ctx );

/**
* @brief Set Diode Selection function.
*
* @param ctx          Click object.
* @param dio_sel      8-bit data that is written into control register.
*
* @details Function is used to perform diode selection.
*/
void color3_set_diode_select ( color3_t *ctx, uint8_t dio_sel );

/**
* @brief Get Diode Selection function.
*
* @param ctx          Click object.
*
* @details Function is used to check diode selection.
*/
uint8_t color3_get_diode_select ( color3_t *ctx ); 

/**
* @brief Set LED Strength function.
*
* @param ctx          Click object.
* @param led_str      8-bit data that is written into control register.
*
* @details  Function is used to set LED drive strength.
*/
void color3_set_led_str ( color3_t *ctx, uint8_t led_str );

/**
* @brief Read LED Strength function.
* 
* @param ctx          Click object.
*
* @details Function is used to check LED drive strength.
*/
uint8_t color3_read_led_str ( color3_t *ctx );

/**
* @brief Read device ID function.
*
* @param ctx          Click object.
*
* @details Function is used to read the device's unique ID number.
*/
uint8_t color3_read_dev_id ( color3_t *ctx );

/**
* @brief Read device status function.
*
* @param ctx          Click object.
*
* @details Function is used to read the contents of device status register.
*/
uint8_t color3_read_dev_stat ( color3_t *ctx );

/**
* @brief Read clear data function.
* 
* @param ctx          Click object.
*
* @details Function is used to read clear data.
*/
uint16_t color3_read_clear_data ( color3_t *ctx );

/**
* @brief Read red data function.
* 
* @param ctx          Click object.
*
* @details Function is used to read red data.
*/
uint16_t color3_read_red_data ( color3_t *ctx );

/**
* @brief Read green data function.
*
* @param ctx          Click object.
*
* @details Function is used to read green data.
*/
uint16_t color3_read_green_data ( color3_t *ctx );

/**
* @brief Read blue data function.
* 
* @param ctx          Click object.
*
* @details Function is used to read blue data.
*/
uint16_t color3_read_blue_data ( color3_t *ctx );

/**
* @brief ead proximity data function.
*
* @param ctx          Click object.
*
* @details Function is used to read proximity data.
*/
uint16_t color3_read_prox_data( color3_t *ctx );

/**
* @brief Get Interrupt state function.
*
* @param ctx          Click object.
*
* @details Function is used to check if an interrupt has occured.
*/
uint8_t color3_get_inter_state ( color3_t *ctx ); 

/**
* @brief Default settings function.
*
* @param ctx          Click object.
*
* @details Function is used to apply default settings.
*/
void color3_set_default_settings ( color3_t *ctx );

/**
* @brief Get color data function.
*
* @param ctx          Click object.
* @param red_data     16-bit data that represents red data.
* @param green_data   16-bit data that represents green data.
* @param blue_data    16-bit data that represents blue data.
*
* @details Function is used to read red, green and blue data.
*/
void color3_get_rgb_data ( color3_t *ctx, uint16_t *red_data, uint16_t *green_data, uint16_t *blue_data );

/**
* @brief Get color ratio function.
* 
* @param ctx          Click object.
* @param color_data   16-bit data that represents colorr data.
*
* @details This function reads data from the desired register.
*/
float color3_get_color_ratio ( color3_t *ctx, uint16_t color_data );

/**
 * @brief Color 3 get rgbc data function.
 * @details This function reads data from 4 channels (Red, Green, Blue, Clear).
 * @param[in] ctx : Click context object.
 * See #color3_t object definition for detailed explanation.
 * @param[out] channels : Channels output (Red, Green, Blue, Clear).
 * See #color3_channels_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color3_get_rgbc_data ( color3_t *ctx, color3_channels_t *channels );

/**
 * @brief Color 3 get color function.
 * @details This function returns the color name flag from the input HSL color.
 * @param[out] hsl : HSL (hue, saturation, lightness) input value.
 * See #color3_hsl_t object definition for detailed explanation.
 * @return Color name flag.
 * See color flags macro definition for detailed explanation.
 * @note None.
 */
uint8_t color3_get_color ( color3_hsl_t *hsl );

/**
 * @brief Color 3 rgbc to hsl function.
 * @details This function converts RGBC (red, green, blue, clear) to HSL (hue, saturation, lightness) color value.
 * @param[in] ctx : Click context object.
 * See #color3_t object definition for detailed explanation.
 * @param[out] rgbc : RGBC (red, green, blue, clear) input value.
 * See #color3_channels_t object definition for detailed explanation.
 * @param[out] hsl : HSL (hue, saturation, lightness) input value.
 * See #color3_hsl_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void color3_rgbc_to_hsl ( color3_t *ctx, color3_channels_t *rgbc, color3_hsl_t *hsl );

#ifdef __cplusplus
}
#endif
#endif  // _COLOR3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
