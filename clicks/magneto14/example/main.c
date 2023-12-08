/*!
 * @file main.c
 * @brief Magneto 14 Click example
 *
 * # Description
 * This library contains API for the Magneto 14 Click driver.
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
 * This example demonstrates the use of the Magneto 14 Click board™.
 * Reads and displays the magnet's angular position in degrees.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneto14.h"

static magneto14_t magneto14;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto14_cfg_t magneto14_cfg;  /**< Click config object. */

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
    magneto14_cfg_setup( &magneto14_cfg );
    MAGNETO14_MAP_MIKROBUS( magneto14_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneto14_init( &magneto14, &magneto14_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO14_ERROR == magneto14_default_cfg ( &magneto14 ) )
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
    if ( MAGNETO14_OK == magneto14_get_field_strength( &magneto14, &field_strength ) )
    {
        if ( ( MAGNETO14_FLD_ST_OK == field_strength ) && 
             ( MAGNETO14_MGH_ST_OK == magneto14_get_mgh( &magneto14 ) ) && 
             ( MAGNETO14_OK == magneto14_get_angle( &magneto14, &angle ) ) )
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
