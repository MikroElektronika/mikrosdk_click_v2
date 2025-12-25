/*!
 * @file main.c
 * @brief DIGI POT 10 Click example
 *
 * # Description
 * This example demonstrates the use of the DIGI POT 10 Click board.
 * The application gradually changes the wiper positions of both potentiometers
 * in opposite directions and logs their values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, checks communication, and applies the default configuration.
 *
 * ## Application Task
 * Alternately increments and decrements the wiper positions of both channels,
 * while logging their values every second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot10.h"

static digipot10_t digipot10;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot10_cfg_t digipot10_cfg;  /**< Click config object. */

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
    digipot10_cfg_setup( &digipot10_cfg );
    DIGIPOT10_MAP_MIKROBUS( digipot10_cfg, MIKROBUS_1 );
    err_t init_flag = digipot10_init( &digipot10, &digipot10_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT10_ERROR == digipot10_default_cfg ( &digipot10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static int16_t wiper_pos = DIGIPOT10_WIPER_ZERO_SCALE;
    static int16_t wiper_step = 33;

    if ( DIGIPOT10_OK == digipot10_set_wiper_0 ( &digipot10, wiper_pos ) )
    {
        log_printf( &logger, " Wiper 0 position: %u\r\n", wiper_pos );
    }
    if ( DIGIPOT10_OK == digipot10_set_wiper_1 ( &digipot10, ( DIGIPOT10_WIPER_FULL_SCALE - wiper_pos ) ) )
    {
        log_printf( &logger, " Wiper 1 position: %u\r\n\n", ( DIGIPOT10_WIPER_FULL_SCALE - wiper_pos ) );
    }

    wiper_pos += wiper_step;
    if ( ( wiper_pos > DIGIPOT10_WIPER_FULL_SCALE ) || 
         ( wiper_pos < DIGIPOT10_WIPER_ZERO_SCALE ) )
    {
        wiper_step = -wiper_step;
        wiper_pos += wiper_step;
        wiper_pos += wiper_step;
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
