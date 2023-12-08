/*!
 * @file main.c
 * @brief DIGI POT 13 Click example
 *
 * # Description
 * This library contains API for DIGI POT 13 Click driver.
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
 * This example demonstrates the use of the DIGI POT 13 Click board™.
 * The demo application iterates through the entire wiper range and 
 * sets the resistance in steps of approximately 50 kOhm.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot13.h"

static digipot13_t digipot13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot13_cfg_t digipot13_cfg;  /**< Click config object. */

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
    digipot13_cfg_setup( &digipot13_cfg );
    DIGIPOT13_MAP_MIKROBUS( digipot13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot13_init( &digipot13, &digipot13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT13_ERROR == digipot13_default_cfg ( &digipot13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    for ( uint8_t res_kohm = DIGIPOT13_RES_0_KOHM; res_kohm <= DIGIPOT13_RES_200_KOHM; res_kohm += DIGIPOT13_RES_50_KOHM )
    {
        if ( DIGIPOT13_OK == digipot13_set_resistance( &digipot13, DIGIPOT13_CFG_RES_WH, ( float ) res_kohm ) )
        {
            log_printf( &logger, " Resistance: %.1f kOhm\r\n", ( float ) res_kohm );
            log_printf( &logger, " ----------------------------\r\n" );
            Delay_ms( 5000 );
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
