/*!
 * @file main.c
 * @brief DIGI POT 11 Click example
 *
 * # Description
 * This example demonstrates the use of DIGI POT 11 click board by changing
 * the wipers position of both U1 and U2 devices.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Iterates through the entire wiper range and sets the wipers position of 
 * both U1 and U2 devices once per second. The current wiper position will 
 * be displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot11.h"

static digipot11_t digipot11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot11_cfg_t digipot11_cfg;  /**< Click config object. */

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
    digipot11_cfg_setup( &digipot11_cfg );
    DIGIPOT11_MAP_MIKROBUS( digipot11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot11_init( &digipot11, &digipot11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint16_t wiper_pos = DIGIPOT11_WIPER_ZERO_SCALE; wiper_pos <= DIGIPOT11_WIPER_FULL_SCALE; wiper_pos += 5 )
    {
        if ( DIGIPOT11_OK == digipot11_set_u1_wiper ( &digipot11, DIGIPOT11_WIPER_SEL_BOTH, ( uint8_t ) wiper_pos ) )
        {
            log_printf( &logger, " U1 wipers position: %u\r\n", wiper_pos );
        }
        if ( DIGIPOT11_OK == digipot11_set_u2_wiper ( &digipot11, DIGIPOT11_WIPER_SEL_BOTH, 
                                                      ( uint8_t ) ( DIGIPOT11_WIPER_FULL_SCALE - wiper_pos ) ) )
        {
            log_printf( &logger, " U2 wipers position: %u\r\n\n", ( DIGIPOT11_WIPER_FULL_SCALE - wiper_pos ) );
        }
        Delay_ms ( 1000 );
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
