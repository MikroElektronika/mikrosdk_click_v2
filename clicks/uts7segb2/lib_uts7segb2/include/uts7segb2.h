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
 * @file uts7segb2.h
 * @brief This file contains API for UT-S 7-SEG B 2 Click Driver.
 */

#ifndef UTS7SEGB2_H
#define UTS7SEGB2_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "spi_specifics.h"

/*!
 * @addtogroup uts7segb2 UT-S 7-SEG B 2 Click Driver
 * @brief API for configuring and manipulating UT-S 7-SEG B 2 Click driver.
 * @{
 */

/**
 * @defgroup uts7segb2_set UT-S 7-SEG B 2 Registers Settings
 * @brief Settings for registers of UT-S 7-SEG B 2 Click driver.
 */

/**
 * @addtogroup uts7segb2_set
 * @{
 */

/**
 * @brief UT-S 7-SEG B 2 segment bitmask data values.
 * @details Specified segment bitmask data values of UT-S 7-SEG B 2 Click driver.
 */
#define UTS7SEGB2_SEG_DIS14_SEG0              0x00000001l
#define UTS7SEGB2_SEG_DIS14_SEG1              0x00000002l
#define UTS7SEGB2_SEG_DIS14_SEG2              0x00000004l
#define UTS7SEGB2_SEG_DIS14_SEG3              0x00000008l
#define UTS7SEGB2_SEG_DIS14_SEG4              0x00000010l
#define UTS7SEGB2_SEG_DIS14_SEG5              0x00000020l
#define UTS7SEGB2_SEG_DIS14_SEG6              0x00000040l
#define UTS7SEGB2_SEG_DIS14_SEG7              0x00000080l
#define UTS7SEGB2_SEG_DIS25_SEG0              0x00000100l
#define UTS7SEGB2_SEG_DIS25_SEG1              0x00000200l
#define UTS7SEGB2_SEG_DIS25_SEG2              0x00000400l
#define UTS7SEGB2_SEG_DIS25_SEG3              0x00000800l
#define UTS7SEGB2_SEG_DIS25_SEG4              0x00001000l
#define UTS7SEGB2_SEG_DIS25_SEG5              0x00002000l
#define UTS7SEGB2_SEG_DIS25_SEG6              0x00004000l
#define UTS7SEGB2_SEG_DIS25_SEG7              0x00008000l
#define UTS7SEGB2_SEG_DIS36_SEG0              0x00010000l
#define UTS7SEGB2_SEG_DIS36_SEG1              0x00020000l
#define UTS7SEGB2_SEG_DIS36_SEG2              0x00040000l
#define UTS7SEGB2_SEG_DIS36_SEG3              0x00080000l
#define UTS7SEGB2_SEG_DIS36_SEG4              0x00100000l
#define UTS7SEGB2_SEG_DIS36_SEG5              0x00200000l
#define UTS7SEGB2_SEG_DIS36_SEG6              0x00400000l
#define UTS7SEGB2_SEG_DIS36_SEG7              0x00800000l
#define UTS7SEGB2_SEG_ALL                     0x01FFFFFFl
#define UTS7SEGB2_SEG_BIT_MASK                0x01FFFFFFl

/**
 * @brief UT-S 7-SEG B 2 data bitmask.
 * @details Specified data bit masks of UT-S 7-SEG B 2 Click driver.
 */
#define UTS7SEGB2_NIBBLE_LOW                  0x000Fu
#define UTS7SEGB2_NIBBLE_HIGH                 0x00F0u
#define UTS7SEGB2_BYTE_LOW                    0x00FFu
#define UTS7SEGB2_WORD_BIT_POS_0              0x0001u
#define UTS7SEGB2_WORD_BIT_POS_14             0x4000u
#define UTS7SEGB2_WORD_BIT_POS_15             0x8000u

/**
 * @brief UT-S 7-SEG B 2 segment position number data values.
 * @details Specified segment position number data values of UT-S 7-SEG B 2 Click driver.
 */
#define UTS7SEGB2_SEG_NUM_START               0
#define UTS7SEGB2_SEG_NUM_END                 23
#define UTS7SEGB2_SEG_NUM_POS                 24

