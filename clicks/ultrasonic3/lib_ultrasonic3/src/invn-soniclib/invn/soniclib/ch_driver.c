/*! \file ch_driver.c
 \brief Internal driver functions for operation with TDK/Chirp ultrasonic sensors.

 The user should not need to edit this file. This file relies on hardware interface
 functions declared in ch_bsp.h. If switching to a different hardware platform, the functions
 declared in ch_bsp.h must be provided by the user.
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#include <string.h>
#include <ctype.h>

#define CH_LOG_MODULE_NAME "CH_DRV"
#include <invn/soniclib/ch_log.h>

#include <invn/soniclib/soniclib.h>
#include <invn/soniclib/chirp_bsp.h>
#include <invn/soniclib/details/ch_driver.h>
#include <invn/soniclib/details/ch_common.h>

#ifdef INCLUDE_SHASTA_SUPPORT
#include <invn/soniclib/details/ch_asic_shasta.h>
#include <invn/icu_interface/shasta_pmut_cmds.h>
#endif

/* DEBUG : Uncomment to toggle GPIO DEBUG1 when waiting sensor interrupt */
// #define CHDRV_WAIT_DEBUG

#define CH_PROG_XFER_RETRY 4

#ifdef INCLUDE_WHITNEY_SUPPORT
#ifdef CHIRP_I2C_SPEED_HZ
/* if BSP provided specific I2C bus speed */
#define I2C_BUS_SPEED_HZ CHIRP_I2C_SPEED_HZ
#else
/* otherwise use default */
#define I2C_BUS_SPEED_HZ CHDRV_I2C_SPEED_DEFAULT_HZ
#endif
#endif /* #ifdef INCLUDE_WHITNEY_SUPPORT */

#if IS_CH_LOG_USED

static inline void print_connected_sensors(int prog_status, const ch_group_t *grp_ptr, uint32_t start_time) {

#if !IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_INFO)
	(void)grp_ptr;
	(void)start_time;
#endif

	if (prog_status) {
		CH_LOG_ERR("No Chirp sensor devices are responding");
	} else {
		CH_LOG_INFO("Sensor count: %u, %lu ms.", grp_ptr->sensor_count, chbsp_timestamp_ms() - start_time);
#ifdef INCLUDE_WHITNEY_SUPPORT
		for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
			ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
			if (dev_ptr->sensor_connected) {
				CH_LOG_INFO("Chirp sensor initialized on I2C addr %u:%u", dev_ptr->bus_index, dev_ptr->i2c_address);
			}
		}
#endif
	}
}

#ifdef INCLUDE_WHITNEY_SUPPORT
static inline void print_freq_lock_status(int freq_lock_status, uint32_t start_time) {
#if !IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_INFO)
	(void)start_time;
#endif
	if (!freq_lock_status) {
		CH_LOG_INFO("Frequency locked, %lu ms", chbsp_timestamp_ms() - start_time);
	} else {
		CH_LOG_ERR("Frequency lock failed");
	}
}
#endif /* #ifdef INCLUDE_WHITNEY_SUPPORT */

static inline void print_rtc_cal_result(const ch_group_t *grp_ptr, uint32_t start_time) {

#if !IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_INFO)
	(void)start_time;
#endif

	CH_LOG_INFO("RTC calibrated, %lu ms", chbsp_timestamp_ms() - start_time);
	for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
		const ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
		if (dev_ptr->sensor_connected) {
			CH_LOG_INFO("%u : Cal result = %u", dev_num, dev_ptr->rtc_cal_result);
		}
	}
}
#endif /* #if IS_CH_LOG_USED */

/*!
 * \brief Transfer firmware to the sensor on-chip memory.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if firmware write succeeded, non-zero otherwise
 *
 * This local function writes the sensor firmware image to the device.
 */
static int write_firmware(ch_dev_t *dev_ptr) {
	int ch_err;

	if (!dev_ptr->sensor_connected) {
		return 1;
	}

	CH_LOG_INFO("Programming sensor...");
#if IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_INFO)
	uint64_t prog_time = chbsp_timestamp_ms();
#endif

	ch_err = ch_common_fw_load(dev_ptr);

	if (!ch_err) {
#if IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_INFO)
		uint16_t fw_wrote_size = dev_ptr->current_fw->fw_text_size + dev_ptr->current_fw->fw_vec_size;
		prog_time              = chbsp_timestamp_ms() - prog_time;
#endif
		CH_LOG_INFO("Wrote %u bytes in %lu ms.", fw_wrote_size, prog_time);
	} else {
		CH_LOG_ERR("Error programming device");
	}

	return ch_err;
}

/*!
 * \brief Initialize sensor memory contents.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if memory write succeeded, non-zero otherwise
 *
 * This local function initializes memory locations in the Chirp sensor, as required by the firmware image.
 */
static int init_ram(ch_dev_t *dev_ptr) {
	int ch_err;

	if (!dev_ptr || !dev_ptr->sensor_connected || (dev_ptr->current_fw->get_fw_ram_init_size() == 0)) {
		return 1;
	}

	uint16_t ram_address;
	uint16_t ram_bytecount;

	ram_address   = dev_ptr->current_fw->get_fw_ram_init_addr();
	ram_bytecount = dev_ptr->current_fw->get_fw_ram_init_size();

	CH_LOG_INFO("Loading RAM init data...");
#if IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_INFO)
	uint32_t prog_time = chbsp_timestamp_ms();
#endif

#ifdef INCLUDE_SHASTA_SUPPORT
	ch_err = chdrv_burst_write(dev_ptr, ram_address, dev_ptr->current_fw->ram_init, ram_bytecount);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	ch_err = chdrv_prog_mem_write(dev_ptr, ram_address, dev_ptr->current_fw->ram_init, ram_bytecount);
#endif

#if IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_INFO)
	if (!ch_err) {
		prog_time = chbsp_timestamp_ms() - prog_time;
		CH_LOG_INFO("Wrote %u bytes in %lu ms.", ram_bytecount, prog_time);
	}
#endif

	return ch_err;
}

/*!
 * \brief Reset and halt a sensor
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if write to sensor succeeded, non-zero otherwise
 *
 * This function resets and halts a sensor device by writing to the control registers.
 *
 * WHITNEY: In order for the device to respond, the PROG pin for the device must be asserted before this function is
 * called.
 */
static int reset_and_halt(ch_dev_t *dev_ptr) {
	int ch_err = 0;
#ifdef INCLUDE_SHASTA_SUPPORT

	// enter debug mode and clear active-low reset bit to do reset
	ch_err |= chdrv_sys_ctrl_write(dev_ptr, SYS_CTRL_DEBUG);

	// enter debug mode and set the active-low reset bit to undo reset
	ch_err |= chdrv_sys_ctrl_write(dev_ptr, (SYS_CTRL_DEBUG | SYS_CTRL_RESET_N));

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	ch_err = chdrv_prog_write(dev_ptr, CH_PROG_REG_CPU, 0x40);  // reset asic			// TODO need define

	ch_err |= chdrv_prog_write(dev_ptr, CH_PROG_REG_CPU, 0x11);  // halt asic and disable watchdog;	// TODO need define
#endif  // INCLUDE_SHASTA_SUPPORT

	return ch_err;
}

/* Interrupt Pin Routines */

void chdrv_int_group_assert(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_int_pin == 1) {
		chbsp_group_int1_clear(grp_ptr);  // active low
	} else if (grp_ptr->sensor_int_pin == 2) {
		chbsp_group_int2_clear(grp_ptr);  // active low
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_int1_set(grp_ptr);                               // active high
#endif
}

void chdrv_int_group_deassert(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_int_pin == 1) {
		chbsp_group_int1_set(grp_ptr);  // inactive high
	} else if (grp_ptr->sensor_int_pin == 2) {
		chbsp_group_int2_set(grp_ptr);  // inactive high
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_int1_clear(grp_ptr);                             // inactive low
#endif
}

