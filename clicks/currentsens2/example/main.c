/*!
 * @file main.c
 * @brief Current Sens 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of Current Sens 2 click board by reading and
 * displaying the input current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the input current measurements and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "currentsens2.h"

static currentsens2_t currentsens2;   /**< Current Sens 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentsens2_cfg_t currentsens2_cfg;  /**< Click config object. */

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
    currentsens2_cfg_setup( &currentsens2_cfg );
    CURRENTSENS2_MAP_MIKROBUS( currentsens2_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == currentsens2_init( &currentsens2, &currentsens2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Remove Click from the electrical circuit \r\n" );
    Delay_ms( 1000 );
    if ( CURRENTSENS2_ERROR == currentsens2_tare ( &currentsens2 ) )
    {
        log_error( &logger, " Click tare error." );
        for ( ; ; );
    }

    currentsens2_set_prim_turn_no( &currentsens2, CURRENTSENS2_NUM_OF_PASSES_1 );

    log_printf( &logger, " Connect Click to the electrical circuit \r\n" );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;
    if ( CURRENTSENS2_OK == currentsens2_get_current ( &currentsens2, &current ) ) 
    {
        log_printf( &logger, " Current : %.2f[A]\r\n\n", current );
        Delay_ms( 1000 );
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
