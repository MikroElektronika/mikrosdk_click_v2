/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file alphanumg2.h
 * @brief This file contains API for AlphaNum G 2 Click Driver.
 */

#ifndef ALPHANUMG2_H
#define ALPHANUMG2_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "spi_specifics.h"

/*!
 * @addtogroup alphanumg2 AlphaNum G 2 Click Driver
 * @brief API for configuring and manipulating AlphaNum G 2 Click driver.
 * @{
 */

/**
 * @defgroup alphanumg2_set AlphaNum G 2 Registers Settings
 * @brief Settings for registers of AlphaNum G 2 Click driver.
 */

/**
 * @addtogroup alphanumg2_set
 * @{
 */

/**
 * @brief AlphaNum G 2 data bit mask.
 * @details Specified data bit masks of AlphaNum G 2 Click driver.
 */
#define ALPHANUMG2_NIBBLE_LOW                0x000Fu
#define ALPHANUMG2_BYTE_LOW                  0x00FFu
#define ALPHANUMG2_WORD_BIT_POS_0            0x0001u
#define ALPHANUMG2_WORD_BIT_POS_14           0x4000u
#define ALPHANUMG2_WORD_BIT_POS_15           0x8000u

/**
 * @brief AlphaNum G 2 brightness range data values.
 * @details Specified brightness range data values of AlphaNum G 2 Click driver.
 */
#define ALPHANUMG2_BRIGHTNESS_MIN            0x0000u
#define ALPHANUMG2_BRIGHTNESS_MAX            0x0FFFu

/**
 * @brief AlphaNum G 2 default character duration.
 * @details Specified default character duration of AlphaNum G 2 Click driver.
 */
#define ALPHANUMG2_DEFAULT_DUR_1000_MS       1000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b alphanumg2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ALPHANUMG2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ALPHANUMG2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // alphanumg2_set

/**
 * @defgroup alphanumg2_map AlphaNum G 2 MikroBUS Map
 * @brief MikroBUS pin mapping of AlphaNum G 2 Click driver.
 */

/**
 * @addtogroup alphanumg2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AlphaNum G 2 Click to the selected MikroBUS.
 */
#define ALPHANUMG2_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.blk  = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.ca1  = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.ca2  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // alphanumg2_map
/*! @} */ // alphanumg2

/**
 * @brief AlphaNum G 2 Click context object.
 * @details Context object definition of AlphaNum G 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t blk;    /**< Blank enable pin. */
    digital_out_t ca1;    /**< Left segment enable pin. */
    digital_out_t ca2;    /**< Right segment enable pin. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    uint16_t char_duration;      /**< Duration of the displayed characters [ms]. */

} alphanumg2_t;

/**
 * @brief AlphaNum G 2 Click configuration object.
 * @details Configuration object definition of AlphaNum G 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t blk;     /**< Blank enable pin. */
    pin_name_t ca1;     /**< Left segment enable pin. */
    pin_name_t ca2;     /**< Right segment enable pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} alphanumg2_cfg_t;

/**
 * @brief AlphaNum G 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ALPHANUMG2_OK = 0,
    ALPHANUMG2_ERROR = -1

} alphanumg2_return_value_t;

/**
 * @brief AlphaNum G 2 Click dot symbol value data.
 * @details Predefined enum values for dot symbol values.
 */
typedef enum
{
    ALPHANUMG2_NO_DOT = 0,
    ALPHANUMG2_SET_DOT

} alphanumg2_dot_t;

/*!
 * @addtogroup alphanumg2 AlphaNum G 2 Click Driver
 * @brief API for configuring and manipulating AlphaNum G 2 Click driver.
 * @{
 */

/**
 * @brief AlphaNum G 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #alphanumg2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void alphanumg2_cfg_setup ( alphanumg2_cfg_t *cfg );

/**
 * @brief AlphaNum G 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #alphanumg2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t alphanumg2_init ( alphanumg2_t *ctx, alphanumg2_cfg_t *cfg );

/**
 * @brief AlphaNum G 2 default configuration function.
 * @details This function executes a default configuration of AlphaNum G 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t alphanumg2_default_cfg ( alphanumg2_t *ctx );

/**
 * @brief AlphaNum G 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t alphanumg2_generic_write ( alphanumg2_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief AlphaNum G 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t alphanumg2_generic_read ( alphanumg2_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief AlphaNum G 2 set character duration function.
 * @details This function is used to set the character display duration [ms].
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @param[in] duration_ms : Character display duration [ms].
 * @return Nothing.
 * @note None.
 */
