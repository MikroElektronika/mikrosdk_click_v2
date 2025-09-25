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
 * @file environment6.h
 * @brief This file contains API for Environment 6 Click Driver.
 */

#ifndef ENVIRONMENT6_H
#define ENVIRONMENT6_H

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
 * @addtogroup environment6 Environment 6 Click Driver
 * @brief API for configuring and manipulating Environment 6 Click driver.
 * @{
 */

/**
 * @defgroup environment6_reg Environment 6 Registers List
 * @brief List of registers of Environment 6 Click driver.
 */

/**
 * @addtogroup environment6_reg
 * @{
 */

/**
 * @brief Environment 6 memory map summary.
 * @details The full list of registers.
 */
#define ENVIRONMENT6_REG_COEFF_3                0x00
#define ENVIRONMENT6_REG_FIELD_0                0x1D
#define ENVIRONMENT6_REG_IDAC_HEAT_0            0x50
#define ENVIRONMENT6_REG_RES_HEAT_0             0x5A
#define ENVIRONMENT6_REG_GAS_WAIT_0             0x64
#define ENVIRONMENT6_REG_GAS_WAIT_SHARED        0x6E
#define ENVIRONMENT6_REG_CTRL_GAS_0             0x70
#define ENVIRONMENT6_REG_CTRL_GAS_1             0x71
#define ENVIRONMENT6_REG_CTRL_HUM               0x72
#define ENVIRONMENT6_REG_STATUS                 0x73
#define ENVIRONMENT6_REG_CTRL_MEAS              0x74
#define ENVIRONMENT6_REG_CONFIG                 0x75
#define ENVIRONMENT6_REG_UNIQUE_ID              0x83
#define ENVIRONMENT6_REG_COEFF_1                0x8A
#define ENVIRONMENT6_REG_CHIP_ID                0xD0
#define ENVIRONMENT6_REG_RESET                  0xE0
#define ENVIRONMENT6_REG_COEFF_2                0xE1
#define ENVIRONMENT6_REG_VARIANT_ID             0xF0

/*! @} */ // environment6_reg

/**
 * @defgroup environment6_set Environment 6 Registers Settings
 * @brief Settings for registers of Environment 6 Click driver.
 */

/**
 * @addtogroup environment6_set
 * @{
 */

/**
 * @brief Environment 6 chip ID value.
 * @details Specified setting for unique chip identifier of Environment 6 Click driver.
 */
#define ENVIRONMENT6_CHIP_ID                    0x61

/**
 * @brief Environment 6 soft reset command settings.
 * @details Specified setting for soft reset command of Environment 6 Click driver.
 */
#define ENVIRONMENT6_SOFT_RESET                 0xB6

/**
 * @brief Environment 6 oversampling setting macros.
 * @details Specified setting for oversampling of Environment 6 Click driver.
 */
#define ENVIRONMENT6_OS_NONE                    0
#define ENVIRONMENT6_OS_1X                      1
#define ENVIRONMENT6_OS_2X                      2
#define ENVIRONMENT6_OS_4X                      3
#define ENVIRONMENT6_OS_8X                      4
#define ENVIRONMENT6_OS_16X                     5

/**
 * @brief Environment 6 IIR Filter settings.
 * @details Specified setting for IIR filter of Environment 6 Click driver.
 */
#define ENVIRONMENT6_FILTER_OFF                 0
#define ENVIRONMENT6_FILTER_SIZE_1              1
#define ENVIRONMENT6_FILTER_SIZE_3              2
#define ENVIRONMENT6_FILTER_SIZE_7              3
#define ENVIRONMENT6_FILTER_SIZE_15             4
#define ENVIRONMENT6_FILTER_SIZE_31             5
#define ENVIRONMENT6_FILTER_SIZE_63             6
#define ENVIRONMENT6_FILTER_SIZE_127            7

/**
 * @brief Environment 6 ODR/Standby time macros.
 * @details Specified setting for ODR/Standby time of Environment 6 Click driver.
 */
#define ENVIRONMENT6_ODR_0_59_MS                0
#define ENVIRONMENT6_ODR_62_5_MS                1
#define ENVIRONMENT6_ODR_125_MS                 2
#define ENVIRONMENT6_ODR_250_MS                 3
#define ENVIRONMENT6_ODR_500_MS                 4
#define ENVIRONMENT6_ODR_1000_MS                5
#define ENVIRONMENT6_ODR_10_MS                  6
#define ENVIRONMENT6_ODR_20_MS                  7
#define ENVIRONMENT6_ODR_NONE                   8

/**
 * @brief Environment 6 operating mode selection settings.
 * @details Specified setting for operating mode selection of Environment 6 Click driver.
 */
#define ENVIRONMENT6_MODE_SLEEP                 0x00
#define ENVIRONMENT6_MODE_FORCED                0x01
#define ENVIRONMENT6_MODE_MASK                  0x03

/**
 * @brief Environment 6 SPI page settings.
 * @details Specified setting for SPI memory page of Environment 6 Click driver.
 */
#define ENVIRONMENT6_MEM_PAGE_1                 0x00
#define ENVIRONMENT6_MEM_PAGE_0                 0x10
#define ENVIRONMENT6_MEM_PAGE_MASK              0x10
#define ENVIRONMENT6_MEM_PAGE_1_REG_MASK        0x80

/**
 * @brief Environment 6 buffer length macros.
 * @details Specified setting for buffer length of Environment 6 Click driver.
 */
#define ENVIRONMENT6_LEN_COEFF_ALL              42
#define ENVIRONMENT6_LEN_COEFF_1                23
#define ENVIRONMENT6_LEN_COEFF_2                14
#define ENVIRONMENT6_LEN_COEFF_3                5
#define ENVIRONMENT6_LEN_FIELD                  17
#define ENVIRONMENT6_LEN_CONFIG                 5

/**
 * @brief Environment 6 coefficient index macros.
 * @details Specified setting for coefficient index of Environment 6 Click driver.
 */
#define ENVIRONMENT6_COEFF_IDX_DTK1_C_LSB       0
#define ENVIRONMENT6_COEFF_IDX_DTK1_C_MSB       1
#define ENVIRONMENT6_COEFF_IDX_DTK2_C           2
#define ENVIRONMENT6_COEFF_IDX_S_C_LSB          4
#define ENVIRONMENT6_COEFF_IDX_S_C_MSB          5
#define ENVIRONMENT6_COEFF_IDX_TK1S_C_LSB       6
#define ENVIRONMENT6_COEFF_IDX_TK1S_C_MSB       7
#define ENVIRONMENT6_COEFF_IDX_TK2S_C           8
#define ENVIRONMENT6_COEFF_IDX_TK3S_C           9
#define ENVIRONMENT6_COEFF_IDX_O_C_LSB          10
#define ENVIRONMENT6_COEFF_IDX_O_C_MSB          11
#define ENVIRONMENT6_COEFF_IDX_TK10_C_LSB       12
#define ENVIRONMENT6_COEFF_IDX_TK10_C_MSB       13
#define ENVIRONMENT6_COEFF_IDX_TK20_C           14
#define ENVIRONMENT6_COEFF_IDX_TK30_C           15
#define ENVIRONMENT6_COEFF_IDX_NLS_C_LSB        18
#define ENVIRONMENT6_COEFF_IDX_NLS_C_MSB        19
#define ENVIRONMENT6_COEFF_IDX_TKNLS_C          20
#define ENVIRONMENT6_COEFF_IDX_NLS3_C           21
#define ENVIRONMENT6_COEFF_IDX_S_H_MSB          23
#define ENVIRONMENT6_COEFF_IDX_S_H_LSB          24
#define ENVIRONMENT6_COEFF_IDX_O_H_LSB          24
#define ENVIRONMENT6_COEFF_IDX_O_H_MSB          25
#define ENVIRONMENT6_COEFF_IDX_TK10H_C          26
#define ENVIRONMENT6_COEFF_IDX_PAR_H4           27
#define ENVIRONMENT6_COEFF_IDX_PAR_H3           28
#define ENVIRONMENT6_COEFF_IDX_HLIN2_C          29
#define ENVIRONMENT6_COEFF_IDX_TKHLIN2_C        30
#define ENVIRONMENT6_COEFF_IDX_DO_C_LSB         31
#define ENVIRONMENT6_COEFF_IDX_DO_C_MSB         32
#define ENVIRONMENT6_COEFF_IDX_TKR_C_LSB        33
#define ENVIRONMENT6_COEFF_IDX_TKR_C_MSB        34
#define ENVIRONMENT6_COEFF_IDX_RO_C             35
#define ENVIRONMENT6_COEFF_IDX_T_AMB_COMP       36
#define ENVIRONMENT6_COEFF_IDX_RES_HEAT_VAL     37
#define ENVIRONMENT6_COEFF_IDX_RES_HEAT_RANGE   39
#define ENVIRONMENT6_COEFF_IDX_RANGE_SW_ERR     41

/**
 * @brief Environment 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Environment 6 Click driver.
 */
#define ENVIRONMENT6_DEVICE_ADDRESS_0           0x76
#define ENVIRONMENT6_DEVICE_ADDRESS_1           0x77

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b environment6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ENVIRONMENT6_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define ENVIRONMENT6_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // environment6_set

/**
 * @defgroup environment6_map Environment 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Environment 6 Click driver.
 */

/**
 * @addtogroup environment6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Environment 6 Click to the selected MikroBUS.
 */
#define ENVIRONMENT6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // environment6_map
/*! @} */ // environment6

/**
 * @brief Environment 6 Click driver selector.
 * @details Selects target driver interface of Environment 6 Click driver.
 */
typedef enum
{
    ENVIRONMENT6_DRV_SEL_SPI,           /**< SPI driver descriptor. */
    ENVIRONMENT6_DRV_SEL_I2C            /**< I2C driver descriptor. */

} environment6_drv_t;

/**
 * @brief Environment 6 Click driver interface.
 * @details Definition of driver interface of Environment 6 Click driver.
 */
struct environment6_s;
typedef err_t ( *environment6_master_io_t )( struct environment6_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Environment 6 Click data object.
 * @details Data object definition of Environment 6 Click driver.
 */
typedef struct
{
    uint8_t status;                     /**< Contains new_data, gasm_valid and heat_stab. */
    uint8_t gas_index;                  /**< The index of the heater profile used. */
    uint8_t meas_index;                 /**< Measurement index to track order. */
    uint8_t res_heat;                   /**< Heater resistance. */
    uint8_t idac;                       /**< Current DAC. */
    uint8_t gas_wait;                   /**< Gas wait period. */
    float temperature;                  /**< Temperature in degree celsius. */
    float pressure;                     /**< Pressure in mBar. */
    float humidity;                     /**< Humidity in % relative humidity x1000. */
    float gas_resistance;               /**< Gas resistance in Ohms. */

} environment6_data_t;

/**
 * @brief Environment 6 Click heater settings object.
 * @details Gas heater setting object definition of Environment 6 Click driver.
 */
typedef struct
{
    uint8_t enable;                     /**< Enable gas measurement. */
    uint16_t heater_temp;               /**< Store the heater temperature for forced mode degree Celsius. */
    uint16_t heater_dur;                /**< Store the heating duration for forced mode in milliseconds. */

} environment6_gas_conf_t;

/**
 * @brief Environment 6 Click sensor settings object.
 * @details ODR, over-sampling and filter sensor object definition of Environment 6 Click driver.
 */
typedef struct
{
    uint8_t os_hum;                     /**< Humidity oversampling. */
    uint8_t os_temp;                    /**< Temperature oversampling. */
    uint8_t os_pres;                    /**< Pressure oversampling. */
    uint8_t filter;                     /**< Filter coefficient. */
    uint8_t odr;                        /**< Standby time between sequential mode measurement profiles. */

} environment6_sen_conf_t;

/**
 * @brief Environment 6 Click calibration data object.
 * @details Calibration data object definition of Environment 6 Click driver.
 */
typedef struct
{
    /**< Calibration coefficients for the humidity sensor. */
    int16_t par_h1;
    int8_t par_h2;
    uint8_t par_h3;
    int8_t par_h4;
    int16_t par_h5;
    uint8_t par_h6;

    /**< Calibration coefficient for the gas sensor. */
    int8_t par_g1;
    int16_t par_g2;
    int8_t par_g3;

    /**< Calibration coefficient for the temperature sensor. */
    uint16_t par_t1;
    uint16_t par_t2;
    int8_t par_t3;

    /**< Calibration coefficient for the pressure sensor. */
    int16_t par_p5;
    int16_t par_p6;
    int8_t par_p7;
    int8_t par_p8;
    uint16_t par_p1;
    uint16_t par_p2;
    int8_t par_p3;
    int8_t par_p4;
    int16_t par_p9;
    int8_t par_p10;
    int8_t par_p11;

    /**< Variable to store the intermediate temperature coefficient. */
    float t_fine;

    /**< Heater resistance range coefficient. */
    uint8_t res_heat_range;

    /**< Heater resistance value coefficient. */
    int8_t res_heat_val;

    /**< Gas resistance range switching error coefficient. */
    int8_t range_sw_err;

} environment6_calib_data_t;

/**
 * @brief Environment 6 Click context object.
 * @details Context object definition of Environment 6 Click driver.
 */
typedef struct environment6_s
{
    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    environment6_drv_t drv_sel;         /**< Master driver interface selector. */

    environment6_master_io_t write_f;   /**< Master write function. */
    environment6_master_io_t read_f;    /**< Master read function. */

    uint8_t spi_mem_page;               /**< SPI memory page setting. */
    environment6_calib_data_t calib;    /**< Sensor calibration data. */
    environment6_sen_conf_t sen_conf;   /**< Sensor ODR, SR, and Filter settings. */
    environment6_gas_conf_t gas_conf;   /**< Gas heater settings. */

} environment6_t;

/**
 * @brief Environment 6 Click configuration object.
 * @details Configuration object definition of Environment 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    environment6_drv_t drv_sel;         /**< Master driver interface selector. */

} environment6_cfg_t;

/**
 * @brief Environment 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ENVIRONMENT6_OK = 0,
    ENVIRONMENT6_ERROR = -1

} environment6_return_value_t;

/*!
 * @addtogroup environment6 Environment 6 Click Driver
 * @brief API for configuring and manipulating Environment 6 Click driver.
 * @{
 */

/**
 * @brief Environment 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #environment6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void environment6_cfg_setup ( environment6_cfg_t *cfg );

/**
 * @brief Environment 6 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #environment6_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #environment6_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void environment6_drv_interface_sel ( environment6_cfg_t *cfg, environment6_drv_t drv_sel );

/**
 * @brief Environment 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #environment6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment6_init ( environment6_t *ctx, environment6_cfg_t *cfg );

/**
 * @brief Environment 6 default configuration function.
 * @details This function executes a default configuration of Environment 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t environment6_default_cfg ( environment6_t *ctx );

/**
 * @brief Environment 6 Write Multiple Registers function.
 * @details This function writes a sequence of bytes starting from the selected register address.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment6_write_regs ( environment6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Environment 6 Read Multiple Registers function.
 * @details This function reads a sequence of bytes starting from the selected register address.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment6_read_regs ( environment6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Environment 6 Write Single Register function.
 * @details This function writes a single byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Byte of data to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment6_write_reg ( environment6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Environment 6 Read Single Register function.
 * @details This function reads a single byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the byte to store read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment6_read_reg ( environment6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Environment 6 Software Reset function.
 * @details This function performs a software reset of the device.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note A delay of 10ms is required after reset.
 */
err_t environment6_soft_reset ( environment6_t *ctx );

/**
 * @brief Environment 6 Check Communication function.
 * @details This function checks device communication by reading the chip ID.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment6_check_comm ( environment6_t *ctx );

/**
 * @brief Environment 6 Set Operating Mode function.
 * @details This function sets the sensor?s operating mode.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] op_mode : Desired operating mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Forces sleep mode before changing to the selected mode.
 */
err_t environment6_set_op_mode ( environment6_t *ctx, uint8_t op_mode );

/**
 * @brief Environment 6 Get Operating Mode function.
 * @details This function reads the current operating mode of the sensor.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[out] op_mode : Pointer to store the current operating mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment6_get_op_mode ( environment6_t *ctx, uint8_t *op_mode );

/**
 * @brief Environment 6 Set Sensor Configuration function.
 * @details This function configures the sensor oversampling, filter, and data rate.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] conf : Sensor configuration structure.
 * See #environment6_sen_conf_t object definition for details.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Device must be in sleep mode before applying configuration.
 */
err_t environment6_set_sensor_conf ( environment6_t *ctx, environment6_sen_conf_t *conf );

/**
 * @brief Environment 6 Set Gas Configuration function.
 * @details This function sets the heater temperature, duration, and enables gas measurements.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[in] conf : Gas configuration structure.
 * See #environment6_gas_conf_t object definition for details.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Device must be in sleep mode before applying configuration.
 */
err_t environment6_set_gas_conf ( environment6_t *ctx, environment6_gas_conf_t *conf );

/**
 * @brief Environment 6 Get Sensor Data function.
 * @details This function triggers a measurement and reads temperature, pressure, humidity, and gas resistance data.
 * @param[in] ctx : Click context object.
 * See #environment6_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to data output structure.
 * See #environment6_data_t object definition for details.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Delays are handled internally based on oversampling and heater duration settings.
 */
err_t environment6_get_data ( environment6_t *ctx, environment6_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ENVIRONMENT6_H

/*! @} */ // environment6

// ------------------------------------------------------------------------ END
