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
 * @file templog7.h
 * @brief This file contains API for Temp-Log 7 Click Driver.
 */

#ifndef TEMPLOG7_H
#define TEMPLOG7_H

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
 * @addtogroup templog7 Temp-Log 7 Click Driver
 * @brief API for configuring and manipulating Temp-Log 7 Click driver.
 * @{
 */

/**
 * @defgroup templog7_cmd Temp-Log 7 Commands List
 * @brief List of commands of Temp-Log 7 Click driver.
 */

/**
 * @addtogroup templog7_cmd
 * @{
 */

/**
 * @brief Temp-Log 7 commands list.
 * @details Specified commands list of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_CMD_CONVERT_TEMP               0x44
#define TEMPLOG7_CMD_ALERT_SEARCH               0xEC
#define TEMPLOG7_CMD_WRITE_SCRATCHPAD_1         0x4E
#define TEMPLOG7_CMD_READ_SCRATCHPAD_1          0xBE
#define TEMPLOG7_CMD_COPY_SCRATCHPAD_1          0x48
#define TEMPLOG7_CMD_WRITE_SCRATCHPAD_2         0x0F
#define TEMPLOG7_CMD_READ_SCRATCHPAD_2          0xAA
#define TEMPLOG7_CMD_COPY_SCRATCHPAD_2          0x55
#define TEMPLOG7_CMD_READ_EEPROM                0xF0
#define TEMPLOG7_CMD_GPIO_WRITE                 0xA5
#define TEMPLOG7_CMD_GPIO_READ                  0xF5

/*! @} */ // templog7_cmd

/**
 * @defgroup templog7_set Temp-Log 7 Settings
 * @brief Settings of Temp-Log 7 Click driver.
 */

/**
 * @addtogroup templog7_set
 * @{
 */

/**
 * @brief Temp-Log 7 temperature calculation values.
 * @details Specified temperature calculation values of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_TEMP_RES_16BIT                 0.0078125f
#define TEMPLOG7_TEMP_RES_12BIT                 0.0625f

/**
 * @brief Temp-Log 7 status register settings.
 * @details Specified status register settings of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_STATUS_ALERT_HIGH              0x80
#define TEMPLOG7_STATUS_ALERT_LOW               0x40
#define TEMPLOG7_STATUS_RESERVED                0x30
#define TEMPLOG7_STATUS_DATA_VALID              0x08
#define TEMPLOG7_STATUS_POWER_MODE              0x04
#define TEMPLOG7_STATUS_ARB_DONE                0x02
#define TEMPLOG7_STATUS_LOCK_STATUS             0x01

/**
 * @brief Temp-Log 7 config 1 register settings.
 * @details Specified config 1 register settings of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_CFG1_TEMP_FMT_12_BIT           0x00
#define TEMPLOG7_CFG1_TEMP_FMT_16_BIT           0x80
#define TEMPLOG7_CFG1_TEMP_FMT_MASK             0x80
#define TEMPLOG7_CFG1_RESERVED                  0x40
#define TEMPLOG7_CFG1_CONV_TIME_SEL_3MS         0x00
#define TEMPLOG7_CFG1_CONV_TIME_SEL_5p5MS       0x20
#define TEMPLOG7_CFG1_CONV_TIME_SEL_MASK        0x20
#define TEMPLOG7_CFG1_ALERT_MODE_ALERT          0x00
#define TEMPLOG7_CFG1_ALERT_MODE_COMPARATOR     0x10
#define TEMPLOG7_CFG1_ALERT_MODE_MASK           0x10
#define TEMPLOG7_CFG1_AVG_SEL_NO_AVG            0x00
#define TEMPLOG7_CFG1_AVG_SEL_8_B2B_CONV        0x08
#define TEMPLOG7_CFG1_AVG_SEL_MASK              0x08
#define TEMPLOG7_CFG1_CONV_MODE_SEL_ONE_SHOT    0x00
#define TEMPLOG7_CFG1_CONV_MODE_SEL_STACKED     0x01
#define TEMPLOG7_CFG1_CONV_MODE_SEL_AUTO        0x02
#define TEMPLOG7_CFG1_CONV_MODE_SEL_MASK        0x07

/**
 * @brief Temp-Log 7 config 2 register settings.
 * @details Specified config 2 register settings of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_CFG2_OD_DIS                    0x00
#define TEMPLOG7_CFG2_OD_EN                     0x80
#define TEMPLOG7_CFG2_OD_MASK                   0x80
#define TEMPLOG7_CFG2_FLEX_ADDR_MODE_HOST       0x00
#define TEMPLOG7_CFG2_FLEX_ADDR_MODE_IO         0x20
#define TEMPLOG7_CFG2_FLEX_ADDR_MODE_RES        0x40
#define TEMPLOG7_CFG2_FLEX_ADDR_MODE_IO_RES     0x60
#define TEMPLOG7_CFG2_FLEX_ADDR_MODE_MASK       0x60
#define TEMPLOG7_CFG2_ARB_MODE_DIS              0x00
#define TEMPLOG7_CFG2_ARB_MODE_SOFT_EN          0x10
#define TEMPLOG7_CFG2_ARB_MODE_FAST_EN          0x18
#define TEMPLOG7_CFG2_ARB_MODE_MASK             0x18
#define TEMPLOG7_CFG2_HYSTERESIS_5_C            0x00
#define TEMPLOG7_CFG2_HYSTERESIS_10_C           0x02
#define TEMPLOG7_CFG2_HYSTERESIS_15_C           0x04
#define TEMPLOG7_CFG2_HYSTERESIS_20_C           0x06
#define TEMPLOG7_CFG2_HYSTERESIS_MASK           0x06
#define TEMPLOG7_CFG2_LOCK_DIS                  0x00
#define TEMPLOG7_CFG2_LOCK_EN                   0x01
#define TEMPLOG7_CFG2_LOCK_MASK                 0x01

/**
 * @brief Temp-Log 7 default temperature alert and offset values.
 * @details Specified default temperature alert and offset values of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_TEMP_ALERT_LOW                 5.0f
#define TEMPLOG7_TEMP_ALERT_HIGH                40.0f
#define TEMPLOG7_TEMP_OFFSET                    0.0f

/**
 * @brief Temp-Log 7 IO read register settings.
 * @details Specified IO read register settings of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_IO_READ_NIO3_STATE             0x80
#define TEMPLOG7_IO_READ_NIO2_STATE             0x40
#define TEMPLOG7_IO_READ_NIO1_STATE             0x20
#define TEMPLOG7_IO_READ_NIO0_STATE             0x10
#define TEMPLOG7_IO_READ_IO3_STATE              0x08
#define TEMPLOG7_IO_READ_IO2_STATE              0x04
#define TEMPLOG7_IO_READ_IO1_STATE              0x02
#define TEMPLOG7_IO_READ_IO0_STATE              0x01

/**
 * @brief Temp-Log 7 IO config register settings.
 * @details Specified IO config register settings of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_IO_CFG_IO3_SEL_INPUT           0x00
#define TEMPLOG7_IO_CFG_IO3_SEL_OUTPUT_LOW      0x80
#define TEMPLOG7_IO_CFG_IO3_SEL_OUTPUT_HIGH     0xC0
#define TEMPLOG7_IO_CFG_IO3_SEL_MASK            0xC0
#define TEMPLOG7_IO_CFG_IO2_SEL_INPUT           0x00
#define TEMPLOG7_IO_CFG_IO2_SEL_ALERT           0x10
#define TEMPLOG7_IO_CFG_IO2_SEL_OUTPUT_LOW      0x20
#define TEMPLOG7_IO_CFG_IO2_SEL_OUTPUT_HIGH     0x30
#define TEMPLOG7_IO_CFG_IO2_SEL_MASK            0x30
#define TEMPLOG7_IO_CFG_IO1_SEL_INPUT           0x00
#define TEMPLOG7_IO_CFG_IO1_SEL_OUTPUT_LOW      0x08
#define TEMPLOG7_IO_CFG_IO1_SEL_OUTPUT_HIGH     0x0C
#define TEMPLOG7_IO_CFG_IO1_SEL_MASK            0x0C
#define TEMPLOG7_IO_CFG_IO0_SEL_INPUT           0x00
#define TEMPLOG7_IO_CFG_IO0_SEL_OUTPUT_LOW      0x02
#define TEMPLOG7_IO_CFG_IO0_SEL_OUTPUT_HIGH     0x03
#define TEMPLOG7_IO_CFG_IO0_SEL_MASK            0x03
#define TEMPLOG7_IO_CHECK_CODE_OK               0xAA

/**
 * @brief Temp-Log 7 EEPROM settings.
 * @details Specified EEPROM settings of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_EEPROM_ADDR_MIN                0x00
#define TEMPLOG7_EEPROM_ADDR_MAX                0xFF
#define TEMPLOG7_EEPROM_ADDR_BLOCK              8
#define TEMPLOG7_EEPROM_ADDR_MASK               0xFFF8u

/**
 * @brief Temp-Log 7 scratchpad 2 settings.
 * @details Specified scratchpad 2 settings of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_COPY_SCRATCHPAD_2_QUALIFIER    0xA5

/**
 * @brief Temp-Log 7 family code value.
 * @details Specified family code value of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_FAMILY_CODE                    0x26

/**
 * @brief Temp-Log 7 address selection macros.
 * @details Specified address selection macros of Temp-Log 7 Click driver.
 */
#define TEMPLOG7_ADDRESS_0                      0x00
#define TEMPLOG7_ADDRESS_ALL                    0xFF

/*! @} */ // templog7_set

/**
 * @defgroup templog7_map Temp-Log 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Temp-Log 7 Click driver.
 */

/**
 * @addtogroup templog7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Temp-Log 7 Click to the selected MikroBUS.
 */
#define TEMPLOG7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // templog7_map
/*! @} */ // templog7

/**
 * @brief Temp-Log 7 Click gpio selector.
 * @details Selects gpio pin of Temp-Log 7 Click driver.
 */
typedef enum
{
    TEMPLOG7_GPIO_0,          /**< GPIO 0 pin. */
    TEMPLOG7_GPIO_1           /**< GPIO 1 pin. */

} templog7_gpio_sel_t;

/**
 * @brief Temp-Log 7 scratchpad 1 object.
 * @details Scratchpad 1 object definition of Temp-Log 7 Click driver.
 */
typedef struct
{
    int16_t temperature;        /**< Raw temperature value (Read only). */
    uint8_t status;             /**< Status value (Read only). */
    uint8_t config_1;           /**< Config 1 setting (Read/Write). */
    uint8_t config_2;           /**< Config 2 setting (Read/Write). */
    uint8_t short_addr;         /**< Short address setting (Read/Write). */
    int16_t temp_limit_low;     /**< Temperature alert limit low setting (Read/Write). */
    int16_t temp_limit_high;    /**< Temperature alert limit high setting (Read/Write). */
    int16_t temp_offset;        /**< Temperature offset setting (Read/Write). */

} templog7_scratchpad_1_t;

/**
 * @brief Temp-Log 7 scratchpad 2 object.
 * @details Scratchpad 2 object definition of Temp-Log 7 Click driver.
 */
typedef struct
{
    uint16_t address;           /**< Address for scratchpad 2 (EEPROM) rounded to 8 bytes - block size (Write only). */
    uint8_t data_buf[ TEMPLOG7_EEPROM_ADDR_BLOCK ];   /**< Block data buffer (Read/Write). */

} templog7_scratchpad_2_t;

/**
 * @brief Temp-Log 7 Click context object.
 * @details Context object definition of Temp-Log 7 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alert;         /**< Alert input pin. */

    // Modules
    one_wire_t ow;              /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t address;            /**< Device address selection. */

} templog7_t;

