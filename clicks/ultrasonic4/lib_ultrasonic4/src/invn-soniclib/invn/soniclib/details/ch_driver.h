/*! \file ch_driver.h
 *
 * \brief Internal driver functions for operation with the Chirp ultrasonic sensor.
 *
 * This file contains definitions for the internal Chirp sensor driver functions
 * and structures within SonicLib.  These functions are provided in source code form
 * to simplify integration with an embedded application and for reference only.
 *
 * The Chirp driver functions provide an interface between the SonicLib public API
 * layer and the actual sensor devices.  The driver manages all software-defined
 * aspects of the Chirp sensor, including the register set.
 *
 * You should not need to edit this file or call the driver functions directly.  Doing so
 * will reduce your ability to benefit from future enhancements and releases from Chirp.
 *
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#ifndef CH_DRIVER_H_
#define CH_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

// #define USE_PRE_PROD_SERIAL_NUM		// if defined, handle pre-production ICU serial number

#include <invn/soniclib/soniclib.h>

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <invn/icu_interface/shasta_pmut_instruction.h>

#define CHDRV_I2C_MAX_WRITE_BYTES 256 /*!< maximum number of bytes in a single I2C write */

#define CHDRV_NB_TRANS_TYPE_STD      (0) /*!< standard non-blocking I/O transaction */
#define CHDRV_NB_TRANS_TYPE_PROG     (1) /*!< non-blocking I/O via low-level programming interface */
#define CHDRV_NB_TRANS_TYPE_EXTERNAL (2) /*!< externally requested non-blocking I/O transaction */

/*** Definitions relative to CHx01 sensors */

/* Programming interface register addresses */
#define CH_PROG_REG_PING 0x00 /*!< Read-only register used during device discovery. */
#define CH_PROG_REG_CPU  0x42 /*!< Processor control register address. */
#define CH_PROG_REG_STAT 0x43 /*!< Processor status register address. */
#define CH_PROG_REG_CTL  0x44 /*!< Data transfer control register address. */
#define CH_PROG_REG_ADDR 0x05 /*!< Data transfer starting address register address. */
#define CH_PROG_REG_CNT  0x07 /*!< Data transfer size register address. */
#define CH_PROG_REG_DATA 0x06 /*!< Data transfer value register address. */

#define CH_PROG_ADDR_WDT_REG          (0x0120) /*!< Watchdog register address */
#define CH_PROG_ADDR_PMUT_CNTRL4_REG  (0x01A6) /*!< PMUT CNTRL4 register address */
#define CH_PROG_ADDR_DEV_I2C_ADDR_REG (0x01C5) /*!< Device own I2C addr register address */
#define CH_PROG_ADDR_IDLE_LOC         (CHX01_PROG_MEM_ADDR + CHX01_PROG_MEM_SIZE - 4) /*!< IDLE loop location */

#define PMUT_CNTRL4_HVVSS_FON (0x0200)
#define PMUT_CNTRL4_HVVDD_FON (0x0400)

#define CH_PROG_SIZEOF(R) ((R)&0x40 ? 1 : 2)
/*!< Macro to determine programming register size. */

#define CH_PROG_XFER_SIZE (256) /*!< max size of a read operation via programming interface */

/*** End of definitions relative to CHx01 sensors */

#define CHDRV_DEBUG_PIN_NUM (0) /*!< debug pin number (index) to use for debug indication */

#define CHDRV_MAX_QUEUE_LENGTH                                                                                         \
	CHIRP_MAX_NUM_SENSORS /*!< Max queued non-blocking I2C/SPI transactions - value from chirp_board_config.h */

#define CHDRV_FREQLOCK_TIMEOUT_MS                                                                                      \
	100                           /*!< Time to wait in chdrv_group_start() for sensor                                  \
	                                      initialization, in milliseconds.  */
#define CHDRV_BANDWIDTH_INDEX_1 6 /*!< Index of first sample to use for calculating bandwidth. */
#define CHDRV_BANDWIDTH_INDEX_2                                                                                        \
	(CHDRV_BANDWIDTH_INDEX_1 + 1) /*!< Index of second sample to                                                       \
	                                use for calculating bandwidth. */

#define CHDRV_SCALEFACTOR_INDEX 4 /*!< Index for calculating scalefactor. */

#define CHDRV_TRIGGER_PULSE_US    5   /*!< Length of INT pulse to trigger sensor, in microseconds - minimum 800ns.  */
#define CHDRV_DELAY_OVERHEAD_US   (0) /*!< Tuning parameter to adjust pre-trigger timing */
#define CHDRV_PRETRIGGER_DELAY_US 600 /*!< Time to delay between triggering rx-only and tx/rx nodes, in us */
#define CHDRV_POST_TRIG_IEN_DELAY_US                                                                                   \
	10 /*!< Time to delay after triggering shared int/trig before re-enabling interrupt */
#define CHDRV_POST_ALGO_INIT_DELAY_MS 3 /*!< Time to delay after triggering algorithm init on sensor, in ms */
#define CHDRV_DELAY_EN_CHARGE_PUMP_MS (5)
#define CHDRV_EVENT_TIMEOUT_MS        (750) /*!< Max time to wait for sensor event, in ms */

#define CHDRV_I2C_SPEED_DEFAULT_HZ (400000) /*!< Default I2C speed assumed if CHIRP_I2C_SPEED_HZ not defined in BSP */

//! Transaction control structure
typedef struct chdrv_transaction {
	uint8_t type;      /*!< Transaction type: 0 = std, 1 = prog interface, 2 = external */
	uint8_t rd_wrb;    /*!< Read/write indicator: 0 if write operation, 1 if read operation */
	uint8_t xfer_num;  /*!< current transfer within this transaction */
	uint16_t addr;     /*!< I2C address (for I2C devices only) */
	uint16_t nbytes;   /*!< Number of bytes to transfer */
	ch_dev_t *dev_ptr; /*!< Pointer to ch_dev_t descriptor structure for individual sensor */
	uint8_t *databuf;  /*!< Pointer to buffer to receive data or containing data to send */
} chdrv_transaction_t;

