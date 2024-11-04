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
 * @file thermo20.h
 * @brief This file contains API for Thermo 20 Click Driver.
 */

#ifndef THERMO20_H
#define THERMO20_H

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
 * @addtogroup thermo20 Thermo 20 Click Driver
 * @brief API for configuring and manipulating Thermo 20 Click driver.
 * @{
 */

/**
 * @defgroup thermo20_reg Thermo 20 Registers List
 * @brief List of registers of Thermo 20 Click driver.
 */

/**
 * @addtogroup thermo20_reg
 * @{
 */

/**
 * @brief Thermo 20 description register.
 * @details Specified register for description of Thermo 20 Click driver.
 */
#define THERMO20_CMD_RESET                  0x1E
#define THERMO20_CMD_READ_SERIAL_NUMBER     0x0A
#define THERMO20_CMD_CONVERSION             0x46
#define THERMO20_CMD_READ_ADC               0x00

/*! @} */ // thermo20_reg

/**
 * @defgroup thermo20_set Thermo 20 Registers Settings
 * @brief Settings for registers of Thermo 20 Click driver.
 */

/**
 * @addtogroup thermo20_set
 * @{
 */

/**
 * @brief Thermo 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 20 Click driver.
 */
#define THERMO20_SET_DEV_ADDR               0x40

/*! @} */ // thermo20_set

/**
 * @defgroup thermo20_map Thermo 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 20 Click driver.
 */

/**
 * @addtogroup thermo20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 20 Click to the selected MikroBUS.
 */
#define THERMO20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); 

/*! @} */ // thermo20_map
/*! @} */ // thermo20

/**
 * @brief Thermo 20 Click context object.
 * @details Context object definition of Thermo 20 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} thermo20_t;

/**
 * @brief Thermo 20 Click configuration object.
 * @details Configuration object definition of Thermo 20 Click driver.
 */
typedef struct
{
    pin_name_t  scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} thermo20_cfg_t;

/**
 * @brief Thermo 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   THERMO20_OK = 0,
   THERMO20_ERROR = -1

} thermo20_return_value_t;

/*!
 * @addtogroup thermo20 Thermo 20 Click Driver
 * @brief API for configuring and manipulating Thermo 20 Click driver.
 * @{
 */

/**
 * @brief Thermo 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo20_cfg_setup ( thermo20_cfg_t *cfg );

/**
 * @brief Thermo 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo20_init ( thermo20_t *ctx, thermo20_cfg_t *cfg );

/**
 * @brief Thermo 20 default configuration function.
 * @details This function executes a default configuration of Thermo 20
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo20_default_cfg ( thermo20_t *ctx );

/**
 * @brief Thermo 20 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo20_generic_write ( thermo20_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Thermo 20 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo20_generic_read ( thermo20_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Send command function.
 * @details The function send the desired command
 * to the TSYS03 Digital Temperature Sensor on the Thermo 20 Click board.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @param[in] cmd Commands byte.
 * See #thermo20_reg defgroup for detailed explanation. * 
 *  @return @li @c  0 - Success,
 *          @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t thermo20_set_cmd ( thermo20_t *ctx, uint8_t cmd );

/**
 * @brief Soft reset function.
 * @details The function is performed by a software reset
 * of the TSYS03 Digital Temperature Sensor on the Thermo 20 Click board.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @return Nothing.
 */
void thermo20_soft_reset ( thermo20_t *ctx );

/**
 * @brief Start conversion function.
 * @details The function set conversion a single temperature conversion
 * of the TSYS03 Digital Temperature Sensor on the Thermo 20 Click board.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @return Nothing.
 * @note A conversion must be started and conducted before the ADC result can be read.
 * he typical conversion time is 12 milliseconds.
 */
void thermo20_start_conversion ( thermo20_t *ctx );

/**
 * @brief Read ADC data function.
 * @details The function 16-bit temperature reprinting ADC result
 * of the TSYS03 Digital Temperature Sensor on the Thermo 20 Click board.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @return 16-bit temperature reprinting ADC result.
 */
uint16_t thermo20_read_adc ( thermo20_t *ctx );

/**
 * @brief Get temperature data function.
 * @details The function get temperature value in degree Celsius
 * of the TSYS03 Digital Temperature Sensor on the Thermo 20 Click board.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @return  float temperature value in degree Celsius.
 */
float thermo20_get_temperature ( thermo20_t *ctx );

/**
 * @brief Get serial number function.
 * @details The function get the serial number
 * of the TSYS03 Digital Temperature Sensor on the Thermo 20 Click board.
 * @param[in] ctx : Click context object.
 * See #thermo20_t object definition for detailed explanation.
 * @return 24-bit serial number.
 */
uint32_t thermo20_get_serial_number ( thermo20_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // THERMO20_H

/*! @} */ // thermo20

// ------------------------------------------------------------------------ END
