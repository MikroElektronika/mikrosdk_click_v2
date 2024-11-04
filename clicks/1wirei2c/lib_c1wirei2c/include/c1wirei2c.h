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
 * @file c1wirei2c.h
 * @brief This file contains API for 1-Wire I2C Click Driver.
 */

#ifndef C1WIREI2C_H
#define C1WIREI2C_H

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
 * @addtogroup c1wirei2c 1-Wire I2C Click Driver
 * @brief API for configuring and manipulating 1-Wire I2C Click driver.
 * @{
 */

/**
 * @defgroup c1wirei2c_cmd 1-Wire I2C Commands List
 * @brief List of commands of 1-Wire I2C Click driver.
 */

/**
 * @addtogroup c1wirei2c_cmd
 * @{
 */

/**
 * @brief 1-Wire I2C commands list.
 * @details Specified commands list of 1-Wire I2C Click driver.
 */
#define C1WIREI2C_CMD_WRITE_DATA_WITH_STOP      0x4B
#define C1WIREI2C_CMD_WRITE_DATA_NO_STOP        0x5A
#define C1WIREI2C_CMD_WRITE_DATA_ONLY           0x69
#define C1WIREI2C_CMD_WRITE_DATA_ONLY_WITH_STOP 0x78
#define C1WIREI2C_CMD_READ_DATA_WITH_STOP       0x87
#define C1WIREI2C_CMD_WRITE_READ_DATA_WITH_STOP 0x2D
#define C1WIREI2C_CMD_WRITE_CONFIGURATION       0xD2
#define C1WIREI2C_CMD_READ_CONFIGURATION        0xE1
#define C1WIREI2C_CMD_ENABLE_SLEEP_MODE         0x1E
#define C1WIREI2C_CMD_READ_DEVICE_REVISION      0xC3

/*! @} */ // c1wirei2c_cmd

/**
 * @defgroup c1wirei2c_set 1-Wire I2C Settings
 * @brief Settings of 1-Wire I2C Click driver.
 */

/**
 * @addtogroup c1wirei2c_set
 * @{
 */

/**
 * @brief 1-Wire I2C configuration register settings.
 * @details Specified configuration register settings of 1-Wire I2C Click driver.
 */
#define C1WIREI2C_CONFIGURATION_SPD_100KHZ      0x00
#define C1WIREI2C_CONFIGURATION_SPD_400KHZ      0x01
#define C1WIREI2C_CONFIGURATION_SPD_900KHZ      0x02
#define C1WIREI2C_CONFIGURATION_SPD_MASK        0x03

/**
 * @brief 1-Wire I2C family code value.
 * @details Specified family code value of 1-Wire I2C Click driver.
 */
#define C1WIREI2C_FAMILY_CODE                   0x19

/**
 * @brief 1-Wire I2C address selection macros.
 * @details Specified address selection macros of 1-Wire I2C Click driver.
 */
#define C1WIREI2C_ADDRESS_0                     0x00
#define C1WIREI2C_ADDRESS_ALL                   0xFF

/*! @} */ // c1wirei2c_set

/**
 * @defgroup c1wirei2c_map 1-Wire I2C MikroBUS Map
 * @brief MikroBUS pin mapping of 1-Wire I2C Click driver.
 */

/**
 * @addtogroup c1wirei2c_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 1-Wire I2C Click to the selected MikroBUS.
 */
#define C1WIREI2C_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ow2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ow1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // c1wirei2c_map
/*! @} */ // c1wirei2c

/**
 * @brief 1-Wire I2C Click gpio selector.
 * @details Selects gpio pin of 1-Wire I2C Click driver.
 */
typedef enum
{
    C1WIREI2C_GPIO_OW1,                 /**< GPIO OW1 pin. */
    C1WIREI2C_GPIO_OW2                  /**< GPIO OW2 pin. */

} c1wirei2c_gpio_sel_t;

/**
 * @brief 1-Wire I2C Click context object.
 * @details Context object definition of 1-Wire I2C Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Reset pin (Active low). */

    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t address;                    /**< Device address selection. */

} c1wirei2c_t;

/**
 * @brief 1-Wire I2C Click configuration object.
 * @details Configuration object definition of 1-Wire I2C Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t ow1;                     /**< GPIO OW1 pin. */
    pin_name_t ow2;                     /**< GPIO OW2 pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin (Active low). */

    c1wirei2c_gpio_sel_t gpio_sel;      /**< GPIO selection. */

} c1wirei2c_cfg_t;

