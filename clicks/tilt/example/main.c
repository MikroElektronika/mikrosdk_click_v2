/*!
 * \file 
 * \brief Tilt Click example
 * 
 * # Description
 * This is a example which demonstrates the use of Tilt Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Detect the movement's direction 
 * of RPI-1035 Surface Mount Type 4-Direction Detector on Tilt click board.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart when the movement's direction is changed.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "tilt.h"

// ------------------------------------------------------------------ VARIABLES

static tilt_t tilt;
static log_t logger;

static uint8_t tilt_direction;
static uint8_t tilt_direction_old;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    tilt_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    tilt_cfg_setup( &cfg );
    TILT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tilt_init( &tilt, &cfg );
    
    tilt_direction_old = 0;
    
    log_printf(&logger, "-------------\r\n");
    log_printf(&logger, " Tilt  Click \r\n");
    log_printf(&logger, "-------------\r\n");
    Delay_ms( 100 );
}

void application_task ( void )
{
    tilt_direction = tilt_direction( &tilt );

    if ( tilt_direction_old != tilt_direction )
    {
        if ( tilt_direction == TILT_LEFT_DETECTION )
        {
            log_printf(&logger, "    LEFT     \r\n");
        }

        if ( tilt_direction == TILT_RIGHT_DETECTION )
        {
            log_printf(&logger, "    RIGHT    \r\n");
        }

        if ( tilt_direction == TILT_UP_DETECTION )
        {
            log_printf(&logger, "     UP      \r\n");
        }

        if ( tilt_direction == TILT_DOWN_DETECTION )
        {
            log_printf(&logger, "    DOWN     \r\n");
        }

        tilt_direction_old = tilt_direction;
        log_printf(&logger, "-------------\r\n");
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
