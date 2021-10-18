/*!
 * @file main.c
 * @brief CAN Bus Click Example.
 *
 * # Description
 * This library contains API for CAN Bus click board™.
 * This example transmits/receives and processes data from CAN Bus click.
 * The library initializes and defines the 
 * UART bus drivers to transmit or receive data. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver, wake-up module, and set high-speed operation mode.
 *
 * ## Application Task
 * Transmitter/Receiver task depends on uncommented code.
 * Receiver logging each received byte to the UART for data logging,
 * while transmitted send messages every 2 seconds.
 *
 * ## Additional Function
 * - static void canbus_clear_app_buf ( void ) - Function clears memory of app_buf.
 * - static err_t canbus_process ( void ) - The general process of collecting presponce
 *   that a module sends.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "canbus.h"

#define PROCESS_BUFFER_SIZE 200

// #define TRANSMIT
#define RECIEVER

static canbus_t canbus;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;
unsigned char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

/**
 * @brief CAN Bus clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void canbus_clear_app_buf ( void );

/**
 * @brief CAN Bus data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t canbus_process ( void );

void application_init ( void ) {
    log_cfg_t log_cfg;        /**< Logger config object. */
    canbus_cfg_t canbus_cfg;  /**< Click config object. */

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

    canbus_cfg_setup( &canbus_cfg );
    CANBUS_MAP_MIKROBUS( canbus_cfg, MIKROBUS_1 );
    err_t init_flag  = canbus_init( &canbus, &canbus_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    canbus_default_cfg ( &canbus );
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    canbus_set_high_speed_mode( &canbus );
    Delay_ms( 100 );
    
    #ifdef TRANSMIT
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      MikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );
        Delay_ms( 1000 );

    #endif
        
    #ifdef RECIEVER

        log_printf( &logger, "   Receive data  \r\n" );
        Delay_ms( 2000 );
    
    #endif
        
    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void ) {
   #ifdef TRANSMIT
    
        canbus_send_data( &canbus, demo_message );
        log_printf( &logger, "\t%s", demo_message );
        Delay_ms( 2000 );
        log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
        canbus_process( );

        if ( app_buf_len > 0 ) {
            log_printf( &logger, "%s", app_buf );
            canbus_clear_app_buf(  );
        }
    
    #endif
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

static void canbus_clear_app_buf ( void ) {
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t canbus_process ( void ) {
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = canbus_generic_read( &canbus, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) {
            canbus_clear_app_buf( );
            return CANBUS_ERROR;
        } else {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) {
            if ( rx_buff[ rx_cnt ] != 0 ) {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            } else {
                app_buf_len--;
                buf_cnt--;
            }

        }
        return CANBUS_OK;
    }
    return CANBUS_ERROR;
}

// ------------------------------------------------------------------------ END
