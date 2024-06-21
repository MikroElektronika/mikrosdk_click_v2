/*!
 * @file main.c
 * @brief Relay 7 Click example
 *
 * # Description
 * This example demonstrates the use of the Relay 7 click board by toggling the relay state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application toggles the state of all relays every 5 seconds. 
 * The results are sent to the UART terminal, where you can monitor their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "relay7.h"

static relay7_t relay7;
static log_t logger;
static relay7_relay_state_t relay_state = RELAY7_STATE_CLOSE;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay7_cfg_t relay7_cfg;  /**< Click config object. */

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
    relay7_cfg_setup( &relay7_cfg );
    RELAY7_MAP_MIKROBUS( relay7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == relay7_init( &relay7, &relay7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RELAY7_ERROR == relay7_default_cfg ( &relay7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t relay_sel = RELAY7_SEL_REL1; relay_sel <= RELAY7_SEL_REL4; relay_sel++ )
    {
        if ( RELAY7_OK == relay7_set_relay( &relay7, relay_sel, relay_state ) )
        {
            log_printf( &logger, " Relay %d ", ( uint16_t ) relay_sel );
            if ( RELAY7_STATE_OPEN == relay_state )
            {
                log_printf( &logger, " normally open state\r\n" );
            }
            else
            {
                log_printf( &logger, " normally close state\r\n" );
            }
        }
        Delay_ms ( 1000 );
    }
    relay_state = ~relay_state;
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
