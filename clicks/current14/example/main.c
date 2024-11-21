/*!
 * @file main.c
 * @brief Current 14 Click example
 *
 * # Description
 * This example demonstrates the use of Current 11 Click board by reading and
 * displaying the input current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and calibrates the zero current offset and data resolution
 * at 3A load current.
 *
 * ## Application Task
 * Reads the input current measurements and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current14.h"

static current14_t current14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current14_cfg_t current14_cfg;  /**< Click config object. */

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
    current14_cfg_setup( &current14_cfg );
    CURRENT14_MAP_MIKROBUS( current14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current14_init( &current14, &current14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT14_ERROR == current14_default_cfg ( &current14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating zero current offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no current flows through the sensor during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT14_ERROR == current14_calib_offset ( &current14 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );

    log_printf( &logger, " Calibrating data resolution in 5 seconds...\r\n" );
    log_printf( &logger, " Keep the load current set at 3A during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT14_ERROR == current14_calib_resolution ( &current14, 3.0f ) )
    {
        log_error( &logger, " Calibrate resolution." );
        for ( ; ; );
    }
    log_printf( &logger, " Data resolution calibration DONE.\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;
    if ( CURRENT14_OK == current14_get_current ( &current14, &current ) )
    {
        log_printf ( &logger, " Current: %.3f A\r\n\n", current );
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
