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
 * @file speaker2.h
 * @brief This file contains API for Speaker 2 Click Driver.
 */

#ifndef SPEAKER2_H
#define SPEAKER2_H

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
 * @addtogroup speaker2 Speaker 2 Click Driver
 * @brief API for configuring and manipulating Speaker 2 Click driver.
 * @{
 */

/**
 * @defgroup speaker2_cmd Speaker 2 Commands List
 * @brief List of commands of Speaker 2 Click driver.
 */

/**
 * @addtogroup speaker2_cmd
 * @{
 */

/**
 * @brief Speaker 2 commands list.
 * @details Specified commands list of Speaker 2 Click driver.
 */
#define SPEAKER2_CMD_PLAY_VP                0xA6
#define SPEAKER2_CMD_PLAY_VP_RN             0xAE
#define SPEAKER2_CMD_PLAY_VP_LP             0xA4
#define SPEAKER2_CMD_PLAY_VP_RN_LP          0xB2
#define SPEAKER2_CMD_EXE_VM                 0xB0
#define SPEAKER2_CMD_EXE_VM_RN              0xBC
#define SPEAKER2_CMD_PLAY_SIL               0xA8
#define SPEAKER2_CMD_STOP                   0x2A
#define SPEAKER2_CMD_STOP_LP                0x2E
#define SPEAKER2_CMD_SPI_PCM_READ           0xAC
#define SPEAKER2_CMD_SPI_SND_DEC            0xC0
#define SPEAKER2_CMD_READ_STATUS            0x40
#define SPEAKER2_CMD_READ_INT               0x46
#define SPEAKER2_CMD_READ_ID                0x48
#define SPEAKER2_CMD_DIG_READ               0xA2
#define SPEAKER2_CMD_DIG_WRITE              0xA0
#define SPEAKER2_CMD_ERASE_MEM              0x24
#define SPEAKER2_CMD_CHIP_ERASE             0x26
#define SPEAKER2_CMD_CHECKSUM               0xF2
#define SPEAKER2_CMD_PWR_UP                 0x10
#define SPEAKER2_CMD_PWR_DN                 0x12
#define SPEAKER2_CMD_SET_CLK_CFG            0xB4
#define SPEAKER2_CMD_RD_CLK_CFG             0xB6
#define SPEAKER2_CMD_WR_CFG_REG             0xB8
#define SPEAKER2_CMD_RD_CFG_REG             0xBA
#define SPEAKER2_CMD_RESET                  0x14

/**
 * @brief Speaker 2 registers list.
 * @details Specified registers list of Speaker 2 Click driver.
 */
#define SPEAKER2_REG_SAMPLE_RATE_OVERWRITE  0x00
#define SPEAKER2_REG_DECOMPRESSION_CONTROL  0x01
#define SPEAKER2_REG_PATH_CONTROL           0x02
#define SPEAKER2_REG_VOLUME_CONTROL         0x03
#define SPEAKER2_REG_CHECKSUM_RESET         0x04
#define SPEAKER2_REG_THERMAL_CONTROL        0x05
#define SPEAKER2_REG_MASK_JUMP_CONTROL      0x08
#define SPEAKER2_REG_PWM_CONTROL            0x09
#define SPEAKER2_REG_CH_CONTROL             0x0C
#define SPEAKER2_REG_CH0_COUNTER_CONTROL    0x0D
#define SPEAKER2_REG_CH1_COUNTER_CONTROL    0x0E
#define SPEAKER2_REG_CH2_COUNTER_CONTROL    0x0F
#define SPEAKER2_REG_CHECKSUM_1_LB          0x10
#define SPEAKER2_REG_CHECKSUM_1_HB          0x11
#define SPEAKER2_REG_CHECKSUM_2_LB          0x12
#define SPEAKER2_REG_CHECKSUM_2_HB          0x13
#define SPEAKER2_REG_GPIO_TRIGGER_CH_SEL_1  0x14
#define SPEAKER2_REG_GPIO_TRIGGER_CH_SEL_2  0x15
#define SPEAKER2_REG_TRIGGER_VOLUME_CONTROL 0x16
#define SPEAKER2_REG_DEBOUNCE_TIME_CONTROL  0x17
#define SPEAKER2_REG_OUTPUT_DATA_CONTROL    0x19
#define SPEAKER2_REG_OUTPUT_ENABLE_CONTROL  0x1A
#define SPEAKER2_REG_PULL_ENABLE_CONTROL    0x1B
#define SPEAKER2_REG_INPUT_DATA_CONTROL     0x1C
#define SPEAKER2_REG_PULL_SELECT_CONTROL    0x1D
#define SPEAKER2_REG_ALT_FUNCTION_CONTROL_1 0x1E
#define SPEAKER2_REG_ALT_FUNCTION_CONTROL_0 0x1F
#define SPEAKER2_REG_R0_L                   0x20
#define SPEAKER2_REG_R0_H                   0x21
#define SPEAKER2_REG_R1_L                   0x22
#define SPEAKER2_REG_R1_H                   0x23
#define SPEAKER2_REG_R2_L                   0x24
#define SPEAKER2_REG_R2_H                   0x25
#define SPEAKER2_REG_R3_L                   0x26
#define SPEAKER2_REG_R3_H                   0x27
#define SPEAKER2_REG_R4_L                   0x28
#define SPEAKER2_REG_R4_H                   0x29
#define SPEAKER2_REG_R5_L                   0x2A
#define SPEAKER2_REG_R5_H                   0x2B
#define SPEAKER2_REG_R6_L                   0x2C
#define SPEAKER2_REG_R6_H                   0x2D
#define SPEAKER2_REG_R7_L                   0x2E
#define SPEAKER2_REG_R7_H                   0x2F

/*! @} */ // speaker2_cmd

/**
 * @defgroup speaker2_set Speaker 2 Registers Settings
 * @brief Settings for registers of Speaker 2 Click driver.
 */

/**
 * @addtogroup speaker2_set
 * @{
 */

/**
 * @brief Speaker 2 device status setting.
 * @details Specified setting for device status of Speaker 2 Click driver.
 */
#define SPEAKER2_STATUS_PD                  0x80
#define SPEAKER2_STATUS_DBUF_RDY            0x40
#define SPEAKER2_STATUS_INT                 0x20
#define SPEAKER2_STATUS_CH2_BSY             0x08
#define SPEAKER2_STATUS_CH1_BSY             0x04
#define SPEAKER2_STATUS_CH0_BSY             0x02
#define SPEAKER2_STATUS_DIG_BSY             0x01
#define SPEAKER2_STATUS_CLEAR               0x00

/**
 * @brief Speaker 2 interrupt status setting.
 * @details Specified setting for interrupt status of Speaker 2 Click driver.
 */
#define SPEAKER2_INT_STATUS_TALARM_INT      0x80
#define SPEAKER2_INT_STATUS_MPT_ERR         0x40
#define SPEAKER2_INT_STATUS_WR_FIN          0x20
#define SPEAKER2_INT_STATUS_CMD_ERR         0x10
#define SPEAKER2_INT_STATUS_OVF_ERR         0x08
#define SPEAKER2_INT_STATUS_CH2_FIN         0x04
#define SPEAKER2_INT_STATUS_CH1_FIN         0x02
#define SPEAKER2_INT_STATUS_CH0_FIN         0x01

/**
 * @brief Speaker 2 device ID setting.
 * @details Specified setting for device ID of Speaker 2 Click driver.
 */
#define SPEAKER2_DEVICE_ID_PART             0x05
#define SPEAKER2_DEVICE_ID_MAN              0xEF
#define SPEAKER2_DEVICE_ID_MEM_TYPE         0x20
#define SPEAKER2_DEVICE_ID_DEV              0x60

/**
 * @brief Speaker 2 GPIO alternate function setting.
 * @details Specified setting for GPIO alternate function of Speaker 2 Click driver.
 */
#define SPEAKER2_GPIO_AF1_IO                0
#define SPEAKER2_GPIO_AF1_AF                0
#define SPEAKER2_GPIO_AF1_FT                1
#define SPEAKER2_GPIO_AF1_RFT               1
#define SPEAKER2_GPIO_AF0_IO                0
#define SPEAKER2_GPIO_AF0_AF                1
#define SPEAKER2_GPIO_AF0_FT                0
#define SPEAKER2_GPIO_AF0_RFT               1
#define SPEAKER2_GPIO_0_POS                 0
#define SPEAKER2_GPIO_1_POS                 1
#define SPEAKER2_GPIO_2_POS                 2
#define SPEAKER2_GPIO_3_POS                 3
#define SPEAKER2_GPIO_4_POS                 4
#define SPEAKER2_GPIO_5_POS                 5

/**
 * @brief Speaker 2 Voice Macros and Voice Prompts setting.
 * @details Specified Voice Macros and Voice Prompts from binary of Speaker 2 Click driver.
 */
#define SPEAKER2_VM0_POI			        0
#define SPEAKER2_VM1_PU				        1
#define SPEAKER2_VM2_WAKEUP			        2
#define SPEAKER2_VM3_ONE			        3
#define SPEAKER2_VM4_TWO			        4
#define SPEAKER2_VM5_THREE			        5
#define SPEAKER2_VM6_FOUR			        6
#define SPEAKER2_VM7_FIVE			        7
#define SPEAKER2_VM8_SIX			        8
#define SPEAKER2_VP9_ONE			        9
#define SPEAKER2_VP10_TWO			        10
#define SPEAKER2_VP11_THREE			        11
#define SPEAKER2_VP12_FOUR			        12
#define SPEAKER2_VP13_FIVE			        13
#define SPEAKER2_VP14_SIX			        14
#define SPEAKER2_VP15_FAST_BEEP		        15

/**
 * @brief Speaker 2 flash size setting.
 * @details Specified setting for flash size of Speaker 2 Click driver.
 */
#define SPEAKER2_FLASH_START                0x000000ul
#define SPEAKER2_FLASH_END                  0x03FFFFul

/**
 * @brief Speaker 2 cmd payload size setting.
 * @details Specified setting for cmd payload size of Speaker 2 Click driver.
 */
#define SPEAKER2_PAYLOAD_SIZE               256

/**
 * @brief Speaker 2 timeout setting.
 * @details Specified setting for timeout of Speaker 2 Click driver.
 */
#define SPEAKER2_TIMEOUT_10S                10000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b speaker2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SPEAKER2_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define SPEAKER2_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // speaker2_set

/**
 * @defgroup speaker2_map Speaker 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Speaker 2 Click driver.
 */

/**
 * @addtogroup speaker2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Speaker 2 Click to the selected MikroBUS.
 */
#define SPEAKER2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.io5  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // speaker2_map
/*! @} */ // speaker2

/**
 * @brief Speaker 2 Click device ID object.
 * @details Device ID object definition of Speaker 2 Click driver.
 */
typedef struct
{
    uint8_t part_id;            /**< ISD2360 Family ID. */
    uint8_t man_id;             /**< JEDEC manufacturer ID. */
    uint8_t mem_type;           /**< JEDEC memory type. */
    uint8_t dev_id;             /**< JEDEC memory size byte. */

} speaker2_device_id_t;

/**
 * @brief Speaker 2 Click context object.
 * @details Context object definition of Speaker 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t io5;          /**< General purpose I/O 5 pin. */

    // Input pins
    digital_in_t rdy;           /**< Active high SPI ready to accept commands pin. */
    digital_in_t int_pin;       /**< Active low interrupt request pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t cmd_payload[ SPEAKER2_PAYLOAD_SIZE ];   /**< Command/response payload data. */
    uint8_t status;             /**< Device status updated during an SPI command transaction. */

    speaker2_device_id_t device_id; /**< Device ID object. */

} speaker2_t;

