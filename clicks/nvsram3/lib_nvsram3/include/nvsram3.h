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
 * @file nvsram3.h
 * @brief This file contains API for nvSRAM 3 Click Driver.
 */

#ifndef NVSRAM3_H
#define NVSRAM3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup nvsram3 nvSRAM 3 Click Driver
 * @brief API for configuring and manipulating nvSRAM 3 Click driver.
 * @{
 */

/**
 * @defgroup nvsram3_reg nvSRAM 3 Registers List
 * @brief List of registers of nvSRAM 3 Click driver.
 */

/**
 * @addtogroup nvsram3_reg
 * @{
 */

/**
 * @brief nvSRAM 3 Control Registers Map.
 * @details Specified register for description of nvSRAM 3 Click driver.
 */

#define NVSRAM3_CONTROL_REG_MEM_CTRL                 0x00
#define NVSRAM3_CONTROL_REG_SERIAL_NUMBER         0x01
#define NVSRAM3_CONTROL_REG_DEVICE_ID                 0x09
#define NVSRAM3_CONTROL_REG_CMD                          0xAA

/**
 * @brief nvSRAM 3 RTC Registers Map.
 * @details Specified register for description of nvSRAM 3 Click driver.
 */

#define NVSRAM3_RTC_REG_FLAGS                                    0x00
#define NVSRAM3_RTC_REG_TIME_KEEPING_CENTURIES       0x01
#define NVSRAM3_RTC_REG_ALARM_SECONDS                     0x02
#define NVSRAM3_RTC_REG_ALARM_MINUTES                     0x03
#define NVSRAM3_RTC_REG_ALARM_HOURS                        0x04
#define NVSRAM3_RTC_REG_ALARM_DAY                            0x05
#define NVSRAM3_RTC_REG_INTERRUPT_STATUS_CONTROL 0x06
#define NVSRAM3_RTC_REG_WATCHDOG_TIMER                  0x07
#define NVSRAM3_RTC_REG_CALIBRATION_CONTROL           0x08
#define NVSRAM3_RTC_REG_TIME_KEEPING_SECONDS          0x09
#define NVSRAM3_RTC_REG_TIME_KEEPING_MINUTES          0x0A
#define NVSRAM3_RTC_REG_TIME_KEEPING_HOURS             0x0B
#define NVSRAM3_RTC_REG_TIME_KEEPING_DAY                 0x0C
#define NVSRAM3_RTC_REG_TIME_KEEPING_DATE                0x0D
#define NVSRAM3_RTC_REG_TIME_KEEPING_MONTHS           0x0E
#define NVSRAM3_RTC_REG_TIME_KEEPING_YEARS              0x0F

/*! @} */ // nvsram3_reg

/**
 * @defgroup nvsram3_set nvSRAM 3 Registers Settings
 * @brief Settings for registers of nvSRAM 3 Click driver.
 */

/**
 * @addtogroup nvsram3_set
 * @{
 */

/**
 * @brief nvSRAM 3 Control Registers description setting.
 * @details Specified setting for description of nvSRAM 3 Click driver.
 */
#define NVSRAM3_SERIAL_NUMBER_LOCK        0x40
#define NVSRAM3_SERIAL_NUMBER_UNLOCK    0x00
#define NVSRAM3_BLOCK_PROTECT_QUARTER 0x04
#define NVSRAM3_BLOCK_PROTECT_HALF        0x08
#define NVSRAM3_BLOCK_PROTECT_FULL        0x0C

#define NVSRAM3_STORE_COMMAND         0x3C
#define NVSRAM3_RECALL_COMMAND        0x60
#define NVSRAM3_ASENB_COMMAND         0x59
#define NVSRAM3_ASDISB_COMMAND        0x19
#define NVSRAM3_SLEEP_COMMAND          0xB9

/**
 * @brief nvSRAM 3 RTC Registers description setting.
 * @details Specified setting for description of nvSRAM 3 Click driver.
 */
#define NVSRAM3_RTC_WRITE_ENABLE      0x02
#define NVSRAM3_RTC_WRITE_DISABLE     0x00
#define NVSRAM3_RTC_READ_ENABLE        0x01
#define NVSRAM3_RTC_READ_DISABLE      0x00

/**
 * @brief nvSRAM 3 device address setting.
 * @details Specified setting for device slave address selection of
 * nvSRAM 3 Click driver.
 */
#define NVSRAM3_MEMORY_DEV_ADDR_0  0x50
#define NVSRAM3_MEMORY_DEV_ADDR_1  0x52
#define NVSRAM3_MEMORY_DEV_ADDR_2  0x54
#define NVSRAM3_MEMORY_DEV_ADDR_3  0x56

#define NVSRAM3_RTC_DEV_ADDR_0  0x68
#define NVSRAM3_RTC_DEV_ADDR_1  0x6A
#define NVSRAM3_RTC_DEV_ADDR_2  0x6C
#define NVSRAM3_RTC_DEV_ADDR_3  0x6E

#define NVSRAM3_CONTROL_DEV_ADDR_0  0x18
#define NVSRAM3_CONTROL_DEV_ADDR_1  0x1A
#define NVSRAM3_CONTROL_DEV_ADDR_2  0x1C
#define NVSRAM3_CONTROL_DEV_ADDR_3  0x1E

/**
 * @brief nvSRAM 3 pins setting.
 * @details Specified setting for HSB and WP pins.
 */

#define NVSRAM3_HSB_ENABLE                                        0x00
#define NVSRAM3_HSB_DISABLE                                       0x01

#define NVSRAM3_WP_ENABLE                                        0x00
#define NVSRAM3_WP_DISABLE                                       0x01

/*! @} */ // nvsram3_set

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief nvSRAM 3 error status.
 * @details Specified error status 
 * for description of nvSRAM 3 Click driver.
 */
#define NVSRAM3_SUCCESS            0
#define NVSRAM3_ERROR              -1


/*! @} */ // status

/**
 * @defgroup nvsram3_map nvSRAM 3 MikroBUS Map
 * @brief MikroBUS pin mapping of nvSRAM 3 Click driver.
 */

/**
 * @addtogroup nvsram3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of nvSRAM 3 Click to the selected MikroBUS.
 */
#define NVSRAM3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.hsb = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nvsram3_map
/*! @} */ // nvsram3

/**
 * @brief nvSRAM 3 Click context object.
 * @details Context object definition of nvSRAM 3 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  hsb;     /**< Hardware Store and HSB pin. */
    digital_out_t  wp;     /**< Hardware Write Protection WP pin. */

    // Input pins

    digital_in_t  int_pin;      /**< Interrupt INT pin. */

    // Modules

    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} nvsram3_t;

