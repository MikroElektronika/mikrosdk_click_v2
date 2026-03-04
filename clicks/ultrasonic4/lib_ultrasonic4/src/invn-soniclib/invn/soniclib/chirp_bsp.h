/*! \file chirp_bsp.h
 *
 * \brief User-supplied board support package functions to interface Chirp SonicLib to a specific
 * hardware platform.
 *
 * This file defines the I/O interfaces that allow the standard Chirp SonicLib sensor driver
 * functions to manage one or more sensors on a specific hardware platform.  These include
 * functions to initialize and control the various I/O pins connecting the sensor to the host
 * system, the SPI or I2C communications interface, timer functions, etc.
 *
 * Typically, most of the functions in the BSP are implemented as "wrapper functions" for
 * operations that are provided in the MCU vendor's I/O library.  So, the BSP largely
 * serves as a translation layer for most functions.
 *
 * The board support package developer should not need to modify this header file.  However,
 * that developer is responsible for implementing these support functions for the hardware
 * platform, using the interfaces defined here.  Note that some functions are optional, depending
 * on the specific runtime requirements (e.g. is non-blocking I/O required?) or development needs
 * (e.g. is debugging support needed?).
 *
 * \note All functions are marked as REQUIRED, RECOMMENDED, or OPTIONAL in their indvidual
 * descriptions.  "Recommended" functions are either not used directly by SonicLib (but may be
 * expected by examples and other applications from Chirp) or are only required to support certain
 * operating configurations (e.g. individual device triggering).
 *
 * \note Some BSP functions are only used with a specific generation of Chirp Sensor, either the
 * ICU family or the earlier CH101 & CH201 devices.  The description of these functions will
 * indicate which sensors are applicable.  If not specified, the requirement applies equally
 * to ICU and CH101/CH201 sensors.
 *
 *	### Organization
 *	The file organization for a BSP is intentionally very flexible, so that you may efficiently
 *	use existing code that supports your hardware or otherwise use your own organizing
 *	preferences.
 *
 *	Typically, the required BSP functions are placed in a file called chbsp_NNNN.c, where
 *	NNNN is the board name.  For example, in the Chirp BSP for the Nucleo144 development
 *	board the main file is called chbsp_nucleo144.c, and in the BSP for the Chirp SmartSonic
 *	evaluation, it is called chbsp_chirp_smartsonic.c.
 *
 *	### Sensor Interrupt Handling
 *
 *	In addition to providing the required \a chbsp_xxx() functions as described above, the BSP
 *	must also provide a routine to handle interrupts from the sensor.  Because the handler
 *	routine is not referenced by SonicLib, it can have any name that fits your conventions.
 *
 *	All Chirp sensors use a level change on an interrupt line to indicate the completion of a
 *	measurement (data ready).
 *
 *	ICU family sensors have two different lines that may be used as the interrupt indicator,
 *	INT1 and INT2.  Interrupt and trigger lines for ICU sensors are high when inactive, so the
 *	interrupt is indicated by a transition to a low level.
 *
 *	ICU sensors may be configured for either pulse mode or latching mode by calling the
 *	\a ch_set_interrupt_mode() function from the application.  In pulse mode, the sensor will
 *	indicate an interrupt by briefly (~800ns) bringing the line low then returning it to a high
 *	level.  In latching mode, the sensor will bring the line low and the interrupt handler in the BSP is
 *	responsible for resetting the line to a high (inactive) level.  By default, ICU sensors
 *	use latching mode.
 *
 *	ICU sensors also use the interrupt line for various other events in addition to data ready.
 *	The interrupt type will be passed to the application's callback routine when an interrupt
 *	occurs.
 *
 *	CH101 and CH201 sensors have a single interrupt line that is normally used only for data
 *	ready interrupts.  The line is low when inactive, so the interrupt consists of a brief
 *	high pulse.  CH101/CH201 sensors always use "INT1" routines and interfaces.
 *
 *	#### Notifying SonicLib that a Sensor Interrupt Occurred
 *
 *	The BSP's handler routine that detects that a sensor interrupt has occurred
 *	(typically to indicate completion of a measurement) must notify SonicLib by
 *	calling \a ch_interrupt().  The \a ch_interrupt() function takes two
 *	parameters, a pointer to the ch_group_t descriptor for the group containing
 *	the interrupting sensor, and the device number within the group.
 *
 *	The sensor will be examined by SonicLib to determine the interrupt type.
 *	Then, the application's callback routine that was registered using
 *	\a ch_io_int_callback_set() will be called to notify the application.
 *	The interrupt type will be passed to the appliction callback routine.
 *
 *	All this processing takes place in the context of the BSP interrupt handler.
 *
 *	### Non-blocking I/O Notification
 *
 *	If non-blocking I/O is used, the BSP's handler functions which processes the
 *	completion of an I/O operation must notify SonicLib that the I/O has completed by
 *	calling the \a ch_io_notify() function.  The group pointer and SPI/I2C bus number must
 *	be passed as parameters to identify which I/O channel has finished.
 *
 *	### Required \b chirp_board_config.h Header File
 *
 *	The board support package must supply a header file called \b chirp_board_config.h containing
 *	definitions of two symbols used in the SonicLib driver functions.
 *
 *	The \b chirp_board_config.h file must be in the C pre-processor include path when you build
 *	your application with SonicLib.
 *
 *	The following symbols must be defined in \b chirp_board_config.h:
 *	- \a CHIRP_MAX_NUM_SENSORS	= maximum number of Chirp sensors
 *	- \a CHIRP_NUM_BUSES	    = number of SPI/I2C bus interfaces
 *
 * #### Special Symbols
 * The following symbols are optional and normally not required.  If defined,
 * they allow special handling in SonicLib for certain hardware configurations
 * or limitations.
 *
 * - \a  MAX_PROG_XFER_SIZE	 	= maximum SPI/I2C transfer size when programming sensor
 *
 *  The sensor is programmed during the \a ch_group_start() function.  Normally,
 * the entire sensor firmware image (6144 bytes for ICU sensors, or 2048 bytes for
 * CH101/CH201 sensors)) is written in a single SPI or I2C write operation. For hardware
 * platforms that cannot support such a large transfer, the MAX_PROG_XFER_SIZE symbol can be
 * defined to specify the maximum size, in bytes, for a single transfer.  The sensor programming
 * will be divided into multiple transfers as necessary.
 *
 *  For example, to limit the maximum transfer size to 256 bytes, add the following
 * line in your \b chirp_board_config.h file:
 *
 * 		#define	MAX_PROG_XFER_SIZE	256
 *
 * - \a  USE_STD_I2C_FOR_IQ		= disable optimized low-level I/Q data readout (CH101/CH201)
 *
 *  This optional symbol is only used with CH101 and CH201 sensors (it has no effect with
 * ICU sensors).  When this symbol is defined, SonicLib will use standard I2C addressing to
 * read I/Q data from the sensor.  Otherwise, an optimized low-level interface
 * is used, with improved performance.
 *
 *
 *	### Implementation Hints
 *
 * Most of the required functions take a pointer to a ch_dev_t device descriptor structure as
 * a handle to identify the sensor being controlled.  The ch_dev_t structure contains various
 * fields with configuration and operating state information for the device.  In general, these
 * values may be obtained using various \a ch_get_XXX() functions provided by the
 * SonicLib API, so it should not be necessary to access fields directly.
 *
 * Some functions take a pointer to a ch_group_t (sensor group descriptor) structure as a parameter
 * but must operate on individual sensors.  These functions can be implemented using the
 * \a ch_get_dev_ptr() function to access the ch_dev_t structure describing each individual sensor
 * in the group, based on its device number (I/O index value).  The total number of possible
 * sensor devices in a group may be obtained by using the \a ch_get_num_ports() function.
 *
 * Similarly, each sensor's ch_dev_t structure contains a \a dev_num field that may be used to
 * manage the pin assignments for the various sensors, by using it as an index into individual
 * arrays which list the pins assigned to the PROG, INT, and RESET_N lines.  The \a dev_num value
 * for a sensor may be obtained using the \a ch_get_dev_num() function.
 *
 * Often, an action should only be taken on a sensor port if a sensor is present and has been
 * successfully initialized and connected.  The \a ch_sensor_is_connected() function can be
 * used to obtain the connection status.
 *
 * These functions are often used together to implement a board support routine, as in the
 * following pseudo-code which shows how to perform an action on all connected devices in a
 * group.  This snippet assumes that a sensor group pointer (ch_group_t *) called \a grp_ptr is
 * an input parameter to the function:
 *
 *		ch_dev_t *dev_ptr;
 *		uint8_t   dev_num;
 *
 *		for (dev_num = 0; dev_num < ch_get_num_ports(grp_ptr); dev_num++ {
 *
 *			dev_ptr = ch_get_dev_ptr(grp_ptr, dev_num);
 *
 *			if (ch_sensor_is_connected(dev_ptr)) {
 *
 *				 DO WHAT NEEDS DOING FOR THIS CONNECTED DEVICE
 *			}
 *		}
 *
 *	The \a dev_num value for each device is specified by the user application as a parameter to
 *	\a ch_init().
 *
 *
 *	\note Example board support packages that implement the chirp_bsp.h functions are available
 *	from Chirp Microsystems for specific platforms.  Contact Chirp for more information.
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#ifndef __CHIRP_BSP_H_
#define __CHIRP_BSP_H_

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <invn/soniclib/soniclib.h>

/*!
 * \brief Toggle a debug indicator pin
 *
 * \param dbg_pin_num  index value for debug pin to toggle
 *
 * This function should change the state (high/low) of the specified debug indicator pin.
 * The \a dbg_pin_num parameter is an index value that specifies which debug pin should
 * be controlled.
 *
 * This function is OPTIONAL.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed for debugging support.
 *       The indicator pins may be any convenient GPIO signals on the host system.  They are
 *       only used to provide a detectable indication of the program execution for debugging.
 *       If used, the debug pin(s) must be initialized during board init.
 */
