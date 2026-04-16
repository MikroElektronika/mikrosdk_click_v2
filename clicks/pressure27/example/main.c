/*!
 * @file main.c
 * @brief Pressure 27 Click example
 *
 * # Description
 * This example demonstrates the use of the Pressure 27 Click board for
 * measuring pressure. The application reads sensor
 * values via the SPI interface and displays the measured results on
 * the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Pressure 27 Click driver. 
 *
 * ## Application Task
 * Periodically reads pressure values from the sensor and
 * logs the results to the serial terminal.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure27.h"

#ifndef MIKROBUS_POSITION_PRESSURE27
    #define MIKROBUS_POSITION_PRESSURE27 MIKROBUS_1
#endif

static pressure27_t pressure27;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure27_cfg_t pressure27_cfg;  /**< Click config object. */

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
    pressure27_cfg_setup( &pressure27_cfg );
    PRESSURE27_MAP_MIKROBUS( pressure27_cfg, MIKROBUS_POSITION_PRESSURE27 );
    if ( SPI_MASTER_ERROR == pressure27_init( &pressure27, &pressure27_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float pressure = 0.0f;

    if ( PRESSURE27_OK == pressure27_get_pressure( &pressure27, &pressure ) )
    {
        log_printf( &logger, " Pressure: %.2f kPa\r\n\n", pressure );
    }
    else
    {
        log_error( &logger, " Pressure read failed.\r\n" );
    }

    Delay_ms( 1000 );
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
