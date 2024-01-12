/*!
 * @file main.c
 * @brief NeoMesh 868MHz Click Example.
 *
 * # Description
 * This example demonstrates the use of NeoMesh 868MHz click board by showing
 * the communication between the two click boards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the click board for the selected
 * application mode.
 *
 * ## Application Task
 * One click board should be set to originator mode and the others to receiver 1 or 2.
 * If the SINGLE_RECEIVER_MODE is enabled, the originator device sends a desired message
 * to RECEIVER_1 node and waits for an acknowledge response, otherwise it sends the same
 * message to both RECEIVER_1 and RECEIVER_2 nodes. The receiver devices reads and parses
 * all incoming AAPI frames and displays them on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "neomesh868mhz.h"

// Comment out the line below to add the APP_RECEIVER_2 to the APP_ORIGINATOR example.
#define SINGLE_RECEIVER_MODE

// Demo aplication selection macros
#define APP_ORIGINATOR              0
#define APP_RECEIVER_1              1
#define APP_RECEIVER_2              2
#define DEMO_APP                    APP_ORIGINATOR

// Text message to send in the originator mode
#define DEMO_TEXT_MESSAGE           "MIKROE-NeoMesh"
#define DEFAULT_PORT                0

// Node ID macros
#define NODE_ID_ORIGINATOR          0x0100u
#define NODE_ID_RECEIVER_1          0x0020u
#define NODE_ID_RECEIVER_2          0x0021u

static neomesh868mhz_t neomesh868mhz;
static log_t logger;
static neomesh868mhz_aapi_frame_t aapi_frame;
static neomesh868mhz_sapi_frame_t sapi_frame;

/**
 * @brief NeoMesh 868MHz parse aapi rsp function.
 * @details This function reads and parses AAPI responses until an expected response is received.
 * @param[in] exp_rsp : Expected AAPI response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error, no expected response is received,
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t neomesh868mhz_parse_aapi_rsp ( uint8_t exp_rsp );

/**
 * @brief NeoMesh 868MHz parse sapi rsp function.
 * @details This function reads and parses SAPI responses until an expected response is received.
 * @param[in] exp_rsp : Expected SAPI response.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error, no expected response is received,
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t neomesh868mhz_parse_sapi_rsp ( uint16_t exp_rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    neomesh868mhz_cfg_t neomesh868mhz_cfg;  /**< Click config object. */

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
    neomesh868mhz_cfg_setup( &neomesh868mhz_cfg );
    NEOMESH868MHZ_MAP_MIKROBUS( neomesh868mhz_cfg, MIKROBUS_1 );
    if ( UART_ERROR == neomesh868mhz_init( &neomesh868mhz, &neomesh868mhz_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "\r\n Enable SAPI over AAPI\r\n" );
    aapi_frame.cmd = NEOMESH868MHZ_CMD_SAPI_TO_AAPI;
    aapi_frame.len = 0;
    neomesh868mhz_send_aapi_frame ( &neomesh868mhz, &aapi_frame );
    neomesh868mhz_parse_sapi_rsp ( NEOMESH868MHZ_SAPI_RSP_BOOTLOADER_START );
    
    log_printf( &logger, "\r\n Login with password\r\n" );
    sapi_frame.cmd = NEOMESH868MHZ_SAPI_CMD_LOGIN;
    sapi_frame.len = 5;
    sapi_frame.payload[ 0 ] = NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_0;
    sapi_frame.payload[ 1 ] = NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_1;
    sapi_frame.payload[ 2 ] = NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_2;
    sapi_frame.payload[ 3 ] = NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_3;
    sapi_frame.payload[ 4 ] = NEOMESH868MHZ_SAPI_LOGIN_PASSWORD_4;
    neomesh868mhz_send_sapi_frame ( &neomesh868mhz, &sapi_frame );
    neomesh868mhz_parse_sapi_rsp ( NEOMESH868MHZ_SAPI_RSP_OK );
    
    log_printf( &logger, "\r\n Set NODE ID to: " );
    sapi_frame.cmd = NEOMESH868MHZ_SAPI_CMD_SET_SETTING;
    sapi_frame.len = 3;
    sapi_frame.payload[ 0 ] = NEOMESH868MHZ_SAPI_SETTINGS_ID_NODE_ID;
#if ( DEMO_APP == APP_RECEIVER_1 )
    log_printf( &logger, "%.4X\r\n", ( uint16_t ) NODE_ID_RECEIVER_1 );
    sapi_frame.payload[ 1 ] = ( uint8_t ) ( ( NODE_ID_RECEIVER_1 >> 8 ) & 0xFF );
    sapi_frame.payload[ 2 ] = ( uint8_t ) ( NODE_ID_RECEIVER_1 & 0xFF );
#elif ( DEMO_APP == APP_RECEIVER_2 )
    log_printf( &logger, "%.4X\r\n", ( uint16_t ) NODE_ID_RECEIVER_2 );
    sapi_frame.payload[ 1 ] = ( uint8_t ) ( ( NODE_ID_RECEIVER_2 >> 8 ) & 0xFF );
    sapi_frame.payload[ 2 ] = ( uint8_t ) ( NODE_ID_RECEIVER_2 & 0xFF );
#elif ( DEMO_APP == APP_ORIGINATOR )
    log_printf( &logger, "%.4X\r\n", ( uint16_t ) NODE_ID_ORIGINATOR );
    sapi_frame.payload[ 1 ] = ( uint8_t ) ( ( NODE_ID_ORIGINATOR >> 8 ) & 0xFF );
    sapi_frame.payload[ 2 ] = ( uint8_t ) ( NODE_ID_ORIGINATOR & 0xFF );
#endif
    neomesh868mhz_send_sapi_frame ( &neomesh868mhz, &sapi_frame );
    neomesh868mhz_parse_sapi_rsp ( NEOMESH868MHZ_SAPI_RSP_OK );
    
    log_printf( &logger, "\r\n Commit settings\r\n" );
    sapi_frame.cmd = NEOMESH868MHZ_SAPI_CMD_COMMIT_SETTINGS;
    sapi_frame.len = 0;
    neomesh868mhz_send_sapi_frame ( &neomesh868mhz, &sapi_frame );
    neomesh868mhz_parse_sapi_rsp ( NEOMESH868MHZ_SAPI_RSP_OK );
    
    log_printf( &logger, "\r\n Start protocol stack\r\n" );
    sapi_frame.cmd = NEOMESH868MHZ_SAPI_CMD_START_PROTOCOL_STACK;
    sapi_frame.len = 0;
    neomesh868mhz_send_sapi_frame ( &neomesh868mhz, &sapi_frame );
    neomesh868mhz_parse_sapi_rsp ( NEOMESH868MHZ_SAPI_RSP_PROTOCOL_STACK_START );
    // Wait for the device to actually switch back to application layer
    while ( !neomesh868mhz_get_cts_pin ( &neomesh868mhz ) );
    
    log_printf( &logger, "\r\n Get NODE info\r\n" );
    aapi_frame.cmd = NEOMESH868MHZ_CMD_NODE_INFO;
    aapi_frame.len = 0;
    neomesh868mhz_send_aapi_frame ( &neomesh868mhz, &aapi_frame );
    neomesh868mhz_parse_aapi_rsp ( NEOMESH868MHZ_RSP_NODE_INFO );
    
    log_printf( &logger, "\r\n Get neighbour list\r\n" );
    aapi_frame.cmd = NEOMESH868MHZ_CMD_NEIGHBOUR_LIST;
    aapi_frame.len = 0;
    neomesh868mhz_send_aapi_frame ( &neomesh868mhz, &aapi_frame );
    neomesh868mhz_parse_aapi_rsp ( NEOMESH868MHZ_RSP_NEIGHBOUR_LIST );
    
#if ( DEMO_APP == APP_RECEIVER_1 )
    log_printf( &logger, "\r\n Application Mode: Receiver 1\r\n" );
#elif ( DEMO_APP == APP_RECEIVER_2 )
    log_printf( &logger, "\r\n Application Mode: Receiver 2\r\n" );
#elif ( DEMO_APP == APP_ORIGINATOR )
    log_printf( &logger, "\r\n Application Mode: Originator\r\n" );
#else
    #error "Selected application mode is not supported!"
#endif
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ( DEMO_APP == APP_ORIGINATOR )
    log_printf( &logger, "\r\n Send message to node: %.4X\r\n", ( uint16_t ) NODE_ID_RECEIVER_1 );
    aapi_frame.cmd = NEOMESH868MHZ_CMD_ACK_SEND;
    aapi_frame.len = 3 + strlen ( DEMO_TEXT_MESSAGE );
    aapi_frame.payload[ 0 ] = ( uint8_t ) ( ( NODE_ID_RECEIVER_1 >> 8 ) & 0xFF );
    aapi_frame.payload[ 1 ] = ( uint8_t ) ( NODE_ID_RECEIVER_1 & 0xFF );
    aapi_frame.payload[ 2 ] = DEFAULT_PORT;
    strcpy ( &aapi_frame.payload[ 3 ], DEMO_TEXT_MESSAGE );
    if ( NEOMESH868MHZ_OK == neomesh868mhz_send_aapi_frame ( &neomesh868mhz, &aapi_frame ) )
    {
        neomesh868mhz_parse_aapi_rsp ( NEOMESH868MHZ_RSP_ACK );
    }
    #ifndef SINGLE_RECEIVER_MODE
        log_printf( &logger, "\r\n Send message to node: %.4X\r\n", ( uint16_t ) NODE_ID_RECEIVER_2 );
        aapi_frame.cmd = NEOMESH868MHZ_CMD_ACK_SEND;
        aapi_frame.len = 3 + strlen ( DEMO_TEXT_MESSAGE );
        aapi_frame.payload[ 0 ] = ( uint8_t ) ( ( NODE_ID_RECEIVER_2 >> 8 ) & 0xFF );
        aapi_frame.payload[ 1 ] = ( uint8_t ) ( NODE_ID_RECEIVER_2 & 0xFF );
        aapi_frame.payload[ 2 ] = DEFAULT_PORT;
        strcpy ( &aapi_frame.payload[ 3 ], DEMO_TEXT_MESSAGE );
        if ( NEOMESH868MHZ_OK == neomesh868mhz_send_aapi_frame ( &neomesh868mhz, &aapi_frame ) )
        {
            neomesh868mhz_parse_aapi_rsp ( NEOMESH868MHZ_RSP_ACK );
        }
    #endif
#else
   neomesh868mhz_parse_aapi_rsp ( NULL );
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

static err_t neomesh868mhz_parse_aapi_rsp ( uint8_t exp_rsp )
{
    while ( NEOMESH868MHZ_OK == neomesh868mhz_read_aapi_frame ( &neomesh868mhz, &aapi_frame ) )
    {
        switch ( aapi_frame.cmd )
        {
            case NEOMESH868MHZ_RSP_ACK:
            {
                log_printf( &logger, "---- ACK ----\r\n" );
                log_printf( &logger, " Originator ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                break;
            }
            case NEOMESH868MHZ_RSP_NACK:
            {
                log_printf( &logger, "---- NACK ----\r\n" );
                log_printf( &logger, " Originator ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                break;
            }
            case NEOMESH868MHZ_RSP_ACK_HOST:
            {
                log_printf( &logger, "---- ACK HOST DATA ----\r\n" );
                log_printf( &logger, " Originator ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                log_printf( &logger, " Packet Age: %.3f sec\r\n", 
                            ( ( ( uint16_t ) aapi_frame.payload[ 2 ] << 8 ) | 
                              aapi_frame.payload[ 3 ] ) * 0.125f );
                log_printf( &logger, " Port: %u\r\n", aapi_frame.payload[ 4 ] );
                log_printf( &logger, " Payload: " );
                for ( uint8_t cnt = 5; cnt < aapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) aapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                aapi_frame.payload[ aapi_frame.len ] = 0;
                log_printf( &logger, " Payload (string): %s\r\n\n", &aapi_frame.payload[ 5 ] );
                break;
            }
            case NEOMESH868MHZ_RSP_ACK_HOST_HAPA:
            {
                log_printf( &logger, "---- ACK HOST DATA HAPA ----\r\n" );
                log_printf( &logger, " Originator ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                log_printf( &logger, " Packet Age: %.3f sec\r\n", 
                            ( ( ( uint32_t ) aapi_frame.payload[ 2 ] << 24 ) | 
                              ( ( uint32_t ) aapi_frame.payload[ 3 ] << 16 ) |
                              ( ( uint16_t ) aapi_frame.payload[ 4 ] << 8 ) | 
                              aapi_frame.payload[ 5 ] ) * pow ( 2, -19 ) );
                log_printf( &logger, " Port: %u\r\n", aapi_frame.payload[ 6 ] );
                log_printf( &logger, " Payload: " );
                for ( uint8_t cnt = 7; cnt < aapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) aapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                break;
            }
            case NEOMESH868MHZ_RSP_NACK_HOST:
            {
                log_printf( &logger, "---- NACK HOST DATA ----\r\n" );
                log_printf( &logger, " Originator ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                log_printf( &logger, " Packet Age: %.3f sec\r\n", 
                            ( ( ( uint16_t ) aapi_frame.payload[ 2 ] << 8 ) | 
                              aapi_frame.payload[ 3 ] ) * 0.125f );
                log_printf( &logger, " Port: %u\r\n", aapi_frame.payload[ 4 ] );
                log_printf( &logger, " Sequence number: %u\r\n", 
                            ( ( ( uint16_t ) aapi_frame.payload[ 5 ] << 8 ) | 
                              aapi_frame.payload[ 6 ] ) & 0x0FFFu );
                log_printf( &logger, " Payload: " );
                for ( uint8_t cnt = 7; cnt < aapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) aapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                break;
            }
            case NEOMESH868MHZ_RSP_NACK_HOST_HAPA:
            {
                log_printf( &logger, "---- NACK HOST DATA HAPA ----\r\n" );
                log_printf( &logger, " Originator ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                log_printf( &logger, " Packet Age: %.3f sec\r\n", 
                            ( ( ( uint32_t ) aapi_frame.payload[ 2 ] << 24 ) | 
                              ( ( uint32_t ) aapi_frame.payload[ 3 ] << 16 ) |
                              ( ( uint16_t ) aapi_frame.payload[ 4 ] << 8 ) | 
                              aapi_frame.payload[ 5 ] ) * pow ( 2, -19 ) );
                log_printf( &logger, " Port: %u\r\n", aapi_frame.payload[ 6 ] );
                log_printf( &logger, " Sequence number: %u\r\n", 
                            ( ( ( uint16_t ) aapi_frame.payload[ 7 ] << 8 ) | 
                              aapi_frame.payload[ 8 ] ) & 0x0FFFu );
                log_printf( &logger, " Payload: " );
                for ( uint8_t cnt = 9; cnt < aapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) aapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                break;
            }
            case NEOMESH868MHZ_RSP_NACK_SEND:
            {
                log_printf( &logger, "---- NACK SEND ----\r\n" );
                log_printf( &logger, " Destination ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                log_printf( &logger, " Sequence number: %u\r\n", 
                            ( ( ( uint16_t ) aapi_frame.payload[ 2 ] << 8 ) | 
                              aapi_frame.payload[ 3 ] ) & 0x0FFFu );
                break;
            }
            case NEOMESH868MHZ_RSP_NACK_DROP:
            {
                log_printf( &logger, "---- NACK DROP ----\r\n" );
                log_printf( &logger, " Destination ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                log_printf( &logger, " Sequence number: %u\r\n", 
                            ( ( ( uint16_t ) aapi_frame.payload[ 2 ] << 8 ) | 
                              aapi_frame.payload[ 3 ] ) & 0x0FFFu );
                break;
            }
            case NEOMESH868MHZ_RSP_NODE_INFO:
            {
                log_printf( &logger, "---- NODE INFO ----\r\n" );
                log_printf( &logger, " Node ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                log_printf( &logger, " Unique ID: %.2X%.2X%.2X%.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 2 ], ( uint16_t ) aapi_frame.payload[ 3 ],
                            ( uint16_t ) aapi_frame.payload[ 4 ], ( uint16_t ) aapi_frame.payload[ 5 ],
                            ( uint16_t ) aapi_frame.payload[ 6 ] );
                log_printf( &logger, " Type: %.2X\r\n", ( uint16_t ) aapi_frame.payload[ 7 ] );
                break;
            }
            case NEOMESH868MHZ_RSP_NEIGHBOUR_LIST:
            {
                log_printf( &logger, "---- NEIGHBOUR LIST ----\r\n" );
                for ( uint8_t cnt = 0; cnt < aapi_frame.len; cnt += 3 )
                {
                    log_printf( &logger, " %u# -> ", ( uint16_t ) ( ( cnt / 3 ) + 1 ) );
                    if ( ( 0xFF != aapi_frame.payload[ cnt ] ) && 
                         ( 0xFF != aapi_frame.payload[ cnt + 1 ] ) )
                    {
                        log_printf( &logger, "Node ID: %.2X%.2X, RSSI: -%u dBm\r\n", 
                                    ( uint16_t ) aapi_frame.payload[ cnt ], 
                                    ( uint16_t ) aapi_frame.payload[ cnt + 1 ], 
                                    ( uint16_t ) aapi_frame.payload[ cnt + 2 ] );
                    }
                    else
                    {
                        log_printf( &logger, "N/A\r\n" );
                    }
                }
                break;
            }
            case NEOMESH868MHZ_RSP_NETWORK_COMMAND:
            {
                log_printf( &logger, "---- NETWORK COMMAND ----\r\n" );
                log_printf( &logger, " Node ID: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ] );
                log_printf( &logger, " Command: %.2X\r\n", ( uint16_t ) aapi_frame.payload[ 2 ] );
                log_printf( &logger, " Payload: " );
                for ( uint8_t cnt = 3; cnt < aapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) aapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                break;
            }
            case NEOMESH868MHZ_RSP_ROUTE_INFO:
            {
                log_printf( &logger, "---- ROUTE INFO ----\r\n" );
                log_printf( &logger, " Bit Mask: " );
                for ( uint8_t cnt = 0; cnt < aapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) aapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                break;
            }
            case NEOMESH868MHZ_RSP_WES_STATUS:
            {
                log_printf( &logger, "---- WES STATUS ----\r\n" );
                if ( !aapi_frame.payload[ 0 ] )
                {
                    log_printf( &logger, " WES stopped\r\n" );
                }
                else
                {
                    log_printf( &logger, " WES server running\r\n" );
                }
                break;
            }
            case NEOMESH868MHZ_RSP_WES_SETUP:
            {
                log_printf( &logger, "---- WES SETUP ----\r\n" );
                log_printf( &logger, " Unique ID: %.2X%.2X%.2X%.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 0 ], ( uint16_t ) aapi_frame.payload[ 1 ],
                            ( uint16_t ) aapi_frame.payload[ 2 ], ( uint16_t ) aapi_frame.payload[ 3 ],
                            ( uint16_t ) aapi_frame.payload[ 4 ] );
                log_printf( &logger, " Type: %.2X\r\n", ( uint16_t ) aapi_frame.payload[ 5 ] );
                break;
            }
            case NEOMESH868MHZ_RSP_GET_SW_VERSION:
            {
                log_printf( &logger, "---- SW VERSION ----\r\n" );
                log_printf( &logger, " HW/SW Type: %.2X\r\n", ( uint16_t ) aapi_frame.payload[ 0 ] );
                log_printf( &logger, " NeoMesh Version: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 1 ], ( uint16_t ) aapi_frame.payload[ 2 ] );
                log_printf( &logger, " Bootloader Version: %.2X%.2X\r\n", 
                            ( uint16_t ) aapi_frame.payload[ 3 ], ( uint16_t ) aapi_frame.payload[ 4 ] );
                break;
            }
            case NEOMESH868MHZ_RSP_ALT_MODE:
            {
                log_printf( &logger, "---- ALT MODE ----\r\n" );
                if ( !aapi_frame.payload[ 0 ] )
                {
                    log_printf( &logger, " Network in Normal mode\r\n" );
                }
                else
                {
                    log_printf( &logger, " Network in Alternate mode\r\n" );
                }
                break;
            }
            default:
            {
                log_printf( &logger, "---- RESPONSE ----\r\n" );
                log_printf( &logger, " CMD: 0x%.2X\r\n", ( uint16_t ) aapi_frame.cmd );
                log_printf( &logger, " LEN: %u\r\n", ( uint16_t ) aapi_frame.len );
                log_printf( &logger, " Payload: " );
                for ( uint8_t cnt = 0; cnt < aapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) aapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                break;
            }
        }
        if ( exp_rsp == aapi_frame.cmd )
        {
            return NEOMESH868MHZ_OK;
        }
    }
    return NEOMESH868MHZ_ERROR;
}

static err_t neomesh868mhz_parse_sapi_rsp ( uint16_t exp_rsp )
{
    while ( NEOMESH868MHZ_OK == neomesh868mhz_read_sapi_frame ( &neomesh868mhz, &sapi_frame ) )
    {
        switch ( sapi_frame.cmd )
        {
            case NEOMESH868MHZ_SAPI_RSP_OK:
            {
                log_printf( &logger, "---- OK ----\r\n" );
                break;
            }
            case NEOMESH868MHZ_SAPI_RSP_ERROR:
            {
                log_printf( &logger, "---- ERROR ----\r\n" );
                break;
            }
            case NEOMESH868MHZ_SAPI_RSP_BOOTLOADER_START:
            {
                log_printf( &logger, "---- Bootloader STARTED ----\r\n" );
                break;
            }
            case NEOMESH868MHZ_SAPI_RSP_PROTOCOL_STACK_START:
            {
                log_printf( &logger, "---- Protocol Stack STARTED ----\r\n" );
                break;
            }
            case NEOMESH868MHZ_SAPI_RSP_PROTOCOL_STACK_ERROR:
            {
                log_printf( &logger, "---- Protocol Stack ERROR ----\r\n" );
                break;
            }
            case NEOMESH868MHZ_SAPI_RSP_SETTINGS_LIST_OUTPUT:
            {
                log_printf( &logger, "---- Settings List Output ----\r\n" );
                log_printf( &logger, " Payload: " );
                for ( uint8_t cnt = 0; cnt < sapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) sapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                break;
            }
            case NEOMESH868MHZ_SAPI_RSP_SETTINGS_VALUE:
            {
                log_printf( &logger, "---- Settings Value ----\r\n" );
                log_printf( &logger, " Payload: " );
                for ( uint8_t cnt = 0; cnt < sapi_frame.len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) sapi_frame.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
                break;
            }
            case NEOMESH868MHZ_SAPI_RSP_RESET:
            {
                log_printf( &logger, "---- Reset EVENT ----\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, "---- RESPONSE ----\r\n" );
                log_printf( &logger, " CMD: 0x%.4X\r\n", ( uint16_t ) sapi_frame.cmd );
                log_printf( &logger, " PLEN: %u\r\n", ( uint16_t ) sapi_frame.len );
                if ( sapi_frame.len )
                {
                    log_printf( &logger, " Payload: " );
                    for ( uint8_t cnt = 0; cnt < sapi_frame.len; cnt++ )
                    {
                        log_printf( &logger, "%.2X ", ( uint16_t ) sapi_frame.payload[ cnt ] );
                    }
                    log_printf( &logger, "\r\n" );
                }
                break;
            }
        }
        if ( exp_rsp == sapi_frame.cmd )
        {
            return NEOMESH868MHZ_OK;
        }
    }
    return NEOMESH868MHZ_ERROR;
}

// ------------------------------------------------------------------------ END
