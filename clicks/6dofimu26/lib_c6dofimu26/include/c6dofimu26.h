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
 * @file c6dofimu26.h
 * @brief This file contains API for 6DOF IMU 26 Click Driver.
 */

#ifndef C6DOFIMU26_H
#define C6DOFIMU26_H

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
 * @addtogroup c6dofimu26 6DOF IMU 26 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 26 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu26_reg 6DOF IMU 26 Registers List
 * @brief List of registers of 6DOF IMU 26 Click driver.
 */

/**
 * @addtogroup c6dofimu26_reg
 * @{
 */

/**
 * @brief 6DOF IMU 26 register map.
 * @details Specified register map of 6DOF IMU 26 Click driver.
 */
#define C6DOFIMU26_REG_RATE_X1                  0x01
#define C6DOFIMU26_REG_RATE_Y1                  0x02
#define C6DOFIMU26_REG_RATE_Z1                  0x03
#define C6DOFIMU26_REG_ACC_X1                   0x04
#define C6DOFIMU26_REG_ACC_Y1                   0x05
#define C6DOFIMU26_REG_ACC_Z1                   0x06
#define C6DOFIMU26_REG_ACC_X3                   0x07
#define C6DOFIMU26_REG_ACC_Y3                   0x08
#define C6DOFIMU26_REG_ACC_Z3                   0x09
#define C6DOFIMU26_REG_RATE_X2                  0x0A
#define C6DOFIMU26_REG_RATE_Y2                  0x0B
#define C6DOFIMU26_REG_RATE_Z2                  0x0C
#define C6DOFIMU26_REG_ACC_X2                   0x0D
#define C6DOFIMU26_REG_ACC_Y2                   0x0E
#define C6DOFIMU26_REG_ACC_Z2                   0x0F
#define C6DOFIMU26_REG_TEMP                     0x10
#define C6DOFIMU26_REG_RATE_DCNT                0x11
#define C6DOFIMU26_REG_ACC_DCNT                 0x12
#define C6DOFIMU26_REG_FREQ_CNTR                0x13
#define C6DOFIMU26_REG_STAT_SUM                 0x14
#define C6DOFIMU26_REG_STAT_SUM_SAT             0x15
#define C6DOFIMU26_REG_STAT_COM                 0x16
#define C6DOFIMU26_REG_STAT_RATE_COM            0x17
#define C6DOFIMU26_REG_STAT_RATE_X              0x18
#define C6DOFIMU26_REG_STAT_RATE_Y              0x19
#define C6DOFIMU26_REG_STAT_RATE_Z              0x1A
#define C6DOFIMU26_REG_STAT_ACC_X               0x1B
#define C6DOFIMU26_REG_STAT_ACC_Y               0x1C
#define C6DOFIMU26_REG_STAT_ACC_Z               0x1D
#define C6DOFIMU26_REG_STAT_SYNC_ACTIVE         0x1E
#define C6DOFIMU26_REG_STAT_INFO                0x1F
#define C6DOFIMU26_REG_CTRL_FILT_RATE           0x25
#define C6DOFIMU26_REG_CTRL_FILT_ACC12          0x26
#define C6DOFIMU26_REG_CTRL_FILT_ACC3           0x27
#define C6DOFIMU26_REG_CTRL_RATE                0x28
#define C6DOFIMU26_REG_CTRL_ACC12               0x29
#define C6DOFIMU26_REG_CTRL_ACC3                0x2A
#define C6DOFIMU26_REG_CTRL_USER_IF             0x33
#define C6DOFIMU26_REG_CTRL_ST                  0x34
#define C6DOFIMU26_REG_CTRL_MODE                0x35
#define C6DOFIMU26_REG_CTRL_RESET               0x36
#define C6DOFIMU26_REG_SYS_TEST                 0x37
#define C6DOFIMU26_REG_SPARE_1                  0x38
#define C6DOFIMU26_REG_SPARE_2                  0x39
#define C6DOFIMU26_REG_SPARE_3                  0x3A
#define C6DOFIMU26_REG_ASIC_ID                  0x3B
#define C6DOFIMU26_REG_COMP_ID                  0x3C
#define C6DOFIMU26_REG_SN_ID1                   0x3D
#define C6DOFIMU26_REG_SN_ID2                   0x3E
#define C6DOFIMU26_REG_SN_ID3                   0x3F

/*! @} */ // c6dofimu26_reg

/**
 * @defgroup c6dofimu26_set 6DOF IMU 26 Registers Settings
 * @brief Settings for registers of 6DOF IMU 26 Click driver.
 */

/**
 * @addtogroup c6dofimu26_set
 * @{
 */

/**
 * @brief 6DOF IMU 26 SPI48BF frame settings.
 * @details Specified settings for SPI48BF frame of 6DOF IMU 26 Click driver.
 */
#define C6DOFIMU26_D_BIT                        0x80
#define C6DOFIMU26_RW_BIT                       0x20
#define C6DOFIMU26_FT_48_BIT                    0x08

/**
 * @brief 6DOF IMU 26 SYS_TEST register settings.
 * @details Specified settings for SYS_TEST register of 6DOF IMU 26 Click driver.
 */
#define C6DOFIMU26_SYS_TEST                     0x55AA

/**
 * @brief 6DOF IMU 26 CTRL_MODE register settings.
 * @details Specified settings for CTRL_MODE register of 6DOF IMU 26 Click driver.
 */
