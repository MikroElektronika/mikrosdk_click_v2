/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file digiisolator4.h
 * @brief This file contains API for DIGI Isolator 4 Click Driver.
 */

#ifndef DIGIISOLATOR4_H
#define DIGIISOLATOR4_H

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
 * @addtogroup digiisolator4 DIGI Isolator 4 Click Driver
 * @brief API for configuring and manipulating DIGI Isolator 4 Click driver.
 * @{
 */

/**
 * @defgroup digiisolator4_map DIGI Isolator 4 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI Isolator 4 Click driver.
 */

/**
 * @addtogroup digiisolator4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI Isolator 4 Click to the selected MikroBUS.
 */
#define DIGIISOLATOR4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // digiisolator4_map
/*! @} */ // digiisolator4

/**
 * @brief DIGI Isolator 4 Click context object.
 * @details Context object definition of DIGI Isolator 4 Click driver.
 */
typedef struct
{
    digital_out_t en;           /**< Output enable pin. */

    digital_in_t in1;           /**< Channel 1 input state pin. */
    digital_in_t in2;           /**< Channel 2 input state pin. */

} digiisolator4_t;

/**
 * @brief DIGI Isolator 4 Click configuration object.
 * @details Configuration object definition of DIGI Isolator 4 Click driver.
 */
typedef struct
{
    pin_name_t en;              /**< Output enable pin descriptor. */
    pin_name_t in1;             /**< Channel 1 input state pin descriptor. */
    pin_name_t in2;             /**< Channel 2 input state pin descriptor. */

} digiisolator4_cfg_t;

/**
 * @brief DIGI Isolator 4 Click output data structure.
 * @details Output data object definition of DIGI Isolator 4 Click driver.
 */
typedef struct
{
    uint8_t in1_state;          /**< Channel 1 input state. */
    uint8_t in2_state;          /**< Channel 2 input state. */

} digiisolator4_inputs_t;

/**
 * @brief DIGI Isolator 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIISOLATOR4_OK = 0,
    DIGIISOLATOR4_ERROR = -1

} digiisolator4_return_value_t;

/*!
 * @addtogroup digiisolator4 DIGI Isolator 4 Click Driver
 * @brief API for configuring and manipulating DIGI Isolator 4 Click driver.
 * @{
 */

/**
 * @brief DIGI Isolator 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digiisolator4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digiisolator4_cfg_setup ( digiisolator4_cfg_t *cfg );

/**
 * @brief DIGI Isolator 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digiisolator4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digiisolator4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator4_init ( digiisolator4_t *ctx, digiisolator4_cfg_t *cfg );

/**
 * @brief DIGI Isolator 4 enable output function.
 * @details This function enables isolator outputs by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void digiisolator4_enable_output ( digiisolator4_t *ctx );

/**
 * @brief DIGI Isolator 4 disable output function.
 * @details This function disables isolator outputs by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void digiisolator4_disable_output ( digiisolator4_t *ctx );

/**
 * @brief DIGI Isolator 4 get IN1 pin function.
 * @details This function returns the IN1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator4_t object definition for detailed explanation.
 * @return IN1 pin logic state.
 * @note None.
 */
uint8_t digiisolator4_get_in1_pin ( digiisolator4_t *ctx );

/**
 * @brief DIGI Isolator 4 get IN2 pin function.
 * @details This function returns the IN2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #digiisolator4_t object definition for detailed explanation.
 * @return IN2 pin logic state.
 * @note None.
 */
uint8_t digiisolator4_get_in2_pin ( digiisolator4_t *ctx );

/**
 * @brief DIGI Isolator 4 read inputs function.
 * @details This function reads the state of both input channels and stores
 * the result in a digiisolator4_inputs_t structure.
 * @param[in] ctx : Click context object.
 * See #digiisolator4_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the structure containing input channels state.
 * See #digiisolator4_inputs_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator4_read_inputs ( digiisolator4_t *ctx, digiisolator4_inputs_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // DIGIISOLATOR4_H

/*! @} */ // digiisolator4

// ------------------------------------------------------------------------ END
