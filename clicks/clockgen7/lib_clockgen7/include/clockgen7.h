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
 * @file clockgen7.h
 * @brief This file contains API for Clock Gen 7 Click Driver.
 */

#ifndef CLOCKGEN7_H
#define CLOCKGEN7_H

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
#include "drv_pwm.h"
#include "spi_specifics.h"

/*!
 * @addtogroup clockgen7 Clock Gen 7 Click Driver
 * @brief API for configuring and manipulating Clock Gen 7 Click driver.
 * @{
 */

/**
 * @defgroup clockgen7_reg Clock Gen 7 Registers List
 * @brief List of registers of Clock Gen 7 Click driver.
 */

/**
 * @addtogroup clockgen7_reg
 * @{
 */

/**
 * @brief Clock Gen 7 register list.
 * @details Specified register list of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_REG_PLL_CFG1             0x02
#define CLOCKGEN7_REG_PLL_CFG2             0x03
#define CLOCKGEN7_REG_PLL_CFG3             0x04
#define CLOCKGEN7_REG_PLL_CFG4             0x05
#define CLOCKGEN7_REG_RATIO_1              0x06
#define CLOCKGEN7_REG_RATIO_2              0x07
#define CLOCKGEN7_REG_RATIO_3              0x08
#define CLOCKGEN7_REG_RATIO_4              0x09
#define CLOCKGEN7_REG_PLL_CFG5             0x16
#define CLOCKGEN7_REG_PLL_CFG6             0x17
#define CLOCKGEN7_REG_PLL_CFG7             0x1E
#define CLOCKGEN7_REG_DEV_ID_0             0x54
#define CLOCKGEN7_REG_DEV_ID_1             0x55
#define CLOCKGEN7_REG_REV_ID_2             0x56
#define CLOCKGEN7_REG_SW_RESET             0x58
#define CLOCKGEN7_REG_XOSC_DRV1            0x68
#define CLOCKGEN7_REG_XOSC_DRV2            0x69
#define CLOCKGEN7_REG_XOSC_DRV3            0x6A
#define CLOCKGEN7_REG_IDLE_CLK_CFG         0x70

/*! @} */ // clockgen7_reg

/**
 * @defgroup clockgen7_set Clock Gen 7 Registers Settings
 * @brief Settings for registers of Clock Gen 7 Click driver.
 */

/**
 * @addtogroup clockgen7_set
 * @{
 */

