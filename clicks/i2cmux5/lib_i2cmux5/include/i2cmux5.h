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
 * @file i2cmux5.h
 * @brief This file contains API for I2C MUX 5 Click Driver.
 */

#ifndef I2CMUX5_H
#define I2CMUX5_H

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
 * @addtogroup i2cmux5 I2C MUX 5 Click Driver
 * @brief API for configuring and manipulating I2C MUX 5 Click driver.
 * @{
 */

/**
 * @defgroup i2cmux5_reg I2C MUX 5 Registers List
 * @brief List of registers of I2C MUX 5 Click driver.
 */

/**
 * @addtogroup i2cmux5_reg
 * @{
 */

/**
 * @brief I2C MUX 5 description register.
 * @details Specified register for description of I2C MUX 5 Click driver.
 */
#define I2CMUX5_REGISTER_0                           0x00
#define I2CMUX5_REGISTER_1                           0x01
#define I2CMUX5_REGISTER_2                           0x02
#define I2CMUX5_REGISTER_3                           0x03

/*! @} */ // i2cmux5_reg

/**
 * @defgroup i2cmux5_set I2C MUX 5 Registers Settings
 * @brief Settings for registers of I2C MUX 5 Click driver.
 */

/**
 * @addtogroup i2cmux5_set
 * @{
 */

/**
 * @brief I2C MUX 5 description setting.
 * @details Specified setting for description of I2C MUX 5 Click driver.
 */

/**
 * @brief I2C MUX 5 Register 0 setting.
 * @details Specified setting for Register 1 of I2C MUX 5 Click driver.
 */
#define I2CMUX5_SET_REG_0_US_BUS_DISCONNECTED        0x00
#define I2CMUX5_SET_REG_0_US_BUS_CONNECTED           0x80
#define I2CMUX5_SET_REG_0_ALERT1_STATE_LOW           0x00
#define I2CMUX5_SET_REG_0_ALERT1_STATE_HIGH          0x40
#define I2CMUX5_SET_REG_0_ALERT2_STATE_LOW           0x00
#define I2CMUX5_SET_REG_0_ALERT2_STATE_HIGH          0x20
#define I2CMUX5_SET_REG_0_ALERT3_STATE_LOW           0x00
#define I2CMUX5_SET_REG_0_ALERT3_STATE_HIGH          0x10
#define I2CMUX5_SET_REG_0_ALERT4_STATE_LOW           0x00
#define I2CMUX5_SET_REG_0_ALERT5_STATE_HIGH          0x08
#define I2CMUX5_SET_REG_0_ATTEMPT_CONN_FAILED        0x00
#define I2CMUX5_SET_REG_0_ATTEMPT_CONN_OK            0x04
#define I2CMUX5_SET_REG_0_NO_LATCHED_TIMEOUT         0x00
#define I2CMUX5_SET_REG_0_LATCHED_TIMEOUT            0x02
#define I2CMUX5_SET_REG_0_NO_TIMEOUT_OCCURRING       0x00
#define I2CMUX5_SET_REG_0_TIMEOUT_OCCURRING          0x01


/**
 * @brief I2C MUX 5 Register 1 setting.
 * @details Specified setting for Register 1 of I2C MUX 5 Click driver.
 */
#define I2CMUX5_SET_REG_1_URTAC_INACTIVE             0x00
#define I2CMUX5_SET_REG_1_URTAC_ACTIVE               0x80
#define I2CMUX5_SET_REG_1_DRTAC_INACTIVE             0x00
#define I2CMUX5_SET_REG_1_DRTAC_ACTIVE               0x40
#define I2CMUX5_SET_REG_1_GPIO_1_LOW                 0x00
#define I2CMUX5_SET_REG_1_GPIO_1_HIGH                0x20
#define I2CMUX5_SET_REG_1_GPIO_2_LOW                 0x00
#define I2CMUX5_SET_REG_1_GPIO_2_HIGH                0x10

/**
 * @brief I2C MUX 5 Register 2 setting.
 * @details Specified setting for Register 2 of I2C MUX 5 Click driver.
 */
#define I2CMUX5_SET_REG_2_CFG_GPIO_1_OUTPUT          0x00
#define I2CMUX5_SET_REG_2_CFG_GPIO_1_INPUT           0x80
#define I2CMUX5_SET_REG_2_CFG_GPIO_2_OUTPUT          0x00
#define I2CMUX5_SET_REG_2_CFG_GPIO_2_INPUT           0x40
#define I2CMUX5_SET_REG_2_BUS_LOGIC_STATE_BITS       0x00
#define I2CMUX5_SET_REG_2_CONN_RGL_LOGIC_STATE       0x20
#define I2CMUX5_SET_REG_2_CFG_GPIO_1_OD_PULL_DOWN    0x00
#define I2CMUX5_SET_REG_2_CFG_GPIO_1_PUSH_PULL       0x10
#define I2CMUX5_SET_REG_2_CFG_GPIO_2_OD_PULL_DOWN    0x00
#define I2CMUX5_SET_REG_2_CFG_GPIO_2_PUSH_PULL       0x08
#define I2CMUX5_SET_REG_2_MASS_WRITE_DISABLE         0x00
#define I2CMUX5_SET_REG_2_MASS_WRITE_ENABLE          0x04
#define I2CMUX5_SET_REG_2_TIMEOUT_DISABLED           0x00
#define I2CMUX5_SET_REG_2_TIMEOUT_MODE_30_MS         0x01
#define I2CMUX5_SET_REG_2_TIMEOUT_MODE_15_MS         0x02
#define I2CMUX5_SET_REG_2_TIMEOUT_MODE_7_5_MS        0x03

/**
 * @brief I2C MUX 5 Register 3 setting.
 * @details Specified setting for Register 3 of I2C MUX 5 Click driver.
 */
#define I2CMUX5_SET_REG_3_BUS_1_SWITCH_OPEN          0x00
#define I2CMUX5_SET_REG_3_BUS_1_SWITCH_CLOSED        0x80
#define I2CMUX5_SET_REG_3_BUS_2_SWITCH_OPEN          0x00
#define I2CMUX5_SET_REG_3_BUS_2_SWITCH_CLOSED        0x40
#define I2CMUX5_SET_REG_3_BUS_3_SWITCH_OPEN          0x00
#define I2CMUX5_SET_REG_3_BUS_3_SWITCH_CLOSED        0x20
#define I2CMUX5_SET_REG_3_BUS_4_SWITCH_OPEN          0x00
#define I2CMUX5_SET_REG_3_BUS_4_SWITCH_CLOSED        0x10

/**
 * @brief I2C MUX 5 Channel Selection Status.
 * @details Specified setting for channel selection status of I2C MUX 5 Click driver.
 */
#define I2CMUX5_CH_SEL_ERROR                         0xFF

/**
 * @brief I2C MUX 5 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C MUX 5 Click driver.
 */
#define I2CMUX5_SET_DEV_ADDR                         0x44

/**
 * @brief I2C MUX 5 channel slave address setting.
 * @details Specified setting for channel slave address selection of
 * I2C MUX 5 Click driver.
 */
#define I2CMUX5_SET_6DOF_IMU_9_ADDR                  0x69
#define I2CMUX5_SET_6DOF_IMU_11_ADDR                 0x0E
#define I2CMUX5_SET_RTC_10_ADDR                      0x68
#define I2CMUX5_SET_ACCEL_10_ADDR                    0x18

/*! @} */ // i2cmux5_set

/**
 * @defgroup i2cmux5_map I2C MUX 5 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C MUX 5 Click driver.
 */

/**
 * @addtogroup sel_ch
 * @{
 */

/**
 * @brief I2C MUX 5 channel selection setting.
 * @details Specified setting for channel selection of
 * I2C MUX 5 Click driver.
 */
#define I2CMUX5_CH_1                                 0x01
#define I2CMUX5_CH_2                                 0x02
#define I2CMUX5_CH_3                                 0x03
#define I2CMUX5_CH_4                                 0x04

/*! @} */ // sel_ch

/**
 * @addtogroup pin_state
 * @{
 */

/**
 * @brief I2C MUX 5 channel selection setting.
 * @details Specified setting for channel selection of
 * I2C MUX 5 Click driver.
 */
#define I2CMUX5_PIN_STATE_LOW                    0
#define I2CMUX5_PIN_STATE_HIGH                   1


/*! @} */ // pin_state

/**
 * @addtogroup i2cmux5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C MUX 5 Click to the selected MikroBUS.
 */
#define I2CMUX5_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );    \
    cfg.ready = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // i2cmux5_map
/*! @} */ // i2cmux5

/**
 * @brief I2C MUX 5 Click context object.
 * @details Context object definition of I2C MUX 5 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  en;         /**< Description. */

    // Input pins

    digital_in_t  ready;       /**< Description. */
    digital_in_t  alert;       /**< Description. */

    // Modules

    i2c_master_t i2c;          /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;     /**< Device slave address (used for I2C driver). */

} i2cmux5_t;

