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
#define COLOR3_RETVAL  uint8_t

#define COLOR3_OK           0x00
#define COLOR3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR3_COMMAND_TYPE_SPECIAL  (3 << 5)
#define COLOR3_COMMAND_TYPE_AUTOINC  (0b01 << 5)
#define COLOR3_COMMAND_SELECT  (1 << 7)
/** \} */

/**
 * \defgroup I2C_slave_address I2C slave address
 * \{
 */
#define COLOR3_I2C_SLAVE_ADDR                                     0x29
/** \} */

/**
 * \defgroup register_addresses Register addresses
 * \{
 */
#define COLOR3_ENABLE                                             0x00
#define COLOR3_ATIME                                              0x01
#define COLOR3_PTIME                                              0x02
#define COLOR3_WTIME                                              0x03
#define COLOR3_AILTL                                              0x04
#define COLOR3_AILTH                                              0x05
#define COLOR3_AIHTL                                              0x06
#define COLOR3_AIHTH                                              0x07
#define COLOR3_PILTL                                              0x08
#define COLOR3_PILTH                                              0x09
#define COLOR3_PIHTL                                              0x0A
#define COLOR3_PIHTH                                              0x0B
#define COLOR3_PERS                                               0x0C
#define COLOR3_CONFIG                                             0x0D
#define COLOR3_PPCOUNT                                            0x0E
#define COLOR3_CONTROL                                            0x0F
#define COLOR3_ID                                                 0x12
#define COLOR3_STATUS                                             0x13
#define COLOR3_CDATA                                              0x14
#define COLOR3_CDATAH                                             0x15
#define COLOR3_RDATA                                              0x16
#define COLOR3_RDATAH                                             0x17
#define COLOR3_GDATA                                              0x18
#define COLOR3_GDATAH                                             0x19
#define COLOR3_BDATA                                              0x1A
#define COLOR3_BDATAH                                             0x1B
#define COLOR3_PDATA                                              0x1C
#define COLOR3_PDATAH                                             0x1D
/** \} */

/**
 * \defgroup enable_register_values Enable register values
 * \{
 */
#define COLOR3_ENABLE_REG_DEFAULT                                 0x00
#define COLOR3_ENABLE_REG_PON                                     0x01
#define COLOR3_ENABLE_REG_AEN                                     0x02
#define COLOR3_ENABLE_REG_PEN                                     0x04
#define COLOR3_ENABLE_REG_WEN                                     0x08
#define COLOR3_ENABLE_REG_AIEN                                    0x10
#define COLOR3_ENABLE_REG_PIEN                                    0x20
/** \} */

/**
 * \defgroup RGBC_timing_register_values RGBC Timing register values
 * \{
 */
#define  COLOR3_RGBC_TIMING_1_CYC                                  0xFF
#define  COLOR3_RGBC_TIMING_4_CYC                                  0xFC
#define  COLOR3_RGBC_TIMING_10_CYC                                 0xF6
#define  COLOR3_RGBC_TIMING_42_CYC                                 0xD6
#define  COLOR3_RGBC_TIMING_64_CYC                                 0xAD
#define  COLOR3_RGBC_TIMING_256_CYC                                0x00
/** \} */

/**
 * \defgroup proximity_pulse_counter_values Proximity pulse counter values
 * \{
 */
#define COLOR3_PROXY_PULSE_1                                      0xFF
#define COLOR3_PROXY_PULSE_10                                     0xF6
#define COLOR3_PROXY_PULSE_42                                     0xD6
#define COLOR3_PROXY_PULSE_64                                     0xAD
#define COLOR3_PROXY_PULSE_256                                    0x00
/** \} */

/**
 * \defgroup proximity_timing_register_values Proximity Timing register values
 * \{
 */
#define COLOR3_WAIT_TIME_REG_1_CYC                                0xFF
#define COLOR3_WAIT_TIME_REG_40_CYC                               0xD8
#define COLOR3_WAIT_TIME_REG_85_CYC                               0xAB
#define COLOR3_WAIT_TIME_REG_256_CYC                              0x00
/** \} */