/**
 * @brief nvSRAM 3 Click configuration object.
 * @details Configuration object definition of nvSRAM 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  hsb;       /**< Hardware Store and HSB pin. */
    pin_name_t  wp;       /**< Hardware Write Protection WP pin. */
    pin_name_t  int_pin;       /**< Interrupt INT pin. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} nvsram3_cfg_t;

typedef struct 
{
    
    uint8_t hours; 
    uint8_t min;
    uint8_t sec; 
    
} nvsram3_rtc_time_t;

typedef struct 
{
    
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t day_of_week;
} nvsram3_rtc_date_t;

typedef struct 
{
    
    uint8_t day;
    uint8_t hours; 
    uint8_t min;
    uint8_t sec; 
    
} nvsram3_rtc_alarm_t;

/*!
 * @addtogroup nvsram3 nvSRAM 3 Click Driver
 * @brief API for configuring and manipulating nvSRAM 3 Click driver.
 * @{
 */

/**
 * @brief nvSRAM 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nvsram3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void nvsram3_cfg_setup ( nvsram3_cfg_t *cfg );

/**
 * @brief nvSRAM 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nvsram3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t nvsram3_init ( nvsram3_t *ctx, nvsram3_cfg_t *cfg );

/**
 * @brief nvSRAM 3 default configuration function.
 * @details This function executes a default configuration of nvSRAM 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t nvsram3_default_cfg ( nvsram3_t *ctx );

/**
 * @brief nvSRAM 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t nvsram3_generic_write ( nvsram3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief nvSRAM 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t nvsram3_generic_read ( nvsram3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief nvSRAM 3 send command function.
 * @details This function writes a desired command by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_send_cmd ( nvsram3_t *ctx, uint8_t cmd );

/**
 * @brief nvSRAM 3 write memory function.
 * @details This function write a desired number of data bytes starting from
 * the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address.
 * @param[in] data_in : Data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_memory_write ( nvsram3_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief nvSRAM 3 read memory function.
 * @details This function reads a desired number of data bytes starting from
 * the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address.
 * @param[out] data_out : Output read data.
 * @param[in] n_bytes : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_memory_read ( nvsram3_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief nvSRAM 3 get device ID function.
 * @details This function reads the device ID register.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @return device_id : Device ID (4 bytes).
 *
 * @endcode
 */
