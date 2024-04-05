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
 * @file silentstep3.h
 * @brief This file contains API for Silent Step 3 Click Driver.
 */

#ifndef SILENTSTEP3_H
#define SILENTSTEP3_H

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

/*!
 * @addtogroup silentstep3 Silent Step 3 Click Driver
 * @brief API for configuring and manipulating Silent Step 3 Click driver.
 * @{
 */

/**
 * @defgroup silentstep3_reg Silent Step 3 Registers List
 * @brief List of registers of Silent Step 3 Click driver.
 */

/**
 * @addtogroup silentstep3_reg
 * @{
 */

/**
 * @brief Silent Step 3 register list.
 * @details Specified register list of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_REG_DRVCTRL                 0x00
#define SILENTSTEP3_REG_CHOPCONF                0x04
#define SILENTSTEP3_REG_SMARTEN                 0x05
#define SILENTSTEP3_REG_SGCSCONF                0x06
#define SILENTSTEP3_REG_DRVCONF                 0x07

/*! @} */ // silentstep3_reg

/**
 * @defgroup silentstep3_set Silent Step 3 Registers Settings
 * @brief Settings for registers of Silent Step 3 Click driver.
 */

/**
 * @addtogroup silentstep3_set
 * @{
 */

/**
 * @brief Silent Step 3 DRVCTRL (SDOFF=1) register setting.
 * @details Specified setting for DRVCTRL (SDOFF=1) register of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_DRVCTRL_1_PHA_MASK          0x20000ul
#define SILENTSTEP3_DRVCTRL_1_CA_MASK           0x1FE00ul
#define SILENTSTEP3_DRVCTRL_1_PHB_MASK          0x00100ul
#define SILENTSTEP3_DRVCTRL_1_CB_MASK           0x000FFul

/**
 * @brief Silent Step 3 DRVCTRL (SDOFF=0) register setting.
 * @details Specified setting for DRVCTRL (SDOFF=0) register of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_DRVCTRL_0_INTPOL_MASK       0x00200ul
#define SILENTSTEP3_DRVCTRL_0_DEDGE_MASK        0x00100ul
#define SILENTSTEP3_DRVCTRL_0_MRES_256          0x00000ul
#define SILENTSTEP3_DRVCTRL_0_MRES_128          0x00001ul
#define SILENTSTEP3_DRVCTRL_0_MRES_64           0x00002ul
#define SILENTSTEP3_DRVCTRL_0_MRES_32           0x00003ul
#define SILENTSTEP3_DRVCTRL_0_MRES_16           0x00004ul
#define SILENTSTEP3_DRVCTRL_0_MRES_8            0x00005ul
#define SILENTSTEP3_DRVCTRL_0_MRES_4            0x00006ul
#define SILENTSTEP3_DRVCTRL_0_MRES_2            0x00007ul
#define SILENTSTEP3_DRVCTRL_0_MRES_1            0x00008ul
#define SILENTSTEP3_DRVCTRL_0_MRES_MASK         0x0000Ful

/**
 * @brief Silent Step 3 CHOPCONF register setting.
 * @details Specified setting for CHOPCONF register of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_CHOPCONF_TBL_16             0x00000ul
#define SILENTSTEP3_CHOPCONF_TBL_24             0x08000ul
#define SILENTSTEP3_CHOPCONF_TBL_32             0x10000ul
#define SILENTSTEP3_CHOPCONF_TBL_54             0x18000ul
#define SILENTSTEP3_CHOPCONF_TBL_MASK           0x18000ul
#define SILENTSTEP3_CHOPCONF_CHM_STANDARD       0x00000ul
#define SILENTSTEP3_CHOPCONF_CHM_FAST           0x04000ul
#define SILENTSTEP3_CHOPCONF_CHM_MASK           0x04000ul
#define SILENTSTEP3_CHOPCONF_RNDTF_DISABLE      0x00000ul
#define SILENTSTEP3_CHOPCONF_RNDTF_ENABLE       0x02000ul
#define SILENTSTEP3_CHOPCONF_RNDTF_MASK         0x02000ul
#define SILENTSTEP3_CHOPCONF_HDEC_16            0x00000ul
#define SILENTSTEP3_CHOPCONF_HDEC_32            0x00800ul
#define SILENTSTEP3_CHOPCONF_HDEC_48            0x01000ul
#define SILENTSTEP3_CHOPCONF_HDEC_64            0x01800ul
#define SILENTSTEP3_CHOPCONF_HDEC_MASK          0x01800ul
#define SILENTSTEP3_CHOPCONF_HEND_0             0x00180ul
#define SILENTSTEP3_CHOPCONF_HEND_MASK          0x00780ul
#define SILENTSTEP3_CHOPCONF_HSTRT_4            0x00030ul
#define SILENTSTEP3_CHOPCONF_HSTRT_MASK         0x00070ul
#define SILENTSTEP3_CHOPCONF_TOFF_4             0x00004ul
#define SILENTSTEP3_CHOPCONF_TOFF_MASK          0x0000Ful

/**
 * @brief Silent Step 3 SMARTEN register setting.
 * @details Specified setting for SMARTEN register of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_SMARTEN_SEIMIN_HALF_CS      0x00000ul
#define SILENTSTEP3_SMARTEN_SEIMIN_QUARTER_CS   0x08000ul
#define SILENTSTEP3_SMARTEN_SEIMIN_MASK         0x08000ul
#define SILENTSTEP3_SMARTEN_SEDN_32             0x00000ul
#define SILENTSTEP3_SMARTEN_SEDN_8              0x02000ul
#define SILENTSTEP3_SMARTEN_SEDN_2              0x04000ul
#define SILENTSTEP3_SMARTEN_SEDN_1              0x06000ul
#define SILENTSTEP3_SMARTEN_SEDN_MASK           0x06000ul
#define SILENTSTEP3_SMARTEN_SEMAX_2             0x00200ul
#define SILENTSTEP3_SMARTEN_SEMAX_MASK          0x00F00ul
#define SILENTSTEP3_SMARTEN_SEUP_1              0x00000ul
#define SILENTSTEP3_SMARTEN_SEUP_2              0x00020ul
#define SILENTSTEP3_SMARTEN_SEUP_4              0x00040ul
#define SILENTSTEP3_SMARTEN_SEUP_8              0x00060ul
#define SILENTSTEP3_SMARTEN_SEUP_MASK           0x00060ul
#define SILENTSTEP3_SMARTEN_SEMIN_2             0x00002ul
#define SILENTSTEP3_SMARTEN_SEMIN_MASK          0x0000Ful

/**
 * @brief Silent Step 3 SGCSCONF register setting.
 * @details Specified setting for SGCSCONF register of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_SGCSCONF_SFILT_STANDARD     0x00000ul
#define SILENTSTEP3_SGCSCONF_SFILT_FILTERED     0x10000ul
#define SILENTSTEP3_SGCSCONF_SFILT_MASK         0x10000ul
#define SILENTSTEP3_SGCSCONF_SGT_0              0x00000ul
#define SILENTSTEP3_SGCSCONF_SGT_MASK           0x07F00ul
#define SILENTSTEP3_SGCSCONF_CS_2_OF_32         0x00002ul
#define SILENTSTEP3_SGCSCONF_CS_MASK            0x0001Ful

/**
 * @brief Silent Step 3 DRVCONF register setting.
 * @details Specified setting for DRVCONF register of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_DRVCONF_TST_MASK            0x10000ul
#define SILENTSTEP3_DRVCONF_SLPH_MIN            0x00000ul
#define SILENTSTEP3_DRVCONF_SLPH_MIN_TEMP       0x04000ul
#define SILENTSTEP3_DRVCONF_SLPH_MED_TEMP       0x08000ul
#define SILENTSTEP3_DRVCONF_SLPH_MAX            0x0C000ul
#define SILENTSTEP3_DRVCONF_SLPH_MASK           0x0C000ul
#define SILENTSTEP3_DRVCONF_SLPL_MIN            0x00000ul
#define SILENTSTEP3_DRVCONF_SLPL_MIN_TEMP       0x01000ul
#define SILENTSTEP3_DRVCONF_SLPL_MED_TEMP       0x02000ul
#define SILENTSTEP3_DRVCONF_SLPL_MAX            0x03000ul
#define SILENTSTEP3_DRVCONF_SLPL_MASK           0x03000ul
#define SILENTSTEP3_DRVCONF_DISS2G_ENABLE       0x00000ul
#define SILENTSTEP3_DRVCONF_DISS2G_DISABLE      0x00400ul
#define SILENTSTEP3_DRVCONF_DISS2G_MASK         0x00400ul
#define SILENTSTEP3_DRVCONF_TS2G_3_2US          0x00000ul
#define SILENTSTEP3_DRVCONF_TS2G_1_6US          0x00100ul
#define SILENTSTEP3_DRVCONF_TS2G_1_2US          0x00200ul
#define SILENTSTEP3_DRVCONF_TS2G_0_8US          0x00300ul
#define SILENTSTEP3_DRVCONF_TS2G_MASK           0x00300ul
#define SILENTSTEP3_DRVCONF_SDOFF_0             0x00000ul
#define SILENTSTEP3_DRVCONF_SDOFF_1             0x00080ul
#define SILENTSTEP3_DRVCONF_SDOFF_MASK          0x00080ul
#define SILENTSTEP3_DRVCONF_VSENSE_305MV        0x00000ul
#define SILENTSTEP3_DRVCONF_VSENSE_165MV        0x00040ul
#define SILENTSTEP3_DRVCONF_VSENSE_MASK         0x00040ul
#define SILENTSTEP3_DRVCONF_RDSEL_MSTEP         0x00000ul
#define SILENTSTEP3_DRVCONF_RDSEL_SG_LEVEL      0x00010ul
#define SILENTSTEP3_DRVCONF_RDSEL_SG_CS_LEVEL   0x00020ul
#define SILENTSTEP3_DRVCONF_RDSEL_MASK          0x00030ul

/**
 * @brief Silent Step 3 pin logic state setting.
 * @details Specified setting for pin logic state of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_PIN_STATE_LOW               0
#define SILENTSTEP3_PIN_STATE_HIGH              1

/**
 * @brief Silent Step 3 direction setting.
 * @details Specified setting for direction of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_DIR_CCW                     0
#define SILENTSTEP3_DIR_CW                      1

/**
 * @brief Silent Step 3 step resolution setting.
 * @details Specified setting for step resolution of Silent Step 3 Click driver.
 */
