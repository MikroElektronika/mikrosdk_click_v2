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
 * @file speaker.c
 * @brief Speaker Click Driver.
 */

#include "speaker.h"

void speaker_cfg_setup ( speaker_cfg_t *cfg ) {
    cfg->pwr = HAL_PIN_NC;
    cfg->sb  = HAL_PIN_NC;
}

err_t speaker_init ( speaker_t *ctx, speaker_cfg_t *cfg ) {

    err_t return_flag = digital_out_init( &ctx->pwr, cfg->pwr );
    return_flag |= digital_out_init( &ctx->sb, cfg->sb );

    return return_flag;
}

err_t speaker_default_cfg ( speaker_t *ctx ) {
    // Click default configuration.
    speaker_shutdown( ctx );
    
    speaker_enable_slave_amp( ctx );
    
    return SPEAKER_OK;
}

err_t speaker_enable_slave_amp ( speaker_t *ctx ) {
    digital_out_low( &ctx->sb );
    
    return SPEAKER_OK;
}

err_t speaker_disable_slave_amp ( speaker_t *ctx ) {
    digital_out_high( &ctx->sb );
    
    return SPEAKER_OK;
}

err_t speaker_shutdown ( speaker_t *ctx ) {
    digital_out_low( &ctx->pwr );
    
    return SPEAKER_OK;
}

err_t speaker_normal_operation ( speaker_t *ctx ) {
    digital_out_high( &ctx->pwr );
    
    return SPEAKER_OK;
}


// ------------------------------------------------------------------------- END
