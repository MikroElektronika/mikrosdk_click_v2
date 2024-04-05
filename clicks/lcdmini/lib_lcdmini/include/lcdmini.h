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
 * @file lcdmini.h
 * @brief This file contains API for LCD mini Click Driver.
 */

#ifndef LCDMINI_H
#define LCDMINI_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup lcdmini LCD mini Click Driver
 * @brief API for configuring and manipulating LCD mini Click driver.
 * @{
 */

/**
 * @defgroup lcdmini_reg LCD mini Registers List
 * @brief List of registers of LCD mini Click driver.
 */

/**
 * @addtogroup lcdmini_reg
 * @{
 */

/**
 * @brief LCD mini description register.
 * @details Specified register for description of LCD mini Click driver.
 */
#define LCDMINI_IODIRB_BANK0                    0x01
#define LCDMINI_OLATB_BANK0                     0x15
#define LCDMINI_IOCON_BANK0                     0x0A
#define LCDMINI_ADDRESS_CODE                    0x40
#define LCDMINI_GPIO_REGISTER                   0x09

/*! @} */ // lcdmini_reg

/**
 * @defgroup lcdmini_set LCD mini Registers Settings
 * @brief Settings for registers of LCD mini Click driver.
 */

/**
 * @addtogroup lcdmini_set
 * @{
 */

/**
 * @brief LCD mini description setting.
 * @details Specified setting for description of LCD mini Click driver.
 */
#define LCDMINI_ENABLE                          0x08
#define LCDMINI_RESET                           0x04

#define LCDMINI_OP_CODE_READ                    0x01
#define LCDMINI_OP_CODE_WRITE                   0xFE

/**
 * @brief LCD mini commands.
 * @details Specified commands for setting up LCD mini Click driver.
 */
#define LCDMINI_CLEAR                           0x01
#define LCDMINI_RETURN_HOME                     0x02
#define LCDMINI_DISPLAY_OFF_CURSOR_OFF          0x08
#define LCDMINI_CURSOR_OFF                      0x0C
#define LCDMINI_UNDERLINE_ON                    0x0E
#define LCDMINI_BLINK_CURSOR_ON                 0x0F
#define LCDMINI_MOVE_CURSOR_LEFT                0x10
#define LCDMINI_MOVE_CURSOR_RIGHT               0x14
#define LCDMINI_TURN_ON                         0x0A
#define LCDMINI_TURN_OFF                        0x0C
#define LCDMINI_SHIFT_LEFT                      0x18
#define LCDMINI_SHIFT_RIGHT                     0x1C
#define LCDMINI_2_LINE_5X7                      0x28

#define LCDMINI_FIRST_ROW                       0x80      
#define LCDMINI_SECOND_ROW                      0xC0   
#define LCDMINI_THIRD_ROW                       0x94 
#define LCDMINI_FOURTH_ROW                      0xD4


/**
 * @brief LCD mini default PWM frequency.
 * @details Specified setting for setting default PWM frequency of LCD mini Click driver.
 */
#define LCDMINI_DEF_FREQ                        500

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b lcdmini_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LCDMINI_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define LCDMINI_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // lcdmini_set

/**
 * @defgroup lcdmini_map LCD mini MikroBUS Map
 * @brief MikroBUS pin mapping of LCD mini Click driver.
 */

/**
 * @addtogroup lcdmini_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LCD mini Click to the selected MikroBUS.
 */
#define LCDMINI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cs2  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lcdmini_map
/*! @} */ // lcdmini

/**
 * @brief LCD mini Click context object.
 * @details Context object definition of LCD mini Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  cs2;             /**< Digipot CS. */
    digital_out_t  rst;             /**< Reset for the port expander. */

    // Input pins
    digital_in_t  int_pin;          /**< INT from the port expander. */

    // Modules
    pwm_t pwm;                      /**< PWM driver object. */
    
    spi_master_t  spi;              /**< SPI driver object. */

    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    uint32_t pwm_freq;              /**< PWM frequency value. */

} lcdmini_t;

/**
 * @brief LCD mini Click configuration object.
 * @details Configuration object definition of LCD mini Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                 /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t   cs2;               /**< Digipot CS. */
    pin_name_t  rst;                /**< Reset for the port expander. */
    pin_name_t  pwm;                /**< PWM pin. */
    pin_name_t  int_pin;            /**< INT from the port expander. */

    // Static variables
    uint32_t dev_pwm_freq;           /**< PWM frequency value. */
    
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} lcdmini_cfg_t;

