/*!
 * \file 
 * \brief MOTION Click example
 * 
 * # Description
 * This application detects any motion around it and shows message
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver enable's the motion detection.
 * 
 * ## Application Task  
 * Detect the motion and send a notification to the UART.
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "motion.h"

// ------------------------------------------------------------------ VARIABLES

static motion_t motion;
static log_t logger;

motion_detect_state_t motion_state;
motion_detect_state_t motion_old_state;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    motion_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");
    log_printf( &logger, "------------------------\r\n" );

    //  Click initialization.

    motion_cfg_setup( &cfg );
    MOTION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motion_init( &motion, &cfg );
    log_printf( &logger, "      Motion Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );

    motion_default_cfg ( &motion );
    log_printf( &logger, "  Enable Motion sensor\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 );

    motion_state = MOTION_NO_DETECT;
    motion_old_state = MOTION_DETECTED;
}

void application_task ( void )
{
    //  Task implementation.

    motion_state = motion_get_detected( &motion );

    if ( motion_state == MOTION_DETECTED &&  motion_old_state == MOTION_NO_DETECT )
    {
        motion_old_state = MOTION_DETECTED;
        log_printf( &logger, "  > Motion detected! <\r\n" );
        log_printf( &logger, "------------------------\r\n" );
   }

   if ( motion_old_state == MOTION_DETECTED &  motion_state == MOTION_NO_DETECT )
   {
        log_printf( &logger, "  There is no movement\r\n" );
        log_printf( &logger, "------------------------\r\n" );
        motion_old_state = MOTION_NO_DETECT;
   }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
