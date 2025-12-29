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
 * @file compass9.h
 * @brief This file contains API for Compass 9 Click Driver.
 */

#ifndef COMPASS9_H
#define COMPASS9_H

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
 * @addtogroup compass9 Compass 9 Click Driver
 * @brief API for configuring and manipulating Compass 9 Click driver.
 * @{
 */

/**
 * @defgroup compass9_reg Compass 9 Registers List
 * @brief List of registers of Compass 9 Click driver.
 */

/**
 * @addtogroup compass9_reg
 * @{
 */

/**
 * @brief Compass 9 register map.
 * @details Specified register map of Compass 9 Click driver.
 */
#define COMPASS9_REG_XOUT0                  0x00
#define COMPASS9_REG_XOUT1                  0x01
#define COMPASS9_REG_YOUT0                  0x02
#define COMPASS9_REG_YOUT1                  0x03
#define COMPASS9_REG_ZOUT0                  0x04
#define COMPASS9_REG_ZOUT1                  0x05
#define COMPASS9_REG_XYZOUT2                0x06
#define COMPASS9_REG_TOUT                   0x07
#define COMPASS9_REG_STATUS                 0x08
#define COMPASS9_REG_CTRL0                  0x09
#define COMPASS9_REG_CTRL1                  0x0A
#define COMPASS9_REG_CTRL2                  0x0B
#define COMPASS9_REG_CTRL3                  0x0C
#define COMPASS9_REG_PRODUCT_ID             0x2F

/*! @} */ // compass9_reg

/**
 * @defgroup compass9_set Compass 9 Registers Settings
 * @brief Settings for registers of Compass 9 Click driver.
 */

/**
 * @addtogroup compass9_set
 * @{
 */

/**
 * @brief Compass 9 STATUS register setting.
 * @details Specified setting for STATUS register of Compass 9 Click driver.
 */
#define COMPASS9_STATUS_OTP_READ_DONE       0x10
#define COMPASS9_STATUS_MEAS_T_DONE         0x02
#define COMPASS9_STATUS_MEAS_M_DONE         0x01

/**
 * @brief Compass 9 CTRL0 register setting.
 * @details Specified setting for CTRL0 register of Compass 9 Click driver.
 */
#define COMPASS9_CTRL0_OTP_READ             0x40
#define COMPASS9_CTRL0_AUTO_SR_EN           0x20
#define COMPASS9_CTRL0_RESET                0x10
#define COMPASS9_CTRL0_SET                  0x08
#define COMPASS9_CTRL0_INT_MEAS_DONE_EN     0x04
#define COMPASS9_CTRL0_TM_T                 0x02
#define COMPASS9_CTRL0_TM_M                 0x01

/**
 * @brief Compass 9 CTRL1 register setting.
 * @details Specified setting for CTRL1 register of Compass 9 Click driver.
 */
#define COMPASS9_CTRL1_SW_RST               0x80
#define COMPASS9_CTRL1_YZ_INHIBIT           0x18
#define COMPASS9_CTRL1_X_INHIBIT            0x04
#define COMPASS9_CTRL1_BW_8_MS              0x00
#define COMPASS9_CTRL1_BW_4_MS              0x01
#define COMPASS9_CTRL1_BW_2_MS              0x02
#define COMPASS9_CTRL1_BW_0_5_MS            0x03
#define COMPASS9_CTRL1_BW_MASK              0x03

/**
 * @brief Compass 9 CTRL2 register setting.
 * @details Specified setting for CTRL2 register of Compass 9 Click driver.
 */
#define COMPASS9_CTRL2_EN_PRD_SET           0x80
#define COMPASS9_CTRL2_PRD_SET_1_SMPL       0x00
#define COMPASS9_CTRL2_PRD_SET_25_SMPL      0x10
#define COMPASS9_CTRL2_PRD_SET_75_SMPL      0x20
#define COMPASS9_CTRL2_PRD_SET_100_SMPL     0x30
#define COMPASS9_CTRL2_PRD_SET_250_SMPL     0x40
#define COMPASS9_CTRL2_PRD_SET_500_SMPL     0x50
#define COMPASS9_CTRL2_PRD_SET_1000_SMPL    0x60
#define COMPASS9_CTRL2_PRD_SET_2000_SMPL    0x70
#define COMPASS9_CTRL2_PRD_SET_MASK         0x70
#define COMPASS9_CTRL2_CMM_EN               0x08
#define COMPASS9_CTRL2_CM_FREQ_OFF          0x00
#define COMPASS9_CTRL2_CM_FREQ_1HZ          0x01
#define COMPASS9_CTRL2_CM_FREQ_10HZ         0x02
#define COMPASS9_CTRL2_CM_FREQ_20HZ         0x03
#define COMPASS9_CTRL2_CM_FREQ_50HZ         0x04
#define COMPASS9_CTRL2_CM_FREQ_100HZ        0x05
#define COMPASS9_CTRL2_CM_FREQ_200HZ        0x06
#define COMPASS9_CTRL2_CM_FREQ_1000HZ       0x07
#define COMPASS9_CTRL2_CM_FREQ_MASK         0x07

/**
 * @brief Compass 9 CTRL3 register setting.
 * @details Specified setting for CTRL3 register of Compass 9 Click driver.
 */
#define COMPASS9_CTRL3_SPI_3W               0x40
#define COMPASS9_CTRL3_ST_ENM               0x04
#define COMPASS9_CTRL3_ST_ENP               0x02

/**
 * @brief Compass 9 data calculation values.
 * @details Specified data calculation values of Compass 9 Click driver.
 */
#define COMPASS9_MAGNETIC_OFFSET            0x020000l
#define COMPASS9_MAGNETIC_COUNTS_PER_G      16384.0
#define COMPASS9_TEMPERATURE_OFFSET         75
#define COMPASS9_TEMPERATURE_RESOLUTION     0.8
#define COMPASS9_TIMEOUT                    2000

/**
 * @brief Compass 9 measurement mode settings.
 * @details Specified measurement mode settings of Compass 9 Click driver.
 */
#define COMPASS9_MEAS_SINGLE_T              0
#define COMPASS9_MEAS_SINGLE_M              1
#define COMPASS9_MEAS_CONTINUOUS_M_1HZ      2
#define COMPASS9_MEAS_CONTINUOUS_M_10HZ     3
#define COMPASS9_MEAS_CONTINUOUS_M_20HZ     4
#define COMPASS9_MEAS_CONTINUOUS_M_50HZ     5
#define COMPASS9_MEAS_CONTINUOUS_M_100HZ    6
#define COMPASS9_MEAS_CONTINUOUS_M_200HZ    7
#define COMPASS9_MEAS_CONTINUOUS_M_1000HZ   8

/**
 * @brief Compass 9 PRODUCT_ID register setting.
 * @details Specified setting for PRODUCT_ID register of Compass 9 Click driver.
 */
#define COMPASS9_PRODUCT_ID                 0x30

/**
 * @brief Compass 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Compass 9 Click driver.
 */
#define COMPASS9_DEVICE_ADDRESS             0x30

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b compass9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define COMPASS9_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define COMPASS9_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // compass9_set

/**
 * @defgroup compass9_map Compass 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Compass 9 Click driver.
 */

/**
 * @addtogroup compass9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Compass 9 Click to the selected MikroBUS.
 */
#define COMPASS9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // compass9_map
/*! @} */ // compass9

/**
 * @brief Compass 9 Click driver selector.
 * @details Selects target driver interface of Compass 9 Click driver.
 */
typedef enum
{
    COMPASS9_DRV_SEL_SPI,           /**< SPI driver descriptor. */
    COMPASS9_DRV_SEL_I2C            /**< I2C driver descriptor. */

} compass9_drv_t;

/**
 * @brief Compass 9 Click driver interface.
 * @details Definition of driver interface of Compass 9 Click driver.
 */
struct compass9_s;
typedef err_t ( *compass9_master_io_t )( struct compass9_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Compass 9 Click context object.
 * @details Context object definition of Compass 9 Click driver.
 */
typedef struct compass9_s
{
    digital_in_t int_pin;           /**< Interrupt pin (active high). */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    compass9_drv_t drv_sel;         /**< Master driver interface selector. */

    compass9_master_io_t write_f;   /**< Master write function. */
    compass9_master_io_t read_f;    /**< Master read function. */

} compass9_t;

/**
 * @brief Compass 9 Click configuration object.
 * @details Configuration object definition of Compass 9 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;             /**< Interrupt pin (active high). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    compass9_drv_t drv_sel;         /**< Master driver interface selector. */

} compass9_cfg_t;

/**
 * @brief Compass 9 magnetic flux data object.
 * @details Magnetic flux data object definition of Compass 9 Click driver.
 */
typedef struct
{
    float x_axis;
    float y_axis;
    float z_axis;

} compass9_magnetic_flux_t;

/**
 * @brief Compass 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COMPASS9_OK = 0,
    COMPASS9_ERROR = -1

} compass9_return_value_t;

/*!
 * @addtogroup compass9 Compass 9 Click Driver
 * @brief API for configuring and manipulating Compass 9 Click driver.
 * @{
 */

/**
 * @brief Compass 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #compass9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void compass9_cfg_setup ( compass9_cfg_t *cfg );

/**
 * @brief Compass 9 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #compass9_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #compass9_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void compass9_drv_interface_sel ( compass9_cfg_t *cfg, compass9_drv_t drv_sel );

/**
 * @brief Compass 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #compass9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_init ( compass9_t *ctx, compass9_cfg_t *cfg );

/**
 * @brief Compass 9 default configuration function.
 * @details This function executes a default configuration of Compass 9
 * Click board.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t compass9_default_cfg ( compass9_t *ctx );

/**
 * @brief Compass 9 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register address.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_write_regs ( compass9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Compass 9 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register address.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_read_regs ( compass9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Compass 9 write register function.
 * @details This function writes a single byte of data to the
 * selected register address.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_write_reg ( compass9_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Compass 9 read register function.
 * @details This function reads a single byte of data from the
 * selected register address.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_read_reg ( compass9_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Compass 9 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t compass9_get_int_pin ( compass9_t *ctx );

/**
 * @brief Compass 9 communication check function.
 * @details This function checks communication by reading the product ID
 * and validating it against the expected value.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_check_communication ( compass9_t *ctx );

/**
 * @brief Compass 9 software reset function.
 * @details This function performs a software reset of the device.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_soft_reset ( compass9_t *ctx );

/**
 * @brief Compass 9 start measurement function.
 * @details This function starts a measurement in a selected operating mode.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] mode : Measurement mode (single or continuous), see COMPASS9_MEAS_x definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_start_measurement ( compass9_t *ctx, uint8_t mode );

/**
 * @brief Compass 9 get magnetic flux function.
 * @details This function reads magnetic flux density values (X, Y, Z axes).
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[out] flux : Magnetic flux density data.
 * See #compass9_magnetic_flux_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_get_magnetic_flux ( compass9_t *ctx, compass9_magnetic_flux_t *flux );

/**
 * @brief Compass 9 get temperature function.
 * @details This function reads the device temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[out] temperature : Output temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t compass9_get_temperature ( compass9_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // COMPASS9_H

/*! @} */ // compass9

// ------------------------------------------------------------------------ END
