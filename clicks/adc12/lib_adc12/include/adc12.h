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
 * @file adc12.h
 * @brief This file contains API for ADC 12 Click Driver.
 */

#ifndef ADC12_H
#define ADC12_H

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
 * @addtogroup adc12 ADC 12 Click Driver
 * @brief API for configuring and manipulating ADC 12 Click driver.
 * @{
 */

/**
 * @defgroup adc12_cmd ADC 12 Commands List
 * @brief List of commands of ADC 12 Click driver.
 */

/**
 * @addtogroup adc12_cmd
 * @{
 */

/**
 * @brief ADC 12 commands list.
 * @details The list of command bytes.
 */
#define ADC12_CMD_SD_MASK           0x80
#define ADC12_CMD_SD_DIFF           0x00
#define ADC12_CMD_SD_SINGLE_END     0x80

#define ADC12_CMD_PD_MASK           0x0C
#define ADC12_CMD_PD_PDADCONV       0x00
#define ADC12_CMD_PD_IROFF_ADON     0x04
#define ADC12_CMD_PD_IRON_ADOFF     0x08
#define ADC12_CMD_PD_IRON_ADON      0x0C

/*! @} */ // adc12_cmd

/**
 * @defgroup adc12_set ADC 12 Registers Settings
 * @brief Settings for registers of ADC 12 Click driver.
 */

/**
 * @addtogroup adc12_set
 * @{
 */

/**
 * @brief ADC 12 Single-Ended channels selection.
 * @details Single-Ended channels selection values.
 */
#define ADC12_SINGLE_END_CH0         0
#define ADC12_SINGLE_END_CH1         1
#define ADC12_SINGLE_END_CH2         2
#define ADC12_SINGLE_END_CH3         3
#define ADC12_SINGLE_END_CH4         4
#define ADC12_SINGLE_END_CH5         5
#define ADC12_SINGLE_END_CH6         6
#define ADC12_SINGLE_END_CH7         7

/**
 * @brief ADC 12 Differential channels selection.
 * @details Differential channels selection values.
 */
#define ADC12_DIFF_CH0_P_CH1_N       0
#define ADC12_DIFF_CH1_P_CH0_N       1
#define ADC12_DIFF_CH2_P_CH3_N       2
#define ADC12_DIFF_CH3_P_CH2_N       3
#define ADC12_DIFF_CH4_P_CH5_N       4
#define ADC12_DIFF_CH5_P_CH4_N       5
#define ADC12_DIFF_CH6_P_CH7_N       6
#define ADC12_DIFF_CH7_P_CH6_N       7

/**
 * @brief ADC 12 Internal Reference value.
 * @details Internal Reference value.
 */
#define ADC12_INTERNAL_VREF          2500

/**
 * @brief ADC 12 ADC Resolution value.
 * @details ADC Resolution value.
 */
#define ADC12_RES                    4096.0

/**
 * @brief ADC 12 device address setting.
 * @details Specified setting for device slave address selection of
 * ADC 12 Click driver.
 */
#define ADC12_DEV_ADDR_DEFAULT        0x48
#define ADC12_DEV_ADDR_01             0x49
#define ADC12_DEV_ADDR_10             0x4A
#define ADC12_DEV_ADDR_11             0x4B

/*! @} */ // adc12_set

/**
 * @defgroup adc12_map ADC 12 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 12 Click driver.
 */

/**
 * @addtogroup adc12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 12 Click to the selected MikroBUS.
 */
#define ADC12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // adc12_map
/*! @} */ // adc12

/**
 * @brief ADC 12 Click context object.
 * @details Context object definition of ADC 12 Click driver.
 */
typedef struct
{
    // Modules

    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */
    
    uint8_t adc12_sd_mode;   /**< Single-Ended/Differential Inputs selection */
    uint8_t adc12_pd_mode;   /**< Power-Down mode */

} adc12_t;

/**
 * @brief ADC 12 Click configuration object.
 * @details Configuration object definition of ADC 12 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} adc12_cfg_t;

/**
 * @brief ADC 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC12_OK = 0,
    ADC12_ERROR = -1

} adc12_return_value_t;

/*!
 * @addtogroup adc12 ADC 12 Click Driver
 * @brief API for configuring and manipulating ADC 12 Click driver.
 * @{
 */

/**
 * @brief ADC 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void adc12_cfg_setup ( adc12_cfg_t *cfg );

/**
 * @brief ADC 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t adc12_init ( adc12_t *ctx, adc12_cfg_t *cfg );

/**
 * @brief ADC 12 send command function.
 * @details This function sends a desired command byte to the Click board via I2C serial interface. 
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @param[in] cmd_byte : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t adc12_send_cmd ( adc12_t *ctx, uint8_t cmd_byte );

/**
 * @brief ADC 12 read data function.
 * @details This function reads two bytes of data from the Click board via I2C serial interface. 
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @param[out] data_out : Read data output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t adc12_read_data ( adc12_t *ctx, uint16_t *data_out );

/**
 * @brief ADC 12 set the Single-Ended/Differential Inputs function.
 * @details This function sets the input mode.
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @param[in] sd_mode : Value that defines input mode.
 * @return None.
 * @note None.
 *
 * @endcode
 */
void adc12_set_sd_mode ( adc12_t *ctx, uint8_t sd_mode );

/**
 * @brief ADC 12 get the Single-Ended/Differential Inputs function.
 * @details This function returns the currently set value for the input mode.
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @return Input mode value.
 * @note None.
 *
 * @endcode
 */
uint8_t adc12_get_sd_mode ( adc12_t *ctx );

/**
 * @brief ADC 12 set the Power-Down mode function.
 * @details This function sets the power-down mode.
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @param[in] pd_mode : Value that defines power-down mode.
 * @return None.
 * @note None.
 *
 * @endcode
 */
void adc12_set_pd_mode ( adc12_t *ctx, uint8_t pd_mode );

/**
 * @brief ADC 12 get the Power-Down mode function.
 * @details This function returns the currently set value for the power-down mode.
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @return Power-down mode value.
 * @note None.
 *
 * @endcode
 */
uint8_t adc12_get_pd_mode ( adc12_t *ctx );

/**
 * @brief ADC 12 read raw ADC data function.
 * @details This function reads raw 12-bit ADC data from the desired channel. 
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @param[in] ch : Value that defines the ADC channel.
 * @param[out] data_out : 12-bit RAW ADC data output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t adc12_read_raw_data ( adc12_t *ctx, uint8_t ch, uint16_t *data_out );

/**
 * @brief ADC 12 read voltage function.
 * @details This function reads the voltage in milivolts from the desired channel. 
 * @param[out] ctx : Click context object.
 * See #adc12_t object definition for detailed explanation.
 * @param[in] ch : Value that defines the ADC channel.
 * @param[in] vref : Reference voltage value.
 * @param[out] data_out : ADC voltage in milivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t adc12_read_voltage ( adc12_t *ctx, uint8_t ch, uint16_t vref, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // ADC12_H

/*! @} */ // adc12

// ------------------------------------------------------------------------ END
