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
 * @file ninab222.h
 * @brief This file contains API for NINA-B222 Click Driver.
 */

#ifndef NINAB222_H
#define NINAB222_H

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
 * @addtogroup ninab222 NINA-B222 Click Driver
 * @brief API for configuring and manipulating NINA-B222 Click driver.
 * @{
 */

/**
 * @defgroup ninab222_cmd NINA-B222 Device Settings
 * @brief Settings for registers of NINA-B222 Click driver.
 */

/**
 * @addtogroup ninab222_cmd
 * @{
 */

/**
 * @brief NINA-B222 AT command.
 * @details Specified setting for AT command of NINA-B222 Click driver.
 */
#define NINAB222_CMD_AT                    "AT"

/**
 * @brief NINA-B222 general commands.
 * @details Specified setting for general commands of NINA-B222 Click driver.
 */
#define NINAB222_CMD_CGMI                  "CGMI"
#define NINAB222_CMD_CGMM                  "CGMM"
#define NINAB222_CMD_CGMR                  "CGMR"
#define NINAB222_CMD_CGSN                  "CGSN"
#define NINAB222_CMD_GMI                   "GMI"
#define NINAB222_CMD_GMM                   "GMM"
#define NINAB222_CMD_GMR                   "GMR"
#define NINAB222_CMD_GSN                   "GSN"
#define NINAB222_CMD_ATI                   "ATI"
#define NINAB222_CMD_CSGT                  "CSGT"

/**
 * @brief NINA-B222 system commands.
 * @details Specified setting for system commands of NINA-B222 Click driver.
 */
#define NINAB222_CMD_ATW                   "W"
#define NINAB222_CMD_ATZ                   "ATZ"
#define NINAB222_CMD_ATE                   "ATE"
#define NINAB222_CMD_UFACTORY              "UFACTORY"
#define NINAB222_CMD_ATD                   "D"
#define NINAB222_CMD_ATS                   "S"
#define NINAB222_CMD_CPWROFF               "CPWROFF"
#define NINAB222_CMD_UFWUPD                "UFWUPD"
#define NINAB222_CMD_UMLA                  "UMLA"
#define NINAB222_CMD_UMLPO                 "UMLPO"
#define NINAB222_CMD_UMRS                  "UMRS"
#define NINAB222_CMD_UMRSCFG               "UMRSCFG"
#define NINAB222_CMD_UMRSIG                "UMRSIG"
#define NINAB222_CMD_UMSM                  "UMSM"
#define NINAB222_CMD_UMSTAT                "UMSTAT"
#define NINAB222_CMD_UPWRMNG               "UPWRMNG"
#define NINAB222_CMD_UPWRREG               "UPWRREG"
#define NINAB222_CMD_USTOP                 "USTOP"

/**
 * @brief NINA-B222 data mode commands.
 * @details Specified setting for data mode commands of NINA-B222 Click driver.
 */
#define NINAB222_CMD_ATO                   "ATO"
#define NINAB222_CMD_UDATR                 "UDATR"
#define NINAB222_CMD_UDATW                 "UDATW"
#define NINAB222_CMD_UDBIND                "UDBIND"
#define NINAB222_CMD_UDBINDC               "UDBINDC"
#define NINAB222_CMD_UDCFG                 "UDCFG"
#define NINAB222_CMD_UDCP                  "UDCP"
#define NINAB222_CMD_UDCPC                 "UDCPC"
#define NINAB222_CMD_UDDRP                 "UDDRP"
#define NINAB222_CMD_UDLP                  "UDLP"
#define NINAB222_CMD_UDSC                  "UDSC"
#define NINAB222_CMD_UDSF                  "UDSF"
#define NINAB222_CMD_UDUV                  "UDUV"
#define NINAB222_CMD_UDWS                  "UDWS"
#define NINAB222_CMD_UUDATA                "UUDATA"
#define NINAB222_CMD_UUDPC                 "UUDPC"
#define NINAB222_CMD_UUDPD                 "UUDPD"
   
/**
 * @brief NINA-B222 bluetooth commands.
 * @details Specified setting for bluetooth commands of NINA-B222 Click driver.
 */
#define NINAB222_CMD_UBTDM                 "UBTDM"
#define NINAB222_CMD_UBTCM                 "UBTCM"
#define NINAB222_CMD_UBTPM                 "UBTPM"
#define NINAB222_CMD_UBTSM                 "UBTSM"
#define NINAB222_CMD_UBTST                 "UBTST"
#define NINAB222_CMD_UBTUC                 "UBTUC"
#define NINAB222_CMD_UBTUPE                "UBTUPE"
#define NINAB222_CMD_UBTOTK                "UBTOTK"
#define NINAB222_CMD_UBTND                 "UBTND"
#define NINAB222_CMD_UBTI                  "UBTI"
#define NINAB222_CMD_UBTD                  "UBTD"
#define NINAB222_CMD_UBTBD                 "UBTBD"
#define NINAB222_CMD_UBTB                  "UBTB"
#define NINAB222_CMD_UBTUB                 "UBTUB"
#define NINAB222_CMD_UBTLN                 "UBTLN"
#define NINAB222_CMD_UBTLC                 "UBTLC"
#define NINAB222_CMD_UBTMSR                "UBTMSR"
#define NINAB222_CMD_UBTMSP                "UBTMSP"
#define NINAB222_CMD_UBTRSS                "UBTRSS"
#define NINAB222_CMD_UBTLQ                 "UBTLQ"
#define NINAB222_CMD_UBTLE                 "UBTLE"
#define NINAB222_CMD_UBTAD                 "UBTAD"
#define NINAB222_CMD_UBTSS                 "UBTSS"
#define NINAB222_CMD_UBTWS                 "UBTWS"
#define NINAB222_CMD_UBTCFG                "UBTCFG"
#define NINAB222_CMD_UBTLECFG              "UBTLECFG"
#define NINAB222_CMD_UBTDIR                "UBTDIR"
#define NINAB222_CMD_UBTACLC               "UBTACLC"
#define NINAB222_CMD_UBTACLD               "UBTACLD"
#define NINAB222_CMD_UBTLK                 "UBTLK"

/**
 * @brief NINA-B222 parameter access commands.
 * @details Parameter access commands of NINA-B222 Click driver.
 */
#define NINAB222_PREFIX_SYMBOL_END         "\r\n"
#define NINAB222_PREFIX_SYMBOL_QUERY       "?"
#define NINAB222_PREFIX_SYMBOL_SET_VAL     "="
#define NINAB222_PREFIX_SYMBOL_PLUS        "+"
#define NINAB222_PREFIX_SYMBOL_AND         "&"
#define NINAB222_PREFIX_SYMBOL_SEPARATOR   ","
#define NINAB222_PREFIX_SYMBOL_SPACE       " "
#define NINAB222_PREFIX_SYMBOL_PERCENT     "%"
#define NINAB222_PREFIX_SYMBOL_NULL        ""
#define NINAB222_PREFIX_SYMBOL_QUOTE       "\""
#define NINAB222_PREFIX_SYMBOL_SPS         "sps://"
#define NINAB222_PREFIX_SYMBOL_ZERO        "0"
#define NINAB222_PREFIX_SYMBOL_ONE         "1"
#define NINAB222_PREFIX_SYMBOL_TWO         "2"

/**
 * @brief NINA-B222 response value data.
 * @details Predefined enum values for driver response values.
 */
#define NINAB222_RSP_OK                    "OK"
#define NINAB222_RSP_ERROR                 "ERROR"

/**
 * @brief NINA-B222 echo On/Off E data value.
 * @details Echo On/Off E data of NINA-B222 Click driver.
 */
#define NINAB222_ECHO_OFF                  0
#define NINAB222_ECHO_ON                   1

/**
 * @brief NINA-B222 start data mode value.
 * @details Start data mode value of NINA-B222 Click driver.
 */
#define NINAB222_MODE_COMMAND              0
#define NINAB222_MODE_DATA                 1
#define NINAB222_MODE_EXT_DATA             2
#define NINAB222_MODE_PPP                  3

/**
 * @brief NINA-B222 bluetooth low energy role data values.
 * @details Bluetooth low energy role data values of NINA-B222 Click driver.
 */
#define NINAB222_GAP_MODE_NON_PAIRING      0
#define NINAB222_GAP_MODE_PAIRING          1

/**
 * @brief NINA-B222 bluetooth low energy role data values.
 * @details Bluetooth low energy role data values of NINA-B222 Click driver.
 */
#define NINAB222_LR_ROLE_DISABLE           0
#define NINAB222_LR_ROLE_CENTRAL           1
#define NINAB222_LR_ROLE_PERIPHERAL        2
#define NINAB222_LR_ROLE_SIMULTANEOUS      3

/**
 * @brief NINA-B222 connectability mode data values.
 * @details Connectability mode data values of NINA-B222 Click driver.
 */
#define NINAB222_GAP_MODE_NON_CONN         1
#define NINAB222_GAP_MODE_CONN             2

/**
 * @brief NINA-B222 connectability mode data values.
 * @details Connectability mode data values of NINA-B222 Click driver.
 */
#define NINAB222_GAP_MODE_NON_DIS          1
#define NINAB222_GAP_MODE_LIM_DIS          2
#define NINAB222_GAP_MODE_GEN_DISC         3

/**
 * @brief NINA-B222 ASCII zero data values.
 * @details ASCII zero data values of NINA-B222 Click driver.
 */
#define NINAB222_ASCII_TABLE_START_NUM     48

/**
 * @brief NINA-B222 pin logic states data values.
 * @details Pin logic states data values values of NINA-B222 Click driver.
 */
#define NINAB222_PIN_STATE_LOW             0
#define NINAB222_PIN_STATE_HIGH            1

/**
 * @brief NINA-B222 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NINAB222_TX_DRV_BUFFER_SIZE        100
#define NINAB222_RX_DRV_BUFFER_SIZE        300

/*! @} */ // ninab222_cmd

/**
 * @defgroup ninab222_map NINA-B222 MikroBUS Map
 * @brief MikroBUS pin mapping of NINA-B222 Click driver.
 */

/**
 * @addtogroup ninab222_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NINA-B222 Click to the selected MikroBUS.
 */
#define NINAB222_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sry = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS );    \
    cfg.io5 = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ninab222_map
/*! @} */ // ninab222

/**
 * @brief NINA-B222 Click context object.
 * @details Context object definition of NINA-B222 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;    /**< Reset pin. */
    digital_out_t cs;     /**< UART clear to send pin. */
    digital_out_t io5;    /**< General purpose pin. */
    digital_out_t sry;     /**< Signal data ready pin. */

    // Input pins
    digital_in_t rts;     /**< UART request to send. */

    // Modules
    uart_t uart;          /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NINAB222_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ NINAB222_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} ninab222_t;