/**
 * @brief UT-S 7-SEG B 2 brightness range data values.
 * @details Specified brightness range data values of UT-S 7-SEG B 2 Click driver.
 */
#define UTS7SEGB2_BRIGHTNESS_MIN              0x0000u
#define UTS7SEGB2_BRIGHTNESS_DEFAULT          0x07FFu
#define UTS7SEGB2_BRIGHTNESS_MAX              0x0FFFu

/**
 * @brief UT-S 7-SEG B 2 description of the base values.
 * @details Specified base values, number of digits used to represent numbers
 * of UT-S 7-SEG B 2 Click driver.
 */
#define UTS7SEGB2_BASE_NUM_SYS_BINARY         2
#define UTS7SEGB2_BINARY_NUM_MAX              UTS7SEGB2_BASE_NUM_SYS_BINARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_BINARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_BINARY - 1
#define UTS7SEGB2_BASE_NUM_SYS_TERNARY        3
#define UTS7SEGB2_TERNARY_NUM_MAX             UTS7SEGB2_BASE_NUM_SYS_TERNARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_TERNARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_TERNARY - 1
#define UTS7SEGB2_BASE_NUM_SYS_QUATERNARY     4
#define UTS7SEGB2_QUATERNARY_NUM_MAX          UTS7SEGB2_BASE_NUM_SYS_QUATERNARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_QUATERNARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_QUATERNARY - 1
#define UTS7SEGB2_BASE_NUM_SYS_QUINARY        5
#define UTS7SEGB2_QUINARY_NUM_MAX             UTS7SEGB2_BASE_NUM_SYS_QUINARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_QUINARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_QUINARY - 1
#define UTS7SEGB2_BASE_NUM_SYS_SENARY         6
#define UTS7SEGB2_SENARY_NUM_MAX              UTS7SEGB2_BASE_NUM_SYS_SENARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_SENARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_SENARY - 1
#define UTS7SEGB2_BASE_NUM_SYS_SEPTENARY      7
#define UTS7SEGB2_SEPTENARY_NUM_MAX           UTS7SEGB2_BASE_NUM_SYS_SEPTENARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_SEPTENARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_SEPTENARY - 1
#define UTS7SEGB2_BASE_NUM_SYS_OCTAL          8
#define UTS7SEGB2_OCTAL_NUM_MAX               UTS7SEGB2_BASE_NUM_SYS_OCTAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_OCTAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_OCTAL - 1
#define UTS7SEGB2_BASE_NUM_SYS_NONARY         9
#define UTS7SEGB2_NONARY_NUM_MAX              UTS7SEGB2_BASE_NUM_SYS_NONARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_NONARY * \
                                              UTS7SEGB2_BASE_NUM_SYS_NONARY - 1
#define UTS7SEGB2_BASE_NUM_SYS_DECIMAL        10
#define UTS7SEGB2_DECIMAL_NUM_MAX             UTS7SEGB2_BASE_NUM_SYS_DECIMAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_DECIMAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_DECIMAL - 1
#define UTS7SEGB2_BASE_NUM_SYS_UNDECIMAL      11
#define UTS7SEGB2_UNDECIMAL_NUM_MAX           UTS7SEGB2_BASE_NUM_SYS_UNDECIMAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_UNDECIMAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_UNDECIMAL - 1
#define UTS7SEGB2_BASE_NUM_SYS_DUODECIMAL     12
#define UTS7SEGB2_DUODECIMAL_NUM_MAX          UTS7SEGB2_BASE_NUM_SYS_DUODECIMAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_DUODECIMAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_DUODECIMAL - 1
#define UTS7SEGB2_BASE_NUM_SYS_HEXADECIMAL    16
#define UTS7SEGB2_HEXADECIMAL_NUM_MAX         UTS7SEGB2_BASE_NUM_SYS_HEXADECIMAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_HEXADECIMAL * \
                                              UTS7SEGB2_BASE_NUM_SYS_HEXADECIMAL - 1

