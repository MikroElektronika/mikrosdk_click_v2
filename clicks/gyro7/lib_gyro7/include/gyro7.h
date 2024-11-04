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
 * @file gyro7.h
 * @brief This file contains API for Gyro 7 Click Driver.
 */

#ifndef GYRO7_H
#define GYRO7_H

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
 * @addtogroup gyro7 Gyro 7 Click Driver
 * @brief API for configuring and manipulating Gyro 7 Click driver.
 * @{
 */

/**
 * @defgroup gyro7_reg Gyro 7 Registers List
 * @brief List of registers of Gyro 7 Click driver.
 */

/**
 * @addtogroup gyro7_reg
 * @{
 */

/**
 * @brief Gyro 7 register map.
 * @details Specified register map of Gyro 7 Click driver.
 */
#define GYRO7_REG_DLPF_B1_H_Y_AXIS          0x02
#define GYRO7_REG_DLPF_B1_L_Y_AXIS          0x09
#define GYRO7_REG_DLPF_B0B2_H_X_AXIS        0x0E
#define GYRO7_REG_DLPF_B0B2_L_X_AXIS        0x0F
#define GYRO7_REG_DLPF_B1_H_X_AXIS          0x10
#define GYRO7_REG_DLPF_B1_L_X_AXIS          0x11
#define GYRO7_REG_DLPF_B0B2_H_Y_AXIS        0x12
#define GYRO7_REG_XG_OFFS_USRH              0x13
#define GYRO7_REG_XG_OFFS_USRL              0x14
#define GYRO7_REG_YG_OFFS_USRH              0x15
#define GYRO7_REG_YG_OFFS_USRL              0x16
#define GYRO7_REG_SMPLRT_DIV                0x19
#define GYRO7_REG_CONFIG                    0x1A
#define GYRO7_REG_GYRO_CONFIG               0x1B
#define GYRO7_REG_HPF_DLPF_RST_AZ           0x26
#define GYRO7_REG_INT_PIN_CFG               0x37
#define GYRO7_REG_INT_ENABLE                0x38
#define GYRO7_REG_INT_STATUS                0x3A
#define GYRO7_REG_TEMP_OUT_H                0x41
#define GYRO7_REG_TEMP_OUT_L                0x42
#define GYRO7_REG_GYRO_XOUT_H               0x43
#define GYRO7_REG_GYRO_XOUT_L               0x44
#define GYRO7_REG_GYRO_YOUT_H               0x45
#define GYRO7_REG_GYRO_YOUT_L               0x46
#define GYRO7_REG_USER_CTRL                 0x6A
#define GYRO7_REG_PWR_MGMT_1                0x6B
#define GYRO7_REG_DLPF_B0B2_L_Y_AXIS        0x70
#define GYRO7_REG_DLPF_A1_H                 0x71
#define GYRO7_REG_DLPF_A1_L                 0x72
#define GYRO7_REG_DLPF_A2_H                 0x73
#define GYRO7_REG_DLPF_A2_L                 0x74
#define GYRO7_REG_WHO_AM_I                  0x75
#define GYRO7_REG_SPI_SEL                   0x76

/*! @} */ // gyro7_reg

/**
 * @defgroup gyro7_set Gyro 7 Registers Settings
 * @brief Settings for registers of Gyro 7 Click driver.
 */

/**
 * @addtogroup gyro7_set
 * @{
 */

/**
 * @brief Gyro 7 DLPF settings.
 * @details Specified DLPF settings of Gyro 7 Click driver.
 */
#define GYRO7_DLPF_B0B2_40_160_HZ           0x0004
#define GYRO7_DLPF_B0B2_80_320_HZ           0x0011
#define GYRO7_DLPF_B0B2_160_640_HZ          0x0040
#define GYRO7_DLPF_B0B2_250_HZ              0x0095
#define GYRO7_DLPF_B0B2_500_HZ              0x0212
#define GYRO7_DLPF_B1_40_160_HZ             0x0008
#define GYRO7_DLPF_B1_80_320_HZ             0x001C
#define GYRO7_DLPF_B1_160_640_HZ            0x006D
#define GYRO7_DLPF_B1_250_HZ                0x0100
#define GYRO7_DLPF_B1_500_HZ                0x0387
#define GYRO7_DLPF_A1_40_160_HZ             0x82D7
#define GYRO7_DLPF_A1_80_320_HZ             0x85AF
#define GYRO7_DLPF_A1_160_640_HZ            0x8B59
#define GYRO7_DLPF_A1_250_HZ                0x91AE
#define GYRO7_DLPF_A1_500_HZ                0xA2EE
#define GYRO7_DLPF_A2_40_160_HZ             0x3D38
#define GYRO7_DLPF_A2_80_320_HZ             0x3A8F
#define GYRO7_DLPF_A2_160_640_HZ            0x3594
#define GYRO7_DLPF_A2_250_HZ                0x307C
#define GYRO7_DLPF_A2_500_HZ                0x24BD
#define GYRO7_DLPF_40_160_HZ                0x00
#define GYRO7_DLPF_80_320_HZ                0x01
#define GYRO7_DLPF_160_640_HZ               0x02
#define GYRO7_DLPF_250_HZ                   0x03
#define GYRO7_DLPF_500_HZ                   0x04

/**
 * @brief Gyro 7 configuration settings.
 * @details Specified settings for configuration register of Gyro 7 Click driver.
 */
#define GYRO7_CONFIG_HPF_ORDER_BYPASS_HPF   0x00
#define GYRO7_CONFIG_HPF_ORDER_ONE_HPF      0x40
#define GYRO7_CONFIG_HPF_ORDER_TWO_HPF      0x60
#define GYRO7_CONFIG_HPF_CFG_M_FACTOR_9     0x00
#define GYRO7_CONFIG_HPF_CFG_M_FACTOR_11    0x04
#define GYRO7_CONFIG_HPF_CFG_M_FACTOR_12    0x08
#define GYRO7_CONFIG_HPF_CFG_M_FACTOR_13    0x0C
#define GYRO7_CONFIG_HPF_CFG_M_FACTOR_14    0x10
#define GYRO7_CONFIG_HPF_CFG_M_FACTOR_15    0x14
#define GYRO7_CONFIG_HPF_CFG_M_FACTOR_16    0x18
#define GYRO7_CONFIG_HPF_CFG_M_FACTOR_17    0x1C
#define GYRO7_CONFIG_DLPF_CFG_BYPASS_DLPF   0x00
#define GYRO7_CONFIG_DLPF_CFG_ENABLE_DLPF   0x02

/**
 * @brief Gyro 7 sample rate settings.
 * @details Specified settings for sample rate register of Gyro 7 Click driver.
 * @note SAMPLE_RATE = INTERNAL_SAMPLE_RATE / ( 1 + SMPLRT_DIV ), where INTERNAL_SAMPLE_RATE = 8 kHz.
 */
#define GYRO7_SAMPLE_RATE_31p25_HZ          255
#define GYRO7_SAMPLE_RATE_40_HZ             199
#define GYRO7_SAMPLE_RATE_80_HZ             99
#define GYRO7_SAMPLE_RATE_100_HZ            79
#define GYRO7_SAMPLE_RATE_200_HZ            39
#define GYRO7_SAMPLE_RATE_400_HZ            19
#define GYRO7_SAMPLE_RATE_800_HZ            9
#define GYRO7_SAMPLE_RATE_1000_HZ           7
#define GYRO7_SAMPLE_RATE_2000_HZ           3
#define GYRO7_SAMPLE_RATE_4000_HZ           1
#define GYRO7_SAMPLE_RATE_8000_HZ           0

/**
 * @brief Gyro 7 interrupt pin config settings.
 * @details Specified settings for interrupt pin config register of Gyro 7 Click driver.
 */
#define GYRO7_INT_PIN_CFG_INT_LEVEL         0x80
#define GYRO7_INT_PIN_CFG_INT_OPEN          0x40
#define GYRO7_INT_PIN_CFG_LATCH_INT_EN      0x20
#define GYRO7_INT_PIN_CFG_INT_RD_CLEAR      0x10

/**
 * @brief Gyro 7 interrupt enable settings.
 * @details Specified settings for interrupt enable register of Gyro 7 Click driver.
 */
#define GYRO7_INT_ENABLE_DATA_RDY_EN        0x01

/**
 * @brief Gyro 7 power management 1 settings.
 * @details Specified settings for power management 1 register of Gyro 7 Click driver.
 */
#define GYRO7_PWR_MGMT_1_DEVICE_RESET       0x80
#define GYRO7_PWR_MGMT_1_SLEEP              0x40
#define GYRO7_PWR_MGMT_1_INTERNAL_OSC       0x00
#define GYRO7_PWR_MGMT_1_PLL_OSC            0x01

/**
 * @brief Gyro 7 gyro configuration settings.
 * @details Specified settings for gyro configuration register of Gyro 7 Click driver.
 */
#define GYRO7_GYRO_CONFIG_XG_ST             0x80
#define GYRO7_GYRO_CONFIG_YG_ST             0x40
#define GYRO7_GYRO_CONFIG_FS_SEL_46p5_DPS   0x00
#define GYRO7_GYRO_CONFIG_FS_SEL_93_DPS     0x08
#define GYRO7_GYRO_CONFIG_FS_SEL_187_DPS    0x10
#define GYRO7_GYRO_CONFIG_FS_SEL_374_DPS    0x18
#define GYRO7_GYRO_CONFIG_FS_SEL_BITS_MASK  0x18
#define GYRO7_GYRO_CONFIG_FCHOICE_B         0x01

/**
 * @brief Gyro 7 gyro sensitivity scale factor.
 * @details Specified values for gyro sensitivity scale factor of Gyro 7 Click driver.
 */
#define GYRO7_GYRO_SENSITIVITY_FS_SEL_0     700.0
#define GYRO7_GYRO_SENSITIVITY_FS_SEL_1     350.0
#define GYRO7_GYRO_SENSITIVITY_FS_SEL_2     175.0
#define GYRO7_GYRO_SENSITIVITY_FS_SEL_3     87.5

/**
 * @brief Gyro 7 temperature calculation constant.
 * @details Specified constant for temperature calculation of Gyro 7 Click driver.
 */
#define GYRO7_TEMP_SENSITIVITY              123.0

/**
 * @brief Gyro 7 WHO AM I register value.
 * @details Specified WHO AM I register value of Gyro 7 Click driver.
 */
#define GYRO7_WHO_AM_I                      0x88

/**
 * @brief Gyro 7 SPI Read/Write bit setting.
 * @details Specified SPI Read/Write bit setting of Gyro 7 Click driver.
 */
#define GYRO7_SPI_READ_WRITE_BIT            0x80

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gyro7_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GYRO7_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define GYRO7_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gyro7_set

/**
 * @defgroup gyro7_map Gyro 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Gyro 7 Click driver.
 */

/**
 * @addtogroup gyro7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Gyro 7 Click to the selected MikroBUS.
 */
#define GYRO7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gyro7_map
/*! @} */ // gyro7

/**
 * @brief Gyro 7 Click context object.
 * @details Context object definition of Gyro 7 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;          /**< Data ready interrupt pin. */

    // Modules
    spi_master_t  spi;              /**< SPI driver object. */

    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */

} gyro7_t;