/**
 * @brief Temp-Log 7 Click configuration object.
 * @details Configuration object definition of Temp-Log 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;             /**< GPIO 0 pin. */
    pin_name_t gp1;             /**< GPIO 1 pin. */

    // Additional gpio pins
    pin_name_t alert;           /**< Alert input pin. */

    templog7_gpio_sel_t gpio_sel;     /**< GPIO selection. */

} templog7_cfg_t;

/**
 * @brief Temp-Log 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPLOG7_OK = 0,
    TEMPLOG7_ERROR = -1

} templog7_return_value_t;

/*!
 * @addtogroup templog7 Temp-Log 7 Click Driver
 * @brief API for configuring and manipulating Temp-Log 7 Click driver.
 * @{
 */

/**
 * @brief Temp-Log 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #templog7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void templog7_cfg_setup ( templog7_cfg_t *cfg );

/**
 * @brief Temp-Log 7 driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #templog7_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #templog7_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void templog7_gpio_selection ( templog7_cfg_t *cfg, templog7_gpio_sel_t gpio_sel );

/**
 * @brief Temp-Log 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #templog7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_init ( templog7_t *ctx, templog7_cfg_t *cfg );

/**
 * @brief Temp-Log 7 default configuration function.
 * @details This function executes a default configuration of Temp-Log 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t templog7_default_cfg ( templog7_t *ctx );

/**
 * @brief Temp-Log 7 check communication function.
 * @details This function checks the communication by reading the ROM address 
 * as well as verifying family code and CRC 8.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_check_communication ( templog7_t *ctx );

/**
 * @brief Temp-Log 7 select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the @b ctx->address.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_select_device ( templog7_t *ctx );

/**
 * @brief Temp-Log 7 write scratchpad 1 function.
 * @details This function writes data to scratchpad 1 using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[in] scratchpad : Scratchpad to be written.
 * See #templog7_scratchpad_1_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_write_scratchpad_1 ( templog7_t *ctx, templog7_scratchpad_1_t *scratchpad );

/**
 * @brief Temp-Log 7 read scratchpad 1 function.
 * @details This function reads data from scratchpad 1 using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[out] scratchpad : Output read scratchpad.
 * See #templog7_scratchpad_1_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_read_scratchpad_1 ( templog7_t *ctx, templog7_scratchpad_1_t *scratchpad );

/**
 * @brief Temp-Log 7 copy scratchpad 1 function.
 * @details This function copies the scratchpad 1 registers to the EEPROM config memory.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_copy_scratchpad_1 ( templog7_t *ctx );

/**
 * @brief Temp-Log 7 write scratchpad 2 function.
 * @details This function writes data to scratchpad 2 using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[in] scratchpad : Scratchpad to be written.
 * See #templog7_scratchpad_2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_write_scratchpad_2 ( templog7_t *ctx, templog7_scratchpad_2_t *scratchpad );

/**
 * @brief Temp-Log 7 read scratchpad 2 function.
 * @details This function reads data from scratchpad 2 using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[in,out] scratchpad : Output read scratchpad, address field must be set.
 * See #templog7_scratchpad_2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_read_scratchpad_2 ( templog7_t *ctx, templog7_scratchpad_2_t *scratchpad );

/**
 * @brief Temp-Log 7 copy scratchpad 2 function.
 * @details This function copies the content of scratchpad 2 to the EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_copy_scratchpad_2 ( templog7_t *ctx );

/**
 * @brief Temp-Log 7 start measurement function.
 * @details This function starts the measurement by sending the convert temperature command.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_start_measurement ( templog7_t *ctx );

/**
 * @brief Temp-Log 7 read temperature function.
 * @details This function starts the one shot measurement and reads the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_read_temperature ( templog7_t *ctx, float *temperature );

/**
 * @brief Temp-Log 7 write EEPROM function.
 * @details This function writes a desired number of data bytes to the EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[in] address : Starting EEPROM address (0x00-0xFF), must be rounded to 8 bytes block.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of data bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_write_eeprom ( templog7_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief Temp-Log 7 read EEPROM function.
 * @details This function reads a desired number of data bytes from the EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[in] address : Starting EEPROM address (0x00-0xFF), must be rounded to 8 bytes block.
 * @param[out] data_out : Data buffer read from EEPROM memory.
 * @param[in] len : Number of data bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_read_eeprom ( templog7_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief Temp-Log 7 clear EEPROM function.
 * @details This function clears the whole EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_clear_eeprom ( templog7_t *ctx );

/**
 * @brief Temp-Log 7 write gpio function.
 * @details This function writes data to the GPIO config register.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[in] data_in : GPIO config register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_write_gpio ( templog7_t *ctx, uint8_t data_in );

/**
 * @brief Temp-Log 7 read gpio function.
 * @details This function reads data from the GPIO read register.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @param[in] data_out : GPIO read register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t templog7_read_gpio ( templog7_t *ctx, uint8_t *data_out );

/**
 * @brief Temp-Log 7 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #templog7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t templog7_get_alert_pin ( templog7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TEMPLOG7_H

/*! @} */ // templog7

// ------------------------------------------------------------------------ END
