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
 * @file dac15.h
 * @brief This file contains API for DAC 15 Click Driver.
 */

#ifndef DAC15_H
#define DAC15_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup dac15 DAC 15 Click Driver
 * @brief API for configuring and manipulating DAC 15 Click driver.
 * @{
 */

/**
 * @defgroup dac15_reg DAC 15 Registers List
 * @brief List of registers of DAC 15 Click driver.
 */

/**
 * @addtogroup dac15_reg
 * @{
 */

/**
 * @brief DAC 15 description register.
 * @details Specified register for description of DAC 15 Click driver.
 */
#define DAC15_REG_NOOP                      0x00
#define DAC15_REG_DEVID                     0x01
#define DAC15_REG_SYNC                      0x02
#define DAC15_REG_CONFIG                    0x03
#define DAC15_REG_GAIN                      0x04
#define DAC15_REG_TRIGGER                   0x05
#define DAC15_REG_BRDCAST                   0x06
#define DAC15_REG_STATUS                    0x07
#define DAC15_REG_DAC_A_DATA                0x08
#define DAC15_REG_DAC_B_DATA                0x09

/*! @} */ // dac15_reg

/**
 * @defgroup dac15_set DAC 15 Registers Settings
 * @brief Settings for registers of DAC 15 Click driver.
 */

/**
 * @addtogroup dac15_set
 * @{
 */

/**
 * @brief DAC 15 description of device ID data.
 * @details Specified device ID data of DAC 15 Click driver.
 */
#define DAC15_DEVICE_ID                     0x0295u

/**
 * @brief DAC 15 SYNC register field descriptions.
 * @details Specified SYNC register field data of DAC 15 Click driver.
 */
#define DAC15_SYNC_DAC_B_BRDCAST_DIS        0x0000u
#define DAC15_SYNC_DAC_B_BRDCAST_EN         0x0100u
#define DAC15_SYNC_DAC_A_BRDCAST_DIS        0x0000u
#define DAC15_SYNC_DAC_A_BRDCAST_EN         0x0080u
#define DAC15_SYNC_DAC_B_SYNC_DIS           0x0000u
#define DAC15_SYNC_DAC_B_SYNC_EN            0x0002u
#define DAC15_SYNC_DAC_A_SYNC_DIS           0x0000u
#define DAC15_SYNC_DAC_A_SYNC_EN            0x0001u

/**
 * @brief DAC 15 CONFIG register field descriptions.
 * @details Specified CONFIG register field data of DAC 15 Click driver.
 */
#define DAC15_CONFIG_REF_PWUP               0x0000u
#define DAC15_CONFIG_REF_PWDWN              0x0100u
#define DAC15_CONFIG_DAC_B_PWUP             0x0000u
#define DAC15_CONFIG_DAC_B_PWDWN            0x0002u
#define DAC15_CONFIG_DAC_A_PWUP             0x0000u
#define DAC15_CONFIG_DAC_A_PWDWN            0x0001u

/**
 * @brief DAC 15 GAIN register field descriptions.
 * @details Specified GAIN register field data of DAC 15 Click driver.
 */
#define DAC15_GAIN_REF_DIV_1                0x0000u
#define DAC15_GAIN_REF_DIV_2                0x0100u
#define DAC15_GAIN_BUFF_B_GAIN_1            0x0000u
#define DAC15_GAIN_BUFF_B_GAIN_2            0x0002u
#define DAC15_GAIN_BUFF_A_GAIN_1            0x0000u
#define DAC15_GAIN_BUFF_A_GAIN_2            0x0001u

/**
 * @brief DAC 15 TRIGGER register field descriptions.
 * @details Specified TRIGGER register field data of DAC 15 Click driver.
 */
#define DAC15_TRIGGER_LDA_SYNC_LOAD_DAC     0x0010u
#define DAC15_TRIGGER_SOFT_RESET            0x000Au

/**
 * @brief DAC 15 DAC selection data.
 * @details Specified DAC selection data of DAC 15 Click driver.
 */
#define DAC15_SET_DAC_A                     0
#define DAC15_SET_DAC_B                     1

/**
 * @brief DAC 15 calculation data.
 * @details Specified calculation data of DAC 15 Click driver.
 */
#define DAC15_DAC_RES_16BIT                 0xFFFFu
#define DAC15_MAX_DAC_DATA                  65535.0f
#define DAC15_MAX_VOUT_MV                   3300.0f
#define DAC15_VREF_3V3                      3.3f
#define DAC15_VREF_5V                       5.0f
#define DAC15_CONV_DEV_MV_TO_V              1000.0f


/**
 * @brief DAC 15 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 15 Click driver.
 */
#define DAC15_DEVICE_ADDRESS_GND            0x48
#define DAC15_DEVICE_ADDRESS_VCC            0x49

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac15_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC15_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DAC15_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac15_set

/**
 * @defgroup dac15_map DAC 15 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 15 Click driver.
 */

/**
 * @addtogroup dac15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 15 Click to the selected MikroBUS.
 */
#define DAC15_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // dac15_map
/*! @} */ // dac15

/**
 * @brief DAC 15 Click driver selector.
 * @details Selects target driver interface of DAC 15 Click driver.
 */
typedef enum
{
    DAC15_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    DAC15_DRV_SEL_I2C       /**< I2C driver descriptor. */

} dac15_drv_t;

/**
 * @brief DAC 15 Click driver interface.
 * @details Definition of driver interface of DAC 15 Click driver.
 */
typedef err_t ( *dac15_master_io_t )( struct dac15_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief DAC 15 Click context object.
 * @details Context object definition of DAC 15 Click driver.
 */
typedef struct dac15_s
{
    digital_out_t rst;    /**< Reset select pin. */
    
    i2c_master_t i2c;     /**< I2C driver object. */
    spi_master_t spi;     /**< SPI driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
    dac15_drv_t drv_sel;           /**< Master driver interface selector. */

    dac15_master_io_t write_f;     /**< Master write function. */
    dac15_master_io_t read_f;      /**< Master read function. */
    
    float vref;    /**< Voltage reference. */

} dac15_t;

/**
 * @brief DAC 15 Click configuration object.
 * @details Configuration object definition of DAC 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rst;     /**< Reset select pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

    dac15_drv_t drv_sel;    /**< Master driver interface selector. */
    float vref;             /**< Voltage reference. */

} dac15_cfg_t;

/**
 * @brief DAC 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC15_OK = 0,
    DAC15_ERROR = -1

} dac15_return_value_t;

/*!
 * @addtogroup dac15 DAC 15 Click Driver
 * @brief API for configuring and manipulating DAC 15 Click driver.
 * @{
 */

/**
 * @brief DAC 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac15_cfg_setup ( dac15_cfg_t *cfg );

/**
 * @brief DAC 15 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #dac15_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #dac15_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void dac15_drv_interface_selection ( dac15_cfg_t *cfg, dac15_drv_t drv_sel );

/**
 * @brief DAC 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_init ( dac15_t *ctx, dac15_cfg_t *cfg );

/**
 * @brief DAC 15 default configuration function.
 * @details This function executes a default configuration of DAC 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac15_default_cfg ( dac15_t *ctx );

/**
 * @brief DAC 15 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_generic_write ( dac15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 15 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_generic_read ( dac15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DAC 15 write register function.
 * @details This function writes a desired data word to the selected register
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_write_reg ( dac15_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 15 read register function.
 * @details This function reads data word from the selected register
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_read_reg ( dac15_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 15 DACs power up to zero scale function.
 * @details This function sets DACs power up to zero scale
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dac15_power_up_to_zero_scale ( dac15_t *ctx );

/**
 * @brief DAC 15 DACs s power up to midscale function.
 * @details This function sets DACs s power up to midscale
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dac15_power_up_to_midscale ( dac15_t *ctx );

/**
 * @brief DAC 15 get device ID function.
 * @details This function reads device ID data
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_get_device_id ( dac15_t *ctx, uint16_t *device_id );

/**
 * @brief DAC 15 set sync mode function.
 * @details This function set sync mode to synchronously load those DACs
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_set_sync_mode ( dac15_t *ctx );

/**
 * @brief DAC 15 soft reset function.
 * @details This function resets the device to its default state
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_soft_reset ( dac15_t *ctx );

/**
 * @brief DAC 15 set DAC data function.
 * @details This function sets the raw DAC data for the selected DAC channel
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] dac_sel : DAC Vout channel: 
 *         @li @c 0 (DAC15_SET_DAC_A) - VOUTA,
 *         @li @c 1 (DAC15_SET_DAC_B) - VOUTB.
 * @param[in] dac_data : DAC raw data, 16-bit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_set_dac_data ( dac15_t *ctx, uint8_t dac_sel, uint16_t dac_data );

/**
 * @brief DAC 15 get DAC data function.
 * @details This function read the raw DAC data for the selected DAC channel
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] dac_sel : DAC Vout channel: 
 *         @li @c 0 (DAC15_SET_DAC_A) - VOUTA,
 *         @li @c 1 (DAC15_SET_DAC_B) - VOUTB.
 * @param[out] dac_data : DAC raw data, 16-bit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_get_dac_data ( dac15_t *ctx, uint8_t dac_sel, uint16_t *dac_data );

/**
 * @brief DAC 15 set DAC output voltage function.
 * @details This function sets the DAC output voltage for the selected DAC channel
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] dac_sel : DAC Vout channel: 
 *         @li @c 0 (DAC15_SET_DAC_A) - VOUTA,
 *         @li @c 1 (DAC15_SET_DAC_B) - VOUTB.
 * @param[in] vtg : DAC output voltage [0V-3.3V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_set_dac_vout ( dac15_t *ctx, uint8_t dac_sel, float vtg );

/**
 * @brief DAC 15 get DAC output voltage function.
 * @details This function reads the DAC output voltage for the selected DAC channel
 * of the DAC80502, Dual, 16-Bit, 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs 
 * With Precision Internal Reference on the USB-C Sink 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] dac_sel : DAC Vout channel: 
 *         @li @c 0 (DAC15_SET_DAC_A) - VOUTA,
 *         @li @c 1 (DAC15_SET_DAC_B) - VOUTB.
 * @param[out] vtg : DAC output voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac15_get_dac_vout ( dac15_t *ctx, uint8_t dac_sel, float *vtg );

#ifdef __cplusplus
}
#endif
#endif // DAC15_H

/*! @} */ // dac15

// ------------------------------------------------------------------------ END
