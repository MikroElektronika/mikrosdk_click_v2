/*!
 * \file 
 * \brief TempLog6 Click example
 * 
 * # Description
 * The example starts off with the initialization and configuration of the click and logger
 * modules, tests the communication channel and reads and displays local and remote temperature
 * values every second.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes and configures the click and logger modules and tests the communication for errors.
 * 
 * ## Application Task  
 * Reads and displays local and remote temperature values every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "templog6.h"

// ------------------------------------------------------------------ VARIABLES

static templog6_t templog6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    templog6_cfg_t cfg;

    uint8_t test;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    templog6_cfg_setup( &cfg );
    TEMPLOG6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog6_init( &templog6, &cfg );
        
    // Test communication 

    test = templog6_read_byte( &templog6, TEMPLOG6_REG_MANUFACTURER_ID );

    if ( test == TEMPLOG6_MANUFACTURER_ID )
    {
        log_printf( &logger, "--- Comunication OK!!! ---\r\n" );
    }
    else
    {
        log_printf( &logger, "--- Comunication ERROR!!! ---\r\n" );
        for ( ; ; );
    }

    templog6_default_cfg( &templog6 );

    log_printf( &logger, "--- Start measurement ---\r\n" );
}

void application_task ( )
{
    float remote_temp;
    float local_temp;
    
    local_temp = templog6_read_byte( &templog6, TEMPLOG6_REG_LOCAL_TEMPERATURE );
    log_printf( &logger, "--- Local Temperature: %f C\r\n", local_temp );
    
    remote_temp = templog6_read_byte( &templog6, TEMPLOG6_REG_REMOTE_TEMPERATURE );
    log_printf( &logger, "--- Remote Temperature: %f C\r\n", remote_temp );
    
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 1000 );
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
