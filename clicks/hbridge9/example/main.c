/*!
 * @file main.c
 * @brief HBridge9 Click example
 *
 * # Description
 * This example demonstrates the use of H-Bridge 9 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which will
 * set the OUT1 to LOW, OUT2 to HIGH polarity, and the runtime to 1000ms.
 *
 * ## Application Task
 * Sends an actuation pulse every 5 seconds which will run the motor for a certain amount of time 
 * as set by default configuration.
 *
 * @note
 * The Voltage should be supplied with 6 to 18V power supply. 
 * Make sure to use a motor that operates in the above voltage range.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge9.h"

static hbridge9_t hbridge9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    hbridge9_cfg_t hbridge9_cfg;  /**< Click config object. */

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

    hbridge9_cfg_setup( &hbridge9_cfg );
    HBRIDGE9_MAP_MIKROBUS( hbridge9_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge9_init( &hbridge9, &hbridge9_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = hbridge9_default_cfg ( &hbridge9 );
    if ( HBRIDGE9_ERROR == init_flag )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    hbridge9_send_actuation_pulse( &hbridge9 );
    log_printf( &logger, " Actuation pulse has been sent. \r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
