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
 * @file barometer9.h
 * @brief This file contains API for Barometer 9 Click Driver.
 */

#ifndef BAROMETER9_H
#define BAROMETER9_H

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
 * @addtogroup barometer9 Barometer 9 Click Driver
 * @brief API for configuring and manipulating Barometer 9 Click driver.
 * @{
 */

/**
 * @defgroup barometer9_reg Barometer 9 Registers List
 * @brief List of registers of Barometer 9 Click driver.
 */

/**
 * @addtogroup barometer9_reg
 * @{
 */

/**
 * @brief Barometer 9 description register.
 * @details Specified register for description of Barometer 9 Click driver.
 */
#define BAROMETER9_REG_PART_ID0             0x00
#define BAROMETER9_REG_PART_ID1             0x01
#define BAROMETER9_REG_UIND0                0x02
#define BAROMETER9_REG_UIND1                0x03
#define BAROMETER9_REG_UIND2                0x04
#define BAROMETER9_REG_UIND3                0x05
#define BAROMETER9_MODE_CFG                 0x06
#define BAROMETER9_MEAS_CFG                 0x07
#define BAROMETER9_STBY_CFG                 0x08
#define BAROMETER9_OVS_CFG                  0x09
#define BAROMETER9_MAVG_CFG                 0x0A
#define BAROMETER9_INTF_CFG                 0x0B
#define BAROMETER9_INT_CFG                  0x0C
#define BAROMETER9_PRESS_LO_XL_CFG          0x0D
#define BAROMETER9_PRESS_LO_L_CFG           0x0E
#define BAROMETER9_PRESS_LO_H_CFG           0x0F
#define BAROMETER9_PRESS_HI_XL_CFG          0x10
#define BAROMETER9_PRESS_HI_L_CFG           0x11
#define BAROMETER9_PRESS_HI_H_CFG           0x12
#define BAROMETER9_FIFO_CFG                 0x13
#define BAROMETER9_DATA_STAT                0x14
#define BAROMETER9_FIFO_STAT                0x15
#define BAROMETER9_INT_STAT                 0x16
#define BAROMETER9_PRESS_OUT_XL             0x17
#define BAROMETER9_PRESS_OUT_L              0x18
#define BAROMETER9_PRESS_OUT_H              0x19
#define BAROMETER9_TEMP_OUT_L               0x1A
#define BAROMETER9_TEMP_OUT_H               0x1B
#define BAROMETER9_PRESS_OUT_F_XL           0x27
#define BAROMETER9_PRESS_OUT_F_L            0x28
#define BAROMETER9_PRESS_OUT_F_H            0x29

/*! @} */ // barometer9_reg

/**
 * @defgroup barometer9_set Barometer 9 Registers Settings
 * @brief Settings for registers of Barometer 9 Click driver.
 */

/**
 * @addtogroup barometer9_set
 * @{
 */

/**
 * @brief Barometer 9 description setting.
 * @details Specified setting for description of Barometer 9 Click driver.
 */
#define BAROMETER9_HIGH_POWER_MODE         0x80
#define BAROMETER9_LOW_POWER_MODE          0x00
#define BAROMETER9_DIRECT_PATH             0x00
#define BAROMETER9_FIFO_MODE               0x20
#define BAROMETER9_AVERAGE_MODE            0x40
#define BAROMETER9_IDLE_MODE               0x00
#define BAROMETER9_MEASURMENT_MODE         0x10
#define BAROMETER9_SW_RESET                0x08
#define BAROMETER9_READ_PRESS_ONLY         0x01
#define BAROMETER9_READ_TEMP_ONLY          0x02
#define BAROMETER9_READ_PRES_AND_TEMP      0x03

/**
 * @brief Barometer 9 MEAS_CFG register setting.
 * @details Specified setting for MEAS_CFG register of Barometer 9 Click driver.
 */
#define BAROMETER9_P_CONV_0                0x00
#define BAROMETER9_P_CONV_1                0x08
#define BAROMETER9_P_CONV_2                0x10
#define BAROMETER9_PT_RATE_1               0x00
#define BAROMETER9_PT_RATE_4               0x01
#define BAROMETER9_PT_RATE_8               0x02
#define BAROMETER9_PT_RATE_16              0x03
#define BAROMETER9_PT_RATE_32              0x04
#define BAROMETER9_PT_RATE_64              0x05
#define BAROMETER9_PT_RATE_128             0x06
#define BAROMETER9_PT_RATE_256             0x07

/**
 * @brief Barometer 9 conversion constants.
 * @details Specified conversion constants of Barometer 9 Click driver.
 */
#define BAROMETER9_TEMPERATURE_CON_CONST   128
#define BAROMETER9_K_TO_C_CON_CONST        273.15f
#define BAROMETER9_PRESSURE_CON_CONST      64

/**
 * @brief Barometer 9 Device ID value.
 * @details Specified Device ID of Barometer 9 Click driver.
 */
#define BAROMETER9_DEVICE_ID                0x0321

/**
 * @brief Barometer 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 9 Click driver.
 */
#define BAROMETER9_DEVICE_ADDRESS            0x20

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b barometer9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BAROMETER9_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define BAROMETER9_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // barometer9_set

/**
 * @defgroup barometer9_map Barometer 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 9 Click driver.
 */

/**
 * @addtogroup barometer9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 9 Click to the selected MikroBUS.
 */
#define BAROMETER9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // barometer9_map
/*! @} */ // barometer9

/**
 * @brief Barometer 9 Click driver selector.
 * @details Selects target driver interface of Barometer 9 Click driver.
 */
typedef enum
{
    BAROMETER9_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    BAROMETER9_DRV_SEL_I2C       /**< I2C driver descriptor. */

} barometer9_drv_t;

/**
 * @brief Barometer 9 Click driver interface.
 * @details Definition of driver interface of Barometer 9 Click driver.
 */
struct barometer9_s;
typedef err_t ( *barometer9_master_io_t )( struct barometer9_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Barometer 9 Click context object.
 * @details Context object definition of Barometer 9 Click driver.
 */
typedef struct barometer9_s
{
    digital_in_t int_pin;               /**< Interrupt pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    barometer9_drv_t drv_sel;           /**< Master driver interface selector. */

    barometer9_master_io_t write_f;     /**< Master write function. */
    barometer9_master_io_t read_f;      /**< Master read function. */

} barometer9_t;

/**
 * @brief Barometer 9 Click configuration object.
 * @details Configuration object definition of Barometer 9 Click driver.
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

    barometer9_drv_t drv_sel;   /**< Master driver interface selector. */

} barometer9_cfg_t;

/**
 * @brief Barometer 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER9_OK = 0,
    BAROMETER9_ERROR = -1

} barometer9_return_value_t;

/*!
 * @addtogroup barometer9 Barometer 9 Click Driver
 * @brief API for configuring and manipulating Barometer 9 Click driver.
 * @{
 */

/**
 * @brief Barometer 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer9_cfg_setup ( barometer9_cfg_t *cfg );

/**
 * @brief Barometer 9 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #barometer9_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #barometer9_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void barometer9_drv_interface_sel ( barometer9_cfg_t *cfg, barometer9_drv_t drv_sel );

/**
 * @brief Barometer 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer9_init ( barometer9_t *ctx, barometer9_cfg_t *cfg );

/**
 * @brief Barometer 9 default configuration function.
 * @details This function executes a default configuration of Barometer 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer9_default_cfg ( barometer9_t *ctx );

/**
 * @brief Barometer 9 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer9_generic_write ( barometer9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 9 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer9_generic_read ( barometer9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 9 Device ID reading function.
 * @details This function is used to read a Device ID of Barometer 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[out] part_id : Device ID value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer9_read_part_id ( barometer9_t *ctx, uint16_t *part_id );

/**
 * @brief Barometer 9 temperature reading function.
 * @details This function is used to read a temperature of Barometer 9
 * click board in degree of Celsius.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degrees of Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer9_get_temperature ( barometer9_t *ctx, float *temperature );

/**
 * @brief Barometer 9 pressure reading function.
 * @details This function is used to read a pressure of Barometer 9
 * click board in Pascals.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[out] pressure : Pressure in Pascals.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer9_get_pressure ( barometer9_t *ctx, float *pressure );

/**
 * @brief Barometer 9 software reset function.
 * @details This function is used to perform software reset of Barometer 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer9_sw_reset ( barometer9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER9_H

/*! @} */ // barometer9

// ------------------------------------------------------------------------ END
