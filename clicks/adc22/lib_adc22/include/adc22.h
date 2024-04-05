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
 * @file adc22.h
 * @brief This file contains API for ADC 22 Click Driver.
 */

#ifndef ADC22_H
#define ADC22_H

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
 * @addtogroup adc22 ADC 22 Click Driver
 * @brief API for configuring and manipulating ADC 22 Click driver.
 * @{
 */

/**
 * @defgroup adc22_cmd ADC 22 commands List
 * @brief List of commands of ADC 22 Click driver.
 */

/**
 * @addtogroup adc22_cmd
 * @{
 */

/**
 * @brief ADC 22 description command.
 * @details Specified command for description of ADC 22 Click driver.
 */
#define ADC22_CMD_NOP                   0x00
#define ADC22_CMD_CLEAR_HWORD           0xC0
#define ADC22_CMD_READ_HWORD            0xC8
#define ADC22_CMD_READ                  0x48
#define ADC22_CMD_WRITE                 0xD0
#define ADC22_CMD_WRITE_MS              0xD2
#define ADC22_CMD_WRITE_LS              0xD4
#define ADC22_CMD_SET_HWORD             0xD8

/*! @} */ // adc22_cmd

/**
 * @defgroup adc22_reg ADC 22 Registers List
 * @brief List of registers of ADC 22 Click driver.
 */

/**
 * @addtogroup adc22_reg
 * @{
 */

/**
 * @brief ADC 22 description register.
 * @details Specified register for description of ADC 22 Click driver.
 */
#define ADC22_REG_DEVICE_ID             0x02
#define ADC22_REG_RST_PWRCTL_LSB        0x04
#define ADC22_REG_RST_PWRCTL_MSB        0x05
#define ADC22_REG_SDI_CTL               0x08
#define ADC22_REG_SDO_CTL_LSB           0x0C
#define ADC22_REG_SDO_CTL_MSB           0x0D
#define ADC22_REG_DATAOUT_CTL_LSB       0x10
#define ADC22_REG_DATAOUT_CTL_MSB       0x11
#define ADC22_REG_RANGE_SEL             0x14
#define ADC22_REG_ALARM_LSB             0x20
#define ADC22_REG_ALARM_MSB             0x21
#define ADC22_REG_ALARM_H_TH_LSB        0x24
#define ADC22_REG_ALARM_H_TH_MSB        0x25
#define ADC22_REG_ALARM_L_TH_LSB        0x28
#define ADC22_REG_ALARM_L_TH_MSB        0x29

/*! @} */ // adc22_reg

/**
 * @defgroup adc22_set ADC 22 Registers Settings
 * @brief Settings for registers of ADC 22 Click driver.
 */

/**
 * @addtogroup adc22_set
 * @{
 */

/**
 * @brief ADC 22 identification numbers associated to a device values.
 * @details Specified identification numbers associated to a device data values of ADC 22 Click driver.
 */
#define ADC22_DEVICE_ADDR_MAX           16

/**
 * @brief ADC 22 SDO mode data values.
 * @details Specified SDO mode data values of ADC 22 Click driver.
 */
#define ADC22_SDO_MODE_SAME_SDI         1
#define ADC22_SDO_MODE_INV              2
#define ADC22_SDO_MODE_ADC_M_CLK        3

/**
 * @brief ADC 22 controls the data output by the device data values.
 * @details Specified controls the data output by the device values of ADC 22 Click driver.
 */
#define ADC22_DATAOUT_CTL_VAL_CONV      0x00
#define ADC22_DATAOUT_CTL_VAL_0_S       0x04
#define ADC22_DATAOUT_CTL_VAL_1_S       0x05
#define ADC22_DATAOUT_CTL_VAL_A_01_S    0x06
#define ADC22_DATAOUT_CTL_VAL_A_0011_S  0x07
#define ADC22_DATAOUT_CTL_PAR_DIS       0x00
#define ADC22_DATAOUT_CTL_PAR_EN        0x08

/**
 * @brief ADC 22 ADC resolution data values.
 * @details Specified ADC resolution data values of ADC 22 Click driver.
 */
#define ADC22_ADC_ZERO_SCALE            2045u
#define ADC22_ADC_MIDDLE_SCALE          2048.0f
#define ADC22_ADC_FULL_SCALE            4096.0f

/**
 * @brief ADC 22 ADC range data values.
 * @details Specified ADC range data values of ADC 22 Click driver.
 */
#define ADC22_ADC_RANGE_12V28           12.28f
#define ADC22_ADC_RANGE_10V24           10.24f
#define ADC22_ADC_RANGE_6V14            6.14f
#define ADC22_ADC_RANGE_5V12            5.12f
#define ADC22_ADC_RANGE_2V56            2.56f
#define ADC22_SET_RANGE_BIT_MASK        0x0F

/**
 * @brief ADC 22 I/O pin state data values.
 * @details Specified I/O pin state data values of ADC 22 Click driver.
 */
#define ADC22_PIN_STATE_LOW             0x00
#define ADC22_PIN_STATE_HIGH            0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc22_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC22_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ADC22_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc22_set

/**
 * @defgroup adc22_map ADC 22 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 22 Click driver.
 */

/**
 * @addtogroup adc22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 22 Click to the selected MikroBUS.
 */
#define ADC22_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rvs = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc22_map
/*! @} */ // adc22

/**
 * @brief ADC 22 Click context object.
 * @details Context object definition of ADC 22 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;     /**< Reset pin. */

    // Input pins
    digital_in_t rvs;      /**< Reflects the status pin. */
    digital_in_t int_pin;  /**< Interrupt pin. */

    // Modules
    spi_master_t spi;      /**< SPI driver object. */

    pin_name_t   chip_select;  /**< Chip select pin descriptor (used for SPI driver). */

} adc22_t;

