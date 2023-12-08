/*!
 * @file main.c
 * @brief DIGI POT 14 Click example
 *
 * # Description
 * This library contains API for DIGI POT 14 Click driver.
 * The demo application uses a digital potentiometer 
 * to change the resistance values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the DIGI POT 14 Click board™.
 * The demo application iterates through the entire wiper range..
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot14.h"

static digipot14_t digipot14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot14_cfg_t digipot14_cfg;  /**< Click config object. */

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
    digipot14_cfg_setup( &digipot14_cfg );
    DIGIPOT14_MAP_MIKROBUS( digipot14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot14_init( &digipot14, &digipot14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT14_ERROR == digipot14_default_cfg ( &digipot14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t wiper_val = DIGIPOT14_MIN_POSITION; wiper_val <= DIGIPOT14_MAX_POSITION; wiper_val++ )
    {
        
        digipot14_set_pot_a_wiper( &digipot14, wiper_val );
        digipot14_set_pot_b_wiper( &digipot14, wiper_val );
        log_printf( &logger, " Resistance = %.3f KOhm \r\n", 
                    ( DIGIPOT14_MAX_RESISTANCE_KOHM * ( wiper_val / DIGIPOT14_MAX_POSITION_NUM ) ) );
        Delay_ms( 1000 );
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