/**
 * @brief Speaker 2 Click configuration object.
 * @details Configuration object definition of Speaker 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rdy;             /**< Active high SPI ready to accept commands pin. */
    pin_name_t io5;             /**< General purpose I/O 5 pin. */
    pin_name_t int_pin;         /**< Active low interrupt request pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} speaker2_cfg_t;

/**
 * @brief Speaker 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPEAKER2_OK = 0,
    SPEAKER2_ERROR = -1

} speaker2_return_value_t;

/*!
 * @addtogroup speaker2 Speaker 2 Click Driver
 * @brief API for configuring and manipulating Speaker 2 Click driver.
 * @{
 */

/**
 * @brief Speaker 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #speaker2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void speaker2_cfg_setup ( speaker2_cfg_t *cfg );

/**
 * @brief Speaker 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #speaker2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speaker2_init ( speaker2_t *ctx, speaker2_cfg_t *cfg );

/**
 * @brief Speaker 2 default configuration function.
 * @details This function executes a default configuration of Speaker 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t speaker2_default_cfg ( speaker2_t *ctx );

/**
 * @brief Speaker 2 send command function.
 * @details This function writes a desired number of data bytes to the selected command
 * and reads response by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in,out] payload : Command payload to be written. Outputs command response.
 * @param[in] payload_len : Command payload/response length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speaker2_send_command ( speaker2_t *ctx, uint8_t cmd, uint8_t *payload, uint16_t payload_len );

/**
 * @brief Speaker 2 set IO5 pin function.
 * @details This function sets the IO5 pin logic state.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void speaker2_set_io5_pin ( speaker2_t *ctx, uint8_t state );

/**
 * @brief Speaker 2 get RDY pin function.
 * @details This function returns the RDY pin logic state.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t speaker2_get_rdy_pin ( speaker2_t *ctx );

/**
 * @brief Speaker 2 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t speaker2_get_int_pin ( speaker2_t *ctx );

/**
 * @brief Speaker 2 wait ready function.
 * @details This function waits for the RDY pin to be set, indicating that the device is ready.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Timeout error.
 */