/**
 * @brief NINA-B222 Click configuration object.
 * @details Configuration object definition of NINA-B222 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t sry;    /**< Signal data ready pin. */
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t cs;     /**< UART clear to send pin. */
    pin_name_t io5;    /**< General purpose pin. */
    pin_name_t rts;    /**< UART request to send. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} ninab222_cfg_t;

/**
 * @brief NINA-B222 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NINAB222_OK = 0,
    NINAB222_ERROR = -1

} ninab222_return_value_t;

/*!
 * @addtogroup ninab222 NINA-B222 Click Driver
 * @brief API for configuring and manipulating NINA-B222 Click driver.
 * @{
 */

/**
 * @brief NINA-B222 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ninab222_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ninab222_cfg_setup ( ninab222_cfg_t *cfg );

/**
 * @brief NINA-B222 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ninab222_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_init ( ninab222_t *ctx, ninab222_cfg_t *cfg );

/**
 * @brief NINA-B222 data writing function.
 * @details This function writes a desired number of data bytes by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_generic_write ( ninab222_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NINA-B222 data reading function.
 * @details This function reads a desired number of data bytes by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_generic_read ( ninab222_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NINA-B222 HW reset function.
 * @details This function performs a hardware reset of the device.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ninab222_hw_reset ( ninab222_t *ctx );

/**
 * @brief NINA-B222 command writing function.
 * @details This function writes a desired command by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_write_cmd ( ninab222_t *ctx, uint8_t *command );

/**
 * @brief NINA-B222 system command writing function.
 * @details This function writes a desired system command by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] command : System command buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_write_sys_cmd ( ninab222_t *ctx, uint8_t *command );

/**
 * @brief NINA-B222 command - parameter writing function.
 * @details This function writes a desired command
 * and parameter by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] command : System command buffer for sending.
 * @param[in] param : Parameter buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_write_cmd_param ( ninab222_t *ctx, uint8_t *command, uint8_t *param );

/**
 * @brief NINA-B222 inquire command function.
 * @details This function writes a desired inquire command 
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] command : System command buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_inquire_cmd ( ninab222_t *ctx, uint8_t *command );

/**
 * @brief NINA-B222 set to factory defined configuration function.
 * @details This function sets to factory defined configuration
 * and performs module switches by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_rst_def_cfg ( ninab222_t *ctx );

/**
 * @brief NINA-B222 reboot DCE function.
 * @details This function reboot DCE and store current configuration
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_reboot_dce ( ninab222_t *ctx );

/**
 * @brief NINA-B222 store current configuration function.
 * @details This function sets the local address of the Bluetooth interface
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_bt_intf ( ninab222_t *ctx );

/**
 * @brief NINA-B222 sets start mode function.
 * @details This function sets the start mode for the module
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] start_mode : Start mode [0-3].
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_start_mode ( ninab222_t *ctx, uint8_t start_mode );

/**
 * @brief NINA-B222 get start mode function.
 * @details This function writes a desired inquiry command 
 * to get the start mode for the module by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_get_start_mode ( ninab222_t *ctx );

/**
 * @brief NINA-B222 sets enter mode function.
 * @details This function requests the module to move to the new mode
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] enter_mode : Enter mode [0-3].
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_enter_mode ( ninab222_t *ctx, uint8_t enter_mode );

/**
 * @brief NINA-B222 set echo function.
 * @details This function configures whether or not the unit echoes 
 * the characters received from the DTE in Command Mode
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] echo_en : Echo On/Off [0-1].
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_echo ( ninab222_t *ctx, uint8_t echo_en );

/**
 * @brief NINA-B222 sets device name function.
 * @details This function sets the local name used as device name for Bluetooth Classic
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] device_name : Device name.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_device_name ( ninab222_t *ctx, uint8_t *device_name );

/**
 * @brief NINA-B222 get device name function.
 * @details This function writes a desired inquiry command 
 * to reads the local name used as device name for Bluetooth Classic
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_get_device_name ( ninab222_t *ctx );

/**
 * @brief NINA-B222 sets low energy role function.
 * @details This function sets the Bluetooth low energy role
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] le_role : Bluetooth low energy role [0-3].
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_le_role ( ninab222_t *ctx, uint8_t le_role );

/**
 * @brief NINA-B222 get low energy role function.
 * @details This function writes a desired inquiry command 
 * to reads the Bluetooth low energy role
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_get_le_role ( ninab222_t *ctx );

/**
 * @brief NINA-B222 get low energy role function.
 * @details This function writes a desired inquiry command 
 * to reads the connected peers and lists them with connection type and peer handle
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_get_peers_list ( ninab222_t *ctx );

/**
 * @brief NINA-B222 sets the default configuration function.
 * @details This function resets the profile to the last stored configuration
 * and reboot the DCE by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] le_role : Bluetooth low energy role [0-3].
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_default_cfg ( ninab222_t *ctx );

/**
 * @brief NINA-B222 sets pairing mode function.
 * @details This function enable or disable pairing mode
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] p_mode : Enable or disable pairing.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_pairing_mode ( ninab222_t *ctx, uint8_t p_mode );

/**
 * @brief NINA-B222 sets connectabilit mode function.
 * @details This function sets the GAP connectability mode
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] c_mode : GAP connectability mode [0-1].
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_connectability ( ninab222_t *ctx, uint8_t c_mode );

/**
 * @brief NINA-B222 sets connectabilit mode function.
 * @details This function writes a desired inquiry command 
 * to reads the GAP connectability mode by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_get_connectability ( ninab222_t *ctx );

/**
 * @brief NINA-B222 sets discoverability mode function.
 * @details This function sets the GAP discoverability mode
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] d_mode : GAP discoverability mode [0-1].
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_set_discoverability ( ninab222_t *ctx, uint8_t d_mode );

/**
 * @brief NINA-B222 sets discoverability mode function.
 * @details This function writes a desired inquiry command 
 * to reads the GAP discoverability mode by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_get_discoverability ( ninab222_t *ctx );

/**
 * @brief NINA-B222 get module-info function.
 * @details This function writes a desired inquiry commands 
 * to read the module information by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note @li @c Manufacturer identification,
 *       @li @c Model identification,
 *       @li @c Software version identification,
 *       @li @c Serial number,
 *       @li @c RS232 Baud Rate Settings,
 */
