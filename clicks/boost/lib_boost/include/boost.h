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
 * \brief This file contains API for BOOST Click driver.
 *
 * \addtogroup boost BOOST Click Driver
 * \{
 */
// ----------------------------------------------------------------------------

#ifndef BOOST_H
#define BOOST_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define BOOST_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs1  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.cs2  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.en   = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BOOST_OK       0
#define BOOST_ERROR  (-1)
/** \} */

/**
 * \defgroup boost_config    Boost configuration
 * \{
 */
#define BOOST_CFG_VREF_BUFFERED         1
#define BOOST_CFG_VREF_UNBUFFERED       0

#define BOOST_CFG_GAIN_1X               1
#define BOOST_CFG_GAIN_2X               0

#define BOOST_CFG_POWER_OUT_ON          1
#define BOOST_CFG_POWER_OUT_OFF         0
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click DAC configuration structure definition.
 */
typedef struct
{
    uint8_t buf;
    uint8_t ga;
    uint8_t shdn;

} boost_dac_cfg_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t cs1;
    digital_out_t cs2;
    digital_out_t en;

    digital_in_t miso;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select1;
    pin_name_t chip_select2;
    spi_master_chip_select_polarity_t cs1_polarity;
    spi_master_chip_select_polarity_t cs2_polarity;

    boost_dac_cfg_t dac;

} boost_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs1;
    pin_name_t cs2;

    // Additional gpio pins 

    pin_name_t en;

    // Static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs1_polarity;
    spi_master_chip_select_polarity_t cs2_polarity;

    boost_dac_cfg_t dac;

} boost_cfg_t;

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
void boost_cfg_setup ( boost_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t boost_init ( boost_t *ctx, boost_cfg_t *cfg );

/**
 * @brief Device Enable function.
 *
 * @param ctx  Click object.
 *
 * @description This function puts the device to power ON state.
 */
void boost_device_enable ( boost_t *ctx );

/**
 * @brief Device Disable function.
 *
 * @param ctx  Click object.
 *
 * @description This function puts the device to power OFF state.
 */
void boost_device_disable ( boost_t *ctx );

/**
 * @brief DAC Setup function.
 *
 * @param ctx  Click object.
 * @param cfg  DAC configuration structure.
 *
 * @description This function performs the setup of the DAC converter of the Boost click.
 */
void boost_dac_setup ( boost_t *ctx, boost_dac_cfg_t *cfg );

/**
 * @brief DAC Write function.
 *
 * @param ctx  Click object.
 * @param dac_val  DAC writing value [12-bit].
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function sets the DAC converter to the selected value and allows the output
 * voltage changing.
 */
err_t boost_dac_write ( boost_t *ctx, uint16_t dac_val );

/**
 * @brief VOUT Read function.
 *
 * @param ctx  Click object.
 * @return Output voltage level [V].
 *
 * @description This function reads the output voltage level.
 */
float boost_vout_read ( boost_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // BOOST_H

/** \} */ // End public_function group
/** \} */ // End click Driver group

// ------------------------------------------------------------------------ END
