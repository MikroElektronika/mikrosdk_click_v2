/*!
 * @file main.c
 * @brief DIGI POT 15 Click example
 *
 * # Description
 * This example demonstrates the use of the DIGI POT 15 Click board for
 * controlling the digital potentiometer wiper position. The application
 * continuously changes the wiper value across its range to simulate
 * variable resistance.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and DIGI POT 15 Click driver, and applies the
 * default configuration.
 *
 * ## Application Task
 * Periodically updates the wiper position in steps across the full scale
 * range and logs the current value to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot15.h"

#ifndef MIKROBUS_POSITION_DIGIPOT15
    #define MIKROBUS_POSITION_DIGIPOT15 MIKROBUS_1
#endif

static digipot15_t digipot15;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot15_cfg_t digipot15_cfg;  /**< Click config object. */

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
    digipot15_cfg_setup( &digipot15_cfg );
    DIGIPOT15_MAP_MIKROBUS( digipot15_cfg, MIKROBUS_POSITION_DIGIPOT15 );
    err_t init_flag = digipot15_init( &digipot15, &digipot15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT15_ERROR == digipot15_default_cfg ( &digipot15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static int16_t wiper_pos = DIGIPOT15_WIPER_ZERO_SCALE;
    static int16_t wiper_step = 33;

    if ( DIGIPOT15_OK == digipot15_set_wiper ( &digipot15, wiper_pos ) )
    {
        log_printf( &logger, " Wiper position: %u\r\n", wiper_pos );
    }

    wiper_pos += wiper_step;
    if ( ( wiper_pos > DIGIPOT15_WIPER_FULL_SCALE ) || 
         ( wiper_pos < DIGIPOT15_WIPER_ZERO_SCALE ) )
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
