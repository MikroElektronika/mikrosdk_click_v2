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
 * @file c8x8b.h
 * @brief This file contains API for 8x8 B Click Driver.
 */

#ifndef c8X8B_H
#define c8X8B_H

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
#include "drv_spi_master.h"

/*!
 * @addtogroup c8x8b 8x8 B Click Driver
 * @brief API for configuring and manipulating 8x8 B Click driver.
 * @{
 */

/**
 * @defgroup c8x8b_reg 8x8 B Registers List
 * @brief List of registers of 8x8 B Click driver.
 */

/**
 * @addtogroup c8x8b_reg
 * @{
 */

/**
 * @brief 8x8 B register.
 * @details Specified register for description of 8x8 B Click driver.
 */
#define C8X8B_DECODE_MODE_REG           0x09
#define C8X8B_INTENSITY_REG             0x0A
#define C8X8B_SCAN_LIMIT_REG            0x0B
#define C8X8B_SHUTDOWN_REG              0x0C
#define C8X8B_DISPLAY_TEST_REG          0x0F

/**
 * @brief 8x8 B Decode-Mode register.
 * @details Decode-Mode register for description of 8x8 B Click driver.
 */
#define C8X8B_NO_DECODE                 0x00
#define C8X8B_DECODE_DIGIT_0            0x01
#define C8X8B_DECODE_DIGIT_3_0          0x0F
#define C8X8B_DECODE_DIGIT_7            0xFF

/**
 * @brief 8x8 B intensity format register.
 * @details Intensity format register for description of 8x8 B Click driver.
 */
#define C8X8B_INTENSITY_1               0x00
#define C8X8B_INTENSITY_3               0x01
#define C8X8B_INTENSITY_5               0x02
#define C8X8B_INTENSITY_7               0x03
#define C8X8B_INTENSITY_9               0x04
#define C8X8B_INTENSITY_11              0x05
#define C8X8B_INTENSITY_13              0x06
#define C8X8B_INTENSITY_15              0x07
#define C8X8B_INTENSITY_17              0x08
#define C8X8B_INTENSITY_19              0x09
#define C8X8B_INTENSITY_21              0x0A
#define C8X8B_INTENSITY_23              0x0B
#define C8X8B_INTENSITY_25              0x0C
#define C8X8B_INTENSITY_27              0x0D
#define C8X8B_INTENSITY_29              0x0E
#define C8X8B_INTENSITY_31              0x0F

/**
 * @brief 8x8 B Scan-limit register.
 * @details Scan-limit register for description of 8x8 B Click driver.
 */
#define C8X8B_DISPLAY_DIGIT_0           0x00
#define C8X8B_DISPLAY_DIGIT_0_1         0x01
#define C8X8B_DISPLAY_DIGIT_0_2         0x02
#define C8X8B_DISPLAY_DIGIT_0_3         0x03
#define C8X8B_DISPLAY_DIGIT_0_4         0x04
#define C8X8B_DISPLAY_DIGIT_0_5         0x05
#define C8X8B_DISPLAY_DIGIT_0_6         0x06
#define C8X8B_DISPLAY_DIGIT_0_7         0x07

/**
 * @brief 8x8 B shutdown register register.
 * @details Shutdown register for description of 8x8 B Click driver.
 */
#define C8X8B_SHUTDOWN_MODE             0x00
#define C8X8B_NORMAL_OPERATION          0x01


#define C8X8B_DISPLAY_NORMAL_OPERATION  0x00
#define C8X8B_DISPLAY_TEST_MODE         0X01
/*! @} */ // c8x8b_reg

/**
 * @defgroup c8x8b_set 8x8 B Registers Settings
 * @brief Settings for registers of 8x8 B Click driver.
 */

/**
 * @addtogroup c8x8b_set
 * @{
 */

/**
 * @brief 8x8 B description setting.
 * @details Specified setting for description of 8x8 B Click driver.
 */

/*! @} */ // c8x8b_set

/**
 * @addtogroup c8x8b_scroll_speed
 * @{
 */

/**
 * @brief 8x8 B scroll speed setting.
 * @details Specified setting for scroll speed of 8x8 B Click.
 */
#define C8X8B_SPEED_FAST    3
#define C8X8B_SPEED_MEDIUM  2
#define C8X8B_SPEED_SLOW    1

