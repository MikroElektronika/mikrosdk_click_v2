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
 * @file rfal_platform.h
 * @brief RFAL platform configuration for NFC 9 Click and mikroSDK.
 */

#ifndef RFAL_PLATFORM_H
#define RFAL_PLATFORM_H

#include "nfc9_rfal.h"

/**
 * @brief NFC 9 RFAL feature configuration.
 * @details NFC 9 Click example supports NFC-A polling only. Other RFAL
 * technologies and optional modes are disabled.
 */
#define RFAL_FEATURE_LISTEN_MODE                 false
#define RFAL_FEATURE_WAKEUP_MODE                 false
#define RFAL_FEATURE_LOWPOWER_MODE               false
#define RFAL_FEATURE_NFCA                        true
#define RFAL_FEATURE_NFCB                        false
#define RFAL_FEATURE_NFCF                        false
#define RFAL_FEATURE_NFCV                        false
#define RFAL_FEATURE_NFC_DEP                     false
#define RFAL_FEATURE_ISO_DEP                     false
#define RFAL_FEATURE_ISO_DEP_POLL                false
#define RFAL_FEATURE_ISO_DEP_LISTEN              false
#define RFAL_FEATURE_T1T                         false
#define RFAL_FEATURE_T2T                         false
#define RFAL_FEATURE_T4T                         false
#define RFAL_FEATURE_ST25TB                      false
#define RFAL_FEATURE_ST25xV                      false
#define RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG       false
#define RFAL_FEATURE_DPO                         false
#define RFAL_FEATURE_DPO_CR                      false
#define RFAL_FEATURE_DLMA                        false

/**
 * @brief NFC 9 RFAL SPI platform mapping.
 * @details Maps RFAL SPI operations to the NFC 9 Click mikroSDK bridge.
 */
#define platformSpiSelect()                      nfc9_rfal_spi_select()
#define platformSpiDeselect()                    nfc9_rfal_spi_deselect()
#define platformSpiTxRx( txBuf, rxBuf, len )     nfc9_rfal_spi_tx_rx( (const uint8_t *)(txBuf), (uint8_t *)(rxBuf), (uint16_t)(len) )

/**
 * @brief NFC 9 RFAL timer platform mapping.
 * @details Maps RFAL delay and timer operations to the NFC 9 Click bridge.
 */
#define platformDelay( ms )                      nfc9_rfal_delay( (uint32_t)(ms) )
#define platformTimerCreate( ms )                nfc9_rfal_timer_create( (uint16_t)(ms) )
#define platformTimerIsExpired( timer )          nfc9_rfal_timer_is_expired( (uint32_t)(timer) )
#define platformTimerGetRemaining( timer )       nfc9_rfal_timer_get_remaining( (uint32_t)(timer) )
#define platformTimerDestroy( timer )            do { (void)(timer); } while (0)
#define platformGetSysTick()                     nfc9_rfal_timer_get_tick()

/**
 * @brief NFC 9 RFAL IRQ platform mapping.
 * @details Maps RFAL GPIO checks to the NFC 9 INT pin.
 */
#define platformGpioIsHigh( port, pin )          nfc9_rfal_irq_is_high()
#define platformGpioIsLow( port, pin )           nfc9_rfal_irq_is_low()
#define ST25R_INT_PORT                           0
#define ST25R_INT_PIN                            0

/**
 * @brief NFC 9 RFAL protection platform mapping.
 * @details Single-threaded example stubs for RFAL critical sections.
 */
#define platformProtectST25RComm()               do { } while (0)
#define platformUnprotectST25RComm()             do { } while (0)
#define platformProtectST25RIrqStatus()          do { } while (0)
#define platformUnprotectST25RIrqStatus()        do { } while (0)
#define platformProtectWorker()                  do { } while (0)
#define platformUnprotectWorker()                do { } while (0)
#define platformIrqST25RPinInitialize()          do { } while (0)
#define platformIrqST25RSetCallback( cb )        do { (void)(cb); } while (0)

/**
 * @brief NFC 9 RFAL optional platform stubs.
 * @details LED, log and assert hooks required by RFAL and unused by this
 * mikroSDK example.
 */
#define platformLedsInitialize()                 do { } while (0)
#define platformLedOff( port, pin )              do { (void)(port); (void)(pin); } while (0)
#define platformLedOn( port, pin )               do { (void)(port); (void)(pin); } while (0)
#define platformLedToggle( port, pin )           do { (void)(port); (void)(pin); } while (0)
#define platformLog(...)                         do { } while (0)
#define platformAssert( exp )                    do { if ( !( exp ) ) { platformErrorHandle(); } } while (0)
#define platformErrorHandle()                    do { } while (0)

#include "rfal_defConfig.h"

#endif // RFAL_PLATFORM_H

// ------------------------------------------------------------------------ END
