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
 * @file vcpmonitor5.h
 * @brief This file contains API for VCP Monitor 5 Click Driver.
 */

#ifndef VCPMONITOR5_H
#define VCPMONITOR5_H

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
 * @addtogroup vcpmonitor5 VCP Monitor 5 Click Driver
 * @brief API for configuring and manipulating VCP Monitor 5 Click driver.
 * @{
 */

/**
 * @defgroup vcpmonitor5_reg VCP Monitor 5 Registers List
 * @brief List of registers of VCP Monitor 5 Click driver.
 */

/**
 * @addtogroup vcpmonitor5_reg
 * @{
 */

/**
 * @brief VCP Monitor 5 description register.
 * @details Specified register for description of VCP Monitor 5 Click driver.
 */
#define VCPMONITOR5_REG_CONFIG                0x00
#define VCPMONITOR5_REG_ADC_CONFIG            0x01
#define VCPMONITOR5_REG_VBUS                  0x05
#define VCPMONITOR5_REG_DIETEMP               0x06
#define VCPMONITOR5_REG_CURRENT               0x07
#define VCPMONITOR5_REG_POWER                 0x08
#define VCPMONITOR5_REG_ENERGY                0x09
#define VCPMONITOR5_REG_CHARGE                0x0A
#define VCPMONITOR5_REG_ALERT_DIAG            0x0B
#define VCPMONITOR5_REG_COL                   0x0C
#define VCPMONITOR5_REG_CUL                   0x0D
#define VCPMONITOR5_REG_BOVL                  0x0E
#define VCPMONITOR5_REG_BUVL                  0x0F
#define VCPMONITOR5_REG_TEMP_LIMIT            0x10
#define VCPMONITOR5_REG_PWR_LIMIT             0x11
#define VCPMONITOR5_REG_MANUFACTURER_ID       0x3E

/*! @} */ // vcpmonitor5_reg

/**
 * @defgroup vcpmonitor5_set VCP Monitor 5 Registers Settings
 * @brief Settings for registers of VCP Monitor 5 Click driver.
 */

/**
 * @addtogroup vcpmonitor5_set
 * @{
 */

/**
 * @brief VCP Monitor 5 configuration register setting.
 * @details Configuration register setting for description of VCP Monitor 5 Click driver.
 */
#define VCPMONITOR5_CFG_RST                    0x80
#define VCPMONITOR5_CFG_RSTACC                 0x40
#define VCPMONITOR5_CFG_CONVDLY                0x01FEu

/**
 * @brief VCP Monitor 5 ADC configuration register setting.
 * @details ADC configuration register setting for description of VCP Monitor 5 Click driver.
 */
#define VCPMONITOR5_ADC_CFG_MODE_SHD          0x00
#define VCPMONITOR5_ADC_CFG_MODE_TRG_BV       0x01
#define VCPMONITOR5_ADC_CFG_MODE_TRG_T        0x04
#define VCPMONITOR5_ADC_CFG_MODE_TRG_BV_T     0x05
#define VCPMONITOR5_ADC_CFG_MODE_TRG_T_C      0x06
#define VCPMONITOR5_ADC_CFG_MODE_TRG_ALL      0x07
#define VCPMONITOR5_ADC_CFG_MODE_SD           0x08
#define VCPMONITOR5_ADC_CFG_MODE_CNT_BV       0x09
#define VCPMONITOR5_ADC_CFG_MODE_CNT_T        0x0C
#define VCPMONITOR5_ADC_CFG_MODE_CNT_BV_T     0x0D
#define VCPMONITOR5_ADC_CFG_MODE_CNT_T_C      0x0E
#define VCPMONITOR5_ADC_CFG_MODE_CNT_ALL      0x0F
#define VCPMONITOR5_ADC_CFG_MODE_BITMASK      0x0FFFu
#define VCPMONITOR5_ADC_CFG_VBSTA             0x07
#define VCPMONITOR5_ADC_CFG_VBSTA_BITMASK     0xF007u
#define VCPMONITOR5_ADC_CFG_AVG               0x07
#define VCPMONITOR5_ADC_CFG_AVG_BITMASK       0xFFF8u

/**
 * @brief VCP Monitor 5 diagnostic flags and aler register setting.
 * @details Diagnostic flags and aler register setting for description of VCP Monitor 5 Click driver.
 */
#define VCPMONITOR5_ALR_DIAG_TRANSPARENT      0x0000u
#define VCPMONITOR5_ALR_DIAG_ALATCH           0x8000u
#define VCPMONITOR5_ALR_DIAG_CNVR_DIS         0x0000u
#define VCPMONITOR5_ALR_DIAG_CNVR_EN          0x4000u
#define VCPMONITOR5_ALR_DIAG_SLWALR_NAVG      0x0000u
#define VCPMONITOR5_ALR_DIAG_SLWALR_AVG       0x2000u
#define VCPMONITOR5_ALR_DIAG_APOL_NORMAL      0x0000u
#define VCPMONITOR5_ALR_DIAG_APOL_INV         0x1000u
#define VCPMONITOR5_ALR_DIAG_W_BITMASK        0xF000u
#define VCPMONITOR5_ALR_DIAG_ENERGYOF         0x0800u
#define VCPMONITOR5_ALR_DIAG_CHARGEOF         0x0400u
#define VCPMONITOR5_ALR_DIAG_MATHOF           0x0200u
#define VCPMONITOR5_ALR_DIAG_TMPOL            0x0080u
#define VCPMONITOR5_ALR_DIAG_CURRENTOL        0x0040u
#define VCPMONITOR5_ALR_DIAG_CURRENTUL        0x0020u
#define VCPMONITOR5_ALR_DIAG_BUSOL            0x0010u
#define VCPMONITOR5_ALR_DIAG_BUSUL            0x0008u
#define VCPMONITOR5_ALR_DIAG_POL              0x0004u
#define VCPMONITOR5_ALR_DIAG_CNVRF            0x0002u
#define VCPMONITOR5_ALR_DIAG_MEMSTAT          0x0001u
#define VCPMONITOR5_ALR_DIAG_R_BITMASK        0x0FFFu

/**
 * @brief VCP Monitor 5 device manufacturer ID data value.
 * @details Device manufacturer ID data value of VCP Monitor 5 Click driver.
 */
#define VCPMONITOR5_MANUFACTURER_ID           0x5449u

/**
 * @brief VCP Monitor 5 measurement calculation data values.
 * @details Measurement calculation data values of VCP Monitor 5 Click driver.
 */
#define VCPMONITOR5_CONV_FACT_VBUS            3.125f
#define VCPMONITOR5_CONV_FACT_DIETEMP         125.0f
#define VCPMONITOR5_CONV_FACT_CURRENT         480.0f
#define VCPMONITOR5_CONV_FACT_POWER           96.0f
#define VCPMONITOR5_CONV_FACT_ENERGY          1.536f
#define VCPMONITOR5_CONV_FACT_CHARGE          30.0f
#define VCPMONITOR5_CALC_EN_CHRG_RES          256.0f
#define VCPMONITOR5_CALC_EN_CHRG              4.0f
#define VCPMONITOR5_UN_CONV_1K                1000.0f
#define VCPMONITOR5_UN_CONV_1M                1000000.0f

/**
 * @brief VCP Monitor 5 device address setting.
 * @details Specified setting for device slave address selection of
 * VCP Monitor 5 Click driver.
 */
#define VCPMONITOR5_DEVICE_ADDRESS_GND        0x44
#define VCPMONITOR5_DEVICE_ADDRESS_VCC        0x45
#define VCPMONITOR5_DEVICE_ADDRESS_SDA        0x46
#define VCPMONITOR5_DEVICE_ADDRESS_SCL        0x47

/*! @} */ // vcpmonitor5_set

/**
 * @defgroup vcpmonitor5_map VCP Monitor 5 MikroBUS Map
 * @brief MikroBUS pin mapping of VCP Monitor 5 Click driver.
 */

/**
 * @addtogroup vcpmonitor5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of VCP Monitor 5 Click to the selected MikroBUS.
 */
#define VCPMONITOR5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // vcpmonitor5_map
/*! @} */ // vcpmonitor5

/**
 * @brief VCP Monitor 5 Click context object.
 * @details Context object definition of VCP Monitor 5 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alr;         /**< Alert pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} vcpmonitor5_t;

/**
 * @brief VCP Monitor 5 Click configuration object.
 * @details Configuration object definition of VCP Monitor 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alr;            /**< Alert pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} vcpmonitor5_cfg_t;

/**
 * @brief VCP Monitor 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VCPMONITOR5_OK = 0,
    VCPMONITOR5_ERROR = -1

} vcpmonitor5_return_value_t;

/*!
 * @addtogroup vcpmonitor5 VCP Monitor 5 Click Driver
 * @brief API for configuring and manipulating VCP Monitor 5 Click driver.
 * @{
 */

/**
 * @brief VCP Monitor 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vcpmonitor5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vcpmonitor5_cfg_setup ( vcpmonitor5_cfg_t *cfg );

/**
 * @brief VCP Monitor 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vcpmonitor5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_init ( vcpmonitor5_t *ctx, vcpmonitor5_cfg_t *cfg );

/**
 * @brief VCP Monitor 5 default configuration function.
 * @details This function executes a default configuration of VCP Monitor 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t vcpmonitor5_default_cfg ( vcpmonitor5_t *ctx );

/**
 * @brief VCP Monitor 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_generic_write ( vcpmonitor5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief VCP Monitor 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_generic_read ( vcpmonitor5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief VCP Monitor 5 register writing function.
 * @details This function writes a 16-bit data to the selected register 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_reg_write ( vcpmonitor5_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief VCP Monitor 5 register reading function.
 * @details This function reads a  16-bit data from the selected register 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_reg_read ( vcpmonitor5_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief VCP Monitor 5 SW reset writing function.
 * @details This function resets all registers to default values
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_sw_reset ( vcpmonitor5_t *ctx );

/**
 * @brief VCP Monitor 5 set conversion delay function.
 * @details This function sets the delay for initial ADC conversion in steps of 2 ms
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] dly_ms : Conversion delay [0-510ms].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_set_conv_dly ( vcpmonitor5_t *ctx, uint16_t dly_ms );

/**
 * @brief VCP Monitor 5 set the operating mode function.
 * @details This function sets the desired operating mode 
 * for continuous or triggered mode on bus voltage, current or temperature measurement
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] op_mode : Operating mode [0x00-0x0F].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_set_op_mode ( vcpmonitor5_t *ctx, uint8_t op_mode );

/**
 * @brief VCP Monitor 5 set the conversion time function.
 * @details This function sets the desired conversion times
 * of the bus voltage, shunt resistor voltage and temperature measurement
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] vbusct : Conversion time of the bus voltage measurement [0x00-0x07].
 * @param[in] vsenct : Conversion time of the shunt resistor voltage [0x00-0x07].
 * @param[in] tct : Conversion time of the temperature measurement [0x00-0x07].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_set_conv_time ( vcpmonitor5_t *ctx, uint8_t vbusct, uint8_t vsenct, uint8_t tct );

/**
 * @brief VCP Monitor 5 set the ADC sample function.
 * @details This function sets the desired ADC sample averaging count to all active inputs
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] avg : ADC sample averaging count [0x00-0x07].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_set_adc_avg ( vcpmonitor5_t *ctx, uint8_t avg );

/**
 * @brief VCP Monitor 5 get the voltage function.
 * @details This function reads the BUS voltage output measurement in volts [V]
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[out] voltage : BUS voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_get_bus_voltage ( vcpmonitor5_t *ctx, float *voltage );

/**
 * @brief VCP Monitor 5 get the temperature function.
 * @details This function reads the internal die temperature measurement in degree Celsius [degC]
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[out] temperature : Internal die temperature measurement [degC].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_get_temperature ( vcpmonitor5_t *ctx, float *temperature );

/**
 * @brief VCP Monitor 5 get the current function.
 * @details This function reads the current measurement result in milliamperes [mA]
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[out] current : Current [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_get_current ( vcpmonitor5_t *ctx, float *current );

/**
 * @brief VCP Monitor 5 get the power function.
 * @details This function reads the power measurement result in watts [W]
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[out] power : Power [W].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_get_power ( vcpmonitor5_t *ctx, float *power );

/**
 * @brief VCP Monitor 5 get the energy function.
 * @details This function reads the energy measurement result in kilojoules [kJ]
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[out] energy : Energy [kJ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_get_energy ( vcpmonitor5_t *ctx, float *energy );

/**
 * @brief VCP Monitor 5 get the charge function.
 * @details This function reads the charge measurement result in Coulombs [C]
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[out] charge : Energy [C].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_get_charge ( vcpmonitor5_t *ctx, float *charge );

/**
 * @brief VCP Monitor 5 set diagnostic function.
 * @details This function sets the diagnostic flags and alert
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[in] diag_flg_alr : Diagnostic flags and alert bitmask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_set_diag_flg_alr ( vcpmonitor5_t *ctx, uint16_t diag_flg_alr );

/**
 * @brief VCP Monitor 5 get diagnostic indicates function.
 * @details This function indicates health flags of the measurements 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[out] indc_flg : Health flags indicator.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_get_indc_flg ( vcpmonitor5_t *ctx, uint16_t *indc_flg );

/**
 * @brief VCP Monitor 5 wait conversion function.
 * @details This function waits until the conversion is completed
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_wait_conv_cmpl ( vcpmonitor5_t *ctx );

/**
 * @brief VCP Monitor 5 get device ID function.
 * @details This function reads the Manufacturer ID register
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @param[out] man_id : Manufacturer ID [0x5449].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor5_get_device_id ( vcpmonitor5_t *ctx, uint16_t *man_id );

/**
 * @brief VCP Monitor 5 get alarm function.
 * @details This function get states of the ALR [INT] pin.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor5_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t vcpmonitor5_get_alarm ( vcpmonitor5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VCPMONITOR5_H

/*! @} */ // vcpmonitor5

// ------------------------------------------------------------------------ END
