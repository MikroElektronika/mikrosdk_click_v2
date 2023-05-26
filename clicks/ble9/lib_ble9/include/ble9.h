/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
 * @file ble9.h
 * @brief This file contains API for BLE 9 Click driver.
 * @addtogroup ble9 BLE 9 Click Driver
 * @{
 */

#ifndef _BLE9_H_
#define _BLE9_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_uart.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BLE9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BLE9_OK                                                 0
#define BLE9_ERROR                                             -1
/** \} */

/**
 * \defgroup response_states  Response states
 * \{
 */
#define BLE9_RSP_READY                                          1
#define BLE9_RSP_NOT_READY                                      0
/** \} */

/**
 * \defgroup commands  Command constants
 * \{
 */

/*!< @brief System commands. */
#define BLE9_CMD_SYSTEM_HELLO_ID                                0x00010020ul
#define BLE9_CMD_SYSTEM_DATA_BUFFER_CLEAR_ID                    0x14010020ul
#define BLE9_CMD_SYSTEM_RESET_ID                                0x01010020ul
#define BLE9_CMD_SYSTEM_HALT_ID                                 0x2001010Cul
#define BLE9_CMD_SYSTEM_SET_TX_POWER_ID                         0x17010020ul
#define BLE9_CMD_SYSTEM_GET_VERSION_ID                          0x1B010020ul
#define BLE9_CMD_SYSTEM_SET_SOFT_TIMER_ID                       0x19010020ul
#define BLE9_CMD_SYSTEM_SET_LAZY_SOFT_TIMER_ID                  0x1A010020ul
#define BLE9_CMD_SYSTEM_SET_IDENTITY_ADDRESS_ID                 0x13010020ul
#define BLE9_CMD_SYSTEM_GET_IDENTITY_ADDRESS_ID                 0x15010020ul
#define BLE9_CMD_SYSTEM_DATA_BUFFER_WRITE_ID                    0x12010020ul

/*!< @brief GAP commands. */
#define BLE9_CMD_GAP_SET_PRIVACY_MODE_ID                        0x01020020ul
#define BLE9_CMD_GAP_ENABLE_WHITELISTING_ID                     0x03020020ul

/*!< @brief Advertiser commands. */
#define BLE9_CMD_ADVERTISER_CREATE_ID                           0x01040020ul
#define BLE9_CMD_ADVERTISER_DELETE_SET_ID                       0x02040020ul
#define BLE9_CMD_ADVERTISER_START_ID                            0x09040320ul
#define BLE9_CMD_ADVERTISER_STOP_ID                             0x0A040020ul
#define BLE9_CMD_ADVERTISER_SET_TIMING_ID                       0x03040020ul
#define BLE9_CMD_ADVERTISER_SET_PHY_ID                          0x06040020ul
#define BLE9_CMD_ADVERTISER_SET_CHANNEL_MAP_ID                  0x04040020ul
#define BLE9_CMD_ADVERTISER_SET_TX_POWER_ID                     0x0B040020ul
#define BLE9_CMD_ADVERTISER_SET_REPORT_SCAN_REQUEST_ID          0x05040020ul
#define BLE9_CMD_ADVERTISER_SET_CONFIGURATION_ID                0x07040020ul
#define BLE9_CMD_ADVERTISER_CLEAR_CONFIGURATION_ID              0x08040020ul
#define BLE9_CMD_ADVERTISER_SET_DATA_ID                         0x0F040020ul
#define BLE9_CMD_ADVERTISER_SET_LONG_DATA_ID                    0x0E040020ul
#define BLE9_CMD_ADVERTISER_START_PERIODIC_ADVERTISING_ID       0x0C040020ul
#define BLE9_CMD_ADVERTISER_STOP_PERIODIC_ADVERTISING_ID        0x0D040020ul

/*!< Helper macros. */
#define BLE9_CMD_NULL                                           0
#define BLE9_SYSTEM_RESUME                                      0
#define BLE9_SYSTEM_HALT                                        1

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE                                      100
#define DRV_TX_BUFFER_SIZE                                      100
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * @details Predefined enum values for dfu reset.
 */
typedef enum
{
    /*!< @brief Boot to normal mode. */
    BLE9_DFU_RESET_MODE_NORMAL = 0,
    /*!< @brief Boot to UART DFU mode. */
    BLE9_DFU_RESET_MODE_UART,
    /*!< @brief Boot to OTA DFU mode. */
    BLE9_DFU_RESET_MODE_OTA
    
} ble9_dfu_reset_mode_t;

/*!< @brief Enum containing predefined
channel selections. */
typedef enum
{
    BLE9_CHANNEL_37 = 0,
    BLE9_CHANNEL_38,
    BLE9_CHANNEL_37_38,
    BLE9_CHANNEL_39,
    BLE9_CHANNEL_37_39,
    BLE9_CHANNEL_38_39,
    BLE9_CHANNEL_ALL
    
} ble9_channel_t;

typedef enum
{
    /*!< @brief (0x1) 1M PHY. */
    BLE9_PHY_TYPE_1M = 1,
    /*!< @brief (0x1) 2M PHY. */
    BLE9_PHY_TYPE_2M,
    /*!< @brief (0x4) Coded PHY,
    125k (S=8) or 500k (S=2). */
    BLE9_PHY_TYPE_CODED,
    /*!< @brief (0xFF) Any PHYs
    the device supports. */
    BLE9_PHY_TYPE_ANY = 0xFF
    
} ble9_phy_type_t;

typedef enum
{
    /*!< @brief Advertising packets. */
    BLE9_PACKAGE_TYPE_ADVERTISING = 0,
    /*!< @brief Scan response packets. */
    BLE9_PACKAGE_TYPE_SCAN_RESPONSE,
    /*!< @brief Periodic advertising packets. */
    BLE9_PACKAGE_TYPE_PERIODIC_ADVERTISING = 8
    
} ble9_package_type_t;

typedef enum
{
    /*!< @brief Not discoverable. */
    BLE9_ADVERTISER_MODE_DISCOVERABLE_NONE = 0,
    /*!< @brief Discoverable using both limited and
    general discovery procedures. */
    BLE9_ADVERTISER_MODE_DISCOVERABLE_LIMITED,
    /*!< @brief Discoverable using general
    discovery procedure */
    BLE9_ADVERTISER_MODE_DISCOVERABLE_GENERAL,
    /*!< @brief Device is not discoverable in either
    limited or generic discovery procedure but may be
    discovered using the Observation procedure. */
    BLE9_ADVERTISER_MODE_DISCOVERABLE_BROADCAST,
    /*!< @brief Send advertising and/or scan response
    data defined by the user. The limited/general
    discoverable flags are defined by the user.*/
    BLE9_ADVERTISER_MODE_DISCOVERABLE_USER_DATA
    
} ble9_adv_mode_discoverable_t;

typedef enum
{
    /*!< @brief Non-connectable non-scannable */
    BLE9_ADVERTISER_MODE_CONNECTABLE_NONE = 0,
    /*!< @brief Directed connectable
    (RESERVED, DO NOT USE) */
    BLE9_ADVERTISER_MODE_CONNECTABLE_DIRECTED,
    /*!< @brief Undirected connectable scannable.
    This mode can only be used in legacy advertising PDUs. */
    BLE9_ADVERTISER_MODE_CONNECTABLE_SCANNABLE,
    /*!< @brief Undirected scannable (Non-connectable
    but responds to scan requests) */
    BLE9_ADVERTISER_MODE_CONNECTABLE_NONE_CONNECTABLE,
    /*!< @brief Undirected connectable non-scannable.
    This mode can only be used in extended advertising PDUs. */
    BLE9_ADVERTISER_MODE_CONNECTABLE_NONE_SCANABLE
    
} ble9_adv_mode_connectable_t;

/**
 * \defgroup type Types
 * \{
 */
typedef struct
{
    /*!< @brief Major release version. */
    uint16_t version_major;
    /*!< @brief Minor release version. */
    uint16_t version_minor;
    /*!< @brief Patch release version. */
    uint16_t version_patch;
    /*!< @brief Build number. */
    uint16_t version_build;
    /*!< @brief Bootloader version. */
    uint32_t version_bootloader;
    /*!< @brief Version hash. */
    uint32_t version_hash;
    
} ble9_version_t;

typedef struct
{
    /*!< @brief Timer handle to use, which is returned in timeout event. */
    uint8_t  ble9_timer_handle;
    /*!< @brief Timer mode.
    Values:
    @b 0: false (timer is repeating)
    @b 1: true (timer runs only once) */
    uint8_t  ble9_timer_single_shot;
    /*!< @brief Frequency interval of events, which indicates how often to send
    events in hardware clock ticks (1 second is equal to 32768 ticks).
    The smallest supported interval value is 328, which is around 10 milliseconds.
    Any parameters between 0 and 328 will be rounded up to 328.
    The maximum value is 2147483647, which corresponds to about 18.2 hours.
    If time is 0, removes the scheduled timer with the same handle. */
    uint32_t ble9_timer_time;
    /*!< @brief Slack time in hardware clock ticks. */
    uint32_t ble9_timer_slack;
    
} ble9_timer_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    uint8_t ble9_adv_handle;
    ble9_version_t ble9_version;
    // Modules
    uart_t uart;

    uint8_t uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    uint8_t uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];
    
} ble9_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;
    pin_name_t tx_pin;

    // Static variables
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking; // Wait for data or not.
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.
    uart_stop_bits_t  stop_bit;      // Stop bits.
    
} ble9_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 * @description This function initializes click configuration structure to default state.
 *
 * @note All used pins will be set to unconnected state.
 */
