/**
 * @file lr1110_modem_driver_version.c
 *
 * @brief Implementation of the get version function
 *
 * Revised BSD License
 * Copyright Semtech Corporation 2020. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "modem/lr1110_modem_driver_version.h"

/*!
 * @brief Helper macro to concatenate string
 */
#define STR_HELPER( x ) #x

/*!
 * @brief Macro to stringify names
 */
#define STR( x ) STR_HELPER( x )

/*!
 * @brief String representation of the driver version
 */
#define LR1110_MODEM_DRIVER_VERSION_FULL                                                               \
    "v" STR( LR1110_MODEM_DRIVER_VERSION_MAJOR ) "." STR( LR1110_MODEM_DRIVER_VERSION_MINOR ) "." STR( \
        LR1110_MODEM_DRIVER_VERSION_PATCH )

/*!
 * @brief Returns version string
 */
char* lr1110_modem_driver_version_get_version_string( void )
{
    return ( char* ) LR1110_MODEM_DRIVER_VERSION_FULL;
}
