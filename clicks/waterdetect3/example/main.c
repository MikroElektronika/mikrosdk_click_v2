/*!
 * @file main.c
 * @brief Water Detect 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Water Detect 3 Click board by
 * detecting if water is present on the sensor part of the click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures hardware for the detection.
 *
 * ## Application Task
 * Detects if any water is present on the sensor part.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "waterdetect3.h"

static waterdetect3_t waterdetect3;   /**< Water Detect 3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waterdetect3_cfg_t waterdetect3_cfg;  /**< Click config object. */

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
    waterdetect3_cfg_setup( &waterdetect3_cfg );
    WATERDETECT3_MAP_MIKROBUS( waterdetect3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == waterdetect3_init( &waterdetect3, &waterdetect3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Turn potentiometer VR1 all the way to the right.\r\n" );
    Delay_ms( 5000 );
    log_printf( &logger, " Place a few drops of water onto the sensor.\r\n" );
    Delay_ms( 5000 );
    log_printf( &logger, " Turn potentiometer VR1 to the left until the detect LED turns off.\r\n" );
    Delay_ms( 5000 );
    
    while ( WATERDETECT3_PIN_STATE_HIGH == waterdetect3_get_int( &waterdetect3 ) );
    
    log_printf( &logger, " Device is ready.\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( WATERDETECT3_PIN_STATE_HIGH == waterdetect3_get_int( &waterdetect3 ) )
    {
        log_printf( &logger, " Water detected.\r\n" );
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