/**
 * @brief Clock Gen 7 PLL_CFG1 register setting.
 * @details Specified setting for PLL_CFG1 register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_UNLOCK_MASK              0x80
#define CLOCKGEN7_AUX_OUT_DIS              0x02
#define CLOCKGEN7_CLK_OUT_DIS              0x01

/**
 * @brief Clock Gen 7 PLL_CFG2 register setting.
 * @details Specified setting for PLL_CFG2 register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_RATIO_MOD_MUL_1          0x00
#define CLOCKGEN7_RATIO_MOD_MUL_2          0x20
#define CLOCKGEN7_RATIO_MOD_MUL_4          0x40
#define CLOCKGEN7_RATIO_MOD_MUL_8          0x60
#define CLOCKGEN7_RATIO_MOD_DIV_2          0x80
#define CLOCKGEN7_RATIO_MOD_DIV_4          0xA0
#define CLOCKGEN7_RATIO_MOD_DIV_8          0xC0
#define CLOCKGEN7_RATIO_MOD_DIV_16         0xE0
#define CLOCKGEN7_RATIO_MOD_MASK           0xE0
#define CLOCKGEN7_AUX_OUT_SEL_REF_CLK      0x00
#define CLOCKGEN7_AUX_OUT_SEL_CLK_IN       0x02
#define CLOCKGEN7_AUX_OUT_SEL_CLK_OUT      0x04
#define CLOCKGEN7_AUX_OUT_SEL_UNLOCK       0x06
#define CLOCKGEN7_AUX_OUT_SEL_MASK         0x06
#define CLOCKGEN7_PLL_EN1                  0x01

/**
 * @brief Clock Gen 7 PLL_CFG3 register setting.
 * @details Specified setting for PLL_CFG3 register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_HOLDOVER_EN              0x08

/**
 * @brief Clock Gen 7 PLL_CFG4 register setting.
 * @details Specified setting for PLL_CFG4 register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_FREEZE_EN                0x08
#define CLOCKGEN7_PLL_EN2                  0x01

/**
 * @brief Clock Gen 7 PLL_CFG5 register setting.
 * @details Specified setting for PLL_CFG5 register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_CLK_IN_SKIP_EN           0x80
#define CLOCKGEN7_AUX_OUT_CFG_CMOS         0x00
#define CLOCKGEN7_AUX_OUT_CFG_OPEN_DRAIN   0x40
#define CLOCKGEN7_REF_CLK_IN_DIV_4         0x00
#define CLOCKGEN7_REF_CLK_IN_DIV_2         0x08
#define CLOCKGEN7_REF_CLK_IN_DIV_1         0x10
#define CLOCKGEN7_REF_CLK_IN_DIV_MASK      0x18
#define CLOCKGEN7_SYSCLK_SRC_AUTO          0x00
#define CLOCKGEN7_SYSCLK_SRC_REF_CLK       0x02
#define CLOCKGEN7_SYSCLK_SRC_INT_OSC       0x04
#define CLOCKGEN7_SYSCLK_SRC_MASK          0x06

/**
 * @brief Clock Gen 7 PLL_CFG6 register setting.
 * @details Specified setting for PLL_CFG6 register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_OUT_GATE_EN              0x00
#define CLOCKGEN7_OUT_GATE_DIS             0x10
#define CLOCKGEN7_RATIO_CFG_20_12          0x00
#define CLOCKGEN7_RATIO_CFG_12_20          0x08

/**
 * @brief Clock Gen 7 PLL_CFG7 register setting.
 * @details Specified setting for PLL_CFG7 register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_FLL_BW_MOD_MUL_1         0x00
#define CLOCKGEN7_FLL_BW_MOD_MUL_16        0x80
#define CLOCKGEN7_FLL_BW_1_HZ              0x00
#define CLOCKGEN7_FLL_BW_2_HZ              0x10
#define CLOCKGEN7_FLL_BW_4_HZ              0x20
#define CLOCKGEN7_FLL_BW_8_HZ              0x30
#define CLOCKGEN7_FLL_BW_16_HZ             0x40
#define CLOCKGEN7_FLL_BW_32_HZ             0x50
#define CLOCKGEN7_FLL_BW_64_HZ             0x60
#define CLOCKGEN7_FLL_BW_128_HZ            0x70
#define CLOCKGEN7_FLL_BW_MASK              0x70

/**
 * @brief Clock Gen 7 SW_RESET register setting.
 * @details Specified setting for SW_RESET register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_SW_RST                   0x5A

/**
 * @brief Clock Gen 7 IDLE_CLK_CFG register setting.
 * @details Specified setting for IDLE_CLK_CFG register of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_IDLE_CLK_EN              0x08
#define CLOCKGEN7_IDLE_CLK_FREQ_DIV_4      0x02
#define CLOCKGEN7_IDLE_CLK_FREQ_DIV_6      0x03
#define CLOCKGEN7_IDLE_CLK_FREQ_DIV_8      0x04
#define CLOCKGEN7_IDLE_CLK_FREQ_DIV_10     0x05
#define CLOCKGEN7_IDLE_CLK_FREQ_DIV_12     0x06
#define CLOCKGEN7_IDLE_CLK_FREQ_DIV_14     0x07
#define CLOCKGEN7_IDLE_CLK_FREQ_MASK       0x07

/**
 * @brief Clock Gen 7 device ID setting.
 * @details Specified setting for device ID of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_DEVICE_ID                0x2501

/**
 * @brief Clock Gen 7 register shadow copies default setting.
 * @details Specified setting for register shadow copies default of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_SHADOW_COPY_DEF          0x00

/**
 * @brief Clock Gen 7 auto-increment setting.
 * @details Specified setting for auto-increment of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_AUTO_INCREMENT           0x80

/**
 * @brief Clock Gen 7 SPI chip address setting.
 * @details Specified setting for SPI chip address of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_SPI_CHIP_ADDRESS         0x9E

/**
 * @brief Clock Gen 7 default PWM settings.
 * @details Specified setting for default PWM of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_DEF_DUTY_CYCLE           0.5

/**
 * @brief Clock Gen 7 ratio format setting.
 * @details Specified setting for ratio format of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_RATIO_SCALE_12_20        1048576.0
#define CLOCKGEN7_RATIO_SCALE_20_12        4096.0

/**
 * @brief Clock Gen 7 ratio byte number setting.
 * @details Specified setting for ratio byte number of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_RATIO_NUM_BYTES          4

/**
 * @brief Clock Gen 7 CLK_IN reference and ratio setting.
 * @details Specified setting for CLK_IN reference and ratio of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_DEF_CLK_IN_FREQ          48000
#define CLOCKGEN7_DEF_RATIO                512.0

/**
 * @brief Clock Gen 7 ratio limits setting.
 * @details Specified setting for ratio limits of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_RATIO_MAX_12_20          4096.0
#define CLOCKGEN7_RATIO_MAX_20_12          1048576.0
#define CLOCKGEN7_RATIO_MIN                0.0

/**
 * @brief Clock Gen 7 PLL lock status setting.
 * @details Specified setting for PLL lock status of Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_STATUS_LOCKED            0
#define CLOCKGEN7_STATUS_UNLOCKED          1

/**
 * @brief Clock Gen 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Clock Gen 7 Click driver.
 */