/**
 * @brief 1-Wire I2C Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C1WIREI2C_OK = 0,
    C1WIREI2C_ERROR = -1

} c1wirei2c_return_value_t;

/*!
 * @addtogroup c1wirei2c 1-Wire I2C Click Driver
 * @brief API for configuring and manipulating 1-Wire I2C Click driver.
 * @{
 */

/**
 * @brief 1-Wire I2C configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c1wirei2c_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c1wirei2c_cfg_setup ( c1wirei2c_cfg_t *cfg );

/**
 * @brief 1-Wire I2C driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c1wirei2c_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #c1wirei2c_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c1wirei2c_gpio_selection ( c1wirei2c_cfg_t *cfg, c1wirei2c_gpio_sel_t gpio_sel );

/**
 * @brief 1-Wire I2C initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c1wirei2c_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_init ( c1wirei2c_t *ctx, c1wirei2c_cfg_t *cfg );

/**
 * @brief 1-Wire I2C default configuration function.
 * @details This function executes a default configuration of 1-Wire I2C
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c1wirei2c_default_cfg ( c1wirei2c_t *ctx );

/**
 * @brief 1-Wire I2C check communication function.
 * @details This function checks the communication by reading the ROM address 
 * as well as verifying family code and CRC 8.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_check_communication ( c1wirei2c_t *ctx );

/**
 * @brief 1-Wire I2C select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the @b ctx->address.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_select_device ( c1wirei2c_t *ctx );

/**
 * @brief 1-Wire I2C write data stop function.
 * @details This function is used to address and write 1-255 bytes to an I2C slave in one transaction.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] slave_addr : 7-bit slave address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_write_data_stop ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief 1-Wire I2C write data function.
 * @details This function addresses and writes 1-255 bytes to an I2C slave without completing the transaction with a stop.
 * It allows writing large amounts of data at one time when used in conjunction with the c1wirei2c_write_data_only or
 * c1wirei2c_write_data_only_stop functions. 
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] slave_addr : 7-bit slave address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_write_data ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief 1-Wire I2C write data only function.
 * @details This function is used when a start and I2C address have previously been issued with a Write Data No Stop Device
 * command. It writes 1-255 bytes to an I2C slave without completing the transaction with a stop and enables writing large amounts
 * of data at one time when used with more Write Data Only or a last Write Data Only with Stop Device commands. 
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_write_data_only ( c1wirei2c_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief 1-Wire I2C write data only stop function.
 * @details This function is used when a start and I2C address have previously been issued with a Write Data No Stop Device
 * command. This command writes 1-255 bytes to an I2C slave completing the transaction with a stop.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_write_data_only_stop ( c1wirei2c_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief 1-Wire I2C read data stop function.
 * @details This function is used to address and read 1-255 bytes from an I2C slave in one transaction.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] slave_addr : 7-bit slave address.
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of data bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_read_data_stop ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief 1-Wire I2C write read data stop function.
 * @details This function is used to first address and write 1-255 bytes to an I2C slave. Secondly, it addresses
 * and reads 1-255 bytes from an I2C slave and issues a stop.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] slave_addr : 7-bit slave address.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of data bytes to write.
 * @param[out] data_out : Output data read.
 * @param[in] out_len : Number of data bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_write_read_data_stop ( c1wirei2c_t *ctx, uint8_t slave_addr, 
                                       uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );

/**
 * @brief 1-Wire I2C write configuration function.
 * @details This function is used to write the settings of the I2C speed bits per the formatting of the Configuration register.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] config : Configuration byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_write_configuration ( c1wirei2c_t *ctx, uint8_t config );

/**
 * @brief 1-Wire I2C read configuration function.
 * @details This function is used to read the settings of the I2C speed bits from the Configuration register.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[out] config : Configuration byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_read_configuration ( c1wirei2c_t *ctx, uint8_t *config );

/**
 * @brief 1-Wire I2C enable sleep mode function.
 * @details This function puts the device into a low current mode. All 1-Wire communication is ignored until woken up. 
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_enable_sleep_mode ( c1wirei2c_t *ctx );

/**
 * @brief 1-Wire I2C read device revision function.
 * @details This function reads the device revision. The read data byte contains the major revision in
 * the upper nibble of the bytes and the minor revision in the lower nibble of the byte.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[out] revision : Device revision byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c1wirei2c_read_device_revision ( c1wirei2c_t *ctx, uint8_t *revision );

/**
 * @brief 1-Wire I2C set rst pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c1wirei2c_set_rst_pin ( c1wirei2c_t *ctx, uint8_t state );

/**
 * @brief 1-Wire I2C reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #c1wirei2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c1wirei2c_reset_device ( c1wirei2c_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // C1WIREI2C_H

/*! @} */ // c1wirei2c

// ------------------------------------------------------------------------ END
