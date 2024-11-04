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
 * @file digiisolator.h
 * @brief This file contains API for DIGI Isolator Click Driver.
 */

#ifndef DIGIISOLATOR_H
#define DIGIISOLATOR_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_uart.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup digiisolator DIGI Isolator Click Driver
 * @brief API for configuring and manipulating DIGI Isolator Click driver.
 * @{
 */

/**
 * @defgroup digiisolator_set DIGI Isolator Registers Settings
 * @brief Settings for registers of DIGI Isolator Click driver.
 */

/**
 * @addtogroup digiisolator_set
 * @{
 */

/**
 * @brief DIGI Isolator ADC setting.
 * @details Specified settings for ADC of DIGI Isolator Click driver.
 */
#define DIGIISOLATOR_VREF_3V3                  3.3
#define DIGIISOLATOR_VREF_5V                   5.0

/**
 * @brief DIGI Isolator driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DIGIISOLATOR_TX_DRV_BUFFER_SIZE        100
#define DIGIISOLATOR_RX_DRV_BUFFER_SIZE        300

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b digiisolator_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DIGIISOLATOR_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define DIGIISOLATOR_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // digiisolator_set

/**
 * @defgroup digiisolator_map DIGI Isolator MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI Isolator Click driver.
 */

/**
 * @addtogroup digiisolator_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI Isolator Click to the selected MikroBUS.
 */
#define DIGIISOLATOR_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO );  \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI );  \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );   \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );    \
    cfg.d1 = MIKROBUS( mikrobus, MIKROBUS_AN );      \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.d2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // digiisolator_map
/*! @} */ // digiisolator

/**
 * @brief DIGI Isolator Click context object.
 * @details Context object definition of DIGI Isolator Click driver.
 */
typedef struct
{
    // Input pins
    analog_in_t adc;     /**< ADC module object. */
    digital_in_t d2;     /**< D2 pin. */

    // Modules
    spi_master_t spi;    /**< SPI driver object. */
    uart_t uart;         /**< UART driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    // Buffers
    char uart_rx_buffer[ DIGIISOLATOR_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ DIGIISOLATOR_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} digiisolator_t;

/**
 * @brief DIGI Isolator Click configuration object.
 * @details Configuration object definition of DIGI Isolator Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rx_pin;     /**< RX pin. */
    pin_name_t tx_pin;     /**< TX pin. */

    // Additional gpio pins
    pin_name_t d1;    /**< D1 pin. */
    pin_name_t d2;    /**< D2 pin. */

    // Static variable
    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */
    uint32_t         baud_rate;                       /**< Clock speed. */
    bool             uart_blocking;                   /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                        /**< Data bits. */
    uart_parity_t    parity_bit;                      /**< Parity bit. */
    uart_stop_bits_t stop_bit;                        /**< Stop bits. */
    
    analog_in_resolution_t resolution;    /**< ADC resolution. */
    float                  vref;          /**< ADC reference voltage. */

} digiisolator_cfg_t;

/**
 * @brief DIGI Isolator Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIISOLATOR_OK = 0,
    DIGIISOLATOR_ERROR = -1

} digiisolator_return_value_t;

/*!
 * @addtogroup digiisolator DIGI Isolator Click Driver
 * @brief API for configuring and manipulating DIGI Isolator Click driver.
 * @{
 */

/**
 * @brief DIGI Isolator configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digiisolator_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digiisolator_cfg_setup ( digiisolator_cfg_t *cfg );

/**
 * @brief DIGI Isolator initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digiisolator_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator_init ( digiisolator_t *ctx, digiisolator_cfg_t *cfg );

/**
 * @brief DIGI Isolator SPI data writing function.
 * @details This function writes a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator_spi_write ( digiisolator_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief DIGI Isolator SPI data reading function.
 * @details This function reads a desired number of data bytes
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator_spi_read ( digiisolator_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief DIGI Isolator SPI write then read function.
 * @details This function writes and then reads a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len_in : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len_out : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator_spi_write_read ( digiisolator_t *ctx, uint8_t *data_in, uint8_t len_in, uint8_t *data_out, uint8_t len_out );

/**
 * @brief DIGI Isolator SPI transfer function.
 * @details This function writes and reads a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be transferred (written/read).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator_spi_transfer ( digiisolator_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len );

/**
 * @brief DIGI Isolator UART data writing function.
 * @details This function writes a desired number of data bytes 
 * by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c >=0 - Success,
 *         @li @c  <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator_uart_write ( digiisolator_t *ctx, char *data_in, uint16_t len );

/**
 * @brief DIGI Isolator UART data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator_uart_read ( digiisolator_t *ctx, char *data_out, uint16_t len );

/**
 * @brief DIGI Isolator read D1 pin value function.
 * @details This function reads results of AD conversion of the D1 pin.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digiisolator_get_d1_pin_value ( digiisolator_t *ctx, uint16_t *data_out );

/**
 * @brief DIGI Isolator read D1 pin voltage level function.
 * @details This function reads results of AD conversion of the D1 pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t digiisolator_get_d1_pin_voltage ( digiisolator_t *ctx, float *data_out );

/**
 * @brief DIGI Isolator get D2 function.
 * @details This function get states of the D2 ( INT ) pin.
 * @param[in] ctx : Click context object.
 * See #digiisolator_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t digiisolator_get_d2 ( digiisolator_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIISOLATOR_H

/*! @} */ // digiisolator

// ------------------------------------------------------------------------ END
