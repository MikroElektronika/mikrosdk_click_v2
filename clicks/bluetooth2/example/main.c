/*!
 * @file main.c
 * @brief Bluetooth2 Click Example.
 *
 * # Description
 * This example reads and processes data from Bluetooth2 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, then performs a factory reset, removes all pairings, and
 * sets the local device name.
 *
 * ## Application Task
 * Logs all the received messages/responses on the USB UART, and if there's any device
 * connected to the click board the module sends a desired message every 5 seconds back to it.
 *
 * ## Additional Function
 * - static void bluetooth2_clear_app_buf ( void )
 * - static err_t bluetooth2_process ( void )
 * - static err_t bluetooth2_display_rsp ( uint16_t timeout )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the click board must be paired in order to exchange messages with each other.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bluetooth2.h"

#define PROCESS_BUFFER_SIZE 200

#define RSP_OK              "OK."
#define RSP_READY           "READY."
#define RSP_RING            "RING"
#define RSP_NO_CARRIER      "NO CARRIER"

// Local device name.
#define DEVICE_NAME         "Bluetooth2 Click"

// Message which will be sent to the connected device.
#define TEXT_TO_SEND        "MikroE - Bluetooth2 click\r\n" 

// Text sending frequency in miliseconds.
#define SENDING_FREQ        5000  

static bluetooth2_t bluetooth2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;
static uint8_t connection_flag = 0;
static uint16_t send_cnt = 0;

/**
 * @brief Bluetooth2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void bluetooth2_clear_app_buf ( void );

/**
 * @brief Bluetooth2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bluetooth2_process ( void );

/**
 * @brief Bluetooth2 display response function.
 * @details This function reads data from device until it sends OK or READY message or until
 * it exceeds the timeout value.
 * @param[in] timeout : Timeout value in miliseconds.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bluetooth2_display_rsp ( uint16_t timeout );

void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    bluetooth2_cfg_t bluetooth2_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    bluetooth2_cfg_setup( &bluetooth2_cfg );
    BLUETOOTH2_MAP_MIKROBUS( bluetooth2_cfg, MIKROBUS_1 );
    err_t init_flag  = bluetooth2_init( &bluetooth2, &bluetooth2_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    bluetooth2_default_cfg ( &bluetooth2 );
    bluetooth2_process( );
    bluetooth2_clear_app_buf( );
    
    log_printf( &logger, " - Factory Reset -\r\n" );
    bluetooth2_factory_reset ( &bluetooth2 );
    bluetooth2_display_rsp ( 2000 ); 
    
    log_printf( &logger, " - Enable OK response -\r\n" );
    bluetooth2_enable_ok_response ( &bluetooth2 );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Remove Pairings -\r\n" );
    bluetooth2_remove_pairings ( &bluetooth2 );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    bluetooth2_set_device_name ( &bluetooth2, DEVICE_NAME );
    bluetooth2_display_rsp ( 1000 ); 
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    bluetooth2_process();
    if ( app_buf_len > 0 ) 
    {
        Delay_ms( 200 );
        bluetooth2_process();
        
        if ( strstr( app_buf, RSP_RING ) )
        {
            connection_flag = 1;
            send_cnt = 0;
        }
        if ( strstr( app_buf, RSP_NO_CARRIER ) )
        {
            connection_flag = 0;
            send_cnt = 0;
        }
        log_printf( &logger, "%s", app_buf );
        bluetooth2_clear_app_buf(  );
    }
    
    if ( connection_flag == 1 && send_cnt++ > SENDING_FREQ )
    {
        bluetooth2_generic_write( &bluetooth2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
        send_cnt = 0;
    }
    
    Delay_ms( 1 );
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

static void bluetooth2_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t bluetooth2_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = bluetooth2_generic_read( &bluetooth2, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) 
        {
            bluetooth2_clear_app_buf(  );
            return BLUETOOTH2_ERROR;
        } 
        else 
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buff[ rx_cnt ] != 0 ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }

        }
        return BLUETOOTH2_OK;
    }
    return BLUETOOTH2_ERROR;
}

static err_t bluetooth2_display_rsp ( uint16_t timeout )
{
    uint16_t timeout_cnt = 0;
    
    bluetooth2_process(  );
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_READY ) == 0 ) && timeout_cnt++ < timeout )
    {
        bluetooth2_process(  );
        Delay_ms( 1 );
    }
    
    if ( app_buf_len > 0 )
    {
        for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt ] );
        }
        bluetooth2_clear_app_buf(  );
        log_printf( &logger, "--------------------------------\r\n" );
        return BLUETOOTH2_OK;
    }
    return BLUETOOTH2_ERROR;
}

// ------------------------------------------------------------------------ END