//!  Queue structure, for non-blocking access
typedef struct chdrv_queue {
	uint8_t read_pending; /*!< Read transaction status: non-zero if read operation is pending */
	uint8_t running;      /*!< Transaction status: non-zero if I/O operation in progress */
	uint8_t len;          /*!< Number of transactions in queue */
	uint8_t idx;          /*!< Index of current transaction within queue */
	chdrv_transaction_t transaction[CHDRV_MAX_QUEUE_LENGTH]; /*!< List of transactions in queue */
} chdrv_queue_t;

/*!
 * \brief  Calibrate the sensor real-time clock against the host microcontroller clock.
 *
 * \param grp_ptr pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * This function sends a pulse (timed by the host MCU) on the INT line to each device in the group, then reads back the
 * count of sensor RTC cycles that elapsed during that pulse on each individual device.  The result is stored in the
 * ch_dev_t descriptor structure for each device and is subsequently used during range calculations.
 *
 * The length of the pulse is grp_ptr->rtc_cal_pulse_ms milliseconds (typically 100ms).
 *
 * \note The calibration pulse is sent to all devices in the group at the same time.  Therefore all connected devices
 * will see the same reference pulse length.
 *
 */
void chdrv_group_measure_rtc(ch_group_t *grp_ptr);

/*!
 * \brief  Calibrate the sensor real-time clock without using a pulse
 *
 * \param grp_ptr pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * This function is used when special RTC calibration using the I/O bus clock signal is
 * used instead of a normal pulse on the INT line.  So, this routine only places the sensor
 * in calibration mode and then reads the result when complete.
 *
 * A special opcode command is written to the normal pre-calibration "trigger"
 * register, followed by a long dummy write transfer.  During the dummy transfer, the sensor will
 * perform its RTC calibration based on the I/O bus clock.  The result is then read as in
 * a normal calibration, except special handling is required to calculate the RTC frequency
 * based on the result.
 *
 * \note This method is only supported in select sensor firmware variants.
 */
void chdrv_group_measure_rtc_no_pulse(ch_group_t *grp_ptr);

/*!
 * \brief Convert the sensor register values to a range using the calibration data in the ch_dev_t struct.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure for a sensor
 * \param tof 		value of TOF register
 * \param tof_sf 	value of TOF_SF register
 *
 * \return range in millimeters, or \a CH_NO_TARGET (0xFFFFFFFF) if no object is detected.
 * The range result format is fixed point with 5 binary fractional digits (divide by 32 to convert to mm).
 *
 * This function takes the time-of-flight and scale factor values from the sensor,
 * and computes the actual one-way range based on the formulas given in the sensor datasheet.
 */
uint32_t chdrv_one_way_range(ch_dev_t *dev_ptr, uint16_t tof, uint16_t tof_sf);

/*!
 * \brief Convert the sensor register values to a round-trip range using the calibration data in the ch_dev_t struct.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param tof 		value of TOF register
 * \param tof_sf 	value of TOF_SF register
 *
 * \return range in millimeters, or \a CH_NO_TARGET (0xFFFFFFFF) if no object is detected.
 * The range result format is fixed point with 5 binary fractional digits (divide by 32 to convert to mm).
 *
 * This function takes the time-of-flight and scale factor values from the sensor,
 * and computes the actual round-trip range based on the formulas given in the sensor datasheet.
 */
uint32_t chdrv_round_trip_range(ch_dev_t *dev_ptr, uint16_t tof, uint16_t tof_sf);

/*!
 * \brief Add an I2C/SPI transaction to the non-blocking queue
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 * \param instance 	pointer to an individual descriptor structure for a sensor
 * \param rd_wrb 	read/write indicator: 0 if write operation, 1 if read operation
 * \param type		transaction type: 0 = std, 1 = prog interface, 2 = external
 * \param addr 		I2C address for transfer
 * \param nbytes 	number of bytes to read/write
 * \param data 		pointer to buffer to receive data or containing data to send
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_group_queue(ch_group_t *grp_ptr, ch_dev_t *instance, uint8_t rd_wrb, uint8_t type, uint16_t addr,
                      uint16_t nbytes, uint8_t *data);

/*!
 * \brief Add an I2C/SPI transaction for an external device to the non-blocking queue
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 * \param instance 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param rd_wrb 	read/write indicator: 0 if write operation, 1 if read operation
 * \param addr 		I2C address for transfer (for I2C devices only)
 * \param nbytes 	number of bytes to read/write
 * \param data 		pointer to buffer to receive data or containing data to send
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function queues an I2C/SPI transaction for an "external" device (i.e. not a Chirp sensor).  It is used when the
 * I2C/SPI bus is shared between the Chirp sensor(s) and other devices.
 *
 * The transaction is flagged for special handling when the I/O operation completes.  Specifically, the
 * \a chbsp_external_irq_handler() will be called by the driver to allow the board support package (BSP)
 * to perform any necessary operations.
 */
int chdrv_external_queue(ch_group_t *grp_ptr, ch_dev_t *instance, uint8_t rd_wrb, uint16_t addr, uint16_t nbytes,
                         uint8_t *data);

/*!
 * \brief Start a non-blocking sensor readout
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * This function starts a non-blocking I/O operation on the specified group of sensors.
 */
void chdrv_group_start_nb(ch_group_t *grp_ptr);

/*!
 * \brief Continue a non-blocking readout
 *
 * \param grp_ptr 			pointer to the ch_group_t descriptor structure for a group of sensors
 * \param bus_index		index value identifying I2C/SPI bus within group
 *
 * Call this function once from your I2C/SPI interrupt handler each time it executes.
 * It will call \a chdrv_group_complete_callback() when all transactions are complete.
 */