#define SILENTSTEP3_MODE_FULL_STEP              8
#define SILENTSTEP3_MODE_HALF_STEP              7
#define SILENTSTEP3_MODE_QUARTER_STEP           6
#define SILENTSTEP3_MODE_1_OVER_8_STEP          5
#define SILENTSTEP3_MODE_1_OVER_16_STEP         4
#define SILENTSTEP3_MODE_1_OVER_32_STEP         3
#define SILENTSTEP3_MODE_1_OVER_64_STEP         2
#define SILENTSTEP3_MODE_1_OVER_128_STEP        1
#define SILENTSTEP3_MODE_1_OVER_256_STEP        0

/**
 * @brief Silent Step 3 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define SILENTSTEP3_SPEED_VERY_SLOW             0
#define SILENTSTEP3_SPEED_SLOW                  1
#define SILENTSTEP3_SPEED_MEDIUM                2
#define SILENTSTEP3_SPEED_FAST                  3
#define SILENTSTEP3_SPEED_VERY_FAST             4 

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b silentstep3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SILENTSTEP3_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define SILENTSTEP3_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // silentstep3_set

/**
 * @defgroup silentstep3_map Silent Step 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Silent Step 3 Click driver.
 */

/**
 * @addtogroup silentstep3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Silent Step 3 Click to the selected MikroBUS.
 */
