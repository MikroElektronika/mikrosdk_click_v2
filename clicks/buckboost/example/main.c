/*!
 * \file 
 * \brief Buck-Boost  Click example
 * 
 * # Description
 * The demo application change output voltage from 2500 mV to 15000 mV every 5 seconds.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device and set default configuration.
 * 
 * ## Application Task  
 *  This is a example which demonstrates the use of Buck Boost Click board.
 *  Change output voltage from 2500 mV to 15000 mV every 5 seconds.
 *  All data logs write on usb uart for aproximetly every 5 sec.
 *  
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buckboost.h"

// ------------------------------------------------------------------ VARIABLES

static buckboost_t buckboost;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    buckboost_cfg_setup( &cfg );
    BUCKBOOST_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost_init( &buckboost, &cfg );

    buckboost_default_cfg( &buckboost );
    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "        Buck Boost Click        \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    log_printf( &logger, " Set Output Voltage of  2500 mV \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    buckboost_set_2500mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Set Output Voltage of  3300 mV \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    buckboost_set_3300mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Set Output Voltage of  4100 mV \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    buckboost_set_4100mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Set Output Voltage of  5000 mV \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    buckboost_set_5000mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Set Output Voltage of  6900 mV \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    buckboost_set_6900mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Set Output Voltage of  8200 mV \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    buckboost_set_8200mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Set Output Voltage of  12000 mV \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    buckboost_set_12000mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Set Output Voltage of  15000 mV \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    buckboost_set_15000mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
