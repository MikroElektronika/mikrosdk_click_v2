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
 * @file irgrid5.h
 * @brief This file contains API for IR Grid 5 Click Driver.
 */

#ifndef IRGRID5_H
#define IRGRID5_H

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
 * @addtogroup irgrid5 IR Grid 5 Click Driver
 * @brief API for configuring and manipulating IR Grid 5 Click driver.
 * @{
 */

/**
 * @defgroup irgrid5_reg IR Grid 5 Registers List
 * @brief List of registers of IR Grid 5 Click driver.
 */

/**
 * @addtogroup irgrid5_reg
 * @{
 */

/**
 * @brief IR Grid 5 opcode values.
 * @details Specified opcode values of IR Grid 5 Click driver.
 */
#define IRGRID5_OPCODE_CMD                  0x0180
#define IRGRID5_OPCODE_CONFIG               0x3A2E
#define IRGRID5_OPCODE_WAKE                 0x57

/**
 * @brief IR Grid 5 commands list.
 * @details Specified commands list of IR Grid 5 Click driver.
 */
#define IRGRID5_CMD_FORCE_START             0x0001
#define IRGRID5_CMD_RESET                   0x0006
#define IRGRID5_CMD_SLEEP                   0x0007

/**
 * @brief IR Grid 5 address map.
 * @details Specified address map of IR Grid 5 Click driver.
 */
#define IRGRID5_ADDR_CONFIG_REFRESH_RATE    0x11F0
#define IRGRID5_ADDR_CONFIG_EMISSIVITY      0x11F2
#define IRGRID5_ADDR_CONFIG_APP_CONFIG      0x11F4
#define IRGRID5_ADDR_CONFIG_I2C_CONFIG      0x11FC
#define IRGRID5_ADDR_CONFIG_DEVICE_ADDRESS  0x11FE
#define IRGRID5_ADDR_CONFIG_BACKGROUND_TEMP 0xEEEE
#define IRGRID5_ADDR_RAM_AUX                0x2E0A
#define IRGRID5_ADDR_RAM_RAW_IR_DATA        0x2E2A
#define IRGRID5_ADDR_RAM_TO                 0x342C
#define IRGRID5_ADDR_RAM_T_SENSOR           0x3A2C
#define IRGRID5_ADDR_RAM_PROGRESS_BAR       0x3C10
#define IRGRID5_ADDR_RAM_DATA_FLAGS         0x3C14
#define IRGRID5_ADDR_EE_DEVICE_ID           0x1230
#define IRGRID5_ADDR_FLASH_FW_VERSION       0xFFF8

/*! @} */ // irgrid5_reg

/**
 * @defgroup irgrid5_set IR Grid 5 Registers Settings
 * @brief Settings for registers of IR Grid 5 Click driver.
 */

/**
 * @addtogroup irgrid5_set
 * @{
 */

/**
 * @brief IR Grid 5 data flags address setting.
 * @details Specified setting for data flags address of IR Grid 5 Click driver.
 */
#define IRGRID5_DATA_FLAGS_BUSY             0x0001
#define IRGRID5_DATA_FLAGS_READY            0x0100
#define IRGRID5_DATA_FLAGS_FRAME_UPDATE     0x0200

/**
 * @brief IR Grid 5 refresh rate address setting.
 * @details Specified setting for refresh rate address of IR Grid 5 Click driver.
 */
#define IRGRID5_REFRESH_RATE_2HZ            0x0002
#define IRGRID5_REFRESH_RATE_4HZ            0x0003
#define IRGRID5_REFRESH_RATE_8HZ            0x0004
#define IRGRID5_REFRESH_RATE_16HZ           0x0005
#define IRGRID5_REFRESH_RATE_MASK           0x0007

/**
 * @brief IR Grid 5 app config address setting.
 * @details Specified setting for app config address of IR Grid 5 Click driver.
 */
#define IRGRID5_APP_CONFIG_OUT_TO           0x0000
#define IRGRID5_APP_CONFIG_OUT_RAW_IR       0x0100
#define IRGRID5_APP_CONFIG_OUT_MASK         0x0100
#define IRGRID5_APP_CONFIG_MEAS_MODE_CONT   0x0000
#define IRGRID5_APP_CONFIG_MEAS_MODE_STEP   0x0800
#define IRGRID5_APP_CONFIG_MEAS_MODE_MASK   0x0800

/**
 * @brief IR Grid 5 I2C config address setting.
 * @details Specified setting for I2C config address of IR Grid 5 Click driver.
 */
#define IRGRID5_I2C_CONFIG_FW_MODE_EN       0x0000
#define IRGRID5_I2C_CONFIG_FW_MODE_DIS      0x0001
#define IRGRID5_I2C_CONFIG_FW_MODE_MASK     0x0001
#define IRGRID5_I2C_CONFIG_CURR_LIMIT_EN    0x0000
#define IRGRID5_I2C_CONFIG_CURR_LIMIT_DIS   0x0002
#define IRGRID5_I2C_CONFIG_CURR_LIMIT_MASK  0x0002
#define IRGRID5_I2C_CONFIG_LEVEL_VDD        0x0000
#define IRGRID5_I2C_CONFIG_LEVEL_1V8        0x0004
#define IRGRID5_I2C_CONFIG_LEVEL_MASK       0x0004

/**
 * @brief IR Grid 5 I2C num pixels setting.
 * @details Specified setting for num pixels of IR Grid 5 Click driver.
 */
#define IRGRID5_NUM_AUX                     20
#define IRGRID5_NUM_PIXELS                  768

/**
 * @brief IR Grid 5 measurement mode setting.
 * @details Specified setting for measurement mode of IR Grid 5 Click driver.
 */
#define IRGRID5_MEAS_MODE_CONT              0
#define IRGRID5_MEAS_MODE_STEP              1

/**
 * @brief IR Grid 5 output format setting.
 * @details Specified setting for output format of IR Grid 5 Click driver.
 */
#define IRGRID5_OUT_FORMAT_TEMPERATURE      0
#define IRGRID5_OUT_FORMAT_NORMALIZED       1

/**
 * @brief IR Grid 5 timeout setting.
 * @details Specified setting for timeout of IR Grid 5 Click driver.
 */
#define IRGRID5_TIMEOUT_MS                  1000

/**
 * @brief IR Grid 5 data resolution setting.
 * @details Specified setting for data resolution of IR Grid 5 Click driver.
 */
#define IRGRID5_OBJ_TEMP_RES                50.0
#define IRGRID5_SENSOR_TEMP_RES             100.0

/**
 * @brief IR Grid 5 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Grid 5 Click driver.
 */
#define IRGRID5_DEVICE_ADDRESS              0x66
#define IRGRID5_DEVICE_ADDRESS_MASK         0x7F

/*! @} */ // irgrid5_set

/**
 * @defgroup irgrid5_map IR Grid 5 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Grid 5 Click driver.
 */

/**
 * @addtogroup irgrid5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Grid 5 Click to the selected MikroBUS.
 */
#define IRGRID5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // irgrid5_map
/*! @} */ // irgrid5

/**
 * @brief IR Grid 5 Click context object.
 * @details Context object definition of IR Grid 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable device pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    // Memory read buffer
    uint8_t mem_buf_8[ IRGRID5_NUM_PIXELS * 2 + 2 ];    /**< 8-bit memory read buffer. */

} irgrid5_t;

