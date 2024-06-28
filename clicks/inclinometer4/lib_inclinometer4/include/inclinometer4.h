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
 * @file inclinometer4.h
 * @brief This file contains API for Inclinometer 4 Click Driver.
 */

#ifndef INCLINOMETER4_H
#define INCLINOMETER4_H

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
 * @addtogroup inclinometer4 Inclinometer 4 Click Driver
 * @brief API for configuring and manipulating Inclinometer 4 Click driver.
 * @{
 */

/**
 * @defgroup inclinometer4_reg Inclinometer 4 Registers List
 * @brief List of registers of Inclinometer 4 Click driver.
 */

/**
 * @addtogroup inclinometer4_reg
 * @{
 */

/**
 * @brief Inclinometer 4 register list.
 * @details Specified register list of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_REG_INT_STATUS                0x00
#define INCLINOMETER4_REG_TEMP_OUT                  0x01
#define INCLINOMETER4_REG_VECM_LSB                  0x02
#define INCLINOMETER4_REG_VECM_MSB                  0x03
#define INCLINOMETER4_REG_OUT_X_LSB                 0x04
#define INCLINOMETER4_REG_OUT_X_MSB                 0x05
#define INCLINOMETER4_REG_OUT_Y_LSB                 0x06
#define INCLINOMETER4_REG_OUT_Y_MSB                 0x07
#define INCLINOMETER4_REG_OUT_Z_LSB                 0x08
#define INCLINOMETER4_REG_OUT_Z_MSB                 0x09
#define INCLINOMETER4_REG_BUF_STATUS                0x0B
#define INCLINOMETER4_REG_BUF_X_LSB                 0x0C
#define INCLINOMETER4_REG_BUF_X_MSB                 0x0D
#define INCLINOMETER4_REG_BUF_Y_LSB                 0x0E
#define INCLINOMETER4_REG_BUF_Y_MSB                 0x0F
#define INCLINOMETER4_REG_BUF_Z_LSB                 0x10
#define INCLINOMETER4_REG_BUF_Z_MSB                 0x11
#define INCLINOMETER4_REG_PROD_REV                  0x12
#define INCLINOMETER4_REG_WHO_AM_I                  0x13
#define INCLINOMETER4_REG_SYS_MODE                  0x14
#define INCLINOMETER4_REG_SENS_CONFIG1              0x15
#define INCLINOMETER4_REG_SENS_CONFIG2              0x16
#define INCLINOMETER4_REG_SENS_CONFIG3              0x17
#define INCLINOMETER4_REG_SENS_CONFIG4              0x18
#define INCLINOMETER4_REG_SENS_CONFIG5              0x19
#define INCLINOMETER4_REG_WAKE_IDLE_LSB             0x1A
#define INCLINOMETER4_REG_WAKE_IDLE_MSB             0x1B
#define INCLINOMETER4_REG_SLEEP_IDLE_LSB            0x1C
#define INCLINOMETER4_REG_SLEEP_IDLE_MSB            0x1D
#define INCLINOMETER4_REG_ASLP_COUNT_LSB            0x1E
#define INCLINOMETER4_REG_ASLP_COUNT_MSB            0x1F
#define INCLINOMETER4_REG_INT_EN                    0x20
#define INCLINOMETER4_REG_INT_PIN_SEL               0x21
#define INCLINOMETER4_REG_OFF_X                     0x22
#define INCLINOMETER4_REG_OFF_Y                     0x23
#define INCLINOMETER4_REG_OFF_Z                     0x24
#define INCLINOMETER4_REG_BUF_CONFIG1               0x26
#define INCLINOMETER4_REG_BUF_CONFIG2               0x27
#define INCLINOMETER4_REG_ORIENT_STATUS             0x28
#define INCLINOMETER4_REG_ORIENT_CONFIG             0x29
#define INCLINOMETER4_REG_ORIENT_DBCOUNT            0x2A
#define INCLINOMETER4_REG_ORIENT_BF_ZCOMP           0x2B
#define INCLINOMETER4_REG_ORIENT_THS_REG            0x2C
#define INCLINOMETER4_REG_SDCD_INT_SRC1             0x2D
#define INCLINOMETER4_REG_SDCD_INT_SRC2             0x2E
#define INCLINOMETER4_REG_SDCD_CONFIG1              0x2F
#define INCLINOMETER4_REG_SDCD_CONFIG2              0x30
#define INCLINOMETER4_REG_SDCD_OT_DBCNT             0x31
#define INCLINOMETER4_REG_SDCD_WT_DBCNT             0x32
#define INCLINOMETER4_REG_SDCD_LTHS_LSB             0x33
#define INCLINOMETER4_REG_SDCD_LTHS_MSB             0x34
#define INCLINOMETER4_REG_SDCD_UTHS_LSB             0x35
#define INCLINOMETER4_REG_SDCD_UTHS_MSB             0x36
#define INCLINOMETER4_REG_SELF_TEST_CONFIG1         0x37
#define INCLINOMETER4_REG_SELF_TEST_CONFIG2         0x38

/*! @} */ // inclinometer4_reg

/**
 * @defgroup inclinometer4_set Inclinometer 4 Registers Settings
 * @brief Settings for registers of Inclinometer 4 Click driver.
 */

/**
 * @addtogroup inclinometer4_set
 * @{
 */

/**
 * @brief Inclinometer 4 INT_STATUS register setting.
 * @details Specified setting for INT_STATUS register of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_INT_STATUS_SRC_DRDY           0x80
#define INCLINOMETER4_INT_STATUS_SRC_OVF            0x40
#define INCLINOMETER4_INT_STATUS_SRC_BUF            0x20
#define INCLINOMETER4_INT_STATUS_SRC_SDCD_OT        0x10
#define INCLINOMETER4_INT_STATUS_SRC_SDCD_WT        0x08
#define INCLINOMETER4_INT_STATUS_SRC_ORIENT         0x04
#define INCLINOMETER4_INT_STATUS_SRC_ASLP           0x02
#define INCLINOMETER4_INT_STATUS_SRC_BOOT           0x01

/**
 * @brief Inclinometer 4 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_WHO_AM_I                      0x83

/**
 * @brief Inclinometer 4 SENS_CONFIG1 register setting.
 * @details Specified setting for SENS_CONFIG1 register of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_SENS_CONFIG1_RST              0x80
#define INCLINOMETER4_SENS_CONFIG1_ST_AXIS_SEL_DIS  0x00
#define INCLINOMETER4_SENS_CONFIG1_ST_AXIS_SEL_X    0x20
#define INCLINOMETER4_SENS_CONFIG1_ST_AXIS_SEL_Y    0x40
#define INCLINOMETER4_SENS_CONFIG1_ST_AXIS_SEL_Z    0x60
#define INCLINOMETER4_SENS_CONFIG1_ST_AXIS_SEL_MASK 0x60
#define INCLINOMETER4_SENS_CONFIG1_ST_POL           0x10
#define INCLINOMETER4_SENS_CONFIG1_SPI_M_4_WIRE     0x00
#define INCLINOMETER4_SENS_CONFIG1_SPI_M_3_WIRE     0x08
#define INCLINOMETER4_SENS_CONFIG1_SPI_M_MASK       0x08
#define INCLINOMETER4_SENS_CONFIG1_FSR_2G           0x00
#define INCLINOMETER4_SENS_CONFIG1_FSR_4G           0x02
#define INCLINOMETER4_SENS_CONFIG1_FSR_8G           0x04
#define INCLINOMETER4_SENS_CONFIG1_FSR_16G          0x06
#define INCLINOMETER4_SENS_CONFIG1_FSR_MASK         0x06
#define INCLINOMETER4_SENS_CONFIG1_MODE_STANDBY     0x00
#define INCLINOMETER4_SENS_CONFIG1_MODE_ACTIVE      0x01
#define INCLINOMETER4_SENS_CONFIG1_MODE_MASK        0x01

/**
 * @brief Inclinometer 4 SENS_CONFIG3 register setting.
 * @details Specified setting for SENS_CONFIG3 register of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_SENS_CONFIG3_WAKE_ODR_MASK    0xF0
#define INCLINOMETER4_SENS_CONFIG3_SLEEP_ODR_MASK   0x0F

/**
 * @brief Inclinometer 4 SENS_CONFIG4 register setting.
 * @details Specified setting for SENS_CONFIG4 register of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_SENS_CONFIG4_EXT_TRIG_M       0x80
#define INCLINOMETER4_SENS_CONFIG4_WAKE_SDCD_WT     0x40
#define INCLINOMETER4_SENS_CONFIG4_WAKE_SDCD_OT     0x20
#define INCLINOMETER4_SENS_CONFIG4_WAKE_ORIENT      0x10
#define INCLINOMETER4_SENS_CONFIG4_DRDY_PUL         0x08
#define INCLINOMETER4_SENS_CONFIG4_INT2_FUNC        0x04
#define INCLINOMETER4_SENS_CONFIG4_INT_PP_OD        0x02
#define INCLINOMETER4_SENS_CONFIG4_INT_POL          0x01

/**
 * @brief Inclinometer 4 INT_EN register setting.
 * @details Specified setting for INT_EN register of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_INT_EN_DRDY                   0x80
#define INCLINOMETER4_INT_EN_BUF                    0x40
#define INCLINOMETER4_INT_EN_SDCD_OT                0x20
#define INCLINOMETER4_INT_EN_SDCD_WT                0x10
#define INCLINOMETER4_INT_EN_ORIENT                 0x08
#define INCLINOMETER4_INT_EN_ASLP                   0x04
#define INCLINOMETER4_INT_EN_BOOT_DIS               0x02
#define INCLINOMETER4_INT_EN_WAKE_OUT               0x01

/**
 * @brief Inclinometer 4 INT_PIN_SEL register setting.
 * @details Specified setting for INT_PIN_SEL register of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_INT_PIN_SEL_DRDY_INT2         0x80
#define INCLINOMETER4_INT_PIN_SEL_BUF_INT2          0x40
#define INCLINOMETER4_INT_PIN_SEL_SDCD_OT_INT2      0x20
#define INCLINOMETER4_INT_PIN_SEL_SDCD_WT_INT2      0x10
#define INCLINOMETER4_INT_PIN_SEL_ORIENT_INT2       0x08
#define INCLINOMETER4_INT_PIN_SEL_ASLP_INT2         0x04
#define INCLINOMETER4_INT_PIN_SEL_BOOT_INT2         0x02
#define INCLINOMETER4_INT_PIN_SEL_WAKE_OUT_INT2     0x01

/**
 * @brief Inclinometer 4 operating mode setting.
 * @details Specified setting for operating mode of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_MODE_STANDBY                  0
#define INCLINOMETER4_MODE_ACTIVE                   1

/**
 * @brief Inclinometer 4 FSR setting.
 * @details Specified setting for FSR of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_FSR_2G                        0
#define INCLINOMETER4_FSR_4G                        1
#define INCLINOMETER4_FSR_8G                        2
#define INCLINOMETER4_FSR_16G                       3

/**
 * @brief Inclinometer 4 ODR setting.
 * @details Specified setting for ODR of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_ODR_3200_HZ                   0
#define INCLINOMETER4_ODR_1600_HZ                   1
#define INCLINOMETER4_ODR_800_HZ                    2
#define INCLINOMETER4_ODR_400_HZ                    3
#define INCLINOMETER4_ODR_200_HZ                    4
#define INCLINOMETER4_ODR_100_HZ                    5
#define INCLINOMETER4_ODR_50_HZ                     6
#define INCLINOMETER4_ODR_25_HZ                     7
#define INCLINOMETER4_ODR_12_5_HZ                   8
#define INCLINOMETER4_ODR_6_25_HZ                   9
#define INCLINOMETER4_ODR_3_125_HZ                  10
#define INCLINOMETER4_ODR_1_563_HZ                  11
#define INCLINOMETER4_ODR_0_781_HZ                  12

/**
 * @brief Inclinometer 4 LSB/g setting.
 * @details Specified setting for LSB/g of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_LSB_PER_G_FSR_2G              1024
#define INCLINOMETER4_LSB_PER_G_FSR_4G              512
#define INCLINOMETER4_LSB_PER_G_FSR_8G              256
#define INCLINOMETER4_LSB_PER_G_FSR_16G             128

/**
 * @brief Inclinometer 4 temperature offset setting.
 * @details Specified setting for temperature offset of Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_TEMP_OFFSET                   25

/**
 * @brief Inclinometer 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Inclinometer 4 Click driver.
 */
#define INCLINOMETER4_DEVICE_ADDRESS_0              0x18
#define INCLINOMETER4_DEVICE_ADDRESS_1              0x19

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b inclinometer4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define INCLINOMETER4_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define INCLINOMETER4_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // inclinometer4_set

/**
 * @defgroup inclinometer4_map Inclinometer 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Inclinometer 4 Click driver.
 */

/**
 * @addtogroup inclinometer4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Inclinometer 4 Click to the selected MikroBUS.
 */
#define INCLINOMETER4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // inclinometer4_map
/*! @} */ // inclinometer4

/**
 * @brief Inclinometer 4 Click driver selector.
 * @details Selects target driver interface of Inclinometer 4 Click driver.
 */
typedef enum
{
    INCLINOMETER4_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    INCLINOMETER4_DRV_SEL_I2C       /**< I2C driver descriptor. */

} inclinometer4_drv_t;

/**
 * @brief Inclinometer 4 Click driver interface.
 * @details Definition of driver interface of Inclinometer 4 Click driver.
 */
struct inclinometer4_s;
typedef err_t ( *inclinometer4_master_io_t )( struct inclinometer4_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Inclinometer 4 Click context object.
 * @details Context object definition of Inclinometer 4 Click driver.
 */
typedef struct inclinometer4_s
{
    digital_in_t int2;                  /**< Interrupt 2 pin. */
    digital_in_t int1;                  /**< Interrupt 1 pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t slave_address;              /**< Device slave address (used for I2C driver). */
    pin_name_t chip_select;             /**< Chip select pin descriptor (used for SPI driver). */
    inclinometer4_drv_t drv_sel;        /**< Master driver interface selector. */

    inclinometer4_master_io_t write_f;  /**< Master write function. */
    inclinometer4_master_io_t read_f;   /**< Master read function. */

    uint16_t lsb_per_g;                 /**< LSB/g nominal sensitivity for FSR. */

} inclinometer4_t;

/**
 * @brief Inclinometer 4 Click configuration object.
 * @details Configuration object definition of Inclinometer 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int2;                    /**< Interrupt 2 pin. */
    pin_name_t int1;                    /**< Interrupt 1 pin. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    inclinometer4_drv_t drv_sel;        /**< Master driver interface selector. */

} inclinometer4_cfg_t;

/**
 * @brief Inclinometer 4 Click Axes data structure.
 * @details Axes data object definition of Inclinometer 4 Click driver.
 */
typedef struct
{
    float x;                            /**< X axis [g]. */
    float y;                            /**< Y axis [g]. */
    float z;                            /**< Z axis [g]. */
    int8_t temperature;                 /**< Temperature [degrees Celsius]. */

} inclinometer4_data_t;

/**
 * @brief Inclinometer 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    INCLINOMETER4_OK = 0,
    INCLINOMETER4_ERROR = -1

} inclinometer4_return_value_t;

/*!
 * @addtogroup inclinometer4 Inclinometer 4 Click Driver
 * @brief API for configuring and manipulating Inclinometer 4 Click driver.
 * @{
 */

/**
 * @brief Inclinometer 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #inclinometer4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void inclinometer4_cfg_setup ( inclinometer4_cfg_t *cfg );

/**
 * @brief Inclinometer 4 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #inclinometer4_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #inclinometer4_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void inclinometer4_drv_interface_sel ( inclinometer4_cfg_t *cfg, inclinometer4_drv_t drv_sel );

/**
 * @brief Inclinometer 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #inclinometer4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_init ( inclinometer4_t *ctx, inclinometer4_cfg_t *cfg );

/**
 * @brief Inclinometer 4 default configuration function.
 * @details This function executes a default configuration of Inclinometer 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t inclinometer4_default_cfg ( inclinometer4_t *ctx );

/**
 * @brief Inclinometer 4 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_write_regs ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Inclinometer 4 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_read_regs ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Inclinometer 4 write reg function.
 * @details This function write a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_write_reg ( inclinometer4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Inclinometer 4 read reg function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_read_reg ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Inclinometer 4 get int1 pin function.
 * @details This function returns the interrupt 1 (INT1) pin logic state.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t inclinometer4_get_int1_pin ( inclinometer4_t *ctx );

/**
 * @brief Inclinometer 4 get int2 pin function.
 * @details This function returns the interrupt 2 (INT2) pin logic state.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t inclinometer4_get_int2_pin ( inclinometer4_t *ctx );

/**
 * @brief Inclinometer 4 check comm function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_check_comm ( inclinometer4_t *ctx );

/**
 * @brief Inclinometer 4 get status function.
 * @details This function reads the interrupt status register.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[out] status : Interrupt status read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_get_status ( inclinometer4_t *ctx, uint8_t *status );

/**
 * @brief Inclinometer 4 sw reset function.
 * @details This function performs the device software reset.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_sw_reset ( inclinometer4_t *ctx );

/**
 * @brief Inclinometer 4 set mode function.
 * @details This function sets the device operating mode to standby or active.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] mode : Operating mode: @li @c 0 - Standby,
 *                                   @li @c 1 - Active.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_set_mode ( inclinometer4_t *ctx, uint8_t mode );

/**
 * @brief Inclinometer 4 set fsr function.
 * @details This function sets the accel measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 0 - 2G,
 *                  @li @c 1 - 4G,
 *                  @li @c 2 - 8G,
 *                  @li @c 3 - 16G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_set_fsr ( inclinometer4_t *ctx, uint8_t fsr );

/**
 * @brief Inclinometer 4 set odr function.
 * @details This function sets the measurement output data rate.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - 3200Hz,
 *                  @li @c 1 - 1600Hz,
 *                  @li @c 2 - 800Hz,
 *                  @li @c 3 - 400Hz,
 *                  @li @c 4 - 200Hz,
 *                  @li @c 5 - 100Hz,
 *                  @li @c 6 - 50Hz,
 *                  @li @c 7 - 25Hz,
 *                  @li @c 8 - 12.5Hz,
 *                  @li @c 9 - 6.25Hz,
 *                  @li @c 10 - 3.125Hz,
 *                  @li @c 11 - 1.563Hz,
 *                  @li @c 12 - 0.781Hz,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_set_odr ( inclinometer4_t *ctx, uint8_t odr );

/**
 * @brief Inclinometer 4 get data function.
 * @details This function reads accel X, Y, and Z axis data in g and temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[out] data_out : X, Y, and Z axis data in g, and temperature in degrees Celsius.
 * See #inclinometer4_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer4_get_data ( inclinometer4_t *ctx, inclinometer4_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // INCLINOMETER4_H

/*! @} */ // inclinometer4

// ------------------------------------------------------------------------ END
