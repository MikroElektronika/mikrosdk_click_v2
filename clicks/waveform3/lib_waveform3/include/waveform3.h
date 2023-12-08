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
 * @file waveform3.h
 * @brief This file contains API for Waveform 3 Click Driver.
 */

#ifndef WAVEFORM3_H
#define WAVEFORM3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
    
/*!
 * @addtogroup waveform3 Waveform 3 Click Driver
 * @brief API for configuring and manipulating Waveform 3 Click driver.
 * @{
 */

/**
 * @defgroup waveform3_reg Waveform 3 Registers List
 * @brief List of registers of Waveform 3 Click driver.
 */

/**
 * @addtogroup waveform3_reg
 * @{
 */

/**
 * @brief Waveform 3 B28 register bit.
 * @details Allows 28-bit frequency register to operate as two 14-bit
 * registers of Waveform 3 Click driver.
 */
#define WAVEFORM3_REG_B28_BIT                                   1 << 13

/**
 * @brief Waveform 3 HLB register bit.
 * @details This control bit allows the user to continuously load the MSBs
 * or LSBs of a frequency register while ignoring the remaining 14 bits.
 */
#define WAVEFORM3_REG_HLB_BIT                                   1 << 12

/**
 * @brief Waveform 3 FSEL register bit.
 * @details This bit defines whether the FREQ0 register or the FREQ1
 * register is used in the phase accumulator.
 */
#define WAVEFORM3_REG_FSEL_BIT                                  1 << 11

/**
 * @brief Waveform 3 PSEL register bit.
 * @details This bit defines whether the PHASE0 register data or the
 * PHASE1 register data is added to the output of the phase accumulator.
 */
#define WAVEFORM3_REG_PSEL_BIT                                  1 << 10

/**
 * @brief Waveform 3 RESET register bit.
 * @details This bit resets internal registers to 0.
 */
#define WAVEFORM3_REG_RESET_BIT                                 1 << 8

/**
 * @brief Waveform 3 SLEEP1 register bit.
 * @details This bit disables the internal MCLK. The DAC output remains
 * at its present value because the NCO is no longer accumulating.
 */
#define WAVEFORM3_REG_SLEEP1_BIT                                1 << 7

/**
 * @brief Waveform 3 SLEEP12 register bit.
 * @details This bit powers down the on-chip DAC. This is useful when
 * the AD9837 is used to output the MSB of the DAC data.
 */
#define WAVEFORM3_REG_SLEEP12_BIT                               1 << 6

/**
 * @brief Waveform 3 OPBITEN register bit.
 * @details This bit, in association with the MODE bit, controls
 * the output at the VOUT pin.
 */
#define WAVEFORM3_REG_OPBITEN_BIT                               1 << 5

/**
 * @brief Waveform 3 DIV2 register bit.
 * @details This bit causes the MSB of the DAC data to be output
 * at the VOUT pin.
 */
#define WAVEFORM3_REG_DIV2_BIT                                  1 << 3

/**
 * @brief Waveform 3 MODE register bit.
 * @details This bit bypasses the SIN ROM, resulting in a triangle
 * output from the DAC.
 */
#define WAVEFORM3_REG_MODE_BIT                                  1 << 1

/**
 * @brief Waveform 3 RESET register bit.
 * @details This bit disables the reset function.
 */
#define WAVEFORM3_REG_RESET_CLEAR                               0x0000

/*! @} */ // waveform3_reg

/**
 * @defgroup mode Waveform 3 Mode Settings
 * @brief Settings for modes of Waveform 3 Click driver.
 */

/**
 * @addtogroup mode
 * @{
 */

/**
 * @brief Waveform 3 sinusoidal output mode.
 * @details Results sinusoidal output from AD9837 waveform generator.
 */
#define WAVEFORM3_CFG_MODE_SINUSOIDAL                           0x00

/**
 * @brief Waveform 3 triangle output mode.
 * @details Results triangle output from AD9837 waveform generator.
 */
#define WAVEFORM3_CFG_MODE_TRIANGLE                             0x01

/**
 * @brief Waveform 3 DAC divided by 2 output mode.
 * @details Results square wave divided by 2 on output from
 * AD9837 waveform generator.
 */
#define WAVEFORM3_CFG_MODE_DAC_2                                0x02

/**
 * @brief Waveform 3 DAC output mode.
 * @details Results square wave on output from AD9837 waveform generator.
 */
#define WAVEFORM3_CFG_MODE_DAC                                  0x03

/*! @} */ // mode

/**
 * @defgroup freq_reg Waveform 3 FREQ Settings
 * @brief Selection for frequency channel of Waveform 3 Click driver.
 */

/**
 * @addtogroup freq_reg
 * @{
 */

/**
 * @brief Waveform 3 FREQ0 channel select.
 * @details Selects FREQ0 frequency channel of AD9837 waveform generator.
 */
#define WAVEFORM3_CFG_FREQ_REG0                                 0x00

/**
 * @brief Waveform 3 FREQ1 channel select.
 * @details Selects FREQ1 frequency channel of AD9837 waveform generator.
 */
#define WAVEFORM3_CFG_FREQ_REG1                                 0x01

/*! @} */ // freq_reg

/**
 * @defgroup phase_reg Waveform 3 PHASE Settings
 * @brief Selection for phase shift channel of Waveform 3 Click driver.
 */

/**
 * @addtogroup phase_reg
 * @{
 */

