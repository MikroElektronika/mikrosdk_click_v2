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
 * @file ata6571.h
 * @brief This file contains API for ATA6571 Click Driver.
 */

#ifndef ATA6571_H
#define ATA6571_H

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
 * @addtogroup ata6571 ATA6571 Click Driver
 * @brief API for configuring and manipulating ATA6571 Click driver.
 * @{
 */

/**
 * @defgroup ata6571_set ATA6571 Device Settings
 * @brief Settings for ATA6571 Click driver.
 */

/**
 * @addtogroup ata6571_set
 * @{
 */

/**
 * @brief ATA6571 operating mode selection.
 * @details Operating mode selection of ATA6571 Click driver.
 */
#define ATA6571_OPERATING_MODE_SLEEP          0x00
#define ATA6571_OPERATING_MODE_STANDBY        0x01
#define ATA6571_OPERATING_MODE_SILENT         0x02
#define ATA6571_OPERATING_MODE_NORMAL         0x03

/**
 * @brief ATA6571 pin state flags.
 * @details Pin state flags of ATA6571 Click driver.
 */
#define ATA6571_PIN_STATE_LOW                 0x00
#define ATA6571_PIN_STATE_HIGH                0x01

/**
 * @brief ATA6571 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // ata6571_set

/**
 * @defgroup ata6571_map ATA6571 MikroBUS Map
 * @brief MikroBUS pin mapping of ATA6571 Click driver.
 */

/**
 * @addtogroup ata6571_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ATA6571 Click to the selected MikroBUS.
 */
#define ATA6571_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.nstb = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.nerr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // ata6571_map
/*! @} */ // ata6571

/**
 * @brief ATA6571 Click context object.
 * @details Context object definition of ATA6571 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t nstb;                      /**< Standby Mode Control. */
    digital_out_t en;                        /**< Enable Control. */

    // Input pins
    digital_in_t nerr;                       /**< Error Indication. */
    
    // Modules
    uart_t uart;                             /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */

} ata6571_t;

/**
 * @brief ATA6571 Click configuration object.
 * @details Configuration object definition of ATA6571 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t nstb;                    /**< Standby Mode Control. */
    pin_name_t nerr;                    /**< Error Indication. */
    pin_name_t en;                      /**< Enable Control. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} ata6571_cfg_t;

/**
 * @brief ATA6571 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ATA6571_OK = 0,
    ATA6571_ERROR = -1

} ata6571_return_value_t;

/*!
 * @addtogroup ata6571 ATA6571 Click Driver
 * @brief API for configuring and manipulating ATA6571 Click driver.
 * @{
 */

/**
 * @brief ATA6571 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ata6571_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ata6571_cfg_setup ( ata6571_cfg_t *cfg );

/**
 * @brief ATA6571 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ata6571_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ata6571_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ata6571_init ( ata6571_t *ctx, ata6571_cfg_t *cfg );

/**
 * @brief ATA6571 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ata6571_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ata6571_generic_write ( ata6571_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief ATA6571 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ata6571_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ata6571_generic_read ( ata6571_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief ATA6571 set standby mode control function.
 * @details This function sets standby mode by setting the NSTB pin.
 * @param[in] ctx : Click context object.
 * See #ata6571_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ata6571_set_nstb_pin ( ata6571_t *ctx, uint8_t state );

/**
 * @brief ATA6571 set power control function.
 * @details This function sets power control by setting the EN pin.
 * @param[in] ctx : Click context object.
 * See #ata6571_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ata6571_set_en_pin ( ata6571_t *ctx, uint8_t state );

/**
 * @brief ATA6571 get error and power-on indication output function.
 * @details This function returns the NERR pin state which is an error and power-on indicator.
 * @param[in] ctx : Click context object.
 * See #ata6571_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ata6571_get_nerr_pin ( ata6571_t *ctx );

/**
 * @brief ATA6571 set operating mode function.
 * @details This function sets the device operating mode by controlling the EN and NSTB pins.
 * @param[in] ctx : Click context object.
 * See #ata6571_t object definition for detailed explanation.
 * @param[in] op_mode - 0x00 ( ATA6571_OPERATING_MODE_SLEEP )  : Sleep mode.
 *                    - 0x01 ( ATA6571_OPERATING_MODE_STANDBY ): Standby mode.
 *                    - 0x00 ( ATA6571_OPERATING_MODE_SILENT ) : Silent mode.
 *                    - 0x01 ( ATA6571_OPERATING_MODE_NORMAL ) : Normal mode.
 * @return None.
 * @note None.
 */
void ata6571_set_operating_mode ( ata6571_t *ctx, uint8_t op_mode );

#ifdef __cplusplus
}
#endif
#endif // ATA6571_H

/*! @} */ // ata6571

// ------------------------------------------------------------------------ END