void chdrv_group_irq_handler(ch_group_t *grp_ptr, uint8_t bus_index);

#ifdef INCLUDE_WHITNEY_SUPPORT
/*!
 * \brief Wait for an individual sensor to finish start-up procedure.
 *
 * \param dev_ptr		pointer to the ch_dev_t descriptor structure for a sensor
 * \param timeout_ms 	number of milliseconds to wait for sensor to finish start-up before returning failure
 *
 * \return 0 if startup sequence finished, non-zero if startup sequence timed out or sensor is not connected
 *
 * After the sensor is programmed, it executes an internal start-up and self-test sequence. This
 * function waits the specified time in milliseconds for the sensor to finish this sequence.
 */
int chdrv_wait_for_lock(ch_dev_t *dev_ptr, uint16_t timeout_ms);

/*!
 * \brief Wait for all sensors to finish start-up procedure.
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * \return 0 if startup sequence finished on all detected sensors, non-zero if startup sequence
 * timed out on any sensor(s).
 *
 * After each sensor is programmed, it executes an internal start-up and self-test sequence. This
 * function waits for all sensor devices to finish this sequence.  For each device, the maximum
 * time to wait is \a CHDRV_FREQLOCK_TIMEOUT_MS milliseconds.
 */
int chdrv_group_wait_for_lock(ch_group_t *grp_ptr);

#endif  // INCLUDE_WHITNEY_SUPPORT

/*!
 * \brief Start a measurement in hardware triggered mode.
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * \return 0 if success, non-zero if \a grp_ptr pointer is invalid
 *
 * This function starts a triggered measurement on each sensor in a group, by briefly asserting
 * the INT line to each device.  Each sensor must have already been placed in hardware triggered
 * mode before this function is called.
 */
int chdrv_group_hw_trigger(ch_group_t *grp_ptr);

/*!
 * \brief Start a measurement in hardware triggered mode on one sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 *
 * \return 0 if success, non-zero if \a dev_ptr pointer is invalid
 *
 * This function starts a triggered measurement on a single sensor, by briefly asserting the INT
 * line to the device. The sensor must have already been placed in hardware triggered mode before
 * this function is called.
 *
 * \note This function requires implementing the optional chirp_bsp.h functions to control the
 * INT pin direction and level for individual sensors (\a chbsp_set_int1_dir_in(), \a chbsp_set_int1_dir_out(),
 * \a chbsp_int1_set(), and \a chbsp_int1_clear()).
 */
int chdrv_hw_trigger(ch_dev_t *dev_ptr);

/*!
 * \brief Detect a connected sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 *
 * \return 1 if sensor is found, 0 if no sensor is found
 *
 * This function checks for a sensor on the I2C bus by attempting to reset, halt, and read from the
 * device using the programming interface I2C address (0x45).
 *
 * In order for the device to respond, the PROG pin for the device must be asserted before this
 * function is called.  If there are multiple sensors in an application, only one device's PROG pin
 * should be active at any time.
 */
int chdrv_prog_ping(ch_dev_t *dev_ptr);

/*!
 * \brief Detect, program, and start a sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 *
 * \return 0 if write to sensor succeeded, non-zero otherwise
 *
 * This function probes the I2C bus for the device.  If it is found, the sensor firmware is
 * programmed into the device, and the application I2C address is set.  Then the sensor is reset
 * and execution starts.
 *
 * Once started, the sensor device will begin an internal initialization and self-test sequence.
 *
 * The \a chdrv_wait_for_lock() function may be used to wait for this sequence to complete.
 *
 * \note This routine will leave the PROG pin de-asserted when it completes.
 */
int chdrv_detect_and_program(ch_dev_t *dev_ptr);

/*!
 * \brief Detect, program, and start all sensors in a group.
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * \return 0 for success, non-zero if write(s) failed to any sensor initially detected as present
 *
 * This function probes the SPI or I2C bus for each device in the group.  For each detected sensor, the
 * firmware is programmed into the device, and in CHx01 sensors the application I2C address is set.
 * Then the sensor is reset and execution starts.
 *
 * Once started, each device will begin an internal initialization and self-test sequence.
 *
 * \note For CHx01 sensors, this routine will leave the PROG pin de-asserted for all devices in
 * the group when it completes.
 */
int chdrv_group_detect_and_program(ch_group_t *grp_ptr);

/*!
 * \brief Initialize the sensor device configuration.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure to be initialized
 * \param i2c_addr		For CHx01 sensors, the I2C address to assign to this device.  This
 * 						will be the "application I2C address" used to access the device after
 * 						it is initialized.  Each sensor on an I2C interface must use a unique
 * 						application I2C address.
 * 						For ICU sensors, this field is ignored.
 * \param io_index		index identifying this device.  Each sensor in a group must have a
 * 				    	unique \a io_index value.
 * \param bus_index	index identifying the I2C/SPI interface (bus) to use with this device
 * \param part_number  	integer part number for sensor (e.g. 101 for CH101 device, or 20201 for ICU-20201))
 *
 * \return 0 (always)
 *
 * This function initializes the ch_dev_t descriptor structure for the device with the specified values.
 */
int chdrv_init(ch_dev_t *dev_ptr, uint8_t i2c_addr, uint8_t io_index, uint8_t bus_index, uint16_t part_number);

/*!
 * \brief Initialize data structures and hardware for sensor interaction and reset sensors.
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * \return 0 if hardware initialization is successful, non-zero otherwise
 *
 * This function is called internally by \a chdrv_group_start().
 */
int chdrv_group_prepare(ch_group_t *grp_ptr);

