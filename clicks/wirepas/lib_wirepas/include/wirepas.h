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
 * @file wirepas.h
 * @brief This file contains API for Wirepas Click Driver.
 */

#ifndef WIREPAS_H
#define WIREPAS_H

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
 * @addtogroup wirepas Wirepas Click Driver
 * @brief API for configuring and manipulating Wirepas Click driver.
 * @{
 */

/**
 * @defgroup wirepas_cmd Wirepas Device Settings
 * @brief Settings for registers of Wirepas Click driver.
 */

/**
 * @addtogroup wirepas_cmd
 * @{
 */

/**
 * @brief Wirepas control commands.
 * @details Specified setting for control commands of Wirepas Click driver.
 */

/**
* @brief Wirepas DSAP attributes primitive ID.
 * @details Specified setting for DSAP attributes primitive ID of Wirepas Click driver.
 */
#define WIREPAS_DSAP_DATA_TX_REQUEST            0x01
#define WIREPAS_DSAP_DATA_TX_CONFIRM            0x81
#define WIREPAS_DSAP_DATA_TX_TT_REQUEST         0x1F
#define WIREPAS_DSAP_DATA_TX_TT_CONFIRM         0x9F
#define WIREPAS_DSAP_DATA_TX_INDICATION         0x02
#define WIREPAS_DSAP_DATA_TX_RESPONSE           0x82
#define WIREPAS_DSAP_DATA_RX_INDICATION         0x03
#define WIREPAS_DSAP_DATA_RX_RESPONSE           0x83

/**
* @brief Wirepas MSAP attributes primitive ID.
 * @details Specified setting for MSAP attributes primitive ID of Wirepas Click driver.
 */
#define WIREPAS_MSAP_INDICATION_POLL_REQUEST    0x04
#define WIREPAS_MSAP_INDICATION_POLL_CONFIRM    0x84
#define WIREPAS_MSAP_STACK_START_REQUEST        0x05
#define WIREPAS_MSAP_STACK_START_CONFIRM        0x85
#define WIREPAS_MSAP_STACK_STOP_REQUEST         0x06
#define WIREPAS_MSAP_STACK_STOP_CONFIRM         0x86
#define WIREPAS_MSAP_STACK_STATE_INDICATION     0x07
#define WIREPAS_MSAP_STACK_STATE_RESPONSE       0x87
#define WIREPAS_MSAP_APP_CONFIG_DATA_RX_IND     0x3F
#define WIREPAS_MSAP_APP_CONFIG_DATA_RX_RESP    0xBF
#define WIREPAS_MSAP_SCAN_NBORS_INDICATION      0x22
#define WIREPAS_MSAP_SCAN_NBORS_RESPONSE        0xA2

/**
* @brief Wirepas CSAP attributes primitive ID.
 * @details Specified setting for CSAP attributes primitive ID of Wirepas Click driver.
 */
#define WIREPAS_CSAP_ATTRIBUTE_WRITE_REQUEST    0x0D
#define WIREPAS_CSAP_ATTRIBUTE_WRITE_CONFIRM    0x8D
#define WIREPAS_CSAP_ATTRIBUTE_READ_REQUEST     0x0E
#define WIREPAS_CSAP_ATTRIBUTE_READ_CONFIRM     0x8E
#define WIREPAS_CSAP_FACTORY_RESET_REQUEST      0x16
#define WIREPAS_CSAP_FACTORY_RESET_CONFIRM      0x96

/**
 * @brief Wirepas CSAP attributes.
 * @details Specified setting for CSAP attributes of Wirepas Click driver.
 */
#define WIREPAS_CSAP_ATTRIBUTE_NODE_ADDRESS     0x01
#define WIREPAS_CSAP_ATTRIBUTE_NETWORK_ADDRESS  0x02
#define WIREPAS_CSAP_ATTRIBUTE_NETWORK_CHANNEL  0x03
#define WIREPAS_CSAP_ATTRIBUTE_NODE_ROLE        0x04

/**
 * @brief Wirepas factory reset code.
 * @details Factory reset code of Wirepas Click driver.
 */
#define WIREPAS_FACTORY_RESET_CODE              "DoIt"

/**
 * @brief Wirepas factory reset code.
 * @details Factory reset code of Wirepas Click driver.
 */
#define WIREPAS_ENDCODE_OCTET                   0xC0

/**
 * @brief Wirepas node role mode settings.
 * @details Specified setting for node role mode of Wirepas Click driver.
 */
#define WIREPAS_ROUTER_NODE_MODE                0x02    
#define WIREPAS_SINK_NODE_MODE                  0x01    

/**
 * @brief Wirepas pin mode settings.
 * @details Specified setting for pin mode of Wirepas Click driver.
 */
#define WIREPAS_PIN_MODE_HIGH                   0x01    
#define WIREPAS_PIN_MODE_LOW                    0x00    

/**
 * @brief Wirepas driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define WIREPAS_TX_DRV_BUFFER_SIZE              200
#define WIREPAS_RX_DRV_BUFFER_SIZE              500

/*! @} */ // wirepas_cmd

/**
 * @defgroup wirepas_map Wirepas MikroBUS Map
 * @brief MikroBUS pin mapping of Wirepas Click driver.
 */

/**
 * @addtogroup wirepas_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Wirepas Click to the selected MikroBUS.
 */
#define WIREPAS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.din = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // wirepas_map
/*! @} */ // wirepas

/**
 * @brief Wirepas Click frame data object.
 * @details Frame data object definition of Wirepas Click driver.
 */
typedef struct
{
    uint8_t primitive_id;                    
    uint8_t frame_id;                 
    uint8_t payload_len;               
    uint8_t payload[ 256 ];            

} wirepas_frame_t;

/**
 * @brief Wirepas Click context object.
 * @details Context object definition of Wirepas Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;   /**< Reset pin. */

    // Input pins
    digital_in_t din;    /**< Data indication. */

    // Modules
    uart_t uart;         /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ WIREPAS_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ WIREPAS_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    wirepas_frame_t frame;
    uint8_t tx_frame_id;

} wirepas_t;

