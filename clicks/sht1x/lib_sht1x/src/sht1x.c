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

#include "sht1x.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void sht1x_cfg_setup ( sht1x_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC; 
}

SHT1X_RETVAL sht1x_init ( sht1x_t *ctx, sht1x_cfg_t *cfg )
{
    // Output pins 

   digital_out_init( &ctx->scl, cfg->scl );
   digital_out_init( &ctx->sda, cfg->sda );
   
    return SHT1X_OK;
}

void sht1x_output_sda ( sht1x_t *ctx, sht1x_cfg_t *cfg )
{
    digital_out_init( &ctx->sda, cfg->sda );
}

void sht1x_input_sda ( sht1x_t *ctx, sht1x_cfg_t *cfg )
{
    digital_in_init( &ctx->sda, cfg->sda );
}

void sht1x_sda_high ( sht1x_t *ctx )
{
    digital_out_high( &ctx->sda );
}

void sht1x_sda_low ( sht1x_t *ctx )
{
    digital_out_low( &ctx->sda );
}

uint8_t sht1x_get_sda ( sht1x_t *ctx )
{
    return digital_in_read( &ctx->sda );
}

void sht1x_scl_high ( sht1x_t *ctx )
{
    digital_out_high( &ctx->scl );
}

void sht1x_scl_low ( sht1x_t *ctx )
{
    digital_out_low( &ctx->scl );
}

float sht1x_calc_temp ( sht1x_t *ctx, uint16_t t )
{
  float temp_out;
  temp_out =  t*0.01 - 40;

  return temp_out;
}

float sht1x_calc_humi ( sht1x_t *ctx, uint16_t h, uint16_t t )
{
  float rh_lin;
  float rh_true;
  float temp_cel;

  temp_cel =  sht1x_calc_temp( ctx, t );
  rh_lin = SHT1X_V3_C3h * h * h + SHT1X_V3_C2h * h + SHT1X_V3_C1;
  rh_true = ( temp_cel - 25 ) * ( SHT1X_T1 + SHT1X_T2h * h ) + rh_lin;

    if( rh_true > 100 )
    {
        rh_true = 100;
    }
    if( rh_true < 0.1 )
    {
        rh_true = 0.1;
    }

    return rh_true;
}

// ------------------------------------------------------------------------- END

