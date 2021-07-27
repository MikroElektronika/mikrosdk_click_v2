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
 * @file  log.h
 * @brief API for LOG driver.
 */

#ifndef LOG_
#define LOG_

#include "stdint.h"

/**
 * @brief Initializes LOG module.
 * @details Initializes LOG driver.
 * @return Nothing
 * @note This function needs to be
 * called before other driver functions.
 */
void log_init ( void );

/**
 * @brief Prints string to UART terminal with a new line.
 * @details Prints @b txt to UART terminal with CR and LF sent additionally.
 * @param[in] txt : String to send.
 * @return Nothing
 */
void log_line ( char *txt );

/**
 * @brief Prints string to UART terminal.
 * @details Prints @b txt to UART terminal.
 * @param[in] txt : String to send.
 * @return Nothing
 */
void log_txt ( char *txt );

/**
 * @brief Prints byte to UART terminal.
 * @details Prints @b t_char to UART terminal.
 * @param[in] t_char : Byte to send.
 * @return Nothing
 */
void log_byte ( char t_char );

#endif


// ------------------------------------------------------------------------ END
