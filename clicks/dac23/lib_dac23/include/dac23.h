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
 * @file dac23.h
 * @brief This file contains API for DAC 23 Click Driver.
 */

#ifndef DAC23_H
#define DAC23_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup dac23 DAC 23 Click Driver
 * @brief API for configuring and manipulating DAC 23 Click driver.
 * @{
 */

/**
 * @defgroup dac23_reg DAC 23 Registers List
 * @brief List of registers of DAC 23 Click driver.
 */

/**
 * @addtogroup dac23_reg
 * @{
 */

/**
 * @brief DAC 23 register map.
 * @details Specified register map of DAC 23 Click driver.
 */
#define DAC23_REG_INTERFACE_CONFIG_A            0x00
#define DAC23_REG_INTERFACE_CONFIG_B            0x01
#define DAC23_REG_DEVICE_CONFIG                 0x02
#define DAC23_REG_CHIP_TYPE                     0x03
#define DAC23_REG_PRODUCT_ID_L                  0x04
#define DAC23_REG_PRODUCT_ID_H                  0x05
#define DAC23_REG_CHIP_GRADE                    0x06
#define DAC23_REG_SCRATCH_PAD                   0x0A
#define DAC23_REG_SPI_REVISION                  0x0B
#define DAC23_REG_VENDOR_ID_L                   0x0C
#define DAC23_REG_VENDOR_ID_H                   0x0D
#define DAC23_REG_STREAM_MODE                   0x0E
#define DAC23_REG_TRANSFER_CONFIG               0x0F
#define DAC23_REG_INTERFACE_CONFIG_C            0x10
#define DAC23_REG_INTERFACE_STATUS_A            0x11
#define DAC23_REG_OUTPUT_OPERATING_MODE_0       0x20
#define DAC23_REG_OUTPUT_CONTROL_0              0x2A
#define DAC23_REG_REFERENCE_CONTROL_0           0x3C
#define DAC23_REG_MUX_OUT_SELECT_0              0x93
#define DAC23_REG_STATUS_CONTROL                0xC2
#define DAC23_REG_HW_LDAC_EN_0                  0xD0
#define DAC23_REG_SW_LDAC_EN_0                  0xD1
#define DAC23_REG_DAC_CH0                       0xD3
#define DAC23_REG_DAC_CH1                       0xD5
#define DAC23_REG_DAC_CH2                       0xD7
#define DAC23_REG_DAC_CH3                       0xD9
#define DAC23_REG_MULTI_DAC_CH                  0xDB
#define DAC23_REG_MULTI_DAC_SEL_0               0xDC
#define DAC23_REG_SW_LDAC_TRIG_0                0xDD
#define DAC23_REG_MULTI_INPUT_CH                0xDF
#define DAC23_REG_MULTI_INPUT_SEL_0             0xE0
#define DAC23_REG_INPUT_SW_LDAC_TRIG_0          0xE1
#define DAC23_REG_INPUT_CH0                     0xE3
#define DAC23_REG_INPUT_CH1                     0xE5
#define DAC23_REG_INPUT_CH2                     0xE7
#define DAC23_REG_INPUT_CH3                     0xE9

/*! @} */ // dac23_reg

/**
 * @defgroup dac23_set DAC 23 Registers Settings
 * @brief Settings for registers of DAC 23 Click driver.
 */

/**
 * @addtogroup dac23_set
 * @{
 */

/**
 * @brief DAC 23 SPI read/write bit setting.
 * @details Specified setting for SPI read/write bit of DAC 23 Click driver.
 */
#define DAC23_SPI_READ_BIT                      0x80

/**
 * @brief DAC 23 ID setting.
 * @details Specified setting for ID of DAC 23 Click driver.
 */
#define DAC23_PRODUCT_ID                        0x0001
#define DAC23_VENDOR_ID                         0x0456

/**
 * @brief DAC 23 REFERENCE_CONTROL_0 register setting.
 * @details Specified setting for REFERENCE_CONTROL_0 register of DAC 23 Click driver.
 */
#define DAC23_REFERENCE_CONTROL_0_SEL_EXT_IN    0x00
#define DAC23_REFERENCE_CONTROL_0_SEL_INT_OUT   0x01
#define DAC23_REFERENCE_CONTROL_0_SEL_MASK      0x01

/**
 * @brief DAC 23 out range select setting.
 * @details Specified setting for out range select of DAC 23 Click driver.
 */
#define DAC23_OUT_RANGE_0_TO_2_5V               0x00
#define DAC23_OUT_RANGE_0_TO_5V                 0x01

/**
 * @brief DAC 23 voltage output setting.
 * @details Specified setting for voltage output of DAC 23 Click driver.
 */
#define DAC23_VZS_OUT_RANGE_0_TO_2_5V           0.0
#define DAC23_VFS_OUT_RANGE_0_TO_2_5V           2.5
#define DAC23_VZS_OUT_RANGE_0_TO_5V             0.0
#define DAC23_VFS_OUT_RANGE_0_TO_5V             5.0
#define DAC23_DAC_RES_16BIT                     0xFFFF

/**
 * @brief DAC 23 output channel selection.
 * @details DAC output channel selection of DAC 23 Click driver.
 */
#define DAC23_CHANNEL_0                         0
#define DAC23_CHANNEL_1                         1
#define DAC23_CHANNEL_2                         2
#define DAC23_CHANNEL_3                         3
#define DAC23_CHANNEL_ALL                       4

/**
 * @brief DAC 23 output operating mode settings.
 * @details Output operating mode settings of DAC 23 Click driver.
 */
#define DAC23_OUT_OP_MODE_NORMAL_OP             0
#define DAC23_OUT_OP_MODE_POWERED_DOWN_0_5K     1
#define DAC23_OUT_OP_MODE_POWERED_DOWN_3_85K    2
#define DAC23_OUT_OP_MODE_POWERED_DOWN_16K      3
#define DAC23_OUT_OP_MODE_MASK                  0x03

/**
 * @brief DAC 23 multiplexer input select settings.
 * @details Multiplexer input select settings of DAC 23 Click driver.
 */
#define DAC23_MUX_SEL_POWERED_DOWN              0x00
#define DAC23_MUX_SEL_VOUT0                     0x01
#define DAC23_MUX_SEL_IOUT0_SOURCE              0x02
#define DAC23_MUX_SEL_IOUT0_SINK                0x03
#define DAC23_MUX_SEL_VOUT1                     0x07
#define DAC23_MUX_SEL_IOUT1_SOURCE              0x08
#define DAC23_MUX_SEL_IOUT1_SINK                0x09
#define DAC23_MUX_SEL_VOUT2                     0x0D
#define DAC23_MUX_SEL_IOUT2_SOURCE              0x0E
#define DAC23_MUX_SEL_IOUT2_SINK                0x0F
#define DAC23_MUX_SEL_VOUT3                     0x13
#define DAC23_MUX_SEL_IOUT3_SOURCE              0x14
#define DAC23_MUX_SEL_IOUT3_SINK                0x15
#define DAC23_MUX_SEL_DIE_TEMPERATURE           0x19
#define DAC23_MUX_SEL_AGND                      0x1A
#define DAC23_MUX_SEL_MASK                      0x1F
#define DAC23_MUX_CURRENT_RESOLUTION_MA         80.0

/**
 * @brief DAC 23 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of DAC 23 Click driver.
 */
#define DAC23_NUM_CONVERSIONS                   100

/**
 * @brief DAC 23 ADC setting.
 * @details Specified settings for ADC of DAC 23 Click driver.
 */
#define DAC23_ADC_RESOLUTION                    0x0FFF
#define DAC23_ADC_VREF_3V3                      3.3
#define DAC23_ADC_VREF_5V                       5.0
#define DAC23_ADC_VREF                          DAC23_ADC_VREF_3V3

/**
 * @brief DAC 23 timeout setting.
 * @details Specified settings for timeout of DAC 23 Click driver.
 */
#define DAC23_TIMEOUT_MS                        2000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac23_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC23_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define DAC23_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac23_set

/**
 * @defgroup dac23_map DAC 23 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 23 Click driver.
 */

/**
 * @addtogroup dac23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 23 Click to the selected MikroBUS.
 */
#define DAC23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.mux = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ldac = MIKROBUS( mikrobus, MIKROBUS_PWM ); \

/*! @} */ // dac23_map
/*! @} */ // dac23

/**
 * @brief DAC 23 Click context object.
 * @details Context object definition of DAC 23 Click driver.
 */
typedef struct
{
    digital_out_t rst;          /**< Reset pin (active low). */
    digital_out_t ldac;         /**< Load DAC pin (active low). */

    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    analog_in_t adc;            /**< ADC module object. */
    float vref;                 /**< ADC reference voltage. */
    
    float v_zero_scale;         /**< Zero scale voltage for output range. */
    float v_full_scale;         /**< Full scale voltage for output range. */

} dac23_t;

/**
 * @brief DAC 23 Click configuration object.
 * @details Configuration object definition of DAC 23 Click driver.
 */
typedef struct
{
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t mux;             /**< Analog pin descriptor. */

    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t ldac;            /**< Load DAC pin (active low). */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} dac23_cfg_t;

/**
 * @brief DAC 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC23_OK = 0,
    DAC23_ERROR = -1

} dac23_return_value_t;

/*!
 * @addtogroup dac23 DAC 23 Click Driver
 * @brief API for configuring and manipulating DAC 23 Click driver.
 * @{
 */

/**
 * @brief DAC 23 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac23_cfg_setup ( dac23_cfg_t *cfg );

/**
 * @brief DAC 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_init ( dac23_t *ctx, dac23_cfg_t *cfg );

/**
 * @brief DAC 23 default configuration function.
 * @details This function executes a default configuration of DAC 23
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac23_default_cfg ( dac23_t *ctx );

/**
 * @brief DAC 23 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_write_reg ( dac23_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DAC 23 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_write_regs ( dac23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 23 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_read_reg ( dac23_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DAC 23 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_read_regs ( dac23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DAC 23 write register word function.
 * @details This function writes two bytes of data starting from the selected register in descending order.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Address ascension must be set to address descending in the INTERFACE_CONFIG_A register.
 */
err_t dac23_write_reg_word ( dac23_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 23 read register word function.
 * @details This function reads two bytes of data starting from the selected register in descending order.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Address ascension must be set to address descending in the INTERFACE_CONFIG_A register.
 */
err_t dac23_read_reg_word ( dac23_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 23 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_read_raw_adc ( dac23_t *ctx, uint16_t *raw_adc );

/**
 * @brief DAC 23 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t dac23_read_voltage ( dac23_t *ctx, float *voltage );

/**
 * @brief DAC 23 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t dac23_read_voltage_avg ( dac23_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief DAC 23 set vref function.
 * @details This function sets the voltage reference for DAC 23 Click driver.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b dac23_init is defined in DAC23_ADC_VREF.
 */
err_t dac23_set_vref ( dac23_t *ctx, float vref );

/**
 * @brief DAC 23 set LDAC pin function.
 * @details This function sets the LDAC pin logic state.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dac23_set_ldac_pin ( dac23_t *ctx, uint8_t state );

/**
 * @brief DAC 23 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dac23_set_rst_pin ( dac23_t *ctx, uint8_t state );

/**
 * @brief DAC 23 reset device function.
 * @details This function resets the device by toggling the reset pin.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dac23_reset_device ( dac23_t *ctx );

/**
 * @brief DAC 23 check communication function.
 * @details This function checks the communication by reading and verifying
 * the product and vendor IDs.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_check_com ( dac23_t *ctx );

/**
 * @brief DAC 23 set output range function.
 * @details This function sets the output voltage range and as well as the @b ctx->v_zero_scale and
 * @b ctx->v_full_scale variables for the selected range.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] range : @li @c 0 - Range from 0V to VREF(2.5V).
 *                    @li @c 1 - Range from 0V to 2xVREF(5V).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_set_out_range ( dac23_t *ctx, uint8_t range );

/**
 * @brief DAC 23 set output operating mode function.
 * @details This function sets the output operating mode for selected channels.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] channel : DAC channels to be updated, see DAC23_CHANNEL_x macros.
 * @param[in] op_mode : Operating mode setting, see DAC23_OUT_OP_MODE_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_set_out_op_mode ( dac23_t *ctx, uint8_t channel, uint8_t op_mode );

/**
 * @brief DAC 23 set multiplexer select function.
 * @details This function sets the output multiplexer select for ADC reading.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] mux_sel : MUX channel select, see DAC23_MUX_SEL_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_set_mux_sel ( dac23_t *ctx, uint8_t mux_sel );

/**
 * @brief DAC 23 set dac value function.
 * @details This function writes the raw 16-bit DAC value to the selected channels.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] channel : DAC channels to be updated, see DAC23_CHANNEL_x macros.
 * @param[in] dac_value : 16-bit raw DAC value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_set_dac_value ( dac23_t *ctx, uint8_t channel, uint16_t dac_value );

/**
 * @brief DAC 23 set output voltage function.
 * @details This function sets the output voltage of one or more channels
 * by converting it to a corresponding DAC code and updating the device.
 * @param[in] ctx : Click context object.
 * See #dac23_t object definition for detailed explanation.
 * @param[in] channel : DAC channels to be updated, see DAC23_CHANNEL_x macros.
 * @param[in] voltage : Float value of voltage to be set.
 * The voltage range depends on the @b dac23_set_out_range setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac23_set_out_voltage ( dac23_t *ctx, uint8_t channel, float voltage );

#ifdef __cplusplus
}
#endif
#endif // DAC23_H

/*! @} */ // dac23

// ------------------------------------------------------------------------ END