#define SILENTSTEP3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sg   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dir  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // silentstep3_map
/*! @} */ // silentstep3

/**
 * @brief Silent Step 3 Click context object.
 * @details Context object definition of Silent Step 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Power MOSFET enable pin (active low). */
    digital_out_t step;         /**< Step signal pin. */
    digital_out_t dir;          /**< Direction control pin. */

    // Input pins
    digital_in_t sg;            /**< Signals a motor stall (active high). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

    uint32_t drvctrl;           /**< DRVCTRL register settings. */
    uint32_t chopconf;          /**< CHOPCONF register settings. */
    uint32_t smarten;           /**< SMARTEN register settings. */
    uint32_t sgcsconf;          /**< SGCSCONF register settings. */
    uint32_t drvconf;           /**< DRVCONF register settings. */

} silentstep3_t;

/**
 * @brief Silent Step 3 Click configuration object.
 * @details Configuration object definition of Silent Step 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t en;              /**< Power MOSFET enable pin (active low). */
    pin_name_t sg;              /**< Signals a motor stall (active high). */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t dir;             /**< Direction control pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} silentstep3_cfg_t;

/**
 * @brief Silent Step 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SILENTSTEP3_OK = 0,
    SILENTSTEP3_ERROR = -1

} silentstep3_return_value_t;

/*!
 * @addtogroup silentstep3 Silent Step 3 Click Driver
 * @brief API for configuring and manipulating Silent Step 3 Click driver.
 * @{
 */

