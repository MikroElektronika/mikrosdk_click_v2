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
 * @file adc25.h
 * @brief This file contains API for ADC 25 Click Driver.
 */

#ifndef ADC25_H
#define ADC25_H

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

/*!
 * @addtogroup adc25 ADC 25 Click Driver
 * @brief API for configuring and manipulating ADC 25 Click driver.
 * @{
 */

/**
 * @defgroup adc25_reg ADC 25 Registers List
 * @brief List of registers of ADC 25 Click driver.
 */

/**
 * @addtogroup adc25_reg
 * @{
 */

/**
 * @brief ADC 25 description map.
 * @details Specified register map of ADC 25 Click driver.
 */
#define ADC25_REG_DEVICE_ID                 0x00
#define ADC25_REG_REVISION_ID               0x01
#define ADC25_REG_STATUS_MSB                0x02
#define ADC25_REG_STATUS_LSB                0x03
#define ADC25_REG_ADC_REF_STATUS            0x04
#define ADC25_REG_DIGITAL_STATUS            0x05
#define ADC25_REG_GPIO_DATA_INPUT           0x07
#define ADC25_REG_FIFO_SEQ_STATUS           0x08
#define ADC25_REG_FIFO_DEPTH_MSB            0x09
#define ADC25_REG_FIFO_DEPTH_LSB            0x0A
#define ADC25_REG_CONVERSION_CTRL           0x10
#define ADC25_REG_RESET                     0x11
#define ADC25_REG_ADC_CFG                   0x12
#define ADC25_REG_REFERENCE_CFG             0x13
#define ADC25_REG_CLK_DIGITAL_CFG           0x14
#define ADC25_REG_GPIO_CFG                  0x17
#define ADC25_REG_SEQUENCER_CFG             0x20
#define ADC25_REG_SEQUENCE_STEP_EN_0        0x21
#define ADC25_REG_SEQUENCE_STEP_EN_1        0x22
#define ADC25_REG_SEQUENCE_STEP_EN_2        0x23
#define ADC25_REG_SEQUENCE_STEP_EN_3        0x24
#define ADC25_REG_FIFO_CFG                  0x25
#define ADC25_REG_DIAG_MONITOR_CFG          0x2A
#define ADC25_REG_PAGE_POINTER              0x3F
#define ADC25_REG_STEPX_AIN_CFG             0x00
#define ADC25_REG_STEPX_ADC_REF_CFG         0x02
#define ADC25_REG_STEPX_FLTR1_CFG           0x03
#define ADC25_REG_STEPX_DELAY_MSB_CFG       0x04
#define ADC25_REG_STEPX_DELAY_LSB_CFG       0x05
#define ADC25_REG_STEPX_OFFSET_CAL_MSB      0x06
#define ADC25_REG_STEPX_OFFSET_CAL_ISB      0x07
#define ADC25_REG_STEPX_OFFSET_CAL_LSB      0x08
#define ADC25_REG_STEPX_GAIN_CAL_MSB        0x09
#define ADC25_REG_STEPX_GAIN_CAL_LSB        0x0A
#define ADC25_REG_STEPX_OW_SYSMON_CFG       0x0B
#define ADC25_REG_STEPX_PAGE_POINTER        0x3F

/*! @} */ // adc25_reg

/**
 * @defgroup adc25_set ADC 25 Registers Settings
 * @brief Settings for registers of ADC 25 Click driver.
 */

/**
 * @addtogroup adc25_set
 * @{
 */

/**
 * @brief ADC 25 SPI command setting.
 * @details Specified setting for SPI command of ADC 25 Click driver.
 */
#define ADC25_CMD_READ_DATA                 0x00
#define ADC25_CMD_READ_REG                  0x40
#define ADC25_CMD_WRITE_REG                 0x80
#define ADC25_CMD_READ_FIFO                 0x0F

/**
 * @brief ADC 25 RESET register setting.
 * @details Specified setting for RESET register of ADC 25 Click driver.
 */
#define ADC25_RESET_SW_CODE                 0x5A

