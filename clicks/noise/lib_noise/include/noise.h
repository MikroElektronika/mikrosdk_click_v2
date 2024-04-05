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
 * \brief This file contains API for Noise Click driver.
 *
 * \addtogroup noise Noise Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NOISE_H
#define NOISE_H

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
#include "drv_analog_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define NOISE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NOISE_OK                        0
#define NOISE_ERROR                    -1
/** \} */

/**
 * \defgroup noise_var NOISE_VAR Variables
 * \{
 */
#define NOISE_DEFAULT_COMMAND           0x07
#define NOISE_DEFAULT_THRESHOLD         0x0400
#define NOISE_DAC_A                     0x00
#define NOISE_DAC_B                     0x08
#define NOISE_VREF_UNBUFFERED           0x00
#define NOISE_VREF_BUFFERED             0x04
#define NOISE_GAIN_2X                   0x00
#define NOISE_GAIN_1X                   0x02
#define NOISE_SHDN_ENABLE               0x00
#define NOISE_SHDN_DISABLE              0x01
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

    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;
    analog_in_t adc;

} noise_t;

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
    pin_name_t int_pin;

    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    // ADC module variables
    analog_in_resolution_t resolution;
    float                  vref;

} noise_cfg_t;

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
 * @param cfg Click configuration structure.
 *
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void noise_cfg_setup ( noise_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t noise_init ( noise_t *ctx, noise_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx Click object.
 *
 * @details This function performs default configuration for Noise click.
 * Typically, it's setting threshold to default value. 
 */
void noise_default_cfg ( noise_t *ctx );

/**
 * @brief Write to Command Register
 *
 * @param ctx      Click object.
 * @param cmd_data Command and data to send.
 *
 * @details This function writes data to click's command register.
 */
void noise_write_cmd_reg ( noise_t *ctx, uint16_t cmd_data );

/**
 * @brief Set Command Register
 *
 * @param ctx           Click object.
 * @param configuration Configuration.
 * @param threshold     Threshold.
 *
 * @details This function sets command register.
 *
 * @returns 0 - success ; -1 - ( threshold value ) error
 *
 * @note
 * <pre>
 * Threshold is integer from [0, 4095] segment.
 * When measured noise level is above threshold, alarm is triggered. 
 * </pre>
 */
err_t noise_set_cmd_reg ( noise_t *ctx, uint8_t configuration, uint16_t threshold );

/**
 * @brief Enable/disable click 
 *
 * @param ctx   Click object.
 * @param state State to set click on.
 *
 * @details This function switches click on or off.
 */
void noise_set_state ( noise_t *ctx, uint8_t state );

/**
 * @brief Reset Click 
 *
 * @param ctx Click object.
 *
 * @details This function performs click reset.
 */
void noise_reset ( noise_t *ctx );

/**
 * @brief Get INT pin state 
 *
 * @param ctx Click object.
 *
 * @returns State of INT pin ( eighter 0 or 1 )
 *
 * @details This function gets int pin state.
 */
uint8_t noise_check_int_pin ( noise_t *ctx );

/**
 * @brief Noise read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #noise_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t noise_read_an_pin_value ( noise_t *ctx, uint16_t *data_out );

/**
 * @brief Noise read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #noise_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t noise_read_an_pin_voltage ( noise_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif  // _NOISE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
