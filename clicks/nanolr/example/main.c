/*!
 * \file 
 * \brief NanoLR Click example
 * 
 * # Description
 * This example reads and processes data from Nano LR clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, and performs the click default configuration.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends a desired message
 * every 2 seconds. All data is being displayed on the USB UART.
 * 
 * ## Additional Function
 * - nanolr_process ( ) - Waits until a new message is ready, then parses it and displays the message
 *                        info on the USB UART.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nanolr.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

// #define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITTER

#define TEXT_TO_SEND "MikroE - Nano LR click"

static nanolr_t nanolr;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void nanolr_process( )
{
    uint8_t tmp_buf[ 200 ];
    
    // Clear RX buffer
    nanolr_generic_read( &nanolr, tmp_buf, 200 );
    
    while ( nanolr_rsp_rdy( &nanolr ) == 0 )
    {
        nanolr_uart_isr ( &nanolr );
        Delay_ms( 1 ); 
    }

    nanolr_err_t error;
    nanolr_rsp_t response;

    error = nanolr_parser_rsp( &nanolr, &response );

    if ( error == 0 )
    {
        log_printf( &logger, "** Message received!\r\n" );
        log_printf( &logger, "** Message Length: %u\r\n", response.length );
        log_printf( &logger, "** Notification ID: 0x%.2X\r\n", ( uint16_t ) response.message_id );
        log_printf( &logger, "** Options: 0x%.4X\r\n", ( response.payload[ 0 ] << 8 ) | response.payload[ 1 ] );
        log_printf( &logger, "** RSSI in dBm: %d\r\n", ( response.payload[ 2 ] << 8 ) | ~response.payload[ 3 ] );
        log_printf( &logger, "** Source Address: 0x%.4X\r\n", ( response.payload[ 4 ] << 8 ) | response.payload[ 5 ] );
        log_printf( &logger, "** Destination Address: 0x%.4X\r\n", ( response.payload[ 6 ] << 8 ) | response.payload[ 7 ] );
        log_printf( &logger, "** Message Content: " );
        for ( uint16_t cnt = 8; cnt < response.length - 4; cnt++ )
        {
            log_printf( &logger, "%c", ( uint16_t ) response.payload[ cnt ] );
        }

        log_printf( &logger, "\r\n** Checksum: 0x%.2X\r\n", ( uint16_t ) response.crc );
    }
    else
    {
        log_printf( &logger, "** Message Error!\r\n" );
    }
    log_printf( &logger, "------------------------------------\r\n" );

    log_printf( &logger, "\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanolr_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nanolr_cfg_setup( &cfg );
    NANOLR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanolr_init( &nanolr, &cfg );

    nanolr_default_cfg( &nanolr );

    log_printf( &logger,  "----  Nano LR Click ----\r\n" );

#ifdef DEMO_APP_RECEIVER
    log_printf( &logger,  "---- RECEIVER MODE ----\r\n" );
#endif
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger,  "---- TRANSMITER MODE ----\r\n" );
#endif 
    Delay_ms( 2000 );
}

void application_task ( void )
{    
#ifdef DEMO_APP_RECEIVER
    nanolr_process( );
#endif

#ifdef DEMO_APP_TRANSMITTER
    nanolr_send_data( &nanolr, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, "The message \"%s\" has been sent!\r\n", ( uint8_t * ) TEXT_TO_SEND );
    log_printf( &logger, "------------------------------------------------------------\r\n" );
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

// ------------------------------------------------------------------------ END
