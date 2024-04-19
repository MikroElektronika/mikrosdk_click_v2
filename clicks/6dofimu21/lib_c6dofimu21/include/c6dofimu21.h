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
 * @file c6dofimu21.h
 * @brief This file contains API for 6DOF IMU 21 Click Driver.
 */

#ifndef C6DOFIMU21_H
#define C6DOFIMU21_H

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
 * @addtogroup c6dofimu21 6DOF IMU 21 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 21 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu21_reg 6DOF IMU 21 Registers List
 * @brief List of registers of 6DOF IMU 21 Click driver.
 */

/**
 * @addtogroup c6dofimu21_reg
 * @{
 */

/**
 * @brief 6DOF IMU 21 description register.
 * @details Specified register for description of 6DOF IMU 21 Click driver.
 */
#define C6DOFIMU21_REG_FIFO_CTRL1               0x06
#define C6DOFIMU21_REG_FIFO_CTRL2               0x07
#define C6DOFIMU21_REG_FIFO_CTRL3               0x08
#define C6DOFIMU21_REG_FIFO_CTRL4               0x09
#define C6DOFIMU21_REG_FIFO_CTRL5               0x0A
#define C6DOFIMU21_REG_DRDY_PULSE_CFG           0x0B
#define C6DOFIMU21_REG_INT0_CTRL                0x0D
#define C6DOFIMU21_REG_INT1_CTRL                0x0E
#define C6DOFIMU21_REG_DEVICE_ID                0x0F
#define C6DOFIMU21_REG_CTRL1_XL                 0x10
#define C6DOFIMU21_REG_CTRL2_G                  0x11
#define C6DOFIMU21_REG_CTRL3_C                  0x12
#define C6DOFIMU21_REG_CTRL4_C                  0x13
#define C6DOFIMU21_REG_CTRL5_C                  0x14
#define C6DOFIMU21_REG_CTRL6_C                  0x15
#define C6DOFIMU21_REG_CTRL7_G                  0x16
#define C6DOFIMU21_REG_CTRL8_XL                 0x17
#define C6DOFIMU21_REG_CTRL9_XL                 0x18
#define C6DOFIMU21_REG_CTRL10_C                 0x19
#define C6DOFIMU21_REG_MASTER_CFG               0x1A
#define C6DOFIMU21_REG_WAKE_UP_SRC              0x1B
#define C6DOFIMU21_REG_TAP_SRC                  0x1C
#define C6DOFIMU21_REG_D6D_SRC                  0x1D
#define C6DOFIMU21_REG_STATUS                   0x1E
#define C6DOFIMU21_REG_T_OUT_L                  0x20
#define C6DOFIMU21_REG_T_OUT_H                  0x21
#define C6DOFIMU21_REG_G_X_OUT_L                0x22
#define C6DOFIMU21_REG_G_X_OUT_H                0x23
#define C6DOFIMU21_REG_G_Y_OUT_L                0x24
#define C6DOFIMU21_REG_G_Y_OUT_H                0x25
#define C6DOFIMU21_REG_G_Z_OUT_L                0x26
#define C6DOFIMU21_REG_G_Z_OUT_H                0x27
#define C6DOFIMU21_REG_XL_X_OUT_L               0x28
#define C6DOFIMU21_REG_XL_X_OUT_H               0x29
#define C6DOFIMU21_REG_XL_Y_OUT_L               0x2A
#define C6DOFIMU21_REG_XL_Y_OUT_H               0x2B
#define C6DOFIMU21_REG_XL_Z_OUT_L               0x2C
#define C6DOFIMU21_REG_XL_Z_OUT_H               0x2D
#define C6DOFIMU21_REG_FIFO_STATUS1             0x3A
#define C6DOFIMU21_REG_FIFO_STATUS2             0x3B
#define C6DOFIMU21_REG_FIFO_STATUS3             0x3C
#define C6DOFIMU21_REG_FIFO_STATUS4             0x3D
#define C6DOFIMU21_REG_FIFO_DATA_OUT_L          0x3E
#define C6DOFIMU21_REG_FIFO_DATA_OUT_H          0x3F
#define C6DOFIMU21_REG_FUNC_SRC1                0x53
#define C6DOFIMU21_REG_TAP_CFG                  0x58
#define C6DOFIMU21_REG_TAP_THS_6D               0x59
#define C6DOFIMU21_REG_INT_DUR2                 0x5A
#define C6DOFIMU21_REG_WAKE_UP_THS              0x5B
#define C6DOFIMU21_REG_WAKE_UP_DUR              0x5C
#define C6DOFIMU21_REG_FREE_FALL                0x5D
#define C6DOFIMU21_REG_MD1_CFG                  0x5E
#define C6DOFIMU21_REG_MD2_CFG                  0x5F
#define C6DOFIMU21_REG_X_OFS_USR                0x73
#define C6DOFIMU21_REG_Y_OFS_USR                0x74
#define C6DOFIMU21_REG_Z_OFS_USR                0x75