/**
 * @brief Silent Step 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #silentstep3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void silentstep3_cfg_setup ( silentstep3_cfg_t *cfg );

/**
 * @brief Silent Step 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #silentstep3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep3_init ( silentstep3_t *ctx, silentstep3_cfg_t *cfg );

/**
 * @brief Silent Step 3 default configuration function.
 * @details This function executes a default configuration of Silent Step 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t silentstep3_default_cfg ( silentstep3_t *ctx );

/**
 * @brief Silent Step 3 write command function.
 * @details This function writes data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 18-bit data to be written.
 * @param[out] data_out : 20-bit response data (Optional).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep3_write_register ( silentstep3_t *ctx, uint8_t reg, uint32_t data_in, uint32_t *data_out );

/**
 * @brief Silent Step 3 set step mode function.
 * @details This function sets the microstep resolution bits in DRVCTRL register.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @param[in] mode : MODE bits setting:
 *                   @li @c 0 - 1/256 microsteps,
 *                   @li @c 1 - 1/128 microsteps,
 *                   @li @c 2 - 1/64 microsteps,
 *                   @li @c 3 - 1/32 microsteps,
 *                   @li @c 4 - 1/16 microsteps,
 *                   @li @c 5 - 1/8 microsteps,
 *                   @li @c 6 - quarter step,
 *                   @li @c 7 - half step,
 *                   @li @c 8 - full step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep3_set_step_mode ( silentstep3_t *ctx, uint8_t mode );

/**
 * @brief Silent Step 3 enable device function.
 * @details This function enables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void silentstep3_enable_device ( silentstep3_t *ctx );

/**
 * @brief Silent Step 3 disable device function.
 * @details This function disables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void silentstep3_disable_device ( silentstep3_t *ctx );

/**
 * @brief Silent Step 3 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void silentstep3_set_direction ( silentstep3_t *ctx, uint8_t dir );

/**
 * @brief Silent Step 3 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void silentstep3_switch_direction ( silentstep3_t *ctx );

/**
 * @brief Silent Step 3 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void silentstep3_set_step_pin ( silentstep3_t *ctx, uint8_t state );

/**
 * @brief Silent Step 3 get sg pin function.
 * @details This function returns the SG pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t silentstep3_get_sg_pin ( silentstep3_t *ctx );

/**
 * @brief Silent Step 3 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #silentstep3_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return None.
 * @note None.
 */
void silentstep3_drive_motor ( silentstep3_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // SILENTSTEP3_H

/*! @} */ // silentstep3

// ------------------------------------------------------------------------ END