void chdrv_int_set_dir_in(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->group->sensor_int_pin == 1) {
		chbsp_set_int1_dir_in(dev_ptr);
	} else if (dev_ptr->group->sensor_int_pin == 2) {
		chbsp_set_int2_dir_in(dev_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_set_int1_dir_in(dev_ptr);
#endif
}

void chdrv_int_group_set_dir_in(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_int_pin == 1) {
		chbsp_group_set_int1_dir_in(grp_ptr);
	} else if (grp_ptr->sensor_int_pin == 2) {
		chbsp_group_set_int2_dir_in(grp_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_set_int1_dir_in(grp_ptr);
#endif
}

void chdrv_int_group_set_dir_out(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_int_pin == 1) {
		chbsp_group_set_int1_dir_out(grp_ptr);
	} else if (grp_ptr->sensor_int_pin == 2) {
		chbsp_group_set_int2_dir_out(grp_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_set_int1_dir_out(grp_ptr);
#endif
}

void chdrv_int_interrupt_enable(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->group->sensor_int_pin == 1) {
		chbsp_int1_interrupt_enable(dev_ptr);
	} else if (dev_ptr->group->sensor_int_pin == 2) {
		chbsp_int2_interrupt_enable(dev_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_int1_interrupt_enable(dev_ptr);
#endif
}

void chdrv_int_interrupt_disable(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->group->sensor_int_pin == 1) {
		chbsp_int1_interrupt_disable(dev_ptr);
	} else if (dev_ptr->group->sensor_int_pin == 2) {
		chbsp_int2_interrupt_disable(dev_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_int1_interrupt_disable(dev_ptr);
#endif
}

void chdrv_int_group_interrupt_enable(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_int_pin == 1) {
		chbsp_group_int1_interrupt_enable(grp_ptr);
	} else if (grp_ptr->sensor_int_pin == 2) {
		chbsp_group_int2_interrupt_enable(grp_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_int1_interrupt_enable(grp_ptr);
#endif
}

void chdrv_int_group_interrupt_disable(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_int_pin == 1) {
		chbsp_group_int1_interrupt_disable(grp_ptr);
	} else if (grp_ptr->sensor_int_pin == 2) {
		chbsp_group_int2_interrupt_disable(grp_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_int1_interrupt_disable(grp_ptr);
#endif
}

/* Trigger Pin Routines */

void chdrv_trig_assert(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->group->sensor_trig_pin == 1) {
		chbsp_int1_clear(dev_ptr);  // active low
	} else if (dev_ptr->group->sensor_trig_pin == 2) {
		chbsp_int2_clear(dev_ptr);  // active low
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_int1_set(dev_ptr);          // active high
#endif
}

void chdrv_trig_deassert(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->group->sensor_trig_pin == 1) {
		chbsp_int1_set(dev_ptr);  // inactive high
	} else if (dev_ptr->group->sensor_trig_pin == 2) {
		chbsp_int2_set(dev_ptr);  // inactive high
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_int1_clear(dev_ptr);        // inactive low
#endif
}

void chdrv_trig_group_assert(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_trig_pin == 1) {
		chbsp_group_int1_clear(grp_ptr);  // active low
	} else if (grp_ptr->sensor_trig_pin == 2) {
		chbsp_group_int2_clear(grp_ptr);  // active low
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_int1_set(grp_ptr);    // active high
#endif
}

void chdrv_trig_group_deassert(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_trig_pin == 1) {
		chbsp_group_int1_set(grp_ptr);  // inactive high
	} else if (grp_ptr->sensor_trig_pin == 2) {
		chbsp_group_int2_set(grp_ptr);  // inactive high
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_int1_clear(grp_ptr);  // inactive low
#endif
}

void chdrv_trig_set_dir_out(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->group->sensor_trig_pin == 1) {
		chbsp_set_int1_dir_out(dev_ptr);
	} else if (dev_ptr->group->sensor_trig_pin == 2) {
		chbsp_set_int2_dir_out(dev_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_set_int1_dir_out(dev_ptr);
#endif
}

void chdrv_trig_group_set_dir_out(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_trig_pin == 1) {
		chbsp_group_set_int1_dir_out(grp_ptr);
	} else if (grp_ptr->sensor_trig_pin == 2) {
		chbsp_group_set_int2_dir_out(grp_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_set_int1_dir_out(grp_ptr);
#endif
}

static void chdrv_trig_group_set_dir_in(ch_group_t *grp_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (grp_ptr->sensor_trig_pin == 1) {
		chbsp_group_set_int1_dir_in(grp_ptr);
	} else if (grp_ptr->sensor_trig_pin == 2) {
		chbsp_group_set_int2_dir_in(grp_ptr);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	chbsp_group_set_int1_dir_in(grp_ptr);
#endif
}

#ifdef INCLUDE_WHITNEY_SUPPORT
/*!
 * \brief Write bytes to a sensor device in programming mode.
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
int chdrv_prog_i2c_write(ch_dev_t *dev_ptr, const uint8_t *message, uint16_t len) {

	dev_ptr->i2c_address = CH_I2C_ADDR_PROG;
	int ch_err           = chbsp_i2c_write(dev_ptr, message, len);
	dev_ptr->i2c_address = dev_ptr->app_i2c_address;

	return ch_err;
}

/*!
 * \brief Read bytes from a sensor device in programming mode.
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
int chdrv_prog_i2c_read(ch_dev_t *dev_ptr, uint8_t *message, uint16_t len) {

	dev_ptr->i2c_address = CH_I2C_ADDR_PROG;
	int ch_err           = chbsp_i2c_read(dev_ptr, message, len);
	dev_ptr->i2c_address = dev_ptr->app_i2c_address;

	return ch_err;
}

/*!
 * \brief Read bytes from a sensor device in programming mode, non-blocking.
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
int chdrv_prog_i2c_read_nb(ch_dev_t *dev_ptr, uint8_t *message, uint16_t len) {

	dev_ptr->i2c_address = CH_I2C_ADDR_PROG;
	int ch_err           = chbsp_i2c_read_nb(dev_ptr, message, len);
	dev_ptr->i2c_address = dev_ptr->app_i2c_address;

	return ch_err;
}
#endif  // INCLUDE_WHITNEY_SUPPORT

/*!
 * \brief Write byte to a sensor application register.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr 		sensor memory/register address
 * \param data_value	data value to transmit
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_write_byte(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t data_value) {
#ifdef INCLUDE_WHITNEY_SUPPORT
	uint8_t message[] = {sizeof(data_value), data_value};  // insert byte count (1) at start of data
#endif                                                     // INCLUDE_WHITNEY_SUPPORT
	int ch_err;

#ifdef INCLUDE_SHASTA_SUPPORT
	ch_err = chdrv_burst_write(dev_ptr, mem_addr, &data_value, 1);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	ch_err = chbsp_i2c_mem_write(dev_ptr, mem_addr, message, sizeof(message));
#endif

	return ch_err;
}

/*!
 * \brief Write multiple bytes to a sensor application register location.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data_ptr 		pointer to transmit buffer containing data to send
 * \param len 		number of bytes to write
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_burst_write(ch_dev_t *dev_ptr, uint16_t mem_addr, const uint8_t *data_ptr, uint16_t num_bytes) {
	int ch_err;

#ifdef INCLUDE_SHASTA_SUPPORT
	uint8_t cmd_buf[2];
	uint16_t command;

	command = (SPI_CMD_MEM_ACCESS | SPI_CMD_WRITE);

	if (mem_addr < SHASTA_PROG_MEM_ADDR) {      // writing to data mem
		mem_addr -= SHASTA_DATA_MEM_ADDR;       // convert to offset from start of mem
	} else {                                    // writing to program mem
		mem_addr -= SHASTA_PROG_MEM_BASE_ADDR;  // convert to offset from start of addr space
		command  |= SPI_CMD_PROG_MEM;           // set program mem access in cmd
	}

	command |= mem_addr;

	cmd_buf[0] = (command & 0x00FF);         // LSB
	cmd_buf[1] = ((command & 0xFF00) >> 8);  // MSB

	chbsp_spi_cs_on(dev_ptr);                                      // assert chip select
	ch_err  = chbsp_spi_write(dev_ptr, cmd_buf, sizeof(cmd_buf));  // send command
	ch_err |= chbsp_spi_write(dev_ptr, data_ptr, num_bytes);       // write data
	chbsp_spi_cs_off(dev_ptr);                                     // de-assert chip select

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint8_t message[CHDRV_I2C_MAX_WRITE_BYTES + 1];
	message[0] = (uint8_t)mem_addr;
	message[1] = num_bytes;
	memcpy(&(message[2]), data_ptr, num_bytes);

	ch_err = chbsp_i2c_write(dev_ptr, message, num_bytes + 2);
#endif

	return ch_err;
}

/*!
 * \brief Write 16 bits to a sensor application register.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param reg_addr 	sensor register address
 * \param data_value 	data value to transmit
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_write_word(ch_dev_t *dev_ptr, uint16_t mem_addr, uint16_t data_value) {
	int ch_err;

#ifdef INCLUDE_SHASTA_SUPPORT
	ch_err = chdrv_burst_write(dev_ptr, mem_addr, (uint8_t *)&data_value, 2);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	// First we write the register address, then the number of bytes we're writing
	// Place byte count (2) in first byte of message
	// Sensor is little-endian, so LSB goes in at the lower address
	uint8_t message[] = {sizeof(data_value), (uint8_t)data_value, (uint8_t)(data_value >> 8)};

	ch_err   = chbsp_i2c_mem_write(dev_ptr, mem_addr, message, sizeof(message));
#endif

	return ch_err;
}

/*!
 * \brief Read byte from a sensor application register.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data_ptr 		pointer to receive buffer
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_read_byte(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data_ptr) {
	uint8_t ret_val;

#ifdef INCLUDE_SHASTA_SUPPORT
	ret_val = chdrv_burst_read(dev_ptr, mem_addr, data_ptr, 1);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	ret_val  = chbsp_i2c_mem_read(dev_ptr, mem_addr, data_ptr, 1);
#endif

	return ret_val;
}

/*!
 * \brief Read multiple bytes from a sensor application register location.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data_ptr 		pointer to receive buffer
 * \param num_bytes 		number of bytes to read
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_burst_read(ch_dev_t *dev_ptr, uint16_t mem_addr, uint8_t *data_ptr, uint16_t num_bytes) {
	uint8_t ret_val;

#ifdef INCLUDE_SHASTA_SUPPORT
	uint8_t cmd_buf[3];  // includes required dummy byte after read cmd
	uint16_t command;

	command = SPI_CMD_MEM_ACCESS;

	if (mem_addr < SHASTA_PROG_MEM_ADDR) {      // writing to data mem
		mem_addr -= SHASTA_DATA_MEM_ADDR;       // convert to offset from start of mem
	} else {                                    // writing to program mem
		mem_addr -= SHASTA_PROG_MEM_BASE_ADDR;  // convert to offset from start of addr space
		command  |= SPI_CMD_PROG_MEM;           // set program mem access in cmd
	}

	command |= mem_addr;

	cmd_buf[0] = (command & 0x00FF);         // LSB
	cmd_buf[1] = ((command & 0xFF00) >> 8);  // MSB
	cmd_buf[2] = 0;

	chbsp_spi_cs_on(dev_ptr);  // assert chip select

	ret_val  = chbsp_spi_write(dev_ptr, cmd_buf, sizeof(cmd_buf));  // send command
	ret_val |= chbsp_spi_read(dev_ptr, data_ptr, num_bytes);        // read data

	chbsp_spi_cs_off(dev_ptr);  // de-assert chip select

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	ret_val  = chbsp_i2c_mem_read(dev_ptr, mem_addr, data_ptr, num_bytes);
#endif

	return ret_val;
}

/*!
 * \brief Read 16 bits from a sensor application register.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param mem_addr 	sensor memory/register address
 * \param data_ptr 		pointer to receive buffer
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_read_word(ch_dev_t *dev_ptr, uint16_t mem_addr, uint16_t *data_ptr) {
	uint8_t ret_val;

#ifdef INCLUDE_SHASTA_SUPPORT
	ret_val = chdrv_burst_read(dev_ptr, mem_addr, (uint8_t *)data_ptr, 2);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	ret_val  = chbsp_i2c_mem_read(dev_ptr, mem_addr, (uint8_t *)data_ptr, 2);
#endif

	return ret_val;
}

#ifdef INCLUDE_SHASTA_SUPPORT
uint8_t chdrv_event_trigger(ch_dev_t *dev_ptr, uint16_t event) {
	uint8_t err                     = RET_ERR;
	uint16_t event_trigger_reg_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->common.event_trigger);

	err = chdrv_write_word(dev_ptr, event_trigger_reg_addr, event);
	return err;
}

static inline uint8_t event_wait(ch_dev_t *dev_ptr) {
	uint8_t err = 0;

	chbsp_event_wait_setup((1 << dev_ptr->io_index));
	chdrv_int_interrupt_enable(dev_ptr);  // *** enable interrupt ***/

#ifdef CHDRV_WAIT_DEBUG
	chbsp_debug_on(1);
#endif /* CHDRV_WAIT_DEBUG */

	err = chbsp_event_wait(CHDRV_EVENT_TIMEOUT_MS, (1 << dev_ptr->io_index));
	/* The interrupts are disabled in the entry of chdrv_int_callback */

#ifdef CHDRV_WAIT_DEBUG
	chbsp_debug_off(1);
#endif /* CHDRV_WAIT_DEBUG */

#ifdef USE_DEFERRED_INTERRUPT_PROCESSING
	if (!err) {
		chdrv_int_callback_deferred(dev_ptr->group, dev_ptr->io_index);
	}
#endif

	return err;
}

uint8_t chdrv_event_trigger_and_wait(ch_dev_t *dev_ptr, uint16_t event) {
	ch_io_int_callback_t app_io_int_callback = NULL;
	uint8_t err                              = 0;

	if (dev_ptr->group->io_int_callback != NULL) {
		/* If an application callback has already been defined
		 * avoid to trigger it when event will happen
		 */
		app_io_int_callback             = dev_ptr->group->io_int_callback;
		dev_ptr->group->io_int_callback = NULL;
	}

	chbsp_event_wait_setup((1 << dev_ptr->io_index));
	chdrv_int_interrupt_enable(dev_ptr);         // *** enable interrupt ***
	err |= chdrv_event_trigger(dev_ptr, event);  // trigger event

#ifdef CHDRV_WAIT_DEBUG
	chbsp_debug_on(1);
#endif /* CHDRV_WAIT_DEBUG */

	err |= chbsp_event_wait(CHDRV_EVENT_TIMEOUT_MS, (1 << dev_ptr->io_index)); /* Wait for sensor to interrupt */
	/* The interrupts are disabled in the entry of chdrv_int_callback */

#ifdef CHDRV_WAIT_DEBUG
	chbsp_debug_off(1);
#endif /* CHDRV_WAIT_DEBUG */

#ifdef USE_DEFERRED_INTERRUPT_PROCESSING
	chdrv_int_callback_deferred(dev_ptr->group, dev_ptr->io_index);
#endif

	if (app_io_int_callback != NULL) {
		/* Restore previously saved callback */
		dev_ptr->group->io_int_callback = app_io_int_callback;
	}

	return err;
}
#endif

// grp_ptr below can likely be const, but we need to fix lower level functions first
uint8_t chdrv_int_notify(ch_group_t *grp_ptr, uint8_t dev_num) {
	ch_dev_t *dev_ptr = grp_ptr->device[dev_num];

	/* Get interrupt type */
	if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
		if (grp_ptr->status != CH_GROUP_STAT_INIT_OK) {
			// dummy read needed in this case because we have not yet read the
			// sensor config address, but we still need the asic to release the
			// interrupt line
			int16_t int_type;
			chdrv_read_word(dev_ptr, SHASTA_DATA_MEM_ADDR, (uint16_t *)&int_type);
		}
#endif
	}

	chbsp_event_notify(1 << dev_num);
	return (grp_ptr->status == CH_GROUP_STAT_INIT_OK) ? 0 : 1;
}

void chdrv_int_callback(ch_group_t *grp_ptr, uint8_t dev_num) {
	ch_dev_t *dev_ptr = grp_ptr->device[dev_num];

	/* avoid being retriggered when pin control changes */
	chdrv_int_interrupt_disable(dev_ptr);

	/* Notify the application context of the event */
	chbsp_event_notify(1 << dev_num);

#ifndef USE_DEFERRED_INTERRUPT_PROCESSING
	chdrv_int_callback_deferred(grp_ptr, dev_num);
#endif
}

void chdrv_int_callback_deferred(ch_group_t *grp_ptr, uint8_t dev_num) {
	ch_dev_t *dev_ptr             = grp_ptr->device[dev_num];
	ch_io_int_callback_t func_ptr = grp_ptr->io_int_callback;  // application callback routine
	ch_interrupt_type_t int_type  = CH_INTERRUPT_TYPE_UNKNOWN;

	/* Get interrupt type */
	if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
		uint16_t int_source_reg_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->common.int_source);
		if (grp_ptr->status != CH_GROUP_STAT_INIT_OK) {
			// dummy read needed in this case because we have not yet read the
			// sensor config address, but we still need the asic to release the
			// interrupt line
			chdrv_read_word(dev_ptr, SHASTA_DATA_MEM_ADDR, (uint16_t *)&int_type);
			// manually set this because dummy read result is garbage
			int_type = CH_INTERRUPT_TYPE_PGM_LOADED;
		} else if (dev_ptr->sens_cfg_addr != 0) {
			chdrv_read_word(dev_ptr, int_source_reg_addr, (uint16_t *)&int_type);

			if (int_type == CH_INTERRUPT_TYPE_DATA_RDY) {  // store num if meas just completed
				uint8_t last_meas;
				uint16_t last_meas_reg_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.last_measurement);

				chdrv_read_byte(dev_ptr, last_meas_reg_addr, &last_meas);
				dev_ptr->last_measurement = last_meas & ~LAST_MEASUREMENT_CONTINUOUS;
				dev_ptr->is_continuous    = (last_meas & LAST_MEASUREMENT_CONTINUOUS) > 0;

				uint8_t last_fmt;
				uint16_t last_fmt_reg_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.iq_output_format);

				chdrv_read_byte(dev_ptr, last_fmt_reg_addr, &last_fmt);
				dev_ptr->iq_output_format = last_fmt;

				chdrv_read_buf_addr(dev_ptr);
			}
		}
#endif
	} else {                                    // if CH_ASIC_GEN_1_WHITNEY
		int_type = CH_INTERRUPT_TYPE_DATA_RDY;  //   Whitney only has data ready interrupt
	}

	/* Call application callback function - pass device number to identify device within group */
	if ((func_ptr != NULL) && (grp_ptr->status == CH_GROUP_STAT_INIT_OK)) {
		(*func_ptr)(grp_ptr, dev_num, int_type);
	}
}

#ifdef INCLUDE_SHASTA_SUPPORT

uint8_t chdrv_sys_ctrl_read(ch_dev_t *dev_ptr, uint8_t *reg_value) {
	uint8_t err      = 0;
	uint16_t command = SPI_CMD_SYS_CTRL_READ;  // set upper bits for read cmd
	uint8_t cmd_buf[2];

	cmd_buf[0] = (command & 0x00FF);         // LSB
	cmd_buf[1] = ((command & 0xFF00) >> 8);  // MSB

	chbsp_spi_cs_on(dev_ptr);  // assert chip select

	err = chbsp_spi_write(dev_ptr, cmd_buf, sizeof(cmd_buf));
	err = chbsp_spi_read(dev_ptr, reg_value, 1);

	chbsp_spi_cs_off(dev_ptr);  // de-assert chip select

	return err;
}

uint8_t chdrv_sys_ctrl_write(ch_dev_t *dev_ptr, uint8_t reg_value) {
	uint8_t err      = 0;
	uint16_t command = SPI_CMD_SYS_CTRL_WRITE;  // set upper bits for write cmd
	uint8_t cmd_buf[2];

	command |= reg_value;

	cmd_buf[0] = (command & 0x00FF);         // LSB
	cmd_buf[1] = ((command & 0xFF00) >> 8);  // MSB

	chbsp_spi_cs_on(dev_ptr);  // assert chip select

	err = chbsp_spi_write(dev_ptr, cmd_buf, sizeof(cmd_buf));

	chbsp_spi_cs_off(dev_ptr);  // de-assert chip select

	return err;
}

uint8_t chdrv_dbg_reg_read(ch_dev_t *dev_ptr, uint8_t reg_id, uint16_t *reg_value) {
	uint8_t err      = 0;
	uint16_t command = SPI_CMD_DBG_REG_READ;  // set upper bits for read cmd
	uint8_t cmd_buf[3];                       // includes required dummy byte
	uint8_t reg_size = 2;

	command |= reg_id;

	cmd_buf[0] = (command & 0x00FF);         // LSB
	cmd_buf[1] = ((command & 0xFF00) >> 8);  // MSB

	if (reg_id > SHASTA_LAST_16BIT_DBG_REG) {
		reg_size = 1;
	}

	chbsp_spi_cs_on(dev_ptr);  // assert chip select

	err  = chbsp_spi_write(dev_ptr, cmd_buf, sizeof(cmd_buf));
	err |= chbsp_spi_read(dev_ptr, (uint8_t *)reg_value, reg_size);

	chbsp_spi_cs_off(dev_ptr);  // de-assert chip select

	return err;
}

uint8_t chdrv_dbg_reg_write(ch_dev_t *dev_ptr, uint8_t reg_id, uint16_t reg_value) {
	uint8_t err      = 0;
	uint16_t command = SPI_CMD_DBG_REG_WRITE;  // set upper bits for write cmd
	uint8_t cmd_buf[2];
	uint8_t reg_size = 2;

	command |= reg_id;

	cmd_buf[0] = (command & 0x00FF);         // LSB
	cmd_buf[1] = ((command & 0xFF00) >> 8);  // MSB

	if (reg_id > SHASTA_LAST_16BIT_DBG_REG) {
		reg_size = 1;
	}

	chbsp_spi_cs_on(dev_ptr);  // assert chip select

	err  = chbsp_spi_write(dev_ptr, cmd_buf, sizeof(cmd_buf));
	err |= chbsp_spi_write(dev_ptr, (uint8_t *)&reg_value, reg_size);

	chbsp_spi_cs_off(dev_ptr);  // de-assert chip select

	return err;
}

uint8_t chdrv_otpmem_read(ch_dev_t *dev_ptr) {
	otp_copy_t otp;
	uint8_t err = 0;

	/* Read values from config mem */
	err = chdrv_otpmem_copy(dev_ptr, &otp);

	/* Copy values to device descriptor */
	if (!err) {
		/* Find part number based on product variant code */
		if (otp.product_variant == CH_PROD_CODE_ICU10201) {
			dev_ptr->part_number = ICU10201_PART_NUMBER;
		} else if (otp.product_variant == CH_PROD_CODE_ICU20201) {
			dev_ptr->part_number = ICU20201_PART_NUMBER;
		} else if (otp.product_variant == CH_PROD_CODE_ICU30201) {
			dev_ptr->part_number = ICU30201_PART_NUMBER;
		} else {
			/* No valid product code => Old OTP format*/
			dev_ptr->part_number = ICU_UNKNOWN_PART_NUMBER;
		}
	}

	if (!err) {
		/* Combine lot and serial number into ID string */
		dev_ptr->id_string[0] = otp.serial.lot[0];  // lot (3 char ascii)
		dev_ptr->id_string[1] = otp.serial.lot[1];
		dev_ptr->id_string[2] = otp.serial.lot[2];
		dev_ptr->id_string[3] = otp.serial.serial_num[0];  // serial num (4 char ascii)
		dev_ptr->id_string[4] = otp.serial.serial_num[1];
		dev_ptr->id_string[5] = otp.serial.serial_num[2];
		dev_ptr->id_string[6] = otp.serial.serial_num[3];
		dev_ptr->id_string[7] = '\0';  // null terminator

		/* Get test data (if any) */
		uint8_t invalid_tests   = otp.test_invalid_bitfield;
		uint8_t num_valid_tests = 0;

		if (dev_ptr->part_number != ICU_UNKNOWN_PART_NUMBER) {
			while (!(invalid_tests & (1 << num_valid_tests))) {  // check bits starting w/ least signif
				num_valid_tests++;                               // test is valid if bit is cleared
			}
		}
		if (num_valid_tests > 0) {
			uint8_t test_idx = num_valid_tests - 1;  // use last valid test result

			dev_ptr->test_clock_cal.rtc_freq    = otp.test[test_idx].rtc_clock_frequency_Hz;
			dev_ptr->test_clock_cal.pmut_fcount = otp.test[test_idx].pmut_fcount;
			dev_ptr->test_clock_cal.pmut_trim   = otp.test[test_idx].pmut_code;
			dev_ptr->test_clock_cal.cpu_trim    = otp.test[test_idx].cpu_code;
		} else {
			/* Insert default RTC freq, in case user tries to use missing factory value */
			dev_ptr->test_clock_cal.rtc_freq = CH_RTC_FREQ_TYPICAL;
		}
	}

	return err;
}

uint8_t chdrv_otpmem_copy(ch_dev_t *dev_ptr, otp_copy_t *otp_ptr) {
	uint8_t err           = 0;
	uint16_t otp_ram_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->otp.otp_copy);

	err = chdrv_burst_read(dev_ptr, otp_ram_addr, (uint8_t *)otp_ptr, sizeof(otp_copy_t));

	if ((otp_ptr->otp_format_major == 0xFF) && (otp_ptr->otp_format_minor == 0xFF)) {
		/* Not programmed - return default values */
		otp_ptr->serial.lot[0]        = 'N';  // id string = "NOTPROG"
		otp_ptr->serial.lot[1]        = 'O';
		otp_ptr->serial.lot[2]        = 'T';
		otp_ptr->serial.serial_num[0] = 'P';
		otp_ptr->serial.serial_num[1] = 'R';
		otp_ptr->serial.serial_num[2] = 'O';
		otp_ptr->serial.serial_num[3] = 'G';
	}
	if ((otp_ptr->otp_format_major == 0xFF) || (otp_ptr->otp_format_major < 4)) {
		otp_ptr->serial.production_site = 0;
		otp_ptr->serial.year_since_2000 = 0;
		otp_ptr->serial.work_week       = 0;

		otp_ptr->product_variant = CH_PROD_CODE_UNKNOWN;
		otp_ptr->package_variant = 0;
		otp_ptr->mems_variant    = 0;
		otp_ptr->module_variant  = 0;
	}

	return err;
}

static const int max_num_trx = sizeof(((measurement_t *)0)->trx_inst) / sizeof(((measurement_t *)0)->trx_inst[0]);

//! Clear all interrupts from instruction array and perform some basic error checking
static uint8_t clear_interrupts(volatile pmut_transceiver_inst_t *inst_ptr, int *eof_idx, int *rx_idx, int *rx_len) {
	uint8_t err = 0;
	*rx_len     = 0;   // total RX length in SMCLK cycles
	*eof_idx    = -1;  // index of EOF instruction
	*rx_idx     = -1;  // offset of first RX instruction
	int j       = 0;
	while (j < max_num_trx && (inst_ptr[j].cmd_config & PMUT_CMD_BITS) != PMUT_CMD_EOF) {

		CH_LOG_TRACE("inst %d: cmd=%d", j, inst_ptr[j].cmd_config & PMUT_CMD_BITS);

		inst_ptr[j].cmd_config &= ~PMUT_RDY_IEN_BITS;
		inst_ptr[j].cmd_config &= ~PMUT_DONE_IEN_BITS;
		if ((inst_ptr[j].cmd_config & PMUT_CMD_BITS) == PMUT_CMD_RX) {
			if (*rx_idx < 0) {
				*rx_idx = j;
			}
			*rx_len += inst_ptr[j].length;
		}
		j++;
	}
	if (j == max_num_trx || j == 0) {
		// return an error when EOF is either missing or the first
		// instruction
		err = 1;
	} else if (*rx_idx < 0) {
		// return an error when there are no RX instructions
		err = 2;
	} else {
		*eof_idx = j;
	}

	CH_LOG_TRACE("clear_interrupts: eof_idx=%d rx_idx=%d", *eof_idx, *rx_idx);

	return err;
}

//! Remove n instructions from the start of the instruction array
static uint8_t remove_from_start(volatile pmut_transceiver_inst_t *inst_ptr, int n) {
	for (int i = n; i < max_num_trx; i++) {
		inst_ptr[i - n] = inst_ptr[i];
	}
	return 0;
}

//! Copy instructions from src to dst
static uint8_t copy_instructions(volatile pmut_transceiver_inst_t *dst, const volatile pmut_transceiver_inst_t *src) {
	for (int i = 0; i < max_num_trx; i++) {
		dst[i] = src[i];
	}
	return 0;
}

static uint8_t limit_rx_len(volatile measurement_t *meas, int rx_len, int eof_idx, uint16_t iq_samples_max) {
	// add one to be safe
	const int rx_samples = (rx_len >> (11 - meas->odr)) + 1;
	if (rx_samples > iq_samples_max) {
		const int samples_to_cut = rx_samples - iq_samples_max;
		const int len_to_cut     = samples_to_cut << (11 - meas->odr);
		if (meas->trx_inst[eof_idx - 1].length > (1 << (11 - meas->odr)) + len_to_cut) {
			// make sure resulting rx instruction will have at least one RX sample left
			// in it after the cut.
			meas->trx_inst[eof_idx - 1].length -= len_to_cut;
			return 0;
		} else {
			return 1;
		}
	} else {
		return 0;
	}
}

uint8_t chdrv_adjust_rx_len(volatile pmut_transceiver_inst_t *trx_inst, uint8_t cic_odr, int rx_len, int eof_idx) {
	const int rx_samples = rx_len >> (11 - cic_odr);
	const int new_rx_len = rx_samples << (11 - cic_odr);
	int len_to_cut       = rx_len - new_rx_len;

	CH_LOG_DEBUG("rx_len=%d rx_samples=%d new_rx_len=%d len_to_cut=%d", rx_len, rx_samples, new_rx_len, len_to_cut);

	if (len_to_cut == 0) {
		// No modification needed for this rx instruction
		return 0;
	} else if (trx_inst[eof_idx - 1].length >= (1 << (11 - cic_odr)) + len_to_cut) {
		// make sure resulting rx instruction will have at least one RX sample left
		// in it after the cut.
		trx_inst[eof_idx - 1].length -= len_to_cut;
		return 0;
	} else {
		// return error otherwise
		return 1;
	}
}

static uint8_t adjust_rx_len(volatile measurement_t *meas, int rx_len, int eof_idx) {
	return chdrv_adjust_rx_len(meas->trx_inst, meas->odr, rx_len, eof_idx);
}

void chdrv_enable_mq_sanitize(ch_dev_t *dev_ptr) {
	dev_ptr->mq_sanitize_enabled = 1;
}

void chdrv_disable_mq_sanitize(ch_dev_t *dev_ptr) {
	dev_ptr->mq_sanitize_enabled = 0;
}

int16_t chdrv_is_mq_sanitize_enabled(const ch_dev_t *dev_ptr) {
	return dev_ptr->mq_sanitize_enabled;
}

//! Sanitize the measurement queue
/*! This function sanitizes the measurement queue by performing several checks
 * to ensure it is compatible with the selected sensor mode. This function
 * potentially modifies the queue, so users should examine the passed queue
 * after loading it.
 *
 * What we check and correct:
 *  - RX length results in an integer number of RX samples.
 *  - done interrupt is set only on last RX instruction and no others
 *  - in continuous RX, if the first measurement config is good but the second is blank, just make
 *    the second a copy of the first
 *  - in continuous RX, ready interrupt is set on last RX and no others
 */
static uint8_t meas_queue_sanitize(measurement_queue_t *q_buf_ptr, uint16_t iq_samples_max) {
	int eof_idx[2];
	int rx_idx[2];
	int rx_len[2];

	CH_LOG_TRACE("clear_interrupts 0");
	uint8_t err = clear_interrupts(q_buf_ptr->meas[0].trx_inst, &eof_idx[0], &rx_idx[0], &rx_len[0]);
	if (err) {
		// if meas queue 0 is bad, just abort
		return err;
	}

	CH_LOG_TRACE("clear_interrupts 1");
	err = clear_interrupts(q_buf_ptr->meas[1].trx_inst, &eof_idx[1], &rx_idx[1], &rx_len[1]);
	switch (q_buf_ptr->trigsrc) {
	case TRIGSRC_CONTINUOUS_RX:
		if (err) {
			// if meas queue 1 is bad, make it a copy of meas queue 0
			q_buf_ptr->meas[1].meas_flags  = q_buf_ptr->meas[0].meas_flags;
			q_buf_ptr->meas[1].meas_period = q_buf_ptr->meas[0].meas_period;
			q_buf_ptr->meas[1].odr         = q_buf_ptr->meas[0].odr;
			copy_instructions(q_buf_ptr->meas[1].trx_inst, q_buf_ptr->meas[0].trx_inst);
			eof_idx[1] = eof_idx[0];
			rx_idx[1]  = rx_idx[0];
			rx_len[1]  = rx_len[0];
			err        = 0;
		}
		for (int i = 0; i < 2; i++) {
			// ready interrupt enable on last instruction
			q_buf_ptr->meas[i].trx_inst[eof_idx[i] - 1].cmd_config |= PMUT_RDY_IEN_BITS;
			// buffer size is halved in continuous mode
			limit_rx_len(&q_buf_ptr->meas[i], rx_len[i], eof_idx[i], iq_samples_max / 2);
			// if we can't adjust the rx length, then return an error but
			// otherwise still try to send the queue
			err = adjust_rx_len(&q_buf_ptr->meas[i], rx_len[i], eof_idx[i]);
			// remove transmit instructions
			remove_from_start(q_buf_ptr->meas[i].trx_inst, rx_idx[i]);
			// adjust EOF and RX indices
			eof_idx[i] -= rx_idx[i];
			rx_idx[i]   = 0;
		}
		// both measurements must be enabled for continuous RX
		q_buf_ptr->meas_start = 0;
		q_buf_ptr->meas_stop  = 1;
		for (int i = 0; i < 2; i++) {
			// done interrupt enable on last instruction
			q_buf_ptr->meas[i].trx_inst[eof_idx[i] - 1].cmd_config |= PMUT_DONE_IEN_BITS;
		}
		break;
	default:
		for (int i = 0; i < 2; i++) {
			if (err && i == 1) {
				// if meas queue 1 is bad, do not attempt to limit rx len or
				// set the done IEN. Return the error condition
				break;
			}
			limit_rx_len(&q_buf_ptr->meas[i], rx_len[i], eof_idx[i], iq_samples_max);
#ifndef ALLOW_RXLEN_FRACTIONAL_SAMPLES
			err = adjust_rx_len(&q_buf_ptr->meas[i], rx_len[i], eof_idx[i]);
#endif
			// done interrupt enable on last instruction
			q_buf_ptr->meas[i].trx_inst[eof_idx[i] - 1].cmd_config |= PMUT_DONE_IEN_BITS;
		}
		break;
	}

	for (int i = 0; i < 2; i++) {
		CH_LOG_TRACE("meas queue %d after sanitize:", i);
		for (int j = 0; j < max_num_trx; j++) {
			CH_LOG_TRACE("inst %d: cmd=0x%04x len=%d", j, q_buf_ptr->meas[i].trx_inst[j].cmd_config,
			             q_buf_ptr->meas[i].trx_inst[j].length);
		}
	}

	return err;
}

uint8_t chdrv_meas_queue_write(ch_dev_t *dev_ptr, measurement_queue_t *q_buf_ptr) {
	uint16_t meas_queue_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->meas_queue);  // addr on sensor
	uint8_t err              = 0;

	if (q_buf_ptr == NULL) {
		q_buf_ptr = &(dev_ptr->meas_queue);  // source is local copy in ch_dev_t
	}
	if (chdrv_is_mq_sanitize_enabled(dev_ptr)) {
		// Note that we do not abort the write when the sanitize funciton returns an
		// error. This is mostly for historical reasons. We have previously allowed
		// writing invalid queues. It is OK to write them so long as they are not
		// used, and it's a bit confusing for us to just arbitrarily set them when
		// the user has not requested it
		meas_queue_sanitize(q_buf_ptr, dev_ptr->current_fw->max_samples);
	}
	err |= chdrv_burst_write(dev_ptr, meas_queue_addr, (uint8_t *)q_buf_ptr, sizeof(measurement_queue_t));

	return err;
}

uint8_t chdrv_meas_queue_read(ch_dev_t *dev_ptr, measurement_queue_t *q_buf_ptr) {
	uint16_t meas_queue_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->meas_queue);  // addr on sensor
	uint8_t err              = 0;

	if (q_buf_ptr == NULL) {
		q_buf_ptr = &(dev_ptr->meas_queue);  // destination is local copy in ch_dev_t
	}

	err |= chdrv_burst_read(dev_ptr, meas_queue_addr, (uint8_t *)q_buf_ptr, sizeof(measurement_queue_t));

	return err;
}

uint8_t chdrv_algo_init(ch_dev_t *dev_ptr) {
	uint8_t err = 0;

	chdrv_event_trigger(dev_ptr, EVENT_ALGO_INIT);  // trigger algo init event on sensor

	chbsp_delay_ms(CHDRV_POST_ALGO_INIT_DELAY_MS);  // delay a bit to let algo init

	return err;
}

uint8_t chdrv_algo_info_read(ch_dev_t *dev_ptr, ICU_ALGO_SHASTA_INFO *algo_info_ptr) {
	uint8_t err;
	uint16_t algo_info_addr   = (uint16_t)(uintptr_t)dev_ptr->sens_algo_info_addr;
	uint16_t algo_info_nbytes = sizeof(ICU_ALGO_SHASTA_INFO);

	err = chdrv_burst_read(dev_ptr, algo_info_addr, (uint8_t *)algo_info_ptr, algo_info_nbytes);

	return err;
}

uint8_t chdrv_algo_cfg_read(ch_dev_t *dev_ptr, void *algo_cfg_ptr) {
	uint8_t err;
	uint16_t algo_cfg_addr   = (uint16_t)(uintptr_t)dev_ptr->algo_info.algo_cfg_ptr;
	uint16_t algo_cfg_nbytes = dev_ptr->algo_info.algo_cfg_len;

	err = chdrv_burst_read(dev_ptr, algo_cfg_addr, (uint8_t *)algo_cfg_ptr, algo_cfg_nbytes);

	return err;
}

uint8_t chdrv_algo_cfg_write(ch_dev_t *dev_ptr, const void *algo_cfg_ptr) {
	uint16_t algo_cfg_addr   = (uint16_t)(uintptr_t)dev_ptr->algo_info.algo_cfg_ptr;
	uint16_t algo_cfg_nbytes = dev_ptr->algo_info.algo_cfg_len;

	return (uint8_t)chdrv_burst_write(dev_ptr, algo_cfg_addr, (uint8_t *)algo_cfg_ptr, algo_cfg_nbytes);
}

uint8_t chdrv_algo_out_read(ch_dev_t *dev_ptr, void *algo_out_ptr) {
	uint8_t err;
	uint16_t algo_out_addr   = (uint16_t)(uintptr_t)dev_ptr->algo_info.algo_out_ptr;
	uint16_t algo_out_nbytes = dev_ptr->algo_info.algo_out_len;

	err = chdrv_burst_read(dev_ptr, algo_out_addr, (uint8_t *)algo_out_ptr, algo_out_nbytes);

	return err;
}

uint8_t chdrv_algo_state_read(ch_dev_t *dev_ptr, void *algo_state_ptr) {
	uint8_t err;
	uint16_t algo_state_addr   = (uint16_t)(uintptr_t)dev_ptr->algo_info.algo_state;
	uint16_t algo_state_nbytes = dev_ptr->algo_info.algo_state_len;

	err = chdrv_burst_read(dev_ptr, algo_state_addr, (uint8_t *)algo_state_ptr, algo_state_nbytes);

	return err;
}

static void clock_init(ch_dev_t *dev_ptr, uint8_t restart) {
	clock_control_t *clock_ctrl_addr = (clock_control_t *)&((dev_ptr->sens_cfg_addr)->common.clock);
	clock_control_t clock_ctrl;
	uint16_t reg_addr;

	if (dev_ptr->rtc_status == CH_RTC_STATUS_EXTERNAL) {
		clock_ctrl.rtc_sources = (SCM_RTC_CLK_PAD_MODE_INPUT | SCM_RTC_CLK_EXT_EN);
	} else {
		clock_ctrl.rtc_sources = SCM_RTC_CLK_PAD_MODE_NONE;
	}
	clock_ctrl.fcount_cycles = SHASTA_FCOUNT_CYCLES;
	clock_ctrl.control       = 0;
	clock_ctrl.step          = 0;

	dev_ptr->fcount_cycles = clock_ctrl.fcount_cycles;

	if (dev_ptr->rtc_status == CH_RTC_STATUS_CAL_FACTORY) {
		/* Use factory test RTC calibration result */
		uint16_t test_rtc_freq = dev_ptr->test_clock_cal.rtc_freq;

		if ((test_rtc_freq != 0) && (test_rtc_freq != UINT16_MAX)) {  // check for actual data
			dev_ptr->rtc_frequency = test_rtc_freq;
		}

		CH_LOG_INFO("Using factory test rtc freq = %05u", test_rtc_freq);
	}

	/* Set clock trim values */
	if (restart) {  // if restart, use values already in ch_dev_t
		clock_ctrl.cpu_trim  = dev_ptr->cpu_trim;
		clock_ctrl.pmut_trim = dev_ptr->pmut_trim;
		clock_ctrl.control   = dev_ptr->pmut_clk_cfg;

	} else {
		clock_ctrl.cpu_trim  = SHASTA_CPU_TRIM_DEFAULT;  // normal start - use default values, will do auto cal later
		clock_ctrl.pmut_trim = SHASTA_PMUT_TRIM_DEFAULT;
	}
	if (dev_ptr->pmut_clk_cfg == CH_PMUT_CLK_OUTPUT_ENABLE) {
		clock_ctrl.pmut_trim |= SCM_PMUT_CLK_PAD_MODE_PMUT;  // enable PMUT clock output

	} else if (dev_ptr->pmut_clk_cfg == CH_PMUT_CLK_SRC_EXTERNAL) {
		clock_ctrl.pmut_trim |= (SCM_PMUT_CLK_PAD_MODE_INPUT | SCM_PMUT_CLK_EXT_EN);
		// enable external PMUT clock input
	}
	CH_LOG_INFO("Restoring pmut_trim=0x%x", clock_ctrl.pmut_trim);

	/* Write to sensor */
	reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_addr->rtc_sources);  // RTC sources
	chdrv_write_byte(dev_ptr, reg_addr, clock_ctrl.rtc_sources);

	reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_addr->cpu_trim);  // CPU trim
	chdrv_write_byte(dev_ptr, reg_addr, clock_ctrl.cpu_trim);

	reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_addr->pmut_trim);  // PMUT trim
	chdrv_write_word(dev_ptr, reg_addr, clock_ctrl.pmut_trim);

	reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_addr->fcount_cycles);  // freq count cycles
	chdrv_write_word(dev_ptr, reg_addr, clock_ctrl.fcount_cycles);

	reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_addr->control);  // clock control
	chdrv_write_byte(dev_ptr, reg_addr, clock_ctrl.control);

	reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_addr->step);  // clock step
	chdrv_write_byte(dev_ptr, reg_addr, clock_ctrl.step);

	/* Trigger event to apply settings */
	chdrv_event_trigger(dev_ptr, EVENT_CONFIG_CLOCKS);

	CH_LOG_INFO("cpu_trim=0x%02x  pmut_trim=0x%04x rtc_source=%d control=0x%02x step=%d", clock_ctrl.cpu_trim,
	            clock_ctrl.pmut_trim, clock_ctrl.rtc_sources, clock_ctrl.control, clock_ctrl.step);
}

