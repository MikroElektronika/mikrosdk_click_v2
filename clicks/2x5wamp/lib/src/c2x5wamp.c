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

#include "c2x5wamp.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Set Standby mode of the amplifier function
 *
 * @param ctx  Click object.
 * 
 * @description Function set Standby operating mode of the amplifier
 * by clear CS pin of 2x5W Amp Click.
 */ 
void dev_stand_by ( c2x5wamp_t *ctx );

/**
 * @brief Set Mute mode of the amplifier function
 *
 * @param ctx  Click object.
 * 
 * @description Function set Mute operating mode of the amplifier
 * by set CS pin and clear PWM pin of 2x5W Amp Click.
 */
void dev_mute ( c2x5wamp_t *ctx );

/**
 * @brief Set Play mode of the amplifier function
 *
 * @param ctx  Click object.
 * 
 * @description Function set Play operating mode of the amplifier
 * by set CS pin and PWM pin of 2x5W Amp Click.
 */
void dev_play ( c2x5wamp_t *ctx );

/**
 * @brief Set amplifier gain to 20dB function
 *
 * @param ctx  Click object.
 * 
 * @description Function set amplifier gain to 20dB 
 * by clear AN and RST pin of 2x5W Amp Click.
 */
void dev_gain_20dB ( c2x5wamp_t *ctx );

/**
 * @brief Set amplifier gain to 26dB function
 *
 * @param ctx  Click object.
 * 
 * @description Function set amplifier gain to 26dB
 * by clear AN and set RST pin of 2x5W Amp Click.
 */
void dev_gain_26dB ( c2x5wamp_t *ctx );

/**
 * @brief Set amplifier gain to 30dB function
 *
 * @param ctx  Click object.
 * 
 * @description Function set amplifier gain to 30dB
 * by set AN and clear RST pin of 2x5W Amp Click.
 */
void dev_gain_30dB ( c2x5wamp_t *ctx );

/**
 * @brief Set amplifier gain to 32dB function
 *
 * @param ctx  Click object.
 * 
 * @description Function set amplifier gain to 32dB
 * by set AN and RST pin of 2x5W Amp Click.
 */
void dev_gain_32dB ( c2x5wamp_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c2x5wamp_cfg_setup ( c2x5wamp_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->gn0   = HAL_PIN_NC;
    cfg->gn1 = HAL_PIN_NC;
    cfg->stb   = HAL_PIN_NC;
    cfg->mute = HAL_PIN_NC;
    cfg->dia = HAL_PIN_NC;
}

C2X5WAMP_RETVAL c2x5wamp_init ( c2x5wamp_t *ctx, c2x5wamp_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->gn0, cfg->gn0 );
    digital_out_init( &ctx->gn1, cfg->gn1 );
    digital_out_init( &ctx->stb, cfg->stb );
    digital_out_init( &ctx->mute, cfg->mute );

    // Input pins

    digital_in_init( &ctx->dia, cfg->dia );

    return C2X5WAMP_OK;
}

void c2x5wamp_default_cfg ( c2x5wamp_t *ctx )
{
    // Click default configuration
    
    // Set Standby mode
    
    dev_stand_by( ctx );
    
    // Set amplifier gain to 20dB
    
    dev_gain_20dB( ctx );
}

//  Set mode selection of the amplifier function 
uint8_t c2x5wamp_set_mode ( c2x5wamp_t *ctx, uint8_t select_mode )
{
    switch ( select_mode )
    {
        case C2X5WAMP_MODE_STANDBY :
        {
            dev_stand_by( ctx );
            break;
        }
        case C2X5WAMP_MODE_MUTE :
        {
            dev_mute( ctx );
            break;
        }
        case C2X5WAMP_MODE_PLAY :
        {
            dev_play( ctx );
            break;
        }
        default :
        {
            return C2X5WAMP_RESULT_ERROR;
        }
    }

    return C2X5WAMP_RESULT_OK;
}

// Set Gain resistors of the amplifier function
uint8_t c2x5wamp_set_gain ( c2x5wamp_t *ctx, uint8_t select_gain )
{
    switch ( select_gain )
    {
        case C2X5WAMP_GAIN_20DB :
        {
            dev_gain_20dB( ctx );
            break;
        }
        case C2X5WAMP_GAIN_26DB :
        {
            dev_gain_26dB( ctx );
            break;
        }
        case C2X5WAMP_GAIN_30DB :
        {
            dev_gain_30dB( ctx );
            break;
        }
        case C2X5WAMP_GAIN_32DB :
        {
            dev_gain_32dB( ctx );
            break;
        }
        default :
        {
            return C2X5WAMP_RESULT_ERROR;
        }
    }

    return C2X5WAMP_RESULT_OK;
}

// Check input impedance function
uint8_t c2x5wamp_check_input ( c2x5wamp_t *ctx )
{
    return digital_in_read( &ctx->dia );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// Set Standby mode of the amplifier function 
void dev_stand_by ( c2x5wamp_t *ctx )
{
    digital_out_low( &ctx->stb );
}

// Set mute mode of the amplifier function 
void dev_mute ( c2x5wamp_t *ctx )
{
    digital_out_high( &ctx->stb );
    digital_out_low( &ctx->mute );
}

// Set Play mode of the amplifier function 
void dev_play ( c2x5wamp_t *ctx )
{
    digital_out_high( &ctx->stb );
    digital_out_high( &ctx->mute );
}

// Set amplifier gain to 20dB function 
void dev_gain_20dB ( c2x5wamp_t *ctx )
{
    digital_out_low( &ctx->gn0 );
    digital_out_low( &ctx->gn1 );
}

// Set amplifier gain to 26dB function 
void dev_gain_26dB ( c2x5wamp_t *ctx )
{
    digital_out_low( &ctx->gn0 );
    digital_out_high( &ctx->gn1 );
}

// Set amplifier gain to 30dB function 
void dev_gain_30dB ( c2x5wamp_t *ctx )
{
    digital_out_high( &ctx->gn0 );
    digital_out_low( &ctx->gn1 );
}

// Set amplifier gain to 32dB function
void dev_gain_32dB ( c2x5wamp_t *ctx )
{
    digital_out_high( &ctx->gn0 );
    digital_out_high( &ctx->gn1 );
}

// ------------------------------------------------------------------------- END

