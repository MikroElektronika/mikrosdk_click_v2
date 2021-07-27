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
 * @file  gpio.h
 * @brief API for Digital GPIO control.
 */

#ifndef GPIO_
#define GPIO_

#include "stdint.h"

/**
 * @brief GPIO initialization.
 * @details This function initializes data pin.
 * @return Nothing
 * @note This function needs to be
 * called before other driver functions.
 */
void pin_init( void );

/**
 * @brief Drive data pin low
 * @details This function sets data pin to low.
 * @return Nothing
 */
void pin_low ( void );

/**
 * @brief Drive data pin high
 * @details This function sets data pin to high.
 * @return Nothing
 */
void pin_high ( void );

/**
 * @brief Release data pin
 * @details This function releases data pin to floating.
 * @return Nothing
 */
void pin_release ( void );

/**
 * @brief Input data pin
 * @details This function gets state of data pin.
 * @return State of data pin.
 */
uint8_t pin_get ( void );

#endif


// ------------------------------------------------------------------------ END
