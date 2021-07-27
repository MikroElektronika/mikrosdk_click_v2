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
 * @file rotaryb.h
 * @brief This file contains API for ROTARY B Click Driver.
 */

#ifndef ROTARYB_H
#define ROTARYB_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup rotaryb ROTARY B Click Driver
 * @brief API for configuring and manipulating ROTARY B Click driver.
 * @{
 */

/**
 * @addtogroup rotaryb_led
 * @{
 */

/**
 * @brief ROTARY B Number of LED's.
 * @details Specified number of LED's that are on.
 */
#define ROTARYB_ONE_LED      0x0001
#define ROTARYB_TWO_LED      0x0101
#define ROTARYB_FOUR_LED     0x1111
#define ROTARYB_EIGHT_LED    0x5555
#define ROTARYB_RESET_LED    0x0000

/*! @} */ // rotaryb_led

/**
 * @defgroup rotaryb_map ROTARY B MikroBUS Map
 * @brief MikroBUS pin mapping of ROTARY B Click driver.
 */

/**
 * @addtogroup rotaryb_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ROTARY B Click to the selected MikroBUS.
 */
#define ROTARYB_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ecb = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.eca = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.sw = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rotaryb_map
/*! @} */ // rotaryb

/**
 * @brief ROTARY B Click context object.
 * @details Context object definition of ROTARY B Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  rst; 
    digital_out_t cs;

    // Input pins

    digital_in_t   ecb;  
    digital_in_t   eca;  
    digital_in_t   sw;   

    // Modules

    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} rotaryb_t;

/**
 * @brief ROTARY B Click configuration object.
 * @details Configuration object definition of ROTARY B Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  ecb;      
    pin_name_t  rst;      
    pin_name_t  eca;      
    pin_name_t  sw;       

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} rotaryb_cfg_t;

/**
 * @brief ROTARY B Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ROTARYB_OK = 0,
   ROTARYB_ERROR = -1

} rotaryb_return_value_t;

/*!
 * @addtogroup rotaryb ROTARY B Click Driver
 * @brief API for configuring and manipulating ROTARY B Click driver.
 * @{
 */

/**
 * @brief ROTARY B configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rotaryb_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rotaryb_cfg_setup ( rotaryb_cfg_t *cfg );

/**
 * @brief ROTARY B initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rotaryb_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rotaryb_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryb_init ( rotaryb_t *ctx, rotaryb_cfg_t *cfg );

/**
 * @brief ROTARY B data transfer function.
 * @details This function reads and writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rotaryb_t object definition for detailed explanation.
 * @param[in] wr_buf : Write data buffer.
 * @param[in] wr_len : Number of byte in write data buffer.
 * @param[in] rd_buf : Read data buffer.
 * @param[in] rd_len : Number of byte in read data buffer.
 * @return Nothing.
 *
 * @note None.
 */
void rotaryb_generic_transfer ( rotaryb_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief ROTARY B generic data write function.
 * @details Function turn on led by data.
 * @param[in] ctx : Click context object.
 * See #rotaryb_t object definition for detailed explanation.
 * @param[in] write_data : Data to write.
 * @return Nothing.
 *
 * @note None.
 */
void rotaryb_turn_on_led_by_data ( rotaryb_t *ctx, uint16_t write_data );

/**
 * @brief ROTARY B turn on led by position function.
 * @details Function turn on led by position
 * @param[in] ctx : Click context object.
 * See #rotaryb_t object definition for detailed explanation.
 * @param[in] led_position : Led position.
 * @return Nothing.
 *
 * @note None.
 */
void rotaryb_turn_on_led_by_position ( rotaryb_t *ctx, uint8_t led_position );

/**
 * @brief Button push state.
 * @details Function return 1 if button is pushed and return 0 if not
 * @param[in] ctx : Click context object.
 * See #rotaryb_t object definition for detailed explanation.
 * @return @li @c 1 - Button is pushed,
 *         @li @c 0 - Button isn't pushed.
 *
 * @note None.
 */
uint8_t rotaryb_button_push ( rotaryb_t *ctx );

/**
 * @brief Get led data state.
 * @details Function return 16-bit data by current led state.
 * @param[in] current_led_state : Current state of led.
 * @return Led state.
 *
 * @note None.
 */
uint16_t rotaryb_get_led_data ( uint8_t current_led_state );

/**
 * @brief Reset led.
 * @details Function turn off all led.
 * @param[in] ctx : Click context object.
 * See #rotaryb_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void rotaryb_reset_led ( rotaryb_t *ctx );

/**
 * @brief State ecb pin.
 * @details Function return ecb state.
 * @param[in] ctx : Click context object.
 * See #rotaryb_t object definition for detailed explanation.
 * @return ecb pin state
 *
 * @note None.
 */
uint8_t rotaryb_get_ecb_state ( rotaryb_t *ctx );

/**
 * @brief State eca pin.
 * @details Function return eca state.
 * @param[in] ctx : Click context object.
 * See #rotaryb_t object definition for detailed explanation.
 * @return eca pin state
 *
 * @note None.
 */
uint8_t rotaryb_get_eca_state ( rotaryb_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ROTARYB_H

/*! @} */ // rotaryb

// ------------------------------------------------------------------------ END
