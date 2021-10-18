/*!
 * \file 
 * \brief EVC Click example
 * 
 * # Description
 * This application allows manipulation of 6 channel volume control
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, default configuration and sets first volume.
 * 
 * ## Application Task  
 * emulates user input and exectuyrd functions based on set of valid commands.
 * 
 * *note:* 
 * Additional Functions :
 * 
 * void test_change ( )               - Emulates user input to change parameters.
 * void mute( )                       - Mute nad 
 * void play ( )                      - Start new settings of the cahnnel
 * uint8_t get_current_channel ( )    - Return current channel.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "evc.h"

// ------------------------------------------------------------------ VARIABLES

static evc_t evc;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

uint8_t get_current_channel ( uint8_t ch )
{
    if ( ch == 1 )
    {
        return EVC_CHANNEL_1;
    }
    if ( ch == 2 )
    {
        return EVC_CHANNEL_2;
    }
    if ( ch == 3 )
    {
        return EVC_CHANNEL_3;
    }
    if ( ch == 4 )
    {
        return EVC_CHANNEL_4;
    }
    if ( ch == 5 )
    {
        return EVC_CHANNEL_5;
    }
    if ( ch == 6 )
    {
        return EVC_CHANNEL_6;
    }
    return EVC_CHANNEL_1;
}

void play ( evc_t *ctx )
{
    uint8_t current_channel;

    if ( ( ctx->play_flag == 1 ) && ( ctx->mute_flag != 1 ) )
    {
        current_channel = get_current_channel( ctx->channel );
        evc_set_volume_full( ctx, current_channel, ctx->volume );

        log_printf( &logger, " Channel [ %d ] -- Volume [ %d ] \r\n", ctx->channel, ctx->volume );
        
        ctx->play_flag = 0;
    }
}

void mute( evc_t *ctx )
{
    /* Mute and Unmute */
    if ( ctx->mute_flag == 0 )
    {
        ctx->mute_flag = 1;
        evc_mute( ctx, EVC_ALL_CHANNEL_MUTE );
        log_printf( &logger, " All channels MUTE !!!\r\n" );
    }
    else
    {
        ctx->mute_flag = 0;
        evc_mute( ctx, EVC_ALL_CHANNEL_UNMUTE );
        log_printf( &logger, " All channels UNMUTE !!!\r\n" );
    }
}

void test_change ( evc_t *ctx )
{
    ctx->channel++;

    if( ctx->channel > 6 )
    {
        ctx->channel = 6;
    }
            
    ctx->volume--;
    if( ctx->volume < -79 )
    {
        ctx->volume = -79;
        mute( ctx );
    }

    ctx->play_flag = 1;

    Delay_ms( 750 );

}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    evc_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    evc_cfg_setup( &cfg );
    EVC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    evc_init( &evc, &cfg );

    evc_default_cfg( &evc );
    log_printf( &logger, " \\-/-\\-/ START EQUALIZER \\-/-\\-/ ");
}

void application_task ( void )
{
    //  Task implementation.

    test_change( &evc );

    play( &evc );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
