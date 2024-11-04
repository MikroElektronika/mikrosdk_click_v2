/*!
 * @file main.c
 * @brief LightRanger10 Click example
 *
 * # Description
 * This example demonstrates the use of LightRanger 10 Click board by reading 
 * and displaying the target object distance in millimeters.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration, and then calibrates
 * the sensor to the object positioned at 200mm distance from the sensor.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then clears the interrupt and reads the target distance
 * in millimeters and displays the results on the USB UART every 200ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lightranger10.h"

static lightranger10_t lightranger10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger10_cfg_t lightranger10_cfg;  /**< Click config object. */

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
    lightranger10_cfg_setup( &lightranger10_cfg );
    LIGHTRANGER10_MAP_MIKROBUS( lightranger10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger10_init( &lightranger10, &lightranger10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER10_ERROR == lightranger10_default_cfg ( &lightranger10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " --- Sensor calibration --- \r\n" );
    log_printf( &logger, " Place an object at 200mm distance from sensor in the next 5 seconds.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Sensor calibration is in progress...\r\n" );
    if ( LIGHTRANGER10_ERROR == lightranger10_calibrate_distance ( &lightranger10, 200 ) )
    {
        log_error( &logger, " Sensor calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    while ( lightranger10_get_int_pin ( &lightranger10 ) );
    
    uint16_t distance_mm;
    if ( ( LIGHTRANGER10_OK == lightranger10_clear_interrupts ( &lightranger10 ) ) && 
         ( LIGHTRANGER10_OK == lightranger10_get_distance ( &lightranger10, &distance_mm ) ) )
    {
        log_printf ( &logger, " Distance: %u mm \r\n\n", distance_mm );
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
