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
 * @file dac18.h
 * @brief This file contains API for DAC 18 Click Driver.
 */

#ifndef DAC18_H
#define DAC18_H

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
 * @addtogroup dac18 DAC 18 Click Driver
 * @brief API for configuring and manipulating DAC 18 Click driver.
 * @{
 */

/**
 * @defgroup dac18_reg DAC 18 Registers List
 * @brief List of registers of DAC 18 Click driver.
 */

/**
 * @addtogroup dac18_reg
 * @{
 */

/**
 * @brief DAC 18 description register.
 * @details Specified register for description of DAC 18 Click driver.
 */
#define DAC18_REG_NOP                          0x00
#define DAC18_REG_DAC0_VOUT_CMP_CONFIG         0x15
#define DAC18_REG_DAC1_VOUT_CMP_CONFIG         0x03
#define DAC18_REG_COMMON_CONFIG                0x1F
#define DAC18_REG_COMMON_TRIGGER               0x20
#define DAC18_REG_FUNCTION_TRIGGER             0x21
#define DAC18_REG_GENERAL_STATUS               0x22
#define DAC18_REG_DEVICE_MODE_CONFIG           0x25
#define DAC18_REG_INTERFACE_CONFIG             0x26
#define DAC18_REG_STATE_MACHINE_CONFIG         0x27
#define DAC18_REG_SRAM_CONFIG                  0x2B
#define DAC18_REG_SRAM_DATA                    0x2C

/**
 * @brief DAC 18 description SRAM register address.
 * @details Specified SRAM register address for description of DAC 18 Click driver.
 */
#define DAC18_SRAM_REG_FUNCTION_CONFIG         0x20
#define DAC18_SRAM_REG_FUNCTION_MAX            0x21
#define DAC18_SRAM_REG_FUNCTION_MIN            0x22
#define DAC18_SRAM_REG_GPI_DEBOUNCE            0x23
#define DAC18_SRAM_REG_VOUT_DATA_0             0x24
#define DAC18_SRAM_REG_VOUT_DATA_1             0x25
#define DAC18_SRAM_REG_VOUT_DATA_2             0x26
#define DAC18_SRAM_REG_VOUT_DATA_3             0x27
#define DAC18_SRAM_REG_VOUT_DATA_4             0x28
#define DAC18_SRAM_REG_VOUT_DATA_5             0x29
#define DAC18_SRAM_REG_VOUT_DATA_6             0x2A
#define DAC18_SRAM_REG_VOUT_DATA_7             0x2B
#define DAC18_SRAM_REG_PWM_FREQUENCY_ERROR     0x9E

/*! @} */ // dac18_reg

/**
 * @defgroup dac18_set DAC 18 Registers Settings
 * @brief Settings for registers of DAC 18 Click driver.
 */

/**
 * @addtogroup dac18_set
 * @{
 */

/**
 * @brief DAC 18 mode selection.
 * @details Specified mode selection of DAC 18 Click driver.
 */
#define DAC18_MODE_CONFIGURATION               0
#define DAC18_MODE_STANDALONE                  1

/**
 * @brief DAC 18 DAC-X-VOUT-CMP-CONFIG register bitmask.
 * @details Specified DAC-X-VOUT-CMP-CONFIG register bitmask of DAC 18 Click driver.
 */
#define DAC18_DACX_VOUT_CFG_GAIN_BITMASK       0x1C00u
#define DAC18_DACX_VOUT_CFG_GAIN_X1            0x0400u
#define DAC18_DACX_VOUT_CFG_GAIN_X1_5          0x0800u
#define DAC18_DACX_VOUT_CFG_GAIN_X2            0x0C00u
#define DAC18_DACX_VOUT_CFG_GAIN_X3            0x1000u
#define DAC18_DACX_VOUT_CFG_GAIN_X4            0x1400u
#define DAC18_DACX_VOUT_CFG_CMPX_OD_EN         0x0010u
#define DAC18_DACX_VOUT_CFG_CMPX_OUT_EN        0x0008u
#define DAC18_DACX_VOUT_CFG_CMPX_HIZ_IN_DIS    0x0004u
#define DAC18_DACX_VOUT_CFG_CMPX_INV_EN        0x0002u
#define DAC18_DACX_VOUT_CFG_CMPX_EN            0x0001u

/**
 * @brief DAC 18 COMMON-CONFIG register bitmask.
 * @details Specified COMMON-CONFIG register bitmask of DAC 18 Click driver.
 */
#define DAC18_COMMON_CFG_DEFAULT               0x03F9u
#define DAC18_COMMON_CFG_DEV_LOCK              0x4000u
#define DAC18_COMMON_CFG_EN_INT_REF            0x1000u
#define DAC18_COMMON_CFG_VOUT0_BITMASK         0x0C00u
#define DAC18_COMMON_CFG_VOUT0_PDN             0x0000u
#define DAC18_COMMON_CFG_VOUT0_10KOHM          0x0400u
#define DAC18_COMMON_CFG_VOUT0_100KOHM         0x0800u
#define DAC18_COMMON_CFG_VOUT0_HIZ             0x0C00u
#define DAC18_COMMON_CFG_VOUT1_BITMASK         0x0060u
#define DAC18_COMMON_CFG_VOUT1_PDN             0x0000u
#define DAC18_COMMON_CFG_VOUT1_10KOHM          0x0040u
#define DAC18_COMMON_CFG_VOUT1_100KOHM         0x0020u
#define DAC18_COMMON_CFG_VOUT1_HIZ             0x0060u

/**
 * @brief DAC 18 COMMON-TRIGGER register bitmask.
 * @details Specified COMMON-TRIGGER register bitmask of DAC 18 Click driver.
 */
#define DAC18_COMMON_TRG_DEV_LOCK              0x5000u
#define DAC18_COMMON_TRG_RESET                 0x0A00u
#define DAC18_COMMON_TRG_NVM_PROG              0x0002u
#define DAC18_COMMON_TRG_NVM_RELOAD            0x0001u

/**
 * @brief DAC 18 FUNCTION-TRIGGER register bitmask.
 * @details Specified FUNCTION-TRIGGER register bitmask of DAC 18 Click driver.
 */
#define DAC18_FUNCTION_TRG_START               0x0001u
#define DAC18_FUNCTION_TRG_STOP                0x0000u

/**
 * @brief DAC 18 GENERAL-STATUS register bitmask.
 * @details Specified GENERAL-STATUS register bitmask of DAC 18 Click driver.
 */
#define DAC18_GEN_STATUS_NVM_CRC_FAIL_INT      0x8000u
#define DAC18_GEN_STATUS_NVM_CRC_FAIL_USER     0x4000u
#define DAC18_GEN_STATUS_DAC_0_BUSY            0x1000u
#define DAC18_GEN_STATUS_DAC_1_BUSY            0x0200u
#define DAC18_GEN_STATUS_NVM_BUSY              0x0100u
#define DAC18_GEN_STATUS_DEVICE_ID_BITMASK     0x00FCu
#define DAC18_GEN_STATUS_DEVICE_ID             0x001Au
#define DAC18_GEN_STATUS_VERSION_ID_BITMASK    0x0003u
#define DAC18_GEN_STATUS_VERSION_ID            0x0000u

/**
 * @brief DAC 18 DEVICE-MODE-CONFIG register bitmask.
 * @details Specified DEVICE-MODE-CONFIG register bitmask of DAC 18 Click driver.
 */
#define DAC18_DEV_MODE_CFG_DEFAULT             0x8000u 
#define DAC18_DEV_MODE_CFG_EN                  0x0000u
#define DAC18_DEV_MODE_CFG_DIS                 0x2000u
#define DAC18_DEV_MODE_CFG_SM_IO_EN            0x0040u

/**
 * @brief DAC 18 STATE-MACHINE-CONFIG register bitmask.
 * @details Specified STATE-MACHINE-CONFIG register bitmask of DAC 18 Click driver.
 */
#define DAC18_STATE_M_CFG_SM_ABORT             0x0004u
#define DAC18_STATE_M_CFG_SM_START             0x0002u
#define DAC18_STATE_M_CFG_SM_EN                0x0001u
#define DAC18_STATE_M_CFG_SM_STOP              0x0000u

/**
 * @brief DAC 18 FUNCTION-CONFIG register data values.
 * @details Specified FUNCTION-CONFIG register data values of DAC 18 Click driver.
 */
#define DAC18_FUN_CFG_F_SEL_TRIANGULAR         0x00
#define DAC18_FUN_CFG_F_SEL_SAWTOOTH           0x01
#define DAC18_FUN_CFG_F_SEL_INV_SAWTOOTH       0x02
#define DAC18_FUN_CFG_F_SEL_DISABLE            0x07
#define DAC18_FUN_CFG_C_STEP_1LSB              0x00
#define DAC18_FUN_CFG_C_STEP_2LSB              0x01
#define DAC18_FUN_CFG_C_STEP_3LSB              0x02
#define DAC18_FUN_CFG_C_STEP_4LSB              0x03
#define DAC18_FUN_CFG_C_STEP_6LSB              0x04
#define DAC18_FUN_CFG_C_STEP_8LSB              0x05
#define DAC18_FUN_CFG_C_STEP_16LSB             0x06
#define DAC18_FUN_CFG_C_STEP_32LSB             0x07
#define DAC18_FUN_CFG_T_STEP_INVALID           0x00
#define DAC18_FUN_CFG_T_STEP_4_US              0x01
#define DAC18_FUN_CFG_T_STEP_8_US              0x02
#define DAC18_FUN_CFG_T_STEP_12_US             0x03
#define DAC18_FUN_CFG_T_STEP_18_US             0x04
#define DAC18_FUN_CFG_T_STEP_27_04_US          0x05
#define DAC18_FUN_CFG_T_STEP_40_48_US          0x06
#define DAC18_FUN_CFG_T_STEP_60_72_US          0x07
#define DAC18_FUN_CFG_T_STEP_91_12_US          0x08
#define DAC18_FUN_CFG_T_STEP_136_72_US         0x09
#define DAC18_FUN_CFG_T_STEP_239_2_US          0x0A
#define DAC18_FUN_CFG_T_STEP_418_64_US         0x0B
#define DAC18_FUN_CFG_T_STEP_732_56_US         0x0C
#define DAC18_FUN_CFG_T_STEP_1282_US           0x0D
#define DAC18_FUN_CFG_T_STEP_2563_92_US        0x0E
#define DAC18_FUN_CFG_T_STEP_5127_92_US        0x0F

/**
 * @brief DAC 18 FUNCTION-MAX and FUNCTION-MIN register data values.
 * @details Specified maximum and minimum DAC code for the function generator data values of DAC 18 Click driver.
 */
#define DAC18_DAC_CODE_MAX_DEFAULT             0x05AAu
#define DAC18_DAC_CODE_MIN_DEFAULT             0x00C8u
#define DAC18_DAC_CODE_12BIT_MAX               0x0FFFu

/**
 * @brief DAC 18 Debounce delay for the GPI pins data values.
 * @details Specified debounce delay for the GPI pins data values of DAC 18 Click driver.
 */
#define DAC18_GPI_DEBOUNCE_50_MS               50.0f
#define DAC18_GPI_DEBOUNCE_MAX                 10485.7f
#define DAC18_GPI_DEBOUNCE_SENS                0.16f

/**
 * @brief DAC 18 default LUT data values.
 * @details Specified debounce delay for the GPI pins data values of DAC 18 Click driver.
 */
#define DAC18_LUT_DEFAULT_VOUT_DATA_0          0xA1C0u
#define DAC18_LUT_DEFAULT_VOUT_DATA_1          0x8E40u
#define DAC18_LUT_DEFAULT_VOUT_DATA_2          0x7AC0u
#define DAC18_LUT_DEFAULT_VOUT_DATA_3          0x6740u
#define DAC18_LUT_DEFAULT_VOUT_DATA_4          0x5380u
#define DAC18_LUT_DEFAULT_VOUT_DATA_5          0x4000u
#define DAC18_LUT_DEFAULT_VOUT_DATA_6          0x2C80u
#define DAC18_LUT_DEFAULT_VOUT_DATA_7          0x18C0u

/**
 * @brief DAC 18 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 18 Click driver.
 */
#define DAC18_DEVICE_ADDRESS_GND               0x48
#define DAC18_DEVICE_ADDRESS_VCC               0x49

/*! @} */ // dac18_set

/**
 * @defgroup dac18_map DAC 18 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 18 Click driver.
 */

/**
 * @addtogroup dac18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 18 Click to the selected MikroBUS.
 */
#define DAC18_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.mod = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dac18_map
/*! @} */ // dac18

/**
 * @brief DAC 18 Click context object.
 * @details Context object definition of DAC 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mod;      /**< MODE pin to select between programming and standalone modes. */

    // Input pins
    digital_in_t gp2;       /**< Standalone mode: General-purpose input 2. */
    digital_in_t gp1;       /**< Standalone mode: General-purpose input 1. */
    digital_in_t gp0;       /**< Standalone mode: General-purpose input 0. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} dac18_t;

/**
 * @brief DAC 18 Click configuration object.
 * @details Configuration object definition of DAC 18 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t gp2;   /**< Standalone mode: General-purpose input 2. */
    pin_name_t mod;   /**< MODE pin to select between programming and standalone modes. */
    pin_name_t gp1;   /**< Standalone mode: General-purpose input 1. */
    pin_name_t gp0;   /**< Standalone mode: General-purpose input 0. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} dac18_cfg_t;

/**
 * @brief DAC 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC18_OK = 0,
    DAC18_ERROR = -1

} dac18_return_value_t;

/*!
 * @addtogroup dac18 DAC 18 Click Driver
 * @brief API for configuring and manipulating DAC 18 Click driver.
 * @{
 */

/**
 * @brief DAC 18 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac18_cfg_setup ( dac18_cfg_t *cfg );

/**
 * @brief DAC 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac18_init ( dac18_t *ctx, dac18_cfg_t *cfg );

/**
 * @brief DAC 18 default configuration function.
 * @details This function executes a default configuration of DAC 18
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac18_default_cfg ( dac18_t *ctx );

/**
 * @brief DAC 18 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac18_generic_write ( dac18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 18 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac18_generic_read ( dac18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DAC 18 register writing function.
 * @details This function writes a 16-bit data to
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac18_register_write ( dac18_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 18 register reading function.
 * @details This function reads a 16-bit starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac18_register_read ( dac18_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 18 PWM OUT0 configuration function.
 * @details This function configures PWM output (OUT0) for the function generator 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] f_sel : Function select (sawtooth or triangular waveform).
 * @param[in] c_step : Code step [0x00-0x07].
 * @param[in] t_step : Time step [0x00-0x0F].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac18_cfg_pwm_out ( dac18_t *ctx, uint8_t f_sel, uint8_t c_step, uint8_t t_step );

/**
 * @brief DAC 18 set DAC code function.
 * @details This function sets min and max DAC code for the function generator
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] f_sel : Function select (sawtooth or triangular waveform).
 * @param[in] max_dc : Maximum DAC code for the function generator.
 * @param[in] min_dc : Minimum DAC code for the function generator.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac18_set_dac_code ( dac18_t *ctx, uint16_t max_dc, uint16_t min_dc );

/**
 * @brief DAC 18 set debounce delay function.
 * @details This function sets the desired debounce delay y for the GPI pins
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] delay_ms : Debounce delay in millisecond [0ms-10485.6ms].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac18_set_debounce_delay ( dac18_t *ctx, float delay_ms );

/**
 * @brief DAC 18 set operation mode function.
 * @details This function selects between programming and standalone modes 
 * by toggling the digital output state of the MOD pin.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] mode : 
 *         @li @c 0 - Configuration mode,
 *         @li @c 1 - Standalone mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void dac18_set_mode ( dac18_t *ctx, uint8_t mode );

/**
 * @brief DAC 18 get GP0 pin state function.
 * @details This function gets states of the GP0 pin.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t dac18_get_gp0 ( dac18_t *ctx );

/**
 * @brief DAC 18 get GP1 pin state function.
 * @details This function gets states of the GP1 pin.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t dac18_get_gp1 ( dac18_t *ctx );

/**
 * @brief DAC 18 get GP2 pin state function.
 * @details This function gets states of the GP2 pin.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t dac18_get_gp2 ( dac18_t *ctx );

/**
 * @brief DAC 18 get GPI status function.
 * @details This function gets GPI status 
 * by reading the states of the GP0, GP1 and GP2 pins.
 * @param[in] ctx : Click context object.
 * See #dac18_t object definition for detailed explanation.
 * @param[in] gpi_status : GPI status [0-7].
 * @return Nothing.
 * @note None.
 */
void dac18_get_gpi_status ( dac18_t *ctx, uint8_t *gpi_status );

#ifdef __cplusplus
}
#endif
#endif // DAC18_H

/*! @} */ // dac18

// ------------------------------------------------------------------------ END