/**
 * \defgroup threshold_values Threshold values
 * \{
 */
#define COLOR3_LOW_THRESHOLD_VALUE                               0x0130
#define COLOR3_HIGH_THRESHOLD_VALUE                              0x0170
/** \} */

/**
 * \defgroup persistence_filtering_values Persistence filtering values
 * \{
 */
#define COLOR3_EVERY_CYC_INTER                                    0x00
#define COLOR3_1_OR_INTER                                         0x01
#define COLOR3_2_OR_INTER                                         0x02
#define COLOR3_3_OR_INTER                                         0x03
#define COLOR3_5_OR_INTER                                         0x04
#define COLOR3_10_OR_INTER                                        0x05
#define COLOR3_15_OR_INTER                                        0x06
#define COLOR3_20_OR_INTER                                        0x07
#define COLOR3_25_OR_INTER                                        0x08
#define COLOR3_30_OR_INTER                                        0x09
#define COLOR3_35_OR_INTER                                        0x0A
#define COLOR3_40_OR_INTER                                        0x0B
#define COLOR3_45_OR_INTER                                        0x0C
#define COLOR3_50_OR_INTER                                        0x0D
#define COLOR3_55_OR_INTER                                        0x0E
#define COLOR3_60_OR_INTER                                        0x0F
/** \} */

/**
 * \defgroup long_wait_value Long wait value
 * \{
 */
#define COLOR3_LONG_WAIT                                          0x02
/** \} */

/**
 * \defgroup RGBC_gain_control RGBC Gain Control
 * \{
 */
#define COLOR3_A_GAIN_1                                           0x00
#define COLOR3_A_GAIN_4                                           0x01
#define COLOR3_A_GAIN_16                                          0x02
#define COLOR3_A_GAIN_60                                          0x03
/** \} */

/**
 * \defgroup proximity_diode _select Proximity Diode Select
 * \{
 */
#define COLOR3_CLEAR_DIODE                                        0x10
#define COLOR3_IR_DIODE                                           0x20
#define COLOR3_BOTH_DIODE                                         0x30
/** \} */

/**
 * \defgroup LED_drive_strength LED Drive Strength
 * \{
 */
#define COLOR3_LED_STR_100                                        0x00
#define COLOR3_LED_STR_50                                         0x40
#define COLOR3_LED_STR_25                                         0x80
#define COLOR3_LED_STR_12_5                                       0xC0
/** \} */

/**
 * \defgroup color_flag Color Flag
 * \{
 */
#define  COLOR3_ORANGE_COLOR_FLAG                        1
#define  COLOR3_RED_COLOR_FLAG                              2
#define  COLOR3_PINK_COLOR_FLAG                            3
#define  COLOR3_PURPLE_COLOR_FLAG                         4
#define  COLOR3_BLUE_COLOR_FLAG                            5
#define  COLOR3_CYAN_COLOR_FLAG                           6
#define  COLOR3_GREEN_COLOR_FLAG                         7
#define  COLOR3_YELLOW_COLOR_FLAG                       8
#define  COLOR3_NON_COLOR_FLAG                            0
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint16_t *clear_data;
    uint16_t *red_data;
    uint16_t *green_data;
    uint16_t *blue_data;
} color3_t;

