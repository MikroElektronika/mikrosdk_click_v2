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
 * @file ldctouch.h
 * @brief This file contains API for LDC Touch Click Driver.
 */

#ifndef LDCTOUCH_H
#define LDCTOUCH_H

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
 * @addtogroup ldctouch LDC Touch Click Driver
 * @brief API for configuring and manipulating LDC Touch Click driver.
 * @{
 */

/**
 * @defgroup ldctouch_reg LDC Touch Registers List
 * @brief List of registers of LDC Touch Click driver.
 */

/**
 * @addtogroup ldctouch_reg
 * @{
 */

/**
 * @brief LDC Touch register map.
 * @details Specified register map of LDC Touch Click driver.
 */
#define LDCTOUCH_REG_STATUS                 0x00
#define LDCTOUCH_REG_OUT                    0x01
#define LDCTOUCH_REG_DATA0_LSB              0x02
#define LDCTOUCH_REG_DATA0_MSB              0x03
#define LDCTOUCH_REG_DATA1_LSB              0x04
#define LDCTOUCH_REG_DATA1_MSB              0x05
#define LDCTOUCH_REG_DATA2_LSB              0x06
#define LDCTOUCH_REG_DATA2_MSB              0x07
#define LDCTOUCH_REG_DATA3_LSB              0x08
#define LDCTOUCH_REG_DATA3_MSB              0x09
#define LDCTOUCH_REG_RESET                  0x0A
#define LDCTOUCH_REG_EN                     0x0C
#define LDCTOUCH_REG_NP_SCAN_RATE           0x0D
#define LDCTOUCH_REG_GAIN0                  0x0E
#define LDCTOUCH_REG_LP_SCAN_RATE           0x0F
#define LDCTOUCH_REG_GAIN1                  0x10
#define LDCTOUCH_REG_INTPOL                 0x11
#define LDCTOUCH_REG_GAIN2                  0x12
#define LDCTOUCH_REG_LP_BASE_INC            0x13
#define LDCTOUCH_REG_GAIN3                  0x14
#define LDCTOUCH_REG_NP_BASE_INC            0x15
#define LDCTOUCH_REG_BTPAUSE_MAXWIN         0x16
#define LDCTOUCH_REG_LC_DIVIDER             0x17
#define LDCTOUCH_REG_HYST                   0x18
#define LDCTOUCH_REG_TWIST                  0x19
#define LDCTOUCH_REG_COMMON_DEFORM          0x1A
#define LDCTOUCH_REG_OPOL_DPOL              0x1C
#define LDCTOUCH_REG_CNTSC                  0x1E
#define LDCTOUCH_REG_SENSOR0_CONFIG         0x20
#define LDCTOUCH_REG_SENSOR1_CONFIG         0x22
#define LDCTOUCH_REG_SENSOR2_CONFIG         0x24
#define LDCTOUCH_REG_FTF0                   0x25
#define LDCTOUCH_REG_SENSOR3_CONFIG         0x26
#define LDCTOUCH_REG_FTF1_2                 0x28
#define LDCTOUCH_REG_FTF3                   0x2B
#define LDCTOUCH_REG_RAW_DATA0_3            0x59
#define LDCTOUCH_REG_RAW_DATA0_2            0x5A
#define LDCTOUCH_REG_RAW_DATA0_1            0x5B
#define LDCTOUCH_REG_RAW_DATA1_3            0x5C
#define LDCTOUCH_REG_RAW_DATA1_2            0x5D
#define LDCTOUCH_REG_RAW_DATA1_1            0x5E
#define LDCTOUCH_REG_RAW_DATA2_3            0x5F
#define LDCTOUCH_REG_RAW_DATA2_2            0x60
#define LDCTOUCH_REG_RAW_DATA2_1            0x61
#define LDCTOUCH_REG_RAW_DATA3_3            0x62
#define LDCTOUCH_REG_RAW_DATA3_2            0x63
#define LDCTOUCH_REG_RAW_DATA3_1            0x64
#define LDCTOUCH_REG_MANUFACTURER_ID_LSB    0xFC
#define LDCTOUCH_REG_MANUFACTURER_ID_MSB    0xFD
#define LDCTOUCH_REG_DEVICE_ID_LSB          0xFE
#define LDCTOUCH_REG_DEVICE_ID_MSB          0xFF

/*! @} */ // ldctouch_reg

/**
 * @defgroup ldctouch_set LDC Touch Registers Settings
 * @brief Settings for registers of LDC Touch Click driver.
 */

/**
 * @addtogroup ldctouch_set
 * @{
 */

/**
 * @brief LDC Touch status settings.
 * @details Specified status settings of LDC Touch Click driver.
 */
#define LDCTOUCH_STATUS_OUT                 0x80
#define LDCTOUCH_STATUS_CHIP_READY          0x40
#define LDCTOUCH_STATUS_READY_TO_WRITE      0x20
#define LDCTOUCH_STATUS_MAXOUT              0x10
#define LDCTOUCH_STATUS_FSM_WD              0x08
#define LDCTOUCH_STATUS_LC_WD               0x04
#define LDCTOUCH_STATUS_TIMEOUT             0x02
#define LDCTOUCH_STATUS_REGISTER_FLAG       0x01

/**
 * @brief LDC Touch operating mode settings.
 * @details Specified operating mode settings of LDC Touch Click driver.
 */
#define LDCTOUCH_MODE_NORMAL                0x00
#define LDCTOUCH_MODE_CONFIG                0x01
#define LDCTOUCH_MODE_FULL_RESET            0x10

/**
 * @brief LDC Touch enable register settings.
 * @details Specified enable register settings of LDC Touch Click driver.
 */
#define LDCTOUCH_EN_CH3_LP                  0x80
#define LDCTOUCH_EN_CH2_LP                  0x40
#define LDCTOUCH_EN_CH1_LP                  0x20
#define LDCTOUCH_EN_CH0_LP                  0x10
#define LDCTOUCH_EN_CH3_NP                  0x08
#define LDCTOUCH_EN_CH2_NP                  0x04
#define LDCTOUCH_EN_CH1_NP                  0x02
#define LDCTOUCH_EN_CH0_NP                  0x01

/**
 * @brief LDC Touch output polarity settings.
 * @details Specified output polarity settings of LDC Touch Click driver.
 */
#define LDCTOUCH_OPOL3_ACTIVE_HIGH          0x80
#define LDCTOUCH_OPOL3_ACTIVE_LOW           0x00
#define LDCTOUCH_OPOL2_ACTIVE_HIGH          0x40
#define LDCTOUCH_OPOL2_ACTIVE_LOW           0x00
#define LDCTOUCH_OPOL1_ACTIVE_HIGH          0x20
#define LDCTOUCH_OPOL1_ACTIVE_LOW           0x00
#define LDCTOUCH_OPOL0_ACTIVE_HIGH          0x10
#define LDCTOUCH_OPOL0_ACTIVE_LOW           0x00
#define LDCTOUCH_DPOL3_DATA_INCREASES       0x08
#define LDCTOUCH_DPOL3_DATA_DECREASES       0x00
#define LDCTOUCH_DPOL2_DATA_INCREASES       0x04
#define LDCTOUCH_DPOL2_DATA_DECREASES       0x00
#define LDCTOUCH_DPOL1_DATA_INCREASES       0x02
#define LDCTOUCH_DPOL1_DATA_DECREASES       0x00
#define LDCTOUCH_DPOL0_DATA_INCREASES       0x01
#define LDCTOUCH_DPOL0_DATA_DECREASES       0x00

/**
 * @brief LDC Touch button mode settings.
 * @details Specified button mode settings of LDC Touch Click driver.
 */
#define LDCTOUCH_BUTTON_MODE_FINGER         0x00
#define LDCTOUCH_BUTTON_MODE_METAL          0x01
#define LDCTOUCH_BUTTON_MODE                LDCTOUCH_BUTTON_MODE_FINGER

/**
 * @brief LDC Touch device ID values.
 * @details Specified device ID values of LDC Touch Click driver.
 */
#define LDCTOUCH_MANUFACTURER_ID_LSB        0x49
#define LDCTOUCH_MANUFACTURER_ID_MSB        0x54
#define LDCTOUCH_DEVICE_ID_LSB              0x00
#define LDCTOUCH_DEVICE_ID_MSB              0x40

/**
 * @brief LDC Touch device address setting.
 * @details Specified setting for device slave address selection of
 * LDC Touch Click driver.
 */
#define LDCTOUCH_DEVICE_ADDRESS             0x2A

/*! @} */ // ldctouch_set

/**
 * @defgroup ldctouch_map LDC Touch MikroBUS Map
 * @brief MikroBUS pin mapping of LDC Touch Click driver.
 */

/**
 * @addtogroup ldctouch_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LDC Touch Click to the selected MikroBUS.
 */
#define LDCTOUCH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.s2 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.s0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.s1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.s3 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ldctouch_map
/*! @} */ // ldctouch

/**
 * @brief LDC Touch Click context object.
 * @details Context object definition of LDC Touch Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  s0;           /**< Sensor 0 status. */
    digital_in_t  s1;           /**< Sensor 1 status. */
    digital_in_t  s2;           /**< Sensor 2 status. */
    digital_in_t  s3;           /**< Sensor 3 status. */
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} ldctouch_t;