void alphanumg2_set_char_duration ( alphanumg2_t *ctx, uint16_t duration_ms );

/**
 * @brief AlphaNum G 2 set outputs OFF function.
 * @details This function sets all constant-current outputs forced to turn off
 * of the TLC5947, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the AlphaNum G 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void alphanumg2_set_outputs_off ( alphanumg2_t *ctx );

/**
 * @brief AlphaNum G 2 set outputs ON function.
 * @details This function sets all constant current outputs 
 * to be controlled by a PWM grayscale time controller
 * of the TLC5947, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the AlphaNum G 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void alphanumg2_set_outputs_on ( alphanumg2_t *ctx );

/**
 * @brief AlphaNum G 2 set segment left OFF function.
 * @details This function is used to turn OFF the left segment 
 * of the LTP-3862G, 0.3 inch (7.62 mm) digit height dual digit 16-segment alphanumeric display
 * on the AlphaNum G 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void alphanumg2_set_seg_left_off ( alphanumg2_t *ctx );

/**
 * @brief AlphaNum G 2 set segment left ON function.
 * @details This function is used to turn ON the left segment 
 * of the LTP-3862G, 0.3 inch (7.62 mm) digit height dual digit 16-segment alphanumeric display
 * on the AlphaNum G 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void alphanumg2_set_seg_left_on ( alphanumg2_t *ctx );

/**
 * @brief AlphaNum G 2 set segment right OFF function.
 * @details This function is used to turn OFF the right segment 
 * of the LTP-3862G, 0.3 inch (7.62 mm) digit height dual digit 16-segment alphanumeric display
 * on the AlphaNum G 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void alphanumg2_set_seg_right_off ( alphanumg2_t *ctx );

/**
 * @brief AlphaNum G 2 set segment right ON function.
 * @details This function is used to turn ON the right segment 
 * of the LTP-3862G, 0.3 inch (7.62 mm) digit height dual digit 16-segment alphanumeric display
 * on the AlphaNum G 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void alphanumg2_set_seg_right_on ( alphanumg2_t *ctx );

/**
 * @brief AlphaNum G 2 set LED output function.
 * @details This function sets the LED driver output 
 * to control to the 24-channel, constant-current sink by using SPI serial interface
 * of the TLC5947, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the AlphaNum G 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @param[in] seg_bit_mask : 16-Segment bit mask.
 * @param[in] seg_dot : Dot symbol.
 * See #alphanumg2_dot_t definition for detailed explanation.
 * @param[in] brightness : Brightness [0-4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For each set the segments are ordered sequentially.
 * Bit '0' corresponds to segment 'A', bit '1' corresponds to segment 'B', and so-on. 
 * Here are the ordered segments for each display:
 *         @li @c 16-Segment: U-T-S-R-P-N-M-K-H-G-F-E-D-C-B-A.
 */
err_t alphanumg2_set_led_output ( alphanumg2_t *ctx, uint16_t seg_bit_mask, 
                                  alphanumg2_dot_t seg_dot, uint16_t brightness );

/**
 * @brief AlphaNum G 2 display character function.
 * @details This function displays the desired characters and brightness on both 16-segments 
 * of the TLC5947, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the AlphaNum G 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #alphanumg2_t object definition for detailed explanation.
 * @param[in] left_char : Left segment - ASCII character.
 * @param[in] left_brightness : Left segment brightness [0-4095].
 * @param[in] right_char : Right segment - ASCII character.
 * @param[in] right_brightness : Right segment brightness [0-4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note 
 */
err_t alphanumg2_display_character ( alphanumg2_t *ctx, uint8_t left_char, uint16_t left_brightness,  
                                                        uint8_t right_char, uint16_t right_brightness );

#ifdef __cplusplus
}
#endif
#endif // ALPHANUMG2_H

/*! @} */ // alphanumg2

// ------------------------------------------------------------------------ END
