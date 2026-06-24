/*!
 * @file main.c
 * @brief Hall Switch 6 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Hall Switch 6 Click board by
 * detecting which magnetic pole is present near the TMAG5230D5D sensor
 * and logging the result via UART. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Hall Switch 6 Click driver.
 *
 * ## Application Task
 * Reads both sensor outputs every 100 ms and logs the detected magnetic
 * pole state. A message is logged only when the state changes.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "hallswitch6.h"

#ifndef MIKROBUS_POSITION_HALLSWITCH6
    #define MIKROBUS_POSITION_HALLSWITCH6 MIKROBUS_1
#endif

static hallswitch6_t hallswitch6;   /**< Hall Switch 6 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallswitch6_cfg_t hallswitch6_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    hallswitch6_cfg_setup( &hallswitch6_cfg );
    HALLSWITCH6_MAP_MIKROBUS( hallswitch6_cfg, MIKROBUS_POSITION_HALLSWITCH6 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hallswitch6_init( &hallswitch6, &hallswitch6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
     
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t pole_old = HALLSWITCH6_POLE_UNINIT;
    uint8_t pole = hallswitch6_get_pole( &hallswitch6 );

    if ( pole != pole_old )
    {
        pole_old = pole;
        switch ( pole )
        {
            case HALLSWITCH6_SOUTH_POLE:
            {
                log_printf( &logger, " Magnetic pole: SOUTH\r\n" );
                break;
            }
            case HALLSWITCH6_NORTH_POLE:
            {
                log_printf( &logger, " Magnetic pole: NORTH\r\n" );
                break;
            }
            case HALLSWITCH6_NO_MAGNET:
            {
                log_printf( &logger, " No magnet detected\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, " Unknown state\r\n" );
                break;
            }
        }
    }

    Delay_ms ( 100 );
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
