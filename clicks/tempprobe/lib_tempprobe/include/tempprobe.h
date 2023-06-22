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
 * @file tempprobe.h
 * @brief This file contains API for Temp Probe Click Driver.
 */

#ifndef TEMPPROBE_H
#define TEMPPROBE_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup tempprobe Temp Probe Click Driver
 * @brief API for configuring and manipulating Temp Probe Click driver.
 * @{
 */

/**
 * @defgroup tempprobe_reg Temp Probe Registers List
 * @brief List of registers of Temp Probe Click driver.
 */

/**
 * @addtogroup tempprobe_reg
 * @{
 */

/**
 * @brief Temp Probe description register.
 * @details Specified register for description of Temp Probe Click driver.
 */
#define TEMPPROBE_REG_COMM_STATUS               0x0000
#define TEMPPROBE_REG_THERMO_K_CONV_RES         0x0024
#define TEMPPROBE_REG_PN_JUNCTION_CONV_RES      0x0030
#define TEMPPROBE_REG_EEPROM_KEY                0x00B0
#define TEMPPROBE_REG_EEPROM_READ_RES_CODE      0x00D0
#define TEMPPROBE_REG_GLOBAL_CONFIG             0x00F0
#define TEMPPROBE_REG_MEAS_MULTIPLE_CHANN_MASK  0x00F4
#define TEMPPROBE_REG_EEPROM_STATUS             0x00F9
#define TEMPPROBE_REG_MUX_CONFIG_DELAY          0x00FF
#define TEMPPROBE_REG_THERMO_K_ASSIGN_DATA      0x0214
#define TEMPPROBE_REG_PN_JUNCTION_ASSIGN_DATA   0x0220
#define TEMPPROBE_REG_CUSTOM_SENS_TABLE_DATA    0x0250

/*! @} */ // tempprobe_reg

/**
 * @defgroup tempprobe_set Temp Probe Registers Settings
 * @brief Settings for registers of Temp Probe Click driver.
 */

/**
 * @addtogroup tempprobe_set
 * @{
 */

/**
 * @brief Temp Probe type setting.
 * @details Specified setting for temperature probe type of Temp Probe Click driver.
 */
#define TEMPPROBE_TYPE_J_THERMOCOUPLE           0x08000000ul
#define TEMPPROBE_TYPE_K_THERMOCOUPLE           0x10000000ul
#define TEMPPROBE_TYPE_E_THERMOCOUPLE           0x18000000ul
#define TEMPPROBE_TYPE_N_THERMOCOUPLE           0x20000000ul
#define TEMPPROBE_TYPE_R_THERMOCOUPLE           0x28000000ul
#define TEMPPROBE_TYPE_S_THERMOCOUPLE           0x30000000ul
#define TEMPPROBE_TYPE_T_THERMOCOUPLE           0x38000000ul
#define TEMPPROBE_TYPE_B_THERMOCOUPLE           0x40000000ul
#define TEMPPROBE_CUSTOM_THERMOCOUPLE           0x48000000ul

/**
 * @brief Temp Probe cold junction setting.
 * @details Specified setting for cold junction of Temp Probe Click driver.
 */
#define TEMPPROBE_CH1_COLD_JUNCTION             0x00400000ul
#define TEMPPROBE_CH2_COLD_JUNCTION             0x00800000ul
#define TEMPPROBE_CH3_COLD_JUNCTION             0x00C00000ul
#define TEMPPROBE_CH4_COLD_JUNCTION             0x01000000ul
#define TEMPPROBE_CH5_COLD_JUNCTION             0x01400000ul
#define TEMPPROBE_CH6_COLD_JUNCTION             0x01800000ul
#define TEMPPROBE_CH7_COLD_JUNCTION             0x01C00000ul
#define TEMPPROBE_CH8_COLD_JUNCTION             0x02000000ul
#define TEMPPROBE_CH9_COLD_JUNCTION             0x02400000ul
#define TEMPPROBE_CH10_COLD_JUNCTION            0x02800000ul
#define TEMPPROBE_NO_COLD_JUNCTION              0x00000000ul

/**
 * @brief Temp Probe open-circuit current setting.
 * @details Specified setting for open-circuit current of Temp Probe Click driver.
 */
#define TEMPPROBE_DIFF_EXTERNAL_CURR            0x00000000ul
#define TEMPPROBE_DIFF_10MICROA_CURR            0x00100000ul
#define TEMPPROBE_DIFF_100MICROA_CURR           0x00140000ul
#define TEMPPROBE_DIFF_500MICROA_CURR           0x00180000ul
#define TEMPPROBE_DIFF_1MILIA_CURR              0x001C0000ul
#define TEMPPROBE_SINGLE_ENDED_EXT_CURR         0x00200000ul
#define TEMPPROBE_SINGLE_ENDED_10MICROA_CURR    0x00300000ul
#define TEMPPROBE_SINGLE_ENDED_100MICROA_CURR   0x00340000ul
#define TEMPPROBE_SINGLE_ENDED_500MICROA_CURR   0x00380000ul
#define TEMPPROBE_SINGLE_ENDED_1MILIA_CURR      0x003C0000ul

/**
 * @brief Temp Probe open-circuit current setting.
 * @details Specified setting for open-circuit current of Temp Probe Click driver.
 */
#define TEMPPROBE_SENSE_RES_CH2_CH1             0x00800000ul
#define TEMPPROBE_SENSE_RES_CH3_CH2             0x00C00000ul
#define TEMPPROBE_SENSE_RES_CH4_CH3             0x01000000ul
#define TEMPPROBE_SENSE_RES_CH5_CH4             0x01400000ul
#define TEMPPROBE_SENSE_RES_CH6_CH5             0x01800000ul
#define TEMPPROBE_SENSE_RES_CH7_CH6             0x01C00000ul
#define TEMPPROBE_SENSE_RES_CH8_CH7             0x02000000ul
#define TEMPPROBE_SENSE_RES_CH9_CH8             0x02400000ul
#define TEMPPROBE_SENSE_RES_CH10_CH9            0x02800000ul

/**
 * @brief Temp Probe RTD sensor configuration setting.
 * @details Specified RTD sensor configuration settings of Temp Probe Click driver.
 */
#define TEMPPROBE_2_WIRE_GND_EXT                0x00000000ul
#define TEMPPROBE_2_WIRE_GND_INT                0x00040000ul
#define TEMPPROBE_3_WIRE_GND_EXT                0x00100000ul
#define TEMPPROBE_3_WIRE_GND_INT                0x00140000ul
#define TEMPPROBE_4_WIRE_GND_EXT                0x00200000ul
#define TEMPPROBE_4_WIRE_GND_INT                0x00240000ul
#define TEMPPROBE_4_WIRE_CURR_ROT               0x00280000ul
#define TEMPPROBE_4_WIRE_KELVIN_RSENSE_GND_EXT  0x00300000ul
#define TEMPPROBE_4_WIRE_KELVIN_RSENSE_GND_INT  0x00340000ul
#define TEMPPROBE_4_WIRE_KELVIN_RSENSE_CURR_ROT 0x00380000ul

/**
 * @brief Temp Probe current setting.
 * @details Specified current settings of Temp Probe Click driver.
 */
#define TEMPPROBE_EXTERNAL_CURR                 0x00000000ul
#define TEMPPROBE_5MICROA_CURR                  0x00004000ul
#define TEMPPROBE_10MICROA_CURR                 0x00008000ul
#define TEMPPROBE_25MICROA_CURR                 0x0000C000ul
#define TEMPPROBE_50MICROA_CURR                 0x00010000ul
#define TEMPPROBE_100MICROA_CURR                0x00014000ul
#define TEMPPROBE_250MICROA_CURR                0x00018000ul
#define TEMPPROBE_500MICROA_CURR                0x0001C000ul
#define TEMPPROBE_1MILIA_CURR                   0x00020000ul

/**
 * @brief Temp Probe curve setting.
 * @details Specified curve settings of Temp Probe Click driver.
 */
#define TEMPPROBE_EUROPEAN_CURVE                0x00000000ul
#define TEMPPROBE_AMERICAN_CURVE                0x00001000ul
#define TEMPPROBE_JAPANESE_CURVE                0x00002000ul
#define TEMPPROBE_ITS_90_CURVE                  0x00003000ul
#define TEMPPROBE_OTHERS_CURVES                 0x00000000ul

/**
 * @brief Temp Probe sense resistor setting.
 * @details Specified sense resistor settings of Temp Probe Click driver.
 */
#define TEMPPROBE_SENSE_RESISTOR                0xE8000000ul
#define TEMPPROBE_SENSE_RES_2K                  0x001F4000ul
#define TEMPPROBE_SENSE_RES_10K2                0x009C40CDul
#define TEMPPROBE_SENSE_RES_1K                  0x000FA933ul

/**
 * @brief Temp Probe diode setting.
 * @details Specified diode settings of Temp Probe Click driver.
 */
#define TEMPPROBE_DIODE                         0xE0000000ul
#define TEMPPROBE_DIRECT_ADC                    0xF0000000ul
#define TEMPPROBE_ANALOG_TEMP_SENS              0xF8000000ul
#define TEMPPROBE_DIODE_SNGL_END                0x04000000ul
#define TEMPPROBE_DIODE_DIFF                    0x00000000ul
#define TEMPPROBE_DIODE_2_READ                  0x00000000ul
#define TEMPPROBE_DIODE_3_READ                  0x02000000ul
#define TEMPPROBE_DIODE_AVRG_ON                 0x01000000ul

/**
 * @brief Temp Probe EEPROM setting.
 * @details Specified EEPROM settings of Temp Probe Click driver.
 */
#define TEMPPROBE_START_CONV                    0x80
#define TEMPPROBE_INITIATE_SLEEP                0x97
#define TEMPPROBE_READ_EEPROM                   0x96
#define TEMPPROBE_WRITE_EEPROM                  0x95

/**
 * @brief Temp Probe measurement setting.
 * @details Specified measurement settings of Temp Probe Click driver.
 */
#define TEMPPROBE_FILTER_FREQ_55HZ              0x00
#define TEMPPROBE_FILTER_FREQ_60HZ              0x01
#define TEMPPROBE_FILTER_FREQ_50HZ              0x02
#define TEMPPROBE_CELSIUS                       0x00
#define TEMPPROBE_FAHRENHEIT                    0x04
#define TEMPPROBE_3_WIRE_RTD_KELVIN_CURR        0x10
#define TEMPPROBE_2_WIRE_RTD_KELVIN_CURR        0x20
#define TEMPPROBE_THERMISTOR_KELVIN_CURR        0x40

/**
 * @brief Temp Probe channel mask setting.
 * @details Specified channel mask settings of Temp Probe Click driver.
 */
#define TEMPPROBE_CH10_MASK                     0x00000200ul
#define TEMPPROBE_CH9_MASK                      0x00000100ul
#define TEMPPROBE_CH8_MASK                      0x00000080ul
#define TEMPPROBE_CH7_MASK                      0x00000040ul
#define TEMPPROBE_CH6_MASK                      0x00000020ul
#define TEMPPROBE_CH5_MASK                      0x00000010ul
#define TEMPPROBE_CH4_MASK                      0x00000008ul
#define TEMPPROBE_CH3_MASK                      0x00000004ul
#define TEMPPROBE_CH2_MASK                      0x00000002ul
#define TEMPPROBE_CH1_MASK                      0x00000001ul
#define TEMPPROBE_NO_CHANN_MASK                 0x00000000ul
#define TEMPPROBE_ALL_CHANN_MASK                0x000003FFul

#define TEMPPROBE_EEPROM_KEY                    0xA53C0F5Aul

/**
 * @brief Temp Probe spi instructions setting.
 * @details Specified spi instructions settings of Temp Probe Click driver.
 */
#define TEMPPROBE_SPI_READ_INSTR                0x03
#define TEMPPROBE_SPI_WRITE_INSTR               0x02

/**
 * @brief Temp Probe error states setting.
 * @details Specified error states settings of Temp Probe Click driver.
 */
#define TEMPPROBE_REG_ADDR_ERROR                0x01
#define TEMPPROBE_NUM_BYTES_ERROR               0x02
#define TEMPPROBE_NO_ERROR                      0x00
#define TEMPPROBE_BUSY_STATE                    0x02
#define TEMPPROBE_NO_BUSY_STATE                 0x01
#define TEMPPROBE_EEPROM_READ_PASS              0x00
#define TEMPPROBE_EEPROM_READ_FAIL              0xFF
#define TEMPPROBE_CHANN_SEL_ERROR               0xFF

#define TEMPPROBE_PN_JUNCTION_DEF_CFG           0xE5000000
#define TEMPPROBE_GLOBAL_CONFIG_DEF_CFG         0x00000072


/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Can be overwritten with @b tempprobe_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define TEMPPROBE_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define TEMPPROBE_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // tempprobe_set

/**
 * @defgroup tempprobe_map Temp Probe MikroBUS Map
 * @brief MikroBUS pin mapping of Temp Probe Click driver.
 */

/**
 * @addtogroup tempprobe_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Temp Probe Click to the selected MikroBUS.
 */
#define TEMPPROBE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tempprobe_map
/*! @} */ // tempprobe

/**
 * @brief Temp Probe Click context object.
 * @details Context object definition of Temp Probe Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;                              /**< Reset. */

    // Input pins
    digital_in_t  int_pin;                           /**< Interrupt. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */
    uint8_t drv_temperature_format;                  /**< Temperature format. */

} tempprobe_t;

