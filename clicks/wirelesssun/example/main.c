/*!
 * @file main.c
 * @brief Wireless SUN Click Example.
 *
 * # Description
 * This example demonstrates the use of Wireless SUN click board by showing
 * the communication between the two click boards configured as BORDER and ROUTER.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the click board by performing a hardware reset
 * and a clear parameters feature, and setting the device network name, device role to
 * BORDER or ROUTER depending on the application mode. In the end, it saves settings and
 * reboots device.
 *
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data and parses
 * the received TCP/UDP messages (BORDER mode) or waits for the connection, reads the parent
 * global address, and then starts sending a desired TCP/UDP messages to the parent every
 * 3 seconds (ROUTER mode).
 *
 * ## Additional Function
 * - static void wirelesssun_clear_app_buf ( void )
 * - static err_t wirelesssun_process ( void )
 * - static err_t wirelesssun_rsp_check ( void )
 * - static void wirelesssun_wait_for_connection ( void )
 * - static void wirelesssun_get_parent_gbl_address ( uint8_t *gbl_addr )
 *
 * @note
 * By default, the BORDER application mode is selected. comment out the DEMO_APP_BORDER macro
 * definition in order to switch the application mode to ROUTER.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "wirelesssun.h"
#include "conversions.h"

// Comment out the line below in order to switch the application mode to ROUTER
#define DEMO_APP_BORDER

// Device network name.
#define DEVICE_NETWORK_NAME         "\"Wireless SUN click\""

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MikroE - Wireless SUN click board"

#define PROCESS_BUFFER_SIZE         600

static wirelesssun_t wirelesssun;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief Wireless SUN clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @return None.
 * @note None.
 */
static void wirelesssun_clear_app_buf ( void );

/**
 * @brief Wireless SUN data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wirelesssun_process ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wirelesssun_rsp_check ( void );

/**
 * @brief Wireless SUN wait for connection function.
 * @details This function waits for the ROUTER connection - FAN join state 5(OPERATIONAL).
 * @return None.
 * @note None.
 */
static void wirelesssun_wait_for_connection ( void );

/**
 * @brief Wireless SUN get parent gbl address function.
 * @details This function reads the parent global address after the ROUTER connects to the BORDER.
 * @return None.
 * @note None.
 */
static void wirelesssun_get_parent_gbl_address ( uint8_t *gbl_addr );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wirelesssun_cfg_t wirelesssun_cfg;  /**< Click config object. */

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
    wirelesssun_cfg_setup( &wirelesssun_cfg );
    WIRELESSSUN_MAP_MIKROBUS( wirelesssun_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wirelesssun_init( &wirelesssun, &wirelesssun_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    log_printf( &logger, "\r\n - Reset device -\r\n" );
    wirelesssun_reset_device ( &wirelesssun );
    wirelesssun_rsp_check ( );
    
    log_printf( &logger, "\r\n - Clear parameters and reboot device -\r\n" );
    wirelesssun_send_cmd ( &wirelesssun, WIRELESSSUN_CMD_CLRST );
    wirelesssun_rsp_check ( );
    
    log_printf( &logger, "\r\n - Set device name -\r\n" );
    wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_NETNAME, DEVICE_NETWORK_NAME );
    wirelesssun_rsp_check ( );
    
    log_printf( &logger, "\r\n - Set device starting role -\r\n" );
#ifdef DEMO_APP_BORDER
    wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_ATSTART, WIRELESSSUN_DEVICE_ROLE_BORDER );
#else
    wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_ATSTART, WIRELESSSUN_DEVICE_ROLE_ROUTER );