/**
 * @brief LCD mini Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LCDMINI_OK = 0,
   LCDMINI_ERROR = -1

} lcdmini_return_value_t;

/*!
 * @addtogroup lcdmini LCD mini Click Driver
 * @brief API for configuring and manipulating LCD mini Click driver.
 * @{
 */

/**
 * @brief LCD mini configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lcdmini_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lcdmini_cfg_setup ( lcdmini_cfg_t *cfg );

/**
 * @brief LCD mini initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lcdmini_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lcdmini_init ( lcdmini_t *ctx, lcdmini_cfg_t *cfg );

/**
 * @brief LCD mini default configuration function.
 * @details This function executes a default configuration of LCD mini
 * click board.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lcdmini_default_cfg ( lcdmini_t *ctx );

/**
 * @brief LCD mini data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lcdmini_generic_write ( lcdmini_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LCD mini data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lcdmini_generic_read ( lcdmini_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LCD mini sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lcdmini_set_duty_cycle ( lcdmini_t *ctx, float duty_cycle );

/**
 * @brief LCD mini stop PWM module.
 * @details This function stops the PWM module output.
 * @param[out] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lcdmini_pwm_stop ( lcdmini_t *ctx );

/**
 * @brief LCD mini start PWM module.
 * @details This function starts the PWM module output.
 * @param[out] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lcdmini_pwm_start ( lcdmini_t *ctx );

/**
 * @brief Set backlight function.
 * @details The function sets backlight value by setting PWM's duty cycle.
 * @param[out] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] backlight_value : Backlight value.
 * @return Nothing.
 * @note Backlight value can be a value between 0 and 1.
 */
void lcdmini_set_backlight ( lcdmini_t *ctx, float backlight_value );

/**
 * @brief Set contrast function.
 * @details The function sets contrast by write 8-bit contrast value to the
 * targeted 8-bit register address of MCP4161 on LCD mini Click board.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] contrast_value : 8-bit contrast value.
 * @return Nothing.
 */
void lcdmini_set_contrast( lcdmini_t *ctx, uint8_t contrast_value );

/**
 * @brief Get interrupt
 * @details Checks is there a interrupt is active.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @return State of the interrupt pin.
 */
uint8_t lcdmini_get_interrupt( lcdmini_t *ctx );

/**
 * @brief Hardware reset function
 * @details Hardware reset function of LCD mini Click bord.
 * @param[out] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @return Nothing.
 */
void lcdmini_hw_reset( lcdmini_t *ctx );

/**
 * @brief LCD mini register data reading function.
 * @details This function reads data byte from the selected register of MCP23S17
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lcdmini_read_register ( lcdmini_t *ctx, uint8_t reg , uint8_t *data_out );

/**
 * @brief LCD mini register data writing function.
 * @details This function writes a 8-bit data to the selected register of MCP23S17
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lcdmini_write_register ( lcdmini_t *ctx, uint8_t reg , uint8_t data_in );

/**
 * @brief LCD mini send command.
 * @details This function writes a 8-bit data to the LCD screeen by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] command : Command to be written.
 * @return Nothing.
 */
void lcdmini_send_cmd ( lcdmini_t *ctx, uint8_t command );

/**
 * @brief LCD mini send character.
 * @details This function writes a character to the LCD screeen by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] character : Command to be written.
 * @return Nothing.
 */
void lcdmini_send_char ( lcdmini_t *ctx, uint8_t character );

/**
 * @brief LCD mini display character.
 * @details This function displays specified character to the LCD screen in selected row and column.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] row : Selected row for data to be written.
 * @param[in] column : Selected column for data to be written.
 * @param[in] character : Character to be written.
 * @return Nothing.
 */
void lcdmini_display_char ( lcdmini_t *ctx, uint8_t row, uint8_t column, char character );

/**
 * @brief LCD mini display text.
 * @details This function displays specified character array to the 
 * LCD screen in selected row and column.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] row : Selected row for data to be written.
 * @param[in] column : Selected column for data to be written.
 * @param[in] data_in : Characters to be written.
 * @param[in] len : Number of character to be written.
 * @return Nothing.
 */
void lcdmini_display_text ( lcdmini_t *ctx, uint8_t row, uint8_t column, char *data_in );

#ifdef __cplusplus
}
#endif
#endif // LCDMINI_H

/*! @} */ // lcdmini

// ------------------------------------------------------------------------ END
