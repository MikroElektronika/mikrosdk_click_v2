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
 * @file ismtx.h
 * @brief This file contains API for ISM TX Click Driver.
 */

#ifndef ISMTX_H
#define ISMTX_H

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

/*!
 * @addtogroup ismtx ISM TX Click Driver
 * @brief API for configuring and manipulating ISM TX Click driver.
 * @{
 */

/**
 * @defgroup ismtx_reg ISM TX Registers List
 * @brief List of registers of ISM TX Click driver.
 */

/**
 * @addtogroup ismtx_reg
 * @{
 */

/**
 * @brief ISM TX description register.
 * @details Specified register for description of ISM TX Click driver.
 */
#define ISMTX_REG_CFG1                  0x00
#define ISMTX_REG_CFG2                  0x01
#define ISMTX_REG_CFG3                  0x02
#define ISMTX_REG_CFG4                  0x03
#define ISMTX_REG_CFG5                  0x04
#define ISMTX_REG_SHDN                  0x05
#define ISMTX_REG_PA1                   0x06
#define ISMTX_REG_PA2                   0x07
#define ISMTX_REG_PLL1                  0x08
#define ISMTX_REG_PLL2                  0x09
#define ISMTX_REG_CFG6                  0x0A
#define ISMTX_REG_PLL3                  0x0B
#define ISMTX_REG_PLL4                  0x0C
#define ISMTX_REG_PLL5                  0x0D
#define ISMTX_REG_PLL6                  0x0E
#define ISMTX_REG_PLL7                  0x0F
#define ISMTX_REG_CFG7                  0x10
#define ISMTX_REG_CFG8                  0x17
#define ISMTX_REG_CFG9                  0x18
#define ISMTX_REG_ADDL1                 0x19
#define ISMTX_REG_ADDL2                 0x1A

/*! @} */ // ismtx_reg

/**
 * @defgroup ismtx_set ISM TX Registers Settings
 * @brief Settings for registers of ISM TX Click driver.
 */

/**
 * @addtogroup ismtx_set
 * @{
 */

/**
 * @brief ISM TX modulation setting.
 * @details Specified setting for modulation of ISM TX Click.
 */
#define ISM_TX_MODULATION_NULL          0
#define ISM_TX_MODULATION_ASK           1
#define ISM_TX_MODULATION_FSK           2

/**
 * @brief ISM TX configuration macro.
 * @details Specified macro for configuration of ISM TX Click driver.
 */
#define ISMTX_CFG_XO_CLK_DELAY          30
#define ISMTX_CFG_XO_CLK_DIV            31
#define ISMTX_CFG_FSK_SHAPE             32
#define ISMTX_CFG_SYNC                  33
#define ISMTX_CFG_MODE                  34
#define ISMTX_CFG_CLKOUT_DELAY          35
#define ISMTX_CFG_BCLK_POSTDIV          36
#define ISMTX_CFG_BCLK_PREDIV           37
#define ISMTX_CFG_PWDN_MODE             38
#define ISMTX_CFG_PA_MODE               39
#define ISMTX_CFG_PA_DRIVERS            40
#define ISMTX_CFG_PA_SHUNT              41
#define ISMTX_CFG_PA_OFFSET_CUR         42
#define ISMTX_CFG_PA_PLL_N              43
#define ISMTX_CFG_PA_LCVCO_DIV          44
#define ISMTX_CFG_PA_LCVCO_MODE         45
#define ISMTX_CFG_CP_CURRENT            46
#define ISMTX_CFG_SPITXEN1              47
#define ISMTX_CFG_FOURWIRE1             48
#define ISMTX_CFG_SPITXEN2              49
#define ISMTX_CFG_FOURWIRE2             50
#define ISMTX_CFG_DELTAF                51
#define ISMTX_CFG_DELTAF_SHAPE          52
#define ISMTX_CFG_TSTEP                 53
#define ISMTX_CFG_EN_LDO                54
#define ISMTX_CFG_DIS_LDO_FUNC_EN       55
#define ISMTX_CFG_PLL_LOOP_BAND         56
#define ISMTX_CFG_LCVCO_FAST_START      57
#define ISMTX_CFG_LCVCO_PWR             58

