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
 * @file accel37.h
 * @brief This file contains API for Accel 37 Click Driver.
 */

#ifndef ACCEL37_H
#define ACCEL37_H

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
 * @addtogroup accel37 Accel 37 Click Driver
 * @brief API for configuring and manipulating Accel 37 Click driver.
 * @{
 */

/**
 * @defgroup accel37_reg Accel 37 Registers List
 * @brief List of registers of Accel 37 Click driver.
 */

/**
 * @addtogroup accel37_reg
 * @{
 */

/**
 * @brief Accel 37 register list.
 * @details Specified register list of Accel 37 Click driver.
 */
#define ACCEL37_REG_DEVID_AD                    0x00  
#define ACCEL37_REG_DEVID_MST                   0x01 
#define ACCEL37_REG_PART_ID                     0x02
#define ACCEL37_REG_REV_ID                      0x03
#define ACCEL37_REG_SERIAL_NUMBER_2             0x05
#define ACCEL37_REG_SERIAL_NUMBER_1             0x06
#define ACCEL37_REG_SERIAL_NUMBER_0             0x07
#define ACCEL37_REG_XDATA                       0x08
#define ACCEL37_REG_YDATA                       0x09
#define ACCEL37_REG_ZDATA                       0x0A
#define ACCEL37_REG_STATUS                      0x0B
#define ACCEL37_REG_FIFO_ENTRIES_L              0x0C
#define ACCEL37_REG_FIFO_ENTRIES_H              0x0D
#define ACCEL37_REG_XDATA_H                     0x0E
#define ACCEL37_REG_XDATA_L                     0x0F
#define ACCEL37_REG_YDATA_H                     0x10
#define ACCEL37_REG_YDATA_L                     0x11
#define ACCEL37_REG_ZDATA_H                     0x12
#define ACCEL37_REG_ZDATA_L                     0x13
#define ACCEL37_REG_TEMP_H                      0x14
#define ACCEL37_REG_TEMP_L                      0x15
#define ACCEL37_REG_EX_ADC_H                    0x16
#define ACCEL37_REG_EX_ADC_L                    0x17
#define ACCEL37_REG_I2C_FIFO_DATA               0x18
#define ACCEL37_REG_SOFT_RESET                  0x1F
#define ACCEL37_REG_THRESH_ACT_H                0x20
#define ACCEL37_REG_THRESH_ACT_L                0x21
#define ACCEL37_REG_TIME_ACT                    0x22
#define ACCEL37_REG_THRESH_INACT_H              0x23
#define ACCEL37_REG_THRESH_INACT_L              0x24
#define ACCEL37_REG_TIME_INACT_H                0x25
#define ACCEL37_REG_TIME_INACT_L                0x26
#define ACCEL37_REG_ACT_INACT_CTL               0x27
#define ACCEL37_REG_FIFO_CONTROL                0x28
#define ACCEL37_REG_FIFO_SAMPLES                0x29
#define ACCEL37_REG_INTMAP1_LOWER               0x2A
#define ACCEL37_REG_INTMAP2_LOWER               0x2B
#define ACCEL37_REG_FILTER_CTL                  0x2C
#define ACCEL37_REG_POWER_CTL                   0x2D
#define ACCEL37_REG_SELF_TEST                   0x2E
#define ACCEL37_REG_TAP_THRESH                  0x2F
#define ACCEL37_REG_TAP_DUR                     0x30
#define ACCEL37_REG_TAP_LATENT                  0x31
#define ACCEL37_REG_TAP_WINDOW                  0x32
#define ACCEL37_REG_X_OFFSET                    0x33
#define ACCEL37_REG_Y_OFFSET                    0x34
#define ACCEL37_REG_Z_OFFSET                    0x35
#define ACCEL37_REG_X_SENS                      0x36
#define ACCEL37_REG_Y_SENS                      0x37
#define ACCEL37_REG_Z_SENS                      0x38
#define ACCEL37_REG_TIMER_CTL                   0x39
#define ACCEL37_REG_INTMAP1_UPPER               0x3A
#define ACCEL37_REG_INTMAP2_UPPER               0x3B
#define ACCEL37_REG_ADC_CTL                     0x3C
#define ACCEL37_REG_TEMP_CTL                    0x3D
#define ACCEL37_REG_TEMP_ADC_OVER_THRSH_H       0x3E
#define ACCEL37_REG_TEMP_ADC_OVER_THRSH_L       0x3F
#define ACCEL37_REG_TEMP_ADC_UNDER_THRSH_H      0x40
#define ACCEL37_REG_TEMP_ADC_UNDER_THRSH_L      0x41
#define ACCEL37_REG_TEMP_ADC_TIMER              0x42
#define ACCEL37_REG_AXIS_MASK                   0x43
#define ACCEL37_REG_STATUS_COPY                 0x44
#define ACCEL37_REG_STATUS_2                    0x45
#define ACCEL37_REG_STATUS_3                    0x46
#define ACCEL37_REG_PEDOMETER_STEP_CNT_H        0x47
#define ACCEL37_REG_PEDOMETER_STEP_CNT_L        0x48
#define ACCEL37_REG_PEDOMETER_CTL               0x49
#define ACCEL37_REG_PEDOMETER_THRES_H           0x4A
#define ACCEL37_REG_PEDOMETER_THRES_L           0x4B
#define ACCEL37_REG_PEDOMETER_SENS_H            0x4C
#define ACCEL37_REG_PEDOMETER_SENS_L            0x4D

/*! @} */ // accel37_reg

/**
 * @defgroup accel37_set Accel 37 Registers Settings
 * @brief Settings for registers of Accel 37 Click driver.
 */

/**
 * @addtogroup accel37_set
 * @{
 */

/**
 * @brief Accel 37 STATUS register setting.
 * @details Specified setting for STATUS register of Accel 37 Click driver.
 */
#define ACCEL37_STATUS_ERR_USER_REGS            0x80
#define ACCEL37_STATUS_AWAKE                    0x40
#define ACCEL37_STATUS_INACT                    0x20
#define ACCEL37_STATUS_ACT                      0x10
#define ACCEL37_STATUS_FIFO_OVER_RUN            0x08
#define ACCEL37_STATUS_FIFO_WATER_MARK          0x04
#define ACCEL37_STATUS_FIFO_READY               0x02
#define ACCEL37_STATUS_DATA_READY               0x01

/**
 * @brief Accel 37 FILTER_CTL register setting.
 * @details Specified setting for FILTER_CTL register of Accel 37 Click driver.
 */
#define ACCEL37_FILTER_CTL_RANGE_2G             0x00
#define ACCEL37_FILTER_CTL_RANGE_4G             0x40
#define ACCEL37_FILTER_CTL_RANGE_8G             0x80
#define ACCEL37_FILTER_CTL_RANGE_MASK           0xC0
#define ACCEL37_FILTER_CTL_I2C_HS               0x20
#define ACCEL37_FILTER_CTL_EXT_SAMPLE           0x08
#define ACCEL37_FILTER_CTL_ODR_12_5HZ           0x00
#define ACCEL37_FILTER_CTL_ODR_25HZ             0x01
#define ACCEL37_FILTER_CTL_ODR_50HZ             0x02
#define ACCEL37_FILTER_CTL_ODR_100HZ            0x03
#define ACCEL37_FILTER_CTL_ODR_200HZ            0x04
#define ACCEL37_FILTER_CTL_ODR_400HZ            0x05
#define ACCEL37_FILTER_CTL_ODR_MASK             0x07

/**
 * @brief Accel 37 POWER_CTL register setting.
 * @details Specified setting for POWER_CTL register of Accel 37 Click driver.
 */
#define ACCEL37_POWER_CTL_EXT_CLK               0x40
#define ACCEL37_POWER_CTL_NOISE_NORMAL          0x00
#define ACCEL37_POWER_CTL_NOISE_ULTRA_LOW       0x20
#define ACCEL37_POWER_CTL_NOISE_LOW             0x30
#define ACCEL37_POWER_CTL_NOISE_MASK            0x30
#define ACCEL37_POWER_CTL_WAKEUP                0x08
#define ACCEL37_POWER_CTL_AUTOSLEEP             0x04
#define ACCEL37_POWER_CTL_STANDBY               0x00
#define ACCEL37_POWER_CTL_MEASURE               0x02
#define ACCEL37_POWER_CTL_MEASURE_MASK          0x03

/**
 * @brief Accel 37 TEMP_CTL register setting.
 * @details Specified setting for TEMP_CTL register of Accel 37 Click driver.
 */
#define ACCEL37_TEMP_CTL_NL_COMP_EN             0x80
#define ACCEL37_TEMP_CTL_TEMP_INACT_EN          0x08
#define ACCEL37_TEMP_CTL_TEMP_ACT_EN            0x02
#define ACCEL37_TEMP_CTL_TEMP_EN                0x01

/**
 * @brief Accel 37 soft reset setting.
 * @details Specified setting for soft reset of Accel 37 Click driver.
 */
#define ACCEL37_SOFT_RESET_KEY                  0x52

/**
 * @brief Accel 37 device id setting.
 * @details Specified setting for device id of Accel 37 Click driver.
 */
#define ACCEL37_DEVID_AD                        0xAD
#define ACCEL37_DEVID_MST                       0x1D
#define ACCEL37_PART_ID                         0xF7

/**
 * @brief Accel 37 output data rate setting.
 * @details Specified setting for output data rate of Accel 37 Click driver.
 */
#define ACCEL37_ODR_12_5HZ                      0
#define ACCEL37_ODR_25HZ                        1
#define ACCEL37_ODR_50HZ                        2
#define ACCEL37_ODR_100HZ                       3
#define ACCEL37_ODR_200HZ                       4
#define ACCEL37_ODR_400HZ                       5

/**
 * @brief Accel 37 full scale setting.
 * @details Specified setting for full scale of Accel 37 Click driver.
 */
#define ACCEL37_FS_2G                           0
#define ACCEL37_FS_4G                           1
#define ACCEL37_FS_8G                           2

/**
 * @brief Accel 37 acceleration measurement sensitivity setting.
 * @details Specified setting for acceleration measurement sensitivity of Accel 37 Click driver.
 */
#define ACCEL37_ACCEL_SENS_2G                   4000.0f
#define ACCEL37_ACCEL_SENS_4G                   2000.0f
#define ACCEL37_ACCEL_SENS_8G                   1000.0f

/**
 * @brief Accel 37 temperature conversion to degC setting.
 * @details Specified setting for temperature conversion to degC of Accel 37 Click driver.
 * @note This sensor measures the internal chip temperature, not ambient temperature.
 */
#define ACCEL37_TEMP_SENS                       53.0f
#define ACCEL37_TEMP_BIAS                    ( -160 )
#define ACCEL37_TEMP_REF_C                      25.0f

/**
 * @brief Accel 37 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 37 Click driver.
 */
#define ACCEL37_DEVICE_ADDRESS_ASEL_GND         0x1D
#define ACCEL37_DEVICE_ADDRESS_ASEL_VCC         0x53
#define ACCEL37_DEVICE_ADDRESS                  ACCEL37_DEVICE_ADDRESS_ASEL_GND

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel37_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL37_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL37_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel37_set

/**
 * @defgroup accel37_map Accel 37 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 37 Click driver.
 */

/**
 * @addtogroup accel37_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 37 Click to the selected MikroBUS.
 */
#define ACCEL37_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel37_map
/*! @} */ // accel37

/**
 * @brief Accel 37 Click driver selector.
 * @details Selects target driver interface of Accel 37 Click driver.
 */
typedef enum
{
    ACCEL37_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ACCEL37_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel37_drv_t;

/**
 * @brief Accel 37 Click driver interface.
 * @details Definition of driver interface of Accel 37 Click driver.
 */
struct accel37_s;
typedef err_t ( *accel37_master_io_t )( struct accel37_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 37 Click context object.
 * @details Context object definition of Accel 37 Click driver.
 */
typedef struct accel37_s
{
    digital_in_t int_pin;                 /**< Interrupt pin (unused). */

    i2c_master_t i2c;                     /**< I2C driver object. */
    spi_master_t spi;                     /**< SPI driver object. */

    uint8_t      slave_address;           /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;             /**< Chip select pin descriptor (used for SPI driver). */
    accel37_drv_t drv_sel;                /**< Master driver interface selector. */

    accel37_master_io_t write_f;          /**< Master write function. */
    accel37_master_io_t read_f;           /**< Master read function. */
    
    float accel_sens;                     /**< Accel sensitivity setting. */

} accel37_t;

/**
 * @brief Accel 37 Click configuration object.
 * @details Configuration object definition of Accel 37 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;         /**< Interrupt pin (unused). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel37_drv_t drv_sel;      /**< Master driver interface selector. */

} accel37_cfg_t;

/**
 * @brief Accel 37 Click axes data structure.
 * @details Axes data object definition of Accel 37 Click driver.
 */
typedef struct
{
    float x;                    /**< X axis. */
    float y;                    /**< Y axis. */
    float z;                    /**< Z axis. */

} accel37_axes_t;

/**
 * @brief Accel 37 Click data structure.
 * @details Data object definition of Accel 37 Click driver.
 */
typedef struct
{
    accel37_axes_t accel;       /**< Accel data. */
    float temperature;          /**< Temperature data. */
  
} accel37_data_t;

/**
 * @brief Accel 37 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL37_OK = 0,
    ACCEL37_ERROR = -1,
    ACCEL37_DATA_NOT_READY = -2

} accel37_return_value_t;

/*!
 * @addtogroup accel37 Accel 37 Click Driver
 * @brief API for configuring and manipulating Accel 37 Click driver.
 * @{
 */

/**
 * @brief Accel 37 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel37_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel37_cfg_setup ( accel37_cfg_t *cfg );

/**
 * @brief Accel 37 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel37_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel37_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel37_drv_interface_sel ( accel37_cfg_t *cfg, accel37_drv_t drv_sel );

/**
 * @brief Accel 37 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel37_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_init ( accel37_t *ctx, accel37_cfg_t *cfg );

/**
 * @brief Accel 37 default configuration function.
 * @details This function executes a default configuration of Accel 37
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel37_default_cfg ( accel37_t *ctx );

/**
 * @brief Accel 37 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_generic_write ( accel37_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 37 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_generic_read ( accel37_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 37 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_write_reg ( accel37_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 37 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data read from the register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_read_reg ( accel37_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 37 check communication function.
 * @details This function checks device communication by reading and verifying
 * the DEVID_AD and DEVID_MST registers.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_check_communication ( accel37_t *ctx );

/**
 * @brief Accel 37 reset device function.
 * @details This function performs a soft reset.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_reset_device ( accel37_t *ctx );

/**
 * @brief Accel 37 set full-scale range function.
 * @details This function sets FSR by modifying bits[7:6] of FILTER_CTL register (0x2C).
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] fsr : Full-scale range value, see ACCEL37_FS_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid FSR or Error.
 * See #err_t definition for detailed explanation.
 * @note This function can be called only if in standby mode.
 */
err_t accel37_set_fsr ( accel37_t *ctx, uint8_t fsr );

/**
 * @brief Accel 37 set output data rate function.
 * @details This function sets the ODR by modifying bits[2:0] of FILTER_CTL register (0x2C).
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] odr : ODR selection. See ACCEL37_ODR_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_set_odr ( accel37_t *ctx, uint8_t odr );

/**
 * @brief Accel 37 check data ready function.
 * @details This function checks whether new acceleration data is available.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Not ready.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_data_ready ( accel37_t *ctx );

/**
 * @brief Accel 37 get acceleration function.
 * @details This function reads and converts the X, Y, Z acceleration data.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[out] accel : Acceleration axes structure.
 * See #accel37_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Data not ready.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_get_accel ( accel37_t *ctx, accel37_axes_t *accel );

/**
 * @brief Accel 37 get temperature function.
 * @details This function reads and calculates the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[out] temp : Pointer to store temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Data not ready.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_get_temp ( accel37_t *ctx, float *temp );

/**
 * @brief Accel 37 get all sensor data function.
 * @details This function retrieves acceleration and temperature data from the device.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[out] data_out : Output data structure containing both acceleration and temperature data.
 * See #accel37_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Accel data not ready.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel37_get_data ( accel37_t *ctx, accel37_data_t *data_out );

/**
 * @brief Accel 37 get INT_PIN function.
 * @details This function returns the logic state of the INT_PIN.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel37_get_int_pin ( accel37_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL37_H

/*! @} */ // accel37

// ------------------------------------------------------------------------ END