/**
 * @brief Temp Probe Click configuration object.
 * @details Configuration object definition of Temp Probe Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;                                     /**< Reset. */
    pin_name_t  int_pin;                                 /**< Interrupt. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} tempprobe_cfg_t;

/**
 * @brief Temp Probe Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPPROBE_OK = 0,
    TEMPPROBE_ERROR = -1

} tempprobe_return_value_t;

/*!
 * @addtogroup tempprobe Temp Probe Click Driver
 * @brief API for configuring and manipulating Temp Probe Click driver.
 * @{
 */

/**
 * @brief Temp Probe configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tempprobe_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tempprobe_cfg_setup ( tempprobe_cfg_t *cfg );

/**
 * @brief Temp Probe initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tempprobe_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t tempprobe_init ( tempprobe_t *ctx, tempprobe_cfg_t *cfg );

/**
 * @brief Temp Probe default configuration function.
 * @details This function executes a default configuration of Temp Probe
 * click board.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t tempprobe_default_cfg ( tempprobe_t *ctx );

/**
 * @brief Byte Write function.
 * @details Function writes one byte data to the register.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @param[in] reg_addr : Address where byte be written.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c  1 - Wrong address parameter,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t tempprobe_write_byte ( tempprobe_t *ctx, uint16_t reg_addr, uint8_t data_in );

/**
 * @brief Word Write function.
 * @details Function writes 32-bit data to the register.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @param[in] reg_addr : Address where data be written.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c  1 - Wrong address parameter,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t tempprobe_write_dword ( tempprobe_t *ctx, uint16_t reg_addr, uint32_t data_in );

/**
 * @brief Byte Read function.
 * @details Function reads the desired number of bytes from the registers.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @param[in] reg_addr : Start address which from byte/bytes be read.
 * @param[out] data_out : Memory where byte/bytes be stored.
 * @param[in] n_bytes : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c  1 - Wrong address parameter,
 *         @li @c  2 - Number of bytes is out of range,
 *         @li @c -1 - Error.
 */