/**
 * @brief ADC 25 ADC_CFG register setting.
 * @details Specified setting for ADC_CFG register of ADC 25 Click driver.
 */
#define ADC25_ADC_CFG_SPEED_MODE_0          0x00
#define ADC25_ADC_CFG_SPEED_MODE_1          0x04
#define ADC25_ADC_CFG_SPEED_MODE_2          0x08
#define ADC25_ADC_CFG_SPEED_MODE_3          0x0C
#define ADC25_ADC_CFG_STBY_MODE_EN          0x02
#define ADC25_ADC_CFG_PWDN_EN               0x01

/**
 * @brief ADC 25 REFERENCE_CFG register setting.
 * @details Specified setting for REFERENCE_CFG register of ADC 25 Click driver.
 */
#define ADC25_REF_CFG_VREF_2_5V             0x00
#define ADC25_REF_CFG_VREF_4_096V           0x02
#define ADC25_REF_CFG_REFP_BUF_EN           0x01
#define ADC25_REF_CFG_REFP_BUF_DIS          0x00

/**
 * @brief ADC 25 GPIO_CFG register setting.
 * @details Specified setting for GPIO_CFG register of ADC 25 Click driver.
 */
#define ADC25_GPIO_CFG_GPIO1_DRDY           0x0C
#define ADC25_GPIO_CFG_GPIO3_FAULT          0xC0
#define ADC25_GPIO_CFG_GPIO0_START          0x03

/**
 * @brief ADC 25 SEQUENCER_CFG register setting.
 * @details Specified setting for SEQUENCER_CFG register of ADC 25 Click driver.
 */
#define ADC25_SEQ_CFG_MODE_SINGLE_SHOT      0x00
#define ADC25_SEQ_CFG_MODE_CONT_SINGLE      0x40
#define ADC25_SEQ_CFG_MODE_SINGLE_SEQ       0x80
#define ADC25_SEQ_CFG_MODE_CONT_SEQ         0xC0
#define ADC25_SEQ_CFG_DRDY_PER_CONV         0x00
#define ADC25_SEQ_CFG_DRDY_PER_STEP         0x01
#define ADC25_SEQ_CFG_DRDY_PER_SEQ          0x02
#define ADC25_SEQ_CFG_DRDY_FIFO_THRES       0x03

/**
 * @brief ADC 25 CONVERSION_CTRL register setting.
 * @details Specified setting for CONVERSION_CTRL register of ADC 25 Click driver.
 */
#define ADC25_CONV_CTRL_START               0x80
#define ADC25_CONV_CTRL_STOP                0x01

/**
 * @brief ADC 25 SEQUENCE_STEP_EN_0 register setting.
 * @details Specified setting for SEQUENCE_STEP_EN_0 register of ADC 25 Click driver.
 */
#define ADC25_SEQ_STEP_0_EN                 0x01
#define ADC25_SEQ_STEP_0_TO_7_EN            0xFF

/**
 * @brief ADC 25 PAGE_POINTER register setting.
 * @details Specified setting for PAGE_POINTER register of ADC 25 Click driver.
 */
#define ADC25_PAGE_GENERAL_CFG              0x00
#define ADC25_PAGE_STEP_0                   0x01

/**
 * @brief ADC 25 STEPx_AIN_CFG register setting.
 * @details Specified setting for STEPx_AIN_CFG register of ADC 25 Click driver.
 */