#endif
    wirelesssun_rsp_check ( );
    
    log_printf( &logger, "\r\n - Save settings and reboot device -\r\n" );
    wirelesssun_send_cmd ( &wirelesssun, WIRELESSSUN_CMD_SVRST );
    wirelesssun_rsp_check ( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_BORDER
    wirelesssun_process( );
    if ( strstr( app_buf, WIRELESSSUN_CMD_PROMPT_SIGN ) )
    {
        uint8_t demo_hex_msg[ 100 ] = { 0 };
        uint8_t demo_text_msg[ 50 ] = { 0 };
        char * __generic_ptr start_msg_ptr = NULL;
        char * __generic_ptr end_msg_ptr = NULL;
        uint8_t msg_len = 0;
        uint8_t msg_cnt = 0;
        if ( ( strstr( app_buf, WIRELESSSUN_RSP_TCPR ) ) || ( strstr( app_buf, WIRELESSSUN_RSP_UDPR ) ) )
        {
            if ( strstr( app_buf, WIRELESSSUN_RSP_TCPR ) )
            {
                start_msg_ptr = strstr( app_buf, WIRELESSSUN_RSP_TCPR );
            }
            else
            {
                start_msg_ptr = strstr( app_buf, WIRELESSSUN_RSP_UDPR );
            }
            start_msg_ptr = strstr ( start_msg_ptr, ">" ) + 2;
            end_msg_ptr = strstr( start_msg_ptr, WIRELESSSUN_CMD_PROMPT_SIGN );
            msg_len = ( end_msg_ptr - start_msg_ptr );
            memcpy ( demo_hex_msg, start_msg_ptr, msg_len );
            for ( msg_cnt = 0; msg_cnt < msg_len; msg_cnt += 2 )
            {
                demo_text_msg[ msg_cnt / 2 ] = hex_to_uint8 ( &demo_hex_msg [ msg_cnt ] );
            }
            if ( strstr( app_buf, WIRELESSSUN_RSP_TCPR ) )
            {
                log_printf( &logger, "\r\n - Received TCP message: \"%s\" -\r\n", demo_text_msg );
            }
            else
            {
                log_printf( &logger, "\r\n - Received UDP message: \"%s\" -\r\n", demo_text_msg );
            }
        }
        wirelesssun_clear_app_buf( );
    }
#else
    wirelesssun_wait_for_connection ( );
    uint8_t gbl_address[ 20 ] = { 0 };
    wirelesssun_get_parent_gbl_address ( gbl_address );
    for ( ; ; )
    {
        uint8_t tcp_udp_params[ 120 ] = { 0 };
        uint8_t demo_hex_msg[ 100 ] = { 0 };
        uint8_t demo_text_msg[ 50 ] = { 0 };
        uint8_t msg_cnt = 0;
        strcpy ( demo_text_msg, DEMO_TEXT_MESSAGE );
        strcpy ( tcp_udp_params, gbl_address );
        strcat ( tcp_udp_params, WIRELESSSUN_CMD_DELIMITER );
        strcat ( tcp_udp_params, WIRELESSSUN_DEFAULT_PORT );
        strcat ( tcp_udp_params, WIRELESSSUN_CMD_DELIMITER );
        for ( msg_cnt = 0; msg_cnt < strlen ( demo_text_msg ); msg_cnt++ )
        {
            uint8_to_hex ( demo_text_msg[ msg_cnt ], &demo_hex_msg[ msg_cnt * 2 ] );
        }
        strcat ( tcp_udp_params, demo_hex_msg );
        log_printf( &logger, "\r\n - Sending \"%s\" message via TCP -\r\n", demo_text_msg );
        wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_TCPS, tcp_udp_params );
        wirelesssun_rsp_check ( );
        Delay_ms ( 3000 );
        
        log_printf( &logger, "\r\n - Sending \"%s\" message via UDP -\r\n", demo_text_msg );
        wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_UDPS, tcp_udp_params );
        wirelesssun_rsp_check ( );
        Delay_ms ( 3000 );
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

static void wirelesssun_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t wirelesssun_process ( void ) 
{
    int32_t rx_size;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = wirelesssun_generic_read( &wirelesssun, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            wirelesssun_clear_app_buf(  );
            log_error( &logger, " Overflow!" );
            return WIRELESSSUN_ERROR;
        } 
        else 
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buf[ rx_cnt ];
                log_printf( &logger, "%c", rx_buf[ rx_cnt ] );
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        return WIRELESSSUN_OK;
    }
    return WIRELESSSUN_ERROR;
}

static err_t wirelesssun_rsp_check ( void )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    wirelesssun_clear_app_buf( );
    wirelesssun_process( );
    while ( 0 == strstr( app_buf, WIRELESSSUN_CMD_PROMPT_SIGN ) )
    {
        wirelesssun_process( );
        if ( timeout_cnt++ >= timeout )
        {
            wirelesssun_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return WIRELESSSUN_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    log_printf( &logger, "\r\n" );     
    return WIRELESSSUN_OK;
}

static void wirelesssun_wait_for_connection ( void )
{
    #define FSTAT_OPERATIONAL "fstat 5(OPERATIONAL)"
    #define FMNG_JOIN_STATE_5 "FMng: changed fan join state (4 -> 5)"
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 60000;
    for ( ; ; ) 
    {
        wirelesssun_process( );
        if ( timeout_cnt++ >= timeout )
        {
            wirelesssun_send_cmd ( &wirelesssun, WIRELESSSUN_CMD_FSTAT );
            wirelesssun_rsp_check ( );
            timeout_cnt = 0;
        }
        Delay_ms( 1 );
        if ( ( strstr( app_buf, FMNG_JOIN_STATE_5 ) ) || 
             ( strstr( app_buf, FSTAT_OPERATIONAL ) ) )
        {
            wirelesssun_clear_app_buf( );
            return;
        }
        if ( strstr( app_buf, WIRELESSSUN_CMD_PROMPT_SIGN ) )
        {
            wirelesssun_clear_app_buf( );
        }
    } 
}

static void wirelesssun_get_parent_gbl_address ( uint8_t *gbl_addr )
{
    #define GBL_ADDRESS_START   "GBL<"
    #define GBL_ADDRESS_END     ">"
    for ( ; ; )
    {
        uint16_t timeout_cnt = 0;
        uint16_t timeout = 10000;
        wirelesssun_send_cmd ( &wirelesssun, WIRELESSSUN_CMD_RPLINF );
        wirelesssun_rsp_check ( );
        for ( ; ; )
        {
            wirelesssun_process( );
            if ( strstr( app_buf, WIRELESSSUN_CMD_PROMPT_SIGN ) )
            {
                char * __generic_ptr start_gbl_ptr = strstr( app_buf, GBL_ADDRESS_START );
                if ( start_gbl_ptr )
                {
                    start_gbl_ptr += 4;
                    Delay_ms( 100 );
                    wirelesssun_process( );
                    char * __generic_ptr end_gbl_ptr = strstr( start_gbl_ptr, GBL_ADDRESS_END );
                    memcpy ( gbl_addr, start_gbl_ptr, end_gbl_ptr - start_gbl_ptr );
                    wirelesssun_clear_app_buf( );
                    return;
                }
                wirelesssun_clear_app_buf( );
            }
            if ( timeout_cnt++ > timeout )
            {
                break;
            }
            Delay_ms( 1 );
        }
    }
}

// ------------------------------------------------------------------------ END
