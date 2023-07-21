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
 * @file environment3.h
 * @brief This file contains API for Environment 3 Click Driver.
 */

#ifndef ENVIRONMENT3_H
#define ENVIRONMENT3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup environment3 Environment 3 Click Driver
 * @brief API for configuring and manipulating Environment 3 Click driver.
 * @{
 */

/**
 * @defgroup environment3_reg Environment 3 Registers List
 * @brief List of registers of Environment 3 Click driver.
 */

/**
 * @addtogroup environment3_reg
 * @{
 */

/**
 * @brief Environment 3 memory map summary.
 * @details The full list of registers.
 */
#define ENVIRONMENT3_REG_STATUS                 0x73
#define ENVIRONMENT3_REG_VARIANT_ID             0xF0
#define ENVIRONMENT3_REG_RESET                  0xE0
#define ENVIRONMENT3_REG_CHIP_ID                0xD0
#define ENVIRONMENT3_REG_CONFIG                 0x75
#define ENVIRONMENT3_REG_CTRL_MEAS              0x74
#define ENVIRONMENT3_REG_CTRL_HUM               0x72
#define ENVIRONMENT3_REG_CTRL_GAS_1             0x71
#define ENVIRONMENT3_REG_CTRL_GAS_0             0x70
#define ENVIRONMENT3_REG_GAS_WAIT_SHARED        0x6E
#define ENVIRONMENT3_REG_GAS_WAIT_0             0x64
#define ENVIRONMENT3_REG_RES_HEAT_0             0x5A
#define ENVIRONMENT3_REG_IDAC_HEAT_0            0x50
#define ENVIRONMENT3_REG_GAS_R_LSB_FIELD_2      0x4F
#define ENVIRONMENT3_REG_GAS_R_MSB_FIELD_2      0x4E
#define ENVIRONMENT3_REG_HUM_LSB_FIELD_2        0x48
#define ENVIRONMENT3_REG_HUM_MSB_FIELD_2        0x47
#define ENVIRONMENT3_REG_TEMP_XLSB_FIELD_2      0x46
#define ENVIRONMENT3_REG_TEMP_LSB_FIELD_2       0x45
#define ENVIRONMENT3_REG_TEMP_MSB_FIELD_2       0x44
#define ENVIRONMENT3_REG_PRESS_XLSB_FIELD_2     0x43
#define ENVIRONMENT3_REG_PRESS_LSB_FIELD_2      0x42
#define ENVIRONMENT3_REG_PRESS_MSB_FIELD_2      0x41
#define ENVIRONMENT3_REG_SUB_MEAS_INDEX_FIELD_2 0x40
#define ENVIRONMENT3_REG_MEAS_STATUS_FIELD_2    0x3F
#define ENVIRONMENT3_REG_GAS_R_LSB_FIELD_1      0x3E
#define ENVIRONMENT3_REG_GAS_R_MSB_FIELD_1      0x3D
#define ENVIRONMENT3_REG_HUM_LSB_FIELD_1        0x37
#define ENVIRONMENT3_REG_HUM_MSB_FIELD_1        0x36
#define ENVIRONMENT3_REG_TEMP_XLSB_FIELD_1      0x35
#define ENVIRONMENT3_REG_TEMP_LSB_FIELD_1       0x34
#define ENVIRONMENT3_REG_TEMP_MSB_FIELD_1       0x33
#define ENVIRONMENT3_REG_PRESS_XLSB_FIELD_1     0x32
#define ENVIRONMENT3_REG_PRESS_LSB_FIELD_1      0x31
#define ENVIRONMENT3_REG_PRESS_MSB_FIELD_1      0x30
#define ENVIRONMENT3_REG_SUB_MEAS_INDEX_FIELD_1 0x2F
#define ENVIRONMENT3_REG_MEAS_STATUS_FIELD_1    0x2E
#define ENVIRONMENT3_REG_GAS_R_LSB_FIELD_0      0x2D
#define ENVIRONMENT3_REG_GAS_R_MSB_FIELD_0      0x2C
#define ENVIRONMENT3_REG_HUM_LSB_FIELD_0        0x26
#define ENVIRONMENT3_REG_HUM_MSB_FIELD_0        0x25
#define ENVIRONMENT3_REG_TEMP_XLSB_FIELD_0      0x24
#define ENVIRONMENT3_REG_TEMP_LSB_FIELD_0       0x23
#define ENVIRONMENT3_REG_TEMP_MSB_FIELD_0       0x22
#define ENVIRONMENT3_REG_PRESS_XLSB_FIELD_0     0x21
#define ENVIRONMENT3_REG_PRESS_LSB_FIELD_0      0x20
#define ENVIRONMENT3_REG_PRESS_MSB_FIELD_0      0x1F
#define ENVIRONMENT3_REG_SUB_MEAS_INDEX_FIELD_0 0x1E
#define ENVIRONMENT3_REG_MEAS_STATUS_FIELD_0    0x1D
#define ENVIRONMENT3_REG_MEM_PAGE               0xF3
#define ENVIRONMENT3_REG_UNIQUE_ID              0x83
#define ENVIRONMENT3_REG_COEFF_1                0x8A
#define ENVIRONMENT3_REG_COEFF_2                0xE1
#define ENVIRONMENT3_REG_COEFF_3                0x00

/*! @} */ // environment3_reg

/**
 * @defgroup environment3_set Environment 3 Registers Settings
 * @brief Settings for registers of Environment 3 Click driver.
 */

/**
 * @addtogroup environment3_set
 * @{
 */

/**
 * @brief Environment 3 chip ID.
 * @details Unique chip ID value.
 */
#define ENVIRONMENT3_CHIP_ID                0x61

/**
 * @brief Environment 3 reset settings.
 * @details Reset setting.
 */
#define ENVIRONMENT3_SOFT_RESET             0xB6

/**
 * @brief Environment 3 errors summary.
 * @details The list of errors.
 */
#define ENVIRONMENT3_E_NULL_PTR             -2
#define ENVIRONMENT3_E_COM_FAIL             -3
#define ENVIRONMENT3_E_INVALID_LENGTH       -4
#define ENVIRONMENT3_W_DEFINE_OP_MODE       1
#define ENVIRONMENT3_W_NO_NEW_DATA          2

/**
 * @brief Environment 3 register mask summary.
 * @details The list of register masks.
 */
#define ENVIRONMENT3_NBCONV_MASK            0x0F
#define ENVIRONMENT3_FILTER_MASK            0x1C
#define ENVIRONMENT3_ODR3_MASK              0x80
#define ENVIRONMENT3_ODR20_MASK             0xE0
#define ENVIRONMENT3_OST_MASK               0xE0
#define ENVIRONMENT3_OSP_MASK               0x1C
#define ENVIRONMENT3_OSH_MASK               0x07
#define ENVIRONMENT3_HCTRL_MASK             0x08
#define ENVIRONMENT3_RUN_GAS_MASK           0x30
#define ENVIRONMENT3_MODE_MASK              0x03
#define ENVIRONMENT3_RHRANGE_MASK           0x30
#define ENVIRONMENT3_RSERROR_MASK           0xF0
#define ENVIRONMENT3_NEW_DATA_MASK          0x80
#define ENVIRONMENT3_GAS_INDEX_MASK         0x0F
#define ENVIRONMENT3_GAS_RANGE_MASK         0x0F
#define ENVIRONMENT3_GASM_VALID_MASK        0x20
#define ENVIRONMENT3_HEAT_STAB_MASK         0x10
#define ENVIRONMENT3_MEM_PAGE_MASK          0x10
#define ENVIRONMENT3_BIT_H1_DATA_MASK       0x0F
#define ENVIRONMENT3_HUM_REG_SHIFT_VAL_MASK 0x04
#define ENVIRONMENT3_SPI_READ_MASK          0x80
#define ENVIRONMENT3_SPI_WRITE_MASK         0x7F

/**
 * @brief Environment 3 register bit position summary.
 * @details The list of bit position masks.
 */
#define ENVIRONMENT3_FILTER_POS             2
#define ENVIRONMENT3_OST_POS                5
#define ENVIRONMENT3_OSP_POS                2
#define ENVIRONMENT3_ODR3_POS               7
#define ENVIRONMENT3_ODR20_POS              5
#define ENVIRONMENT3_RUN_GAS_POS            4
#define ENVIRONMENT3_HCTRL_POS              3

/**
 * @brief Environment 3 enable/disable macros.
 * @details Enable/disable macros.
 */
#define ENVIRONMENT3_ENABLE                 0x01
#define ENVIRONMENT3_DISABLE                0x00
#define ENVIRONMENT3_ENABLE_HEATER          0x00
#define ENVIRONMENT3_DISABLE_HEATER         0x01
#define ENVIRONMENT3_ENABLE_GAS_MEAS_H      0x02
#define ENVIRONMENT3_ENABLE_GAS_MEAS_L      0x01
#define ENVIRONMENT3_DISABLE_GAS_MEAS       0x00

/**
 * @brief Environment 3 variant ID macros.
 * @details Variant ID macros.
 */
#define ENVIRONMENT3_VARIANT_GAS_LOW        0x00
#define ENVIRONMENT3_VARIANT_GAS_HIGH       0x01

/**
 * @brief Environment 3 oversampling setting macros.
 * @details Oversampling setting macros.
 */
#define ENVIRONMENT3_OS_NONE                0
#define ENVIRONMENT3_OS_1X                  1
#define ENVIRONMENT3_OS_2X                  2
#define ENVIRONMENT3_OS_4X                  3
#define ENVIRONMENT3_OS_8X                  4
#define ENVIRONMENT3_OS_16X                 5

/**
 * @brief Environment 3 IIR Filter settings.
 * @details IIR Filter settings.
 */
#define ENVIRONMENT3_FILTER_OFF             0
#define ENVIRONMENT3_FILTER_SIZE_1          1
#define ENVIRONMENT3_FILTER_SIZE_3          2
#define ENVIRONMENT3_FILTER_SIZE_7          3
#define ENVIRONMENT3_FILTER_SIZE_15         4
#define ENVIRONMENT3_FILTER_SIZE_31         5
#define ENVIRONMENT3_FILTER_SIZE_63         6
#define ENVIRONMENT3_FILTER_SIZE_127        7

/**
 * @brief Environment 3 ODR/Standby time macros.
 * @details ODR/Standby time macros.
 */
#define ENVIRONMENT3_ODR_0_59_MS            0
#define ENVIRONMENT3_ODR_62_5_MS            1
#define ENVIRONMENT3_ODR_125_MS             2
#define ENVIRONMENT3_ODR_250_MS             3
#define ENVIRONMENT3_ODR_500_MS             4
#define ENVIRONMENT3_ODR_1000_MS            5
#define ENVIRONMENT3_ODR_10_MS              6
#define ENVIRONMENT3_ODR_20_MS              7
#define ENVIRONMENT3_ODR_NONE               8

/**
 * @brief Environment 3 operating mode selection settings.
 * @details Operating mode selection setting.
 */
#define ENVIRONMENT3_MODE_SLEEP             0
#define ENVIRONMENT3_MODE_FORCED            1

/**
 * @brief Environment 3 SPI page settings.
 * @details SPI memory page setting.
 */
#define ENVIRONMENT3_MEM_PAGE_0             0x10
#define ENVIRONMENT3_MEM_PAGE_1             0x00

/**
 * @brief Environment 3 buffer length macros.
 * @details Buffer length.
 */
#define ENVIRONMENT3_LEN_COEFF_ALL          42
#define ENVIRONMENT3_LEN_COEFF_1            23
#define ENVIRONMENT3_LEN_COEFF_2            14
#define ENVIRONMENT3_LEN_COEFF_3            5
#define ENVIRONMENT3_LEN_FIELD              17
#define ENVIRONMENT3_LEN_CONFIG             5
#define ENVIRONMENT3_LEN_INTERLEAVE_BUFF    20

/**
 * @brief Environment 3 coefficient index macros.
 * @details Coefficient index setting.
 */
#define ENVIRONMENT3_IDX_T2_LSB             0
#define ENVIRONMENT3_IDX_T2_MSB             1
#define ENVIRONMENT3_IDX_T3                 2
#define ENVIRONMENT3_IDX_P1_LSB             4
#define ENVIRONMENT3_IDX_P1_MSB             5
#define ENVIRONMENT3_IDX_P2_LSB             6
#define ENVIRONMENT3_IDX_P2_MSB             7
#define ENVIRONMENT3_IDX_P3                 8
#define ENVIRONMENT3_IDX_P4_LSB             10
#define ENVIRONMENT3_IDX_P4_MSB             11
#define ENVIRONMENT3_IDX_P5_LSB             12
#define ENVIRONMENT3_IDX_P5_MSB             13
#define ENVIRONMENT3_IDX_P7                 14
#define ENVIRONMENT3_IDX_P6                 15
#define ENVIRONMENT3_IDX_P8_LSB             18
#define ENVIRONMENT3_IDX_P8_MSB             19
#define ENVIRONMENT3_IDX_P9_LSB             20
#define ENVIRONMENT3_IDX_P9_MSB             21
#define ENVIRONMENT3_IDX_P10                22
#define ENVIRONMENT3_IDX_H2_MSB             23
#define ENVIRONMENT3_IDX_H2_LSB             24
#define ENVIRONMENT3_IDX_H1_LSB             24
#define ENVIRONMENT3_IDX_H1_MSB             25
#define ENVIRONMENT3_IDX_H3                 26
#define ENVIRONMENT3_IDX_H4                 27
#define ENVIRONMENT3_IDX_H5                 28
#define ENVIRONMENT3_IDX_H6                 29
#define ENVIRONMENT3_IDX_H7                 30
#define ENVIRONMENT3_IDX_T1_LSB             31
#define ENVIRONMENT3_IDX_T1_MSB             32
#define ENVIRONMENT3_IDX_GH2_LSB            33
#define ENVIRONMENT3_IDX_GH2_MSB            34
#define ENVIRONMENT3_IDX_GH1                35
#define ENVIRONMENT3_IDX_GH3                36
#define ENVIRONMENT3_IDX_RES_HEAT_VAL       37
#define ENVIRONMENT3_IDX_RES_HEAT_RANGE     39
#define ENVIRONMENT3_IDX_RANGE_SW_ERR       41

/**
 * @brief Environment 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Environment 3 Click driver.
 */
#define ENVIRONMENT3_DEVICE_SLAVE_ADDR_0    0x76
#define ENVIRONMENT3_DEVICE_SLAVE_ADDR_1    0x77

/*! @} */ // environment3_set

/**
 * @defgroup environment3_map Environment 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Environment 3 Click driver.
 */

/**
 * @addtogroup environment3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Environment 3 Click to the selected MikroBUS.
 */
#define ENVIRONMENT3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \

/*! @} */ // environment3_map
/*! @} */ // environment3

/**
 * @brief Environment 3 Click driver selector.
 * @details Selects target driver interface of Environment 3 Click driver.
 */
typedef enum
{
    ENVIRONMENT3_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    ENVIRONMENT3_DRV_SEL_I2C       /**< I2C driver descriptor. */

} environment3_drv_t;

/**
 * @brief Environment 3 Click driver interface.
 * @details Definition of driver interface of Environment 3 Click driver.
 */
typedef err_t ( *environment3_master_io_t )( struct environment3_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Environment 3 field data structure.
 * @details Field data structure definition.
 */
typedef struct
{
    uint8_t status;
    uint8_t gas_index;
    uint8_t meas_index;
    uint8_t res_heat;
    uint8_t idac;
    uint8_t gas_wait;
    float temperature;
    float pressure;
    float humidity;
    float gas_resistance;
    
} environment3_field_data_t;

/**
 * @brief Environment 3 calibration data structure.
 * @details Calibration data structure definition.
 */
typedef struct
{
    uint16_t par_h1;
    uint16_t par_h2;
    int8_t par_h3;
    int8_t par_h4;
    int8_t par_h5;
    uint8_t par_h6;
    int8_t par_h7;
    int8_t par_gh1;
    int16_t par_gh2;
    int8_t par_gh3;
    uint16_t par_t1;
    int16_t par_t2;
    int8_t par_t3;
    uint16_t par_p1;
    int16_t par_p2;
    int8_t par_p3;
    int16_t par_p4;
    int16_t par_p5;
    int8_t par_p6;
    int8_t par_p7;
    int16_t par_p8;
    int16_t par_p9;
    uint8_t par_p10;
    float t_fine;
    uint8_t res_heat_range;
    int8_t res_heat_val;
    int8_t range_sw_err;
    
} environment3_calibration_data_t;

/**
 * @brief Environment 3 TPH settings structure.
 * @details Temperature, pressure, humidity settings structure definition.
 */
typedef struct
{
    uint8_t os_hum;
    uint8_t os_temp;
    uint8_t os_pres;
    uint8_t filter;
    uint8_t odr;
    
} environment3_tph_settings_t;

/**
 * @brief Environment 3 gas settings structure.
 * @details gas settings structure definition.
 */
typedef struct
{
    uint8_t enable;
    uint16_t heater_temp;
    uint16_t heater_dur;

} environment3_gas_settings_t;

/**
 * @brief Environment 3 Click context object.
 * @details Context object definition of Environment 3 Click driver.
 */
typedef struct environment3_s
{
    i2c_master_t  i2c;                              /**< I2C driver object. */
    spi_master_t  spi;                              /**< SPI driver object. */

    uint8_t     slave_address;                      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                        /**< Chip select pin descriptor (used for SPI driver). */
    environment3_drv_t  drv_sel;                    /**< Master driver interface selector. */

    environment3_master_io_t  write_f;              /**< Master write function. */
    environment3_master_io_t  read_f;               /**< Master read function. */
    
    environment3_field_data_t f_data;
    environment3_calibration_data_t calib;
    environment3_tph_settings_t tph_sett;
    environment3_gas_settings_t gas_sett;

    uint8_t device_mem_page;
    uint8_t device_variant_id;

} environment3_t;

/**
 * @brief Environment 3 Click configuration object.
 * @details Configuration object definition of Environment 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    environment3_drv_t  drv_sel;                        /**< Master driver interface selector. */

} environment3_cfg_t;

/**
 * @brief Environment 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ENVIRONMENT3_OK = 0,
    ENVIRONMENT3_ERROR = -1

} environment3_return_value_t;

/*!
 * @addtogroup environment3 Environment 3 Click Driver
 * @brief API for configuring and manipulating Environment 3 Click driver.
 * @{
 */

/**
 * @brief Environment 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #environment3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void environment3_cfg_setup ( environment3_cfg_t *cfg );

/**
 * @brief Environment 3 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #environment3_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #environment3_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void environment3_drv_interface_selection ( environment3_cfg_t *cfg, environment3_drv_t drv_sel );

/**
 * @brief Environment 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #environment3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment3_init ( environment3_t *ctx, environment3_cfg_t *cfg );

/**
 * @brief Environment 3 default configuration function.
 * @details This function executes a default configuration of Environment 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t environment3_default_cfg ( environment3_t *ctx );

/**
 * @brief Environment 3 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment3_generic_write ( environment3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Environment 3 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment3_generic_read ( environment3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Environment 3 single data writing function.
 * @details This function writes a single data byte to the desired register.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment3_write_byte ( environment3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Environment 3 single data reading function.
 * @details This function reads a single data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @return Read data byte.
 * @note None.
 */
uint8_t environment3_read_byte ( environment3_t *ctx, uint8_t reg );

/**
 * @brief Environment 3 check device ID function.
 * @details This function checks the device ID.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  0 - ID correct,
 *         @li @c -1 - Wrong ID read.
 * @note None.
 */
int8_t environment3_check_id ( environment3_t *ctx );

/**
 * @brief Environment 3 get device ID function.
 * @details This function gets the device ID.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return Device ID.
 * @note None.
 */
uint8_t environment3_get_device_id ( environment3_t *ctx );

/**
 * @brief Environment 3 soft reset function.
 * @details This function soft-resets the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
int8_t environment3_soft_reset ( environment3_t *ctx );

/**
 * @brief Environment 3 get all data function.
 * @details This function reads the temperature, humidity, pressure, and gas resistance data
 * from the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[out] temp : Temperature value in Celsius.
 * @param[out] hum : Temperature value in Percents.
 * @param[out] pres : Pressure value in mBar.
 * @param[out] gas : Gas resistance value in Ohms.
 * @return @li @c  2 - No new data.
 *         @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
int8_t environment3_get_all_data ( environment3_t *ctx, float *temp, float *hum, float *pres, uint32_t *gas );

/**
 * @brief Environment 3 get temperature data function.
 * @details This function reads the temperature from the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  2.0 - No new data.
 *         @li @c -1.0 - Error.
 *         @li - Temperature value in Celsius.
 * @note None.
 */
float environment3_get_temperature ( environment3_t *ctx );

/**
 * @brief Environment 3 get humidity data function.
 * @details This function reads the humidity from the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  2.0 - No new data.
 *         @li @c -1.0 - Error.
 *         @li - Humidity value in Percents.
 * @note None.
 */
float environment3_get_humidity ( environment3_t *ctx );

/**
 * @brief Environment 3 get pressure data function.
 * @details This function reads the pressure from the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  2.0 - No new data.
 *         @li @c -1.0 - Error.
 *         @li - Pressure value in mBar.
 * @note None.
 */
float environment3_get_pressure ( environment3_t *ctx );

/**
 * @brief Environment 3 get gas resistance data function.
 * @details This function reads the gas resistance from the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @return @li @c  2.0 - No new data.
 *         @li @c -1.0 - Error.
 *         @li - Gas resistance value in Ohms.
 * @note None.
 */
float environment3_get_gas_resistance ( environment3_t *ctx );

/**
 * @brief Environment 3 read data from register address function.
 * @details This function reads the desired number of data bytes starting from 
 * the given register address of sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Communication fail.
 * @note None.
 */
int8_t environment3_get_regs ( environment3_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief Environment 3 write data to registers function.
 * @details This function writes the desired number of data bytes to registers starting from 
 * the given register address of sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] reg : Array of registers addresses.
 * @param[in] data_in : Array of data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Communication fail.
 *         @li @c -3 - Invalid length.
 * @note The length of reg and data_in arrays must be the same.
 */
int8_t environment3_set_regs ( environment3_t *ctx, uint8_t *reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Environment 3 enable heater function.
 * @details This function enables or disables the gas sensor heater.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] state : 1 - Enable, 0 - Disable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Communication fail.
 * @note None.
 */
int8_t environment3_enable_heater ( environment3_t *ctx, uint8_t state );

/**
 * @brief Environment 3 set heater configuration function.
 * @details This function sets the gas configuration of the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] conf : Gas setting object.
 * See #environment3_gas_settings_t gas setting object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Communication fail.
 * @note None.
 */
int8_t environment3_set_heater_conf ( environment3_t *ctx, environment3_gas_settings_t *conf );

/**
 * @brief Environment 3 set sensor configuration function.
 * @details This function sets the oversampling, filter and odr configuration of the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] conf : THP setting object.
 * See #environment3_tph_settings_t TPH setting object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Communication fail.
 * @note None.
 */
int8_t environment3_set_sensor_conf ( environment3_t *ctx, environment3_tph_settings_t *conf );

/**
 * @brief Environment 3 set operating mode function.
 * @details This function sets the operating mode of the sensor ( FORCED or SLEEP ).
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] op_mode : 0 - SLEEP, 1 - FORCED.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Communication fail.
 * @note None.
 */
int8_t environment3_set_operating_mode ( environment3_t *ctx, uint8_t op_mode );

/**
 * @brief Environment 3 get operating mode function.
 * @details This function gets the operating mode of the sensor.
 * @param[in] ctx : Click context object.
 * See #environment3_t object definition for detailed explanation.
 * @param[in] op_mode : 0 - SLEEP, 1 - FORCED.
 * @return @li @c -1 - Error.
 *         @li - Operating mode.
 * @note None.
 */
int8_t environment3_get_operating_mode ( environment3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ENVIRONMENT3_H

/*! @} */ // environment3

// ------------------------------------------------------------------------ END
