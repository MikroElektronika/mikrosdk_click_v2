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
 * @file accel30.h
 * @brief This file contains API for Accel 30 Click Driver.
 */

#ifndef ACCEL30_H
#define ACCEL30_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup accel30 Accel 30 Click Driver
 * @brief API for configuring and manipulating Accel 30 Click driver.
 * @{
 */

/**
 * @defgroup accel30_reg Accel 30 Registers List
 * @brief List of registers of Accel 30 Click driver.
 */

/**
 * @addtogroup accel30_reg
 * @{
 */

/**
 * @brief Accel 30 description register.
 * @details Specified register for description of Accel 30 Click driver.
 */
#define ACCEL30_REG_EXT_STAT_1                0x00
#define ACCEL30_REG_EXT_STAT_2                0x01
#define ACCEL30_REG_XOUT_LSB                  0x02
#define ACCEL30_REG_XOUT_MSB                  0x03
#define ACCEL30_REG_YOUT_LSB                  0x04
#define ACCEL30_REG_YOUT_MSB                  0x05
#define ACCEL30_REG_ZOUT_LSB                  0x06
#define ACCEL30_REG_ZOUT_MSB                  0x07
#define ACCEL30_REG_STATUS_1                  0x08
#define ACCEL30_REG_STATUS_2                  0x09
#define ACCEL30_REG_FREG_1                    0x0D
#define ACCEL30_REG_FREG_2                    0x0E
#define ACCEL30_REG_INIT_1                    0x0F
#define ACCEL30_REG_MODE_C                    0x10
#define ACCEL30_REG_WAKE_C                    0x11
#define ACCEL30_REG_SNIFF_C                   0x12
#define ACCEL30_REG_SNIFFTH_C                 0x13
#define ACCEL30_REG_SNIFFCF_C                 0x14
#define ACCEL30_REG_RANGE_C                   0x15
#define ACCEL30_REG_FIFO_C                    0x16
#define ACCEL30_REG_INTR_C                    0x17
#define ACCEL30_REG_INIT_3                    0x1A
#define ACCEL30_REG_SCRATCH                   0x1B
#define ACCEL30_REG_POWER_MODE                0x1C
#define ACCEL30_REG_DMX                       0x20
#define ACCEL30_REG_DMY                       0x21
#define ACCEL30_REG_DMZ                       0x22
#define ACCEL30_REG_RESET                     0x24
#define ACCEL30_REG_INIT_2                    0x28
#define ACCEL30_REG_TRIGC                     0x29
#define ACCEL30_REG_XOFFL                     0x2A
#define ACCEL30_REG_XOFFH                     0x2B
#define ACCEL30_REG_YOFFL                     0x2C
#define ACCEL30_REG_YOFFH                     0x2D
#define ACCEL30_REG_ZOFFL                     0x2E
#define ACCEL30_REG_ZOFFH                     0x2F
#define ACCEL30_REG_XGAIN                     0x30
#define ACCEL30_REG_YGAIN                     0x31
#define ACCEL30_REG_ZGAIN                     0x32
#define ACCEL30_REG_OPT                       0x3B
#define ACCEL30_REG_GAIN                      0x21


/*! @} */ // accel30_reg

/**
 * @defgroup accel30_set Accel 30 Registers Settings
 * @brief Settings for registers of Accel 30 Click driver.
 */

/**
 * @addtogroup accel30_set
 * @{
 */

/**
 * @brief Accel 30 description setting.
 * @details Specified setting for description of Accel 30 Click driver.
 */
#define ACCEL30_MODE_BIT_MASK                 0xF0
#define ACCEL30_RANGE_BIT_MASK                0x07
#define ACCEL30_GAIN_BIT_MASK                 0x3F
#define ACCEL30_RESOLUTION_BIT_MASK           0x70
#define ACCEL30_DMX_PN_DISABLE                0x00
#define ACCEL30_DMX_RES_BIT_MASK              0x01
#define ACCEL30_ENABLE_XYZ_AXIS_PD            0x00
#define ACCEL30_TRIG_CMD_CONTINUOUS           0x00
#define ACCEL30_TRIG_CMD_ONE_SHOT             0x01
#define ACCEL30_FORCE_RESET                   0x40
#define ACCEL30_I2C_ENABLE                    0x40
#define ACCEL30_SPI_ENABLE                    0x80
#define ACCEL30_MODE_BIT_MASK                 0xF0

/**
 * @brief Accel 30 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 30 Click driver.
 */
#define ACCEL30_DEVICE_ADDRESS_GND            0x4C
#define ACCEL30_DEVICE_ADDRESS_VCC            0x6C

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel30_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL30_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL30_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel30_set

/**
 * @defgroup accel30_map Accel 30 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 30 Click driver.
 */

/**
 * @addtogroup accel30_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 30 Click to the selected MikroBUS.
 */
#define ACCEL30_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel30_map
/*! @} */ // accel30

/**
 * @brief Accel 30 Click driver selector.
 * @details Selects target driver interface of Accel 30 Click driver.
 */
typedef enum
{
    ACCEL30_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ACCEL30_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel30_drv_t;

/**
 * @brief Accel 30 Click driver interface.
 * @details Definition of driver interface of Accel 30 Click driver.
 */
typedef err_t ( *accel30_master_io_t )( struct accel30_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 30 Click context object.
 * @details Context object definition of Accel 30 Click driver.
 */
typedef struct accel30_s
{
    digital_out_t rst;               /**< Reset pin. */

    digital_in_t int_pin;            /**< Interrupt pin. */

    i2c_master_t i2c;                /**< I2C driver object. */
    spi_master_t spi;                /**< SPI driver object. */

    uint8_t      slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    accel30_drv_t drv_sel;           /**< Master driver interface selector. */

    accel30_master_io_t write_f;     /**< Master write function. */
    accel30_master_io_t read_f;      /**< Master read function. */
    
    uint8_t range_cfg;               /**< Range configuration. */
    uint8_t resolution_cfg;          /**< Resolution configuration. */

} accel30_t;

/**
 * @brief Accel 30 Click configuration object.
 * @details Configuration object definition of Accel 30 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rst;             /**< Reset pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel30_drv_t drv_sel;      /**< Master driver interface selector. */

} accel30_cfg_t;

/**
 * @brief Accel 30 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL30_OK = 0,
    ACCEL30_ERROR = -1

} accel30_return_value_t;

/**
 * @brief Accel 30 Click gain value data.
 * @details Predefined enum values for driver gain values.
 */
typedef enum
{
    ACCEL30_GAIN_DEFAULT = 0,
    ACCEL30_GAIN_4X,
    ACCEL30_GAIN_1X,
    ACCEL30_GAIN_NOT_USED
    
} accel30_gain_t;

/**
 * @brief Accel 30 Click operating mode value data.
 * @details Predefined enum values for driver mode values.
 */
typedef enum
{
    ACCEL30_MODE_SLEEP   = 0,
    ACCEL30_MODE_STANDBY = 1,
    ACCEL30_MODE_SNIFF   = 2,
    ACCEL30_MODE_CWAKE   = 5, 
    ACCEL30_MODE_TRIG    = 7
    
} accel30_op_mode_t;

/**
 * @brief Accel 30 Click range value data.
 * @details Predefined enum values for driver range values.
 */
typedef enum
{
    ACCEL30_RANGE_2G = 0,
    ACCEL30_RANGE_4G,
    ACCEL30_RANGE_8G,
    ACCEL30_RANGE_12G,
    ACCEL30_RANGE_16G,
    ACCEL30_RANGE_END
    
} accel30_range_t;

/**
 * @brief Accel 30 Click resolution value data.
 * @details Predefined enum values for driver resolution values.
 */
typedef enum
{
    ACCEL30_RESOLUTION_6BIT = 0, 
    ACCEL30_RESOLUTION_7BIT, 
    ACCEL30_RESOLUTION_8BIT, 
    ACCEL30_RESOLUTION_10BIT, 
    ACCEL30_RESOLUTION_12BIT, 
    ACCEL30_RESOLUTION_14BIT, 
    ACCEL30_RESOLUTION_END
    
} accel30_resolution_t;

/**
 * @brief Accel 30 Click CWAKE sampling value data.
 * @details Predefined enum values for driver CWAKE sampling values.
 */
typedef enum
{
    ACCEL30_CWAKE_DEFAULT_50Hz = 0,
    ACCEL30_CWAKE_0p4Hz,
    ACCEL30_CWAKE_0p8Hz,
    ACCEL30_CWAKE_2Hz,
    ACCEL30_CWAKE_6Hz,
    ACCEL30_CWAKE_14Hz,
    ACCEL30_CWAKE_28Hz,
    ACCEL30_CWAKE_54Hz,
    ACCEL30_CWAKE_100Hz,
    ACCEL30_CWAKE_210Hz,
    ACCEL30_CWAKE_400Hz,
    ACCEL30_CWAKE_600Hz,
    ACCEL30_CWAKE_RESER0,
    ACCEL30_CWAKE_RESER1,
    ACCEL30_CWAKE_RESER2,
    ACCEL30_CWAKE_750Hz,
    ACCEL30_CWAKE_END
    
} accel30_cwake_t;

/**
 * @brief Accel 30 Click SNIFF sampling value data.
 * @details Predefined enum values for driver SNIFF sampling values.
 */
typedef enum
{
    ACCEL30_SNIFF_SR_DEFAULT_6Hz = 0,
    ACCEL30_SNIFF_SR_0p4Hz,
    ACCEL30_SNIFF_SR_0p8Hz,
    ACCEL30_SNIFF_SR_2Hz,
    ACCEL30_SNIFF_SR_6Hz,
    ACCEL30_SNIFF_SR_13Hz,
    ACCEL30_SNIFF_SR_25Hz,
    ACCEL30_SNIFF_SR_50Hz,
    ACCEL30_SNIFF_SR_100Hz,
    ACCEL30_SNIFF_SR_200Hz,
    ACCEL30_SNIFF_SR_400Hz,
    ACCEL30_SNIFF_SR_END
    
} accel30_sniff_sr_t;

/**
 * @brief Accel 30 Click FIFO mode value data.
 * @details Predefined enum values for driver FIFO mode values.
 */
typedef enum
{
    ACCEL30_FIFO_MODE_NORMAL = 0,
    ACCEL30_FIFO_MODE_WATERMARK,
    ACCEL30_FIFO_MODE_END
    
} accel30_fifo_mode_t;

/**
 * @brief Accel 30 Click power mode value data.
 * @details Predefined enum values for driver power mode values.
 */
typedef enum 
{
    ACCEL30_LOW_POWER = 0,
    ACCEL30_RESERVED_1,
    ACCEL30_RESERVED_2,
    ACCEL30_ULOW_POWER,
    ACCEL30_PRE_POWER
    
} accel30_power_mode_t;

/**
 * @brief Accel 30 Click Axis structure object.
 * @details Axis structure object definition of Accel 30 Click driver.
 */
typedef struct 
{
    int16_t x;
    int16_t y;
    int16_t z;

} accel30_axis_t;

/**
 * @brief Accel 30 Click Axis averaged structure object.
 * @details Axis averaged structure object definition of Accel 30 Click driver.
 */
typedef struct 
{
    float x;
    float y;
    float z;

} accel30_avg_axis_t;

/*!
 * @addtogroup accel30 Accel 30 Click Driver
 * @brief API for configuring and manipulating Accel 30 Click driver.
 * @{
 */

/**
 * @brief Accel 30 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel30_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel30_cfg_setup ( accel30_cfg_t *cfg );

/**
 * @brief Accel 30 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel30_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel30_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel30_drv_interface_selection ( accel30_cfg_t *cfg, accel30_drv_t drv_sel );

/**
 * @brief Accel 30 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel30_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_init ( accel30_t *ctx, accel30_cfg_t *cfg );

/**
 * @brief Accel 30 default configuration function.
 * @details This function executes a default configuration of Accel 30
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel30_default_cfg ( accel30_t *ctx );

/**
 * @brief Accel 30 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_generic_write ( accel30_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 30 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_generic_read ( accel30_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 30 set operating mode function.
 * @details This function set the desired operating mode value
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] mode : Operating mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_set_mode ( accel30_t *ctx, accel30_op_mode_t mode );

/**
 * @brief Accel 30 set range control function.
 * @details This function set the desired range control value
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] range : Range control.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_set_range_ctrl ( accel30_t *ctx, accel30_range_t range );

/**
 * @brief Accel 30 soft reset function.
 * @details This function perform a software reset
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_soft_reset ( accel30_t *ctx );

/**
 * @brief Accel 30 set sniff gain function.
 * @details This function set the desired sniff gain value
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] gain : Sniff gain.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_set_sniff_gain ( accel30_t *ctx, accel30_gain_t gain );

/**
 * @brief Accel 30 set wake gain function.
 * @details This function set the desired wake gain value
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] gain : Sniff gain.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_set_wake_gain ( accel30_t *ctx, accel30_gain_t gain );

/**
 * @brief Accel 30 set resolution control function.
 * @details This function set the desired resolution control value
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] resolution : Resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_set_resolution_ctrl ( accel30_t *ctx, accel30_resolution_t resolution );

/**
 * @brief Accel 30 set sampling rate function.
 * @details This function set the desired sampling rate value
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] sample_rate : Sampling rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_set_sample_rate ( accel30_t *ctx, accel30_cwake_t sample_rate );

/**
 * @brief Accel 30 set sniff sampling rate function.
 * @details This function set the desired sniff sampling rate value
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] sample_rate : Sniff sampling rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_set_sniff_sample_rate ( accel30_t *ctx, accel30_sniff_sr_t sample_rate );

/**
 * @brief Accel 30 set power mode function.
 * @details This function set the desired power mode
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] sample_rate : Sniff sampling rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_set_pwr_mode (accel30_t *ctx, accel30_power_mode_t pwr_mode );

/**
 * @brief Accel 30 get accel data function.
 * @details This function reads accel data for all three axis
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[out] acc_axis : Accel axis output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_get_axis ( accel30_t *ctx, accel30_axis_t *acc_axis );

/**
 * @brief Accel 30 get accel averaged data function.
 * @details This function reads accel averaged data for all three axis
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[out] acc_avg_axis : Accel averaged axis output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel30_get_avg_axes ( accel30_t *ctx, accel30_avg_axis_t *acc_avg_axis );

/**
 * @brief Accel 30 get interrupt function.
 * @details This function get states of the Interrupt ( INT ) pin
 * of MC3635 3-Axis Accelerometer on the Accel 30 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 * @note None.
 */
uint8_t accel30_get_int_pin ( accel30_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL30_H

/*! @} */ // accel30

// ------------------------------------------------------------------------ END