uint32_t chdrv_cpu_freq_adjust(ch_dev_t *dev_ptr, uint32_t pmut_op_freq) {
	uint32_t mult_offset = 0;
	uint32_t min_offset;
	uint32_t max_offset;
	uint8_t start_trim;
	int8_t trim_adj                 = 0;
	clock_control_t *clock_ctrl_ptr = (clock_control_t *)&((dev_ptr->sens_cfg_addr)->common.clock);
	uint16_t reg_addr               = (uint16_t)(uintptr_t) & (clock_ctrl_ptr->cpu_trim);
	uint32_t cpu_freq               = chdrv_cpu_freq_calculate(dev_ptr);  // get starting cpu freq
	uint32_t pmut_clock_freq        = (pmut_op_freq * CH_PMUT_TICKS_PER_CYCLE);

	chdrv_read_byte(dev_ptr, reg_addr, &start_trim);  // get starting CPU clock trim value
	dev_ptr->cpu_trim = start_trim;                   // store in dev descriptor

	/* Adjust trim if CPU freq is close to multiple of (PMUT freq * 16) */
	min_offset = (pmut_clock_freq / 8);      // min positive offset from multiple of pmut_freq*16
	max_offset = (pmut_clock_freq * 7 / 8);  // max positive offset from multiple of pmut_freq*16

	mult_offset = (cpu_freq % pmut_clock_freq);  // calculate offset for current CPU freq

	CH_LOG_INFO("Starting cpu_freq=%lu  starting cpu_trim=%d", cpu_freq, start_trim);
	CH_LOG_DEBUG("mult_offset=%lu  (min=%lu  max=%lu)", mult_offset, min_offset, max_offset);

	while ((mult_offset < min_offset) || (mult_offset > max_offset)) {
		uint8_t new_trim;

		if (trim_adj > 0) {
			trim_adj = -trim_adj;  // try subtracting same adjustment value
		} else {
			trim_adj = abs(trim_adj);  // try adding next higher adjustment value
			trim_adj++;
		}

		new_trim = (start_trim + trim_adj);  // calculate new trim value

		if ((new_trim == 0) || (new_trim > SHASTA_CPU_TRIM_MAX)) {
			cpu_freq = 0;  // error - trim out of range
			CH_LOG_ERR("CPU trim out of range");
			break;
		}

		if (cpu_freq != 0) {  // if no error
			CH_LOG_INFO("Setting cpu_trim to %d", new_trim);

			chdrv_write_byte(dev_ptr, reg_addr, new_trim);  // write new value to clock_config cpu_trim
			chdrv_event_trigger(dev_ptr, EVENT_CONFIG_CLOCKS);

			dev_ptr->cpu_trim = new_trim;                           // update trim value in dev descriptor
			cpu_freq          = chdrv_cpu_freq_calculate(dev_ptr);  // get updated frequency and recalculate mult offset
			mult_offset       = (cpu_freq % pmut_clock_freq);

			CH_LOG_INFO("cpu_freq=%lu  mult_offset=%lu", cpu_freq, mult_offset);
		}
	}

	return cpu_freq;  // return final CPU frequency
}
#endif  // INCLUDE_SHASTA_SUPPORT