void chbsp_debug_toggle(uint8_t dbg_pin_num);

/*!
 * \brief Turn on a debug indicator pin
 *
 * \param dbg_pin_num  index value for debug pin to turn on
 *
 * This function should drive the specified debug indicator pin high.
 * The \a dbg_pin_num parameter is an index value that specifies which debug pin should
 * be controlled.
 *
 * This function is OPTIONAL.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed for debugging support.
 *       The indicator pins may be any convenient GPIO signals on the host system.  They are
 *       only used to provide a detectable indication of the program execution for debugging.
 *       If used, the debug pin(s) must be initialized during board init.
 */
void chbsp_debug_on(uint8_t dbg_pin_num);

/*!
 * \brief Turn off a debug indicator pin
 *
 * \param dbg_pin_num  index value for debug pin to turn off
 *
 * This function should drive the the specified debug indicator pin low.
 * The \a dbg_pin_num parameter is an index value that specifies which debug pin should
 * be controlled.
 *
 * This function is OPTIONAL.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed for debugging support.
 *       The indicator pins may be any convenient GPIO signals on the host system.  They are
 *       only used to provide a detectable indication of the program execution for debugging.
 *       If used, the debug pin(s) must be initialized during board init.
 */
void chbsp_debug_off(uint8_t dbg_pin_num);

