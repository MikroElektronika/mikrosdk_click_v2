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
 * @file nfc9_rfal.h
 * @brief RFAL platform bridge for NFC 9 Click.
 */

#ifndef NFC9_RFAL_H
#define NFC9_RFAL_H

#ifdef __cplusplus
extern "C"{
#endif

#include "nfc9.h"

/**
 * @brief NFC 9 RFAL context setup function.
 * @details This function sets the NFC 9 Click context used by the RFAL
 * platform bridge.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void nfc9_rfal_set_context ( nfc9_t *ctx );

/**
 * @brief NFC 9 RFAL SPI select function.
 * @details This function selects the ST25R210 SPI device.
 * @return Nothing.
 * @note None.
 */
void nfc9_rfal_spi_select ( void );

/**
 * @brief NFC 9 RFAL SPI deselect function.
 * @details This function deselects the ST25R210 SPI device.
 * @return Nothing.
 * @note None.
 */
void nfc9_rfal_spi_deselect ( void );

/**
 * @brief NFC 9 RFAL SPI transfer function.
 * @details This function performs an RFAL SPI transmit/receive operation.
 * @param[in] tx_buf : Transmit data buffer.
 * @param[out] rx_buf : Receive data buffer.
 * @param[in] len : Number of bytes to transfer.
 * @return Nothing.
 * @note None.
 */
void nfc9_rfal_spi_tx_rx ( const uint8_t *tx_buf, uint8_t *rx_buf, uint16_t len );

/**
 * @brief NFC 9 RFAL delay function.
 * @details This function blocks for the requested number of milliseconds.
 * @param[in] ms : Delay time in milliseconds.
 * @return Nothing.
 * @note None.
 */
void nfc9_rfal_delay ( uint32_t ms );

/**
 * @brief NFC 9 RFAL timer create function.
 * @details This function creates a software timer deadline.
 * @param[in] ms : Timer period in milliseconds.
 * @return Timer deadline tick.
 * @note None.
 */
uint32_t nfc9_rfal_timer_create ( uint16_t ms );

/**
 * @brief NFC 9 RFAL timer expiry check function.
 * @details This function checks whether the selected software timer expired.
 * @param[in] timer : Timer deadline tick.
 * @return @li @c 1 - Timer expired,
 *         @li @c 0 - Timer running.
 * @note None.
 */
uint8_t nfc9_rfal_timer_is_expired ( uint32_t timer );

/**
 * @brief NFC 9 RFAL timer remaining time function.
 * @details This function gets the remaining time for a software timer.
 * @param[in] timer : Timer deadline tick.
 * @return Remaining time in milliseconds.
 * @note None.
 */
uint32_t nfc9_rfal_timer_get_remaining ( uint32_t timer );

/**
 * @brief NFC 9 RFAL tick read function.
 * @details This function gets the current software timer tick.
 * @return Current tick in milliseconds.
 * @note None.
 */
uint32_t nfc9_rfal_timer_get_tick ( void );

/**
 * @brief NFC 9 RFAL IRQ high check function.
 * @details This function checks whether the ST25R210 INT pin is high.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfc9_rfal_irq_is_high ( void );

/**
 * @brief NFC 9 RFAL IRQ low check function.
 * @details This function checks whether the ST25R210 INT pin is low.
 * @return Inverted pin logic state.
 * @note None.
 */
uint8_t nfc9_rfal_irq_is_low ( void );

#ifdef __cplusplus
}
#endif
#endif // NFC9_RFAL_H

// ------------------------------------------------------------------------ END
