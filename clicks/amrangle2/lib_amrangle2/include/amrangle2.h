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
 * @file amrangle2.h
 * @brief This file contains API for AMR Angle 2 Click Driver.
 */

#ifndef AMRANGLE2_H
#define AMRANGLE2_H

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
 * @addtogroup amrangle2 AMR Angle 2 Click Driver
 * @brief API for configuring and manipulating AMR Angle 2 Click driver.
 * @{
 */

/**
 * @defgroup amrangle2_reg AMR Angle 2 Registers List
 * @brief List of registers of AMR Angle 2 Click driver.
 */

/**
 * @addtogroup amrangle2_reg
 * @{
 */

/**
 * @brief AMR Angle 2 register list.
 * @details Specified register list of AMR Angle 2 Click driver.
 */
#define AMRANGLE2_REG_ADC_MODE_CONTROL          0x0000
#define AMRANGLE2_REG_ADC_CONFIGURATION         0x8000
#define AMRANGLE2_REG_UNIPOLAR                  0x8800
#define AMRANGLE2_REG_BIPOLAR                   0x9000
#define AMRANGLE2_REG_RANGE                     0x9800
#define AMRANGLE2_REG_CUSTOM_SCAN0              0xA000
#define AMRANGLE2_REG_CUSTOM_SCAN1              0xA800
#define AMRANGLE2_REG_SAMPLE_SET                0xB000

/*! @} */ // amrangle2_reg

/**
 * @defgroup amrangle2_set AMR Angle 2 Registers Settings
 * @brief Settings for registers of AMR Angle 2 Click driver.
 */

/**
 * @addtogroup amrangle2_set
 * @{
 */

/**
 * @brief AMR Angle 2 adc mode register settings.
 * @details Specified adc mode register settings of AMR Angle 2 Click driver.
 */
#define AMRANGLE2_SCAN_UNCHANGED                0x0000
#define AMRANGLE2_SCAN_MANUAL                   0x0800
#define AMRANGLE2_SCAN_REPEAT                   0x1000
#define AMRANGLE2_SCAN_STANDARD_INT             0x1800
#define AMRANGLE2_SCAN_STANDARD_EXT             0x2000
#define AMRANGLE2_SCAN_UPPER_INT                0x2800
#define AMRANGLE2_SCAN_UPPER_EXT                0x3000
#define AMRANGLE2_SCAN_CUSTOM_INT               0x3800
#define AMRANGLE2_SCAN_CUSTOM_EXT               0x4000
#define AMRANGLE2_SCAN_SAMPLE_SET               0x4800
#define AMRANGLE2_CHSEL_AIN0                    0x0000
#define AMRANGLE2_CHSEL_AIN1                    0x0080
#define AMRANGLE2_CHSEL_AIN2                    0x0100
#define AMRANGLE2_CHSEL_AIN3                    0x0180
#define AMRANGLE2_RESET_FIFO                    0x0020
#define AMRANGLE2_RESET_ALL                     0x0040
#define AMRANGLE2_PM_NORMAL                     0x0000
#define AMRANGLE2_PM_AUTO_SHUTDOWN              0x0008
#define AMRANGLE2_PM_AUTO_STANDBY               0x0010
#define AMRANGLE2_CHAN_ID_ENABLE                0x0004
#define AMRANGLE2_SWCNV_START                   0x0002

/**
 * @brief AMR Angle 2 adc configuration register settings.
 * @details Specified adc configuration register settings of AMR Angle 2 Click driver.
 */
#define AMRANGLE2_REFSEL_EXT_DIFFERENTIAL       0x0400
#define AMRANGLE2_AVGON                         0x0200
#define AMRANGLE2_NAVG_4                        0x0000
#define AMRANGLE2_NAVG_8                        0x0080
#define AMRANGLE2_NAVG_16                       0x0100
#define AMRANGLE2_NAVG_32                       0x0180
#define AMRANGLE2_NSCAN_4                       0x0000
#define AMRANGLE2_NSCAN_8                       0x0020
#define AMRANGLE2_NSCAN_12                      0x0040
#define AMRANGLE2_NSCAN_16                      0x0060
#define AMRANGLE2_SPM_NORMAL                    0x0000
#define AMRANGLE2_SPM_FULL_SHUTDOWN             0x0008
#define AMRANGLE2_SPM_PARTIAL_SHUTDOWN          0x0010
#define AMRANGLE2_ECHO_ON                       0x0004

/**
 * @brief AMR Angle 2 range register settings.
 * @details Specified range register settings of AMR Angle 2 Click driver.
 */
#define AMRANGLE2_RANGE01_HALF_VREF             0x0000
#define AMRANGLE2_RANGE01_FULL_VREF             0x0400
#define AMRANGLE2_RANGE23_HALF_VREF             0x0000
#define AMRANGLE2_RANGE23_FULL_VREF             0x0200

/**
 * @brief AMR Angle 2 bipolar register settings.
 * @details Specified bipolar register settings of AMR Angle 2 Click driver.
 */
#define AMRANGLE2_BCH01_UNIPOLAR                0x0000
#define AMRANGLE2_BCH01_BIPOLAR_FULLY_DIFF      0x0400
#define AMRANGLE2_BCH23_UNIPOLAR                0x0000
#define AMRANGLE2_BCH23_BIPOLAR_FULLY_DIFF      0x0200

/**
 * @brief AMR Angle 2 Vsin and Vcos calculation values.
 * @details Specified Vsin and Vcos calculation values of AMR Angle 2 Click driver.
 */
#define AMRANGLE2_ADC_VREF                      3.3
#define AMRANGLE2_ADC_RESOLUTION                0x0FFF

/**
 * @brief AMR Angle 2 angle calculation values.
 * @details Specified angle calculation values of AMR Angle 2 Click driver.
 */
#define AMRANGLE2_RADIANS_TO_DEGREES            57.295779513
#define AMRANGLE2_ANGLE_ZERO_OFFSET             90.0

/**
 * @brief AMR Angle 2 temperature calculation values.
 * @details Specified temperature calculation values of AMR Angle 2 Click driver.
 */
#define AMRANGLE2_TEMP_VDD                      3.3
#define AMRANGLE2_TEMP_TCAL                     25.0
#define AMRANGLE2_TEMP_TCO                      0.003173
#define AMRANGLE2_TEMP_NUM_CONVERSIONS          100

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b amrangle2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define AMRANGLE2_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define AMRANGLE2_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // amrangle2_set

/**
 * @defgroup amrangle2_map AMR Angle 2 MikroBUS Map
 * @brief MikroBUS pin mapping of AMR Angle 2 Click driver.
 */

/**
 * @addtogroup amrangle2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AMR Angle 2 Click to the selected MikroBUS.
 */
#define AMRANGLE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.cst  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.eoc  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // amrangle2_map
/*! @} */ // amrangle2

/**
 * @brief AMR Angle 2 Click context object.
 * @details Context object definition of AMR Angle 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cst;          /**< Active-Low Conversion Start pin. */

    // Input pins
    digital_in_t  eoc;          /**< End of Conversion pin. Data is valid after EOC pulls low. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */
    analog_in_t   adc;          /**< ADC module object. */

    pin_name_t    chip_select;  /**< Chip select pin descriptor (used for SPI driver). */
    float         vcal;         /**< Vcal for AMRANGLE2_TEMP_TCAL, calculate using amrangle2_calibrate_temperature function. */

} amrangle2_t;

