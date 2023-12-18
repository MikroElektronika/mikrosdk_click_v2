/*!
 * @file main.c
 * @brief AlphaNum G 2 Click example
 *
 * # Description
 * This example demonstrates the use of the AlphaNum G 2 Click board™ 
 * by writing and displaying the desired alphanumeric characters.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application displays digits from '0' to '9', 
 * symbols: colon, semicolon, less-than, equals-to, greater-than, question mark, at sign 
 * and capital alphabet letters, on both alphanumeric segments of the click. 
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "alphanumg2.h"

#define ASCII_CHARACTER_DIGIT_0        '0'
#define ASCII_CHARACTER_UPPERCASE_Z    'Z'

static alphanumg2_t alphanumg2;
static log_t logger;
static uint8_t character = ASCII_CHARACTER_DIGIT_0;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    alphanumg2_cfg_t alphanumg2_cfg;  /**< Click config object. */

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
    alphanumg2_cfg_setup( &alphanumg2_cfg );
    ALPHANUMG2_MAP_MIKROBUS( alphanumg2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == alphanumg2_init( &alphanumg2, &alphanumg2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ALPHANUMG2_ERROR == alphanumg2_default_cfg ( &alphanumg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, " %c %c\r\n", character, character + 1 );
    if ( ALPHANUMG2_OK == alphanumg2_display_character( &alphanumg2, 
                                                        character, ALPHANUMG2_BRIGHTNESS_MAX, 
                                                        character + 1, ALPHANUMG2_BRIGHTNESS_MAX ) )
    {
        character++;
        if ( ASCII_CHARACTER_UPPERCASE_Z <= character )
        {
            character = ASCII_CHARACTER_DIGIT_0;
            log_printf( &logger, "------------------------\r\n" );
            Delay_ms( 1000 );
        }
    }
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
