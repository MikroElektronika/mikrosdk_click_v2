/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file dali2.h
 * @brief This file contains API for DALI 2 Click Driver.
 */

#ifndef DALI2_H
#define DALI2_H

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
 * @addtogroup dali2 DALI 2 Click Driver
 * @brief API for configuring and manipulating DALI 2 Click driver.
 * @{
 */

/**
 * @defgroup dali2_set DALI 2 Settings
 * @brief Settings of DALI 2 Click driver.
 */

/**
 * @addtogroup dali2_set
 * @{
 */

/**
 * @brief DALI 2 short-address selection.
 * @details Use with address values from 0 to 63 to address one commissioned control gear.
 * This is the only address type supported by dali2_query because one device can reply.
 */
#define DALI2_ADDRESS_SHORT                     0

/**
 * @brief DALI 2 group-address selection.
 * @details Use with address values from 0 to 15 to address all control gear assigned to one group.
 * Group commands affect several devices and must not be used for backward-frame queries.
 */
#define DALI2_ADDRESS_GROUP                     1

/**
 * @brief DALI 2 broadcast-address selection.
 * @details The address value is ignored and the command affects all control gear on the bus.
 * Broadcast commands do not identify one device and must not be used for queries.
 */
#define DALI2_ADDRESS_BROADCAST                 2

/**
 * @brief DALI 2 address limits and encoding masks.
 * @details Short addresses use 0 to 63, group addresses use 0 to 15, and the selector bit
 * distinguishes direct arc power data from a command in the encoded address byte.
 */
#define DALI2_SHORT_ADDRESS_MAX                 63
#define DALI2_GROUP_ADDRESS_MAX                 15
#define DALI2_ADDRESS_GROUP_MASK                0x80
#define DALI2_ADDRESS_BROADCAST_MASK            0xFE
#define DALI2_ADDRESS_COMMAND_MASK              0x01

/**
 * @brief DALI 2 control commands.
 * @details Commands for switching, relative dimming, and scene recall.
 * Add a scene number from 0 to 15 to DALI2_CMD_GO_TO_SCENE_BASE.
 */
#define DALI2_CMD_OFF                           0x00
#define DALI2_CMD_UP                            0x01
#define DALI2_CMD_DOWN                          0x02
#define DALI2_CMD_STEP_UP                       0x03
#define DALI2_CMD_STEP_DOWN                     0x04
#define DALI2_CMD_RECALL_MAX_LEVEL              0x05
#define DALI2_CMD_RECALL_MIN_LEVEL              0x06
#define DALI2_CMD_STEP_DOWN_AND_OFF             0x07
#define DALI2_CMD_ON_AND_STEP_UP                0x08
#define DALI2_CMD_ENABLE_DAPC_SEQUENCE          0x09
#define DALI2_CMD_GO_TO_SCENE_BASE              0x10

/**
 * @brief DALI 2 query commands.
 * @details Common control-gear queries. Use a short address to avoid simultaneous replies.
 */
#define DALI2_CMD_QUERY_STATUS                  0x90
#define DALI2_CMD_QUERY_CONTROL_GEAR_PRESENT    0x91
#define DALI2_CMD_QUERY_LAMP_FAILURE            0x92
#define DALI2_CMD_QUERY_LAMP_POWER_ON           0x93
#define DALI2_CMD_QUERY_LIMIT_ERROR             0x94
#define DALI2_CMD_QUERY_RESET_STATE             0x95
#define DALI2_CMD_QUERY_MISSING_SHORT_ADDRESS   0x96
#define DALI2_CMD_QUERY_VERSION_NUMBER          0x97
#define DALI2_CMD_QUERY_CONTENT_DTR0            0x98
#define DALI2_CMD_QUERY_DEVICE_TYPE             0x99
#define DALI2_CMD_QUERY_PHYSICAL_MINIMUM        0x9A
#define DALI2_CMD_QUERY_POWER_FAILURE           0x9B
#define DALI2_CMD_QUERY_ACTUAL_LEVEL            0xA0
#define DALI2_CMD_QUERY_MAX_LEVEL               0xA1
#define DALI2_CMD_QUERY_MIN_LEVEL               0xA2
#define DALI2_CMD_QUERY_POWER_ON_LEVEL          0xA3
#define DALI2_CMD_QUERY_SYSTEM_FAILURE_LEVEL    0xA4
#define DALI2_CMD_QUERY_FADE_TIME_RATE          0xA5
#define DALI2_RESPONSE_YES                      0xFF

/**
 * @brief DALI 2 status masks.
 * @details Bit masks for the byte returned by DALI2_CMD_QUERY_STATUS.
 */
#define DALI2_STATUS_CONTROL_GEAR_FAILURE       0x01
#define DALI2_STATUS_LAMP_FAILURE               0x02
#define DALI2_STATUS_LAMP_ON                    0x04
#define DALI2_STATUS_LIMIT_ERROR                0x08
#define DALI2_STATUS_FADE_RUNNING               0x10
#define DALI2_STATUS_RESET_STATE                0x20
#define DALI2_STATUS_MISSING_SHORT_ADDRESS      0x40
#define DALI2_STATUS_POWER_FAILURE              0x80

/**
 * @brief DALI 2 arc power levels.
 * @details Levels 1 to 254 use the control gear's dimming curve, not a linear percentage.
 * Level 0 switches the lamp off; MASK stops an active fade without selecting a new level.
 */
#define DALI2_LEVEL_OFF                         0
#define DALI2_LEVEL_MIN                         1
#define DALI2_LEVEL_MAX                         254
#define DALI2_LEVEL_MASK                        255

/**
 * @brief DALI 2 GPIO levels.
 * @details Both optocoupler interfaces invert the physical bus: GPIO low means bus idle.
 */
#define DALI2_PIN_IDLE                          0
#define DALI2_PIN_ACTIVE                        1

/*! @} */ // dali2_set

/**
 * @defgroup dali2_map DALI 2 MikroBUS Map
 * @brief MikroBUS pin mapping of DALI 2 Click driver.
 */

/**
 * @addtogroup dali2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DALI 2 Click to the selected MikroBUS.
 */
#define DALI2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dali2_map
/*! @} */ // dali2

/**
 * @brief DALI 2 Click context object.
 * @details Context object definition of DALI 2 Click driver.
 * @note This blocking, single-master driver supports 16-bit forward and 8-bit backward frames.
 * It does not implement commissioning, multi-master arbitration, or 24-bit control-device frames.
 * GPIO and interrupt overhead must be small compared with the nominal 416.7 us half-bit time.
 * Verify timing on the target MCU; do not call the driver concurrently or from an interrupt.
 */
typedef struct
{
    digital_out_t tx_pin;       /**< DALI TX pin. */

    digital_in_t rx_pin;        /**< DALI RX pin. */

} dali2_t;

/**
 * @brief DALI 2 Click configuration object.
 * @details Configuration object definition of DALI 2 Click driver.
 */
typedef struct
{
    pin_name_t tx_pin;          /**< DALI TX pin. */
    pin_name_t rx_pin;          /**< DALI RX pin. */

} dali2_cfg_t;

/**
 * @brief DALI 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DALI2_OK = 0,
    DALI2_ERROR = -1,            /**< Invalid argument or GPIO initialization error. */
    DALI2_ERROR_TIMEOUT = -2,    /**< No backward frame started within the response window. */
    DALI2_ERROR_BUSY = -3,       /**< Bus did not remain idle before transmission. */
    DALI2_ERROR_FRAME = -4       /**< Invalid start bit, Manchester transition, or stop condition. */

} dali2_return_value_t;