/*! @} */ // c8x8b_scroll_speed

/**
 * @defgroup c8x8b_map 8x8 B MikroBUS Map
 * @brief MikroBUS pin mapping of 8x8 B Click driver.
 */

/**
 * @addtogroup c8x8b_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 8x8 B Click to the selected MikroBUS.
 */
#define C8X8B_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // c8x8b_map
/*! @} */ // c8x8b

/**
 * @brief 8x8 B Click context object.
 * @details Context object definition of 8x8 B Click driver.
 */
typedef struct
{
    
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t speed_scroll;
    
} c8x8b_t;

/**
 * @brief 8x8 B Click configuration object.
 * @details Configuration object definition of 8x8 B Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */
    
    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} c8x8b_cfg_t;

/**
 * @brief 8x8 B Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   C8X8B_OK = 0,
   C8X8B_ERROR = -1

} c8x8b_return_value_t;

/*!
 * @addtogroup c8x8b 8x8 B Click Driver
 * @brief API for configuring and manipulating 8x8 B Click driver.
 * @{
 */

/**
 * @brief 8x8 B configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c8x8b_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c8x8b_cfg_setup ( c8x8b_cfg_t *cfg );

/**
 * @brief 8x8 B initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c8x8b_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c8x8b_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8x8b_init ( c8x8b_t *ctx, c8x8b_cfg_t *cfg );

/**
 * @brief 8x8 B default configuration function.
 * @details This function executes a default configuration of 8x8 B
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c8x8b_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void c8x8b_default_cfg ( c8x8b_t *ctx );

/**
 * @brief 8x8 B data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c8x8b_t object definition for detailed explanation.
 * @param[in] cmd : The command to be executed.
 * @param[in] tx_data : Data to be sent.
 * @return Nothing.
 * 
 * @note None.
 */
void c8x8b_write_cmd ( c8x8b_t *ctx, uint8_t cmd, uint8_t tx_data  );

/**
 * @brief 8x8 B function for refresh display.
 * @details The function switches off all LEDs.
 * @param[in] ctx : Click context object.
 * See #c8x8b_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note None.
 */
void c8x8b_display_refresh ( c8x8b_t *ctx );

/**
 * @brief 8x8 B scroll setting function.
 * @details This function sets the sroll speed.
 * @param[in] ctx : Click context object.
 * See #c8x8b_t object definition for detailed explanation.
 * @param[in] cmd : The command to be executed.
 * @param[in] speed : Speed that will be set.
 * @return Nothing.
 * 
 * @note Options: 
 *     Fast speed (30ms per character),
 *     Medium speed (100ms per character) - default speed,
 *     Slow speed ( 200ms per character),
 */
void c8x8b_set_speed_scroll ( c8x8b_t *ctx, uint8_t speed );

/**
 * @brief 8x8 B function for displaying scrolling string.
 * @details This function displayes scrolling string to the display.
 * @param[in] ctx : Click context object.
 * See #c8x8b_t object definition for detailed explanation.
 * @param[in] p_array : Pointer to the string to be displayed
 * @return Nothing.
 * 
 * @note 
 *  Function that displays scrolled string with set speed.
 *  If the speed is not set before calling the function,
 *  default scroll speed is 100ms per character.
 */
void c8x8b_display_string ( c8x8b_t *ctx, char *p_array );

/**
 * @brief 8x8 B function for displaying one character.
 * @details This function displayes one character to the display.
 * @param[in] ctx : Click context object.
 * See #c8x8b_t object definition for detailed explanation.
 * @param[in] tx_byte : Character to be displayed.
 * @return Nothing.
 * 
 * @note None.
 * 
 */
void c8x8b_display_byte ( c8x8b_t *ctx, char tx_byte );

/**
 * @brief 8x8 B function for displaying image.
 * @details This function displayes image to the display.
 * @param[in] ctx : Click context object.
 * See #c8x8b_t object definition for detailed explanation.
 * @param[in] p_image : Pointer to the image to be displayed.
 * @return Nothing.
 * 
 * @note Function for displays the image.
 *  The image consists of eight elements (eight columns that build the image).
 * 
 */
void c8x8b_display_image ( c8x8b_t *ctx, uint8_t *p_image );

#ifdef __cplusplus
}
#endif
#endif // c8X8B_H

/*! @} */ // c8x8b

// ------------------------------------------------------------------------ END