/*! @} */ // c6dofimu21_reg

/**
 * @defgroup c6dofimu21_set 6DOF IMU 21 Registers Settings
 * @brief Settings for registers of 6DOF IMU 21 Click driver.
 */

/**
 * @addtogroup c6dofimu21_set
 * @{
 */

/**
 * @brief 6DOF IMU 21 description setting.
 * @details Specified setting for description of 6DOF IMU 21 Click driver.
 */
#define C6DOFIMU21_FULL_SCALE_MASK              0x0C
#define C6DOFIMU21_ACCLE_FS_2G                  0x00
#define C6DOFIMU21_ACCLE_FS_16G                 0x04
#define C6DOFIMU21_ACCLE_FS_4G                  0x08
#define C6DOFIMU21_ACCLE_FS_8G                  0x0C
#define C6DOFIMU21_GYRO_FS_250DPS               0x00
#define C6DOFIMU21_GYRO_FS_500DPS               0x04
#define C6DOFIMU21_GYRO_FS_1000DPS              0x08
#define C6DOFIMU21_GYRO_FS_2000DPS              0x0C

/**
 * @brief 6DOF IMU 21 accel ODR setting.
 * @details Specified setting for accel ODR of 6DOF IMU 21 Click driver.
 */
#define C6DOFIMU21_ODR_XL_POWER_DOWN            0x00
#define C6DOFIMU21_ODR_XL_1_6_HZ                0xB0
#define C6DOFIMU21_ODR_XL_12_5_HZ               0x10
#define C6DOFIMU21_ODR_XL_26_HZ                 0x20
#define C6DOFIMU21_ODR_XL_52_HZ                 0x30
#define C6DOFIMU21_ODR_XL_104_HZ                0x40
#define C6DOFIMU21_ODR_XL_208_HZ                0x50
#define C6DOFIMU21_ODR_XL_416_HZ                0x60
#define C6DOFIMU21_ODR_XL_833_HZ                0x70
#define C6DOFIMU21_ODR_XL_1_66_KHZ              0x80
#define C6DOFIMU21_ODR_XL_3_33_KHZ              0x90
#define C6DOFIMU21_ODR_XL_6_66_KHZ              0xA0

/**
 * @brief 6DOF IMU 21 gyro ODR setting.
 * @details Specified setting for gyro ODR of 6DOF IMU 21 Click driver.
 */
#define C6DOFIMU21_ODR_G_POWER_DOWN             0x00
#define C6DOFIMU21_ODR_G_12_5_HZ                0x10
#define C6DOFIMU21_ODR_G_26_HZ                  0x20
#define C6DOFIMU21_ODR_G_52_HZ                  0x30
#define C6DOFIMU21_ODR_G_104_HZ                 0x40
#define C6DOFIMU21_ODR_G_208_HZ                 0x50
#define C6DOFIMU21_ODR_G_416_HZ                 0x60
#define C6DOFIMU21_ODR_G_833_HZ                 0x70
#define C6DOFIMU21_ODR_G_1_66_KHZ               0x80
#define C6DOFIMU21_ODR_G_3_33_KHZ               0x90
#define C6DOFIMU21_ODR_G_6_66_KHZ               0xA0

/**
 * @brief 6DOF IMU 21 software reset setting.
 * @details Specified setting for software reset of 6DOF IMU 21 Click driver.
 */
#define C6DOFIMU21_SOFTWARE_RESET               0x01


/**
 * @brief 6DOF IMU 21 device ID setting.
 * @details Specified setting for device ID of 6DOF IMU 21 Click driver.
 */
#define C6DOFIMU21_DEVICE_ID                    0x6A

/**
 * @brief 6DOF IMU 21 data conversion factor setting.
 * @details The specified value of data conversion factor of
 * 6DOF IMU 21 Click driver.
 */
#define C6DOFIMU21_ACCEL_2G_CONV_MUL            0.061f
#define C6DOFIMU21_ACCEL_4G_CONV_MUL            0.122f
#define C6DOFIMU21_ACCEL_8G_CONV_MUL            0.244f
#define C6DOFIMU21_ACCEL_16G_CONV_MUL           0.488f
#define C6DOFIMU21_GYRO_250DPS_CONV_MUL         8.75f
#define C6DOFIMU21_GYRO_500DPS_CONV_MUL         17.5f
#define C6DOFIMU21_GYRO_1000DPS_CONV_MUL        35.0f
#define C6DOFIMU21_GYRO_2000DPS_CONV_MUL        70.0f

/**
 * @brief 6DOF IMU 21 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 21 Click driver.
 */
