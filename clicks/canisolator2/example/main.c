/*!
 * @file main.c
 * @brief CAN Isolator 2 Click Example.
 *
 * # Description
 * This example reads and processes data from CAN Isolator 2 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and wake-up module.
 *
 * ## Application Task
 * Transmitter/Receiver task depends on uncommented code.
 * Receiver logging each received byte to the UART for data logging,
 * while transmitted send messages every 2 seconds.
 *
 * ## Additional Function
 * - static void canisolator2_clear_app_buf ( void )
 * - static err_t canisolator2_process ( void )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "canisolator2.h"

#define PROCESS_BUFFER_SIZE 200

// #define TRANSMIT
#define RECIEVER

static canisolator2_t canisolator2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

unsigned char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

/**
 * @brief CAN Isolator 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void canisolator2_clear_app_buf ( void );

/**
 * @brief CAN Isolator 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t canisolator2_process ( void );

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    canisolator2_cfg_t canisolator2_cfg;  /**< Click config object. */

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

    canisolator2_cfg_setup( &canisolator2_cfg );
    CANISOLATOR2_MAP_MIKROBUS( canisolator2_cfg, MIKROBUS_1 );
    err_t init_flag  = canisolator2_init( &canisolator2, &canisolator2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
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
    
        canisolator2_send_data( &canisolator2, demo_message );
        log_printf( &logger, "\t%s", demo_message );
        Delay_ms( 2000 );
        log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
        canisolator2_process( );

        if ( app_buf_len > 0 ) {
            log_printf( &logger, "%s", app_buf );
            canisolator2_clear_app_buf(  );
        }
    
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

static void canisolator2_clear_app_buf ( void ) {
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t canisolator2_process ( void ) {
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = canisolator2_generic_read( &canisolator2, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) {
           canisolator2_clear_app_buf(  );
            return CANISOLATOR2_ERROR;
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
        return CANISOLATOR2_OK;
    }
    return CANISOLATOR2_ERROR;
}

// ------------------------------------------------------------------------ END
