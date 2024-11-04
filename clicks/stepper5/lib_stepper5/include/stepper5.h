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
 * @file stepper5.h
 * @brief This file contains API for Stepper 5 Click Driver.
 */

#ifndef STEPPER5_H
#define STEPPER5_H

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
#include "drv_uart.h"

/*!
 * @addtogroup stepper5 Stepper 5 Click Driver
 * @brief API for configuring and manipulating Stepper 5 Click driver.
 * @{
 */

/**
 * @defgroup stepper5_reg Stepper 5 Registers List
 * @brief List of registers of Stepper 5 Click driver.
 */

/**
 * @addtogroup stepper5_reg
 * @{
 */

 /**
 * @brief Stepper 5 registers.
 * @details Specified registers of Stepper 5 Click driver.
 */
#define STEPPER5_REG_GCONF                      0x00
#define STEPPER5_REG_GSTAT                      0x01
#define STEPPER5_REG_IFCNT                      0x02
#define STEPPER5_REG_SLAVECONF                  0x03
#define STEPPER5_REG_OTP_PROG                   0x04
#define STEPPER5_REG_OTP_READ                   0x05
#define STEPPER5_REG_IOIN                       0x06
#define STEPPER5_REG_FACTORY_CONF               0x07
#define STEPPER5_REG_IHOLD_IRUN                 0x10
#define STEPPER5_REG_TPOWERDOWN                 0x11
#define STEPPER5_REG_TSTEP                      0x12
#define STEPPER5_REG_TPWMTHRS                   0x13
#define STEPPER5_REG_VACTUAL                    0x22
#define STEPPER5_REG_MSCNT                      0x6A
#define STEPPER5_REG_MSCURACT                   0x6B
#define STEPPER5_REG_CHOPCONF                   0x6C
#define STEPPER5_REG_COOLCONF                   0x6D
#define STEPPER5_REG_DRV_STATUS                 0x6F
#define STEPPER5_REG_PWMCONF                    0x70
#define STEPPER5_REG_PWM_SCALE                  0x71
#define STEPPER5_REG_PWM_AUTO                   0x72

/*! @} */ // stepper5_reg

/**
 * @defgroup stepper5_set Stepper 5 Device Settings
 * @brief Settings for registers of Stepper 5 Click driver.
 */

/**
 * @addtogroup stepper5_set
 * @{
 */

/**
* @brief Stepper 5 version settings.
* @details Specified version settings of Stepper 5 Click driver.
*/
#define STEPPER5_IOIN_VERSION_MASK              0xFF000000ul
#define STEPPER5_IOIN_VERSION_DEFAULT           0x20000000ul

/**
 * @brief Stepper 5 direction setting.
 * @details Specified setting for direction of Stepper 5 Click driver.
 */
#define STEPPER5_DIR_CW                         0
#define STEPPER5_DIR_CCW                        1

/**
 * @brief Stepper 5 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 5 Click driver.
 */
#define STEPPER5_PIN_STATE_LOW                  0
#define STEPPER5_PIN_STATE_HIGH                 1

/**
 * @brief Stepper 5 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER5_SPEED_VERY_SLOW                0
#define STEPPER5_SPEED_SLOW                     1
#define STEPPER5_SPEED_MEDIUM                   2
#define STEPPER5_SPEED_FAST                     3
#define STEPPER5_SPEED_VERY_FAST                4

/**
 * @brief Stepper 5 GCONF register settings.
 * @details Specified setting for GCONF register of Stepper 5 Click driver.
 */
