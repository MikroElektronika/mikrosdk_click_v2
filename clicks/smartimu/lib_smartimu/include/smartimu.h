/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file smartimu.h
 * @brief This file contains API for Smart IMU Click Driver.
 */

#ifndef SMARTIMU_H
#define SMARTIMU_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup smartimu Smart IMU Click Driver
 * @brief API for configuring and manipulating Smart IMU Click driver.
 * @{
 */

/**
 * @defgroup smartimu_reg Smart IMU Registers List
 * @brief List of registers of Smart IMU Click driver.
 */

/**
 * @addtogroup smartimu_reg
 * @{
 */

/**
 * @brief Smart IMU DMA channel register list.
 * @details Specified DMA channel register list of Smart IMU Click driver.
 */
#define SMARTIMU_REG_CHAN_CMD                   0x00
#define SMARTIMU_REG_CHAN_FIFO_W                0x01
#define SMARTIMU_REG_CHAN_FIFO_NW               0x02
#define SMARTIMU_REG_CHAN_STATUS                0x03

/**
 * @brief Smart IMU control and status register list.
 * @details Specified control and status register list of Smart IMU Click driver.
 */
#define SMARTIMU_REG_CHIP_CTRL                  0x05
#define SMARTIMU_REG_HOST_IF_CTRL               0x06
#define SMARTIMU_REG_HOST_INT_CTRL              0x07
#define SMARTIMU_REG_RESET_REQ                  0x14
#define SMARTIMU_REG_HOST_CTRL                  0x16
#define SMARTIMU_REG_HOST_STATUS                0x17
#define SMARTIMU_REG_FUSER2_ID                  0x1C
#define SMARTIMU_REG_BOOT_STATUS                0x25
#define SMARTIMU_REG_CHIP_ID                    0x2B
#define SMARTIMU_REG_INT_STATUS                 0x2D
#define SMARTIMU_REG_ERROR_VAL                  0x2E

/*! @} */ // smartimu_reg

/**
 * @defgroup smartimu_set Smart IMU Registers Settings
 * @brief Settings for registers of Smart IMU Click driver.
 */

/**
 * @addtogroup smartimu_set
 * @{
 */

/**
 * @brief Smart IMU boot status register(0x25) setting.
 * @details Specified setting for boot status register of Smart IMU Click driver.
 */
#define SMARTIMU_BOOT_STAT_HOST_IF_RDY          0x10  
#define SMARTIMU_BOOT_STAT_FW_VFY_DONE          0x20  
#define SMARTIMU_BOOT_STAT_FW_VFY_ERR           0x40  
#define SMARTIMU_BOOT_STAT_FW_IDLE              0x80  

/**
 * @brief Smart IMU chip control register(0x05) setting.
 * @details Specified setting for chip control register of Smart IMU Click driver.
 */
#define SMARTIMU_CHIP_CTRL_CPU_TURBO_DIS        0x01
#define SMARTIMU_CHIP_CTRL_CPU_CLEAR_ERR        0x02

/**
 * @brief Smart IMU interrupt control register(0x07) setting.
 * @details Specified setting for interrupt control register of Smart IMU Click driver.
 */
#define SMARTIMU_HOST_INT_CTRL_W_FIFO           0x01
#define SMARTIMU_HOST_INT_CTRL_NW_FIFO          0x02 
#define SMARTIMU_HOST_INT_CTRL_STATUS           0x04
#define SMARTIMU_HOST_INT_CTRL_DEBUG            0x08  
#define SMARTIMU_HOST_INT_CTRL_FAULT            0x10
#define SMARTIMU_HOST_INT_CTRL_ACT_LOW          0x20  
#define SMARTIMU_HOST_INT_CTRL_EDGE             0x40  
#define SMARTIMU_HOST_INT_CTRL_OPEN_DRAIN       0x80  
#define SMARTIMU_HOST_INT_HIGH_LEVEL_PP         0x00  

 /**
 * @brief Smart IMU interrupt status register(0x2D) setting.
 * @details Specified setting for interrupt status register of Smart IMU Click driver.
 */
#define SMARTIMU_INT_STAT_HOST_INT              0x01
#define SMARTIMU_INT_STAT_W_NO_DATA             0x00
#define SMARTIMU_INT_STAT_W_IMMEDIATE           0x02
#define SMARTIMU_INT_STAT_W_LATENCY             0x04
#define SMARTIMU_INT_STAT_W_NO_WATER            0x06
#define SMARTIMU_INT_STAT_NW_NO_DATA            0x00
#define SMARTIMU_INT_STAT_NW_IMMEDIATE          0x08
#define SMARTIMU_INT_STAT_NW_LATENCY            0x10
#define SMARTIMU_INT_STAT_NW_NO_WATER           0x18
#define SMARTIMU_INT_STAT_STATUS_CH             0x20
#define SMARTIMU_INT_STAT_DEBUG_CH              0x40
#define SMARTIMU_INT_STAT_RESET_FAULT           0x80

 /**
 * @brief Smart IMU reset request register(0x14) setting.
 * @details Specified setting for reset request register of Smart IMU Click driver.
 */
#define SMARTIMU_RESET_REQUEST                  0x01

 /**
 * @brief Smart IMU host command IDs setting.
 * @details Specified setting for host command IDs of Smart IMU Click driver.
 */
#define SMARTIMU_CMD_DOWNLOAD_MORTEM            0x0001u
#define SMARTIMU_CMD_UPLOAD_FW                  0x0002u
#define SMARTIMU_CMD_BOOT_RAM                   0x0003u
#define SMARTIMU_CMD_INJECTION_MODE             0x0007u
#define SMARTIMU_CMD_INJECT_DATA                0x0008u
#define SMARTIMU_CMD_FIFO_FLUSH                 0x0009u
#define SMARTIMU_CMD_SOFT_PASS                  0x000Au
#define SMARTIMU_CMD_SELF_TEST                  0x000Bu
#define SMARTIMU_CMD_OFFSET_COMP                0x000Cu
#define SMARTIMU_CMD_CONFIGURE_SENSOR           0x000Du
#define SMARTIMU_CMD_DYNAMIC_RANGE              0x000Eu
#define SMARTIMU_CMD_SENSITIVITY                0x000Fu
#define SMARTIMU_CMD_DEBUG_TEST                 0x0010u
#define SMARTIMU_CMD_DUT_CONTINUE               0x0011u
#define SMARTIMU_CMD_DUT_START_TEST             0x0012u
#define SMARTIMU_CMD_CTRL_FIFO_FORMAT           0x0015u
#define SMARTIMU_CMD_HOST_INTERFACE_SPEED       0x0017u

 /**
 * @brief Smart IMU command header size setting.
 * @details Specified setting for command header size of Smart IMU Click driver.
 */
#define SMARTIMU_CMD_HEADER_SIZE                0x04u

 /**
 * @brief Smart IMU FIFO flush command payload setting.
 * @details Specified setting for FIFO flush command payload of Smart IMU Click driver.
 */
#define SMARTIMU_FIFO_FLUSH_ALL                 0xFFu
#define SMARTIMU_FIFO_FLUSH_NWU                 0xFCu
#define SMARTIMU_FIFO_FLUSH_WU                  0xFDu

 /**
 * @brief Smart IMU virtual sensor IDs setting.
 * @details Specified setting for virtual sensor IDs of Smart IMU Click driver.
 */
#define SMARTIMU_VSENSOR_ACCEL_CORR_NWU         0x04u
#define SMARTIMU_VSENSOR_ACCEL_CORR_WU          0x06u
#define SMARTIMU_VSENSOR_GYRO_CORR_NWU          0x0Du
#define SMARTIMU_VSENSOR_GYRO_CORR_WU           0x0Fu

 /**
 * @brief Smart IMU FIFO event IDs setting.
 * @details Specified FIFO event IDs of Smart IMU Click driver.
 * */
#define SMARTIMU_FIFO_PADDING                   0x00u
#define SMARTIMU_FIFO_FILLER                    0xFFu

 /**
 * @brief Smart IMU timestamp events setting.
 * @details Specified setting for timestamp events of Smart IMU Click driver.
 */
#define SMARTIMU_FIFO_TS_SMALL_NWU              0xF5u
#define SMARTIMU_FIFO_TS_LARGE_NWU              0xF6u
#define SMARTIMU_FIFO_TS_FULL_NWU               0xF7u
#define SMARTIMU_FIFO_TS_SMALL_WU               0xFBu
#define SMARTIMU_FIFO_TS_LARGE_WU               0xFCu
#define SMARTIMU_FIFO_TS_FULL_WU                0xFDu

 /**
 * @brief Smart IMU meta events setting.
 * @details Specified setting for meta events of Smart IMU Click driver.
 */
#define SMARTIMU_FIFO_META_NWU                  0xF8u
#define SMARTIMU_FIFO_META_WU                   0xFEu

/**
 * @brief Smart IMU meta event codes setting.
 * @details Specified setting for meta event codes of Smart IMU Click driver.
 */
#define SMARTIMU_META_FLUSH_COMPLETE            0x01u
#define SMARTIMU_META_SAMPLE_RATE_CHG           0x02u
#define SMARTIMU_META_POWER_MODE_CHG            0x03u
#define SMARTIMU_META_SYSTEM_ERROR              0x04u
#define SMARTIMU_META_FIFO_OVERFLOW             0x0Cu
#define SMARTIMU_META_INITIALIZED               0x10u
#define SMARTIMU_META_SPACER                    0x14u

/**
 * @brief Smart IMU virtual sensor payload size setting.
 * @details Specified setting for virtual sensor payload size of Smart IMU Click driver.
 */
#define SMARTIMU_CFG_SENSOR_PAYLOAD_SIZE        0x08u

/**
 * @brief Smart IMU FIFO timestamp payload size setting.
 * @details Specified setting for FIFO timestamp payload size of Smart IMU Click driver.
 */
#define SMARTIMU_FIFO_TS_SMALL_PAYLOAD_SIZE     0x01u
#define SMARTIMU_FIFO_TS_LARGE_PAYLOAD_SIZE     0x02u
#define SMARTIMU_FIFO_TS_FULL_PAYLOAD_SIZE      0x05u

/**
 * @brief Smart IMU FIFO meta event payload size setting.
 * @details Specified setting for FIFO meta event payload size of Smart IMU Click driver.
 */
#define SMARTIMU_FIFO_META_PAYLOAD_SIZE         0x03u

/**
 * @brief Smart IMU FIFO sensor event payload size setting.
 * @details Specified setting for FIFO sensor event payload size of Smart IMU Click driver.
 */
#define SMARTIMU_FIFO_SENSOR_PAYLOAD_SIZE       0x06u

/**
 * @brief Smart IMU firmware word size setting.
 * @details Specified setting for firmware word size of Smart IMU Click driver.
 */
#define SMARTIMU_FW_WORD_SIZE                   0x04u

/**
 * @brief Smart IMU device identifier setting.
 * @details Specified setting for device identifier of Smart IMU Click driver.
 */
#define SMARTIMU_CHIP_ID_VALUE                  0x7Cu
#define SMARTIMU_FUSER2_ID_VALUE                0x89u

/**
 * @brief Smart IMU sensor scale factors setting.
 * @details Specified setting for sensor scale factors of Smart IMU Click driver.
 */
#define SMARTIMU_ACCEL_SCALE_8G                 4096.0f
#define SMARTIMU_GYRO_SCALE_2000DPS             16.384f

/**
 * @brief Smart IMU sensor odr setting.
 * @details Specified setting for odr of Smart IMU Click driver.
 */
#define SMARTIMU_DEFAULT_ODR_HZ                 10.0f

/**
 * @brief Smart IMU Firmware upload chunk size setting.
 * @details Specified setting for Firmware upload chunk size of Smart IMU Click driver.
 */
#define SMARTIMU_FW_FIRST_CHUNK                 248u
#define SMARTIMU_FW_CHUNK_SIZE                  252u

/**
 * @brief Smart IMU Maximum FIFO bytes setting.
 * @details Specified setting for Maximum FIFO bytes of Smart IMU Click driver.
 */
#define SMARTIMU_FIFO_READ_MAX                  250u

/**
 * @brief Smart IMU device address setting.
 * @details Specified setting for device slave address selection of
 * Smart IMU Click driver.
 */
#define SMARTIMU_DEVICE_ADDRESS_0               0x28u
#define SMARTIMU_DEVICE_ADDRESS_1               0x29u
#define SMARTIMU_DEVICE_ADDRESS                 SMARTIMU_DEVICE_ADDRESS_0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b smartimu_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SMARTIMU_SET_DATA_SAMPLE_EDGE     SET_SPI_DATA_SAMPLE_EDGE
#define SMARTIMU_SET_DATA_SAMPLE_MIDDLE   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // smartimu_set

/**
 * @defgroup smartimu_map Smart IMU MikroBUS Map
 * @brief MikroBUS pin mapping of Smart IMU Click driver.
 */

/**
 * @addtogroup smartimu_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart IMU Click to the selected MikroBUS.
 */
#define SMARTIMU_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartimu_map
/*! @} */ // smartimu

/**
 * @brief Smart IMU Click driver selector.
 * @details Selects target driver interface of Smart IMU Click driver.
 */
typedef enum
{
    SMARTIMU_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    SMARTIMU_DRV_SEL_I2C       /**< I2C driver descriptor. */

} smartimu_drv_t;

/**
 * @brief Smart IMU Click driver interface.
 * @details Definition of driver interface of Smart IMU Click driver.
 */
struct smartimu_s;
typedef err_t ( *smartimu_master_io_t )( struct smartimu_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Smart IMU Click context object.
 * @details Context object definition of Smart IMU Click driver.
 */
typedef struct smartimu_s
{
    digital_in_t int_pin;                  /**< Interrupt pin. */

    i2c_master_t i2c;                      /**< I2C driver object. */
    spi_master_t spi;                      /**< SPI driver object. */

    uint8_t      slave_address;            /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;              /**< Chip select pin descriptor (used for SPI driver). */
    smartimu_drv_t drv_sel;                /**< Master driver interface selector. */

    smartimu_master_io_t write_f;          /**< Master write function. */
    smartimu_master_io_t read_f;           /**< Master read function. */

    float accel_scale;                     /**< Accelerometer scale factor (LSB/g).*/
    float gyro_scale;                      /**< Gyroscope scale factor (LSB/dps). */

} smartimu_t;

/**
 * @brief Smart IMU Click configuration object.
 * @details Configuration object definition of Smart IMU Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    smartimu_drv_t drv_sel;     /**< Master driver interface selector. */

} smartimu_cfg_t;

/**
 * @brief Smart IMU Click axes data structure.
 * @details Axes data object definition of Smart IMU Click driver.
 */
typedef struct
{
    float x;                   /**< X-axis (g or dps). */
    float y;                   /**< Y-axis (g or dps). */
    float z;                   /**< Z-axis (g or dps). */

} smartimu_axes_t;

/**
 * @brief Smart IMU Click data structure.
 * @details Data object definition of Smart IMU Click driver.
 */
typedef struct
{
    smartimu_axes_t accel;     /**< Accelerometer data in g. */
    smartimu_axes_t gyro;      /**< Gyroscope data in dps. */

} smartimu_data_t;

/**
 * @brief Smart IMU Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTIMU_OK = 0,
    SMARTIMU_ERROR = -1

} smartimu_return_value_t;

/*!
 * @addtogroup smartimu Smart IMU Click Driver
 * @brief API for configuring and manipulating Smart IMU Click driver.
 * @{
 */

/**
 * @brief Smart IMU configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartimu_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartimu_cfg_setup ( smartimu_cfg_t *cfg );

/**
 * @brief Smart IMU driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #smartimu_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #smartimu_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void smartimu_drv_interface_sel ( smartimu_cfg_t *cfg, smartimu_drv_t drv_sel );

/**
 * @brief Smart IMU initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartimu_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_init ( smartimu_t *ctx, smartimu_cfg_t *cfg );

/**
 * @brief Smart IMU default configuration function.
 * @details This function executes a default configuration of Smart IMU
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartimu_default_cfg ( smartimu_t *ctx );

/**
 * @brief Smart IMU data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_generic_write ( smartimu_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart IMU data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_generic_read ( smartimu_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart IMU check communication function.
 * @details This function verifies that the host can communicate with the
 * BHI385 by reading the Chip ID register (0x2B).
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_check_communication ( smartimu_t *ctx );

/**
 * @brief Smart IMU reset device function.
 * @details This function performs a software reset of the BHI385 by writing
 * 0x01 to the Reset Request register (0x14).
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_reset_device ( smartimu_t *ctx );

/**
 * @brief Smart IMU send command function.
 * @details This function builds and sends a command packet to the BHI385
 * via DMA channel 0 (register 0x00).
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] cmd_id : Command identifier.
 * @param[in] payload : Pointer to the command payload buffer.
 * @param[in] payload_len : Number of valid bytes in the payload buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_send_command ( smartimu_t *ctx, uint16_t cmd_id, uint8_t *payload, uint16_t payload_len );

/**
 * @brief Smart IMU upload firmware function.
 * @details This function uploads a firmware binary image to the BHI385
 * program RAM using the bootloader upload protocol.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] fw_data : Pointer to the firmware byte array.
 * @param[in] fw_size : Total firmware size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_upload_firmware ( smartimu_t *ctx, const uint8_t *fw_data, uint32_t fw_size ); 

/**
 * @brief Smart IMU configure sensor function.
 * @details This function configures a virtual sensor on the BHI385
 * by sending a configure sensor command (0x000D) with an 8-byte payload.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] sensor_id : Virtual sensor identifier.
 * @param[in] odr_hz : Desired output data rate in Hz.
 * @param[in] latency_ms : Maximum latency in milliseconds. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_configure_vir_sensor ( smartimu_t *ctx, uint8_t sensor_id, float odr_hz, uint32_t latency_ms );

/**
 * @brief Smart IMU get int_pin function.
 * @details This function reads the logic state of the int_pin.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t smartimu_get_int_pin ( smartimu_t *ctx );

/**
 * @brief Smart IMU drain FIFO channel function.
 * @details This function reads and discards multiple bytes from the
 * specified FIFO channel register.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] fifo_reg : FIFO channel register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_drain_fifo_channel ( smartimu_t *ctx, uint8_t fifo_reg );

/**
 * @brief Smart IMU read FIFO channel function.
 * @details This function reads multiple bytes from the specified
 * FIFO channel and parses the event stream according to the
 * BHI385 FIFO data format.
 * @param[in] ctx : Click context object.
 * See #smartimu_t object definition for detailed explanation.
 * @param[in] fifo_reg : FIFO channel register address.
 * @param[out] data_out : Pointer to the output data structure.
 * See #smartimu_data_t object definition for detailed explanation.
 * @param[out] sample_found : Accel or gyro sample detection flag
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartimu_read_fifo_channel ( smartimu_t *ctx, uint8_t fifo_reg, smartimu_data_t *data_out, uint8_t *sample_found );

#ifdef __cplusplus
}
#endif
#endif // SMARTIMU_H

/*! @} */ // smartimu

// ------------------------------------------------------------------------ END
