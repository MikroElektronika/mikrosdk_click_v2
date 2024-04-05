/*!
 * @file main.c
 * @brief UART MUX 2 Click Example.
 *
 * # Description
 * This library contains API for UART MUX 2 Click driver.
 * This example transmits/receives and processes data from UART MUX 2 clicks.
 * The library initializes and defines the UART bus drivers 
 * to transmit or receive data. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and set UART channel module.
 *
 * ## Application Task
 * Transmitter/Receiver task depend on uncommented code.
 * Receiver logging each received byte to the UART for data logging,
 * while transmitted send messages every 2 seconds.
 *
 * ## Additional Function
 * - static void uartmux2_clear_app_buf ( void ) - Function clears memory of app_buf.
 * - static err_t uartmux2_process ( void ) - The general process of collecting presponce
 * that a module sends.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "uartmux2.h"

#define PROCESS_BUFFER_SIZE 200

#define TRANSMITTER
// #define RECIEVER

static uartmux2_t uartmux2;
static log_t logger;
static uint8_t uart_ch;
static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

unsigned char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

/**
 * @brief UART MUX 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void uartmux2_clear_app_buf ( void );

/**
 * @brief UART MUX 2 data reading function.
 * @details This function reads data from device and concats data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t uartmux2_process ( void );

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    uartmux2_cfg_t uartmux2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n Application Init \r\n" );

    // Click initialization.

    uartmux2_cfg_setup( &uartmux2_cfg );
    UARTMUX2_MAP_MIKROBUS( uartmux2_cfg, MIKROBUS_1 );
    err_t init_flag  = uartmux2_init( &uartmux2, &uartmux2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uartmux2_default_cfg ( &uartmux2 );
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_printf( &logger, "\r\n Application Task \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 500 );
    
    #ifdef TRANSMITTER
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      mikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );
        Delay_ms ( 1000 );

    #endif

    #ifdef RECIEVER

        uart_ch = UARTMUX2_CHANNEL_0;
        log_printf( &logger, "   Receive data  \r\n" );
        log_printf( &logger, "      UART%u \r\n", ( uint16_t ) uart_ch );
        uartmux2_set_channel( &uartmux2, uart_ch );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    
    #endif
        
    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void ) {
    #ifdef TRANSMITTER
    
    for ( uart_ch = UARTMUX2_CHANNEL_0; uart_ch <= UARTMUX2_CHANNEL_3; uart_ch++ ) {
        uartmux2_set_channel( &uartmux2, uart_ch );
        Delay_ms ( 100 );
        uartmux2_send_data( &uartmux2, demo_message );
        log_printf( &logger, "  UART%u : ", ( uint16_t ) uart_ch ); 
    
        for ( uint8_t cnt = 0; cnt < 9; cnt ++ ) {
            log_printf( &logger, "%c", demo_message[ cnt ] );
            Delay_ms ( 100 );
        }     
    }
    
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 100 );
    
    
    #endif
    
    #ifdef RECIEVER
    
    uartmux2_process( );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        uartmux2_clear_app_buf(  );
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

static void uartmux2_clear_app_buf ( void ) {
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t uartmux2_process ( void ) {
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = uartmux2_generic_read( &uartmux2, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) {
            uartmux2_clear_app_buf(  );
            return -2;
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
        return 0;
    }
    return -1;
}

// ------------------------------------------------------------------------ END
