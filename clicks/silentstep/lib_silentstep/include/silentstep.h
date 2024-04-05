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
 * @file silentstep.h
 * @brief This file contains API for Silent Step Click Driver.
 */

#ifndef SILENTSTEP_H
#define SILENTSTEP_H

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
 * @addtogroup silentstep Silent Step Click Driver
 * @brief API for configuring and manipulating Silent Step Click driver.
 * @{
 */

/**
 * @defgroup silentstep_reg Silent Step Registers List
 * @brief List of registers of Silent Step Click driver.
 */

/**
 * @addtogroup silentstep_reg
 * @{
 */

 /**
 * @brief Silent Step registers.
 * @details Specified registers of Silent Step Click driver.
 */
#define SILENTSTEP_REG_GCONF                    0x00
#define SILENTSTEP_REG_GSTAT                    0x01
#define SILENTSTEP_REG_IFCNT                    0x02
#define SILENTSTEP_REG_SLAVECONF                0x03
#define SILENTSTEP_REG_IOIN                     0x04
#define SILENTSTEP_REG_X_COMPARE                0x05
#define SILENTSTEP_REG_IHOLD_IRUN               0x10
#define SILENTSTEP_REG_TPOWERDOWN               0x11
#define SILENTSTEP_REG_TSTEP                    0x12
#define SILENTSTEP_REG_TPWMTHRS                 0x13
#define SILENTSTEP_REG_TCOOLTHRS                0x14
#define SILENTSTEP_REG_THIGH                    0x15
#define SILENTSTEP_REG_RAMP_MODE                0x20
#define SILENTSTEP_REG_XACTUAL                  0x21
#define SILENTSTEP_REG_VACTUAL                  0x22
#define SILENTSTEP_REG_VSTART                   0x23
#define SILENTSTEP_REG_A1                       0x24
#define SILENTSTEP_REG_V1                       0x25
#define SILENTSTEP_REG_AMAX                     0x26
#define SILENTSTEP_REG_VMAX                     0x27
#define SILENTSTEP_REG_DMAX                     0x28
#define SILENTSTEP_REG_D1                       0x2A
#define SILENTSTEP_REG_VSTOP                    0x2B
#define SILENTSTEP_REG_TZEROWAIT                0x2C
#define SILENTSTEP_REG_XTARGET                  0x2D
#define SILENTSTEP_REG_VDCMIN                   0x33
#define SILENTSTEP_REG_SW_MODE                  0x34
#define SILENTSTEP_REG_RAMP_STAT                0x35
#define SILENTSTEP_REG_XLATCH                   0x36
#define SILENTSTEP_REG_ENCMODE                  0x38
#define SILENTSTEP_REG_X_ENC                    0x39
#define SILENTSTEP_REG_ENC_CONST                0x3A
#define SILENTSTEP_REG_ENC_STATUS               0x3B
#define SILENTSTEP_REG_ENC_LATCH                0x3C
#define SILENTSTEP_REG_MSLUT_0                  0x60
#define SILENTSTEP_REG_MSLUT_1                  0x61
#define SILENTSTEP_REG_MSLUT_2                  0x62
#define SILENTSTEP_REG_MSLUT_3                  0x63
#define SILENTSTEP_REG_MSLUT_4                  0x64
#define SILENTSTEP_REG_MSLUT_5                  0x65
#define SILENTSTEP_REG_MSLUT_6                  0x66
#define SILENTSTEP_REG_MSLUT_7                  0x67
#define SILENTSTEP_REG_MSLUTSEL                 0x68
#define SILENTSTEP_REG_MSLUTSTART               0x69
#define SILENTSTEP_REG_MSCNT                    0x6A
#define SILENTSTEP_REG_MSCURACT                 0x6B
#define SILENTSTEP_REG_CHOPCONF                 0x6C
#define SILENTSTEP_REG_COOLCONF                 0x6D
#define SILENTSTEP_REG_DCCTRL                   0x6E
#define SILENTSTEP_REG_DRV_STATUS               0x6F
#define SILENTSTEP_REG_PWMCONF                  0x70
#define SILENTSTEP_REG_PWM_SCALE                0x71
#define SILENTSTEP_REG_ENCM_CTRL                0x72
#define SILENTSTEP_REG_LOST_STEPS               0x73

/*! @} */ // silentstep_reg

/**
 * @defgroup silentstep_set Silent Step Registers Settings
 * @brief Settings for registers of Silent Step Click driver.
 */

/**
 * @addtogroup silentstep_set
 * @{
 */

/**
* @brief Silent Step version settings.
* @details Specified version settings of Silent Step Click driver.
*/
#define SILENTSTEP_IOIN_VERSION_MASK            0xFF000000ul
#define SILENTSTEP_IOIN_VERSION_DEFAULT         0x11000000ul

/**
 * @brief Silent Step direction setting.
 * @details Specified setting for direction of Silent Step Click driver.
 */
#define SILENTSTEP_DIR_CW                       0
#define SILENTSTEP_DIR_CCW                      1

/**
 * @brief Silent Step pin logic state setting.
 * @details Specified setting for pin logic state of Silent Step Click driver.
 */
#define SILENTSTEP_PIN_STATE_LOW                0
#define SILENTSTEP_PIN_STATE_HIGH               1

/**
 * @brief Silent Step device speed settings.
 * @details Specified setting for rotation speed.
 */
#define SILENTSTEP_SPEED_VERY_SLOW              0
#define SILENTSTEP_SPEED_SLOW                   1
#define SILENTSTEP_SPEED_MEDIUM                 2
#define SILENTSTEP_SPEED_FAST                   3
#define SILENTSTEP_SPEED_VERY_FAST              4

/**
 * @brief Silent Step off time settings.
 * @details Specified setting for off time that controls duration of slow decay phase.
 */
#define SILENTSTEP_TOFF_MASK                    0x0000000Ful
#define SILENTSTEP_TOFF_SHIFT                   0
#define SILENTSTEP_TOFF_DRIVER_DISABLE          0
#define SILENTSTEP_TOFF_MIN                     1
#define SILENTSTEP_TOFF_DEFAULT                 4
#define SILENTSTEP_TOFF_MAX                     15

/**
 * @brief Silent Step step resolution settings.
 * @details Specified setting for micro step resolution.
 */
#define SILENTSTEP_MRES_MASK                    0x0F000000ul
#define SILENTSTEP_MRES_SHIFT                   24
#define SILENTSTEP_MRES_256                     0
#define SILENTSTEP_MRES_128                     1
#define SILENTSTEP_MRES_64                      2
#define SILENTSTEP_MRES_32                      3
#define SILENTSTEP_MRES_16                      4
#define SILENTSTEP_MRES_8                       5
#define SILENTSTEP_MRES_4                       6
#define SILENTSTEP_MRES_2                       7
#define SILENTSTEP_MRES_FULLSTEP                8

/**
 * @brief Silent Step run current settings.
 * @details Specified setting for motor run current.
 */
#define SILENTSTEP_IRUN_MASK                    0x00000F00ul
#define SILENTSTEP_IRUN_SHIFT                   8
#define SILENTSTEP_IRUN_MIN                     0
#define SILENTSTEP_IRUN_DEFAULT                 2
#define SILENTSTEP_IRUN_MAX                     31

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b silentstep_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SILENTSTEP_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define SILENTSTEP_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // silentstep_set

/**
 * @defgroup silentstep_map Silent Step MikroBUS Map
 * @brief MikroBUS pin mapping of Silent Step Click driver.
 */

/**
 * @addtogroup silentstep_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Silent Step Click to the selected MikroBUS.
 */
#define SILENTSTEP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.spm  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sdm  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dir  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // silentstep_map
/*! @} */ // silentstep

/**
 * @brief Silent Step Click context object.
 * @details Context object definition of Silent Step Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t spm;          /**< SPI mode enable pin (active high). */
    digital_out_t sdm;          /**< SD mode enable pin (active high). */
    digital_out_t step;         /**< Step signal pin. */
    digital_out_t dir;          /**< Direction control pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} silentstep_t;

/**
 * @brief Silent Step Click configuration object.
 * @details Configuration object definition of Silent Step Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t spm;             /**< SPI mode enable pin (active high). */
    pin_name_t sdm;             /**< SD mode enable pin (active high). */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t dir;             /**< Direction control pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} silentstep_cfg_t;

/**
 * @brief Silent Step Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SILENTSTEP_OK = 0,
    SILENTSTEP_ERROR = -1

} silentstep_return_value_t;

/*!
 * @addtogroup silentstep Silent Step Click Driver
 * @brief API for configuring and manipulating Silent Step Click driver.
 * @{
 */

/**
 * @brief Silent Step configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #silentstep_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void silentstep_cfg_setup ( silentstep_cfg_t *cfg );

/**
 * @brief Silent Step initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #silentstep_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep_init ( silentstep_t *ctx, silentstep_cfg_t *cfg );

/**
 * @brief Silent Step default configuration function.
 * @details This function executes a default configuration of Silent Step
 * click board.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t silentstep_default_cfg ( silentstep_t *ctx );

/**
 * @brief Silent Step write reg function.
 * @details This function writes a desired 32-bit data to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep_write_reg ( silentstep_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief Silent Step read reg function.
 * @details This function reads 32-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 32-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep_read_reg ( silentstep_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief Silent Step check com function.
 * @details This function checks the SPI communication by reading and verifying the device version.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep_check_com ( silentstep_t *ctx );

/**
 * @brief Silent Step set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void silentstep_set_direction ( silentstep_t *ctx, uint8_t dir );

/**
 * @brief Silent Step switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void silentstep_switch_direction ( silentstep_t *ctx );

/**
 * @brief Silent Step set spm pin function.
 * @details This function sets the SPM pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void silentstep_set_spm_pin ( silentstep_t *ctx, uint8_t state );

/**
 * @brief Silent Step set sdm pin function.
 * @details This function sets the SDM pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void silentstep_set_sdm_pin ( silentstep_t *ctx, uint8_t state );

/**
 * @brief Silent Step set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void silentstep_set_step_pin ( silentstep_t *ctx, uint8_t state );

/**
 * @brief Silent Step set toff function.
 * @details This function sets the off time and driver enable bits in CHOPCONF register.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] toff : TOFF bits setting [0-15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep_set_toff ( silentstep_t *ctx, uint8_t toff );

/**
 * @brief Silent Step set step res function.
 * @details This function sets the microstep resolution bits in CHOPCONF register.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] mres : MRES bits setting:
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
err_t silentstep_set_step_res ( silentstep_t *ctx, uint8_t mres );

/**
 * @brief Silent Step set run current function.
 * @details This function sets the motor run current bits in IHOLD_IRUN register.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
 * @param[in] irun : IRUN bits setting [0-31].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t silentstep_set_run_current ( silentstep_t *ctx, uint8_t irun );

/**
 * @brief Silent Step driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #silentstep_t object definition for detailed explanation.
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
void silentstep_drive_motor ( silentstep_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // SILENTSTEP_H

/*! @} */ // silentstep

// ------------------------------------------------------------------------ END
