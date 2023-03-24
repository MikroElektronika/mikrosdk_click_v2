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
 * @file dcmotor17.c
 * @brief DC Motor 17 Click Driver.
 */

#include "dcmotor17.h"

void dcmotor17_cfg_setup ( dcmotor17_cfg_t *cfg ) {
    cfg->i1a   = HAL_PIN_NC;
    cfg->i2a = HAL_PIN_NC;
    cfg->stby   = HAL_PIN_NC;
    cfg->i1b = HAL_PIN_NC;
    cfg->i2b = HAL_PIN_NC;
}

err_t dcmotor17_init ( dcmotor17_t *ctx, dcmotor17_cfg_t *cfg ) {
    err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->i1a, cfg->i1a );
    return_flag |= digital_out_init( &ctx->i2a, cfg->i2a );
    return_flag |= digital_out_init( &ctx->stby, cfg->stby );
    return_flag |= digital_out_init( &ctx->i1b, cfg->i1b );
    return_flag |= digital_out_init( &ctx->i2b, cfg->i2b );

    return return_flag;
}

void dcmotor17_default_cfg ( dcmotor17_t *ctx ) {
    // Stop the motor.
    dcmotor17_stop( ctx, DCMOTOR17_SEL_OUT_A );
    dcmotor17_stop( ctx, DCMOTOR17_SEL_OUT_B );
    
    // Set to normal operating mode.
    dcmotor17_set_mode( ctx, DCMOTOR17_SEL_MODE_NORMAL );
}

void dcmotor17_standby_mode ( dcmotor17_t *ctx ) {
    digital_out_low( &ctx->stby );
}

void dcmotor17_normal_mode ( dcmotor17_t *ctx ) {
    digital_out_high( &ctx->stby );
}

dcmotor17_retval_t dcmotor17_set_mode ( dcmotor17_t *ctx, uint8_t op_mode ) {
    dcmotor17_retval_t retval_flag = DCMOTOR17_ERROR;
    
    if ( ( op_mode == DCMOTOR17_SEL_MODE_STANDBY ) ) {
        dcmotor17_standby_mode( ctx );
        retval_flag = DCMOTOR17_OK;
    }
    else if ( op_mode == DCMOTOR17_SEL_MODE_NORMAL ) {
        dcmotor17_normal_mode( ctx );
        retval_flag = DCMOTOR17_OK;    
    } 
            
    return retval_flag;
}

dcmotor17_retval_t dcmotor17_stop ( dcmotor17_t *ctx, uint8_t sel_out ) {
    dcmotor17_retval_t retval_flag = DCMOTOR17_ERROR;
    
    if ( sel_out == DCMOTOR17_SEL_OUT_A ) {
        digital_out_low( &ctx->i1a );
        digital_out_low( &ctx->i1b );
        retval_flag = DCMOTOR17_OK;
    }
    else if ( sel_out == DCMOTOR17_SEL_OUT_B ) {
        digital_out_low( &ctx->i2a );
        digital_out_low( &ctx->i2b );
        retval_flag = DCMOTOR17_OK;
    }
    
    return retval_flag;
}

dcmotor17_retval_t dcmotor17_forward ( dcmotor17_t *ctx, uint8_t sel_out ) {   
    dcmotor17_retval_t retval_flag = DCMOTOR17_ERROR;
    
    if ( sel_out == DCMOTOR17_SEL_OUT_A ) {
        digital_out_high( &ctx->i1a );
        digital_out_high( &ctx->i1b );
        retval_flag = DCMOTOR17_OK;
    }
    else if ( sel_out == DCMOTOR17_SEL_OUT_B ) {
        digital_out_high( &ctx->i2a );
        digital_out_high( &ctx->i2b );
        retval_flag = DCMOTOR17_OK;
    }
    
    return retval_flag;
}

dcmotor17_retval_t dcmotor17_reverse ( dcmotor17_t *ctx, uint8_t sel_out ) { 
    dcmotor17_retval_t retval_flag = DCMOTOR17_ERROR;
    
    if ( sel_out == DCMOTOR17_SEL_OUT_A ) {
        digital_out_low( &ctx->i1a );
        digital_out_high( &ctx->i1b );
        retval_flag = DCMOTOR17_OK;
    }
    else if ( sel_out == DCMOTOR17_SEL_OUT_B ) {
        digital_out_low( &ctx->i2a );
        digital_out_high( &ctx->i2b );
        retval_flag = DCMOTOR17_OK;
    }
    
    return retval_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
