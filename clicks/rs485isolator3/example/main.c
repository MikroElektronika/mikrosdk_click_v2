/*!
 * @file main.c
 * @brief RS485 Isolator 3 Click Example.
 *
 * # Description
 * This example reads and processes data from RS485 Isolator 3 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the selected mode.
 *
 * ## Application Task
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * ## Additional Function
 * - static err_t rs485isolator3_process ( void )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "rs485isolator3.h"

#define PROCESS_BUFFER_SIZE 200

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

static rs485isolator3_t rs485isolator3;
static log_t logger;

uint8_t data_buf[ 8 ] = { 'M', 'i', 'k', 'r', 'o', 'E', '\r', '\n' };

/**
 * @brief RS485 Isolator 3 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rs485isolator3_process ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs485isolator3_cfg_t rs485isolator3_cfg;  /**< Click config object. */

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
    rs485isolator3_cfg_setup( &rs485isolator3_cfg );
    RS485ISOLATOR3_MAP_MIKROBUS( rs485isolator3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rs485isolator3_init( &rs485isolator3, &rs485isolator3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    rs485isolator3_default_cfg ( &rs485isolator3 );
    
#ifdef DEMO_APP_RECEIVER
    rs485isolator3_enable_receiver_input( &rs485isolator3 );
    rs485isolator3_disable_output( &rs485isolator3 );
    log_info( &logger, "---- Receiver mode ----" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator3_disable_receiver_input( &rs485isolator3 );
    rs485isolator3_enable_output( &rs485isolator3 );    
    log_info( &logger, "---- Transmitter mode ----" );
#endif
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_RECEIVER
    rs485isolator3_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator3_generic_write( &rs485isolator3, data_buf, strlen( data_buf ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#endif    
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

static err_t rs485isolator3_process ( void ) 
{
    int32_t rx_size;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = rs485isolator3_generic_read( &rs485isolator3, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        log_printf( &logger, "%s", rx_buf );
        return RS485ISOLATOR3_OK;
    }
    return RS485ISOLATOR3_ERROR;
}

// ------------------------------------------------------------------------ END
