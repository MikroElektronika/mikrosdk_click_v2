/*!
 * @file main.c
 * @brief Charger 24 Click example
 *
 * # Description
 * This example demonstrates the use of the Charger 24 Click board. The application 
 * initializes the device, enables battery charging, and continuously monitors the 
 * charging and USB power status. It displays whether the battery is currently 
 * charging, fully charged, or if no input is detected, as well as whether the USB 
 * power is valid.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Charger 24 Click driver and enables charging while disabling boost mode.
 *
 * ## Application Task
 * Periodically reads and logs the charging and USB power status.
 *
 * @note
 * Ensure a valid USB input source and battery are connected to observe status transitions.
 *
 * @author Stefan Filipovic
 *
 */


#include "board.h"
#include "log.h"
#include "charger24.h"

static charger24_t charger24;   /**< Charger 24 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger24_cfg_t charger24_cfg;  /**< Click config object. */

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
    charger24_cfg_setup( &charger24_cfg );
    CHARGER24_MAP_MIKROBUS( charger24_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger24_init( &charger24, &charger24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    charger24_disable_boost ( &charger24 );
    charger24_enable_charging ( &charger24 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t status = charger24_get_status ( &charger24 );
    
    log_printf( &logger, "\r\n Charging status: " );
    switch ( status )
    {
        case CHARGER24_STATE_NO_INPUT:
        {
            log_printf( &logger, "No input or fault\r\n" );
            break;
        }
        case CHARGER24_STATE_CHARGING:
        {
            log_printf( &logger, "Trickle, precharge, fast charge\r\n" );
            break;
        }
        case CHARGER24_STATE_CHARGE_DONE:
        {
            log_printf( &logger, "Top-off and done\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, "Unknown\r\n" );
            break;
        }
    }

    log_printf( &logger, " USB status: " );
    if ( charger24_get_iok_pin( &charger24 ) )
    {
        log_printf( &logger, "No power\r\n" );
    }
    else
    {
        log_printf( &logger, "Power good\r\n" );
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