/**
 * @brief Gyro 7 Click configuration object.
 * @details Configuration object definition of Gyro 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                 /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  int_pin;            /**< Data ready interrupt pin. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} gyro7_cfg_t;

/**
 * @brief Gyro 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GYRO7_OK = 0,
    GYRO7_ERROR = -1

} gyro7_return_value_t;

/*!
 * @addtogroup gyro7 Gyro 7 Click Driver
 * @brief API for configuring and manipulating Gyro 7 Click driver.
 * @{
 */

/**
 * @brief Gyro 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gyro7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gyro7_cfg_setup ( gyro7_cfg_t *cfg );

/**
 * @brief Gyro 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gyro7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_init ( gyro7_t *ctx, gyro7_cfg_t *cfg );

/**
 * @brief Gyro 7 default configuration function.
 * @details This function executes a default configuration of Gyro 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t gyro7_default_cfg ( gyro7_t *ctx );

/**
 * @brief Gyro 7 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_generic_write ( gyro7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Gyro 7 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_generic_read ( gyro7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Gyro 7 write register function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_write_register ( gyro7_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Gyro 7 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_read_register ( gyro7_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Gyro 7 check communication function.
 * @details This function checks the communication by reading and verifying the WHO AM I register.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_check_communication ( gyro7_t *ctx );

/**
 * @brief Gyro 7 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gyro7_get_int_pin ( gyro7_t *ctx );

/**
 * @brief Gyro 7 set DLPF config function.
 * @details This function sets the DLPF register for the selected corner frequency.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @param[in] freq : @li @c 0 - 40/160 Hz,
 *                   @li @c 1 - 80/320 Hz,
 *                   @li @c 2 - 160/640 Hz,
 *                   @li @c 3 - 250 Hz,
 *                   @li @c 4 - 500 Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_set_dlpf_config ( gyro7_t *ctx, uint8_t freq );

/**
 * @brief Gyro 7 read gyroscope function.
 * @details This function reads the gyroscope X and Y axis in degrees per second (dps).
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @param[out] x_axis : X axis value in dps.
 * @param[out] y_axis : Y axis value in dps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_read_gyroscope ( gyro7_t *ctx, float *x_axis, float *y_axis );

/**
 * @brief Gyro 7 read temperature function.
 * @details This function reads the internal temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #gyro7_t object definition for detailed explanation.
 * @param[out] temperature : Internal temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gyro7_read_temperature ( gyro7_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // GYRO7_H

/*! @} */ // gyro7

// ------------------------------------------------------------------------ END
