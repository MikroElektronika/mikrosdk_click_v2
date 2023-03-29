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
 * @file dac13.h
 * @brief This file contains API for DAC 13 Click Driver.
 */

#ifndef DAC13_H
#define DAC13_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup dac13 DAC 13 Click Driver
 * @brief API for configuring and manipulating DAC 13 Click driver.
 * @{
 */

/**
 * @defgroup dac13_reg DAC 13 Registers List
 * @brief List of registers of DAC 13 Click driver.
 */

/**
 * @addtogroup dac13_reg
 * @{
 */

/**
 * @brief DAC 13 register list.
 * @details Specified register list of DAC 13 Click driver.
 */
#define DAC13_REG_INTERFACE_CONFIG_A        0x00
#define DAC13_REG_INTERFACE_CONFIG_B        0x01
#define DAC13_REG_DEVICE_CONFIG             0x02
#define DAC13_REG_CHIP_TYPE                 0x03
#define DAC13_REG_PRODUCT_ID_L              0x04
#define DAC13_REG_PRODUCT_ID_H              0x05
#define DAC13_REG_CHIP_GRADE                0x06
#define DAC13_REG_SCRATCH_PAD               0x0A
#define DAC13_REG_SPI_REVISION              0x0B
#define DAC13_REG_VENDOR_L                  0x0C
#define DAC13_REG_VENDOR_H                  0x0D
#define DAC13_REG_STREAM_MODE               0x0E
#define DAC13_REG_TRANSFER_REGISTER         0x0F
#define DAC13_REG_INTERFACE_CONFIG_C        0x10
#define DAC13_REG_INTERFACE_STATUS_A        0x11
#define DAC13_REG_INTERFACE_CONFIG_D        0x14
#define DAC13_REG_REFERENCE_CONFIG          0x15
#define DAC13_REG_ERR_ALARM_MASK            0x16
#define DAC13_REG_ERR_STATUS                0x17
#define DAC13_REG_POWERDOWN_CONFIG          0x18
#define DAC13_REG_CH0_OUTPUT_RANGE          0x19
#define DAC13_REG_HW_LDAC_16B               0x28
#define DAC13_REG_CH0_DAC_16B               0x2A
#define DAC13_REG_DAC_PAGE_16B              0x2E
#define DAC13_REG_CH_SELECT_16B             0x2F
#define DAC13_REG_INPUT_PAGE_16B            0x31
#define DAC13_REG_SW_LDAC_16B               0x32
#define DAC13_REG_CH0_INPUT_16B             0x34
#define DAC13_REG_HW_LDAC_24B               0x37
#define DAC13_REG_CH0_DAC_24B               0x3A
#define DAC13_REG_DAC_PAGE_24B              0x40
#define DAC13_REG_CH_SELECT_24B             0x41
#define DAC13_REG_INPUT_PAGE_24B            0x44
#define DAC13_REG_SW_LDAC_24B               0x45
#define DAC13_REG_CH0_INPUT_24B             0x48

/*! @} */ // dac13_reg

/**
 * @defgroup dac13_set DAC 13 Registers Settings
 * @brief Settings for registers of DAC 13 Click driver.
 */

/**
 * @addtogroup dac13_set
 * @{
 */

/**
 * @brief DAC 13 SPI read/write bit setting.
 * @details Specified setting for SPI read/write bit of DAC 13 Click driver.
 */
#define DAC13_SPI_READ_BIT                  0x80

/**
 * @brief DAC 13 ID setting.
 * @details Specified setting for ID of DAC 13 Click driver.
 */
#define DAC13_PRODUCT_ID                    0x400B
#define DAC13_VENDOR_ID                     0x0456

/**
 * @brief DAC 13 REFERENCE_CONFIG register setting.
 * @details Specified setting for REFERENCE_CONFIG register of DAC 13 Click driver.
 */
#define DAC13_IDUMP_FASTMODE                0x40
#define DAC13_REFERENCE_VOLTAGE_SEL_INT     0x00
#define DAC13_REFERENCE_VOLTAGE_SEL_INT_OUT 0x01
#define DAC13_REFERENCE_VOLTAGE_SEL_EXT     0x02
#define DAC13_REFERENCE_VOLTAGE_SEL_MASK    0x03

/**
 * @brief DAC 13 out range select setting.
 * @details Specified setting for out range select of DAC 13 Click driver.
 */
#define DAC13_OUT_RANGE_0_TO_2p5V           0x00
#define DAC13_OUT_RANGE_0_TO_5V             0x01
#define DAC13_OUT_RANGE_0_TO_10V            0x02
#define DAC13_OUT_RANGE_NEG_5_TO_5V         0x03
#define DAC13_OUT_RANGE_NEG_2p5_TO_7p5V     0x04

/**
 * @brief DAC 13 voltage output setting.
 * @details Specified setting for voltage output of DAC 13 Click driver.
 */
#define DAC13_VZS_OUT_RANGE_0_TO_2p5V       ( -0.197f )
#define DAC13_VFS_OUT_RANGE_0_TO_2p5V       ( 2.701f )
#define DAC13_VZS_OUT_RANGE_0_TO_5V         ( -0.077f )
#define DAC13_VFS_OUT_RANGE_0_TO_5V         ( 5.077f )
#define DAC13_VZS_OUT_RANGE_0_TO_10V        ( -0.162f )
#define DAC13_VFS_OUT_RANGE_0_TO_10V        ( 10.164f )
#define DAC13_VZS_OUT_RANGE_NEG_5_TO_5V     ( -5.164f )
#define DAC13_VFS_OUT_RANGE_NEG_5_TO_5V     ( 5.162f )
#define DAC13_VZS_OUT_RANGE_NEG_2p5_TO_7p5V ( -2.663f )
#define DAC13_VFS_OUT_RANGE_NEG_2p5_TO_7p5V ( 7.663f )
#define DAC13_DAC_RES_16BIT                 0xFFFF

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac13_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC13_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define DAC13_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac13_set

/**
 * @defgroup dac13_map DAC 13 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 13 Click driver.
 */

/**
 * @addtogroup dac13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 13 Click to the selected MikroBUS.
 */
#define DAC13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ldc = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dac13_map
/*! @} */ // dac13

/**
 * @brief DAC 13 Click context object.
 * @details Context object definition of DAC 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ldc;              /**< Load DAC pin (Active LOW). */
    digital_out_t rst;              /**< Reset pin (Active LOW). */

    // Input pins
    digital_in_t alt;               /**< Alert pin (Active LOW). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    
    float        v_zero_scale;      /**< Zero scale voltage for output range. */
    float        v_full_scale;      /**< Full scale voltage for output range. */

} dac13_t;

