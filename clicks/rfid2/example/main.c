/*!
 * @file main.c
 * @brief RFID 2 Click Example.
 *
 * # Description
 * This example reads and processes data from RFID 2 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART module and sets RST pin as OUTPUT and INT pin as INPUT, also, 
 * initializes Driver init and reset chip.
 *
 * ## Application Task
 * Reads the ID card (HEX) and logs data on the USB UART.
 *
 * ## Additional Function
 * - static void rfid2_clear_app_buf ( void ) - Function clears memory of app_buf.
 * - static err_t rfid2_process ( void ) - The general process of collecting data the module sends.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "rfid2.h"

#define PROCESS_BUFFER_SIZE 200

static rfid2_t rfid2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief RFID 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void rfid2_clear_app_buf ( void );

/**
 * @brief RFID 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rfid2_process ( void );

void application_init ( void ) {
    log_cfg_t log_cfg;      /**< Logger config object. */
    rfid2_cfg_t rfid2_cfg;  /**< Click config object. */

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
    rfid2_cfg_setup( &rfid2_cfg );
    RFID2_MAP_MIKROBUS( rfid2_cfg, MIKROBUS_1 );
    err_t init_flag  = rfid2_init( &rfid2, &rfid2_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 100 );
    rfid2_reset( &rfid2 );
    Delay_ms( 100 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    log_printf( &logger, "*** Please, put your ID card.***\r\n" );
    log_printf( &logger, "*** ID card :\r\n" );
}

void application_task ( void ) {
    app_buf_len = rfid2_generic_read( &rfid2, app_buf, PROCESS_BUFFER_SIZE );
    
    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        memset( app_buf, 0, PROCESS_BUFFER_SIZE );    
    }
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

static void rfid2_clear_app_buf ( void ) {
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t rfid2_process ( void ) {
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = rfid2_generic_read( &rfid2, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) {
            rfid2_clear_app_buf(  );
            return RFID2_ERROR;
        } 
        else {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) {
            if ( rx_buff[ rx_cnt ] != 0 ) {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else{
                app_buf_len--;
                buf_cnt--;
            }

        }
        return RFID2_OK;
    }
    return RFID2_ERROR;
}

// ------------------------------------------------------------------------ END
