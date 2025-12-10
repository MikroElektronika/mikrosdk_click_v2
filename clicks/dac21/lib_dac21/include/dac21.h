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
 * @file dac21.h
 * @brief This file contains API for DAC 21 Click Driver.
 */

#ifndef DAC21_H
#define DAC21_H

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
 * @addtogroup dac21 DAC 21 Click Driver
 * @brief API for configuring and manipulating DAC 21 Click driver.
 * @{
 */

/**
 * @defgroup dac21_reg DAC 21 Registers List
 * @brief List of registers of DAC 21 Click driver.
 */

/**
 * @addtogroup dac21_reg
 * @{
 */

/**
 * @brief DAC 21 register list.
 * @details Specified register list of DAC 21 Click driver.
 */
#define DAC21_REG_VOLATILE_DAC_WIPER_0          0x00
#define DAC21_REG_VOLATILE_DAC_WIPER_1          0x01
#define DAC21_REG_VOLATILE_DAC_WIPER_2          0x02
#define DAC21_REG_VOLATILE_DAC_WIPER_3          0x03
#define DAC21_REG_VOLATILE_DAC_WIPER_4          0x04
#define DAC21_REG_VOLATILE_DAC_WIPER_5          0x05
#define DAC21_REG_VOLATILE_DAC_WIPER_6          0x06
#define DAC21_REG_VOLATILE_DAC_WIPER_7          0x07
#define DAC21_REG_VOLATILE_VREF                 0x08
#define DAC21_REG_VOLATILE_POWER_DOWN           0x09
#define DAC21_REG_VOLATILE_GAIN_AND_STATUS      0x0A
#define DAC21_REG_GP_MTP_0                      0x0C
#define DAC21_REG_GP_MTP_1                      0x0D
#define DAC21_REG_GP_MTP_2                      0x0E
#define DAC21_REG_GP_MTP_3                      0x0F
#define DAC21_REG_NONVOLATILE_DAC_WIPER_0       0x10
#define DAC21_REG_NONVOLATILE_DAC_WIPER_1       0x11
#define DAC21_REG_NONVOLATILE_DAC_WIPER_2       0x12
#define DAC21_REG_NONVOLATILE_DAC_WIPER_3       0x13
#define DAC21_REG_NONVOLATILE_DAC_WIPER_4       0x14
#define DAC21_REG_NONVOLATILE_DAC_WIPER_5       0x15
#define DAC21_REG_NONVOLATILE_DAC_WIPER_6       0x16
#define DAC21_REG_NONVOLATILE_DAC_WIPER_7       0x17
#define DAC21_REG_NONVOLATILE_VREF              0x18
#define DAC21_REG_NONVOLATILE_POWER_DOWN        0x19
#define DAC21_REG_NONVOLATILE_GAIN_AND_ADDRESS  0x1A
#define DAC21_REG_NONVOLATILE_WIPERLOCK_TECH    0x1B
#define DAC21_REG_GP_MTP_4                      0x1C
#define DAC21_REG_GP_MTP_5                      0x1D
#define DAC21_REG_GP_MTP_6                      0x1E
#define DAC21_REG_GP_MTP_7                      0x1F

/**
 * @brief DAC 21 command settings.
 * @details Specified command settings of DAC 21 Click driver.
 */
#define DAC21_CMD_WRITE                         0x00
#define DAC21_CMD_READ                          0x06

/*! @} */ // dac21_reg

/**
 * @defgroup dac21_set DAC 21 Registers Settings
 * @brief Settings for registers of DAC 21 Click driver.
 */

/**
 * @addtogroup dac21_set
 * @{
 */

/**
 * @brief DAC 21 output channel selection.
 * @details DAC output channel selection of DAC 21 Click driver.
 */
#define DAC21_CHANNEL_NONE                      0x00
#define DAC21_CHANNEL_0                         0x01
#define DAC21_CHANNEL_1                         0x02
#define DAC21_CHANNEL_2                         0x04
#define DAC21_CHANNEL_3                         0x08
#define DAC21_CHANNEL_4                         0x10
#define DAC21_CHANNEL_5                         0x20
#define DAC21_CHANNEL_6                         0x40
#define DAC21_CHANNEL_7                         0x80
#define DAC21_CHANNEL_ALL                       0xFF

/**
 * @brief DAC 21 VREF settings.
 * @details DAC VREF settings of DAC 21 Click driver.
 */
#define DAC21_VREF_BUFFERED                     3
#define DAC21_VREF_UNBUFFERED                   2
#define DAC21_VREF_INT_BAND_GAP                 1
#define DAC21_VREF_VDD_UNBUFFERED               0

/**
 * @brief DAC 21 power settings.
 * @details Power settings of DAC 21 Click driver.
 */
#define DAC21_PWR_PDOWN_HIZ                     3
#define DAC21_PWR_PDOWN_100K                    2
#define DAC21_PWR_PDOWN_1K                      1
#define DAC21_PWR_NORMAL_OPERATION              0

/**
 * @brief DAC 21 range values.
 * @details DAC range values of DAC 21 Click driver.
 */
#define DAC21_DAC_VALUE_MIN                     0x0000
#define DAC21_DAC_VALUE_MID                     0x07FF
#define DAC21_DAC_VALUE_MAX                     0x0FFF

/**
 * @brief DAC 21 VREF and VCC values.
 * @details DAC VREF and VCC values of DAC 21 Click driver.
 */
#define DAC21_VREF_INT_3V                       3000
#define DAC21_VCC_LEVEL                         3300

/**
 * @brief DAC 21 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 21 Click driver.
 */
#define DAC21_DEVICE_ADDRESS_A1A0_00            0x60
#define DAC21_DEVICE_ADDRESS_A1A0_01            0x61
#define DAC21_DEVICE_ADDRESS_A1A0_10            0x62
#define DAC21_DEVICE_ADDRESS_A1A0_11            0x63

/*! @} */ // dac21_set

/**
 * @defgroup dac21_map DAC 21 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 21 Click driver.
 */

/**
 * @addtogroup dac21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 21 Click to the selected MikroBUS.
 */
#define DAC21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.lt0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.lt1 = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // dac21_map
/*! @} */ // dac21

/**
 * @brief DAC 21 Click context object.
 * @details Context object definition of DAC 21 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t lt0;          /**< Latch 0 pin for even number outputs. */
    digital_out_t lt1;          /**< Latch 1 pin for odd number outputs. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} dac21_t;

/**
 * @brief DAC 21 Click configuration object.
 * @details Configuration object definition of DAC 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t lt0;             /**< Latch 0 pin for even number outputs. */
    pin_name_t lt1;             /**< Latch 1 pin for odd number outputs. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} dac21_cfg_t;

/**
 * @brief DAC 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC21_OK = 0,
    DAC21_ERROR = -1

} dac21_return_value_t;

/*!
 * @addtogroup dac21 DAC 21 Click Driver
 * @brief API for configuring and manipulating DAC 21 Click driver.
 * @{
 */

/**
 * @brief DAC 21 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac21_cfg_setup ( dac21_cfg_t *cfg );

/**
 * @brief DAC 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac21_init ( dac21_t *ctx, dac21_cfg_t *cfg );

/**
 * @brief DAC 21 default configuration function.
 * @details This function executes a default configuration of DAC 21
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac21_default_cfg ( dac21_t *ctx );

/**
 * @brief DAC 21 write register function.
 * @details This function writes a 16-bit data word to the selected register address.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac21_write_reg ( dac21_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 21 read register function.
 * @details This function reads a 16-bit data word from the selected register address.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac21_read_reg ( dac21_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 21 set LAT0 pin state function.
 * @details This function sets the LAT0 pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] state : Logic state (0 - Low, 1 - High).
 * @return None.
 * @note None.
 */
void dac21_set_lat0_pin ( dac21_t *ctx, uint8_t state );

/**
 * @brief DAC 21 set LAT1 pin state function.
 * @details This function sets the LAT1 pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] state : Logic state (0 - Low, 1 - High).
 * @return None.
 * @note None.
 */
void dac21_set_lat1_pin ( dac21_t *ctx, uint8_t state );

/**
 * @brief DAC 21 set reference control function.
 * @details This function configures the reference mode for the selected DAC channels.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0 ... bit7 - CH7).
 * @param[in] vref : Reference mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p vref argument).
 * See #err_t definition for detailed explanation.
 * @note Multiple channels can be updated simultaneously.
 */
err_t dac21_set_vref_control ( dac21_t *ctx, uint8_t channel, uint8_t vref );

/**
 * @brief DAC 21 set power control function.
 * @details This function configures the power mode for the selected DAC channels.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0 ... bit7 - CH7).
 * @param[in] pwr : Power control setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p pwr argument).
 * See #err_t definition for detailed explanation.
 * @note Multiple channels can be updated simultaneously.
 */
err_t dac21_set_power_control ( dac21_t *ctx, uint8_t channel, uint8_t pwr );

/**
 * @brief DAC 21 set DAC value function.
 * @details This function writes the 12-bit DAC code value to one or more channels
 * and latches the output values by toggling the LAT pins.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0 ... bit7 - CH7).
 * @param[in] value : DAC code value (0 to @ref DAC21_DAC_VALUE_MAX).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid @p value argument).
 * See #err_t definition for detailed explanation.
 * @note After updating, the function toggles LAT0 and LAT1 pins to apply the output.
 */
err_t dac21_set_dac_value ( dac21_t *ctx, uint8_t channel, uint16_t value );

/**
 * @brief DAC 21 set DAC voltage function.
 * @details This function sets the output voltage (in millivolts) for one or more channels
 * by converting it to a corresponding DAC code and updating the device.
 * @param[in] ctx : Click context object.
 * See #dac21_t object definition for detailed explanation.
 * @param[in] channel : Bitmask of DAC channels to be updated (bit0 - CH0 ... bit7 - CH7).
 * @param[in] voltage_mv : Desired output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (voltage out of range).
 * See #err_t definition for detailed explanation.
 * @note The calculation is based on an internal 3 V reference.
 */
err_t dac21_set_dac_voltage ( dac21_t *ctx, uint8_t channel, uint16_t voltage_mv );

#ifdef __cplusplus
}
#endif
#endif // DAC21_H

/*! @} */ // dac21

// ------------------------------------------------------------------------ END
