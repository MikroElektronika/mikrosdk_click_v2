/*!
 * @file main.c
 * @brief LR 6 Click example
 *
 * # Description
 * This example demonstrates the use of LR 6 Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application is an echo example that sends a demo LoRa packet string 
 * and receives and processes all incoming data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lr6.h"

static lr6_t lr6;
static log_t logger;

// Demo string to be sent
#define LR6_DEMO_TEXT            "MikroE\r\n" 

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr6_cfg_t lr6_cfg;  /**< Click config object. */

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
    lr6_cfg_setup( &lr6_cfg );
    LR6_MAP_MIKROBUS( lr6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == lr6_init( &lr6, &lr6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LR6_ERROR == lr6_default_cfg ( &lr6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " --------------------\r\n" );
}

void application_task ( void )
{
    uint8_t rx_data[ 255 ] = { 0 };
    if ( LR6_OK == lr6_send_data( &lr6, LR6_DEMO_TEXT, strlen( LR6_DEMO_TEXT ), LR6_TX_MODE_SYNC ) ) 
    {
        log_info( &logger, " Send - success" );
        uint8_t rx_len = 0;
        do 
        {
            if ( LR6_OK == lr6_receive_data( &lr6, rx_data, strlen( LR6_DEMO_TEXT ), &rx_len ) )
            {
                if ( rx_len > 0 )
                { 
                    log_info( &logger, " Receive - success" );
                    log_printf( &logger, " > Receive: " );
                    for ( uint8_t cnt = 0; cnt < strlen( LR6_DEMO_TEXT ); cnt++ )
                    {
                        log_printf( &logger, "%c", rx_data[ cnt ] );
                    }

                    int8_t rssi, snr;
                    if ( LR6_OK == lr6_get_packet_status( &lr6, &rssi, &snr ) )
                    {
                        log_printf( &logger, " Rssi Pkt: %d dBm\r\n", ( int16_t ) rssi );
                        log_printf( &logger, " Snr Pkt : %d dB\r\n", ( int16_t ) snr );
                        log_printf( &logger, " --------------------\r\n" );
                        break;
                    }
                }
            }
        } 
        while ( rx_len == 0 );
    }
    else
    {
        log_info( &logger, "Send - fail" );
    }
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
