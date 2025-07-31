/*!
 * @file main.c
 * @brief ESP8684 Click Example.
 *
 * # Description
 * This example connects to the desired WiFi network and then
 * connects to the TCP/UDP server, writes then reads data to and from it.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and wifi communication, then connects to the desired WiFi network
 * and sends data to the TCP/UDP server.
 *
 * ## Application Task
 * Writes and reads data from TCP/UDP server, processes all incoming data 
 * and displays them on the USB UART.
 *
 * ## Additional Function
 * - void esp8684_clear_app_buf ( void )
 * - void esp8684_log_app_buf ( void )
 * - err_t esp8684_process ( void )
 * - err_t esp8684_rsp_check ( uint8_t *response )
 * - void esp8684_error_check( err_t error_flag )
 * - void esp8684_send_message ( uint8_t *link_id, uint8_t *message )
 * - void esp8684_con_device_to_network ( void )
 * - void esp8684_send_data ( void )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "esp8684.h"
#include "string.h"
#include "conversions.h"

#define PROCESS_BUFFER_SIZE 200

#define ESP8684_SSID                        "MIKROE GUEST"
#define ESP8684_PASSWORD                    "!guest.mikroe!"

#define ESP8684_DATA                        "MikroE ESP8684 Click"

// TCP/UDP example parameters
#define REMOTE_IP                           "54.187.244.144"// TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port
#define TCP_LINK_ID                         "0"             // TCP link ID
#define UDP_LINK_ID                         "1"             // UDP link ID

esp8684_t esp8684;
log_t logger;

uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
int32_t app_buf_len = 0;

err_t app_error_flag;

/**
 * @brief ESP8684 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return Nothing.
 * @note None.
 */
void esp8684_clear_app_buf ( void );

/**
 * @brief ESP8684 log application buffer.
 * @details This function logs application buffer and reset its length.
 * @return Nothing.
 * @note None.
 */
void esp8684_log_app_buf ( void );

/**
 * @brief ESP8684 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t esp8684_process ( void );

/**
 * @brief ESP8684 response check function.
 * @details This function checks the response of the sent command.
 * @param[in] response : Expected response. 
 * @return @li @c  0 - Responded as expected.
 *         @li @c -1 - The response isn't the same..
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t esp8684_rsp_check ( uint8_t *response );

/**
 * @brief ESP8684 error check function.
 * @details This function checks if error has occurred.
 * @param[in] error_flag : Data to be checked. 
 * @return Nothing.
 * @note None.
 */
void esp8684_error_check( err_t error_flag );

/**
 * @brief ESP8684 send message function.
 * @details This function is used to send messages to the host.
 * @param[in] link_id : Host link id. 
 * @param[in] message : Message to be sent. 
 * @return Nothing.
 * @note None.
 */
void esp8684_send_message ( uint8_t *link_id, uint8_t *message );

/**
 * @brief ESP8684 connect device to the network.
 * @details This function is used to connect device to network.
 * @return Nothing.
 * @note None.
 */
void esp8684_con_device_to_network ( void );

/**
 * @brief ESP8684 send message to the host.
 * @details This function is used to send messages to the host.
 * @return Nothing.
 * @note None.
 */
void esp8684_send_data ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    esp8684_cfg_t esp8684_cfg;  /**< Click config object. */

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
    esp8684_cfg_setup( &esp8684_cfg );
    ESP8684_MAP_MIKROBUS( esp8684_cfg, MIKROBUS_1 );
    if ( UART_ERROR == esp8684_init( &esp8684, &esp8684_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    esp8684_default_cfg( &esp8684 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    esp8684_process( );
    esp8684_clear_app_buf( );
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_AT, NULL );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_RST, NULL );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_READY );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    esp8684_process( );
    esp8684_clear_app_buf();
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_GMR, NULL );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // Communication initialization
    esp8684_con_device_to_network ( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, "Sending and reading data from the TCP/UDP server \r\n" );
    esp8684_send_data( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

void esp8684_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

void esp8684_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    esp8684_clear_app_buf(  );
}

