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
 * @file smartdof3.h
 * @brief This file contains API for Smart DOF 3 Click Driver.
 */

#ifndef SMARTDOF3_H
#define SMARTDOF3_H

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
 * @addtogroup smartdof3 Smart DOF 3 Click Driver
 * @brief API for configuring and manipulating Smart DOF 3 Click driver.
 * @{
 */

/**
 * @defgroup smartdof3_reg Smart DOF 3 Registers List
 * @brief List of registers of Smart DOF 3 Click driver.
 */

/**
 * @addtogroup smartdof3_reg
 * @{
 */

/**
 * @brief Smart DOF 3 description register.
 * @details Specified register for description of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_REG_FUNC_CFG_ACCESS             0x01
#define SMARTDOF3_REG_PIN_CTRL                    0x02
#define SMARTDOF3_REG_DRDY_PULSED_REG             0x0B
#define SMARTDOF3_REG_INT1_CTRL                   0x0D
#define SMARTDOF3_REG_INT2_CTRL                   0x0E
#define SMARTDOF3_REG_WHO_AM_I                    0x0F
#define SMARTDOF3_REG_CTRL1_XL                    0x10
#define SMARTDOF3_REG_CTRL2_G                     0x11
#define SMARTDOF3_REG_CTRL3_C                     0x12
#define SMARTDOF3_REG_CTRL4_C                     0x13
#define SMARTDOF3_REG_CTRL5_C                     0x14
#define SMARTDOF3_REG_CTRL6_C                     0x15
#define SMARTDOF3_REG_CTRL7_G                     0x16
#define SMARTDOF3_REG_CTRL9_C                     0x18
#define SMARTDOF3_REG_CTRL10_C                    0x19
#define SMARTDOF3_REG_ISPU_INT_STATUS0_MP         0x1A
#define SMARTDOF3_REG_ISPU_INT_STATUS1_MP         0x1B
#define SMARTDOF3_REG_ISPU_INT_STATUS2_MP         0x1C
#define SMARTDOF3_REG_ISPU_INT_STATUS3_MP         0x1D
#define SMARTDOF3_REG_STATUS                      0x1E
#define SMARTDOF3_REG_OUT_TEMP_L                  0x20
#define SMARTDOF3_REG_OUT_TEMP_H                  0x21
#define SMARTDOF3_REG_OUTX_L_G                    0x22
#define SMARTDOF3_REG_OUTX_H_G                    0x23
#define SMARTDOF3_REG_OUTY_L_G                    0x24
#define SMARTDOF3_REG_OUTY_H_G                    0x25
#define SMARTDOF3_REG_OUTZ_L_G                    0x26
#define SMARTDOF3_REG_OUTZ_H_G                    0x27
#define SMARTDOF3_REG_OUTX_L_A                    0x28
#define SMARTDOF3_REG_OUTX_H_A                    0x29
#define SMARTDOF3_REG_OUTY_L_A                    0x2A
#define SMARTDOF3_REG_OUTY_H_A                    0x2B
#define SMARTDOF3_REG_OUTZ_L_A                    0x2C
#define SMARTDOF3_REG_OUTZ_H_A                    0x2D
#define SMARTDOF3_REG_STATUS_MASTER_MAINPAGE      0x39
#define SMARTDOF3_REG_TIMESTAMP0                  0x40
#define SMARTDOF3_REG_TIMESTAMP1                  0x41
#define SMARTDOF3_REG_TIMESTAMP2                  0x42
#define SMARTDOF3_REG_TIMESTAMP3                  0x43
#define SMARTDOF3_REG_MD1_CFG                     0x5E
#define SMARTDOF3_REG_MD2_CFG                     0x5F
#define SMARTDOF3_REG_INTERNAL_FREQ_FINE          0x63
#define SMARTDOF3_REG_ISPU_DUMMY_CFG_1_L          0x73
#define SMARTDOF3_REG_ISPU_DUMMY_CFG_1_H          0x74
#define SMARTDOF3_REG_ISPU_DUMMY_CFG_2_L          0x75
#define SMARTDOF3_REG_ISPU_DUMMY_CFG_2_H          0x76
#define SMARTDOF3_REG_ISPU_DUMMY_CFG_3_L          0x77
#define SMARTDOF3_REG_ISPU_DUMMY_CFG_3_H          0x78
#define SMARTDOF3_REG_ISPU_DUMMY_CFG_4_L          0x79
#define SMARTDOF3_REG_ISPU_DUMMY_CFG_4_H          0x7A

/*! @} */ // smartdof3_reg

/**
 * @defgroup smartdof3_set Smart DOF 3 Registers Settings
 * @brief Settings for registers of Smart DOF 3 Click driver.
 */

/**
 * @addtogroup smartdof3_set
 * @{
 */

/**
 * @brief Smart DOF 3 device ID value.
 * @details Specified device ID value of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_DEVICE_ID                       0x22

/**
 * @brief Smart DOF 3 control 3 register value.
 * @details Specified control 3 register value of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_CTRL3_SOFT_RESET                0x01
#define SMARTDOF3_CTRL3_IF_INC_DISABLE            0x00
#define SMARTDOF3_CTRL3_IF_INC_ENABLE             0x04
#define SMARTDOF3_CTRL3_IF_INC_BIT_MASK           0xFB
#define SMARTDOF3_CTRL3_BDU_DISABLE               0x00
#define SMARTDOF3_CTRL3_BDU_ENABLE                0x40
#define SMARTDOF3_CTRL3_BDU_BIT_MASK              0xBF

/**
 * @brief Smart DOF 3 accelerometer ODR configuration setting value.
 * @details Specified accelerometer ODR configuration setting of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_ODR_XL_G_OFF                    0x00
#define SMARTDOF3_ODR_XL_G_12_5_HZ                0x01
#define SMARTDOF3_ODR_XL_G_26_HZ                  0x02
#define SMARTDOF3_ODR_XL_G_52_HZ                  0x03
#define SMARTDOF3_ODR_XL_G_104_HZ                 0x04
#define SMARTDOF3_ODR_XL_G_208_HZ                 0x05
#define SMARTDOF3_ODR_XL_G_416_HZ                 0x06
#define SMARTDOF3_ODR_XL_G_833_HZ                 0x07
#define SMARTDOF3_ODR_XL_G_1667_HZ                0x08
#define SMARTDOF3_ODR_XL_G_3333_HZ                0x09
#define SMARTDOF3_ODR_XL_G_6667_HZ                0x0A
#define SMARTDOF3_ODR_XL_G_BIT_MASK               0x0F

/**
 * @brief Smart DOF 3 accel full-scale selection value.
 * @details Specified accelerometer full-scale selection value of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_XL_FULL_SCALE_2G                0x00
#define SMARTDOF3_XL_FULL_SCALE_16G               0x01
#define SMARTDOF3_XL_FULL_SCALE_4G                0x02
#define SMARTDOF3_XL_FULL_SCALE_8G                0x03
#define SMARTDOF3_XL_FULL_SCALE_BIT_MASK          0x03

/**
 * @brief Smart DOF 3 operating mode value.
 * @details Specified operating mode value of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_OP_MODE_PERFORMANCE_LOW         0x00
#define SMARTDOF3_OP_MODE_PERFORMANCE_HIGH        0x01

/**
 * @brief Smart DOF 3 accel full-scale selection value.
 * @details Specified accelerometer full-scale selection value of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_TIMESTAMP_ENABLE                0x20

/**
 * @brief Smart DOF 3 accel sensitivity data value.
 * @details Specified accelerometer sensitivity value for description of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_ACC_SENSITIVITY_FS_2G           0.061
#define SMARTDOF3_ACC_SENSITIVITY_FS_4G           0.122
#define SMARTDOF3_ACC_SENSITIVITY_FS_8G           0.244
#define SMARTDOF3_ACC_SENSITIVITY_FS_16G          0.488

/**
 * @brief Smart DOF 3 gyro chain full-scale selection value.
 * @details Specified gyroscope chain full-scale selection value of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_GY_FULL_SCALE_125DPS            0x01
#define SMARTDOF3_GY_FULL_SCALE_250DPS            0x00
#define SMARTDOF3_GY_FULL_SCALE_500DPS            0x02
#define SMARTDOF3_GY_FULL_SCALE_1000DPS           0x04
#define SMARTDOF3_GY_FULL_SCALE_2000DPS           0x06
#define SMARTDOF3_GY_FULL_SCALE_BIT_MASK          0x07

/**
 * @brief Smart DOF 3 gyro sensitivity data value.
 * @details Specified gyroscope sensitivity value of Smart DOF 3 Click driver.
 */
#define SMARTDOF3_GYRO_SENSITIVITY_FS_125DPS      0.004375
#define SMARTDOF3_GYRO_SENSITIVITY_FS_250DPS      0.00875
#define SMARTDOF3_GYRO_SENSITIVITY_FS_500DPS      0.0175
#define SMARTDOF3_GYRO_SENSITIVITY_FS_1000DPS     0.035
#define SMARTDOF3_GYRO_SENSITIVITY_FS_2000DPS     0.07

/**
 * @brief Smart DOF 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart DOF 3 Click driver.
 */
#define SMARTDOF3_DEVICE_ADDRESS_GND              0x6A
#define SMARTDOF3_DEVICE_ADDRESS_VCC              0x6B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b smartdof3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SMARTDOF3_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define SMARTDOF3_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // smartdof3_set

/**
 * @defgroup smartdof3_map Smart DOF 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart DOF 3 Click driver.
 */

/**
 * @addtogroup smartdof3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart DOF 3 Click to the selected MikroBUS.
 */
#define SMARTDOF3_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.it2 = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.it1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartdof3_map
/*! @} */ // smartdof3

/**
 * @brief Smart DOF 3 Click driver selector.
 * @details Selects target driver interface of Smart DOF 3 Click driver.
 */
typedef enum
{
    SMARTDOF3_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    SMARTDOF3_DRV_SEL_I2C       /**< I2C driver descriptor. */

} smartdof3_drv_t;

/**
 * @brief Smart DOF 3 Click driver interface.
 * @details Definition of driver interface of Smart DOF 3 Click driver.
 */
typedef err_t ( *smartdof3_master_io_t )( struct smartdof3_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Smart DOF 3 Click context object.
 * @details Context object definition of Smart DOF 3 Click driver.
 */
typedef struct smartdof3_s
{
    digital_in_t it2;    /**< Interrupt 2 pin. */
    digital_in_t it1;    /**< Interrupt 1 pin. */

    i2c_master_t i2c;    /**< I2C driver object. */
    spi_master_t spi;    /**< SPI driver object. */

    uint8_t      slave_address;       /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;         /**< Chip select pin descriptor (used for SPI driver). */
    smartdof3_drv_t drv_sel;          /**< Master driver interface selector. */

    smartdof3_master_io_t write_f;    /**< Master write function. */
    smartdof3_master_io_t read_f;     /**< Master read function. */

} smartdof3_t;

/**
 * @brief Smart DOF 3 Click configuration object.
 * @details Configuration object definition of Smart DOF 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t it2;     /**< Interrupt 1 pin. */
    pin_name_t it1;     /**< Interrupt 1 pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

    smartdof3_drv_t drv_sel;    /**< Master driver interface selector. */

} smartdof3_cfg_t;

/**
 * @brief Smart DOF 3 Click sensor status structure object.
 * @details Sensor status object definition of Smart DOF 3 Click driver.
 */
typedef struct 
{
    uint8_t tda;     /**< Temperature new data available. */
    uint8_t gda;     /**< Gyroscope new data available. */
    uint8_t xlda;    /**< Accelerometer new data available. */

} smartdof3_status_t;

/**
 * @brief Smart DOF 3 Click axis raw data structure object.
 * @details Axis raw data object definition of Smart DOF 3 Click driver.
 */
typedef struct 
{
    int16_t x;    /**< X-axis angular rate output raw data. */
    int16_t y;    /**< Y-axis angular rate output raw data. */
    int16_t z;    /**< Z-axis angular rate output raw data. */

} smartdof3_axis_data_t;

/**
 * @brief Smart DOF 3 Click sensor axes structure object.
 * @details Sensor axes object definition of Smart DOF 3 Click driver.
 */
typedef struct 
{
    float x;    /**< X-axis: convert raw-data into engineering units. */
    float y;    /**< Y-axis: convert raw-data into engineering units. */
    float z;    /**< Z-axis: convert raw-data into engineering units. */

} smartdof3_axis_t;

/**
 * @brief Smart DOF 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTDOF3_OK = 0,
    SMARTDOF3_ERROR = -1

} smartdof3_return_value_t;

/*!
 * @addtogroup smartdof3 Smart DOF 3 Click Driver
 * @brief API for configuring and manipulating Smart DOF 3 Click driver.
 * @{
 */

/**
 * @brief Smart DOF 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartdof3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartdof3_cfg_setup ( smartdof3_cfg_t *cfg );

/**
 * @brief Smart DOF 3 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #smartdof3_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #smartdof3_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void smartdof3_drv_interface_selection ( smartdof3_cfg_t *cfg, smartdof3_drv_t drv_sel );

/**
 * @brief Smart DOF 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartdof3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_init ( smartdof3_t *ctx, smartdof3_cfg_t *cfg );

/**
 * @brief Smart DOF 3 default configuration function.
 * @details This function executes a default configuration of Smart DOF 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartdof3_default_cfg ( smartdof3_t *ctx );

/**
 * @brief Smart DOF 3 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_generic_write ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 3 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_generic_read ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart DOF 3 get device ID function.
 * @details This function reads a device ID value
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_device_id ( smartdof3_t *ctx, uint8_t *device_id );

/**
 * @brief Smart DOF 3 software reset function.
 * @details This function perform a software reset
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_soft_reset ( smartdof3_t *ctx );

/**
 * @brief Smart DOF 3 enable auto-increment function.
 * @details This function enable automatically incremented 
 * during a multiple byte access with a serial interface
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_en_auto_incr ( smartdof3_t *ctx );

/**
 * @brief Smart DOF 3 enable block data update function.
 * @details This function enable block data, 
 * output registers are not updated until LSB and MSB have been read,
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_en_block_data_upd ( smartdof3_t *ctx );

/**
 * @brief Smart DOF 3 sets the operation mode function.
 * @details This function sets the desired operation mode
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] acc_op_mode : Accel operation mode (high-performance enable/disable).
 * @param[in] gyro_op_mode : Gyro operation mode (high-performance enable/disable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_set_op_mode ( smartdof3_t *ctx, uint8_t acc_op_mode, uint8_t gyro_op_mode );

/**
 * @brief Smart DOF 3 sets the accel data rate function.
 * @details This function select the accelerometer data rate
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] data_rate : Accelerometer ODR selection
 *         @li @c  0x00 (SMARTDOF3_ODR_XL_G_OFF)     - Power-down,
 *         @li @c  0x01 (SMARTDOF3_ODR_XL_G_12_5_HZ) -  12.5Hz (low-power, high-performance),
 *         @li @c  0x02 (SMARTDOF3_ODR_XL_G_26_HZ)   -  26Hz (low-power, high-performance),
 *         @li @c  0x03 (SMARTDOF3_ODR_XL_G_52_HZ)   -  52Hz (low-power, high-performance),
 *         @li @c  0x04 (SMARTDOF3_ODR_XL_G_104_HZ)  - 104Hz (low-power, high-performance),
 *         @li @c  0x05 (SMARTDOF3_ODR_XL_G_208_HZ)  - 208Hz (low-power, high-performance),
 *         @li @c  0x06 (SMARTDOF3_ODR_XL_G_416_HZ)  - 416Hz (high-performance),
 *         @li @c  0x07 (SMARTDOF3_ODR_XL_G_833_HZ)  - 833Hz (high-performance),
 *         @li @c  0x08 (SMARTDOF3_ODR_XL_G_1667_HZ) - 1.667Hz (high-performance),
 *         @li @c  0x09 (SMARTDOF3_ODR_XL_G_3333_HZ) - 3.333kHz (high-performance),
 *         @li @c  0x0A (SMARTDOF3_ODR_XL_G_6667_HZ) - 6.667kHz (high-performance).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_set_acc_data_rate ( smartdof3_t *ctx, uint8_t data_rate );

/**
 * @brief Smart DOF 3 sets the accel full-scale range function.
 * @details This function selects the full-scale acceleration range
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] data_scale : Accelerometer full-scale selection
 *         @li @c  0x00 (SMARTDOF3_XL_FULL_SCALE_2g)  -  ±2g,
 *         @li @c  0x01 (SMARTDOF3_XL_FULL_SCALE_16g) - ±16g,
 *         @li @c  0x02 (SMARTDOF3_XL_FULL_SCALE_4g)  -  ±4g,
 *         @li @c  0x03 (SMARTDOF3_XL_FULL_SCALE_8g) -   ±8g.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_set_acc_full_scale ( smartdof3_t *ctx, uint8_t data_scale );

/**
 * @brief Smart DOF 3 get the accel full-scale range function.
 * @details This function reads selected the full-scale acceleration range
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] data_scale : Accelerometer full-scale selection. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_acc_full_scale ( smartdof3_t *ctx, uint8_t *data_scale );

/**
 * @brief Smart DOF 3 get the accel sensitivity function.
 * @details This function reads the accelerometer sensitivity data 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] sensitivity : Accelerometer sensitivity data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_acc_sensitivity ( smartdof3_t *ctx, float *sensitivity );

/**
 * @brief Smart DOF 3 sets the gyro data rate function.
 * @details This function select the gyroscope data rate
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] data_rate : Gyroscope ODR selection
 *         @li @c  0x00 (SMARTDOF3_ODR_XL_G_OFF)     - Power-down,
 *         @li @c  0x01 (SMARTDOF3_ODR_XL_G_12_5_HZ) -  12.5Hz (low-power, high-performance),
 *         @li @c  0x02 (SMARTDOF3_ODR_XL_G_26_HZ)   -  26Hz (low-power, high-performance),
 *         @li @c  0x03 (SMARTDOF3_ODR_XL_G_52_HZ)   -  52Hz (low-power, high-performance),
 *         @li @c  0x04 (SMARTDOF3_ODR_XL_G_104_HZ)  - 104Hz (low-power, high-performance),
 *         @li @c  0x05 (SMARTDOF3_ODR_XL_G_208_HZ)  - 208Hz (low-power, high-performance),
 *         @li @c  0x06 (SMARTDOF3_ODR_XL_G_416_HZ)  - 416Hz (high-performance),
 *         @li @c  0x07 (SMARTDOF3_ODR_XL_G_833_HZ)  - 833Hz (high-performance),
 *         @li @c  0x08 (SMARTDOF3_ODR_XL_G_1667_HZ) - 1.667Hz (high-performance),
 *         @li @c  0x09 (SMARTDOF3_ODR_XL_G_3333_HZ) - 3.333kHz (high-performance),
 *         @li @c  0x0A (SMARTDOF3_ODR_XL_G_6667_HZ) - 6.667kHz (high-performance).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_set_gyro_data_rate ( smartdof3_t *ctx, uint8_t data_rate );

/**
 * @brief Smart DOF 3 sets the gyro full-scale range function.
 * @details This function selects the full-scale gyroscope range
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] data_scale : Gyroscope full-scale selection
 *         @li @c  0x00 (SMARTDOF3_GY_FULL_SCALE_250dps)  -  ±125dps,
 *         @li @c  0x01 (SMARTDOF3_GY_FULL_SCALE_125dps)  -  ±250dps,
 *         @li @c  0x02 (SMARTDOF3_GY_FULL_SCALE_500dps)  -  ±500dps,
 *         @li @c  0x04 (SMARTDOF3_GY_FULL_SCALE_1000dps) - ±1000dps.
 *         @li @c  0x08 (SMARTDOF3_GY_FULL_SCALE_2000dps) - ±2000dps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_set_gyro_full_scale ( smartdof3_t *ctx, uint8_t data_scale );

/**
 * @brief Smart DOF 3 get the gyro full-scale range function.
 * @details This function reads selected the full-scale gyroscope range
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] data_scale : Gyroscope full-scale selection. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_gyro_full_scale ( smartdof3_t *ctx, uint8_t *data_scale );

/**
 * @brief Smart DOF 3 get the status function.
 * @details This function reads status data
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] status : Sensor status object. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_status ( smartdof3_t *ctx, smartdof3_status_t *status );

/**
 * @brief Smart DOF 3 get the gyro sensitivity function.
 * @details This function reads the gyroscope sensitivity data 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] sensitivity : Gyroscope sensitivity data.
 * See smartdof3_status_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_gyro_sensitivity ( smartdof3_t *ctx, float *sensitivity );

/**
 * @brief Smart DOF 3 get the accel data function.
 * @details This function reads the accelerometer raw data 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] acc_axis : Accelerometer raw data object.
 * See smartdof3_axis_data_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_acc_axis_data ( smartdof3_t *ctx, smartdof3_axis_data_t *acc_axis );

/**
 * @brief Smart DOF 3 get the gyro data function.
 * @details This function reads the gyroscope raw data 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] gyro_axis : Gyroscope raw data object.
 * See smartdof3_axis_data_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_gyro_axis_data ( smartdof3_t *ctx, smartdof3_axis_data_t *gyro_axis );

/**
 * @brief Smart DOF 3 get the accel sensor axes function.
 * @details This function reads the accelerometer sensor axes data 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] acc_axis : Linear acceleration output data object (mg).
 * See smartdof3_axis_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_acc_axis ( smartdof3_t *ctx, smartdof3_axis_t *acc_axis );

/**
 * @brief Smart DOF 3 get the gyro sensor axes function.
 * @details This function reads the gyroscope sensor axes data 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] gyro_axis : Angular rate output data object (dps).
 * See smartdof3_axis_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_gyro_axis ( smartdof3_t *ctx, smartdof3_axis_t *gyro_axis );

/**
 * @brief Smart DOF 3 enable the temperature function.
 * @details This function enable the temperature data output
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_enable_temperature ( smartdof3_t *ctx );

/**
 * @brief Smart DOF 3 get the temperature data function.
 * @details This function reads the temperature raw data 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] temp_raw : Temperature raw data (16-bit word in two’s complement).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_temperature_raw ( smartdof3_t *ctx, int16_t *temp_raw );

/**
 * @brief Smart DOF 3 get the temperature function.
 * @details This function reads the temperature data 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[out] temperature : Temperature (degrees Celsius).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof3_get_temperature ( smartdof3_t *ctx, float *temperature );

/**
 * @brief Smart DOF 3 get interrupt 1 function.
 * @details This function gets states of the Interrupt 1 ( IT1-INT ) pin 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t smartdof3_get_in1_pin ( smartdof3_t *ctx );

/**
 * @brief Smart DOF 3 get interrupt 2 function.
 * @details This function gets states of the Interrupt 2 ( IT2-AN ) pin 
 * of the ISM330IS, iNEMO inertial module: always-on 3-axis accelerometer and 3-axis gyroscope
 * on the Smart DOF 3 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t smartdof3_get_in2_pin ( smartdof3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SMARTDOF3_H

/*! @} */ // smartdof3

// ------------------------------------------------------------------------ END
