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

#include "microwave2.h"

// ------------------------------------------------------------------ VARIABLES

static uint8_t comming_dev[6] = {'@','C',13,10,0};
static uint8_t going_dev[6] = {'@','L',13,10,0};
static uint8_t nomovement_dev[6] = {'@','N',13,10,0};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t dev_strcmp ( uint8_t *str1, uint8_t *str2 );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void microwave2_cfg_setup ( microwave2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->da   = HAL_PIN_NC;
    cfg->dl = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

MICROWAVE2_RETVAL microwave2_init ( microwave2_t *ctx, microwave2_cfg_t *cfg )
{
    uart_config_t uart_cfg;

    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Input pins

    digital_in_init( &ctx->da, cfg->da );
    digital_in_init( &ctx->dl, cfg->dl );

    ctx->internal_sync = 0;
    ctx->array_counter = 0;
    ctx->address_holder = 0;

    return MICROWAVE2_OK;
}

void microwave2_generic_multi_write ( microwave2_t *ctx, char *data_buf,  uint8_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

void microwave2_generic_multi_read ( microwave2_t *ctx, char *data_buf,  uint8_t len )
{
    uart_read( &ctx->uart, data_buf, len ); 
}

char microwave2_generic_single_read ( microwave2_t *ctx )
{
    uint8_t rx_data;

    uart_read( &ctx->uart, rx_data, 1 ); 
    
    return rx_data;
}

void microwave2_generic_single_write ( microwave2_t *ctx, char tx_data )
{
    uart_write( &ctx->uart, tx_data, 1 );
}

uint8_t microwave2_da_state( microwave2_t *ctx )
{
    return digital_in_read( &ctx->da );
}

uint8_t microwave2_dl_state( microwave2_t *ctx )
{
    return digital_in_read( &ctx->dl );
}

uint8_t microwave2_check_trafic ( microwave2_t *ctx )
{
    uint8_t *dev_s1;
    uint8_t *dev_s2;
    uint8_t tmp;

    if ( dev_s1 );
    if ( dev_s2 );
    
    if ( ctx->internal_sync == 1 )
    {
        ctx->internal_sync = 0;
        dev_s1 = ctx->address_holder;
        dev_s2 = &going_dev[ 0 ]; //test if comming

        tmp = dev_strcmp( dev_s1, dev_s2 );
        if ( tmp == 0 )
        {
            return MICROWAVE2_MOVING_AWAY;
        }

        dev_s1 = ctx->address_holder;
        dev_s2 = &comming_dev[0]; //test if going
        tmp = dev_strcmp(dev_s1, dev_s2);
        if ( tmp == 0 )
        {
            return MICROWAVE2_MOVING_CLOSER;
        }
       
        dev_s1 = ctx->address_holder;
        dev_s2 = &nomovement_dev[0]; //test if no monvement
        tmp = dev_strcmp( dev_s1, dev_s2);
        if ( tmp == 0 )
        {
            return MICROWAVE2_STOPPED_MOVING;
        }
    }
    return 0;
}

void microwave2_uart_handler ( microwave2_t *ctx, uint8_t *packeg_buffer, uint8_t r_data )
{
    ctx->address_holder = packeg_buffer;
   
    packeg_buffer[ctx->array_counter] = r_data;
    microwave2_generic_single_write( ctx, r_data ); 

    ctx->array_counter++;
    if ( packeg_buffer[ 0 ] != '@' )
    {
        ctx->array_counter = 0;
    }
    if ( ctx->array_counter == 4 )
    {
      ctx->array_counter = 0;
      ctx->internal_sync = 1;
    }

}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t dev_strcmp ( uint8_t *str1, uint8_t *str2 )
{
    while ( *str1 == *str2 )
    {
      if ( *str1 == '\0' ) 
      {
          return *str1 - *str2;
      }
      str1++;
      str2++;
    }

    return 1;
}

// ------------------------------------------------------------------------- END