/*!
 * \brief Initialize and start a group of sensors.
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * \return 0 if successful, 1 if device doesn't respond
 *
 * This function resets each sensor in programming mode, transfers the firmware image to the sensor's
 * on-chip memory, and starts the sensor.  For CH101 and CH201 sensors, the I2C address is changed from
 * the default value.
 *
 * In a normal startup, a timed pulse is sent on the INT line for real-time clock
 * calibration. This may be over-ridden by specifying that default (factory) values should be used,
 * or by supplying custom clock calibration values.  Either of these options may be enabled by calling the
 * \a ch_set_clock_cal() function before ch_group_start().
 *
 *
 * This function assumes firmware-specific initialization has already been performed for each ch_dev_t
 * descriptor in the sensor group.  (See \a ch_init()).
 */
uint8_t chdrv_group_start(ch_group_t *grp_ptr);

/*!
 * \brief Restart a sensor
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function restarts a single sensor, using previously stored initialization
 * values.
 */
int chdrv_restart(ch_dev_t *dev_ptr);

/*!
 * \brief Write byte to a sensor application register.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param reg_addr 	register address
 * \param data 		data value to transmit
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_write_byte(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t data);

/*!
 * \brief Write 16 bits to a sensor application register.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data 		data value to transmit
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_write_word(ch_dev_t *dev_ptr, uint16_t mem_addr, uint16_t data);

/*!
 * \brief Read byte from a sensor application register.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data 		pointer to receive buffer
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_read_byte(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data);

/*!
 * \brief Read 16 bits from a sensor application register.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data 		pointer to receive buffer
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_read_word(ch_dev_t *dev_ptr, uint16_t mem_addr, uint16_t *data);

/*!
 * \brief Read multiple bytes from a sensor application register location.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data 		pointer to receive buffer
 * \param len 		number of bytes to read
 *
 * \return 0 if successful, non-zero otherwise
 *
 */
int chdrv_burst_read(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data, uint16_t len);

/*!
 * \brief Read the IQ buffer address from the sensor and store in dev_ptr.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 *
 * \return 0 if successful, non-zero otherwise
 *
 */
int chdrv_read_buf_addr(ch_dev_t *dev_ptr);

/*!
 * \brief Write multiple bytes to a sensor application register location.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data 		pointer to transmit buffer containing data to send
 * \param num_bytes number of bytes to write
 *
 * \return 0 if successful, non-zero otherwise
 *
 */
int chdrv_burst_write(ch_dev_t *dev_ptr, uint16_t mem_addr, const uint8_t *data, uint16_t num_bytes);

/*!
 * \brief Perform a soft reset on a sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 * \param mem_addr 	sensor memory/register address
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function performs a soft reset on an individual sensor by writing to a special control register.
 */
int chdrv_soft_reset(ch_dev_t *dev_ptr);

/*!
 * \brief Perform a hard reset on a group of sensors.
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function performs a hardware reset on each device in a group of sensors by asserting each device's RESET_N pin.
 */
int chdrv_group_hard_reset(ch_group_t *grp_ptr);

/*!
 * \brief Perform a soft reset on a group of sensors.
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function performs a soft reset on each device in a group of sensors by writing to a special
 * control register.
 */
int chdrv_group_soft_reset(ch_group_t *grp_ptr);

/*!
 * \brief Put CHx01 sensor(s) in idle state
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure for a sensor
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function places the sensor processor in a known state by loading an idle loop
 * instruction sequence.  This is used only during early initialization of the device.
 * This is NOT the same as putting a running device into "idle mode" (CH_MODE_IDLE) by
 * using the \a ch_set_mode() function.
 */
int chdrv_set_idle(ch_dev_t *dev_ptr);

/*!
 * \brief Write to a CHx01 programming register.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param reg_addr 	sensor programming register address.
 * \param data 		8-bit or 16-bit data to transmit.
 *
 * \return 0 if write to sensor succeeded, non-zero otherwise
 *
 * This function writes a value to a sensor programming register.
 */
int chdrv_prog_write(ch_dev_t *dev_ptr, uint8_t reg_addr, uint16_t data);

/*!
 * \brief Write bytes to a CHx01 device in programming mode.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param message 	pointer to a buffer containing the bytes to write
 * \param len 		number of bytes to write
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function writes bytes to the device using the programming I2C address.  The
 * PROG line for the device must have been asserted before this function is called.
 */
int chdrv_prog_i2c_write(ch_dev_t *dev_ptr, const uint8_t *message, uint16_t len);

/*!
 * \brief Read bytes from a CHx01 device in programming mode.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param message 	pointer to a buffer where read bytes will be placed
 * \param len 		number of bytes to read
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function reads bytes from the device using the programming I2C address.  The
 * PROG line for the device must have been asserted before this function is called.
 */
int chdrv_prog_i2c_read(ch_dev_t *dev_ptr, uint8_t *message, uint16_t len);

/*!
 * \brief Read bytes from a CHx01 device in programming mode, non-blocking.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param message 	pointer to a buffer where read bytes will be placed
 * \param len 		number of bytes to read
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function temporarily changes the device I2C address to the low-level programming
 * interface, and issues a non-blocking read request. The PROG line for the device must have
 * been asserted before this function is called.
 */
int chdrv_prog_i2c_read_nb(ch_dev_t *dev_ptr, uint8_t *message, uint16_t len);

/*!
 * \brief Write to CHx01 sensor memory.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param addr		sensor programming register start address
 * \param message	pointer to data to transmit
 * \param nbytes	number of bytes to write
 *
 * \return 0 if write to sensor succeeded, non-zero otherwise
 *
 * This function writes to sensor memory using the low-level programming interface.  The type
 * of write is automatically determined based on data length and target address alignment.
 */
int chdrv_prog_mem_write(ch_dev_t *dev_ptr, uint16_t addr, const uint8_t *message, uint16_t nbytes);