#define STEPPER5_GCONF_I_SCALE_ANALOG_INT_5V    0x00000000ul
#define STEPPER5_GCONF_I_SCALE_ANALOG_EXT_VREF  0x00000001ul
#define STEPPER5_GCONF_INTERNAL_RSENSE_EXT      0x00000000ul
#define STEPPER5_GCONF_INTERNAL_RSENSE_INT      0x00000002ul
#define STEPPER5_GCONF_EN_SPREAD_CYCLE_SCHOP    0x00000000ul
#define STEPPER5_GCONF_EN_SPREAD_CYCLE_SCYCLE   0x00000004ul
#define STEPPER5_GCONF_SHAFT_INVERSE            0x00000008ul
#define STEPPER5_GCONF_INDEX_OTPW_FIRST_MSTEP   0x00000000ul
#define STEPPER5_GCONF_INDEX_OTPW_OVERTEMP      0x00000010ul
#define STEPPER5_GCONF_INDEX_STEP_OTPW          0x00000000ul
#define STEPPER5_GCONF_INDEX_STEP_INT           0x00000020ul
#define STEPPER5_GCONF_PDN_DISABLE_SSC_REDUCT   0x00000000ul
#define STEPPER5_GCONF_PDN_DISABLE_UART_EN      0x00000040ul
#define STEPPER5_GCONF_MSTEP_REG_SELECT_MS_PINS 0x00000000ul
#define STEPPER5_GCONF_MSTEP_REG_SELECT_MSTEP   0x00000080ul
#define STEPPER5_GCONF_MULTISTEP_FILT_DIS       0x00000000ul
#define STEPPER5_GCONF_MULTISTEP_FILT_EN        0x00000100ul
#define STEPPER5_GCONF_TEST_MODE_NORMAL         0x00000000ul
#define STEPPER5_GCONF_TEST_MODE_ENN            0x00000200ul

/**
 * @brief Stepper 5 off time settings.
 * @details Specified setting for off time that controls duration of slow decay phase.
 */
#define STEPPER5_TOFF_MASK                      0x0000000Ful
#define STEPPER5_TOFF_SHIFT                     0
#define STEPPER5_TOFF_DRIVER_DISABLE            0
#define STEPPER5_TOFF_MIN                       1
#define STEPPER5_TOFF_DEFAULT                   4
#define STEPPER5_TOFF_MAX                       15

/**
 * @brief Stepper 5 step resolution settings.
 * @details Specified setting for micro step resolution.
 */
#define STEPPER5_MRES_MASK                      0x0F000000ul
#define STEPPER5_MRES_SHIFT                     24
#define STEPPER5_MRES_256                       0
#define STEPPER5_MRES_128                       1
#define STEPPER5_MRES_64                        2
#define STEPPER5_MRES_32                        3
#define STEPPER5_MRES_16                        4
#define STEPPER5_MRES_8                         5
#define STEPPER5_MRES_4                         6
#define STEPPER5_MRES_2                         7
#define STEPPER5_MRES_FULLSTEP                  8

/**
 * @brief Stepper 5 run current settings.
 * @details Specified setting for motor run current.
 */
#define STEPPER5_IRUN_MASK                      0x00000F00ul
#define STEPPER5_IRUN_SHIFT                     8
#define STEPPER5_IRUN_MIN                       0
#define STEPPER5_IRUN_DEFAULT                   16
#define STEPPER5_IRUN_MAX                       31

/**
* @brief Stepper 5 UART settings.
* @details Specified UART settings of Stepper 5 Click driver.
*/
#define STEPPER5_UART_SYNC_BYTE                 0x05
#define STEPPER5_UART_SLAVE_ADDRESS             0x00
#define STEPPER5_UART_WRITE_BIT                 0x80

/**
 * @brief Stepper 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define STEPPER5_TX_DRV_BUFFER_SIZE             100
#define STEPPER5_RX_DRV_BUFFER_SIZE             300

/*! @} */ // stepper5_set

/**
 * @defgroup stepper5_map Stepper 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 5 Click driver.
 */

/**
 * @addtogroup stepper5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 5 Click to the selected MikroBUS.
 */
#define STEPPER5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.diag = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ind = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // stepper5_map
/*! @} */ // stepper5

