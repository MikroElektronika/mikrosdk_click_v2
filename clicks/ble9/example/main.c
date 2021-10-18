/*!
 * @file main.c
 * @brief Ble9 Click example
 *
 * # Description
 * This example reads and processes data from BLE 9 click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and starts module advertising.
 *
 * ## Application Task
 * Reads received data.
 *
 * ## Additional Function
 * - ble9_process ( ) - Logs all received messages on UART, and sends
 *   the certain message back to connected device.
 *
 * <pre>
 * For more information on the chip itself and the firmware on it,
 * please visit the following page:
 *     [1] https://docs.silabs.com/bluetooth/3.1
 *         - Take into condideration that the library itself
 *           is designed to work with GSDK version 3.1.0
 *           If you wish to use a different version of firmware,
 *           take into consideration that some functions might not work.
 * </pre>
 *
 * @author Strahinja Jacimovic
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "ble9.h"
#include "log.h"

#define PROCESS_COUNTER 5
#define PROCESS_RX_BUFFER_SIZE 50
#define PROCESS_PARSER_BUFFER_SIZE 50

// ------------------------------------------------------------------ VARIABLES

static ble9_t ble9;
static log_t logger;
static uint8_t data_mode = 0;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static int8_t ble9_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;

    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;

    // Clear current buffer
    memset( current_parser_buf, 0, PROCESS_PARSER_BUFFER_SIZE );

    while( process_cnt != 0 )
    {
        rsp_size = ble9_generic_read( &ble9, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
        {
            // Storages data in current buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }

            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );

            log_printf( &logger, "%s", current_parser_buf );
            Delay_100ms( );
        }
        else
        {
            process_cnt--;

            // Process delay
            Delay_ms( 100 );
        }
    }

    return 0;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble9_cfg_t cfg;

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
    Delay_ms( 100 );

    //  Click initialization.

    ble9_cfg_setup( &cfg );
    BLE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble9_init( &ble9, &cfg );

    log_printf( &logger, "Creating advertising point...\n" );
    Delay_ms( 100 );
    ble9_advertiser_create_id( &ble9 );

    log_printf( &logger, "Starting module advertizing...\n" );
    Delay_ms( 100 );
    ble9_advertiser_start( &ble9, BLE9_ADVERTISER_MODE_DISCOVERABLE_GENERAL,
                                  BLE9_ADVERTISER_MODE_CONNECTABLE_SCANNABLE );

    log_printf( &logger, "The module has been configured.\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    ble9_process( );
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
