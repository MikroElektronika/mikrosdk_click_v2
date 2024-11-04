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
 * @file lr.h
 * @brief This file contains API for LR Click Driver.
 */

#ifndef LR_H
#define LR_H

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
 * @addtogroup lr LR Click Driver
 * @brief API for configuring and manipulating LR Click driver.
 * @{
 */

/**
 * @defgroup lr_set LR Device Settings
 * @brief Settings for registers of LR Click driver.
 */

/**
 * @addtogroup lr_set
 * @{
 */

/**
 * @brief LR Click Commands.
 * @details Specified Commands of LR Click driver.
 */
#define LR_CMD_SYS_GET_VER          "sys get ver"
#define LR_CMD_MAC_PAUSE            "mac pause"
#define LR_CMD_RADIO_SET_WDT        "radio set wdt 0"
#define LR_ARG_0                    "0"

/**
 * @brief LR Join mode.
 * @details Specified Join mode settings of LR Click driver.
 */
#define LR_JM_OTAA                  "otaa"
#define LR_JM_ABP                   "abp"

/**
 * @brief LR Payload.
 * @details Specified Payload of LR Click driver.
 */
#define LR_PL_CNF                   "cnf "
#define LR_PL_UNCNF                 "uncnf "

/**
 * @brief LR Errors.
 * @details Specified errors values of LR Click driver.
 */
#define LR_INVALID_PARAM            1
#define LR_NOT_JOINED               2
#define LR_NO_FREE_CH               3
#define LR_SILENT                   4
#define LR_ERR_REJOIN_NEEDED        5
#define LR_BUSY                     6
#define LR_MAC_PAUSED               7
#define LR_INVALID_PAR_DATA_LEN     8
#define LR_KEYS_NOT_INIT            9
#define LR_MAC_ERR                  10
#define LR_MAC_RX                   12
#define LR_INVALID_REPAR_DATA_LEN   13
#define LR_RADIO_ERR                14
#define LR_DENIED                   18  

/**
 * @brief LR Command String Max Size.
 * @details Specified command string max Size of LR Click driver.
 */
#define LR_MAX_DATA_SIZE            256
#define LR_MAX_TRANSFER_SIZE        384

#define LR_MAX_CMD_SIZE             64

/**
 * @brief LR Response String Max Size.
 * @details Maximum size of responce string of LR Click driver.
 */
#define LR_MAX_RSP_SIZE             20

/**
 * @brief LR Number of Response Indexes.
 * @details Number of response indexes of LR Click driver.
 */
#define LR_RESP_COUNT               100

/**
 * @brief LR Timer Limit.
 * @details Specified timer limit of LR Click driver in ms.
 */
#define LR_TIMER_EXPIRED            50000

/**
 * @brief LR Variables.
 * @details Specified variables of LR Click driver.
 */
#define LR_MAC_TX                   "mac tx "
#define LR_JOIN                     "mac join "
#define LR_RADIO_TX                 "radio tx "
#define LR_RADIO_RX                 "radio rx "

/**
 * @brief LR driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_RX_BUFFER_SIZE                       300

/*! @} */ // lr_set

/**
 * @defgroup lr_map LR MikroBUS Map
 * @brief MikroBUS pin mapping of LR Click driver.
 */

/**
 * @addtogroup lr_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR Click to the selected MikroBUS.
 */
#define LR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lr_map
/*! @} */ // lr

/**
 * @brief Click buffers object definition.
 * @details Definition of buffer object of LR Click driver.
 */
typedef struct
{
    char     tx_buffer[ LR_MAX_TRANSFER_SIZE ];
    char     rx_buffer[ LR_MAX_TRANSFER_SIZE ];
    uint16_t rx_buffer_len;

} lr_buffers_t;

/**
 * @brief Timer Flags and Counter object definition.
 * @details Definition of timer, flags and counter object of LR Click driver.
 */
typedef struct
{
    bool     timer_f;
    bool     timeout_f;
    bool     timer_use_f;
    uint32_t ticker;
    uint32_t timer_max;
    
} lr_timer_t;

/**
 * @brief  Process Flags object definition.
 * @details Definition of Flags object of LR Click driver.
 */
typedef struct
{
    bool rsp_rdy_f;
    bool lr_rdy_f;
    
} lr_procces_flags_t;

/**
 * @brief Response object definition.
 * @details Definition of Responce object object of LR Click driver.
 */
typedef struct
{
    bool  rsp_f;
    char  *rsp_buffer;
    bool  callback_default;
    void ( *callback_resp )( char *response );
    
} lr_response_t;

/**
 * @brief Mac object definition.
 * @details Definition of Mac object of LR Click driver.
 */
typedef struct
{
    char *payload; 
    char *port_no; 
    char *buffer;
    char *response;
    
} lr_mac_t;

/**
 * @brief LR Click context object.
 * @details Context object definition of LR Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t rts;          /**< UART Ready-To-Send pin. */

    // Input pins
    digital_in_t cts;           /**< UART Clear-To-Send pin. */

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */

    lr_buffers_t buff;
    lr_timer_t tm;
    lr_procces_flags_t flags;
    lr_response_t rsp;
    char data_in;
    
} lr_t;