/*!
 * \brief Assert the reset pin for all sensors.
 *
 * This function should drive the Chirp sensor reset pin low (assert RESET_N) on all sensors.
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used with ICU sensors,
 * which do not have a reset pin.
 */
void chbsp_reset_assert(void);

/*!
 * \brief Deassert the reset pin for all sensors.
 *
 * This function should drive the Chirp sensor reset pin high (or open drain if there is a pull-up)
 * on all sensors.
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used with ICU sensors,
 * which do not have a reset pin.
 */
void chbsp_reset_release(void);

/*!
 * \brief Assert the PROG pin
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should drive the Chirp sensor PROG pin high for the specified device.  It is used
 * by the driver to initiate I2C communication with a specific Chirp sensor device before a unique
 * I2C address is assigned to the device or when the programming interface is used.
 *
 * When the PROG pin is asserted, the device will respond to the standard programming I2C
 * address (0x45).
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 */
void chbsp_program_enable(ch_dev_t *dev_ptr);

/*!
 * \brief Deassert the PROG pin
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should drive the Chirp sensor PROG pin low for the specified device.
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 */
void chbsp_program_disable(ch_dev_t *dev_ptr);

/*!
 * \brief Configure the Chirp sensor INT1 pin as an output for a group of sensors
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function should configure each Chirp sensor's INT1 pin as an output (from the perspective
 * of the host system).
 *
 * This function is REQUIRED.
 */
void chbsp_group_set_int1_dir_out(ch_group_t *grp_ptr);

/*!
 * \brief Configure the Chirp sensor INT1 pin as an output for one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should configure the Chirp sensor INT1 pin as an output (from the perspective
 * of the host system).
 *
 * This function is RECOMMENDED.
 *
 * \note RECOMMENDED - Implementing this function is optional and is only required if individual
 * sensor hardware triggering is used.  It is not required if the sensors are operated only in
 * free-running mode, or if they are always triggered as a group, using \a ch_group_trigger().
 * However, implementing this function is required if sensors will be triggered individually,
 * using \a ch_trigger().
 */
