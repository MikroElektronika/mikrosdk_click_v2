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
 * @file dac20.h
 * @brief This file contains API for DAC 20 Click Driver.
 */

#ifndef DAC20_H
#define DAC20_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup dac20 DAC 20 Click Driver
 * @brief API for configuring and manipulating DAC 20 Click driver.
 * @{
 */

/**
 * @defgroup dac20_reg DAC 20 Registers List
 * @brief List of registers of DAC 20 Click driver.
 */

/**
 * @addtogroup dac20_reg
 * @{
 */

/**
 * @brief DAC 20 register list.
 * @details Specified register list of DAC 20 Click driver.
 */
#define DAC20_REG_VOLATILE_DAC_WIPER_0          0x00
#define DAC20_REG_VOLATILE_DAC_WIPER_1          0x01
#define DAC20_REG_VOLATILE_VREF                 0x08
#define DAC20_REG_VOLATILE_POWER_DOWN           0x09
#define DAC20_REG_VOLATILE_GAIN_AND_STATUS      0x0A
#define DAC20_REG_GP_MTP_0                      0x0C
#define DAC20_REG_GP_MTP_1                      0x0D
#define DAC20_REG_GP_MTP_2                      0x0E
#define DAC20_REG_GP_MTP_3                      0x0F
#define DAC20_REG_NONVOLATILE_DAC_WIPER_0       0x10
#define DAC20_REG_NONVOLATILE_DAC_WIPER_1       0x11
#define DAC20_REG_NONVOLATILE_VREF              0x18
#define DAC20_REG_NONVOLATILE_POWER_DOWN        0x19
#define DAC20_REG_NONVOLATILE_GAIN_AND_ADDRESS  0x1A
#define DAC20_REG_NONVOLATILE_WIPERLOCK_TECH    0x1B
#define DAC20_REG_GP_MTP_4                      0x1C
#define DAC20_REG_GP_MTP_5                      0x1D
#define DAC20_REG_GP_MTP_6                      0x1E
#define DAC20_REG_GP_MTP_7                      0x1F

/**
 * @brief DAC 20 command settings.
 * @details Specified command settings of DAC 20 Click driver.
 */
#define DAC20_CMD_WRITE                         0x00
#define DAC20_CMD_READ                          0x06

/*! @} */ // dac20_reg

/**
 * @defgroup dac20_set DAC 20 Registers Settings
 * @brief Settings for registers of DAC 20 Click driver.
 */

/**
 * @addtogroup dac20_set
 * @{
 */

/**
 * @brief DAC 20 output channel selection.
 * @details DAC output channel selection of DAC 20 Click driver.
 */
#define DAC20_CHANNEL_NONE                      0x00
#define DAC20_CHANNEL_0                         0x01
#define DAC20_CHANNEL_1                         0x02
#define DAC20_CHANNEL_ALL                       0x03

/**
 * @brief DAC 20 VREF settings.
 * @details DAC VREF settings of DAC 20 Click driver.
 */
#define DAC20_VREF_BUFFERED                     3
#define DAC20_VREF_UNBUFFERED                   2
#define DAC20_VREF_INT_BAND_GAP                 1
#define DAC20_VREF_VDD_UNBUFFERED               0

/**
 * @brief DAC 20 power settings.
 * @details Power settings of DAC 20 Click driver.
 */
#define DAC20_PWR_PDOWN_HIZ                     3
#define DAC20_PWR_PDOWN_100K                    2
#define DAC20_PWR_PDOWN_1K                      1
#define DAC20_PWR_NORMAL_OPERATION              0

/**
 * @brief DAC 20 range values.
 * @details DAC range values of DAC 20 Click driver.
 */
#define DAC20_DAC_VALUE_MIN                     0x0000
#define DAC20_DAC_VALUE_MID                     0x07FF
#define DAC20_DAC_VALUE_MAX                     0x0FFF

/**
 * @brief DAC 20 VREF and VCC values.
 * @details DAC VREF and VCC values of DAC 20 Click driver.
 */
#define DAC20_VREF_INT_2048V                    2048
#define DAC20_VREF_INT_4096V                    4096
#define DAC20_VREF_INT                          DAC20_VREF_INT_2048V
#define DAC20_VCC_LEVEL                         3300

/**
 * @brief DAC 20 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 20 Click driver.
 */
#define DAC20_DEVICE_ADDRESS_A1A0_00            0x60
#define DAC20_DEVICE_ADDRESS_A1A0_01            0x61
#define DAC20_DEVICE_ADDRESS_A1A0_10            0x62
#define DAC20_DEVICE_ADDRESS_A1A0_11            0x63

/*! @} */ // dac20_set

/**
 * @defgroup dac20_map DAC 20 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 20 Click driver.
 */

/**
 * @addtogroup dac20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 20 Click to the selected MikroBUS.
 */
#define DAC20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.latch = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // dac20_map
/*! @} */ // dac20

/**
 * @brief DAC 20 Click context object.
 * @details Context object definition of DAC 20 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t latch;        /**< DAC wiper register latch pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} dac20_t;

/**
 * @brief DAC 20 Click configuration object.
 * @details Configuration object definition of DAC 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t latch;           /**< DAC wiper register latch pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} dac20_cfg_t;

/**
 * @brief DAC 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC20_OK = 0,
    DAC20_ERROR = -1

} dac20_return_value_t;

/*!
 * @addtogroup dac20 DAC 20 Click Driver
 * @brief API for configuring and manipulating DAC 20 Click driver.
 * @{
 */

/**
 * @brief DAC 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac20_cfg_setup ( dac20_cfg_t *cfg );

/**
 * @brief DAC 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac20_init ( dac20_t *ctx, dac20_cfg_t *cfg );

/**
 * @brief DAC 20 default configuration function.
 * @details This function executes a default configuration of DAC 20
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac20_default_cfg ( dac20_t *ctx );

/**
 * @brief DAC 20 write register function.
 * @details This function writes a 16-bit data word to the selected register address.
 * @param[in] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac20_write_reg ( dac20_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 20 read register function.
 * @details This function reads a 16-bit data word from the selected register address.
 * @param[in] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac20_read_reg ( dac20_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 20 set latch pin state function.
 * @details This function sets the latch pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @param[in] state : Logic state (0 - Low, 1 - High).
 * @return None.
 * @note None.
 */
void dac20_set_latch_pin ( dac20_t *ctx, uint8_t state );

/**
 * @brief DAC 20 set reference control function.
 * @details This function configures the reference mode for the selected DAC channels.
 * @param[in] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0, bit1 - CH1).
 * @param[in] vref : Reference mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p vref argument).
 * See #err_t definition for detailed explanation.
 * @note Multiple channels can be updated simultaneously.
 */
err_t dac20_set_vref_control ( dac20_t *ctx, uint8_t channel, uint8_t vref );

/**
 * @brief DAC 20 set power control function.
 * @details This function configures the power mode for the selected DAC channels.
 * @param[in] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0, bit1 - CH1).
 * @param[in] pwr : Power control setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p pwr argument).
 * See #err_t definition for detailed explanation.
 * @note Multiple channels can be updated simultaneously.
 */
err_t dac20_set_power_control ( dac20_t *ctx, uint8_t channel, uint8_t pwr );

/**
 * @brief DAC 20 set DAC value function.
 * @details This function writes the 12-bit DAC code value to one or more channels
 * and latches the output values by toggling the LAT pin.
 * @param[in] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0, bit1 - CH1).
 * @param[in] value : DAC code value (0 to @ref DAC20_DAC_VALUE_MAX).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p value argument).
 * See #err_t definition for detailed explanation.
 * @note After updating, the function toggles LATCH pin to apply the output.
 */
err_t dac20_set_dac_value ( dac20_t *ctx, uint8_t channel, uint16_t value );

/**
 * @brief DAC 20 set DAC voltage function.
 * @details This function sets the output voltage (in millivolts) for one or more channels
 * by converting it to a corresponding DAC code and updating the device.
 * @param[in] ctx : Click context object.
 * See #dac20_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0, bit1 - CH1).
 * @param[in] voltage_mv : Desired output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (voltage out of range).
 * See #err_t definition for detailed explanation.
 * @note The calculation is based on an DAC20_VREF_INT reference.
 */
err_t dac20_set_dac_voltage ( dac20_t *ctx, uint8_t channel, uint16_t voltage_mv );

#ifdef __cplusplus
}
#endif
#endif // DAC20_H

/*! @} */ // dac20

// ------------------------------------------------------------------------ END
