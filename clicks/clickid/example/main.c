/*!
 * @file main.c
 * @brief ClickID Example.
 *
 * # Description
 * This example reads the information from ClickID permanent memory.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and checks the communication with the Click board.
 *
 * ## Application Task
 * Reads the information from ClickID permanent manifest every 5 seconds.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "clickid.h"

static clickid_t clickid;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clickid_cfg_t clickid_cfg;  /**< ClickID config object. */

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

    // ClickID initialization.
    clickid_cfg_setup( &clickid_cfg );
    CLICKID_MAP_MIKROBUS( clickid_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == clickid_init( &clickid, &clickid_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CLICKID_ERROR == clickid_check_communication ( &clickid ) )
    {
        log_error( &logger, " Communication fail." );
        log_printf( &logger, "Check if the Click is attached to the correct " );
        log_printf( &logger, "MIKROBUS socket, and try again.\r\n" );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    clickid_information_t info;
    if ( CLICKID_OK == clickid_read_information ( &clickid, &info ) )
    {
        log_printf ( &logger, "\r\n --- Click info ---\r\n" );
        log_printf ( &logger, " Name: %s\r\n", info.name );
        log_printf ( &logger, " PID: MIKROE-%u\r\n", info.serial );
        log_printf ( &logger, " HW REV.: %u.%.2u\r\n", 
                     ( uint16_t ) info.hw_rev.major, ( uint16_t ) info.hw_rev.minor );
        log_printf ( &logger, " Type: 0x%.4X\r\n", info.type );
        log_printf ( &logger, " Custom: 0x%.2X\r\n", ( uint16_t ) info.custom );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
