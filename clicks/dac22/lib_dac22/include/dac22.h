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
 * @file dac22.h
 * @brief This file contains API for DAC 22 Click Driver.
 */

#ifndef DAC22_H
#define DAC22_H

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
 * @addtogroup dac22 DAC 22 Click Driver
 * @brief API for configuring and manipulating DAC 22 Click driver.
 * @{
 */

/**
 * @defgroup dac22_reg DAC 22 Registers List
 * @brief List of registers of DAC 22 Click driver.
 */

/**
 * @addtogroup dac22_reg
 * @{
 */

/**
 * @brief DAC 22 register list.
 * @details Specified register list of DAC 22 Click driver.
 */
#define DAC22_REG_VOLATILE_DAC_WIPER_0          0x00
#define DAC22_REG_VOLATILE_DAC_WIPER_1          0x01
#define DAC22_REG_VOLATILE_VREF                 0x08
#define DAC22_REG_VOLATILE_POWER_DOWN           0x09
#define DAC22_REG_VOLATILE_GAIN_AND_STATUS      0x0A
#define DAC22_REG_GP_MTP_0                      0x0C
#define DAC22_REG_GP_MTP_1                      0x0D
#define DAC22_REG_GP_MTP_2                      0x0E
#define DAC22_REG_GP_MTP_3                      0x0F
#define DAC22_REG_NONVOLATILE_DAC_WIPER_0       0x10
#define DAC22_REG_NONVOLATILE_DAC_WIPER_1       0x11
#define DAC22_REG_NONVOLATILE_VREF              0x18
#define DAC22_REG_NONVOLATILE_POWER_DOWN        0x19
#define DAC22_REG_NONVOLATILE_GAIN              0x1A
#define DAC22_REG_NONVOLATILE_WIPERLOCK_TECH    0x1B
#define DAC22_REG_GP_MTP_4                      0x1C
#define DAC22_REG_GP_MTP_5                      0x1D
#define DAC22_REG_GP_MTP_6                      0x1E
#define DAC22_REG_GP_MTP_7                      0x1F

/**
 * @brief DAC 22 command settings.
 * @details Specified command settings of DAC 22 Click driver.
 */
#define DAC22_CMD_WRITE                         0x00
#define DAC22_CMD_READ                          0x06

/*! @} */ // dac22_reg

/**
 * @defgroup dac22_set DAC 22 Registers Settings
 * @brief Settings for registers of DAC 22 Click driver.
 */

/**
 * @addtogroup dac22_set
 * @{
 */

/**
 * @brief DAC 22 output channel selection.
 * @details DAC output channel selection of DAC 22 Click driver.
 */
#define DAC22_CHANNEL_NONE                      0x00
#define DAC22_CHANNEL_0                         0x01
#define DAC22_CHANNEL_1                         0x02
#define DAC22_CHANNEL_ALL                       0x03

/**
 * @brief DAC 22 VREF settings.
 * @details DAC VREF settings of DAC 22 Click driver.
 */
#define DAC22_VREF_BUFFERED                     3
#define DAC22_VREF_UNBUFFERED                   2
#define DAC22_VREF_INT_BAND_GAP                 1
#define DAC22_VREF_VDD_UNBUFFERED               0

/**
 * @brief DAC 22 power settings.
 * @details Power settings of DAC 22 Click driver.
 */
#define DAC22_PWR_PDOWN_HIZ                     3
#define DAC22_PWR_PDOWN_100K                    2
#define DAC22_PWR_PDOWN_1K                      1
#define DAC22_PWR_NORMAL_OPERATION              0

/**
 * @brief DAC 22 range values.
 * @details DAC range values of DAC 22 Click driver.
 */
#define DAC22_DAC_VALUE_MIN                     0x0000
#define DAC22_DAC_VALUE_MID                     0x07FF
#define DAC22_DAC_VALUE_MAX                     0x0FFF

/**
 * @brief DAC 22 VREF and VCC values.
 * @details DAC VREF and VCC values of DAC 22 Click driver.
 */
#define DAC22_VREF_INT_2048V                    2048
#define DAC22_VREF_INT_4096V                    4096
#define DAC22_VREF_INT                          DAC22_VREF_INT_2048V
#define DAC22_VCC_LEVEL                         3300

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dac22_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DAC22_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define DAC22_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dac22_set

/**
 * @defgroup dac22_map DAC 22 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 22 Click driver.
 */

/**
 * @addtogroup dac22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 22 Click to the selected MikroBUS.
 */
#define DAC22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.latch = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // dac22_map
/*! @} */ // dac22

/**
 * @brief DAC 22 Click context object.
 * @details Context object definition of DAC 22 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t latch;        /**< DAC wiper register latch pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

} dac22_t;

/**
 * @brief DAC 22 Click configuration object.
 * @details Configuration object definition of DAC 22 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t latch;           /**< DAC wiper register latch pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} dac22_cfg_t;

/**
 * @brief DAC 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC22_OK = 0,
    DAC22_ERROR = -1

} dac22_return_value_t;

/*!
 * @addtogroup dac22 DAC 22 Click Driver
 * @brief API for configuring and manipulating DAC 22 Click driver.
 * @{
 */

/**
 * @brief DAC 22 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac22_cfg_setup ( dac22_cfg_t *cfg );

/**
 * @brief DAC 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac22_init ( dac22_t *ctx, dac22_cfg_t *cfg );

/**
 * @brief DAC 22 default configuration function.
 * @details This function executes a default configuration of DAC 22
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac22_default_cfg ( dac22_t *ctx );

/**
 * @brief DAC 22 write register function.
 * @details This function writes a 16-bit data word to the selected register address.
 * @param[in] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac22_write_reg ( dac22_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 22 read register function.
 * @details This function reads a 16-bit data word from the selected register address.
 * @param[in] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac22_read_reg ( dac22_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 22 set latch pin state function.
 * @details This function sets the latch pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @param[in] state : Logic state (0 - Low, 1 - High).
 * @return None.
 * @note None.
 */
void dac22_set_latch_pin ( dac22_t *ctx, uint8_t state );

/**
 * @brief DAC 22 set reference control function.
 * @details This function configures the reference mode for the selected DAC channels.
 * @param[in] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0, bit1 - CH1).
 * @param[in] vref : Reference mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p vref argument).
 * See #err_t definition for detailed explanation.
 * @note Multiple channels can be updated simultaneously.
 */
err_t dac22_set_vref_control ( dac22_t *ctx, uint8_t channel, uint8_t vref );

/**
 * @brief DAC 22 set power control function.
 * @details This function configures the power mode for the selected DAC channels.
 * @param[in] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0, bit1 - CH1).
 * @param[in] pwr : Power control setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p pwr argument).
 * See #err_t definition for detailed explanation.
 * @note Multiple channels can be updated simultaneously.
 */
err_t dac22_set_power_control ( dac22_t *ctx, uint8_t channel, uint8_t pwr );

/**
 * @brief DAC 22 set DAC value function.
 * @details This function writes the 12-bit DAC code value to one or more channels
 * and latches the output values by toggling the LAT pin.
 * @param[in] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0, bit1 - CH1).
 * @param[in] value : DAC code value (0 to @ref DAC22_DAC_VALUE_MAX).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p value argument).
 * See #err_t definition for detailed explanation.
 * @note After updating, the function toggles LATCH pin to apply the output.
 */
err_t dac22_set_dac_value ( dac22_t *ctx, uint8_t channel, uint16_t value );

/**
 * @brief DAC 22 set DAC voltage function.
 * @details This function sets the output voltage (in millivolts) for one or more channels
 * by converting it to a corresponding DAC code and updating the device.
 * @param[in] ctx : Click context object.
 * See #dac22_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0, bit1 - CH1).
 * @param[in] voltage_mv : Desired output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (voltage out of range).
 * See #err_t definition for detailed explanation.
 * @note The calculation is based on an DAC22_VREF_INT reference.
 */
err_t dac22_set_dac_voltage ( dac22_t *ctx, uint8_t channel, uint16_t voltage_mv );

#ifdef __cplusplus
}
#endif
#endif // DAC22_H

/*! @} */ // dac22

// ------------------------------------------------------------------------ END
