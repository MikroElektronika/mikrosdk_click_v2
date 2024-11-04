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
 * @file accel21.h
 * @brief This file contains API for Accel 21 Click Driver.
 */

#ifndef ACCEL21_H
#define ACCEL21_H

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
 * @addtogroup accel21 Accel 21 Click Driver
 * @brief API for configuring and manipulating Accel 21 Click driver.
 * @{
 */

/**
 * @defgroup accel21_reg Accel 21 Registers List
 * @brief List of registers of Accel 21 Click driver.
 */

/**
 * @addtogroup accel21_reg
 * @{
 */

/**
 * @brief Accel 21 description register.
 * @details Specified register for description of Accel 21 Click driver.
 */
#define ACCEL21_REG_STATUS_AUX               0x07
#define ACCEL21_REG_OUT_TEMP_L               0x0C
#define ACCEL21_REG_OUT_TEMP_H               0x0D
#define ACCEL21_REG_INT_COUNTER              0x0E
#define ACCEL21_REG_WHO_AM_I                 0x0F
#define ACCEL21_REG_TEMP_CFG                 0x1F
#define ACCEL21_REG_CTRL_REG1                0x20
#define ACCEL21_REG_CTRL_REG2                0x21
#define ACCEL21_REG_CTRL_REG3                0x22
#define ACCEL21_REG_CTRL_REG4                0x23
#define ACCEL21_REG_CTRL_REG5                0x24
#define ACCEL21_REG_CTRL_REG6                0x25
#define ACCEL21_REG_REFERENCE_DATACAPTURE    0x26
#define ACCEL21_REG_STATUS                   0x27
#define ACCEL21_REG_OUT_X_L                  0x28
#define ACCEL21_REG_OUT_X_H                  0x29
#define ACCEL21_REG_OUT_Y_L                  0x2A
#define ACCEL21_REG_OUT_Y_H                  0x2B
#define ACCEL21_REG_OUT_Z_L                  0x2C
#define ACCEL21_REG_OUT_Z_H                  0x2D
#define ACCEL21_REG_FIFO_CTRL                0x2E
#define ACCEL21_REG_FIFO_SRC                 0x2F
#define ACCEL21_REG_INT1_CFG                 0x30
#define ACCEL21_REG_INT1_SRC                 0x31
#define ACCEL21_REG_INT1_THS                 0x32
#define ACCEL21_REG_INT1_DURATION            0x33
#define ACCEL21_REG_INT2_CFG                 0x34
#define ACCEL21_REG_INT2_SRC                 0x35
#define ACCEL21_REG_INT2_THS                 0x36
#define ACCEL21_REG_INT2_DURATION            0x37
#define ACCEL21_REG_CLICK_CFG                0x38
#define ACCEL21_REG_CLICK_SRC                0x39
#define ACCEL21_REG_CLICK_THS                0x3A
#define ACCEL21_REG_TIME_LIMIT               0x3B
#define ACCEL21_REG_TIME_LATENCY             0x3C
#define ACCEL21_REG_ACT_THS                  0x3E
#define ACCEL21_REG_ACT_DUR                  0x3F

/*! @} */ // accel21_reg

/**
 * @defgroup accel21_set Accel 21 Registers Settings
 * @brief Settings for registers of Accel 21 Click driver.
 */

/**
 * @addtogroup accel21_set
 * @{
 */

/**
 * @brief Accel 21 description setting.
 * @details Specified setting for description of Accel 21 Click driver.
 */
#define ACCEL21_STATUS_AUX_TDA_BIT_MASK       0x04
#define ACCEL21_STATUS_AUX_TOR_BIT_MASK       0x40

#define ACCEL21_TEMP_CFG_TEMP_EN_BIT_MASK     0xC0

#define ACCEL21_WHO_AM_I                      0x33

#define ACCEL21_OP_MODE_NORMAL                0x00
#define ACCEL21_OP_MODE_HIGH_RESOLUTION       0x01
#define ACCEL21_OP_MODE_LOW_POWER             0x02
#define ACCEL21_OP_MODE_NOT_ALLOWED           0x02
#define ACCEL21_CTRL_OP_MODE_BIT_MASK         0x08

#define ACCEL21_STATUS_NEW_DATA_AVL_BIT_MASK  0x08
#define ACCEL21_STATUS_DATA_OVERRUN_BIT_MASK  0x80

#define ACCEL21_CTRL_REG1_ODR_PWR_DOWN_MODE   0x00
#define ACCEL21_CTRL_REG1_ODR_1_Hz            0x01
#define ACCEL21_CTRL_REG1_ODR_10_Hz           0x02
#define ACCEL21_CTRL_REG1_ODR_25_Hz           0x03
#define ACCEL21_CTRL_REG1_ODR_50_Hz           0x04
#define ACCEL21_CTRL_REG1_ODR_100_Hz          0x05
#define ACCEL21_CTRL_REG1_ODR_200_Hz          0x06
#define ACCEL21_CTRL_REG1_ODR_400_Hz          0x07
#define ACCEL21_CTRL_REG1_ODR_1_62_kHz        0x08
#define ACCEL21_CTRL_REG1_ODR_1_344_kHz       0x09
#define ACCEL21_CTRL_REG1_ODR_BIT_MASK        0xF0

#define ACCEL21_CTRL_REG1_LPEN_DISABLE        0x00
#define ACCEL21_CTRL_REG1_LPEN_ENABLE         0x01
#define ACCEL21_CTRL_REG1_LPEN_BIT_MASK       0x08

#define ACCEL21_CTRL_REG1_XYZEN_DISABLE       0x00
#define ACCEL21_CTRL_REG1_XYZEN_ENABLE        0x01
#define ACCEL21_CTRL_REG1_ZEN_BIT_MASK        0x04
#define ACCEL21_CTRL_REG1_YEN_BIT_MASK        0x02
#define ACCEL21_CTRL_REG1_XEN_BIT_MASK        0x01

#define ACCEL21_CTRL_REG4_BDU_CONTIN_UPDATE   0x00
#define ACCEL21_CTRL_REG4_BDU_NOT_UPDATE      0x01
#define ACCEL21_CTRL_REG4_BDU_BIT_MASK        0x80

#define ACCEL21_CTRL_REG4_FS_2_g              0x00
#define ACCEL21_CTRL_REG4_FS_4_g              0x01
#define ACCEL21_CTRL_REG4_FS_10_g             0x02
#define ACCEL21_CTRL_REG4_FS_16_g             0x03
#define ACCEL21_CTRL_REG4_FS_BIT_MASK         0x30

#define ACCEL21_CTRL_REG4_HR_DISABLE          0x00
#define ACCEL21_CTRL_REG4_HR_ENABLE           0x01
#define ACCEL21_CTRL_REG1_HR_BIT_MASK         0x08

/**
 * @brief Accel 21 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 21 Click driver.
 */
#define ACCEL21_DEVICE_ADDRESS_GND            0x18
#define ACCEL21_DEVICE_ADDRESS_VCC            0x19

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel21_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL21_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL21_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel21_set

/**
 * @defgroup accel21_map Accel 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 21 Click driver.
 */

/**
 * @addtogroup accel21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 21 Click to the selected MikroBUS.
 */
#define ACCEL21_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel21_map
/*! @} */ // accel21

/**
 * @brief Accel 21 Click driver selector.
 * @details Selects target driver interface of Accel 21 Click driver.
 */
typedef enum
{
    ACCEL21_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ACCEL21_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel21_drv_t;

/**
 * @brief Accel 21 Click driver interface.
 * @details Definition of driver interface of Accel 21 Click driver.
 */
typedef err_t ( *accel21_master_io_t )( struct accel21_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 21 Click context object.
 * @details Context object definition of Accel 21 Click driver.
 */
typedef struct accel21_s
{
    digital_out_t rst;   /**< Reset pin. */

    digital_in_t in1;    /**< Interrupt pin 1. */
    digital_in_t in2;    /**< Interrupt pin 2. */

    i2c_master_t i2c;    /**< I2C driver object. */
    spi_master_t spi;    /**< SPI driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
    accel21_drv_t drv_sel;         /**< Master driver interface selector. */

    accel21_master_io_t write_f;    /**< Master write function. */
    accel21_master_io_t read_f;     /**< Master read function. */

} accel21_t;

/**
 * @brief Accel 21 Click configuration object.
 * @details Configuration object definition of Accel 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rst;     /**< Reset pin. */
    pin_name_t in1;     /**< Interrupt pin 1. */
    pin_name_t in2;     /**< Interrupt pin 2. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel21_drv_t drv_sel;    /**< Master driver interface selector. */

} accel21_cfg_t;

/**
 * @brief Accel 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL21_OK = 0,
    ACCEL21_ERROR = -1

} accel21_return_value_t;

/**
 * @brief Accel 21 Click Axis structure object.
 * @details Axis structure object definition of Accel 21 Click driver.
 */
typedef struct 
{
    int16_t x;
    int16_t y;
    int16_t z;

} accel21_axis_t;

/**
 * @brief Accel 21 Click configuration structure object.
 * @details Configuration structure object definition of Accel 21 Click driver.
 */
typedef struct 
{
    uint8_t odr;
    uint8_t lpen;
    uint8_t zen;
    uint8_t yen;
    uint8_t xen;
    uint8_t bdu;
    uint8_t fs;
    uint8_t hr;

} accel21_config_t;

/*!
 * @addtogroup accel21 Accel 21 Click Driver
 * @brief API for configuring and manipulating Accel 21 Click driver.
 * @{
 */

/**
 * @brief Accel 21 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel21_cfg_setup ( accel21_cfg_t *cfg );

/**
 * @brief Accel 21 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel21_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel21_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel21_drv_interface_selection ( accel21_cfg_t *cfg, accel21_drv_t drv_sel );

/**
 * @brief Accel 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_init ( accel21_t *ctx, accel21_cfg_t *cfg );

/**
 * @brief Accel 21 default configuration function.
 * @details This function executes a default configuration of Accel 21
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel21_default_cfg ( accel21_t *ctx );

/**
 * @brief Accel 21 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_generic_write ( accel21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 21 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_generic_read ( accel21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 21 get temperature status function.
 * @details This function reads a temperature status
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[out] temp_status : Output temperature status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_get_temp_status ( accel21_t *ctx, uint8_t *temp_status );

/**
 * @brief Accel 21 check temperature data ready function.
 * @details This function check if temperature data ready
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[out] temp_data_ready : Temperature new data available:
 *         @li @c  0 - new temperature data is not yet available,
 *         @li @c  1 - new temperature data is available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_check_temp_data_ready ( accel21_t *ctx, uint8_t *temp_data_ready );

/**
 * @brief Accel 21 enable temperature data function.
 * @details This function enables the temperature sensor
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_enable_temp_data ( accel21_t *ctx );

/**
 * @brief Accel 21 check temperature overrun function.
 * @details This function check if new temperature data 
 * has overwritten the previous data
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] temp_data_ovr : Temperature new data available:
 *         @li @c  0 - no overrun has occurred,
 *         @li @c  1 - new temperature data has overwritten the previous data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_check_temp_data_ovr ( accel21_t *ctx, uint8_t *temp_data_ovr );

/**
 * @brief Accel 21 get temperature data function.
 * @details This function reads the raw temperature data
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] temp_data : Temperature sensor data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Temperature data can be enabled by setting the 
 * TEMP_EN[1:0] bits to ‘1’ in the ACCEL21_REG_TEMP_CFG (1Fh) register.
 * To retrieve the temperature sensor data 
 * the BDU bit in CTRL_REG4 (23h) must be set to ‘1’.
 * Both the OUT_TEMP_L (0Ch), OUT_TEMP_H (0Dh) registers must be read.
 */
err_t accel21_get_temp_data ( accel21_t *ctx, int16_t *temp_data );

/**
 * @brief Accel 21 get temperature function.
 * @details This function reads the raw temperature data and converts it to Celsius
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Temperature data can be enabled by setting the 
 * TEMP_EN[1:0] bits to ‘1’ in the ACCEL21_REG_TEMP_CFG (1Fh) register.
 * To retrieve the temperature sensor data 
 * the BDU bit in CTRL_REG4 (23h) must be set to ‘1’.
 * Both the OUT_TEMP_L (0Ch), OUT_TEMP_H (0Dh) registers must be read.
 */
err_t accel21_get_temperature ( accel21_t *ctx, float *temperature );

/**
 * @brief Accel 21 set operating mode function.
 * @details This function set the desired operating mode
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @param[in] op_mode : Operating mode:
 *         @li @c  0 - normal,
 *         @li @c  1 - highresolution mode,
 *         @li @c  2 - low-power.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_set_op_mode ( accel21_t *ctx, uint8_t op_mode );

/**
 * @brief Accel 21 get operating mode function.
 * @details This function reads the operating mode
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] op_mode : Operating mode:
 *         @li @c  0 - normal,
 *         @li @c  1 - highresolution mode,
 *         @li @c  2 - low-power.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_get_op_mode ( accel21_t *ctx, uint8_t *op_mode );

/**
 * @brief Accel 21 get device ID function.
 * @details This function reads the device ID
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_get_device_id ( accel21_t *ctx, uint8_t *device_id );

/**
 * @brief Accel 21 check device ID function.
 * @details This function checking the device ID
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @return @li @c  0 - OK,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_check_id ( accel21_t *ctx );

/**
 * @brief Accel 21 get status function.
 * @details This function reads the status data
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_get_status ( accel21_t *ctx, uint8_t *status );

/**
 * @brief Accel 21 check accel overrun function.
 * @details This function check if new accel data 
 * has overwritten the previous data
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * @param[out] data_overrun : X-, Y- and Z-axis data overrun.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_check_data_overrun ( accel21_t *ctx, uint8_t *data_overrun );

/**
 * @brief Accel 21 check accel data ready function.
 * @details This function check if accel data ready
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[out] new_data_avl : Temperature new data available:
 *         @li @c  0 - a new set of data is not yet available,
 *         @li @c  1 - a new set of data is available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_check_new_data ( accel21_t *ctx, uint8_t *new_data_avl );

/**
 * @brief Accel 21 set config function.
 * @details This function set sensor configuration
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[out] config : Configuration structure object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_set_config ( accel21_t *ctx, accel21_config_t config );

/**
 * @brief Accel 21 get accel data function.
 * @details This function reads accel data for all three axis
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[out] acc_axis : Accel axis output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel21_get_axis ( accel21_t *ctx, accel21_axis_t *acc_axis );

/**
 * @brief Accel 21 get interrupt 1 function.
 * @details This function get states of the Interrupt 1 ( PWM pin )
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t accel21_get_in1_pin ( accel21_t *ctx );

/**
 * @brief Accel 21 get interrupt 2 function.
 * @details This function get states of the Interrupt 2 ( INT pin )
 * of the the MEMS digital output motion sensor 
 * ultra-low-power high-performance 3-axis accelerometer
 * on the Accel 21 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t accel21_get_in2_pin ( accel21_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL21_H

/*! @} */ // accel21

// ------------------------------------------------------------------------ END