/*!
 * \brief Set the pre-trigger delay for rx-only sensors.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 * \param delay_us		time to delay between triggering rx-only and tx/rx nodes, in microseconds
 *
 * This function sets a delay interval that will be inserted between triggering rx-only sensors
 * and tx/rx sensors.  This delay allows the rx-only sensor(s) to settle from any startup disruption
 * (e.g. PMUT "ringdown") before the ultrasound pulse is generated by the tx node.
 *
 */
void chdrv_pretrigger_delay_set(ch_group_t *grp_ptr, uint16_t delay_us);

/*!
 * \brief Read the system control register from a sensor.
 *
 * \param dev_ptr		pointer to the ch_dev_t config structure for a sensor
 * \param reg_value_ptr	pointer to location to receive register value
 *
 * \return 0 if register read succeeded, non-zero otherwise
 *
 * This function reads the system control register from an ICU sensor and
 * returns the value in the location specified by \a reg_value_ptr.
 *
 */
uint8_t chdrv_sys_ctrl_read(ch_dev_t *dev_ptr, uint8_t *reg_value_ptr);

/*!
 * \brief Write the system control register in a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param reg_value	register value to write
 *
 * \return 0 if register write succeeded, non-zero otherwise
 *
 * This function writes \a reg_value to the system control register in
 * an ICU sensor.
 *
 * \return 0 if register write succeeded, non-zero otherwise
 *
 */
uint8_t chdrv_sys_ctrl_write(ch_dev_t *dev_ptr, uint8_t reg_value);

/*!
 * \brief Read the debug register from a sensor.
 *
 * \param dev_ptr		pointer to the ch_dev_t config structure for a sensor
 * \param reg_value_ptr	pointer to location to receive register value
 *
 * \return 0 if register read succeeded, non-zero otherwise
 *
 * This function reads the debug register from an ICU sensor and
 * returns the value in the location specified by \a reg_value_ptr.
 */
uint8_t chdrv_dbg_reg_read(ch_dev_t *dev_ptr, uint8_t reg_id, uint16_t *reg_value_ptr);

/*!
 * \brief Write the debug register in a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param reg_value	register value to write
 *
 * \return 0 if register write succeeded, non-zero otherwise
 *
 * This function writes \a reg_value to the debug register in an ICU sensor.
 *
 * \return 0 if register write succeeded, non-zero otherwise
 *
 */
uint8_t chdrv_dbg_reg_write(ch_dev_t *dev_ptr, uint8_t reg_id, uint16_t reg_value);

/*!
 * \brief Notify SonicLib that a sensor interrupt was received
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 * \param dev_num	interrupting sensor's device number within group
 * \return 0 for success, non-zero otherwise.
 *
 *
 * This function should be called from the board support package when
 * an interrupt from the sensor is received.  The \a dev_num parameter
 * indicates which sensor interrupted.
 *
 * Unlike \a chdrv_int_callback(), this function does not call the user supplied
 * callback. It is intended to be used when the user would like more control
 * of exactly what happens when an interrupt is received from the sensor.
 *
 * Other differences from \a chdrv_int_callback():
 *
 *   - This function does not disable interrupt handling. This must be done in
 *     user code if needed.
 *   - This function does not read any metadata from the sensor, with one exception.
 *     During sensor programming, this funciton performs one SPI read in order
 *     to cause the ASIC to release the interrupt line.
 *   - This function does not update state of the dev_ptr
 *
 */
uint8_t chdrv_int_notify(ch_group_t *grp_ptr, uint8_t dev_num);

/*!
 * \brief Driver callback routine for sensor interrupt.
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 * \param dev_num	interrupting sensor's device number within group
 *
 *
 * This function is called from \a ch_interrupt() when
 * an interrupt from the sensor is received. The \a dev_num parameter
 * indicates which sensor interrupted.
 *
 */
void chdrv_int_callback(ch_group_t *grp_ptr, uint8_t dev_num);

/*!
 * \brief Driver callback deferred routine for sensor interrupt.
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 * \param dev_num	interrupting sensor's device number within group
 *
 *
 * This function is called from \a ch_interrupt() when
 * an interrupt from the sensor is received. Or shall be called in app context
 * if USE_DEFERRED_INTERRUPT_PROCESSING is defined.
 * The \a dev_num parameter indicates which sensor interrupted.
 *
 * For sensor data-ready interrupts, this routine will in turn call the
 * application's callback routine which was set using \a ch_io_int_callback_set().
 *
 * See also \a ch_io_int_callback_set()
 */
void chdrv_int_callback_deferred(ch_group_t *grp_ptr, uint8_t dev_num);

#ifdef INCLUDE_SHASTA_SUPPORT

/*!
 * \brief Trigger an event on a sensor and return immediately.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param event		event type to trigger
 *
 * This function will trigger the event specified by \a event on an ICU sensor.
 * The routine will return immediately, without waiting for any completion
 * notification from the sensor.
 *
 * See also \a chdrv_event_trigger_and_wait()
 */
uint8_t chdrv_event_trigger(ch_dev_t *dev_ptr, uint16_t event);

/*!
 * \brief Trigger an event on a sensor and wait for completion.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param event		event type to trigger
 *
 * This function will trigger the event specified by \a event on an ICU sensor.
 * The routine will wait for the sensor to indicate the event has completed
 * by generating a pulse on the interrupt line.
 *
 * See also \a chdrv_event_trigger()
 */
uint8_t chdrv_event_trigger_and_wait(ch_dev_t *dev_ptr, uint16_t event);

