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
 * @file gyro9.h
 * @brief This file contains API for Gyro 9 Click Driver.
 */

#ifndef GYRO9_H
#define GYRO9_H

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
 * @addtogroup gyro9 Gyro 9 Click Driver
 * @brief API for configuring and manipulating Gyro 9 Click driver.
 * @{
 */

/**
 * @defgroup gyro9_reg Gyro 9 Registers List
 * @brief List of registers of Gyro 9 Click driver.
 */

/**
 * @addtogroup gyro9_reg
 * @{
 */

/**
 * @brief Gyro 9 description register.
 * @details Specified register for description of Gyro 9 Click driver.
 */
#define GYRO9_REG_WHO_AM_I                 0x0F
#define GYRO9_REG_CTRL_REG1                0x20
#define GYRO9_REG_CTRL_REG2                0x21
#define GYRO9_REG_CTRL_REG3                0x22
#define GYRO9_REG_CTRL_REG4                0x23
#define GYRO9_REG_CTRL_REG5                0x24
#define GYRO9_REG_REFERENCE                0x25
#define GYRO9_REG_OUT_TEMP                 0x26
#define GYRO9_REG_STATUS_REG               0x27
#define GYRO9_REG_OUT_X_L                  0x28
#define GYRO9_REG_OUT_X_H                  0x29
#define GYRO9_REG_OUT_Y_L                  0x2A
#define GYRO9_REG_OUT_Y_H                  0x2B
#define GYRO9_REG_OUT_Z_L                  0x2C
#define GYRO9_REG_OUT_Z_H                  0x2D
#define GYRO9_REG_FIFO_CTRL_REG            0x2E
#define GYRO9_REG_FIFO_SRC_REG             0x2F
#define GYRO9_REG_INT1_CFG                 0x30
#define GYRO9_REG_INT1_SRC                 0x31
#define GYRO9_REG_INT1_TSH_XH              0x32
#define GYRO9_REG_INT1_TSH_XL              0x33
#define GYRO9_REG_INT1_TSH_YH              0x34
#define GYRO9_REG_INT1_TSH_YL              0x35
#define GYRO9_REG_INT1_TSH_ZH              0x36
#define GYRO9_REG_INT1_TSH_ZL              0x37
#define GYRO9_REG_INT1_DURATION            0x38

/*! @} */ // gyro9_reg

/**
 * @defgroup gyro9_set Gyro 9 Registers Settings
 * @brief Settings for registers of Gyro 9 Click driver.
 */

/**
 * @addtogroup gyro9_set
 * @{
 */

/**
 * @brief Gyro 9 device identification values.
 * @details Specified device identification values of Gyro 9 Click driver.
 */
#define GYRO9_WHO_AM_I                     0xD3

/**
 * @brief Gyro 9 output data rate selection.
 * @details Specified output data rate selection of Gyro 9 Click driver.
 */
#define GYRO9_ODR_100_HZ                   0x00
#define GYRO9_ODR_200_HZ                   0x01
#define GYRO9_ODR_400_HZ                   0x02
#define GYRO9_ODR_800_HZ                   0x03
#define GYRO9_ODR_BIT_MASK                 0xC0

/**
 * @brief Gyro 9 bandwidth selection.
 * @details Specified bandwidth selection of Gyro 9 Click driver.
 */
#define GYRO9_BW_0                         0x00
#define GYRO9_BW_1                         0x01
#define GYRO9_BW_2                         0x02
#define GYRO9_BW_3                         0x03
#define GYRO9_BW_BIT_MASK                  0x30

/**
 * @brief Gyro 9 power mode selection.
 * @details Specified power mode selection of Gyro 9 Click driver.
 */
#define GYRO9_PD_POWER_DOWN                0x00
#define GYRO9_PD_SLEEP                     0x08
#define GYRO9_PD_NORMAL                    0x0F
#define GYRO9_PD_BIT_MASK                  0x08

/**
 * @brief Gyro 9 power mode selection.
 * @details Specified power mode selection of Gyro 9 Click driver.
 */
#define GYRO9_FIFO_CTRL_BYPASS_MODE        0x00
#define GYRO9_FIFO_CTRL_FIFO_MODE          0x01
#define GYRO9_FIFO_CTRL_STREAM_MODE        0x02
#define GYRO9_FIFO_CTRL_BIT_MASK           0xE0

/**
 * @brief Gyro 9 control register 3 data values.
 * @details Specified control register 3 data values of Gyro 9 Click driver.
 */
#define GYRO9_CTRL_I1_INT1_EN              0x80
#define GYRO9_CTRL_I1_INT1_DIS             0x00
#define GYRO9_CTRL_I1_BOOT_EN              0x40
#define GYRO9_CTRL_I1_BOOT_DIS             0x00
#define GYRO9_CTRL_H_LACTIVE_EN            0x20
#define GYRO9_CTRL_H_LACTIVE_DIS           0x00
#define GYRO9_CTRL_PP_OD_EN                0x10
#define GYRO9_CTRL_PP_OD_DIS               0x00
#define GYRO9_CTRL_I2_DRDY_EN              0x08
#define GYRO9_CTRL_I2_DRDY_DIS             0x00
#define GYRO9_CTRL_I2_WTM_EN               0x04
#define GYRO9_CTRL_I2_WTM_DIS              0x00
#define GYRO9_CTRL_I2_ORUN_EN              0x02
#define GYRO9_CTRL_I2_ORUN_DIS             0x00
#define GYRO9_CTRL_I2_EMPTY_EN             0x01
#define GYRO9_CTRL_I2_EMPTY_DIS            0x00

/**
 * @brief Gyro 9 device identification values.
 * @details Specified device identification values of Gyro 9 Click driver.
 */
#define GYRO9_SENSITIVITY_DPS              0.00875f

/**
 * @brief Gyro 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Gyro 9 Click driver.
 */
#define GYRO9_DEVICE_ADDRESS_GND           0x68
#define GYRO9_DEVICE_ADDRESS_VCC           0x69

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gyro9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GYRO9_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define GYRO9_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gyro9_set

/**
 * @defgroup gyro9_map Gyro 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Gyro 9 Click driver.
 */

/**
 * @addtogroup gyro9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Gyro 9 Click to the selected MikroBUS.
 */
#define GYRO9_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.dr   = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gyro9_map
/*! @} */ // gyro9

/**
 * @brief Gyro 9 Click driver selector.
 * @details Selects target driver interface of Gyro 9 Click driver.
 */
typedef enum
{
    GYRO9_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    GYRO9_DRV_SEL_I2C       /**< I2C driver descriptor. */

} gyro9_drv_t;

/**
 * @brief Gyro 9 Click driver interface.
 * @details Definition of driver interface of Gyro 9 Click driver.
 */
typedef err_t ( *gyro9_master_io_t )( struct gyro9_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Gyro 9 Click context object.
 * @details Context object definition of Gyro 9 Click driver.
 */
typedef struct gyro9_s
{
    digital_in_t dr;         /**< Data ready pin. */
    digital_in_t int_pin;    /**< Interrupt pin. */

    i2c_master_t i2c;        /**< I2C driver object. */
    spi_master_t spi;        /**< SPI driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
    gyro9_drv_t drv_sel;           /**< Master driver interface selector. */

    gyro9_master_io_t write_f;     /**< Master write function. */
    gyro9_master_io_t read_f;      /**< Master read function. */

} gyro9_t;

/**
 * @brief Gyro 9 Click configuration object.
 * @details Configuration object definition of Gyro 9 Click driver.
 */
typedef struct
{
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t dr;         /**< Data ready pin. */
    pin_name_t int_pin;    /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

    gyro9_drv_t drv_sel;    /**< Master driver interface selector. */

} gyro9_cfg_t;

/**
 * @brief Gyro 9 Click axis raw data structure object.
 * @details Axis raw data object definition of Gyro 9 Click driver.
 */
typedef struct 
{
    int16_t x;    /**< X-axis angular rate output raw data. */
    int16_t y;    /**< Y-axis angular rate output raw data. */
    int16_t z;    /**< Z-axis angular rate output raw data. */

} gyro9_axis_data_t;


/**
 * @brief Gyro 9 Click sensor axes structure object.
 * @details Sensor axes object definition of Gyro 9 Click driver.
 */
typedef struct 
{
    float x;    /**< X-axis: convert raw-data into engineering units. */
    float y;    /**< Y-axis: convert raw-data into engineering units. */
    float z;    /**< Z-axis: convert raw-data into engineering units. */

} gyro9_axis_t;

/**
 * @brief Gyro 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GYRO9_OK = 0,
    GYRO9_ERROR = -1

} gyro9_return_value_t;

/*!
 * @addtogroup gyro9 Gyro 9 Click Driver
 * @brief API for configuring and manipulating Gyro 9 Click driver.
 * @{
 */

/**
 * @brief Gyro 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gyro9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gyro9_cfg_setup ( gyro9_cfg_t *cfg );

/**
 * @brief Gyro 9 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gyro9_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gyro9_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gyro9_drv_interface_selection ( gyro9_cfg_t *cfg, gyro9_drv_t drv_sel );

/**
 * @brief Gyro 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gyro9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_init ( gyro9_t *ctx, gyro9_cfg_t *cfg );

/**
 * @brief Gyro 9 default configuration function.
 * @details This function executes a default configuration of Gyro 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t gyro9_default_cfg ( gyro9_t *ctx );

/**
 * @brief Gyro 9 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_generic_write ( gyro9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Gyro 9 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_generic_read ( gyro9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Gyro 9 get device ID function.
 * @details This function reads a device identification value
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[out] who_am_i : Device identification data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_get_device_id ( gyro9_t *ctx, uint8_t *who_am_i );

/**
 * @brief Gyro 9 set output data rate function.
 * @details This function sets the desired output data rate
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] odr : Output data rate [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_set_output_data_rate ( gyro9_t *ctx, uint8_t odr );

/**
 * @brief Gyro 9 set bandwidth function.
 * @details This function sets the desired bandwidth
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] bandwidth : Bandwidth selection [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_set_bandwidth_sel ( gyro9_t *ctx, uint8_t bandwidth );

/**
 * @brief Gyro 9 set power-down mode function.
 * @details This function sets power-down mode
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_set_mode_pd ( gyro9_t *ctx );

/**
 * @brief Gyro 9 set sleep mode function.
 * @details This function sets sleep mode
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_set_mode_sleep ( gyro9_t *ctx );

/**
 * @brief Gyro 9 set normal mode function.
 * @details This function sets normal mode
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_set_mode_normal ( gyro9_t *ctx );

/**
 * @brief Gyro 9 set FIFO mode function.
 * @details This function sets the desired FIFO mode
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] fifo_mode : FIFO mode configuration [0-2].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_set_fifo_mode ( gyro9_t *ctx, uint8_t fifo_mode );

/**
 * @brief Gyro 9 enable data ready function.
 * @details This function enable data ready DR pin 
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_enable_data_ready ( gyro9_t *ctx );

/**
 * @brief Gyro 9 get status function.
 * @details This function reads status register
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] status : Status register data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_get_status ( gyro9_t *ctx, uint8_t *status );

/**
 * @brief Gyro 9 get gyro data function.
 * @details This function reads the gyroscope raw data 
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[out] gyro_axis : Gyroscope raw data object.
 * See #gyro9_axis_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_get_axis_data ( gyro9_t *ctx, gyro9_axis_data_t *gyro_axis );

/**
 * @brief Gyro 9 get gyro sensor axes function.
 * @details This function reads the gyroscope raw data and convert to the engineering units 
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[out] gyro_axis : Angular rate output data object (dps).
 * See #gyro9_axis_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_get_gyro_axis ( gyro9_t *ctx, gyro9_axis_t *gyro_axis );

/**
 * @brief Gyro 9 get temperature data function.
 * @details This function reads the temperature raw data 
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[out] temp_raw : Temperature raw data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro9_get_temperature_raw ( gyro9_t *ctx, int8_t *temp_raw );

/**
 * @brief Gyro 9 get data ready function.
 * @details This function gets states of the data ready (DR) pin 
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @return @li @c 0 - Data is not ready,
 *         @li @c 1 - Data is ready.
 * @note None.
 */
uint8_t gyro9_get_data_ready ( gyro9_t *ctx );

/**
 * @brief Gyro 9 get interrupt function.
 * @details This function gets states of the Interrupt (INT) pin 
 * of the A3G4250D, MEMS motion sensor: 3-axis digital output gyroscope
 * on the Gyro 9 click board™.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t gyro9_get_interrupt ( gyro9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // GYRO9_H

/*! @} */ // gyro9

// ------------------------------------------------------------------------ END