/**
 * @brief Stepper 5 Click context object.
 * @details Context object definition of Stepper 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;                  /**< Direction control pin. */
    digital_out_t en;                   /**< Enable output pin (active low). */
    digital_out_t step;                 /**< Step signal pin. */

    // Input pins
    digital_in_t diag;                  /**< Diagnostic pin. */
    digital_in_t ind;                   /**< Configurable index pulse pin. */

    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ STEPPER5_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ STEPPER5_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} stepper5_t;

/**
 * @brief Stepper 5 Click configuration object.
 * @details Configuration object definition of Stepper 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t diag;                    /**< Diagnostic pin. */
    pin_name_t dir;                     /**< Direction control pin. */
    pin_name_t en;                      /**< Enable output pin (active low). */
    pin_name_t step;                    /**< Step signal pin. */
    pin_name_t ind;                     /**< Configurable index pulse pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} stepper5_cfg_t;

/**
 * @brief Stepper 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER5_OK = 0,
    STEPPER5_ERROR = -1

} stepper5_return_value_t;

/*!
 * @addtogroup stepper5 Stepper 5 Click Driver
 * @brief API for configuring and manipulating Stepper 5 Click driver.
 * @{
 */

/**
 * @brief Stepper 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper5_cfg_setup ( stepper5_cfg_t *cfg );

/**
 * @brief Stepper 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper5_init ( stepper5_t *ctx, stepper5_cfg_t *cfg );

/**
 * @brief Stepper 5 default configuration function.
 * @details This function executes a default configuration of Stepper 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper5_default_cfg ( stepper5_t *ctx );

/**
 * @brief Stepper 5 write reg function.
 * @details This function writes a desired 32-bit data to the selected register 
 * by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return None.
 * @note None.
 */
void stepper5_write_reg ( stepper5_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief Stepper 5 read reg function.
 * @details This function reads 32-bit data from the selected register by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 32-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper5_read_reg ( stepper5_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief Stepper 5 check com function.
 * @details This function checks the UART communication by reading and verifying the device version.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper5_check_com ( stepper5_t *ctx );

/**
 * @brief Stepper 5 enable device function.
 * @details This function enables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper5_enable_device ( stepper5_t *ctx );

/**
 * @brief Stepper 5 disable device function.
 * @details This function disables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper5_disable_device ( stepper5_t *ctx );

/**
 * @brief Stepper 5 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper5_set_direction ( stepper5_t *ctx, uint8_t dir );

/**
 * @brief Stepper 5 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper5_switch_direction ( stepper5_t *ctx );

/**
 * @brief Stepper 5 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper5_set_step_pin ( stepper5_t *ctx, uint8_t state );

/**
 * @brief Stepper 5 get diag pin function.
 * @details This function returns the DIAG pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper5_get_diag_pin ( stepper5_t *ctx );

/**
 * @brief Stepper 5 get index pin function.
 * @details This function returns the INDEX pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper5_get_index_pin ( stepper5_t *ctx );

/**
 * @brief Stepper 5 set toff function.
 * @details This function sets the off time and driver enable bits in CHOPCONF register.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @param[in] toff : TOFF bits setting [0-15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper5_set_toff ( stepper5_t *ctx, uint8_t toff );

/**
 * @brief Stepper 5 set step res function.
 * @details This function sets the microstep resolution bits in CHOPCONF register.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
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
err_t stepper5_set_step_res ( stepper5_t *ctx, uint8_t mres );

/**
 * @brief Stepper 5 set run current function.
 * @details This function sets the motor run current bits in IHOLD_IRUN register.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
 * @param[in] irun : IRUN bits setting [0-31].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper5_set_run_current ( stepper5_t *ctx, uint8_t irun );

/**
 * @brief Stepper 5 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper5_t object definition for detailed explanation.
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
void stepper5_drive_motor ( stepper5_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER5_H

/*! @} */ // stepper5

// ------------------------------------------------------------------------ END