err_t speaker2_wait_ready ( speaker2_t *ctx );

/**
 * @brief Speaker 2 wait status function.
 * @details This function waits until the device status matches the given mask and state.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] mask : Status mask.
 * @param[in] state : Desired status state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Timeout error.
 */
err_t speaker2_wait_status ( speaker2_t *ctx, uint8_t mask, uint8_t state );

/**
 * @brief Speaker 2 wait idle function.
 * @details This function waits for the device to enter an idle state.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Timeout error.
 */
err_t speaker2_wait_idle ( speaker2_t *ctx );

/**
 * @brief Speaker 2 check communication function.
 * @details This function verifies communication with the device by checking the device ID.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Communication error.
 */
err_t speaker2_check_communication ( speaker2_t *ctx );

/**
 * @brief Speaker 2 read status function.
 * @details This function reads the device status and optionally stores the interrupt status.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[out] int_status : Pointer to the variable for storing interrupt status (optional).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_read_status ( speaker2_t *ctx, uint8_t *int_status );

/**
 * @brief Speaker 2 clear interrupt function.
 * @details This function clears the interrupt register and optionally stores the interrupt status.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[out] int_status : Pointer to the variable for storing interrupt status (optional).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_clear_interrupt ( speaker2_t *ctx, uint8_t *int_status );

/**
 * @brief Speaker 2 read device ID function.
 * @details This function reads the device ID and stores it in the provided device ID structure.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[out] device_id : Pointer to the structure for storing the device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_read_device_id ( speaker2_t *ctx, speaker2_device_id_t *device_id );

/**
 * @brief Speaker 2 power up function.
 * @details This function powers up the device and configures GPIO functionality.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_power_up ( speaker2_t *ctx );

/**
 * @brief Speaker 2 power down function.
 * @details This function powers down the device and waits for the appropriate status.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_power_down ( speaker2_t *ctx );

/**
 * @brief Speaker 2 reset device function.
 * @details This function resets the device by sending a reset command.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_reset_device ( speaker2_t *ctx );

/**
 * @brief Speaker 2 memory erase function.
 * @details This function erases the 1kB sector of memory containing the specified address.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] address : Memory address to erase.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_memory_erase ( speaker2_t *ctx, uint32_t address );

/**
 * @brief Speaker 2 chip erase function.
 * @details This function erases the entire chip memory.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_chip_erase ( speaker2_t *ctx );

/**
 * @brief Speaker 2 flash write function.
 * @details This function writes data to the flash memory at the specified address.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] address : Flash memory address.
 * @param[in] data_in : Pointer to the data to write.
 * @param[in] data_len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_flash_write ( speaker2_t *ctx, uint32_t address, uint8_t *data_in, uint16_t data_len );

/**
 * @brief Speaker 2 flash read function.
 * @details This function reads data from the flash memory at the specified address.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] address : Flash memory address.
 * @param[out] data_out : Pointer to the buffer for storing the read data.
 * @param[in] data_len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_flash_read ( speaker2_t *ctx, uint32_t address, uint8_t *data_out, uint16_t data_len );

/**
 * @brief Speaker 2 write binary function.
 * @details This function writes binary data to the flash memory at the specified address.
 * It divides the data into smaller chunks if the total data length exceeds the payload limit.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] address : Flash memory address to write to.
 * @param[in] data_in : Pointer to the binary data to write.
 * @param[in] data_len : Total length of the binary data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note The function uses chunked writing with a maximum size of half of @b SPEAKER2_PAYLOAD_SIZE.
 */