void chbsp_set_int1_dir_out(ch_dev_t *dev_ptr);

/*!
 * \brief Configure the Chirp sensor INT1 pins as inputs for a group of sensors
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function should configure each Chirp sensor's INT1 pin as an input (from the perspective
 * of the host system).
 *
 * This function is REQUIRED.
 */
void chbsp_group_set_int1_dir_in(ch_group_t *grp_ptr);

/*!
 * \brief Configure the Chirp sensor INT1 pin as an input for one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should configure the Chirp sensor INT1 pin as an input (from the perspective of
 * the host system).
 *
 * This function is RECOMMENDED.
 *
 * \note RECOMMENDED - Implementing this function is optional and is only required if individual
 * sensor hardware triggering is used.  It is not required if the sensors are operated only in
 * free-running mode, or if they are only triggered as a group, using \a ch_group_trigger().
 * However, implementing this function is required if sensors will be triggered individually, using
 * \a ch_trigger().
 */
void chbsp_set_int1_dir_in(ch_dev_t *dev_ptr);

/*!
 * \brief Set the INT1 pins low for a group of sensors.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function should drive the INT1 line low for each sensor in the group.
 *
 * This function is REQUIRED.
 */
void chbsp_group_int1_clear(ch_group_t *grp_ptr);

/*!
 * \brief Set the INT1 pin low for one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should drive the INT1 line low for the specified sensor.
 *
 * \note RECOMMENDED - Implementing this function is optional and only needed for individual
 * sensor hardware triggering using \a ch_trigger().  It is not required if sensors are only
 * triggered as a group using \a ch_group_trigger().
 */
void chbsp_int1_clear(ch_dev_t *dev_ptr);

/*!
 * \brief Set the INT1 pins high for a group of sensors.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function should drive the INT1 line high for each sensor in the group.
 *
 * This function is REQUIRED.
 */
void chbsp_group_int1_set(ch_group_t *grp_ptr);

/*!
 * \brief Set the INT1 pin high for one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should drive the INT1 line high for the specified sensor.
 *
 * This function is OPTIONAL.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed for individual sensor
 * hardware triggering using \a ch_trigger().  It is not required if sensors are only triggered
 * as a group using \a ch_group_trigger().
 */
void chbsp_int1_set(ch_dev_t *dev_ptr);

/*!
 * \brief Enable INT1 interrupts for a group of sensors.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * For each sensor in the group, this function should enable the host interrupt associated with
 * the Chirp sensor device's INT1 line.
 *
 * This function is REQUIRED.
 */
void chbsp_group_int1_interrupt_enable(ch_group_t *grp_ptr);

/*!
 * \brief Enable the INT1 interrupt for one sensor
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should enable the host interrupt associated with the Chirp sensor device's
 * INT1 line.
 *
 * This function is REQUIRED.
 */
void chbsp_int1_interrupt_enable(ch_dev_t *dev_ptr);

/*!
 * \brief Disable INT1 interrupts for a group of sensors
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * For each sensor in the group, this function should disable the host interrupt associated
 * with the Chirp sensor device's INT1 line.
 * *
 * This function is REQUIRED.
 */
void chbsp_group_int1_interrupt_disable(ch_group_t *grp_ptr);

/*!
 * \brief Disable the INT1 interrupt for one sensor
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should disable the host interrupt associated with the Chirp sensor device's
 * INT1 line.
 *
 * This function is REQUIRED.
 */
void chbsp_int1_interrupt_disable(ch_dev_t *dev_ptr);

/*!
 * \brief Configure the Chirp sensor INT2 pin as an output for a group of sensors
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function should configure each Chirp sensor's INT2 pin as an output (from the perspective
 * of the host system).
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_group_set_int2_dir_out(ch_group_t *grp_ptr);

/*!
 * \brief Configure the Chirp sensor INT2 pin as an output for one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should configure the Chirp sensor INT2 pin as an output (from the perspective
 * of the host system).
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 *
 * \note RECOMMENDED - Implementing this function is optional and is only required if individual
 * sensor hardware triggering using INT2 is used.  It is not required if the sensors are operated
 * only in free-running mode, if only INT1 is used, or if they are always triggered as a group, using
 * \a ch_group_trigger().  However, implementing this function is required if sensors will be
 * triggered individually, using \a ch_trigger().
 */
void chbsp_set_int2_dir_out(ch_dev_t *dev_ptr);

