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
 * @file buckboost4.h
 * @brief This file contains API for Buck-Boost 4 Click Driver.
 */

#ifndef BUCKBOOST4_H
#define BUCKBOOST4_H

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
 * @addtogroup buckboost4 Buck-Boost 4 Click Driver
 * @brief API for configuring and manipulating Buck-Boost 4 Click driver.
 * @{
 */

/**
 * @defgroup buckboost4_reg Buck-Boost 4 Registers List
 * @brief List of registers of Buck-Boost 4 Click driver.
 */

/**
 * @addtogroup buckboost4_reg
 * @{
 */

/**
 * @brief Buck-Boost 4 description register.
 * @details Specified register for description of Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_REG_REF_MSB                   0x00
#define BUCKBOOST4_REG_REF_LSB                   0x01
#define BUCKBOOST4_REG_IOUT_LIMIT                0x02
#define BUCKBOOST4_REG_VOUT_SR                   0x03
#define BUCKBOOST4_REG_VOUT_FS                   0x04
#define BUCKBOOST4_REG_CDC                       0x05
#define BUCKBOOST4_REG_MODE                      0x06
#define BUCKBOOST4_REG_STATUS                    0x07

/*! @} */ // buckboost4_reg

/**
 * @defgroup buckboost4_set Buck-Boost 4 Registers Settings
 * @brief Settings for registers of Buck-Boost 4 Click driver.
 */

/**
 * @addtogroup buckboost4_set
 * @{
 */

/**
 * @brief Buck-Boost 4 internal reference voltage data values.
 * @details Internal reference voltage data values of Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_VREF_MV_MIN                   45.0f
#define BUCKBOOST4_VREF_MV_MAX                   1200.0f
#define BUCKBOOST4_VREF_MV_STEP                  0.5645f

/**
 * @brief Buck-Boost 4 current limit target voltage data values.
 * @details Current limit target voltage data values of Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_IOUT_LIMIT_CT_DIS             0x00
#define BUCKBOOST4_IOUT_LIMIT_CT_EN              0x01
#define BUCKBOOST4_IOUT_LIMIT_CLTV_MIN           0.0f
#define BUCKBOOST4_IOUT_LIMIT_CLTV_MAX           63.5f
#define BUCKBOOST4_IOUT_LIMIT_CLTV_STEP          0.5f

/**
 * @brief Buck-Boost 4 overcurrent response time data values.
 * @details Overcurrent response time data values of Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_VOUT_SR_OCP_DELAY_128_US      0x00
#define BUCKBOOST4_VOUT_SR_OCP_DELAY_3_S         0x01
#define BUCKBOOST4_VOUT_SR_OCP_DELAY_6_S         0x02
#define BUCKBOOST4_VOUT_SR_OCP_DELAY_12_S        0x03
#define BUCKBOOST4_VOUT_SR_OCP_DELAY_BIT_MASK    0xCF

/**
 * @brief Buck-Boost 4 slew rate for output voltage change data values.
 * @details Slew rate for output voltage change data values of Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_VOUT_SR_SR_MV_US_1_25         0x00
#define BUCKBOOST4_VOUT_SR_SR_MV_US_2_5          0x01
#define BUCKBOOST4_VOUT_SR_SR_MV_US_5            0x02
#define BUCKBOOST4_VOUT_SR_SR_MV_US_10           0x03
#define BUCKBOOST4_VOUT_SR_SR_BIT_MASK           0xFC

/**
 * @brief Buck-Boost 4 output feedback voltage and ratio data values.
 * @details Output feedback voltage and ratio data values of Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_VOUT_FS_FB_EXT                0x80
#define BUCKBOOST4_VOUT_FS_INTFB_0_2256          0x00
#define BUCKBOOST4_VOUT_FS_INTFB_0_1128          0x01
#define BUCKBOOST4_VOUT_FS_INTFB_0_0752          0x02
#define BUCKBOOST4_VOUT_FS_INTFB_0_0564          0x03
#define BUCKBOOST4_VOUT_FS_INTFB_BIT_MASK        0xFC

/**
 * @brief Buck-Boost 4 mode configuration data values.
 * @details Mode configuration data values of Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_MODE_OE_EN                    0x80
#define BUCKBOOST4_MODE_FSWDBL_DIS               0x00
#define BUCKBOOST4_MODE_FSWDBL_EN                0x01
#define BUCKBOOST4_MODE_HICCUP_DIS               0x00
#define BUCKBOOST4_MODE_HICCUP_EN                0x01
#define BUCKBOOST4_MODE_DISCHG_DIS               0x00
#define BUCKBOOST4_MODE_DISCHG_EN                0x01
#define BUCKBOOST4_MODE_FPWM_DIS                 0x00
#define BUCKBOOST4_MODE_FPWM_EN                  0x01
#define BUCKBOOST4_MODE_BIT_MASK                 0x8D

/**
 * @brief Buck-Boost 4 output voltage limits data values.
 * @details Output voltage limits data values of Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_VOUT_LIM_MIN                  0.8f
#define BUCKBOOST4_VOUT_LIM_5_V                  5.0f
#define BUCKBOOST4_VOUT_LIM_10_V                 10.0f
#define BUCKBOOST4_VOUT_LIM_15_V                 15.0f
#define BUCKBOOST4_VOUT_LIM_20_V                 20.0f
#define BUCKBOOST4_VOUT_LIM_MAX                  21.286f
#define BUCKBOOST4_INTFB_STEP_MAX                0.2256f
#define BUCKBOOST4_CONVERT_V_TO_MV               1000.0f

/**
 * @brief Buck-Boost 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Buck-Boost 4 Click driver.
 */
#define BUCKBOOST4_DEVICE_ADDRESS_0              0x75
#define BUCKBOOST4_DEVICE_ADDRESS_1              0x74

/*! @} */ // buckboost4_set

/**
 * @defgroup buckboost4_map Buck-Boost 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck-Boost 4 Click driver.
 */

/**
 * @addtogroup buckboost4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck-Boost 4 Click to the selected MikroBUS.
 */
#define BUCKBOOST4_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buckboost4_map
/*! @} */ // buckboost4

/**
 * @brief Buck-Boost 4 Click context object.
 * @details Context object definition of Buck-Boost 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;        /**< Enable the device pin. */

    // Input pins
    digital_in_t int_pin;    /**< Fault indicator pin. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} buckboost4_t;

/**
 * @brief Buck-Boost 4 Click configuration object.
 * @details Configuration object definition of Buck-Boost 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;         /**< Enable the device pin. */
    pin_name_t int_pin;    /**< Fault indicator pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} buckboost4_cfg_t;

/**
 * @brief Buck-Boost 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCKBOOST4_OK = 0,
    BUCKBOOST4_ERROR = -1

} buckboost4_return_value_t;

/*!
 * @addtogroup buckboost4 Buck-Boost 4 Click Driver
 * @brief API for configuring and manipulating Buck-Boost 4 Click driver.
 * @{
 */

/**
 * @brief Buck-Boost 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buckboost4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buckboost4_cfg_setup ( buckboost4_cfg_t *cfg );

/**
 * @brief Buck-Boost 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buckboost4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_init ( buckboost4_t *ctx, buckboost4_cfg_t *cfg );

/**
 * @brief Buck-Boost 4 default configuration function.
 * @details This function executes a default configuration of Buck-Boost 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t buckboost4_default_cfg ( buckboost4_t *ctx );

/**
 * @brief Buck-Boost 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_generic_write ( buckboost4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Buck-Boost 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_generic_read ( buckboost4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Buck-Boost 4 enable the device function.
 * @details This function is used to enable 
 * the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @return Nothing.
 */
void buckboost4_enable_device ( buckboost4_t *ctx );

/**
 * @brief Buck-Boost 4 disable the device function.
 * @details This function is used to disable 
 * the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @return Nothing.
 */
void buckboost4_disable_device ( buckboost4_t *ctx );

/**
 * @brief Buck-Boost 4 set internal reference voltage function.
 * @details This function sets the internal reference voltage
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] vref_mv : Internal reference voltage [45mV-1200mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_set_vref ( buckboost4_t *ctx, float vref_mv );

/**
 * @brief Buck-Boost 4 current limit config function.
 * @details This function configures the current limit
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] cl_en : Disable or enable current limit [0-1].
 * @param[in] cltv_mv : Current limit target voltage between the ISP and ISN [0mV- 63.5mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_current_limit_cfg ( buckboost4_t *ctx, uint8_t cl_en, float cltv_mv );

/**
 * @brief Buck-Boost 4 sets the output overcurrent response time function.
 * @details This function sets the response time of the device 
 * when the output overcurrent limit is reached
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] ocp_delay : Output overcurrent limit delay [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_set_ocp_delay ( buckboost4_t *ctx, uint8_t ocp_delay );

/**
 * @brief Buck-Boost 4 sets the slew rate for output voltage change function.
 * @details This function sets the slew rate for output voltage change
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] ocp_delay : Slew rate for output voltage change [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_set_slew_rate ( buckboost4_t *ctx, uint8_t slew_rate );

/**
 * @brief Buck-Boost 4 enable external output voltage feedback function.
 * @details This function is used to enable external output voltage feedback
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_en_ext_output_vtg ( buckboost4_t *ctx );

/**
 * @brief Buck-Boost 4 set the internal feedback ratio function.
 * @details This function sets the internal feedback ratio
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] int_fb_ratio : Internal feedback ratio [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_set_int_fb_ratio ( buckboost4_t *ctx, uint8_t int_fb_ratio );

/**
 * @brief Buck-Boost 4 enable output voltage function.
 * @details This function enables the output voltage
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_output_enable ( buckboost4_t *ctx );

/**
 * @brief Buck-Boost 4 disable output voltage function.
 * @details This function disables the output voltage
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_output_disable ( buckboost4_t *ctx );

/**
 * @brief Buck-Boost 4 set mode function.
 * @details This function configures the mode
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] fswdbl : Switching frequency doubling in buck-boost mode [0-1].
 * @param[in] hiccup : Hiccup mode [0-1].
 * @param[in] dischg : Output discharge [0-1].
 * @param[in] fpwm : Select operating mode at light load condition [0-1].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_set_mode ( buckboost4_t *ctx, uint8_t fswdbl, uint8_t hiccup, 
                                               uint8_t dischg, uint8_t fpwm );

/**
 * @brief Buck-Boost 4 get status function.
 * @details This function reads the status data
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_get_status ( buckboost4_t *ctx, uint8_t *status );

/**
 * @brief Buck-Boost 4 set the output voltage function.
 * @details This function sets the output voltage
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @param[in] vout_v : Output voltage [0.8V-21.286V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost4_set_vout ( buckboost4_t *ctx, float vout_v );

/**
 * @brief Buck-Boost 4 check fault indicator function.
 * @details This function gets the status of the fault indicator
 * of the TPS55289, 30-V, 8-A Buck-Boost Converter with I2C Interface
 * on the Buck-Boost 4 Click board™. 
 * @param[in] ctx : Click context object.
 * See #buckboost4_t object definition for detailed explanation.
 * @return @li @c 0 - Internal fault happening,
 *         @li @c 1 - No fault.
 * @note When the device is set to use internal feedback, 
 * this pin is a fault indicator output.
 */
uint8_t buckboost4_fault_indicator ( buckboost4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUCKBOOST4_H

/*! @} */ // buckboost4

// ------------------------------------------------------------------------ END
