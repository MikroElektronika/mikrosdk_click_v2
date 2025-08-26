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
 * @file accel33.h
 * @brief This file contains API for Accel 33 Click Driver.
 */

#ifndef ACCEL33_H
#define ACCEL33_H

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
 * @addtogroup accel33 Accel 33 Click Driver
 * @brief API for configuring and manipulating Accel 33 Click driver.
 * @{
 */

/**
 * @defgroup accel33_reg Accel 33 Registers List
 * @brief List of registers of Accel 33 Click driver.
 */

/**
 * @addtogroup accel33_reg
 * @{
 */

/**
 * @brief Accel 33 register map.
 * @details Specified register map of Accel 33 Click driver.
 */
#define ACCEL33_REG_XHPL                    0x00
#define ACCEL33_REG_XHPH                    0x01
#define ACCEL33_REG_YHPL                    0x02
#define ACCEL33_REG_YHPH                    0x03
#define ACCEL33_REG_ZHPL                    0x04
#define ACCEL33_REG_ZHPH                    0x05
#define ACCEL33_REG_XOUTL                   0x06
#define ACCEL33_REG_XOUTH                   0x07
#define ACCEL33_REG_YOUTL                   0x08
#define ACCEL33_REG_YOUTH                   0x09
#define ACCEL33_REG_ZOUTL                   0x0A
#define ACCEL33_REG_ZOUTH                   0x0B
#define ACCEL33_REG_COTR                    0x0C
#define ACCEL33_REG_WHO_AM_I                0x0F
#define ACCEL33_REG_INS2                    0x13
#define ACCEL33_REG_INS3                    0x14
#define ACCEL33_REG_STATUS_REG              0x15
#define ACCEL33_REG_INT_REL                 0x17
#define ACCEL33_REG_CNTL1                   0x18
#define ACCEL33_REG_CNTL2                   0x19
#define ACCEL33_REG_CNTL3                   0x1A
#define ACCEL33_REG_ODCNTL                  0x1B
#define ACCEL33_REG_INC1                    0x1C
#define ACCEL33_REG_INC2                    0x1D
#define ACCEL33_REG_INC4                    0x1F
#define ACCEL33_REG_INC5                    0x20
#define ACCEL33_REG_INC6                    0x21
#define ACCEL33_REG_WUFC                    0x23
#define ACCEL33_REG_MAN_WAKE                0x2C
#define ACCEL33_REG_BTS_CNTL                0x2D
#define ACCEL33_REG_BTSC                    0x2E
#define ACCEL33_REG_BTS_TH                  0x2F
#define ACCEL33_REG_WUF_TH                  0x30
#define ACCEL33_REG_BTS_WUF_TH              0x31
#define ACCEL33_REG_LP_CNTL                 0x35
#define ACCEL33_REG_BUF_CNTL1               0x3A
#define ACCEL33_REG_BUF_CNTL2               0x3B
#define ACCEL33_REG_BUF_STATUS_1            0x3C
#define ACCEL33_REG_BUF_STATUS_2            0x3D
#define ACCEL33_REG_BUF_CLEAR               0x3E
#define ACCEL33_REG_BUF_READ                0x3F
#define ACCEL33_REG_BUF_WUF_CNTL            0x46
#define ACCEL33_REG_SELFTEST                0x60

/*! @} */ // accel33_reg

/**
 * @defgroup accel33_set Accel 33 Registers Settings
 * @brief Settings for registers of Accel 33 Click driver.
 */

/**
 * @addtogroup accel33_set
 * @{
 */

/**
 * @brief Accel 33 INS2 register setting.
 * @details Specified setting for INS2 register of Accel 33 Click driver.
 */
#define ACCEL33_INS2_BTS                    0x80
#define ACCEL33_INS2_BFI                    0x40
#define ACCEL33_INS2_WMI                    0x20
#define ACCEL33_INS2_DRDY                   0x10
#define ACCEL33_INS2_WUFS                   0x02

/**
 * @brief Accel 33 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of Accel 33 Click driver.
 */
#define ACCEL33_WHO_AM_I                    0xCC

/**
 * @brief Accel 33 CNTL1 register setting.
 * @details Specified setting for CNTL1 register of Accel 33 Click driver.
 */
#define ACCEL33_CNTL1_OPMODE_STANDBY        0x00
#define ACCEL33_CNTL1_OPMODE_LOW_POWER      0x80
#define ACCEL33_CNTL1_OPMODE_HIGH_RES       0xC0
#define ACCEL33_CNTL1_OPMODE_MASK           0xC0
#define ACCEL33_CNTL1_DRDYE_DIS             0x00
#define ACCEL33_CNTL1_DRDYE_EN              0x20
#define ACCEL33_CNTL1_DRDYE_MASK            0x20
#define ACCEL33_CNTL1_GSEL_8G               0x00
#define ACCEL33_CNTL1_GSEL_16G              0x08
#define ACCEL33_CNTL1_GSEL_32G              0x10
#define ACCEL33_CNTL1_GSEL_64G              0x18
#define ACCEL33_CNTL1_GSEL_MASK             0x18
#define ACCEL33_CNTL1_WUFE_DIS              0x00
#define ACCEL33_CNTL1_WUFE_EN               0x02
#define ACCEL33_CNTL1_WUFE_MASK             0x02

/**
 * @brief Accel 33 ODCNTL register setting.
 * @details Specified setting for ODCNTL register of Accel 33 Click driver.
 */
#define ACCEL33_ODCNTL_LPRO_ODR_9           0x00
#define ACCEL33_ODCNTL_LPRO_ODR_2           0x40
#define ACCEL33_ODCNTL_LPRO_MASK            0x40
#define ACCEL33_ODCNTL_OSA_0_781HZ          0x00
#define ACCEL33_ODCNTL_OSA_1_563HZ          0x01
#define ACCEL33_ODCNTL_OSA_3_125HZ          0x02
#define ACCEL33_ODCNTL_OSA_6_25HZ           0x03
#define ACCEL33_ODCNTL_OSA_12_5HZ           0x04
#define ACCEL33_ODCNTL_OSA_25HZ             0x05
#define ACCEL33_ODCNTL_OSA_50HZ             0x06
#define ACCEL33_ODCNTL_OSA_100HZ            0x07
#define ACCEL33_ODCNTL_OSA_200HZ            0x08
#define ACCEL33_ODCNTL_OSA_400HZ            0x09
#define ACCEL33_ODCNTL_OSA_800HZ            0x0A
#define ACCEL33_ODCNTL_OSA_1600HZ           0x0B
#define ACCEL33_ODCNTL_OSA_3200HZ           0x0C
#define ACCEL33_ODCNTL_OSA_6400HZ           0x0D
#define ACCEL33_ODCNTL_OSA_12800HZ          0x0E
#define ACCEL33_ODCNTL_OSA_25600HZ          0x0F
#define ACCEL33_ODCNTL_OSA_MASK             0x0F

/**
 * @brief Accel 33 INC1 register setting.
 * @details Specified setting for INC1 register of Accel 33 Click driver.
 */
#define ACCEL33_INC1_PW1_50US               0x00
#define ACCEL33_INC1_PW1_OSA_PERIOD         0x40
#define ACCEL33_INC1_PW1_2X_OSA_PERIOD      0x80
#define ACCEL33_INC1_PW1_MASK               0xC0
#define ACCEL33_INC1_IEN1_DIS               0x00
#define ACCEL33_INC1_IEN1_EN                0x20
#define ACCEL33_INC1_IEN1_MASK              0x20
#define ACCEL33_INC1_IEA1_ACTIVE_LOW        0x00
#define ACCEL33_INC1_IEA1_ACTIVE_HIGH       0x10
#define ACCEL33_INC1_IEA1_MASK              0x10
#define ACCEL33_INC1_IEL1_LATCH             0x00
#define ACCEL33_INC1_IEL1_PULSE             0x08
#define ACCEL33_INC1_IEL1_MASK              0x08
#define ACCEL33_INC1_STPOL_NOMINAL          0x00
#define ACCEL33_INC1_STPOL_INVERTED         0x02
#define ACCEL33_INC1_STPOL_MASK             0x02
#define ACCEL33_INC1_SPI3E_4_WIRE           0x00
#define ACCEL33_INC1_SPI3E_3_WIRE           0x01
#define ACCEL33_INC1_SPI3E_MASK             0x01

/**
 * @brief Accel 33 INC4 register setting.
 * @details Specified setting for INC4 register of Accel 33 Click driver.
 */
#define ACCEL33_INC4_BFI1_DIS               0x00
#define ACCEL33_INC4_BFI1_EN                0x40
#define ACCEL33_INC4_BFI1_MASK              0x40
#define ACCEL33_INC4_WMI1_DIS               0x00
#define ACCEL33_INC4_WMI1_EN                0x20
#define ACCEL33_INC4_WMI1_MASK              0x20
#define ACCEL33_INC4_DRDYI1_DIS             0x00
#define ACCEL33_INC4_DRDYI1_EN              0x10
#define ACCEL33_INC4_DRDYI1_MASK            0x10
#define ACCEL33_INC4_BTSI1_DIS              0x00
#define ACCEL33_INC4_BTSI1_EN               0x08
#define ACCEL33_INC4_BTSI1_MASK             0x08
#define ACCEL33_INC4_WUFI1_DIS              0x00
#define ACCEL33_INC4_WUFI1_EN               0x02
#define ACCEL33_INC4_WUFI1_MASK             0x02

/**
 * @brief Accel 33 INC5 register setting.
 * @details Specified setting for INC5 register of Accel 33 Click driver.
 */
#define ACCEL33_INC5_PW2_50US               0x00
#define ACCEL33_INC5_PW2_OSA_PERIOD         0x40
#define ACCEL33_INC5_PW2_2X_OSA_PERIOD      0x80
#define ACCEL33_INC5_PW2_MASK               0xC0
#define ACCEL33_INC5_IEN2_DIS               0x00
#define ACCEL33_INC5_IEN2_EN                0x20
#define ACCEL33_INC5_IEN2_MASK              0x20
#define ACCEL33_INC5_IEA2_ACTIVE_LOW        0x00
#define ACCEL33_INC5_IEA2_ACTIVE_HIGH       0x10
#define ACCEL33_INC5_IEA2_MASK              0x10
#define ACCEL33_INC5_IEL2_LATCH             0x00
#define ACCEL33_INC5_IEL2_PULSE             0x08
#define ACCEL33_INC5_IEL2_MASK              0x08
#define ACCEL33_INC5_ACLR2_DIS              0x00
#define ACCEL33_INC5_ACLR2_EN               0x04
#define ACCEL33_INC5_ACLR2_MASK             0x04
#define ACCEL33_INC5_ACLR1_DIS              0x00
#define ACCEL33_INC5_ACLR1_EN               0x02
#define ACCEL33_INC5_ACLR1_MASK             0x02

/**
 * @brief Accel 33 INC6 register setting.
 * @details Specified setting for INC6 register of Accel 33 Click driver.
 */
#define ACCEL33_INC6_BFI2_DIS               0x00
#define ACCEL33_INC6_BFI2_EN                0x40
#define ACCEL33_INC6_BFI2_MASK              0x40
#define ACCEL33_INC6_WMI2_DIS               0x00
#define ACCEL33_INC6_WMI2_EN                0x20
#define ACCEL33_INC6_WMI2_MASK              0x20
#define ACCEL33_INC6_DRDYI2_DIS             0x00
#define ACCEL33_INC6_DRDYI2_EN              0x10
#define ACCEL33_INC6_DRDYI2_MASK            0x10
#define ACCEL33_INC6_BTSI2_DIS              0x00
#define ACCEL33_INC6_BTSI2_EN               0x08
#define ACCEL33_INC6_BTSI2_MASK             0x08
#define ACCEL33_INC6_WUFI2_DIS              0x00
#define ACCEL33_INC6_WUFI2_EN               0x02
#define ACCEL33_INC6_WUFI2_MASK             0x02

/**
 * @brief Accel 33 operation mode setting.
 * @details Specified setting for operation mode of Accel 33 Click driver.
 */
#define ACCEL33_OPMODE_STANDBY              0
#define ACCEL33_OPMODE_LOW_POWER            1
#define ACCEL33_OPMODE_HIGH_RES             2

/**
 * @brief Accel 33 full-scale range setting.
 * @details Specified setting for full-scale range of Accel 33 Click driver.
 */
#define ACCEL_FSR_8G                        0
#define ACCEL_FSR_16G                       1
#define ACCEL_FSR_32G                       2
#define ACCEL_FSR_64G                       3

/**
 * @brief Accel 33 output data rate setting.
 * @details Specified setting for output data rate of Accel 33 Click driver.
 */
#define ACCEL33_ODR_0_781HZ                 0
#define ACCEL33_ODR_1_563HZ                 1
#define ACCEL33_ODR_3_125HZ                 2
#define ACCEL33_ODR_6_25HZ                  3
#define ACCEL33_ODR_12_5HZ                  4
#define ACCEL33_ODR_25HZ                    5
#define ACCEL33_ODR_50HZ                    6
#define ACCEL33_ODR_100HZ                   7
#define ACCEL33_ODR_200HZ                   8
#define ACCEL33_ODR_400HZ                   9
#define ACCEL33_ODR_800HZ                   10
#define ACCEL33_ODR_1600HZ                  11
#define ACCEL33_ODR_3200HZ                  12
#define ACCEL33_ODR_6400HZ                  13
#define ACCEL33_ODR_12800HZ                 14
#define ACCEL33_ODR_25600HZ                 15

/**
 * @brief Accel 33 data resolution settings.
 * @details Specified data resolution settings of Accel 33 Click driver.
 */
#define ACCEL33_SENSITIVITY_COUNTS_PER_G    4096.0f

/**
 * @brief Accel 33 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 33 Click driver.
 */
#define ACCEL33_DEVICE_ADDRESS_0            0x1E
#define ACCEL33_DEVICE_ADDRESS_1            0x1F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel33_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL33_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL33_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel33_set

/**
 * @defgroup accel33_map Accel 33 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 33 Click driver.
 */

/**
 * @addtogroup accel33_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 33 Click to the selected MikroBUS.
 */
#define ACCEL33_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel33_map
/*! @} */ // accel33

/**
 * @brief Accel 33 Click driver selector.
 * @details Selects target driver interface of Accel 33 Click driver.
 */
typedef enum
{
    ACCEL33_DRV_SEL_SPI,            /**< SPI driver descriptor. */
    ACCEL33_DRV_SEL_I2C             /**< I2C driver descriptor. */

} accel33_drv_t;

/**
 * @brief Accel 33 Click driver interface.
 * @details Definition of driver interface of Accel 33 Click driver.
 */
struct accel33_s;
typedef err_t ( *accel33_master_io_t )( struct accel33_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 33 Click context object.
 * @details Context object definition of Accel 33 Click driver.
 */
typedef struct accel33_s
{
    digital_out_t rst;              /**< Reset pin (active low). */

    digital_in_t int1;              /**< Interrupt 1 pin. */
    digital_in_t int2;              /**< Interrupt 2 pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    accel33_drv_t drv_sel;          /**< Master driver interface selector. */

    accel33_master_io_t write_f;    /**< Master write function. */
    accel33_master_io_t read_f;     /**< Master read function. */
    float accel_sens;               /**< Accel sensitivity setting. */

} accel33_t;

/**
 * @brief Accel 33 Click configuration object.
 * @details Configuration object definition of Accel 33 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int1;                /**< Interrupt 1 pin. */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t int2;                /**< Interrupt 2 pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel33_drv_t drv_sel;          /**< Master driver interface selector. */

} accel33_cfg_t;

/**
 * @brief Accel 33 Click axes data structure.
 * @details Axes data object definition of Accel 33 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} accel33_axes_t;

/**
 * @brief Accel 33 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL33_OK = 0,
    ACCEL33_ERROR = -1,
    ACCEL33_DATA_NOT_READY = -2

} accel33_return_value_t;

/*!
 * @addtogroup accel33 Accel 33 Click Driver
 * @brief API for configuring and manipulating Accel 33 Click driver.
 * @{
 */

/**
 * @brief Accel 33 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel33_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel33_cfg_setup ( accel33_cfg_t *cfg );

/**
 * @brief Accel 33 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel33_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel33_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel33_drv_interface_sel ( accel33_cfg_t *cfg, accel33_drv_t drv_sel );

/**
 * @brief Accel 33 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel33_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel33_init ( accel33_t *ctx, accel33_cfg_t *cfg );

/**
 * @brief Accel 33 default configuration function.
 * @details This function executes a default configuration of Accel 33
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel33_default_cfg ( accel33_t *ctx );

/**
 * @brief Accel 33 Write Registers function.
 * @details This function writes a sequence of bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to data to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_write_regs ( accel33_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 33 Read Registers function.
 * @details This function reads a sequence of bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the memory to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_read_regs ( accel33_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 33 Write Register function.
 * @details This function writes a single byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_write_reg ( accel33_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 33 Read Register function.
 * @details This function reads a single byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory to store read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_read_reg ( accel33_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 33 Enable Device function.
 * @details This function sets the RST pin high to enable the device.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @note None.
 */
void accel33_enable_device ( accel33_t *ctx );

/**
 * @brief Accel 33 Disable Device function.
 * @details This function sets the RST pin low to disable the device.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @note None.
 */
void accel33_disable_device ( accel33_t *ctx );

/**
 * @brief Accel 33 Get INT1 Pin function.
 * @details This function returns the logic state of the INT1 pin.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel33_get_int1_pin ( accel33_t *ctx );

/**
 * @brief Accel 33 Get INT2 Pin function.
 * @details This function returns the logic state of the INT2 pin.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel33_get_int2_pin ( accel33_t *ctx );

/**
 * @brief Accel 33 Check Communication function.
 * @details This function checks the communication by reading the WHO_AM_I register.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_check_communication ( accel33_t *ctx );

/**
 * @brief Accel 33 Set Operation Mode function.
 * @details This function sets the current operation mode.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[in] op_mode : Operation mode setting.
                        @li @c 0 - Standby,
 *                      @li @c 1 - Low power,
 *                      @li @c 2 - High resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_set_op_mode ( accel33_t *ctx, uint8_t op_mode );

/**
 * @brief Accel 33 Set Full-Scale Range function.
 * @details This function sets the accelerometer's full-scale range.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[in] fsr : Full-scale range setting.
                    @li @c 0 - 8G,
 *                  @li @c 1 - 16G,
 *                  @li @c 2 - 32G,
 *                  @li @c 3 - 64G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_set_fsr ( accel33_t *ctx, uint8_t fsr );

/**
 * @brief Accel 33 Set Output Data Rate function.
 * @details This function sets the accelerometer's output data rate.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[in] odr : Output data rate setting, see ACCEL33_ODR_x macros definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_set_odr ( accel33_t *ctx, uint8_t odr );

/**
 * @brief Accel 33 Get Data Ready Flag function.
 * @details This function checks if new acceleration data is available.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c ACCEL33_INS2_DRDY - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accel33_get_drdy ( accel33_t *ctx, uint8_t *drdy );

/**
 * @brief Accel 33 Get Acceleration Data function.
 * @details This function reads and converts the raw acceleration data for all three axes.
 * @param[in] ctx : Click context object.
 * See #accel33_t object definition for detailed explanation.
 * @param[out] accel : Pointer to the structure to store acceleration values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Data not ready.
 * @note None.
 */
err_t accel33_get_accel ( accel33_t *ctx, accel33_axes_t *accel );

#ifdef __cplusplus
}
#endif
#endif // ACCEL33_H

/*! @} */ // accel33

// ------------------------------------------------------------------------ END