/**
 * @brief ADC 22 Click configuration object.
 * @details Configuration object definition of ADC 22 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rvs;      /**< Reflects the status pin. */
    pin_name_t rst;      /**< Reset pin. */
    pin_name_t int_pin;  /**< Interrupt pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adc22_cfg_t;

/**
 * @brief ADC 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC22_OK = 0,
    ADC22_ERROR = -1

} adc22_return_value_t;

/**
 * @brief ADC 22 Click ADC ranges selections.
 * @details Predefined enum values for driver ADC ranges selections.
 */
typedef enum
{
    ADC22_RANGE_BI_12V28 = 0x00,    /**< Input range = ±3×VREF     [–12.288:12.288]. */
    ADC22_RANGE_BI_10V24 = 0x01,    /**< Input range = ±2.5×VREF   [–10.24:10.24]. */
    ADC22_RANGE_BI_6V14 = 0x02,     /**< Input range = ±1.5×VREF   [–6.144:6.144]. */
    ADC22_RANGE_BI_5V12 = 0x03,     /**< Input range = ±1.25×VREF  [–5.12:5.12]. */
    ADC22_RANGE_BI_2V56 = 0x04,     /**< Input range = ±0.625×VREF [–2.56:2.56]. */
    ADC22_RANGE_12V28 = 0x08,       /**< Input range = 3×VREF      [0:12.288]. */
    ADC22_RANGE_10V24 = 0x09,       /**< Input range = 2.5×VREF    [0:10.24]. */
    ADC22_RANGE_6V14 = 0x0A,        /**< Input range = 1.5×VREF    [0:6.144]. */
    ADC22_RANGE_5V12 = 0x0B         /**< Input range = 1.25×VREF   [0:5.12]. */

} adc22_range_sel_t;

/*!
 * @addtogroup adc22 ADC 22 Click Driver
 * @brief API for configuring and manipulating ADC 22 Click driver.
 * @{
 */

/**
 * @brief ADC 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc22_cfg_setup ( adc22_cfg_t *cfg );

/**
 * @brief ADC 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_init ( adc22_t *ctx, adc22_cfg_t *cfg );

/**
 * @brief ADC 22 default configuration function.
 * @details This function executes a default configuration of ADC 22
 * click board.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc22_default_cfg ( adc22_t *ctx );

/**
 * @brief ADC 22 HW reset function.
 * @details This function resets the module by toggling the reset [RST] pin
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void adc22_hw_reset ( adc22_t *ctx );

/**
 * @brief ADC 22 get interrupt function.
 * @details This function get states of the interrupt [INT] pin
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t adc22_get_interrupt ( adc22_t *ctx );

/**
 * @brief ADC 22 get RVS function.
 * @details This function get states of the reflects status [RVS] pin
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t adc22_get_rvs ( adc22_t *ctx );


/**
 * @brief ADC 22 data writing function.
 * @details This function writes a desired data to the selected register 
 * by using desired write command of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[in] w_cmd : Write command.
 * See #adc22_cmd definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_write_reg ( adc22_t *ctx, uint8_t w_cmd, uint8_t reg, uint8_t data_in );

/**
 * @brief ADC 22 data reading function.
 * @details This function reads a data bytes from the selected register
 * by using desired read command of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[in] r_cmd : Raed command.
 * See #adc22_cmd definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_read_reg ( adc22_t *ctx, uint8_t r_cmd, uint8_t reg, uint8_t *data_out );

/**
 * @brief ADC 22 get ADC raw data function.
 * @details This function reads a 12-bit ADC raw data
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[out] raw_adc : 12-bit ADC raw data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_get_adc_raw_data ( adc22_t *ctx, uint16_t *raw_adc );

/**
 * @brief ADC 22 get voltage level function.
 * @details This function reads results of 12-bit ADC raw data 
 * and converts them to proportional voltage level, 
 * depending on the configured operating input range
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_get_voltage ( adc22_t *ctx, float *voltage );

/**
 * @brief ADC 22 set device address function.
 * @details This function sets the device address
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[in] device_addr : Device address [0-16].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_set_device_addr ( adc22_t *ctx, uint8_t device_addr );

/**
 * @brief ADC 22 get device ID function.
 * @details This function reads the device address ID
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[out] device_id : Device ID [0-16].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_get_device_id ( adc22_t *ctx, uint8_t *device_id );

/**
 * @brief ADC 22 set SDO mode function.
 * @details This function configure desired SDO operation mode
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[in] sdo_mode : SDO operation mode [1-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_set_sdo_mode ( adc22_t *ctx, uint8_t sdo_mode );

/**
 * @brief ADC 22 enable output data parity function.
 * @details This function enables output data parity and configure output value [1's]
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_en_out_data_parity ( adc22_t *ctx );

/**
 * @brief ADC 22 set range function.
 * @details This function sets operating input range
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[in] range : Input range.
 * See #adc22_range_sel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_set_range ( adc22_t *ctx, adc22_range_sel_t range );

/**
 * @brief ADC 22 get range function.
 * @details This function reads the operating input range
 * of the ADS8665IPW, 12-Bit, High-Speed, Single-Supply, 
 * SAR ADC Data Acquisition System With Programmable, Bipolar Input Ranges
 * on the ADC 22 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc22_t object definition for detailed explanation.
 * @param[out] range : Input range.
 * See #adc22_range_sel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc22_get_range ( adc22_t *ctx, uint8_t *range );

#ifdef __cplusplus
}
#endif
#endif // ADC22_H

/*! @} */ // adc22

// ------------------------------------------------------------------------ END