/**
 * @brief I2C MUX 5 Click configuration object.
 * @details Configuration object definition of I2C MUX 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;         /**< Description. */
    pin_name_t  ready;      /**< Description. */
    pin_name_t  alert;      /**< Description. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} i2cmux5_cfg_t;

/*!
 * @addtogroup i2cmux5 I2C MUX 5 Click Driver
 * @brief API for configuring and manipulating I2C MUX 5 Click driver.
 * @{
 */

/**
 * @brief I2C MUX 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cmux5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void i2cmux5_cfg_setup ( i2cmux5_cfg_t *cfg );

/**
 * @brief I2C MUX 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cmux5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2cmux5_init ( i2cmux5_t *ctx, i2cmux5_cfg_t *cfg );

/**
 * @brief I2C MUX 5 default configuration function.
 * @details This function executes a default configuration of I2C MUX 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
void i2cmux5_default_cfg ( i2cmux5_t *ctx );

/**
 * @brief I2C MUX 5 HW reset function.
 * @details This function executes a hardware reset of I2C MUX 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 *
 * @endcode
 */
void i2cmux5_hw_reset ( i2cmux5_t *ctx );

/**
 * @brief I2C MUX 5 enable the device function.
 * @details This function executes power-up of the device and 
 * enables I2C communication of I2C MUX 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 *
 * @endcode
 */