uint32_t chdrv_cpu_freq_calculate(ch_dev_t *dev_ptr) {
	uint32_t cpu_freq = 0;
#ifdef INCLUDE_SHASTA_SUPPORT
	clock_control_t *clock_ctrl_ptr    = (clock_control_t *)&((dev_ptr->sens_cfg_addr)->common.clock);
	raw_output_data_t *output_data_ptr = (raw_output_data_t *)&((dev_ptr->sens_cfg_addr)->raw);
	uint16_t raw_cpu_count;
	uint16_t reg_addr;
	uint8_t err = 0;

	/* Calculate CPU frequency */
	reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_ptr->fcount_cycles);  // fcount cycles
	chdrv_write_word(dev_ptr, reg_addr, dev_ptr->fcount_cycles);

	err = chdrv_event_trigger_and_wait(dev_ptr, EVENT_CPU_FCOUNT);  // start CPU freq count

	if (err) {
		CH_LOG_ERR("error waiting for EVENT_CPU_FCOUNT");
	}

	if (!err) {
		reg_addr = (uint16_t)(uintptr_t) & (output_data_ptr->cpu_clock_fcount);  // CPU freq count
		chdrv_read_word(dev_ptr, reg_addr, &raw_cpu_count);

		cpu_freq = (dev_ptr->rtc_frequency * raw_cpu_count) / (dev_ptr->fcount_cycles / 16);

		CH_LOG_INFO("raw_cpu_count = %u  cpu_freq = %lu Hz", raw_cpu_count, cpu_freq);
	}

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	cpu_freq = (dev_ptr->op_frequency * 16);  // estimate CPU frequency
#endif  // INCLUDE_SHASTA_SUPPORT

	return cpu_freq;
}

/*!
 * \brief  Run sensor built-in-self-test (BIST)
 *
 * \param dev_ptr 	pointer to the ch_dev_t device descriptor for a sensor
 */
uint8_t chdrv_run_bist(ch_dev_t *dev_ptr) {
	uint8_t err = 0;

#ifdef INCLUDE_SHASTA_SUPPORT
	uint16_t pmut_trim;
	uint16_t pmut_trim_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->common.clock.pmut_trim);  // PMUT trim

	chdrv_read_word(dev_ptr, pmut_trim_addr, &pmut_trim);

	CH_LOG_DEBUG("Triggering BIST :");
	CH_LOG_DEBUG("pmut freq trim before = 0x%04x", pmut_trim);

	chdrv_int_interrupt_enable(dev_ptr);
	err = chdrv_event_trigger_and_wait(dev_ptr, EVENT_BIST);

	if (err) {
		CH_LOG_ERR("error waiting for EVENT_BIST");
	}

	if (!err) {
		chdrv_read_word(dev_ptr, pmut_trim_addr, &pmut_trim);
		dev_ptr->pmut_trim = pmut_trim;

		CH_LOG_DEBUG("pmut freq trim after = 0x%04x", pmut_trim);
	}

#ifdef READ_BIST_DATA  // Not needed for normal startup sequence
	bist_t *bist_addr = (bist_t *)&((dev_ptr->sens_cfg_addr)->bist);
	bist_t bist_data;  // local copy
	/* Read BIST data */

	if (!err) {
		err |= chdrv_burst_read(dev_ptr, (uint16_t)(uintptr_t)bist_addr, (uint8_t *)&bist_data, sizeof(bist_data));
	}

	if (!err) {
#if IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_DEBUG)
		uint8_t num_xcvr_inst       = sizeof(bist_data.tx_opt_cal_inst) / sizeof(bist_data.tx_opt_cal_inst[0]);
		uint16_t fcount             = (uint16_t)bist_data.fcount;
		uint16_t pmut_clock_fn_code = (uint16_t)bist_data.pmut_clock_fn_code;
		uint16_t bist_sf            = (uint16_t)bist_data.sf;
		uint16_t bist_rd0           = (uint16_t)bist_data.rd[0];
		uint16_t bist_rd1           = (uint16_t)bist_data.rd[1];
		uint16_t cmd_config;
		uint16_t length;

		CH_LOG_DEBUG("\r\nBIST:  fcount=%d  pmut_clock_fn_code=0x%04x  sf=%d  rd=[%d,%d]", fcount, pmut_clock_fn_code,
		             bist_sf, bist_rd0, bist_rd1);

		for (int i = 0; i < num_xcvr_inst; i++) {
			cmd_config = (uint16_t)bist_data.tx_opt_cal_inst[i].cmd_config;
			length     = (uint16_t)bist_data.tx_opt_cal_inst[i].length;
			CH_LOG_DEBUG("   PMUT instr %d:  cmd_config=0x%04x  length=%d", i, cmd_config, length);
		}
#endif

	} else {
		CH_LOG_ERR("Error running BIST");
	}
