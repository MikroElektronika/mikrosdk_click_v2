/*!
 * \file
 * \brief Ozone2 Click example
 *
 * # Description
 * This example shows the value of ozone measurement aquired from Ozone2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Calls functions for driver initializaton used for data conversion and results reading.
 *
 * ## Application Task
 * Reads the level of ozone in the air every with repetition of 1 second.
 * This driver is able to get the level of ozone gas in the range from 10 to 1000 ppm.
 * #note#
 * Be sure that you correctly set the AD convertor which you want to use.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ozone2.h"

// ------------------------------------------------------------------ VARIABLES

static ozone2_t ozone2;
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

    ozone2_cfg_t ozone2_cfg;

    //  Click initialization.

    ozone2_cfg_setup( &ozone2_cfg );
    OZONE2_MAP_MIKROBUS( ozone2_cfg, MIKROBUS_1 );

    if ( ozone2_init( &ozone2, &ozone2_cfg ) == OZONE2_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----\n" );
}

void application_task ( void )
{
    uint16_t o3_ppm;

    if ( ozone2_read_measurement( &ozone2, &o3_ppm ) == OZONE2_OK )
    {
        log_printf( &logger, "  O3 [ppm] : %u\r\n", o3_ppm );
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
