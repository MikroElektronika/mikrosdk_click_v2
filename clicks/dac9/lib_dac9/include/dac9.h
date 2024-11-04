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
 * @file dac9.h
 * @brief This file contains API for DAC 9 Click Driver.
 */

#ifndef DAC9_H
#define DAC9_H

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
 * @addtogroup dac9 DAC 9 Click Driver
 * @brief API for configuring and manipulating DAC 9 Click driver.
 * @{
 */

/**
 * @defgroup dac9_reg DAC 9 Registers List
 * @brief List of registers of DAC 9 Click driver.
 */

/**
 * @addtogroup dac9_reg
 * @{
 */

/**
 * @brief DAC 9 description register.
 * @details Specified register for description of DAC 9 Click driver.
 */
#define DAC9_REG_NOOP                      0x00
#define DAC9_REG_DEVID                     0x01
#define DAC9_REG_SYNC                      0x02
#define DAC9_REG_CONFIG                    0x03
#define DAC9_REG_GAIN                      0x04
#define DAC9_REG_TRIGGER                   0x05
#define DAC9_REG_STATUS                    0x07
#define DAC9_REG_DAC                       0x08

/*! @} */ // dac9_reg

/**
 * @defgroup dac9_set DAC 9 Registers Settings
 * @brief Settings for registers of DAC 9 Click driver.
 */

/**
 * @addtogroup dac9_set
 * @{
 */

/**
 * @brief DAC 9 description setting.
 * @details Specified setting for description of DAC 9 Click driver.
 */
#define DAC9_SYNC_DISABLE                0x0000
#define DAC9_SYNC_ENABLE                 0x0001

#define DAC9_CONFIG_REF_PWDWN_ENABLE     0x0000
#define DAC9_CONFIG_REF_PWDWN_DISABLE    0x0100
#define DAC9_CONFIG_REF_PWDWN_BIT_MASK   0x0100
#define DAC9_CONFIG_DAC_PWDWN_DISABLE    0x0000
#define DAC9_CONFIG_DAC_PWDWN_ENABLE     0x0001
#define DAC9_CONFIG_DAC_PWDWN_BIT_MASK   0x0001
    
#define DAC9_GAIN_REF_DIV_DISABLE        0x0000
#define DAC9_GAIN_REF_DIV_2              0x0100
#define DAC9_GAIN_REF_DIV_BIT_MASK       0x0100
#define DAC9_GAIN_BUFF_GAIN_1            0x0000
#define DAC9_GAIN_BUFF_GAIN_2            0x0001
#define DAC9_GAIN_BUFF_GAIN_BIT_MASK     0x0001

#define DAC9_TRIGGER_LDAC                0x0010
#define DAC9_TRIGGER_SOFT_RESET          0x000A

#define DAC9_STATUS_REF_ALARM_BIT_MASK   0x0001

/**
 * @brief DAC 9 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 9 Click driver.
 */
#define DAC9_I2C_ADR_AGND                0x48
#define DAC9_I2C_ADR_VDD                 0x49
#define DAC9_I2C_ADR_SDA                 0x4A
#define DAC9_I2C_ADR_SCL                 0x4B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC9_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DAC9_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac9_set

/**
 * @defgroup dac9_map DAC 9 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 9 Click driver.
 */

/**
 * @addtogroup dac9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 9 Click to the selected MikroBUS.
 */
#define DAC9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // dac9_map
/*! @} */ // dac9

/**
 * @brief DAC 9 Click driver selector.
 * @details Selects target driver interface of DAC 9 Click driver.
 */
typedef enum
{
   DAC9_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   DAC9_DRV_SEL_I2C       /**< I2C driver descriptor. */

} dac9_drv_t;

/**
 * @brief DAC 9 Click driver interface.
 * @details Definition of driver interface of DAC 9 Click driver.
 */
typedef err_t ( *dac9_master_io_t )( struct dac9_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief DAC 9 Click context object.
 * @details Context object definition of DAC 9 Click driver.
 */
typedef struct dac9_s
{
    i2c_master_t  i2c;                              /**< I2C driver object. */
    spi_master_t  spi;                              /**< SPI driver object. */

    uint8_t     slave_address;                      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                        /**< Chip select pin descriptor (used for SPI driver). */
    dac9_drv_t  drv_sel;               /**< Master driver interface selector. */

    dac9_master_io_t  write_f;         /**< Master write function. */
    dac9_master_io_t  read_f;          /**< Master read function. */

} dac9_t;

/**
 * @brief DAC 9 Click configuration object.
 * @details Configuration object definition of DAC 9 Click driver.
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

   dac9_drv_t  drv_sel;                   /**< Master driver interface selector. */

} dac9_cfg_t;

/**
 * @brief DAC 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DAC9_OK = 0,
   DAC9_ERROR = -1

} dac9_return_value_t;

/*!
 * @addtogroup dac9 DAC 9 Click Driver
 * @brief API for configuring and manipulating DAC 9 Click driver.
 * @{
 */

/**
 * @brief DAC 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac9_cfg_setup ( dac9_cfg_t *cfg );

/**
 * @brief DAC 9 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #dac9_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #dac9_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void dac9_drv_interface_selection ( dac9_cfg_t *cfg, dac9_drv_t drv_sel );

/**
 * @brief DAC 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac9_init ( dac9_t *ctx, dac9_cfg_t *cfg );

/**
 * @brief DAC 9 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac9_generic_write ( dac9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 9 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac9_generic_read ( dac9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Enable synchronous function.
 * @details The function is used to set synchronous or asynchronous mode.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] en_sync : DAC output mode
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
**/
err_t dac9_enable_sync ( dac9_t *ctx, uint8_t en_sync );

/**
 * @brief Set config function.
 * @details The function is used to set the devices configuration.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] en_ref_pwdwn : Internal reference mode.
 * @param[in] en_dac_pwdwn : DAC in power-up mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
**/
err_t dac9_set_config ( dac9_t *ctx, uint16_t en_ref_pwdwn, uint16_t en_dac_pwdwn );

/**
 * @brief Set gain function.
 * @details The function is used to set gain and internal voltage reference.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] en_ref_div : Reference voltage mode.
 * @param[in] en_buff_gain : DAC gain mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
**/
err_t dac9_set_gain ( dac9_t *ctx, uint16_t en_ref_div, uint16_t en_buff_gain );

/**
 * @brief Set synchronously load function.
 * @details The function is used to set 'LDAC' bit in order to synchronously
 * load the DAC in synchronous mode, This bit is self resetting.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @return Nothing.
**/
void dac9_set_synchronously_load ( dac9_t *ctx );

/**
 * @brief Set reset function.
 * @details The function is used to perform software reset.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @return Nothing.
**/
void dac9_soft_reset ( dac9_t *ctx );

/**
 * @brief Get ref alarm function.
 * @details The function is used to get reference alarm
 * of the device.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @return @li @c  0x00 - Ok.,
 *         @li @c  0x01 - Difference between the reference and supply pins
 *                        is below a minimum analog threshold.
**/
uint8_t dac9_get_ref_alarm ( dac9_t *ctx );

/**
 * @brief Set Vout function.
 * @details The function is used set Vout ( mV ) by calculating input data 
 * and writing it to the DAC data register.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] vout_mv : Vout in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
**/
err_t dac9_set_vout ( dac9_t *ctx, uint16_t vout_mv );

#ifdef __cplusplus
}
#endif
#endif // DAC9_H

/*! @} */ // dac9

// ------------------------------------------------------------------------ END
