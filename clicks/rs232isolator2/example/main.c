/*!
 * @file main.c
 * @brief RS232 Isolator 2 Click Example.
 *
 * # Description
 * This library contains API for RS 232 Isolator 2 Click driver.
 * This example transmits/receives and processes data from RS 232 Isolator 2 clicks.
 * The library initializes and defines the UART bus drivers 
 * to transmit or receive data. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and wake-up module.
 *
 * ## Application Task
 * Transmitter/Receiver task depend on uncommented code.
 * Receiver logging each received byte to the UART for data logging,
 * while transmitted send messages every 2 seconds.
 *
 * ## Additional Function
 * - static void rs232isolator2_clear_app_buf ( void ) - Function clears memory of app_buf.
 * - static err_t rs232isolator2_process ( void ) - The general process of collecting presponce
 *   that a module sends.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rs232isolator2.h"

#define PROCESS_BUFFER_SIZE 200

#define TRANSMITTER
// #define RECIEVER

static rs232isolator2_t rs232isolator2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;
unsigned char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

/**
 * @brief RS 232 Isolator 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void rs232isolator2_clear_app_buf ( void );

/**
 * @brief RS 232 Isolator 2 data reading function.
 * @details This function reads data from device and concats data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rs232isolator2_process ( void );

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs232isolator2_cfg_t rs232isolator2_cfg;  /**< Click config object. */

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

    rs232isolator2_cfg_setup( &rs232isolator2_cfg );
    RS232ISOLATOR2_MAP_MIKROBUS( rs232isolator2_cfg, MIKROBUS_1 );
    err_t init_flag  = rs232isolator2_init( &rs232isolator2, &rs232isolator2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    
    #ifdef TRANSMITTER
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      mikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );
        Delay_ms ( 1000 );

    #endif
        
    #ifdef RECIEVER

        log_printf( &logger, "   Receive data  \r\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    
    #endif
        
    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void ) {
    
    #ifdef TRANSMITTER
    
    rs232isolator2_send_data( &rs232isolator2, demo_message );
    log_printf( &logger, "%s", demo_message );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
    rs232isolator2_process( );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        rs232isolator2_clear_app_buf(  );
    }
    
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

static void rs232isolator2_clear_app_buf ( void ) {
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t rs232isolator2_process ( void ) {
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = rs232isolator2_generic_read( &rs232isolator2, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) {
            rs232isolator2_clear_app_buf(  );
            return RS232ISOLATOR2_ERROR;
        } else {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) {
            if ( rx_buff[ rx_cnt ] != 0 ) {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            } else {
                app_buf_len--;
            }

        }
        return RS232ISOLATOR2_OK;
    }
    return RS232ISOLATOR2_ERROR;
}

// ------------------------------------------------------------------------ END
