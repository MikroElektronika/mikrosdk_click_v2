/*!
 * @file main.c
 * @brief Air Velocity Click example
 *
 * # Description
 * This example demonstrates the use of Air Velocity click board by reading
 * and displaying the output counts and air velocity in m/sec.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the output counts and converts it to air velocity in m/sec. Both values
 * will be displayed on the USB UART approximately every 250ms.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "airvelocity.h"

static airvelocity_t airvelocity;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airvelocity_cfg_t airvelocity_cfg;  /**< Click config object. */

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
    airvelocity_cfg_setup( &airvelocity_cfg );
    AIRVELOCITY_MAP_MIKROBUS( airvelocity_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == airvelocity_init( &airvelocity, &airvelocity_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t out_counts;
    if ( AIRVELOCITY_OK == airvelocity_read_output ( &airvelocity, &out_counts ) )
    {
        log_printf ( &logger, " Out counts: %u\r\n", out_counts );
        log_printf ( &logger, " Air velocity: %.2f m/s\r\n\n", airvelocity_convert_counts_to_mps ( out_counts ) );
        Delay_ms ( 250 );
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
