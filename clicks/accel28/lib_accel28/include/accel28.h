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
 * @file accel28.h
 * @brief This file contains API for Accel 28 Click Driver.
 */

#ifndef ACCEL28_H
#define ACCEL28_H

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
 * @addtogroup accel28 Accel 28 Click Driver
 * @brief API for configuring and manipulating Accel 28 Click driver.
 * @{
 */

/**
 * @defgroup accel28_reg Accel 28 Registers List
 * @brief List of registers of Accel 28 Click driver.
 */

/**
 * @addtogroup accel28_reg
 * @{
 */

/**
 * @brief Accel 28 description register.
 * @details Specified register for description of Accel 28 Click driver.
 */
#define ACCEL28_REG_TEMP_L                              0x0B
#define ACCEL28_REG_TEMP_H                              0x0C
#define ACCEL28_REG_WHO_AM_I                            0x0F
#define ACCEL28_REG_ACT_THS                             0x1E
#define ACCEL28_REG_ACT_DUS                             0x1F
#define ACCEL28_REG_CTRL1                               0x20
#define ACCEL28_REG_CTRL2                               0x21
#define ACCEL28_REG_CTRL3                               0x22
#define ACCEL28_REG_CTRL4                               0x23
#define ACCEL28_REG_CTRL5                               0x24
#define ACCEL28_REG_CTRL6                               0x25
#define ACCEL28_REG_CTRL7                               0x26
#define ACCEL28_REG_STATUS                              0x27
#define ACCEL28_REG_OUT_X_L                             0x28
#define ACCEL28_REG_OUT_X_H                             0x29
#define ACCEL28_REG_OUT_Y_L                             0x2A
#define ACCEL28_REG_OUT_Y_H                             0x2B
#define ACCEL28_REG_OUT_Z_L                             0x2C
#define ACCEL28_REG_OUT_Z_H                             0x2D
#define ACCEL28_REG_FIFO_CTRL                           0x2E
#define ACCEL28_REG_FIFO_SRC                            0x2F
#define ACCEL28_REG_IG_CFG1                             0x30
#define ACCEL28_REG_IG_SRC1                             0x31
#define ACCEL28_REG_IG_THS_X1                           0x32
#define ACCEL28_REG_IG_THS_Y1                           0x33
#define ACCEL28_REG_IG_THS_Z1                           0x34
#define ACCEL28_REG_IG_DUR1                             0x35
#define ACCEL28_REG_IG_CFG2                             0x36
#define ACCEL28_REG_IG_SRC2                             0x37
#define ACCEL28_REG_IG_THS2                             0x38
#define ACCEL28_REG_IG_DUR2                             0x39
#define ACCEL28_REG_XL_REFERENCE                        0x3A
#define ACCEL28_REG_XH_REFERENCE                        0x3B
#define ACCEL28_REG_YL_REFERENCE                        0x3C
#define ACCEL28_REG_YH_REFERENCE                        0x3D
#define ACCEL28_REG_ZL_REFERENCE                        0x3E
#define ACCEL28_REG_ZH_REFERENCE                        0x3F

/*! @} */ // accel28_reg

/**
 * @defgroup accel28_set Accel 28 Registers Settings
 * @brief Settings for registers of Accel 28 Click driver.
 */

/**
 * @addtogroup accel28_set
 * @{
 */

/**
 * @brief Accel 28 description setting.
 * @details Specified setting for description of Accel 28 Click driver.
 */
#define ACCEL28_WHO_AM_I_VALUE                          0x41

/**
 * @brief Accel 28 CTRL1 register setting.
 * @details Specified CTRL1 register setting for description of 
 * Accel 28 Click driver.
 */
#define ACCEL28_CTRL1_X_AXIS_ENABLE                     0x01
#define ACCEL28_CTRL1_Y_AXIS_ENABLE                     0x02
#define ACCEL28_CTRL1_Z_AXIS_ENABLE                     0x04
#define ACCEL28_CTRL1_BLOCK_DATA_UPATE_EN               0x08
#define ACCEL28_CTRL1_ODR_POWER_DOWN                    0x00
#define ACCEL28_CTRL1_ODR_10HZ                          0x10
#define ACCEL28_CTRL1_ODR_50HZ                          0x20
#define ACCEL28_CTRL1_ODR_100HZ                         0x30
#define ACCEL28_CTRL1_ODR_200HZ                         0x40
#define ACCEL28_CTRL1_ODR_400HZ                         0x50
#define ACCEL28_CTRL1_ODR_800HZ                         0x60
#define ACCEL28_CTRL1_ODR_NA                            0x70
#define ACCEL28_CTRL1_HR_MODE                           0x80

/**
 * @brief Accel 28 CTRL2 register setting.
 * @details Specified CTRL2 register setting for description of Accel 28 Click driver.
 */
#define ACCEL28_CTRL2_HP_ENABLE_INT2                    0x01
#define ACCEL28_CTRL2_HP_ENABLE_INT1                    0x02
#define ACCEL28_CTRL2_FDS_ENABLE                        0x04
#define ACCEL28_CTRL2_HPM_NORMAL_MODE                   0x00
#define ACCEL28_CTRL2_HPM_REF_SIGNAL_FILTERING          0x08
#define ACCEL28_CTRL2_HPM_FREQ_DEV_50                   0x00
#define ACCEL28_CTRL2_HPM_FREQ_DEV_100                  0x20
#define ACCEL28_CTRL2_HPM_FREQ_DEV_9                    0x40
#define ACCEL28_CTRL2_HPM_FREQ_DEV_400                  0x60 

/**
 * @brief Accel 28 CTRL3 register setting.
 * @details Specified CTRL3 register setting for description of 
 * Accel 28 Click driver.
 */
#define ACCEL28_CTRL3_INT1_DRDY_EN                      0x01 
#define ACCEL28_CTRL3_INT1_FTH                          0x02 
#define ACCEL28_CTRL3_INT1_OVR                          0x04 
#define ACCEL28_CTRL3_INT1_IG1                          0x08 
#define ACCEL28_CTRL3_INT1_IG2                          0x10 
#define ACCEL28_CTRL3_INT1_INACT_EN                     0x20 
#define ACCEL28_CTRL3_STOP_FTH                          0x40 
#define ACCEL28_CTRL3_FIFO_EN                           0x80 

/**
 * @brief Accel 28 CTRL4 register setting.
 * @details Specified CTRL4 register setting for description of 
 * Accel 28 Click driver.
 */
#define ACCEL28_CTRL4_SPI_MODE_3_WIRE                   0x01 
#define ACCEL28_CTRL4_SPI_MODE_4_WIRE                   0x00 
#define ACCEL28_CTRL4_I2C_DISABLED                      0x02 
#define ACCEL28_CTRL4_I2C_ENABLED                       0x00 
#define ACCEL28_CTRL4_ADD_INC_ENABLED                   0x04 
#define ACCEL28_CTRL4_BW_SCALE_ODR                      0x00 
#define ACCEL28_CTRL4_BW_SCALE_BW                       0x08 
#define ACCEL28_CTRL4_FS_2G                             0x00 
#define ACCEL28_CTRL4_FS_4G                             0x20 
#define ACCEL28_CTRL4_FS_8G                             0x30 
#define ACCEL28_CTRL4_FS_MASK                           0x30 
#define ACCEL28_CTRL4_BW_400HZ                          0x00 
#define ACCEL28_CTRL4_BW_200HZ                          0x40 
#define ACCEL28_CTRL4_BW_100HZ                          0x80 
#define ACCEL28_CTRL4_BW_50HZ                           0xC0 

/**
 * @brief Accel 28 CTRL5 register setting.
 * @details Specified CTRL5 register setting for description of 
 * Accel 28 Click driver.
 */
#define ACCEL28_CTRL5_INT_PUSH_PULL                     0x00 
#define ACCEL28_CTRL5_INT_OPEN_DRAIN                    0x01 
#define ACCEL28_CTRL5_INT_ACTIVE_HIGH                   0x00 
#define ACCEL28_CTRL5_INT_ACTIVE_LOW                    0x02 
#define ACCEL28_CTRL5_NORMAL_MODE                       0x00 
#define ACCEL28_CTRL5_POSITIVE_SELF_TEST                0x04
#define ACCEL28_CTRL5_NEGATIVE_SELF_TEST                0x08
#define ACCEL28_CTRL5_DEC_UDATE_OFF                     0x00
#define ACCEL28_CTRL5_DEC_UDATE_2_SAMPLES               0x10
#define ACCEL28_CTRL5_DEC_UDATE_4_SAMPLES               0x20
#define ACCEL28_CTRL5_DEC_UDATE_8_SAMPLES               0x30
#define ACCEL28_CTRL5_SW_RESET                          0x40
#define ACCEL28_CTRL5_DEBUG_MODE                        0x80

/**
 * @brief Accel 28 CTRL6 register setting.
 * @details Specified CTRL6 register setting for description of 
 * Accel 28 Click driver.
 */
#define ACCEL28_CTRL6_INT2_DRDY                         0x01
#define ACCEL28_CTRL6_INT2_FTH                          0x02
#define ACCEL28_CTRL6_INT2_EMPTY                        0x04
#define ACCEL28_CTRL6_INT2_IG1                          0x08
#define ACCEL28_CTRL6_INT2_IG2                          0x10
#define ACCEL28_CTRL6_INT2_BOOT                         0x20
#define ACCEL28_CTRL6_BOOT                              0x80

/**
 * @brief Accel 28 STATUS register setting.
 * @details Specified STATUS register setting for description of 
 * Accel 28 Click driver.
 */
#define ACCEL28_STATUS_X_DATA_AVL                       0x01
#define ACCEL28_STATUS_Y_DATA_AVL                       0x02 
#define ACCEL28_STATUS_Z_DATA_AVL                       0x04 
#define ACCEL28_STATUS_ZYX_DATA_AVL                     0x08 
#define ACCEL28_STATUS_X_DATA_OVERRUN                   0x10
#define ACCEL28_STATUS_Y_DATA_OVERRUN                   0x20 
#define ACCEL28_STATUS_Z_DATA_OVERRUN                   0x40 
#define ACCEL28_STATUS_ZYX_DATA_OVERRUN                 0x80

/**
 * @brief Accel 28 conversion multiplier setting.
 * @details Specified setting for data conversion multiplier of
 * Accel 28 Click driver.
 */
#define ACCEL28_2G_DATA_CONV                            0.061f
#define ACCEL28_4G_DATA_CONV                            0.122f
#define ACCEL28_8G_DATA_CONV                            0.244f

/**
 * @brief Accel 28 pin state setting.
 * @details Specified setting for pin state of
 * Accel 28 Click driver.
 */
#define ACCEL28_PIN_STATE_HIGH                          0x01
#define ACCEL28_PIN_STATE_LOW                           0x00

/**
 * @brief Accel 28 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 28 Click driver.
 */
#define ACCEL28_DEVICE_ADDRESS_0                        0x1E
#define ACCEL28_DEVICE_ADDRESS_1                        0x1D

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel28_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL28_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL28_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel28_set

/**
 * @defgroup accel28_map Accel 28 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 28 Click driver.
 */

/**
 * @addtogroup accel28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 28 Click to the selected MikroBUS.
 */
#define ACCEL28_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel28_map
/*! @} */ // accel28

/**
 * @brief Accel 28 Click driver selector.
 * @details Selects target driver interface of Accel 28 Click driver.
 */
typedef enum
{
    ACCEL28_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ACCEL28_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel28_drv_t;

/**
 * @brief Accel 28 Click driver interface.
 * @details Definition of driver interface of Accel 28 Click driver.
 */
typedef err_t ( *accel28_master_io_t )( struct accel28_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 28 Click context object.
 * @details Context object definition of Accel 28 Click driver.
 */
typedef struct accel28_s
{
    digital_in_t int_pin;           /**< Interrupt pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    accel28_drv_t drv_sel;          /**< Master driver interface selector. */

    accel28_master_io_t write_f;    /**< Master write function. */
    accel28_master_io_t read_f;     /**< Master read function. */

} accel28_t;

/**
 * @brief Accel 28 Click configuration object.
 * @details Configuration object definition of Accel 28 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel28_drv_t drv_sel;                /**< Master driver interface selector. */

} accel28_cfg_t;

/**
 * @brief Accel 28 Click data object.
 * @details Data object definition of Accel 28 Click driver.
 */
typedef struct
{
    float x_data;           /**< X-axis data. */
    float y_data;           /**< Y-axis data. */
    float z_data;           /**< Z-axis data. */
    
} accel28_data_t;

/**
 * @brief Accel 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL28_OK = 0,
    ACCEL28_ERROR = -1

} accel28_return_value_t;

/*!
 * @addtogroup accel28 Accel 28 Click Driver
 * @brief API for configuring and manipulating Accel 28 Click driver.
 * @{
 */

/**
 * @brief Accel 28 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel28_cfg_setup ( accel28_cfg_t *cfg );

/**
 * @brief Accel 28 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel28_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel28_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel28_drv_interface_selection ( accel28_cfg_t *cfg, accel28_drv_t drv_sel );

/**
 * @brief Accel 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel28_init ( accel28_t *ctx, accel28_cfg_t *cfg );

/**
 * @brief Accel 28 default configuration function.
 * @details This function executes a default configuration of Accel 28
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel28_default_cfg ( accel28_t *ctx );

/**
 * @brief Accel 28 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel28_generic_write ( accel28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 28 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel28_generic_read ( accel28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 28 interrupt reading function.
 * @details This function reads the interrupt state data.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @return State of the INT pin.
 * @note None.
 */
uint8_t accel28_get_int_state ( accel28_t *ctx );

/**
 * @brief Accel 28 raw data reading function.
 * @details This function reads the raw accel data.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[out] data_out : Accel data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel28_get_raw_data ( accel28_t *ctx, accel28_data_t *data_out );

/**
 * @brief Accel 28 data reading function.
 * @details This function reads the accel data.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[out] data_out : Accel data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel28_get_data ( accel28_t *ctx, accel28_data_t *data_out );

/**
 * @brief Accel 28 register data writing function.
 * @details This function writes a byte of data into the selected register.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel28_write_reg ( accel28_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 28 register data reading function.
 * @details This function reads a byte of data from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel28_read_reg ( accel28_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 28 SW reset function.
 * @details This function performes software reset.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel28_sw_reset ( accel28_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL28_H

/*! @} */ // accel28

// ------------------------------------------------------------------------ END
