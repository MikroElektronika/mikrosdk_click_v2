/*!
 * \file 
 * \brief PwrMeter2 Click example
 * 
 * # Description
 * This app measuring and monitoring voltage up to 24V and current up to 5A.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Gets calculated voltage, current and power data every 500 milliseconds
 * and shows results on UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pwrmeter2.h"

// ------------------------------------------------------------------ VARIABLES

static pwrmeter2_t pwrmeter2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pwrmeter2_cfg_t pwrmeter2_cfg;  /**< Click config object. */

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
    pwrmeter2_cfg_setup( &pwrmeter2_cfg );
    PWRMETER2_MAP_MIKROBUS( pwrmeter2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == pwrmeter2_init( &pwrmeter2, &pwrmeter2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PWRMETER2_ERROR == pwrmeter2_default_cfg ( &pwrmeter2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;
    float current = 0;
    float power = 0;
    if ( PWRMETER2_OK == pwrmeter2_get_data( &pwrmeter2, &voltage, &current, &power ) )
    {
        log_printf( &logger, " U = %.3f V\r\n", voltage );
        log_printf( &logger, " I = %.3f A\r\n", current );
        log_printf( &logger, " P = %.3f W\r\n\n", power );
        Delay_ms ( 500 );
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