#define C6DOFIMU21_DEVICE_ADDRESS_0             0x6A
#define C6DOFIMU21_DEVICE_ADDRESS_1             0x6B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu21_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU21_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU21_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu21_set

/**
 * @defgroup c6dofimu21_map 6DOF IMU 21 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 21 Click driver.
 */

/**
 * @addtogroup c6dofimu21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 21 Click to the selected MikroBUS.
 */
#define C6DOFIMU21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.i1   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.i0   = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu21_map
/*! @} */ // c6dofimu21

/**
 * @brief 6DOF IMU 21 Click driver selector.
 * @details Selects target driver interface of 6DOF IMU 21 Click driver.
 */
typedef enum
{
    C6DOFIMU21_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    C6DOFIMU21_DRV_SEL_I2C       /**< I2C driver descriptor. */

} c6dofimu21_drv_t;

/**
 * @brief 6DOF IMU 21 Click driver interface.
 * @details Definition of driver interface of 6DOF IMU 21 Click driver.
 */
struct c6dofimu21_s;
typedef err_t ( *c6dofimu21_master_io_t )( struct c6dofimu21_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief 6DOF IMU 21 Click context object.
 * @details Context object definition of 6DOF IMU 21 Click driver.
 */
typedef struct c6dofimu21_s
{
    digital_in_t i1;                    /**< Interrupt 1 pin. */
    digital_in_t i0;                    /**< Interrupt 0 pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    c6dofimu21_drv_t drv_sel;           /**< Master driver interface selector. */

    c6dofimu21_master_io_t write_f;     /**< Master write function. */
    c6dofimu21_master_io_t read_f;      /**< Master read function. */

} c6dofimu21_t;

/**
 * @brief 6DOF IMU 21 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t i1;              /**< Interrupt 1 pin. */
    pin_name_t i0;              /**< Interrupt 0 pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    c6dofimu21_drv_t drv_sel;   /**< Master driver interface selector. */

} c6dofimu21_cfg_t;

/**
 * @brief 6DOF IMU 21 data object.
 * @details Data object definition of 6DOF IMU 21 Click driver.
 */
typedef struct
{
    float x_data;
    float y_data;
    float z_data;

} c6dofimu21_data_t;

/**
 * @brief 6DOF IMU 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU21_OK = 0,
    C6DOFIMU21_ERROR = -1

} c6dofimu21_return_value_t;

/*!
 * @addtogroup c6dofimu21 6DOF IMU 21 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 21 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu21_cfg_setup ( c6dofimu21_cfg_t *cfg );

/**
 * @brief 6DOF IMU 21 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu21_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c6dofimu21_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c6dofimu21_drv_interface_sel ( c6dofimu21_cfg_t *cfg, c6dofimu21_drv_t drv_sel );

/**
 * @brief 6DOF IMU 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu21_init ( c6dofimu21_t *ctx, c6dofimu21_cfg_t *cfg );

/**
 * @brief 6DOF IMU 21 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 21
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu21_default_cfg ( c6dofimu21_t *ctx );

/**
 * @brief 6DOF IMU 21 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu21_generic_write ( c6dofimu21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 21 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu21_generic_read ( c6dofimu21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 21 get int0 pin function.
 * @details This function returns the INT0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu22_get_int0_pin ( c6dofimu21_t *ctx );

/**
 * @brief 6DOF IMU 21 get int1 pin function.
 * @details This function returns the INT1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu22_get_int1_pin ( c6dofimu21_t *ctx );

/**
 * @brief 6DOF IMU 21 data writing function.
 * @details This function writes a data byte into the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu21_write_reg ( c6dofimu21_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 6DOF IMU 21 register data reading function.
 * @details This function reads a data byte from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu21_read_reg ( c6dofimu21_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 6DOF IMU 21 software reset device function.
 * @details This function performs the device software reset.
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu21_software_reset ( c6dofimu21_t *ctx );

/**
 * @brief 6DOF IMU 21 read accel function.
 * @details This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (mg).
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @param[out] accel_data : Output accelerometer data.
 * See #c6dofimu21_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu21_read_accel_data ( c6dofimu21_t *ctx, c6dofimu21_data_t *accel_data );

/**
 * @brief 6DOF IMU 21 read gyro function.
 * @details This function reads the angular rate of X, Y, and Z axis in degrees per second (mdps).
 * @param[in] ctx : Click context object.
 * See #c6dofimu21_t object definition for detailed explanation.
 * @param[out] gyro_data : Output gyro data.
 * See #c6dofimu21_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu21_read_gyro_data ( c6dofimu21_t *ctx, c6dofimu21_data_t *gyro_data );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU21_H

/*! @} */ // c6dofimu21

// ------------------------------------------------------------------------ END
