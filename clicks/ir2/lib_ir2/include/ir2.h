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
 * @file ir2.h
 * @brief This file contains API for IR 2 Click Driver.
 */

#ifndef IR2_H
#define IR2_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup ir2 IR 2 Click Driver
 * @brief API for configuring and manipulating IR 2 Click driver.
 * @{
 */

/**
 * @defgroup ir2_cfg IR 2 Device Settings
 * @brief Settings for configuration of IR 2 Click driver.
 */

/**
 * @addtogroup ir2_cfg
 * @{
 */

/**
 * @brief IR 2 control commands.
 * @details Specified setting for control commands of IR Click driver.
 */
#define IR2_STATE_HIGH          0x01
#define IR2_STATE_LOW           0x00

/**
 * @brief IR 2 default PWM frequency and duty cycle.
 * @details Default PWM frequency and duty cycle setting of IR 2 Click driver.
 */
#define IR2_DEF_FREQ            38000
#define IR2_DEF_DUTY_CYCLE      0.25

/*! @} */ // ir2_cfg

/**
 * @defgroup ir2_map IR 2 MikroBUS Map
 * @brief MikroBUS pin mapping of IR 2 Click driver.
 */

/**
 * @addtogroup ir2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR 2 Click to the selected MikroBUS.
 */
#define IR2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ir2_map
/*! @} */ // ir2

/**
 * @brief IR 2 Click driver selector.
 * @details Selects target driver interface of IR Click driver.
 */
typedef enum
{
    IR2_DRV_SEL_GPIO,        /**< GPIO driver descriptor. */
    IR2_DRV_SEL_UART         /**< UART driver descriptor. */

} ir2_drv_t;
/**
 * @brief IR 2 Click context object.
 * @details Context object definition of IR 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t out_pin;   /**< OUT pin. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */

    ir2_drv_t  drv_sel;     /**< Master driver interface selector. */

} ir2_t;

/**
 * @brief IR 2 Click configuration object.
 * @details Configuration object definition of IR 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;         /**< PWM pin. */
    pin_name_t int_pin;     /**< INT pin. */
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */
    
    uint32_t dev_pwm_freq;  /**< PWM frequency value. */

    ir2_drv_t  drv_sel;     /**< Master driver interface selector. */

} ir2_cfg_t;

/**
 * @brief IR 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IR2_OK = 0,
    IR2_ERROR = -1

} ir2_return_value_t;

/*!
 * @addtogroup ir2 IR 2 Click Driver
 * @brief API for configuring and manipulating IR 2 Click driver.
 * @{
 */

/**
 * @brief IR 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ir2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ir2_cfg_setup ( ir2_cfg_t *cfg );

/**
 * @brief IR 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ir2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ir2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ir2_drv_interface_selection ( ir2_cfg_t *cfg, ir2_drv_t drv_sel );

/**
 * @brief IR 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ir2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ir2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ir2_init ( ir2_t *ctx, ir2_cfg_t *cfg );

/**
 * @brief IR 2 get OUT pin function.
 * @details This function returns the OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ir2_t object definition for detailed explanation.
 * @return State of the OUT pin.
 * @note None.
 */
uint8_t ir2_get_out_pin ( ir2_t *ctx );

/**
 * @brief IR 2 NEC send data function.
 * @details This function sends an address and data bytes using NEC protocol.
 * @param[in] ctx : Click context object.
 * See #ir2_t object definition for detailed explanation.
 * @param[in] address : Input address data.
 * @param[in] data_in : Input data byte.
 * @return Nothing.
 * @note None.
 */
void ir2_nec_send_data ( ir2_t *ctx, uint8_t address, uint8_t data_in );

/**
 * @brief IR 2 NEC read data function.
 * @details This function reads an address and data bytes by using NEC protocol.
 * @param[in] ctx : Click context object.
 * See #ir2_t object definition for detailed explanation.
 * @param[out] address : Output read address byte.
 * @param[out] data_out : Output read data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ir2_nec_read_data ( ir2_t *ctx, uint8_t *address, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // IR2_H

/*! @} */ // ir2

// ------------------------------------------------------------------------ END
