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
 * @file dtmfgenerator.h
 * @brief This file contains API for DTMF Generator Click Driver.
 */

#ifndef DTMFGENERATOR_H
#define DTMFGENERATOR_H

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

/*!
 * @addtogroup dtmfgenerator DTMF Generator Click Driver
 * @brief API for configuring and manipulating DTMF Generator Click driver.
 * @{
 */

/**
 * @defgroup dtmfgenerator_set DTMF Generator Registers Settings
 * @brief Settings for registers of DTMF Generator Click driver.
 */
/**
 * @addtogroup dtmfgenerator_set
 * @{
 */

/**
 * @brief DTMF Generator description setting.
 * @details Specified setting for description of DTMF Generator Click driver.
 */
#define DTMFGENERATOR_OUT_TONE_0                                    0x00
#define DTMFGENERATOR_OUT_TONE_1                                    0x01
#define DTMFGENERATOR_OUT_TONE_2                                    0x02
#define DTMFGENERATOR_OUT_TONE_3                                    0x03
#define DTMFGENERATOR_OUT_TONE_4                                    0x04
#define DTMFGENERATOR_OUT_TONE_5                                    0x05
#define DTMFGENERATOR_OUT_TONE_6                                    0x06
#define DTMFGENERATOR_OUT_TONE_7                                    0x07
#define DTMFGENERATOR_OUT_TONE_8                                    0x08
#define DTMFGENERATOR_OUT_TONE_9                                    0x09
#define DTMFGENERATOR_OUT_TONE_A                                    0x0A
#define DTMFGENERATOR_OUT_TONE_B                                    0x0B
#define DTMFGENERATOR_OUT_TONE_C                                    0x0C
#define DTMFGENERATOR_OUT_TONE_D                                    0x0D
#define DTMFGENERATOR_OUT_TONE_ASTERISK                             0x0E
#define DTMFGENERATOR_OUT_TONE_HASH                                 0x0F
#define DTMFGENERATOR_OUT_TONE_STOP                                 0x10

#define DTMFGENERATOR_GPIO_PIN_STATE_LOW                            0x00
#define DTMFGENERATOR_GPIO_PIN_STATE_HIGH                           0x01
/*! @} */ // dtmfgenerator_set

/**
 * @defgroup dtmfgenerator_map DTMF Generator MikroBUS Map
 * @brief MikroBUS pin mapping of DTMF Generator Click driver.
 */

/**
 * @addtogroup dtmfgenerator_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DTMF Generator Click to the selected MikroBUS.
 */
#define DTMFGENERATOR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.dat = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ce = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // dtmfgenerator_map
/*! @} */ // dtmfgenerator

/**
 * @brief DTMF Generator Click context object.
 * @details Context object definition of DTMF Generator Click driver.
 */
typedef struct
{
    digital_out_t  dat;     /**< Data Input. */
    digital_out_t  ce;       /**< Chip Enable. */
    digital_out_t  clk;     /**< Data Synchronous Clock Input. */

} dtmfgenerator_t;

/**
 * @brief DTMF Generator Click configuration object.
 * @details Configuration object definition of DTMF Generator Click driver.
 */
typedef struct
{
    pin_name_t  dat;    /**< Data Input. */
    pin_name_t  ce;      /**< Chip Enable. */
    pin_name_t  clk;    /**< Data Synchronous Clock Input. */

} dtmfgenerator_cfg_t;

/**
 * @brief DTMF Generator Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DTMFGENERATOR_OK = 0,
   DTMFGENERATOR_ERROR = -1

} dtmfgenerator_return_value_t;

/*!
 * @addtogroup dtmfgenerator DTMF Generator Click Driver
 * @brief API for configuring and manipulating DTMF Generator Click driver.
 * @{
 */

/**
 * @brief DTMF Generator configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dtmfgenerator_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dtmfgenerator_cfg_setup ( dtmfgenerator_cfg_t *cfg );

/**
 * @brief DTMF Generator initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dtmfgenerator_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dtmfgenerator_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmfgenerator_init ( dtmfgenerator_t *ctx, dtmfgenerator_cfg_t *cfg );

/**
 * @brief Set DATA ( RST ) pin state function.
 * @details The function set DATA ( RST ) pin state.
 * @param[out] ctx : Click context object.
 * See #dtmfgenerator_t object definition for detailed explanation.
 * @param[in] pin_state : The RST the pin state ( low or high ).
 * @return Nothing.
 */
void dtmfgenerator_set_dat ( dtmfgenerator_t *ctx, uint8_t pin_state );

/**
 * @brief Set CE ( CS ) pin state function.
 * @details The function set CE ( CS ) pin state.
 * @param[out] ctx : Click context object.
 * See #dtmfgenerator_t object definition for detailed explanation.
 * @param[in] pin_state : The RST the pin state ( low or high ).
 * @return Nothing.
 */
void dtmfgenerator_set_ce ( dtmfgenerator_t *ctx, uint8_t pin_state );

/**
 * @brief Set CLK ( PWM ) pin state function.
 * @details The function set CLK ( PWM ) pin state.
 * @param[out] ctx : Click context object.
 * See #dtmfgenerator_t object definition for detailed explanation.
 * @param[in] pin_state : The PWM the pin state ( low or high ).
 * @return Nothing.
 */
void dtmfgenerator_set_clk ( dtmfgenerator_t *ctx, uint8_t pin_state );

/**
 * @brief Power ON function.
 * @details The function run the power-on sequence.
 * @param[in] ctx : Click context object.
 * See #dtmfgenerator_t object definition for detailed explanation.
 * @return Nothing.
 */
void dtmfgenerator_power_on ( dtmfgenerator_t *ctx );

/**
 * @brief Transmit output tone function.
 *
 * @details The function transmit duration time of the desired tone.
 * @param[in] ctx : Click context object.
 * See #dtmfgenerator_t object definition for detailed explanation.
 * @param[in] out_tone : The tone for digit that is being sent to the DTMF Generator.
 * @param[in] delay_m_s : 16-bit tone duration time in milliseconds.
 * @return Nothing.
 */
void dtmfgenerator_transmit_out_tone ( dtmfgenerator_t *ctx, uint8_t out_tone, uint16_t delay_m_s );

#ifdef __cplusplus
}
#endif
#endif // DTMFGENERATOR_H

/*! @} */ // dtmfgenerator

// ------------------------------------------------------------------------ END
