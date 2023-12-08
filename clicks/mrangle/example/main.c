/*!
 * @file main.c
 * @brief MrAngle Click example
 *
 * # Description
 * This library contains API for the MR Angle click driver.
 * This demo application shows an example of angle measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app performs default settings.
 *
 * ## Application Task
 * This is an example that shows the use of an MR Angle click board™.
 * The application task consists of reading the angle measurements in degrees ( 0 - 180 ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mrangle.h"

static mrangle_t mrangle;
static log_t logger;
static float angle;

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    mrangle_cfg_t mrangle_cfg;  /**< Click config object. */

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
    mrangle_cfg_setup( &mrangle_cfg );
    MRANGLE_MAP_MIKROBUS( mrangle_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mrangle_init( &mrangle, &mrangle_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    mrangle_default_cfg ( &mrangle );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    mrangle_get_angle( &mrangle, &angle );
    log_printf( &logger, " Angle: %.2f deg\r\n", angle );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 1000 );
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
