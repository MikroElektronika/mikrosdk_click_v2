/*!
 * @file main.c
 * @brief LED Flash 3 Click example
 *
 * # Description
 * This app demonstrate flash mode on LED Flash 3 Click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Turning the LED on for a second and off for another second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ledflash3.h"

static ledflash3_t ledflash3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledflash3_cfg_t ledflash3_cfg;  /**< Click config object. */

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
    ledflash3_cfg_setup( &ledflash3_cfg );
    LEDFLASH3_MAP_MIKROBUS( ledflash3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledflash3_init( &ledflash3, &ledflash3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDFLASH3_ERROR == ledflash3_default_cfg ( &ledflash3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task ");
}

void application_task ( void ) 
{
    ledflash3_strobe_pin( &ledflash3 );
    Delay_ms( 2000 );
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