#define ADC25_AIN_CFG_AIN0_SE               0x00
#define ADC25_AIN_CFG_AIN1_SE               0x01
#define ADC25_AIN_CFG_AIN2_SE               0x02
#define ADC25_AIN_CFG_AIN3_SE               0x03
#define ADC25_AIN_CFG_AIN4_SE               0x04
#define ADC25_AIN_CFG_AIN5_SE               0x05
#define ADC25_AIN_CFG_AIN6_SE               0x06
#define ADC25_AIN_CFG_AIN7_SE               0x07
#define ADC25_AIN_CFG_AIN8_SE               0x08
#define ADC25_AIN_CFG_AIN9_SE               0x09
#define ADC25_AIN_CFG_AIN10_SE              0x0A
#define ADC25_AIN_CFG_AIN11_SE              0x0B
#define ADC25_AIN_CFG_AIN12_SE              0x0C
#define ADC25_AIN_CFG_AIN13_SE              0x0D
#define ADC25_AIN_CFG_AIN14_SE              0x0E
#define ADC25_AIN_CFG_AIN15_SE              0x0F
#define ADC25_AIN_CFG_AIN0_AIN1_DIFF        0x10
#define ADC25_AIN_CFG_AIN2_AIN3_DIFF        0x11
#define ADC25_AIN_CFG_AIN4_AIN5_DIFF        0x12
#define ADC25_AIN_CFG_AIN6_AIN7_DIFF        0x13
#define ADC25_AIN_CFG_AIN8_AIN9_DIFF        0x14
#define ADC25_AIN_CFG_AIN10_AIN11_DIFF      0x15
#define ADC25_AIN_CFG_AIN12_AIN13_DIFF      0x16
#define ADC25_AIN_CFG_AIN14_AIN15_DIFF      0x17

/**
 * @brief ADC 25 STEPx_ADC_REF_CFG register setting.
 * @details Specified setting for STEPx_ADC_REF_CFG register of ADC 25 Click driver.
 */
#define ADC25_ADC_REF_CFG_GAIN_1            0x00
#define ADC25_ADC_REF_CFG_GAIN_2            0x40
#define ADC25_ADC_REF_CFG_GAIN_4            0x80
#define ADC25_ADC_REF_CFG_GAIN_8            0xC0
#define ADC25_ADC_REF_CFG_CODING_BIPOLAR    0x00
#define ADC25_ADC_REF_CFG_CODING_UNIPOLAR   0x20
#define ADC25_ADC_REF_CFG_REF_EXT           0x00
#define ADC25_ADC_REF_CFG_REF_INT           0x10
#define ADC25_ADC_REF_CFG_NUM_CONV_1        0x00

/**
 * @brief ADC 25 STEPx_FLTR1_CFG register setting.
 * @details Specified setting for STEPx_FLTR1_CFG register of ADC 25 Click driver.
 */
#define ADC25_FLTR_CFG_SINC4                0x00
#define ADC25_FLTR_CFG_SINC3                0x20
#define ADC25_FLTR_CFG_OSR_16               0x01
#define ADC25_FLTR_CFG_OSR_32               0x03
#define ADC25_FLTR_CFG_OSR_64               0x04
#define ADC25_FLTR_CFG_OSR_128              0x05
#define ADC25_FLTR_CFG_OSR_256              0x06
#define ADC25_FLTR_CFG_OSR_512              0x07
#define ADC25_FLTR_CFG_OSR_1024             0x08
#define ADC25_FLTR_CFG_OSR_2048             0x09

/**
 * @brief ADC 25 DEVICE_ID register setting.
 * @details Specified setting for DEVICE_ID register of ADC 25 Click driver.
 */
#define ADC25_DEVICE_ID_INVALID             0x00

/**
 * @brief ADC 25 sequencer setting.
 * @details Specified setting for sequencer of ADC 25 Click driver.
 */
#define ADC25_NUM_SEQ_STEPS                 8

/**
 * @brief ADC 25 sign extend setting.
 * @details Specified setting for sign extend of ADC 25 Click driver.
 */
#define ADC25_BIT_23_MASK                   0x00800000
#define ADC25_ONES_EXTEND_MASK              0xFF000000
#define ADC25_ZERO_EXTEND_MASK              0x00FFFFFF

/**
 * @brief ADC 25 FIFO_CFG register setting.
 * @details Specified setting for FIFO_CFG register of ADC 25 Click driver.
 */
#define ADC25_FIFO_CFG_FIFO_EN              0x01

/**
 * @brief ADC 25 voltage and current calculation constants setting.
 * @details Specified setting for voltage and current calculation constants of ADC 25 Click driver.
 */