#endif  // READ_BIST_DATA

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	(void)dev_ptr;                            // not supported on CHx01
	err = 1;
#endif  // INCLUDE_SHASTA_SUPPORT
	return err;
}

/*!
 * \brief  Calibrate the sensor real-time clock against the host microcontroller clock.
 *
 * \param grp_ptr pointer to the ch_group_t config structure for a group of sensors
 *
 * This function sends a pulse (timed by the host MCU) on the INT line to each sensor device
 * in the group, then reads back the counts of sensor RTC cycles that elapsed during that pulse
 * on each individual device.  The result is stored in the ch_dev_t config structure for each
 * device and is subsequently used during range calculations.
 *
 * The length of the pulse is \a dev_ptr->rtc_cal_pulse_ms milliseconds (typically 100).  This
 * value is set during \a ch_init().
 *
 * \note The calibration pulse is sent to all devices in the group at the same time.  Therefore
 * all connected devices will see the same reference pulse length.
 *
 */
void chdrv_group_measure_rtc(ch_group_t *grp_ptr) {
	uint8_t i;
	const uint32_t pulselength = grp_ptr->rtc_cal_pulse_ms;

	/* Make sure TRIG line is inactive  */
	chdrv_trig_group_deassert(grp_ptr);

	/* Configure the host's side of the TRIG pin as an output */
	chdrv_trig_group_set_dir_out(grp_ptr);

	/* Make sure TRIG line is inactive */
	chdrv_trig_group_deassert(grp_ptr);

	/* Set up RTC calibration */
	for (i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr = grp_ptr->device[i];
#ifdef INCLUDE_SHASTA_SUPPORT
		if (grp_ptr->sensor_trig_pin == 2) {
			uint16_t trigcfg_addr =
					(uint16_t)(uintptr_t) & ((shasta_config_t *)SHASTA_FIXED_CFG_ADDR)->meas_queue.trigsrc;
			chdrv_write_byte(dev_ptr, trigcfg_addr, TRIGSRC_HWTRIGGER_INT2);
		}
#endif

		if (dev_ptr->sensor_connected) {
			dev_ptr->current_fw->calib_funcs->prepare_pulse_timer(dev_ptr);
		}
	}

	chbsp_delay_ms(10);  // delay before sending pulse

	/* Trigger a pulse on the TRIG line */
	chdrv_trig_group_assert(grp_ptr);

#ifdef INCLUDE_SHASTA_SUPPORT
	/* Shasta uses two separated pulses, so end the first one */
	chbsp_delay_us(10);                  // short duration
	chdrv_trig_group_deassert(grp_ptr);  // end pulse
#endif

	chbsp_delay_ms(pulselength);  // delay for calibration pulse duration

#ifdef INCLUDE_SHASTA_SUPPORT
	/* Shasta uses two separated pulses, so begin the second one */
	chdrv_trig_group_assert(grp_ptr);  // start pulse
	chbsp_delay_us(10);                // short duration
#endif

	chdrv_trig_group_deassert(grp_ptr);  // end pulse

#ifdef INCLUDE_SHASTA_SUPPORT
	/* Configure the TRIG pin as an input again */
	chdrv_trig_group_set_dir_in(grp_ptr);

	// /* Wait for all sensors to complete
	chbsp_delay_us(100);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	/* Keep the IO held for at least 50 us to allow the ASIC FW to deactivate the PT logic.
	   It will be set as input later once we will expect INT from the sensor. */
	chbsp_delay_us(100);
#endif

	/* Store RTC cal results */
	for (i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr = grp_ptr->device[i];
		if (dev_ptr->sensor_connected) {
			dev_ptr->rtc_status = CH_RTC_STATUS_CAL_DONE;
			dev_ptr->current_fw->calib_funcs->store_pt_result(dev_ptr);
		}
	}
}

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
void chdrv_group_measure_rtc_no_pulse(ch_group_t *grp_ptr) {
	uint8_t i;

	/* Configure the host's side of the INT pin as an output */
	chdrv_int_group_set_dir_out(grp_ptr);

	/* Make sure INT line is inactive */
	chdrv_int_group_deassert(grp_ptr);

	/* Set up RTC calibration */
	for (i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr = grp_ptr->device[i];

		if (dev_ptr->sensor_connected) {
			dev_ptr->current_fw->calib_funcs->prepare_pulse_timer(dev_ptr);
		}
	}

	/* Store RTC cal results */
	for (i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr = grp_ptr->device[i];
		if (dev_ptr->sensor_connected) {

			dev_ptr->current_fw->calib_funcs->store_pt_result(dev_ptr);
		}
	}
}

void chdrv_group_measure_pmut(ch_group_t *grp_ptr) {

	/* Store BIST and PMUT calibration results */
	for (uint8_t i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr = grp_ptr->device[i];
		if (dev_ptr->sensor_connected) {

			/* Call calibration func */
			dev_ptr->current_fw->calib_funcs->store_op_freq(dev_ptr);

			if (dev_ptr->current_fw->calib_funcs->store_bandwidth != NULL) {
				dev_ptr->current_fw->calib_funcs->store_bandwidth(dev_ptr);
			}

			/* Calculate amplitude scale factor */
			ch_iq_sample_t sf_sample;
			uint16_t scalefactor_idx;

#ifdef INCLUDE_SHASTA_SUPPORT
			scalefactor_idx = ICU_SCALEFACTOR_INDEX;
#elif defined(INCLUDE_WHITNEY_SUPPORT)
			scalefactor_idx = CHX01_SCALEFACTOR_INDEX;
#endif
			ch_get_iq_data(dev_ptr, &sf_sample, scalefactor_idx, 1, CH_IO_MODE_BLOCK);
			dev_ptr->amp_scale_factor = ch_iq_to_amplitude(&sf_sample);
		}
	}
}

/*!
 * \brief Convert register values to a range using the calibration data.
 *
 * \param dev_ptr 	pointer to the ch_dev_t config structure for a sensor
 * \param tof 		value of sensor TOF register
 * \param tof_sf 	value of sensor TOF_SF register
 *
 * \return range in millimeters, or \a CH_NO_TARGET (0xFFFFFFFF) if no object is detected.
 *
 * The range result format is fixed point with 5 binary fractional digits (divide by 32 to
 * convert to mm).
 *
 * This function takes the time-of-flight and scale factor values from the sensor,
 * and computes the actual one-way range based on the formulas given in the sensor
 * datasheet.
 */
uint32_t chdrv_one_way_range(ch_dev_t *dev_ptr, uint16_t tof, uint16_t tof_sf) {
	uint32_t num   = (CH_SPEEDOFSOUND_MPS * dev_ptr->group->rtc_cal_pulse_ms * (uint32_t)tof);
	uint32_t den   = ((uint32_t)dev_ptr->rtc_cal_result * (uint32_t)tof_sf) >> 10;
	uint32_t range = (num / den);

	if (tof == UINT16_MAX) {
		return CH_NO_TARGET;
	}

	if (dev_ptr->part_number == CH201_PART_NUMBER) {
		range *= 2;  // CH-201 range (TOF) encoding is 1/2 of actual
	}

	CH_LOG_DEBUG("%u:%u: timeOfFlight=%u, tofScaleFactor=%u, num=%lu, den=%lu, range=%lu", dev_ptr->bus_index,
	             dev_ptr->io_index, tof, tof_sf, num, den, range);

	return range;
}

/*!
 * \brief Add an I2C/SPI transaction to the non-blocking queue
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 * \param dev_ptr 	pointer to an individual ch_dev_t config structure for a sensor
 * \param rd_wrb 	read/write indicator: 0 if write operation, 1 if read operation
 * \param type		type of transaction (standard, program interface, or external)
 * \param addr		I2C address
 * \param nbytes 	number of bytes to read/write
 * \param data_ptr 		pointer to buffer to receive data or containing data to send
 *
 * \return 0 if successful, non-zero otherwise
 */
int chdrv_group_queue(ch_group_t *grp_ptr, ch_dev_t *dev_ptr, uint8_t rd_wrb, uint8_t type, uint16_t addr,
                      uint16_t nbytes, uint8_t *data_ptr) {

	uint8_t bus_num = ch_get_bus(dev_ptr);
	int ret_val;

	chdrv_queue_t *q       = &(grp_ptr->queue[bus_num]);
	chdrv_transaction_t *t = &(q->transaction[q->len]);

	if (q->len < CHDRV_MAX_QUEUE_LENGTH) {
		t->databuf  = data_ptr;
		t->dev_ptr  = dev_ptr;
		t->addr     = addr;
		t->nbytes   = nbytes;
		t->rd_wrb   = rd_wrb;
		t->type     = type;
		t->xfer_num = 0;
		q->len++;
		ret_val = 0;
	} else {
		ret_val = 1;
	}

	return ret_val;
}

/*!
 * \brief Start a non-blocking sensor readout
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 *
 * This function starts a non-blocking I/O operation on the specified group of sensors.
 */
void chdrv_group_start_nb(ch_group_t *grp_ptr) {

	for (int bus_num = 0; bus_num < grp_ptr->num_buses; bus_num++) {
		chdrv_queue_t *q = &(grp_ptr->queue[bus_num]);

		if ((q->len != 0) && !(q->running)) {
			chdrv_group_irq_handler(grp_ptr, bus_num);
		}
	}
}

/*!
 * \brief Continue a non-blocking readout
 *
 * \param grp_ptr 				pointer to the ch_group_t config structure for a group of sensors
 * \param bus_index		index value identifying I2C/SPI bus within group
 *
 * Call this function once from your I2C interrupt handler each time it executes.
 * It will call the user's callback routine (grp_ptr->io_complete_callback) when all transactions
 * are complete.
 */
#ifdef INCLUDE_WHITNEY_SUPPORT
void chdrv_group_irq_handler(ch_group_t *grp_ptr, uint8_t bus_index) {
	int i;
	int transactions_pending;
	chdrv_queue_t *q       = &(grp_ptr->queue[bus_index]);
	chdrv_transaction_t *t = &(q->transaction[q->idx]);
	ch_dev_t *dev_ptr      = NULL;

	if (q->idx < q->len) {
		dev_ptr    = q->transaction[q->idx].dev_ptr;
		q->running = 1;

		if (t->type == CHDRV_NB_TRANS_TYPE_EXTERNAL) {
			/* Externally-requested transfer */

			(q->idx)++;
			chbsp_external_irq_handler(t);
			t->xfer_num++;  // count this transfer

		} else if (t->type == CHDRV_NB_TRANS_TYPE_PROG) {
			/* Programming interface transfer */

			/* programming interface has max transfer size - check if still more to do during this transaction */
			uint8_t total_xfers = (t->nbytes + (CH_PROG_XFER_SIZE - 1)) / CH_PROG_XFER_SIZE;

			if (t->xfer_num < total_xfers) {
				/* still need to complete this transaction */

				uint16_t bytes_left;
				uint16_t xfer_bytes;

				bytes_left = (t->nbytes - (t->xfer_num * CH_PROG_XFER_SIZE));

				if (t->rd_wrb) {  // only read operations supported for now

					if (grp_ptr->i2c_drv_flags & I2C_DRV_FLAG_RESET_AFTER_NB) {
						chbsp_i2c_reset(dev_ptr);  // reset I2C bus if BSP says it's needed */
					}

					chbsp_program_enable(dev_ptr);  // assert PROG pin

					uint8_t message[] = {(0x80 | CH_PROG_REG_CTL), 0x09};  // read burst command

					if (bytes_left > CH_PROG_XFER_SIZE) {
						xfer_bytes = CH_PROG_XFER_SIZE;
					} else {
						xfer_bytes = bytes_left;
					}
					chdrv_prog_write(dev_ptr, CH_PROG_REG_ADDR, (t->addr + (t->xfer_num * CH_PROG_XFER_SIZE)));
					chdrv_prog_write(dev_ptr, CH_PROG_REG_CNT, (xfer_bytes - 1));
					(void)chdrv_prog_i2c_write(dev_ptr, message, sizeof(message));
					(void)chdrv_prog_i2c_read_nb(dev_ptr, (t->databuf + (t->xfer_num * CH_PROG_XFER_SIZE)), xfer_bytes);
				}

				t->xfer_num++;  // count this transfer

				/* if this is the last transfer in this transaction, advance queue index */
				if (t->xfer_num >= total_xfers) {
					(q->idx)++;
				}
			}

		} else {
			/* Standard transfer */
			if (t->rd_wrb) {
				(q->idx)++;
				chbsp_i2c_mem_read_nb(t->dev_ptr, t->addr, t->databuf, t->nbytes);

			} else {
				(q->idx)++;
				chbsp_i2c_mem_write_nb(t->dev_ptr, t->addr, t->databuf, t->nbytes);
			}
			t->xfer_num++;  // count this transfer
		}
		transactions_pending = 1;
	} else {

		if (q->idx >= 1) {
			dev_ptr = q->transaction[(q->idx - 1)].dev_ptr;  // get dev_ptr for previous completed transaction
			if (dev_ptr != NULL) {
				chbsp_program_disable(dev_ptr);  // de-assert PROG pin for completed transaction

				if (grp_ptr->i2c_drv_flags & I2C_DRV_FLAG_RESET_AFTER_NB) {
					chbsp_i2c_reset(dev_ptr);  // reset I2C bus if BSP requires it
				}
			}
		}

		q->len               = 0;
		q->idx               = 0;
		q->running           = 0;
		transactions_pending = 0;

		for (i = 0; i < grp_ptr->num_buses; i++) {
			if (grp_ptr->queue[i].len) {
				transactions_pending = 1;
				break;
			}
		}
	}

	if (!transactions_pending) {
		ch_io_complete_callback_t func_ptr = grp_ptr->io_complete_callback;

		if (func_ptr != NULL) {
			(*func_ptr)(grp_ptr);
		}
	}
}
#else
void chdrv_group_irq_handler(ch_group_t *grp_ptr, uint8_t bus_index) {
	int i;
	int transactions_pending;
	chdrv_queue_t *q       = &(grp_ptr->queue[bus_index]);
	chdrv_transaction_t *t = &(q->transaction[q->idx]);
	ch_dev_t *dev_ptr      = q->transaction[q->idx].dev_ptr;
	uint8_t cmd_buf[3];
	uint16_t command;

	/* Deassert chipselect of previous completed transaction */
	if (q->idx >= 1) {
		dev_ptr = q->transaction[(q->idx - 1)].dev_ptr;  // get dev_ptr for previous completed transaction
		if (dev_ptr != NULL)
			chbsp_spi_cs_off(dev_ptr);  // de-assert chip select
	}

	/* Launch next transaction */
	if (q->idx < q->len) {
		dev_ptr    = q->transaction[q->idx].dev_ptr;
		q->running = 1;

		if (t->type == CHDRV_NB_TRANS_TYPE_STD) {
			/* Standard transfer */
			if (t->rd_wrb) {  // only read operations supported for now
				(q->idx)++;

				// reading from data or prog mem
				command = SPI_CMD_MEM_ACCESS;
				if (t->addr < SHASTA_PROG_MEM_ADDR)
					command |= t->addr - SHASTA_DATA_MEM_ADDR;
				else
					command |= (t->addr - SHASTA_PROG_MEM_BASE_ADDR) | SPI_CMD_PROG_MEM;

				cmd_buf[0] = (command & 0x00FF);         // LSB
				cmd_buf[1] = ((command & 0xFF00) >> 8);  // MSB
				cmd_buf[2] = 0;

				chbsp_spi_cs_on(dev_ptr);              // assert chip select
				chbsp_spi_write(dev_ptr, cmd_buf, 3);  // send command
				chbsp_spi_mem_read_nb(t->dev_ptr, t->addr, t->databuf, t->nbytes);
			}
			t->xfer_num++;  // count this transfer
		}
		transactions_pending = 1;
	} else {
		q->len               = 0;
		q->idx               = 0;
		q->running           = 0;
		transactions_pending = 0;

		for (i = 0; i < grp_ptr->num_buses; i++) {
			if (grp_ptr->queue[i].len) {
				transactions_pending = 1;
				break;
			}
		}
	}

	if (!transactions_pending) {
		ch_io_complete_callback_t func_ptr = grp_ptr->io_complete_callback;

		if (func_ptr != NULL) {
			(*func_ptr)(grp_ptr);
		}
	}
}