/*!
 * \brief Configure the Chirp sensor INT2 pins as inputs for a group of sensors
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function should configure each Chirp sensor's INT2 pin as an input (from the perspective
 * of the host system).
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_group_set_int2_dir_in(ch_group_t *grp_ptr);

/*!
 * \brief Configure the Chirp sensor INT2 pin as an input for one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should configure the Chirp sensor INT2 pin as an input (from the perspective of
 * the host system).
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 *
 * \note OPTIONAL - Implementing this function is optional and is only required if individual
 * sensor hardware triggering using INT2 is used.  It is not required if the sensors are operated
 * only in free-running mode, if only INT1 is used, or if they are always triggered as a group, using
 * \a ch_group_trigger().  However, implementing this function is required if sensors will be
 * triggered individually, using \a ch_trigger().
 */
void chbsp_set_int2_dir_in(ch_dev_t *dev_ptr);

/*!
 * \brief Set the INT2 pins as inactive for a group of sensors.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function should drive the INT2 line low for each sensor in the group.
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 *
 * \note OPTIONAL - This function is only needed if the INT2 line is used for triggering
 * ICU sensors.
 */
void chbsp_group_int2_clear(ch_group_t *grp_ptr);

/*!
 * \brief Set the INT2 pin as inactive for one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should drive the INT2 line low for the specified sensor.
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed for individual sensor
 * hardware triggering using \a ch_trigger() when INT2 is configured as the trigger pin.
 * It is not required if sensors are only triggered as a group using \a ch_group_trigger().
 */
void chbsp_int2_clear(ch_dev_t *dev_ptr);

/*!
 * \brief Set the INT2 pins high for a group of sensors.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function should drive the INT2 line high for each sensor in the group.
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_group_int2_set(ch_group_t *grp_ptr);

/*!
 * \brief Set the INT2 pin high for one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should drive the INT2 line high for the specified sensor.
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed for individual sensor
 * hardware triggering using \a ch_trigger() when INT2 is configured as the trigger pin.
 * It is not required if sensors are only triggered as a group using \a ch_group_trigger().
 */
void chbsp_int2_set(ch_dev_t *dev_ptr);

/*!
 * \brief Enable INT2 interrupts for a group of sensors.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * For each sensor in the group, this function should enable the host interrupt associated with
 * the Chirp sensor device's INT2 line.
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_group_int2_interrupt_enable(ch_group_t *grp_ptr);

/*!
 * \brief Enable the INT2 interrupt for one sensor
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should enable the host interrupt associated with the Chirp sensor device's
 * INT2 line.
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_int2_interrupt_enable(ch_dev_t *dev_ptr);

/*!
 * \brief Disable INT2 interrupts for a group of sensors
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * For each sensor in the group, this function should disable the host interrupt associated
 * with the Chirp sensor device's INT2 line.
 * *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_group_int2_interrupt_disable(ch_group_t *grp_ptr);

/*!
 * \brief Disable the INT2 interrupt for one sensor
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should disable the host interrupt associated with the Chirp sensor device's
 * INT2 line.
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_int2_interrupt_disable(ch_dev_t *dev_ptr);

/*!
 * \brief Delay for specified number of microseconds
 *
 * \param us  	number of microseconds to delay before returning
 *
 * This function should wait for the specified number of microseconds before returning to
 * the caller.
 *
 * This function is REQUIRED.
 */
void chbsp_delay_us(uint32_t us);

/*!
 * \brief Delay for specified number of milliseconds.
 *
 * \param ms 	number of milliseconds to delay before returning
 *
 * This function should wait for the specified number of milliseconds before returning to
 * the caller.
 *
 * This function is REQUIRED.
 *
 * \note This function is used during the \a ch_group_start() function to control the length
 * of the calibration pulse sent to the Chirp sensor device during the real-time clock (RTC)
 * calibration, based on the pulse length specified in the board support package.  The
 * accuracy of this pulse timing will directly affect the accuracy of the range values
 * calculated by the sensor.
 */
void chbsp_delay_ms(uint32_t ms);

/*!
 * \brief Return a free-running counter value in milliseconds.
 *
 * \return a 32-bit free-running counter value in milliseconds
 *
 * This function should use a running timer to provide an updated timestamp, in milliseconds,
 * when called.
 *
 *
 * This function is REQUIRED for ICU and CH101/CH201 sensors.
 */
uint32_t chbsp_timestamp_ms(void);