uint32_t nvsram3_get_device_id ( nvsram3_t *ctx );

/**
 * @brief nvSRAM 3 RTC read register function.
 * @details This function reads data byte from the selected RTC register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] rtc_reg : RTC register address.
 * @param[out] data_out : data read from the selected register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_rtc_read_reg ( nvsram3_t *ctx, uint8_t rtc_reg, uint8_t *data_out );

/**
 * @brief nvSRAM 3 RTC write register function.
 * @details This function writes data byte to the selected RTC register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] rtc_reg : RTC register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_rtc_write_reg ( nvsram3_t *ctx, uint8_t rtc_reg, uint8_t data_in ) ;

/**
 * @brief nvSRAM 3 get RTC time function.
 * @details This function get RTC time data structure.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[out] rtc_time : RTC time context object.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram3_get_rtc_time ( nvsram3_t *ctx, nvsram3_rtc_time_t *rtc_time );

/**
 * @brief nvSRAM 3 set RTC time function.
 * @details This function set RTC time data structure. 
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] rtc_time : RTC time context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_set_rtc_time ( nvsram3_t *ctx, nvsram3_rtc_time_t rtc_time );

/**
 * @brief nvSRAM 3 get RTC date function.
 * @details This function get RTC date data structure.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[out] rtc_date : RTC date context object.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram3_get_rtc_date ( nvsram3_t *ctx, nvsram3_rtc_date_t *rtc_date );

/**
 * @brief nvSRAM 3 set RTC date function.
 * @details This function set RTC date data structure.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] rtc_date : RTC date context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_set_rtc_date ( nvsram3_t *ctx, nvsram3_rtc_date_t rtc_date );

/**
 * @brief nvSRAM 3 get RTC alarm function.
 * @details This function get RTC alarm structure.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[out] rtc_alarm : RTC alarm context object.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void nvsram3_get_rtc_alarm ( nvsram3_t *ctx, nvsram3_rtc_alarm_t *rtc_alarm );

/**
 * @brief nvSRAM 3 set RTC alarm function.
 * @details This function set RTC date alarm structure.
 * @param[in] ctx : Click context object.
 * See #nvsram4_t object definition for detailed explanation.
 * @param[in] rtc_alarm : RTC alarm context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_set_rtc_alarm ( nvsram3_t *ctx, nvsram3_rtc_alarm_t rtc_alarm );

/**
 * @brief nvSRAM 3 hardware store function.
 * @details This function set hardware store by setting the HSB pin state.
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] state : 
 *         @li @c 0 ( NVSRAM3_HSB_ENABLE ) - Store operations,
 *         @li @c 1 ( NVSRAM3_HSB_DISABLE )- Resume the serial communication.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_hardware_store ( nvsram3_t *ctx, uint8_t state );

/**
 * @brief nvSRAM 3 write protection function.
 * @details This function set write protection by setting the WP pin state. 
 * @param[in] ctx : Click context object.
 * See #nvsram3_t object definition for detailed explanation.
 * @param[in] state : 
 *         @li @c 0 ( NVSRAM3_WP_ENABLE ) - Enable write protection,
 *         @li @c 1 ( NVSRAM3_WP_DISABLE ) - Disable write protection.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nvsram3_hw_write_protection ( nvsram3_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // NVSRAM3_H

/*! @} */ // nvsram3

// ------------------------------------------------------------------------ END
