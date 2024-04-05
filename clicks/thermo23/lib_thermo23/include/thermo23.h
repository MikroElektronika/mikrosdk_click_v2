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
 * @file thermo23.h
 * @brief This file contains API for Thermo 23 Click Driver.
 */

#ifndef THERMO23_H
#define THERMO23_H

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
#include "drv_uart.h"

/*!
 * @addtogroup thermo23 Thermo 23 Click Driver
 * @brief API for configuring and manipulating Thermo 23 Click driver.
 * @{
 */

/**
 * @defgroup thermo23_cmd Thermo 23 Device Settings
 * @brief Settings for registers of Thermo 23 Click driver.
 */

/**
 * @addtogroup thermo23_cmd
 * @{
 */

/**
 * @brief Thermo 23 control commands.
 * @details Specified setting for control commands of Thermo 23 Click driver.
 */
#define THERMO23_CMD_SOFT_RESET             0xB4
#define THERMO23_CMD_GLOBAL_INIT            0x8C
#define THERMO23_CMD_GLOBAL_ADDRESS_ASSIGN  0x90
#define THERMO23_CMD_GLOBAL_CLEAR_INT       0xA9
#define THERMO23_CMD_GLOBAL_WRITE_TEMP      0xF0
#define THERMO23_CMD_GLOBAL_WRITE_CONFIG    0xF2
#define THERMO23_CMD_GLOBAL_WRITE_TLOW      0xF4
#define THERMO23_CMD_GLOBAL_WRITE_THIGH     0xF6
#define THERMO23_CMD_GLOBAL_READ_TEMP       0xF1
#define THERMO23_CMD_GLOBAL_READ_CONFIG     0xF3
#define THERMO23_CMD_GLOBAL_READ_TLOW       0xF5
#define THERMO23_CMD_GLOBAL_READ_THIGH      0xF7
#define THERMO23_CMD_INDIVIDUAL_WRITE_BIT   0x00
#define THERMO23_CMD_INDIVIDUAL_READ_BIT    0x01

/**
 * @brief Thermo 23 calibration byte.
 * @details Specified calibration byte of Thermo 23 Click driver.
 */
#define THERMO23_CALIBRATION_BYTE           0x55

/**
 * @brief Thermo 23 timeout value in milliseconds.
 * @details Specified timeout value in milliseconds of Thermo 23 Click driver.
 */
#define THERMO23_TIMEOUT                    5000

/**
 * @brief Thermo 23 config register settings.
 * @details Specified config register settings of Thermo 23 Click driver.
 */
#define THERMO23_CONFIG_INT_EN              0x8000
#define THERMO23_CONFIG_CR_0p25HZ           0x0000
#define THERMO23_CONFIG_CR_1HZ              0x2000
#define THERMO23_CONFIG_CR_4HZ              0x4000
#define THERMO23_CONFIG_CR_8HZ              0x6000
#define THERMO23_CONFIG_FH                  0x1000
#define THERMO23_CONFIG_FL                  0x0800
#define THERMO23_CONFIG_LC                  0x0400
#define THERMO23_CONFIG_MODE_SHUTDOWN       0x0000
#define THERMO23_CONFIG_MODE_ONE_SHOT       0x0100
#define THERMO23_CONFIG_MODE_CONTINUOUS     0x0200
#define THERMO23_CONFIG_ETM                 0x0080
#define THERMO23_CONFIG_RESERVED_BITS       0x007F

/**
 * @brief Thermo 23 temperature resolution.
 * @details Specified temperature resolution of Thermo 23 Click driver.
 */
#define THERMO23_TEMP_RESOLUTION            0.0625

/**
 * @brief Thermo 23 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                     200

/*! @} */ // thermo23_cmd

/**
 * @defgroup thermo23_map Thermo 23 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 23 Click driver.
 */

/**
 * @addtogroup thermo23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 23 Click to the selected MikroBUS.
 */
#define THERMO23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );

/*! @} */ // thermo23_map
/*! @} */ // thermo23

/**
 * @brief Thermo 23 Click context object.
 * @details Context object definition of Thermo 23 Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    
    uint16_t config;                            /**< Config register settings. */

} thermo23_t;

/**
 * @brief Thermo 23 Click configuration object.
 * @details Configuration object definition of Thermo 23 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} thermo23_cfg_t;

/**
 * @brief Thermo 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO23_OK = 0,
    THERMO23_ERROR = -1

} thermo23_return_value_t;

/*!
 * @addtogroup thermo23 Thermo 23 Click Driver
 * @brief API for configuring and manipulating Thermo 23 Click driver.
 * @{
 */

/**
 * @brief Thermo 23 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo23_cfg_setup ( thermo23_cfg_t *cfg );

/**
 * @brief Thermo 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo23_init ( thermo23_t *ctx, thermo23_cfg_t *cfg );

/**
 * @brief Thermo 23 default configuration function.
 * @details This function executes a default configuration of Thermo 23
 * click board.
 * @param[in] ctx : Click context object.
 * See #thermo23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo23_default_cfg ( thermo23_t *ctx );

/**
 * @brief Thermo 23 write command function.
 * @details This function writes a desired data to the selected command by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo23_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error/Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo23_write_command ( thermo23_t *ctx, uint8_t cmd, uint16_t data_in );

/**
 * @brief Thermo 23 read command function.
 * @details This function reads data from the selected command by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo23_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error/Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo23_read_command ( thermo23_t *ctx, uint8_t cmd, uint16_t *data_out );

/**
 * @brief Thermo 23 set config function.
 * @details This function sets the configuration register.
 * @param[in] ctx : Click context object.
 * See #thermo23_t object definition for detailed explanation.
 * @param[in] config : Config register value to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error/Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo23_set_config ( thermo23_t *ctx, uint16_t config );

/**
 * @brief Thermo 23 read temperature function.
 * @details This function reads the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo23_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error/Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo23_read_temperature ( thermo23_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // THERMO23_H

/*! @} */ // thermo23

// ------------------------------------------------------------------------ END