/*!
 * \brief Read OTP memory contents
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * This function reads and processes the contents of the one-time programmable (OTP)
 * memory in the sensor.  The OTP memory contains unique information about the sensor
 * device, such as the sensor lot and serial number, production date and location,
 * and specific part and packaging information.
 *
 * This function instructs the sensor to copy its internal OTP values to an SPI
 * accessible location and reads the values using \a chdrv_otpmem_copy().  It
 * then examines the contents to set various tracking values (sensor type,
 * ID string, etc.).
 *
 * See also \a chdrv_otpmem_copy(), \a ch_get_sensor_id(), \a ch_get_mfg_info()
 */
uint8_t chdrv_otpmem_read(ch_dev_t *dev_ptr);

/*!
 * \brief Copy OTP memory contents
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param otp_copy_ptr	address of otp_copy_t structure to receive OTP contents
 *
 * This function reads the contents of the one-time programmable (OTP) memory
 * in the sensor and copies the values to the structure specified by \a otp_copy_ptr.
 *
 * \note Before this function may be used the first time, the sensor must be
 * instructed to copy the internal OTP values to a shared memory location accessible
 * via SPI.  The EVENT_COPY_OTP_TO_RAM event must be issued to the sensor
 * to perform this operation.
 *
 * See also \a chdrv_otpmem_read()
 */
uint8_t chdrv_otpmem_copy(ch_dev_t *dev_ptr, otp_copy_t *otp_copy_ptr);

/*!
 * \brief Initialize the measurement algorithm on a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if failure detected
 *
 * This function initializes a measurement algorithm that has already
 * been programmed into an ICU sensor.
 */
uint8_t chdrv_algo_init(ch_dev_t *dev_ptr);

/*!
 * \brief Read the algorithm information data from a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if failure detected
 *
 * This function reads the algorithm information data for an algorithm that
 * has been programmed into an ICU sensor.
 */
uint8_t chdrv_algo_info_read(ch_dev_t *dev_ptr, ICU_ALGO_SHASTA_INFO *algo_info_ptr);

/*!
 * \brief Read the algorithm configuration data from a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if failure detected
 *
 * This function reads the algorithm configuration data for an algorithm that
 * has been programmed into an ICU sensor.  The format of the configuration
 * data is defined by the specific algorithm being used.
 */
uint8_t chdrv_algo_cfg_read(ch_dev_t *dev_ptr, void *algo_cfg_ptr);

/*!
 * \brief Write the algorithm configuration data to a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if failure detected
 *
 * This function write the algorithm configuration data for an algorithm that
 * has been programmed into an ICU sensor.  The format of the configuration
 * data is defined by the specific algorithm being used.
 */
uint8_t chdrv_algo_cfg_write(ch_dev_t *dev_ptr, const void *algo_cfg_ptr);

/*!
 * \brief Read the algorithm output data from a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if failure detected
 *
 * This function reads the algorithm output data for an algorithm that
 * has been programmed into an ICU sensor.  The format of the output
 * data is defined by the specific algorithm being used.
 */
uint8_t chdrv_algo_out_read(ch_dev_t *dev_ptr, void *algo_out_ptr);

/*!
 * \brief Read the algorithm state data from a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if failure detected
 *
 * This function reads the algorithm state data for an algorithm that
 * has been programmed into an ICU sensor.  The format of the state
 * data is defined by the specific algorithm being used.
 */
uint8_t chdrv_algo_state_read(ch_dev_t *dev_ptr, void *algo_state_ptr);

/*!
 * \brief Write the measurement queue to a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param q_buf_ptr	pointer to the meas queue to write, NULL = use ch_dev_t copy
 *
 * \return 0 if success, non-zero if error
 *
 * This function writes a measurement queue structure to a sensor.
 *
 * If \a q_buf_ptr is NULL, this function writes the local copy of the measurement queue
 * structure in \a ch_dev_t to the sensor shared memory.  It is typically used after some
 * measurement settings have been modified.
 * If \a q_buf_ptr is not NULL, the measurement queue values from the specified location
 * will be written to the sensor.  The copy in the \a ch_dev_t structure is not modified.
 */
uint8_t chdrv_meas_queue_write(ch_dev_t *dev_ptr, measurement_queue_t *q_buf_ptr);

/*!
 * \brief Read the measurement queue from a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param q_buf_ptr	pointer to the meas queue to write, NULL = update ch_dev_t copy
 *
 * \return 0 if success, non-zero if error
 *
 * This function reads the measurement queue structure from the sensor and copies it
 * to the location indiciated by \a q_buf_ptr.
 *
 * If \a q_buf_ptr is NULL, the measurement queue copy in the \a ch_dev_t descriptor will
 * be updated with the values read from the sensor.
 * If \a q_buf_ptr is not NULL, the measurement queue values read from the device will
 * be copied to the specified location.
 */
uint8_t chdrv_meas_queue_read(ch_dev_t *dev_ptr, measurement_queue_t *q_buf_ptr);

#endif

/*!
 * \brief Assert the hardware trigger line for a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * This function asserts the specified sensor's h/w trigger line to initiate
 * a measurement.  For ICU sensors, the line indicated by the current measurement
 * configuration for trigger pin (INT1 or INT2) will be set to a low (active) level.
 * For CH101/CH201 sensors, the single INT line will be set to a high level.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to manipulate the line levels.
 *
 * See also \a chdrv_group_trig_assert(), \a chdrv_trig_deassert()
 */
void chdrv_trig_assert(ch_dev_t *dev_ptr);

/*!
 * \brief De-assert the hardware trigger line for a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * This function de-asserts the specified sensor's h/w trigger line used to initiate
 * a measurement.  For ICU sensors, the line indicated by the current measurement
 * configuration for trigger pin (INT1 or INT2) will be reset to a high (inactive) level.
 * For CH101/CH201 sensors, the single INT line will be reset to a low level.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to manipulate the line levels.
 *
 * See also \a chdrv_group_trig_assert(), \a chdrv_trig_assert()
 */
void chdrv_trig_deassert(ch_dev_t *dev_ptr);

