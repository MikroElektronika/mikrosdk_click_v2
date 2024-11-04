/*!
 * @file main.c
 * @brief Thyone-I Click Example.
 *
 * # Description
 * This example demonstrates the use of the Thyone-I Click board by sending and receiving data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration and setting the MAC addresses and mode.
 *
 * ## Application Task
 * Transmitter mode - Sending data to the devices within range ( thyonei_broadcast_data_req ), with same MAC group ( thyonei_multicast_data_req )
 * and with the selected MAC destination address ( thyonei_unicast_data_req ).
 * Receiver mode - Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static err_t thyonei_get_resp ( thyonei_t *ctx, uint8_t response )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "thyonei.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

/**
 * @brief Thyone-I MAC addresses.
 * @details Specified setting for MAC addresses of Thyone-I Click driver.
 */
#define TRANSMITTER_MAC_ADDRESS     0x6C000001ul
#define RECEIVER_MAC_ADDRESS        0x6C000002ul
#define MAC_GROUP_ADDRESS           0xAA

#define SOURCE_ADDRESS              TRANSMITTER_MAC_ADDRESS /* Change the value of this macro to change 
                                                               between transmitter and receiver mode */
#if ( TRANSMITTER_MAC_ADDRESS == SOURCE_ADDRESS )
    #define DESTINATION_ADDRESS     RECEIVER_MAC_ADDRESS
#else
    #define DESTINATION_ADDRESS     TRANSMITTER_MAC_ADDRESS
#endif

/**
 * @brief Thyone-I Message.
 * @details Specified message to be sent to receivers of Thyone-I Click driver.
 */
#define MESSAGE                     "Thyone-I Click Ecample "

