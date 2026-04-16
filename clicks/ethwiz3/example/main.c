/*!
 * @file main.c
 * @brief ETH WIZ 3 Click example
 *
 * # Description
 * This example demonstrates the use of the ETH WIZ 3 Click board in TCP client
 * mode using the module AT command interface. The device is configured to use
 * DHCP, connect to a remote TCP echo server, and periodically send a predefined
 * message. When the TCP connection is active, the application transmits the
 * message and displays the received echo response on the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and ETH WIZ 3 Click driver, resets the device to AT
 * mode, reads and displays basic device information (MAC address, firmware
 * version, product name), configures the TCP client parameters (DHCP, remote
 * host IP/port), saves settings, and reboots the device to data mode.
 *
 * ## Application Task
 * Monitors the TCP connection status pin and reports changes. When the
 * connection is active, the application sends the predefined message to the
 * remote server and prints the received response.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ethwiz3.h"

#ifndef MIKROBUS_POSITION_ETHWIZ3
    #define MIKROBUS_POSITION_ETHWIZ3 MIKROBUS_1
#endif

// Message content
#define MESSAGE_CONTENT     "ETH WIZ 3 Click board - demo example."

// TCP server parameters
#define REMOTE_IP           "54.187.244.144"    // TCP echo server IP address
#define REMOTE_PORT         "51111"             // TCP echo server port

static ethwiz3_t ethwiz3;
static log_t logger;

static uint8_t app_buf[ 200 ] = { 0 };
static uint16_t app_buf_len = 0;

/**
 * @brief ETH WIZ 3 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void ethwiz3_clear_app_buf ( void );

/**
 * @brief ETH WIZ 3 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void ethwiz3_log_app_buf ( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ethwiz3_cfg_t ethwiz3_cfg;  /**< Click config object. */

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
    ethwiz3_cfg_setup( &ethwiz3_cfg );
    ETHWIZ3_MAP_MIKROBUS( ethwiz3_cfg, MIKROBUS_POSITION_ETHWIZ3 );
    if ( ETHWIZ3_OK != ethwiz3_init( &ethwiz3, &ethwiz3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    ethwiz3_clear_app_buf ( );

    log_printf( &logger, ">>> Reset Device to AT Mode <<<\r\n" );
    ethwiz3_set_at_mode ( &ethwiz3 );
    ethwiz3_reset_device ( &ethwiz3 );
    if ( ETHWIZ3_OK == ethwiz3_data_read ( &ethwiz3, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }

    log_printf( &logger, ">>> Get MAC Address <<<\r\n" );
    if ( ETHWIZ3_OK == ethwiz3_cmd_get ( &ethwiz3, ETHWIZ3_CMD_MAC_ADDRESS, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }

    log_printf( &logger, ">>> Query Firmware Version <<<\r\n" );
    if ( ETHWIZ3_OK == ethwiz3_cmd_get ( &ethwiz3, ETHWIZ3_CMD_FIRMWARE_VERSION, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }

    log_printf( &logger, ">>> Get Product Name <<<\r\n" );
    if ( ETHWIZ3_OK == ethwiz3_cmd_get ( &ethwiz3, ETHWIZ3_CMD_PRODUCT_NAME, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }

    log_printf( &logger, ">>> Set Network Operation Mode to TCP Client <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_NETWORK_OPERATION_MODE, ETHWIZ3_OP_MODE_TCP_CLIENT );

    log_printf( &logger, ">>> Set IP Address Allocation Method to DHCP <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_IP_ADDRESS_METHOD, ETHWIZ3_IM_DHCP );

    log_printf( &logger, ">>> Set Remote Host IP Address <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_REMOTE_IP, REMOTE_IP );

    log_printf( &logger, ">>> Set Remote Host Port Number <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_REMOTE_PORT, REMOTE_PORT );

    log_printf( &logger, ">>> Save Settings <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_SAVE_SETTINGS, NULL );

    log_printf( &logger, ">>> Reboot Device to Data Mode <<<\r\n" );
    ethwiz3_cmd_set ( &ethwiz3, ETHWIZ3_CMD_DEVICE_REBOOT, NULL );
    if ( ETHWIZ3_OK == ethwiz3_data_read ( &ethwiz3, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
    {
        ethwiz3_log_app_buf ( );
        ethwiz3_clear_app_buf ( );
    }
    ethwiz3_set_data_mode ( &ethwiz3 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t tcp_active = 0;
    uint8_t tcp_pin = ethwiz3_get_tcp_pin ( &ethwiz3 );
    if ( tcp_pin != tcp_active )
    {
        tcp_active = tcp_pin;
        log_printf( &logger, ">>> TCP Connection state: %s <<<\r\n", ( char * ) ( tcp_active ? "Active" : "Idle" ) );
        log_printf( &logger, "\r\n-----------------------------\r\n" );
    }
    if ( tcp_active )
    {
        log_printf( &logger, ">>> Write Message: " );
        if ( ETHWIZ3_OK == ethwiz3_data_write ( &ethwiz3, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) ) )
        {
            log_printf( &logger, "OK\r\n" );
            log_printf( &logger, "<<< Response: " );
            if ( ETHWIZ3_OK == ethwiz3_data_read ( &ethwiz3, app_buf, &app_buf_len, sizeof ( app_buf ) ) )
            {
                ethwiz3_log_app_buf ( );
                ethwiz3_clear_app_buf ( );
            }
            log_printf( &logger, "\r\n" );
        }
        else
        {
            log_printf( &logger, "NOK\r\n" );
        }
    }
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

static void ethwiz3_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ethwiz3_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    if ( app_buf_len )
    {
        log_printf( &logger, "\r\n-----------------------------\r\n" );
    }
}

// ------------------------------------------------------------------------ END
