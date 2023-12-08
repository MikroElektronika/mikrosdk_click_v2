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
 * @file dcmotor24.h
 * @brief This file contains API for DC Motor 24 Click Driver.
 */

#ifndef DCMOTOR24_H
#define DCMOTOR24_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup dcmotor24 DC Motor 24 Click Driver
 * @brief API for configuring and manipulating DC Motor 24 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor24_set DC Motor 24 Settings
 * @brief Settings of DC Motor 24 Click driver.
 */

/**
 * @addtogroup dcmotor24_set
 * @{
 */

/**
 * @brief DC Motor 24 configuration protocol (CFG_REG) setting.
 * @details Specified setting for configuration protocol (CFG_REG) of DC Motor 24 Click driver.
 */
#define DCMOTOR24_CFG_DR                    0x0002u
#define DCMOTOR24_CFG_CL_2p5A               0x0000u
#define DCMOTOR24_CFG_CL_4A                 0x0004u
#define DCMOTOR24_CFG_CL_6p6A               0x0008u
#define DCMOTOR24_CFG_CL_8p6A               0x000Cu
#define DCMOTOR24_CFG_CL_MASK               0x000Cu
#define DCMOTOR24_CFG_VSR                   0x0100u
#define DCMOTOR24_CFG_ISR                   0x0200u
#define DCMOTOR24_CFG_ISR_DIS               0x0400u
#define DCMOTOR24_CFG_OL_ON                 0x0800u

/**
 * @brief DC Motor 24 diagnostics protocol (DIA_REG) setting.
 * @details Specified setting for diagnostics protocol (DIA_REG) of DC Motor 24 Click driver.
 */
#define DCMOTOR24_DIA_OL_OFF                0x0001u
#define DCMOTOR24_DIA_OL_ON                 0x0002u
#define DCMOTOR24_DIA_VS_UV                 0x0004u
#define DCMOTOR24_DIA_VDD_OV                0x0008u
#define DCMOTOR24_DIA_ILIM                  0x0010u
#define DCMOTOR24_DIA_TWARN                 0x0020u
#define DCMOTOR24_DIA_TSD                   0x0040u
#define DCMOTOR24_DIA_ACT                   0x0080u
#define DCMOTOR24_DIA_OC_LS1                0x0100u
#define DCMOTOR24_DIA_OC_LS2                0x0200u
#define DCMOTOR24_DIA_OC_HS1                0x0400u
#define DCMOTOR24_DIA_OC_HS2                0x0800u
#define DCMOTOR24_DIA_SGND_OFF              0x4000u
#define DCMOTOR24_DIA_SBAT_OFF              0x8000u

/**
 * @brief DC Motor 24 direction setting.
 * @details Specified setting for direction of DC Motor 24 Click driver.
 */
#define DCMOTOR24_DIR_REVERSE               0
#define DCMOTOR24_DIR_FORWARD               1

/**
 * @brief DC Motor 24 default PWM frequency.
 * @details Specified setting for default PWM frequency of DC Motor 24 Click driver.
 */
#define DCMOTOR24_DEF_FREQ                  5000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dcmotor24_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DCMOTOR24_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DCMOTOR24_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dcmotor24_set

/**
 * @defgroup dcmotor24_map DC Motor 24 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 24 Click driver.
 */

/**
 * @addtogroup dcmotor24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 24 Click to the selected MikroBUS.
 */
#define DCMOTOR24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // dcmotor24_map
/*! @} */ // dcmotor24

/**
 * @brief DC Motor 24 Click context object.
 * @details Context object definition of DC Motor 24 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;          /**< Direction select pin (High-Forward, Low-Reverse). */
    digital_out_t en;           /**< Enable pin (Active high). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */
    pwm_t        pwm;           /**< PWM driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */
    uint32_t     pwm_freq;      /**< PWM frequency value. */
    
    uint16_t     config_word;

} dcmotor24_t;

/**
 * @brief DC Motor 24 Click configuration object.
 * @details Configuration object definition of DC Motor 24 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */    
    pin_name_t pwm;             /**< PWM pin. */

    // Additional gpio pins
    pin_name_t dir;             /**< Direction select pin (High-Forward, Low-Reverse). */
    pin_name_t en;              /**< Enable pin (Active high). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    uint32_t                          dev_pwm_freq; /**< PWM frequency value. */

} dcmotor24_cfg_t;

/**
 * @brief DC Motor 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR24_OK = 0,
    DCMOTOR24_ERROR = -1

} dcmotor24_return_value_t;

/*!
 * @addtogroup dcmotor24 DC Motor 24 Click Driver
 * @brief API for configuring and manipulating DC Motor 24 Click driver.
 * @{
 */

/**
 * @brief DC Motor 24 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor24_cfg_setup ( dcmotor24_cfg_t *cfg );

/**
 * @brief DC Motor 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor24_init ( dcmotor24_t *ctx, dcmotor24_cfg_t *cfg );

/**
 * @brief DC Motor 24 default configuration function.
 * @details This function executes a default configuration of DC Motor 24
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor24_default_cfg ( dcmotor24_t *ctx );

/**
 * @brief DC Motor 24 write config function.
 * @details This function writes a desired configuration word by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @param[in] config_word : Configuration word for CFG_REG.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor24_write_config ( dcmotor24_t *ctx, uint16_t config_word );

/**
 * @brief DC Motor 24 read diag function.
 * @details This function reads a diagnostics word by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @param[out] diag : Diagnostics word from DIA_REG.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor24_read_diag ( dcmotor24_t *ctx, uint16_t *diag );

/**
 * @brief DC Motor 24 set direction function.
 * @details This function sets the motor direction.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @param[in] dir @li @c 0 - Reverse,
 *                @li @c 1 - Forward.
 * @return None.
 * @note None.
 */
void dcmotor24_set_direction ( dcmotor24_t *ctx, uint8_t dir );

/**
 * @brief DC Motor 24 switch direction function.
 * @details This function switches the direction by toggling the DIR pin state.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor24_switch_direction ( dcmotor24_t *ctx );

/**
 * @brief DC Motor 24 enable output function.
 * @details This function enables the output by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor24_enable_output ( dcmotor24_t *ctx );

/**
 * @brief DC Motor 24 disable output function.
 * @details This function disables the output by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor24_disable_output ( dcmotor24_t *ctx );

/**
 * @brief DC Motor 24 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor24_set_duty_cycle ( dcmotor24_t *ctx, float duty_cycle );

/**
 * @brief DC Motor 24 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor24_pwm_stop ( dcmotor24_t *ctx );

/**
 * @brief DC Motor 24 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor24_pwm_start ( dcmotor24_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR24_H

/*! @} */ // dcmotor24

// ------------------------------------------------------------------------ END