/**
 * @brief UT-S 7-SEG B 2 dots bitmask data values.
 * @details Specified dots bitmask data values of UT-S 7-SEG B 2 Click driver.
 */
#define UTS7SEGB2_TOP_SEG_NO_DOT              0x00
#define UTS7SEGB2_TOP_SEG_DOT_RIGHT           0x01
#define UTS7SEGB2_TOP_SEG_DOT_MIDDLE          0x02
#define UTS7SEGB2_TOP_SEG_DOT_LEFT            0x04
#define UTS7SEGB2_BOTTOM_SEG_NO_DOT           0x00
#define UTS7SEGB2_BOTTOM_SEG_DOT_RIGHT        0x20
#define UTS7SEGB2_BOTTOM_SEG_DOT_LEFT         0x08
#define UTS7SEGB2_BOTTOM_SEG_DOT_MIDDLE       0x10

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b uts7segb2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define UTS7SEGB2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define UTS7SEGB2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // uts7segb2_set

/**
 * @defgroup uts7segb2_map UT-S 7-SEG B 2 MikroBUS Map
 * @brief MikroBUS pin mapping of UT-S 7-SEG B 2 Click driver.
 */

/**
 * @addtogroup uts7segb2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UT-S 7-SEG B 2 Click to the selected MikroBUS.
 */
#define UTS7SEGB2_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.cs2  = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // uts7segb2_map
/*! @} */ // uts7segb2

/**
 * @brief UT-S 7-SEG B 2 Click context object.
 * @details Context object definition of UT-S 7-SEG B 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cs2;    /**< Chip select 2 pin descriptor (used for SPI driver). */
    digital_out_t pwm;    /**< Blank enable pin. */

    // Modules
    spi_master_t spi;     /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} uts7segb2_t;

/**
 * @brief UT-S 7-SEG B 2 Click configuration object.
 * @details Configuration object definition of UT-S 7-SEG B 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t cs2;    /**< Chip select 2 pin descriptor (used for SPI driver). */
    pin_name_t pwm;    /**< Blank enable pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} uts7segb2_cfg_t;

/**
 * @brief UT-S 7-SEG B 2 character configuration object.
 * @details Character onfiguration object definition of UT-S 7-SEG B 2 Click driver.
 */
typedef struct
{
    uint8_t  char_top_left;        /**< Top left character. */
    uint8_t  char_top_mid;         /**< Top middle character. */
    uint8_t  char_top_right;       /**< Top right character. */
    uint8_t  char_bottom_left;     /**< Bottom left character. */
    uint8_t  char_bottom_mid;      /**< Bottom middle character. */
    uint8_t  char_bottom_right;    /**< Bottom right character. */
    uint16_t brightness;           /**< Character brightness. */

} uts7segb2_character_cfg_t;

/**
 * @brief UT-S 7-SEG B 2 number configuration object.
 * @details Number onfiguration object definition of UT-S 7-SEG B 2 Click driver.
 */
typedef struct
{
    uint16_t num_top;              /**< Top number. */
    uint16_t brightness_top;       /**< Top number brightness. */
    uint16_t num_bottom;           /**< Bottom number. */
    uint16_t brightness_bottom;    /**< Bottom number brightness. */
    uint8_t  base;                 /**< Total count of digits used to express numbers in a number system. */
    uint8_t  dot_bit_mask;         /**< Dot bitmask. */

} uts7segb2_number_cfg_t;

/**
 * @brief UT-S 7-SEG B 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UTS7SEGB2_OK = 0,
    UTS7SEGB2_ERROR = -1

} uts7segb2_return_value_t;

/**
 * @brief UT-S 7-SEG B 2 segment group selection value data.
 * @details Predefined enum values for driver segment group selection.
 */
typedef enum
{
    UTS7SEGB2_SEG_TOP = 0,
    UTS7SEGB2_SEG_BOTTOM

} uts7segb2_seg_sel_t;

/*!
 * @addtogroup uts7segb2 UT-S 7-SEG B 2 Click Driver
 * @brief API for configuring and manipulating UT-S 7-SEG B 2 Click driver.
 * @{
 */

