/*!
 * @file main.c
 * @brief N-PLC Click Example.
 *
 * # Description
 * This example demonstrates the use of an N-PLC click boards by showing
 * the communication between the two click boards configured as a receiver and transmitter.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, resets the click board to default config, displays the firmware version
 * and switches to data operation mode. After that displays the selected application mode
 * and sends an initial message in case of transmitter mode.
 *
 * ## Application Task
 * Reads all the received data and echoes them back to the transmitter. The received and echoed messages
 * will be displayed on the USB UART.
 * 
 * @note
 * Once both devices are programmed, one as a receiver and the other as a transmitter, you will need to reset
 * the transmitter board in order to start the communication by sending an initial message.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nplc.h"

// Comment out the line below in order to switch the application mode to receiver
// #define DEMO_APP_TRANSMITTER

#define DEMO_TEXT_MESSAGE       "MikroE - N-PLC click board"

#define PROCESS_BUFFER_SIZE     200
#define RSP_TIMEOUT_MS          20000

static nplc_t nplc;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief N-PLC clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void nplc_clear_app_buf ( void );

/**
 * @brief N-PLC data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read or buffer overflow error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nplc_process ( void );

/**
 * @brief N-PLC display response function.
 * @details This function checks if any data is received from device and displays it on the USB UART.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nplc_display_rsp ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nplc_cfg_t nplc_cfg;  /**< Click config object. */

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
    nplc_cfg_setup( &nplc_cfg );
    NPLC_MAP_MIKROBUS( nplc_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nplc_init( &nplc, &nplc_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    } 
    nplc_process( );
    nplc_clear_app_buf( );

    log_printf( &logger, " - HW reset -\r\n" );
    nplc_hw_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to command mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_COMMAND );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Factory reset -\r\n" );
    nplc_factory_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Reboot -\r\n" );
    nplc_sw_reset ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to command mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_COMMAND );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Show firmware version -\r\n" );
    nplc_firmware_version ( &nplc );
    nplc_display_rsp ( );
    
    log_printf( &logger, " - Go to data mode -\r\n" );
    nplc_set_mode ( &nplc, NPLC_MODE_DATA );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
    
    log_printf( &logger, " Sending initial message: %s", ( char * ) DEMO_TEXT_MESSAGE );
    nplc_generic_write( &nplc, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "\r\n--------------------------------\r\n" );
    Delay_ms ( 1000 ); 
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif   
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    nplc_process ( );
    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 500 );
        nplc_process( );
        log_printf( &logger, " Received message: %s", app_buf );
        log_printf( &logger, "\r\n--------------------------------\r\n" );
        Delay_ms ( 500 );
        log_printf( &logger, " Sending echo response: %s", app_buf );
        nplc_generic_write( &nplc, app_buf, app_buf_len );
        log_printf( &logger, "\r\n--------------------------------\r\n\n" );
        nplc_clear_app_buf( );
        Delay_ms ( 1000 ); 
    }
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

static void nplc_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t nplc_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    Delay_ms ( 1 );
    rx_size = nplc_generic_read( &nplc, rx_buff, PROCESS_BUFFER_SIZE );
    Delay_ms ( 1 );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            nplc_clear_app_buf( );
            return NPLC_ERROR;
        } 
        else 
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buff[ rx_cnt ] ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        return NPLC_OK;
    }
    return NPLC_ERROR;
}

static err_t nplc_display_rsp ( void )
{
    uint32_t timeout = RSP_TIMEOUT_MS;
    while ( timeout-- ) 
    {
        nplc_process( );
        if ( app_buf_len > 0 ) 
        {
            Delay_ms ( 100 );
            nplc_process( );
            for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
            {
                log_printf( &logger, "%c", app_buf[ buf_cnt ] );
            }
            nplc_clear_app_buf( );
            log_printf( &logger, "\r\n--------------------------------\r\n" );
            return NPLC_OK;
        }
    }
    return NPLC_ERROR;
}

// ------------------------------------------------------------------------ END