/**
 * @brief Wait for any interrupt event
 *
 * @param time_out_ms time-out of the wait loop
 * @return 0 if an event has been received on INT pin, 1 if time-out happened
 *
 * This function is called during initialization when an event is triggered on sensor
 * and we wait the the result. This event is called in "application" context
 */
uint8_t chbsp_event_wait(uint16_t time_out_ms, uint32_t event_mask);

/**
 * @brief Notify an interrupt event for the selected device
 *
 * @param event_mask Each bit of the mask represents a device
 *
 * This function is called from \a ch_interrupt , in interrupt context
 */
void chbsp_event_notify(uint32_t event_mask);

/**
 * @brief Prepare the mechanism to wait for an event
 *
 * This function is called before \a chbsp_event_wait
 */
void chbsp_event_wait_setup(uint32_t event_mask);

/*!
 * \brief Initialize the host's I2C hardware.
 *
 * \return 0 if successful, 1 on error
 *
 * This function should perform general I2C initialization on the host system.  This includes
 * both hardware initialization and setting up any necessary software structures.  Upon
 * successful return from this routine, the system should be ready to perform I/O operations
 * such as \a chbsp_i2c_read() and \a chbsp_i2c_write().
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 */
int chbsp_i2c_init(void);

/*!
 * \brief Return I2C information for a sensor port on the board.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 * \param dev_num		device number within sensor group
 * \param info_ptr		pointer to structure to be filled with I2C config values
 *
 * \return 0 if successful, 1 if error
 *
 * This function is called by SonicLib functions to obtain I2C operating parameters for
 * a specific device on the board.
 *
 * This function returns I2C values in the ch_i2c_info_t structure specified by \a info_ptr.
 * The structure includes three fields.
 *  - The \a address field contains the I2C address for the sensor.
 *  - The \a bus_num field contains the I2C bus number (index).
 *  - The \a drv_flags field contains various bit flags through which the BSP can inform
 *  SonicLib driver functions to perform specific actions during I2C I/O operations.  The
 *  possible flags include:
 *  - - \a I2C_DRV_FLAG_RESET_AFTER_NB - the I2C interface needs to be reset after non-blocking
 *  transfers
 *  - - \a I2C_DRV_FLAG_USE_PROG_NB - use high-speed programming interface for non-blocking
 *  transfers
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 */
uint8_t chbsp_i2c_get_info(ch_group_t *grp_ptr, uint8_t dev_num, ch_i2c_info_t *info_ptr);

/*!
 * \brief Write bytes to an I2C slave.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param data 			data to be transmitted
 * \param num_bytes 	length of data to be transmitted
 *
 * \return 0 if successful, 1 on error or NACK
 *
 * This function should write one or more bytes of data to an I2C slave device.
 * The I2C interface will have already been initialized using \a chbsp_i2c_init().
 *
 * \note Implementations of this function should use the \a ch_get_i2c_address() function to
 * obtain the device I2C address.
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 */
int chbsp_i2c_write(ch_dev_t *dev_ptr, const uint8_t *data, uint16_t num_bytes);

// clang-format off
/*!
 * \brief Write bytes to an I2C slave using memory addressing.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr		internal memory or register address within device
 * \param data 			data to be transmitted
 * \param num_bytes 	length of data to be transmitted
 *
 * \return 0 if successful, 1 on error or NACK
 *
 * This function should write one or more bytes of data to an I2C slave device using an internal
 * memory or register address.  The remote device will write \a num_bytes bytes of
 * data starting at internal memory/register address \a mem_addr.
 * The I2C interface will have already been initialized using \a chbsp_i2c_init().
 *
 * The \a chbsp_i2c_mem_write() function is basically a standard I2C data write, except that the
 * destination register address and the number of bytes being written must be included, like
 * a header.
 *
 * The byte sequence being sent should look like the following:
 *     0    |     1       |     2        |    3      |    4          |   etc...
 * :------: | :------:    | :------:     | :------:  | :------:      | :------:
 * I2C Addr | \a mem_addr | *\a data | *(\a data + 1)| *(\a data + 2)|   ...
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 *
 * \note Implementations of this function should use the \a ch_get_i2c_address() function to obtain
 * the device I2C address.
 */
// clang-format on
int chbsp_i2c_mem_write(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data, uint16_t num_bytes);

