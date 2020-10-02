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
 */

#include "nanopower2.h" 

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void nanopower2_cfg_setup ( nanopower2_cfg_t *cfg )
{
    cfg->out = HAL_PIN_NC;
}

NANOPOWER2_RETVAL nanopower2_init ( nanopower2_t *ctx, nanopower2_cfg_t *cfg )
{
    
    digital_in_init( &ctx->out, cfg->out );

    return NANOPOWER2_OK;
}


NANOPOWER2_RETVAL nanopower2_check_output ( nanopower2_t *ctx )
{
	if ( digital_in_read( &ctx->out ) )
		return 1;
	else
		return 0;
}

// ------------------------------------------------------------------------- END

