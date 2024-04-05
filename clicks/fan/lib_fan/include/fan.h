/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file fan.h
 *
 * \brief This file contains API for Fan Click driver.
 *
 * \addtogroup fan Fan Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FAN_H
#define FAN_H

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

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macro Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define FAN_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup register Registers
 * \{
 */
#define FAN_CONFIGURATION         0x20
#define FAN_STATUS                0x24
#define FAN_STALL_STATUS          0x25
#define FAN_SPIN_STATUS           0x26
#define FAN_DRIVE_FAIL_STATUS     0x27
#define FAN_INTERRUPT_ENABLE      0x29
#define FAN_PWM_POLARITY          0x2A
#define FAN_PWM_OUTPUT_CONFIG     0x2B
#define FAN_PWM_BASE_FREQ         0x2D
#define FAN_SETTING               0x30
#define FAN_DIVIDE                0x31
#define FAN_CONFIG1               0x32
#define FAN_CONFIG2               0x33
#define FAN_GAIN                  0x35
#define FAN_SPINUP                0x36
#define FAN_MAX_STEP              0x37
#define FAN_MIN_DRIVE             0x38
#define FAN_VALID_TACH            0x39
#define FAN_FAIL_LOW              0x3A
#define FAN_FAIL_HIGH             0x3B
#define FAN_TACH_TARGET_LOW       0x3C
#define FAN_TACH_TARGET_HIGH      0x3D
#define FAN_TACH_READING_HIGH     0x3E
#define FAN_TACH_READING_LOW      0x3F
#define FAN_SOFTWARE_LOCK         0xEF
#define FAN_PRODUCT_ID            0xFD
#define FAN_MANUFACTUERE_ID       0xFE
#define FAN_REVISION              0xFF

#define FAN_RPM_MIN_500           0x00
#define FAN_RPM_MIN_1000          0x01
#define FAN_RPM_MIN_2000          0x02
#define FAN_RPM_MIN_4000          0x03
#define FAN_EDGE_1_POLE           0x00
#define FAN_EDGE_2_POLE           0x01
#define FAN_EDGE_3_POLE           0x02
#define FAN_EDGE_4_POLE           0x03
#define FAN_UPDATE_100MS          0x00
#define FAN_UPDATE_200MS          0x01
#define FAN_UPDATE_300MS          0x02
#define FAN_UPDATE_400MS          0x03
#define FAN_UPDATE_500MS          0x04
#define FAN_UPDATE_800MS          0x05
#define FAN_UPDATE_1200MS         0x06
#define FAN_UPDATE_1600MS         0x07
#define FAN_DERIVATIVE_NONE       0x00
#define FAN_DERIVATIVE_BASIC      0x01
#define FAN_DERIVATIVE_STEP       0x02
#define FAN_DERIVATIVE_BOTH       0x03
#define FAN_RPM_0                 0x00
#define FAN_RPM_50                0x01
#define FAN_RPM_100               0x02
#define FAN_RPM_200               0x03
#define FAN_GAIN_1X               0x00
#define FAN_GAIN_2X               0x01
#define FAN_GAIN_4X               0x02
#define FAN_GAIN_8X               0x03
#define FAN_DRIVE_CNT_DISABLED     0x0
#define FAN_DRIVE_CNT_16           0x0
#define FAN_DRIVE_CNT_32           0x0
#define FAN_DRIVE_CNT_64           0x0
#define FAN_SPINUP_30PERCENT      0x00
#define FAN_SPINUP_35PERCENT      0x01
#define FAN_SPINUP_40PERCENT      0x02
#define FAN_SPINUP_45PERCENT      0x03
#define FAN_SPINUP_50PERCENT      0x04
#define FAN_SPINUP_55PERCENT      0x05
#define FAN_SPINUP_60PERCENT      0x06
#define FAN_SPINUP_65PERCENT      0x07
#define FAN_SPINUP_250MS          0x00
#define FAN_SPINUP_500MS          0x00
#define FAN_SPINUP_1S             0x00
#define FAN_SPINUP_2S             0x00
/** \} */

/**
 * \defgroup static Static Variables
 * \{
 */
#define EN_ALGO  ( 1 << 7 )
#define RANGE  ( 1 << 5 ) | ( 1 << 6 )
#define RANGE_BIT  5
#define EDGES  ( 1 << 3 ) | ( 1 << 4 )
#define EDGES_BIT  3
#define UPDATE  ( 1 << 0 ) | ( 1 << 1 ) | ( 1 << 2 )
#define UPDATE_BIT  0
#define EN_RAMP  ( 1 << 6 )
#define GLITCH_EN  ( 1 << 5 )
#define DER_OPT  ( 1 << 3 ) | ( 1 << 4 )
#define DER_OPT_BIT  3
#define ERR_RNG  ( 1 << 2 ) | ( 1 << 1 )
#define ERR_RNG_BIT  1
#define GAIND  ( 1 << 5 ) | ( 1 << 4 )
#define GAIND_BIT  4
#define GAINI  ( 1 << 3 ) | ( 1 << 2 )
#define GAINI_BIT  2
#define GAINP  ( 1 << 1 ) | ( 1 << 0 )
#define GAINP_BIT  0
#define NOKICK  ( 1 << 5 )
#define DRIVE_FAIL_CNT  ( 1 << 7 ) | ( 1 << 6 )
#define DRIVE_FAIL_CNT_BIT  6
#define SPIN_LVL  ( 1 << 4 ) | ( 1 << 3 ) | ( 1 << 2 )
#define SPIN_LVL_BIT  2
#define SPINUP_TIME  ( 1 << 1 ) | ( 1 << 0 )
#define SPINUP_TIME_BIT  0
/** \} */

/**
 * \defgroup time Time Definition
 * \{
 */
#define TACH_CONSTANT 3932160
#define SEC_MIN 60
/** \} */

/**
 * \defgroup addr Device Address
 * \{
 */
#define FAN_DEV_ADDR  0x2F
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Fan setup definition.
 */
typedef struct
{
  uint8_t  number_of_poles;
  uint8_t  number_of_edges;
  uint8_t  range;
  uint8_t  mul;
  double   frequency;
  uint8_t  fsc_mode;
  uint8_t  software_lock;

} fan_setup_t;

/**
 * @brief Fan setup configuration.
 */
typedef struct
{
  uint8_t  poles_cfg;
  uint8_t  edges_cfg;
  uint8_t  range_cfg;
  uint8_t  mul_cfg;
  double   frequency_cfg;
  uint8_t  mode_cfg;
  uint8_t  lock_cfg;

} fan_setup_cfg_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    digital_in_t  int_pin;          /**< Interrupt event pin object. >*/
    i2c_master_t  i2c;              /**< Communication module object. >*/
    uint8_t       slave_address;    /**< Device slave address. >*/
    fan_setup_t   fan_setup;        /**< Fan setup. >*/

} fan_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    pin_name_t       scl;              /**< Module clock pin name. >*/
    pin_name_t       sda;              /**< Module data pin name. >*/
    pin_name_t       int_pin;          /**< Interrupt event pin name. >*/
    uint32_t         i2c_speed;        /**< Module speed. >*/
    uint8_t          i2c_address;      /**< Device slave address. >*/
    fan_setup_cfg_t  fan_setup_cfg;    /**< Fan configuration setup. >*/

} fan_cfg_t;

