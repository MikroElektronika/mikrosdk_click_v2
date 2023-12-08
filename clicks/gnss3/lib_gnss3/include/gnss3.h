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
 * \brief This file contains API for GNSS3 Click driver.
 *
 * \addtogroup gnss3 GNSS3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GNSS3_H
#define GNSS3_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define GNSS3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * @brief GNSS 3 response buffer commands.
 * @details Specified response buffer commands of GNSS 3 Click driver.
 */
#define GNSS3_RSP_START                         "$"
#define GNSS3_RSP_DELIMITER                     ","
#define GNSS3_RSP_GNGGA                         "$GNGGA"

/**
 * @brief GNSS 3 GNGGA command elements.
 * @details Specified GNGGA command elements of GNSS 3 Click driver.
 */
#define GNSS3_GNGGA_ELEMENT_SIZE                15
#define GNSS3_GNGGA_TIME                        1
#define GNSS3_GNGGA_LATITUDE                    2
#define GNSS3_GNGGA_LATITUDE_SIDE               3
#define GNSS3_GNGGA_LONGITUDE                   4
#define GNSS3_GNGGA_LONGITUDE_SIDE              5
#define GNSS3_GNGGA_QUALITY_INDICATOR           6
#define GNSS3_GNGGA_NUMBER_OF_SATELLITES        7
#define GNSS3_GNGGA_H_DILUTION_OF_POS           8
#define GNSS3_GNGGA_ALTITUDE                    9
#define GNSS3_GNGGA_ALTITUDE_UNIT               10
#define GNSS3_GNGGA_GEOIDAL_SEPARATION          11
#define GNSS3_GNGGA_GEOIDAL_SEPARATION_UNIT     12
#define GNSS3_GNGGA_TIME_SINCE_LAST_DGPS        13
#define GNSS3_GNGGA_DGPS_REFERENCE_STATION_ID   14

/**
 * \defgroup driver Driver define
 * \{
 */
#define GNSS3_DRV_RX_BUFFER_SIZE                500
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
    digital_out_t rst;
    digital_in_t int_pin;
    
    uart_t uart;

    char uart_rx_buffer[ GNSS3_DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ GNSS3_DRV_RX_BUFFER_SIZE ];

} gnss3_t;

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
    pin_name_t int_pin;

    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} gnss3_cfg_t;

/**
 * @brief GNSS 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS3_OK = 0,
    GNSS3_ERROR = -1

} gnss3_return_value_t;

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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void gnss3_cfg_setup ( gnss3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gnss3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t gnss3_init ( gnss3_t *ctx, gnss3_cfg_t *cfg );

/**
 * @brief Wake-up module.
 * @param gnss3 Click object.
 */
void gnss3_module_wakeup ( gnss3_t *ctx );

/**
 * @brief Set RST ( reset ) pin state.
 * @param gnss3 Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void gnss3_set_rst_pin ( gnss3_t *ctx, uint8_t state );

/**
 * @brief Get PPS pin state.
 * @param gnss3 Click object.
 * @return current pin state.
 */
uint8_t gnss3_get_int_pin ( gnss3_t *ctx );

/**
 * @brief Generic write function.
 * @param gnss3 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void gnss3_generic_write ( gnss3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param gnss3 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t gnss3_generic_read ( gnss3_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief GNSS 3 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss3_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif  // _GNSS3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
