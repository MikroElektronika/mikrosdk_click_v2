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
 * @file rng2.h
 * @brief This file contains API for RNG 2 Click Driver.
 */

#ifndef RNG2_H
#define RNG2_H

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

/*!
 * @addtogroup rng2 RNG 2 Click Driver
 * @brief API for configuring and manipulating RNG 2 Click driver.
 * @{
 */

/**
 * @defgroup rng2_reg RNG 2 Registers List
 * @brief List of registers of RNG 2 Click driver.
 */

/**
 * @addtogroup rng2_reg
 * @{
 */

/**
 * @brief RNG 2 word address values.
 * @details Specified word address values of RNG 2 Click driver.
 */
#define RNG2_WORD_RESET                     0x00
#define RNG2_WORD_SLEEP                     0x01
#define RNG2_WORD_CMD                       0x03

/**
 * @brief RNG 2 command address values.
 * @details Specified command address values of RNG 2 Click driver.
 */
#define RNG2_CMD_INFO                       0x30
#define RNG2_CMD_RANDOM                     0x16
#define RNG2_CMD_READ                       0x02
#define RNG2_CMD_SELFTEST                   0x77

/**
 * @brief RNG 2 param1 and param2 values.
 * @details Specified param1 and param2 values of RNG 2 Click driver.
 */
#define RNG2_PARAM1_INFO                    0x00
#define RNG2_PARAM2_INFO                    0x0000
#define RNG2_PARAM1_RANDOM                  0x00
#define RNG2_PARAM2_RANDOM                  0x0000
#define RNG2_PARAM1_READ                    0x01
#define RNG2_PARAM2_READ                    0x0000
#define RNG2_PARAM1_SELFTEST_STATUS         0x00
#define RNG2_PARAM2_SELFTEST_STATUS         0x0000
#define RNG2_PARAM1_SELFTEST_DRBG           0x01
#define RNG2_PARAM2_SELFTEST_DRBG           0x0000
#define RNG2_PARAM1_SELFTEST_SHA256         0x20
#define RNG2_PARAM2_SELFTEST_SHA256         0x0000
#define RNG2_PARAM1_SELFTEST_DRBG_SHA256    0x20
#define RNG2_PARAM2_SELFTEST_DRBG_SHA256    0x0000

/*! @} */ // rng2_reg

/**
 * @defgroup rng2_set RNG 2 Registers Settings
 * @brief Settings for registers of RNG 2 Click driver.
 */

/**
 * @addtogroup rng2_set
 * @{
 */

/**
 * @brief RNG 2 INFO setting.
 * @details Specified setting for INFO of RNG 2 Click driver.
 */
#define RNG2_INFO_DEVICE_ID                 0xD0
#define RNG2_INFO_SILICON_ID                0x20
#define RNG2_INFO_DATA_LEN                  4

/**
 * @brief RNG 2 RANDOM setting.
 * @details Specified setting for RANDOM of RNG 2 Click driver.
 */
#define RNG2_RANDOM_DATA_IN_LEN             20
#define RNG2_RANDOM_DATA_OUT_LEN            32

/**
 * @brief RNG 2 GROUP setting.
 * @details Specified setting for GROUP of RNG 2 Click driver.
 */
#define RNG2_GROUP_MIN_BYTES                4
#define RNG2_GROUP_MAX_BYTES                87
#define RNG2_GROUP_MAX_DATA_LEN             80

/**
 * @brief RNG 2 I2C timeout setting.
 * @details Specified setting for I2C timeout of RNG 2 Click driver.
 */
#define RNG2_I2C_TIMEOUT                    100000ul

/**
 * @brief RNG 2 device address setting.
 * @details Specified setting for device slave address selection of
 * RNG 2 Click driver.
 */
#define RNG2_DEVICE_ADDRESS                 0x40

/*! @} */ // rng2_set

/**
 * @defgroup rng2_map RNG 2 MikroBUS Map
 * @brief MikroBUS pin mapping of RNG 2 Click driver.
 */

