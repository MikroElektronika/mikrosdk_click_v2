/*!
 * @file main.c
 * @brief Hall Switch 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of Hall Switch 2 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and makes an initial log.
 *
 * ## Application Task
 * Displays the corresponding message on the USB UART based on the switches state, 
 * i.e. based on the magnetic field presence.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallswitch2.h"

static hallswitch2_t hallswitch2;   /**< Hall Switch 2 Click driver object. */
static log_t logger;                /**< Logger object. */
static uint8_t print_state = 0xFF;  /**< Starting case, any number above 2 should be good for our example. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    hallswitch2_cfg_t hallswitch2_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    hallswitch2_cfg_setup( &hallswitch2_cfg );
    HALLSWITCH2_MAP_MIKROBUS( hallswitch2_cfg, MIKROBUS_1 );
    if ( hallswitch2_init( &hallswitch2, &hallswitch2_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    switch ( hallswitch2_check_state( &hallswitch2 ) )
    {
        case HALLSWITCH2_NO_MAGNET_DETECTED:
        {
            if ( HALLSWITCH2_NO_MAGNET_DETECTED != print_state )
            {
                log_printf( &logger, " No magnet detected\r\n" );
                log_printf( &logger, " Switches - disabled\r\n\r\n" );
                print_state = HALLSWITCH2_NO_MAGNET_DETECTED;
            }
            break;
        }
        case HALLSWITCH2_S_POLE_DETECTED:
        {
            if ( HALLSWITCH2_S_POLE_DETECTED != print_state )
            {
                log_printf( &logger, " South pole detected\r\n" );
                log_printf( &logger, " Switch 1 - enabled\r\n\r\n" );
                print_state = HALLSWITCH2_S_POLE_DETECTED;
            }
            break;
        }
        case HALLSWITCH2_N_POLE_DETECTED:
        {
            if ( HALLSWITCH2_N_POLE_DETECTED != print_state )
            {
                log_printf( &logger, " North pole detected\r\n" );
                log_printf( &logger, " Switch 2 - enabled\r\n\r\n" );
                print_state = HALLSWITCH2_N_POLE_DETECTED;
            }
            break;
        }
        default:
        {
            break;
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
