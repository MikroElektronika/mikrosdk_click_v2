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
 * Configuring Clicks and log objects.
 * Setting the Click in the default configuration.
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

    touchpad_cfg_setup( &cfg );
    TOUCHPAD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchpad_init( &touchpad, &cfg );

    touchpad_default_cfg( &touchpad );

    log_info( &logger, "---- Waiting for a new touch or gesure event ----" );
    Delay_ms ( 500 );
}

void application_task ( void )
{
    uint8_t state;
    uint8_t gesture;
    touchpad_cord_t cord;

    //  Task implementation.

    Delay_ms ( 50 );
    state = touchpad_get_event_state( &touchpad );
    if ( state == TOUCHPAD_EVENT_TOUCH )
    {
        touchpad_get_touch_coordinate( &touchpad, &cord );

        log_printf( &logger, "\r\n>> Touch coordinate <<" );
        log_printf( &logger, "\r\n>> ........... <<\r\n" );
        log_printf( &logger, "** X cord: %d \r\n** Y cord: %d \r\n", cord.x, cord.y );
        log_printf( &logger, ">> ........... <<\r\n" );
        Delay_ms ( 50 );
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

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