/**
 * @brief IR Grid 5 Click configuration object.
 * @details Configuration object definition of IR Grid 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable device pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} irgrid5_cfg_t;

/**
 * @brief IR Grid 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRGRID5_DATA_READY = 1,
    IRGRID5_OK = 0,
    IRGRID5_ERROR = -1,
    IRGRID5_ERROR_TIMEOUT = -2

} irgrid5_return_value_t;

/*!
 * @addtogroup irgrid5 IR Grid 5 Click Driver
 * @brief API for configuring and manipulating IR Grid 5 Click driver.
 * @{
 */

/**
 * @brief IR Grid 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irgrid5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irgrid5_cfg_setup ( irgrid5_cfg_t *cfg );

/**
 * @brief IR Grid 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irgrid5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irgrid5_init ( irgrid5_t *ctx, irgrid5_cfg_t *cfg );

/**
 * @brief IR Grid 5 default configuration function.
 * @details This function executes a default configuration of IR Grid 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t irgrid5_default_cfg ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 command write function.
 * @details This function writes a 16-bit command to the IR Grid 5 device.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[in] data_in : 16-bit command data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_cmd_write ( irgrid5_t *ctx, uint16_t data_in );

/**
 * @brief IR Grid 5 memory read function.
 * @details This function reads data from the IR Grid 5 memory starting at the given address.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[in] addr : Memory address to read from.
 * @param[out] data_out : Output buffer for the read data.
 * @param[in] len : Number of 16-bit words to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_mem_read ( irgrid5_t *ctx, uint16_t addr, uint16_t *data_out, uint16_t len );

/**
 * @brief IR Grid 5 configuration write function.
 * @details This function writes a 16-bit data value to the specified configuration address.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[in] addr : Configuration address to write to.
 * @param[in] data_in : 16-bit data to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_config_write ( irgrid5_t *ctx, uint16_t addr, uint16_t data_in );

/**
 * @brief IR Grid 5 reset function.
 * @details This function issues a reset command to the IR Grid 5 device.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_reset ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 force start function.
 * @details This function forces the device to start a new measurement cycle.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_force_start ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 clear ready status function.
 * @details This function clears the ready status.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_clear_ready ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 check data ready function.
 * @details This function checks if new data is available and the device is not busy.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return @li @c  0 - Data not ready or device is busy,
 *         @li @c  1 - Data ready,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_check_ready ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 sleep function.
 * @details This function puts the IR Grid 5 device into sleep mode.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_sleep ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 wake-up function.
 * @details This function sends a wake-up command to the IR Grid 5 device.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_wake_up ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 enable device function.
 * @details This function enables the IR Grid 5 device by setting the EN pin high.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void irgrid5_enable_device ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 disable device function.
 * @details This function disables the IR Grid 5 device by setting the EN pin low.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void irgrid5_disable_device ( irgrid5_t *ctx );

/**
 * @brief IR Grid 5 get device ID function.
 * @details This function reads the device ID from the IR Grid 5 EEPROM.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[out] device_id : Pointer to memory where 4 words of device ID will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_get_device_id ( irgrid5_t *ctx, uint16_t *device_id );

/**
 * @brief IR Grid 5 get firmware version function.
 * @details This function reads the firmware version from the IR Grid 5 flash memory.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[out] fw_ver : Pointer to a 3-byte array for storing firmware version.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_get_fw_version ( irgrid5_t *ctx, uint8_t *fw_ver );

/**
 * @brief IR Grid 5 set measurement mode function.
 * @details This function sets the measurement mode (continuous or step) in the configuration register.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[in] mode : Measurement mode (see @c IRGRID5_MEAS_MODE_CONT or @c IRGRID5_MEAS_MODE_STEP).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_set_meas_mode ( irgrid5_t *ctx, uint8_t mode );

/**
 * @brief IR Grid 5 set output format function.
 * @details This function sets the output format in the configuration register.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[in] out_format : Output format (see @c IRGRID5_OUT_FORMAT_TEMPERATURE or @c IRGRID5_OUT_FORMAT_NORMALIZED).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_set_out_format ( irgrid5_t *ctx, uint8_t out_format );

/**
 * @brief IR Grid 5 set refresh rate function.
 * @details This function sets the refresh rate in the configuration register.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[in] rate : Refresh rate (see @c IRGRID5_REFRESH_RATE_xHZ macros).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t irgrid5_set_refresh_rate ( irgrid5_t *ctx, uint8_t rate );

/**
 * @brief IR Grid 5 get measurement function.
 * @details This function reads object temperature image and sensor internal temperatures from the IR Grid 5 device.
 * @param[in] ctx : Click context object.
 * See #irgrid5_t object definition for detailed explanation.
 * @param[out] obj_image : Array of object temperature values in Celsius (IRGRID5_NUM_PIXELS elements).
 * @param[out] sensor_temp : Pointer to store sensor internal temperature value in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * @note None.
 */
err_t irgrid5_get_measurement ( irgrid5_t *ctx, float *obj_image, float *sensor_temp );

#ifdef __cplusplus
}
#endif
#endif // IRGRID5_H

/*! @} */ // irgrid5

// ------------------------------------------------------------------------ END
