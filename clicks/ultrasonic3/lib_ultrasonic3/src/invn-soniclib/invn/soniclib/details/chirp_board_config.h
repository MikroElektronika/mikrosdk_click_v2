/*
 * chirp_board_config.h
 *
 * This file defines default values for the required symbols used to build an
 * application with the Chirp SonicLib API and driver.  These symbols are used
 * for static array allocations and counters in SonicLib (and often
 * applications), and are based on the number of specific resources on the
 * target board.
 *
 * For this file to be included, you must define the symbol
 * INVN_SONICLIB_INTERNAL_BOARD_CONFIG in your build system, for example, using
 * the gcc -D option. Otherwise, soniclib will look for this header relative
 * to your include path. That is, if you do not define the above symbol, you
 * MUST have chirp_board_config.h directly on your include path.
 *
 * In the latter case, you can start with a copy of this file placed somewhere
 * in your include path, then modify it to your liking.
 *
 * Three symbols are conditionally defined:
 *  INCLUDE_WHITNEY_SUPPORT - includes support for CHx01 parts
 *  CHIRP_MAX_NUM_SENSORS - the number of possible sensor devices (i.e. the
 *                          number of sensor ports)
 *  CHIRP_NUM_BUSES - the number of I2C/SPI buses on the board that are used
 *                    for those sensor ports
 *
 * Two additional symbols are conditionally defined for shasta only:
 *  CHIRP_SENSOR_INT_PIN - Pin used for interrupts. 1=INT1, 2=INT2
 *  CHIPR_SENSOR_TRIG_PIN - Pin used for triggering. 1=INT1, 2=INT2
 *
 * If you wish to override these values, then you must compile with different
 * symbol definitions (-D option with gcc).
 *
 * For example, to build with 2 max sensors, 1 bus, and with shasta
 * (ICU-x0201) support, use:
 *
 * -DCHIRP_MAX_NUM_SENSORS=2 -DCHIRP_NUM_BUSES=1 -DINCLUDE_SHASTA_SUPPORT
 */

#ifndef CHIRP_BOARD_CONFIG_H_
#define CHIRP_BOARD_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(INCLUDE_SHASTA_SUPPORT) && !defined(INCLUDE_WHITNEY_SUPPORT)
#define INCLUDE_WHITNEY_SUPPORT
#endif

/* Settings for the Chirp driver test setup */
#ifndef CHIRP_MAX_NUM_SENSORS
#define CHIRP_MAX_NUM_SENSORS 4  // maximum possible number of sensor devices
#endif

#ifndef CHIRP_NUM_BUSES
#define CHIRP_NUM_BUSES 2  // number of I2C/SPI buses used by sensors
#endif

#ifndef CHIRP_RTC_CAL_PULSE_MS
#define CHIRP_RTC_CAL_PULSE_MS 100 /* Default length of RTC calibration pulse */
#endif

#ifdef INCLUDE_SHASTA_SUPPORT
#ifndef CHIRP_SENSOR_INT_PIN
#define CHIRP_SENSOR_INT_PIN 1
#endif
#ifndef CHIRP_SENSOR_TRIG_PIN
#define CHIRP_SENSOR_TRIG_PIN 1
#endif
#endif  // INCLUDE_SHASTA_SUPPORT

#ifdef __cplusplus
}
#endif

#endif /* CHIRP_BOARD_CONFIG_H_ */
