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
 * @file press.h
 * @brief This file contains API for PRESS Click Driver.
 */

#ifndef PRESS_H
#define PRESS_H

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
 * @addtogroup press PRESS Click Driver
 * @brief API for configuring and manipulating PRESS Click driver.
 * @{
 */

/**
 * @defgroup press_reg PRESS Registers List
 * @brief List of registers of PRESS Click driver.
 */

/**
 * @addtogroup press_reg
 * @{
 */

/**
 * @brief PRESS description register.
 * @details Specified register for description of PRESS Click driver.
 */
#define PRESS_REG_INTERRUPT_CFG            0x0B
#define PRESS_REG_THS_P_L                  0x0C
#define PRESS_REG_THS_P_H                  0x0D
#define PRESS_REG_IF_CTRL                  0x0E
#define PRESS_REG_WHO_AM_I                 0x0F
#define PRESS_REG_CTRL_REG1                0x10
#define PRESS_REG_CTRL_REG2                0x11
#define PRESS_REG_CTRL_REG3                0x12
#define PRESS_REG_FIFO_CTRL                0x14
#define PRESS_REG_FIFO_WTM                 0x15
#define PRESS_REG_REF_P_L                  0x16
#define PRESS_REG_REF_P_H                  0x17
#define PRESS_REG_I3C_IF_CTRL              0x19
#define PRESS_REG_RPDS_L                   0x1A
#define PRESS_REG_RPDS_H                   0x1B
#define PRESS_REG_INT_SOURCE               0x24
#define PRESS_REG_FIFO_STATUS1             0x25
#define PRESS_REG_FIFO_STATUS2             0x26
#define PRESS_REG_STATUS                   0x27
#define PRESS_REG_PRESSURE_OUT_XL          0x28
#define PRESS_REG_PRESSURE_OUT_L           0x29
#define PRESS_REG_PRESSURE_OUT_H           0x2A
#define PRESS_REG_TEMP_OUT_L               0x2B
#define PRESS_REG_TEMP_OUT_H               0x2C
#define PRESS_REG_FIFO_DATA_OUT_PRESS_XL   0x78
#define PRESS_REG_FIFO_DATA_OUT_PRESS_L    0x79
#define PRESS_REG_FIFO_DATA_OUT_PRESS_H    0x7A

/*! @} */ // press_reg

/**
 * @defgroup press_set PRESS Registers Settings
 * @brief Settings for registers of PRESS Click driver.
 */

/**
 * @addtogroup press_set
 * @{
 */

/**
 * @brief PRESS device Who am I data value.
 * @details Specified device Who am I data value of PRESS Click driver.
 */
#define PRESS_WHO_AM_I                     0xB4

/**
 * @brief PRESS description of control register 1, output data rate and average selection.
 * @details Specified setting for control register 1 of PRESS Click driver.
 */
#define PRESS_ODR_PWR_DOWN_ONE_SHOT        0x00
#define PRESS_ODR_1HZ                      0x08
#define PRESS_ODR_4HZ                      0x10
#define PRESS_ODR_10HZ                     0x18
#define PRESS_ODR_25HZ                     0x20
#define PRESS_ODR_50HZ                     0x28
#define PRESS_ODR_75HZ                     0x30
#define PRESS_ODR_100HZ                    0x38
#define PRESS_ODR_200HZ                    0x40
#define PRESS_ODR_BIT_MASK                 0x78
#define PRESS_AVG_4                        0x00
#define PRESS_AVG_8                        0x01
#define PRESS_AVG_16                       0x02
#define PRESS_AVG_32                       0x03
#define PRESS_AVG_64                       0x04
#define PRESS_AVG_128                      0x05
#define PRESS_AVG_512                      0x07
#define PRESS_AVG_BIT_MASK                 0x07

/**
 * @brief PRESS description of control register 2 setting.
 * @details Specified setting for control register 2 of PRESS Click driver.
 */
#define PRESS_BOOT_NORMAL_MODE             0x00
#define PRESS_REBOOT_MEMORY_CONTENT        0x80
#define PRESS_FS_MODE_1_1260HPA            0x00
#define PRESS_FS_MODE_2_4060HPA            0x40
#define PRESS_LFPF_CFG_ODR_4               0x00
#define PRESS_LFPF_CFG_ODR_9               0x20
#define PRESS_DISABLE_LPFP                 0x00
#define PRESS_ENABLE_LPFP                  0x10
#define PRESS_BDU_CONTINUOUS               0x00
#define PRESS_BDU_MSB_LSB_READ             0x08
#define PRESS_SW_RESET                     0x04
#define PRESS_ONESHOT_IDLE                 0x00
#define PRESS_ONESHOT_NEW_DATA             0x01

/**
 * @brief PRESS description of control register 3, Qvar configuration and auto increment.
 * @details Specified setting for Qvar configuration of PRESS Click driver.
 */
#define PRESS_REBOOT_AH_QVAR_EN            0x80
#define PRESS_REBOOT_AH_QVAR_DIS           0x00
#define PRESS_REBOOT_AH_QVAR_P_AUTO_EN     0x20
#define PRESS_REBOOT_AH_QVAR_P_AUTO_DIS    0x00
#define PRESS_REBOOT_IF_ADD_INC_EN         0x01
#define PRESS_REBOOT_IF_ADD_INC_DIS        0x00

/**
 * @brief PRESS description of FIFO mode selection.
 * @details Specified setting for FIFO mode selection of PRESS Click driver.
 */
#define PRESS_TRIG_F_MODE_BYPASS           0x00
#define PRESS_TRIG_F_MODE_FIFO             0x01
#define PRESS_TRIG_F_MODE_CONT             0x02
#define PRESS_TRIG_F_MODE_BYPASS_FIFO      0x05
#define PRESS_TRIG_F_MODE_BYPASS_CONT      0x06
#define PRESS_TRIG_F_MODE_CONT_FIFO        0x07

/**
 * @brief PRESS description of status register.
 * @details Specified setting for status register of PRESS Click driver.
 */
#define PRESS_STATUS_TEMP_OVERRUN          0x20
#define PRESS_STATUS_PRESS_OVERRUN         0x10
#define PRESS_STATUS_TEMP_AVAILABLE        0x02
#define PRESS_STATUS_PRESS_AVAILABLE       0x01

/**
 * @brief PRESS description AH and Qvar configuration.
 * @details Specified AH and Qvar configuration of PRESS Click driver.
 */
#define PRESS_AH_QVAR_DISABLE              0x00
#define PRESS_AH_QVAR_ENABLE               0x01

/**
 * @brief PRESS description of calculation values.
 * @details Specified setting for status register of PRESS Click driver.
 */
#define PRESS_LSB_HPA_FS_MODE_4096         4096.0f
#define PRESS_LSB_HPA_FS_MODE_2048         2048.0f
#define PRESS_TEMP_SENS                    100.0f
#define PRESS_QVAR_GAIN_LSB_MV             426000.0f

/**
 * @brief PRESS device address setting.
 * @details Specified setting for device slave address selection of
 * PRESS Click driver.
 */
#define PRESS_DEVICE_ADDRESS               0x5C

/*! @} */ // press_set

/**
 * @defgroup press_map PRESS MikroBUS Map
 * @brief MikroBUS pin mapping of PRESS Click driver.
 */

/**
 * @addtogroup press_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PRESS Click to the selected MikroBUS.
 */
#define PRESS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // press_map
/*! @} */ // press

/**
 * @brief PRESS Click context object.
 * @details Context object definition of PRESS Click driver.
 */
typedef struct
{

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} press_t;

/**
 * @brief PRESS Click configuration object.
 * @details Configuration object definition of PRESS Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} press_cfg_t;

/**
 * @brief PRESS Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESS_OK = 0,
    PRESS_ERROR = -1

} press_return_value_t;

/*!
 * @addtogroup press PRESS Click Driver
 * @brief API for configuring and manipulating PRESS Click driver.
 * @{
 */

/**
 * @brief PRESS configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #press_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void press_cfg_setup ( press_cfg_t *cfg );

/**
 * @brief PRESS initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #press_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_init ( press_t *ctx, press_cfg_t *cfg );

/**
 * @brief PRESS default configuration function.
 * @details This function executes a default configuration of PRESS
 * Click board.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t press_default_cfg ( press_t *ctx );

/**
 * @brief PRESS I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * See #press_reg definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_generic_write ( press_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief PRESS I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * See #press_reg definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_generic_read ( press_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief PRESS I2C register writing function.
 * @details This function writes a desired data byte 
 * to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * See #press_reg definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_reg_write ( press_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PRESS I2C register reading function.
 * @details This function reads a data byte from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * See #press_reg definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_reg_read ( press_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PRESS software reset function.
 * @details This function performs the software reset
 * of the ILPS28QSW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with Qvar detection in a water-resistant package
 * on the PRESS Click board™.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_sw_reset ( press_t *ctx );

/**
 * @brief PRESS config AH and Qva function.
 * @details This function performs the enable or disable AH and Qvar
 * of the ILPS28QSW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with Qvar detection in a water-resistant package
 * on the PRESS Click board™.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[in] ah_qvar_en : Config AH and Qva:
 *         @li @c 0 [PRESS_AH_QVAR_DISABLE] - AH and Qvar are disabled,
 *         @li @c 1 [PRESS_AH_QVAR_ENABLE] - AH and Qvar are enabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_config_ah_qvar ( press_t *ctx, uint8_t ah_qvar_en );

/**
 * @brief PRESS gets the raw data function.
 * @details This function reads the pressure, temperature and Qvar raw data
 * of the ILPS28QSW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with Qvar detection in a water-resistant package
 * on the PRESS Click board™.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[out] press_data : Pressure data.
 * @param[out] qvar_data : Qvar data.
 * @param[out] temp_data : Temperature data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_get_raw_data ( press_t *ctx, uint32_t *press_data, uint32_t *qvar_data, uint16_t *temp_data );

/**
 * @brief PRESS gets the measurement data function.
 * @details This function reads temperature and pressure data conversion
 * of the ILPS28QSW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with Qvar detection in a water-resistant package
 * on the PRESS Click board™.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data ( mbar ).
 * @param[out] temperature : Temperature data ( degree Celsius ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_get_measurement_data ( press_t *ctx, float *pressure, float *temperature );

/**
 * @brief PRESS gets the AH/Qvar data function.
 * @details This function reads Qvar data conversion
 * of the ILPS28QSW, Dual full-scale, 1260 hPa and 4060 hPa, 
 * absolute digital output barometer with Qvar detection in a water-resistant package
 * on the PRESS Click board™.
 * @param[in] ctx : Click context object.
 * See #press_t object definition for detailed explanation.
 * @param[out] ah_qvar : Qvar data ( mV ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t press_get_ah_qvar_data ( press_t *ctx, float *ah_qvar );

#ifdef __cplusplus
}
#endif
#endif // PRESS_H

/*! @} */ // press

// ------------------------------------------------------------------------ END