/**
 * @brief LDC Touch Click configuration object.
 * @details Configuration object definition of LDC Touch Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  s0;             /**< Sensor 0 status. */
    pin_name_t  s1;             /**< Sensor 1 status. */
    pin_name_t  s2;             /**< Sensor 2 status. */
    pin_name_t  s3;             /**< Sensor 3 status. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} ldctouch_cfg_t;

/**
 * @brief LDC Touch Click data object.
 * @details Data object definition of LDC Touch Click driver.
 */
typedef struct
{
    uint8_t status;
    uint8_t out_state;
    int16_t ch0_raw_button;
    int16_t ch1_raw_button;
    int16_t ch2_raw_button;
    int16_t ch3_raw_button;

} ldctouch_data_t;

/**
 * @brief LDC Touch Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LDCTOUCH_OK = 0,
    LDCTOUCH_ERROR = -1

} ldctouch_return_value_t;

/*!
 * @addtogroup ldctouch LDC Touch Click Driver
 * @brief API for configuring and manipulating LDC Touch Click driver.
 * @{
 */

/**
 * @brief LDC Touch configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ldctouch_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ldctouch_cfg_setup ( ldctouch_cfg_t *cfg );

/**
 * @brief LDC Touch initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ldctouch_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldctouch_init ( ldctouch_t *ctx, ldctouch_cfg_t *cfg );

/**
 * @brief LDC Touch default configuration function.
 * @details This function executes a default configuration of LDC Touch
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ldctouch_default_cfg ( ldctouch_t *ctx );

/**
 * @brief LDC Touch I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldctouch_generic_write ( ldctouch_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LDC Touch I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldctouch_generic_read ( ldctouch_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LDC Touch write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldctouch_write_register ( ldctouch_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LDC Touch read register function.
 * @details This function reads data from the selected register.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldctouch_read_register ( ldctouch_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LDC Touch get s0 pin function.
 * @details This function returns the S0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ldctouch_get_s0_pin ( ldctouch_t *ctx );

/**
 * @brief LDC Touch get s1 pin function.
 * @details This function returns the S1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ldctouch_get_s1_pin ( ldctouch_t *ctx );

/**
 * @brief LDC Touch get s2 pin function.
 * @details This function returns the S2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ldctouch_get_s2_pin ( ldctouch_t *ctx );

/**
 * @brief LDC Touch get s3 pin function.
 * @details This function returns the S3 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ldctouch_get_s3_pin ( ldctouch_t *ctx );

/**
 * @brief LDC Touch get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ldctouch_get_int_pin ( ldctouch_t *ctx );

/**
 * @brief LDC Touch check communication function.
 * @details This function checks the communication by reading and verifying 
 * the defice and manufacturer IDs.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldctouch_check_communication ( ldctouch_t *ctx );

/**
 * @brief LDC Touch set operation mode function.
 * @details This function sets the operation mode.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0x00 - Normal,
 *                   @li @c 0x01 - Config,
 *                   @li @c 0x10 - Full Reset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldctouch_set_operation_mode ( ldctouch_t *ctx, uint8_t mode );

/**
 * @brief LDC Touch get data function.
 * @details This function reads status, out_state, and all buttons raw data.
 * @param[in] ctx : Click context object.
 * See #ldctouch_t object definition for detailed explanation.
 * @param[out] button_data : Button data object.
 * See #ldctouch_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldctouch_get_data ( ldctouch_t *ctx, ldctouch_data_t *button_data );

#ifdef __cplusplus
}
#endif
#endif // LDCTOUCH_H

/*! @} */ // ldctouch

// ------------------------------------------------------------------------ END