/**
 * @brief ISM TX configuration value.
 * @details Specified setting for configuration of ISM TX Click driver.
 */
#define ISMTX_XO_CLK_DELAY_NO_CYC       0x00
#define ISMTX_XO_CLK_DELAY_16_CYC       0x01
#define ISMTX_XO_CLK_DELAY_32_CYC       0x02
#define ISMTX_XO_CLK_DELAY_64_CYC       0x03

#define ISMTX_XO_CLK_DIV_4              0x00
#define ISMTX_XO_CLK_DIV_5              0x01
#define ISMTX_XO_CLK_DIV_6              0x02
#define ISMTX_XO_CLK_DIV_7              0x03

#define ISMTX_FSK_SHAPE_DISABLED        0x00
#define ISMTX_FSK_SHAPE_ENABLED         0x01

#define ISMTX_SYNC_DISABLE              0x00
#define ISMTX_SYNC_ENABLE               0x01

#define ISMTX_MODE_ASK                  0x00
#define ISMTX_MODE_FSK                  0x01

#define ISMTX_CLKOUT_DELAY_64_CYC       0x00
#define ISMTX_CLKOUT_DELAY_128_CYC      0x01
#define ISMTX_CLKOUT_DELAY_256_CYC      0x02
#define ISMTX_CLKOUT_DELAY_512_CYC      0x03

#define ISMTX_PWDN_MODE_SHUTDOWN        0x00
#define ISMTX_PWDN_MODE_STAMDBY         0x01
#define ISMTX_PWDN_MODE_FAST_WAKEUP     0x02
#define ISMTX_PWDN_MODE_FAST_WAKEUP_    0x03

#define ISMTX_PA_MODE_NORMAL            0x00
#define ISMTX_PA_MODE_BOOST             0x01

#define ISMTX_PA_DRIVERS_1              0x00
#define ISMTX_PA_DRIVERS_2              0x01
#define ISMTX_PA_DRIVERS_3              0x02
#define ISMTX_PA_DRIVERS_4              0x03
#define ISMTX_PA_DRIVERS_5              0x04
#define ISMTX_PA_DRIVERS_6              0x05
#define ISMTX_PA_DRIVERS_7              0x06
#define ISMTX_PA_DRIVERS_8              0x07

#define ISMTX_PA_SHUNT_0                0x00
#define ISMTX_PA_SHUNT_175              0x01
#define ISMTX_PA_SHUNT_350              0x02
#define ISMTX_PA_SHUNT_525              0x03
#define ISMTX_PA_SHUNT_700              0x04
#define ISMTX_PA_SHUNT_875              0x05
#define ISMTX_PA_SHUNT_1050             0x06
#define ISMTX_PA_SHUNT_1225             0x07
#define ISMTX_PA_SHUNT_1400             0x08
#define ISMTX_PA_SHUNT_1575             0x09
#define ISMTX_PA_SHUNT_1750             0x0A
#define ISMTX_PA_SHUNT_1925             0x0B
#define ISMTX_PA_SHUNT_2100             0x0C
#define ISMTX_PA_SHUNT_2275             0x0D
#define ISMTX_PA_SHUNT_2450             0x0E
#define ISMTX_PA_SHUNT_2625             0x0F
#define ISMTX_PA_SHUNT_2800             0x10
#define ISMTX_PA_SHUNT_2975             0x11
#define ISMTX_PA_SHUNT_3150             0x12
#define ISMTX_PA_SHUNT_3325             0x13
#define ISMTX_PA_SHUNT_3500             0x14
#define ISMTX_PA_SHUNT_3675             0x15
#define ISMTX_PA_SHUNT_3850             0x16
#define ISMTX_PA_SHUNT_4025             0x17
#define ISMTX_PA_SHUNT_4200             0x18
#define ISMTX_PA_SHUNT_4375             0x19
#define ISMTX_PA_SHUNT_4550             0x1A
#define ISMTX_PA_SHUNT_4725             0x1B
#define ISMTX_PA_SHUNT_4900             0x1C
#define ISMTX_PA_SHUNT_5075             0x1D
#define ISMTX_PA_SHUNT_5250             0x1E
#define ISMTX_PA_SHUNT_5425             0x1F

