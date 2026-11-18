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
 * @file wifi10_wpa.h
 * @brief Internal WPA2 key derivation for WiFi 10 Click.
 */

#ifndef WIFI10_WPA_H
#define WIFI10_WPA_H

#include <stdint.h>

/**
 * @brief WiFi 10 WPA2 key derivation function.
 * @details Derives a 32-byte pairwise master key with PBKDF2-HMAC-SHA1 and 4096 iterations.
 * @param[in] ssid : SSID used as the salt.
 * @param[in] ssid_length : Number of SSID bytes, from 1 to 32.
 * @param[in] password : WPA2 passphrase in printable ASCII.
 * @param[in] password_length : Number of passphrase bytes, from 8 to 63.
 * @param[out] pmk : Output buffer with room for the 32-byte key.
 * @return Nothing.
 * @note The caller validates lengths and the passphrase before calling this function.
 */
void wifi10_derive_pmk ( char *ssid, uint8_t ssid_length, char *password, uint8_t password_length, uint8_t *pmk );

#endif // WIFI10_WPA_H
