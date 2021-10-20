/*!
 * @file main.c
 * @brief ISO 9141 Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of ISO 9141 Click board that contains a monolithic bus driver with ISO 9141 interface.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART used for communication and another UART bus used for data logging.
 *
 * ## Application Task
 * In this example transmitter/Receiver task depend on uncommented code
 * Receiver logging each received byte to the UART for data logging,
 * while transmitted send messages every 2 seconds.
 *
 * ## Additional Function
 * - static void iso9141_clear_app_buf ( void ) - Function clears memory of app_buf.
 * - static err_t iso9141_process ( void ) - The general process of collecting presponce.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "iso9141.h"

#define PROCESS_BUFFER_SIZE 200

#define TRANSMIT
//  #define RECEIVER

static iso9141_t iso9141;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief ISO 9141 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void iso9141_clear_app_buf ( void );

/**
 * @brief ISO 9141 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t iso9141_process ( void );

static uint8_t demo_message_data[ 9 ] =  { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    iso9141_cfg_t iso9141_cfg;  /**< Click config object. */

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
    log_info( &logger, " \t Application Init \r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );
    log_printf( &logger, "           ISO 9141  click         \r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );

    // Click initialization.
    iso9141_cfg_setup( &iso9141_cfg );
    ISO9141_MAP_MIKROBUS( iso9141_cfg, MIKROBUS_1 );
    err_t init_flag  = iso9141_init( &iso9141, &iso9141_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. \r\n" );
        log_info( &logger, " Please, run program again... \r\n" );

        for ( ; ; );
    }

    Delay_ms( 100 );
    log_printf( &logger, "   Set app mode:   \r\n" );
    Delay_ms( 100 );

#ifdef TRANSMIT
    log_printf( &logger, "   Transmit data   \r\n" );
    log_printf( &logger, "    Send data:    \r\n" );
    log_printf( &logger, "      MikroE      \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 1000 );
#elif defined RECEIVER
    log_printf( &logger, "   Receive data  \r\n" );
    Delay_ms( 2000 );
#else
    # error PLEASE SELECT TRANSMIT OR RECEIVE MODE!!!
#endif

    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void ) 
{
#ifdef TRANSMIT
    iso9141_send_data( &iso9141, demo_message_data );
    log_printf( &logger, "\r\n Message Sent : %s \r\n", demo_message_data );
    Delay_ms( 2000 );
    log_printf( &logger, "------------------\r\n" );    
#elif defined RECEIVER
    iso9141_process( );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        iso9141_clear_app_buf(  );
    }
#else
    # error PLEASE SELECT TRANSMIT OR RECEIVE MODE!!!
#endif
}

void main ( void )
{
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

static void iso9141_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t iso9141_process ( void )
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = iso9141_generic_read( &iso9141, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) {
            iso9141_clear_app_buf(  );
            return ISO9141_ERROR;
        }
        else {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) {
            if ( rx_buff[ rx_cnt ] != 0 ) {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else {
                app_buf_len--;
                buf_cnt--;
            }

        }
        return ISO9141_OK;
    }
    return ISO9141_ERROR;
}

// ------------------------------------------------------------------------ END
