/*!
 * \file 
 * \brief TempLog Click example
 * 
 * # Description
 * This example returns values of the temperature from the sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Click driver.
 * 
 * ## Application Task  
 * Reads temperature from temperature register in decimal value in 9-bit resolution,
 * converts that decimal value in celsius value and checks Alert pin witch goes active (low)
 * if the measured temperature meets or exceeds the high temperature limit.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "templog.h"

// ------------------------------------------------------------------ VARIABLES

static templog_t templog;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    templog_cfg_t cfg;

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
    templog_cfg_setup ( &cfg );    
    TEMPLOG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( TEMPLOG_OK != templog_init ( &templog, &cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    templog_default_cfg ( &templog );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t temp_in_dec = 0;
    float temp_in_cels = 0;
    
    temp_in_dec = temp_log_read_temp_dec( &templog, TEMP_LOG_RESOLUTION_9_BITS );
    temp_in_cels = temp_log_convert_to_celsius( temp_in_dec );
    
    log_printf( &logger, "Temperature in celsius value is: %.2f\r\n", temp_in_cels );

    if ( temp_log_get_alert( &templog ) == 0 )
    {
        log_printf( &logger, "TEMPERATURE LIMIT ALARMING!\r\n" );
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