static thyonei_t thyonei;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Thyone-I get response function.
 * @details This function is used to get response or received data from the device. 
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.]
 * @param[in] response : Sent command expected response.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t thyonei_get_resp ( thyonei_t *ctx, uint8_t response );

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    thyonei_cfg_t thyonei_cfg;  /**< Click config object. */

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
    thyonei_cfg_setup( &thyonei_cfg );
    THYONEI_MAP_MIKROBUS( thyonei_cfg, MIKROBUS_1 );
    if ( UART_ERROR == thyonei_init( &thyonei, &thyonei_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    thyonei_default_cfg ( &thyonei );

    thyonei_generic_read( &thyonei, app_buf, PROCESS_BUFFER_SIZE );

    uint8_t tmp_data [ 4 ] = { 0 };
    uint8_t len = 0;

    thyonei_get_req( &thyonei, THYONEI_INDEX_SERIAL_NUMBER, &len, tmp_data );
    log_printf( &logger, " Thyone-I serial number: 0x" );
    for( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        log_printf( &logger, "%.2X", ( uint16_t ) tmp_data[ cnt ] );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "= = = = = = = = = = = = = = =\r\n" );

    log_printf( &logger, " Thyone-I factory reset request: \r\n" );
    thyonei_send_command( &thyonei, THYONEI_CMD_FACTORY_RESET_REQ, 0, NULL );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_FACTORY_RESET_REQ );

    log_printf( &logger, " Thyone-I Set Mode to normal mode: \r\n" );
    tmp_data[ 0 ] = 0;
    thyonei_set_req( &thyonei, THYONEI_INDEX_MODULE_MODE, 1, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_printf( &logger, " Thyone-I Set RF-Profile to 0: \r\n" );
    tmp_data[ 0 ] = 0;
    thyonei_set_req( &thyonei, THYONEI_INDEX_RF_PROFILE, 1, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_printf( &logger, " Thyone-I Set MAC Group ID to 0xAA: \r\n" );
    tmp_data[ 0 ] = MAC_GROUP_ADDRESS;
    thyonei_set_req( &thyonei, THYONEI_INDEX_MAC_GROUP_ID, 1, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_printf( &logger, " Thyone-I Set Source MAC address: \r\n" );
    tmp_data[ 0 ] = ( uint8_t ) SOURCE_ADDRESS;
    tmp_data[ 1 ] = ( uint8_t ) ( SOURCE_ADDRESS >> 8 );
    tmp_data[ 2 ] = ( uint8_t ) ( SOURCE_ADDRESS >> 16 );
    tmp_data[ 3 ] = ( uint8_t ) ( SOURCE_ADDRESS >> 24 );
    thyonei_set_req( &thyonei, THYONEI_INDEX_MAC_SOURCE_ADDRESS, 4, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_printf( &logger, " Thyone-I Set Destination MAC address: \r\n" );
    tmp_data[ 0 ] = ( uint8_t ) DESTINATION_ADDRESS;
    tmp_data[ 1 ] = ( uint8_t ) ( DESTINATION_ADDRESS >> 8 );
    tmp_data[ 2 ] = ( uint8_t ) ( DESTINATION_ADDRESS >> 16 );
    tmp_data[ 3 ] = ( uint8_t ) ( DESTINATION_ADDRESS >> 24 );
    thyonei_set_req( &thyonei, THYONEI_INDEX_MAC_DEST_ADDRESS, 4, tmp_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_SET_REQ );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ( TRANSMITTER_MAC_ADDRESS == SOURCE_ADDRESS )
    uint8_t message_data[ PROCESS_BUFFER_SIZE ] = { 0 };

    #define BROADCAST_MESSAGE       "Broadcast"
    strcpy( message_data, MESSAGE );
    strcat( message_data, BROADCAST_MESSAGE );
    log_printf( &logger, " Thyone-I sending broadcast message: \r\n" );
    thyonei_broadcast_data_req( &thyonei, strlen( message_data ), message_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_DATA_CNF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    #define MULTICAST_MESSAGE       "Multicast"
    strcpy( message_data, MESSAGE );
    strcat( message_data, MULTICAST_MESSAGE );
    log_printf( &logger, " Thyone-I sending multicast message: \r\n" );
    thyonei_multicast_data_req( &thyonei, strlen( message_data ), message_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_DATA_CNF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    #define UNICAST_MESSAGE         "Unicast"
    strcpy( message_data, MESSAGE );
    strcat( message_data, UNICAST_MESSAGE );
    log_printf( &logger, " Thyone-I sending unicast message: \r\n" );
    thyonei_unicast_data_req( &thyonei, strlen( message_data ), message_data );
    thyonei_get_resp ( &thyonei, THYONEI_CMD_DATA_CNF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    thyonei_get_resp ( &thyonei, THYONEI_CMD_DATA_IND );
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

static err_t thyonei_get_resp ( thyonei_t *ctx, uint8_t response )
{
    err_t error_flag = THYONEI_OK;
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    
    Delay_ms ( 1000 );
    rx_size = thyonei_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 )
    {    
        if ( ( response | THYONEI_RESPONSE_CODE ) == rx_buf[ 1 ] )
        {
            if ( 0 == rx_buf[ 4 ] )
            {
                log_printf( &logger, " Response OK \r\n" );
                error_flag = THYONEI_OK;
            }
            else 
            {
                log_printf( &logger, " Response ERROR: 0x%.2X \r\n", ( uint16_t ) rx_buf[ 4 ] );
                error_flag = THYONEI_ERROR;
            }
        }
        else if ( ( THYONEI_CMD_DATA_IND == rx_buf[ 1 ] ) && ( THYONEI_CMD_DATA_IND == response ) )
        {
            uint8_t data_len = rx_buf[ 2 ]; 
            log_printf( &logger, " Data received: \r\n" );
            for ( uint8_t n_cnt = 0; n_cnt < ( data_len - 5 ); n_cnt++ )
            {
                log_printf( &logger, "%c", rx_buf[ 9 + n_cnt ] );
            }
            log_printf( &logger, "\r\n" );
        }
        else 
        {
            log_printf( &logger, "Error \r\n" );
            error_flag = THYONEI_ERROR;
        }
        log_printf( &logger, "= = = = = = = = = = = = = = =\r\n" );
        return error_flag;
    }
    
}
// ------------------------------------------------------------------------ END
