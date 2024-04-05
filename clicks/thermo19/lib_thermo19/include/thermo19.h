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
 * @file thermo19.h
 * @brief This file contains API for Thermo 19 Click Driver.
 */

#ifndef THERMO19_H
#define THERMO19_H

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
#include "drv_one_wire.h"

/*!
 * @addtogroup thermo19 Thermo 19 Click Driver
 * @brief API for configuring and manipulating Thermo 19 Click driver.
 * @{
 */

/**
 * @defgroup thermo19_cmd Thermo 19 Commands List
 * @brief List of commands of Thermo 19 Click driver.
 */

/**
 * @addtogroup thermo19_cmd
 * @{
 */

/**
 * @brief Thermo 19 commands list.
 * @details Specified commands list of Thermo 19 Click driver.
 */
#define THERMO19_CMD_CONVERT_TEMPERATURE            0x44
#define THERMO19_CMD_WRITE_SCRATCHPAD               0x4E
#define THERMO19_CMD_READ_SCRATCHPAD                0xBE
#define THERMO19_CMD_DETECT_ADDRESS                 0x88
#define THERMO19_CMD_SELECT_ADDRESS                 0x70

/*! @} */ // thermo19_cmd

/**
 * @defgroup thermo19_set Thermo 19 Settings
 * @brief Settings of Thermo 19 Click driver.
 */

/**
 * @addtogroup thermo19_set
 * @{
 */

/**
 * @brief Thermo 19 config register settings.
 * @details Specified config register settings of Thermo 19 Click driver.
 */
#define THERMO19_CONFIG_FORMAT_NORMAL               0x00
#define THERMO19_CONFIG_FORMAT_EXTEND               0x80
#define THERMO19_CONFIG_FORMAT_BIT_MASK             0x80
#define THERMO19_CONFIG_RESOLUTION_8BIT             0x00
#define THERMO19_CONFIG_RESOLUTION_9BIT             0x20
#define THERMO19_CONFIG_RESOLUTION_10BIT            0x40
#define THERMO19_CONFIG_RESOLUTION_12BIT            0x60
#define THERMO19_CONFIG_RESOLUTION_BIT_MASK         0x60
#define THERMO19_CONFIG_COMP_INT_COMPARATOR         0x00
#define THERMO19_CONFIG_COMP_INT_INTERRUPT          0x10
#define THERMO19_CONFIG_COMP_INT_BIT_MASK           0x10
#define THERMO19_CONFIG_FAULT_QUEUE_SINGLE          0x00
#define THERMO19_CONFIG_FAULT_QUEUE_MULTIPLE        0x08
#define THERMO19_CONFIG_FAULT_QUEUE_BIT_MASK        0x08
#define THERMO19_CONFIG_CONVERSION_RATE_0           0x00
#define THERMO19_CONFIG_CONVERSION_RATE_1_64        0x01
#define THERMO19_CONFIG_CONVERSION_RATE_1_32        0x02
#define THERMO19_CONFIG_CONVERSION_RATE_1_16        0x03
#define THERMO19_CONFIG_CONVERSION_RATE_1_4         0x04
#define THERMO19_CONFIG_CONVERSION_RATE_1_1         0x05
#define THERMO19_CONFIG_CONVERSION_RATE_4_1         0x06
#define THERMO19_CONFIG_CONVERSION_RATE_8_1         0x07
#define THERMO19_CONFIG_CONVERSION_RATE_BIT_MASK    0x07

/**
 * @brief Thermo 19 status register settings.
 * @details Specified status register settings of Thermo 19 Click driver.
 */
#define THERMO19_STATUS_TH_FAULT_OCCURED            0x80
#define THERMO19_STATUS_TH_FAULT_NOT_OCCURED        0x00
#define THERMO19_STATUS_TH_FAULT_BIT_MASK           0x80
#define THERMO19_STATUS_TL_FAULT_OCCURED            0x40
#define THERMO19_STATUS_TL_FAULT_NOT_OCCURED        0x00
#define THERMO19_STATUS_TL_FAULT_BIT_MASK           0x40
#define THERMO19_STATUS_ADDRRESS_0                  0x1A
#define THERMO19_STATUS_ADDRRESS_1                  0x3A
#define THERMO19_STATUS_ADDRRESS_BIT_MASK           0x3F

/**
 * @brief Thermo 19 address settings.
 * @details Specified address settings of Thermo 19 Click driver.
 */
#define THERMO19_ADDRESS_0                          0x1A
#define THERMO19_ADDRESS_1                          0x3A
#define THERMO19_ADDRESS_ALL                        0xFF
#define THERMO19_ADDRESS_BIT_MASK                   0x3F

/**
 * @brief Thermo 19 temperature calculation values.
 * @details Specified temperature calculation values of Thermo 19 Click driver.
 */
#define THERMO19_DATA_RESOLUTION                    0.0625

/**
 * @brief Thermo 19 family code value.
 * @details Specified family code value of Thermo 19 Click driver.
 */