err_t speaker2_write_binary ( speaker2_t *ctx, uint32_t address, const uint8_t *data_in, uint16_t data_len );

/**
 * @brief Speaker 2 write configuration register function.
 * @details This function writes a value to a configuration register.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_write_cfg_reg ( speaker2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Speaker 2 read configuration register function.
 * @details This function reads a value from a configuration register.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the buffer for storing the read value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_read_cfg_reg ( speaker2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Speaker 2 set clock configuration function.
 * @details This function sets the clock configuration for the device.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] clk_cfg : Clock configuration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_set_clock_cfg ( speaker2_t *ctx, uint8_t clk_cfg );

/**
 * @brief Speaker 2 read clock configuration function.
 * @details This function reads the current clock configuration from the device.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[out] clk_cfg : Pointer to the buffer for storing the clock configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_read_clock_cfg ( speaker2_t *ctx, uint8_t *clk_cfg );

/**
 * @brief Speaker 2 SPI audio write function.
 * @details This function sends audio data to the device via the SPI interface for decoding.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to the audio data to send.
 * @param[in] data_len : Length of the audio data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note The data length must not exceed @b SPEAKER2_PAYLOAD_SIZE.
 */
err_t speaker2_spi_audio_write ( speaker2_t *ctx, uint8_t *data_in, uint16_t data_len );

