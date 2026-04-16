/*!
 * @file main.c
 * @brief Pressure 24 Click example
 *
 * # Description
 * This example demonstrates the use of the Pressure 24 Click board for
 * measuring pressure and temperature data. The application reads sensor
 * values via the SPI interface and displays the measured results on
 * the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Pressure 24 Click driver and verifies
 * the device identifier.
 *
 * ## Application Task
 * Periodically reads pressure and temperature values from the sensor and
 * logs the results to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure24.h"

#ifndef MIKROBUS_POSITION_PRESSURE24
    #define MIKROBUS_POSITION_PRESSURE24 MIKROBUS_1
#endif

static pressure24_t pressure24;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure24_cfg_t pressure24_cfg;  /**< Click config object. */

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
    pressure24_cfg_setup( &pressure24_cfg );
    PRESSURE24_MAP_MIKROBUS( pressure24_cfg, MIKROBUS_POSITION_PRESSURE24 );
    if ( SPI_MASTER_ERROR == pressure24_init( &pressure24, &pressure24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t identifier = 0;
    if ( PRESSURE24_OK == pressure24_get_identifier ( &pressure24, &identifier ) )
    {
        log_printf ( &logger, " Identifier: 0x%.4X\r\n", identifier );
    }

    if ( PRESSURE24_IDENTIFIER_SPI_ID != ( identifier & PRESSURE24_IDENTIFIER_SPI_ID_MASK ) )
    {
        log_error( &logger, " SPI ID read fail." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float pressure = 0;
    float temperature = 0;
    if ( PRESSURE24_OK == pressure24_get_pressure ( &pressure24, &pressure ) )
    {
        log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure );
    }
    if ( PRESSURE24_OK == pressure24_get_temperature ( &pressure24, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.1f degC\r\n\n", temperature );
    }
    Delay_ms ( 100 );
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
