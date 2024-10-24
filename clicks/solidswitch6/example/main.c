/*!
 * @file main.c
 * @brief SolidSwitch 6 Click example
 *
 * # Description
 * This library contains API for the SolidSwitch 6 Click driver 
 * and demonstrate uses of the high-side switch controller with intelligent fuse protection.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application reads and displays the device temperature 
 * and voltage level of the current sense amplifier, NTC, and output voltage measurement.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solidswitch6.h"

static solidswitch6_t solidswitch6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch6_cfg_t solidswitch6_cfg;  /**< Click config object. */
    
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
    solidswitch6_cfg_setup( &solidswitch6_cfg );
    SOLIDSWITCH6_MAP_MIKROBUS( solidswitch6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch6_init( &solidswitch6, &solidswitch6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH6_ERROR == solidswitch6_default_cfg ( &solidswitch6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ______________________\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    float app_buf = 0;
    if ( SOLIDSWITCH6_OK == solidswitch6_get_device_temp( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " Temperature: %.2f [degC]\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vntc( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " NTC: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vout( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " Vout: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    if ( SOLIDSWITCH6_OK == solidswitch6_get_vds( &solidswitch6, &app_buf ) )
    {
        log_printf( &logger, " VDS: %.2f V\r\n", app_buf );
        Delay_ms ( 100 );
    }

    log_printf( &logger, " ______________________\r\n" );
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
