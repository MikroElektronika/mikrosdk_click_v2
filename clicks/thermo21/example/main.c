/*!
 * @file main.c
 * @brief Thermo21 Click example
 *
 * # Description
 * This example application showcases ability of the click board
 * to read temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules(SPI, UART).
 *
 * ## Application Task
 * Read and log temperautre every half second.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo21.h"

static thermo21_t thermo21;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo21_cfg_t thermo21_cfg;  /**< Click config object. */

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
    thermo21_cfg_setup( &thermo21_cfg );
    THERMO21_MAP_MIKROBUS( thermo21_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermo21_init( &thermo21, &thermo21_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature = 0;
    if ( !thermo21_temperature_read( &thermo21, &temperature ) )
    {
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
    }
    Delay_ms( 500 );
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
