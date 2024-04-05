/*!
 * @file main.c
 * @brief CXPI Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the CXPI Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART driver.
 * In addition to this module is placed inside transmitter/receiver working mode
 * cappable of transmission/receive the data.
 *
 * ## Application Task
 * Transmitter/Receiver task depend on uncommented code
 * Receiver logging each received byte to the UART for data logging,
 * while transmitted send messages every 5 seconds.
 *
 * ## Additional Function
 * - static void cxpi_clear_current_rsp_buf ( void )
 * - static void cxpi_process ( void )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "cxpi.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 100
#define PROCESS_PARSER_BUFFER_SIZE 100

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITTER

static cxpi_t cxpi;
static log_t logger;

static char current_rsp_buf[ PROCESS_PARSER_BUFFER_SIZE ];
unsigned char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

/**
 * @brief CXPI clearing application buffer.
 * @details This function clears memory of application buffer and resets it's length and counter.
 */
static void cxpi_clear_current_rsp_buf ( void );

/**
 * @brief CXPI data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 */
static void cxpi_process ( void );

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    cxpi_cfg_t cxpi_cfg;  /**< Click config object. */

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

    // Click initialization.

    cxpi_cfg_setup( &cxpi_cfg );
    CXPI_MAP_MIKROBUS( cxpi_cfg, MIKROBUS_1 );
    err_t init_flag  = cxpi_init( &cxpi, &cxpi_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    cxpi_set_through_mode( &cxpi );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Send data:    \r\n" );
    log_printf( &logger, "      MikroE      \r\n" );
    Delay_ms ( 1000 );
#elif defined DEMO_APP_RECEIVER
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "   Receive data  \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    # error PLEASE SELECT TRANSMIT OR RECEIVE MODE!!!
#endif

    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void ) {
#ifdef DEMO_APP_TRANSMITTER
    cxpi_send_command( &cxpi, &demo_message[ 0 ] );
    log_printf( &logger, " Sent data : %s",  &demo_message[ 0 ] );
    log_printf( &logger, "------------------\r\n" ); 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif defined DEMO_APP_RECEIVER
    cxpi_process( );
    if ( current_rsp_buf > 0 ) {
        log_printf( &logger, "%s", current_rsp_buf );
        cxpi_clear_current_rsp_buf( );
    }
#else
    # error PLEASE SELECT TRANSMIT OR RECEIVE MODE!!!
#endif
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

static void cxpi_clear_current_rsp_buf ( void ) {
    memset( current_rsp_buf, 0, PROCESS_PARSER_BUFFER_SIZE );
}

static void cxpi_process ( void ) {
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;

    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;

    // Clear parser buffer
    memset( current_rsp_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 

    while( process_cnt != 0 ) {
        rsp_size = cxpi_generic_read( &cxpi, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 ) {
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ ) {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE ) {
                strncat( current_rsp_buf, uart_rx_buffer, rsp_size );
            }

            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } else {
            process_cnt--;
            // Process delay 
            Delay_ms ( 100 );
        }
    }
}

// ------------------------------------------------------------------------ END