/**
 * @brief LR Click configuration object.
 * @details Configuration object definition of LR Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin. */
    pin_name_t rts;                     /**< UART Ready-To-Send pin. */
    pin_name_t cts;                     /**< UART Clear-To-Send pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} lr_cfg_t;

/**
 * @brief LR Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LR_OK = 0,
   LR_ERROR = -1

} lr_return_value_t;

/*!
 * @addtogroup lr LR Click Driver
 * @brief API for configuring and manipulating LR Click driver.
 * @{
 */

/**
 * @brief LR configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr_cfg_setup ( lr_cfg_t *cfg );

/**
 * @brief LR initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr_init ( lr_t *ctx, lr_cfg_t *cfg );

/**
 * @brief LR default configuration function.
 * @details This function executes a default configuration of LR
 * Click board.
 * @param[in] ctx : Click context object.
 * See #lr_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void lr_default_cfg ( lr_t *ctx, bool cb_default, void ( *response_p )( char *response ) );

/**
 * @brief LR data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return Nothing.
 * @note None.
 */
void lr_generic_write ( lr_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LR data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * @note None.
 */
int32_t lr_generic_read ( lr_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command function.
 * @details Used by parser to send data inside the software buffer. User can send valid
 *          commands with this function but command string and data should be well formated.
 * @param[in] ctx : Click context object.
 * See #lr_t object definition for detailed explanation.
 * @param[in] comd : Well formated command string.
 * @param[out] response : Response data.
 * @return Nothing.
 * @note None.
 */
void lr_cmd ( lr_t *ctx, char *cmd,  char *response );

/**
 * @brief Function for writing mac parameters
 * @details This function write mac parameters to tx_buffer.
 * @param[in] ctx : Click context object. 
 * See #lr_t object definition for detailed explanation.
 * @param[in] mac : Mac structure object  
 * @return LR flag.
 * @note None.
 */
uint8_t lr_mac_tx ( lr_t *ctx, lr_mac_t *mac );

/**
 * @brief Function for setting join mode
 * @details This function sets join mode.
 * @param[in] ctx : Click context object. 
 * See #lr_t object definition for detailed explanation.
 * @param[in] join_mode : Join mode.
 * @param[out] response : Response.
 * @return LR flag.
 * @note None.
 */
uint8_t lr_join ( lr_t *ctx, char *join_mode, char *response );

/**
 * @brief Main receiver function  
 * @details This function is used for receive message.
 * @param[in] ctx : Click context object. 
 * See #lr_t object definition for detailed explanation.
 * @param[in] window_size : Window size.
 * @param[out] response : Response.
 * @return LR flag.
 * @note None.
 */
uint8_t lr_rx ( lr_t *ctx, char *window_size, char *response );

/**
 * @brief Main tnanceiver function
 * @details This function is used for sending message.
 * @param[in] ctx : Click context object. 
 * See #lr_t object definition for detailed explanation.
 * @param[in] buffer : Buffer to be send.
 * @return LR flag.
 * @note None.
 */
uint8_t lr_tx ( lr_t *ctx, char *buffer );

/**
 * @brief Receiver
 * @details Must be placed inside the user made uart interrupt routine.
 * @param[in] ctx : Click context object. 
 * See #lr_t object definition for detailed explanation.
 * @param[in] rx_input : Data from uart receive register
 * @return Nothing.
 * @note None.
 */
void lr_rx_isr ( lr_t *ctx, char rx_input );

/**
 * @brief Timer
 * @details Used for host timing. Should be placed inside the previously made interrupt
 * routine made by user that occurs on every one milisecond.
 * @param[in] ctx : Click context object. 
 * See #lr_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void lr_tick_isr ( lr_t *ctx );

/**
 * @brief Timer Configuration
 * @details Used to configure host watchdog. When timeout occurs response with no data
 *          will be parsed. If user provide 0 as argument timer will be turned off. By
 *          default after the initialization timer limit is turned on and set to
 * @param[in] ctx : Click context object.
 * See #lr_t object definition for detailed explanation.
 * @param[in] timer_limit : ( 0 ~ 4294967296 )  
 * @return Nothing.
 * 
 * @link TIMER_EXPIRED @endlink
 *
 * @note
 * <pre>  
 * RN2483 have it's own watchdog timer, this one should be longer than watchdog and can be 
 * used to restart the module in case of when library does not receiving responses from the 
 * module.
 * </pre> 
 */
void lr_tick_conf ( lr_t *ctx, uint32_t timer_limit );

/**
 * @brief Main Process
 * @details Function must be placed inside the infinite while loop.
 * @param[in] ctx : Click context object.
 * See #lr_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void lr_isr_process ( lr_t *ctx );

/**
 * @brief Function for write char
 * @details Function write char into ctx objects.
 * @param[in] ctx : Click context object.
 * See #lr_t object definition for detailed explanation.
 * @param[in] data_in : Char to be written 
 * @return Nothing.
 * @note None.
 */
void lr_put_char ( lr_t *ctx, char data_in );

#ifdef __cplusplus
}
#endif
#endif // LR_H

/*! @} */ // lr

// ------------------------------------------------------------------------ END