err_t tempprobe_read_bytes( tempprobe_t *ctx, uint16_t reg_addr, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Word Read function.
 * @details Function reads 32-bit data from the registers.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @param[in] reg_addr : Address which from data be read.
 * @param[out] data_out : Memory where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c  1 - Wrong address parameter,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t tempprobe_read_dword ( tempprobe_t *ctx, uint16_t reg_addr, uint32_t *data_out );

/**
 * @brief Busy Check function.
 * @details Function returns 2 if the device is busy, or 1 if is not (conversion cycle is finished).
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @return @li @c  1 - Conversion cycle is finished,
 *         @li @c  2 - Busy.
 */
uint8_t tempprobe_check_busy ( tempprobe_t *ctx );

/**
 * @brief Reset function.
 * @details Function performs the device reset and waits until reset command is
 * finished and the device is ready for ussing.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @return Nothing.
 */
void tempprobe_reset( tempprobe_t *ctx );

/**
 * @brief EEPROM Write function.
 * @details Function writes the current settings from the chip registers to
 * the EEPROM memory and checks is error occurred.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @returns EEPROM status byte from the register (error check register)
 */
uint8_t tempprobe_write_eeprom_data ( tempprobe_t *ctx );

/**
 * @brief EEPROM Read function.
 * @details Function reads the memorized settings from the EEPROM memory and writes
 * this settings to the chip configuration registers. Also checks is reading has passed or not.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @returns 0 - Reading has passed, or error byte from the EEPROM status register if error is occurred.
 */
uint8_t tempprobe_read_eeprom_data ( tempprobe_t *ctx );

/**
 * @brief Temperature Read function.
 * @details Function reads temperature data from the desired channel.
 * @param[in] ctx : Click context object.
 * See #tempprobe_t object definition for detailed explanation.
 * @param[in] sel_channel : Channel which from temperature be read.
 * @param[out] data_out : Memory where temperature data be stored.
 * @returns 1 - Temperature data is valid, or if is not valid returns error status byte
 */
uint8_t tempprobe_read_temp ( tempprobe_t *ctx, uint16_t sel_channel, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // TEMPPROBE_H

/*! @} */ // tempprobe

// ------------------------------------------------------------------------ END
