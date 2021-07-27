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
 * @file  swi.h
 * @brief API for SWI master driver.
 */

#ifndef SWI_
#define SWI_

#include "stdint.h"

/**
 * @brief SWI driver return values data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SWI_RET_VAL_OK      = 0,
    SWI_RET_VAL_ERROR   = -1
}swi_return_value_t;

/**
 * @brief SWI driver acknowledgement values.
 * @details Predefined enum values for driver acknowledgement values.
 */
typedef enum
{
    SWI_ACK             = 0,
    SWI_NACK            = 1
}swi_acknowledgement_t;

/**
 * @brief SWI driver logic values.
 * @details Predefined enum values for driver logic values.
 */
typedef enum
{
    SWI_LOGIC_0         = 0,
    SWI_LOGIC_1         = 1
}swi_logic_lvl_t;

/**
 * @brief Initializes SWI communication.
 * @details Initializes GPIO for data and SWI 
 * driver, restarts device, discovers device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note This function needs to be
 * called before other driver functions.
 */
int8_t swi_init ( void );

/**
 * @brief Resets device and checks devices response.
 * @details Resets device and sends discovery signal.
 * @return @li @c  0 - Device found,
 *         @li @c -1 - No device.
 */
int8_t swi_reset ( void );

/**
 * @brief Send start SWI signal.
 * @details Sends to device signal for 
 * starting communication.
 * @return Nothing
 */
void swi_start ( void );

/**
 * @brief Send stop SWI signal.
 * @details Sends to device signal for 
 * stoping communication.
 * @return Nothing
 */
void swi_stop ( void );

/**
 * @brief Send logic signal to device.
 * @details Sends logic 0 or 1 relative 
 * to parameter @b logic_level.
 * @param[in] logic_level : @li @c  0 - SWI_LOGIC_0,
 *                          @li @c  1 - SWI_LOGIC_1.
 * @return Nothing
 */
void swi_logic_write ( swi_logic_lvl_t logic_level );

/**
 * @brief Receive logic signal from device.
 * @details Sends signal for response and 
 * returns logic level.
 * @return @li @c  0 - SWI_LOGIC_0,
 *         @li @c  1 - SWI_LOGIC_1.
 */
uint8_t swi_logic_read ( void );

/**
 * @brief Send byte to device.
 * @details Sends desired byte to device 
 * and check response.
 * @param[in] byte_to_send : Byte that will be sent.
 * @return @li @c  0 - SWI_ACK,
 *         @li @c  1 - SWI_NACK.
 */
uint8_t swi_send_byte ( uint8_t byte_to_send );

/**
 * @brief Receive byte from device.
 * @details Sample byte receive from device.
 * @param[out] byte_to_receive : Byte that 
 * received data will be stored in.
 * @param[in] ack_nack : @li @c  0 - SWI_ACK,
 *                       @li @c  1 - SWI_NACK.
 * @return Nothing
 */
void swi_receive_byte ( uint8_t *byte_to_receive, swi_acknowledgement_t ack_nack );

#endif


// ------------------------------------------------------------------------ END
