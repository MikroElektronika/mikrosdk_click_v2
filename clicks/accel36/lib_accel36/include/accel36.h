/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file accel36.h
 * @brief This file contains API for Accel 36 Click Driver.
 */

#ifndef ACCEL36_H
#define ACCEL36_H

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
 * @addtogroup accel36 Accel 36 Click Driver
 * @brief API for configuring and manipulating Accel 36 Click driver.
 * @{
 */

/**
 * @defgroup accel36_reg Accel 36 Registers List
 * @brief List of registers of Accel 36 Click driver.
 */

/**
 * @addtogroup accel36_reg
 * @{
 */

/**
 * @brief Accel 36 register list.
 * @details Specified register list of Accel 36 Click driver.
 */
#define ACCEL36_REG_EXT_STAT_1          0x00
#define ACCEL36_REG_EXT_STAT_2          0x01
#define ACCEL36_REG_XOUT_LSB            0x02
#define ACCEL36_REG_XOUT_MSB            0x03
#define ACCEL36_REG_YOUT_LSB            0x04
#define ACCEL36_REG_YOUT_MSB            0x05
#define ACCEL36_REG_ZOUT_LSB            0x06
#define ACCEL36_REG_ZOUT_MSB            0x07
#define ACCEL36_REG_STATUS_1            0x08
#define ACCEL36_REG_STATUS_2            0x09
#define ACCEL36_REG_FREG_1              0x0D
#define ACCEL36_REG_FREG_2              0x0E
#define ACCEL36_REG_INIT_1              0x0F
#define ACCEL36_REG_MODE_C              0x10
#define ACCEL36_REG_RATE_1              0x11
#define ACCEL36_REG_SNIFF_C             0x12
#define ACCEL36_REG_SNIFFTH_C           0x13
#define ACCEL36_REG_SNIFFCF_C           0x14
#define ACCEL36_REG_RANGE_C             0x15
#define ACCEL36_REG_FIFO_C              0x16
#define ACCEL36_REG_INTR_C              0x17
#define ACCEL36_REG_CHIP_ID             0x18
#define ACCEL36_REG_INIT_3              0x1A
#define ACCEL36_REG_SCRATCH             0x1B
#define ACCEL36_REG_PMCR                0x1C
#define ACCEL36_REG_DMX                 0x20
#define ACCEL36_REG_DMY                 0x21
#define ACCEL36_REG_DMZ                 0x22
#define ACCEL36_REG_RESET               0x24
#define ACCEL36_REG_INIT_2              0x28
#define ACCEL36_REG_TRIGC               0x29
#define ACCEL36_REG_XOFFL               0x2A
#define ACCEL36_REG_XOFFH               0x2B
#define ACCEL36_REG_YOFFL               0x2C
#define ACCEL36_REG_YOFFH               0x2D
#define ACCEL36_REG_ZOFFL               0x2E
#define ACCEL36_REG_ZOFFH               0x2F
#define ACCEL36_REG_XGAIN               0x30
#define ACCEL36_REG_YGAIN               0x31
#define ACCEL36_REG_ZGAIN               0x32

/*! @} */ // accel36_reg

/**
 * @defgroup accel36_set Accel 36 Registers Settings
 * @brief Settings for registers of Accel 36 Click driver.
 */

/**
 * @addtogroup accel36_set
 * @{
 */

/**
 * @brief Accel 36 FEATURE register 1 setting.
 * @details Specified setting for FEATURE register 1 of Accel 36 Click driver.
 */
#define ACCEL36_FREG1_SPI_EN            0x80
#define ACCEL36_FREG1_I2C_EN            0x40
#define ACCEL36_FREG1_SPI3_EN           0x20
#define ACCEL36_FREG1_INTSC_EN          0x10
#define ACCEL36_FREG1_FREEZE            0x08

/**
 * @brief Accel 36 INITIALIZATION register 1 setting.
 * @details Specified setting for INITIALIZATION register 1 of Accel 36 Click driver.
 */
#define ACCEL36_INIT_1_VALUE            0x42
#define ACCEL36_INIT_2_VALUE            0x00
#define ACCEL36_INIT_3_VALUE            0x00
#define ACCEL36_DMX_INIT_VALUE          0x01
#define ACCEL36_DMY_INIT_VALUE          0x80

/**
 * @brief Accel 36 RESET register setting.
 * @details Specified setting for RESET register of Accel 36 Click driver.
 */
#define ACCEL36_RESET_CMD               0x40
#define ACCEL36_RELOAD_CMD              0x80

/**
 * @brief Accel 36 MODE CONTROL register setting.
 * @details Specified setting for MODE CONTROL Register of Accel 36 Click driver.
 */
#define ACCEL36_MODE_SLEEP              0x00
#define ACCEL36_MODE_STANDBY            0x01
#define ACCEL36_MODE_SNIFF              0x02
#define ACCEL36_MODE_CWAKE              0x05
#define ACCEL36_MODE_SWAKE              0x06
#define ACCEL36_MODE_TRIG               0x07
#define ACCEL36_MODE_MASK               0x07
#define ACCEL36_MODE_TRIG_CMD           0x80
#define ACCEL36_MODE_X_AXIS_PD          0x10
#define ACCEL36_MODE_Y_AXIS_PD          0x20
#define ACCEL36_MODE_Z_AXIS_PD          0x40

/**
 * @brief Accel 36 STATUS 1 register setting.
 * @details Specified setting for STATUS 1 Register of Accel 36 Click driver.
 */
#define ACCEL36_STATUS1_INT_PEND        0x80
#define ACCEL36_STATUS1_FIFO_THRESH     0x40
#define ACCEL36_STATUS1_FIFO_FULL       0x20
#define ACCEL36_STATUS1_FIFO_EMPTY      0x10
#define ACCEL36_STATUS1_NEW_DATA        0x08
#define ACCEL36_STATUS1_MODE_MASK       0x07

/**
 * @brief Accel 36 RANGE AND RESOLUTION CONTROL register setting.
 * @details Specified setting for RANGE AND RESOLUTION CONTROL Register of Accel 36 Click driver.
 */
#define ACCEL36_RANGE_2G                0x00
#define ACCEL36_RANGE_4G                0x10
#define ACCEL36_RANGE_8G                0x20
#define ACCEL36_RANGE_16G               0x30
#define ACCEL36_RANGE_12G               0x40
#define ACCEL36_RANGE_MASK              0x70
#define ACCEL36_RES_6BIT                0x00
#define ACCEL36_RES_7BIT                0x01
#define ACCEL36_RES_8BIT                0x02
#define ACCEL36_RES_10BIT               0x03
#define ACCEL36_RES_12BIT               0x04
#define ACCEL36_RES_14BIT               0x05
#define ACCEL36_RES_MASK                0x07
#define ACCEL36_RANGE_BIT               4

/**
 * @brief Accel 36 full-scale range setting.
 * @details Specified setting for full-scale range of Accel 36 Click driver.
 */
#define ACCEL36_FSR_2G                  0x00
#define ACCEL36_FSR_4G                  0x01
#define ACCEL36_FSR_8G                  0x02
#define ACCEL36_FSR_16G                 0x03
#define ACCEL36_FSR_12G                 0x04

/**
 * @brief Accel 36 PMCR register setting.
 * @details Specified setting for PMCR register of Accel 36 Click driver.
 */
#define ACCEL36_CSPM_LOW_POWER          0x00
#define ACCEL36_CSPM_ULTRA_LOW_POWER    0x03
#define ACCEL36_CSPM_PRECISION          0x04
#define ACCEL36_CSPM_MASK               0x07
#define ACCEL36_SPM_LOW_POWER           0x00
#define ACCEL36_SPM_ULTRA_LOW_POWER     0x30
#define ACCEL36_SPM_PRECISION           0x40
#define ACCEL36_SPM_MASK                0x70
#define ACCEL36_PMCR_SPI_HS_EN          0x80

/**
 * @brief Accel 36 output data rate setting.
 * @details Specified setting for output data rate of Accel 36 Click driver.
 */
#define ACCEL36_ODR_14HZ                0x05
#define ACCEL36_ODR_28HZ                0x06
#define ACCEL36_ODR_54HZ                0x07
#define ACCEL36_ODR_105HZ               0x08
#define ACCEL36_ODR_210HZ               0x09
#define ACCEL36_ODR_400HZ               0x0A
#define ACCEL36_ODR_600HZ               0x0B

/**
 * @brief Accel 36 chip ID setting.
 * @details Specified setting for chip ID of Accel 36 Click driver.
 */
#define ACCEL36_CHIP_ID                 0x71

/**
 * @brief Accel 36 sensitivity setting.
 * @details Specified setting for sensitivity of Accel 36 Click driver.
 */
#define ACCEL36_SENS_2G                 4096.0f
#define ACCEL36_SENS_4G                 2048.0f
#define ACCEL36_SENS_8G                 1024.0f
#define ACCEL36_SENS_12G                683.0f 
#define ACCEL36_SENS_16G                512.0f 

/**
 * @brief Accel 36 timeout setting.
 * @details Specified setting for timeout of Accel 36 Click driver.
 */
#define ACCEL36_ID_TIMEOUT_MS           100
#define ACCEL36_SPI_ENABLE_MS           100

/**
 * @brief Accel 36 initialization data value setting.
 * @details Specified setting for initialization data value of Accel 36 Click driver.
 */
#define ACCEL36_ID_POLL_DATA            0x00
#define ACCEL36_SPI_ENABLE_POLL_DATA    0x80

/**
 * @brief Accel 36 MSB and LSB masks setting.
 * @details Specified setting for MSB and LSB masks of Accel 36 Click driver.
 */
#define ACCEL36_MSB_BYTE_MASK          0xF0
#define ACCEL36_LSB_BYTE_MASK          0x0F

/**
 * @brief Accel 36 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 36 Click driver.
 */
#define ACCEL36_DEVICE_ADDRESS_GND      0x4C  
#define ACCEL36_DEVICE_ADDRESS_VCC      0x6C 
#define ACCEL36_DEVICE_ADDRESS          ACCEL36_DEVICE_ADDRESS_GND

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel36_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL36_SET_DATA_SAMPLE_EDGE    SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL36_SET_DATA_SAMPLE_MIDDLE  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel36_set

/**
 * @defgroup accel36_map Accel 36 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 36 Click driver.
 */

/**
 * @addtogroup accel36_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 36 Click to the selected MikroBUS.
 */
#define ACCEL36_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel36_map
/*! @} */ // accel36

/**
 * @brief Accel 36 Click driver selector.
 * @details Selects target driver interface of Accel 36 Click driver.
 */
typedef enum
{
    ACCEL36_DRV_SEL_SPI,                  /**< SPI driver descriptor. */
    ACCEL36_DRV_SEL_I2C                   /**< I2C driver descriptor. */

} accel36_drv_t;

/**
 * @brief Accel 36 Click driver interface.
 * @details Definition of driver interface of Accel 36 Click driver.
 */
struct accel36_s;
typedef err_t ( *accel36_master_io_t )( struct accel36_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 36 Click context object.
 * @details Context object definition of Accel 36 Click driver.
 */
typedef struct accel36_s
{
    digital_in_t int_pin;                 /**< Interrupt pin (unused). */

    i2c_master_t i2c;                     /**< I2C driver object. */
    spi_master_t spi;                     /**< SPI driver object. */

    uint8_t      slave_address;           /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;             /**< Chip select pin descriptor (used for SPI driver). */
    accel36_drv_t drv_sel;                /**< Master driver interface selector. */

    accel36_master_io_t write_f;          /**< Master write function. */
    accel36_master_io_t read_f;           /**< Master read function. */

    float accel_sens;                     /**< Acceleration sensitivity in LSB/g. */

} accel36_t;

/**
 * @brief Accel 36 Click configuration object.
 * @details Configuration object definition of Accel 36 Click driver.
 */
typedef struct
{
    pin_name_t scl;               /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;               /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;              /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;              /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;               /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;           /**< Interrupt pin. */

    uint32_t   i2c_speed;         /**< I2C serial speed. */
    uint8_t    i2c_address;       /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    accel36_drv_t drv_sel;        /**< Master driver interface selector. */

} accel36_cfg_t;

/**
 * @brief Accel 36 Click axes data structure.
 * @details Axes data object definition of Accel 36 Click driver.
 */
typedef struct
{
    float x;    /**< X axis. */
    float y;    /**< Y axis. */
    float z;    /**< Z axis. */

} accel36_axes_t;

/**
 * @brief Accel 36 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCEL36_OK = 0,
    ACCEL36_ERROR = -1,
    ACCEL36_DATA_NOT_READY = -2    

} accel36_return_value_t;

/*!
 * @addtogroup accel36 Accel 36 Click Driver
 * @brief API for configuring and manipulating Accel 36 Click driver.
 * @{
 */

/**
 * @brief Accel 36 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel36_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel36_cfg_setup ( accel36_cfg_t *cfg );

/**
 * @brief Accel 36 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel36_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel36_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel36_drv_interface_sel ( accel36_cfg_t *cfg, accel36_drv_t drv_sel );

/**
 * @brief Accel 36 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel36_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_init ( accel36_t *ctx, accel36_cfg_t *cfg );

/**
 * @brief Accel 36 default configuration function.
 * @details This function executes a default configuration of Accel 36
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel36_default_cfg ( accel36_t *ctx );

/**
 * @brief Accel 36 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_write_reg ( accel36_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Accel 36 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_write_regs ( accel36_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 36 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_read_reg ( accel36_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Accel 36 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_read_regs ( accel36_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 36 check communication function.
 * @details This function checks device communication by reading
 * device ID register.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_check_communication ( accel36_t *ctx );

/**
 * @brief Accel 36 reset device function.
 * @details This function performs a device reset.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_reset_device ( accel36_t *ctx );

/**
 * @brief Accel 36 set full-scale range function.
 * @details This function sets FSR by modifying bits[6:4] of 
 * Range and Resolution Control Register.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] : Full-scale range value, see ACCEL36_FS_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_set_fsr ( accel36_t *ctx, uint8_t fsr );

/**
 * @brief Accel 36 set output data rate function.
 * @details This function sets the ODR by modifying bits[3:0] of Rate register 1.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[in] : ODR selection. See ACCEL36_ODR_x macro definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_set_odr ( accel36_t *ctx, uint8_t odr );

/**
 * @brief Accel 36 check data ready function.
 * @details This function checks whether new acceleration data is available.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_data_ready ( accel36_t *ctx );

/**
 * @brief Accel 36 get acceleration function.
 * @details This function reads and converts the X, Y, Z acceleration data.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @param[out] : Acceleration axes structure.
 * See #accel36_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel36_get_accel ( accel36_t *ctx, accel36_axes_t *accel );

/**
 * @brief Accel 36 get interrupt pin function.
 * @details This function returns the logic state of interrupt pin.
 * @param[in] ctx : Click context object.
 * See #accel36_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t accel36_get_int_pin ( accel36_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL36_H

/*! @} */ // accel36

// ------------------------------------------------------------------------ END
