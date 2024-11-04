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
 * @file ambient16.h
 * @brief This file contains API for Ambient 16 Click Driver.
 */

#ifndef AMBIENT16_H
#define AMBIENT16_H

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

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ambient16 Ambient 16 Click Driver
 * @brief API for configuring and manipulating Ambient 16 Click driver.
 * @{
 */

/**
 * @defgroup ambient16_reg Ambient 16 Registers List
 * @brief List of registers of Ambient 16 Click driver.
 */

/**
 * @addtogroup ambient16_reg
 * @{
 */

/**
 * @brief Ambient 16 description register.
 * @details Specified register for description of Ambient 16 Click driver.
 */
#define AMBIENT16_CONTROL_REG               0x00
#define AMBIENT16_TIMING_REG                0x01
#define AMBIENT16_INTERRUPT_REG             0x02
#define AMBIENT16_TH_LOW_LSB_REG            0x03
#define AMBIENT16_TH_LOW_MSB_REG            0x04
#define AMBIENT16_TH_HIGH_LSB_REG           0x05
#define AMBIENT16_TH_HIGH_MSB_REG           0x06
#define AMBIENT16_GAIN_REG                  0x07
#define AMBIENT16_PART_ID_REG               0x12
#define AMBIENT16_DATA0_LSB_REG             0x14
#define AMBIENT16_DATA0_MSB_REG             0x15
#define AMBIENT16_DATA1_LSB_REG             0x16
#define AMBIENT16_DATA1_MSB_REG             0x17
#define AMBIENT16_WAIT_REG                  0x18

/*! @} */ // ambient16_reg

/**
 * @defgroup ambient16_set Ambient 16 Registers Settings
 * @brief Settings for registers of Ambient 16 Click driver.
 */

/**
 * @addtogroup ambient16_set
 * @{
 */

/**
 * @brief Ambient 16 description setting.
 * @details Specified setting for description of Ambient 16 Click driver.
 */

/**
 * @brief Ambient 16 commands.
 * @details Specified commands of Ambient 16 Click driver.
 */
#define AMBIENT16_SOFTWARE_RESET                                0xE4
#define AMBIENT16_INTERRUPT_RESET                               0xE1

/**
 * @brief Ambient 16 interrupt settings.
 * @details Specified interrupt setting for description of Ambient 16 Click driver.
 */
#define AMBIENT16_ADC_INTERRUPT_ENABLE                          0x20
#define AMBIENT16_ADC_ENABLE                                    0x02
#define AMBIENT16_POWER_ENABLE                                  0x01

#define AMBIENT16_UNLATCH_MODE                                  0x20
#define AMBIENT16_LATCH_MODE                                    0x00

#define AMBIENT16_INTERRUPT_ENABLE                              0x10
#define AMBIENT16_INTERRUPT_DISABLE                             0x00

/**
 * @brief Ambient 16 interrupt mode settings.
 * @details Specified interrupt mode setting for description of Ambient 16 Click driver.
 */
#define AMBIENT16_INT_ACTIVE_ON_END_OF_MEASURMENT               0x00
#define AMBIENT16_INT_UPDATE_ON_END_OF_MEASURMENT               0x01
#define AMBIENT16_INT_UPDATE_ON_2_CONSEC_TRESHOLDS              0x02
#define AMBIENT16_INT_UPDATE_ON_3_CONSEC_TRESHOLDS              0x03
#define AMBIENT16_INT_UPDATE_ON_4_CONSEC_TRESHOLDS              0x04
#define AMBIENT16_INT_UPDATE_ON_5_CONSEC_TRESHOLDS              0x05
#define AMBIENT16_INT_UPDATE_ON_6_CONSEC_TRESHOLDS              0x06
#define AMBIENT16_INT_UPDATE_ON_7_CONSEC_TRESHOLDS              0x07
#define AMBIENT16_INT_UPDATE_ON_8_CONSEC_TRESHOLDS              0x08
#define AMBIENT16_INT_UPDATE_ON_9_CONSEC_TRESHOLDS              0x09
#define AMBIENT16_INT_UPDATE_ON_10_CONSEC_TRESHOLDS             0x0A
#define AMBIENT16_INT_UPDATE_ON_11_CONSEC_TRESHOLDS             0x0B
#define AMBIENT16_INT_UPDATE_ON_12_CONSEC_TRESHOLDS             0x0C
#define AMBIENT16_INT_UPDATE_ON_13_CONSEC_TRESHOLDS             0x0D
#define AMBIENT16_INT_UPDATE_ON_14_CONSEC_TRESHOLDS             0x0E
#define AMBIENT16_INT_UPDATE_ON_15_CONSEC_TRESHOLDS             0x0F

/**
 * @brief Ambient 16 gain mode settings.
 * @details Specified gain mode setting for description of Ambient 16 Click driver.
 */
#define AMBIENT16_X1_GAIN                                       0x00
#define AMBIENT16_X2_GAIN                                       0x01
#define AMBIENT16_X64_GAIN                                      0x02
#define AMBIENT16_X128_GAIN                                     0x03

/**
 * @brief Ambient 16 wait settings.
 * @details Specified wait setting for description of Ambient 16 Click driver.
 */
#define AMBIENT16_ENABLE_WAIT                                   0x01
#define AMBIENT16_DISABLE_WAIT                                  0x00

/**
 * @brief Ambient 16 INT pin state.
 * @details Specified INT pin state of Ambient 16 Click driver.
 */
#define AMBIENT16_INT_STATE_HIGH                                0x01
#define AMBIENT16_INT_STATE_LOW                                 0x00

/**
 * @brief Ambient 16 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 16 Click driver.
 */
#define AMBIENT16_I2C_SLAVE_ADR_0                               0x29
#define AMBIENT16_I2C_SLAVE_ADR_1                               0x39

/*! @} */ // ambient16_set

/**
 * @defgroup ambient16_map Ambient 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 16 Click driver.
 */

/**
 * @addtogroup ambient16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 16 Click to the selected MikroBUS.
 */
#define AMBIENT16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient16_map
/*! @} */ // ambient16

/**
 * @brief Ambient 16 Click context object.
 * @details Context object definition of Ambient 16 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;       /**< Interrupt. */

    // Modules
    i2c_master_t i2c;            /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;       /**< Device slave address (used for I2C driver). */

} ambient16_t;

