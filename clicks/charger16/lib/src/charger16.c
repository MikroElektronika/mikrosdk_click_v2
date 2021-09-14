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
 * @file charger16.c
 * @brief Charger 16 Click Driver.
 */

#include "charger16.h"

void charger16_cfg_setup ( charger16_cfg_t *cfg ) 
{
    cfg->en   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
}

err_t charger16_init ( charger16_t *ctx, charger16_cfg_t *cfg ) 
{
   err_t return_flag = 0;

   return_flag |= digital_out_init( &ctx->en, cfg->en );
   return_flag |= digital_out_init( &ctx->pwm, cfg->pwm );

    return return_flag;
}

err_t charger16_default_cfg ( charger16_t *ctx ) 
{
    err_t err_flag = charger16_enable_charging( ctx );
    
    return err_flag;
}

err_t charger16_enable_charging ( charger16_t *ctx ) 
{
    digital_out_high( &ctx->en );
    digital_out_high( &ctx->pwm );
    
    return CHARGER16_OK;
}

err_t charger16_disable_charging ( charger16_t *ctx ) 
{
    digital_out_low( &ctx->en );
    digital_out_low( &ctx->pwm );
    
    return CHARGER16_OK;
}


// ------------------------------------------------------------------------- END
