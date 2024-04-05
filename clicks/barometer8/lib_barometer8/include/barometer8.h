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
 * @file barometer8.h
 * @brief This file contains API for Barometer 8 Click Driver.
 */

#ifndef BAROMETER8_H
#define BAROMETER8_H

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
 * @addtogroup barometer8 Barometer 8 Click Driver
 * @brief API for configuring and manipulating Barometer 8 Click driver.
 * @{
 */

/**
 * @defgroup barometer8_reg Barometer 8 Registers List
 * @brief List of registers of Barometer 8 Click driver.
 */

/**
 * @addtogroup barometer8_reg
 * @{
 */

/**
 * @brief Barometer 8 registers list.
 * @details Specified registers list of Barometer 8 Click driver.
 */
#define BAROMETER8_REG_INTERRUPT_CFG            0x0B
#define BAROMETER8_REG_THS_P_L                  0x0C
#define BAROMETER8_REG_THS_P_H                  0x0D
#define BAROMETER8_REG_IF_CTRL                  0x0E
#define BAROMETER8_REG_WHO_AM_I                 0x0F
#define BAROMETER8_REG_CTRL_REG1                0x10
#define BAROMETER8_REG_CTRL_REG2                0x11
#define BAROMETER8_REG_CTRL_REG3                0x12
#define BAROMETER8_REG_FIFO_CTRL                0x14
#define BAROMETER8_REG_FIFO_WTM                 0x15
#define BAROMETER8_REG_REF_P_L                  0x16
#define BAROMETER8_REG_REF_P_H                  0x17
#define BAROMETER8_REG_I3C_IF_CTRL              0x19
#define BAROMETER8_REG_RPDS_L                   0x1A
#define BAROMETER8_REG_RPDS_H                   0x1B
#define BAROMETER8_REG_INT_SOURCE               0x24
#define BAROMETER8_REG_FIFO_STATUS1             0x25
#define BAROMETER8_REG_FIFO_STATUS2             0x26
#define BAROMETER8_REG_STATUS                   0x27
#define BAROMETER8_REG_PRESSURE_OUT_XL          0x28
#define BAROMETER8_REG_PRESSURE_OUT_L           0x29
#define BAROMETER8_REG_PRESSURE_OUT_H           0x2A
#define BAROMETER8_REG_TEMP_OUT_L               0x2B
#define BAROMETER8_REG_TEMP_OUT_H               0x2C
#define BAROMETER8_REG_FIFO_DATA_OUT_PRESS_XL   0x78
#define BAROMETER8_REG_FIFO_DATA_OUT_PRESS_L    0x79
#define BAROMETER8_REG_FIFO_DATA_OUT_PRESS_H    0x7A

/*! @} */ // barometer8_reg

/**
 * @defgroup barometer8_set Barometer 8 Registers Settings
 * @brief Settings for registers of Barometer 8 Click driver.
 */

/**
 * @addtogroup barometer8_set
 * @{
 */

/**
 * @brief Barometer 8 IF_CTRL register settings.
 * @details Specified settings for IF_CTRL register of Barometer 8 Click driver.
 */
#define BAROMETER8_DISABLE_I2C_AND_I3C          0x40
#define BAROMETER8_ENABLE_SPI_READ              0x20
#define BAROMETER8_SDA_PULL_UP                  0x10
#define BAROMETER8_CS_PULL_UP_DISC              0x02

/**
 * @brief Barometer 8 WHO_AM_I register value.
 * @details Specified value of WHO_AM_I register of Barometer 8 Click driver.
 */
#define BAROMETER8_WHO_AM_I                     0xB4

/**
 * @brief Barometer 8 CTRL_REG1 register settings.
 * @details Specified settings for CTRL_REG1 register of Barometer 8 Click driver.
 */
#define BAROMETER8_ODR_PD_OR_ONE_SHOT           0x00
#define BAROMETER8_ODR_1HZ                      0x08
#define BAROMETER8_ODR_4HZ                      0x10
#define BAROMETER8_ODR_10HZ                     0x18
#define BAROMETER8_ODR_25HZ                     0x20
#define BAROMETER8_ODR_50HZ                     0x28
#define BAROMETER8_ODR_75HZ                     0x30
#define BAROMETER8_ODR_100HZ                    0x38
#define BAROMETER8_ODR_200HZ                    0x40
#define BAROMETER8_ODR_BIT_MASK                 0x78
#define BAROMETER8_AVG_4                        0x00
#define BAROMETER8_AVG_8                        0x01
#define BAROMETER8_AVG_16                       0x02
#define BAROMETER8_AVG_32                       0x03
#define BAROMETER8_AVG_64                       0x04
#define BAROMETER8_AVG_128                      0x05
#define BAROMETER8_AVG_512                      0x07
#define BAROMETER8_AVG_BIT_MASK                 0x07

/**
 * @brief Barometer 8 CTRL_REG2 register settings.
 * @details Specified settings for CTRL_REG2 register of Barometer 8 Click driver.
 */
#define BAROMETER8_BOOT_NORMAL                  0x00
#define BAROMETER8_REBOOT_MEMORY                0x80
#define BAROMETER8_FS_MODE_1                    0x00
#define BAROMETER8_FS_MODE_2                    0x40
#define BAROMETER8_LFPF_CFG_ODR_4               0x00
#define BAROMETER8_LFPF_CFG_ODR_9               0x20
#define BAROMETER8_DISABLE_LPFP                 0x00
#define BAROMETER8_ENABLE_LPFP                  0x10
#define BAROMETER8_BDU_CONTINUOUS               0x00
#define BAROMETER8_BDU_MSB_LSB_READ             0x08
#define BAROMETER8_SWRESET                      0x04
#define BAROMETER8_ONESHOT_IDLE                 0x00
#define BAROMETER8_ONESHOT_NEW_DATA             0x01

/**
 * @brief Barometer 8 STATUS register settings.
 * @details Specified settings for STATUS register of Barometer 8 Click driver.
 */
#define BAROMETER8_STATUS_T_OR                  0x20
#define BAROMETER8_STATUS_P_OR                  0x10
#define BAROMETER8_STATUS_T_DA                  0x02
#define BAROMETER8_STATUS_P_DA                  0x01

/**
 * @brief Barometer 8 calculation values.
 * @details Specified calculation values of Barometer 8 Click driver.
 */
#define BAROMETER8_PRESSURE_FS_MODE_1_RES       4096.0
#define BAROMETER8_PRESSURE_FS_MODE_2_RES       2048.0
#define BAROMETER8_TEMPERATURE_RES              0.01

/**
 * @brief Barometer 8 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 8 Click driver.
 */
#define BAROMETER8_SET_DEVICE_ADDRESS           0x5C

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b barometer8_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BAROMETER8_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define BAROMETER8_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // barometer8_set

/**
 * @defgroup barometer8_map Barometer 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 8 Click driver.
 */

/**
 * @addtogroup barometer8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 8 Click to the selected MikroBUS.
 */
#define BAROMETER8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // barometer8_map
/*! @} */ // barometer8

/**
 * @brief Barometer 8 Click driver selector.
 * @details Selects target driver interface of Barometer 8 Click driver.
 */
typedef enum
{
    BAROMETER8_DRV_SEL_SPI,             /**< SPI driver descriptor. */
    BAROMETER8_DRV_SEL_I2C              /**< I2C driver descriptor. */

} barometer8_drv_t;

/**
 * @brief Barometer 8 Click driver interface.
 * @details Definition of driver interface of Barometer 8 Click driver.
 */
typedef err_t ( *barometer8_master_io_t )( struct barometer8_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Barometer 8 Click context object.
 * @details Context object definition of Barometer 8 Click driver.
 */
typedef struct barometer8_s
{
    i2c_master_t  i2c;                  /**< I2C driver object. */
    spi_master_t  spi;                  /**< SPI driver object. */

    uint8_t     slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;            /**< Chip select pin descriptor (used for SPI driver). */
    barometer8_drv_t  drv_sel;          /**< Master driver interface selector. */

    barometer8_master_io_t  write_f;    /**< Master write function. */
    barometer8_master_io_t  read_f;     /**< Master read function. */
    
    uint8_t ctrl_reg2;                  /**< Control register 2 settings. Used for pressure full-scale mode resolution. */

} barometer8_t;

/**
 * @brief Barometer 8 Click configuration object.
 * @details Configuration object definition of Barometer 8 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                    /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                     /**< Chip select pin descriptor for SPI driver. */

    uint32_t  i2c_speed;                /**< I2C serial speed. */
    uint8_t   i2c_address;              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    barometer8_drv_t  drv_sel;          /**< Master driver interface selector. */

} barometer8_cfg_t;

/**
 * @brief Barometer 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER8_OK = 0,
    BAROMETER8_ERROR = -1

} barometer8_return_value_t;

/*!
 * @addtogroup barometer8 Barometer 8 Click Driver
 * @brief API for configuring and manipulating Barometer 8 Click driver.
 * @{
 */

/**
 * @brief Barometer 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer8_cfg_setup ( barometer8_cfg_t *cfg );

/**
 * @brief Barometer 8 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #barometer8_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #barometer8_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void barometer8_drv_interface_selection ( barometer8_cfg_t *cfg, barometer8_drv_t drv_sel );

/**
 * @brief Barometer 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer8_init ( barometer8_t *ctx, barometer8_cfg_t *cfg );

/**
 * @brief Barometer 8 default configuration function.
 * @details This function executes a default configuration of Barometer 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer8_default_cfg ( barometer8_t *ctx );

/**
 * @brief Barometer 8 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer8_generic_write ( barometer8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 8 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer8_generic_read ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 8 write register function.
 * @details This function writes a desired data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer8_write_register ( barometer8_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Barometer 8 read register function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer8_read_register ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Barometer 8 check communication function.
 * @details This function checks the communication by reading and verifying the WHO_AM_I register value.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer8_check_communication ( barometer8_t *ctx );

/**
 * @brief Barometer 8 software reset function.
 * @details This function performs the software reset command.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer8_software_reset ( barometer8_t *ctx );

/**
 * @brief Barometer 8 read data function.
 * @details This function reads the pressure and temperature raw data and converts them to mBar and Celsius.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[out] pressure : Pressure in mBar.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer8_read_data ( barometer8_t *ctx, float *pressure, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER8_H

/*! @} */ // barometer8

// ------------------------------------------------------------------------ END
