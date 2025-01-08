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
 * @file hbridge17.h
 * @brief This file contains API for H-Bridge 17 Click Driver.
 */

#ifndef HBRIDGE17_H
#define HBRIDGE17_H

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
 * @addtogroup hbridge17 H-Bridge 17 Click Driver
 * @brief API for configuring and manipulating H-Bridge 17 Click driver.
 * @{
 */

/**
 * @defgroup hbridge17_map H-Bridge 17 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 17 Click driver.
 */

/**
 * @addtogroup hbridge17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 17 Click to the selected MikroBUS.
 */
#define HBRIDGE17_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge17_map
/*! @} */ // hbridge17

/**
 * @brief H-Bridge 17 Click context object.
 * @details Context object definition of H-Bridge 17 Click driver.
 */
typedef struct
{
    digital_out_t in2;    /**< Output 2 control pin. */
    digital_out_t en;     /**< IC enable pin. */
    digital_out_t in1;    /**< Output 1 control pin. */
    digital_in_t  flt;    /**< Fault indication pin. */

} hbridge17_t;

/**
 * @brief H-Bridge 17 Click configuration object.
 * @details Configuration object definition of H-Bridge 17 Click driver.
 */
typedef struct
{
    pin_name_t in2;   /**< Output 2 control pin. */
    pin_name_t en;    /**< IC enable pin. */
    pin_name_t in1;   /**< Output 1 control pin. */
    pin_name_t flt;   /**< Fault indication pin. */

} hbridge17_cfg_t;

/**
 * @brief H-Bridge 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE17_OK = 0,
    HBRIDGE17_ERROR = -1

} hbridge17_return_value_t;

/**
 * @brief H-Bridge 17 Click motor states selection.
 * @details Predefined enum values for motor states selection.
 */
typedef enum
{
    HBRIDGE17_DRIVE_MOTOR_FORWARD = 0,
    HBRIDGE17_DRIVE_MOTOR_BRAKE,
    HBRIDGE17_DRIVE_MOTOR_REVERSE,
    HBRIDGE17_DRIVE_MOTOR_FREEWHEEL,
    
} hbridge17_out_state_t;

/*!
 * @addtogroup hbridge17 H-Bridge 17 Click Driver
 * @brief API for configuring and manipulating H-Bridge 17 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 17 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge17_cfg_setup ( hbridge17_cfg_t *cfg );

/**
 * @brief H-Bridge 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge17_init ( hbridge17_t *ctx, hbridge17_cfg_t *cfg );

/**
 * @brief H-Bridge 17 IC enable function.
 * @details This function enables driver IC by setting the EN (RST) pin 
 * on the high level of the H-Bridge 17 Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void hbridge17_ic_enable ( hbridge17_t *ctx );

/**
 * @brief H-Bridge 17 IC disable function.
 * @details This function disables driver IC by setting the EN (RST) pin 
 * on the low level of the H-Bridge 17 Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void hbridge17_ic_disable ( hbridge17_t *ctx );

/**
 * @brief H-Bridge 17 set IN1 pin state function.
 * @details This function sets the IN1 (PWM) pin on the high level of
 * H-Bridge 17 Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void hbridge17_set_in1_pin ( hbridge17_t *ctx );

/**
 * @brief H-Bridge 17 IN1 pin clearing function.
 * @details This function clears the IN1 (PWM) pin on the low level of
 * H-Bridge 17 Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void hbridge17_clear_in1_pin ( hbridge17_t *ctx );

/**
 * @brief H-Bridge 17 set IN2 pin state function.
 * @details This function sets the IN2 (AN) pin on the high level of
 * H-Bridge 17 Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void hbridge17_set_in2_pin ( hbridge17_t *ctx );

/**
 * @brief H-Bridge 17 IN2 pin clearing function.
 * @details This function clears the IN2 (AN) pin on the low level of
 * H-Bridge 17 Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void hbridge17_clear_in2_pin ( hbridge17_t *ctx );

/**
 * @brief H-Bridge 17 set output function.
 * @details This function is used to set the output state of
 * H-Bridge 17 Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @param[in] out_state : Motor states selection.
 * See #hbridge17_out_state_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge17_set_out_state ( hbridge17_t *ctx, hbridge17_out_state_t out_state );

/**
 * @brief H-Bridge 17 fault indication function.
 * @details This function reads the state of the FLT (INT) pin of H-Bridge 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge17_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t hbridge17_fault_indication ( hbridge17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE17_H

/*! @} */ // hbridge17

// ------------------------------------------------------------------------ END
