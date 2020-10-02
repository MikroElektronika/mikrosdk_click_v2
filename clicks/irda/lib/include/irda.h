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
 * \file irda.h
 *
 * \brief This file contains API for IrDA Click driver.
 *
 * \addtogroup irda IrDA Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _IRDA_H_
#define _IRDA_H_

#include "drv_digital_out.h"
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
#define IRDA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX  ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX  ); \
    cfg.mod    = MIKROBUS( mikrobus, MIKROBUS_AN  ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en     = MIKROBUS( mikrobus, MIKROBUS_CS  )
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Click error code definition.
 */
typedef enum
{
    IRDA_OK = 0x0,
    IRDA_ERR_INIT_DRV = 0xFF

} irda_err_t;

/**
 * @brief Click mode settings.
 */
typedef enum
{
    IRDA_MODE_CMD = 0,
    IRDA_MODE_DATA

} irda_mode_t;

/**
 * @brief Click power mode settings.
 */
typedef enum
{
    IRDA_PWR_OFF = 0,
    IRDA_PWR_ON

} irda_pwr_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    //  Control pins.
    digital_out_t  mod;
    digital_out_t  rst;
    digital_out_t  en;

    //  Module.
    uart_t  uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} irda_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication gpio pins.
    pin_name_t  tx_pin;
    pin_name_t  rx_pin;

    //  Additional gpio pins.
    pin_name_t  mod;
    pin_name_t  rst;
    pin_name_t  en;

    //  Configuration variables.
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} irda_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state.
 */
void
irda_cfg_setup( irda_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0 - Ok,
 *          0xFF - Driver init error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 */
irda_err_t
irda_init( irda_t *ctx, irda_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for IrDA click.
 */
void
irda_default_cfg( irda_t *ctx );

/**
 * @brief Mode Setup function.
 *
 * @param ctx  Click object.
 * @param state  0 - Command mode,
 *               1 - Data mode.
 *
 * @description This function allows IrDA click mode to be set.
 */
void
irda_mode_setup( irda_t *ctx, irda_mode_t state );

/**
 * @brief Power Setup function.
 *
 * @param ctx  Click object.
 * @param state  0 - Power off,
 *               1 - Power on.
 *
 * @description This function allows IrDA click power mode to be set.
 */
void
irda_pwr_setup( irda_t *ctx, irda_pwr_t state );

/**
 * @brief Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a device reset operation.
 *
 * @note After the reset operation was done, the device will be returned back
 *       to normal mode.
 */
void
irda_reset( irda_t *ctx );

/**
 * @brief Generic Multiple Send function.
 *
 * @param ctx  Click object.
 * @param tx_data  Data to be sent.
 *
 * @description This function allows data sending operation of multiple data
 *              bytes to be performed.
 */
void
irda_generic_multiple_send( irda_t *ctx, char *tx_data );

/**
 * @brief Generic Multiple Receive function.
 *
 * @param ctx  Click object.
 * @param rx_data  Memory where read data be stored.
 * @param termination_char  Termination character.
 *
 * @description This function allows data receiving operation of multiple data
 *              bytes to be performed.
 * @note The function will receive data bytes from the device until termination
 *       character was received. At the end of the received data buffer, this
 *       function will add '\0' character.
 */
void
irda_generic_multiple_receive( irda_t *ctx, char *rx_data,
                               char termination_char );

/**
 * @brief Generic Single Send function.
 *
 * @param ctx  Click object.
 * @param tx_data  Data to be sent.
 *
 * @description This function allows data sending operation of single data byte
 *              to be performed.
 */
void
irda_generic_single_send( irda_t *ctx, char tx_data );

/**
 * @brief Generic Single Receive function.
 *
 * @param ctx  Click object.
 *
 * @returns Received data byte.
 *
 * @description This function allows data receiving operation of single data
 *              byte to be performed.
 */
char
irda_generic_single_receive( irda_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _IRDA_H_

/** \} */ //  End public_function group
/// \}    //  End irda group
/*! @} */
// ------------------------------------------------------------------------ END