/**
 * @brief DAC 13 Click configuration object.
 * @details Configuration object definition of DAC 13 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t ldc;                 /**< Load DAC pin (Active LOW). */
    pin_name_t rst;                 /**< Reset pin (Active LOW). */
    pin_name_t alt;                 /**< Alert pin (Active LOW). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} dac13_cfg_t;

/**
 * @brief DAC 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC13_OK = 0,
    DAC13_ERROR = -1

} dac13_return_value_t;

/*!
 * @addtogroup dac13 DAC 13 Click Driver
 * @brief API for configuring and manipulating DAC 13 Click driver.
 * @{
 */

/**
 * @brief DAC 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac13_cfg_setup ( dac13_cfg_t *cfg );

/**
 * @brief DAC 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_init ( dac13_t *ctx, dac13_cfg_t *cfg );

/**
 * @brief DAC 13 default configuration function.
 * @details This function executes a default configuration of DAC 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac13_default_cfg ( dac13_t *ctx );

/**
 * @brief DAC 13 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_generic_write ( dac13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 13 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_generic_read ( dac13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DAC 13 write register function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_write_register ( dac13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DAC 13 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_read_register ( dac13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DAC 13 write register 16b function.
 * @details This function writes two bytes of data starting from the selected register in descending order
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Address direction must be set to address descending in the INTERFACE_CONFIG_A register.
 */
err_t dac13_write_register_16b ( dac13_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 13 read register 16b function.
 * @details This function reads two bytes of data starting from the selected register in descending order
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Address direction must be set to address descending in the INTERFACE_CONFIG_A register.
 */
err_t dac13_read_register_16b ( dac13_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 13 set ldc pin function.
 * @details This function sets the LDC pin logic state.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dac13_set_ldc_pin ( dac13_t *ctx, uint8_t state );

/**
 * @brief DAC 13 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dac13_set_rst_pin ( dac13_t *ctx, uint8_t state );

/**
 * @brief DAC 13 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dac13_get_alert_pin ( dac13_t *ctx );

/**
 * @brief DAC 13 reset device function.
 * @details This function resets the device by toggling the reset pin.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dac13_reset_device ( dac13_t *ctx );

/**
 * @brief DAC 13 check communication function.
 * @details This function checks the communication by reading and verifying
 * the product and vendor IDs.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_check_communication ( dac13_t *ctx );

/**
 * @brief DAC 13 set output range function.
 * @details This function sets the output voltage range and as well as the @b ctx->v_zero_scale and
 * @b ctx->v_full_scale variables for the selected range.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] out_range : @li @c 0 - Range from 0V to 2.5V - Output gain jumper must be set to X1.
 *                        @li @c 1 - Range from 0V to 5V - Output gain jumper must be set to X1.
 *                        @li @c 2 - Range from 0V to 10V - Output gain jumper must be set to X2.
 *                        @li @c 3 - Range from -5V to 5V - Output gain jumper must be set to X2.
 *                        @li @c 4 - Range from -2.5V to 7.5V - Output gain jumper must be set to X2.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_set_output_range ( dac13_t *ctx, uint8_t out_range );

/**
 * @brief DAC 13 set dac value function.
 * @details This function sets the raw DAC value.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] dac_value : 16-bit raw DAC value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_set_dac_value ( dac13_t *ctx, uint16_t dac_value );

/**
 * @brief DAC 13 set output voltage function.
 * @details This function sets the DAC output voltage.
 * @param[in] ctx : Click context object.
 * See #dac13_t object definition for detailed explanation.
 * @param[in] voltage : Float value of voltage to be set.
 * The voltage range depends on the @b dac13_set_output_range setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac13_set_output_voltage ( dac13_t *ctx, float voltage );

#ifdef __cplusplus
}
#endif
#endif // DAC13_H

/*! @} */ // dac13

// ------------------------------------------------------------------------ END
