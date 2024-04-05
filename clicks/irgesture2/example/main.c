/*!
 * @file main.c
 * @brief IRGesture2 Click example
 *
 * # Description
 * This example demonstrates the use of IR Gesture 2 click board by reading and displaying
 * the raw ADC values of entire 60-pixel IR photodiode array.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for an end of conversion interrupt and then reads the raw ADC values of entire
 * 60-pixel IR photodiode array and displays the results on the USB UART as a 10x6 matrix
 * every 100ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irgesture2.h"

static irgesture2_t irgesture2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgesture2_cfg_t irgesture2_cfg;  /**< Click config object. */

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
    irgesture2_cfg_setup( &irgesture2_cfg );
    IRGESTURE2_MAP_MIKROBUS( irgesture2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == irgesture2_init( &irgesture2, &irgesture2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGESTURE2_ERROR == irgesture2_default_cfg ( &irgesture2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    // Wait for an end of conversion interrupt
    while ( irgesture2_get_int_pin ( &irgesture2 ) );
    
    int16_t pixels[ IRGESTURE2_NUM_SENSOR_PIXELS ];
    if ( IRGESTURE2_OK == irgesture2_read_pixels ( &irgesture2, pixels, false ) )
    {
        for ( uint8_t cnt = 0; cnt < IRGESTURE2_NUM_SENSOR_PIXELS; cnt++ )
        {
            if ( 0 == ( cnt % IRGESTURE2_SENSOR_X_SIZE ) )
            {
                log_printf( &logger, "\r\n" );
            }
            log_printf( &logger, "%d\t", pixels[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
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
