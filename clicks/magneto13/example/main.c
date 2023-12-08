/*!
 * @file main.c
 * @brief Magneto 13 Click example
 *
 * # Description
 * This library contains API for the Magneto 13 Click driver.
 * The demo application reads and displays 
 * the magnet's angular position in degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Magneto 13 Click board™.
 * Reads and displays the magnet's angular position in degrees.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneto13.h"

static magneto13_t magneto13;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto13_cfg_t magneto13_cfg;  /**< Click config object. */

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
    magneto13_cfg_setup( &magneto13_cfg );
    MAGNETO13_MAP_MIKROBUS( magneto13_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneto13_init( &magneto13, &magneto13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO13_ERROR == magneto13_default_cfg ( &magneto13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------- \r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    static uint8_t field_strength = 0;
    static float angle = 0;
    if ( MAGNETO13_OK == magneto13_get_field_strength( &magneto13, &field_strength ) )
    {
        if ( ( MAGNETO13_FLD_ST_OK == field_strength ) && ( MAGNETO13_OK == magneto13_get_angle( &magneto13, &angle ) ) )
        {
            log_printf( &logger, " Angle: %.2f [deg]\r\n", angle );
            log_printf( &logger, " -------------------- \r\n" );
            Delay_ms( 1000 );
        }
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
