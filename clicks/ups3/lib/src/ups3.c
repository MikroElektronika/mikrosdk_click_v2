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
 * @file ups3.c
 * @brief UPS 3 Click Driver.
 */

#include "ups3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Reset delay.
 * @details Reset delay for 100 milliseconds.
 */
static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ups3_cfg_setup ( ups3_cfg_t *cfg ) {
    cfg->err   = HAL_PIN_NC;
    cfg->cok = HAL_PIN_NC;
    cfg->dir   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t ups3_init ( ups3_t *ctx, ups3_cfg_t *cfg ) {
    err_t return_flag = 0;

    return_flag |=  digital_out_init( &ctx->dir, cfg->dir );
    return_flag |=  digital_out_init( &ctx->en, cfg->en );

    return_flag |=  digital_in_init( &ctx->err, cfg->err );
    return_flag |=  digital_in_init( &ctx->cok, cfg->cok );
    return_flag |=  digital_in_init( &ctx->int_pin, cfg->int_pin );

    return return_flag;
}

err_t ups3_default_cfg ( ups3_t *ctx ) {
    return ups3_set_enable( ctx, UPS3_ENABLE_NORMAL_OPERATION );
}

uint8_t ups3_get_error ( ups3_t *ctx ) {
    return digital_in_read( &ctx->err );
}

uint8_t ups3_get_cap_ok ( ups3_t *ctx ) {
    return digital_in_read( &ctx->cok );
}

uint8_t ups3_get_chrg ( ups3_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

err_t ups3_select_dir_mode ( ups3_t *ctx, uint8_t dir_mode ) {
    err_t status;
    status = UPS3_SUCCESS;
    
    if ( dir_mode == UPS3_DIR_MODE_BACKUP ) {
        digital_out_low( &ctx->dir );    
    } else if ( dir_mode == UPS3_DIR_MODE_CHARGE ) {
        digital_out_high( &ctx->dir );    
    } else {
        status = UPS3_ERROR;    
    } 
    
    return status;
}

err_t ups3_set_enable ( ups3_t *ctx, uint8_t enable ) {
    err_t status;
    status = UPS3_SUCCESS;
    
    if ( enable == UPS3_ENABLE_SHUTDOWN ) {
        digital_out_low( &ctx->en );    
    } else if ( enable == UPS3_ENABLE_NORMAL_OPERATION ) {
        digital_out_high( &ctx->en );    
    } else {
        status = UPS3_ERROR;    
    } 
    
    return status;
}

err_t ups3_hw_reset ( ups3_t *ctx ) {
    err_t status;
    status = UPS3_SUCCESS;
    
    status |= ups3_set_enable( ctx, UPS3_ENABLE_SHUTDOWN );
    dev_reset_delay( );
    status |= ups3_set_enable( ctx, UPS3_ENABLE_NORMAL_OPERATION );
    dev_reset_delay( );
    
    return status;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_100ms( );   
}

// ------------------------------------------------------------------------- END