#define THERMO19_FAMILY_CODE                        0x3B

/**
 * @brief Thermo 19 default config values.
 * @details Specified default config values of Thermo 19 Click driver.
 */
#define THERMO19_DEFAULT_CONFIG                     ( THERMO19_CONFIG_RESOLUTION_12BIT | THERMO19_CONFIG_COMP_INT_INTERRUPT )
#define THERMO19_DEFAULT_ADDRESS                    THERMO19_ADDRESS_ALL
#define THERMO19_DEFAULT_TEMP_HIGH_ALARM            0xFFFF
#define THERMO19_DEFAULT_TEMP_LOW_ALARM             0x0000

/*! @} */ // thermo19_set

/**
 * @defgroup thermo19_map Thermo 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 19 Click driver.
 */

/**
 * @addtogroup thermo19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 19 Click to the selected MikroBUS.
 */

#define THERMO19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // thermo19_map
/*! @} */ // thermo19

/**
 * @brief Thermo 19 Click gpio selector.
 * @details Selects gpio pin of Thermo 19 Click driver.
 */
typedef enum
{
    THERMO19_GPIO_0,      /**< GPIO 0 pin. */
    THERMO19_GPIO_1       /**< GPIO 1 pin. */

} thermo19_gpio_sel_t;

/**
 * @brief Thermo 19 Click context object.
 * @details Context object definition of Thermo 19 Click driver.
 */
typedef struct
{
    digital_in_t alt;                   /**< Alert pin. */
    
    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */
    
    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t config;                     /**< Device configuration register setting. */
    uint8_t address;                    /**< Device address selection. */
    
} thermo19_t;

/**
 * @brief Thermo 19 Click configuration object.
 * @details Configuration object definition of Thermo 19 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;                     /**< GPIO 0 pin. */
    pin_name_t gp1;                     /**< GPIO 1 pin. */
    pin_name_t alt;                     /**< Alert pin. */
    
    thermo19_gpio_sel_t gpio_sel;       /**< GPIO selection. */

} thermo19_cfg_t;

/**
 * @brief Thermo 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO19_OK = 0,
    THERMO19_ERROR = -1

} thermo19_return_value_t;

/*!
 * @addtogroup thermo19 Thermo 19 Click Driver
 * @brief API for configuring and manipulating Thermo 19 Click driver.
 * @{
 */

/**
 * @brief Thermo 19 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo19_cfg_setup ( thermo19_cfg_t *cfg );

/**
 * @brief Thermo 19 driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #thermo19_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #thermo19_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void thermo19_gpio_selection ( thermo19_cfg_t *cfg, thermo19_gpio_sel_t gpio_sel );

/**
 * @brief Thermo 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo19_init ( thermo19_t *ctx, thermo19_cfg_t *cfg );

/**
 * @brief Thermo 19 default configuration function.
 * @details This function executes a default configuration of Thermo 19
 * click board.
 * @param[in] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo19_default_cfg ( thermo19_t *ctx );

/**
 * @brief Thermo 19 check communication function.
 * @details This function checks the communication by reading the ROM address twice and comparing
 * the two results, as well as verifying the family code byte.
 * @param[in] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo19_check_communication ( thermo19_t *ctx );

/**
 * @brief Thermo 19 select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the configuration byte.
 * @param[in] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo19_select_device ( thermo19_t *ctx );

/**
 * @brief Thermo 19 start measurement function.
 * @details This function starts the measurement by sending an appropriate command for that.
 * @param[in] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo19_start_measurement ( thermo19_t *ctx );

/**
 * @brief Thermo 19 read scratchpad function.
 * @details This function reads the scratchpad bytes.
 * @param[in] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @param[out] scratchpad : Scratchpad [5-bytes] of device with the address set in @b ctx->config.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo19_read_scratchpad ( thermo19_t *ctx, uint8_t *scratchpad );

/**
 * @brief Thermo 19 write scratchpad function.
 * @details This function writes the temperature thresholds and configuration byte to the scratchpad.
 * @param[in] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @param[in] temp_high : Temperature high limit.
 * @param[in] temp_low : Temperature low limit.
 * @param[in] config : Configuration byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo19_write_scratchpad ( thermo19_t *ctx, uint16_t temp_high, uint16_t temp_low, uint8_t config );

/**
 * @brief Thermo 19 read temperature function.
 * @details This function reads the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo19_read_temperature ( thermo19_t *ctx, float *temperature );

/**
 * @brief Thermo 19 get alert pin function.
 * @details Reads the current input value of the ALT pin.
 * @param[in] ctx : Click context object.
 * See #thermo19_t object definition for detailed explanation.
 * @return Function returns pin logical state (1 or 0).
 * @note None.
 */
uint8_t thermo19_get_alert_pin ( thermo19_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // THERMO19_H

/*! @} */ // thermo19

// ------------------------------------------------------------------------ END
