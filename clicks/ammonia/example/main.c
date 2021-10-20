/*!
 * \file
 * \brief Ammonia Click example
 *
 * # Description
 * This example shows the value of ammonia measurement aquired from Ammonia Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Calls functions for driver initializaton used for data conversion and results reading.
 *
 * ## Application Task
 * Reads the level of ammonia in the air every with repetition of 1 second.
 * This driver is able to get the level of ammonia gas in the range from 5 to 200 ppm.
 * #note#
 * Be sure that you correctly set the AD convertor which you want to use.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ammonia.h"

// ------------------------------------------------------------------ VARIABLES

static ammonia_t ammonia;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    ammonia_cfg_t ammonia_cfg;

    //  Click initialization.

    ammonia_cfg_setup( &ammonia_cfg );
    AMMONIA_MAP_MIKROBUS( ammonia_cfg, MIKROBUS_1 );

    if ( ammonia_init( &ammonia, &ammonia_cfg ) == AMMONIA_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----\n" );
}

void application_task ( void )
{
    uint16_t nh3_ppm;

    if ( ammonia_read_measurement( &ammonia, &nh3_ppm ) == AMMONIA_OK )
    {
        log_printf( &logger, "  NH3 [ppm] : %u\r\n", nh3_ppm );
        Delay_ms( 1000 );
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