err_t ninab222_get_info ( ninab222_t *ctx );

/**
 * @brief NINA-B222 default remote peer function.
 * @details This function remote peer when entering either 
 * the Data mode or Extended data mode
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] domain : Specifies Bluetooth address of the remote device.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_remote_peer ( ninab222_t *ctx, uint8_t *domain );

/**
 * @brief NINA-B222 default remote peer function.
 * @details This function sets the Bluetooth low energy role, 
 * sets the data mode for the module and reboot DCE
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab222_periph_pairing_cfg ( ninab222_t *ctx );

/**
 * @brief NINA-B222 set clear to send pin state function.
 * @details This function sets a desired logic state of the CTS (CS) pin.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] cts : Pin logic state.
 * @note None.
 */
void ninab222_clear_to_send ( ninab222_t *ctx, uint8_t cts );

/**
 * @brief NINA-B222 get request to send pin state function.
 * @details This function return logic state of the RTS (INT) pin.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return Logic state of the CTS pin.
 * @note None.
 */
uint8_t ninab222_request_to_send ( ninab222_t *ctx );

/**
 * @brief NINA-B222 set SRY pin state function.
 * @details This function sets a desired logic state of the SRY (AN) pin.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] cts : Pin logic state.
 * @note None.
 */
void ninab222_set_sry_pin ( ninab222_t *ctx, uint8_t state );

/**
 * @brief NINA-B222 set IO5 pin state function.
 * @details This function sets a desired logic state of the IO5 (PWM) pin.
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @param[in] cts : Pin logic state.
 * @note None.
 */
void ninab222_set_io5_pin ( ninab222_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // NINAB222_H

/*! @} */ // ninab222

// ------------------------------------------------------------------------ END
