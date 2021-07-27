/*!
 * \file 
 * \brief IR reflect Click example
 * 
 * # Description
 * Example demonstrates the use of IR Reflect Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - Start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of IR Reflect Click board.
 * On this type of photointerrupter the infrared emitter and receiver are facing the same direction,
 * the infrared beam from the emitter gets bounced back to the receiver when an object 
 * is placed within the detecting range of the sensor ( optimal range is 3mm ).
 * These sensors are used to detect an object's presence or motion, such as a piece of paper passing through a printer
 * and counting when sensor is triggered.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * Data logs on usb uart when the sensor is triggered.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irreflect.h"

// ------------------------------------------------------------------ VARIABLES

static irreflect_t irreflect;
static log_t logger;

static uint8_t ir_state;
static uint8_t ir_state_old;
static uint16_t counter;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irreflect_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application ----\n");

    //  Click initialization.
    irreflect_cfg_setup( &cfg );
    IRREFLECT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irreflect_init( &irreflect, &cfg );
    
    ir_state = 0;
    ir_state_old = 0;
    counter = 1;
}

void application_task ( void )
{
    //  Task implementation.
    
    ir_state = irreflect_reflect_status( &irreflect );

    if ( ir_state_old != ir_state )
    {
        if ( ir_state )
        {
            log_printf( &logger, "  Counter = %u\n", counter);
            counter++;
        }
        ir_state_old = ir_state;
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
