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
 * @file waveform4.h
 * @brief This file contains API for Waveform 4 Click Driver.
 */

#ifndef WAVEFORM4_H
#define WAVEFORM4_H

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
 * @addtogroup waveform4 Waveform 4 Click Driver
 * @brief API for configuring and manipulating Waveform 4 Click driver.
 * @{
 */

/**
 * @defgroup waveform4_reg Waveform 4 Registers List
 * @brief List of registers of Waveform 4 Click driver.
 */

/**
 * @addtogroup waveform4_reg
 * @{
 */

/**
 * @brief Waveform 4 register map.
 * @details Specified register map of Waveform 4 Click driver.
 */
#define WAVEFORM4_REG_SPI_CONFIG                0x0000
#define WAVEFORM4_REG_POWER_CONFIG              0x0001
#define WAVEFORM4_REG_CLOCK_CONFIG              0x0002
#define WAVEFORM4_REG_REF_ADJ                   0x0003
#define WAVEFORM4_REG_DAC4_AGAIN                0x0004
#define WAVEFORM4_REG_DAC3_AGAIN                0x0005
#define WAVEFORM4_REG_DAC2_AGAIN                0x0006
#define WAVEFORM4_REG_DAC1_AGAIN                0x0007
#define WAVEFORM4_REG_DACX_RANGE                0x0008
#define WAVEFORM4_REG_DAC4_RSET                 0x0009
#define WAVEFORM4_REG_DAC3_RSET                 0x000A
#define WAVEFORM4_REG_DAC2_RSET                 0x000B
#define WAVEFORM4_REG_DAC1_RSET                 0x000C
#define WAVEFORM4_REG_CAL_CONFIG                0x000D
#define WAVEFORM4_REG_COMP_OFFSET               0x000E
#define WAVEFORM4_REG_RAM_UPDATE                0x001D
#define WAVEFORM4_REG_PAT_STATUS                0x001E
#define WAVEFORM4_REG_PAT_TYPE                  0x001F
#define WAVEFORM4_REG_PATTERN_DLY               0x0020
#define WAVEFORM4_REG_DAC4_DOF                  0x0022
#define WAVEFORM4_REG_DAC3_DOF                  0x0023
#define WAVEFORM4_REG_DAC2_DOF                  0x0024
#define WAVEFORM4_REG_DAC1_DOF                  0x0025
#define WAVEFORM4_REG_WAV43_CONFIG              0x0026
#define WAVEFORM4_REG_WAV21_CONFIG              0x0027 
#define WAVEFORM4_REG_PAT_TIMEBASE              0x0028
#define WAVEFORM4_REG_PAT_PERIOD                0x0029
#define WAVEFORM4_REG_DAC43_PATX                0x002A
#define WAVEFORM4_REG_DAC21_PATX                0x002B                
#define WAVEFORM4_REG_DOUT_START_DLY            0x002C
#define WAVEFORM4_REG_DOUT_CONFIG               0x002D
#define WAVEFORM4_REG_DAC4_CST                  0x002E
#define WAVEFORM4_REG_DAC3_CST                  0x002F
#define WAVEFORM4_REG_DAC2_CST                  0x0030
#define WAVEFORM4_REG_DAC1_CST                  0x0031
#define WAVEFORM4_REG_DAC4_DGAIN                0x0032
#define WAVEFORM4_REG_DAC3_DGAIN                0x0033
#define WAVEFORM4_REG_DAC2_DGAIN                0x0034
#define WAVEFORM4_REG_DAC1_DGAIN                0x0035
#define WAVEFORM4_REG_SAW43_CONFIG              0x0036
#define WAVEFORM4_REG_SAW21_CONFIG              0x0037
#define WAVEFORM4_REG_DDS_TW32                  0x003E
#define WAVEFORM4_REG_DDS_TW1                   0x003F
#define WAVEFORM4_REG_DDS4_PW                   0x0040
#define WAVEFORM4_REG_DDS3_PW                   0x0041
#define WAVEFORM4_REG_DDS2_PW                   0x0042
#define WAVEFORM4_REG_DDS1_PW                   0x0043
#define WAVEFORM4_REG_TRIG_TW_SEL               0x0044
#define WAVEFORM4_REG_DDSX_CONFIG               0x0045
#define WAVEFORM4_REG_TW_RAM_CONFIG             0x0047
#define WAVEFORM4_REG_START_DLY4                0x0050
#define WAVEFORM4_REG_START_ADDR4               0x0051
#define WAVEFORM4_REG_STOP_ADDR4                0x0052
#define WAVEFORM4_REG_DDS_CYC4                  0x0053
#define WAVEFORM4_REG_START_DLY3                0x0054
#define WAVEFORM4_REG_START_ADDR3               0x0055
#define WAVEFORM4_REG_STOP_ADDR3                0x0056
#define WAVEFORM4_REG_DDS_CYC3                  0x0057
#define WAVEFORM4_REG_START_DLY2                0x0058
#define WAVEFORM4_REG_START_ADDR2               0x0059
#define WAVEFORM4_REG_STOP_ADDR2                0x005A
#define WAVEFORM4_REG_DDS_CYC2                  0x005B
#define WAVEFORM4_REG_START_DLY1                0x005C
#define WAVEFORM4_REG_START_ADDR1               0x005D
#define WAVEFORM4_REG_STOP_ADDR1                0x005E
#define WAVEFORM4_REG_DDS_CYC1                  0x005F
#define WAVEFORM4_REG_CFG_ERROR                 0x0060
#define WAVEFORM4_SRAM_ADDRESS_MIN              0x6000
#define WAVEFORM4_SRAM_ADDRESS_MAX              0x6FFF

/*! @} */ // waveform4_reg

/**
 * @defgroup waveform4_set Waveform 4 Registers Settings
 * @brief Settings for registers of Waveform 4 Click driver.
 */

/**
 * @addtogroup waveform4_set
 * @{
 */

/**
 * @brief Waveform 4 wave config macros.
 * @details Specified macros for wave config of Waveform 4 Click driver.
 */
#define WAVEFORM4_WAV_CFG_PRESTORE_CST          0x00
#define WAVEFORM4_WAV_CFG_PRESTORE_SAWTOOTH     0x10
#define WAVEFORM4_WAV_CFG_PRESTORE_PSEUDO       0x20
#define WAVEFORM4_WAV_CFG_PRESTORE_DDS          0x30
#define WAVEFORM4_WAV_CFG_WAVE_FROM_RAM         0x00
#define WAVEFORM4_WAV_CFG_WAVE_PRESTORED        0x01
#define WAVEFORM4_WAV_CFG_WAVE_PRESTORED_DELAY  0x02
#define WAVEFORM4_WAV_CFG_WAVE_PRESTORED_RAM    0x03
#define WAVEFORM4_DDSX_CFG_ENABLE_COSINE        0x08
#define WAVEFORM4_SAW_CFG_RAMP_UP               0x00
#define WAVEFORM4_SAW_CFG_RAMP_DOWN             0x01
#define WAVEFORM4_SAW_CFG_TRIANGLE              0x02
#define WAVEFORM4_SAW_CFG_NO_WAVE               0x03
#define WAVEFORM4_SAW_CFG_STEP_1                0x04

/**
 * @brief Waveform 4 default settings macros.
 * @details Specified macros for default settings of Waveform 4 Click driver.
 */
#define WAVEFORM4_DEFAULT_GAIN                  0.5
#define WAVEFORM4_DEFAULT_FREQUENCY             100000

/**
 * @brief Waveform 4 ram update and pat status register macros.
 * @details Specified macros for ram update and pat status registers of Waveform 4 Click driver.
 */
#define WAVEFORM4_UPDATE_SETTINGS               0x01
#define WAVEFORM4_MEM_ACCESS_ENABLE             0x04
#define WAVEFORM4_MEM_ACCESS_DISABLE            0x00
#define WAVEFORM4_BUF_READ                      0x08
#define WAVEFORM4_START_PATTERN                 0x01
#define WAVEFORM4_STOP_PATTERN                  0x00

/**
 * @brief Waveform 4 channel selection macros.
 * @details Specified macros for channel selection of Waveform 4 Click driver.
 */
#define WAVEFORM4_CHANNEL_1                     0x00
#define WAVEFORM4_CHANNEL_2                     0x01
#define WAVEFORM4_CHANNEL_3                     0x02
#define WAVEFORM4_CHANNEL_4                     0x03

/**
 * @brief Waveform 4 wave output selection macros.
 * @details Specified macros for wave output selection of Waveform 4 Click driver.
 */
#define WAVEFORM4_WAVE_SINE                     0x00
#define WAVEFORM4_WAVE_COSINE                   0x01
#define WAVEFORM4_WAVE_TRIANGLE                 0x02
#define WAVEFORM4_WAVE_POSITIVE_SAWTOOTH        0x03
#define WAVEFORM4_WAVE_NEGATIVE_SAWTOOTH        0x04

/**
 * @brief Waveform 4 gain calculation macros.
 * @details Specified macros for gain calculation of Waveform 4 Click driver.
 */
#define WAVEFORM4_GAIN_MAX                      2.0
#define WAVEFORM4_GAIN_MIN                      (-2.0)
#define WAVEFORM4_GAIN_RESOLUTION               1024

/**
 * @brief Waveform 4 frequency calculation constants.
 * @details Specified constants for frequency calculation of Waveform 4 Click driver.
 */
#define WAVEFORM4_MASTER_CLOCK                  125000000
#define WAVEFORM4_FREQ_RESOLUTION               0x1000000

/**
 * @brief Waveform 4 SPI read/write setting.
 * @details Specified setting for SPI read/write of Waveform 4 Click driver.
 */
#define WAVEFORM4_SPI_READ_MASK                 0x80
#define WAVEFORM4_SPI_WRITE_MASK                0x7F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b waveform4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define WAVEFORM4_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define WAVEFORM4_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // waveform4_set

/**
 * @defgroup waveform4_map Waveform 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Waveform 4 Click driver.
 */

/**
 * @addtogroup waveform4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Waveform 4 Click to the selected MikroBUS.
 */
#define WAVEFORM4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.trg  = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // waveform4_map
/*! @} */ // waveform4

/**
 * @brief Waveform 4 Click context object.
 * @details Context object definition of Waveform 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset pin. */
    digital_out_t  trg;         /**< Pattern Trigger pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} waveform4_t;

/**
 * @brief Waveform 4 Click configuration object.
 * @details Configuration object definition of Waveform 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;            /**< Reset pin. */
    pin_name_t  trg;            /**< Pattern Trigger pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} waveform4_cfg_t;

/**
 * @brief Waveform 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WAVEFORM4_OK = 0,
    WAVEFORM4_ERROR = -1

} waveform4_return_value_t;

/*!
 * @addtogroup waveform4 Waveform 4 Click Driver
 * @brief API for configuring and manipulating Waveform 4 Click driver.
 * @{
 */

/**
 * @brief Waveform 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #waveform4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void waveform4_cfg_setup ( waveform4_cfg_t *cfg );

/**
 * @brief Waveform 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #waveform4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_init ( waveform4_t *ctx, waveform4_cfg_t *cfg );

/**
 * @brief Waveform 4 default configuration function.
 * @details This function executes a default configuration of Waveform 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t waveform4_default_cfg ( waveform4_t *ctx );

/**
 * @brief Waveform 4 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_write_registers ( waveform4_t *ctx, uint16_t reg, uint16_t *data_in, uint8_t len );

/**
 * @brief Waveform 4 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_read_registers ( waveform4_t *ctx, uint16_t reg, uint16_t *data_out, uint8_t len );

/**
 * @brief Waveform 4 single data writing function.
 * @details This function writes a single data byte to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_write_register ( waveform4_t *ctx, uint16_t reg, uint16_t data_in );

/**
 * @brief Waveform 4 single data reading function.
 * @details This function reads a single data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_read_register ( waveform4_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief Waveform 4 set RST pin function.
 * @details This function sets the RST pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void waveform4_set_rst_pin ( waveform4_t *ctx, uint8_t state );

/**
 * @brief Waveform 4 set TRG pin function.
 * @details This function sets the TRG pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void waveform4_set_trg_pin ( waveform4_t *ctx, uint8_t state );

/**
 * @brief Waveform 4 reset registers function.
 * @details This function resets all registers to default values.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void waveform4_reset_registers ( waveform4_t *ctx );

/**
 * @brief Waveform 4 start pattern function.
 * @details This function starts pattern generation by setting the RUN bit to 1 and 
 * the TRG pin low logic state.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_start_pattern ( waveform4_t *ctx );

/**
 * @brief Waveform 4 stop pattern function.
 * @details This function stops pattern generation by setting the RUN bit to 0 and 
 * the TRG pin high logic state.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_stop_pattern ( waveform4_t *ctx );

/**
 * @brief Waveform 4 update settings function.
 * @details This function updates all SPI setting with new configuration by setting
 * RAMUPDATE bit to 1.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_update_settings ( waveform4_t *ctx );

/**
 * @brief Waveform 4 write sram function.
 * @details This function writes a desired number of data bytes to the SRAM starting from
 * the selected memory address.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] address : SRAM memory address [0x6000,0x6FFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_write_sram ( waveform4_t *ctx, uint16_t address, uint16_t *data_in, uint16_t len );

/**
 * @brief Waveform 4 read sram function.
 * @details This function reads a desired number of data bytes from the SRAM starting from
 * the selected memory address.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] address : SRAM memory address [0x6000,0x6FFF].
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_read_sram ( waveform4_t *ctx, uint16_t address, uint16_t *data_out, uint16_t len );

/**
 * @brief Waveform 4 set frequency function.
 * @details This function sets the sine and cosine (DDS) waves output frequency.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] freq : Frequency in Hz ( up to 125MHz ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_set_frequency ( waveform4_t *ctx, uint32_t freq );

/**
 * @brief Waveform 4 set gain function.
 * @details This function sets the gain level of a desired channel.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] channel : Channel number [0,3].
 * @param[in] gain : Gain level [-2,2].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_set_gain ( waveform4_t *ctx, uint8_t channel, float gain );

/**
 * @brief Waveform 4 set wave output function.
 * @details This function sets a desired output signal wave to the selected channel.
 * @param[in] ctx : Click context object.
 * See #waveform4_t object definition for detailed explanation.
 * @param[in] channel : Channel number [0,3].
 * @param[in] wave : @li @c  0 - Sine wave,
 *                   @li @c  1 - Cosine wave,
 *                   @li @c  2 - Triangle wave,
 *                   @li @c  3 - Positive sawtooth wave,
 *                   @li @c  4 - Negative sawtooth wave.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_set_wave_output ( waveform4_t *ctx, uint8_t channel, uint8_t wave );

#ifdef __cplusplus
}
#endif
#endif // WAVEFORM4_H

/*! @} */ // waveform4

// ------------------------------------------------------------------------ END