/**
 * @brief Wirepas Click configuration object.
 * @details Configuration object definition of Wirepas Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin. */
    pin_name_t din;                             /**< Data indication. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} wirepas_cfg_t;

/**
 * @brief Wirepas Click sink data object.
 * @details Sink data object definition of Wirepas Click driver.
 */
typedef struct
{
    uint16_t pduid;                             /** PDU identifier. */
    uint8_t source_endpoint;                    /** Source endpoint number. */
    uint32_t destination_addr;                  /** Destination node address. */
    uint8_t destination_endpoint;               /** Destination node number. */

} wirepas_sink_data;

/**
 * @brief Wirepas Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIREPAS_OK = 0,
    WIREPAS_DATA_RDY = 1,
    WIREPAS_ERROR = -1

} wirepas_return_value_t;

/*!
 * @addtogroup wirepas Wirepas Click Driver
 * @brief API for configuring and manipulating Wirepas Click driver.
 * @{
 */

/**
 * @brief Wirepas configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #wirepas_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void wirepas_cfg_setup ( wirepas_cfg_t *cfg );

/**
 * @brief Wirepas initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wirepas_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_init ( wirepas_t *ctx, wirepas_cfg_t *cfg );

/**
 * @brief Wirepas default configuration function.
 * @details This function executes a default configuration of Wirepas
 * Click board.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void wirepas_default_cfg ( wirepas_t *ctx );

/**
 * @brief Wirepas data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_generic_write ( wirepas_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Wirepas data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_generic_read ( wirepas_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Wirepas get DIN state function.
 * @details This function reads a state of the din pin.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @return State of the DIN pin.
 * @note None.
 */
uint8_t wirepas_get_din_state ( wirepas_t *ctx );

/**
 * @brief Wirepas set RST pin state function.
 * @details This function is used to set RST pin state.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] pin_state : State of the RST pin.
 * @return Nothing.
 * @note None.
 */
void wirepas_set_rst ( wirepas_t *ctx, uint8_t pin_state );

/**
 * @brief Wirepas hardware reset function.
 * @details This function is used to perform a hardware reset.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] pin_state : State of the RST pin.
 * @return Nothing.
 * @note None.
 */
void wirepas_hw_reset ( wirepas_t *ctx );

/**
 * @brief Wirepas send command function.
 * @details This function is used to send command.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] primitive_id : The PDU ID can be used to keep track of APDUs processed.
 * @param[in] payload_length : Payload length in octets, excluding the CRC octets.
 * @param[in] payload : The payload of the frame, depends on the primitive in question.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_send_command ( wirepas_t *ctx, uint8_t primitive_id,  
                             uint8_t payload_length, uint8_t *payload );

/**
 * @brief Wirepas send ack function.
 * @details This function is used to send response to sent data.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] primitive_id : The PDU ID can be used to keep track of APDUs processed.
 * @param[in] frame_id : Message frame id.
 * @param[in] result : Indication result.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_send_ack ( wirepas_t *ctx, uint8_t primitive_id, uint8_t frame_id, uint8_t result );

/**
 * @brief Wirepas write CSAP attribute function.
 * @details This function is used to set specific CSAP attribute.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] attribute_id : The ID of the attribute that is written.
 * @param[in] attribute_len : The length (in octets) of the attribute that is written.
 * @param[in] attribute_val : The value that is written to the attribute specified by the set attribute ID.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_write_csap_attribute ( wirepas_t *ctx, uint16_t attribute_id, 
                                     uint8_t attribute_len, uint8_t *attribute_val );

/**
 * @brief @brief Wirepas read CSAP attribute function.
 * @details This function is used to read value specific CSAP attribute.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] attribute_id : The ID of the attribute that is written.
 * @param[out] attribute_len : The length (in octets) of the attribute that is read.
 * @param[out] attribute_val : The value that is read.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_read_csap_attribute ( wirepas_t *ctx, uint16_t attribute_id, 
                                    uint8_t *attribute_len, uint8_t *attribute_val );

/**
 * @brief @brief Wirepas set node address function.
 * @details This function is used to set node address.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] address : Node address.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_set_node_address ( wirepas_t *ctx, uint32_t address );

/**
 * @brief @brief Wirepas set net address function.
 * @details This function is used to set net address.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] net_address : Net address.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_set_net_address ( wirepas_t *ctx, uint32_t net_address );

/**
 * @brief @brief Wirepas read frame function.
 * @details This function is used to read whole frame of the Wirepas Click data.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[out] frame : Read frame data.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_read_frame ( wirepas_t *ctx, wirepas_frame_t *frame );

/**
 * @brief @brief Wirepas send data function.
 * @details This function is used to send data to the other devices.
 * @param[in] ctx : Click context object.
 * See #wirepas_t object definition for detailed explanation.
 * @param[in] sink_data : Sink data object.
 * @param[in] tx_op : The TX options are indicated as a bit field with individual bits.
 * @param[in] apdu_length : The length of the following APDU in octets.
 * @param[in] apdu : Application payload.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirepas_send_data ( wirepas_t *ctx, wirepas_sink_data sink_data, 
                          uint8_t tx_op, uint8_t apdu_length, uint8_t *apdu );

#ifdef __cplusplus
}
#endif
#endif // WIREPAS_H

/*! @} */ // wirepas

// ------------------------------------------------------------------------ END
