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
 * @file pressure2307ba.h
 * @brief This file contains API for Pressure 23 07BA Click Driver.
 */

#ifndef PRESSURE2307BA_H
#define PRESSURE2307BA_H

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
 * @addtogroup pressure2307ba Pressure 23 07BA Click Driver
 * @brief API for configuring and manipulating Pressure 23 07BA Click driver.
 * @{
 */

/**
 * @defgroup pressure2307ba_reg Pressure 23 07BA Registers List
 * @brief List of registers of Pressure 23 07BA Click driver.
 */

/**
 * @addtogroup pressure2307ba_reg
 * @{
 */

/**
 * @brief Pressure 23 07BA description register.
 * @details Specified register for description of Pressure 23 07BA Click driver.
 */
#define PRESSURE2307BA_REG_SERIAL_NUMBER_MSB         0x02
#define PRESSURE2307BA_REG_SERIAL_NUMBER_LSB         0x03
#define PRESSURE2307BA_REG_COEF_C1                   0x04
#define PRESSURE2307BA_REG_COEF_C2                   0x05
#define PRESSURE2307BA_REG_COEF_C3                   0x06
#define PRESSURE2307BA_REG_COEF_C4                   0x07
#define PRESSURE2307BA_REG_COEF_C5                   0x08
#define PRESSURE2307BA_REG_COEF_C6                   0x09
#define PRESSURE2307BA_REG_COEF_C7                   0x0A
#define PRESSURE2307BA_REG_COEF_C8                   0x0B
#define PRESSURE2307BA_REG_COEF_C5_C4_MSB            0x0C
#define PRESSURE2307BA_REG_COEF_C8_C6_MSB            0x0D
#define PRESSURE2307BA_REG_PROM_ID_CRC               0x0F

/*! @} */ // pressure2307ba_reg

/**
 * @defgroup pressure2307ba_cmd Pressure 23 07BA Command List
 * @brief List of commands of Pressure 23 07BA Click driver.
 */

/**
 * @addtogroup pressure2307ba_cmd
 * @{
 */

/**
 * @brief Pressure 23 07BA description command.
 * @details Specified command for description of Pressure 23 07BA Click driver.
 */
#define PRESSURE2307BA_CMD_RESET                     0x10
#define PRESSURE2307BA_CMD_WRITE_CONFIG_PRESS        0x20
#define PRESSURE2307BA_CMD_WRITE_CONFIG_TEMP         0x22
#define PRESSURE2307BA_CMD_READ_CONFIG_PRESS         0x28
#define PRESSURE2307BA_CMD_READ_CONFIG_TEMP          0x2A
#define PRESSURE2307BA_CMD_READ_MEMORY               0xE0
#define PRESSURE2307BA_CMD_START_CONVERSION          0x40
#define PRESSURE2307BA_CMD_START_CONVERSION_PRESS    0x44
#define PRESSURE2307BA_CMD_START_CONVERSION_TEMP     0x48
#define PRESSURE2307BA_CMD_READ_ADC_REG              0x50
#define PRESSURE2307BA_CMD_READ_ADC_REG_PRESS        0x54
#define PRESSURE2307BA_CMD_READ_ADC_REG_TEMP         0x58
#define PRESSURE2307BA_CMD_WRITE_OPERATION_REG       0x14
#define PRESSURE2307BA_CMD_READ_OPERATION_REG        0x16
#define PRESSURE2307BA_CMD_WRITE_INTERRUPT_MASK      0x18
#define PRESSURE2307BA_CMD_READ_INTERRUPT_MASK       0x1A
#define PRESSURE2307BA_CMD_WRITE_INTERRUPT_REG       0x1C
#define PRESSURE2307BA_CMD_READ_INTERRUPT_REG        0x1E
#define PRESSURE2307BA_CMD_WRITE_LIMIT_REG_TEMP_L    0x30
#define PRESSURE2307BA_CMD_WRITE_LIMIT_REG_TEMP_H    0x32
#define PRESSURE2307BA_CMD_WRITE_LIMIT_REG_PRESS_L   0x34
#define PRESSURE2307BA_CMD_WRITE_LIMIT_REG_PRESS_H   0x36
#define PRESSURE2307BA_CMD_READ_LIMIT_REG_TEMP_L     0x38
#define PRESSURE2307BA_CMD_READ_LIMIT_REG_TEMP_H     0x3A
#define PRESSURE2307BA_CMD_READ_LIMIT_REG_PRESS_L    0x3C
#define PRESSURE2307BA_CMD_READ_LIMIT_REG_PRESS_H    0x3E

/*! @} */ // pressure2307ba_cmd

/**
 * @defgroup pressure2307ba_set Pressure 23 07BA Registers Settings
 * @brief Settings for registers of Pressure 23 07BA Click driver.
 */

/**
 * @addtogroup pressure2307ba_set
 * @{
 */

/**
 * @brief Pressure 23 07BA description of sensor configuration data.
 * @details Specified sensor configuration data of Pressure 23 07BA Click driver.
 */
#define PRESSURE2307BA_SNSR_CFG_SEL_PRESS           0x00
#define PRESSURE2307BA_SNSR_CFG_SEL_TEMP            0x01
#define PRESSURE2307BA_SNSR_CFG_SEL_BIT_MASK        0x01
#define PRESSURE2307BA_SNSR_CFG_RATIO_OFF           0x00
#define PRESSURE2307BA_SNSR_CFG_RATIO_1             0x01
#define PRESSURE2307BA_SNSR_CFG_RATIO_2             0x02
#define PRESSURE2307BA_SNSR_CFG_RATIO_4             0x03
#define PRESSURE2307BA_SNSR_CFG_RATIO_8             0x04
#define PRESSURE2307BA_SNSR_CFG_RATIO_16            0x05
#define PRESSURE2307BA_SNSR_CFG_RATIO_32            0x06
#define PRESSURE2307BA_SNSR_CFG_RATIO_BIT_MASK      0x07
#define PRESSURE2307BA_SNSR_CFG_FILTER_OFF          0x00
#define PRESSURE2307BA_SNSR_CFG_FILTER_2            0x01
#define PRESSURE2307BA_SNSR_CFG_FILTER_4            0x02
#define PRESSURE2307BA_SNSR_CFG_FILTER_8            0x03
#define PRESSURE2307BA_SNSR_CFG_FILTER_16           0x04
#define PRESSURE2307BA_SNSR_CFG_FILTER_32           0x05
#define PRESSURE2307BA_SNSR_CFG_FILTER_BIT_MASK     0x07
#define PRESSURE2307BA_SNSR_CFG_RES_24_BIT          0x00
#define PRESSURE2307BA_SNSR_CFG_RES_16_BIT          0x01
#define PRESSURE2307BA_SNSR_CFG_RES_8_BIT           0x02
#define PRESSURE2307BA_SNSR_CFG_RES_BIT_MASK        0x03
#define PRESSURE2307BA_SNSR_CFG_OSR_0               0x00
#define PRESSURE2307BA_SNSR_CFG_OSR_1               0x01
#define PRESSURE2307BA_SNSR_CFG_OSR_2               0x02
#define PRESSURE2307BA_SNSR_CFG_OSR_3               0x03
#define PRESSURE2307BA_SNSR_CFG_OSR_4               0x04
#define PRESSURE2307BA_SNSR_CFG_OSR_5               0x05
#define PRESSURE2307BA_SNSR_CFG_OSR_6               0x06
#define PRESSURE2307BA_SNSR_CFG_OSR_BIT_MASK        0x07

/**
 * @brief Pressure 23 07BA description of conversion selection and ADC selection data.
 * @details Specified conversion selection and ADC selection data of Pressure 23 07BA Click driver.
 */
#define PRESSURE2307BA_CNV_ADC_SEL_PRESS            0x00
#define PRESSURE2307BA_CNV_ADC_SEL_TEMP             0x01
#define PRESSURE2307BA_CNV_ADC_BIT_MASK             0x01
#define PRESSURE2307BA_CNV_ADC_REG_BIT_MASK         0x04

/**
 * @brief Pressure 23 07BA description of operation register data.
 * @details Specified operation register data of Pressure 23 07BA Click driver.
 */
#define PRESSURE2307BA_OP_REG_FIFO_INT_TH_OFF       0x00
#define PRESSURE2307BA_OP_REG_FIFO_INT_TH_BIT_MASK  0x1F
#define PRESSURE2307BA_OP_REG_FIFO_MODE_OFF         0x00
#define PRESSURE2307BA_OP_REG_FIFO_MODE_BIT_MASK    0x03
#define PRESSURE2307BA_OP_REG_DELAY_OFF             0x00
#define PRESSURE2307BA_OP_REG_DELAY_5_MS            0x01
#define PRESSURE2307BA_OP_REG_DELAY_10_MS           0x02
#define PRESSURE2307BA_OP_REG_DELAY_20_MS           0x03
#define PRESSURE2307BA_OP_REG_DELAY_50_MS           0x04
#define PRESSURE2307BA_OP_REG_DELAY_100_MS          0x05
#define PRESSURE2307BA_OP_REG_DELAY_200_MS          0x06
#define PRESSURE2307BA_OP_REG_DELAY_500_MS          0x07
#define PRESSURE2307BA_OP_REG_DELAY_1_SEC           0x08
#define PRESSURE2307BA_OP_REG_DELAY_2_SEC           0x09
#define PRESSURE2307BA_OP_REG_DELAY_5_SEC           0x0A
#define PRESSURE2307BA_OP_REG_DELAY_10_SEC          0x0B
#define PRESSURE2307BA_OP_REG_DELAY_20_SEC          0x0C
#define PRESSURE2307BA_OP_REG_DELAY_60_SEC          0x0D
#define PRESSURE2307BA_OP_REG_DELAY_BIT_MASK        0x0F

/**
 * @brief Pressure 23 07BA description of limit register data.
 * @details Specified limit register data of Pressure 23 07BA Click driver.
 */
#define PRESSURE2307BA_LIM_REG_SEL_TEMP             0x00
#define PRESSURE2307BA_LIM_REG_SEL_PRESS            0x01
#define PRESSURE2307BA_LIM_REG_SEL_BIT_MASK         0x01
#define PRESSURE2307BA_LIM_REG_LIM_LOW              0x00
#define PRESSURE2307BA_LIM_REG_LIM_HIGH             0x01
#define PRESSURE2307BA_LIM_REG_LIM_BIT_MASK         0x01

/**
 * @brief Pressure 23 07BA calculation coefficients.
 * @details Specified calculation coefficients of Pressure 23 07BA Click driver.
 */
#define PRESSURE2307BA_COEF_DT                     -3.037801253E-14
#define PRESSURE2307BA_COEF_ET                     -1.079036179E-10
#define PRESSURE2307BA_COEF_FT                      7.558105437E-18
#define PRESSURE2307BA_COEF_GT                     -1.988019651E-25
#define PRESSURE2307BA_COEF_EP                      9.65965184878317E-10
#define PRESSURE2307BA_COEF_GP                     -7.44063838851138E-19
#define PRESSURE2307BA_COEF_HP                     -6.86793865715534E-17
#define PRESSURE2307BA_COEF_IP                     -2.73594458439415E-18
#define PRESSURE2307BA_COEF_JP                     -1.93891892136926E-16
#define PRESSURE2307BA_COEF_KP                      1.11467352484525E-26
#define PRESSURE2307BA_COEF_LP                      1.83448924520177E-24
#define PRESSURE2307BA_COEF_MP                      1.23642876257138E-25
#define PRESSURE2307BA_COEF_NP                      6.19373870077221E-27
#define PRESSURE2307BA_COEF_OP                      1.37287101917619E-23
#define PRESSURE2307BA_COEF_PP                      8.11976718528928E-36
#define PRESSURE2307BA_COEF_QP                     -9.35126613904527E-34
#define PRESSURE2307BA_COEF_RP                     -1.73061923874059E-33
#define PRESSURE2307BA_COEF_SP                      2.92999600253747E-33
#define PRESSURE2307BA_COEF_TP                     -3.65988281559036E-31

/**
 * @brief Pressure 23 07BA device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 23 07BA Click driver.
 */
#define PRESSURE2307BA_DEVICE_ADDRESS_GND            0x77
#define PRESSURE2307BA_DEVICE_ADDRESS_VCC            0x76

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b pressure2307ba_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define PRESSURE2307BA_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define PRESSURE2307BA_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // pressure2307ba_set

/**
 * @defgroup pressure2307ba_map Pressure 23 07BA MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 23 07BA Click driver.
 */

/**
 * @addtogroup pressure2307ba_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 23 07BA Click to the selected MikroBUS.
 */
#define PRESSURE2307BA_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure2307ba_map
/*! @} */ // pressure2307ba

/**
 * @brief Pressure 23 07BA Click driver selector.
 * @details Selects target driver interface of Pressure 23 07BA Click driver.
 */
typedef enum
{
    PRESSURE2307BA_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    PRESSURE2307BA_DRV_SEL_I2C       /**< I2C driver descriptor. */

} pressure2307ba_drv_t;

/**
 * @brief Pressure 23 07BA Click driver interface.
 * @details Definition of driver interface of Pressure 23 07BA Click driver.
 */
struct pressure2307ba_s;
typedef err_t ( *pressure2307ba_master_io_t )( struct pressure2307ba_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Pressure 23 07BA Click context object.
 * @details Context object definition of Pressure 23 07BA Click driver.
 */
typedef struct pressure2307ba_s
{
    digital_in_t int_pin;            /**< Interrupt pin. */

    i2c_master_t i2c;                /**< I2C driver object. */
    spi_master_t spi;                /**< SPI driver object. */

    uint8_t      slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    pressure2307ba_drv_t drv_sel;        /**< Master driver interface selector. */
    
    // Calibration data (factory calibrated) from PROM   
    uint32_t   prom_serial_num;      /**< Serial number. */
    uint8_t    prom_product_id;      /**< Product ID. */
    uint8_t    prom_crc;             /**< 8-bit CRC. */
    
    uint16_t   prom_c1;              /**< C1 coefficient. */
    uint16_t   prom_c2;              /**< C2 coefficient. */
    uint16_t   prom_c3;              /**< C3 coefficient. */
    uint32_t   prom_c4;              /**< C4 coefficient. */
    uint32_t   prom_c5;              /**< C5 coefficient. */
    uint32_t   prom_c6;              /**< C6 coefficient. */
    uint16_t   prom_c7;              /**< C7 coefficient. */
    uint32_t   prom_c8;              /**< C8 coefficient. */
    
    uint8_t    osr_press;            /**< Pressure conversion time. */
    uint8_t    osr_temp;             /**< Temperature conversion time. */

    pressure2307ba_master_io_t write_f;  /**< Master write function. */
    pressure2307ba_master_io_t read_f;   /**< Master read function. */

} pressure2307ba_t;

/**
 * @brief Pressure 23 07BA Click configuration object.
 * @details Configuration object definition of Pressure 23 07BA Click driver.
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

    pressure2307ba_drv_t drv_sel;                       /**< Master driver interface selector. */

} pressure2307ba_cfg_t;

/**
 * @brief Pressure 23 07BA Click sensor configuration object.
 * @details Sensor configuration object definition of Pressure 23 07BA Click driver.
 */
typedef struct
{
    uint8_t    sel;           /**< Configuration selection. */
    uint8_t    ratio;         /**< Ratio configuration. */
    uint8_t    filter;        /**< Filter configuration. */
    uint8_t    resolution;    /**< Resolution configuration. */
    uint8_t    osr;           /**< OSR configuration. */

} pressure2307ba_sensor_cfg_t;

/**
 * @brief Pressure 23 07BA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE2307BA_OK = 0,
    PRESSURE2307BA_ERROR = -1

} pressure2307ba_return_value_t;

/*!
 * @addtogroup pressure2307ba Pressure 23 07BA Click Driver
 * @brief API for configuring and manipulating Pressure 23 07BA Click driver.
 * @{
 */

/**
 * @brief Pressure 23 07BA configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure2307ba_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure2307ba_cfg_setup ( pressure2307ba_cfg_t *cfg );

/**
 * @brief Pressure 23 07BA driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #pressure2307ba_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #pressure2307ba_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void pressure2307ba_drv_int_sel ( pressure2307ba_cfg_t *cfg, pressure2307ba_drv_t drv_sel );

/**
 * @brief Pressure 23 07BA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure2307ba_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_init ( pressure2307ba_t *ctx, pressure2307ba_cfg_t *cfg );

/**
 * @brief Pressure 23 07BA default configuration function.
 * @details This function executes a default configuration of Pressure 23 07BA
 * click board.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pressure2307ba_default_cfg ( pressure2307ba_t *ctx );

/**
 * @brief Pressure 23 07BA data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_generic_write ( pressure2307ba_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 23 07BA data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_generic_read ( pressure2307ba_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 23 07BA set the command function.
 * @details This function writes the desired command
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_set_command ( pressure2307ba_t *ctx, uint8_t cmd );

/**
 * @brief Pressure 23 07BA software reset function.
 * @details This function performs the reset sequence shall be sent once after power-on 
 * to make sure that the calibration data gets loaded into the internal register
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_sw_reset ( pressure2307ba_t *ctx );

/**
 * @brief Pressure 23 07BA read memory function.
 * @details This function reads memory is used to download coefficients programmed 
 * in the memory during factory calibration
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] prom : Output read data from PROM.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_read_memory ( pressure2307ba_t *ctx, uint8_t reg, uint16_t *prom );

/**
 * @brief Pressure 23 07BA start the conversion function.
 * @details This function start the desired conversion, pressure or temperature conversion
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] sel_cnv : Conversion selection
 *         @li @c 0x00 (PRESSURE2307BA_CNV_ADC_SEL_PRESS) - Pressure conversion,
 *         @li @c 0x01 (PRESSURE2307BA_CNV_ADC_SEL_TEMP)  - Temperature conversion.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_start_conversion ( pressure2307ba_t *ctx, uint8_t sel_cnv );

/**
 * @brief Pressure 23 07BA configuration data writing function.
 * @details This function writes a desired sensor configuration 
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] config : Sensor configuration object.
 * See #pressure2307ba_sensor_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_write_config ( pressure2307ba_t *ctx, pressure2307ba_sensor_cfg_t config );

/**
 * @brief Pressure 23 07BA configuration data reading function.
 * @details This function reads a sensor configuration 
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[out] config : Sensor configuration object.
 * See #pressure2307ba_sensor_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_read_config ( pressure2307ba_t *ctx, uint8_t sel_cfg, pressure2307ba_sensor_cfg_t *config );

/**
 * @brief Pressure 23 07BA ADC data reading function.
 * @details This function reads a desired ADC register data, converted pressure or/and temperature value
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] sel_data : ADC register data selection
 *         @li @c 0x00 (PRESSURE2307BA_CNV_ADC_SEL_PRESS) - Pressure,
 *         @li @c 0x01 (PRESSURE2307BA_CNV_ADC_SEL_TEMP)  - Temperature.
 * @param[out] adc_data : Desired ADC raw data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_read_adc ( pressure2307ba_t *ctx, uint8_t sel_data, uint32_t *adc_data );

/**
 * @brief Pressure 23 07BA operation register data writing function.
 * @details This function writes a operation register to control behavior of the FIFO and the automatic mode
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] fifo_int_th : FIFO Interrupt threshold [0-31].
 * @param[in] fifo_mode : FIFO mode [0-2].
 * @param[in] delay : Time between automatically triggered measurements [0-13].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_write_op_reg ( pressure2307ba_t *ctx, uint8_t fifo_int_th, uint8_t fifo_mode, uint8_t delay );

/**
 * @brief Pressure 23 07BA operation register data reading function.
 * @details This function reads a operation register data
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[out] fifo_int_th : FIFO Interrupt threshold [0-31].
 * @param[out] fifo_mode : FIFO mode [0-2].
 * @param[out] delay : Time between automatically triggered measurements [0-13].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_read_op_reg ( pressure2307ba_t *ctx, uint8_t *fifo_int_th, uint8_t *fifo_mode, uint8_t *delay );

/**
 * @brief Pressure 23 07BA interrupt mask data writing function.
 * @details This function writes a interrupt mask data to enable interruptions 
 * which may trigger the application to execute specific actions
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] int_mask_data : Interrupt mask data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_write_int_mask ( pressure2307ba_t *ctx, uint16_t int_mask_data );

/**
 * @brief Pressure 23 07BA interrupt mask data reading function.
 * @details This function reads a interrupt mask data 
 * which may trigger the application to execute specific actions
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[out] int_mask_data : Interrupt mask data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_read_int_mask ( pressure2307ba_t *ctx, uint16_t *int_mask_data );

/**
 * @brief Pressure 23 07BA interrupt register data writing function.
 * @details This function writes a interrupt register data to enable interruptions 
 * which may trigger the application to execute specific actions
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] int_reg_data : Interrupt register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_write_int_reg ( pressure2307ba_t *ctx, uint16_t int_reg_data );

/**
 * @brief Pressure 23 07BA interrupt register data reading function.
 * @details This function reads a interrupt register data 
 * which may trigger the application to execute specific actions
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[out] int_reg_data : Interrupt register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_read_int_reg ( pressure2307ba_t *ctx, uint16_t *int_reg_data );

/**
 * @brief Pressure 23 07BA limit register data writing function.
 * @details This function writes a limit register data to 
 * allow to automatically rise an interrupt if one or both converted values does 
 * exceed the limits programmed in the registers
 * which may trigger the application to execute specific actions
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] sel_adr : Limit register data selection
 *         @li @c 0x00 (PRESSURE2307BA_LIM_REG_SEL_TEMP)   - Temperature,
 *         @li @c 0x01 (PRESSURE2307BA_LIM_REG_SEL_PRESS)  - Pressure.
 * @param[in] sel_lim : Limit selection
 *         @li @c 0x00 (PRESSURE2307BA_LIM_REG_LIM_LOW)   - Low limit,
 *         @li @c 0x01 (PRESSURE2307BA_LIM_REG_LIM_HIGH)  - High limit.
 * @param[in] lim_reg_data : Limit register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_write_lim_reg ( pressure2307ba_t *ctx, uint8_t sel_adr, uint8_t sel_lim, uint16_t lim_reg_data );

/**
 * @brief Pressure 23 07BA limit register data reading function.
 * @details This function reads a limit register data 
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[in] sel_adr : Limit register data selection
 *         @li @c 0x00 (PRESSURE2307BA_LIM_REG_SEL_TEMP)   - Temperature,
 *         @li @c 0x01 (PRESSURE2307BA_LIM_REG_SEL_PRESS)  - Pressure.
 * @param[in] sel_lim : Limit selection
 *         @li @c 0x00 (PRESSURE2307BA_LIM_REG_LIM_LOW)   - Low limit,
 *         @li @c 0x01 (PRESSURE2307BA_LIM_REG_LIM_HIGH)  - High limit.
 * @param[out] lim_reg_data : Limit register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_read_lim_reg ( pressure2307ba_t *ctx, uint8_t sel_adr, uint8_t sel_lim, uint16_t *lim_reg_data );

/**
 * @brief Pressure 23 07BA get the ADC pressure data function.
 * @details This function reads a raw digital pressure value
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[out] pressure : Raw digital pressure value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_get_adc_data_press ( pressure2307ba_t *ctx, uint32_t *pressure );

/**
 * @brief Pressure 23 07BA get the ADC temperature data function.
 * @details This function reads a raw digital temperature value
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[out] temperature : Raw digital temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_get_adc_data_temp ( pressure2307ba_t *ctx, uint32_t *temperature );

/**
 * @brief Pressure 23 07BA gets the calibration data function.
 * @details This function reads and store calibration data, factory calibrated from the PROM memory 
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_get_calibration_data ( pressure2307ba_t *ctx );

/**
 * @brief Pressure 23 07BA gets the measurement data function.
 * @details This function reads temperature and pressure data conversion
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data ( mbar ).
 * @param[out] temperature : Temperature data ( degree Celsius ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure2307ba_get_measurement_data ( pressure2307ba_t *ctx, float *pressure, float *temperature );

/**
 * @brief Pressure 23 07BA gets the interrupt function.
 * @details This function get states of the interrupt [INT] pin
 * of the MS5849-07BA, Ultra-compact, chlorine resistant, absolute pressure sensor
 * on the Pressure 23 07BA Click board™.
 * @param[in] ctx : Click context object.
 * See #pressure2307ba_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t pressure2307ba_get_interrupt ( pressure2307ba_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE2307BA_H

/*! @} */ // pressure2307ba

// ------------------------------------------------------------------------ END