#endif  // INCLUDE_WHITNEY_SUPPORT

#ifdef INCLUDE_WHITNEY_SUPPORT
/*!
 * \brief Wait for an individual sensor to finish start-up procedure.
 *
 * \param dev_ptr 			pointer to the ch_dev_t config structure for a sensor
 * \param timeout_ms 	number of milliseconds to wait for sensor to finish start-up before returning failure
 *
 * \return 0 if startup sequence finished, non-zero if startup sequence timed out or sensor is not connected
 *
 * After the sensor is programmed, it executes an internal start-up and self-test sequence. This function waits the
 * specified time in milliseconds for the sensor to finish this sequence.
 */
int chdrv_wait_for_lock(ch_dev_t *dev_ptr, uint16_t timeout_ms) {
	uint32_t start_time = chbsp_timestamp_ms();
	int ch_err          = !(dev_ptr->sensor_connected);

	while (!ch_err && !(dev_ptr->current_fw->calib_funcs->get_locked_state(dev_ptr))) {
		chbsp_delay_ms(10);
		ch_err = ((chbsp_timestamp_ms() - start_time) > timeout_ms);
	}

	if (ch_err) {
		CH_LOG_INFO("Sensor %hhu initialization timed out or missing", dev_ptr->io_index);
	}

	return ch_err;
}

/*!
 * \brief Wait for all sensors to finish start-up procedure.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * \return 0 if startup sequence finished on all detected sensors, non-zero if startup sequence
 * timed out on any sensor(s).
 *
 * After each sensor is programmed, it executes an internal start-up and self-test sequence. This
 * function waits for all sensor devices to finish this sequence.  For each device, the maximum
 * time to wait is \a CHDRV_FREQLOCK_TIMEOUT_MS milliseconds.
 */
int chdrv_group_wait_for_lock(ch_group_t *grp_ptr) {
	int ch_err = 0;

	for (uint8_t i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr = grp_ptr->device[i];

		if (dev_ptr->sensor_connected) {
			ch_err |= chdrv_wait_for_lock(dev_ptr, CHDRV_FREQLOCK_TIMEOUT_MS);
		}
	}
	return ch_err;
}
#endif  // INCLUDE_WHITNEY_SUPPORT

/*!
 * \brief Start a measurement in hardware triggered mode.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * \return 0 if success, non-zero if \a grp_ptr pointer is invalid
 *
 * This function starts a triggered measurement on each sensor in a group, by briefly asserting the INT line to each
 * device. Each sensor must have already been placed in hardware triggered mode before this function is called.
 */
int chdrv_group_hw_trigger(ch_group_t *grp_ptr) {
	int ch_err = (grp_ptr == NULL);
	ch_dev_t *dev_ptr;
	uint8_t dev_num;

	if (!ch_err) {
		if (grp_ptr->sensor_int_pin == grp_ptr->sensor_trig_pin) {
			// Disable interrupt before triggering pulse on shared INT/TRIG line
			chdrv_int_group_interrupt_disable(grp_ptr);  // *** disable interrupts ***
		}

		chdrv_trig_group_set_dir_out(grp_ptr);  // Set TRIG pin(s) as output

		if (grp_ptr->pretrig_delay_us == 0) {
			/* No pre-trigger delay - trigger rx-only and tx/rx nodes together */
			chdrv_trig_group_assert(grp_ptr);
			chbsp_delay_us(CHDRV_TRIGGER_PULSE_US);
			chdrv_trig_group_deassert(grp_ptr);
		} else {
			/* Pre-trigger rx-only nodes, delay, then trigger tx/rx nodes */

			// Pre-trigger any rx-only nodes
			for (dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
				dev_ptr = grp_ptr->device[dev_num];

				if (dev_ptr->mode == CH_MODE_TRIGGERED_RX_ONLY) {  // if rx-only mode
					chdrv_trig_assert(dev_ptr);                    // trigger this sensor
				}
			}

			chbsp_delay_us(CHDRV_TRIGGER_PULSE_US);  // delay for pulse duration

			chdrv_trig_group_deassert(grp_ptr);  // end pulse on all lines

			// Delay before triggering tx/rx node(s)
			chbsp_delay_us(grp_ptr->pretrig_delay_us - (CHDRV_TRIGGER_PULSE_US + CHDRV_DELAY_OVERHEAD_US));

			// Trigger any tx/rx nodes
			for (dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
				dev_ptr = grp_ptr->device[dev_num];

				if (dev_ptr->mode == CH_MODE_TRIGGERED_TX_RX) {  // if tx/rx mode
					chdrv_trig_assert(dev_ptr);                  // trigger this sensor
				}
			}

			chbsp_delay_us(CHDRV_TRIGGER_PULSE_US);  // delay for pulse duration

			chdrv_trig_group_deassert(grp_ptr);  // end pulse on all lines
		}

		if (grp_ptr->sensor_int_pin == grp_ptr->sensor_trig_pin) {
			// Delay a bit before re-enabling pin interrupt to avoid possibly triggering on falling-edge noise
			chbsp_delay_us(CHDRV_POST_TRIG_IEN_DELAY_US);

			chdrv_int_group_set_dir_in(grp_ptr);        // make shared INT/TRIG line an input again
			chdrv_int_group_interrupt_enable(grp_ptr);  // *** enable interrupts ***
		}
	}
	return ch_err;
}

/*!
 * \brief Start a measurement in hardware triggered mode on one sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if success, non-zero if \a dev_ptr pointer is invalid
 *
 * This function starts a triggered measurement on a single sensor, by briefly asserting the INT line to the device.
 * The sensor must have already been placed in hardware triggered mode before this function is called.
 *
 * \note This function requires implementing the optional BSP functions to control the INT pin direction
 *       and level for individual sensors (\a chbsp_set_int1_dir_in(), \a chbsp_set_int1_dir_out(), \a chbsp_int1_set(),
 * and \a chbsp_int1_clear()).
 */
int chdrv_hw_trigger(ch_dev_t *dev_ptr) {
	int ch_err       = !dev_ptr;
	uint8_t trig_pin = dev_ptr->group->sensor_trig_pin;
	uint8_t int_pin  = dev_ptr->group->sensor_int_pin;

	if (!ch_err) {
		if (int_pin == trig_pin) {
			// Disable interrupt before triggering pulse on shared INT/TRIG line
			chdrv_int_interrupt_disable(dev_ptr);  // *** disable interrupt ***
		}

		chdrv_trig_set_dir_out(dev_ptr);  // Set TRIG pin as output

		// Generate pulse
		chdrv_trig_assert(dev_ptr);
		chbsp_delay_us(CHDRV_TRIGGER_PULSE_US);
		chdrv_trig_deassert(dev_ptr);

		if (int_pin == trig_pin) {
			// Delay a bit before re-enabling pin interrupt to avoid possibly triggering on falling-edge noise
			chbsp_delay_us(CHDRV_POST_TRIG_IEN_DELAY_US);

			chdrv_int_set_dir_in(dev_ptr);        // make shared INT/TRIG line an input again
			chdrv_int_interrupt_enable(dev_ptr);  // *** enable interrupt ***
		}
	}
	return ch_err;
}

/*!
 * \brief Write to a sensor programming register.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param reg_addr 	sensor programming register address.
 * \param data 		8-bit or 16-bit data to transmit.
 *
 * \return 0 if write to sensor succeeded, non-zero otherwise
 *
 * This local function writes a value to a sensor programming register.
 */
int chdrv_prog_write(ch_dev_t *dev_ptr, uint8_t reg_addr, uint16_t data) {
	uint8_t ret_val = 1;
	(void)dev_ptr;

	/* Set register address write bit */
	reg_addr |= 0x80;

#ifdef INCLUDE_WHITNEY_SUPPORT
	/* Write the register address, followed by the value to be written */
	uint8_t message[] = {reg_addr, (uint8_t)data, (uint8_t)(data >> 8)};

	/* For the 2-byte registers, we also need to also write MSB after the LSB */
	ret_val = chdrv_prog_i2c_write(dev_ptr, message, (1 + CH_PROG_SIZEOF(reg_addr)));
#else
	(void)data;
#endif  // INCLUDE_WHITNEY_SUPPORT

	return ret_val;
}

#ifdef INCLUDE_WHITNEY_SUPPORT
/*!
 * \brief Write to sensor memory in programming mode.
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
int chdrv_prog_mem_write(ch_dev_t *dev_ptr, uint16_t addr, const uint8_t *message, uint16_t nbytes) {
	int ch_err = (nbytes == 0);

	if (!ch_err) {
		ch_err = chdrv_prog_write(dev_ptr, CH_PROG_REG_ADDR, addr);
	}

	if (nbytes == 1 || (nbytes == 2 && !(addr & 1))) {
		uint16_t data = message[0] | (message[1] << 8);
		if (!ch_err) {
			ch_err = chdrv_prog_write(dev_ptr, CH_PROG_REG_DATA, data);
		}
		if (!ch_err) {
			uint8_t opcode = (0x03 | ((nbytes == 1) ? 0x08 : 0x00));  // TODO need define

			ch_err = chdrv_prog_write(dev_ptr, CH_PROG_REG_CTL, opcode);
		}
	} else {
		const uint8_t burst_hdr[2] = {0xC4, 0x0B};  // TODO need define

		if (!ch_err) {
			ch_err = chdrv_prog_write(dev_ptr, CH_PROG_REG_CNT, (nbytes - 1));
		}
		if (!ch_err) {
			ch_err = chdrv_prog_i2c_write(dev_ptr, (uint8_t *)burst_hdr, sizeof(burst_hdr));
		}
		if (!ch_err) {
			ch_err = chdrv_prog_i2c_write(dev_ptr, message, nbytes);
		}
	}
	return ch_err;
}

/*!
 * \brief Read from a sensor programming register.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 * \param reg_addr 	sensor programming register address
 * \param data_ptr	 	pointer to a buffer where read bytes will be placed
 *
 * \return 0 if read from sensor succeeded, non-zero otherwise
 *
 * This local function reads a value from a sensor programming register.
 */
static int prog_read(ch_dev_t *dev_ptr, uint8_t reg_addr, uint16_t *data_ptr) {
	uint8_t nbytes = CH_PROG_SIZEOF(reg_addr);

	uint8_t read_data[2];
	uint8_t message[1] = {0x7F & reg_addr};

	int ch_err = chdrv_prog_i2c_write(dev_ptr, message, sizeof(message));

	if (!ch_err) {
		ch_err = chdrv_prog_i2c_read(dev_ptr, read_data, nbytes);
	}

	if (!ch_err) {
		*data_ptr = read_data[0];
		if (nbytes > 1) {
			*data_ptr |= (((uint16_t)read_data[1]) << 8);
		}
	}

	return ch_err;
}

static inline uint8_t run_charge_pumps(ch_dev_t *dev_ptr) {
	uint8_t ch_err;
	uint16_t write_val;

	/* PMUT.CNTRL4 = HVVSS_FON */
	write_val = PMUT_CNTRL4_HVVSS_FON;
	ch_err    = chdrv_prog_mem_write(dev_ptr, CH_PROG_ADDR_PMUT_CNTRL4_REG, (uint8_t *)&write_val, sizeof(write_val));
	chbsp_delay_ms(CHDRV_DELAY_EN_CHARGE_PUMP_MS);
	/* PMUT.CNTRL4 = (HVVSS_FON | HVVDD_FON) */
	write_val  = PMUT_CNTRL4_HVVSS_FON | PMUT_CNTRL4_HVVDD_FON;
	ch_err    |= chdrv_prog_mem_write(dev_ptr, CH_PROG_ADDR_PMUT_CNTRL4_REG, (uint8_t *)&write_val, sizeof(write_val));
	chbsp_delay_ms(CHDRV_DELAY_EN_CHARGE_PUMP_MS);
	/* PMUT.CNTRL4 = 0 */
	write_val  = 0x0000;
	ch_err    |= chdrv_prog_mem_write(dev_ptr, CH_PROG_ADDR_PMUT_CNTRL4_REG, (uint8_t *)&write_val, sizeof(write_val));

	return ch_err;
}

static inline uint8_t whitney_detect_and_program(ch_dev_t *dev_ptr) {
	uint8_t ch_err = 0;

	chbsp_program_enable(dev_ptr);  // assert PROG pin

	if (!chdrv_prog_ping(dev_ptr)) {
		/* prog_ping failed - no device found */
		CH_LOG_INFO("Ping failed, device %u not found", dev_ptr->io_index);

		dev_ptr->sensor_connected = 0;
		goto EXIT_WHITNEY_DETECT_AND_PROGRAM;
	}

	/* Device found on bus */
	CH_LOG_INFO("Device %u found on bus", dev_ptr->io_index);

	dev_ptr->sensor_connected = 1;
	dev_ptr->trig_type        = CH_TRIGGER_TYPE_HW;  // use hardware triggering by default

#if IS_CH_LOG_LEVEL_USED(CH_LOG_LEVEL_DEBUG)
	if (!ch_err) {
		uint16_t prog_stat = UINT16_MAX;
		ch_err             = prog_read(dev_ptr, CH_PROG_REG_STAT, &prog_stat);
		CH_LOG_DEBUG("PROG_STAT: 0x%02X", prog_stat);
	}
#endif

	if (!ch_err) {
		dev_ptr->asic_gen = CH_ASIC_GEN_1_WHITNEY;
		dev_ptr->int_mode = CH_INTERRUPT_MODE_PULSE;  // always uses interrupt pulse

		ch_err  = init_ram(dev_ptr);        // init ram values
		ch_err |= write_firmware(dev_ptr);  // transfer program
		ch_err |= reset_and_halt(dev_ptr);  // reset asic, since it was running mystery code before halt
	}

	if (!ch_err) {
		CH_LOG_INFO("Changing I2C address to %u", dev_ptr->i2c_address);

		ch_err = chdrv_prog_mem_write(dev_ptr, CH_PROG_ADDR_DEV_I2C_ADDR_REG, &dev_ptr->i2c_address, 1);
	}

	/* Run charge pumps */
	if (!ch_err) {
		ch_err = run_charge_pumps(dev_ptr);
	}

	if (!ch_err) {
		ch_err = chdrv_prog_write(dev_ptr, CH_PROG_REG_CPU, 2);  // Exit programming mode and run the chip
	}

EXIT_WHITNEY_DETECT_AND_PROGRAM:
	chbsp_program_disable(dev_ptr);  // de-assert PROG pin

	if (ch_err) {  // if error, reinitialize I2C bus associated with this device
		chbsp_debug_toggle(CHDRV_DEBUG_PIN_NUM);
		chbsp_i2c_reset(dev_ptr);

		dev_ptr->sensor_connected = 0;  // only marked as connected if no errors
	}

	return ch_err;
}