#define C6DOFIMU26_CTRL_MODE_EOI_CTRL           0x0003
#define C6DOFIMU26_CTRL_MODE_EN_SENSOR          0x0001

/**
 * @brief 6DOF IMU 26 measurement calculation settings.
 * @details Specified settings for measurement calculation of 6DOF IMU 26 Click driver.
 */
#define C6DOFIMU26_ACCEL_LSB_RES                3200
#define C6DOFIMU26_ACCEL_M_S2_TO_G              9.80665
#define C6DOFIMU26_GYRO_LSB_RES                 1600
#define C6DOFIMU26_TEMP_LSB_RES                 100

/**
 * @brief 6DOF IMU 26 address jumper selection.
 * @details Specified settings for address jumper selection of 6DOF IMU 26 Click driver.
 */
#define C6DOFIMU26_ADDRESS_0                    0
#define C6DOFIMU26_ADDRESS_1                    1
#define C6DOFIMU26_ADDRESS_2                    2
#define C6DOFIMU26_ADDRESS_3                    3
#define C6DOFIMU26_ADDRESS                      C6DOFIMU26_ADDRESS_3

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu26_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU26_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU26_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu26_set

/**
 * @defgroup c6dofimu26_map 6DOF IMU 26 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 26 Click driver.
 */

/**
 * @addtogroup c6dofimu26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 26 Click to the selected MikroBUS.
 */
#define C6DOFIMU26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dry = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu26_map
/*! @} */ // c6dofimu26

/**
 * @brief 6DOF IMU 26 Click context object.
 * @details Context object definition of 6DOF IMU 26 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */

    // Input pins
    digital_in_t dry;           /**< Data ready sync pin (active high). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} c6dofimu26_t;

/**
 * @brief 6DOF IMU 26 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 26 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t dry;             /**< Data ready sync pin (active high). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} c6dofimu26_cfg_t;

/**
 * @brief 6DOF IMU 26 Click axes data structure.
 * @details Axes data object definition of 6DOF IMU 26 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} c6dofimu26_axes_t;

/**
 * @brief 6DOF IMU 26 Click data structure.
 * @details Data object definition of 6DOF IMU 26 Click driver.
 */
typedef struct
{
    c6dofimu26_axes_t accel;        /**< Accel data. */
    c6dofimu26_axes_t gyro;         /**< Gyro data. */
    float temperature;              /**< Temperature data. */

} c6dofimu26_data_t;

/**
 * @brief 6DOF IMU 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU26_OK = 0,
    C6DOFIMU26_ERROR = -1

} c6dofimu26_return_value_t;

/*!
 * @addtogroup c6dofimu26 6DOF IMU 26 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 26 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 26 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu26_cfg_setup ( c6dofimu26_cfg_t *cfg );

/**
 * @brief 6DOF IMU 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu26_init ( c6dofimu26_t *ctx, c6dofimu26_cfg_t *cfg );

/**
 * @brief 6DOF IMU 26 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 26
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu26_default_cfg ( c6dofimu26_t *ctx );

/**
 * @brief 6DOF IMU 26 write register function.
 * @details This function writes data to a specified register of the 6DOF IMU 26 device.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c6dofimu26_write_reg ( c6dofimu26_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief 6DOF IMU 26 read register function.
 * @details This function reads data from a specified register of the 6DOF IMU 26 device.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to store the read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c6dofimu26_read_reg ( c6dofimu26_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief 6DOF IMU 26 set reset pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c6dofimu26_set_rst_pin ( c6dofimu26_t *ctx, uint8_t state );

/**
 * @brief 6DOF IMU 26 get data ready pin function.
 * @details This function reads the logic state of the data ready (DRY) pin.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu26_get_dry_pin ( c6dofimu26_t *ctx );

/**
 * @brief 6DOF IMU 26 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c6dofimu26_reset_device ( c6dofimu26_t *ctx );

/**
 * @brief 6DOF IMU 26 check communication function.
 * @details This function checks the communication by writing and reading the system test register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c6dofimu26_check_communication ( c6dofimu26_t *ctx );

/**
 * @brief 6DOF IMU 26 get accelerometer data function.
 * @details This function reads the accelerometer X, Y, and Z axis values.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @param[out] accel : Pointer to store accelerometer values in g.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c6dofimu26_get_accel ( c6dofimu26_t *ctx, c6dofimu26_axes_t *accel );

/**
 * @brief 6DOF IMU 26 get gyroscope data function.
 * @details This function reads the gyroscope X, Y, and Z axis values.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @param[out] gyro : Pointer to store gyroscope values in dps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c6dofimu26_get_gyro ( c6dofimu26_t *ctx, c6dofimu26_axes_t *gyro );

/**
 * @brief 6DOF IMU 26 get temperature function.
 * @details This function reads the temperature sensor value.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @param[out] temp : Pointer to store temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c6dofimu26_get_temp ( c6dofimu26_t *ctx, float *temp );

/**
 * @brief 6DOF IMU 26 get all sensor data function.
 * @details This function reads the accelerometer, gyroscope, and temperature data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu26_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to store sensor data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c6dofimu26_get_data ( c6dofimu26_t *ctx, c6dofimu26_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU26_H

/*! @} */ // c6dofimu26

// ------------------------------------------------------------------------ END