#define ISMTX_PA_OFFSET_CUR_NO          0x00
#define ISMTX_PA_OFFSET_CUR_5_PCT       0x01
#define ISMTX_PA_OFFSET_CUR_10_PCT      0x02
#define ISMTX_PA_OFFSET_CUR_15_PCT      0x03

#define ISMTX_PA_PLL_N_INT              0x00
#define ISMTX_PA_PLL_N_FRAC             0x01

#define ISMTX_PA_LCVCO_DIV_NO           0x00
#define ISMTX_PA_LCVCO_DIV_4            0x01
#define ISMTX_PA_LCVCO_DIV_8            0x02
#define ISMTX_PA_LCVCO_DIV_12           0x03

#define ISMTX_PA_LCVCO_MODE_RING        0x00
#define ISMTX_PA_LCVCO_MODE_LC          0x01

#define ISMTX_CP_CURRENT_5uA            0x00
#define ISMTX_CP_CURRENT_10uA           0x01
#define ISMTX_CP_CURRENT_15uA           0x02
#define ISMTX_CP_CURRENT_20uA           0x03

#define ISMTX_SPITXEN1_DISABLED         0x00
#define ISMTX_SPITXEN1_ENABLED          0x01

#define ISMTX_FOURWIRE1_DISABLED        0x00
#define ISMTX_FOURWIRE1_ENABLED         0x01

#define ISMTX_SPITXEN2_DISABLED         0x00
#define ISMTX_SPITXEN2_ENABLED          0x01

#define ISMTX_FOURWIRE2_DISABLED        0x00
#define ISMTX_FOURWIRE2_ENABLED         0x01

#define ISMTX_BCLK_POSTDIV_1            0x01
#define ISMTX_BCLK_POSTDIV_2            0x02
#define ISMTX_BCLK_POSTDIV_3            0x03
#define ISMTX_BCLK_POSTDIV_4            0x04
#define ISMTX_BCLK_POSTDIV_5            0x05

/*! @} */ // ismtx_set

/**
 * @defgroup ismtx_map ISM TX MikroBUS Map
 * @brief MikroBUS pin mapping of ISM TX Click driver.
 */

/**
 * @addtogroup ismtx_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISM TX Click to the selected MikroBUS.
 */
#define ISMTX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); 

/*! @} */ // ismtx_map
/*! @} */ // ismtx

/**
 * @brief ISM TX Click context object.
 * @details Context object definition of ISM TX Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mosi;             /**< SPI MOSI pin. */

    // Modules
    spi_master_t  spi;              /**< SPI driver object. */
    spi_master_config_t spi_config;

    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    pin_name_t  tx_data;
    
    uint8_t modulation;

} ismtx_t;

/**
 * @brief ISM TX Click configuration object.
 * @details Configuration object definition of ISM TX Click driver.
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

} ismtx_cfg_t;

/**
 * @brief ISM TX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISMTX_OK = 0,
    ISMTX_ERROR = -1,
    ISMTX_PARAMETER_ERROR = -2

} ismtx_return_value_t;

/*!
 * @addtogroup ismtx ISM TX Click Driver
 * @brief API for configuring and manipulating ISM TX Click driver.
 * @{
 */

/**
 * @brief ISM TX configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ismtx_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ismtx_cfg_setup ( ismtx_cfg_t *cfg );

/**
 * @brief ISM TX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ismtx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismtx_init ( ismtx_t *ctx, ismtx_cfg_t *cfg );

/**
 * @brief ISM TX default configuration function.
 * @details This function executes a default configuration of ISM TX
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ismtx_default_cfg ( ismtx_t *ctx );

/**
 * @brief ISM TX data writing function.
 * @details This function writes a bytes to the selected 
 *          register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismtx_generic_write ( ismtx_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ISM TX data reading function.
 * @details This function reads a byte from the selected 
 *          register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismtx_generic_read ( ismtx_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ISM TX software reset.
 * @details This function sends reset command and then clears it.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @return Nothing.
 * @note After reset there is 1 second delay.
 */
