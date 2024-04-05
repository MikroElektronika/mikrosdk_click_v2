/*!
 * @file main.c
 * @brief Hall Switch 3 Click example
 *
 * # Description
 * This example demonstrates the use of Hall Switch 3 Click board 
 * by reading and displaying the magnetic field strength value.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Hall Switch 3 Click board.
 * The demo application reads and displays the relative magnetic field strength value [Gaussian units] 
 * and detects when the magnetic field strength is not in the configured range. 
 * The results are sent to the UART terminal, where you can monitor their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallswitch3.h"

static hallswitch3_t hallswitch3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallswitch3_cfg_t hallswitch3_cfg;  /**< Click config object. */

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
    hallswitch3_cfg_setup( &hallswitch3_cfg );
    HALLSWITCH3_MAP_MIKROBUS( hallswitch3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hallswitch3_init( &hallswitch3, &hallswitch3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLSWITCH3_ERROR == hallswitch3_default_cfg ( &hallswitch3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    int8_t mag_data = 0;
    if ( HALLSWITCH3_OK == hallswitch3_get_mag_data( &hallswitch3, &mag_data ) )
    {
        log_printf( &logger, " Magnetic Field: %d [Gs]\r\n", ( int16_t ) mag_data );
        if ( HALLSWITCH3_OUT_STATE_LOW == hallswitch3_check_mag_field( &hallswitch3 ) )
        {
            log_printf( &logger, " The switch is open.\r\n" );
        }
    }
    Delay_ms ( 1000 );
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
