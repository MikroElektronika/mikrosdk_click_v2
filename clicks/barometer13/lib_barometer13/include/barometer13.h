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
 * @file barometer13.h
 * @brief This file contains API for Barometer 13 Click Driver.
 */

#ifndef BAROMETER13_H
#define BAROMETER13_H

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
 * @addtogroup barometer13 Barometer 13 Click Driver
 * @brief API for configuring and manipulating Barometer 13 Click driver.
 * @{
 */

/**
 * @defgroup barometer13_reg Barometer 13 Registers List
 * @brief List of registers of Barometer 13 Click driver.
 */

/**
 * @addtogroup barometer13_reg
 * @{
 */

/**
 * @brief Barometer 13 description register.
 * @details Specified register for description of Barometer 13 Click driver.
 */
#define BAROMETER13_REG_CHIP_ID                 0x01
#define BAROMETER13_REG_REV_ID                  0x02
#define BAROMETER13_REG_CHIP_STATUS             0x11
#define BAROMETER13_REG_DRIVE_CONFIG            0x13
#define BAROMETER13_REG_INT_CONFIG              0x14
#define BAROMETER13_REG_INT_SOURCE              0x15
#define BAROMETER13_REG_FIFO_CONFIG             0x16
#define BAROMETER13_REG_FIFO_COUNT              0x17
#define BAROMETER13_REG_FIFO_SEL                0x18
#define BAROMETER13_REG_TEMP_DATA_XLSB          0x1D
#define BAROMETER13_REG_TEMP_DATA_LSB           0x1E
#define BAROMETER13_REG_TEMP_DATA_MSB           0x1F
#define BAROMETER13_REG_PRESS_DATA_XLSB         0x20
#define BAROMETER13_REG_PRESS_DATA_LSB          0x21
#define BAROMETER13_REG_PRESS_DATA_MSB          0x22
#define BAROMETER13_REG_INT_STATUS              0x27
#define BAROMETER13_REG_STATUS                  0x28
#define BAROMETER13_REG_FIFO_DATA               0x29
#define BAROMETER13_REG_NVM_ADDR                0x2B
#define BAROMETER13_REG_NVM_DATA_LSB            0x2C
#define BAROMETER13_REG_NVM_DATA_MSB            0x2D
#define BAROMETER13_REG_DSP_CONFIG              0x30
#define BAROMETER13_REG_DSP_IIR                 0x31
#define BAROMETER13_REG_OOR_THR_P_LSB           0x32
#define BAROMETER13_REG_OOR_THR_P_MSB           0x33
#define BAROMETER13_REG_OOR_RANGE               0x34
#define BAROMETER13_REG_OOR_CONFIG              0x35
#define BAROMETER13_REG_OSR_CONFIG              0x36
#define BAROMETER13_REG_ODR_CONFIG              0x37
#define BAROMETER13_REG_OSR_EFF                 0x38
#define BAROMETER13_REG_CMD                     0x7E

/*! @} */ // barometer13_reg

/**
 * @defgroup barometer13_set Barometer 13 Registers Settings
 * @brief Settings for registers of Barometer 13 Click driver.
 */

/**
 * @addtogroup barometer13_set
 * @{
 */

/**
 * @brief Barometer 13 identification and revision ID data values.
 * @details Identification and revision ID data values of Barometer 13 Click driver.
 */
#define BAROMETER13_CHIP_ID                     0x51
#define BAROMETER13_REV_ID                      0x32

/**
 * @brief Barometer 13 interrupt configuration register data values.
 * @details Interrupt configuration register data values of Barometer 13 Click driver.
 */
#define BAROMETER13_INT_ENABLE                  0x08
#define BAROMETER13_INT_DISABLE                 0x00
#define BAROMETER13_INT_OPEN_DRAIN              0x04
#define BAROMETER13_INT_PUSH_PULL               0x00
#define BAROMETER13_INT_ACTIVE_HIGH             0x02
#define BAROMETER13_INT_ACTIVE_LOW              0x00
#define BAROMETER13_INT_LATCHED                 0x01
#define BAROMETER13_INT_PULSED                  0x00

/**
 * @brief Barometer 13 interrupt source selection data values.
 * @details Interrupt source selection data values of Barometer 13 Click driver.
 */
#define BAROMETER13_OOR_P_EN                    0x08
#define BAROMETER13_FIFO_THS_EN                 0x04
#define BAROMETER13_FIFO_FULL_EN                0x02
#define BAROMETER13_DRDY_DATA_EN                0x01
#define BAROMETER13_DRDY_DATA_DIS               0x00

/**
 * @brief Barometer 13 interrupt status register data values.
 * @details Interrupt status register data values of Barometer 13 Click driver.
 */
#define BAROMETER13_INT_STATUS_POR              0x10
#define BAROMETER13_INT_STATUS_OOR_P            0x08
#define BAROMETER13_INT_STATUS_FIFO_THS         0x04
#define BAROMETER13_INT_STATUS_FIFO_FULL        0x02
#define BAROMETER13_INT_STATUS_DRDY_DATA_REG    0x01

/**
 * @brief Barometer 13 DSP configuration data values.
 * @details DSP configuration data values of Barometer 13 Click driver.
 */
#define BAROMETER13_OOR_SEL_IIR_P               0x80
#define BAROMETER13_FIFO_SEL_IIR_P              0x40
#define BAROMETER13_SHDW_SEL_IIR_P              0x20
#define BAROMETER13_FIFO_SEL_IIR_T              0x10
#define BAROMETER13_SHDW_SEL_IIR_T              0x08
#define BAROMETER13_IIR_FLUSH_FORCED_EN         0x04
#define BAROMETER13_DSP_CFG_RESERVED_BITS       0x03

/**
 * @brief Barometer 13 DSP configuration data values.
 * @details DSP configuration data values of Barometer 13 Click driver.
 */
#define BAROMETER13_SET_IIR_P_BYPASS            0x00
#define BAROMETER13_SET_IIR_P_FLT_COEF_1        0x08
#define BAROMETER13_SET_IIR_P_FLT_COEF_3        0x10
#define BAROMETER13_SET_IIR_P_FLT_COEF_7        0x18
#define BAROMETER13_SET_IIR_P_FLT_COEF_15       0x20
#define BAROMETER13_SET_IIR_P_FLT_COEF_31       0x28
#define BAROMETER13_SET_IIR_P_FLT_COEF_63       0x30
#define BAROMETER13_SET_IIR_P_FLT_COEF_127      0x38
#define BAROMETER13_SET_IIR_T_BYPASS            0x00
#define BAROMETER13_SET_IIR_T_FLT_COEF_1        0x01
#define BAROMETER13_SET_IIR_T_FLT_COEF_3        0x02
#define BAROMETER13_SET_IIR_T_FLT_COEF_7        0x03
#define BAROMETER13_SET_IIR_T_FLT_COEF_15       0x04
#define BAROMETER13_SET_IIR_T_FLT_COEF_31       0x05
#define BAROMETER13_SET_IIR_T_FLT_COEF_63       0x06
#define BAROMETER13_SET_IIR_T_FLT_COEF_127      0x07

/**
 * @brief Barometer 13 over-sampling rate (OSR) configuration data values.
 * @details Over-sampling rate (OSR) configuration data values of Barometer 13 Click driver.
 */
#define BAROMETER13_PRESS_EN                    0x40
#define BAROMETER13_OSR_P_1X                    0x00
#define BAROMETER13_OSR_P_2X                    0x08
#define BAROMETER13_OSR_P_4X                    0x10
#define BAROMETER13_OSR_P_8X                    0x18
#define BAROMETER13_OSR_P_16X                   0x20
#define BAROMETER13_OSR_P_32X                   0x28
#define BAROMETER13_OSR_P_64X                   0x30
#define BAROMETER13_OSR_P_128X                  0x38
#define BAROMETER13_OSR_T_1X                    0x00
#define BAROMETER13_OSR_T_2X                    0x01
#define BAROMETER13_OSR_T_4X                    0x02
#define BAROMETER13_OSR_T_8X                    0x03
#define BAROMETER13_OSR_T_16X                   0x04
#define BAROMETER13_OSR_T_32X                   0x05
#define BAROMETER13_OSR_T_64X                   0x06
#define BAROMETER13_OSR_T_128X                  0x07

/**
 * @brief Barometer 13 output data rate (ODR) configuration data values.
 * @details Output data rate (ODR) configuration data values of Barometer 13 Click driver.
 */
#define BAROMETER13_DEEP_DIS                    0x80
#define BAROMETER13_ODR_240_HZ                  0x00
#define BAROMETER13_ODR_218_537_HZ              0x04
#define BAROMETER13_ODR_199_111_HZ              0x08
#define BAROMETER13_ODR_179_2_HZ                0x0C
#define BAROMETER13_ODR_160_HZ                  0x10
#define BAROMETER13_ODR_149_333_HZ              0x14
#define BAROMETER13_ODR_140_HZ                  0x18
#define BAROMETER13_ODR_129_855_HZ              0x1C
#define BAROMETER13_ODR_120_HZ                  0x20
#define BAROMETER13_ODR_110_164_HZ              0x24
#define BAROMETER13_ODR_100_299_HZ              0x28
#define BAROMETER13_ODR_89p6_HZ                 0x2C
#define BAROMETER13_ODR_80_HZ                   0x30
#define BAROMETER13_ODR_70_HZ                   0x34
#define BAROMETER13_ODR_60_HZ                   0x38
#define BAROMETER13_ODR_50_056_HZ               0x3C
#define BAROMETER13_ODR_45_025_HZ               0x40
#define BAROMETER13_ODR_40_HZ                   0x44
#define BAROMETER13_ODR_35_HZ                   0x48
#define BAROMETER13_ODR_30_HZ                   0x4C
#define BAROMETER13_ODR_25_005_HZ               0x50
#define BAROMETER13_ODR_20_HZ                   0x54
#define BAROMETER13_ODR_15_HZ                   0x58
#define BAROMETER13_ODR_10_HZ                   0x5C
#define BAROMETER13_ODR_5_HZ                    0x60
#define BAROMETER13_ODR_4_HZ                    0x64
#define BAROMETER13_ODR_3_HZ                    0x68
#define BAROMETER13_ODR_2_HZ                    0x6C
#define BAROMETER13_ODR_1_HZ                    0x70
#define BAROMETER13_ODR_0_5_HZ                  0x74
#define BAROMETER13_ODR_0_25_HZ                 0x78
#define BAROMETER13_ODR_0_125_HZ                0x7C
#define BAROMETER13_PWR_MODE_STANDBY            0x00
#define BAROMETER13_PWR_MODE_NORMAL             0x01
#define BAROMETER13_PWR_MODE_FORCE              0x02
#define BAROMETER13_PWR_MODE_NON_STOP           0x03

/**
 * @brief Barometer 13 states of the interrupt.
 * @details States of the interrupt of Barometer 13 Click driver.
 */
#define BAROMETER13_INT_STATE_HIGH              0x01
#define BAROMETER13_INT_STATE_LOW               0x00

/**
 * @brief Barometer 13 pressure and temperature resolution.
 * @details Pressure and temperature resolution of Barometer 13 Click driver.
 */
#define BAROMETER13_PRESS_DATA_RES              64.0f
#define BAROMETER13_TEMP_DATA_RES               65536.0f
#define BAROMETER13_PA_TO_MBAR                  100.0f

/**
 * @brief Barometer 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 13 Click driver.
 */
#define BAROMETER13_DEVICE_ADDRESS_1            0x46
#define BAROMETER13_DEVICE_ADDRESS_0            0x47

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b barometer13_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BAROMETER13_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define BAROMETER13_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // barometer13_set

/**
 * @defgroup barometer13_map Barometer 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 13 Click driver.
 */

/**
 * @addtogroup barometer13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 13 Click to the selected MikroBUS.
 */
#define BAROMETER13_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // barometer13_map
/*! @} */ // barometer13

/**
 * @brief Barometer 13 Click driver selector.
 * @details Selects target driver interface of Barometer 13 Click driver.
 */
typedef enum
{
    BAROMETER13_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    BAROMETER13_DRV_SEL_I2C       /**< I2C driver descriptor. */

} barometer13_drv_t;

/**
 * @brief Barometer 13 Click driver interface.
 * @details Definition of driver interface of Barometer 13 Click driver.
 */
typedef err_t ( *barometer13_master_io_t )( struct barometer13_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Barometer 13 Click context object.
 * @details Context object definition of Barometer 13 Click driver.
 */
typedef struct barometer13_s
{
    digital_in_t int_pin;          /**< Interrupt pin. */

    i2c_master_t i2c;              /**< I2C driver object. */
    spi_master_t spi;              /**< SPI driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
    barometer13_drv_t drv_sel;     /**< Master driver interface selector. */

    barometer13_master_io_t write_f;    /**< Master write function. */
    barometer13_master_io_t read_f;     /**< Master read function. */

} barometer13_t;

/**
 * @brief Barometer 13 Click configuration object.
 * @details Configuration object definition of Barometer 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;    /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

    barometer13_drv_t drv_sel;    /**< Master driver interface selector. */

} barometer13_cfg_t;

/**
 * @brief Barometer 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER13_OK = 0,
    BAROMETER13_ERROR = -1

} barometer13_return_value_t;

/*!
 * @addtogroup barometer13 Barometer 13 Click Driver
 * @brief API for configuring and manipulating Barometer 13 Click driver.
 * @{
 */

/**
 * @brief Barometer 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer13_cfg_setup ( barometer13_cfg_t *cfg );

/**
 * @brief Barometer 13 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #barometer13_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #barometer13_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void barometer13_drv_interface_sel ( barometer13_cfg_t *cfg, barometer13_drv_t drv_sel );

/**
 * @brief Barometer 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_init ( barometer13_t *ctx, barometer13_cfg_t *cfg );

/**
 * @brief Barometer 13 default configuration function.
 * @details This function executes a default configuration of Barometer 13
 * Click board.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer13_default_cfg ( barometer13_t *ctx );

/**
 * @brief Barometer 13 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_generic_write ( barometer13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 13 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_generic_read ( barometer13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 13 register data writing function.
 * @details This function writes the data bytes to the selected register
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_reg_write ( barometer13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Barometer 13 register data reading function.
 * @details This function reads the data bytes from the selected register
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_reg_read ( barometer13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Barometer 13 get device ID function.
 * @details This function reads the ASIC identification ID and revision ID
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[out] chip_id : ASIC identification ID.
 * @param[out] rev_id : ASIC revision ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_get_device_id ( barometer13_t *ctx, uint8_t *chip_id, uint8_t *rev_id );

/**
 * @brief Barometer 13 set the interrupt config function.
 * @details This function sets the interrupt configuration
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] int_en : Interrupt enabling.
 * @param[in] int_od : Interrupt pin config.
 * @param[in] int_pol : Interrupt polarity.
 * @param[in] int_mode : Interrupt mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_set_int_cfg ( barometer13_t *ctx, uint8_t int_en, uint8_t int_od, 
                                                    uint8_t int_pol, uint8_t int_mode );

/**
 * @brief Barometer 13 set data ready function.
 * @details This function sets the data ready
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] en_drdy_data : Data ready enable-disable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_set_drdy_data ( barometer13_t *ctx, uint8_t en_drdy_data );

/**
 * @brief Barometer 13 get interrupt status function.
 * @details This function reads the interrupt status
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[out] int_status : Interrupt status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_get_int_status ( barometer13_t *ctx, uint8_t *int_status );

/**
 * @brief Barometer 13 set shadow IIR selection function.
 * @details This function sets the shadow registers IIR selection 
 * of the pressure and temperature data
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] shdw_sel_iir_p : IIR selection pressure data.
 * @param[in] shdw_sel_iir_t : IIR selection temperature data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_set_shdw_sel ( barometer13_t *ctx, uint8_t shdw_sel_iir_p, uint8_t shdw_sel_iir_t );

/**
 * @brief Barometer 13 set LPF band filter function.
 * @details This function sets the LPF band filter selection
 * of the pressure and temperature data
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] set_iir_p : Pressure IIR LPF band filter selection.
 * @param[in] set_iir_t : Temperature IIR LPF band filter selection
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This field cannot be written during an ongoing P/T conversion.
 */
err_t barometer13_set_lpf_band_flt ( barometer13_t *ctx, uint8_t set_iir_p, uint8_t set_iir_t );

/**
 * @brief Barometer 13 set over-sampling rate function.
 * @details This function sets the pressure and temperature over-sampling data rate
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] osr_p : Pressure over-sampling data rate.
 * @param[in] osr_t : Temperature over-sampling data rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_set_osr ( barometer13_t *ctx, uint8_t osr_p, uint8_t osr_t );

/**
 * @brief Barometer 13 enable pressure data function.
 * @details This function is used to enabled pressure data output
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_press_enable ( barometer13_t *ctx );

/**
 * @brief Barometer 13 set the output data rate function.
 * @details This function sets the pressure and temperature output data rate
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] odr : Output data rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_set_odr ( barometer13_t *ctx, uint8_t odr );

/**
 * @brief Barometer 13 set power mode configuration function.
 * @details This function sets the pressure and temperature power mode configuration
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[in] pwr_mode : Power mode configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_set_pwr_mode ( barometer13_t *ctx, uint8_t pwr_mode );

/**
 * @brief Barometer 13 get raw data function.
 * @details This function reads the pressure and temperature raw data value
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[out] press_data : Raw digital pressure value.
 * @param[out] temp_data : Raw digital temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_get_raw_data ( barometer13_t *ctx, int32_t *press_data, int32_t *temp_data );

/**
 * @brief Barometer 13 get the measurement data function.
 * @details This function reads the pressure and temperature measurement data
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[out] pressure : Pressure value [mBar-hPa].
 * @param[out] temperature : Temperature data [degree Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_get_measurement ( barometer13_t *ctx, float *pressure, float *temperature );

/**
 * @brief Barometer 13 get the pressure data function.
 * @details This function reads the pressure measurement data
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @param[out] pressure : Pressure value [mBar-hPa].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer13_get_pressure ( barometer13_t *ctx, float *pressure );

/**
 * @brief Barometer 13 get the interrupt function.
 * @details This function get states of the interrupt [INT] pin
 * of the BMP585, Barometric Pressure Sensor
 * on the Barometer 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #barometer13_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t barometer13_get_interrupt ( barometer13_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER13_H

/*! @} */ // barometer13

// ------------------------------------------------------------------------ END
