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
 * @file clockgen4.h
 * @brief This file contains API for Clock Gen 4 Click Driver.
 */

#ifndef CLOCKGEN4_H
#define CLOCKGEN4_H

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
 * @addtogroup clockgen4 Clock Gen 4 Click Driver
 * @brief API for configuring and manipulating Clock Gen 4 Click driver.
 * @{
 */

/**
 * @defgroup clockgen4_reg Clock Gen 4 Registers List
 * @brief List of registers of Clock Gen 4 Click driver.
 */

/**
 * @addtogroup clockgen4_reg
 * @{
 */

/**
 * @brief Clock Gen 4 description register.
 * @details Specified register for description of Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_REG_DEV_ID         0x01
#define CLOCKGEN4_REG_DEV_CTL        0x02
#define CLOCKGEN4_REG_DEV_CFG_1      0x03
#define CLOCKGEN4_REG_GLOB_CFG       0x05
#define CLOCKGEN4_REG_M_MSB          0x06
#define CLOCKGEN4_REG_L_MSB          0x07
#define CLOCKGEN4_REG_M_LSB          0x08
#define CLOCKGEN4_REG_L_LSB          0x09
#define CLOCKGEN4_REG_FNC_CFG_1      0x16
#define CLOCKGEN4_REG_FNC_CFG_2      0x17

/*! @} */ // clockgen4_reg

/**
 * @defgroup clockgen4_set Clock Gen 4 Registers Settings
 * @brief Settings for registers of Clock Gen 4 Click driver.
 */

/**
 * @addtogroup clockgen4_set
 * @{
 */

/**
 * @brief Clock Gen 4 description setting.
 * @details Specified setting for description of Clock Gen 4 Click driver.
 */

/**
 * @brief Clock Gen 4 Increment Bit.
 * @details Increment Bit of Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_INCR_ENABLE        0x80
#define CLOCKGEN4_INCR_DISABLE       0x00

/**
 * @brief Clock Gen 4 device control.
 * @details Device control of Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_PLL_UNLOCKED       0x00
#define CLOCKGEN4_PLL_LOCKED         0x80
#define CLOCKGEN4_AUX_OUT_EN         0x00
#define CLOCKGEN4_AUX_OUT_DIS        0x02
#define CLOCKGEN4_CLK_OUT_EN         0x00
#define CLOCKGEN4_CLK_OUT_DIS        0x01

/**
 * @brief Clock Gen 4 device configuration 1.
 * @details Device configuration 1 of Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_R_MOD_SEL_L_0      0x00
#define CLOCKGEN4_R_MOD_SEL_L_1      0x20
#define CLOCKGEN4_R_MOD_SEL_L_2      0x40
#define CLOCKGEN4_R_MOD_SEL_L_3      0x60
#define CLOCKGEN4_R_MOD_SEL_R_1      0x80
#define CLOCKGEN4_R_MOD_SEL_R_2      0xA0
#define CLOCKGEN4_R_MOD_SEL_R_3      0xC0
#define CLOCKGEN4_R_MOD_SEL_R_4      0xE0
#define CLOCKGEN4_REG_CLK            0x00
#define CLOCKGEN4_CLK_OUT            0x04
#define CLOCKGEN4_PLL_STAT_IND       0x06
#define CLOCKGEN4_DEV_CFG_1_EN       0x01
#define CLOCKGEN4_DEV_CFG_1_DIS      0x00

/**
 * @brief Clock Gen 4 global configuration.
 * @details Global configuration of Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_DEV_CFG_FRZ        0x00
#define CLOCKGEN4_DEV_CFG_UNFRZ      0x08
#define CLOCKGEN4_DEV_CFG_2_EN       0x01
#define CLOCKGEN4_DEV_CFG_2_DIS      0x00

/**
 * @brief Clock Gen 4 function configuration 1.
 * @details Function configuration 1 of Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_AUX_OUT_ACT_H      0x00 
#define CLOCKGEN4_AUX_OUT_ACT_L      0x40 
#define CLOCKGEN4_REF_CLK_DIV_4      0x00 
#define CLOCKGEN4_REF_CLK_DIV_2      0x08 
#define CLOCKGEN4_REF_CLK_DIV_1      0x10 

/**
 * @brief Clock Gen 4 function configuration 2.
 * @details Function configuration 2 of Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_CLK_OUT_UNL_L      0x00
#define CLOCKGEN4_CLK_OUT_UNL_U      0x10

/**
 * @brief Clock Gen 4 input clock.
 * @details Input clock of Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_REF_CLK_25_MHZ     25.0

/**
 * @brief Clock Gen 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Clock Gen 4 Click driver.
 */
#define CLOCKGEN4_I2C_ADR_GND    0x4E
#define CLOCKGEN4_I2C_ADR_VCC    0x4F

#define CLOCKGEN4_SPI_CHIP_ADR   0x9E
/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b clockgen4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CLOCKGEN4_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define CLOCKGEN4_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE
/*! @} */ // clockgen4_set

/**
 * @defgroup clockgen4_map Clock Gen 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Clock Gen 4 Click driver.
 */

/**
 * @addtogroup clockgen4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Clock Gen 4 Click to the selected MikroBUS.
 */
#define CLOCKGEN4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \

/*! @} */ // clockgen4_map
/*! @} */ // clockgen4

/**
 * @brief Clock Gen 4 Click driver selector.
 * @details Selects target driver interface of Clock Gen 4 Click driver.
 */
typedef enum
{
   CLOCKGEN4_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   CLOCKGEN4_DRV_SEL_I2C       /**< I2C driver descriptor. */

} clockgen4_drv_t;

/**
 * @brief Clock Gen 4 Click driver interface.
 * @details Definition of driver interface of Clock Gen 4 Click driver.
 */
typedef err_t ( *clockgen4_master_io_t )( struct clockgen4_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Clock Gen 4 Click context object.
 * @details Context object definition of Clock Gen 4 Click driver.
 */
typedef struct clockgen4_s
{
    i2c_master_t  i2c;                                  /**< I2C driver object. */
    spi_master_t  spi;                                  /**< SPI driver object. */
                                                        
    uint8_t     slave_address;                          /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                            /**< Chip select pin descriptor (used for SPI driver). */
    clockgen4_drv_t  drv_sel;                           /**< Master driver interface selector. */
                                                        
    clockgen4_master_io_t  write_f;                     /**< Master write function. */
    clockgen4_master_io_t  read_f;                      /**< Master read function. */

} clockgen4_t;

/**
 * @brief Clock Gen 4 Click configuration object.
 * @details Configuration object definition of Clock Gen 4 Click driver.
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

   clockgen4_drv_t  drv_sel;                            /**< Master driver interface selector. */

} clockgen4_cfg_t;

/**
 * @brief Clock Gen 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CLOCKGEN4_OK = 0,
   CLOCKGEN4_ERROR = -1

} clockgen4_return_value_t;

/*!
 * @addtogroup clockgen4 Clock Gen 4 Click Driver
 * @brief API for configuring and manipulating Clock Gen 4 Click driver.
 * @{
 */

/**
 * @brief Clock Gen 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #clockgen4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void clockgen4_cfg_setup ( clockgen4_cfg_t *cfg );

/**
 * @brief Clock Gen 4 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #clockgen4_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #clockgen4_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void clockgen4_drv_interface_selection ( clockgen4_cfg_t *cfg, clockgen4_drv_t drv_sel );

/**
 * @brief Clock Gen 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #clockgen4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen4_init ( clockgen4_t *ctx, clockgen4_cfg_t *cfg );

/**
 * @brief Clock Gen 4 default configuration function.
 * @details This function executes a default configuration of Clock Gen 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t clockgen4_default_cfg ( clockgen4_t *ctx );

/**
 * @brief Clock Gen 4 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen4_generic_write ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Clock Gen 4 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen4_generic_read ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Clock Gen 4 device control function.
 * @details Function is used to write to device control register in order to apply settings.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] dev_ctl : 8-bit input data.
 * @return Nothing.
 * @note Settings available : Unlock Indicator(Read Only), Auxiliary Output Disable.
 * PLL Clock Output Disable.
 */
void clockgen4_dev_ctl ( clockgen4_t *ctx, uint8_t dev_ctl );

/**
 * @brief Clock Gen 4 device configuration function.
 * @details Function is used to write to device configuration 1 register 
 * in order to apply settings.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] dev_cfg : 8-bit input data.
 * @return Nothing.
 * @note Settings available : R-Mod Selection, Auxiliary Output Source Selection.
 * Enable Device Configuration Registers 1.
 */
void clockgen4_dev_cfg ( clockgen4_t *ctx, uint8_t dev_cfg );

/**
 * @brief Clock Gen 4 global configuration function.
 * @details Function is used to write to function configuration 2 register
 * in order to apply settings.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] glob_cfg : 8-bit input data.
 * @return Nothing.
 * @note Settings available : Device Configuration Freeze,
 * Enable Device Configuration Registers 2.
 */
void clockgen4_glob_cfg ( clockgen4_t *ctx, uint8_t glob_cfg );

/**
 * @brief Clock Gen 4 configuration 1 function.
 * @details Function is used to write to function configuration 1 register
 * in order to apply settings.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] fnc_cfg : 8-bit input data.
 * @return Nothing.
 * @note Settings available : AUX PLL Lock Output Configuration,
 * Reference Clock Input Divider.
 */
void clockgen4_fnc_cfg_1 ( clockgen4_t *ctx, uint8_t fnc_cfg );

/**
 * @brief Clock Gen 4 configuration 2 function.
 * @details Function is used to write to function configuration 2 register
 * in order to apply settings.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] fnc_cfg : 8-bit input data.
 * @return Nothing.
 * @note Settings available : Enable PLL Clock Output on Unlock.
 */
void clockgen4_fnc_cfg_2 ( clockgen4_t *ctx, uint8_t fnc_cfg );

/**
 * @brief Clock Gen 4 set ratio function.
 * @details Function is used to set the ratio between the output signal and
 * the input clock.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] ratio :float value that represents the ratio between the output signal 
 * and the input clock.
 * @return sdr : 32-bit calculated input data.
 * @note To calculate the Ratio to store in the register(s), divide the desired 
 * output clock frequency by the given input clock.
 */
uint32_t clockgen4_set_ratio ( clockgen4_t *ctx, float ratio );


#ifdef __cplusplus
}
#endif
#endif // CLOCKGEN4_H

/*! @} */ // clockgen4

// ------------------------------------------------------------------------ END