#endif  // INCLUDE_WHITNEY_SUPPORT

#ifdef INCLUDE_SHASTA_SUPPORT

/*!
 * \brief Reset and run a sensor
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if write to sensor succeeded, non-zero otherwise
 *
 * This function resets and runs a sensor device by writing to the control registers.
 */
static int reset_and_run(ch_dev_t *dev_ptr) {
	int ch_err = 0;

	ch_err |= chdrv_sys_ctrl_write(dev_ptr, SYS_CTRL_DEBUG);  // reset (SYS_CTRL_RESET_N is low)
	ch_err |= chdrv_sys_ctrl_write(dev_ptr, (SYS_CTRL_DEBUG | SYS_CTRL_RESET_N));
	// clear reset, stay in debug mode

	chdrv_dbg_reg_write(dev_ptr, SHASTA_DBG_REG_CPU_STAT, CPU_STAT_PUC_PND);  // Clear PUC reset occurred status bit.
	chdrv_dbg_reg_write(dev_ptr, SHASTA_DBG_REG_CPU_CTL, (CPU_CTL_RST_BRK_EN | CPU_CTL_FRZ_BRK_EN | CPU_CTL_RUN));
	// run CPU, enable reset, freeze wdog/timers when halted
	return ch_err;
}

static uint8_t exit_debug(ch_dev_t *dev_ptr) {
	uint8_t err          = 0;
	uint8_t sys_ctrl_val = 0;

	err = chdrv_sys_ctrl_read(dev_ptr, &sys_ctrl_val);

	if (!err) {
		sys_ctrl_val &= ~SYS_CTRL_DEBUG;  // clear debug
		err           = chdrv_sys_ctrl_write(dev_ptr, sys_ctrl_val);
	}

	return err;
}

int chdrv_read_buf_addr(ch_dev_t *dev_ptr) {
	int ch_err = 0;
	uint16_t buf_addr;
	uint16_t buf_addr_reg_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.reserved2);

	ch_err = chdrv_read_word(dev_ptr, buf_addr_reg_addr, &buf_addr);
	if (buf_addr != 0) {
		dev_ptr->buf_addr = buf_addr;
	} else {
		// for backwards compatibility before the reserved2 field was used
		// to store the buffer address
		dev_ptr->buf_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.IQdata);
	}
	return ch_err;
}

static inline uint8_t shasta_detect_and_program(ch_dev_t *dev_ptr) {
	uint8_t ch_err;

	if (!chdrv_prog_ping(dev_ptr)) {
		/* prog_ping failed - no device found */
		CH_LOG_INFO("Ping failed, device %u not found", dev_ptr->io_index);
		dev_ptr->sensor_connected = 0;
		/* continue without returning error */
		return 0;
	}

	/* device found on bus*/
	CH_LOG_INFO("Device %u found on bus", dev_ptr->io_index);

	dev_ptr->sensor_connected = 1;
	dev_ptr->trig_type        = CH_TRIGGER_TYPE_HW;       // use hardware triggering by default
	dev_ptr->asic_gen         = CH_ASIC_GEN_2_SHASTA;     // sensor ASIC design generation
	dev_ptr->int_mode         = CH_INTERRUPT_MODE_LATCH;  // uses latching (non-pulsed) interrupt by default

	ch_err  = reset_and_halt(dev_ptr);  // reset and enter debug mode for programming
	ch_err |= init_ram(dev_ptr);        // init ram values

	if (dev_ptr->group->sensor_int_pin != 1) {
		uint16_t intcfg_addr = (uint16_t)(uintptr_t) & ((shasta_config_t *)SHASTA_FIXED_CFG_ADDR)->meas_queue.intconfig;
		ch_err               = chdrv_write_byte(dev_ptr, intcfg_addr, INTCONFIG_DR_INT2);
	}

	chbsp_event_wait_setup((1 << dev_ptr->io_index));
	chdrv_int_interrupt_enable(dev_ptr);  // *** enable interrupt ***

	ch_err |= write_firmware(dev_ptr);  // transfer program

	ch_err |= reset_and_run(dev_ptr);  // reset asic, exit debug mode, and run

	if (!ch_err) {
		ch_err |= event_wait(dev_ptr);  // wait for sensor to interrupt
		if (ch_err) {
			CH_LOG_ERR("No reset event from sensor %u", dev_ptr->io_index);
		}
	}

	/* Get addr of shared config mem and algo info */
	if (!ch_err) {
		uint16_t config_addr;

		ch_err = chdrv_read_word(dev_ptr, SHASTA_CONFIG_PTR_ADDR, &config_addr);
		if (!ch_err) {
			dev_ptr->sens_cfg_addr = (shasta_config_t *)(uintptr_t)config_addr;

			uint16_t algo_info_addr;
			ch_err                       = chdrv_read_word(dev_ptr, SHASTA_ALGO_INFO_PTR_ADDR, &algo_info_addr);
			dev_ptr->sens_algo_info_addr = (ICU_ALGO_SHASTA_INFO *)(uintptr_t)algo_info_addr;
		}
		if (!ch_err) {
			ch_err = chdrv_read_buf_addr(dev_ptr);
		}
		if (!ch_err) {
			uint16_t ver_major_addr = (uint16_t)(uintptr_t)&dev_ptr->sens_cfg_addr->common.reg_map_format.major;
			uint16_t ver_minor_addr = (uint16_t)(uintptr_t)&dev_ptr->sens_cfg_addr->common.reg_map_format.minor;
			ch_err                  = chdrv_read_byte(dev_ptr, ver_major_addr, &dev_ptr->reg_fmt_ver_major);
			if (!ch_err) {
				ch_err = chdrv_read_byte(dev_ptr, ver_minor_addr, &dev_ptr->reg_fmt_ver_minor);
			}
		}

		CH_LOG_INFO("Sensor shared mem addr = 0x%04x", (uint16_t)(uintptr_t)dev_ptr->sens_cfg_addr);
		CH_LOG_INFO("Sensor algo info addr = 0x%04x", (uint16_t)(uintptr_t)dev_ptr->sens_algo_info_addr);
		CH_LOG_INFO("Sensor register map version = %u.%u", dev_ptr->reg_fmt_ver_major, dev_ptr->reg_fmt_ver_minor);
	}

	/* Copy OTP (one-time-programmable) mem contents to sensor ram and process contents.
	 * Firmware not including initialization feature may not be able to copy OTP
	 */
	if (!ch_err && dev_ptr->current_fw->fw_includes_sensor_init) {
		ch_err = chdrv_otpmem_read(dev_ptr);
	}

	/* Read sensor algorithm info */
	if (!ch_err) {
		ch_err = chdrv_algo_info_read(dev_ptr, &(dev_ptr->algo_info));
	}
	if (!ch_err) {
		uint16_t iq_data_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.IQdata);  // start of I/Q data
		// find the IQ buffer size through pointer arithmetic. IQ buffer is
		// always guaranteed to be followed by algo_out. Divide by 4 to get the
		// result in terms of IQ samples instead of bytes
		dev_ptr->current_fw->max_samples = ((uint16_t)dev_ptr->algo_info.algo_out_ptr - iq_data_addr) >> 2;
		CH_LOG_INFO("dev_ptr->current_fw->max_samples=%d", dev_ptr->current_fw->max_samples);

		/* Might point later on a dedicated algo config structure */
		dev_ptr->algo_cfg_ptr = NULL;
	}

	if (ch_err) {
		dev_ptr->sensor_connected = 0;  // only marked as connected if no errors
	}

	return ch_err;
}

#endif  // INCLUDE_SHASTA_SUPPORT

/*!
 * \brief Detect a connected sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 1 if sensor is found, 0 if no sensor is found
 *
 * This function checks for a sensor sensor on the I2C bus by attempting to reset, halt, and read from the device using
 * the programming interface I2C address (0x45).
 *
 * In order for the device to respond, the PROG pin for the device must be asserted before this function is called.
 */
int chdrv_prog_ping(ch_dev_t *dev_ptr) {
	int ch_err = 0;

#ifdef INCLUDE_SHASTA_SUPPORT
	uint16_t reg_val         = 0;
	uint8_t sys_ctrl_reg_val = 0;

	ch_err |= chdrv_sys_ctrl_read(dev_ptr, (uint8_t *)&sys_ctrl_reg_val);

	ch_err |= chdrv_sys_ctrl_write(dev_ptr, SYS_CTRL_DEBUG);  // reset (SYS_CTRL_RESET_N is low)

	ch_err |= chdrv_sys_ctrl_write(dev_ptr, (SYS_CTRL_DEBUG | SYS_CTRL_RESET_N));

	if (!ch_err) {
		reg_val = 0;

		ch_err = chdrv_dbg_reg_read(dev_ptr, SHASTA_DBG_REG_CPU_ID_HI, &reg_val);

		ch_err |= (reg_val != SHASTA_CPU_ID_HI_VALUE); /* set err if not expected value */
	}

	if (!ch_err) {  // if a sensor was found, wait for power-on reset to clear
		sys_ctrl_reg_val = 0;

		do {
			ch_err = chdrv_sys_ctrl_read(dev_ptr, &sys_ctrl_reg_val);
		} while (!ch_err && !(sys_ctrl_reg_val & SYS_CTRL_POR_N));
	}

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	ch_err = reset_and_halt(dev_ptr);

	/* Try a dummy write to the sensor to make sure it's connected and working */
	uint16_t tmp  = 0;
	ch_err       |= prog_read(dev_ptr, CH_PROG_REG_PING, &tmp);

	if (!ch_err) {
		CH_LOG_INFO("Test I2C read: %04X", tmp);
	}
#endif  // INCLUDE_SHASTA_SUPPORT

	return !(ch_err); /* convert err to boolean indicator whether sensor was found */
}

/*!
 * \brief Detect, program, and start a sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if write to sensor succeeded, non-zero otherwise
 *
 * This function probes the I2C bus for the device.  If it is found, the sensor firmware is programmed into the
 * device, and the application I2C address is set.  Then the sensor is reset and execution starts.
 *
 * Once started, the sensor device will begin an internal initialization and self-test sequence.  The \a
 * chdrv_wait_for_lock() function may be used to wait for this sequence to complete.
 *
 * \note This routine will leave the PROG pin de-asserted when it completes.
 */
int chdrv_detect_and_program(ch_dev_t *dev_ptr) {
	if (!dev_ptr || (dev_ptr->current_fw == NULL)) {
		return 1;
	}

#ifdef INCLUDE_WHITNEY_SUPPORT
	return whitney_detect_and_program(dev_ptr);
#elif defined(INCLUDE_SHASTA_SUPPORT)
	return shasta_detect_and_program(dev_ptr);
#endif  // INCLUDE_WHITNEY_SUPPORT
}

/*!
 * \brief Put CHx01 sensors on a bus into an idle state
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor, used to identify the target I2C bus
 *
 * \return 0 if successful, non-zero on error
 *
 * This function loads a tiny idle loop program to all ASICs on a given i2c bus.  This function assumes that all of the
 * devices on the given bus are halted in programming mode (i.e. PROG line is asserted).
 *
 * \note This routine writes to all devices simultaneously, so I2C signalling (i.e. ack's) on the bus may be driven by
 * multiple slaves at once.
 */
int chdrv_set_idle(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_WHITNEY_SUPPORT
	const uint16_t idle_loop[2] = {0x4003, 0xFFFC};  // TODO need define
	int ch_err = chdrv_prog_mem_write(dev_ptr, CH_PROG_ADDR_IDLE_LOC, (uint8_t *)&idle_loop[0], sizeof(idle_loop));
	if (!ch_err) {
		ch_err = reset_and_halt(dev_ptr);
	}

	// keep wdt stopped after we exit programming mode
	uint16_t val = 0x5a80;  // TODO need define
	if (!ch_err) {
		ch_err = chdrv_prog_mem_write(dev_ptr, CH_PROG_ADDR_WDT_REG, (uint8_t *)&val, sizeof(val));
	}

	return ch_err;
#else
	(void)dev_ptr;  // does not apply to Shasta
	return 0;
#endif  // INCLUDE_WHITNEY_SUPPORT
}

/*!
 * \brief Detect, program, and start all sensors in a group.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * \return 0 for success, non-zero if write(s) failed to any sensor initially detected as present
 *
 * This function probes the I2C bus for each device in the group.  For each detected sensor, the sensor firmware is
 * programmed into the device, and the application I2C address is set.  Then the sensor is reset and execution starts.
 *
 * Once started, each sensor device will begin an internal initialization and self-test sequence.  The
 * \a chdrv_group_wait_for_lock() function may be used to wait for this sequence to complete on all devices in the
 * group.
 *
 * \note This routine will leave the PROG pin de-asserted for all devices in the group when it completes.
 */
int chdrv_group_detect_and_program(ch_group_t *grp_ptr) {
	int ch_err = 0;

	for (uint8_t i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr = grp_ptr->device[i];

		ch_err = chdrv_detect_and_program(dev_ptr);

		if (!ch_err && dev_ptr->sensor_connected) {
			grp_ptr->sensor_count++;
		}

		if (ch_err) {
			break;
		}
	}
	return ch_err;
}

/*!
 * \brief Initialize data structures and hardware for sensor interaction.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 * \param num_ports 	the total number of physical sensor ports available
 *
 * \return 0 if hardware initialization is successful, non-zero otherwise
 *
 * This function is called internally by \a chdrv_group_start().
 */
int chdrv_group_prepare(ch_group_t *grp_ptr) {
	int ch_err = !grp_ptr;
	uint8_t i;

	if (!ch_err) {
		grp_ptr->sensor_count = 0;

		for (i = 0; i < grp_ptr->num_buses; i++) {
			grp_ptr->queue[i].len          = 0;
			grp_ptr->queue[i].idx          = 0;
			grp_ptr->queue[i].read_pending = 0;
			grp_ptr->queue[i].running      = 0;
		}

		grp_ptr->sensor_int_pin  = CHIRP_SENSOR_INT_PIN;
		grp_ptr->sensor_trig_pin = CHIRP_SENSOR_TRIG_PIN;

#ifdef INCLUDE_WHITNEY_SUPPORT
		ch_err = chbsp_i2c_init();
#endif
	}

	return ch_err;
}