/**
 * @brief Waveform 3 PHASE0 channel select.
 * @details Selects PHASE0 phase shift channel of AD9837 waveform generator.
 */
#define WAVEFORM3_CFG_PHASE_REG0                                0x00

/**
 * @brief Waveform 3 PHASE1 channel select.
 * @details Selects PHASE1 phase shift channel of AD9837 waveform generator.
 */
#define WAVEFORM3_CFG_PHASE_REG1                                0x01

/*! @} */ // phase_reg

/**
 * @defgroup waveform3_default_settings Waveform 3 default Settings
 * @brief Default settings on reset, located in default_cfg function.
 */

/**
 * @addtogroup waveform3_default_settings
 * @{
 */

/**
 * @brief Waveform 3 default FREQ0 value.
 * @details This is the value of frequency on freq0 channel after reset.
 */
#define WAVEFORM3_DEFAULT_FREQ0                                 0

/**
 * @brief Waveform 3 default FREQ1 value.
 * @details This is the value of frequency on freq1 channel after reset.
 */
#define WAVEFORM3_DEFAULT_FREQ1                                 0

/**
 * @brief Waveform 3 default PHASE0 value.
 * @details This is the value of phase shift on phase0 channel after reset.
 */
#define WAVEFORM3_DEFAULT_PHASE0                                0

/**
 * @brief Waveform 3 default PHASE1 value.
 * @details This is the value of phase shift on phase1 channel after reset.
 */
#define WAVEFORM3_DEFAULT_PHASE1                                0

/*! @} */ // waveform3_default_settings

/**
 * @defgroup waveform3_map Waveform 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Waveform 3 Click driver.
 */

/**
 * @addtogroup waveform3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Waveform 3 Click to the selected MikroBUS.
 */
#define WAVEFORM3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // waveform3_map
/*! @} */ // waveform3

/**
 * @brief Waveform 3 Click context object.
 * @details Context object definition of Waveform 3 Click driver.
 */
typedef struct
{
    // Modules

    spi_master_t  spi;                                   /**< SPI driver object. */

    pin_name_t  chip_select;                             /**< Chip select pin descriptor (used for SPI driver). */

} waveform3_t;

/**
 * @brief Waveform 3 Click configuration object.
 * @details Configuration object definition of Waveform 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} waveform3_cfg_t;

/**
 * @brief Waveform 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WAVEFORM3_OK = 0,
    WAVEFORM3_ERROR = -1

} waveform3_return_value_t;

/*!
 * @addtogroup waveform3 Waveform 3 Click Driver
 * @brief API for configuring and manipulating Waveform 3 Click driver.
 * @{
 */

/**
 * @brief Waveform 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #waveform3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void waveform3_cfg_setup ( waveform3_cfg_t *cfg );

/**
 * @brief Waveform 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #waveform3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #waveform3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform3_init ( waveform3_t *ctx, waveform3_cfg_t *cfg );

/**
 * @brief Waveform 3 default configuration function.
 * @details This function executes a default configuration of Waveform 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #waveform3_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void waveform3_default_cfg ( waveform3_t *ctx );

/**
 * @brief Waveform 3 write register function.
 * @details This function is used for word transfer as a core of communication.
 * @param[in] ctx : Click context object.
 * See #waveform3_t object definition for detailed explanation.
 * @param[in] data_in : Word data.
 * 
 * @note None.
 */
void waveform3_write_register ( waveform3_t *ctx, uint16_t data_in );

/**
 * @brief Waveform 3 reset function.
 * @details This function performs simple reset of AD9837 waveform generator.
 * @param[in] ctx : Click context object.
 * See #waveform3_t object definition for detailed explanation.
 * 
 * @note None.
 */
void waveform3_reset ( waveform3_t *ctx );

/**
 * @brief Waveform 3 set frequency function.
 * @details This function sets desired frequency ( in Hz ) on desired freq channel.
 * @param[in] ctx : Click context object.
 * See #waveform3_t object definition for detailed explanation.
 * @param[in] frequency : Frequency value.
 * @param[in] freq_reg : FREQx channel.
 * @return Actual calculated set frequency.
 * 
 * @note If the correction coefficient is not used, it is advisable to check
 * the return frequency value.
 */
uint32_t waveform3_set_freq ( waveform3_t *ctx, uint32_t frequency, uint8_t freq_reg );

/**
 * @brief Waveform 3 set phase function.
 * @details This function sets desired phase shift ( in degrees ) on desired phase channel.
 * @param[in] ctx : Click context object.
 * See #waveform3_t object definition for detailed explanation.
 * @param[in] phase : Phase shift value.
 * @param[in] phase_reg : PHASEx channel.
 * @return Actual set phase shift represented in integer value.
 * 
 * @note None.
 */
uint16_t waveform3_set_phase ( waveform3_t *ctx, float phase, uint8_t phase_reg );

/**
 * @brief Waveform 3 set mode function.
 * @details This function sets output mode, freq and phase channels of AD9837 waveform generator.
 * @param[in] ctx : Click context object.
 * See #waveform3_t object definition for detailed explanation.
 * @param[in] mode : Wave output modes.
 * @param[in] freq_reg : FREQx channel.
 * @param[in] phase_reg : PHASEx channel.
 * 
 * @note None.
 */
void waveform3_set_mode ( waveform3_t *ctx, uint8_t mode, uint8_t freq_reg, uint8_t phase_reg );

#ifdef __cplusplus
}
#endif
#endif // WAVEFORM3_H

/*! @} */ // waveform3

// ------------------------------------------------------------------------ END
