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
 * \file
 *
 * \brief This file contains API for DMX Click driver.
 *
 * \addtogroup dmx DMX Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DMX_H
#define DMX_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define DMX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.abr = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.run = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DMX_OK                  0
#define DMX_ERROR              -1
#define DMX_ERROR_TIMEOUT      -2
/** \} */

/**
 * \defgroup dmx_cmd_response DMX command response
 * \{
 */
#define DMX_RSP_OK              "OK"
#define DMX_RSP_ERROR           "ERR"
/** \} */

/**
 * \defgroup dmx_commands DMX commands
 * \{
 */
#define DMX_CMD_SADR            "@SADR,001\0"
#define DMX_CMD_BLEN            "@BLEN,006\0"
#define DMX_CMD_ITMR            "@ITMR,001\0"
#define DMX_CMD_FTMR            "@FTMR,001\0"
#define DMX_CMD_FLEN_MASTER     "@FLEN,010\0"
#define DMX_CMD_FLEN_SLAVE      "@FLEN,006\0"
#define DMX_CMD_SCOD            "@SCOD,000\0"
#define DMX_CMD_PURGEBFR        "!PURGEBFR\0"
#define DMX_CMD_STORECFG        "!STORECFG\0"
#define DMX_CMD_CLEARCFG        "!CLEARCFG\0"
#define DMX_CMD_DISPLCFG        "!DISPLCFG\0"
/** \} */

/**
 * \defgroup dmx_settings DMX settings
 * \{
 */
#define DMX_SLAVE               0
#define DMX_MASTER              1
#define DMX_CONFIG_MODE         0
#define DMX_RUN_MODE            1
#define DMX_INT_INACTIVE        0
#define DMX_INT_ACTIVE          1
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DMX_DRV_RX_BUFFER_SIZE  300
#define DMX_DRV_TX_BUFFER_SIZE  100
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 
    digital_out_t rst;
    digital_out_t abr;
    digital_out_t run;

    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    uart_t uart;

    uint8_t uart_rx_buffer[ DMX_DRV_RX_BUFFER_SIZE ];
    uint8_t uart_tx_buffer[ DMX_DRV_TX_BUFFER_SIZE ];

} dmx_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 
    pin_name_t rst;
    pin_name_t abr;
    pin_name_t run;
    pin_name_t int_pin;

    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} dmx_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void dmx_cfg_setup ( dmx_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t dmx_init ( dmx_t *ctx, dmx_cfg_t *cfg );

/**
 * @brief Reset function.
 * @param ctx Click object.
 */
void dmx_reset ( dmx_t *ctx, uint8_t dev_mode );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void dmx_generic_write ( dmx_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
err_t dmx_generic_read ( dmx_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Send command function.
 * @param ctx Click object.
 * @param cmd Command to be sent.
 */
void dmx_send_cmd ( dmx_t* ctx, uint8_t *cmd );

/**
 * @brief Mode Setting function
 * @param ctx Click object.
 * @param run_mode 0 - config mode, 1 - run mode
 * @details This function allows user to put device in config or run mode.
 * @note Config mode must be set when user wants to execute device configuration.
 *       When run mode is set, the data transfer is started.
 */
void dmx_run ( dmx_t *ctx, uint8_t run_mode );

/**
 * @brief Interrupt Check function
 * @param ctx Click object.
 * @returns 0 - inactive state, 1 - active state
 *
 * @details This function checks the interrupt state.
 */
uint8_t dmx_check_int ( dmx_t *ctx );

/**
 * @brief Reset Setting function
 * @param ctx Click object.
 * @param state RST pin state.
 * 
 * @details This function sets reset pin state.
 */
void dmx_set_reset ( dmx_t *ctx, uint8_t state );

/**
 * @brief Auto Baud Rate Setting function
 * @param ctx Click object.
 * @param state ABR pin state.
 * 
 * @details This function sets auto (default) baud rate.
 * @note The default baud rate is 115200 bps.
 */
void dmx_set_auto_baud_rate ( dmx_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _DMX_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
