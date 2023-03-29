/*!
 * @file main.c
 * @brief Boost 8 Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the Boost 8 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes EN+ and EN- pins, UART log, and performs default configuration.
 *
 * ## Application Task
 * Waits for user input in order to determine what output should be enabled.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "boost8.h"

static boost8_t boost8;   /**< Boost 8 Click driver object. */
static log_t logger;    /**< Logger object. */

/**
 * @brief Boost 8 log list of commands.
 * @details This function is used for logging a list of available commands used in this example.
 */
void boost8_list_of_commands( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost8_cfg_t boost8_cfg;  /**< Click config object. */

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
    boost8_cfg_setup( &boost8_cfg );
    BOOST8_MAP_MIKROBUS( boost8_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == boost8_init( &boost8, &boost8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    boost8_default_cfg ( &boost8 );
    
    log_info( &logger, " Application Task " );
    boost8_list_of_commands();
}

void application_task ( void ) 
{
    char inx;
    
    // Waiting for the user input and performing actions based on a selected command.
    if ( log_read( &logger, &inx, 1 ) != BOOST8_ERROR )
    {
        switch(inx)
        {
            case '1' :
            {
                log_printf( &logger, "Turning on positive output \r\n" );
                boost8_enable_positive_voltage( &boost8 );
                break;
            }
            case '2' :
            {
                log_printf( &logger, "Turning off positive output \r\n" );
                boost8_disable_positive_voltage( &boost8 );
                break;
            }
            case '3' :
            {
                log_printf( &logger, "Turning on negative output \r\n" );
                boost8_enable_negative_voltage( &boost8 );
                break;
            }
            case '4':
            {
                log_printf( &logger, "Turning off negative output \r\n" );
                boost8_disable_negative_voltage( &boost8 );
                break;
            }
            case '5' :
            {
                log_printf( &logger, "Turning on both outputs \r\n" );
                boost8_enable_both_outputs( &boost8 );
                break;
            }
            case '6' :
            {
                log_printf( &logger, "Turning off both outputs \r\n" );
                boost8_disable_both_outputs( &boost8 );
                break;
            }
            default:
            {
                log_printf( &logger, "> Invalid command \r\n" );
                boost8_list_of_commands();
                break;
            }
        }
    }
    
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

void boost8_list_of_commands( void )
{
    log_printf( &logger, "> List of valid commands: \r\n" );
    log_printf( &logger, "1 - Turn on positive output \r\n" );
    log_printf( &logger, "2 - Turn off positive output \r\n" );
    log_printf( &logger, "3 - Turn on negative output \r\n" );
    log_printf( &logger, "4 - Turn off negative output \r\n" );
    log_printf( &logger, "5 - Turn on both outputs \r\n" );
    log_printf( &logger, "6 - Turn off both outputs \r\n" );
    log_printf( &logger, "Enter command from provided list:  \r\n" );
}

// ------------------------------------------------------------------------ END