/*!
 * @addtogroup dali2 DALI 2 Click Driver
 * @brief API for configuring and manipulating DALI 2 Click driver.
 * @{
 */

/**
 * @brief DALI 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dali2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dali2_cfg_setup ( dali2_cfg_t *cfg );

/**
 * @brief DALI 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dali2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dali2_init ( dali2_t *ctx, dali2_cfg_t *cfg );

/**
 * @brief DALI 2 default configuration function.
 * @details This function releases TX and checks that the powered DALI bus is idle.
 * It does not change the addresses or settings of connected control gear.
 * @param[in] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @return @li @c DALI2_OK - Bus is idle and ready,
 *         @li @c DALI2_ERROR_BUSY - Bus is busy or bus power is missing.
 * See #dali2_return_value_t definition for detailed explanation.
 * @note Connect an external, current-limited DALI bus power supply before calling this function.
 */
err_t dali2_default_cfg ( dali2_t *ctx );

/**
 * @brief DALI 2 generic write function.
 * @details This function waits for bus idle, then transmits the address and data bytes,
 * MSB first, with a start bit and two idle stop bits. TX is released when the function returns.
 * @param[in] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @param[in] address : Fully encoded address byte, including the command selector bit,
 * or a special-command opcode.
 * @param[in] data_in : Command, arc power level, or special-command parameter.
 * @return @li @c DALI2_OK - Frame transmitted,
 *         @li @c DALI2_ERROR_BUSY - Bus is not available.
 * See #dali2_return_value_t definition for detailed explanation.
 * @note Successful transmission does not confirm that control gear received the frame.
 * Call dali2_read_response immediately after a query. Configuration and commissioning
 * command repetition requirements must be handled by the caller; this function sends once.
 */
