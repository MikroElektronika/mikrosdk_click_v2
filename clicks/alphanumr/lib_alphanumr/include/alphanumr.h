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
 * @file alphanumr.h
 * @brief This file contains API for AlphaNum R Click Driver.
 */

#ifndef ALPHANUMR_H
#define ALPHANUMR_H

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

/*!
 * @addtogroup alphanumr AlphaNum R Click Driver
 * @brief API for configuring and manipulating AlphaNum R Click driver.
 * @{
 */

/**
 * @defgroup alphanumr_map AlphaNum R MikroBUS Map
 * @brief MikroBUS pin mapping of AlphaNum R Click driver.
 */

/**
 * @addtogroup alphanumr_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AlphaNum R Click to the selected MikroBUS.
 */
#define ALPHANUMR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.le2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ns1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ns = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // alphanumr_map
/*! @} */ // alphanumr

/**
 * @brief AlphaNum R Click context object.
 * @details Context object definition of AlphaNum R Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  le2; 
    digital_out_t  ns1; 
    digital_out_t  ns;  

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */
    
    uint16_t display_speed;
} alphanumr_t;

/**
 * @brief AlphaNum R Click configuration object.
 * @details Configuration object definition of AlphaNum R Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  le2;      
    pin_name_t  ns1;      
    pin_name_t  ns;       

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} alphanumr_cfg_t;

/**
 * @brief AlphaNum R Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ALPHANUMR_OK = 0,
   ALPHANUMR_ERROR = -1

} alphanumr_return_value_t;

/*!
 * @addtogroup alphanumr AlphaNum R Click Driver
 * @brief API for configuring and manipulating AlphaNum R Click driver.
 * @{
 */

/**
 * @brief AlphaNum R configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #alphanumr_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void alphanumr_cfg_setup ( alphanumr_cfg_t *cfg );

/**
 * @brief AlphaNum R initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #alphanumr_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #alphanumr_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t alphanumr_init ( alphanumr_t *ctx, alphanumr_cfg_t *cfg );

/**
 * @brief Delay character display function.
 * @details This function sets the time interval at which the symbols are displayed.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @param[in] delay_char_display    Delay time interval in ms.
 * @return Nothing.
 * 
 */
void alphanumr_set_display_interval ( alphanumr_t *ctx, uint16_t delay_char_display );

/**
 * @brief Display write function.
 * @details This function displays symbols on the left and right LED segments.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @param[in] left_char    Left segment symbol.
 * @param[in] right_char   Right segment symbol.
 * @return Nothing.
 * 
 */
void alphanumr_display_write ( alphanumr_t *ctx, uint16_t left_char, uint16_t right_char );

/**
 * @brief Character write function.
 * @details This function displays characters on the left and right LED segments.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @param[in] left_char    Left segment symbol.
 * @param[in] right_char   Right segment symbol.
 * @return Nothing.
 * 
 */
void alphanumr_write_character ( alphanumr_t *ctx, uint8_t left_char, uint8_t right_char );

/**
 * @brief Number write function.
 * @details This function displays numbers on the left and right LED segments.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @param[in] left_char    Left segment symbol.
 * @param[in] right_char   Right segment symbol.
 * @return Nothing.
 * 
 */
void alphanumr_write_number ( alphanumr_t *ctx, uint8_t left_char, uint8_t right_char );

/**
 * @brief Reset set high function.
 * @details This function sets the output voltage on the reset pin to high.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @return Nothing.
 * 
 */
void alphanumr_set_rst_high ( alphanumr_t *ctx );

/**
 * @brief Reset set low function.
 * @details This function sets the output voltage on the reset pin to low.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @return Nothing.
 * 
 */
void alphanumr_set_rst_low ( alphanumr_t *ctx );

/**
 * @brief PWM set high function.
 * @details This function sets the output voltage on the PWM pin to high.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @return Nothing.
 * 
 */
void alphanumr_set_pwm_high ( alphanumr_t *ctx );

/**
 * @brief PWM set low function.
 * @details This function sets the output voltage on the PWM pin to highlow.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @return Nothing.
 * 
 */
void alphanumr_set_pwm_low ( alphanumr_t *ctx );

/**
 * @brief Interrupt set high function.
 * @details This function sets the output voltage on the interrupt pin to high.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @return Nothing.
 * 
 */
void alphanumr_set_int_high ( alphanumr_t *ctx );

/**
 * @brief Interrupt set low function.
 * @details This function sets the output voltage on the interrupt pin to high.
 * @param[in] ctx : Click configuration structure.
 * See #alphanumr_t object definition for detailed explanation
 * @return Nothing.
 * 
 */
void alphanumr_set_int_low ( alphanumr_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ALPHANUMR_H

/*! @} */ // alphanumr

// ------------------------------------------------------------------------ END
