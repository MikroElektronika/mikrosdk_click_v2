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
 * \brief This file contains API for Bargraph 2 Click driver.
 *
 * \addtogroup bargraph2 Bargraph 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BARGRAPH2_H
#define BARGRAPH2_H

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

#define BARGRAPH2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.mr    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pwm   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BARGRAPH2_RETVAL  uint8_t

#define BARGRAPH2_OK           0x00
#define BARGRAPH2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup led_power Led Power control
 * \{
 */
#define BARGRAPH2_POWER_ON    1
#define BARGRAPH2_POWER_OFF   0
/** \} */

/**
 * \defgroup led_segment LED Segment
 * \{
 */
#define BARGRAPH2_LED_SEG_0   0x00
#define BARGRAPH2_LED_SEG_1   0x01
#define BARGRAPH2_LED_SEG_2   0x02
#define BARGRAPH2_LED_SEG_3   0x04
#define BARGRAPH2_LED_SEG_4   0x08
#define BARGRAPH2_LED_SEG_5   0x10
#define BARGRAPH2_LED_SEG_6   0x20
#define BARGRAPH2_LED_SEG_7   0x40
#define BARGRAPH2_LED_SEG_8   0x80
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

    digital_out_t mr;
    digital_out_t pwm;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} bargraph2_t;

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

    pin_name_t mr;
    pin_name_t pwm;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} bargraph2_cfg_t;

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
void bargraph2_cfg_setup ( bargraph2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BARGRAPH2_RETVAL bargraph2_init ( bargraph2_t *ctx, bargraph2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Bargraph 2 click.
 */
void bargraph2_default_cfg ( bargraph2_t *ctx );

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
void bargraph2_generic_transfer ( bargraph2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function does a reset of the click module.
 */
void bargraph2_reset ( bargraph2_t *ctx ); 

/**
 * @brief Write byte function.
 *
 * @param ctx          Click object.
 * @param input_data   Input data variable.
 *
 * @description This function writes one byte of data.
 */
void bargraph2_write_byte ( bargraph2_t *ctx, uint8_t input_data ); 

/**
 * @brief LED green function.
 *
 * @param ctx          Click object.
 * @param index        Index variable.
 * 
 * @note LED register layout: (24th bit) 3 [MSB, LSB], 2 [MSB, LSB], 1 [MSB, LSB] (1st bit)
 *       Green LEDs: From 1 to 10. (REG_1: 8, REG_2: 2) 
 * 
 * @description This function turns on the green LED diode of the chosen segment.
 */
void bargraph2_led_green ( bargraph2_t *ctx, uint8_t index );

/**
 * @brief LED red function.
 *
 * @param ctx          Click object.
 * @param index        Index variable.
 *
 * @note LED register layout: (24th bit) 3 [MSB, LSB], 2 [MSB, LSB], 1 [MSB, LSB] (1st bit)
 *       Red LEDs: From 11 to 20. (REG_2: 6, REG_3: 4)
 * 
 * @description This function turns on the red LED diode of the chosen segment.
 */
void bargraph2_led_red ( bargraph2_t *ctx, uint8_t index );

/**
 * @brief LED yellow function.
 *
 * @param ctx          Click object.
 * @param index        Index variable.
 *
 * @note LED register layout: (24th bit) 3 [MSB, LSB], 2 [MSB, LSB], 1 [MSB, LSB] (1st bit)
 * 
 * @description This function turns on the green & red (yellow light) LED diode
 *              of the chosen segment.
 */
void bargraph2_led_yellow ( bargraph2_t *ctx, uint8_t index );

/**
 * @brief LEDs green function.
 *
 * @param ctx          Click object.
 * @param start_index  Index variable.
 * @param end_index    End variable.
 * 
 * @description This function turns on green LED diodes from the starting index
 *              to the end index.
 */
void bargraph2_leds_green ( bargraph2_t *ctx, int start_index, int end_index ); 

/**
 * @brief LEDs red function.
 *
 * @param ctx          Click object.
 * @param start_index  Index variable.
 * @param end_index    End variable.
 * 
 * @description This function turns on red LED diodes from the starting index
 *              to the end index.
 */
void bargraph2_leds_red ( bargraph2_t *ctx, int start_index, int end_index ); 

/**
 * @brief LEDs red function.
 *
 * @param ctx          Click object.
 * @param start_index  Index variable.
 * @param end_index    End variable.
 * 
 * @description This function turns on green & red (yellow light) LED diodes from
 *              the starting index to the end index.
 */
void bargraph2_leds_yellow ( bargraph2_t *ctx, int start_index, int end_index );

/**
 * @brief Lights out function.
 *
 * @param ctx          Click object.
 * 
 * @description This function turns off all the LED diodes.
 */
void bargraph2_lights_out ( bargraph2_t *ctx ); 

/**
 * @brief Lights out function.
 *
 * @param ctx          Click object.
 * @param power_on_of  Power state ON/OFF
 * 
 * @description This function turns off all the LED diodes.
 */
void barpgraph2_power ( bargraph2_t *ctx, uint8_t power_on_off );

#ifdef __cplusplus
}
#endif
#endif  // _BARGRAPH2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
