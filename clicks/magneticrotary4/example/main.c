/*!
 * @file main.c
 * @brief MagneticRotary4 Click example
 *
 * # Description
 * This example demonstrates the use of Magnetic Rotary 4 click board by reading 
 * and displaying the magnet (potentiometer) angular position in degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, sets the rotation direction, and calibrates the sensor 
 * for potentiometer zero position.
 *
 * ## Application Task
 * Reads the magnet (potentiometer) angular position in degrees every 100ms 
 * and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneticrotary4.h"

static magneticrotary4_t magneticrotary4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary4_cfg_t magneticrotary4_cfg;  /**< Click config object. */

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
    magneticrotary4_cfg_setup( &magneticrotary4_cfg );
    MAGNETICROTARY4_MAP_MIKROBUS( magneticrotary4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary4_init( &magneticrotary4, &magneticrotary4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY4_ERROR == magneticrotary4_set_rotation_direction ( &magneticrotary4, MAGNETICROTARY4_DIRECTION_CW ) )
    {
        log_error( &logger, " Set rotation direction." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY4_ERROR == magneticrotary4_calibrate_zero_position ( &magneticrotary4 ) )
    {
        log_error( &logger, " Calibrate zero position." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float angle;
    if ( MAGNETICROTARY4_OK == magneticrotary4_get_angle ( &magneticrotary4, &angle ) )
    {
        log_printf( &logger, " Angle: %.1f degrees\r\n\n", angle );
        Delay_ms ( 100 );
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
