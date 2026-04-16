/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file solidswitch7.h
 * @brief This file contains API for SolidSwitch 7 Click Driver.
 */

#ifndef SOLIDSWITCH7_H
#define SOLIDSWITCH7_H

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
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup solidswitch7 SolidSwitch 7 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 7 Click driver.
 * @{
 */

/**
 * @defgroup solidswitch7_set SolidSwitch 7 Settings
 * @brief Settings of SolidSwitch 7 Click driver.
 */

/**
 * @addtogroup solidswitch7_set
 * @{
 */

/**
 * @brief SolidSwitch 7 current measurement calculation values.
 * @details Specified current measurement calculation values of SolidSwitch 7 Click driver.
 */
#define SOLIDSWITCH7_RS1_KOHM           3.0
#define SOLIDSWITCH7_RS2_KOHM           10.0
#define SOLIDSWITCH7_RS_SEL             SOLIDSWITCH7_RS2_KOHM
#define SOLIDSWITCH7_CURRENT_SCALE      10.0

/**
 * @brief SolidSwitch 7 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of SolidSwitch 7 Click driver.
 */
#define SOLIDSWITCH7_NUM_CONVERSIONS    200

/**
 * @brief SolidSwitch 7 ADC setting.
 * @details Specified settings for ADC of SolidSwitch 7 Click driver.
 */
#define SOLIDSWITCH7_ADC_RESOLUTION     0x0FFF
#define SOLIDSWITCH7_VREF_3V3           3.3
#define SOLIDSWITCH7_VREF_5V            5.0
#define SOLIDSWITCH7_VREF               SOLIDSWITCH7_VREF_3V3

/**
 * @brief SolidSwitch 7 timeout setting.
 * @details Specified setting for timeout of SolidSwitch 7 Click driver.
 */
#define SOLIDSWITCH7_TIMEOUT_MS         2000

/**
 * @brief SolidSwitch 7 device address setting.
 * @details Specified setting for device slave address selection of
 * SolidSwitch 7 Click driver.
 */
#define SOLIDSWITCH7_SET_DEV_ADDR       0x4D

/*! @} */ // solidswitch7_set

/**
 * @defgroup solidswitch7_map SolidSwitch 7 MikroBUS Map
 * @brief MikroBUS pin mapping of SolidSwitch 7 Click driver.
 */

/**
 * @addtogroup solidswitch7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SolidSwitch 7 Click to the selected MikroBUS.
 */
#define SOLIDSWITCH7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.in0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sen = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt_rst = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solidswitch7_map
/*! @} */ // solidswitch7

/**
 * @brief SolidSwitch 7 Click driver selector.
 * @details Selects target driver interface of SolidSwitch 7 Click driver.
 */
typedef enum
{
    SOLIDSWITCH7_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    SOLIDSWITCH7_DRV_SEL_I2C        /**< I2C driver descriptor. */

} solidswitch7_drv_t;

/**
 * @brief SolidSwitch 7 Click context object.
 * @details Context object definition of SolidSwitch 7 Click driver.
 */
typedef struct
{
    digital_out_t in0;                  /**< Output switch state control pin. */
    digital_out_t sen;                  /**< Analog diagonstic enable pin (active high). */
    digital_out_t flt_rst;              /**< Automatic fault reset enable pin (active low). */

    analog_in_t  adc;                   /**< ADC module object. */
    i2c_master_t i2c;                   /**< I2C driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    float        vref;                  /**< ADC reference voltage. */
    solidswitch7_drv_t drv_sel;         /**< Master driver interface selector. */

} solidswitch7_t;

/**
 * @brief SolidSwitch 7 Click configuration object.
 * @details Configuration object definition of SolidSwitch 7 Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t in0;                     /**< Output switch state control pin. */
    pin_name_t sen;                     /**< Analog diagonstic enable pin (active high). */
    pin_name_t flt_rst;                 /**< Automatic fault reset enable pin (active low). */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;   /**< I2C serial speed. */
    uint8_t                i2c_address; /**< I2C slave address. */
    
    solidswitch7_drv_t drv_sel;         /**< Master driver interface selector. */

} solidswitch7_cfg_t;

/**
 * @brief SolidSwitch 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLIDSWITCH7_OK = 0,
    SOLIDSWITCH7_ERROR = -1

} solidswitch7_return_value_t;

/*!
 * @addtogroup solidswitch7 SolidSwitch 7 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 7 Click driver.
 * @{
 */

/**
 * @brief SolidSwitch 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solidswitch7_cfg_setup ( solidswitch7_cfg_t *cfg );

/**
 * @brief SolidSwitch 7 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch7_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #solidswitch7_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void solidswitch7_drv_interface_sel ( solidswitch7_cfg_t *cfg, solidswitch7_drv_t drv_sel );

/**
 * @brief SolidSwitch 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solidswitch7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch7_init ( solidswitch7_t *ctx, solidswitch7_cfg_t *cfg );

/**
 * @brief SolidSwitch 7 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch7_read_raw_adc ( solidswitch7_t *ctx, uint16_t *raw_adc );

/**
 * @brief SolidSwitch 7 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t solidswitch7_read_voltage ( solidswitch7_t *ctx, float *voltage );

/**
 * @brief SolidSwitch 7 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t solidswitch7_read_voltage_avg ( solidswitch7_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief SolidSwitch 7 set vref function.
 * @details This function sets the voltage reference for SolidSwitch 7 Click driver.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b solidswitch7_init is 3.3V.
 */
err_t solidswitch7_set_vref ( solidswitch7_t *ctx, float vref );

/**
 * @brief SolidSwitch 7 enable output function.
 * @details This function sets the IN0 pin to high logic level to enable the output stage.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch7_output_enable ( solidswitch7_t *ctx );

/**
 * @brief SolidSwitch 7 disable output function.
 * @details This function sets the IN0 pin to low logic level to disable the output stage.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch7_output_disable ( solidswitch7_t *ctx );

/**
 * @brief SolidSwitch 7 enable analog diagnostic function.
 * @details This function sets the SEN pin to high logic level to enable the analog diagnostic output.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch7_an_diag_enable ( solidswitch7_t *ctx );

/**
 * @brief SolidSwitch 7 disable analog diagnostic function.
 * @details This function sets the SEN pin to low logic level to disable the analog diagnostic output.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch7_an_diag_disable ( solidswitch7_t *ctx );

/**
 * @brief SolidSwitch 7 enable automatic fault reset function.
 * @details This function sets the FLT_RST pin to low logic level to enable automatic fault reset.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch7_auto_rst_enable ( solidswitch7_t *ctx );

/**
 * @brief SolidSwitch 7 disable automatic fault reset function.
 * @details This function sets the FLT_RST pin to high logic level to disable automatic fault reset.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch7_auto_rst_disable ( solidswitch7_t *ctx );

/**
 * @brief SolidSwitch 7 read load current function.
 * @details This function reads the analog voltage from the diagnostic output and calculates the load current.
 * @param[in] ctx : Click context object.
 * See #solidswitch7_t object definition for detailed explanation.
 * @param[out] current : Pointer to float variable where current value in amperes will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note This function relies on SOLIDSWITCH7_RS_SEL and SOLIDSWITCH7_VREF settings.
 */
err_t solidswitch7_read_current ( solidswitch7_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // SOLIDSWITCH7_H

/*! @} */ // solidswitch7

// ------------------------------------------------------------------------ END