static void calibrate_rtc(ch_group_t *grp_ptr, uint8_t restart) {
	if (grp_ptr->rtc_cal_type == CH_RTC_CAL_BUS) {
		/* Calibrate RTC clocks using I/O bus clock (no pulse generation) */
		chdrv_group_measure_rtc_no_pulse(grp_ptr);
	}
	if ((grp_ptr->rtc_cal_type == CH_RTC_CAL_BUS) || (grp_ptr->rtc_cal_type == CH_RTC_CAL_MANUAL)) {
		/* RTC freq already set - synthesize missing input values using defaults */
		for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
			ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
			if (dev_ptr->sensor_connected) {
				dev_ptr->group->rtc_cal_pulse_ms = CH_COMMON_RTC_CAL_PULSE_MS;
				dev_ptr->rtc_cal_result =
						(uint16_t)((uint32_t)dev_ptr->rtc_frequency * CH_COMMON_RTC_CAL_PULSE_MS / 1000);
			}
		}
	} else if (!restart) {
		/* Calibrate RTC clocks if normal start */
		chdrv_group_measure_rtc(grp_ptr);
	}
}

#ifdef INCLUDE_WHITNEY_SUPPORT
static inline void set_all_devices_idle(ch_group_t *grp_ptr) {
	chbsp_reset_assert();
	for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++)
		chbsp_program_enable(grp_ptr->device[dev_num]);
	chbsp_delay_ms(1);
	chbsp_reset_release();

	/* For every i2c bus, set the devices idle in parallel, then disable programming mode for all devices on that bus
	 * This is kludgey because we don't have a great way of iterating over the i2c buses */
	ch_dev_t *prev_dev_ptr = grp_ptr->device[0];
	chdrv_set_idle(prev_dev_ptr); /* set devices on first bus to idle */

	for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
		ch_dev_t *dev_ptr = grp_ptr->device[dev_num];

		if (dev_ptr->bus_index != prev_dev_ptr->bus_index) /* if a different bus */
			chdrv_set_idle(dev_ptr);                       /* set devices on this bus to idle */

		chbsp_program_disable(dev_ptr);
		prev_dev_ptr = dev_ptr;
	}
}

/**
 * @brief      Counts the number of connected sensors per bus.
 *
 * @param      grp_ptr  The group pointer
 */
static inline void count_connected_sensors_per_bus(ch_group_t *grp_ptr) {
	/* init all counts */
	for (uint8_t bus_num = 0; bus_num < grp_ptr->num_buses; bus_num++)
		grp_ptr->num_connected[bus_num] = 0;

	/* count connected sensors per bus */
	for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
		const ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
		if (dev_ptr->sensor_connected)
			grp_ptr->num_connected[dev_ptr->bus_index] += 1;
	}
}

static inline uint8_t whitney_group_start(ch_group_t *grp_ptr) {
	uint8_t ch_err;
	uint8_t prog_tries = 0;
#if IS_CH_LOG_USED
	const uint32_t start_time = chbsp_timestamp_ms();
#endif

RESET_AND_LOAD:
	do {
		set_all_devices_idle(grp_ptr);

		ch_err = chdrv_group_detect_and_program(grp_ptr);
		if (ch_err)
			prog_tries++;

	} while (ch_err && (prog_tries < CH_PROG_XFER_RETRY));

	if (!ch_err) {
		ch_err = (grp_ptr->sensor_count == 0);

#if IS_CH_LOG_USED
		print_connected_sensors(ch_err, grp_ptr, start_time);
#endif
	}

	if (!ch_err) {
		ch_err = chdrv_group_wait_for_lock(grp_ptr);

#if IS_CH_LOG_USED
		print_freq_lock_status(ch_err, start_time);
#endif
		if (ch_err) {
			prog_tries++;
			if (prog_tries < (CH_PROG_XFER_RETRY + 1)) {
				goto RESET_AND_LOAD;
			}
		} else {
			grp_ptr->io_bus_speed_hz = I2C_BUS_SPEED_HZ;
		}
	}

	if (!ch_err) {
		chbsp_delay_ms(1);

		calibrate_rtc(grp_ptr, 0);

#if IS_CH_LOG_USED
		if (grp_ptr->rtc_cal_type == CH_RTC_CAL_STD) {
			print_rtc_cal_result(grp_ptr, start_time);
		}
#endif

		/* Normal start or manual RTC clock cal - run BIST and measure PMUT freq */
		chdrv_group_measure_pmut(grp_ptr);
	}

	count_connected_sensors_per_bus(grp_ptr);

	return ch_err;
}
#endif

#ifdef INCLUDE_SHASTA_SUPPORT
static inline int init_int_pins_config(ch_group_t *grp_ptr) {
	int ch_err = 0;
	/* from chirp_board_config.h */
	grp_ptr->sensor_int_pin  = CHIRP_SENSOR_INT_PIN;
	grp_ptr->sensor_trig_pin = CHIRP_SENSOR_TRIG_PIN;

	if (CHIRP_SENSOR_INT_PIN != 2)
		return 0;

	/* If sensors use INT2 for interrupt, change it now (trig set later in ch_common_set_mode()) */
	for (int dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
		ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
		if (!dev_ptr->sensor_connected)
			continue;

		dev_ptr->meas_queue.intconfig  = INTCONFIG_DR_INT2;
		ch_err                        |= chdrv_meas_queue_write(dev_ptr, NULL);
		if (!ch_err)
			chdrv_event_trigger(dev_ptr, EVENT_CONFIG_TRIGGER);
	}
	return ch_err;
}

static inline void set_clock_config(const ch_group_t *grp_ptr) {
	for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
		ch_dev_t *dev_ptr                        = grp_ptr->device[dev_num];
		volatile clock_control_t *clock_ctrl_ptr = &((dev_ptr->sens_cfg_addr)->common.clock);
		uint16_t reg_addr                        = (uint16_t)(uintptr_t) & (clock_ctrl_ptr->fcount_cycles);

		if (!dev_ptr->sensor_connected) {
			continue;
		}

		/* Set clock config */
		chdrv_write_word(dev_ptr, reg_addr, dev_ptr->fcount_cycles);  // set fcount cycles
		chdrv_event_trigger(dev_ptr, EVENT_CONFIG_CLOCKS);            // force sensor update

		/* Store only bandwidth if restart, will use existing clock cal */
		if (dev_ptr->current_fw->calib_funcs->store_bandwidth != NULL) {
			dev_ptr->current_fw->calib_funcs->store_bandwidth(dev_ptr);
		}
	}
}

static inline uint8_t shasta_group_start(ch_group_t *grp_ptr) {
	uint8_t ch_err;
	uint8_t prog_tries = 0;
#if IS_CH_LOG_USED
	const uint32_t start_time = chbsp_timestamp_ms();
#endif

	do {
		ch_err = chdrv_group_detect_and_program(grp_ptr);
		if (ch_err)
			prog_tries++;

	} while (ch_err && (prog_tries < CH_PROG_XFER_RETRY));

	if (!ch_err) {
		ch_err = (grp_ptr->sensor_count == 0);

#if IS_CH_LOG_USED
		print_connected_sensors(ch_err, grp_ptr, start_time);
#endif
	}

	if (!ch_err) {
		chbsp_delay_ms(1);

		for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
			ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
			if (dev_ptr->sensor_connected)
				clock_init(dev_ptr, 0);
		}

		calibrate_rtc(grp_ptr, 0);

#if IS_CH_LOG_USED
		if (grp_ptr->rtc_cal_type == CH_RTC_CAL_STD) {
			print_rtc_cal_result(grp_ptr, start_time);
		}
#endif

		CH_LOG_DEBUG("Exiting debug mode");
		for (uint8_t dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
			ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
			if (dev_ptr->sensor_connected) {
				exit_debug(dev_ptr); /* exit debug mode */
			}
		}

		/* Normal start or manual RTC clock cal - run BIST and measure PMUT freq */
		chdrv_group_measure_pmut(grp_ptr);
	}

	/* Set interrupt and trigger pins from BSP definitions */
	if (!ch_err)
		ch_err = init_int_pins_config(grp_ptr);

	return ch_err;
}

#endif /* #ifdef INCLUDE_SHASTA_SUPPORT */

uint8_t chdrv_group_start(ch_group_t *grp_ptr) {
	int ch_err;

	if (!grp_ptr)
		return RET_ERR;

	ch_err = chdrv_group_prepare(grp_ptr);
	if (ch_err)
		return ch_err;

#ifdef INCLUDE_WHITNEY_SUPPORT
	return whitney_group_start(grp_ptr);
#elif defined(INCLUDE_SHASTA_SUPPORT)
	return shasta_group_start(grp_ptr);
#endif
}

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
int chdrv_restart(ch_dev_t *dev_ptr) {
	int ch_err = RET_ERR;

#ifdef INCLUDE_SHASTA_SUPPORT
	ch_err = chdrv_soft_reset(dev_ptr);  // reset, enter debug mode

	if (!ch_err) {
		ch_err = chdrv_detect_and_program(dev_ptr);
	}

	clock_init(dev_ptr, 1);               // init clock, restart w/ saved values
	chdrv_int_interrupt_enable(dev_ptr);  // *** enable interrupt ***

	exit_debug(dev_ptr);  // exit debug mode
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	(void)dev_ptr;  // not supported for CH101/CH201
#endif

	return ch_err;
}

/*!
 * \brief Perform a soft reset on a sensor
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function performs a soft reset on an individual sensor by writing to a special control register.
 */
int chdrv_soft_reset(ch_dev_t *dev_ptr) {
	int ch_err = RET_ERR;

	if (dev_ptr->sensor_connected) {

#ifdef INCLUDE_SHASTA_SUPPORT
		ch_err = reset_and_halt(dev_ptr);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
		chbsp_program_enable(dev_ptr);

		ch_err = reset_and_halt(dev_ptr);

		if (!ch_err) {
			ch_err = init_ram(dev_ptr) || reset_and_halt(dev_ptr);
		}
		if (!ch_err) {
			ch_err = chdrv_prog_mem_write(dev_ptr, 0x01C5, &dev_ptr->i2c_address, 1) ||  // TODO need define
			         chdrv_prog_write(dev_ptr, CH_PROG_REG_CPU, 2);  // Exit programming mode and run the chip
		}

		if (!ch_err) {
			chbsp_program_disable(dev_ptr);
		}
#endif  // INCLUDE_SHASTA_SUPPORT
	}
	return ch_err;
}

/*!
 * \brief Perform a hard reset on a group of sensors.
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function performs a hardware reset on each device in a group of sensors.  For
 * CH101 and CH201 sensors, each device's RESET_N pin is asserted and then a soft reset
 * is performed.
 *
 * ICU sensors do not have a hardware reset pin, so only a soft reset is performed.
 */
int chdrv_group_hard_reset(ch_group_t *grp_ptr) {

#ifdef INCLUDE_WHITNEY_SUPPORT
	chbsp_reset_assert();
	chbsp_delay_us(1);
	chbsp_reset_release();
#endif

	for (uint8_t i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr = grp_ptr->device[i];

		int ch_err = chdrv_soft_reset(dev_ptr);

		if (ch_err) {
			dev_ptr->sensor_connected = 0;  // only marked as connected if no errors
		}
	}
	return 0;
}

/*!
 * \brief Perform a soft reset on a group of sensor devices
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 *
 * \return 0 if successful, non-zero otherwise
 *
 * This function performs a soft reset on each device in a group of sensors by writing to a special control register.
 */
int chdrv_group_soft_reset(ch_group_t *grp_ptr) {
	int ch_err = 0;

	for (uint8_t i = 0; i < grp_ptr->num_ports; i++) {
		ch_dev_t *dev_ptr  = grp_ptr->device[i];
		ch_err            |= chdrv_soft_reset(dev_ptr);
	}

	return ch_err;
}

/*!
 * \brief Set the pre-trigger delay for rx-only sensors
 *
 * \param grp_ptr 		pointer to the ch_group_t config structure for a group of sensors
 * \param delay_us		time to delay between triggering rx-only and tx/rx nodes, in microseconds
 *
 * This function sets a delay interval that will be inserted between triggering rx-only sensor
 * and tx/rx sensors.  This delay allows the rx-only sensor(s) to settle from any startup disruption
 * (e.g. PMUT "ringdown") before the ultrasound pulse is generated by the tx node.
 *
 */
void chdrv_pretrigger_delay_set(ch_group_t *grp_ptr, uint16_t delay_us) {

	grp_ptr->pretrig_delay_us = delay_us;
}

/*!
 * \brief Check if sensor reset has occurred.
 *
 * \param dev_ptr       pointer to the ch_dev_t descriptor structure
 * \param reset_state_ptr   pointer to variable that will be updated with 0 = No Reset, 1 = Reset has occurred.
 *
 *  \return 0 if successful, non-zero otherwise
 *
 * This function checks if an PUC (Power Up Clear)  main reset event has occurred by checking the PUC_PND
 * status bit in CPU_STAT debug register.
 * The function updates the "\a reset_state_ptr is set to 1 if the sensor was reset, otherwise it is set to zero.
 * Note this will continue to return a reset state as set until the PUC_PND bit is cleared
 * by writing a 1 to it, which is done in reset_and_run function.
 *
 */
uint8_t chdrv_check_reset_state(ch_dev_t *dev_ptr, uint8_t *reset_state_ptr) {
	uint8_t ch_err = 0;
#ifdef INCLUDE_SHASTA_SUPPORT
	uint8_t sys_ctrl_val  = 0;
	uint16_t cpu_stat_val = 0;
	int in_debug_mode     = 0;  // 0 = Not in debug mode, 1 = in debug mode.

	ch_err = chdrv_sys_ctrl_read(dev_ptr, &sys_ctrl_val);

	// Check if the CPU is in debug mode.
	if (sys_ctrl_val & SYS_CTRL_DEBUG) {
		in_debug_mode = 1;
	} else {  // Enable debug mode.
		sys_ctrl_val |= SYS_CTRL_DEBUG;
		ch_err       |= chdrv_sys_ctrl_write(dev_ptr, sys_ctrl_val);
	}

	ch_err |= chdrv_dbg_reg_read(dev_ptr, SHASTA_DBG_REG_CPU_STAT, &cpu_stat_val);
	if (cpu_stat_val & CPU_STAT_PUC_PND) {
		*reset_state_ptr = 1;
	} else {
		*reset_state_ptr = 0;
	}

	// If not in debug mode, restore normal mode.
	if (!in_debug_mode) {
		sys_ctrl_val &= ~(SYS_CTRL_DEBUG);
		ch_err       |= chdrv_sys_ctrl_write(dev_ptr, sys_ctrl_val);
	}
#else
	ch_err = 1;  // Not supported in whitney, returning non-zero value.
	(void)dev_ptr;
	(void)reset_state_ptr;
#endif
	return ch_err;
}