#define ADC25_VREF_INTERNAL_V               2.5f
#define ADC25_ATTENUATION_FACTOR            10.0f
#define ADC25_FULL_SCALE                    8388608.0f
#define ADC25_SHUNT_RES_OHM                 249.0f
#define ADC25_CONV_MILI                     1000.0f

/**
 * @brief ADC 25 timeout in milliseconds setting.
 * @details Specified setting for timeout in milliseconds of ADC 25 Click driver.
 */
#define ADC25_TIMEOUT_MS                    1000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc25_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC25_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ADC25_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc25_set

/**
 * @defgroup adc25_map ADC 25 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 25 Click driver.
 */

/**
 * @addtogroup adc25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 25 Click to the selected MikroBUS.
 */
#define ADC25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.st   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc25_map
/*! @} */ // adc25

/**
 * @brief ADC 25 Click context object.
 * @details Context object definition of ADC 25 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                              /**< Reset pin(active low). */
    digital_out_t st;                               /**< Conversion start pin. */

    // Input pins
    digital_in_t rdy;                               /**< Data ready pin(active low). */

    // Modules
    spi_master_t spi;                               /**< SPI driver object. */

    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */

} adc25_t;

/**
 * @brief ADC 25 Click configuration object.
 * @details Configuration object definition of ADC 25 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                                 /**< Reset pin descriptor. */
    pin_name_t st;                                  /**< Conversion start pin descriptor. */
    pin_name_t rdy;                                 /**< Data ready pin descriptor. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adc25_cfg_t;

/**
 * @brief ADC 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC25_OK = 0,
    ADC25_ERROR = -1

} adc25_return_value_t;

/*!
 * @addtogroup adc25 ADC 25 Click Driver
 * @brief API for configuring and manipulating ADC 25 Click driver.
 * @{
 */

/**
 * @brief ADC 25 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc25_cfg_setup ( adc25_cfg_t *cfg );

/**
 * @brief ADC 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc25_init ( adc25_t *ctx, adc25_cfg_t *cfg );

/**
 * @brief ADC 25 default configuration function.
 * @details This function executes a default configuration of ADC 25
 * Click board.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc25_default_cfg ( adc25_t *ctx );

/**
 * @brief ADC 25 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc25_write_reg ( adc25_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ADC 25 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc25_read_reg ( adc25_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ADC 25 hardware reset function.
 * @details This function performs a hardware reset of the device by toggling
 * the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void adc25_hw_reset ( adc25_t *ctx );

/**
 * @brief ADC 25 software reset function.
 * @details This function performs a software reset by writing the reset code
 * (0x5A) to the RESET register.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc25_sw_reset ( adc25_t *ctx );

/**
 * @brief ADC 25 start conversion function.
 * @details This function starts ADC conversions by setting the START bit
 * in the CONVERSION_CTRL register.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc25_start_conversion ( adc25_t *ctx );

/**
 * @brief ADC 25 stop conversion function.
 * @details This function stops ADC conversions by setting the STOP bit
 * in the CONVERSION_CTRL register.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc25_stop_conversion ( adc25_t *ctx );

/**
 * @brief ADC 25 read raw data function.
 * @details This function reads the latest 24-bit raw conversion result from
 * the device.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @param[out] raw_data : Pointer to the 24-bit signed output value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc25_read_raw_data ( adc25_t *ctx, int32_t *raw_data );

/**
 * @brief ADC 25 get voltage sequence function.
 * @details This function waits for the sequencer to complete a full sequence,
 * then reads conversion results and converts each to a voltage.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @param[out] voltage : Pointer to the output voltage array in Volts.
 * @param[in] len : Number of conversion results to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc25_get_voltage_seq ( adc25_t *ctx, float *voltage, uint8_t len );

/**
 * @brief ADC 25 get data ready function.
 * @details This function reads the logic state of the DRDY pin.
 * @param[in] ctx : Click context object.
 * See #adc25_t object definition for detailed explanation.
 * @return DRDY pin logic state.
 * @note None.
 */
uint8_t adc25_get_data_ready ( adc25_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ADC25_H

/*! @} */ // adc25

// ------------------------------------------------------------------------ END