/**
 * @brief Ambient 16 Click configuration object.
 * @details Configuration object definition of Ambient 16 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;    /**< Interrupt. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} ambient16_cfg_t;

/**
 * @brief Ambient 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT16_OK = 0,
    AMBIENT16_ERROR = -1

} ambient16_return_value_t;

/*!
 * @addtogroup ambient16 Ambient 16 Click Driver
 * @brief API for configuring and manipulating Ambient 16 Click driver.
 * @{
 */

/**
 * @brief Ambient 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient16_cfg_setup ( ambient16_cfg_t *cfg );

/**
 * @brief Ambient 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_init ( ambient16_t *ctx, ambient16_cfg_t *cfg );

/**
 * @brief Ambient 16 default configuration function.
 * @details This function executes a default configuration of Ambient 16
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient16_default_cfg ( ambient16_t *ctx );

/**
 * @brief Ambient 16 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_generic_write ( ambient16_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Ambient 16 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_generic_read ( ambient16_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Ambient 16 get INT state function.
 * @details This function reads a state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @return @li @c 1 - Pin state high,
 *         @li @c 0 - Pin state low.
 */
uint8_t ambient16_get_int_state ( ambient16_t *ctx );

/**
 * @brief Ambient 16 set register value function.
 * @details This function writes a desired value into a selected 
 * register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] value : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_set_reg ( ambient16_t *ctx, uint8_t reg, uint8_t value );

/**
 * @brief Ambient 16 send command function.
 * @details This function sends a desired command by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] cmd : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_send_cmd ( ambient16_t *ctx, uint8_t cmd );

/**
 * @brief Ambient 16 software reset function.
 * @details This function executes a software reset of Ambient 16 Click board.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_sw_reset ( ambient16_t *ctx );

/**
 * @brief Ambient 16 interrupt reset function.
 * @details This function executes an interrupt reset of Ambient 16 Click board.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_int_reset ( ambient16_t *ctx );

/**
 * @brief Ambient 16 set interrupt threshold lower level function.
 * @details This function is used for setting interrupt threshold lower level 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] th_val : Treshold data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_set_th_low ( ambient16_t *ctx, uint16_t th_val );

/**
 * @brief Ambient 16 set interrupt threshold upper level function.
 * @details This function is used for setting interrupt threshold upper level 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] th_val : Treshold data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_set_th_high ( ambient16_t *ctx, uint16_t th_val );

/**
 * @brief Ambient 16 set ADC gain function.
 * @details This function is used for setting ADC gain mode 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] data0_gain : Gain setting of ADC for DATA0.
 * @param[in] data1_gain : Gain setting of ADC for DATA1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_set_gain ( ambient16_t *ctx, uint8_t data0_gain, uint8_t data1_gain );

/**
 * @brief Ambient 16 get part ID function.
 * @details This function is used for reading part ID 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[out] part_id : Part ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_get_part_id ( ambient16_t *ctx, uint8_t *part_id );

/**
 * @brief Ambient 16 get ADC data function.
 * @details This function is used for reading ADC data from DATA0 and DATA1 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[out] data0 : Output read data from DATA0.
 * @param[out] data1 : Output read data from DATA1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_get_data ( ambient16_t *ctx, uint16_t *data0, uint16_t *data1 );

/**
 * @brief Ambient 16 get data function.
 * @details This function is used for reading data from DATA0 and DATA1 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[out] data0 : Output read data from DATA0 in lux.
 * @param[out] data1 : Output read data from DATA1 in lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ambient16_read_data ( ambient16_t *ctx, float *data0, float *data1 );

/**
 * @brief Ambient 16 set wait function.
 * @details This function is used for enabling wait mode 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient16_t object definition for detailed explanation.
 * @param[in] wait_mode : Wait mode data.
 * @return Nothing.
 * @note If wait function is enabled there is interval ( Twt ) after each measurment.
 */
void ambient16_set_wait ( ambient16_t *ctx, uint8_t wait_mode );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT16_H

/*! @} */ // ambient16

// ------------------------------------------------------------------------ END