err_t dali2_generic_write ( dali2_t *ctx, uint8_t address, uint8_t data_in );

/**
 * @brief DALI 2 read response function.
 * @details This function waits for a response and decodes one byte, resynchronizing at each
 * Manchester bit transition. The output is updated only after a complete frame with valid stop bits.
 * @param[in] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @param[out] data_out : Received byte.
 * @return @li @c DALI2_OK - Backward frame received,
 *         @li @c DALI2_ERROR - Output pointer is NULL,
 *         @li @c DALI2_ERROR_TIMEOUT - No backward frame received,
 *         @li @c DALI2_ERROR_FRAME - Invalid frame.
 * See #dali2_return_value_t definition for detailed explanation.
 * @note Call immediately after transmitting a query, without logging or delaying first.
 * For yes/no queries, no reply can mean "no"; it is not distinguishable from an absent device.
 */
err_t dali2_read_response ( dali2_t *ctx, uint8_t *data_out );

/**
 * @brief DALI 2 send command function.
 * @details This function encodes the selected destination and sends one command frame.
 * @param[in] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @param[in] address : Short address 0 to 63, group address 0 to 15, or any value for broadcast.
 * @param[in] address_type : Selects one device, a group, or all bus devices respectively.
 * @param[in] command : DALI command byte.
 * @return @li @c DALI2_OK - Command transmitted,
 *         @li @c DALI2_ERROR - Invalid address or address type,
 *         @li @c DALI2_ERROR_BUSY - Bus is not available.
 * See #dali2_return_value_t definition for detailed explanation.
 * @note No automatic repetition is performed. Use dali2_query for a command expecting a reply.
 */
err_t dali2_send_command ( dali2_t *ctx, uint8_t address, uint8_t address_type, uint8_t command );

/**
 * @brief DALI 2 set level function.
 * @details This function sends a direct arc power control frame to one device, a group,
 * or all control gear.
 * @param[in] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @param[in] address : Short address 0 to 63, group address 0 to 15, or any value for broadcast.
 * @param[in] address_type : Selects one device, a group, or all bus devices respectively.
 * @param[in] level : 0 for off, 1 to 254 for an arc power level, or 255 for MASK.
 * @return @li @c DALI2_OK - Arc power level transmitted,
 *         @li @c DALI2_ERROR - Invalid address or address type,
 *         @li @c DALI2_ERROR_BUSY - Bus is not available.
 * See #dali2_return_value_t definition for detailed explanation.
 * @note Control gear applies its configured minimum, maximum, fade time, and dimming curve.
 */
err_t dali2_set_level ( dali2_t *ctx, uint8_t address, uint8_t address_type, uint8_t level );

/**
 * @brief DALI 2 query function.
 * @details This function sends a query to a short address and immediately reads its backward frame.
 * @param[in] ctx : Click context object.
 * See #dali2_t object definition for detailed explanation.
 * @param[in] address : Commissioned short address from 0 to 63.
 * @param[in] command : Query command byte, for example DALI2_CMD_QUERY_STATUS.
 * @param[out] response : Received byte; unchanged if the query fails.
 * @return @li @c DALI2_OK - Query response received,
 *         @li @c DALI2_ERROR - Invalid argument,
 *         @li @c DALI2_ERROR_BUSY - Bus is not available,
 *         @li @c DALI2_ERROR_TIMEOUT - No response received,
 *         @li @c DALI2_ERROR_FRAME - Invalid response frame.
 * See #dali2_return_value_t definition for detailed explanation.
 * @note Group and broadcast queries are intentionally excluded to avoid colliding replies.
 * No reply to a yes/no query can indicate "no" or an absent device.
 */
err_t dali2_query ( dali2_t *ctx, uint8_t address, uint8_t command, uint8_t *response );

#ifdef __cplusplus
}
#endif
#endif // DALI2_H

/*! @} */ // dali2

// ------------------------------------------------------------------------ END
