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
 * @file barometer14.h
 * @brief This file contains API for Barometer 14 Click Driver.
 */

#ifndef BAROMETER14_H
#define BAROMETER14_H

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
 * @addtogroup barometer14 Barometer 14 Click Driver
 * @brief API for configuring and manipulating Barometer 14 Click driver.
 * @{
 */

/**
 * @defgroup barometer14_cmd Barometer 14 Commands List
 * @brief List of commands of Barometer 14 Click driver.
 */

/**
 * @addtogroup barometer14_cmd
 * @{
 */

/**
 * @brief Barometer 14 command list.
 * @details Specified command list of Barometer 14 Click driver.
 */
#define BAROMETER14_CMD_MEASURE_PRESSURE            0xA8
#define BAROMETER14_CMD_MEASURE_ACCELERATION        0xA9
#define BAROMETER14_CMD_MEASURE_TEMPERATURE         0xAA
#define BAROMETER14_CMD_READ_ID                     0xC3
#define BAROMETER14_CMD_SELF_TEST                   0xC5
#define BAROMETER14_CMD_TRIGGER_SOFTRESET           0xC7
#define BAROMETER14_CMD_READ_STATUS_REG             0xD8
#define BAROMETER14_CMD_SET_SERIAL_INTERFACE        0xD0
#define BAROMETER14_CMD_ENTER_AUTONOMOUS_STATE      0xC1
#define BAROMETER14_CMD_ENTER_SLEEP                 0xC2
#define BAROMETER14_CMD_READ_AS_HISTORY             0xA0
#define BAROMETER14_CMD_READ_AS_PRESS_BUF           0xA1
#define BAROMETER14_CMD_READ_AS_ACC_BUF             0xA2
#define BAROMETER14_CMD_READ_ACC_REC_STATS          0xD7
#define BAROMETER14_CMD_SAVE_AS_CONFIG              0xD4
#define BAROMETER14_CMD_READ_AS_CONFIG              0xD5
#define BAROMETER14_CMD_WRITE_DATA_LINE             0xB1
#define BAROMETER14_CMD_READ_DATA_LINE              0xB2

/*! @} */ // barometer14_cmd

/**
 * @defgroup barometer14_set Barometer 14 Registers Settings
 * @brief Settings for registers of Barometer 14 Click driver.
 */

/**
 * @addtogroup barometer14_set
 * @{
 */

/**
 * @brief Barometer 14 error response setting.
 * @details Specified setting for error response of Barometer 14 Click driver.
 */
#define BAROMETER14_RESP_EMPTY_BUFFER               0xE0
#define BAROMETER14_RESP_INVALID_CMD                0xE7
#define BAROMETER14_RESP_CRC_FAIL                   0xEC
#define BAROMETER14_RESP_COLLISION                  0xED
#define BAROMETER14_RESP_OVERFLOW                   0xEF

/**
 * @brief Barometer 14 measurement status setting.
 * @details Specified setting for measurement status of Barometer 14 Click driver.
 */
#define BAROMETER14_MEAS_STATUS_OK                  0x00
#define BAROMETER14_MEAS_STATUS_ADC_UNDERFLOW       0x01
#define BAROMETER14_MEAS_STATUS_ADC_OVERFLOW        0x02
#define BAROMETER14_MEAS_STATUS_WIRE_BOND           0x04
#define BAROMETER14_MEAS_STATUS_DIAG_RES            0x08
#define BAROMETER14_MEAS_STATUS_NUM_UNDERFLOW       0x10
#define BAROMETER14_MEAS_STATUS_NUM_OVERFLOW        0x20
#define BAROMETER14_MEAS_STATUS_CAL_CRC             0x40
#define BAROMETER14_MEAS_STATUS_ADC_TIMEOUT         0x80

/**
 * @brief Barometer 14 self test setting.
 * @details Specified setting for self test of Barometer 14 Click driver.
 */
#define BAROMETER14_SELF_TEST_NO_MEM                0x00
#define BAROMETER14_SELF_TEST_WITH_MEM              0x01
#define BAROMETER14_SELF_TEST_STATUS_OK             0x00
#define BAROMETER14_SELF_TEST_MEM_CRC_FAIL          0x01
#define BAROMETER14_SELF_TEST_SIGNAL_PATH_FAIL      0x02
#define BAROMETER14_SELF_TEST_OSC_FAIL              0x04

/**
 * @brief Barometer 14 status register clear setting.
 * @details Specified setting for status register clear of Barometer 14 Click driver.
 */
#define BAROMETER14_STATUS_CLEAR                    0xAC
#define BAROMETER14_STATUS_NO_CLEAR                 0x53

/**
 * @brief Barometer 14 serial interface type setting.
 * @details Specified setting for serial interface type of Barometer 14 Click driver.
 */
#define BAROMETER14_SERIAL_I2C                      0x00
#define BAROMETER14_SERIAL_SPI                      0x01
#define BAROMETER14_SERIAL_I2C_FILTER               0x02

/**
 * @brief Barometer 14 config ID mask setting.
 * @details Specified setting for config ID mask of Barometer 14 Click driver.
 */
#define BAROMETER14_CONFIG_ID_MASK                  0x1F

/**
 * @brief Barometer 14 autonomous state sensor selection setting.
 * @details Specified setting for autonomous state sensor selection of Barometer 14 Click driver.
 */
#define BAROMETER14_AS_SENSOR_PRESSURE              0x00
#define BAROMETER14_AS_SENSOR_ACCELERATION          0x01
#define BAROMETER14_AS_SENSOR_DISABLED              0xFF

/**
 * @brief Barometer 14 threshold setting.
 * @details Specified setting for threshold of Barometer 14 Click driver.
 */
#define BAROMETER14_THR_LOWER_EN                    0x01
#define BAROMETER14_THR_UPPER_EN                    0x02
#define BAROMETER14_THR_TYPE_ABSOLUTE               0x00
#define BAROMETER14_THR_TYPE_RATE_CHANGE            0x04
#define BAROMETER14_THR_TYPE_REL_ON_STATE           0x08
#define BAROMETER14_THR_TYPE_REL_CONFIG_START       0x0C
#define BAROMETER14_THR_ACT_TO_ON_STATE             0x00
#define BAROMETER14_THR_ACT_CHANGE_CONFIG           0x40
#define BAROMETER14_THR_ACT_ACC_RECORDING           0x80
#define BAROMETER14_THR_ALERT_ON_CHANGE             0x20

/**
 * @brief Barometer 14 write data line keyword setting.
 * @details Specified setting for data line keyword of Barometer 14 Click driver.
 */
#define BAROMETER14_DATA_WRITE_KEYWORD              0x9D

/**
 * @brief Barometer 14 flash storage setting.
 * @details Specified setting for flash storage of Barometer 14 Click driver.
 */
#define BAROMETER14_DATA_STORAGE_MAX_ADDR           0x0BE0
#define BAROMETER14_DATA_LINE_BYTES                 32

/**
 * @brief Barometer 14 measurement result conversion factors setting.
 * @details Specified setting for measurement result conversion factors of Barometer 14 Click driver.
 */
#define BAROMETER14_PRESS_RES                       16.0f
#define BAROMETER14_ACC_RES                         16.0f
#define BAROMETER14_TEMP_RES                        128.0f

/**
 * @brief Barometer 14 SPI processing time delays setting.
 * @details Specified setting for SPI processing time delays of Barometer 14 Click driver.
 */
#define BAROMETER14_PROC_TIME_PRESS_MS              2
#define BAROMETER14_PROC_TIME_ACC_MS                2
#define BAROMETER14_PROC_TIME_TEMP_MS               2
#define BAROMETER14_PROC_TIME_READ_ID_MS            2
#define BAROMETER14_PROC_TIME_SELF_TEST_MS          5
#define BAROMETER14_PROC_TIME_SELF_TEST_MEM_MS      300
#define BAROMETER14_PROC_TIME_STATUS_MS             2
#define BAROMETER14_PROC_TIME_SET_SERIAL_MS         10
#define BAROMETER14_PROC_TIME_AS_HISTORY_MS         2
#define BAROMETER14_PROC_TIME_AS_BUFFER_MS          2
#define BAROMETER14_PROC_TIME_ACC_REC_MS            2
#define BAROMETER14_PROC_TIME_SAVE_AS_CFG_MS        20
#define BAROMETER14_PROC_TIME_READ_AS_CFG_MS        2
#define BAROMETER14_PROC_TIME_WRITE_DATA_MS         10
#define BAROMETER14_PROC_TIME_READ_DATA_MS          2

/**
 * @brief Barometer 14 BUSY pin polling timeout in milliseconds setting.
 * @details Specified setting for BUSY pin polling timeout in milliseconds of Barometer 14 Click driver.
 */
#define BAROMETER14_BUSY_TIMEOUT_MS                 1000

/**
 * @brief Barometer 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 14 Click driver.
 */
#define BAROMETER14_DEVICE_ADDRESS                  0x36

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b barometer14_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BAROMETER14_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define BAROMETER14_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // barometer14_set

/**
 * @defgroup barometer14_map Barometer 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 14 Click driver.
 */

/**
 * @addtogroup barometer14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 14 Click to the selected MikroBUS.
 */
#define BAROMETER14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wkp  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.alt  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // barometer14_map
/*! @} */ // barometer14

/**
 * @brief Barometer 14 Click driver selector.
 * @details Selects target driver interface of Barometer 14 Click driver.
 */
typedef enum
{
    BAROMETER14_DRV_SEL_SPI,                  /**< SPI driver descriptor. */
    BAROMETER14_DRV_SEL_I2C                   /**< I2C driver descriptor. */

} barometer14_drv_t;

/**
 * @brief Barometer 14 Click driver interface.
 * @details Definition of driver interface of Barometer 14 Click driver.
 */
struct barometer14_s;
typedef err_t ( *barometer14_master_io_t )( struct barometer14_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Barometer 14 Click context object.
 * @details Context object definition of Barometer 14 Click driver.
 */
typedef struct barometer14_s
{
    digital_in_t wkp;                               /**< Wake-up/BUSY monitoring pin. */
    digital_in_t alt;                               /**< Alert pin. */

    i2c_master_t i2c;                               /**< I2C driver object. */
    spi_master_t spi;                               /**< SPI driver object. */

    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */
    barometer14_drv_t drv_sel;                      /**< Master driver interface selector. */

    barometer14_master_io_t write_f;                /**< Master write function. */
    barometer14_master_io_t read_f;                 /**< Master read function. */

} barometer14_t;

/**
 * @brief Barometer 14 Click configuration object.
 * @details Configuration object definition of Barometer 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t wkp;                                 /**< Wake-up/BUSY monitoring pin */
    pin_name_t alt;                                 /**< Alert pin. */

    uint32_t   i2c_speed;                           /**< I2C serial speed. */
    uint8_t    i2c_address;                         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    barometer14_drv_t drv_sel;                      /**< Master driver interface selector. */

} barometer14_cfg_t;

/**
 * @brief Barometer 14 threshold configuration data structure.
 * @details Threshold configuration object definition of Barometer 14 Click driver.
 */
typedef struct
{
    uint8_t config;                                 /**< Threshold type and enable bits. */
    uint8_t trans_lower;                            /**< Lower threshold action and target config ID. */
    int16_t thrld_lower;                            /**< Lower threshold value (16 LSB = 1 kPa or 1 g). */
    uint8_t trans_upper;                            /**< Upper threshold action and target config ID. */
    int16_t thrld_upper;                            /**< Upper threshold value (16 LSB = 1 kPa or 1 g). */

} barometer14_threshold_cfg_t;

/**
 * @brief Barometer 14 measurement configuration data structure.
 * @details Measurement configuration object definition of Barometer 14 Click driver.
 */
typedef struct
{
    uint8_t  sensor;                                /**< Sensor selection (BAROMETER14_AS_SENSOR_*). */
    uint8_t  postcounter;                           /**< Measurement postcounter (1-255). */
    uint16_t rec_samples;                           /**< Number of samples for Acceleration Recording. */

    barometer14_threshold_cfg_t thr_1;              /**< High-priority threshold configuration. */
    barometer14_threshold_cfg_t thr_2;              /**< Low-priority threshold configuration. */

} barometer14_meas_cfg_t;

/**
 * @brief Barometer 14 autonomous state configuration data structure.
 * @details Autonomous state configuration object definition of Barometer 14 Click driver.
 */
typedef struct
{
    uint8_t  confg_id;                                    /**< Configuration identifier (0-31). */
    uint8_t  precounter;                            /**< AS Timer precounter in milliseconds (1-179). */
    uint16_t postcounter;                           /**< AS Timer postcounter (0-4096). */
    uint8_t  timeout;                               /**< Timeout setting (0 = disabled, 1-31 = 2^n periods). */

    barometer14_meas_cfg_t meas_1;                  /**< High-priority measurement configuration. */
    barometer14_meas_cfg_t meas_2;                  /**< Low-priority measurement configuration. */

} barometer14_as_cfg_t;

/**
 * @brief Barometer 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER14_OK = 0,
    BAROMETER14_ERROR = -1

} barometer14_return_value_t;

/*!
 * @addtogroup barometer14 Barometer 14 Click Driver
 * @brief API for configuring and manipulating Barometer 14 Click driver.
 * @{
 */

/**
 * @brief Barometer 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer14_cfg_setup ( barometer14_cfg_t *cfg );

/**
 * @brief Barometer 14 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #barometer14_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #barometer14_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set. SPI mode requires an MCU where the minimum achievable 
 * SPI clock does not exceed 100 kHz due to half-duplex implementation.
 */
void barometer14_drv_interface_sel ( barometer14_cfg_t *cfg, barometer14_drv_t drv_sel );

/**
 * @brief Barometer 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_init ( barometer14_t *ctx, barometer14_cfg_t *cfg );

/**
 * @brief Barometer 14 default configuration function.
 * @details This function executes a default configuration of Barometer 14
 * Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer14_default_cfg ( barometer14_t *ctx );

/**
 * @brief Barometer 14 measure pressure function.
 * @details This function triggers a single pressure measurement and reads
 * the result from Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[out] meas_status : Measurement status byte. 0 means no error.
 * See BAROMETER14_MEAS_STATUS_* bit mask definitions for detailed explanation.
 * @param[out] pressure : Pressure result in kPa.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_measure_pressure ( barometer14_t *ctx, uint8_t *meas_status, float *pressure );

/**
 * @brief Barometer 14 measure acceleration function.
 * @details This function triggers a single acceleration measurement and reads
 * the result from Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[out] meas_status : Measurement status byte. 0 means no error.
 * See BAROMETER14_MEAS_STATUS_* bit mask definitions for detailed explanation.
 * @param[out] acceleration : Acceleration result in g (Z-axis only).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_measure_accel ( barometer14_t *ctx, uint8_t *meas_status, float *acceleration );

/**
 * @brief Barometer 14 measure temperature function.
 * @details This function triggers a single temperature measurement and reads
 * the result from Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[out] meas_status : Measurement status byte. 0 means no error.
 * See BAROMETER14_MEAS_STATUS_* bit mask definitions for detailed explanation.
 * @param[out] temperature : Temperature result in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_measure_temp ( barometer14_t *ctx, uint8_t *meas_status, float *temperature );

/**
 * @brief Barometer 14 read ID function.
 * @details This function reads the sensor ID and product code from
 * Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[out] sensor_id : 32-bit unique sensor ID.
 * @param[out] product_code : 16-bit product code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_read_id ( barometer14_t *ctx, uint32_t *sensor_id, uint16_t *product_code );

/**
 * @brief Barometer 14 self test function.
 * @details This function runs the device self-test of Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] config : Self-test configuration byte.
 * See BAROMETER14_SELF_TEST_NO_MEM and BAROMETER14_SELF_TEST_WITH_MEM definitions.
 * @param[out] test_status : Pointer to self-test result byte. 0 means all checks passed.
 * See BAROMETER14_SELF_TEST_STATUS_* bit mask definitions for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note With memory check the processing time can be up to 280 ms.
 */
err_t barometer14_self_test ( barometer14_t *ctx, uint8_t config, uint8_t *test_status );

/**
 * @brief Barometer 14 soft reset function.
 * @details This function triggers a software reset of Barometer 14 Click board.
 * The device reinitializes and re-enters On State after approximately 10 ms.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call barometer14_default_cfg after this function to reconfigure the device.
 */
err_t barometer14_soft_reset ( barometer14_t *ctx );

/**
 * @brief Barometer 14 read status function.
 * @details This function reads the Device Status Register of Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] clear : Clear parameter.
 * Use BAROMETER14_STATUS_CLEAR to read and clear, or BAROMETER14_STATUS_NO_CLEAR to read only.
 * @param[out] dev_status : 24-bit Device Status word.
 * See BAROMETER14_DEV_STATUS_* bit mask definitions for detailed explanation.
 * @param[out] auto_status : 16-bit Autonomous Status word.
 * See BAROMETER14_AUTO_STATUS_* bit mask definitions for detailed explanation.
 * @param[out] meas_status : 8-bit Measurement Status byte.
 * @param[out] last_cfg_id : Last Autonomous State configuration ID used.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Always clear the status register before entering Autonomous State.
 */
err_t barometer14_read_status ( barometer14_t *ctx,
                                uint8_t clear,
                                uint32_t *dev_status,
                                uint16_t *auto_status,
                                uint8_t *meas_status,
                                uint8_t *last_cfg_id );

/**
 * @brief Barometer 14 lock serial interface function.
 * @details This function permanently locks the serial interface in the device flash
 * of Barometer 14 Click board. After this there is no need for serial interface selection after
 * every reset, but the interface cannot be changed anymore.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] type : Interface type to lock.
 * See BAROMETER14_SERIAL_* definitions for detailed explanation.
 * @param[out] set_status : Pointer to command result byte.
 * Bit 3 means already locked (not an error). Bit 7 means flash write failed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note After locking the serial interface, it is not possible to change the interface type anymore.
 */
err_t barometer14_lock_ser_interface ( barometer14_t *ctx, uint8_t type, uint8_t *set_status );

/**
 * @brief Barometer 14 enter autonomous state function.
 * @details This function transitions the device into Autonomous State.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] config_id : Initial Autonomous State configuration ID to use (0-31).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Status register should be cleared before this command to ensure correct Autonomous State operation.
 */
err_t barometer14_enter_auto_state ( barometer14_t *ctx, uint8_t config_id );

/**
 * @brief Barometer 14 enter sleep function.
 * @details This function transitions the device into Sleep state.
 * No response is read back. The device can only be woken by pulling WKP pin LOW.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_enter_sleep ( barometer14_t *ctx );

/**
 * @brief Barometer 14 read autonomous state history function.
 * @details This function reads the Autonomous State configuration history from
 * Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[out] length : Number of valid entries in the history (0-16).
 * @param[out] ids : Pointer to a buffer of at least 16 bytes for the config IDs.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_read_as_history ( barometer14_t *ctx, uint8_t *length, uint8_t *ids );

/**
 * @brief Barometer 14 read autonomous state pressure buffer function.
 * @details This function reads the Autonomous State pressure measurement buffer from
 * Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[out] length : Number of valid entries in the buffer (0-16).
 * @param[out] pressure : Pointer to a buffer of at least 16 floats for the results in kPa.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_read_as_press_buf ( barometer14_t *ctx, uint8_t *length, float *pressure );

/**
 * @brief Barometer 14 read autonomous state acceleration buffer function.
 * @details This function reads the Autonomous State acceleration measurement buffer from
 * Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[out] length : Number of valid entries in the buffer (0-16).
 * @param[out] acceleration : Pointer to a buffer of at least 16 floats for the results in g.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_read_as_accel_buf ( barometer14_t *ctx, uint8_t *length, float *acceleration );

/**
 * @brief Barometer 14 save autonomous state configuration function.
 * @details This function saves an Autonomous State configuration to the device flash
 * of Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] as_cfg : Pointer to the configuration to save.
 * See #barometer14_as_cfg_t object definition for detailed explanation.
 * @param[out] save_status : Pointer to a command result byte.
 * Bit 0 means a parameter was out of range and adjusted. Bit 7 means flash write failed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_save_as_config ( barometer14_t *ctx, barometer14_as_cfg_t *as_cfg, uint8_t *save_status );

/**
 * @brief Barometer 14 read autonomous state configuration function.
 * @details This function reads back a stored Autonomous State configuration from
 * Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] confg_id : Configuration ID to read (0-31).
 * @param[out] as_cfg : Pointer to the result structure.
 * See #barometer14_as_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_read_as_config ( barometer14_t *ctx, uint8_t confg_id, barometer14_as_cfg_t *as_cfg );

/**
 * @brief Barometer 14 write flash function.
 * @details This function writes 32 bytes of user data to the internal flash of
 * Barometer 14 Click board. Address must be 32-byte aligned.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] address : Target flash address (0x0000-0x0BE0, multiple of 32).
 * @param[in] data_in : Pointer to exactly 32 bytes of data to be written.
 * @param[out] write_status : Pointer to a command result byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Each 32-byte block can be written at most 100 times.
 */
err_t barometer14_write_flash ( barometer14_t *ctx, uint16_t address, uint8_t *data_in, uint8_t *write_status );

/**
 * @brief Barometer 14 read flash function.
 * @details This function reads 32 bytes of user data from the internal flash of
 * Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @param[in] address : Source flash address (0x0000-0x0BE0).
 * @param[out] data_out : Pointer to a buffer of at least 32 bytes.
 * @param[out] read_status : Pointer to a command result byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer14_read_flash ( barometer14_t *ctx, uint16_t address, uint8_t *data_out, uint8_t *read_status );

/**
 * @brief Barometer 14 get ALT pin function.
 * @details This function returns the state of the ALT pin of Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @return ALT pin state level.
 * @note None.
 */
uint8_t barometer14_get_alt ( barometer14_t *ctx );

/**
 * @brief Barometer 14 get WKP pin function.
 * @details This function returns the state of the WKP pin of Barometer 14 Click board.
 * @param[in] ctx : Click context object.
 * See #barometer14_t object definition for detailed explanation.
 * @return WKP pin state level.
 * @note None.
 */
uint8_t barometer14_get_wkp ( barometer14_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER14_H

/*! @} */ // barometer14

// ------------------------------------------------------------------------ END
