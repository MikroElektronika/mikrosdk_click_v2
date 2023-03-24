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

#include "magneto4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MAGNETO4_DUMMY 0

#define MAGNETO4_NO_MOVEMENT               0x00
#define MAGNETO4_RTOL_DIRECTION            0x01
#define MAGNETO4_LTOR_DIRECTION            0x02
   
#define MAGNETO4_RISING_EDGE               0x00
#define MAGNETO4_FALLING_EDGE              0x01

#define MAGNETO4_PIN_STATE_LOW             0x00
#define MAGNETO4_PIN_STATE_HIGH            0x01

#define MAGNETO4_START_STATE_PIN_A         0x00
#define MAGNETO4_START_STATE_PIN_B         0x00

#define MAGNETO_FIRST_BIT_12               0x0FFF
#define MAGNETO_STATUS_BIT_FIELD           0x0000003E

#define MAGNETO_STATUS_BIT_1               0x02
#define MAGNETO_STATUS_BIT_2               0x04
#define MAGNETO_STATUS_BIT_3               0x08
#define MAGNETO_STATUS_BIT_4               0x10
#define MAGNETO_STATUS_BIT_5               0x20

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void magneto4_cfg_setup ( magneto4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

     cfg->a = HAL_PIN_NC;
     cfg->b = HAL_PIN_NC;
     cfg->pwm = HAL_PIN_NC;
     cfg->ind = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MAGNETO4_RETVAL magneto4_init ( magneto4_t *ctx, magneto4_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MAGNETO4_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return MAGNETO4_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MAGNETO4_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // Input pins

    digital_in_init( &ctx->a,  cfg->a  );
    digital_in_init( &ctx->b, cfg->b );
    digital_in_init( &ctx->pwm, cfg->pwm );
    digital_in_init( &ctx->ind, cfg->ind );

    return MAGNETO4_OK;
}

void magneto4_default_cfg ( magneto4_t *ctx )
{
    // Click default configuration
    
    magneto4_set_start_position( ctx, MAGNETO4_ENCODER_TO_ZERO_POSITION );
    
    // First read of magnetic field strength
    
    magneto4_start_measurement( ctx );
}

void magneto4_generic_transfer 
( 
    magneto4_t *ctx,
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

uint8_t magneto4_get_out_a ( magneto4_t *ctx )
{
    return digital_in_read( &ctx->a );
}

uint8_t magneto4_get_out_b ( magneto4_t *ctx )
{
    return digital_in_read( &ctx->b );
}

uint8_t magneto4_get_index ( magneto4_t *ctx )
{
    return digital_in_read( &ctx->ind );
}

uint32_t magneto4_start_measurement ( magneto4_t *ctx )
{
    uint8_t rx_buf[ 3 ];
    uint32_t res_val = 0;

    magneto4_generic_transfer( ctx, rx_buf, 3 );
    
    res_val = rx_buf[ 0 ];
    res_val <<= 8;
    res_val |= rx_buf[ 1 ];
    res_val <<= 8;
    res_val |= rx_buf[ 2 ];
    
    return res_val;
}

uint16_t magneto4_get_magnetic_field ( magneto4_t *ctx )
{
    uint16_t magnetic_data;
    uint32_t raw_data = 0;
    
    raw_data = magneto4_start_measurement( ctx );
    
    magnetic_data = ( uint16_t ) ( raw_data >> 6 );
    magnetic_data &= MAGNETO_FIRST_BIT_12;
    
    return magnetic_data;
}

uint8_t magneto4_get_magnetic_status ( magneto4_t *ctx, mag_status_t *mag_status )
{
    uint16_t error_code;
    uint32_t raw_value;

    raw_value = magneto4_start_measurement( ctx );
    
    raw_value &= MAGNETO_STATUS_BIT_FIELD;
    error_code = ( uint8_t ) raw_value; 

    mag_status->dec_val  = error_code & MAGNETO_STATUS_BIT_1;
    mag_status->inc_val  = error_code & MAGNETO_STATUS_BIT_2;
    mag_status->lin_val  = error_code & MAGNETO_STATUS_BIT_3;
    mag_status->cof_val  = error_code & MAGNETO_STATUS_BIT_4;
    mag_status->ocf_val  = error_code & MAGNETO_STATUS_BIT_5;
  
    return error_code;
}

uint8_t magneto4_get_encoder_direction ( magneto4_t *ctx )
{
    // Detected change on ENCA
    
    if (  ctx->state_a != magneto4_get_out_a( ctx ) )
    {
        // Take new value and set edge depends on new value
        
        if ( ( ctx->state_a = magneto4_get_out_a( ctx ) ) == 1 )
        {
            ctx->a_edge = MAGNETO4_RISING_EDGE;    
        }
        else
        {
            ctx->a_edge = MAGNETO4_FALLING_EDGE;
        }

        // Decide movement depends last encoder edges
        
        switch ( ctx->a_edge )
        {
            case MAGNETO4_RISING_EDGE:
            {
                if ( ctx->b_edge == MAGNETO4_RISING_EDGE )
                {
                    return MAGNETO4_RTOL_DIRECTION;    
                }
                else
                {
                    return MAGNETO4_LTOR_DIRECTION;    
                }
                
                break;
            }
            case MAGNETO4_FALLING_EDGE:
            {
                if ( ctx->b_edge == MAGNETO4_RISING_EDGE )
                {
                    return MAGNETO4_LTOR_DIRECTION;    
                }
                else
                {
                    return MAGNETO4_RTOL_DIRECTION;    
                }
                
                break;
            }
            default :
            {
                // Unknown state, might be first movement detected or too fast rotation
                
                return MAGNETO4_NO_MOVEMENT;
                break;
            }
        }
    }
    
    // Detected change on ENCB
    
    if (  ctx->state_b != magneto4_get_out_b( ctx ) )
    {
        // Take new value and set edge depends on new value
        
        if ( ( ctx->state_b = magneto4_get_out_b( ctx ) ) == 1 )
        {
            ctx->b_edge = MAGNETO4_RISING_EDGE;    
        }
        else
        {
            ctx->b_edge = MAGNETO4_FALLING_EDGE;   
        }

        // Decide movement depends last encoder edges
        
        switch ( ctx->b_edge )
        {
            case MAGNETO4_RISING_EDGE:
            {
                if ( ctx->a_edge == MAGNETO4_RISING_EDGE )
                {
                    return MAGNETO4_LTOR_DIRECTION;    
                }
                else
                {
                    return MAGNETO4_RTOL_DIRECTION;    
                }
                
                break;
            }
            case MAGNETO4_FALLING_EDGE:
            {
                if ( ctx->a_edge == MAGNETO4_RISING_EDGE )
                {
                    return MAGNETO4_RTOL_DIRECTION;    
                }
                else
                {
                    return MAGNETO4_LTOR_DIRECTION;    
                }
                
                break;
            }
            default :
            {
                // Unknown state, might be first movement detected or too fast rotation
                
                return MAGNETO4_NO_MOVEMENT;
                break;
            }
        }
    }
    
    return MAGNETO4_NO_MOVEMENT;
}

void magneto4_get_encoder_position ( magneto4_t *ctx )
{
    uint8_t encoder_dir;
    uint8_t index;
     
    encoder_dir = magneto4_get_encoder_direction( ctx );
    
    index = magneto4_get_index( ctx );
     
    if ( ( index == MAGNETO4_PIN_STATE_HIGH ) && ( encoder_dir != MAGNETO4_NO_MOVEMENT ) )
    {
        if ( encoder_dir == MAGNETO4_RTOL_DIRECTION )
        {
            ctx->encoder_position--;
        }
        else if ( encoder_dir == MAGNETO4_LTOR_DIRECTION )
        {
            ctx->encoder_position++;
        }
    }
}

void magneto4_set_start_position ( magneto4_t *ctx, int32_t encoder_pos )
{
    ctx->encoder_position = encoder_pos;
    ctx->state_a = MAGNETO4_START_STATE_PIN_A;
    ctx->state_b = MAGNETO4_START_STATE_PIN_B;
}


// ------------------------------------------------------------------------- END