err_t esp8684_process ( void )
{
    err_t return_flag = ESP8684_ERROR;
    int32_t rx_size;
    uint8_t rx_buff[ ESP8684_RX_DRV_BUFFER_SIZE ] = { 0 };
    
    rx_size = esp8684_generic_read( &esp8684, rx_buff, ESP8684_RX_DRV_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = ESP8684_OK;

        if ( app_buf_len + rx_size >= ESP8684_RX_DRV_BUFFER_SIZE )
        {
            esp8684_clear_app_buf( );
            return_flag = ESP8684_OVERFLOW;
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
                buf_cnt--;
                app_buf_len--;
            }
        }
    } 

    return return_flag;
}

err_t esp8684_rsp_check ( uint8_t *response )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 50000;
    err_t error_flag = esp8684_process( );
    if ( ( error_flag != ESP8684_OK ) && ( error_flag != ESP8684_ERROR ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, response ) == 0 ) && ( strstr( app_buf, ESP8684_RSP_ERROR ) == 0 ) )
    {
        error_flag = esp8684_process( );
        if ( ( error_flag != ESP8684_OK ) && ( error_flag != ESP8684_ERROR ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        
        if ( timeout_cnt > timeout )
        {
            esp8684_clear_app_buf( );
            return ESP8684_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    esp8684_log_app_buf();
    
    return ESP8684_OK;
}

void esp8684_error_check( err_t error_flag )
{
    if ( ( ESP8684_OK != error_flag ) && ( error_flag != ESP8684_ERROR ) )
    {
        switch ( error_flag )
        {
            case ( ESP8684_OVERFLOW ):
                log_error( &logger, " Overflow!" );
                break;
            case ( ESP8684_TIMEOUT ):
                log_error( &logger, " Timeout!" );
                break;
            default:
                break;
        }
    }
    log_printf( &logger, "\r\n-----------------------------------\r\n" );
}

void esp8684_send_message ( uint8_t *link_id, uint8_t *message )
{
    uint8_t cmd_buf[ 100 ] = { 0 };
    uint8_t message_len_buf[ 5 ] = { 0 };
    uint16_t message_len = strlen( message );
    
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );
    strcpy( cmd_buf, link_id );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    esp8684_send_cmd( &esp8684, ESP8684_CMD_CIPSEND, cmd_buf );
    
    if ( ESP8684_OK == esp8684_rsp_check( ESP8684_READY_FOR_SEND ) )
    {
        esp8684_generic_write( &esp8684, message, strlen(message) ); 
        esp8684_generic_write( &esp8684, "\032", 1 ); 
    }
}

void esp8684_con_device_to_network ( void )
{
    esp8684_send_cmd( &esp8684, ESP8684_CMD_CWMODE, "1" );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_connect_to_network( &esp8684, ESP8684_SSID, ESP8684_PASSWORD );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_CIPMUX, "1" );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_CIPRECVMODE, "0" );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_send_query_cmd( &esp8684, ESP8684_CMD_CIPSTATE );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
}

void esp8684_send_data ( void )
{
    esp8684_connect_for_trans( &esp8684, "TCP", TCP_LINK_ID, REMOTE_IP, REMOTE_PORT );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_connect_for_trans( &esp8684, "UDP", UDP_LINK_ID, REMOTE_IP, REMOTE_PORT );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_send_message( TCP_LINK_ID, ESP8684_DATA );
    Delay_ms ( 500 );
    
    log_printf( &logger, "Read data TCP: \r\n" );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_RECEIVE );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 1000 );
    
    esp8684_send_message( UDP_LINK_ID, ESP8684_DATA );
    Delay_ms ( 500 );
    
    log_printf( &logger, "Read data UDP: \r\n" );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_RECEIVE );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_CIPCLOSE, TCP_LINK_ID );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_CIPCLOSE, UDP_LINK_ID );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
}

// ------------------------------------------------------------------------ END
