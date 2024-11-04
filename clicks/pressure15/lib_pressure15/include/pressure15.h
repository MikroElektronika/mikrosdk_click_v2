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
 * @file pressure15.h
 * @brief This file contains API for Pressure 15 Click Driver.
 */

#ifndef PRESSURE15_H
#define PRESSURE15_H

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

/*!
 * @addtogroup pressure15 Pressure 15 Click Driver
 * @brief API for configuring and manipulating Pressure 15 Click driver.
 * @{
 */

/**
 * @defgroup pressure15_reg Pressure 15 Registers List
 * @brief List of registers of Pressure 15 Click driver.
 */

/**
 * @addtogroup pressure15_reg
 * @{
 */

/**
 * @brief Pressure 15 description register.
 * @details Specified register for description of Pressure 15 Click driver.
 */
#define PRESSURE15_REG_INTERRUPT_CFG            0x0B
#define PRESSURE15_REG_THS_P_L                  0x0C
#define PRESSURE15_REG_THS_P_H                  0x0D
#define PRESSURE15_REG_IF_CTRL                  0x0E
#define PRESSURE15_REG_WHO_AM_I                 0x0F
#define PRESSURE15_REG_CTRL_REG1                0x10
#define PRESSURE15_REG_CTRL_REG2                0x11
#define PRESSURE15_REG_CTRL_REG3                0x12
#define PRESSURE15_REG_FIFO_CTRL                0x13
#define PRESSURE15_REG_FIFO_WTM                 0x14
#define PRESSURE15_REG_REF_PL_L                 0x15
#define PRESSURE15_REG_REF_PL_H                 0x16
#define PRESSURE15_REG_RPDS_L                   0x18
#define PRESSURE15_REG_RPDS_H                   0x19
#define PRESSURE15_REG_INT_SOURCE               0x24
#define PRESSURE15_REG_FIFO_STATUS1             0x25
#define PRESSURE15_REG_FIFO_STATUS2             0x26
#define PRESSURE15_REG_STATUS                   0x27
#define PRESSURE15_REG_PRESSURE_OUT_XL          0x28
#define PRESSURE15_REG_PRESSURE_OUT_L           0x29
#define PRESSURE15_REG_PRESSURE_OUT_H           0x2A
#define PRESSURE15_REG_TEMP_OUT_L               0x2B
#define PRESSURE15_REG_TEMP_OUT_H               0x2C
#define PRESSURE15_REG_LPFP_RES                 0x3C
#define PRESSURE15_REG_FIFO_DATA_OUT_PRESS_XL   0x78
#define PRESSURE15_REG_FIFO_DATA_OUT_PRESS_L    0x79
#define PRESSURE15_REG_FIFO_DATA_OUT_PRESS_H    0x7A
#define PRESSURE15_REG_FIFO_DATA_OUT_TEMP_L     0x7B
#define PRESSURE15_REG_FIFO_DATA_OUT_TEMP_H     0x7C

/*! @} */ // pressure15_reg

/**
 * @defgroup pressure15_set Pressure 15 Registers Settings
 * @brief Settings for registers of Pressure 15 Click driver.
 */

/**
 * @addtogroup pressure15_set
 * @{
 */

/**
 * @brief Pressure 15 device ID.
 * @details Device ID of Pressure 15 Click.
 */
#define PRESSURE15_ID 0xB3

/**
 * @brief Pressure 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 15 Click driver.
 */
#define PRESSURE15_SET_DEV_ADDR  0x5C

/*! @} */ // pressure15_set

/**
 * @defgroup pressure15_map Pressure 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 15 Click driver.
 */

/**
 * @addtogroup pressure15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 15 Click to the selected MikroBUS.
 */
#define PRESSURE15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure15_map
/*! @} */ // pressure15

/**
 * @brief Pressure 15 Click driver selector.
 * @details Selects target driver interface of Pressure 15 Click driver.
 */
typedef enum
{
   PRESSURE15_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   PRESSURE15_DRV_SEL_I2C       /**< I2C driver descriptor. */

} pressure15_drv_t;

/**
 * @brief Pressure 15 Click driver interface.
 * @details Definition of driver interface of Pressure 15 Click driver.
 */
typedef err_t ( *pressure15_master_io_t )( struct pressure15_s*, uint8_t, uint8_t*, uint8_t ); 
/**< Driver serial interface. */

/**
 * @brief Pressure 15 Click context object.
 * @details Context object definition of Pressure 15 Click driver.
 */
typedef struct pressure15_s
{
    digital_in_t  int_pin;          /**< Interrupt pin. */

    i2c_master_t  i2c;              /**< I2C driver object. */
    spi_master_t  spi;              /**< SPI driver object. */

    uint8_t     slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    pressure15_drv_t  drv_sel;      /**< Master driver interface selector. */

    pressure15_master_io_t  write_f;/**< Master write function. */
    pressure15_master_io_t  read_f; /**< Master read function. */

} pressure15_t;

/**
 * @brief Pressure 15 Click configuration object.
 * @details Configuration object definition of Pressure 15 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

    pressure15_drv_t  drv_sel;                      /**< Master driver interface selector. */

} pressure15_cfg_t;

/**
 * @brief Pressure 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   PRESSURE15_OK = 0,
   PRESSURE15_ERROR = -1

} pressure15_return_value_t;

/*!
 * @addtogroup pressure15 Pressure 15 Click Driver
 * @brief API for configuring and manipulating Pressure 15 Click driver.
 * @{
 */

/**
 * @brief Pressure 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure15_cfg_setup ( pressure15_cfg_t *cfg );

/**
 * @brief Pressure 15 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #pressure15_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #pressure15_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void pressure15_drv_interface_selection ( pressure15_cfg_t *cfg, pressure15_drv_t drv_sel );

/**
 * @brief Pressure 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure15_init ( pressure15_t *ctx, pressure15_cfg_t *cfg );

/**
 * @brief Pressure 15 default configuration function.
 * @details This function executes a default configuration of Pressure 15
 * Click board.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pressure15_default_cfg ( pressure15_t *ctx );

/**
 * @brief Pressure 15 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pressure15_generic_write ( pressure15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 15 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pressure15_generic_read ( pressure15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Get interrupt pin state.
 * @details Read state of interrupt pin.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @return Interrupt pin state.
 */
uint8_t pressure15_get_int ( pressure15_t *ctx );

/**
 * @brief Get temperature data.
 * @details Read and calculate temperature data from device.
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data in degC unit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pressure15_get_temperature ( pressure15_t *ctx, float *temperature );

/**
 * @brief Get pressure data.
 * @details Read and calculate pressure data from device
 * @param[in] ctx : Click context object.
 * See #pressure15_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data in hPa unit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pressure15_get_pressure ( pressure15_t *ctx, float *pressure );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE15_H

/*! @} */ // pressure15

// ------------------------------------------------------------------------ END
