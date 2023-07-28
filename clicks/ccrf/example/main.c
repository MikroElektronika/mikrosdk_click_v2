/*!
 * \file 
 * \brief ccRF Click example
 * 
 * # Description
 * This example demonstrates the use of an ccRF click board by showing
 * the communication between the two click boards configured as a receiver and transmitter.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, performs the click default configuration and 
 * displays the selected application mode.
 *
 * ## Application Task
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * \author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "ccrf.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - ccRF click board\0"

static ccrf_t ccrf;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf_cfg_t cfg;

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
    ccrf_cfg_setup( &cfg );
    CCRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf_init( &ccrf, &cfg );

    ccrf_default_cfg( &ccrf );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ccrf_transmit_packet( &ccrf, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 2000 );
#else
    uint8_t data_buf[ 64 ] = { 0 };
    uint8_t data_len = sizeof( data_buf );
    if ( CCRF_CRC_OK == ccrf_receive_packet( &ccrf, data_buf, &data_len ) )
    {
        log_printf( &logger, " A new message has received: \"" );
        for ( uint16_t cnt = 0; cnt < data_len; cnt++ )
        {
            log_printf( &logger, "%c", data_buf[ cnt ] );
        }
        log_printf( &logger, "\"\r\n" );
    }
#endif
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