/** \} */ // End type group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Functions
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param[out] cfg Click configuration structure. See #fan_cfg_t object
 * definition.
 *
 * @description This function initializes click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state.
 */
void
fan_cfg_setup ( fan_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function executes a default configuration for the FAN click.
 */
err_t
fan_default_cfg ( fan_t *ctx );

/**
 * @brief Initialization function.
 *
 * @param[out] ctx Click object. See #fan_t object definition.
 * @param[in] cfg Click configuration structure. See #fan_cfg_t object
 * definition.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click board.
 */
err_t
fan_init ( fan_t *ctx, fan_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] reg Register address.
 * @param[in] data_in Data to be written.
 * @param[in] len Number of bytes to be written.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function writes the desired number of data bytes starting
 * from the selected register.
 */
err_t
fan_generic_write ( fan_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] reg Register address.
 * @param[out] data_out Output data buffer.
 * @param[in] len Number of bytes to be read.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads the desired number of data bytes starting
 * from the selected register.
 */
err_t
fan_generic_read ( fan_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Write byte function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] reg Register address.
 * @param[in] data_in Data byte to be written.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function writes one byte of data to the selected register.
 */
err_t
fan_write_byte ( fan_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Read byte function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] reg Register address.
 * @param[out] data_out Output data.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads one byte of data from the selected register.
 */
err_t
fan_read_byte ( fan_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Fan lock registers function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] lock Lock command.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Lock Column describes the locking mechanism, if any, used
 * for individual registers. All SWL registers are Software Locked and therefore
 * made read-only when the LOCK bit is set..
 */
err_t
fan_lock_registers ( fan_t *ctx, uint8_t lock );

/**
 * @brief Get device info function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[out] info Output info.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description 1 - Product ID, 2 - Manufacturer ID, 3 - Revision number.
 */
err_t
fan_device_info ( fan_t *ctx, uint8_t *info );

/**
 * @brief Set valid tach function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] tach Tach value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Valid TACH Count register stores the maximum TACH Reading
 * Register value to indicate that the fan is spinning properly. The value is
 * referenced at the end of the Spin Up Routine to determine if the fan has
 * started operating and decide if the device needs to retry.
 */
err_t
fan_set_valid_tach ( fan_t *ctx, uint16_t tach );

/**
 * @brief Get valid tach function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[out] data_out Output tach value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Valid TACH Count register stores the maximum TACH Reading
 * Register value to indicate that the fan is spinning properly. The value is
 * referenced at the end of the Spin Up Routine to determine if the fan has
 * started operating and decide if the device needs to retry.
 */
err_t
fan_get_valid_tach ( fan_t *ctx, uint16_t *data_out );

/**
 * @brief Get drive band fail function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[out] data_out Output read value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Drive Fail Band Registers store the number of tach
 * counts used by the Fan Drive Fail detection circuitry. This circuitry is
 * activated when the fan drive setting high byte is at FFh. When it is enabled,
 * the actual measured fan speed is compared against the target fan speed. These
 * registers are only used when the FSC is active.
 */
err_t
fan_get_driveband_fail ( fan_t *ctx, uint16_t *data_out );

/**
 * @brief Set target tach function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] tach Target tach value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The TACH Target Registers hold the target tachometer value that
 * is maintained by the RPM-based Fan Speed Control Algorithm.
 */
err_t
fan_set_target_tach ( fan_t *ctx, uint16_t tach );

/**
 * @brief Get tach function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[out] data_out Output tach value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The TACH Count register stores the current TACH Reading
 * Register value to show the current reading of rotation per minute.
 */
err_t
fan_get_tach ( fan_t *ctx, uint16_t *data_out );

/**
 * @brief Enable fan control algorithm function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] fsc True enable fan control, false manual mode.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description This function enable Fan Control Algorithm.
 */
err_t
fan_enable_fsc ( fan_t *ctx, uint8_t fsc );

/**
 * @brief Set number of edges that needs to be detected function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] range Target value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Adjusts the range of reported and programmed tachometer reading
 * values. The RANGE bits determine the weighting of all TACH values.
 */
err_t
fan_set_range ( fan_t *ctx, uint8_t range );

/**
 * @brief Set number of edges on fan function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] edges Target value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Determines the minimum number of edges that must be detected on
 * the TACHx signal to determine a single rotation. A typical fan measured 5
 * edges (for a 2-pole fan). For more accurate tachometer measurement, the
 * minimum number of edges measured may be increased.
 */
err_t
fan_set_edges ( fan_t *ctx, uint8_t edges );

/**
 * @brief Update time function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] update Time to be updated.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description determines the base time between fan driver updates. The Update
 * Time, along with the Fan Step Register, is used to control the ramp rate of
 * the drive response to provide a cleaner transition of the actual fan
 * operation as the desired fan speed changes.
 */
err_t
fan_set_update ( fan_t *ctx, uint8_t update );

/**
 * @brief Ramp up mode function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] tamp_control True enable ramp rate control.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Enables ramp rate control when the fan driver is operated in the
 * Direct Setting Mode.
 */
err_t
fan_enable_ramp ( fan_t *ctx, uint8_t ramp_control );

/**
 * @brief Glitch enable function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] glitch True enable glitch filter.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Disables the low pass glitch filter that removes high frequency
 * noise injected on the TACHx pin.
 */
err_t
fan_enable_glitch ( fan_t *ctx, uint8_t glitch );

/**
 * @brief Set derivative function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] derivative Basic derivative / Step Derivative / Both.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Control some of the advanced options that affect the derivative
 * portion of the RPM-based Fan Speed Control Algorithm.
 */
err_t
fan_set_derivative ( fan_t *ctx, uint8_t derivative );

/**
 * @brief Set error range function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] error Target error value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Control some of the advanced options that affect the error
 * window. When the measured fan speed is within the programmed error window
 * around the target speed, then the fan drive setting is not updated.
 */
err_t
fan_set_error_range ( fan_t *ctx, uint8_t error );

/**
 * @brief Set gain D function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] gain Target gain value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Control some of the advanced options that affect the derivative
 * portion of the RPM-based Fan Speed Control Algorithm. The Gain register
 * stores the gain terms used by the proportional and integral portions of the
 * RPM-based Fan Speed Control Algorithm. These gain terms are used as the KD,
 * KI, and KP gain terms in a classic PID control solution.
 */
err_t
fan_set_gaind ( fan_t *ctx, uint8_t gain );

/**
 * @brief Set drive fail counter function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] count Disabled / 16 / 32 / 64.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Determines how many update cycles are used for the Drive Fail
 * detection function.
 */
err_t
fan_set_drivefail ( fan_t *ctx, uint8_t count );

/**
 * @brief No kick enable function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] no_kick True enable no kick functionality.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Turns ON no kick functionality.
 */
err_t
fan_enable_no_kick ( fan_t *ctx, uint8_t no_kick );

/**
 * @brief Set spin level function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] spin Target spin level.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description Determines if the Spin Up Routine will drive the fan to 100%
 * duty cycle for 1/4 of the programmed spin up time before driving it at the
 * programmed level.
 */
err_t
fan_set_spin_level ( fan_t *ctx, uint8_t spin );

/**
 * @brief Set spin time function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] time Target time value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Spin Up Configuration register controls the settings of
 * Spin Up Routine.
 */
err_t
fan_set_spin_time ( fan_t *ctx, uint8_t time );

/**
 * @brief Set maximum step function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] step Maximum step value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Max Step register, along with the Update Time, controls
 * the ramp rate of the fan driver response calculated by the RPM-based Fan
 * Speed Control Algorithm. The value of the register represents the maximum
 * step size the fan driver will take between update times.
 */
err_t
fan_set_max_step ( fan_t *ctx, uint8_t step );

/**
 * @brief Set minimum drive function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] min_drive Minimum drive value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Minimum Drive register stores the minimum drive setting
 * for the RPM-based Fan Speed Control Algorithm. The RPM-based Fan Speed
 * Control Algorithm will not drive the fan at a level lower than the minimum
 * drive unless the target Fan Speed is set at FFh.
 */
err_t
fan_set_min_drive ( fan_t *ctx, double min_drive );

/**
 * @brief Update multiplier function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 *
 * @description Performs update of multiplier.
 */
void
fan_update_multiplier ( fan_t *ctx );

/**
 * @brief Set external clock speed function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] freq Target frequency.
 *
 * @description Specifies external clock speed if different from standard.
 */
void
fan_set_clock ( fan_t *ctx, double freq );

/**
 * @brief Fan configuration function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] cfg Target configuration value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Configuration Register controls the basic functionality of
 * the EMC2301.
 */
err_t
fan_device_cfg ( fan_t *ctx, uint8_t cfg );

/**
 * @brief Get fan status function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[out] data_out Output status value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Status register indicates that the fan driver has
 * stalled or failed or that the Watchdog Timer has expired.
 */
err_t
fan_get_status ( fan_t *ctx, uint8_t *data_out );

/**
 * @brief Get fan stall status function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[out] data_out Output status value.
 *              - FAN_STALL      = 1
 *              - FAN_SPIN       = 2
 *              - FAN_DRIVE_FAIL = 4
 *              - FAN_WATCH      = 128
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The TACH Target Registers hold the target tachometer value that
 * is maintained by the RPM-based Fan Speed Control Algorithm.
 */
err_t
fan_get_stall_status ( fan_t *ctx, uint8_t *data_out );

/**
 * @brief Get spin status function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[out] data_out Output status value.
 *              - FAN_SPIN has failed = 1
 *              - FAN_SPIN ok         = 0
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Spin Status register indicates that the fan driver has
 * failed to spin-up.
 */
err_t
fan_get_spin_status ( fan_t *ctx, uint8_t *data_out );

/**
 * @brief Get fan drive fail status function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[out] data_out Output status value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Drive Fail Status register indicates that the fan driver
 * cannot drive to the programmed speed even at 100% duty cycle.
 */
err_t
fan_get_drive_fail ( fan_t *ctx, uint8_t *data_out );

/**
 * @brief Enable / disable external interrupts function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] enable True enable external interrupts.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Interrupt Enable controls the masking for the Fan
 * channel. When a channel is enabled, it will cause the ALERT# pin to be
 * asserted when an error condition is detected.
 */
err_t
fan_interrupts ( fan_t *ctx, uint8_t enable );

/**
 * @brief Set PWM base frequency function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] freq Target frequency value.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The PWM Base Frequency register determines the base frequency
 * that is used with the PWM Divide register to determine the final PWM
 * frequency.
 */
err_t
fan_pwm_base ( fan_t *ctx, uint8_t freq );

/**
 * @brief Fan setting function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 * @param[in] percentage Percentage of duty.
 *
 * @return See #err_t definition type of data.
 *            0  - Ok,
 *          (-1) - Error.
 *
 * @description The Fan Setting register always displays the current setting of
 * the fan driver. Reading from the register will report the current fan speed
 * setting of the fan driver regardless of the operating mode. Therefore it is
 * possible that reading from this register will not report data that was
 * previously written into this register.
 */
err_t
fan_setting ( fan_t *ctx, double percentage );

/**
 * @brief Read INT pin function.
 *
 * @param[in] ctx Click object. See #fan_t object definition.
 *
 * @return True or false.
 *
 * @description Reads the current digital level of INT pin.
 */
uint8_t
fan_read_int_pin ( fan_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // FAN_H

/** \} */ // End public_function group
/// \}    // End click driver group
/*! @} */
// ------------------------------------------------------------------------- END
