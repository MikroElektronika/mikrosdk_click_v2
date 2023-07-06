/*!
 * @file 
 * @brief FT Click example
 * 
 * # Description
 * This example demonstrates the use of an FT click board by showing
 * the communication between the two click boards.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device and makes an initial log.
 * 
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data or 
 * sends the desired text message once per second.
 * 
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "ft.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - FT click board\r\n\0"

static ft_t ft;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    ft_cfg_t ft_cfg;

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
    ft_cfg_setup( &ft_cfg );
    FT_MAP_MIKROBUS( ft_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ft_init( &ft, &ft_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

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
    ft_send_package( &ft, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ), 1 );
    log_printf( &logger, " Sent data: %s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 );
#else
    uint8_t rsp_data_buf[ FT_MAX_DATA_BUFFER ] = { 0 };
    uint8_t rx_byte = 0;
    if ( 1 == ft_generic_read( &ft, &rx_byte, 1 ) )
    {
        ft_isr_parser( &ft, rx_byte ); 
        if ( FT_NEW_DATA_AVAILABLE == ft_get_data_status( &ft ) )
        {
            if ( ft_get_data( &ft, rsp_data_buf ) )
            {
                log_printf( &logger, " Received data: %s", rsp_data_buf );
            }
        }
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
