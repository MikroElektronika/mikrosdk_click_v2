/*!
 * \file 
 * \brief DcMotor10 Click example
 * 
 * # Description
 * This example is running dc motors on channels 1 through 3.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI, click drivers and uninhibites the device.
 * 
 * ## Application Task  
 * This example demonstrates the use of DC MOTOR 10 click by running dc motors 
 * on channels 1 through 3, first all 3 together and then separately.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor10.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor10_t dcmotor10;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor10_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor10_cfg_setup( &cfg );
    DCMOTOR10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor10_init( &dcmotor10, &cfg );
    Delay_ms( 100 );
    
    dcmotor10_inhibit(&dcmotor10, DCMOTOR10_UNINHIBIT );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_RESET_STATUS_REG );
    Delay_ms( 100 );
}

void application_task ( void )
{
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_1 | DCMOTOR10_ENABLE_2 
                      | DCMOTOR10_ENABLE_3 );
    Delay_ms( 5000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_1 );
    Delay_ms( 5000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_2 );
    Delay_ms( 5000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_3 );
    Delay_ms( 5000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_RESET_STATUS_REG );
    Delay_ms( 1000 );
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
