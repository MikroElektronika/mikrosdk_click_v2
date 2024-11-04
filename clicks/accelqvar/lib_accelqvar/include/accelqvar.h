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
 * @file accelqvar.h
 * @brief This file contains API for AccelQvar Click Driver.
 */

#ifndef ACCELQVAR_H
#define ACCELQVAR_H

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
 * @addtogroup accelqvar AccelQvar Click Driver
 * @brief API for configuring and manipulating AccelQvar Click driver.
 * @{
 */

/**
 * @defgroup accelqvar_reg AccelQvar Registers List
 * @brief List of registers of AccelQvar Click driver.
 */

/**
 * @addtogroup accelqvar_reg
 * @{
 */

/**
 * @brief AccelQvar description register.
 * @details Specified register for description of AccelQvar Click driver.
 */
#define ACCELQVAR_REG_PIN_CTRL                             0x0C
#define ACCELQVAR_REG_WAKE_UP_DUR_EXT                      0x0E
#define ACCELQVAR_REG_WHO_AM_I                             0x0F
#define ACCELQVAR_REG_CTRL1                                0x10
#define ACCELQVAR_REG_CTRL2                                0x11
#define ACCELQVAR_REG_CTRL3                                0x12
#define ACCELQVAR_REG_CTRL4                                0x13
#define ACCELQVAR_REG_CTRL5                                0x14
#define ACCELQVAR_REG_FIFO_CTRL                            0x15
#define ACCELQVAR_REG_FIFO_WTM                             0x16
#define ACCELQVAR_REG_INTERRUPT_CFG                        0x17
#define ACCELQVAR_REG_SIXD                                 0x18
#define ACCELQVAR_REG_WAKE_UP_THS                          0x1C
#define ACCELQVAR_REG_WAKE_UP_DUR                          0x1D
#define ACCELQVAR_REG_FREE_FALL                            0x1E
#define ACCELQVAR_REG_MD1_CFG                              0x1F
#define ACCELQVAR_REG_MD2_CFG                              0x20
#define ACCELQVAR_REG_WAKE_UP_SRC                          0x21
#define ACCELQVAR_REG_TAP_SRC                              0x22
#define ACCELQVAR_REG_SIXD_SRC                             0x23
#define ACCELQVAR_REG_ALL_INT_SRC                          0x24
#define ACCELQVAR_REG_STATUS                               0x25
#define ACCELQVAR_REG_FIFO_STATUS1                         0x26
#define ACCELQVAR_REG_FIFO_STATUS2                         0x27
#define ACCELQVAR_REG_OUT_X_L                              0x28
#define ACCELQVAR_REG_OUT_X_H                              0x29
#define ACCELQVAR_REG_OUT_Y_L                              0x2A
#define ACCELQVAR_REG_OUT_Y_H                              0x2B
#define ACCELQVAR_REG_OUT_Z_L                              0x2C
#define ACCELQVAR_REG_OUT_Z_H                              0x2D
#define ACCELQVAR_REG_OUT_T_AH_QVAR_L                      0x2E
#define ACCELQVAR_REG_OUT_T_AH_QVAR_H                      0x2F
#define ACCELQVAR_REG_AH_QVAR_CFG                          0x31
#define ACCELQVAR_REG_SELF_TEST                            0x32
#define ACCELQVAR_REG_I3C_IF_CTRL                          0x33
#define ACCELQVAR_REG_EMB_FUNC_STATUS_MAINPAGE             0x34
#define ACCELQVAR_REG_FSM_STATUS_MAINPAGE                  0x35
#define ACCELQVAR_REG_MLC_STATUS_MAINPAGE                  0x36
#define ACCELQVAR_REG_SLEEP                                0x3D
#define ACCELQVAR_REG_IF_WAKE_UP                           0x3E
#define ACCELQVAR_REG_FUNC_CFG_ACCESS                      0x3F
#define ACCELQVAR_REG_FIFO_DATA_OUT_TAG                    0x40
#define ACCELQVAR_REG_FIFO_DATA_OUT_X_L                    0x41
#define ACCELQVAR_REG_FIFO_DATA_OUT_X_H                    0x42
#define ACCELQVAR_REG_FIFO_DATA_OUT_Y_L                    0x43
#define ACCELQVAR_REG_FIFO_DATA_OUT_Y_H                    0x44
#define ACCELQVAR_REG_FIFO_DATA_OUT_Z_L                    0x45
#define ACCELQVAR_REG_FIFO_DATA_OUT_Z_H                    0x46
#define ACCELQVAR_REG_FIFO_BATCH_DEC                       0x47
#define ACCELQVAR_REG_TAP_CFG0                             0x6F
#define ACCELQVAR_REG_TAP_CFG1                             0x70
#define ACCELQVAR_REG_TAP_CFG2                             0x71
#define ACCELQVAR_REG_TAP_CFG3                             0x72
#define ACCELQVAR_REG_TAP_CFG4                             0x73
#define ACCELQVAR_REG_TAP_CFG5                             0x74
#define ACCELQVAR_REG_TAP_CFG6                             0x75
#define ACCELQVAR_REG_TIMESTAMP0                           0x7A
#define ACCELQVAR_REG_TIMESTAMP1                           0x7B
#define ACCELQVAR_REG_TIMESTAMP2                           0x7C
#define ACCELQVAR_REG_TIMESTAMP3                           0x7D

/*! @} */ // accelqvar_reg

/**
 * @defgroup accelqvar_set AccelQvar Registers Settings
 * @brief Settings for registers of AccelQvar Click driver.
 */

/**
 * @addtogroup accelqvar_set
 * @{
 */

/**
 * @brief AccelQvar device ID data value.
 * @details Device ID data value of AccelQvar Click driver.
 */
#define ACCELQVAR_WHO_AM_I                                 0x47

/**
 * @brief AccelQvar CTRL1 register description bitmask.
 * @details CTRL1 register description bitmask of AccelQvar Click driver.
 */
#define ACCELQVAR_CTRL1_INT1_ON_RES                        0x40
#define ACCELQVAR_CTRL1_SW_RESET                           0x20
#define ACCELQVAR_CTRL1_IF_ADD_INC                         0x10
#define ACCELQVAR_CTRL1_DRDY_PULSED                        0x08
#define ACCELQVAR_CTRL1_WU_X_EN                            0x04
#define ACCELQVAR_CTRL1_WU_Y_EN                            0x02
#define ACCELQVAR_CTRL1_WU_Z_EN                            0x01

/**
 * @brief AccelQvar CTRL2 register description bitmask.
 * @details CTRL2 register description bitmask of AccelQvar Click driver.
 */
#define ACCELQVAR_CTRL2_INT1_BOOT                          0x80
#define ACCELQVAR_CTRL2_INT1_FIFO_FULL                     0x40
#define ACCELQVAR_CTRL2_INT1_FIFO_TH                       0x20
#define ACCELQVAR_CTRL2_INT1_FIFO_OVR                      0x10
#define ACCELQVAR_CTRL2_INT1_DRDY                          0x08

/**
 * @brief AccelQvar CTRL3 register description bitmask.
 * @details CTRL3 register description bitmask of AccelQvar Click driver.
 */
#define ACCELQVAR_CTRL3_INT2_BOOT                          0x80
#define ACCELQVAR_CTRL3_INT2_FIFO_FULL                     0x40
#define ACCELQVAR_CTRL3_INT2_FIFO_TH                       0x20
#define ACCELQVAR_CTRL3_INT2_FIFO_OVR                      0x10
#define ACCELQVAR_CTRL3_INT2_DRDY                          0x08
#define ACCELQVAR_CTRL3_HP_EN                              0x04
#define ACCELQVAR_CTRL3_ST_SIGN_Y                          0x02
#define ACCELQVAR_CTRL3_ST_SIGN_X                          0x01

/**
 * @brief AccelQvar CTRL4 register description bitmask.
 * @details CTRL4 register description bitmask of AccelQvar Click driver.
 */
#define ACCELQVAR_CTRL4_INACT_ODR_25                       0xC0
#define ACCELQVAR_CTRL4_INACT_ODR_3                        0x80
#define ACCELQVAR_CTRL4_INACT_ODR1_6                       0x40
#define ACCELQVAR_CTRL4_INACT_ODR1_STAT                    0x00
#define ACCELQVAR_CTRL4_BDU                                0x20
#define ACCELQVAR_CTRL4_EMB_FUNC_EN                        0x10
#define ACCELQVAR_CTRL4_FIFO_EN                            0x08
#define ACCELQVAR_CTRL4_SOC                                0x02
#define ACCELQVAR_CTRL4_BOOT                               0x01

/**
 * @brief AccelQvar CTRL5 register description bitmask.
 * @details CTRL5 register description bitmask of AccelQvar Click driver.
 */
#define ACCELQVAR_CTRL5_ODR_ONE_SHOT_IFACE                 0xF0
#define ACCELQVAR_CTRL5_ODR_ONE_SHOT_INT2                  0xE0
#define ACCELQVAR_CTRL5_ODR_800_HZ                         0xB0
#define ACCELQVAR_CTRL5_ODR_400_HZ                         0xA0
#define ACCELQVAR_CTRL5_ODR_200_HZ                         0x90
#define ACCELQVAR_CTRL5_ODR_100_HZ                         0x80
#define ACCELQVAR_CTRL5_ODR_50_HZ                          0x70
#define ACCELQVAR_CTRL5_ODR_25_HZ                          0x60
#define ACCELQVAR_CTRL5_ODR_12_5_HZ                        0x50
#define ACCELQVAR_CTRL5_ODR_6_HZ                           0x40
#define ACCELQVAR_CTRL5_ODR_ULP_25_HZ                      0x30
#define ACCELQVAR_CTRL5_ODR_ULP_3_HZ                       0x20
#define ACCELQVAR_CTRL5_ODR_ULP_1_6_HZ                     0x10
#define ACCELQVAR_CTRL5_ODR_PWR_DOWN                       0x00
#define ACCELQVAR_CTRL5_BW_ODR_16                          0x0C
#define ACCELQVAR_CTRL5_BW_ODR_8                           0x08
#define ACCELQVAR_CTRL5_BW_ODR_4                           0x04
#define ACCELQVAR_CTRL5_BW_ODR_2                           0x00
#define ACCELQVAR_CTRL5_FS_16_G                            0x03
#define ACCELQVAR_CTRL5_FS_8_G                             0x02
#define ACCELQVAR_CTRL5_FS_4_G                             0x01
#define ACCELQVAR_CTRL5_FS_2_G                             0x00

/**
 * @brief AccelQvar AH_QVAR_CFG register description bitmask.
 * @details AH_QVAR_CFG register description bitmask of AccelQvar Click driver.
 */
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_EN                   0x80
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_NOTCH_EN             0x40
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_NOTCH_CUTOFF         0x00
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_C_ZIN_75_MOHM        0x0C
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_C_ZIN_310_MOHM       0x08
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_C_ZIN_175_MOHM       0x04
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_C_ZIN_520_MOHM       0x00
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_GAIN_4               0x03
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_GAIN_2               0x02
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_GAIN_1               0x01
#define ACCELQVAR_AH_QVAR_CFG_AH_QVAR_GAIN_0_5             0x00

/**
 * @brief AccelQvar IF_WAKE_UP register description bitmask.
 * @details IF_WAKE_UP register description bitmask of AccelQvar Click driver.
 */
#define ACCELQVAR_IF_WAKE_UP_SOFT_PD                       0x01

/**
 * @brief AccelQvar full scale sensitivity data value.
 * @details Full scale sensitivity data value of AccelQvar Click driver.
 */
#define ACCELQVAR_SENSITIVITY_FS_2G                        0.061f
#define ACCELQVAR_SENSITIVITY_FS_4G                        0.122f
#define ACCELQVAR_SENSITIVITY_FS_8G                        0.244f
#define ACCELQVAR_SENSITIVITY_FS_16G                       0.488f

/**
 * @brief AccelQvar calculation data value.
 * @details Calculation data value of AccelQvar Click driver.
 */
#define ACCELQVAR_QVAR_DIVIDER                             74.4f
#define ACCELQVAR_TEMP_DIVIDER                             355.5f
#define ACCELQVAR_TEMP_ZERO_VAL                            25.0f

/**
 * @brief AccelQvar device address setting.
 * @details Specified setting for device slave address selection of
 * AccelQvar Click driver.
 */
#define ACCELQVAR_DEVICE_ADDRESS_GND                       0x18
#define ACCELQVAR_DEVICE_ADDRESS_VCC                       0x19

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accelqvar_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCELQVAR_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ACCELQVAR_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accelqvar_set

/**
 * @defgroup accelqvar_map AccelQvar MikroBUS Map
 * @brief MikroBUS pin mapping of AccelQvar Click driver.
 */

/**
 * @addtogroup accelqvar_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AccelQvar Click to the selected MikroBUS.
 */
#define ACCELQVAR_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.it1  = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.it2  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accelqvar_map
/*! @} */ // accelqvar

/**
 * @brief AccelQvar Click driver selector.
 * @details Selects target driver interface of AccelQvar Click driver.
 */
typedef enum
{
    ACCELQVAR_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ACCELQVAR_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accelqvar_drv_t;

/**
 * @brief AccelQvar Click driver interface.
 * @details Definition of driver interface of AccelQvar Click driver.
 */
struct accelqvar_s;
typedef err_t ( *accelqvar_master_io_t )( struct accelqvar_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief AccelQvar Click context object.
 * @details Context object definition of AccelQvar Click driver.
 */
typedef struct accelqvar_s
{
    digital_in_t it1;    /**< Interrupt pin 1. */
    digital_in_t it2;    /**< Interrupt pin 2. */

    i2c_master_t i2c;    /**< I2C driver object. */
    spi_master_t spi;    /**< SPI driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
    accelqvar_drv_t drv_sel;       /**< Master driver interface selector. */

    accelqvar_master_io_t write_f;    /**< Master write function. */
    accelqvar_master_io_t read_f;     /**< Master read function. */

    float sensitivity;

} accelqvar_t;

/**
 * @brief AccelQvar Click configuration object.
 * @details Configuration object definition of AccelQvar Click driver.
 */
typedef struct
{
    pin_name_t scl;     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t it1;     /**< Interrupt pin 1. */
    pin_name_t it2;     /**< Interrupt pin 2. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accelqvar_drv_t drv_sel;    /**< Master driver interface selector. */

} accelqvar_cfg_t;

/**
 * @brief AccelQvar Click axes data.
 * @details Axes data object definition of AccelQvar Click driver.
 */
typedef struct
{
    float x;    /**< X-axis: convert raw-data into engineering units. */
    float y;    /**< Y-axis: convert raw-data into engineering units. */
    float z;    /**< Z-axis: convert raw-data into engineering units. */

} accelqvar_axes_t;

/**
 * @brief AccelQvar Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCELQVAR_OK = 0,
    ACCELQVAR_ERROR = -1

} accelqvar_return_value_t;

/*!
 * @addtogroup accelqvar AccelQvar Click Driver
 * @brief API for configuring and manipulating AccelQvar Click driver.
 * @{
 */

/**
 * @brief AccelQvar configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accelqvar_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accelqvar_cfg_setup ( accelqvar_cfg_t *cfg );

/**
 * @brief AccelQvar driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accelqvar_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accelqvar_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accelqvar_drv_interface_sel ( accelqvar_cfg_t *cfg, accelqvar_drv_t drv_sel );

/**
 * @brief AccelQvar initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accelqvar_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_init ( accelqvar_t *ctx, accelqvar_cfg_t *cfg );

/**
 * @brief AccelQvar default configuration function.
 * @details This function executes a default configuration of AccelQvar
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accelqvar_default_cfg ( accelqvar_t *ctx );

/**
 * @brief AccelQvar data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_generic_write ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief AccelQvar data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_generic_read ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief AccelQvar get device ID function.
 * @details This function reads the device identification data
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_get_device_id ( accelqvar_t *ctx, uint8_t *device_id );

/**
 * @brief AccelQvar software reset function.
 * @details This function trigger the soft reset sequence
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_sw_reset ( accelqvar_t *ctx );

/**
 * @brief AccelQvar ODR selection function.
 * @details This function is used for the ODR selection
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] odr : ODR selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_set_odr ( accelqvar_t *ctx, uint8_t odr );

/**
 * @brief AccelQvar set full scale function.
 * @details This function sets the full scale data
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] fsr : Full-scale selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_set_fsr ( accelqvar_t *ctx, uint8_t fsr );

/**
 * @brief AccelQvar get the accel sensor axes function.
 * @details This function reads the accelerometer sensor axes data 
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[out] axes : Linear acceleration output data object [mg].
 * See #accelqvar_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_get_axes_data ( accelqvar_t *ctx, accelqvar_axes_t *axes );

/**
 * @brief AccelQvar SPI wake up function.
 * @details This function performs deep power-down to soft power-down when the SPI interface
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_spi_wake_up ( accelqvar_t *ctx );

/**
 * @brief AccelQvar enable QVAR function.
 * @details This function enables the analog hub and Qvar chain
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_en_qvar ( accelqvar_t *ctx );

/**
 * @brief AccelQvar get QVAR data function.
 * @details This function reads the Qvar electrostatic sensor data output
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[out] qvar : Qvar electrostatic sensor data output [mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelqvar_get_qvar_data ( accelqvar_t *ctx, float *qvar );

/**
 * @brief AccelQvar get interrupt 1 function.
 * @details This function get states of the interrupt 1 [AN] pin
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t accelqvar_get_int1 ( accelqvar_t *ctx );

/**
 * @brief AccelQvar get interrupt 2 function.
 * @details This function get states of the interrupt 2 [INT] pin
 * of the LIS2DUXS12, Ultralow-power accelerometer with Qvar, AI, & anti-aliasing
 * on the AccelQvar Click board?.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t accelqvar_get_int2 ( accelqvar_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCELQVAR_H

/*! @} */ // accelqvar

// ------------------------------------------------------------------------ END