typedef struct
{
  uint16_t *clear_data;
  uint16_t *red_data;
  uint16_t *green_data;
  uint16_t *blue_data;

} color3_const_t;

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

    color3_const_t dev_const;

} color3_cfg_t;

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
void color3_cfg_setup ( color3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param color3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COLOR3_RETVAL color3_init ( color3_t *ctx, color3_cfg_t *cfg );

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
void color3_generic_write ( color3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void color3_generic_read ( color3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Normal write byte function.
 * @param wrAddr       8-bit register address.
 * @param wrData       8-bit data to be written into register.
 *
 * @description  Function writes 2 bytes of data, with normal settings.
 */
void color3_normal_wr_byte ( color3_t *ctx, uint8_t wr_addr, uint8_t wr_data );

/**
 * @brief Special write byte function.
 *
 * 
 * @param ctx          Click object.
 * @param wrAddr       8-bit register address.
 * @param wrData       8-bit data to be written into register.
 *
 * @description Function writes 2 bytes of data, with special settings.
 */
 void color3_special_wr_byte ( color3_t *ctx, uint8_t wr_addr, uint8_t wr_data );

 /**
 * @brief Read byte function.
 *
 * 
 * @param ctx          Click object.
 * @param rd_addr      8-bit register address.
 *
 * @description Function reads single byte of data from specified register.
 */
 uint8_t color3_read_byte ( color3_t *ctx, uint8_t rd_addr );

 /**
 * @brief Normal write data function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_addr      8-bit register address.
 * @param wr_ata       16-bit data to be written into registers.
 *
 * @description Function writes 2 bytes of data, with normal settings.
 */
 void color3_normal_wr_data ( color3_t *ctx, uint8_t wr_addr, uint16_t wr_data );
 
 /**
 * @brief Special write function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_addr      8-bit register address.
 * @param wr_data      16-bit data to be written into registers.
 *
 * @description Function writes 2 bytes of data, with special settings.
 */
 void color3_special_wr_data ( color3_t *ctx, uint8_t wr_addr, uint16_t wr_data );

 /**
 * @brief Read data function.
 *
 * 
 * @param ctx          Click object.
 * @param rd_addr      8-bit register address.
 *
 * @description Function reads 2 bytes of data from specified registers.
 */
 uint16_t color3_read_data ( color3_t *ctx, uint8_t rd_addr );

 /**
 * @brief Write Enable Register function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_data      8-bit data to be written into enable register.
 *
 * @description Function is used to write into enable register.
 */
 void color3_write_enable_register ( color3_t *ctx, uint8_t wr_data );

 /**
 * @brief Read Enable Register function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read from enable register.
 */
 uint8_t color3_read_enable_register ( color3_t *ctx );

 /**
 * @brief Write RGBC Timing Register function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_data      8-bit data to be written into RGBC timing register.
 *
 * @description Function is used to write into RGBC timing register.
 */
 void color3_write_rgbc_timing_register ( color3_t *ctx , uint8_t wr_data );

 /**
 * @brief Read RGBC Timing Register function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description Function is used to read from RGBC timing register..
 */
 uint8_t color3_read_rgbc_timing_register ( color3_t *ctx ); 

 /**
 * @brief Write Proximity Timing Register function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_data  8-bit data to be written into proximity timing register.
 *
 * @description Function is used to write into proximity timing register.
 */
  void color3_write_proxy_timing_register ( color3_t *ctx );

 /**
 * @brief Read Proximity Timing Register function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description Function is used to read from proximity timing register.
 */
  uint8_t color3_read_proxy_timing_register ( color3_t *ctx );

 /**
 * @brief Write Wait Time Register function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_data      8-bit data to be written into wait time register.
 *
 * @description Function is used to write into wait time register.
 */
 void color3_write_wait_time_register ( color3_t *ctx, uint8_t wr_data );

 /**
 * @brief Read Wait Time Register function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read from wait time register.
 */
  uint8_t color3_read_wait_time_register ( color3_t *ctx );

 /**
 * @brief RGBC interrupt threshold low value function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_data      16-bit data to be written into RGBC interrupt threshold low value registers.
 *
 * @description Function is used to set RGBC interrupt threshold low value.
 */
  void color3_set_inter_trsh_lo_val( color3_t *ctx, uint16_t wr_data );

 /**
 * @brief RGBC interrupt threshold high value function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_data      16-bit data to be written into RGBC interrupt threshold high value registers.
 *
 * @description Function is used to set RGBC interrupt threshold high value.
 */
 void color3_set_inter_trsh_hi_val ( color3_t *ctx, uint16_t wr_data );

 /**
 * @brief Proximity interrupt threshold low value function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_data      16-bit data to be written into proximity interrupt threshold low value registers.
 *
 * @description Function is used to set proximity interrupt threshold low value.
 */
  void color3_set_proxy_inter_trsh_lo_val ( color3_t *ctx, uint16_t wr_data );

 /**
 * @brief Proximity interrupt threshold high value function.
 *
 * 
 * @param ctx          Click object.
 * @param wr_data      16-bit data to be written into proximity interrupt threshold high value registers.
 *
 * @description Function is used to set proximity interrupt threshold high value.
 */
  void color3_set_proxy_inter_trsh_hi_val ( color3_t *ctx, uint16_t wr_data );

 /**
 * @brief Set Interrupt persistence persistence function.
 *
 * 
 * @param ctx          Click object.
 * @param int_pers     8-bit data to be written into wait time register.
 *
 * @description Function is used to control the filtering interrupt capabilities of the device.
 */
  void color3_set_interrupt_persistence ( color3_t *ctx, uint8_t int_pers );

 /**
 * @brief Read Interrupt persistence function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to check RGBC interrupt persistence settings.
 */
  uint8_t color3_read_interrupt_persistence ( color3_t *ctx );
 
 /**
 * @brief Set Proximity interrupt persistence function.
 *
 * 
 * @param ctx          Click object.
 * @param int_pers  8-bit data that represents proximity interrupt persistence.
 *
 * @description Function is used to control the filtering interrupt capabilities of the device.
 */
  void color3_setproxy_interrupt_persistence ( color3_t *ctx, uint8_t int_pers );

 /**
 * @brief Read Proximity interrupt persistence function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to check proximity interrupt persistence settings.
 */
  uint8_t color3_read_proxy_interrupt_persistence ( color3_t *ctx );

 /**
 * @brief Set long wait function.
 *
 * 
 * @param ctx          Click object.
 * @param lon_wait     8-bit data that is written into configuration register.
 *
 * @description Function is used to enable or disable long wait by writing into configuration register.
 */
  void color3_setLongWait ( color3_t *ctx, uint8_t lon_wait );

 /**
 * @brief Read long wait function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to check if the long wait is enabled or disabled.
 */
  uint8_t color3_read_long_wait ( color3_t *ctx );

 /**
 * @brief Write Proximity Pulse Count function.
 *
 * 
 * @param ctx          Click object.
 * @param pulse_cnt    8-bit data that is written into proximity pulse count register.
 *
 * @description Function sets the number of proximity pulses that will be transmitted.
 */
  void color3_write_pulse_cnt ( color3_t *ctx, uint8_t pulse_cnt );

 /**
 * @brief Read Proximity Pulse Count function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to check set number of proximity pulses that will be transmitted.
 */
  uint8_t color3_read_pulse_cnt ( color3_t *ctx );

 /**
 * @brief Write RGBC Gain Value function.
 *
 * 
 * @param ctx          Click object.
 * @param gain_val     8-bit data that is written into control register.
 *
 * @description Function is used to set RGBC Gain Value.
 */
  void color3_write_rgbc_gain ( color3_t *ctx, uint8_t gain_val );

 /**
 * @brief Read RGBC Gain Value function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to check RGBC Gain Value.
 */
  uint8_t color3_read_rgbc_gain ( color3_t *ctx );

 /**
 * @brief Set Diode Selection function.
 *
 * 
 * @param ctx          Click object.
 * @param dio_sel      8-bit data that is written into control register.
 *
 * @description Function is used to perform diode selection.
 */
 void color3_set_diode_select ( color3_t *ctx, uint8_t dio_sel );

 /**
 * @brief Get Diode Selection function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to check diode selection.
 */
  uint8_t color3_get_diode_select ( color3_t *ctx ); 

 /**
 * @brief Set LED Strength function.
 *
 * 
 * @param ctx          Click object.
 * @param led_str      8-bit data that is written into control register.
 *
 * @description  Function is used to set LED drive strength.
 */
  void color3_set_led_str ( color3_t *ctx, uint8_t led_str );

 /**
 * @brief Read LED Strength function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to check LED drive strength.
 */
  uint8_t color3_read_led_str ( color3_t *ctx );

 /**
 * @brief Read device ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read the device's unique ID number.
 */
  uint8_t color3_read_dev_id ( color3_t *ctx );

 /**
 * @brief Read device status function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read the contents of device status register.
 */
  uint8_t color3_read_dev_stat ( color3_t *ctx );

 /**
 * @brief Read clear data function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read clear data.
 */
  uint16_t color3_read_clear_data ( color3_t *ctx );

 /**
 * @brief Read red data function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read red data.
 */
  uint16_t color3_read_red_data ( color3_t *ctx );

 /**
 * @brief Read green data function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read green data.
 */
  uint16_t color3_read_green_data ( color3_t *ctx );

 /**
 * @brief Read blue data function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read blue data.
 */
  uint16_t color3_read_blue_data ( color3_t *ctx );

 /**
 * @brief ead proximity data function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to read proximity data.
 */
  uint16_t color3_read_proxy_data( color3_t *ctx );

 /**
 * @brief Get Interrupt state function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to check if an interrupt has occured.
 */
 uint8_t color3_get_inter_state ( color3_t *ctx ); 

 /**
 * @brief Default settings function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to apply default settings.
 */
  void color3_set_default_settings ( color3_t *ctx );

 /**
 * @brief Get color data function.
 *
 * 
 * @param ctx          Click object.
 * @param red_data     16-bit data that represents red data.
 * @param green_data   16-bit data that represents green data.
 * @param blue_data    16-bit data that represents blue data.
 *
 * @description Function is used to read red, green and blue data.
 */
  void color3_get_rgb_data ( color3_t *ctx, uint16_t *red_data, uint16_t *green_data, uint16_t *blue_data );

 /**
 * @brief Get color ratio function.
 *
 * 
 * @param ctx          Click object.
 * @param color_data   16-bit data that represents colorr data.
 *
 * @description This function reads data from the desired register.
 */
  float color3_get_color_ratio ( color3_t *ctx, uint16_t color_data );

 /**
 * @brief Get color value function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description Function is used to calculate HSL color.
 */
  float color3_get_color_value ( color3_t *ctx );

 /**
 * @brief Get CRBG data function.
 *
 * 
 * @param ctx          Click object.
 * @param clear_data   16-bit data that represents clear data.
 * @param red_data     16-bit data that represents red data.
 * @param green_data   16-bit data that represents green data.
 * @param blue_data    16-bit data that represents blue data.
 *
 * @description Function is used to read clear, red, blue and green data values.
 */
  void color3_get_crgb_data ( color3_t *ctx, color3_const_t *data_const );

/**
 * @brief RGB to hsl.
 *
 * 
 * @param ctx          Click object.
 * @param red          16-bit data that red  data.
 * @param green        16-bit data that green data.
 * @param blue         16-bit data that blue data.
 *
 * @description Function is used to translate RGB to hsl.
 */
static float color3_rgb_to_hsl( color3_t *ctx, float red, float green, float blue );

/**
 * @brief Detect color.
 *
 * @param color_value    Color value in HSL.
 *
 * @returns               Color flag.
 *
 * @description This function determines which color is read
 * by click sensor after color3_get_color_value() function has
 * been invoked previously.
 *
 * @note
 * <pre>
 * Detect color
 *    ORANGE color - from 0.992  to 0.999
 *    RED color    - from 0.9750 to 0.9919
 *    PINK color   - from 0.920  to 0.9749
 *    PURPLE color - from 0.6201 to 0.919
 *    BLUE color   - from 0.521  to 0.6200
 *    CYAN color   - from 0.4700 to 0.520
 *    GREEN color  - from 0.210  to 0.469
 *    YELLOW color - from 0.0650 to 0.209
 * </pre>
 */
uint8_t color3_get_color ( float color_value );

#ifdef __cplusplus
}
#endif
#endif  // _COLOR3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