void i2cmux5_dev_enable ( i2cmux5_t *ctx );

/**
 * @brief I2C MUX 5 check rdy function.
 * @details This function check connection ready digital output of I2C MUX 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @return @li @c  0 - None of the downstream channels is connected,
 *         @li @c  1 - One or more downstream channels is connected.
 *
 * @endcode
 */
uint8_t i2cmux5_check_rdy ( i2cmux5_t *ctx );

/**
 * @brief I2C MUX 5 check alert function.
 * @details This function check fault alert output of I2C MUX 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @return @li @c  0 - A fault occurs to alert the host controller,
 *         @li @c  1 - Passes this information to the master on the upstream bus.
 *
 * @endcode
 */
uint8_t i2cmux5_check_alert ( i2cmux5_t *ctx );

/**
 * @brief I2C MUX 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2cmux5_generic_write ( i2cmux5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief I2C MUX 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2cmux5_generic_read ( i2cmux5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief I2C MUX 5 check channel alert function.
 * @details This function reads a desired channel alert status of I2C MUX 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @param[in] ch_numb : The number of the desired channel ( from 1 to 4 ).
 * @param[in] rx_len : Number of bytes to be read.
 * @return Alert status on the selected channel:
 *         @li @c   0 - Inactive,
 *         @li @c   1 - Active,
 *         @li @c 255 - Error, wrong channel selection.
 * 
 * @note None.
 *
 * @endcode
 */
uint8_t i2cmux5_check_ch_alert ( i2cmux5_t *ctx, uint8_t n_channel );

/**
 * @brief I2C MUX 5 I2C channel writing function.
 * @details This function writes via desired channel 
 * a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @param[in] sel_ch : Number of the desired channel ( from 1 to 4 ).
 * @param[in] ch_slave_addr : Slave address of the device connected to the desired channel.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 *
 * @note None.
 *
 * @endcode
 */
void i2cmux5_channel_write_byte ( i2cmux5_t *ctx, uint8_t sel_ch, uint8_t ch_slave_addr, uint8_t reg, uint8_t tx_data );

/**
 * @brief I2C MUX 5 I2C channel reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cmux5_t object definition for detailed explanation.
 * @param[in] sel_ch : Number of the desired channel ( from 1 to 4 ).
 * @param[in] ch_slave_addr : Slave address of the device connected to the desired channel.
 * @param[in] reg : Start register address.
 * @return Output read data.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t i2cmux5_channel_read_byte ( i2cmux5_t *ctx, uint8_t sel_ch, uint8_t ch_slave_addr, uint8_t reg );

#ifdef __cplusplus
}
#endif
#endif // I2CMUX5_H

/*! @} */ // i2cmux5

// ------------------------------------------------------------------------ END
