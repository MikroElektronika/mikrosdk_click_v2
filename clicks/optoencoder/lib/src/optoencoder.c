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

#include "optoencoder.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void optoencoder_cfg_setup ( optoencoder_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->o1 = HAL_PIN_NC;
    cfg->o2 = HAL_PIN_NC;
}

OPTOENCODER_RETVAL optoencoder_init ( optoencoder_t *ctx, optoencoder_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->o1, cfg->o1 );
    digital_in_init( &ctx->o2, cfg->o2 );

    return OPTOENCODER_OK;
}

uint8_t optoencoder_get_o1 ( optoencoder_t *ctx )
{
    return digital_in_read( &ctx->o1 );
}

uint8_t optoencoder_get_o2 ( optoencoder_t *ctx )
{
    return digital_in_read( &ctx->o2 );
}

void optoencoder_init_dev ( optoencoder_t *ctx )
{
    ctx->o1_flag = optoencoder_get_o1( ctx );
    ctx->o2_flag = optoencoder_get_o2( ctx );
    
    if ( ctx->o1_flag == 1 && ctx->o2_flag == 1 )  // 2
    {
        ctx->rotary_flag = 2;
    }
    else if ( ctx->o1_flag == 0 && ctx->o2_flag == 1 ) // 1
    {
        ctx->rotary_flag = 1;
    }
    else if ( ctx->o1_flag == 1 && ctx->o2_flag == 0 ) // 3
    {
        ctx->rotary_flag = 3;
    }
    else if ( ctx->o1_flag == 0 && ctx->o2_flag == 0 ) // 0
    {
        ctx->rotary_flag = 0;
    }
    ctx->dev_rotation = 0;
}

int16_t optoencoder_get_position ( optoencoder_t *ctx )
{
      int8_t steps = 0;
      
      ctx->o1_flag = optoencoder_get_o1( ctx );
      ctx->o2_flag = optoencoder_get_o2( ctx );
      
      if ( ctx->o1_flag == 1 && ctx->o2_flag == 1 )  // 2
      {
          if ( ctx->rotary_flag == 1 )
          {
              ctx->dev_rotation = ctx->dev_rotation + 90;
          }
          else if ( ctx->rotary_flag == 3 )
          {
              ctx->dev_rotation = ctx->dev_rotation - 90;
          }
          else
          {
              ctx->dev_rotation =  ctx->dev_rotation;
          }
          
          ctx->rotary_flag = 2;
      }
      else if ( ctx->o1_flag == 0 && ctx->o2_flag == 1 ) // 1
      {
          if ( ctx->rotary_flag == 0 )
          {
              ctx->dev_rotation = ctx->dev_rotation + 90;
          }
          else if ( ctx->rotary_flag == 2 )
          {
              ctx->dev_rotation = ctx->dev_rotation - 90;
          }
          else
          {
              ctx->dev_rotation =  ctx->dev_rotation;
          }

          ctx->rotary_flag = 1;
      }
      else if ( ctx->o1_flag == 1 && ctx->o2_flag == 0 ) // 3
      {
          if ( ctx->rotary_flag == 2 )
          {
              ctx->dev_rotation = ctx->dev_rotation + 90;              
          }
          else if ( ctx->rotary_flag == 0 )
          {
              ctx->dev_rotation = ctx->dev_rotation - 90;
          }
          else
          {
              ctx->dev_rotation =  ctx->dev_rotation;
          }
              
          ctx->rotary_flag = 3;
      }
      else if ( ctx->o1_flag == 0 && ctx->o2_flag == 0 ) // 0
      {
          if ( ctx->rotary_flag == 3 )
          {
              ctx->dev_rotation = ctx->dev_rotation + 90;
          }
          else if ( ctx->rotary_flag == 1 )
          {
              ctx->dev_rotation = ctx->dev_rotation - 90;
          }
          else
          {
              ctx->dev_rotation =  ctx->dev_rotation;
          }

          ctx->rotary_flag = 0;
      }

      if ( ctx->dev_rotation == 0 )
      {
          return 0;
      }

      steps = ctx->dev_rotation / 360;
      return  steps;
}

// ------------------------------------------------------------------------- END

