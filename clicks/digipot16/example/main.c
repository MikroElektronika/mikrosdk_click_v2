/*!
 * @file main.c
 * @brief DIGI POT 16 Click example
 *
 * # Description
 * This example demonstrates the use of the DIGI POT 16 Click board for
 * controlling the digital potentiometer wiper position. The application
 * continuously changes the wiper value across its range to simulate
 * variable resistance.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and DIGI POT 16 Click driver, and applies the
 * default configuration.
 *
 * ## Application Task
 * Periodically sweeps the wiper position back and forth across the full scale range
 * (0 to 1023) in steps of 33. Logs the current wiper position and the
 * corresponding calculated resistances RWB and RWA to the serial terminal.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot16.h"

#ifndef MIKROBUS_POSITION_DIGIPOT16
    #define MIKROBUS_POSITION_DIGIPOT16 MIKROBUS_1
#endif

static digipot16_t digipot16;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot16_cfg_t digipot16_cfg;  /**< Click config object. */

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
    digipot16_cfg_setup( &digipot16_cfg );
    DIGIPOT16_MAP_MIKROBUS( digipot16_cfg, MIKROBUS_POSITION_DIGIPOT16 );
    if ( SPI_MASTER_ERROR == digipot16_init( &digipot16, &digipot16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT16_ERROR == digipot16_default_cfg ( &digipot16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static int16_t wiper_pos = DIGIPOT16_WIPER_ZERO_SCALE;
    static int16_t wiper_step = 33;
    uint32_t rwb_ohm = 0;
    uint32_t rwa_ohm = 0;

    if ( DIGIPOT16_OK == digipot16_set_wiper ( &digipot16, ( uint16_t ) wiper_pos ) )
    {
        if ( DIGIPOT16_OK == digipot16_get_resistance ( &digipot16, &rwb_ohm, &rwa_ohm ) )
        {
            log_printf( &logger, " Wiper position: %d\r\n", wiper_pos );
            log_printf( &logger, " RWB: %lu Ohm\r\n", rwb_ohm );
            log_printf( &logger, " RWA: %lu Ohm\r\n", rwa_ohm );
            log_printf( &logger, " -------------------------------\r\n");
        }
        else
        {
            log_error ( &logger, " Failed to get resistance." );
        }
    }
    else
    {
        log_error ( &logger, " Failed to set wiper." );
    }

    wiper_pos += wiper_step;
    if ( ( wiper_pos > DIGIPOT16_WIPER_FULL_SCALE ) ||
         ( wiper_pos < DIGIPOT16_WIPER_ZERO_SCALE ) )
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
