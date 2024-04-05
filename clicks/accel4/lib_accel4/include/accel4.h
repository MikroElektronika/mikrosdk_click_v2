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
 * @file accel4.h
 * @brief This file contains API for Accel 4 Click Driver.
 */

#ifndef ACCEL4_H
#define ACCEL4_H

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
 * @addtogroup accel4 Accel 4 Click Driver
 * @brief API for configuring and manipulating Accel 4 Click driver.
 * @{
 */

/**
 * @defgroup accel4_reg Accel 4 Registers List
 * @brief List of registers of Accel 4 Click driver.
 */

/**
 * @addtogroup accel4_reg
 * @{
 */

/**
 * @brief Accel 4 description register.
 * @details Specified register for description of Accel 4 Click driver.
 */
#define ACCEL4_REG_INT_STATUS             0x00
#define ACCEL4_REG_TEMP_OUT               0x01
#define ACCEL4_REG_VECM_LSB               0x02
#define ACCEL4_REG_VECM_MSB               0x03
#define ACCEL4_REG_OUT_X_LSB              0x04
#define ACCEL4_REG_OUT_X_MSB              0x05
#define ACCEL4_REG_OUT_Y_LSB              0x06
#define ACCEL4_REG_OUT_Y_MSB              0x07
#define ACCEL4_REG_OUT_Z_LSB              0x08
#define ACCEL4_REG_OUT_Z_MSB              0x09
#define ACCEL4_REG_BUF_STATUS             0x0B
#define ACCEL4_REG_BUF_X_LSB              0x0C
#define ACCEL4_REG_BUF_X_MSB              0x0D
#define ACCEL4_REG_BUF_Y_LSB              0x0E
#define ACCEL4_REG_BUF_Y_MSB              0x0F
#define ACCEL4_REG_BUF_Z_LSB              0x10
#define ACCEL4_REG_BUF_Z_MSB              0x11
#define ACCEL4_REG_PROD_REV               0x12
#define ACCEL4_REG_WHO_AM_I               0x13
#define ACCEL4_REG_SYS_MODE               0x14
#define ACCEL4_REG_SENS_CONFIG1           0x15
#define ACCEL4_REG_SENS_CONFIG2           0x16
#define ACCEL4_REG_SENS_CONFIG3           0x17
#define ACCEL4_REG_SENS_CONFIG4           0x18
#define ACCEL4_REG_SENS_CONFIG5           0x19
#define ACCEL4_REG_WAKE_IDLE_LSB          0x1A
#define ACCEL4_REG_WAKE_IDLE_MSB          0x1B
#define ACCEL4_REG_SLEEP_IDLE_LSB         0x1C
#define ACCEL4_REG_SLEEP_IDLE_MSB         0x1D
#define ACCEL4_REG_ASLP_COUINT_LSB        0x1E
#define ACCEL4_REG_ASLP_COUINT_MSB        0x1F
#define ACCEL4_REG_INT_EN                 0x20
#define ACCEL4_REG_INT_PIN_SEL            0x21
#define ACCEL4_REG_OFF_X                  0x22
#define ACCEL4_REG_OFF_Y                  0x23
#define ACCEL4_REG_OFF_Z                  0x24
#define ACCEL4_REG_BUF_CONFIG1            0x26
#define ACCEL4_REG_BUF_CONFIG2            0x27
#define ACCEL4_REG_ORIENT_STATUS          0x28
#define ACCEL4_REG_ORIENT_CONFIG          0x29
#define ACCEL4_REG_ORINET_DBCOUNT         0x2A
#define ACCEL4_REG_ORIENT_BF_ZCOMP        0x2B
#define ACCEL4_REG_ORIENT_THS_REG         0x2C
#define ACCEL4_REG_SDCD_INT_SRC1          0x2D
#define ACCEL4_REG_SDCD_INT_SRC2          0x2E
#define ACCEL4_REG_SDCD_CONFIG1           0x2F
#define ACCEL4_REG_SDCD_CONFIG2           0x30
#define ACCEL4_REG_SDCD_OT_DBCNT          0x31
#define ACCEL4_REG_SDCD_WT_DBCNT          0x32
#define ACCEL4_REG_SDCD_LTHS_LSB          0x33
#define ACCEL4_REG_SDCD_LTHS_MSB          0x34
#define ACCEL4_REG_SDCD_UTHS_LSB          0x35
#define ACCEL4_REG_SDCD_UTHS_MSB          0x36
#define ACCEL4_REG_SELF_TEST_CONFIG1      0x37
#define ACCEL4_REG_SELF_TEST_CONFIG2      0x38

/*! @} */ // accel4_reg

/**
 * @defgroup accel4_set Accel 4 Registers Settings
 * @brief Settings for registers of Accel 4 Click driver.
 */

/**
 * @addtogroup accel4_set
 * @{
 */

/**
 * @brief Accel 4 identification value.
 * @details Specified identification of Accel 4 Click driver.
 */
#define ACCEL4_DEVICE_ID                    0x84

/**
 * @brief Accel 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 4 Click driver.
 */
#define ACCEL4_SET_DEV_ADDR                 0x18

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL4_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL4_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel4_set

/**
 * @defgroup accel4_map Accel 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 4 Click driver.
 */

/**
 * @addtogroup accel4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 4 Click to the selected MikroBUS.
 */
#define ACCEL4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel4_map
/*! @} */ // accel4

/**
 * @brief Accel 4 Click driver selector.
 * @details Selects target driver interface of Accel 4 Click driver.
 */
typedef enum
{
   ACCEL4_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   ACCEL4_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel4_drv_t;

/**
 * @brief Accel 4 Click driver interface.
 * @details Definition of driver interface of Accel 4 Click driver.
 */
typedef err_t ( *accel4_master_io_t )( struct accel4_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 4 Click context object.
 * @details Context object definition of Accel 4 Click driver.
 */
typedef struct accel4_s
{
    digital_in_t  int2;             /**< Interrput 2. */
    digital_in_t  int1;             /**< Interrput 1. */

    i2c_master_t  i2c;              /**< I2C driver object. */
    spi_master_t  spi;              /**< SPI driver object. */

    uint8_t     slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    accel4_drv_t  drv_sel;          /**< Master driver interface selector. */

    accel4_master_io_t  write_f;    /**< Master write function. */
    accel4_master_io_t  read_f;     /**< Master read function. */
   
    float resolution;

} accel4_t;

/**
 * @brief Accel 4 Click configuration object.
 * @details Configuration object definition of Accel 4 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  int2;       /**< Interrupt 2. */
    pin_name_t  int1;       /**< Interrupt 1. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

   accel4_drv_t  drv_sel;   /**< Master driver interface selector. */

} accel4_cfg_t;

/**
 * @brief Accel 4 Click axes data.
 * @details Axes data object definition of Accel 4 Click driver.
 */
typedef struct
{
   float x; /**< X axis. */
   float y; /**< Y axis. */
   float z; /**< Z axis. */

} accel4_axes_t;

/**
 * @brief Accel 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ACCEL4_OK = 0,
   ACCEL4_ERROR = -1

} accel4_return_value_t;

/*!
 * @addtogroup accel4 Accel 4 Click Driver
 * @brief API for configuring and manipulating Accel 4 Click driver.
 * @{
 */

/**
 * @brief Accel 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel4_cfg_setup ( accel4_cfg_t *cfg );

/**
 * @brief Accel 4 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel4_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel4_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel4_drv_interface_selection ( accel4_cfg_t *cfg, accel4_drv_t drv_sel );

/**
 * @brief Accel 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel4_init ( accel4_t *ctx, accel4_cfg_t *cfg );

/**
 * @brief Accel 4 default configuration function.
 * @details This function executes a default configuration of Accel 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel4_default_cfg ( accel4_t *ctx );

/**
 * @brief Accel 4 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel4_generic_write ( accel4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 4 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel4_generic_read ( accel4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Get interrupt 1 pin state.
 * @details This function reads logic state of interrupt 1 pin.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @return State of interrupt pin.
 */
uint8_t accel4_get_int1 ( accel4_t *ctx );

/**
 * @brief Get interrupt 2 pin state.
 * @details This function reads logic state of interrupt 2 pin.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @return State of interrupt pin.
 */
uint8_t accel4_get_int2 ( accel4_t *ctx );

/**
 * @brief Accel data reading.
 * @details This function reads a accel data and calculates it with 
 * resolution set in @b ctx object. Data will be set in @b axes object.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @param[out] axes : Axes data object.
 * See #accel4_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t accel4_get_axes_data ( accel4_t *ctx, accel4_axes_t *axes );

/**
 * @brief Reads current resolution of output data.
 * @details This function reads current configuration for 
 * resolution of output data.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @return Resolution of the output data.
 * @note User should call this function and set updated data to 
 * context object whenever the configuration is changed.
 */
float accel4_axes_get_resolution ( accel4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL4_H

/*! @} */ // accel4

// ------------------------------------------------------------------------ END
