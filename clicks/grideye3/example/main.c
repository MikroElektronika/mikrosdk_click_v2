/*!
 * @file main.c
 * @brief Grid-EYE 3 Click example
 *
 * # Description
 * This example demonstrates the use of Grid-EYE 3 Click by reading and displaying
 * the temperature measurements as an 8x8 pixels grid.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which enables
 * the data ready interrupt and sets data measurement to 10 frames per second.
 *
 * ## Application Task
 * Waits for a data ready interrupt and then reads the grid temperature measurements
 * and displays the results on the USB UART in a form of an 8x8 pixels grid.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "grideye3.h"

static grideye3_t grideye3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    grideye3_cfg_t grideye3_cfg;  /**< Click config object. */

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
    grideye3_cfg_setup( &grideye3_cfg );
    GRIDEYE3_MAP_MIKROBUS( grideye3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == grideye3_init( &grideye3, &grideye3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GRIDEYE3_ERROR == grideye3_default_cfg ( &grideye3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Wait for data ready interrupt
    while ( grideye3_get_int_pin ( &grideye3 ) );
    
    if ( GRIDEYE3_OK == grideye3_read_grid ( &grideye3 ) )
    {
        grideye3_clear_status ( &grideye3 );
        for ( uint8_t cnt = 0; cnt < GRIDEYE3_NUM_PIXELS; cnt++ )
        {
            if ( 0 == ( cnt % 8 ) )
            {
                log_printf( &logger, "\r\n" );
            }
            log_printf( &logger, "%.2f ", grideye3.grid_temp[ cnt ] );
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
