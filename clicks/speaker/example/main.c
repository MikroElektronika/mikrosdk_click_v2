/*!
 * @file main.c
 * @brief Speaker Click Example.
 *
 * # Description
 * This library contains API for the Speaker click driver.
 * This application controls the operating modes of the 
 * Speaker click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART.
 * After driver initialization, the application performs the default settings.
 *
 * ## Application Task
 * This is an example that shows the use of a Speaker click board™.
 * The task of the application consists of 
 * switching two modes of operation: normal and shutdown modes.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "speaker.h"

static speaker_t speaker;       /**< Speaker Click driver object. */
static log_t logger;            /**< Logger object. */

void application_init ( void ) {
    log_cfg_t log_cfg;          /**< Logger config object. */
    speaker_cfg_t speaker_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    speaker_cfg_setup( &speaker_cfg );
    SPEAKER_MAP_MIKROBUS( speaker_cfg, MIKROBUS_1 );
    if ( speaker_init( &speaker, &speaker_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    speaker_default_cfg ( &speaker );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Normal Operation Mode \r\n" );
    speaker_normal_operation( &speaker );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Enter Shutdown Mode  \r\n" );
    speaker_shutdown( &speaker );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
