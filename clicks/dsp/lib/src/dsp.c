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
 * @file dsp.c
 * @brief DSP Click Driver.
 */

#include "dsp.h"


// ------------------------------------------------------------- PRIVATE MACROS 

#define DSP_MASK_BIT_0    0x01
#define DSP_MASK_BIT_1    0x02
#define DSP_MASK_BIT_2    0x04
#define DSP_MASK_BIT_3    0x08


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dsp_cfg_setup ( dsp_cfg_t *cfg ) {
    cfg->p0   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->p1   = HAL_PIN_NC;
    cfg->p3 = HAL_PIN_NC;
    cfg->p2 = HAL_PIN_NC;
}

err_t dsp_init ( dsp_t *ctx, dsp_cfg_t *cfg ) {
    err_t return_flag = 0;

    return_flag |=  digital_out_init( &ctx->p0, cfg->p0 );
    return_flag |=  digital_out_init( &ctx->rst, cfg->rst );
    return_flag |=  digital_out_init( &ctx->p1, cfg->p1 );
    return_flag |=  digital_out_init( &ctx->p3, cfg->p3 );
    return_flag |=  digital_out_init( &ctx->p2, cfg->p2 );

    return return_flag;
}

void dsp_default_cfg ( dsp_t *ctx ) {
    // Click default configuration.
    dsp_power_on( ctx );
    
    // Click default configuration.
    dsp_reset( ctx );
}

void dsp_pin_set_p0 ( dsp_t *ctx, uint8_t pin_state ) {
   
    digital_out_write( &ctx->p0, pin_state );
}

void dsp_pin_set_p1 ( dsp_t *ctx, uint8_t pin_state ) {
   
    digital_out_write( &ctx->p1, pin_state );
}

void dsp_pin_set_p2 ( dsp_t *ctx, uint8_t pin_state ) {
   
    digital_out_write( &ctx->p2, pin_state );
}

void dsp_pin_set_p3 ( dsp_t *ctx, uint8_t pin_state ) {
   
    digital_out_write( &ctx->p3, pin_state );
}

void dsp_power_on ( dsp_t *ctx ) {
    digital_out_high( &ctx->rst );
}

void dsp_reset ( dsp_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}


dsp_retval_t dsp_set_effect ( dsp_t *ctx, uint8_t effects ) {  
    
    dsp_retval_t retval_flag = DSP_OK;
    
    if ( effects > DSP_SET_EFFECT_DELAY1 ) {
        retval_flag = DSP_ERROR;
    } else {
        if ( effects & DSP_MASK_BIT_0 ) {
            digital_out_high( &ctx->p0 );    
        } else {
            digital_out_low( &ctx->p0 );     
        }
    
        if ( effects & DSP_MASK_BIT_1 ) {
            digital_out_low( &ctx->p1 );      
        } else {
            digital_out_low( &ctx->p1 );
        }
    
        if ( effects & DSP_MASK_BIT_2 ) {
            digital_out_high( &ctx->p2 );        
        } else {
            digital_out_low( &ctx->p2 );     
        }
    
        if ( effects & DSP_MASK_BIT_3 ) {
            digital_out_high( &ctx->p3 );        
        } else {
            digital_out_low( &ctx->p3 );     
        }
    }
    
    return retval_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_100ms( );
}


// ------------------------------------------------------------------------- END