// clang-format off
/*!
 * \brief Write bytes to an I2C slave using memory addressing, non-blocking.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr		internal memory or register address within device
 * \param data 			pointer to the start of data to be transmitted
 * \param num_bytes		length of data to be transmitted
 *
 * \return 0 if successful, 1 on error or NACK
 *
 * This function should initiate a non-blocking write of the specified number of bytes to an
 * I2C slave device, using an internal memory or register address.  The remote device will write
 * \a num_bytes bytes of data starting at internal memory/register address \a mem_addr.
 *
 * The I2C interface must have already been initialized using \a chbsp_i2c_init().
 *
 * The byte sequence being sent should look like the following:
 *     0    |     1       |     2        |    3      |    4          |   etc...
 * :------: | :------:    | :------:     | :------:  | :------:      | :------:
 * I2C Addr | \a mem_addr | *\a data | *(\a data + 1)| *(\a data + 2)|   ...
 *
 * This function is OPTIONAL for CH101 and CH201 sensors.  It is not used for ICU sensors.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed if non-blocking
 * writes on the I2C bus are required.  It is not called by SonicLib functions.
 * To perform a blocking write, see \a chbsp_i2c_mem_write().
 *
 * \note Implementations of this function should use the \a ch_get_i2c_address() function to obtain
 * the device I2C address.
 */
int chbsp_i2c_mem_write_nb(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data, uint16_t num_bytes);
// clang-format on

/*!
 * \brief Read bytes from an I2C slave.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param data 			pointer to receive data buffer
 * \param num_bytes 	number of bytes to read
 *
 * \return 0 if successful, 1 on error or NACK
 *
 * This function should read the specified number of bytes from an I2C slave device.
 * The I2C interface must have already been initialized using \a chbsp_i2c_init().
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 *
 * \note Implementations of this function should use the \a ch_get_i2c_address() function to obtain
 * the device I2C address.
 */
int chbsp_i2c_read(ch_dev_t *dev_ptr, uint8_t *data, uint16_t num_bytes);

// clang-format off
/*!
 * \brief Read bytes from an I2C slave using memory addressing.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr		internal memory or register address within device
 * \param data 			pointer to receive data buffer
 * \param num_bytes 	number of bytes to read
 *
 * \return 0 if successful, 1 on error or NACK
 *
 * This function should read the specified number of bytes from an I2C slave device, using
 * an internal memory or register address.  The remote device will return \a num_bytes bytes
 * starting at internal memory/register address \a mem_addr.
 *
 * The I2C interface must have already been initialized using \a chbsp_i2c_init().
 *
 * There are two distinct phases to the transfer.  First, the register address must be written
 * to the sensor, then a read operation must be done to obtain the data.  (Note that the byte
 * count does not have to be sent to the device during a read operation, unlike in \a chbsp_i2c_mem_write()).)
 *
 * The preferred way to do this is with a *repeated-start operation*, in which the write phase is
 * followed by another I2C Start condition (rather than a Stop) and then the read operation begins
 * immediately.  This prevents another device on the bus from getting control between the write and
 * read phases.  Many micro-controller I/O libraries include dedicated I2C functions to perform just
 * such an operation for writing registers.
 *
 * When using the repeated start, the overall sequence looks like this:
 *
 * |                         Write phase  ||    \|           |                   Read Phase                            ||||||   \|
 * :-----------: | :------:  | :------:    | :------------:  | :-----------------:  | :------:  | :-------:     | :------:      | :-------: | :---:
 * **I2C START** | I2C Addr  | \a mem_addr | \b I2C \b START | I2C Addr + read bit  |  *\a data | *(\a data + 1)| *(\a data + 2)| etc...    | \b I2C \b STOP
 *
 * If the repeated-start technique is not used, it is possible to read from the sensor using separate,
 * sequential I2C write and read operations.  In this case, the sequence is much the same, except that
 * the write phase is ended by an I2C Stop condition, then an I2C Start is issued to begin the read phase.
 * However, this may be a problem if more than one bus master is present,
 * because the bus is not held between the two phases.
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 *
 * \note Implementations of this function should use the \a ch_get_i2c_address() function to obtain
 * the device I2C address.
 */
// clang-format on

int chbsp_i2c_mem_read(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data, uint16_t num_bytes);

/*!
 * \brief Read bytes from an I2C slave, non-blocking.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param data 			pointer to receive data buffer
 * \param num_bytes 	number of bytes to read
 *
 * \return 0 if successful, 1 on error or NACK
 *
 * This function should initiate a non-blocking read of the specified number of bytes from
 * an I2C slave.
 *
 * The I2C interface must have already been initialized using \a chbsp_i2c_init().
 *
 * This function is OPTIONAL for CH101 and CH201 sensors.  It is not used for ICU sensors.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed if non-blocking
 * I/Q readout is required.
 *
 * \note Implementations of this function should use the \a ch_get_i2c_address() function to
 * obtain the device I2C address.
 */
