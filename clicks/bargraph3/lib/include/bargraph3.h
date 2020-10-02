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
 * \brief This file contains API for BARGRAPH 3 Click driver.
 *
 * \addtogroup bargraph3 BARGRAPH 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BARGRAPH3_H
#define BARGRAPH3_H

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

#define BARGRAPH3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.oe = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BARGRAPH3_RETVAL  uint8_t

#define BARGRAPH3_OK           0x00
#define BARGRAPH3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup display Display
 * \{
 */
#define BARGRAPH3_LED_0  0
#define BARGRAPH3_LED_1  1
#define BARGRAPH3_LED_2  2
#define BARGRAPH3_LED_3  3
#define BARGRAPH3_LED_4  4
#define BARGRAPH3_LED_5  5
/** \} */

/**
 * \defgroup control_led Control led
 * \{
 */
#define BARGRAPH3_INCREASE_LED     1
#define BARGRAPH3_CONTROL_ONE_LED  0
/** \} */

/**
 * \defgroup direction Direction
 * \{
 */
#define BARGRAPH3_DIRECTION_TOP_TO_BOTTOM  1
#define BARGRAPH3_DIRECTION_BOTTOM_TO_TOP  0
/** \} */

/**
 * \defgroup enable Enable
 * \{
 */
#define BARGRAPH3_DEVICE_ENABLE  0
#define BARGRAPH3_DEVICE_DISABLE 1
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

    digital_out_t oe;
    digital_out_t rst;
    digital_out_t pwm;
   
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} bargraph3_t;

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

    pin_name_t oe;
    pin_name_t rst;
    pin_name_t pwm;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} bargraph3_cfg_t;

/** \} */ // End types groupS
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
void bargraph3_cfg_setup ( bargraph3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BARGRAPH3_RETVAL bargraph3_init ( bargraph3_t *ctx, bargraph3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for BARGRAPH 3 click.
 */
void bargraph3_default_cfg ( bargraph3_t *ctx );

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
void bargraph3_generic_transfer ( bargraph3_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Functions for enable the chip.
 *
 * @param ctx          Click object.
 * @param state        State.
 *
 * @description This function enable the chip.
 */void bargraph3_enable ( bargraph3_t *ctx, uint8_t state );

/**
 * @brief Functions for reset the chip.
 *
 * @param ctx          Click object.
 *
 * @description This function reset the chip.
 */void bargraph3_reset ( bargraph3_t *ctx );

 /**
 * @brief Functions for set PWM.
 *
 * @param ctx          Click object.
 * @param state        State.
 *
 * @description This function set PWM.
 */void bargraph3_set_pwm ( bargraph3_t *ctx, uint8_t state );

 /**
 * @brief Displays function.
 *
 * @param ctx          Click object.
 * @param ctrl         Led control ( INCREASE_LED or CONTROL_ONE_LED ).
 * @param dir          Display direction ( TOP_TO_BOTTOM or BOTTOM_TO_TOP ).
 * @param counter      BarGraph display counter ( 0..5 ).
 *
 * @description This function control the displey.
 */void bargraph3_display ( bargraph3_t *ctx, uint8_t ctrl, uint8_t dir, uint8_t counter);

#ifdef __cplusplus
}
#endif
#endif  // _BARGRAPH3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