void ismtx_soft_reset ( ismtx_t *ctx );

/**
 * @brief ISM TX writing configuration.
 * @details This function writes a desired 
 *          value to selected configuration.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] cfg_macro : Configuration macro.
 * @param[in] cfg_value : Configuration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Unknown @b cfg_macro,
 *         @li @c -2 - @b cfg_value greater then maximum 
 *                              value for specific macro.
 * See #err_t definition for detailed explanation.
 */
err_t ismtx_set_cfg ( ismtx_t *ctx, uint8_t cfg_macro, uint8_t cfg_value );

/**
 * @brief ISM TX reading configuration.
 * @details This function reads a desired a desired 
 *          value to selected configuration
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] cfg_macro : Configuration macro.
 * @param[out] cfg_value : Configuration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Unknown @b cfg_macro.
 * See #err_t definition for detailed explanation.
 */
err_t ismtx_get_cfg ( ismtx_t *ctx, uint8_t cfg_macro, uint8_t *cfg_value );

/**
 * @brief Setting specific frequency for transmission.
 * @details This function sets a desired frequency for transmiting data.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] freq : Frequency[Hz].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Frequency value error.
 * See #err_t definition for detailed explanation.
 * @note Frequency must be between 250000000 and 950000000.
 */
err_t ismtx_set_frequency ( ismtx_t *ctx, uint32_t freq );

/**
 * @brief Getting current frequency for transmission .
 * @details This function gets a currently set frequency for transmiting data.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @return Frequency value[Hz].
 */
uint32_t ismtx_get_frequency ( ismtx_t *ctx );

/**
 * @brief Adjust frequency for transmission.
 * @details This function sets a frequency deviation to 
 *          desired value, and tweaks frequency value.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] deviation_freq : Frequency deviation value.
 * @return @li @c  0 - Success,
 *         @li @c -2 - @b deviation_freq greater then maximum value.
 * See #err_t definition for detailed explanation.
 * @note Frequency must be between 250000000 and 950000000.
 */
err_t ismtx_adjust_freq_deviation ( ismtx_t *ctx, uint32_t deviation_freq );

/**
 * @brief Adjust manchester baudrate.
 * @details This function sets a baudrate.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] baud : Baudrate value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Baudrate value error,
 *         @li @c -2 - Baudrate configuration value error.
 * See #err_t definition for detailed explanation.
 * @note Baud must be between 195 and 200000.
 */
err_t ismtx_adjust_man_bitrate ( ismtx_t *ctx, uint32_t baud );

/**
 * @brief Function for trinsmiting data.
 * @details Function sets converts data to mancheter data, sets device in 
 * transmition mode, transmits data and then returns device in normal mode.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] tx_data : Data to transmit.
 * @param[in] tx_len : Data transmition lenght.
 * @return @li @c  0 - Success,
 *         @li @c -1 - @b tx_len greater then maximum value.
 * See #err_t definition for detailed explanation.
 * @note Thins fucntion limits you to 64 bytes to transmit due to array limition, 
 * device doesn't have that limit. If you need to send more then maximum value and 
 * your architecture allows it you can increse maximum value in source files.
 */
err_t ismtx_transmit_raw_data ( ismtx_t *ctx, uint8_t *tx_data, uint8_t tx_len );

/**
 * @brief Function for transmitting data with preamble byte and lenght.
 * @details Function transmits preamble byte, data length and then data.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @param[in] preamble_byte : Preamble byte(first byte to transmit for communication sync).
 * @param[in] tx_data : Data to transmit.
 * @param[in] tx_data_len : @b tx_data length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - @b tx_data_len greater then maximum value.
 * See #err_t definition for detailed explanation.
 * @note Thins fucntion limits you to 62 bytes to transmit due to @b ismtx_transmit_raw_data limition.
 */
err_t ismtx_transmit_data ( ismtx_t *ctx, uint8_t preamble_byte, uint8_t *tx_data, uint8_t tx_data_len );

#ifdef __cplusplus
}
#endif
#endif // ISMTX_H

/*! @} */ // ismtx

// ------------------------------------------------------------------------ END