void ble9_cfg_setup ( ble9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * @description This function initializes all necessary pins and peripherals used for this click.
 *
 * @return err_t
 */
err_t ble9_init ( ble9_t *ctx, ble9_cfg_t *cfg );

/**
 * @brief Verify whether the communication between the host and
 * the device is functional.
 *
 * @param ctx Click object.
 *
 * @return err_t
 */
err_t ble9_sys_hello ( ble9_t *ctx );

/**
 * @brief Get the firmware version information.
 *
 * @b ctx->ble9_version @b values:
 * Field               | Description               |
 * --------------------|---------------------------|
 * version_major       | Major release version     |
 * version_minor       | Minor release version     |
 * version_patch       | Patch release number      |
 * version_build       | Build number              |
 * version_bootloader  | Bootloader version        |
 * version_hash        | Version hash              |
 *
 * @param ctx Click object.
 *
 * @return err_t
 *
 * @note See #ble9_version_t for more information.
 */
err_t ble9_sys_get_version ( ble9_t *ctx );

/**
 * @brief Set the device's Bluetooth identity address.
 * The address can be a public device address or a static device address.
 * A valid address set with this command will be written into persistent storage using NVM keys.
 * The stack returns an error if the static device address does not conform to the Bluetooth specification.
 * The new address will be effective in the next system reboot.
 * The stack will use the address in the NVM keys when present.
 * Otherwise, it uses the default Bluetooth public device address which is programmed at production.
 * The stack treats 00:00:00:00:00:00 and ff:ff:ff:ff:ff:ff as invalid addresses.
 * Therefore, passing one of them into this command will cause the stack to delete the NVM keys
 * and use the default address in the next system reboot.
 *
 * @param ctx Click object.
 * @param address Bluetooth identity address in little endian format.
 * @param type Address type.
 *             @b 1 Static device address
 *             @b 0 Public device address
 *
 * @note Because the NVM keys are located in flash and flash wearing can occur,
 * avoid calling this command regularly.
 */
void ble9_sys_set_id_addr ( ble9_t *ctx, uint8_t *address, uint8_t type );

/**
 * @brief Read the Bluetooth identity address used by the device,
 * which can be a public or random static device address.
 *
 * @param ctx Click object.
 * @param data_buf Array address for storing return values.
 * @param type Address type.
 *             @b 1 Static device address
 *             @b 0 Public device address
 *
 * @return err_t
 */
err_t ble9_sys_get_id_address ( ble9_t *ctx, uint8_t *data_buf, uint8_t type );

/**
 * @brief Reset the system. The command does not have a response but it triggers
 * one of the boot events (normal reset or boot to DFU mode) depending
 * on the selected boot mode.
 *
 * @param ctx Click object.
 * @param reset_mode See #ble9_dfu_reset_mode_t for more information.
 */
void ble9_sys_reset ( ble9_t *ctx, ble9_dfu_reset_mode_t reset_mode );

/**
 * @brief Force radio to idle state and allow device to sleep. Advertising, scanning,
 * connections, and software timers are halted by this command.
 * Halted operations resume after calling this command with parameter 0.
 * Connections stay alive if the system is resumed before connection supervision timeout.
 *
 * @param ctx Click object.
 * @param halt @b 1 halt
 *             @b 0 resume
 *
 * @return err_t
 *
 * @note Use this command only for a short time period (a few seconds at maximum).
 * Although it halts Bluetooth activity, all tasks and operations still exist inside
 * the stack with their own concepts of time. Halting the system for a long period
 * of time may have negative consequences on stack's internal states.
 *
 * @warning The software timer is also halted. Hardware interrupts are the
 * only way to wake up from energy mode 2 when the system is halted.
 */
err_t ble9_sys_halt ( ble9_t *ctx, uint8_t halt );

/**
 * @brief Set the global minimum and maximum radiated TX power levels for Bluetooth.
 * This returns selected power levels that are radiated from the antenna at TX.
 * The transmitter power at antenna pin will apply the RF TX path gain to match this setting.
 * RF TX path gain can be set in the Bluetooth configuration. If the GATT server contains a
 * TX power service, the TX Power Level attribute will be updated with the selected maximum power level.
 * A selected power level may be different than the requested value if the device cannot
 * meet the requirement. For Bluetooth connections, the maximum radiated TX power is limited to 10 dBm
 * if Adaptive Frequency Hopping (AFH) is not enabled.
 * The minimum TX power setting is used by LE power control. It has no effect in Bluetooth stack
 * if the LE power control feature is not enabled. However, the application may still use this setting
 * for other purposes, e.g., setting the minimum TX power for DTM transmitter test.
 * The minimum and maximum radiated TX power levels can also be configured in the Bluetooth configuration
 * and passed into the Bluetooth stack initialization. By default, the minimum radiated TX power
 * level is configured to -3 dBm and the maximum radiated TX power level to 8 dBm.
 *
 * @param ctx Click object.
 * @param min_power Minimum radiated TX power. Unit: 0.1 dBm. For example, the value 10 means 1 dBm.
 * @param max_power Maximum radiated TX power. Unit: 0.1 dBm. For example, the value 10 means 1 dBm.
 *
 * @warning Do not use this command while advertising or scanning. Furthermore, the
 * stack does not allow setting TX powers during connections.
 */
void ble9_sys_set_tx_power ( ble9_t *ctx, int16_t min_power, int16_t max_power );

/**
 * @brief Write data into the system data buffer.
 * Data will be appended to the end of existing data.
 *
 * @param ctx Click object.
 * @param data_len Array length.
 * @param wr_data Data to write.
 *
 * @return err_t
 */
err_t ble9_sys_data_buf_write ( ble9_t *ctx, uint16_t data_len, uint8_t *wr_data );

/**
 * @brief Remove all data from the system data buffer.
 *
 * @param ctx Click object.
 *
 * @return err_t
 */
err_t ble9_sys_data_buf_clear ( ble9_t *ctx );

/**
 * @brief Start a software timer. Multiple concurrent timers can be running simultaneously.
 * 256 unique timer handles (IDs) are available. The maximum number of concurrent timers
 * is configurable at device initialization. Up to 16 concurrent timers can be configured.
 * The default configuration is 4. As the RAM for storing timer data is pre-allocated
 * at initialization, an application should not configure the amount more than it needs
 * for minimizing RAM usage.
 *
 * @param ctx Click object.
 * @param ble9_timer Timer structure. See #ble9_timer_t for more information.
 *
 * @return err_t
 */
err_t ble9_sys_set_soft_timer ( ble9_t  *ctx, ble9_timer_t *ble9_timer );

/**
 * @brief Start a software timer with slack. The slack parameter allows the
 * stack to optimize wakeups and save power. The timer event is triggered between
 * time and time + slack
 *
 * @param ctx Click object.
 * @param ble9_timer Timer structure. See #ble9_timer_t for more information.
 *
 * @return err_t
 */
err_t ble9_sys_set_lazy_soft_timer ( ble9_t *ctx, ble9_timer_t *ble9_timer );

/**
 * @brief Enable or disable the privacy feature on all GAP roles.
 * New privacy mode will take effect for advertising next time advertising is enabled,
 * for scanning next time scanning is enabled, and for initiating on the next
 * open connection command. When privacy is enabled and the device is advertising or scanning,
 * the stack will maintain a periodic timer with the specified time interval as a timeout value.
 * At each timeout, the stack will generate a new private resolvable address and use it in
 * advertising data packets and scanning requests.
 * By default, privacy feature is disabled.
 *
 * @param ctx Click object.
 * @param privacy @b 1 Enable privacy
 *                @b 0 Disable privacy
 * @param interval_in_minutes The minimum time interval between a private address change.
 * This parameter is ignored if this command is issued to disable privacy mode.
 * Values:
 * @b 0: Use default interval, 15 minutes.
 * @b n: The time interval in minutes.
 *
 * @return err_t
 */
err_t ble9_gap_set_privacy_mode ( ble9_t *ctx, uint8_t privacy, uint8_t interval_in_minutes );

/**
 * @brief Enable or disable whitelisting. The setting will be effective the next time
 * that scanning is enabled.
 *
 * @param ctx Click object.
 * @param enable @b 1 Enable
 *               @b 0 Disable
 *
 * @return err_t
 */
err_t ble9_gap_en_wlist ( ble9_t *ctx, uint8_t enable );

/**
 * @brief Create an advertising ID. The handle of the created advertising
 * ID is returned in response.
 *
 * @param ctx Click object.
 *
 * @return err_t
 */
err_t ble9_adv_create_id ( ble9_t *ctx );

/**
 * @brief Delete an advertising ID.
 *
 * @param ctx Click object.
 *
 * @return err_t
 */
err_t ble9_adv_delete_id ( ble9_t *ctx );

/**
 * @brief Set the advertising timing parameters of the given advertising set.
 * This setting will take effect next time that advertising is enabled.
 *
 * @param ctx Click object.
 * @param interval_min Minimum advertising interval. Value in units of 0.625 ms
 * Range: 0x20 to 0xFFFF
 * Time range: 20 ms to 40.96 s
 * Default value: 100 ms
 * @param interval_max Maximum advertising interval. Value in units of 0.625 ms
 * Range: 0x20 to 0xFFFF
 * Time range: 20 ms to 40.96 s
 * Note: interval_max should be bigger than interval_min
 * Default value: 200 ms
 * @param duration Advertising duration for this advertising set.
 * Value 0 indicates no advertising duration limit and advertising continues until it is disabled.
 * A non-zero value sets the duration in units of 10 ms.
 * The duration begins at the start of the first advertising event of this advertising set.
 * Range: 0x0001 to 0xFFFF
 * Time range: 10 ms to 655.35 s
 * Default value: 0
 * @param maxevents If non-zero, indicates the maximum number of advertising events
 * to send before the advertiser is stopped. Value 0 indicates no maximum number limit.
 * Default value: 0
 *
 * @return err_t
 */
err_t ble9_adv_set_timing ( ble9_t *ctx, uint16_t interval_min, uint16_t interval_max, 
                            uint16_t duration, uint8_t maxevents );

/**
 * @brief Set advertising PHYs of the given advertising set. This setting will take
 * effect next time that advertising is enabled. The invalid parameter error is
 * returned if a PHY value is invalid or the device does not support a given PHY.
 *
 * @param ctx Click object.
 * @param primary_phy The PHY on which the advertising packets are transmitted on the primary advertising channel.
 * If legacy advertising PDUs are used, 1M PHY must be used.
 * @param secondary_phy The PHY on which the advertising packets are transmitted on the secondary advertising channel.
 *
 * @note See #ble9_phy_type_t for more information.
 *
 * @return err_t
 */
err_t ble9_adv_set_phy ( ble9_t *ctx, ble9_phy_type_t primary_phy, ble9_phy_type_t secondary_phy );

/**
 * @brief Set the primary advertising channel map of the given advertising set.
 * This setting will take effect next time that advertising is enabled.
 *
 * @param ctx Click object.
 * @param channel_map Advertising channel map which determines which of the three channels will be used for advertising.
 * This value is given as a bitmask.
 *
 * @return err_t
 *
 * @note See #ble9_channel_t for more information.
 * @note Recommended value: 7
 */
err_t ble9_adv_set_channel_map ( ble9_t *ctx, ble9_channel_t channel_map );

/**
 * @brief Limit the maximum advertising TX power on the given advertising set.
 * The maximum TX power of legacy advertising is further constrained to be less than +10 dBm.
 * Extended advertising TX power can be +10 dBm and over if Adaptive Frequency Hopping is enabled.
 * This setting will take effect next time advertising is enabled.
 *
 * @param ctx Click object.
 * @param power TX power in 0.1 dBm steps. For example, the value of 10 is 1 dBm and 55 is 5.5 dBm.
 * @param set_power The selected maximum advertising TX power.
 *
 * @return err_t
 */
err_t ble9_adv_set_tx_power ( ble9_t *ctx, int16_t power, int16_t *set_power );

/**
 * @brief Enable or disable the scan request notification of a given advertising set.
 * This setting will take effect next time that advertising is enabled.
 *
 * @param ctx Click object.
 * @param report_scan_req If non-zero, enables scan request notification and scan requests will be reported as events.
 * Default value: 0
 *
 * @return err_t
 */
err_t ble9_adv_set_report_scan_req ( ble9_t *ctx, uint8_t report_scan_req );

/**
 * @brief Enable advertising configuration flags on the given advertising set.
 * The configuration change will take effect next time that advertising is enabled.
 * These configuration flags can be disabled using #ble9_adv_clear_configuration.
 *
 * @param ctx Click object.
 * @param configurations Advertising configuration flags to enable. This value can be a bitmask of multiple flags.
 * @b Flags:
 * 1 (Bit 0): Use legacy advertising PDUs.
 * 2 (Bit 1): Omit advertiser's address from all PDUs (anonymous advertising). This flag is effective only in extended advertising.
 * 4 (Bit 2): Use gap_non_resolvable address type. Advertising must be in non-connectable mode if this configuration is enabled.
 * 8 (Bit 3): Include TX power in advertising packets. This flag is effective only in extended advertising.
 * Default value: 1
 *
 * @return err_t
 */
err_t ble9_adv_set_configuration ( ble9_t *ctx, uint8_t configurations );

/**
 * @brief Disable advertising configuration flags on the given advertising set.
 * The configuration change will take effect next time that advertising is enabled.
 * These configuration flags can be enabled using #ble9_adv_set_configuration.
 *
 * @param ctx Click object.
 * @param configurations Advertising configuration flags to disable.
 * This value can be a bitmask of multiple flags. See #ble9_adv_set_configuration for possible flags.
 *
 * @return err_t
 */
err_t ble9_adv_clear_configuration ( ble9_t *ctx, uint8_t configurations );

/**
 * @brief Set user-defined data in advertising packets, scan response packets, or periodic advertising packets.
 * Maximum 31 bytes of data can be set for legacy advertising. Maximum 191 bytes of data can be set for
 * connectable extended advertising. Maximum 253 bytes of data can be set for periodic and non-connectable
 * extended advertising. For setting longer advertising data, use command #ble9_adv_set_long_data.
 * If advertising mode is currently enabled, the new advertising data will be used immediately.
 * Advertising mode can be enabled using command #ble9_adv_start. Periodic advertising mode can be enabled
 * using command #ble9_adv_start_per_adv.
 * The invalid parameter error will be returned in the following situations:
 * Data length is more than 31 bytes but the advertiser can only advertise using legacy advertising PDUs.
 * Data is too long to fit into a single advertisement.
 * Set data of the advertising data packet when the advertiser is advertising in scannable mode using
 * extended advertising PDUs. Set data of the scan response data packet when the advertiser is advertising in
 * connectable mode using extended advertising PDUs. Note that the user-defined data may be overwritten by the
 * system when the advertising is later enabled in a discoverable mode other than user_data.
 *
 * @param ctx Click object.
 * @param packet_type This value selects whether data is intended for advertising packets,
 * scan response packets, or periodic advertising packets.
 * @b Values:
 * Field          | Description                  |
 * ---------------|------------------------------|
 * @b 0           | Advertising packets          |
 * @b 1           | Scan response packets        |
 * @b 8           | Periodic advertising packets |
 * @param adv_data_len Array length.
 * @param adv_data Data to be set.
 *
 * @return err_t
 *
 * @note See #ble9_package_type_t for more information.
 */
err_t ble9_adv_set_data ( ble9_t *ctx, ble9_package_type_t packet_type, 
                          uint16_t adv_data_len, uint8_t *adv_data );

/**
 * @brief Set advertising data for a specified packet type and advertising set.
 * Data currently in the system data buffer will be extracted as the advertising data.
 * The buffer will be emptied after this command regardless of the completion status.
 * Prior to calling this command, add data to the buffer with one or multiple calls to
 * #ble9_sys_data_buffer_write.
 * Maximum 31 bytes of data can be set for legacy advertising. Maximum 191 bytes of data
 * can be set for connectable extended advertising. Maximum 1650 bytes of data can be
 * set for periodic and non-connectable extended advertising, but advertising parameters
 * may limit the amount of data that can be sent in a single advertisement.
 * See #ble9_adv_set_data for more details on advertising data.
 *
 * @param ctx Click object.
 * @param packet_type This value selects whether data is intended for advertising packets,
 * scan response packets, or periodic advertising packets.
 * @b Values:
 * Field          | Description                  |
 * ---------------|------------------------------|
 * @b 0           | Advertising packets          |
 * @b 1           | Scan response packets        |
 * @b 8           | Periodic advertising packets |
 *
 * @return err_t
 *
 * @note See #ble9_package_type_t for more information.
 */
err_t ble9_adv_set_long_data ( ble9_t *ctx, ble9_package_type_t packet_type );

/**
 * @brief Start advertising of a given advertising set with specified discoverable and connectable modes.
 * The number of concurrent advertising is limited by MAX_ADVERTISERS configuration.
 * The number of concurrent connectable advertising is also limited by MAX_CONNECTIONS configuration.
 * For example, only one connectable advertising can be enabled if the device has (MAX_CONNECTIONS - 1)
 * connections when this command is called. The limitation does not apply to non-connectable advertising.
 * The default advertising configuration in the stack is set to using legacy advertising PDUs on 1M PHY.
 *
 * @param ctx Click object.
 * @param discover Discoverable mode. See #ble9_adv_mode_discoverable_t for more information.
 * @param connect Connectable mode. See #ble9_adv_mode_connectable_t for more information.
 *
 * @return err_t
 *
 * @warning @b BLE9_ADVERTISER_MODE_CONNECTABLE_DIRECTED is reserver. Do not use it.
 */
err_t ble9_adv_start ( ble9_t *ctx, ble9_adv_mode_discoverable_t discover, 
                       ble9_adv_mode_connectable_t connect );

/**
 * @brief Stop the advertising of the given advertising set. Counterpart with #ble9_adv_start.
 * This command does not affect the enable state of the periodic advertising set, i.e.,
 * periodic advertising is not stopped.
 *
 * @param ctx Click object.
 *
 * @return err_t
 */
err_t ble9_adv_stop ( ble9_t *ctx );

/**
 * @brief Start periodic advertising on the given advertising set. The stack enables the advertising
 * set automatically if the set was not enabled and the set can advertise using extended advertising
 * PDUs beside the syncInfo, which is needed for the periodic advertising.
 * The invalid parameter error is returned if the application has configured legacy advertising PDUs
 * or anonymous advertising, or the advertising set is enabled using legacy advertising PDUs.
 * To stop periodic advertising, use #ble9_adv_stop_per_adv command with the
 * handle received in response from this command.
 *
 * @param ctx Click object.
 * @param interval_min Minimum periodic advertising interval. Value in units of 1.25 ms.
 * Field          | Description       |
 * ---------------|-------------------|
 * Range          | 0x06 to 0xFFFF    |
 * Time range     | 7.5 ms to 81.92 s |
 * Default value  | 100 ms            |
 * @param interval_max Maximum periodic advertising interval. Value in units of 1.25 ms.
 * Field          | Description       |
 * ---------------|-------------------|
 * Range          | 0x06 to 0xFFFF    |
 * Time range     | 7.5 ms to 81.92 s |
 * Default value  | 200 ms            |
 * @param flags Periodic advertising configurations. Bitmask of the following:
 * Bit 0: Include TX power in advertising PDU.
 * @return err_t
 *
 * @note @b interval_max should be bigger than @b interval_min
 */
err_t ble9_adv_start_per_adv ( ble9_t *ctx, uint16_t interval_min, uint16_t interval_max, uint8_t flags );

/**
 * @brief Stop the periodic advertising on the given advertising set.
 * Counterpart with #ble9_adv_start_per_adv.
 * This command does not affect the enable state of the advertising set, i.e.,
 * legacy or extended advertising is not stopped.
 *
 * @param ctx Click object.
 *
 * @return err_t
 */
err_t ble9_adv_stop_per_adv( ble9_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer.
 * @param len Length of data to be written.
 */
void ble9_generic_write ( ble9_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer.
 * @param max_len Maximum length of data that can be read.
 *
 * @return Number of bytes read.
 */
int32_t ble9_generic_read ( ble9_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Function for transmiting commands.
 *
 * @param ctx Click object.
 * @param command Command to be transmitted.
 *
 * @description This function allows the user to transmit data and send commands to the module.
 */
void ble9_send_command ( ble9_t *ctx, uint32_t command );

#ifdef __cplusplus
}
#endif
#endif  // _BLE9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------- END