/**
 * @addtogroup rng2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RNG 2 Click to the selected MikroBUS.
 */
#define RNG2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // rng2_map
/*! @} */ // rng2

/**
 * @brief RNG 2 Click command packet object.
 * @details Command packet object definition of RNG 2 Click driver.
 */
typedef struct
{
    uint8_t opcode;             /**< Command opcode. */
    uint8_t param1;             /**< The first parameter. */
    uint16_t param2;            /**< The second parameter. */
    uint8_t data_buf[ RNG2_GROUP_MAX_DATA_LEN ];    /**< Optional remaining data. */
    uint8_t data_len;           /**< Remaining data length. */

} rng2_cmd_pkt_t;

/**
 * @brief RNG 2 Click response packet object.
 * @details Response packet object definition of RNG 2 Click driver.
 */
typedef struct
{
    uint8_t data_buf[ RNG2_GROUP_MAX_BYTES - 3 ];   /**< Data buffer. */
    uint8_t data_len;           /**< Data length. */

} rng2_rsp_pkt_t;

/**
 * @brief RNG 2 Click context object.
 * @details Context object definition of RNG 2 Click driver.
 */
typedef struct
{
    // Modules
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint8_t i2c_started;        /**< I2C started flag. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    rng2_cmd_pkt_t cmd_pkt;     /**< Command packet. */
    rng2_rsp_pkt_t rsp_pkt;     /**< Response packet. */

} rng2_t;

/**
 * @brief RNG 2 Click configuration object.
 * @details Configuration object definition of RNG 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint8_t    i2c_address;     /**< I2C slave address. */

} rng2_cfg_t;

/**
 * @brief RNG 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RNG2_OK = 0,
    RNG2_ERROR = -1

} rng2_return_value_t;

/*!
 * @addtogroup rng2 RNG 2 Click Driver
 * @brief API for configuring and manipulating RNG 2 Click driver.
 * @{
 */

/**
 * @brief RNG 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rng2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rng2_cfg_setup ( rng2_cfg_t *cfg );

/**
 * @brief RNG 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rng2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rng2_init ( rng2_t *ctx, rng2_cfg_t *cfg );

/**
 * @brief RNG 2 default configuration function.
 * @details This function executes a default configuration of RNG 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rng2_default_cfg ( rng2_t *ctx );

/**
 * @brief RNG 2 send wake function.
 * @details This function sends a wake condition to the RNG 2 Click board.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rng2_send_wake ( rng2_t *ctx );

/**
 * @brief RNG 2 reset counter function.
 * @details This function issues a reset command to reset the internal counter on the RNG 2 Click board.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rng2_reset_counter ( rng2_t *ctx );

/**
 * @brief RNG 2 I2C sync function.
 * @details This function performs a synchronization sequence with the RNG 2 Click board using I2C signals.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rng2_i2c_sync ( rng2_t *ctx );

/**
 * @brief RNG 2 low power mode function.
 * @details This function places the RNG 2 Click board into low power (sleep) mode.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rng2_low_power_mode ( rng2_t *ctx );

/**
 * @brief RNG 2 write packet function.
 * @details This function constructs and writes a command packet to the RNG 2 Click board.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rng2_write_packet ( rng2_t *ctx );

/**
 * @brief RNG 2 read packet function.
 * @details This function reads a response packet from the RNG 2 Click board and verifies CRC.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note The response packet is stored in the ctx->rsp_pkt.
 */
err_t rng2_read_packet ( rng2_t *ctx );

/**
 * @brief RNG 2 read info function.
 * @details This function sends an info command and validates the device and silicon ID on the RNG 2 Click board.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note The response packet is stored in the ctx->rsp_pkt.
 */
err_t rng2_read_info ( rng2_t *ctx );

/**
 * @brief RNG 2 read random number function.
 * @details This function requests and reads a 32-byte random number from the RNG 2 Click board.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note The response packet is stored in the ctx->rsp_pkt.
 */
err_t rng2_read_random_num ( rng2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RNG2_H

/*! @} */ // rng2

// ------------------------------------------------------------------------ END