int chbsp_i2c_read_nb(ch_dev_t *dev_ptr, uint8_t *data, uint16_t num_bytes);

/*!
 * \brief Read bytes from an I2C slave using memory addressing, non-blocking.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr		internal memory or register address within device
 * \param data 			pointer to receive data buffer
 * \param num_bytes 	number of bytes to read
 *
 * \return 0 if successful, 1 on error
 *
 * This function should initiate a non-blocking read of the specified number of bytes from an I2C slave.
 * The I2C interface must have already been initialized using \a chbsp_i2c_init().
 *
 * This function is OPTIONAL for CH101 and CH201 sensors.  It is not used for ICU sensors.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed if non-blocking I/Q
 * readout is required.
 */
int chbsp_i2c_mem_read_nb(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data, uint16_t num_bytes);

/*!
 * \brief Interrupt handler callout for external devices sharing the SPI/I2C bus.
 *
 * \param trans 	pointer to Chirp sensor transaction control structure
 *
 * This function is called when a non-blocking SPI/I2C operation completes on an "external"
 * (non Chirp sensor) device. The \a chbsp_external_queue() function should be called to
 * add such a transaction to the SPI/I2C queue.
 *
 * This function is OPTIONAL.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed if devices other
 * than the Chirp sensor(s) are operating on the same SPI/I2C bus and sharing the Chirp driver
 * non-blocking SPI/I2C I/O mechanism.
 */
void chbsp_external_irq_handler(chdrv_transaction_t *trans);

/*!
 * \brief Reset I2C bus associated with device.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function should perform a reset of the I2C interface for the specified device.
 *
 * This function is REQUIRED for CH101 and CH201 sensors.  It is not used for ICU sensors.
 */
void chbsp_i2c_reset(ch_dev_t *dev_ptr);

/*!
 * \brief Assert the SPI chip select line for a device
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function is REQUIRED for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_spi_cs_on(ch_dev_t *dev_ptr);

/*!
 * \brief De-assert the SPI chip select line for a device
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * This function is REQUIRED for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
void chbsp_spi_cs_off(ch_dev_t *dev_ptr);

/*!
 * \brief Write bytes to an SPI slave.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param data 			data to be transmitted
 * \param num_bytes 	length of data to be transmitted
 *
 * \return 0 if successful, 1 on error or NACK
 *
 * This function should write one or more bytes of data to an SPI slave device.
 *
 * This function is REQUIRED for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
int chbsp_spi_write(ch_dev_t *dev_ptr, const uint8_t *data, uint16_t num_bytes);

/*!
 * \brief Read bytes from an SPI slave.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param data 			pointer to receive data buffer
 * \param num_bytes 	number of bytes to read
 *
 * \return 0 if successful, 1 on error or NACK
 *
 * This function should read the specified number of bytes from an SPI slave device.
 *
 * This function is REQUIRED for ICU sensors.  It is not used for CH101 or CH201 sensors.
 */
int chbsp_spi_read(ch_dev_t *dev_ptr, uint8_t *data, uint16_t num_bytes);

/*!
 * \brief Read bytes from an SPI slave using memory addressing, non-blocking.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr		internal memory or register address within device
 * \param data 			pointer to receive data buffer
 * \param num_bytes 	number of bytes to read
 *
 * \return 0 if successful, 1 on error
 *
 * This function should initiate a non-blocking read of the specified number of bytes from an SPI slave.
 *
 * This function is OPTIONAL for ICU sensors.  It is not used for CH101 or CH201 sensors.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed if non-blocking I/Q
 * readout is required.
 */
int chbsp_spi_mem_read_nb(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data, uint16_t num_bytes);

/*!
 * \brief Output a text string via serial interface
 *
 * \param str		pointer to a string of characters to be output
 *
 * This function should print debug information to the console. The user can implement this
 * function to print characters over a serial port, for example.
 *
 * In the Chirp SonicLib sensor driver, debug message output may be enabled by defining
 * \a CH_LOG_MODULE_LEVEL.
 *
 * \note OPTIONAL - Implementing this function is optional and only needed for debugging support.
 */
void chbsp_print_str(const char *str);

#ifdef __cplusplus
}
#endif

#endif /* __CHIRP_BSP_H_ */