/**
 * @brief UT-S 7-SEG B 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uts7segb2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uts7segb2_cfg_setup ( uts7segb2_cfg_t *cfg );

/**
 * @brief UT-S 7-SEG B 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uts7segb2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_init ( uts7segb2_t *ctx, uts7segb2_cfg_t *cfg );

/**
 * @brief UT-S 7-SEG B 2 default configuration function.
 * @details This function executes a default configuration of UT-S 7-SEG B 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t uts7segb2_default_cfg ( uts7segb2_t *ctx );

/**
 * @brief UT-S 7-SEG B 2 top segment data writing function.
 * @details This function writes a desired number of data bytes on top segment 
 * of the TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_top_seg_write ( uts7segb2_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief UT-S 7-SEG B 2 top segment data reading function.
 * @details This function reads a desired number of data bytes on top segment 
 * of the TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_top_seg_read ( uts7segb2_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief UT-S 7-SEG B 2 bottom segment data writing function.
 * @details This function writes a desired number of data bytes on bottom segment 
 * of the TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_bottom_seg_write ( uts7segb2_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief UT-S 7-SEG B 2 bottom segment data reading function.
 * @details This function reads a desired number of data bytes on bottom segment 
 * of the TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_bottom_seg_read ( uts7segb2_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief UT-S 7-SEG B 2 set outputs ON function.
 * @details This function sets all constant current outputs 
 * to be controlled by a PWM grayscale time controller
 * of the TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.ad.
 * @return Nothing.
 * @note None.
 */
void uts7segb2_set_outputs_on ( uts7segb2_t *ctx );

/**
 * @brief UT-S 7-SEG B 2 set outputs OFF function.
 * @details This function sets all constant-current outputs forced to turn off
 * of the TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.ad.
 * @return Nothing.
 * @note None.
 */
void uts7segb2_set_outputs_off ( uts7segb2_t *ctx );

/**
 * @brief UT-S 7-SEG B 2 set segment position function.
 * @details This function sets desired brightness value of the selected segment position
 * of the JSS-3011BUB-21 driven by TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[in] seg_sel : Segment group selection [0-1] - [Top-Bottom].
 * @param[in] seg_num : Selected segment position, 3 7-seg groups of 8 positions each [0-23].
 * @param[in] brightness : Brightness [0-4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_set_seg_pos ( uts7segb2_t *ctx, uts7segb2_seg_sel_t seg_sel, 
                              uint8_t seg_num, uint16_t brightness );

/**
 * @brief UT-S 7-SEG B 2 set LED output function.
 * @details This function sets the LED driver output to control 6 x JSS-3011BUB-21
 * driven by TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[in] seg_sel : Segment group selection [0-1] - [Top-Bottom].
 * @param[in] seg_bit_mask : Selected segment bitmaks [0-0x01FFFFFF].
 * @param[in] brightness : Brightness [0-4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_set_led_output ( uts7segb2_t *ctx, uts7segb2_seg_sel_t seg_sel, 
                                 uint32_t seg_bit_mask, uint16_t brightness );

/**
 * @brief UT-S 7-SEG B 2 display character function.
 * @details This function displays the desired characters and brightness 
 * on the selected segments driven by 
 * TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[in] ascii_char : ASCII character configuration object.
 * See #uts7segb2_character_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_display_character ( uts7segb2_t *ctx, uts7segb2_character_cfg_t ascii_char );

/**
 * @brief UT-S 7-SEG B 2 display number function.
 * @details This function displays the desired number and brightness 
 * on the selected segments driven by 
 * TLC5947DAPR, 24-Channel, 12-Bit PWM LED Driver With Internal Oscillator
 * on the UT-S 7-SEG B 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #uts7segb2_t object definition for detailed explanation.
 * @param[in] number : Number configuration object.
 * See #uts7segb2_number_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uts7segb2_display_number ( uts7segb2_t *ctx, uts7segb2_number_cfg_t number );

#ifdef __cplusplus
}
#endif
#endif // UTS7SEGB2_H

/*! @} */ // uts7segb2

// ------------------------------------------------------------------------ END