/*!
 * \brief Assert the hardware trigger lines for all sensors in a group.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function asserts the h/w trigger lines for all sensors in a group to initiate
 * a measurement.  For ICU sensors, the line indicated by the current measurement
 * configuration for trigger pin (INT1 or INT2) will be set to a low (active) level.
 * For CH101/CH201 sensors, the sensors' INT lines will be set to a high level.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to manipulate the line levels.
 *
 * See also \a chdrv_trig_assert(), \a chdrv_trig_group_deassert()
 */
void chdrv_trig_group_assert(ch_group_t *grp_ptr);

/*!
 * \brief De-assert the hardware trigger lines for all sensors in a group.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function de-asserts the h/w trigger lines for all sensors in a group.
 * For ICU sensors, the lines indicated by the current measurement
 * configuration for trigger pin (INT1 or INT2) will be reset to a high (inactive) level.
 * For CH101/CH201 sensors, the sensors' INT lines will be reset to a low level.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to manipulate the line levels.
 *
 * See also \a chdrv_trig_deassert(), \a chdrv_trig_group_assert()
 */
void chdrv_trig_group_deassert(ch_group_t *grp_ptr);

/*!
 * \brief Configure the hardware trigger line for a sensor as an output.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * This function configures the specified sensor's h/w trigger line an an
 * output pin.  For ICU sensors, the current measurement configuration for
 * trigger pin (INT1 or INT2) is used.  For CH101/CH201 sensors, the single
 * INT line is used.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to set the pin direction.
 */
void chdrv_trig_set_dir_out(ch_dev_t *dev_ptr);

/*!
 * \brief Configure the hardware trigger lines for all sensors in a group as outputs.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function configures the h/w trigger lines for all sensors in a group as
 * output pins.  For ICU sensors, the current measurement configuration for
 * trigger pin (INT1 or INT2) is used.  For CH101/CH201 sensors, the single
 * INT line is used.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to set the pin direction.
 */
void chdrv_trig_group_set_dir_out(ch_group_t *grp_ptr);

/*!
 * \brief Assert the interrupt lines for all sensors in a group.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function asserts the interrupt lines for all sensors in a group.
 * For ICU sensors, the lines indicated by the current measurement
 * configuration for interrupt pin (INT1 or INT2) will be set to a low (active) level.
 * For CH101/CH201 sensors, the sensors' INT lines will be set to a high level.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to manipulate the line levels.
 *
 * See also \a chdrv_trig_deassert(), \a chdrv_trig_group_assert()
 */
void chdrv_int_group_assert(ch_group_t *grp_ptr);

/*!
 * \brief De-assert the interrupt lines for all sensors in a group.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * This function de-asserts the interrupt lines for all sensors in a group.
 * For ICU sensors, the lines indicated by the current measurement
 * configuration for interrupt pin (INT1 or INT2) will be reset to a high (inactive) level.
 * For CH101/CH201 sensors, the sensors' INT lines will be reset to a low level.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to manipulate the line levels.
 *
 * See also \a chdrv_trig_deassert(), \a chdrv_trig_group_assert()
 */
void chdrv_int_group_deassert(ch_group_t *grp_ptr);

/*!
 * \brief Configure the interrupt line for a sensor as an input.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * This function configures the specified sensor's interrupt line an an
 * input pin.  For ICU sensors, the current measurement configuration for
 * interrupt pin (INT1 or INT2) is used.  For CH101/CH201 sensors, the single
 * INT line is used.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to set the pin direction.
 */
void chdrv_int_set_dir_in(ch_dev_t *dev_ptr);

/*!
 * \brief Configure the interrupt lines for all sensors in a group as inputs.
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 *
 * This function configures the interrupt lines for all sensors in a group as
 * input pins.  For ICU sensors, the current measurement configuration for
 * interrupt pin (INT1 or INT2) is used.  For CH101/CH201 sensors, the single
 * INT line is used.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to set the pin direction.
 */
void chdrv_int_group_set_dir_in(ch_group_t *grp_ptr);

/*!
 * \brief Configure the interrupt lines for all sensors in a group as outputs.
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 *
 * This function configures the interrupt lines for all sensors in a group as
 * output pins.  For ICU sensors, the current measurement configuration for
 * interrupt pin (INT1 or INT2) is used.  For CH101/CH201 sensors, the single
 * INT line is used.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to set the pin direction.
 */
void chdrv_int_group_set_dir_out(ch_group_t *grp_ptr);

/*!
 * \brief Enable interrupts on the interrupt line for a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * This function enables host micro-controller interrupts to be generated by
 * the specified sensor's interrupt line.
 *
 * For ICU sensors, the line indicated by the current measurement configuration
 * for interrupt pin (INT1 or INT2) will have interrupts enabled.
 * For CH101/CH201 sensors, the single INT line will have interrupts enabled.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to enable interrupts.
 *
 * See also \a chdrv_int_interrupt_disable(), \a chdrv_int_group_interrupt_enable()
 */
void chdrv_int_interrupt_enable(ch_dev_t *dev_ptr);

/*!
 * \brief Disable interrupts on the interrupt line for a sensor.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * This function disables host micro-controller interrupts from being generated by
 * the specified sensor's interrupt line.
 *
 * For ICU sensors, the line indicated by the current measurement configuration
 * for interrupt pin (INT1 or INT2) will have interrupts disabled.
 * For CH101/CH201 sensors, the single INT line will have interrupts disabled.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to disable interrupts.
 *
 * See also \a chdrv_int_interrupt_enable(), \a chdrv_int_group_interrupt_disable()
 */
void chdrv_int_interrupt_disable(ch_dev_t *dev_ptr);