#define CLOCKGEN7_DEVICE_ADDRESS_GND       0x4E
#define CLOCKGEN7_DEVICE_ADDRESS_VDD       0x4F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b clockgen7_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CLOCKGEN7_SET_DATA_SAMPLE_EDGE     SET_SPI_DATA_SAMPLE_EDGE
#define CLOCKGEN7_SET_DATA_SAMPLE_MIDDLE   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // clockgen7_set

/**
 * @defgroup clockgen7_map Clock Gen 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Clock Gen 7 Click driver.
 */

/**
 * @addtogroup clockgen7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Clock Gen 7 Click to the selected MikroBUS.
 */
#define CLOCKGEN7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cin  = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // clockgen7_map
/*! @} */ // clockgen7

/**
 * @brief Clock Gen 7 Click driver selector.
 * @details Selects target driver interface of Clock Gen 7 Click driver.
 */
typedef enum
{
    CLOCKGEN7_DRV_SEL_SPI,                  /**< SPI driver descriptor. */
    CLOCKGEN7_DRV_SEL_I2C                   /**< I2C driver descriptor. */

} clockgen7_drv_t;

/**
 * @brief Clock Gen 7 Click driver interface.
 * @details Definition of driver interface of Clock Gen 7 Click driver.
 */
struct clockgen7_s;
typedef err_t ( *clockgen7_master_io_t )( struct clockgen7_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Clock Gen 7 Click context object.
 * @details Context object definition of Clock Gen 7 Click driver.
 */
typedef struct clockgen7_s
{
    pwm_t cin;                                      /**< PWM driver object. */
    i2c_master_t i2c;                               /**< I2C driver object. */
    spi_master_t spi;                               /**< SPI driver object. */

    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */
    clockgen7_drv_t drv_sel;                        /**< Master driver interface selector. */

    clockgen7_master_io_t write_f;                  /**< Master write function. */
    clockgen7_master_io_t read_f;                   /**< Master read function. */

    uint8_t shadow_pll_cfg1;                        /**< Shadow copy of PLL_CFG1 register (for SPI write-only interface). */
    uint8_t shadow_pll_cfg2;                        /**< Shadow copy of PLL_CFG2 register (for SPI write-only interface). */
    uint8_t shadow_pll_cfg4;                        /**< Shadow copy of PLL_CFG4 register (for SPI write-only interface). */
    uint8_t shadow_pll_cfg5;                        /**< Shadow copy of PLL_CFG5 register (for SPI write-only interface). */
    uint8_t shadow_pll_cfg6;                        /**< Shadow copy of PLL_CFG6 register (for SPI write-only interface). */

    uint8_t ratio_format;                           /**< Active ratio format. */

} clockgen7_t;

/**
 * @brief Clock Gen 7 Click configuration object.
 * @details Configuration object definition of Clock Gen 7 Click driver.
 */
typedef struct
{
    pin_name_t scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t cin;                                 /**< PWM pin. */

    uint32_t   i2c_speed;                           /**< I2C serial speed. */
    uint8_t    i2c_address;                         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    uint32_t   cin_freq;                            /**< CLK_IN reference frequency. */

    clockgen7_drv_t drv_sel;                        /**< Master driver interface selector. */

} clockgen7_cfg_t;

/**
 * @brief Clock Gen 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CLOCKGEN7_OK = 0,
    CLOCKGEN7_ERROR = -1

} clockgen7_return_value_t;

/*!
 * @addtogroup clockgen7 Clock Gen 7 Click Driver
 * @brief API for configuring and manipulating Clock Gen 7 Click driver.
 * @{
 */

/**
 * @brief Clock Gen 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #clockgen7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void clockgen7_cfg_setup ( clockgen7_cfg_t *cfg );

/**
 * @brief Clock Gen 7 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #clockgen7_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #clockgen7_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void clockgen7_drv_interface_sel ( clockgen7_cfg_t *cfg, clockgen7_drv_t drv_sel );

/**
 * @brief Clock Gen 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #clockgen7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_init ( clockgen7_t *ctx, clockgen7_cfg_t *cfg );

/**
 * @brief Clock Gen 7 default configuration function.
 * @details This function executes a default configuration of Clock Gen 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t clockgen7_default_cfg ( clockgen7_t *ctx );

/**
 * @brief Clock Gen 7 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_write_reg ( clockgen7_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Clock Gen 7 write registers function.
 * @details This function writes a sequential block of data starting from the
 * selected register.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_write_regs ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Clock Gen 7 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Register reads are supported over the I2C interface only. The CS2501
 * SPI is write-only, so this function returns an error in SPI mode.
 */
err_t clockgen7_read_reg ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Clock Gen 7 read registers function.
 * @details This function reads a sequential block of data starting from the
 * selected register.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Register reads are supported over the I2C interface only. The CS2501
 * SPI is write-only, so this function returns an error in SPI mode.
 */
err_t clockgen7_read_regs ( clockgen7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Clock Gen 7 software reset function.
 * @details This function performs a software reset by writing 0x5A 
 * to the SW_RESET register.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_sw_reset ( clockgen7_t *ctx );

/**
 * @brief Clock Gen 7 check communication function.
 * @details This function checks communication by reading and verifying the
 * device ID.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on register reads and is supported over the I2C
 * interface only.
 */
err_t clockgen7_check_communication ( clockgen7_t *ctx );

/**
 * @brief Clock Gen 7 set CLK_IN frequency function.
 * @details This function sets the CLK_IN frequency generated on the
 * CIN pin.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] freq : CLK_IN frequency in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_set_clk_in_freq ( clockgen7_t *ctx, uint32_t freq );

/**
 * @brief Clock Gen 7 set ratio function.
 * @details This function sets the PLL ratio that defines the CLK_OUT to CLK_IN
 * multiplication factor.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] ratio : CLK_OUT to CLK_IN multiplication factor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_set_ratio ( clockgen7_t *ctx, float ratio );

/**
 * @brief Clock Gen 7 PLL enable function.
 * @details This function enables the PLL by setting both PLL enable bits.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_pll_enable ( clockgen7_t *ctx );

/**
 * @brief Clock Gen 7 PLL disable function.
 * @details This function disables the PLL by clearing both PLL enable bits.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_pll_disable ( clockgen7_t *ctx );

/**
 * @brief Clock Gen 7 get lock status function.
 * @details This function reads the PLL lock status from the
 * PLL_CFG1 register.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[out] status : @li @c 0 - PLL locked,
 *                      @li @c 1 - PLL unlocked.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on register reads and is supported over the I2C
 * interface only.
 */
err_t clockgen7_get_lock_status ( clockgen7_t *ctx, uint8_t *status );

/**
 * @brief Clock Gen 7 set AUX_OUT function.
 * @details This function selects the signal routed to the AUX_OUT pin.
 * @param[in] ctx : Click context object.
 * See #clockgen7_t object definition for detailed explanation.
 * @param[in] aux_sel : @li @c 0x00 - REF_CLK_IN,
 *                      @li @c 0x02 - CLK_IN,
 *                      @li @c 0x04 - CLK_OUT,
 *                      @li @c 0x06 - PLL unlock.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen7_set_aux_out ( clockgen7_t *ctx, uint8_t aux_sel );

#ifdef __cplusplus
}
#endif
#endif // CLOCKGEN7_H

/*! @} */ // clockgen7

// ------------------------------------------------------------------------ END