/**
 * @brief AMR Angle 2 Click configuration object.
 * @details Configuration object definition of AMR Angle 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t an;              /**< Analog pin descriptor. */

    // Additional gpio pins
    pin_name_t cst;             /**< Active-Low Conversion Start pin. */
    pin_name_t eoc;             /**< End of Conversion pin. Data is valid after EOC pulls low. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */
    
    analog_in_resolution_t  resolution;                 /**< ADC resolution. */
    float                   vref;                       /**< ADC reference voltage. */

} amrangle2_cfg_t;

/**
 * @brief AMR Angle 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMRANGLE2_OK = 0,
    AMRANGLE2_ERROR = -1

} amrangle2_return_value_t;

/*!
 * @addtogroup amrangle2 AMR Angle 2 Click Driver
 * @brief API for configuring and manipulating AMR Angle 2 Click driver.
 * @{
 */

/**
 * @brief AMR Angle 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #amrangle2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void amrangle2_cfg_setup ( amrangle2_cfg_t *cfg );

/**
 * @brief AMR Angle 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #amrangle2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amrangle2_init ( amrangle2_t *ctx, amrangle2_cfg_t *cfg );

/**
 * @brief AMR Angle 2 default configuration function.
 * @details This function executes a default configuration of AMR Angle 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t amrangle2_default_cfg ( amrangle2_t *ctx );

/**
 * @brief AMR Angle 2 spi transfer function.
 * @details This function writes and reads a word of data simultaneously
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c >=0 - 16-bit data read,
 *         @li @c  -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amrangle2_spi_transfer ( amrangle2_t *ctx, uint16_t data_in );

/**
 * @brief AMR Angle 2 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amrangle2_read_an_pin_value ( amrangle2_t *ctx, uint16_t *data_out );

/**
 * @brief AMR Angle 2 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t amrangle2_read_an_pin_voltage ( amrangle2_t *ctx, float *data_out );

/**
 * @brief AMR Angle 2 calibrate temperature function.
 * @details This function calibrates the temperature readings (@b ctx->vcal) to the known room 
 * temperature in Celsius (@b AMRANGLE2_TEMP_TCAL).
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Adjust the value of macro @b AMRANGLE2_TEMP_TCAL to the known room temperature for correct calibration.
 */
err_t amrangle2_calibrate_temperature ( amrangle2_t *ctx );

/**
 * @brief AMR Angle 2 read temperature function.
 * @details This function reads a temperature measurements in Celsius.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amrangle2_read_temperature ( amrangle2_t *ctx, float *temperature );

/**
 * @brief AMR Angle 2 read vsin vcos function.
 * @details This function reads a voltage of sine and cosine differential signal outputs.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @param[out] vsin : Sine voltage.
 * @param[out] vcos : Cosine voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amrangle2_read_vsin_vcos ( amrangle2_t *ctx, float *vsin, float *vcos );

/**
 * @brief AMR Angle 2 read angle function.
 * @details This function reads a Vsin and Vcos voltages and converts them to angle in Degrees.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @param[out] angle : Angular position in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t amrangle2_read_angle ( amrangle2_t *ctx, float *angle );

/**
 * @brief AMR Angle 2 set cst pin function.
 * @details This function sets the conversion start (CST) pin logic state.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void amrangle2_set_cst_pin ( amrangle2_t *ctx, uint8_t state );

/**
 * @brief AMR Angle 2 get eoc pin function.
 * @details This function returns the conversion end (EOC) pin logic state.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t amrangle2_get_eoc_pin ( amrangle2_t *ctx );

/**
 * @brief AMR Angle 2 start conversion function.
 * @details This function starts the conversion and waits for the end of conversion indication.
 * @param[in] ctx : Click context object.
 * See #amrangle2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void amrangle2_start_conversion ( amrangle2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // AMRANGLE2_H

/*! @} */ // amrangle2

// ------------------------------------------------------------------------ END