/*!
 * \brief Enable interrupts on the interrupt lines for all sensors in a group.
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 *
 * This function enables host micro-controller interrupts to be generated by
 * all interrupt lines for sensors in the specified sensor group.
 *
 * For ICU sensors, the lines indicated by the current measurement configuration
 * for interrupt pin (INT1 or INT2) will have interrupts enabled.
 * For CH101/CH201 sensors, the single INT lines will have interrupts enabled.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to enable interrupts.
 *
 * See also \a chdrv_int_interrupt_enable, \a chdrv_int_group_interrupt_disable()
 */
void chdrv_int_group_interrupt_enable(ch_group_t *grp_ptr);

/*!
 * \brief Disable interrupts on the interrupt lines for all sensors in a group.
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 *
 * This function disables host micro-controller interrupts from being generated by
 * all interrupt lines for sensors in the specified sensor group.
 *
 * For ICU sensors, the lines indicated by the current measurement configuration
 * for interrupt pin (INT1 or INT2) will have interrupts disabled.
 * For CH101/CH201 sensors, the single INT lines will have interrupts disabled.
 *
 * This function calls the appropriate routine(s) in the the board support package
 * to disable interrupts.
 *
 * See also \a chdrv_int_interrupt_disable, \a chdrv_int_group_interrupt_enable()
 */
void chdrv_int_group_interrupt_disable(ch_group_t *grp_ptr);

/*!
 * \brief Calculate sensor micro-controller CPU frequency, in Hz.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return Sensor CPU frequency, in Hz
 *
 * This function calculates and returns the processor frequency, in Hz, of the internal
 * micro-controller in the sensor.
 */
uint32_t chdrv_cpu_freq_calculate(ch_dev_t *dev_ptr);

/*!
 * \brief Adjust sensor micro-controller CPU frequency.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 * \param pmut_freq	PMUT transducer frequency, in Hz
 *
 * \return Sensor CPU frequency after adjustment, in Hz
 *
 * This function fine tunes the internal micro-controller processor frequency
 * to avoid harmonic relationships with the PMUT transducer frequency.
 *
 * See also \a chdrv_cpu_freq_calculate()
 */
uint32_t chdrv_cpu_freq_adjust(ch_dev_t *dev_ptr, uint32_t pmut_freq);

/*!
 * \brief Run built-in self test (BIST) on sensor
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if error
 *
 * This function initiates the build-in self test (BIST) on a sensor.
 */
uint8_t chdrv_run_bist(ch_dev_t *dev_ptr);

/*!
 * \brief Measure the ultrasonic transducer frequency & bandwidth.
 *
 * \param dev_ptr	pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if error
 *
 * This function initiates the calibration of the PMUT transducer to determine
 * performance characteristics, including operating frequency and bandwidth.
 */
void chdrv_group_measure_pmut(ch_group_t *grp_ptr);

uint8_t chdrv_check_reset_state(ch_dev_t *dev_ptr, uint8_t *reset_state);

/**
 * @brief Enable the measurement config sanitization step when loading configs
 *
 * Not all possible measurement configurations are valid. In particular, there
 * are limits on instruction length and specific control flags that need to be
 * set appropriately. This function enables the sanitization, which is on by
 * default.
 *
 * @param[in,out]  dev_ptr The device pointer.
 *
 * @return
 *
 * @note See chdrv_disable_mq_sanitize() and chdrv_is_mq_sanitize_enabled().
 * @warning
 */
void chdrv_enable_mq_sanitize(ch_dev_t *dev_ptr);

/**
 * @brief Disable the measurement config sanitization step when loading configs
 *
 * Not all possible measurement configurations are valid. In particular, there
 * are limits on instruction length and specific control flags that need to be
 * set appropriately. This function disabled the sanitization, which is on by
 * default.
 *
 * This function is intended to be called from ch_common_init(), before the
 * FW specific initialization function. This allows a specific ASIC firmware to
 * change the setting in its initialization function.
 *
 * See chdrv_enable_mq_sanitize().
 *
 * @param[in,out]  dev_ptr The device pointer.
 *
 * @return
 *
 * @note See chdrv_enable_mq_sanitize() and chdrv_is_mq_sanitize_enabled().
 * @warning
 */
void chdrv_disable_mq_sanitize(ch_dev_t *dev_ptr);

/**
 * @brief Check whether the measurement config sanitization is enabled.
 *
 * See chdrv_enable_mq_sanitize().
 *
 * @param[in,out]  dev_ptr The device pointer.
 *
 * @return The enabled status of the sanitization.
 *
 * @retval 0 Sanitization disabled.
 * @retval 1 Sanitization enabled.
 *
 * @note
 * @warning
 */
int16_t chdrv_is_mq_sanitize_enabled(const ch_dev_t *dev_ptr);

/**
 * @brief This function trims the total RX length to remove excess ADC samples
 *        that don't result in additional IQ sample
 *
 * The ICU-x0201 parts use an oversampling ADC. The PMUT state machine time-base
 * is in terms of the ADC clock. That is, when you set the length of the instruction,
 * you are specifying the length in ADC clock cycles. There are many values of total RX
 * length that result in the same number of total IQ samples. This function trims
 * the excess RX length.
 *
 * It is required to run this function before loading the config to avoid particular
 * values of RX length that can cause some undesirable or unexpected behavior.
 *
 * @param trx_inst a pointer to a instruction sequence. The instructions will
 *                 potentially be modified by this function
 * @param rx_len the total rx length in SMCLK cycles
 * @param eof_idx the index of the EOF instruction
 *
 * @return An error code.
 *
 * @retval 0 Success.
 * @retval 1 The trim could not be completed because it would result in a 0 length
 *           RX instruction. Either remove the final RX instruction or make it longer.
 */
uint8_t chdrv_adjust_rx_len(volatile pmut_transceiver_inst_t *trx_inst, uint8_t cic_odr, int rx_len, int eof_idx);

#ifdef __cplusplus
}
#endif

#endif /* CH_DRIVER_H_ */