/**
 * @brief Speaker 2 PCM audio read function.
 * @details This function reads PCM audio data from the device via the SPI interface.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the buffer for storing the read PCM audio data.
 * @param[in] data_len : Length of the audio data to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note The data length must not exceed half of @b SPEAKER2_PAYLOAD_SIZE.
 */
err_t speaker2_pcm_audio_read ( speaker2_t *ctx, uint16_t *data_out, uint16_t data_len );

/**
 * @brief Speaker 2 play voice function.
 * @details This function plays a voice at the specified index.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] index : Voice index to play.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_play_voice ( speaker2_t *ctx, uint16_t index );

/**
 * @brief Speaker 2 play voice loop function.
 * @details This function plays a voice in a loop for a specified number of iterations.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] index : Voice index to play.
 * @param[in] loop_cnt : Number of iterations to loop.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_play_voice_loop ( speaker2_t *ctx, uint16_t index, uint16_t loop_cnt );

/**
 * @brief Speaker 2 play macro function.
 * @details This function executes a macro command at the specified index.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] index : Macro index to execute.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_play_macro ( speaker2_t *ctx, uint16_t index );

/**
 * @brief Speaker 2 play silence function.
 * @details This function plays a period of silence for a specified duration.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @param[in] len : Duration of silence in 32 milliseconds steps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_play_silence ( speaker2_t *ctx, uint8_t len );

/**
 * @brief Speaker 2 stop play function.
 * @details This function stops any ongoing playback of voice or macro.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_stop_play ( speaker2_t *ctx );

/**
 * @brief Speaker 2 stop loop play function.
 * @details This function stops any ongoing looped playback.
 * @param[in] ctx : Click context object.
 * See #speaker2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t speaker2_stop_loop_play ( speaker2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SPEAKER2_H

/*! @} */ // speaker2

// ------------------------------------------------------------------------ END
