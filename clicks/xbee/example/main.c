/*!
 * @file main.c
 * @brief XBEE Click Example.
 *
 * # Description
 * This example demonstrates the use of an XBEE Click board by showing
 * the communication between the two Click boards configured in transparent mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Click board by performing a factory reset, 
 * and setting the device name, destination address, and api mode to transparent.
 *
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data or 
 * sends the desired message every 3 seconds.
 *
 * ## Additional Function
 * - static void xbee_clear_app_buf ( void )
 * - static err_t xbee_process ( void )
 * - static err_t xbee_display_rsp ( uint16_t timeout )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "xbee.h"

// Device name (Node identifier).
#define DEVICE_NAME                 "XBEE Click"

// Enter here the specific serial number high and low bytes of the remote device as a hex string or 
// leave it set to broadcast addresses for forwarding messages to all devices
#define DESTINATION_ADDRESS_HIGH    XBEE_BROADCAST_DEST_ADDRESS_HIGH
#define DESTINATION_ADDRESS_LOW     XBEE_BROADCAST_DEST_ADDRESS_LOW

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - XBEE Click board\r\n"

// Application process buffer size
#define PROCESS_BUFFER_SIZE         200

static xbee_t xbee;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief XBEE clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void xbee_clear_app_buf ( void );

/**
 * @brief XBEE data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xbee_process ( void );

/**
 * @brief XBEE display response function.
 * @details This function reads data from device until it sends OK or ERROR message or until
 * it exceeds the timeout value.
 * @param[in] timeout : Timeout value in miliseconds.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xbee_display_rsp ( uint16_t timeout );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xbee_cfg_t xbee_cfg;  /**< Click config object. */

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
    xbee_cfg_setup( &xbee_cfg );
    XBEE_MAP_MIKROBUS( xbee_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xbee_init( &xbee, &xbee_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    xbee_hw_reset ( &xbee );
    xbee_process( );
    xbee_clear_app_buf( );
    
    log_printf( &logger, " - Enter command mode -\r\n" );
    xbee_enter_command_mode ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Factory Reset -\r\n" );
    xbee_factory_reset ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Get serial number -\r\n" );
    xbee_get_serial_number ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    xbee_set_device_name ( &xbee, DEVICE_NAME );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set Destination Address -\r\n" );
    xbee_set_destination_address ( &xbee, DESTINATION_ADDRESS_HIGH, DESTINATION_ADDRESS_LOW );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Set API mode -\r\n" );
    xbee_set_api_mode ( &xbee, XBEE_MODE_TRANSPARENT );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Apply changes -\r\n" );
    xbee_apply_changes ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 ); 
    
    log_printf( &logger, " - Save changes -\r\n" );
    xbee_save_changes ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 );
    
    log_printf( &logger, " - Exit command mode -\r\n" );
    xbee_exit_command_mode ( &xbee );
    Delay_ms ( 100 );
    xbee_display_rsp ( 1000 ); 
    
    app_buf_len = 0;
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    xbee_generic_write( &xbee, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 ); 
#else
    xbee_process( );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        xbee_clear_app_buf(  );
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

static void xbee_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t xbee_process ( void ) 
{
    int32_t rx_size;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = xbee_generic_read( &xbee, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            xbee_clear_app_buf(  );
            return XBEE_ERROR;
        } 
        else 
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] != 0 ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buf[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        return XBEE_OK;
    }
    return XBEE_ERROR;
}

static err_t xbee_display_rsp ( uint16_t timeout )
{
    uint16_t timeout_cnt = 0;
    xbee_process ( );
    while ( ( 0 == strstr( app_buf, XBEE_RSP_OK ) ) && 
            ( 0 == strstr( app_buf, XBEE_RSP_ERROR ) ) && 
            ( timeout_cnt++ < timeout ) )
    {
        xbee_process ( );
        Delay_ms ( 1 );
    }
    if ( app_buf_len > 0 )
    {
        for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt ] );
        }
        xbee_clear_app_buf ( );
        log_printf( &logger, "--------------------------------\r\n" );
        return XBEE_OK;
    }
    return XBEE_ERROR;
}

// ------------------------------------------------------------------------ END
