/*!
 * @file main.c
 * @brief IR Grid 4 Click example
 *
 * # Description
 * This example demonstrates the use of IR Grid 4 Click by reading and displaying
 * the ambient and object temperature measurements in a 16x12 pixels grid format.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the ambient and object temperature measurements every 500ms and displays
 * the results on the USB UART in a form of a 16x12 pixels grid.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irgrid4.h"

static irgrid4_t irgrid4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid4_cfg_t irgrid4_cfg;  /**< Click config object. */

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
    irgrid4_cfg_setup( &irgrid4_cfg );
    IRGRID4_MAP_MIKROBUS( irgrid4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgrid4_init( &irgrid4, &irgrid4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGRID4_ERROR == irgrid4_default_cfg ( &irgrid4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float image[ 192 ] = { 0 };
    float ambient_temp = 0;
    if ( IRGRID4_OK == irgrid4_get_measurement ( &irgrid4, &ambient_temp, image ) )
    {
        log_printf( &logger, " Ambient temperature: %.2f degC\r\n", ambient_temp );
        log_printf( &logger, "--- Object temperature image ---\r\n" );
        for ( uint8_t pixel_cnt = 0; pixel_cnt < 192; pixel_cnt++ ) 
        {
            log_printf( &logger, "%.2f", image[ pixel_cnt ] );
            if ( 15 == ( pixel_cnt % 16 ) ) 
            {
                log_printf( &logger, "\r\n" );
            }
            else 
            {
                log_printf( &logger, " | " );
            }
        }
        log_printf( &logger, "--------------------------------\r\n" );
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
