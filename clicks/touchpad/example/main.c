/*!
 * \file 
 * \brief Touchpad Click example
 * 
 * # Description
 * Demo application shows reading of current event:
 *   - touch event (Touch Coordinates)
 *   - Gesture event (gesture type)
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Setting the click in the default configuration.
 * 
 * ## Application Task  
 * Reads every touch and gesture and this data logs to USBUART.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "touchpad.h"

// ------------------------------------------------------------------ VARIABLES

static touchpad_t touchpad;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchpad_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    touchpad_cfg_setup( &cfg );
    TOUCHPAD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchpad_init( &touchpad, &cfg );

    touchpad_default_cfg( &touchpad );

    log_info( &logger, "---- Waiting for a new touch or gesure event ----" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    uint8_t state;
    uint8_t gesture;
    touchpad_cord_t cord;

    //  Task implementation.

    Delay_ms( 50 );
    state = touchpad_get_event_state( &touchpad );
    if ( state == TOUCHPAD_EVENT_TOUCH )
    {
        touchpad_get_touch_coordinate( &touchpad, &cord );

        log_printf( &logger, "\r\n>> Touch coordinate <<" );
        log_printf( &logger, "\r\n>> ........... <<\r\n" );
        log_printf( &logger, "** X cord: %d \r\n** Y cord: %d \r\n", cord.x, cord.y );
        log_printf( &logger, ">> ........... <<\r\n" );
        Delay_ms( 50 );
    }
    else if ( state == TOUCHPAD_EVENT_GESTURE )
    {
        gesture = touchpad_get_gesture_type( &touchpad );
        switch( gesture )
        {
            case TOUCHPAD_GS_CLICK_AND_HOLD :
            {
                log_printf( &logger, "**Gesture type: Click and Hold\r\n" );
                break;
            }
            case TOUCHPAD_GS_DOUBLE_CLICK :
            {
                log_printf( &logger, "\r\n**Gesture type: Double Click\r\n" );
                break;
            }
            case TOUCHPAD_GS_SINGLE_CLICK :
            {
                log_printf( &logger, "\r\n**Gesture type: Single Click\r\n" );
                break;
            }
            case TOUCHPAD_GS_DOWN_SWIPE :
            {
                log_printf( &logger, "\r\n**Gesture type: Down Swipe\r\n" );
                break;
            }
            case TOUCHPAD_GS_DOWN_SWIPE_AND_HOLD :
            {
                log_printf( &logger, "\r\n**Gesture type: Down Swipe and Hold\r\n" );
                break;
            }
            case TOUCHPAD_GS_RIGHT_SWIPE :
            {
                log_printf( &logger, "\r\n**Gesture type: Right Swipe\r\n" );
                break;
            }
            case TOUCHPAD_GS_RIGHT_SWIPE_AND_HOLD :
            {
                log_printf( &logger, "\r\n**Gesture type: Right Swipe and Hold\r\n" );
                break;
            }
            case TOUCHPAD_GS_UP_SWIPE :
            {
                log_printf( &logger, "\r\n**Gesture type: Up Swipe\r\n" );
                break;
            }
            case TOUCHPAD_GS_UP_SWIPE_AND_HOLD :
            {
                log_printf( &logger, "\r\n**Gesture type: Up Swipe and Hold\r\n" );
                break;
            }
            case TOUCHPAD_GS_LEFT_SWIPE :
            {
                log_printf( &logger, "\r\n**Gesture type: Left Swipe\r\n" );
                break;
            }
            case TOUCHPAD_GS_LEFT_SWIPE_AND_HOLD :
            {
                log_printf( &logger, "\r\n**Gesture type: Left Swipe and Hold\r\n" );
                break;
            }
       }
    }
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
